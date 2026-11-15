#include "companion_experience200.h"
void companion_gain200(unsigned char*raw,unsigned id,int base,int job,unsigned beRate,unsigned jeRate){PartyGrowth200 m;party_growth_read200(raw+16+id*32,&m);if(!party_growth_gain200(&m,id,base,job,beRate,jeRate)||!party_progress_put200(raw,id,&m))abort();npc_state_put32_55(raw+636,crc32(0,raw,636));}
