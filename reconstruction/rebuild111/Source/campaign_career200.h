/* MIT. Native career proof and advancement family; no job/level grants. */
#ifndef MYRO_CAMPAIGN_CAREER200_H
#define MYRO_CAMPAIGN_CAREER200_H
#include "campaign_state200.h"
#include "job_identity52.h"
/* Retain first-career identity through normal promotion and rebirth. */
static unsigned campaign_career_root200(unsigned job){if(!job_valid52(job)||job==0||job==J52_HIGH_NOVICE)return 0;if(job==J52_SUPER_NOVICE)return J52_SUPER_NOVICE;job=job_parent52(job);if(job>=1&&job<=6)return job;switch(job){case 7:case 11:return 1;case 8:case 9:case 10:return 2;case 17:case 18:return 3;case 12:case 13:return 4;case 14:case 15:case 16:return 5;case 19:case 20:return 6;case J60_STAR_GLADIATOR:case J60_SOUL_LINKER:return J60_TAEKWON;default:return job;}}
static unsigned campaign_recommended_role200(unsigned root){switch(root){case 1:case 4:case J60_TAEKWON:return C200_VANGUARD;case 2:case 5:case J60_NINJA:case J60_GUNSLINGER:return C200_PATHFINDER;case 3:case 6:return C200_KEEPER;default:return C200_UNCHOSEN;}}
#define CAMPAIGN_SUPER_INTENT200 (1u<<31)
/* Explicit intent is a story exemption, never an early Super Novice job grant. */
static int campaign_super_intent200(NpcState55*s,unsigned actualJob){Campaign200 c;if(actualJob!=0||campaign_load200(s,&c)!=1||c.cursor!=1||c.route)return 0;c.objectives|=CAMPAIGN_SUPER_INTENT200|1u;return campaign_store200(s,&c);}
/* Inspect the actual native job or the explicitly accepted Novice exception. */
static unsigned campaign_verified_career200(const NpcState55*s,unsigned job){Campaign200 c;unsigned root=campaign_career_root200(job);if(campaign_load200(s,&c)!=1||c.cursor!=1)return 0;if(job==0&&(c.objectives&CAMPAIGN_SUPER_INTENT200))root=J52_SUPER_NOVICE;if(!root)return 0;if(c.lineage&&c.lineage!=root)return 0;return root;}
static int campaign_job_proof200(NpcState55*s,unsigned job){Campaign200 c;if(!campaign_verified_career200(s,job)||campaign_load200(s,&c)!=1)return 0;if(c.objectives&1)return 1;return campaign_objective200(s,1,0);}
/* Pure predicate for the later normal-play change guard. Developer changes use
 * their existing separate path. Do not reject a paid quest halfway through it:
 * its entry must first display the permanent-family warning. */
static int campaign_career_allows200(unsigned committed,unsigned job){if(!committed)return 1;if(committed==J52_SUPER_NOVICE&&job==0)return 1;if(job==J52_HIGH_NOVICE)return committed>=1&&committed<=6;return campaign_career_root200(job)==committed;}
#endif
