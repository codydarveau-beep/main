/* MIT. Local NPC services; prototype placement/prices, bounded local storage. */
#ifndef MYRO_MERCHANT_SERVICES_H
#define MYRO_MERCHANT_SERVICES_H
enum {MS_CLOSED,MS_MENU,MS_BUY,MS_SELL,MS_CART,MS_STORAGE,MS_STYLES};
enum {MS_BUY_ROW,MS_SELL_ROW,MS_RENT_ROW,MS_MANAGE_ROW,MS_RETURN_ROW,MS_REST_ROW,MS_HOME_ROW,MS_STORAGE_ROW,MS_REPAIR_ROW,MS_LEAVE_ROW,MS_ROWS};
typedef struct {int mode,choice,item,quantity,confirm,storagePaid;} MerchantUI;
static void merchant_open(MerchantUI*u,Combat*g){memset(u,0,sizeof(*u));u->mode=MS_MENU;u->quantity=1;g->autoAttack=0;combat_notice(g,POP_ITEMS,"Buy/sell, cart and local services. Prices are prototype values.");}
static void merchant_styles_open(MerchantUI*u,Combat*g){memset(u,0,sizeof(*u));u->mode=MS_STYLES;g->autoAttack=0;combat_notice(g,POP_ITEMS,"Cart stylist: all five styles are free to test here.");}
static int merchant_here(const Combat*g,int near){return near&&g->mapId==2&&g->hp>0&&g->hideLeft<=0;}
/* Return1 only for durable changes, so the existing disk transaction saves them. */
static int merchant_service(Combat*g,int action,int near){
 if(!merchant_here(g,near)){combat_notice(g,POP_ITEMS,"Return to the Prontera merchant for services.");return 0;}
 if(action==MS_REPAIR_ROW){const OwnedItem52*piece=inventory_broken52(g);if(!piece){combat_notice(g,POP_ITEMS,"No damaged weapon; no Zeny spent.");return 0;}if(g->zeny<5000){combat_notice(g,POP_ITEMS,"Weapon repair needs 5000 Zeny; nothing spent.");return 0;}g->zeny-=5000;inventory_repair52(g,piece->uid);combat_notice(g,POP_ITEMS,"Weapon repaired for 5000 Zeny.");return 1;}
 if(action==MS_RENT_ROW){
  if(g->jobId!=6||!g->ranks[59]){combat_notice(g,POP_ITEMS,"Cart rental requires Merchant and learned Pushcart.");return 0;}
  if(g->cartOwned){combat_notice(g,POP_ITEMS,"You already have a cart. Manage or return it here.");return 0;}
  if(g->zeny<800){combat_notice(g,POP_ITEMS,"Cart rental needs 800 Zeny; nothing spent.");return 0;}
  g->zeny-=800;g->cartOwned=1;g->cartStyle=0;combat_notice(g,POP_ITEMS,"Cart rented for 800 Zeny. Pushcart opens management.");return 1;
 }
 if(action==MS_RETURN_ROW){
  if(!g->cartOwned){combat_notice(g,POP_ITEMS,"No rented cart to return.");return 0;}
  if(inventory_cart_weight(g)){combat_notice(g,POP_ITEMS,"Empty your cart before returning it. Items kept.");return 0;}
  g->cartOwned=0;g->cartStyle=0;combat_notice(g,POP_ITEMS,"Empty cart returned. Rental fees are not refunded.");return 1;
 }
 if(action==MS_REST_ROW){
  if(g->hp==g->maxhp&&g->sp==g->maxsp&&g->poisonLeft<=0&&g->blindLeft<=0&&g->silenceLeft<=0&&g->confusionLeft<=0){combat_notice(g,POP_ITEMS,"Already recovered; no Zeny spent.");return 0;}
  if(g->zeny<100){combat_notice(g,POP_ITEMS,"Recovery costs 100 Zeny; nothing spent.");return 0;}
  g->zeny-=100;g->hp=g->maxhp;g->sp=g->maxsp;g->poisonLeft=g->poisonTick=g->blindLeft=g->silenceLeft=g->confusionLeft=0;g->sitting=g->autoAttack=0;combat_interrupt_cast(g);combat_notice(g,POP_ITEMS,"Recovered HP/SP and common ailments for 100 Zeny (prototype).");return 1;
 }
 if(action==MS_HOME_ROW){WorldPosition p={g->mapId,g->x,g->y};if(!combat_position_valid(p)){combat_notice(g,POP_ITEMS,"Cannot bind this position.");return 0;}if(g->home.map==p.map&&g->home.x==p.x&&g->home.y==p.y){combat_notice(g,POP_ITEMS,"Home is already bound here.");return 0;}g->home=p;combat_notice(g,POP_ITEMS,"Home bound here in Prontera. Teleport/Warp use this point.");return 1;}
 return 0;
}
static int merchant_input(MerchantUI*u,Combat*g,unsigned p,int near){
 if(!u->mode)return 0;if(!merchant_here(g,near)){u->mode=MS_CLOSED;combat_notice(g,POP_ITEMS,"Merchant interaction closed.");return 0;}
 if(u->mode==MS_STYLES){if(u->item<0||u->item>4)u->item=0;if(p&4){u->mode=MS_CLOSED;return 0;}if(g->jobId!=6||!g->cartOwned){combat_notice(g,POP_ITEMS,"Become Merchant and rent a cart at the supplies merchant first.");return 0;}if(p&1024)u->item=(u->item+4)%5;else if(p&2048)u->item=(u->item+1)%5;else if(p&2){if(g->cartStyle==u->item){combat_notice(g,POP_ITEMS,"This cart style is already selected.");return 0;}g->cartStyle=u->item;combat_notice(g,POP_ITEMS,"Cart style %d applied. Free prototype test service.",u->item+1);return 1;}return 0;}
 if(u->mode==MS_MENU){
  if(u->confirm){if(p&4){u->confirm=0;combat_notice(g,POP_ITEMS,"Service cancelled; nothing spent.");return 0;}if(p&2){u->confirm=0;if(u->choice==MS_STORAGE_ROW){if(!u->storagePaid&&g->zeny<50){combat_notice(g,POP_ITEMS,"Local storage access costs 50 Zeny; nothing spent.");return 0;}int paid=!u->storagePaid;if(paid)g->zeny-=50;u->storagePaid=1;u->mode=MS_STORAGE;u->item=0;combat_notice(g,POP_ITEMS,"Local storage open. Access paid for this conversation.");return paid;}return merchant_service(g,u->choice,near);}return 0;}
  if(p&4){u->mode=MS_CLOSED;return 0;}
  if(p&1024)u->choice=(u->choice+MS_ROWS-1)%MS_ROWS;else if(p&2048)u->choice=(u->choice+1)%MS_ROWS;
  else if(p&2){
   if(u->choice==MS_LEAVE_ROW)u->mode=MS_CLOSED;
   else if(u->choice==MS_BUY_ROW||u->choice==MS_SELL_ROW){u->mode=u->choice==MS_BUY_ROW?MS_BUY:MS_SELL;u->item=0;}
   else if(u->choice==MS_MANAGE_ROW){if(g->jobId!=6||!g->cartOwned)combat_notice(g,POP_ITEMS,"Merchant with a rented cart required.");else{u->mode=MS_CART;u->item=0;combat_notice(g,POP_ITEMS,"Store/take cart items. Left/right: quantity; B: services.");}}
   else if(u->choice==MS_STORAGE_ROW&&u->storagePaid){u->mode=MS_STORAGE;u->item=0;}else{u->confirm=1;combat_notice(g,POP_ITEMS,"A again confirms this service; B cancels without payment.");}
  }return 0;
 }
 if(p&4){u->mode=MS_MENU;u->confirm=0;return 0;}
 if(u->mode==MS_CART&&(g->jobId!=6||!g->cartOwned)){u->mode=MS_MENU;return 0;}
 if(u->mode==MS_STORAGE&&!u->storagePaid){u->mode=MS_MENU;return 0;}int transfer=u->mode==MS_CART||u->mode==MS_STORAGE;int count=transfer?ITEM_COUNT*2:ITEM_COUNT;
 if(p&1024)u->item=(u->item+count-1)%count;else if(p&2048)u->item=(u->item+1)%count;
 else if(transfer&&(p&(4096|8192))){int q=u->quantity;u->quantity=(p&8192)?(q==1?10:q==10?100:1):(q==100?10:q==10?1:100);}
 else if(p&8)u->quantity=u->quantity==1?10:u->quantity==10?100:1;
 else if(!transfer&&(p&4096))u->mode=MS_BUY;
 else if(!transfer&&(p&8192))u->mode=MS_SELL;
 else if(p&2){
  if(!transfer)return shop_trade(g,u->item,u->quantity,u->mode==MS_SELL);
  int item=u->item%ITEM_COUNT,take=u->item>=ITEM_COUNT;
  if(u->mode==MS_STORAGE){if(!inventory_storage_transfer(g,item,u->quantity,take)){combat_notice(g,POP_ITEMS,"Storage transfer blocked by counts, equipped gear or bag weight.");return 0;}combat_notice(g,POP_ITEMS,"%s %d %s %s local storage.",take?"Took":"Stored",u->quantity,itemDefs[item].name,take?"from":"in");return 1;}
  g->cartQuantity=u->quantity;
  if(!inventory_cart_transfer(g,item,take)){combat_notice(g,POP_ITEMS,"Cart transfer blocked by counts, equipped gear or weight.");return 0;}
  combat_notice(g,POP_ITEMS,"%s %d %s.",take?"Took":"Stored",u->quantity,itemDefs[item].name);return 1;
 }return 0;
}
#endif
