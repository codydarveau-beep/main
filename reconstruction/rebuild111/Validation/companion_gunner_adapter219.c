#define MYRO_HOST 1
#include <assert.h>
#include "combat.h"
#include "campaign_battle200.h"
static Combat basicGame208;
static unsigned damage208,cues208;
static int blocked208(void*p,float x,float y,float a,float b){(void)p;(void)x;(void)y;(void)a;(void)b;return 0;}
static void hit208(Combat*g,CampaignFollower200*m,int target,unsigned life,int damage,unsigned magic){(void)g;(void)m;assert(target==0&&life==123&&!magic);damage208=(unsigned)damage;}
static void cue208(Combat*g,unsigned skill,float x,float y){(void)g;(void)x;(void)y;assert(skill==2);cues208++;}
static NpcState55 archerRecord212;static unsigned cues212;
static void sound212(Combat*g,unsigned effect){(void)g;assert(effect==16);cues212++;}
void begin219(unsigned identity,unsigned job,unsigned jl,unsigned points,unsigned agility,unsigned dex,unsigned bless,unsigned agibuff,unsigned enabled,unsigned preference,unsigned cooling,unsigned distance,unsigned counter,unsigned seed,unsigned rear,unsigned spare,unsigned*out){
 Combat*g=&basicGame208;memset(g,0,sizeof(*g));g->mapId=3;g->x=g->y=100;g->hp=100;g->sp=77;g->time=10;CombatMob*e=g->mobs;e->enabled=1;e->kind=0;e->faceX=(float)((int)rear-1);g->rng=seed;(void)spare;e->hp=100000;e->life=123;e->x=100+distance;e->y=100;
 CampaignFollower200 m={0};m.id=identity;m.job=job;m.jobLevel=jl;m.level=90;m.hp=100;m.sp=points;m.map=3;m.x=m.y=100;m.stats[1]=agility;m.stats[4]=dex;m.buffRank[0]=bless;m.buffRank[1]=agibuff;m.buffUntil[0]=bless?20:0;m.buffUntil[1]=agibuff?20:0;m.target=0;m.targetLife=123;m.thinkAt=1000;m.skillAt=cooling?11:0;
 unsigned char b[640];party_progress_empty200(b);PartyGrowth200 p={90,1234,jl,0,job,100,points};assert(party_progress_put200(b,identity,&p));campaignPartyState200=&archerRecord212;assert(party_progress_commit200(campaignPartyState200,b));campaignConfig200.skills[identity]=enabled;campaignConfig200.priority[identity]=preference;
 memset(campaignArrows212,0,sizeof campaignArrows212);campaignArrowNext212=counter;memset(campaignNativeFx212,0,sizeof campaignNativeFx212);campaignNativeFxNext212=0;partyNativeSound212=sound212;cues212=0;
 party_gunner_tick219(g,&m,.01f,0);
 out[0]=m.sp;out[1]=m.pendingSkill;out[2]=m.pendingRank;out[3]=m.remainingHits204;out[4]=(unsigned)m.pendingTarget;out[5]=m.pendingLife;out[6]=m.lastSkill;
 memcpy(out+7,&m.attackAt,4);memcpy(out+8,&m.attackUntil,4);memcpy(out+9,&m.nextAttack,4);memcpy(out+10,&m.impactAt,4);memcpy(out+11,&m.castUntil,4);memcpy(out+12,&m.skillAt,4);out[13]=campaignArrowNext212;out[14]=cues212;memcpy(out+15,campaignArrows212,sizeof campaignArrows212);out[71]=g->rng;npc_state_clear55(&archerRecord212);
}

static unsigned final218,cueCount218;
static void final_hit218(Combat*g,CampaignFollower200*m,int target,unsigned life,int damage){(void)g;(void)m;assert(target==0&&life==123&&damage>=1);final218=(unsigned)damage;}
static void cue218(Combat*g,unsigned skill,float x,float y){(void)g;(void)x;(void)y;assert(skill==378);cueCount218++;}
void impact219(unsigned job,unsigned jl,unsigned skill,unsigned rank,unsigned points,unsigned level,unsigned strength,unsigned dex,unsigned luck,unsigned kind,unsigned seed,unsigned scenario,unsigned remaining,unsigned paid,unsigned cached,unsigned*out){
 Combat*g=&basicGame208;memset(g,0,sizeof(*g));g->mapId=3;g->x=g->y=100;g->level=100;g->time=10;g->rng=seed;g->sp=77;CombatMob*e=g->mobs;e->enabled=1;e->kind=kind;e->hp=100000;e->life=123;e->x=164;e->y=100;e->faceX=1;e->poisonLeft=2.5f;e->poisonTick=.8f;
 CampaignFollower200 m={0};m.id=15;m.job=job;m.jobLevel=jl;m.level=level;m.hp=100;m.sp=points;m.map=3;m.x=m.y=100;m.stats[0]=strength;m.stats[4]=dex;m.stats[5]=luck;m.pendingSkill=m.lastSkill=skill;m.pendingRank=rank;m.remainingHits204=remaining;m.pendingTarget=0;m.pendingLife=123;m.impactAt=10;m.impactPaid209=paid;m.impactDamage218=cached;
 unsigned char b[640];party_progress_empty200(b);PartyGrowth200 p={level,1234,jl,0,job,100,points};assert(party_progress_put200(b,15,&p));campaignPartyState200=&archerRecord212;assert(party_progress_commit200(campaignPartyState200,b));
 if(scenario&1)g->canAim=blocked208;if(scenario&2)e->x=197;if(scenario&4)e->life++;if(scenario&8)e->enabled=0;if(scenario&16)g->time=9;if(scenario&32)e->frozenLeft=2;if(scenario&64)e->stoneLeft=2;
 final218=cueCount218=0;party_cached_physical219(g,&m,final_hit218,cue218,combat_knockback);
 out[0]=m.sp;out[1]=m.pendingSkill;out[2]=m.impactPaid209;out[3]=m.impactDamage218;out[4]=m.remainingHits204;out[5]=g->rng;out[6]=final218;out[7]=cueCount218;
 memcpy(out+8,&m.impactAt,4);memcpy(out+9,&m.attackUntil,4);memcpy(out+10,&e->faceX,4);memcpy(out+11,&e->faceY,4);memcpy(out+12,&e->poisonLeft,4);memcpy(out+13,&e->poisonTick,4);out[14]=(unsigned)g->sp;out[15]=(unsigned)combat_mob_flee(e);npc_state_clear55(&archerRecord212);
}
