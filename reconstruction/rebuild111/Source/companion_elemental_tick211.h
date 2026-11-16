/* Original Edda/Kaede targeted caster scoring, distinct from Takius priorities. */
#ifndef MYRO_COMPANION_ELEMENTAL_TICK211_H
#define MYRO_COMPANION_ELEMENTAL_TICK211_H
static unsigned party_elemental_choice211(const CampaignFollower200*m,const CombatMob*enemy,unsigned*rank){
 static const unsigned ordinary[3]={3,9,21},ninja[3]={352,355,358};
 const unsigned*skills=m->id==COMP200_KAEDE?ninja:ordinary;
 unsigned best=0,score=0;*rank=0;
 for(unsigned i=0;i<3;i++){
  unsigned skill=skills[i],learned=party_skill_rank193(m,skill);if(!learned)continue;
  unsigned cost=party_caster_cost194(m,skill,learned);if(cost>m->sp)continue;
  int rate=class_element_rate48(enemy,(int)party_impact_element204(skill,1));if(rate<=0)continue;
  const ClassSkill50*d=class_skill_data50(skill);unsigned hits=d?(unsigned)abs(d->hits[learned-1]):learned;if(!hits)hits=1;
  unsigned value=hits*(unsigned)rate*(skill==352?90:100);
  if(campaignConfig200.priority[m->id]==PARTY_SUPPORT200)value/=cost?cost:1;
  if(value>score){best=skill;score=value;*rank=learned;}
 }
 return best;
}
static void party_elemental_tick211(Combat*g,CampaignFollower200*m,float dt,unsigned slot){
 if(g->peaceful||!campaignConfig200.skills[m->id])return;
 if(!party_target_ok200(g,m->target)||g->mobs[m->target].life!=m->targetLife||g->time>=m->thinkAt){m->target=party_choose_target200(g,m);m->targetLife=m->target>=0?g->mobs[m->target].life:0;m->thinkAt=g->time+.15f;}
 if(m->target<0)return;
 unsigned rank,skill=party_elemental_choice211(m,g->mobs+m->target,&rank);if(skill)party_targeted_tick211(g,m,dt,slot,skill,rank);
}
#endif
