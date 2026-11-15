/* MIT. Personal spheres, original combo windows and pre-renewal Asura. */
static void class_combo50(Combat*g,int id,int target){
 float delay=stat_amotion48(g)*.001f;if(g->castDelay>delay)delay=g->castDelay;delay+=.3f;
 g->class50.comboUntil=g->time+delay;g->class50.comboSkill=id;g->class50.comboTarget=target;g->class50.comboLife=g->mobs[target].life;
 g->moveLock45=delay;g->cooldown=delay;
}
static int class_triple50(Combat*g,int target){
 int rank=job_parent52(g->jobId)==18?class_rank50(g,202):0;if(!rank||skill_burst_slot49(g)<0||!class_chance50(g,30-rank,100))return 0;
 CombatMob*m=&g->mobs[target];class_fx50(g,202,rank,m->x,m->y);skill_hit_ex(g,target,class_physical50(g,m,100+20*rank,0,-1),0,3);
 if(m->hp>0&&class_rank50(g,211))class_combo50(g,202,target);return 1;
}
/* Original Champion additions. Palm Strike is a server-timed attack, whereas
 * Chain Crush's divided damage follows the client's 200ms multihit interval. */
static int class_palm_slot52(const Combat*g){for(int i=0;i<CLASS_DELAYED52;i++)if(!g->class50.delayed52[i].skill)return i;return -1;}
static void class_champion_combo52(Combat*g,unsigned id,int target,int rank){
 const ClassSkill50*d=class_skill_data50(id);int delay=(int)d->delay[rank-1]-4*stat_value(g,1)+2*stat_value(g,4),motion=stat_amotion48(g);
 if(delay<motion)delay=motion;g->castDelay=delay*.001f;
 g->class50.comboUntil=g->time+g->castDelay;g->class50.comboSkill=(int)id;g->class50.comboTarget=target;g->class50.comboLife=g->mobs[target].life;
 g->moveLock45=g->castDelay;g->cooldown=g->castDelay;
}
static void class_champion_execute52(Combat*g,unsigned id,int rank,int target){
 if(id==SK52_CH_SOULCOLLECT){g->class50.spheres=5;for(int i=0;i<5;i++)g->class50.sphereUntil[i]=g->time+class_duration50(id,rank,0);return;}
 if(id==SK52_CH_PALMSTRIKE){int slot=class_palm_slot52(g);if(slot<0)return;g->class50.delayed52[slot]=(ClassDelayed52){id,(unsigned)rank,g->mapId,g->jobId,g->mobs[target].life,target,g->time+1.f+stat_amotion48(g)*.001f};return;}
 CombatMob*m=&g->mobs[target];
 if(id==SK52_CH_TIGERFIST){
  skill_hit(g,target,class_physical50(g,m,40+100*rank,0,-1),0);
  if(m->hp>0&&!combat_status_boss(m)&&class_chance50(g,10+10*rank,100))m->class50.rootUntil=g->time+class_duration50(id,rank,1);
  if(m->hp>0)class_champion_combo52(g,id,target,rank);else g->class50.comboUntil=0;return;
 }
 if(id==SK52_CH_CHAINCRUSH){
  int slot=skill_burst_slot49(g);if(slot<0)return;int hits=(rank+1)/2,damage=combat_hit_bonus50(g,m,class_physical50(g,m,400+100*rank,0,-1));
  if(damage<1)damage=1;if(hits>damage)hits=damage;
  g->bursts49[slot]=(SkillBurst49){.active=1,.target=target,.hits=hits,.damage=damage,.skill=(int)id,.rank=rank,.life=m->life,.map=g->mapId,.job=g->jobId,.next=g->time+stat_amotion48(g)*.001f,.gap=.2f};
  class_champion_combo52(g,id,target,rank);
 }
}
static void class_champion_tick52(Combat*g){
 for(int i=0;i<CLASS_DELAYED52;i++){
  ClassDelayed52*p=g->class50.delayed52+i;if(!p->skill)continue;int target=p->target;
  if(g->hp<=0||p->map!=g->mapId||p->job!=g->jobId||target<0||target>=MOB_COUNT||!g->mobs[target].enabled||g->mobs[target].hp<=0||g->mobs[target].life!=p->life){p->skill=0;continue;}
  if(g->time+.00001f<p->at)continue;unsigned id=p->skill;int rank=(int)p->rank;p->skill=0;CombatMob*m=&g->mobs[target];
  class_fx50(g,id,rank,m->x,m->y);
  if(g->hideLeft<=0&&!m->hidden)skill_hit(g,target,class_physical50(g,m,200+100*rank,0,-1),0);
  if(m->hp>0)combat_knockback(g,target,m->x-g->x,m->y-g->y,24);
 }
}
static void class_monk_execute50(Combat*g,unsigned id,int rank,int target,float x,float y,int spentSpheres){
 if(id==200){if(g->class50.spheres>=rank){for(int i=1;i<g->class50.spheres;i++)g->class50.sphereUntil[i-1]=g->class50.sphereUntil[i];g->class50.spheres--;}
  g->class50.sphereUntil[g->class50.spheres++]=g->time+600;return;
 }
 if(id==201){int gain=0;if(g->class50.spheres){gain=7*g->class50.spheres;g->class50.spheres=0;memset(g->class50.sphereUntil,0,sizeof(g->class50.sphereUntil));}
  else if(target>=0&&!combat_status_boss(&g->mobs[target])&&class_chance50(g,20,100)){gain=2*mobSourceLevel[g->mobs[target].kind];g->mobs[target].aggro=!g->mobs[target].training;}
  g->sp+=gain;if(g->sp>g->maxsp)g->sp=g->maxsp;return;
 }
 if(id==203){g->x=x;g->y=y;g->hitStun=0;g->autoAttack=0;g->skillCD[210-1]=2;return;}
 if(id==207||id==208||id==209){class_buff50(g,id,rank);return;}
 CombatMob*m=&g->mobs[target];
 if(id==205){int vit=mobStunVit[m->kind]*(m->class50.stripUntil[2]>0?60:100)/100;
  int power=class_physical50(g,m,100+75*rank,1,-1)*(combat_enemy_defense(m)+vit)/100;skill_hit(g,target,power<1?1:power,0);return;
 }
 if(id==206){skill_hit_ex(g,target,class_physical50(g,m,100+50*rank,0,-1)*spentSpheres,0,spentSpheres);return;}
 if(id==210){int ratio=100+100*(8+g->sp/10);if(ratio>60000)ratio=60000;
  skill_hit(g,target,class_physical50(g,m,ratio,1,0)+250+150*rank,0);
  g->sp=0;g->class50.until[209-127]=0;g->class50.until[210-127]=g->time+class_duration50(210,rank,1);g->class50.level[210-127]=rank;g->class50.comboUntil=0;
  if(g->class50.rootUntil>g->time){g->class50.rootUntil=0;m->class50.bladeUntil=0;g->moveLock45=0;}return;
 }
 if(id==211||id==212){skill_hit_ex(g,target,class_physical50(g,m,id==211?150+50*rank:240+60*rank,0,-1),0,id==211?4:1);
  if(m->hp>0)class_combo50(g,id,target);return;
 }
 if(id==213){float cx=m->x,cy=m->y;skill_hit(g,target,class_physical50(g,m,300,0,-1),0);
  for(int i=0;i<MOB_COUNT;i++)if(i!=target&&class_in_area50(g,&g->mobs[i],cx,cy,12)){combat_knockback(g,i,g->mobs[i].x-cx,g->mobs[i].y-cy,40);class_stun50(g,&g->mobs[i],70,5);}
 }
}
