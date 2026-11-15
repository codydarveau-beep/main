/* MIT. Host simulation checks; does not claim Xbox runtime verification. */
#include <assert.h>
#include "combat.h"
static int openworld(void*w,float x,float y,float nx,float ny){(void)w;(void)x;(void)y;return nx>-1000&&ny>-1000&&nx<1000&&ny<1000;}
static int wall(void*w,float x,float y,float nx,float ny){(void)w;(void)x;(void)y;(void)nx;(void)ny;return 0;}
static void one(Combat*g){combat_init(g,0,0,openworld,NULL);for(int i=1;i<MOB_COUNT;i++){g->mobs[i].hp=0;g->mobs[i].deadAt=10000;}g->mobs[0].x=12;g->mobs[0].y=0;g->mobs[0].homeX=12;g->mobs[0].homeY=0;g->mobs[0].wanderAt=10000;g->target=0;}
int main(void){
 Combat g;one(&g);combat_attack(&g);combat_tick(&g,.05f,0,0);int hp=g.mobs[0].hp;assert(hp>=36&&hp<=40);
 for(int i=0;i<10;i++)combat_tick(&g,.05f,0,0);
 assert(g.mobs[0].hp==hp); /* cooldown */
 one(&g);g.canMove=wall;combat_attack(&g);for(int i=0;i<60;i++)combat_tick(&g,.05f,0,0);
 assert(g.mobs[0].hp==50&&g.hp==60); /* wall blocks hits */
 one(&g);g.mobs[0].x=100;g.canMove=wall;combat_attack(&g);for(int i=0;i<20;i++)combat_tick(&g,.05f,0,0);
 assert(g.mobs[0].hp==50); /* range */
 one(&g);combat_attack(&g);for(int i=0;i<150&&g.mobs[0].hp;i++)combat_tick(&g,.05f,0,0);
 assert(g.mobs[0].hp==0&&g.kills==1&&g.exp==2&&g.jexp==1);
 int kills=g.kills;for(int i=0;i<60;i++)combat_tick(&g,.05f,0,0);
 assert(g.kills==kills); /* no repeated reward */
 while(g.time-g.mobs[0].deadAt<8.1f)combat_tick(&g,.05f,0,0);
 assert(g.mobs[0].hp==50&&!g.mobs[0].aggro); /* respawn */
 one(&g);g.hp=1;g.mobs[0].aggro=1;combat_tick(&g,.05f,0,0);
 assert(g.hp==0);float dead=g.deadAt;combat_attack(&g);assert(g.hp==0);while(g.time-dead<1.6f)combat_tick(&g,.05f,0,0);combat_attack(&g);assert(g.hp==g.maxhp&&g.target==-1);
 one(&g);g.hp=20;int apples=g.apples;combat_eat(&g);assert(g.hp>=36&&g.hp<=42&&g.apples==apples-1);g.hp=g.maxhp;apples=g.apples;combat_eat(&g);assert(g.apples==apples);
 combat_init(&g,0,0,openworld,NULL);combat_select(&g,-1);assert(g.target==7);combat_select(&g,1);assert(g.target==0);combat_cancel(&g);assert(g.target==-1&&!g.autoAttack);
 one(&g);combat_attack(&g);combat_tick(&g,.05f,1,0);assert(!g.autoAttack); /* manual movement cancels */
 one(&g);for(int i=0;i<20000;i++)combat_reward(&g,&g.mobs[0]);assert(g.level==TEST_LEVEL_CAP&&g.joblevel==10&&g.exp==0&&g.jexp==0&&g.hp==g.maxhp);
 one(&g);float t=g.time;combat_tick(&g,0,0,0);assert(g.time==t);
 puts("PASS: cooldowns, wall/range checks, reward once, respawn, KO recovery, apples, targeting, cancellation, level caps and frozen time");return 0;
}
