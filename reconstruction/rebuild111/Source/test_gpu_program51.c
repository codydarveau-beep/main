/* Real command generator: unchanged shader words, no redundant actor uploads. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
enum{NV097_SET_TRANSFORM_PROGRAM_START=1,NV097_SET_TRANSFORM_EXECUTION_MODE,NV097_SET_TRANSFORM_PROGRAM_CXT_WRITE_EN,NV097_SET_TRANSFORM_PROGRAM_LOAD,NV097_SET_TRANSFORM_PROGRAM};
static uint32_t words[4096];static unsigned used,submissions;
static uint32_t*pb_begin(void){return words+used;}
static uint32_t*pb_push1(uint32_t*p,unsigned reg,unsigned value){*p++=reg;*p++=value;return p;}
static void pb_push(uint32_t*p,unsigned reg,unsigned count){*p=reg|(count<<16);}
static void pb_end(uint32_t*p){used=p-words;submissions++;}
#include "gpu_program51.h"
int main(void){
 static const uint32_t terrain[]={
#include "terrain.inl"
 },screen[]={
#include "screen.inl"
 };
 for(int frame=0;frame<60;frame++){
  gpu_program_frame51();used=submissions=0;program(1);unsigned afterTerrain=used;assert(submissions==1);
  for(int i=0;i<40;i++)program(1);assert(used==afterTerrain&&submissions==1);
  program(0);unsigned afterScreen=used;assert(submissions==2);
  for(int i=0;i<100;i++)program(0);assert(used==afterScreen&&submissions==2);
  for(unsigned i=0;i<sizeof(terrain)/4;i+=4)assert(!memcmp(words+9+i+i/4,terrain+i,16));
  for(unsigned i=0;i<sizeof(screen)/4;i+=4)assert(!memcmp(words+afterTerrain+9+i+i/4,screen+i,16));
  program(1);assert(submissions==3);assert(!memcmp(words,words+afterScreen,afterTerrain*4));
 }
 puts("PASS60 frames: terrain/screen/terrain selects exact original shader words; 140 redundant program uploads per frame omitted; frame reset restores first upload.");
}
