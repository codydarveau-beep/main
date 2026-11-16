#include "hotbar_motion.h"
/* SPDX-License-Identifier: MIT. Spatial window focus and transactional pick/drop assignment. */
#ifndef MYRO_WINDOW_UI_H
#define MYRO_WINDOW_UI_H
#include "quick_slot.h"
#include "window_layout161.h"
#include "quest_journal65.h"
enum {UI_STATUS,UI_ITEMS,UI_EQUIP,UI_SKILLS,UI_QUESTS,UI_WINDOWS65};
typedef struct {unsigned open,openSerial,openedAt[5];int active,inside,focus,choice[5],skillPage,skillScroll,itemScroll,assignBank;int questInfo257,questInfoScroll257;uint32_t questInfoID257;int skillInfo55,skillInfoScroll55;int itemInfo58,itemInfoScroll58,itemInfoId58,itemInfoKnown58;unsigned skillInfoId55;int skillDetailed46,equipPicker49,equipChoice49;int placing,dropSlot;unsigned carried;int dropRemember;float tipTime,selectionTime;int hintStat,hintSkill;unsigned observedSlot;int observedLevel,observedJob;} WindowUI;
/* Ordinals refer only to owned stacks. Catalog IDs remain stable for saves/hotbars. */
static const OwnedItem52*ui_owned_instance52(const Combat*g,int ordinal){if(ordinal<0)return NULL;for(unsigned i=0;i<g->owned52.count[0];i++)if(g->owned52.items[i].quantity&&ordinal--==0)return g->owned52.items+i;return NULL;}
static int ui_owned_count47(const Combat*g){int n=0;for(unsigned i=0;i<g->owned52.count[0];i++)if(g->owned52.items[i].quantity)n++;return n;}
static int ui_owned_item47(const Combat*g,int ordinal){const OwnedItem52*p=ui_owned_instance52(g,ordinal);return p?inventory_catalog52(p->sourceID):-1;}
/* Three visible rows; maintain a row viewport rather than jumping whole pages. */
static int ui_inventory_row(const Combat*g,const WindowUI*u,int choice){int count=ui_owned_count47(g),rows=(count+3)/4,max=rows>3?rows-3:0,first=u->itemScroll;if(first<0)first=0;if(first>max)first=max;if(choice>=0&&choice<count){int row=choice/4;if(row<first)first=row;else if(row>=first+3)first=row-2;}return first<0?0:first>max?max:first;}
static int ui_top_position42(int w){return w==UI_QUESTS?0:w==UI_EQUIP?1:w==UI_STATUS?2:w==UI_ITEMS?3:4;}
static int ui_top_window42(int position){static const int order[]={UI_QUESTS,UI_EQUIP,UI_STATUS,UI_ITEMS,UI_SKILLS};return order[position];}
static int ui_available(const WindowUI*u,int f){return f>=0&&f<10&&(f<5||(u->open&(1u<<(f-5))));}
static int ui_count(int w){return w==UI_QUESTS?(int)quest_count65():w==UI_STATUS?6:w==UI_ITEMS?ITEM_COUNT:w==UI_EQUIP?EQUIP_SLOTS46:8;}
static void ui_ack(WindowUI*u,int w){if(w==UI_STATUS)u->hintStat=0;if(w==UI_SKILLS)u->hintSkill=0;}
static void ui_open(WindowUI*u,int w,int inside){u->skillPage=1;u->questInfo257=0;u->skillInfo55=0;u->equipPicker49=0;u->open|=1u<<w;u->openedAt[w]=++u->openSerial;u->focus=5+w;u->inside=inside;u->active=1;u->placing=0;u->tipTime=4;ui_ack(u,w);}
static void ui_close(WindowUI*u,int w){u->questInfo257=0;u->equipPicker49=0;u->open&=~(1u<<w);u->inside=u->placing=0;u->tipTime=0;int last=-1;for(int i=0;i<5;i++)if((u->open&(1u<<i))&&(last<0||u->openedAt[i]>=u->openedAt[last]))last=i;if(last<0){u->active=0;u->focus=w;}else{u->active=1;u->focus=5+last;}}

static const OwnedItem52*ui_equip_instance52(const Combat*g,int slot,int ordinal){if(ordinal<=0)return NULL;for(unsigned i=0;i<g->owned52.count[0];i++){const OwnedItem52*p=g->owned52.items+i;int id=inventory_catalog52(p->sourceID);if(p->quantity&&!p->equipped&&!(p->flags&OWNED_BROKEN52)&&id>=0&&inventory_fits50(g,id,slot)&&--ordinal==0)return p;}return NULL;}
static int ui_equip_item49(const Combat*g,int slot,int ordinal){const OwnedItem52*p=ui_equip_instance52(g,slot,ordinal);return p?inventory_catalog52(p->sourceID):-1;}
static int ui_equip_count49(const Combat*g,int slot){int n=1;while(ui_equip_instance52(g,slot,n))n++;return n;}
/* Choose open windows by direction. Diagonal peers remain reachable without
 * passing through the top buttons; same-row/column peers win when present. */
static void ui_spatial(WindowUI*u,unsigned p){int f=u->focus;if(f<5){int position=ui_top_position42(f);if(p&4096)u->focus=ui_top_window42(position?position-1:0);else if(p&8192)u->focus=ui_top_window42(position<4?position+1:4);else if(p&2048){int best=-1,score=99999,x=292+position*40;for(int k=0;k<5;k++)if(u->open&(1u<<k)){int cost=abs(windowX[k]+windowWidth161[k]/2-x)*3+windowY[k];if(cost<score){best=5+k;score=cost;}}if(best>=0)u->focus=best;}return;}int w=f-5,best=-1,score=99999,sx=windowX[w]+windowWidth161[w]/2,sy=windowY[w]+windowHeight161[w]/2;for(int k=0;k<5;k++)if(k!=w&&(u->open&(1u<<k))){int dx=windowX[k]+windowWidth161[k]/2-sx,dy=windowY[k]+windowHeight161[k]/2-sy;if(((p&4096)&&dx>=0)||((p&8192)&&dx<=0)||((p&1024)&&dy>=0)||((p&2048)&&dy<=0))continue;int cost=(p&(4096|8192))?abs(dy)*3+abs(dx):abs(dx)*3+abs(dy);if(cost<score){score=cost;best=5+k;}}if(best>=0)u->focus=best;else if(p&1024)u->focus=w;}

static void ui_tick(WindowUI*u,const Combat*g,float dt){u->skillPage=1;if(!u->active||!u->inside||u->focus!=5+UI_QUESTS)u->questInfo257=0;if(!u->active||!u->inside||u->focus!=5+UI_SKILLS)u->skillInfo55=0;if(!u->active||!u->inside||(u->focus!=5+UI_ITEMS&&u->focus!=5+UI_EQUIP))u->itemInfo58=0;if(!u->active||!u->inside||u->focus!=5+UI_EQUIP)u->equipPicker49=0;int owned=ui_owned_count47(g);if(u->choice[UI_ITEMS]>=owned)u->choice[UI_ITEMS]=owned?owned-1:-1;hotbar_motion(g->hotSlot/6,dt);if(!u->active)u->dropRemember=0;if(u->tipTime>0)u->tipTime-=dt;if(u->selectionTime>0)u->selectionTime-=dt;if(g->hotSlot+g->hotAttack*12!=u->observedSlot){u->selectionTime=2.5f;u->observedSlot=g->hotSlot+g->hotAttack*12;}if(g->level>u->observedLevel)u->hintStat=1;if(g->joblevel>u->observedJob)u->hintSkill=1;u->observedLevel=g->level;u->observedJob=g->joblevel;if(u->active&&u->inside&&u->focus==5+UI_STATUS)u->hintStat=0;if(u->active&&u->inside&&u->focus==5+UI_SKILLS)u->hintSkill=0;}
static void ui_unbind(Combat*g,unsigned binding){for(int i=0;i<12;i++)if(g->hotbar[i]==binding)g->hotbar[i]=BIND_EMPTY50;for(int i=0;i<2;i++)if(quick_binding(g,i)==binding)quick_bind_to(g,i,BIND_EMPTY50);combat_message(g,"Removed bindings for %s.",binding_name(binding));}
/* LB flanks the left edge, RB the right; rows remain spatially connected. */
static void ui_drop_move(WindowUI*u,unsigned p){int n=u->dropSlot;if(n<12){int col=n%6,row=(n/6)^(u->assignBank&1);if(p&4096)n=col?n-1:12;else if(p&8192)n=col<5?n+1:13;else if((p&1024)&&row)n^=6;else if((p&2048)&&!row)n^=6;}else{if(n==12&&(p&8192))n=(u->assignBank&1)*6;else if(n==13&&(p&4096))n=(u->assignBank&1)*6+5;}u->dropSlot=n;}
/* Slots are drawn as two columns, five rows, in row-major order. */
static int ui_equip_move50b(int slot,unsigned p){
 if(slot<0)return p&1024?EQUIP_SLOTS46-2:p&2048?0:-1;
 if(p&1024)return slot<2?-1:slot-2;
 if(p&2048)return slot+2>=EQUIP_SLOTS46?-1:slot+2;
 if(p&4096)return slot&1?slot-1:slot;
 if(p&8192)return !(slot&1)&&slot+1<EQUIP_SLOTS46?slot+1:slot;
 return slot;
}
static void ui_input(WindowUI*u,Combat*g,unsigned p){
 if(!u->active)return;if(!u->inside&&u->focus>=5&&(p&128)){window_position_reset161((unsigned)(u->focus-5));return;}u->skillPage=1;if(p)u->tipTime=4;
 if(u->questInfo257){if(p&(2|4|64))u->questInfo257=0;else if(p&8)quest_toggle65(u->questInfoID257);else if(p&1024){if(u->questInfoScroll257)u->questInfoScroll257--;}else if(p&2048)u->questInfoScroll257++;return;}
 if(u->itemInfo58){if(p&(4|16|64))u->itemInfo58=0;else if(p&1024){if(u->itemInfoScroll58)u->itemInfoScroll58--;}else if(p&2048)u->itemInfoScroll58++;return;}
 if(u->inside&&!u->placing&&!u->equipPicker49&&(p&16)&&(u->focus==5+UI_ITEMS||u->focus==5+UI_EQUIP)){int slot=u->choice[u->focus-5];const OwnedItem52*piece=u->focus==5+UI_ITEMS?ui_owned_instance52(g,slot):slot>=0&&slot<EQUIP_SLOTS46?inventory_instance52(g,slot):NULL;if(piece){int id=item_source50(piece->sourceID);if(id>=0){u->itemInfo58=1;u->itemInfoId58=id;u->itemInfoKnown58=piece->identified;u->itemInfoScroll58=0;}}return;}
 if(u->skillInfo55){if(p&(4|16|64))u->skillInfo55=0;else if(p&1024){if(u->skillInfoScroll55)u->skillInfoScroll55--;}else if(p&2048)u->skillInfoScroll55++;return;}
 if(u->inside&&!u->placing&&u->focus==5+UI_SKILLS&&(p&16)&&u->choice[UI_SKILLS]>=0&&u->choice[UI_SKILLS]<(int)class_count(g)){u->skillInfo55=1;u->skillInfoId55=class_skill(g,u->choice[UI_SKILLS]);u->skillInfoScroll55=0;return;}

 if(u->equipPicker49){if((p&4)||!u->inside||u->focus!=5+UI_EQUIP){u->equipPicker49=0;return;}int slot=u->choice[UI_EQUIP];if(slot<0||slot>=EQUIP_SLOTS46){u->equipPicker49=0;return;}int n=ui_equip_count49(g,slot);if(u->equipChoice49>=n)u->equipChoice49=n-1;if(p&1024)u->equipChoice49=(u->equipChoice49+n-1)%n;else if(p&2048)u->equipChoice49=(u->equipChoice49+1)%n;else if(p&2){if(!u->equipChoice49){inventory_remove46(g,slot);stat_refresh(g);}else{int id=ui_equip_item49(g,slot,u->equipChoice49);if(id<0)return;if(inventory_equip_uid52(g,ui_equip_instance52(g,slot,u->equipChoice49)->uid,slot))stat_refresh(g);}u->equipPicker49=0;}return;}
 if((p&64)&&u->focus>=5){ui_close(u,u->focus-5);return;}
 if(u->placing){if(p&4){u->placing=0;return;}ui_drop_move(u,p);if(p&16){if(u->dropSlot<12)g->hotbar[u->dropSlot]=BIND_EMPTY50;else quick_bind_to(g,u->dropSlot-12,BIND_EMPTY50);return;}if(p&2){int ok=u->dropSlot<12?(binding_valid(u->carried)&&(binding_item(u->carried)>=0||skill_rank(g,u->carried))):quick_bind_to(g,u->dropSlot-12,u->carried);if(ok){if(u->dropSlot<12)g->hotbar[u->dropSlot]=u->carried;u->placing=0;combat_message(g,"Assigned %s.",binding_name(u->carried));}}return;}
 if(p&4){if(u->inside)u->inside=0;else u->active=0;return;}
 if(!u->inside){if(p&(1024|2048|4096|8192))ui_spatial(u,p);else if(p&2){if(u->focus<5)ui_open(u,u->focus,0);else{u->inside=1;ui_ack(u,u->focus-5);}}else if((p&8)&&u->focus>=5)ui_close(u,u->focus-5);return;}
 int w=u->focus-5,*choice=&u->choice[w],count=w==UI_ITEMS?ui_owned_count47(g):w==UI_SKILLS?(int)class_count(g):ui_count(w);if(*choice< -1||*choice>=count)*choice=0;
 if(w==UI_SKILLS&&(p&32768)){u->skillDetailed46=!u->skillDetailed46;return;}
 if(w==UI_SKILLS&&*choice>=0&&(p&(32|512))){unsigned id=class_skill(g,*choice);skill_choose_rank45(g,id,(p&512)?1:-1);return;}
 if(!count){*choice=-1;if(p&2)ui_close(u,w);return;}
 if(w==UI_EQUIP&&(p&(1024|2048|4096|8192)))*choice=ui_equip_move50b(*choice,p);
 else if((w==UI_ITEMS||(w==UI_SKILLS&&!u->skillDetailed46))&&(p&(1024|2048|4096|8192))){if(p&1024)*choice=*choice<0?count-1:*choice<4?-1:*choice-4;else if(p&2048){if(*choice<0)*choice=0;else if((*choice/4+1)*4>=count)*choice=-1;else{*choice+=4;if(*choice>=count)*choice=count-1;}}else if(p&4096)*choice=*choice<0?count-1:(*choice+count-1)%count;else *choice=*choice<0?0:(*choice+1)%count;}
 else if(p&1024)*choice=*choice<=-1?count-1:*choice-1;
 else if(p&2048)*choice=*choice>=count-1?-1:*choice+1;
 else if((p&2)&&*choice==-1)ui_close(u,w);
 else if((w==UI_ITEMS||w==UI_SKILLS)&&*choice>=0&&(p&(2|16))){unsigned binding=w==UI_ITEMS?BIND_ITEM_BASE50+ui_owned_item47(g,*choice):class_skill(g,*choice);if(w==UI_SKILLS&&(binding==249||binding==165)&&(p&2)){g->utilityMenu=binding==249?500:501;g->autoAttack=0;u->active=u->inside=0;return;}if(p&16){ui_unbind(g,binding);return;}if(!binding_valid(binding)||(binding_item(binding)<0&&!skill_rank(g,binding))){combat_message(g,"Learn an active skill or choose a usable item first.");return;}u->carried=binding;u->placing=1;u->assignBank=(int)(g->hotSlot/6);if(!u->dropRemember)u->dropSlot=g->hotSlot;u->dropRemember=1;}
 else if((p&2)&&*choice>=0){if(w==UI_QUESTS){u->questInfo257=1;u->questInfoScroll257=0;u->questInfoID257=quest_at65((unsigned)*choice);}else if(w==UI_EQUIP){u->equipPicker49=1;u->equipChoice49=0;}}
 else if(p&8){if(w==UI_QUESTS&&*choice>=0){quest_toggle65(quest_at65((unsigned)*choice));}else if(w==UI_STATUS&&*choice>=0){if(!stat_raise(g,*choice))combat_message(g,"Not enough points, or stat cap reached.");}else if(w==UI_ITEMS&&*choice>=0){g->itemActionUID52=ui_owned_instance52(g,*choice)->uid;inventory_action(g,ui_owned_item47(g,*choice));if(g->utilityMenu)u->active=u->inside=0;}else if(w==UI_SKILLS&&u->skillPage&&*choice>=0)skill_learn(g,class_skill(g,*choice));}
 if(w==UI_ITEMS)u->itemScroll=ui_inventory_row(g,u,*choice);
}
#endif
