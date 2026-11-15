/* MIT. One source-resolution frame on GPU; bounded raw/packed CPU staging.
 * Call prepare/release at a GPU fence, before submitting this frame's draws. */
#ifndef MYRO_WATER_STREAM190_H
#define MYRO_WATER_STREAM190_H
#include "water_wave190.h"
static void*waterGpu190;static unsigned char*waterRaw190,*waterPacked190;static FILE*waterFile190;
static unsigned waterBytes190,waterPackedCapacity190,waterBank190=~0u,waterFrame190=~0u,waterReads190;static float waterTime190;
static void water_release190(void){if(waterGpu190)MmFreeContiguousMemory(waterGpu190);waterGpu190=NULL;free(waterRaw190);free(waterPacked190);waterRaw190=waterPacked190=NULL;if(waterFile190)fclose(waterFile190);waterFile190=NULL;waterBytes190=waterPackedCapacity190=0;waterBank190=waterFrame190=~0u;}
static void water_prepare190(unsigned map){
 if(!waterOriginal190||!water_map_valid51a(map)||!waterMaps[map].count){water_release190();return;}
 unsigned bank=waterSettings190[map].type,frame=water_frame190(map,waterTime190);if(bank==waterBank190&&frame==waterFrame190)return;
 const WaterFrame190*f=&waterFrames190[bank][frame];unsigned raw=f->width*f->width*4;
 if(raw>WATER_MAX_FRAME_BYTES190||!f->packed||f->packed>raw+1024||f->offset>WATER_FILE_BYTES190||f->packed>WATER_FILE_BYTES190-f->offset)fail("Water frame bounds invalid");
 if(waterBytes190!=raw){water_release190();waterRaw190=malloc(raw);waterGpu190=gpu_alloc(raw);if(!waterRaw190)fail("Water frame allocation failed");waterBytes190=raw;}
 if(waterPackedCapacity190<f->packed){free(waterPacked190);waterPacked190=malloc(f->packed);waterPackedCapacity190=f->packed;if(!waterPacked190)fail("Water stream allocation failed");}
 if(!waterFile190){
#ifdef MYRO_HOST
 const char*path=getenv("MYRO_WATER_PATH");if(!path)path="../Water/water.bin";
#else
 const char*path="D:\\water.bin";
#endif
 waterFile190=fopen(path,"rb");if(!waterFile190||fseek(waterFile190,0,SEEK_END)||ftell(waterFile190)!=WATER_FILE_BYTES190)fail("Water file missing or incorrect");}
 if(fseek(waterFile190,f->offset,SEEK_SET)||fread(waterPacked190,1,f->packed,waterFile190)!=f->packed)fail("Water frame read failed");
 z_stream z={0};
#ifndef MYRO_HOST
 z.zalloc=asset_zalloc;z.zfree=asset_zfree;
#endif
 z.next_in=waterPacked190;z.avail_in=f->packed;z.next_out=waterRaw190;z.avail_out=raw;int ok=inflateInit(&z)==Z_OK;if(ok){ok=inflate(&z,Z_FINISH)==Z_STREAM_END&&z.total_out==raw&&!z.avail_in;inflateEnd(&z);}if(!ok||crc32(0,waterRaw190,raw)!=f->crc)fail("Water frame checksum invalid");memcpy(waterGpu190,waterRaw190,raw);waterBank190=bank;waterFrame190=frame;waterReads190++;
}
#endif
