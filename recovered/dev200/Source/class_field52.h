/* Source Songs.js/SpiderWeb/Basilica geometry, no gameplay radius markers. */
static void trans_tile52(const float*m,float x,float y,float radius,float lift,unsigned side){if(x-radius<0||y-radius<0||x+radius>=gw*8||y+radius>=gh*8)return;float z=height_at(x,y)+lift;SpellPoint41 q[4]={{x-radius,y-radius,z},{x+radius,y-radius,z},{x+radius,y+radius,z},{x-radius,y+radius,z}};float uv[8]={0,0,side,0,side,side,0,side};field_quad48(m,q,uv);}
static void trans_field52(const Combat*g,const float*m){
 int active=class_active50(g,SK52_PA_GOSPEL)||class_active50(g,SK52_HP_BASILICA);for(unsigned i=0;i<CLASS_AREAS50&&!active;i++){const ClassArea50*a=g->areas50+i;active=a->map==g->mapId&&a->until>g->time&&(a->id==SK52_PF_FOGWALL||a->id==SK52_HW_GRAVITATION);}if(FIELD_HAVE_WEB52)for(unsigned i=0;i<MOB_COUNT&&!active;i++)active=g->mobs[i].enabled&&g->mobs[i].hp>0&&g->mobs[i].class50.webUntil52>g->time;if(!active)return;
 uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,0x303);pb_end(p);
 for(unsigned i=0;i<CLASS_AREAS50;i++){const ClassArea50*a=g->areas50+i;if(a->map!=g->mapId||a->until<=g->time||(a->id!=SK52_PF_FOGWALL&&a->id!=SK52_HW_GRAVITATION))continue;int fog=a->id==SK52_PF_FOGWALL,rows=fog?1:2;
  field_bind48(fog?17:16,fog?9:3,0);for(int y=-rows;y<=rows;y++)for(int x=-2;x<=2;x++)trans_tile52(m,a->x+x*8,a->y+y*8,4,.15f,64);
  if(FIELD_HAVE_LENS52){field_bind48(14,10,0);for(int y=-rows;y<=rows;y++)for(int x=-2;x<=2;x++){float phase=((x+y)&1)?3.1415927f:0;float lift=(.4f-.2f*sinf(phase+g->time*1000/(540*3.1415927f)))*8;trans_tile52(m,a->x+x*8,a->y+y*8,4,lift,64);}}
 }
 if(class_active50(g,SK52_PA_GOSPEL)){field_bind48(16,1,0);for(int y=-3;y<=3;y++)for(int x=-3;x<=3;x++)if(abs(x)<2||abs(y)<2)trans_tile52(m,g->class50.gospelX52+x*8,g->class50.gospelY52+y*8,4,.15f,64);field_bind48(15,10,0);for(int y=-3;y<=3;y++)for(int x=-3;x<=3;x++)if(abs(x)<2||abs(y)<2)trans_tile52(m,g->class50.gospelX52+x*8,g->class50.gospelY52+y*8,4,3.2f-1.6f*sinf(((x+y)&1)*3.1415927f+g->time*1000/(540*3.1415927f)),64);}
 if(FIELD_HAVE_WEB52){field_bind48(13,15,0);for(unsigned i=0;i<MOB_COUNT;i++){const CombatMob*q=g->mobs+i;if(q->enabled&&q->hp>0&&q->class50.webUntil52>g->time)trans_tile52(m,q->x,q->y,8*(1.5f+.05f*sinf((i&1)*3.1415927f+g->time*1000/(540*3.1415927f))),.15f,128);}}
 if(class_active50(g,SK52_HP_BASILICA)){p=pb_begin();p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,1);pb_end(p);static const float radius[4]={2.45f,2.52f,2.6f,2.6f},height[4]={2,2.1f,2,2},angle[4]={0,10,26.6f,79.8f};for(unsigned i=0;i<4;i++){field_bind48(11,i<2?2:1,0);field_cylinder48(m,g->class50.basilicaX52,g->class50.basilicaY52,radius[i]*8,radius[i]*8,height[i]*8,angle[i]*.017453293f,4,0);}}
 p=pb_begin();p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,1);pb_end(p);
}
