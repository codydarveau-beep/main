/* GPL-3.0-or-later. Original equipment/refinement/repair script semantics,
 * adapted from Hercules script.cpp to per-copy owned inventory. Script owns
 * prices/materials/chance rolls; these commands never charge a second time. */
#ifndef MYRO_NPC_EQUIPMENT59_H
#define MYRO_NPC_EQUIPMENT59_H
#include "npc_refine_rates59.h"
static OwnedItem52*npc_equipment_slot59(Combat*g,int64_t slot){
 static const uint32_t positions[]={0,256,16,32,2,4,64,8,128,512,1};
 if(slot<=0||slot>=11)return NULL;
 for(unsigned i=0;i<g->owned52.count[0];i++)if(g->owned52.items[i].equipped&positions[slot])return g->owned52.items+i;
 return NULL;
}
static int npc_equipment_handles59(const char*name){static const char*const names[]={"getequipid","getequipname","getequipisequiped","getequipisenableref","getequipisidentify","getequiprefinerycnt","getequipweaponlv","getequippercentrefinery","successrefitem","failedrefitem","downrefitem","getbrokenid","getbrokencount","repair","repairall"};for(unsigned i=0;i<sizeof(names)/sizeof(*names);i++)if(!strcmp(name,names[i]))return 1;return 0;}
static int npc_equipment_command59(Combat*g,NpcMachine55*m,const char*name,const NpcValue55*args,uint32_t count,NpcValue55*out){
 if(!npc_equipment_handles59(name))return-1;*out=npc_vm_number55(0);int64_t slot=0,amount=1;
 int broken=!strcmp(name,"getbrokenid"),repair=!strcmp(name,"repair"),all=!strcmp(name,"repairall"),brokenCount=!strcmp(name,"getbrokencount");
 if(broken||repair||all||brokenCount){
  if(all||brokenCount){if(count)return N55_ERROR;}else if(count!=1||!npc_vm_integer55(m,args[0],&slot))return N55_ERROR;
  unsigned ordinal=0,changed=0;
  for(unsigned i=0;i<g->owned52.count[0];i++){OwnedItem52*p=g->owned52.items+i;const OwnedRule52*r=item_rule52(p->sourceID);if(!r||!owned_gear52(r)||!(p->flags&OWNED_BROKEN52))continue;ordinal++;
   if(all||(repair&&slot==(int64_t)ordinal)){p->flags&=(uint8_t)~OWNED_BROKEN52;changed=1;}
   else if(broken&&slot==(int64_t)ordinal){*out=npc_vm_number55(p->sourceID);break;}
  }
  if(brokenCount)*out=npc_vm_number55(ordinal);if(changed){inventory_sync_gear52(g);stat_refresh(g);}return N55_READY;
 }
 if(!count||!npc_vm_integer55(m,args[0],&slot))return N55_ERROR;
 int sum=!strcmp(name,"getequiprefinerycnt"),percent=!strcmp(name,"getequippercentrefinery"),success=!strcmp(name,"successrefitem"),down=!strcmp(name,"downrefitem");
 if(sum){int64_t total=0;for(unsigned i=0;i<count;i++){if(!npc_vm_integer55(m,args[i],&slot))return N55_ERROR;OwnedItem52*p=npc_equipment_slot59(g,slot);if(p)total+=p->refine;}*out=npc_vm_number55(total);return N55_READY;}
 if(percent||success||down){if(count>2||(count==2&&!npc_vm_integer55(m,args[1],&amount)))return N55_ERROR;if(percent){if(count==1)amount=0;if(amount<0||amount>1)return N55_ERROR;}else if(amount<0||amount>10)return N55_ERROR;}
 else if(count!=1)return N55_ERROR;
 OwnedItem52*p=npc_equipment_slot59(g,slot);const OwnedRule52*r=p?item_rule52(p->sourceID):NULL;const EquipmentRule52*e=p?equipment_rule52(p->sourceID):NULL;
 if(!strcmp(name,"getequipid"))*out=npc_vm_number55(p?(int64_t)p->sourceID:-1);
 else if(!strcmp(name,"getequipname"))*out=npc_vm_string55(e?e->name:"");
 else if(!strcmp(name,"getequipisequiped"))*out=npc_vm_number55(p!=NULL);
 else if(!strcmp(name,"getequipisenableref"))*out=npc_vm_number55(r&&r->refineable);
 else if(!strcmp(name,"getequipisidentify"))*out=npc_vm_number55(p&&p->identified);
 else if(!strcmp(name,"getequipweaponlv"))*out=npc_vm_number55(e?e->weaponLevel:0);
 else if(percent){unsigned level=e?e->weaponLevel:5;if(p&&r&&r->refineable&&p->refine<10&&level<5)*out=npc_vm_number55(npcRefineRates59[level][amount][p->refine]);}
 else if(success||down){if(p&&r&&r->refineable){int level=(int)p->refine+(down?-(int)amount:(int)amount);p->refine=(uint8_t)(level<0?0:level>10?10:level);inventory_sync_gear52(g);stat_refresh(g);}}
 else if(!strcmp(name,"failedrefitem")&&p){uint32_t uid=p->uid;owned_unequip52(&g->owned52,uid);if(owned_remove52(&g->owned52,0,uid,1)!=OWNED_OK52)return N55_ERROR;inventory_sync_gear52(g);stat_refresh(g);}
 return N55_READY;
}
#endif
