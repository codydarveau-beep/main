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
 if(access==GENERIC_WRITE){assert(how==CREATE_ALWAYS&&(flags&FILE_FLAG_WRITE_THROUGH));if(openWriteFail){lastError=ERROR_ACCESS_DENIED;return NULL;}}
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
int main(void){
 char tmp[]="/tmp/myro-save-adapter-XXXXXX";assert(mkdtemp(tmp));strcpy(testRoot,tmp);assert(save_disk_init());assert(save_disk_init());
 SaveStore s={0};s.read=save_disk_read;s.write=save_disk_write;Combat g,h;combat_init(&g,2100,1636,openworld,NULL);
 assert(!save_load(&s,&g,2100,1636,openworld,NULL)&&!s.blocked);assert(save_commit(&s,&g)&&flushes==1);
 g.apples=8;assert(save_commit(&s,&g)&&flushes==2);memset(&s,0,sizeof(s));s.read=save_disk_read;s.write=save_disk_write;
 assert(save_load(&s,&h,2100,1636,openworld,NULL)&&h.apples==8&&s.sequence==2);
 shortWrite=1;g.apples=9;assert(!save_commit(&s,&g)&&saveDiskError==ERROR_WRITE_FAULT);shortWrite=0;
 assert(save_load(&s,&h,2100,1636,openworld,NULL)&&h.apples==8);
 flushFail=1;assert(!save_commit(&s,&g));flushFail=0;
 assert(save_load(&s,&h,2100,1636,openworld,NULL)); /* complete unconfirmed record may survive, but is CRC-checked */
 openWriteFail=1;assert(!save_commit(&s,&g)&&saveDiskError==ERROR_ACCESS_DENIED);openWriteFail=0;
 assert(save_load(&s,&h,2100,1636,openworld,NULL));

 /* Real old-format files are read-only inputs to migration. */
 assert(save_directory("E:\\MyROOffline\\Save01"));
 const char*oldPaths[2]={"E:\\MyROOffline\\Save01\\char-a.dat","E:\\MyROOffline\\Save01\\char-b.dat"};
 unsigned char oldBytes[2][LEGACY_BYTES];LegacyCharacter old;
 g.level=4;g.statPoints=stat_budget(4);g.joblevel=2;g.hp=73;g.maxhp=90;g.sp=9;g.maxsp=16;g.exp=4;g.jexp=10;
 for(int i=0;i<2;i++){
  g.apples=20+i;legacy_capture(&old,&g,40+i);legacy_encode(oldBytes[i],&old);
  FILE*f=fopen(mapped(oldPaths[i]),"wb");assert(f);assert(fwrite(oldBytes[i],1,LEGACY_BYTES,f)==LEGACY_BYTES);assert(fclose(f)==0);
 }
 Combat migrated;assert(save_disk_import(&migrated,2100,1636,openworld,NULL)==1&&migrated.apples==21&&migrated.extraItems[0]==3&&!migrated.equipment&&migrated.level==4&&migrated.joblevel==2&&migrated.hp==73&&migrated.exp==4&&migrated.jexp==10);
 assert(save_commit(&s,&migrated));
 for(int i=0;i<2;i++){
  unsigned char verify[LEGACY_BYTES];FILE*f=fopen(mapped(oldPaths[i]),"rb");assert(f);assert(fread(verify,1,LEGACY_BYTES,f)==LEGACY_BYTES);assert(fclose(f)==0);assert(!memcmp(verify,oldBytes[i],LEGACY_BYTES));assert(unlink(mapped(oldPaths[i]))==0);
 }
 assert(rmdir(mapped("E:\\MyROOffline\\Save01"))==0);

 /* Prefer the Test 06 inventory save and keep its file contents intact. */
 assert(save_directory("E:\\MyROOffline\\Save02"));
 const char*v2paths[2]={"E:\\MyROOffline\\Save02\\char-a.dat","E:\\MyROOffline\\Save02\\char-b.dat"};
 unsigned char v2bytes[2][V2_BYTES];V2Character v2;
 for(int i=0;i<2;i++){
  g.apples=30+i;g.extraItems[0]=0;g.equipment=15;v2_capture(&v2,&g,100+i);v2_encode(v2bytes[i],&v2);
  FILE*f=fopen(mapped(v2paths[i]),"wb");assert(f);assert(fwrite(v2bytes[i],1,V2_BYTES,f)==V2_BYTES);assert(fclose(f)==0);
 }
 assert(save_disk_import(&migrated,2100,1636,openworld,NULL)==1&&migrated.apples==31&&migrated.extraItems[0]==0&&migrated.equipment==15&&migrated.level==4);
 assert(save_commit(&s,&migrated));
 for(int i=0;i<2;i++){
  unsigned char verify[V2_BYTES];FILE*f=fopen(mapped(v2paths[i]),"rb");assert(f);assert(fread(verify,1,V2_BYTES,f)==V2_BYTES);assert(fclose(f)==0);assert(!memcmp(verify,v2bytes[i],V2_BYTES));assert(unlink(mapped(v2paths[i]))==0);
 }
 assert(rmdir(mapped("E:\\MyROOffline\\Save02"))==0);

 /* Read-only import of the latest working skills build. */
 assert(save_directory("E:\\MyROOffline\\Save03"));
 const char*v3paths[2]={"E:\\MyROOffline\\Save03\\char-a.dat","E:\\MyROOffline\\Save03\\char-b.dat"};
 unsigned char v3bytes[2][V3_BYTES];V3Character v3;
 for(int i=0;i<2;i++){
  g.apples=40+i;g.hotbar[7]=3;g.hotSlot=7;v3_capture(&v3,&g,200+i);v3_encode(v3bytes[i],&v3);
  FILE*f=fopen(mapped(v3paths[i]),"wb");assert(f);assert(fwrite(v3bytes[i],1,V3_BYTES,f)==V3_BYTES);assert(fclose(f)==0);
 }
 assert(save_disk_import(&migrated,2100,1636,openworld,NULL)==1&&migrated.apples==41&&migrated.hotSlot==7&&migrated.hotbar[7]==3&&migrated.mapId==0&&migrated.equipment==15);
 assert(save_commit(&s,&migrated));
 for(int i=0;i<2;i++){
  unsigned char verify[V3_BYTES];FILE*f=fopen(mapped(v3paths[i]),"rb");assert(f);assert(fread(verify,1,V3_BYTES,f)==V3_BYTES);assert(fclose(f)==0);assert(!memcmp(verify,v3bytes[i],V3_BYTES));assert(unlink(mapped(v3paths[i]))==0);
 }
 assert(rmdir(mapped("E:\\MyROOffline\\Save03"))==0);
 /* Working Test08/09 map+hotbar import is read-only and initializes Zeny. */
 assert(save_directory("E:\\MyROOffline\\Save04"));
 const char*v4paths[2]={"E:\\MyROOffline\\Save04\\char-a.dat","E:\\MyROOffline\\Save04\\char-b.dat"};
 unsigned char v4bytes[2][V4_BYTES];V4Character v4;
 for(int i=0;i<2;i++){g.mapId=1;g.apples=50+i;g.hotbar[7]=4;g.hotSlot=7;v4_capture(&v4,&g,300+i);v4_encode(v4bytes[i],&v4);FILE*f=fopen(mapped(v4paths[i]),"wb");assert(f);assert(fwrite(v4bytes[i],1,V4_BYTES,f)==V4_BYTES);assert(!fclose(f));}
 assert(save_disk_import(&migrated,1604,1604,openworld,NULL)==1&&migrated.mapId==1&&migrated.apples==51&&migrated.hotbar[7]==4&&migrated.zeny==0);
 migrated.zeny=12345;assert(save_commit(&s,&migrated));Combat recovered;assert(save_load(&s,&recovered,1604,1604,openworld,NULL)&&recovered.zeny==12345);
 for(int i=0;i<2;i++){unsigned char verify[V4_BYTES];FILE*f=fopen(mapped(v4paths[i]),"rb");assert(f);assert(fread(verify,1,V4_BYTES,f)==V4_BYTES);assert(!fclose(f));assert(!memcmp(verify,v4bytes[i],V4_BYTES));assert(!unlink(mapped(v4paths[i])));}
 assert(!rmdir(mapped("E:\\MyROOffline\\Save04")));
 /* Test12 Save05 imports into Save06 without changing the source records. */
 assert(save_directory("E:\\MyROOffline\\Save05"));
 const char*v5paths[2]={"E:\\MyROOffline\\Save05\\char-a.dat","E:\\MyROOffline\\Save05\\char-b.dat"};
 unsigned char v5bytes[2][V5_BYTES];V5Character v5;
 for(int i=0;i<2;i++){g.mapId=3;g.zeny=76543;g.apples=60+i;v5_capture(&v5,&g,400+i);v5_encode(v5bytes[i],&v5);FILE*f=fopen(mapped(v5paths[i]),"wb");assert(f);assert(fwrite(v5bytes[i],1,V5_BYTES,f)==V5_BYTES);assert(!fclose(f));}
 assert(save_disk_import(&migrated,1604,1604,openworld,NULL)==1&&migrated.mapId==3&&migrated.apples==61&&migrated.zeny==76543&&migrated.statPoints==stat_budget(migrated.level));
 assert(stat_raise(&migrated,2));assert(skill_assign(&migrated,7,7));assert(save_commit(&s,&migrated));assert(save_load(&s,&recovered,1604,1604,openworld,NULL)&&recovered.stats[2]==2&&recovered.hotbar[7]==7);
 for(int i=0;i<2;i++){unsigned char verify[V5_BYTES];FILE*f=fopen(mapped(v5paths[i]),"rb");assert(f);assert(fread(verify,1,V5_BYTES,f)==V5_BYTES);assert(!fclose(f));assert(!memcmp(verify,v5bytes[i],V5_BYTES));assert(!unlink(mapped(v5paths[i])));}
 assert(!rmdir(mapped("E:\\MyROOffline\\Save05")));
 /* Read-only Test13a Save06 migration preserves allocated stats and existing hotbars. */
 assert(save_directory("E:\\MyROOffline\\Save06"));const char*v6paths[2]={"E:\\MyROOffline\\Save06\\char-a.dat","E:\\MyROOffline\\Save06\\char-b.dat"};
 unsigned char v6bytes[2][V6_BYTES];V6Character v6;
 for(int i=0;i<2;i++){g.apples=70+i;g.stats[0]=2;g.statPoints=stat_budget(g.level)-stat_spent(g.stats);v6_capture(&v6,&g,500+i);v6_encode(v6bytes[i],&v6);FILE*f=fopen(mapped(v6paths[i]),"wb");assert(f);assert(fwrite(v6bytes[i],1,V6_BYTES,f)==V6_BYTES);assert(!fclose(f));}
 assert(save_disk_import(&migrated,1604,1604,openworld,NULL)==1&&migrated.apples==71&&migrated.stats[0]==2&&!migrated.jobId&&migrated.statPoints==stat_budget(migrated.level)-2);assert(save_commit(&s,&migrated));
 for(int i=0;i<2;i++){unsigned char verify[V6_BYTES];FILE*f=fopen(mapped(v6paths[i]),"rb");assert(f);assert(fread(verify,1,V6_BYTES,f)==V6_BYTES);assert(!fclose(f));assert(!memcmp(verify,v6bytes[i],V6_BYTES));assert(!unlink(mapped(v6paths[i])));}
 assert(!rmdir(mapped("E:\\MyROOffline\\Save06")));
 /* Test14 Save07 migration preserves job/ranks and defaults LB to Apple. */
 assert(save_directory("E:\\MyROOffline\\Save07"));
 const char*v7paths[2]={"E:\\MyROOffline\\Save07\\char-a.dat","E:\\MyROOffline\\Save07\\char-b.dat"};
 unsigned char v7bytes[2][V7_BYTES];V7Character v7;
 g.jobId=1;g.joblevel=7;g.jexp=0;g.ranks[0]=5;g.ranks[1]=1;g.skillPoints=0;stat_refresh(&g);
 for(int i=0;i<2;i++){g.apples=80+i;v7_capture(&v7,&g,600+i);v7_encode(v7bytes[i],&v7);FILE*f=fopen(mapped(v7paths[i]),"wb");assert(f);assert(fwrite(v7bytes[i],1,V7_BYTES,f)==V7_BYTES);assert(!fclose(f));}
 assert(save_disk_import(&migrated,1604,1604,openworld,NULL)==1&&migrated.apples==81&&migrated.jobId==1&&migrated.ranks[1]==1&&migrated.quickKind==0&&migrated.quickId==0);
 migrated.quickKind=1;migrated.quickId=8;assert(save_commit(&s,&migrated));assert(save_load(&s,&recovered,1604,1604,openworld,NULL)&&recovered.quickKind==1&&recovered.quickId==8);
 for(int i=0;i<2;i++){unsigned char verify[V7_BYTES];FILE*f=fopen(mapped(v7paths[i]),"rb");assert(f);assert(fread(verify,1,V7_BYTES,f)==V7_BYTES);assert(!fclose(f));assert(!memcmp(verify,v7bytes[i],V7_BYTES));assert(!unlink(mapped(v7paths[i])));}
 assert(!rmdir(mapped("E:\\MyROOffline\\Save07")));
 /* Test15 Save08 import retains its LB binding and source bytes. */
 assert(save_directory("E:\\MyROOffline\\Save08"));const char*v8paths[2]={"E:\\MyROOffline\\Save08\\char-a.dat","E:\\MyROOffline\\Save08\\char-b.dat"};
 unsigned char v8bytes[2][V8_BYTES];V8Character v8;g.quickKind=1;g.quickId=8;
 for(int i=0;i<2;i++){g.apples=90+i;v8_capture(&v8,&g,700+i);v8_encode(v8bytes[i],&v8);FILE*f=fopen(mapped(v8paths[i]),"wb");assert(f);assert(fwrite(v8bytes[i],1,V8_BYTES,f)==V8_BYTES);assert(!fclose(f));}
 assert(save_disk_import(&migrated,1604,1604,openworld,NULL)==1&&migrated.apples==91&&migrated.jobId==1&&migrated.ranks[1]==1&&migrated.quickKind==1&&migrated.quickId==8);assert(save_commit(&s,&migrated));
 assert(save_load(&s,&recovered,1604,1604,openworld,NULL)&&recovered.quickId==8);
 for(int i=0;i<2;i++){unsigned char verify[V8_BYTES];FILE*f=fopen(mapped(v8paths[i]),"rb");assert(f);assert(fread(verify,1,V8_BYTES,f)==V8_BYTES);assert(!fclose(f));assert(!memcmp(verify,v8bytes[i],V8_BYTES));assert(!unlink(mapped(v8paths[i])));}
 assert(!rmdir(mapped("E:\\MyROOffline\\Save08")));

 /* Test16 Save09 preserves Thief ranks and both source slots on actual disk. */
 combat_init(&g,1604,1604,openworld,NULL);g.joblevel=10;assert(combat_change_job(&g,4));g.joblevel=20;g.skillPoints=19;for(int i=0;i<3;i++)assert(skill_learn(&g,13));assert(skill_learn(&g,14));g.quickKind=1;g.quickId=14;g.mapId=3;
 assert(save_directory("E:\\MyROOffline\\Save09"));const char*p9="E:\\MyROOffline\\Save09\\char-a.dat";V9Character v9;v9_capture(&v9,&g,900);unsigned char b9[V9_BYTES],verify9[V9_BYTES];v9_encode(b9,&v9);FILE*f9=fopen(mapped(p9),"wb");assert(f9&&fwrite(b9,1,V9_BYTES,f9)==V9_BYTES&&!fclose(f9));
 assert(save_disk_import(&migrated,1604,1604,openworld,NULL)==1&&migrated.jobId==4&&migrated.ranks[9]==3&&migrated.ranks[10]==1&&migrated.extraItems[5]==0&&migrated.quickId==14);assert(save_commit(&s,&migrated));assert(save_load(&s,&recovered,1604,1604,openworld,NULL)&&recovered.jobId==4&&recovered.quickId==14);
 f9=fopen(mapped(p9),"rb");assert(f9&&fread(verify9,1,V9_BYTES,f9)==V9_BYTES&&!fclose(f9)&&!memcmp(b9,verify9,V9_BYTES));assert(!unlink(mapped(p9)));assert(!rmdir(mapped("E:\\MyROOffline\\Save09")));
 /* Save10 imports to separate Save11 slots and old bytes survive even failed import. */
 assert(save_directory("E:\\MyROOffline\\Save10"));const char*p10="E:\\MyROOffline\\Save10\\char-a.dat";V10Character v10;v10_capture(&v10,&g,1000);unsigned char b10[V10_BYTES],verify10[V10_BYTES];v10_encode(b10,&v10);FILE*f10=fopen(mapped(p10),"wb");assert(f10&&fwrite(b10,1,V10_BYTES,f10)==V10_BYTES&&!fclose(f10));
 assert(save_disk_import(&migrated,1604,1604,openworld,NULL)==1&&migrated.jobId==4&&migrated.joblevel==20&&migrated.ranks[9]==3&&!migrated.ranks[17]);assert(save_commit(&s,&migrated));
 f10=fopen(mapped(p10),"rb");assert(f10&&fread(verify10,1,V10_BYTES,f10)==V10_BYTES&&!fclose(f10)&&!memcmp(b10,verify10,V10_BYTES));
 b10[50]^=1;f10=fopen(mapped(p10),"wb");assert(f10&&fwrite(b10,1,V10_BYTES,f10)==V10_BYTES&&!fclose(f10));assert(save_disk_import(&migrated,1604,1604,openworld,NULL)==-1);
 f10=fopen(mapped(p10),"rb");assert(f10&&fread(verify10,1,V10_BYTES,f10)==V10_BYTES&&!fclose(f10)&&!memcmp(b10,verify10,V10_BYTES));assert(!unlink(mapped(p10)));assert(!rmdir(mapped("E:\\MyROOffline\\Save10")));
 /* Test21 Save11 remains unchanged after Save12 commit. */
 assert(save_directory("E:\\MyROOffline\\Save11"));const char*p11="E:\\MyROOffline\\Save11\\char-a.dat";V11Character v11;v11_capture(&v11,&g,1100);unsigned char b11[V11_BYTES],verify11[V11_BYTES];v11_encode(b11,&v11);FILE*f11=fopen(mapped(p11),"wb");assert(f11&&fwrite(b11,1,V11_BYTES,f11)==V11_BYTES&&!fclose(f11));assert(save_disk_import(&migrated,1604,1604,openworld,NULL)==1&&migrated.rbBinding==255);migrated.rbBinding=128;assert(save_commit(&s,&migrated));assert(save_load(&s,&recovered,1604,1604,openworld,NULL)&&recovered.rbBinding==128);f11=fopen(mapped(p11),"rb");assert(f11&&fread(verify11,1,V11_BYTES,f11)==V11_BYTES&&!fclose(f11)&&!memcmp(b11,verify11,V11_BYTES));assert(!unlink(mapped(p11)));assert(!rmdir(mapped("E:\\MyROOffline\\Save11")));

 /* Accepted Test22/23 Save12 import: preserve both quick slots and source bytes. */
 assert(save_directory("E:\\MyROOffline\\Save12"));const char*p12="E:\\MyROOffline\\Save12\\char-a.dat";g.rbBinding=128;V12Character v12;v12_capture(&v12,&g,1200);assert(v12_valid(&v12));unsigned char b12[V12_BYTES],verify12[V12_BYTES];v12_encode(b12,&v12);FILE*f12=fopen(mapped(p12),"wb");assert(f12&&fwrite(b12,1,V12_BYTES,f12)==V12_BYTES&&!fclose(f12));assert(save_disk_import(&migrated,1604,1604,openworld,NULL)==1&&migrated.rbBinding==128&&!migrated.ranks[25]&&!migrated.ranks[26]);assert(save_commit(&s,&migrated));f12=fopen(mapped(p12),"rb");assert(f12&&fread(verify12,1,V12_BYTES,f12)==V12_BYTES&&!fclose(f12)&&!memcmp(b12,verify12,V12_BYTES));assert(!unlink(mapped(p12)));assert(!rmdir(mapped("E:\\MyROOffline\\Save12")));
 assert(unlink(mapped(savePaths[0]))==0);assert(unlink(mapped(savePaths[1]))==0);
 assert(rmdir(mapped("E:\\MyROOffline\\Save14"))==0);assert(rmdir(mapped("E:\\MyROOffline"))==0);assert(rmdir(testRoot)==0);
 puts("PASS: actual native disk adapter via host shim: directory reuse, real file round-trip, write-through/flush, restart, partial write, flush error, access denial, unchanged v1/v2/v3/v4/v5/v6 files, retained Zeny during migration");return 0;
}
