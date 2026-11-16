#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <zlib.h>
static unsigned resident,peak,allocations,vertices,primitives;static float minx,maxx,miny,maxy;
static void fail(const char*s){fprintf(stderr,"%s\n",s);abort();}
static void*gpu_alloc(unsigned n){unsigned*p=malloc(n+sizeof(*p));assert(p);*p=n;resident+=n;if(resident>peak)peak=resident;allocations++;return p+1;}
static void MmFreeContiguousMemory(void*vp){unsigned*p=(unsigned*)vp-1;resident-=*p;free(p);}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned z,unsigned size){(void)n;unsigned char*r=malloc(size);assert(r);uLongf bytes=size;assert(uncompress(r,&bytes,p,z)==Z_OK&&bytes==size);return r;}
static void gpu_depth_state(int v){assert(!v);}static void program(int v){assert(!v);}static void bindTexture(void*p,unsigned w,unsigned h,unsigned pitch,unsigned fmt){assert(p&&w==512&&h<=1024&&pitch==1024&&fmt==0x00011d2a);}
#define NV097_SET_ALPHA_TEST_ENABLE 1
#define NV097_SET_VERTEX_DATA_ARRAY_FORMAT 128
#define NV097_SET_CULL_FACE_ENABLE 2
#define NV097_SET_BLEND_ENABLE 3
#define NV097_SET_BEGIN_END 4
static float spriteClipLow54=-1e9f,spriteClipHigh54=1e9f;
static uint32_t commands[4096];static uint32_t*pb_begin(void){return commands;}static void pb_end(uint32_t*p){(void)p;}
static uint32_t*pb_push1(uint32_t*p,unsigned k,unsigned v){if(k==NV097_SET_BEGIN_END&&v){assert(v==7);primitives++;}return p;}
static uint32_t*vertex(uint32_t*p,float x,float y,float z,float u,float v){assert(isfinite(x)&&isfinite(y)&&z==100);assert(u>=0&&u<=512&&v>=0&&v<=1024);assert(y>=spriteClipLow54-.001f&&y<=spriteClipHigh54+.001f);minx=fminf(minx,x);maxx=fmaxf(maxx,x);miny=fminf(miny,y);maxy=fmaxf(maxy,y);vertices++;return p;}

#include "willow_death259.h"
int main(void){assert(willow_death_code259(1,0,0)==1);unsigned poses=0;willow_prepare259(3,100);assert(allocations==2&&resident==2*512*willowArt259[0].height*2);unsigned constant=resident;
for(unsigned species=0;species<2;species++){const WillowArt259*a=willowArt259+species;for(unsigned dir=0;dir<8;dir++)for(unsigned frame=0;frame<a->frames;frame++){unsigned code=willow_death_code259(species?27:19,dir,frame*.025f+.001f);assert(code==2+dir*32+frame);vertices=primitives=0;minx=miny=1e9f;maxx=maxy=-1e9f;willow_draw259(species,code-2,320,240,100,1);const WillowPose259*pose=&a->poses[dir][frame];assert(primitives==pose->count&&vertices==pose->count*4);assert(maxx-minx<1024&&maxy-miny<1024);if(frame==7)assert(maxx-minx>128);poses++;for(unsigned actor=0;actor<64;actor++)willow_draw259(species,code-2,320,240,100,1);assert(allocations==2&&resident==constant);spriteClipLow54=200;spriteClipHigh54=280;willow_draw259(species,code-2,320,240,100,1);spriteClipLow54=-1e9f;spriteClipHigh54=1e9f;}assert(willow_death_code259(species?27:19,7,20)==2+7*32+a->frames-1);}
willow_prepare259(0,3099);assert(resident==constant);willow_prepare259(0,3100);assert(!resident);willow_prepare259(1,4000);assert(allocations==3);willow_release259();assert(!resident);printf("PASS actual layered Willow/Elder Willow death renderer: %u original poses; source timing, unbounded source expansion, alpha atlas/UVs, all camera-facing directions, water clipping, shared allocation under 64 simultaneous draws, idle/map cleanup. GPU boundary modeled. Peak shared GPU bytes %u.\n",poses,peak);}
