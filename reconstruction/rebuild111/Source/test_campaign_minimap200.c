/* Host draw recorder for retained story markers; no GPU or target claims. */
#define main stage_fixture_main200
#include "test_campaign_stage198.c"
#undef main
#include "campaign_data200.h"
static int tracked200=1;
static int quest_tracked65(unsigned id){assert(id==CAMPAIGN_QUEST200);return tracked200;}
typedef struct{float x,y;unsigned color;int size;}Mark200;
static Mark200 marks200[16];static unsigned markCount200;
static void minimap_marker(float x,float y,unsigned color,int size){assert(markCount200<16);marks200[markCount200++]=(Mark200){x,y,color,size};}
#include "campaign_minimap200.h"
static void draw200(const CampaignStageDefinition200*d,unsigned checkpoint,unsigned objectives){Campaign200 c={0};c.cursor=d->cursor;c.route=1;c.lineage=1;c.checkpoint=checkpoint;c.objectives=objectives;assert(campaign_store200(&state,&c));game.mapId=d->map;campaignStage200=(CampaignStage200){&game,&state,d,1};unsigned rev=state.revision;markCount200=0;campaign_minimap200(&game);assert(state.revision==rev);}
int main(void){
 const CampaignStageDefinition200*d=campaign_stage_select198(3,12,0);assert(d);draw200(d,9,3);assert(markCount200==4&&marks200[2].x==364&&marks200[2].y==1028);draw200(d,9,7);assert(markCount200==2);draw200(d,8,3);assert(markCount200==2);
 d=campaign_stage_select198(10,120,0);assert(d);draw200(d,7,0);assert(markCount200==2);draw200(d,7,0x300);assert(markCount200==8&&marks200[2].x==820&&marks200[6].x==868);draw200(d,7,0x310);assert(markCount200==6&&marks200[2].x==844);
 d=campaign_stage_select198(28,495,0);assert(d);draw200(d,campaign_stage_gate198(28),0);assert(markCount200==0);draw200(d,campaign_stage_gate198(28),0x200);assert(markCount200==2&&marks200[0].x==1180&&marks200[0].y==1156);draw200(d,campaign_stage_gate198(28),0x204);assert(!markCount200);
 d=campaign_stage_select198(34,496,0);assert(d);draw200(d,8,0x100);assert(markCount200==2);draw200(d,8,0x300);assert(markCount200==8&&marks200[2].x==2292&&marks200[6].x==2340);
 tracked200=0;markCount200=0;campaign_minimap200(&game);assert(!markCount200);tracked200=1;game.mapId=7;campaign_minimap200(&game);assert(!markCount200);game.mapId=496;campaignStage200.active=0;campaign_minimap200(&game);assert(!markCount200);
 npc_state_clear55(&state);puts("PASS retained story markers: lead contacts, evidence spacing, collected proofs, encounter gates, chapter-four ordering, alias maps, tracking and no state mutation. HOST ONLY.");
}
