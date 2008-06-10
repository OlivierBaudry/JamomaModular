max v2;#N vpatcher 202 218 1277 787;#P window setfont "Sans Serif" 9.;#N vpatcher 10 59 610 459;#P outlet 114 212 15 0;#P window setfont "Sans Serif" 9.;#P window linecount 0;#P newex 114 159 27 196617 t b i;#P newex 114 185 68 196617 pack set 0 0.;#P newex 114 136 27 196617 + 1;#P newex 114 112 61 196617 unpack 0 0.;#P newex 114 89 52 196617 listfunnel;#P window linecount 1;#P newex 73 64 51 196617 zl slice 1;#P inlet 73 39 15 0;#P connect 0 0 1 0;#P connect 1 1 2 0;#P connect 2 0 3 0;#P connect 3 0 4 0;#P connect 4 0 6 0;#P connect 6 0 5 0;#P connect 5 0 7 0;#P connect 6 1 5 1;#P connect 3 1 5 2;#P pop;#P newobj 467 168 66 196617 p formatting;#P user multiSlider 7 51 241 63 -60. 0. 10 2937 47 0 0 2 2 0 0;#M frgb 91 91 91;#M brgb 17 17 17;#M rgb2 127 127 127;#M rgb3 0 0 0;#M rgb4 43 62 107;#M rgb5 74 105 182;#M rgb6 112 158 18;#M rgb7 149 211 110;#M rgb8 187 9 201;#M rgb9 224 62 37;#M rgb10 7 114 128;#P objectname 10gains;#P newex 266 385 47 196617 pcontrol;#P newex 133 361 143 196617 jcom.algorithm_control~;#P message 105 150 191 196617 /preset/store 1 default \, /preset/write;#B color 3;#P newex 244 444 64 196617 jcom.out~ 1;#P newex 133 332 49 196617 jcom.in~;#P message 113 172 125 196617 /documentation/generate;#B color 3;#P window linecount 2;#P message 98 250 65 196617 \; max refresh;#P window linecount 1;#P newex 467 114 69 196617 pvar 10gains;#P newex 467 49 80 196617 pvar Frequency;#P window linecount 2;#P newex 15 206 308 196617 jcom.hub jmod.10_harmonics~ @size 2U-half @module_type audio @description "Additive synthesis using 10 harmonic partials.";#P objectname jcom.hub;#P window linecount 1;#P comment 29 173 79 196617 command input;#P inlet 15 173 13 0;#P message 244 172 31 196617 /init;#P outlet 244 473 13 0;#P flonum 88 29 40 9 0 0 8224 3 181 181 181 221 221 221 255 255 255 0 0 0;#P objectname Frequency;#P window linecount 2;#P newex 467 74 403 196617 jcom.parameter frequency @type msg_float @range 20 20000 @range/clipmode none @ramp/drive scheduler @ramp/function linear @description "Frequency of the signal.";#P objectname frequency;#P newex 467 136 377 196617 jcom.parameter harmonic_gains @type msg_list @ramp/drive scheduler @ramp/function linear @description "List of gain values (dB) for the 10 partials";#P objectname harmonic_gains;#P window linecount 1;#P comment 8 30 76 196617 Frequency (Hz);#B frgb 149 149 149;#P newex 133 414 121 196617 jalg.10_harmonics~;#P outlet 15 249 13 0;#P comment 217 491 101 196617 ---signal outputs---;#P bpatcher 0 0 256 120 0 0 jcom.gui 0 $0_;#P objectname jmod.gui.1Uh.a.stereo;#P fasten 19 0 12 0 110 193 20 193;#P connect 10 0 12 0;#P fasten 16 0 12 0 118 193 20 193;#P fasten 9 0 12 0 249 193 20 193;#P connect 12 0 2 0;#P connect 17 0 20 0;#P connect 20 0 3 0;#P fasten 21 0 3 0 271 408 138 408;#P connect 3 1 18 0;#P connect 18 0 8 0;#P connect 20 1 21 0;#P fasten 6 0 13 0 472 105 462 105 462 42 472 42;#P connect 13 0 6 0;#P fasten 23 0 14 0 472 189 461 189 461 110 472 110;#P connect 14 0 5 0;#P connect 5 0 23 0;#P pop;