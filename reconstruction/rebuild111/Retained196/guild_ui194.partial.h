typedef struct{
 unsigned page,row,project,decor;
}GuildUI194;

static GuildUI194 guildUI194;
static int(*guildVisit194)(Combat*);

static int guild_near194(const Combat*g){
 return guild_open194(questPins65)&&g->hp>0&&(
  (
   g->mapId==132&&
   combat_dist(g->x,g->y,188,1116)<22&&
   (!g->canMove||
    g->canMove(g->world,g->x,g->y,188,1116))
  )||
  (
   g->mapId==GUILD_MAP194&&
   combat_dist(g->x,g->y,128,1444)<24&&
   (!g->canMove||
    g->canMove(g->world,g->x,g->y,128,1444))
  )
 );
}

static void guild_ui_open194(Combat*g){
 memset(&guildUI194,0,sizeof(guildUI194));
 g->utilityMenu=504;
 g->autoAttack=g->floorGather60=g->approachSkill53=0;
 g->route53.state=0;
}

static void guild_arcade_result194(Combat*g){
 if(!arcade194.over||arcade194.submitted)return;

 unsigned score=arcade194.game==AR194_PUZZLE?
  (arcade194.won?10000/(arcade194.score+1):0):
  arcade194.score;

 if(guild_score194(questPins65,arcade194.game,score))
  arcade194.submitted=1;
 else
  combat_message(
   g,"Your cabinet score could not be saved. Please retry.");
}

static void guild_ui_input194(
 Combat*g,unsigned pressed,unsigned held,float dt
){
 GuildUI194*u=&guildUI194;
 Guild194 hall;

 if(guild_load194(questPins65,&hall)<0||
    !guild_open194(questPins65)){
  g->utilityMenu=0;
  combat_message(g,"Guild record could not be read.");
  return;
 }

 if(g->utilityMenu==505){
  guild_arcade_result194(g);

  if(pressed&4){
   g->utilityMenu=504;
   u->page=3;
   u->row=arcade194.game;
   return;
  }

  if(arcade194.over&&(pressed&2))
   guild_arcade_result194(g);

  arcade_input194(&arcade194,pressed);
  arcade_tick194(&arcade194,held,dt);
  guild_arcade_result194(g);
  return;
 }

 if(pressed&4){
  if(u->page==0)g->utilityMenu=0;
  else{
   u->row=u->page==1?u->project:
          u->page==2?12:
          u->page==3?13:14;
   u->page=0;
  }
  return;
 }

 if(u->page==0){
  if(pressed&1024)u->row=(u->row+15)%16;
  else if(pressed&2048)u->row=(u->row+1)%16;
  else if(pressed&2){
   if(u->row<12){
    u->project=u->row;
    u->page=1;
   }else if(u->row==12){
    u->page=2;
    u->decor=hall.decor;
   }else if(u->row==13){
    u->page=3;
    u->row=0;
   }else if(u->row==14){
    u->page=4;
    u->row=0;
   }else if(guildVisit194&&guildVisit194(g)){
    g->utilityMenu=0;
   }else{
    combat_message(g,"The guild entrance could not be reached.");
   }
  }
 }else if(u->page==1&&(pressed&2)){
  unsigned id=u->project;

  if(hall.built&(1u<<id)){
   combat_message(g,"This improvement is already finished.");
   return;
  }

  if(!(hall.accepted&(1u<<id))){
   if(guild_accept194(questPins65,id))
    combat_message(
     g,"Guild project added to Side Quests. Bring the materials here.");
   else
    combat_message(
     g,"Complete the listed story milestone and earlier improvements first.");
  }else if(guild_build194(questPins65,g,id)){
   combat_message(
    g,"Guild improvement complete. Thank you for making room for us.");
  }else{
   combat_message(
    g,"Keep the required materials in your bag. Nothing was spent.");
  }
 }else if(u->page==2){
  if(pressed&4096)u->decor=(u->decor+3)%4;
  else if(pressed&8192)u->decor=(u->decor+1)%4;
  else if(pressed&2){
   if(guild_decor194(questPins65,u->decor)){
    combat_message(g,"Guild furnishings saved.");
    u->page=0;
    u->row=12;
   }else{
    combat_message(
     g,"Build the common room and the matching facilities first.");
   }
  }
 }else if(u->page==3){
  if(pressed&1024)u->row=(u->row+5)%6;
  else if(pressed&2048)u->row=(u->row+1)%6;
  else if(pressed&2){
   if(!(hall.built&(1u<<(6+u->row)))){
    u->project=6+u->row;
    u->page=1;
    return;
   }

   arcade_reset194(
    &arcade194,u->row,(unsigned)(g->time*1000)+u->row+1);

   g->utilityMenu=505;
  }
 }else if(u->page==4){
  if(pressed&1024)u->row=(u->row+18)%19;
  else if(pressed&2048)u->row=(u->row+1)%19;
  else if(pressed&2){
   Campaign200 c;

   if(campaign_load200(questPins65,&c)!=1){
    combat_message(g,"The guild roster could not be read.");
    return;
   }

   if(c.recruits&(1u<<u->row))
    combat_message(
     g,"Already a member. Choose your active group in Companions.");
   else if(guild_invite194(questPins65,u->row))
    combat_message(
     g,"Invitation accepted. Choose your active group in Companions.");
   else
    combat_message(
     g,"Meet this ally in the story first. No invitation was sent.");
  }
 }
}
