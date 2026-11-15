/* SPDX-License-Identifier: MIT. Shared learned-skill/item validation for both quick slots. */
#ifndef MYRO_QUICK_SLOT_H
#define MYRO_QUICK_SLOT_H
static int quick_item_valid(unsigned id){return id<ITEM_COUNT&&(itemDefs[id].healMin||itemDefs[id].spMin||itemDefs[id].equipBit);}
static unsigned quick_binding(const Combat*g,int which){return which?g->rbBinding:g->quickKind==2?BIND_EMPTY50:g->quickKind?g->quickId:BIND_ITEM_BASE50+g->quickId;}
static int quick_bind_to(Combat*g,int which,unsigned binding){
 int item=binding_item(binding);if(binding!=BIND_EMPTY50&&(!binding_valid(binding)||(item<0&&!skill_rank(g,binding)))){combat_message(g,"Learn an active skill or choose a usable item first.");return 0;}
 if(which)g->rbBinding=binding;else if(binding==BIND_EMPTY50){g->quickKind=2;g->quickId=0;}else{g->quickKind=item>=0?0:1;g->quickId=item>=0?(unsigned)item:binding;}
 combat_message(g,"%s: %s.",which?"RB":"LB",binding_name(binding));return 1;
}
static int quick_bind(Combat*g,unsigned kind,unsigned id){if(kind>1)return 0;return quick_bind_to(g,0,kind?id:BIND_ITEM_BASE50+id);}
static int bar_bind_item(Combat*g,unsigned slot,unsigned id){if(slot>=12||!quick_item_valid(id))return 0;g->hotbar[slot]=BIND_ITEM_BASE50+id;return 1;}
/* Taps use the quick action on release; holds open a window, never use an item. */
typedef struct{float elapsed[2];unsigned down,latched,suppress;} QuickHold;
static unsigned quick_hold_hints(QuickHold*h,unsigned buttons,float dt,int enabled,unsigned hints){unsigned result=0;if(!enabled){memset(h,0,sizeof(*h));h->suppress=((buttons&32)?1:0)|((buttons&512)?2:0);return 0;}for(int i=0;i<2;i++){unsigned bit=1u<<i,mask=i?512:32;if(h->suppress&bit){if(!(buttons&mask))h->suppress&=~bit;continue;}if(buttons&mask){if(!(h->down&bit)){h->elapsed[i]=0;h->down|=bit;}h->elapsed[i]+=dt;if((hints&bit)&&h->elapsed[i]>=.6f&&!(h->latched&bit)){h->latched|=bit;result|=4u<<i;}}else if(h->down&bit){if(!(h->latched&bit))result|=bit;h->down&=~bit;h->latched&=~bit;h->elapsed[i]=0;}}return result;}
static unsigned quick_hold_tick(QuickHold*h,unsigned buttons,float dt,int enabled){return quick_hold_hints(h,buttons,dt,enabled,3);}
#endif
