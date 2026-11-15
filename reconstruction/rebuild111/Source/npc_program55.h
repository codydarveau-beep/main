/* MIT. Checked portable NPC program container; loaded one conversation at a time. */
#ifndef MYRO_NPC_PROGRAM55_H
#define MYRO_NPC_PROGRAM55_H
#include <stdlib.h>
#include <zlib.h>
#include "npc_vm55.h"
#define NPC_PROGRAM_HEADER55 40u
typedef struct{NpcProgram55 program;void*allocation;}NpcLoadedProgram55;
static uint32_t npc_program_u3255(const unsigned char*p){return(uint32_t)p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;}
static void npc_program_free55(NpcLoadedProgram55*p){if(p){free(p->allocation);memset(p,0,sizeof(*p));}}
static int npc_program_verify55(const NpcProgram55*p){
 if(!npc_vm_program55(p)||p->strings[0]||p->strings[p->stringBytes-1])return 0;
 for(uint32_t i=0;i<p->count;i++){NpcInstruction55 in=p->code[i];if(in.op>N55_UPDATE)return 0;
 switch(in.op){case N55_STRING:case N55_REF:case N55_CALL:if(!npc_vm_text55(p,in.a))return 0;if(in.op==N55_CALL&&in.b>NPC_VM_STACK55)return 0;break;
 case N55_JUMP:case N55_JZ:if(in.a>=p->count)return 0;break;
 case N55_UNARY:if(in.a>N55_COMPLEMENT)return 0;break;
 case N55_BINARY:if(in.a>N55_OR)return 0;break;
 case N55_UPDATE:if(in.a>1||in.b>1)return 0;break;
 default:break;}}
 for(unsigned kind=0;kind<2;kind++){const NpcEntry55*t=kind?p->functions:p->labels;uint32_t count=kind?p->functionCount:p->labelCount;
  for(uint32_t i=0;i<count;i++){const char*name=npc_vm_text55(p,t[i].name);if(!name||!*name||t[i].entry>=p->count)return 0;for(uint32_t j=0;j<i;j++)if(!strcmp(name,npc_vm_text55(p,t[j].name)))return 0;}}
 return 1;
}
/* Failure never replaces a previously loaded program. Input bytes need not remain live. */
static int npc_program_load55(NpcLoadedProgram55*out,const void*bytes,size_t length){
 if(!out||!bytes||length<NPC_PROGRAM_HEADER55)return 0;const unsigned char*b=bytes;
 if(memcmp(b,"MYRONP55",8)||npc_program_u3255(b+8)!=1||npc_program_u3255(b+12)!=length)return 0;
 uint32_t nc=npc_program_u3255(b+16),ns=npc_program_u3255(b+20),nl=npc_program_u3255(b+24),nf=npc_program_u3255(b+28);
 if(!nc||nc>NPC_VM_MAX_CODE55||!ns||ns>NPC_VM_MAX_STRINGS55||nl>nc||nf>nc)return 0;
 uint64_t expected=NPC_PROGRAM_HEADER55+(uint64_t)nc*12+((uint64_t)nl+nf)*8+ns;
 if(expected!=length||crc32(crc32(0,b,32),b+36,(uInt)(length-36))!=npc_program_u3255(b+32))return 0;
 /* Owner is a stable 32-bit packed identity, widened by the interpreter. */
 size_t codeBytes=nc*sizeof(NpcInstruction55),entryBytes=((size_t)nl+nf)*sizeof(NpcEntry55);
 void*mem=malloc(codeBytes+entryBytes+ns);if(!mem)return 0;NpcLoadedProgram55 trial={0};trial.allocation=mem;
 NpcInstruction55*code=mem;NpcEntry55*entries=(NpcEntry55*)((unsigned char*)mem+codeBytes);char*strings=(char*)entries+entryBytes;size_t at=NPC_PROGRAM_HEADER55;
 for(uint32_t i=0;i<nc;i++,at+=12)code[i]=(NpcInstruction55){npc_program_u3255(b+at),npc_program_u3255(b+at+4),npc_program_u3255(b+at+8)};
 for(uint32_t i=0;i<nl+nf;i++,at+=8)entries[i]=(NpcEntry55){npc_program_u3255(b+at),npc_program_u3255(b+at+4)};
 memcpy(strings,b+at,ns);trial.program=(NpcProgram55){code,nc,strings,ns,entries,entries+nl,nl,nf,npc_program_u3255(b+36)};
 if(!npc_program_verify55(&trial.program)){npc_program_free55(&trial);return 0;}npc_program_free55(out);*out=trial;return 1;
}
/* The disc reader already owns a complete, aligned program allocation. Decode
 * its fixed-width words in place rather than retaining a second full copy.
 * Only success transfers ownership. Failure preserves the loaded program;
 * the caller still owns (and may free) the rejected input. */
static int npc_program_take180(NpcLoadedProgram55*out,unsigned char**bytes,size_t length){
 if(!out||!bytes||!*bytes||length<NPC_PROGRAM_HEADER55||sizeof(NpcInstruction55)!=12||sizeof(NpcEntry55)!=8)return 0;
 unsigned char*b=*bytes;
 if(memcmp(b,"MYRONP55",8)||npc_program_u3255(b+8)!=1||npc_program_u3255(b+12)!=length)return 0;
 uint32_t nc=npc_program_u3255(b+16),ns=npc_program_u3255(b+20),nl=npc_program_u3255(b+24),nf=npc_program_u3255(b+28);
 if(!nc||nc>NPC_VM_MAX_CODE55||!ns||ns>NPC_VM_MAX_STRINGS55||nl>nc||nf>nc)return 0;
 uint64_t expected=NPC_PROGRAM_HEADER55+(uint64_t)nc*12+((uint64_t)nl+nf)*8+ns;
 if(expected!=length||crc32(crc32(0,b,32),b+36,(uInt)(length-36))!=npc_program_u3255(b+32))return 0;
 NpcInstruction55*code=(NpcInstruction55*)(b+NPC_PROGRAM_HEADER55);
 NpcEntry55*entries=(NpcEntry55*)(b+NPC_PROGRAM_HEADER55+nc*12);
 size_t at=NPC_PROGRAM_HEADER55;
 for(uint32_t i=0;i<nc;i++,at+=12){NpcInstruction55 in={npc_program_u3255(b+at),npc_program_u3255(b+at+4),npc_program_u3255(b+at+8)};code[i]=in;}
 for(uint32_t i=0;i<nl+nf;i++,at+=8){NpcEntry55 entry={npc_program_u3255(b+at),npc_program_u3255(b+at+4)};entries[i]=entry;}
 NpcLoadedProgram55 trial={0};trial.allocation=b;
 trial.program=(NpcProgram55){code,nc,(char*)b+at,ns,entries,entries+nl,nl,nf,npc_program_u3255(b+36)};
 if(!npc_program_verify55(&trial.program))return 0;
 npc_program_free55(out);*out=trial;*bytes=NULL;return 1;
}
#endif
