/* Native companion EXP and level rules; no player-stat mirroring. */
#ifndef MYRO_COMPANION_EXPERIENCE200_H
#define MYRO_COMPANION_EXPERIENCE200_H
#include "combat.h"
#include "companion_paths200.h"
static int party_growth_gain200(PartyGrowth200*m,unsigned id,int base,int job,unsigned baseRate,unsigned jobRate){if(id>=19||!party_growth_valid200(m))return 0;unsigned oldLevel=m->level;uint64_t be=(uint64_t)m->exp+(unsigned)solo_exp_rate164(base,(int)m->level,baseRate),je=(uint64_t)m->jobExp+(unsigned)solo_exp_rate164(job,(int)m->level,jobRate);m->exp=be>INT_MAX?INT_MAX:(unsigned)be;m->jobExp=je>INT_MAX?INT_MAX:(unsigned)je;const int*bc=progression_base_curve43(m->job),*jc=progression_job_curve43(m->job);unsigned cap=(unsigned)progression_job_cap43(m->job);while(m->level<250&&bc[m->level-1]>0&&m->exp>=(unsigned)bc[m->level-1]){m->exp-=(unsigned)bc[m->level-1];m->level++;}while(m->jobLevel<cap&&jc[m->jobLevel-1]>0&&m->jobExp>=(unsigned)jc[m->jobLevel-1]){m->jobExp-=(unsigned)jc[m->jobLevel-1];m->jobLevel++;}if(m->level==250)m->exp=0;if(m->jobLevel==cap)m->jobExp=0;if(m->level!=oldLevel){unsigned char stats[6];if(!party_growth_stats200(id,m->job,m->level,stats,&m->hp,&m->sp))return 0;}return 1;}
#endif
