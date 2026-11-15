/* SPDX-License-Identifier: MIT. Bounded MP3 decode/resample; decoder is CC0. */
#ifndef MYRO_MUSIC_STREAM_H
#define MYRO_MUSIC_STREAM_H
#define MINIMP3_IMPLEMENTATION
#define MINIMP3_ONLY_MP3
#define MINIMP3_NO_SIMD
#include "vendor/minimp3.h"
#include <string.h>
typedef struct {
 mp3dec_t decoder;short pcm[MINIMP3_MAX_SAMPLES_PER_FRAME];
 const unsigned char*data;unsigned bytes,offset,count,pos,phase,loops;
 unsigned outputSamples;int a,b,error;
} MusicStream;
static int music_source_next(MusicStream*s){
 for(unsigned attempt=0;attempt<16;attempt++){
  if(s->pos<s->count)return s->pcm[s->pos++];
  if(s->offset>=s->bytes){s->offset=0;s->loops++;mp3dec_init(&s->decoder);}
  unsigned remaining=s->bytes-s->offset;mp3dec_frame_info_t info={0};
  int n=mp3dec_decode_frame(&s->decoder,s->data+s->offset,remaining>4096?4096:remaining,s->pcm,&info);
  if(info.frame_bytes<=0){if(remaining<2048){s->offset=s->bytes;continue;}s->error=2;return 0;}
  if((unsigned)info.frame_bytes>remaining){s->error=3;return 0;}s->offset+=info.frame_bytes;
  if(n<=0)continue;
  if(info.hz!=22050||info.channels!=1||n>MINIMP3_MAX_SAMPLES_PER_FRAME){s->error=4;return 0;}
  s->count=n;s->pos=0;
 }
 s->error=5;return 0;
}
static int music_stream_start(MusicStream*s,const unsigned char*data,unsigned bytes){
 memset(s,0,sizeof(*s));s->data=data;s->bytes=bytes;if(!data||bytes<4){s->error=1;return 0;}
 mp3dec_init(&s->decoder);s->a=music_source_next(s);s->b=music_source_next(s);return !s->error;
}
static int music_stream_sample(MusicStream*s){
 if(s->error)return 0;
 int value=s->a+(int)((int64_t)(s->b-s->a)*s->phase/48000);
 s->phase+=22050;if(s->phase>=48000){s->phase-=48000;s->a=s->b;s->b=music_source_next(s);}
 s->outputSamples++;return value;
}
#endif
