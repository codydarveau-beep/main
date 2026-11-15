/* MIT. Bounded integer/string formatting used by original job dialogues. */
#ifndef MYRO_NPC_FORMAT55_H
#define MYRO_NPC_FORMAT55_H
static int npc_format55(NpcMachine55*m,const NpcValue55*args,unsigned count,NpcValue55*out){
 if(!count)return N55_ERROR;NpcValue55 format;if(!npc_vm_value55(m,args[0],&format)||format.kind!=N55_STRING_KIND)return N55_ERROR;char text[4096];unsigned used=0,arg=1;const char*p=format.text;
 while(*p){if(*p!='%'){if(used+1>=sizeof(text))return N55_ERROR;text[used++]=*p++;continue;}p++;if(*p=='%'){if(used+1>=sizeof(text))return N55_ERROR;text[used++]=*p++;continue;}unsigned zero=*p=='0',width=0;if(zero)p++;while(*p>='0'&&*p<='9'){width=width*10+(*p++-'0');if(width>128)return N55_ERROR;}if(arg>=count)return N55_ERROR;NpcValue55 v;if(!npc_vm_value55(m,args[arg++],&v))return N55_ERROR;char number[160];const char*part=number;int size;
  if(*p=='s'){if(v.kind!=N55_STRING_KIND)return N55_ERROR;part=v.text;size=(int)strlen(part);}else{if(v.kind!=N55_NUMBER_KIND)return N55_ERROR;if(*p=='d'||*p=='i')size=snprintf(number,sizeof(number),zero?"%0*lld":"%*lld",(int)width,(long long)v.number);else if(*p=='u')size=snprintf(number,sizeof(number),zero?"%0*llu":"%*llu",(int)width,(unsigned long long)v.number);else if(*p=='x'||*p=='X')size=snprintf(number,sizeof(number),*p=='X'?(zero?"%0*llX":"%*llX"):(zero?"%0*llx":"%*llx"),(int)width,(unsigned long long)v.number);else return N55_ERROR;if(size<0||size>=(int)sizeof(number))return N55_ERROR;}
  p++;if((unsigned)size>=sizeof(text)-used)return N55_ERROR;memcpy(text+used,part,(size_t)size);used+=(unsigned)size;
 }text[used]=0;if(used+1>NPC_VM_TEXT55-m->textUsed)return N55_ERROR;char*copy=m->text+m->textUsed;memcpy(copy,text,used+1);m->textUsed+=used+1;*out=npc_vm_string55(copy);return N55_READY;
}
#endif
