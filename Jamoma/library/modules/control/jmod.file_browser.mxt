max v2;#N vpatcher 393 120 1165 555;#P origin -7 -40;#P window setfont "Sans Serif" 9.;#P hidden newex 469 130 86 196617 pvar folderDepth;#P window linecount 2;#P hidden newex 469 157 279 196617 jcom.parameter depth @type msg_int @range 0 9 @clipmode low;#P objectname depth;#P window linecount 1;#P hidden newex 403 102 202 196617 jcom.parameter folder @type msg_symbol;#P objectname folder;#N vpatcher 696 281 1202 685;#P window setfont "Sans Serif" 9.;#P window linecount 0;#P newex 59 306 46 196617 t l clear;#P outlet 59 341 15 0;#P inlet 59 40 15 0;#P newex 59 70 79 196617 sel 0 1 2 3 4;#P window linecount 2;#P message 98 224 266 196617 JPEG "GIF " GIFf "PNG " PNGf 8BPS TIFF PICT "SWF " BMPf "BMP " qtif "SGI " TPIC PNTG qdgx PFix PICS PICS;#P window linecount 1;#P message 85 194 334 196617 "MOV " "AVI " MooV "VfW " dvc! MPEG MPGa MPGv MPGx SWFL "SWF ";#P message 72 160 398 196617 "MP3 " "Mp3 " PLAY MPG3 SwaT MPEG AIFF AIFC "SD2 " Sd2f .WAV WAVE ULAW sfil;#P window linecount 4;#P message 59 100 322 196617 "MP3 " "Mp3 " PLAY MPG3 SwaT MPEG AIFF AIFC "SD2 " Sd2f .WAV WAVE ULAW sfil MooV "VfW " dvc! MPEG MPGa MPGv MPGx SWFL "SWF " JPEG "GIF " GIFf "PNG " PNGf 8BPS TIFF PICT "SWF " BMPf "BMP " qtif "SGI " TPIC PNTG qdgx PFix PICS PICS MIDI TEXT 3DMF;#P window linecount 1;#P newex 59 278 94 196617 prepend add_types;#P connect 6 0 5 0;#P connect 5 0 1 0;#P connect 4 0 0 0;#P connect 3 0 0 0;#P connect 2 0 0 0;#P connect 1 0 0 0;#P connect 0 0 8 0;#P connect 8 0 7 0;#P connect 8 1 7 0;#P connect 5 1 2 0;#P connect 5 2 3 0;#P connect 5 3 4 0;#P pop;#P hidden newobj 8 68 63 196617 p add-types;#P hidden newex 450 201 56 196617 pvar Type;#P window linecount 2;#P hidden newex 450 223 239 196617 jcom.parameter type @type msg_list @description "Choose between different file types";#P objectname type[1];#P window linecount 1;#P hidden newex 12 130 173 196617 jcom.parameter file @type msg_list;#P objectname file;#P hidden newex 240 130 210 196617 jcom.message number_items @type msg_int;#P hidden newex 563 22 48 196617 loadbang;#P hidden newex 500 22 58 196617 r jcom.init;#P hidden newex 500 45 54 196617 onebang 1;#P user ubumenu 8 41 53 196617 0 1 1 0;#X add all;#X add audio;#X add video;#X add pictures;#X prefix_set 0 0 <none> 0;#X pattrmode 1;#P objectname Type;#P hidden newex 500 66 57 196617 t clear set;#P button 8 21 15 0;#P objectname bt_opendialog;#P hidden newex 323 24 76 196617 opendialog fold;#P user dropfile 25 22 253 40 0 fold;#P user textedit 23 21 253 39 32896 3 9;#P user ubumenu 112 42 139 196617 0 1 1 0;#X types "MOV " MooV "AVI " JPEG "GIF " GIFf "PNG " PNGf 8BPS TIFF PICT "SWF " BMPf "BMP " qtif "SGI " TPIC PNTG qdgx PFix PICS PICS "MOV " "AVI " MooV "VfW " dvc! MPEG MPGa MPGv MPGx SWFL "SWF " clea "MP3 " "Mp3 " PLAY MPG3 SwaT MPEG AIFF AIFC "SD2 " Sd2f .WAV WAVE ULAW sfil clea JPEG "GIF " GIFf "PNG " PNGf 8BPS TIFF PICT "SWF " BMPf "BMP " qtif "SGI " TPIC PNTG;#X prefix_set 0 1 "Macintosh HD:/Users/alexanje/Movies/" 4;#X pattrmode 1;#P objectname menu;#P number 97 42 13 9 0 0 8225 3 181 181 181 221 221 221 255 255 255 0 0 0;#P objectname folderDepth;#P hidden message 97 61 48 196617 depth \$1;#P hidden newex 240 108 72 196617 route populate;#P hidden newex 387 51 74 196617 prepend prefix;#P hidden button 323 73 15 0;#P hidden newex 323 51 60 196617 prepend set;#P hidden newex 119 319 49 196617 jcom.out;#P hidden newex 119 267 45 196617 jcom.in;#P hidden message 38 178 125 196617 /documentation/generate;#P window linecount 2;#P hidden newex 16 203 357 196617 jcom.hub jmod.file_browser @size 1U-half @module_type control @description "Browsing and selecting files to send to audio or video players";#P objectname jcom.hub;#P hidden inlet 16 179 13 0;#P hidden outlet 16 316 13 0;#P window linecount 1;#P comment 70 44 34 196617 depth;#B frgb 149 149 149;#P bpatcher 0 0 256 62 0 0 jcom.gui.mxt 0 $0_;#P objectname jcom.gui.1Uh.a.stereo;#P hidden connect 20 0 28 0;#P hidden fasten 14 1 25 0 181 94 17 94;#P hidden connect 3 0 4 0;#P hidden fasten 5 0 4 0 43 197 21 197;#P hidden connect 4 0 2 0;#P hidden connect 8 0 15 0;#P lcolor 3;#P hidden connect 9 0 15 0;#P lcolor 3;#P hidden connect 19 1 15 0;#P lcolor 3;#P hidden connect 13 0 12 0;#P hidden connect 28 0 14 0;#P hidden connect 25 0 14 0;#P hidden connect 10 0 14 0;#P lcolor 3;#P hidden connect 12 0 14 0;#P lcolor 3;#P hidden connect 19 0 14 0;#P lcolor 3;#P hidden connect 14 2 11 0;#P hidden connect 11 0 24 0;#P hidden connect 18 0 17 0;#P lcolor 3;#P hidden connect 29 1 8 0;#P hidden connect 17 0 8 0;#P hidden connect 16 0 8 0;#P lcolor 3;#P hidden connect 8 0 9 0;#P hidden connect 29 1 10 0;#P hidden connect 16 0 10 0;#P lcolor 3;#P hidden fasten 17 0 10 0 328 46 392 46;#P hidden fasten 26 0 27 0 455 256 444 256 444 197 455 197;#P hidden connect 27 0 26 0;#P hidden fasten 30 0 31 0 474 183 463 183 463 125 474 125;#P hidden connect 31 0 30 0;#P hidden fasten 23 0 21 0 568 42 505 42;#P hidden connect 22 0 21 0;#P hidden connect 21 0 19 0;#P pop;