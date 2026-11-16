/* Suri's original learned Trifecta proc and same-target Quadruple follow-up. */
#ifndef MYRO_COMPANION_MONK220_H
#define MYRO_COMPANION_MONK220_H
static unsigned party_monk_choice220(const CampaignFollower200*m,const CombatMob*e,float now,unsigned*rank){
 *rank=0;if(!campaignConfig200.skills[m->id]||campaignConfig200.priority[m->id]==PARTY_SUPPORT200||now<m->skillAt||now>=m->comboUntil220||m->auxSkill220!=202||m->pendingTarget!=m->target||m->pendingLife!=e->life)return 1;
 *rank=party_skill_rank193(m,211);if(!*rank||m->sp<party_skill_cost200(211,*rank)){*rank=0;return 1;}return 211;
}
static void party_monk_tick220(Combat*g,CampaignFollower200*m,float dt,unsigned slot){
 if(g->peaceful)return;
 if(!party_target_ok200(g,m->target)||g->mobs[m->target].life!=m->targetLife||g->time>=m->thinkAt){m->target=party_choose_target200(g,m);m->targetLife=m->target>=0?g->mobs[m->target].life:0;m->thinkAt=g->time+.15f;}
 if(m->target<0)return;CombatMob*e=g->mobs+m->target;m->ownsMove=1;combat_face(&m->faceX,&m->faceY,e->x-m->x,e->y-m->y);
 if(combat_dist(m->x,m->y,e->x,e->y)>16){party_walk_to200(g,m,e->x,e->y,16,dt,slot,m->target);return;}
 m->moving=0;if(g->time<m->nextAttack||!party_line200(g,m->x,m->y,e->x,e->y))return;
 unsigned rank,skill=party_monk_choice220(m,e,g->time,&rank),hits=skill==211?4:1;
 if(skill==1&&campaignConfig200.skills[m->id]){unsigned learned=party_skill_rank193(m,202);if(learned&&combat_random(g)%100<30-learned){skill=202;rank=learned;hits=3;}}
 party_career_physical_begin217(g,m,e,skill,rank);m->remainingHits204=hits;m->impactDamage218=m->splitRemainder220=0;
}
#endif
