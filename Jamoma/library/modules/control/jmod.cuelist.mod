max v2;
#N vpatcher 221 158 1164 648;
#P window setfont "Sans Serif" 9.;
#P window linecount 1;
#P newex 104 192 78 196617 jmod.pass open;
#P window linecount 2;
#P newex 419 233 208 196617 jmod.message.mxt $0_ /view @description "View current cue script in a text window.";
#P window linecount 1;
#P newex 419 211 84 196617 pvar OpenButten;
#P user jsui 103 26 51 22 1 0 0 jsui_textbutton.js View;
#P objectname OpenButten;
#P window linecount 2;
#P newex 419 365 305 196617 jmod.message.mxt $0_ /remote @type generic @description "Wireless communication of messages to modules via the bridge.";
#P newex 419 305 238 196617 jmod.message.mxt $0_ /cue_event @type generic @description "Recall cue event from cue script.";
#P user jsui 157 26 93 22 1 0 0 jsui_textbutton.js "Get State";
#P objectname GetStateButton;
#P user jsui 7 26 93 22 1 0 0 jsui_textbutton.js "Load Cue Script";
#P objectname CueScriptButton;
#P window linecount 1;
#P newex 104 227 45 196617 pcontrol;
#P message 38 89 43 196617 autodoc;
#P newex 419 117 107 196617 pvar CueScriptButton;
#P window linecount 4;
#P newex 419 139 338 196617 jmod.message.mxt $0_ /load_script @description "Load cue script from file. <br>NOTE: jmod.cue_list will be watching the file and automatically update if the content of the file is changed. This way you can use an external editor to work on the cue script while Jamoma is running.";
#P window linecount 2;
#P message 16 406 65 196617 \; max refresh;
#P message 16 369 75 196617 \; jmod.init bang;
#P window linecount 1;
#N vpatcher 85 87 878 762;
#P origin 0 -1;
#P window setfont "Sans Serif" 9.;
#P message 573 40 121 196617 /eple/tre 1;
#P window linecount 1;
#P newex 496 35 62 196617 prepend set;
#P window linecount 0;
#P message 177 32 121 196617 /remote /eple/tre 1;
#P newex 100 27 62 196617 prepend set;
#P newex 408 570 42 196617 t resume;
#P window linecount 1;
#P newex 292 164 27 196617 i;
#P newex 292 190 40 196617 uzi;
#P window linecount 0;
#P newex 292 214 58 196617 prepend line;
#P newex 408 547 30 196617 defer;
#P newex 408 525 33 196617 del 0;
#P newex 408 493 56 196617 t b i pause;
#P newex 408 471 98 196617 route WAIT;
#P newex 350 398 27 196617 + 1;
#P newex 350 377 52 196617 jmod.s==;
#P newex 218 91 37 196617 t open;
#P newex 366 88 86 196617 s jmod.to_bridge;
#N vpatcher 72 104 672 504;
#P window setfont "Sans Serif" 9.;
#P window linecount 0;
#P newex 60 58 120 196617 t b jmod.getstate clear;
#P inlet 60 28 14 0;
#P window linecount 1;
#P newex 60 121 49 196617 deferlow;
#P newex 60 143 35 196617 t open;
#P newex 115 187 40 196617 text;
#P newex 115 116 86 196617 s jmod.to_bridge;
#P newex 115 141 139 196617 r jmod.from_bridge.getstate;
#P connect 5 0 6 0;
#P connect 6 0 4 0;
#P connect 4 0 3 0;
#P connect 6 1 1 0;
#P connect 0 0 2 0;
#P fasten 6 2 2 0 175 84 280 84 280 175 120 175;
#P connect 3 0 2 0;
#P pop;
#P newobj 144 91 61 196617 p get_state;
#P window linecount 2;
#P comment 283 340 59 196617 bang: empty line;
#P window linecount 1;
#P newex 496 586 86 196617 s jmod.to_bridge;
#P newex 292 120 294 196617 t b query s stop;
#P newex 350 345 50 196617 zl slice 1;
#P newex 350 442 68 196617 gate 2 1;
#P newex 292 294 50 196617 route set;
#P newex 292 270 40 196617 text;
#N vpatcher 34 89 430 588;
#P outlet 271 402 15 0;
#P window setfont "Sans Serif" 9.;
#P newex 87 101 76 196617 route bang;
#P inlet 87 58 15 0;
#P newex 271 353 35 196617 zl reg;
#P newex 271 320 65 196617 prepend read;
#P newex 123 290 21 196617 t 1;
#P newex 87 141 55 196617 opendialog;
#P newex 215 319 51 196617 filewatch;
#P connect 5 0 6 0;
#P connect 6 0 1 0;
#P connect 6 1 2 0;
#P lcolor 13;
#P connect 1 0 2 0;
#P lcolor 14;
#P connect 6 1 0 0;
#P lcolor 13;
#P connect 1 0 0 0;
#P lcolor 14;
#P connect 2 0 0 0;
#P connect 6 1 3 0;
#P lcolor 13;
#P connect 1 0 3 0;
#P lcolor 14;
#P connect 0 0 4 0;
#P connect 3 0 4 0;
#P connect 4 0 7 0;
#P pop;
#P newobj 70 91 69 196617 p filewatcher;
#P newex 292 317 126 196617 route bang cue_event;
#P window linecount 0;
#P newex 70 62 383 196617 jmod.oscroute /load_script /get_state /view /cue_event /remote;
#P outlet 70 490 15 0;
#P inlet 70 22 15 0;
#P comment 419 376 152 196617 jmod.s== looks for cue_event messages. Only if the argument of the cue_event message equals the desired cue_event \, messages are let through the 2nd outlet for further processing.;
#P comment 588 93 182 196617 cue_events are done by reading through the script one line at a time.;
#P comment 588 134 182 196617 Only lines belonging to the current cue_event are passed through;
#P comment 508 472 72 196617 Wait before pulling next line;
#P connect 4 0 6 0;
#P connect 6 0 8 0;
#P connect 4 0 29 0;
#P connect 6 1 16 0;
#P connect 29 0 30 0;
#P connect 6 2 18 0;
#P connect 6 3 13 0;
#P connect 13 0 27 0;
#P fasten 28 0 26 0 413 612 254 612 254 186 297 186;
#P lcolor 14;
#P fasten 22 2 26 0 459 614 251 614 251 184 297 184;
#P lcolor 14;
#P connect 27 0 26 0;
#P fasten 26 2 25 0 327 210 297 210;
#P fasten 13 1 9 0 391 264 297 264;
#P fasten 18 0 9 0 223 252 297 252;
#P fasten 8 0 9 0 75 260 297 260;
#P connect 25 0 9 0;
#P connect 9 0 10 0;
#P connect 10 0 7 0;
#P fasten 9 2 27 1 327 291 401 291 401 156 314 156;
#P lcolor 1;
#P connect 7 1 12 0;
#P connect 12 0 19 0;
#P connect 19 0 20 0;
#P connect 20 0 11 0;
#P connect 6 4 17 0;
#P fasten 13 2 19 1 485 370 397 370;
#P connect 7 2 11 1;
#P connect 11 1 21 0;
#P connect 21 0 22 0;
#P connect 22 0 23 0;
#P fasten 13 3 23 0 579 521 413 521;
#P connect 23 0 24 0;
#P connect 24 0 28 0;
#P connect 22 1 23 1;
#P connect 6 4 31 0;
#P connect 21 1 14 0;
#P connect 31 0 32 0;
#P pop;
#P newobj 104 285 95 196617 p jmod.cuelist.alg;
#P newex 419 36 102 196617 pvar GetStateButton;
#P window linecount 3;
#P newex 16 114 186 196617 jmod.hub $0_ jmod.cuelist @size 1U-half @module_type control @description "Manage cue list in text format";
#P objectname jmod.hub;
#P inlet 16 90 13 0;
#P outlet 16 316 13 0;
#P window linecount 2;
#P newex 419 56 280 196617 jmod.message.mxt $0_ /get_state @description "Poll state for all bridged modules\\\, and display in text window.";
#P objectname jmod.parameter.mxt;
#P bpatcher 0 0 256 62 0 0 jmod.gui.mxt 0 $0_;
#P objectname jmod.gui.1Uh.a.stereo.mxt;
#P window linecount 3;
#P newex 210 114 79 196617 pattrstorage @autorestore 0 @savemode 0;
#X client_rect 14 59 654 299;
#X storage_rect 0 0 640 240;
#P objectname jmod.cuelist;
#P fasten 12 0 5 0 43 108 21 108;
#P connect 4 0 5 0;
#P connect 5 0 3 0;
#P fasten 7 0 3 0 109 309 21 309;
#P connect 5 1 21 0;
#P connect 21 0 13 0;
#P fasten 21 1 7 0 177 259 109 259;
#P connect 13 0 7 0;
#P connect 0 0 5 1;
#P connect 5 2 0 0;
#P connect 6 0 2 0;
#P connect 11 0 10 0;
#P connect 19 0 20 0;
#P pop;
