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
#include "art_assets40.h"
#include "art_visual39.h"
#include "developer.h"
int main(void){unsigned rawTotal=0,frames=0,pixels=0;
 for(int i=0;i<ART39_COUNT;i++){SparseSprite s={0};const Art39Blob*b=&art39Blobs[i];assert(b->offset+b->packed<=sizeof(art39Packed));sprite_load(&s,"art",art39Packed+b->offset,b->packed,b->raw);rawTotal+=b->raw;assert(b->scale>0&&b->scale<=1);for(unsigned f=0;f<s.frames;f++){unsigned*d=s.directory+f*5;assert(d[0]+d[2]<=128&&d[1]+d[3]<=s.h);for(unsigned j=0;j<d[2]*d[3];j++)if(s.pixels[d[4]+2*j+1]&128)pixels++;frames++;}assert(s.frames>0&&pixels);for(int group=0;group<5;group++)for(int dir=0;dir<8;dir++)for(int t=0;t<100;t++)assert(sprite_frame(&s,group,dir,t*.05f,0,1)<s.frames);free(s.raw);}
 assert(rawTotal<3*1024*1024);assert(ART39_COUNT==18);Combat g;combat_init(&g,1500,1500,NULL,NULL);Art39State st={0};art39_observe(&st,&g,0);g.fxSkill=3;g.fxAt=g.time=1;g.fxX=12;g.fxY=34;art39_observe(&st,&g,0);assert(st.events[0].clip==5&&st.events[0].x==12);art39_observe(&st,&g,0);assert(st.next==1);for(int i=2;i<30;i++){g.fxAt=g.time=i;art39_observe(&st,&g,0);}assert(st.next==29);art39_observe(&st,&g,1);assert(!st.next&&st.events[0].clip==-1);g.time=0;art39_observe(&st,&g,1);assert(st.lastTime==0);
 assert(art39_skill_clip(31)==-1&&art39_skill_clip(67)==0&&art39_skill_clip(51)==3&&art39_skill_clip(68)==-1);
 int gaps=0;for(int p=0;p<46;p++)gaps+=cast_quarter_gap(1,p);assert(gaps==4);gaps=0;for(int p=0;p<46;p++)gaps+=cast_quarter_gap(.5,p);assert(gaps==2);assert(!cast_quarter_gap(NAN,0));assert(!cast_quarter_gap(0,0));for(int t=1;t<10000;t++)for(int p=0;p<46;p++){int v=cast_quarter_gap(t*.01f,p);assert(v==0||v==1);}
 DeveloperUI u={0};u.tab=3;u.row=3;dev_input(&u,&g,4096);assert(u.preview==17);dev_input(&u,&g,8192);assert(!u.preview);dev_input(&u,&g,2);assert(u.previewRequest);assert(dev_rows(3)==4);
 /* Actual replacement player path uses embedded composite, not disc fallback. */
 sprite_set_equipment(1,32);assert(spriteJob==1&&spriteGear==3);assert(sprites[0].actions==64);unsigned epoch=spriteEpoch;sprite_set_equipment(1,32);assert(spriteEpoch==epoch);for(int d=0;d<8;d++)for(int i=0;i<10;i++)assert(sprite_frame(&sprites[0],2,d,i*.05f,.45f,0)<sprites[0].frames);free(sprites[0].raw);
 printf("PASS40 native artwork decoder:18 clips,%u frames,%u opaque pixels,%u decoded bytes; variant, event bounds/reset, preview controls and quarter-second marks\n",frames,pixels,rawTotal);
}
