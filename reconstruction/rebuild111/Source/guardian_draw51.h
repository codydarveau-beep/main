/* Two original 3D Thor guardians. Original textures and 40 Hz source poses. */
#include "guardian_data51.h"
#include "guardian_motion53.h"
#include "guardian_pose_cache65.h"
static GuardianCache65 guardianCache65;
static void*guardianTextures51[2];
typedef struct {unsigned bank,group;float elapsed,duration,x,y,z,fx,fy;int repeat;float scale60;} GuardianDraw51;
static GuardianDraw51 guardianDraw51[SPRITE_SLOT_COUNT];
static unsigned char*guardian_expand51(const unsigned*d){unsigned char*cp=enemy_read51(d[0],d[1]);if(crc32(0,cp,d[1])!=d[3])fail("Guardian checksum failed");unsigned char*p=inflateasset("guardian",cp,d[1],d[2]);free(cp);return p;}
static float*guardian_pose_read65(void*context,unsigned bank,unsigned frame){(void)context;return(float*)guardian_expand51(bank==8?guardianPoses8[frame]:guardianPoses7[frame]);}
static void guardian_reset51(void){guardian_cache_clear65(&guardianCache65);for(unsigned i=0;i<2;i++){if(guardianTextures51[i])MmFreeContiguousMemory(guardianTextures51[i]);guardianTextures51[i]=NULL;}}
static void guardian_prepare51(void){for(unsigned slot=1;slot<SPRITE_SLOT_COUNT;slot++){unsigned bank=guardianDraw51[slot].bank;if(bank!=7&&bank!=8)continue;unsigned i=bank-7;if(guardianTextures51[i])continue;const unsigned*d=bank==7?guardianTexture7:guardianTexture8;unsigned char*p=guardian_expand51(d);guardianTextures51[i]=gpu_alloc(d[2]);memcpy(guardianTextures51[i],p,d[2]);free(p);}}
static void guardian_draw51(int slot,const float*m){
 const GuardianDraw51*a=&guardianDraw51[slot];if(a->bank!=7&&a->bank!=8)return;unsigned i=a->bank-7;const unsigned(*groups)[3]=i?guardianGroups8:guardianGroups7;const unsigned*g=groups[a->group];unsigned frame=guardian_frame53(g,a->elapsed,a->repeat);unsigned count=i?GUARDIAN_VERTICES8:GUARDIAN_VERTICES7;
 const unsigned*d=i?guardianPoses8[frame]:guardianPoses7[frame];if(d[2]!=count*20)fail("Guardian pose layout invalid");const float*pose65=guardian_cache_get65(&guardianCache65,a->bank,frame,d[2],guardian_pose_read65,NULL);if(!pose65)fail("Guardian pose cache load failed");
 float co,si;guardian_yaw53(a->fx,a->fy,&co,&si);
 gpu_depth_state(1);program(0);bindTexture(guardianTextures51[i],768,512,1536,0x00011d2a);
 uint32_t*p=pb_begin();for(int f=0;f<16;f++)p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+f*4,2);p=pb_push1(p,NV097_SET_CULL_FACE_ENABLE,0);p=pb_push1(p,NV097_SET_BLEND_ENABLE,1);p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,1);p=pb_push1(p,NV097_SET_ALPHA_FUNC,0x204);p=pb_push1(p,NV097_SET_ALPHA_REF,1);pb_end(p);
 for(unsigned begin=0;begin<count;begin+=30){unsigned end=begin+30;if(end>count)end=count;p=pb_begin();p=pb_push1(p,NV097_SET_BEGIN_END,5);
  for(unsigned n=begin;n<end;n++){const float*v=pose65+n*5;float lx,ly;guardian_local53(a->bank,v,&lx,&ly);float scale60=a->scale60>0?a->scale60:1;lx*=scale60;ly*=scale60;float x=a->x+co*lx-si*ly,y=a->y+si*lx+co*ly,z=a->z+v[2]*scale60;float sx=m[0]*x+m[1]*y+m[2]*z+m[3],sy=m[4]*x+m[5]*y+m[6]*z+m[7],depth=m[8]*x+m[9]*y+m[10]*z+m[11]-WORLD_SPRITE_BIAS;p=vertex(p,sx,sy,depth,v[3],v[4]);}
  p=pb_push1(p,NV097_SET_BEGIN_END,0);pb_end(p);
 }
}
