/* SPDX-License-Identifier: MIT. AC97 descriptor ring accounting; no IRQ dependency. */
#ifndef MYRO_SOUND_POLL_H
#define MYRO_SOUND_POLL_H
static unsigned sound_pending(unsigned submitted,unsigned current,unsigned status){
 if(!submitted)return 0;unsigned last=(submitted-1)&31;current&=31;
 if((status&1)&&current==last)return 0; /* last descriptor drained and halted */
 return ((last-current)&31)+1;
}
#endif
