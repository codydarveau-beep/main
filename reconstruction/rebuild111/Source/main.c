#include "menu_groups48.h"
/* SPDX-License-Identifier: MIT
 * Xbox offline inventory prototype. Writes only its local character save files.
 */
#include <hal/debug.h>
#include <hal/video.h>
#include <windows.h>
#include <pbkit/pbkit.h>
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
static uint16_t *terrain; static uint8_t *walk;
static unsigned mw,mh,nverts;static uint32_t *cellStarts;static float *groundHeights,*meshVertices;static unsigned char *meshRaw;
static unsigned tw,th,gw,gh;
static float spawnx,spawny;
static int gpuReady;static char runtimeStage[100]="Starting";
static void fail(const char*s);
#include <zlib.h>
#include "world_data.h"
#include "projection.h"
#include "interior_rooms181.h"
#include "view_controls54.h"
static voidpf asset_zalloc(voidpf opaque,uInt count,uInt size){
 (void)opaque;if(size&&count>SIZE_MAX/size)return NULL;return calloc(count,size);
}
static void asset_zfree(voidpf opaque,voidpf p){(void)opaque;free(p);}
static unsigned char *inflateasset(const char *name,const unsigned char *src,unsigned packed,unsigned raw){
 debugPrint("Unpacking %s...\n",name);
 unsigned char *p=malloc(raw);if(!p)fail("Insufficient memory while unpacking");
 z_stream z={0};z.zalloc=asset_zalloc;z.zfree=asset_zfree;z.next_in=(Bytef*)src;z.avail_in=packed;z.next_out=p;z.avail_out=raw;
 int init=inflateInit(&z);if(init!=Z_OK){char msg[128];snprintf(msg,sizeof(msg),"Inflater init failed for %s: %d",name,init);fail(msg);}
 int result=inflate(&z,Z_FINISH);unsigned long n=z.total_out;inflateEnd(&z);
 if(result!=Z_STREAM_END||n!=raw)fail("Embedded asset decompression failed");return p;
}
#include "map_loader.h"
#include "controller_tolerance58.h"
static int button(SDL_GameController *p,SDL_GameControllerButton b){return p&&SDL_GameControllerGetButton(p,b);}
static float axis(SDL_GameController*p,SDL_GameControllerAxis a){if(!p)return 0;int v=SDL_GameControllerGetAxis(p,a);if(a<=SDL_CONTROLLER_AXIS_RIGHTY){unsigned stick=a>=SDL_CONTROLLER_AXIS_RIGHTX;int x=SDL_GameControllerGetAxis(p,stick?SDL_CONTROLLER_AXIS_RIGHTX:SDL_CONTROLLER_AXIS_LEFTX),y=SDL_GameControllerGetAxis(p,stick?SDL_CONTROLLER_AXIS_RIGHTY:SDL_CONTROLLER_AXIS_LEFTY);return stick_accept58(x,y,stickSteps58[stick])?v/32768.f:0;}return(v>-6500&&v<6500)?0:v/32768.f;}

#include "controller_nav61.h"
static unsigned menuRightSuppressed161;
static unsigned menu_sticks61(SDL_GameController*p){static unsigned held[2];if(!p){held[0]=held[1]=0;return 0;}for(unsigned i=0;i<2;i++)held[i]=(i&&menuRightSuppressed161)?0:menu_stick61(SDL_GameControllerGetAxis(p,i?SDL_CONTROLLER_AXIS_RIGHTX:SDL_CONTROLLER_AXIS_LEFTX),SDL_GameControllerGetAxis(p,i?SDL_CONTROLLER_AXIS_RIGHTY:SDL_CONTROLLER_AXIS_LEFTY),stickSteps58[i],held[i]);return held[0]?held[0]:held[1];}

#include "walk_footprint46.h"
static int allowed(float x,float y){return walk_footprint46(walk,gw,gh,x,y);}
static float height_at(float x,float y){
 int ix=(int)(x/16),iy=(int)(y/16);if(ix<0)ix=0;if(iy<0)iy=0;if(ix>=(int)mw)ix=mw-1;if(iy>=(int)mh)iy=mh-1;
 float fx=x/16-ix,fy=y/16-iy;const float *h=groundHeights+(iy*mw+ix)*4;
 if(fx>fy)return surface_height(surfaceMap,gw,gh,x,y,h[0]+(h[1]-h[0])*fx+(h[3]-h[1])*fy);
 return surface_height(surfaceMap,gw,gh,x,y,h[0]+(h[3]-h[2])*fx+(h[2]-h[0])*fy);
}
#include "combat.h"
#include "input_repeat.h"
#include "cast_ray.h"
#include "ground_cursor.h"
#include "sprites.h"
#include "heap_trim183.h"
static int renderer_can_species52(void*world,unsigned kind){(void)world;if(kind>=MOB_SPEC_COUNT)return 0;if(sprites[kind+1].raw)return 1;unsigned art=mob_art_kind55(kind);unsigned bytes=art<50?legacyEnemyStreams171[art].packed+legacyEnemyStreams171[art].raw:enemyStreams51[art-50].packed+enemyStreams51[art-50].raw;MM_STATISTICS memory={0};memory.Length=sizeof(memory);MmQueryStatistics(&memory);return (uint64_t)memory.AvailablePages*4096>bytes+2u*1024*1024;}
static void renderer_species_sync52(Combat*g){if(!g->creatureAssetsChanged52)return;unsigned char wanted[MOB_SPEC_COUNT]={0};for(unsigned i=0;i<SPAWN_DEF_COUNT;i++)if(spawnDefs[i].map==g->mapId)wanted[spawnDefs[i].kind]=1;for(unsigned i=0;i<MOB_COUNT;i++){CombatMob*m=g->mobs+i;if(m->enabled&&(m->hp>0||g->time-m->deadAt<1.5f))wanted[m->kind]=1;}while(pb_busy()){}enemy_cache_clear51();for(unsigned i=0;i<MOB_SPEC_COUNT;i++)if(!wanted[i]&&sprites[i+1].raw){free(sprites[i+1].raw);memset(sprites+i+1,0,sizeof(*sprites));}for(unsigned i=0;i<MOB_SPEC_COUNT;i++)if(wanted[i]&&!sprites[i+1].raw)sprite_load_enemy44(i);spriteEpoch++;g->creatureAssetsChanged52=0;}

#include "player_contact.h"
#include "walk_phase62.h"
static WalkPhase62 expandedWalk62;
#include "frame_profile50b.h"
static uint64_t frame_clock50b(void){return KeQueryPerformanceCounter();}
static volatile unsigned frameAudioTicks50b;
#define FRAME_AUDIO_CLOCK50B() ((unsigned)frame_clock50b())
#define FRAME_AUDIO_ADD50B(n) (frameAudioTicks50b+=(n))
#define MYRO_MUSIC_DISC50 1
#include "sound.h"
#include "world_collision45.h"
static int world_can_cast(void*unused,float x,float y,float nx,float ny){(void)unused;return cast_ray(walk,gw,gh,x,y,nx,ny);}
#include "gpu.h"
#include "gpu_inflate.h"
#include "guardian_draw51.h"
#include "art_draw39.h"
#define MYRO_ORIGINAL_ART39 1
#include "save_xbox.h"
#include "screen_xbox55.h"
#include "autosave_xbox50b.h"
#include "shop.h"
#include "core_npc53.h"
#include "merchant_services.h"
#include "hud.h"
#include "window_ui.h"
#include "window_draw.h"
#include "diagnostics45.h"
#include "target_geometry41.h"
#include "target_marker40.h"
#include "target_select47.h"
#include "hotbar_input53.h"
#include "session_controls40.h"
#include "cart_pose40.h"
#include "merchant_draw.h"
#define DAMAGE_NATIVE53 1
#include "damage_draw.h"
#include "skills_ui.h"
#include "minimap_upload.h"
static int world_in_water(void*,float,float,float,float);
#include "world_maps.h"
#include "utility_draw.h"
#include "minimap_draw.h"
#include "scenery.h"
#include "water_draw.h"
#include "water_query.h"
#include "pending_warps.h"
#include "developer.h"
#include "npc_game_xbox55.h"
#include "npc_trader180.h"
#include "npc_procedural180.h"
#include "npc_portrait_draw171.h"
#include "pause_draw.h"
#include "developer_draw.h"
#include "spell_world41.h"
#include "portal_draw52.h"
#include "portal_draw61.h"
#include "ice_draw48.h"
#include "trans_burst52.h"
#include "field_draw48.h"
#include "trans_burst_draw52.h"
#include "render_cache50.h"
#include "headgear54.h"
#include "headgear_ui180.h"
#include "stylist_preview191.h"
typedef struct{unsigned frame;HeadPose54 pose;}PaperContext200;
static void paper_draw200(void*context,int x,int y){PaperContext200*c=context;unsigned used200=(unsigned)(hudBatch.vertices-hudSkinVertices54b)/HUD_QUAD_FLOATS+hudBatch.count;hud_batch_end();head_paper_doll180(&sprites[0],c->frame,c->pose,x,y,52,104);hud_batch_begin();hudBatch.vertices=hudSkinVertices54b+used200*HUD_QUAD_FLOATS;}
static void npc_render_release171(void);
static void core_npc_render_release183(void);
static void mercenary_render_release180(void);
static void class_sound_map180(void);
static void class_sound_map_release173(void);
#include "monster_visibility180.h"
static void campaign_portrait_release200(void);
static void render_release54(void){campaign_portrait_release200();core_npc_render_release183();core_trader_clear180();class_sound_map_release173();death_sound_clear180();mercenary_render_release180();art_gpu_release172();art_cache_clear183();appearance_hair_release58();spell_texture_release50();head_release54();portal_release61();npc_render_release171();npc_portrait_release171();npc_disc_clear55(&npcGame55.disc);npc_program_trim171(&npcGame55.programs,NULL,0);}
#include "attack_sequence50c.h"
typedef struct {int slot,kind;unsigned frame;float x,y,depth,groundY;unsigned sourceFade50c;int water54;float waterline54,scale60;} DrawActor;
#include "water_actor54.h"
#include "campaign_scene200.h"
#include "campaign_scene_ui200.h"
#include "campaign_portrait_draw200.h"
#include "campaign_rescue200.h"

static int near_pending(const Combat*g){if(g->hp<=0)return 0;for(unsigned i=0;i<PENDING_WARP_COUNT;i++)if(pendingWarps[i].map==activeMap&&combat_dist(g->x,g->y,pendingWarps[i].x,pendingWarps[i].y)<22)return 1;return 0;}
#include "facing45.h"
#include "sprite_slots45.h"
static SpriteSlots45 mobSlots45;
static Facing45 mobFacing45[MOB_COUNT],playerFacing164;
#include "quicken_trail45.h"
static int facing(float fx,float fy,float co,float si){float sx=co*fx+si*fy,sy=si*fx-co*fy;return ((int)floorf(atan2f(-sx,sy)*4/3.14159265f+.5f)+8)%8;}
#include "core_npc_draw53.h"
#include "ground_draw58.h"
#include "npc_render55.h"
#include "npc_effect_draw172.h"
#include "npc_halo180.h"
#include "npc_dialogue_draw55.h"
#include "mercenary_draw180.h"
#include "campaign_actor_render200.h"
#include "companion_render50.h"
#include "campaign_world200.h"
#include "campaign_party_ui200.h"
#include "regional_world194.h"
#include "guild_ui194.h"
#include "guild_world194.h"
#include "regional_draw194.h"
#include "class_sound_cache50.h"
static void fail(const char*s){
 if(gpuReady)pb_show_debug_screen();MM_STATISTICS mem={0};mem.Length=sizeof(mem);MmQueryStatistics(&mem);
 debugPrint("MyRO 1.11.0 recovery stopped: %s\nStage: %s\nFree RAM: %lu KiB\nReset to retry. Existing saves are preserved.\n",s,runtimeStage,mem.AvailablePages*4);for(;;)Sleep(1000);
}
#include "performance_draw50b.h"
#include "memory_draw183.h"
#include "npc_cache183.h"
static void boss_wallclock53(void);
#include "frontend_xbox56.h"
#include "save_browser56.h"
#include "menu_signature58.h"
static void boss_wallclock53(void){FILETIME ft;GetSystemTimeAsFileTime(&ft);uint64_t ticks=(uint64_t)ft.dwLowDateTime|((uint64_t)ft.dwHighDateTime<<32);boss_clock53(ticks/10000000u);}
extern void pb_hardware_config54(int,void(*)(void));
static void hardware_report54(void){debugPrint("MyRO 2.0.0 GPU report\nStage: %s\nMesh vertex base %08x, source first %u, window %u\n",runtimeStage,(unsigned)gpuRangeBase54,gpuRangeFirst54,gpuRangeCount54);}
static void holiday_map_clock64(uint64_t utc){static uint64_t seen64=UINT64_MAX;uint64_t day=utc/86400;if(day==seen64)return;seen64=day;holidayMapMask64=seasonal_mask64(utc);}
int main(void){boss_wallclock53();FILE*hardwareTrace54=fopen("D:\\gpu-trace.on","rb");int trace54=hardwareTrace54!=NULL;if(hardwareTrace54)fclose(hardwareTrace54);pb_hardware_config54(trace54,hardware_report54);
 static FrameProfile50b frameProfile50b;uint64_t frameFrequency50b=KeQueryPerformanceFrequency();
 XVideoSetMode(640,480,32,REFRESH_DEFAULT);
 if(SDL_Init(SDL_INIT_GAMECONTROLLER)!=0)fail(SDL_GetError());if(pb_init()!=0)fail("GPU init failed");gpuReady=1;pb_show_front_screen();gpu_setup();
 campaign_admission_install194();guildVisit194=guild_world_visit194;guildRoomCompleted194=guild_world_completed194;guildRoomStyle194=guild_world_style194;regionalVisit194=regional_world_visit194;regionalReturn194=regional_world_return194;visualCacheRelease50=render_release54;worldHeapTrim183=heap_trim183;worldWaterRelease190=water_release190;worldSceneRelease200=campaign_reset200;campaignSessionReset200=campaign_reset200;combat_campaign_kill200=campaign_killed200;campaignJobGuard200=campaign_job_guard200;npc_campaign_page200=campaign_native_page200;combat_campaign_enemy200=party_enemy200;combat_friendly_heal200=campaign_friendly_heal200;combat_friendly_revive_ready200=campaign_friendly_revive_ready200;combat_friendly_revive200=campaign_friendly_revive200;combat_friendly_buff_ready200=campaign_friendly_buff_ready200;combat_friendly_buff200=campaign_friendly_buff200;combat_party_recover200=campaign_party_recover200;combat_party_needs_recovery200=campaign_party_needs_recovery200;campaignPartyDraw200=campaign_party_draw200;
 sound_init();world_blob_init();npcLegacyPortal181=portal_legacy181;sprite_load_all();art39_init();hud_init();skin_init();damage_init53();
 SDL_GameController*pad=NULL;for(int i=0;i<SDL_NumJoysticks();i++)if(SDL_IsGameController(i)){pad=SDL_GameControllerOpen(i);if(pad)break;}
 static TargetTrack41 targetTrack;static Art39State artState;static Combat game;
 static SaveStore saves;save_npc_setup55(&saves);saves.prepare=world_prepare;SDL_GameControllerUpdate();saves.recoverToCamp=0;
 npcSaveBridge55.utc=bossNow53>=UINT64_C(11644473600)?bossNow53-UINT64_C(11644473600):0;holiday_map_clock64(npcSaveBridge55.utc);int diskReady=save_disk_init(),saveError=0,confirmLoad=0,loadedCharacter52=0;if(diskReady)screen_load55();
 Autosave50b autosave50b={.choice=1,.newest=-1,.read=autosave_disk_read50b,.write=autosave_disk_write50b};if(diskReady)autosave_load50b(&autosave50b);else autosave50b.sessionOnly=1;
 if(diskReady)prefs_load56();
 frontRestart56:
 frontend_run56(&game,&saves,&pad,&autosave50b,diskReady);loadedCharacter52=1;saveError=0;
 world_town(&game);npc_native_init55(&game);sprite_set_equipment_sex60(class_actor_id50(game.jobId,game.mounted48),game.equipment,game.sex55);appearance_sprite58(&sprites[0],&game);
 cameraCurrent163=cameraStart65;
 float walkMeasured=0,walkDistance=0,walkSeconds=0;float yaw=0,tilt=.825f,zoom=camera_start_zoom180();int paused=0,overlay=0,aiming=0;unsigned aimedSkill=4;DeveloperUI devUI={0};int devOpen=developerSession56;paused=developerSession56;if(devOpen)dev_open(&devUI,&game);PauseUI pauseUI={0};pauseUI.allowTesting58=developerUnlocked56;WindowUI ui={0};QuickHold quickHold={0};StartShortcut startShortcut={0};RangedTest rangedTest={0};ui.observedLevel=game.level;ui.observedJob=game.joblevel;ui.hintStat=game.statPoints>0;ui.hintSkill=game.skillPoints>0;float aimX=game.x,aimY=game.y;InputRepeat numberRepeat={0},navigationRepeat={0};int jobTrainingDirty=0;unsigned previous=frontend_buttons56(pad),titleFadeOut56=0;int jobOpen=0,jobChoice=0,jobConfirm=0;MerchantUI merchantUI={0};int utilityChoice=0;int shopOpen=0,showHelp=!game.diagnosticsOff45,testWarpOpen=0,testWarpChoice=0;char lastMessage[100]={0};DWORD messageUntil=0;
 unsigned observedCamera65=cameraRevision65,observedGuardians162=guardianSprites162;
 DWORD last=GetTickCount(),fpsTime=last;unsigned frames=0,fps=0;int sceneryEnabled=(int)sceneryEnabled61;
 DWORD lastAuto=last,saveNotice=last;int noticeActive=1;
 frameProfile50b.audioPrevious=frameAudioTicks50b;
 for(;;){boss_wallclock53();npcSaveBridge55.utc=bossNow53>=UINT64_C(11644473600)?bossNow53-UINT64_C(11644473600):0;holiday_map_clock64(npcSaveBridge55.utc);
  uint64_t frameAt50b=frame_clock50b();
  SDL_Event e;while(SDL_PollEvent(&e)){
   if(e.type==SDL_CONTROLLERDEVICEADDED&&!pad)pad=SDL_GameControllerOpen(e.cdevice.which);
   if(e.type==SDL_CONTROLLERDEVICEREMOVED&&pad&&SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(pad))==e.cdevice.which){SDL_GameControllerClose(pad);pad=NULL;}
  }
  SDL_GameControllerUpdate();DWORD now=GetTickCount();npc_cache_frame183(&npcGame55,now);float frameSeconds=(now-last)/1000.f,dt=frameSeconds;last=now;if(dt>.05f)dt=.05f;
  unsigned buttons=0;
  if(button(pad,SDL_CONTROLLER_BUTTON_START))buttons|=1;
  if(button(pad,SDL_CONTROLLER_BUTTON_A))buttons|=2;
  if(button(pad,SDL_CONTROLLER_BUTTON_B))buttons|=4;
  if(button(pad,SDL_CONTROLLER_BUTTON_X))buttons|=8;
  if(button(pad,SDL_CONTROLLER_BUTTON_Y))buttons|=16;
  if(button(pad,SDL_CONTROLLER_BUTTON_LEFTSHOULDER))buttons|=32;
  if(button(pad,SDL_CONTROLLER_BUTTON_RIGHTSTICK))buttons|=64;
  if(button(pad,SDL_CONTROLLER_BUTTON_LEFTSTICK))buttons|=128;
  if(button(pad,SDL_CONTROLLER_BUTTON_BACK))buttons|=256;
  if(button(pad,SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))buttons|=512;
  if(button(pad,SDL_CONTROLLER_BUTTON_DPAD_UP))buttons|=1024;
  if(button(pad,SDL_CONTROLLER_BUTTON_DPAD_DOWN))buttons|=2048;
  if(button(pad,SDL_CONTROLLER_BUTTON_DPAD_LEFT))buttons|=4096;
  if(button(pad,SDL_CONTROLLER_BUTTON_DPAD_RIGHT))buttons|=8192;
  if(axis(pad,SDL_CONTROLLER_AXIS_TRIGGERLEFT)>.4f)buttons|=16384;
  if(axis(pad,SDL_CONTROLLER_AXIS_TRIGGERRIGHT)>.4f)buttons|=32768;
  int stylingPreview191=!paused&&shopOpen==2&&coreNpcUI53.npc>=0&&core_descriptor180(coreNpcUI53.npc)->kind==10;preview_turn191(&stylistTurn191,axis(pad,SDL_CONTROLLER_AXIS_RIGHTX),dt,stylingPreview191);
  menuRightSuppressed161=stylingPreview191||(!paused&&!shopOpen&&!jobOpen&&!game.utilityMenu&&ui.active&&!ui.inside&&!ui.placing&&ui.focus>=5);
  float windowRx161=0,windowRy161=0;
  if(menuRightSuppressed161&&!stylingPreview191){windowRx161=axis(pad,SDL_CONTROLLER_AXIS_RIGHTX);windowRy161=axis(pad,SDL_CONTROLLER_AXIS_RIGHTY);window_position_move161((unsigned)(ui.focus-5),windowRx161*120.f*dt,windowRy161*120.f*dt);}
  if(paused||ui.active||shopOpen||jobOpen||game.utilityMenu||confirmLoad)buttons|=menu_sticks61(pad);
  unsigned pressed=buttons&~previous;previous=buttons;if(titleFadeOut56)pressed=0;
  unsigned repeatMask=0,repeatContext=0;
  if(paused&&devOpen&&!devUI.confirm&&((devUI.tab<2&&devUI.row<2)||(devUI.tab==0&&(devUI.row==6||devUI.row==7)))){repeatMask=4096|8192;repeatContext=100+devUI.tab*10+devUI.row;}
  else if(paused&&!devOpen&&!testWarpOpen&&!confirmLoad&&pause_adjustable53(&pauseUI)){repeatMask=4096|8192;repeatContext=200+pauseUI.row;}
  else if(jobOpen&&!jobConfirm&&(jobChoice==7||jobChoice==8)){repeatMask=2;repeatContext=300+jobChoice;}
  else if(!paused&&ui.active&&ui.inside&&!ui.placing&&ui.focus==5&&ui.choice[0]>=0){repeatMask=2;repeatContext=400+ui.choice[0];}
  else if(!paused&&ui.active&&ui.inside&&!ui.placing&&ui.focus==8&&ui.skillPage&&ui.choice[3]>=0){repeatMask=8;repeatContext=500+ui.choice[3]+game.jobId*32;}
  pressed|=input_repeat(&numberRepeat,buttons,repeatMask,repeatContext,dt);
  unsigned navContext=game.utilityMenu?90:paused?(devOpen?(devUI.confirm?0:10+devUI.tab):testWarpOpen?20:confirmLoad?21:30+pauseUI.tab):shopOpen?40:jobOpen?(jobConfirm?0:50):ui.active?(60+ui.focus+ui.inside*10+ui.placing*20):0;
  unsigned navMask=navContext?(1024|2048|4096|8192):0;
  if(paused&&devOpen&&((devUI.tab<2&&devUI.row<2)||(devUI.tab==0&&(devUI.row==6||devUI.row==7))))navMask&=~(4096|8192);
  if(paused&&!devOpen&&!testWarpOpen&&!confirmLoad&&pause_adjustable53(&pauseUI))navMask&=~(4096|8192);
  pressed|=input_repeat(&navigationRepeat,buttons,navMask,navContext,dt);
  if(jobTrainingDirty&&(!(buttons&2)||!jobOpen||repeatContext<307||repeatContext>308)){jobTrainingDirty=0;if(diskReady&&npc_native_can_save55(&npcGame55)&&autosave_enabled50b(autosave50b.choice)){saveDiskError=0;saveError=!save_commit(&saves,&game);save_disk_feedback(&saves,saveError);lastAuto=now;}}
  unsigned menuBefore58=menu_signature58(&game,&ui,&pauseUI,&devUI,&merchantUI,&coreNpcUI53,&npcGame55,testWarpChoice,jobChoice,utilityChoice);
  ui_tick(&ui,&game,dt);
  unsigned quickActions=quick_hold_hints(&quickHold,buttons,dt,!paused&&!scene_ui_modal200()&&!ui.active&&!shopOpen&&!jobOpen&&!game.utilityMenu&&!(pressed&(1|256)),(ui.hintStat?1u:0u)|(ui.hintSkill?2u:0u));
  if(quickActions&4){ui_open(&ui,UI_STATUS,1);}
  if(quickActions&8){ui_open(&ui,UI_SKILLS,1);ui.skillPage=1;}
  int utilityWasOpen=game.utilityMenu!=0;int menuInput=utilityWasOpen||scene_ui_modal200()||paused||ui.active||shopOpen||jobOpen||(pressed&(1|256));
  if(pressed&1){if(pauseUI.editing61)pause_set61(&game,&autosave50b,pauseUI.tab,pauseUI.row,pauseUI.before61);pause_screen_cancel55(&pauseUI);sceneryEnabled=(int)sceneryEnabled61;game.utilityMenu=0;utilityChoice=0;devOpen=0;testWarpOpen=0;shopOpen=0;jobOpen=0;ui.active=0;ui.inside=0;ui.placing=0;paused=!paused;confirmLoad=0;if(paused){pauseUI.tab=0;pauseUI.row=pauseUI.detail=pauseUI.inside=0;}}
  else if(!paused&&scene_ui_modal200())scene_ui_input200(pressed,game.jobId);
  else if(!paused&&!shopOpen&&!jobOpen&&!game.utilityMenu&&(pressed&256)){ui.active=!ui.active;ui.inside=0;ui.placing=0;}

  else if(!paused&&!shopOpen&&!jobOpen&&!game.utilityMenu)ui_input(&ui,&game,pressed);
  if(developerUnlocked56&&start_shortcut_tick(&startShortcut,buttons&1,dt,(pressed&1)!=0,paused)){pauseUI.tab=P53_TESTING;pauseUI.row=pauseUI.detail=pauseUI.inside=0;devOpen=testWarpOpen=confirmLoad=0;}
  if(menuInput)aiming=0;
  if(utilityWasOpen&&!paused&&game.utilityMenu==63&&(pressed&(4096|8192))){int q=game.cartQuantity?game.cartQuantity:1;game.cartQuantity=(pressed&8192)?(q==1?10:q==10?100:1):(q==100?10:q==10?1:100);}
  if(utilityWasOpen&&!paused&&game.utilityMenu==503)campaign_party_input200(&game,pressed,&utilityChoice);
  else if(utilityWasOpen&&!paused&&game.utilityMenu==504)guild_ui_input194(&game,pressed,(unsigned)(dt*1000.f+.5f));
  else if(utilityWasOpen&&!paused){int n=skill_utility_rows(&game);if((pressed&16)&&game.utilityMenu==54){combat_memorize(&game);utilityChoice=0;}else if(pressed&4){game.utilityMenu=0;utilityChoice=0;combat_message(&game,"Menu closed. Pending choice cancelled.");}else if(n&&(pressed&1024))utilityChoice=(utilityChoice+n-1)%n;else if(n&&(pressed&2048))utilityChoice=(utilityChoice+1)%n;else if((pressed&8)&&game.utilityMenu==500){if(!homun_learn50(&game,utilityChoice-4))combat_message(&game,"Check Homunculus points, prerequisites and intimacy.");}else if(pressed&2){if(skill_utility_commit(&game,utilityChoice)&&!game.utilityMenu)utilityChoice=0;}}
  if(jobOpen){
   if(pressed&4){if(jobConfirm)jobConfirm=0;else jobOpen=0;}
   else if(pressed&1024){jobChoice=(jobChoice+12)%13;jobConfirm=0;}
   else if(pressed&2048){jobChoice=(jobChoice+1)%13;jobConfirm=0;}
   else if(pressed&2){int changed=0;
    if(jobChoice<7){if(!jobConfirm)jobConfirm=1;else{unsigned id=jobChoice<6?jobChoice+1:0;changed=combat_change_job(&game,id);jobConfirm=0;}}
    else if(jobChoice==7){int needed=job_next(&game);if(needed){combat_gain_exp(&game,0,needed-game.jexp);combat_message(&game,"TEST training: Job level %d.",game.joblevel);changed=1;}else combat_message(&game,"Job cap reached for this test class.");}
    else if(jobChoice==8){if(game.level<TEST_LEVEL_CAP){combat_gain_exp(&game,progression_base_curve43(game.jobId)[game.level-1]-game.exp,0);combat_message(&game,"TEST training: Base level %d.",game.level);changed=1;}else combat_message(&game,"Base cap250 reached for this test.");}
    else if(jobChoice==9){game.poisonLeft=30;game.poisonTick=0;combat_message(&game,"TEST poison applied. Exit and cast Detoxify to remove it.");}else if(jobChoice==10){if(inventory_count(&game,ITEM_BOW)==0)inventory_add(&game,ITEM_BOW,1);if(game.zeny<1000)game.zeny=1000;combat_message(&game,"TEST supplies: Bow and at least 1000 Zeny.");changed=1;}else if(jobChoice==11){game.home=(WorldPosition){game.mapId,game.x,game.y};combat_message(&game,"Home bound here in Prontera.");changed=1;}else jobOpen=0;
    if(changed&&(jobChoice==7||jobChoice==8))jobTrainingDirty=1;
    if(changed&&jobChoice!=7&&jobChoice!=8){sprite_set_equipment_sex60(class_actor_id50(game.jobId,game.mounted48),game.equipment,game.sex55);appearance_sprite58(&sprites[0],&game);if(diskReady&&npc_native_can_save55(&npcGame55)&&autosave_enabled50b(autosave50b.choice)){saveDiskError=0;saveError=!save_commit(&saves,&game);save_disk_feedback(&saves,saveError);saveNotice=now;noticeActive=1;lastAuto=now;}}
   }
  }
  if(shopOpen==3&&!paused)npc_game_input55(&npcGame55,pressed);
  if(shopOpen&&shopOpen!=3){int changed;if(shopOpen==2){changed=core_npc_input53(&coreNpcUI53,&game,pressed);if(coreNpcUI53.mode==-2){const Dungeon53*d=dungeons53+coreNpcUI53.destination;int fee=dungeonWarpFees53[d->tier];changed=0;const char*reason194=combatTravelAdmission194?combatTravelAdmission194(&game,d->map):NULL;if(reason194)combat_message(&game,"%s",reason194);else if(game.zeny>=fee&&world_test_warp(&game,d->map)){game.x=d->x;game.y=d->y;world_safe(&game.x,&game.y);game.zeny-=fee;changed=1;combat_message(&game,"Arrived at %s for %d Zeny.",d->name,fee);}coreNpcUI53.mode=-1;}if(coreNpcUI53.mode<0){shopOpen=0;if(coreNpcUI53.npc==CORE_NPC_COUNT53)core_trader_clear180();}}else{changed=merchant_input(&merchantUI,&game,pressed,merchantUI.mode==MS_STYLES?world_near_stylist(&game):world_near_merchant(&game));if(!merchantUI.mode)shopOpen=0;}if(changed&&diskReady&&npc_native_can_save55(&npcGame55)&&autosave_enabled50b(autosave50b.choice)){saveDiskError=0;saveError=!save_commit(&saves,&game);save_disk_feedback(&saves,saveError);saveNotice=now;noticeActive=1;lastAuto=now;}}
  if(menuInput&&paused){
   if(devOpen){CombatMob*practice=&game.mobs[MOB_COUNT-1];int before=practice->enabled?practice->kind:-1;if(dev_input(&devUI,&game,(pressed&~(32u|512u|16384u|32768u))|((pressed&16384u)?32u:0u)|((pressed&32768u)?512u:0u)))devOpen=0;if(gameRatesDirty164&&diskReady){if(prefs_save56())gameRatesDirty164=0;else snprintf(devUI.status,sizeof(devUI.status),"Rate settings could not be saved; changes remain active.");}int after=practice->enabled?practice->kind:-1;if(before!=after)sprite_test_target(activeMap,after);if(game.utilityTestWater){game.utilityTestWater=0;world_test_water(&game);snprintf(devUI.status,sizeof(devUI.status),"%.95s",game.log);}}else if(testWarpOpen){
    if(pressed&4)testWarpOpen=0;
    else if(pressed&4096)testWarpChoice=travel_region48(testWarpChoice,-1);
    else if(pressed&8192)testWarpChoice=travel_region48(testWarpChoice,1);
    else if(pressed&1024)testWarpChoice=travel_step48(testWarpChoice,-1);
    else if(pressed&2048)testWarpChoice=travel_step48(testWarpChoice,1);
    else if(pressed&2){
     if(world_test_warp(&game,testWarpChoice)){
      testWarpOpen=0;paused=0;aiming=0;aimX=game.x;aimY=game.y;
      if(diskReady&&npc_native_can_save55(&npcGame55)&&autosave_enabled50b(autosave50b.choice)){saveDiskError=0;saveError=!save_commit(&saves,&game);save_disk_feedback(&saves,saveError);saveNotice=now;noticeActive=1;lastAuto=now;}
     }else combat_message(&game,"Test warp destination unavailable.");
    }
   }else if(confirmLoad){
    int result=save_browser_input56(&saves,&game,pressed,diskReady);
    if(result==1){confirmLoad=0;saveNotice=now;noticeActive=1;lastAuto=now;aiming=0;}
    else if(result==2){titleFadeOut56=1;confirmLoad=0;}
   }else {
    if(!pauseUI.editing61)pauseUI.value61=pause_value61(&game,&autosave50b,pauseUI.tab,pauseUI.row);
    int action=pause_input(&pauseUI,pressed);
    if(action==PA_OPTION_PREVIEW61||action==PA_OPTION_CANCEL61){pause_set61(&game,&autosave50b,pauseUI.tab,pauseUI.row,pauseUI.value61);if(action==PA_OPTION_PREVIEW61&&pauseUI.tab==P53_AUDIO&&pauseUI.row>=6)sound_menu58();sceneryEnabled=(int)sceneryEnabled61;}
    if(action==PA_PREFS_SAVE58){if(pauseUI.tab==P53_GAMEPLAY&&pauseUI.row==4){autosave50b.pending=1;autosave50b.changedAt=now;lastAuto=now;}sceneryEnabled=(int)sceneryEnabled61;}
if(action==PA_AUTOLOOT58){autoLootOff58=!autoLootOff58;if(diskReady)prefs_save56();}
   if(action==PA_MENU_SOUND58){sound_menu_enabled58(!menuSoundEnabled58);if(diskReady)prefs_save56();}
    if(action==PA_PREFS_SAVE58){if(diskReady)prefs_save56();}
    if(action==PA_SCREEN_SAVE55){int stored=diskReady&&screen_save55();snprintf(saves.status,sizeof(saves.status),stored?"Screen adjustment saved.":"Screen adjustment is session-only; HDD write unavailable.");}
    if(action==PA_SAVE){save_browser_open56(1);confirmLoad=1;}
    else if(action==PA_TITLE56){save_browser_open56(3);confirmLoad=1;}
    else if(action==PA_AUTOSAVE_DOWN50B||action==PA_AUTOSAVE_UP50B){if(autosave_change50b(&autosave50b,action==PA_AUTOSAVE_UP50B?1:-1,now))lastAuto=now;}
    else if(action==PA_ATTACK_MODE52){game.autoAttackToggle52=!game.autoAttackToggle52;prefsAttack56=game.autoAttackToggle52;if(diskReady)prefs_save56();}
    else if(action==PA_VIEW_DOWN52||action==PA_VIEW_UP52){game.monsterView52=monster_view_step52(game.monsterView52,action==PA_VIEW_UP52?1:-1);prefsView56=game.monsterView52;if(diskReady)prefs_save56();}
    else if(action==PA_INVINCIBLE52&&!developerUnlocked56){snprintf(saves.status,sizeof(saves.status),"Developer Mode is locked.");}
    else if(action==PA_INVINCIBLE52){game.debugPlayerInvincible52=!game.debugPlayerInvincible52;snprintf(saves.status,sizeof(saves.status),"Player invincibility %s (this session).",game.debugPlayerInvincible52?"on":"off");}
    else if(action==PA_LOAD){save_browser_open56(2);confirmLoad=1;}
    else if(action==PA_MEMO){combat_memorize(&game);snprintf(saves.status,sizeof(saves.status),"%.95s",game.log);}
    else if((action==PA_TRAVEL||action==PA_DEV)&&!developerUnlocked56){snprintf(saves.status,sizeof(saves.status),"Developer Mode is locked.");}
    else if(action==PA_TRAVEL){npc_game_cancel55(&npcGame55);testWarpOpen=1;testWarpChoice=activeMap;game.autoAttack=0;}
    else if(action==PA_DEV){npc_game_cancel55(&npcGame55);devOpen=1;dev_open(&devUI,&game);game.autoAttack=0;}
    else if(action==PA_MERC180){game.utilityMenu=503;utilityChoice=0;campaign_party_ui_reset200();paused=0;}
    else if(action==PA_RESUME)paused=0;
    else if(action==PA_MUSIC_DOWN)sound_music_volume(-10);else if(action==PA_MUSIC_UP)sound_music_volume(10);
    else if(action==PA_SFX_DOWN)sound_effects_volume(-10);else if(action==PA_SFX_UP)sound_effects_volume(10);
    else if(action==PA_MUSIC_MUTE)sound_music_toggle();else if(action==PA_SFX_MUTE)sound_toggle();else if(action==PA_TONE)sound_test_tone();
    else if(action>=PA_POP_DAMAGE&&action<=PA_POP_LOOT){game.popupDisabled^=1u<<(action-PA_POP_DAMAGE);snprintf(saves.status,sizeof(saves.status),"Pop-up preference updated.");if(diskReady&&npc_native_can_save55(&npcGame55)&&autosave_enabled50b(autosave50b.choice)){saveDiskError=0;saveError=!save_commit(&saves,&game);save_disk_feedback(&saves,saveError);}}
    else if(action==PA_TOOLTIPS){game.tooltipsDisabled=!game.tooltipsDisabled;snprintf(saves.status,sizeof(saves.status),"Tooltips %s.",game.tooltipsDisabled?"off":"on");if(diskReady&&npc_native_can_save55(&npcGame55)&&autosave_enabled50b(autosave50b.choice)){saveDiskError=0;saveError=!save_commit(&saves,&game);save_disk_feedback(&saves,saveError);}}
    else if(action==PA_HELP){showHelp=!showHelp;game.diagnosticsOff45=!showHelp;}else if(action==PA_SCENERY)sceneryEnabled=!sceneryEnabled;
    if(diskReady&&action>=PA_MUSIC_DOWN&&action<=PA_SFX_MUTE)prefs_save56();
   }
  }

  if(!paused&&!scene_ui_modal200()){npc_game_tick55(&npcGame55,(unsigned)(dt*1000.f+.5f),npcSaveBridge55.utc);unsigned npcClip64;while(npc_audio_pop64(&npcGame55.audio64,&npcClip64))sound_play(SOUND_NPC_FIRST64+npcClip64);npc_proc_tick180(&npcGame55);if(npcGame55.musicRequest64[0]){for(unsigned t64=0;t64<MUSIC_TRACKS;t64++)if(!strcmp(musicNames[t64],npcGame55.musicRequest64)){sound_music_track58((int)t64);break;}npcGame55.musicRequest64[0]=0;}if(npc_native_ui55())shopOpen=3;else if(shopOpen==3)shopOpen=0;}
  questPlayer194=&game;campaign_world_bind200(&game);if(activeMap==494&&(guildRoomLoadedMask194!=guild_world_completed194()||guildRoomLoadedStyle194!=guild_world_style194())){activeMap=~0u;if(world_activate(494)){world_safe(&game.x,&game.y);world_town(&game);}}
  if(autosave50b.pending&&(!(paused&&!devOpen&&!testWarpOpen&&!confirmLoad&&pause_autosave53(&pauseUI))||autosave_pending50b(&autosave50b,now,buttons&(4096|8192)))){if(diskReady&&autosave_commit50b(&autosave50b))snprintf(saves.status,sizeof(saves.status),"Autosave %s; preference remembered.",autosaveNames50b[autosave50b.choice]);else{autosave50b.pending=0;autosave50b.sessionOnly=1;snprintf(saves.status,sizeof(saves.status),"Autosave preference not stored; session only.");}}
  if(!paused&&!ui.active&&!shopOpen&&!jobOpen&&!game.utilityMenu&&(pressed&128)&&game.hp>0){if(!game.sitting&&skill_rank(&game,338)<3)combat_message(&game,"Learn Basic Skill level 3 to sit.");else if(game.hideLeft>0)combat_message(&game,"B or Hiding: emerge before sitting.");else{game.sitting=!game.sitting;game.autoAttack=0;aiming=0;combat_tip(&game,game.sitting?"Sitting: faster HP/SP recovery. L3 to stand.":"Standing.");}}
  if(!paused&&!ui.active&&!shopOpen&&!jobOpen&&pad&&!menuInput){
   if(hotbar_input53(&game,pressed)){
    aiming=0;noticeActive=0;
   }
   if(pressed&4){if(aiming){aiming=0;combat_message(&game,"Ground targeting cancelled; SP kept.");}else combat_cancel(&game);noticeActive=0;}
   {int step=target_button47a(pressed);if(step!=2)target_select58(&game,step,yaw,tilt,zoom);}
   if(pressed&2){
    unsigned id=aiming?aimedSkill:hot_binding(&game);noticeActive=0;
    if(id==0&&(game.autoAttack||game.floorGather60||ground_live58(&game,game.floorTarget58))){combat_attack(&game);aiming=0;}
    else if(id!=0&&ground_activate58(&game)){aiming=0;}
    else if(game.hideLeft>0){if(id==38||id==130||id==132||id==144||id==SK60_NJ_SHADOWJUMP||id==SK60_NJ_KIRIKAGE)skill_cast(&game,id,aimX,aimY);else combat_message(&game,"B or Hiding: emerge before interacting.");}
    else if(game.sitting){int item=binding_item(id);if(item>=0)inventory_action(&game,item);else combat_message(&game,"Press L3 to stand before moving or using skills.");}
    else if(combat_portal_near(&game)>=0){int k=combat_portal_near(&game);const char*reason194=combatTravelAdmission194?combatTravelAdmission194(&game,game.portals[k].destination.map):NULL;if(reason194)combat_message(&game,"%s",reason194);else{game.travel=game.portals[k].destination;game.portals[k].uses--;game.travelRequest=1;}aiming=0;}
    else if(world_near_gate(&game)){
     world_travel(&game);aiming=0;aimX=game.x;aimY=game.y;
     if(diskReady&&npc_native_can_save55(&npcGame55)&&autosave_enabled50b(autosave50b.choice)){saveDiskError=0;saveError=!save_commit(&saves,&game);save_disk_feedback(&saves,saveError);saveNotice=now;noticeActive=1;lastAuto=now;}
    }
    else if(near_pending(&game)){combat_message(&game,"That red warp leads to an area not connected in this build.");}
    else if(guild_open194(questPins65)&&guild_near194(&game)){guild_ui_open194(&game);aiming=0;}
    else if(regional_near194(questPins65,&game)>=0){regional_ui_open194(&game,(unsigned)regional_near194(questPins65,&game));aiming=0;}
    else if(campaign_world_near200()>=0){campaign_world_interact200();aiming=0;}
    else if(npc_game_near55(&npcGame55)>=0){unsigned record180=(unsigned)npc_game_near55(&npcGame55);if(npcRecords55[record180].kind==2){if(npc_trader_open180(&npcGame55,&coreNpcUI53,record180))shopOpen=2;}else if(npc_game_open55(&npcGame55,record180))shopOpen=3;aiming=0;}
    else if(core_npc_near53(&game)>=0){core_npc_open53(&coreNpcUI53,&game,core_npc_near53(&game));shopOpen=2;aiming=0;}
    else if(game.hp<=0){aiming=0;combat_attack(&game);}
    else if(binding_item(id)>=0){inventory_action(&game,binding_item(id));}
    else if(combat_casting(&game)){combat_message(&game,"Casting; B or movement cancels.");}
    else if(skill_ground(id)&&!aiming){
     aiming=1;aimedSkill=id;aimX=game.x;aimY=game.y;
     if(id!=48&&id!=53&&id!=54&&combat_valid_target(&game,game.target)){aimX=game.mobs[game.target].x;aimY=game.mobs[game.target].y;}
     combat_message(&game,"R stick: aim ground. A: cast. B: cancel.");
    }else if(skill_cast(&game,id,aimX,aimY)){aiming=0;}
   }
   for(int quick=0;quick<2;quick++)if(quickActions&(1u<<quick)){
    unsigned binding=quick_binding(&game,quick);int item=binding_item(binding);if(binding!=0&&ground_activate58(&game)){aiming=0;continue;}
    if(binding==BIND_EMPTY50)combat_message(&game,"%s is empty. Assign an item or skill in Select.",quick?"RB":"LB");
    else if(item>=0)inventory_action(&game,item);
    else if(game.hideLeft>0&&binding!=38&&binding!=130&&binding!=132&&binding!=144)combat_message(&game,"B or Hiding: emerge before casting.");
    else if(game.sitting)combat_message(&game,"Press L3 to stand before casting.");
    else if(combat_casting(&game))combat_message(&game,"Casting; B or movement cancels.");
    else if(skill_ground(binding)&&(!aiming||aimedSkill!=binding)){aiming=1;aimedSkill=binding;aimX=game.x;aimY=game.y;if(binding!=48&&binding!=53&&binding!=54&&combat_valid_target(&game,game.target)){aimX=game.mobs[game.target].x;aimY=game.mobs[game.target].y;}combat_message(&game,"Right stick: aim. A or quick button: cast. B: cancel.");}
    else if(skill_cast(&game,binding,aimX,aimY))aiming=0;
   }
   if(aiming){
    float rx=axis(pad,SDL_CONTROLLER_AXIS_RIGHTX),ry=axis(pad,SDL_CONTROLLER_AXIS_RIGHTY);
    aimX+=(cosf(yaw)*rx+sinf(yaw)*ry)*dt*100;aimY+=(sinf(yaw)*rx-cosf(yaw)*ry)*dt*100;
    ground_cursor_clamp(&aimX,&aimY,game.x,game.y,skill_ground_range(&game,aimedSkill),gw,gh);
   }else {yaw-=axis(pad,SDL_CONTROLLER_AXIS_RIGHTX)*dt*1.5f;tilt+=axis(pad,SDL_CONTROLLER_AXIS_RIGHTY)*dt*.6f;}
   if(tilt<.459f)tilt=.459f;if(tilt>1.13f)tilt=1.13f;
   zoom+=(axis(pad,SDL_CONTROLLER_AXIS_TRIGGERRIGHT)-axis(pad,SDL_CONTROLLER_AXIS_TRIGGERLEFT))*dt*.6f;
   zoom=view_zoom_clamp54(zoom);cameraCurrent163=(unsigned)(1.f+(zoom-.85f)*99.f/5.15f+.5f);
  }
  if(observedCamera65!=cameraRevision65){zoom=camera_zoom65(cameraCurrent163);observedCamera65=cameraRevision65;}zoom=view_zoom_clamp54(zoom);cameraCurrent163=(unsigned)(1.f+(zoom-.85f)*99.f/5.15f+.5f);
  if(observedGuardians162!=guardianSprites162){while(pb_busy()){}sprite_release_enemies();gpu_stream_reset51();guardian_reset51();game.creatureAssetsChanged52=1;renderer_species_sync52(&game);memset(guardianMotion53,0,sizeof(guardianMotion53));observedGuardians162=guardianSprites162;}
  float co=cosf(yaw),si=sinf(yaw),ct=cosf(tilt),sn=sinf(tilt);
  float dx=axis(pad,SDL_CONTROLLER_AXIS_LEFTX),dy=axis(pad,SDL_CONTROLLER_AXIS_LEFTY),length=sqrtf(dx*dx+dy*dy);if(length>1){dx/=length;dy/=length;}
  float oldX=game.x,oldY=game.y;int ownsInput=ui.active||shopOpen||jobOpen||game.utilityMenu||menuInput||!pad;
  waterTime190=game.time;game.canSpecies52=renderer_can_species52;static DWORD lastCalendar52;if(!game.calendarMonth52||GetTickCount()-lastCalendar52>60000){SYSTEMTIME clock52;GetLocalTime(&clock52);game.calendarDay52=clock52.wDay;game.calendarMonth52=clock52.wMonth;lastCalendar52=GetTickCount();}
  if(game.fxSkill==131&&game.attackAt<=game.lastCast){unsigned frames=sprites[0].meta[(16+facing(game.faceX,game.faceY,co,si))*3+1];float remaining=game.lastCast+.45f+7*frames*.030f-game.time;if(remaining>game.moveLock45)game.moveLock45=remaining;}
  game.attackPaused52=aiming||shopOpen||jobOpen||game.utilityMenu;session_world_tick43(&game,dt,paused||scene_ui_modal200(),ownsInput,co*dx+si*dy,si*dx-co*dy);
  rescue_tick200(&campaignRescue200,dt,paused||scene_ui_modal200());campaign_party_bind200(&game);campaign_battle_tick200(&game,dt,paused||scene_ui_modal200());campaign_follow_tick200(&campaignParty200,&game,dt,paused||scene_ui_modal200());
  renderer_species_sync52(&game);
  if(!paused&&!ownsInput){if(aiming)ground_cursor_follow(&aimX,&aimY,oldX,oldY,game.x,game.y,skill_ground_range(&game,aimedSkill),gw,gh);walkDistance+=combat_dist(oldX,oldY,game.x,game.y);walkSeconds+=frameSeconds;if(walkSeconds>=.5f){walkMeasured=walkDistance/walkSeconds;walkDistance=walkSeconds=0;}}else{walkMeasured=walkDistance=walkSeconds=0;}
  ranged_test_tick(&rangedTest,&game,dt,!paused&&!scene_ui_modal200());
  if(game.hp<=0)aiming=0;
  if(!paused&&!ui.active&&!shopOpen&&!jobOpen&&pad&&diskReady&&npc_native_can_save55(&npcGame55)&&autosave_due50b(autosave50b.choice,now,lastAuto)){
   lastAuto=now;
   if(save_dirty(&saves,&game)){saveDiskError=0;saveError=!save_commit(&saves,&game);save_disk_feedback(&saves,saveError);saveNotice=now;noticeActive=1;}
  }
  if(game.travelRequest){world_skill_travel(&game);aiming=0;aimX=game.x;aimY=game.y;if(diskReady&&npc_native_can_save55(&npcGame55)&&autosave_enabled50b(autosave50b.choice)){saveDiskError=0;saveError=!save_commit(&saves,&game);save_disk_feedback(&saves,saveError);lastAuto=now;}}
  if(devUI.rangedRequest){devUI.rangedRequest=0;ranged_test_arm(&rangedTest,&game);devOpen=0;paused=0;combat_message(&game,"Practice ranged hit in 1 second after resume.");}
  if(devUI.previewRequest){devUI.previewRequest=0;art39Preview=devUI.preview;art39_load_clip45(art39Preview<20?art39Preview:art39Preview>=21?art39Preview-1:ART39_COUNT);art39PreviewAt=game.time;devOpen=0;paused=0;}
  if((pressed&(1024|2048|4096|8192|32|512|16384|32768))&&menuBefore58!=menu_signature58(&game,&ui,&pauseUI,&devUI,&merchantUI,&coreNpcUI53,&npcGame55,testWarpChoice,jobChoice,utilityChoice))sound_menu58();
  frame_span50b(&frameProfile50b,FRAME_UPDATE50B,frame_clock50b(),&frameAt50b);
  spriteDualGear50=class_dual_gear50(&game);sprite_set_equipment_sex60(class_actor_id50(game.jobId,game.mounted48),game.equipment,game.sex55);Appearance58 renderedAppearance58=stylist_preview58(&coreNpcUI53,&game,shopOpen==2);if(!appearance_equal58(sprites[0].appearance58,renderedAppearance58)||sprites[0].sex58!=game.sex55){sprites[0].appearance58=renderedAppearance58;sprites[0].sex58=game.sex55;spriteEpoch++;}if(art39Preview>=0&&game.time-art39PreviewAt>=8){art39Preview=-1;art45Job=~0u;}art50Copy=game.persistent50.copySkill;art39_prepare45(game.jobId,game.cartStyle);art39_tarot_prepare52(&game);
  companion_prepare50(&game);class_sound_prepare50(&game);class_sound_song50(&game);
  art39_observe(&artState,&game,activeMap);
  float x=game.x,y=game.y,z=height_at(x,y);
  static float cameraHeight53,cameraX53,cameraY53;static unsigned cameraMap53=~0u;if(cameraMap53!=activeMap||combat_dist(cameraX53,cameraY53,x,y)>128){cameraHeight53=z;cameraMap53=activeMap;}else cameraHeight53+=(z-cameraHeight53)*fminf(1,frameSeconds*10);cameraX53=x;cameraY53=y;float matrix[16];world_camera(matrix,x,y,cameraHeight53,yaw,tilt,zoom);npc_proc_camera180(&npcGame55,matrix);rooms_focus181(&interiorRooms181,game.x,game.y);float actorDepthSlope50=sprite_depth_slope50(matrix);
  DrawActor actors[RENDER_MOBS+30];int actorCount=0;
  int dir=(game.jobId==J52_SUPER_NOVICE||game.jobId>=J60_NINJA)?facing_stable45(&playerFacing164,activeMap,game.jobId+1,game.faceX,game.faceY,co,si):facing(game.faceX,game.faceY,co,si),group=0;float elapsed=game.time,duration=0;int repeat=0;
  if(game.hp<=0||game.trickDead55){group=4;elapsed=game.time-game.deadAt;duration=1;repeat=0;}
  else if(combat_casting(&game)){group=game.jobId>=12?7:6;elapsed=game.spellCastTotal-game.spellCastLeft;duration=game.spellCastTotal;}
  else if(game.fxSkill==64&&game.time-game.lastCast<.45f){group=2;elapsed=game.time-game.lastCast;duration=.45f;}
  else if(game.time-game.lastCast<.45f&&(((game.jobId==2||game.jobId==8||game.jobId==9||game.jobId==10)&&(game.fxSkill==3||game.fxSkill==9||((game.fxSkill>=21&&game.fxSkill<=24)||game.fxSkill==29||game.fxSkill==30||game.fxSkill==31||game.fxSkill==36||game.fxSkill==48||game.fxSkill==49||game.fxSkill==67)))||((game.jobId>=3&&game.jobId<=6||game.jobId==8)&&(game.fxSkill==5||game.fxSkill==6||game.fxSkill==10||game.fxSkill==14||game.fxSkill>=40)))){group=6;elapsed=game.time-game.lastCast;duration=.45f;}
  else if(sonic_pose50c(&game,&sprites[0],dir,&elapsed,&duration)){group=2;repeat=0;}
  else if(game.time-game.attackAt<COMBAT_ATTACK_ANIMATION53){group=2;elapsed=game.time-game.attackAt;duration=COMBAT_ATTACK_ANIMATION53;}
  else if(game.time-game.hurtAt<.24f){group=3;elapsed=game.time-game.hurtAt;duration=.24f;}
  else if(game.sitting){group=5;repeat=0;}
  else if(game.moving){group=1;repeat=1;}
  else if(game.autoAttack&&(game.equipment&49)){group=7;repeat=1;}
  dir=npc_proc_direction180(&npcGame55,1,0,dir);int cartDir=dir;if(game.hp>0&&game.fxSkill==64&&game.time-game.lastCast>=0&&game.time-game.lastCast<.45f)dir=(dir+(int)((game.time-game.lastCast)*8/.45f))%8;
  {float walk=walk_phase62(&expandedWalk62,game.x,game.y,game.time,game.mapId,game.jobId,group==1);if(group==1&&(game.jobId==J52_SUPER_NOVICE||(game.jobId>=J60_NINJA&&game.jobId<=J60_SOUL_LINKER)))elapsed=walk;}
  head_prepare54(&game);HeadPose54 playerHeadPose54=head_pose54(&sprites[0],group,dir,elapsed,duration,repeat);head_frames54(playerHeadPose54,game.time);
  float contactX,contactY;world_project(matrix,x,y,z,&contactX,&contactY);
  actors[actorCount++]=(DrawActor){0,0,sprite_frame(&sprites[0],group,dir,elapsed,duration,repeat),contactX+player_contact60(class_actor_id50(game.jobId,game.mounted48),game.sex55,dir)[0]*zoom/3.f,contactY+player_contact60(class_actor_id50(game.jobId,game.mounted48),game.sex55,dir)[1]*zoom/3.f,WORLD_DEPTH_CENTRE-WORLD_SPRITE_BIAS};
  water_actor_mark54(&actors[actorCount-1],matrix,x,y,z);
  const DrawActor*playerDraw=&actors[0];DrawActor quickenPlayer45=*playerDraw;const unsigned*playerCrop=sprites[0].directory+playerDraw->frame*5;
  unsigned playerBounds58[4];appearance_bounds58(&sprites[0],playerDraw->frame,0,playerBounds58);float castHeadX=playerDraw->x,castHeadTop=playerDraw->y+((float)playerBounds58[1]-sprites[0].anchorY)*zoom/3.f;
  CartPose40 cartPose;int cartReady=cart_pose40(&game,matrix,zoom,cartDir,height_at,&cartPose);CartPose40 storyCartPose;int storyCartReady=campaign_cart_pose200(&game,matrix,co,si,zoom,&storyCartPose);
  float targetX=-100,targetY=-100;TargetBounds41 targetBounds={0};int targetReady=0;
  /* Bound GPU sprite storage; choose nearest on-screen monsters first. */
  int visible[RENDER_MOBS],visibleCount=monster_select180(&game,matrix,x,y,visible,height_at);
  memset(guardianDraw51,0,sizeof(guardianDraw51));
  int visibleSlots45[RENDER_MOBS];unsigned visibleLives45[RENDER_MOBS];for(int vi=0;vi<visibleCount;vi++)visibleLives45[vi]=game.mobs[visible[vi]].life;sprite_slots45(&mobSlots45,activeMap,visible,visibleLives45,visibleCount,visibleSlots45);
  for(int vi=0;vi<visibleCount;vi++){int i=visible[vi];CombatMob*m=&game.mobs[i];
   float zz=height_at(m->x,m->y),px=matrix[0]*m->x+matrix[1]*m->y+matrix[3],py=matrix[4]*m->x+matrix[5]*m->y+matrix[6]*zz+matrix[7];
   float depth=matrix[8]*m->x+matrix[9]*m->y+matrix[10]*zz+matrix[11]-WORLD_SPRITE_BIAS;
   if(i==game.target){targetX=px;targetY=py;}
   if(px< -100||px>740||py< -100||py>580)continue;
   group=0;duration=0;elapsed=game.time+i*.217f;repeat=1;
   if(m->hp<=0){group=4;elapsed=game.time-m->deadAt;duration=1;repeat=0;}
   else if(game.time-m->hurtAt<.2f){group=3;elapsed=game.time-m->hurtAt;duration=.2f;repeat=0;}
   else if(game.time-m->attackAt<mobSpecs[m->kind].motion){group=2;elapsed=game.time-m->attackAt;duration=mobSpecs[m->kind].motion;repeat=0;}
   else if(m->moving)group=1;
   if(m->frozenLeft>0||m->stoneLeft>0){group=0;elapsed=0;repeat=0;}
   dir=facing_stable45(&mobFacing45[i],activeMap,m->life,m->faceX,m->faceY,co,si);
   dir=npc_proc_direction180(&npcGame55,NPC_MOB_ENTITY172+i+1,m->life,dir);unsigned guardianBank162=guardian_bank162(m->kind);if(guardianBank162){GuardianPose53 pose=guardian_motion_rate162(&guardianMotion53[i],&game,m,guardianBank162,guardian_attack_rate164(&game,m,guardianBank162));if(guardianSprites162){group=pose.group;elapsed=pose.elapsed;duration=0;repeat=pose.repeat;}else guardianDraw51[visibleSlots45[vi]]=(GuardianDraw51){guardianBank162,pose.group,pose.elapsed,0,m->x,m->y,zz,pose.fx,pose.fy,pose.repeat};}
   actors[actorCount++]=(DrawActor){visibleSlots45[vi],m->kind+1,sprite_frame(&sprites[m->kind+1],group,dir,elapsed,duration,repeat),px,py,depth,0,m->hp<=0&&sprites[m->kind+1].alpha4444};
   actors[actorCount-1].scale60=m->hp>0&&m->class50.swooUntil60>game.time?.5f:1;if(guardianBank162&&guardianSprites162)actors[actorCount-1].scale60*=guardianSpriteScale162[guardianBank162-7];
   if(sprites[m->kind+1].guardian51)guardianDraw51[visibleSlots45[vi]].scale60=actors[actorCount-1].scale60;
   water_actor_mark54(&actors[actorCount-1],matrix,m->x,m->y,zz);
   if(i==game.target)targetReady=target_bounds41(&targetTrack,i,m->life,sprites[m->kind+1].directory+actors[actorCount-1].frame*5,sprites[m->kind+1].anchorX,sprites[m->kind+1].anchorY,px,py,zoom/3.f*actors[actorCount-1].scale60,dt,&targetBounds);
  }
  mercenary_actors180(&game,matrix,co,si,zoom,actors,&actorCount);companion_actors50(&game,matrix,co,si,zoom,actors,&actorCount);
  // Far-to-near transparency ordering; terrain depth still occludes billboards.
  core_npc_actors53(&game,matrix,co,si,actors,&actorCount);npc_render_actors55(&game,matrix,co,si,actors,&actorCount);campaignStageModal200=scene_ui_modal200();campaign_actor_collect200(&game,matrix,co,si,zoom,actors,&actorCount);
  for(int i=1;i<actorCount;i++){DrawActor a=actors[i];int j=i;while(j>0&&actors[j-1].depth<a.depth){actors[j]=actors[j-1];j--;}actors[j]=a;}
  if(saves.operationResult58>0)saveError=0;else if(saves.operationResult58<0)saveError=1;
  sound_drain(&game);
  frame_span50b(&frameProfile50b,FRAME_PREPARE50B,frame_clock50b(),&frameAt50b);
  pb_wait_for_vbl();pb_target_back_buffer();pb_reset();while(pb_busy()){}unsigned char usedGpu183[SPRITE_SLOT_COUNT]={1};for(int i=0;i<actorCount;i++)usedGpu183[actors[i].slot]=1;gpu_entity_frame183(now,usedGpu183);effect_cache_frame183(now);art_cache_frame183(now);enemy_cache_frame183(now);death_sound_frame183(now);heap_frame183(now);campaign_portrait_prepare200(&npcGame55);water_prepare_view190(matrix,activeMap);gpu_program_frame51();
  if(titleFadeOut56>=180){npc_portrait_release171();npc_game_clear55(&npcGame55);npc_variables_clear55(&npcVariables55);npc_state_clear55(&npcQuests55);npcSaveBridge55.canSave=NULL;npcSaveBridge55.saveContext=NULL;npcSaveBridge55.hasClean=0;bank_cache_clear56();world_release();activeMap=~0u;game.autoAttack=0;goto frontRestart56;}
  frame_span50b(&frameProfile50b,FRAME_WAIT50B,frame_clock50b(),&frameAt50b);
  /* Match the black backside tiles: unpainted map space must not reveal guide markings. */
  pb_fill(0,0,640,480,0xff000000);gpu_depth_state(1);pb_erase_depth_stencil_buffer(0,0,640,480);
  uint64_t drawAt51=frame_clock50b();
  spriteQuickenPlayer45=game.quickenLeft>0&&game.hp>0;spriteBerserkPlayer45=combat_berserk_active(&game);spriteHiddenPlayer=(game.hideLeft>0||class_active50(&game,130)||class_active50(&game,SK52_ST_CHASEWALK))&&game.hp>0;spriteCoatedPlayer=game.energyCoatLeft>0&&game.hp>0;memset(spriteFlash49,0,sizeof(spriteFlash49));spriteFlash49[0]=trans_flash52(game.fxSkill,game.time-game.fxAt);for(int vi=0;vi<visibleCount;vi++){const CombatMob*t=&game.mobs[visible[vi]];float age=game.time-t->flashAt49;if(t->flashAt49>0&&age>=.5f&&age<1){unsigned seed=(unsigned)(age*20)*0x9e3779b9u+t->life;spriteFlash49[visibleSlots45[vi]]=0x808080u|(seed&0x7f7f7fu);}}memset(spriteFrozen,0,sizeof(spriteFrozen));for(int vi=0;vi<visibleCount;vi++)spriteFrozen[visibleSlots45[vi]]=game.mobs[visible[vi]].frozenLeft>0;memset(spriteStone,0,sizeof(spriteStone));for(int vi=0;vi<visibleCount;vi++)spriteStone[visibleSlots45[vi]]=game.mobs[visible[vi]].stoneLeft>0;memset(spritePoison,0,sizeof(spritePoison));spritePoison[0]=game.poisonLeft>0&&game.hp>0;for(int vi=0;vi<visibleCount;vi++)spritePoison[visibleSlots45[vi]]=game.mobs[visible[vi]].poisonLeft>0&&game.mobs[visible[vi]].hp>0;
  unsigned visualEntities180[SPRITE_SLOT_COUNT]={0},visualLives180[SPRITE_SLOT_COUNT]={0};visualEntities180[0]=1;
  for(int vi=0;vi<visibleCount;vi++){unsigned slot=visibleSlots45[vi],mob=visible[vi];visualEntities180[slot]=NPC_MOB_ENTITY172+mob+1;visualLives180[slot]=game.mobs[mob].life;}
  for(int i=0;i<actorCount;i++){DrawActor*a=&actors[i];if(a->kind>=SCRIPT_NPC_KIND55&&a->kind<SCRIPT_NPC_KIND55+SCRIPT_NPC_SLOTS55)visualEntities180[a->slot]=NPC_ENTITY_BASE55+scriptNpcRecords55[a->kind-SCRIPT_NPC_KIND55]+1;unsigned flash=npc_proc_flash180(&npcGame55,visualEntities180[a->slot],visualLives180[a->slot]);if(flash)spriteFlash49[a->slot]=flash;sprite_upload(actor_shape50(a->kind),a->frame,a->slot);}
  campaign_actor_prepare200();head_upload54();stylist_prepare191(stylingPreview191);guardian_prepare51();npcHaloQuads180=0;
  quicken_record45(&game,&quickenPlayer45,cartDir);
  frame_draw_span51(&frameProfile50b,DRAW_UPLOAD51,frame_clock50b(),&drawAt51);
  gpu_ground(matrix,(int)(x/16),(int)(y/16),1);
  frame_draw_span51(&frameProfile50b,DRAW_TERRAIN51,frame_clock50b(),&drawAt51);
  sceneFocusX61=game.x;sceneFocusY61=game.y;if(sceneryEnabled)scenery_draw(matrix,activeMap);trap_draw50(&game,matrix);
  ground_draw58(&game,matrix,zoom,actorDepthSlope50);campaign_parcel_draw200(&game,matrix,zoom,actorDepthSlope50);campaign_document_draw200(&game,matrix,zoom,actorDepthSlope50);regional_document_draw194(&game,matrix,zoom,actorDepthSlope50);
  frame_draw_span51(&frameProfile50b,DRAW_SCENERY51,frame_clock50b(),&drawAt51);
  for(int i=0;i<actorCount;i++){DrawActor*a=&actors[i];if(!a->water54)continue;if(actor_shape50(a->kind)->guardian51){guardian_draw51(a->slot,matrix);continue;}spriteClipLow54=a->waterline54;spriteClipHigh54=1e9f;if((a->kind>=NPC_KIND53&&a->kind<NPC_KIND53+NPC_CACHE_COUNT53)||(a->kind>=SCRIPT_NPC_KIND55&&a->kind<SCRIPT_NPC_KIND55+SCRIPT_NPC_SLOTS55))gpu_npc_sprite182(entityTextures[a->slot],actor_shape50(a->kind),a->x,a->y,a->depth,npc_actor_scale55(a->kind,zoom),a->groundY,actorDepthSlope50,(matrix[8]*matrix[4]+matrix[9]*matrix[5])/(matrix[4]*matrix[4]+matrix[5]*matrix[5]));else gpu_actor_sprite50c(entityTextures[a->slot],actor_shape50(a->kind),a->x,a->y,a->depth,npc_actor_scale55(a->kind,zoom)*(a->scale60>0?a->scale60:1),a->kind==0?contactY:a->kind>=COMPANION_KIND50?a->groundY:a->y,actorDepthSlope50,a->sourceFade50c);if(a->kind==0)head_draw54(playerHeadPose54,a->x,a->y,a->depth,zoom/3.f,contactY,actorDepthSlope50);sprite_clip_reset54();}
  water_draw(matrix,activeMap);
  portal_draw61(&game,matrix,activeMap);
  spell_world_draw41(&game,&artState,matrix,aiming,aimedSkill,aimX,aimY);
  ice_draw48(&game,matrix);field_draw48(&game,&artState,matrix);
  for(int wall=0;wall<3;wall++)if(combat_safety_live(&game,wall)){const SafetyWall*w=game.safety+wall;float wx=game.x-w->x,wy=game.y-w->y;if(wx*wx+wy*wy>5.6f*5.6f&&matrix[8]*(w->x-game.x)+matrix[9]*(w->y-game.y)>=0)art39_world(41,game.time-w->createdAt49,matrix,w->x,w->y,zoom,0);}
  art39DrawCount=0;
  frame_draw_span51(&frameProfile50b,DRAW_WORLD51,frame_clock50b(),&drawAt51);


  for(int i=0;i<actorCount;i++){DrawActor*a=&actors[i];if(storyCartReady&&storyCartPose.depth>=a->depth){art39_one(10,0,storyCartPose.sx,storyCartPose.sy,storyCartPose.depth,zoom/3,1,0,storyCartPose.dir);storyCartReady=0;}if(cartReady&&cartPose.depth>=a->depth){art39_one(10+cartPose.style,cartPose.elapsed,cartPose.sx,cartPose.sy,cartPose.depth,zoom/3,1,game.moving?1:0,cartPose.dir);cartReady=0;}if(a->kind==0)quicken_draw45(&game,matrix,zoom);if(actor_shape50(a->kind)->guardian51){if(!a->water54)guardian_draw51(a->slot,matrix);continue;}if(a->water54)spriteClipHigh54=a->waterline54;npc_halo_draw180(&npcGame55,visualEntities180[a->slot],visualLives180[a->slot],a,actor_shape50(a->kind),npc_actor_scale55(a->kind,zoom)*(a->scale60>0?a->scale60:1),a->kind==0?contactY:a->kind>=COMPANION_KIND50?a->groundY:a->y,actorDepthSlope50);if((a->kind>=NPC_KIND53&&a->kind<NPC_KIND53+NPC_CACHE_COUNT53)||(a->kind>=SCRIPT_NPC_KIND55&&a->kind<SCRIPT_NPC_KIND55+SCRIPT_NPC_SLOTS55))gpu_npc_sprite182(entityTextures[a->slot],actor_shape50(a->kind),a->x,a->y,a->depth,npc_actor_scale55(a->kind,zoom),a->groundY,actorDepthSlope50,(matrix[8]*matrix[4]+matrix[9]*matrix[5])/(matrix[4]*matrix[4]+matrix[5]*matrix[5]));else gpu_actor_sprite50c(entityTextures[a->slot],actor_shape50(a->kind),a->x,a->y,a->depth,npc_actor_scale55(a->kind,zoom)*(a->scale60>0?a->scale60:1),a->kind==0?contactY:a->kind>=COMPANION_KIND50?a->groundY:a->y,actorDepthSlope50,a->sourceFade50c);if(a->kind==0)head_draw54(playerHeadPose54,a->x,a->y,a->depth,zoom/3.f,contactY,actorDepthSlope50);sprite_clip_reset54();}
  if(storyCartReady)art39_one(10,0,storyCartPose.sx,storyCartPose.sy,storyCartPose.depth,zoom/3,1,0,storyCartPose.dir);
  if(cartReady)art39_one(10+cartPose.style,cartPose.elapsed,cartPose.sx,cartPose.sy,cartPose.depth,zoom/3,1,game.moving?1:0,cartPose.dir);
  frame_draw_span51(&frameProfile50b,DRAW_ACTORS51,frame_clock50b(),&drawAt51);
  art39_draw(&artState,&game,matrix,zoom);campaign_party_fx_draw200(&game,matrix,zoom);npc_fx_draw172(&npcGame55,matrix,zoom);safety_draw50(&game,matrix,1);trans_burst_draw52(&game,&artState,matrix);enemy_projectiles45(&game,matrix,zoom);mercenary_arrow180(&game,matrix,zoom);

  frame_draw_span51(&frameProfile50b,DRAW_EFFECTS51,frame_clock50b(),&drawAt51);
  if(overlay)for(int gy=(int)y/8-20;gy<=(int)y/8+20;gy++)for(int gx=(int)x/8-20;gx<=(int)x/8+20;gx++)if(gx>=0&&gy>=0&&gx<(int)gw&&gy<(int)gh&&!walk[gy*gw+gx]){
   float xx=gx*8+4,yy=gy*8+4,zz=height_at(xx,yy);int px=(int)(matrix[0]*xx+matrix[1]*yy+matrix[3]),py=(int)(matrix[4]*xx+matrix[5]*yy+matrix[6]*zz+matrix[7]);if(px>2&&px<638&&py>100&&py<315)pb_fill(px,py,2,2,0xffff4848);
  }
  skill_safety_overlay(&game,matrix);
  skill_overlay(&game,matrix,aiming&&aimedSkill!=30&&aimedSkill!=32,aimedSkill,aimX,aimY);skill_expansion_overlay(&game,matrix);skill_utility_overlay(&game,matrix);skill_acolyte_overlay(&game,matrix);
  frame_draw_span51(&frameProfile50b,DRAW_MARKERS51,frame_clock50b(),&drawAt51);
  frame_span50b(&frameProfile50b,FRAME_DRAW50B,frame_clock50b(),&frameAt50b);
  frames++;if(now-fpsTime>=1000){fps=frames*1000/(now-fpsTime);frames=0;fpsTime=now;}
  MM_STATISTICS mem={0};mem.Length=sizeof(mem);MmQueryStatistics(&mem);
  if(strcmp(lastMessage,game.log)){snprintf(lastMessage,sizeof(lastMessage),"%s",game.log);messageUntil=now+4500;}
  showHelp=!game.diagnosticsOff45;
  if(!paused&&!ui.active&&!shopOpen&&!jobOpen){hud_batch_begin_texture53(damageTexture53,512,256,1024,0x00011d2a);damage_draw(&game,matrix);hud_batch_end();}
  /* Demon blindness is a view penalty, not the ordinary HIT/FLEE ailment. */
  if(game.hp>0&&game.jobId==J60_STAR_GLADIATOR&&game.joblevel>=50&&class_rank50(&game,SK60_SG_DEVIL)){for(int y60=0;y60<480;y60+=8){float dy60=(y60+4-contactY)/.85f,half60=dy60*dy60<19600?sqrtf(19600-dy60*dy60):0;int left60=(int)(contactX-half60),right60=(int)(contactX+half60);if(left60<0)left60=0;if(left60>640)left60=640;if(right60<0)right60=0;if(right60>640)right60=640;if(left60)pb_fill(0,y60,left60,8,0xff000000);if(right60<640)pb_fill(right60,y60,640-right60,8,0xff000000);}}
  if(!paused)campaign_portrait_draw200(&npcGame55);
  /* Dedicated minimap texture precedes the shared HUD vertex batch. */
  if(!jobOpen&&!shopOpen)ui_minimap(&game,activeMap);
  hud_batch_begin();
  if(!paused&&!ui.active&&!shopOpen)npc_waiting_bubbles55(&npcGame55,matrix);
  if(!targetReady)targetTrack.valid=0;
  if(!paused&&targetReady&&combat_valid_target(&game,game.target)){CombatMob*m=&game.mobs[game.target];ui_target_bounds41(targetBounds,m->hp,combat_mob_max(m));ui_enemy_label47(targetBounds,combat_npc_name55?combat_npc_name55(combat_npc_context55,m):mobSpecs[m->kind].name,m->hp,combat_mob_max(m));}

  if(!paused&&!ui.active&&!shopOpen&&!jobOpen){ui_cast_overhead(&game,castHeadX,castHeadTop);ui_spell_callout41(&game,castHeadX,castHeadTop);}
  if(jobOpen)ui_job_menu(&game,jobChoice,jobConfirm);
  else if(shopOpen==3)npc_dialogue_panels55(&npcGame55);
  else if(shopOpen==2)core_npc_draw53(&game,&coreNpcUI53);
  else if(shopOpen)merchant_draw(&game,&merchantUI);
  else{
   ui_player_status(&game);
   ui_compass61(yaw);

   int gate=world_gate(&game);char context[100]={0};
   if(!game.tooltipsDisabled&&combat_portal_near(&game)>=0)snprintf(context,sizeof(context),"A: enter your Warp Portal");
   else if(!game.tooltipsDisabled&&gate>=0)snprintf(context,sizeof(context),"A: travel to %s",mapLabels[worldGates[gate].destination]);
   else if(!game.tooltipsDisabled&&near_pending(&game))snprintf(context,sizeof(context),"Red warp: destination not connected yet");
   else if(!game.tooltipsDisabled&&guild_open194(questPins65)&&guild_near194(&game))snprintf(context,sizeof(context),"A: guild noticeboard");
   else if(!game.tooltipsDisabled&&regional_near194(questPins65,&game)>=0)snprintf(context,sizeof(context),"A: read courier notice");
   else if(!game.tooltipsDisabled&&campaign_world_near200()>=0)snprintf(context,sizeof(context),"%s",campaign_context200());
   else if(!game.tooltipsDisabled&&npc_game_near55(&npcGame55)>=0)snprintf(context,sizeof(context),"A: talk to %s",npcRecords55[npc_game_near55(&npcGame55)].label);
   else if(!game.tooltipsDisabled&&core_npc_near53(&game)>=0)snprintf(context,sizeof(context),"A: talk to %s",coreNpcs53[core_npc_near53(&game)].name);
   else if(!game.tooltipsDisabled&&aiming){const char*reason=skill_ground_reason(&game,aimedSkill,aimX,aimY);snprintf(context,sizeof(context),"%s",reason?reason:"Right stick: aim   A: cast   B: cancel");}

   /* Hotbar is composed between inactive and active windows by ui_draw. */

   if(!paused&&!shopOpen&&!jobOpen&&!game.utilityMenu)ui_diagnostics45(&game,&ui,fps,mem.AvailablePages/256,activeMap,walkMeasured,saveError?"SAVE ERROR":save_dirty(&saves,&game)?"Unsaved":"Saved",hudBatch.peak);
   if(!(ui.open&1))ui_safety_status(&game);
   ui_buffs(&game);

   if(!paused){PaperContext200 paper200={quickenPlayer45.frame,playerHeadPose54};uiPaperContext200=&paper200;uiPaperDraw200=!jobOpen&&!shopOpen&&!game.utilityMenu&&!ui.equipPicker49?paper_draw200:NULL;ui_draw(&game,&ui,!game.tooltipsDisabled);if(!game.utilityMenu){if(saveError)ui_caption40(&game,"SAVE ERROR - open START for details",ui.placing);else ui_feedback40(&game,&ui,context,(int32_t)(messageUntil-now)>0?game.log:NULL,ui.selectionTime>0?binding_name(hot_binding(&game)):NULL,!game.tooltipsDisabled);}}
   if(game.utilityMenu==504)guild_ui_draw194(&game);else if(game.utilityMenu)ui_utility(&game,utilityChoice);
   if(!paused)scene_ui_draw200();
   if(paused&&confirmLoad)save_browser_draw56();
   if(paused&&devOpen)dev_draw(&devUI,&game);
   if(paused&&!devOpen&&!testWarpOpen&&!confirmLoad){ui_pause_options50b(&pauseUI,confirmLoad,showHelp,sceneryEnabled,diskReady,(saveError&&saves.errorDetail58[0]?saves.errorDetail58:saves.status),!game.tooltipsDisabled,game.popupDisabled,autosave50b.choice,game.autoAttackToggle52,game.monsterView52,game.debugPlayerInvincible52);if(!confirmLoad&&pauseUI.detail==1)ui_performance53(&frameProfile50b);if(!confirmLoad&&pauseUI.detail==4)ui_memory183();if(!confirmLoad&&pauseUI.detail==2){ui_audio_queue50(soundAhead,soundUnderruns,soundRestarts50,soundBadQueues50,soundHardwareCursor,soundHardwareLast50,soundHardwareFlags50,musicStream.error,soundStatus);ui_audio_residency50(musicResident50/1024,musicPeakResident50/1024,musicLoadError50,spell_texture_bytes50()/1024);}}
   if(paused&&testWarpOpen){
    hud_panel(60,55,520,370);hud_text(78,69,"Test travel - choose a map");
    hud_text(78,98,"Left/right: region    Up/down: map    A: warp");
    int region48=travel_group48(testWarpChoice),travelRow51=travel_row51(testWarpChoice),travelFirst51=travelRow51/TRAVEL_PAGE_ROWS51*TRAVEL_PAGE_ROWS51;hud_text(82,128,"< %s >",travelGroupNames48[region48]);
    for(int row48=travelFirst51;row48<travelCounts48[region48]&&row48<travelFirst51+TRAVEL_PAGE_ROWS51;row48++){int k=travelGroups48[region48][row48],yy=169+(row48-travelFirst51)*30;
     if(k==testWarpChoice)pb_fill(72,yy-2,496,26,0xff8fd1ff);
     hud_text(82,yy,"%s%s",mapLabels[k],k==activeMap?" (here)":"");
    }
    hud_text(78,349,"Map %u / %u",(unsigned)travelRow51+1,(unsigned)travelCounts48[region48]);
    hud_text(78,371,"Arrives at a safe camp. Autosave setting applies.");
    hud_text(78,389,"%s",game.hp<=0?"KO travel revives you with full HP and SP.":"Items, HP/SP, levels and Zeny are kept.");
   }
   if(!pad)hud_text(160,305,"No controller - simulation paused");
  }
  hud_batch_end();
  if(stylingPreview191)stylist_draw191();
  if(!paused&&shopOpen==3)npc_dialogue_text55(&npcGame55);
  /* Reuse only the currently selected player's uploaded pose for the paper doll. */
  /* Paper doll is drawn in its owning window layer. */

  frame_span50b(&frameProfile50b,FRAME_HUD50B,frame_clock50b(),&frameAt50b);
  if(titleFadeOut56){unsigned elapsed=(unsigned)(frameSeconds*1000);if(!elapsed)elapsed=1;titleFadeOut56+=elapsed;if(titleFadeOut56>180)titleFadeOut56=180;frontend_fade56(titleFadeOut56*255/180);}
  if(frontendFadeIn56){frontend_fade56(frontendFadeIn56*255/180);unsigned elapsed=(unsigned)(frameSeconds*1000);frontendFadeIn56=elapsed>=frontendFadeIn56?0:frontendFadeIn56-elapsed;}
  while(pb_busy()){}while(pb_finished()){}
  if(titleFadeOut56>=180){npc_portrait_release171();npc_game_clear55(&npcGame55);npc_variables_clear55(&npcVariables55);npc_state_clear55(&npcQuests55);npcSaveBridge55.canSave=NULL;npcSaveBridge55.saveContext=NULL;npcSaveBridge55.hasClean=0;bank_cache_clear56();world_release();activeMap=~0u;game.autoAttack=0;goto frontRestart56;}
  frame_span50b(&frameProfile50b,FRAME_WAIT50B,frame_clock50b(),&frameAt50b);
  frame_finish50b(&frameProfile50b,frameFrequency50b,frameAudioTicks50b,!paused);
 }
}
