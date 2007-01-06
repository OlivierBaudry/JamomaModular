max v2;#N vpatcher 315 44 1227 751;#P origin -52 -169;#P window setfont "Sans Serif" 9.;#P window linecount 1;#P hidden newex 20 370 71 196617 gate 1 0;#P hidden newex 20 326 56 196617 pvar pik 2;#P hidden newex 20 349 50 196617 zl nth 4;#P user jit.pwindow 129 17 61 45 0 1 0 0 1 0;#P objectname pik;#P hidden newex 100 343 78 196617 jcom.pass open;#P hidden newex 100 369 45 196617 pcontrol;#P hidden newex 168 417 49 196617 jcom.out;#P hidden inlet 243 273 13 0;#P hidden inlet 170 274 13 0;#P window linecount 2;#P hidden comment 185 274 65 196617 VIDEO INPUTs;#P window linecount 1;#P hidden newex 170 305 83 196617 jcom.in 2;#P hidden message 103 158 191 196617 /preset/store 1 default \, /preset/write;#B color 3;#P window linecount 2;#P hidden newex 484 592 313 196617 jcom.parameter key/blue @repetitions 0 @type msg_float @range 0. 1. @description "blue level of the chromakey";#P objectname key/blue;#P window linecount 1;#P hidden newex 484 564 40 196617 pvar B;#P window linecount 2;#P hidden newex 484 508 320 196617 jcom.parameter key/green @repetitions 0 @type msg_float @range 0. 1. @description "green level of the chromakey";#P objectname key/green;#P window linecount 1;#P hidden newex 484 486 40 196617 pvar G;#P window linecount 2;#P hidden newex 484 433 310 196617 jcom.parameter key/red @repetitions 0 @type msg_float @range 0. 1. @description "red level of the chromakey";#P objectname key/red;#P window linecount 1;#P hidden newex 484 405 40 196617 pvar R;#P hidden newex 278 561 40 196617 pvar B;#P hidden newex 237 561 40 196617 pvar G;#P hidden newex 196 561 40 196617 pvar R;#P hidden newex 196 487 57 196617 pvar color;#P hidden newex 196 534 93 196617 unpack 0. 0. 0.;#P hidden newex 196 511 77 196617 vexpr $i1/255.;#P flonum 69 57 35 9 0 0 8224 3 255 255 255 221 221 221 222 222 222 0 0 0;#P objectname minkey;#P toggle 70 94 15 0;#P objectname alphaignore;#P flonum 228 72 28 9 0 0 8224 3 255 255 255 221 221 221 222 222 222 0 0 0;#P objectname B;#P flonum 183 72 29 9 0 0 8224 3 255 255 255 221 221 221 222 222 222 0 0 0;#P objectname G;#P flonum 141 72 29 9 0 0 8224 3 255 255 255 221 221 221 222 222 222 0 0 0;#P objectname R;#P comment 216 74 13 196617 B;#B frgb 255 255 255;#P comment 172 74 13 196617 G;#B frgb 255 255 255;#P comment 128 74 13 196617 R;#B frgb 255 255 255;#P comment 1 94 65 196617 Alpha :;#B frgb 255 255 255;#P comment 2 76 65 196617 Maximum :;#B frgb 255 255 255;#P flonum 69 75 35 9 0 0 8224 3 255 255 255 221 221 221 222 222 222 0 0 0;#P objectname maxkey;#P comment 1 59 65 196617 Minimum :;#B frgb 255 255 255;#P comment 1 42 65 196617 Fade :;#B frgb 255 255 255;#P flonum 68 41 35 9 0 0 8224 3 255 255 255 221 221 221 222 222 222 0 0 0;#P objectname fade;#P hidden newex 484 337 85 196617 pvar alphaignore;#P window linecount 2;#P hidden newex 484 357 275 196617 jcom.parameter alpha @repetitions 0 @type msg_toggle @range 0. 1. @description "alpha of the chromakey";#P objectname alpha;#P window linecount 1;#P hidden newex 484 270 69 196617 pvar maxkey;#P window linecount 2;#P hidden newex 484 290 311 196617 jcom.parameter maxkey @repetitions 0 @type msg_float @range 0. 10. @description "maxkey of the chromakey";#P objectname maxkey[1];#P window linecount 1;#P hidden newex 484 201 66 196617 pvar minkey;#P window linecount 2;#P hidden newex 484 221 308 196617 jcom.parameter minkey @repetitions 0 @type msg_float @range 0. 10. @description "minkey of the chromakey";#P objectname minkey[1];#P window linecount 1;#P hidden newex 484 132 53 196617 pvar fade;#P window linecount 2;#P hidden newex 484 152 295 196617 jcom.parameter fade @repetitions 0 @type msg_float @range 0. 10. @description "fade of the chromakey";#P objectname fade[1];#P user swatch 126 87 129 33;#P objectname color;#P user suckah 129 20 62 41;#P hidden message 360 287 65 196617 \; max refresh;#P window linecount 1;#P comment 2 25 65 196617 Tolerance :;#B frgb 255 255 255;#P hidden newex 484 62 46 196617 pvar tol;#P window linecount 2;#P hidden newex 484 84 314 196617 jcom.parameter tolerance @repetitions 0 @type msg_float @range 0. 1. @description "Tolerance of the chromakey";#P objectname tolerance;#P window linecount 1;#P hidden message 114 176 125 196617 /documentation/generate;#B color 3;#P window linecount 3;#P hidden newex 8 204 326 196617 jcom.hub jmod.chromakey% @size 2U-half @module_type video @algorithm_type jitter @description "Simple 2-source chromakey : Keying based on chromatic distance";#P objectname jcom.hub;#P window linecount 1;#P hidden comment 183 438 75 196617 VIDEO OUTPUT;#P hidden outlet 168 438 13 0;#P hidden newex 168 395 109 196617 jalg.chromakey%.mxt;#P window linecount 2;#P hidden message 360 252 72 196617 \; jcom.init bang;#P window linecount 1;#P hidden comment 22 173 79 196617 command input;#P hidden outlet 8 260 13 0;#P hidden inlet 8 173 13 0;#P flonum 69 24 35 9 0 0 8224 3 255 255 255 221 221 221 222 222 222 0 0 0;#P objectname tol;#P bpatcher 0 0 255 119 0 0 jcom.gui.mxt 0 $0_;#P objectname jcom.gui.1Uh.v.mxb;#P hidden fasten 51 0 9 0 108 195 13 195;#P hidden fasten 10 0 9 0 119 195 13 195;#P hidden connect 2 0 9 0;#P hidden connect 9 0 3 0;#P hidden fasten 62 0 61 0 25 393 8 393 8 316 25 316;#P hidden connect 61 1 60 0;#P hidden connect 60 0 62 0;#P hidden fasten 54 0 62 1 175 296 86 296;#P hidden connect 52 2 58 0;#P hidden connect 58 0 57 0;#P hidden fasten 15 0 16 0 134 85 131 85;#P hidden connect 57 0 6 0;#P hidden connect 58 1 6 0;#P hidden connect 6 0 56 0;#P hidden connect 56 0 7 0;#P hidden connect 54 0 52 0;#P hidden connect 41 0 39 0;#P hidden connect 39 0 40 0;#P hidden connect 40 0 42 0;#P hidden connect 52 0 6 1;#P hidden connect 40 1 43 0;#P hidden connect 55 0 52 1;#P hidden connect 52 1 6 2;#P hidden connect 40 2 44 0;#P hidden fasten 11 0 12 0 489 119 477 119 477 57 489 57;#P hidden connect 12 0 11 0;#P hidden fasten 17 0 18 0 489 185 477 185 477 127 489 127;#P hidden connect 18 0 17 0;#P hidden fasten 19 0 20 0 489 254 477 254 477 196 489 196;#P hidden connect 20 0 19 0;#P hidden fasten 21 0 22 0 489 323 477 323 477 265 489 265;#P hidden connect 22 0 21 0;#P hidden fasten 23 0 24 0 489 390 477 390 477 332 489 332;#P hidden connect 24 0 23 0;#P hidden fasten 46 0 45 0 489 467 473 467 473 401 489 401;#P hidden connect 45 0 46 0;#P hidden fasten 48 0 47 0 489 548 474 548 474 482 489 482;#P hidden connect 47 0 48 0;#P hidden fasten 50 0 49 0 489 626 473 626 473 560 489 560;#P hidden connect 49 0 50 0;#P pop;