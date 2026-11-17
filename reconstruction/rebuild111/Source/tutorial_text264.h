/* Targeted tutorial wording only. Original script branches/rewards stay intact. */
#ifndef MYRO_TUTORIAL_TEXT264_H
#define MYRO_TUTORIAL_TEXT264_H
/* Original program-owner keys, verified from the released script metadata.
 * VM owners are script keys, not NPC record indexes. */
#define TUTORIAL_EDWIN264 UINT64_C(2160113634)
#define TUTORIAL_ALICE264 UINT64_C(1371341032)
static int tutorial_training_owner264(uint64_t owner){static const uint64_t keys[]={UINT64_C(1130313496),UINT64_C(92636178),UINT64_C(3986431089),TUTORIAL_ALICE264,UINT64_C(1441133371),TUTORIAL_EDWIN264,UINT64_C(1833317889),UINT64_C(2008477514),UINT64_C(1766847468),UINT64_C(345442616)};for(unsigned i=0;i<sizeof(keys)/sizeof(*keys);i++)if(keys[i]==owner)return 1;return 0;}

static const char*tutorial_text264(uint64_t owner,const char*page,const char*message){
 if(owner==TUTORIAL_EDWIN264){/* Edwin's original interface lesson. */
  if(strstr(message,"In the Option Window, you can adjust"))return "Press START to open Settings. Audio controls music and sound effects. Video controls the minimap, compass and screen adjustment.";
  if(strstr(message,"With the sound button, you can"))return "In Audio, choose a setting and press A to edit it. LEFT/RIGHT adjusts the value, A saves and B cancels.";
  if(strstr(message,"With the Skin option, you can"))return "Draw ranges and water options are under Diagnostics > Video Testing.";
  if(!strcmp(message,"a skin.")&&strstr(page,"Draw ranges and water"))return "";
  if(strstr(message,"Snap function")||strstr(message,"snap options"))return "";
  if(strstr(message,"Well, it all depends on your experience."))return "B returns to the previous menu. Your settings are kept separately from your character.";
  if(!strncmp(message,"In Skills, highlight a skill",27)||!strncmp(message,"Press Select to choose a window",31))return "";/* Already taught by the relevant tutor. */
  if(!strcmp(message,"If you want to check the weight limit of the items you can carry, check the bottom left of the"))return "Your current weight and Zeny appear at the bottom of Items.";
  if(!strcmp(message,"Basic Info window.")&&strstr(page,"weight and Zeny"))return "";
  if(strstr(message,"The numerical value next to the weight limit"))return "Zeny is the currency used by shops and services. The weight readout shows your current load and carrying limit.";
 }
 if(owner==TUTORIAL_ALICE264){/* Alice's inventory/equipment lesson. */
  if(strstr(message,"In the Inventory Window, you'll see 3 tabs"))return "Items shows everything you are carrying in one grid. Consumables such as potions can be used there or assigned to a hotbar.";
  if(!strcmp(message,"items in the ^4A708Bequip^000000 tab"))return "weapons and armor among your carried items.";
  if(!strcmp(message,"items in the ^4A708Betc^000000 tab"))return "materials and other carried items.";
 }
 return message;
}
/* Preserve original option ordinals when removing the online-party lesson. */
static const char*tutorial_option264(uint64_t owner,const char*text,size_t*length){if(owner==TUTORIAL_EDWIN264){if(*length==12&&!strncmp(text,"Party Window",12))return NULL;if(*length==13&&!strncmp(text,"Option Window",13)){*length=8;return "Settings";}}return text;}
static int npc_dialogue_visible264(uint64_t owner,const char*text){
 const char*p=text;while(*p==' '||*p=='\n'||*p=='\r'||*p=='\t')p++;
 if(tutorial_training_owner264(owner)&&*p=='['){const char*end=strchr(p,']'),*nl=strchr(p,'\n');if(end&&end-p<64&&(!nl||end<nl))p=end+1;}
 while(*p){if(*p=='^'){unsigned i=1;while(i<=6&&((p[i]>='0'&&p[i]<='9')||(p[i]>='a'&&p[i]<='f')||(p[i]>='A'&&p[i]<='F')))i++;if(i==7){p+=7;continue;}}if(*p!=' '&&*p!='\n'&&*p!='\r'&&*p!='\t')return 1;p++;}return 0;
}
#endif
