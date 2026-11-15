/* MIT. Pre-renewal self support and offensive uses against Undead/Demons. */
static int class_undead50(const CombatMob*m){return mobClassData50[m->kind][0]==1||mobElement48[m->kind][0]==9;}
static int class_evil50(const CombatMob*m){return class_undead50(m)||mobClassData50[m->kind][0]==6;}
static void class_high_priest_execute52(Combat*g,unsigned id,int rank){
 if(id==SK52_HP_ASSUMPTIO){g->buffs[2]=0;g->shieldHP=g->shieldHits=0;class_buff50(g,id,rank);}
 if(id==SK52_HP_BASILICA){class_buff50(g,id,rank);g->class50.basilicaX52=g->x;g->class50.basilicaY52=g->y;g->autoAttack=0;g->castDelay=0;}
}
static int class_priest_cell50(const ClassArea50*a,float x,float y){
 float dx=fabsf(x-a->x),dy=fabsf(y-a->y);
 return a->id==189?dx<20&&dy<20&&(dx<12||dy<12):dx<28&&dy<28&&(dx<12||dy<12);
}
static void class_priest_execute50(Combat*g,unsigned id,int rank,int target,float x,float y){
 if(id==187||id==188||id==190||id==192||id==193){class_buff50(g,id,rank);return;}
 if(id==189||id==197){ClassArea50*a=&g->areas50[class_area_slot50(g)];*a=(ClassArea50){.id=id,.rank=rank,.hits=(rank+3)*2,.map=g->mapId,.x=x,.y=y,.until=g->time+class_duration50(id,rank,0),.next=g->time+1,.created=g->time};return;}
 CombatMob*m=&g->mobs[target];
 if(id==191){if(class_undead50(m)){if(!combat_status_boss(m))m->mobBlind=class_duration50(id,rank,1);}else{m->frozenLeft=m->stoneLeft=m->stoneWait=m->stun=0;m->class50.sleepUntil=0;m->aggro=0;}return;}
 if(id==194){if(m->class50.silenceUntil>g->time)m->class50.silenceUntil=0;else if(!combat_status_boss(m))m->class50.silenceUntil=g->time+class_duration50(id,rank,0)*(100-mobStunVit[m->kind])/100;return;}
 if(id==196){m->class50.lexUntil=g->time+class_duration50(id,rank,0);return;}
 if(id==185||id==195){int chance=20*rank+stat_value(g,5)+stat_value(g,3)+g->level+200-(int)((int64_t)200*m->hp/combat_mob_max(m));if(chance>700)chance=700;
  int damage=!combat_status_boss(m)&&class_chance50(g,chance,1000)?m->hp:(g->level+stat_value(g,3)+10*rank)*class_attack_rate48(g,m,6)/100;
  skill_hit(g,target,damage,0);
 }
}
static void class_priest_tick50(Combat*g,ClassArea50*a){
 if(class_field_at48(g,104,a->x,a->y)){a->until=0;return;}
 int rank=a->rank,oldSkill=g->fxSkill,oldRank=g->fxRank48;g->fxSkill=a->id;g->fxRank48=rank;
 if(a->id==189){int heal=rank>6?777:rank*100;
  if(class_priest_cell50(a,g->x,g->y)&&g->hp>0&&g->hp<g->maxhp){int amount=g->maxhp-g->hp;if(amount>heal)amount=heal;g->hp+=amount;a->hits--;}
  for(int i=0;i<MOB_COUNT&&a->hits>0;i++){CombatMob*m=&g->mobs[i];if(!class_in_area50(g,m,a->x,a->y,20)||!class_priest_cell50(a,m->x,m->y))continue;
   if(class_evil50(m)){int damage=heal/2*class_attack_rate48(g,m,6)/100;damage=combat_hit_bonus50(g,m,damage);skill_hit_now49(g,i,damage,0,1);a->hits-=2;}
   else if(m->hp<combat_mob_max(m)){m->hp+=heal;if(m->hp>combat_mob_max(m))m->hp=combat_mob_max(m);a->hits--;}
  }
  if(a->hits<=0)a->until=0;a->next+=1;
 }else{
  for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(class_in_area50(g,m,a->x,a->y,28)&&class_priest_cell50(a,m->x,m->y)&&class_evil50(m)&&skill_burst_slot49(g)>=0)skill_magic_hit_ex48(g,i,combat_magic_power48(g)*rank*class_attack_rate48(g,m,6)/100,0,rank);}
  a->next+=3;
 }
 g->fxSkill=oldSkill;g->fxRank48=oldRank;
}
