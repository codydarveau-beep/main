/* GPL-3.0-or-later. Source-compatible quest text operations, bounded by VM arena. */
#ifndef MYRO_NPC_STRING59_H
#define MYRO_NPC_STRING59_H
static int npc_string_match59(const char*a,const char*b,size_t n,int usecase){for(size_t i=0;i<n;i++)if(usecase?a[i]!=b[i]:npc_ascii_lower55((unsigned char)a[i])!=npc_ascii_lower55((unsigned char)b[i]))return 0;return 1;}
static int npc_string_command59(NpcMachine55*m,const char*name,const NpcValue55*args,uint32_t count,NpcValue55*out){
 int character=!strcmp(name,"charat"),insert=!strcmp(name,"insertchar"),replace=!strcmp(name,"replacestr");if(!character&&!insert&&!replace)return-1;
 if(count<(replace?3u:insert?3u:2u)||count>(replace?5u:insert?3u:2u))return N55_ERROR;NpcValue55 text;if(!npc_vm_value55(m,args[0],&text)||text.kind!=N55_STRING_KIND)return N55_ERROR;size_t n=strlen(text.text);int64_t index;
 if(character){if(!npc_vm_integer55(m,args[1],&index))return N55_ERROR;if(index<0||(uint64_t)index>=n){*out=npc_vm_string55("");return N55_READY;}return npc_text_copy55(m,text.text+index,1,out)?N55_READY:N55_ERROR;}
 NpcValue55 addition;if(!npc_vm_value55(m,args[1],&addition)||addition.kind!=N55_STRING_KIND)return N55_ERROR;
 if(insert){if(!npc_vm_integer55(m,args[2],&index))return N55_ERROR;size_t at=index<0?0:(uint64_t)index>n?n:(size_t)index,length=*addition.text?n+1:at;if(length>=NPC_VM_TEXT55-m->textUsed)return N55_ERROR;char*p=m->text+m->textUsed;memmove(p,text.text,at);if(*addition.text){p[at]=*addition.text;memmove(p+at+1,text.text+at,n-at);}p[length]=0;m->textUsed+=(uint32_t)length+1;*out=npc_vm_string55(p);return N55_READY;}
 NpcValue55 replacement;int64_t usecase=1,limit=-1;if(!npc_vm_value55(m,args[2],&replacement)||replacement.kind!=N55_STRING_KIND||(count>=4&&!npc_vm_integer55(m,args[3],&usecase))||(count==5&&(!npc_vm_integer55(m,args[4],&limit)||!limit)))return N55_ERROR;
 size_t find=strlen(addition.text),added=strlen(replacement.text);if(!find)return N55_ERROR;size_t length=0;int64_t found=0;
 for(size_t i=0;i<n;){int match=found!=limit&&find<=n-i&&npc_string_match59(text.text+i,addition.text,find,usecase!=0);size_t take=match?added:1;if(take>=NPC_VM_TEXT55-m->textUsed||length>=NPC_VM_TEXT55-m->textUsed-take)return N55_ERROR;length+=take;i+=match?find:1;if(match)found++;}
 if(length>=NPC_VM_TEXT55-m->textUsed)return N55_ERROR;char*p=m->text+m->textUsed;size_t used=0;found=0;for(size_t i=0;i<n;){int match=found!=limit&&find<=n-i&&npc_string_match59(text.text+i,addition.text,find,usecase!=0);if(match){memmove(p+used,replacement.text,added);used+=added;i+=find;found++;}else p[used++]=text.text[i++];}p[used]=0;m->textUsed+=(uint32_t)used+1;*out=npc_vm_string55(p);return N55_READY;
}
#endif
