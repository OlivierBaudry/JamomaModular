max v2;#N vpatcher 137 168 919 816;#P origin 0 -10;#P window setfont "Sans Serif" 9.;#N vpatcher 20 74 620 474;#P window setfont "Sans Serif" 9.;#P window linecount 1;#P comment 80 272 455 196617 We can not actually use jcom.return here \, as it would produce a feedback loop \, talking to itself.;#P message 80 86 152 196617 name jcom.remote.module.from;#P message 95 108 170 196617 name "that deaf dumb and blind kid";#P newex 80 52 41 196617 sel 1 0;#P newex 80 193 86 196617 prepend /remote;#P newex 106 244 373 196617 jcom.return remote @description "Reports all changes of values in all modules";#P newex 80 150 206 196617 jcom.receive "that deaf dumb and blind kid";#P window linecount 2;#P comment 123 50 191 196617 if we are not listening \, jcom.receive is set to another argument to save cpu;#P inlet 80 32 15 0;#P outlet 80 245 15 0;#P connect 1 0 6 0;#P connect 6 0 8 0;#P lcolor 1;#P connect 7 0 3 0;#P connect 8 0 3 0;#P connect 3 0 5 0;#P connect 5 0 0 0;#P connect 6 1 7 0;#P lcolor 1;#P pop;#P newobj 53 529 43 196617 p listen;#P outlet 53 577 15 0;#P newex 620 196 57 196617 route read;#B color 12;#P window linecount 2;#P comment 581 436 185 196617 <- events are sent remotely to the target parameter in the target module.;#P window linecount 1;#P newex 418 433 161 196617 jcom.send jcom.remote.module.to;#N vpatcher 33 59 633 459;#P window setfont "Sans Serif" 9.;#P window linecount 2;#P comment 322 309 234 196617 This is done by stopping the delay in the [WAIT_or_pass_on] subpatch.;#P comment 322 280 234 196617 If a new cue is triggered \, we have to make sure that any current cue on WAIT is cancelled.;#P window linecount 1;#P comment 322 32 135 196617 WAIT (pause/resume);#P comment 322 125 213 196617 WAIT will cause uzi to pause and resume;#P newex 50 60 240 196617 t s b;#P newex 80 258 64 196617 prepend line;#P newex 80 229 81 196617 expr $i1+$i2-1;#P newex 50 196 40 196617 uzi;#P newex 50 121 81 196617 unpack 0 0;#P newex 50 166 81 196617 expr $i2-$i1+1;#P window setfont "Sans Serif" 18.;#N coll $0_cues 1;#P newobj 50 86 140 196626 coll $0_cues 1;#P inlet 50 30 15 0;#P inlet 303 30 15 0;#P outlet 80 280 15 0;#P outlet 280 278 15 0;#P window setfont "Sans Serif" 9.;#P window linecount 2;#P comment 322 81 181 196617 Use Uzi to dump the lines of the script that belong to the desired cue.;#P window linecount 0;#P comment 68 32 135 196617 Cue that we want to trigger;#P comment 79 303 118 196617 poll lines from [text];#P connect 6 0 13 0;#P connect 13 0 7 0;#P connect 7 0 9 0;#P connect 9 0 8 0;#P connect 8 0 10 0;#P fasten 5 0 10 0 308 189 55 189;#P connect 10 2 11 0;#P connect 11 0 12 0;#P connect 12 0 4 0;#P connect 9 1 8 1;#P fasten 9 0 11 1 55 152 156 152;#P connect 13 1 3 0;#P pop;#P newobj 418 192 74 196617 p trigger_cue;#P newex 393 524 336 196617 jcom.return cues @description "Returns a list of all cues in the script.";#N vpatcher 60 72 913 742;#P window setfont "Sans Serif" 9.;#P newex 158 586 80 196617 s $1_set_menu;#P window linecount 1;#P comment 546 214 29 196617 <-;#P comment 244 470 29 196617 ->;#P comment 134 307 29 196617 ->;#P window linecount 0;#P newex 265 211 51 196617 zl slice 1;#P window linecount 6;#P comment 173 468 72 196617 internally store cue names and what line they start and end at;#P window linecount 3;#P comment 30 354 114 196617 the list has to be reversed to start with the first cue;#P window linecount 2;#P comment 649 606 84 196617 return list of cues;#P comment 649 110 108 196617 bang when new text file has been read;#P window linecount 1;#P comment 413 522 117 196617 connect to text inlet;#P comment 139 49 413 196617 - the names of all cues.;#P comment 139 62 412 196617 - what line they start and end at.;#P outlet 649 584 15 0;#P comment 413 509 100 196617 grab from text;#P comment 444 118 100 196617 text outlet 3;#P comment 365 118 100 196617 text outlet 2;#P newex 158 352 37 196617 zl rev;#P newex 158 305 67 196617 zl group 256;#P inlet 649 145 15 0;#P window linecount 0;#P newex 311 269 20 196617 t b;#P newex 311 314 27 196617 i;#P newex 476 261 27 196617 t i i;#P newex 305 389 27 196617 - 1;#P newex 277 367 66 196617 unpack s 0 0;#P newex 476 211 57 196617 expr $i2-$i1+1;#P newex 446 170 105 196617 t i i i;#N coll $0_cues 1;#P newobj 265 466 77 196617 coll $0_cues 1;#P newex 265 425 72 196617 prepend store;#P window linecount 1;#P newex 265 167 51 196617 route set;#P newex 265 342 56 196617 pack s 0 0;#P newex 265 189 54 196617 route CUE;#P newex 476 423 64 196617 prepend line;#P newex 446 191 40 196617 uzi;#P newex 391 426 69 196617 t query clear;#P inlet 446 145 15 0;#P inlet 367 145 15 0;#P inlet 265 145 15 0;#P outlet 391 511 15 0;#P comment 263 118 100 196617 text outlet 1;#P comment 139 36 414 196617 When the cue script is loaded \, it is scanned by this subpatch in order to get:;#P window linecount 0;#P comment 271 99 238 196617 -------- connect to text outlets --------;#P comment 568 206 83 196617 the text file is scanned from end to beginning;#P comment 30 297 114 196617 all cue names are stored here \, and dumped at the end.;#P comment 144 214 119 196617 discard comments -->;#P comment 134 354 29 196617 ->;#P connect 40 0 27 0;#P connect 12 1 27 0;#P connect 27 0 28 0;#P connect 28 0 44 0;#P connect 8 0 16 0;#P connect 16 0 14 0;#P connect 14 0 40 0;#P connect 40 0 15 0;#P connect 15 0 17 0;#P fasten 11 1 18 0 455 454 270 454;#P connect 17 0 18 0;#P connect 15 0 21 0;#P fasten 23 1 15 1 498 294 293 294;#P connect 21 1 22 0;#P connect 40 0 25 0;#P connect 25 0 24 0;#P connect 24 0 15 2;#P fasten 19 2 24 1 545 307 333 307;#P fasten 22 0 24 1 310 411 354 411 354 309 333 309;#P fasten 26 0 11 0 654 392 396 392;#P fasten 13 0 7 0 481 486 396 486;#P connect 11 0 7 0;#P connect 10 0 19 0;#P connect 19 0 12 0;#P connect 12 2 20 0;#P connect 20 0 23 0;#P connect 23 0 13 0;#P connect 19 1 20 1;#P fasten 28 0 32 0 163 565 654 565;#P pop;#P newobj 342 338 61 196617 p find_cues;#P newex 342 298 63 196617 grab 3;#N vpatcher 468 122 1036 516;#P window setfont "Sans Serif" 9.;#P window linecount 1;#P newex 260 298 64 196617 fromsymbol;#P newex 232 276 38 196617 gate 2;#P newex 277 247 27 196617 + 1;#P newex 277 225 31 196617 == 1;#P newex 260 179 27 196617 t l l;#P newex 277 203 34 196617 zl len;#P window linecount 0;#P newex 218 157 66 196617 regexp #.*;#P newex 201 83 79 196617 regexp (.*)#.*;#P newex 335 121 50 196617 s display;#P window linecount 1;#P comment 332 85 209 196617 filter out comments (text starting with a #);#P newex 252 121 66 196617 regexp #.*;#P newex 201 54 50 196617 route set;#P newex 232 328 75 196617 route bang CUE;#P inlet 201 30 15 0;#P outlet 296 354 15 0;#P window linecount 0;#P comment 221 30 100 196617 from text;#P comment 7 57 186 196617 All lines from text starts of with "set" \, so we have to get rid of that;#P connect 3 0 5 0;#P connect 5 0 9 0;#P connect 9 1 10 0;#P connect 6 3 10 0;#P connect 14 0 15 0;#P connect 16 0 4 0;#P connect 15 0 4 0;#P connect 9 3 6 0;#P connect 10 3 12 0;#P connect 12 0 15 1;#P connect 15 1 16 0;#P connect 12 1 11 0;#P connect 11 0 13 0;#P connect 13 0 14 0;#P connect 4 2 2 0;#P connect 9 1 8 0;#P connect 3 0 8 0;#P pop;#P newobj 418 341 58 196617 p cue_gate;#N vpatcher 33 59 756 447;#P window setfont "Sans Serif" 9.;#P window linecount 2;#P comment 97 300 74 196617 cue events passed through;#P window linecount 0;#P newex 397 129 36 196617 t stop;#P window linecount 2;#P newex 210 237 43 196617 t resume;#P window linecount 1;#P newex 210 214 30 196617 defer;#P newex 210 192 33 196617 del 0;#P newex 210 160 56 196617 t b i pause;#P newex 210 118 98 196617 route WAIT;#P inlet 210 65 15 0;#P inlet 397 84 15 0;#P outlet 78 300 15 0;#P outlet 210 300 15 0;#P window linecount 0;#P comment 207 34 265 196617 If a WAIT message is received \, uzi is paused for a while. Other messages are passed through to the right outlet.;#P comment 227 300 35 196617 to uzi;#P comment 421 83 232 196617 If a new cue is triggered \, we have to make sure that the previous one is cancelled.;#P fasten 7 1 4 0 303 147 83 147;#P connect 6 0 7 0;#P connect 7 0 8 0;#P fasten 12 0 9 0 402 187 215 187;#P connect 8 0 9 0;#P connect 9 0 10 0;#P connect 10 0 11 0;#P fasten 8 2 3 0 261 282 215 282;#P connect 11 0 3 0;#P connect 8 1 9 1;#P connect 5 0 12 0;#P pop;#P newobj 418 373 100 196617 p WAIT_or_pass_on;#P newex 507 223 123 196617 jcom.filesaver.mxt TEXT;#P newex 53 47 108 196617 jcom.oscroute /listen;#P newex 329 106 37 196617 t open;#N vpatcher 525 121 1145 584;#P window setfont "Sans Serif" 9.;#P window linecount 1;#P message 341 130 152 196617 name jcom.remote.module.from;#P message 356 152 170 196617 name "that deaf dumb and blind kid";#P newex 341 96 41 196617 sel 1 0;#P newex 341 194 206 196617 jcom.receive "that deaf dumb and blind kid";#P window linecount 0;#P newex 60 116 49 196617 deferlow;#N vpatcher 10 59 1017 607;#P window setfont "Sans Serif" 9.;#P newex 93 102 40 196617 t b s b;#P window linecount 3;#P comment 286 196 208 196617 This stops jcom.receive from listening if we are not currently requesting the names of all modules.;#P window linecount 1;#P message 123 217 152 196617 name jcom.remote.module.from;#B color 5;#P message 93 198 170 196617 name "that deaf dumb and blind kid";#B color 5;#P newex 51 469 50 196617 t cr l tab;#P newex 51 437 113 196617 zl join;#P newex 113 369 51 196617 zl slice 1;#P newex 51 409 72 196617 sprintf %s%s;#P newex 93 340 27 196617 t b l;#P newex 612 159 35 196617 t cr s;#P newex 93 50 40 196617 t s s s;#P newex 51 376 36 196617 zl reg;#P newex 93 312 160 196617 jcom.oscroute /parameter_value;#P newex 637 184 89 196617 prepend # Module;#P newex 93 243 206 196617 jcom.receive "that deaf dumb and blind kid";#B color 5;#P newex 93 283 70 196617 osc-route /*;#P window linecount 2;#P newex 108 154 112 196617 jcom.send jcom.remote.module.to;#B color 5;#P window linecount 1;#P newex 108 128 175 196617 sprintf %s/parameter_values/dump;#P inlet 93 30 15 0;#P outlet 51 529 15 0;#P window linecount 0;#P comment 625 126 184 196617 This part introduce a comment to mark the beginning of a new module;#P connect 12 0 9 0;#P connect 9 0 13 0;#P connect 13 0 15 0;#P connect 15 0 16 0;#P fasten 16 0 1 0 56 507 56 507;#P fasten 16 1 1 0 76 507 56 507;#P fasten 16 2 1 0 96 507 56 507;#P fasten 11 0 1 0 617 513 56 513;#P fasten 7 0 1 0 642 513 56 513;#P fasten 10 1 9 1 113 85 82 85;#P connect 2 0 10 0;#P connect 10 0 20 0;#P connect 20 0 17 0;#P connect 18 0 6 0;#P connect 17 0 6 0;#P connect 6 0 5 0;#P connect 5 0 8 0;#P connect 8 0 12 0;#P connect 20 1 3 0;#P connect 3 0 4 0;#P connect 12 1 14 0;#P connect 14 0 13 1;#P connect 20 2 18 0;#P connect 14 1 15 1;#P fasten 10 2 11 0 128 84 617 84;#P connect 11 1 7 0;#P pop;#P newobj 141 145 120 196617 p get_parameter_values;#P newex 60 72 71 196617 t open b clear;#P newex 60 198 40 196617 text;#N vpatcher 10 59 841 552;#P window setfont "Sans Serif" 9.;#P window linecount 1;#P message 215 203 152 196617 name jcom.remote.module.from;#B color 5;#P message 175 183 170 196617 name "that deaf dumb and blind kid";#B color 5;#P newex 175 408 69 196617 route symbol;#P newex 50 50 231 196617 t dump b /*/module_name/get b clear;#P message 105 259 55 196617 sort -1 -1;#P newex 175 329 102 196617 sprintf store %s %s;#N coll ;#P newobj 175 380 53 196617 coll;#P newex 175 298 143 196617 jcom.oscroute /module_name;#P newex 175 273 70 196617 osc-route /*;#P newex 175 238 206 196617 jcom.receive "that deaf dumb and blind kid";#B color 5;#P window linecount 2;#P newex 174 96 112 196617 jcom.send jcom.remote.module.to;#B color 5;#P inlet 50 30 15 0;#P outlet 175 430 15 0;#P window linecount 0;#P comment 293 100 86 196617 Request names of all modules;#P comment 282 383 145 196617 coll is used to store names of all modules so that they can be alphabetized.;#P comment 399 183 208 196617 This stops jcom.receive from listening if we are not currently requesting the names of all modules.;#P connect 4 0 12 0;#P connect 12 1 11 0;#P connect 12 2 5 0;#P connect 12 1 14 0;#P connect 15 0 6 0;#P connect 14 0 6 0;#P connect 6 0 7 0;#P connect 7 0 8 0;#P connect 8 0 10 0;#P fasten 11 0 9 0 110 356 180 356;#P connect 10 0 9 0;#P fasten 12 0 9 0 55 360 180 360;#P fasten 12 4 9 0 275 72 392 72 392 361 180 361;#P connect 9 0 13 0;#P connect 13 0 3 0;#P connect 12 3 15 0;#P fasten 8 0 10 1 180 322 272 322;#P pop;#P newobj 141 123 123 196617 p get_names_of_modules;#P inlet 60 28 14 0;#P connect 0 0 3 0;#P connect 3 0 5 0;#P connect 5 0 2 0;#P connect 4 0 2 0;#P fasten 3 2 2 0 125 142 65 142;#P connect 3 1 1 0;#P connect 1 0 4 0;#P connect 7 0 9 0;#P lcolor 1;#P connect 9 0 6 0;#P connect 8 0 6 0;#P connect 7 1 8 0;#P lcolor 1;#P pop;#P newobj 240 106 61 196617 p get_state;#P window setfont "Sans Serif" 18.;#P newex 418 296 47 196626 text;#P window setfont "Sans Serif" 9.;#P newex 151 140 108 196617 jcom.filewatcher.mxt;#P newex 151 71 545 196617 jcom.oscroute /load_script /get_state /view /cue /save_script /remote;#P inlet 53 26 15 0;#P connect 0 0 6 0;#P connect 6 0 18 0;#P connect 18 0 17 0;#P connect 6 1 1 0;#P connect 1 0 2 0;#P connect 1 1 4 0;#P connect 1 2 5 0;#P fasten 11 0 10 0 347 361 320 361 320 294 347 294;#P connect 10 0 11 0;#P connect 10 1 11 1;#P connect 10 2 11 2;#P fasten 3 1 11 3 441 330 398 330;#P connect 11 1 12 0;#P connect 1 3 13 0;#P fasten 2 0 3 0 156 236 423 236;#P fasten 7 0 3 0 512 246 423 246;#P connect 13 0 3 0;#P fasten 10 3 3 0 398 318 415 318 415 294 423 294;#P fasten 5 0 3 0 334 233 423 233;#P connect 3 0 9 0;#P connect 9 0 8 0;#P fasten 1 5 14 0 601 102 698 102 698 425 423 425;#P lcolor 2;#P connect 8 0 14 0;#P fasten 8 1 13 1 513 398 688 398 688 182 487 182;#P lcolor 7;#P connect 1 4 7 0;#P connect 13 1 8 1;#P fasten 2 0 16 0 156 164 625 164;#P lcolor 13;#P connect 16 0 7 1;#P lcolor 13;#P pop;