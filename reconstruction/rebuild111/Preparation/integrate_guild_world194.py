from pathlib import Path
import re
S=Path(__file__).resolve().parent.parent/'Source'
def append_array(s,name,value):
 pat=r'('+re.escape(name)+r'(?:\[[^]]*\])+\s*=\s*\{)(.*?)(\};)'
 m=re.search(pat,s,re.S);assert m,name
 body=m[2].rstrip().rstrip(',')+','+value
 return s[:m.start()]+m[1]+body+m[3]+s[m.end():]
p=S/'world_data.h';s=p.read_text().replace('#define WORLD_MAP_COUNT 494','#define WORLD_MAP_COUNT 495',1)
for name,value in [('worldBlobs','{{0}}'),('minimapBlobs45','{0}'),('mapLabels','"Guild hall"'),('mapNames','"guild_in194"'),('mapWidths','100'),('mapHeights','100')]:s=append_array(s,name,value)
p.write_text(s)
p=S/'map_limits43.h';s=p.read_text().replace('#define MYRO_MAP_COUNT43 494','#define MYRO_MAP_COUNT43 495',1)
for name in ['mapWidth43','mapHeight43']:s=append_array(s,name,'1600')
p.write_text(s)
p=S/'world_regions51.h';s=append_array(p.read_text(),'peacefulMaps51','1');p.write_text(s)
p=S/'map_loader.h';s=p.read_text().replace('static void load(unsigned map){','#include "guild_room_geometry194.h"\nstatic void load(unsigned map){\n if(map==494){guild_room_load194();return;}',1);p.write_text(s)
p=S/'world_availability44.h';s=p.read_text().replace('static int world_destination_ready44(unsigned id){return','static int world_destination_ready44(unsigned id){if(id==494)return 1;return',1);p.write_text(s)
p=S/'scenery.h';s=p.read_text().replace('static void scenery_load(unsigned id){','static void scenery_load(unsigned id){if(id==494){sceneTexture=sceneMesh=NULL;sceneVertices=sceneH=0;sceneW=2048;memset(&scene,0,sizeof(scene));return;}',1);p.write_text(s)
p=S/'minimap_upload.h';s=p.read_text().replace(' const WorldBlob*b=&minimapBlobs200[surfaceMap];',''' if(surfaceMap==494){if(!minimapTexture200)minimapTexture200=gpu_alloc(256*128*2);memset(minimapTexture200,0,256*128*2);for(unsigned y=0;y<MINIMAP_H200;y++)for(unsigned x=0;x<MINIMAP_W200;x++){unsigned wx=x*gw/MINIMAP_W200,wy=y*gh/MINIMAP_H200;((uint16_t*)minimapTexture200)[y*256+x]=walk[wy*gw+wx]?0xdefb:0x2104;}minimapLoaded200=494;__sync_synchronize();return;}
 const WorldBlob*b=&minimapBlobs200[surfaceMap];''',1);p.write_text(s)
p=S/'guild194.h';s=p.read_text().replace('g->mapId==132&&combat_dist(g->x,g->y,188,1116)<=28','((g->mapId==132&&combat_dist(g->x,g->y,188,1116)<=28)||(g->mapId==494&&combat_dist(g->x,g->y,800,1440)<=28))',1);p.write_text(s)
p=S/'main.c';s=p.read_text().replace('#include "guild_ui194.h"','#include "guild_ui194.h"\n#include "guild_world194.h"',1);s=s.replace('campaign_admission_install194();','campaign_admission_install194();guildVisit194=guild_world_visit194;guildRoomCompleted194=guild_world_completed194;guildRoomStyle194=guild_world_style194;',1)
s=s.replace('questPlayer194=&game;campaign_world_bind200(&game);','questPlayer194=&game;campaign_world_bind200(&game);if(activeMap==494&&(guildRoomLoadedMask194!=guild_world_completed194()||guildRoomLoadedStyle194!=guild_world_style194())){activeMap=~0u;if(world_activate(494)){world_safe(&game.x,&game.y);world_town(&game);}}',1);p.write_text(s)
p=S/'guild_ui194.h';s=p.read_text().replace('label=row<12?guildProjects194[row].title:extra[row-12];','label=row<12?guildProjects194[row].title:(row==14&&g->mapId==494)?"Return to Alberta":extra[row-12];',1);p.write_text(s)
p=S/'regional_draw194.h';s=p.read_text().replace('CampaignRegions194 r;if(!campaign_regions_load194','CampaignRegions194 r;if(guild_open194(questPins65)&&guild_near194(g))campaign_document_one193(g,m,zoom,slope,g->mapId==494?800:188,g->mapId==494?1440:1116);if(!campaign_regions_load194',1);p.write_text(s)
print('Added separate 1600x1600 reconstructed guild map 494, project rooms, return passage and reused minimap allocation; original 494 maps/packs unchanged')
