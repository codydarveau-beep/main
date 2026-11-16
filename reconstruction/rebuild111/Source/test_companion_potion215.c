#include "test_companion_fixture205.h"
#define main melee_fixture215
#include "test_companion_melee213.c"
#undef main
static CampaignFollower200*prepare215(unsigned job,unsigned recipient){
 CampaignFollower200*m=prepare213(COMP200_MAYA,job,job==20?50:70);m->maxHP=100;m->stats[2]=40;player201.zeny=54321;player201.peaceful=1;
 owned_init52(&player201.owned52);assert(owned_add52(&player201.owned52,0,501,3,item_rule52)==OWNED_OK52);
 if(recipient==0)player201.hp=1;
 if(recipient==2){m->hp=1;assert(party_vital_store200(&record201,m->id,m->level,m->hp,m->sp));}
 if(recipient==1){CampaignFollower200*a=m+1;memset(a,0,sizeof(*a));a->id=COMP200_YUUFA;a->job=3;a->jobLevel=2;a->level=20;a->initialized=1;a->map=3;a->x=112;a->y=100;a->hp=1;a->maxHP=100;a->sp=10;a->life=4321;a->regenAt=1000;a->stats[2]=40;campaignParty200.count=2;unsigned char b[640];assert(party_progress_load200(&record201,b)==1);PartyGrowth200 friend={20,1234,2,0,3,1,10};assert(party_progress_put200(b,a->id,&friend)&&party_progress_commit200(&record201,b));}
 return m;
}
static PartyGrowth200 saved215(unsigned id){unsigned char b[640];PartyGrowth200 p;assert(party_progress_load200(&record201,b)==1);party_growth_read200(b+16+id*32,&p);return p;}
static int deny215(void*p,float x,float y,float a,float b){(void)p;(void)x;(void)y;(void)a;(void)b;return 0;}
int main(void){
 for(unsigned job=20;job<=32;job+=12){
  for(unsigned recipient=0;recipient<3;recipient++){
   CampaignFollower200*m=prepare215(job,recipient);unsigned sp=m->sp,cost=party_skill_cost200(242,1);assert(party_skill_rank193(m,242));
   unsigned missing=recipient?99:999,vitality=recipient?40:(unsigned)stat_value(&player201,2),heal=party_potion_amount215(party_skill_rank193(m,238),vitality,missing);
   campaign_battle_tick200(&player201,.01f,0);assert(m->lastSkill==242&&!m->pendingSkill&&m->sp==sp-cost&&player201.sp==77&&player201.zeny==54321&&inventory_count(&player201,inventory_catalog52(501))==2);
   assert((recipient==0?(unsigned)player201.hp:campaignParty200.members[recipient==1?1:0].hp)==1+heal);
   PartyGrowth200 p=saved215(m->id);assert(p.hp==m->hp&&p.sp==m->sp&&p.exp==1234&&p.job==job&&p.jobLevel==(job==20?50:70));
   if(recipient==1){p=saved215(COMP200_YUUFA);assert(p.hp==1+heal&&p.sp==10&&p.exp==1234&&p.job==3);}
   player201.time+=.1f;campaign_battle_tick200(&player201,.01f,0);assert(m->sp==sp-cost&&inventory_count(&player201,inventory_catalog52(501))==2);
  }
  for(unsigned reason=0;reason<9;reason++){
   CampaignFollower200*m=prepare215(job,0);
   if(reason==0)failGrowth200=1;
   if(reason==1){const NpcVariable55*v=npc_state_get55(&record201,PARTY_PROGRESS_KEY200,0);v->text[1279]=v->text[1279]=='0'?'1':'0';}
   if(reason==2)owned_init52(&player201.owned52);
   if(reason==3)campaignConfig200.skills[m->id]=0;
   if(reason==4){m->sp=0;assert(party_vital_store200(&record201,m->id,m->level,m->hp,0));}
   if(reason==5)player201.canAim=deny215;
   if(reason==6)m->skillAt=11;
   if(reason==7)player201.hp=player201.maxhp;
   if(reason==8){m->job=20;m->jobLevel=1;assert(!party_skill_rank193(m,242));}
   unsigned hp=player201.hp,sp=m->sp,revision=record201.revision;OwnedItems52 bag=player201.owned52;unsigned char before[640],after[640];assert(party_read_hex200(&record201,PARTY_PROGRESS_KEY200,0,before,640)==1);
   campaign_battle_tick200(&player201,.01f,0);failGrowth200=0;
   assert(player201.hp==(int)hp&&player201.sp==77&&player201.zeny==54321&&m->sp==sp&&m->hp==100&&!m->lastSkill&&record201.revision==revision&&!memcmp(&bag,&player201.owned52,sizeof bag));
   assert(party_read_hex200(&record201,PARTY_PROGRESS_KEY200,0,after,640)==1&&!memcmp(before,after,640));
  }
  CampaignFollower200*m=prepare215(job,0);m->x=180;unsigned sp=m->sp;campaign_battle_tick200(&player201,.01f,0);assert(m->ownsMove&&m->x<180&&player201.hp==1&&m->sp==sp&&inventory_count(&player201,inventory_catalog52(501))==3);
  m=prepare215(job,3);player201.peaceful=0;int hp=player201.mobs[0].hp;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==1&&m->pendingRank==1&&m->sp==100&&!campaignNativeFxNext212&&!campaignArrowNext212);player201.time=m->impactAt+.001f;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&player201.mobs[0].hp<hp&&m->sp==100&&inventory_count(&player201,inventory_catalog52(501))==3);
 }
 npc_state_clear55(&record201);puts("PASS Maya actual support and basic combat in both careers; durable player/ally/self recovery and failed-transaction resource preservation. Host only.");
}
