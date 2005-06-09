max v2;
#N vpatcher 0 478 498 747;
#P window setfont "Sans Serif" 9.;
#P window linecount 1;
#P hidden message 106 87 43 196617 autodoc;
#B color 3;
#P window linecount 3;
#P hidden newex 0 109 345 196617 jmod.hub $0_ jmod.op% @size 1U-half @module_type video @library_type jitter @num_inputs 2 @num_outputs 1 @description "Perform mathematical operations using two video inputs as the operands";
#P user ubumenu 64 29 60 196617 0 1 1 0;
#X add pass;
#X add *;
#X add /;
#X add +;
#X add -;
#X add +m;
#X add -m;
#X add %;
#X add min;
#X add max;
#X add abs;
#X add avg;
#X add absdiff;
#X add !pass;
#X add !/;
#X add !-;
#X add !%;
#X add &;
#X add |;
#X add ^;
#X add ~;
#X add >>;
#X add <<;
#X add &&;
#X add ||;
#X add !;
#X add >;
#X add <;
#X add >=;
#X add <=;
#X add ==;
#X add !=;
#X add >p;
#X add <p;
#X add >=p;
#X add <=p;
#X add ==p;
#X add !=p;
#X add sin;
#X add cos;
#X add tan;
#X add asin;
#X add acos;
#X add atan;
#X add atan2;
#X add sinh;
#X add cosh;
#X add tanh;
#X add asinh;
#X add acosh;
#X add atanh;
#X add exp;
#X add exp2;
#X add ln;
#X add log2;
#X add log10;
#X add hypot;
#X add pow;
#X add sqrt;
#X add ceil;
#X add floor;
#X add round;
#X add trunc;
#X add ignore;
#X prefix_set 0 0 0 0;
#P window linecount 1;
#P comment 41 31 45 196617 op;
#P window linecount 4;
#P hidden newex 259 6 173 196617 jmod.parameter $0_ op @type menu @description "Chooses the type of operation to perform on the two video inputs to the module.";
#P objectname jmod.parameter.mxb[1];
#P window linecount 1;
#P hidden comment 182 231 75 196617 VIDEO OUTPUT;
#P hidden outlet 167 231 13 0;
#P hidden inlet 214 166 13 0;
#P hidden comment 229 166 65 196617 VIDEO INPUT;
#P hidden newex 167 188 131 196617 jmod.op%.alg;
#P window linecount 2;
#P hidden message 27 185 72 196617 \; jmod.init bang;
#B color 3;
#P window linecount 1;
#P hidden comment 14 84 79 196617 command input;
#P hidden outlet 0 171 13 0;
#P hidden inlet 0 84 13 0;
#P hidden inlet 313 166 15 0;
#P hidden comment 330 166 65 196617 VIDEO INPUT;
#P hidden comment 14 -24 79 196617 command input;
#P hidden inlet 0 -24 13 0;
#P window linecount 3;
#P hidden newex 348 109 79 196617 pattrstorage @autorestore 0 @savemode 0;
#X client_rect 0 0 640 240;
#X storage_rect 0 0 640 240;
#P objectname jmod.op%;
#P bpatcher 0 0 256 60 0 0 jmod.gui.mxt 0 $0_;
#P objectname jmod.gui.1Uh.v.mxb;
#P hidden connect 19 0 18 0;
#P hidden connect 6 0 18 0;
#P hidden connect 18 0 7 0;
#P hidden connect 15 0 17 0;
#P hidden connect 18 1 10 0;
#P hidden connect 10 0 13 0;
#P hidden connect 12 0 10 1;
#P hidden fasten 10 0 0 2 172 213 464 213 464 -7 251 -7;
#P hidden connect 17 0 15 0;
#P hidden connect 5 0 10 2;
#P hidden connect 1 0 18 1;
#P hidden connect 18 2 1 0;
#P pop;
