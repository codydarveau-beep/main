/* MIT. Real save controller: recovery bypasses unsafe saved-map preparation. */
#include <assert.h>
#include "combat.h"
#include "developer.h"
#include "save_store.h"
typedef struct {unsigned char disk[SAVE_BYTES];unsigned requested,prepares,writes;} Recovery44;
static int read44(void*c,int slot,unsigned char*b){if(slot)return SLOT_MISSING;memcpy(b,((Recovery44*)c)->disk,SAVE_BYTES);return SLOT_RAW;}
static int write44(void*c,int slot,const unsigned char*b){(void)slot;(void)b;((Recovery44*)c)->writes++;return 0;}
static int prepare44(void*c,unsigned map,float*x,float*y){Recovery44*r=c;r->requested=map;r->prepares++;*x=1500;*y=1500;return map==0;}
static int walk44(void*c,float x,float y,float nx,float ny){(void)c;(void)x;(void)y;return nx>0&&ny>0;}
int main(void){Combat g,h;combat_init(&g,1500,1500,walk44,NULL);dev_class_preset(&g,7);g.mapId=17;g.x=100;g.y=100;SavedCharacter character;save_capture(&character,&g,5);assert(save_valid(&character));Recovery44 r={0};save_encode(r.disk,&character);unsigned char before[SAVE_BYTES];memcpy(before,r.disk,SAVE_BYTES);SaveStore s={.ctx=&r,.read=read44,.write=write44,.prepare=prepare44};assert(!save_load(&s,&h,1500,1500,walk44,NULL));assert(r.requested==17&&r.prepares==1&&!r.writes);s.recoverToCamp=1;assert(save_load(&s,&h,1500,1500,walk44,NULL));assert(r.requested==0&&r.prepares==2&&!r.writes);assert(h.jobId==7&&h.level==99&&h.mapId==0&&h.x==1500&&h.y==1500);assert(h.hp==g.hp&&h.zeny==g.zeny&&!memcmp(h.ranks,g.ranks,sizeof(h.ranks)));assert(!memcmp(before,r.disk,SAVE_BYTES));puts("PASS44 recovery prepares only safe camp, preserves character and original disk slots; unavailable map rejected.");}
