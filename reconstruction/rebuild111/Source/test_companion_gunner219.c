#include "test_companion_fixture205.h"
#define main melee_fixture219
#include "test_companion_melee213.c"
#undef main
static CampaignFollower200*prepare219(void){CampaignFollower200*m=prepare213(15,42,70);m->stats[0]=40;m->stats[4]=100;m->stats[5]=20;player201.mobs[0].x=164;player201.zeny=54321;return m;}
static int deny219(void*p,float x,float y,float a,float b){(void)p;(void)x;(void)y;(void)a;(void)b;return 0;}
int main(void){
 CampaignFollower200*m=prepare219();unsigned rank=party_skill_rank193(m,378),cost=party_caster_cost194(m,378,rank),sp=m->sp;assert(rank);
 campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==378&&m->pendingRank==rank&&m->remainingHits204==5&&!m->impactPaid209&&m->sp==sp&&!campaignArrowNext212);
 int damage=0;unsigned rng=0;for(unsigned hit=0;hit<5;hit++){int hp=player201.mobs[0].hp;player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(m->sp==sp-cost&&player201.sp==77&&player201.zeny==54321&&player201.mobs[0].hp<hp);if(!hit){damage=hp-player201.mobs[0].hp;rng=player201.rng;player201.mobs[0].class50.tarotDef52=900;}else assert(hp-player201.mobs[0].hp==damage&&player201.rng==rng);if(hit<4)assert(m->pendingSkill==378&&m->remainingHits204==4-hit);else assert(!m->pendingSkill);}
 unsigned char b[640];PartyGrowth200 saved;assert(party_progress_load200(&record201,b)==1);party_growth_read200(b+16+15*32,&saved);assert(saved.sp==m->sp&&saved.hp==m->hp&&saved.exp==1234&&saved.job==42&&saved.jobLevel==70);
 for(unsigned reason=0;reason<7;reason++){
  m=prepare219();int hp=player201.mobs[0].hp;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==378&&m->sp==100);
  if(reason==0)player201.mobs[0].life++;if(reason==1)player201.mobs[0].x=197;if(reason==2)player201.mobs[0].hp=0;if(reason==3)failGrowth200=1;
  if(reason==4){const NpcVariable55*v=npc_state_get55(&record201,PARTY_PROGRESS_KEY200,0);v->text[1279]=v->text[1279]=='0'?'1':'0';}
  if(reason==5){m->sp=0;assert(party_vital_store200(&record201,15,m->level,m->hp,0));}if(reason==6)player201.canAim=deny219;
  unsigned revision=record201.revision,beforeRng=player201.rng;unsigned char before[640],after[640];assert(party_read_hex200(&record201,PARTY_PROGRESS_KEY200,0,before,640)==1);player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);failGrowth200=0;
  assert(!m->pendingSkill&&!m->impactPaid209&&m->sp==(reason==5?0:100)&&player201.sp==77&&player201.zeny==54321&&record201.revision==revision&&player201.rng==beforeRng&&player201.mobs[0].hp==(reason==2?0:hp));assert(party_read_hex200(&record201,PARTY_PROGRESS_KEY200,0,after,640)==1&&!memcmp(before,after,640));
 }
 m=prepare219();campaign_battle_tick200(&player201,.01f,0);player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==378&&m->sp==100-cost);player201.mobs[0].life++;int hp=player201.mobs[0].hp;unsigned beforeRng=player201.rng;player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&m->sp==100-cost&&player201.rng==beforeRng&&player201.mobs[0].hp==hp);
 unsigned seed;for(seed=1;seed<=100;seed++){m=prepare219();campaignConfig200.priority[15]=PARTY_SUPPORT200;player201.rng=seed;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==1&&!m->pendingRank&&!campaignArrowNext212);if(m->remainingHits204==2)break;}assert(seed<=100);
 for(unsigned hit=0;hit<2;hit++){hp=player201.mobs[0].hp;player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(m->sp==100&&player201.mobs[0].hp<hp);}
 m=prepare219();campaignConfig200.skills[15]=0;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==1&&m->remainingHits204==1);
 m=prepare219();m->sp=0;assert(party_vital_store200(&record201,15,m->level,m->hp,0));campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==1&&m->sp==0);
 m=prepare219();campaign_battle_tick200(&player201,.01f,1);assert(!m->pendingSkill&&m->sp==100);
 npc_state_clear55(&record201);puts("PASS actual Corin ranged kit: original five-hit Rapid Shower and Chain Action/basic, cached damage, one saved own-SP fee and denied/failed/interrupted series preservation. Host only.");
}
