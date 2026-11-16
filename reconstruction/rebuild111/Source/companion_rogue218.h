/* Kest's original rear-attack/Envenom/basic decisions and Double Attack.
 * Repeated physical hits reuse the original fully reduced damage and one fee. */
#ifndef MYRO_COMPANION_ROGUE218_H
#define MYRO_COMPANION_ROGUE218_H
static unsigned party_rogue_choice218(const CampaignFollower200*m,const CombatMob*e,float now,unsigned*rank){
 *rank=0;if(!campaignConfig200.skills[m->id]||campaignConfig200.priority[m->id]==PARTY_SUPPORT200||now<m->skillAt)return 1;
 unsigned skill=13;
 if((m->x-e->x)*e->faceX+(m->y-e->y)*e->faceY<0&&party_skill_rank193(m,142))skill=142;
 *rank=party_skill_rank193(m,skill);if(!*rank||m->sp<party_skill_cost200(skill,*rank)){*rank=0;return 1;}return skill;
}
static void party_rogue_tick218(Combat*g,CampaignFollower200*m,float dt,unsigned slot){
 if(g->peaceful)return;
 if(!party_target_ok200(g,m->target)||g->mobs[m->target].life!=m->targetLife||g->time>=m->thinkAt){m->target=party_choose_target200(g,m);m->targetLife=m->target>=0?g->mobs[m->target].life:0;m->thinkAt=g->time+.15f;}
 if(m->target<0)return;CombatMob*e=g->mobs+m->target;unsigned rank,skill=party_rogue_choice218(m,e,g->time,&rank);m->ownsMove=1;combat_face(&m->faceX,&m->faceY,e->x-m->x,e->y-m->y);
 if(combat_dist(m->x,m->y,e->x,e->y)>16){party_walk_to200(g,m,e->x,e->y,16,dt,slot,m->target);return;}
 m->moving=0;if(g->time<m->nextAttack||!party_line200(g,m->x,m->y,e->x,e->y))return;
 unsigned hits=1;if(skill==1&&campaignConfig200.skills[m->id]){unsigned learned=party_skill_rank193(m,12);if(learned)hits+=(combat_random(g)%100<5*learned);}
 party_career_physical_begin217(g,m,e,skill,rank);m->remainingHits204=hits;m->impactDamage218=0;
}
#include "companion_cached_physical219.h"
#endif
