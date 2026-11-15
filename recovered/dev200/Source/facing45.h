/* MIT. Screen-space octants with a seven-degree hysteresis at sprite boundaries. */
#ifndef MYRO_FACING45_H
#define MYRO_FACING45_H
typedef struct {int ready,dir;unsigned life,map;} Facing45;
static int facing_stable45(Facing45*t,unsigned map,unsigned life,float fx,float fy,float co,float si){float a=atan2f(-(co*fx+si*fy),si*fx-co*fy),centre=t->dir*.7853981634f,delta=remainderf(a-centre,6.283185307f);if(!t->ready||t->map!=map||t->life!=life||fabsf(delta)>.512699082f){t->dir=((int)floorf(a/.7853981634f+.5f)+8)%8;t->ready=1;t->map=map;t->life=life;}return t->dir;}
#endif
