/* MIT. Source 40Hz GR2 clocks, independent of 2D attack/hurt compression.
 * The source side views and attack lunge face local -Y, not +Y. */
#include "guardian_origin53.h"
typedef struct {unsigned map,life,group;float since,x,y,fx,fy;int ready;float attackSince64,lastAttack64,hurtSince164,lastHurt164;} GuardianMotion53;
typedef struct {unsigned group;float elapsed,fx,fy;int repeat;} GuardianPose53;
static GuardianMotion53 guardianMotion53[MOB_COUNT];
static float guardian_attack_rate164(const Combat*g,const CombatMob*m,unsigned bank){const unsigned(*groups)[3]=bank==8?guardianGroups8:guardianGroups7;return fmaxf(groups[2][2]*.001f,groups[2][1]*.025f)/fmaxf(.05f,combat_enemy_delay164(g,m));}

static GuardianPose53 guardian_motion_rate162(GuardianMotion53*s,const Combat*g,const CombatMob*m,unsigned bank,float attackRate){
 const unsigned(*groups)[3]=bank==8?guardianGroups8:guardianGroups7;float attackSpan162=fmaxf(groups[2][2]*.001f,groups[2][1]*.025f)/(attackRate>0?attackRate:1);
 if(!s->ready||s->map!=g->mapId||s->life!=m->life){*s=(GuardianMotion53){g->mapId,m->life,0,g->time,m->x,m->y,m->faceX,m->faceY,1,-100,-100,-100,-100};}
 /* A new hit must not restart the opening frames of a GR2 swing in progress. */
 if(m->attackAt>s->lastAttack64){s->lastAttack64=m->attackAt;if(g->time-s->attackSince64>=attackSpan162){float previousEnd=s->attackSince64+attackSpan162;s->attackSince64=m->attackAt-previousEnd<.25f?previousEnd:m->attackAt;}}
 if(m->hurtAt>s->lastHurt164){s->lastHurt164=m->hurtAt;if(g->time-s->hurtSince164>=.24f)s->hurtSince164=m->hurtAt;}
 unsigned group=0;float elapsed=0;int repeat=1;float fx=m->faceX,fy=m->faceY;
 if(m->hp<=0){group=4;elapsed=fmaxf(0,g->time-m->deadAt)*fmaxf(groups[4][2]*.001f,groups[4][1]*.025f);repeat=0;}
 else if(m->frozenLeft>0||m->stoneLeft>0){group=0;elapsed=0;repeat=0;}
 else if(g->time-s->attackSince64>=0&&g->time-s->attackSince64<attackSpan162){group=2;elapsed=(g->time-s->attackSince64)*attackRate;repeat=0;}
 else if(m->moving){group=1;float dx=m->x-s->x,dy=m->y-s->y;if(dx*dx+dy*dy>.00001f&&dx*dx+dy*dy<256){float d=sqrtf(dx*dx+dy*dy);fx=dx/d;fy=dy/d;}}
 else if(g->time-s->hurtSince164>=0&&g->time-s->hurtSince164<.24f){group=3;elapsed=(g->time-s->hurtSince164)*groups[3][2]*.001f/.24f;repeat=0;}
 if(group!=s->group){s->group=group;s->since=g->time;}
 if(repeat)elapsed=g->time-s->since;
 if(fx*fx+fy*fy<.00001f){fx=s->fx;fy=s->fy;}s->x=m->x;s->y=m->y;s->fx=fx;s->fy=fy;
 return(GuardianPose53){group,elapsed,fx,fy,repeat};
}
static GuardianPose53 guardian_motion53(GuardianMotion53*s,const Combat*g,const CombatMob*m,unsigned bank){return guardian_motion_rate162(s,g,m,bank,1.f);}
static unsigned guardian_frame53(const unsigned*g,float elapsed,int repeat){float time=fmaxf(0,elapsed);if(repeat&&g[2])time=fmodf(time,g[2]*.001f);unsigned frame=(unsigned)(time*40.f+.0001f);if(frame>=g[1])frame=g[1]-1;return g[0]+frame;}
static void guardian_yaw53(float fx,float fy,float*co,float*si){float angle=atan2f(fy,fx)+1.570796327f;*co=cosf(angle);*si=sinf(angle);}

static void guardian_local53(unsigned bank,const float*v,float*x,float*y){unsigned i=bank-7;*x=v[0]-guardianOrigin53[i][0];*y=v[1]-guardianOrigin53[i][1];}
