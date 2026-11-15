#define MYRO_HOST 1
#include <stdio.h>
#include <assert.h>
#include "combat.h"
int main(void){for(int level=1;level<250;level++)assert(stat_budget(level)==soloStatBudget53[level-1]);assert(stat_budget(250)==7224&&stat_budget(999)==7224);static Combat g;combat_init(&g,100,100,NULL,NULL);g.jobId=8;g.level=250;for(int i=0;i<6;i++)g.stats[i]=150;g.stats[5]=96;g.statPoints=stat_total48(&g)-stat_spent(g.stats);assert(g.statPoints==11&&stat_raise(&g,5)&&g.stats[5]==97&&!g.statPoints&&!stat_raise(&g,5));g.level=249;for(int i=0;i<6;i++)g.stats[i]=1;g.statPoints=stat_total48(&g)-stat_spent(g.stats);int before=g.statPoints;g.exp=progression_base_curve43(g.jobId)[248]-1;combat_gain_exp(&g,1,0);assert(g.level==250&&g.statPoints-before==56);before=g.statPoints;combat_gain_exp(&g,100,0);assert(g.statPoints==before);puts("PASS +2 stat points only at base250; trans five150/last96 spends11 to reach97 with zero left; actual249->250 awards56 once; pre-cap budgets unchanged.");}
