max v2;#N vpatcher 189 89 1269 588;#P origin 0 -86;#P window setfont "Sans Serif" 9.;#P hidden newex 415 261 59 196617 pvar Reset;#P hidden newex 415 284 482 196617 jcom.message random_reset @type msg_none @description "reset boids randomly inside the flyrect";#P objectname jcom.parameter[3];#P user jsui 134 41 25 15 1 0 0 jsui_textbutton.js reset;#P objectname Reset;#P hidden newex 28 427 57 196617 pvar Mode;#P hidden newex 29 449 331 196617 jcom.parameter mode @type msg_int @description "Turn boids on/off";#P objectname mode;#P window setfont Verdana 9.;#P user ubumenu 106 20 61 472055817 0 1 1 0;#X add new(xyz);#X add new(xyz)/old(xyz);#X add new(xyz)/old(xyz)/speed/azi/ele;#X prefix_set 0 0 <none> 0;#X pattrmode 1;#P objectname Mode;#P window setfont "Sans Serif" 9.;#P newex 121 174 154 196617 jcom.oscroute /open_inspector;#P newex 43 218 44 196617 pcontrol;#P newex 43 196 41 196617 t open;#N vpatcher 831 140 1119 554;#P origin 12 23;#P window setfont "Sans Serif" 9.;#P flonum 1 82 28 9 0. 0 8225 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname Minspeed;#P flonum 1 101 28 9 0. 0 8225 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname Maxspeed;#P window linecount 1;#P comment 32 391 27 196617 back;#B frgb 181 181 181;#P comment 32 373 32 196617 front;#B frgb 181 181 181;#P comment 32 335 32 196617 right;#B frgb 181 181 181;#P comment 32 353 42 196617 bottom;#B frgb 181 181 181;#P comment 32 316 22 196617 top;#B frgb 181 181 181;#P flonum 1 278 28 9 0. 0 8225 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname Prefdist;#P flonum 1 261 28 9 0. 0 8225 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname Accel;#P flonum 1 243 28 9 0. 0 8225 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname Inertia;#P flonum 1 226 28 9 0. 0 8225 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname Speed;#P flonum 1 210 28 9 0. 0 8225 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname Edgedist;#P flonum 1 193 28 9 0. 0 8225 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname Repel;#P flonum 1 175 28 9 0. 0 8225 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname Avoid;#P flonum 1 155 28 9 0. 0 8225 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname Match;#P flonum 1 137 28 9 0. 0 8225 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname Attract;#P flonum 1 65 28 9 0. 0 8225 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname Neighbors;#P flonum 1 119 28 9 0. 0 8225 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname Center;#P window linecount 0;#P hidden newex 148 451 50 196617 pvar bb6;#P hidden newex 130 472 50 196617 pvar bb5;#P hidden newex 94 451 50 196617 pvar bb4;#P flonum 2 391 29 9 0 0 8224 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname bb6;#P flonum 2 373 29 9 0 0 8224 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname bb5;#P flonum 2 353 29 9 0 0 8224 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname bb4;#P flonum 2 335 29 9 0 0 8224 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname bb3;#P flonum 2 316 29 9 0 0 8224 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname bb2;#P hidden newex 78 473 50 196617 pvar bb3;#P hidden newex 38 451 50 196617 pvar bb2;#P hidden newex 26 474 50 196617 pvar bb1;#P hidden newex 28 497 144 196617 jcom.list2parameter.mxt 6;#P window linecount 3;#P hidden newex 178 487 313 196617 jcom.parameter flyrect @type msg_list @ramp linear.sched @repetitions 1 @range -1. 1. @clipmode both @description "bounding box (walls) in which to fly (left/top/right/bottom/front/back)";#P objectname flyrect;#P flonum 2 299 29 9 0 0 8224 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname bb1;#P window linecount 2;#P comment 74 332 104 196617 bounding box (walls) in which to fly;#B frgb 181 181 181;#P window linecount 1;#P newex 803 727 71 196617 pvar Prefdist;#P window linecount 2;#P newex 802 746 329 196617 jcom.parameter prefdist @repetitions 0 @type msg_float @range 0. 100. @clipmode low @description "preferred distance from neighbors";#P objectname prefdist;#P window linecount 1;#P newex 460 727 59 196617 pvar Accel;#P window linecount 2;#P newex 460 747 317 196617 jcom.parameter acceleration @repetitions 0 @type msg_float @range 0. 100. @clipmode low @description "speed of acceleration";#P objectname acceleration;#P window linecount 1;#P newex 458 664 64 196617 pvar Inertia;#P window linecount 2;#P newex 458 684 335 196617 jcom.parameter inertia @repetitions 0 @type msg_float @range 0. 100. @clipmode low @description "willingness to change speed and direction";#P objectname inertia;#P window linecount 1;#P newex 458 601 60 196617 pvar Speed;#P window linecount 2;#P newex 458 621 282 196617 jcom.parameter speed @repetitions 0 @type msg_float @range 0. 100. @clipmode low @description "overall speed";#P objectname speed;#P window linecount 1;#P newex 458 540 71 196617 pvar Edgedist;#P window linecount 2;#P newex 458 560 342 196617 jcom.parameter edgedist @repetitions 0 @type msg_float @range 0. 100. @clipmode low @description "distance of vision for avoiding wall edges";#P objectname edgedist;#P window linecount 1;#P newex 544 477 58 196617 pvar Repel;#P window linecount 2;#P newex 544 497 326 196617 jcom.parameter repel @repetitions 0 @type msg_float @range 0. 100. @clipmode low @description "strengh of wall avoidance instinct";#P objectname repel;#P window linecount 1;#P newex 544 415 60 196617 pvar Avoid;#P window linecount 2;#P newex 544 435 329 196617 jcom.parameter avoid @repetitions 0 @type msg_float @range 0. 100. @clipmode low @description "strength of neighbor avoidance instinct";#P objectname avoid;#P window linecount 1;#P comment 32 137 170 196617 strength of attraction to 'attractpt';#B frgb 181 181 181;#P comment 32 119 142 196617 strength of centering instinct;#B frgb 181 181 181;#P comment 32 100 149 196617 maximum speed of speed range;#B frgb 181 181 181;#P comment 34 83 146 196617 minimum speed of speed range;#B frgb 181 181 181;#P comment 32 65 249 196617 number of neighbors each boid consults when flocking;#B frgb 181 181 181;#P newex 458 349 61 196617 pvar Match;#P window linecount 2;#P newex 458 369 349 196617 jcom.parameter match @repetitions 0 @type msg_float @range 0. 100. @clipmode low @description "strength of neighbor speed matching instinct";#P objectname match;#P window linecount 1;#P newex 458 282 68 196617 pvar Attract;#P window linecount 2;#P newex 458 302 337 196617 jcom.parameter attract @repetitions 0 @type msg_float @range 0. 100. @clipmode low @description "strength of attraction to 'attractpoint'";#P objectname attract;#P window linecount 1;#P newex 458 218 64 196617 pvar Center;#P window linecount 2;#P newex 458 238 310 196617 jcom.parameter center @repetitions 0 @type msg_float @range 0. 100. @clipmode low @description "strength of centering instinct";#P objectname center;#P window linecount 1;#P newex 458 156 75 196617 pvar Minspeed;#P window linecount 2;#P newex 458 176 322 196617 jcom.parameter minspeed @repetitions 0 @type msg_float @range 0. 100. @clipmode low @description "minimum speed of speed range";#P objectname minspeed;#P window linecount 1;#P newex 458 95 78 196617 pvar Maxspeed;#P window linecount 2;#P newex 458 115 325 196617 jcom.parameter maxspeed @repetitions 0 @type msg_float @range 0. 100. @clipmode low @description "maximum speed of speed range";#P objectname maxspeed;#P window linecount 1;#P newex 458 33 78 196617 pvar Neighbors;#P window linecount 2;#P newex 458 53 389 196617 jcom.parameter neighbors @repetitions 0 @type msg_float @range 0. 100. @clipmode low @description "number of neighbors each boid consults when flocking";#P objectname neighbors;#P window linecount 1;#P hidden newex 55 616 167 196617 loadmess patcher Boids3d-settings;#P hidden newex 44 594 40 196617 t front;#P hidden newex 44 569 151 196617 jcom.oscroute /open_inspector;#P hidden inlet 44 542 15 0;#N thispatcher;#Q end;#P hidden newobj 55 636 61 196617 thispatcher;#P comment 32 278 165 196617 preferred distance from neighbors;#B frgb 181 181 181;#P comment 32 261 105 196617 speed of acceleration;#B frgb 181 181 181;#P comment 32 243 194 196617 willingness to change speed and direction;#B frgb 181 181 181;#P comment 32 226 70 196617 overall speed;#B frgb 181 181 181;#P comment 32 210 196 196617 distance of vision for avoiding wall edges;#B frgb 181 181 181;#P comment 32 193 162 196617 strengh of wall avoidance instinct;#B frgb 181 181 181;#P comment 32 175 185 196617 strength of neighbor avoidance instinct;#B frgb 181 181 181;#P comment 32 155 209 196617 strength of neighbor speed matching instinct;#B frgb 181 181 181;#P hidden newex 15 757 138 196617 loadmess patcher Colorblobs;#P hidden newex 4 735 40 196617 t front;#P hidden newex 4 710 151 196617 jcom.oscroute /open_inspector;#P hidden inlet 4 683 15 0;#N thispatcher;#Q end;#P hidden newobj 15 777 61 196617 thispatcher;#P hidden message 207 230 214 196617 window size 100 100 400 615 \, window exec;#N thispatcher;#Q window flags nogrow close zoom nofloat;#Q window size 831 140 1119 554;#Q window title;#Q window exec;#Q savewindow 1;#Q end;#P hidden newobj 357 292 59 196617 thispatcher;#P hidden newex 208 356 88 196617 bgcolor 80 80 80;#P hidden message 94 372 239 196617 window flags nogrow \, savewindow 1 \, window exec;#P hidden message 95 393 158 196617 window flags grow \, window exec;#P window linecount 0;#P comment 32 299 100 196617 left;#B frgb 181 181 181;#P window setfont "Sans Serif" 18.;#P comment 48 22 211 196626 extended settings;#B frgb 181 181 181;#P connect 8 0 9 0;#P hidden connect 9 0 10 0;#P hidden connect 10 0 7 0;#P connect 11 0 7 0;#P hidden fasten 59 0 60 0 33 520 21 520 21 471 31 471;#P hidden connect 60 0 59 0;#P hidden fasten 59 1 61 0 46 525 14 525 14 449 43 449;#P hidden connect 61 0 59 1;#P hidden fasten 21 0 22 0 49 563 49 563;#P hidden connect 22 0 23 0;#P hidden connect 62 0 59 2;#P hidden connect 23 0 20 0;#P connect 24 0 20 0;#P hidden connect 68 0 59 3;#P hidden fasten 59 2 62 0 59 531 11 531 11 438 83 438;#P hidden connect 69 0 59 4;#P hidden connect 70 0 59 5;#P hidden fasten 59 3 68 0 72 534 8 534 8 432 99 432;#P hidden fasten 59 4 69 0 85 540 4 540 4 426 135 426;#P hidden fasten 59 5 70 0 98 545 3 545 3 418 156 418 154 449;#P hidden connect 58 0 59 10;#P hidden connect 59 10 58 0;#P hidden connect 6 0 5 0;#P hidden connect 3 0 5 0;#P hidden connect 2 0 5 0;#P fasten 25 0 26 0 463 86 451 86 451 28 463 28;#P connect 26 0 25 0;#P fasten 27 0 28 0 463 148 451 148 451 90 463 90;#P connect 28 0 27 0;#P fasten 29 0 30 0 463 209 451 209 451 151 463 151;#P connect 30 0 29 0;#P fasten 31 0 32 0 463 271 451 271 451 213 463 213;#P connect 32 0 31 0;#P fasten 33 0 34 0 463 335 451 335 451 277 463 277;#P connect 34 0 33 0;#P fasten 35 0 36 0 463 402 451 402 451 344 463 344;#P connect 36 0 35 0;#P fasten 46 0 47 0 463 593 451 593 451 535 463 535;#P connect 47 0 46 0;#P fasten 48 0 49 0 463 654 451 654 451 596 463 596;#P connect 49 0 48 0;#P fasten 50 0 51 0 463 717 451 717 451 659 463 659;#P connect 51 0 50 0;#P fasten 52 0 53 0 465 780 453 780 453 722 465 722;#P connect 53 0 52 0;#P fasten 42 0 43 0 549 468 537 468 537 410 549 410;#P connect 43 0 42 0;#P fasten 44 0 45 0 549 530 537 530 537 472 549 472;#P connect 45 0 44 0;#P connect 55 0 54 0;#P fasten 54 0 55 0 807 780 796 780 796 722 808 722;#P pop;#P newobj 43 239 67 196617 p inspector;#B color 4;#P objectname inspector;#P flonum 224 43 30 9 0 0 8224 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname PosZ;#P hidden newex 498 189 55 196617 pvar PosZ;#P hidden newex 445 167 56 196617 pvar PosY;#P hidden newex 435 190 56 196617 pvar PosX;#P hidden newex 432 209 144 196617 jcom.list2parameter.mxt 3;#P window linecount 2;#P hidden newex 589 203 464 196617 jcom.parameter attractpoint/xyz @type msg_list @ramp linear.sched @repetitions 1 @range -1. 1. @clipmode none @description "Current position of the point of attraction in xyz-coordinates";#P objectname attractpoint/xyz;#P window linecount 1;#P comment 173 30 72 196617 Center X/Y/Z;#B frgb 181 181 181;#P flonum 195 43 30 9 0 0 8224 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname PosY;#P flonum 168 43 28 9 0 0 8224 3 181 181 181 221 221 221 222 222 222 0 0 0;#P objectname PosX;#P hidden newex 691 106 65 196617 pvar ard_on;#P hidden newex 691 128 333 196617 jcom.parameter on @type msg_toggle @description "Turn boids on/off";#P objectname on;#P user jsui 107 41 25 14 1 0 0 jcom.jsui_texttoggle.js off on 204 204 204 0 0 0 121 255 15;#P objectname ard_on;#P message 49 71 191 196617 /preset/store 1 default \, /preset/write;#B color 3;#P newex 119 154 43 196617 jcom.in;#P comment 0 42 78 196617 update rate [Hz];#B frgb 149 149 149;#P newex 119 220 45 196617 pcontrol;#P newex 119 200 78 196617 jcom.pass open;#P hidden newex 419 95 83 196617 pvar Updaterate;#P number 77 41 28 9 0 0 8225 3 181 181 181 221 221 221 255 255 255 0 0 0;#P objectname Updaterate;#P window linecount 2;#P hidden newex 419 113 263 196617 jcom.parameter updaterate @type msg_int @range 0 50 @clipmode low @description "updaterate of the flock";#P objectname updaterate;#P message 23 363 65 196617 \; max refresh;#P window linecount 1;#P message 185 88 31 196617 /init;#P newex 119 291 85 196617 jalg.boids3d.mxt;#B color 4;#P comment 0 22 77 196617 Number of boids;#B frgb 149 149 149;#P number 77 20 27 9 0 0 8225 3 181 181 181 221 221 221 255 255 255 0 0 0;#P objectname Number;#P hidden newex 419 31 68 196617 pvar Number;#P window linecount 2;#P newex 16 113 334 196617 jcom.hub jmod.boids3d @size 1U-half @module_type control @inspector 1 @description "Jamoma implementation of Boids3D by Eric L. Singer";#P objectname jcom.hub;#P inlet 16 89 13 0;#P outlet 16 315 13 0;#P window linecount 1;#P hidden newex 419 51 539 196617 jcom.parameter number @repetitions 0 @type msg_int @range 0 32 @clipmode low @description "number of boids";#P objectname number;#P message 224 277 153 196617 /updaterate 33;#P newex 225 257 61 196617 prepend set;#P message 56 88 125 196617 /documentation/generate;#B color 3;#P bpatcher 0 -1 256 62 0 0 jcom.gui.mxt 0 $0_;#P objectname jcom.gui.audio-component.mxt;#P fasten 12 0 7 0 190 109 21 109;#P connect 6 0 7 0;#P fasten 1 0 7 0 61 109 21 109;#P fasten 21 0 7 0 54 109 21 109;#P connect 7 0 5 0;#P hidden fasten 39 0 40 0 34 472 21 472 21 419 33 419;#P hidden connect 40 0 39 0;#P fasten 37 0 35 0 126 193 48 193;#P connect 35 0 36 0;#P connect 36 0 34 0;#P fasten 37 1 17 0 270 197 124 197;#P connect 17 0 18 0;#P connect 18 0 11 0;#P fasten 17 1 11 0 192 268 124 268;#P connect 20 0 37 0;#P connect 2 0 3 0;#P fasten 17 1 2 0 192 248 230 248;#P connect 43 0 42 0;#P hidden fasten 4 0 8 0 424 74 412 74 412 26 424 26;#P hidden connect 8 0 4 0;#P hidden fasten 14 0 16 0 424 146 412 146 412 88 424 88;#P hidden connect 16 0 14 0;#P hidden connect 30 0 29 0;#P hidden fasten 29 0 30 0 437 233 428 233 428 184 440 184;#P hidden fasten 29 1 31 0 450 238 421 238 421 162 450 162;#P hidden connect 31 0 29 1;#P hidden connect 32 0 29 2;#P hidden fasten 29 2 32 0 463 242 415 242 415 154 503 154;#P hidden connect 28 0 29 10;#P hidden connect 29 10 28 0;#P hidden fasten 23 0 24 0 696 151 687 151 687 100 696 100;#P hidden connect 24 0 23 0;#P pop;