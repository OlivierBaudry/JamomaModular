max v2;#N vpatcher 592 54 1052 397;#P origin 44 0;#P window setfont "Sans Serif" 9.;#P message 51 184 64 196617 name dumbto;#P message 129 185 152 196617 name jcom.remote.module.to;#P outlet 89 305 15 0;#P newex 44 56 93 196617 t b s;#P newex 44 101 93 196617 sprintf %s/%s;#P newex 44 283 191 196617 regexp .*:(.*);#P newex 114 160 162 196617 sprintf %s:dump;#P newex 44 132 246 196617 t b s b;#P message 280 213 152 196617 name jcom.remote.module.from;#P message 44 222 59 196617 name dumb;#P newex 44 253 188 196617 jcom.receive dumb;#P newex 114 213 161 196617 jcom.send dumbto;#P inlet 61 75 15 0;#P inlet 44 36 15 0;#P outlet 21 134 15 0;#P window linecount 2;#P comment 251 281 161 196617 shouldn't we replace the first star by the parameter's name ???;#P connect 11 0 1 0;#P connect 2 0 12 0;#P connect 12 0 11 0;#P connect 3 0 11 0;#P connect 11 0 8 0;#P connect 8 0 6 0;#P connect 6 0 5 0;#P fasten 7 0 5 0 285 246 49 246;#P connect 5 0 10 0;#P fasten 8 0 15 0 49 166 56 166;#P connect 10 1 13 0;#P connect 8 1 9 0;#P connect 9 0 4 0;#P connect 14 0 4 0;#P fasten 15 0 4 0 56 206 119 206;#P connect 12 1 11 1;#P fasten 8 2 14 0 285 179 134 179;#P connect 8 2 7 0;#P pop;