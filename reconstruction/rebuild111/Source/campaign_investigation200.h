/* MIT. Witness receipts from acknowledged, unchanged native Payon dialogue. */
#ifndef MYRO_CAMPAIGN_INVESTIGATION200_H
#define MYRO_CAMPAIGN_INVESTIGATION200_H
#include "campaign_state200.h"
#include "chapter1_data200.h"
/* Bit0: Vuicokk's Undead account; bit1: the grandson's independent memory.
 * Bit2 is a physical archive comparison, granted only by the world adapter. */
static int campaign_investigation_page200(NpcState55*state,unsigned playerMap,unsigned npcMap,const char*unique,const char*text){
 Campaign200 c;if(!state||!unique||!text||campaign_load200(state,&c)!=1||c.cursor!=3||c.checkpoint!=CHAPTER2_INVESTIGATION_GATE200||playerMap!=11||npcMap!=11)return 1;
 unsigned bit=32;if(!strcmp(unique,"Monster Scholar#02")&&strstr(text,"citizens of Payon!"))bit=0;else if(!strcmp(unique,"Young Man#2payon")&&strstr(text,"dearly departed grandfather"))bit=1;
 if(bit==32||(c.objectives&(1u<<bit)))return 1;
 return campaign_objective200(state,3,bit);
}
#endif
