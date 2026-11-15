/* MIT. Save/class/progression and live-menu mechanics across the expansion. */
#include <assert.h>
#include "combat.h"
#include "developer.h"
#include "save_store.h"
#include "session_controls40.h"
#include "cast_layout43.h"
static int clear(void*w,float x,float y,float nx,float ny){(void)w;(void)x;(void)y;return nx>=8&&ny>=8&&nx<3192&&ny<3192;}
int main(void){Combat g,h;SavedCharacter s,t;unsigned char disk[SAVE_BYTES];
for(unsigned job=0;job<=11;job++){combat_init(&g,1500,1500,clear,NULL);if(job)dev_class_preset(&g,job);assert(g.jobId==job);if(job){assert(g.level==99);assert(g.joblevel==progression_job_cap43(job));}for(unsigned map=0;map<18;map++){g.mapId=map;g.x=100;g.y=100;save_capture(&s,&g,1);if(!save_valid(&s)){fprintf(stderr,"invalid preset job%u map%u hp%d/%d sp%d/%d points%d\n",job,map,g.hp,g.maxhp,g.sp,g.maxsp,g.statPoints);abort();}save_encode(disk,&s);assert(save_decode(&t,disk)==1);assert(t.jobId==job&&t.mapId==map&&!memcmp(t.ranks,g.ranks,LEARN_COUNT));disk[600]^=1;assert(save_decode(&t,disk)==0);} }
for(unsigned job=0;job<=11;job++){combat_init(&g,1500,1500,clear,NULL);g.jobId=job;g.statPoints=stat_total48(&g);stat_refresh(&g);for(int level=1;level<99;level++){int need=progression_base_curve43(job)[g.level-1];combat_gain_exp(&g,need,0);assert(g.level==level+1);assert(g.hp==g.maxhp&&g.sp==g.maxsp);save_capture(&s,&g,1);assert(save_valid(&s));}combat_gain_exp(&g,1000000,0);assert(g.level==99&&g.exp==0);for(int level=1;level<job_cap(&g);level++){int need=job_next(&g);assert(need>0);combat_gain_exp(&g,0,need);assert(g.joblevel==level+1);}assert(!job_next(&g));save_capture(&s,&g,1);assert(save_valid(&s));}
combat_init(&g,1500,1500,clear,NULL);g.poisonLeft=30;g.hp=g.maxhp;float now=g.time,x=g.x;session_world_tick43(&g,.05f,0,1,1,1);assert(g.time>now&&g.x==x&&g.poisonLeft<30);now=g.time;float poison=g.poisonLeft;session_world_tick43(&g,.05f,1,0,1,1);assert(g.time==now&&g.poisonLeft==poison);
for(int ticks=1;ticks<=120;ticks++){int margin,used,step,n;cast_layout41(ticks*.05f,&margin,&used,&step,&n);assert(margin==0&&used==step*n-1);assert(!cast_quarter_gap(ticks*.05f,0)&&!cast_quarter_gap(ticks*.05f,used-1));int gaps=0;for(int p=0;p<used;p++)gaps+=cast_quarter_gap(ticks*.05f,p);assert(gaps==n-1);}
puts("PASS43 twelve classes:216 class/map save roundtrips, checksum rejection, all98 natural base-level transitions per class, class-specific job caps/curves, full table bounds, live Select/pausedSTART timers, equal full-width cast cells.");}
