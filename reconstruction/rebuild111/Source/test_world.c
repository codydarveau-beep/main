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
int main(void){
 world_blob_init();unsigned residency[WORLD_MAP_COUNT]={0};Combat g;
 for(unsigned i=0;i<WORLD_MAP_COUNT;i++){
  assert(world_activate(i));assert(activeMap==i&&allocated==4);assert(allowed(spawnx,spawny));assert(scene.count[0]>0&&scene.count[1]==0);residency[i]=bytesNow;navigation_check(i);
  {const WorldBlob*b=&worldBlobs[i][4];unsigned char*reference=world_expand(i,4,"atlas reference");assert(!memcmp(sceneTexture,reference+8,b->raw-8));free(reference);}
  // Every transformed model vertex must lie inside the instance AABB.
  float*vertices=(float*)sceneMesh;
  for(unsigned k=0;k<scene.count[0];k++){SceneInstance*in=scene.instances[0]+k;SceneModel*d=scene.model+in->model;for(unsigned j=d->start;j<d->start+d->count;j++)for(int a=0;a<3;a++){float p=in->matrix[a*4+3];for(int b=0;b<3;b++)p+=in->matrix[a*4+b]*vertices[j*5+b];assert(p>=in->bounds[a]-.01f&&p<=in->bounds[a+3]+.01f);}}
  for(unsigned j=0;j<WORLD_GATE_COUNT;j++)if(worldGates[j].source==i){WorldGate t=worldGates[j];int possible=0;for(float y=t.y-t.ry;y<=t.y+t.ry;y+=8)for(float x=t.x-t.rx;x<=t.x+t.rx;x+=8)if(allowed(x,y))possible=1;assert(possible);}
  combat_init(&g,spawnx,spawny,world_can_move,NULL);g.mapId=i;world_town(&g);assert(g.peaceful==(i==2||i==3));if(g.peaceful){for(int k=0;k<8;k++)assert(g.mobs[k].hp==0);for(int k=0;k<1000;k++)combat_tick(&g,.05f,0,0);for(int k=0;k<8;k++)assert(g.mobs[k].hp==0);}
  if(i==2){float x,y;world_merchant(&x,&y);assert(world_can_move(NULL,spawnx,spawny,x,y));g.x=x;g.y=y;assert(world_near_merchant(&g));world_instructor(&x,&y);assert(world_can_move(NULL,spawnx,spawny,x,y));g.x=x;g.y=y;assert(world_near_instructor(&g)&&!world_near_merchant(&g));}
  printf("Map %u %s: %u terrain vertices, %u scenery placements, GPU bytes %u\n",i,mapNames[i],nverts,scene.count[0],bytesNow);
 }
 // Exact source populations, bounded placement and fixed-region plants.
 for(unsigned map=0;map<WORLD_MAP_COUNT;map++){
  world_activate(map);combat_init(&g,spawnx,spawny,world_can_move,NULL);g.mapId=map;world_town(&g);
  unsigned expected=0,actual=0;for(unsigned j=0;j<SPAWN_DEF_COUNT;j++)if(spawnDefs[j].map==map)expected+=spawnDefs[j].count;
  for(unsigned j=0;j<MOB_COUNT;j++)if(g.mobs[j].enabled){CombatMob*m=&g.mobs[j];actual++;assert(m->hp==mobSpecs[m->kind].hp&&allowed(m->x,m->y));
   const SpawnDef*d=&spawnDefs[m->spawnDef];assert(d->map==map&&d->kind==(unsigned)m->kind);
   if(d->x)assert(fabsf(m->x-(d->x*8+4))<=(d->rx+64)*8);
   if(d->y)assert(fabsf(m->y-(d->y*8+4))<=(d->ry+64)*8);
  }
  assert(expected==actual&&actual<=MOB_COUNT);printf("Map %u: %u source monsters, valid placement and species (blocked old plant regions use nearest legal cell)\n",map,actual);
 }
 // Each authentic warp uses real load/unload and preserves durable fields.
 for(unsigned i=0;i<WORLD_GATE_COUNT;i++){
  WorldGate t=worldGates[i];world_activate(t.source);combat_init(&g,spawnx,spawny,world_can_move,NULL);g.mapId=t.source;g.x=t.x;g.y=t.y;g.hp=39;g.sp=7;g.zeny=12345;g.extraItems[0]=0;g.equipment=15;g.hotbar[7]=4;g.hotSlot=7;
  assert(world_near_gate(&g));unsigned expected=worldGates[world_gate(&g)].destination;world_travel(&g);assert(activeMap==expected&&g.mapId==expected&&allocated==4&&bytesNow==residency[activeMap]);assert(allowed(g.x,g.y)&&g.hp==39&&g.sp==7&&g.zeny==12345&&g.equipment==15&&g.extraItems[0]==0&&g.hotSlot==7&&g.hotbar[7]==4);
 }
 // Test-menu travel preserves durable state, including same-map travel.
 for(unsigned i=0;i<WORLD_MAP_COUNT;i++){
  g.hp=39;g.sp=7;g.zeny=12345;g.equipment=15;g.hotSlot=7;g.hotbar[7]=4;
  assert(world_test_warp(&g,i));assert(activeMap==i&&g.mapId==i&&allowed(g.x,g.y));
  assert(allocated==4&&bytesNow==residency[i]);assert(g.hp==39&&g.sp==7&&g.zeny==12345&&g.equipment==15&&g.hotSlot==7&&g.hotbar[7]==4);
  assert(world_test_warp(&g,i)&&allowed(g.x,g.y));
 }
 unsigned before=activeMap;assert(!world_test_warp(&g,WORLD_MAP_COUNT)&&activeMap==before);
 g.hp=0;assert(!world_test_warp(&g,0)&&activeMap==before);g.hp=39;
 world_activate(3);combat_init(&g,spawnx,spawny,world_can_move,NULL);g.mapId=3;g.zeny=9876;SaveStore s={0};s.read=rd;s.write=wr;s.prepare=world_prepare;assert(save_commit(&s,&g));world_activate(0);Combat restored;assert(save_load(&s,&restored,spawnx,spawny,world_can_move,NULL));world_town(&restored);assert(activeMap==3&&restored.mapId==3&&restored.zeny==9876&&restored.peaceful&&allowed(restored.x,restored.y));
 for(int i=0;i<70;i++){unsigned map=i%WORLD_MAP_COUNT;assert(world_activate(map));assert(allocated==4&&bytesNow==residency[map]);}
 world_release();assert(!allocated&&!bytesNow&&!walk&&!cellStarts&&!groundHeights&&!gpuTerrain&&!gpuMesh&&!sceneTexture&&!sceneMesh&&!sceneMetadataRaw);
 assert(world_test_warp(&g,2));g.jobId=2;g.joblevel=3;g.ranks[2]=g.ranks[3]=1;g.skillPoints=0;stat_refresh(&g);g.hotbar[7]=9;
 assert(world_test_warp(&g,5)&&g.jobId==2&&g.joblevel==3&&g.ranks[3]==1&&g.hotbar[7]==9);
 for(unsigned k=0;k<WORLD_GATE_COUNT;k++)if(worldGates[k].source==activeMap){g.x=worldGates[k].x;g.y=worldGates[k].y;unsigned dest=worldGates[k].destination;g.fields[0].remaining=5;g.barriers[0].expires=g.time+100;g.angelusLeft=100;world_travel(&g);assert(!g.fields[0].remaining&&!g.barriers[0].expires&&!g.angelusLeft);assert(g.mapId==dest&&g.jobId==2&&g.ranks[2]==1&&g.ranks[3]==1&&g.hotbar[7]==9);break;}
 printf("PASS seven real maps/scenery, every warp, peaceful towns, accessible merchant, saved map preparation, 70 repeated loads, exact resource release; peak simulated GPU bytes %u. Not Xbox RAM/FPS.\n",bytesPeak);return 0;
}
