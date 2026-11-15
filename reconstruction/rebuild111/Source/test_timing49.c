/* MIT. Damage, audio, movement locking and target lifetime share the hit clock. */
#define main old_classes49_main
#include "test_classes48.c"
#undef main
static void advance49(Combat*g,float seconds){while(seconds>.0001f){float dt=seconds>.01f?.01f:seconds;combat_tick(g,dt,0,0);seconds-=dt;}}
int main(void){Combat g;prepare48(&g,9);CombatMob*m=&g.mobs[MOB_COUNT-1];g.fxSkill=23;g.fxRank48=10;int hp=m->hp;skill_hit_ex(&g,MOB_COUNT-1,500,0,5);assert(m->hp==hp-100&&m->hitLockUntil49>g.time);advance49(&g,.19f);assert(m->hp==hp-100);advance49(&g,.02f);assert(m->hp==hp-200);advance49(&g,.6f);assert(m->hp==hp-500&&g.soundWrite>=5);
 prepare48(&g,9);m=&g.mobs[MOB_COUNT-1];g.fxSkill=78;hp=m->hp;skill_hit_ex(&g,MOB_COUNT-1,300,0,3);assert(m->hp==hp-100);advance49(&g,.14f);assert(m->hp==hp-100);advance49(&g,.02f);assert(m->hp==hp-200);advance49(&g,.1f);assert(m->hp==hp-200);advance49(&g,.02f);assert(m->hp==hp-300);
 prepare48(&g,9);m=&g.mobs[MOB_COUNT-1];g.fxSkill=3;skill_hit_ex(&g,MOB_COUNT-1,1000,0,10);hp=m->hp;m->life++;advance49(&g,1);assert(m->hp==hp);for(int i=0;i<SKILL_BURSTS49;i++)assert(!g.bursts49[i].active);
 prepare48(&g,9);for(int i=0;i<SKILL_BURSTS49;i++)g.bursts49[i].active=1;int sp=g.sp;assert(!skill_burst_ready49(&g,23,10,g.x,g.y)&&g.sp==sp);
 puts("PASS49 actual200ms packet burst hits, Water Ball150/125ms, per-hit damage/sound/flinch, exact totals, target life guard and queue exhaustion resource preservation.");}
