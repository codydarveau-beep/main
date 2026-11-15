/* Original impact element rules; physical hits remain neutral. */
#ifndef MYRO_COMPANION_ELEMENT204_H
#define MYRO_COMPANION_ELEMENT204_H
static unsigned party_impact_element204(unsigned skill,unsigned magic){if(!magic)return 0;switch(skill){case 3:case 352:return 3;case 9:case 355:return 1;case 21:case 358:return 4;case 438:case 439:case 440:return 0;default:return 6;}}
#endif
