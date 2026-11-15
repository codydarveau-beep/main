#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "sprite_tint.h"
int main(){uint16_t q[4]={0xffff,0x8000,0x0000,0x7fff};sprite_green(q,4,2);assert((q[0]&0x8000)&&(q[1]&0x8000));assert(q[2]==0&&q[3]==0x7fff);assert((q[0]>>5&31)>(q[0]>>10&31));uint32_t p[3]={0xffff0000,0xff202020,0x00336699};sprite_green(p,3,4);assert((p[0]>>24)==255&&(p[1]>>24)==255&&(p[2]>>24)==0);assert((p[1]>>8&255)>(p[1]>>16&255));puts("PASS poison green tint for16/32-bit textures; transparency/alpha preserved");}
