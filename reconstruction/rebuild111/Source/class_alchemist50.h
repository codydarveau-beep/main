/* MIT. Source solo potion pitching, chemical protection, Bomb and summons. */
#include "companion_data50.h"
static int class_summon_ready50(const Combat*g,unsigned id,int rank){
 int same=0;for(int i=0;i<CLASS_SUMMONS50;i++){const ClassSummon50*s=&g->summons50[i];if(s->until<=g->time||s->map!=g->mapId||s->hp<=0)continue;if((id==244)==(s->kind==5))same++;if(id==243&&s->kind!=5&&s->kind!=rank-1)return 0;}
 return same<(id==243?6-rank:3)&&class_summon_slot50(g)>=0;
}
static void class_alchemist_execute50(Combat*g,unsigned id,int rank,int target,float x,float y){
 if(id>=245&&id<=248){class_buff50(g,id,rank);return;}
 if(id==240){ClassArea50*a=&g->areas50[class_area_slot50(g)];*a=(ClassArea50){.id=id,.rank=rank,.map=g->mapId,.x=x,.y=y,.until=g->time+class_duration50(id,rank,0),.next=g->time,.created=g->time};return;}
 if(id==241){CombatMob*m=&g->mobs[target];int damage=class_physical50(g,m,100+40*rank,1,0)-mobStunVit[m->kind];skill_hit(g,target,damage,0);if(m->hp>0&&!combat_status_boss(m)&&class_chance50(g,3*rank*(100-mobStunVit[m->kind])/100,100)){m->class50.bleedUntil=g->time+class_duration50(id,rank,1);m->class50.bleedNext=g->time+10;}return;}
 if(id==242){int item=item_source50(500+rank);const ItemDef*d=&itemDefs[item];int bonus=100+10*class_rank50(g,242)+5*class_rank50(g,238),heal=0,sp=0;
  if(d->healMin)heal=(d->healMin+combat_random(g)%(d->healMax-d->healMin+1))*bonus/100*(100+2*stat_value(g,2))/100*(100+10*skill_rank(g,26))/100;
  if(d->spMin)sp=(d->spMin+combat_random(g)%(d->spMax-d->spMin+1))*bonus/100*(100+2*stat_value(g,3))/100*(100+10*skill_rank(g,25))/100;
  g->hp+=heal;g->sp+=sp;if(g->hp>g->maxhp)g->hp=g->maxhp;if(g->sp>g->maxsp)g->sp=g->maxsp;return;
 }
 if(id==243||id==244){int k=class_summon_slot50(g),kind=id==244?5:rank-1;g->summons50[k]=(ClassSummon50){.kind=kind,.rank=rank,.hp=(int)summonData50[kind][1],.target=-1,.map=g->mapId,.x=x,.y=y,.until=g->time+class_duration50(id,rank,0),.next=g->time,.created=g->time,.attackAt=-100};return;}
}
static void class_alchemist_tick50(Combat*g,ClassArea50*a){
 if(class_field_at48(g,104,a->x,a->y)){a->until=0;return;}a->next+=1;class_sound_emit50(g,240);
 int old=g->fxSkill;g->fxSkill=240;for(int i=0;i<MOB_COUNT;i++)if(class_in_area50(g,&g->mobs[i],a->x,a->y,12))skill_hit(g,i,class_physical50(g,&g->mobs[i],100+20*a->rank,0,3),0);g->fxSkill=old;
}
static void class_summons_tick50(Combat*g){
 for(int n=0;n<CLASS_SUMMONS50;n++){ClassSummon50*s=&g->summons50[n];if(s->map!=g->mapId||s->until<=g->time||s->hp<=0)continue;const unsigned*d=summonData50[s->kind];
  if(s->kind==5){if(s->triggered&&g->time>=s->next){int old=g->fxSkill;g->fxSkill=244;for(int i=0;i<MOB_COUNT;i++)if(class_in_area50(g,&g->mobs[i],s->x,s->y,28))skill_hit(g,i,s->hp*class_attack_rate48(g,&g->mobs[i],0)/100,0);g->fxSkill=old;class_fx50(g,244,s->rank,s->x,s->y);s->attackAt=g->time;s->hp=0;s->until=g->time+.5f;}continue;}
  if(g->time<s->next)continue;
  int target=-1;float nearest=d[2]+.01f;for(int i=0;i<MOB_COUNT;i++)if(class_in_area50(g,&g->mobs[i],s->x,s->y,d[2])){float distance=combat_dist(s->x,s->y,g->mobs[i].x,g->mobs[i].y);if(distance<nearest){target=i;nearest=distance;}}
  s->target=target;if(target<0)continue;CombatMob*m=&g->mobs[target];int damage=d[3]+combat_random(g)%(d[4]-d[3]+1);damage=combat_reduce48(damage,combat_enemy_defense(m),mobStunVit[m->kind]);
  if(!class_chance50(g,combat_hit_rate(d[6],combat_mob_flee(m)),100)){combat_miss(g,m->x,m->y);}else{int old=g->fxSkill;g->fxSkill=0;skill_hit(g,target,damage,0);g->fxSkill=old;if(m->hp>0){m->class50.companionTarget=n+2;m->aggro=1;}}
  s->attackAt=g->time;s->next=g->time+d[7]/1000.f;
 }
}
