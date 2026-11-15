/* GPL-3.0-or-later. Original100-kill mission; no online ranking benefits. */
#include "taekwon_mission_data60.h"
static int expanded_mob_kind60(unsigned source){for(int i=0;i<MOB_SPEC_COUNT;i++)if((unsigned)mobSpecs[i].id==source)return i;return -1;}
static int taekwon_mission_eligible60(const Combat*g,unsigned kind){
 if(kind>=MOB_SPEC_COUNT||mobSourceLevel[kind]>g->level||(mobSpecs[kind].flags&4))return 0;
 for(unsigned i=0;i<sizeof(spawnDefs)/sizeof(*spawnDefs);i++)if(spawnDefs[i].kind==kind&&spawnDefs[i].count)return 1;return 0;
}
static unsigned taekwon_mission_pick60(Combat*g,int weighted){
 unsigned total=0;for(unsigned i=0;i<sizeof(taekwonMissionData60)/sizeof(*taekwonMissionData60);i++)if(taekwon_mission_eligible60(g,taekwonMissionData60[i][0]))total+=weighted?taekwonMissionData60[i][1]:1;
 if(!total)return 1002;unsigned roll=combat_random(g)%total;
 for(unsigned i=0;i<sizeof(taekwonMissionData60)/sizeof(*taekwonMissionData60);i++)if(taekwon_mission_eligible60(g,taekwonMissionData60[i][0])){unsigned chance=weighted?taekwonMissionData60[i][1]:1;if(roll<chance)return mobSpecs[taekwonMissionData60[i][0]].id;roll-=chance;}return 1002;
}
static void taekwon_mission_reward60(Combat*g,const CombatMob*m){
 ExpandedState60*s=&g->expanded60;if(g->jobId!=J60_TAEKWON||m->training||!s->missionSource||s->missionSource!=(unsigned)mobSpecs[m->kind].id)return;
 if(++s->missionCount>=100){if(s->missionScore<1000000000)s->missionScore++;s->missionSource=taekwon_mission_pick60(g,0);s->missionCount=0;}
}
