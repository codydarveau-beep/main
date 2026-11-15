/* MIT. User-facing session gesture and deferred damage regressions. */
#include <assert.h>
#include "combat.h"
#include "window_ui.h"
#include "developer.h"
#include "session_controls40.h"
int main(void){QuickHold q={0};for(int i=0;i<20;i++)assert(!quick_hold_hints(&q,32,.05f,1,0));assert(quick_hold_hints(&q,0,.01f,1,0)==1);for(int i=0;i<20;i++)assert(!quick_hold_hints(&q,512,.05f,1,1));assert(quick_hold_hints(&q,0,.01f,1,1)==2);unsigned events=0;for(int i=0;i<20;i++)events|=quick_hold_hints(&q,32,.05f,1,1);assert(events==4);assert(!quick_hold_hints(&q,0,.01f,1,1));events=0;for(int i=0;i<20;i++)events|=quick_hold_hints(&q,512,.05f,1,2);assert(events==8);assert(!quick_hold_hints(&q,0,.01f,1,2));quick_hold_hints(&q,32,.1f,0,3);assert(!quick_hold_hints(&q,32,1,1,3));assert(!quick_hold_hints(&q,0,.1f,1,3));
StartShortcut start={0};assert(!start_shortcut_tick(&start,1,.05f,1,1));assert(!start_shortcut_tick(&start,0,.05f,0,1));int count=0;for(int i=0;i<40;i++)count+=start_shortcut_tick(&start,1,.05f,i==0,1);assert(count==1&&start.fired);assert(!start_shortcut_tick(&start,0,.01f,0,1));for(int i=0;i<40;i++)assert(!start_shortcut_tick(&start,1,.05f,i==0,0));
Combat g;combat_init(&g,1500,1500,NULL,NULL);g.maxhp=g.hp=200;assert(g.hp==200);RangedTest t={0};ranged_test_arm(&t,&g);assert(!ranged_test_tick(&t,&g,10,0)&&g.hp==200);for(int i=0;i<19;i++)assert(!ranged_test_tick(&t,&g,.05f,1));assert(g.hp==200);assert(ranged_test_tick(&t,&g,.1f,1)&&g.hp==180);assert(!ranged_test_tick(&t,&g,5,1));ranged_test_arm(&t,&g);g.mapId++;assert(!ranged_test_tick(&t,&g,2,1)&&!t.active&&g.hp==180);ranged_test_arm(&t,&g);g.hp=0;assert(!ranged_test_tick(&t,&g,2,1)&&!t.active);
combat_tip(&g,"Sitting instructions");assert(g.logIsTip);combat_message(&g,"A real action response");assert(!g.logIsTip);puts("PASS40 quick taps/visible-hint-only holds and suppression, short/long START, deferred one-shot ranged damage/pause/travel/death guards, optional hint classification");}
