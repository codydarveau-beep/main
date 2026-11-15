#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "minimap.h"
int main(void){
 uint32_t image[512*256];uint8_t grid[400*400];memset(grid,1,sizeof(grid));
 const unsigned sizes[][2]={{400,400},{312,392},{268,268},{1,1},{1,400},{400,1},{0,0}};
 for(unsigned k=0;k<sizeof(sizes)/sizeof(*sizes);k++){
  unsigned w=sizes[k][0],h=sizes[k][1];for(unsigned i=0;i<512*256;i++)image[i]=0x12345678;
  minimap_raster(image,512,288,144,grid,w,h);
  for(int y=0;y<256;y++)for(int x=0;x<512;x++)if(x<288||x>=384||y<144||y>=216)assert(image[y*512+x]==0x12345678);
  for(int i=-1;i<=2;i++){int x,y;minimap_point(w*8.f*i,h*8.f*i,w,h,&x,&y);assert(x>=0&&x<96&&y>=0&&y<72);}
 }
 uint8_t four[4]={1,0,0,1};minimap_raster(image,512,288,144,four,2,2);
 assert(image[144*512+300]==0xff8999b2);assert(image[215*512+300]==0xffffffff);
 int x0,y0,x1,y1;minimap_point(0,0,2,2,&x0,&y0);minimap_point(16,16,2,2,&x1,&y1);assert(x0<x1&&y0>y1);
 puts("PASS minimap raster bounds, aspect ratios, clamped markers, north-up orientation");
}
