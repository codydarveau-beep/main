#define MYRO_HOST 1
#include <assert.h>
#include "combat.h"
#include "campaign_battle200.h"
static Combat basicGame208;
static unsigned damage208,cues208;
static int blocked208(void*p,float x,float y,float a,float b){(void)p;(void)x;(void)y;(void)a;(void)b;return 0;}
static void hit208(Combat*g,CampaignFollower200*m,int target,unsigned life,int damage,unsigned magic){(void)g;(void)m;assert(target==0&&life==123&&!magic);damage208=(unsigned)damage;}
static void cue208(Combat*g,unsigned skill,float x,float y){(void)g;(void)x;(void)y;assert(skill==2);cues208++;}
void venom213(unsigned rank,unsigned job,unsigned jl,unsigned level,unsigned strength,unsigned dex,unsigned luck,unsigned bless,unsigned kind,unsigned seed,unsigned scenario,unsigned*out){
 Combat*g=&basicGame208;memset(g,0,sizeof(*g));g->mapId=3;g->x=g->y=100;g->time=10;g->rng=seed;CombatMob*e=g->mobs;e->enabled=1;e->kind=kind;e->hp=100000;e->life=123;e->x=112;e->y=100;e->poisonLeft=2.5f;e->poisonTick=.8f;
 CampaignFollower200 m={0};m.id=6;m.job=job;m.jobLevel=jl;m.level=level;m.hp=100;m.sp=77;m.map=3;m.x=m.y=100;m.stats[0]=strength;m.stats[4]=dex;m.stats[5]=luck;m.buffRank[0]=bless;m.buffUntil[0]=bless?20:0;m.pendingSkill=m.lastSkill=13;m.pendingRank=rank;m.remainingHits204=1;m.pendingTarget=0;m.pendingLife=123;m.impactAt=10;
 if(scenario&1)g->canAim=blocked208;if(scenario&2)e->x=125;if(scenario&4)e->life++;if(scenario&8)e->enabled=0;if(scenario&16)g->time=9;
 damage208=0;party_envenom_step213(g,&m,hit208,party_poison_after213);out[0]=m.sp;out[1]=m.pendingSkill;out[2]=damage208;out[3]=g->rng;memcpy(out+4,&e->poisonLeft,4);memcpy(out+5,&e->poisonTick,4);out[6]=(unsigned)combat_mob_flee(e);
}
