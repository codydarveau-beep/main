/* MIT. Original classic sprites with bounded source flight/orbit clocks.
 * roBrowserLegacy source EF15/22/62/116/117, pinned in TIMING-AUDIT49.md.
 */
static void classic_flight49(unsigned clip,const Art39Event*e,const Combat*g,const float*m,float zoom,float age,float duration,float arc){
 if(age<0||age>=duration)return;float t=age/duration,tx=e->x,ty=e->y;
 if(e->target45>=0&&e->target45<MOB_COUNT){const CombatMob*q=&g->mobs[e->target45];if(q->enabled&&q->life==e->life45){tx=q->x;ty=q->y;}}
 float x=e->startX+(tx-e->startX)*t,y=e->startY+(ty-e->startY)*t;
 art39_world_z45(clip,age,m,x,y,zoom,1,8*(3+arc*4*t*(1-t)));
}
/* Source EF15: five particle1 copies,20ms apart,250ms flight and100..500%
   growth. Hit-index offsets, retreat and arc restore the missing curved trail.
   Reuse original streamed art and the existing40-pose shared draw budget. */
static void classic_soul180(const Art39Event*e,const Combat*g,const float*m,float zoom,float age,unsigned hit){
 float tx=e->x,ty=e->y;if(e->target45>=0&&e->target45<MOB_COUNT){const CombatMob*q=g->mobs+e->target45;if(q->enabled&&q->life==e->life45){tx=q->x;ty=q->y;}}
 float angle=(hit%5)*1.256637061f,sx=e->startX+16*cosf(angle),sy=e->startY+16*sinf(angle),dx=tx-sx,dy=ty-sy,length=sqrtf(dx*dx+dy*dy);
 unsigned beforeGain200=art39Gain200;for(unsigned duplicate=0;duplicate<5;duplicate++){
  float elapsed=age+.25f-duplicate*.02f;if(elapsed<0||elapsed>=.25f)continue;float p=elapsed/.25f,sine=sinf(p*3.141592654f),retreat=fminf(24*(1+hit*.2f),length*.15f)*sine;
  float x=sx+dx*p,y=sy+dy*p;if(length>.001f){x-=dx/length*retreat;y-=dy/length*retreat;}
  art39Gain200=(unsigned)(beforeGain200*powf(.65f,(float)duplicate));art39_world_z45(43,elapsed,m,x,y,zoom*(1+4*p),1,24+32*(1+hit*.1f)*sine);
 }art39Gain200=beforeGain200;
}
static int classic_event49(const Art39Event*e,const Combat*g,const float*m,float zoom,float age){
 if(e->skill==10){for(int n=0;n<15;n++){float t=age-.4f-n*.01f;if(t<0||t>=1.3f)continue;float a=n*2.399963f;art39_world_z45(45,0,m,g->x+sinf(a)*12,g->y+cosf(a)*12,zoom*.18f,1,t/1.3f*48);}return 1;}
 if(e->skill==23||e->skill==78){unsigned beforeGain200=art39Gain200;if(e->skill==23)art39Gain200=128;int count=e->bolts>0?e->bolts:1;for(int n=0;n<count;n++){
 float at=e->skill==78?(n? .15f+(n-1)*.125f:0):n*.2f,t=age-at;
 if(e->skill==23){classic_soul180(e,g,m,zoom,t,(unsigned)n);if(t>=0&&t<.25f){art39_world_z45(45,t,m,e->startX,e->startY,zoom,0,24);art39_world_z45(46,t,m,e->x,e->y,zoom,0,16);}}
 else{classic_flight49(44,e,g,m,zoom,t+.5f,.5f,7.5f);if(t>=0&&t<.25f)art39_world_z45(46,t,m,e->x,e->y,zoom,0,12);if(t>=-.5f&&t<0)art39_world_z45(48+n%3,t+.5f,m,e->startX,e->startY,zoom,1,8+32*(t+.5f));}
 }art39Gain200=beforeGain200;return 1;}
 if(e->skill==74){for(int d=0;d<8;d++)for(int n=0;n<4;n++){float t=age-n*.1f;if(t<0||t>=.8f)continue;float a=d*.78539816f,r=t/.8f*64;art39_world_z45(42,t,m,e->startX+sinf(a)*r,e->startY+cosf(a)*r,zoom*(1-t/.8f*.6f),1,16);}return 1;}
 if(e->skill==118){float t=age/.14f;if(t<2){if(t>1)t=2-t;art39_world_z45(47,age,m,e->startX+(e->x-e->startX)*t,e->startY+(e->y-e->startY)*t,zoom,1,16);}return 1;}
 return 0;
}
static void classic_persistent49(const Combat*g,const float*m,float zoom){
 if(g->sightLeft>0)for(int n=9;n>=0;n--){float a=(g->time-n*.0122f)*5.1501519f;art39_world_z45(42,g->time,m,g->x+24*sinf(a),g->y+24*cosf(a),zoom*(1-n*.035f),1,32);}
 for(int i=0;i<3;i++)if(combat_safety_live(g,i)){const SafetyWall*w=&g->safety[i];float dx=g->x-w->x,dy=g->y-w->y;if(dx*dx+dy*dy<=5.6f*5.6f||m[8]*(w->x-g->x)+m[9]*(w->y-g->y)<0)art39_world(41,g->time-w->createdAt49,m,w->x,w->y,zoom,0);}
}
