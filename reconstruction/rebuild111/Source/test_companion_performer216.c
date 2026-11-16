#include "test_companion_fixture205.h"
#define main melee_fixture216
#include "test_companion_melee213.c"
#undef main
static CampaignFollower200*prepare216(unsigned id,unsigned job,unsigned jl){CampaignFollower200*m=prepare213(id,job,jl);m->stats[0]=40;m->stats[5]=20;player201.zeny=54321;return m;}
int main(void){
 static const unsigned careers[4][3]={{9,15,50},{9,29,70},{10,16,50},{10,30,70}};
 for(unsigned row=0;row<4;row++){
  unsigned id=careers[row][0],job=careers[row][1],jl=careers[row][2],skill=id==9?173:180;CampaignFollower200*m=prepare216(id,job,jl);unsigned rank=party_skill_rank193(m,skill),cost=party_caster_cost194(m,skill,rank),sp=m->sp;int hp=player201.mobs[0].hp;assert(rank);
  player201.mobs[0].x=164;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==skill&&m->pendingRank==rank&&!m->impactPaid209&&m->sp==sp&&campaignArrowNext212==1&&!campaignNativeFxNext212&&player201.mobs[0].hp==hp);assert(campaignArrows212[0].end==m->impactAt&&campaignArrows212[0].start<m->impactAt);
  player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&m->impactPaid209&&m->sp==sp-cost&&player201.sp==77&&player201.zeny==54321&&player201.mobs[0].hp<hp);
  unsigned char b[640];PartyGrowth200 saved;assert(party_progress_load200(&record201,b)==1);party_growth_read200(b+16+id*32,&saved);assert(saved.sp==m->sp&&saved.hp==m->hp&&saved.exp==1234&&saved.job==job&&saved.jobLevel==jl);
  for(unsigned reason=0;reason<6;reason++){
   m=prepare216(id,job,jl);campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==skill&&m->sp==100);hp=player201.mobs[0].hp;
   if(reason==0)player201.mobs[0].life++;
   if(reason==1)player201.mobs[0].x=197;
   if(reason==2)player201.mobs[0].hp=0;
   if(reason==3)failGrowth200=1;
   if(reason==4){const NpcVariable55*v=npc_state_get55(&record201,PARTY_PROGRESS_KEY200,0);v->text[1279]=v->text[1279]=='0'?'1':'0';}
   if(reason==5){m->sp=0;assert(party_vital_store200(&record201,id,m->level,m->hp,0));}
   unsigned revision=record201.revision;unsigned char before[640],after[640];assert(party_read_hex200(&record201,PARTY_PROGRESS_KEY200,0,before,640)==1);
   player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);failGrowth200=0;
   assert(!m->pendingSkill&&!m->impactPaid209&&m->sp==(reason==5?0:100)&&player201.sp==77&&player201.zeny==54321&&record201.revision==revision&&player201.mobs[0].hp==(reason==2?0:hp));assert(party_read_hex200(&record201,PARTY_PROGRESS_KEY200,0,after,640)==1&&!memcmp(before,after,640));
  }
  for(unsigned basic=0;basic<4;basic++){
   m=prepare216(id,job,jl);if(basic==0)campaignConfig200.skills[id]=0;if(basic==1)campaignConfig200.priority[id]=PARTY_SUPPORT200;if(basic==2)m->skillAt=11;if(basic==3){m->sp=0;assert(party_vital_store200(&record201,id,m->level,m->hp,0));}
   hp=player201.mobs[0].hp;sp=m->sp;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==1&&!m->pendingRank&&m->sp==sp&&campaignArrowNext212==1);player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&m->sp==sp&&player201.mobs[0].hp<hp);
  }
  m=prepare216(id,job,jl);campaign_battle_tick200(&player201,.01f,1);assert(!m->pendingSkill&&!campaignArrowNext212&&m->sp==100);
  m=prepare216(id,job,jl);player201.peaceful=1;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&!campaignArrowNext212&&m->sp==100);
 }
 npc_state_clear55(&record201);puts("PASS Oren and Lale actual ranged careers: original choices, arrows, deferred saved own-SP payment, real hits/basic fallback and denied-impact preservation. Host only.");
}
