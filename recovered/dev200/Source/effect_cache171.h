/* MIT. Bounded field/target-ring GPU variants; retire only after queued draws finish. */
#ifndef MYRO_EFFECT_CACHE171_H
#define MYRO_EFFECT_CACHE171_H
#define EFFECT_CACHE_BYTES171 (1024u*1024u)
#define EFFECT_CACHE_SLOTS171 128u
typedef struct{void**slot;unsigned bytes,raw;uint64_t used;unsigned touched183;}EffectCache171;
static EffectCache171 effectCache171[EFFECT_CACHE_SLOTS171];static unsigned effectCacheBytes171;static uint64_t effectCacheClock171;static unsigned effectCacheTime183;
static void effect_cache_evict171(unsigned i){EffectCache171*e=effectCache171+i;if(!e->slot)return;while(pb_busy()){}if(*e->slot){MmFreeContiguousMemory(*e->slot);*e->slot=NULL;}effectCacheBytes171-=e->bytes;memset(e,0,sizeof(*e));}
/* True means fresh storage; caller fills the exact original pixels before binding. */
static int effect_cache_prepare171(void**slot,unsigned bytes){if(!slot||!bytes||bytes>EFFECT_CACHE_BYTES171)fail("Effect cache bounds invalid");unsigned allocation=(bytes+4095u)&~4095u;int empty=-1;for(unsigned i=0;i<EFFECT_CACHE_SLOTS171;i++){EffectCache171*e=effectCache171+i;if(e->slot==slot){if(e->raw!=bytes){effect_cache_evict171(i);empty=(int)i;break;}e->used=++effectCacheClock171;e->touched183=effectCacheTime183;return 0;}if(!e->slot&&empty<0)empty=(int)i;}
 while(empty<0||effectCacheBytes171+allocation>EFFECT_CACHE_BYTES171){int victim=-1;for(unsigned i=0;i<EFFECT_CACHE_SLOTS171;i++)if(effectCache171[i].slot&&(victim<0||effectCache171[i].used<effectCache171[victim].used))victim=(int)i;if(victim<0)fail("Effect cache capacity invalid");effect_cache_evict171((unsigned)victim);if(empty<0)empty=victim;}
 if(*slot)fail("Unregistered effect texture");*slot=gpu_alloc(allocation);effectCache171[empty]=(EffectCache171){slot,allocation,bytes,++effectCacheClock171,effectCacheTime183};effectCacheBytes171+=allocation;return 1;}
static void effect_cache_frame183(unsigned now){effectCacheTime183=now;for(unsigned i=0;i<EFFECT_CACHE_SLOTS171;i++)if(effectCache171[i].slot&&(unsigned)(now-effectCache171[i].touched183)>=3000)effect_cache_evict171(i);}
static void effect_cache_clear171(void){for(unsigned i=0;i<EFFECT_CACHE_SLOTS171;i++)effect_cache_evict171(i);effectCacheClock171=0;}
#endif
