/* Original static restrictions for job-exam rooms; NPC script warps bypass these player-action checks. */
#ifndef MYRO_JOB_MAP_FLAGS55_H
#define MYRO_JOB_MAP_FLAGS55_H
static int job_noteleport55(unsigned map){switch(map){case 65u:case 101u:case 107u:case 426u:case 427u:case 428u:case 429u:case 430u:case 431u:case 432u:case 433u:case 434u:case 435u:case 481u:case 482u:case 483u:case 484u:case 485u:case 486u:case 487u:case 488u:return 1;default:return 0;}}
static int job_noskill55(unsigned map){return map==482;}
static int job_nowarp55(unsigned map){(void)map;return 0;}
static int job_noreturn55(unsigned map){(void)map;return 0;}
#endif
