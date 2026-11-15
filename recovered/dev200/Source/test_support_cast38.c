/* MIT. New five-spell live timing, source interrupt flags and atomic HP/reagent rules. */
#include <assert.h>
#include "save_store.h"
#include "developer.h"
static int clear(void*w,float x,float y,float a,float b){return a>8&&b>8&&a<3192&&b<3192;}
static void fresh(Combat*g,unsigned id){combat_init(g,1500,1500,clear,NULL);dev_class_preset(g,id==56?4:id==59?5:3);memset(g->mobs,0,sizeof(g->mobs));g->peaceful=1;g->sp=g->maxsp=1000;CombatMob*m=&g->mobs[0];m->enabled=m->training=1;m->kind=1;m->hp=m->testMaxHP=10000;m->x=g->x+8;m->y=g->y;g->target=0;}
static void finish(Combat*g){int n=0;while(combat_casting(g)){combat_tick(g,.05f,0,0);assert(++n<100);}}
int main(void){Combat g;unsigned ids[]={6,41,33,59,56};for(unsigned j=0;j<5;j++){unsigned id=ids[j];fresh(&g,id);int sp=g.sp,hp=g.hp,arrows=inventory_count(&g,ITEM_ARROW),stones=inventory_count(&g,ITEM_STONE);char log[100];memcpy(log,g.log,100);assert(skill_cast(&g,id,0,0)&&combat_casting(&g)&&g.sp==sp&&g.hp==hp&&!memcmp(log,g.log,100));assert(fabsf(g.spellCastTotal-skill_cast_seconds(&g,id,skill_rank(&g,id)))<.00001f);finish(&g);assert(g.sp==sp-skill_cost(&g,id));assert(g.hp==hp-(id==6?15:0));if(id==6)assert(g.buffs[1]>0);if(id==33)assert(g.angelusLeft==300);if(id==59)assert(inventory_count(&g,ITEM_ARROW)==arrows-1&&g.mobs[0].hp<10000);if(id==56)assert(inventory_count(&g,ITEM_STONE)==stones+1);
 fresh(&g,id);sp=g.sp;hp=g.hp;assert(skill_cast(&g,id,0,0));combat_ranged_hit(&g,1);if(id==56||id==59){assert(combat_casting(&g)&&!g.spellCastInterruptible);finish(&g);assert(g.sp==sp-skill_cost(&g,id));}else assert(!combat_casting(&g)&&g.sp==sp&&g.hp==hp-1);
 fresh(&g,id);sp=g.sp;assert(skill_cast(&g,id,0,0));combat_tick(&g,.05f,1,0);assert(!combat_casting(&g)&&g.sp==sp);fresh(&g,id);assert(skill_cast(&g,id,0,0));combat_cancel(&g);assert(!combat_casting(&g));}
 fresh(&g,6);g.hp=15;int sp=g.sp;assert(!skill_cast(&g,6,0,0)&&g.sp==sp&&g.hp==15);g.hp=16;assert(skill_cast(&g,6,0,0));finish(&g);assert(g.hp==1&&g.sp==sp-45);fresh(&g,6);assert(skill_cast(&g,6,0,0));g.hp=15;sp=g.sp;finish(&g);assert(g.sp==sp&&g.hp==15&&!g.buffs[1]);
 fresh(&g,59);assert(skill_cast(&g,59,0,0));*inventory_stack(&g,ITEM_ARROW)=0;sp=g.sp;finish(&g);assert(g.sp==sp&&g.mobs[0].hp==10000);
 fresh(&g,56);int stones=inventory_count(&g,ITEM_STONE);assert(skill_cast(&g,56,0,0));g.sp=2;finish(&g);assert(g.sp==2&&inventory_count(&g,ITEM_STONE)==stones);
 puts("PASS38 five source-timed support/quest spells: cast/after-delay, no start popup, HP/SP/ammo/stone completion, source damage-interrupt flags, movement/B cancellation and failure atomicity");
}
