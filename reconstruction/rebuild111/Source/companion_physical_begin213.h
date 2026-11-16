/* Shared original physical attack initialization; no player equipment/resources. */
#ifndef MYRO_COMPANION_PHYSICAL_BEGIN213_H
#define MYRO_COMPANION_PHYSICAL_BEGIN213_H
static int party_physical_begin213(Combat*g,CampaignFollower200*m,CombatMob*e,unsigned skill,unsigned rank){
 float distance=combat_dist(m->x,m->y,e->x,e->y);
 unsigned cost=skill==1?0:rank?party_skill_cost200(skill,rank):0;
 if(m->sp<cost)return 0;
 if(!party_save_vital200(m,m->hp,m->sp-cost))return 0;
 int item=inventory_catalog52(partyWeapons202[m->id]),weapon=item>=0?itemDefs[item].wtype:0;
 if(weapon<0||weapon>22)weapon=0;
 int motion=m->job>=21?jobMotion52[m->job][weapon]:m->job>=12?classMotion50[m->job-12][weapon]:baseMotion48[m->job][weapon>12?0:weapon];
 motion-=motion*(4*party_stat200(m,1,g->time)+party_stat200(m,4,g->time))/1000;if(motion<30)motion=30;
 float period=motion*.002f,duration=fminf(.75f,period),launch=g->time+duration*.6f,arrival=launch+distance/360.f;
 m->attackAt=g->time;m->attackUntil=g->time+duration;m->nextAttack=g->time+period;m->pendingSkill=m->lastSkill=skill;m->pendingRank=rank;m->remainingHits204=skill==17&&rank?2:1;m->pendingTarget=m->target;m->pendingLife=e->life;m->castUntil=0;m->impactAt=launch;
 if(m->id==COMP200_JUDIA){
  m->impactAt=arrival;
  campaignArrows212[campaignArrowNext212++%8]=(CampaignArrow212){g->mapId,m->x,m->y,e->x,e->y,launch,arrival};
  if(rank){campaignArrows212[campaignArrowNext212++%8]=(CampaignArrow212){g->mapId,m->x,m->y,e->x,e->y,launch+.1f,arrival+.1f};arrival+=.1f;}
  m->attackUntil=fmaxf(m->attackUntil,arrival);m->nextAttack=fmaxf(m->nextAttack,m->attackUntil);
 }
 if(skill==2||(skill==17&&rank))party_native_effect212(g,m,16);
 if(skill!=1&&(m->id!=COMP200_JUDIA||rank))m->skillAt=g->time+(campaignConfig200.priority[m->id]==PARTY_OFFENSE200?1.f:3.f);
 return 1;
}
#endif
