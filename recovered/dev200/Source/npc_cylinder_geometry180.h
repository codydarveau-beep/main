/* GPL-3.0-or-later. Original client cylinder animation parameters, native geometry. */
#ifndef MYRO_NPC_CYLINDER_GEOMETRY180_H
#define MYRO_NPC_CYLINDER_GEOMETRY180_H
#include <math.h>
#include "npc_cylinder_data180.h"
typedef struct{float bottom,top,height,alpha;}NpcCylinderPose180;
static unsigned npc_cylinder_lifetime180(unsigned id){unsigned end=0;for(unsigned i=0;i<sizeof(npcCylinders180)/sizeof(*npcCylinders180);i++){const NpcCylinder180*c=npcCylinders180+i;if(c->id!=id)continue;unsigned n=c->delay+c->duration+(c->count-1)*c->gap;if(c->flags&32)n=30000;if(n>end)end=n;}return end;}
static int npc_cylinder_pose180(const NpcCylinder180*c,unsigned age,NpcCylinderPose180*out){
 if(age>=c->duration||!c->duration)return 0;float p=(float)age/c->duration,ramp=fminf(1,age/(float)(c->duration>1000?1000:c->duration));
 *out=(NpcCylinderPose180){c->bottom,c->top,c->height,c->alpha};
 switch(c->animation){case 1:out->height*=ramp;break;case 2:out->top*=ramp;break;case 3:out->bottom*=1-p;out->top*=1-p;out->height*=p<.5f?p*2:(1-p)*2;break;case 4:out->bottom*=p;out->top*=p;break;case 5:out->height*=p<.5f?p*2:(1-p)*2;break;default:break;}
 if(c->flags&1)out->alpha*=p<.25f?p*4:p>.75f?(1-p)*4:1;else if(c->flags&2)out->alpha*=1-p;
 return out->alpha>0;
}
/* Build one source vertex in cells, then convert to native eight-unit cells.
   Camera-facing effects use the current camera basis instead of a baked view. */
static void npc_cylinder_point180(const NpcCylinder180*c,const NpcCylinderPose180*p,unsigned side,unsigned upper,float angle,float randomAngle,const float*m,float*out){
 float a=(float)side*6.283185307f/c->total+angle,r=upper?p->top:p->bottom;
 float x=sinf(a)*r,y=cosf(a)*r,z=upper?p->height:0;
 float tilt=c->angleX*.01745329252f,ct=cosf(tilt),st=sinf(tilt),v=y;
 y=y*ct+z*st;z=z*ct-v*st;
 if(c->angleRandom){float ra=randomAngle*.01745329252f,cr=cosf(ra),sr=sinf(ra);v=x;x=x*cr-z*sr;z=v*sr+z*cr;}
 float zoom=sqrtf(m[0]*m[0]+m[1]*m[1]),co=zoom>0?m[0]/zoom:1,si=zoom>0?m[1]/zoom:0;
 if(c->flags&8){float sn=zoom>0?fminf(1,fmaxf(-1,-m[6]/zoom)):1,ctilt=sqrtf(fmaxf(0,1-sn*sn));z+=c->posZ;out[0]=(co*x+si*sn*y-si*ctilt*z)*8;out[1]=(si*x-co*sn*y+co*ctilt*z)*8;out[2]=(ctilt*y+sn*z)*8;}
 else{if(c->flags&16){v=x;x=co*x-si*y;y=si*v+co*y;}out[0]=x*8;out[1]=y*8;out[2]=(z+c->posZ)*8;}
}
#endif
