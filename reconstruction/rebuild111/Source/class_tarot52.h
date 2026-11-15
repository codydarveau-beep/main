/* MIT. Source14-card solo Tarot outcomes; Fortune is expanded without recursion. */
static void class_tarot_execute52(Combat*g,int rank,int target){
 if(!class_chance50(g,rank*8+1,100)){g->sp+=skill_cost(g,SK52_CG_TAROTCARD);return;}
 CombatMob*m=&g->mobs[target];int pending=1,fortuneExpanded=0;for(int draw=0;draw<16&&pending>0&&m->hp>0;draw++){
  int card=combat_random(g)%14;pending--;m->class50.tarotVisual52=card+1;m->class50.tarotVisualSelf52=card==5;m->class50.tarotVisualAt52=g->time;class_sound_emit50(g,SK52_CG_TAROTCARD);float until=g->time+class_duration50(SK52_CG_TAROTCARD,rank,1);int boss=combat_status_boss(m);
  switch(card){
   case 0:if(!m->class50.initialized)m->class50.initialized=1;m->class50.sp=0;break;
   case 1:if(!boss){m->class50.tarotUntil52=until;m->class50.tarotMatk52=-50;}break;
   case 2:m->provokeLeft=0;m->provokeRank=0;m->element48=0;break;
   case 3:skill_hit_now49(g,target,1000,0,1);if(!boss)m->class50.stripUntil[1+combat_random(g)%3]=until;break;
   case 4:if(!boss){m->class50.tarotUntil52=until;m->class50.tarotAtk52=-50;}break;
   case 5:g->hp+=2000;if(g->hp>g->maxhp)g->hp=g->maxhp;for(int n=0;n<128;n++){float x=12+8*(combat_random(g)%(mapWidth43[g->mapId]/8-3)),y=12+8*(combat_random(g)%(mapHeight43[g->mapId]/8-3));if(!g->canMove||g->canMove(g->world,x,y,x,y)){m->x=x;m->y=y;break;}}break;
   case 6:pending+=fortuneExpanded?1:2;fortuneExpanded=1;break;
   case 7:if(!boss){int status=combat_random(g)%3;if(!status)m->class50.rootUntil=until;else if(status==1){m->frozenLeft=until-g->time;m->freezeAt=g->time;}else m->stoneLeft=until-g->time;}break;
   case 8:if(!boss){m->hp=1;m->class50.sp=0;m->class50.curseUntil52=until;class_poison50(g,m,100,until-g->time);}break;
   case 9:if(!boss)m->class50.confuseUntil=until;break;
   case 10:skill_hit_now49(g,target,6666,0,1);if(!boss){m->class50.tarotUntil52=until;m->class50.tarotAtk52=m->class50.tarotMatk52=-50;if(class_chance50(g,rank,100))m->class50.curseUntil52=until;}break;
   case 11:skill_hit_now49(g,target,4444,0,1);break;
   case 12:if(!boss)m->stun=5;break;
   case 13:if(!boss){m->class50.tarotUntil52=until;m->class50.tarotAtk52=m->class50.tarotMatk52=m->class50.tarotHit52=m->class50.tarotFlee52=m->class50.tarotDef52=-20;}break;
  }
 }
}
