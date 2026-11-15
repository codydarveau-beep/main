/* MIT. Compare published50a pixels; poison GPU memory to catch CPU composition. */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sanitizer/asan_interface.h>
#include <zlib.h>
#include "combat.h"
#define MYRO_HOST 1
static void fail(const char*s){fprintf(stderr,"%s\n",s);abort();}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned z,unsigned raw){(void)n;(void)p;(void)z;(void)raw;abort();}
#include "sprites.h"
#include "sprite_tint.h"
static void*entityTextures[SPRITE_SLOT_COUNT];static unsigned uploadedFrames[SPRITE_SLOT_COUNT],uploadedEpoch[SPRITE_SLOT_COUNT];static const SparseSprite*uploadedSource[SPRITE_SLOT_COUNT];
static void*gpu_alloc(unsigned n){return calloc(1,n);}
static unsigned char*gpu50b;static unsigned writes50b;
static void*checked_copy50b(void*d,const void*s,size_t n){uintptr_t source=(uintptr_t)s,gpu=(uintptr_t)gpu50b;assert(source<gpu||source>=gpu+65536);if(d==gpu50b){assert(n==65536);__asan_unpoison_memory_region(d,n);writes50b++;}return memcpy(d,s,n);}
static void*checked_clear50b(void*d,int c,size_t n){assert(d!=gpu50b);return memset(d,c,n);}
#define memcpy checked_copy50b
#define memset checked_clear50b
#include "gpu_sprite_upload45.h"
#undef memcpy
#undef memset
/* Frozen published implementation, retained solely as a pixel reference. */
#define spriteFlash49 refFlash
#define uploadedFlash49 refUploadedFlash
#define spriteFrozen refFrozen
#define spritePoison refPoison
#define spriteStone refStone
#define spriteHiddenPlayer refHidden
#define spriteCoatedPlayer refCoated
#define spriteQuickenPlayer45 refQuicken
#define spriteBerserkPlayer45 refBerserk
#define sprite_poisoned ref_poisoned
#define sprite_upload ref_upload
#define uploadedFrames refFrames
#define uploadedEpoch refEpoch
#define uploadedSource refSource
static unsigned refFrames[SPRITE_SLOT_COUNT],refEpoch[SPRITE_SLOT_COUNT];static const SparseSprite*refSource[SPRITE_SLOT_COUNT];
#include "fixtures50b/upload50a.h"
#undef spriteFlash49
#undef uploadedFlash49
#undef spriteFrozen
#undef spritePoison
#undef spriteStone
#undef spriteHiddenPlayer
#undef spriteCoatedPlayer
#undef spriteQuickenPlayer45
#undef spriteBerserkPlayer45
#undef sprite_poisoned
#undef sprite_upload
#undef uploadedFrames
#undef uploadedEpoch
#undef uploadedSource
int main(void){gpu50b=malloc(65536);unsigned char*reference=malloc(65536),pixels[8*5*4];unsigned directory[]={3,7,8,5,0};for(unsigned i=0;i<sizeof(pixels);i++)pixels[i]=(i*37+91)&255;SparseSprite s={0};s.raw=pixels;s.pixels=pixels;s.directory=directory;s.frames=1;s.h=128;spriteEpoch=17;
 for(int mode=0;mode<3;mode++){s.bytesPerPixel=mode==2?4:2;s.alpha4444=mode==1;
  for(unsigned flags=0;flags<256;flags++){
   spriteFrozen[0]=refFrozen[0]=!!(flags&1);spritePoison[0]=refPoison[0]=!!(flags&2);spriteStone[0]=refStone[0]=!!(flags&4);spriteHiddenPlayer=refHidden=!!(flags&8);spriteCoatedPlayer=refCoated=!!(flags&16);spriteQuickenPlayer45=refQuicken=!!(flags&32);spriteBerserkPlayer45=refBerserk=!!(flags&64);spriteFlash49[0]=refFlash[0]=flags&128?0x78abef:0;
   uploadedFrames[0]=refFrames[0]=~0u;entityTextures[0]=reference;ref_upload(&s,0,0);
   unsigned before=writes50b;entityTextures[0]=gpu50b;__asan_poison_memory_region(gpu50b,65536);sprite_upload(&s,0,0);__asan_unpoison_memory_region(gpu50b,65536);assert(writes50b==before+1&&!memcmp(reference,gpu50b,65536));
   __asan_poison_memory_region(gpu50b,65536);sprite_upload(&s,0,0);__asan_unpoison_memory_region(gpu50b,65536);assert(writes50b==before+1&&!memcmp(reference,gpu50b,65536));
  }
 }
 free(gpu50b);free(reference);puts("PASS50b 768 published50a pixel comparisons across1555/4444/RGBA and every status combination; poisoned GPU destination receives one sequential write, no CPU read/compose, and unchanged poses perform zero uploads.");}
