max v2;
#N vpatcher 77 104 1064 674;
#P window setfont "Sans Serif" 9.;
#P window linecount 1;
#P newex 591 434 80 196617 print jsjsjsjsjs;
#P window linecount 2;
#P hidden newex 359 280 43 196617 prepend append;
#P window linecount 1;
#P hidden newex 537 69 83 196617 s $1_message;
#P hidden newex 537 46 129 196617 prepend preview_window;
#P bpatcher 450 15 60 46 0 0 jmod.gui.video-component.mxt 0 $1;
#P objectname pwindow;
#P hidden newex 259 67 29 196617 gate;
#P objectname pwindow_gate;
#P hidden newex 427 282 50 196617 tosymbol;
#P hidden newex 563 309 65 196617 t menu_build;
#P window linecount 2;
#P hidden newex 427 302 99 196617 prepend menu_presets_add;
#P hidden newex 495 267 100 196617 t menu_presets_clear;
#P window linecount 1;
#P hidden message 341 194 32 196617 clear;
#P hidden newex 341 172 55 196617 r jmod.init;
#P hidden newex 447 382 90 196617 s $1_FROM_MGUI;
#P hidden outlet 405 104 13 0;
#P objectname outlet_16;
#P hidden outlet 391 104 13 0;
#P objectname outlet_15;
#P hidden outlet 377 104 13 0;
#P objectname outlet_14;
#P hidden outlet 363 104 13 0;
#P objectname outlet_13;
#P hidden outlet 349 104 13 0;
#P objectname outlet_12;
#P hidden outlet 335 104 13 0;
#P objectname outlet_11;
#P hidden outlet 321 104 13 0;
#P objectname outlet_10;
#P hidden outlet 307 104 13 0;
#P objectname outlet_9;
#P hidden outlet 293 104 13 0;
#P objectname outlet_8;
#P hidden outlet 279 104 13 0;
#P objectname outlet_7;
#P hidden outlet 265 104 13 0;
#P objectname outlet_6;
#P hidden outlet 251 104 13 0;
#P objectname outlet_5;
#P hidden outlet 237 104 13 0;
#P objectname outlet_4;
#P hidden outlet 223 104 13 0;
#P objectname outlet_3;
#P hidden outlet 209 104 13 0;
#P objectname outlet_2;
#P hidden outlet 195 104 13 0;
#P objectname outlet_1;
#P hidden inlet 629 -57 13 0;
#P objectname inlet_32;
#P hidden inlet 615 -57 13 0;
#P objectname inlet_31;
#P hidden inlet 601 -57 13 0;
#P objectname inlet_30;
#P hidden inlet 587 -57 13 0;
#P objectname inlet_29;
#P hidden inlet 573 -57 13 0;
#P objectname inlet_28;
#P hidden inlet 559 -57 13 0;
#P objectname inlet_27;
#P hidden inlet 545 -57 13 0;
#P objectname inlet_26;
#P hidden inlet 531 -57 13 0;
#P objectname inlet_25;
#P hidden inlet 517 -57 13 0;
#P objectname inlet_24;
#P hidden inlet 503 -57 13 0;
#P objectname inlet_23;
#P hidden inlet 489 -57 13 0;
#P objectname inlet_22;
#P hidden inlet 475 -57 13 0;
#P objectname inlet_21;
#P hidden inlet 461 -57 13 0;
#P objectname inlet_20;
#P hidden inlet 447 -57 13 0;
#P objectname inlet_19;
#P hidden inlet 433 -57 13 0;
#P objectname inlet_18;
#P hidden inlet 419 -57 13 0;
#P objectname inlet_17;
#P hidden inlet 405 -57 13 0;
#P objectname inlet_16;
#P hidden inlet 391 -57 13 0;
#P objectname inlet_15;
#P hidden inlet 377 -57 13 0;
#P objectname inlet_14;
#P hidden inlet 363 -57 13 0;
#P objectname inlet_13;
#P hidden inlet 349 -57 13 0;
#P objectname inlet_12;
#P hidden inlet 335 -57 13 0;
#P objectname inlet_11;
#P hidden inlet 321 -57 13 0;
#P objectname inlet_10;
#P hidden inlet 307 -57 13 0;
#P objectname inlet_9;
#P hidden inlet 293 -57 13 0;
#P objectname inlet_8;
#P hidden inlet 279 -57 13 0;
#P objectname inlet_7;
#P hidden inlet 265 -57 13 0;
#P objectname inlet_6;
#P hidden inlet 251 -57 13 0;
#P objectname inlet_5;
#P hidden inlet 237 -57 13 0;
#P objectname inlet_4;
#P hidden inlet 223 -57 13 0;
#P objectname inlet_3;
#P hidden inlet 209 -57 13 0;
#P objectname inlet_2;
#P hidden inlet 195 -57 13 0;
#P objectname inlet_1;
#P bpatcher 345 2 163 16 0 -190 jmod.gui.audio-component.mxt 0 $1;
#P objectname controls;
#P hidden newex 291 289 22 196617 b 1;
#N thispatcher;
#Q end;
#P hidden newobj 291 372 60 196617 thispatcher;
#P hidden newex 291 351 166 196617 js jmod.gui.constructor.js $1;
#P window linecount 2;
#P hidden newex 155 232 487 196617 route MODULE_TITLE ATTRIBUTES BUILD PARAMETERS NEW_PRESETS NEW_PRESETS_START MENU_REBUILD;
#P window linecount 1;
#P hidden newex 155 212 93 196617 r $1_FROM_MHUB;
#P hidden newex 155 366 90 196617 prepend setitem 0;
#P window linecount 3;
#P hidden comment 216 119 404 196617 this first half of the inlets/outlets are the raw unprocessed signal(s) \, the second half are the processed signal(s). The connections are scripted into existence when the number of channels is received from the module hub.;
#P hidden outlet 419 104 13 0;
#P objectname outlet_17;
#P hidden outlet 433 104 13 0;
#P objectname outlet_18;
#P hidden outlet 447 104 13 0;
#P objectname outlet_19;
#P hidden outlet 461 104 13 0;
#P objectname outlet_20;
#P hidden outlet 475 104 13 0;
#P objectname outlet_21;
#P hidden outlet 489 104 13 0;
#P objectname outlet_22;
#P hidden outlet 503 104 13 0;
#P objectname outlet_23;
#P hidden outlet 517 104 13 0;
#P objectname outlet_24;
#P hidden outlet 531 104 13 0;
#P objectname outlet_25;
#P hidden outlet 545 104 13 0;
#P objectname outlet_26;
#P hidden outlet 559 104 13 0;
#P objectname outlet_27;
#P hidden outlet 573 104 13 0;
#P objectname outlet_28;
#P hidden outlet 587 104 13 0;
#P objectname outlet_29;
#P hidden outlet 601 104 13 0;
#P objectname outlet_30;
#P hidden outlet 615 104 13 0;
#P objectname outlet_31;
#P hidden outlet 629 104 13 0;
#P objectname outlet_32;
#P user umenu 11 2 226 196644 3 64 18 0;
#X setrgb 165 165 165 221 221 221 255 255 255 221 221 221 170 170 170 119 119 119 187 187 187;
#X add jamoma;
#P user pictctrl 0 0 510 61 jmod.bg.metal.black.1U.pct 0 0 1 0 24 0 0 0 510 61 2 0 1 1 1 1 1 270;
#P noclick;
#P objectname background;
#P user umenu 17 1 72 196647 1 64 17 1;
#P objectname param_reference;
#P user umenu 0 1 15 196647 1 64 17 1;
#X add "Defeat Signal Meters";
#X add "Clear Signal Meters";
#X add -;
#X add "Load Settings...";
#X add "Save Settings...";
#X add "Restore Default Settings";
#X add -;
#X add "Open Online Reference";
#X add "View Internal Components";
#P objectname menu;
#P hidden connect 24 1 2 0;
#P hidden connect 24 3 0 0;
#P hidden connect 21 0 3 0;
#P hidden connect 87 0 1 0;
#P hidden connect 78 0 1 0;
#P hidden connect 22 0 23 0;
#P hidden connect 23 0 21 0;
#P hidden connect 28 0 83 1;
#P hidden connect 23 2 26 0;
#P hidden connect 26 0 24 0;
#P hidden connect 0 0 24 0;
#P hidden fasten 79 0 24 0 500 342 296 342;
#P hidden fasten 80 0 24 0 432 342 296 342;
#P hidden fasten 23 1 24 0 228 317 296 317;
#P hidden fasten 81 0 24 0 568 342 296 342;
#P hidden connect 24 0 25 0;
#P hidden connect 77 0 78 0;
#P hidden connect 28 0 27 0;
#P hidden fasten 24 2 27 0 374 406 653 406 653 -18 350 -18;
#P hidden connect 29 0 27 1;
#P hidden connect 30 0 27 2;
#P hidden connect 31 0 27 3;
#P hidden connect 23 3 87 0;
#P hidden connect 32 0 27 4;
#P hidden connect 33 0 27 5;
#P hidden connect 34 0 27 6;
#P hidden connect 35 0 27 7;
#P hidden connect 36 0 27 8;
#P hidden connect 37 0 27 9;
#P hidden connect 38 0 27 10;
#P hidden connect 39 0 27 11;
#P hidden connect 40 0 27 12;
#P hidden connect 41 0 27 13;
#P hidden connect 42 0 27 14;
#P hidden connect 43 0 27 15;
#P hidden connect 44 0 27 16;
#P hidden connect 45 0 27 17;
#P hidden connect 46 0 27 18;
#P hidden connect 47 0 27 19;
#P hidden connect 48 0 27 20;
#P hidden connect 23 4 82 0;
#P hidden connect 82 0 80 0;
#P hidden connect 49 0 27 21;
#P hidden connect 50 0 27 22;
#P hidden connect 51 0 27 23;
#P hidden connect 52 0 27 24;
#P hidden connect 53 0 27 25;
#P hidden connect 24 4 76 0;
#P hidden connect 54 0 27 26;
#P hidden connect 28 0 84 0;
#P hidden connect 55 0 27 27;
#P hidden connect 56 0 27 28;
#P hidden connect 57 0 27 29;
#P hidden connect 58 0 27 30;
#P hidden connect 59 0 27 31;
#P hidden connect 23 5 79 0;
#P hidden connect 84 0 85 0;
#P hidden connect 85 0 86 0;
#P hidden connect 23 6 81 0;
#P connect 24 4 88 0;
#P pop;
