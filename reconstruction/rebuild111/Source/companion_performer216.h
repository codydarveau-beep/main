/* Original Oren/Lale physical ranged kits: deferred own-SP payment, preserved
 * basic fallback reach, native projectile timing and learned career skills. */
#ifndef MYRO_COMPANION_PERFORMER216_H
#define MYRO_COMPANION_PERFORMER216_H
static unsigned party_performer_choice216(const CampaignFollower200*m,float now,unsigned*rank){
 unsigned skill=m->id==9?173:180;*rank=0;
 if(!campaignConfig200.skills[m->id]||campaignConfig200.priority[m->id]==PARTY_SUPPORT200||now<m->skillAt)return 1;
 *rank=party_skill_rank193(m,skill);
 if(!*rank||m->sp<party_skill_cost200(skill,*rank)){*rank=0;return 1;}return skill;
}
static void party_performer_begin216(Combat*g,CampaignFollower200*m,CombatMob*e,unsigned skill,unsigned rank){
 int item=inventory_catalog52(partyWeapons202[m->id]),weapon=item>=0?itemDefs[item].wtype:0;if(weapon<0||weapon>22)weapon=0;
 int motion=jobMotion52[m->job][weapon];motion-=motion*(4*party_stat200(m,1,g->time)+party_stat200(m,4,g->time))/1000;if(motion<30)motion=30;
 float period=motion*.002f,duration=fmaxf(.1f,fminf(.75f,period)),launch=g->time+duration*.6f;
 m->pendingSkill=m->lastSkill=skill;m->pendingRank=rank;m->remainingHits204=1;m->impactPaid209=0;m->pendingTarget=m->target;m->pendingLife=e->life;m->attackAt=g->time;m->attackUntil=g->time+duration;m->castUntil=0;m->impactAt=launch+combat_dist(m->x,m->y,e->x,e->y)/360.f;m->nextAttack=g->time+period;
 if(skill!=1){const ClassSkill50*d=class_skill_data50(skill);float delay=d?d->delay[rank-1]/1000.f:0;m->nextAttack=fmaxf(m->nextAttack,g->time+delay);m->skillAt=g->time+fmaxf(delay,campaignConfig200.priority[m->id]==PARTY_OFFENSE200?1.f:3.f);}
 campaignArrows212[campaignArrowNext212++%8]=(CampaignArrow212){g->mapId,m->x,m->y,e->x,e->y,launch,m->impactAt};
}
static void party_performer_tick216(Combat*g,CampaignFollower200*m,float dt,unsigned slot){
 if(g->peaceful)return;
 if(!party_target_ok200(g,m->target)||g->mobs[m->target].life!=m->targetLife||g->time>=m->thinkAt){m->target=party_choose_target200(g,m);m->targetLife=m->target>=0?g->mobs[m->target].life:0;m->thinkAt=g->time+.15f;}
 if(m->target<0)return;CombatMob*e=g->mobs+m->target;unsigned rank,skill=party_performer_choice216(m,g->time,&rank);float reach=skill==1?16:72;m->ownsMove=1;combat_face(&m->faceX,&m->faceY,e->x-m->x,e->y-m->y);
 if(combat_dist(m->x,m->y,e->x,e->y)>reach){party_walk_to200(g,m,e->x,e->y,reach,dt,slot,m->target);return;}
 m->moving=0;if(g->time<m->nextAttack||!party_line200(g,m->x,m->y,e->x,e->y))return;party_performer_begin216(g,m,e,skill,rank);
}
static void party_performer_step216(Combat*g,CampaignFollower200*m,PartyBoltHit204 hit,PartyBoltCue204 cue){
 unsigned skill=m->pendingSkill;if((skill!=1&&skill!=173&&skill!=180)||g->time<m->impactAt)return;m->pendingSkill=0;
 int target=m->pendingTarget;if(!party_target_ok200(g,target)||g->mobs[target].life!=m->pendingLife)return;CombatMob*e=g->mobs+target;
 if(combat_dist(m->x,m->y,e->x,e->y)>96||!party_line200(g,m->x,m->y,e->x,e->y))return;
 if(!m->impactPaid209){unsigned cost=skill==1?0:party_caster_cost194(m,skill,m->pendingRank);if(m->sp<cost||!party_save_vital200(m,m->hp,m->sp-cost))return;m->impactPaid209=1;}
 if(combat_random(g)%100>=(unsigned)combat_hit_rate((int)m->level+party_stat200(m,4,g->time),combat_mob_flee(e))){combat_miss(g,e->x,e->y);return;}
 int damage=(int)party_power_values202(m->id,(unsigned)party_stat200(m,0,g->time),(unsigned)party_stat200(m,4,g->time),(unsigned)party_stat200(m,5,g->time));if(skill!=1)damage=damage*(125+25*(int)m->pendingRank)/100;
 if(skill!=1)cue(g,skill,e->x,e->y);hit(g,m,target,m->pendingLife,damage,0);
}
#endif
