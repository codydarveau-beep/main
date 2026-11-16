#define CAMPAIGN_LIVE_COMPANIONS226 1
#define CAMPAIGN_SEQUENCE_LIMITATIONS240 "Host recorder with live independent companion growth/rewards. Native job completion and scene-specific enemy deaths remain fixtures; not target acceptance."
#define CAMPAIGN_SEQUENCE_ENTRY226 candidate_scene_sequences226
#include "test_campaign_sequence200.c"
int main(void){candidate_scene_sequences226();assert(recruitSeen226==((1u<<19)-1));assert(combatSeen226==recruitSeen226);assert(combatKills226&&chapterRewards226==216);printf("PASS actual chapter companion bridge: all recruited characters use durable independent growth; %u real AI kills and %u chapter reward/idempotency checks. Original scene-proof fixtures and host raster boundaries remain.\n",combatKills226,chapterRewards226);return 0;}
