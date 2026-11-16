/* Original Miri priorities, including prepared follow-up and size preferences. */
#ifndef MYRO_COMPANION_SOULLINKER_TICK210_H
#define MYRO_COMPANION_SOULLINKER_TICK210_H
static unsigned party_soullinker_choice210(const CampaignFollower200*m,const CombatMob*enemy,float now,unsigned*rank){
 *rank=0;unsigned learned=party_skill_rank193(m,440);
 if(m->esmaUntil209>now&&learned&&m->sp>=party_caster_cost194(m,440,learned)){*rank=learned;return 440;}
 unsigned first=mobClassData50[enemy->kind][1]==0?438:439;
 for(unsigned i=0;i<2;i++){unsigned skill=i?(first==438?439:438):first;learned=party_skill_rank193(m,skill);if(learned&&m->sp>=party_caster_cost194(m,skill,learned)){*rank=learned;return skill;}}
 return 0;
}
#include "companion_targeted_begin211.h"
static void party_soullinker_tick210(Combat*g,CampaignFollower200*m,float dt,unsigned slot){
 if(g->peaceful||!campaignConfig200.skills[m->id])return;
 if(!party_target_ok200(g,m->target)||g->mobs[m->target].life!=m->targetLife||g->time>=m->thinkAt){m->target=party_choose_target200(g,m);m->targetLife=m->target>=0?g->mobs[m->target].life:0;m->thinkAt=g->time+.15f;}
 if(m->target<0)return;
 CombatMob*enemy=g->mobs+m->target;unsigned rank,skill=party_soullinker_choice210(m,enemy,g->time,&rank);
 if(!skill)return;
 party_targeted_tick211(g,m,dt,slot,skill,rank);
}
#endif
