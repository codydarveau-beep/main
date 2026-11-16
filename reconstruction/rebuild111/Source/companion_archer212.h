/* Original Judia basic/Double Strafe representation, travel and hit series. */
#ifndef MYRO_COMPANION_ARCHER212_H
#define MYRO_COMPANION_ARCHER212_H
typedef struct{unsigned map;float x,y,toX,toY,start,end;}CampaignArrow212;
static CampaignArrow212 campaignArrows212[8];static unsigned campaignArrowNext212;
typedef struct{unsigned id,map,member,life;float at,x,y,z;unsigned positioned;}CampaignNativeFx212;
static CampaignNativeFx212 campaignNativeFx212[8];static unsigned campaignNativeFxNext212;
static void(*partyNativeSound212)(Combat*,unsigned);
static void party_native_effect212(Combat*g,CampaignFollower200*m,unsigned effect){campaignNativeFx212[campaignNativeFxNext212++%8]=(CampaignNativeFx212){effect,g->mapId,m->id,m->life,g->time,0,0,0,0};if(partyNativeSound212)partyNativeSound212(g,effect);}

static void party_archer_step212(Combat*g,CampaignFollower200*m,PartyBoltHit204 hit){
 if(m->pendingSkill!=17||g->time<m->impactAt)return;m->pendingSkill=0;
 int target=m->pendingTarget;if(!party_target_ok200(g,target)||g->mobs[target].life!=m->pendingLife)return;
 CombatMob*e=g->mobs+target;if(combat_dist(m->x,m->y,e->x,e->y)>96||!party_line200(g,m->x,m->y,e->x,e->y))return;
 int accuracy=(int)m->level+party_stat200(m,4,g->time)+(int)party_skill_rank193(m,15);
 if(combat_random(g)%100>=(unsigned)combat_hit_rate(accuracy,combat_mob_flee(e)))combat_miss(g,e->x,e->y);
 else{int damage=(int)party_power_values202(m->id,(unsigned)party_stat200(m,0,g->time),(unsigned)party_stat200(m,4,g->time),(unsigned)party_stat200(m,5,g->time));if(m->pendingRank)damage=damage*(90+10*(int)m->pendingRank)/100;hit(g,m,target,m->pendingLife,damage,0);}
 if(m->remainingHits204<2||e->hp<=0||e->life!=m->pendingLife)return;
 m->remainingHits204--;m->pendingSkill=17;m->impactAt=g->time+.1f;
}
static unsigned party_archer_rank212(const CampaignFollower200*m,float now){
 if(!campaignConfig200.skills[m->id]||campaignConfig200.priority[m->id]==PARTY_SUPPORT200||now<m->skillAt)return 0;
 unsigned rank=party_skill_rank193(m,17);return rank&&m->sp>=party_skill_cost200(17,rank)?rank:0;
}
#include "companion_physical_begin213.h"
static void party_archer_tick212(Combat*g,CampaignFollower200*m,float dt,unsigned slot){
 if(g->peaceful)return;
 if(!party_target_ok200(g,m->target)||g->mobs[m->target].life!=m->targetLife||g->time>=m->thinkAt){m->target=party_choose_target200(g,m);m->targetLife=m->target>=0?g->mobs[m->target].life:0;m->thinkAt=g->time+.15f;}
 if(m->target<0)return;CombatMob*e=g->mobs+m->target;m->ownsMove=1;combat_face(&m->faceX,&m->faceY,e->x-m->x,e->y-m->y);float distance=combat_dist(m->x,m->y,e->x,e->y);
 if(distance>72){party_walk_to200(g,m,e->x,e->y,72,dt,slot,m->target);return;}
 m->moving=0;if(g->time<m->nextAttack||!party_line200(g,m->x,m->y,e->x,e->y))return;
 unsigned rank=party_archer_rank212(m,g->time);party_physical_begin213(g,m,e,17,rank);
}
#endif
