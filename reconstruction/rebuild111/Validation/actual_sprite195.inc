/* SPDX-License-Identifier: MIT. Validated sparse SPR/ACT frame container. */
typedef struct EnemyStream51 EnemyStream51;
typedef struct {unsigned w,h,frames,actions,sequenceCount,anchorX,anchorY,pixelBytes;unsigned *meta,*sequence,*directory;unsigned char *pixels,*raw;unsigned bytesPerPixel,alpha4444;const EnemyStream51*stream51;unsigned*blocks51;unsigned guardian51;unsigned char*appearancePoses58,*material58;Appearance58 appearance58;unsigned actor58,sex58;} SparseSprite;

#include "actor_origin59.h"


static void sprite_set_equipment(unsigned id,unsigned equipment);
static void sprite_load(SparseSprite*s,const char*name,const unsigned char*src,unsigned packed,unsigned size){
 if(size<32||size>16*1024*1024)fail("Sprite size outside bounds");
 unsigned char*p=inflateasset(name,src,packed,size);s->raw=p;memcpy(s,p,32);s->bytesPerPixel=(s->pixelBytes&0x80000000)?2:4;s->alpha4444=(s->pixelBytes>>30)&1;unsigned appearanceFlag58=s->pixelBytes&0x20000000u;s->pixelBytes&=appearanceFlag58?0x1fffffffu:0x3fffffffu;
 if(!((s->w==128&&(s->h==128||s->h==256))||(s->w==256&&s->h==128&&s->alpha4444&&!appearanceFlag58))||s->frames>1024||(s->actions!=40&&s->actions!=48&&s->actions!=56&&s->actions!=64)||s->sequenceCount>8192||s->anchorX>s->w||s->anchorY>s->h)fail("Sprite header mismatch");
 if(s->w*s->h*s->bytesPerPixel>65536)fail("Sprite exceeds GPU slot capacity");
 unsigned bytes=32+s->actions*12+s->sequenceCount*4+s->frames*20;
 if(appearanceFlag58){if(s->bytesPerPixel!=2||s->alpha4444||s->pixelBytes&1)fail("Appearance format invalid");bytes+=s->frames*12+s->pixelBytes/2;}
 if(bytes>size||s->pixelBytes!=size-bytes)fail("Sprite layout mismatch");
 s->meta=(unsigned*)(p+32);s->sequence=s->meta+s->actions*3;s->directory=s->sequence+s->sequenceCount;s->pixels=(unsigned char*)(s->directory+s->frames*5);if(appearanceFlag58){s->appearancePoses58=s->pixels;s->material58=s->pixels+s->frames*12;s->pixels=s->material58+s->pixelBytes/2;}
 for(unsigned i=0;i<s->actions;i++){unsigned*a=s->meta+i*3;if(a[0]>s->sequenceCount||!a[1]||a[1]>s->sequenceCount-a[0]||a[2]<20)fail("Invalid animation sequence");}
 for(unsigned i=0;i<s->sequenceCount;i++)if(s->sequence[i]>=s->frames)fail("Sprite frame index outside bounds");
 for(unsigned i=0;i<s->frames;i++){unsigned*d=s->directory+i*5;if(d[0]>s->w||d[1]>s->h||d[2]>s->w-d[0]||d[3]>s->h-d[1]||d[4]>s->pixelBytes||d[2]*d[3]*s->bytesPerPixel>s->pixelBytes-d[4])fail("Sprite crop outside bounds");}
 actor_origin_correct59(s);
}
