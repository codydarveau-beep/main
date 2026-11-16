/* Original Pip support priority: learned Heal in reach, then his physical kit. */
#ifndef MYRO_COMPANION_PIP_SUPPORT214_H
#define MYRO_COMPANION_PIP_SUPPORT214_H
typedef void(*PartyResolve214)(Combat*,CampaignFollower200*);
static int party_pip_heal214(Combat*g,CampaignFollower200*m,PartyResolve214 resolve){
 if(!campaignConfig200.skills[m->id]||g->time<m->skillAt)return 0;
 unsigned rank=party_skill_rank193(m,SKILL_HEAL);if(!rank)return 0;
 unsigned cost=party_skill_cost200(SKILL_HEAL,rank);int target=party_heal_target200(g,m);if(target==-2||m->sp<cost)return 0;
 CampaignFollower200*recipient=target>=0?party_member200((unsigned)target):NULL;
 float x=recipient?recipient->x:g->x,y=recipient?recipient->y:g->y;
 if(combat_dist(m->x,m->y,x,y)>64||!party_line200(g,m->x,m->y,x,y)||!party_save_vital200(m,m->hp,m->sp-cost))return 0;
 m->pendingSkill=m->lastSkill=SKILL_HEAL;m->pendingRank=rank;m->healTarget=target;m->pendingLife=recipient?recipient->life:0;m->attackAt=g->time;m->attackUntil=g->time+.6f;m->impactAt=g->time;m->castUntil=0;m->nextAttack=m->skillAt=g->time+1;m->ownsMove=1;m->moving=0;
 resolve(g,m);return 1;
}
#endif
