#define main old_creatures_main
#include "test_creatures51.c"
#undef main
#include "projection.h"
#define NV097_SET_ALPHA_FUNC 0
#define NV097_SET_ALPHA_REF 0
#include "guardian_draw51.h"
#define SOUND_COUNT 560
static int soundDevice=1,soundLock;
static const short*soundData[SOUND_COUNT];static unsigned soundLengths[SOUND_COUNT];
#include "sound_mix.h"
static SoundVoice soundVoices[6];
static void EnterCriticalSection(int*p){(void)p;}static void LeaveCriticalSection(int*p){(void)p;}
#include "death_sound51.h"
int main(void){unsigned poses=0,sounds=0;float m[16];world_camera(m,100,100,0,.7f,.8f,2.5f);
 for(unsigned bank=7;bank<=8;bank++){
  const unsigned(*groups)[3]=bank==7?guardianGroups7:guardianGroups8;
  guardianDraw51[1]=(GuardianDraw51){bank,0,0,0,100,100,0,0,1,1};guardian_prepare51();
  for(unsigned group=0;group<5;group++)for(unsigned frame=0;frame<groups[group][1];frame++){
   GuardianDraw51*a=&guardianDraw51[1];a->group=group;a->elapsed=frame*.025f;a->repeat=0;guardian_draw51(1,m);poses++;
   const unsigned(*desc)[4]=bank==7?guardianPoses7:guardianPoses8;unsigned f=guardianFrame51[bank-7],count=desc[f][2]/sizeof(float);for(unsigned i=0;i<count;i++)assert(isfinite(guardianPose51[bank-7][i]));
  }
  guardian_reset51();assert(!guardianTextures51[bank-7]&&!guardianPose51[bank-7]);
 }
 for(unsigned id=116;id<SOUND_COUNT;id++){death_sound_prepare51(id);if(deathSounds51[id-116][2]){sounds++;assert(soundLengths[id]*2==deathSounds51[id-116][2]);soundVoices[0]=(SoundVoice){id,0,1};}assert(deathBytes51<=2097152);}
 for(unsigned i=0;i<12;i++)free(deathCache51[i].p);enemy_cache_clear51();printf("PASS %u original guardian pose draws with native projection and teardown; %u death cues, bounded PCM cache/voice retirement\n",poses,sounds);
}
