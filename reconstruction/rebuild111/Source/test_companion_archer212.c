#include "test_companion_fixture205.h"
#include "npc_effect_data172.h"
#include "npc_effect_audio_data172.h"
#include "npc_cylinder_geometry180.h"
#include "npc_particle_pose180.h"
static unsigned nativeDraws212,ringPoses212,roomHidden212;
static int interiorRooms181;
static int rooms_point181(const int*r,float x,float y){(void)r;(void)x;(void)y;return !roomHidden212;}
static float height_at(float x,float y){(void)x;(void)y;return 7;}
static unsigned npc_special_lifetime180(unsigned id){(void)id;return 0;}
static unsigned npc_legacy_lifetime181(unsigned id){(void)id;return 0;}
static void npc_cylinder_draw180(unsigned id,unsigned age,unsigned seed,const float*m,float x,float y){(void)seed;(void)m;assert(id==16&&isfinite(x)&&isfinite(y));nativeDraws212++;for(unsigned i=0;i<sizeof(npcCylinders180)/sizeof(*npcCylinders180);i++)if(npcCylinders180[i].id==id){NpcCylinderPose180 pose;unsigned end=npcCylinders180[i].delay;if(age>=end&&npc_cylinder_pose180(npcCylinders180+i,age-end,&pose)){assert(isfinite(pose.alpha)&&isfinite(pose.height));ringPoses212++;}}}
static void npc_particle_draw180(unsigned id,unsigned age,unsigned created,unsigned seed,const float*m,float x,float y,float a,float b,float c){(void)id;(void)age;(void)created;(void)seed;(void)m;(void)x;(void)y;(void)a;(void)b;(void)c;}
static void npc_special_draw180(unsigned id,unsigned age,unsigned seed,const float*m,float x,float y){(void)id;(void)age;(void)seed;(void)m;(void)x;(void)y;}
static void npc_legacy_draw181(const Combat*g,unsigned id,unsigned age,unsigned seed,const float*m,float x,float y){(void)g;(void)id;(void)age;(void)seed;(void)m;(void)x;(void)y;}
static void npc_fx_one172(const NpcFxClip172*c,unsigned age,const float*m,float x,float y,float zoom){(void)c;(void)age;(void)m;(void)x;(void)y;(void)zoom;assert(0);}
#include "campaign_native_fx212.h"
static CampaignFollower200*prepare212(unsigned job,unsigned jl){
 CampaignFollower200*m=mage204();m->id=COMP200_JUDIA;m->job=job;m->jobLevel=jl;m->level=90;m->hp=100;m->sp=500;m->stats[1]=40;m->stats[3]=100;m->stats[4]=90;m->life=1234;m->pendingSkill=0;m->nextAttack=m->skillAt=0;m->target=-1;
 unsigned char b[640];assert(party_progress_load200(&record201,b)==1);PartyGrowth200 p={90,1234,jl,0,job,100,500};assert(party_progress_put200(b,COMP200_JUDIA,&p)&&party_progress_commit200(&record201,b));
 campaignConfig200.skills[COMP200_JUDIA]=1;campaignConfig200.priority[COMP200_JUDIA]=PARTY_BALANCED200;campaignConfig200.mode[COMP200_JUDIA]=PARTY_ASSIST200;memset(campaignArrows212,0,sizeof campaignArrows212);campaignArrowNext212=0;memset(campaignNativeFx212,0,sizeof campaignNativeFx212);campaignNativeFxNext212=0;partyNativeSound212=campaign_native_sound212;return m;
}
int main(void){
 for(unsigned row=0;row<2;row++){
  CampaignFollower200*m=prepare212(row?28:14,row?70:50);unsigned sp=m->sp,rank=party_skill_rank193(m,17),cost=party_skill_cost200(17,rank);int hp=player201.mobs[0].hp;assert(rank);
  campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==17&&m->pendingRank==rank&&m->remainingHits204==2&&m->sp==sp-cost&&campaignArrowNext212==2&&player201.mobs[0].hp==hp);
  assert(campaignNativeFxNext212==1&&campaignNativeFx212[0].id==16&&campaignNativeFx212[0].life==m->life);assert(player201.soundWrite&&player201.soundEvents[(player201.soundWrite-1)%32]==SOUND_NPC_FIRST64+34);
  assert(campaignArrows212[0].start>player201.time&&campaignArrows212[0].end==m->impactAt&&campaignArrows212[1].start>campaignArrows212[0].start);
  player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==17&&m->remainingHits204==1&&m->sp==sp-cost&&player201.mobs[0].hp<hp);hp=player201.mobs[0].hp;
  player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&m->sp==sp-cost&&player201.mobs[0].hp<hp&&player201.sp==77);
  unsigned char b[640];PartyGrowth200 saved;assert(party_progress_load200(&record201,b)==1);party_growth_read200(b+16+COMP200_JUDIA*32,&saved);assert(saved.sp==m->sp&&saved.exp==1234&&saved.job==m->job);
  m=prepare212(row?28:14,row?70:50);campaignConfig200.priority[COMP200_JUDIA]=PARTY_SUPPORT200;sp=m->sp;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==17&&m->pendingRank==0&&m->remainingHits204==1&&m->sp==sp&&campaignArrowNext212==1&&!campaignNativeFxNext212);
  m=prepare212(row?28:14,row?70:50);unsigned revision=record201.revision;sp=m->sp;failGrowth200=1;campaign_battle_tick200(&player201,.01f,0);failGrowth200=0;assert(!m->pendingSkill&&m->sp==sp&&record201.revision==revision&&!campaignArrowNext212&&!campaignNativeFxNext212);
 }
 CampaignFollower200*m=prepare212(28,70);party_native_effect212(&player201,m,16);nativeDraws212=ringPoses212=0;player201.time+=.2f;float matrix[16]={0};unsigned revision=record201.revision;campaign_native_fx_draw212(&player201,matrix,2);assert(nativeDraws212==1&&ringPoses212==3&&record201.revision==revision&&campaignNativeFx212[0].positioned);
 roomHidden212=1;campaign_native_fx_draw212(&player201,matrix,2);assert(nativeDraws212==1);roomHidden212=0;m->life++;campaign_native_fx_draw212(&player201,matrix,2);assert(nativeDraws212==1);m->life--;campaignParty200.count=0;campaign_native_fx_draw212(&player201,matrix,2);assert(nativeDraws212==1);campaignParty200.count=1;player201.time+=1.1f;campaign_native_fx_draw212(&player201,matrix,2);assert(!campaignNativeFx212[0].id);
 npc_state_clear55(&record201);puts("PASS actual Judia careers: delayed arrows, complete real double hits, native fallback, durable one-time payment, failed save and owned native effect lifecycle. Host recording only, no Xbox/Xemu raster/playtest.");
}
