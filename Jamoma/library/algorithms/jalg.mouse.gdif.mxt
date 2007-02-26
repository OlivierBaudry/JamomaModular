max v2;#N vpatcher 193 80 1198 742;#P origin 99 -15;#P window setfont "Sans Serif" 9.;#N vpatcher 34 163 1187 599;#P origin 0 -5;#P window setfont "Sans Serif" 9.;#P window linecount 0;#P newex 924 200 67 196617 slide 10. 10.;#P newex 790 200 67 196617 slide 10. 10.;#N vpatcher 10 59 269 406;#P window setfont "Sans Serif" 9.;#P newex 92 235 34 196617 * -1.;#P newex 144 46 58 196617 r jcom.init;#P newex 92 212 27 196617 / 0.;#P newex 55 212 27 196617 / 0.;#P newex 123 105 76 196617 unpack 0 0 0 0;#P button 123 46 15 0;#P newex 123 75 58 196617 screensize;#P inlet 55 46 15 0;#P inlet 92 46 15 0;#P outlet 55 260 15 0;#P outlet 92 260 15 0;#P connect 3 0 7 0;#P connect 7 0 1 0;#P fasten 6 2 7 1 77 157;#P connect 2 0 8 0;#P connect 8 0 10 0;#P connect 10 0 0 0;#P connect 6 3 8 1;#P connect 5 0 4 0;#P fasten 9 0 4 0 149 69 128 69;#P connect 4 0 6 0;#P pop;#P newobj 790 170 144 196617 p normalize;#P newex 924 146 29 196617 gate;#P newex 790 146 29 196617 gate;#P window linecount 2;#P newex 790 307 301 196617 jcom.return gdif/performance/fluidity @type msg_float @range 0. 1. @description "Fluidity of movements (legato-staccato)";#P newex 790 256 274 196617 jcom.return gdif/performance/dynamics @type msg_float @range 0. 1. @description "Dynamic level (pp-FF)";#P window linecount 1;#P newex 790 231 144 196617 cartopol;#P newex 943 95 101 196617 r $0_delta_vertical;#P newex 809 95 110 196617 r $0_delta_horizontal;#P newex 519 241 86 196617 scale 0. 1. -1. 1.;#P newex 346 241 86 196617 scale 0. 1. -1. 1.;#P newex 19 53 178 196617 jcom.oscroute /on /unit /description;#P newex 538 95 104 196617 r $0_vertical;#P newex 365 95 113 196617 r $0_horizontal;#P newex 90 95 96 196617 r $0_button;#P newex 519 146 29 196617 gate;#P newex 346 146 29 196617 gate;#P inlet 19 26 15 0;#P toggle 19 116 15 0;#P newex 71 146 29 196617 gate;#N vpatcher 532 157 913 485;#P window setfont "Sans Serif" 9.;#P newex 144 46 58 196617 r jcom.init;#P newex 92 184 23 196617 abs;#P newex 92 160 27 196617 -;#P newex 92 212 27 196617 / 0.;#P newex 55 212 27 196617 / 0.;#P newex 123 105 76 196617 unpack 0 0 0 0;#P button 123 46 15 0;#P newex 123 75 58 196617 screensize;#P inlet 55 46 15 0;#P inlet 92 46 15 0;#P outlet 55 260 15 0;#P outlet 92 260 15 0;#P comment 223 80 100 196617 Finds the number of pixels of the screen and uses his to calculate absolute position on screen.;#P connect 4 0 8 0;#P connect 8 0 2 0;#P fasten 7 2 8 1 77 157;#P connect 3 0 10 0;#P connect 10 0 11 0;#P connect 11 0 9 0;#P connect 9 0 1 0;#P connect 7 3 10 1;#P connect 7 3 9 1;#P connect 6 0 5 0;#P fasten 12 0 5 0 149 69 128 69;#P connect 5 0 7 0;#P pop;#P newobj 346 195 183 196617 p normalize;#P connect 3 0 9 0;#P connect 9 0 2 0;#P fasten 2 0 1 0 24 137 76 137;#P connect 6 0 1 1;#P fasten 2 0 4 0 24 137 351 137;#P connect 4 0 0 0;#P connect 0 0 10 0;#P connect 7 0 4 1;#P fasten 2 0 5 0 24 137 524 137;#P connect 5 0 0 1;#P connect 0 1 11 0;#P connect 8 0 5 1;#P fasten 2 0 17 0 24 133 795 133;#P connect 17 0 19 0;#P connect 19 0 20 0;#P connect 20 0 14 0;#P connect 14 0 15 0;#P connect 14 1 16 0;#P connect 12 0 17 1;#P fasten 2 0 18 0 24 133 929 133;#P connect 18 0 19 1;#P connect 19 1 21 0;#P connect 21 0 14 1;#P connect 13 0 18 1;#P pop;#P newobj 756 223 62 196617 p gdif-meta;#N vpatcher 49 159 923 666;#P origin 0 -5;#P window setfont "Sans Serif" 9.;#P newex 519 241 86 196617 scale 0. 1. -1. 1.;#P newex 346 241 86 196617 scale 0. 1. -1. 1.;#P newex 19 53 178 196617 jcom.oscroute /on /unit /description;#P newex 538 95 104 196617 r $0_vertical;#P newex 365 95 113 196617 r $0_horizontal;#P newex 90 95 96 196617 r $0_button;#P newex 519 146 29 196617 gate;#P newex 346 146 29 196617 gate;#P inlet 19 26 15 0;#P toggle 19 116 15 0;#P newex 71 146 29 196617 gate;#P window linecount 2;#P newex 71 371 261 196617 jcom.return gdif/device/mouse/button/2/press @type toggle @range 0 1 @description "Button up or down";#P newex 519 422 298 196617 jcom.return gdif/body/device/mouse/location/vertical @type msg_float @range 0. 1. @description "Vertical position of hand";#P newex 346 371 308 196617 jcom.return gdif/device/mouse/location/horizontal @type msg_float @range 0. 1. @description "Horizontal position of hand";#P window linecount 1;#N vpatcher 532 157 913 485;#P window setfont "Sans Serif" 9.;#P newex 144 46 58 196617 r jcom.init;#P newex 92 184 23 196617 abs;#P newex 92 160 27 196617 -;#P newex 92 212 27 196617 / 0.;#P newex 55 212 27 196617 / 0.;#P newex 123 105 76 196617 unpack 0 0 0 0;#P button 123 46 15 0;#P newex 123 75 58 196617 screensize;#P inlet 55 46 15 0;#P inlet 92 46 15 0;#P outlet 55 260 15 0;#P outlet 92 260 15 0;#P comment 223 80 100 196617 Finds the number of pixels of the screen and uses his to calculate absolute position on screen.;#P connect 4 0 8 0;#P connect 8 0 2 0;#P fasten 7 2 8 1 77 157;#P connect 3 0 10 0;#P connect 10 0 11 0;#P connect 11 0 9 0;#P connect 9 0 1 0;#P connect 7 3 10 1;#P connect 7 3 9 1;#P fasten 12 0 5 0 149 69 128 69;#P connect 6 0 5 0;#P connect 5 0 7 0;#P pop;#P newobj 346 195 183 196617 p normalize;#P connect 6 0 12 0;#P connect 12 0 5 0;#P fasten 5 0 4 0 24 137 76 137;#P connect 4 0 3 0;#P connect 9 0 4 1;#P fasten 5 0 7 0 24 137 351 137;#P connect 7 0 0 0;#P connect 0 0 13 0;#P connect 13 0 1 0;#P connect 10 0 7 1;#P fasten 5 0 8 0 24 137 524 137;#P connect 8 0 0 1;#P connect 0 1 14 0;#P connect 14 0 2 0;#P connect 11 0 8 1;#P pop;#P newobj 594 223 69 196617 p gdif-device;#N vpatcher 18 137 1171 573;#P origin 0 -5;#P window setfont "Sans Serif" 9.;#P newex 924 200 67 196617 slide 10. 10.;#P newex 790 200 67 196617 slide 10. 10.;#P window linecount 0;#N vpatcher 10 59 269 406;#P window setfont "Sans Serif" 9.;#P newex 92 235 34 196617 * -1.;#P newex 144 46 58 196617 r jcom.init;#P newex 92 212 27 196617 / 0.;#P newex 55 212 27 196617 / 0.;#P newex 123 105 76 196617 unpack 0 0 0 0;#P button 123 46 15 0;#P newex 123 75 58 196617 screensize;#P inlet 55 46 15 0;#P inlet 92 46 15 0;#P outlet 55 260 15 0;#P outlet 92 260 15 0;#P connect 3 0 7 0;#P connect 7 0 1 0;#P fasten 6 2 7 1 77 157;#P connect 2 0 8 0;#P connect 8 0 10 0;#P connect 10 0 0 0;#P connect 6 3 8 1;#P fasten 9 0 4 0 149 69 128 69;#P connect 5 0 4 0;#P connect 4 0 6 0;#P pop;#P newobj 790 170 144 196617 p normalize;#P newex 924 146 29 196617 gate;#P newex 790 146 29 196617 gate;#P window linecount 2;#P newex 790 307 301 196617 jcom.return gdif/performance/fluidity @type msg_float @range 0. 1. @description "Fluidity of movements (legato-staccato)";#P newex 790 256 274 196617 jcom.return gdif/performance/dynamics @type msg_float @range 0. 1. @description "Dynamic level (pp-FF)";#P window linecount 1;#P newex 790 231 144 196617 cartopol;#P newex 943 95 101 196617 r $0_delta_vertical;#P newex 809 95 110 196617 r $0_delta_horizontal;#P newex 519 241 86 196617 scale 0. 1. -1. 1.;#P newex 346 241 86 196617 scale 0. 1. -1. 1.;#P newex 19 53 178 196617 jcom.oscroute /on /unit /description;#P newex 538 95 104 196617 r $0_vertical;#P newex 365 95 113 196617 r $0_horizontal;#P newex 90 95 96 196617 r $0_button;#P newex 519 146 29 196617 gate;#P newex 346 146 29 196617 gate;#P inlet 19 26 15 0;#P toggle 19 116 15 0;#P newex 71 146 29 196617 gate;#N vpatcher 532 157 913 485;#P window setfont "Sans Serif" 9.;#P newex 144 46 58 196617 r jcom.init;#P newex 92 184 23 196617 abs;#P newex 92 160 27 196617 -;#P newex 92 212 27 196617 / 0.;#P newex 55 212 27 196617 / 0.;#P newex 123 105 76 196617 unpack 0 0 0 0;#P button 123 46 15 0;#P newex 123 75 58 196617 screensize;#P inlet 55 46 15 0;#P inlet 92 46 15 0;#P outlet 55 260 15 0;#P outlet 92 260 15 0;#P comment 223 80 100 196617 Finds the number of pixels of the screen and uses his to calculate absolute position on screen.;#P connect 4 0 8 0;#P connect 8 0 2 0;#P fasten 7 2 8 1 77 157;#P connect 3 0 10 0;#P connect 10 0 11 0;#P connect 11 0 9 0;#P connect 9 0 1 0;#P connect 7 3 10 1;#P connect 7 3 9 1;#P fasten 12 0 5 0 149 69 128 69;#P connect 6 0 5 0;#P connect 5 0 7 0;#P pop;#P newobj 346 195 183 196617 p normalize;#P connect 3 0 9 0;#P connect 9 0 2 0;#P fasten 2 0 1 0 24 137 76 137;#P connect 6 0 1 1;#P fasten 2 0 4 0 24 137 351 137;#P connect 4 0 0 0;#P connect 0 0 10 0;#P connect 7 0 4 1;#P fasten 2 0 5 0 24 137 524 137;#P connect 5 0 0 1;#P connect 0 1 11 0;#P connect 8 0 5 1;#P fasten 2 0 17 0 24 133 795 133;#P connect 17 0 19 0;#P connect 19 0 20 0;#P connect 20 0 14 0;#P connect 14 0 15 0;#P connect 14 1 16 0;#P connect 12 0 17 1;#P fasten 2 0 18 0 24 133 929 133;#P connect 18 0 19 1;#P connect 19 1 21 0;#P connect 21 0 14 1;#P connect 13 0 18 1;#P pop;#P newobj 702 192 97 196617 p gdif-performance;#P newex 159 66 27 196617 + 1;#P newex 159 90 101 196617 gate 2 1;#P toggle 250 122 15 0;#P number 298 122 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;#P newex 250 155 58 196617 metro 100;#P newex 699 378 119 196617 r $0_delta_vertical;#P newex 565 378 128 196617 r $0_delta_horizontal;#P newex 248 254 101 196617 s $0_delta_vertical;#P newex 203 229 110 196617 s $0_delta_horizontal;#P newex 414 378 91 196617 r $0_vertical;#P newex 308 378 100 196617 r $0_horizontal;#P newex 50 378 83 196617 r $0_button;#N vpatcher 10 59 269 406;#P window setfont "Sans Serif" 9.;#P newex 144 46 58 196617 r jcom.init;#P newex 92 184 23 196617 abs;#P newex 92 160 27 196617 -;#P newex 92 212 27 196617 / 0.;#P newex 55 212 27 196617 / 0.;#P newex 123 105 76 196617 unpack 0 0 0 0;#P button 123 46 15 0;#P newex 123 75 58 196617 screensize;#P inlet 55 46 15 0;#P inlet 92 46 15 0;#P outlet 55 260 15 0;#P outlet 92 260 15 0;#P connect 3 0 7 0;#P connect 7 0 1 0;#P fasten 6 2 7 1 77 157;#P connect 2 0 9 0;#P connect 9 0 10 0;#P connect 10 0 8 0;#P connect 8 0 0 0;#P connect 6 3 9 1;#P connect 6 3 8 1;#P connect 5 0 4 0;#P fasten 11 0 4 0 149 69 128 69;#P connect 4 0 6 0;#P pop;#P newobj 308 401 116 196617 p normalize;#P window linecount 2;#P newex 308 456 229 196617 jcom.return position/y @type msg_float @range 0. 1. @description "Vertical position of mouse";#P newex 308 423 232 196617 jcom.return position/x @type msg_float @range 0. 1. @description "Horizontal position of mouse";#P newex 50 423 250 196617 jcom.return button @type toggle @range 0 1 @description "Mouse button";#P window linecount 1;#N vpatcher 18 137 1201 646;#P origin 0 -5;#P window setfont "Sans Serif" 9.;#P window linecount 0;#N vpatcher 10 59 269 406;#P window setfont "Sans Serif" 9.;#P newex 92 235 34 196617 * -1.;#P newex 144 46 58 196617 r jcom.init;#P newex 92 212 27 196617 / 0.;#P newex 55 212 27 196617 / 0.;#P newex 123 105 76 196617 unpack 0 0 0 0;#P button 123 46 15 0;#P newex 123 75 58 196617 screensize;#P inlet 55 46 15 0;#P inlet 92 46 15 0;#P outlet 55 260 15 0;#P outlet 92 260 15 0;#P connect 3 0 7 0;#P connect 7 0 1 0;#P fasten 6 2 7 1 77 157;#P connect 2 0 8 0;#P connect 8 0 10 0;#P connect 10 0 0 0;#P connect 6 3 8 1;#P connect 5 0 4 0;#P fasten 9 0 4 0 149 69 128 69;#P connect 4 0 6 0;#P pop;#P newobj 790 170 144 196617 p normalize;#P newex 924 146 29 196617 gate;#P newex 790 146 29 196617 gate;#P window linecount 2;#P newex 790 270 322 196617 jcom.return gdif/body/hand/right/motion/direction @type msg_float @range 0. 1. @description "Direction of motion in radians";#P newex 790 219 323 196617 jcom.return gdif/body/hand/right/motion/quantity @type msg_float @range 0. 1. @description "Quantity of Motion (QoM) of hand";#P window linecount 1;#P newex 790 194 144 196617 cartopol;#P newex 943 95 101 196617 r $0_delta_vertical;#P newex 809 95 110 196617 r $0_delta_horizontal;#P window linecount 2;#P newex 699 371 298 196617 jcom.return gdif/body/hand/right/orientation @type msg_float @range 0. 1. @description "Vertical position of hand";#P newex 662 327 287 196617 jcom.return gdif/body/hand/right/distance @type msg_float @range 0. 1. @description "Horizontal position of hand";#P window linecount 1;#P newex 662 303 47 196617 cartopol;#P newex 519 241 86 196617 scale 0. 1. -1. 1.;#P newex 346 241 86 196617 scale 0. 1. -1. 1.;#P newex 19 53 178 196617 jcom.oscroute /on /unit /description;#P newex 538 95 104 196617 r $0_vertical;#P newex 365 95 113 196617 r $0_horizontal;#P newex 90 95 96 196617 r $0_button;#P newex 519 146 29 196617 gate;#P newex 346 146 29 196617 gate;#P inlet 19 26 15 0;#P toggle 19 116 15 0;#P newex 71 146 29 196617 gate;#P window linecount 2;#P newex 71 371 272 196617 jcom.return gdif/body/hand/right/finger/2/press @type toggle @range 0 1 @description "Finger up or down";#P newex 519 422 298 196617 jcom.return gdif/body/hand/right/location/vertical @type msg_float @range 0. 1. @description "Vertical position of hand";#P newex 346 371 308 196617 jcom.return gdif/body/hand/right/location/horizontal @type msg_float @range 0. 1. @description "Horizontal position of hand";#P window linecount 1;#N vpatcher 532 157 913 485;#P window setfont "Sans Serif" 9.;#P newex 144 46 58 196617 r jcom.init;#P newex 92 184 23 196617 abs;#P newex 92 160 27 196617 -;#P newex 92 212 27 196617 / 0.;#P newex 55 212 27 196617 / 0.;#P newex 123 105 76 196617 unpack 0 0 0 0;#P button 123 46 15 0;#P newex 123 75 58 196617 screensize;#P inlet 55 46 15 0;#P inlet 92 46 15 0;#P outlet 55 260 15 0;#P outlet 92 260 15 0;#P comment 223 80 100 196617 Finds the number of pixels of the screen and uses his to calculate absolute position on screen.;#P connect 4 0 8 0;#P connect 8 0 2 0;#P fasten 7 2 8 1 77 157;#P connect 3 0 10 0;#P connect 10 0 11 0;#P connect 11 0 9 0;#P connect 9 0 1 0;#P connect 7 3 10 1;#P connect 7 3 9 1;#P connect 6 0 5 0;#P fasten 12 0 5 0 149 69 128 69;#P connect 5 0 7 0;#P pop;#P newobj 346 195 183 196617 p normalize;#P connect 6 0 12 0;#P connect 12 0 5 0;#P fasten 5 0 4 0 24 137 76 137;#P connect 4 0 3 0;#P connect 9 0 4 1;#P fasten 5 0 7 0 24 137 351 137;#P connect 7 0 0 0;#P connect 0 0 13 0;#P connect 13 0 1 0;#P connect 10 0 7 1;#P fasten 5 0 8 0 24 137 524 137;#P connect 8 0 0 1;#P connect 0 1 14 0;#P connect 14 0 2 0;#P connect 11 0 8 1;#P connect 13 0 15 0;#P connect 15 0 16 0;#P connect 14 0 15 1;#P connect 15 1 17 0;#P fasten 5 0 23 0 24 133 795 133;#P connect 23 0 25 0;#P connect 25 0 20 0;#P connect 20 0 21 0;#P connect 20 1 22 0;#P connect 18 0 23 1;#P fasten 5 0 24 0 24 133 929 133;#P connect 24 0 25 1;#P connect 25 1 20 1;#P connect 19 0 24 1;#P pop;#P newobj 580 192 61 196617 p gdif-body;#P newex 158 277 102 196617 s $0_vertical;#P newex 113 254 111 196617 s $0_horizontal;#P newex 68 229 94 196617 s $0_button;#P newex 432 157 370 196617 jcom.oscroute /raw /cooked /body /device /environment /performance /meta;#N vpatcher 202 309 1171 681;#P origin 0 -5;#P window setfont "Sans Serif" 9.;#P window linecount 1;#P newex 19 53 178 196617 jcom.oscroute /on /unit /description;#P newex 676 95 103 196617 r $0_vertical;#P newex 365 95 112 196617 r $0_horizontal;#P newex 90 95 95 196617 r $0_button;#P newex 657 146 29 196617 gate;#P newex 346 146 29 196617 gate;#P inlet 19 26 15 0;#P toggle 19 116 15 0;#P newex 71 146 29 196617 gate;#P window linecount 2;#P newex 71 241 236 196617 jcom.return gdif/cooked/button @type toggle @range 0 1 @description "Mouse button on or off";#P newex 657 241 282 196617 jcom.return gdif/cooked/location/vertical @type msg_float @range 0. 1. @description "Vertical position of mouse";#P newex 346 241 291 196617 jcom.return gdif/cooked/location/horizontal @type msg_float @range 0. 1. @description "Horizontal position of mouse";#P window linecount 1;#N vpatcher 532 157 913 485;#P window setfont "Sans Serif" 9.;#P newex 144 46 58 196617 r jcom.init;#P newex 92 184 23 196617 abs;#P newex 92 160 27 196617 -;#P newex 92 212 27 196617 / 0.;#P newex 55 212 27 196617 / 0.;#P newex 123 105 76 196617 unpack 0 0 0 0;#P button 123 46 15 0;#P newex 123 75 58 196617 screensize;#P inlet 55 46 15 0;#P inlet 92 46 15 0;#P outlet 55 260 15 0;#P outlet 92 260 15 0;#P comment 223 80 100 196617 Finds the number of pixels of the screen and uses his to calculate absolute position on screen.;#P connect 4 0 8 0;#P connect 8 0 2 0;#P fasten 7 2 8 1 77 157;#P connect 3 0 10 0;#P connect 10 0 11 0;#P connect 11 0 9 0;#P connect 9 0 1 0;#P connect 7 3 10 1;#P connect 7 3 9 1;#P fasten 12 0 5 0 149 69 128 69;#P connect 6 0 5 0;#P connect 5 0 7 0;#P pop;#P newobj 346 195 321 196617 p normalize;#P window linecount 0;#P comment 71 322 391 196617 These are the pre-processed data values \, based on doing simple filtering and scaling.;#P connect 7 0 13 0;#P connect 13 0 6 0;#P fasten 6 0 5 0 24 137 76 137;#P connect 5 0 4 0;#P connect 10 0 5 1;#P fasten 6 0 8 0 24 137 351 137;#P connect 8 0 1 0;#P connect 1 0 2 0;#P connect 11 0 8 1;#P fasten 6 0 9 0 24 137 662 137;#P connect 9 0 1 1;#P connect 1 1 3 0;#P connect 12 0 9 1;#P pop;#P newobj 503 192 70 196617 p gdif-cooked;#N vpatcher 203 231 1232 612;#P origin 0 -18;#P window setfont "Sans Serif" 9.;#P window linecount 1;#P newex 679 94 99 196617 r $0_vertical;#P newex 368 94 108 196617 r $0_horizontal;#P newex 93 94 91 196617 r $0_button;#P button 25 186 15 0;#P window linecount 0;#P newex 29 50 178 196617 jcom.oscroute /on /unit /description;#P window linecount 1;#P message 25 242 48 196617 "Pixels";#P window linecount 0;#P message 25 215 299 196617 "These are the raw values coming out of the mousestate object";#P window linecount 1;#P newex 660 134 29 196617 gate;#P newex 349 134 29 196617 gate;#P inlet 29 29 15 0;#P toggle 29 104 15 0;#P window linecount 0;#P newex 74 134 29 196617 gate;#P window linecount 2;#P newex 74 161 223 196617 jcom.return gdif/raw/button @type toggle @range 0 1 @description "Mouse button on off";#P newex 660 161 270 196617 jcom.return gdif/raw/location/vertical @type msg_int @range 0 2000 @description "Vertical position of mouse";#P newex 349 161 280 196617 jcom.return gdif/raw/location/horizontal @type msg_int @range 0 2000 @description "Horizontal position of mouse";#P connect 11 0 8 0;#P connect 5 0 10 0;#P connect 10 0 4 0;#P fasten 4 0 3 0 34 125 79 125;#P connect 3 0 2 0;#P connect 12 0 3 1;#P fasten 4 0 6 0 34 125 354 125;#P connect 6 0 0 0;#P connect 13 0 6 1;#P fasten 4 0 7 0 34 125 665 125;#P connect 7 0 1 0;#P connect 14 0 7 1;#P pop;#P newobj 432 192 58 196617 p gdif-raw;#P newex 123 155 21 196617 t 1;#P newex 68 155 50 196617 t reset 0;#P newex 68 120 41 196617 sel 0 1;#P toggle 21 198 15 0;#P newex 21 225 29 196617 gate;#P newex 21 246 43 196617 change;#P message 26 155 34 196617 zero;#P newex 565 496 47 196617 cartopol;#N vpatcher 10 59 269 406;#P window setfont "Sans Serif" 9.;#P newex 92 235 34 196617 * -1.;#P newex 144 46 58 196617 r jcom.init;#P newex 92 212 27 196617 / 0.;#P newex 55 212 27 196617 / 0.;#P newex 123 105 76 196617 unpack 0 0 0 0;#P button 123 46 15 0;#P newex 123 75 58 196617 screensize;#P inlet 55 46 15 0;#P inlet 92 46 15 0;#P outlet 55 260 15 0;#P outlet 92 260 15 0;#P connect 3 0 7 0;#P connect 7 0 1 0;#P fasten 6 2 7 1 77 157;#P connect 2 0 8 0;#P connect 8 0 10 0;#P connect 10 0 0 0;#P connect 6 3 8 1;#P fasten 9 0 4 0 149 69 128 69;#P connect 5 0 4 0;#P connect 4 0 6 0;#P pop;#P newobj 565 401 144 196617 p normalize;#P window linecount 2;#P newex 602 523 296 196617 jcom.return delta/angle @type msg_float @range -3.14 3.14 @description "Angle (in radians) of relative position of mouse.";#P window linecount 1;#P newex 159 120 41 196617 sel 1 0;#P message 193 155 40 196617 nopoll;#P message 159 155 30 196617 poll;#P window linecount 2;#P newex 565 568 399 196617 jcom.return delta/magnitude @type msg_float @range 0. 0.4 @description "Mangitude (in screen percentage) of relative position of mouse (sum of horizontal and vertical).";#P newex 566 456 241 196617 jcom.return delta/y @type msg_float @range -0.2 0.2 @description "Vertical delta position of mouse";#P newex 565 423 251 196617 jcom.return delta/x @type msg_float @range -0.2 0.2 @description "Horizontal delta position of mouse";#P window linecount 1;#P newex 68 199 193 196617 mousestate;#B color 5;#P newex 68 45 468 196617 jcom.oscroute /reference /mode /on /sample_rate /gdif;#P inlet 68 21 15 0;#P comment 50 346 110 196617 Old-style messaging...;#P connect 18 1 16 0;#P connect 19 0 16 0;#P connect 16 0 15 0;#P connect 15 0 14 0;#P fasten 14 1 13 0 42 269 11 269 11 149 31 149;#P fasten 3 0 15 1 73 221 45 221;#P connect 31 0 27 0;#P connect 1 0 2 0;#P connect 2 0 17 0;#P connect 17 0 18 0;#P fasten 7 0 3 0 164 184 73 184;#P fasten 8 0 3 0 198 184 73 184;#P fasten 13 0 3 0 31 184 73 184;#P fasten 18 0 3 0 73 185 73 185;#P fasten 38 0 3 0 255 185 73 185;#P connect 3 0 23 0;#P connect 3 1 24 0;#P fasten 17 1 19 0 88 146 128 146;#P connect 3 2 25 0;#P connect 2 1 42 0;#P connect 42 0 41 0;#P connect 41 0 9 0;#P connect 9 0 7 0;#P connect 9 1 8 0;#P connect 3 3 34 0;#P connect 3 4 35 0;#P connect 2 2 41 1;#P connect 41 1 40 0;#P connect 40 0 38 0;#P connect 2 3 39 0;#P connect 39 0 38 1;#P connect 32 0 30 0;#P connect 30 0 28 0;#P connect 30 1 29 0;#P connect 33 0 30 1;#P connect 2 4 22 0;#P connect 22 0 20 0;#P connect 22 1 21 0;#P connect 36 0 11 0;#P connect 11 0 4 0;#P connect 11 0 12 0;#P connect 12 0 6 0;#P connect 11 1 5 0;#P connect 22 2 26 0;#P connect 22 3 44 0;#P connect 11 1 12 1;#P connect 12 1 10 0;#P connect 37 0 11 1;#P connect 22 5 43 0;#P connect 22 6 45 0;#P pop;