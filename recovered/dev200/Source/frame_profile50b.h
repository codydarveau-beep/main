/* MIT. Integer-only wall-time accounting. Audio overlaps main-thread spans. */
#ifndef MYRO_FRAME_PROFILE50B_H
#define MYRO_FRAME_PROFILE50B_H
#include <stdint.h>
#include <string.h>
enum {FRAME_UPDATE50B,FRAME_PREPARE50B,FRAME_DRAW50B,FRAME_HUD50B,FRAME_WAIT50B,FRAME_STAGES50B};
enum{DRAW_UPLOAD51,DRAW_TERRAIN51,DRAW_SCENERY51,DRAW_WORLD51,DRAW_ACTORS51,DRAW_EFFECTS51,DRAW_MARKERS51,DRAW_STAGES51};
typedef struct {uint64_t drawCurrent[DRAW_STAGES51],drawSum[DRAW_STAGES51];unsigned drawTenths[DRAW_STAGES51];uint64_t current[FRAME_STAGES50B],sum[FRAME_STAGES50B],audio;unsigned frames,audioPrevious,ready,tenths[FRAME_STAGES50B+1];} FrameProfile50b;
static void frame_span50b(FrameProfile50b*p,int stage,uint64_t now,uint64_t*at){p->current[stage]+=now-*at;*at=now;}
static void frame_draw_span51(FrameProfile50b*p,int stage,uint64_t now,uint64_t*at){p->drawCurrent[stage]+=now-*at;*at=now;}
static void frame_finish50b(FrameProfile50b*p,uint64_t frequency,unsigned audioTicks,int running){
 unsigned audio=audioTicks-p->audioPrevious;p->audioPrevious=audioTicks;
 if(!running){memset(p->drawCurrent,0,sizeof(p->drawCurrent));memset(p->drawSum,0,sizeof(p->drawSum));memset(p->current,0,sizeof(p->current));memset(p->sum,0,sizeof(p->sum));p->frames=0;p->audio=0;return;}
 p->audio+=audio;p->frames++;uint64_t total=0;
 for(int i=0;i<FRAME_STAGES50B;i++){p->sum[i]+=p->current[i];p->current[i]=0;total+=p->sum[i];}
 for(int i=0;i<DRAW_STAGES51;i++){p->drawSum[i]+=p->drawCurrent[i];p->drawCurrent[i]=0;}
 if(!frequency||total<frequency)return;
 uint64_t divisor=frequency*p->frames;
 for(int i=0;i<DRAW_STAGES51;i++)p->drawTenths[i]=(unsigned)(p->drawSum[i]*10000/divisor);
 memset(p->drawSum,0,sizeof(p->drawSum));
 for(int i=0;i<FRAME_STAGES50B;i++)p->tenths[i]=(unsigned)(p->sum[i]*10000/divisor);
 p->tenths[FRAME_STAGES50B]=(unsigned)(p->audio*10000/divisor);p->ready=1;
 memset(p->sum,0,sizeof(p->sum));p->audio=0;p->frames=0;
}
#endif
