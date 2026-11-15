/* MIT. Bounded script/art reads; no all-world NPC art allocation. */
#ifndef MYRO_NPC_DISC55_H
#define MYRO_NPC_DISC55_H
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <zlib.h>
#include "npc_program55.h"
#include "npc_registry_data55.h"
#include "npc_art_data55.h"
#define NPC_ART_CACHE_SLOTS55 64u
#define NPC_ART_CACHE_BYTES55 (512u*1024u)
typedef int(*NpcDiscRead55)(void*,unsigned,uint32_t,unsigned char*,uint32_t);
typedef struct{uint32_t frame,bytes;unsigned char*data;uint64_t used;unsigned touched183;}NpcArtEntry55;
typedef struct{NpcDiscRead55 read;void*context;NpcArtEntry55 art[NPC_ART_CACHE_SLOTS55];uint32_t artBytes;uint64_t clock;unsigned time183;}NpcDisc55;
static int npc_disc_program55(void*context,uint32_t id,unsigned char**out,uint32_t*length){NpcDisc55*d=context;if(!d||!d->read||!id||id>NPC_PROGRAM_COUNT55||!out||!length)return 0;uint32_t at=npcProgramFiles55[id-1].offset,n=npcProgramFiles55[id-1].bytes;if(n<NPC_PROGRAM_HEADER55||at>NPC_SCRIPT_FILE_BYTES55||n>NPC_SCRIPT_FILE_BYTES55-at)return 0;unsigned char*p=malloc(n);if(!p)return 0;if(!d->read(d->context,0,at,p,n)||npc_program_u3255(p+36)!=npcProgramFiles55[id-1].owner){free(p);return 0;}*out=p;*length=n;return 1;}
static void npc_disc_evict55(NpcDisc55*d,unsigned slot){NpcArtEntry55*e=d->art+slot;if(e->data){d->artBytes-=e->bytes;free(e->data);}memset(e,0,sizeof(*e));}
static const unsigned char*npc_disc_art55(NpcDisc55*d,unsigned frame){if(!d||!d->read||frame>=NPC_FRAME_COUNT55||d->clock==UINT64_MAX)return NULL;unsigned slot=0;for(unsigned i=0;i<NPC_ART_CACHE_SLOTS55;i++){NpcArtEntry55*e=d->art+i;if(e->data&&e->frame==frame){e->used=++d->clock;e->touched183=d->time183;return e->data;}if(!e->data||(d->art[slot].data&&e->used<d->art[slot].used))slot=i;}
 const NpcArtFrame55*f=npcFrames55+frame;if(!f->packed||f->packed>NPC_ART_CACHE_BYTES55||f->offset>NPC_FILE_BYTES55||f->packed>NPC_FILE_BYTES55-f->offset||!f->raw||f->raw>70000)return NULL;unsigned char*p=malloc(f->packed);if(!p)return NULL;if(!d->read(d->context,1,f->offset,p,f->packed)||crc32(0,p,f->packed)!=f->crc){free(p);return NULL;}
 npc_disc_evict55(d,slot);while(d->artBytes>NPC_ART_CACHE_BYTES55-f->packed){unsigned oldest=NPC_ART_CACHE_SLOTS55;for(unsigned i=0;i<NPC_ART_CACHE_SLOTS55;i++)if(d->art[i].data&&(oldest==NPC_ART_CACHE_SLOTS55||d->art[i].used<d->art[oldest].used))oldest=i;if(oldest==NPC_ART_CACHE_SLOTS55){free(p);return NULL;}npc_disc_evict55(d,oldest);}
 d->art[slot]=(NpcArtEntry55){frame,f->packed,p,++d->clock,d->time183};d->artBytes+=f->packed;return p;
}
static void npc_disc_frame183(NpcDisc55*d,unsigned now){d->time183=now;for(unsigned i=0;i<NPC_ART_CACHE_SLOTS55;i++)if(d->art[i].data&&(unsigned)(now-d->art[i].touched183)>=15000)npc_disc_evict55(d,i);}
static void npc_disc_clear55(NpcDisc55*d){for(unsigned i=0;i<NPC_ART_CACHE_SLOTS55;i++)npc_disc_evict55(d,i);d->clock=0;}
static unsigned npc_disc_pose55(unsigned model,unsigned direction,uint64_t milliseconds){if(model>=NPC_MODEL_COUNT55||direction>=8)return UINT32_MAX;const NpcModel55*m=npcModels55+model;unsigned count=m->count[direction],delay=m->delay[direction];if(!count||!delay)return UINT32_MAX;unsigned at=m->start[direction]+(unsigned)((milliseconds/delay)%count);if(at>=sizeof(npcSequence55)/sizeof(*npcSequence55))return UINT32_MAX;return npcSequence55[at];}
#endif
