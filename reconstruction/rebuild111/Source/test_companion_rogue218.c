#include "test_companion_fixture205.h"
#define main melee_fixture218
#include "test_companion_melee213.c"
#undef main
static CampaignFollower200*prepare218(unsigned job,unsigned jl){CampaignFollower200*m=prepare213(7,job,jl);m->stats[0]=50;m->stats[4]=100;player201.zeny=54321;player201.mobs[0].faceX=1;return m;}
static int deny218(void*p,float x,float y,float a,float b){(void)p;(void)x;(void)y;(void)a;(void)b;return 0;}
int main(void){
 static const unsigned careers[3][2]={{4,50},{13,50},{27,70}};
 for(unsigned row=0;row<3;row++){
  unsigned job=careers[row][0],jl=careers[row][1];CampaignFollower200*m=prepare218(job,jl);unsigned skill=party_skill_rank193(m,142)?142:13,rank=party_skill_rank193(m,skill),cost=party_caster_cost194(m,skill,rank),sp=m->sp;int hp=player201.mobs[0].hp;assert(rank);
  campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==skill&&m->pendingRank==rank&&m->sp==sp&&!m->impactPaid209&&!campaignArrowNext212);
  player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&m->impactPaid209&&m->sp==sp-cost&&player201.mobs[0].hp<hp&&player201.sp==77&&player201.zeny==54321);if(skill==142)assert(player201.mobs[0].faceX==-1);
  unsigned char b[640];PartyGrowth200 saved;assert(party_progress_load200(&record201,b)==1);party_growth_read200(b+16+7*32,&saved);assert(saved.sp==m->sp&&saved.hp==m->hp&&saved.exp==1234&&saved.job==job&&saved.jobLevel==jl);
  m=prepare218(job,jl);player201.mobs[0].faceX=-1;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==13);player201.time=m->impactAt+.0001f;hp=player201.mobs[0].hp;campaign_battle_tick200(&player201,.01f,0);assert(player201.mobs[0].hp<hp&&m->sp<100);
  for(unsigned reason=0;reason<7;reason++){
   m=prepare218(job,jl);hp=player201.mobs[0].hp;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==skill&&m->sp==100);
   if(reason==0)player201.mobs[0].life++;if(reason==1)player201.mobs[0].x=125;if(reason==2)player201.mobs[0].hp=0;if(reason==3)failGrowth200=1;
   if(reason==4){const NpcVariable55*v=npc_state_get55(&record201,PARTY_PROGRESS_KEY200,0);v->text[1279]=v->text[1279]=='0'?'1':'0';}
   if(reason==5){m->sp=0;assert(party_vital_store200(&record201,7,m->level,m->hp,0));}if(reason==6)player201.canAim=deny218;
   unsigned revision=record201.revision,rng=player201.rng;unsigned char before[640],after[640];assert(party_read_hex200(&record201,PARTY_PROGRESS_KEY200,0,before,640)==1);player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);failGrowth200=0;
   assert(!m->pendingSkill&&!m->impactPaid209&&m->sp==(reason==5?0:100)&&player201.sp==77&&player201.zeny==54321&&record201.revision==revision&&player201.rng==rng&&player201.mobs[0].hp==(reason==2?0:hp)&&!player201.mobs[0].poisonLeft);assert(party_read_hex200(&record201,PARTY_PROGRESS_KEY200,0,after,640)==1&&!memcmp(before,after,640));
  }
  unsigned seed;for(seed=1;seed<=100;seed++){m=prepare218(job,jl);campaignConfig200.priority[7]=PARTY_SUPPORT200;player201.rng=seed;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==1&&!m->pendingRank);if(m->remainingHits204==2)break;}assert(seed<=100);
  hp=player201.mobs[0].hp;player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);int damage=hp-player201.mobs[0].hp;assert(damage>0&&m->pendingSkill==1&&m->remainingHits204==1&&m->impactPaid209&&m->sp==100);unsigned rng=player201.rng,revision=record201.revision;hp=player201.mobs[0].hp;player201.mobs[0].class50.tarotDef52=1000;player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&hp-player201.mobs[0].hp==damage&&player201.rng==rng&&m->sp==100&&record201.revision==revision);
  m=prepare218(job,jl);campaignConfig200.skills[7]=0;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==1&&m->remainingHits204==1&&!m->pendingRank&&m->sp==100);
  m=prepare218(job,jl);campaign_battle_tick200(&player201,.01f,1);assert(!m->pendingSkill&&m->sp==100);
 }
 npc_state_clear55(&record201);puts("PASS Kest actual three-career battle: rear attack, Envenom, cached Double Attack, one deferred saved payment and denied/failed-impact preservation. Host only.");
}
