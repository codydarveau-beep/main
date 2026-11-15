/* SPDX-License-Identifier: MIT. Disjoint 16-bit skill/item shortcut identifiers. */
#ifndef MYRO_BINDINGS50_H
#define MYRO_BINDINGS50_H
#include <stdint.h>
#include "job_identity52.h"
typedef uint16_t SkillBinding50;
enum { BIND_ITEM_BASE50=4096, BIND_EMPTY50=65535, SKILL_CAP50=512 };
/* Historical Save48 bytes are translated only at the import boundary. */
static unsigned binding_from48(unsigned id){
 if(id==255)return BIND_EMPTY50;
 if(id<127)return id;
 if(id>=128&&id<128+115)return BIND_ITEM_BASE50+id-128;
 return BIND_EMPTY50+1u; /* Invalid values cannot silently become empty. */
}
#endif
