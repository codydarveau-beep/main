/* MIT. Record actual Test35 HUD, utility and assignment drawing; no GPU simulation. */
#define main baseline_ui_recorder_main
#include "test_window_render.c"
#undef main
#include "developer.h"
#include "utility_draw.h"
#include "developer_draw.h"
#include "diagnostics45.h"
#include "performance_draw50b.h"
#include "shop.h"
#include "merchant_services.h"
#include "shop_draw.h"
#include "merchant_draw.h"
#include "hud_palette.h"
#include "target_marker40.h"
int main(int argc,char**argv){assert(argc>=2);float vertices[HUD_BATCH_QUADS*HUD_QUAD_FLOATS];batch.vertices=vertices;Combat g;combat_init(&g,1500,1500,NULL,NULL);dev_class_preset(&g,6);WindowUI u={0};u.hintStat=u.hintSkill=1;skin_init();FILE*f=fopen("/tmp/myro40-skin.raw","wb");assert(f&&fwrite(skinTexture,1,skin_image_raw,f)==skin_image_raw);fclose(f);
 if(!strcmp(argv[1],"quest257")){NpcState55 log={0},pins={0};quest_journal_bind65(&log,&pins);assert(npc_quest_add55(&log,npcQuestDefinitions55[atoi(argv[2])].id,0,0));questPlayer194=&g;ui_open(&u,UI_QUESTS,1);u.choice[UI_QUESTS]=0;if(atoi(argv[3]))ui_input(&u,&g,2);u.questInfoScroll257=atoi(argv[4]);ui_draw(&g,&u,1);npc_state_clear55(&log);npc_state_clear55(&pins);questLog65=questPins65=NULL;questPlayer194=NULL;}
 else if(!strcmp(argv[1],"storyminimap242")){unsigned row=(unsigned)atoi(argv[2]);assert(row<42);const CampaignStageDefinition200*d=row<33?campaignLaterStages197+row:campaignStages200+row-33;NpcState55 state={0},quests={0};Campaign200 c={0};c.cursor=d->cursor;c.route=c.lineage=1;unsigned gate=campaign_stage_gate198(c.cursor);c.checkpoint=gate<256?gate:0;c.objectives=campaign_stage_enemies198(d);assert(campaign_store200(&state,&c));quest_journal_bind65(&quests,&state);campaignStage200=(CampaignStage200){&g,&state,d,1};g.mapId=d->map;g.x=d->x;g.y=d->y;gw=mapWidths[d->map]*2;gh=mapHeights[d->map]*2;minimapSize60=atoi(argv[3])?DISPLAY_LARGE60:DISPLAY_SMALL60;ui_minimap(&g,d->map);npc_state_clear55(&state);npc_state_clear55(&quests);campaignStage200.active=0;}
 else if(!strcmp(argv[1],"diagvideo255")){PauseUI p={.tab=P53_DIAGNOSTICS64,.row=4,.inside=1,.detail=5,.screenRow=atoi(argv[2]),.editing61=atoi(argv[3]),.allowTesting58=atoi(argv[4])};assert(p.screenRow>=0&&p.screenRow<9);p.value61=pause_value61(&g,&(Autosave50b){.choice=1},P53_VIDEO_TEST255,p.screenRow);ui_pause_options50b(&p,0,1,1,1,"Restoration check.",1,0,1,0,0,0);}
 else if(!strcmp(argv[1],"settings194")){PauseUI p={.tab=atoi(argv[2]),.row=atoi(argv[3]),.inside=1,.allowTesting58=1,.editing61=atoi(argv[4]),.frontOnly61=atoi(argv[5])};assert(p.tab>=pause_first61(&p)&&p.tab<pause_first61(&p)+pause_tabs58(&p));assert(p.row>=0&&p.row<pause_count(p.tab));p.value61=pause_value61(&g,&(Autosave50b){.choice=1},p.tab,p.row);ui_pause_options50b(&p,0,1,1,1,"Development check.",1,0,1,0,0,0);}
 else if(!strcmp(argv[1],"windows194")){unsigned w=(unsigned)atoi(argv[2]);assert(w<5);u.open=31;u.focus=5+w;u.choice[w]=0;ui_player_status(&g);ui_minimap(&g,2);ui_draw(&g,&u,1);ui_feedback40(&g,&u,NULL,NULL,NULL,1);}
 else if(!strcmp(argv[1],"autosave50b")){PauseUI menu={.tab=P53_GAMEPLAY,.row=4};ui_pause_options50b(&menu,0,1,1,1,"Autosave preference remembered.",1,0,atoi(argv[2]),0,0,0);FrameProfile50b perf={.ready=1};for(int i=0;i<6;i++)perf.tenths[i]=123;ui_performance50b(&perf);}
 else if(!strcmp(argv[1],"performance50b")){PauseUI menu={.tab=0};ui_pause_options41(&menu,0,1,1,1,"Saved.",1,0);FrameProfile50b perf={0};perf.ready=argc>2?atoi(argv[2]):1;for(int i=0;i<6;i++)perf.tenths[i]=argc>3?atoi(argv[3]):123;ui_performance50b(&perf);}
 else if(!strcmp(argv[1],"status50")){dev_class_preset(&g,argc>2?atoi(argv[2]):18);ui_open(&u,UI_STATUS,1);u.choice[UI_STATUS]=argc>3?atoi(argv[3]):2;ui_draw(&g,&u,1);}
 else if(!strcmp(argv[1],"craft50")){dev_class_preset(&g,atoi(argv[2]));g.utilityMenu=g.jobId==20?239:600;g.class50.craftTool=argc>4?atoi(argv[4]):614;ui_utility(&g,atoi(argv[3]));}
 else if(!strcmp(argv[1],"companion50")){dev_class_preset(&g,20);homun_create50(&g);g.persistent50.homunType=atoi(argv[2]);g.utilityMenu=500;ui_utility(&g,atoi(argv[3]));}
 else if(!strcmp(argv[1],"buffs50")){dev_class_preset(&g,atoi(argv[2]));for(int id=127;id<254;id++)if(class_rank50(&g,id)&&!skill_passive(id)){g.class50.level[id-127]=class_rank50(&g,id);g.class50.until[id-127]=g.time+60;}ui_buffs(&g);}
 else if(!strcmp(argv[1],"audio50")){PauseUI p={.tab=1};ui_pause_options41(&p,0,1,1,1,"Saved.",1,0);ui_audio_queue50(4,1234,5,99,31,2,0x1c,0,"Audio output recovered (5).");ui_audio_residency50(1606,3212,7,8544);}
 else if(!strcmp(argv[1],"enemy47")){int edge=atoi(argv[2]);float x=edge&1?610:30,y=edge&2?450:100;TargetBounds41 b={x-8,y-30,x+8,y};ui_target_bounds41(b,atoi(argv[3]),1000000);ui_enemy_label47(b,"Moonlight Flower",atoi(argv[3]),1000000);}
 else if(!strcmp(argv[1],"diag45")){g.diagnosticsOff45=atoi(argv[2]);u.open=atoi(argv[3]);ui_diagnostics45(&g,&u,60,24,11,50,"Saved",600);if(g.diagnosticsOff45){assert(!batch.count);free(skinTexture);return 0;}}
 else if(!strcmp(argv[1],"minimap44")){unsigned id=atoi(argv[2]);if(id<WORLD_MAP_COUNT){gw=mapWidths[id]*2;gh=mapHeights[id]*2;}ui_minimap(&g,id);if(id>=WORLD_MAP_COUNT){assert(!batch.count);free(skinTexture);return 0;}}
 else if(!strcmp(argv[1],"status44")){dev_class_preset(&g,7);g.hp=g.maxhp=atoi(argv[2]);ui_player_status(&g);}
 else if(!strcmp(argv[1],"roll")){float phase=argc>2?atof(argv[2]):0;hotbarPhase=phase;hotbarTarget=phase;ui_hotbar(&g,0);ui_quick_slots(&g,&u);ui_level_hints(&u);}
 else if(!strcmp(argv[1],"assign")){u.active=u.placing=1;u.dropSlot=argc>2?atoi(argv[2]):0;u.carried=64;ui_draw(&g,&u,1);ui_quick_slots(&g,&u);}
 else if(!strcmp(argv[1],"equip49")){dev_class_preset(&g,11);ui_open(&u,UI_EQUIP,1);u.equipPicker49=1;u.equipChoice49=argc>2?atoi(argv[2]):0;ui_draw(&g,&u,1);}
 else if(!strcmp(argv[1],"craft")){g.utilityMenu=60;ui_utility(&g,1);}
 else if(!strcmp(argv[1],"cart")){g.utilityMenu=63;g.cartOwned=1;ui_utility(&g,argc>2?atoi(argv[2]):0);}
 else if(!strcmp(argv[1],"appraise")){g.utilityMenu=62;ui_utility(&g,0);}
 else if(!strcmp(argv[1],"styles")){g.utilityMenu=65;g.cartOwned=1;ui_utility(&g,4);}
 else if(!strcmp(argv[1],"skills")){int job=argc>2?atoi(argv[2]):6;dev_class_preset(&g,job);ui_open(&u,UI_SKILLS,1);u.skillPage=1;u.choice[3]=class_count(&g)-1;u.skillDetailed46=argc>3?atoi(argv[3]):0;ui_draw(&g,&u,1);}
 else if(!strcmp(argv[1],"inventory")){ui_open(&u,UI_ITEMS,1);u.choice[1]=argc>2?atoi(argv[2]):0;ui_draw(&g,&u,1);}
 else if(!strcmp(argv[1],"cast")){g.spellCastTotal=argc>3?atof(argv[3]):5;g.spellCastLeft=argc>2?atof(argv[2]):5;g.spellCastId=67;ui_cast_status(&g);}
 else if(!strcmp(argv[1],"services")){MerchantUI m;merchant_open(&m,&g);m.choice=argc>2?atoi(argv[2]):0;m.confirm=argc>3?atoi(argv[3]):0;merchant_draw(&g,&m);}
 else if(!strcmp(argv[1],"servicecart")){MerchantUI m;merchant_open(&m,&g);m.mode=MS_CART;m.item=argc>2?atoi(argv[2]):0;g.cartOwned=1;merchant_draw(&g,&m);}
 else if(!strcmp(argv[1],"shop")){MerchantUI m;merchant_open(&m,&g);m.mode=argc>3&&atoi(argv[3])?MS_SELL:MS_BUY;m.item=argc>2?atoi(argv[2]):0;merchant_draw(&g,&m);}
 else if(!strcmp(argv[1],"equip")){dev_class_preset(&g,1);ui_open(&u,UI_EQUIP,1);u.choice[2]=argc>2?atoi(argv[2]):0;ui_draw(&g,&u,1);}
 else if(!strcmp(argv[1],"feedback")){int flags=argc>2?atoi(argv[2]):7,id=argc>3?atoi(argv[3]):0;const char*message=flags&16?"A long notification checks wrapping without covering the skill name or the interaction help window.":"HP is already full. Item kept.";const char*help=flags&16?"Right stick: aim carefully on clear ground. A: confirm the chosen location. B: cancel without cost.":"A: talk to the job instructor";if(flags&32)u.open=15;g.tooltipsDisabled=(flags&64)!=0;if(flags&8){g.spellCastTotal=6.44f;g.spellCastLeft=3.2f;g.spellCastId=3;}ui_player_status(&g);ui_minimap(&g,2);ui_play_feedback_at(&g,flags&4?help:NULL,flags&2?message:NULL,flags&1?binding_name(id):NULL,flags&32);if(flags&8)ui_cast_overhead(&g,320,210);ui_draw(&g,&u,0);ui_hotbar(&g,0);ui_quick_slots(&g,&u);ui_level_hints(&u);}
 else if(!strcmp(argv[1],"windows")){u.open=15;u.active=u.inside=1;u.focus=5+(argc>2?atoi(argv[2]):0);u.choice[u.focus-5]=argc>3?atoi(argv[3]):0;u.tipTime=5;g.tooltipsDisabled=argc>4?atoi(argv[4]):0;ui_player_status(&g);ui_minimap(&g,2);ui_draw(&g,&u,1);ui_feedback40(&g,&u,NULL,NULL,NULL,1);ui_quick_slots(&g,&u);}
 else if(!strcmp(argv[1],"storage")){MerchantUI m;merchant_open(&m,&g);m.mode=MS_STORAGE;m.storagePaid=1;m.item=argc>2?atoi(argv[2]):0;assert(owned_add52(&g.owned52,2,itemDefs[m.item%ITEM_COUNT].id,30000,item_rule52)==OWNED_OK52);merchant_draw(&g,&m);}
 else if(!strcmp(argv[1],"preview39")){DeveloperUI d={.tab=3,.row=3,.preview=argc>2?atoi(argv[2]):0};dev_draw(&d,&g);}
 else if(!strcmp(argv[1],"dock40")){int f=atoi(argv[2]);g.tooltipsDisabled=(f&16)!=0;g.logIsTip=(f&8)!=0;u.open=15;u.active=(f&1)!=0;u.inside=(f&2)!=0;u.focus=8;u.placing=(f&256)!=0;u.tipTime=4;ui_draw(&g,&u,1);ui_feedback40(&g,&u,f&128?"A: talk to the merchant":NULL,f&4?"Sitting: faster HP/SP recovery. L3 to stand.":NULL,f&64?"Selected skill":NULL,(f&32)!=0);}
 else if(!strcmp(argv[1],"target40")){ui_target_marker(320,245,atoi(argv[2]),100);}
 else if(!strcmp(argv[1],"stylist40")){MerchantUI m;merchant_styles_open(&m,&g);g.cartOwned=1;m.item=atoi(argv[2]);merchant_draw(&g,&m);}
 else if(!strcmp(argv[1],"label40")){ui_feedback40(&g,&u,NULL,NULL,binding_name(atoi(argv[2])),1);}
 else if(!strcmp(argv[1],"pause38")){PauseUI p={.tab=0,.row=argc>2?atoi(argv[2]):0};ui_pause_options(&p,0,1,1,1,"Settings and character ready.",argc>3?atoi(argv[3]):1);}
 else if(!strcmp(argv[1],"toggles41")){PauseUI p={.tab=P53_MESSAGES,.row=atoi(argv[2])%pause_count(P53_MESSAGES)};ui_pause_options41(&p,0,1,1,1,"Preferences saved.",1,atoi(argv[3]));}
 else if(!strcmp(argv[1],"popup41")){g.popupDisabled=atoi(argv[2]);unsigned category=1u<<atoi(argv[3]);if(category==POP_SPEECH){g.fxSkill=24;g.fxAt=g.time=1;ui_spell_callout41(&g,320,210);}else{combat_notice(&g,category,"Test notification.");ui_feedback40(&g,&u,NULL,g.log,NULL,0);}}
 else if(!strcmp(argv[1],"money41")){ui_open(&u,UI_ITEMS,0);g.zeny=atoi(argv[2]);ui_draw(&g,&u,1);}
 else if(!strcmp(argv[1],"dev41")){DeveloperUI d={.tab=atoi(argv[2]),.row=atoi(argv[3]),.classGroup=argc>4?atoi(argv[4]):0};dev_draw(&d,&g);}
 else assert(0);
 if(!strcmp(argv[1],"cast")&&!combat_casting(&g)){assert(batch.count==0);free(skinTexture);return 0;}if(!strcmp(argv[1],"popup41")){unsigned cat=1u<<atoi(argv[3]);assert((batch.count>0)==!(g.popupDisabled&cat));}else assert(batch.count>0);assert(batch.count<=HUD_BATCH_QUADS);fprintf(stderr,"PASS Test40 %s: %u quads\n",argv[1],batch.count);free(skinTexture);}
