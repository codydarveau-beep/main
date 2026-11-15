/* MIT. Optional per-character guild improvements; main story never charges these. */
#ifndef MYRO_GUILD194_H
#define MYRO_GUILD194_H
#include "campaign_state200.h"

#define GUILD_KEY194 UINT64_C(0xeca20000f219bc70)
#define GUILD_QUEST194 2000000100u
#define GUILD_PROJECTS194 12u

typedef struct{
 unsigned accepted,built,decor,highscore[6];
}Guild194;

typedef struct{
 const char*name,*pitch;
 unsigned chapter,requires,item[2],amount[2];
}GuildProject194;

static const GuildProject194 guildProjects194[12]={
 {
  "A roof over every head",
  "Maya: A dry ledger is a useful ledger. A dry adventurer is a pleasant surprise. Bring lumber and cloth; we will repair the roof and door.",
  9,0,{1019,914},{40,10}
 },
 {
  "A table with room for one more",
  "Yuufa: We have beds. Now we need somewhere people can sit without being asked why they are here.",
  12,1,{1019,998},{30,10}
 },
 {
  "Dagna's second chance",
  "Dagna: This bench makes hinges, not restraints. You may remind me of that whenever necessary.",
  18,3,{999,1003},{20,10}
 },
 {
  "Copies nobody can burn",
  "Nera: One copy is a secret. Several copies, in several hands, are a record.",
  18,3,{914,991},{20,10}
 },
 {
  "A door held wider",
  "Brann: The next room is empty. The landlord calls it storage. I think we can improve that description.",
  24,15,{1019,999},{80,20}
 },
 {
  "The extremely important recreation annex",
  "Maya: Rest is productive. I have written it in the accounts, so it must be true. Help Pip wire the cabinets.",
  15,3,{1019,938},{25,15}
 },
 {
  "Poring Pong",
  "Pip: The Poring volunteered to be a ball. The paddle remains unconvinced. Build our first cabinet.",
  15,35,{1019,909},{10,5}
 },
 {
  "Peco Patrol",
  "Corin: This one shoots at painted monsters. I recommend it over several of my previous employers.",
  18,39,{998,1003},{10,5}
 },
 {
  "Herb Trail",
  "Yuufa: You eat herbs, get longer, and must not bite yourself. I am assured this is medicinal research.",
  15,35,{511,938},{10,5}
 },
 {
  "Pupa Breaker",
  "Dagna: An excellent demonstration of applied force. Please use the cabinet, not the guild's actual walls.",
  18,39,{999,909},{5,10}
 },
 {
  "Kafra's Lost Parcels",
  "Nera: Sixteen parcels. Fifteen spaces. A familiar workplace situation, regrettably.",
  18,43,{1019,914},{10,10}
 },
 {
  "Moonlight Munch",
  "Miri: The ghosts agreed to chase a Poring for an afternoon. Nobody is bound here; the dots are biscuits.",
  24,47,{991,938},{10,10}
 }
};

static int guild_load194(const NpcState55*s,Guild194*out){
 if(!s||!out)return-1;

 const NpcVariable55*v=npc_state_get55(s,GUILD_KEY194,0);
 memset(out,0,sizeof(*out));

 if(!v)return 0;
 if(v->kind!=NPC_STATE_STRING_KIND55||v->length!=112)return-1;

 unsigned char b[56];

 for(unsigned i=0;i<56;i++){
  unsigned n=0;

  for(unsigned j=0;j<2;j++){
   unsigned c=(unsigned char)v->text[i*2+j];

   if(c>='0'&&c<='9')c-='0';
   else if(c>='a'&&c<='f')c=c-'a'+10;
   else return-1;

   n=n*16+c;
  }

  b[i]=(unsigned char)n;
 }

 if(memcmp(b,"RGH1",4)||
    npc_state_u32_55(b+52)!=crc32(0,b,52))
  return-1;

 out->accepted=npc_state_u32_55(b+4);
 out->built=npc_state_u32_55(b+8);
 out->decor=npc_state_u32_55(b+12);

 if(out->accepted>=4096||
    out->built>=4096||
    (out->built&~out->accepted)||
    out->decor>3)
  return-1;

 for(unsigned i=0;i<6;i++)
  out->highscore[i]=npc_state_u32_55(b+16+i*4);

 for(unsigned i=40;i<52;i++)
  if(b[i])return-1;

 return 1;
}

static int guild_store194(NpcState55*s,const Guild194*g){
 if(!s||
    g->accepted>=4096||
    g->built>=4096||
    (g->built&~g->accepted)||
    g->decor>3)
  return 0;

 unsigned char b[56]={0};

 memcpy(b,"RGH1",4);
 npc_state_put32_55(b+4,g->accepted);
 npc_state_put32_55(b+8,g->built);
 npc_state_put32_55(b+12,g->decor);

 for(unsigned i=0;i<6;i++)
  npc_state_put32_55(b+16+i*4,g->highscore[i]);

 npc_state_put32_55(b+52,crc32(0,b,52));

 char text[113];
 const char*h="0123456789abcdef";

 for(unsigned i=0;i<56;i++){
  text[2*i]=h[b[i]>>4];
  text[2*i+1]=h[b[i]&15];
 }

 text[112]=0;

 return npc_state_set_text55(s,GUILD_KEY194,0,text,112);
}

static int guild_open194(const NpcState55*s){
 Campaign200 c;
 return campaign_load200(s,&c)==1&&c.cursor>=9&&*c.guild;
}

static int guild_available194(const NpcState55*s,unsigned project){
 if(project>=12)return 0;

 Campaign200 c;
 Guild194 g;
 const GuildProject194*p=guildProjects194+project;

 return guild_open194(s)&&
        campaign_load200(s,&c)==1&&
        guild_load194(s,&g)>=0&&
        c.cursor>=p->chapter&&
        (g.built&p->requires)==p->requires;
}

static int guild_accept194(NpcState55*s,unsigned project){
 Guild194 g;

 if(!guild_available194(s,project)||guild_load194(s,&g)<0)
  return 0;

 g.accepted|=1u<<project;
 return guild_store194(s,&g);
}

/* Preflight a disposable inventory before committing the small guild record.
 * Both become part of the same ordinary save bundle; no yield between them. */
static int guild_build194(
 NpcState55*s,Combat*player,unsigned project
){
 Guild194 g;

 if(!guild_available194(s,project)||
    guild_load194(s,&g)<0||
    !(g.accepted&(1u<<project))||
    (g.built&(1u<<project)))
  return 0;

 const GuildProject194*p=guildProjects194+project;

 OwnedItems52*bag=malloc(sizeof(*bag));
 if(!bag)return 0;
 *bag=player->owned52;

 for(unsigned k=0;k<2;k++){
  unsigned left=p->amount[k];

  for(unsigned i=0;i<bag->count[0]&&left;){
   OwnedItem52*o=bag->items+i;

   if(o->sourceID!=p->item[k]||o->equipped){
    i++;
    continue;
   }

   unsigned amount=o->quantity<left?o->quantity:left;
   unsigned uid=o->uid;
   int erased=amount==o->quantity;

   if(owned_remove52(bag,0,uid,amount)!=OWNED_OK52){
    free(bag);
    return 0;
   }

   left-=amount;
   if(!erased)i++;
  }

  if(left){
   free(bag);
   return 0;
  }
 }

 g.built|=1u<<project;

 if(!guild_store194(s,&g)){
  free(bag);
  return 0;
 }

 player->owned52=*bag;
 free(bag);
 return 1;
}

static int guild_score194(
 NpcState55*s,unsigned game,unsigned score
){
 Guild194 g;

 if(game>=6||
    guild_load194(s,&g)<0||
    !(g.built&(1u<<(6+game))))
  return 0;

 if(score<=g.highscore[game])return 1;

 g.highscore[game]=score;
 return guild_store194(s,&g);
}

static int guild_decor194(NpcState55*s,unsigned decor){
 Guild194 g;

 if(decor>3||
    guild_load194(s,&g)<0||
    !(g.built&2)||
    (decor==2&&!(g.built&8))||
    (decor==3&&!(g.built&4)))
  return 0;

 g.decor=decor;
 return guild_store194(s,&g);
}

/* Declining an introduction never permanently deletes a recruit.
 * Future cast remains hidden. */
static unsigned guild_met_mask194(unsigned cursor){
 static const unsigned char after[19]={
  8,2,8,15,2,14,11,13,5,13,13,16,5,8,18,16,13,23,23
 };

 unsigned mask=0;

 for(unsigned id=0;id<19;id++)
  if(cursor>after[id])mask|=1u<<id;

 return mask;
}

static int guild_invite194(NpcState55*s,unsigned id){
 Campaign200 c;

 if(id>=19||
    !guild_open194(s)||
    campaign_load200(s,&c)!=1||
    !(guild_met_mask194(c.cursor)&(1u<<id)))
  return 0;

 if(c.recruits&(1u<<id))return 1;

 c.recruits|=1u<<id;
 return campaign_store200(s,&c);
}
#endif
