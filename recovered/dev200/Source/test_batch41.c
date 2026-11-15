/* MIT. Actual movement/cast/controller paths, not just UI timer arithmetic. */
#include <assert.h>
#include "save_store.h"
#include "developer.h"
#include "window_ui.h"
#include "shop.h"
#include "merchant_services.h"
static int clear(void*w,float x,float y,float nx,float ny){return nx>8&&ny>8&&nx<3192&&ny<3192;}
static void fresh(Combat*g,int job){combat_init(g,1500,1500,clear,NULL);if(job)dev_class_preset(g,job);memset(g->mobs,0,sizeof(g->mobs));g->mapId=2;if(job==2){g->stats[4]=1;g->statPoints=stat_budget(g->level)-stat_spent(g->stats);}}
static void waitcast(Combat*g,int ticks){for(int i=0;i<ticks;i++)combat_tick(g,.05f,0,0);}
int main(void){Combat g;fresh(&g,0);float base=76.5f*.84f;assert(fabsf(combat_walk_speed(&g)-base)<.001);for(int i=0;i<200;i++)combat_tick(&g,.05f,1,0);assert(fabsf(g.x-1500-base*10)<.3f);g.buffs[1]=100;assert(fabsf(combat_walk_speed(&g)-base*1.25f)<.001);fresh(&g,6);g.cartOwned=1;g.ranks[59]=1;assert(fabsf(combat_walk_speed(&g)-base*100/145)<.001);g.ranks[59]=10;assert(fabsf(combat_walk_speed(&g)-base)<.001);
 fresh(&g,0);CombatMob*m=&g.mobs[0];m->enabled=m->training=1;m->hp=m->testMaxHP=1000;m->kind=1;m->x=1600;m->y=1500;g.autoAttack=1;g.target=0;combat_tick(&g,.05f,0,0);assert(fabsf(g.x-1500-base*.05f)<.001);
 hotbarStarted=0;hotbar_motion(0,0);hotbar_motion(1,.05f);assert(fabsf(hotbar_front(1)-.5f)<.001);hotbar_motion(1,.05f);assert(hotbar_front(1)>.999f);hotbar_motion(0,.025f);hotbar_motion(1,.025f);assert(hotbar_front(1)>.999f);
 WindowUI u={0};ui_open(&u,UI_ITEMS,1);ui_input(&u,&g,2048);ui_input(&u,&g,2048);assert(u.choice[1]==8&&u.itemScroll==0);ui_input(&u,&g,2048);assert(u.choice[1]==12&&u.itemScroll==1);ui_input(&u,&g,2048);assert(u.choice[1]==16&&u.itemScroll==2);ui_input(&u,&g,1024);assert(u.choice[1]==12&&u.itemScroll==2);ui_input(&u,&g,1024);assert(u.choice[1]==8&&u.itemScroll==2);ui_input(&u,&g,1024);assert(u.choice[1]==4&&u.itemScroll==1);ui_input(&u,&g,1024);assert(u.choice[1]==0&&u.itemScroll==0);ui_input(&u,&g,4096);assert(u.choice[1]==17&&u.itemScroll==2);ui_input(&u,&g,8192);assert(u.choice[1]==0&&u.itemScroll==0);
 /* Cast pays only at successful completion, with no natural SP regen while pending. */
 fresh(&g,2);int sp=g.sp;assert(skill_cast(&g,67,0,0)&&fabsf(g.coatCastLeft-skill_cast_seconds(&g,67,1))<.0001f&&g.sp==sp&&!g.energyCoatLeft&&g.lastCast<0&&g.fxAt<0);waitcast(&g,99);assert(g.coatCastLeft>0&&g.sp==sp&&!g.energyCoatLeft);waitcast(&g,1);assert(!g.coatCastLeft&&g.sp==sp-30&&g.energyCoatLeft==300);
 fresh(&g,2);g.sp-=10;sp=g.sp;assert(skill_cast(&g,67,0,0));waitcast(&g,99);assert(g.sp==sp);waitcast(&g,1);assert(g.sp==sp-30);
 fresh(&g,2);sp=g.sp;assert(skill_cast(&g,67,0,0));assert(!skill_cast(&g,3,g.x,g.y));combat_attack(&g);assert(!g.autoAttack&&g.coatCastLeft>0);combat_cancel(&g);assert(!g.coatCastLeft&&!g.energyCoatLeft&&g.sp==sp);
 fresh(&g,2);sp=g.sp;assert(skill_cast(&g,67,0,0));float x=g.x;combat_tick(&g,.05f,1,0);assert(!g.coatCastLeft&&!g.energyCoatLeft&&g.sp==sp&&g.x>x);
 fresh(&g,2);sp=g.sp;assert(skill_cast(&g,67,0,0));assert(combat_ranged_hit(&g,10)==10);assert(!g.coatCastLeft&&g.sp==sp);
 fresh(&g,2);sp=g.sp;assert(skill_cast(&g,67,0,0));g.pneuma[0]=(PneumaField){g.x,g.y,10};assert(!combat_ranged_hit(&g,10)&&g.coatCastLeft>0);waitcast(&g,100);assert(g.energyCoatLeft>0&&g.sp==sp-30);
 fresh(&g,2);sp=g.sp;assert(skill_cast(&g,67,0,0));m=&g.mobs[0];m->enabled=m->aggro=1;m->kind=1;m->hp=1000;m->x=m->homeX=g.x+8;m->y=m->homeY=g.y;int hp=g.hp;for(int i=0;i<20&&g.coatCastLeft>0;i++)combat_tick(&g,.05f,0,0);assert(g.hp<hp&&!g.coatCastLeft&&g.sp==sp);
 fresh(&g,2);sp=g.sp;assert(skill_cast(&g,67,0,0));m=&g.mobs[0];m->enabled=m->aggro=1;m->kind=1;m->hp=1000;m->x=m->homeX=g.x+8;m->y=m->homeY=g.y;g.safety[0]=(SafetyWall){g.x,g.y,10,0,11};waitcast(&g,100);assert(g.safety[0].hits<11&&g.energyCoatLeft>0&&g.sp==sp-30);
 fresh(&g,2);assert(skill_cast(&g,67,0,0));g.sp=29;waitcast(&g,100);assert(!g.coatCastLeft&&!g.energyCoatLeft&&g.sp==29);
 fresh(&g,2);sp=g.sp;assert(skill_cast(&g,67,0,0));g.silenceLeft=2;waitcast(&g,1);assert(!g.coatCastLeft&&g.sp==sp);
 fresh(&g,2);sp=g.sp;assert(skill_cast(&g,67,0,0));*inventory_stack(&g,ITEM_ARROW)=inventory_weight_max(&g);waitcast(&g,1);assert(!g.coatCastLeft&&g.sp==sp);
 fresh(&g,2);assert(skill_cast(&g,67,0,0));SavedCharacter a,b;unsigned char bytes[SAVE_BYTES];save_capture(&a,&g,1);assert(save_valid(&a));save_encode(bytes,&a);assert(save_decode(&b,bytes)==1);Combat h;save_restore(&h,&b,1500,1500,clear,NULL);assert(!h.coatCastLeft&&!h.energyCoatLeft&&h.sp==g.sp);
 puts("PASS37:15% manual/chase/buff/cart speed,0.10s flip/reversal, row-scroll navigation,DEX-adjusted cast/payment/regen, B/movement/landed-hit/condition interruptions, blocked hits and transient Save20 cast state");
}
