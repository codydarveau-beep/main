/* MIT. Visual room isolation from the existing collision grid; never changes
 * walkability, quest state or NPC execution. One byte/cell on split interiors,
 * temporary bounded flood queue during loading, no per-frame heap allocation. */
#ifndef MYRO_INTERIOR_ROOMS181_H
#define MYRO_INTERIOR_ROOMS181_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct{unsigned width,height,count,active;uint8_t*owner;}InteriorRooms181;
static InteriorRooms181 interiorRooms181;
static void rooms_clear181(InteriorRooms181*r){free(r->owner);memset(r,0,sizeof(*r));}
static int rooms_map181(const char*name){return name&&(strstr(name,"_in")||!strcmp(name,"prt_castle")||!strcmp(name,"prt_church")||!strcmp(name,"gef_tower"));}
static void rooms_neighbors181(unsigned at,unsigned width,unsigned height,unsigned out[4],unsigned*count){unsigned x=at%width,y=at/width;*count=0;if(x)out[(*count)++]=at-1;if(x+1<width)out[(*count)++]=at+1;if(y)out[(*count)++]=at-width;if(y+1<height)out[(*count)++]=at+width;}
static int rooms_build181(InteriorRooms181*r,const char*name,const uint8_t*walk,unsigned width,unsigned height){
 rooms_clear181(r);if(!rooms_map181(name)||!walk||!width||!height||width>512||height>512)return 0;unsigned cells=width*height;
 uint8_t*owner=calloc(cells,1);uint32_t*queue=malloc(cells*sizeof(*queue));if(!owner||!queue){free(owner);free(queue);return 0;}
 unsigned regions=0;
 for(unsigned start=0;start<cells;start++)if(walk[start]&&!owner[start]){
  unsigned begin=0,end=1;queue[0]=start;owner[start]=255;
  while(begin<end){unsigned next[4],count;rooms_neighbors181(queue[begin++],width,height,next,&count);for(unsigned i=0;i<count;i++)if(walk[next[i]]&&!owner[next[i]]){owner[next[i]]=255;queue[end++]=next[i];}}
  /* Tiny isolated collision flecks are decoration, not another room. */
  if(end<16)continue;if(regions==254){free(owner);free(queue);return 0;}regions++;for(unsigned i=0;i<end;i++)owner[queue[i]]=(uint8_t)regions;
 }
 if(regions<2){free(owner);free(queue);return 0;}
 /* Expand room ownership across walls/decorative ground, without connecting
    the original walkable components. Equal-distance ties are deterministic. */
 unsigned begin=0,end=0;for(unsigned i=0;i<cells;i++){if(owner[i]==255)owner[i]=0;if(owner[i])queue[end++]=i;}
 while(begin<end){unsigned at=queue[begin++],next[4],count;rooms_neighbors181(at,width,height,next,&count);for(unsigned i=0;i<count;i++)if(!owner[next[i]]){owner[next[i]]=owner[at];queue[end++]=next[i];}}
 free(queue);*r=(InteriorRooms181){width,height,regions,0,owner};return 1;
}
static void rooms_focus181(InteriorRooms181*r,float x,float y){r->active=0;if(!r->owner||!isfinite(x)||!isfinite(y)||x<0||y<0)return;unsigned gx=(unsigned)(x/8),gy=(unsigned)(y/8);if(gx<r->width&&gy<r->height)r->active=r->owner[gy*r->width+gx];}
static int rooms_point181(const InteriorRooms181*r,float x,float y){if(!r->owner||!r->active)return 1;if(!isfinite(x)||!isfinite(y)||x<0||y<0)return 0;unsigned gx=(unsigned)(x/8),gy=(unsigned)(y/8);return gx<r->width&&gy<r->height&&r->owner[gy*r->width+gx]==r->active;}
static int rooms_near181(const InteriorRooms181*r,float observerX,float observerY,float x,float y){if(!r->owner||!isfinite(observerX)||!isfinite(observerY)||observerX<0||observerY<0)return 1;unsigned ox=(unsigned)(observerX/8),oy=(unsigned)(observerY/8);if(ox>=r->width||oy>=r->height)return 1;unsigned active=r->owner[oy*r->width+ox];if(!active)return 1;if(!isfinite(x)||!isfinite(y)||x<0||y<0)return 0;unsigned tx=(unsigned)(x/8),ty=(unsigned)(y/8);return tx<r->width&&ty<r->height&&r->owner[ty*r->width+tx]==active;}
static int rooms_box181(const InteriorRooms181*r,float x0,float y0,float x1,float y1){if(!r->owner||!r->active)return 1;if(!isfinite(x0)||!isfinite(y0)||!isfinite(x1)||!isfinite(y1)||x0>x1||y0>y1)return 0;int left=(int)floorf(x0/8),right=(int)floorf(x1/8),top=(int)floorf(y0/8),bottom=(int)floorf(y1/8);if(left<0)left=0;if(top<0)top=0;if(right>=(int)r->width)right=r->width-1;if(bottom>=(int)r->height)bottom=r->height-1;for(int y=top;y<=bottom;y++)for(int x=left;x<=right;x++)if(r->owner[y*r->width+x]==r->active)return 1;return 0;}
/* Scenery builds these small room-membership bitsets once during loading. */
static void rooms_box_bits181(const InteriorRooms181*r,float x0,float y0,float x1,float y1,uint8_t*bits){unsigned bytes=(r->count+7)/8;memset(bits,0,bytes);if(!r->owner)return;int left=(int)floorf(x0/8),right=(int)floorf(x1/8),top=(int)floorf(y0/8),bottom=(int)floorf(y1/8);if(left<0)left=0;if(top<0)top=0;if(right>=(int)r->width)right=r->width-1;if(bottom>=(int)r->height)bottom=r->height-1;for(int y=top;y<=bottom;y++)for(int x=left;x<=right;x++){unsigned id=r->owner[y*r->width+x];if(id&&id<=r->count)bits[(id-1)/8]|=1u<<((id-1)%8);}}
static int rooms_tile181(const InteriorRooms181*r,unsigned x,unsigned y){if(!r->owner||!r->active)return 1;unsigned left=x*2,top=y*2;if(left>=r->width||top>=r->height)return 0;for(unsigned yy=top;yy<top+2&&yy<r->height;yy++)for(unsigned xx=left;xx<left+2&&xx<r->width;xx++)if(r->owner[yy*r->width+xx]==r->active)return 1;return 0;}
#endif
