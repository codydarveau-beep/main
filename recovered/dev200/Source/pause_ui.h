/* SPDX-License-Identifier: MIT. Pure pause-menu controller, host testable. */
#ifndef MYRO_PAUSE_UI_H
#define MYRO_PAUSE_UI_H
#include "screen_layout55.h"
#include "view_controls54.h"
#include "controller_tolerance58.h"
typedef struct{int tab,row,detail,inside,screenRow,screenEditing,screenBefore,allowTesting58,stickEditing58,stickBefore58,editing61,value61,before61,frontOnly61;} PauseUI;
enum{PA_NONE,PA_SAVE,PA_LOAD,PA_TRAVEL,PA_RESUME,PA_MUSIC_DOWN,PA_MUSIC_UP,PA_SFX_DOWN,PA_SFX_UP,PA_MUSIC_MUTE,PA_SFX_MUTE,PA_TONE,PA_HELP,PA_SCENERY,PA_DEV,PA_MEMO,PA_TOOLTIPS,PA_TOGGLES,PA_POP_DAMAGE,PA_POP_REWARDS,PA_POP_SKILLS,PA_POP_ITEMS,PA_POP_SYSTEM,PA_POP_SPEECH,PA_POP_LOOT,PA_AUTOSAVE_DOWN50B,PA_AUTOSAVE_UP50B,PA_ATTACK_MODE52,PA_VIEW_DOWN52,PA_VIEW_UP52,PA_INVINCIBLE52,PA_SCREEN_SAVE55,PA_TITLE56,PA_PREFS_SAVE58,PA_MENU_SOUND58,PA_AUTOLOOT58,PA_OPTION_PREVIEW61,PA_OPTION_CANCEL61,PA_MERC180};
enum{P53_GAME,P53_GAMEPLAY,P53_AUDIO,P53_VIDEO,P53_MESSAGES,P53_TESTING,P53_DIAGNOSTICS64,P53_TABS};
static int pause_first61(const PauseUI*u){return u->frontOnly61?P53_GAMEPLAY:P53_GAME;}
static int pause_tabs58(const PauseUI*u){return u->frontOnly61?4:P53_TABS-(u->allowTesting58?0:2);}
static int pause_count(int tab){static const unsigned char rows[P53_TABS]={5,7,8,9,8,5,4};return tab>=0&&tab<P53_TABS?rows[tab]:0;}
static int pause_field61(const PauseUI*u){return (u->tab==P53_TESTING&&u->row>=3)||u->tab==P53_GAMEPLAY||u->tab==P53_AUDIO||u->tab==P53_MESSAGES||(u->tab==P53_VIDEO&&(u->row!=5));}
static int pause_adjustable53(const PauseUI*u){return u->editing61||u->screenEditing;}
static int pause_autosave53(const PauseUI*u){return u->inside&&u->editing61&&u->tab==P53_GAMEPLAY&&u->row==4;}
static void pause_screen_cancel55(PauseUI*u){if(u->editing61){u->value61=u->before61;u->editing61=0;}if(u->screenEditing){screen_layout_set55((unsigned)u->screenRow,u->screenBefore);u->screenEditing=0;}}
static int pause_step61(const PauseUI*u,int delta){int max=1,step=1;if(u->tab==P53_TESTING&&u->row==4)max=8;if(u->tab==P53_VIDEO&&(u->row<2||u->row==6||u->row==7))return (int)monster_view_step52((unsigned)u->value61,delta);if(u->tab==P53_GAMEPLAY){if(u->row==4)max=6;else if(u->row>=5)max=25;}if(u->tab==P53_VIDEO&&(u->row==3||u->row==4))max=2;if(u->tab==P53_AUDIO&&(u->row&1)){max=100;step=5;}int n=u->value61+delta*step;return n<0?0:n>max?max:n;}
static int pause_input(PauseUI*u,unsigned p){
 if(u->tab<pause_first61(u)||u->tab>=pause_first61(u)+pause_tabs58(u)){u->tab=pause_first61(u);u->row=u->detail=u->inside=u->editing61=0;}
 unsigned categories200=p&(16384u|32768u);if(categories200&&!u->editing61&&!u->screenEditing){if(categories200!=(16384u|32768u)){int first=pause_first61(u),count=pause_tabs58(u);u->tab=first+(u->tab-first+(categories200&32768u?1:count-1))%count;u->row=u->detail=0;}return PA_NONE;}
 if(u->detail==3){if(p&4){if(u->screenEditing)pause_screen_cancel55(u);else u->detail=0;return PA_NONE;}if(u->screenEditing){if(p&2){u->screenEditing=0;return PA_SCREEN_SAVE55;}if(p&(4096|8192))screen_layout_set55((unsigned)u->screenRow,screen_layout_value55((unsigned)u->screenRow)+((p&8192)?1:-1));return PA_NONE;}if(p&4096){u->detail=0;return PA_NONE;}if(p&(1024|2048)){u->screenRow=(u->screenRow+((p&1024)?5:1))%6;return PA_NONE;}if(p&(2|8192)){if(u->screenRow==5){u->detail=0;return PA_NONE;}if(u->screenRow==4){screenLayout55=(ScreenLayout55){100,100,0,0};return PA_SCREEN_SAVE55;}u->screenBefore=screen_layout_value55((unsigned)u->screenRow);u->screenEditing=1;}return PA_NONE;}
 if(u->editing61){if(p&4){pause_screen_cancel55(u);return PA_OPTION_CANCEL61;}if(p&2){u->editing61=0;return PA_PREFS_SAVE58;}if(p&(4096|8192)){u->value61=pause_step61(u,p&8192?1:-1);return PA_OPTION_PREVIEW61;}return PA_NONE;}
 if(p&4){if(u->detail){u->detail=0;return PA_NONE;}if(u->inside){u->inside=0;return PA_NONE;}return PA_RESUME;}
 if(!u->inside){if(p&(1024|2048)){u->tab=pause_first61(u)+(u->tab-pause_first61(u)+((p&1024)?pause_tabs58(u)-1:1))%pause_tabs58(u);u->row=u->detail=0;}else if(p&(2|8192)){u->inside=1;u->row=0;}return PA_NONE;}
 if(p&4096){if(u->detail)u->detail=0;else u->inside=0;return PA_NONE;}
 if(u->detail)return PA_NONE;
 int n=pause_count(u->tab);if(p&1024){u->row=(u->row+n-1)%n;return PA_NONE;}if(p&2048){u->row=(u->row+1)%n;return PA_NONE;}
 if(!(p&(2|8192)))return PA_NONE;
 if(pause_field61(u)){u->before61=u->value61;u->editing61=1;return PA_NONE;}
 if(u->tab==P53_GAME){static const int actions[5]={PA_SAVE,PA_LOAD,PA_MERC180,PA_TITLE56,PA_RESUME};return actions[u->row];}
 if(u->tab==P53_VIDEO&&u->row==5){u->detail=3;u->screenRow=u->screenEditing=0;return PA_NONE;}
 if(u->tab==P53_TESTING){static const int actions[3]={PA_DEV,PA_TRAVEL,PA_INVINCIBLE52};return actions[u->row];}if(u->tab==P53_DIAGNOSTICS64){if(!u->row)return PA_HELP;u->detail=u->row==3?4:u->row;return PA_NONE;}
 return PA_NONE;
}
#endif
