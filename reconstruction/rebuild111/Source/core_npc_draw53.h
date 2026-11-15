#include "npc_direction191.h"
#include "interior_rooms181.h"
/* MIT. Compact core-service conversation and original source NPC poses. */
static void core_npc_draw53(const Combat*g,const CoreNpcUI53*u){if(u->mode<0)return;const CoreNpc53*n=core_descriptor180(u->npc);
 if(n->kind==10){
 ui_panel(72,60,496,356,n->name,1,-1);pb_fill(88,94,190,258,0xffeaf0f5);ui_outline(88,94,190,258,0xff8999b2);ui_scaled(104,104,1,"Your new look");
 ui_scaled(294,91,.85f,"500 Zeny per service");
 static const char*labels[]={"Hair style","Hair colour","Clothing colour","Leave"};
 for(unsigned i=0;i<4;i++){int y=120+i*38;ui_cell(292,y-3,260,34,u->choice==(int)i);ui_scaled(302,y+1,1,"%s",labels[i]);if(i<3){char value[20];snprintf(value,sizeof(value),"%u",stylist_value58(u->confirm?u->preview58:g->appearance58,i)+(i==0));ui_scaled(540-ui_text_width(value,1),y+1,1,"%s",value);}}
 ui_scaled(302,282,1,"Zeny: %d",g->zeny);char lines[8][96];int rows=ui_wrap(u->confirm?"Browse freely. You only pay when you confirm.":"Choose a service to preview a change.",lines,242,.85f);for(int i=0;i<rows&&i<3;i++)ui_scaled(302,305+i*16,.85f,"%s",lines[i]);
 preview_hint191(&stylistTurn191,183,303);
 ui_hint64(88,365,.9f,u->confirm?"LEFT/RIGHT: browse   A: pay 500 Zeny   B: cancel":"UP/DOWN: service   A: preview   B: leave");
 ui_fit47(88,392,464,.85f,g->log);return;
 }
 if(n->kind==9){ui_panel(100,64,440,354,n->name,1,-1);ui_scaled(116,99,.82f,"Jellopies! My beard's favourite snack.");ui_scaled(116,121,.82f,"Feed it,I'll untangle your stats and skills.");const char*labels[]={"Reset stats","Reset skills","Reset both","Leave"};for(unsigned i=0;i<4;i++){int y=170+i*34;ui_cell(111,y-2,417,30,u->choice==(int)i);if(i<3)ui_scaled(119,y,.8f,"%s: %u Zeny + %u Jellopies",labels[i],resetZeny55[i],resetJellopy55[i]);else ui_scaled(119,y,.8f,"%s",labels[i]);}ui_hint64(116,340,.8f,u->confirm?"A: confirm payment/reset | B: cancel":"A: choose | B: leave");ui_scaled(116,385,.67f,"%.87s",g->log);return;}
 if(n->kind==7||n->kind==8){ui_panel(100,64,440,354,n->name,1,-1);ui_scaled(116,101,.9f,"First Aid quest");ui_scaled(116,139,.8f,"Novice: Job level 4 or Base level 12.");ui_scaled(116,172,.8f,"Speak to Nami,then the castle Nursing Instructor.");ui_scaled(116,205,.8f,"Return to Nami with 3 Red Herbs and 3 Clovers.");ui_scaled(116,250,.8f,"Progress: %s",skill_rank(g,1)?"First Aid learned":g->noviceQuest54b==2?"Return with materials":g->noviceQuest54b==1?"Visit the castle nurse":"Speak to Nami");ui_hint64(116,340,.8f,"A: speak / complete | B: leave");ui_scaled(116,385,.67f,"%.87s",g->log);return;}
 if(n->kind==6){ui_panel(100,64,440,354,n->name,1,-1);const char*text=npcDialoguePages54a[n->start+u->choice];int row=0;while(*text&&row<9){char line[64];unsigned len=0;while(*text&&*text!='\n'&&len<sizeof(line)-1)line[len++]=*text++;line[len]=0;if(*text=='\n')text++;ui_scaled(116,102+row++*27,.8f,"%s",line);}ui_hint64(116,374,.8f,"A: %s | B: leave",u->choice+1<(int)n->count?"continue":"close");return;}
 if(n->kind==4||n->kind==5){ui_panel(100,64,440,354,n->name,1,-1);ui_scaled(116,91,.85f,"%d Zeny",g->zeny);int rows=n->kind==4?dungeon_count53(u->tier):3,first=u->choice/8*8;
 if(n->kind==4)ui_scaled(116,116,.85f,"%s | %d Zeny | L/R: tier",(const char*[]){"Low","Mid","High","Hardest"}[u->tier],dungeonWarpFees53[u->tier]);
 for(int i=first;i<rows&&i<first+8;i++){int y=151+(i-first)*24;ui_cell(111,y-2,417,23,i==u->choice);if(n->kind==4){int id=dungeon_nth53(u->tier,i);ui_scaled(121,y,.85f,"%.48s",dungeons53[id].name);}else if(i==0)ui_scaled(121,y,.85f,"Full HP/SP restore - %u Zeny",n->storage);else ui_scaled(121,y,.85f,i==1?"HP only - 100 Zeny (or what you can afford)":"Leave");}
 ui_hint64(116,360,.8f,u->confirm?"A: confirm | B: cancel":"Up/down: choose | A: select | B: leave");ui_scaled(116,390,.67f,"%.87s",g->log);return;}
 if(n->kind==3){const CoreQuest53*q=coreQuests53+n->start;ui_panel(100,64,440,354,n->name,1,-1);ui_scaled(116,92,.85f,"Repeatable item collection quest");ui_scaled(116,118,.9f,"Reward: %.36s",itemDefs[q->reward].name);for(unsigned i=0;i<q->count;i++){int item=q->needs[i][0];ui_scaled(116,157+i*27,.8f,"%.26s  %u / %u",itemDefs[item].name,core_quest_count53(&g->owned52,item),q->needs[i][1]);}ui_scaled(116,281,.8f,"Fee: %u Zeny | You have: %d",q->zeny,g->zeny);ui_scaled(116,306,.75f,"Materials must be plain and unequipped.");ui_hint64(116,342,.85f,u->confirm?"A: confirm trade | B: cancel":"A: trade materials | B: leave");ui_scaled(116,381,.67f,"%.87s",g->log);return;}
 if(u->mode==CN_BUY53||u->mode==CN_SELL53){
  int rows=core_npc_rows53(u,g),first=u->choice/8*8,names=140,prices=70;
  for(int i=first;i<rows&&i<first+8;i++){const OwnedItem52*owned=u->mode==CN_SELL53?g->owned52.items+i:NULL;int item=owned?item_source50(owned->sourceID):(int)core_stock180(n->start+i)[0];if(item<0)continue;int w=ui_text_width(itemDefs[item].name,1);if(w>names)names=w;char cost[40];snprintf(cost,sizeof(cost),"%d Z",owned?shop_price(g,item,1):core_npc_price53(g,n,i));w=ui_text_width(cost,1);if(w>prices)prices=w;}
  ShopLayout182 l=shop_frame182(g,n->name,u->mode==CN_SELL53?"Sell items":"Buy items",rows,u->choice,u->quantity,names,prices);
  for(int i=l.first;i<rows&&i<l.first+8;i++){const OwnedItem52*owned=u->mode==CN_SELL53?g->owned52.items+i:NULL;int item=owned?item_source50(owned->sourceID):(int)core_stock180(n->start+i)[0];char detail[80];if(owned)snprintf(detail,sizeof(detail),"%s+%u   Qty: %u",owned->equipped?"Equipped  ":"",owned->refine,owned->quantity);else snprintf(detail,sizeof(detail),"Owned: %d",inventory_count(g,item));shop_row182(&l,i-l.first,item,item>=0?itemDefs[item].name:"Unknown item",detail,item<0?0:owned?shop_price(g,item,1):core_npc_price53(g,n,i),i==u->choice);}
  shop_footer182(g,&l,rows,u->choice,u->confirm);return;
 }
 if(n->kind==2&&u->mode==CN_MENU53){int width=280,height=160,x=(640-width)/2,y=(480-height)/2;char title[96];snprintf(title,sizeof(title),"%s",n->name);size_t titleEnd=strlen(title);while(titleEnd&&ui_text_width(title,1)>width-24)title[--titleEnd]=0;ui_panel(x,y,width,height,title,1,-1);ui_scaled(x+12,y+27,1,"%d Zeny",g->zeny);const char*labels[]={"Buy","Sell","Leave"};for(int i=0;i<3;i++){ui_cell(x+10,y+51+i*24,width-20,22,i==u->choice);ui_scaled(x+20,y+54+i*24,1,"%s",labels[i]);}ui_hint64(x+12,y+134,.8f,"A: select  B: leave");return;}
 ui_panel(110,68,420,350,n->name,1,-1);ui_scaled(124,94,.9f,"Welcome. How may I help you?");ui_scaled(124,116,.85f,"%d Zeny | Quantity: %d",g->zeny,u->quantity);int rows=core_npc_rows53(u,g),first=u->choice/8*8;
 for(int i=first;i<rows&&i<first+8;i++){int y=148+(i-first)*25;ui_cell(121,y-2,397,24,i==u->choice);char line[100];
  if(u->mode==CN_MENU53){int action=core_npc_action53(n,i);if(n->kind==2)snprintf(line,sizeof(line),"%s",(const char*[]){"Buy","Sell","Leave"}[action]);else if(action==1)snprintf(line,sizeof(line),"Storage - %u Zeny%s",n->storage,u->paid?" (paid)":"");else if(action==2)snprintf(line,sizeof(line),"Rent Pushcart - %u Zeny",n->cart);else snprintf(line,sizeof(line),"%s",(const char*[]){"Set return point","","","Manage cart","Return empty cart","Leave"}[action]);}
  else if(u->mode==CN_BUY53){int item=core_stock180(n->start+i)[0];snprintf(line,sizeof(line),"%.27s  %d Zeny",itemDefs[item].name,core_npc_price53(g,n,i));}
  else{unsigned box=u->mode==CN_SELL53?0:u->box;const OwnedItem52*p=g->owned52.items+owned_base52(box)+i;int item=item_source50(p->sourceID);snprintf(line,sizeof(line),"%s+%u %.24s x%u",p->equipped?"E ":"",p->refine,item>=0?itemDefs[item].name:"Item",p->quantity);}
  ui_scaled(130,y,.82f,"%s",line);
 }
 if(!rows)ui_text(130,153,"No items.");
 if(u->mode==CN_STORAGE53||u->mode==CN_CART53)ui_scaled(124,354,.8f,"L/R: bag / %s | Viewing: %s",u->mode==CN_CART53?"cart":"storage",u->box?"stored items":"bag");
 ui_hint64(124,377,.8f,"%s",u->confirm?"A: confirm   B: cancel":"D-pad: choose   A: select   B: back   X: qty");ui_scaled(124,397,.65f,"%.88s",g->log);
}
#define NPC_CACHE_COUNT53 4
#define NPC_KIND53 (MOB_SPEC_COUNT+6)
static SparseSprite npcSprites53[NPC_CACHE_COUNT53];static int npcCacheModels53[NPC_CACHE_COUNT53]={-1,-1,-1,-1};
static void core_npc_render_release183(void){for(unsigned i=0;i<NPC_CACHE_COUNT53;i++){free(npcSprites53[i].raw);memset(npcSprites53+i,0,sizeof(npcSprites53[i]));npcCacheModels53[i]=-1;uploadedFrames[RENDER_MOBS+12+i]=~0u;uploadedSource[RENDER_MOBS+12+i]=NULL;}}
static void core_npc_actors53(const Combat*g,const float*m,float co,float si,DrawActor*actors,int*count){int ids[4]={-1,-1,-1,-1};float best[4]={1e30f,1e30f,1e30f,1e30f};
 for(unsigned i=0;i<CORE_NPC_COUNT53;i++){const CoreNpc53*n=coreNpcs53+i;if((core_npc_override55&&core_npc_override55(i))||n->map!=g->mapId||!rooms_point181(&interiorRooms181,n->x,n->y)||!monster_visible52(npcView64,n->x-g->x,n->y-g->y))continue;float z=height_at(n->x,n->y),x=m[0]*n->x+m[1]*n->y+m[3],y=m[4]*n->x+m[5]*n->y+m[6]*z+m[7];if(x< -60||x>700||y< -100||y>550)continue;float d=combat_dist(g->x,g->y,n->x,n->y);for(int j=0;j<4;j++)if(d<best[j]){for(int k=3;k>j;k--){best[k]=best[k-1];ids[k]=ids[k-1];}best[j]=d;ids[j]=i;break;}}
 for(int slot=0;slot<4;slot++){int model=ids[slot]<0?-1:(int)coreNpcs53[ids[slot]].model;if(model!=npcCacheModels53[slot]){while(pb_busy()){}free(npcSprites53[slot].raw);memset(npcSprites53+slot,0,sizeof(SparseSprite));npcCacheModels53[slot]=model;uploadedSource[RENDER_MOBS+12+slot]=NULL;if(model>=0){const unsigned*b=coreNpcModels53[model];if(crc32(0,coreNpcPixels53+b[0],b[1])!=b[3])fail("NPC source checksum");sprite_load(npcSprites53+slot,"core NPC",coreNpcPixels53+b[0],b[1],b[2]);}else if(entityTextures[RENDER_MOBS+12+slot]){MmFreeContiguousMemory(entityTextures[RENDER_MOBS+12+slot]);entityTextures[RENDER_MOBS+12+slot]=NULL;}}
  if(ids[slot]<0)continue;const CoreNpc53*n=coreNpcs53+ids[slot];float z=height_at(n->x,n->y),x=m[0]*n->x+m[1]*n->y+m[3],y=m[4]*n->x+m[5]*n->y+m[6]*z+m[7],depth=m[8]*n->x+m[9]*n->y+m[10]*z+m[11]-WORLD_SPRITE_BIAS,a=n->dir*.7853981634f;int dir=(int)npc_direction191(n->dir,co,si);actors[(*count)++]=(DrawActor){RENDER_MOBS+12+slot,NPC_KIND53+slot,(unsigned)dir,x,y,depth,y};
 }
}
