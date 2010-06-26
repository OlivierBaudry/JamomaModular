/* 
 * jcom.hub
 * External for Jamoma: the main control center
 * By Tim Place, Copyright � 2006
 * 
 * License: This code is licensed under the terms of the GNU LGPL
 * http://www.gnu.org/licenses/lgpl.html 
 */

// TODO: get module name (by default) from the patcher name so it doesn't have to be specified manually
// TODO: idea from Adrian Freed is to use jit.cellblock for a documentation interface
// TODO: AF suggested adding beta functions to the functionlib (lots of unpublished work and use previously by David Wessel)

#include "jcom.hub.h"
#include <functional>
#include "jpatcher_api.h"


#define value value_list[0]

// Globals
static t_class		*s_hub_class;						// Required: Global pointer for our class
t_object			*g_jcom_send_notifications = NULL;	// Shared instance for communicating about module instantiation and deletion

/** A function object for determining if one t_subscriber object should follow another t_subscriber.
 * This is determined by the alphabetical ordering of the names of the two t_subscribers.
 */
struct _subIsLess : binary_function<t_subscriber*, t_subscriber*, bool> {
	bool operator()(const t_subscriber* p, const t_subscriber* q)
		{	return jcom_core_string_compare(p->name->s_name, q->name->s_name); }
} subscriberIsLess;


/************************************************************************************/
// Main() Function

int JAMOMA_EXPORT_MAXOBJ main(void)
{
	t_class *c;
	
	// Initialize Globals
	jamoma_init();
	common_symbols_init();

	// Define our class
	c = class_new("jcom.hub",(method)hub_new, (method)hub_free, sizeof(t_hub), (method)0L, A_GIMME, 0);
	
	// Make methods accessible for our class:
 	class_addmethod(c, (method)hub_symbol,				"anything",					A_GIMME, 0L);

	class_addmethod(c, (method)hub_getobj_audioin,		"getobj_audioin",			A_CANT, 0);		// return a pointer to the jcom.in~ object
	class_addmethod(c, (method)hub_getobj_audioout,		"getobj_audioout",			A_CANT, 0);		// return a pointer to the jcom.out~ object

	class_addmethod(c, (method)hub_bang,				"bang",						0);				// bang is used by one of the ramp driving mechanisms to calculate values

	class_addmethod(c, (method)hub_subscribe,			"subscribe",				A_CANT, 0L);	// client object subscribing
	class_addmethod(c, (method)hub_unsubscribe,			"unsubscribe",				A_CANT, 0L);	// client object unsubscribing
	class_addmethod(c, (method)hub_subscriptions_refresh,	"refreshSubscriptions",	0);
	class_addmethod(c, (method)hub_receive,				"__feedback__",				A_GIMME, 0L);	// feedback from parameters and such
	class_addmethod(c, (method)hub_private,				"private", 					A_GIMME, 0L);	// internal communications such as jcom.remote
	class_addmethod(c, (method)hub_return,				"return",					A_GIMME, 0L);	// feedback from jcom.return
	class_addmethod(c, (method)hub_return_extended,		"return_extended",			A_GIMME, 0L);	// feedback from jcom.return
//	class_addmethod(c, (method)hub_autodoc,				"documentation/generate",	0);
//	class_addmethod(c, (method)hub_autodoc,				"/documentation/generate",	0);
//	class_addmethod(c, (method)hub_presets_post,		"preset/post",	0); 
//	class_addmethod(c, (method)hub_presets_post,		"/preset/post",	0); 
	class_addmethod(c, (method)hub_paramnames_get,		"parameter_names:/dump",		0L);
	class_addmethod(c, (method)hub_paramnames_get,		"/parameter_names:/dump", 	0L);
	class_addmethod(c, (method)hub_messagenames_get,	"message_names:/dump",		0L);
	class_addmethod(c, (method)hub_messagenames_get,	"/message_names:/dump",		0L);
	class_addmethod(c, (method)hub_returnnames_get,		"return_names:/dump",		0L);
	class_addmethod(c, (method)hub_returnnames_get,		"/return_names:/dump",		0L);
	class_addmethod(c, (method)hub_allnames_get,		"*_names:/dump",				0L);
	class_addmethod(c, (method)hub_allnames_get,		"/*_names:/dump",			0L);
	class_addmethod(c, (method)hub_paramvalues_get,		"parameter_values:/dump",	0L);
	class_addmethod(c, (method)hub_paramvalues_get,		"/parameter_values:/dump",	0L);
	class_addmethod(c, (method)hub_modulename_get,		"module_name:/get", 0L);
	class_addmethod(c, (method)hub_modulename_get,		"/module_name:/get",			0L);
	class_addmethod(c, (method)core_modulename_get,		"core_module_name:/get",			0L);
	class_addmethod(c, (method)hub_algorithmtype_get,	"algorithm_type:/get", A_CANT);
	class_addmethod(c, (method)hub_algorithmtype_get,	"/algorithm_type:/get",		A_CANT);
	
	class_addmethod(c, (method)hub_paramnames_linklist,		"fetchParameterNamesInLinklist",	A_CANT, 0); // used by the ui ref menu
	class_addmethod(c, (method)hub_messagenames_linklist,	"fetchMessageNamesInLinklist",		A_CANT, 0); // used by the ui ref menu
	class_addmethod(c, (method)hub_returnnames_linklist,	"fetchReturnNamesInLinklist",		A_CANT, 0); // used by the ui ref menu
	class_addmethod(c, (method)hub_presetnames_linklist,	"fetchPresetNamesInLinklist",		A_CANT, 0); // used by the ui menu

	class_addmethod(c, (method)hub_module_help,				"module/help",			A_CANT, 0); // used by the ui ref menu
	class_addmethod(c, (method)hub_module_help,				"/module/help",			A_CANT, 0); // used by the ui ref menu
	class_addmethod(c, (method)hub_module_reference,		"module/reference",		A_CANT, 0); // used by the ui ref menu	
	class_addmethod(c, (method)hub_module_reference,		"/module/reference",		A_CANT, 0); // used by the ui ref menu	
	
	//class_addmethod(c, (method)hub_examine_context,		"loadbang", A_CANT, 0);
	class_addmethod(c, (method)hub_notify,				"notify",					A_CANT, 0);
	class_addmethod(c, (method)hub_assist,				"assist",					A_CANT, 0L); 
    class_addmethod(c, (method)object_obex_dumpout,		"dumpout",					A_CANT,	0);

	class_addmethod(c, (method)hub_edclose,				"edclose",	A_CANT, 0);		// notification of closing the /getstate text editor window

	CLASS_ATTR_SYM(c,		"name",				0,	t_hub,	osc_name);				// instance name (osc)
	CLASS_ATTR_ACCESSORS(c,	"name",				NULL,	hub_attr_setname);

	CLASS_ATTR_SYM(c,		"class",			0,	t_hub,	attr_name);				// module class name
	CLASS_ATTR_SYM(c,		"module_type",		0,	t_hub,	attr_type);
	CLASS_ATTR_SYM(c,		"algorithm_type",	0,	t_hub,	attr_algorithm_type);
	CLASS_ATTR_SYM(c,		"description",		0,	t_hub,	attr_description);
	
	CLASS_ATTR_SYM(c,		"user_path",		0,	t_hub,	user_path);	// the path of the last file used to save the presets

	// Finalize our class
	class_register(_sym_box, c);
	s_hub_class = c;
	
	return 0;
}


/************************************************************************************/
// Object Life

void *hub_new(t_symbol *s, long argc, t_atom *argv)
{
	short			i;
	long			attrstart = attr_args_offset(argc, argv);
	t_hub			*x = (t_hub *)object_alloc(s_hub_class);
	t_symbol		*name = _sym_nothing;
	t_atom			a[2];
	
	if (attrstart && argv)
		atom_arg_getsym(&name, 0, attrstart, argv);
	else {
		t_object*	patcher = jamoma_object_getpatcher((t_object*)x);
		t_symbol*	filepath = object_attr_getsym(patcher, _sym_filepath);
		char		pathstr[MAX_PATH_CHARS];
		char*		filename = 0;
		
		strncpy_zero(pathstr, filepath->s_name, MAX_PATH_CHARS);
		filename = strrchr(pathstr, '.');
		if (filename) {
			*filename = 0;	// strip the suffix by setting '.' to terminating NULL char
			filename = strrchr(pathstr, '/');
			if (filename) {
				// Our module name is the patchers name since the patcher is typically located
				// at /some/where/nameToUseForModule.maxpat
				filename++; // get rid of slash
				name = gensym(filename);
			}
			else
				name = gensym(pathstr);
		} else {
			// We are an unnamed jcom.hub inserted into an unsaved max patcher which has
			// no '.' in it's filename.  Just leave as untitled, at least until it is saved.
			name = gensym("Untitled");
		}
	}
		
	if (x) {
		for (i=k_num_outlets; i > 0; i--)
			x->outlets[i-1] = outlet_new(x, 0);
		object_obex_store((void *)x, _sym_dumpout, (t_object *)x->outlets[k_outlet_dumpout]);
		x->init_qelem = qelem_new(x, (method)hub_qfn_init);

		// set default attributes
		x->attr_name = name;
		x->osc_name = _sym_nothing;
		x->attr_type = jps_control;
		x->attr_description = _sym_nothing;
		x->attr_algorithm_type = jps_default;		// poly for audio, jitter for video, control for control
		x->attr_size = jps_1U_half;
		x->attr_inspector = 0;
		x->using_wildcard = false;
		x->in_object = NULL;						// module MUST have a jcom.in object
		x->out_object = NULL;						// the jcom.out object is optional
		x->gui_object = NULL;						// jcom.remote in the gui
		x->num_parameters = 0;
		for (i=0; i<MAX_NUM_CHANNELS; i++)
			x->meter_object[i] = NULL;
		
		x->preset = new presetList;					// begin with no presets
		x->subscriber = new subscriberList;			// ... and no subscribers
		
		attr_args_process(x, argc, argv);			// handle attribute args
		
		x->jcom_send = NULL;
		x->jcom_receive = NULL;
		atom_setsym(a, jps_jcom_remote_fromModule);
		x->jcom_send = (t_object*)object_new_typed(_sym_box, jps_jcom_send, 1, a);
		
		atom_setsym(a, jps_jcom_remote_toModule);
		
		// 2010-03-01: Marlon has had some crashes, with overdrive on, which look like they may be caused by 
		// this jcom.receive object having been created prior to the jcom.hub being fully set-up via the
		// deferred hub_examine_context() call at the end of this method.  
		// This results in this hub receiving messages before it is really ready for them... [TAP]
		x->jcom_receive = (t_object*)object_new_typed(_sym_box, jps_jcom_receive, 1, a);
		object_method(x->jcom_receive, jps_setcallback, &hub_receive_callback, x);
					
		if (!g_jcom_send_notifications) {
			atom_setsym(a, gensym("notifications"));
			g_jcom_send_notifications = (t_object*)object_new_typed(_sym_box, jps_jcom_send, 1, a);
		}
		
		x->container = jamoma_object_getpatcher((t_object*)x);
		
		// The following must be deferred because we have to interrogate our box,
		// and our box is not yet valid until we have finished instantiating the object.
		// Trying to use a loadbang method instead is also not fully successful (as of Max 5.0.6)
		defer_low(x, (method)hub_examine_context, 0, 0, 0);
	}
	return x;
}


long hub_iterate_callback(t_hub *x, t_object *obj)
{
	method		subscribeMethod = NULL;
	//ObjectPtr	p = jbox_get_patcher(obj);
	//SymbolPtr	s = jpatcher_get_name(p);
	//SymbolPtr	name = object_classname(obj);
	
	//object_post(ObjectPtr(x), "iterate: %s (in %s)", name->s_name, s);
	
	if (!object_classname_compare(obj, jps_jcom_hub)) {
		subscribeMethod = zgetfn(obj, jps_subscribe);
		if (subscribeMethod)
			(*subscribeMethod)(obj);
	}
	return 0;
}

void hub_subscriptions_refresh(t_hub *x)
{
	long result = 0;

	object_method(x->container, _sym_iterate, (method)hub_iterate_callback, x, PI_DEEP, &result);
}


// TODO: When running in the debugger, it seems like we are iterating through this function a whole bunch of times!
// Can we put it in a qelem or something so that it only gets called once? [TAP]
// But actually, maybe it is just a Max 4.6 funky Runtime thing?  Let's take a look again when we get to Max 5
void hub_examine_context(t_hub *x)
{
	AtomCount	argc = 0;
	AtomPtr		argv = NULL;
	SymbolPtr	context = jamoma_patcher_getcontext(x->container);

	// Try to get OSC Name of module from an argument
	jamoma_patcher_getargs(x->container, &argc, &argv);	// <-- this call allocates memory for argv
	if (argc) {
		x->osc_name = atom_getsym(argv+(argc-1));
		sysmem_freeptr(argv);
	}
	else
		x->osc_name = _sym_nothing;
	
	// Try to get OSC Name of module from scripting name
	if (x->osc_name == _sym_nothing)
		x->osc_name = jamoma_patcher_getvarname(x->container);

	// In this case we overwrite whatever happened above
	if (context == gensym("toplevel")) {
		x->osc_name = gensym("/editing_this_module");
		x->editing = true;
	}
	else {
		t_object*	patcher = jamoma_object_getpatcher((t_object*)x);
		t_object*	box = object_attr_getobj(patcher, jps_box);
		t_object*	ui = NULL;
		t_symbol*	objclass = NULL;
		
		x->editing = false;		
		ui = object_attr_getobj(patcher, gensym("firstobject"));
		while (ui) {
			objclass = object_attr_getsym(ui, gensym("maxclass"));
			if (objclass == gensym("jcom.ui"))
				break;
			ui = object_attr_getobj(ui, gensym("nextobject"));
		}
		
		if (ui) {
			t_rect	boxRect;
			t_rect	uiRect;
			
			if (context == gensym("bpatcher")) {
				object_attr_get_rect(ui, _sym_presentation_rect, &uiRect);
				object_attr_get_rect(box, _sym_patching_rect, &boxRect);
				boxRect.width = uiRect.width;
				boxRect.height = uiRect.height;
				object_attr_set_rect(box, _sym_patching_rect, &boxRect);
				object_attr_get_rect(box, _sym_presentation_rect, &boxRect);
				boxRect.width = uiRect.width;
				boxRect.height = uiRect.height;
				object_attr_set_rect(box, _sym_presentation_rect, &boxRect);
			}
			else if (context == gensym("subpatcher")) {
				object_attr_get_rect(ui, _sym_presentation_rect, &uiRect);
				object_attr_get_rect(patcher, _sym_defrect, &boxRect);
				boxRect.width = uiRect.width;
				boxRect.height = uiRect.height;				
				object_attr_set_rect(patcher, _sym_defrect, &boxRect);				
				object_attr_setchar(patcher, _sym_toolbarvisible, 0);	
				object_method_parse(patcher, _sym_window, "flags nogrow", NULL); //get rid of the grow thingies
				object_method_parse(patcher, _sym_window, "exec", NULL); 
				object_attr_setsym(patcher, _sym_title, x->attr_name); //set the window title to the module class, jcom.ui shows osc_name already 
				object_attr_setchar(patcher, _sym_enablehscroll, 0);   // turn off scroll bars
				object_attr_setchar(patcher, _sym_enablevscroll, 0);				
			}
		
		}
	}

	object_attr_setsym(x, _sym_name, x->osc_name);
	
	hub_subscriptions_refresh(x);
	hub_internals_create(x);

	qelem_unset(x->init_qelem);		// clear the last thing to make sure we don't call into this a bunch of times
	qelem_set(x->init_qelem);		// flag the queue for initialization
}


void hub_free(t_hub *x)
{
	subscriberIterator i;
	subscriberList *subscriber = x->subscriber;
	t_atom a[2];

	object_free(x->preset_interface);
	jamoma_hub_remove(x->osc_name);

	atom_setsym(a, x->attr_name);
	atom_setsym(a+1, x->osc_name);
	object_method_typed(g_jcom_send_notifications, gensym("module.removed"), 2, a, NULL);

	critical_enter(0);
	for (i = subscriber->begin(); i != subscriber->end(); ++i) {
		// notify the subscriber that the hub is going away
		if (!NOGOOD((*i)->object))
			object_method((*i)->object, jps_release);
		sysmem_freeptr(*i);
	}
	critical_exit(0);	

	object_free(x->textEditor);
	if (x->textSize)
		free(x->text);
		
	hub_internals_destroy(x);
 	hub_presets_clear(x, NULL, 0, NULL);
	qelem_free(x->init_qelem);
	if (x->jcom_send)
		object_free(x->jcom_send);
	if (x->jcom_receive)
		object_free(x->jcom_receive);
	x->subscriber->clear();
	delete x->subscriber;
	delete x->preset;
}


void hub_notify(t_hub *x, t_symbol *s, t_symbol *msg, void *sender, void *data)
{
	if (sender == x->preset_interface) {
		if (msg == _sym_attr_modified) {
			t_symbol* name;

			name = (t_symbol *)object_method((t_object *)data, _sym_getname);
		}
		else if (msg == _sym_free) {
			object_detach_byptr(x, x->preset_interface);
			x->preset_interface = NULL;
		}
	}
}

/************************************************************************************/
// Communication with jcom.param objects

// This method is called from clients such as jcom.parameter to register it with this hub
t_symbol* hub_subscribe(t_hub *x, t_symbol *name, t_object *subscriber_object, t_symbol *type)
{
	t_subscriber	*new_subscriber;
	
	if (subscriber_object == NULL) {
		if (x->editing)
			object_error((t_object*)x, "Null object cannot subscribe to jcom.hub (in % module)", x->attr_name->s_name);
		else	
			object_error((t_object*)x, "Null object cannot subscribe to jcom.hub (in % module)", x->osc_name->s_name);
		return _sym_nothing;
	}
	
	// if this object has been previously subscribed, we remove it before adding it again
	// perhaps we could just ignore the second subscription instead?  what about parameter renaming situations?
	hub_unsubscribe(x, subscriber_object);
	
	// Create the new item
	new_subscriber = (t_subscriber *)sysmem_newptr(sizeof(t_subscriber));
	new_subscriber->object = subscriber_object;
	new_subscriber->name = name;
	new_subscriber->type = type;

	critical_enter(0);
	// Merge new subscriber into subscriber list sorted alphabetically
	x->subscriber->merge(new_subscriber, subscriberIsLess);

	// special cases and other caching
	if (new_subscriber->type == jps_subscribe_in) {
		x->in_object = (t_object*)subscriber_object;
		if (x->out_object) {		// set up pointers between jcom.in and jcom.out
			object_method(x->in_object, jps_link_out, x->out_object);
			object_method(x->out_object, jps_link_in, x->in_object);
		}
	}
	if (new_subscriber->type == jps_subscribe_out) {
		x->out_object = (t_object*)subscriber_object;
		if (x->in_object) {		// set up pointers between jcom.in and jcom.out
			object_method(x->in_object, jps_link_out, x->out_object);
			object_method(x->out_object, jps_link_in, x->in_object);
		}
		for (int i=0; i<MAX_NUM_CHANNELS; i++) {
			if (x->meter_object[i])
				object_method(x->out_object, jps_register_meter, i, x->meter_object[i]);
		}
		object_method(x->out_object, jps_register_preview, x->gui_object);
	}

	if (new_subscriber->type == jps_subscribe_remote) {
		int meternum = 0;
		sscanf( new_subscriber->name->s_name, "%i__meter__", &meternum);
		if (meternum > 0) {
			x->meter_object[meternum-1] = (t_object*)new_subscriber->object;
			if (x->out_object)
				object_method(x->out_object, jps_register_meter, meternum-1, x->meter_object[meternum-1]);
		}
	}
	
	if (new_subscriber->type == jps_subscribe_parameter)
		x->num_parameters++;
	if (new_subscriber->name == jps__gui__) {
		x->gui_object = subscriber_object;
		if (x->out_object)
			object_method(x->out_object, jps_register_preview, x->gui_object);				
	}
	critical_exit(0);
	
	return x->attr_name;			// return the module name to the parameter
}


void hub_unsubscribe(t_hub *x, t_object *subscriber_object)
{
	subscriberList	*subscribers = x->subscriber;
	
	// Search the linked list for this object and remove it
	t_subscriber* t;
	critical_enter(0);
	for (subscriberIterator item = subscribers->begin(); item != subscribers->end(); ++item) {
		t = *item;
		
		if (t->object == subscriber_object) {
			if (t->type == jps_subscribe_parameter)
				x->num_parameters--;
			/*	Temporarily disabling this for Jamoma 0.5
				We need to evaluate whether or not this is needed any more given the new way we are doing the UI.
				[TAP]

			else if (t->type == jps_subscribe_in) {
				if (x->out_object)
					object_method(x->out_object, jps_unlink_out);
			}
			else if (t->type == jps_subscribe_out) {
				if (x->in_object)
					object_method(x->in_object, jps_unlink_in);
			}
				
			else if (t->type == jps_subscribe_remote) {
				char temp[32];
				for (short i=0; i<MAX_NUM_CHANNELS; i++) {
					snprintf(temp, 32, "__meter__%i", i);
					if (t->name == gensym(temp)) {
						if (x->out_object)
							object_method(x->out_object, gensym("remove_meters"));
					}
				}
			}
			*/
			item = subscribers->erase(item);
			sysmem_freeptr(t);
			
			/** XXX why does this need to be here?  It seems Microsoft's compiler is generating code 
			 * that will preincrement (++) the item iterator in the for loop despite the fact that 
			 * the for loops if condition has been met and following conditional statement shouldn't
			 * execute.  Either that or something awkward about the the behavior of their STL 
			 * implementation */
			// XXX -- TIM is commenting it out temporarily.  It may not effect us anymore with all of the recent changes?
			// If we have processed the unsub then we really want to just break right away...
			//if (item == subscribers->end())
				break;

		}
	}
	// TODO: We really need to use our own mutex instead of the global critical region [TAP]
	critical_exit(0);
}


// Receive parameter values from jcom.parameter
void hub_receive(t_hub *x, t_symbol *name, long argc, t_atom *argv)
{
	char		namestring[256];
	t_symbol	*osc;
	
	strcpy(namestring, "/");						// perhaps we could optimize this operation
	strcat(namestring, argv->a_w.w_sym->s_name);	//	by creating a table when the param is bound
	osc = gensym(namestring);						//	then we could look-up the symbol instead of using gensym()

	if (x->in_object != NULL)
		object_method_typed(x->in_object, jps_algorithm_message, argc, argv, NULL);	// send to jcom.in
	if (x->out_object != NULL)
		object_method_typed(x->out_object, jps_algorithm_message, argc, argv, NULL);	// send to jcom.out

	//hub_internals_dispatch(x, argv->a_w.w_sym, argc-1, argv+1);
	hub_outlet_return(x, osc, argc-1, argv+1);
}


// Receive private messages from jcom.remote
void hub_private(t_hub *x, t_symbol *name, long argc, t_atom *argv)
{
	t_symbol		*private_id = _sym_nothing;	
	t_symbol		*private_message = _sym_nothing;
	t_symbol		*userpath = _sym_nothing;
	t_atom			a;
	
	private_id = atom_getsym(argv);
	argc--;
	argv++;
	private_message = atom_getsym(argv);
	argc--;
	argv++;
	if (private_id == jps__gui__) {
		if (private_message == jps_slash_preset_slash_default)			// 	/preset/default
			hub_preset_default(x, NULL, 0, NULL);
		else if (private_message == jps_slash_preset_slash_load) {		// 	/preset/load
			atom_setsym(&a, userpath);
			hub_preset_read(x, NULL, 1, &a);
		}
		else if (private_message == jps_slash_preset_slash_recall)		// 	/preset/load
			hub_preset_recall(x, _sym_list, 1, argv);
		else if (private_message == jps_slash_preset_slash_store)
			hub_preset_store(x, _sym_list, argc, argv);
		else if (private_message == jps_slash_preset_slash_storenext) 
			hub_preset_store_next(x, _sym_list, argc, argv);
		else if (private_message == jps_slash_preset_slash_copy)			// 	/preset/load
			hub_preset_copy(x, _sym_list, argc, argv);
		else if (private_message == jps_slash_preset_slash_write) {		//	/preset/save
			atom_setsym(&a, userpath);
			hub_preset_write(x, NULL, 1, &a);
		}
		else if (private_message == jps_slash_module_view_internals)		//	/module/view_internals
			hub_module_view_alg(x, NULL, 0, NULL);
		else if (private_message == gensym("/module/help"))
			hub_module_help(x);
		else if (private_message == gensym("/module/reference")) {
			char refstr[MAX_FILENAME_CHARS];
			
			strncpy_zero(refstr, x->attr_name->s_name, MAX_FILENAME_CHARS);
			object_method_sym(gensym("max")->s_thing, gensym("html_ref"), gensym(refstr), NULL);
			//hub_module_reference(x);
		}
		else if (private_message == gensym("/preset/interface")) {
			hub_preset_interface(x);
		}
		else if (private_message == gensym("/getstate")) {
			hub_getstate(x);
		}
		else if (private_message == jps_slash_ui_slash_freeze) {			// 	/view/freeze
			hub_symbol(x, jps_slash_ui_slash_freeze, argc, argv);
		}
		else if ( private_message == jps_slash_ui_slash_refresh )		//	/view/refresh
			hub_ui_refresh(x, NULL, 0, NULL);
		else if (private_message == gensym("fetchParameterNamesInLinklist"))
			hub_paramnames_linklist(x, (t_linklist*)atom_getobj(argv));
		else if (private_message == gensym("fetchMessageNamesInLinklist"))
			hub_messagenames_linklist(x, (t_linklist*)atom_getobj(argv));
		else if (private_message == gensym("fetchReturnNamesInLinklist"))
			hub_returnnames_linklist(x, (t_linklist*)atom_getobj(argv));
		else if (private_message == gensym("fetchPresetNamesInLinklist"))
			hub_presetnames_linklist(x, (t_linklist*)atom_getobj(argv));
		else
			hub_symbol(x, private_message, argc, argv);
	}
}


// Receive messages from jcom.return - don't send messages back to the algorithm
void hub_return(t_hub *x, t_symbol *name, long argc, t_atom *argv)
{
	char		namestring[256];
	t_symbol	*osc;
	
	strcpy(namestring, "/");						// perhaps we could optimize this operation
	strcat(namestring, argv->a_w.w_sym->s_name);	//	by creating a table when the param is bound
	osc = gensym(namestring);						//	then we could look-up the symbol instead of using gensym()
	hub_outlet_return(x, osc, argc-1, argv+1);
}


// A version of the above that performs wilcard substitution
void hub_return_extended(t_hub *x, t_symbol *name, long argc, t_atom *argv)
{
	char		namestring[256];
	t_symbol	*osc;
	
	strcpy(namestring, "/");						// perhaps we could optimize this operation
	strcat(namestring, argv->a_w.w_sym->s_name);	//	by creating a table when the param is bound
	if (namestring[strlen(namestring)-1] == '*') {
		namestring[strlen(namestring)-1] = 0;
		if (argv[1].a_type == A_LONG)
			snprintf(namestring, 256, "%s%ld", namestring, argv[1].a_w.w_long);
		else if (argv[1].a_type == A_FLOAT)
			snprintf(namestring, 256, "%s%f", namestring, argv[1].a_w.w_float);
		else // assuming symbol
			strcat(namestring, atom_getsym(argv+1)->s_name);
		osc = gensym(namestring);						//	then we could look-up the symbol instead of using gensym()
		hub_outlet_return(x, osc, argc-2, argv+2);		
	}
	else {
		osc = gensym(namestring);						//	then we could look-up the symbol instead of using gensym()
		hub_outlet_return(x, osc, argc-1, argv+1);
	}
}


// All messages being returned from the module should be funneled through this function!
void hub_outlet_return(t_hub *x, t_symbol *msg, long argc, t_atom *argv)
{
	outlet_anything(x->outlets[k_outlet_return], msg, argc, argv);

	if (x->osc_name == NULL)					// it's possible for this method to be called before osc_name is valid
		return;								//	...
	if (x->jcom_send) {
		char		mess[256];
		t_symbol	*osc;
		
		strcpy(mess, x->osc_name->s_name);
		strcat(mess, msg->s_name);
		osc = gensym(mess);
		object_method_typed(x->jcom_send, osc, argc, argv, NULL);
	}
}


void hub_getstate(t_hub *x)
{
	subscriberList*		subscriber = x->subscriber;	// head of the linked list
	subscriberIterator	i;
	t_subscriber*		t;
	char*				text = NULL;
	long				textsize = 0;

	if (!x->textEditor)
		x->textEditor = (t_object*)object_new(_sym_nobox, _sym_jed, x, 0);
	
	if (!x->textSize) {
		x->textSize = 4096;
		x->text = (char*)malloc(sizeof(char) * x->textSize);
	}
	x->text[0] = 0;
	
	critical_enter(0);
	for (i = subscriber->begin(); i != subscriber->end(); ++i) {
		t = *i;
		if (t->type == jps_subscribe_parameter) {
			long	ac = NULL; 
			t_atom* av = NULL;
			
			object_attr_getvalueof(t->object, jps_value, &ac, &av);		// get
			atom_gettext(ac, av, &textsize, &text, 0);
			
			// this is a really lame way to do this...
			if (strlen(x->text) > (x->textSize - 1024)) {
				x->textSize += 4096;
				x->text = (char*)realloc(x->text, x->textSize);
			}
			
			strncat_zero(x->text, x->osc_name->s_name, x->textSize);
			strncat_zero(x->text, "/", x->textSize);
			strncat_zero(x->text, t->name->s_name, x->textSize);
			strncat_zero(x->text, " ", x->textSize);
			strncat_zero(x->text, text, x->textSize);
			strncat_zero(x->text, "\n", x->textSize);

			sysmem_freeptr(text);
			text = NULL;
			textsize = 0;
		}
	}
	critical_exit(0);
	
	object_method(x->textEditor, _sym_settext, x->text, _sym_utf_8);
	object_attr_setchar(x->textEditor, gensym("scratch"), 1); 
	object_attr_setsym(x->textEditor, _sym_title, gensym("jamoma module state"));
	
	sysmem_freeptr(text);
}


void hub_edclose(t_hub *x, char **text, long size)
{	
	x->textEditor = NULL;
}


void hub_script(t_hub* x, SymbolPtr s, AtomCount ac, AtomPtr av)
{
	object_method_typed(x->container, _sym_script, ac, av, NULL);
}


t_symbol *hub_modulename_get(t_hub *x)
{
	t_atom	a;

	if (x->osc_name != NULL) {
		if (x->osc_name != _sym_nothing) {
			atom_setsym(&a, x->osc_name);	
			hub_outlet_return(x, gensym("/module_name"), 1, &a);
		}
	}
	return x->attr_name;
}


// TODO: Can we remove these?  I think so and that we should use attr accessors to get this info [TAP]
t_symbol* core_modulename_get(t_hub *x)
{
	return x->attr_name;
}

t_symbol *hub_algorithmtype_get(t_hub *x)
{
	return x->attr_algorithm_type;
}


void hub_paramnames_linklist(t_hub *x, t_linklist *ll)
{
	subscriberList*		subscriber = x->subscriber;	// linked list of subscribers
	subscriberIterator	i;
	t_subscriber*		t;
	t_symobject*		o;
	
	//	critical_enter(0);
	for (i = subscriber->begin(); i != subscriber->end(); ++i) {
		t = *i;
		if (t->type == jps_subscribe_parameter) {
			o = (t_symobject *)symobject_new(t->name);
			linklist_append(ll, o);
		}
	}
	//	critical_exit(0);
}

void hub_messagenames_linklist(t_hub *x, t_linklist *ll)
{
	subscriberList*		subscriber = x->subscriber;	// linked list of subscribers
	subscriberIterator	i;
	t_subscriber*		t;
	t_symobject*		o;
	
//	critical_enter(0);
	for (i = subscriber->begin(); i != subscriber->end(); ++i) {
		t = *i;
		if (t->type == jps_subscribe_message) {
			o = (t_symobject *)symobject_new(t->name);
			linklist_append(ll, o);
		}
	}
//	critical_exit(0);
}

void hub_returnnames_linklist(t_hub *x, t_linklist *ll)
{
	subscriberList*		subscriber = x->subscriber;	// linked list of subscribers
	subscriberIterator	i;
	t_subscriber*		t;
	t_symobject*		o;
	
	//	critical_enter(0);
	for (i = subscriber->begin(); i != subscriber->end(); ++i) {
		t = *i;
		if (t->type == jps_subscribe_return) {
			o = (t_symobject *)symobject_new(t->name);
			linklist_append(ll, o);
		}
	}
	//	critical_exit(0);
}

void hub_init(t_hub *x, t_symbol*, long, t_atom*)
{
	subscriberList	*subscriber = x->subscriber;
	subscriberIterator i;

	// The flag is indicating that we're in the middle of initialization
	x->flag_init = 1;
	// Search the linked list for jcom.init objects and 'bang' them
	critical_enter(0);
	for (i = subscriber->begin(); i != subscriber->end(); ++i) {
		if ((*i)->type == jps_subscribe_init)
			object_method((*i)->object, jps_go);		// TODO: This is an exceptionally bad thing to do inside of the critical region
														// It could result in a deadlock
	}
	
	critical_exit(0);
	defer_low(x, (method)hub_preset_default, 0, 0, 0L);
}


// send a local jcom.init message for the module
void hub_qfn_init(t_hub *x)
{
	hub_gui_build(x);							// immediately set up the GUI
	defer_low(x, (method)hub_init, 0, 0, 0);	// defer the rest of the initialization
}


// send info to gui constructor
void hub_gui_build(t_hub *x)
{
	subscriberList 	*subscriber = x->subscriber;

	if (x->gui_object != NULL) {
		t_atom				a[3];
		subscriberIterator	i;
		t_subscriber*		t;
		
		critical_enter(0);
		for (i = subscriber->begin(); i != subscriber->end(); ++i) {
			t = *i;
			if ((t->type == jps_subscribe_remote) && t->name == jps__gui__) {
				atom_setsym(&a[0], gensym("module_name"));
				atom_setsym(&a[1], x->osc_name);
				object_method_typed(x->gui_object, jps_dispatched, 2, a, NULL);			
				
				atom_setsym(&a[0], gensym("module_class"));
				atom_setsym(&a[1], x->attr_name);
				object_method_typed(x->gui_object, jps_dispatched, 2, a, NULL);			
				
				atom_setsym(&a[0], gensym("module_type"));
				atom_setsym(&a[1], x->attr_type);
				object_method_typed(x->gui_object, jps_dispatched, 2, a, NULL);			
			}
		}
		critical_exit(0);
	}
}


/************************************************************************************/
// Methods bound to input/inlets

// Method for Assistance Messages
void hub_assist(t_hub *x, void *b, long msg, long arg, char *dst)
{
	if (msg==1) 						// Inlet
		strcpy(dst, "input");
	else {							// Outlets
		switch(arg) {
			case k_outlet_return:
					strcpy(dst, "return: connect to return outlet");
					break;
			case k_outlet_dumpout:
					strcpy(dst, "dumpout");
					break;
		}
 	}		
}


// return a pointer to the jcom.in~ object
t_object* hub_getobj_audioin(t_hub *x)
{
	if (x->attr_type == jps_audio)
		return x->in_object;
	else
		return NULL;
}


// return a pointer to the jcom.out~ object
t_object* hub_getobj_audioout(t_hub *x)
{
	if (x->attr_type == jps_audio)
		return x->out_object;
	else
		return NULL;
}


// Return a list of parameters and message for this module
void hub_paramnames_get(t_hub *x)
{
	subscriberList		*subscriber = x->subscriber;	// head of the linked list
	t_atom				a;
	t_atom				*av;
	long				ac;
	subscriberIterator	i;
	t_subscriber*		t;
	short				num_params_with_priority = 0;
	short				num_params_recalled = 0;
	short				p;
	
	hub_outlet_return(x, jps_parameter_names_start, 0, NULL);
	
	// Count the number of parameters with a priority
	critical_enter(0);
	for (i = subscriber->begin(); i != subscriber->end(); ++i) {
		t = *i;
		if (t->type == jps_subscribe_parameter) {
			ac = NULL; 
			av = NULL;	
			object_attr_getvalueof(t->object, jps_priority, &ac, &av);
			if (atom_getlong(av) > 0)
				num_params_with_priority++;		
		}
	}
	critical_exit(0);

	if (num_params_with_priority > 0) {
		p=1;
		while (num_params_with_priority > num_params_recalled) {
			critical_enter(0);
			for (i = subscriber->begin(); i != subscriber->end(); ++i) {
				t = *i;
				if (t->type == jps_subscribe_parameter) {
					ac = NULL; 
					av = NULL;	
					object_attr_getvalueof(t->object, jps_priority, &ac, &av);
					if (atom_getlong(av) == p) {
						ac = NULL; av = NULL;								// init
						atom_setsym(&a, t->name);
						if (t->type == jps_subscribe_parameter)
							hub_outlet_return(x, jps_parameter_name, 1, &a);
						num_params_recalled++;
					}
				}
			}
			critical_exit(0);
			p++;
		}

		// Recall items with priority 0 now
		critical_enter(0);
		for (i = subscriber->begin(); i != subscriber->end(); ++i) {
			t = *i;
			if (t->type == jps_subscribe_parameter) {
				ac = NULL; 
				av = NULL;	
				object_attr_getvalueof(t->object, jps_priority, &ac, &av);
				if (atom_getlong(av) == 0) {
					ac = NULL; av = NULL;										// init
					atom_setsym(&a, t->name);
					if (t->type == jps_subscribe_parameter)
						hub_outlet_return(x, jps_parameter_name, 1, &a);
				}
			}
		}
		critical_exit(0);
	}
	else {
		critical_enter(0);
		for (i = subscriber->begin(); i != subscriber->end(); ++i) {
			t = *i;
			if (t->type == jps_subscribe_parameter) {
				ac = NULL; 
				av = NULL;	
				object_attr_getvalueof(t->object, jps_priority, &ac, &av);
				if (atom_getlong(av) == 0) {
					ac = NULL; av = NULL;										// init
					atom_setsym(&a, t->name);
					if (t->type == jps_subscribe_parameter)
						hub_outlet_return(x, jps_parameter_name, 1, &a);
				}
			}
		}
		critical_exit(0);
	}

	hub_outlet_return(x, jps_parameter_names_end, 0, NULL);
}


// Return a list of parameters and message for this module
void hub_paramvalues_get(t_hub *x)
{
	subscriberList		*subscriber = x->subscriber;	// head of the linked list
	t_atom				*av;
	long				ac;
	char				osc[512];
	subscriberIterator	i;
	t_subscriber*		t;
	short				num_params_with_priority = 0;
	short				num_params_recalled = 0;
	short				p;

	hub_outlet_return(x, jps_parameter_values_start, 0, NULL);
	
	// Count the number of parameters with a priority
	critical_enter(0);
	for (i = subscriber->begin(); i != subscriber->end(); ++i) {
		t = *i;
		if (t->type == jps_subscribe_parameter) {
			ac = NULL; 
			av = NULL;	
			object_attr_getvalueof(t->object, jps_priority, &ac, &av);
			if (atom_getlong(av) > 0)
				num_params_with_priority++;		
		}
	}
	critical_exit(0);

	if (num_params_with_priority > 0) {
		p=1;
		while (num_params_with_priority > num_params_recalled) {
			critical_enter(0);
			for (i = subscriber->begin(); i != subscriber->end(); ++i) {
				t = *i;
				if (t->type == jps_subscribe_parameter) {
					ac = NULL; 
					av = NULL;	
					object_attr_getvalueof(t->object, jps_priority, &ac, &av);
//					post("Priority" + atom_getlong(av));
					if (atom_getlong(av) == p) {
						ac = NULL; av = NULL;										// init
						object_attr_getvalueof(t->object, jps_value, &ac, &av);		// get	
						snprintf(osc, 512, "%s/%s", jps_parameter_value->s_name, t->name->s_name);
						hub_outlet_return(x, gensym(osc), ac, av);
						num_params_recalled++;
					}
				}
			}
			critical_exit(0);
			p++;
		}

		// Recall items with priority 0 now
		critical_enter(0);
		for (i = subscriber->begin(); i != subscriber->end(); ++i) {
			t = *i;
			if (t->type == jps_subscribe_parameter) {
				ac = NULL; 
				av = NULL;	
				object_attr_getvalueof(t->object, jps_priority, &ac, &av);
				if (atom_getlong(av) == 0) {
					ac = NULL; av = NULL;										// init
					object_attr_getvalueof(t->object, jps_value, &ac, &av);		// get	
					snprintf(osc, 512, "%s/%s", jps_parameter_value->s_name, t->name->s_name);
					hub_outlet_return(x, gensym(osc), ac, av);
				}
			}
		}
		critical_exit(0);
	}
	else {
		critical_enter(0);
		for (i = subscriber->begin(); i != subscriber->end(); ++i) {
			t = *i;
			if (t->type == jps_subscribe_parameter) {
				ac = NULL; 
				av = NULL;	
				object_attr_getvalueof(t->object, jps_priority, &ac, &av);
				if (atom_getlong(av) == 0) {
					ac = NULL; av = NULL;										// init
					object_attr_getvalueof(t->object, jps_value, &ac, &av);		// get	
					snprintf(osc, 512, "%s/%s", jps_parameter_value->s_name, t->name->s_name);
					hub_outlet_return(x, gensym(osc), ac, av);
				}
			}
		}
		critical_exit(0);
	}
	hub_outlet_return(x, jps_parameter_values_end, 0, NULL);
}


void hub_messagenames_get(t_hub *x)
{
	subscriberList	*subscriber = x->subscriber;	// linked list of subscribers
	t_atom			a;
	
	hub_outlet_return(x, jps_message_names_start, 0, NULL);
	
	subscriberIterator i;
	t_subscriber* t;
	critical_enter(0);
	for (i = subscriber->begin(); i != subscriber->end(); ++i) {
		t = *i;
		atom_setsym(&a, t->name);
		if (t->type == jps_subscribe_message)
			hub_outlet_return(x, jps_message_name, 1, &a);
	}
	critical_exit(0);
	hub_outlet_return(x, jps_message_names_end, 0, NULL);
}


void hub_returnnames_get(t_hub *x)
{
	subscriberList	*subscriber = x->subscriber;	// head of the linked list
	t_atom			a;
	
	hub_outlet_return(x, jps_return_names_start, 0, NULL);
	
	subscriberIterator i;
	t_subscriber* t;
	critical_enter(0);
	for (i = subscriber->begin(); i != subscriber->end(); ++i) {
		t = *i;
		atom_setsym(&a, t->name);
		if (t->type == jps_subscribe_return)
			hub_outlet_return(x, jps_message_return, 1, &a);
	}
	critical_exit(0);
	hub_outlet_return(x, jps_return_names_end, 0, NULL);
}


// TODO: Should this be removed and replaced by a call to the Jamoma object in the framework?
void hub_allnames_get(t_hub *x)
{
	hub_paramnames_get(x);
	hub_messagenames_get(x);
	hub_returnnames_get(x);
}


void hub_module_help(t_hub* x)
{
	classname_openhelp(x->attr_name->s_name);
}

void hub_module_reference(t_hub* x)
{
	classname_openrefpage(x->attr_name->s_name);
}


// SYMBOL INPUT
void hub_symbol(t_hub *x, t_symbol *msg, long argc, t_atom *argv)
{
	bool			found = false;
	subscriberList	*subscriber = x->subscriber;
	char			input[MAX_STRING_LEN];	// our input string
	char			*input2 = input;		// pointer to our input string
	char			*split;
	t_symbol		*osc = NULL;
	t_symbol		*name = msg;			// default to the name being the message

	strcpy(input, msg->s_name);
	if (*input2 == '/')				// leading slash means it's OSC...
		input2++;					// remove the leading slash

	split = strchr(input2, ':');	// remove (and store) the param name
	if (split != NULL) {
		*split = NULL;				// now input2 = param name; split = a message for the parameter object
		split += 2;					// this will jump the pointer past the :/ to the actual name
		osc = gensym(split);
	}
	name = gensym(input2);

	subscriberIterator i;
	t_subscriber* t;
	critical_enter(0);
	if (name == jps_star) {			// wildcard
		t_symbol* type;
		for (i = subscriber->begin(); i != subscriber->end(); ++i) {
			t = *i; type = t->type;
			if (type == jps_subscribe_parameter 
			  || type == jps_subscribe_message 
			  || type == jps_subscribe_return) {
				if (osc == NULL) {
					object_method_typed(t->object, jps_dispatched, argc, argv, NULL);
				}
				else {
					object_method_typed(t->object, osc, argc, argv, NULL);
				}
			}
		}
	}
	else {
		
		// search the linked list of params to find the right one
		for (i = subscriber->begin(); (i != subscriber->end()) && (found == false); ++i) {
			t = *i; 
			if (t->name == name) {
				found = true;
				break;
			}
		}

		// dispatch to the correct jcom.param object
		if (found == true) {
			if (osc == NULL) {
				object_method_typed(t->object, jps_dispatched, argc, argv, NULL);
			}
			else
				object_method_typed(t->object, osc, argc, argv, NULL);
		}
		else {
			// Check to see if it's a message we need to forward to jcom.out
			if (name == jps_slash_audio_meters_freeze || name == jps_audio_meters_freeze) {
				t_atom msg[2];
				atom_setsym(msg, name);
				jcom_core_atom_copy(msg+1, argv);
				if (x->out_object != NULL)
					object_method_typed(x->out_object, jps_algorithm_message, 2, msg, NULL);	
			} else if (!x->using_wildcard) {
				// if we got here through the use a remote message to modules named by a wildcard
				// then we need don't post annoying errors to the Max window
				if (x->editing)
					object_error((t_object*)x, "No message or parameter named %s (in %s module).", name->s_name, x->attr_name->s_name);
				else	
					object_error((t_object*)x, "No message or parameter named %s (in %s module).", name->s_name, x->osc_name->s_name);
			}
		}
	}
	critical_exit(0);
}


void hub_module_view_alg(t_hub *x, t_symbol*, long, t_atom*)
{
	if (x->in_object != NULL)
		object_method_typed(x->in_object, jps_open, 0, 0L, NULL);					// send "open" to jcom.in
	hub_outlet_return(x, jps_slash_module_view_internals, 0, 0L);					// return from jcom.hub left outlet
}


// FREEZE UI for all parameters
void hub_ui_freeze(t_hub *x, t_symbol*, long argc, t_atom *argv)
{
	subscriberList *subscriber = x->subscriber;	// head of the linked list
	t_max_err err = MAX_ERR_NONE;

	// Change freeze status for all messages and parameters
	subscriberIterator i;
	t_subscriber* t;

	// Change freeze attribute for the gui
	// FIXME: This call is not working!!!!
	// this means that the ui menu does not always reflect the state correctly
	err = object_attr_setlong(x->gui_object, gensym("ui_is_frozen"), atom_getlong(argv));

	critical_enter(0);
 	for (i = subscriber->begin(); i != subscriber->end(); ++i) {
		t = *i;
		if (t->type == jps_subscribe_parameter)
			object_method_typed(t->object, jps_ui_slash_freeze, 1, argv, NULL);
	}
	critical_exit(0);
}


// REFRESH UI for all parameters
void hub_ui_refresh(t_hub *x, t_symbol*, long, t_atom*)
{
	subscriberList *subscriber = x->subscriber;	// head of the linked list
	
	subscriberIterator i;
	t_subscriber* t;
	critical_enter(0);
	for (i = subscriber->begin(); i != subscriber->end(); ++i) {
		t = *i;
		if (t->type == jps_subscribe_parameter)
			object_method_typed(t->object, jps_ui_slash_refresh, 0, 0L, NULL);
	}
	critical_exit(0);
}


// receive messages from our internal jcom.receive external
void hub_receive_callback(void *z, t_symbol *msg, long argc, t_atom *argv)
{
	t_hub		*x = (t_hub *)z;
	char		mess[256];
	char		*in = &mess[0];
	char		*split;
	t_symbol	*osc;
	
	strncpy_zero(mess, msg->s_name, 256);
	if (*in == '/')					// remove leading slash...
		in++;
		
	split = strchr(in, '/');		// get the OSC message for the module
	if (split == NULL) {
		if (x->editing)
			object_error((t_object*)x, "%s module received message from jcom.send with problematic or missing OSC namespace (%s) in %s module", 
										x->attr_name->s_name, mess, x->attr_name->s_name);
		else	
			object_error((t_object*)x, "%s module received message from jcom.send with problematic or missing OSC namespace (%s) in %s module", 
										x->attr_name->s_name, mess, x->osc_name->s_name);
		return;
	}

	*split = 0;						
	
	if (*in == '*') {										// wildcard
		// when parsing wildcards, we need to check and see if there is actually a valid subscriber
		// before blindly sending the message... 
		split++;
		osc = gensym(split);
		x->using_wildcard = true;
		object_method_typed(x, osc, argc, argv, NULL);		// call the method on this hub object
		x->using_wildcard = false;
	}
	else if (x->osc_name && x->osc_name->s_name[0] && !strcmp(mess, x->osc_name->s_name)) {		// check if we are the correct module...
		split++;
		osc = gensym(split);
		object_method_typed(x, osc, argc, argv, NULL);		// call the method on this hub object
	}
}



// 'bang' method for user input
void hub_bang(t_hub *x)
{	
	subscriberList		*subscriber = x->subscriber;	// head of the linked list
	subscriberIterator	i;
	t_subscriber		*t;
	t_symbol			*type;
	
	for (i = subscriber->begin(); i != subscriber->end(); ++i) {
		t = *i; 
		type = t->type;		
		if (type == jps_subscribe_parameter || type == jps_subscribe_message)
			object_method(t->object, gensym("/ramp/update"));
	}	
}


// TODO: need a custom setter so that we can update the display of the module name in the ui
t_max_err hub_attr_setname(t_hub* x, t_object* attr, long argc, t_atom* argv)
{
	if (argc && argv) {
		char			name[256];
		unsigned short	i;
		t_max_err		err = MAX_ERR_NONE;
		char*			nametest;
		t_atom			a[2];
		int				instance = 0;
		TTBoolean		nameConflict = false;
		t_symbol*		nameOriginal;
		
		x->osc_name = atom_getsym(argv);

		// No arg is present -- try to invent something intelligent for a name
		if (x->osc_name == _sym_nothing) {
			// it's annoting when doing fast demos and such to have to see this, so it is now silent when doing this:
			// object_post((t_object*)x, "%s: this module was not given an osc name as an argument!  making up something that will hopefully work.", x->attr_name->s_name);

			// Strip jmod. from the beginning of patch names, this happens if you drag a module from browser to bpatcher
			if (strncmp(x->attr_name->s_name, "jmod.", 5) == 0)
				x->osc_name = gensym(x->attr_name->s_name + 5);
			else
				x->osc_name = x->attr_name;
		}
		
		strcpy(name, x->osc_name->s_name);
		
		// the name is autoprepended with a /
		if (name[0] != '/') {
			char newname[256];
			
			strcpy(newname, "/");
			strcat(newname, name);
			strcpy(name, newname);
		}
		
		// search for illegal characters as specified by the OSC standard and replace them
		for (i=0; i<strlen(name); i++) {
/*			TODO :This has to happen only when setting the OSC name from the module's file name
			if (name[i] == '.')
				name[i] = '_';
			else */
			if (name[i] == '[')
				name[i] = '.';
			else if (name[i] == ']')
				name[i] = 0;
		}
		
		// if arg contains a slash then we must complain
		nametest = name + 1;
		if (strchr(nametest, '/'))
			object_error((t_object*)x, "%s: OSC NAME GIVEN TO MODULES MAY NOT CONTAIN A SLASH OTHER THAN THE LEADING SLASH!", x->attr_name->s_name);
		nameOriginal = gensym(name);
	again:
		x->osc_name = gensym(name);
		
		// update the ui object
		if (x->gui_object) {
			atom_setsym(&a[0], gensym("module_name"));
			atom_setsym(&a[1], x->osc_name);
			object_method_typed(x->gui_object, jps_dispatched, 2, a, NULL);			
		}
		
		// Register with the framework, and making sure this name hasn't already been used...
		// TODO: is the framework making sure that this t_object is unique and hasn't already been registered?
		err = jamoma_hub_register(x->osc_name, (t_object *)x);
		if (err) {
			if (instance) {
				nametest = strrchr(name, '.');
				if (nametest)
					*nametest = 0;
			}
			instance++;
			nametest = name;
			snprintf(name, 256, "%s.%i", name, instance);
			nameConflict = true;
			err = MAX_ERR_NONE;
			goto again;
		}
		if (nameConflict)
			object_post((t_object*)x, "Jamoma cannot create multiple modules with the same OSC identifier (%s).  Using %s instead.", nameOriginal->s_name, name);
		
		// And send a notification to the environment
		atom_setsym(a, x->attr_name);
		atom_setsym(a+1, x->osc_name);
		object_method_typed(g_jcom_send_notifications, gensym("module.new"), 2, a, NULL);
	}
	return MAX_ERR_NONE;
}

