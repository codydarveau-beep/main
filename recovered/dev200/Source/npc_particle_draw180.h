#include "interior_rooms181.h"
/* MIT. Original procedural billboards share the bounded field texture cache. */
#include "npc_particle_pose180.h"
static void*npcParticleGpu180[sizeof(npcParticleTextures180)/sizeof(*npcParticleTextures180)][16];
static unsigned npcParticleQuads180;
static int npc_particle_bind180(unsigned texture,unsigned level){
 if(texture>=sizeof(npcParticleTextures180)/sizeof(*npcParticleTextures180)||!level||level>15)return 0;
 const NpcParticleTexture180*t=npcParticleTextures180+texture;if((t->tw*2)%64||!t->raw||t->raw>EFFECT_CACHE_BYTES171||t->raw!=t->tw*t->th*2||t->packed>t->raw+1024||t->offset>NPC_FX_BYTES172||t->packed>NPC_FX_BYTES172-t->offset)return 0;
 MM_STATISTICS memory={0};memory.Length=sizeof(memory);MmQueryStatistics(&memory);if((uint64_t)memory.AvailablePages*4096u<4u*1024u*1024u+t->raw+t->packed)return 0;
 void**slot=&npcParticleGpu180[texture][level];if(effect_cache_prepare171(slot,t->raw)){
  unsigned char*packed=malloc(t->packed),*raw=malloc(t->raw);int ok=packed&&raw&&npc_fx_read172(NULL,t->offset,packed,t->packed)&&crc32(0,packed,t->packed)==t->crc;
  if(ok){z_stream z={0};
#ifndef MYRO_HOST
  z.zalloc=asset_zalloc;z.zfree=asset_zfree;
#endif
  z.next_in=packed;z.avail_in=t->packed;z.next_out=raw;z.avail_out=t->raw;if(inflateInit(&z)!=Z_OK)ok=0;else{ok=inflate(&z,Z_FINISH)==Z_STREAM_END&&z.total_out==t->raw&&!z.avail_in;inflateEnd(&z);}}
  if(ok){for(unsigned i=0;i<t->raw;i+=2){unsigned pixel=raw[i]|(unsigned)raw[i+1]<<8,result=0;for(unsigned shift=0;shift<16;shift+=4)result|=((((pixel>>shift)&15)*level+7)/15)<<shift;raw[i]=(unsigned char)result;raw[i+1]=(unsigned char)(result>>8);}memcpy(*slot,raw,t->raw);}
  free(packed);free(raw);if(!ok){for(unsigned i=0;i<EFFECT_CACHE_SLOTS171;i++)if(effectCache171[i].slot==slot){effect_cache_evict171(i);break;}return 0;}
 }
 bindTexture(*slot,t->tw,t->th,t->tw*2,0x00011d2a);return 1;
}
static void npc_particle_draw180(unsigned id,unsigned age,unsigned created,unsigned seed,const float*m,float x,float y,float fixedX,float fixedY,float fixedZ){
 float zoom=sqrtf(m[0]*m[0]+m[1]*m[1]),scale=zoom/3.f;if(zoom<=0)return;
 for(unsigned index=0;index<sizeof(npcParticles180)/sizeof(*npcParticles180)&&npcParticleQuads180<128;index++){
  const NpcParticle180*n=npcParticles180+index;if(n->id!=id)continue;
  for(unsigned copy=0;copy<npc_particle_copies180(n)&&npcParticleQuads180<128;copy++){
   NpcParticlePose180 pose;if(!npc_particle_pose180(n,age,copy,seed+index*131u,created,&pose))continue;
   float pxWorld=pose.x,pyWorld=pose.y;if(n->kind==2){float yaw=atan2f(m[1],m[0]),co=cosf(yaw),si=sinf(yaw);pxWorld=pose.x*co-pose.y*si;pyWorld=pose.y*co+pose.x*si;}
   int attached=npp180(n,NP180_attachedEntity,0)!=0;float wx=(attached?x:fixedX)+pxWorld*8,wy=(attached?y:fixedY)+pyWorld*8,wz=(attached?height_at(x,y):fixedZ)+pose.z*8,sx,sy;
   if(!rooms_point181(&interiorRooms181,wx,wy))continue;
   if(npp180(n,NP180_shadowTexture,0))wz=height_at(wx,wy)+.12f;world_project(m,wx,wy,wz,&sx,&sy);
   float angle=pose.angle*.01745329252f;if(npp180(n,NP180_rotateWithCamera,0))angle+=atan2f(m[1],m[0]);float co=cosf(angle),si=sinf(angle),w=pose.w*scale,h=pose.h*scale;
   sx+=pose.offsetX*scale;sy+=pose.offsetY*scale;float radius=(fabsf(w)+fabsf(h))*.5f;if(sx+radius<0||sx-radius>640||sy+radius<0||sy-radius>480)continue;
   unsigned level=(unsigned)floorf(fminf(1,pose.alpha)*15+.5f);if(!level)continue;
   gpu_depth_state(0);program(0);if(!npc_particle_bind180(pose.texture,level))continue;
   const NpcParticleTexture180*t=npcParticleTextures180+pose.texture;
   float depth=m[8]*wx+m[9]*wy+m[10]*wz+m[11]-WORLD_SPRITE_BIAS*2;
   uint32_t*p=pb_begin();for(unsigned a=0;a<16;a++)p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+a*4,2);
   p=pb_push1(p,NV097_SET_CULL_FACE_ENABLE,0);p=pb_push1(p,NV097_SET_DEPTH_TEST_ENABLE,!pose.overlay);p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,0);p=pb_push1(p,NV097_SET_BLEND_ENABLE,1);p=pb_push1(p,NV097_SET_BLEND_FUNC_SFACTOR,1);p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,pose.additive?1:0x303);p=pb_push1(p,NV097_SET_BEGIN_END,6);
   static const float corner[4][2]={{-.5f,-.5f},{.5f,-.5f},{-.5f,.5f},{.5f,.5f}};
   for(unsigned c=0;c<4;c++){float px=corner[c][0]*w,py=corner[c][1]*h;p=vertex(p,sx+px*co-py*si,sy+px*si+py*co,depth,(c&1)?t->w-.5f:.5f,(c&2)?t->h-.5f:.5f);}
   p=pb_push1(p,NV097_SET_BEGIN_END,0);p=pb_push1(p,NV097_SET_BLEND_FUNC_SFACTOR,0x302);p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,0x303);pb_end(p);npcParticleQuads180++;
  }
 }
}
