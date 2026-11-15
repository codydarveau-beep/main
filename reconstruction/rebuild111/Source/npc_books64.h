#ifndef MYRO_NPC_BOOKS64_H
#define MYRO_NPC_BOOKS64_H
#include "npc_books_data64.h"
typedef struct{int slot;unsigned book,scroll;}NpcBookView64;
static int npc_book_index64(unsigned id){for(unsigned i=0;i<sizeof(npcBooks64)/sizeof(*npcBooks64);i++)if(npcBooks64[i].id==id)return(int)i;return-1;}
#endif
