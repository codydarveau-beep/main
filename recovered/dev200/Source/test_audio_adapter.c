/* SPDX-License-Identifier: MIT. Real polling producer, fake platform operations. */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "combat.h"
#define MYRO_SOUND_HOST
#define WINAPI
#define PAGE_READWRITE 1
#define PAGE_WRITECOMBINE 2
#define THREAD_PRIORITY_ABOVE_NORMAL 1
typedef unsigned DWORD;typedef void*LPVOID;typedef void*HANDLE;typedef int CRITICAL_SECTION;
static int lock,failAlloc,failThread,played;static unsigned queued;
static void InitializeCriticalSection(int*l){*l=0;}
static void EnterCriticalSection(int*l){(void)l;assert(!lock);lock=1;}
static void LeaveCriticalSection(int*l){(void)l;assert(lock);lock=0;}
static void*MmAllocateContiguousMemoryEx(unsigned n,unsigned a,unsigned b,unsigned c,unsigned d){(void)a;(void)b;(void)c;(void)d;return failAlloc?NULL:malloc(n);}
static void XAudioInit(int bits,int channels,void*callback,void*data){assert(bits==16&&channels==2&&!callback&&!data);}
static void XAudioProvideSamples(unsigned char*p,unsigned n,int final){assert(p&&n==4096&&!final);queued++;}
static void XAudioPlay(void){played=1;}
static void XAudioPause(void){played=0;}
static HANDLE CreateThread(void*a,unsigned n,DWORD(*f)(LPVOID),void*b,unsigned c,void*d){(void)a;(void)n;(void)f;(void)b;(void)c;(void)d;return failThread?NULL:(HANDLE)1;}
static int SetThreadPriority(HANDLE t,int p){(void)t;(void)p;return 1;}
static void Sleep(unsigned n){(void)n;}
static DWORD GetTickCount(void){return 0;}
#include "sound.h"
int main(void){
 failAlloc=1;sound_init();assert(!soundDevice&&strstr(soundStatus,"allocation"));failAlloc=0;
 sound_init();assert(soundDevice&&played&&queued==4&&soundCallbacks==4&&soundSubmitted==4&&!soundNonzero);
 sound_play(0);assert(soundQueued==1);for(int k=0;k<20;k++)sound_submit();assert(soundNonzero&&soundPeak&&soundCallbacks==24);
 unsigned q=soundQueued;sound_toggle();sound_play(0);assert(soundMuted&&soundQueued==q);
 sound_test_tone();assert(!soundMuted&&soundToneLeft==24000);sound_submit();assert(soundToneLeft==24000-1024);
 for(int k=0;k<24;k++)sound_submit();assert(!soundToneLeft);
 // Music selection, shared themes, independent gain/mute and field transitions.
 sound_music_map(2);for(int k=0;k<20;k++)sound_submit();assert(musicCurrent==2&&!musicStream.error&&musicStream.outputSamples>0);
 sound_music_map(0);for(int k=0;k<20;k++)sound_submit();assert(musicCurrent==3&&!musicStream.error);
 unsigned changes=musicChanges,playedSamples=musicStream.outputSamples;sound_music_map(1);for(int k=0;k<5;k++)sound_submit();assert(musicChanges==changes&&musicStream.outputSamples>playedSamples);
 sound_music_toggle();unsigned beforeNonzero=soundNonzero;for(int k=0;k<5;k++)sound_submit();assert(soundNonzero==beforeNonzero);
 sound_music_volume(1000);assert(musicVolume==100&&!musicMuted);sound_music_volume(-1000);assert(!musicVolume);sound_effects_volume(-1000);assert(!soundVolume);sound_effects_volume(1000);assert(soundVolume==100);
 for(unsigned map=0;map<MUSIC_MAP_COUNT49;map++){sound_music_map(map);for(int k=0;k<10;k++)sound_submit();assert(musicCurrent==(int)musicMapTracks[map]&&!musicStream.error);}
 // Long running playback and the exact reported Payon -> Sograt -> Prontera route.
 musicVolume=25;for(int k=0;k<12000;k++)sound_submit();assert(musicStream.loops>0&&!musicStream.error);
 for(int round=0;round<20;round++){unsigned route[]={11,7,2,12,13,16,0};for(unsigned n=0;n<sizeof(route)/sizeof(route[0]);n++){sound_music_map(route[n]);for(int k=0;k<10;k++)sound_submit();assert(musicCurrent==music_map_track49(route[n])&&!musicStream.error);}}
 assert(strcmp(musicNames[music_map_track49(11)],"14.mp3")==0);assert(strcmp(musicNames[music_map_track49(7)],"24.mp3")==0);assert(strcmp(musicNames[music_map_track49(2)],"08.mp3")==0);
 sound_music_map(999);for(int k=0;k<10;k++)sound_submit();assert(musicCurrent==-1);
 free(soundMemory);
 puts("PASS native producer: allocation failure, four-buffer prime, real PCM refill, mute, beep and counters. All18 source map themes,256seconds continuous playback,140 repeated post-loop travel changes, same-theme continuity and invalid-map stop passed.");
}
