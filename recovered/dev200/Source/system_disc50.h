#ifndef MYRO_SYSTEM_DISC50_H
#define MYRO_SYSTEM_DISC50_H
/* MIT. Shared bounded reader for original single-player system resources. */
#include "system_data50.h"
static unsigned char*system_packed50(unsigned id){
 if(id>=SYSTEM_BLOBS50)fail("System resource index invalid");const SystemBlob50*b=&systemBlobs50[id];if(!b->packed||b->offset>SYSTEM_FILE_BYTES50||b->packed>SYSTEM_FILE_BYTES50-b->offset||b->raw>16*1024*1024)fail("System resource bounds invalid");unsigned char*p=malloc(b->packed);if(!p)fail("System read allocation failed");unsigned done=0;
#ifdef MYRO_HOST
 const char*path=getenv("MYRO_SYSTEM_PATH50");if(!path)path="../Systems/systems.bin";FILE*f=fopen(path,"rb");if(!f){free(p);fail("Cannot open systems.bin");}fseek(f,0,SEEK_END);long size=ftell(f);if(size!=SYSTEM_FILE_BYTES50||fseek(f,b->offset,SEEK_SET)){fclose(f);free(p);fail("System file size/seek mismatch");}while(done<b->packed){unsigned n=b->packed-done;if(n>32768)n=32768;unsigned got=fread(p+done,1,n,f);if(!got){fclose(f);free(p);fail("System resource read failed");}done+=got;}fclose(f);
#else
 HANDLE f=CreateFile("D:\\systems.bin",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);if(f==INVALID_HANDLE_VALUE){free(p);fail("Cannot open D: systems.bin");}DWORD high=0,size=GetFileSize(f,&high),at=SetFilePointer(f,b->offset,NULL,FILE_BEGIN);if(high||size!=SYSTEM_FILE_BYTES50||at!=b->offset){CloseHandle(f);free(p);fail("System file size/seek mismatch");}while(done<b->packed){DWORD n=b->packed-done,got=0;if(n>32768)n=32768;if(!ReadFile(f,p+done,n,&got,NULL)||!got||got>n){CloseHandle(f);free(p);fail("System resource read failed");}done+=got;}CloseHandle(f);
#endif
 if(crc32(0,p,b->packed)!=b->crc){free(p);fail("System resource checksum failed");}return p;
}
static unsigned char*system_expand50(unsigned id){unsigned char*p=system_packed50(id),*raw=inflateasset("original system resource",p,systemBlobs50[id].packed,systemBlobs50[id].raw);free(p);return raw;}

#endif
