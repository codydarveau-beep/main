#include "interior_rooms181.h"
/* MIT. Core services only; original source placement, stock and service fees. */
#include "core_npc_data53.h"
#include "core_trader_state180.h"
enum{CN_MENU53,CN_BUY53,CN_SELL53,CN_STORAGE53,CN_CART53,CN_QUEST53,CN_WARP53,CN_HEAL53};
typedef struct{int npc,mode,choice,quantity,box,confirm,paid,tier,destination;Appearance58 preview58;}CoreNpcUI53;
static CoreNpcUI53 coreNpcUI53;
static int(*core_npc_override55)(unsigned);
#include "core_quests53.h"
#include "dungeon_services53.h"
#include "reset_service55.h"
#include "stylist58.h"
static int core_npc_near53(const Combat*g){if(g->hp<=0||g->hideLeft>0)return -1;int found=-1;float best=28.001f;for(unsigned i=0;i<CORE_NPC_COUNT53;i++){const CoreNpc53*n=coreNpcs53+i;if((core_npc_override55&&core_npc_override55(i))||n->map!=g->mapId||!rooms_near181(&interiorRooms181,g->x,g->y,n->x,n->y))continue;float d=combat_dist(g->x,g->y,n->x,n->y);if(d<best){best=d;found=i;}}return found;}
static int core_npc_here53(const Combat*g,int id){if(id<0||id>CORE_NPC_COUNT53||(id==CORE_NPC_COUNT53&&!coreTraderRows180))return 0;const CoreNpc53*n=core_descriptor180(id);return(id==CORE_NPC_COUNT53||!core_npc_override55||!core_npc_override55((unsigned)id))&&g->hp>0&&g->hideLeft<=0&&g->mapId==n->map&&combat_dist(g->x,g->y,n->x,n->y)<=32;}
static void core_npc_open53(CoreNpcUI53*u,Combat*g,int id){*u=(CoreNpcUI53){id,core_descriptor180(id)->kind==6?CN_MENU53:core_descriptor180(id)->kind==3?CN_QUEST53:core_descriptor180(id)->kind==4?CN_WARP53:core_descriptor180(id)->kind==5?CN_HEAL53:CN_MENU53,0,1};u->tier=core_descriptor180(id)->flags;g->autoAttack=0;g->approachSkill53=0;g->route53.state=0;g->sitting=0;combat_interrupt_cast(g);combat_notice(g,POP_SYSTEM,"%s: welcome.",core_descriptor180(id)->name);}
static int core_npc_price53(const Combat*g,const CoreNpc53*n,int row){if(row<0||row>=(int)n->count)return 0;const unsigned*s=core_stock180(n->start+row);int base=s[1]?(int)s[1]:shopBuy[s[0]];if(base<=0)return 0;int price=(int)((int64_t)base*(100-shop_rate(g,0))/100);return price>0?price:1;}
static int core_npc_buy53(Combat*g,const CoreNpc53*n,int row,int quantity){int price=core_npc_price53(g,n,row);if(price<=0||quantity<1||quantity>100)return 0;unsigned item=core_stock180(n->start+row)[0];int64_t total=(int64_t)quantity*price;if(total>g->zeny){combat_notice(g,POP_ITEMS,"Not enough Zeny. Nothing spent.");return 0;}if(!inventory_can_add(g,item,quantity)||!inventory_add(g,item,quantity)){combat_notice(g,POP_ITEMS,"Not enough bag space or weight allowance.");return 0;}g->zeny-=(int)total;combat_notice(g,POP_ITEMS,"Bought %d %s for %d Zeny.",quantity,itemDefs[item].name,(int)total);return 1;}
static int core_npc_action53(const CoreNpc53*n,int row){if(n->kind==2)return row;for(int a=0;a<6;a++){if((a==0&&!(n->flags&1))||(a>=2&&a<=4&&!(n->flags&2)))continue;if(!row--)return a;}return 5;}
static int core_npc_rows53(const CoreNpcUI53*u,const Combat*g){const CoreNpc53*n=core_descriptor180(u->npc);if(u->mode==CN_MENU53)return n->kind==1?2+!!(n->flags&1)+3*!!(n->flags&2):3;if(u->mode==CN_BUY53)return n->count;return g->owned52.count[u->mode==CN_SELL53?0:u->box];}
static const OwnedItem52*core_npc_item53(const CoreNpcUI53*u,const Combat*g){unsigned box=u->mode==CN_SELL53?0:u->box;return u->choice>=0&&u->choice<g->owned52.count[box]?g->owned52.items+owned_base52(box)+u->choice:NULL;}
/* Return durable mutation; mode<0 closes the conversation. */
static int novice_quest_input54b(CoreNpcUI53*u,Combat*g,const CoreNpc53*n,unsigned p){if(p&4){u->mode=-1;return 0;}if(!(p&2))return 0;int rank=skill_rank_index(1);if(g->ranks[rank]){combat_notice(g,POP_SKILLS,"You already know First Aid.");return 0;}
 if(g->jobId!=0||!(g->joblevel>3||g->level>11)){combat_notice(g,POP_SKILLS,"Nami teaches Novices above Job 3 or Base 11.");return 0;}
 if(n->kind==8){if(g->noviceQuest54b==1){g->noviceQuest54b=2;combat_notice(g,POP_SKILLS,"The nurse provides the bandaging lesson. Return to Nami.");return 1;}combat_notice(g,POP_SKILLS,"Speak to Nami in Prontera's inn first.");return 0;}
 if(!g->noviceQuest54b){g->noviceQuest54b=1;combat_notice(g,POP_SKILLS,"Bring 3 Red Herbs,3 Clovers;visit the castle's Nursing Instructor.");return 1;}
 if(g->noviceQuest54b<2){combat_notice(g,POP_SKILLS,"Visit the Nursing Instructor in Prontera Castle first.");return 0;}
 int herb=item_source50(507),clover=item_source50(705);if(herb<0||clover<0||core_quest_count53(&g->owned52,herb)<3||core_quest_count53(&g->owned52,clover)<3){combat_notice(g,POP_SKILLS,"Need 3 plain Red Herbs and 3 plain Clovers.");return 0;}
 OwnedItems52*trial=malloc(sizeof(*trial));if(!trial)return 0;*trial=g->owned52;unsigned sources[2]={507,705};for(int k=0;k<2;k++){unsigned left=3;while(left){OwnedItem52*item=NULL;for(unsigned j=0;j<trial->count[0];j++)if(core_quest_plain53(trial->items+j,sources[k])){item=trial->items+j;break;}if(!item){free(trial);return 0;}unsigned amount=item->quantity<left?item->quantity:left;if(owned_remove52(trial,0,item->uid,amount)!=OWNED_OK52){free(trial);return 0;}left-=amount;}}g->owned52=*trial;free(trial);g->ranks[rank]=1;combat_notice(g,POP_SKILLS,"Nami taught you First Aid. No skill point spent.");return 1;}
static int core_npc_input53(CoreNpcUI53*u,Combat*g,unsigned p){if(!core_npc_here53(g,u->npc)){u->mode=-1;return 0;}const CoreNpc53*n=core_descriptor180(u->npc);if(n->kind==10)return stylist_input58(u,g,p);if(n->kind==9){if(p&4){if(u->confirm)u->confirm=0;else u->mode=-1;return 0;}if(p&(1024|2048)){u->choice=(u->choice+((p&1024)?3:1))%4;u->confirm=0;return 0;}if(!(p&2))return 0;if(u->choice==3){u->mode=-1;return 0;}if(!u->confirm){u->confirm=1;return 0;}u->confirm=0;return reset_apply55(g,u->choice);}if(n->kind==7||n->kind==8)return novice_quest_input54b(u,g,n,p);if(n->kind==6){if(p&4)u->mode=-1;else if(p&2){if(++u->choice>=(int)n->count)u->mode=-1;}return 0;}if(n->kind==4||n->kind==5)return dungeon_input53(u,g,n,p);if(n->kind==3){if(p&4){if(u->confirm)u->confirm=0;else u->mode=-1;return 0;}if(p&2){if(!u->confirm){u->confirm=1;return 0;}u->confirm=0;return core_quest_exchange53(g,n->start);}return 0;}int rows=core_npc_rows53(u,g);if(u->choice>=rows)u->choice=rows?rows-1:0;
 if(p&4){if(u->confirm)u->confirm=0;else if(u->mode==CN_MENU53)u->mode=-1;else{u->mode=CN_MENU53;u->choice=0;}return 0;}
 if(p&1024){u->choice=rows?(u->choice+rows-1)%rows:0;u->confirm=0;return 0;}if(p&2048){u->choice=rows?(u->choice+1)%rows:0;u->confirm=0;return 0;}
 if(u->mode==CN_STORAGE53||u->mode==CN_CART53){if(p&(4096|8192)){unsigned other=u->mode==CN_STORAGE53?2:1;u->box=u->box?0:other;u->choice=u->confirm=0;return 0;}}
 if(u->mode!=CN_MENU53&&(p&8)){u->quantity=u->quantity==1?10:u->quantity==10?100:1;u->confirm=0;return 0;}
 if(!(p&2))return 0;
 if(u->mode==CN_MENU53){int action=core_npc_action53(n,u->choice);
  if(n->kind==2){if(action==2){u->mode=-1;return 0;}u->mode=u->choice?CN_SELL53:CN_BUY53;u->choice=0;return 0;}
  if(action==5){u->mode=-1;return 0;}if(action==3){if(!g->cartOwned){combat_notice(g,POP_ITEMS,"Rent a cart first.");return 0;}u->mode=CN_CART53;u->box=u->choice=0;return 0;}
  if(action==1&&skill_rank(g,338)<6){combat_notice(g,POP_SKILLS,"Learn Basic Skill level 6 to use storage.");return 0;}
  if(action==1&&u->paid){u->mode=CN_STORAGE53;u->box=u->choice=0;return 0;}
  if(!u->confirm){u->confirm=1;combat_notice(g,POP_SYSTEM,"A confirms; B cancels without payment.");return 0;}u->confirm=0;
  if(action==0){WorldPosition home={n->saveMap,n->saveX,n->saveY};if(!combat_position_valid(home))return 0;g->home=home;combat_notice(g,POP_SYSTEM,"Return point set. Butterfly Wings and revival return here.");return 1;}
  if(action==1){if(g->zeny<(int)n->storage){combat_notice(g,POP_ITEMS,"Storage requires %u Zeny.",n->storage);return 0;}g->zeny-=n->storage;u->paid=1;u->mode=CN_STORAGE53;u->box=u->choice=0;combat_notice(g,POP_ITEMS,"Storage open. Access paid for this conversation.");return n->storage>0;}
  if(action==2){if((job_first50(g->jobId)!=6&&g->jobId!=J52_SUPER_NOVICE)||!skill_rank(g,63)){combat_notice(g,POP_ITEMS,"Learn Pushcart as a Merchant class first.");return 0;}if(g->cartOwned){combat_notice(g,POP_ITEMS,"You already have a cart.");return 0;}if(g->zeny<(int)n->cart){combat_notice(g,POP_ITEMS,"Cart rental requires %u Zeny.",n->cart);return 0;}g->zeny-=n->cart;g->cartOwned=1;g->cartStyle=0;combat_notice(g,POP_ITEMS,"Pushcart rented.");return 1;}
  if(action==4){if(!g->cartOwned||g->owned52.count[1]){combat_notice(g,POP_ITEMS,"Return requires an empty rented cart.");return 0;}g->cartOwned=0;g->cartStyle=0;return 1;}return 0;
 }
 if(!rows)return 0;if(!u->confirm){u->confirm=1;return 0;}u->confirm=0;
 if(u->mode==CN_BUY53)return core_npc_buy53(g,n,u->choice,u->quantity);
 const OwnedItem52*piece=core_npc_item53(u,g);if(!piece)return 0;uint32_t uid=piece->uid,source=piece->sourceID;unsigned quantity=u->quantity;if(quantity>piece->quantity)quantity=piece->quantity;int item=item_source50(source);if(item<0)return 0;
 if(u->mode==CN_SELL53)return shop_sell_uid55(g,uid,quantity);
 unsigned other=u->mode==CN_CART53?1:2,from=u->box,to=from?0:other;const OwnedRule52*rule=item_rule52(source);if((to==0&&inventory_weight(g)+(int64_t)quantity*rule->weight>inventory_weight_max(g))||(to==1&&inventory_cart_weight(g)+(int64_t)quantity*rule->weight>CART_WEIGHT_MAX)){combat_notice(g,POP_ITEMS,"Weight limit; item kept.");return 0;}if(owned_transfer52(&g->owned52,from,to,uid,quantity,item_rule52)!=OWNED_OK52){combat_notice(g,POP_ITEMS,"Transfer blocked. Unequip gear and check capacity.");return 0;}combat_notice(g,POP_ITEMS,"Transferred %u %s.",quantity,itemDefs[item].name);return 1;
}
