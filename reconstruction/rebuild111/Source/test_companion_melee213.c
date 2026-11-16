#include "test_companion_fixture205.h"
static CampaignFollower200*prepare213(unsigned id,unsigned job,unsigned jl){
 CampaignFollower200*m=mage204();m->id=id;m->job=job;m->jobLevel=jl;m->level=90;m->hp=100;m->sp=100;m->stats[1]=40;m->stats[3]=100;m->stats[4]=90;m->life=1234;m->pendingSkill=0;m->nextAttack=m->skillAt=0;m->target=-1;player201.rng=1;player201.mobs[0].x=112;
 unsigned char b[640];assert(party_progress_load200(&record201,b)==1);PartyGrowth200 p={90,1234,jl,0,job,100,100};assert(party_progress_put200(b,id,&p)&&party_progress_commit200(&record201,b));campaignConfig200.skills[id]=1;campaignConfig200.priority[id]=PARTY_BALANCED200;campaignConfig200.mode[id]=PARTY_ASSIST200;memset(campaignArrows212,0,sizeof campaignArrows212);campaignArrowNext212=0;memset(campaignNativeFx212,0,sizeof campaignNativeFx212);campaignNativeFxNext212=0;partyNativeSound212=NULL;return m;
}
int main(void){
 static const unsigned careers[4][3]={{COMP200_BRANN,7,50},{COMP200_BRANN,21,70},{COMP200_IRUGA,12,50},{COMP200_IRUGA,26,70}};
 for(unsigned row=0;row<4;row++){
  unsigned id=careers[row][0],job=careers[row][1],jl=careers[row][2],skill=id==COMP200_BRANN?2:13;CampaignFollower200*m=prepare213(id,job,jl);unsigned sp=m->sp,rank=party_skill_rank193(m,skill),cost=party_skill_cost200(skill,rank);int hp=player201.mobs[0].hp;assert(rank);
  campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==skill&&m->pendingRank==rank&&m->remainingHits204==1&&m->sp==sp-cost&&player201.mobs[0].hp==hp&&!campaignArrowNext212&&campaignNativeFxNext212==(id==COMP200_BRANN?1:0));
  player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&m->sp==sp-cost&&player201.mobs[0].hp<hp&&player201.sp==77);if(id==COMP200_IRUGA)assert(player201.mobs[0].poisonLeft>0&&player201.mobs[0].poisonTick==0);
  unsigned char b[640];PartyGrowth200 saved;assert(party_progress_load200(&record201,b)==1);party_growth_read200(b+16+id*32,&saved);assert(saved.sp==m->sp&&saved.exp==1234&&saved.job==job);
  m=prepare213(id,job,jl);campaignConfig200.priority[id]=PARTY_SUPPORT200;sp=m->sp;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==1&&m->sp==sp&&!campaignNativeFxNext212);
  m=prepare213(id,job,jl);m->sp=0;assert(party_vital_store200(&record201,id,m->level,m->hp,0));campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==1&&m->pendingRank==0&&m->sp==0&&!campaignNativeFxNext212);
  m=prepare213(id,job,jl);unsigned revision=record201.revision;sp=m->sp;failGrowth200=1;campaign_battle_tick200(&player201,.01f,0);failGrowth200=0;assert(!m->pendingSkill&&m->sp==sp&&record201.revision==revision&&!campaignArrowNext212&&!campaignNativeFxNext212);
  m=prepare213(id,job,jl);campaign_battle_tick200(&player201,.01f,1);assert(!m->pendingSkill&&m->sp==100);
 }
 npc_state_clear55(&record201);puts("PASS actual Brann and Iruga careers: own learned physical skills, real hits/poison, durable one-time payment, basic fallback, paused and failed-save preservation. World activation and target playtests remain separate; HOST ONLY.");
}
