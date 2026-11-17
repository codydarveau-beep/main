#define MYRO_HOST
#define MYRO_DISC_ENEMIES44 1
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include "combat.h"
static void fail(const char*s){fprintf(stderr,"%s\n",s);abort();}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned packed,unsigned raw){(void)n;unsigned char*b=malloc(raw);assert(b);uLongf len=raw;assert(uncompress(b,&len,p,packed)==Z_OK&&len==raw);return b;}
#include "sprites.h"
int main(void){unsigned total=0;assert(guardianSprites162==1);for(unsigned mode=1;mode<2;mode++){for(unsigned bank=7;bank<=8;bank++){unsigned kind=bank==7?448:449;sprite_stream_load51(kind);SparseSprite*s=&sprites[kind+1];fprintf(stderr,"STATE bank%u guardian%u stream%u alpha%u anchor%u,%u canvas%ux%u frames%u\n",bank,s->guardian51,!!s->stream51,s->alpha4444,s->anchorX,s->anchorY,s->w,s->h,s->frames);if(!mode){assert(s->guardian51==bank&&!s->stream51);}else{assert(!s->guardian51&&s->stream51&&s->alpha4444==1&&s->anchorY==630&&s->anchorX==192&&s->w==384&&s->h==768&&s->frames==(bank==7?3624:3760));unsigned metadata=32+40*12+s->sequenceCount*4+s->frames*36;assert(metadata<262144);unsigned transparent=0,visible=0;for(unsigned frame=0;frame<s->frames;frame++){unsigned*d=s->directory+frame*5;assert(d[0]>0&&d[1]>0&&d[0]+d[2]<384&&d[1]+d[3]<768);unsigned char*p=sprite_crop51(s,frame);for(unsigned n=0;n<d[2]*d[3];n++){unsigned short v;memcpy(&v,p+n*2,2);transparent+=(v>>12)==0;visible+=(v>>12)>0;}total++;}assert(visible&&transparent);for(unsigned a=0;a<40;a++)for(unsigned f=0;f<s->meta[a*3+1];f++){assert(sprite_frame(s,a/8,a%8,f*.025f+.0001f,0,1)==s->sequence[s->meta[a*3]+f]);assert(sprite_frame(s,a/8,a%8,f*.025f+.0001f,0,0)==s->sequence[s->meta[a*3]+f]);}printf("PASS bank%u: %u alpha frames, %u metadata bytes, %u transparent crop pixels.\n",bank,s->frames,metadata,transparent);}sprite_release_enemies();}}assert(total==7384);puts("PASS actual sprite-only loader, all crop CRC/decompression, transparency, clipping,40Hz sequencing and map/cache cleanup for both Guardians.");}
