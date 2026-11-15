#define MYRO_HOST 1
#include <assert.h>
#include <stdlib.h>
static unsigned scenario204,fail204;
static void*allocate204(size_t n){return fail204?NULL:malloc(n);}
#define NPC_STATE_ALLOC55 allocate204
#define NPC_STATE_FREE55 free
#include "combat.h"
#include "campaign_battle200.h"
static Combat fixture204;
static NpcState55 record204;
static int damage204;
static int blocked204(void*p,float a,float b,float c,float d){(void)p;(void)a;(void)b;(void)c;(void)d;return 0;}
static void hit204(Combat*g,CampaignFollower200*m,int target,unsigned life,int damage,unsigned magic){(void)g;(void)m;(void)target;(void)life;assert(magic==1);damage204=damage;if(scenario204&16)g->mobs[target].hp=0;}
static void cue204(Combat*g,unsigned skill,float x,float y){(void)g;(void)skill;(void)x;(void)y;}
void step204(unsigned skill,unsigned rank,unsigned remaining,unsigned sp,unsigned intelligence,unsigned seed,unsigned scenario,unsigned*out){scenario204=scenario;fail204=0;memset(&fixture204,0,sizeof fixture204);fixture204.hp=100;fixture204.time=10;fixture204.mapId=3;fixture204.rng=seed;fixture204.x=fixture204.y=100;CombatMob*e=fixture204.mobs;e->enabled=1;e->kind=0;e->hp=100000;e->x=112;e->y=100;e->life=123;CampaignFollower200 m={0};m.id=2;m.job=2;m.level=20;m.jobLevel=50;m.hp=100;m.sp=sp;m.stats[3]=(unsigned char)intelligence;m.pendingTarget=0;m.pendingLife=123;m.pendingSkill=m.lastSkill=skill;m.pendingRank=rank;m.remainingHits204=remaining;m.x=m.y=100;m.impactAt=10;m.nextAttack=0;unsigned char b[640];party_progress_empty200(b);PartyGrowth200 progress={20,0,50,0,2,100,sp};assert(party_progress_put200(b,2,&progress));campaignPartyState200=&record204;assert(party_progress_commit200(&record204,b));if(scenario&2)fixture204.canAim=blocked204;if(scenario&4)e->x=220;if(scenario&8)e->life++;if(scenario&32)e->enabled=0;fail204=scenario&1;damage204=0;party_bolt_step204(&fixture204,&m,hit204,cue204);out[0]=m.sp;out[1]=m.pendingSkill;out[2]=m.remainingHits204;out[3]=(unsigned)damage204;out[4]=fixture204.rng;memcpy(out+5,&m.impactAt,4);memcpy(out+6,&m.nextAttack,4);fail204=0;npc_state_clear55(&record204);}
