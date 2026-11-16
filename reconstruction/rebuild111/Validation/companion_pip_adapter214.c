#define MYRO_HOST 1
#include <assert.h>
#include <stdlib.h>
static unsigned failed214;
static void*allocate214(size_t n){return failed214?NULL:malloc(n);}
#define NPC_STATE_ALLOC55 allocate214
#define NPC_STATE_FREE55 free
#include "combat.h"
#include "campaign_battle200.h"
static Combat pipGame214;static NpcState55 pipState214;static unsigned resolved214;
static int blocked214(void*p,float x,float y,float a,float b){(void)p;(void)x;(void)y;(void)a;(void)b;return 0;}
static void resolve214(Combat*g,CampaignFollower200*m){(void)g;assert(m->pendingSkill==10);resolved214++;}
void pip214(unsigned jl,unsigned points,unsigned preference,unsigned enabled,unsigned cooling,unsigned distance,unsigned recipient,unsigned blocked,unsigned failed,unsigned*out){
 Combat*g=&pipGame214;memset(g,0,sizeof(*g));g->mapId=3;g->x=g->y=100;g->hp=recipient==0?1:1000;g->maxhp=1000;g->sp=77;g->time=10;if(blocked)g->canAim=blocked214;memset(&campaignParty200,0,sizeof campaignParty200);campaignParty200.count=2;
 CampaignFollower200*m=campaignParty200.members;m->id=13;m->job=40;m->jobLevel=jl;m->level=90;m->hp=recipient==2?1:100;m->maxHP=100;m->sp=points;m->map=3;m->initialized=1;m->life=1234;m->x=100+distance;m->y=100;m->skillAt=cooling?11:0;
 CampaignFollower200*a=m+1;a->id=4;a->map=3;a->initialized=1;a->hp=recipient==1?1:100;a->maxHP=100;a->x=a->y=100;a->life=123;
 unsigned char b[640];party_progress_empty200(b);PartyGrowth200 p={90,1234,jl,0,40,m->hp,points};assert(party_progress_put200(b,13,&p));campaignPartyState200=&pipState214;assert(party_progress_commit200(campaignPartyState200,b));campaignConfig200.skills[13]=enabled;campaignConfig200.priority[13]=preference;resolved214=0;failed214=failed;party_pip_heal214(g,m,resolve214);failed214=0;
 out[0]=m->sp;out[1]=m->pendingSkill;out[2]=m->pendingRank;out[3]=(unsigned)m->healTarget;out[4]=m->pendingLife;out[5]=m->lastSkill;memcpy(out+6,&m->attackAt,4);memcpy(out+7,&m->attackUntil,4);memcpy(out+8,&m->nextAttack,4);memcpy(out+9,&m->impactAt,4);memcpy(out+10,&m->castUntil,4);memcpy(out+11,&m->skillAt,4);out[12]=resolved214;out[13]=(unsigned)g->sp;npc_state_clear55(&pipState214);
}
