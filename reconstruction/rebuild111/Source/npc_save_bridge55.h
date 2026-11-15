/* MIT. Shared alternating-save adapter: character and NPC state commit together. */
#ifndef MYRO_NPC_SAVE_BRIDGE55_H
#define MYRO_NPC_SAVE_BRIDGE55_H
#include "save_store.h"
#include "npc_variables55.h"
#include "npc_save_bundle55.h"
typedef int(*NpcSaveReadBlob55)(void*,int,unsigned char**,uint32_t*);
typedef int(*NpcSaveWriteBlob55)(void*,int,const unsigned char*,uint32_t);
typedef struct{NpcVariables55*variables;NpcState55*quests;NpcSaveBundle55 cached[2];NpcSaveReadBlob55 read;NpcSaveWriteBlob55 write;void*context;uint64_t utc;uint64_t clean[4];int hasClean;int(*canSave)(void*);void*saveContext;}NpcSaveBridge55;
static NpcState55*npc_save_state55(NpcSaveBridge55*b,unsigned i){NpcState55*states=b->variables->shared?b->variables->shared:b->variables->domain;return i==3?b->quests:states+(i==0?N55_VAR_CHARACTER:i==1?N55_VAR_ACCOUNT:N55_VAR_WORLD);}
static int npc_save_character55(void*context,const unsigned char*data,uint32_t bytes){(void)context;static SavedCharacter checked;return bytes==SAVE_BYTES&&save_decode(&checked,data)==1;}
static int npc_save_read55(void*context,int slot,unsigned char*out){NpcSaveBridge55*b=context;if(slot<0||slot>1||!b->read||!out)return SLOT_IO;unsigned char*bytes=NULL;uint32_t size=0;int status=b->read(b->context,slot,&bytes,&size);if(status!=SLOT_RAW){free(bytes);npc_bundle_clear55(b->cached+slot);return status;}
 int valid=npc_bundle_decode55(b->cached+slot,bytes,size,npc_save_character55,NULL);free(bytes);if(!valid){npc_bundle_clear55(b->cached+slot);return SLOT_BAD_SIZE;}static SavedCharacter checked;if(save_decode(&checked,b->cached[slot].character)!=1||checked.sequence!=b->cached[slot].sequence){npc_bundle_clear55(b->cached+slot);return SLOT_BAD_SIZE;}memcpy(out,b->cached[slot].character,SAVE_BYTES);return SLOT_RAW;
}
static int npc_save_write55(void*context,int slot,const unsigned char*character){NpcSaveBridge55*b=context;if(slot<0||slot>1||!b->write||!character)return 0;const NpcState55*states[4];for(unsigned i=0;i<4;i++)states[i]=npc_save_state55(b,i);unsigned char*bytes=NULL;uint32_t size=0;uint32_t sequence;
 /* Read the encoded character sequence via its decoder, not a duplicated wire offset. */
 static SavedCharacter checked;if(save_decode(&checked,character)!=1)return 0;sequence=checked.sequence;
 if(!npc_bundle_encode55(character,SAVE_BYTES,states,sequence,b->utc,&bytes,&size))return 0;int ok=b->write(b->context,slot,bytes,size);free(bytes);return ok;
}
static int npc_save_loaded55(void*context,int slot){NpcSaveBridge55*b=context;if(slot<0||slot>1||!b->cached[slot].character)return 0;for(unsigned i=0;i<4;i++){NpcState55*live=npc_save_state55(b,i);npc_state_clear55(live);*live=b->cached[slot].state[i];memset(b->cached[slot].state+i,0,sizeof(NpcState55));}while(b->variables->locals)npc_variable_release_frame55(b->variables,b->variables->locals->frame);NpcState55*domains=b->variables->shared?b->variables->shared:b->variables->domain;npc_state_clear55(domains+N55_VAR_CHARACTER_TEMP);return 1;}
static void npc_save_clean55(void*context){NpcSaveBridge55*b=context;for(unsigned i=0;i<4;i++)b->clean[i]=npc_save_state55(b,i)->revision;b->hasClean=1;}
static int npc_save_can_save55(void*context){NpcSaveBridge55*b=context;return !b->canSave||b->canSave(b->saveContext);}
static int npc_save_dirty55(void*context){NpcSaveBridge55*b=context;if(!b->hasClean)return 1;for(unsigned i=0;i<4;i++)if(b->clean[i]!=npc_save_state55(b,i)->revision)return 1;return 0;}
static void npc_save_bridge_clear55(NpcSaveBridge55*b){npc_bundle_clear55(b->cached);npc_bundle_clear55(b->cached+1);memset(b,0,sizeof(*b));}
#endif
