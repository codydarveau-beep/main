/* MIT. Per-character logical-pixel window positions in the existing save bundle. */
#ifndef MYRO_WINDOW_LAYOUT161_H
#define MYRO_WINDOW_LAYOUT161_H
#include "npc_variables55.h"
#define WINDOW_LAYOUT_COUNT161 5
static const int windowDefaultX161[5]={185,462,18,462,18},windowDefaultY161[5]={126,118,188,294,126};
static const int windowWidth161[5]={320,172,270,172,160},windowHeight161[5]={138,174,248,144,110};
static int windowX[5]={185,462,18,462,18},windowY[5]={126,118,188,294,126};
static NpcState55*windowState161;
static unsigned windowLayoutDirty161;static int windowDrag161=-1;static float windowFractionX161,windowFractionY161;
static int window_visible_area200(unsigned i,int x,int y){int w=windowWidth161[i],h=windowHeight161[i],l=x>0?x:0,t=y>0?y:0,r=x+w<640?x+w:640,b=y+h<480?y+h:480;return r>l&&b>t?(r-l)*(b-t):0;}
static int window_position_valid161(unsigned i,int x,int y){return i<5&&window_visible_area200(i,x,y)>=(windowWidth161[i]*windowHeight161[i]+3)/4;}
static void window_clamp200(unsigned i,int*x,int*y){int w=windowWidth161[i],h=windowHeight161[i],qw=(w+3)/4,qh=(h+3)/4;if(*x<qw-w)*x=qw-w;if(*x>640-qw)*x=640-qw;if(*y<qh-h)*y=qh-h;if(*y>480-qh)*y=480-qh;int need=(w*h+3)/4;if(window_visible_area200(i,*x,*y)>=need)return;int vw=(*x<0?*x+w:*x+w>640?640-*x:w),vh=(*y<0?*y+h:*y+h>480?480-*y:h),nx=*x,ny=*y,requiredW=(need+vh-1)/vh,requiredH=(need+vw-1)/vw;if(requiredW<=w)nx=*x<0?requiredW-w:640-requiredW;if(requiredH<=h)ny=*y<0?requiredH-h:480-requiredH;if(requiredW<=w&&(requiredH>h||abs(nx-*x)<=abs(ny-*y)))*x=nx;else *y=ny;}
static int window_position_set161(unsigned i,int x,int y){if(i>=5)return 0;window_clamp200(i,&x,&y);if(x==windowX[i]&&y==windowY[i])return 0;uint32_t packed=(uint16_t)(int16_t)x|((uint32_t)(uint16_t)(int16_t)y<<16);if(windowState161&&!npc_state_set_number55(windowState161,npc_variable_key55("myro_window_layout161",0),i,(UINT64_C(1)<<32)|packed))return 0;windowX[i]=x;windowY[i]=y;windowLayoutDirty161=1;return 1;}
static int window_position_reset161(unsigned i){windowDrag161=-1;windowFractionX161=windowFractionY161=0;return i<5?window_position_set161(i,windowDefaultX161[i],windowDefaultY161[i]):0;}
static int window_position_move161(unsigned i,float dx,float dy){if(i>=5||dx!=dx||dy!=dy)return 0;if(windowDrag161!=(int)i){windowDrag161=(int)i;windowFractionX161=windowFractionY161=0;}windowFractionX161+=dx;windowFractionY161+=dy;int x=(int)windowFractionX161,y=(int)windowFractionY161;windowFractionX161-=x;windowFractionY161-=y;return window_position_set161(i,windowX[i]+x,windowY[i]+y);}
static void window_position_load161(NpcState55*state){windowState161=state;for(unsigned i=0;i<5;i++){uint64_t packed=state?(uint64_t)npc_state_number55(state,npc_variable_key55("myro_window_layout161",0),i):0;int x=(int16_t)(packed&65535),y=(int16_t)((packed>>16)&65535);if(!packed||!window_position_valid161(i,x,y)){x=windowDefaultX161[i];y=windowDefaultY161[i];}windowX[i]=x;windowY[i]=y;}windowLayoutDirty161=0;windowDrag161=-1;windowFractionX161=windowFractionY161=0;}
#endif
