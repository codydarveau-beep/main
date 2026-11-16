/* Original basic/Bash impact, including learned career passive 35. */
#ifndef MYRO_COMPANION_BASIC_IMPACT208_H
#define MYRO_COMPANION_BASIC_IMPACT208_H
static unsigned party_flee208(const CampaignFollower200*m,float now){return m->level+(unsigned)party_stat200(m,1,now)+3*party_skill_rank193(m,34);}
static void party_basic_step208(Combat*g,CampaignFollower200*m,PartyBoltHit204 hit,PartyBoltCue204 cue){
 unsigned skill=m->pendingSkill;
 if((skill!=1&&skill!=SKILL_BASH)||g->time<m->impactAt)return;
 m->pendingSkill=0;
 int target=m->pendingTarget;
 if(!party_target_ok200(g,target)||g->mobs[target].life!=m->pendingLife)return;
 CombatMob*enemy=g->mobs+target;
 if(combat_dist(m->x,m->y,enemy->x,enemy->y)>24||!party_line200(g,m->x,m->y,enemy->x,enemy->y))return;
 int damage=(int)party_power_values202(m->id,(unsigned)party_stat200(m,0,g->time),(unsigned)party_stat200(m,4,g->time),(unsigned)party_stat200(m,5,g->time));
 damage+=4*(int)party_skill_rank193(m,35);
 if(skill==SKILL_BASH)damage=damage*(100+30*(int)m->pendingRank)/100;
 if(combat_random(g)%100>=(unsigned)combat_hit_rate((int)m->level+party_stat200(m,4,g->time),combat_mob_flee(enemy))){combat_miss(g,enemy->x,enemy->y);return;}
 hit(g,m,target,m->pendingLife,damage,0);
 if(skill!=1&&cue)cue(g,skill,enemy->x,enemy->y);
}
#endif
