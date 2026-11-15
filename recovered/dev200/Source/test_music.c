/* SPDX-License-Identifier: MIT. Actual decoder/resampler, complete supplied tracks. */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "music_stream.h"
int main(int argc,char**argv){assert(argc>1);MusicStream s;
 assert(!music_stream_start(&s,NULL,0)&&s.error==1);
 unsigned char bad[4096]={0};assert(!music_stream_start(&s,bad,sizeof(bad))&&s.error);
 for(int i=1;i<argc;i++){
  FILE*f=fopen(argv[i],"rb");assert(f);fseek(f,0,SEEK_END);unsigned n=ftell(f);rewind(f);unsigned char*b=malloc(n);assert(b&&fread(b,1,n,f)==n);fclose(f);
  assert(music_stream_start(&s,b,n));uint64_t energy=0;unsigned samples=0,firstLoop=0;
  while(s.loops<2){int x=music_stream_sample(&s);assert(!s.error&&x>=-32768&&x<=32767);energy+=x<0?-x:x;samples++;if(s.loops==1&&!firstLoop)firstLoop=samples;assert(samples<48000*700u);}
  assert(firstLoop>48000*100u&&energy>10000000);printf("PASS %s: loop %.2fs, decoded twice, nonzero PCM, bounded state %zu bytes\n",argv[i],firstLoop/48000.,sizeof(s));free(b);
 }
}
