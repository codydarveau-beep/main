/* SPDX-License-Identifier: MIT. Behavioural checks for controller/QOL build. */
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "save_store.h"
#include "quick_slot.h"
#include "window_ui.h"
#include "pause_ui.h"
#include "walk_surface.h"
int main(void){
 Combat g,h;combat_init(&g,1500,1500,NULL,NULL);g.peaceful=1;
 float x=g.x;combat_tick(&g,.05f,1,0);assert(fabsf(g.x-x-4.5f)<.001f);
 g.buffs[1]=20;x=g.x;combat_tick(&g,.05f,1,0);assert(fabsf(g.x-x-5.625f)<.001f);
 g.sitting=1;g.autoAttack=1;x=g.x;combat_tick(&g,.05f,1,0);assert(g.sitting&&g.x==x&&!g.moving&&!g.autoAttack);
 combat_attack(&g);assert(g.sitting&&!g.autoAttack);int hp=g.hp,sp=g.sp;assert(!skill_cast(&g,1,0,0)&&g.sitting&&g.hp==hp&&g.sp==sp);
 g.hp=20;inventory_action(&g,ITEM_APPLE);assert(g.sitting&&g.hp>20);
 assert(!quick_bind(&g,0,ITEM_JELLOPY));assert(quick_bind(&g,0,ITEM_RED_POTION));assert(!quick_bind(&g,1,SKILL_MAGNUM));assert(quick_bind(&g,1,SKILL_HEAVENS_DRIVE));
 SavedCharacter c;save_capture(&c,&g,1);unsigned char raw[SAVE_BYTES];save_encode(raw,&c);assert(save_decode(&c,raw)==1);save_restore(&h,&c,1500,1500,NULL,NULL);assert(h.quickKind==1&&h.quickId==4);
 SaveStore store={0};save_mark_clean(&store,&g);assert(!save_dirty(&store,&g));assert(quick_bind(&g,0,0)&&save_dirty(&store,&g));
 save_capture(&c,&g,1);c.quickKind=0;c.quickId=1;save_encode(raw,&c);assert(!save_decode(&c,raw));c.quickKind=1;c.quickId=8;save_encode(raw,&c);assert(!save_decode(&c,raw));
 WindowUI u={.open=15,.active=1,.inside=1,.focus=5};u.choice[1]=3;ui_input(&u,&g,16);ui_input(&u,&g,16);ui_input(&u,&g,2);assert(g.quickKind==0&&g.quickId==3);u.focus=7;u.choice[3]=4;ui_input(&u,&g,2);assert(g.quickKind==1&&g.quickId==4);
 PauseUI p={0};assert(pause_input(&p,2)==PA_SAVE);pause_input(&p,2048);assert(pause_input(&p,2)==PA_LOAD);pause_input(&p,2048);assert(pause_input(&p,2)==PA_TRAVEL);
 pause_input(&p,512);assert(p.tab==1&&!p.row);assert(pause_input(&p,8192)==PA_MUSIC_UP);pause_input(&p,2048);assert(pause_input(&p,4096)==PA_SFX_DOWN);pause_input(&p,2048);assert(pause_input(&p,2)==PA_MUSIC_MUTE);pause_input(&p,512);assert(pause_input(&p,2)==PA_HELP);pause_input(&p,2048);assert(pause_input(&p,2)==PA_SCENERY);assert(pause_input(&p,4)==PA_RESUME);
 for(unsigned m=0;m<7;m++)for(unsigned i=surfaceOffsets[m];i<surfaceOffsets[m+1];i++){
  const WalkSurface*s=&surfaceCells[i];if(i>surfaceOffsets[m])assert(surfaceCells[i-1].cell<s->cell);
  unsigned w=m==2?312:m==3?268:m==4?380:400,hgt=m==2?392:m==3?268:m==4?340:400;
  float xx=(s->cell%w+.5f)*8,yy=(s->cell/w+.5f)*8,z=surface_height(m,w,hgt,xx,yy,-9999);assert(fabsf(z-(s->z[0]+s->z[3])/32.f)<.001f);
 }
 assert(surface_height(7,400,400,0,0,123)==123);
 /* Only actual damage breaks the sitting lock. */
 combat_init(&g,1500,1500,NULL,NULL);g.sitting=1;for(int i=0;i<MOB_COUNT;i++)g.mobs[i].enabled=0;CombatMob*m=&g.mobs[0];m->enabled=1;m->kind=0;m->hp=50;m->aggro=1;m->x=g.x;m->y=g.y;m->homeX=g.x;m->homeY=g.y;m->cooldown=0;
 g.buffs[2]=20;g.shieldHP=999;g.shieldHits=5;combat_tick(&g,.05f,0,0);assert(g.sitting&&g.hp==g.maxhp);g.buffs[2]=0;m->cooldown=0;combat_tick(&g,.05f,0,0);assert(!g.sitting&&g.hp<g.maxhp);
 puts("PASS 1.5x walking/buffed speed, sitting lock/actions/shield/damage, LB bindings/validation/UI/save dirty round-trip, all pause actions and sparse surface cells");
}
