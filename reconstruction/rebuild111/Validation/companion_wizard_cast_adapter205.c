#define MYRO_HOST 1
#include <assert.h>
#include <stdlib.h>
static unsigned failCast205;
static void*allocCast205(size_t n){return failCast205?NULL:malloc(n);}
#define NPC_STATE_ALLOC55 allocCast205
#define NPC_STATE_FREE55 free
#include "combat.h"
#include "campaign_battle200.h"
_Static_assert(sizeof(CombatField)==6160,"Native shared field layout must remain exact");
static Combat castGame205;static NpcState55 castState205;
static int blockedCast205(void*p,float a,float b,float c,float d){(void)p;(void)a;(void)b;(void)c;(void)d;return 0;}
void cast205(unsigned skill,unsigned rank,unsigned points,unsigned intelligence,unsigned seed,unsigned scenario,unsigned*out,unsigned char*field){Combat*g=&castGame205;memset(g,0,sizeof(*g));g->hp=100;g->mapId=3;g->time=10;g->x=g->y=100;g->rng=seed;CombatMob*enemy=g->mobs;enemy->enabled=1;enemy->kind=0;enemy->hp=100000;enemy->life=123;enemy->x=160;enemy->y=100;CampaignFollower200 m={0};m.id=2;m.map=3;m.hp=100;m.level=20;m.job=9;m.jobLevel=50;m.sp=points;m.pendingSkill=skill;m.pendingRank=rank;m.lastSkill=skill;m.stats[3]=(unsigned char)intelligence;m.x=m.y=100;m.groundX205=160;m.groundY205=100;m.impactAt=10;unsigned char b[640];party_progress_empty200(b);PartyGrowth200 progress={20,0,50,0,9,100,points};failCast205=0;assert(party_progress_put200(b,2,&progress));campaignPartyState200=&castState205;assert(party_progress_commit200(&castState205,b));if(scenario&2)for(unsigned i=0;i<COMBAT_FIELDS;i++)g->fields[i].remaining=1;if(scenario&4)g->canAim=blockedCast205;if(scenario&8)m.groundX205=400;if(scenario&16)enemy->enabled=0;failCast205=scenario&1;party_wizard_cast205(g,&m);failCast205=0;out[0]=m.sp;out[1]=m.pendingSkill;out[2]=g->rng;memcpy(field,g->fields,6160);npc_state_clear55(&castState205);}
