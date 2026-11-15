/* MIT. Solo poison, positional attacks, stripping and stealing. */
static void class_poison_area50(Combat*g,float x,float y,int rank){for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(class_in_area50(g,m,x,y,12))class_poison50(g,m,100,class_duration50(135,rank,1));}}
static void class_assassin_execute50(Combat*g,unsigned id,int rank,int target,float x,float y){
 if(id==130){if(class_active50(g,id))g->class50.until[id-127]=0;else{g->hideLeft=0;g->class50.level[id-127]=rank;g->class50.until[id-127]=g->time+86400;g->class50.next[id-127]=g->time+class_duration50(id,rank,0);g->autoAttack=0;}return;}
 if(id==133||id==134){class_buff50(g,id,rank);if(id==134)g->class50.next[id-127]=(rank+1)/2+rank/10;return;}
 if(id==135){ClassArea50*a=&g->areas50[class_area_slot50(g)];*a=(ClassArea50){.id=id,.rank=rank,.map=g->mapId,.x=x,.y=y,.until=g->time+class_duration50(id,rank,0),.next=g->time,.created=g->time};return;}
 CombatMob*m=&g->mobs[target];
 if(id==136){m->class50.splasherUntil=g->time+class_duration50(id,rank,0);m->class50.splasherRank=rank;g->skillCD[id-1]=class_duration50(id,rank,0)+3;return;}
 if(id==132){float tx=m->x,ty=m->y;for(int i=0;i<MOB_COUNT;i++)if(class_in_area50(g,&g->mobs[i],tx,ty,12))skill_hit(g,i,class_physical50(g,&g->mobs[i],100+20*rank,0,-1),0);return;}
 if(id==131){int ratio=400+40*rank;if(class_rank50(g,137))ratio=ratio*110/100;skill_hit_ex(g,target,class_physical50(g,m,ratio,0,-1),0,8);if(m->hp>0)class_stun50(g,m,10+2*rank,5);return;}
 if(id==138){skill_hit(g,target,class_physical50(g,m,100,0,-1),0);if(m->hp>0)class_poison50(g,m,50,15);}
}
static void class_rogue_execute50(Combat*g,unsigned id,int rank,int target,float x,float y){
 if(id==150){ClassArea50*a=&g->areas50[class_area_slot50(g)];*a=(ClassArea50){.id=id,.rank=rank,.map=g->mapId,.x=x,.y=y,.until=g->time+class_duration50(id,rank,0),.created=g->time};return;}
 if(id==144){g->hideLeft=0;for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(!class_in_area50(g,m,g->x,g->y,12))continue;skill_hit(g,i,class_physical50(g,m,100+40*rank,0,-1),0);if(m->hp>0){class_stun50(g,m,10+3*rank,5);if(!combat_status_boss(m)&&class_chance50(g,10+3*rank,100))m->mobBlind=30;}}return;}
 CombatMob*m=&g->mobs[target];
 if(id==141){int chance=rank*10+(g->level-mobSourceLevel[m->kind])*2+stat_value(g,4)/2+stat_value(g,5)/2;if(class_chance50(g,chance,1000)){int lv=mobSourceLevel[m->kind],amount=lv*rank/10+lv*8+combat_random(g)%(2*lv+1);if(g->zeny<=1000000000-amount){g->zeny+=amount;m->class50.coinStolen=1;combat_notice(g,POP_LOOT,"Stole %d Zeny.",amount);}}m->aggro=!m->training;return;}
 if(id==142){int ratio=inventory_wtype46(g)==10?100+(200+40*rank)/2:300+40*rank;g->hideLeft=0;skill_hit(g,target,class_physical50(g,m,ratio,0,-1),0);combat_face(&m->faceX,&m->faceY,g->x-m->x,g->y-m->y);return;}
 if(id>=145&&id<=148){int delta=stat_value(g,4)-mobSourceDex[m->kind],chance=5+5*rank+delta/5;if(chance<5)chance=5;if(class_chance50(g,chance,100)){float duration=class_duration50(id,rank,0)+delta*.5f;if(duration<0)duration=0;m->class50.stripUntil[id-145]=g->time+duration;}return;}
 if(id==149){skill_hit(g,target,class_physical50(g,m,100+30*rank,0,-1),0);if(m->hp<=0)return;for(int i=0;i<512;i++){float xx=12+8*(combat_random(g)%(mapWidth43[g->mapId]/8-3)),yy=12+8*(combat_random(g)%(mapHeight43[g->mapId]/8-3));if(!g->canMove||g->canMove(g->world,xx,yy,xx,yy)){g->x=xx;g->y=yy;m->x=xx+8;m->y=yy;if(g->canMove&&!g->canMove(g->world,m->x,m->y,m->x,m->y)){m->x=xx;m->y=yy;}m->aggro=!m->training;break;}}return;}
 if(id==153){m->class50.closeUntil=g->time+10;g->class50.until[id-127]=g->time+10;g->class50.level[id-127]=rank;g->class50.comboTarget=target;}
}
