max v2;
#N vpatcher 72 96 677 782;
#P origin 0 -1024;
#P window setfont "Sans Serif" 9.;
#P window linecount 1;
#P hidden newex 180 164 47 196617 pcontrol;
#P hidden newex 180 143 78 196617 jmod.pass open;
#P hidden newex 17 607 386 196617 jmod.parameter $0_ /edge_thresh @type msg_float @description "Edge threshold";
#P objectname jmod.parameter.mxt[5];
#P hidden newex 17 587 89 196617 pvar edge_thresh;
#P flonum 164 40 35 9 0. 0 8225 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P objectname edge_thresh;
#P user ubumenu 116 40 48 196617 0 1 1 0;
#X add None;
#X add Sobel;
#X add Prewitt;
#X add Robcross;
#X add Binedge;
#X prefix_set 0 0 <none> 0;
#X pattrmode 1;
#P objectname algorithm;
#P comment 89 42 30 196617 edge;
#P flonum 52 40 35 9 0. 0 8225 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P objectname slide;
#P user radiogroup 34 40 18 16;
#X size 1;
#X offset 16;
#X inactive 0;
#X itemtype 1;
#X flagmode 0;
#X set 1;
#X done;
#P objectname trails;
#P comment 4 42 35 196617 trails;
#P hidden newex 16 545 351 196617 jmod.parameter $0_ /algorithm @type menu @description "Edge detection";
#P objectname jmod.parameter.mxt[4];
#P hidden newex 16 525 77 196617 pvar algorithm;
#P window linecount 2;
#P hidden newex 16 470 213 196617 jmod.parameter $0_ /slide @type msg_float @description "Level of slide for thre trails";
#P objectname jmod.parameter.mxt[3];
#P window linecount 1;
#P hidden newex 16 450 55 196617 pvar slide;
#P hidden newex 16 406 380 196617 jmod.parameter $0_ /trails @type toggle @description "Trails - ghostlike image";
#P objectname jmod.parameter.mxt[2];
#P hidden newex 16 386 59 196617 pvar trails;
#P user radiogroup 163 22 18 16;
#X size 1;
#X offset 16;
#X inactive 0;
#X itemtype 1;
#X flagmode 0;
#X set 1;
#X done;
#P objectname noise;
#P hidden newex 16 342 340 196617 jmod.parameter $0_ /noise @type toggle @description "Noise reduction";
#P objectname jmod.parameter.mxt[1];
#P hidden newex 16 322 57 196617 pvar noise;
#P comment 89 24 78 196617 noise reduction;
#P hidden comment 194 217 75 196617 Analysis output;
#P hidden outlet 403 218 13 0;
#P flonum 53 22 35 9 0. 0 8225 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P objectname threshold;
#P comment 4 24 52 196617 threshold;
#P hidden message 99 86 50 196617 /autodoc;
#B color 3;
#P hidden newex 16 270 352 196617 jmod.parameter $0_ /threshold @type msg_float @description "Threshold";
#P objectname jmod.parameter.mxt;
#P hidden newex 16 250 76 196617 pvar threshold;
#P window linecount 3;
#P hidden newex 396 106 79 196617 pattrstorage @autorestore 0 @savemode 0;
#X client_rect 0 0 640 240;
#X storage_rect 0 0 640 240;
#P objectname jmod.motion%;
#P window linecount 1;
#P hidden comment 417 218 75 196617 VIDEO OUTPUT;
#P hidden outlet 180 217 13 0;
#P hidden inlet 403 169 13 0;
#P hidden comment 418 169 65 196617 VIDEO INPUT;
#P hidden newex 180 189 233 196617 jmod.motion%.alg;
#P window linecount 2;
#P hidden message 459 332 72 196617 \; jmod.init bang;
#B color 3;
#P window linecount 1;
#P hidden comment 15 84 79 196617 command input;
#P window linecount 2;
#P hidden newex 1 109 385 196617 jmod.hub $0_ jmod.motion% $1 @size 1U-half @module_type video @library_type jitter @num_inputs 1 @num_outputs 2 @description "Motion-related analysis";
#P objectname jmod.hub;
#P hidden outlet 1 171 13 0;
#P hidden inlet 1 84 13 0;
#P bpatcher 0 0 256 60 0 0 jmod.gui.mxt 0 $0_;
#P objectname jmod.gui;
#P hidden user com 415 536 285 196617 29;
#K set 0 16748 25976 24942 25701 29216 21093 26227 30061 8266 25966 29541 28265 30067 8296 29812 28730 12079 28021 29545 25441 27751 25971 29813 29285 29486 30057 28462 28271 3328;
#K end;
#P hidden fasten 7 1 1 0 408 210 485 210 485 -6 5 -6;
#P hidden connect 2 0 4 0;
#P hidden fasten 15 0 4 0 104 105 6 105;
#P hidden connect 4 0 3 0;
#P hidden fasten 14 0 13 0 21 295 11 295 11 245 21 245;
#P hidden connect 13 0 14 0;
#P hidden fasten 22 0 21 0 21 367 11 367 11 317 21 317;
#P hidden connect 21 0 22 0;
#P hidden fasten 25 0 24 0 21 431 9 431 9 379 21 379;
#P hidden connect 24 0 25 0;
#P hidden fasten 27 0 26 0 21 504 11 504 11 445 21 445;
#P hidden connect 26 0 27 0;
#P hidden fasten 29 0 28 0 21 570 11 570 11 520 21 520;
#P hidden connect 28 0 29 0;
#P hidden fasten 37 0 36 0 22 632 12 632 12 582 22 582;
#P hidden connect 36 0 37 0;
#P hidden connect 4 1 38 0;
#P hidden connect 38 0 39 0;
#P hidden fasten 38 1 7 0 253 185 185 185;
#P hidden connect 39 0 7 0;
#P hidden connect 7 0 10 0;
#P hidden connect 12 0 4 1;
#P hidden connect 4 2 12 0;
#P hidden connect 9 0 7 1;
#P hidden connect 7 1 18 0;
#P pop;
