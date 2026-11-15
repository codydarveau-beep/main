/* MIT. Sparse, typed NPC/quest variables. No raw pointers are serialized. */
#ifndef MYRO_NPC_STATE55_H
#define MYRO_NPC_STATE55_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <zlib.h>
#ifndef NPC_STATE_ALLOC55
#define NPC_STATE_ALLOC55 malloc
#define NPC_STATE_FREE55 free
#endif
#define NPC_STATE_ENTRIES55 16384u
#define NPC_STATE_TEXT55 131072u
#define NPC_STATE_STRING55 4095u
#define NPC_STATE_INDEX55 32768u
#define NPC_STATE_FILE55 (32u+NPC_STATE_ENTRIES55*32u+NPC_STATE_TEXT55)
typedef struct{uint64_t key;uint32_t index,kind;int64_t number;char*text;uint32_t length;}NpcVariable55;
typedef struct{NpcVariable55*entries;uint32_t count,capacity,textBytes,revision;}NpcState55;
enum{NPC_STATE_NUMBER55=1,NPC_STATE_STRING_KIND55=2};
static uint32_t npc_state_u32_55(const unsigned char*p){return(uint32_t)p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;}
static uint64_t npc_state_u64_55(const unsigned char*p){return(uint64_t)npc_state_u32_55(p)|(uint64_t)npc_state_u32_55(p+4)<<32;}
static void npc_state_put32_55(unsigned char*p,uint32_t n){for(unsigned i=0;i<4;i++)p[i]=(unsigned char)(n>>(i*8));}
static void npc_state_put64_55(unsigned char*p,uint64_t n){npc_state_put32_55(p,(uint32_t)n);npc_state_put32_55(p+4,(uint32_t)(n>>32));}
static int npc_state_compare55(const NpcVariable55*v,uint64_t key,uint32_t index){return v->key<key?-1:v->key>key?1:v->index<index?-1:v->index>index?1:0;}
static uint32_t npc_state_find55(const NpcState55*s,uint64_t key,uint32_t index,int*found){uint32_t lo=0,hi=s->count;while(lo<hi){uint32_t mid=lo+(hi-lo)/2;if(npc_state_compare55(s->entries+mid,key,index)<0)lo=mid+1;else hi=mid;}*found=lo<s->count&&!npc_state_compare55(s->entries+lo,key,index);return lo;}
static const NpcVariable55*npc_state_get55(const NpcState55*s,uint64_t key,uint32_t index){if(!key||index>=NPC_STATE_INDEX55)return NULL;int found;uint32_t at=npc_state_find55(s,key,index,&found);return found?s->entries+at:NULL;}
static int64_t npc_state_number55(const NpcState55*s,uint64_t key,uint32_t index){const NpcVariable55*v=npc_state_get55(s,key,index);return v&&v->kind==NPC_STATE_NUMBER55?v->number:0;}
static const char*npc_state_text55(const NpcState55*s,uint64_t key,uint32_t index){const NpcVariable55*v=npc_state_get55(s,key,index);return v&&v->kind==NPC_STATE_STRING_KIND55?v->text:"";}
static void npc_state_clear55(NpcState55*s){for(uint32_t i=0;i<s->count;i++)NPC_STATE_FREE55(s->entries[i].text);NPC_STATE_FREE55(s->entries);memset(s,0,sizeof(*s));}
static int npc_state_reserve55(NpcState55*s,uint32_t wanted){if(wanted<=s->capacity)return 1;if(wanted>NPC_STATE_ENTRIES55)return 0;uint32_t n=s->capacity?s->capacity*2:32;while(n<wanted)n*=2;if(n>NPC_STATE_ENTRIES55)n=NPC_STATE_ENTRIES55;NpcVariable55*p=NPC_STATE_ALLOC55((size_t)n*sizeof(*p));if(!p)return 0;if(s->count)memcpy(p,s->entries,(size_t)s->count*sizeof(*p));NPC_STATE_FREE55(s->entries);s->entries=p;s->capacity=n;return 1;}
static int npc_state_set55(NpcState55*s,uint64_t key,uint32_t index,uint32_t kind,int64_t number,const char*text,uint32_t length){
 if(!key||index>=NPC_STATE_INDEX55||(kind!=NPC_STATE_NUMBER55&&kind!=NPC_STATE_STRING_KIND55)||length>NPC_STATE_STRING55||(kind==NPC_STATE_STRING_KIND55&&(!text||memchr(text,0,length)))||(kind==NPC_STATE_NUMBER55&&length))return 0;
 int found;uint32_t at=npc_state_find55(s,key,index,&found);NpcVariable55*old=found?s->entries+at:NULL;
 if(kind==NPC_STATE_NUMBER55?!number:!length){if(!found)return 1;s->textBytes-=old->length;NPC_STATE_FREE55(old->text);memmove(old,old+1,(s->count-at-1)*sizeof(*old));s->count--;s->revision++;return 1;}
 if(old&&old->kind==kind&&(kind==NPC_STATE_NUMBER55?old->number==number:old->length==length&&!memcmp(old->text,text,length)))return 1;
 uint32_t total=s->textBytes-(old?old->length:0)+length;if(total>NPC_STATE_TEXT55)return 0;
 char*copy=NULL;if(kind==NPC_STATE_STRING_KIND55){copy=NPC_STATE_ALLOC55(length+1);if(!copy)return 0;memcpy(copy,text,length);copy[length]=0;}
 if(!found&&!npc_state_reserve55(s,s->count+1)){NPC_STATE_FREE55(copy);return 0;}
 if(found)NPC_STATE_FREE55(s->entries[at].text);else{memmove(s->entries+at+1,s->entries+at,(s->count-at)*sizeof(*s->entries));s->count++;}
 s->entries[at]=(NpcVariable55){key,index,kind,number,copy,length};s->textBytes=total;s->revision++;return 1;
}
static int npc_state_set_number55(NpcState55*s,uint64_t key,uint32_t index,int64_t value){return npc_state_set55(s,key,index,NPC_STATE_NUMBER55,value,NULL,0);}
static int npc_state_set_text55(NpcState55*s,uint64_t key,uint32_t index,const char*value,uint32_t length){return npc_state_set55(s,key,index,NPC_STATE_STRING_KIND55,0,value,length);}
static uint32_t npc_state_wire_bytes55(const NpcState55*s){return 32+s->count*32+s->textBytes;}
static int npc_state_encode55(const NpcState55*s,unsigned char*out,uint32_t capacity){uint32_t bytes=npc_state_wire_bytes55(s);if(s->count>NPC_STATE_ENTRIES55||s->textBytes>NPC_STATE_TEXT55||capacity<bytes)return 0;memset(out,0,28);memcpy(out,"MYRONQ55",8);npc_state_put32_55(out+8,1);npc_state_put32_55(out+12,bytes);npc_state_put32_55(out+16,s->count);npc_state_put32_55(out+20,s->textBytes);uint32_t at=28;
 for(uint32_t i=0;i<s->count;i++){const NpcVariable55*v=s->entries+i;npc_state_put64_55(out+at,v->key);npc_state_put32_55(out+at+8,v->index);npc_state_put32_55(out+at+12,v->kind);npc_state_put64_55(out+at+16,(uint64_t)v->number);npc_state_put32_55(out+at+24,v->length);npc_state_put32_55(out+at+28,0);at+=32;if(v->length){memcpy(out+at,v->text,v->length);at+=v->length;}}
 npc_state_put32_55(out+at,crc32(0,out,at));return 1;}
/* Validate into a temporary store; failure leaves the live state untouched. */
static int npc_state_decode55(NpcState55*s,const unsigned char*data,uint32_t bytes){
 if(bytes<32||bytes>NPC_STATE_FILE55||memcmp(data,"MYRONQ55",8)||npc_state_u32_55(data+8)!=1||npc_state_u32_55(data+12)!=bytes||npc_state_u32_55(data+24)||crc32(0,data,bytes-4)!=npc_state_u32_55(data+bytes-4))return 0;
 uint32_t count=npc_state_u32_55(data+16),textBytes=npc_state_u32_55(data+20);if(count>NPC_STATE_ENTRIES55||textBytes>NPC_STATE_TEXT55||32+count*32+textBytes!=bytes)return 0;NpcState55 trial={0};if(!npc_state_reserve55(&trial,count))return 0;uint32_t at=28;
 for(uint32_t i=0;i<count;i++){if(at>bytes-4||bytes-4-at<32)goto bad;NpcVariable55 v={0};v.key=npc_state_u64_55(data+at);v.index=npc_state_u32_55(data+at+8);v.kind=npc_state_u32_55(data+at+12);uint64_t bits=npc_state_u64_55(data+at+16);v.number=bits<=INT64_MAX?(int64_t)bits:INT64_MIN+(int64_t)(bits-(UINT64_C(1)<<63));v.length=npc_state_u32_55(data+at+24);
  if(!v.key||v.index>=NPC_STATE_INDEX55||npc_state_u32_55(data+at+28)||(i&&npc_state_compare55(trial.entries+i-1,v.key,v.index)>=0))goto bad;at+=32;
  if(v.kind==NPC_STATE_NUMBER55){if(v.length||!v.number)goto bad;}else if(v.kind==NPC_STATE_STRING_KIND55){if(v.number||!v.length||v.length>NPC_STATE_STRING55||v.length>bytes-4-at||memchr(data+at,0,v.length))goto bad;v.text=NPC_STATE_ALLOC55(v.length+1);if(!v.text)goto bad;memcpy(v.text,data+at,v.length);v.text[v.length]=0;at+=v.length;}else goto bad;
  trial.entries[trial.count++]=v;trial.textBytes+=v.length;
 }
 if(at!=bytes-4||trial.textBytes!=textBytes)goto bad;trial.revision=s->revision+1;npc_state_clear55(s);*s=trial;return 1;
bad:npc_state_clear55(&trial);return 0;
}
#endif
