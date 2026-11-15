/* MIT. Real encoded pack/producer/cache, rapid requests and I/O failure paths. */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
static int lock,feedDuringRead50;
static unsigned readsOutsideLock50;
static void sound_submit(void);
static size_t music_test_read50(void*p,size_t size,size_t n,FILE*f){
 assert(!lock);readsOutsideLock50++;
 if(feedDuringRead50)sound_submit();
 return fread(p,size,n,f);
}
#define MYRO_HOST 1
#define MYRO_MUSIC_DISC50 1
#define fread music_test_read50
#define main old_audio_adapter50_main
#include "test_audio_adapter.c"
#undef main
#undef fread
extern const unsigned char music0[],music1[],music2[],music3[],music4[],music5[],music6[],music7[],music8[],music9[];
static const unsigned char*original50[]={music0,music1,music2,music3,music4,music5,music6,music7,music8,music9};
static unsigned encoded_residency50(void){unsigned sum=0,count=0;for(int i=0;i<MUSIC_TRACKS;i++)if(musicData[i]){sum+=musicSizes[i];count++;}assert(sum==musicResident50&&count<=2);return sum;}
static void settle50(void){for(int n=0;n<6;n++)sound_submit();assert(musicCurrent==musicRequested);assert(!musicStream.error);assert(encoded_residency50()==(musicCurrent<0?0:musicSizes[musicCurrent]));}
int main(void){
 sound_init();assert(soundDevice&&!musicResident50);feedDuringRead50=1;
 unsigned all=0;for(int i=0;i<MUSIC_TRACKS;i++)all+=musicSizes[i];assert(all==9676327);
 for(unsigned round=0;round<8;round++)for(unsigned map=0;map<MUSIC_MAP_COUNT49;map++){
  unsigned track=music_map_track49(map),before=musicDiscReads50;
  int same=musicCurrent==(int)track;sound_music_map(map);encoded_residency50();
  if(same)assert(musicDiscReads50==before);
  settle50();assert(musicCurrent==(int)track);
  assert(!memcmp(musicData[track],original50[track],musicSizes[track]));
  /* Compare actual output samples against the unchanged reference decoder. */
  MusicStream reference=musicStream;for(unsigned sample=0;sample<8192;sample++){
   int expected=(music_stream_sample(&reference)*musicVolume/100)*2048/2048;
   assert(musicFade==2048&&music_output()==expected);
  }
 }
 /* Incoming requests can be replaced before the fade finishes, or cancelled
  * by immediately returning to the still-playing map. No abandoned MP3 stays. */
 for(int cycle=0;cycle<80;cycle++){
  sound_music_map(3);sound_music_map(2);sound_music_map(7);sound_music_map(3);
  encoded_residency50();settle50();assert(musicCurrent==4&&musicResident50==778971);
 }
 assert(all-musicResident50==8897356);assert(musicPeakResident50<=2*1644147);
 /* Missing, wrong-length and corrupt packs keep current music and remain
  * retryable. They must never hold the audio lock during file access. */
 feedDuringRead50=0;const char*source=getenv("MYRO_MUSIC_PATH50");if(!source)source="../Music/music.bin";
 char originalPath[1024];snprintf(originalPath,sizeof(originalPath),"%s",source);
 assert(!setenv("MYRO_MUSIC_PATH50","/tmp/myro50-missing-music.bin",1));
 sound_music_map(2);assert(musicLoadError50==4&&musicCurrent==4&&musicRequested==4);settle50();
 FILE*in=fopen(originalPath,"rb");assert(in);unsigned char*pack=malloc(MUSIC_FILE_BYTES50);assert(pack);assert(fread(pack,1,MUSIC_FILE_BYTES50,in)==MUSIC_FILE_BYTES50&&!fclose(in));
 char fault[]="/tmp/myro-music50-XXXXXX";int fd=mkstemp(fault);assert(fd>=0);FILE*out=fdopen(fd,"wb");assert(out);assert(fwrite(pack,1,MUSIC_FILE_BYTES50-1,out)==MUSIC_FILE_BYTES50-1&&!fclose(out));
 assert(!setenv("MYRO_MUSIC_PATH50",fault,1));sound_music_map(2);assert(musicLoadError50==5&&musicCurrent==4&&musicRequested==4);settle50();
 pack[musicBlobs50[2].offset+800]^=1;out=fopen(fault,"wb");assert(out);assert(fwrite(pack,1,MUSIC_FILE_BYTES50,out)==MUSIC_FILE_BYTES50&&!fclose(out));
 sound_music_map(2);assert(musicLoadError50==7&&musicCurrent==4&&musicRequested==4);settle50();free(pack);assert(!remove(fault));
 assert(!setenv("MYRO_MUSIC_PATH50",originalPath,1));sound_music_map(2);settle50();assert(!musicLoadError50&&musicCurrent==2);
 sound_music_map(999);settle50();assert(!musicResident50&&musicCurrent==-1);
 assert(readsOutsideLock50>1000&&!lock);free(soundMemory);
 printf("PASS50 original10 MP3 byte/sample equality,144 map visits,320 rapid requests, old playback fed during unlocked reads, missing/truncated/CRC recovery, two-buffer peak %u, Izlude encoded RAM saving8897356 bytes.\n",musicPeakResident50);
}
