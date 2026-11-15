/* MIT. Exercise the native WinAPI music-reader branch with bounded file shims. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <zlib.h>
typedef FILE*HANDLE;typedef unsigned DWORD;typedef int BOOL;
#define INVALID_HANDLE_VALUE NULL
#define GENERIC_READ 1
#define FILE_SHARE_READ 2
#define OPEN_EXISTING 3
#define FILE_ATTRIBUTE_NORMAL 4
#define FILE_BEGIN SEEK_SET
static unsigned opens50,closes50,requests50;static int fault50;
static HANDLE CreateFile(const char*name,unsigned access,unsigned share,void*security,unsigned mode,unsigned attr,void*template){
 assert(!strcmp(name,"D:\\music.bin")&&access==1&&share==2&&!security&&mode==3&&attr==4&&!template);
 if(fault50==1)return INVALID_HANDLE_VALUE;
 const char*path=getenv("MYRO_MUSIC_PATH50");if(!path)path="../Music/music.bin";
 FILE*f=fopen(path,"rb");assert(f);opens50++;return f;
}
static DWORD GetFileSize(HANDLE f,DWORD*high){assert(!fseek(f,0,SEEK_END));long size=ftell(f);assert(size>0);*high=fault50==2?1:0;return fault50==3?size-1:size;}
static void SetLastError(unsigned n){assert(!n);}
static DWORD SetFilePointer(HANDLE f,unsigned offset,void*high,unsigned method){assert(!high&&method==FILE_BEGIN);assert(!fseek(f,offset,method));return fault50==4?offset+1:offset;}
static BOOL ReadFile(HANDLE f,void*p,unsigned n,DWORD*got,void*overlapped){
 assert(n>0&&n<=32768&&!overlapped);requests50++;
 if(fault50==5){*got=0;return 0;}if(fault50==6){*got=0;return 1;}
 *got=fread(p,1,fault50==7&&n>1?n/2:n,f);if(fault50==8&&*got)((unsigned char*)p)[0]^=1;
 return 1;
}
static void CloseHandle(HANDLE f){assert(!fclose(f));closes50++;}
#define MYRO_MUSIC_DISC50 1
#include "music_data.h"
int main(void){
 music_blob_init();
 for(unsigned i=0;i<MUSIC_TRACKS;i++){
  music_cache_keep50(-1);unsigned char*p=music_read_track50(i);assert(p&&!musicLoadError50&&crc32(0,p,musicSizes[i])==musicBlobs50[i].crc);music_cache_install50(i,p);assert(musicResident50==musicSizes[i]);
 }
 music_cache_keep50(-1);assert(!musicResident50);
 for(fault50=1;fault50<=8;fault50++){
  unsigned char*p=music_read_track50(2);
  if(fault50==7){assert(p&&!musicLoadError50);free(p);}else assert(!p&&musicLoadError50==(fault50==1?4:fault50<=4?5:fault50<=6?6:7));
  assert(opens50==closes50&&!musicResident50);
 }
 fault50=0;assert(!music_read_track50(MUSIC_TRACKS)&&musicLoadError50==1);
 printf("PASS50 native WinAPI music reader:10 CRC-checked tracks, bounded32KiB requests (%u), open/size/highword/seek/short-read/failure/CRC guards, all handles and buffers released.\n",requests50);
}
