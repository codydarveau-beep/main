#define MYRO_HOST
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <zlib.h>
#include "encounter_data.h"
static void fail(const char*s){fprintf(stderr,"%s\n",s);exit(1);}
static unsigned char*inflateasset(const char*name,const unsigned char*p,unsigned packed,unsigned raw){(void)name;unsigned char*b=malloc(raw);assert(b);uLongf n=raw;assert(uncompress(b,&n,p,packed)==Z_OK&&n==raw);return b;}
#include "sprites.h"
int main(void){sprite_load_all();assert(sprites[0].actions==64&&sprites[0].bytesPerPixel==2&&sprites[0].pixelBytes<1400000);
 for(unsigned group=0;group<6;group++)for(unsigned d=0;d<8;d++)for(unsigned t=0;t<100;t++)assert(sprite_frame(&sprites[0],group,d,t*.1f,0,1)<sprites[0].frames);
 for(unsigned j=0;j<42;j++){sprite_set_job(j%7);assert(sprites[0].actions==64&&sprites[0].bytesPerPixel==2&&sprites[0].pixelBytes<1400000);for(unsigned group=0;group<sprites[0].actions/8;group++)for(unsigned dir=0;dir<8;dir++)assert(sprite_frame(&sprites[0],group,dir,.3f,.45f,0)<sprites[0].frames);}
 free(sprites[0].raw);memset(&sprites[0],0,sizeof(sprites[0]));unsigned peak=0;
 for(unsigned map=0;map<7;map++){
  sprite_load_map(map);unsigned bytes=0,kinds=0;
  for(unsigned k=0;k<MOB_SPEC_COUNT;k++)if(sprites[k+1].raw){SparseSprite*s=&sprites[k+1];assert(s->bytesPerPixel==2);bytes+=enemyRaw[k];kinds++;
   for(unsigned a=0;a<5;a++)for(unsigned d=0;d<8;d++)for(unsigned tick=0;tick<100;tick++)assert(sprite_frame(s,a,d,tick*.1f,0,1)<s->frames);
  }
  for(int target=0;target<MOB_SPEC_COUNT;target++){sprite_test_target(map,target);assert(sprites[target+1].raw);for(unsigned k=0;k<MOB_SPEC_COUNT;k++){int expected=(int)k==target;for(unsigned j=0;j<SPAWN_DEF_COUNT;j++)if(spawnDefs[j].map==map&&spawnDefs[j].kind==k)expected=1;assert((sprites[k+1].raw!=NULL)==expected);}assert(sprite_frame(&sprites[target+1],0,0,0,0,1)<sprites[target+1].frames);}sprite_test_target(map,-1);
  if(bytes>peak)peak=bytes;printf("Map %u: %u sprite types, %u decoded bytes\n",map,kinds,bytes);sprite_release_enemies();
  for(unsigned k=1;k<=MOB_SPEC_COUNT;k++)assert(!sprites[k].raw);
 }
 assert(peak<2600000);printf("PASS player sitting actions, actual loader, 16-bit sprites, animation bounds and release; peak map sprite bytes %u\n",peak);
}
