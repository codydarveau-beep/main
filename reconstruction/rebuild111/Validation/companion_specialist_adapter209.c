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
static unsigned after209;
static void hit209(Combat*g,CampaignFollower200*m,int target,unsigned life,int damage,unsigned magic){(void)m;(void)life;assert(magic==1);damage204=damage;if(scenario204&16)g->mobs[target].hp=0;}
static void cue209(Combat*g,unsigned skill,float x,float y){(void)g;(void)skill;(void)x;(void)y;}
static void after_effect209(Combat*g,CampaignFollower200*m,int target,unsigned skill,unsigned rank){(void)m;(void)rank;if(g->mobs[target].hp<=0)return;if(skill==438)after209=1;else if(skill==439&&mobClassData50[g->mobs[target].kind][1]==1)after209=2;}
void step209(unsigned skill,unsigned rank,unsigned remaining,unsigned paid,unsigned points,unsigned intelligence,unsigned level,unsigned jl,unsigned kind,unsigned primed,unsigned seed,unsigned scenario,unsigned*out){
 scenario204=scenario;fail204=0;Combat*g=&fixture204;memset(g,0,sizeof(*g));g->hp=100;g->sp=77;g->time=10;g->mapId=3;g->rng=seed;g->x=g->y=100;CombatMob*e=g->mobs;e->enabled=1;e->kind=kind;e->hp=100000;e->x=112;e->y=100;e->life=123;
 CampaignFollower200 m={0};m.id=skill<438?14:18;m.job=skill<438?41:45;m.level=level;m.jobLevel=jl;m.hp=100;m.sp=points;m.stats[3]=intelligence;m.pendingTarget=0;m.pendingLife=123;m.pendingSkill=m.lastSkill=skill;m.pendingRank=rank;m.remainingHits204=remaining;m.impactPaid209=paid;m.esmaUntil209=primed?11:0;m.x=m.y=100;m.impactAt=10;
 unsigned char b[640];party_progress_empty200(b);PartyGrowth200 progress={level,0,jl,0,m.job,100,points};assert(party_progress_put200(b,m.id,&progress));campaignPartyState200=&record204;assert(party_progress_commit200(&record204,b));
 if(scenario&2)g->canAim=blocked204;if(scenario&4)e->x=300;if(scenario&8)e->life++;if(scenario&32)e->enabled=0;
 fail204=scenario&1;damage204=0;after209=0;party_specialist_step209(g,&m,hit209,cue209,after_effect209);out[0]=m.sp;out[1]=m.pendingSkill;out[2]=m.remainingHits204;out[3]=m.impactPaid209;memcpy(out+4,&m.esmaUntil209,4);memcpy(out+5,&m.impactAt,4);memcpy(out+6,&m.attackUntil,4);out[7]=g->rng;out[8]=(unsigned)damage204;out[9]=after209;out[10]=(unsigned)g->sp;fail204=0;npc_state_clear55(&record204);
}

unsigned choice210(unsigned jl,unsigned level,unsigned points,unsigned kind,unsigned primed,unsigned*out){CampaignFollower200 m={0};CombatMob e={0};m.id=18;m.job=45;m.jobLevel=jl;m.level=level;m.sp=points;m.esmaUntil209=primed?11:0;e.kind=kind;return party_soullinker_choice210(&m,&e,10,out);}
