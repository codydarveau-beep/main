/* MIT. Reconstructed controller guild board and retained regional page contract. */
#ifndef MYRO_GUILD_UI194_H
#define MYRO_GUILD_UI194_H
#include "regional194.h"
#include "guild_arcade194.h"
#include "campaign_companions200.h"
typedef char GuildArcadeBudget194[sizeof(GuildArcade194)<=2048?1:-1];
typedef struct{unsigned page,row,project,journey,cabinet;GuildArcade194 arcade;}GuildUI194;
static GuildUI194 guildUI194;
static int(*regionalVisit194)(Combat*,unsigned);
static int(*regionalReturn194)(Combat*,unsigned);
static int(*guildVisit194)(Combat*);
static const char*guild_item_name194(unsigned source){int i=inventory_catalog52(source);return i>=0?itemDefs[i].name:"Supplies";}
static void guild_ui_open194(Combat*g){
 if(!guild_open194(questPins65)||!guild_near194(g))return;
 memset(&guildUI194,0,sizeof(guildUI194));g->utilityMenu=504;g->autoAttack=g->floorGather60=g->approachSkill53=0;g->route53.state=0;
}
static void regional_ui_open194(Combat*g,unsigned journey){
 if(journey>=REGIONAL_COUNT194)return;memset(&guildUI194,0,sizeof(guildUI194));guildUI194.page=7;guildUI194.journey=journey;
 g->utilityMenu=504;g->autoAttack=g->floorGather60=g->approachSkill53=0;g->route53.state=0;
}
static int regional_ui_lines194(const char*text,char lines[24][96]){
 int count=0;while(*text&&count<14){const char*end=strchr(text,'\n');size_t length=end?(size_t)(end-text):strlen(text);char paragraph[768];
  if(length>=sizeof paragraph)length=sizeof paragraph-1;memcpy(paragraph,text,length);paragraph[length]=0;
  if(length){char wrapped[8][96];int rows=ui_wrap(paragraph,wrapped,454,1);for(int i=0;i<rows&&count<14;i++)memcpy(lines[count++],wrapped[i],96);}
  else lines[count++][0]=0;if(!end)break;text=end+1;
 }return count;
}
static const char*regional_status194(unsigned index){
 CampaignRegions194 r;if(!regional_available194(questPins65,index)||!campaign_regions_load194(questPins65,&r))return "Later";
 unsigned bit=regional_bit194(index);return r.completed&bit?"Received":r.unlocked&bit?"Passage":r.accepted&bit?"Supplies":"Open";
}
static int guild_arcade_save194(Combat*g){Arcade194*a=&guildUI194.arcade;if(!a->over||a->submitted)return 1;unsigned score=a->game==AR194_PUZZLE?(a->won?10000/(a->score+1):0):a->score;if(guild_score194(questPins65,a->game,score)){a->submitted=1;return 1;}combat_message(g,"Your cabinet score could not be saved. Please retry.");return 0;}
static void guild_arcade_start196(Combat*g,unsigned kind){arcade_start_seed196(&guildUI194.arcade,kind,(unsigned)(g->time*1000)+kind+1);}
static void guild_ui_input_held197(Combat*g,unsigned pressed,unsigned held,float dt){
 GuildUI194*u=&guildUI194;Guild194 guild;CampaignRegions194 regions;
 if(!guild_open194(questPins65)||guild_load194(questPins65,&guild)<0||!campaign_regions_load194(questPins65,&regions)){combat_message(g,"Guild record could not be read.");g->utilityMenu=0;return;}
 if(u->page==4){
  if(pressed&4){if(guild_arcade_save194(g)){u->page=3;u->row=u->cabinet;}return;}
  if(u->arcade.over&&(pressed&2)&&!guild_arcade_save194(g))return;
  arcade_input194(&u->arcade,pressed);arcade_tick_held197(&u->arcade,held,dt);if(u->arcade.over&&!u->arcade.submitted)guild_arcade_save194(g);return;
 }
 if(pressed&4){
  if(u->page==7||u->page==0)g->utilityMenu=0;
  else if(u->page==6){u->page=5;u->row=u->journey;}
  else if(u->page==5){u->page=0;u->row=16;}
  else{unsigned row=u->page==1?u->project:u->page==2?12:u->page==8?14:13;u->page=0;u->row=row;}return;
 }
 unsigned count=u->page==0?17:u->page==2?4:u->page==3?6:u->page==5?9:u->page==8?19:0;
 if(count){if(pressed&1024)u->row=(u->row+count-1)%count;else if(pressed&2048)u->row=(u->row+1)%count;}
 if(u->page==7){
  if((pressed&8)&&regionalReturn194){if(regionalReturn194(g,u->journey))g->utilityMenu=0;else combat_message(g,"The return passage could not be completed. No fee was charged.");}
  else if(pressed&2){if(regional_collect194(questPins65,g,u->journey))combat_message(g,"Courier parcel received.");else combat_message(g,"Check your bag capacity, or whether this parcel was already received.");}return;
 }
 if(!(pressed&2))return;
 if(u->page==0){
  if(u->row<12){u->project=u->row;u->page=1;}
  else if(u->row==12){u->page=2;u->row=guild.style;}
  else if(u->row==13){u->page=3;u->row=0;}
  else if(u->row==14){u->page=8;u->row=0;}
  else if(u->row==15){if(guildVisit194&&guildVisit194(g))g->utilityMenu=0;else combat_message(g,"The guild doorway could not be opened.");}
  else{u->page=5;u->row=0;}return;
 }
 if(u->page==1){unsigned bit=1u<<u->project;
  int ok=!(guild.accepted&bit)?guild_accept194(questPins65,u->project):guild_deliver194(questPins65,g,u->project);
  combat_message(g,ok?"Guild project progress saved.":"Check the story milestone, earlier facilities and required supplies.");return;
 }
 if(u->page==2){combat_message(g,guild_style194(questPins65,u->row)?"Guild furnishings saved.":"Finish the matching common-room improvement first.");return;}
 if(u->page==3){if(!(guild.completed&(1u<<(u->row+6)))){combat_message(g,"Finish the matching guild improvement at the noticeboard first.");return;}
  u->cabinet=u->row;u->page=4;guild_arcade_start196(g,u->cabinet);return;
 }
 if(u->page==8){Campaign200 c;if(campaign_load200(questPins65,&c)!=1){combat_message(g,"The guild roster could not be read.");return;}unsigned bit=1u<<u->row;
  combat_message(g,(c.recruits&bit)?"Already a member. Choose your active group in Companions.":guild_invite194(questPins65,u->row)?"Invitation accepted. Choose your active group in Companions.":"Meet this ally in the story first. No invitation was sent.");return;}
 if(u->page==5){u->journey=u->row;u->page=6;return;}
 if(u->page==6){unsigned index=u->journey,bit=regional_bit194(index);int ok=0;
  if(!(regions.accepted&bit))ok=regional_accept194(questPins65,index);
  else if(!(regions.unlocked&bit))ok=regional_deliver194(questPins65,g,index);
  else if(regionalVisit194){ok=regionalVisit194(g,index);if(ok)g->utilityMenu=0;}
  if(!ok)combat_message(g,"Check the milestone, supplies, fare and destination before travelling.");
 }
}
static void guild_ui_input194(Combat*g,unsigned pressed,unsigned milliseconds){guild_ui_input_held197(g,pressed,pressed,milliseconds/1000.f);}
static void arcade_poring194(
 int x,int y,int size,unsigned color
){
 for(int r=0;r<size;r++){
  float v=(r-size*.5f)/(size*.5f);
  int w=(int)(sqrtf(fmaxf(0,1-v*v))*size*.5f);
  if(w)pb_fill(x+size/2-w,y+r,w*2,1,color);
 }

 if(size>=8){
  pb_fill(x+size/3,y+size/2,1,2,0xff000000);
  pb_fill(x+size*2/3,y+size/2,1,2,0xff000000);
  pb_fill(x+size/2,y+size*2/3,2,1,0xff000000);
 }
}

static void arcade_draw194(void){
 const Arcade194*a=&guildUI194.arcade;

 ui_panel(68,46,504,390,arcade_names194[a->game],1,-1);
 pb_fill(84,105,472,286,0xff101711);

 ui_scaled(
  88,77,1,"Score %u    Lives %u    Round %u",
  a->score,a->lives,a->level);

 int x=100,y=116,w=440,h=264;

 if(a->game==AR194_PONG){
  for(int k=0;k<15;k++)
   pb_fill(x+w/2,y+k*18,2,8,0xff5b7568);

  pb_fill(x+20,y+(int)(a->paddle*h)-27,6,54,0xff6aabef);
  pb_fill(x+w-26,y+(int)(a->opponent*h)-27,6,54,0xff60d27a);

  arcade_poring194(
   x+(int)(a->x*w)-5,y+(int)(a->y*h)-5,10,0xffedbfd1);
 }
 else if(a->game==AR194_PATROL){
  for(unsigned i=0;i<36;i++)if(a->board[i]){
   int ex=x+(int)(
    (.12f+i%9*.09f+sinf(a->time*.8f)*.04f)*w);
   int ey=y+(int)((.12f+i/9*.085f)*h);

   pb_fill(ex-6,ey-4,12,8,0xffffdf56);
   pb_fill(ex-8,ey+2,3,5,0xffbd8c3e);
   pb_fill(ex+5,ey+2,3,5,0xffbd8c3e);
   pb_fill(ex+2,ey-2,2,2,0xff000000);
  }

  arcade_poring194(
   x+(int)(a->x*w)-7,y+(int)(h*.89f),14,0xffedbfd1);

  for(unsigned i=0;i<24;i++)if(a->shots[i].on)
   pb_fill(
    x+(int)(a->shots[i].x*w),
    y+(int)(a->shots[i].y*h),
    2,5,
    a->shots[i].vy<0?0xff65dffa:0xffff4848);
 }
 else if(a->game==AR194_SNAKE||a->game==AR194_MAZE){
  const int cell=15,gx=148,gy=116;

  if(a->game==AR194_SNAKE){
   for(unsigned i=0;i<a->length;i++)
    pb_fill(
     gx+a->snake[i]%23*cell+1,
     gy+a->snake[i]/23*cell+1,
     13,13,i?0xff60d27a:0xffedbfd1);

   pb_fill(
    gx+a->food%23*cell+4,
    gy+a->food/23*cell+4,
    7,7,0xffff4848);
  }else{
   for(unsigned i=0;i<AR194_CELLS;i++){
    int xx=gx+i%23*cell,yy=gy+i/23*cell;

    if(!a->board[i])
     pb_fill(xx,yy,14,14,0xff6aabef);
    else if(a->board[i]<3)
     pb_fill(
      xx+(a->board[i]==2?5:6),
      yy+(a->board[i]==2?5:6),
      a->board[i]==2?5:2,
      a->board[i]==2?5:2,
      0xffffdf56);
   }

   arcade_poring194(
    gx+a->food%23*cell+1,
    gy+a->food/23*cell+1,
    13,0xffedbfd1);

   for(unsigned i=0;i<4;i++)
    arcade_poring194(
     gx+a->ghosts[i]%23*cell+2,
     gy+a->ghosts[i]/23*cell+2,
     11,
     a->powerUntil>a->time?0xff8999b2:
      (unsigned[]){
       0xffff4848,0xff65dffa,0xffffdf56,0xff60d27a
      }[i]);
  }
 }
 else if(a->game==AR194_BREAKER){
  for(unsigned i=0;i<60;i++)if(a->board[i]){
   int xx=x+i%10*44,yy=y+26+i/10*13;
   pb_fill(xx+1,yy,41,11,i/10%2?0xff60d27a:0xffbd8c3e);
  }

  pb_fill(
   x+(int)(a->paddle*w)-44,
   y+(int)(h*.92f),
   88,6,0xff6aabef);

  arcade_poring194(
   x+(int)(a->x*w)-5,y+(int)(a->y*h)-5,10,0xffedbfd1);
 }
 else if(a->game==AR194_PUZZLE){
  for(unsigned i=0;i<16;i++){
   int xx=182+i%4*70,yy=112+i/4*66;

   pb_fill(
    xx,yy,66,62,
    a->tiles[i]?0xffdbe3ed:0xff27392b);

   if(i==a->cursor)
    ui_outline(xx-1,yy-1,68,64,0xffffdf56);

   if(a->tiles[i]){
    arcade_poring194(xx+21,yy+8,24,0xffedbfd1);

    char n[8];
    snprintf(n,sizeof(n),"%u",a->tiles[i]);

    ui_scaled(
     xx+31-ui_text_width(n,1)/2,yy+39,1,"%s",n);
   }
  }
 }

 if(a->paused||a->over){
  pb_fill(176,204,288,84,0xffeaf0f5);
  ui_outline(176,204,288,84,0xff6aabef);

  ui_scaled(
   196,218,1,"%s",
   a->paused?"Resting the Poring...":
   a->won?"A splendid result!":
          "Another biscuit, another try.");

  ui_hint64(
   196,253,.9f,
   a->paused?"Y: resume   B: leave":
             "A: play again   B: leave");
 }

 const char*help=
  a->game==AR194_PONG?
   "UP/DOWN: paddle":
  a->game==AR194_PATROL?
   "LEFT/RIGHT: move   A: fire":
  a->game==AR194_BREAKER?
   "LEFT/RIGHT: paddle   A: launch":
  a->game==AR194_PUZZLE?
   "D-PAD: choose   A: slide":
   "D-PAD: move";

 ui_hint64(
  88,400,.85f,"%s   Y: pause   B: leave",help);
}

static void guild_arcade_draw194(void){arcade_draw194();}
static void guild_ui_draw194(const Combat*g){
 GuildUI194*u=&guildUI194;Guild194 guild;CampaignRegions194 regions;
 if(guild_load194(questPins65,&guild)<0||!campaign_regions_load194(questPins65,&regions))return;
 if(u->page==4){guild_arcade_draw194();return;}
 const char*title=u->page==5?"Regional journeys":u->page==6?regionalJourneys194[u->journey].title:u->page==7?"Courier notice":"Guild noticeboard";
 ui_panel(72,70,496,350,title,1,-1);
 if(u->page==7){char lines[24][96];int count=regional_ui_lines194(regionalJourneys194[u->journey].letter,lines);for(int i=0;i<count;i++)ui_scaled(94,110+i*16,1,"%s",lines[i]);
  ui_hint64(94,392,.85f,"A: claim parcel   X: free return   B: close");return;}
 if(u->page==1||u->page==6){
  unsigned index=u->page==1?u->project:u->journey;const char*pitch=u->page==1?guildProjects194[index].pitch:regionalJourneys194[index].pitch;
  char lines[8][96];int n=ui_wrap(pitch,lines,454,1);for(int i=0;i<n;i++)ui_scaled(94,110+i*16,1,"%s",lines[i]);
  const unsigned*items=u->page==1?guildProjects194[index].item:regionalJourneys194[index].item;
  const unsigned*amounts=u->page==1?guildProjects194[index].amount:regionalJourneys194[index].amount;
  for(unsigned k=0;k<2;k++)ui_scaled(94,282+k*22,1,"%u/%u %s",guild_material_count194(g,items[k]),amounts[k],guild_item_name194(items[k]));
  if(u->page==6)ui_scaled(94,336,1,"Courier fare: %u Zeny",regionalJourneys194[index].fare);
  ui_hint64(94,392,.85f,u->page==6?"A: accept / deliver / travel   B: journeys":"A: accept / deliver   B: noticeboard");return;
 }
 unsigned count=u->page==0?17:u->page==2?4:u->page==3?6:u->page==8?19:9,first=u->row/7*7;
 static const char*styles[]={"Plain and practical","Cosy common room","Reading room","Workshop"};
 for(unsigned row=first;row<count&&row<first+7;row++){
  const char*label="";char line[192];
  if(u->page==0){static const char*extra[]={"Arrange furnishings","Play arcade cabinets","Invite an introduced ally","Visit the guild hall","Regional journeys"};label=row<12?guildProjects194[row].title:(row==15&&g->mapId==494)?"Return to Alberta":extra[row-12];}
  else if(u->page==8){Campaign200 c;if(campaign_load200(questPins65,&c)!=1)return;label=(guild_met_mask194(c.cursor)&(1u<<row))?campaignCompanions200[row].name:"Not yet introduced";}
  else if(u->page==2)label=styles[row];
  else if(u->page==3){snprintf(line,sizeof(line),"%s   Best: %u",guildProjects194[row+6].title,guild.scores[row]);label=line;}
  else{snprintf(line,sizeof(line),"%s   %s",regionalJourneys194[row].title,regional_status194(row));label=line;}
  int y=108+(int)(row-first)*36;ui_cell(84,y-3,472,31,row==u->row);ui_fit47(94,y,452,1,label);
 }
 ui_hint64(94,392,.85f,"UP/DOWN: select   A: open   B: back");
}
#endif
