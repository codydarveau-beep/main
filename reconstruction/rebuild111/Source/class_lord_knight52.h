/* MIT. Solo pre-renewal Lord Knight buffs and bounded divided physical hits. */
static void class_lord_knight_end52(Combat*g){
 g->class50.until[SK52_LK_BERSERK-127]=0;g->class50.berserkWas52=0;g->endureLeft=0;g->endureHits=0;g->class50.regenBlockedUntil52=g->time+300;stat_refresh(g);if(g->hp>100)g->hp=100;
}
static void class_lord_knight_execute52(Combat*g,unsigned id,int rank,int target){
 if(id==SK52_LK_AURABLADE||id==SK52_LK_PARRYING||id==SK52_LK_CONCENTRATION||id==SK52_LK_TENSIONRELAX||id==SK52_LK_BERSERK){
  class_buff50(g,id,rank);
  if(id==SK52_LK_CONCENTRATION){g->endureLeft=class_duration50(id,rank,0);g->endureHits=7;}
  if(id==SK52_LK_TENSIONRELAX){g->sitting=1;g->autoAttack=0;g->class50.next[id-127]=g->time+10;}
  if(id==SK52_LK_BERSERK){g->class50.berserkWas52=1;g->class50.next[id-127]=g->time+class_duration50(id,rank,1);stat_refresh(g);g->hp=g->maxhp;g->sp=0;g->sitting=0;g->endureLeft=class_duration50(id,rank,0);g->endureHits=1000000;}
  return;
 }
 CombatMob*m=&g->mobs[target];
 if(id==SK52_LK_SPIRALPIERCE){
  int weapon=inventory_slot46(g,0),weight=weapon>=0?itemWeights[weapon]:0,str=stat_value(g,0)/10;int64_t hit=(int64_t)weight*8/100;hit=hit*(100+50*rank)/100+str*str;
  unsigned size=mobClassData50[m->kind][1];hit=hit*(size==0?125:size==2?75:100)/100;hit=hit*class_attack_rate48(g,m,class_weapon_element50(g))/100;if(hit<1)hit=1;if(hit>200000000)hit=200000000;
  int slot=skill_burst_slot49(g);if(slot<0)return;int damage=combat_hit_bonus50(g,m,(int)hit*5);
  g->bursts49[slot]=(SkillBurst49){.active=1,.target=target,.hits=5,.damage=damage,.skill=(int)id,.rank=rank,.life=m->life,.map=g->mapId,.job=g->jobId,.next=g->time+stat_amotion48(g)*.001f,.gap=.2f};
  if(!combat_status_boss(m))m->class50.rootUntil=g->time+class_duration50(id,rank,1);return;
 }
 if(id==SK52_LK_HEADCRUSH){skill_hit(g,target,class_physical50(g,m,100+40*rank,0,-1),0);if(m->hp>0&&!combat_status_boss(m)&&!class_evil50(m)&&class_chance50(g,50,100)){m->class50.bleedUntil=g->time+class_duration50(id,rank,1);m->class50.bleedNext=g->time+10;}return;}
 if(id==SK52_LK_JOINTBEAT){unsigned joint=combat_random(g)%6;int ratio=100+(10*rank-50)*(joint==5?2:1);skill_hit(g,target,class_physical50(g,m,ratio,0,-1),0);
  if(m->hp>0&&!combat_status_boss(m)&&class_chance50(g,5*rank+5,100)){m->class50.jointUntil52[joint]=g->time+class_duration50(id,rank,1);if(joint==5){m->class50.bleedUntil=m->class50.jointUntil52[joint];m->class50.bleedNext=g->time+10;}}
 }
}
static void class_lord_knight_tick52(Combat*g){
 int rank=class_active50(g,SK52_LK_BERSERK);
 if(g->class50.berserkWas52&&!rank){class_lord_knight_end52(g);return;}
 if(rank){float*next=&g->class50.next[SK52_LK_BERSERK-127];while(g->time>=*next){*next+=class_duration50(SK52_LK_BERSERK,rank,1);int loss=g->maxhp/20;if(g->hp-loss<=100){g->hp=100;class_lord_knight_end52(g);break;}g->hp-=loss;}}
 if(class_active50(g,SK52_LK_PARRYING)&&inventory_wtype46(g)!=3)g->class50.until[SK52_LK_PARRYING-127]=0;
 if(class_active50(g,SK52_LK_TENSIONRELAX)){if(!g->sitting||(g->time>=g->class50.next[SK52_LK_TENSIONRELAX-127]&&g->hp>=g->maxhp))g->class50.until[SK52_LK_TENSIONRELAX-127]=0;else if(g->time>=g->class50.next[SK52_LK_TENSIONRELAX-127])g->class50.next[SK52_LK_TENSIONRELAX-127]+=10;}
 for(int i=0;i<MOB_COUNT;i++)for(unsigned j=0;j<6;j++)if(g->mobs[i].class50.jointUntil52[j]<=g->time)g->mobs[i].class50.jointUntil52[j]=0;
}
#include "brandish_cells52.h"
static int class_brandish_cell52(unsigned dir,int tx,int ty,int mx,int my,int rank){
 static const int dx[8]={0,-1,-1,-1,0,1,1,1},dy[8]={1,1,0,-1,-1,-1,0,1};
 for(int row=-1;row<=3;row++){
  unsigned flag=row<=0?1:(unsigned)row+1;if((row==1&&rank<=3)||(row==2&&rank<=6)||(row==3&&rank<=9))continue;
  for(int i=0;i<5;i++){if(row==3&&(i==0||i==4))continue;if(mx==tx+brandishCells52[dir][i][0]+dx[dir]*(row+1)&&my==ty+brandishCells52[dir][i][1]+dy[dir]*(row+1))return (int)flag;}
 }return 0;
}
static void class_knight_spear52(Combat*g,unsigned id,int rank,int target){
 CombatMob*m=&g->mobs[target];
 if(id==SK52_KN_PIERCE){unsigned size=mobClassData50[m->kind][1];int hits=size<3?size+1:2,damage=class_physical50(g,m,100+10*rank,0,-1)*hits;skill_hit_ex(g,target,damage,0,hits);return;}
 if(id==SK52_KN_SPEARBOOMERANG){skill_hit(g,target,class_physical50(g,m,100+50*rank,0,-1),0);return;}
 int tx=(int)floorf(m->x/8),ty=(int)floorf(m->y/8),sx=(int)floorf(g->x/8),sy=(int)floorf(g->y/8);unsigned dir=((int)floorf(atan2f((float)(sx-tx),(float)(ty-sy))/.7853981634f+.5f)+8)%8;
 if(id==SK52_KN_SPEARSTAB){
  static const int dx[8]={0,-1,-1,-1,0,1,1,1},dy[8]={1,1,0,-1,-1,-1,0,1};
  for(int i=0;i<MOB_COUNT;i++){CombatMob*t=&g->mobs[i];if(!t->enabled||t->hp<=0)continue;int mx=(int)floorf(t->x/8),my=(int)floorf(t->y/8),inside=i==target;for(int n=0;n<4;n++)if(mx==tx-dx[dir]*n&&my==ty-dy[dir]*n)inside=1;if(!inside||!class_reachable50(g,g->x,g->y,t->x,t->y))continue;skill_hit(g,i,class_physical50(g,t,100+20*rank,0,-1),0);if(t->hp>0)combat_knockback(g,i,t->x-g->x,t->y-g->y,48);}
  return;
 }
 for(int i=0;i<MOB_COUNT;i++){CombatMob*t=&g->mobs[i];if(!t->enabled||t->hp<=0||!class_reachable50(g,g->x,g->y,t->x,t->y))continue;int flag=class_brandish_cell52(dir,tx,ty,(int)floorf(t->x/8),(int)floorf(t->y/8),rank);if(!flag)continue;int base=100+20*rank,ratio=base;if(flag==1){if(rank>3)ratio+=base/2;if(rank>6)ratio+=base/4;if(rank>9)ratio+=base/8;}if(flag==2){if(rank>6)ratio+=base/2;if(rank>9)ratio+=base/4;}if(flag==3&&rank>9)ratio+=base/2;skill_hit(g,i,class_physical50(g,t,ratio,0,-1),0);if(t->hp>0)combat_knockback(g,i,t->x-g->x,t->y-g->y,24);}
}
