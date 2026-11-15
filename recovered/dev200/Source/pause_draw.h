/* RO-style grouped settings with explicit field transactions. */
#include "pause_ui.h"
#include "autosave50b.h"
#include "pause_settings61.h"
static const char*pauseTabs61[P53_TABS]={"Game","Gameplay","Audio","Video","Messages","Testing","Diagnostics"};
static void pause_row61(int tab,int row,char*label,char*value,unsigned autosave,unsigned attack,unsigned view,int tips,unsigned popups,int invincible,int diagnostics){
 const char*name="";value[0]=0;int n=0;Autosave50b a={.choice=autosave};n=pause_value61(NULL,&a,tab,row);
 if(tab==P53_GAME){static const char*names[]={"Save character...","Load character...","Companions...","Return to title...","Resume game"};name=names[row];}
 else if(tab==P53_GAMEPLAY){static const char*names[]={"Auto attack","Basic Attack First Target","Auto target herbs","Auto loot","Autosave","Left stick tolerance","Right stick tolerance"};name=names[row];if(row==0)snprintf(value,48,"%s",attack?"Toggle":"Cancel on Kill");else if(row==1)snprintf(value,48,"%s",n?"Enemies":"Items");else if(row==4)snprintf(value,48,"%s",autosaveNames50b[autosave<7?autosave:1]);else if(row>=5)snprintf(value,48,"%d%%",n*2);else snprintf(value,48,"%s",n?"ON":"OFF");}
 else if(tab==P53_AUDIO){static const char*names[]={"Music","Music volume","Effects","Effects volume","Enemy sounds","Enemy sounds volume","Menu navigation sound","Menu sound volume"};name=names[row];if(row&1)snprintf(value,48,"%d%%",n);else snprintf(value,48,"%s",n?"ON":"OFF");}
 else if(tab==P53_VIDEO){static const char*names[]={"Monster Draw Range","Scenery Draw Range","Scenery","Minimap","Compass","Screen adjustment...","Map Draw Range","NPC Draw Range","Always Show Quests"};name=names[row];if(row==8)snprintf(value,48,"%s",alwaysShowQuests65?"ON":"OFF");else if(row<2||row==6||row==7)snprintf(value,48,"%s",monsterViewNames52[row==0?(view<MONSTER_VIEW_COUNT53?view:MONSTER_VIEW_DEFAULT53):row==1?sceneryView60:row==6?mapView64:npcView64]);else if(row==3||row==4)snprintf(value,48,"%s",(const char*[]){"OFF","SMALL","LARGE"}[n]);else if(row<5)snprintf(value,48,"%s",n?"ON":"OFF");}
 else if(tab==P53_MESSAGES){static const char*names[]={"Tooltips","Damage","EXP / level-up","Skill / status","Item / service","System","Spell name callouts","Loot messages"};name=names[row];snprintf(value,48,"%s",(!row?tips:!(popups&(1u<<(row-1))))?"ON":"OFF");}
 else if(tab==P53_TESTING){static const char*names[]={"Developer tools...","Test travel...","Invincibility","Water appearance","Water animation frames"};name=names[row];if(row==2)snprintf(value,48,"%s",invincible?"ON":"OFF");else if(row==3)snprintf(value,48,"%s",waterOriginal190?"ORIGINAL":"CURRENT");else if(row==4)snprintf(value,48,"%s",waterFrameNames200[waterAnimation200<9?waterAnimation200:0]);}else{static const char*names[]={"Diagnostics Window","Frame timings...","Audio report...","Memory report..."};name=names[row];if(!row)snprintf(value,48,"%s",diagnostics?"ON":"OFF");}
 snprintf(label,64,"%s",name);
}
/* Small solid triangles share the HUD palette and need no new texture. */
#include "option_triangle200.h"
static void ui_pause_options50b(const PauseUI*u,int confirm,int help,int scenery,int disk,const char*status,int tips,unsigned popupMask,unsigned autosave,unsigned attackMode,unsigned view,int invincible){
 (void)scenery;
 if(u->detail==3){ui_outline(4,4,632,472,0xffffffff);ui_panel(120,94,400,286,"Screen adjustment",0,-1);static const char*names[]={"Width","Height","Horizontal position","Vertical position","Restore defaults","Done"};for(int i=0;i<6;i++){int y=127+i*29;ui_cell(132,y,376,26,i==u->screenRow);if(i<4)ui_scaled(142,y+4,1,"%s: %d%s%s",names[i],screen_layout_value55((unsigned)i),i<2?"%":" px","");else ui_scaled(142,y+4,1,"%s",names[i]);if(i==u->screenRow&&u->screenEditing&&i<4){int n=screen_layout_value55((unsigned)i),lo=i<2?50:i==2?-64:-48,hi=i<2?100:i==2?64:48;if(n>lo)ui_option_triangle62(134,y+12,0);if(n<hi)ui_option_triangle62(498,y+12,1);}}ui_hint64(140,318,.8f,u->screenEditing?"LEFT/RIGHT: adjust   A: save   B: cancel":"A: edit   B: Video menu");ui_scaled(140,341,.75f,"Fit the white border inside your TV picture.");return;}
 ui_panel(14,48,490,380,u->frontOnly61?"Settings":"MyRO - Paused",0,-1);pb_fill(23,79,122,281,0xffdbe3ed);
 for(int k=0;k<pause_tabs58(u);k++){int i=pause_first61(u)+k,y=91+k*35;ui_cell(27,y-2,114,28,u->tab==i&&!u->inside);ui_scaled(35,y+4,1,"%s",pauseTabs61[i]);}
 if(confirm){ui_scaled(158,133,.8f,"Load the selected character?");ui_scaled(158,160,.75f,"Unsaved progress will be replaced.");ui_hint64(158,212,.8f,"A: load    B: back");}
 else if(!u->detail)for(int i=u->tab==P53_MESSAGES?(u->row/5)*5:0;i<pause_count(u->tab)&&(u->tab!=P53_MESSAGES||i<(u->row/5)*5+5);i++){char label[64],value[48];int y=88+(u->tab==P53_MESSAGES?i%5:i)*(u->tab==P53_MESSAGES?52:u->tab==P53_VIDEO?28:31);pause_row61(u->tab,i,label,value,autosave,attackMode,view,tips,popupMask,invincible,help);ui_cell(151,y-2,344,29,i==u->row&&u->inside);ui_scaled(159,y+2,.92f,"%s",label);int width=ui_text_width(value,.85f);ui_scaled((u->editing61&&i==u->row?476:488)-width,y+3,.85f,"%s",value);if(u->editing61&&i==u->row){if(pause_step61(u,-1)!=u->value61)ui_option_triangle62(465-width,y+9,0);if(pause_step61(u,1)!=u->value61)ui_option_triangle62(484,y+9,1);}
  if(u->tab==P53_MESSAGES){static const char*help64[]={"Show contextual help for selected actions.","Show combat damage, criticals and misses.","Show earned EXP and level-up notices.","Show skill results and status notices.","Show item pickups and service results.","Show general game and system notices.","Show spell names when spells are cast.","Show messages describing collected loot."};pb_fill(157,y+29,332,19,0xffeaf0f5);ui_scaled(163,y+31,.8f,"%s",help64[i]);}
  int slider=(u->tab==P53_TESTING&&i==4)||(u->tab==P53_GAMEPLAY&&i>=4)||(u->tab==P53_AUDIO&&(i&1))||(u->tab==P53_VIDEO&&(i<2||i==6||i==7));if(slider){unsigned position=0;if(u->tab==P53_TESTING)position=waterAnimation200*100/8;else if(u->tab==P53_AUDIO){Autosave50b a={0};position=pause_value61(NULL,&a,u->tab,i);}else if(u->tab==P53_GAMEPLAY)position=i==4?(autosave<7?autosave:1)*100/6:stickSteps58[i-5]*4;else{unsigned setting=i==0?view:i==1?sceneryView60:i==6?mapView64:npcView64;position=setting&&setting<MONSTER_VIEW_COUNT53?(monsterCells52[setting]<16?0:monsterCells52[setting]-16)*100/112:100;}int x=386;pb_fill(x,y+21,100,2,0xff8999b2);pb_fill(x+(int)position-2,y+18,4,8,0xffe5bc30);}
 }
 ui_hint64(28,376,.78f,u->editing61?"LEFT/RIGHT: adjust   A: save   B: cancel":u->inside?"LT/RT: category   A: edit   B: back":"LT/RT: category   A: open   B: back");
 ui_hint64(28,400,.72f,u->frontOnly61?"Settings also apply when you enter the game.":"START: resume game");
 char lines[8][96];int rows=ui_wrap(status,lines,102,.68f),sideHeight=64+rows*18;if(sideHeight<90)sideHeight=90;ui_panel(512,62,120,sideHeight,"Info",0,-1);for(int i=0;i<rows&&i<8;i++)ui_scaled(519,91+i*18,.68f,"%s",lines[i]);ui_scaled(519,62+sideHeight-32,.65f,"MyRO v2.0.0 DEV");ui_scaled(519,62+sideHeight-16,.65f,disk?"HDD available":"Session only");
}

static void ui_pause_options41(const PauseUI*u,int confirm,int help,int scenery,int disk,const char*status,int tips,unsigned popupMask){ui_pause_options50b(u,confirm,help,scenery,disk,status,tips,popupMask,1,0,0,0);}

static void ui_pause_options(const PauseUI*u,int confirm,int help,int scenery,int disk,const char*status,int tips){ui_pause_options41(u,confirm,help,scenery,disk,status,tips,POP_DAMAGE);}

static void ui_pause(const PauseUI*u,int confirm,int help,int scenery,int disk,const char*status){ui_pause_options(u,confirm,help,scenery,disk,status,1);}

/* Actual playback diagnostics, shown only on the Audio category. */
static void ui_audio_queue50(unsigned ahead,unsigned gaps,unsigned restarts,unsigned bad,unsigned cursor,unsigned last,unsigned flags,int decoderError,const char*status){
 ui_scaled(159,126,.75f,"Queue %u/4   gaps %u   restarts %u",ahead,gaps,restarts);
 ui_scaled(159,151,.65f,"DMA %u -> %u  flags %02X  invalid %u  MP3 %d",cursor,last,flags,bad,decoderError);
 ui_scaled(159,176,.65f,"%.64s",status);
}
static void ui_audio_residency50(unsigned encodedKiB,unsigned peakKiB,int readError,unsigned spellKiB){
 ui_scaled(159,201,.65f,"Music %u KiB  peak %u  read %d  spell %u KiB",encodedKiB,peakKiB,readError,spellKiB);
}
