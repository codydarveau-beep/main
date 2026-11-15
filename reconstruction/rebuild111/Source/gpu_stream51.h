/* Cropped enemy textures avoid allocating a full 1024-square MVP canvas. */
static unsigned entityCropped51[SPRITE_SLOT_COUNT];
static unsigned entityCapacity51[SPRITE_SLOT_COUNT],cropPitch51[SPRITE_SLOT_COUNT],cropWidth51[SPRITE_SLOT_COUNT],cropHeight51[SPRITE_SLOT_COUNT];
static unsigned char*cropScratch51;static unsigned cropScratchBytes51;
static unsigned entityUsed183[SPRITE_SLOT_COUNT],entityTime183,cropScratchUsed183;
/* Previous-frame GPU work must have completed before retiring any texture. */
static void gpu_entity_frame183(unsigned now,const unsigned char*used){entityTime183=now;for(unsigned i=1;i<SPRITE_SLOT_COUNT;i++){if(used[i]){entityUsed183[i]=now;continue;}if(entityTextures[i]&&(unsigned)(now-entityUsed183[i])>=3000){MmFreeContiguousMemory(entityTextures[i]);entityTextures[i]=NULL;entityCapacity51[i]=entityCropped51[i]=0;uploadedFrames[i]=~0u;uploadedSource[i]=NULL;}}if(cropScratch51&&(unsigned)(now-cropScratchUsed183)>=3000){free(cropScratch51);cropScratch51=NULL;cropScratchBytes51=0;}}
static void gpu_stream_reset51(void){for(unsigned i=1;i<SPRITE_SLOT_COUNT;i++){if(entityTextures[i])MmFreeContiguousMemory(entityTextures[i]);entityTextures[i]=NULL;entityCapacity51[i]=0;entityCropped51[i]=0;uploadedFrames[i]=~0u;uploadedSource[i]=NULL;}free(cropScratch51);cropScratch51=NULL;cropScratchBytes51=0;}
static void sprite_stream_upload51(SparseSprite*s,unsigned frame,int slot){
 unsigned state=spriteEpoch+(sprite_poisoned(slot)?0x80000000u:0)+(spriteFrozen[slot]?0x40000000u:0)+(spriteStone[slot]?0x10000000u:0);
 if(entityTextures[slot]&&uploadedFrames[slot]==frame&&uploadedSource[slot]==s&&uploadedEpoch[slot]==state&&uploadedFlash49[slot]==spriteFlash49[slot])return;
 cropScratchUsed183=entityTime183;unsigned*d=s->directory+frame*5;unsigned width=d[2]+2,height=d[3]+2,pitch=(width*2+63)&~63u,bytes=pitch*height;
 if(bytes>2097152)fail("Creature GPU crop too large");
 if(cropScratchBytes51<bytes){free(cropScratch51);cropScratch51=malloc(bytes);if(!cropScratch51)fail("Creature crop scratch allocation failed");cropScratchBytes51=bytes;}
 memset(cropScratch51,0,bytes);unsigned char*source=sprite_crop51(s,frame);for(unsigned y=0;y<d[3];y++)memcpy(cropScratch51+(y+1)*pitch+2,source+y*d[2]*2,d[2]*2);
 if(s->alpha4444)sprite_tint4444_45(cropScratch51,bytes/2,spriteFrozen[slot],spriteStone[slot],sprite_poisoned(slot));else{if(spriteFrozen[slot])sprite_ice(cropScratch51,bytes/2,2);if(spriteStone[slot])sprite_stone(cropScratch51,bytes/2,2);if(sprite_poisoned(slot))sprite_green(cropScratch51,bytes/2,2);}
 if(spriteFlash49[slot])sprite_flash49(cropScratch51,bytes/2,2,s->alpha4444,spriteFlash49[slot]);
 unsigned capacity=entityTextures[slot]?(entityCapacity51[slot]?entityCapacity51[slot]:65536):0;
 if(capacity<bytes||(capacity>65536&&capacity>bytes*4)){if(entityTextures[slot])MmFreeContiguousMemory(entityTextures[slot]);capacity=(bytes+4095)&~4095u;entityTextures[slot]=gpu_alloc(capacity);}entityCapacity51[slot]=capacity;entityCropped51[slot]=1;
 memcpy(entityTextures[slot],cropScratch51,bytes);spriteUploadBytes51+=bytes;cropPitch51[slot]=pitch;cropWidth51[slot]=width;cropHeight51[slot]=height;
 uploadedFrames[slot]=frame;uploadedSource[slot]=s;uploadedEpoch[slot]=state;uploadedFlash49[slot]=spriteFlash49[slot];
}
static void gpu_stream_plane51(void*texture,SparseSprite*s,float x,float y,float depth,float scale,float top,float bottom){
 int slot=-1;for(unsigned i=1;i<SPRITE_SLOT_COUNT;i++)if(entityTextures[i]==texture){slot=i;break;}if(slot<0)fail("Creature texture slot missing");unsigned*d=s->directory+uploadedFrames[slot]*5;
 gpu_depth_state(0);program(0);bindTexture(texture,cropWidth51[slot],cropHeight51[slot],cropPitch51[slot],s->alpha4444?0x00011d2a:0x0001102a);
 uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,0);for(int i=0;i<16;i++)p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+i*4,2);p=pb_push1(p,NV097_SET_CULL_FACE_ENABLE,0);p=pb_push1(p,NV097_SET_BLEND_ENABLE,1);
 float x0=x+((float)d[0]-s->anchorX-1)*scale,y0=y+((float)d[1]-s->anchorY-1)*scale,w=cropWidth51[slot]*scale,h=cropHeight51[slot]*scale;
 float z0=top+(bottom-top)*((float)d[1]-1)/s->h,z1=top+(bottom-top)*(d[1]+d[3]+1.f)/s->h;
 SpriteSlice54 slice;if(!sprite_slice54(y0,h,z0,z1,cropHeight51[slot],&slice)){pb_end(p);return;}p=pb_push1(p,NV097_SET_BEGIN_END,6);p=vertex(p,x0,slice.y,slice.top,0,slice.v0);p=vertex(p,x0+w,slice.y,slice.top,cropWidth51[slot],slice.v0);p=vertex(p,x0,slice.y+slice.height,slice.bottom,0,slice.v1);p=vertex(p,x0+w,slice.y+slice.height,slice.bottom,cropWidth51[slot],slice.v1);p=pb_push1(p,NV097_SET_BEGIN_END,0);pb_end(p);(void)depth;
}
