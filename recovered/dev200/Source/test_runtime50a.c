/* MIT. Hot-loop dirtiness remains equivalent, without computing disk CRCs. */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "combat.h"
#include "developer.h"
#include "projection.h"
#include "save_format.h"
/* Instrument the existing encode function itself, without replacing payload logic. */
static unsigned diskChecks50a;
static void counted_encode50a(unsigned char*p,const SavedCharacter*s){diskChecks50a++;save_encode(p,s);}
#define save_encode counted_encode50a
#include "save_store.h"
#undef save_encode
static int canonical_dirty50a(const SaveStore*s,const Combat*g){SavedCharacter c;unsigned char bytes[SAVE_BYTES];save_capture(&c,g,1);save_encode(bytes,&c);return !s->hasClean||memcmp(bytes+24,s->clean+24,56)||memcmp(bytes+84,s->clean+84,SAVE_BYTES-4-84);}
static void check_dirty50a(SaveStore*s,Combat*g){assert(!!save_dirty(s,g)==!!canonical_dirty50a(s,g));}
int main(void){static Combat g;static SaveStore s;
 for(int job=0;job<21;job++){combat_init(&g,1500,1500,NULL,NULL);dev_class_preset(&g,job);save_mark_clean(&s,&g);assert(!save_dirty(&s,&g));for(int i=0;i<1000;i++){g.rng++;assert(!save_dirty(&s,&g));}check_dirty50a(&s,&g);
  g.x+=1;check_dirty50a(&s,&g);assert(save_dirty(&s,&g));g.x-=1;
  g.hp--;check_dirty50a(&s,&g);g.hp++;g.zeny++;check_dirty50a(&s,&g);g.zeny--;
  for(int item=0;item<ITEM_COUNT;item++){g.storageItems[item]++;check_dirty50a(&s,&g);g.storageItems[item]--;}
  for(int rank=0;rank<LEARN_COUNT;rank++){g.useRanks45[rank]^=1;check_dirty50a(&s,&g);g.useRanks45[rank]^=1;}
  g.persistent50.homunHunger++;check_dirty50a(&s,&g);g.persistent50.homunHunger--;assert(!save_dirty(&s,&g));
 }
 assert(!diskChecks50a);/* The HUD/clean-marking paths never call checksum serialization. */
 SavedCharacter c,d;unsigned char disk[SAVE_BYTES];save_capture(&c,&g,2);save_encode(disk,&c);assert(save_u32(disk+SAVE_BYTES-4)==save_crc(disk,SAVE_BYTES-4)&&save_decode(&d,disk)==1);
 for(int t=0;t<64;t++)for(int z=0;z<8;z++)for(int y=-256;y<=256;y+=8){float tilt=.52f+t*.61f/63,zoom=.85f+z*.95f/7,m[16];world_camera(m,1500,1500,0,.2f,tilt,zoom);float expected=sprite_upright_depth50(8388608,y,128,zoom,tilt),actual=sprite_upright_cached50(8388608,y,128,sprite_depth_slope50(m));assert(fabsf(actual-expected)<=1);}
 puts("PASS50a21jobs/21000idle dirty checks, all catalog/rank/persistent mutations match canonical serialization, zero disk encodes in HUD, real disk CRC/save codec preserved and33280 cached-depth projections within one depth unit.");}
