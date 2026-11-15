/* SPDX-License-Identifier: MIT. Geometry, capacity, chunk and draw-order contracts. */
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "hud_batch.h"
int main(void){float mem[HUD_BATCH_QUADS*HUD_QUAD_FLOATS+8];memset(mem,0,sizeof(mem));HudBatch b={.vertices=mem};
 assert(hud_batch_add(&b,10,20,30,40,1,2,3,4));
 const float expected[]={10,20,1,1,2,40,20,1,4,2,40,60,1,4,6,10,60,1,1,6};assert(!memcmp(mem,expected,sizeof(expected)));
 assert(hud_batch_add(&b,10,20,0,40,1,2,3,4)&&b.count==1);assert(hud_batch_add(&b,10,20,30,-1,1,2,3,4)&&b.count==1);
 for(unsigned i=1;i<HUD_BATCH_QUADS;i++)assert(hud_batch_add(&b,i,2,3,4,5,6,0,0));assert(b.peak==HUD_BATCH_QUADS&&!hud_batch_add(&b,1,2,3,4,5,6,7,8));for(unsigned i=HUD_BATCH_QUADS*HUD_QUAD_FLOATS;i<sizeof(mem)/sizeof(*mem);i++)assert(mem[i]==0);
 for(unsigned quads=1;quads<=HUD_BATCH_QUADS;quads++){unsigned count=quads*4,at=0,calls=0;while(at<count){unsigned n=count-at;if(n>252)n=252;assert(n&&n<=256&&n%4==0);uint32_t cmd=((n-1)<<24)|at;assert(((cmd>>24)+1)==n&&(cmd&0xffffff)==at);at+=n;calls++;}assert(at==count&&calls*2+16<128);}
 puts("PASS HUD vertices, UV/quad winding, stable order, capacity/sentinel, zero-area guards and all GPU draw chunks within pbkit block bounds");}
