max v2;#N vpatcher 352 137 1170 533;#P origin 10 -85;#P window setfont "Sans Serif" 9.;#P window linecount 1;#P hidden newex 175 129 43 196617 jcom.in;#P user jsui 35 28 20 15 1 0 0 jcom.jsui_texttoggle.js off on;#P objectname on;#P hidden newex 495 46 44 196617 pvar on;#P window linecount 2;#P hidden newex 495 68 220 196617 jcom.parameter on @type msg_toggle @range/clipmode none @description "Turn polling on";#P objectname on[1];#P window linecount 1;#P hidden newex 175 171 45 196617 pcontrol;#P hidden newex 175 150 91 196617 jcom.pass open;#P hidden message 38 69 125 196617 /documentation/generate;#P window linecount 2;#P hidden message 16 229 66 196617 \; max refresh;#P hidden message 16 195 75 196617 \; jcom.init bang;#P window linecount 1;#P hidden newex 175 247 119 196617 jalg.spacenavigator;#P window linecount 2;#P hidden newex 16 94 313 196617 jcom.hub jmod.spacenavigator @size 1U-half @module_type control @description "Use the Space Navigator from 3D Connexion";#P objectname jcom.hub;#P hidden inlet 16 70 13 0;#P hidden outlet 16 132 13 0;#P window linecount 1;#P hidden message 281 223 153 196617 /menu 0;#P hidden newex 281 201 61 196617 prepend set;#P bpatcher 0 0 256 62 0 0 jcom.gui 0;#P objectname jcom.gui.1Uh.a.stereo;#P hidden fasten 9 0 5 0 43 88 21 88;#P hidden connect 4 0 5 0;#P hidden connect 5 0 3 0;#P hidden connect 15 0 10 0;#P hidden connect 10 0 11 0;#P hidden fasten 10 1 6 0 261 192 180 192;#P hidden connect 11 0 6 0;#P hidden fasten 10 1 1 0 261 192 286 192;#P hidden connect 1 0 2 0;#P hidden fasten 12 0 13 0 500 101 488 101 488 41 500 41;#P hidden connect 13 0 12 0;#P pop;