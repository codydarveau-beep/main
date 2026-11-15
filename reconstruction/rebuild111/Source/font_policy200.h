/* MIT. CRT readability: native7/8/9px text advances one atlas size.
 * Native10/11px stays unchanged; all sizes remain integer-sampled. */
#ifndef MYRO_FONT_POLICY200_H
#define MYRO_FONT_POLICY200_H
static unsigned ui_font_size200(float scale){int size=(int)(11*scale+.5f);if(size<7)size=7;if(size>11)size=11;if(size<10)size++;return(unsigned)size;}
static float ui_font_smaller200(float scale){unsigned size=ui_font_size200(scale);if(size<=8)return 7.f/11.f;/* Invert the readability mapping rather than applying it twice. */return(size==11?9.f:size-2.f)/11.f;}
#endif
