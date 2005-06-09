max v2;
#N vpatcher 341 385 1013 720;
#P window setfont "Sans Serif" 9.;
#P window linecount 1;
#P hidden message 103 87 43 196617 autodoc;
#B color 3;
#P window linecount 2;
#P hidden newex 9 250 270 196617 jmod.message $0_ jit.wake @description "Send messages directly to the internal jit.wake object from Jitter";
#P objectname jmod.parameter.mxb[5];
#P window linecount 1;
#P comment 115 20 32 196617 bleed;
#P comment 120 34 26 196617 gain;
#P comment 77 46 62 196617 normalize;
#P user radiogroup 62 44 79 16;
#X size 1;
#X offset 16;
#X inactive 0;
#X itemtype 1;
#X flagmode 0;
#X set 0;
#X done;
#P window linecount 2;
#P hidden newex 309 131 232 196617 jmod.parameter $0_ normalize @type toggle @description "Switches normalization on and off";
#P objectname jmod.parameter.mxb;
#P flonum 143 18 35 9 0 0 8224 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 143 32 35 9 0 0 8224 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P hidden newex 309 3 274 196617 jmod.parameter $0_ bleed @type msg_float @ramp 1 @description "Sets convolution kernel value for all colors";
#P objectname jmod.parameter.mxb[4];
#P hidden newex 309 35 235 196617 jmod.parameter $0_ gain @type msg_float @ramp 1 @description "The gain level for all colors";
#P objectname jmod.parameter.mxb[3];
#P flonum 65 18 35 9 0 0 8224 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P window linecount 1;
#P comment 5 20 65 196617 feedforward;
#P flonum 65 32 35 9 0 0 8224 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P comment 22 34 48 196617 feedback;
#P window linecount 2;
#P hidden newex 309 99 258 196617 jmod.parameter $0_ feedback @type msg_float @ramp 1 @description "The feedback value for all colors";
#P objectname jmod.parameter.mxb[1];
#P window linecount 3;
#P hidden newex 217 113 79 196617 pattrstorage @autorestore 0 @savemode 0;
#X client_rect 0 0 640 240;
#X storage_rect 0 0 640 240;
#P objectname jmod.wake%;
#P window linecount 1;
#P hidden comment 117 217 75 196617 VIDEO OUTPUT;
#P hidden outlet 102 217 13 0;
#P hidden inlet 174 169 13 0;
#P hidden comment 189 169 65 196617 VIDEO INPUT;
#P hidden newex 102 190 82 196617 jmod.wake%.alg;
#P window linecount 2;
#P hidden message 18 163 72 196617 \; jmod.init bang;
#B color 3;
#P window linecount 1;
#P hidden comment 14 84 79 196617 command input;
#P window linecount 4;
#P hidden newex 0 109 214 196617 jmod.hub $0_ jmod.wake% @size 1U-half @module_type video @library_type jitter @num_inputs 1 @num_outputs 1 "Video feedback with convolution for trippy effects";
#P hidden outlet 0 171 13 0;
#P hidden inlet 0 84 13 0;
#P bpatcher 0 0 256 60 0 0 jmod.gui.mxt 0 $0_;
#P objectname jmod.gui.1Uh.v.mxb;
#P window linecount 2;
#P hidden newex 309 67 275 196617 jmod.parameter $0_ feedforward @type msg_float @ramp 1 @description "The feedforward value for all colors";
#P objectname jmod.parameter.mxb[2];
#P hidden fasten 7 0 1 0 107 211 303 211 303 -16 5 -16;
#P hidden connect 28 0 4 0;
#P hidden connect 2 0 4 0;
#P hidden connect 4 0 3 0;
#P hidden connect 22 0 23 0;
#P hidden connect 0 0 17 0;
#P hidden connect 13 0 15 0;
#P hidden connect 4 1 7 0;
#P hidden connect 7 0 10 0;
#P hidden connect 19 0 21 0;
#P hidden connect 18 0 20 0;
#P hidden connect 9 0 7 1;
#P hidden connect 12 0 4 1;
#P hidden connect 4 2 12 0;
#P hidden connect 21 0 19 0;
#P hidden connect 20 0 18 0;
#P hidden connect 17 0 0 0;
#P hidden connect 15 0 13 0;
#P hidden connect 23 0 22 0;
#P pop;
