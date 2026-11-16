/* MIT. HUD-pass corners: float thickness avoids quantizing33% to a50% change. */
static void ui_target_solid(float x,float y,float w,float h,unsigned color){for(unsigned i=0;i<sizeof(skinColors)/sizeof(skinColors[0]);i++)if(skinColors[i]==color){float u,v;hud_solid_uv(i,&u,&v);hud_quad(x,y,w,h,u,v,0,0);return;}fail("Target marker palette missing");}
static void ui_target_marker(int x,int y,int hp,int maxhp){if(x<20||x>620||y<80||y>412)return;const float t=4.f/3,top=y-23,bottom=y+4,left=x-12,right=x+12;
 for(int side=0;side<2;side++){float xx=side?right-7:left,vx=side?right-t:left;ui_target_solid(xx,top,7,t,0xffffdf56);ui_target_solid(vx,top,t,6,0xffffdf56);ui_target_solid(xx,bottom-t,7,t,0xffffdf56);ui_target_solid(vx,bottom-6,t,6,0xffffdf56);}
 if(!enemyHPTesting261)return;pb_fill(x-16,y-29,32,4,0xff181818);int n=maxhp>0?hp*30/maxhp:0;if(n>30)n=30;if(n>0)pb_fill(x-15,y-28,n,2,0xff6bde71);
}
#include "target_geometry41.h"
/* Current native path uses current sprite crop rather than a fixed24px box. */
static void ui_target_bounds41(TargetBounds41 r,int hp,int maxhp){if(r.x1<2||r.x0>638||r.y1<2||r.y0>478)return;if(r.x0<2)r.x0=2;if(r.y0<9)r.y0=9;if(r.x1>638)r.x1=638;if(r.y1>478)r.y1=478;const float t=4.f/3;for(int side=0;side<2;side++){float x=side?r.x1-7:r.x0,vx=side?r.x1-t:r.x0;ui_target_solid(x,r.y0,7,t,0xffffdf56);ui_target_solid(vx,r.y0,t,6,0xffffdf56);ui_target_solid(x,r.y1-t,7,t,0xffffdf56);ui_target_solid(vx,r.y1-6,t,6,0xffffdf56);}if(!enemyHPTesting261)return;int x=(int)((r.x0+r.x1)*.5f),y=(int)r.y0-7;if(x<25)x=25;if(x>615)x=615;if(y<2)y=2;pb_fill(x-24,y,48,4,0xff181818);int n=maxhp>0?hp*46/maxhp:0;if(n>46)n=46;if(n>0)pb_fill(x-23,y+1,n,2,0xff6bde71);}
/* Selected-monster labels use the name literally: no spell punctuation. */
static void ui_enemy_label47(TargetBounds41 r,const char*name,int hp,int maxhp){
 float center=(r.x0+r.x1)*.5f;if(enemyHPTesting261){char current[24],maximum[24];snprintf(current,sizeof(current),"%d /",hp);snprintf(maximum,sizeof(maximum),"%d",maxhp);float scale=.7f;int width=ui_text_width(current,scale),other=ui_text_width(maximum,scale);if(other>width)width=other;if(width>46)scale*=46.f/width;int barY=(int)r.y0-7,y=barY-22;if(y<2)y=2;for(int row=0;row<2;row++){const char*text=row?maximum:current;int w=ui_text_width(text,scale),x=(int)(center-w/2.f);if(x<2)x=2;if(x+w>628)x=628-w;ui_scaled(x+1,y+row*10+1,scale,"%s",text);ui_light(x,y+row*10,scale,text);}
 }float ns=.8f;int w=ui_text_width(name,ns)+10;if(w>220){ns*=210.f/(w-10);w=220;}int x=(int)(center-w*.5f),ny=(int)r.y1+4;if(x<2)x=2;if(x+w>628)x=628-w;if(ny>459)ny=459;if(ny<2)ny=2;pb_fill(x,ny,w,16,0x70000000);ui_light(x+5,ny+1,ns,name);
}
