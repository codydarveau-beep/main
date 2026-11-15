/* One settings adapter shared by the title and in-game pause menus. */
#ifndef MYRO_PAUSE_SETTINGS61_H
#define MYRO_PAUSE_SETTINGS61_H
static unsigned prefsTooltip61=1,prefsPopup61;
static int pause_value61(const Combat*g,const Autosave50b*a,int tab,int row){
 if(tab==P53_GAMEPLAY){switch(row){case 0:return g?g->autoAttackToggle52:prefsAttack56;case 1:return basicFirst60;case 2:return autoHerbs60;case 3:return !autoLootOff58;case 4:return a->choice;default:return stickSteps58[row-5];}}
 if(tab==P53_AUDIO){switch(row){case 0:return !musicMuted;case 1:return musicVolume;case 2:return !soundMuted;case 3:return soundVolume;case 4:return !enemyMuted60;case 5:return enemyVolume60;case 6:return menuSoundEnabled58;default:return menuVolume60;}}
 if(tab==P53_VIDEO){switch(row){case 0:return g?g->monsterView52:prefsView56;case 1:return sceneryView60;case 2:return sceneryEnabled61;case 3:return minimapSize60;case 4:return compassSize60;case 6:return mapView64;case 7:return npcView64;case 8:return alwaysShowQuests65;default:return 0;}}
 if(tab==P53_TESTING)return row==3?waterOriginal190:row==4?waterAnimation200:0;
 if(tab==P53_MESSAGES)return !row?(g?!g->tooltipsDisabled:prefsTooltip61):!((g?g->popupDisabled:prefsPopup61)&(1u<<(row-1)));
 return 0;
}
static void pause_set61(Combat*g,Autosave50b*a,int tab,int row,int value){unsigned v=value<0?0:(unsigned)value;
 if(tab==P53_AUDIO){EnterCriticalSection(&soundLock);switch(row){case 0:musicMuted=!v;break;case 1:musicVolume=v>100?100:v;break;case 2:soundMuted=!v;if(!v){memset(soundVoices,0,sizeof(soundVoices));menuSoundActive58=0;}break;case 3:soundVolume=v>100?100:v;break;case 4:enemyMuted60=!v;break;case 5:enemyVolume60=v>100?100:v;break;case 6:menuSoundEnabled58=!!v;if(!v)menuSoundActive58=0;break;case 7:menuVolume60=v>100?100:v;break;}LeaveCriticalSection(&soundLock);return;}
 if(tab==P53_GAMEPLAY){switch(row){case 0:prefsAttack56=!!v;if(g)g->autoAttackToggle52=!!v;break;case 1:basicFirst60=!!v;break;case 2:autoHerbs60=!!v;break;case 3:autoLootOff58=!v;break;case 4:a->choice=v<7?v:6;break;case 5:case 6:stickSteps58[row-5]=v<26?v:25;break;}return;}
 if(tab==P53_VIDEO){switch(row){case 0:prefsView56=v<MONSTER_VIEW_COUNT53?v:MONSTER_VIEW_DEFAULT53;if(g)g->monsterView52=prefsView56;break;case 1:sceneryView60=v<MONSTER_VIEW_COUNT53?v:SCENERY_VIEW_DEFAULT180;break;case 2:sceneryEnabled61=!!v;break;case 3:minimapSize60=v<3?v:1;break;case 4:compassSize60=v<3?v:1;break;case 6:mapView64=v<MONSTER_VIEW_COUNT53?v:MAP_VIEW_DEFAULT180;break;case 7:npcView64=v<MONSTER_VIEW_COUNT53?v:NPC_VIEW_DEFAULT180;break;case 8:alwaysShowQuests65=!!v;break;}return;}
 if(tab==P53_TESTING){if(row==3)waterOriginal190=!!v;else if(row==4)waterAnimation200=v<9?v:8;return;}
 if(tab==P53_MESSAGES){if(!row){prefsTooltip61=!!v;if(g)g->tooltipsDisabled=!v;}else{unsigned bit=1u<<(row-1);if(v)prefsPopup61&=~bit;else prefsPopup61|=bit;if(g)g->popupDisabled=(g->popupDisabled&~bit)|(prefsPopup61&bit);}}
}
#endif
