/* MIT. Existing cross-runtime pins protect live VM/call stacks while trimming
 * inactive cached scripts. The2MiB maximum still permits large quest programs. */
static unsigned npcTrimAt183;
static void npc_cache_frame183(NpcGame55*g,unsigned now){npc_disc_frame183(&g->disc,now);if((unsigned)(now-npcTrimAt183)<5000)return;npcTrimAt183=now;MM_STATISTICS m={0};m.Length=sizeof(m);MmQueryStatistics(&m);if(m.AvailablePages<2048)npc_program_trim171(&g->programs,NULL,512u*1024u);}
