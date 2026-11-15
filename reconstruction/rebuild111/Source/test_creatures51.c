/* Exercise actual streaming, source pixels, cache eviction, GPU crops and fades. */
#define MYRO_HOST 1
#define MYRO_DISC_ENEMIES44 1
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <zlib.h>
#include "combat.h"
static void fail(const char*s){fprintf(stderr,"%s\n",s);abort();}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned z,unsigned raw){(void)n;unsigned char*r=malloc(raw);assert(r);uLongf bytes=raw;assert(uncompress(r,&bytes,p,z)==Z_OK&&bytes==raw);return r;}
#include "sprites.h"
#include "sprite_tint.h"
static void*entityTextures[SPRITE_SLOT_COUNT];static unsigned uploadedFrames[SPRITE_SLOT_COUNT],uploadedEpoch[SPRITE_SLOT_COUNT];static const SparseSprite*uploadedSource[SPRITE_SLOT_COUNT];
static void*gpu_alloc(unsigned n){void*p=malloc(n);assert(p);return p;}
static void MmFreeContiguousMemory(void*p){free(p);}
static void gpu_stream_plane51(void*t,SparseSprite*s,float x,float y,float d,float scale,float top,float bottom);
/* Strip command submission only: the native upload implementation is unchanged. */
#define gpu_depth_state(x) ((void)0)
#define program(x) ((void)0)
#define bindTexture(t,w,h,p,f) ((void)0)
#define NV097_SET_ALPHA_TEST_ENABLE 0
#define NV097_SET_VERTEX_DATA_ARRAY_FORMAT 0
#define NV097_SET_CULL_FACE_ENABLE 0
#define NV097_SET_BLEND_ENABLE 0
#define NV097_SET_BEGIN_END 0
static uint32_t commands[4096];static uint32_t*pb_begin(void){return commands;}static void pb_end(uint32_t*p){(void)p;}
static uint32_t*pb_push1(uint32_t*p,unsigned a,unsigned b){(void)a;(void)b;return p;}
static uint32_t*vertex(uint32_t*p,float x,float y,float z,float u,float v){assert(isfinite(x)&&isfinite(y)&&isfinite(z)&&isfinite(u)&&isfinite(v));return p;}
#include "gpu_sprite_upload45.h"
int main(void){unsigned bodies=0,frames=0,maxCrop=0;
 for(unsigned k=50;k<MOB_SPEC_COUNT;k++){
  sprite_load_enemy44(k);SparseSprite*s=&sprites[k+1];if(s->guardian51){assert(mobSpecs[k].id==1829||mobSpecs[k].id==1830);continue;}
  bodies++;for(unsigned a=0;a<40;a++){unsigned f=sprite_frame(s,a/8,a%8,123.4f,0,1);assert(f<s->frames);}
  for(unsigned f=0;f<s->frames;f++){
   unsigned*d=s->directory+f*5;unsigned slot=1+f%32;sprite_upload(s,f,slot);unsigned char*src=sprite_crop51(s,f);if(d[2]*d[3]*2>maxCrop)maxCrop=d[2]*d[3]*2;
   for(unsigned y=0;y<d[3];y++)assert(!memcmp((unsigned char*)entityTextures[slot]+(y+1)*cropPitch51[slot]+2,src+y*d[2]*2,d[2]*2));
   gpu_stream_plane51(entityTextures[slot],s,320,245,8388608,.8f,8300000,8400000);frames++;assert(cropBytes51<=2097152);
  }
  /* Status transitions and clear restore original source bytes/alpha. */
  unsigned slot=1;spriteFrozen[slot]=1;spritePoison[slot]=1;spriteFlash49[slot]=0x80ffff;sprite_upload(s,0,slot);spriteFrozen[slot]=spritePoison[slot]=spriteFlash49[slot]=0;sprite_upload(s,0,slot);unsigned*d=s->directory;unsigned char*src=sprite_crop51(s,0);for(unsigned y=0;y<d[3];y++)assert(!memcmp((unsigned char*)entityTextures[slot]+(y+1)*cropPitch51[slot]+2,src+y*d[2]*2,d[2]*2));
  enemy_cache_clear51();free(s->raw);memset(s,0,sizeof(*s));spriteEpoch++;
  if(k%50==0)printf("PASS species%u frames%u cache bounded\n",k,frames);
 }
 sprite_release_enemies();gpu_stream_reset51();assert(!cropBytes51);printf("PASS %u new 2D species, %u complete original frames, max crop %u, statuses/alpha/eviction/map teardown\n",bodies,frames,maxCrop);
}
