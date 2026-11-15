/* MIT. Quest job advancement retains the first-job skill investment. */
#ifndef MYRO_NPC_JOB_CHANGE55_H
#define MYRO_NPC_JOB_CHANGE55_H
#include "npc_identity55.h"
static int(*campaignJobGuard200)(Combat*,unsigned);
static int npc_first_job55(unsigned job){return job==J60_TAEKWON||job>=1&&job<=6||job>=J52_HIGH_SWORDSMAN&&job<=J52_HIGH_MERCHANT;}
static int npc_job_binding55(const Combat*g,unsigned id){if(id>=SKILL_COUNT||!id)return 1;int k=skill_rank_index(id);return k>=0&&g->ranks[k]>0;}
static int npc_change_job55(Combat*g,unsigned job){
 if(!job_valid52(job)||g->hp<=0)return 0;if(campaignJobGuard200&&!campaignJobGuard200(g,job))return 0;if(job==g->jobId)return 1;
 if((g->jobId==0||g->jobId==J52_HIGH_NOVICE)&&job!=0&&(g->joblevel<10||g->ranks[310]<9))return 0;
 int advance=npc_first_job55(g->jobId)&&!npc_first_job55(job)&&!job_high_first52(job)&&job!=J52_SUPER_NOVICE&&npc_base_class55(g->jobId)==npc_base_class55(job)&&job_transcendent52(g->jobId)==job_transcendent52(job);
 unsigned carry=advance?g->jobSkillCarry55+g->joblevel-1:0;if(carry>49)return 0;
 unsigned char ranks[LEARN_COUNT],uses[LEARN_COUNT];SkillBinding50 hotbar[12];int points=g->skillPoints;unsigned rb=g->rbBinding,quickKind=g->quickKind,quickId=g->quickId;memcpy(ranks,g->ranks,sizeof(ranks));memcpy(uses,g->useRanks45,sizeof(uses));memcpy(hotbar,g->hotbar,sizeof(hotbar));
 if(!combat_change_job(g,job))return 0;
 if(advance){g->jobSkillCarry55=carry;g->skillPoints=points;for(unsigned i=0;i<LEARN_COUNT;i++)if(job_owns_skill48(job,learnJobs[i],learnIds[i])){g->ranks[i]=ranks[i];g->useRanks45[i]=uses[i];}for(unsigned i=0;i<12;i++){unsigned id=hotbar[i];if(npc_job_binding55(g,id))g->hotbar[i]=hotbar[i];}if(npc_job_binding55(g,rb))g->rbBinding=rb;if(quickKind!=1||npc_job_binding55(g,quickId)){g->quickKind=quickKind;g->quickId=quickId;}stat_refresh(g);}
 combat_message(g,"Now %s.",job_name(job));return 1;
}
#endif
