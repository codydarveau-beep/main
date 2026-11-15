/* MIT. Original basic NPC item operations against the owned-instance inventory. */
#ifndef MYRO_NPC_ITEM_COMMANDS55_H
#define MYRO_NPC_ITEM_COMMANDS55_H
#include "npc_items55.h"
#include "npc_constants_data55.h"
typedef int(*NpcItemOverflow55)(void*,uint32_t,uint32_t,int);
static int npc_item_text_equal55(const char*a,const char*b){for(;*a&&*b;a++,b++){unsigned x=(unsigned char)*a,y=(unsigned char)*b;if(x>='A'&&x<='Z')x+=32;if(y>='A'&&y<='Z')y+=32;if(x!=y)return 0;}return!*a&&!*b;}
static int npc_item_source55(NpcMachine55*m,NpcValue55 arg,int allowNegative,uint32_t*out,int*identified){NpcValue55 value;int64_t source;if(!npc_vm_value55(m,arg,&value))return 0;*identified=1;
 if(value.kind==N55_STRING_KIND){if(!npc_constant55(value.text,&source)){source=0;for(unsigned i=0;i<ITEM_COUNT;i++)if(npc_item_text_equal55(itemDefs[i].name,value.text)){source=itemDefs[i].id;break;}}}else source=value.number;
 if(source<0&&allowNegative){if(source==INT64_MIN)return 0;source=-source;*identified=0;}if(source<=0||source>UINT32_MAX)return 0;const OwnedRule52*rule=item_rule52((uint32_t)source);if(!rule)return 0;if(!owned_gear52(rule))*identified=1;*out=(uint32_t)source;return 1;
}
static int npc_item_give55(Combat*g,uint32_t source,uint32_t amount,int identified,NpcItemOverflow55 overflow,void*context){if(!amount)return 1;const OwnedRule52*rule=item_rule52(source);if(!rule||amount>INT_MAX)return 0;
 if(!npc_items_fit55(g,&source,&amount,1))return overflow?overflow(context,source,amount,identified):0;OwnedItems52*trial=malloc(sizeof(*trial));if(!trial)return 0;*trial=g->owned52;inventory_compact52(trial);uint32_t first=trial->nextUID;if(owned_add52(trial,0,source,amount,item_rule52)!=OWNED_OK52){free(trial);return 0;}if(!identified)for(unsigned i=0;i<trial->count[0];i++)if(trial->items[i].uid>=first)trial->items[i].identified=0;
 if(!owned_valid52(trial,item_rule52)){free(trial);return 0;}g->owned52=*trial;free(trial);return 1;
}
static int npc_item_command55(Combat*g,uint32_t account,NpcMachine55*m,const char*name,const NpcValue55*args,uint32_t count,NpcValue55*out,NpcItemOverflow55 overflow,void*context){
 int action=!strcmp(name,"countitem")?1:!strcmp(name,"getitem")?2:!strcmp(name,"delitem")?3:!strcmp(name,"checkweight")?4:!strcmp(name,"getitemname")?5:!strcmp(name,"getitemslots")?6:0;if(!action)return-1;*out=npc_vm_number55(0);
 if(action==4){if(!count||count%2||count>NPC_VM_STACK55)return N55_ERROR;uint32_t sources[NPC_VM_STACK55/2],amounts[NPC_VM_STACK55/2];for(unsigned i=0;i<count;i+=2){int identified;int64_t amount;if(!npc_item_source55(m,args[i],0,sources+i/2,&identified)||!npc_vm_integer55(m,args[i+1],&amount)||amount<=0||amount>INT_MAX)return N55_ERROR;amounts[i/2]=(uint32_t)amount;}*out=npc_vm_number55(npc_items_fit55(g,sources,amounts,count/2));return N55_READY;}
 if(count!=(action==2||action==3?2u:1u)&&!((action==2||action==3)&&count==3))return N55_ERROR;
 uint32_t source;int identified;if(!npc_item_source55(m,args[0],action==2,&source,&identified))return N55_ERROR;
 if(action==1){*out=npc_vm_number55((int64_t)npc_item_count55(g,source));return N55_READY;}
 if(action==5){int item=item_source50(source);if(item<0)return N55_ERROR;*out=npc_vm_string55(itemDefs[item].name);return N55_READY;}
 if(action==6){*out=npc_vm_number55(item_rule52(source)->slots);return N55_READY;}
 int64_t amount,target;if(count==3&&(!npc_vm_integer55(m,args[2],&target)||target<0||target>UINT32_MAX))return N55_ERROR;if(count==3&&(uint32_t)target!=account)return N55_READY;
 if(!npc_vm_integer55(m,args[1],&amount)||amount>INT_MAX)return N55_ERROR;if(amount<=0)return N55_READY;return(action==2?npc_item_give55(g,source,(uint32_t)amount,identified,overflow,context):npc_item_take55(g,source,(uint32_t)amount))?N55_READY:N55_ERROR;
}
#endif
