/* MIT. Window and fixed unboxed quest tracker. All current original quests are side quests. */
static void ui_quest_bar65(int x,int y,int width,uint32_t id){uint64_t done,total;if(!quest_progress65(id,&done,&total))return;pb_fill(x,y,width,5,0xff000000);pb_fill(x+1,y+1,width-2,3,0xffeaf0f5);int fill=(int)(done*(width-2)/total);if(fill)pb_fill(x+1,y+1,fill,3,0xffedbfd1);}
static void ui_quest_window65(WindowUI*u,int focus,int inside){int x=windowX[UI_QUESTS],y=windowY[UI_QUESTS],count=quest_count65(),choice=u->choice[UI_QUESTS];ui_panel(x,y,160,110,"Quests",focus,inside&&choice==-1);if(choice>=count)choice=count?count-1:-1;u->choice[UI_QUESTS]=choice;int first=choice<0?0:choice/3*3;for(int i=first;i<count&&i<first+3;i++){uint32_t id=quest_at65(i);int yy=y+22+(i-first)*24;ui_cell(x+4,yy-1,152,23,inside&&choice==i);pb_fill(x+7,yy+4,7,7,quest_tracked65(id)?0xff6aabef:0xffeaf0f5);ui_fit47(x+19,yy,133,.85f,quest_title65(id));ui_quest_bar65(x+19,yy+15,131,id);}if(!count)ui_scaled(x+8,y+25,.85f,"No recorded quests.");ui_hint64(x+8,y+95,.75f,"A: details | X: track");}
static void ui_quest_tracker65(const WindowUI*u){
 if(!alwaysShowQuests65||(u->open&(1u<<UI_QUESTS)))return;
 int y=126;unsigned shown=0;
 for(unsigned i=0;i<quest_count65()&&shown<3;i++){
  uint32_t id=quest_at65(i);if(!quest_tracked65(id))continue;
  const int textX=39;char title[160],lines[8][96];
  if(id==CAMPAIGN_QUEST200)ui_weight61(textX,y,.9f,"MAIN QUEST",3);else ui_light(textX,y,.9f,"SIDE QUEST");
  /* A fixed mark gutter never shifts titles or objectives. */
  int mark269=quest_mark269(id);if(mark269==1){pb_fill(25,y+6,3,3,0xff60d27a);pb_fill(28,y+3,3,6,0xff60d27a);}else if(mark269==2){for(int k269=0;k269<7;k269++){pb_fill(25+k269,y+3+k269,1,1,0xffff4848);pb_fill(31-k269,y+3+k269,1,1,0xffff4848);}}y+=15;
  snprintf(title,sizeof(title),"%s",quest_title65(id));while(*title&&ui_text_width(title,1)>228)title[strlen(title)-1]=0;
  ui_light(textX,y,1,title);ui_light(textX+1,y,1,title);y+=16;
  int n=ui_wrap(quest_summary257(id),lines,228,1);if(n>3){n=3;size_t len=strlen(lines[2]);while(len&&ui_text_width(lines[2],1)+ui_text_width("...",1)>228)lines[2][--len]=0;strcat(lines[2],"...");}
  for(int line=0;line<n;line++){ui_light(textX,y,1,lines[line]);y+=15;}
  uint64_t done,total;if(quest_progress65(id,&done,&total)){ui_quest_bar65(textX,y,160,id);y+=8;}y+=8;shown++;
 }
}
/* Inspection is modal and read-only apart from the explicit tracking button. */
static void ui_quest_info257(WindowUI*u){if(!u->questInfo257)return;static char text[8192];quest_details257(u->questInfoID257,text,sizeof(text));ui_panel(86,68,468,348,"Quest details",0,-1);unsigned lines=npc_text_icons64(text,440,0,0,ui_skill_info_width55,NULL,NULL),maximum=lines>18?lines-18:0;if((unsigned)u->questInfoScroll257>maximum)u->questInfoScroll257=(int)maximum;npc_text_icons64(text,440,(unsigned)u->questInfoScroll257,18,ui_skill_info_width55,ui_skill_info_glyph55,NULL);ui_hint64(100,395,.8f,"Up/down: scroll | X: track | B: close");}
