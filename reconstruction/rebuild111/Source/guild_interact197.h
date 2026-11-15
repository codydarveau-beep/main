/* Physical cabinet controls; included after the actual guild UI. */
#ifndef MYRO_GUILD_INTERACT197_H
#define MYRO_GUILD_INTERACT197_H
static int guild_world_interact197(Combat*g){int near=guild_world_near197(g);if(near<0)return 0;if(near>=100){guild_ui_open194(g);if(g->utilityMenu!=504){memset(&guildUI194,0,sizeof guildUI194);g->utilityMenu=504;g->autoAttack=g->floorGather60=g->approachSkill53=0;g->route53.state=0;}guildUI194.cabinet=(unsigned)near-100;guildUI194.page=4;guild_arcade_start196(g,guildUI194.cabinet);return 1;}
 const GuildDoor194*d=guildDoors194+near;if(d->any&&!(guild_world_completed194()&d->any)){combat_message(g,"Finish the matching guild improvement before opening this room.");return 1;}
 if(!world_script_warp55(NULL,g,d->map,d->toX,d->toY,0,1))combat_message(g,"The guild doorway could not be reached. Nothing was spent.");return 1;
}
#endif
