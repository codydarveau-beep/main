#include "test_companion_fixture205.h"
#define main specialist_impact_fixture210
#include "test_companion_specialist209.c"
#undef main
static CampaignFollower200*prepare210(void){
 CampaignFollower200*m=special209(438,7,1);m->pendingSkill=0;m->nextAttack=m->skillAt=0;m->target=-1;m->esmaUntil209=0;m->regenAt=1000;
 campaignConfig200.skills[18]=1;campaignConfig200.priority[18]=PARTY_BALANCED200;campaignConfig200.mode[18]=PARTY_ASSIST200;
 player201.mobs[0].x=164;return m;
}
int main(void){
 CampaignFollower200*m=prepare210();unsigned sp=m->sp;int hp=player201.mobs[0].hp;
 campaign_battle_tick200(&player201,.01f,0);unsigned primer=m->pendingSkill,rank=m->pendingRank;assert((primer==438||primer==439)&&m->castUntil>player201.time&&m->sp==sp&&m->remainingHits204==1&&!m->impactPaid209);
 unsigned cost=party_caster_cost194(m,primer,rank);player201.time=m->castUntil+.001f;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&m->sp==sp-cost&&m->esmaUntil209>player201.time&&player201.mobs[0].hp<hp&&player201.sp==77);
 player201.time=m->nextAttack+.001f;sp=m->sp;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==440&&m->remainingHits204==party_skill_rank193(m,440)&&!m->impactPaid209&&m->sp==sp);
 unsigned hits=m->remainingHits204;cost=party_caster_cost194(m,440,m->pendingRank);hp=player201.mobs[0].hp;
 for(unsigned k=0;k<hits;k++){player201.time=m->impactAt+.0001f;campaign_battle_tick200(&player201,.01f,0);assert(m->sp==sp-cost&&m->esmaUntil209==0&&player201.sp==77);if(k+1<hits)assert(m->pendingSkill==440&&m->remainingHits204==hits-k-1);}
 assert(!m->pendingSkill&&player201.mobs[0].hp<hp);
 m=prepare210();m->esmaUntil209=player201.time+3;sp=m->sp;campaign_battle_tick200(&player201,.01f,0);assert(m->pendingSkill==440&&m->castUntil>player201.time);float primed=m->esmaUntil209;assert(party_hurt200(&player201,m,1));assert(!m->pendingSkill&&m->sp==sp&&m->esmaUntil209==primed);
 m=prepare210();campaignConfig200.skills[18]=0;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill);
 m=prepare210();player201.peaceful=1;campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill);
 m=prepare210();m->sp=0;assert(party_vital_store200(&record201,18,m->level,m->hp,0));campaign_battle_tick200(&player201,.01f,0);assert(!m->pendingSkill&&m->sp==0);
 npc_state_clear55(&record201);puts("PASS actual Soul Linker candidate choice/cast/impact series and interruption; world roster activation and target playtests remain separate. HOST ONLY.");
}
