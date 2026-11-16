#include "test_companion_fixture205.h"
#define main specialist_impact_fixture211
#include "test_companion_specialist209.c"
#undef main
static CampaignFollower200*prepare211(unsigned id,unsigned job,unsigned jl){
 CampaignFollower200*m=special209(352,10,10);m->id=id;m->job=job;m->jobLevel=jl;m->pendingSkill=0;m->nextAttack=m->skillAt=0;m->target=-1;m->regenAt=1000;m->stats[4]=40;
 unsigned char b[640];assert(party_progress_load200(&record201,b)==1);PartyGrowth200 p={90,1234,jl,0,job,100,500};assert(party_progress_put200(b,id,&p)&&party_progress_commit200(&record201,b));
 campaignConfig200.skills[id]=1;campaignConfig200.priority[id]=PARTY_BALANCED200;campaignConfig200.mode[id]=PARTY_ASSIST200;player201.mobs[0].x=164;return m;
}
int main(void){
 static const unsigned careers[3][3]={{COMP200_EDDA,10,50},{COMP200_EDDA,23,70},{COMP200_KAEDE,41,70}};
 for(unsigned row=0;row<3;row++){
  unsigned id=careers[row][0],job=careers[row][1],jl=careers[row][2];CampaignFollower200*m=prepare211(id,job,jl);unsigned rank,chosen=party_elemental_choice211(m,player201.mobs,&rank);assert(chosen&&rank);unsigned sp=m->sp,cost=party_caster_cost194(m,chosen,rank);int hp=player201.mobs[0].hp;
  campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==chosen&&m->pendingRank==rank&&m->castUntil>player201.time&&m->sp==sp&&!m->impactPaid209);
  unsigned hits=m->remainingHits204;assert(hits>0&&hits<=10);
  for(unsigned k=0;k<hits;k++){player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(m->sp==sp-cost&&player201.sp==77);if(k+1<hits)assert(m->pendingSkill==chosen&&m->remainingHits204==hits-k-1);}
  assert(!m->pendingSkill&&player201.mobs[0].hp<hp);
  unsigned char b[640];PartyGrowth200 saved;assert(party_progress_load200(&record201,b)==1);party_growth_read200(b+16+id*32,&saved);assert(saved.sp==m->sp&&saved.exp==1234&&saved.job==job);
  m=prepare211(id,job,jl);sp=m->sp;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill&&m->castUntil>player201.time);assert(party_hurt200(&player201,m,1));assert(!m->pendingSkill&&m->sp==sp&&player201.sp==77);
  m=prepare211(id,job,jl);sp=m->sp;hp=player201.mobs[0].hp;campaign_battle_tick200(&player201,.01f,0);player201.time=m->impactAt+.0001f;failGrowth200=1;campaign_battle_tick200(&player201,.01f,0);failGrowth200=0;assert(!m->pendingSkill&&m->sp==sp&&player201.mobs[0].hp==hp);
  m=prepare211(id,job,jl);campaignConfig200.skills[id]=0;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill);
 }
 npc_state_clear55(&record201);puts("PASS actual Edda/Kaede candidate careers: original choices, complete real hit series, durable one-time payment, interruption and failed save; world activation and target playtests remain separate. HOST ONLY.");
}
