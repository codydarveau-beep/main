/* Original skill costs, Kaina and Meditation; only the acting ally pays. */
#ifndef MYRO_COMPANION_SKILL_COST201_H
#define MYRO_COMPANION_SKILL_COST201_H
#include "combat.h"
#include "companion_skills201.h"
static unsigned party_skill_base_cost201(unsigned skill,unsigned rank){if(rank<1)rank=1;if(rank>10)rank=10;if(skill<127)return classicCosts164[skill][rank-1];const ClassSkill50*d=class_skill_data50(skill);return d?d->sp[rank-1]:0;}
static unsigned party_skill_cost_values201(unsigned id,unsigned job,unsigned jobLevel,unsigned level,unsigned skill,unsigned rank){unsigned cost=party_skill_base_cost201(skill,rank);if(skill>=438&&skill<=440){unsigned rate=level>=90?7:level>=80?5:level>=70?3:0;cost-=cost*rate*party_skill_path_rank201(id,job,jobLevel,437)/100;}return cost*(100-4*party_skill_path_rank201(id,job,jobLevel,279))/100;}
#endif
