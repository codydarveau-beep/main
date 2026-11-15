/* MIT. One native-large minimap texture, reused on map changes (64KiB). */
#include "minimap_data200.h"
static void*minimapTexture200;
static unsigned minimapLoaded200=~0u,minimapReads200;
static void minimap_upload(void){
 while(pb_busy()){}if(surfaceMap>=WORLD_MAP_COUNT)fail("Minimap map index");
 const WorldBlob*b=&minimapBlobs200[surfaceMap];
 if(b->raw!=MINIMAP_W200*MINIMAP_H200*2||!b->packed||b->packed>b->raw+1024||b->offset>MINIMAP_FILE_BYTES200||b->packed>MINIMAP_FILE_BYTES200-b->offset)fail("Minimap dimensions/bounds");
#ifdef MYRO_HOST
 const char*path=getenv("MYRO_MINIMAP_PATH");if(!path)path="../Interface/minimaps.bin";
#else
 const char*path="D:\\minimaps.bin";
#endif
 FILE*f=fopen(path,"rb");if(!f)fail("Minimaps file missing");
 if(fseek(f,0,SEEK_END)||ftell(f)!=MINIMAP_FILE_BYTES200||fseek(f,b->offset,SEEK_SET)){fclose(f);fail("Minimaps file size/seek mismatch");}
 unsigned char*packed=malloc(b->packed);if(!packed){fclose(f);fail("Minimap read allocation failed");}
 int ok=fread(packed,1,b->packed,f)==b->packed;fclose(f);if(!ok){free(packed);fail("Minimap read failed");}
 unsigned char*raw=inflateasset("native-large minimap",packed,b->packed,b->raw);free(packed);
 if(crc32(0,raw,b->raw)!=b->crc){free(raw);fail("Minimap checksum mismatch");}
 if(!minimapTexture200)minimapTexture200=gpu_alloc(256*128*2);
 memset(minimapTexture200,0,256*128*2);
 for(unsigned y=0;y<MINIMAP_H200;y++)memcpy((uint16_t*)minimapTexture200+y*256,raw+y*MINIMAP_W200*2,MINIMAP_W200*2);
 free(raw);minimapLoaded200=surfaceMap;minimapReads200++;__sync_synchronize();
}
