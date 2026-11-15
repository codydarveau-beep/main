/* GPL-3.0-or-later. Solo Taekwon stances and original combo conditions. */
static int taekwon_kick60(unsigned id){return id==SK60_TK_STORMKICK||id==SK60_TK_DOWNKICK||id==SK60_TK_TURNKICK||id==SK60_TK_COUNTER;}
static int taekwon_stance60(unsigned id){return id==SK60_TK_READYSTORM||id==SK60_TK_READYDOWN||id==SK60_TK_READYTURN||id==SK60_TK_READYCOUNTER||id==SK60_TK_DODGE;}
static int taekwon_ready60(Combat*g,unsigned id,int target){
 if(g->jobId==J60_SOUL_LINKER&&(taekwon_kick60(id)||taekwon_stance60(id)&&id!=SK60_TK_DODGE||id==SK60_TK_JUMPKICK)){combat_notice(g,POP_SKILLS,"Soul Linkers cannot use kick techniques; resources kept.");return 0;}
 if(id==SK60_TK_MISSION&&g->jobId!=J60_TAEKWON){combat_notice(g,POP_SKILLS,"Taekwon Mission is for Taekwon characters.");return 0;}
 if(taekwon_kick60(id)&&(g->class50.tkComboUntil60<=g->time||g->class50.tkComboSkill60!=id||g->class50.tkComboTarget60<0||g->class50.tkComboTarget60>=MOB_COUNT||g->mobs[g->class50.tkComboTarget60].life!=g->class50.tkComboLife60)){combat_notice(g,POP_SKILLS,"Wait for this kick's stance to trigger.");return 0;}
 if(taekwon_kick60(id)&&id!=SK60_TK_STORMKICK&&target!=g->class50.tkComboTarget60){combat_notice(g,POP_SKILLS,"Use the kick against the same target.");return 0;}
 return 1;
}
static void taekwon_after_attack60(Combat*g,int target){
 if(g->jobId!=J60_TAEKWON&&g->jobId!=J60_STAR_GLADIATOR)return;if(g->class50.tkComboUntil60>g->time)return;
 static const unsigned stance[]={SK60_TK_READYSTORM,SK60_TK_READYDOWN,SK60_TK_READYTURN,SK60_TK_READYCOUNTER};
 for(int i=0;i<4;i++)if(class_active50(g,stance[i])&&class_chance50(g,i==3?20:15,100)){
  float window=(2000-4*stat_value(g,1)-2*stat_value(g,4))*.001f;if(window<.1f)window=.1f;
  g->class50.tkComboUntil60=g->time+window;g->class50.tkComboSkill60=stance[i]+1;g->class50.tkComboTarget60=target;g->class50.tkComboLife60=g->mobs[target].life;
  combat_notice(g,POP_SKILLS,"%s ready",skillDefs[stance[i]+1].name);break;
 }
}
static int taekwon_received60(Combat*g,int mob,int damage,int ranged){
 if(damage<=0||!class_active50(g,SK60_TK_DODGE)||(!ranged&&g->class50.spurtUntil60<=g->time)||!class_chance50(g,20,100))return damage;
 if(mob>=0&&mob<MOB_COUNT&&class_rank50(g,SK60_TK_JUMPKICK)&&g->class50.tkComboUntil60<=g->time){g->class50.tkComboUntil60=g->time+2;g->class50.tkComboSkill60=SK60_TK_JUMPKICK;g->class50.tkComboTarget60=mob;g->class50.tkComboLife60=g->mobs[mob].life;}
 combat_guard_number53(g);return 0;
}
static void taekwon_execute60(Combat*g,unsigned id,int rank,int target,float x,float y){
 (void)x;(void)y;
 if(taekwon_stance60(id)){if(class_active50(g,id))g->class50.until[id-127]=0;else{g->class50.level[id-127]=rank;g->class50.until[id-127]=g->time+86400;}return;}
 if(id==SK60_TK_SEVENWIND){class_buff50(g,id,rank);return;}
 if(id==SK60_TK_MISSION){ExpandedState60*s=&g->expanded60;if(!s->missionSource||(!s->missionCount&&class_chance50(g,1,100)))s->missionSource=taekwon_mission_pick60(g,1);int kind=expanded_mob_kind60(s->missionSource);combat_notice(g,POP_SKILLS,"Mission: %s %u/100 (%u completed)",kind>=0?mobSpecs[kind].name:"Poring",s->missionCount,s->missionScore);return;}
 int ratio=(id==SK60_TK_STORMKICK||id==SK60_TK_DOWNKICK)?160+20*rank:190+30*rank;
 if(id==SK60_TK_JUMPKICK){if(target<0||target>=MOB_COUNT)return;ratio=30+10*rank;int run=class_active50(g,SK60_TK_RUN);if(run||(g->class50.tkComboUntil60>g->time&&g->class50.tkComboSkill60==id))ratio+=10*g->level/3;if(run&&g->class50.spurtUntil60>g->time)ratio*=2;ninja_near_target60(g,&g->mobs[target]);g->class50.until[SK60_TK_RUN-127]=0;}
 g->class50.tkComboUntil60=0;
 if(id==SK60_TK_STORMKICK){float radius=class_skill_data50(id)->splash[rank-1]*8+4;for(int i=0;i<MOB_COUNT;i++)if(class_in_area50(g,&g->mobs[i],g->x,g->y,radius))skill_hit(g,i,class_physical50(g,&g->mobs[i],ratio,0,-1),0);return;}
 if(target<0||target>=MOB_COUNT)return;CombatMob*m=&g->mobs[target];float tx=m->x,ty=m->y;skill_hit(g,target,class_physical50(g,m,ratio,0,-1),0);
 if(id==SK60_TK_DOWNKICK&&m->hp>0)class_stun50(g,m,100,class_duration50(id,rank,1));
 if(id==SK60_TK_TURNKICK){float radius=class_skill_data50(id)->splash[rank-1]*8+4;for(int i=0;i<MOB_COUNT;i++)if(i!=target&&class_in_area50(g,&g->mobs[i],tx,ty,radius)){skill_hit(g,i,class_physical50(g,&g->mobs[i],ratio,0,-1),0);if(g->mobs[i].hp>0)combat_knockback(g,i,g->mobs[i].x-tx,g->mobs[i].y-ty,8*class_skill_data50(id)->knockback[rank-1]);}}
}
