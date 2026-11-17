
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "item_count46.h"
#include "skin_data.h"
#define SKIN_H 2048
#define ITEM_ICON_BASE52 16384
static void*skinTexture;static float uv[4];static unsigned draws;
static const unsigned short dynamic[4]={300,1700,32,24};
static const unsigned short*item_icon_rect52(int id){return id==ITEM_ICON_BASE52?dynamic:NULL;}
static int skin_item_fallback52(int id){return id==ITEM_ICON_BASE52+1?108:-1;}
static void hud_setup(void*t,unsigned w,unsigned h,unsigned pitch,unsigned fmt,int blend){assert(t==skinTexture&&w==512&&h==2048&&pitch==2048&&fmt==0x1122a&&blend==1);}
static void hud_quad(float x,float y,float w,float h,float u,float v,float uw,float vh){assert(x==12&&y==13&&w==22&&h==22);uv[0]=u;uv[1]=v;uv[2]=uw;uv[3]=vh;draws++;}
#include "actual_skin_icon268.inc"
static void check(int id,const unsigned short*r){unsigned before=draws;skin_icon(id,12,13,22,22);assert(draws==before+1);assert(uv[0]==r[0]+.5f&&uv[1]==r[1]+.5f&&uv[2]==r[2]-1.f&&uv[3]==r[3]-1.f);/* Every bilinear footprint stays in this rect, even at its vertices. */assert(floorf(uv[0]-.5f)>=r[0]&&ceilf(uv[0]+uv[2]-.5f)<=r[0]+r[2]-1);assert(floorf(uv[1]-.5f)>=r[1]&&ceilf(uv[1]+uv[3]-.5f)<=r[1]+r[3]-1);}
int main(void){for(unsigned i=0;i<sizeof(skinRects)/sizeof(*skinRects);i++)check(i,skinRects[i]);check(ITEM_ICON_BASE52,dynamic);check(ITEM_ICON_BASE52+1,skinRects[108]);unsigned n=draws;skin_icon(-1,12,13,22,22);skin_icon(ITEM_ICON_BASE52+2,12,13,22,22);assert(draws==n);printf("PASS actual skin_icon: %u authored/dynamic/fallback rectangles preserve native half-texel origins and size-minus-one UV extents; no neighboring atlas pixels in bilinear footprint. Host arithmetic, not Xbox raster acceptance.\n",draws);}
