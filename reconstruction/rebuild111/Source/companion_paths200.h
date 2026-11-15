/* Original per-person stat priorities and story/growth promotion rules. */
#ifndef MYRO_COMPANION_PATHS200_H
#define MYRO_COMPANION_PATHS200_H
#include "companion_progress200.h"
#include "job_identity52.h"
#include "solo_tables53.h"
#include "companion_paths_data200.h"
static unsigned party_growth_promotion200(unsigned id,unsigned job,unsigned jobLevel,unsigned cursor){if(id>=19||cursor<15)return job;unsigned target=job;if(id==1&&job==1)target=11;else if(id==4&&job==3)target=17;else if(id==2&&job==2)target=9;else if(id==7&&job==4)target=13;else if(cursor>=27&&id<13&&job==partyFinalJobs200[id])target=partyPromotedJobs200[id];if(target==job||jobLevel<(job==8?70u:50u))return job;return target;}
static int party_growth_stats200(unsigned id,unsigned job,unsigned level,unsigned char stats[6],unsigned*hp,unsigned*sp){if(id>=19||job>=J52_COUNT)return 0;if(level<1)level=1;if(level>250)level=250;memset(stats,1,6);int budget=soloStatBudget53[level-1]+(level==250?2:0);unsigned cursor=0,skips=0;while(budget>=2&&skips<12){unsigned stat=partyStatPaths200[id][cursor++%12],cost=1+(stats[stat]+9)/10;if(stats[stat]<150&&budget>=(int)cost){stats[stat]++;budget-=(int)cost;skips=0;}else skips++;}if(!job)job=partyInitialJobs200[id];uint64_t baseHP=solojobHP52[job][level-1],baseSP=solojobSP52[job][level-1];baseHP+=baseHP*stats[2]/100;baseSP+=baseSP*stats[3]/100;*hp=baseHP<1?1:baseHP>20000000?20000000:(unsigned)baseHP;*sp=baseSP<1?1:baseSP>20000000?20000000:(unsigned)baseSP;return 1;}
#endif
