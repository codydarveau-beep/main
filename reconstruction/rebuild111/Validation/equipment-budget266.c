#define MYRO_HOST
#define MYRO_DISC_ENEMIES44 1
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "combat.h"
#include "developer.h"
static void fail(const char*s){fprintf(stderr,"HEAD TEST:%s\n",s);exit(2);}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned packed,unsigned raw){(void)n;unsigned char*b=malloc(raw);assert(b);uLongf len=raw;assert(uncompress(b,&len,p,packed)==Z_OK&&len==raw);return b;}
#include "sprites.h"
#include "projection.h"
#include "sprite_slice54.h"
#include "sprite_tint.h"
static unsigned spriteFrozen[SPRITE_SLOT_COUNT],spriteStone[SPRITE_SLOT_COUNT],spritePoison[SPRITE_SLOT_COUNT],spriteFlash49[SPRITE_SLOT_COUNT];
static int spriteHiddenPlayer,spriteCoatedPlayer,spriteQuickenPlayer45,spriteBerserkPlayer45;
static unsigned liveGPU,peakGPU;static void*gpu_alloc(unsigned n){size_t*p=malloc(n+sizeof(size_t));assert(p);*p=n;liveGPU+=n;if(liveGPU>peakGPU)peakGPU=liveGPU;return p+1;}
static void MmFreeContiguousMemory(void*p){if(p){size_t*q=(size_t*)p-1;assert(liveGPU>=*q);liveGPU-=*q;free(q);}}
static int pb_busy(void){return 0;}static uint32_t commands[512];static unsigned vertexCount;static float vertices[64][5];
static uint32_t*pb_begin(void){return commands;}static void pb_end(uint32_t*p){(void)p;}static uint32_t*pb_push1(uint32_t*p,unsigned reg,unsigned value){(void)reg;(void)value;return p;}
static uint32_t*vertex(uint32_t*p,float x,float y,float z,float u,float v){assert(vertexCount<64);float a[]={x,y,z,u,v};memcpy(vertices[vertexCount++],a,sizeof(a));return p;}
static void gpu_depth_state(unsigned write){(void)write;}static void program(unsigned n){(void)n;}static void bindTexture(void*t,unsigned w,unsigned h,unsigned pitch,unsigned format){assert(t&&w&&h&&pitch>=w*2&&!(pitch%64)&&format==0x00011d2a);}
enum{NV097_SET_VERTEX_DATA_ARRAY_FORMAT,NV097_SET_CULL_FACE_ENABLE=20,NV097_SET_ALPHA_TEST_ENABLE,NV097_SET_BLEND_ENABLE,NV097_SET_BEGIN_END};
#include "headgear54.h"
static Combat g;

static unsigned char spriteScratch50b[65536];static unsigned quads;static float boundsUI[4];
static void hud_setup_direct(void*t,unsigned w,unsigned h,unsigned pitch,unsigned format,int blend){assert(t&&w&&h&&pitch>=w*2&&blend);assert(format==0x00011d2a||format==0x0001102a||format==0x0001122a);}
static void hud_quad(float x,float y,float w,float h,float u,float v,float uw,float vh){(void)u;(void)v;assert(w>0&&h>0&&uw>0&&vh>0);boundsUI[0]=fminf(boundsUI[0],x);boundsUI[1]=fminf(boundsUI[1],y);boundsUI[2]=fmaxf(boundsUI[2],x+w);boundsUI[3]=fmaxf(boundsUI[3],y+h);quads++;}
static void*entityTextures[SPRITE_SLOT_COUNT];
#include "appearance_render58.h"
#include "headgear_ui180.h"
#include "equipment_preview260.h"

int main(void){unsigned maxAll=0,maxFront=0,view=0;for(unsigned i=0;i<sizeof(headgearDefs54)/sizeof(*headgearDefs54);i++){HeadCache54 cache={0};head_load54(&cache,headgearDefs54[i]);for(unsigned f=0;f<cache.frames;f++){const unsigned*d=cache.directory+f*8;unsigned bytes=((d[2]*2+63)&~63u)*d[3];if(bytes>maxAll)maxAll=bytes;}unsigned first=cache.sequence[cache.meta[0]],*d=cache.directory+first*8,bytes=((d[2]*2+63)&~63u)*d[3];if(bytes>maxFront){maxFront=bytes;view=cache.view;}head_clear_one54(&cache);}head_release54();assert(!liveGPU);printf("PASS full mapped headgear metadata inventory: largest frame GPU bytes%u; largest forward frame%u view%u. Conservative equipment-preview body+3maximum front crops=%u bytes (separate from existing world head textures). Host asset accounting, not Xbox free RAM.\n",maxAll,maxFront,view,65536+3*maxFront);}
