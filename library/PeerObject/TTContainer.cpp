/* 
 * A Container object
 * Copyright © 2010, Théo de la Hogue
 * 
 * License: This code is licensed under the terms of the "New BSD License"
 * http://creativecommons.org/licenses/BSD/
 */

#include "TTContainer.h"

#define thisTTClass			TTContainer
#define thisTTClassName		"Container"
#define thisTTClassTags		"node, container"

TT_MODULAR_CONSTRUCTOR,
mPriority(0), 
mDescription(kTTSymEmpty),
mType(TT("control")),
mInitialized(NO),
mContent(kTTValNONE),
maddress(kTTSymEmpty),
mApplication(NULL),
mReturnAddressCallback(NULL),
mReturnValueCallback(NULL),
mObjectsObserversCache(NULL),
mObserver(NULL)
{
	arguments.get(0, (TTPtr*)&mApplication);
	TT_ASSERT("Application passed to TTContainer is not NULL", mApplication);
	
	if(arguments.getSize() == 3) {
		arguments.get(1, (TTPtr*)&mReturnAddressCallback);
		arguments.get(2, (TTPtr*)&mReturnValueCallback);
	}
	
	addAttribute(Priority, kTypeUInt8);
	addAttribute(Description, kTypeSymbol);
	addAttribute(Type, kTypeSymbol);
	
	addAttributeWithGetter(Content, kTypeLocalValue);
	addAttributeProperty(Content, readOnly, YES);
	
	addAttribute(Initialized, kTypeBoolean);
	addAttributeProperty(Initialised, readOnly, YES);
	
	addAttributeWithSetter(address, kTypeSymbol);

	addMessageWithArgument(send);
	
	// needed to be handled by a TTTextHandler
	addMessageWithArgument(writeAsText);
	
	mIsSending = false;	
}

TTContainer::~TTContainer()
{
	unbind();
	
	if (mReturnAddressCallback)
		TTObjectRelease(TTObjectHandle(&mReturnAddressCallback));
	
	if (mReturnValueCallback)
		TTObjectRelease(TTObjectHandle(&mReturnValueCallback));
}

TTErr TTContainer::send(TTValue& AddressAndValue)
{
	TTValue			cacheElement, v;
	TTValuePtr		valueToSend;
	TTObjectPtr		anObject;
	TTSymbolPtr		aRelativeAddress, service;
	TTErr			err;
	
	if (!mIsSending) {
		
		// lock
		mIsSending = true;
		
		if (mObjectsObserversCache) {
			
			// get relativeAddress and valueToSend
			AddressAndValue.get(0, &aRelativeAddress);
			AddressAndValue.get(1, (TTPtr*)&valueToSend);
				
			// get the Data object
			err = mObjectsObserversCache->lookup(aRelativeAddress, cacheElement);
			
			// if the relativeAddress is in the cache
			if (!err) {
				
				cacheElement.get(0, (TTPtr*)&anObject);
				
				// TODO : a generic way to send things to any object
				// it is a Data
				if (anObject->getName() == TT("Data")) {
					
					// What kind of service the data is used for ?
					anObject->getAttributeValue(TT("service"), v);
					v.get(0, &service);
					
					if (service == kTTSym_return)
						return kTTErrNone;
					
					// set the value attribute using a command
					anObject->sendMessage(kTTSym_command, *valueToSend);
					
					// passing messages through the container
					if (service == kTTSym_message)
						if (mReturnAddressCallback && mReturnValueCallback) {
							// return the address
							v = TTValue(aRelativeAddress);
							mReturnAddressCallback->notify(v);
							
							// return the value
							mReturnValueCallback->notify(*valueToSend);
						}
						
				}
				// it is a Viewer
				else if (anObject->getName() == TT("Viewer")) {
					
					// set the address attribute
					anObject->setAttributeValue(kTTSym_Address, *valueToSend);
				}
			}
			// if not use TTModularDirectory instead
			else {
				// unlock
				mIsSending = false;
				return kTTErrGeneric; // TODO : this would allow us to use * also
			}
				
			//TODO : send to other attribute ?
			
		}

		// unlock
		mIsSending = false;	
	}
	
	return kTTErrNone;
}

TTErr TTContainer::setaddress(const TTValue& value)
{	
	unbind();
	maddress = value;
	return bind();
}

TTErr TTContainer::getContent(TTValue& value)
{
	return mObjectsObserversCache->getKeys(value);
}

TTErr TTContainer::bind()
{
	TTNodePtr		aNode;
	TTValuePtr		newBaton;
	TTPtr			aContext;
	TTList			aNodeList, allObjectsNodes;
	TTValue			v;
	TTErr			err = kTTErrNone;
	
	mObjectsObserversCache  = new TTHash();
	
	// 1. Look for all nodes under the address into the directory with the same Context
	err = getDirectoryFrom(this)->Lookup(maddress, aNodeList, &aNode);
	aContext = aNode->getContext();
	
	v.append(aContext);
	err = getDirectoryFrom(this)->LookFor(&aNodeList, TTContainerTestObjectAndContext, &v, allObjectsNodes, &aNode);
	
	// 2. make a cache containing each relativeAddress : Data and Observer
	for (allObjectsNodes.begin(); allObjectsNodes.end(); allObjectsNodes.next()) {
		
		allObjectsNodes.current().get(0, (TTPtr*)&aNode);
		makeCacheElement(aNode);
	}
	
	// 3. Observe any creation or destruction below the address
	mObserver = NULL; // without this, TTObjectInstantiate try to release an oldObject that doesn't exist ... Is it good ?
	TTObjectInstantiate(TT("Callback"), &mObserver, kTTValNONE);
	
	newBaton = new TTValue(TTPtr(this));
	newBaton->append(aContext);
	
	mObserver->setAttributeValue(TT("Baton"), TTPtr(newBaton));
	mObserver->setAttributeValue(TT("Function"), TTPtr(&TTContainerDirectoryCallback));
	
	mObserver->setAttributeValue(TT("Owner"), TT("TTContainer"));		// this is usefull only to debug
	
	getDirectoryFrom(this)->addObserverForNotifications(maddress, *mObserver);
	
	// 4. Check if all cache elements are initialized
	isInitialized();
	
	return kTTErrNone;
}

TTErr TTContainer::makeCacheElement(TTNodePtr aNode)
{
	TTValue			cacheElement, v;
	TTSymbolPtr		aRelativeAddress, service;
	TTObjectPtr		anObject, newObserver;
	TTAttributePtr	anAttribute = NULL;
	TTValuePtr		newBaton;
	TTErr			err;
	
	// process the relative address
	aNode->getOscAddress(&aRelativeAddress, maddress);
	
	// Filter NULL object
	anObject = aNode->getObject();
	if (!anObject)
		return kTTErrGeneric;
	
	cacheElement.append((TTPtr)anObject);
	
	// Special case for Data : observe his value
	// it is a Data
	if (anObject->getName() == TT("Data")) {
		
		// What kind of service the data is used for ?
		anObject->getAttributeValue(TT("service"), v);
		v.get(0, &service);
		
		// observe the Value attribute of parameter and return
		if (service == kTTSym_parameter || service == kTTSym_return) {
			
			// create a Value Attribute observer on it
			anObject->findAttribute(kTTSym_Value, &anAttribute);
			
			newObserver = NULL; // without this, TTObjectInstantiate try to release an oldObject that doesn't exist ... Is it good ?
			TTObjectInstantiate(TT("Callback"), &newObserver, kTTValNONE);
			
			newBaton = new TTValue(TTPtr(this));
			newBaton->append(aRelativeAddress);
			
			newObserver->setAttributeValue(TT("Baton"), TTPtr(newBaton));
			newObserver->setAttributeValue(TT("Function"), TTPtr(&TTContainerValueAttributeCallback));
			newObserver->setAttributeValue(TT("Owner"), TT("TTContainer"));					// this is usefull only to debug
			
			anAttribute->registerObserverForNotifications(*newObserver);
			
			// add observer to the cacheElement
			cacheElement.append((TTPtr)newObserver);
		}
		// add NULL to the cacheElement
		else
			cacheElement.append(NULL);
	}
	// add NULL to the cacheElement
	else
		cacheElement.append(NULL);
	
	
	// don't observe his initialisation state of message and return
	if (service == kTTSym_message || service == kTTSym_return) {
		// add observer to the cacheElement
		cacheElement.append(NULL);
	}
	else {
		// create an Initialized Attribute Observer on it
		err = anObject->findAttribute(kTTSym_Initialized, &anAttribute);
		
		if (!err) {
			newObserver = NULL; // without this, TTObjectInstantiate try to release an oldObject that doesn't exist ... Is it good ?
			TTObjectInstantiate(TT("Callback"), &newObserver, kTTValNONE);
			
			newBaton = new TTValue(TTPtr(this));
			newBaton->append(aRelativeAddress);
			
			newObserver->setAttributeValue(TT("Baton"), TTPtr(newBaton));
			newObserver->setAttributeValue(TT("Function"), TTPtr(&TTContainerInitializedAttributeCallback));
			newObserver->setAttributeValue(TT("Owner"), TT("TTContainer"));					// this is usefull only to debug
			
			anAttribute->registerObserverForNotifications(*newObserver);
			
			// add observer to the cacheElement
			cacheElement.append((TTPtr)newObserver);
		}
		else
			cacheElement.append(NULL);
	}
	
	// append the cacheElement to the cache hash table
	mObjectsObserversCache->append(aRelativeAddress, cacheElement);
	
	return kTTErrNone;
}

TTErr TTContainer::deleteCacheElement(TTNodePtr aNode)
{
	TTSymbolPtr		aRelativeAddress;
	TTValue			cacheElement;
	TTObjectPtr		anObject, aValueObserver, anInitObserver;
	TTAttributePtr	anAttribute;
	TTErr			err;
	
	// process the relative address
	aNode->getOscAddress(&aRelativeAddress, maddress);
	
	// delete attribute observers
	err = mObjectsObserversCache->lookup(aRelativeAddress, cacheElement);
	
	if (!err) {
		
		// get the object using the node instead of the stored one
		anObject = aNode->getObject();
		
		// Filter NULL object
		if (anObject) {
			
			// it is a Data
			if (anObject->getName() == TT("Data")) {
				
				// delete Value observer
				cacheElement.get(1, (TTPtr*)&aValueObserver);
				anAttribute = NULL;
				err = anObject->findAttribute(kTTSym_Value, &anAttribute);
				
				if(!err){
					
					err = anAttribute->unregisterObserverForNotifications(*aValueObserver);
					
					if(!err)
						TTObjectRelease(&aValueObserver);
				}
			}
			
			// delete Initialized observer
			cacheElement.get(2, (TTPtr*)&anInitObserver);
			anAttribute = NULL;
			err = anObject->findAttribute(kTTSym_Initialized, &anAttribute);
			
			if(!err){
				
				err = anAttribute->unregisterObserverForNotifications(*anInitObserver);
				
				if(!err)
					TTObjectRelease(&anInitObserver);
			}
		}
	}

	// remove cacheData
	return mObjectsObserversCache->remove(aRelativeAddress);
}

TTErr TTContainer::unbind()
{
	TTValue			hk, v;
	TTValue			cacheElement;
	TTObjectPtr		anObject, aValueObserver, anInitObserver;
	TTAttributePtr	anAttribute;
	TTSymbolPtr		key;
	TTUInt8			i;
	TTErr			err;
	
	// delete all attribute observers of mDatasObserversCache
	if (mObjectsObserversCache) {
		
		mObjectsObserversCache->getKeys(hk);
		
		for (i=0; i<mObjectsObserversCache->getSize(); i++) {
			
			hk.get(i,(TTSymbolPtr*)&key);
			mObjectsObserversCache->lookup(key, cacheElement);
			cacheElement.get(0, (TTPtr*)&anObject);
			
			if (anObject) {
				// is it a Data ?
				if (anObject->getName() == TT("Data")) {
					
					// delete Value observer
					cacheElement.get(1, (TTPtr*)&aValueObserver);
					anAttribute = NULL;
					err = anObject->findAttribute(kTTSym_Value, &anAttribute);
					
					if (!err) {
						
						err = anAttribute->unregisterObserverForNotifications(*aValueObserver);
						
						if (!err)
							TTObjectRelease(&aValueObserver);
					}
				}
			}
			
			// delete Initialized observer
			cacheElement.get(2, (TTPtr*)&anInitObserver);
			anAttribute = NULL;
			err = anObject->findAttribute(kTTSym_Initialized, &anAttribute);
			
			if (!err) {
				
				err = anAttribute->unregisterObserverForNotifications(*aValueObserver);
				
				if (!err)
					TTObjectRelease(&anInitObserver);
			}
		}
		
		delete mObjectsObserversCache;
	}
	
	// stop life cycle observation
	if (mObserver && getDirectoryFrom(this)) {
		
		err = getDirectoryFrom(this)->removeObserverForNotifications(maddress, *mObserver);
		
		if (!err)
			TTObjectRelease(&mObserver);
	}
	
	maddress = kTTSymEmpty;
	
	return kTTErrNone;
}

TTErr TTContainer::isInitialized()
{
	TTAttributePtr	anAttribute = NULL;
	TTValue			hk, v;
	TTValue			cacheElement;
	TTObjectPtr		anObject;
	TTBoolean		init, result;
	TTSymbolPtr		key, service;
	TTUInt8			i;
	TTErr			err;
	
	// check all initialization states
	result = YES;
	if (mObjectsObserversCache) {
		
		mObjectsObserversCache->getKeys(hk);
		
		for (i=0; i<mObjectsObserversCache->getSize(); i++) {
			
			hk.get(i,(TTSymbolPtr*)&key);
			mObjectsObserversCache->lookup(key, cacheElement);
			cacheElement.get(0, (TTPtr*)&anObject);
			
			if (anObject->getName() == TT("Data")) {
				
				// What kind of service the data is used for ?
				anObject->getAttributeValue(TT("service"), v);
				v.get(0, &service);
				
				if (service == kTTSym_parameter) {
				
					anObject->getAttributeValue(kTTSym_Initialized, v);
					v.get(0, init);
			
					result &= init;
			
					if (!result)
						break;
				}
			}
		}
	}
	
	// set mInitilized if it changes and notify observers
	if (result != mInitialized) {
		mInitialized = result;
		err = this->findAttribute(kTTSym_Initialized, &anAttribute);
		
		if (!err)
			anAttribute->sendNotification(kTTSym_notify, mInitialized);	// we use kTTSym_notify because we know that observers are TTCallback
	}
	
	return kTTErrNone;
}

TTErr TTContainer::writeAsText(const TTValue& value)
{
	TTTextHandlerPtr aTextHandler;
	ofstream		*file;
	TTUInt16		i;
	TTValue			keys, cacheElement, s, arg;
	TTSymbolPtr		name, service;
	TTObjectPtr		anObject;
	
	value.get(0, (TTPtr*)&aTextHandler);
	file = aTextHandler->mWriter;
	
	// html header
	*file <<  "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">";	
	*file << "<html>";
	*file << "\t<head>";
	*file << "\t\t<meta http-equiv=\"content-type\" content=\"text/html;charset=ISO-8859-1\">";
	*file << "<title>" << this->maddress->getCString() << "</title>";	
	
	this->cssDefinition(file);
	
	*file << "\t</head>";
	*file << "";
	
	// html body
	*file << "<body>";
	*file << "\t<div id=\"jmod_header\">";
	
	// Top of page displaying name of module etc.
	*file << "\t<img src=\"../../../documentation/graphics/jmodular.icon.png\" width=\"128\" height=\"128\">";	
	*file << "\t<h1>" << this->maddress->getCString() << "</h1>";
	*file << "\t<h2>" << this->mDescription->getCString() << "</h2>";
	
	// Menu
	*file << "\t<h6><a href=\"../../../documentation/html/index.html\">Table of Contents</a> | <a href=\"../../../documentation/html/modules.html\">Index of Modules</a> | <a href=\"../../../documentation/html/credits.html\">Credits</a> | <a href=\"http://pledgie.com/campaigns/5615\">Donate</a> | <a href=\"http://www.jamoma.org/\">Jamoma.org</a></h6>";
	*file << "\t</div>";
	*file << "";
	
	/* 
		Configuration
	*/
	*file << "\t<h3> Configuration </h3>";
	*file << "\t<p> Model Type: <code>" << this->mType->getCString() << "</code> <br>";
	
	/* 
		Inlets and outlets Objects 
	*/
	
	// TODO : Make TTIn and TTOut and store them
	*file << "\t<p>Number of signal inlets: <code> 0 </code> <br/>";
	*file << "\t<p>Number of signal outlets: <code> 0 </code> <br/>";

	
	mObjectsObserversCache->getKeys(keys);
	/* 
		Data @service parameter
	*/
	*file << "\t<h3> Parameters </h3>";	
	this->dataHeading(file);

	for (i=0; i<keys.getSize(); i++)
	{
		keys.get(i, &name);
		mObjectsObserversCache->lookup(name, cacheElement);
		cacheElement.get(0, (TTPtr*)&anObject);
		
		if (anObject->getName() == TT("Data")) {
			anObject->getAttributeValue(kTTSym_service, s);
			s.get(0, &service);
			
			if (service == kTTSym_parameter) {
				*file << "\t\t<tr>";
				*file << "\t\t\t<td class=\"instructionName\"> " << name->getCString() << "</td>";
				
				arg = TTValue(TTPtr(anObject));
				aTextHandler->setAttributeValue(kTTSym_Object, arg);
				
				arg = TTValue(TTPtr(aTextHandler));
				anObject->sendMessage(TT("writeAsText"), arg);
				*file << "\t\t<tr>";
			}
		}
	}
	
	// End of table
	*file << "\t</table>";
	*file << "";
	*file << "\t<p>&nbsp;</p>";
	*file << "";
	
	
	/* 
	 Data @service message
	 */
	*file << "\t<h3> Messages </h3>";	
	this->dataHeading(file);
	
	for (i=0; i<keys.getSize(); i++)
	{
		keys.get(i, &name);
		mObjectsObserversCache->lookup(name, cacheElement);
		cacheElement.get(0, (TTPtr*)&anObject);
		
		if (anObject->getName() == TT("Data")) {
			anObject->getAttributeValue(kTTSym_service, s);
			s.get(0, &service);
			
			if (service == kTTSym_message) {
				*file << "\t\t<tr>";
				*file << "\t\t\t<td class=\"instructionName\"> " << name->getCString() << "</td>";
				
				arg = TTValue(TTPtr(anObject));
				aTextHandler->setAttributeValue(kTTSym_Object, arg);
				
				arg = TTValue(TTPtr(aTextHandler));
				anObject->sendMessage(TT("writeAsText"), arg);
				*file << "\t\t<tr>";
			}
		}
	}
	
	// End of table
	*file << "\t</table>";
	*file << "";
	*file << "\t<p>&nbsp;</p>";
	*file << "";
	
	
	/* 
	 Data @service return
	 */
	*file << "\t<h3> Returns </h3>";	
	this->dataHeading(file);
	
	for (i=0; i<keys.getSize(); i++)
	{
		keys.get(i, &name);
		mObjectsObserversCache->lookup(name, cacheElement);
		cacheElement.get(0, (TTPtr*)&anObject);
		
		if (anObject->getName() == TT("Data")) {
			anObject->getAttributeValue(kTTSym_service, s);
			s.get(0, &service);
			
			if (service == kTTSym_return) {
				*file << "\t\t<tr>";
				*file << "\t\t\t<td class=\"instructionName\"> " << name->getCString() << "</td>";
				
				arg = TTValue(TTPtr(anObject));
				aTextHandler->setAttributeValue(kTTSym_Object, arg);
				
				arg = TTValue(TTPtr(aTextHandler));
				anObject->sendMessage(TT("writeAsText"), arg);
				*file << "\t\t<tr>";
			}
		}
	}
	
	// End of table
	*file << "\t</table>";
	*file << "";
	*file << "\t<p>&nbsp;</p>";
	*file << "";
	
	
	// Some final info on Jamoma
	*file << "\t<h3> About Jamoma </h3>";		
	*file << "\t<p> Jamoma is a system for creating and exchanging structured Max patches. ";
	*file << "\tIt consists of both a set of guidelines and an implementation of those guidelines. ";
	*file << "\tFor more information please visit <a href=\"http://jamoma.org/\">jamoma.org</a>. </p> ";
	
	// End of page
	*file << "</body>";
	*file << "</html>";

	return kTTErrNone;
}

void TTContainer::dataHeading(ofstream *file)
{		
	*file << "\t<table>";
	*file << "\t\t<tr class=\"tableHeading2\">";
	*file << "\t\t\t<td> /name </td>";
	*file << "\t\t\t<td> /type </td>";
	*file << "\t\t\t<td> /range/bounds </td>";
	*file << "\t\t\t<td> /range/clipmode </td>";
#ifdef TTDATA_RAMPLIB
	*file << "\t\t\t<td> /ramp/drive </td>";
	*file << "\t\t\t<td> /ramp/function </td>";
#endif
	*file << "\t\t\t<td> /dataspace </td>"; 
	*file << "\t\t\t<td> /dataspace/unit/native </td>"; 
	*file << "\t\t\t<td> /repetitions/allow </td>";	
	*file << "\t\t\t<td> /description </td>";
	*file << "\t\t<tr>";
}

void TTContainer::cssDefinition(ofstream *file)
{
	*file << "<style type=\"text/css\">";
	
	*file <<	"\
				body {\
				margin: 0px;\
				font-family: Arial, Helvetica, sans-serif;\
				}\
				\
				h1 {\
				font-size: 24px;\
				font-weight:100;\
				padding-top: 1em;\
				margin: 0;\
				}\
				\
				\
				h2 {\
				font-size: 18px;\
				font-weight:200;\
				margin: 0;\
				color: #555;\
				text-transform: lowercase;\
				}\
				\
				h3 {\
				color: #888;\
				border-bottom: 1px solid #333;\
				font-size: 18px;\
				font-weight:100;\
				margin-top: 20px;\
				margin-bottom: 10px;\
				margin-left: 2%;\
				margin-right: 2%;\
				}\
				\
				h4{\
				color: #333;\
				font-size: 14px;\
				font-weight: bold;\
				margin-bottom: 0px;\
				margin-left: 2%;\
				margin-right: 2%;\
				}\
				\
				h6 {\
				font-size: 12px;\
				font-weight:100;\
				line-height: 1.2;\
				margin-right: 2%;\
				margin-left: 2%;\
				}\
				\
				p {\
				font-size: 12px;\
				font-weight:100;\
				margin: 5px 2%;\
				padding-bottom: 1em;\
				}\
				\
				ul{\
				margin-top:0;\
				padding-top:0;\
				}\
				\
				li {\
				font-size: 12px;\
				font-weight:100;\
				margin-top: 0;\
				margin-left: 10px;\
				padding: 0em 0em 0.3em;\
				}\
				\
				img {\
				padding: 10px 10px 0px 0px;\
				}\
				\
				\
				#jmod_header{\
				display: block;\
				margin: 0 0 40px 0;\
				}\
				\
				#jmod_header img{\
				float: left;\
				}\
				\
				\
				.objectname {\
				font-size: 24px;\
				font-weight: bold;\
				}\
				\
				\
				.moduleName {\
				font-size: 2em;\
				background-color: #c5c5c5;\
				text-align: right;\
				vertical-align: top;\
				font-weight: bold;\
				}\
				.moduleDescription {\
				font-size: 1em;\
				background-color: #000000;\
				color: #c5c5c5;\
				text-align: right;\
				vertical-align: top;\
				}\
				\
				.tableHeading2 {\
				background-color: #eee;\
				text-align: left;\
				vertical-align: top;\
				font-weight:bold;\
				font-size: 12px;\
				}\
				\
				table {\
				border: 0px;\
				width: 96%;\
				margin-top: 10px;\
				margin-bottom: 10px;\
				margin-left: 2%;\
				font-size: 14px;\
				}\
				";
	
	*file <<	"\
				\
				.instructionName {\
				font-family: 'Courier New', Courier, mono;\
				background-color: #edd;\
				vertical-align: top;\
				}\
				\
				.instructionType {\
				font-family: 'Times New Roman', Times, serif;\
				background-color: #eee;\
				vertical-align: top;\
				}\
				\
				.instructionDataspace {\
				font-family: 'Times New Roman', Times, serif;\
				background-color: #eed;\
				vertical-align: top;\
				}\
				\
				.instructionDataspaceUnitNative {\
				font-family: 'Times New Roman', Times, serif;\
				background-color: #eee;\
				vertical-align: top;\
				}\
				\
				.instructionRangeBounds {\
				font-family: 'Times New Roman', Times, serif;\
				background-color: #eed;\
				vertical-align: top;\
				}\
				.instructionRangeClipmode {\
				font-family: 'Times New Roman', Times, serif;\
				background-color: #eee;\
				vertical-align: top;\
				}\
				.instructionRampDrive {\
				font-family: 'Times New Roman', Times, serif;\
				background-color: #eed;\
				vertical-align: top;\
				}\
				.instructionRampFunction {\
				font-family: 'Times New Roman', Times, serif;\
				background-color: #eee;\
				vertical-align: top;\
				}\
				.instructionRepetitionsAllow {\
				font-family: 'Times New Roman', Times, serif;\
				background-color: #eed;\
				vertical-align: top;\
				}\
				.instructionDescription {\
				font-family: 'Times New Roman', Times, serif;\
				background-color: #eee;\
				vertical-align: top;\
				}\
				td {\
				padding-right: 5px;\
				padding-left: 5px;\
				}\
				ul {\
				list-style-type: disc;\
				}\
				.patchimage {\
				clear: both;\
				}\
				.comment {\
				color: #6666FF;\
				}\
				.smallTable {\
				width: 400px;\
				border: none;\
				}\
				caption {\
				font-size: 11px;\
				font-style: italic;\
				}\
				.filepath {\
				font-family: 'Courier New', Courier, mono;\
				}\
				.instruction {\
				font-family: 'Courier New', Courier, mono;\
				}\
				";
	
	*file << "</style>";
}

#if 0
#pragma mark -
#pragma mark Some Methods
#endif

TTErr TTContainerDirectoryCallback(TTPtr baton, TTValue& data)
{
	TTValuePtr		b;
	TTValue			arg;
	TTContainerPtr	aContainer;
	TTPtr			hisContext;
	TTCallbackPtr	anObserver;
	TTNodePtr		aNode;
	TTSymbolPtr		anAddress;
	TTUInt8			flag;
	
	// unpack baton (a TTContainerPtr, his Context)
	b = (TTValuePtr)baton;
	b->get(0, (TTPtr*)&aContainer);
	b->get(1, (TTPtr*)&hisContext);
	
	// Unpack data (oscAddress, aNode, flag, anObserver)
	data.get(0, &anAddress);
	data.get(1, (TTPtr*)&aNode);
	data.get(2, flag);
	data.get(3, (TTPtr*)&anObserver);
	
	// Prepare argument
	arg.append(hisContext);
	
	switch (flag) {

		case kAddressCreated :
		{
			if (TTContainerTestObjectAndContext(aNode, &arg))
			   aContainer->makeCacheElement(aNode);
			
			break;
		}
			
		case kAddressDestroyed :
		{
			if (TTContainerTestObjectAndContext(aNode, &arg)) 
				 aContainer->deleteCacheElement(aNode);
			
			break;
		}
			
		default:
			break;
	}
	
	return kTTErrNone;
}

TTErr TTContainerValueAttributeCallback(TTPtr baton, TTValue& data)
{
	TTValuePtr		b;
	TTContainerPtr	aContainer;
	TTSymbolPtr		relativeAddress;
	TTValue			address;
		
	// unpack baton
	b = (TTValuePtr)baton;
	b->get(0, (TTPtr*)&aContainer);
	b->get(1, &relativeAddress);
	
	if (aContainer->mReturnAddressCallback && aContainer->mReturnValueCallback) {
		// return the address
		address.append(relativeAddress);
		aContainer->mReturnAddressCallback->notify(address);
		
		// return the value
		aContainer->mReturnValueCallback->notify(data);
	}
	else
		return kTTErrGeneric;
	
	return kTTErrNone;
}

TTErr TTContainerInitializedAttributeCallback(TTPtr baton, TTValue& data)
{
	TTValuePtr		b;
	TTContainerPtr	aContainer;
	
	// unpack baton
	b = (TTValuePtr)baton;
	b->get(0, (TTPtr*)&aContainer);
	
	// Check if all cache elements are initialized
	aContainer->isInitialized();
	
	return kTTErrNone;
}

TTBoolean TTContainerTestObjectAndContext(TTNodePtr n, TTPtr args)
{
	TTValue		v;
	TTValuePtr	av;
	TTPtr		c, t_c, p_c;
	
	// our context
	av = (TTValuePtr)args;
	av->get(0, (TTPtr*)&t_c);
	
	// context of the tested node
	c = n->getContext();
	
	// context of the parent of the tested node
	if (n->getParent())
		if (n->getParent()->getName() != S_SEPARATOR)
			p_c = n->getParent()->getContext();
		else
			p_c = NULL;
	
	// Keep only nodes from our context if they aren't under the root (p_c is NULL)
	// if contexts are different, check also if the parent context is the same as our context
	return (c == t_c && p_c ) || (c != t_c && p_c == t_c );

}
