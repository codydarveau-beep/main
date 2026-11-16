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


int main(void){unsigned kinds[]={19,27,448,449};unsigned frames=0;for(unsigned k=0;k<4;k++){unsigned kind=kinds[k];if(kind<50)sprite_load_enemy44(kind);else sprite_stream_load51(kind);SparseSprite*s=sprites+kind+1;assert(s->raw);printf("KIND %u w%u h%u frames%u stream%u\n",kind,s->w,s->h,s->frames,!!s->stream51);for(unsigned i=0;i<s->frames;i++){sprite_upload(s,i,1);assert(entityTextures[1]&&entityCapacity51[1]);frames++;}gpu_stream_reset51();sprite_release_enemies();assert(!enemyStreamFile51&&!cropBytes51&&!enemyPackedBytes164);}printf("PASS actual Willow/Elder Willow/guardian sprite upload and cleanup: %u frames; GPU boundary recorded, target raster not tested.\n",frames);}
