/* SPDX-License-Identifier: MIT. Shared bounds/format logic, host-testable. */
#ifndef MYRO_SCENERY_FORMAT_H
#define MYRO_SCENERY_FORMAT_H
#include <stdint.h>
#include <math.h>
#include <string.h>
typedef struct {uint32_t start,count;} SceneModel;
typedef struct {uint32_t model;float matrix[12],bounds[6];} SceneInstance;
typedef struct {unsigned models,count[2];SceneModel*model;SceneInstance*instances[2];} SceneData;
static int scene_metadata(SceneData*s,unsigned char*raw,unsigned size,unsigned vertices){
 if(size<12||sizeof(SceneInstance)!=76||sizeof(SceneModel)!=8)return 0;
 uint32_t m,n0,n1;memcpy(&m,raw,4);memcpy(&n0,raw+4,4);memcpy(&n1,raw+8,4);
 if(m>1024||n0>10000||n1>10000||size!=12+m*8+(n0+n1)*76||(!m&&(n0||n1||vertices)))return 0;
 SceneData d={0};d.models=m;d.count[0]=n0;d.count[1]=n1;d.model=(SceneModel*)(raw+12);d.instances[0]=(SceneInstance*)(raw+12+m*8);d.instances[1]=d.instances[0]+n0;
 for(unsigned i=0;i<m;i++){SceneModel*a=&d.model[i];if(a->start%3||a->count%3||!a->count||a->start>vertices||a->count>vertices-a->start)return 0;}
 for(unsigned i=0;i<n0+n1;i++){
  SceneInstance*a=d.instances[0]+i;if(a->model>=m)return 0;
  for(int j=0;j<12;j++)if(!isfinite(a->matrix[j]))return 0;
  for(int j=0;j<6;j++)if(!isfinite(a->bounds[j]))return 0;
  for(int j=0;j<3;j++)if(a->bounds[j]>a->bounds[j+3])return 0;
 }
 *s=d;return 1;
}
/* Use distance to the full world AABB, preserving large nearby buildings. */
static int scene_range61(const SceneInstance*a,float x,float y,unsigned cells){if(!cells)return 1;float dx=x<a->bounds[0]?a->bounds[0]-x:x>a->bounds[3]?x-a->bounds[3]:0,dy=y<a->bounds[1]?a->bounds[1]-y:y>a->bounds[4]?y-a->bounds[4]:0,r=cells*8.f;return dx*dx+dy*dy<=r*r;}
static int scene_visible(const SceneInstance*a,const float*m){
 /* The camera projection is affine. Its interval extrema occur at AABB
    corners; summing each signed axis interval gives those same extrema
    without projecting all eight corners. Keep the original boundary test
    within a small rounding margin to prevent objects popping at an edge. */
 float xmin=m[3],xmax=m[3],ymin=m[7],ymax=m[7];
 for(int j=0;j<3;j++){
  float x0=m[j]*a->bounds[j],x1=m[j]*a->bounds[j+3];
  float y0=m[j+4]*a->bounds[j],y1=m[j+4]*a->bounds[j+3];
  xmin+=x0<x1?x0:x1;xmax+=x0>x1?x0:x1;
  ymin+=y0<y1?y0:y1;ymax+=y0>y1?y0:y1;
 }
 /* Fast answer except at the exact clipping boundary; use the former
    arithmetic order there so floating-point rounding cannot change culling. */
 if(fabsf(xmax+4)<.0625f||fabsf(xmin-644)<.0625f||fabsf(ymax+4)<.0625f||fabsf(ymin-484)<.0625f){
  xmin=ymin=1e30f;xmax=ymax=-1e30f;
  for(int k=0;k<8;k++){
   float x=a->bounds[(k&1)?3:0],y=a->bounds[(k&2)?4:1],z=a->bounds[(k&4)?5:2];
   float sx=m[0]*x+m[1]*y+m[2]*z+m[3],sy=m[4]*x+m[5]*y+m[6]*z+m[7];
   if(sx<xmin)xmin=sx;if(sx>xmax)xmax=sx;if(sy<ymin)ymin=sy;if(sy>ymax)ymax=sy;
  }
 }
 return xmax>=-4&&xmin<=644&&ymax>=-4&&ymin<=484;
}
static void scene_matrix(float*out,const float*camera,const SceneInstance*a){
 for(int r=0;r<3;r++)for(int j=0;j<4;j++){
  float n=j==3?camera[r*4+3]:0;
  for(int k=0;k<3;k++)n+=camera[r*4+k]*a->matrix[k*4+j];out[r*4+j]=n;
 }
 out[12]=1;out[13]=out[14]=out[15]=0;
}
#endif
