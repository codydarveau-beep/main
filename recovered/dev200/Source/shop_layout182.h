/* MIT. Eight visible item rows; dimensions depend on actual page contents. */
#ifndef MYRO_SHOP_LAYOUT182_H
#define MYRO_SHOP_LAYOUT182_H
typedef struct{int x,y,width,height,first,visible,nameWidth,priceX,priceWidth,listY,footerY;}ShopLayout182;
static ShopLayout182 shop_layout182(int rows,int choice,int nameWidth,int priceWidth){
 if(rows<0)rows=0;if(choice<0)choice=0;if(rows&&choice>=rows)choice=rows-1;
 int first=choice/8*8,visible=rows-first;if(visible>8)visible=8;if(visible<0)visible=0;
 if(nameWidth<140)nameWidth=140;if(nameWidth>300)nameWidth=300;if(priceWidth<70)priceWidth=70;if(priceWidth>116)priceWidth=116;
 int width=nameWidth+priceWidth+74;if(width<360)width=360;if(width>560)width=560;nameWidth=width-priceWidth-74;
 int height=70+(visible?visible:1)*32+8+58,x=(640-width)/2,y=(480-height)/2;
 ShopLayout182 l={x,y,width,height,first,visible,nameWidth,x+width-12-priceWidth,priceWidth,y+70,y+70+(visible?visible:1)*32+8};return l;
}
#endif
