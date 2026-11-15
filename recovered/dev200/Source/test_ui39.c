/* MIT. Record actual Test35 HUD, utility and assignment drawing; no GPU simulation. */
#define main baseline_ui_recorder_main
#include "test_window_render.c"
#undef main
#include "developer.h"
#include "utility_draw.h"
#include "developer_draw.h"
#include "shop.h"
#include "merchant_services.h"
#include "shop_draw.h"
#include "merchant_draw.h"
int main(int argc,char**argv){assert(argc>=2);float vertices[HUD_BATCH_QUADS*HUD_QUAD_FLOATS];batch.vertices=vertices;Combat g;combat_init(&g,1500,1500,NULL,NULL);dev_class_preset(&g,6);WindowUI u={0};u.hintStat=u.hintSkill=1;skin_init();FILE*f=fopen("/tmp/myro38-skin.raw","wb");assert(f&&fwrite(skinTexture,1,skin_image_raw,f)==skin_image_raw);fclose(f);
 if(!strcmp(argv[1],"roll")){float phase=argc>2?atof(argv[2]):0;hotbarPhase=phase;hotbarTarget=phase;ui_hotbar(&g,0);ui_quick_slots(&g,&u);ui_level_hints(&u);}
 else if(!strcmp(argv[1],"assign")){u.active=u.placing=1;u.dropSlot=argc>2?atoi(argv[2]):0;u.carried=64;ui_draw(&g,&u,1);ui_quick_slots(&g,&u);}
 else if(!strcmp(argv[1],"craft")){g.utilityMenu=60;ui_utility(&g,1);}
 else if(!strcmp(argv[1],"cart")){g.utilityMenu=63;g.cartOwned=1;ui_utility(&g,argc>2?atoi(argv[2]):0);}
 else if(!strcmp(argv[1],"appraise")){g.utilityMenu=62;ui_utility(&g,0);}
 else if(!strcmp(argv[1],"styles")){g.utilityMenu=65;g.cartOwned=1;ui_utility(&g,4);}
 else if(!strcmp(argv[1],"skills")){int job=argc>2?atoi(argv[2]):6;dev_class_preset(&g,job);ui_open(&u,UI_SKILLS,1);u.skillPage=1;u.choice[3]=class_count(&g)-1;ui_draw(&g,&u,1);}
 else if(!strcmp(argv[1],"inventory")){ui_open(&u,UI_ITEMS,1);u.choice[1]=argc>2?atoi(argv[2]):0;ui_draw(&g,&u,1);}
 else if(!strcmp(argv[1],"cast")){g.spellCastTotal=argc>3?atof(argv[3]):5;g.spellCastLeft=argc>2?atof(argv[2]):5;g.spellCastId=67;ui_cast_status(&g);}
 else if(!strcmp(argv[1],"services")){MerchantUI m;merchant_open(&m,&g);m.choice=argc>2?atoi(argv[2]):0;m.confirm=argc>3?atoi(argv[3]):0;merchant_draw(&g,&m);}
 else if(!strcmp(argv[1],"servicecart")){MerchantUI m;merchant_open(&m,&g);m.mode=MS_CART;m.item=argc>2?atoi(argv[2]):0;g.cartOwned=1;merchant_draw(&g,&m);}
 else if(!strcmp(argv[1],"shop")){MerchantUI m;merchant_open(&m,&g);m.mode=argc>3&&atoi(argv[3])?MS_SELL:MS_BUY;m.item=argc>2?atoi(argv[2]):0;merchant_draw(&g,&m);}
 else if(!strcmp(argv[1],"equip")){dev_class_preset(&g,1);ui_open(&u,UI_EQUIP,1);u.choice[2]=5;ui_draw(&g,&u,1);}
 else if(!strcmp(argv[1],"feedback")){int flags=argc>2?atoi(argv[2]):7,id=argc>3?atoi(argv[3]):0;const char*message=flags&16?"A long notification checks wrapping without covering the skill name or the interaction help window.":"HP is already full. Item kept.";const char*help=flags&16?"Right stick: aim carefully on clear ground. A: confirm the chosen location. B: cancel without cost.":"A: talk to the job instructor";if(flags&32)u.open=15;g.tooltipsDisabled=(flags&64)!=0;if(flags&8){g.spellCastTotal=6.44f;g.spellCastLeft=3.2f;g.spellCastId=3;}ui_player_status(&g);ui_minimap(&g,2);ui_play_feedback_at(&g,flags&4?help:NULL,flags&2?message:NULL,flags&1?binding_name(id):NULL,flags&32);if(flags&8)ui_cast_overhead(&g,320,210);ui_draw(&g,&u,0);ui_hotbar(&g,0);ui_quick_slots(&g,&u);ui_level_hints(&u);}
 else if(!strcmp(argv[1],"windows")){u.open=15;u.active=u.inside=1;u.focus=4+(argc>2?atoi(argv[2]):0);u.choice[u.focus-4]=argc>3?atoi(argv[3]):0;u.tipTime=5;g.tooltipsDisabled=argc>4?atoi(argv[4]):0;ui_player_status(&g);ui_minimap(&g,2);ui_draw(&g,&u,1);ui_quick_slots(&g,&u);}
 else if(!strcmp(argv[1],"storage")){MerchantUI m;merchant_open(&m,&g);m.mode=MS_STORAGE;m.storagePaid=1;m.item=argc>2?atoi(argv[2]):0;g.storageItems[m.item%ITEM_COUNT]=30000;merchant_draw(&g,&m);}
 else if(!strcmp(argv[1],"preview39")){DeveloperUI d={.tab=3,.row=3,.preview=argc>2?atoi(argv[2]):0};dev_draw(&d,&g);}
 else if(!strcmp(argv[1],"pause38")){PauseUI p={.tab=0,.row=argc>2?atoi(argv[2]):0};ui_pause_options(&p,0,1,1,1,"Settings and character ready.",argc>3?atoi(argv[3]):1);}
 else assert(0);
 if(!strcmp(argv[1],"cast")&&!combat_casting(&g)){assert(batch.count==0);free(skinTexture);return 0;}assert(batch.count>0&&batch.count<=HUD_BATCH_QUADS);fprintf(stderr,"PASS Test39 %s: %u quads\n",argv[1],batch.count);free(skinTexture);}
