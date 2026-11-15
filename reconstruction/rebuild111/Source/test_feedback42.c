/* MIT. Regression for actual test-stylist states, hit scheduler and semantic button order. */
#define main previous_save_suite_main
#include "test_save41.c"
#undef main
#include "shop.h"
#include "merchant_services.h"
#include "window_ui.h"
int main(void){Combat g,h;Disk d;SaveStore s;init(&d,&s);character(&g);dev_class_preset(&g,6);g.cartOwned=1;g.mapId=2;MerchantUI u;merchant_styles_open(&u,&g);for(int style=0;style<5;style++){u.item=style;merchant_input(&u,&g,2,1);assert(g.cartStyle==style);assert(save_commit(&s,&g));assert(save_load(&s,&h,1500,1500,walk,NULL)&&h.cartStyle==style&&h.level==20);}
/* Actual normal Change Cart still rejects high style at level20. */
g.utilityMenu=65;g.sp=g.maxsp;unsigned style=g.cartStyle;assert(!skill_utility_commit(&g,4)&&g.cartStyle==style);
for(int ms=0;ms<=300;ms+=10){combat_init(&g,1500,1500,NULL,NULL);g.attackSoundDelayMs=ms;g.time=1;combat_hit_sound(&g,3);assert(g.soundWrite==3);for(int i=0;i<3;i++)assert(fabsf(g.soundDue[i]-(1+ms*.001f+i*.1f))<.00001f);unsigned id;g.time=1+ms*.001f-.001f;assert(!combat_next_sound(&g,&id));g.time=1+ms*.001f;assert(combat_next_sound(&g,&id)&&id==0);g.soundRead=g.soundWrite=0;g.time=2;combat_sound(&g,0);combat_sound(&g,1);assert(g.soundDue[0]==2);assert(g.soundDue[1]>=2);}
WindowUI w={.active=1,.focus=UI_STATUS};int expected[4]={UI_STATUS,UI_EQUIP,UI_ITEMS,UI_SKILLS};for(int i=0;i<4;i++){assert(w.focus==expected[i]);assert(ui_top_position42(w.focus)==i);ui_input(&w,&g,8192);}for(int i=3;i>=0;i--){assert(w.focus==expected[i]);ui_input(&w,&g,4096);}w.focus=UI_EQUIP;ui_input(&w,&g,2);assert(w.open==(1u<<UI_EQUIP)&&w.focus==4+UI_EQUIP);puts("PASS42 all five real stylist saves/load, normal skill level gate,31 sound delay values/multi-hit spacing, semantic Status/Equip/Items/Skills navigation and open");}
