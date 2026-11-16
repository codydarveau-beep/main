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
void begin217(unsigned identity,unsigned job,unsigned jl,unsigned points,unsigned agility,unsigned dex,unsigned bless,unsigned agibuff,unsigned enabled,unsigned preference,unsigned cooling,unsigned distance,unsigned counter,unsigned kind,unsigned traits,unsigned stunned,unsigned*out){
 Combat*g=&basicGame208;memset(g,0,sizeof(*g));g->mapId=3;g->x=g->y=100;g->hp=100;g->sp=77;g->time=10;CombatMob*e=g->mobs;e->enabled=1;e->kind=(int)kind;e->training=traits?1:0;e->testTraits=(int)traits;e->stun=(float)stunned;e->hp=100000;e->life=123;e->x=100+distance;e->y=100;
 CampaignFollower200 m={0};m.id=identity;m.job=job;m.jobLevel=jl;m.level=90;m.hp=100;m.sp=points;m.map=3;m.x=m.y=100;m.stats[1]=agility;m.stats[4]=dex;m.buffRank[0]=bless;m.buffRank[1]=agibuff;m.buffUntil[0]=bless?20:0;m.buffUntil[1]=agibuff?20:0;m.target=0;m.targetLife=123;m.thinkAt=1000;m.skillAt=cooling?11:0;
 unsigned char b[640];party_progress_empty200(b);PartyGrowth200 p={90,1234,jl,0,job,100,points};assert(party_progress_put200(b,identity,&p));campaignPartyState200=&archerRecord212;assert(party_progress_commit200(campaignPartyState200,b));campaignConfig200.skills[identity]=enabled;campaignConfig200.priority[identity]=preference;
 memset(campaignArrows212,0,sizeof campaignArrows212);campaignArrowNext212=counter;memset(campaignNativeFx212,0,sizeof campaignNativeFx212);campaignNativeFxNext212=0;partyNativeSound212=sound212;cues212=0;
 party_blacksmith_tick217(g,&m,.01f,0);
 out[0]=m.sp;out[1]=m.pendingSkill;out[2]=m.pendingRank;out[3]=m.remainingHits204;out[4]=(unsigned)m.pendingTarget;out[5]=m.pendingLife;out[6]=m.lastSkill;
 memcpy(out+7,&m.attackAt,4);memcpy(out+8,&m.attackUntil,4);memcpy(out+9,&m.nextAttack,4);memcpy(out+10,&m.impactAt,4);memcpy(out+11,&m.castUntil,4);memcpy(out+12,&m.skillAt,4);out[13]=campaignArrowNext212;out[14]=cues212;memcpy(out+15,campaignArrows212,sizeof campaignArrows212);npc_state_clear55(&archerRecord212);
}

static void cue217(Combat*g,unsigned skill,float x,float y){(void)g;(void)x;(void)y;assert(skill==230);cues208++;}
void hammer217(unsigned job,unsigned jl,unsigned rank,unsigned points,unsigned kind,unsigned seed,unsigned scenario,unsigned*out){
 Combat*g=&basicGame208;memset(g,0,sizeof(*g));g->mapId=3;g->level=100;g->x=g->y=100;g->time=10;g->rng=seed;g->sp=77;
 for(unsigned i=0;i<3;i++){CombatMob*e=g->mobs+i;e->enabled=1;e->kind=kind;e->hp=100000;e->life=123;e->x=i==0?164:i==1?180:185;e->y=100;}
 CampaignFollower200 m={0};m.id=11;m.job=job;m.jobLevel=jl;m.level=90;m.hp=100;m.sp=points;m.map=3;m.x=m.y=100;m.pendingSkill=m.lastSkill=230;m.pendingRank=rank;m.remainingHits204=1;m.pendingTarget=0;m.pendingLife=123;m.impactAt=10;
 unsigned char b[640];party_progress_empty200(b);PartyGrowth200 p={90,1234,jl,0,job,100,points};assert(party_progress_put200(b,11,&p));campaignPartyState200=&archerRecord212;assert(party_progress_commit200(campaignPartyState200,b));
 if(scenario&1)g->canAim=blocked208;if(scenario&2)g->mobs[0].x=181;if(scenario&4)g->mobs[0].life++;if(scenario&8)g->mobs[0].enabled=0;if(scenario&16)g->time=9;if(scenario&32)g->mobs[1].frozenLeft=2;if(scenario&64)g->mobs[1].stun=2.5f;if(scenario&128)g->mobs[1].stoneLeft=2;if(scenario&256){g->mobs[1].training=1;g->mobs[1].testTraits=3;}
 cues208=0;party_blacksmith_step217(g,&m,hit208,cue217);out[0]=m.sp;out[1]=m.pendingSkill;out[2]=m.impactPaid209;out[3]=g->rng;for(unsigned i=0;i<3;i++)memcpy(out+4+i,&g->mobs[i].stun,4);out[7]=cues208;for(unsigned i=0;i<3;i++)out[8+i]=(unsigned)g->mobs[i].hp;out[11]=(unsigned)g->sp;npc_state_clear55(&archerRecord212);
}
static NpcState55 impactRecord216;
static void cue216(Combat*g,unsigned skill,float x,float y){(void)g;(void)x;(void)y;assert(skill==173||skill==180);cues208++;}
void basic217(unsigned identity,unsigned job,unsigned jl,unsigned skill,unsigned rank,unsigned points,unsigned level,unsigned strength,unsigned dex,unsigned luck,unsigned seed,unsigned scenario,unsigned*out){
 Combat*g=&basicGame208;memset(g,0,sizeof(*g));g->mapId=3;g->x=g->y=100;g->time=10;g->rng=seed;g->sp=77;CombatMob*e=g->mobs;e->enabled=1;e->kind=0;e->hp=100000;e->life=123;e->x=112;e->y=100;
 CampaignFollower200 m={0};m.id=identity;m.job=job;m.jobLevel=jl;m.level=level;m.hp=100;m.sp=points;m.map=3;m.x=m.y=100;m.stats[0]=strength;m.stats[4]=dex;m.stats[5]=luck;m.pendingSkill=m.lastSkill=skill;m.pendingRank=rank;m.remainingHits204=1;m.pendingTarget=0;m.pendingLife=123;m.impactAt=10;
 unsigned char b[640];party_progress_empty200(b);PartyGrowth200 p={level,1234,jl,0,job,100,points};assert(party_progress_put200(b,identity,&p));campaignPartyState200=&impactRecord216;assert(party_progress_commit200(campaignPartyState200,b));
 if(scenario&1)g->canAim=blocked208;if(scenario&2)e->x=125;if(scenario&4)e->life++;if(scenario&8)e->enabled=0;if(scenario&16)g->time=9;
 damage208=cues208=0;party_blacksmith_step217(g,&m,hit208,cue216);
 out[0]=m.sp;out[1]=m.pendingSkill;out[2]=m.impactPaid209;out[3]=damage208;out[4]=g->rng;out[5]=cues208;out[6]=(unsigned)combat_mob_flee(e);out[7]=(unsigned)g->sp;npc_state_clear55(&impactRecord216);
}
