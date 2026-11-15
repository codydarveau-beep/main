/* SPDX-License-Identifier: MIT. Native AC97 producer polled by a worker thread.
 * nxdk/xemu callback issue: https://github.com/xemu-project/xemu/issues/1529
 * SDL remains in use for controllers; SDL audio is not opened in this build.
 */
#ifndef MYRO_SOUND_HOST
#include <hal/audio.h>
#include <xboxkrnl/xboxkrnl.h>
#endif
#include "npc_sound_names64.h"
#define SOUND_COUNT (SOUND_NPC_FIRST64+NPC_SOUND_COUNT64)
#define SOUND_FRAMES 1024
#define SOUND_BYTES (SOUND_FRAMES*4)
extern const short*soundData[SOUND_COUNT];extern unsigned soundLengths[SOUND_COUNT];
#include "sound_mix.h"
#include "sound_poll.h"
#include "sound_watch50.h"
#include "music.h"
#include "menu_sound58.h"
static SoundVoice soundVoices[6];static int soundDevice;
static volatile unsigned soundCallbacks,soundQueued,soundPeak,soundNonzero,soundUnderruns,soundHardwareCursor,soundAhead;
static volatile unsigned soundRestarts50,soundBadQueues50,soundHardwareLast50,soundHardwareFlags50;
static SoundWatch50 soundWatch50;static int soundWasDrained50;
static unsigned soundToneLeft,soundTonePhase,soundSubmitted;static char soundDriver[24]="AC97 polling";
static int soundMuted,soundVolume=100;static char soundStatus[100]="SFX not initialized";
static CRITICAL_SECTION soundLock;static unsigned char*soundMemory;static HANDLE soundThread;
static void sound_fill(short*out){
 for(unsigned i=0;i<SOUND_FRAMES;i++){
  int effects=sound_sample_buses61(soundVoices,6,soundData,soundLengths,SOUND_COUNT,SOUND_TOTAL50,enemyMuted60?0:enemyVolume60);if(menuSoundActive58&&menuSoundEnabled58&&!soundMuted){if(menuSoundPosition58<sizeof(menuPoring58)/sizeof(*menuPoring58))effects+=menuPoring58[menuSoundPosition58++]*16*(int)menuVolume60/100;else menuSoundActive58=0;}out[i*2]=out[i*2+1]=sound_output52(soundMuted?0:effects,soundVolume,music_output());
  if(soundToneLeft){int envelope=soundToneLeft<960?soundToneLeft:960;int tone=((soundTonePhase++/55)&1)?2200:-2200;tone=tone*envelope/960;out[i*2]=out[i*2+1]=(short)tone;soundToneLeft--;}
  int v=out[i*2];unsigned peak=v<0?-v:v;if(peak){soundNonzero++;if(peak>soundPeak)soundPeak=peak;}
 }
 soundCallbacks++;
}
/* Mix/read in cached RAM; DMA memory is a sequential write-only destination. */
static short soundScratch50b[SOUND_FRAMES*2];
static void sound_submit(void){
 unsigned char*buffer=soundMemory+(soundSubmitted&31)*SOUND_BYTES;
 EnterCriticalSection(&soundLock);sound_fill(soundScratch50b);LeaveCriticalSection(&soundLock);
#ifdef SOUND_DMA_COPY50B
 SOUND_DMA_COPY50B(buffer,soundScratch50b,SOUND_BYTES);
#else
 memcpy(buffer,soundScratch50b,SOUND_BYTES);
#endif
 /* Flush write-combining stores before publishing this buffer to DMA. */
#ifdef SOUND_DMA_PUBLISH50
 SOUND_DMA_PUBLISH50();
#elif !defined(MYRO_SOUND_HOST)
 __asm__ __volatile__("sfence" ::: "memory");
#endif
 XAudioProvideSamples(buffer,SOUND_BYTES,0);soundSubmitted++;
}
static SoundSnapshot50 sound_hardware_snapshot50(void){
 /* One aligned 32-bit read captures CIV/LVI/status from the same instant. */
#ifdef SOUND_DMA_SNAPSHOT50
 unsigned word=SOUND_DMA_SNAPSHOT50();
#else
 unsigned word=*(volatile uint32_t*)0xfec00114;
#endif
 SoundSnapshot50 s=sound_snapshot50(soundSubmitted,word);
 soundHardwareCursor=s.cursor;soundHardwareLast50=s.last;soundHardwareFlags50=s.flags;
 return s;
}
static int sound_dma_reset50(void){
#ifdef SOUND_DMA_RESET50
 return SOUND_DMA_RESET50();
#elif !defined(MYRO_SOUND_HOST)
 extern AC97_DEVICE ac97Device;
 XAudioPause();volatile unsigned char*regs=(volatile unsigned char*)0xfec00000;
 regs[0x11b]=0x1e;regs[0x17b]=0x1e;
 for(unsigned n=0;n<20;n++){
  if(!((regs[0x11b]|regs[0x17b])&2)){ac97Device.nextDescriptor=0;return 1;}
  Sleep(1);
 }
 return 0;
#else
 return 1;
#endif
}
static int sound_restart50(unsigned now){
 if(!sound_dma_reset50()){
  snprintf(soundStatus,sizeof(soundStatus),"Audio DMA reset failed; retrying.");
  soundWatch50.progressAt=now;soundWatch50.badAt=now;return 0;
 }
 soundSubmitted=0;for(unsigned i=0;i<SOUND_AHEAD50;i++)sound_submit();XAudioPlay();
 memset(&soundWatch50,0,sizeof(soundWatch50));soundWasDrained50=0;soundRestarts50++;
 snprintf(soundStatus,sizeof(soundStatus),"Audio output recovered (%u).",soundRestarts50);return 1;
}
static void sound_worker_step50(unsigned now){
 SoundSnapshot50 s=sound_hardware_snapshot50();soundAhead=s.pending;
 if(s.pending==SOUND_BAD_QUEUE50)soundBadQueues50++;
 if(sound_recover_needed50(&soundWatch50,s,now)){sound_restart50(now);return;}
 if(!s.pending){if(!soundWasDrained50)soundUnderruns++;soundWasDrained50=1;}
 else soundWasDrained50=0;
 /* Re-read the live cursor after each decode/mix. Never assume hardware stood
  * still while producing a block, and bound catch-up work per worker turn. */
 for(unsigned n=0;s.pending<SOUND_AHEAD50&&n<8;n++){
  sound_submit();s=sound_hardware_snapshot50();soundAhead=s.pending;
 }
}
static void sound_profile_step50b(unsigned now){
#ifdef FRAME_AUDIO_CLOCK50B
 unsigned at=FRAME_AUDIO_CLOCK50B();
#endif
 sound_worker_step50(now);
#ifdef FRAME_AUDIO_CLOCK50B
 FRAME_AUDIO_ADD50B(FRAME_AUDIO_CLOCK50B()-at);
#endif
}
static DWORD WINAPI sound_worker(LPVOID unused){
 (void)unused;for(;;){sound_profile_step50b(GetTickCount());Sleep(2);}return 0;
}
static void sound_init(void){
 music_blob_init();InitializeCriticalSection(&soundLock);
 soundMemory=MmAllocateContiguousMemoryEx(SOUND_BYTES*32,0,0x03ffafff,4096,PAGE_READWRITE|PAGE_WRITECOMBINE);
 if(!soundMemory){snprintf(soundStatus,sizeof(soundStatus),"SFX: DMA buffer allocation failed");return;}
 memset(soundMemory,0,SOUND_BYTES*32);XAudioInit(16,2,NULL,NULL);
 /* Prime before playback. No user callback, SDL semaphore or audio IRQ
  * is needed to feed subsequent buffers. */
 for(unsigned i=0;i<SOUND_AHEAD50;i++)sound_submit();XAudioPlay();
 soundThread=CreateThread(NULL,65536,sound_worker,NULL,0,NULL);
 if(!soundThread){XAudioPause();snprintf(soundStatus,sizeof(soundStatus),"SFX: audio worker creation failed");return;}
 SetThreadPriority(soundThread,THREAD_PRIORITY_ABOVE_NORMAL);soundDevice=1;
 snprintf(soundStatus,sizeof(soundStatus),"SFX ready - native AC97 / polled DMA");
}

#include "death_sound51.h"
static void class_sound_play180(unsigned id);
static void sound_play(unsigned id){class_sound_play180(id);
 if(sound_creature61(id,SOUND_TOTAL50)&&(enemyMuted60||!enemyVolume60))return;death_sound_prepare51(id);
 if(!soundDevice||id>=SOUND_COUNT||!soundLengths[id])return;
 EnterCriticalSection(&soundLock);
 if(!soundMuted&&sound_voice_start191(soundVoices,6,id,id>=SOUND_NPC_FIRST64,id==SOUND_JUPITEL180?2u:0u))soundQueued++;
 LeaveCriticalSection(&soundLock);
}
static void sound_menu_enabled58(unsigned enabled){if(!soundDevice){menuSoundEnabled58=!!enabled;return;}EnterCriticalSection(&soundLock);menuSoundEnabled58=!!enabled;if(!enabled)menuSoundActive58=0;LeaveCriticalSection(&soundLock);}
static void sound_menu58(void){if(!soundDevice||!menuSoundEnabled58)return;EnterCriticalSection(&soundLock);if(!soundMuted){menuSoundPosition58=0;menuSoundActive58=1;}LeaveCriticalSection(&soundLock);}
static void sound_toggle(void){if(!soundDevice)return;EnterCriticalSection(&soundLock);soundMuted=!soundMuted;memset(soundVoices,0,sizeof(soundVoices));menuSoundActive58=0;soundToneLeft=0;LeaveCriticalSection(&soundLock);}
static void sound_drain(Combat*g){unsigned id;while(combat_next_sound(g,&id))sound_play(id);}
static void sound_test_tone(void){if(!soundDevice)return;EnterCriticalSection(&soundLock);soundMuted=0;soundToneLeft=24000;soundTonePhase=0;LeaveCriticalSection(&soundLock);}

static void sound_music_track58(int track){if(!soundDevice)return;
#ifdef MYRO_MUSIC_DISC50
 EnterCriticalSection(&soundLock);
 if(track<0){musicRequested=-1;LeaveCriticalSection(&soundLock);return;}
 if(musicData[track]){musicRequested=track;if(track==musicCurrent)music_cache_keep50(musicCurrent);LeaveCriticalSection(&soundLock);return;}
 /* Cancel an unplayed request before reading so rapid map switches keep only
  * two encoded buffers. Current playback and its worker remain live during I/O. */
 musicRequested=musicCurrent;music_cache_keep50(musicCurrent);LeaveCriticalSection(&soundLock);
 unsigned char*p=music_read_track50((unsigned)track);
 EnterCriticalSection(&soundLock);
 if(p){music_cache_install50((unsigned)track,p);musicRequested=track;}
 else snprintf(soundStatus,sizeof(soundStatus),"Music read error %d; previous track kept.",musicLoadError50);
 LeaveCriticalSection(&soundLock);
#else
 EnterCriticalSection(&soundLock);musicRequested=track;LeaveCriticalSection(&soundLock);
#endif
}
static void sound_music_map(unsigned map){sound_music_track58(music_map_track49(map));}
static void sound_music_login58(void){for(unsigned i=0;i<MUSIC_TRACKS;i++)if(!strcmp(musicNames[i],"01.mp3")){sound_music_track58((int)i);return;}}
static void sound_music_volume(int delta){if(!soundDevice)return;EnterCriticalSection(&soundLock);musicVolume+=delta;if(musicVolume<0)musicVolume=0;if(musicVolume>100)musicVolume=100;if(delta>0)musicMuted=0;LeaveCriticalSection(&soundLock);}
static void sound_effects_volume(int delta){if(!soundDevice)return;EnterCriticalSection(&soundLock);soundVolume+=delta;if(soundVolume<0)soundVolume=0;if(soundVolume>100)soundVolume=100;if(delta>0)soundMuted=0;LeaveCriticalSection(&soundLock);}
static void sound_music_toggle(void){if(!soundDevice)return;EnterCriticalSection(&soundLock);musicMuted=!musicMuted;LeaveCriticalSection(&soundLock);}
