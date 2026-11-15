/* Actual evidence renderer with host GPU recording; not rasterization. */
#define MYRO_HOST 1
#include <assert.h>
#include "combat.h"
#include "campaign_stage200.h"
#include "projection.h"
static NpcState55 documentState207;
static NpcState55*questPins65=&documentState207;
static int interiorRooms181,hidden207,catalog207,icon207,rect207;
static unsigned positionCount207,quadCount207,begins207;
static float positions207[64],quads207[320];
static int rooms_point181(const int*r,float x,float y){(void)r;(void)x;(void)y;return !hidden207;}
static float height_at(float x,float y){assert(positionCount207<32);positions207[positionCount207*2]=x;positions207[positionCount207*2+1]=y;positionCount207++;return 7;}
static int document_catalog207(int id){assert(id==1550);return catalog207;}
static void item_icon_begin52(void){begins207++;}
#define ITEM_ICON_BASE52 16384
#define SKIN_H 2048
static int itemIcons[1],skinTexture;
static const unsigned short skinRects[1][4]={{11,12,13,14}};
static const unsigned short*item_icon_rect52(int id){assert(id==16384);return rect207?skinRects[0]:NULL;}
static void hud_setup_direct(int tex,int width,int height,int pitch,unsigned mode,int blend){assert(tex==skinTexture&&width==512&&height==2048&&pitch==2048&&mode==0x1122a&&blend==1);}
static uint32_t commands207[4];
static uint32_t*pb_begin(void){return commands207;}
#define NV097_SET_DEPTH_TEST_ENABLE 1
#define NV097_SET_DEPTH_MASK 2
static uint32_t*pb_push1(uint32_t*p,unsigned op,unsigned value){assert((op==1&&value==1)||(op==2&&value==0));return p+1;}
static void pb_end(uint32_t*p){assert(p==commands207+2);}
static void ground_quad58(float x,float y,float w,float h,float top,float bottom,float u,float v,float uw,float vh){assert(quadCount207<32);float row[10]={x,y,w,h,top,bottom,u,v,uw,vh};memcpy(quads207+quadCount207*10,row,sizeof row);quadCount207++;}
#define inventory_catalog52 document_catalog207
#include "campaign_document207.h"
#undef inventory_catalog52
unsigned document207(unsigned row,unsigned cursor,unsigned map,unsigned guild,unsigned active,unsigned failure,const float*matrix,float zoom,float slope,float*out){
 Combat g={0};g.mapId=map;Campaign200 c={0};c.cursor=cursor;c.route=1;c.lineage=1;if(guild)strcpy(c.guild,"Fixture");assert(campaign_store200(questPins65,&c));unsigned revision=questPins65->revision;
 campaignStage200.definition=row<9?campaignStages200+row:row<42?campaignLaterStages197+row-9:NULL;campaignStage200.active=active;
 hidden207=failure==1;catalog207=failure==2?-1:0;itemIcons[0]=failure==3?-1:failure>=4?16384:0;rect207=failure!=5;positionCount207=quadCount207=begins207=0;
 campaign_document_draw200(&g,matrix,zoom,slope);assert(questPins65->revision==revision);
 out[0]=positionCount207;out[1]=quadCount207;out[2]=begins207;memcpy(out+3,positions207,positionCount207*2*sizeof(float));memcpy(out+67,quads207,quadCount207*10*sizeof(float));return quadCount207;
}
void document_clear207(void){npc_state_clear55(&documentState207);}
