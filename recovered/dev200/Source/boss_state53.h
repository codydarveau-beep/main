/* MIT. Fixed-capacity dead-spawn deadlines, absolute UTC seconds. */
#ifndef MYRO_BOSS_STATE53_H
#define MYRO_BOSS_STATE53_H
#include "boss_keys53.h"
typedef struct {uint64_t until[BOSS_COUNT53];} BossState53;
static uint64_t bossNow53;
static void boss_clock53(uint64_t now){bossNow53=now;}
static void boss_capture53(BossState53*to,const BossState53*from){for(unsigned i=0;i<BOSS_COUNT53;i++){uint64_t u=from->until[i];to->until[i]=u>bossNow53?(u-bossNow53>600?bossNow53+600:u):0;}}
static void boss_tick_state53(BossState53*s,uint64_t*seen){if(*seen==bossNow53)return;for(unsigned i=0;i<BOSS_COUNT53;i++){uint64_t u=s->until[i];if(!u)continue;if(*seen&&bossNow53<*seen){uint64_t left=u>*seen?u-*seen:0;s->until[i]=left?bossNow53+(left>600?600:left):0;}else if(u<=bossNow53)s->until[i]=0;}*seen=bossNow53;}
#endif
