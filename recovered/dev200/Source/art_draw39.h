#include "interior_rooms181.h"
/* MIT. Sampled original STR clips, one fixed GPU slot per visible instance.
 * RGB is premultiplied offline; ONE+ONE makes the source black transparent.
 * This is a bounded screen-facing prototype, not full original client playback.
 */
#include "projection.h"
/* Per-draw brightness for premultiplied additive artwork; no new textures. */
static unsigned art39Gain200=255;
#include "visual_cache50.h"
#include "art_assets45.h"
#if !defined(MYRO_HOST) || defined(MYRO_DISC_EFFECTS45)
#include "effect_disc45.h"
#endif
#include "art_visual39.h"
#include "spell_geometry41.h"
#include "class_art_needs50.h"
static SparseSprite art39Sprites[ART39_COUNT];static void*art39Textures[ART39_DRAW_LIMIT];
static unsigned art39Uploads[ART39_DRAW_LIMIT],art39Sources[ART39_DRAW_LIMIT],art39DrawCount;
static int art39Preview=-1;static float art39PreviewAt;
static unsigned art50Copy,art50LastCopy;static unsigned art45Job=~0u;static int art45Cart=-1;
#include "art_metadata183.h"
#define ART_CACHE_BYTES183 (256u*1024u)
#include "art_stream183.h"
static unsigned artCacheBytes183,artCacheClock183,artCacheAge183[ART39_COUNT],artCacheUsed183[ART39_COUNT];
static unsigned artCacheTime183,artGpuUsed183[ART39_DRAW_LIMIT];
static void art_retire183(unsigned i){if(!art39Sprites[i].raw)return;free(art39Sprites[i].raw);memset(art39Sprites+i,0,sizeof(art39Sprites[i]));artCacheBytes183-=artStreams183[i].raw;artCacheAge183[i]=artCacheUsed183[i]=0;}
static void art_cache_clear183(void){for(unsigned i=0;i<ART39_COUNT;i++)art_retire183(i);artCacheClock183=0;art_stream_clear183();}
/* Called once after the previous GPU frame has completed, never during draws. */
static void art_cache_frame183(unsigned now){artCacheTime183=now;art_stream_frame183(now);for(unsigned i=0;i<ART39_COUNT;i++)if(art39Sprites[i].raw&&(unsigned)(now-artCacheUsed183[i])>=15000)art_retire183(i);for(unsigned i=0;i<ART39_DRAW_LIMIT;i++)if(art39Textures[i]&&(unsigned)(now-artGpuUsed183[i])>=3000){
#ifdef MYRO_HOST
 free(art39Textures[i]);
#else
 MmFreeContiguousMemory(art39Textures[i]);
#endif
 art39Textures[i]=NULL;art39Uploads[i]=art39Sources[i]=~0u;}}
static void art39_load_clip45(unsigned i){if(i>=ART39_COUNT)return;artCacheUsed183[i]=artCacheTime183;artCacheAge183[i]=++artCacheClock183;if(art39Sprites[i].raw)return;const ArtStream183*b=&artStreams183[i];
 if(b->raw>ART_CACHE_BYTES183)fail("Effect metadata cache bound");while(artCacheBytes183+b->raw>ART_CACHE_BYTES183){int victim=-1;for(unsigned k=0;k<ART39_COUNT;k++)if(art39Sprites[k].raw&&(victim<0||artCacheAge183[k]<artCacheAge183[victim]))victim=(int)k;if(victim<0)fail("Effect metadata accounting invalid");art_retire183((unsigned)victim);}art_stream_load183(i);artCacheBytes183+=b->raw;
}

static void art39_prepare45(unsigned job,int cart){if(cart<0||cart>4)cart=0;if(job==art45Job&&((job_first50(job)!=6&&job!=J52_SUPER_NOVICE)||cart==art45Cart)&&art50Copy==art50LastCopy)return;
#ifndef MYRO_HOST
 while(pb_busy()){}
#endif
 if(job!=art45Job&&visualCacheRelease50)visualCacheRelease50();
 unsigned baseJob=job_parent52(job);unsigned char need[ART39_COUNT]={0};static const unsigned core[]={1,5,15,24,FX50_ARROW_PROJECTILE};for(unsigned i=0;i<sizeof(core)/sizeof(core[0]);i++)need[core[i]]=1;
 if(baseJob==2||baseJob==8||baseJob==9||baseJob==10){for(int i=41;i<=46;i++)need[i]=1;for(int i=48;i<=50;i++)need[i]=1;unsigned list[]={0,2,4,6,8,16,17,18};for(unsigned i=0;i<8;i++)need[list[i]]=1;}
 if(baseJob==1||baseJob==7||baseJob==11)need[21]=1;if(baseJob==7)need[25]=1;
 if(baseJob==3)need[3]=1;if(baseJob==6){need[9]=1;need[10+cart]=1;}
 if(baseJob==8||baseJob==9){need[7]=1;for(unsigned i=20;i<=24;i++)need[i]=1;need[26]=1;for(int i=37;i<=40;i++)need[i]=1;}
 if(baseJob==10){need[27]=need[28]=need[29]=1;for(int i=32;i<=35;i++)need[i]=1;}
 if(baseJob==3)need[45]=1;
 class_art_needs50(need,job,art50Copy);
 if(baseJob==11){need[30]=need[31]=need[36]=need[47]=1;}
 if((job_first50(job)==6||job==J52_SUPER_NOVICE))need[10+cart]=1;
 for(unsigned i=0;i<ART39_COUNT;i++)if(!need[i]&&art39Sprites[i].raw)art_retire183(i);
 /* Decode only when a visible effect actually requests this clip. */
 for(unsigned i=0;i<ART39_DRAW_LIMIT;i++)art39Uploads[i]=art39Sources[i]=~0u;art45Job=job;art45Cart=cart;art50LastCopy=art50Copy;
}
/* Keep only currently displayed Tarot cards decoded, rather than all fourteen. */
static void art39_tarot_prepare52(const Combat*g){unsigned mask=0;for(unsigned i=0;i<MOB_COUNT;i++){const CombatMob*m=g->mobs+i;int card=m->class50.tarotVisual52;if(m->enabled&&card>=1&&card<=14&&g->time-m->class50.tarotVisualAt52>=0&&g->time-m->class50.tarotVisualAt52<3)mask|=1u<<(card-1);}for(unsigned i=0;i<14;i++)if(!(mask&(1u<<i)))art_retire183(FX52_TAROT_BASE+i);}
static void art39_init(void){art_cache_clear183();art39_prepare45(0,0);for(unsigned i=0;i<ART39_DRAW_LIMIT;i++){art39Textures[i]=NULL;art39Uploads[i]=art39Sources[i]=~0u;artGpuUsed183[i]=0;}}
static void art39_one(unsigned clip,float elapsed,float x,float y,float depth,float scale,int loop,int group,int direction){
 if(clip>=ART39_COUNT||elapsed<0||art39DrawCount>=ART39_DRAW_LIMIT||!isfinite(x)||!isfinite(y))return;
 const ArtMetadata183*meta=artMetadata183+clip;if(!loop&&elapsed>=meta->durationMs/1000.f)return;
 float rect[4];sprite_screen_rect(x,y,scale,meta->anchorX,meta->anchorY,meta->h,rect);if(rect[0]+rect[2]<0||rect[0]>640||rect[1]+rect[3]<0||rect[1]>480)return;
 art39_load_clip45(clip);SparseSprite*s=&art39Sprites[clip];unsigned frame=sprite_frame(s,group,direction,elapsed,0,1);
 unsigned slot=art39DrawCount++;artGpuUsed183[slot]=artCacheTime183;if(!art39Textures[slot])art39Textures[slot]=gpu_alloc(65536);
 if(art39Uploads[slot]!=frame||art39Sources[slot]!=clip){unsigned*d=s->directory+frame*5;const unsigned char*pixels=art_stream_crop183(clip,frame);unsigned char*dest=art39Textures[slot];memset(dest,0,65536);for(unsigned y=0;y<d[3];y++)memcpy(dest+((d[1]+y)*128+d[0])*2,pixels+y*d[2]*2,d[2]*2);art39Uploads[slot]=frame;art39Sources[slot]=clip;}
 uint32_t*p=pb_begin();if(art39Gain200<255&&clip>=15&&clip<51){p=pb_push1(p,NV097_SET_BLEND_COLOR,(art39Gain200<<24)|0xffffffu);p=pb_push1(p,NV097_SET_BLEND_FUNC_SFACTOR,NV097_SET_BLEND_FUNC_SFACTOR_V_CONSTANT_ALPHA);}else p=pb_push1(p,NV097_SET_BLEND_FUNC_SFACTOR,clip>=51?1:(clip<10||clip>=15)?1:0x302);p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,clip>=51?0x303:(clip<10||clip>=15)?1:0x303);pb_end(p);
 gpu_sprite(art39Textures[slot],s,x,y,depth,scale);
 p=pb_begin();p=pb_push1(p,NV097_SET_BLEND_FUNC_SFACTOR,0x302);p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,0x303);pb_end(p);
}
static void art_gpu_release172(void){
#ifndef MYRO_HOST
while(pb_busy()){}
#endif
for(unsigned i=0;i<ART39_DRAW_LIMIT;i++){if(art39Textures[i]){
#ifdef MYRO_HOST
free(art39Textures[i]);
#else
MmFreeContiguousMemory(art39Textures[i]);
#endif
}art39Textures[i]=NULL;art39Uploads[i]=art39Sources[i]=~0u;}}
static void art39_world_z45(unsigned clip,float elapsed,const float*m,float x,float y,float zoom,int loop,float lift){if(!rooms_point181(&interiorRooms181,x,y)||clip>=ART39_COUNT||x<0||y<0||x>=gw*8||y>=gh*8)return;float sx,sy;world_project(m,x,y,height_at(x,y)+lift,&sx,&sy);float depth=m[8]*x+m[9]*y+m[10]*(height_at(x,y)+lift)+m[11]-WORLD_SPRITE_BIAS*2;art39_one(clip,elapsed,sx,sy,depth,zoom/(3*art39Blobs[clip].scale),loop,0,0);}
static void art39_world(unsigned clip,float elapsed,const float*m,float x,float y,float zoom,int loop){art39_world_z45(clip,elapsed,m,x,y,zoom,loop,0);}
static void art_fireball41(const float*m,float sx,float sy,float tx,float ty,float phase,float zoom){if(phase<0||phase>=1)return;float x=sx+(tx-sx)*phase,y=sy+(ty-sy)*phase,px,py,z=height_at(x,y)+14;world_project(m,x,y,z,&px,&py);float depth=m[8]*x+m[9]*y+m[10]*z+m[11]-WORLD_SPRITE_BIAS*2;art39_one(18,phase*.35f,px,py,depth,zoom/(3*.5f),1,0,0);}
static void art_storm41(const float*m,float x,float y,float elapsed,float zoom){if(elapsed<0)return;for(int b=0;b<5;b++){float age=elapsed-b*.08f;if(age<0)continue;int pulse=(int)(age/.5f);float dx,dy;spell_storm_point41(b,pulse,&dx,&dy);art39_world(17,fmodf(age,.5f),m,x+dx,y+dy,zoom,0);}}
#include "classic_draw49.h"
#include "class_draw50.h"
static void art39_draw(const Art39State*s,const Combat*g,const float*m,float zoom){
 classic_persistent49(g,m,zoom);class_persistent_draw50(g,m,zoom);
 for(int i=0;i<CLASS_AREAS50;i++){const ClassArea50*a=&g->areas50[i];if(a->until<=g->time||a->map!=g->mapId)continue;int clip=a->id==135?FX50_VENOMDUST:a->id==189?FX50_SANCTUARY:a->id==197?FX50_MAGNUS:a->id==240?FX50_DEMONSTRATION:-1;if(clip>=0)art39_world(clip,g->time-a->created,m,a->x,a->y,zoom,1);}
 if(homun_alive50(g)&&g->time-g->class50.homunFxAt<3){int h=g->class50.homunFx-1,c=h==0?45:h==4?FX50_CASTLING:h==5?FX50_DEFENSE:h==7?FX50_BLOODLUST:h==15?FX50_SUI_EXPLOSION:-1;if(c>=0)art39_world(c,g->time-g->class50.homunFxAt,m,g->class50.homunX,g->class50.homunY,zoom,0);}

 if(combat_casting(g)&&(g->spellCastId==23||g->spellCastId==78)&&g->spellCastTarget>=0&&g->spellCastTarget<MOB_COUNT){int id=g->spellCastId;const CombatMob*t=&g->mobs[g->spellCastTarget];Art39Event e={.skill=id,.x=t->x,.y=t->y,.startX=g->x,.startY=g->y,.target45=g->spellCastTarget,.life45=t->life,.bolts=1};classic_event49(&e,g,m,zoom,-g->spellCastLeft);}
 if(combat_casting(g)){if(g->spellCastId==24&&g->spellCastLeft<=.35f){int t=g->spellCastTarget;if(t>=0&&t<MOB_COUNT&&g->mobs[t].enabled&&g->mobs[t].hp>0)art_fireball41(m,g->x,g->y,g->mobs[t].x,g->mobs[t].y,1-g->spellCastLeft/.35f,zoom);}}
 /* Let the first bolt reach its impact as the accepted cast timer completes. */
 if(combat_casting(g)&&g->spellCastLeft<=.4f){int air=art_air_clip40(g->spellCastId),target=g->spellCastTarget;if(air>=0&&target>=0&&target<MOB_COUNT){const CombatMob*t=&g->mobs[target];if(t->enabled&&t->hp>0&&!t->hidden){int bolts=skill_rank(g,g->spellCastId);if(bolts>10)bolts=10;for(int b=0;b<bolts;b++)art39_world(air,.4f-g->spellCastLeft-b*.2f,m,t->x,t->y,zoom,0);}}}

 for(int i=0;i<ART39_EVENTS;i++){const Art39Event*e=&s->events[i];float elapsed=g->time-e->at;if(e->clip<0||elapsed<0||elapsed>=4.2f)continue;if(class_event_draw50(e,g,m,zoom,elapsed)||classic_event49(e,g,m,zoom,elapsed))continue;int air=art_air_clip40(e->skill);if(air>=0){int bolts=e->bolts<1?1:e->bolts>10?10:e->bolts;for(int b=0;b<bolts;b++)art39_world(air,elapsed+e->lead-b*.2f,m,e->x,e->y,zoom,0);}if(e->skill==76){float tx=e->x,ty=e->y;if(e->target45>=0&&e->target45<MOB_COUNT&&g->mobs[e->target45].enabled&&g->mobs[e->target45].life==e->life45){tx=g->mobs[e->target45].x;ty=g->mobs[e->target45].y;}float t=elapsed/.25f;if(t<1){float x=e->startX+(tx-e->startX)*t,y=e->startY+(ty-e->startY)*t;float px,py;world_project(m,x,y,height_at(x,y)+16,&px,&py);art39_one(26,elapsed,px,py,WORLD_DEPTH_CENTRE-WORLD_SPRITE_BIAS*3,zoom/(3*.5f),1,0,0);}else art39_world(6,elapsed-.25f,m,tx,ty,zoom,0);continue;}if(e->skill==24&&e->lead==0)art_fireball41(m,e->startX,e->startY,e->x,e->y,elapsed/.35f,zoom);float visualX=e->x,visualY=e->y;if(e->skill>=127&&e->target45>=0&&e->target45<MOB_COUNT&&g->mobs[e->target45].life==e->life45){visualX=g->mobs[e->target45].x;visualY=g->mobs[e->target45].y;}art39_world(e->clip,elapsed-(e->skill==24&&e->lead==0?.35f:air>=0&&e->lead==0?.3f:0),m,e->follow?g->x:visualX,e->follow?g->y:visualY,zoom,0);}
 /* Energy Coat persists through the player upload tint; cast pulse is one-shot. */
 for(int i=0;i<COMBAT_BARRIERS;i++){const CombatBarrier*f=&g->barriers[i];if(f->expires>g->time)for(int c=0;c<3;c++)if(f->hits[c]>0)art39_world(4,g->time,m,f->x+(c-1)*f->axisX*8,f->y+(c-1)*f->axisY*8,zoom,1);}
 for(int i=0;i<COMBAT_FIELDS;i++){const CombatField*f=&g->fields[i];if(f->remaining||g->time<f->fadeUntil){if(!f->secondId)art_storm41(m,f->x,f->y,g->time-(f->nextAt-(f->expected-f->remaining)*.5f),zoom);else if(f->secondId==82){art39_world(23,g->time-f->createdAt45,m,f->x,f->y,zoom,1);}else if(f->secondId==75){for(int n=0;n<f->expected;n++){float age=g->time-f->createdAt45-n;art39_world(37+n%4,age,m,f->meteorX49[n],f->meteorY49[n],zoom,0);}}else if(f->secondId==73){float age=g->time-(f->triggered45?f->triggeredAt45:f->createdAt45);if(f->triggered45){for(int level=0;level<3;level++)art39_world_z45(4,age+level*.1f,m,f->x,f->y,zoom,1,level*6.f);art39_world(21,age,m,f->x,f->y,zoom,0);}else{art39_world(20,age,m,f->x,f->y,zoom,0);art39_world(4,age,m,f->x,f->y,zoom,1);}}else{unsigned clip=f->secondId==75?5:f->secondId==80?22:7;float age=f->secondId==73?(f->triggered45?g->time-f->triggeredAt45:g->time-f->createdAt45):g->time-f->createdAt45;art39_world(clip,age,m,f->x,f->y,zoom,f->secondId==73?!f->triggered45:1);}}}
 for(int i=0;i<MOB_COUNT;i++){const CombatMob*t=&g->mobs[i];if(!t->enabled||t->hp<=0||t->hidden)continue;if(t->frozenLeft>0)art39_world(2,fminf(.55f,fmaxf(0,g->time-t->freezeAt)),m,t->x,t->y,zoom,1);if(t->stoneWait>0)art39_world(8,g->time,m,t->x,t->y,zoom,1);}
 if(art39Preview>=0&&g->time-art39PreviewAt<8){unsigned c=art39Preview;float elapsed=g->time-art39PreviewAt;if(c>=21&&c<29)art39_world(c-1,elapsed,m,g->x,g->y,zoom,1);else if(c==7)art_storm41(m,g->x,g->y,elapsed,zoom);else if(c<10||(c>=15&&c<20))art39_world(c,elapsed,m,g->x,g->y,zoom,c!=0);else if(c<15){float sx,sy;world_project(m,g->x+16,g->y,height_at(g->x+16,g->y),&sx,&sy);art39_one(c,elapsed,sx,sy,WORLD_DEPTH_CENTRE-WORLD_SPRITE_BIAS*3,zoom/3,1,1,0);}}
}
