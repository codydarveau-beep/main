/* MIT. Actual stored casting frames -> native sprite quad -> overhead indicator. */
#include <assert.h>
#include <zlib.h>
#include "combat.h"
#include "projection.h"
#include "cast_indicator.h"
#include "actor_data.h"
#include "player_contact.h"
static unsigned u32(const unsigned char*p){return p[0]|p[1]<<8|p[2]<<16|(unsigned)p[3]<<24;}
int main(int argc,char**argv){assert(argc==2);FILE*f=fopen(argv[1],"rb");assert(f);unsigned char*b=malloc(ACTOR_FILE_BYTES);assert(fread(b,1,ACTOR_FILE_BYTES,f)==ACTOR_FILE_BYTES);fclose(f);unsigned count=0;int minY=480,maxY=0;Combat g;combat_init(&g,1500,1500,NULL,NULL);g.spellCastTotal=5;g.spellCastLeft=2.5f;
 for(unsigned v=0;v<ACTOR_VARIANTS;v++){const ActorBlob*a=&actorBlobs[v];unsigned char*raw=malloc(a->raw);uLongf n=a->raw;assert(uncompress(raw,&n,b+a->offset,a->packed)==Z_OK&&n==a->raw);unsigned actions=u32(raw+12),seq=u32(raw+16),ax=u32(raw+20),ay=u32(raw+24),height=u32(raw+4),directory=32+actions*12+seq*4;
 for(unsigned dir=0;dir<8;dir++){unsigned meta=32+(6*8+dir)*12,start=u32(raw+meta),frames=u32(raw+meta+4);for(unsigned frame=0;frame<frames;frame++){unsigned index=u32(raw+32+actions*12+(start+frame)*4);unsigned cy=u32(raw+directory+index*20+4),hh=u32(raw+directory+index*20+12);assert(hh);for(int z=0;z<3;z++){float scale=(z==0?.85f:z==1?1.2f:1.8f)/3,px=320+playerContact[a->job][dir][0]*scale,py=245+playerContact[a->job][dir][1]*scale,rect[4];sprite_screen_rect(px,py,scale,ax,ay,height,rect);float visibleTop=rect[1]+cy*scale;CastIndicator bar;assert(cast_indicator(&g,px,visibleTop,&bar));assert(bar.y+6<=visibleTop-3&&bar.x>=2&&bar.x+48<=638);if(bar.y<minY)minY=bar.y;if(bar.y>maxY)maxY=bar.y;assert(bar.y>=178&&bar.y+6<240);count++;}}}free(raw);}
 free(b);printf("PASS38 %u actual cast-frame/variant/direction/zoom cases: bar above visible crop, screen bounds, feedback clearance; y%d..%d\n",count,minY,maxY);
}
