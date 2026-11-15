#define MYRO_HOST 1
#include <stdlib.h>
static int failWrites200;
static void*state_alloc200(size_t n){return failWrites200?NULL:malloc(n);}
#define NPC_STATE_ALLOC55 state_alloc200
#define NPC_STATE_FREE55 free
#include "campaign_scene200.h"
void scene_poll_reference200(const unsigned char*data,unsigned bytes,unsigned cursor,unsigned role,unsigned node,unsigned objectives,unsigned recruits,unsigned named,unsigned fail,unsigned out[6]){NpcState55 state={0};Campaign200 c={0};c.cursor=cursor;c.route=role;c.lineage=role;c.checkpoint=node;c.objectives=objectives;c.recruits=recruits;if(named)strcpy(c.guild,"Recovery");if(!campaign_store200(&state,&c))abort();unsigned char*p=malloc(bytes);if(!p)abort();memcpy(p,data,bytes);Scene200 scene={&state,p,bytes,scene_u16_200(p+6),16+scene_u16_200(p+6)*32,cursor,1};failWrites200=fail;out[0]=(unsigned)scene_poll200(&scene);failWrites200=0;if(campaign_load200(&state,&c)!=1)abort();out[1]=c.cursor;out[2]=c.checkpoint;out[3]=c.objectives;out[4]=c.recruits;out[5]=scene.data!=NULL;scene_close200(&scene);npc_state_clear55(&state);}
