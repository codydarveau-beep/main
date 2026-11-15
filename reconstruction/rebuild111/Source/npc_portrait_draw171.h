/* MIT. One original portrait texture, released when no longer requested. */
#ifndef MYRO_NPC_PORTRAIT_DRAW171_H
#define MYRO_NPC_PORTRAIT_DRAW171_H
#include "npc_portrait171.h"
static unsigned char*npcPortraitTexture171;
static int npcPortraitLoaded171=-1,npcPortraitFailed171=-1;
static unsigned npcPortraitMap171=~0u;
static int npc_portrait_read171(void*ctx,unsigned at,unsigned char*out,unsigned bytes){(void)ctx;HANDLE f=CreateFile("D:\\portraits.bin",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);if(f==INVALID_HANDLE_VALUE)return 0;DWORD high=0,size=GetFileSize(f,&high),done=0;int ok=!high&&size==NPC_PORTRAIT_FILE_BYTES171&&SetFilePointer(f,at,NULL,FILE_BEGIN)==at;while(ok&&done<bytes){DWORD count=bytes-done,got=0;if(count>32768)count=32768;ok=ReadFile(f,out+done,count,&got,NULL)&&got&&got<=count;done+=got;}CloseHandle(f);return ok;}
static void npc_portrait_release171(void){if(npcPortraitTexture171){while(pb_busy()){}MmFreeContiguousMemory(npcPortraitTexture171);}npcPortraitTexture171=NULL;npcPortraitLoaded171=npcPortraitFailed171=-1;npcPortraitMap171=~0u;}
/* Called after previous GPU work finishes, before recording this frame. */
static void npc_portrait_prepare171(NpcGame55*g){if(g->player.game->mapId!=npcPortraitMap171){npc_portrait_release171();npcPortraitMap171=g->player.game->mapId;}int index=g->cutinPosition<=4?npc_portrait_index171(g->cutin):-1;if(index<0){if(npcPortraitTexture171)npc_portrait_release171();return;}if(index==npcPortraitLoaded171||index==npcPortraitFailed171)return;
 if(!npcPortraitTexture171){MM_STATISTICS m={0};m.Length=sizeof(m);MmQueryStatistics(&m);if(m.AvailablePages*4096u<5u*1024u*1024u){npcPortraitFailed171=index;return;}npcPortraitTexture171=MmAllocateContiguousMemoryEx(NPC_PORTRAIT_RAW171,0,0x03ffafff,4096,PAGE_READWRITE|PAGE_WRITECOMBINE);if(!npcPortraitTexture171){npcPortraitFailed171=index;return;}}
 npcPortraitLoaded171=-1;if(!npc_portrait_decode171((unsigned)index,npc_portrait_read171,NULL,npcPortraitTexture171,NPC_PORTRAIT_RAW171)){npcPortraitFailed171=index;return;}npcPortraitLoaded171=index;npcPortraitFailed171=-1;}
static void npc_portrait_draw171(const NpcGame55*g){float rect[4];if(npcPortraitLoaded171<0||!npcPortraitTexture171||!g->cutin[0]||npc_portrait_index171(g->cutin)!=npcPortraitLoaded171||!npc_portrait_rect171((unsigned)npcPortraitLoaded171,g->cutinPosition,rect))return;if(g->cutinPosition==3){hud_setup_direct(skinTexture,512,SKIN_H,2048,0x0001122a,1);ui_panel((int)rect[0]-2,(int)rect[1]-20,(int)rect[2]+4,(int)rect[3]+22,"",0,-1);}hud_setup_direct(npcPortraitTexture171,512,512,2048,0x0001122a,1);hud_quad(rect[0],rect[1],rect[2],rect[3],0,0,rect[2],rect[3]);}
#endif
