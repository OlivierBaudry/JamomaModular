max v2;#N vpatcher 715 205 1695 877;#P window setfont "Sans Serif" 9.;#P hidden newex 106 458 50 196617 route set;#P hidden newex 238 500 62 196617 prepend set;#P hidden newex 13 503 48 196617 t clear;#P hidden newex 224 479 42 196617 sel null;#P hidden message 133 366 24 196617 null;#P hidden newex 133 344 46 196617 sel bang;#N vpatcher 10 59 610 459;#P window setfont "Sans Serif" 9.;#P newex 24 119 48 196617 t b clear;#P window linecount 1;#P newex 50 76 46 196617 sel bang;#P window linecount 0;#P newex 86 120 62 196617 prepend set;#P newex 86 100 51 196617 tosymbol;#P newex 50 50 56 196617 route text;#P inlet 50 30 15 0;#P outlet 61 194 15 0;#P connect 5 0 6 0;#P connect 1 0 2 0;#P connect 2 0 5 0;#P connect 6 0 0 0;#P connect 6 1 0 0;#P connect 4 0 0 0;#P connect 5 1 3 0;#P connect 3 0 4 0;#P pop;#P hidden newobj 179 78 30 196617 p;#P window linecount 2;#P hidden newex 4 418 385 196617 jcom.parameter osc_prefix @repetitions 0 @description "Define a string to concatenate to the beginning of all OpenSoundControl strings sent by this module.";#P objectname osc_prefix;#P window linecount 1;#P hidden newex 169 364 51 196617 tosymbol;#P hidden newex 133 324 56 196617 route text;#P user textedit 155 122 251 140 98436 3 9;#P comment 103 126 56 196617 osc prefix;#B frgb 255 255 255;#P user textedit 155 21 251 39 98436 3 9;#P comment 103 25 56 196617 osc prefix;#B frgb 255 255 255;#P hidden newex 408 393 101 196617 pvar multicast_port;#P window linecount 2;#P hidden newex 408 415 401 196617 jcom.parameter multicast_port @type msg_int @clipmode none @description "Set the network port number used for sending out multicast OpenSoundControl messages.";#P objectname multicast_port[1];#P number 47 124 35 9 0 0 8224 3 255 255 255 221 221 221 222 222 222 0 0 0;#P objectname multicast_port;#P window linecount 1;#P comment 22 126 29 196617 port;#B frgb 255 255 255;#P hidden newex 408 476 99 196617 pvar multicast_join;#P window linecount 2;#P hidden newex 408 496 380 196617 jcom.parameter multicast_join @type msg_int @clipmode none @description "Set the network port number on which to receive OpenSoundControl messages.";#P objectname multicast_join[1];#P window linecount 3;#P hidden newex 367 322 314 196617 jcom.parameter multicast_ip @repetitions 0 @description "Define the multicast host to for OpenSoundControl messages to which you would like to join.  This may be symbolic or an ip address.";#P objectname multicast_ip;#P window linecount 1;#P hidden newex 367 302 51 196617 tosymbol;#P hidden newex 367 282 56 196617 route text;#P user jsui 114 141 42 18 1 0 0 jcom.jsui_texttoggle.js Join Leave 204 204 204 0 0 0 162 226 132;#P objectname multicast_join;#P comment 22 144 90 196617 multicast address;#B frgb 255 255 255;#P user textedit 155 141 251 159 98436 3 9 127.0.0.1;#N thispatcher;#Q end;#P hidden newobj 560 77 61 196617 thispatcher;#P hidden message 637 52 72 196617 offset 0 -120;#P hidden message 560 52 66 196617 offset 0 -19;#P hidden newex 560 30 165 196617 sel 0 1;#P hidden inlet 560 9 15 0;#P window linecount 2;#P hidden newex 367 106 398 196617 jcom.parameter send_host @repetitions 0 @description "Set the host to which OpenSoundControl messages should be sent.  This may be symbolic or an ip address.";#P objectname send_host;#P window linecount 1;#P hidden newex 367 86 51 196617 tosymbol;#P hidden newex 367 66 56 196617 route text;#P number 66 42 35 9 0 0 8224 3 255 255 255 221 221 221 222 222 222 0 0 0;#P objectname port_out;#P number 66 25 35 9 0 0 8224 3 255 255 255 221 221 221 222 222 222 0 0 0;#P objectname port_in;#P user textedit 155 40 251 58 98436 3 9 127.0.0.1;#P comment 18 44 52 196617 send port;#B frgb 255 255 255;#P hidden newex 367 217 73 196617 pvar port_out;#P window linecount 2;#P hidden newex 367 239 362 196617 jcom.parameter send_port @type msg_int @clipmode none @description "Set the network port number used for sending out OpenSoundControl messages.";#P objectname send_port;#P window linecount 1;#P comment 4 27 66 196617 receive port;#B frgb 255 255 255;#P hidden newex 367 153 67 196617 pvar port_in;#P window linecount 2;#P hidden newex 367 173 378 196617 jcom.parameter receive_port @type msg_int @clipmode none @description "Set the network port number on which to receive OpenSoundControl messages.";#P objectname receive_port;#P user fpic -1 100 258 64 jcom.bg.j4.control.1U-half.pct 0 0 0 0. 0 0 0;#P window linecount 1;#P comment 107 44 52 196617 send host;#B frgb 255 255 255;#P user fpic -1 -1 258 64 jcom.bg.j4.control.1U-half.pct 0 0 0 0. 0 0 0;#P hidden connect 41 0 38 0;#P hidden connect 37 0 38 0;#P hidden connect 42 0 43 0;#P hidden connect 38 0 45 0;#P hidden connect 35 0 36 0;#P hidden connect 36 0 40 0;#P hidden connect 40 0 41 0;#P hidden connect 43 0 33 0;#P hidden connect 44 0 33 0;#P hidden connect 14 0 9 0;#P hidden connect 39 0 35 0;#P hidden connect 25 0 20 0;#P hidden connect 40 1 37 0;#P hidden connect 33 0 39 0;#P hidden connect 45 0 42 0;#P hidden connect 42 1 44 0;#P hidden connect 9 0 12 0;#P hidden connect 12 0 13 0;#P hidden connect 13 0 14 0;#P hidden fasten 3 0 4 0 372 207 360 207 360 148 372 148;#P hidden connect 4 0 3 0;#P hidden fasten 6 0 7 0 372 272 360 272 360 210 372 210;#P hidden connect 7 0 6 0;#P hidden connect 20 0 23 0;#P hidden connect 23 0 24 0;#P hidden connect 24 0 25 0;#P hidden fasten 30 0 31 0 413 462 401 462 401 386 413 386;#P hidden connect 31 0 30 0;#P hidden fasten 26 0 27 0 413 532 401 532 401 471 413 471;#P hidden connect 27 0 26 0;#P hidden connect 15 0 16 0;#P hidden connect 16 0 17 0;#P hidden connect 18 0 19 0;#P hidden connect 17 0 19 0;#P hidden connect 16 1 18 0;#P pop;