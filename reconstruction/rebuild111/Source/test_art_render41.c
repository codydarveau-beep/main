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


#include "developer.h"

static unsigned gw=512,gh=512,drawCalls;
static float height_at(float x,float y){(void)x;(void)y;return 0;}
static void*gpu_alloc(unsigned n){return calloc(1,n);}
static uint32_t commands[64];
#define NV097_SET_BLEND_FUNC_SFACTOR 1
#define NV097_SET_BLEND_FUNC_DFACTOR 2
static uint32_t*pb_begin(void){return commands;}
static uint32_t*pb_push1(uint32_t*p,unsigned m,unsigned v){assert(m==1||m==2);assert(v==1||v==0x302||v==0x303);return p;}
static void pb_end(uint32_t*p){(void)p;}
static void gpu_sprite(void*t,SparseSprite*s,float x,float y,float z,float scale){assert(t&&s->w==128&&s->h<=256&&isfinite(x)&&isfinite(y)&&isfinite(z)&&scale>0);drawCalls++;}
#include "art_draw39.h"
int main(void){art39_init();Combat g;combat_init(&g,1500,1500,NULL,NULL);float m[16];world_camera(m,g.x,g.y,0,0,.785f,1.2f);Art39State st={0};art39_observe(&st,&g,0);
for(unsigned c=0;c<20;c++)for(int frame=0;frame<60;frame++){art39DrawCount=0;drawCalls=0;art39_world(c,frame*.033f,m,g.x,g.y,1.2f,1);assert(art39DrawCount==1&&drawCalls==1);unsigned*d=art39Sprites[c].directory+art39Uploads[0]*5;unsigned char*actual=art39Textures[0];for(unsigned y=0;y<d[3];y++)assert(!memcmp(actual+((d[1]+y)*128+d[0])*2,art39Sprites[c].pixels+d[4]+y*d[2]*2,d[2]*2));}
art39DrawCount=0;art39_one(0,0,10000,10000,0,1,1,0,0);assert(!art39DrawCount);art39_one(0,99,320,240,0,1,0,0,0);assert(!art39DrawCount);
for(int i=0;i<100;i++)art39_world(i%20,0,m,g.x,g.y,1.2f,1);assert(art39DrawCount==ART39_DRAW_LIMIT);
/* Air phase exists during the final cast interval, before impact. */
Combat cast;combat_init(&cast,1500,1500,NULL,NULL);cast.spellCastId=3;cast.spellCastLeft=.2f;cast.spellCastTotal=1;cast.spellCastTarget=0;cast.mobs[0].enabled=1;cast.mobs[0].hp=100;cast.mobs[0].x=cast.x;cast.mobs[0].y=cast.y;Art39State flight={0};art39_observe(&flight,&cast,0);art39DrawCount=0;art39_draw(&flight,&cast,m,1.2f);int found=0;for(int j=0;j<art39DrawCount;j++)found|=art39Sources[j]==15;assert(found);cast.spellCastLeft=0;cast.fxSkill=3;cast.fxAt=cast.time=1;cast.fxX=cast.x;cast.fxY=cast.y;art39_observe(&flight,&cast,0);assert(flight.events[0].lead==.4f);
/* New flight/aura paths are visible before completion; frozen art holds. */
cast.spellCastId=24;cast.spellCastLeft=.175f;art39DrawCount=0;art39_draw(&flight,&cast,m,1.2f);int orb=0,aura=0;for(int j=0;j<art39DrawCount;j++){orb|=art39Sources[j]==18;aura|=art39Sources[j]==19;}assert(orb&&aura);
Combat ice;combat_init(&ice,1500,1500,NULL,NULL);ice.mobs[0].enabled=1;ice.mobs[0].hp=20;ice.mobs[0].x=ice.x;ice.mobs[0].y=ice.y;ice.mobs[0].frozenLeft=20;ice.mobs[0].freezeAt=1;ice.time=2;Art39State quiet={0};for(int j=0;j<ART39_EVENTS;j++)quiet.events[j].clip=-1;art39DrawCount=0;art39_draw(&quiet,&ice,m,1.2f);assert(art39DrawCount==1&&art39Sources[0]==2);unsigned frozenFrame=art39Uploads[0];ice.time=9;art39DrawCount=0;art39_draw(&quiet,&ice,m,1.2f);assert(art39Uploads[0]==frozenFrame);
art39DrawCount=0;art_storm41(m,g.x,g.y,.4f,1.2f);assert(art39DrawCount==5);for(int j=0;j<art39DrawCount;j++)assert(art39Sources[j]==17);
for(int i=0;i<ART39_EVENTS;i++)st.events[i]=(Art39Event){i%10,g.x,g.y,0,0};g.energyCoatLeft=10;
for(int i=0;i<COMBAT_BARRIERS;i++){g.barriers[i].x=g.x;g.barriers[i].y=g.y;g.barriers[i].axisX=1;g.barriers[i].expires=10;for(int c=0;c<3;c++)g.barriers[i].hits[c]=5;}
for(int i=0;i<COMBAT_FIELDS;i++){g.fields[i].x=g.x;g.fields[i].y=g.y;g.fields[i].remaining=2;g.fields[i].expected=3;g.fields[i].nextAt=.5;}
for(int i=0;i<MOB_COUNT;i++){g.mobs[i].enabled=1;g.mobs[i].hp=20;g.mobs[i].frozenLeft=10;g.mobs[i].x=g.x;g.mobs[i].y=g.y;}
art39DrawCount=0;art39_draw(&st,&g,m,1.2f);assert(art39DrawCount==ART39_DRAW_LIMIT);
for(int i=0;i<ART39_COUNT;i++)free(art39Sprites[i].raw);for(int i=0;i<ART39_DRAW_LIMIT;i++)free(art39Textures[i]);puts("PASS40 actual artwork draw traversal:1200 clip/frame uploads, sparse pixels/cache, culling/expiry,24-slot cap and saturated simultaneous fields/status/events");}
