/* Original Brann and Iruga physical choices, distinct from later specialist kits. */
#ifndef MYRO_COMPANION_MELEE_TICK213_H
#define MYRO_COMPANION_MELEE_TICK213_H
static unsigned party_melee_choice213(const CampaignFollower200*m,float now,unsigned*rank){
 unsigned skill=m->id==COMP200_IRUGA?13:2;*rank=party_skill_rank193(m,skill);
 if(!*rank||!campaignConfig200.skills[m->id]||campaignConfig200.priority[m->id]==PARTY_SUPPORT200||now<m->skillAt)return 1;
 if(m->sp<party_skill_cost200(skill,*rank)){*rank=0;return 1;}
 return skill;
}
static void party_melee_tick213(Combat*g,CampaignFollower200*m,float dt,unsigned slot){
 if(g->peaceful)return;
 if(!party_target_ok200(g,m->target)||g->mobs[m->target].life!=m->targetLife||g->time>=m->thinkAt){m->target=party_choose_target200(g,m);m->targetLife=m->target>=0?g->mobs[m->target].life:0;m->thinkAt=g->time+.15f;}
 if(m->target<0)return;CombatMob*e=g->mobs+m->target;m->ownsMove=1;combat_face(&m->faceX,&m->faceY,e->x-m->x,e->y-m->y);
 if(combat_dist(m->x,m->y,e->x,e->y)>16){party_walk_to200(g,m,e->x,e->y,16,dt,slot,m->target);return;}
 m->moving=0;if(g->time<m->nextAttack||!party_line200(g,m->x,m->y,e->x,e->y))return;
 unsigned rank,skill=party_melee_choice213(m,g->time,&rank);party_physical_begin213(g,m,e,skill,rank);
}
typedef void(*PartyPoisonAfter213)(Combat*,CombatMob*,unsigned);
static void party_poison_after213(Combat*g,CombatMob*enemy,unsigned rank){class_poison50(g,enemy,10+4*(int)rank,10+5*(float)rank);}
static void party_envenom_step213(Combat*g,CampaignFollower200*m,PartyBoltHit204 hit,PartyPoisonAfter213 after){
 if(m->pendingSkill!=13||g->time<m->impactAt)return;m->pendingSkill=0;
 int target=m->pendingTarget;if(!party_target_ok200(g,target)||g->mobs[target].life!=m->pendingLife)return;
 CombatMob*e=g->mobs+target;if(combat_dist(m->x,m->y,e->x,e->y)>24||!party_line200(g,m->x,m->y,e->x,e->y))return;
 if(combat_random(g)%100>=(unsigned)combat_hit_rate((int)m->level+party_stat200(m,4,g->time),combat_mob_flee(e))){combat_miss(g,e->x,e->y);return;}
 int damage=(int)party_power_values202(m->id,(unsigned)party_stat200(m,0,g->time),(unsigned)party_stat200(m,4,g->time),(unsigned)party_stat200(m,5,g->time));damage+=15*(int)m->pendingRank+3*(int)party_skill_rank193(m,129);
 hit(g,m,target,m->pendingLife,damage,0);if(e->hp>0)after(g,e,m->pendingRank);
}
#endif
