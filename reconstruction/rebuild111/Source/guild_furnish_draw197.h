/* Authentic released furniture atlas AND 3D mesh, extracted from the same pack. */
#ifndef MYRO_GUILD_FURNISH_DRAW197_H
#define MYRO_GUILD_FURNISH_DRAW197_H
static void*guildFurnishTexture197;static float*guildFurnishMesh197;
static void guild_furnish_release197(void){if(guildFurnishTexture197)MmFreeContiguousMemory(guildFurnishTexture197);guildFurnishTexture197=NULL;free(guildFurnishMesh197);guildFurnishMesh197=NULL;}
static void guild_furnish_prepare197(const Combat*g){if(g->mapId!=GUILD_MAP194||guildFurnishTexture197)return;
#ifdef MYRO_HOST
 const char*path=getenv("MYRO_GUILD_HALL197");if(!path)path="../Guild/guildhall.bin";
#else
 const char*path="D:\\guildhall.bin";
#endif
 FILE*f=fopen(path,"rb");if(!f)fail("Guild furnishing pack missing");unsigned packed=GUILD_ATLAS_PACKED197+GUILD_MESH_PACKED197;unsigned char*p=malloc(packed);if(!p){fclose(f);return;}int ok=!fseek(f,0,SEEK_END)&&ftell(f)==packed&&!fseek(f,0,SEEK_SET)&&fread(p,1,packed,f)==packed;fclose(f);if(!ok){free(p);fail("Guild furnishing read failed");}unsigned char*raw=inflateasset("Guild furnishing atlas",p,GUILD_ATLAS_PACKED197,131072);if(crc32(0,raw,131072)!=GUILD_ATLAS_RAW_CRC197)fail("Guild furnishing atlas checksum mismatch");guildFurnishTexture197=gpu_alloc(131072);memcpy(guildFurnishTexture197,raw,131072);free(raw);guildFurnishMesh197=(float*)inflateasset("Guild original furniture mesh",p+GUILD_ATLAS_PACKED197,GUILD_MESH_PACKED197,GUILD_MESH_RAW197);free(p);if(crc32(0,(unsigned char*)guildFurnishMesh197,GUILD_MESH_RAW197)!=GUILD_MESH_RAW_CRC197)fail("Guild furniture mesh checksum mismatch");}
static void guild_furnish_draw197(const Combat*g,const float*m){if(g->mapId!=GUILD_MAP194||!guildFurnishTexture197||!guildFurnishMesh197)return;hud_setup_direct(guildFurnishTexture197,256,256,512,0x0001102a,0);uint32_t*cmd=pb_begin();cmd=pb_push1(cmd,NV097_SET_DEPTH_TEST_ENABLE,1);cmd=pb_push1(cmd,NV097_SET_DEPTH_MASK,1);cmd=pb_push1(cmd,NV097_SET_ALPHA_TEST_ENABLE,1);cmd=pb_push1(cmd,NV097_SET_ALPHA_FUNC,0x204);cmd=pb_push1(cmd,NV097_SET_ALPHA_REF,127);pb_end(cmd);
 for(unsigned i=0;i<guildPropCount197;i++){const GuildProp194*p=guildProps197+i;if(p->model>=5||!rooms_point181(&interiorRooms181,p->x,p->y))continue;const float*v=guildFurnishMesh197+guildModels197[p->model].first*5;unsigned count=guildModels197[p->model].count;float c=cosf(p->angle),s=sinf(p->angle),base=height_at(p->x,p->y);uint32_t*cmd=pb_begin();cmd=pb_push1(cmd,NV097_SET_BEGIN_END,5);
  for(unsigned j=0;j<count;j++,v+=5){float x=p->x+(c*v[0]-s*v[1])*p->scale,y=p->y+(s*v[0]+c*v[1])*p->scale,z=base+v[2]*p->scale,sx,sy;world_project(m,x,y,z,&sx,&sy);float depth=m[8]*x+m[9]*y+m[10]*z+m[11];cmd=vertex(cmd,sx,sy,depth,v[3],v[4]);}
  cmd=pb_push1(cmd,NV097_SET_BEGIN_END,0);pb_end(cmd);
 }gpu_depth_state(1);
}
#endif
