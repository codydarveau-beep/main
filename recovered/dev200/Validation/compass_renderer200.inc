#include "compass_layout62.h"
static void compass_line62(int x,int y,int nx,int ny,unsigned color,int width){int dx=abs(nx-x),dy=-abs(ny-y),sx=x<nx?1:-1,sy=y<ny?1:-1,error=dx+dy;for(;;){pb_fill(x-width/2,y-width/2,width,width,color);if(x==nx&&y==ny)break;int e=2*error;if(e>=dy){error+=dy;x+=sx;}if(e<=dx){error+=dx;y+=sy;}}}
/* Draw only the annulus; its centre and the surrounding world stay transparent. */
static void compass_ring62(int cx,int cy,int radius,int thickness,unsigned color){int inner=radius-thickness;for(int y=-radius;y<=radius;y++){int outer=(int)sqrtf((float)(radius*radius-y*y));int hole=abs(y)<=inner?(int)ceilf(sqrtf((float)(inner*inner-y*y))):0;if(hole>0){pb_fill(cx-outer,cy+y,outer-hole+1,1,color);pb_fill(cx+hole,cy+y,outer-hole+1,1,color);}else pb_fill(cx-outer,cy+y,outer*2+1,1,color);}}
/* Floral points replace the crossed spears; open centre preserves world visibility. */
static void compass_blossom200(int x,int y,int north){int w=north?16:12,h=north?16:12;hud_quad(x-w/2,y-h/2,w,h,COMPASS_ART_X200+(north?0:16),COMPASS_ART_Y200,w,h);}
static void ui_compass61(float yaw){
 if(compassSize60==DISPLAY_OFF60)return;
 int cx,cy,r;compass_layout62(minimapSize60,compassSize60,&cx,&cy,&r);float co=cosf(yaw),si=sinf(yaw);
 compass_ring62(cx+2,cy+3,r+2,5,0x70000000);
 compass_ring62(cx,cy,r+1,5,0xff241d1b);
 compass_ring62(cx,cy,r,3,0xffbd8c3e);
 compass_ring62(cx,cy,r-1,1,0xfff4d47a);
 /* Restrained alternating over/under gold stitches suggest a Nordic braid. */
 for(unsigned k=0;k<24;k++){float a=k*.2617993878f,rad=r-(k&1?0:1);int x=cx+(int)roundf(sinf(a)*rad),y=cy+(int)roundf(cosf(a)*rad);pb_fill(x,y,1,1,k&1?0xff78532e:0xffffe6a2);}
 hud_setup(skinTexture,512,SKIN_H,2048,0x0001122a,1);
 for(int i=0;i<4;i++){
  float dx=i==0?si:i==1?co:i==2?-si:-co,dy=i==0?-co:i==1?si:i==2?co:-si;
  /* A leaf at the foot of each blossom ties it into the gold ring. */
  int lx=cx+(int)roundf(dx*(r-3)),ly=cy+(int)roundf(dy*(r-3));
  hud_quad(lx-3,ly-2,7,5,COMPASS_ART_X200+32,COMPASS_ART_Y200,7,5);
  int fx=cx+(int)roundf(dx*(r+3)),fy=cy+(int)roundf(dy*(r+3));compass_blossom200(fx,fy,i==0);
  int x=cx+(int)roundf(dx*(r+(i?20:23))),y=cy+(int)roundf(dy*(r+(i?20:23)));
  hud_quad(x-8,y-8,16,16,COMPASS_LETTERS_X200+i*16,SKIN_COMPASS_Y62,16,16);
 }
}
