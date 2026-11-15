/* MIT. Bounded, on-demand script cache; live VM call frames pin their programs. */
#ifndef MYRO_NPC_PROGRAM_CACHE55_H
#define MYRO_NPC_PROGRAM_CACHE55_H
#include "npc_program55.h"
#define NPC_PROGRAM_CACHE55 40u
#define NPC_PROGRAM_CACHE_BYTES55 (2u*1024u*1024u)
typedef int(*NpcProgramRead55)(void*,uint32_t,unsigned char**,uint32_t*);
typedef struct{uint32_t id,bytes;uint64_t used;NpcLoadedProgram55 loaded;}NpcProgramCacheEntry55;
typedef struct{NpcProgramCacheEntry55 entries[NPC_PROGRAM_CACHE55];uint32_t bytes;uint64_t clock;NpcProgramRead55 read;void*context;uint32_t limit;int(*otherPinned)(void*,const NpcProgram55*);void*pinContext;}NpcProgramCache55;
static int npc_program_pinned55(const NpcMachine55*m,const NpcProgram55*p){if(!m||m->status==N55_DONE||m->status==N55_ERROR)return 0;if(m->program==p)return 1;for(uint32_t i=0;i<m->depth;i++)if(m->frames[i].program==p)return 1;return 0;}
static int npc_program_cache_pinned55(const NpcProgramCache55*c,const NpcMachine55*m,const NpcProgram55*p){return npc_program_pinned55(m,p)||(c->otherPinned&&c->otherPinned(c->pinContext,p));}
/* Only idle programs may be reclaimed; cross-map scripts/call frames remain pinned. */
static unsigned npc_program_trim171(NpcProgramCache55*c,const NpcMachine55*m,unsigned target){unsigned freed=0;while(c->bytes>target){int slot=-1;for(unsigned i=0;i<NPC_PROGRAM_CACHE55;i++)if(c->entries[i].loaded.allocation&&!npc_program_cache_pinned55(c,m,&c->entries[i].loaded.program)&&(slot<0||c->entries[i].used<c->entries[slot].used))slot=(int)i;if(slot<0)break;NpcProgramCacheEntry55*e=c->entries+slot;freed+=e->bytes;c->bytes-=e->bytes;npc_program_free55(&e->loaded);memset(e,0,sizeof(*e));}return freed;}
static const NpcProgram55*npc_program_cached55(NpcProgramCache55*c,const NpcMachine55*m,uint32_t id){
 if(!c||!id||!c->read||c->clock==UINT64_MAX)return NULL;int slot=-1;for(unsigned i=0;i<NPC_PROGRAM_CACHE55;i++){NpcProgramCacheEntry55*e=c->entries+i;if(e->id==id&&e->loaded.allocation){e->used=++c->clock;return&e->loaded.program;}if(!npc_program_cache_pinned55(c,m,&e->loaded.program)&&(slot<0||!e->loaded.allocation||(c->entries[slot].loaded.allocation&&e->used<c->entries[slot].used)))slot=(int)i;}
 if(slot<0)return NULL;unsigned char*bytes=NULL;uint32_t length=0;if(!c->read(c->context,id,&bytes,&length)){free(bytes);return NULL;}NpcLoadedProgram55 trial={0};uint32_t limit=c->limit?c->limit:NPC_PROGRAM_CACHE_BYTES55;int valid=length<=limit&&npc_program_take180(&trial,&bytes,length);free(bytes);if(!valid)return NULL;
 /* Additional unpinned entries can be evicted to honor the memory budget. */
 uint32_t remove=c->entries[slot].bytes;for(unsigned i=0;c->bytes-remove+length>limit&&i<NPC_PROGRAM_CACHE55;i++){NpcProgramCacheEntry55*e=c->entries+i;if((int)i==slot||!e->loaded.allocation||npc_program_cache_pinned55(c,m,&e->loaded.program))continue;c->bytes-=e->bytes;npc_program_free55(&e->loaded);memset(e,0,sizeof(*e));}
 if(c->bytes-remove+length>limit){npc_program_free55(&trial);return NULL;}NpcProgramCacheEntry55*e=c->entries+slot;c->bytes-=e->bytes;npc_program_free55(&e->loaded);e->loaded=trial;e->id=id;e->bytes=length;e->used=++c->clock;c->bytes+=length;return&e->loaded.program;
}
static void npc_program_cache_clear55(NpcProgramCache55*c){for(unsigned i=0;i<NPC_PROGRAM_CACHE55;i++)npc_program_free55(&c->entries[i].loaded);memset(c,0,sizeof(*c));}
#endif
