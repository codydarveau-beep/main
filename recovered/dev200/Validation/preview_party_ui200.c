#define TITLE_U200 0
#define TITLE_V200 130
#define TITLE_W200 280
#define TITLE_H200 16
#define MYRO_HOST 1
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include "combat.h"
#include "campaign_battle200.h"
static int px,py,pw,ph,inside;
static void bounds(float x,float y,float w,float h){assert(w>=0&&h>=0&&x>=0&&y>=0&&x+w<=640&&y+h<=480);if(inside)assert(x>=px&&y>=py&&x+w<=px+pw&&y+h<=py+ph);}
static void hud_quad(float x,float y,float w,float h,float u,float v,float uw,float vh){bounds(x,y,w,h);printf("Q %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f\n",x,y,w,h,u,v,uw,vh);}
static void hud_panel(int x,int y,int w,int h){bounds(x,y,w,h);}
static void pb_fill(int x,int y,int w,int h,unsigned color){bounds(x,y,w,h);printf("F %d %d %d %d %u\n",x,y,w,h,color);}
#include "skin_layout.h"
#include "ui_context.h"
static void ui_panel(int x,int y,int w,int h,const char*title,int focus,int close){(void)title;(void)focus;(void)close;inside=0;bounds(x,y,w,h);px=x;py=y;pw=w;ph=h;inside=1;pb_fill(x,y,w,h,0xffffffff);pb_fill(x,y,w,1,0xff8999b2);pb_fill(x+w-1,y,1,h,0xff8999b2);pb_fill(x,y,1,h,0xff8999b2);pb_fill(x,y+h-1,w,1,0xff8999b2);hud_quad(x+1,y+1,w-2,17,TITLE_U200,TITLE_V200,TITLE_W200,TITLE_H200);ui_scaled(x+7,y+1,1,"%s",title);}
static void ui_cell(int x,int y,int w,int h,int selected){bounds(x,y,w,h);if(selected){pb_fill(x,y,w,h,0xffffedaa);pb_fill(x,y,w,1,0xffe5bc30);pb_fill(x,y+h-1,w,1,0xffe5bc30);pb_fill(x,y,1,h,0xffe5bc30);pb_fill(x+w-1,y,1,h,0xffe5bc30);}}
#include "campaign_party_ui200.h"
static Combat g;
int main(int argc,char**argv){NpcState55 state={0};campaignRosterState200=campaignPartyState200=&state;Campaign200 c={0};c.cursor=3;c.route=1;c.lineage=1;c.recruits=18;assert(campaign_store200(&state,&c));party_config_default200(&campaignConfig200,18);combat_init(&g,100,100,NULL,NULL);g.level=25;unsigned ids[]={1,4};campaign_follow_select200(&campaignParty200,18,ids,2);for(unsigned i=0;i<2;i++)assert(party_init_vital200(campaignParty200.members+i,&g));if(argc>1&&argv[1][0]=='1'){campaignPartyUI200.inside=campaignPartyUI200.editing=1;campaignPartyUI200.id=4;campaignPartyUI200.row=1;campaignPartyUI200.draft=2;}campaign_party_draw200(&g,0);npc_state_clear55(&state);}
