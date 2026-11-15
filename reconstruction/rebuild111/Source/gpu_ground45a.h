#include "interior_rooms181.h"
#include "terrain_key52.h"
#include "gpu_vertex_window54.h"
#include "terrain_view180.h"
/* MIT. Native terrain submission; CCW matches the corrected camera. */
static unsigned gpu_ground(const float matrix[16],int cx,int cy,int cullBack){
 gpu_depth_state(1);program(1);bindTexture(gpuTerrain,tw,th,tw*2,groundTextureFormat52);
 uint32_t *p=pb_begin();
 p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,groundTextureFormat52==TERRAIN_ARGB1555_52);
 p=pb_push1(p,NV097_SET_ALPHA_FUNC,0x204);p=pb_push1(p,NV097_SET_ALPHA_REF,127);
 p=pb_push1(p,NV097_SET_CULL_FACE,NV097_SET_CULL_FACE_V_BACK);
 p=pb_push1(p,NV097_SET_FRONT_FACE,NV097_SET_FRONT_FACE_V_CCW);
 p=pb_push1(p,NV097_SET_CULL_FACE_ENABLE,cullBack);
 p=pb_push1(p,NV097_SET_DEPTH_TEST_ENABLE,1);p=pb_push1(p,NV097_SET_DEPTH_MASK,1);p=pb_push1(p,NV097_SET_BLEND_ENABLE,0);
 p=pb_push1(p,NV097_SET_TRANSFORM_CONSTANT_LOAD,96);
 pb_push(p++,NV097_SET_TRANSFORM_CONSTANT,16);memcpy(p,matrix,64);p+=16;
 for(int i=0;i<16;i++)p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+i*4,2);
 p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT,2|(3<<4)|(20<<8));
 p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+9*4,2|(2<<4)|(20<<8));
 p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_OFFSET,(DWORD)gpuMesh&0x03ffffff);
 p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_OFFSET+9*4,((DWORD)gpuMesh+12)&0x03ffffff);
 p=pb_push1(p,NV097_BREAK_VERTEX_BUFFER_CACHE,0);pb_end(p);
 static unsigned boundsMap180=~0u;static float low180,high180;
 if(boundsMap180!=surfaceMap){low180=1e30f;high180=-1e30f;for(unsigned i=0;i<mw*mh*4;i++){float z=groundHeights[i];if(z<low180)low180=z;if(z>high180)high180=z;}boundsMap180=surfaceMap;}
 TerrainView180 view180=terrain_view180(matrix,mw,mh,cx,cy,mapView64<MONSTER_VIEW_COUNT53?monsterCells52[mapView64]:0,low180,high180);
 int x0=view180.x0,x1=view180.x1,y0=view180.y0,y1=view180.y1;
 if(x0>x1||y0>y1)return 0;
 unsigned total=0;
 for(int y=y0;y<=y1;y++){
  if(!interiorRooms181.active){unsigned start=cellStarts[y*mw+x0],end=cellStarts[y*mw+x1+1];if(end>start){total+=(end-start)/3;gpu_triangle_range54(gpuMesh,nverts,start,end-start);}continue;}
  int run=-1;for(int x=x0;x<=x1+1;x++){int visible=x<=x1&&rooms_tile181(&interiorRooms181,(unsigned)x,(unsigned)y);if(visible&&run<0)run=x;if(!visible&&run>=0){unsigned start=cellStarts[y*mw+run],end=cellStarts[y*mw+x];if(end>start){total+=(end-start)/3;gpu_triangle_range54(gpuMesh,nverts,start,end-start);}run=-1;}}

 }
 return total;
}
