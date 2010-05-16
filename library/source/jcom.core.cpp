/* 
 * jcom.core
 * shared code used by the jamoma core externals
 * By Tim Place, Copyright � 2006
 * 
 * License: This code is licensed under the terms of the GNU LGPL
 * http://www.gnu.org/licenses/lgpl.html 
 */

//#include "ext.h"		// Max externals header
//#include "ext_obex.h"	// Obex header
#include "jcom.core.h"
#include "Jamoma.h"

#pragma mark -
#pragma mark Hub Bindings

// Registering with the jcom.hub object
t_object *jcom_core_subscribe(t_object *x, t_symbol *name, t_object *container, t_symbol *object_type)
{
	t_object	*patcher = container;
	t_object	*box;
	t_symbol	*objclass = NULL;
	t_object	*hub = NULL;
	
again5:
	box = object_attr_getobj(patcher, _sym_firstobject);
	while (box) {
		objclass = object_attr_getsym(box, _sym_maxclass);
		if (objclass == jps_jcom_hub) {
			hub = object_attr_getobj(box, _sym_object);
			object_method(hub, jps_subscribe, name, x, object_type);
			return hub;
		}
		box = object_attr_getobj(box, _sym_nextobject);
	}
	patcher = object_attr_getobj(patcher, _sym_parentpatcher);
	if (patcher)
		goto again5;

	return NULL;
}


// Registering with the jcom.hub object -- when we have a pointer to the hub already
t_object *jcom_core_subscribe(t_object *x, t_symbol *name, t_object *container, t_symbol *object_type, t_object* hub)
{	
	object_method(hub, jps_subscribe, name, x, object_type);
	return hub;
}


// Unregister from the jcom.hub object
//void jcom_core_unsubscribe(void *hub, t_symbol *name)
void jcom_core_unsubscribe(t_object *hub, void *object)
{
	if (hub)
		object_method(hub, jps_unsubscribe, object);
}


#pragma mark -
#pragma mark Atom Utilities

// Copying all of the elements should be faster than branching and copying one element
//	(that's the theory anyway...)
void jcom_core_atom_copy(t_atom *dst, t_atom *src)
{
	//	memcpy(dst, src, sizeof(t_atom));
	sysmem_copyptr(src, dst, sizeof(t_atom));
}


bool jcom_core_atom_compare(t_symbol *type, t_atom *a1, t_atom *a2)
{
	if (!a1 || !a2)
		return 0;
		
	if (type == jps_decimal) {				// float is first so that it gets process the most quickly
		if (atom_getfloat(a1) == atom_getfloat(a2))
			return 1;
	}
	else if ((type == jps_integer) || (type == jps_boolean)) {
		if (atom_getlong(a1) == atom_getlong(a2))
			return 1;
	}
	else if (type == jps_string) {
		if (atom_getsym(a1) == atom_getsym(a2))
			return 1;
	}
	else if ((type == jps_generic) || (type == jps_array)) {
		// type array should be checked here as well.  If type == array and this function is called
		// it means we are dealing with a list of length 1, so we only need to compare one atom anyway.
		
		// note that if the two are of different types, then they are obviously not the same
		if ((a1->a_type == A_LONG) && (a2->a_type == A_LONG)) {
			if (a1->a_w.w_long == a2->a_w.w_long)
				return 1;
		}
		else if ((a1->a_type == A_FLOAT) && (a2->a_type == A_FLOAT)) {
			if (a1->a_w.w_float == a2->a_w.w_float)
				return 1;
		}
		else if ((a1->a_type == A_SYM) && (a2->a_type == A_SYM)) {
			if (a1->a_w.w_sym == a2->a_w.w_sym)
				return 1;
		}
	}
	else
		error("atom_compare: cannot do comparison on this data type");
	return 0;
}


void jcom_core_file_writeline(t_filehandle *fh, long *the_eof, char *the_text)
{
	char 	tempstring[4096];
	short	err = 0;
	long	len = 0;
	
	strcpy(tempstring, the_text);
	strcat(tempstring, "\n");
	len = strlen(tempstring);
	err = sysfile_write(*fh, &len, &tempstring);
	if (err) {
		error("jamoma: sysfile_write error (%d)", err);
		return;
	}
	*the_eof = *the_eof + len;
}


// Compare Strings: Is s2 after s1 in alphabetical order?
bool jcom_core_string_compare(char *s1, char *s2)
{
	short i;
	short len1 = strlen(s1);
	short len2 = strlen(s2);
	bool result = false;
	bool keepgoing = true;
	
	if (len2 < len1)
		len1 = len2;	// only compare the characters of the short string
		
	for (i=0; i<len1 && keepgoing; i++) {
		if (s1[i] < s2[i]) {
			result = true;
			keepgoing = false;
		}
		else if (s1[i] > s2[i])
			keepgoing = false;
	}
	return result;
}


// Load an external for internal use
// returns true if successful
bool jcom_core_loadextern(t_symbol *objectname, long argc, t_atom *argv, t_object **object)
{
	t_class 	*c = NULL;
	t_object	*p = NULL;

	c = class_findbyname(jps_box, objectname);
	if (!c) {
		p = (t_object *)newinstance(objectname, 0, NULL);
		if (p) {
			c = class_findbyname(jps_box, objectname);
			freeobject(p);
			p = NULL;
		}
		else {
			error("jamoma: could not load extern (%s) within the core", objectname->s_name);
			return false;
		}
	}

	if (*object != NULL) {			// if there was an object set previously, free it first...
		object_free(*object);
		*object = NULL;
	}

	*object = (t_object *)object_new_typed(CLASS_BOX, objectname, argc, argv);
	return true;
}


// Function the translates a Max path+filename combo into a correct absolutepath
// TODO: remove this function once we've completed the transition to Max5, as path_topathname() is fixed for Max5
void jcom_core_getfilepath(short in_path, char *in_filename, char *out_filepath)
{
	char	path[4096];
	
	path_topathname(in_path, in_filename, path);

#ifdef MAC_VERSION
	char *temppath;
	temppath = strchr(path, ':');
	*temppath = '\0';
	temppath += 1;

	// at this point temppath points to the path after the volume, and out_filepath points to the volume
	sprintf(out_filepath, "/Volumes/%s%s", path, temppath);
#else // WIN_VERSION
	strcpy(out_filepath, path);
#endif
}


// Add attributes that are common to many subscribers (such as parameter, message, and return)
void jcom_core_subscriber_classinit_common(t_class *c, t_object *attr, bool define_name)
{
	// METHODS
	class_addmethod(c, (method)jcom_core_subscriber_subscribe,	"subscribe",	A_CANT, 0); // called by a new hub to tell us to subscribe to it
	class_addmethod(c, (method)jcom_core_subscriber_hubrelease,	"release",		A_CANT, 0);	// notification of hub being freed
	class_addmethod(c, (method)object_obex_dumpout,				"dumpout",		A_CANT, 0);  

	// ATTRIBUTE: name
	if (define_name)
		jamoma_class_attr_new(c, "name", _sym_symbol, (method)jcom_core_subscriber_attribute_common_setname, (method)jcom_core_attr_getname);
}


void jcom_core_subscriber_classinit_extended(t_class *c, t_object *attr, bool define_name)
{
	jcom_core_subscriber_classinit_common(c, attr, define_name);

	// TODO: The name of the attributes should be substituted for their jps_* symbol pointers.
	
	// ATTRIBUTE: range <low, high>
	jamoma_class_attr_array_new(c, 	"range/bounds", 		_sym_float32, 2, (method)jcom_core_attr_setrange, (method)jcom_core_attr_getrange);
		
	// ATTRIBUTE: clipmode - options are none, low, high, both, wrap, fold
	jamoma_class_attr_new(c, 		"range/clipmode",	 	_sym_symbol, (method)jcom_core_attr_setclipmode, (method)jcom_core_attr_getclipmode);
	CLASS_ATTR_ENUM(c,				"range/clipmode",		0,	"none low high both wrap fold");	

	// ATTRIBUTE: repetitions - 0 means repetitive values are not allowed, 1 means they are
	jamoma_class_attr_new(c, 		"repetitions/allow", 	_sym_long, (method)jcom_core_attr_setrepetitions, (method)jcom_core_attr_getrepetitions);

	// ATTRIBUTE: type 
	// this is not defined here because some objects (i.e jcom.parameter) need to treat this in different ways

	// ATTRIBUTE: description - does nothing, but is accessed by jcom.dispatcher for /autodoc generation
	jamoma_class_attr_new(c,		"description", 			_sym_symbol, (method)jcom_core_attr_setdescription, (method)jcom_core_attr_getdescription);
	CLASS_ATTR_STYLE(c,				"description",			0, "text_onesymbol");
}


// arg is subscriber name
void jcom_core_subscriber_new_common(t_jcom_core_subscriber_common *x, t_symbol *name, t_symbol *subscriber_type)
{
	t_atom 	a;
	
	x->subscriber_type = subscriber_type;
	x->custom_subscribe = NULL;
	x->hub = NULL;
	x->module_name = _sym_nothing;

	// we call the function directly here rather than use object_attr_setvalueof() 
	// because parameters with pattr bindings don't actually have their own 'name' attribute
	atom_setsym(&a, name);
	jcom_core_subscriber_attribute_common_setname(x, NULL, 1, &a);
 	
	x->container = jamoma_object_getpatcher((t_object*)x);
	
	// set up the jcom.receive the listens to broadcast messages from the hub
	atom_setsym(&a, jps_jcom_broadcast_fromHub);	
}


void jcom_core_subscriber_new_extended(t_jcom_core_subscriber_extended *x, t_symbol *name, t_symbol *subscriber_type)
{
	jcom_core_subscriber_new_common((t_jcom_core_subscriber_common *)x, name, subscriber_type);
	
	x->attr_range[0] = 0.0;
	x->attr_range[1] = 1.0;
	x->attr_clipmode = jps_none;
	x->attr_description = _sym_nothing;
	x->attr_type = jps_generic;
	x->attr_repetitions = 0;	// this should default to the most efficient and common way of working, so repetitions are filtered [TAP]
}


// function for registering with the jcom.hub object
void jcom_core_subscriber_subscribe(t_jcom_core_subscriber_common *x)
{
	if (x->hub)
		x->hub = jcom_core_subscribe((t_object*)x, x->attr_name, x->container, x->subscriber_type, x->hub);
	else
		x->hub = jcom_core_subscribe((t_object*)x, x->attr_name, x->container, x->subscriber_type);
	if (x->hub) {
		x->module_name = (t_symbol *)object_method(x->hub, jps_core_module_name_get);
		if (x->custom_subscribe)
			x->custom_subscribe(x);
	}
}


// Notification that the hub no longer exists
void jcom_core_subscriber_hubrelease(t_jcom_core_subscriber_common *x)
{
	x->hub = NULL;
}


// Set a custom subscribe method
void jcom_core_subscriber_setcustomsubscribe_method(t_jcom_core_subscriber_common *x, t_subscribe_method meth)
{
	x->custom_subscribe = meth;
}


// Unsubscribe and common freeing code
void jcom_core_subscriber_common_free(t_jcom_core_subscriber_common *x)
{
	jcom_core_unsubscribe(x->hub, x);
	x->hub = NULL;
}




// COMMON ATTRIBUTE: name
t_max_err jcom_core_subscriber_attribute_common_setname(t_jcom_core_subscriber_common *x, void *attr, long argc, t_atom *argv)
{	
	t_symbol *arg = atom_getsym(argv);
	x->attr_name = arg;

	if (arg->s_name[strlen(arg->s_name)-1] == '*')
		x->has_wildcard = true;
	else
		x->has_wildcard = false;

//	if (x->subscriber_type == jps_subscribe_return && x->hub) {
	if (x->hub) {
		jcom_core_unsubscribe(x->hub, x);
		x->hub = NULL;
//		x->attr_name = atom_getsym(argv);
		jcom_core_subscriber_subscribe((t_jcom_core_subscriber_common*)x);
	}
	// if the client understands 'update_name' then we call it
	object_method(x, SymbolGen("update_name"));
	
	return MAX_ERR_NONE;
}

t_max_err jcom_core_attr_getname(t_jcom_core_subscriber_extended *x, void *attr, long *argc, t_atom **argv)
{
	*argc = 1;
	if (!(*argv)) // otherwise use memory passed in
		*argv = (t_atom *)sysmem_newptr(sizeof(t_atom));
	atom_setsym(*argv, x->attr_name);
	return MAX_ERR_NONE;
}

t_max_err jcom_core_attr_setname(t_jcom_core_subscriber_extended *x, void *attr, long argc, t_atom *argv)
{
	if (argc && argv) {
		jcom_core_unsubscribe(x->hub, x);
		x->hub = NULL;
		x->attr_name = atom_getsym(argv);
		jcom_core_subscriber_subscribe((t_jcom_core_subscriber_common*)x);
	}
	return MAX_ERR_NONE;
}


// We are using a custom setter here because relying on the offset seemed to cause memory corruption
// This was the easiest way to avoid that.
t_max_err jcom_core_attr_setrange(t_jcom_core_subscriber_extended *x, void *attr, long argc, t_atom *argv)
{	
	if (argc)
		x->attr_range[0] = atom_getfloat(argv+0);
	if (argc > 1)
		x->attr_range[1] = atom_getfloat(argv+1);
	
	return MAX_ERR_NONE;
}

t_max_err jcom_core_attr_getrange(t_jcom_core_subscriber_extended *x, void *attr, long *argc, t_atom **argv)
{
	*argc = 2;
	
	//sysmem_ptrsize(*argv)
	// FIXME: This checks if we have memory passed in, good, but how do we know if it is enough memory for 2 atoms? [TAP]
	if (!(*argv)) // otherwise use memory passed in
		*argv = (t_atom *)sysmem_newptr(sizeof(t_atom) * 2);

	atom_setfloat(*argv, x->attr_range[0]);
	atom_setfloat(*argv+1, x->attr_range[1]);

	return MAX_ERR_NONE;
}


t_max_err jcom_core_attr_getrepetitions(t_jcom_core_subscriber_extended *x, void *attr, long *argc, t_atom **argv)
{
	*argc = 1;
	if (!(*argv)) // otherwise use memory passed in
		*argv = (t_atom *)sysmem_newptr(sizeof(t_atom));
	atom_setlong(*argv, x->attr_repetitions);
	return MAX_ERR_NONE;
}

t_max_err jcom_core_attr_setrepetitions(t_jcom_core_subscriber_extended *x, void *attr, long argc, t_atom *argv)
{
	if (argc && argv)
		x->attr_repetitions = atom_getlong(argv);
	return MAX_ERR_NONE;
}


t_max_err jcom_core_attr_getclipmode(t_jcom_core_subscriber_extended *x, void *attr, long *argc, t_atom **argv)
{
	*argc = 1;
	if (!(*argv)) // otherwise use memory passed in
		*argv = (t_atom *)sysmem_newptr(sizeof(t_atom));
	atom_setsym(*argv, x->attr_clipmode);
	return MAX_ERR_NONE;
}

t_max_err jcom_core_attr_setclipmode(t_jcom_core_subscriber_extended *x, void *attr, long argc, t_atom *argv)
{
	if (argc && argv)
		x->attr_clipmode = atom_getsym(argv);
	return MAX_ERR_NONE;
}


t_max_err jcom_core_attr_getdescription(t_jcom_core_subscriber_extended *x, void *attr, long *argc, t_atom **argv)
{
	*argc = 1;
	if (!(*argv)) // otherwise use memory passed in
		*argv = (t_atom *)sysmem_newptr(sizeof(t_atom));
	atom_setsym(*argv, x->attr_description);

	return MAX_ERR_NONE;
}

t_max_err jcom_core_attr_setdescription(t_jcom_core_subscriber_extended *x, void *attr, long argc, t_atom *argv)
{
	char*	text = NULL;
	long	textsize = 0;
	
	atom_gettext(argc, argv, &textsize, &text, OBEX_UTIL_ATOM_GETTEXT_SYM_NO_QUOTE);
	if (text && textsize) {
		x->attr_description = SymbolGen(text);
		sysmem_freeptr(text);
	}
	return MAX_ERR_NONE;
}


