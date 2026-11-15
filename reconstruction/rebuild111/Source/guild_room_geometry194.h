/* Exact deployed base map, retained room rules and original-floor ownership.
 * No synthetic replacement geometry. Original native map 451 remains untouched. */
#ifndef MYRO_GUILD_ROOM_GEOMETRY194_H
#define MYRO_GUILD_ROOM_GEOMETRY194_H
#include "guild_layout194.h"
#include "guild_props197.h"
static unsigned(*guildRoomCompleted194)(void);
static unsigned(*guildRoomStyle194)(void);
static unsigned guildRoomLoadedMask194,guildRoomLoadedStyle194;
static unsigned char*guildOriginalFloor197;static unsigned guildOriginalCells197;
static void guild_floor_release197(void){free(guildOriginalFloor197);guildOriginalFloor197=NULL;guildOriginalCells197=0;}
static void guild_floor_capture197(void){guild_floor_release197();guildOriginalCells197=gw*gh;if(!guildOriginalCells197||guildOriginalCells197>512*512)fail("Guild floor dimensions invalid");guildOriginalFloor197=calloc((guildOriginalCells197+7)/8,1);if(!guildOriginalFloor197)fail("Guild original floor allocation failed");for(unsigned i=0;i<guildOriginalCells197;i++)if(walk[i])guildOriginalFloor197[i>>3]|=(unsigned char)(1u<<(i&7));spawnx=192;spawny=1408;}
/* Called only AFTER room ownership is built from the complete original floor. */
static void guild_floor_apply197(void){if(!guildOriginalFloor197||guildOriginalCells197!=gw*gh)fail("Guild original floor unavailable");guildRoomLoadedMask194=guildRoomCompleted194?guildRoomCompleted194():0;guildRoomLoadedStyle194=guildRoomStyle194?guildRoomStyle194():0;
 for(unsigned i=0;i<guildOriginalCells197;i++){unsigned x=i%gw,y=i/gw;walk[i]=(unsigned char)(((guildOriginalFloor197[i>>3]>>(i&7))&1)&&guild_room_ready194(guildRoomLoadedMask194,x*8+4,y*8+4));}
 if(!(guildRoomLoadedMask194&16))for(unsigned x=8;x<40;x++)walk[75*gw+x]=0;
 guild_props_build197(guildRoomLoadedMask194,guildRoomLoadedStyle194);guild_props_collision197();
}
#endif
