/* MIT. One256KiB texture; campaign and native NPC cutins never stay allocated together. */
#ifndef MYRO_CAMPAIGN_PORTRAIT_DRAW200_H
#define MYRO_CAMPAIGN_PORTRAIT_DRAW200_H
#include "campaign_portrait200.h"
static unsigned char*campaignPortraitTexture200;
static int campaignPortraitLoaded200=-1,campaignPortraitFailed200=-1,campaignPortraitModal200;
static unsigned campaignPortraitMap200=~0u;
static void campaign_portrait_release200(void){if(campaignPortraitTexture200){while(pb_busy()){}MmFreeContiguousMemory(campaignPortraitTexture200);}campaignPortraitTexture200=NULL;campaignPortraitLoaded200=campaignPortraitFailed200=-1;campaignPortraitMap200=~0u;}
static int campaign_portrait_read200(void*context,unsigned at,unsigned char*out,unsigned bytes){(void)context;
#ifdef MYRO_HOST
 const char*path=getenv("MYRO_CAMPAIGN_PORTRAIT_PATH");if(!path)path="../Campaign/portraits.bin";
#else
 const char*path="D:\\storyportraits.bin";
#endif
 FILE*f=fopen(path,"rb");if(!f)return 0;int ok=!fseek(f,0,SEEK_END)&&ftell(f)==CAMPAIGN_PORTRAIT_FILE_BYTES200&&at<=CAMPAIGN_PORTRAIT_FILE_BYTES200&&bytes<=CAMPAIGN_PORTRAIT_FILE_BYTES200-at&&!fseek(f,at,SEEK_SET)&&fread(out,1,bytes,f)==bytes;fclose(f);return ok;}
/* Call only after the previous GPU frame finishes, before recording this frame. */
static void campaign_portrait_prepare200(NpcGame55*g){campaignPortraitModal200=scene_ui_modal200();if(!campaignPortraitModal200){campaign_portrait_release200();npc_portrait_prepare171(g);return;}if(npcPortraitTexture171)npc_portrait_release171();int wanted=scene_ui_tick200()==SC200_LINE?campaign_portrait_index200(scene_text200(&campaignUI200.scene,0),scene_expression200(&campaignUI200.scene)):-1;if(wanted<0){campaign_portrait_release200();return;}if(campaignPortraitMap200!=g->player.game->mapId){campaign_portrait_release200();campaignPortraitMap200=g->player.game->mapId;}if(wanted==campaignPortraitLoaded200||wanted==campaignPortraitFailed200)return;if(!campaignPortraitTexture200){MM_STATISTICS memory={0};memory.Length=sizeof(memory);MmQueryStatistics(&memory);if(memory.AvailablePages*4096u<1536u*1024u){campaignPortraitFailed200=wanted;return;}campaignPortraitTexture200=MmAllocateContiguousMemoryEx(CAMPAIGN_PORTRAIT_RAW200,0,0x03ffafff,4096,PAGE_READWRITE|PAGE_WRITECOMBINE);if(!campaignPortraitTexture200){campaignPortraitFailed200=wanted;return;}}campaignPortraitLoaded200=-1;if(!campaign_portrait_decode200((unsigned)wanted,campaign_portrait_read200,NULL,campaignPortraitTexture200,CAMPAIGN_PORTRAIT_RAW200)){campaignPortraitFailed200=wanted;return;}campaignPortraitLoaded200=wanted;campaignPortraitFailed200=-1;}
static void campaign_portrait_draw200(const NpcGame55*g){if(!campaignPortraitModal200){npc_portrait_draw171(g);return;}if(!campaignPortraitTexture200||campaignPortraitLoaded200<0||scene_ui_tick200()!=SC200_LINE)return;int wanted=campaign_portrait_index200(scene_text200(&campaignUI200.scene,0),scene_expression200(&campaignUI200.scene));if(wanted!=campaignPortraitLoaded200)return;hud_setup_direct(campaignPortraitTexture200,256,256,1024,0x0001122a,1);hud_quad(8,200,256,256,0,0,256,256);}
#endif
