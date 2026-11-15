/* Fixed-capacity owned instances, independent of the size of the item catalog.
 * All operations preflight before mutation. No heap allocation or float IDs. */
#ifndef MYRO_OWNED_ITEMS52_H
#define MYRO_OWNED_ITEMS52_H
#include <stdint.h>
#include <string.h>
#include <limits.h>
#define OWNED_BAG52 100
#define OWNED_CART52 100
#define OWNED_STORAGE52 600
#define OWNED_MAX52 800
#define OWNED_STACK52 30000u
#define OWNED_LEGACY_STACK52 1u
#define OWNED_RESERVED_CARDS52 2u
#define OWNED_BROKEN52 4u
#define OWNED_FLAG_MASK52 7u
#define OWNED_NO_CART52 1u
#define OWNED_NO_STORAGE52 2u
#define OWNED_TWO_HAND52 4u
#define OWNED_PET_EGG52 8u
enum {OWNED_MISC52,OWNED_WEAPON52,OWNED_ARMOR52,OWNED_CARD52};
typedef struct {uint32_t sourceID,location,weight,stackLimit;uint8_t kind,slots,refineable,flags;} OwnedRule52;
typedef const OwnedRule52*(*OwnedLookup52)(uint32_t);
typedef struct {uint32_t uid,sourceID,quantity,cards[4],equipped;uint8_t refine,identified,bound,flags;} OwnedItem52;
typedef char OwnedItemSize52[(sizeof(OwnedItem52)==36)?1:-1];
typedef struct {OwnedItem52 items[OWNED_MAX52];uint16_t count[3];uint32_t nextUID;} OwnedItems52;
enum {OWNED_OK52,OWNED_BAD_ITEM52,OWNED_FULL52,OWNED_BAD_QUANTITY52,OWNED_EQUIPPED52,OWNED_UNIDENTIFIED52,OWNED_WRONG_CARD52,OWNED_NO_SOCKET52,OWNED_UID_LIMIT52,OWNED_RESERVED52,OWNED_RESTRICTED52};
static unsigned owned_base52(unsigned box){return box==0?0:box==1?OWNED_BAG52:OWNED_BAG52+OWNED_CART52;}
static unsigned owned_capacity52(unsigned box){return box==2?OWNED_STORAGE52:OWNED_BAG52;}
static OwnedItem52*owned_find52(OwnedItems52*b,unsigned box,uint32_t uid){if(!b||box>=3||!uid)return 0;unsigned at=owned_base52(box);for(unsigned i=0;i<b->count[box];i++)if(b->items[at+i].uid==uid)return b->items+at+i;return 0;}
static int owned_gear52(const OwnedRule52*r){return r&&(r->kind==OWNED_WEAPON52||r->kind==OWNED_ARMOR52);}
static void owned_init52(OwnedItems52*b){memset(b,0,sizeof(*b));b->nextUID=1;}
static void owned_erase52(OwnedItems52*b,unsigned box,OwnedItem52*p){unsigned base=owned_base52(box),i=(unsigned)(p-b->items)-base;memmove(p,p+1,(b->count[box]-i-1)*sizeof(*p));memset(b->items+base+--b->count[box],0,sizeof(*p));}
static int owned_add52(OwnedItems52*b,unsigned box,uint32_t item,uint32_t quantity,OwnedLookup52 lookup){
 if(!b||box>=3||!lookup)return OWNED_BAD_ITEM52;const OwnedRule52*r=lookup(item);if(!r)return OWNED_BAD_ITEM52;if(!quantity)return OWNED_BAD_QUANTITY52;
 unsigned base=owned_base52(box),cap=owned_capacity52(box),count=b->count[box];if(count>cap)return OWNED_BAD_ITEM52;
 uint32_t stack=owned_gear52(r)?1:r->stackLimit;if(!stack||stack>OWNED_STACK52)return OWNED_BAD_ITEM52;
 uint64_t room=0;for(unsigned i=0;i<count;i++){OwnedItem52*p=b->items+base+i;if(!owned_gear52(r)&&p->sourceID==item&&p->identified&&!p->bound&&!(p->flags&~OWNED_LEGACY_STACK52)&&p->quantity<stack)room+=stack-p->quantity;}
 uint64_t rest=quantity>room?quantity-room:0,needed=(rest+stack-1)/stack;if(needed>cap-count)return OWNED_FULL52;if(!b->nextUID||needed>UINT32_MAX-b->nextUID)return OWNED_UID_LIMIT52;
 for(unsigned i=0;i<count&&quantity;i++){OwnedItem52*p=b->items+base+i;if(owned_gear52(r)||p->sourceID!=item||!p->identified||p->bound||(p->flags&~OWNED_LEGACY_STACK52)||p->quantity>=stack)continue;uint32_t n=stack-p->quantity;if(n>quantity)n=quantity;p->quantity+=n;p->flags&=(uint8_t)~OWNED_LEGACY_STACK52;quantity-=n;}
 while(quantity){uint32_t n=quantity<stack?quantity:stack;OwnedItem52*p=b->items+base+b->count[box]++;memset(p,0,sizeof(*p));p->uid=b->nextUID++;p->sourceID=item;p->quantity=n;p->identified=1;quantity-=n;}return OWNED_OK52;
}
static int owned_remove52(OwnedItems52*b,unsigned box,uint32_t uid,uint32_t quantity){OwnedItem52*p=owned_find52(b,box,uid);if(!p)return OWNED_BAD_ITEM52;if(!quantity||quantity>p->quantity)return OWNED_BAD_QUANTITY52;if(p->equipped)return OWNED_EQUIPPED52;p->quantity-=quantity;if(!p->quantity)owned_erase52(b,box,p);return OWNED_OK52;}
/* Equipment/card location values are the original EQP bits, not GUI slot indices. */
static int owned_insert_card52(OwnedItems52*b,uint32_t gearUID,uint32_t cardUID,OwnedLookup52 lookup,uint32_t*resultUID){
 if(!b||!lookup||gearUID==cardUID)return OWNED_BAD_ITEM52;OwnedItem52*gear=owned_find52(b,0,gearUID),*card=owned_find52(b,0,cardUID);if(!gear||!card)return OWNED_BAD_ITEM52;
 const OwnedRule52*g=lookup(gear->sourceID),*c=lookup(card->sourceID);if(!owned_gear52(g)||!c||c->kind!=OWNED_CARD52)return OWNED_BAD_ITEM52;
 if(!gear->identified)return OWNED_UNIDENTIFIED52;if(gear->equipped)return OWNED_EQUIPPED52;if(gear->flags&OWNED_RESERVED_CARDS52)return OWNED_RESERVED52;
 if(!(g->location&c->location)||(g->kind==OWNED_WEAPON52&&c->location==(1u<<5)))return OWNED_WRONG_CARD52;
 if(!g->slots||g->slots>4)return OWNED_NO_SOCKET52;unsigned slot=0;for(;slot<g->slots;slot++)if(!gear->cards[slot])break;if(slot==g->slots)return OWNED_NO_SOCKET52;
 if(!card->quantity||!gear->quantity)return OWNED_BAD_QUANTITY52;
 int split=gear->quantity>1;if(split){if(!(gear->flags&OWNED_LEGACY_STACK52))return OWNED_BAD_QUANTITY52;if(b->count[0]==OWNED_BAG52&&card->quantity>1)return OWNED_FULL52;if(!b->nextUID||b->nextUID==UINT32_MAX)return OWNED_UID_LIMIT52;}
 uint32_t source=card->sourceID;int consumed=owned_remove52(b,0,cardUID,1);if(consumed!=OWNED_OK52)return consumed;gear=owned_find52(b,0,gearUID);
 if(split){OwnedItem52 one=*gear;gear->quantity--;one.uid=b->nextUID++;one.quantity=1;one.flags&=(uint8_t)~OWNED_LEGACY_STACK52;one.cards[slot]=source;b->items[b->count[0]++]=one;if(resultUID)*resultUID=one.uid;}
 else{gear->cards[slot]=source;if(resultUID)*resultUID=gearUID;}return OWNED_OK52;
}
static int owned_transfer52(OwnedItems52*b,unsigned from,unsigned to,uint32_t uid,uint32_t quantity,OwnedLookup52 lookup){
 if(!b||!lookup||from>=3||to>=3||from==to)return OWNED_BAD_ITEM52;OwnedItem52*p=owned_find52(b,from,uid);if(!p)return OWNED_BAD_ITEM52;const OwnedRule52*r=lookup(p->sourceID);if(!r)return OWNED_BAD_ITEM52;
 if(!quantity||quantity>p->quantity)return OWNED_BAD_QUANTITY52;if(p->equipped)return OWNED_EQUIPPED52;if((to==1&&(r->flags&OWNED_NO_CART52))||(to==2&&(r->flags&OWNED_NO_STORAGE52)))return OWNED_RESTRICTED52;
 if(!owned_gear52(r)&&p->identified&&!p->bound&&!p->refine&&!p->flags){int result=owned_add52(b,to,p->sourceID,quantity,lookup);if(result!=OWNED_OK52)return result;return owned_remove52(b,from,uid,quantity);}
 if(b->count[to]>=owned_capacity52(to))return OWNED_FULL52;int split=quantity<p->quantity;if(split&&(!b->nextUID||b->nextUID==UINT32_MAX))return OWNED_UID_LIMIT52;
 OwnedItem52 copy=*p;copy.quantity=quantity;if(split){copy.uid=b->nextUID++;p->quantity-=quantity;}else owned_erase52(b,from,p);
 if(copy.quantity==1)copy.flags&=(uint8_t)~OWNED_LEGACY_STACK52;b->items[owned_base52(to)+b->count[to]++]=copy;return OWNED_OK52;
}
static int owned_valid52(const OwnedItems52*b,OwnedLookup52 lookup){
 if(!b||!lookup||!b->nextUID)return 0;
 for(unsigned box=0;box<3;box++){unsigned cap=owned_capacity52(box),base=owned_base52(box);if(b->count[box]>cap)return 0;
  for(unsigned i=0;i<b->count[box];i++){const OwnedItem52*p=b->items+base+i;const OwnedRule52*r=lookup(p->sourceID);if(!r||!p->uid||p->uid>=b->nextUID||!p->quantity||p->quantity>1000000000u||p->identified>1||p->refine>20||p->bound>4||(p->flags&~OWNED_FLAG_MASK52))return 0;
   if(box&&p->equipped)return 0;uint32_t positions=r->location;if(r->kind==OWNED_WEAPON52)positions|=32u;
   if(p->equipped&&(!owned_gear52(r)||!p->identified||p->quantity!=1||(p->equipped&~positions)))return 0;
   if(p->equipped&&r->kind==OWNED_WEAPON52&&((r->flags&OWNED_TWO_HAND52)?p->equipped!=34u:(p->equipped!=2u&&p->equipped!=32u)))return 0;
   if(p->equipped&&r->kind==OWNED_ARMOR52&&r->location==136u&&p->equipped!=8u&&p->equipped!=128u)return 0;
   if(p->refine&&!r->refineable)return 0;if(!owned_gear52(r)&&p->refine)return 0;
   if((p->flags&OWNED_BROKEN52)&&(!owned_gear52(r)||p->equipped))return 0;
   if(p->quantity>(owned_gear52(r)?1:r->stackLimit)&&!(p->flags&OWNED_LEGACY_STACK52))return 0;
   if(p->flags&OWNED_RESERVED_CARDS52){uint32_t tag=p->cards[0];if((tag!=255&&tag!=254&&tag!=256)||(tag==255&&!owned_gear52(r))||(tag==254&&r->kind==OWNED_CARD52)||(tag==256&&!(r->flags&OWNED_PET_EGG52)))return 0;for(unsigned k=1;k<4;k++)if(p->cards[k]>65535)return 0;}
   for(unsigned c=0;c<4;c++)if(p->cards[c]&&!(p->flags&OWNED_RESERVED_CARDS52)){const OwnedRule52*k=lookup(p->cards[c]);if(!owned_gear52(r)||!p->identified||p->quantity!=1||c>=r->slots||!k||k->kind!=OWNED_CARD52||!(r->location&k->location)||(r->kind==OWNED_WEAPON52&&k->location==(1u<<5)))return 0;}
   for(unsigned j=0;j<i;j++)if(b->items[base+j].uid==p->uid)return 0;
   for(unsigned earlier=0;earlier<box;earlier++){unsigned start=owned_base52(earlier);for(unsigned j=0;j<b->count[earlier];j++)if(b->items[start+j].uid==p->uid)return 0;}
   if(box==0&&p->equipped)for(unsigned j=0;j<i;j++)if(b->items[j].equipped&p->equipped)return 0;
  }
  for(unsigned i=b->count[box];i<cap;i++){const unsigned char*p=(const unsigned char*)(b->items+base+i);for(unsigned n=0;n<sizeof(OwnedItem52);n++)if(p[n])return 0;}
 }return 1;
}
#endif
