/* MIT. Original solo offensive songs, delayed jokes/screams and Encore. */
#include "class_callouts50.h"
static int class_song_weapon50(const Combat*g,unsigned id){int weapon=inventory_wtype46(g);return id==174?weapon==14:id==181?weapon==15:weapon==14||weapon==15;}
static void class_song_start50(Combat*g,int id,int rank){class_sound_emit50(g,id);
 g->class50.song=id;g->class50.songRank=rank;g->class50.lastSong=id;g->class50.lastSongRank=rank;
 g->class50.songStarted=g->time;g->class50.songUntil=g->time+class_duration50(id,rank,0);g->class50.songNext=g->time;g->class50.songDrain=g->time+(id==183?10:3);g->autoAttack=0;
}
static void class_performer_execute50(Combat*g,unsigned id,int rank,int target,float x,float y){
 if(id==174||id==181||id==183){class_song_start50(g,id,rank);return;}
 if(id==176){g->class50.song=0;return;}
 if(id==177){class_song_start50(g,g->class50.lastSong,g->class50.lastSongRank);return;}
 if(id==175||id==182){g->class50.next[id-127]=g->time+2;g->class50.level[id-127]=rank;
  if(id==175)combat_notice(g,POP_SPEECH,"%s",ba_frostjoke50[combat_random(g)%(sizeof(ba_frostjoke50)/sizeof(*ba_frostjoke50))]);
  else combat_notice(g,POP_SPEECH,"%s",dc_scream50[combat_random(g)%(sizeof(dc_scream50)/sizeof(*dc_scream50))]);return;
 }
 CombatMob*m=&g->mobs[target];
 if(id==173||id==180){skill_hit(g,target,class_physical50(g,m,125+25*rank,0,-1),0);return;}
 if(id==178){if(!combat_status_boss(m)&&class_chance50(g,50,100))m->class50.confuseUntil=g->time+class_duration50(id,rank,0);return;}
 if(id==184&&!combat_status_boss(m)&&g->level>mobSourceLevel[m->kind]&&(mobClassData50[m->kind][0]==6||mobClassData50[m->kind][0]==7||mobClassData50[m->kind][0]==8)&&class_chance50(g,70,100))m->class50.charmUntil=g->time+class_duration50(id,rank,0);
 (void)x;(void)y;
}
static void class_performer_tick50(Combat*g){
 for(int id=175;id<=182;id+=7){if(!g->class50.next[id-127]||g->class50.next[id-127]>g->time)continue;g->class50.next[id-127]=0;int rank=g->class50.level[id-127];
  for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(!class_in_area50(g,m,g->x,g->y,112)||combat_status_boss(m))continue;
   if(id==175){if(!mobFreezeImmune[m->kind]&&class_chance50(g,(15+5*rank)*(100-mobFreezeMdef[m->kind])/100,100)){m->freezeAt=g->time;m->frozenLeft=class_duration50(id,rank,1);m->moving=0;}}
   else class_stun50(g,m,25+5*rank,class_duration50(id,rank,1));
  }
 }
 int id=g->class50.song,rank=g->class50.songRank;if(!id)return;
 if(g->hp<=0||g->class50.songUntil<=g->time||!class_song_weapon50(g,id)){g->class50.song=0;return;}
 if(g->time>=g->class50.songDrain){if(g->sp<1){g->class50.song=0;return;}g->sp--;g->class50.songDrain+=id==183?10:3;}
 if(g->time<g->class50.songNext)return;g->class50.songNext+=3;
 int oldSkill=g->fxSkill,oldRank=g->fxRank48;g->fxSkill=id;g->fxRank48=rank;
 for(int i=0;i<MOB_COUNT;i++){CombatMob*m=&g->mobs[i];if(!class_in_area50(g,m,g->x,g->y,28))continue;
  if(id==174)skill_hit(g,i,(30+10*rank+3*class_rank50(g,172))*class_attack_rate48(g,m,0)/100,0);
  else if(id==181){if(!m->class50.initialized){m->class50.sp=mobClassData50[m->kind][2];m->class50.initialized=1;}m->class50.sp-=5+5*rank+(class_rank50(g,179)?5+class_rank50(g,179):0);if(m->class50.sp<0)m->class50.sp=0;}
  else if(id==183&&!combat_status_boss(m)){m->class50.danceUntil=g->time+class_duration50(id,rank,1);m->class50.danceMove=stat_value(g,1)/10+3*rank+5+class_rank50(g,179);m->class50.danceAttack=stat_value(g,4)/10+3*rank+5+class_rank50(g,179);}
 }
 g->fxSkill=oldSkill;g->fxRank48=oldRank;
}
