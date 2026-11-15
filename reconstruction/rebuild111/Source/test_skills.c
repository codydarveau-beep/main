/* SPDX-License-Identifier: MIT. Portable skill rules and saved assignment checks. */
#include <assert.h>
#include <stdio.h>
#include "save_store.h"
#include "save_v2.h"
static int openworld(void*w,float x,float y,float nx,float ny){(void)w;(void)x;(void)y;return nx>=8&&ny>=8&&nx<3192&&ny<3192;}
static int wall(void*w,float x,float y,float nx,float ny){(void)w;(void)x;(void)y;(void)nx;(void)ny;return 0;}
static void init(Combat*g){combat_init(g,2100,1636,openworld,NULL);for(int i=0;i<8;i++){g->mobs[i].x=2300+i*10;g->mobs[i].y=1636;g->mobs[i].wanderAt=10000;}g->mobs[0].x=2112;g->mobs[0].homeX=2112;g->target=0;}
int main(void){Combat g;init(&g);assert(!skill_cast(&g,1,0,0)&&g.sp==10&&g.skillCD[0]==0);g.hp=50;assert(skill_cast(&g,1,0,0)&&g.hp==55&&g.sp==7);assert(!skill_cast(&g,1,0,0)&&g.sp==7);combat_tick(&g,.05f,0,0);assert(g.skillCD[0]>0);float cd=g.skillCD[0];combat_tick(&g,0,0,0);assert(g.skillCD[0]==cd);
 init(&g);assert(!skill_cast(&g,255,0,0)&&g.sp==10);g.sp=0;int hp=g.mobs[0].hp;assert(!skill_cast(&g,2,0,0)&&g.mobs[0].hp==hp&&g.skillCD[1]==0);g.sp=3;assert(!skill_cast(&g,3,0,0)&&g.sp==3);
 init(&g);assert(skill_cast(&g,2,0,0)&&g.mobs[0].hp==30&&g.sp==6&&g.mobs[0].stun>1);int life=g.hp;for(int i=0;i<10;i++)combat_tick(&g,.05f,0,0);assert(g.hp==life); /* stun suppresses retaliation */
 init(&g);g.mobs[0].x=2200;assert(!skill_cast(&g,2,0,0)&&g.sp==10);assert(skill_cast(&g,3,0,0)&&g.mobs[0].hp==20&&g.sp==6);init(&g);g.canMove=wall;assert(!skill_cast(&g,3,0,0)&&g.sp==10);
 init(&g);assert(!skill_cast(&g,4,3000,3000)&&g.sp==10);assert(!skill_cast(&g,4,NAN,1636)&&g.sp==10);g.canMove=wall;assert(!skill_cast(&g,4,2100,1636)&&g.sp==10);
 init(&g);g.mobs[0].x=2110;g.mobs[1].x=2120;g.mobs[0].hp=g.mobs[1].hp=10;assert(skill_cast(&g,4,2112,1636));assert(g.kills==2&&g.exp==4&&g.jexp==2&&g.sp==5);assert(g.mobs[0].hp==0&&g.mobs[1].hp==0);assert(!skill_cast(&g,4,2112,1636)&&g.kills==2&&g.sp==5);
 init(&g);g.sp=0;for(int i=0;i<200;i++)combat_tick(&g,.05f,0,0);assert(g.sp>0&&g.sp<=g.maxsp);g.hp=0;g.sp=0;for(int i=0;i<200;i++)combat_tick(&g,.05f,0,0);assert(g.sp==0&&!skill_cast(&g,1,0,0));
 init(&g);g.hotSlot=0;skill_slot(&g,-1,0);assert(g.hotSlot==3);skill_slot(&g,0,1);assert(g.hotSlot==7);skill_slot(&g,1,0);assert(g.hotSlot==4);assert(skill_assign(&g,7,3)&&g.hotbar[7]==3);assert(!skill_assign(&g,8,1)&&!skill_assign(&g,0,99));assert(skill_assign(&g,1,255));
 SaveStore store={0};save_mark_clean(&store,&g);assert(!save_dirty(&store,&g));g.hotSlot=6;assert(save_dirty(&store,&g));save_mark_clean(&store,&g);skill_assign(&g,6,4);assert(save_dirty(&store,&g));
 SavedCharacter c,p;save_capture(&c,&g,10);unsigned char raw[SAVE_BYTES];save_encode(raw,&c);assert(save_decode(&p,raw)==1);Combat h;save_restore(&h,&p,2100,1636,openworld,NULL);assert(h.hotSlot==6&&!memcmp(h.hotbar,g.hotbar,8));
 c.hotbar[0]=99;save_encode(raw,&c);assert(save_decode(&p,raw)==0);c.hotbar[0]=0;c.hotSlot=8;save_encode(raw,&c);assert(save_decode(&p,raw)==0);
 V2Character old;v2_capture(&old,&g,50);unsigned char oldRaw[V2_BYTES];v2_encode(oldRaw,&old);V2Character parsed;assert(v2_decode(&parsed,oldRaw)==1);v2_restore(&h,&parsed,2100,1636,openworld,NULL);const unsigned char defaults[8]={0,1,2,3,4,255,255,255};assert(!memcmp(h.hotbar,defaults,8)&&h.hotSlot==0);
 puts("PASS: no-SP/full-HP/cooldown/range/wall/NaN rejection, Bash stun, ranged magic, AoE rewards once, SP regen/KO, hotbar wrap/assignment/persistence, v2 import");return 0;}
