/* MIT. Original-script IDs are distinct from internal class/skill indexes. */
#ifndef MYRO_NPC_IDENTITY55_H
#define MYRO_NPC_IDENTITY55_H
#include "npc_class_ids55.h"
static int npc_native_job55(unsigned source){for(unsigned i=0;i<J52_COUNT;i++)if(job_source52(i)==source)return(int)i;return-1;}
static unsigned npc_eaclass55(unsigned native){return native<J52_COUNT?npcClassIds55[native]:~0u;}
static unsigned npc_base_job55(unsigned native,unsigned sex){if(native>=J52_COUNT)return~0u;unsigned base=npcClassIds55[native]&0x0fffu;if(base==515)return sex?19:20;for(unsigned i=0;i<J52_COUNT;i++)if(npcClassIds55[i]==base)return job_source52(i);return~0u;}
static unsigned npc_base_class55(unsigned native){if(native>=J52_COUNT)return~0u;unsigned base=npcClassIds55[native]&0x00ffu;for(unsigned i=0;i<J52_COUNT;i++)if(npcClassIds55[i]==base)return job_source52(i);return~0u;}
static int npc_native_skill55(unsigned source){if(source==143)return 339;if(source==1)return 338;for(unsigned i=0;i<sizeof(itemSkillMap52)/sizeof(*itemSkillMap52);i++)if(itemSkillMap52[i][0]==source)return itemSkillMap52[i][1];return-1;}
static unsigned npc_source_skill55(unsigned native){if(native==339)return 143;if(native==338)return 1;return native<sizeof(itemNativeSources52)/sizeof(*itemNativeSources52)?itemNativeSources52[native]:0;}
#endif
