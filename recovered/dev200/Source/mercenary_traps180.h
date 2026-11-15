/* MIT. Source mercenary traps share the existing bounded trap renderer/tick. */
static int mercenary_trap_ground180(Combat*g,float*x,float*y){
 Mercenary180*m=&g->mercenary180;float fx=m->faceX,fy=m->faceY;if(fabsf(fx)+fabsf(fy)<.01f)fy=1;
 *x=floorf((m->x+fx*16)/8)*8+4;*y=floorf((m->y+fy*16)/8)*8+4;
 if(class_trap_slot50(g)<0||!class_reachable50(g,m->x,m->y,*x,*y)||(g->canMove&&!g->canMove(g->world,m->x,m->y,*x,*y)))return 0;
 for(unsigned i=0;i<CLASS_TRAPS50;i++){ClassTrap50*t=g->traps50+i;if(t->map==g->mapId&&t->until>g->time&&fabsf(t->x-*x)<12&&fabsf(t->y-*y)<12)return 0;}
 for(unsigned i=0;i<MOB_COUNT;i++)if(class_in_area50(g,g->mobs+i,*x,*y,12))return 0;
 return 1;
}
static int mercenary_trap_place180(Combat*g,unsigned source,unsigned rank){
 float x,y;if(!mercenary_trap_ground180(g,&x,&y))return 0;
 Mercenary180*m=&g->mercenary180;const MercenaryData180*d=mercenary_data180(m->source);const MercenarySkill180*s=mercenarySkills180+source-8201;
 static const unsigned hunter[4]={154,155,158,160};int slot=class_trap_slot50(g);if(!d||slot<0)return 0;
 g->traps50[slot]=(ClassTrap50){.id=hunter[source-8209],.rank=rank,.map=g->mapId,.x=x,.y=y,.until=g->time+s->duration[rank-1]/1000.f,.created=g->time,.mercenary180=m->source,.dex180=d->dex,.int180=d->intel,.atk180=d->atk1+(m->bonusMS[1]?15*m->bonusLevel[1]:0),.originX180=m->x,.originY180=m->y};
 return 1;
}
static void mercenary_trap_trigger180(Combat*g,ClassTrap50*t,int victim){
 if(t->triggered)return;t->triggered=1;t->until=g->time+1.5f;unsigned source=t->id==154?8209:t->id==155?8210:t->id==158?8211:8212,rank=t->rank;
 const MercenarySkill180*s=mercenarySkills180+source-8201;const MercenaryData180*d=mercenary_data180(t->mercenary180);if(!d)return;class_fx50(g,t->id,rank,t->x,t->y);
 CombatMob*hit=g->mobs+victim;
 if(source==8209){if(!combat_status_boss(hit))combat_knockback(g,victim,hit->x-t->originX180,hit->y-t->originY180,s->knockback[rank-1]*8);return;}
 float radius=s->splash[rank-1]*8+4;
 for(int i=0;i<MOB_COUNT;i++){CombatMob*e=g->mobs+i;if(i!=victim&&!class_in_area50(g,e,t->x,t->y,radius))continue;
  if(source==8211){if(!combat_status_boss(e)&&class_chance50(g,(40+10*rank)*(100-mobInt48[e->kind])/100,100))e->class50.sleepUntil=g->time+s->duration2[rank-1]/1000.f;continue;}
  int damage;
  if(source==8210)damage=rank*(t->dex180+75)*(100+t->int180)/100;
  else damage=combat_reduce48((t->atk180+(d->atk2?combat_random(g)%(d->atk2+1):0))*(50+10*rank)/100,combat_enemy_defense(e),mobStunVit[e->kind]);
  damage=damage*class_element_rate48(e,source==8210?2:1)/100;if(damage>0)mercenary_hit180(g,i,damage,1);
  if(e->hp<=0)continue;if(source==8210)class_stun50(g,e,5*rank,5);else skill_freeze164(g,e,100,s->duration2[rank-1]);
 }
}
