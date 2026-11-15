#define MYRO_HOST 1
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <zlib.h>
#define WORLD_MAP_COUNT 494
#include "water_mode190.h"
#include "water_data.h"
static void fail(const char*s){fprintf(stderr,"%s\n",s);exit(3);}
static void*gpu_alloc(unsigned n){void*p=malloc(n);assert(p);return p;}
static void MmFreeContiguousMemory(void*p){free(p);}
#include "water_stream190.h"
int main(void){
 waterOriginal190=1;unsigned map=0;while(map<WORLD_MAP_COUNT&&!waterMaps[map].count)map++;assert(map<WORLD_MAP_COUNT);
 for(unsigned setting=0;setting<9;setting++){
  waterAnimation200=setting;unsigned count=waterFrameCounts200[setting];
  for(unsigned m=0;m<WORLD_MAP_COUNT;m++){
   unsigned seen=0;float duration=32.f*waterSettings190[m].animation/60.f;
   for(unsigned i=0;i<2048;i++){float t=(i+.25f)*duration/2048;unsigned f=water_frame190(m,t);assert(f<32);seen|=1u<<f;assert(water_frame190(m,t+duration)==f);}
   assert((unsigned)__builtin_popcount(seen)==count);
   float t=.13f,z=water_corner190(m,3,6,t,17);assert(isfinite(z));if(setting==8)assert(z==water_corner190(m,3,6,120.2f,17));
  }
  water_release190();unsigned reads=waterReads190;float duration=32.f*waterSettings190[map].animation/60.f;
  for(unsigned i=0;i<512;i++){waterTime190=(i+.25f)*duration/512;water_prepare190(map);unsigned before=waterReads190;water_prepare190(map);assert(waterReads190==before);}
  assert(waterReads190-reads==count);printf("%s: %u source-frame reads per cycle\n",waterFrameNames200[setting],count);
 }
 waterOriginal190=0;water_prepare190(map);assert(!waterGpu190&&!waterFile190&&!waterRaw190&&!waterPacked190);
 puts("PASS all 494 maps/all 9 frame selectors, unchanged cycle duration, streaming skips held frames, frozen single-frame waves and CURRENT buffer release.");
}
