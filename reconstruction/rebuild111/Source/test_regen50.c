/* MIT. Source-derived recovery expectations through the actual combat update. */
#include <assert.h>
#include "combat.h"
#include "travel_status45.h"
static void fresh50(Combat*g,unsigned job){
 combat_init(g,1500,1500,NULL,NULL);g->jobId=job;g->level=99;g->joblevel=50;
 memset(g->mobs,0,sizeof(g->mobs));memset(g->extraItems,0,sizeof(g->extraItems));
 g->jellopy=g->clover=g->apples=0;g->peaceful=1;memset(g->ranks,0,sizeof(g->ranks));
 memset(g->stats,1,sizeof(g->stats));g->stats[2]=40;g->stats[3]=80;stat_refresh(g);
 g->hp=1;g->sp=0;
}
static void wait50(Combat*g,unsigned ms,int move){while(ms){unsigned step=ms>10?10:ms;combat_tick(g,step*.001f,move,0);ms-=step;}}
static int hpAmount50(const Combat*g){return 1+stat_value(g,2)/5+g->maxhp/200;}
static int spAmount50(const Combat*g){int i=stat_value(g,3);return 1+i/6+g->maxsp/100+(i>=120?(i-120)/2+4:0);}
static void buff50(Combat*g,unsigned id){g->class50.until[id-127]=100000;g->class50.level[id-127]=1;}
int main(void){Combat g,h;
 for(unsigned job=0;job<21;job++){
  fresh50(&g,job);int hp=hpAmount50(&g),sp=spAmount50(&g);
  wait50(&g,5999,0);assert(g.hp==1&&g.sp==0);wait50(&g,1,0);assert(g.hp==1+hp&&g.sp==0);
  wait50(&g,1999,0);assert(g.sp==0);wait50(&g,1,0);assert(g.sp==sp);
  fresh50(&g,job);hp=hpAmount50(&g);sp=spAmount50(&g);g.sitting=1;
  wait50(&g,2999,0);assert(g.hp==1&&g.sp==0);wait50(&g,1,0);assert(g.hp==1+hp);
  wait50(&g,999,0);assert(!g.sp);wait50(&g,1,0);assert(g.sp==sp);
 }
 /* Wizard/Mage/Sage/High Wizard and Priest all own Increase SP Recovery. */
 const unsigned spJobs[]={2,8,9,10,17};
 for(unsigned j=0;j<sizeof(spJobs)/sizeof(*spJobs);j++)for(int sitting=0;sitting<2;sitting++){
  fresh50(&g,spJobs[j]);g.ranks[skill_rank_index(25)]=10;g.sitting=sitting;
  int base=spAmount50(&g),skill=30+10*g.maxsp/500;
  wait50(&g,9999,0);assert(g.sp==base*(sitting?2:1));wait50(&g,1,0);assert(g.sp==base*(sitting?2:1)+skill);
 }
 /* Walking keeps natural SP, pauses passive SP; resuming retains its fraction. */
 fresh50(&g,9);g.ranks[skill_rank_index(25)]=10;int base=spAmount50(&g),skill=30+10*g.maxsp/500;
 wait50(&g,7000,0);wait50(&g,8000,1);assert(g.sp==base&&g.recovery50.skillSP==7000);
 wait50(&g,3000,0);assert(g.sp==2*base+skill);
 /* Walking HP requires the quest passive and uses twelve seconds, not six. */
 fresh50(&g,7);g.ranks[skill_rank_index(26)]=10;int hp=hpAmount50(&g);wait50(&g,12000,1);assert(g.hp==1);
 g.ranks[skill_rank_index(44)]=1;wait50(&g,11999,1);assert(g.hp==1);wait50(&g,1,1);assert(g.hp==1+hp&&g.recovery50.skillHP==0);
 wait50(&g,10000,0);assert(g.hp==1+2*hp+50+10*g.maxhp/500);
 /* Damage, stationary attacks and casting do not restart recovery clocks. */
 fresh50(&g,9);g.ranks[skill_rank_index(25)]=10;base=spAmount50(&g);skill=30+10*g.maxsp/500;
 for(int n=0;n<1000;n++){g.autoAttack=1;g.lastDamage=g.lastCast=g.time;g.spellCastLeft=100;g.spellCastId=3;g.spellCastJob=9;g.spellCastMap=g.mapId;g.spellCastRank=1;g.ranks[skill_rank_index(3)]=1;g.spellCastTarget=-1;combat_tick(&g,.01f,0,0);}
 assert(g.sp==base+skill);
 /* Poison/Hiding/Cloaking pause clocks. Death and full resources cannot bank ticks. */
 fresh50(&g,9);wait50(&g,7000,0);g.poisonLeft=100;wait50(&g,10000,0);assert(!g.sp&&g.recovery50.sp==7000);
 buff50(&g,190);wait50(&g,1000,0);assert(g.sp==spAmount50(&g));
 fresh50(&g,9);g.hideLeft=100;g.hideRank=10;g.sp=100;wait50(&g,10000,0);assert(g.sp<=100&&!g.recovery50.sp);
 g.hideLeft=0;g.sp=100;buff50(&g,130);g.class50.level[130-127]=3;wait50(&g,10000,0);assert(g.sp<=100&&!g.recovery50.sp);
 fresh50(&g,9);g.hp=0;wait50(&g,10000,0);assert(!g.sp&&!g.recovery50.sp);
 fresh50(&g,9);g.hp=g.maxhp;g.sp=g.maxsp;wait50(&g,30000,0);assert(!g.recovery50.hp&&!g.recovery50.sp);
 g.hp--;g.sp--;wait50(&g,1000,0);assert(g.hp==g.maxhp-1&&g.sp==g.maxsp-1);
 /* Fifty percent is inclusive. Fractions resume once the load is removed. */
 fresh50(&g,9);wait50(&g,7000,0);int capacity=inventory_weight_max(&g);
 *inventory_stack(&g,ITEM_ARROW)=capacity/2-1;assert(!inventory_overweight(&g,50));
 ++*inventory_stack(&g,ITEM_ARROW);assert(inventory_overweight(&g,50));wait50(&g,10000,0);assert(!g.sp&&g.recovery50.sp==7000);
 *inventory_stack(&g,ITEM_ARROW)=0;wait50(&g,1000,0);assert(g.sp==spAmount50(&g));
 /* INT120 bonus uses total INT including job bonuses and Blessing. */
 fresh50(&g,9);g.stats[3]=99;g.buffs[0]=100;g.buffLevels[0]=20;assert(stat_value(&g,3)>=120);stat_refresh(&g);
 wait50(&g,8000,0);assert(g.sp==spAmount50(&g));
 /* Magnificat doubles only natural SP, including its sitting combination. */
 fresh50(&g,17);g.ranks[skill_rank_index(25)]=10;buff50(&g,192);base=spAmount50(&g);skill=30+10*g.maxsp/500;
 wait50(&g,10000,0);assert(g.sp==2*base+skill);
 fresh50(&g,17);buff50(&g,192);g.sitting=1;base=spAmount50(&g);wait50(&g,2000,0);assert(g.sp==base);
 /* Performing/Maximize/Fury/Asura block natural SP; learned/sitting regen is distinct. */
 for(int mode=0;mode<4;mode++){
  fresh50(&g,mode==0?15:mode==1?19:18);
  g.sp=100;
  if(mode==0){int instrument=-1;for(int i=0;i<ITEM_COUNT;i++)if(itemDefs[i].id==1901)instrument=i;assert(instrument>=0);inventory_add(&g,instrument,1);inventory_action(&g,instrument);g.class50.song=174;g.class50.songRank=5;g.class50.songUntil=100000;g.class50.songDrain=3;g.class50.songNext=3;}
  else {buff50(&g,mode==1?234:mode==2?209:210);g.class50.next[234-127]=1;}
  wait50(&g,8000,0);assert(!g.recovery50.sp&&g.sp<=100&&g.hp>1);

 }
 fresh50(&g,18);g.sitting=1;g.ranks[skill_rank_index(199)]=5;buff50(&g,209);
 int cadence=10+5*g.maxsp/500;wait50(&g,10000,0);assert(g.sp==cadence);
 fresh50(&g,18);g.sitting=1;g.ranks[skill_rank_index(199)]=5;*inventory_stack(&g,ITEM_ARROW)=inventory_weight_max(&g)/2;
 hp=20+5*g.maxhp/500;cadence=10+5*g.maxsp/500;wait50(&g,19999,0);assert(g.hp==1&&!g.sp);wait50(&g,1,0);assert(g.hp==1+hp&&g.sp==cadence);
 /* Zoning preserves fractions; loading does not add elapsed recovery. */
 fresh50(&g,9);wait50(&g,7000,0);TravelStatus45 t=travel_capture45(&g);fresh50(&h,9);travel_restore45(&h,&t);wait50(&h,1000,0);assert(h.sp==spAmount50(&h));
 /* Frame-rate-independent integer clocks, with less than one millisecond remainder. */
 fresh50(&g,9);fresh50(&h,9);for(int n=0;n<960;n++)combat_tick(&g,1.f/60,0,0);wait50(&h,16000,0);
 assert(g.hp==h.hp&&g.sp==h.sp&&g.recovery50.fractionalMS>=0&&g.recovery50.fractionalMS<1);
 puts("PASS50 recovery: all 21 jobs, original 6s/8s formulas, sitting, HP/SP passives, movement, retained clocks, weight, poison/hide/death/full, INT120, Magnificat, Fury/Asura/performances, overweight Spiritual Cadence and zoning.");
}
