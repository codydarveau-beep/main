/* MIT. Integer elapsed-time averaging, paused snapshots and counter rollover. */
#include <assert.h>
#include <stdio.h>
#include "frame_profile50b.h"
int main(void){FrameProfile50b p={0};uint64_t at=0;unsigned audio=0;
 for(int f=0;f<50;f++){frame_span50b(&p,FRAME_UPDATE50B,at+1000,&at);frame_span50b(&p,FRAME_PREPARE50B,at+2000,&at);frame_span50b(&p,FRAME_DRAW50B,at+3000,&at);frame_span50b(&p,FRAME_HUD50B,at+4000,&at);frame_span50b(&p,FRAME_WAIT50B,at+10000,&at);audio+=500;frame_finish50b(&p,1000000,audio,1);}
 assert(p.ready);const unsigned expected[]={10,20,30,40,100,5};for(int i=0;i<6;i++)assert(p.tenths[i]==expected[i]);
 for(int f=0;f<100;f++){p.current[0]=99999;audio+=10000;frame_finish50b(&p,1000000,audio,0);}for(int i=0;i<6;i++)assert(p.tenths[i]==expected[i]);
 memset(&p,0,sizeof(p));p.audioPrevious=UINT32_MAX-99;audio=100;frame_finish50b(&p,1000000,audio,1);assert(p.audio==200);
 memset(&p,0,sizeof(p));p.current[0]=733333333;frame_finish50b(&p,733333333,73333333,1);assert(p.tenths[0]==10000&&p.tenths[5]==999); /* 64-bit products, integer truncation. */
 puts("PASS50b frame-stage averaging at two clock frequencies, overlapping audio accounting, pause exclusion/retained snapshots, 32-bit audio wrap and64-bit scaling.");}
