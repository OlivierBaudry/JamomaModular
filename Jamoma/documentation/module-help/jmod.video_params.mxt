max v2;
#N vpatcher 249 81 668 323;
#P origin -13 -19;
#P window setfont "Sans Serif" 18.;
#P comment 3 1 206 196626 Video Controls;
#P window setfont "Sans Serif" 12.;
#P comment 3 31 270 196620 Standard video module messages;
#P hidden outlet 185 195 15 0;
#P window setfont "Sans Serif" 9.;
#P message 28 106 68 196617 /preview \$1;
#P toggle 11 106 15 0;
#P message 28 52 53 196617 /mute \$1;
#P toggle 11 52 15 0;
#P message 28 124 58 196617 /genframe;
#P toggle 11 88 15 0;
#P message 28 88 60 196617 /freeze \$1;
#P message 28 70 62 196617 /bypass \$1;
#P toggle 11 70 15 0;
#P user panel 0 0 373 27;
#X brgb 230 214 144;
#X frgb 0 0 0;
#X border 0;
#X rounded 0;
#X shadow 0;
#X done;
#P background;
#P user panel 0 31 373 113;
#X brgb 254 241 180;
#X frgb 0 0 0;
#X border 0;
#X rounded 0;
#X shadow 0;
#X done;
#P background;
#P hidden connect 7 0 8 0;
#P hidden connect 2 0 3 0;
#P hidden connect 5 0 4 0;
#P hidden connect 9 0 10 0;
#P hidden connect 6 0 11 0;
#P hidden connect 10 0 11 0;
#P hidden connect 4 0 11 0;
#P hidden connect 3 0 11 0;
#P hidden connect 8 0 11 0;
#P pop;
