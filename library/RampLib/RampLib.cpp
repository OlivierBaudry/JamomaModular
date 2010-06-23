/* 
 * Jamoma RampLib Base Class
 * Copyright © 2008, Tim Place
 * 
 * License: This code is licensed under the terms of the GNU LGPL
 * http://www.gnu.org/licenses/lgpl.html 
 */

#ifdef WIN_VERSION
 #pragma warning(disable:4083) //warning C4083: expected 'newline'; found identifier 's'
#endif // WIN_VERSION

#include "RampLib.h"
#include "ext.h"

#define thisTTClass RampUnit

RampUnit::RampUnit(const char* rampName, RampUnitCallback aCallbackMethod, void *aBaton) : 
	TTObject(kTTValNONE),
	mFunction(NULL),
	callback(aCallbackMethod),
	baton(aBaton),
	startValue(NULL),
	targetValue(NULL),
	currentValue(NULL),
	normalizedValue(0.0),
	numValues(0),
	functionUnit(NULL)
{
	setNumValues(1);
	currentValue[0] = 0.0;
	targetValue[0] = 0.0;
	startValue[0] = 0.0;

	addAttributeWithSetter(Function, kTypeSymbol);
	setAttributeValue(TT("Function"), TT("linear"));
}


RampUnit::~RampUnit()
{
	TTObjectRelease(&functionUnit);
	delete [] currentValue;
	delete [] targetValue;
	delete [] startValue;
}


void RampUnit::set(TTUInt32 newNumValues, TTFloat64 *newValues)
{
	TTUInt32 i;
	
	stop();
	setNumValues(newNumValues);
	for (i=0; i<newNumValues; i++)
		currentValue[i] = newValues[i];
}


TTErr RampUnit::setFunction(const TTValue& functionName)
{
	TTErr		err;
	TTSymbolPtr	newFunctionName = NULL;
	
	functionName.get(0, &newFunctionName);
	
	if (newFunctionName == TT("none"))
		newFunctionName = TT("linear");
	
	if (newFunctionName == mFunction)
		return kTTErrNone;
	
	mFunction = newFunctionName;
	err = FunctionLib::createUnit(mFunction, (TTObject**)&functionUnit);
	if (err)
		logError("Jamoma ramp unit failed to load the requested FunctionUnit from TTBlue.");
	return err;
}


TTErr RampUnit::getFunctionParameterNames(TTValue& names)
{
	functionUnit->getAttributeNames(names);
	return kTTErrNone;
}


TTErr RampUnit::setFunctionParameterValue(TTSymbol* parameterName, TTValue& newValue)
{
	functionUnit->setAttributeValue(parameterName, newValue);
	return kTTErrNone;
}


TTErr RampUnit::getFunctionParameterValue(TTSymbol* parameterName, TTValue& value)
{
	functionUnit->getAttributeValue(parameterName, value);
	return kTTErrNone;
}


void RampUnit::setNumValues(TTUInt32 newNumValues)
{
	if (newNumValues != numValues) {
		if (numValues != 0) {
			delete [] currentValue;
			delete [] targetValue;
			delete [] startValue;
		}
		
		currentValue = new TTFloat64[newNumValues];
		targetValue = new TTFloat64[newNumValues];
		startValue = new TTFloat64[newNumValues];
		numValues = newNumValues;
	}
	sendMessage(TT("numValuesChanged"));	// Notify sub-classes (if they respond to this message)
}

 
/***************************************************************************
	RampLib
 ***************************************************************************/

#include "AsyncRamp.h"
#include "NoneRamp.h"
#include "QueueRamp.h"
#include "SchedulerRamp.h"


JamomaError RampLib::createUnit(const TTSymbol* unitName, RampUnit **unit, RampUnitCallback callback, void* baton)
{
	if (*unit)
		delete *unit;

	// These should be alphabetized
	if (unitName == TT("async"))
		*unit = (RampUnit*) new AsyncRamp(callback, baton);
	else if (unitName == TT("none"))
		*unit = (RampUnit*) new NoneRamp(callback, baton);
	else if (unitName == TT("queue"))
		*unit = (RampUnit*) new QueueRamp(callback, baton);
	else if (unitName == TT("scheduler"))
		*unit = (RampUnit*) new SchedulerRamp(callback, baton);
	else {
		// Invalid function specified default to linear
		error("Jamoma RampLib: Invalid RampUnit ( %s ) specified", (char*)unitName);
		*unit = (RampUnit*) new NoneRamp(callback, baton);
	}
	return JAMOMA_ERR_NONE;
}


void RampLib::getUnitNames(TTValue& unitNames)
{
	unitNames.clear();
	unitNames.append(TT("async"));
	unitNames.append(TT("none"));
	unitNames.append(TT("queue"));
	unitNames.append(TT("scheduler"));
}

