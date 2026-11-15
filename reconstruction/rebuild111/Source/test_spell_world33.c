/* SPDX-License-Identifier: MIT. Actual embedded seven-map loader integration; GPU calls mocked. */
#define MYRO_HOST
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include <assert.h>
#include <zlib.h>
static void debugPrint(const char*s,...){(void)s;}
static uint16_t *terrain;static uint8_t*walk;
static unsigned mw,mh,nverts,tw,th,gw,gh;static uint32_t*cellStarts;static float *groundHeights,*meshVertices;static unsigned char*meshRaw;static float spawnx,spawny;
static void fail(const char*s){fprintf(stderr,"%s\n",s);exit(1);}
#include "world_data.h"
static voidpf asset_zalloc(voidpf opaque,uInt count,uInt size){
 (void)opaque;if(size&&count>SIZE_MAX/size)return NULL;return calloc(count,size);
}
static void asset_zfree(voidpf opaque,voidpf p){(void)opaque;free(p);}
static unsigned char *inflateasset(const char *name,const unsigned char *src,unsigned packed,unsigned raw){
 debugPrint("Unpacking %s from executable...\n",name);
 unsigned char *p=malloc(raw);if(!p)fail("Insufficient memory while unpacking");
 z_stream z={0};z.zalloc=asset_zalloc;z.zfree=asset_zfree;z.next_in=(Bytef*)src;z.avail_in=packed;z.next_out=p;z.avail_out=raw;
 int init=inflateInit(&z);if(init!=Z_OK){char msg[128];snprintf(msg,sizeof(msg),"Inflater init failed for %s: %d",name,init);fail(msg);}
 int result=inflate(&z,Z_FINISH);unsigned long n=z.total_out;inflateEnd(&z);
 if(result!=Z_STREAM_END||n!=raw)fail("Embedded asset decompression failed");return p;
}
#include "map_loader.h"
static int allowed(float x,float y){int cx=(int)(x/8),cy=(int)(y/8);return cx>=1&&cy>=1&&cx<(int)gw-1&&cy<(int)gh-1&&walk[cy*gw+cx];}
static float height_at(float x,float y){
 int ix=(int)(x/16),iy=(int)(y/16);if(ix<0)ix=0;if(iy<0)iy=0;if(ix>=(int)mw)ix=mw-1;if(iy>=(int)mh)iy=mh-1;
 float fx=x/16-ix,fy=y/16-iy;const float *h=groundHeights+(iy*mw+ix)*4;
 if(fx>fy)return surface_height(surfaceMap,gw,gh,x,y,h[0]+(h[1]-h[0])*fx+(h[3]-h[1])*fy);
 return surface_height(surfaceMap,gw,gh,x,y,h[0]+(h[3]-h[2])*fx+(h[2]-h[0])*fy);
}

#include "combat.h"
static int world_can_move(void*unused,float x,float y,float nx,float ny){
 (void)unused;float d=combat_dist(x,y,nx,ny);int steps=(int)(d/3)+1;float lastZ=height_at(x,y);
 for(int i=1;i<=steps;i++){float xx=x+(nx-x)*i/steps,yy=y+(ny-y)*i/steps;if(!allowed(xx,yy))return 0;float z=height_at(xx,yy);if(fabsf(z-lastZ)>8)return 0;lastZ=z;}return 1;
}

#include "save_store.h"
static void *gpuTerrain,*gpuMesh;
typedef struct{void*p;unsigned n;} Allocation;
static Allocation allocations[16];static unsigned allocated,bytesNow,bytesPeak,loads;
static void*gpu_alloc(unsigned n){void*p=malloc(n);assert(p);for(int i=0;i<16;i++)if(!allocations[i].p){allocations[i]=(Allocation){p,n};allocated++;bytesNow+=n;if(bytesNow>bytesPeak)bytesPeak=bytesNow;return p;}assert(0);return NULL;}
static void MmFreeContiguousMemory(void*p){for(int i=0;i<16;i++)if(allocations[i].p==p){allocated--;bytesNow-=allocations[i].n;allocations[i].p=NULL;free(p);return;}assert(!"free of untracked GPU resource");}
static int pb_busy(void){return 0;}
static void gpu_memory(void){gpuTerrain=gpu_alloc(tw*th*2);memcpy(gpuTerrain,terrain,tw*th*2);free((unsigned char*)terrain-8);terrain=NULL;gpuMesh=gpu_alloc(nverts*20);memcpy(gpuMesh,meshVertices,nverts*20);free(meshRaw);meshRaw=NULL;meshVertices=NULL;}
static void world_loading(const char*s){(void)s;loads++;}
static void world_loading_end(void){}
#include "gpu_inflate.h"
#include "world_maps.h"
#include "scenery.h"
static unsigned char saved[2][SAVE_BYTES];static int valid[2];
static int rd(void*c,int i,unsigned char*out){(void)c;if(!valid[i])return SLOT_MISSING;memcpy(out,saved[i],SAVE_BYTES);return SLOT_RAW;}
static int wr(void*c,int i,const unsigned char*in){(void)c;memcpy(saved[i],in,SAVE_BYTES);valid[i]=1;return 1;}
static void navigation_check(unsigned map){
 unsigned n=gw*gh,*queue=malloc(n*4);unsigned char*seen=calloc(n,1);assert(queue&&seen);unsigned head=0,tail=0,start=(unsigned)(spawny/8)*gw+(unsigned)(spawnx/8);queue[tail++]=start;seen[start]=1;
 while(head<tail){unsigned k=queue[head++],x=k%gw,y=k/gw;int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};for(int i=0;i<4;i++){int xx=(int)x+dx[i],yy=(int)y+dy[i];if(xx<1||yy<1||xx>=(int)gw-1||yy>=(int)gh-1)continue;unsigned next=yy*gw+xx;if(!seen[next]&&world_can_move(NULL,x*8+4,y*8+4,xx*8+4,yy*8+4)){seen[next]=1;queue[tail++]=next;}}}
 for(unsigned i=0;i<WORLD_GATE_COUNT;i++)if(worldGates[i].source==map){WorldGate t=worldGates[i];int reachable=0;for(float y=t.y-t.ry;y<=t.y+t.ry;y+=8)for(float x=t.x-t.rx;x<=t.x+t.rx;x+=8){int xx=x/8,yy=y/8;if(xx>=0&&yy>=0&&xx<(int)gw&&yy<(int)gh&&seen[yy*gw+xx])reachable=1;}assert(reachable);}
 free(queue);free(seen);
}
#include "water_data.h"
#include "water_query.h"
#include "developer.h"
int main(void){Combat g;unsigned wetMaps=0;for(unsigned map=0;map<WORLD_MAP_COUNT;map++){assert(world_activate(map));combat_init(&g,spawnx,spawny,world_can_move,NULL);g.mapId=map;world_town(&g);g.inWater=world_in_water;dev_class_preset(&g,3);int found=world_test_water(&g);printf("Map%u wading:%s at%.0f,%.0f\n",map,found?"yes":"no",g.x,g.y);if(found){wetMaps++;assert(world_in_water(NULL,g.x,g.y,g.x,g.y));assert(skill_cast(&g,55,0,0)&&inventory_count(&g,ITEM_HOLY_WATER)==1);}combat_memorize(&g);assert(g.memoCount==1);WorldPosition memo=g.memos[0];g.travel=(WorldPosition){2,1244,1476};g.travelRequest=1;assert(world_skill_travel(&g)&&activeMap==2&&g.mapId==2&&allowed(g.x,g.y)&&g.memoCount==1&&g.memos[0].map==memo.map&&g.ranks[51]);g.travel=memo;g.travelRequest=1;assert(world_skill_travel(&g)&&activeMap==map&&allowed(g.x,g.y));}
 assert(wetMaps>0);world_release();assert(!allocated&&!bytesNow);puts("PASS all7 actual map loads, bridge-aware wading query/crafting, local/cross-map spell travel preserves required character state, resource release");return 0;}
