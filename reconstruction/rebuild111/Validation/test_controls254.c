#include <assert.h>
#include <stdio.h>
#include "combat.h"
#include "window_ui.h"
static Combat game;
int main(void){combat_init(&game,100,100,NULL,NULL);game.statPoints=100;WindowUI ui={0};ui_open(&ui,UI_STATUS,0);unsigned before=game.stats[0];ui_input(&ui,&game,8);assert(game.stats[0]==before);ui_open(&ui,UI_STATUS,0);ui_input(&ui,&game,2);ui.choice[UI_STATUS]=0;ui_input(&ui,&game,2);assert(game.stats[0]==before);ui_input(&ui,&game,8);assert(game.stats[0]==before+1&&game.statPoints<100);ui_input(&ui,&game,4);assert(!ui.inside);unsigned points=game.statPoints;ui_input(&ui,&game,8);assert(game.statPoints==points);
for(unsigned front=0;front<2;front++){ui=(WindowUI){.assignBank=front,.dropSlot=front*6};ui_drop_move(&ui,2048);assert(ui.dropSlot==(1-front)*6);ui_drop_move(&ui,1024);assert(ui.dropSlot==front*6);ui_drop_move(&ui,4096);assert(ui.dropSlot==12);ui_drop_move(&ui,8192);assert(ui.dropSlot==front*6);ui.dropSlot=front*6+5;ui_drop_move(&ui,8192);assert(ui.dropSlot==13);ui_drop_move(&ui,4096);assert(ui.dropSlot==front*6+5);}
puts("PASS actual UI controls: highlighted windows do not allocate, A enters, X allocates, B exits; front bank/cursor/quick-slot mapping remains consistent for either hotbar.");}
