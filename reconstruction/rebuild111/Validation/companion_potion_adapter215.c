#define MYRO_HOST 1
#include <assert.h>
#include <stdlib.h>
static unsigned failed215;
static void*allocate215(size_t n){return failed215?NULL:malloc(n);}
#define NPC_STATE_ALLOC55 allocate215
#define NPC_STATE_FREE55 free
#include "combat.h"
#include "campaign_battle200.h"
static Combat potionGame215;static NpcState55 potionState215;static unsigned healed215,cues215;
static int blocked215(void*p,float x,float y,float a,float b){(void)p;(void)x;(void)y;(void)a;(void)b;return 0;}
static void number215(Combat*g,float x,float y,int amount){(void)g;(void)x;(void)y;healed215=(unsigned)amount;}
static void cue215(Combat*g,unsigned skill,float x,float y){(void)g;(void)x;(void)y;assert(skill==SKILL_HEAL);cues215++;}
void potion215(unsigned job,unsigned jl,unsigned points,unsigned preference,unsigned enabled,unsigned cooling,unsigned distance,unsigned recipient,unsigned vitality,unsigned potions,unsigned blocked,unsigned failure,unsigned*out,unsigned char*raw){
 Combat*g=&potionGame215;memset(g,0,sizeof(*g));g->mapId=3;g->x=g->y=100;g->hp=recipient==0?1:1000;g->maxhp=1000;g->sp=77;g->zeny=54321;g->time=10;g->stats[2]=vitality;if(blocked)g->canAim=blocked215;owned_init52(&g->owned52);if(potions)assert(owned_add52(&g->owned52,0,501,potions,item_rule52)==OWNED_OK52);
 memset(&campaignParty200,0,sizeof campaignParty200);campaignParty200.count=2;CampaignFollower200*m=campaignParty200.members;m->id=12;m->job=job;m->jobLevel=jl;m->level=90;m->hp=recipient==2?1:100;m->maxHP=100;m->sp=points;m->map=3;m->initialized=1;m->life=1234;m->x=100+distance;m->y=100;m->stats[2]=vitality;m->skillAt=cooling?11:0;
 CampaignFollower200*a=m+1;a->id=4;a->job=3;a->jobLevel=2;a->level=20;a->map=3;a->initialized=1;a->hp=recipient==1?1:100;a->maxHP=100;a->sp=10;a->x=a->y=100;a->life=123;a->stats[2]=vitality;
 unsigned char b[640];party_progress_empty200(b);PartyGrowth200 p={90,1234,jl,0,job,m->hp,points},friend={20,1234,2,0,3,a->hp,10};assert(party_progress_put200(b,12,&p)&&party_progress_put200(b,4,&friend));npc_state_put32_55(b+12,17);campaignPartyState200=&potionState215;assert(party_progress_commit200(campaignPartyState200,b));campaignConfig200.skills[12]=enabled;campaignConfig200.priority[12]=preference;healed215=cues215=0;
 if(failure==2){const NpcVariable55*v=npc_state_get55(campaignPartyState200,PARTY_PROGRESS_KEY200,0);v->text[1279]=v->text[1279]=='0'?'1':'0';}
 unsigned revision=potionState215.revision;failed215=failure==1;unsigned handled=(unsigned)party_maya_support215(g,m,0,number215,cue215);failed215=0;
 out[0]=handled;out[1]=m->sp;out[2]=m->hp;out[3]=a->hp;out[4]=(unsigned)g->hp;out[5]=(unsigned)g->sp;out[6]=(unsigned)inventory_count(g,inventory_catalog52(501));out[7]=m->lastSkill;memcpy(out+8,&m->attackAt,4);memcpy(out+9,&m->attackUntil,4);memcpy(out+10,&m->nextAttack,4);memcpy(out+11,&m->skillAt,4);out[12]=healed215;out[13]=cues215;out[14]=(unsigned)g->zeny;out[15]=(unsigned)stat_value(g,2);out[16]=potionState215.revision-revision;
 assert(party_read_hex200(campaignPartyState200,PARTY_PROGRESS_KEY200,0,raw,640)==1);npc_state_clear55(&potionState215);
}
