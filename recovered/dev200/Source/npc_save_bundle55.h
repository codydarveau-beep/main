/* MIT. Character and persistent NPC state share one checksummed transaction. */
#ifndef MYRO_NPC_SAVE_BUNDLE55_H
#define MYRO_NPC_SAVE_BUNDLE55_H
#include "npc_state55.h"
#define NPC_BUNDLE_HEADER55 64u
#define NPC_BUNDLE_CHARACTER55 1048576u
#define NPC_BUNDLE_LIMIT55 (NPC_BUNDLE_HEADER55+NPC_BUNDLE_CHARACTER55+4u*NPC_STATE_FILE55)
typedef struct{unsigned char*character;uint32_t characterBytes,sequence;uint64_t utc;NpcState55 state[4];}NpcSaveBundle55;
static void npc_bundle_clear55(NpcSaveBundle55*b){if(!b)return;free(b->character);for(unsigned i=0;i<4;i++)npc_state_clear55(b->state+i);memset(b,0,sizeof(*b));}
static uint32_t npc_bundle_crc55(const unsigned char*p,uint32_t n){return crc32(crc32(0,p,56),p+60,n-60);}
/* Four stores: character flags, account flags, world flags, quest log. */
static int npc_bundle_encode55(const unsigned char*character,uint32_t characterBytes,const NpcState55*const states[4],uint32_t sequence,uint64_t utc,unsigned char**out,uint32_t*outBytes){
 if(!character||!characterBytes||characterBytes>NPC_BUNDLE_CHARACTER55||!sequence||!out||!outBytes)return 0;uint64_t total=NPC_BUNDLE_HEADER55+characterBytes;uint32_t sizes[4];for(unsigned i=0;i<4;i++){if(!states[i])return 0;sizes[i]=npc_state_wire_bytes55(states[i]);if(sizes[i]>NPC_STATE_FILE55)return 0;total+=sizes[i];}if(total>NPC_BUNDLE_LIMIT55)return 0;
 unsigned char*p=calloc(1,(size_t)total);if(!p)return 0;memcpy(p,"MYROSB55",8);npc_state_put32_55(p+8,1);npc_state_put32_55(p+12,(uint32_t)total);npc_state_put32_55(p+16,sequence);npc_state_put64_55(p+24,utc);npc_state_put32_55(p+32,characterBytes);uint32_t at=NPC_BUNDLE_HEADER55;memcpy(p+at,character,characterBytes);at+=characterBytes;
 for(unsigned i=0;i<4;i++){npc_state_put32_55(p+36+i*4,sizes[i]);if(!npc_state_encode55(states[i],p+at,sizes[i])){free(p);return 0;}at+=sizes[i];}npc_state_put32_55(p+56,npc_bundle_crc55(p,(uint32_t)total));*out=p;*outBytes=(uint32_t)total;return 1;
}
/* Unknown versions, truncated data and invalid character data never replace live state. */
static int npc_bundle_decode55(NpcSaveBundle55*out,const unsigned char*p,uint32_t bytes,int(*validateCharacter)(void*,const unsigned char*,uint32_t),void*context){
 if(!out||!p||bytes<NPC_BUNDLE_HEADER55||bytes>NPC_BUNDLE_LIMIT55||memcmp(p,"MYROSB55",8)||npc_state_u32_55(p+8)!=1||npc_state_u32_55(p+12)!=bytes||!npc_state_u32_55(p+16)||npc_state_u32_55(p+20)||npc_state_u32_55(p+52)||npc_state_u32_55(p+60)||npc_bundle_crc55(p,bytes)!=npc_state_u32_55(p+56))return 0;
 uint32_t characterBytes=npc_state_u32_55(p+32),sizes[4];if(!characterBytes||characterBytes>NPC_BUNDLE_CHARACTER55)return 0;uint64_t total=NPC_BUNDLE_HEADER55+(uint64_t)characterBytes;for(unsigned i=0;i<4;i++){sizes[i]=npc_state_u32_55(p+36+i*4);if(sizes[i]<32||sizes[i]>NPC_STATE_FILE55)return 0;total+=sizes[i];}if(total!=bytes||!validateCharacter||!validateCharacter(context,p+NPC_BUNDLE_HEADER55,characterBytes))return 0;
 NpcSaveBundle55 trial={0};trial.character=malloc(characterBytes);if(!trial.character)return 0;memcpy(trial.character,p+NPC_BUNDLE_HEADER55,characterBytes);trial.characterBytes=characterBytes;trial.sequence=npc_state_u32_55(p+16);trial.utc=npc_state_u64_55(p+24);uint32_t at=NPC_BUNDLE_HEADER55+characterBytes;
 for(unsigned i=0;i<4;i++){if(!npc_state_decode55(trial.state+i,p+at,sizes[i])){npc_bundle_clear55(&trial);return 0;}at+=sizes[i];}npc_bundle_clear55(out);*out=trial;return 1;
}
#endif
