/* MIT. One personal hireling; durable integers are stored in the NPC character bundle. */
#ifndef MYRO_MERCENARY_STATE180_H
#define MYRO_MERCENARY_STATE180_H
#include "mercenary_data180.h"
typedef struct{
 unsigned source,hp,sp,remaining,kills,faith[3],calls[3],hold,bonusLevel[5],bonusMS[5];
 float x,y,faceX,faceY,attackAt,attackUntil,nextAttack,hurtAt,regenAt,stuck,castUntil,cooldown[37],buffUntil[37],potionUntil;
 unsigned map,moving,castSkill,castRank,castLife,potionRank,pendingLife,pendingSkill,pendingRank,pendingHits;
 int target,castTarget,pendingTarget;float impactAt,shotAt,shotEnd,shotX,shotY,shotToX,shotToY;
 unsigned frenzy180,frenzyDrain180;float frenzyNext180,regenBlocked180;
}Mercenary180;
static const MercenaryData180*mercenary_data180(unsigned source){return source>=6017&&source<=6046?mercenaryData180+source-6017:NULL;}
static unsigned mercenary_guild180(unsigned source){return source<6027?0:source<6037?1:2;}
static unsigned mercenary_maxhp180(const Mercenary180*m){const MercenaryData180*d=mercenary_data180(m->source);return d?d->hp*(100+(m->bonusMS[2]?5*m->bonusLevel[2]:0))*(m->frenzy180?3:1)/100:0;}
static unsigned mercenary_maxsp180(const Mercenary180*m){const MercenaryData180*d=mercenary_data180(m->source);return d?d->sp*(100+(m->bonusMS[3]?5*m->bonusLevel[3]:0))/100:0;}
#endif
