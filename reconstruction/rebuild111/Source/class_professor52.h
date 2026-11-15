/* MIT. Source pre-renewal Professor: personal casts and monster interactions. */
static void class_professor_execute52(Combat*g,unsigned id,int rank,int target,float x,float y){
 if(id==SK52_PF_HPCONVERSION){int hp=g->maxhp/10;g->hp-=hp;g->sp+=hp*rank/10;if(g->sp>g->maxsp)g->sp=g->maxsp;return;}
 if(id==SK52_PF_MEMORIZE){g->class50.memorizeCasts52=5;g->class50.level[id-127]=rank;g->class50.until[id-127]=g->time+2147483.f;return;}
 if(id==SK52_PF_DOUBLECASTING){class_buff50(g,id,rank);return;}
 if(id==SK52_PF_FOGWALL){int slot=class_area_slot50(g);if(slot>=0)g->areas50[slot]=(ClassArea50){.id=(int)id,.rank=rank,.map=g->mapId,.x=x,.y=y,.until=g->time+class_duration50(id,rank,0),.created=g->time};return;}
 CombatMob*m=&g->mobs[target];if(!m->class50.initialized){m->class50.initialized=1;m->class50.sp=mobClassData50[m->kind][2];}
 if(id==SK52_PF_SOULCHANGE){m->class50.soulChanged52=1;g->sp+=g->maxsp*3/100;if(g->sp>g->maxsp)g->sp=g->maxsp;return;}
 if(id==SK52_PF_SOULBURN){if(class_chance50(g,rank==5?70:30+10*rank,100)){if(rank==5)skill_magic_hit48(g,target,m->class50.sp*2,0);m->class50.sp=0;}else{if(rank==5){int damage=combat_reduce48(g->sp*2,combat_mdef48(g),combat_mdef_soft48(g));g->hp-=damage<g->hp?damage:g->hp;if(!g->hp){g->deadAt=g->time;g->autoAttack=0;combat_support_clear(g);}}g->sp=0;}return;}
 if(id==SK52_PF_MINDBREAKER){if(!combat_status_boss(m)&&!class_undead50(m)&&m->class50.mindUntil52<=g->time&&class_chance50(g,55+5*rank,100)){m->class50.mindUntil52=g->time+class_duration50(id,rank,0);m->class50.mindRank52=rank;m->castUntil48=0;m->frozenLeft=m->stoneLeft=m->class50.sleepUntil=0;m->aggro=!m->training;}return;}
 if(id==SK52_PF_SPIDERWEB){if(m->class50.webUntil52>g->time)m->class50.webStacks52++;else{m->class50.webUntil52=g->time+class_duration50(id,rank,1);m->class50.webStacks52=1;m->class50.webRoot52=1;}return;}
}
static void class_professor_tick52(Combat*g){
 for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(m->class50.mindUntil52<=g->time)m->class50.mindUntil52=0;if(m->class50.webUntil52<=g->time){m->class50.webUntil52=0;m->class50.webRoot52=m->class50.webStacks52=0;}if(m->enabled&&m->hp>0&&class_fog_at52(g,m->x,m->y)&&!combat_status_boss(m))m->mobBlind=fmaxf(m->mobBlind,30);}
 for(int i=0;i<CLASS_DELAYED52;i++){ClassDelayed52*p=&g->class50.doubleBolt52[i];if(!p->skill)continue;int target=p->target;if(g->hp<=0||p->map!=g->mapId||p->job!=g->jobId||target<0||target>=MOB_COUNT||!g->mobs[target].enabled||g->mobs[target].hp<=0||g->mobs[target].life!=p->life){p->skill=0;continue;}if(g->time<p->at)continue;unsigned id=p->skill;int rank=p->rank;p->skill=0;int old=g->fxSkill;g->fxSkill=id;int power=combat_magic_power48(g),element=id==3?3:id==9?1:4;skill_magic_hit_ex48(g,target,class_multi_element48(g,&g->mobs[target],element,power,rank),0,rank);g->fxSkill=old;}
}
static void class_double_bolt52(Combat*g,unsigned id,int rank,int target){if((id!=3&&id!=9&&id!=21)||target<0||target>=MOB_COUNT)return;int level=class_active50(g,SK52_PF_DOUBLECASTING);if(!level||!class_chance50(g,30+10*level,100))return;for(int i=0;i<CLASS_DELAYED52;i++)if(!g->class50.doubleBolt52[i].skill){g->class50.doubleBolt52[i]=(ClassDelayed52){id,(unsigned)rank,g->mapId,g->jobId,g->mobs[target].life,target,g->time+stat_amotion48(g)*.001f};return;}}
