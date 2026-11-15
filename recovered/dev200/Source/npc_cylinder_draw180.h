/* Original textures share the existing one-MiB field cache, including opacity variants. */
#include "npc_cylinder_geometry180.h"
static void*npcCylinderGpu180[sizeof(npcCylinderTextures180)/sizeof(*npcCylinderTextures180)][16];
static unsigned npcCylinderQuads180;
static int npc_cylinder_bind180(unsigned texture,unsigned level){
 if(texture>=sizeof(npcCylinderTextures180)/sizeof(*npcCylinderTextures180)||!level||level>15)return 0;
 MM_STATISTICS mem={0};mem.Length=sizeof(mem);MmQueryStatistics(&mem);if(mem.AvailablePages*4096u<4u*1024u*1024u)return 0;
 void**slot=&npcCylinderGpu180[texture][level];
 if(effect_cache_prepare171(slot,8192)){
  const NpcCylinderTexture180*t=npcCylinderTextures180+texture;unsigned char*packed=malloc(t->packed),*raw=malloc(8192);int ok=packed&&raw&&t->packed<=16384&&npc_fx_read172(NULL,t->offset,packed,t->packed)&&crc32(0,packed,t->packed)==t->crc;
  if(ok){z_stream stream={0};
#ifndef MYRO_HOST
   stream.zalloc=asset_zalloc;stream.zfree=asset_zfree;
#endif
   stream.next_in=packed;stream.avail_in=t->packed;stream.next_out=raw;stream.avail_out=8192;
   if(inflateInit(&stream)!=Z_OK)ok=0;else{ok=inflate(&stream,Z_FINISH)==Z_STREAM_END&&stream.total_out==8192&&!stream.avail_in;inflateEnd(&stream);}
  }
  if(ok){for(unsigned i=0;i<8192;i+=2){unsigned v=raw[i]|(unsigned)raw[i+1]<<8,a=((v>>12)*level+7)/15;v=(v&4095)|(a<<12);raw[i]=(unsigned char)v;raw[i+1]=(unsigned char)(v>>8);}memcpy(*slot,raw,8192);}
  free(raw);free(packed);if(!ok){for(unsigned i=0;i<EFFECT_CACHE_SLOTS171;i++)if(effectCache171[i].slot==slot){effect_cache_evict171(i);break;}return 0;}
 }
 bindTexture(*slot,64,64,128,0x00011d2a);return 1;
}
static void npc_cylinder_one180(const NpcCylinder180*c,unsigned age,unsigned seed,const float*m,float x,float y){
 NpcCylinderPose180 pose;if(!npc_cylinder_pose180(c,age,&pose)||npcCylinderQuads180>=512)return;
 unsigned level=(unsigned)floorf(fminf(1,pose.alpha)*15+.5f);if(!level)return;
 spell_world_begin41();if(!npc_cylinder_bind180(c->texture,level))return;
 uint32_t*pb=pb_begin();pb=pb_push1(pb,NV097_SET_BLEND_FUNC_DFACTOR,(c->flags&64)?1:0x303);pb_end(pb);
 float angle=(c->flags&4)?age*.00436332313f:0,random=(seed%65536)/65536.f*c->angleRandom,z=height_at(x,y)+.12f;
 for(unsigned i=0;i<c->sides&&npcCylinderQuads180<512;i++,npcCylinderQuads180++){
  SpellPoint41 q[4];static const unsigned ds[4]={0,0,1,1},up[4]={0,1,1,0};
  for(unsigned j=0;j<4;j++){float v[3];npc_cylinder_point180(c,&pose,i+ds[j],up[j],angle,random,m,v);q[j]=(SpellPoint41){x+v[0],y+v[1],z+v[2]};}
  float u=(float)i*64*c->repeatX/c->sides,v=(float)(i+1)*64*c->repeatX/c->sides;
  /* The current table repeats whole textures. Split at repeat boundaries so
     NPOT clamp sampling never stretches a repeated arc into one bright edge. */
  unsigned repeat=(unsigned)c->repeatX;if(repeat>1){float segment=64.f*repeat/c->sides;u=fmodf(u,64);v=u+segment;}
  float uv[8]={u+.5f,63.5f,u+.5f,.5f,v-.5f,.5f,v-.5f,63.5f};field_quad48(m,q,uv);
 }
 pb=pb_begin();pb=pb_push1(pb,NV097_SET_BLEND_FUNC_DFACTOR,0x303);pb_end(pb);
}
static void npc_cylinder_draw180(unsigned id,unsigned age,unsigned seed,const float*m,float x,float y){
 float sx,sy;world_project(m,x,y,height_at(x,y),&sx,&sy);if(sx< -200||sx>840||sy< -300||sy>780)return;
 for(unsigned i=0;i<sizeof(npcCylinders180)/sizeof(*npcCylinders180);i++){const NpcCylinder180*c=npcCylinders180+i;if(c->id!=id)continue;
  for(unsigned copy=0;copy<c->count;copy++){unsigned delay=c->delay+copy*c->gap;if(age<delay)continue;unsigned clock=age-delay;
   if(c->flags&32){int period=(int)c->duration+c->repeatDelay;if(period<1)period=1;unsigned cycle=clock/(unsigned)period;unsigned active=(c->duration+(unsigned)period-1)/(unsigned)period;if(active>32)active=32;for(unsigned n=0;n<active&&n<=cycle;n++){unsigned t=clock-(cycle-n)*(unsigned)period;if(t<c->duration)npc_cylinder_one180(c,t,seed+i*7919+copy*131+(cycle-n)*409,m,x,y);}}
   else npc_cylinder_one180(c,clock,seed+i*7919+copy*131,m,x,y);
  }
 }
}
