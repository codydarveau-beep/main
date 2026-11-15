/* MIT. Bounded shared decoded poses; each draw consumes data before eviction. */
#ifndef MYRO_GUARDIAN_POSE_CACHE65_H
#define MYRO_GUARDIAN_POSE_CACHE65_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define GUARDIAN_CACHE_BYTES65 (1024u*1024u)
#define GUARDIAN_CACHE_SLOTS65 16u
typedef struct{unsigned bank,frame,bytes;uint64_t used;float*data;}GuardianCacheEntry65;
typedef struct{GuardianCacheEntry65 entries[GUARDIAN_CACHE_SLOTS65];unsigned bytes;uint64_t clock,hits,loads;}GuardianCache65;
static void guardian_cache_clear65(GuardianCache65*c){for(unsigned i=0;i<GUARDIAN_CACHE_SLOTS65;i++)free(c->entries[i].data);memset(c,0,sizeof(*c));}
static const float*guardian_cache_get65(GuardianCache65*c,unsigned bank,unsigned frame,unsigned bytes,float*(*read)(void*,unsigned,unsigned),void*context){if(!bytes||bytes>GUARDIAN_CACHE_BYTES65||!read)return NULL;int slot=-1;for(unsigned i=0;i<GUARDIAN_CACHE_SLOTS65;i++){GuardianCacheEntry65*e=c->entries+i;if(e->data&&e->bank==bank&&e->frame==frame&&e->bytes==bytes){e->used=++c->clock;c->hits++;return e->data;}if(slot<0||!e->data||(c->entries[slot].data&&e->used<c->entries[slot].used))slot=(int)i;}GuardianCacheEntry65*e=c->entries+slot;if(e->data){c->bytes-=e->bytes;free(e->data);memset(e,0,sizeof(*e));}while(c->bytes+bytes>GUARDIAN_CACHE_BYTES65){int old=-1;for(unsigned i=0;i<GUARDIAN_CACHE_SLOTS65;i++)if(c->entries[i].data&&(old<0||c->entries[i].used<c->entries[old].used))old=(int)i;if(old<0)return NULL;c->bytes-=c->entries[old].bytes;free(c->entries[old].data);memset(c->entries+old,0,sizeof(*e));}float*p=read(context,bank,frame);if(!p)return NULL;*e=(GuardianCacheEntry65){bank,frame,bytes,++c->clock,p};c->bytes+=bytes;c->loads++;return p;}
#endif
