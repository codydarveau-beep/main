/* MIT. Source-derived stat boundaries, progression accounting and grouped navigation. */
#include <assert.h>
#include "combat.h"
#include "developer.h"
#include "save_format.h"
#include "menu_groups48.h"
int main(void){Combat g;combat_init(&g,1500,1500,0,0);assert(stat_budget(1)==48&&stat_budget(99)==1273);g.stats[0]=10;assert(stat_cost(&g,0)==2);g.stats[0]=11;assert(stat_cost(&g,0)==3);g.stats[0]=99;g.statPoints=10000;assert(!stat_raise(&g,0));
 for(int job=1;job<21;job++){combat_init(&g,1500,1500,0,0);dev_class_preset(&g,job);assert(g.jobId==(unsigned)job);assert(g.statPoints+stat_spent(g.stats)==stat_total48(&g));assert(stat_total48(&g)==(job==8?1325:1273));assert(combat_matk_min48(&g)<=combat_matk_max48(&g));assert(combat_aspd48(&g)>=0&&combat_aspd48(&g)<=1900);assert(g.hp==stat_maxhp(&g)&&g.sp==stat_maxsp(&g));SavedCharacter s;save_capture(&s,&g,1);assert(save_valid(&s));}
 assert(combat_reduce48(100,25,10)==65);assert(combat_reduce48(10,100,500)==1);DeveloperUI u={.tab=2};combat_init(&g,1500,1500,0,0);assert(dev_class_job48(&u)==1);dev_input(&u,&g,8192);assert(u.classGroup==1&&dev_class_job48(&u)==7);dev_input(&u,&g,2048);assert(dev_class_job48(&u)==11);dev_input(&u,&g,8192);assert(u.classGroup==2&&dev_class_job48(&u)==8);dev_input(&u,&g,8192);assert(u.classGroup==0&&u.row==0);
 int seen[18]={0};assert(travelGroupNames48[0][0]);for(int group=0;group<5;group++)for(int row=0;row<travelCounts48[group];row++){int m=travelGroups48[group][row];assert(!seen[m]++);assert(travel_group48(m)==group);assert(travel_step48(travel_step48(m,1),-1)==m);assert(travel_group48(travel_region48(m,1))==(group+1)%5);}for(int i=0;i<18;i++)assert(seen[i]==1);
 combat_init(&g,1500,1500,0,0);dev_class_preset(&g,9);assert(skill_rank(&g,73)>0&&!skill_rank(&g,85)&&!skill_rank(&g,87));dev_class_preset(&g,8);assert(skill_rank(&g,73)>0&&skill_rank(&g,85)>0&&skill_rank(&g,87)>0);puts("PASS50 twenty-one class stat/HP/SP/budget/save models, source statcost boundaries, damage defense, Wizard/transcendent separation, grouped class controls and all18 map groups.");}
