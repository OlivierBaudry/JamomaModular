max v2;
#N vpatcher 0 0 1415 796;
#P origin -94 -501;
#P window setfont "Sans Serif" 9.;
#P window linecount 1;
#P comment 584 266 238 9109513 5. start recording and generate random example data.;
#P window linecount 2;
#P comment 584 238 238 9109513 4. write rest of the stream definitions: variable names seperated by \\\\\\\, and frame description;
#P comment 584 210 238 9109513 3. open an SDIF file to write (like below \, only change path and file name);
#P window linecount 1;
#P comment 584 195 238 9109513 2. enter ID for all streams in use;
#P comment 584 180 238 9109513 1. enter the number of streams;
#P comment 579 162 238 9109513 For now \, use this order when using the module:;
#P window setfont "Sans Serif" 14.;
#P comment 521 415 238 9109518 Still to be implemented:;
#P comment 160 518 238 9109518 For testing purposes:;
#P window setfont "Sans Serif" 9.;
#P comment 296 171 238 9109513 I'll fix this \, to make the input order arbitrary \, later..;
#P window linecount 2;
#P comment 296 140 238 9109513 When using several streams \, start by defining the "last" stream (e.g. 2 before 1 before 0);
#P window linecount 1;
#P comment 150 21 180 9109513 (must be set before defining streams);
#B frgb 181 181 181;
#P hidden newex 911 659 87 9109513 pvar record_button;
#P window linecount 2;
#P hidden newex 911 682 235 9109513 jcom.parameter write_control/record_button @type msg_toggle @description "Start/Stop recording";
#P objectname write_control/record_button;
#P window linecount 1;
#P hidden newex 1120 501 48 9109513 route text;
#P window linecount 2;
#P hidden newex 1169 487 242 9109513 jcom.message stream3/description @type msg_symbol @description "one word stream description";
#P objectname jalg.sdif.player[1];
#P hidden newex 1120 521 235 9109513 jcom.message stream3/variables @type msg_symbol @description "Martix row variables. separated by \\\\\\\,";
#P objectname jalg.sdif.player[2];
#P hidden newex 1071 555 264 9109513 jcom.message stream3/ID @type msg_symbol @description "4 letter frame/matrix identificator. e.g. 1MID or XPOS";
#P objectname jalg.sdif.player[4];
#P hidden newex 1169 356 242 9109513 jcom.message stream2/description @type msg_symbol @description "one word stream description";
#P objectname jalg.sdif.player[11];
#P hidden newex 1120 390 235 9109513 jcom.message stream2/variables @type msg_symbol @description "Martix row variables. separated by \\\\\\\,";
#P objectname jalg.sdif.player[12];
#P hidden newex 1071 424 264 9109513 jcom.message stream2/ID @type msg_symbol @description "4 letter frame/matrix identificator. e.g. 1MID or XPOS";
#P objectname jalg.sdif.player[13];
#P window linecount 1;
#P hidden newex 1071 535 48 9109513 route text;
#P hidden newex 1169 467 48 9109513 route text;
#P hidden newex 1120 370 48 9109513 route text;
#P hidden newex 1071 404 48 9109513 route text;
#P hidden newex 1169 336 48 9109513 route text;
#P window linecount 3;
#P comment 597 25 82 9109513 variable names mustbe seperaed by \\\\\\\,;
#P window linecount 2;
#P comment 515 25 82 9109513 4. define MTD/FTD;
#P number 133 21 17 9 1 0 8225 139 149 149 149 221 221 221 222 222 222 0 0 0;
#P objectname streamcount;
#P window linecount 1;
#P hidden newex 911 603 82 9109513 pvar streamcount;
#P comment 2 21 132 9109513 Number of streams to record:;
#B frgb 181 181 181;
#P hidden newex 911 628 406 9109513 jcom.parameter streamcount @type msg_int @description "Number of streams to be recorded";
#P objectname streamcount[1];
#P hidden newex 1120 237 48 9109513 route text;
#P window linecount 2;
#P hidden newex 1169 223 242 9109513 jcom.message stream1/description @type msg_symbol @description "one word stream description";
#P objectname jalg.sdif.player[8];
#P hidden newex 1120 257 235 9109513 jcom.message stream1/variables @type msg_symbol @description "Martix row variables. separated by \\\\\\\,";
#P objectname jalg.sdif.player[9];
#P hidden newex 1071 291 264 9109513 jcom.message stream1/ID @type msg_symbol @description "4 letter frame/matrix identificator. e.g. 1MID or XPOS";
#P objectname jalg.sdif.player[10];
#P window setfont "Sans Serif" 10.;
#P window linecount 1;
#P message 81 599 105 9109514 set c:/lala1.sdif \, print;
#P window setfont "Sans Serif" 9.;
#N ftm.sdif.info --> 0;
#T _#ftm version 2 2;
#T _#scope begin;
#T _#absargs $0_ $1_ $2_ $3_ $4_ $5_ $6_ $7_ $8_ $9_;
#P newobj 81 631 61 9109513 ftm.sdif.info;
#P window linecount 2;
#P hidden newex 1169 89 242 9109513 jcom.message stream0/description @type msg_symbol @description "one word stream description";
#P objectname jalg.sdif.player[7];
#P hidden newex 1120 123 235 9109513 jcom.message stream0/variables @type msg_symbol @description "Martix row variables. separated by \\\\\\\,";
#P objectname jalg.sdif.player[6];
#P hidden newex 1071 157 264 9109513 jcom.message stream0/ID @type msg_symbol @description "4 letter frame/matrix identificator. e.g. 1MID or XPOS";
#P objectname jalg.sdif.player[3];
#P window linecount 1;
#P hidden newex 1071 271 48 9109513 route text;
#P hidden newex 1169 203 48 9109513 route text;
#P hidden newex 1120 103 48 9109513 route text;
#P user textedit 157 102 377 120 98316 139 9;
#P comment 63 103 47 9109513 Stream 3;
#B frgb 181 181 181;
#P user textedit 109 102 146 120 98308 139 9;
#P user textedit 380 102 503 120 98308 139 9;
#P user textedit 157 85 377 103 98316 139 9;
#P comment 63 86 47 9109513 Stream 2;
#B frgb 181 181 181;
#P user textedit 109 85 146 103 98308 139 9;
#P user textedit 380 85 503 103 98308 139 9;
#P user textedit 157 68 377 86 98316 139 9;
#P comment 63 69 47 9109513 Stream 1;
#B frgb 181 181 181;
#P user textedit 109 68 146 86 98308 139 9;
#P user textedit 380 68 503 86 98308 139 9;
#P hidden newex 1071 137 48 9109513 route text;
#P hidden newex 1169 69 48 9109513 route text;
#P comment 380 39 88 9109513 Frame description;
#B frgb 181 181 181;
#P user textedit 157 51 377 69 98316 139 9 "X\, Y\, Z";
#P comment 157 39 71 9109513 Variable names;
#B frgb 181 181 181;
#P comment 63 52 47 9109513 Stream 0;
#B frgb 181 181 181;
#P toggle 312 581 15 0;
#N vpatcher 10 59 610 459;
#P window setfont "Sans Serif" 9.;
#P window linecount 1;
#P newex 115 231 163 9109513 pack 0. 0. 0. 0. 0. 0.;
#P newex 293 196 29 9109513 * 1.;
#P newex 293 174 35 9109513 * 0.1;
#P newex 251 174 41 9109513 * 0.01;
#P newex 217 174 33 9109513 - 49.;
#P newex 175 174 41 9109513 * 0.34;
#P newex 145 174 27 9109513 - 1.;
#P newex 115 146 64 9109513 random 100;
#P window linecount 0;
#P newex 115 114 58 9109513 metro 100;
#P outlet 115 269 15 0;
#P inlet 115 62 15 0;
#P comment 227 105 100 9109513 just silly random data....;
#P connect 1 0 3 0;
#P connect 3 0 4 0;
#P fasten 4 0 11 0 120 197 120 197;
#P connect 11 0 2 0;
#P fasten 4 0 5 0 120 168 150 168;
#P connect 5 0 11 1;
#P fasten 4 0 6 0 120 168 180 168;
#P connect 6 0 11 2;
#P fasten 7 0 11 3 222 211 210 211;
#P fasten 4 0 7 0 120 168 222 168;
#P fasten 8 0 11 4 256 211 240 211;
#P fasten 4 0 8 0 120 168 256 168;
#P fasten 10 0 11 5 298 222 270 222;
#P fasten 4 0 9 0 120 168 298 168;
#P connect 9 0 10 0;
#P fasten 9 0 10 1 298 193 317 193;
#P pop;
#P newobj 312 600 76 9109513 p random_data;
#P newex 312 699 85 9109513 prepend /data/1;
#P newex 312 624 80 9109513 prepend set 0 0;
#P newex 312 648 27 9109513 t b l;
#P user ftm.object 312 675 51 18 139 9 --> 0;
#T _#obj 1 fmat;
#T _#def 0 "_fmat 2 3" stream1 local;
#P toggle 205 584 15 0;
#N vpatcher 130 531 730 931;
#P window setfont "Sans Serif" 9.;
#P window linecount 1;
#P newex 115 231 163 9109513 pack 0. 0. 0. 0. 0. 0.;
#P newex 293 196 29 9109513 * 1.;
#P newex 293 174 35 9109513 * 0.1;
#P newex 251 174 41 9109513 * 0.01;
#P newex 217 174 33 9109513 - 49.;
#P newex 175 174 41 9109513 * 0.34;
#P newex 145 174 27 9109513 - 1.;
#P newex 115 146 64 9109513 random 100;
#P window linecount 0;
#P newex 115 114 58 9109513 metro 100;
#P outlet 115 269 15 0;
#P inlet 115 62 15 0;
#P comment 227 105 100 9109513 just silly random data....;
#P connect 1 0 3 0;
#P connect 3 0 4 0;
#P fasten 4 0 11 0 120 197 120 197;
#P connect 11 0 2 0;
#P fasten 4 0 5 0 120 168 150 168;
#P connect 5 0 11 1;
#P fasten 4 0 6 0 120 168 180 168;
#P connect 6 0 11 2;
#P fasten 7 0 11 3 222 211 210 211;
#P fasten 4 0 7 0 120 168 222 168;
#P fasten 8 0 11 4 256 211 240 211;
#P fasten 4 0 8 0 120 168 256 168;
#P fasten 10 0 11 5 298 222 270 222;
#P fasten 4 0 9 0 120 168 298 168;
#P connect 9 0 10 0;
#P fasten 9 0 10 1 298 193 317 193;
#P pop;
#P newobj 205 603 76 9109513 p random_data;
#P newex 619 561 117 9109513 prepend /write_control;
#P comment 613 446 110 9109513 3. Open an SDIF file;
#P newex 205 701 85 9109513 prepend /data/0;
#P newex 205 626 80 9109513 prepend set 0 0;
#P comment 626 505 82 9109513 5. define NVT's;
#P window linecount 2;
#P comment 200 547 178 9109513 Randomly generated data for the two first streams (three columns):;
#P window linecount 1;
#P newex 205 650 27 9109513 t b l;
#P user ftm.object 205 677 51 18 139 9 --> 0;
#T _#obj 2 fmat;
#T _#def 0 "_fmat 2 3" stream0 local;
#P user ftm.object 619 520 30 18 139 9 --> 0;
#T _#obj 3 dict;
#T _#mess 3 set _table_name _jmod.sdif.record;
#T _#mess 3 set _Jamoma _test;
#T _#def 1 _dict test_nvt local;
#P user ftm.mess 619 542 67 15 139 9 255 255 255 0 0 0 1 2 0 0 --> 0;
#T _#line "_nvt $test_nvt";
#T _#scope end;
#P window setfont "Sans Serif" 10.;
#P message 623 460 157 9109514 /write_control open C:/lala1.sdif;
#P user panel 606 438 125 24;
#X brgb 244 231 185;
#X frgb 0 0 0;
#X border 0;
#X rounded 0;
#X shadow 0;
#X done;
#P user panel 611 502 106 19;
#X brgb 244 231 185;
#X frgb 0 0 0;
#X border 0;
#X rounded 0;
#X shadow 0;
#X done;
#P user panel 197 544 200 35;
#X brgb 244 231 185;
#X frgb 0 0 0;
#X border 0;
#X rounded 0;
#X shadow 0;
#X done;
#P user panel 191 541 224 192;
#X brgb 165 169 216;
#X frgb 0 0 0;
#X border 0;
#X rounded 0;
#X shadow 0;
#X done;
#P user panel 597 496 168 84;
#X brgb 165 169 216;
#X frgb 0 0 0;
#X border 0;
#X rounded 0;
#X shadow 0;
#X done;
#P user panel 572 433 387 46;
#X brgb 165 169 216;
#X frgb 0 0 0;
#X border 0;
#X rounded 0;
#X shadow 0;
#X done;
#P window setfont "Sans Serif" 9.;
#P user textedit 109 51 146 69 98308 139 9 XACC;
#P hidden message 66 148 191 9109513 /preset/store 1 default \, /preset/write;
#B color 3;
#P window linecount 2;
#P hidden message 280 283 75 9109513 \; jcom.init bang;
#P window linecount 1;
#P hidden message 146 341 406 9109513 /streamcount 1;
#P hidden newex 146 320 62 9109513 prepend set;
#P hidden message 93 166 125 9109513 /documentation/generate;
#P comment 109 39 47 9109513 ID;
#B frgb 181 181 181;
#P user jsui 5 92 45 19 3 0 0 jcom.jsui_texttoggle.js Record Record 68 68 68 225 225 225 40 255 40 0 0 0;
#P objectname record_button;
#P hidden newex 63 269 43 9109513 jcom.in;
#P hidden newex 63 317 45 9109513 pcontrol;
#P hidden newex 63 293 78 9109513 jcom.pass open;
#P window linecount 2;
#P hidden message 210 283 65 9109513 \; max refresh;
#P window linecount 1;
#P hidden message 219 166 31 9109513 /init;
#P hidden newex 63 442 70 9109513 jalg.sdif.record;
#P objectname jalg.sdif.player;
#P window linecount 2;
#P hidden newex 30 191 229 9109513 jcom.hub jmod.sdif.record @size 2U @module_type control @description "Single stream SDIF file player";
#P objectname jcom.hub;
#P hidden inlet 30 167 13 0;
#P hidden outlet 30 393 13 0;
#P user textedit 380 51 503 69 98308 139 9 XYZ_acceleration;
#P user panel 62 38 446 82;
#X brgb 20 20 20;
#X frgb 0 0 0;
#X border 0;
#X rounded 0;
#X shadow 0;
#X done;
#P bpatcher 0 0 511 122 0 0 jcom.gui.mxt 0 $0_;
#P objectname jcom.gui.audio-component.mxt;
#P hidden connect 18 0 5 0;
#P hidden connect 14 0 5 0;
#P hidden fasten 7 0 5 0 224 187 35 187;
#P hidden connect 4 0 5 0;
#P hidden connect 5 0 3 0;
#P hidden connect 11 0 9 0;
#P hidden connect 9 0 10 0;
#P hidden fasten 9 1 6 0 136 376 68 376;
#P hidden connect 26 0 6 0;
#P hidden connect 10 0 6 0;
#P hidden connect 36 0 6 0;
#P hidden connect 34 0 6 0;
#P hidden connect 42 0 6 0;
#P connect 70 0 69 0;
#P hidden fasten 9 1 15 0 136 317 151 317;
#P hidden connect 15 0 16 0;
#P connect 38 0 37 0;
#P connect 37 0 33 0;
#P connect 33 0 30 0;
#P connect 30 0 29 0;
#P connect 30 1 29 0;
#P connect 29 0 34 0;
#P connect 44 0 43 0;
#P connect 43 0 41 0;
#P connect 41 0 40 0;
#P connect 40 1 39 0;
#P connect 40 0 39 0;
#P connect 39 0 42 0;
#P connect 27 0 36 0;
#P hidden fasten 75 0 77 0 916 652 907 652 907 596 916 596;
#P hidden connect 77 0 75 0;
#P hidden fasten 93 0 94 0 916 718 907 718 907 654 916 654;
#P hidden connect 94 0 93 0;
#P hidden fasten 19 0 50 0 114 69 1076 69;
#P hidden connect 50 0 66 0;
#P hidden fasten 52 0 65 0 114 85 1062 85 1062 202 1076 202;
#P hidden connect 65 0 71 0;
#P hidden fasten 56 0 82 0 114 102 1052 102 1052 336 1076 336;
#P hidden connect 82 0 86 0;
#P hidden fasten 60 0 85 0 114 120 1042 120 1042 467 1076 467;
#P hidden connect 85 0 89 0;
#P hidden fasten 47 0 63 0 162 68 1125 68;
#P hidden connect 63 0 67 0;
#P hidden fasten 54 0 74 0 162 84 1063 84 1063 202 1125 202;
#P hidden connect 74 0 72 0;
#P hidden fasten 58 0 83 0 162 101 1053 101 1053 335 1125 335;
#P hidden connect 83 0 87 0;
#P hidden fasten 62 0 92 0 162 119 1043 119 1043 466 1125 466;
#P hidden connect 92 0 90 0;
#P hidden fasten 2 0 49 0 385 67 1174 67;
#P hidden connect 49 0 68 0;
#P hidden fasten 51 0 64 0 385 83 1064 83 1064 201 1174 201;
#P hidden connect 64 0 73 0;
#P hidden fasten 55 0 81 0 385 100 1054 100 1054 334 1174 334;
#P hidden connect 81 0 88 0;
#P hidden fasten 59 0 84 0 385 118 1044 118 1044 465 1174 465;
#P hidden connect 84 0 91 0;
#P pop;
