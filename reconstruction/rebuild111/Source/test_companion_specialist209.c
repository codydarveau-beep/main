/* Production impact integration; choices and full roster activation stay guarded. */
#include "test_companion_fixture205.h"
static CampaignFollower200*special209(unsigned skill,unsigned rank,unsigned hits){
 CampaignFollower200*m=prepare201(50);enemy201();m->id=skill<438?14:18;m->job=skill<438?42:43;m->jobLevel=50;m->level=90;m->hp=100;m->sp=500;m->stats[3]=100;
 unsigned char b[640];assert(party_progress_load200(&record201,b)==1);PartyGrowth200 p={90,1234,50,0,m->job,100,500};assert(party_progress_put200(b,m->id,&p)&&party_progress_commit200(&record201,b));
 m->pendingSkill=m->lastSkill=skill;m->pendingRank=rank;m->remainingHits204=hits;m->impactPaid209=0;m->pendingTarget=0;m->pendingLife=123;m->impactAt=player201.time;
 return m;
}
int main(void){
 CampaignFollower200*m=special209(440,3,3);unsigned sp=m->sp;int hp=player201.mobs[0].hp;party_resolve200(&player201,m);assert(!m->pendingSkill&&m->sp==sp&&player201.mobs[0].hp==hp);
 m=special209(438,7,1);sp=m->sp;unsigned cost=party_caster_cost194(m,438,7);hp=player201.mobs[0].hp;party_resolve200(&player201,m);assert(!m->pendingSkill&&m->impactPaid209&&m->sp==sp-cost&&player201.mobs[0].hp<hp&&m->esmaUntil209>player201.time);
 m->pendingSkill=m->lastSkill=440;m->pendingRank=m->remainingHits204=3;m->impactPaid209=0;m->impactAt=player201.time;sp=m->sp;cost=party_caster_cost194(m,440,3);hp=player201.mobs[0].hp;
 for(unsigned hit=0;hit<3;hit++){player201.time=m->impactAt;party_resolve200(&player201,m);assert(m->sp==sp-cost&&m->esmaUntil209==0&&m->impactPaid209&&player201.sp==77);if(hit<2)assert(m->pendingSkill==440&&m->remainingHits204==2-hit&&m->attackUntil>=m->impactAt+.05f);}
 assert(!m->pendingSkill&&player201.mobs[0].hp<hp);
 unsigned char b[640];PartyGrowth200 persisted;assert(party_progress_load200(&record201,b)==1);party_growth_read200(b+16+m->id*32,&persisted);assert(persisted.sp==m->sp&&persisted.exp==1234&&persisted.job==43);
 m=special209(439,7,1);sp=m->sp;hp=player201.mobs[0].hp;unsigned revision=record201.revision;failGrowth200=1;party_resolve200(&player201,m);failGrowth200=0;assert(!m->pendingSkill&&!m->impactPaid209&&m->esmaUntil209==0&&m->sp==sp&&player201.mobs[0].hp==hp&&record201.revision==revision);
 m=special209(440,3,3);m->esmaUntil209=player201.time+1;player201.mobs[0].life++;sp=m->sp;party_resolve200(&player201,m);assert(!m->pendingSkill&&m->sp==sp&&!m->impactPaid209&&m->esmaUntil209>player201.time);
 for(unsigned i=0;i<3;i++){unsigned skill=(unsigned[]){352,355,358}[i];m=special209(skill,3,3);sp=m->sp;cost=party_caster_cost194(m,skill,3);hp=player201.mobs[0].hp;for(unsigned hit=0;hit<3;hit++){player201.time=m->impactAt;party_resolve200(&player201,m);assert(m->sp==sp-cost&&player201.sp==77);}assert(!m->pendingSkill&&player201.mobs[0].hp<hp);}
 npc_state_clear55(&record201);puts("PASS actual specialist impact series, priming, durable one-time payment and failed/stale preservation. Choices and target playtests remain separate; HOST ONLY.");
}
