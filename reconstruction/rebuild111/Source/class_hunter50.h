/* MIT. Pre-renewal Hunter traps and the personal Falcon. */
static void mercenary_trap_trigger180(Combat*,ClassTrap50*,int);
static int class_falcon_ready50(const Combat*g){return job_parent52(g->jobId)==14&&g->persistent50.falcon&&class_rank50(g,165);}
static void class_blitz50(Combat*g,int target,int rank,int automatic){
 CombatMob*m=&g->mobs[target];int hits=automatic?g->joblevel/10+1:rank;if(hits>rank)hits=rank;if(hits<1)hits=1;
 int count=0;for(int i=0;i<MOB_COUNT;i++)if(class_in_area50(g,&g->mobs[i],m->x,m->y,12))count++;
 int perHit=2*(stat_value(g,4)/10+stat_value(g,3)/2+3*class_rank50(g,166)+40);
 float x=m->x,y=m->y;class_fx50(g,167,rank,x,y);
 for(int i=0;i<MOB_COUNT;i++)if(class_in_area50(g,&g->mobs[i],x,y,12)){int damage=perHit*hits;if(automatic&&count>1)damage/=count;skill_hit_ex(g,i,damage,0,hits);}
}
static void class_trap_trigger50(Combat*g,ClassTrap50*t,int victim){
 if(t->mercenary180){mercenary_trap_trigger180(g,t,victim);return;}
 if(t->triggered)return;int id=t->id,rank=t->rank;t->triggered=1;t->until=g->time+1.5f;
 class_fx50(g,id,rank,t->x,t->y);CombatMob*hit=&g->mobs[victim];
 if(id==154){combat_knockback(g,victim,hit->x-g->x,hit->y-g->y,8*(4+rank));return;}
 if(id==156){float seconds=class_duration50(id,rank,1)/(1+mobSourceAgi[hit->kind]/10);if(combat_status_boss(hit))seconds/=5;if(seconds<3)seconds=3;hit->class50.rootUntil=g->time+seconds;t->until=hit->class50.rootUntil;hit->x=t->x;hit->y=t->y;hit->moving=0;return;}
 if(id==163){combat_notice(g,POP_SPEECH,"Talkie Box");return;}
 float radius=8*(class_skill_data50(id)->splash[rank-1]) +4;
 for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(!class_in_area50(g,m,t->x,t->y,radius))continue;
  if(id==157){if(!m->class50.initialized){m->class50.sp=mobClassData50[m->kind][2];m->class50.initialized=1;}int loss=(int)mobClassData50[m->kind][2]*(10+15*rank)/100;m->class50.sp-=loss;if(m->class50.sp<0)m->class50.sp=0;continue;}
  if(id==158){if(!combat_status_boss(m)&&class_chance50(g,(40+10*rank)*(100-mobInt48[m->kind])/100,100))m->class50.sleepUntil=g->time+class_duration50(id,rank,1);continue;}
  if(id==159){if(!combat_status_boss(m))m->mobBlind=class_duration50(id,rank,1);continue;}
  if(id==160){skill_hit(g,i,class_physical50(g,m,50+10*rank,0,1),0);if(m->hp>0&&!mobFreezeImmune[m->kind]&&class_chance50(g,(100-mobFreezeMdef[m->kind])*100/100,100)){m->freezeAt=g->time;m->frozenLeft=class_duration50(id,rank,1);m->moving=0;}continue;}
  int dex=stat_value(g,4),intel=stat_value(g,3),element=id==155?2:id==161?4:3;
  int damage=rank*(id==155?dex+75:id==161?dex/2+50:dex/2+75)*(100+intel)/100;
  skill_hit(g,i,damage*class_attack_rate48(g,m,element)/100,0);if(id==155&&m->hp>0)class_stun50(g,m,5*rank,5);
 }
}
static void class_traps_tick50(Combat*g){
 for(int n=0;n<CLASS_TRAPS50;n++){ClassTrap50*t=&g->traps50[n];if(t->map!=g->mapId){t->until=0;continue;}if(t->until<=g->time||t->triggered||g->time<t->created+.1f)continue;
  for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(class_in_area50(g,m,t->x,t->y,12)&&!m->hidden){class_trap_trigger50(g,t,i);break;}}
 }
}
static void class_hunter_execute50(Combat*g,unsigned id,int rank,int target,float x,float y){
 if(id>=154&&id<=163){ClassTrap50*t=&g->traps50[class_trap_slot50(g)];*t=(ClassTrap50){.id=id,.rank=rank,.map=g->mapId,.x=x,.y=y,.until=g->time+class_duration50(id,rank,0),.created=g->time};return;}
 if(id==139||id==169){int n=class_nearest_trap50(g,id,rank);if(n<0)return;g->traps50[n].until=0;if(id==139)inventory_add(g,item_source50(1065),1);return;}
 if(id==167){class_blitz50(g,target,rank,0);return;}
 if(id==168){for(int i=0;i<MOB_COUNT;i++)if(g->mobs[i].enabled&&combat_dist(x,y,g->mobs[i].x,g->mobs[i].y)<=28)g->mobs[i].hidden=0;return;}
 if(id==170||id==171){CombatMob*m=&g->mobs[target];skill_hit_ex(g,target,class_physical50(g,m,id==170?150:50+8*stat_value(g,0),0,-1)*(id==171?2:1),0,id==171?2:1);if(id==170)combat_knockback(g,target,m->x-g->x,m->y-g->y,24);}
}
