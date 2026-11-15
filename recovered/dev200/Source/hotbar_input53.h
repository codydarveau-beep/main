/* MIT. Selection is independent of persistent basic-attack intent. */
#ifndef MYRO_HOTBAR_INPUT53_H
#define MYRO_HOTBAR_INPUT53_H
static int hotbar_input53(Combat*g,unsigned pressed){if(!(pressed&(1024|2048|4096|8192)))return 0;if(pressed&4096)skill_slot(g,-1,0);else if(pressed&8192)skill_slot(g,1,0);else skill_slot(g,0,1);return 1;}
#endif
