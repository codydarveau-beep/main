#include "interior_rooms181.h"
/* SPDX-License-Identifier: MIT. Static translucent water, source map heights.
 * One 4 KiB GPU allocation for all maps; no animation or resident water VBO.
 * Opaque terrain/scenery depth clips the shorelines and bridges. */
#include "water_data.h"
#include "water_stream190.h"
#include "water_original190.h"
static void*waterTexture;
static void water_draw(const float*camera,unsigned map){
 if(!water_map_valid51a(map)||!waterMaps[map].count)return;
 if(waterOriginal190&&!waterGpu190)return;
 if(!waterOriginal190&&!waterTexture){waterTexture=gpu_alloc(512);for(int i=0;i<128;i++)((uint32_t*)waterTexture)[i]=0x78569cccu;}
 gpu_depth_state(0);program(1);if(waterOriginal190&&waterGpu190){unsigned width=waterFrames190[waterSettings190[map].type][waterFrame190].width;bindTexture(waterGpu190,width,width,width*4,0x0001122a);}else bindTexture(waterTexture,32,4,128,0x0001122a);
 uint32_t*p=pb_begin();
 p=pb_push1(p,NV097_SET_CULL_FACE_ENABLE,0);p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,0);
 p=pb_push1(p,NV097_SET_DEPTH_TEST_ENABLE,1);p=pb_push1(p,NV097_SET_DEPTH_MASK,0);p=pb_push1(p,NV097_SET_BLEND_ENABLE,1);
 for(int i=0;i<16;i++)p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+i*4,2);
 p=pb_push1(p,NV097_SET_TRANSFORM_CONSTANT_LOAD,96);pb_push(p++,NV097_SET_TRANSFORM_CONSTANT,16);memcpy(p,camera,64);p+=16;pb_end(p);
 if(waterOriginal190&&waterGpu190){water_original_tiles190(camera,map);return;}
 float z=waterMaps[map].z;
 for(unsigned i=waterMaps[map].start,end=i+waterMaps[map].count;i<end;i++){
  const unsigned short*r=waterRects[i];if(!rooms_box181(&interiorRooms181,r[0],r[1],r[2],r[3]))continue;float sx0=1e9f,sy0=1e9f,sx1=-1e9f,sy1=-1e9f;
  for(int k=0;k<4;k++){float x=r[k&1?2:0],y=r[k&2?3:1],sx=camera[0]*x+camera[1]*y+camera[3],sy=camera[4]*x+camera[5]*y+camera[6]*z+camera[7];if(sx<sx0)sx0=sx;if(sx>sx1)sx1=sx;if(sy<sy0)sy0=sy;if(sy>sy1)sy1=sy;}
  if(sx1<0||sy1<0||sx0>640||sy0>480)continue;
  p=pb_begin();p=pb_push1(p,NV097_SET_BEGIN_END,6);
  p=vertex(p,r[0],r[1],z,1,1);p=vertex(p,r[2],r[1],z,1,1);
  p=vertex(p,r[0],r[3],z,1,1);p=vertex(p,r[2],r[3],z,1,1);
  p=pb_push1(p,NV097_SET_BEGIN_END,0);pb_end(p);
 }
}
