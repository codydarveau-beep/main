/* MIT. Record actual Test35 HUD, utility and assignment drawing; no GPU simulation. */
#define main baseline_ui_recorder_main
#include "test_window_render.c"
#undef main
#include "developer.h"
#include "utility_draw.h"
int main(int argc,char**argv){assert(argc>=2);float vertices[HUD_BATCH_QUADS*HUD_QUAD_FLOATS];batch.vertices=vertices;Combat g;combat_init(&g,1500,1500,NULL,NULL);dev_class_preset(&g,6);WindowUI u={0};u.hintStat=u.hintSkill=1;skin_init();FILE*f=fopen("/tmp/myro35-skin.raw","wb");assert(f&&fwrite(skinTexture,1,skin_image_raw,f)==skin_image_raw);fclose(f);
 if(!strcmp(argv[1],"roll")){float phase=argc>2?atof(argv[2]):0;hotbarPhase=phase;hotbarTarget=phase;ui_hotbar(&g,0);ui_quick_slots(&g,&u);ui_level_hints(&u);}
 else if(!strcmp(argv[1],"assign")){u.active=u.placing=1;u.dropSlot=argc>2?atoi(argv[2]):0;u.carried=64;ui_draw(&g,&u,1);ui_quick_slots(&g,&u);}
 else if(!strcmp(argv[1],"craft")){g.utilityMenu=60;ui_utility(&g,1);}
 else if(!strcmp(argv[1],"cart")){g.utilityMenu=63;g.cartOwned=1;ui_utility(&g,argc>2?atoi(argv[2]):0);}
 else if(!strcmp(argv[1],"appraise")){g.utilityMenu=62;ui_utility(&g,0);}
 else if(!strcmp(argv[1],"styles")){g.utilityMenu=65;g.cartOwned=1;ui_utility(&g,4);}
 else if(!strcmp(argv[1],"skills")){int job=argc>2?atoi(argv[2]):6;dev_class_preset(&g,job);ui_open(&u,UI_SKILLS,1);u.skillPage=1;u.choice[3]=class_count(&g)-1;ui_draw(&g,&u,1);}
 else if(!strcmp(argv[1],"equip")){dev_class_preset(&g,1);ui_open(&u,UI_EQUIP,1);u.choice[2]=5;ui_draw(&g,&u,1);}
 else assert(0);
 assert(batch.count>0&&batch.count<=HUD_BATCH_QUADS);fprintf(stderr,"PASS Test35 %s: %u quads\n",argv[1],batch.count);free(skinTexture);}
