// External Object for Jamoma: OSC router
// By Timothy Place, Copyright � 2006
// License: GNU LGPL

#include "ext.h"					// Max Header
#include "ext_strings.h"			// String Functions
#include "commonsyms.h"				// Common symbols used by the Max 4.5 API
#include "ext_obex.h"				// Max Object Extensions (attributes) Header

#define MAX_ARGCOUNT 100
#define MAX_MESS_SIZE 2048

typedef struct _oscroute{					// Data Structure for this object
	t_object	ob;							// REQUIRED: Our object
	void		*obex;						// REQUIRED: Object Extensions used by Jitter/Attribute stuff 
	void 		*outlets[MAX_ARGCOUNT];		// my outlet array
	void		*outlet_overflow;			// this outlet doubles as the dumpout outlet
	t_symbol	*arguments[MAX_ARGCOUNT];	// symbols to match
	short		num_args;
	long		attr_strip;					// ATTRIBUTE: 1 = strip leading slash off any messages
} t_oscroute;

// Prototypes for our methods:
void *oscroute_new(t_symbol *s, long argc, t_atom *argv);
void oscroute_assist(t_oscroute *x, void *b, long msg, long arg, char *dst);
void oscroute_bang(t_oscroute *x);
void oscroute_int(t_oscroute *x, long n);
void oscroute_float(t_oscroute *x, double f);
void oscroute_list(t_oscroute *x, t_symbol *msg, short argc, t_atom *argv);
void oscroute_symbol(t_oscroute *x, t_symbol *msg, short argc, t_atom *argv);
//void oscroute_list(t_oscroute *x, t_symbol *msg, short argc, t_atom *argv);

// Globals
t_class		*oscroute_class;				// Required: Global pointer for our class


/************************************************************************************/
// Main() Function

int main(void)				// main recieves a copy of the Max function macros table
{
	long attrflags = 0;
	t_class *c;
	t_object *attr;
	
	// Initialize Globals
	common_symbols_init();

	// Define our class
	c = class_new("jmod.oscroute",(method)oscroute_new, (method)0L, (short)sizeof(t_oscroute), (method)0L, A_GIMME, 0);
	class_obexoffset_set(c, calcoffset(t_oscroute, obex));

	// Make methods accessible for our class: 
	class_addmethod(c, (method)oscroute_bang,			"bang",		0L,			0L);	
	class_addmethod(c, (method)oscroute_int,			"int",		A_DEFLONG,	0L);
	class_addmethod(c, (method)oscroute_float,			"float",	A_DEFFLOAT,	0L);
	class_addmethod(c, (method)oscroute_list,			"list",		A_GIMME,	0L);
  	class_addmethod(c, (method)oscroute_symbol,			"anything", A_GIMME,	0L);	
	class_addmethod(c, (method)oscroute_assist,			"assist",	A_CANT,		0L); 
    class_addmethod(c, (method)object_obex_dumpout, 	"dumpout",	A_CANT,		0);  
    class_addmethod(c, (method)object_obex_quickref,	"quickref", A_CANT,		0);

	// ATTRIBUTE: strip
	attr = attr_offset_new("strip", _sym_long, attrflags,
		(method)0, (method)0, calcoffset(t_oscroute, attr_strip));
	class_addattr(c, attr);	

	// Finalize our class
	class_register(CLASS_BOX, c);
	oscroute_class = c;
	return 0;
}


/************************************************************************************/
// Object Life

void *oscroute_new(t_symbol *s, long argc, t_atom *argv)
{
	short i;
	t_oscroute	*x = (t_oscroute *)object_alloc(oscroute_class);
	
	if(x){
		x->outlet_overflow = outlet_new(x, 0);		// overflow outlet
		//object_obex_store((void *)x, _sym_dumpout, (object *)x->outlet_overflow);	// dumpout
		x->num_args = argc;		

		for(i=x->num_args-1; i >= 0; i--){				
			x->outlets[i] = outlet_new(x, 0);		// Create Outlet
			switch(argv[i].a_type){
				case A_SYM:
					//atom_setsym(&(x->arguments[i]), atom_getsym(argv+i));
					x->arguments[i] = atom_getsym(argv+i);
					break;
				default:
					error("jmod.oscroute - invalid arguments - all args must be symbols");
			}
		}
		//attr_args_process(x, argc, argv);			//handle attribute args	
	}
	return (x);										// return the pointer to our new instantiation
}


/************************************************************************************/
// Methods bound to input/inlets

// Method for Assistance Messages
void oscroute_assist(t_oscroute *x, void *b, long msg, long arg, char *dst)
{
	if(msg==1) 						// Inlet
		strcpy(dst, "Input");
	else if(msg==2){ 				// Outlets
		if(arg < x->num_args)
			strcpy(dst, x->arguments[arg]->s_name);
		else
			strcpy(dst, "dumpout / overflow from non-matching input");	
 	}		
}


// BANG INPUT: STRAIGHT TO OVERFLOW
void oscroute_bang(t_oscroute *x)
{
	outlet_bang(x->outlet_overflow);
}

// INT INPUT: STRAIGHT TO OVERFLOW
void oscroute_int(t_oscroute *x, long n)
{
	outlet_int(x->outlet_overflow, n);
}

// FLOAT INPUT: STRAIGHT TO OVERFLOW
void oscroute_float(t_oscroute *x, double f)
{
	outlet_float(x->outlet_overflow, f);
}

// LIST INPUT: STRAIGHT TO OVERFLOW
void oscroute_list(t_oscroute *x, t_symbol *msg, short argc, t_atom *argv)
{
	outlet_list(x->outlet_overflow, _sym_list, argc , argv);
}

// SYMBOL INPUT
void oscroute_symbol(t_oscroute *x, t_symbol *msg, short argc, t_atom *argv)
{
	short		i;
	t_symbol	*message;				// our input message to match
	t_symbol	*output;
	char		input[MAX_MESS_SIZE];	// our input string
	char		*temp;
	
	strcpy(input, msg->s_name);

	// Make sure we are dealing with valid OSC input by looking for a leading slash
	
	if(input[0] != '/') {
		outlet_anything(x->outlet_overflow, msg, argc , argv);
		return;
	}

	temp = strchr(input+1, '/');
	
	// if there is no second slash
	
	if(temp == NULL){
		message = gensym(input);
		// no arguments: return bang
		if (argc==0) {
			for(i=0; i< x->num_args; i++) {
				if(message == x->arguments[i]) {
					outlet_bang(x->outlets[i]);
					return;
				}
			}
		}
		// one argument, return int, float or anything
		else if (argc==1) {
			// int argument
			if (argv->a_type==A_LONG) {
				for(i=0; i< x->num_args; i++) {
					if(message == x->arguments[i]) {
						outlet_int(x->outlets[i],argv->a_w.w_long);
						return;
					}				
				}
			}
			// float argument
			else if (argv->a_type==A_FLOAT) {
				for(i=0; i< x->num_args; i++) {
					if(message == x->arguments[i]) {
						outlet_float(x->outlets[i],argv->a_w.w_float);
						return;
					}				
				}
			}
			// something else
			else if (argv->a_type==A_SYM) {
				for(i=0; i< x->num_args; i++) {
					if(message == x->arguments[i]) {
						outlet_anything(x->outlets[i],argv->a_w.w_sym,0,0);
						return;
					}				
				}
			}
		}		
		// There are two or more arguments, check if first is A_SYM
		for (i=0; i< x->num_args; i++) {
			if (message == x->arguments[i]) {		
				if (argv->a_type==A_SYM) {
					output = argv->a_w.w_sym;
					argc--;
					argv++;
				}
				else
					output = _sym_list;
				outlet_anything(x->outlets[i], output, argc , argv);
				return;
			}

		}
	}
	// there is a second slash
	else {
		*temp = '\0';		// terminate the input string	
		message = gensym(input);
		*temp = '/';		// add the slash back in
		output = gensym(temp);

		for (i=0; i< x->num_args; i++) {
			if (message == x->arguments[i]) {
				outlet_anything(x->outlets[i], output, argc , argv);
				return;
			}
		}
	}
	// the message was never reckognised
	outlet_anything(x->outlet_overflow, msg, argc , argv);
}