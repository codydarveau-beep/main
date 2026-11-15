/* MIT. Real WAV blocks and publication through the actual audio worker lock. */
#define main original_audio_worker_tests50
#include "test_audio_recovery50.c"
#undef main
#include <zlib.h>
#define MYRO_HOST 1
static void fail(const char*s){fprintf(stderr,"%s\n",s);abort();}
static unsigned char*inflateasset(const char*n,const unsigned char*p,unsigned size,unsigned raw){(void)n;assert(!lock50);unsigned char*out=malloc(raw);assert(out);uLongf len=raw;assert(uncompress(out,&len,p,size)==Z_OK&&len==raw);return out;}
#include "system_disc50.h"
#include "class_sound_cache50.h"
int main(void){sound_init();Combat g;combat_init(&g,1500,1500,NULL,NULL);unsigned peak=0,heard=0;
 const short*protectedData[60];unsigned protectedLengths[60];memcpy(protectedData,soundData,sizeof(protectedData));memcpy(protectedLengths,soundLengths,sizeof(protectedLengths));
 for(unsigned repeat=0;repeat<3;repeat++)for(unsigned job=0;job<21;job++){
  g.jobId=job;class_sound_prepare50(&g);assert(!lock50&&classSoundBytes50<4*1024*1024);if(classSoundBytes50>peak)peak=classSoundBytes50;
  for(unsigned i=0;i<CLASS_SOUND_COUNT50;i++){unsigned id=60+i;if(!classSoundMemory50[i]){assert(!soundLengths[id]);continue;}assert(soundLengths[id]==classSounds50[i].frames&&soundData[id]==classSoundMemory50[i]);int nonzero=0;for(unsigned n=0;n<soundLengths[id];n++)nonzero|=soundData[id][n];assert(nonzero);sound_play(id);turn50(2);heard++;}
  assert(!memcmp(soundData,protectedData,sizeof(protectedData))&&!memcmp(soundLengths,protectedLengths,sizeof(protectedLengths)));
 }
 /* Returning to a class with no added clips kills old voices before freeing PCM. */
 g.jobId=0;class_sound_prepare50(&g);assert(!classSoundBytes50);for(int i=0;i<6;i++)if(soundVoices[i].id>=60)assert(!soundVoices[i].active);
 for(int i=0;i<CLASS_SOUND_COUNT50;i++)assert(!classSoundMemory50[i]);free(soundMemory);
 printf("PASS50 original class audio through21jobs/three cache cycles: %u playable clips, %u-byte maximum current-class PCM, unlocked file/decode work, old60clips unchanged and no retired live voice.\n",heard,peak);
}
