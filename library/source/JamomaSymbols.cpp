/* 
 * Jamoma Symbols
 * Symbols cached to avoid repeated calls to the expensive SymbolGen() function
 * By Tim Place, Copyright © 2006
 * 
 * License: This code is licensed under the terms of the "New BSD License"
 * http://creativecommons.org/licenses/BSD/
 */

#ifdef WIN_VERSION
 #pragma warning(disable:4083) //warning C4083: expected 'newline'; found identifier 's'
#endif // WIN_VERSION

#include "MaxObjectTypes.h"
#include "JamomaSymbols.h"

t_symbol	*jps_done,
//		*jps_none,					// ramp stuff
			*jps_linear,
			*jps_linear_q,
			*jps_ramp_update,
			*jps_low,					// clip stuff
			*jps_high, 
			*jps_both,
			*jps_wrap,
			*jps_fold,
			*jps_inc,					// increase, decrease
			*jps_dec,
			*jps_generic, 				// types
			*jps_integer, 
			*jps_decimal, 
			*jps_string,
			*jps_array,
			*jps_boolean, 
			*jps_none,				// this type only used by jcom.message
			*jps_jcom_hub, 
			*jps_feedback,
			*jps_module_name_get,		// common OSC messages according to the JIG
			*jps_core_module_name_get,
			*jps_dumpout,
			*jps_audio, 
			*jps_video, 
			*jps_control, 
			*jps_dispatched, 
			*jps_parameter_name,
			*jps_message_name,
			*jps_message_return,
			*jps_parameter_names_start, 
			*jps_parameter_names_end,			
			*jps_message_names_start, 
			*jps_message_names_end,
			*jps_return_names_start, 
			*jps_return_names_end,
			*jps_parameter_values_start,
			*jps_parameter_values_end,
			*jps_parameter_value,
			*jps_subscribe,				// subscribe stuff
			*jps_unsubscribe,
			*jps_release,
			*jps_subscribe_in,
			*jps_subscribe_out,
			*jps_subscribe_message,
			*jps_subscribe_parameter,
			*jps_subscribe_remote,
			*jps_subscribe_return,
			*jps_subscribe_init,
			*jps_subscribe_meter,
			*jps_inspector,
			*jps_num_inputs,				// signal inlets and outlets
			*jps_num_outputs,
			*jps_type,						// parameter/message/return attributes
			*jps_algorithm_type,
			*jps_name,
			*jps_dataspace,
			*jps_unit_native,	
			*jps_unit_active,				
			*jps_unit_display,
			*jps_range,
			*jps_range_bounds,
			*jps_range_clipmode,
			*jps_clipmode,
			*jps_ramp,
			*jps_ramp_drive,
			*jps_ramp_function,
			*jps_repetitions,
			*jps_repetitions_allow,
			*jps_description,
			*jps_value,
			*jps_sigcount,				// signals to module
			*jps_siglist,
			*jps_config_changed,
			*jps_algorithm,
			*jps_get_num_channels,
			*jps_module_type,			// module type
			*jps_poly,
			*jps_default,
			*jps_jitter,
			*jps_1U,
			*jps_1U_half,
			*jps_algorithm_message,
			*jps_private,
			*jps__gui__,
			*jps__jcom_in__,
			*jps__jcom_out__,
			*jps___preview__,
			*jps_return,
			*jps_return_extended,
			*jps_go,
			*jps_init,
			*jps_ATTRIBUTES,
			*jps_BUILD,
			*jps_MODULE_NAME,			// name of this module class
			*jps_MODULE_TITLE,			// OSC name of this module instance
			*jps_PARAMETER,
			*jps_NEW_PRESETS_START,
			*jps_NEW_PRESETS,
			*jps_MENU_REBUILD,
			*jps_size,
			*jps_skin,
			*jps_jcom_send,	
			*jps_jcom_receive,
			*jps_jcom_remote_fromModule, 			
			*jps_jcom_remote_toModule,
			*jps_jcom_broadcast_fromHub,
			*jps_from_in_object,
			*jps_box,
			*jps_setcallback,
			*jps_link_in,				// common OSC messages, etc.
			*jps_link_out,
			*jps_unlink_in,
			*jps_unlink_out,
			*jps_audio_gain_midi,
			*jps_slash_audio_gain_midi,
			*jps_audio_mute,
			*jps_slash_audio_mute,
			*jps_audio_bypass,
			*jps_slash_audio_bypass,
			*jps_audio_mix,
			*jps_slash_audio_mix,
			*jps_audio_sample_rate,
			*jps_slash_audio_sample_rate,
			*jps_audio_meters_freeze,
			*jps_slash_audio_meters_freeze,
			*jps_video_mute,
			*jps_slash_video_mute,
			*jps_video_bypass,
			*jps_slash_video_bypass,
			*jps_video_freeze,
			*jps_slash_video_freeze,
			*jps_video_preview,
			*jps_slash_video_preview,			
			*jps_open,							// 	open
			*jps_slash_module_view_internals,	//	/module/view_internals
			*jps_slash_preset_slash_default,		// 	/preset/default
			*jps_slash_preset_slash_load,		// 	/preset/load
			*jps_slash_preset_slash_store,
			*jps_slash_preset_slash_storenext,
			*jps_slash_preset_slash_storecurrent,
			*jps_slash_preset_slash_recall,
			*jps_slash_preset_slash_write,		// 	/preset/save
			*jps_slash_preset_slash_writeagain,	// 	/preset/save
			*jps_slash_preset_slash_copy,		// 	/preset/save
			*jps_ui_slash_freeze,				//	view/freeze
			*jps_slash_ui_slash_freeze,			//	/view/freeze
			*jps_ui_slash_refresh,				//	view/refresh
			*jps_slash_ui_slash_refresh,			//	/view/refresh		
			*jps_register_meter,
			*jps_register_preview,
			*jps_voices,
			*jps_mute,
			*jps_target,
			*jps_sendlastvalue,
			*jps_sendbypassedvalue,
			*jps_star,
			*jps_priority,
			*jps_add,							// used for calling methods on jcom.receivemaster
			*jps_remove,
			*jps_dispatch
			;


void jamomaSymbolsInit()
{
	jps_done						= SymbolGen("done");
	// ramp stuff
	jps_none						= SymbolGen("none");
	jps_linear						= SymbolGen("linear");
	jps_linear_q					= SymbolGen("linear.q");
	jps_ramp_update					= SymbolGen("ramp_update");
	//clip stuff
	jps_low							= SymbolGen("low"); 
	jps_high						= SymbolGen("high"); 
	jps_both						= SymbolGen("both");
	jps_wrap						= SymbolGen("wrap");
	jps_fold						= SymbolGen("fold");
	// increase and decrease
	jps_inc							= SymbolGen("inc");
	jps_dec							= SymbolGen("dec");
	// types
	jps_generic					= SymbolGen("generic"); 
	jps_integer						= SymbolGen("integer"); 
	jps_decimal					= SymbolGen("decimal"); 
	jps_string					= SymbolGen("string");
	jps_array					= SymbolGen("array");
	jps_boolean					= SymbolGen("boolean");
	jps_none					= SymbolGen("none");			// this type only used by jcom.message
	jps_jcom_hub					= SymbolGen("jcom.hub"); 
    jps_feedback					= SymbolGen("__feedback__");		// used for parameter feedback to the hub
	// common OSC messages according to the JIG
	jps_module_name_get				= SymbolGen("/module_name:/get");
	jps_core_module_name_get		= SymbolGen("core_module_name:/get");
	jps_dumpout						= SymbolGen("dumpout");
	jps_audio						= SymbolGen("audio");
	jps_video						= SymbolGen("video");
	jps_control						= SymbolGen("control");
	jps_dispatched					= SymbolGen("dispatched");
	jps_parameter_name				= SymbolGen("/parameter_name");
	jps_message_name				= SymbolGen("/message_name");
	jps_message_return				= SymbolGen("/return_name");
	jps_parameter_names_start		= SymbolGen("/parameter_names_start");
	jps_parameter_names_end			= SymbolGen("/parameter_names_end");
	jps_message_names_start			= SymbolGen("/message_names_start"); 
	jps_message_names_end			= SymbolGen("/message_names_end");
	jps_return_names_start			= SymbolGen("/return_names_start");
	jps_return_names_end			= SymbolGen("/return_names_end");
	jps_parameter_values_start		= SymbolGen("/parameter_values_start");
	jps_parameter_values_end		= SymbolGen("/parameter_values_end");
	jps_parameter_value				= SymbolGen("/parameter_value");
	// subscribe stuff
    jps_subscribe					= SymbolGen("subscribe");
	jps_unsubscribe					= SymbolGen("unsubscribe");
	jps_release						= SymbolGen("release");
	jps_subscribe_in				= SymbolGen("subscribe_in"); 
	jps_subscribe_out				= SymbolGen("subscribe_out"); 
	jps_subscribe_message			= SymbolGen("subscribe_message"); 
	jps_subscribe_parameter			= SymbolGen("subscribe_parameter"); 
	jps_subscribe_remote			= SymbolGen("subscribe_remote"); 
	jps_subscribe_return			= SymbolGen("subscribe_return");
	jps_subscribe_init				= SymbolGen("subscribe_init");
	jps_subscribe_meter				= SymbolGen("subscribe_meter");
	// signal inlets and outlets
	jps_num_inputs					= SymbolGen("num_inputs");
	jps_num_outputs					= SymbolGen("num_outputs");
	// parameter/message/return attributes
	jps_inspector					= SymbolGen("inspector");
	jps_type						= SymbolGen("type");
	jps_dataspace					= SymbolGen("dataspace");
	jps_unit_native					= SymbolGen("dataspace/unit/native");
	jps_unit_active					= SymbolGen("dataspace/unit/active");
	jps_unit_display				= SymbolGen("dataspace/unit/display");
	// %TODO: jps_range should probably be removed
	jps_range						= SymbolGen("range");
	jps_range_bounds				= SymbolGen("range/bounds");
	jps_range_clipmode				= SymbolGen("range/clipmode");
	// %TODO: jps_clipmode should probably be removed
	jps_clipmode					= SymbolGen("clipmode");
	jps_ramp						= SymbolGen("ramp");
	jps_ramp_drive					= SymbolGen("ramp/drive");
	jps_ramp_function				= SymbolGen("ramp/function");
	// %TODO: jps_repetitions should probably be removed
	jps_repetitions					= SymbolGen("repetitions");
	jps_repetitions_allow			= SymbolGen("repetitions/allow");
	jps_description					= SymbolGen("description");
	jps_value						= SymbolGen("value");
	jps_algorithm_type				= SymbolGen("algorithm_type");
	jps_name						= SymbolGen("name");
	// signals to module
	jps_sigcount					= SymbolGen("sigcount");
	jps_siglist						= SymbolGen("siglist");
	jps_config_changed				= SymbolGen("config_changed");
	jps_algorithm					= SymbolGen("algorithm");
	jps_get_num_channels			= SymbolGen("get_num_channels");
	// module type
	jps_module_type					= SymbolGen("module_type");
	jps_poly						= SymbolGen("poly");
	jps_default						= SymbolGen("default");
	jps_jitter						= SymbolGen("jitter");
	jps_1U							= SymbolGen("1U");
	jps_1U_half						= SymbolGen("1U-half");
	jps_algorithm_message			= SymbolGen("algorithm_message");
	jps_private						= SymbolGen("private");		// method called in the hub by jcom.remote
	jps__gui__						= SymbolGen("__GUI__");		// name of jcom.remote in the gui
	jps__jcom_in__					= SymbolGen("__jcom_in__");	// name of the module's jcom.in object
	jps__jcom_out__					= SymbolGen("__jcom_out__");	// name of the module's jcom.out object
	jps___preview__					= SymbolGen("__preview__");	// name of the remote for jitter preview matrices
	jps_return						= SymbolGen("return");			// method called in the hub by jcom.return
	jps_return_extended				= SymbolGen("return_extended");
	jps_go							= SymbolGen("go");				// method in jcom.init called by the hub
	jps_init						= SymbolGen("/init");			// method in the hub called from jcom.init
	jps_ATTRIBUTES					= SymbolGen("ATTRIBUTES");
	jps_BUILD						= SymbolGen("BUILD");
	jps_MODULE_NAME					= SymbolGen("MODULE_NAME");	// name of this module class
	jps_MODULE_TITLE				= SymbolGen("MODULE_TITLE");	// OSC id of of this module instance
	jps_PARAMETER					= SymbolGen("PARAMETER");
	jps_NEW_PRESETS_START			= SymbolGen("NEW_PRESETS_START");
	jps_NEW_PRESETS					= SymbolGen("NEW_PRESETS");
	jps_MENU_REBUILD				= SymbolGen("MENU_REBUILD");
	jps_size						= SymbolGen("size");
	jps_skin						= SymbolGen("skin");
	jps_jcom_send					= SymbolGen("jcom.send");	
	jps_jcom_receive				= SymbolGen("jcom.receive");
	jps_jcom_remote_fromModule 		= SymbolGen("jcom.remote.module.from");	// different than in jamoma 0.3.x to avoid conflicts...
	jps_jcom_remote_toModule 		= SymbolGen("jcom.remote.module.to");
	jps_jcom_broadcast_fromHub		= SymbolGen("jcom.broadcast.hub.from");	// used to tell subscribers in a module to subscribe (hub has changed)
	jps_from_in_object				= SymbolGen("from_in_object");	// messages to the jcom.out object
	jps_box							= SymbolGen("box");
	jps_setcallback					= SymbolGen("setcallback");
	jps_link_in						= SymbolGen("link_in");
	jps_link_out					= SymbolGen("link_out");
	jps_unlink_in					= SymbolGen("unlink_in");
	jps_unlink_out					= SymbolGen("unlink_out");
	jps_audio_gain_midi				= SymbolGen("audio/gain/midi");		// used by the i/o objects...
	jps_slash_audio_gain_midi		= SymbolGen("/audio/gain/midi");
	jps_audio_mute					= SymbolGen("audio/mute");
	jps_slash_audio_mute			= SymbolGen("/audio/mute");
	jps_audio_bypass				= SymbolGen("audio/bypass");
	jps_slash_audio_bypass			= SymbolGen("/audio/bypass");
	jps_audio_mix					= SymbolGen("audio/mix");
	jps_slash_audio_mix				= SymbolGen("/audio/mix");
	jps_audio_sample_rate			= SymbolGen("audio/sample_rate");
	jps_slash_audio_sample_rate		= SymbolGen("/audio/sample_rate");
	jps_audio_meters_freeze			= SymbolGen("audio/meters/freeze");
	jps_slash_audio_meters_freeze 	= SymbolGen("/audio/meters/freeze");
	jps_video_mute					= SymbolGen("video/mute");
	jps_slash_video_mute			= SymbolGen("/video/mute");
	jps_video_bypass				= SymbolGen("video/bypass");
	jps_slash_video_bypass			= SymbolGen("/video/bypass");
	jps_video_freeze				= SymbolGen("video/freeze");
	jps_slash_video_freeze			= SymbolGen("/video/freeze");
	jps_video_preview				= SymbolGen("video/preview");
	jps_slash_video_preview			= SymbolGen("/video/preview");	
	jps_register_meter				= SymbolGen("register_meter");
	jps_register_preview			= SymbolGen("register_preview");
	jps_open						= SymbolGen("open");
	jps_slash_module_view_internals = SymbolGen("/module/view_internals");
	jps_slash_preset_slash_default 	= SymbolGen("/preset/default");
	jps_slash_preset_slash_load		= SymbolGen("/preset/load");
	jps_slash_preset_slash_recall	= SymbolGen("/preset/recall");
	jps_slash_preset_slash_write	= SymbolGen("/preset/write");
	jps_slash_preset_slash_writeagain	= SymbolGen("/preset/writeagain");
	jps_slash_preset_slash_store	= SymbolGen("/preset/store");
	jps_slash_preset_slash_storenext	= SymbolGen("/preset/storenext");
	jps_slash_preset_slash_storecurrent = SymbolGen("/preset/storecurrent");
	jps_slash_preset_slash_copy		= SymbolGen("/preset/copy");		
	jps_ui_slash_freeze				= SymbolGen("view/freeze");
	jps_slash_ui_slash_freeze		= SymbolGen("/view/freeze");
	jps_ui_slash_refresh			= SymbolGen("view/refresh");
	jps_slash_ui_slash_refresh		= SymbolGen("/view/refresh");
	jps_voices						= SymbolGen("voices");
	jps_mute						= SymbolGen("mute");
	jps_target						= SymbolGen("target");
	jps_sendlastvalue				= SymbolGen("sendlastvalue");
	jps_sendbypassedvalue			= SymbolGen("sendbypassedvalue");
	jps_star						= SymbolGen("*");
	jps_priority					= SymbolGen("priority");
	jps_add							= SymbolGen("add");					// used for calling methods on jcom.receivemaster
	jps_remove						= SymbolGen("remove");
	jps_dispatch					= SymbolGen("dispatch");
}

