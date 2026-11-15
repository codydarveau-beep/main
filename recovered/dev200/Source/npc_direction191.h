/* MIT. Server0=N,1=NW; ACT0=S,1=SW. Original client maps4,3,2,1,0,7,6,5. */
#ifndef MYRO_NPC_DIRECTION191_H
#define MYRO_NPC_DIRECTION191_H
static unsigned npc_direction191(unsigned server,float co,float si){float a=(server&7)*.7853981634f,fx=-sinf(a),fy=cosf(a),sx=co*fx+si*fy,sy=si*fx-co*fy;return((int)floorf(atan2f(-sx,sy)*4/3.14159265f+.5f)+8)%8;}
#endif
