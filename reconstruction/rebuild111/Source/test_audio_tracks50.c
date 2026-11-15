#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "music.h"
int main(void){music_blob_init();for(int i=0;i<MUSIC_TRACKS;i++){
 assert(music_stream_start(&musicStream,musicData[i],musicSizes[i]));
 unsigned samples=0,audible=0,nonzero=0,maxQuiet=0,quiet=0;int peak=0;
 while(musicStream.loops<2&&!musicStream.error&&samples<48000u*1200){int v=music_stream_sample(&musicStream);samples++;int a=v<0?-v:v;if(a>peak)peak=a;if(a)nonzero++;if(a>50){audible++;quiet=0;}else if(++quiet>maxQuiet)maxQuiet=quiet;}
 printf("track%d %s bytes%u samples%u seconds%u loops%u error%d audiblePercent%u nonzeroPercent%u peak%d maxQuietMs%u\n",i,musicNames[i],musicSizes[i],samples,samples/48000,musicStream.loops,musicStream.error,100u*audible/samples,100u*nonzero/samples,peak,maxQuiet/48);fflush(stdout);
 assert(!musicStream.error&&musicStream.loops>=2&&audible>samples/2);
}return 0;}
