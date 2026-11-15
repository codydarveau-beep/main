/* MIT. Distinct guild interior. Native quest rooms and pack offsets are untouched. */
#ifndef MYRO_GUILD_WORLD194_H
#define MYRO_GUILD_WORLD194_H
static unsigned guild_world_completed194(void){Guild194 g;return guild_load194(questPins65,&g)>=0?g.completed:0;}
static unsigned guild_world_style194(void){Guild194 g;return guild_load194(questPins65,&g)>=0?g.style:0;}
static int guild_world_visit194(Combat*g){
 if(!guild_open194(questPins65)||!guild_near194(g))return 0;
 if(g->mapId==494)return world_script_warp55(NULL,g,132,188,1116,0,1);
 if(!(guild_world_completed194()&1))return 0;
 return world_script_warp55(NULL,g,494,192,1408,0,1);
}
/* Retained physical door/cabinet positions; no fee or character-state shortcut. */
static int guild_world_near197(const Combat*g){if(!g||g->mapId!=GUILD_MAP194||g->hp<=0)return-1;float distance=24;int best=-1;
 for(unsigned i=0;i<sizeof(guildDoors194)/sizeof(*guildDoors194);i++){const GuildDoor194*d=guildDoors194+i;float n=combat_dist(g->x,g->y,d->x,d->y);if(n<distance){distance=n;best=(int)i;}}
 unsigned mask=guild_world_completed194();if(mask&32)for(unsigned i=0;i<6;i++)if(mask&(1u<<(6+i))){float n=combat_dist(g->x,g->y,1332,464+i*88);if(n<distance){distance=n;best=100+(int)i;}}return best;
}
static const char*guild_world_context197(const Combat*g){int near=guild_world_near197(g);if(near<0)return "";static char text[96];if(near>=100)snprintf(text,sizeof text,"A: play %s",guildProjects194[6+near-100].title);else snprintf(text,sizeof text,"A: %s",guildDoors194[near].label);return text;}
#endif
