/* MIT. Exact-sized on-demand NPC files and coexistence with existing core services. */
#ifndef MYRO_NPC_GAME_XBOX55_H
#define MYRO_NPC_GAME_XBOX55_H
#include "npc_game55.h"
static NpcGame55 npcGame55;
static int npc_native_gate_available64(unsigned gate){return npc_game_gate_available64(&npcGame55,gate);}
static HANDLE npcFiles55[2];
static int coreNpcRegistry55[CORE_NPC_COUNT53];
static unsigned char coreNpcReplaced55[CORE_NPC_COUNT53];
static int npc_native_read55(void*context,unsigned kind,uint32_t at,unsigned char*out,uint32_t bytes){(void)context;if(kind>1||!out)return 0;uint32_t expected=kind?NPC_FILE_BYTES55:NPC_SCRIPT_FILE_BYTES55;if(at>expected||bytes>expected-at)return 0;
 if(!npcFiles55[kind]){const char*path=kind?"D:\\npcs.bin":"D:\\scripts.bin";HANDLE file=CreateFile(path,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);if(file==INVALID_HANDLE_VALUE)return 0;DWORD high=0,size=GetFileSize(file,&high);if(high||size!=expected){CloseHandle(file);return 0;}npcFiles55[kind]=file;}
 if(SetFilePointer(npcFiles55[kind],at,NULL,FILE_BEGIN)!=at)return 0;DWORD done=0;while(done<bytes){DWORD n=bytes-done;if(n>32768)n=32768;DWORD got=0;if(!ReadFile(npcFiles55[kind],out+done,n,&got,NULL)||!got||got>n)return 0;done+=got;}return 1;
}
static int npc_core_replaced55(unsigned index){if(index>=CORE_NPC_COUNT53)return 1;if(coreNpcReplaced55[index])return 1;int record=coreNpcRegistry55[index];return record>=0&&(npcGame55.scene.flags[record]&(N55_NPC_DISABLED|N55_NPC_HIDDEN));}
static int npc_native_can_save55(void*context){NpcGame55*g=context;if(g->pendingTalk>=0||g->lobby>=0||g->storage64.slot>=0||g->book64.slot>=0)return 0;for(unsigned i=0;i<NPC_GAME_VMS55;i++)if(g->vm[i].attached&&g->vm[i].machine.status!=N55_DONE&&g->vm[i].machine.status!=N55_ERROR)return 0;return npc_mercenary_store180(g);}
static void npc_native_init55(Combat*game){quest_journal_bind65(&npcQuests55,(npcVariables55.shared?npcVariables55.shared:npcVariables55.domain)+N55_VAR_CHARACTER);window_position_load161((npcVariables55.shared?npcVariables55.shared:npcVariables55.domain)+N55_VAR_CHARACTER);memset(coreNpcReplaced55,0,sizeof(coreNpcReplaced55));npc_game_init55(&npcGame55,game,&npcVariables55,&npcQuests55,npc_native_read55,NULL,world_script_warp55,NULL,npcSaveBridge55.utc);
 for(unsigned i=0;i<CORE_NPC_COUNT53;i++){coreNpcRegistry55[i]=-1;const CoreNpc53*old=coreNpcs53+i;if(old->map>=MYRO_MAP_COUNT43)continue;unsigned start=npcMapSpans55[old->map].start,count=npcMapSpans55[old->map].count;for(unsigned j=0;j<count;j++){unsigned id=npcMapRecords55[start+j];const NpcRecord55*n=npcRecords55+id;if(n->flags&2)continue;if(n->x!=old->x||n->y!=old->y)continue;coreNpcRegistry55[i]=(int)id;if(NPC_RELEASE_JOBS_ONLY55&&n->program)coreNpcReplaced55[i]=1;else if(old->kind==1||old->kind==2)npcGame55.scene.flags[id]|=N55_NPC_CORE;else if(old->kind==3||old->kind==6||old->kind==7||old->kind==8)coreNpcReplaced55[i]=1;break;}}
 worldGateAvailable64=npc_native_gate_available64;core_npc_override55=npc_core_replaced55;npcSaveBridge55.canSave=npc_native_can_save55;npcSaveBridge55.saveContext=&npcGame55;
}
static int npc_native_ui55(void){return npcGame55.book64.slot>=0||npcGame55.storage64.slot>=0||npcGame55.ui>=0||npcGame55.pendingTalk>=0||npcGame55.lobby>=0;}
#endif
