#include <assert.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include "combat.h"
#include "quest_journal65.h"
#include "font_metrics65.h"
#include "controller_tokens64.h"
#include "../Validation/actual_wrap194.inc"
static unsigned draws;
static void pb_fill(int x,int y,int w,int h,unsigned c){(void)c;assert(x>=0&&y>=0&&w>=0&&h>=0&&x+w<=640&&y+h<=480);draws++;}
static void ui_panel(int x,int y,int w,int h,const char*t,int f,int c){(void)t;(void)f;(void)c;pb_fill(x,y,w,h,0);}
static void ui_cell(int x,int y,int w,int h,int selected){(void)selected;pb_fill(x,y,w,h,0);}
static void ui_scaled(int x,int y,float scale,const char*format,...){char s[160];va_list ap;va_start(ap,format);vsnprintf(s,sizeof(s),format,ap);va_end(ap);assert(x>=0&&y>=0&&x+ui_text_width(s,scale)<=640&&y+11<=480);draws++;}
static void ui_hint64(int x,int y,float scale,const char*format,...){char s[160];va_list ap;va_start(ap,format);vsnprintf(s,sizeof(s),format,ap);va_end(ap);ui_scaled(x,y,scale,"%s",s);}
static void ui_fit47(int x,int y,int width,float scale,const char*s){(void)scale;(void)s;assert(x>=0&&y>=0&&x+width<=640&&y+11<=480);draws++;}
#include "guild_ui194.h"
static int warpFailure;
static int world_script_warp55(void*ctx,Combat*g,unsigned map,float x,float y,int random,int clean){(void)ctx;(void)random;(void)clean;if(warpFailure)return 0;g->mapId=map;g->x=x;g->y=y;return 1;}
#include "regional_world194.h"
static Combat game,before;
static NpcState55 state,logState;
static void compact(const char*from,char*out){while(*from){if(!isspace((unsigned char)*from))*out++=*from;from++;}*out=0;}
int main(void){
 combat_init(&game,188,1116,NULL,NULL);game.zeny=20000;game.level=99;game.mapId=132;
 Campaign200 story={0};story.cursor=36;story.route=1;story.lineage=1;strcpy(story.guild,"Recovery");assert(campaign_store200(&state,&story));quest_journal_bind65(&logState,&state);questPlayer194=&game;
 Guild194 guild={4095,4095,0,{0}};assert(guild_store194(&state,&guild));assert(npc_state_set_number55(&logState,1014,0,1));
 unsigned mask=(1u<<0)|(1u<<1)|(1u<<2)|(1u<<7)|(1u<<8)|(1u<<10)|(1u<<11)|(1u<<12)|(1u<<13);CampaignRegions194 regions={mask,mask,mask};assert(campaign_regions_store194(&state,&regions));
 assert(quest_count65()==23);for(unsigned i=0;i<quest_count65();i++)for(unsigned j=0;j<i;j++)assert(quest_at65(i)!=quest_at65(j));
 uint32_t winter=REGIONAL_QUEST194;assert(!quest_tracked65(winter));assert(quest_toggle65(winter)&&quest_tracked65(winter));assert(quest_toggle65(winter)&&!quest_tracked65(winter));
 regions.unlocked&=~1u;regions.completed&=~1u;assert(campaign_regions_store194(&state,&regions));assert(owned_add52(&game.owned52,0,1019,5,item_rule52)==OWNED_OK52);
 uint64_t done,total;assert(quest_progress65(winter,&done,&total)&&done==5&&total==20);
 guild_ui_open194(&game);assert(game.utilityMenu==504);
 for(unsigned row=0;row<17;row++){guildUI194.row=row;guild_ui_draw194(&game);}
 guildUI194.row=16;guild_ui_input194(&game,2,16);assert(guildUI194.page==5);guild_ui_draw194(&game);
 for(unsigned i=0;i<9;i++){
  guildUI194.row=i;guild_ui_draw194(&game);guild_ui_input194(&game,2,16);assert(guildUI194.page==6&&guildUI194.journey==i);guild_ui_draw194(&game);
  guild_ui_input194(&game,4,16);assert(guildUI194.page==5&&guildUI194.row==i);
  char lines[24][96],joined[2304]={0},a[2304],b[2304];int n=regional_ui_lines194(regionalJourneys194[i].letter,lines);assert(n>0&&n<=14);
  for(int j=0;j<n;j++){assert(ui_text_width(lines[j],1)<=454);strcat(joined,lines[j]);}
  compact(joined,a);compact(regionalJourneys194[i].letter,b);assert(!strcmp(a,b));
  guildUI194.page=7;guildUI194.journey=i;guild_ui_draw194(&game);guildUI194.page=5;
 }
 guild_ui_input194(&game,4,16);assert(guildUI194.page==0&&guildUI194.row==16);
 regionalVisit194=regional_world_visit194;regionalReturn194=regional_world_return194;
 regions.unlocked|=1u;regions.completed&=~1u;assert(campaign_regions_store194(&state,&regions));
 before=game;warpFailure=1;unsigned revision=state.revision;assert(!regional_world_visit194(&game,0)&&!memcmp(&game,&before,sizeof(game))&&state.revision==revision);warpFailure=0;
 assert(regional_world_visit194(&game,0)&&game.zeny==19000&&game.mapId==386);
 game.x=regionalJourneys194[0].noteX;game.y=regionalJourneys194[0].noteY;regional_ui_open194(&game,0);guild_ui_input194(&game,2,16);assert(quest_custom_completed194(winter));
 guild_ui_input194(&game,8,16);assert(!game.utilityMenu&&game.mapId==132&&game.zeny==19000);
 for(unsigned cabinet=0;cabinet<6;cabinet++){
  guildUI194.page=3;guildUI194.row=cabinet;guild_ui_input194(&game,2,16);assert(guildUI194.page==4);
  for(unsigned i=0;i<4000;i++){
   unsigned buttons=(i%4==0?8192:i%4==1?2048:i%4==2?4096:1024)|(i%3==0?2:0);
   guild_ui_input194(&game,buttons,120);if(i%100==0)guild_ui_draw194(&game);
   assert(guildUI194.arcade.length<=ARCADE_CELLS194&&guildUI194.arcade.kind<6);
  }
  guild_ui_input194(&game,4,16);assert(guildUI194.page==3);
 }
 npc_state_clear55(&state);npc_state_clear55(&logState);
 printf("PASS HOST: 17-row guild navigation, nine dispatch pages, exact letter paragraph preservation at actual font metrics, journal counters/tracking, failed-fare preservation, completed free return, six bounded cabinet simulations and %u recorded layout operations; no GPU/Xbox playtest\n",draws);
}
