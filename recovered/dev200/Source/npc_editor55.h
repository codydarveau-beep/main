/* MIT. Bounded controller editor for original NPC numeric/string questions. */
#ifndef MYRO_NPC_EDITOR55_H
#define MYRO_NPC_EDITOR55_H
#include <stdint.h>
#include <string.h>
#include <limits.h>
#define NPC_EDITOR_BYTES55 256u
typedef struct{char text[NPC_EDITOR_BYTES55];uint32_t length,choice,string;}NpcEditor55;
static const char npcEditorKeys55[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .,_-'!?\"#$%&()*+/:;<=>@[\\]^`{|}~";
static const char npcEditorDigits55[]="1234567890-";
static unsigned npc_editor_count55(const NpcEditor55*e){return(unsigned)strlen(e->string?npcEditorKeys55:npcEditorDigits55)+1;}
static int npc_editor_number55(const char*text,int64_t*out){int negative=*text=='-';if(negative)text++;if(!*text)return 0;uint64_t n=0,limit=negative?UINT64_C(2147483648):UINT64_C(2147483647);for(;*text;text++){if(*text<'0'||*text>'9')return 0;unsigned digit=(unsigned)(*text-'0');if(n>(limit-digit)/10)return 0;n=n*10+digit;}*out=negative?-(int64_t)n:(int64_t)n;return 1;}
/* Return1submit,2cancel,0continue. START remains the pause action. */
static int npc_editor_input55(NpcEditor55*e,unsigned buttons){unsigned count=npc_editor_count55(e),columns=e->string?10:6;if(buttons&4)return 2;if(buttons&8){if(e->length)e->text[--e->length]=0;return 0;}if(buttons&16)return 1;if(buttons&4096)e->choice=(e->choice+count-1)%count;else if(buttons&8192)e->choice=(e->choice+1)%count;else if(buttons&(1024|2048)){unsigned rows=(count+columns-1)/columns,row=e->choice/columns,col=e->choice%columns;row=(row+((buttons&1024)?rows-1:1))%rows;e->choice=row*columns+col;if(e->choice>=count)e->choice=count-1;}else if(buttons&2){if(e->choice==count-1)return 1;if(e->length+1<NPC_EDITOR_BYTES55){e->text[e->length++]=(e->string?npcEditorKeys55:npcEditorDigits55)[e->choice];e->text[e->length]=0;}}return 0;}
#endif
