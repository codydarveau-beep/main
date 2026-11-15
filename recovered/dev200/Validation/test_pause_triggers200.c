#include <assert.h>
#include <stdio.h>
#include "combat.h"
#include "pause_ui.h"
int main(void){PauseUI u={.tab=P53_GAME,.inside=1,.allowTesting58=1,.row=3};assert(pause_input(&u,32768)==PA_NONE&&u.tab==P53_GAMEPLAY&&!u.row&&u.inside);pause_input(&u,16384);assert(u.tab==P53_GAME);pause_input(&u,16384);assert(u.tab==P53_DIAGNOSTICS64);pause_input(&u,32|512);assert(u.tab==P53_DIAGNOSTICS64);pause_input(&u,16384|32768);assert(u.tab==P53_DIAGNOSTICS64);u.tab=P53_AUDIO;u.editing61=1;pause_input(&u,32768);assert(u.tab==P53_AUDIO&&u.editing61);u.editing61=0;u.detail=2;pause_input(&u,32768);assert(u.tab==P53_VIDEO&&!u.detail);u=(PauseUI){.frontOnly61=1,.tab=P53_MESSAGES};pause_input(&u,32768);assert(u.tab==P53_GAMEPLAY);puts("PASS LT/RT category shortcuts, wrap and inside focus, no Black/White navigation, simultaneous-trigger stability, edits protected and title-settings categories.");}
