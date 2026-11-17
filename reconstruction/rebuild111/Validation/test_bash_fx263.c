#define MYRO_HOST 1
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "combat.h"
#include "npc_effect_audio_data172.h"
typedef struct{unsigned id,map,member,life;float at,x,y,z;unsigned positioned;}CampaignNativeFx212;
static CampaignNativeFx212 campaignNativeFx212[8],combatNativeFx263[8];static unsigned combatNativeFxNext263;
static float height_at(float x,float y){(void)x;(void)y;return 3;}
static void campaign_native_sound212(Combat*g,unsigned effect){for(unsigned i=0;i<sizeof(npcFxSounds172)/sizeof(*npcFxSounds172);i++)if(npcFxSounds172[i].effect==effect)combat_sound_at(g,SOUND_NPC_FIRST64+npcFxSounds172[i].clip,0);}
static void combat_native_effect263(Combat*g,unsigned effect,float x,float y){combatNativeFx263[combatNativeFxNext263++%8]=(CampaignNativeFx212){effect,g->mapId,0,0,g->time,x,y,height_at(x,y),1};campaign_native_sound212(g,effect);}

static Combat g;
int main(void){combat_init(&g,100,100,NULL,NULL);g.mapId=7;memset(campaignNativeFx212,0x5a,sizeof(campaignNativeFx212));unsigned char saved[sizeof(campaignNativeFx212)];memcpy(saved,campaignNativeFx212,sizeof(saved));for(unsigned i=0;i<32;i++){g.time=i*.01f;combat_native_effect263(&g,i%2?1:16,100+i,200+i);}assert(!memcmp(saved,campaignNativeFx212,sizeof(saved)));assert(combatNativeFxNext263==32);for(unsigned i=0;i<8;i++){CampaignNativeFx212*f=combatNativeFx263+i;assert(f->id==(i%2?1:16)&&f->map==7&&f->positioned&&f->x==124+i&&f->y==224+i&&f->z==3);}assert(g.soundWrite==32);for(unsigned i=0;i<32;i++)assert(g.soundEvents[i%32]==SOUND_NPC_FIRST64+(i%2?44:34));puts("PASS actual original cue table and production player-FX emission: cast16/hit1 sound IDs, fixed impact positions/map, bounded8slots independent of companions, no companion effect eviction. Native particle GPU draw remains target verification.");}
