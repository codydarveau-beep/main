/* Original appearance/readparam commands backed by the real character state.
 * Unsupported look types/values fail explicitly rather than becoming no-ops. */
#ifndef MYRO_NPC_APPEARANCE59_H
#define MYRO_NPC_APPEARANCE59_H
#include "appearance_limits58.h"
static int npc_appearance_command59(Combat*g,NpcMachine55*m,const char*name,const NpcValue55*args,uint32_t count,NpcValue55*out){int64_t look,value;*out=npc_vm_number55(0);
 if(!strcmp(name,"getlook")){if(count!=1||!npc_vm_integer55(m,args[0],&look))return N55_ERROR;switch(look){case 0:value=job_source52(g->jobId);break;case 1:value=g->appearance58.hair+1;break;case 6:value=g->appearance58.colour;break;case 7:value=g->appearance58.cloth;break;default:return N55_ERROR;}*out=npc_vm_number55(value);return N55_READY;}
 if(!strcmp(name,"setlook")){if(count!=2||!npc_vm_integer55(m,args[0],&look)||!npc_vm_integer55(m,args[1],&value))return N55_ERROR;Appearance58 a=g->appearance58;unsigned actor=class_actor_id50(g->jobId,g->mounted48);if(look==1&&value>=1&&value<=42)a.hair=(unsigned)value-1;else if(look==6&&value>=0&&value<=8)a.colour=(unsigned)value;else if(look==7&&value>=0&&actor<49&&value<=clothMax58[actor])a.cloth=(unsigned)value;else return N55_ERROR;g->appearance58=a;return N55_READY;}
 if(!strcmp(name,"getbattleflag")){NpcValue55 v;if(count!=1||!npc_vm_value55(m,args[0],&v)||v.kind!=N55_STRING_KIND)return N55_ERROR;static const struct{const char*name;int value;}flags[]={{"features/replace_refine_npcs",0},{"min_hair_style",1},{"max_hair_style",42},{"min_hair_color",0},{"max_hair_color",8},{"min_cloth_color",0},{"max_cloth_color",4}};if(!strcmp(v.text,"max_cloth_color")){unsigned actor=class_actor_id50(g->jobId,g->mounted48);*out=npc_vm_number55(actor<49?clothMax58[actor]:0);return N55_READY;}for(unsigned i=0;i<sizeof(flags)/sizeof(*flags);i++)if(!strcmp(v.text,flags[i].name)){*out=npc_vm_number55(flags[i].value);return N55_READY;}return N55_ERROR;}
 if(!strcmp(name,"readparam")){if(count!=1||!npc_vm_integer55(m,args[0],&look))return N55_ERROR;if(look>=13&&look<=18)value=g->stats[look-13];else if(look==5)value=g->hp;else if(look==6)value=g->maxhp;else if(look==7)value=g->sp;else if(look==8)value=g->maxsp;else return N55_ERROR;*out=npc_vm_number55(value);return N55_READY;}
 return-1;
}
#endif
