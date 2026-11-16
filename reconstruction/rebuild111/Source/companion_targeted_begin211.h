/* Shared original targeted-caster movement and cast initialization. */
#ifndef MYRO_COMPANION_TARGETED_BEGIN211_H
#define MYRO_COMPANION_TARGETED_BEGIN211_H
static void party_targeted_tick211(Combat*g,CampaignFollower200*m,float dt,unsigned slot,unsigned skill,unsigned rank){
 CombatMob*enemy=g->mobs+m->target;
 const ClassSkill50*d=class_skill_data50(skill);const CastTiming*t=cast_timing(skill);
 float reach=d?fabsf((float)d->range[rank-1])*8.f:72.f,distance=combat_dist(m->x,m->y,enemy->x,enemy->y);
 m->ownsMove=1;combat_face(&m->faceX,&m->faceY,enemy->x-m->x,enemy->y-m->y);
 if(distance<32&&distance>1){float step=party_walk_speed200(m,g->time)*fminf(dt,.05f);m->moving=combat_move(g,&m->x,&m->y,m->x+(m->x-enemy->x)/distance*step,m->y+(m->y-enemy->y)/distance*step);if(m->moving){m->elapsed+=dt;return;}}
 if(distance>reach){party_walk_to200(g,m,enemy->x,enemy->y,reach,dt,slot,m->target);return;}
 m->moving=0;if(g->time<m->nextAttack||g->time<m->skillAt||!party_line200(g,m->x,m->y,enemy->x,enemy->y))return;
 unsigned hits=skill==440?rank:d?(unsigned)abs(d->hits[rank-1]):rank;if(!hits)hits=1;
 float dex=fminf(150,(float)party_stat200(m,4,g->time)),cast=(d?d->cast[rank-1]:t?t->cast[rank-1]:0)*(150-dex)/150000.f,delay=(d?d->delay[rank-1]:t?t->delay[rank-1]:0)/1000.f;
 m->pendingSkill=m->lastSkill=skill;m->pendingRank=rank;m->remainingHits204=hits;m->impactPaid209=0;m->pendingTarget=m->target;m->pendingLife=enemy->life;m->attackAt=g->time;m->castUntil=m->impactAt=g->time+cast;m->attackUntil=m->impactAt+(hits-1)*.2f+.3f;m->nextAttack=m->skillAt=fmaxf(m->attackUntil,m->impactAt+delay);
 if(cast>0)combat_sound_at(g,58,0);
}
#endif
