/* MIT. Equipment selection is modal, filters real owned gear and preserves navigation. */
#include <assert.h>
#include "combat.h"
#include "developer.h"
#include "window_ui.h"
int main(void){Combat g;combat_init(&g,1500,1500,NULL,NULL);dev_class_preset(&g,11);WindowUI u={.open=(1u<<UI_EQUIP)|(1u<<UI_ITEMS),.active=1,.focus=4+UI_EQUIP};ui_spatial(&u,8192);assert(u.focus==4+UI_ITEMS);ui_spatial(&u,4096);assert(u.focus==4+UI_EQUIP);
 ui_open(&u,UI_EQUIP,1);u.choice[UI_EQUIP]=0;int original=inventory_slot46(&g,0);ui_input(&u,&g,2);assert(u.equipPicker49);ui_input(&u,&g,4);assert(!u.equipPicker49&&inventory_slot46(&g,0)==original&&u.inside);
 ui_input(&u,&g,2);int spear=-1;for(int c=1;c<ui_equip_count49(&g,0);c++){int id=ui_equip_item49(&g,0,c);assert(inventory_count(&g,id)>0&&inventory_can_equip46(&g,id)&&itemDefs[id].slot==0);if(itemDefs[id].id==1451)spear=c;}assert(spear>0);u.equipChoice49=spear;ui_input(&u,&g,2);assert(!u.equipPicker49&&inventory_wtype46(&g)==5&&inventory_slot46(&g,3)<0);ui_input(&u,&g,2);ui_input(&u,&g,2);assert(inventory_slot46(&g,0)<0);
 for(int job=8;job<=9;job++){dev_class_preset(&g,job);int found=0;for(unsigned c=0;c<class_count(&g);c++)found|=class_skill(&g,c)==89;assert(found);}
 puts("PASS49 diagonal window focus, filtered modal equipment, cancellation, spear availability, two-hand/shield replacement, unequip and Wizard/HighWizard Ice Wall visibility.");}
