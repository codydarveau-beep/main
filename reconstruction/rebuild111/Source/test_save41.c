/* SPDX-License-Identifier: MIT
 * Exact save-controller tests with injectable disk faults. No Xbox runtime claim.
 */
#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include "save_store.h"
#include "developer.h"
typedef struct {unsigned char bytes[2][SAVE_BYTES];int size[2],io[2],failAt,lie,reads,writes;} Disk;
static int memread(void*ctx,int i,unsigned char*out){Disk*d=ctx;d->reads++;if(d->io[i])return SLOT_IO;if(d->size[i]<0)return SLOT_MISSING;if(d->size[i]!=SAVE_BYTES)return SLOT_BAD_SIZE;memcpy(out,d->bytes[i],SAVE_BYTES);return SLOT_RAW;}
static int memwrite(void*ctx,int i,const unsigned char*p){Disk*d=ctx;d->writes++;int n=d->failAt<0?SAVE_BYTES:d->failAt;memcpy(d->bytes[i],p,n);d->size[i]=n;if(d->lie&&n==SAVE_BYTES)d->bytes[i][70]^=1;return d->failAt<0;}
static void init(Disk*d,SaveStore*s){memset(d,0,sizeof(*d));d->size[0]=d->size[1]=-1;d->failAt=-1;memset(s,0,sizeof(*s));s->ctx=d;s->read=memread;s->write=memwrite;}
static int walk(void*w,float x,float y,float nx,float ny){(void)w;(void)x;(void)y;return nx>=8&&ny>=8&&nx<3192&&ny<3192;}
static int blocked(void*w,float x,float y,float nx,float ny){(void)w;(void)x;(void)y;(void)nx;(void)ny;return 0;}
static void character(Combat*g){combat_init(g,2100,1636,walk,NULL);g->level=4;g->statPoints=stat_budget(4);g->joblevel=2;g->maxhp=90;g->hp=73;g->maxsp=16;g->sp=9;g->exp=4;g->jexp=10;g->kills=17;g->jellopy=8;g->clover=5;g->apples=6;g->x=2120;g->y=1640;g->storageItems[ITEM_JELLOPY]=123;g->tooltipsDisabled=1;}
int main(void){
 Disk d;SaveStore s;Combat g,h;init(&d,&s);character(&g);combat_init(&h,2100,1636,walk,NULL);
 assert(!save_load(&s,&h,2100,1636,walk,NULL)&&!s.blocked&&s.newest==-1);assert(save_dirty(&s,&g));
 assert(save_commit(&s,&g)&&s.sequence==1&&s.newest==0&&!save_dirty(&s,&g));
 g.rng++;g.time+=10;g.mobs[0].hp=1;assert(!save_dirty(&s,&g)); /* transient world isn't a character change */
 g.apples++;assert(save_dirty(&s,&g));assert(save_commit(&s,&g)&&s.sequence==2&&s.newest==1);
 assert(save_load(&s,&h,2100,1636,walk,NULL));assert(h.level==4&&h.joblevel==2&&h.hp==73&&h.maxhp==90&&h.sp==9&&h.maxsp==16&&h.exp==4&&h.jexp==10&&h.kills==17&&h.apples==7&&h.jellopy==8&&h.clover==5&&h.x==2120&&h.y==1640&&h.rng==g.rng&&h.storageItems[ITEM_JELLOPY]==123&&h.tooltipsDisabled==1);
 assert(h.mobs[0].hp==50&&!h.autoAttack&&h.target==-1&&h.time==0); /* fresh encounter/timers */
 Disk golden=d;unsigned char protected[SAVE_BYTES];memcpy(protected,d.bytes[1],SAVE_BYTES);
 /* Every possible truncated write length preserves the newest confirmed copy. */
 for(int n=0;n<SAVE_BYTES;n++){
  d=golden;d.failAt=n;g.apples=8;assert(!save_commit(&s,&g));assert(!memcmp(d.bytes[1],protected,SAVE_BYTES));
  assert(save_load(&s,&h,2100,1636,walk,NULL)&&h.apples==7&&s.sequence==2);
 }
 d=golden;d.lie=1;assert(!save_commit(&s,&g));assert(!memcmp(d.bytes[1],protected,SAVE_BYTES));assert(save_load(&s,&h,2100,1636,walk,NULL)&&h.apples==7);
 /* Exhaustive single-bit corruption of the newest copy falls back to #1. */
 for(int bit=0;bit<SAVE_BYTES*8;bit++){
  d=golden;d.bytes[1][bit/8]^=1u<<(bit%8);
  assert(save_load(&s,&h,2100,1636,walk,NULL)&&s.sequence==1&&h.apples==6);
 }
 d=golden;d.bytes[1][70]^=1;assert(save_load(&s,&h,2100,1636,walk,NULL)&&s.bad&&!s.blocked);assert(save_commit(&s,&h)&&s.sequence==2); /* repair only expendable slot */
 d=golden;d.io[1]=1;int writes=d.writes;assert(!save_commit(&s,&g)&&s.blocked&&d.writes==writes); /* unknown newer file: never write */
 d=golden;save_put(d.bytes[1]+8,23);writes=d.writes;assert(!save_commit(&s,&g)&&s.blocked&&d.writes==writes); /* future version */
 d=golden;memset(d.bytes,0,sizeof(d.bytes));writes=d.writes;assert(!save_commit(&s,&g)&&d.writes==writes); /* both damaged preserved */
 d=golden;g.hp=0;assert(save_commit(&s,&g));assert(save_load(&s,&h,2100,1636,walk,NULL)&&h.hp==0);combat_attack(&h);assert(h.hp==h.maxhp&&h.x==2100&&h.y==1636); /* KO remains escapable */
 assert(save_load(&s,&h,2100,1636,blocked,NULL)&&h.x==2100&&h.y==1636&&h.apples==8); /* blocked location relocates */
 /* Checksums are not the only validation: reject semantically invalid data. */
 SavedCharacter c;character(&g);save_capture(&c,&g,10);unsigned char raw[SAVE_BYTES];save_encode(raw,&c);assert(save_decode(&c,raw)==1);
 const int offs[]={40,44,48,52,56,60,64,68,72,76,128};
 for(unsigned i=0;i<sizeof(offs)/sizeof(offs[0]);i++){save_encode(raw,&c);save_put(raw+offs[i],UINT32_MAX);save_put(raw+SAVE_BYTES-4,save_crc(raw,SAVE_BYTES-4));SavedCharacter unchanged=c;assert(save_decode(&unchanged,raw)==0&&unchanged.sequence==c.sequence);}
 save_encode(raw,&c);save_put(raw+24,0x7fc00000u);save_put(raw+SAVE_BYTES-4,save_crc(raw,SAVE_BYTES-4));assert(save_decode(&c,raw)==0); /* NaN */
 save_encode(raw,&c);save_put(raw+32,0);save_put(raw+36,0);save_put(raw+SAVE_BYTES-4,save_crc(raw,SAVE_BYTES-4));assert(save_decode(&c,raw)==0); /* bad facing */
 d=golden;SavedCharacter max;save_capture(&max,&g,UINT32_MAX);save_encode(d.bytes[1],&max);writes=d.writes;assert(!save_commit(&s,&g)&&d.writes==writes); /* no sequence wrap */
 c.mapId=7;save_encode(raw,&c);assert(save_decode(&c,raw)==0); /* unavailable maps rejected */
 init(&d,&s);combat_init(&g,1500,1500,walk,NULL);dev_class_preset(&g,6);g.cartOwned=1;g.cartItems[ITEM_TREE_ROOT]=10;assert(save_commit(&s,&g)&&!save_dirty(&s,&g));g.cartItems[ITEM_TREE_ROOT]++;assert(save_dirty(&s,&g));assert(save_commit(&s,&g)&&save_load(&s,&h,1500,1500,walk,NULL)&&h.cartOwned&&h.cartItems[ITEM_TREE_ROOT]==11&&h.ranks[57]==10&&h.extraItems[14]==3);
 puts("PASS: round-trip, dirty tracking, 512 interrupted writes, read-back failure, 4096 corruptions, recovery, foreign/IO preservation, KO, relocation, semantic bounds, sequence limit");return 0;
}
