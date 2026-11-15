/* Free previews; exactly500 Zeny for each confirmed, changed service. */
#ifndef MYRO_STYLIST58_H
#define MYRO_STYLIST58_H
#include "appearance_limits58.h"
#define STYLIST_FEE58 500
static unsigned stylist_max58(const Combat*g,unsigned service){if(service==0)return 41;if(service==1)return 8;unsigned actor=class_actor_id50(g->jobId,g->mounted48);return actor<49?clothMax58[actor]:0;}
static unsigned stylist_value58(Appearance58 a,unsigned service){return service==0?a.hair:service==1?a.colour:a.cloth;}
static void stylist_set58(Appearance58*a,unsigned service,unsigned value){if(!service)a->hair=value;else if(service==1)a->colour=value;else a->cloth=value;}
static int stylist_apply58(Combat*g,unsigned service,unsigned value){if(service>2||value>stylist_max58(g,service)||g->hp<=0)return 0;if(stylist_value58(g->appearance58,service)==value){combat_notice(g,POP_SYSTEM,"That is your current look. No charge.");return 0;}if(g->zeny<STYLIST_FEE58){combat_notice(g,POP_ITEMS,"Each service costs 500 Zeny. Nothing changed or spent.");return 0;}stylist_set58(&g->appearance58,service,value);g->zeny-=STYLIST_FEE58;combat_notice(g,POP_ITEMS,"Your new look is ready! 500 Zeny paid.");return 1;}
static int stylist_input58(CoreNpcUI53*u,Combat*g,unsigned p){if(!u->confirm){if(p&4){u->mode=-1;return 0;}if(p&(1024|2048))u->choice=(u->choice+((p&1024)?3:1))%4;if(p&2){if(u->choice==3){u->mode=-1;return 0;}if(!stylist_max58(g,u->choice)){combat_notice(g,POP_SYSTEM,"No alternate clothing palettes are available for this class yet.");return 0;}u->preview58=g->appearance58;u->confirm=1;}return 0;}
 if(p&4){u->confirm=0;u->preview58=g->appearance58;return 0;}if(p&(4096|8192)){unsigned max=stylist_max58(g,u->choice),value=stylist_value58(u->preview58,u->choice);value=(value+((p&4096)?max:1))%(max+1);stylist_set58(&u->preview58,u->choice,value);}if(p&2){int changed=stylist_apply58(g,u->choice,stylist_value58(u->preview58,u->choice));u->preview58=g->appearance58;u->confirm=0;return changed;}return 0;}
static Appearance58 stylist_preview58(const CoreNpcUI53*u,const Combat*g,int open){return open&&u->npc>=0&&u->npc<CORE_NPC_COUNT53&&coreNpcs53[u->npc].kind==10&&u->confirm?u->preview58:g->appearance58;}
#endif
