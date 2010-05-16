/* 
 * jcom.map
 * External for Jamoma: map input to output: y=f(x)
 * Copyright © 2007
 * 
 * License: This code is licensed under the terms of the GNU LGPL
 * http://www.gnu.org/licenses/lgpl.html 
 */

#include "Jamoma.h"


// Data Structure for this object
typedef struct _map {
	t_object		ob;
	void			*outlet;
	t_symbol		*attr_function;
	double			attr_inputMin;
	double			attr_inputMax;
	double			attr_outputMin;
	double			attr_outputMax;
	double 			a, b;				// Coefficients used for normalizing input
	double			c, d;				// Coefficients used for scaling normalized output
	TTAudioObject	*functionUnit;
	bool			valid;				// true if the functionUnit can be used
	TTHashPtr		parameterNames;		// cache of parameter names, mapped from lowercase (Max) to uppercase (TT)
} t_map;


// Prototypes for methods
void*		map_new(t_symbol *name, long argc, t_atom *argv);
void		map_free(t_map *obj);
void		map_assist(t_map *obj, void *b, long m, long a, char *s);
void		map_int(t_map *obj, long x);
void		map_float(t_map *obj, double x);
void		map_list(t_map* obj, SymbolPtr message, AtomCount ac, AtomPtr av);
void		map_getFunctions(t_map *x, t_symbol *msg, long argc, t_atom *argv);
void		map_getParameter(t_map *x, t_symbol *msg, long argc, t_atom *argv);
void		map_getFunctionParameters(t_map *x, t_symbol *msg, long argc, t_atom *argv);
void		map_setParameter(t_map *x, t_symbol *msg, long argc, t_atom *argv);
t_max_err	map_setFunction(t_map *obj, void *attr, long argc, t_atom *argv);
t_max_err	map_setInputMin(t_map *obj, void *attr, long argc, t_atom *argv);
t_max_err	map_setInputMax(t_map *obj, void *attr, long argc, t_atom *argv);
void 		map_scaleInput(t_map *obj);
t_max_err	map_setOutputMin(t_map *obj, void *attr, long argc, t_atom *argv);
t_max_err	map_setOutputMax(t_map *obj, void *attr, long argc, t_atom *argv);
void 		map_scaleOutput(t_map *obj);


// Globals
t_class		*map_class;			// Required. Global pointing to this class


/************************************************************************************/
// Main() Function

int JAMOMA_EXPORT_MAXOBJ main(void)
{
	t_class *c;
	
	jamoma_init();
	common_symbols_init();

	// Define our class
	c = class_new("jcom.map",(method)map_new, (method)map_free, sizeof(t_map), (method)0L, A_GIMME, 0);

	// Make methods accessible for our class: 
	class_addmethod(c, (method)map_int,						"int",						A_LONG, 0L);
	class_addmethod(c, (method)map_float,					"float",					A_FLOAT, 0L);
	class_addmethod(c, (method)map_list,					"list",						A_GIMME, 0L);
	class_addmethod(c, (method)map_getFunctions,			"functions.get",			A_GIMME, 0);
 	class_addmethod(c, (method)map_getParameter,			"parameter.get",			A_GIMME, 0);
	class_addmethod(c, (method)map_getFunctionParameters,	"function.parameters.get",	A_GIMME, 0);
 	class_addmethod(c, (method)map_setParameter,			"parameter",				A_GIMME, 0);
	class_addmethod(c, (method)map_assist,					"assist",					A_CANT, 0L); 
    class_addmethod(c, (method)object_obex_dumpout,			"dumpout",					A_CANT,0);

	// ATTRIBUTE: set the function to use
	class_addattr(c, 
		attr_offset_new("function", _sym_symbol, 0,
		(method)0, (method)map_setFunction, calcoffset(t_map, attr_function)));
	// ATTRIBUTE: set the input minimum value
	class_addattr(c,
		attr_offset_new("inputMin", _sym_float64, 0,
		(method)0, (method)map_setInputMin, calcoffset(t_map, attr_inputMin)));
	// ATTRIBUTE: set the input maximum value
	class_addattr(c,
		attr_offset_new("inputMax", _sym_float64, 0,
		(method)0, (method)map_setInputMax, calcoffset(t_map, attr_inputMax)));	
		
	// ATTRIBUTE: set the output minimum value
	class_addattr(c,
		attr_offset_new("outputMin", _sym_float64, 0,
		(method)0, (method)map_setOutputMin, calcoffset(t_map, attr_outputMin)));
	// ATTRIBUTE: set the output maximum value
	class_addattr(c,
		attr_offset_new("outputMax", _sym_float64, 0,
		(method)0, (method)map_setOutputMax, calcoffset(t_map, attr_outputMax)));

	// Finalize our class
	class_register(CLASS_BOX, c);
	map_class = c;
	return 0;
}


/************************************************************************************/
// Object Life

void *map_new(t_symbol *name, long argc, t_atom *argv)
{
	t_map *obj;									// Declare an object (based on our struct)

	obj = (t_map *)object_alloc(map_class);		// Create object, store pointer to it (get 1 inlet free)
	if (obj) {
		obj->parameterNames = new TTHash;
		object_obex_store((void *)obj, _sym_dumpout, (object *)outlet_new(obj,NULL));
	    obj->outlet = outlet_new(obj, 0);
		obj->attr_function = _sym_nothing;
		obj->attr_inputMin = 0;
		obj->attr_inputMax = 1;
		obj->attr_outputMin = 0;
		obj->attr_outputMax = 1;
		obj->functionUnit = NULL;
		obj->valid = false;
		attr_args_process(obj, argc, argv);
		map_scaleInput(obj);
		map_scaleOutput(obj);
		if (!obj->functionUnit)
			object_attr_setsym(obj, gensym("function"), gensym("linear"));
	}
	return obj;										// Return pointer to our instance
}


void map_free(t_map *obj)
{
	if (obj->functionUnit)
		delete obj->functionUnit;
	delete obj->parameterNames;
}


/************************************************************************************/
// Methods bound to input/inlets

// Method for Assistance Messages
void map_assist(t_map *x, void *b, long msg, long arg, char *dst)
{
	if (msg==1) 							// Inlets
		strcpy(dst, "x");
	else if (msg==2) { 					// Outlets
		switch(arg) {
			case 0: strcpy(dst, "y=f(x)"); break;
			default: strcpy(dst, "dumpout"); break;
 		}
 	}
}


void map_int(t_map *obj, long x)
{
	map_float(obj, (double)x);
}


void map_float(t_map *obj, double x)
{
	double y;
	
	if (obj->valid) {
		//y = obj->c * obj->functionUnit->map(obj->a * x + obj->b) + obj->d;
		obj->functionUnit->calculate(obj->a * x + obj->b, y);
		y = obj->c * y + obj->d;
		outlet_float(obj->outlet, y);
	}
}


void map_list(t_map* obj, SymbolPtr message, AtomCount argc, AtomPtr argv)
{	
	if (obj->valid) {
		TTValue		v;
		TTValue		ret;
		double		x, y;
		AtomCount	ac = 0;
		AtomPtr		av = NULL;

		v.clear();
		for (int i=0; i<argc; i++) {
			x = atom_getfloat(argv+i);
			v.append(obj->a * x + obj->b);
		}
		
		obj->functionUnit->calculate(v, ret);
		
		ac = ret.getSize();
		av = new Atom[ac];
		for (int i=0; i<ac; i++) {
			ret.get(i, y);
			y = obj->c * y + obj->d;
			atom_setfloat(av+i, y);
		}

		outlet_anything(obj->outlet, _sym_list, ac, av);
		delete [] av;
	}
}


void map_getFunctions(t_map *obj, t_symbol *msg, long argc, t_atom *argv)
{
	t_atom		a[2];
	long		numFunctions = 0;
	long		i;
	TTValue		functionNames;
	TTSymbol*	aName;
	
	atom_setsym(a+0, gensym("clear"));
	object_obex_dumpout(obj, gensym("functions"), 1, a);
	
	FunctionLib::getUnitNames(functionNames);
	numFunctions = functionNames.getSize();

	atom_setsym(a+0, gensym("append"));
	for (i=0; i<numFunctions; i++) {
		functionNames.get(i, &aName);
		atom_setsym(a+1, gensym((char*)aName->getCString()));
		object_obex_dumpout(obj, gensym("functions"), 2, a);
	}
}


void map_getParameter(t_map *obj, t_symbol *msg, long argc, t_atom *argv)
{
	t_atom*		a;
	TTSymbol*	parameterName;
	TTValue		parameterValue;
	int			numValues;
	int			i;
	TTSymbol*	tempSymbol;
	double		tempValue;
	TTValue		v;
	
	if (!argc) {
		error("jcom.map: not enough arguments to parameter.get");
		return;
	}
	
	// get the correct TT name for the parameter given the Max name
	parameterName = TT(atom_getsym(argv)->s_name);
	obj->parameterNames->lookup(parameterName, v);
	v.get(0, &parameterName);
	
	obj->functionUnit->getAttributeValue(parameterName, parameterValue);
	numValues = parameterValue.getSize();
	if (numValues) {
		a = (t_atom *)sysmem_newptr(sizeof(t_atom) * (numValues+1));
		// First list item is name of parameter
		atom_setsym(a, gensym((char*)parameterName->getCString()));
		// Next the whole shebang is copied
		for (i=0; i<numValues; i++) {
			if (parameterValue.getType(i) == kTypeSymbol) {
				parameterValue.get(i, &tempSymbol);
				atom_setsym(a+i+1, gensym((char*)tempSymbol->getCString()));
			}
			else {
				parameterValue.get(i, tempValue);
				atom_setfloat(a+i+1, tempValue);
			}
		}
		object_obex_dumpout(obj, gensym("current.parameter"), numValues+1, a);
	
		// The pointer to an atom assign in the getParameter method needs to be freed.
		sysmem_freeptr(a);
	}
}

void map_getFunctionParameters(t_map *obj, t_symbol *msg, long argc, t_atom *argv)
{
	t_atom		a[2];
	long		n;
	TTValue		names;
	TTSymbol*	aName;

	atom_setsym(a+0, gensym("clear"));
	object_obex_dumpout(obj, gensym("function.parameters"), 1, a);

	obj->parameterNames->getKeys(names);
	n = names.getSize();
	if (n) {
		for (int i=0; i<n; i++) {
			atom_setsym(a+0, gensym("append"));
			names.get(i, &aName);
			atom_setsym(a+1, gensym((char*)aName->getCString()));
			object_obex_dumpout(obj, gensym("function.parameters"), 2, a);
		}
	}
	else
		object_obex_dumpout(obj, gensym("function.parameters.get"), 0, 0);		// no parameters
}




void map_setParameter(t_map *obj, t_symbol *msg, long argc, t_atom *argv)
{
	TTSymbol*	parameterName;
	TTValue		newValue;
	TTValue		v;
	int			i;
	
	if (argc < 2) {
		error("jcom.map: not enough arguments to setParameter");
		return;
	}
	
	// get the correct TT name for the parameter given the Max name
	parameterName = TT(atom_getsym(argv)->s_name);
	obj->parameterNames->lookup(parameterName, v);
	v.get(0, &parameterName);
	
	for (i=1; i<=(argc-1); i++) {
		if (argv[i].a_type == A_SYM)
			newValue.append(TT(atom_getsym(argv+1)->s_name));
		else
			newValue.append(atom_getfloat(argv+i));
	}
	obj->functionUnit->setAttributeValue(parameterName, newValue);
}


// ATTRIBUTE:
void map_doSetFunction(t_map *obj, t_symbol *newFunctionName)
{
	obj->attr_function = newFunctionName;
	FunctionLib::createUnit(TT(obj->attr_function->s_name), (TTObject **)&obj->functionUnit);

	if (obj->functionUnit) {
		long		n;
		TTValue		names;
		TTSymbol*	aName;
		TTString	nameString;
		
		obj->parameterNames->clear();
		obj->functionUnit->getAttributeNames(names);
		n = names.getSize();
		for (int i=0; i<n; i++) {
			names.get(i, &aName);
			nameString = aName->getString();
			
			if (aName == TT("Bypass") || aName == TT("Mute") || aName == TT("MaxNumChannels") || aName == TT("SampleRate"))
				continue;										// don't publish these parameters

			if (nameString[0] > 64 && nameString[0] < 91) {		// ignore all params not starting with upper-case
				nameString[0] += 32;							// convert first letter to lower-case for Max

				TTValuePtr v = new TTValue(aName);
				obj->parameterNames->append(TT(nameString.c_str()), *v);
			}
		}
	}
	obj->valid = true;
}

t_max_err map_setFunction(t_map *obj, void *attr, long argc, t_atom *argv)
{
	obj->valid = false;	// prevent values from being processed by the function while it is in a state of flux
	defer(obj, (method)map_doSetFunction, atom_getsym(argv), 0, NULL);
	return MAX_ERR_NONE;
}


// ATTRIBUTE: Set input minimum
t_max_err map_setInputMin(t_map *obj, void *attr, long argc, t_atom *argv)
{
	obj->attr_inputMin = atom_getfloat(argv);
	map_scaleInput(obj);
	return MAX_ERR_NONE;
}


// ATTRIBUTE: Set input maximum
t_max_err map_setInputMax(t_map *obj, void *attr, long argc, t_atom *argv)
{
	obj->attr_inputMax = atom_getfloat(argv);
	map_scaleInput(obj);
	return MAX_ERR_NONE;
}


// Recalculate values to use for scaling of input values
void map_scaleInput(t_map *obj)
{
	// Prevent dividing by 0
	if (obj->attr_inputMin == obj->attr_inputMax)
		{
			obj->a = 1;
			post("jcom.map: Same value used for input min and max.");
		}
	else
		obj->a = 1./(obj->attr_inputMax - obj->attr_inputMin);
	obj->b = -1 * obj->a * obj->attr_inputMin;
}


// ATTRIBUTE: Set output minimum
t_max_err map_setOutputMin(t_map *obj, void *attr, long argc, t_atom *argv)
{
	obj->attr_outputMin = atom_getfloat(argv);
	map_scaleOutput(obj);
	return MAX_ERR_NONE;

}


// ATTRIBUTE: Set output maximum
t_max_err map_setOutputMax(t_map *obj, void *attr, long argc, t_atom *argv)
{
	obj->attr_outputMax = atom_getfloat(argv);
	map_scaleOutput(obj);
	return MAX_ERR_NONE;
}


// Recalculate values to use for scaling of output values
void map_scaleOutput(t_map *obj)
{
	obj->c = obj->attr_outputMax - obj->attr_outputMin;
	obj->d = obj->attr_outputMin;
}
