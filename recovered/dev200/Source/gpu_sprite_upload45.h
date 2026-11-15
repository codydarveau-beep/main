#include "appearance_render58.h"
static unsigned spriteFlash49[SPRITE_SLOT_COUNT],uploadedFlash49[SPRITE_SLOT_COUNT];
static unsigned spriteFrozen[SPRITE_SLOT_COUNT],spritePoison[SPRITE_SLOT_COUNT],spriteStone[SPRITE_SLOT_COUNT];static int spriteHiddenPlayer,spriteCoatedPlayer,spriteQuickenPlayer45,spriteBerserkPlayer45;
static int sprite_poisoned(int slot){return slot>=0&&slot<SPRITE_SLOT_COUNT&&spritePoison[slot];}
/* Compose colours in cached RAM, then stream one write into GPU memory. */
static unsigned char spriteScratch50b[65536] __attribute__((aligned(16)));
static unsigned uploadedTop51[SPRITE_SLOT_COUNT],uploadedBottom51[SPRITE_SLOT_COUNT],uploadedBpp51[SPRITE_SLOT_COUNT],uploadedHeight51[SPRITE_SLOT_COUNT],uploadedWidth180[SPRITE_SLOT_COUNT],uploadedBaseEpoch51[SPRITE_SLOT_COUNT],uploadedBackground51[SPRITE_SLOT_COUNT];
static unsigned long long spriteUploadBytes51;
#include "gpu_stream51.h"
static void sprite_upload(SparseSprite*s,unsigned frame,int slot){
 if(s&&s->guardian51)return;if(s&&s->stream51){sprite_stream_upload51(s,frame,slot);return;}
 if(slot<0||slot>=SPRITE_SLOT_COUNT||!s||!s->raw||frame>=s->frames)fail("Actor upload bounds invalid");/* A cropped streamed enemy may leave less than the legacy64KiB canvas.
  * Restore capacity and invalidate the layout before cache checks or uploads. */
 unsigned capacity51=entityTextures[slot]?(entityCapacity51[slot]?entityCapacity51[slot]:65536):0;
 if(capacity51<65536){if(entityTextures[slot])MmFreeContiguousMemory(entityTextures[slot]);entityTextures[slot]=gpu_alloc(65536);entityCapacity51[slot]=65536;uploadedFrames[slot]=~0u;}
 if(entityCropped51[slot]){uploadedFrames[slot]=~0u;entityCropped51[slot]=0;}
 if(uploadedWidth180[slot]==s->w&&uploadedHeight51[slot]==s->h&&uploadedBpp51[slot]==s->bytesPerPixel&&uploadedFlash49[slot]==spriteFlash49[slot]&&uploadedFrames[slot]==frame&&uploadedSource[slot]==s&&uploadedEpoch[slot]==spriteEpoch+(sprite_poisoned(slot)?0x80000000u:0)+(spriteFrozen[slot]?0x40000000u:0)+(spriteStone[slot]?0x10000000u:0)+((slot==0&&spriteHiddenPlayer)?0x20000000u:0)+((slot==0&&spriteCoatedPlayer)?0x08000000u:0)+((slot==0&&spriteQuickenPlayer45)?0x04000000u:0)+((slot==0&&spriteBerserkPlayer45)?0x02000000u:0))return;unsigned*d=s->directory+frame*5;
 unsigned char*dest=spriteScratch50b;memset(dest,0,128*128*4);
 for(unsigned y=0;y<d[3];y++)memcpy(dest+((d[1]+y)*s->w+d[0])*s->bytesPerPixel,s->pixels+d[4]+y*d[2]*s->bytesPerPixel,d[2]*s->bytesPerPixel);
 unsigned appearanceBounds58[4];appearance_compose58(s,frame,(unsigned)slot,dest,appearanceBounds58);
 if(s->alpha4444){if(spriteFrozen[slot]||spriteStone[slot]||sprite_poisoned(slot))sprite_tint4444_45(dest,s->w*s->h,spriteFrozen[slot],spriteStone[slot],sprite_poisoned(slot));}else{
 if(slot==0&&s->bytesPerPixel==2&&(spriteQuickenPlayer45||spriteBerserkPlayer45))sprite_warm45(dest,s->w*s->h,spriteBerserkPlayer45);if(slot==0&&spriteCoatedPlayer)sprite_coat(dest,s->w*s->h,s->bytesPerPixel);if(spriteFrozen[slot])sprite_ice(dest,s->w*s->h,s->bytesPerPixel);if(slot==0&&spriteHiddenPlayer)sprite_hide(dest,s->w*s->h,s->bytesPerPixel);
 if(sprite_poisoned(slot))sprite_green(dest,s->w*s->h,s->bytesPerPixel);if(spriteStone[slot])sprite_stone(dest,s->w*s->h,s->bytesPerPixel);
}
 if(spriteFlash49[slot])sprite_flash49(dest,s->w*s->h,s->bytesPerPixel,s->alpha4444,spriteFlash49[slot]);/* The composed image is unchanged. Publish only the row band that can differ
  * from the prior image; retain a full copy for a fresh texture/layout/background.
  * A single sequential write avoids CPU reads from write-combined GPU memory. */
 unsigned background=0,pixel=0;
 if(d[1])pixel=0;
 else if(d[1]+d[3]<s->h)pixel=(s->h-1)*s->w;
 else if(d[0])pixel=d[1]*s->w;
 else if(d[0]+d[2]<s->w)pixel=d[1]*s->w+s->w-1;
 memcpy(&background,dest+pixel*s->bytesPerPixel,s->bytesPerPixel);
 unsigned top=appearanceBounds58[1],bottom=appearanceBounds58[3];
 int full=uploadedFrames[slot]==~0u||uploadedBaseEpoch51[slot]!=spriteEpoch||uploadedBpp51[slot]!=s->bytesPerPixel||uploadedHeight51[slot]!=s->h||uploadedWidth180[slot]!=s->w||uploadedBackground51[slot]!=background;
 if(!full){if(uploadedTop51[slot]<top)top=uploadedTop51[slot];if(uploadedBottom51[slot]>bottom)bottom=uploadedBottom51[slot];}
 unsigned offset=full?0:top*s->w*s->bytesPerPixel,bytes=full?65536:(bottom-top)*s->w*s->bytesPerPixel;
 if(bytes)memcpy((unsigned char*)entityTextures[slot]+offset,dest+offset,bytes);
 spriteUploadBytes51+=bytes;uploadedTop51[slot]=appearanceBounds58[1];uploadedBottom51[slot]=appearanceBounds58[3];uploadedBpp51[slot]=s->bytesPerPixel;uploadedHeight51[slot]=s->h;uploadedWidth180[slot]=s->w;uploadedBaseEpoch51[slot]=spriteEpoch;uploadedBackground51[slot]=background;
 uploadedFlash49[slot]=spriteFlash49[slot];
 uploadedFrames[slot]=frame;uploadedSource[slot]=s;uploadedEpoch[slot]=spriteEpoch+(sprite_poisoned(slot)?0x80000000u:0)+(spriteFrozen[slot]?0x40000000u:0)+(spriteStone[slot]?0x10000000u:0)+((slot==0&&spriteHiddenPlayer)?0x20000000u:0)+((slot==0&&spriteCoatedPlayer)?0x08000000u:0)+((slot==0&&spriteQuickenPlayer45)?0x04000000u:0)+((slot==0&&spriteBerserkPlayer45)?0x02000000u:0);
}
