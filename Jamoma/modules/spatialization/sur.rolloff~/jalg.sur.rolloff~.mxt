max v2;#N vpatcher -3 81 1275 807;#P origin 34 -18;#P window setfont "Sans Serif" 9.;#P window linecount 1;#P message 898 233 54 196617 voices \$1;#P number 927 62 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;#P newex 80 86 417 196617 jcom.multi.out~;#P objectname multiout;#P newex 80 602 417 196617 jcom.multi.in~;#P objectname multiin;#P newex 779 83 98 196617 jcom.oscroute /aed;#P window linecount 3;#P newex 1025 161 98 196617 jcom.oscroute /reference_distance /roll_off;#P objectname oscroute;#P window linecount 1;#P newex 779 163 222 196617 route 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16;#P objectname route;#P newex 969 540 86 196617 prepend dspstate;#P inlet 20 49 15 0;#P newex 969 515 54 196617 dspstate~;#P newex 867 109 93 196617 jcom.pass /voices;#P outlet 80 640 15 0;#P objectname out[1];#P inlet 80 49 15 0;#P objectname in[1];#N thispatcher;#Q end;#P newobj 867 612 61 196617 thispatcher;#P newex 867 587 106 196617 js jcom.sur.rolloff.js;#P objectname javascript;#P connect 2 0 12 0;#P connect 11 0 3 0;#P fasten 6 0 10 0 25 76 784 76;#P connect 10 0 8 0;#P connect 10 1 4 0;#P connect 14 0 0 0;#P connect 4 0 0 0;#P fasten 7 0 0 0 974 577 872 577;#P connect 0 0 1 0;#P connect 13 0 14 0;#P connect 5 0 7 0;#P fasten 4 1 9 0 955 138 1030 138;#P pop;