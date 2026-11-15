#include "hired_helpers191.h"
/* MIT. Character-scoped hireling contracts and guild loyalty; no save wire change. */
static uint64_t npc_merc_key180(unsigned family){return npc_variable_key55(family==0?"__myroMercenary180":family==1?"__myroMercFaith180":family==2?"__myroMercCalls180":"__myroMercTimers180",0);}
static int npc_mercenary_store180(NpcGame55*n){
 NpcState55*s=npc_game_character_state55(n);Combat*g=n->player.game;Mercenary180*m=&g->mercenary180;
 if(!m->source&&!m->faith[0]&&!m->faith[1]&&!m->faith[2]&&!m->calls[0]&&!m->calls[1]&&!m->calls[2]&&!npc_state_number55(s,npc_merc_key180(0),0))return 1;
 if(s->count>NPC_STATE_ENTRIES55-104||!npc_state_reserve55(s,s->count+104))return 0;
 unsigned fields[21]={m->source,m->hp,m->sp,m->remaining,m->kills,m->hold};for(unsigned i=0;i<5;i++){fields[6+i]=m->bonusLevel[i];fields[11+i]=m->bonusMS[i];}fields[16]=m->potionRank;fields[17]=m->potionUntil>g->time?(unsigned)((m->potionUntil-g->time)*1000):0;
 fields[18]=m->frenzy180&&m->frenzyNext180>g->time?(unsigned)((m->frenzyNext180-g->time)*1000):0;fields[19]=m->regenBlocked180>g->time?(unsigned)((m->regenBlocked180-g->time)*1000):0;fields[20]=m->frenzyDrain180;
 for(unsigned i=0;i<21;i++)if(!npc_state_set_number55(s,npc_merc_key180(0),i,fields[i]))return 0;
 for(unsigned i=0;i<3;i++)if(!npc_state_set_number55(s,npc_merc_key180(1),i,m->faith[i])||!npc_state_set_number55(s,npc_merc_key180(2),i,m->calls[i]))return 0;
 for(unsigned i=0;i<37;i++){unsigned cd=m->source&&m->cooldown[i]>g->time?(unsigned)((m->cooldown[i]-g->time)*1000):0,buff=m->source&&m->buffUntil[i]>g->time?(unsigned)((m->buffUntil[i]-g->time)*1000):0;if(!npc_state_set_number55(s,npc_merc_key180(3),i,cd)||!npc_state_set_number55(s,npc_merc_key180(3),i+37,buff))return 0;}
 return 1;
}
static unsigned npc_merc_get180(NpcState55*s,unsigned key,unsigned index,unsigned max){int64_t n=npc_state_number55(s,npc_merc_key180(key),index);return n<0||n>max?0:(unsigned)n;}
static void npc_mercenary_load180(NpcGame55*n){Combat*g=n->player.game;Mercenary180*m=&g->mercenary180;NpcState55*s=npc_game_character_state55(n);memset(m,0,sizeof(*m));m->target=m->pendingTarget=-1;if(!MERCENARY_HIRING_ENABLED191)return;
 for(unsigned i=0;i<3;i++){m->faith[i]=npc_merc_get180(s,1,i,32767);m->calls[i]=npc_merc_get180(s,2,i,INT_MAX);}
 unsigned source=npc_merc_get180(s,0,0,6046);const MercenaryData180*d=mercenary_data180(source);if(!d)return;m->source=source;m->hp=npc_merc_get180(s,0,1,d->hp*4);m->sp=npc_merc_get180(s,0,2,d->sp*2);m->remaining=npc_merc_get180(s,0,3,1800000);m->kills=npc_merc_get180(s,0,4,INT_MAX);m->hold=npc_merc_get180(s,0,5,1);for(unsigned i=0;i<5;i++){m->bonusLevel[i]=npc_merc_get180(s,0,6+i,4);m->bonusMS[i]=npc_merc_get180(s,0,11+i,600000);}m->potionRank=npc_merc_get180(s,0,16,3);m->potionUntil=g->time+npc_merc_get180(s,0,17,1800000)/1000.f;
 for(unsigned i=0;i<37;i++){m->cooldown[i]=g->time+npc_merc_get180(s,3,i,3600000)/1000.f;m->buffUntil[i]=g->time+npc_merc_get180(s,3,i+37,3600000)/1000.f;}
 m->frenzy180=m->buffUntil[5]>g->time;m->frenzyNext180=g->time+npc_merc_get180(s,0,18,15000)/1000.f;m->regenBlocked180=g->time+npc_merc_get180(s,0,19,300000)/1000.f;m->frenzyDrain180=npc_merc_get180(s,0,20,d->hp);if(m->frenzy180&&!m->frenzyDrain180)m->frenzyDrain180=mercenary_maxhp180(m)*5/100;if(m->hp>mercenary_maxhp180(m))m->hp=mercenary_maxhp180(m);
 if(!m->hp||!m->remaining){m->source=0;return;}mercenary_place180(g);
}
static int npc_mercenary_item180(void*context,Combat*g,unsigned source){
 NpcGame55*n=context;if(!n||n->player.game!=g)return-1;int contract=source>=12153&&source<=12182,potion=source==12184||source==12185||(source>=12241&&source<=12243);if(!contract&&!potion)return-1;if(!MERCENARY_HIRING_ENABLED191){combat_notice(g,POP_ITEMS,"Hireling contracts are unavailable. Item kept.");return 1;}Mercenary180*m=&g->mercenary180;
 if((contract&&(m->source||g->hp<=0))||(potion&&!mercenary_alive180(g))){combat_notice(g,POP_ITEMS,contract?"A mercenary is already hired. Contract kept.":"Hire a mercenary first. Potion kept.");return 1;}
 unsigned id=source<12163?6017+source-12153:source<12173?6037+source-12163:6027+source-12173;const MercenaryData180*d=contract?mercenary_data180(id):mercenary_data180(m->source);
 if(potion&&(m->frenzy180||(source==12184&&m->hp>=mercenary_maxhp180(m))||(source==12185&&m->sp>=mercenary_maxsp180(m))||(source==12242&&d->level<40)||(source==12243&&d->level<80)||(source>=12241&&source<=12243&&m->potionUntil>g->time&&m->potionRank>=source-12240))){combat_notice(g,POP_ITEMS,"That potion cannot help this mercenary now. Item kept.");return 1;}
 uint32_t uid=0;for(unsigned i=0;i<g->owned52.count[0];i++)if(g->owned52.items[i].sourceID==source&&g->owned52.items[i].quantity){uid=g->owned52.items[i].uid;break;}NpcState55*s=npc_game_character_state55(n);if(!uid||s->count>NPC_STATE_ENTRIES55-104||!npc_state_reserve55(s,s->count+104))return 1;
 if(owned_remove52(&g->owned52,0,uid,1)!=OWNED_OK52)return 1;
 if(contract){unsigned faith[3],calls[3];memcpy(faith,m->faith,sizeof(faith));memcpy(calls,m->calls,sizeof(calls));memset(m,0,sizeof(*m));memcpy(m->faith,faith,sizeof(faith));memcpy(m->calls,calls,sizeof(calls));m->source=id;m->hp=d->hp;m->sp=d->sp;m->remaining=1800000;unsigned guild=mercenary_guild180(id);if(m->calls[guild]<INT_MAX)m->calls[guild]++;mercenary_place180(g);g->utilityMenu=502;combat_notice(g,POP_SYSTEM,"%s hired for30minutes.",d->name);}
 else if(source==12184)m->hp=fminf(mercenary_maxhp180(m),m->hp+1000);else if(source==12185)m->sp=fminf(mercenary_maxsp180(m),m->sp+100);else{m->potionRank=source-12240;m->potionUntil=g->time+1800;}
 return npc_mercenary_store180(n)?1:0;
}
static int npc_mercenary_command180(NpcGame55*n,NpcRuntime55*r,NpcMachine55*vm,const char*name,const NpcValue55*args,unsigned count,NpcValue55*out){
 int get=!strcmp(name,"mercenary_get_faith"),set=!strcmp(name,"mercenary_set_faith");if(!get&&!set)return-1;int64_t guild,delta=0;if(!r->attached||count!=(set?2u:1u)||!npc_vm_integer55(vm,args[0],&guild)||guild<0||guild>2||(set&&!npc_vm_integer55(vm,args[1],&delta)))return N55_ERROR;Mercenary180*m=&n->player.game->mercenary180;
 if(set){unsigned before=m->faith[guild];int64_t value=delta>32767?32767:delta< -32767?0:(int64_t)before+delta;m->faith[guild]=value<0?0:value>32767?32767:(unsigned)value;if(!npc_mercenary_store180(n)){m->faith[guild]=before;return N55_ERROR;}}
 *out=npc_vm_number55(m->faith[guild]);return N55_READY;
}
