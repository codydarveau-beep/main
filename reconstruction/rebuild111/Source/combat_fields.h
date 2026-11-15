/* MIT. Fixed-capacity transient ground effects. Never stored in character saves. */
static int combat_field_slot(const Combat*g){for(int i=0;i<COMBAT_FIELDS;i++)if(!g->fields[i].remaining&&g->time>=g->fields[i].fadeUntil)return i;return -1;}
static void combat_field_total(Combat*g,CombatField*f,int i){
 if(f->expected>1&&f->hits[i]){combat_combo(g,&f->totalEvent[i],f->lastX[i],f->lastY[i],f->total[i]);if(f->totalEvent[i])combat_enemy_tag180(g,g->mobs+i,&g->damage[(f->totalEvent[i]-1)%DAMAGE_EVENTS]);}
}
static void combat_fields_tick(Combat*g){
 if(g->hp<=0){memset(g->fields,0,sizeof(g->fields));return;}
 for(int fno=0;fno<COMBAT_FIELDS;fno++){CombatField*f=&g->fields[fno];if(!f->remaining||g->time+.0001f<f->nextAt)continue;
  if(f->secondId==73&&!f->triggered45){if(g->time-f->createdAt45>=30){f->remaining=0;continue;}int close=0;for(int i=0;i<MOB_COUNT;i++)if(g->mobs[i].enabled&&g->mobs[i].hp>0&&combat_dist(g->mobs[i].x,g->mobs[i].y,f->x,f->y)<=f->radius){close=1;break;}if(!close){f->nextAt=g->time+.1f;continue;}f->triggered45=1;f->triggeredAt45=g->time;}

  int hitAny180=0;int meteor=f->expected-f->remaining;float hitX=f->secondId==75?f->meteorX49[meteor]:f->x,hitY=f->secondId==75?f->meteorY49[meteor]:f->y,hitRadius=f->secondId==75?28:f->radius;
  for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(!m->enabled||m->hp<=0||class_field_at48(g,104,m->x,m->y)||fabsf(m->x-hitX)>(hitRadius>0?hitRadius:20)||fabsf(m->y-hitY)>(hitRadius>0?hitRadius:20)||(g->canAim&&!g->canAim(g->world,hitX,hitY,m->x,m->y)))continue;
   if(f->secondId==80&&(m->frozenLeft>0||g->time+.0001f<m->gustNext164))continue;
   if(f->secondId==77&&g->time+.0001f<m->vermNext164)continue;
   if(f->secondId==82){if(!combat_status_boss(m)){m->slowLeft=2;m->slowRank=f->rank;}continue;}int rate=class_attack_rate48(g,m,4),damage=f->power*rate/100;if(f->secondId==73||f->secondId==75)damage=f->power*class_attack_rate48(g,m,3)/100;if(f->secondId==80)damage=f->power*class_attack_rate48(g,m,1)/100;if(damage<=0)continue;if(mobSpecs[m->kind].flags&16)damage=1;
   damage=combat_magic_def48(m,damage,1);if(damage>0)hitAny180=1;f->total[i]+=damage;f->hits[i]++;f->lastX[i]=m->x;f->lastY[i]=m->y;int oldSkill=g->fxSkill,oldRank=g->fxRank48;g->fxSkill=f->secondId?f->secondId:30;g->fxRank48=f->rank;if(f->secondId==75)skill_hit_ex(g,i,damage*((f->rank+1)/2),0,(f->rank+1)/2);else if(f->secondId==77){damage=combat_hit_bonus50(g,m,damage);skill_hit_now49(g,i,damage,0,10);g->damage[(g->damageNext-1)%DAMAGE_EVENTS].hitGap=.1f;skill_stagger49(g,m);if(m->hp>0&&!combat_status_boss(m)&&m->hitLockUntil49<g->time+.9f)m->hitLockUntil49=g->time+.9f;m->vermNext164=g->time+1.25f;}else skill_hit(g,i,damage,0);g->fxSkill=oldSkill;g->fxRank48=oldRank;skill_wizard_status164(g,m,f->secondId,f->rank);if(f->secondId==80){m->gustNext164=g->time+.45f;unsigned direction=combat_random(g)%8;static const float dx[8]={1,1,0,-1,-1,-1,0,1},dy[8]={0,1,1,1,0,-1,-1,-1};combat_knockback(g,i,dx[direction],dy[direction],16);}if(f->secondId!=75&&f->secondId!=77)combat_field_total(g,f,i);
  }
  if(f->secondId==80){if(hitAny180)combat_hit_sound(g,1);}else if(f->secondId!=77)skill_sound49(g,f->secondId);f->remaining--;f->nextAt+=f->secondId==75?1.f:f->secondId==77?1.25f:f->secondId==80?.45f:f->secondId==73?.2f:f->secondId==82?.5f:1.f;f->fadeUntil=f->secondId==75?f->createdAt45+f->expected+.6f:g->time+.2f;

 }
}
static void combat_field_start(Combat*g,float x,float y,int rank,int power){int k=combat_field_slot(g);if(k<0)return;CombatField*f=&g->fields[k];memset(f,0,sizeof(*f));f->x=x;f->y=y;f->remaining=f->expected=rank;f->power=power;f->nextAt=g->time;combat_fields_tick(g);}
