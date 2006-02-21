max v2;
#N vpatcher 259 125 782 719;
#P origin 0 -1024;
#P window setfont "Sans Serif" 9.;
#P hidden user com 321 519 146 196617 28;
#K set 0 16748 25976 24942 25701 29216 21093 26227 30061 8266 25966 29541 28265 30067 3432 29812 28730 12079 28021 29545 25441 27751 25971 29813 29285 29486 30057 28462 28271;
#K end;
#P window linecount 1;
#P hidden newex 180 236 177 196617 jmod.oscroute /brightness /contrast;
#P hidden newex 180 171 47 196617 pcontrol;
#P hidden newex 180 148 78 196617 jmod.pass open;
#P hidden newex 18 497 90 196617 pvar monochrome;
#P window linecount 2;
#P hidden newex 18 519 230 196617 jmod.parameter $0_ /monochrome @type toggle @description "Monochrome image - 0 is default";
#P objectname jmod.parameter.mxt[3];
#P window linecount 1;
#P comment 98 42 66 196617 monochrome;
#P user radiogroup 160 40 18 16;
#X size 1;
#X offset 16;
#X inactive 0;
#X itemtype 1;
#X flagmode 0;
#X set 0;
#X done;
#P objectname monochrome;
#P hidden newex 17 417 80 196617 pvar saturation;
#P window linecount 2;
#P hidden newex 17 439 364 196617 jmod.parameter $0_ /saturation @type msg_float @ramp 1 @repetitions 0 @range 0. 4. @clipmode none @description "Saturation of image - 1 is default";
#P objectname jmod.parameter.mxt[2];
#P flonum 56 41 35 9 0 0 8224 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P objectname saturation;
#P flonum 143 22 35 9 0 0 8224 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P objectname contrast;
#P flonum 56 22 35 9 0. 0 8225 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P objectname brightness;
#P window linecount 1;
#P comment 5 42 56 196617 saturation;
#P comment 98 24 48 196617 contrast;
#P comment 4 24 57 196617 brightness;
#P hidden newex 16 329 72 196617 pvar contrast;
#P hidden message 99 86 50 196617 /autodoc;
#B color 3;
#P window linecount 2;
#P hidden newex 16 357 356 196617 jmod.parameter $0_ /contrast @type msg_float @ramp 1 @repetitions 0 @range 0. 4. @clipmode none @description "Contrast of image - 1 is default";
#P objectname jmod.parameter.mxt[1];
#P hidden newex 16 277 365 196617 jmod.parameter $0_ /brightness @type msg_float @ramp 1 @repetitions 0 @range 0. 4. @clipmode none @description "Brightness of image - 1 is default";
#P objectname jmod.parameter.mxt;
#P window linecount 1;
#P hidden newex 16 251 81 196617 pvar brightness;
#P window linecount 3;
#P hidden newex 396 106 79 196617 pattrstorage @autorestore 0 @savemode 0;
#X client_rect 782 465 1336 822;
#X storage_rect 0 0 640 240;
#P objectname jmod.brcosa%;
#P window linecount 1;
#P hidden comment 384 237 75 196617 VIDEO OUTPUT;
#P hidden outlet 369 237 13 0;
#P hidden inlet 369 172 13 0;
#P hidden comment 384 173 65 196617 VIDEO INPUT;
#P hidden newex 180 200 199 196617 jmod.brcosa%.alg;
#P window linecount 2;
#P hidden message 393 474 72 196617 \; jmod.init bang;
#B color 3;
#P window linecount 1;
#P hidden comment 15 84 79 196617 command input;
#P window linecount 2;
#P hidden newex 1 109 385 196617 jmod.hub $0_ jmod.brcosa% $1 @size 1U-half @module_type video @library_type jitter @num_inputs 1 @num_outputs 1 @description "Simple image controls";
#P objectname jmod.hub;
#P hidden outlet 1 171 13 0;
#P hidden inlet 1 84 13 0;
#P bpatcher 0 0 256 60 0 0 jmod.gui.mxt 0 $0_;
#P objectname jmod.gui;
#P hidden fasten 6 1 0 0 374 223 484 223 484 -5 5 -5;
#P hidden fasten 15 0 3 0 104 105 6 105;
#P hidden connect 1 0 3 0;
#P hidden connect 3 0 2 0;
#P hidden fasten 13 0 12 0 21 311 11 311 11 248 21 248;
#P hidden connect 12 0 13 0;
#P hidden fasten 31 0 13 0 185 272 21 272;
#P hidden fasten 14 0 16 0 21 395 10 395 10 325 21 325;
#P hidden fasten 31 1 14 0 268 344 21 344;
#P hidden connect 16 0 14 0;
#P hidden fasten 23 0 24 0 22 474 11 474 11 408 22 408;
#P hidden connect 24 0 23 0;
#P hidden fasten 27 0 28 0 23 554 12 554 12 488 23 488;
#P hidden connect 28 0 27 0;
#P hidden connect 3 1 29 0;
#P hidden connect 29 0 30 0;
#P hidden connect 30 0 6 0;
#P hidden fasten 29 1 6 0 253 193 185 193;
#P hidden connect 6 0 31 0;
#P hidden connect 8 0 6 1;
#P hidden connect 6 1 9 0;
#P hidden connect 11 0 3 1;
#P hidden connect 3 2 11 0;
#P pop;
