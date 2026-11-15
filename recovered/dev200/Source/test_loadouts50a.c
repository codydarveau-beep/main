/* MIT. Exercise real developer switches with formerly overweight carried kits. */
#include <assert.h>
#include <stdio.h>
#include "combat.h"
#include "developer.h"
#include "save_format.h"
int main(void){static Combat g,clean;static SavedCharacter saved;static unsigned char disk[SAVE_BYTES];
 for(int previous=1;previous<=20;previous++)for(int next=1;next<=20;next++){
  combat_init(&g,1500,1500,NULL,NULL);dev_class_preset(&g,previous);if(previous==11)g.mounted48=1;
  for(int i=0;i<ITEM_COUNT;i++)*inventory_stack(&g,i)=100;/* Reproduce accumulated/overweight kit. */
  g.storageItems[ITEM_CLOVER]=17;g.cartOwned=1;g.cartItems[ITEM_JELLOPY]=23;
  dev_class_preset(&g,next);combat_init(&clean,1500,1500,NULL,NULL);dev_class_preset(&clean,next);
  assert(g.jobId==(unsigned)next&&!inventory_overweight(&g,50));assert(g.quickKind!=0||inventory_count(&g,g.quickId)>0);
  assert(g.storageItems[ITEM_CLOVER]==17&&g.cartItems[ITEM_JELLOPY]==23);
  for(int i=0;i<ITEM_COUNT;i++)assert(inventory_count(&g,i)==inventory_count(&clean,i));
  for(int slot=0;slot<EQUIP_SLOTS46;slot++){int item=inventory_slot46(&g,slot);assert(item<0||inventory_count(&g,item)>0&&inventory_fits50(&g,item,slot));}
  save_capture(&saved,&g,50);if(!save_valid(&saved)){fprintf(stderr,"invalid switch %d to %d, weight %lld/%d\n",previous,next,(long long)inventory_weight(&g),inventory_weight_max(&g));abort();}save_encode(disk,&saved);assert(save_decode(&saved,disk)==1);
  if(next==9){assert(!inventory_count(&g,ITEM_KATANA)&&!inventory_count(&g,ITEM_ARROW)&&inventory_wtype46(&g)==9);assert(dev_spawn(&g,0,3));CombatMob*m=&g.mobs[MOB_COUNT-1];m->x=g.x+10;m->y=g.y;int sp=g.sp;if(!skill_cast(&g,3,m->x,m->y)){fprintf(stderr,"Wizard cast failed after %d: %s\n",previous,g.log);abort();}for(int t=0;t<600&&combat_casting(&g);t++)combat_tick(&g,.01f,0,0);assert(g.sp<sp);}
 }
 /* A real Wizard passive recovery cycle remains enabled by the lighter kit. */
 combat_init(&g,1500,1500,NULL,NULL);dev_class_preset(&g,9);g.sp=0;memset(g.mobs,0,sizeof(g.mobs));for(int i=0;i<1100;i++)combat_tick(&g,.01f,0,0);assert(g.sp>0);
 puts("PASS50a 400 real class-switch pairs: deterministic class-only supplies, no accumulated bag weight, every kit under50%, valid equipment/Save50, storage/cart preserved, Wizard casting and SP recovery enabled.");
}
