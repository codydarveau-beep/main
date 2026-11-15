/* MIT. Actual controller navigation follows the drawn two-column slot layout. */
#include <assert.h>
#include <stdio.h>
#include "combat.h"
#include "developer.h"
#include "window_ui.h"
int main(void){static Combat g;combat_init(&g,1500,1500,NULL,NULL);dev_class_preset(&g,11);WindowUI u={0};ui_open(&u,UI_EQUIP,1);
 for(int row=0;row<5;row++)for(int col=0;col<2;col++){
  int slot=row*2+col;u.choice[UI_EQUIP]=slot;ui_input(&u,&g,1024);assert(u.choice[UI_EQUIP]==(row?slot-2:-1));
  u.choice[UI_EQUIP]=slot;ui_input(&u,&g,2048);assert(u.choice[UI_EQUIP]==(row<4?slot+2:-1));
  u.choice[UI_EQUIP]=slot;ui_input(&u,&g,4096);assert(u.choice[UI_EQUIP]==row*2);
  u.choice[UI_EQUIP]=slot;ui_input(&u,&g,8192);assert(u.choice[UI_EQUIP]==row*2+1);
 }
 u.choice[UI_EQUIP]=-1;ui_input(&u,&g,2048);assert(u.choice[UI_EQUIP]==0);ui_input(&u,&g,2);assert(u.equipPicker49);ui_input(&u,&g,2048);assert(u.equipChoice49==1);ui_input(&u,&g,4);assert(!u.equipPicker49&&u.inside);ui_input(&u,&g,4);assert(!u.inside&&u.active);
 u.inside=1;u.choice[UI_EQUIP]=-1;ui_input(&u,&g,2);assert(!(u.open&(1u<<UI_EQUIP)));
 puts("PASS50b 40 actual D-pad slot moves, vertical column retention, horizontal row retention, edge/header behavior, compatible equipment modal and B/close controls.");}
