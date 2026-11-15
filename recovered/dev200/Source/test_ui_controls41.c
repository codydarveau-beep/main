/* MIT. Actual UI navigation, menu action, and text-free cast bar contracts. */
#include <assert.h>
#include "combat.h"
#include "window_ui.h"
#include "pause_ui.h"
#include "cast_indicator.h"
#include "developer.h"
int main(void){Combat g;WindowUI u;int cases=0;combat_init(&g,1500,1500,NULL,NULL);
 for(int job=0;job<=6;job++){if(job)dev_class_preset(&g,job);for(int w=0;w<4;w++)for(int page=0;page<(w==UI_SKILLS?2:1);page++){memset(&u,0,sizeof(u));ui_open(&u,w,1);u.skillPage=page;int n=w==UI_SKILLS&&page?(int)class_count(&g):ui_count(w);if(!n)continue;u.choice[w]=-1;ui_input(&u,&g,1024);assert(u.choice[w]==n-1);if(w==UI_ITEMS)assert(u.itemScroll==(ITEM_COUNT+3)/4-3);ui_input(&u,&g,2048);assert(u.choice[w]==-1);ui_input(&u,&g,2048);assert(u.choice[w]==0);ui_input(&u,&g,1024);assert(u.choice[w]==-1);cases++;}}
 PauseUI p={0};p.row=3;assert(pause_input(&p,2)==PA_NONE&&p.tab==3);p.row=1;assert(pause_input(&p,2)==PA_TOOLTIPS);p.tab=0;p.row=4;assert(pause_input(&p,2)==PA_RESUME);p.row=0;pause_input(&p,1024);assert(p.row==4);pause_input(&p,2048);assert(!p.row);pause_input(&p,512);assert(p.tab==1&&pause_count(1)==4);pause_input(&p,512);assert(p.tab==2&&pause_count(2)==2);pause_input(&p,512);assert(p.tab==3&&pause_count(3)==12);pause_input(&p,512);assert(p.tab==0&&pause_count(0)==5);for(int i=2;i<9;i++){p.tab=3;p.row=i;assert(pause_input(&p,2)==PA_POP_DAMAGE+i-2);}p.row=0;pause_input(&p,1024);assert(p.row==11);pause_input(&p,2048);assert(p.row==0);
 CastIndicator b;assert(!cast_indicator(&g,320,210,&b));g.spellCastTotal=5;g.spellCastLeft=5;assert(cast_indicator(&g,320,210,&b)&&b.x==296&&b.y==200&&b.fill==0);g.spellCastLeft=2.5f;assert(cast_indicator(&g,320,210,&b)&&b.fill==23);g.spellCastLeft=.01f;assert(cast_indicator(&g,320,210,&b)&&b.fill==45);g.spellCastLeft=0;assert(!cast_indicator(&g,320,210,&b));g.spellCastLeft=1;assert(cast_indicator(&g,-100,-100,&b)&&b.x==2&&b.y==2);assert(cast_indicator(&g,1000,1000,&b)&&b.x==590&&b.y==472);assert(!cast_indicator(&g,NAN,210,&b));
 printf("PASS38 %d window/job/page close-button up/down wraps, pause tooltip action and six-pixel cast indicator progress/hide/clamps\n",cases);
}
