/* MIT. Real native decoder/data, bounded event replay, cast marks and preview input. */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <zlib.h>
#include "combat.h"
static void fail(const char*s){fprintf(stderr,"%s\n",s);abort();}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned sz,unsigned raw){(void)n;unsigned char*d=malloc(raw);assert(d);uLongf len=raw;assert(uncompress(d,&len,p,sz)==Z_OK&&len==raw);return d;}
#define MYRO_HOST 1
#include "sprites.h"

#include "art_visual39.h"
#include "developer.h"

#include "sprite_tint.h"
static void*entityTextures[SPRITE_SLOT_COUNT];static unsigned uploadedFrames[SPRITE_SLOT_COUNT],uploadedEpoch[SPRITE_SLOT_COUNT];static const SparseSprite*uploadedSource[SPRITE_SLOT_COUNT];
static void*gpu_alloc(unsigned bytes){return calloc(1,bytes);}
#include "gpu_sprite_upload45.h"

int main(void){sprite_set_equipment(1,32);SparseSprite*s=&sprites[0];unsigned frame=sprite_frame(s,0,0,0,0,0);unsigned crc=crc32(0,s->raw,(32+s->actions*12+s->sequenceCount*4+s->frames*20+s->pixelBytes));entityTextures[0]=calloc(1,65536);unsigned char base[65536];uploadedFrames[0]=~0u;sprite_upload(s,frame,0);memcpy(base,entityTextures[0],65536);spriteCoatedPlayer=1;sprite_upload(s,frame,0);assert(memcmp(base,entityTextures[0],65536));assert(uploadedEpoch[0]==spriteEpoch+0x08000000);((unsigned char*)entityTextures[0])[0]=0x5a;sprite_upload(s,frame,0);assert(((unsigned char*)entityTextures[0])[0]==0x5a);spriteCoatedPlayer=0;sprite_upload(s,frame,0);assert(!memcmp(base,entityTextures[0],65536));spriteCoatedPlayer=spriteHiddenPlayer=1;sprite_upload(s,frame,0);assert(uploadedEpoch[0]==spriteEpoch+0x28000000);assert(crc32(0,s->raw,(32+s->actions*12+s->sequenceCount*4+s->frames*20+s->pixelBytes))==crc);unsigned a[3]={0x00996633,0x7f111111,0xffaabbcc},alpha[3];for(int i=0;i<3;i++)alpha[i]=a[i]>>24;sprite_coat(a,3,4);for(int i=0;i<3;i++)assert(a[i]>>24==alpha[i]);free(entityTextures[0]);free(s->raw);puts("PASS40 actual GPU upload function: Coat-on/off cached stance invalidation/reuse, steady tint, source/alpha preserved, hiding composition");}
