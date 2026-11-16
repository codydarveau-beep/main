#define CAMPAIGN_LIVE_COMPANIONS226 1
#define CAMPAIGN_REAL_COMBAT232 1
#define CAMPAIGN_SEQUENCE_ROLES232 1
#define CAMPAIGN_SEQUENCE_REPLIES232 1
#define CAMPAIGN_SEQUENCE_LIMITATIONS240 "Host recorder with qualified stats and player HP/SP topups; actual authored enemy combat/death hooks execute. Native job prerequisites remain fixtures; not balance or target acceptance."
#define CAMPAIGN_SEQUENCE_ENTRY226 candidate_combat_sequences232
#include "test_campaign_sequence200.c"
int main(void){candidate_combat_sequences232();assert(encounterKills232&&chapterRewards226==36);printf("PASS actual authored scene combat/death integration: %u deaths, %u real combat ticks. Explicit qualified host fixture with explicit HP/SP topups; no balance, original Xbox or Xemu claim.\n",encounterKills232,encounterTicks232);return 0;}
