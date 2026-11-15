#include <assert.h>
#include <stdio.h>
#include "sound_poll.h"
int main(void){assert(!sound_pending(0,0,1));
 unsigned submitted=4,current=0;
 for(unsigned turn=0;turn<100000;turn++){
  unsigned pending=sound_pending(submitted,current&31,0);assert(pending>=1&&pending<=4);
  while(pending<4){assert((submitted&31)!=(current&31));submitted++;pending++;}
  // Consume one, two or all pending buffers; a drained CIV stays on last.
  unsigned consume=1+turn%4;
  if(consume>=pending){current=submitted-1;assert(!sound_pending(submitted,current&31,1));
   unsigned previous=submitted;for(unsigned k=0;k<4;k++){assert((submitted&31)!=(current&31));submitted++;}current=previous;
  }else current+=consume;
 }
 assert(sound_pending(32,30,0)==2);assert(sound_pending(33,31,0)==2);assert(sound_pending(33,0,1)==0);
 puts("PASS 100000 queue cycles: partial consumption, drained recovery, distinct active/refill slots and 32-descriptor wrapping");
}
