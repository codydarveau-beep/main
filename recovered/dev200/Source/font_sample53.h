/* Native pixel glyphs; same Basic Info font family at every UI size. */
#ifndef MYRO_FONT_SAMPLE53_H
#define MYRO_FONT_SAMPLE53_H
#include "font_native53.h"
#include "font_crop180.h"
#include "font_policy200.h"
static void hud_glyph53(float x,float y,float w,float h,float u,float v,float uw,float vh){
 if(uw==16&&vh==16&&u>=0&&u<256&&(v<96||(v>=160&&v<256))){unsigned k=(unsigned)(u/16)+(unsigned)((v>=160?v-160:v)/16)*16;unsigned sz=ui_font_size200(w/16.f);unsigned index=(sz-7)*192+(v>=160?96:0)+k;const unsigned short*r=nativeGlyph53[index];const unsigned char*b=nativeCrop180[index];if(b[2]&&b[3])hud_quad((int)(x+.5f)-1+b[0],(int)(y+.5f)+b[1],b[2],b[3],r[0]+b[0],r[1]+b[1],b[2],b[3]);return;}
 hud_quad(x,y,w,h,u+.5f,v+.5f,uw-1.f,vh-1.f);
}
#endif
