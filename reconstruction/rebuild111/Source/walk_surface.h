/* SPDX-License-Identifier: MIT. No expanded height grid or per-frame allocation. */
#ifndef MYRO_WALK_SURFACE_H
#define MYRO_WALK_SURFACE_H
typedef struct {unsigned cell;short z[4];} WalkSurface;
static const WalkSurface*surfaceCells45;static unsigned surfaceCount45;
static unsigned surfaceMap;
static int surface_contains45(unsigned width,unsigned height,float x,float y){if(!surfaceCells45||x<0||y<0||x>=width*8.f||y>=height*8.f)return 0;unsigned key=(unsigned)(y/8)*width+(unsigned)(x/8),lo=0,hi=surfaceCount45;while(lo<hi){unsigned m=(lo+hi)/2;if(surfaceCells45[m].cell<key)lo=m+1;else hi=m;}return lo<surfaceCount45&&surfaceCells45[lo].cell==key;}
static float surface_height(unsigned map,unsigned width,unsigned height,float x,float y,float fallback){
 if(map!=surfaceMap||!surfaceCells45||!width||!height||x<0||y<0||x>=width*8.f||y>=height*8.f)return fallback;
 unsigned cx=(unsigned)(x/8),cy=(unsigned)(y/8),key=cy*width+cx,lo=0,end=surfaceCount45,hi=end;
 while(lo<hi){unsigned m=(lo+hi)/2;if(surfaceCells45[m].cell<key)lo=m+1;else hi=m;}
 if(lo>=end||surfaceCells45[lo].cell!=key)return fallback;
 const short*q=surfaceCells45[lo].z;float fx=x/8-cx,fy=y/8-cy;
 if(fx>fy)return(q[0]+(q[1]-q[0])*fx+(q[3]-q[1])*fy)/16.f;
 return(q[0]+(q[3]-q[2])*fx+(q[2]-q[0])*fy)/16.f;
}
#endif
