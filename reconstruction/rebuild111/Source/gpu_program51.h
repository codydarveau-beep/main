#include "screen_layout55.h"
/* MIT. Reuse the selected vertex program within a frame. No draw data changes. */
static int gpuProgram51=-1,gpuScreenDirty55=1;static ScreenLayout55 gpuScreenLast55;
static void gpu_program_frame51(void){gpuProgram51=-1;gpuScreenDirty55=1;}
static void program(int terrainProgram){
 int fitted=screenLayout55.width!=100||screenLayout55.height!=100||screenLayout55.x||screenLayout55.y;if(fitted&&(gpuScreenDirty55||memcmp(&gpuScreenLast55,&screenLayout55,sizeof(screenLayout55)))){float scale[4],offset[4];screen_layout_constants55(scale,offset);uint32_t*constants=pb_begin();constants=pb_push1(constants,NV097_SET_TRANSFORM_CONSTANT_LOAD,100);pb_push(constants++,NV097_SET_TRANSFORM_CONSTANT,8);memcpy(constants,scale,16);memcpy(constants+4,offset,16);constants+=8;pb_end(constants);gpuScreenLast55=screenLayout55;gpuScreenDirty55=0;}
 terrainProgram=!!terrainProgram;int selected=terrainProgram|(fitted?2:0);if(gpuProgram51==selected)return;
 static const uint32_t terrainCode[]={
 #include "terrain.inl"
 };
 static const uint32_t screenCode[]={
 #include "screen.inl"
 };
 static const uint32_t terrainOriginal55[]={
 #include "terrain_unscaled55.inl"
 };
 static const uint32_t screenOriginal55[]={
 #include "screen_unscaled55.inl"
 };
 const uint32_t *code=fitted?(terrainProgram?terrainCode:screenCode):(terrainProgram?terrainOriginal55:screenOriginal55);unsigned n=fitted?(terrainProgram?sizeof(terrainCode)/4:sizeof(screenCode)/4):(terrainProgram?sizeof(terrainOriginal55)/4:sizeof(screenOriginal55)/4);
 uint32_t *p=pb_begin();
 p=pb_push1(p,NV097_SET_TRANSFORM_PROGRAM_START,0);
 p=pb_push1(p,NV097_SET_TRANSFORM_EXECUTION_MODE,6);
 p=pb_push1(p,NV097_SET_TRANSFORM_PROGRAM_CXT_WRITE_EN,0);
 p=pb_push1(p,NV097_SET_TRANSFORM_PROGRAM_LOAD,0);
 for(unsigned i=0;i<n;i+=4){pb_push(p++,NV097_SET_TRANSFORM_PROGRAM,4);memcpy(p,code+i,16);p+=4;}
 pb_end(p);gpuProgram51=selected;
}
