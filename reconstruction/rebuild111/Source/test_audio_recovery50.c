/* MIT. Exercise the actual audio worker with timed DMA consumption and failures. */
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
static unsigned clock50,cursor50,last50,next50,left50,played50,provided50,fences50,resets50,forceBad50,forceFrozen50;
static int running50,halted50=1,lock50;static unsigned char*allocation50;static const short*buffers50[32];
static void InitializeCriticalSection(int*l){*l=0;}
static void EnterCriticalSection(int*l){(void)l;assert(!lock50);lock50=1;}
static void LeaveCriticalSection(int*l){(void)l;assert(lock50);lock50=0;}
static void*MmAllocateContiguousMemoryEx(unsigned n,unsigned a,unsigned b,unsigned c,unsigned d){(void)a;(void)b;(void)c;(void)d;return allocation50=malloc(n);}
static void XAudioInit(int bits,int channels,void*callback,void*data){assert(bits==16&&channels==2&&!callback&&!data);}
static void publish50(void){fences50++;}
#define SOUND_DMA_PUBLISH50() publish50()
static unsigned snapshot50(void){unsigned cur=forceBad50?(last50+1)&31:cursor50;return cur|(last50<<8)|((halted50?1:0)<<16);}
#define SOUND_DMA_SNAPSHOT50() snapshot50()
static void XAudioProvideSamples(unsigned char*p,unsigned n,int final){
 assert(n==4096&&!final);assert(fences50==provided50+1);assert(p==allocation50+next50*4096);
 assert(!running50||halted50||next50!=cursor50);buffers50[next50]=(const short*)p;last50=next50;
 if(running50&&halted50){cursor50=next50;left50=1024;halted50=0;}
 next50=(next50+1)&31;provided50++;
}
static void XAudioPlay(void){running50=1;halted50=0;cursor50=0;left50=1024;}
static void XAudioPause(void){running50=0;}
static int reset50(void){running50=0;halted50=1;cursor50=last50=next50=0;left50=0;forceBad50=forceFrozen50=0;resets50++;return 1;}
#define SOUND_DMA_RESET50() reset50()
static HANDLE CreateThread(void*a,unsigned n,DWORD(*f)(LPVOID),void*b,unsigned c,void*d){(void)a;(void)f;(void)b;(void)c;(void)d;assert(n==65536);return (HANDLE)1;}
static int SetThreadPriority(HANDLE t,int p){(void)t;(void)p;return 1;}
static void Sleep(unsigned n){clock50+=n;}
static DWORD GetTickCount(void){return clock50;}
#include "sound.h"
static void consume50(unsigned frames){
 if(forceFrozen50)return;
 while(running50&&!halted50&&frames){unsigned n=frames<left50?frames:left50;left50-=n;frames-=n;if(!left50){assert(buffers50[cursor50]);played50++;if(cursor50==last50)halted50=1;else{cursor50=(cursor50+1)&31;left50=1024;}}}
}
static void turn50(unsigned ms){consume50(ms*48);clock50+=ms;sound_worker_step50(clock50);}
int main(void){
 sound_init();assert(soundDevice&&provided50==4&&fences50==4);sound_music_map(2);
 for(unsigned k=0;k<300000;k++)turn50(2); /* ten minutes, hundreds of ring wraps */
 assert(played50>28000&&!soundUnderruns&&!resets50&&!musicStream.error&&musicStream.loops>0&&soundNonzero);
 /* A stalled cursor one beyond LVI looks like32 queued blocks to the old policy:
  * old worker would never feed it. The bounded policy resets/reprimes it. */
 forceBad50=1;assert(sound_pending(soundSubmitted,(last50+1)&31,0)==32);
 unsigned before=provided50;for(unsigned k=0;k<12;k++)turn50(2);
 assert(resets50==1&&soundRestarts50==1&&provided50>before&&soundBadQueues50>=10);
 for(unsigned k=0;k<500;k++)turn50(2);assert(!musicStream.error);
 /* Nominal-looking frozen DMA is recovered too; silence/mute are not mistaken
  * for a stall, since hardware progress is independent of PCM values. */
 forceFrozen50=1;before=resets50;for(unsigned k=0;k<140;k++)turn50(2);assert(resets50==before+1);
 musicMuted=1;before=resets50;for(unsigned k=0;k<1000;k++)turn50(2);assert(resets50==before);musicMuted=0;
 /* Long scheduling gaps drain the queue, then a normal refill resumes it. */
 for(unsigned k=0;k<100;k++){turn50(500);for(unsigned j=0;j<20;j++)turn50(2);}assert(soundUnderruns>=100&&!musicStream.error);
 unsigned restarts=soundRestarts50;for(unsigned k=0;k<2000;k++)turn50(2);assert(soundRestarts50==restarts&&soundAhead<=4);
 /* Watchdog deadlines remain valid through unsigned clock rollover. */
 SoundWatch50 w={0};SoundSnapshot50 bad={.cursor=5,.last=4,.pending=SOUND_BAD_QUEUE50};
 assert(!sound_recover_needed50(&w,bad,UINT32_MAX-10));assert(sound_recover_needed50(&w,bad,15));
#ifdef MYRO_MUSIC_DISC50
 music_cache_keep50(-1);assert(!musicResident50);
#endif
 free(soundMemory);puts("PASS50 actual worker:600s DMA clock/ring wraps, publish fence ordering, invalid-queue stall reproduction/recovery, frozen DMA restart, mute safety,100 long underruns, resumed music and clock wrap.");
}
