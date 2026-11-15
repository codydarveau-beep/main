/* MIT. Bounded, suspendable interpreter for compiled original NPC control flow. */
#ifndef MYRO_NPC_VM55_H
#define MYRO_NPC_VM55_H
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#define NPC_VM_STACK55 512u
#define NPC_VM_FRAMES55 32u
#define NPC_VM_TEXT55 32768u
#define NPC_VM_MAX_CODE55 65536u
#define NPC_VM_MAX_STRINGS55 262144u
enum{N55_STOP,N55_INT,N55_STRING,N55_REF,N55_READ,N55_STORE,N55_DUP,N55_DROP,N55_UNARY,N55_BINARY,N55_JUMP,N55_JZ,N55_CALL,N55_RETURN,N55_INDEX,N55_UPDATE};
enum{N55_ADD,N55_SUBTRACT,N55_MULTIPLY,N55_DIVIDE,N55_MODULO,N55_POWER,N55_SHIFT_LEFT,N55_SHIFT_RIGHT,N55_LESS,N55_LESS_EQUAL,N55_GREATER,N55_GREATER_EQUAL,N55_EQUAL,N55_NOT_EQUAL,N55_AND,N55_XOR,N55_OR};
enum{N55_POSITIVE,N55_NEGATIVE,N55_NOT,N55_COMPLEMENT};
enum{N55_NUMBER_KIND=1,N55_STRING_KIND,N55_REFERENCE_KIND};
enum{N55_READY,N55_DONE,N55_WAIT,N55_YIELD,N55_ERROR};
typedef struct{uint32_t op,a,b;}NpcInstruction55;
typedef struct{uint32_t name,entry;}NpcEntry55;
typedef struct{const NpcInstruction55*code;uint32_t count;const char*strings;uint32_t stringBytes;const NpcEntry55*labels,*functions;uint32_t labelCount,functionCount;uint64_t owner;}NpcProgram55;
typedef struct{int64_t number;const char*text;uint64_t owner;uint32_t kind,index,frame;}NpcValue55;
typedef struct NpcMachine55 NpcMachine55;
typedef int(*NpcRead55)(void*,const NpcValue55*,NpcValue55*);
typedef int(*NpcWrite55)(void*,const NpcValue55*,const NpcValue55*);
/* Handler returns READY/WAIT/DONE/ERROR. Unsupported commands MUST return ERROR. */
typedef int(*NpcCall55)(void*,NpcMachine55*,const char*,const NpcValue55*,uint32_t,NpcValue55*);
typedef const NpcProgram55*(*NpcResolve55)(void*,const char*);
typedef void(*NpcReleaseFrame55)(void*,uint32_t);
typedef struct{NpcRead55 read;NpcWrite55 write;NpcCall55 call;NpcResolve55 resolve;NpcReleaseFrame55 releaseFrame;void*context;}NpcApi55;
typedef struct{const NpcProgram55*program;uint32_t pc,base,argc,frame,callerFrame;uint64_t callerOwner;}NpcFrame55;
struct NpcMachine55{const NpcProgram55*program;NpcApi55 api;NpcValue55 stack[NPC_VM_STACK55];NpcFrame55 frames[NPC_VM_FRAMES55];uint32_t pc,top,depth,frame,nextFrame,status,pendingBase,textUsed;uint64_t owner,steps;char text[NPC_VM_TEXT55];const char*error;};
static NpcValue55 npc_vm_number55(int64_t value){NpcValue55 v={0};v.kind=N55_NUMBER_KIND;v.number=value;return v;}
static NpcValue55 npc_vm_string55(const char*value){NpcValue55 v={0};v.kind=N55_STRING_KIND;v.text=value;return v;}
static int npc_vm_error55(NpcMachine55*m,const char*error){m->error=error;m->status=N55_ERROR;return 0;}
static const char*npc_vm_text55(const NpcProgram55*p,uint32_t offset){if(!p||!p->strings||offset>=p->stringBytes||!memchr(p->strings+offset,0,p->stringBytes-offset))return NULL;return p->strings+offset;}
static int npc_vm_program55(const NpcProgram55*p){if(!p||!p->code||!p->count||p->count>NPC_VM_MAX_CODE55||!p->strings||!p->stringBytes||p->stringBytes>NPC_VM_MAX_STRINGS55)return 0;if((p->labelCount&&!p->labels)||(p->functionCount&&!p->functions))return 0;return 1;}
static int npc_vm_push55(NpcMachine55*m,NpcValue55 v){if(m->top>=NPC_VM_STACK55)return npc_vm_error55(m,"NPC operand stack limit");m->stack[m->top++]=v;return 1;}
static uint32_t npc_vm_floor55(const NpcMachine55*m){return m->depth?m->frames[m->depth-1].base+m->frames[m->depth-1].argc:0;}
static int npc_vm_pop55(NpcMachine55*m,NpcValue55*out){if(m->top<=npc_vm_floor55(m))return npc_vm_error55(m,"NPC operand stack underflow");*out=m->stack[--m->top];return 1;}
static int npc_vm_value55(NpcMachine55*m,NpcValue55 v,NpcValue55*out){int borrowed=v.kind==N55_REFERENCE_KIND;for(unsigned i=0;i<8;i++){if(v.kind==N55_NUMBER_KIND){*out=v;return 1;}if(v.kind==N55_STRING_KIND&&v.text){if(borrowed){size_t n=strlen(v.text);if(n>=NPC_VM_TEXT55-m->textUsed)return npc_vm_error55(m,"NPC temporary text limit");char*copy=m->text+m->textUsed;memmove(copy,v.text,n+1);m->textUsed+=(uint32_t)n+1;v.text=copy;}*out=v;return 1;}NpcValue55 next;if(v.kind!=N55_REFERENCE_KIND||!v.text||!m->api.read||!m->api.read(m->api.context,&v,&next))return npc_vm_error55(m,"NPC variable read failed");v=next;}return npc_vm_error55(m,"NPC reference cycle");}
static int npc_vm_integer55(NpcMachine55*m,NpcValue55 v,int64_t*out){NpcValue55 r;if(!npc_vm_value55(m,v,&r))return 0;if(r.kind!=N55_NUMBER_KIND)return npc_vm_error55(m,"NPC expected integer");*out=r.number;return 1;}
static int npc_vm_truth55(NpcMachine55*m,NpcValue55 v,int*out){NpcValue55 r;if(!npc_vm_value55(m,v,&r))return 0;*out=r.kind==N55_NUMBER_KIND?r.number!=0:*r.text!=0;return 1;}
static int64_t npc_vm_bits55(uint64_t bits){return bits<=INT64_MAX?(int64_t)bits:INT64_MIN+(int64_t)(bits-(UINT64_C(1)<<63));}
static int64_t npc_vm_add55(int64_t a,int64_t b){if(b>0&&a>INT64_MAX-b)return INT64_MAX;if(b<0&&a<INT64_MIN-b)return INT64_MIN;return a+b;}
static int64_t npc_vm_sub55(int64_t a,int64_t b){if(b<0&&a>INT64_MAX+b)return INT64_MAX;if(b>0&&a<INT64_MIN+b)return INT64_MIN;return a-b;}
static int64_t npc_vm_mul55(int64_t a,int64_t b){int negative=(a<0)!=(b<0);uint64_t x=a<0?0-(uint64_t)a:(uint64_t)a,y=b<0?0-(uint64_t)b:(uint64_t)b,cap=negative?UINT64_C(1)<<63:INT64_MAX;if(y&&x>cap/y)return negative?INT64_MIN:INT64_MAX;uint64_t n=x*y;return negative?(n==(UINT64_C(1)<<63)?INT64_MIN:-(int64_t)n):(int64_t)n;}
static const char*npc_vm_decimal55(int64_t n,char text[24]){char*p=text+23;*p=0;uint64_t value=n<0?0-(uint64_t)n:(uint64_t)n;do{*--p=(char)('0'+value%10);value/=10;}while(value);if(n<0)*--p='-';return p;}
static int npc_vm_concat55(NpcMachine55*m,NpcValue55 a,NpcValue55 b,NpcValue55*out){char left[24],right[24];const char*x=a.kind==N55_NUMBER_KIND?npc_vm_decimal55(a.number,left):a.text,*y=b.kind==N55_NUMBER_KIND?npc_vm_decimal55(b.number,right):b.text;uint32_t room=NPC_VM_TEXT55-m->textUsed;size_t nx=strlen(x),ny=strlen(y);if(nx>=room||ny>=room-nx)return npc_vm_error55(m,"NPC temporary text limit");char*p=m->text+m->textUsed;memcpy(p,x,nx);memcpy(p+nx,y,ny+1);m->textUsed+=(uint32_t)(nx+ny+1);*out=npc_vm_string55(p);return 1;}
static int npc_vm_binary55(NpcMachine55*m,uint32_t op,NpcValue55 left,NpcValue55 right,NpcValue55*out){NpcValue55 a,b;if(!npc_vm_value55(m,left,&a)||!npc_vm_value55(m,right,&b))return 0;if(op==N55_ADD&&(a.kind==N55_STRING_KIND||b.kind==N55_STRING_KIND))return npc_vm_concat55(m,a,b,out);
 if(a.kind==N55_STRING_KIND||b.kind==N55_STRING_KIND){if(a.kind!=b.kind||op<N55_LESS||op>N55_NOT_EQUAL)return npc_vm_error55(m,"NPC invalid string operation");int c=strcmp(a.text,b.text);*out=npc_vm_number55(op==N55_LESS?c<0:op==N55_LESS_EQUAL?c<=0:op==N55_GREATER?c>0:op==N55_GREATER_EQUAL?c>=0:op==N55_EQUAL?c==0:c!=0);return 1;}
 int64_t x=a.number,y=b.number,n=0;switch(op){case N55_ADD:n=npc_vm_add55(x,y);break;case N55_SUBTRACT:n=npc_vm_sub55(x,y);break;case N55_MULTIPLY:n=npc_vm_mul55(x,y);break;case N55_DIVIDE:if(!y)return npc_vm_error55(m,"NPC division by zero");n=x==INT64_MIN&&y==-1?INT64_MAX:x/y;break;case N55_MODULO:if(!y)return npc_vm_error55(m,"NPC modulo by zero");n=x==INT64_MIN&&y==-1?0:x%y;break;case N55_POWER:if(y<0)return npc_vm_error55(m,"NPC negative integer exponent");n=1;while(y){if(y&1)n=npc_vm_mul55(n,x);y>>=1;if(y)x=npc_vm_mul55(x,x);}break;case N55_SHIFT_LEFT:if(y<0||y>=64)return npc_vm_error55(m,"NPC shift range");n=npc_vm_bits55((uint64_t)x<<y);break;case N55_SHIFT_RIGHT:if(y<0||y>=64)return npc_vm_error55(m,"NPC shift range");n=!y?x:npc_vm_bits55(((uint64_t)x>>y)|(x<0?(UINT64_MAX<<(64-y)):0));break;case N55_LESS:n=x<y;break;case N55_LESS_EQUAL:n=x<=y;break;case N55_GREATER:n=x>y;break;case N55_GREATER_EQUAL:n=x>=y;break;case N55_EQUAL:n=x==y;break;case N55_NOT_EQUAL:n=x!=y;break;case N55_AND:n=npc_vm_bits55((uint64_t)x&(uint64_t)y);break;case N55_XOR:n=npc_vm_bits55((uint64_t)x^(uint64_t)y);break;case N55_OR:n=npc_vm_bits55((uint64_t)x|(uint64_t)y);break;default:return npc_vm_error55(m,"NPC unknown binary operation");}*out=npc_vm_number55(n);return 1;}
static int npc_vm_target55(NpcMachine55*m,uint32_t pc){if(pc>=m->program->count)return npc_vm_error55(m,"NPC branch outside code");m->pc=pc;return 1;}
static int npc_vm_entry55(const NpcProgram55*p,const NpcEntry55*table,uint32_t count,const char*name,uint32_t*out){for(uint32_t i=0;i<count;i++){const char*s=npc_vm_text55(p,table[i].name);if(s&&!strcmp(s,name)){if(table[i].entry>=p->count)return 0;*out=table[i].entry;return 1;}}return 0;}
static int npc_vm_enter55(NpcMachine55*m,const NpcProgram55*p,uint32_t entry,uint32_t base,uint32_t argc){if(!npc_vm_program55(p)||entry>=p->count||base>m->top||argc>m->top-base||m->depth>=NPC_VM_FRAMES55)return npc_vm_error55(m,"NPC call frame limit or invalid function");if(m->nextFrame==UINT32_MAX)return npc_vm_error55(m,"NPC frame identity limit");m->frames[m->depth++]=(NpcFrame55){m->program,m->pc,base,argc,++m->nextFrame,m->frame,m->owner};if(p->owner)m->owner=p->owner;m->program=p;m->pc=entry;m->frame=m->nextFrame;return 1;}
static void npc_vm_cancel55(NpcMachine55*m){if(m->api.releaseFrame){while(m->depth){m->api.releaseFrame(m->api.context,m->frame);m->frame=m->frames[--m->depth].callerFrame;}m->api.releaseFrame(m->api.context,m->frame);}m->top=m->depth=0;m->status=N55_DONE;}
static int npc_vm_start55(NpcMachine55*m,const NpcProgram55*p,uint32_t entry,uint64_t owner,NpcApi55 api){memset(m,0,sizeof(*m));m->api=api;m->program=p;m->owner=owner;m->frame=m->nextFrame=1;if(!npc_vm_program55(p)||entry>=p->count)return npc_vm_error55(m,"NPC invalid program");m->pc=entry;return 1;}
static int npc_vm_resume55(NpcMachine55*m,NpcValue55 result){if(m->status!=N55_WAIT)return npc_vm_error55(m,"NPC resume without pending input");m->top=m->pendingBase;m->status=N55_READY;return npc_vm_push55(m,result);}
static int npc_vm_call55(NpcMachine55*m,const char*name,uint32_t argc){if(argc>m->top-npc_vm_floor55(m))return npc_vm_error55(m,"NPC call argument underflow");uint32_t base=m->top-argc,entry;NpcValue55*outArgs=m->stack+base,result=npc_vm_number55(0);
 if(!strcmp(name,"getargcount")){if(argc)return npc_vm_error55(m,"NPC getargcount arguments");if(!m->depth)return npc_vm_error55(m,"NPC getargcount outside function");result=npc_vm_number55(m->frames[m->depth-1].argc);}
 else if(!strcmp(name,"getarg")){int64_t index;if(!argc||argc>2||!npc_vm_integer55(m,outArgs[0],&index))return npc_vm_error55(m,"NPC getarg arguments");if(!m->depth)return npc_vm_error55(m,"NPC getarg outside function");NpcFrame55*f=m->frames+m->depth-1;if(index<0||(uint64_t)index>=f->argc){if(argc<2)return npc_vm_error55(m,"NPC missing required argument");result=outArgs[1];}else result=m->stack[f->base+(uint32_t)index];}
 else if(!strcmp(name,"set")){if((argc!=2&&argc!=3)||outArgs[0].kind!=N55_REFERENCE_KIND||!m->api.write)return npc_vm_error55(m,"NPC set arguments");NpcValue55 value;result=outArgs[0];if(argc==3&&!npc_vm_value55(m,outArgs[2],&result))return 0;if(!npc_vm_value55(m,outArgs[1],&value)||!m->api.write(m->api.context,outArgs,&value))return npc_vm_error55(m,"NPC set failed");}
 else if(npc_vm_entry55(m->program,m->program->functions,m->program->functionCount,name,&entry))return npc_vm_enter55(m,m->program,entry,base,argc);
 else if(!strcmp(name,"callsub")||!strcmp(name,"callfunc")){if(!argc)return npc_vm_error55(m,"NPC missing function name");const char*target=NULL;if(!strcmp(name,"callsub")&&outArgs[0].kind==N55_REFERENCE_KIND)target=outArgs[0].text;else{NpcValue55 n;if(!npc_vm_value55(m,outArgs[0],&n)||n.kind!=N55_STRING_KIND)return npc_vm_error55(m,"NPC invalid function name");target=n.text;}if(!strcmp(name,"callsub")){if(!npc_vm_entry55(m->program,m->program->labels,m->program->labelCount,target,&entry))return npc_vm_error55(m,"NPC missing subroutine label");memmove(m->stack+base,m->stack+base+1,(argc-1)*sizeof(*m->stack));m->top--;return npc_vm_enter55(m,m->program,entry,base,argc-1);}const NpcProgram55*p=m->api.resolve?m->api.resolve(m->api.context,target):NULL;if(!p)return npc_vm_error55(m,"NPC missing global function");memmove(m->stack+base,m->stack+base+1,(argc-1)*sizeof(*m->stack));m->top--;return npc_vm_enter55(m,p,0,base,argc-1);}
 else{if(!m->api.call)return npc_vm_error55(m,"NPC command handler absent");int status=m->api.call(m->api.context,m,name,outArgs,argc,&result);if(status==N55_WAIT){m->pendingBase=base;m->status=N55_WAIT;return 1;}if(status==N55_DONE){npc_vm_cancel55(m);return 1;}if(status!=N55_READY)return npc_vm_error55(m,"NPC unsupported or failed command");}
 m->top=base;return npc_vm_push55(m,result);
}
static int npc_vm_run55(NpcMachine55*m,uint32_t budget){if(m->status==N55_WAIT||m->status==N55_DONE||m->status==N55_ERROR)return m->status;m->status=N55_READY;while(budget--){if(m->pc>=m->program->count){npc_vm_error55(m,"NPC instruction outside program");break;}NpcInstruction55 in=m->program->code[m->pc++];NpcValue55 a,b,r;int64_t index;int truth;m->steps++;
 switch(in.op){case N55_STOP:npc_vm_cancel55(m);return m->status;case N55_INT:if(!npc_vm_push55(m,npc_vm_number55(npc_vm_bits55((uint64_t)in.a|(uint64_t)in.b<<32))))return m->status;break;
 case N55_STRING:case N55_REF:{const char*s=npc_vm_text55(m->program,in.a);if(!s){npc_vm_error55(m,"NPC string outside pool");return m->status;}r=npc_vm_string55(s);if(in.op==N55_REF){r.kind=N55_REFERENCE_KIND;r.owner=m->owner;r.frame=m->frame;}if(!npc_vm_push55(m,r))return m->status;break;}
 case N55_READ:if(!npc_vm_pop55(m,&a)||!npc_vm_value55(m,a,&r)||!npc_vm_push55(m,r))return m->status;break;
 case N55_STORE:if(!npc_vm_pop55(m,&b)||!npc_vm_pop55(m,&a)||!npc_vm_value55(m,b,&r))return m->status;if(a.kind!=N55_REFERENCE_KIND||!m->api.write||!m->api.write(m->api.context,&a,&r)){npc_vm_error55(m,"NPC variable assignment failed");return m->status;}if(!npc_vm_push55(m,r))return m->status;break;
 case N55_DUP:if(m->top<=npc_vm_floor55(m)){npc_vm_error55(m,"NPC duplicate underflow");return m->status;}if(!npc_vm_push55(m,m->stack[m->top-1]))return m->status;break;
 case N55_DROP:if(!npc_vm_pop55(m,&a))return m->status;/* Escaping values must be copied by state/UI handlers. No live arguments remain here. */if(!m->depth&&!m->top)m->textUsed=0;break;
 case N55_UNARY:if(!npc_vm_pop55(m,&a))return m->status;if(in.a==N55_NOT){if(!npc_vm_truth55(m,a,&truth))return m->status;r=npc_vm_number55(!truth);}else{if(!npc_vm_integer55(m,a,&index))return m->status;if(in.a>N55_COMPLEMENT){npc_vm_error55(m,"NPC unknown unary operation");return m->status;}r=npc_vm_number55(in.a==N55_POSITIVE?index:in.a==N55_NEGATIVE?(index==INT64_MIN?INT64_MAX:-index):npc_vm_bits55(~(uint64_t)index));}if(!npc_vm_push55(m,r))return m->status;break;
 case N55_BINARY:if(!npc_vm_pop55(m,&b)||!npc_vm_pop55(m,&a)||!npc_vm_binary55(m,in.a,a,b,&r)||!npc_vm_push55(m,r))return m->status;break;
 case N55_JUMP:if(!npc_vm_target55(m,in.a))return m->status;break;
 case N55_JZ:if(!npc_vm_pop55(m,&a)||!npc_vm_truth55(m,a,&truth))return m->status;if(!truth&&!npc_vm_target55(m,in.a))return m->status;break;
 case N55_CALL:{const char*name=npc_vm_text55(m->program,in.a);if(!name){npc_vm_error55(m,"NPC command name outside pool");return m->status;}if(!npc_vm_call55(m,name,in.b))return m->status;if(m->status==N55_WAIT||m->status==N55_DONE)return m->status;break;}
 case N55_RETURN:if(!npc_vm_pop55(m,&a)||!npc_vm_value55(m,a,&r))return m->status;if(!m->depth){npc_vm_cancel55(m);return m->status;}{if(r.kind==N55_STRING_KIND){NpcValue55 copy;if(!npc_vm_concat55(m,r,npc_vm_string55(""),&copy))return m->status;r=copy;}NpcFrame55 f=m->frames[--m->depth];if(m->api.releaseFrame)m->api.releaseFrame(m->api.context,m->frame);m->top=f.base;m->program=f.program;m->pc=f.pc;m->frame=f.callerFrame;m->owner=f.callerOwner;if(!npc_vm_push55(m,r))return m->status;}break;
 case N55_INDEX:if(!npc_vm_pop55(m,&b)||!npc_vm_pop55(m,&a)||!npc_vm_integer55(m,b,&index))return m->status;if(a.kind!=N55_REFERENCE_KIND||index<0||index>=32768){npc_vm_error55(m,"NPC array index range");return m->status;}a.index=(uint32_t)index;if(!npc_vm_push55(m,a))return m->status;break;
 case N55_UPDATE:if(!npc_vm_pop55(m,&a)||a.kind!=N55_REFERENCE_KIND||!npc_vm_integer55(m,a,&index)){npc_vm_error55(m,"NPC update requires integer variable");return m->status;}r=npc_vm_number55(npc_vm_add55(index,in.a?1:-1));if(!m->api.write||!m->api.write(m->api.context,&a,&r)){npc_vm_error55(m,"NPC increment failed");return m->status;}if(!npc_vm_push55(m,in.b?npc_vm_number55(index):r))return m->status;break;
 default:npc_vm_error55(m,"NPC unknown instruction");return m->status;
 }
 }if(m->status==N55_READY)m->status=N55_YIELD;return m->status;}
#endif
