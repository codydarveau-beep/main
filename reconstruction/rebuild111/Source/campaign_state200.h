/* MIT. Small per-character campaign state; ordinary NPC variables remain intact.
 * One typed value commits a complete versioned record, never half a milestone. */
#ifndef MYRO_CAMPAIGN_STATE200_H
#define MYRO_CAMPAIGN_STATE200_H
#include "npc_state55.h"
static const NpcState55*campaignRosterState200;
#define CAMPAIGN_QUEST200 2000000000u
#define CAMPAIGN_KEY200 UINT64_C(0xeca20000f219bc61)
#define CAMPAIGN_SCENES200 36u
#define CAMPAIGN_COMPANIONS200 19u
#define CAMPAIGN_WIRE200 64u
#define CAMPAIGN_TEXT200 128u
enum{C200_UNCHOSEN,C200_VANGUARD,C200_PATHFINDER,C200_KEEPER};
typedef struct{unsigned cursor,route,lineage,recruits,objectives,checkpoint;char guild[25];}Campaign200;
static int campaign_valid200(const Campaign200*c){if(!c||c->cursor>36||c->route>3||c->lineage>45||(c->route==0)!=(c->lineage==0)||c->recruits>=(1u<<19)||c->checkpoint>255||!memchr(c->guild,0,sizeof(c->guild)))return 0;if(c->cursor>1&&!c->route)return 0;for(unsigned i=0;c->guild[i];i++)if((unsigned char)c->guild[i]<32||(unsigned char)c->guild[i]>126)return 0;return 1;}
/* 1=valid record,0=absent,-1=unreadable. Do not silently reset corruption. */
static int campaign_load200(const NpcState55*s,Campaign200*out){if(!s||!out)return-1;const NpcVariable55*v=npc_state_get55(s,CAMPAIGN_KEY200,0);if(!v)return 0;if(v->kind!=NPC_STATE_STRING_KIND55||v->length!=CAMPAIGN_TEXT200)return-1;unsigned char b[64];for(unsigned i=0;i<64;i++){unsigned n=0;for(unsigned j=0;j<2;j++){unsigned char x=v->text[i*2+j];if(x>='0'&&x<='9')x-='0';else if(x>='a'&&x<='f')x=x-'a'+10;else return-1;n=(n<<4)|x;}b[i]=(unsigned char)n;}if(memcmp(b,"ROC2",4)||b[4]!=1||b[5]||b[6]||b[7]||npc_state_u32_55(b+60)!=crc32(0,b,60))return-1;Campaign200 c={0};c.cursor=b[8];c.route=b[9];c.lineage=b[10];c.checkpoint=b[11];c.recruits=npc_state_u32_55(b+12);c.objectives=npc_state_u32_55(b+16);memcpy(c.guild,b+20,25);for(unsigned i=45;i<60;i++)if(b[i])return-1;if(!campaign_valid200(&c))return-1;*out=c;return 1;}
static int campaign_store200(NpcState55*s,const Campaign200*c){if(!s||!campaign_valid200(c))return 0;unsigned char b[64]={0};memcpy(b,"ROC2",4);b[4]=1;b[8]=(unsigned char)c->cursor;b[9]=(unsigned char)c->route;b[10]=(unsigned char)c->lineage;b[11]=(unsigned char)c->checkpoint;npc_state_put32_55(b+12,c->recruits);npc_state_put32_55(b+16,c->objectives);memcpy(b+20,c->guild,strlen(c->guild));npc_state_put32_55(b+60,crc32(0,b,60));char text[129];static const char hex[]="0123456789abcdef";for(unsigned i=0;i<64;i++){text[2*i]=hex[b[i]>>4];text[2*i+1]=hex[b[i]&15];}text[128]=0;return npc_state_set_text55(s,CAMPAIGN_KEY200,0,text,128);}
/* Released developer sandbox is a completed campaign with its dedicated flag.
 * The same high bit at scene 1 is Super Novice intent, not sandbox conversion. */
static int campaign_sandbox_state228(const NpcState55*s){Campaign200 c;return s&&campaign_load200(s,&c)==1&&c.cursor==36&&!!(c.objectives&UINT32_C(0x80000000));}
static int campaign_begin200(NpcState55*s){Campaign200 c={0};int found=campaign_load200(s,&c);return found==1?1:found<0?0:campaign_store200(s,&c);}
static int campaign_commit_role200(NpcState55*s,unsigned route,unsigned lineage){Campaign200 c;if(campaign_load200(s,&c)!=1||route<1||route>3||lineage<1||lineage>45)return 0;if(c.route)return c.route==route&&c.lineage==lineage;if(c.cursor!=1)return 0;c.route=route;c.lineage=lineage;return campaign_store200(s,&c);}
static int campaign_objective200(NpcState55*s,unsigned expected,unsigned bit){Campaign200 c;if(bit>=32||campaign_load200(s,&c)!=1||c.cursor!=expected||c.cursor>=36)return 0;c.objectives|=1u<<bit;return campaign_store200(s,&c);}
static int campaign_checkpoint200(NpcState55*s,unsigned expected,unsigned step){Campaign200 c;if(step>255||campaign_load200(s,&c)!=1||c.cursor!=expected||c.cursor>=36)return 0;c.checkpoint=step;return campaign_store200(s,&c);}
/* Released completion rules retain the opening proof for scenes 0-11; later
 * scenes use their authored mask, or bit 0 when no explicit mask exists. */
static int campaign_advance200(NpcState55*s,unsigned expected,unsigned required){Campaign200 c;unsigned mask=expected<12?(required|(expected==0?3u:1u)):(required?required:1u);if(campaign_load200(s,&c)!=1||expected>=36||c.cursor!=expected||(c.objectives&mask)!=mask||(expected==1&&!c.route))return 0;c.cursor++;c.objectives=c.checkpoint=0;return campaign_store200(s,&c);}
/* An authored, explicitly accepted offer commits recruitment and its proof together. */
static int campaign_join200(NpcState55*s,unsigned expected,unsigned mask){Campaign200 c;if(!mask||mask>=(1u<<CAMPAIGN_COMPANIONS200)||campaign_load200(s,&c)!=1||c.cursor!=expected)return 0;c.recruits|=mask;c.objectives|=1u;return campaign_store200(s,&c);}
static int campaign_recruit200(NpcState55*s,unsigned id){Campaign200 c;if(id>=19||campaign_load200(s,&c)!=1)return 0;c.recruits|=1u<<id;return campaign_store200(s,&c);}
static int campaign_guild200(NpcState55*s,const char*name){Campaign200 c;if(!name||campaign_load200(s,&c)!=1||c.cursor!=5||!*name||strlen(name)>24||*name==' '||name[strlen(name)-1]==' ')return 0;char clean[25]={0};memcpy(clean,name,strlen(name));memcpy(c.guild,clean,sizeof(clean));return campaign_store200(s,&c);}
#endif
