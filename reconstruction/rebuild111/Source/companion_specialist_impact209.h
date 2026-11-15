/* Original targeted Ninja and Soul Linker impact family. Choice stays separate. */
#ifndef MYRO_COMPANION_SPECIALIST_IMPACT209_H
#define MYRO_COMPANION_SPECIALIST_IMPACT209_H
static int party_specialist_spell209(unsigned skill){return skill==352||skill==355||skill==358||(skill>=438&&skill<=440);}
typedef void(*PartySpecialistAfter209)(Combat*,CampaignFollower200*,int,unsigned,unsigned);
static void party_specialist_after209(Combat*g,CampaignFollower200*m,int target,unsigned skill,unsigned rank){
 CombatMob*e=g->mobs+target;
 if(e->hp<=0)return;
 if(skill==438)combat_knockback(g,target,e->x-m->x,e->y-m->y,16);
 else if(skill==439&&mobClassData50[e->kind][1]==1)class_stun50(g,e,30+10*(int)rank,class_duration50(skill,(int)rank,0));
}
static void party_specialist_step209(Combat*g,CampaignFollower200*m,PartyBoltHit204 hit,PartyBoltCue204 cue,PartySpecialistAfter209 after){
 unsigned skill=m->pendingSkill,rank=m->pendingRank;
 if(!party_specialist_spell209(skill)||g->time<m->impactAt)return;
 m->pendingSkill=0;
 if(!rank||rank>10||!party_target_ok200(g,m->pendingTarget))return;
 int target=m->pendingTarget;CombatMob*e=g->mobs+target;
 const ClassSkill50*d=class_skill_data50(skill);
 float range=d?fabsf((float)d->range[rank-1])*8.f:96;
 if(e->life!=m->pendingLife||combat_dist(m->x,m->y,e->x,e->y)>range||!party_line200(g,m->x,m->y,e->x,e->y))return;
 unsigned wasPaid=m->impactPaid209;
 if(!wasPaid){
  unsigned cost=party_caster_cost194(m,skill,rank);
  if((skill==440&&m->esmaUntil209<=g->time)||m->sp<cost||!party_save_vital200(m,m->hp,m->sp-cost))return;
  m->impactPaid209=1;
  if(skill==440)m->esmaUntil209=0;
  else if((skill==438||skill==439)&&rank>=7)m->esmaUntil209=g->time+class_duration50(440,(int)rank,0);
 }
 unsigned intelligence=(unsigned)party_stat200(m,3,g->time),low=intelligence+(intelligence/7)*(intelligence/7),high=intelligence+(intelligence/5)*(intelligence/5);
 int ratio=100,size=mobClassData50[e->kind][1];
 if(skill==352)ratio=90;
 else if(skill==440)ratio=(int)m->level+40;
 else if(skill==439)ratio=size==2?1:100+5*(int)rank;
 else if(skill==438)ratio=size==0?100+10*(int)rank:1;
 int damage=(int)(low+combat_random(g)%(high-low+1))*ratio/100;
 if(damage<1)damage=1;
 hit(g,m,target,m->pendingLife,damage,1);
 if(!wasPaid)cue(g,skill,e->x,e->y);
 else campaignFx200[campaignFxNext200++%8]=(CampaignFx200){skill,g->mapId,e->x,e->y,g->time};
 after(g,m,target,skill,rank);
 if(m->remainingHits204<2||e->hp<=0||e->life!=m->pendingLife)return;
 m->remainingHits204--;m->pendingSkill=skill;m->impactAt=g->time+.2f;
 if(m->attackUntil<m->impactAt+.05f)m->attackUntil=m->impactAt+.05f;
}
#endif
