#include "test_companion_fixture205.h"
#define main melee_fixture220
#include "test_companion_melee213.c"
#undef main
static CampaignFollower200*prepare220(unsigned job,unsigned jl){CampaignFollower200*m=prepare213(5,job,jl);m->stats[0]=50;m->stats[4]=100;campaignConfig200.skills[5]=1;campaignConfig200.priority[5]=PARTY_BALANCED200;player201.zeny=54321;return m;}
static CampaignFollower200*triple220(unsigned job,unsigned jl){for(unsigned seed=1;seed<=100;seed++){CampaignFollower200*m=prepare220(job,jl);player201.rng=seed;campaign_battle_tick200(&player201,.01f,0);if(m->pendingSkill==202){assert(m->remainingHits204==3);return m;}}assert(0);return NULL;}
static int deny220(void*p,float x,float y,float a,float b){(void)p;(void)x;(void)y;(void)a;(void)b;return 0;}
int main(void){
 for(unsigned row=0;row<2;row++){
  unsigned job=row?25:18,jl=row?70:50;CampaignFollower200*m=triple220(job,jl);unsigned sp=m->sp,rng=0;int low=INT_MAX,high=0;assert(party_skill_rank193(m,211));
  for(unsigned hit=0;hit<3;hit++){int hp=player201.mobs[0].hp;player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);int damage=hp-player201.mobs[0].hp;assert(damage>0&&m->sp==sp);if(damage<low)low=damage;if(damage>high)high=damage;if(!hit){rng=player201.rng;player201.mobs[0].class50.tarotDef52=900;}else assert(player201.rng==rng);}
  assert(!m->pendingSkill&&high-low<=1&&m->auxSkill220==202&&m->comboUntil220>player201.time&&m->skillAt==player201.time);
  player201.mobs[0].class50.tarotDef52=0;player201.time=fmaxf(m->nextAttack,m->attackUntil)+.0001f;assert(player201.time<m->comboUntil220);campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==211&&m->remainingHits204==4&&m->comboUntil220==0&&m->sp==sp);
  unsigned cost=party_caster_cost194(m,211,m->pendingRank);low=INT_MAX;high=0;for(unsigned hit=0;hit<4;hit++){int hp=player201.mobs[0].hp;player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);int damage=hp-player201.mobs[0].hp;assert(damage>0&&m->sp==sp-cost&&player201.sp==77&&player201.zeny==54321);if(damage<low)low=damage;if(damage>high)high=damage;}
  assert(!m->pendingSkill&&high-low<=1);unsigned char b[640];PartyGrowth200 saved;assert(party_progress_load200(&record201,b)==1);party_growth_read200(b+16+5*32,&saved);assert(saved.sp==m->sp&&saved.hp==m->hp&&saved.exp==1234&&saved.job==job);
  for(unsigned reason=0;reason<7;reason++){
   m=prepare220(job,jl);m->auxSkill220=202;m->comboUntil220=11;m->pendingTarget=0;m->pendingLife=123;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==211&&m->sp==100);int hp=player201.mobs[0].hp;
   if(reason==0)player201.mobs[0].life++;if(reason==1)player201.mobs[0].x=125;if(reason==2)player201.mobs[0].hp=0;if(reason==3)failGrowth200=1;
   if(reason==4){const NpcVariable55*v=npc_state_get55(&record201,PARTY_PROGRESS_KEY200,0);v->text[1279]=v->text[1279]=='0'?'1':'0';}
   if(reason==5){m->sp=0;assert(party_vital_store200(&record201,5,m->level,m->hp,0));}if(reason==6)player201.canAim=deny220;
   unsigned revision=record201.revision,beforeRng=player201.rng;unsigned char before[640],after[640];assert(party_read_hex200(&record201,PARTY_PROGRESS_KEY200,0,before,640)==1);player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);failGrowth200=0;
   assert(!m->pendingSkill&&!m->impactPaid209&&m->sp==(reason==5?0:100)&&player201.sp==77&&player201.zeny==54321&&record201.revision==revision&&player201.rng==beforeRng&&player201.mobs[0].hp==(reason==2?0:hp));assert(party_read_hex200(&record201,PARTY_PROGRESS_KEY200,0,after,640)==1&&!memcmp(before,after,640));
  }
  m=triple220(job,jl);int hp=player201.mobs[0].hp;unsigned revision=record201.revision;const NpcVariable55*invalid=npc_state_get55(&record201,PARTY_PROGRESS_KEY200,0);invalid->text[1279]=invalid->text[1279]=='0'?'1':'0';player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&!m->impactPaid209&&!m->auxSkill220&&!m->comboUntil220&&m->sp==100&&record201.revision==revision&&player201.mobs[0].hp==hp);
  m=prepare220(job,jl);campaignConfig200.skills[5]=0;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==1&&m->remainingHits204==1);
 }
 npc_state_clear55(&record201);puts("PASS actual Suri careers: complete original Trifecta/Quadruple chain, split damage and follow-up window, one durable fee, real impacts and failed-storage/resource preservation. Host only.");
}
