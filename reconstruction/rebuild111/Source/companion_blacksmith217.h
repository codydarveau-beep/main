/* Dagna's original Hammer Fall priority and deferred-payment physical branch. */
#ifndef MYRO_COMPANION_BLACKSMITH217_H
#define MYRO_COMPANION_BLACKSMITH217_H
static unsigned party_blacksmith_choice217(const CampaignFollower200*m,const CombatMob*enemy,float now,unsigned*rank){
 *rank=0;if(!campaignConfig200.skills[m->id]||campaignConfig200.priority[m->id]==PARTY_SUPPORT200||now<m->skillAt||combat_status_boss(enemy)||enemy->stun>0)return 1;
 *rank=party_skill_rank193(m,230);if(!*rank||m->sp<party_skill_cost200(230,*rank)){*rank=0;return 1;}return 230;
}
static void party_blacksmith_tick217(Combat*g,CampaignFollower200*m,float dt,unsigned slot){
 if(g->peaceful)return;
 if(!party_target_ok200(g,m->target)||g->mobs[m->target].life!=m->targetLife||g->time>=m->thinkAt){m->target=party_choose_target200(g,m);m->targetLife=m->target>=0?g->mobs[m->target].life:0;m->thinkAt=g->time+.15f;}
 if(m->target<0)return;CombatMob*e=g->mobs+m->target;unsigned rank,skill=party_blacksmith_choice217(m,e,g->time,&rank);float reach=skill==230?64:16;m->ownsMove=1;combat_face(&m->faceX,&m->faceY,e->x-m->x,e->y-m->y);
 if(combat_dist(m->x,m->y,e->x,e->y)>reach){party_walk_to200(g,m,e->x,e->y,reach,dt,slot,m->target);return;}
 m->moving=0;if(g->time<m->nextAttack||!party_line200(g,m->x,m->y,e->x,e->y))return;party_career_physical_begin217(g,m,e,skill,rank);
}
static void party_blacksmith_step217(Combat*g,CampaignFollower200*m,PartyBoltHit204 hit,PartyBoltCue204 cue){
 unsigned skill=m->pendingSkill;if((skill!=1&&skill!=230)||g->time<m->impactAt)return;
 if(skill==1){if(party_target_ok200(g,m->pendingTarget)&&combat_dist(m->x,m->y,g->mobs[m->pendingTarget].x,g->mobs[m->pendingTarget].y)>24){m->pendingSkill=0;return;}party_performer_step216(g,m,hit,cue);return;}
 m->pendingSkill=0;int target=m->pendingTarget;if(!party_target_ok200(g,target)||g->mobs[target].life!=m->pendingLife)return;CombatMob*e=g->mobs+target;
 if(combat_dist(m->x,m->y,e->x,e->y)>80||!party_line200(g,m->x,m->y,e->x,e->y))return;
 unsigned cost=party_caster_cost194(m,230,m->pendingRank);if(m->sp<cost||!party_save_vital200(m,m->hp,m->sp-cost))return;m->impactPaid209=1;
 for(unsigned i=0;i<MOB_COUNT;i++){CombatMob*other=g->mobs+i;if(party_target_ok200(g,(int)i)&&combat_dist(e->x,e->y,other->x,other->y)<=20&&party_line200(g,e->x,e->y,other->x,other->y))class_stun50(g,other,20+10*(int)m->pendingRank,class_duration50(230,(int)m->pendingRank,1));}
 cue(g,230,e->x,e->y);
}
#endif
