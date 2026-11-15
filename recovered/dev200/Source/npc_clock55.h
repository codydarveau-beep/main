/* MIT. Integer calendar conversion avoids the Xbox CRT's 32-bit time_t limit. */
#ifndef MYRO_NPC_CLOCK55_H
#define MYRO_NPC_CLOCK55_H
#include <time.h>
static int npc_clock_parts55(uint64_t stamp,struct tm*out){
 if(stamp>UINT64_C(253402300799))return 0;uint64_t days=stamp/86400;int64_t z=(int64_t)days+719468,era=z/146097;unsigned doe=(unsigned)(z-era*146097),yoe=(doe-doe/1460+doe/36524-doe/146096)/365;int year=(int)(yoe+era*400);unsigned doy=doe-(365*yoe+yoe/4-yoe/100),mp=(5*doy+2)/153,day=doy-(153*mp+2)/5+1;int month=(int)mp+(mp<10?3:-9);year+=month<=2;
 static const unsigned starts[]={0,31,59,90,120,151,181,212,243,273,304,334};memset(out,0,sizeof(*out));out->tm_year=year-1900;out->tm_mon=month-1;out->tm_mday=day;out->tm_wday=(days+4)%7;out->tm_yday=starts[month-1]+day-1+(month>2&&year%4==0&&(year%100!=0||year%400==0));unsigned sec=stamp%86400;out->tm_hour=sec/3600;out->tm_min=sec/60%60;out->tm_sec=sec%60;return 1;
}
static int npc_clock_command55(uint64_t now,NpcMachine55*m,const char*name,const NpcValue55*args,unsigned count,NpcValue55*out){
 if(strcmp(name,"gettime")&&strcmp(name,"gettimestr"))return-1;struct tm parts;
 if(!strcmp(name,"gettime")){int64_t type,local=1;if(count<1||count>2||!npc_vm_integer55(m,args[0],&type)||(count==2&&!npc_vm_integer55(m,args[1],&local))||!npc_clock_parts55(now,&parts))return N55_ERROR;
  /* Offline scripts share the Xbox clock; no server-timezone setting exists. */
  int values[]={-1,parts.tm_sec,parts.tm_min,parts.tm_hour,parts.tm_wday,parts.tm_mday,parts.tm_mon+1,parts.tm_year+1900,parts.tm_yday+1};*out=npc_vm_number55(type>=1&&type<=8?values[type]:-1);return N55_READY;
 }
 NpcValue55 format;int64_t length,stamp;if(count<2||count>3||!npc_vm_value55(m,args[0],&format)||format.kind!=N55_STRING_KIND||!npc_vm_integer55(m,args[1],&length)||length<0||length>1023)return N55_ERROR;if(count==3){if(!npc_vm_integer55(m,args[2],&stamp)||stamp<0)return N55_ERROR;now=(uint64_t)stamp;}if(!npc_clock_parts55(now,&parts))return N55_ERROR;
 char text[1024]={0};if(length&&!strftime(text,(size_t)length,format.text,&parts))text[0]=0;size_t bytes=strlen(text)+1;if(bytes>NPC_VM_TEXT55-m->textUsed)return N55_ERROR;char*copy=m->text+m->textUsed;memcpy(copy,text,bytes);m->textUsed+=(unsigned)bytes;*out=npc_vm_string55(copy);return N55_READY;
}
#endif
