/* 
 * jcom.init
 * External for Jamoma: send bang to initialize something
 *	bang source may be global or for just one module
 * By Tim Place, Copyright � 2006
 * 
 * License: This code is licensed under the terms of the GNU LGPL
 * http://www.gnu.org/licenses/lgpl.html 
 */

#include "Jamoma.h"

// Data Structure for this object
typedef struct _init{
	t_jcom_core_subscriber_common	common;
	void							*outlet;
	void							*dumpout;
} t_init;

// Prototypes for methods
void *init_new(t_symbol *s, long argc, t_atom *argv);			// New Object Creation Method
void init_assist(t_init *x, void *b, long m, long a, char *s);	// Assistance Method
void init_go(t_init *x);
void init_bang(t_init *x);

// Globals
t_class			*g_init_class;			// Required. Global pointing to this class


/************************************************************************************/
// Main() Function

int JAMOMA_EXPORT_MAXOBJ main(void)
{
	t_class		*c;
	t_object 	*attr = NULL;
	
	jamoma_init();
	common_symbols_init();

	// Define our class
	c = class_new("jcom.init",(method)init_new, (method)jcom_core_subscriber_common_free, sizeof(t_init), (method)0L, A_GIMME, 0);

	// Make methods accessible for our class: 
	class_addmethod(c, (method)init_bang,				"bang",			0L);
	class_addmethod(c, (method)init_go,					"go",			A_CANT, 0);
    class_addmethod(c, (method)init_assist,				"assist",		A_CANT, 0L);
	
	jcom_core_subscriber_classinit_common(c, attr);	
	
	// Finalize our class
	class_register(CLASS_BOX, c);
	g_init_class = c;

	return 0;
}


/************************************************************************************/
// Object Life

// Create
void *init_new(t_symbol *s, long argc, t_atom *argv)
{
	long 		attrstart = attr_args_offset(argc, argv);		// support normal arguments
	t_init 		*x = (t_init *)object_alloc(g_init_class);
	t_symbol	*name = _sym_nothing;

	if (attrstart && argv)
		atom_arg_getsym(&name, 0, attrstart, argv);
	else
		name = symbol_unique();
	
	if (x) {
		x->dumpout = outlet_new(x, NULL);
		x->outlet = outlet_new(x, NULL);
		object_obex_store((void *)x, jps_dumpout, (object *)x->dumpout);		// setup the dumpout

		jcom_core_subscriber_new_common(&x->common, name, jps_subscribe_init);
		attr_args_process(x, argc, argv);					// handle attribute args				

		jcom_core_subscriber_subscribe((t_jcom_core_subscriber_common*)x);
	}
	return (x);												// Return the pointer
}


/************************************************************************************/
// Methods bound to input/inlets

// Method for Assistance Messages
void init_assist(t_init *x, void *b, long msg, long arg, char *dst)
{
	if (msg==1) 	// Inlets
		strcpy(dst, "bang is passed through to the outlet");
	else if (msg==2) { // Outlets
		if (arg == 0) 
			strcpy(dst, "bang on initialization");
		else 
			strcpy(dst, "dumpout");
	}
}

// GO!
void init_go(t_init *x)
{
	outlet_bang(x->outlet);
}

// BANG!
void init_bang(t_init *x)
{
	if (x->common.hub != NULL)
		object_method_typed(x->common.hub, jps_init, 0, NULL, NULL);
}
