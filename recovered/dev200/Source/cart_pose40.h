/* MIT. Cart keeps an adjustable ground separation; source wheel contact meets terrain.
 * Depth is sorted with actors. Idle elapsed is zero: source only has walk cycles.
 */
#include "cart_contact40.h"
typedef struct{float x,y,sx,sy,depth,elapsed;unsigned style;int dir;} CartPose40;
static int cart_pose40(const Combat*g,const float*m,float zoom,int dir,float(*height)(float,float),CartPose40*p){if(!g->cartOwned||g->jobId!=6||g->hp<=0||dir<0||dir>7)return 0;float d=sqrtf(g->faceX*g->faceX+g->faceY*g->faceY),fx=d>.001f?g->faceX/d:0,fy=d>.001f?g->faceY/d:1;float distance=13;p->x=g->x-fx*distance;p->y=g->y-fy*distance;p->style=g->cartStyle<0?0:g->cartStyle>4?4:g->cartStyle;p->dir=dir;float z=height(p->x,p->y);world_project(m,p->x,p->y,z,&p->sx,&p->sy);p->sx+=(64-cartContact40[p->style][dir][0])*zoom/3;p->sy+=(90-cartContact40[p->style][dir][1])*zoom/3;p->depth=m[8]*p->x+m[9]*p->y+m[10]*z+m[11]-WORLD_SPRITE_BIAS;p->elapsed=g->moving?g->time:0;return 1;}
