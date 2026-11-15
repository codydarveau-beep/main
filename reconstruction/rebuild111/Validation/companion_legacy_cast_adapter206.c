#define MYRO_HOST 1
#include <assert.h>
#include "combat.h"
#include "campaign_battle200.h"
static Combat legacyGame206;static NpcState55 legacyState206;
void legacy206(unsigned job,unsigned jobLevel,unsigned points,unsigned seed,unsigned*out){Combat*g=&legacyGame206;memset(g,0,sizeof(*g));g->hp=100;g->sp=77;g->mapId=3;g->time=10;g->x=g->y=100;g->rng=seed;CombatMob*e=g->mobs;e->enabled=1;e->kind=0;e->hp=100000;e->life=123;e->x=112;e->y=100;CampaignFollower200 m={0};m.id=4;m.map=3;m.job=job;m.jobLevel=jobLevel;m.level=20;m.hp=100;m.sp=points;m.stats[3]=30;m.x=m.y=100;m.pendingSkill=m.lastSkill=51;m.pendingRank=1;m.pendingLife=123;m.pendingTarget=0;m.impactAt=10;unsigned char b[640];party_progress_empty200(b);PartyGrowth200 p={20,0,jobLevel,0,job,100,points};assert(party_progress_put200(b,4,&p));campaignPartyState200=&legacyState206;assert(party_progress_commit200(&legacyState206,b));party_resolve200(g,&m);out[0]=m.sp;out[1]=m.pendingSkill;out[2]=g->rng;out[3]=(unsigned)g->sp;npc_state_clear55(&legacyState206);}

unsigned basic206(unsigned id,unsigned job,unsigned jl){CampaignFollower200 m={0};m.id=id;m.job=job;m.jobLevel=jl;return party_basic_rank206(&m);}
