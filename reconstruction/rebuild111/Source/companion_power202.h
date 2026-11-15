/* Original authored weapons and melee/ranged stat contribution. */
#ifndef MYRO_COMPANION_POWER202_H
#define MYRO_COMPANION_POWER202_H
#include "combat.h"
#include "companion_weapons202.h"
static unsigned party_power_values202(unsigned id,unsigned strength,unsigned dexterity,unsigned luck){unsigned weapon=id<19?partyWeapons202[id]:0;int item=inventory_catalog52(weapon);unsigned attack=item>=0?(unsigned)itemDefs[item].attack:0;unsigned main=id<16&&(0x8700u&(1u<<id))?dexterity:strength,other=id<16&&(0x8700u&(1u<<id))?strength:dexterity;return main+(main/10)*(main/10)+other/5+luck/5+attack;}
#endif
