/* MIT. Independent visual reconstructions for undocumented legacy built-ins.
 * Original client textures, deterministic animation, existing128-quad/cache caps.
 * These are explicitly not asserted to be pixel-identical proprietary effects. */
typedef int(*NpcLegacyPortal181)(const Combat*,const float*,float,float,unsigned);
static NpcLegacyPortal181 npcLegacyPortal181;
static unsigned npc_legacy_lifetime181(unsigned id){for(unsigned i=0;i<sizeof(npcLegacyGeometry181)/sizeof(*npcLegacyGeometry181);i++)if(npcLegacyGeometry181[i].id==id)return npcLegacyGeometry181[i].duration;return 0;}
static int npc_legacy_quad181(const NpcLegacyGeometry181*d,unsigned alpha,const float*m,const float q[4][3],float u0,float u1,int additive){return npc_special_quad_mode181(d->texture,alpha,m,q,u0,u1,additive);}
static void npc_legacy_billboard181(const NpcLegacyGeometry181*d,unsigned alpha,const float*m,float x,float y,float z,float w,float h){float zoom=sqrtf(m[0]*m[0]+m[1]*m[1]);if(zoom<=0)return;float co=m[0]/zoom,si=m[1]/zoom,q[4][3];for(unsigned v=0;v<4;v++){float dx=(v&1)?.5f*w:-.5f*w;q[v][0]=x+co*dx;q[v][1]=y+si*dx;q[v][2]=z+((v&2)?h:0);}npc_legacy_quad181(d,alpha,m,q,0,1,1);}
static void npc_legacy_draw181(const Combat*g,unsigned id,unsigned age,unsigned seed,const float*m,float x,float y){
 const NpcLegacyGeometry181*d=NULL;for(unsigned i=0;i<sizeof(npcLegacyGeometry181)/sizeof(*npcLegacyGeometry181);i++)if(npcLegacyGeometry181[i].id==id){d=npcLegacyGeometry181+i;break;}
 if(!d||age>=d->duration||npcParticleQuads180>=128||!rooms_point181(&interiorRooms181,x,y))return;
 float p=(float)age/d->duration,fade=fminf(1,fminf(p*8,(1-p)*5)),z=height_at(x,y)+.12f,rad=.01745329252f;unsigned alpha=(unsigned)(15*fminf(1,d->alpha*fade)+.5f);if(!alpha)return;
 if(d->mode==0){/* Rotating conical shells and four phased map-light bands. */
  for(unsigned band=0;band<d->bands;band++)for(unsigned side=0;side<16&&npcParticleQuads180<128;side++){
   float q[4][3],phase=age*.0006f+band*1.570796327f,spread=band*.5f;for(unsigned v=0;v<4;v++){float a=phase+(side+(v&1))*.392699082f,r=((v&2)?d->top:d->bottom)+spread;q[v][0]=x+cosf(a)*r*8;q[v][1]=y+sinf(a)*r*8;q[v][2]=z+((v&2)?d->height*8:0);}npc_legacy_quad181(d,alpha,m,q,side/16.f,(side+1)/16.f,1);
  }
 }else if(d->mode==1){/* Six latitude bands/twelve slices, ground-contact sphere. */
  float radius=d->radius*8*(.85f+.15f*sinf(p*3.141592654f));for(unsigned row=0;row<6;row++)for(unsigned column=0;column<12&&npcParticleQuads180<128;column++){
   float q[4][3];for(unsigned v=0;v<4;v++){float latitude=(row+((v&2)?1:0))*3.141592654f/6,longitude=(column+(v&1))*6.283185307f/12+age*.0003f;q[v][0]=x+radius*sinf(latitude)*cosf(longitude);q[v][1]=y+radius*sinf(latitude)*sinf(longitude);q[v][2]=z+radius*(1-cosf(latitude));}npc_legacy_quad181(d,alpha,m,q,column/12.f,(column+1)/12.f,1);
  }
 }else if(d->mode==2){for(unsigned i=0;i<10&&npcParticleQuads180<128;i++){float t=fmodf(p+i*.1f,1),a=t*12.56637061f+i*.628318531f,r=8+16*t;npc_legacy_billboard181(d,alpha,m,x+cosf(a)*r,y+sinf(a)*r,z+t*24,20,3);}}
 else if(d->mode==3){/* Four narrow five-sided shafts with gentle width movement. */
  for(unsigned band=0;band<4;band++)for(unsigned edge=0;edge<5&&npcParticleQuads180<128;edge++){
   float width=(d->variant==1?(band==3?4:4+2*band):(band==3?2:2+band))*.32f;if(band&1)width+=.16f*sinf(age*.0008f+band*3.141592654f);float q[4][3];for(unsigned v=0;v<4;v++){float a=((edge+(v&1))*72+band*25)*rad;q[v][0]=x+width*cosf(a)+((v&2)?-22.4f:0);q[v][1]=y+width*sinf(a)+((v&2)?-22.4f:0);q[v][2]=z+((v&2)?96:0);}npc_legacy_quad181(d,alpha,m,q,0,1,1);
  }
 }else if(d->mode==4){float radius=d->radius*8*(.7f+.3f*fminf(1,p*4)),a=age*.001f,co=cosf(a),si=sinf(a),q[4][3];for(unsigned v=0;v<4;v++){float xx=(v&1)?radius:-radius,yy=(v&2)?radius:-radius;q[v][0]=x+xx*co-yy*si;q[v][1]=y+xx*si+yy*co;q[v][2]=z;}npc_legacy_quad181(d,alpha,m,q,0,1,1);}
 else if(d->mode==5){/* Procedural black bat silhouettes; slow/fast Niflheim variants. */
  float zoom=sqrtf(m[0]*m[0]+m[1]*m[1]);if(zoom<=0)return;float co=m[0]/zoom,si=m[1]/zoom;
  for(unsigned bat=0;bat<4&&npcParticleQuads180<128;bat++){unsigned random=npc_particle_hash180(seed+bat*7919);float phase=age*.001f*d->speed+bat*1.570796327f,cx=x+cosf(phase)*(12+(random%17)),cy=y+sinf(phase)*(12+(random%17)),cz=z+20+bat*7+4*sinf(phase*2),flap=sinf(age*.015f*d->speed+bat),w=5+fabsf(flap)*2;
   float outline[10][2]={{-1,0},{-w,3*flap},{-w*.65f,-1},{-w*.4f,-2},{0,-2},{w*.4f,-2},{w*.65f,-1},{w,3*flap},{1,0},{0,1}};
   for(unsigned edge=0;edge<10&&npcParticleQuads180<128;edge++){float q[4][3];for(unsigned v=0;v<4;v++){unsigned point=v==0?edge:v==1?(edge+1)%10:10;float dx=point==10?0:outline[point][0],dy=point==10?0:outline[point][1];q[v][0]=cx+co*dx;q[v][1]=cy+si*dx;q[v][2]=cz+dy;}npc_legacy_quad181(d,alpha,m,q,0,1,0);}
  }
 }else if(d->mode==6&&npcLegacyPortal181){if(npcLegacyPortal181(g,m,x,y,seed))npcParticleQuads180+=npcParticleQuads180<=112?16:128-npcParticleQuads180;}
}
