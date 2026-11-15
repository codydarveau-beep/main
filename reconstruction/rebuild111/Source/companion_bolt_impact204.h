/* Original ordinary bolt impacts: one debit, individual rolls, serial-safe repeats. */
#ifndef MYRO_COMPANION_BOLT_IMPACT204_H
#define MYRO_COMPANION_BOLT_IMPACT204_H
static int party_bolt_skill204(unsigned skill){return skill==3||skill==9||skill==21;}
typedef void(*PartyBoltHit204)(Combat*,CampaignFollower200*,int,unsigned,int,unsigned);
typedef void(*PartyBoltCue204)(Combat*,unsigned,float,float);
static void party_bolt_step204(Combat*g,CampaignFollower200*m,PartyBoltHit204 hit,PartyBoltCue204 cue){unsigned skill=m->pendingSkill;if(!party_bolt_skill204(skill)||g->time<m->impactAt)return;m->pendingSkill=0;int target=m->pendingTarget;if(!party_target_ok200(g,target)||g->mobs[target].life!=m->pendingLife)return;CombatMob*e=g->mobs+target;if(combat_dist(m->x,m->y,e->x,e->y)>96||!party_line200(g,m->x,m->y,e->x,e->y))return;if(m->remainingHits204==m->pendingRank){unsigned cost=party_skill_base_cost201(skill,m->pendingRank);if(m->sp<cost||!party_save_vital200(m,m->hp,m->sp-cost))return;}unsigned intelligence=(unsigned)party_stat200(m,3,g->time),low=intelligence+(intelligence/7)*(intelligence/7),high=intelligence+(intelligence/5)*(intelligence/5);int damage=(int)(low+combat_random(g)%(high-low+1));hit(g,m,target,m->pendingLife,damage,1);cue(g,skill,e->x,e->y);if(m->remainingHits204<2||e->hp<=0||e->life!=m->pendingLife)return;m->remainingHits204--;m->pendingSkill=skill;m->impactAt=g->time+.2f;}
#endif
