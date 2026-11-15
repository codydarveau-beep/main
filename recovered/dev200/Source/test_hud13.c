/* SPDX-License-Identifier: MIT. Focus, lifecycle, stat, buff and sleep regressions. */
#include <assert.h>
#include "combat.h"
#include "window_ui.h"
#include "save_store.h"
#include "save_v5.h"
static void quiet(Combat*g){for(int i=0;i<MOB_COUNT;i++)g->mobs[i].enabled=g->mobs[i].hp=0;}
static CombatMob*mob(Combat*g,int k,float x,float y){CombatMob*m=&g->mobs[k];memset(m,0,sizeof(*m));m->enabled=1;m->hp=50;m->x=m->homeX=x;m->y=m->homeY=y;m->spawnDef=-1;m->wanderAt=0;return m;}
int main(void){
 Combat g;combat_init(&g,1500,1500,NULL,NULL);quiet(&g);
 assert(g.statPoints==12&&g.stats[0]==1);assert(stat_raise(&g,2)&&g.maxhp==65&&g.statPoints==10);assert(stat_raise(&g,3)&&g.maxsp==12);assert(!stat_raise(&g,9));
 g.hp=g.maxhp;g.sp=g.maxsp;int sp=g.sp;assert(skill_cast(&g,5,g.x,g.y)&&g.sp==sp-4&&stat_value(&g,0)==11);assert(!skill_cast(&g,5,g.x,g.y)&&g.sp==sp-4);
 combat_tick(&g,.05,0,0);assert(g.buffs[0]>119);g.buffs[0]=.02;combat_tick(&g,.05,0,0);assert(g.buffs[0]==0&&stat_value(&g,0)==1);
 g.castDelay=0;g.sp=20;assert(skill_cast(&g,6,g.x,g.y));float x=g.x;g.sitting=1;combat_tick(&g,.05,1,0);assert(g.sitting&&g.x==x);g.sitting=0;combat_tick(&g,.05,1,0);assert(g.x>x+5.6);
 g.castDelay=0;g.sp=g.maxsp;assert(skill_cast(&g,7,g.x,g.y));int hp=g.hp;CombatMob*m=mob(&g,0,g.x,g.y);m->aggro=1;combat_tick(&g,.05,0,0);assert(g.hp==hp&&g.shieldHits==4&&g.shieldHP<g.maxhp*30/100);
 quiet(&g);g.sitting=1;g.hp=10;g.sp=0;g.lastDamage=-100;g.lastCast=-100;memset(&g.recovery50,0,sizeof(g.recovery50));
 for(int i=0;i<21;i++)combat_tick(&g,.05,0,0);assert(g.hp==11&&g.sp==1&&g.sitting);
 g.level=10;g.statPoints=stat_budget(10)-stat_spent(g.stats);stat_refresh(&g);g.hp=g.maxhp;g.sp=g.maxsp;
 assert(skill_assign(&g,7,7));SavedCharacter c;save_capture(&c,&g,1);assert(save_valid(&c));unsigned char raw[SAVE_BYTES];save_encode(raw,&c);assert(save_decode(&c,raw)==1);Combat restored;save_restore(&restored,&c,1500,1500,NULL,NULL);assert(restored.stats[2]==2&&restored.stats[3]==2&&restored.statPoints==g.statPoints&&restored.hotbar[7]==7&&!restored.buffs[0]&&!restored.buffs[1]&&!restored.buffs[2]&&!restored.sitting);
 SaveStore store={0};save_mark_clean(&store,&g);assert(!save_dirty(&store,&g));assert(stat_raise(&g,4));assert(save_dirty(&store,&g));c.statPoints++;assert(!save_valid(&c));
 /* Old V5 records cannot smuggle newly added skills. Roundtrip keeps old bytes untouched. */
 Combat old;combat_init(&old,1500,1500,NULL,NULL);old.level=5;old.hp=60;old.zeny=9876;old.mapId=3;V5Character v5;v5_capture(&v5,&old,25);unsigned char previous[V5_BYTES],copy[V5_BYTES];v5_encode(previous,&v5);memcpy(copy,previous,V5_BYTES);assert(v5_decode(&v5,previous)==1);v5_restore(&restored,&v5,1500,1500,NULL,NULL);assert(restored.statPoints==28&&restored.stats[0]==1&&restored.zeny==9876&&restored.mapId==3&&!memcmp(previous,copy,V5_BYTES));v5.hotbar[0]=7;assert(!v5_valid(&v5));
 /* Remote normal actors retain state; combat/boss actors keep running; respawn timers still fire. */
 combat_init(&g,1500,1500,NULL,NULL);quiet(&g);m=mob(&g,0,2800,1500);m->hp=23;float initial=m->x;combat_tick(&g,.05,0,0);assert(m->sleeping&&m->x==initial&&m->hp==23&&g.sleepCount==1);
 for(int i=0;i<100;i++)combat_tick(&g,.05,0,0);assert(m->x==initial&&m->hp==23);
 g.x=1900;combat_tick(&g,.05,0,0);assert(m->sleeping);g.x=2000;combat_tick(&g,.05,0,0);assert(!m->sleeping&&g.awakeCount==1);
 g.x=1500;m->aggro=1;combat_tick(&g,.05,0,0);assert(!m->sleeping);m->aggro=0;m->kind=10;combat_tick(&g,.05,0,0);assert(!m->sleeping);m->kind=0;m->hp=0;m->deadAt=g.time-10;m->respawnAt=0;combat_tick(&g,.05,0,0);assert(m->hp==50);combat_tick(&g,.05,0,0);assert(m->sleeping);
 /* Focus enters windows separately, B backs out without closing, X/close acts only on focus. */
 WindowUI u={0};u.active=1;ui_input(&u,&g,2);assert(u.open==1&&u.focus==4&&!u.inside);ui_input(&u,&g,2);assert(u.inside);ui_input(&u,&g,4);assert(!u.inside&&u.open==1&&u.active);ui_input(&u,&g,4);assert(!u.active&&u.open==1);
 u.active=1;ui_input(&u,&g,8);assert(!u.open&&u.focus==0);u.focus=3;ui_input(&u,&g,2);ui_input(&u,&g,2);assert(u.inside&&u.focus==7);u.choice[3]=5;g.hotSlot=7;ui_input(&u,&g,2);assert(g.hotbar[7]==5);ui_input(&u,&g,512);assert(g.hotSlot==4);u.choice[3]=0;ui_input(&u,&g,1024);assert(u.choice[3]==-1);ui_input(&u,&g,2);assert(!u.open&&!u.inside&&u.focus==3);
 for(int mask=0;mask<16;mask++)for(int f=0;f<8;f++)if(f<4||(mask&(1<<(f-4)))){u=(WindowUI){.active=1,.open=mask,.focus=f};for(int i=0;i<32;i++){ui_input(&u,&g,8192);assert(ui_available(&u,u.focus));}}
 /* Every grid cell is reachable; Heaven's Drive is row2/column1 and casts. */
 u=(WindowUI){.active=1,.inside=1,.open=8,.focus=7};g.sp=g.maxsp;g.castDelay=0;memset(g.skillCD,0,sizeof(g.skillCD));g.hp=g.maxhp;u.choice[3]=0;ui_input(&u,&g,2048);assert(u.choice[3]==4);ui_input(&u,&g,2);assert(g.hotbar[g.hotSlot]==SKILL_HEAVENS_DRIVE);int beforeSP=g.sp;assert(skill_cast(&g,g.hotbar[g.hotSlot],g.x,g.y)&&g.sp==beforeSP-5);
 for(int w=1;w<=3;w+=2)for(int start=0;start<8;start++){u=(WindowUI){.active=1,.inside=1,.open=1u<<w,.focus=4+w};u.choice[w]=start;for(int n=0;n<8;n++){ui_input(&u,&g,8192);assert(u.choice[w]==(start+n+1)%8);}ui_input(&u,&g,1024);assert(u.choice[w]==(start<4?-1:start-4));}
 puts("PASS Test13 stats, budgets, save6, old-save5, buffs/costs/expiry/shields, sitting, AI sleep/wake/boss/respawn, and all window focus masks");
}
