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
#include "sprite_slice54.h"
#include "gpu_sprite_upload45.h"


int main(void){sprite_stream_load51(19);SparseSprite*s=sprites+20;printf("alpha %u\n",s->alpha4444);FILE*f=fopen("Validation/willow-death253.bin","wb");for(unsigned dir=0;dir<8;dir++){unsigned*a=s->meta+(32+dir)*3;printf("direction %u count%u ms%u\n",dir,a[1],a[2]);for(unsigned i=0;i<a[1];i++){unsigned frame=s->sequence[a[0]+i],*d=s->directory+frame*5,h[8]={dir,i,frame,d[0],d[1],d[2],d[3],d[2]*d[3]*2};printf(" frame%u crop%u,%u %ux%u\n",frame,d[0],d[1],d[2],d[3]);fwrite(h,4,8,f);fwrite(sprite_crop51(s,frame),1,h[7],f);}}fclose(f);sprite_release_enemies();}