/* SPDX-License-Identifier: MIT. Bounded schematic walkability map; no heap. */
#ifndef MYRO_MINIMAP_H
#define MYRO_MINIMAP_H
#define MINI_W 96
#define MINI_H 72
static void minimap_size(unsigned gw,unsigned gh,int*w,int*h){
 *w=*h=0;if(!gw||!gh)return;
 if((uint64_t)gw*MINI_H>=(uint64_t)gh*MINI_W){*w=MINI_W;*h=(uint64_t)gh*MINI_W/gw;}
 else {*h=MINI_H;*w=(uint64_t)gw*MINI_H/gh;}
 if(*w<1)*w=1;if(*h<1)*h=1;
}
static void minimap_point(float x,float y,unsigned gw,unsigned gh,int*px,int*py){
 int w,h;minimap_size(gw,gh,&w,&h);float xx=gw?x/(gw*8.f):0,yy=gh?y/(gh*8.f):0;
 if(xx<0)xx=0;if(xx>1)xx=1;if(yy<0)yy=0;if(yy>1)yy=1;
 *px=(MINI_W-w)/2+(int)(xx*(w-1));*py=(MINI_H-h)/2+(int)((1-yy)*(h-1));
}
static void minimap_raster(uint32_t*dst,unsigned stride,int ox,int oy,const uint8_t*grid,unsigned gw,unsigned gh){
 int w,h;minimap_size(gw,gh,&w,&h);int left=(MINI_W-w)/2,top=(MINI_H-h)/2;
 for(int y=0;y<MINI_H;y++)for(int x=0;x<MINI_W;x++){
  uint32_t c=0xffeaf0f5;
  if(grid&&x>=left&&x<left+w&&y>=top&&y<top+h){
   unsigned cx=(uint64_t)(x-left)*gw/w,cy=gh-1-(uint64_t)(y-top)*gh/h;
   c=grid[cy*gw+cx]?0xffffffff:0xff8999b2;
  }
  dst[(oy+y)*stride+ox+x]=c;
 }
}
#endif
