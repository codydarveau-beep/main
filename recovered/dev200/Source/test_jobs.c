/* SPDX-License-Identifier: MIT. Progression, class learning, combat and save migration. */
#include <assert.h>
#include <limits.h>
#include "save_store.h"
#include "save_v6.h"
#include "window_ui.h"
int main(void){
 Combat g;combat_init(&g,1500,1500,NULL,NULL);for(int i=0;i<MOB_COUNT;i++)g.mobs[i].enabled=g.mobs[i].hp=0;
 assert(!combat_change_job(&g,1));combat_gain_exp(&g,0,2000);assert(g.joblevel==10&&g.jexp==0&&!g.skillPoints);
 g.level=10;g.statPoints=stat_budget(10);stat_refresh(&g);g.hp=g.maxhp;g.sp=g.maxsp;g.zeny=1234;g.apples=12;
 V6Character old;v6_capture(&old,&g,70);unsigned char before[V6_BYTES],copy[V6_BYTES];v6_encode(before,&old);memcpy(copy,before,V6_BYTES);assert(v6_decode(&old,before)==1);Combat migrated;v6_restore(&migrated,&old,1500,1500,NULL,NULL);assert(migrated.jobId==0&&migrated.level==10&&migrated.joblevel==10&&migrated.zeny==1234&&!memcmp(copy,before,V6_BYTES));
 int hp=g.hp,sp=g.sp;assert(combat_change_job(&g,1)&&g.jobId==1&&g.joblevel==1&&!g.skillPoints&&g.apples==12&&g.zeny==1234&&g.hp==hp&&g.sp==sp&&g.maxhp>hp);
 assert(!skill_learn(&g,8)&&!skill_learn(&g,9));combat_gain_exp(&g,0,firstJobCurve[0]);assert(g.joblevel==2&&g.skillPoints==1&&g.jexp==0);assert(skill_learn(&g,2)&&g.ranks[0]==1&&!g.skillPoints);
 while(g.joblevel<8)combat_gain_exp(&g,0,job_next(&g)-g.jexp);
 assert(g.skillPoints==6);for(int i=0;i<4;i++)assert(skill_learn(&g,2));assert(g.ranks[0]==5&&skill_learn(&g,8)&&g.ranks[1]==1&&g.skillPoints==1);
 assert(skill_assign(&g,7,8));CombatMob*m=&g.mobs[0];m->enabled=1;m->hp=1000;m->kind=0;m->x=g.x+10;m->y=g.y;m->spawnDef=-1;g.sp=g.maxsp;assert(skill_cast(&g,8,g.x,g.y)&&m->hp<1000&&g.fxSkill==8&&g.fxX==g.x);int spentSP=g.sp;assert(!skill_cast(&g,8,g.x,g.y)&&g.sp==spentSP);
 SavedCharacter c;save_capture(&c,&g,1);assert(save_valid(&c));unsigned char raw[SAVE_BYTES];save_encode(raw,&c);assert(save_decode(&c,raw)==1);Combat h;save_restore(&h,&c,1500,1500,NULL,NULL);assert(h.jobId==1&&h.ranks[0]==5&&h.ranks[1]==1&&h.skillPoints==1&&h.hotbar[7]==8&&h.maxhp==g.maxhp);
 SaveStore store={0};save_mark_clean(&store,&g);assert(!save_dirty(&store,&g));assert(skill_learn(&g,8)&&save_dirty(&store,&g));
 assert(combat_change_job(&g,2)&&g.joblevel==1&&g.hotbar[7]==255&&!g.ranks[0]&&!g.ranks[1]);assert(!skill_learn(&g,2));combat_gain_exp(&g,0,1000);assert(g.skillPoints==g.joblevel-1);assert(skill_learn(&g,3)&&skill_learn(&g,9));assert(skill_assign(&g,7,9));g.castDelay=0;g.sp=g.maxsp;m=&g.mobs[0];m->hp=1000;g.target=0;assert(skill_cast(&g,9,g.x,g.y)&&m->hp<1000);
 WindowUI u={.active=1,.inside=1,.focus=7,.open=8};ui_input(&u,&g,16384);assert(u.skillPage==1);u.choice[3]=1;int rank=g.ranks[3];ui_input(&u,&g,8);assert(g.ranks[3]==rank+1);ui_input(&u,&g,2);assert(g.hotbar[g.hotSlot]==9);ui_input(&u,&g,16384);assert(!u.skillPage&&u.choice[3]==0);
 while(g.level<20)combat_gain_exp(&g,baseCurve[g.level-1]-g.exp,0);while(g.joblevel<TEST_JOB_CAP)combat_gain_exp(&g,0,job_next(&g)-g.jexp);combat_gain_exp(&g,999999,999999);assert(g.exp==0&&g.jexp==0&&g.statPoints+stat_spent(g.stats)==stat_budget(20));save_capture(&c,&g,2);assert(save_valid(&c));
 c.jobId=3;assert(!save_valid(&c));save_capture(&c,&g,2);c.ranks[0]=1;assert(!save_valid(&c));save_capture(&c,&g,2);c.skillPoints=INT_MAX;assert(!save_valid(&c));c.level=INT_MAX;assert(!save_valid(&c));old.level=INT_MAX;assert(!v6_valid(&old));
 puts("PASS job entry/reset, original XP tables and caps, skill-point budgets/prerequisites, learned AoE/Cold Bolt, class UI, Save07 ranks and read-only Save06 preservation");
}
