/* MIT. User-visible, stable preview indices and explicit effect names. */
#ifndef MYRO_ART_CATALOG40_H
#define MYRO_ART_CATALOG40_H
#define ART_PREVIEW_COUNT 28
static const char*artPreviewNames40[ART_PREVIEW_COUNT]={"Energy Coat cast","Cure","Freeze","Holy hit","Fire Wall","Fire hit","Wind hit","Thunder Storm small bolts","Stone Curse","Cart Revolution","Cart 1","Cart 2","Cart 3","Cart 4","Cart 5","Air: Fire Bolt","Air: Cold Bolt","Air: Lightning Bolt","Fire Ball flight","Casting aura","Spell target circle","Fire Pillar standing","Fire Pillar trigger","Storm Gust blizzard","Quagmire bubbles","Earth hit","Bowling Bash","Jupitel orb"};
static int art_air_clip40(int skill){return skill==3?15:skill==9?16:skill==21?17:-1;}
#endif
