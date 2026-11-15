/* MIT. Protect every HUD region, not just icon/minimap bounds. */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "skin_layout.h"
#include "skin_data.h"
#include "minimap.h"
extern const unsigned char skin_image[];extern const unsigned int skin_image_raw,skin_image_size;
static int overlap(const unsigned short*a,int x,int y,int w,int h){return a[0]<x+w&&a[0]+a[2]>x&&a[1]<y+h&&a[1]+a[3]>y;}
int main(void){uint32_t*p=malloc(skin_image_raw),*o=malloc(skin_image_raw);uLongf n=skin_image_raw;assert(uncompress((void*)o,&n,skin_image,skin_image_size)==Z_OK&&n==SKIN_W*SKIN_H*4);for(int y=0;y<96;y++)for(int x=0;x<256;x++){unsigned a=o[y*512+x],b=o[(y+160)*512+x];assert((a>>24)==(b>>24));if(b>>24)assert((b&0xffffff)==0xffffff);}for(int i=0;i<77;i++){const unsigned short*r=skinRects[i];assert(r[0]+r[2]<=SKIN_W&&r[1]+r[3]<=SKIN_H);assert(!overlap(r,0,0,256,96)&&!overlap(r,0,160,256,96)&&!overlap(r,384,144,120,36)&&!overlap(r,480,184,32,32)&&!overlap(r,288,144,96,72));for(int j=0;j<i;j++)assert(!overlap(r,skinRects[j][0],skinRects[j][1],skinRects[j][2],skinRects[j][3]));}
 uint8_t grid[400*400];memset(grid,1,sizeof(grid));unsigned dims[][2]={{400,400},{400,400},{312,392},{268,268},{380,340},{400,400},{400,400}};for(int k=0;k<7;k++){memcpy(p,o,n);minimap_raster(p,512,288,144,grid,dims[k][0],dims[k][1]);for(int i=0;i<77;i++){const unsigned short*r=skinRects[i];for(int y=0;y<r[3];y++)assert(!memcmp(p+(r[1]+y)*512+r[0],o+(r[1]+y)*512+r[0],r[2]*4));}for(int y=144;y<180;y++)assert(!memcmp(p+y*512+384,o+y*512+384,120*4));}free(p);free(o);puts("PASS77 icons pairwise disjoint; both fonts,damage,critical,minimap protected; all7 map raster updates");}
