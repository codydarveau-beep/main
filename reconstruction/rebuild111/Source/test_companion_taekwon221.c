#include "test_companion_fixture205.h"
#define main melee_fixture221
#include "test_companion_melee213.c"
#undef main
static CampaignFollower200*prepare221(unsigned id){CampaignFollower200*m=prepare213(id,id==16?43:44,50);m->stats[0]=50;m->stats[4]=100;campaignConfig200.skills[id]=1;campaignConfig200.priority[id]=PARTY_BALANCED200;player201.zeny=54321;return m;}
static CampaignFollower200*armed221(unsigned id){for(unsigned seed=1;seed<=200;seed++){CampaignFollower200*m=prepare221(id);player201.rng=seed;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==1);player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);if(m->auxSkill220){assert(m->auxSkill220==(id==16?386:390)&&m->comboUntil220>player201.time&&m->pendingLife==123);return m;}}assert(0);return NULL;}
static void cluster221(void){for(unsigned i=1;i<3;i++){player201.mobs[i]=player201.mobs[0];player201.mobs[i].life=123+i;player201.mobs[i].x=i==1?116:121;player201.mobs[i].y=i==1?108:100;player201.mobs[i].hp=100000;}}
static int deny221(void*p,float x,float y,float a,float b){(void)p;(void)x;(void)y;(void)a;(void)b;return 0;}
int main(void){
 for(unsigned id=16;id<=17;id++){
  CampaignFollower200*m=armed221(id);unsigned skill=id==16?386:390,sp=m->sp;player201.time=fmaxf(m->nextAttack,m->attackUntil)+.0001f;assert(player201.time<m->comboUntil220);cluster221();campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==skill&&m->remainingHits204==1&&m->comboUntil220==0&&!m->impactPaid209&&m->sp==sp&&!campaignArrowNext212);
  unsigned cost=party_caster_cost194(m,skill,m->pendingRank);int hp=player201.mobs[0].hp;player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&m->impactPaid209&&m->sp==sp-cost&&player201.mobs[0].hp<hp&&player201.mobs[1].hp<100000&&player201.sp==77&&player201.zeny==54321&&player201.mobs[0].x==112);
  if(id==16)assert(player201.mobs[2].hp==100000&&player201.mobs[1].x==116&&player201.mobs[1].y==108);else assert(player201.mobs[2].hp<100000&&combat_dist(116,108,player201.mobs[1].x,player201.mobs[1].y)>0&&combat_dist(121,100,player201.mobs[2].x,player201.mobs[2].y)>0);
  unsigned char b[640];PartyGrowth200 saved;assert(party_progress_load200(&record201,b)==1);party_growth_read200(b+16+id*32,&saved);assert(saved.sp==m->sp&&saved.hp==m->hp&&saved.exp==1234&&saved.job==(id==16?43:44));
  for(unsigned reason=0;reason<7;reason++){
   m=prepare221(id);m->auxSkill220=skill;m->comboUntil220=11;m->pendingTarget=0;m->pendingLife=123;cluster221();campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==skill&&m->sp==100);int oldHP=player201.mobs[0].hp;
   if(reason==0)player201.mobs[0].life++;if(reason==1)player201.mobs[0].x=125;if(reason==2)player201.mobs[0].hp=0;if(reason==3)failGrowth200=1;
   if(reason==4){const NpcVariable55*v=npc_state_get55(&record201,PARTY_PROGRESS_KEY200,0);v->text[1279]=v->text[1279]=='0'?'1':'0';}if(reason==5){m->sp=0;assert(party_vital_store200(&record201,id,m->level,m->hp,0));}if(reason==6)player201.canAim=deny221;
   unsigned revision=record201.revision,rng=player201.rng;unsigned char before[640],after[640];assert(party_read_hex200(&record201,PARTY_PROGRESS_KEY200,0,before,640)==1);player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);failGrowth200=0;
   assert(!m->pendingSkill&&!m->impactPaid209&&m->sp==(reason==5?0:100)&&player201.sp==77&&player201.zeny==54321&&record201.revision==revision&&player201.rng==rng&&player201.mobs[0].hp==(reason==2?0:oldHP)&&player201.mobs[1].hp==100000&&player201.mobs[2].hp==100000&&player201.mobs[1].x==116&&player201.mobs[2].x==121);assert(party_read_hex200(&record201,PARTY_PROGRESS_KEY200,0,after,640)==1&&!memcmp(before,after,640));
  }
  m=prepare221(id);m->auxSkill220=skill;m->comboUntil220=11;m->pendingTarget=0;m->pendingLife=123;cluster221();campaign_battle_tick200(&player201,.01f,0);player201.mobs[0].hp=1;player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(player201.mobs[0].hp==0&&player201.mobs[1].hp<100000);
  m=prepare221(id);campaignConfig200.skills[id]=0;for(unsigned turn=0;turn<10;turn++){player201.time=fmaxf(m->nextAttack,m->attackUntil)+.001f;campaign_battle_tick200(&player201,.01f,0);player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(!m->auxSkill220&&!m->comboUntil220&&m->sp==100);}
 }
 npc_state_clear55(&record201);puts("PASS actual Daro/Haneul native stance-to-kick sequences, real area damage/knockback, original boundaries, saved own-SP fees and denied/failed-impact preservation. Host only.");
}
