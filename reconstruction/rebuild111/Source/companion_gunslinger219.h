/* Corin's original ranged basic/Chain Action/Rapid Shower kit. */
#ifndef MYRO_COMPANION_GUNSLINGER219_H
#define MYRO_COMPANION_GUNSLINGER219_H
static unsigned party_gunner_choice219(const CampaignFollower200*m,float now,unsigned*rank){
 *rank=0;if(!campaignConfig200.skills[m->id]||campaignConfig200.priority[m->id]==PARTY_SUPPORT200||now<m->skillAt)return 1;
 *rank=party_skill_rank193(m,378);if(!*rank||m->sp<party_skill_cost200(378,*rank)){*rank=0;return 1;}return 378;
}
static void party_gunner_tick219(Combat*g,CampaignFollower200*m,float dt,unsigned slot){
 if(g->peaceful)return;
 if(!party_target_ok200(g,m->target)||g->mobs[m->target].life!=m->targetLife||g->time>=m->thinkAt){m->target=party_choose_target200(g,m);m->targetLife=m->target>=0?g->mobs[m->target].life:0;m->thinkAt=g->time+.15f;}
 if(m->target<0)return;CombatMob*e=g->mobs+m->target;m->ownsMove=1;combat_face(&m->faceX,&m->faceY,e->x-m->x,e->y-m->y);
 if(combat_dist(m->x,m->y,e->x,e->y)>72){party_walk_to200(g,m,e->x,e->y,72,dt,slot,m->target);return;}
 m->moving=0;if(g->time<m->nextAttack||!party_line200(g,m->x,m->y,e->x,e->y))return;
 unsigned rank,skill=party_gunner_choice219(m,g->time,&rank),hits=skill==378?5:1;
 if(skill==1&&campaignConfig200.skills[m->id]){unsigned learned=party_skill_rank193(m,374);if(learned)hits+=(combat_random(g)%100<5*learned);}
 party_career_physical_begin217(g,m,e,skill,rank);m->remainingHits204=hits;m->impactDamage218=0;
}
#endif
