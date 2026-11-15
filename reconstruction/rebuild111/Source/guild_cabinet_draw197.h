/* One 128 KiB cabinet atlas, six current views; never all 48 views resident. */
#ifndef MYRO_GUILD_CABINET_DRAW197_H
#define MYRO_GUILD_CABINET_DRAW197_H
#include "guild_view197.h"
static void*guildCabinetTexture197;static unsigned guildCabinetPose197[6]={~0u,~0u,~0u,~0u,~0u,~0u};
static void guild_cabinet_release197(void){if(guildCabinetTexture197)MmFreeContiguousMemory(guildCabinetTexture197);guildCabinetTexture197=NULL;for(unsigned i=0;i<6;i++)guildCabinetPose197[i]=~0u;}
static void campaign_guild_release197(void){campaign_reset200();guild_furnish_release197();guild_cabinet_release197();}
static int guild_cabinet_read197(void*ctx,unsigned at,unsigned char*out,unsigned bytes){FILE*f=ctx;return at<=GUILD_VIEWS_BYTES197&&bytes<=GUILD_VIEWS_BYTES197-at&&!fseek(f,at,SEEK_SET)&&fread(out,1,bytes,f)==bytes;}
/* Main calls this at the same GPU frame fence as all other sprite uploads. */
static void guild_cabinet_prepare197(const Combat*g,float camera){if(g->mapId!=GUILD_MAP194)return;unsigned mask=guild_world_completed194();if(!(mask&32))mask=0;/* world_camera looks from (sin(yaw),-cos(yaw)); the controls face +X. */unsigned view=guild_view_direction197(camera-1.57079632679f,0);int changed=0;for(unsigned i=0;i<6;i++)if(guildCabinetPose197[i]!=((mask&(1u<<(6+i)))?view:~0u))changed=1;if(!changed)return;
 while(pb_busy()){}
 if(!guildCabinetTexture197){guildCabinetTexture197=gpu_alloc(256*256*2);if(!guildCabinetTexture197)return;memset(guildCabinetTexture197,0,256*256*2);}
#ifdef MYRO_HOST
 const char*path=getenv("MYRO_GUILD_VIEWS197");if(!path)path="../Guild/Directional197/views.bin";
#else
 const char*path="D:\\guildviews.bin";
#endif
 FILE*f=fopen(path,"rb");if(!f)return;if(fseek(f,0,SEEK_END)||ftell(f)!=GUILD_VIEWS_BYTES197){fclose(f);return;}unsigned char*frame=malloc(GUILD_VIEW_RAW197);if(!frame){fclose(f);return;}
 for(unsigned i=0;i<6;i++){unsigned wanted=(mask&(1u<<(6+i)))?view:~0u;if(wanted==guildCabinetPose197[i])continue;unsigned x=(i%4)*64,y=(i/4)*96;
  if(wanted!=~0u&&!guild_view_decode197(i,wanted,guild_cabinet_read197,f,frame,GUILD_VIEW_RAW197))continue;
  for(unsigned row=0;row<96;row++){unsigned char*to=(unsigned char*)guildCabinetTexture197+((y+row)*256+x)*2;if(wanted==~0u)memset(to,0,128);else memcpy(to,frame+row*128,128);}guildCabinetPose197[i]=wanted;
 }
 free(frame);fclose(f);__sync_synchronize();
}
static void guild_cabinet_draw197(const Combat*g,const float*m,float zoom,float slope){if(g->mapId!=GUILD_MAP194||!guildCabinetTexture197)return;unsigned mask=guild_world_completed194();if(!(mask&32))return;
 for(unsigned i=0;i<6;i++){if(!(mask&(1u<<(6+i)))||guildCabinetPose197[i]==~0u)continue;float wx=1316,wy=464+i*88;if(!rooms_point181(&interiorRooms181,wx,wy))continue;float z=height_at(wx,wy),sx,sy;world_project(m,wx,wy,z,&sx,&sy);float scale=zoom*.5f,w=64*scale,h=96*scale,left=sx-32*scale,top=sy-94*scale;if(left+w<0||left>640||top+h<0||top>480)continue;float depth=m[8]*wx+m[9]*wy+m[10]*z+m[11]-WORLD_SPRITE_BIAS,zt=sprite_upright_cached50(depth,top,sy,slope),zb=sprite_upright_cached50(depth,top+h,sy,slope);
  hud_setup_direct(guildCabinetTexture197,256,256,512,0x0001102a,0);uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_DEPTH_TEST_ENABLE,1);p=pb_push1(p,NV097_SET_DEPTH_MASK,1);p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,1);p=pb_push1(p,NV097_SET_ALPHA_FUNC,0x204);p=pb_push1(p,NV097_SET_ALPHA_REF,127);pb_end(p);ground_quad58(left,top,w,h,zt,zb,(i%4)*64,(i/4)*96,64,96);
 }gpu_depth_state(1);
}
#endif
