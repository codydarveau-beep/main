/* MIT. Authored roster identities. Unprepared careers do not borrow wrong art. */
#ifndef MYRO_CAMPAIGN_COMPANIONS200_H
#define MYRO_CAMPAIGN_COMPANIONS200_H
#include "job_identity52.h"
enum{COMP200_BRANN,COMP200_ROAN,COMP200_TAKIUS,COMP200_EDDA,COMP200_YUUFA,COMP200_SURI,COMP200_IRUGA,COMP200_KEST,COMP200_JUDIA,COMP200_OREN,COMP200_LALE,COMP200_DAGNA,COMP200_MAYA,COMP200_PIP,COMP200_KAEDE,COMP200_CORIN,COMP200_DARO,COMP200_HANEUL,COMP200_MIRI};
typedef struct{const char*name;unsigned career,sceneActor;}CampaignCompanion200;
static const CampaignCompanion200 campaignCompanions200[19]={
 {"Brann",7,255},{"Roan",11,1},{"Takius",9,255},{"Edda",10,255},
 {"Yuufa",17,2},{"Suri",18,255},{"Iruga",12,255},{"Kest",13,255},
 {"Judia",14,255},{"Oren",15,255},{"Lale",16,255},{"Dagna",19,255},
 {"Maya",20,255},{"Pip",J52_SUPER_NOVICE,255},{"Kaede",J60_NINJA,255},
 {"Corin",J60_GUNSLINGER,255},{"Daro",J60_TAEKWON,255},
 {"Haneul",J60_STAR_GLADIATOR,255},{"Miri",J60_SOUL_LINKER,255}};
#endif
