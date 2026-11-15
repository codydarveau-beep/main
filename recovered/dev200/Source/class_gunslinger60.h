/* GPL-3.0-or-later. Original pre-renewal Gunslinger effects, bounded by the existing combat pools.
 * Formula references: Hercules battle.cpp, skill.cpp and status.cpp (pre-RE).
 * Resource ownership stays in expanded_resources60 and the shared cast pipeline. */
static int gunslinger_ready60(Combat*g,unsigned id,int target,float x,float y){
 if(id==SK60_GS_DESPERADO||id==SK60_GS_GROUNDDRIFT){
  if(class_area_slot50(g)<0){combat_notice(g,POP_SKILLS,"Wait for an active ground effect to expire; resources kept.");return 0;}
  if(id==SK60_GS_GROUNDDRIFT&&g->canMove&&!g->canMove(g->world,x,y,x,y))return 0;
 }
 if((id==SK60_GS_TRIPLEACTION||id==SK60_GS_RAPIDSHOWER)&&skill_burst_slot49(g)<0){combat_notice(g,POP_SKILLS,"Wait for active skill hits; resources kept.");return 0;}
 if(class_skill_data50(id)->target==2&&(target<0||target>=MOB_COUNT||!g->mobs[target].enabled||g->mobs[target].hp<=0))return 0;
 return 1;
}
static void gunslinger_execute60(Combat*g,unsigned id,int rank,int target,float x,float y){
 if(id==SK60_GS_GLITTERING){
  if(class_chance50(g,20+10*rank,100)){
   if(g->expandedCoins60==10){memmove(g->class50.coinUntil60,g->class50.coinUntil60+1,9*sizeof(float));g->expandedCoins60--;}
   g->class50.coinUntil60[g->expandedCoins60++]=g->time+class_duration50(id,rank,0);
  }else if(g->expandedCoins60){g->expandedCoins60--;memmove(g->class50.coinUntil60,g->class50.coinUntil60+1,g->expandedCoins60*sizeof(float));}
  combat_notice(g,POP_SKILLS,"%u coins",g->expandedCoins60);return;
 }
 if(id==SK60_GS_MADNESSCANCEL||id==SK60_GS_ADJUSTMENT||id==SK60_GS_INCREASING||id==SK60_GS_GATLINGFEVER){
  if(id==SK60_GS_GATLINGFEVER&&class_active50(g,id))g->class50.until[id-127]=0;
  else{class_buff50(g,id,rank);if(id==SK60_GS_MADNESSCANCEL)g->class50.until[SK60_GS_ADJUSTMENT-127]=0;if(id==SK60_GS_ADJUSTMENT)g->class50.until[SK60_GS_MADNESSCANCEL-127]=0;}
  return;
 }
 if(id==SK60_GS_DESPERADO||id==SK60_GS_GROUNDDRIFT){
  int element=class_weapon_element50(g);if(id==SK60_GS_GROUNDDRIFT&&!element)element=(int[]){4,7,5,1,3}[combat_random(g)%5];
  ClassArea50*a=&g->areas50[class_area_slot50(g)];
  *a=(ClassArea50){.id=id,.rank=rank,.map=g->mapId,.x=id==SK60_GS_DESPERADO?g->x:x,.y=id==SK60_GS_DESPERADO?g->y:y,.until=g->time+class_duration50(id,rank,0),.next=g->time,.created=g->time,.power=element};return;
 }
 if(target<0||target>=MOB_COUNT)return;CombatMob*m=&g->mobs[target];
 if(id==SK60_GS_CRACKER){int chance=65-5*(int)(combat_dist(g->x,g->y,m->x,m->y)/8);class_stun50(g,m,chance<30?30:chance,class_duration50(id,rank,1));return;}
 if(id==SK60_GS_FLING){skill_hit(g,target,g->joblevel,0);if(m->hp>0){m->class50.flingUntil60=g->time+class_duration50(id,rank,0);m->class50.flingCoins60=g->class50.flingSpent60?g->class50.flingSpent60:5;}return;}
 int ratio=100,hits=1,ignore=0;
 switch(id){
 case SK60_GS_TRIPLEACTION:ratio=100+50*rank;hits=3;break;
 case SK60_GS_BULLSEYE:if(!combat_status_boss(m)&&(mobClassData50[m->kind][0]==2||mobClassData50[m->kind][0]==7))ratio=500;break;
 case SK60_GS_TRACKING:ratio=200+100*rank;break;
 case SK60_GS_PIERCINGSHOT:ratio=100+20*rank;ignore=1;break;
 case SK60_GS_RAPIDSHOWER:ratio=100+10*rank;hits=5;break;
 case SK60_GS_DUST:ratio=100+50*rank;break;
 case SK60_GS_FULLBUSTER:ratio=300+100*rank;break;
 case SK60_GS_SPREADATTACK:ratio=100+20*(rank-1);break;
 }
 if(id==SK60_GS_SPREADATTACK){float tx=m->x,ty=m->y;int radius=class_skill_data50(id)->splash[rank-1]*8;for(int i=0;i<MOB_COUNT;i++)if(class_in_area50(g,&g->mobs[i],tx,ty,radius))skill_hit(g,i,class_physical50(g,&g->mobs[i],ratio,0,-1),0);return;}
 int damage=class_physical50(g,m,ratio,ignore,-1);
 if(id==SK60_GS_MAGICALBULLET)damage=combat_reduce48(item_physical_bonus52(g,m,(class_weapon_power50(g,m,0)+combat_matk_min48(g))*class_attack_rate48(g,m,8)/100,id),combat_enemy_defense(m),mobStunVit[m->kind]);
 skill_hit_ex(g,target,damage*hits,0,hits);
 if(m->hp>0&&id==SK60_GS_DISARM&&!combat_status_boss(m)&&class_chance50(g,3*rank+(stat_value(g,4)-mobSourceDex[m->kind])/5,100))m->class50.stripUntil[0]=g->time+class_duration50(id,rank,0);
 if(m->hp>0&&id==SK60_GS_PIERCINGSHOT&&!combat_status_boss(m)&&class_chance50(g,3*rank,100)){m->class50.bleedUntil=g->time+class_duration50(id,rank,1);m->class50.bleedNext=g->time+10;}
 if(m->hp>0&&id==SK60_GS_BULLSEYE&&ratio==500&&class_chance50(g,1,1000))m->hp=1;
 if(m->hp>0&&id==SK60_GS_DUST)combat_knockback(g,target,m->x-g->x,m->y-g->y,8*class_skill_data50(id)->knockback[rank-1]);
 if(id==SK60_GS_FULLBUSTER&&class_chance50(g,2*rank,100))g->blindLeft=class_duration50(id,rank,1);
}
static void gunslinger_tick60(Combat*g){
 unsigned n=0;for(unsigned i=0;i<g->expandedCoins60;i++)if(g->class50.coinUntil60[i]>g->time)g->class50.coinUntil60[n++]=g->class50.coinUntil60[i];g->expandedCoins60=n;
 for(int k=0;k<CLASS_AREAS50;k++){
  ClassArea50*a=&g->areas50[k];if(a->id!=SK60_GS_DESPERADO&&a->id!=SK60_GS_GROUNDDRIFT)continue;
  if(a->map!=g->mapId){a->until=0;continue;}if(a->until<=g->time||a->next>g->time)continue;
  int old=g->fxSkill;g->fxSkill=a->id;
  if(a->id==SK60_GS_DESPERADO){
   /* Ten 100 ms pulses; probability depends on each original 7x7 cell. */
   a->next=g->time+.1f;if(a->hits++>=10){a->until=0;g->fxSkill=old;continue;}
   for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(!class_in_area50(g,m,a->x,a->y,28))continue;int dx=abs((int)floorf(m->x/8)-(int)floorf(a->x/8)),dy=abs((int)floorf(m->y/8)-(int)floorf(a->y/8)),chance;if(dx>3||dy>3)continue;
    if(dx<2||dy<2){int outerCell60=dx>dy?dx:dy;chance=36-12*(outerCell60?outerCell60-1:0);}else chance=28-4*dx-4*dy;if(chance<1)chance=1;
    if(class_chance50(g,chance,100))skill_hit(g,i,class_physical50(g,m,100+50*(a->rank-1),0,a->power),0);
   }
  }else{
   a->next=g->time+.1f;int triggered=0;for(int i=0;i<MOB_COUNT;i++)if(class_in_area50(g,&g->mobs[i],a->x,a->y,12)){triggered=1;break;}
   if(triggered){a->until=0;class_fx50(g,a->id,a->rank,a->x,a->y);for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(!class_in_area50(g,m,a->x,a->y,12))continue;
    int damage=class_physical50(g,m,100,0,a->power)+50*a->rank*class_attack_rate48(g,m,0)/100;skill_hit(g,i,damage,0);if(m->hp<=0)continue;float duration=class_duration50(a->id,a->rank,1);
    if(a->power==4)class_stun50(g,m,5,duration);else if(a->power==5)class_poison50(g,m,5,duration);else if(a->power==7&&!combat_status_boss(m)&&class_chance50(g,5,100))m->mobBlind=duration;else if(a->power==1&&!combat_status_boss(m)&&!mobFreezeImmune[m->kind]&&class_chance50(g,5,100)){m->frozenLeft=duration;m->freezeAt=g->time;}else if(a->power==3)combat_knockback(g,i,m->x-a->x,m->y-a->y,24);
   }}
  }
  g->fxSkill=old;
 }
}
