/* Original default-career physical impact cache: one fee and one hit roll for a series. */
#ifndef MYRO_COMPANION_CACHED_PHYSICAL219_H
#define MYRO_COMPANION_CACHED_PHYSICAL219_H
typedef void(*PartyPhysicalFinal218)(Combat*,CampaignFollower200*,int,unsigned,int);
typedef void(*PartyPhysicalPush221)(Combat*,int,float,float,float);
static void party_kick_ready221(Combat*g,CampaignFollower200*m,CombatMob*e){
 if((m->id!=16&&m->id!=17)||!campaignConfig200.skills[m->id]||m->comboUntil220>g->time)return;
 unsigned stance=m->id==16?385:389,skill=stance+1;if(!party_skill_rank193(m,stance)||!party_skill_rank193(m,skill)||combat_random(g)%100>=15)return;
 m->auxSkill220=skill;m->comboUntil220=g->time+fmaxf(.1f,(2000-4*party_stat200(m,1,g->time)-2*party_stat200(m,4,g->time))*.001f);m->pendingLife=e->life;
}
static int party_kick_skill221(unsigned skill){return skill==386||skill==388||skill==390||skill==392;}
static int party_kick_ratio221(unsigned skill,unsigned rank){return(skill==386||skill==388)?160+20*(int)rank:190+30*(int)rank;}
static void party_kick_area221(Combat*g,CampaignFollower200*m,int target,unsigned skill,unsigned rank,PartyPhysicalFinal218 hit,PartyPhysicalPush221 push){
 if(skill!=386&&skill!=390)return;const ClassSkill50*d=class_skill_data50(skill);if(!d||!rank||rank>10)return;CombatMob*primary=g->mobs+target;
 float x=skill==386?m->x:primary->x,y=skill==386?m->y:primary->y,radius=d->splash[rank-1]*8.f+4;
 for(unsigned i=0;i<MOB_COUNT;i++){CombatMob*e=g->mobs+i;if((int)i==target||!party_target_ok200(g,(int)i)||combat_dist(x,y,e->x,e->y)>radius||!party_line200(g,x,y,e->x,e->y))continue;
  int rate=class_element_rate48(e,0);if(rate<=0)continue;int power=(int)party_power_values202(m->id,(unsigned)party_stat200(m,0,g->time),(unsigned)party_stat200(m,4,g->time),(unsigned)party_stat200(m,5,g->time));power=power*party_kick_ratio221(skill,rank)/100;int damage=combat_reduce48(power*rate/100,combat_enemy_defense(e),mobStunVit[e->kind]);hit(g,m,(int)i,e->life,damage);
  if(skill==390&&e->hp>0)push(g,(int)i,e->x-x,e->y-y,d->knockback[rank-1]*8.f);
 }
}
static void party_cached_physical219(Combat*g,CampaignFollower200*m,PartyPhysicalFinal218 hit,PartyBoltCue204 cue,PartyPhysicalPush221 push){
 unsigned skill=m->pendingSkill,rank=m->pendingRank;if((skill!=1&&skill!=13&&skill!=142&&skill!=378&&skill!=202&&skill!=211&&!party_kick_skill221(skill))||g->time<m->impactAt)return;m->pendingSkill=0;
 int target=m->pendingTarget;if(!party_target_ok200(g,target)||g->mobs[target].life!=m->pendingLife)return;CombatMob*e=g->mobs+target;
 if(combat_dist(m->x,m->y,e->x,e->y)>(m->id==15?96:24)||!party_line200(g,m->x,m->y,e->x,e->y))return;
 if(!m->impactPaid209){
  unsigned cost=(skill==1||skill==202)?0:party_caster_cost194(m,skill,rank);if(m->sp<cost||!party_save_vital200(m,m->hp,m->sp-cost))return;m->impactPaid209=1;
  if(combat_random(g)%100>=(unsigned)combat_hit_rate((int)m->level+party_stat200(m,4,g->time)+(m->id==15?(int)party_skill_rank193(m,373):0),combat_mob_flee(e))){combat_miss(g,e->x,e->y);return;}
  int power=(int)party_power_values202(m->id,(unsigned)party_stat200(m,0,g->time),(unsigned)party_stat200(m,4,g->time),(unsigned)party_stat200(m,5,g->time));if(skill==13)power+=15*(int)rank;
  if(m->id==5)power+=3*(int)party_skill_rank193(m,198);
  if(party_kick_skill221(skill))power=power*party_kick_ratio221(skill,rank)/100;else if(skill==202)power=power*(100+20*(int)rank)/100;else if(skill==211)power=power*(150+50*(int)rank)/100;else if(skill==142)power=power*(300+40*(int)rank)/100;else if(skill==378)power=power*(100+10*(int)rank)/100;
  int rate=class_element_rate48(e,0);if(rate<=0)return;
  m->impactDamage218=(unsigned)combat_reduce48(power*rate/100,combat_enemy_defense(e),mobStunVit[e->kind]);m->splitRemainder220=0;
  if(skill==202||skill==211){unsigned hits=m->remainingHits204?m->remainingHits204:1,total=m->impactDamage218;m->impactDamage218=total/hits;m->splitRemainder220=total%hits;if(!m->impactDamage218){m->impactDamage218=1;m->splitRemainder220=0;}}
  if(skill!=1&&skill!=202)cue(g,skill,e->x,e->y);
 }
 unsigned damage=m->impactDamage218;if(m->splitRemainder220){damage++;m->splitRemainder220--;}const ClassSkill50*kick=skill==386?class_skill_data50(skill):NULL;if(!kick||combat_dist(m->x,m->y,e->x,e->y)<=kick->splash[rank-1]*8.f+4)hit(g,m,target,m->pendingLife,(int)damage);
 party_kick_area221(g,m,target,skill,rank,hit,push);
 if(e->hp<=0)return;
 if(skill==142)combat_face(&e->faceX,&e->faceY,m->x-e->x,m->y-e->y);
 else if(skill==13)party_poison_after213(g,e,rank);else if(skill==388)class_stun50(g,e,100,class_duration50(skill,(int)rank,1));
 if(m->remainingHits204<2){if(skill==202&&party_skill_rank193(m,211)){m->auxSkill220=202;m->comboUntil220=g->time+1.2f;m->skillAt=g->time;}else if(skill==1)party_kick_ready221(g,m,e);return;}if(e->life!=m->pendingLife)return;
 m->remainingHits204--;m->pendingSkill=skill;m->impactAt=g->time+.1f;m->attackUntil=fmaxf(m->attackUntil,m->impactAt+.05f);
}
#endif
