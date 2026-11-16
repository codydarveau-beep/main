/* MIT. Cached native NPC chronology/dependency checks. No allocations, script
 * execution or inventory changes. Initialization remains a separate lifecycle. */
#ifndef MYRO_NATIVE_ADMISSION194_H
#define MYRO_NATIVE_ADMISSION194_H
#include "campaign_access194.h"
#include "npc_registry_data55.h"
#include "npc_access_data194.h"
#include "story_departure193.h"

typedef struct{
 const NpcState55*state;
 unsigned revision,valid,sandbox,opening;
 unsigned char map[CAMPAIGN_ACCESS_MAPS194];
}NativeAdmissionCache194;

typedef char NativeAdmissionProgramCount194[
 NPC_ACCESS_PROGRAMS194==NPC_PROGRAM_COUNT55?1:-1
];

static void native_admission_refresh194(
 NativeAdmissionCache194*c,const NpcState55*s,int sandbox
){
 memset(c,0,sizeof(*c));
 c->state=s;
 c->revision=s?s->revision:0;
 c->valid=1;
 c->sandbox=!!sandbox;

 Campaign200 story;
 unsigned regions=0;

 int readable=
  campaign_load200(s,&story)==1&&
  campaign_regions_read194(s,&regions);

 c->opening=
  readable&&!story.cursor&&!story.checkpoint&&!story.route;

 for(unsigned map=0;map<CAMPAIGN_ACCESS_MAPS194;map++)
  c->map[map]=(unsigned char)(
   sandbox?campaign_access_decide194(NULL,0,map,1):
   !readable?ACCESS_RECORD194:
   campaign_access_decide194(&story,regions,map,0)
  );

 if(!sandbox&&readable&&story.cursor>=1&&career_pilgrimage194(s))
  c->map[108]=ACCESS_OPEN194;
}

static const char*native_admission_reason194(
 const NativeAdmissionCache194*c,unsigned npc
){
 if(!c||!c->valid||npc>=NPC_RECORD_COUNT55)
  return "This character's travel record is unavailable.";

 const NpcRecord55*n=npcRecords55+npc;

 if(n->map<CAMPAIGN_ACCESS_MAPS194&&c->map[n->map])
  return campaign_access_message194(c->map[n->map]);

 unsigned program=n->program;

 if(!program)return NULL;

 if(program>NPC_ACCESS_PROGRAMS194)
  return "This NPC's travel service is unavailable.";

 /* These menus preflight the selected route before fees/savepoints.
    Checking all possible cities would disable the entire service. */
 /* Hanson has multiple career recommendation destinations. During the
    opening every graduation route resolves to the campaign opening;
    unrelated later career dependencies must not hide the exit NPC. */
 if(c->opening&&program==3875)return NULL;

 if(program==696||program==3604||program==3866)
  return NULL;

 for(unsigned i=npcAccessOffsets194[program-1];
     i<npcAccessOffsets194[program];i++){

  unsigned map=npcAccessMaps194[i];

  if(map>=CAMPAIGN_ACCESS_MAPS194)
   return "This NPC's destination is unavailable.";

  if(c->opening&&story_departure_maps193(n->map,map))
   map=0;

  if(c->map[map])
   return campaign_access_message194(c->map[map]);
 }

 return NULL;
}
#endif
