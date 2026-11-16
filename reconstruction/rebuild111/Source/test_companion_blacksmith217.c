#include "test_companion_fixture205.h"
#define main melee_fixture217
#include "test_companion_melee213.c"
#undef main
static CampaignFollower200*prepare217(unsigned job){CampaignFollower200*m=prepare213(11,job,job==19?50:70);player201.zeny=54321;return m;}
static int denied217(void*p,float x,float y,float a,float b){(void)p;(void)x;(void)y;(void)a;(void)b;return 0;}
int main(void){
 for(unsigned job=19;job<=31;job+=12){
  CampaignFollower200*m=prepare217(job);unsigned rank=party_skill_rank193(m,230),cost=party_caster_cost194(m,230,rank),sp=m->sp;assert(rank);
  for(unsigned i=1;i<3;i++){player201.mobs[i]=player201.mobs[0];player201.mobs[i].life=123+i;player201.mobs[i].x=i==1?128:133;}
  int hp=player201.mobs[0].hp;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==230&&m->pendingRank==rank&&!m->impactPaid209&&m->sp==sp&&!campaignArrowNext212&&!campaignNativeFxNext212);
  player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&m->impactPaid209&&m->sp==sp-cost&&player201.sp==77&&player201.zeny==54321&&player201.mobs[0].hp==hp&&player201.mobs[0].stun>0&&player201.mobs[2].stun==0);
  unsigned char b[640];PartyGrowth200 p;assert(party_progress_load200(&record201,b)==1);party_growth_read200(b+16+11*32,&p);assert(p.sp==m->sp&&p.hp==m->hp&&p.exp==1234&&p.job==job);
  for(unsigned reason=0;reason<7;reason++){
   m=prepare217(job);hp=player201.mobs[0].hp;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==230&&m->sp==100);
   if(reason==0)player201.mobs[0].life++;
   if(reason==1)player201.mobs[0].x=181;
   if(reason==2)player201.mobs[0].hp=0;
   if(reason==3)failGrowth200=1;
   if(reason==4){const NpcVariable55*v=npc_state_get55(&record201,PARTY_PROGRESS_KEY200,0);v->text[1279]=v->text[1279]=='0'?'1':'0';}
   if(reason==5){m->sp=0;assert(party_vital_store200(&record201,11,m->level,m->hp,0));}
   if(reason==6)player201.canAim=denied217;
   unsigned revision=record201.revision;unsigned char before[640],after[640];assert(party_read_hex200(&record201,PARTY_PROGRESS_KEY200,0,before,640)==1);player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);failGrowth200=0;
   assert(!m->pendingSkill&&!m->impactPaid209&&m->sp==(reason==5?0:100)&&player201.sp==77&&player201.zeny==54321&&record201.revision==revision&&player201.mobs[0].hp==(reason==2?0:hp)&&player201.mobs[0].stun==0);assert(party_read_hex200(&record201,PARTY_PROGRESS_KEY200,0,after,640)==1&&!memcmp(before,after,640));
  }
  for(unsigned reason=0;reason<6;reason++){
   m=prepare217(job);if(reason==0)campaignConfig200.skills[11]=0;if(reason==1)campaignConfig200.priority[11]=PARTY_SUPPORT200;if(reason==2)m->skillAt=11;if(reason==3){m->sp=0;assert(party_vital_store200(&record201,11,m->level,m->hp,0));}if(reason==4)player201.mobs[0].stun=2;
   if(reason==5){unsigned kind=0;while(kind<MOB_SPEC_COUNT&&(!mobUtility[kind].blocked||combat_racer_kind164(kind)))kind++;assert(kind<MOB_SPEC_COUNT);player201.mobs[0].kind=(int)kind;}
   sp=m->sp;hp=player201.mobs[0].hp;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==1&&!m->pendingRank&&m->sp==sp&&!campaignArrowNext212);player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&m->sp==sp&&player201.mobs[0].hp<hp);
  }
  m=prepare217(job);player201.mobs[0].x=164;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==230&&m->sp==100&&m->x==100);
  m=prepare217(job);player201.mobs[0].x=165;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&m->sp==100&&m->x>100);
  m=prepare217(job);player201.mobs[0].training=1;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&m->sp==100);
 }
 npc_state_clear55(&record201);puts("PASS actual Dagna careers: original area stun, saved deferred payment, real basic fallback and failed-impact preservation. Host only.");
}
