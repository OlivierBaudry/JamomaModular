max v2;#N vpatcher 638 388 1493 823;#P window setfont "Sans Serif" 9.;#P window linecount 1;#P hidden newex 198 154 38 196617 jcom.in;#P window linecount 2;#P hidden newex 490 184 266 196617 jcom.message send @description "An OpenSoundControl message to send out over the network.";#P hidden newex 198 304 278 196617 jcom.return receive @description "OpenSoundControl messages coming in from the network are reported here.";#P user umenu 177 2 76 196647 1 64 18 1;#X add single;#X add multicast;#P objectname multicast_button;#P window linecount 1;#P hidden newex 493 99 110 196617 pvar multicast_button;#P window linecount 2;#P hidden newex 493 121 283 196617 jcom.parameter mode @type msg_toggle @clipmode none @description "Choose between single IP or multicast usage";#P objectname mode;#P bpatcher 0 20 256 42 0 -19 jalg.oscnet.ui.mxt 0 $0_;#P objectname jalg.oscnet.ui.mxt;#P window linecount 1;#P hidden comment 44 276 100 196617 * activity monitor;#P hidden newex 198 198 45 196617 pcontrol;#P hidden newex 198 176 91 196617 jcom.pass open;#P hidden message 38 69 125 196617 /documentation/generate;#P window linecount 2;#P hidden message 99 195 66 196617 \; max refresh;#P window linecount 1;#P hidden message 167 69 37 196617 /init;#P hidden newex 198 282 80 196617 jalg.oscnet.mxt;#P window linecount 3;#P hidden newex 16 94 365 196617 jcom.hub jmod.oscnet @size 1U-half @module_type control @description "Send and receive OpenSoundControl over a network port.  You may receive directly or join up to 2 multicast addresses in addition to receiving directly.";#P objectname jcom.hub;#P hidden inlet 16 70 13 0;#P hidden outlet 16 146 13 0;#P window linecount 1;#P hidden comment 44 254 100 196617 * activity monitor;#P bpatcher 0 0 256 62 0 0 jcom.gui.mxt 0;#P objectname jcom.gui.1Uh.a.stereo.mxt;#P hidden fasten 13 1 12 0 622 161 792 161 792 14 5 14;#P hidden connect 15 0 12 0;#P hidden fasten 8 0 4 0 43 88 21 88;#P hidden connect 3 0 4 0;#P hidden fasten 6 0 4 0 172 90 21 90;#P hidden connect 4 0 2 0;#P hidden connect 18 0 9 0;#P hidden connect 9 0 10 0;#P hidden fasten 9 1 5 0 284 222 203 222;#P hidden connect 10 0 5 0;#P hidden connect 5 0 16 0;#P hidden fasten 13 0 14 0 498 158 486 158 486 92 498 92;#P hidden connect 14 0 13 0;#P pop;