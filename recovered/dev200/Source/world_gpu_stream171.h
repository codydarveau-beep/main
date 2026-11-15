/* MIT. Stream final GPU buffers directly; retain only collision/height metadata. */
#ifndef MYRO_WORLD_GPU_STREAM171_H
#define MYRO_WORLD_GPU_STREAM171_H
#include "world_stream171.h"
#include "terrain_alpha171.h"
static void*sceneMesh,*sceneTexture;static unsigned sceneVertices,sceneW,sceneH;
typedef struct{unsigned start,bytes;unsigned char*dest;}WorldGpuSlice171;
typedef struct{unsigned mode,map,headerBytes;unsigned char header[12];unsigned ready,count;WorldGpuSlice171 slices[3];}WorldGpuBuild171;
static int world_gpu_sink171(void*context,unsigned offset,unsigned char*data,unsigned bytes){WorldGpuBuild171*c=context;unsigned used=0;if(offset<c->headerBytes){unsigned n=c->headerBytes-offset;if(n>bytes)n=bytes;memcpy(c->header+offset,data,n);used=n;if(offset+n<c->headerBytes)return 1;const WorldBlob*b=worldBlobs[c->map];unsigned prefix=c->headerBytes;
 if(c->mode==0){memcpy(&tw,c->header,4);memcpy(&th,c->header+4,4);if(!tw||tw>4096||!th||th>4096||b[0].raw!=8+tw*th*2)return 0;gpuTerrain=gpu_alloc(tw*th*2);groundTextureFormat52=terrainAlpha171[c->map]?TERRAIN_ARGB1555_52:TERRAIN_RGB565_52;c->slices[c->count++]=(WorldGpuSlice171){prefix,tw*th*2,gpuTerrain};terrain=NULL;}
 else if(c->mode==1){memcpy(&mw,c->header,4);memcpy(&mh,c->header+4,4);memcpy(&nverts,c->header+8,4);if(mw!=mapWidths[c->map]||mh!=mapHeights[c->map]||nverts>1000000||nverts%3||b[3].raw!=12+(mw*mh+1)*4+mw*mh*16+nverts*20)return 0;cellStarts=malloc((mw*mh+1)*4);groundHeights=malloc(mw*mh*16);if(!cellStarts||!groundHeights)return 0;gpuMesh=gpu_alloc(nverts*20);c->slices[c->count++]=(WorldGpuSlice171){prefix,(mw*mh+1)*4,(unsigned char*)cellStarts};prefix+=(mw*mh+1)*4;c->slices[c->count++]=(WorldGpuSlice171){prefix,mw*mh*16,(unsigned char*)groundHeights};prefix+=mw*mh*16;c->slices[c->count++]=(WorldGpuSlice171){prefix,nverts*20,gpuMesh};meshRaw=NULL;meshVertices=NULL;}
 else if(c->mode==3){memcpy(&sceneW,c->header,4);memcpy(&sceneH,c->header+4,4);if(sceneW!=2048||!sceneH||sceneH>2048||b[4].raw!=8+sceneW*sceneH*2)return 0;if(!sceneTexture)sceneTexture=gpu_alloc(sceneW*sceneH*2);c->slices[c->count++]=(WorldGpuSlice171){prefix,sceneW*sceneH*2,sceneTexture};}
 else{memcpy(&sceneVertices,c->header,4);if(sceneVertices>100000||sceneVertices%3||b[5].raw!=4+sceneVertices*20)return 0;sceneMesh=sceneVertices?gpu_alloc(sceneVertices*20):NULL;c->slices[c->count++]=(WorldGpuSlice171){prefix,sceneVertices*20,sceneMesh};}c->ready=1;}
 if(!c->ready)return 0;while(used<bytes){unsigned at=offset+used,k=0;for(;k<c->count;k++)if(at>=c->slices[k].start&&at<c->slices[k].start+c->slices[k].bytes)break;if(k==c->count)return 0;WorldGpuSlice171*s=c->slices+k;unsigned n=s->start+s->bytes-at;if(n>bytes-used)n=bytes-used;
 if(c->mode==0&&terrainAlpha171[c->map]){if((n|at)&1)return 0;uint16_t*p=(uint16_t*)(data+used);for(unsigned j=0;j<n/2;j++){unsigned v=p[j];p[j]=terrain_magenta52(v)?0:(uint16_t)(0x8000u|((v>>11)<<10)|(((v>>6)&31)<<5)|(v&31));}}
 if((c->mode==1&&k==2)||c->mode==2){if((n|at)&3)return 0;for(unsigned j=0;j<n;j+=4){float f;memcpy(&f,data+used+j,4);if(!isfinite(f))return 0;}}
 memcpy(s->dest+at-s->start,data+used,n);used+=n;}return 1;}
#ifndef MYRO_HOST
static int world_gpu_read171(void*context,unsigned at,unsigned char*out,unsigned bytes){HANDLE f=*(HANDLE*)context;if(SetFilePointer(f,at,NULL,FILE_BEGIN)!=at)return 0;DWORD done=0;while(done<bytes){DWORD got=0,n=bytes-done;if(n>32768)n=32768;if(!ReadFile(f,out+done,n,&got,NULL)||!got||got>n)return 0;done+=got;}return 1;}
static void world_gpu_section171(unsigned map,unsigned section,unsigned mode,unsigned headerBytes){HANDLE f=CreateFile("D:\\world.bin",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);if(f==INVALID_HANDLE_VALUE)fail("Cannot open streamed world data");DWORD high=0,size=GetFileSize(f,&high);WorldGpuBuild171 c={0};c.mode=mode;c.map=map;c.headerBytes=headerBytes;int ok=!high&&size==WORLD_FILE_BYTES&&world_stream171(&worldBlobs[map][section],world_gpu_read171,&f,world_gpu_sink171,&c);CloseHandle(f);if(!ok)fail("Streamed map section failed validation");}
/* Reserve the largest map texture before smaller allocations fragment its space. */
static void world_gpu_reserve171(unsigned map){const WorldBlob*b=worldBlobs[map];if(b[5].raw>4){unsigned bytes=b[4].raw;if(bytes<8||((bytes-8)%4096)||bytes-8>8388608)fail("Scenery reservation bounds invalid");sceneTexture=gpu_alloc(bytes-8);}}
static void world_terrain_gpu171(unsigned map){world_gpu_section171(map,0,0,8);}
static void world_geometry_gpu171(unsigned map){world_gpu_section171(map,3,1,12);if(cellStarts[mw*mh]!=nverts)fail("Geometry directory mismatch");for(unsigned i=0;i<mw*mh;i++)if(cellStarts[i]>cellStarts[i+1]||cellStarts[i]%3)fail("Invalid geometry directory");for(unsigned i=0;i<mw*mh*4;i++)if(!isfinite(groundHeights[i]))fail("Invalid ground height");}
static void world_scenery_atlas171(unsigned map){world_gpu_section171(map,4,3,8);}
static void world_scenery_gpu171(unsigned map){world_gpu_section171(map,5,2,4);}
#endif
#endif
