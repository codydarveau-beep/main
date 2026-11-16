/* MIT. Versioned per-character formation/preferences and companion vitals. */
#ifndef MYRO_CAMPAIGN_PARTY_STATE200_H
#define MYRO_CAMPAIGN_PARTY_STATE200_H
#include "campaign_state200.h"
#include "campaign_companions200.h"
#define PARTY_CONFIG_KEY200 UINT64_C(0xeca20000f219bc62)
#define PARTY_VITAL_KEY200 UINT64_C(0xeca20000f219bc63)
enum{PARTY_ASSIST200,PARTY_DEFEND200,PARTY_PASSIVE200};
enum{PARTY_BALANCED200,PARTY_OFFENSE200,PARTY_SUPPORT200};
typedef struct{unsigned char active[3],mode[19],priority[19],skills[19];}CampaignPartyConfig200;
static CampaignPartyConfig200 campaignConfig200;
static NpcState55*campaignPartyState200;
static int party_read_hex200(const NpcState55*s,uint64_t key,unsigned index,unsigned char*out,unsigned bytes){if(!s)return-1;const NpcVariable55*v=npc_state_get55(s,key,index);if(!v)return 0;if(v->kind!=NPC_STATE_STRING_KIND55||v->length!=bytes*2)return-1;for(unsigned i=0;i<bytes;i++){unsigned value=0;for(unsigned j=0;j<2;j++){unsigned x=(unsigned char)v->text[i*2+j];if(x>='0'&&x<='9')x-='0';else if(x>='a'&&x<='f')x=x-'a'+10;else return-1;value=value*16+x;}out[i]=(unsigned char)value;}return 1;}
static int party_write_hex200(NpcState55*s,uint64_t key,unsigned index,const unsigned char*b,unsigned bytes){if(!s||bytes>256)return 0;char text[513];static const char h[]="0123456789abcdef";for(unsigned i=0;i<bytes;i++){text[i*2]=h[b[i]>>4];text[i*2+1]=h[b[i]&15];}text[bytes*2]=0;return npc_state_set_text55(s,key,index,text,bytes*2);}
static int party_config_valid200(const CampaignPartyConfig200*c,unsigned recruits){unsigned mask=0;for(unsigned i=0;i<3;i++){unsigned id=c->active[i];if(id==255)continue;if(id>=19||!(recruits&(1u<<id))||(mask&(1u<<id)))return 0;mask|=1u<<id;}for(unsigned i=0;i<19;i++)if(c->mode[i]>2||c->priority[i]>2||c->skills[i]>1)return 0;return 1;}
static void party_config_default200(CampaignPartyConfig200*c,unsigned recruits){memset(c,0,sizeof(*c));memset(c->active,255,3);for(unsigned i=0;i<19;i++)c->skills[i]=1;c->priority[COMP200_YUUFA]=PARTY_SUPPORT200;unsigned n=0;for(unsigned i=0;i<19&&n<3;i++)if((recruits&(1u<<i)))c->active[n++]=(unsigned char)i;}
static int party_config_store200(NpcState55*s,const CampaignPartyConfig200*c,unsigned recruits){if(!party_config_valid200(c,recruits))return 0;unsigned char b[80]={0};memcpy(b,"RPT2",4);b[4]=1;memcpy(b+8,c->active,3);memcpy(b+11,c->mode,19);memcpy(b+30,c->priority,19);memcpy(b+49,c->skills,19);npc_state_put32_55(b+76,crc32(0,b,76));return party_write_hex200(s,PARTY_CONFIG_KEY200,0,b,80);}
static int party_config_load200(const NpcState55*s,CampaignPartyConfig200*c,unsigned recruits){unsigned char b[80];int found=party_read_hex200(s,PARTY_CONFIG_KEY200,0,b,80);if(found!=1)return found;if(memcmp(b,"RPT2",4)||b[4]!=1||b[5]||b[6]||b[7]||npc_state_u32_55(b+76)!=crc32(0,b,76))return-1;for(unsigned i=68;i<76;i++)if(b[i])return-1;CampaignPartyConfig200 q;memcpy(q.active,b+8,3);memcpy(q.mode,b+11,19);memcpy(q.priority,b+30,19);memcpy(q.skills,b+49,19);if(!party_config_valid200(&q,recruits))return-1;*c=q;return 1;}
#include "companion_progress200.h"
static int party_vitals_load200(const NpcState55*s,unsigned char b[640]){return party_progress_load200(s,b);}
static int party_vitals_put200(unsigned char b[640],unsigned id,unsigned level,unsigned hp,unsigned sp){if(id>=19||!level||level>250)return 0;PartyGrowth200 m;if(npc_state_u32_55(b+8)&(1u<<id)){party_growth_read200(b+16+id*32,&m);if(m.level!=level)return 0;}else m=(PartyGrowth200){level,0,2,0,partyInitialJobs200[id],0,0};m.hp=hp;m.sp=sp;return party_progress_put200(b,id,&m);}
static int party_vitals_commit200(NpcState55*s,unsigned char b[640]){return party_progress_commit200(s,b);}
static int party_vital_read200(const NpcState55*s,unsigned id,unsigned*level,unsigned*hp,unsigned*sp){unsigned char b[640];if(id>=19)return-1;int found=party_vitals_load200(s,b);if(found!=1)return found;if(!(npc_state_u32_55(b+8)&(1u<<id)))return 0;PartyGrowth200 m;party_growth_read200(b+16+id*32,&m);*level=m.level;*hp=m.hp;*sp=m.sp;return 1;}
static int party_vital_store200(NpcState55*s,unsigned id,unsigned level,unsigned hp,unsigned sp){unsigned char b[640];if(party_vitals_load200(s,b)<0||!party_vitals_put200(b,id,level,hp,sp))return 0;return party_vitals_commit200(s,b);}
#endif
