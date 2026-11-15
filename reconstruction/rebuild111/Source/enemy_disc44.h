/* MIT. Validated disc-only monster species, one active body at a time. */
#include "enemy_disc_data44.h"
static unsigned enemyDiscReads44;
static unsigned char*enemy_packed44(unsigned index){
 if(index>=ENEMY_DISC_COUNT)fail("Enemy variant index invalid");const EnemyBlob44*b=&enemyBlobs44[index];
 if(!b->packed||b->offset>ENEMY_FILE_BYTES||b->packed>ENEMY_FILE_BYTES-b->offset)fail("Enemy section bounds invalid");
 unsigned char*p=malloc(b->packed);if(!p)fail("Insufficient memory for disc read");unsigned done=0;char message[180];
#ifdef MYRO_HOST
 const char*path=getenv("MYRO_ENEMY_PATH");if(!path)path="../Enemies/enemies.bin";
 FILE*f=fopen(path,"rb");if(!f){free(p);fail("Cannot open enemies.bin (host)");}fseek(f,0,SEEK_END);long size=ftell(f);
 if(size!=ENEMY_FILE_BYTES||fseek(f,b->offset,SEEK_SET)){fclose(f);free(p);fail("enemies.bin size/seek mismatch");}
 while(done<b->packed){unsigned n=b->packed-done;if(n>32768)n=32768;unsigned got=fread(p+done,1,n,f);if(!got){fclose(f);free(p);fail("enemies.bin host read failed");}done+=got;}fclose(f);
#else
 const char*path="D:\\enemies.bin";HANDLE f=CreateFile(path,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
 if(f==INVALID_HANDLE_VALUE){unsigned err=GetLastError();free(p);snprintf(message,sizeof(message),"Cannot open D: enemies.bin: error %u. Mount the complete Test44 ISO.",err);fail(message);}
 DWORD high=0,size=GetFileSize(f,&high);SetLastError(0);DWORD at=SetFilePointer(f,b->offset,NULL,FILE_BEGIN);
 if(high||size!=ENEMY_FILE_BYTES||at!=b->offset){unsigned err=GetLastError();CloseHandle(f);free(p);snprintf(message,sizeof(message),"enemies.bin size/seek failed: enemy%u offset%u error%u",index,b->offset,err);fail(message);}
 while(done<b->packed){DWORD n=b->packed-done,got=0;if(n>32768)n=32768;BOOL ok=ReadFile(f,p+done,n,&got,NULL);if(!ok||!got||got>n){unsigned err=GetLastError();CloseHandle(f);free(p);snprintf(message,sizeof(message),"enemies.bin read failed: enemy%u offset%u request%lu got%lu error%u",index,b->offset+done,(unsigned long)n,(unsigned long)got,err);fail(message);}done+=got;}CloseHandle(f);
#endif
 if(crc32(0,p,b->packed)!=b->crc){free(p);snprintf(message,sizeof(message),"enemies.bin checksum failed: enemy%u",index);fail(message);}
 enemyDiscReads44++;return p;
}
