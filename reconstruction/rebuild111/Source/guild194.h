/* MIT. Reconstructed guild state using recovered released RGH1 wire layout.
 * Native quest variables and released project costs/rewards remain independent. */
#ifndef MYRO_GUILD194_H
#define MYRO_GUILD194_H
#include "campaign_state200.h"
#include "guild_data194.h"
#define GUILD_KEY194 UINT64_C(0xeca20000f219bc70)
#define GUILD_PROJECTS194 12u
typedef struct{unsigned accepted,completed,style,scores[6];}Guild194;
static int guild_valid194(const Guild194*g){return g&&g->accepted<4096&&g->completed<4096&&!(g->completed&~g->accepted)&&g->style<4;}
static int guild_load194(const NpcState55*s,Guild194*out){
 if(!s||!out)return-1;Guild194 g={0};const NpcVariable55*v=npc_state_get55(s,GUILD_KEY194,0);
 if(!v){*out=g;return 0;}if(v->kind!=NPC_STATE_STRING_KIND55||v->length!=112)return-1;
 unsigned char wire[56];
 for(unsigned i=0;i<56;i++){
  unsigned value=0;for(unsigned j=0;j<2;j++){unsigned x=(unsigned char)v->text[i*2+j];if(x>='0'&&x<='9')x-='0';else if(x>='a'&&x<='f')x=x-'a'+10;else return-1;value=(value<<4)|x;}wire[i]=(unsigned char)value;
 }
 if(memcmp(wire,"RGH1",4)||npc_state_u32_55(wire+52)!=crc32(0,wire,52))return-1;
 for(unsigned i=40;i<52;i++)if(wire[i])return-1;
 g.accepted=npc_state_u32_55(wire+4);g.completed=npc_state_u32_55(wire+8);g.style=npc_state_u32_55(wire+12);
 for(unsigned i=0;i<6;i++)g.scores[i]=npc_state_u32_55(wire+16+i*4);
 if(!guild_valid194(&g))return-1;*out=g;return 1;
}
static int guild_store194(NpcState55*s,const Guild194*g){
 if(!s||!guild_valid194(g))return 0;unsigned char wire[56]={0};memcpy(wire,"RGH1",4);
 npc_state_put32_55(wire+4,g->accepted);npc_state_put32_55(wire+8,g->completed);npc_state_put32_55(wire+12,g->style);
 for(unsigned i=0;i<6;i++)npc_state_put32_55(wire+16+i*4,g->scores[i]);npc_state_put32_55(wire+52,crc32(0,wire,52));
 char text[113];static const char hex[]="0123456789abcdef";
 for(unsigned i=0;i<56;i++){text[i*2]=hex[wire[i]>>4];text[i*2+1]=hex[wire[i]&15];}text[112]=0;
 return npc_state_set_text55(s,GUILD_KEY194,0,text,112);
}
static int guild_open194(const NpcState55*s){Campaign200 c;Guild194 g;return campaign_load200(s,&c)==1&&c.cursor>=9&&*c.guild&&guild_load194(s,&g)>=0;}
static int guild_near194(const Combat*g){return g&&g->hp>0&&((g->mapId==132&&combat_dist(g->x,g->y,188,1116)<=28)||(g->mapId==494&&combat_dist(g->x,g->y,800,1440)<=28));}
static int guild_project_available194(const NpcState55*s,unsigned index){
 Campaign200 c;Guild194 g;if(index>=GUILD_PROJECTS194||!guild_open194(s)||campaign_load200(s,&c)!=1||guild_load194(s,&g)<0)return 0;
 const GuildProject194*p=guildProjects194+index;return c.cursor>=p->minimum&&(g.completed&p->requires)==p->requires;
}
static int guild_accept194(NpcState55*s,unsigned index){
 Guild194 g;if(!guild_project_available194(s,index)||guild_load194(s,&g)<0)return 0;
 unsigned bit=1u<<index;if(g.accepted&bit)return 1;g.accepted|=bit;return guild_store194(s,&g);
}
static unsigned guild_material_count194(const Combat*g,unsigned source){
 unsigned n=0;for(unsigned i=0;i<g->owned52.count[0];i++){const OwnedItem52*p=g->owned52.items+i;if(p->sourceID==source&&!p->equipped&&!p->bound)n+=p->quantity;}return n;
}
static int guild_deliver194(NpcState55*s,Combat*game,unsigned index){
 Guild194 g;if(!game||!guild_project_available194(s,index)||guild_load194(s,&g)<0)return 0;
 unsigned bit=1u<<index;if(!(g.accepted&bit)||(g.completed&bit))return 0;
 OwnedItems52*bag=malloc(sizeof(*bag));if(!bag)return 0;*bag=game->owned52;
 const GuildProject194*p=guildProjects194+index;
 for(unsigned k=0;k<2;k++){
  unsigned left=p->amount[k];for(unsigned i=0;i<bag->count[0]&&left;){OwnedItem52*o=bag->items+i;
   if(o->sourceID!=p->item[k]||o->equipped||o->bound){i++;continue;}
   unsigned amount=o->quantity<left?o->quantity:left,uid=o->uid;int erased=amount==o->quantity;
   if(owned_remove52(bag,0,uid,amount)!=OWNED_OK52){free(bag);return 0;}left-=amount;if(!erased)i++;
  }if(left){free(bag);return 0;}
 }
 g.completed|=bit;if(!guild_store194(s,&g)){free(bag);return 0;}game->owned52=*bag;free(bag);return 1;
}
static int guild_style194(NpcState55*s,unsigned style){
 Guild194 g;if(style>3||guild_load194(s,&g)<0||!(g.completed&2)||(style==2&&!(g.completed&8))||(style==3&&!(g.completed&4)))return 0;
 g.style=style;return guild_store194(s,&g);
}
static int guild_score194(NpcState55*s,unsigned cabinet,unsigned score){
 Guild194 g;if(cabinet>=6||guild_load194(s,&g)<0||!(g.completed&(1u<<(cabinet+6))))return 0;
 if(score<=g.scores[cabinet])return 1;g.scores[cabinet]=score;return guild_store194(s,&g);
}
#endif
