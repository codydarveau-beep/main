/* GPL-3.0-or-later. Source billboard animation parameters, without heap particles. */
#ifndef MYRO_NPC_PARTICLE_POSE180_H
#define MYRO_NPC_PARTICLE_POSE180_H
#include <math.h>
#include <stdint.h>
#include "npc_particle_data180.h"
typedef struct{float x,y,z,w,h,offsetX,offsetY,angle,alpha;unsigned texture,overlay,additive;}NpcParticlePose180;
static float npp180(const NpcParticle180*n,unsigned key,float fallback){float v=n->p[key];return isfinite(v)?v:fallback;}
static uint32_t npc_particle_hash180(uint32_t x){x^=x>>16;x*=0x7feb352du;x^=x>>15;x*=0x846ca68bu;return x^(x>>16);}
static float npc_particle_random180(unsigned seed,unsigned channel,float lo,float hi,int integer){float p=(npc_particle_hash180(seed+channel*0x9e3779b9u)&0xffffffu)/16777216.f;if(integer){lo=ceilf(lo);hi=floorf(hi);return lo+floorf(p*fmaxf(1,hi-lo+1));}return lo+(hi-lo)*p;}
static float npc_particle_pair180(const NpcParticle180*n,unsigned lo,unsigned hi,float fallback,unsigned seed,unsigned channel){float a=npp180(n,lo,-INFINITY),b=npp180(n,hi,-INFINITY);return isfinite(a)&&isfinite(b)?npc_particle_random180(seed,channel,a,b,n->kind==2):fallback;}
static unsigned npc_particle_copies180(const NpcParticle180*n){float count=npp180(n,NP180_duplicate,1);return count<1?1:count>32?32:(unsigned)count;}
static unsigned npc_particle_lifetime180(unsigned id){unsigned end=0;for(unsigned i=0;i<sizeof(npcParticles180)/sizeof(*npcParticles180);i++){const NpcParticle180*n=npcParticles180+i;if(n->id!=id)continue;unsigned duration=(unsigned)fmaxf(1,npp180(n,NP180_durationRandHi,npp180(n,NP180_duration,1000)));unsigned last=(unsigned)fmaxf(0,npp180(n,NP180_delayStart,0))+(npc_particle_copies180(n)-1)*(unsigned)fmaxf(0,npp180(n,NP180_timeBetweenDupli,200))+duration;if(n->kind!=3&&npp180(n,NP180_repeat,0))last=30000;if(last>end)end=last;}return end>30000?30000:end;}
static int npc_particle_pose180(const NpcParticle180*n,unsigned age,unsigned copy,unsigned seed,unsigned created,NpcParticlePose180*out){
 if(copy>=npc_particle_copies180(n)||!n->count)return 0;seed=npc_particle_hash180(seed+copy*7919u);
 float duration=npc_particle_pair180(n,NP180_durationRandLo,NP180_durationRandHi,npp180(n,NP180_duration,1000),seed,1);if(duration<1)return 0;
 float delay=fmaxf(0,npp180(n,NP180_delayStart,0))+copy*fmaxf(0,npp180(n,NP180_timeBetweenDupli,200));float elapsed=(float)age-delay;if(elapsed<0)return 0;
 if(elapsed>=duration){if(n->kind!=3&&npp180(n,NP180_repeat,0))elapsed=fmodf(elapsed,duration);else return 0;}
 float p=elapsed/duration,ease=log10f(1+9*p),start[3],end[3],position[3];
 static const unsigned base[3]={NP180_posx,NP180_posy,NP180_posz},from[3]={NP180_posxStart,NP180_posyStart,NP180_poszStart},to[3]={NP180_posxEnd,NP180_posyEnd,NP180_poszEnd};
 static const unsigned same[3]={NP180_posxRand,NP180_posyRand,NP180_poszRand},different[3]={NP180_posxRandDiff,NP180_posyRandDiff,NP180_poszRandDiff};
 static const unsigned fromRand[3]={NP180_posxStartRand,NP180_posyStartRand,NP180_poszStartRand},toRand[3]={NP180_posxEndRand,NP180_posyEndRand,NP180_poszEndRand};
 static const unsigned fromMid[3]={NP180_posxStartRandMiddle,NP180_posyStartRandMiddle,NP180_poszStartRandMiddle},toMid[3]={NP180_posxEndRandMiddle,NP180_posyEndRandMiddle,NP180_poszEndRandMiddle},smooth[3]={NP180_posxSmooth,NP180_posySmooth,NP180_poszSmooth};
 for(unsigned axis=0;axis<3;axis++){
  start[axis]=npp180(n,from[axis],0);end[axis]=npp180(n,to[axis],0);float value=npp180(n,base[axis],-INFINITY);if(isfinite(value))start[axis]=end[axis]=value;
  float radius=npp180(n,same[axis],0);if(radius)start[axis]=end[axis]=npc_particle_random180(seed,10+axis,-radius,radius,n->kind==2);
  radius=npp180(n,different[axis],0);if(radius){start[axis]=npc_particle_random180(seed,20+axis,-radius,radius,n->kind==2);end[axis]=npc_particle_random180(seed,30+axis,-radius,radius,n->kind==2);}
  radius=npp180(n,fromRand[axis],0);if(radius){float middle=npp180(n,fromMid[axis],0);start[axis]=npc_particle_random180(seed,40+axis,middle-radius,middle+radius,n->kind==2);}
  radius=npp180(n,toRand[axis],0);if(radius){float middle=npp180(n,toMid[axis],0);end[axis]=npc_particle_random180(seed,50+axis,middle-radius,middle+radius,n->kind==2);}
 }
 float retreat=npp180(n,NP180_retreat,0),arc=npp180(n,NP180_arc,0),angle=npc_particle_pair180(n,NP180_angleRandLo,NP180_angleRandHi,npp180(n,NP180_angle,0),seed,70);
 if(npp180(n,NP180_soulStrikePattern,0)){unsigned hit=(unsigned)(created/duration)%5;float a=hit*1.256637061f;start[0]+=cosf(a)*2;start[1]+=sinf(a)*2;retreat*=1+.2f*hit;arc*=1+.1f*hit;angle+=72*hit;}
 for(unsigned axis=0;axis<3;axis++)position[axis]=start[axis]+(end[axis]-start[axis])*(npp180(n,smooth[axis],0)?ease:p);
 float phase=p*6.108652382f*npp180(n,NP180_nbOfRotation,1)-(npp180(n,NP180_rotateLate,0)+copy*npp180(n,NP180_rotateLateDelta,0))*1.570796327f;
 if(npp180(n,NP180_rotatePosX,0)>0)position[0]=npp180(n,NP180_rotatePosX,0)*cosf(phase)*(npp180(n,NP180_rotationClockwise,0)?-1:1);
 if(npp180(n,NP180_rotatePosY,0)>0)position[1]=npp180(n,NP180_rotatePosY,0)*sinf(phase);
 if(retreat){float dx=end[0]-start[0],dy=end[1]-start[1],distance=sqrtf(dx*dx+dy*dy);if(distance>.001f){position[0]=start[0]+dx*p-dx/distance*sinf(p*3.141592654f)*retreat;position[1]=start[1]+dy*p-dy/distance*sinf(p*3.141592654f)*retreat;}}
 position[2]+=arc*sinf(p*3.141592654f)+npp180(n,NP180_zOffset,0)+npp180(n,NP180_zOffsetStart,0)*(1-p);
 if(npp180(n,NP180_circlePattern,0)){float radius=npp180(n,NP180_circleInnerSize,0),outer=npc_particle_pair180(n,NP180_circleOuterSizeRandLo,NP180_circleOuterSizeRandHi,radius,seed,71);radius+=(outer-radius)*p;position[0]+=cosf(angle*.01745329252f)*radius;position[1]+=sinf(angle*.01745329252f)*radius;}
 float size=npp180(n,NP180_size,1),delta=copy*npp180(n,NP180_sizeDelta,0),sx=npp180(n,NP180_sizeStart,size+delta),sy=sx,ex=npp180(n,NP180_sizeEnd,size+delta),ey=ex;
 sx=npp180(n,NP180_sizeStartX,npp180(n,NP180_sizeX,sx));sy=npp180(n,NP180_sizeStartY,npp180(n,NP180_sizeY,sy));ex=npp180(n,NP180_sizeEndX,npp180(n,NP180_sizeX,ex));ey=npp180(n,NP180_sizeEndY,npp180(n,NP180_sizeY,ey));
 float radius=npp180(n,NP180_sizeRand,0);if(radius)sx=sy=ex=ey=size+npc_particle_random180(seed,80,-radius,radius,0);
 radius=npp180(n,NP180_sizeRandX,0);if(radius){float middle=npp180(n,NP180_sizeRandXMiddle,100);sx=ex=npc_particle_random180(seed,81,middle-radius,middle+radius,0);}
 radius=npp180(n,NP180_sizeRandY,0);if(radius){float middle=npp180(n,NP180_sizeRandYMiddle,100);sy=ey=npc_particle_random180(seed,82,middle-radius,middle+radius,0);}
 sx=npc_particle_pair180(n,NP180_sizeRandStartXLo,NP180_sizeRandStartXHi,sx,seed,83);sy=npc_particle_pair180(n,NP180_sizeRandStartYLo,NP180_sizeRandStartYHi,sy,seed,84);ex=npc_particle_pair180(n,NP180_sizeRandEndXLo,NP180_sizeRandEndXHi,ex,seed,85);ey=npc_particle_pair180(n,NP180_sizeRandEndYLo,NP180_sizeRandEndYHi,ey,seed,86);
 float q=npp180(n,NP180_sizeSmooth,0)?ease:p;float width=sx+(ex-sx)*q,height=sy+(ey-sy)*q;
 if(npp180(n,NP180_rotate,0))angle+=(npp180(n,NP180_toAngle,0)-angle)*p;
 if(npp180(n,NP180_rotateToTarget,0))angle+=90-atan2f(end[1]-start[1],end[0]-start[0])*57.29577951f;
 float alpha=fminf(1,fmaxf(0,npp180(n,NP180_alphaMax,1)+copy*npp180(n,NP180_alphaMaxDelta,0)));
 if(npp180(n,NP180_fadeIn,0)&&p<.25f)alpha*=p*4;else if(npp180(n,NP180_fadeOut,0)&&p>.75f)alpha*=(1-p)*4;else if(npp180(n,NP180_sparkling,0))alpha*=.5f+.5f*cosf(p*19.19862177f*npp180(n,NP180_sparkNumber,1));
 unsigned index=0;if(n->count>1&&(!n->sprite||n->kind==3||npp180(n,NP180_playSprite,0)))index=(unsigned)(elapsed/fmaxf(1,npp180(n,NP180_frameDelay,npp180(n,NP180_delayFrame,n->ms))))%n->count;
 unsigned texture=npcParticleFrames180[n->first+index];const NpcParticleTexture180*t=npcParticleTextures180+texture;
 *out=(NpcParticlePose180){position[0],position[1],position[2],width*t->planeW,height*t->planeH,width*t->offsetX,height*t->offsetY+npp180(n,NP180_yOffset,0),angle,fmaxf(0,alpha),texture,npp180(n,NP180_overlay,0)!=0,(int)npp180(n,NP180_blendMode,0)==2};
 return out->alpha>0&&out->w!=0&&out->h!=0;
}
#endif
