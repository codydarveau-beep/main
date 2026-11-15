/* MIT. Validated disc-only player variants, one active body at a time. */
#include "actor_data.h"
static unsigned actorDiscReads;
static unsigned char*actor_blob_packed58(const ActorBlob*b,unsigned index){
 if(!b->packed||b->offset>ACTOR_FILE_BYTES||b->packed>ACTOR_FILE_BYTES-b->offset)fail("Actor section bounds invalid");
 unsigned char*p=malloc(b->packed);if(!p)fail("Insufficient memory for disc read");unsigned done=0;char message[180];
#ifdef MYRO_HOST
 const char*path=getenv("MYRO_ACTOR_PATH");if(!path)path="Xbox-Weapons-Test-19/Actors/actors.bin";
 FILE*f=fopen(path,"rb");if(!f){free(p);fail("Cannot open actors.bin (host)");}fseek(f,0,SEEK_END);long size=ftell(f);
 if(size!=ACTOR_FILE_BYTES||fseek(f,b->offset,SEEK_SET)){fclose(f);free(p);fail("actors.bin size/seek mismatch");}
 while(done<b->packed){unsigned n=b->packed-done;if(n>32768)n=32768;unsigned got=fread(p+done,1,n,f);if(!got){fclose(f);free(p);fail("actors.bin host read failed");}done+=got;}fclose(f);
#else
 const char*path="D:\\actors.bin";HANDLE f=CreateFile(path,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
 if(f==INVALID_HANDLE_VALUE){unsigned err=GetLastError();free(p);snprintf(message,sizeof(message),"Cannot open D: actors.bin: error %u. Mount the complete Test44 ISO.",err);fail(message);}
 DWORD high=0,size=GetFileSize(f,&high);SetLastError(0);DWORD at=SetFilePointer(f,b->offset,NULL,FILE_BEGIN);
 if(high||size!=ACTOR_FILE_BYTES||at!=b->offset){unsigned err=GetLastError();CloseHandle(f);free(p);snprintf(message,sizeof(message),"actors.bin size/seek failed: actor%u offset%u error%u",index,b->offset,err);fail(message);}
 while(done<b->packed){DWORD n=b->packed-done,got=0;if(n>32768)n=32768;BOOL ok=ReadFile(f,p+done,n,&got,NULL);if(!ok||!got||got>n){unsigned err=GetLastError();CloseHandle(f);free(p);snprintf(message,sizeof(message),"actors.bin read failed: actor%u offset%u request%lu got%lu error%u",index,b->offset+done,(unsigned long)n,(unsigned long)got,err);fail(message);}done+=got;}CloseHandle(f);
#endif
 if(crc32(0,p,b->packed)!=b->crc){free(p);snprintf(message,sizeof(message),"actors.bin checksum failed: actor%u",index);fail(message);}
 actorDiscReads++;return p;
}

static unsigned char*actor_packed(unsigned index){if(index>=ACTOR_VARIANTS)fail("Actor variant index invalid");return actor_blob_packed58(actorBlobs+index,index);}
