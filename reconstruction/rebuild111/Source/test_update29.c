/* MIT. Actual controls and normal physical combat; Test29 regressions. */
#include <assert.h>
#include "save_store.h"
#include "developer.h"
#include "window_ui.h"
#include "pause_ui.h"
#include "input_repeat.h"
static void prepare(Combat*g){combat_init(g,1500,1500,NULL,NULL);dev_class_preset(g,4);memset(g->mobs,0,sizeof(g->mobs));g->debugFreeze=1;g->debugImmortal=0;CombatMob*m=&g->mobs[0];m->kind=5;m->training=m->enabled=1;m->hp=m->testMaxHP=1000000;m->x=m->homeX=1508;m->y=m->homeY=1500;m->spawnDef=-1;g->target=0;}
int main(void){Combat g;prepare(&g);assert(g.hotAttack&&hot_binding(&g)==0);for(int bar=0;bar<2;bar++){g.hotSlot=bar*4;g.hotAttack=1;for(int col=0;col<5;col++){assert(hot_column(&g)==(unsigned)col);if(!col)assert(hot_binding(&g)==0);skill_slot(&g,1,0);}assert(g.hotAttack);skill_slot(&g,0,1);assert(g.hotSlot/4==(unsigned)(1-bar)&&hot_binding(&g)==0);}
 for(int i=0;i<8;i++)g.hotbar[i]=255;ui_unbind(&g,0);g.hotAttack=1;assert(hot_binding(&g)==0);g.hotbar[7]=41;g.hotSlot=7;g.hotAttack=0;skill_slot(&g,1,0);assert(g.hotAttack&&g.hotSlot/4==1);skill_slot(&g,-1,0);assert(!g.hotAttack&&g.hotSlot==7);
 prepare(&g);g.buffs[1]=0;float x=g.x;combat_tick(&g,.05f,1,0);assert(fabsf(g.x-x-4.095f)<.001f);g.buffs[1]=120;x=g.x;combat_tick(&g,.05f,1,0);assert(fabsf(g.x-x-5.11875f)<.001f);
 assert(combat_hit_rate(0,200)==5&&combat_hit_rate(200,0)==100&&combat_hit_rate(20,20)==80);g.buffs[1]=0;g.stats[4]=10;g.stats[1]=20;g.ranks[30]=10;assert(combat_hit(&g)==30&&combat_flee(&g)==70);int flee=combat_mob_flee(&g.mobs[0]);g.mobs[0].slowLeft=130;g.mobs[0].slowRank=10;assert(combat_mob_flee(&g.mobs[0])<flee);g.stats[5]=30;assert(combat_target_crit(&g,&g.mobs[0])==110-2*mobStatusLuk[5]);
 prepare(&g);g.stats[4]=1;g.stats[5]=1;g.level=1;int hits=0,misses=0;for(int i=0;i<500;i++){g.target=0;g.autoAttack=1;g.cooldown=0;g.hitStun=0;int hp=g.mobs[0].hp;combat_tick(&g,.05f,0,0);DamageEvent*d=&g.damage[(g.damageNext-1)%DAMAGE_EVENTS];if(d->kind==2){misses++;assert(g.mobs[0].hp==hp);}else{hits++;assert(g.mobs[0].hp<hp);}}assert(hits>200&&misses>100);
 prepare(&g);g.debugFreeze=0;g.stats[1]=30;g.ranks[30]=10;g.autoAttack=0;g.mobs[0].training=0;g.mobs[0].aggro=1;hits=misses=0;for(int i=0;i<500;i++){g.hp=g.maxhp;g.mobs[0].cooldown=0;g.hitStun=0;combat_tick(&g,.05f,0,0);if(g.hp==g.maxhp)misses++;else hits++;}assert(misses>300&&hits>10);
 DeveloperUI dev={.tab=0,.row=6};int pace=g.walkPercent;dev_input(&dev,&g,4096);assert(g.walkPercent==pace-1);dev_input(&dev,&g,2);assert(g.walkPercent==91);
 PauseUI p={.tab=1,.row=3};assert(pause_count(1)==4&&pause_input(&p,2)==PA_SFX_MUTE);
 puts("PASS permanent Basic Attack on both five-slot bars; all8 editable bindings retained; measured81.9/102.375 walking; source HIT/FLEE/slow/crit; real miss leaves HP unchanged; no Test Sound row");}
