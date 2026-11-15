/* MIT. Shared skill list/grid controls retain rank selection and close wrap. */
#include <assert.h>
#include <stdio.h>
#include "combat.h"
#include "window_ui.h"
#include "developer.h"
int main(void){Combat g;combat_init(&g,1200,1200,NULL,NULL);dev_class_preset(&g,8);WindowUI u={0};ui_open(&u,UI_SKILLS,1);u.skillPage=1;u.choice[3]=3;unsigned id=class_skill(&g,3),rank=skill_rank(&g,id);ui_input(&u,&g,32768);assert(u.skillDetailed46&&u.choice[3]==3);ui_input(&u,&g,2048);assert(u.choice[3]==4);ui_input(&u,&g,1024);assert(u.choice[3]==3);ui_input(&u,&g,32);if(rank>1)assert(skill_rank(&g,id)==rank-1);ui_input(&u,&g,512);assert(skill_rank(&g,id)==rank);ui_input(&u,&g,32768);assert(!u.skillDetailed46);ui_input(&u,&g,2048);assert(u.choice[3]==7);u.skillDetailed46=1;u.choice[3]=-1;ui_input(&u,&g,1024);assert(u.choice[3]==(int)class_count(&g)-1);puts("PASS46 RT grid/list switch, list/grid navigation, selected skill preservation, White/Black cast ranks and close wrap.");}
