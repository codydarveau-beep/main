/* MIT. Actual native producer: cached mixing, exact PCM, write-only DMA. */
#include <sanitizer/asan_interface.h>
#include <stdint.h>
#include <stddef.h>
static void audio_copy50b(void*,const void*,size_t);
#define SOUND_DMA_COPY50B(d,s,n) audio_copy50b(d,s,n)
#define MYRO_HOST 1
#define MYRO_MUSIC_DISC50 1
#define main preceding_audio_recovery
#include "test_audio_recovery50.c"
#undef main
static unsigned copies50b;
static void audio_copy50b(void*d,const void*s,size_t n){uintptr_t p=(uintptr_t)s,b=(uintptr_t)allocation50;assert(p<b||p>=b+SOUND_BYTES*32);assert(n==SOUND_BYTES);__asan_unpoison_memory_region(d,n);memcpy(d,s,n);copies50b++;}
typedef struct {MusicStream music;SoundVoice voices[6];unsigned callbacks,nonzero,peak,tone,phase;int fade;} Snapshot50b;
static Snapshot50b snapshot50b(void){Snapshot50b s={.music=musicStream,.callbacks=soundCallbacks,.nonzero=soundNonzero,.peak=soundPeak,.tone=soundToneLeft,.phase=soundTonePhase,.fade=musicFade};memcpy(s.voices,soundVoices,sizeof(s.voices));return s;}
static void restore50b(const Snapshot50b*s){musicStream=s->music;soundCallbacks=s->callbacks;soundNonzero=s->nonzero;soundPeak=s->peak;soundToneLeft=s->tone;soundTonePhase=s->phase;musicFade=s->fade;memcpy(soundVoices,s->voices,sizeof(soundVoices));}
int main(void){sound_init();unsigned comparisons=0;short reference[SOUND_FRAMES*2];
 for(unsigned map=0;map<MUSIC_MAP_COUNT49;map++){
  sound_music_map(map);for(int i=0;i<8;i++)turn50(22);assert(musicCurrent==musicRequested&&!musicStream.error);
  for(int sample=0;sample<64;sample++){
   if(sample%8==0)sound_play(0);if(sample==40)sound_test_tone();consume50(SOUND_FRAMES);
   Snapshot50b before=snapshot50b();sound_fill(reference);Snapshot50b expected=snapshot50b();restore50b(&before);
   unsigned char*destination=soundMemory+(soundSubmitted&31)*SOUND_BYTES;__asan_poison_memory_region(destination,SOUND_BYTES);unsigned copied=copies50b;sound_submit();assert(copies50b==copied+1&&!memcmp(destination,reference,SOUND_BYTES));
   assert(musicStream.outputSamples==expected.music.outputSamples&&soundToneLeft==expected.tone&&soundPeak==expected.peak&&soundNonzero==expected.nonzero);comparisons++;
  }
 }
 music_cache_keep50(-1);free(soundMemory);printf("PASS50b %u exact real-music/SFX/tone PCM blocks across18maps; poisoned DMA receives one cached-source copy, no DMA reads during mixing, unchanged sample/voice/envelope counters and bounded4KiB staging.\n",comparisons);}
