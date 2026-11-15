/* Sparse, explicitly little-endian owned-item section for the next save format.
 * This is not yet the active character-save adapter. Save50 remains untouched. */
#ifndef MYRO_OWNED_CODEC52_H
#define MYRO_OWNED_CODEC52_H
#include <stdlib.h>
#include <zlib.h>
#include "owned_items52.h"
#define OWNED_WIRE_HEADER52 64u
#define OWNED_WIRE_RECORD52 36u
#define OWNED_WIRE_MAX52 (OWNED_WIRE_HEADER52+OWNED_MAX52*OWNED_WIRE_RECORD52+4u)
static uint32_t owned_get32_52(const unsigned char*p){return(uint32_t)p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;}
static void owned_put32_52(unsigned char*p,uint32_t x){p[0]=(unsigned char)x;p[1]=(unsigned char)(x>>8);p[2]=(unsigned char)(x>>16);p[3]=(unsigned char)(x>>24);}
static unsigned owned_wire_bytes52(const OwnedItems52*b){return OWNED_WIRE_HEADER52+((unsigned)b->count[0]+b->count[1]+b->count[2])*OWNED_WIRE_RECORD52+4;}
/* Invalid input never changes the output. Caller supplies a bounded buffer. */
static unsigned owned_encode52(unsigned char*out,unsigned capacity,const OwnedItems52*b,OwnedLookup52 lookup){
 if(!out||!owned_valid52(b,lookup))return 0;unsigned size=owned_wire_bytes52(b);if(size>capacity||size>OWNED_WIRE_MAX52)return 0;
 memset(out,0,size);memcpy(out,"MYROIV52",8);owned_put32_52(out+8,52);owned_put32_52(out+12,size);owned_put32_52(out+16,b->nextUID);
 for(unsigned box=0;box<3;box++)owned_put32_52(out+20+box*4,b->count[box]);unsigned at=OWNED_WIRE_HEADER52;
 for(unsigned box=0;box<3;box++)for(unsigned i=0;i<b->count[box];i++){
  const OwnedItem52*p=b->items+owned_base52(box)+i;owned_put32_52(out+at,p->uid);owned_put32_52(out+at+4,p->sourceID);owned_put32_52(out+at+8,p->quantity);for(unsigned k=0;k<4;k++)owned_put32_52(out+at+12+k*4,p->cards[k]);owned_put32_52(out+at+28,p->equipped);out[at+32]=p->refine;out[at+33]=p->identified;out[at+34]=p->bound;out[at+35]=p->flags;at+=OWNED_WIRE_RECORD52;
 }
 owned_put32_52(out+size-4,(uint32_t)crc32(0,out,size-4));return size;
}
/* 1 valid,0 corrupt,-1 unknown version,-2 allocation failure. Output is atomic. */
static int owned_decode52(OwnedItems52*out,const unsigned char*raw,unsigned size,OwnedLookup52 lookup){
 if(!out||!raw||!lookup||size<OWNED_WIRE_HEADER52+4||size>OWNED_WIRE_MAX52)return 0;
 if(memcmp(raw,"MYROIV52",8)||owned_get32_52(raw+8)!=52)return -1;
 if(owned_get32_52(raw+12)!=size||(uint32_t)crc32(0,raw,size-4)!=owned_get32_52(raw+size-4))return 0;
 uint32_t count[3];unsigned total=0;for(unsigned box=0;box<3;box++){count[box]=owned_get32_52(raw+20+box*4);if(count[box]>owned_capacity52(box))return 0;total+=count[box];}
 if(size!=OWNED_WIRE_HEADER52+total*OWNED_WIRE_RECORD52+4)return 0;for(unsigned i=32;i<OWNED_WIRE_HEADER52;i++)if(raw[i])return 0;
 OwnedItems52*t=malloc(sizeof(*t));if(!t)return -2;owned_init52(t);t->nextUID=owned_get32_52(raw+16);for(unsigned box=0;box<3;box++)t->count[box]=(uint16_t)count[box];unsigned at=OWNED_WIRE_HEADER52;
 for(unsigned box=0;box<3;box++)for(unsigned i=0;i<count[box];i++){
  OwnedItem52*p=t->items+owned_base52(box)+i;p->uid=owned_get32_52(raw+at);p->sourceID=owned_get32_52(raw+at+4);p->quantity=owned_get32_52(raw+at+8);for(unsigned k=0;k<4;k++)p->cards[k]=owned_get32_52(raw+at+12+k*4);p->equipped=owned_get32_52(raw+at+28);p->refine=raw[at+32];p->identified=raw[at+33];p->bound=raw[at+34];p->flags=raw[at+35];at+=OWNED_WIRE_RECORD52;
 }
 int valid=owned_valid52(t,lookup);if(valid)memcpy(out,t,sizeof(*t));free(t);return valid;
}
#endif
