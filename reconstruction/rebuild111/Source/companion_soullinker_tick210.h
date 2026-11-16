/* Original Miri priorities, including prepared follow-up and size preferences. */
#ifndef MYRO_COMPANION_SOULLINKER_TICK210_H
#define MYRO_COMPANION_SOULLINKER_TICK210_H
static unsigned party_soullinker_choice210(const CampaignFollower200*m,const CombatMob*enemy,float now,unsigned*rank){
 *rank=0;unsigned learned=party_skill_rank193(m,440);
 if(m->esmaUntil209>now&&learned&&m->sp>=party_caster_cost194(m,440,learned)){*rank=learned;return 440;}
 unsigned first=mobClassData50[enemy->kind][1]==0?438:439;
 for(unsigned i=0;i<2;i++){unsigned skill=i?(first==438?439:438):first;learned=party_skill_rank193(m,skill);if(learned&&m->sp>=party_caster_cost194(m,skill,learned)){*rank=learned;return skill;}}
 return 0;
}
static void party_soullinker_tick210(Combat*g,CampaignFollower200*m,float dt,unsigned slot){
 if(g->peaceful||!campaignConfig200.skills[m->id])return;
 if(!party_target_ok200(g,m->target)||g->mobs[m->target].life!=m->targetLife||g->time>=m->thinkAt){m->target=party_choose_target200(g,m);m->targetLife=m->target>=0?g->mobs[m->target].life:0;m->thinkAt=g->time+.15f;}
 if(m->target<0)return;
 CombatMob*enemy=g->mobs+m->target;unsigned rank,skill=party_soullinker_choice210(m,enemy,g->time,&rank);
 if(!skill)return;
 const ClassSkill50*d=class_skill_data50(skill);if(!d)return;
 float reach=fabsf((float)d->range[rank-1])*8.f,distance=combat_dist(m->x,m->y,enemy->x,enemy->y);
 m->ownsMove=1;combat_face(&m->faceX,&m->faceY,enemy->x-m->x,enemy->y-m->y);
 if(distance<32&&distance>1){float step=party_walk_speed200(m,g->time)*fminf(dt,.05f);m->moving=combat_move(g,&m->x,&m->y,m->x+(m->x-enemy->x)/distance*step,m->y+(m->y-enemy->y)/distance*step);if(m->moving){m->elapsed+=dt;return;}}
 if(distance>reach){party_walk_to200(g,m,enemy->x,enemy->y,reach,dt,slot,m->target);return;}
 m->moving=0;if(g->time<m->nextAttack||g->time<m->skillAt||!party_line200(g,m->x,m->y,enemy->x,enemy->y))return;
 unsigned hits=skill==440?rank:(unsigned)abs(d->hits[rank-1]);if(!hits)hits=1;
 float dex=fminf(150,(float)party_stat200(m,4,g->time)),cast=d->cast[rank-1]*(150-dex)/150000.f,delay=d->delay[rank-1]/1000.f;
 m->pendingSkill=m->lastSkill=skill;m->pendingRank=rank;m->remainingHits204=hits;m->impactPaid209=0;m->pendingTarget=m->target;m->pendingLife=enemy->life;m->attackAt=g->time;m->castUntil=m->impactAt=g->time+cast;m->attackUntil=m->impactAt+(hits-1)*.2f+.3f;m->nextAttack=m->skillAt=fmaxf(m->attackUntil,m->impactAt+delay);
 if(cast>0)combat_sound_at(g,58,0);
}
#endif
