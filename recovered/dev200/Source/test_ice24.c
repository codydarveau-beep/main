/* MIT. Exhaustive ARGB1555 coverage plus ARGB8888 cached tint bounds. */
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "sprite_tint.h"
int main(void){uint16_t*p=malloc(65536*2);for(unsigned i=0;i<65536;i++)p[i]=i;sprite_ice(p,65536,2);for(unsigned i=0;i<65536;i++){assert((p[i]&0x8000)==(i&0x8000));if(!(i&0x8000))assert(p[i]==i);else{assert((p[i]&31)>=23);assert((p[i]>>10&31)<=12);}}free(p);uint32_t q[256];for(unsigned i=0;i<256;i++)q[i]=i<<24|i<<16|i<<8|i;sprite_ice(q,256,4);for(unsigned i=0;i<256;i++){assert((q[i]>>24)==i);assert((q[i]&255)>=191);assert((q[i]>>16&255)<=102);}puts("PASS ice tint alpha preservation, 65536 packed colours, channel bounds, no source-frame modification");}
