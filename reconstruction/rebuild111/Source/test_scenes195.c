#define MYRO_HOST 1
#include <assert.h>
#include <stdio.h>
#include "campaign_scene200.h"
static int read_scene195(void*ctx,unsigned at,unsigned char*out,unsigned n){FILE*f=ctx;return !fseek(f,at,SEEK_SET)&&fread(out,1,n,f)==n;}
int main(int argc,char**argv){assert(argc==2);FILE*f=fopen(argv[1],"rb");assert(f);unsigned nodes=0;
 for(unsigned cursor=0;cursor<CAMPAIGN_PACKED_SCENES195;cursor++){
  unsigned raw=chapter1Index200[cursor].raw,packed=chapter1Index200[cursor].packed;unsigned char*p=malloc(packed),*out=malloc(raw);assert(p&&out&&read_scene195(f,chapter1Index200[cursor].offset,p,packed));assert(scene_inflate200(out,raw,p,packed));assert(crc32(0,out,raw)==chapter1Index200[cursor].crc&&scene_validate200(out,raw,cursor));unsigned count=scene_u16_200(out+6);nodes+=count;
  for(unsigned node=0;node<count;node++){unsigned char*n=out+16+node*32;unsigned old=npc_state_u32_55(n+28);npc_state_put32_55(n+28,6);assert(!scene_validate200(out,raw,cursor));npc_state_put32_55(n+28,0x5100);assert(!scene_validate200(out,raw,cursor));npc_state_put32_55(n+28,old);}
  for(unsigned role=1;role<=3;role++){
   NpcState55 state={0};Campaign200 c={.cursor=cursor,.route=role,.lineage=role,.recruits=0};assert(campaign_store200(&state,&c));Scene200 scene={.state=&state,.data=out,.bytes=raw,.count=count,.pool=16+count*32,.cursor=cursor};
   for(unsigned node=0;node<count;node++){assert(campaign_checkpoint200(&state,cursor,node));unsigned word=npc_state_u32_55(out+16+node*32+28);assert(scene_expression200(&scene)==(word&255u));assert(scene_emotion195(&scene)==(word>>8));}
   Scene200 opened={0};assert(campaign_checkpoint200(&state,cursor,0));int ok=scene_open200(&opened,&state,read_scene195,f);assert(ok==(cursor<CAMPAIGN_RELEASE_SCENES193));if(ok){assert(scene_expression200(&opened)==(npc_state_u32_55(out+44)&255u));scene_close200(&opened);}npc_state_clear55(&state);
  }
  free(out);free(p);
 }
 fclose(f);printf("PASS released scene wire, %u node cue/checkpoint reads across three roles, corruption rejection and retained activation ceiling. No world/playthrough claim.\n",nodes);return 0;}
