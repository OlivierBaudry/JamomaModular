// Read, write, and otherwise operate on text files.
// To edit text files, launch an external editor.
// Copyright (c) 2009 by Timothy Place

#include "Jamoma.h"


// Data Structure for this object
typedef struct {
	Object		base;
	TTListPtr	lines;
} JaTextfile;


// Prototypes for methods: need a method for each incoming message type:
void *JaTextfile_new(t_symbol *msg, long argc, t_atom *argv);
void JaTextfile_assist(JaTextfile *x, void *b, long msg, long arg, char *dst);
void JaTextfile_bang(JaTextfile *x);


// Class Statics
static ClassPtr	sTextfileClass;


/************************************************************************************/
// Main() Function

int JAMOMA_EXPORT_MAXOBJ main(void)
{
	ClassPtr	c = class_new("jcom.textfile",(method)JaTextfile_new, (method)NULL, sizeof(JaTextfile), (method)0L, A_GIMME, 0);
	
	common_symbols_init();
	class_addmethod(c, (method)JaTextfile_bang,		"bang",		0L);
    class_addmethod(c, (method)JaTextfile_assist,	"assist",	A_CANT, 0L); 

	class_register(_sym_box, c);
	sTextfileClass = c;
	return 0;
}


/************************************************************************************/
// Object Creation Method

void *JaTextfile_new(t_symbol *msg, long argc, t_atom *argv)
{
	JaTextfile *x;
	 
	x = (JaTextfile*)object_alloc(sTextfileClass);
	if (x) {
		//handle attribute args	
    	attr_args_process(x, argc, argv); 
    }
 	return (x);
}


/************************************************************************************/
// Methods bound to input/inlets

// Method for Assistance Messages
void JaTextfile_assist(JaTextfile *x, void *b, long msg, long arg, char *dst)
{
	if (msg==1) { 		// Inlets
		switch (arg) {
			case 0: strcpy(dst, "(bang) remove the focus from elsewhere and give it to the patcher view"); break;
		}
	}
	else if (msg==2) { 	// Outlets
		switch (arg) {
			default: strcpy(dst, ""); break;
		}
	}
}


// METHOD: bang
void JaTextfile_bang(JaTextfile *x)
{
	ObjectPtr	patcher = NULL;
	ObjectPtr	patcherview = NULL;
	
	object_obex_lookup(x, gensym("#P"), &patcher);
	if (patcher)
		patcherview = object_attr_getobj(patcher, _sym_firstview);
//		patcherview = jpatcher_get_firstview(patcher);
	if (patcherview)
		object_method(patcherview, _sym_select);
}
