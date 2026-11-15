/* Original elemental choice: learned skills, strict tie order, no cheaper fallback. */
#ifndef MYRO_COMPANION_BOLT_CHOICE204_H
#define MYRO_COMPANION_BOLT_CHOICE204_H
#include "companion_skill_cost201.h"
static unsigned party_choose_bolt_values204(const unsigned ranks[3],const int rates[3],unsigned sp,unsigned*outRank){static const unsigned skills[3]={3,9,21};unsigned best=0;int score=ranks[0]&&rates[0]>=0?rates[0]:-1;for(unsigned i=1;i<3;i++)if(ranks[i]&&rates[i]>score){best=i;score=rates[i];}if(score<=0)return 0;unsigned rank=ranks[best]?ranks[best]:1;if(sp<party_skill_base_cost201(skills[best],rank))return 0;*outRank=rank;return skills[best];}
#endif
