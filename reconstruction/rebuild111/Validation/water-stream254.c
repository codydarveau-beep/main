#define MYRO_HOST 1
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <zlib.h>
#define WORLD_MAP_COUNT 497
#include "water_mode190.h"
#include "water_data.h"
static void fail(const char*s){fprintf(stderr,"%s\n",s);exit(3);}
static void*gpu_alloc(unsigned n){void*p=malloc(n);assert(p);return p;}
static void MmFreeContiguousMemory(void*p){free(p);}
#include "water_stream190.h"
int main(void){unsigned calls=0,peak=0;assert(waterOriginal190==1);waterOriginal190=0;water_prepare190(0);assert(!waterGpu190&&!waterFile190&&!waterBytes190);waterOriginal190=1;
 for(unsigned map=0;map<497;map++){
  const WaterMap190*w=waterSettings190+map;
  for(unsigned q=0;q<8;q++){float x=4.25f+q*17.13f,y=19.75f+q*15.7f,t=q*.173f,z=water_surface190(map,x,y,t,waterMaps[map].z);assert(isfinite(z)&&fabsf(z-waterMaps[map].z)<=w->height+.001f);float zz=water_surface190(map,16*q,32*q,t,waterMaps[map].z),corner=water_corner190(map,q,2*q,t,waterMaps[map].z);assert(fabsf(zz-corner)<.0001f);}
  if(!waterMaps[map].count){water_prepare190(map);assert(!waterGpu190&&!waterRaw190&&!waterPacked190&&!waterFile190);continue;}
  for(unsigned frame=0;frame<32;frame++){
   waterTime190=(frame+.25f)*w->animation/60.f;water_prepare190(map);assert(waterFrame190==frame&&waterBank190==w->type);const WaterFrame190*f=&waterFrames190[w->type][frame];assert(waterBytes190==f->width*f->width*4&&crc32(0,waterGpu190,waterBytes190)==f->crc);unsigned reads=waterReads190;water_prepare190(map);assert(reads==waterReads190);unsigned total=waterBytes190*2+waterPackedCapacity190;if(total>peak)peak=total;calls++;
  }
 }
 for(unsigned q=0;q<100;q++){waterOriginal190=1;waterTime190=q*.1f;water_prepare190(q%497);waterOriginal190=0;water_prepare190(q%497);assert(!waterGpu190&&!waterRaw190&&!waterPacked190&&!waterFile190&&waterBytes190==0&&waterPackedCapacity190==0);}
 assert(peak<=WATER_MAX_FRAME_BYTES190*3+1024);water_release190();printf("PASS %u live original map/frame loads; all497 wave/triangle surfaces; same-frame zero-read reuse;100 toggle/map cycles; default/dry/off zero buffers; peak persistent CPU+GPU %u bytes.\n",calls,peak);
}
