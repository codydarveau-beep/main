/* MIT. Story companions replace the original contract-hireling player feature.
 * Keep reusable movement/combat code, but expose no legacy hiring service. */
#ifndef MYRO_HIRED_HELPERS191_H
#define MYRO_HIRED_HELPERS191_H
#include <string.h>
#define MERCENARY_HIRING_ENABLED191 0
static int mercenary_npc_disabled191(const char*name){return !MERCENARY_HIRING_ENABLED191&&name&&(!strncmp(name,"Mercenary Manager",17)||!strncmp(name,"Mercenary Merchant",18));}
#endif
