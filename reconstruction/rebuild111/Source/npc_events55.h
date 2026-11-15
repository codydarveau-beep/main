/* MIT. Bounded event deadlines; no per-frame scan of every NPC. */
#ifndef MYRO_NPC_EVENTS55_H
#define MYRO_NPC_EVENTS55_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define NPC_EVENTS_LIMIT55 2048u
typedef struct{uint64_t at,order,owner;uint32_t program,label,kind,unitLife172;}NpcEvent55;
typedef struct{NpcEvent55*heap;uint32_t count,capacity;uint64_t nextOrder;}NpcEvents55;
static int npc_event_before55(const NpcEvent55*a,const NpcEvent55*b){return a->at<b->at||(a->at==b->at&&a->order<b->order);}
static void npc_event_down55(NpcEvents55*q,uint32_t i){NpcEvent55 value=q->heap[i];for(;;){uint32_t child=i*2+1;if(child>=q->count)break;if(child+1<q->count&&npc_event_before55(q->heap+child+1,q->heap+child))child++;if(!npc_event_before55(q->heap+child,&value))break;q->heap[i]=q->heap[child];i=child;}q->heap[i]=value;}
static int npc_event_schedule55(NpcEvents55*q,uint64_t now,uint64_t delay,uint64_t owner,uint32_t program,uint32_t label,uint32_t kind){
 if(!q||!owner||!program||q->count>=NPC_EVENTS_LIMIT55||q->nextOrder==UINT64_MAX)return 0;
 if(q->count==q->capacity){uint32_t n=q->capacity?q->capacity*2:16;if(n>NPC_EVENTS_LIMIT55)n=NPC_EVENTS_LIMIT55;NpcEvent55*p=malloc((size_t)n*sizeof(*p));if(!p)return 0;if(q->count)memcpy(p,q->heap,q->count*sizeof(*p));free(q->heap);q->heap=p;q->capacity=n;}
 NpcEvent55 value={now>UINT64_MAX-delay?UINT64_MAX:now+delay,++q->nextOrder,owner,program,label,kind};uint32_t at=q->count++;while(at){uint32_t parent=(at-1)/2;if(!npc_event_before55(&value,q->heap+parent))break;q->heap[at]=q->heap[parent];at=parent;}q->heap[at]=value;return 1;
}
/* Remove matches before rebuilding; cancellation never invokes user code. */
static uint32_t npc_event_cancel55(NpcEvents55*q,uint64_t owner,uint32_t program,uint32_t label,int anyLabel){uint32_t kept=0,removed=0;for(uint32_t i=0;i<q->count;i++){NpcEvent55 e=q->heap[i];if(e.owner==owner&&e.program==program&&(anyLabel||e.label==label))removed++;else q->heap[kept++]=e;}q->count=kept;for(uint32_t i=q->count/2;i;i--)npc_event_down55(q,i-1);return removed;}
static int npc_event_due55(NpcEvents55*q,uint64_t now,NpcEvent55*out){if(!q||!out||!q->count||q->heap[0].at>now)return 0;*out=q->heap[0];q->count--;if(q->count){q->heap[0]=q->heap[q->count];npc_event_down55(q,0);}return 1;}
/* Pop before callback, allowing scripts to cancel or enqueue events safely. */
static uint32_t npc_events_dispatch55(NpcEvents55*q,uint64_t now,uint32_t budget,void(*run)(void*,const NpcEvent55*),void*context){uint32_t done=0;NpcEvent55 event;if(!run)return 0;while(done<budget&&npc_event_due55(q,now,&event)){run(context,&event);done++;}return done;}
static void npc_events_clear55(NpcEvents55*q){free(q->heap);memset(q,0,sizeof(*q));}
#endif
