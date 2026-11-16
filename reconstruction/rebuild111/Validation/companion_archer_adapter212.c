#define MYRO_HOST 1
#include <assert.h>
#include "combat.h"
#include "campaign_battle200.h"
static Combat basicGame208;
static unsigned damage208,cues208;
static int blocked208(void*p,float x,float y,float a,float b){(void)p;(void)x;(void)y;(void)a;(void)b;return 0;}
static void hit208(Combat*g,CampaignFollower200*m,int target,unsigned life,int damage,unsigned magic){(void)g;(void)m;assert(target==0&&life==123&&!magic);damage208=(unsigned)damage;}
static void cue208(Combat*g,unsigned skill,float x,float y){(void)g;(void)x;(void)y;assert(skill==2);cues208++;}
void archer212(unsigned rank,unsigned remaining,unsigned job,unsigned jl,unsigned level,unsigned strength,unsigned dex,unsigned luck,unsigned bless,unsigned seed,unsigned scenario,unsigned*out){
 Combat*g=&basicGame208;memset(g,0,sizeof(*g));g->mapId=3;g->x=g->y=100;g->time=10;g->rng=seed;CombatMob*e=g->mobs;e->enabled=1;e->kind=0;e->hp=100000;e->life=123;e->x=164;e->y=100;
 CampaignFollower200 m={0};m.id=8;m.job=job;m.jobLevel=jl;m.level=level;m.hp=100;m.sp=77;m.map=3;m.x=m.y=100;m.stats[0]=strength;m.stats[4]=dex;m.stats[5]=luck;m.buffRank[0]=bless;m.buffUntil[0]=bless?20:0;m.pendingSkill=m.lastSkill=17;m.pendingRank=rank;m.remainingHits204=remaining;m.pendingTarget=0;m.pendingLife=123;m.impactAt=10;
 if(scenario&1)g->canAim=blocked208;if(scenario&2)e->x=197;if(scenario&4)e->life++;if(scenario&8)e->enabled=0;if(scenario&16)g->time=9;
 damage208=0;party_archer_step212(g,&m,hit208);out[0]=m.sp;out[1]=m.pendingSkill;out[2]=m.remainingHits204;out[3]=damage208;out[4]=g->rng;memcpy(out+5,&m.impactAt,4);memcpy(out+6,&m.attackUntil,4);out[7]=(unsigned)combat_mob_flee(e);
}
static NpcState55 archerRecord212;static unsigned cues212;
static void sound212(Combat*g,unsigned effect){(void)g;assert(effect==16);cues212++;}
void begin212(unsigned job,unsigned jl,unsigned points,unsigned agility,unsigned dex,unsigned bless,unsigned agibuff,unsigned enabled,unsigned preference,unsigned cooling,unsigned distance,unsigned counter,unsigned*out){
 Combat*g=&basicGame208;memset(g,0,sizeof(*g));g->mapId=3;g->x=g->y=100;g->hp=100;g->sp=77;g->time=10;CombatMob*e=g->mobs;e->enabled=1;e->kind=0;e->hp=100000;e->life=123;e->x=100+distance;e->y=100;
 CampaignFollower200 m={0};m.id=8;m.job=job;m.jobLevel=jl;m.level=90;m.hp=100;m.sp=points;m.map=3;m.x=m.y=100;m.stats[1]=agility;m.stats[4]=dex;m.buffRank[0]=bless;m.buffRank[1]=agibuff;m.buffUntil[0]=bless?20:0;m.buffUntil[1]=agibuff?20:0;m.target=0;m.targetLife=123;m.thinkAt=1000;m.skillAt=cooling?11:0;
 unsigned char b[640];party_progress_empty200(b);PartyGrowth200 p={90,1234,jl,0,job,100,points};assert(party_progress_put200(b,8,&p));campaignPartyState200=&archerRecord212;assert(party_progress_commit200(campaignPartyState200,b));campaignConfig200.skills[8]=enabled;campaignConfig200.priority[8]=preference;
 memset(campaignArrows212,0,sizeof campaignArrows212);campaignArrowNext212=counter;memset(campaignNativeFx212,0,sizeof campaignNativeFx212);campaignNativeFxNext212=0;partyNativeSound212=sound212;cues212=0;
 party_archer_tick212(g,&m,.01f,0);
 out[0]=m.sp;out[1]=m.pendingSkill;out[2]=m.pendingRank;out[3]=m.remainingHits204;out[4]=(unsigned)m.pendingTarget;out[5]=m.pendingLife;out[6]=m.lastSkill;
 memcpy(out+7,&m.attackAt,4);memcpy(out+8,&m.attackUntil,4);memcpy(out+9,&m.nextAttack,4);memcpy(out+10,&m.impactAt,4);memcpy(out+11,&m.castUntil,4);memcpy(out+12,&m.skillAt,4);out[13]=campaignArrowNext212;out[14]=cues212;memcpy(out+15,campaignArrows212,sizeof campaignArrows212);npc_state_clear55(&archerRecord212);
}
