#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "save_store.h"
#include "window_ui.h"
static void ready(Combat*g){g->sp=g->maxsp;g->castDelay=0;memset(g->skillCD,0,sizeof(g->skillCD));g->sitting=0;}
static void trained(Combat*g){g->joblevel=20;g->skillPoints=19;g->jexp=0;}
int main(void){
 Combat g,h;combat_init(&g,1500,1500,NULL,NULL);g.level=10;g.joblevel=10;g.statPoints=stat_budget(10);g.stats[3]=10;g.statPoints-=stat_spent(g.stats);stat_refresh(&g);g.equipment=1;
 assert(combat_change_job(&g,3)&&!(g.equipment&1)&&g.extraItems[1]==1);trained(&g);assert(!skill_learn(&g,5)&&!skill_learn(&g,6));
 for(int i=0;i<3;i++)assert(skill_learn(&g,10));for(int i=0;i<5;i++)assert(skill_learn(&g,11));assert(skill_learn(&g,5)&&skill_learn(&g,5)&&skill_learn(&g,6));assert(g.skillPoints==8);
 assert(!quick_bind(&g,1,11)&&!skill_assign(&g,0,11));inventory_action(&g,4);assert(!(g.equipment&1));assert(divine_reduction(&g,6)==15&&divine_reduction(&g,1)==15&&!divine_reduction(&g,2));
 ready(&g);g.hp=g.maxhp/2;int hp=g.hp,sp=g.sp;assert(skill_cast(&g,10,0,0)&&g.hp>hp&&g.sp==sp-19);ready(&g);g.hp=g.maxhp;sp=g.sp;assert(!skill_cast(&g,10,0,0)&&g.sp==sp);
 ready(&g);assert(skill_cast(&g,5,0,0)&&stat_value(&g,0)==3);ready(&g);assert(skill_cast(&g,6,0,0)&&stat_value(&g,1)==4);
 assert(bar_bind_item(&g,0,0)&&g.hotbar[0]==128);assert(quick_bind(&g,1,10));SavedCharacter c;save_capture(&c,&g,12);assert(save_valid(&c));unsigned char raw[SAVE_BYTES];save_encode(raw,&c);assert(save_decode(&c,raw)==1);save_restore(&h,&c,1500,1500,NULL,NULL);assert(h.jobId==3&&h.ranks[4]==3&&h.ranks[5]==5&&h.ranks[7]==1&&h.quickId==10&&h.hotbar[0]==128);
 assert(combat_change_job(&g,4)&&g.hotbar[0]==128&&g.quickKind==0);trained(&g);assert(!skill_learn(&g,14));for(int i=0;i<10;i++)assert(skill_learn(&g,12));for(int i=0;i<3;i++)assert(skill_learn(&g,13));assert(skill_learn(&g,14)&&!skill_learn(&g,14));assert(g.skillPoints==5);
 for(int i=0;i<MOB_COUNT;i++)g.mobs[i].enabled=0;CombatMob*m=&g.mobs[0];memset(m,0,sizeof(*m));m->enabled=1;m->kind=2;m->hp=427;m->x=m->homeX=g.x+8;m->y=m->homeY=g.y;m->spawnDef=-1;g.target=0;ready(&g);assert(skill_cast(&g,13,0,0)&&m->poisonLeft==25);hp=m->hp;for(int i=0;i<42;i++)combat_tick(&g,.05f,0,0);assert(m->hp<hp&&m->hp>=mobSpecs[2].hp/4);
 ready(&g);g.poisonLeft=30;assert(skill_cast(&g,14,0,0)&&g.poisonLeft==0);ready(&g);sp=g.sp;assert(!skill_cast(&g,14,0,0)&&g.sp==sp);
 m->kind=9;m->hp=344;m->poisonLeft=0;ready(&g);assert(skill_cast(&g,13,0,0)&&m->poisonLeft==0);
 g.peaceful=1;g.equipment=1;m->kind=2;m->poisonLeft=0;int doubles=0;for(int i=0;i<1000;i++){m->hp=100000;g.autoAttack=1;g.target=0;g.cooldown=0;combat_tick(&g,.05f,0,0);if(!strncmp(g.log,"Double Attack",13))doubles++;}assert(doubles>300&&doubles<700);g.equipment=0;for(int i=0;i<20;i++){m->hp=100000;g.autoAttack=1;g.cooldown=0;combat_tick(&g,.05f,0,0);assert(strncmp(g.log,"Double Attack",13));}
 WindowUI u={.active=1,.inside=1,.focus=5,.open=15};u.choice[1]=0;int stock=g.apples;ui_input(&u,&g,2);assert(g.hotbar[0]==128&&g.apples==stock);ui_input(&u,&g,16);assert(u.assignBank==1&&g.hotSlot==4);u.choice[1]=3;ui_input(&u,&g,2);assert(g.hotbar[4]==131);ui_input(&u,&g,16);assert(u.assignBank==2);ui_input(&u,&g,2);assert(g.quickKind==0&&g.quickId==3);ui_input(&u,&g,16);assert(u.assignBank==0&&g.hotSlot==0);
 u.focus=7;u.skillPage=0;u.choice[3]=4;ui_input(&u,&g,16);ui_input(&u,&g,16);assert(u.assignBank==2);ui_input(&u,&g,2);assert(g.quickKind==1&&g.quickId==4);ui_input(&u,&g,16);ui_input(&u,&g,2);assert(g.hotbar[0]==4);
 u.focus=5;u.choice[1]=0;g.hp=10;stock=g.apples;ui_input(&u,&g,8);assert(g.apples==stock-1&&g.hp>10);
 save_capture(&c,&g,13);assert(save_valid(&c));save_encode(raw,&c);assert(save_decode(&c,raw)==1);save_restore(&h,&c,1500,1500,NULL,NULL);assert(h.jobId==4&&h.ranks[8]==10&&h.ranks[9]==3&&h.ranks[10]==1&&h.hotbar[4]==131);
 u.focus=7;u.skillPage=1;u.choice[3]=7;ui_input(&u,&g,2);assert(u.choice[3]==0);assert(class_skill(&g,7)==12);
 puts("PASS Acolyte/Thief growth/job restrictions, prereqs/passives/heal/buffs/poison/Detox, dagger-only Double Attack, unified Y/A item+skill assignment, Save09 rank/mixed-slot round-trips");
}
