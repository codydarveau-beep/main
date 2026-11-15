/* MIT. Distinct guild interior. Native quest rooms and pack offsets are untouched. */
#ifndef MYRO_GUILD_WORLD194_H
#define MYRO_GUILD_WORLD194_H
static unsigned guild_world_completed194(void){Guild194 g;return guild_load194(questPins65,&g)>=0?g.completed:0;}
static unsigned guild_world_style194(void){Guild194 g;return guild_load194(questPins65,&g)>=0?g.style:0;}
static int guild_world_visit194(Combat*g){
 if(!guild_open194(questPins65)||!guild_near194(g))return 0;
 if(g->mapId==494)return world_script_warp55(NULL,g,132,188,1116,0,1);
 if(!(guild_world_completed194()&1))return 0;
 return world_script_warp55(NULL,g,494,800,1440,0,1);
}
#endif
