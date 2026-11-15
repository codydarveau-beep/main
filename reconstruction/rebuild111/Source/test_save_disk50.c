/* SPDX-License-Identifier: MIT
 * Exercise the native adapter against host files through a minimal WinAPI shim.
 * This tests the actual adapter code, not the Xbox kernel or FATX filesystem.
 * Build with -I path/to/nxdk/lib so its unchanged mount declarations are used.
 */
#define _POSIX_C_SOURCE 200809L
#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
typedef uint32_t DWORD;typedef int BOOL;typedef int32_t NTSTATUS;typedef FILE*HANDLE;
typedef struct {NTSTATUS Status;} IO_STATUS_BLOCK;
#define INVALID_HANDLE_VALUE NULL
#define TRUE 1
#define FALSE 0
#define FILE_ATTRIBUTE_DIRECTORY 0x10
#define FILE_ATTRIBUTE_NORMAL 0x80
#define INVALID_FILE_ATTRIBUTES UINT32_MAX
#define INVALID_FILE_SIZE UINT32_MAX
#define FILE_SHARE_READ 1
#define GENERIC_READ 0x80000000u
#define GENERIC_WRITE 0x40000000u
#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define FILE_FLAG_WRITE_THROUGH 0x80000000u
#define ERROR_SUCCESS 0
#define ERROR_FILE_NOT_FOUND 2
#define ERROR_PATH_NOT_FOUND 3
#define ERROR_ACCESS_DENIED 5
#define ERROR_WRITE_FAULT 29
#define STATUS_PENDING 0x103
static char testRoot[256];static DWORD lastError;static int flushes,flushFail,shortWrite,openWriteFail;
static const char*mapped(const char*p){static char buf[512];assert(!strncmp(p,"E:\\MyROOffline",14));snprintf(buf,sizeof(buf),"%s/%s",testRoot,p+3);for(char*q=buf;*q;q++)if(*q=='\\')*q='/';return buf;}
static DWORD GetLastError(void){return lastError;}static void SetLastError(DWORD n){lastError=n;}
static BOOL CreateDirectory(const char*p,void*x){(void)x;int ret=mkdir(mapped(p),0700);lastError=ret?ERROR_ACCESS_DENIED:0;return ret==0;}
static DWORD GetFileAttributes(const char*p){struct stat s;if(stat(mapped(p),&s))return INVALID_FILE_ATTRIBUTES;return S_ISDIR(s.st_mode)?FILE_ATTRIBUTE_DIRECTORY:FILE_ATTRIBUTE_NORMAL;}
static HANDLE CreateFile(const char*p,DWORD access,DWORD share,void*sec,DWORD how,DWORD flags,void*template){
 (void)share;(void)sec;(void)template;
 if(access==GENERIC_WRITE){assert(strstr(p,"\\Save50\\"));assert(how==CREATE_ALWAYS&&(flags&FILE_FLAG_WRITE_THROUGH));if(openWriteFail){lastError=ERROR_ACCESS_DENIED;return NULL;}}
 else assert(access==GENERIC_READ&&how==OPEN_EXISTING);
 FILE*f=fopen(mapped(p),access==GENERIC_WRITE?"wb":"rb");lastError=f?0:errno==ENOENT?ERROR_FILE_NOT_FOUND:ERROR_ACCESS_DENIED;return f;
}
static DWORD GetFileSize(HANDLE f,DWORD*high){long at=ftell(f);fseek(f,0,SEEK_END);long n=ftell(f);fseek(f,at,SEEK_SET);*high=0;return (DWORD)n;}
static BOOL ReadFile(HANDLE f,void*p,DWORD n,DWORD*got,void*over){(void)over;*got=fread(p,1,n,f);return !ferror(f);}
static BOOL WriteFile(HANDLE f,const void*p,DWORD n,DWORD*wrote,void*over){(void)over;*wrote=fwrite(p,1,shortWrite?n/2:n,f);return !ferror(f);}
static BOOL CloseHandle(HANDLE f){return fclose(f)==0;}
static NTSTATUS NtFlushBuffersFile(HANDLE f,IO_STATUS_BLOCK*io){flushes++;if(flushFail)return -1;assert(fflush(f)==0&&fsync(fileno(f))==0);io->Status=0;return 0;}
static DWORD RtlNtStatusToDosError(NTSTATUS s){(void)s;return ERROR_WRITE_FAULT;}
static NTSTATUS NtWaitForSingleObject(HANDLE f,BOOL a,void*t){(void)f;(void)a;(void)t;return 0;}
bool nxIsDriveMounted(char c){assert(c=='E');return true;}
bool nxMountDrive(char c,const char*p){(void)c;(void)p;abort();}
#include "save_xbox.h"
static int openworld(void*c,float x,float y,float nx,float ny){(void)c;(void)x;(void)y;return nx>=8&&nx<3192&&ny>=8&&ny<3192;}
static void fixture50(const char*path,const unsigned char*bytes,unsigned size){FILE*f=fopen(mapped(path),"wb");assert(f&&fwrite(bytes,1,size,f)==size);assert(!fclose(f));}
static int prepared50;static unsigned preparedMap50;
static int prepare50(void*ctx,unsigned map,float*x,float*y){(void)ctx;prepared50++;preparedMap50=map;*x=2100;*y=1636;return 1;}
int main(void){
 char tmp[]="/tmp/myro-save50-XXXXXX";assert(mkdtemp(tmp));strcpy(testRoot,tmp);assert(save_disk_init()&&save_disk_init());
 SaveStore s={0};s.read=save_disk_read;s.write=save_disk_write;s.prepare=prepare50;Combat g,h;combat_init(&g,2100,1636,openworld,NULL);
 assert(!save_load(&s,&g,2100,1636,openworld,NULL)&&!s.blocked);assert(!save_disk_import50(&s,&g,2100,1636,openworld,NULL));
 assert(save_directory("E:\\MyROOffline\\Save48"));
 const char*oldPaths[2]={"E:\\MyROOffline\\Save48\\char-a.dat","E:\\MyROOffline\\Save48\\char-b.dat"};
 unsigned char original[2][SAVE48_BYTES50];
 for(int i=0;i<2;i++){FILE*f=fopen(i?"fixtures50/save48-job10.dat":"fixtures50/save48-job00.dat","rb");assert(f&&fread(original[i],1,SAVE48_BYTES50,f)==SAVE48_BYTES50&&!fclose(f));fixture50(oldPaths[i],original[i],SAVE48_BYTES50);}
 assert(save_disk_import50(&s,&g,2100,1636,openworld,NULL)==1&&g.jobId==10&&g.apples==42&&prepared50==1&&preparedMap50==g.mapId&&g.hotbar[10]==BIND_EMPTY50);
 assert(save_commit(&s,&g)&&flushes==1);g.apples=43;assert(save_commit(&s,&g)&&flushes==2);
 assert(save_load(&s,&h,2100,1636,openworld,NULL)&&h.apples==43&&h.hotbar[10]==BIND_EMPTY50&&s.sequence==2);
 shortWrite=1;g.apples=44;assert(!save_commit(&s,&g)&&saveDiskError==ERROR_WRITE_FAULT);shortWrite=0;assert(save_load(&s,&h,2100,1636,openworld,NULL)&&h.apples==43);
 openWriteFail=1;assert(!save_commit(&s,&g)&&saveDiskError==ERROR_ACCESS_DENIED);openWriteFail=0;
 flushFail=1;assert(!save_commit(&s,&g));flushFail=0;assert(save_load(&s,&h,2100,1636,openworld,NULL));
 /* Every commit above is restricted to Save50 by the actual adapter shim. */
 for(int i=0;i<2;i++){unsigned char b[SAVE48_BYTES50];FILE*f=fopen(mapped(oldPaths[i]),"rb");assert(f&&fread(b,1,sizeof(b),f)==sizeof(b)&&!fclose(f));assert(!memcmp(b,original[i],sizeof(b)));}
 s.recoverToCamp=1;assert(save_disk_import50(&s,&h,0,0,openworld,NULL)==1&&h.jobId==10&&h.mapId==0&&h.x==2100&&h.y==1636);s.recoverToCamp=0;
 unsigned char bad[SAVE48_BYTES50];memcpy(bad,original[1],sizeof(bad));bad[2700]^=1;fixture50(oldPaths[1],bad,sizeof(bad));assert(save_disk_import50(&s,&h,2100,1636,openworld,NULL)==1&&h.jobId==0);
 fixture50(oldPaths[0],bad,sizeof(bad));assert(save_disk_import50(&s,&h,2100,1636,openworld,NULL)==-1);
 memcpy(bad,original[1],sizeof(bad));save_put(bad+8,99);fixture50(oldPaths[1],bad,sizeof(bad));fixture50(oldPaths[0],original[0],sizeof(bad));assert(save_disk_import50(&s,&h,2100,1636,openworld,NULL)==-1);
 for(int i=0;i<2;i++){assert(!unlink(mapped(oldPaths[i])));assert(!unlink(mapped(savePaths[i])));}
 assert(!rmdir(mapped("E:\\MyROOffline\\Save48")));assert(!rmdir(mapped("E:\\MyROOffline\\Save50")));assert(!rmdir(mapped("E:\\MyROOffline")));assert(!rmdir(tmp));
 puts("PASS50 actual disk adapter: read-only Save48 migration/newest choice/map preparation/recovery, isolated Save50 writes, 8192-byte read-back, short-write/flush/access failures and corrupt/future source preservation.");
}
