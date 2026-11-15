/* SPDX-License-Identifier: MIT. Real projection math; not a GPU simulation. */
#include <assert.h>
#include <stdio.h>
#include "projection.h"
#include "scenery_format.h"
static float project(const float*m,int row,float x,float y,float z){return m[row*4]*x+m[row*4+1]*y+m[row*4+2]*z+m[row*4+3];}
int main(void){
 for(int i=0;i<64;i++)for(int k=0;k<8;k++){
  float yaw=i*.1f,tilt=.52f+k*.08f,m[16],x=1244,y=1476,z=16;world_camera(m,x,y,z,yaw,tilt,1.2f);
  assert(fabsf(project(m,0,x,y,z)-320)<.001f);assert(fabsf(project(m,1,x,y,z)-245)<.001f);assert(fabsf(project(m,2,x,y,z)-WORLD_DEPTH_CENTRE)<=4);
  // A roof directly on the same screen point must hide the character.
  float h=120,shift=tanf(tilt)*h,rx=x+sinf(yaw)*shift,ry=y-cosf(yaw)*shift,rz=z+h;
  assert(fabsf(project(m,0,rx,ry,rz)-320)<.002f);assert(fabsf(project(m,1,rx,ry,rz)-245)<.002f);
  assert(project(m,2,rx,ry,rz)<WORLD_DEPTH_CENTRE-WORLD_SPRITE_BIAS);
  // Shared-model composition retains the same camera depth and range.
  SceneInstance in={0};in.matrix[0]=1;in.matrix[5]=1;in.matrix[10]=1;in.matrix[3]=rx;in.matrix[7]=ry;in.matrix[11]=rz;float combined[16];scene_matrix(combined,m,&in);
  assert(fabsf(combined[11]-project(m,2,rx,ry,rz))<=4);assert(combined[11]>0&&combined[11]<16777215);
 }
 puts("PASS camera centre, rotation/tilt, overhead occlusion depth, shared instance composition and 24-bit range");return 0;
}
