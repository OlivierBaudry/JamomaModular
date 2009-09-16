// Read, write, and otherwise operate on text files.
// To edit text files, launch an external editor.
// Copyright (c) 2009 by Timothy Place

#include "Jamoma.h"


// Data Structure for this object
typedef struct {
	Object		base;
	TTCString	filename[MAX_FILENAME_CHARS];
	short		path;
	TTListPtr	lines;
	SymbolPtr	editorName;
} Textfile;

typedef Textfile* TextfilePtr;


// Prototypes for methods: need a method for each incoming message type:
void*	TextfileNew(SymbolPtr msg, AtomCount ac, AtomPtr av);
void	TextfileFree(TextfilePtr x);
void	TextfileAssist(TextfilePtr x, void* b, long msg, long arg, char* dst);

void	TextfileRead(SymbolPtr s, AtomCount ac, AtomPtr av);
void	TextfileWrite(SymbolPtr s, AtomCount ac, AtomPtr av);
void	TextfileOpen(TextfilePtr x);
void	TextfileDump(TextfilePtr x);
void	TextfileLine(TextfilePtr x, long i);
void	TextfileNext(TextfilePtr x);
void	TextfileClear(TextfilePtr x);


// Class Statics
static ClassPtr	sTextfileClass;


/************************************************************************************/
// Main() Function

int JAMOMA_EXPORT_MAXOBJ main(void)
{
	ClassPtr	c = class_new("jcom.textfile",(method)TextfileNew, (method)TextfileFree, sizeof(Textfile), (method)0L, A_GIMME, 0);
	
	common_symbols_init();
	class_addmethod(c, (method)TextfileRead,		"read",		A_DEFER,	0);
	class_addmethod(c, (method)TextfileWrite,		"write",	A_DEFER,	0);
	class_addmethod(c, (method)TextfileOpen,		"open",		0);
	class_addmethod(c, (method)TextfileOpen,		"dblclick",	A_CANT,		0);
	class_addmethod(c, (method)TextfileDump,		"dump",		0);
	class_addmethod(c, (method)TextfileLine,		"int",		A_LONG,		0);
	class_addmethod(c, (method)TextfileLine,		"line",		A_LONG,		0);
	class_addmethod(c, (method)TextfileNext,		"next",		0);
	class_addmethod(c, (method)TextfileNext,		"bang",		0);
	class_addmethod(c, (method)TextfileClear,		"clear",	0);
    class_addmethod(c, (method)TextfileAssist,		"assist",	A_CANT,		0); 

	CLASS_ATTR_SYM(c,	"editor",	0,	Textfile, editorName);
	
	class_register(_sym_box, c);
	sTextfileClass = c;
	return 0;
}


/************************************************************************************/
// Object Creation Method

void* TextfileNew(SymbolPtr msg, AtomCount ac, AtomPtr av)
{
	TextfilePtr	x;
	 
	x = (TextfilePtr)object_alloc(sTextfileClass);
	if (x) {
		x->lines = new TTList;
		
#ifdef MAC_VERSION
		x->editorName = gensym("TextMate");
#else
		x->editorName = gensym("C:\\Windows\\notepad.exe");
#endif
		
		//handle attribute args	
    	attr_args_process(x, ac, av); 
    }
 	return (x);
}


void TextfileFree(TextfilePtr x)
{
	delete x->lines;
}


/************************************************************************************/
// Methods bound to input/inlets


void TextfileAssist(TextfilePtr x, void* b, long msg, long arg, char* dst)
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


void	TextfileRead(SymbolPtr s, AtomCount ac, AtomPtr av)
{
	;
}


void	TextfileWrite(SymbolPtr s, AtomCount ac, AtomPtr av)
{
	;
}


void	TextfileOpen(TextfilePtr x)
{
	t_object *workspace = (t_object*)object_new(CLASS_NOBOX, gensym("workspace"));
	
	if(x->path)
		object_method(workspace, gensym("openfilewithapp"), x->path, x->filename, editorname->s_name);
	object_free(workspace);
}


void	TextfileDump(TextfilePtr x)
{
	;
}


void	TextfileLine(TextfilePtr x, long i)
{
	;
}


void TextfileNext(TextfilePtr x)
{
	;
}


void TextfileClear(TextfilePtr x)
{
	;
}

