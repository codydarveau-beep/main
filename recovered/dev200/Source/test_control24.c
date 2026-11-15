/* MIT. Real cast/tick/save code; control, AoE, source costs and migration. */
#include <assert.h>
#include "save_store.h"
#include "save_v12.h"
#include "developer.h"
#include "quick_slot.h"
static int deny(void*w,float a,float b,float c,float d){(void)w;(void)a;(void)b;(void)c;(void)d;return 0;}
static void mage(Combat*g){combat_init(g,1500,1500,NULL,NULL);g->jobId=2;g->joblevel=50;g->skillPoints=49;g->level=20;g->statPoints=stat_budget(20);stat_refresh(g);dev_restore(g);for(int i=0;i<MOB_COUNT;i++)g->mobs[i].enabled=0;for(int j=0;j<5;j++)assert(skill_learn(g,9));for(int j=0;j<4;j++)assert(skill_learn(g,21));}
static void ready(Combat*g){g->castDelay=0;memset(g->skillCD,0,sizeof(g->skillCD));g->sp=g->maxsp;}
static void mob(Combat*g,int i,int kind,float x,float y){CombatMob*m=&g->mobs[i];memset(m,0,sizeof(*m));m->enabled=1;m->kind=kind;m->hp=10000;m->x=m->homeX=x;m->y=m->homeY=y;m->aggro=1;m->spawnDef=-1;m->attackAt=-100;}
int main(void){Combat g,h;combat_init(&g,1500,1500,NULL,NULL);g.jobId=2;g.joblevel=50;g.skillPoints=49;assert(!skill_learn(&g,29)&&!skill_learn(&g,30));mage(&g);
 V12Character old;v12_capture(&old,&g,8);assert(v12_valid(&old));unsigned char before[V12_BYTES],copy[V12_BYTES];v12_encode(before,&old);memcpy(copy,before,sizeof(copy));assert(v12_decode(&old,before)==1);v12_restore(&h,&old,1500,1500,NULL,NULL);assert(!h.ranks[25]&&!h.ranks[26]&&h.ranks[3]==5&&h.ranks[17]==4&&h.skillPoints==40&&!memcmp(before,copy,V12_BYTES));old.hotbar[0]=29;assert(!v12_valid(&old));
 assert(skill_learn(&g,29)&&skill_learn(&g,30));assert(skill_cost(&g,29)==25&&skill_cost(&g,30)==29);assert(class_count(&g)==9);assert(skill_ground(30)&&!skill_ground(29));
 for(int j=1;j<10;j++){assert(skill_learn(&g,29)&&skill_learn(&g,30));}assert(skill_cost(&g,29)==16&&skill_cost(&g,30)==74);g.hotbar[6]=29;g.hotbar[7]=30;assert(quick_bind_to(&g,0,29)&&quick_bind_to(&g,1,30));SavedCharacter c;save_capture(&c,&g,9);assert(save_valid(&c));unsigned char raw[SAVE_BYTES];save_encode(raw,&c);assert(save_decode(&c,raw)==1);save_restore(&h,&c,1500,1500,NULL,NULL);assert(h.ranks[25]==10&&h.ranks[26]==10&&h.rbBinding==30&&h.quickId==29&&h.hotbar[7]==30);
 SaveStore store={0};save_mark_clean(&store,&g);assert(!save_dirty(&store,&g));g.ranks[25]--;g.skillPoints++;assert(save_dirty(&store,&g));g.ranks[25]++;g.skillPoints--;
 // Freeze chance, movement/attack suppression, natural expiry, breaking on damage.
 g.ranks[25]=1;int frozen=0;for(int tries=0;tries<100&&!frozen;tries++){ready(&g);mob(&g,0,1,1520,1500);g.target=0;assert(skill_cast(&g,29,0,0));frozen=g.mobs[0].frozenLeft>0;}assert(frozen);float x=g.mobs[0].x;int hp=g.hp;combat_tick(&g,.05f,0,0);assert(g.mobs[0].x==x&&!g.mobs[0].moving&&g.hp==hp&&g.mobs[0].attackAt==-100);for(int j=0;j<70;j++)combat_tick(&g,.05f,0,0);assert(g.mobs[0].frozenLeft==0&&g.mobs[0].x<x);
 g.mobs[0].frozenLeft=3;combat_enemy_damage(&g,&g.mobs[0],1);assert(!g.mobs[0].frozenLeft);
 // Wind gets water-property bonus for first hit, then returns to natural armour.
 ready(&g);mob(&g,0,1,1520,1500);g.target=0;g.mobs[0].frozenLeft=3;assert(skill_cast(&g,21,0,0));assert(g.mobs[0].hp==10000-(144*175/100+144*3)&&!g.mobs[0].frozenLeft);
 // Square AoE includes its corners, excludes outside, and never touches disabled mobs.
 ready(&g);g.ranks[26]=4;mob(&g,0,1,1559,1519);mob(&g,1,1,1561,1500);mob(&g,2,1,1540,1500);g.mobs[2].enabled=0;g.mobs[0].frozenLeft=3;assert(skill_cast(&g,30,1540,1500));g.debugFreeze=1;for(int t=0;t<30;t++)combat_tick(&g,.05f,0,0);assert(g.mobs[0].hp==10000-(115*175/100+115*3)&&!g.mobs[0].frozenLeft);assert(g.mobs[1].hp==10000&&g.mobs[2].hp==10000);assert(g.damage[(g.damageNext-1)%DAMAGE_EVENTS].kind==1);
 int sp=g.sp;assert(!skill_cast(&g,30,1540,1500)&&g.sp==sp);ready(&g);sp=g.sp;assert(!skill_cast(&g,30,NAN,1500)&&g.sp==sp);assert(!skill_cast(&g,30,1600,1500)&&g.sp==sp);g.canMove=g.canAim=deny;assert(!skill_cast(&g,30,1540,1500)&&g.sp==sp);g.canMove=g.canAim=NULL;g.sp=0;assert(!skill_cast(&g,29,0,0)&&!g.skillCD[28]);
 // Job reset removes new bindings, ranks and cooldowns; old formats reject future IDs.
 ready(&g);assert(combat_change_job(&g,1));assert(g.quickKind==0&&g.rbBinding==255&&g.hotbar[7]==255&&!g.ranks[25]&&!g.ranks[26]);
 puts("PASS Test24 prerequisites/costs, freeze chance/AI suppression/expiry/break, wind armour transition, bounded square AoE and multi-hits, SP/cooldown/wall/NaN guards, Save13 ranks/both quick slots/dirty tracking, frozen read-only Save12 importer, job reset");}
