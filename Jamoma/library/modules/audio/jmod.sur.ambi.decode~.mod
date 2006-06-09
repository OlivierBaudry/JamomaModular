max v2;#N vpatcher 75 67 1017 680;#P window setfont "Sans Serif" 9.;#P window linecount 1;#P hidden comment 362 460 158 196617 ----multicable signal output----;#P hidden message 98 121 50 196617 /autodoc;#P hidden newex 151 251 84 196617 jmod.pass open;#P hidden newex 151 276 47 196617 pcontrol;#N vpatcher 38 82 638 482;#P window setfont "Sans Serif" 9.;#P newex 233 88 126 196617 jmod.sur.ambi.getW~.mxt;#P newex 233 286 36 196617 pass~;#P outlet 233 324 15 0;#P inlet 61 61 15 0;#P user gain~ 233 150 24 100 158 0 1.071519 7.94321 10.;#P inlet 233 61 15 0;#P newex 61 117 126 196617 jmod.oscroute /gain/midi;#P connect 3 0 0 0;#P connect 1 0 6 0;#P connect 6 0 2 0;#P connect 0 0 2 0;#P connect 2 0 5 0;#P connect 5 0 4 0;#P pop;#P hidden newobj 235 413 74 196617 p display_gain;#P window linecount 2;#P hidden newex 557 522 349 196617 jmod.message.mxt $0_ /aed @type msg_list @description "List describing index (counting from 1)\\\, azimuth\\\, elevation\\\, distance for one speaker.";#P window linecount 1;#P hidden newex 557 423 58 196617 pvar Third;#P window linecount 2;#P hidden newex 557 445 355 196617 jmod.parameter.mxt $0_ /third @type msg_float @ramp 0 @repetitions 0 @range 0. 2. @clipmode both @description "Third order weight (KLMNOPQ).";#P objectname jmod.parameter[5];#P window linecount 1;#P hidden newex 557 359 65 196617 pvar Second;#P window linecount 2;#P hidden newex 557 381 355 196617 jmod.parameter.mxt $0_ /second @type msg_float @ramp 0 @repetitions 0 @range 0. 2. @clipmode both @description "Second order weight (RSTUV).";#P objectname jmod.parameter[4];#P window linecount 1;#P hidden newex 557 295 56 196617 pvar First;#P window linecount 2;#P hidden newex 557 317 337 196617 jmod.parameter.mxt $0_ /first @type msg_float @ramp 0 @repetitions 0 @range 0. 2. @clipmode both @description "First order weight (XYZ).";#P objectname jmod.parameter[3];#P window linecount 1;#P hidden newex 557 231 56 196617 pvar Omni;#P window linecount 2;#P hidden newex 557 253 337 196617 jmod.parameter.mxt $0_ /omni @type msg_float @ramp 0 @repetitions 0 @range 0. 2. @clipmode both @description "Zeroth order weight (W).";#P objectname jmod.parameter[2];#P number 45 39 35 9 1 3 8227 3 198 198 198 221 221 221 222 222 222 0 0 0;#P objectname Order;#P flonum 125 39 40 9 0. 2. 8227 3 198 198 198 221 221 221 222 222 222 0 0 0;#P objectname First;#P flonum 205 39 40 9 0. 2. 8227 3 198 198 198 221 221 221 222 222 222 0 0 0;#P objectname Third;#P flonum 205 21 40 9 0. 2. 8227 3 198 198 198 221 221 221 222 222 222 0 0 0;#P objectname Second;#P window linecount 1;#P comment 173 41 31 196617 3rd;#B frgb 172 172 172;#P comment 173 23 31 196617 2nd;#B frgb 172 172 172;#P comment 88 41 37 196617 1st;#B frgb 172 172 172;#P comment 88 23 37 196617 Omni;#B frgb 172 172 172;#P comment 3 41 41 196617 Order;#B frgb 172 172 172;#N comlet Channel 1;#P hidden outlet 347 460 13 0;#N comlet W - omni;#P hidden inlet 491 247 13 0;#P hidden comment 317 248 158 196617 ----multicable signal input----;#P hidden message 235 336 20 196617 \$2;#P hidden newex 235 313 72 196617 route mute;#P hidden newex 235 360 38 196617 mute~;#P hidden newex 347 420 154 196617 jmod.sur.ambi.decode~.alg;#P window linecount 2;#P hidden message 28 528 65 196617 \; max refresh;#P window linecount 1;#P hidden newex 557 144 60 196617 pvar Order;#P window linecount 4;#P hidden newex 0 150 312 196617 jmod.hub $0_ jmod.sur.ambi.decode~ @size 1U-half @module_type audio.ambisonic @num_inputs 1 @num_outputs 1 @description "Decoding ambisonic signal to multispeaker setup. <br>NOTE: The positions of the speakers are not maintained by this module.";#P objectname jmod.hub;#P window linecount 1;#P hidden comment 14 121 79 196617 command input;#P hidden inlet 0 121 13 0;#P window linecount 2;#P hidden message 28 496 72 196617 \; jmod.init bang;#P window linecount 3;#P hidden newex 340 150 79 196617 pattrstorage @autorestore 0 @savemode 0;#X client_rect 34 59 1010 799;#X storage_rect 0 0 640 240;#P objectname jmod.sur.ambi.decode~;#P flonum 125 21 40 9 0. 2. 8227 3 198 198 198 221 221 221 222 222 222 0 0 0;#P objectname Omni;#P hidden newex 557 166 332 196617 jmod.parameter.mxt $0_ /order @type msg_int @ramp 0 @repetitions 0 @range 1 3 @clipmode both @description "Order of decoding for ambisonic signal.  Changes only take effect when audio is off.";#P objectname jmod.parameter[1];#P window linecount 1;#P comment 3 23 41 196617 Voices;#B frgb 172 172 172;#P number 45 21 35 9 1 16 8227 3 198 198 198 221 221 221 222 222 222 0 0 0;#P objectname Voices;#P hidden outlet 0 246 13 0;#P hidden newex 557 48 63 196617 pvar Voices;#P window linecount 3;#P hidden newex 557 73 365 196617 jmod.parameter.mxt $0_ /voices @type msg_int @ramp 0 @repetitions 0 @range 1 16 @clipmode both @description "The number of audio channels that the ambisonic signal is diffused to. Changes only take effect when audio is off.";#P objectname jmod.parameter;#P bpatcher 0 0 255 60 0 0 jmod.gui.mxt 0 $0_;#P objectname jmod.gui.1Uh.a.stereo.mxt;#P hidden fasten 40 0 0 0 240 503 530 503 530 -5 5 -5;#P hidden connect 10 0 12 0;#P hidden fasten 43 0 12 0 103 138 5 138;#P hidden connect 12 0 3 0;#P hidden connect 12 1 42 0;#P hidden connect 42 0 41 0;#P hidden connect 42 1 17 0;#P hidden connect 17 0 18 0;#P hidden connect 18 0 16 0;#P hidden connect 16 0 40 0;#P hidden fasten 17 1 40 0 302 399 240 399;#P hidden connect 20 0 40 1;#P hidden connect 8 0 12 1;#P hidden connect 12 2 8 0;#P hidden connect 17 1 15 0;#P hidden connect 16 0 15 0;#P hidden fasten 41 0 15 0 156 300 352 300;#P hidden connect 15 0 21 0;#P hidden connect 20 0 15 1;#P hidden fasten 1 0 2 0 562 118 552 118 552 41 562 41;#P hidden connect 2 0 1 0;#P hidden fasten 6 0 13 0 562 210 552 210 552 140 562 140;#P hidden connect 13 0 6 0;#P hidden fasten 31 0 32 0 562 286 552 286 552 227 562 227;#P hidden connect 32 0 31 0;#P hidden fasten 33 0 34 0 562 350 552 350 552 291 562 291;#P hidden connect 34 0 33 0;#P hidden fasten 35 0 36 0 562 414 552 414 552 355 562 355;#P hidden connect 36 0 35 0;#P hidden fasten 37 0 38 0 562 478 552 478 552 419 562 419;#P hidden connect 38 0 37 0;#P pop;