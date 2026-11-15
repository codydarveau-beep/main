/* MIT. Compact shops reuse the original item-slot shadow and shared atlas.
 * Presentation only: stock, discounts, quantities and transactions are unchanged. */
static void ui_panel(int,int,int,int,const char*,int,int);
static int ui_text_width(const char*,float);
static void ui_scaled(int,int,float,const char*,...);
static void ui_fit47(int,int,int,float,const char*);
static void ui_bold_fit47(int,int,int,const char*);
static void ui_hint64(int,int,float,const char*,...);
static void ui_cell(int,int,int,int,int);
static void skin_icon(int,int,int,int,int);
static int shop_icon182(int);

#ifndef SKIN46_SLOT
#define SKIN46_SLOT 108
#endif
#include "shop_layout182.h"
static ShopLayout182 shop_frame182(const Combat*g,const char*title,const char*mode,int rows,int choice,int quantity,int nameWidth,int priceWidth){
 ShopLayout182 l=shop_layout182(rows,choice,nameWidth,priceWidth);char label[96];snprintf(label,sizeof(label),"%s",title);size_t end=strlen(label);while(end&&ui_text_width(label,1)>l.width-28)label[--end]=0;
 ui_panel(l.x,l.y,l.width,l.height,label,1,-1);ui_scaled(l.x+12,l.y+26,1,"%d Zeny",g->zeny);char amount[48];snprintf(amount,sizeof(amount),"Quantity: %d",quantity);ui_scaled(l.x+l.width-12-ui_text_width(amount,.9f),l.y+27,.9f,"%s",amount);
 pb_fill(l.x+8,l.y+47,l.width-16,20,0xffeaf0f5);ui_bold_fit47(l.x+45,l.y+49,l.nameWidth,mode);ui_bold_fit47(l.priceX,l.y+49,l.priceWidth,"Unit price");
 return l;
}
static void shop_row182(const ShopLayout182*l,int row,int item,const char*name,const char*detail,int price,int selected){
 int y=l->listY+row*32;ui_cell(l->x+8,y,l->width-16,31,selected);
 if(!selected&&row)pb_fill(l->x+12,y-1,l->width-24,1,0xffeaf0f5);
 skin_icon(SKIN46_SLOT,l->x+12,y,30,30);int icon=shop_icon182(item);if(icon>=0)skin_icon(icon,l->x+16,y+1,22,22);
 ui_fit47(l->x+46,y+1,l->nameWidth,1,name);ui_fit47(l->x+46,y+17,l->nameWidth,.8f,detail);
 char cost[40];snprintf(cost,sizeof(cost),price>0?"%d Z":"--",price);int x=l->priceX+l->priceWidth-ui_text_width(cost,1);ui_bold_fit47(x,y+8,l->priceWidth,cost);
}
static void shop_footer182(const Combat*g,const ShopLayout182*l,int total,int choice,int confirm){
 if(total>0)ui_scaled(l->x+12,l->footerY,.8f,"%d-%d / %d",l->first+1,l->first+l->visible,total);else ui_scaled(l->x+12,l->listY+6,1,"No items.");
 ui_hint64(l->x+12,l->footerY+18,.8f,confirm?"A: confirm  B: cancel":"UP/DOWN: item  A: select  B: back  X: quantity");
 ui_fit47(l->x+12,l->footerY+38,l->width-24,.8f,g->log);(void)choice;
}
static void hud_shop(const Combat*g,int choice,int sell,int quantity){
 int first=choice/8*8,count=ITEM_COUNT-first;if(count>8)count=8;int names=140,prices=70;
 for(int i=first;i<first+count;i++){int w=ui_text_width(itemDefs[i].name,1);if(w>names)names=w;char price[40];snprintf(price,sizeof(price),"%d Z",shop_price(g,i,sell));w=ui_text_width(price,1);if(w>prices)prices=w;}
 ShopLayout182 l=shop_frame182(g,"Item Shop",sell?"Sell items":"Buy items",ITEM_COUNT,choice,quantity,names,prices);
 for(int i=first;i<first+count;i++){char detail[48];snprintf(detail,sizeof(detail),"Owned: %d",inventory_count(g,i));shop_row182(&l,i-first,i,itemDefs[i].name,detail,shop_price(g,i,sell),i==choice);}
 shop_footer182(g,&l,ITEM_COUNT,choice,0);
}
