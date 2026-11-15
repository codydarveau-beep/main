/* GPL-3.0-or-later. roBrowserLegacy2dc0d153 LockOnTarget.js/.vs/.fs. */
static float lockon_width49(float age){float t=age/.05f;if(t<1)t=1;if(t>5)t=5;return (6-t)*24;}
static unsigned lockon_pulse49(float age){if(age<0)age=0;return 20-((unsigned)floorf(age/.02f)%20);}
static int lockon_target49(const Combat*g){if(!combat_casting(g)||g->spellCastTarget<0||g->spellCastTarget>=MOB_COUNT)return -1;const CombatMob*t=&g->mobs[g->spellCastTarget];return t->enabled&&t->hp>0&&t->life==g->spellCastLife?g->spellCastTarget:-1;}
