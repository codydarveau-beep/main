/* MIT. Pure admission hooks. Install before opening a character session. */
#ifndef MYRO_TRAVEL_ADMISSION194_H
#define MYRO_TRAVEL_ADMISSION194_H
static const char*(*npcTravelAdmission194)(Combat*,unsigned);
static const char*(*combatTravelAdmission194)(Combat*,unsigned);
static const char*(*npcNativeAdmission194)(unsigned);
static void(*npcTravelRedirect193)(Combat*,unsigned*,float*,float*);
#endif
