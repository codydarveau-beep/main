/* MIT. Original client front-end art with controller-driven offline characters. */
#ifndef MYRO_FRONTEND_XBOX56_H
#define MYRO_FRONTEND_XBOX56_H
#include "frontend_state56.h"
#include "frontend_layout58.h"
#include "character_pages62.h"
#include "appearance_picker112.h"
#include "fade_texture57.h"
#include "title_font58.h"
#include "character_bank56.h"
#include "frontend_prefs56.h"
extern const unsigned char frontend_title56[],frontend_select56[],frontend_creation56[];
extern const unsigned frontend_title_bytes56,frontend_select_bytes56,frontend_creation_bytes56;
static void*frontendTitleTexture56,*frontendWindowTexture56,*frontendFadeTexture56;
static void*titleFontTexture58;
static unsigned frontendWindowPage56=~0u,frontendFadeIn56;
static unsigned frontend_buttons56(SDL_GameController*p){unsigned b=0;static const SDL_GameControllerButton keys[]={SDL_CONTROLLER_BUTTON_START,SDL_CONTROLLER_BUTTON_A,SDL_CONTROLLER_BUTTON_B,SDL_CONTROLLER_BUTTON_X,SDL_CONTROLLER_BUTTON_Y,SDL_CONTROLLER_BUTTON_LEFTSHOULDER,SDL_CONTROLLER_BUTTON_RIGHTSTICK,SDL_CONTROLLER_BUTTON_LEFTSTICK,SDL_CONTROLLER_BUTTON_BACK,SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,SDL_CONTROLLER_BUTTON_DPAD_UP,SDL_CONTROLLER_BUTTON_DPAD_DOWN,SDL_CONTROLLER_BUTTON_DPAD_LEFT,SDL_CONTROLLER_BUTTON_DPAD_RIGHT};for(unsigned i=0;i<14;i++)if(button(p,keys[i]))b|=1u<<i;if(axis(p,SDL_CONTROLLER_AXIS_TRIGGERLEFT)>.4f)b|=16384;if(axis(p,SDL_CONTROLLER_AXIS_TRIGGERRIGHT)>.4f)b|=32768;return b|menu_sticks61(p);}
static void frontend_fade56(unsigned alpha){if(!alpha)return;if(alpha>255)alpha=255;if(!frontendFadeTexture56){uint32_t pixels[FADE_BYTES57/4];fade_pixels57(pixels);frontendFadeTexture56=gpu_alloc(sizeof(pixels));memcpy(frontendFadeTexture56,pixels,sizeof(pixels));}hud_setup_direct(frontendFadeTexture56,FADE_WIDTH57,FADE_HEIGHT57,FADE_PITCH57,0x0001122a,1);hud_quad(0,0,640,480,.5f,alpha+.5f,0,0);}
static void*frontend_art56(const unsigned char*data,unsigned packed,unsigned raw){unsigned char*p=inflateasset("start menu",data,packed,raw);void*t=gpu_alloc(raw);memcpy(t,p,raw);free(p);return t;}
static void frontend_previews_release58(void);
static void appearance_texture_release112(void);
static void frontend_art_release56(void){while(pb_busy()){}if(frontendTitleTexture56)MmFreeContiguousMemory(frontendTitleTexture56);if(frontendWindowTexture56)MmFreeContiguousMemory(frontendWindowTexture56);frontendTitleTexture56=frontendWindowTexture56=NULL;frontendWindowPage56=~0u;if(titleFontTexture58)MmFreeContiguousMemory(titleFontTexture58);titleFontTexture58=NULL;appearance_texture_release112();frontend_previews_release58();}
static void frontend_background56(unsigned page){if(!frontendTitleTexture56)frontendTitleTexture56=frontend_art56(frontend_title56,frontend_title_bytes56,640*480*2);hud_setup_direct(frontendTitleTexture56,640,480,1280,0x0001112a,0);hud_quad(0,0,640,480,0,0,640,480);if(page!=F56_CHARACTERS&&page!=F56_CREATE)return;if(frontendWindowPage56!=page){while(pb_busy()){}if(frontendWindowTexture56)MmFreeContiguousMemory(frontendWindowTexture56);frontendWindowTexture56=frontend_art56(page==F56_CREATE?frontend_creation56:frontend_select56,page==F56_CREATE?frontend_creation_bytes56:frontend_select_bytes56,576*342*2);frontendWindowPage56=page;}hud_setup_direct(frontendWindowTexture56,576,342,1152,0x0001112a,0);hud_quad(32,54,576,342,0,0,576,342);}
typedef struct{SparseSprite sprite;unsigned actor,ready,variant,headViews[3],headSex,headVariant,headReady;FrontHead180 heads[3];}FrontPreview58;
static FrontPreview58 frontPreviews58[3];
static void frontend_previews_release58(void){while(pb_busy()){}for(unsigned i=0;i<3;i++){for(unsigned j=0;j<3;j++)front_head_clear180(frontPreviews58[i].heads+j);free(frontPreviews58[i].sprite.raw);memset(frontPreviews58+i,0,sizeof(*frontPreviews58));}appearance_hair_release58();spriteEpoch++;}
static void frontend_preview56(unsigned job,float x,float y,unsigned slot,Appearance58 appearance,unsigned sex,const unsigned*headSources180,unsigned direction191){
 if(slot>=3)return;unsigned actor=class_actor_id50(job,0);FrontPreview58*c=frontPreviews58+slot;
 if(!c->ready||c->actor!=actor||(actor>=44&&c->sprite.sex58!=sex)){while(pb_busy()){}free(c->sprite.raw);memset(&c->sprite,0,sizeof(c->sprite));unsigned index=0;while(index<ACTOR_VARIANTS&&(actorBlobs[index].job!=actor||actorBlobs[index].gear||(actorSex60[index]!=2&&actorSex60[index]!=sex)))index++;if(index==ACTOR_VARIANTS)return;const ActorBlob*b=actorBlobs+index;unsigned char*p=actor_packed(index);sprite_load(&c->sprite,"character preview",p,b->packed,b->raw);free(p);c->sprite.actor58=actor;c->actor=actor;c->variant=index;c->ready=1;spriteEpoch++;}
 SparseSprite*s=&c->sprite;if(!appearance_equal58(s->appearance58,appearance)||s->sex58!=sex){s->appearance58=appearance;s->sex58=sex;spriteEpoch++;}direction191%=8;unsigned frame=s->sequence[s->meta[direction191*3]];unsigned*d=s->directory+frame*5;
 sprite_upload(s,frame,(int)slot);hud_setup_direct(entityTextures[slot],128,s->h,128*s->bytesPerPixel,s->alpha4444?0x00011d2a:s->bytesPerPixel==2?0x0001102a:0x0001122a,1);
 hud_quad(x-d[0]-d[2]*.5f,y-d[1]-d[3],128,s->h,0,0,128,s->h);
 unsigned views180[3]={0};if(headSources180)for(unsigned i=0;i<3;i++)views180[i]=head_item_view54(headSources180[i]);head_unique_views54(views180);unsigned headSex180=job>=J60_NINJA?sex:(job_parent52(job)==16||job==J52_GYPSY)?0:1;
 if(!c->headReady||c->headVariant!=c->variant||c->headSex!=headSex180||memcmp(views180,c->headViews,sizeof(views180))){while(pb_busy()){}HeadPose54 pose180={0};if(views180[0]||views180[1]||views180[2])pose180=front_head_pose180(c->variant,s->meta[0]);for(unsigned i=0;i<3;i++){front_head_clear180(c->heads+i);if(views180[i])front_head_load180(c->heads+i,views180[i],headSex180,pose180);}memcpy(c->headViews,views180,sizeof(views180));c->headSex=headSex180;c->headVariant=c->variant;c->headReady=1;}
 for(unsigned i=0;i<3;i++)front_head_draw180(c->heads+i,x-d[0]-d[2]*.5f+s->anchorX,y-d[1]-d[3]+s->anchorY);
}
static void frontend_stat_line112(int x,int y,int nx,int ny){int dx=abs(nx-x),dy=-abs(ny-y),sx=x<nx?1:-1,sy=y<ny?1:-1,error=dx+dy;for(;;){pb_fill(x,y,1,1,0xff8999b2);if(x==nx&&y==ny)break;int e=2*error;if(e>=dy){error+=dy;x+=sx;}if(e<=dx){error+=dx;y+=sy;}}}
static void frontend_stat_web58(const unsigned char stats[6],int selected){
 static const unsigned around[6]={0,1,2,3,5,4};float px[6],py[6];for(unsigned i=0;i<6;i++){unsigned a=around[i],b=around[(i+1)%6];frontend_stat_line112(frontStatPoints58[a][0],frontStatPoints58[a][1],frontStatPoints58[b][0],frontStatPoints58[b][1]);frontend_stat_line112(FRONT_STAT_X112,FRONT_STAT_Y112,frontStatPoints58[a][0],frontStatPoints58[a][1]);}
 for(unsigned i=0;i<6;i++){unsigned n=around[i];float r=stats[n]/9.f;px[i]=FRONT_STAT_X112+(frontStatPoints58[n][0]-FRONT_STAT_X112)*r;py[i]=FRONT_STAT_Y112+(frontStatPoints58[n][1]-FRONT_STAT_Y112)*r;}
 for(int y=136;y<261;y++){float left=1000,right=-1000;for(unsigned i=0;i<6;i++){unsigned j=(i+1)%6;if((py[i]<=y&&py[j]>y)||(py[j]<=y&&py[i]>y)){float x=px[i]+(y-py[i])*(px[j]-px[i])/(py[j]-py[i]);if(x<left)left=x;if(x>right)right=x;}}if(right>left)pb_fill((int)ceilf(left),y,(int)floorf(right)-(int)ceilf(left)+1,1,0x4065dffa);}
 static const char*names[]={"STR","AGI","VIT","INT","DEX","LUK"};for(unsigned n=0;n<6;n++){int x=frontStatPoints58[n][0],y=frontStatPoints58[n][1];ui_cell(x-25,y-10,50,21,selected==(int)n);ui_scaled(x-20,y-6,.75f,"%s %u",names[n],stats[n]);}
}
#include "frontend_choices112.h"
static void frontend_keyboard56(NpcEditor55*e){unsigned count=npc_editor_count55(e),rows=(count+9)/10;int height=110+rows*20,top=(480-height)/2;ui_panel(120,top,400,height,"Character name",0,-1);ui_text(136,top+30,"%.19s",e->text);for(unsigned k=0;k<count;k++){unsigned x=136+(k%10)*36,y=top+64+(k/10)*20;ui_cell(x,y,34,19,k==e->choice);ui_scaled(x+5,y+2,.8f,k==count-1?"OK":"%c",k==count-1?' ':npcEditorKeys55[k]);}ui_hint64(134,top+height-29,.75f,"A: type  X: erase  Y: OK  B: cancel");}
#include "character_create56.h"
static void frontend_page_arrows62(unsigned page){for(unsigned right=0;right<2;right++){if(right?page==2:page==0)continue;for(int i=0;i<7;i++){int half=right?6-i:i;pb_fill((right?567:66)+i,166-half,1,half*2+1,0xff6aabef);}}}
static void frontend_page_indicators62(const CharacterPages62*p){hud_setup(skinTexture,512,SKIN_H,2048,0x0001122a,1);for(unsigned i=0;i<3;i++){float t=p->active[i],rect[4],u,v;character_page_rect62(i,t,rect);unsigned shade=(unsigned)(t*16+.5f);if(shade>16)shade=16;hud_solid_uv(26,&u,&v);/* Existing12.5% black shadow, offset one pixel. */hud_quad(rect[0]+1,rect[1]+1,rect[2],rect[3],u,v,0,0);hud_solid_uv(60+shade,&u,&v);hud_quad(rect[0],rect[1],rect[2],rect[3],u,v,0,0);}}

static void frontend_scan_slots56(Frontend56*f){for(unsigned c=0;c<9;c++)f->slots[c]=bank_latest56(c)>=0?F56_COMPATIBLE:bank_occupied56(c)?F56_INCOMPATIBLE:F56_EMPTY;}
/* No map is loaded until the fade reaches black and a valid character is chosen. */
static int frontend_run56(Combat*game,SaveStore*saves,SDL_GameController**controller,Autosave50b*autosave,int disk){
 sound_music_login58();Frontend56 f;frontend_init56(&f);f.fade=2;f.opaque=255;f.unlocked=(unsigned)developerUnlocked56;if(disk)bank_scan56();frontend_scan_slots56(&f);NpcEditor55 editor={0};editor.string=1;unsigned char initialStats[6]={5,5,5,5,5,5};char name[20]="";int keyboard=0,createRow=0,creationSex=1,settingsRow=0,editing=0,before=0,beforeMute=0,devMode=0;CharacterPages62 characterPages62={0};PauseUI screen={.tab=P53_AUDIO,.frontOnly61=1};AppearancePicker112 picker112={0};char status[100]="";unsigned previous=~0u,lastPage=~0u;DWORD last=GetTickCount();InputRepeat repeat={0};
 for(;;){boss_wallclock53();npcSaveBridge55.utc=bossNow53>=UINT64_C(11644473600)?bossNow53-UINT64_C(11644473600):0;SDL_Event event;while(SDL_PollEvent(&event)){if(event.type==SDL_CONTROLLERDEVICEADDED&&!*controller)*controller=SDL_GameControllerOpen(event.cdevice.which);if(event.type==SDL_CONTROLLERDEVICEREMOVED&&*controller&&SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(*controller))==event.cdevice.which){SDL_GameControllerClose(*controller);*controller=NULL;}}
 SDL_GameControllerUpdate();DWORD now=GetTickCount();unsigned ms=now-last;last=now;if(ms>50)ms=50;menuRightSuppressed161=f.page==F56_CREATE;preview_turn191(&creationTurn191,axis(*controller,SDL_CONTROLLER_AXIS_RIGHTX),ms/1000.f,f.page==F56_CREATE);unsigned buttons=frontend_buttons56(*controller),pressed=buttons&~previous;previous=buttons;if(f.page!=F56_PRESS)pressed|=input_repeat(&repeat,buttons,1024|2048|4096|8192,f.page+1,ms/1000.f);
 if(f.page!=lastPage){lastPage=f.page;if(f.page==F56_CREATE){memset(name,0,sizeof(name));memset(&editor,0,sizeof(editor));editor.string=1;memset(initialStats,5,6);createRow=keyboard=0;creationSex=1;creationAppearance58=(Appearance58){0};picker112=(AppearancePicker112){0};}if(f.page==F56_CHARACTERS&&!devMode)status[0]=0;}
 unsigned beforeCursor58=f.row+f.slot*16+(f.page==F56_SETTINGS?(unsigned)(screen.tab*16+screen.row):settingsRow)*256+createRow*4096+(keyboard?editor.choice*65536u:0)+picker112.cursor*16777619u+picker112.mode*67108864u;
 if(!f.fade){
 if(f.page==F56_HOME&&(pressed&(2|8192))&&f.row==0)devMode=(int)f.unlocked;
 if(f.page==F56_SETTINGS){
  if(!screen.editing61)screen.value61=pause_value61(NULL,autosave,pause_setting_tab255(&screen),pause_setting_row255(&screen));
  int action=pause_input(&screen,pressed);
  if(action==PA_OPTION_PREVIEW61||action==PA_OPTION_CANCEL61){pause_set61(NULL,autosave,pause_setting_tab255(&screen),pause_setting_row255(&screen),screen.value61);if(action==PA_OPTION_PREVIEW61&&screen.tab==P53_AUDIO&&screen.row>=6)sound_menu58();}
  if(action==PA_PREFS_SAVE58){if(screen.tab==P53_MESSAGES)prefsHaveMessages61=1;if(screen.tab==P53_GAMEPLAY&&screen.row==4&&disk)autosave_commit50b(autosave);snprintf(status,sizeof(status),disk&&prefs_save56()?"Preferences saved.":"Preferences apply for this session.");}
  if(action==PA_SCREEN_SAVE55)snprintf(status,sizeof(status),disk&&screen_save55()?"Screen adjustment saved.":"Screen adjustment is session-only.");
  if(action==PA_RESUME)frontend_goto56(&f,F56_HOME,F56_NONE);
 }else if(f.page==F56_CREATE){
  if(keyboard){if(editor.length>=19&&(pressed&2)&&editor.choice<npc_editor_count55(&editor)-1)pressed&=~2u;int action=npc_editor_input55(&editor,pressed);if(action==2)keyboard=0;else if(action==1){if(frontend_name56(editor.text)){snprintf(name,sizeof(name),"%.19s",editor.text);keyboard=0;status[0]=0;}else snprintf(status,sizeof(status),"Use 1-19 letters/numbers, with no edge spaces.");}}
  else if(picker112.mode)appearance_input112(&picker112,&creationAppearance58,pressed);
  else if(pressed&4)frontend_goto56(&f,F56_CHARACTERS,F56_NONE);
  else if(pressed&(1024|2048))createRow=(createRow+((pressed&1024)?10:1))%11;
  else if(createRow>=1&&createRow<=6&&(pressed&(4096|8192|2|8))){front_stat_adjust58(initialStats,(unsigned)createRow-1,(pressed&(4096|8))?-1:1);}
  else if(createRow==7&&(pressed&(4096|8192|2)))creationSex=!creationSex;
  else if((createRow==8||createRow==9)&&(pressed&(8192|2)))appearance_open112(&picker112,creationAppearance58,(unsigned)createRow-7);
  else if(pressed&2){if(createRow==0){snprintf(editor.text,sizeof(editor.text),"%s",name);editor.length=(unsigned)strlen(name);keyboard=1;}else if(createRow==10){if(!disk)snprintf(status,sizeof(status),"HDD unavailable; cannot create a saved character.");else if(frontend_name56(name))frontend_create56(&f);else snprintf(status,sizeof(status),"Choose a character name first.");}}
 }else frontend_input56(&f,pressed);
 }
 unsigned afterCursor58=f.row+f.slot*16+(f.page==F56_SETTINGS?(unsigned)(screen.tab*16+screen.row):settingsRow)*256+createRow*4096+(keyboard?editor.choice*65536u:0)+picker112.cursor*16777619u+picker112.mode*67108864u;if((pressed&(1024|2048|4096|8192|32|512))&&beforeCursor58!=afterCursor58)sound_menu58();
 if(f.page==F56_CHARACTERS)character_pages_tick62(&characterPages62,f.slot/3,ms);unsigned action=frontend_tick56(&f,ms);developerUnlocked56=(int)f.unlocked;
 pb_wait_for_vbl();pb_target_back_buffer();pb_reset();while(pb_busy()){}hud_frame_begin253();gpu_program_frame51();pb_fill(0,0,640,480,0xff181818);frontend_background56(f.page);
 if(f.page==F56_CHARACTERS){unsigned first=f.slot/3*3;for(unsigned c=first;c<first+3;c++){int record=bank_latest56(c);if(record>=0)frontend_preview56(characterRecords56[c][record].job,(float)front_slot_shadow58(c),213,(unsigned)(c-first),characterRecords56[c][record].appearance58,characterRecords56[c][record].sex58,characterRecords56[c][record].headSources180,0);}}
 else if(f.page==F56_CREATE){pb_fill(60,96,152,196,0xffeaf0f5);frontend_preview56(0,137,244,0,creationAppearance58,(unsigned)creationSex,NULL,creationTurn191.direction);}
 hud_batch_begin();
 if(f.page==F56_PRESS||f.page==F56_HOME){}
 else if(f.page==F56_DEVELOPER){ui_panel(133,222,374,158,"Developer Mode",0,-1);ui_text(149,254,"Choose a character to edit and test.");ui_scaled(149,283,.85f,"Build, classes, items, practice and travel");ui_scaled(149,308,.85f,"share the existing testing tools.");ui_text(149,342,"A: choose character   B: back");}
 else if(f.page==F56_CHARACTERS){frontend_page_arrows62(f.slot/3);frontend_page_indicators62(&characterPages62);unsigned first=f.slot/3*3;if(devMode)ui_scaled(48,77,.8f,"Developer Mode");for(unsigned c=first;c<first+3;c++){int r=bank_latest56(c);unsigned x=(unsigned)front_slot_x58(c);if(c==f.slot)ui_outline(x,98,130,138,0xffe5bc30);if(r<0&&bank_occupied56(c))pb_fill(x+2,100,126,134,0x60000000);ui_scaled(x+4,243,.75f,"%u: %.16s",c+1,r>=0?characterRecords56[c][r].name:bank_occupied56(c)?"Unsupported":"Empty slot");}int r=bank_latest56(f.slot);if(r>=0){CharacterRecord56*c=&characterRecords56[f.slot][r];ui_scaled(98,258,.8f,"%.19s",c->name);ui_scaled(98,274,.8f,"%.18s",job_name(c->job));ui_scaled(98,290,.8f,"%u / %u",c->level,c->joblevel);ui_scaled(98,306,.8f,"%d",c->exp);ui_scaled(98,322,.8f,"%d",c->hp);ui_scaled(98,338,.8f,"%d",c->sp);for(unsigned i=0;i<6;i++)ui_scaled(250,258+i*16,.8f,"%u",c->stats[i]);}ui_panel(40,400,560,44,"",0,-1);ui_hint_center200(48,419,544,22,.85f,"D-pad: slots   LB/RB: page   A: play/create   X: delete   B: back");if(f.deleteConfirm){ui_panel(130,188,380,114,"Delete character?",0,-1);ui_text(147,221,"All of this character's saves are deleted.");ui_text(147,256,"A: delete    B: keep character");}}
 else if(f.page==F56_CREATE){preview_hint191(&creationTurn191,137,254);pb_fill(218,91,378,301,0xffffffff);ui_panel(statPanel112.x,statPanel112.y,statPanel112.w,statPanel112.h,"Starting stats",createRow>=1&&createRow<=6,-1);frontend_stat_web58(initialStats,createRow>=1&&createRow<=6?createRow-1:-1);ui_scaled(440,333,.65f,"Opposite stats trade points.");ui_hint64(440,353,.65f,"Left/right: adjust");appearance_panels112(creationAppearance58,&picker112,createRow);if(createRow==0)ui_outline(87,298,107,19,0xffe5bc30);ui_fit47(93,302,101,.8f,name[0]?name:"Choose a name");ui_cell(64,326,145,25,createRow==7);ui_scaled(72,332,.8f,"Gender: %s",creationSex?"Male":"Female");ui_cell(64,363,145,25,createRow==10);ui_scaled(72,369,.8f,"Create character");ui_hint64(46,446,.8f,picker112.mode?"D-pad: preview   A: keep choice   B: undo":"Up/down: field   A / Right: open   B: back");}
 else if(f.page==F56_SETTINGS)ui_pause_options50b(&screen,0,0,sceneryEnabled61,disk,status,prefsTooltip61,prefsPopup61,autosave->choice,prefsAttack56,prefsView56,0);
 if(*status&&f.page!=F56_SETTINGS){ui_panel(50,445,540,27,"",0,-1);ui_scaled(60,451,.75f,"%.85s",status);}if(!*controller){ui_panel(152,12,336,32,"",0,-1);ui_text(164,20,"Connect a controller to continue.");}
 hud_batch_end();if(f.page==F56_CREATE){appearance_thumbnails112(creationAppearance58,(unsigned)creationSex);if(keyboard){hud_batch_begin();frontend_keyboard56(&editor);hud_batch_end();}}if(f.page==F56_PRESS||f.page==F56_HOME){if(!titleFontTexture58)titleFontTexture58=frontend_art56(titleFont58,titleFontBytes58,512*128*4);unsigned first=f.page==F56_PRESS?0:1,last=f.page==F56_PRESS?1:3;if(f.page==F56_HOME){unsigned w=titleLabels58[f.row+1][2];pb_fill((640-w)/2,298+f.row*35,w,30,0x90e7ba36);}hud_setup_direct(titleFontTexture58,512,128,2048,0x0001122a,1);for(unsigned i=first;i<last;i++){const unsigned*r=titleLabels58[i];hud_quad((int)((640-r[2])*.5f+.5f),i?298+(i-1)*35:376,r[2],32,r[0],r[1],r[2],32);}if(f.unlocked){const unsigned*r=titleLabels58[3];hud_quad((640-r[2])/2,245,r[2],32,r[0],r[1],r[2],32);}}frontend_fade56(f.opaque);while(pb_busy()){}while(pb_finished()){}
 if(action==F56_OPEN_DEVELOPER){devMode=1;}
 else if(action==F56_DELETE_CHARACTER){int ok=disk&&bank_delete_character56(f.slot);frontend_scan_slots56(&f);snprintf(status,sizeof(status),ok?"Character deleted.":"Could not delete every save; remaining records kept.");}
 else if(action==F56_OPEN_CHARACTER||action==F56_CREATE_CHARACTER){
  int ok=0;if(action==F56_OPEN_CHARACTER){int record=bank_latest56(f.slot);save_select56(f.slot,0);if(disk&&record>=0)ok=bank_load56(saves,game,(unsigned)record);}else ok=frontend_new56(game,f.slot,name,initialStats,(unsigned)creationSex,saves,disk);
  if(ok){prefs_character61(game);developerSession56=devMode;frontend_art_release56();frontendFadeIn56=180;return 1;}
  snprintf(status,sizeof(status),"Character could not be %s. Original saves are kept.",action==F56_OPEN_CHARACTER?"loaded":"created");f.page=f.nextPage=F56_CHARACTERS;f.fade=2;f.fadeMs=0;f.opaque=255;bank_scan56();frontend_scan_slots56(&f);
 }
 }
}
#endif
