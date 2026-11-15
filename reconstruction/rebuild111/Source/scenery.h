/* SPDX-License-Identifier: MIT. Shared static scenery, alpha-tested GPU instances. */
#include "scenery_format.h"
#include "interior_rooms181.h"
static uint8_t*sceneRoomBits181;static unsigned sceneRoomStride181;
static void*sceneTexture,*sceneMesh;static unsigned sceneW,sceneH,sceneVertices;
static unsigned char*sceneMetadataRaw;static SceneData scene;
static void scenery_load(unsigned id){ const WorldBlob*b=worldBlobs[id];
 unsigned scenery1_raw=b[5].raw,scenery2_raw=b[6].raw;
#ifndef MYRO_HOST
 if(b[5].raw>4)world_scenery_atlas171(id);else{sceneTexture=NULL;sceneW=2048;sceneH=0;}
#else
 unsigned char*packed=world_packed(id,4);sceneTexture=gpu_atlas(packed,b[4].packed,b[4].raw,2048,2048,&sceneW,&sceneH);free(packed);
#endif
 if(sceneW!=2048)fail("Scenery atlas width invalid");
 unsigned char*p;
#ifndef MYRO_HOST
 world_scenery_gpu171(id);
#else
 p=world_expand(id,5,"shared scenery geometry");
 if(scenery1_raw<4)fail("Scenery geometry truncated");memcpy(&sceneVertices,p,4);
 if(sceneVertices>100000||sceneVertices%3||scenery1_raw!=4+sceneVertices*20)fail("Scenery geometry invalid");
 for(unsigned i=0;i<sceneVertices*5;i++){float f;memcpy(&f,p+4+i*4,4);if(!isfinite(f))fail("Non-finite scenery vertex");}
 sceneMesh=NULL;if(sceneVertices){sceneMesh=gpu_alloc(sceneVertices*20);memcpy(sceneMesh,p+4,sceneVertices*20);}free(p);
#endif
 sceneMetadataRaw=world_expand(id,6,"scenery instances");
 if(!scene_metadata(&scene,sceneMetadataRaw,scenery2_raw,sceneVertices))fail("Invalid scenery metadata");
 if(!sceneVertices){if(sceneTexture)MmFreeContiguousMemory(sceneTexture);sceneTexture=NULL;sceneW=sceneH=0;}
 const OrdinaryTown52*ordinary52=ordinary_town52(id);if(ordinary52)for(unsigned layer=0;layer<2;layer++){unsigned kept=0;for(unsigned i=0;i<scene.count[layer];i++)if(ordinary_keep52(ordinary52,scene.instances[layer][i].model))scene.instances[layer][kept++]=scene.instances[layer][i];scene.count[layer]=kept;}
 sceneRoomStride181=(interiorRooms181.count+7)/8;if(sceneRoomStride181&&scene.count[0]&&scene.count[0]<=65536/sceneRoomStride181){sceneRoomBits181=malloc(scene.count[0]*sceneRoomStride181);if(sceneRoomBits181)for(unsigned i=0;i<scene.count[0];i++){const float*b=scene.instances[0][i].bounds;rooms_box_bits181(&interiorRooms181,b[0],b[1],b[3],b[4],sceneRoomBits181+i*sceneRoomStride181);}}
}
static void scenery_release(void){
 free(sceneRoomBits181);sceneRoomBits181=NULL;sceneRoomStride181=0;
 if(sceneTexture)MmFreeContiguousMemory(sceneTexture);if(sceneMesh)MmFreeContiguousMemory(sceneMesh);if(sceneMetadataRaw)free(sceneMetadataRaw);sceneTexture=sceneMesh=NULL;sceneMetadataRaw=NULL;sceneVertices=sceneW=sceneH=0;memset(&scene,0,sizeof(scene));
}
#ifndef MYRO_HOST
static float sceneFocusX61,sceneFocusY61;
static unsigned scenery_draw(const float*camera,unsigned map){
 if(!sceneVertices)return 0;
 map=0;gpu_depth_state(1);program(1);bindTexture(sceneTexture,sceneW,sceneH,sceneW*2,0x0001102a);
 uint32_t*p=pb_begin();
 p=pb_push1(p,NV097_SET_CULL_FACE_ENABLE,0);p=pb_push1(p,NV097_SET_DEPTH_TEST_ENABLE,1);p=pb_push1(p,NV097_SET_DEPTH_MASK,1);p=pb_push1(p,NV097_SET_BLEND_ENABLE,0);
 p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,1);p=pb_push1(p,NV097_SET_ALPHA_FUNC,0x204);p=pb_push1(p,NV097_SET_ALPHA_REF,127);
 for(int i=0;i<16;i++)p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+i*4,2);
 p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT,2|(3<<4)|(20<<8));p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+9*4,2|(2<<4)|(20<<8));
 /* Each gpu_triangle_range54 call sets its rebased position/UV addresses
    and invalidates the vertex cache before drawing. */
 pb_end(p);
 unsigned drawn=0;
 for(unsigned i=0;i<scene.count[map];i++){
  SceneInstance*a=&scene.instances[map][i];unsigned room=interiorRooms181.active;if(sceneRoomBits181&&room&&!(sceneRoomBits181[i*sceneRoomStride181+(room-1)/8]&(1u<<((room-1)%8))))continue;if(!scene_range61(a,sceneFocusX61,sceneFocusY61,sceneryView60<MONSTER_VIEW_COUNT53?monsterCells52[sceneryView60]:0)||!scene_visible(a,camera))continue;SceneModel*d=&scene.model[a->model];float matrix[16];scene_matrix(matrix,camera,a);
  p=pb_begin();p=pb_push1(p,NV097_SET_TRANSFORM_CONSTANT_LOAD,96);pb_push(p++,NV097_SET_TRANSFORM_CONSTANT,16);memcpy(p,matrix,64);p+=16;
  pb_end(p);gpu_triangle_range54(sceneMesh,sceneVertices,d->start,d->count);drawn++;
 }
 p=pb_begin();p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,0);pb_end(p);return drawn;
}

#endif
