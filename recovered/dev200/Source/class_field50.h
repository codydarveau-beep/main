#include "class_field52.h"
/* GPL-3.0-or-later. Original EF253/328 cylinders, timed independently of hits. */
static void class_field_draw50(const Combat*g,const Art39State*s,const float*m){
 trans_field52(g,m);
 for(int i=0;i<ART39_EVENTS;i++){const Art39Event*e=&s->events[i];float age=g->time-e->at;
  if(e->skill==SK52_CH_TIGERFIST&&age>=0&&age<1.3f){for(int n=0;n<4;n++){float t=age-n*.1f,fade=field_fade48(t,1);if(fade<=0)continue;field_bind48(10,(int)(4.5f*fade+.5f),0);field_cylinder48(m,g->x,g->y,24*(1-t),48*(1-t),16,g->time,20,0);}}
  if(e->skill==201&&age>=0&&age<1.5f){field_bind48(10,(int)(4.5f*field_fade48(age,1.5f)+.5f),0);for(int n=0;n<3;n++)field_cylinder48(m,g->x,g->y,8.8f,8.8f,120*fminf(1,age),g->time+n*2.0943951f,20,0);}
  if(e->skill==210&&age>=0&&age<.8f){field_bind48(9,(int)(15*field_fade48(age,.8f)+.5f),0);field_cylinder48(m,g->x,g->y,8,36*age/.8f,-32,0,20,0);field_cylinder48(m,g->x,g->y,8,20*age/.8f,-32,0,20,0);}
 }
}
