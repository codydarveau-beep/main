/* Candidate-only integration: actual world, dialogue/controller, staging,
 * movement, encounter ownership, camera projection and art readers.
 * GPU/raster and native job quest completion are not simulated here. */
#define main legacy_world_sequence200
#include "test_world43.c"
#undef main
#include "quest_journal65.h"
#include "campaign_admission_runtime194.h"
#include "font_metrics65.h"
#include "controller_tokens64.h"
#include "../Validation/actual_wrap194.inc"
static unsigned textDraws200;
static void pb_fill(int x,int y,int w,int h,unsigned c){(void)c;assert(x>=0&&y>=0&&w>=0&&h>=0&&x+w<=640&&y+h<=480);}
static void ui_panel(int x,int y,int w,int h,const char*t,int f,int c){(void)t;(void)f;(void)c;pb_fill(x,y,w,h,0);}
static void ui_cell(int x,int y,int w,int h,int s){(void)s;pb_fill(x,y,w,h,0);}
static void ui_scaled(int x,int y,float scale,const char*fmt,...){char s[512];va_list ap;va_start(ap,fmt);vsnprintf(s,sizeof s,fmt,ap);va_end(ap);assert(x>=0&&y>=0&&x+ui_text_width(s,scale)<=640&&y+11<=480);textDraws200++;}
static void ui_hint64(int x,int y,float scale,const char*fmt,...){char s[512];va_list ap;va_start(ap,fmt);vsnprintf(s,sizeof s,fmt,ap);va_end(ap);ui_scaled(x,y,scale,"%s",s);}
static void ui_fit47(int x,int y,int w,float scale,const char*s){(void)scale;(void)s;assert(x>=0&&y>=0&&x+w<=640&&y+11<=480);textDraws200++;}
#include "campaign_scene_ui200.h"
#include "campaign_rescue200.h"
#include "campaign_stage200.h"
#include "campaign_encounter198.h"
#include "campaign_investigation200.h"
#include "campaign_portrait200.h"
#include "session_controls40.h"
#include "projection.h"
#include "../Validation/actual_sprite195.inc"
#include "../Validation/scene_presentation_declarations200.inc"
#define MERCENARY_KIND180 1000
#define MERCENARY_TEXTURE180 120
static void*entityTextures[256];static unsigned entityCapacity51[256],uploadedFrames[256];static const void*uploadedSource[256];
static unsigned npcView64;
static float waterTime190;
#include "water_data.h"
#include "water_wave190.h"
#include "water_actor54.h"
#include "campaign_actor_render200.h"
static Combat player200;
static NpcState55 character200,quests200;
static NpcMonsters55 monsters200;
static unsigned frames200,proofs200,kills200,scenes200,cameras200,portraitsDecoded200;
static FILE*portraitFile200;
static unsigned char*portraitPixels200;
static int portraitIndex200=-1;
static int read_portrait200(void*ctx,unsigned at,unsigned char*out,unsigned bytes){FILE*f=ctx;return !fseek(f,at,SEEK_SET)&&fread(out,1,bytes,f)==bytes;}
static void portrait_frame200(int modal){int index=modal&&scene_ui_tick200()==SC200_LINE?campaign_portrait_index200(scene_text200(&campaignUI200.scene,0),scene_expression200(&campaignUI200.scene)):-1;if(index<0){free(portraitPixels200);portraitPixels200=NULL;portraitIndex200=-1;return;}if(!portraitPixels200){portraitPixels200=malloc(CAMPAIGN_PORTRAIT_RAW200);assert(portraitPixels200);}if(index!=portraitIndex200){assert(campaign_portrait_decode200((unsigned)index,read_portrait200,portraitFile200,portraitPixels200,CAMPAIGN_PORTRAIT_RAW200));portraitIndex200=index;portraitsDecoded200++;}}

static void release_scene200(void){campaign_encounter_reset198();rescue_reset200(&campaignRescue200);scene_ui_release200();campaign_actor_release200();free(portraitPixels200);portraitPixels200=NULL;portraitIndex200=-1;memset(&campaignStage200,0,sizeof campaignStage200);}
static Campaign200 story200(void){Campaign200 c;assert(campaign_load200(&character200,&c)==1);return c;}
static void bind200(void){campaign_stage_bind_bounded200(&campaignStage200,&player200,&character200,1,36);rescue_bind200(&campaignRescue200,&player200,&monsters200,&character200,1);}
static void enter200(unsigned map,float x,float y){assert(world_destination_ready44(map));assert(world_activate(map));if(x<0){x=spawnx;y=spawny;}player200.mapId=map;player200.x=x;player200.y=y;player200.canMove=world_can_move;player200.world=NULL;player200.hp=1000;if(!allowed(x,y))fprintf(stderr,"Unwalkable scene position: cursor %u map %u x %.0f y %.0f\n",story200().cursor,map,x,y);assert(allowed(x,y));bind200();}
static void frame200(void){bind200();int modal=scene_ui_modal200();float x=player200.x,y=player200.y,time=player200.time;session_world_tick43(&player200,.01f,modal,modal,1,0);if(modal)assert(player200.x==x&&player200.y==y&&player200.time==time);else{player200.x=x;player200.y=y;}unsigned before=monsters200.count;campaign_encounter_tick198(&player200,&monsters200,&character200,modal);if(modal)assert(monsters200.count==before);campaignStageModal200=modal;rooms_focus181(&interiorRooms181,x,y);portrait_frame200(modal);for(unsigned angle=0;angle<8;angle++){float yaw=angle*.7853981634f,m[16];world_camera(m,x,y,height_at(x,y),yaw,.8f,2.f);DrawActor actors[8];int n=0;campaign_actor_collect_ready200(&player200,m,cosf(yaw),sinf(yaw),2,actors,&n,1);assert(n>=0&&n<=4);if(modal){unsigned expected=campaignRescue200.active?4:campaignStage200.active?campaignStage200.definition->count:0;if((unsigned)n!=expected)fprintf(stderr,"Scene actor visibility mismatch: cursor %u map %u yaw %u expected %u got %d\n",story200().cursor,player200.mapId,angle,expected,n);assert((unsigned)n==expected);}for(int i=0;i<n;i++)assert(isfinite(actors[i].x)&&isfinite(actors[i].y)&&isfinite(actors[i].depth)&&actors[i].x>=-80&&actors[i].x<=720&&actors[i].y>=-160&&actors[i].y<=560);cameras200++;}campaign_actor_prepare200();if(modal)scene_ui_draw200();frames200++;}
static void open200(void){assert(scene_ui_open_bounded200(&character200,36));assert(!scene_ui_open_bounded200(&character200,37));}
static void kill_story200(void){for(unsigned i=0;i<monsters200.count;i++){NpcMonster55*m=monsters200.rows+i;if(!m->alive||m->map!=player200.mapId||m->slot<0)continue;CombatMob*b=player200.mobs+m->slot;assert(b->life==m->serial);b->hp=0;rescue_killed200(&campaignRescue200,&player200,b);campaign_encounter_killed198(&player200,b);m->alive=m->hp=0;b->enabled=0;kills200++;}}
static int proof200(void){Campaign200 c=story200();if(c.cursor==0){enter200(0,1468,2780);rescue_tick200(&campaignRescue200,.05f,0);kill_story200();assert(rescue_interact200(&campaignRescue200,R200_DRIVER)==0);for(unsigned i=0;i<100&&campaignRescue200.escort;i++){player200.x=1468;player200.y=campaignRescue200.driverY;rescue_tick200(&campaignRescue200,.05f,0);}c=story200();assert(c.objectives&1);player200.x=1484;player200.y=2788;rescue_interact200(&campaignRescue200,R200_PARCEL);assert((story200().objectives&3)==3);proofs200++;return 1;}
 if(c.cursor==1){unsigned jobs[]={1,5,3};player200.jobId=jobs[campaignUI200.role];assert(campaign_job_proof200(&character200,player200.jobId));proofs200++;return 1;}
 if(c.cursor==3){enter200(11,-1,-1);assert(campaign_investigation_page200(&character200,11,11,"Monster Scholar#02","citizens of Payon!"));assert(campaign_investigation_page200(&character200,11,11,"Young Man#2payon","dearly departed grandfather"));}
 unsigned before=story200().objectives;
 for(unsigned row=0;row<42;row++){const CampaignStageDefinition200*d=row<33?campaignLaterStages197+row:campaignStages200+row-33;if(d->cursor!=c.cursor)continue;Campaign200 now=story200();if((now.objectives&d->recoveredFields197[7])!=d->recoveredFields197[7])continue;enter200(d->map,d->x,d->y);campaign_encounter_tick198(&player200,&monsters200,&character200,0);kill_story200();
  unsigned docs=d->cursor<5?1:d->cursor>=6?d->recoveredFields197[0]:0;
  for(unsigned k=0;k<docs;k++){unsigned index=k;if(c.cursor==31)index=campaignStageOrder198[c.route-1][k];float x,y;campaign_stage_document198(d,index,&x,&y);player200.x=x;player200.y=y;assert(allowed(x,y));bind200();int near=campaign_stage_near200(&campaignStage200);assert(near==110+(int)index);int action=campaign_stage_interact200(&campaignStage200,near);assert(action==2||action==-1);proofs200++;}
 }
 return story200().objectives!=before;
}
static void lead200(unsigned cursor){if(cursor<3){enter200(0,1452,2820);return;}Campaign200 c=story200();const CampaignStageDefinition200*chosen=NULL;for(unsigned row=0;row<42;row++){const CampaignStageDefinition200*d=row<33?campaignLaterStages197+row:campaignStages200+row-33;if(d->cursor==cursor&&d->count&&(c.objectives&d->recoveredFields197[7])==d->recoveredFields197[7]&&!(c.objectives&d->recoveredFields197[8])){chosen=d;break;}}assert(chosen);unsigned actor=campaign_stage_lead198(chosen);assert(actor<chosen->count);enter200(chosen->map,chosen->actor[actor].x,chosen->actor[actor].y);assert(campaign_stage_near200(&campaignStage200)==100+(int)actor);}
int main(void){portraitFile200=fopen(getenv("MYRO_CAMPAIGN_PORTRAIT_PATH"),"rb");assert(portraitFile200);worldSceneRelease200=release_scene200;quest_journal_bind65(&quests200,&character200);campaign_admission_install194();for(unsigned role=0;role<3;role++)for(unsigned variant=0;variant<2;variant++){npc_state_clear55(&character200);assert(campaign_begin200(&character200));memset(&player200,0,sizeof player200);player200.hp=player200.maxhp=1000;player200.level=1;player200.faceY=1;campaignUI200.role=role;unsigned retries[36]={0};for(unsigned cursor=0;cursor<36;cursor++){assert(story200().cursor==cursor);lead200(cursor);open200();campaignUI200.role=role;for(unsigned steps=0;story200().cursor==cursor&&steps<256;steps++){int status=scene_ui_tick200();frame200();if(status==SC200_LINE){scene_ui_input200(2,player200.jobId);}else if(status==SC200_CHOICE){campaignUI200.choice=variant&&!retries[cursor]++;scene_ui_input200(2,player200.jobId);}else if(status==SC200_ROLE){scene_ui_input200(2,player200.jobId);scene_ui_input200(2,player200.jobId);}else if(status==SC200_GUILD){assert(campaign_guild200(&character200,"Recovery"));}else if(status==SC200_WAIT){assert(proof200());lead200(cursor);open200();campaignUI200.role=role;}else if(status==SC200_CLOSED){lead200(cursor);open200();campaignUI200.role=role;}else assert(status==SC200_COMPLETE);}
 if(story200().cursor!=cursor+1)fprintf(stderr,"Scene sequence did not advance: cursor %u checkpoint %u objectives %x\n",cursor,story200().checkpoint,story200().objectives);assert(story200().cursor==cursor+1);scenes200++;scene_ui_release200();}
 assert(story200().cursor==36);release_scene200();world_release();npc_monsters_clear55(&monsters200);activeMap=~0u;}
 fclose(portraitFile200);npc_state_clear55(&character200);npc_state_clear55(&quests200);assert(!allocated&&!bytesNow);printf("PASS candidate scene sequences %u, frames %u, physical proofs %u, scripted enemy events %u, camera records %u dialogue draw operations %u and portrait decodes %u. Host recorder only; native job completion and combat outcomes are fixtures; companion growth/AI and Xbox acceptance remain separate.\n",scenes200,frames200,proofs200,kills200,cameras200,textDraws200,portraitsDecoded200);}
