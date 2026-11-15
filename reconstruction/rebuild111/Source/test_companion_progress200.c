#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
static int failAlloc200;
static void*alloc200(size_t n){return failAlloc200?NULL:malloc(n);}
#define NPC_STATE_ALLOC55 alloc200
#define NPC_STATE_FREE55 free
#include "campaign_party_state200.h"
#include "companion_progress200.h"
static unsigned char serialized200[NPC_STATE_FILE55],after200[NPC_STATE_FILE55];
int main(void){NpcState55 a={0},b={0},restored={0};unsigned char raw[640],copy[640],other[640];assert(party_progress_load200(&a,raw)==0&&!a.count);unsigned char legacy[256]={0};memcpy(legacy,"RPV2",4);legacy[4]=1;npc_state_put32_55(legacy+8,1u<<COMP200_ROAN);npc_state_put32_55(legacy+24,37);npc_state_put32_55(legacy+28,12);npc_state_put32_55(legacy+32,8);npc_state_put32_55(legacy+252,crc32(0,legacy,252));assert(party_write_hex200(&a,PARTY_VITAL_KEY200,0,legacy,256));CampaignPartyConfig200 config;party_config_default200(&config,1u<<COMP200_ROAN);config.mode[COMP200_ROAN]=PARTY_DEFEND200;assert(party_config_store200(&a,&config,1u<<COMP200_ROAN));unsigned revision=a.revision;assert(npc_state_encode55(&a,serialized200,sizeof serialized200));unsigned n=npc_state_wire_bytes55(&a);
 assert(party_progress_load200(&a,raw)==1&&a.revision==revision&&npc_state_get55(&a,PARTY_PROGRESS_KEY200,0)->length==512);PartyGrowth200 member;party_growth_read200(raw+16+COMP200_ROAN*32,&member);assert(member.level==37&&!member.exp&&member.jobLevel==2&&!member.jobExp&&member.job==1&&member.hp==12&&member.sp==8);
 failAlloc200=1;assert(!party_progress_commit200(&a,raw));failAlloc200=0;assert(a.revision==revision&&npc_state_encode55(&a,after200,sizeof after200)&&!memcmp(serialized200,after200,n));assert(party_progress_commit200(&a,raw));assert(npc_state_get55(&a,PARTY_PROGRESS_KEY200,0)->length==1280);assert(party_progress_load200(&a,copy)==1&&party_progress_valid200(copy,1));
 member.exp=123456;member.jobLevel=24;member.jobExp=654321;member.hp=11;member.sp=7;assert(party_progress_put200(copy,COMP200_ROAN,&member)&&party_progress_commit200(&a,copy));assert(party_progress_load200(&a,copy)==1);config.active[0]=255;assert(party_config_store200(&a,&config,1u<<COMP200_ROAN));config.active[0]=COMP200_ROAN;assert(party_config_store200(&a,&config,1u<<COMP200_ROAN));assert(party_progress_load200(&a,raw)==1&&!memcmp(raw,copy,640));
 assert(party_progress_load200(&b,other)==0);PartyGrowth200 second={9,22,3,11,3,2,1};assert(party_progress_put200(other,COMP200_YUUFA,&second)&&party_progress_commit200(&b,other));assert(party_progress_load200(&a,raw)==1&&!memcmp(raw,copy,640));
 assert(npc_state_encode55(&a,serialized200,sizeof serialized200));n=npc_state_wire_bytes55(&a);assert(npc_state_decode55(&restored,serialized200,n));assert(party_progress_load200(&restored,raw)==1&&!memcmp(raw,copy,640));CampaignPartyConfig200 readConfig;assert(party_config_load200(&restored,&readConfig,1u<<COMP200_ROAN)==1&&!memcmp(&config,&readConfig,sizeof config));
 revision=a.revision;raw[4]=2;assert(!party_progress_commit200(&a,raw)&&a.revision==revision);assert(npc_state_encode55(&a,after200,sizeof after200)&&!memcmp(serialized200,after200,n));memcpy(raw,copy,640);PartyGrowth200 invalid=member;invalid.level=0;assert(!party_progress_put200(raw,COMP200_ROAN,&invalid)&&!memcmp(raw,copy,640));
 npc_state_clear55(&a);npc_state_clear55(&b);npc_state_clear55(&restored);puts("PASS original legacy record migration, failed-write atomicity, independent character growth/settings, reserve-setting isolation and complete sparse-save roundtrip. Battle/formation caller integration remains pending; HOST ONLY.");}
