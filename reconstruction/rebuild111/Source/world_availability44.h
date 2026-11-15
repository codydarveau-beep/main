/* MIT. Never offer a blue/interactable gate to an absent or malformed disc map. */
#ifndef MYRO_WORLD_AVAILABILITY44_H
#define MYRO_WORLD_AVAILABILITY44_H
static int world_sections_ready44(const WorldBlob*b,unsigned fileBytes){for(unsigned i=0;i<7;i++)if(!b[i].packed||!b[i].raw||b[i].offset>fileBytes||b[i].packed>fileBytes-b[i].offset)return 0;return 1;}
static int world_destination_ready44(unsigned id){if(id==494)return 1;return id<WORLD_MAP_COUNT&&mapWidths[id]&&mapHeights[id]&&world_sections_ready44(worldBlobs[id],WORLD_FILE_BYTES);}
#endif
