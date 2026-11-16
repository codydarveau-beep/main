/* Shared original default-career physical initiation; impact payment stays deferred. */
#ifndef MYRO_COMPANION_CAREER_BEGIN217_H
#define MYRO_COMPANION_CAREER_BEGIN217_H
static void party_career_physical_begin217(Combat*g,CampaignFollower200*m,CombatMob*e,unsigned skill,unsigned rank){
 int item=inventory_catalog52(partyWeapons202[m->id]),weapon=item>=0?itemDefs[item].wtype:0;if(weapon<0||weapon>22)weapon=0;
 int motion=jobMotion52[m->job][weapon];motion-=motion*(4*party_stat200(m,1,g->time)+party_stat200(m,4,g->time))/1000;if(motion<30)motion=30;
 float period=motion*.002f,duration=fmaxf(.1f,fminf(.75f,period)),launch=g->time+duration*.6f;
 m->pendingSkill=m->lastSkill=skill;m->pendingRank=rank;m->remainingHits204=1;m->impactPaid209=0;m->pendingTarget=m->target;m->pendingLife=e->life;m->attackAt=g->time;m->attackUntil=g->time+duration;m->castUntil=0;m->impactAt=launch;m->nextAttack=g->time+period;
 if(skill!=1){const ClassSkill50*d=class_skill_data50(skill);float delay=d?d->delay[rank-1]/1000.f:0;m->nextAttack=fmaxf(m->nextAttack,g->time+delay);m->skillAt=g->time+fmaxf(delay,campaignConfig200.priority[m->id]==PARTY_OFFENSE200?1.f:3.f);}
 if(m->id==9||m->id==10){m->impactAt+=combat_dist(m->x,m->y,e->x,e->y)/360.f;campaignArrows212[campaignArrowNext212++%8]=(CampaignArrow212){g->mapId,m->x,m->y,e->x,e->y,launch,m->impactAt};}
}
#endif
