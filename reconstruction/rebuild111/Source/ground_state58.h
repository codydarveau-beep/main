/* Bounded session-world floor items; no texture allocation per drop. */
#ifndef MYRO_GROUND_STATE58_H
#define MYRO_GROUND_STATE58_H
#define GROUND_ITEMS58 8192u
typedef struct{unsigned source,count,map,life;float x,y,createdAt60,skipUntil60;}GroundItem58;
static GroundItem58 groundItems58[GROUND_ITEMS58];static unsigned groundUsed58,groundLife58,autoLootOff58;
static void ground_clear58(void){memset(groundItems58,0,groundUsed58*sizeof(*groundItems58));groundUsed58=0;}
#endif
