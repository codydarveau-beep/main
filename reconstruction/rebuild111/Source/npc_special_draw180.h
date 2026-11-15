/* GPL-3.0-or-later. Bounded source SpiderWeb/SwirlingAura/QuadHorn geometry.
   Native cells are eight world units. Textures share the existing effect cache. */
static int npc_special_quad_mode181(unsigned texture,unsigned level,const float*m,const float q[4][3],float u0,float u1,unsigned additive){
 if(npcParticleQuads180>=128||!level)return 0;
 float px[4],py[4],depth[4],loX=INFINITY,loY=INFINITY,hiX=-INFINITY,hiY=-INFINITY;
 for(unsigned i=0;i<4;i++){world_project(m,q[i][0],q[i][1],q[i][2],px+i,py+i);depth[i]=m[8]*q[i][0]+m[9]*q[i][1]+m[10]*q[i][2]+m[11]-WORLD_SPRITE_BIAS;loX=fminf(loX,px[i]);hiX=fmaxf(hiX,px[i]);loY=fminf(loY,py[i]);hiY=fmaxf(hiY,py[i]);}
 if(hiX<0||loX>640||hiY<0||loY>480)return 0;
 gpu_depth_state(0);program(0);if(!npc_particle_bind180(texture,level))return 0;
 const NpcParticleTexture180*t=npcParticleTextures180+texture;uint32_t*p=pb_begin();
 for(unsigned a=0;a<16;a++)p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+a*4,2);
 p=pb_push1(p,NV097_SET_CULL_FACE_ENABLE,0);p=pb_push1(p,NV097_SET_DEPTH_TEST_ENABLE,1);p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,0);p=pb_push1(p,NV097_SET_BLEND_ENABLE,1);p=pb_push1(p,NV097_SET_BLEND_FUNC_SFACTOR,1);p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,additive?1:0x303);p=pb_push1(p,NV097_SET_BEGIN_END,6);
 for(unsigned i=0;i<4;i++)p=vertex(p,px[i],py[i],depth[i],(i&1)?u1*(t->w-1)+.5f:u0*(t->w-1)+.5f,(i&2)?t->h-.5f:.5f);
 p=pb_push1(p,NV097_SET_BEGIN_END,0);p=pb_push1(p,NV097_SET_BLEND_FUNC_SFACTOR,0x302);p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,0x303);pb_end(p);npcParticleQuads180++;return 1;
}
static int npc_special_quad_uv180(unsigned t,unsigned a,const float*m,const float q[4][3],float u0,float u1){return npc_special_quad_mode181(t,a,m,q,u0,u1,0);}
static int npc_special_quad180(unsigned t,unsigned a,const float*m,const float q[4][3]){return npc_special_quad_uv180(t,a,m,q,0,1);}
static unsigned npc_special_lifetime180(unsigned id){return id==404||id==200?30000:id==27?755:id==335?4000:0;}
static void npc_special_draw180(unsigned id,unsigned age,unsigned seed,const float*m,float x,float y){
 const float rad=.01745329252f;
 if(id==335){
  if(npcParticleQuads180>=128||!npc_particle_bind180(npcParticleSpecial180[3],15))return;gpu_depth_state(0);program(0);uint32_t*p=pb_begin();for(unsigned a=0;a<16;a++)p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+a*4,2);p=pb_push1(p,NV097_SET_DEPTH_TEST_ENABLE,0);p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,0);p=pb_push1(p,NV097_SET_BLEND_ENABLE,1);p=pb_push1(p,NV097_SET_BLEND_FUNC_SFACTOR,1);p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,0x303);p=pb_push1(p,NV097_SET_BEGIN_END,6);p=vertex(p,0,0,0,.5f,.5f);p=vertex(p,640,0,0,.5f,.5f);p=vertex(p,0,480,0,.5f,.5f);p=vertex(p,640,480,0,.5f,.5f);p=pb_push1(p,NV097_SET_BEGIN_END,0);p=pb_push1(p,NV097_SET_BLEND_FUNC_SFACTOR,0x302);pb_end(p);npcParticleQuads180++;
 }
 else if(id==404){float size=(1.5f+.05f*sinf((seed&1?3.141592654f:0)+age/(540*3.141592654f)))*8,z=height_at(x,y)+.12f;float q[4][3]={{x-size,y-size,z},{x+size,y-size,z},{x-size,y+size,z},{x+size,y+size,z}};npc_special_quad180(npcParticleSpecial180[0],15,m,q);}
 else if(id==200){float process=age/25.f,growth=process<=90?fmaxf(0,sinf(process*rad)):1,z=height_at(x,y);for(unsigned band=0;band<3;band++)for(unsigned k=0;k<20&&npcParticleQuads180<128;k++){
  float q[4][3],distance=(3.9f+.2f*band)*.22f*.6f*8,maxHeight=(15-2.f*band)*.22f*8,rise=(55-5.f*band)*rad;
  for(unsigned v=0;v<4;v++){unsigned segment=k+(v&1);float angle=(band*90+process*(band+3)+segment*15.75f)*rad,h=maxHeight*sinf((90+(segment-10.f)*9)*rad)*growth,extra=(v&2)?cosf(rise)*h:0;q[v][0]=x+(distance+extra)*cosf(angle);q[v][1]=y+(distance+extra)*sinf(angle);q[v][2]=z+((v&2)?sinf(rise)*h:0)+.12f;}
  npc_special_quad_uv180(npcParticleSpecial180[1],7,m,q,k/20.f,(k+1)/20.f);
 }}
 else if(id==27){/* specialeffect supplies only one owner: original Trail's zero-distance
                  fallback advances south for the configured two-cell overshoot. */
  for(unsigned born=0;born<=83&&born<=age;born+=17){unsigned elapsed=age-born;if(elapsed>=670)continue;unsigned random=npc_particle_hash180(seed+born);float angle=npc_particle_random180(random,1,0,6.283185307f,0),spread=npc_particle_random180(random,2,.1f,.3f,0)*8,cx=x+cosf(angle)*spread,cy=y-born*.024f*8+sinf(angle)*spread;
   float h=npc_particle_random180(random,3,.2f,1.8f,0)*8,b=npc_particle_random180(random,4,.06f,.22f,0)*8,rot=npc_particle_random180(random,5,0,6.283185307f,0),tilt=npc_particle_random180(random,6,-15,15,0)*rad,t=fminf(1,elapsed/330.f),offset=(.5f-2*(1-t)*(1-t))*8,z=height_at(cx,cy)+h*.9f+offset;
   float corners[5][3];for(unsigned v=0;v<5;v++){float vx=v==4?0:(v==0||v==3?-b:b),vy=v==4?0:(v<2?b:-b),vz=v==4?h:-h,yy=vy*cosf(tilt)-vz*sinf(tilt),zz=vy*sinf(tilt)+vz*cosf(tilt);corners[v][0]=cx+vx*cosf(rot)-yy*sinf(rot);corners[v][1]=cy+vx*sinf(rot)+yy*cosf(rot);corners[v][2]=z+zz;}
   unsigned alpha=(unsigned)(15*fminf(1,(670-elapsed)/170.f)+.5f);for(unsigned face=0;face<4&&npcParticleQuads180<128;face++){float q[4][3];memcpy(q[0],corners[face],sizeof(q[0]));memcpy(q[1],corners[(face+1)%4],sizeof(q[1]));memcpy(q[2],corners[4],sizeof(q[2]));memcpy(q[3],corners[4],sizeof(q[3]));npc_special_quad180(npcParticleSpecial180[2],alpha,m,q);}
  }
 }
}
