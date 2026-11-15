/* SPDX-License-Identifier: MIT. Shared screen projection and 24-bit depth space. */
#ifndef MYRO_PROJECTION_H
#define MYRO_PROJECTION_H
#include <math.h>
#define WORLD_DEPTH_CENTRE 8388608.0f
#define WORLD_DEPTH_SCALE 2048.0f
#define WORLD_SPRITE_BIAS 256.0f
static void world_camera(float m[16],float x,float y,float z,float yaw,float tilt,float zoom){
 float co=cosf(yaw),si=sinf(yaw),ct=cosf(tilt),sn=sinf(tilt),d=WORLD_DEPTH_SCALE;
 m[0]=zoom*co;m[1]=zoom*si;m[2]=0;m[3]=320-zoom*(co*x+si*y);
 m[4]=zoom*ct*si;m[5]=-zoom*ct*co;m[6]=-zoom*sn;m[7]=245-zoom*ct*(si*x-co*y)+zoom*sn*z;
 m[8]=-d*sn*si;m[9]=d*sn*co;m[10]=-d*ct;m[11]=WORLD_DEPTH_CENTRE+d*sn*si*x-d*sn*co*y+d*ct*z;
 m[12]=1;m[13]=m[14]=m[15]=0;
}
static void world_project(const float*m,float x,float y,float z,float*px,float*py){*px=m[0]*x+m[1]*y+m[3];*py=m[4]*x+m[5]*y+m[6]*z+m[7];}
/* Shared with the actual gpu_sprite vertex submission and host regression. */
static void sprite_screen_rect(float x,float y,float scale,unsigned ax,unsigned ay,unsigned height,float*r){r[0]=x-ax*scale;r[1]=y-ay*scale;r[2]=128*scale;r[3]=height*scale;}
/* Characters stand upright in world Z. A constant-depth screen rectangle lets
 * a wall's raised vertices hide the head even when its base is behind the feet.
 * Convert vertical screen displacement back to height at the actor's XY. */
/* The camera matrix already contains this ratio; compute it once per frame. */
static float sprite_depth_slope50(const float*m){return m[10]/m[6];}
static float sprite_upright_cached50(float footDepth,float screenY,float footY,float slope){return footDepth+(screenY-footY)*slope;}
static float sprite_upright_depth50(float footDepth,float screenY,float footY,float cameraZoom,float tilt){return footDepth+(screenY-footY)*WORLD_DEPTH_SCALE/(cameraZoom*tanf(tilt));}
/* Expanded translucent death copies are source screen-space fades, rather than
 * upright bodies. Keep their original foot depth so terrain cannot slice them. */
static void sprite_depth_corners50c(float depth,float top,float bottom,float foot,float slope,int sourceFade,float*out){
 out[0]=sourceFade?depth:sprite_upright_cached50(depth,top,foot,slope);
 out[1]=sourceFade?depth:sprite_upright_cached50(depth,bottom,foot,slope);
}
#endif
