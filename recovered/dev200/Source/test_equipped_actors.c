#define MYRO_HOST
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <zlib.h>
#include "encounter_data.h"
static void fail(const char*s){fprintf(stderr,"%s\n",s);exit(1);}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned packed,unsigned raw){(void)n;unsigned char*b=malloc(raw);assert(b);uLongf size=raw;assert(uncompress(b,&size,p,packed)==Z_OK&&size==raw);return b;}
#include "sprites.h"
int main(){sprite_load_all();unsigned max=0;for(unsigned pass=0;pass<3;pass++)for(unsigned i=0;i<ACTOR_VARIANTS;i++){const ActorBlob*a=&actorBlobs[i];unsigned eq=a->gear==2?16:a->gear==1?1:0;sprite_set_equipment(a->job,eq);assert(spriteJob==a->job&&spriteGear==a->gear);SparseSprite*s=&sprites[0];assert(s->actions==64&&s->bytesPerPixel==2);if(a->raw>max)max=a->raw;for(int group=0;group<8;group++)for(int dir=0;dir<8;dir++)for(int k=0;k<20;k++)assert(sprite_frame(s,group,dir,k*.04,.45,0)<s->frames);unsigned reads=actorDiscReads;sprite_set_equipment(a->job,eq|2|4);assert(actorDiscReads==reads);if(a->gear==1){sprite_set_equipment(a->job,eq|8);assert(actorDiscReads==reads);}if(a->gear){for(int d=0;d<8;d++){unsigned*meta=s->meta+(2*8+d)*3;assert(meta[1]>=5);}}}assert(max<1600000);free(sprites[0].raw);sprites[0].raw=NULL;printf("PASS actual equipped actor disc reads,42variant swaps,64actions/all directions/frame bounds, cache ignores armour/Guard; peak decoded %u bytes\n",max);}
