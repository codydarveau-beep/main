/* Global1.4 preferences; progression and character records remain separate. */
#ifndef MYRO_OPTIONS61_H
#define MYRO_OPTIONS61_H
/* Guardians always use the accepted sprite renderer. Old preference bits are ignored. */
static const unsigned guardianSprites162=1;
enum{DISPLAY_OFF60,DISPLAY_SMALL60,DISPLAY_LARGE60};
enum{FIRST_ITEMS60,FIRST_ENEMIES60};
enum{MAP_VIEW_DEFAULT180=0,SCENERY_VIEW_DEFAULT180=0,NPC_VIEW_DEFAULT180=0};
static unsigned mapView64=MAP_VIEW_DEFAULT180,npcView64=NPC_VIEW_DEFAULT180;
static unsigned sceneryView60=SCENERY_VIEW_DEFAULT180;
static unsigned minimapSize60=DISPLAY_SMALL60,compassSize60=DISPLAY_SMALL60;
static unsigned portalEffects60=1,basicFirst60=FIRST_ITEMS60,autoHerbs60;
static unsigned enemyVolume60=100,enemyMuted60,menuVolume60=35,sceneryEnabled61=1;
/* Developer observation only; deliberately resets off each session. */
static unsigned enemyHPTesting261;
static unsigned prefsView56=MONSTER_VIEW_DEFAULT53,prefsAttack56;
#endif
