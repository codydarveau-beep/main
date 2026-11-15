/* MIT. Read a complete encoded track outside the audio lock; decoder loops RAM.
 * At most the current and incoming MP3 are resident. Never perform disc reads in
 * the audio worker. Mutation/release helpers run under soundLock.
 */
#include "music_pack50.h"
#include <zlib.h>
static unsigned musicResident50,musicPeakResident50,musicDiscReads50;
static int musicLoadError50;
static void music_cache_keep50(int track){
 for(int i=0;i<MUSIC_TRACKS;i++)if(i!=track&&musicData[i]){
  free((void*)musicData[i]);musicData[i]=NULL;musicResident50-=musicSizes[i];
 }
}
static unsigned char*music_read_track50(unsigned track){
 if(track>=MUSIC_TRACKS){musicLoadError50=1;return NULL;}
 const MusicBlob50*b=&musicBlobs50[track];
 if(!b->bytes||b->bytes>2*1024*1024||b->offset>MUSIC_FILE_BYTES50||b->bytes>MUSIC_FILE_BYTES50-b->offset){musicLoadError50=2;return NULL;}
 unsigned char*p=malloc(b->bytes);if(!p){musicLoadError50=3;return NULL;}unsigned done=0;
#ifdef MYRO_HOST
 const char*path=getenv("MYRO_MUSIC_PATH50");if(!path)path="../Music/music.bin";
 FILE*f=fopen(path,"rb");if(!f){free(p);musicLoadError50=4;return NULL;}
 int bad=fseek(f,0,SEEK_END);long size=ftell(f);
 if(bad||size!=MUSIC_FILE_BYTES50||fseek(f,b->offset,SEEK_SET)){fclose(f);free(p);musicLoadError50=5;return NULL;}
 while(done<b->bytes){unsigned n=b->bytes-done;if(n>32768)n=32768;unsigned got=fread(p+done,1,n,f);if(!got){fclose(f);free(p);musicLoadError50=6;return NULL;}done+=got;}fclose(f);
#else
 HANDLE f=CreateFile("D:\\music.bin",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
 if(f==INVALID_HANDLE_VALUE){free(p);musicLoadError50=4;return NULL;}
 DWORD high=0,size=GetFileSize(f,&high);SetLastError(0);DWORD at=SetFilePointer(f,b->offset,NULL,FILE_BEGIN);
 if(high||size!=MUSIC_FILE_BYTES50||at!=b->offset){CloseHandle(f);free(p);musicLoadError50=5;return NULL;}
 while(done<b->bytes){DWORD n=b->bytes-done,got=0;if(n>32768)n=32768;BOOL ok=ReadFile(f,p+done,n,&got,NULL);if(!ok||!got||got>n){CloseHandle(f);free(p);musicLoadError50=6;return NULL;}done+=got;}CloseHandle(f);
#endif
 if(crc32(0,p,b->bytes)!=b->crc){free(p);musicLoadError50=7;return NULL;}
 musicLoadError50=0;musicDiscReads50++;return p;
}
static void music_cache_install50(unsigned track,unsigned char*p){
 musicData[track]=p;musicResident50+=musicSizes[track];
 if(musicResident50>musicPeakResident50)musicPeakResident50=musicResident50;
}
