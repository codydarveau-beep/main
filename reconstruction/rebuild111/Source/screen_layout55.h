/* MIT. Final screen fitting only: the camera/world projection is unchanged. */
#ifndef MYRO_SCREEN_LAYOUT55_H
#define MYRO_SCREEN_LAYOUT55_H
#include <stdint.h>
typedef struct{int width,height,x,y;}ScreenLayout55;
static ScreenLayout55 screenLayout55={100,100,0,0};
static int screen_layout_valid55(const ScreenLayout55*s){return s->width>=50&&s->width<=100&&s->height>=50&&s->height<=100&&s->x>=-64&&s->x<=64&&s->y>=-48&&s->y<=48;}
static int screen_layout_value55(unsigned row){return row==0?screenLayout55.width:row==1?screenLayout55.height:row==2?screenLayout55.x:screenLayout55.y;}
static void screen_layout_set55(unsigned row,int value){int lo=row<2?50:row==2?-64:-48,hi=row<2?100:row==2?64:48;if(value<lo)value=lo;if(value>hi)value=hi;if(row==0)screenLayout55.width=value;else if(row==1)screenLayout55.height=value;else if(row==2)screenLayout55.x=value;else if(row==3)screenLayout55.y=value;}
static void screen_layout_constants55(float scale[4],float offset[4]){scale[0]=screenLayout55.width*.01f;scale[1]=screenLayout55.height*.01f;scale[2]=scale[3]=1;offset[0]=320*(1-scale[0])+screenLayout55.x;offset[1]=240*(1-scale[1])+screenLayout55.y;offset[2]=offset[3]=0;}
static int screen_layout_edge55(int coordinate,int horizontal){int percent=horizontal?screenLayout55.width:screenLayout55.height,size=horizontal?640:480,shift=horizontal?screenLayout55.x:screenLayout55.y;int value=coordinate*percent+(size*(100-percent))/2+shift*100;return value>=0?(value+50)/100:-((-value+50)/100);}
#endif
