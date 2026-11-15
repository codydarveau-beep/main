/* Distance-driven source walk cadence for the five expanded class bodies.
 * ACT milliseconds = cells * 4.6 * .37 * 4 * 25. Body/hair share elapsed.
 * Cosmetic state only: no changes to movement, collision, saves or RNG. */
#ifndef MYRO_WALK_PHASE62_H
#define MYRO_WALK_PHASE62_H
#include <math.h>
typedef struct{float x,y,time,elapsed;unsigned map,job,ready;}WalkPhase62;
static float walk_phase62(WalkPhase62*s,float x,float y,float time,unsigned map,unsigned job,int moving){
 if(!s->ready||s->map!=map||s->job!=job||time<s->time){*s=(WalkPhase62){x,y,time,0,map,job,1};return 0;}
 float dx=x-s->x,dy=y-s->y,d=hypotf(dx,dy);s->x=x;s->y=y;s->time=time;
 if(!moving)s->elapsed=0;else if(isfinite(d)&&d<=32)s->elapsed=fmodf(s->elapsed+d*(.1702f/8.f),1024.f);else s->elapsed=0;
 return s->elapsed;
}
#endif
