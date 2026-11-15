/* MIT. Explicit manual slots, one autosave, confirmation for overwrite/load/delete. */
#ifndef MYRO_SAVE_BROWSER56_H
#define MYRO_SAVE_BROWSER56_H
typedef struct{int mode,row,confirm;char status[100];}SaveBrowser56;
static SaveBrowser56 saveBrowser56;
static void save_browser_open56(int mode){memset(&saveBrowser56,0,sizeof(saveBrowser56));saveBrowser56.mode=mode;saveBrowser56.row=mode==1?1:0;for(unsigned r=0;r<10;r++)bank_record_scan56(saveCharacter56,r);}
/* Return1closed,2return-to-title,0continue. */
static int save_browser_input56(SaveStore*store,Combat*g,unsigned p,int disk){SaveBrowser56*u=&saveBrowser56;if(p&4){if(u->confirm)u->confirm=0;else return 1;return 0;}if(u->mode==3){if(p&(1024|2048))u->row=(u->row+((p&1024)?2:1))%3;if(p&2){if(u->row==2)return 1;if(u->row==1)return 2;if(disk&&bank_save56(store,g,0))return 2;snprintf(u->status,100,"%.99s",store->status);}return 0;}
 unsigned r=(unsigned)u->row;CharacterRecord56*c=&characterRecords56[saveCharacter56][r];
 if(u->confirm){if(p&2){int op=u->confirm;u->confirm=0;int ok=0;if(op==3)ok=disk&&bank_delete_record56(saveCharacter56,r);else if(op==1)ok=disk&&bank_save56(store,g,r);else if(op==2){npc_game_cancel55(&npcGame55);ok=disk&&bank_load56(store,g,r);if(ok){npc_game_clear55(&npcGame55);npc_variables_reset_transient55(&npcVariables55);npc_native_init55(g);world_town(g);frontendFadeIn56=180;return 1;}}snprintf(u->status,100,"%s",ok?(op==3?"Save deleted.":"Character saved."):store->status);}return 0;}
 if(p&(1024|2048)){u->row=(u->row+((p&1024)?9:1))%10;return 0;}
 if((p&8)&&c->state){u->confirm=3;return 0;}
 if(p&2){if(u->mode==1){if(!r){snprintf(u->status,100,"Choose a manual slot. Autosave is automatic.");return 0;}if(c->state)u->confirm=1;else{int ok=disk&&bank_save56(store,g,r);snprintf(u->status,100,"%s",ok?"Character saved.":store->status);}}else if(c->state==1)u->confirm=2;else snprintf(u->status,100,c->state?"This save is incompatible or unreadable.":"This slot is empty.");}
 return 0;}
static void save_browser_draw56(void){SaveBrowser56*u=&saveBrowser56;ui_panel(111,55,418,375,u->mode==1?"Save Character":u->mode==2?"Load Character":"Return to title",0,-1);if(u->mode==3){static const char*labels[]={"Save and return","Return without saving","Cancel"};ui_scaled(131,100,.85f,"Unsaved progress is lost if you leave it behind.");for(int i=0;i<3;i++){ui_cell(126,147+i*40,388,32,i==u->row);ui_text(141,154+i*40,"%s",labels[i]);}}else for(unsigned r=0;r<10;r++){CharacterRecord56*c=&characterRecords56[saveCharacter56][r];unsigned y=91+r*27;ui_cell(125,y,390,25,(int)r==u->row);char label[32];if(r)snprintf(label,32,"Manual %u",r);else snprintf(label,32,"Autosave");ui_scaled(135,y+5,.8f,"%s: %.19s",label,c->state==1?c->name:c->state?"Incompatible / unreadable":"Empty");if(c->state==1)ui_scaled(370,y+5,.75f,"Lv %u / %u",c->level,c->joblevel);if(c->state==2)pb_fill(128,y+2,384,21,0x60000000);}
 ui_hint64(130,369,.75f,"A: choose   X: delete   B: back");ui_scaled(130,394,.75f,"%.68s",u->status);if(u->confirm){ui_panel(139,170,362,124,u->confirm==1?"Overwrite this save?":u->confirm==2?"Load this save?":"Delete this save?",0,-1);ui_scaled(156,207,.8f,u->confirm==2?"Unsaved progress will be replaced.":"This action replaces or removes this record.");ui_text(156,250,"A: confirm   B: cancel");}}
#endif
