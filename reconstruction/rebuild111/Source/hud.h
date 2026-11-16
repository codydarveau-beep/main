/* SPDX-License-Identifier: MIT. Compact alpha-textured HUD, no debug text plane. */
extern const unsigned char font_image[],loading_image[],merchant_image[],fontWidths[96];
extern const unsigned int font_image_raw,font_image_size,loading_image_raw,loading_image_size,merchant_image_raw,merchant_image_size;
#include "skin_layout.h"
static void*skinTexture;
#include "hud_batch.h"
#include "skin_colors.h"
#include "hud_palette.h"
static HudBatch hudBatch;
static unsigned hudSkinUsed253,hudDamageUsed253;
static float *hudSkinVertices54b,*hudDamageVertices54b;
static void*hudBatchTexture53;static unsigned hudBatchWidth53,hudBatchHeight53,hudBatchPitch53,hudBatchFormat53;
static void*loadingTexture;static int loadingArtError;
static SparseSprite merchantSprite;
#include "hud_state180.h"
static void hud_init(void){
 hudSkinVertices54b=gpu_alloc(HUD_BATCH_QUADS*HUD_QUAD_FLOATS*sizeof(float));
 hudDamageVertices54b=gpu_alloc(HUD_BATCH_QUADS*HUD_QUAD_FLOATS*sizeof(float));
 hudBatch.vertices=hudSkinVertices54b;
 sprite_load(&merchantSprite,"merchant",merchant_image,merchant_image_size,merchant_image_raw);
}
static void hud_setup_direct(void*texture,unsigned width,unsigned height,unsigned pitch,unsigned format,int blend){
 program(0);bindTexture(texture,width,height,pitch,format);uint32_t*p=pb_begin();
 p=hud_state180(p,blend);pb_end(p);
}
static void hud_setup(void*texture,unsigned width,unsigned height,unsigned pitch,unsigned format,int blend){
 if(hudBatch.active){if(texture!=hudBatchTexture53)fail("HUD batch texture mismatch");return;}
 hud_setup_direct(texture,width,height,pitch,format,blend);
}
static void item_icon_begin52(void);
/* Previous GPU frame must be idle before resetting either vertex arena. */
static void hud_frame_begin253(void){if(hudBatch.active)fail("HUD frame reset inside a batch");hudSkinUsed253=hudDamageUsed253=0;hudBatch.count=0;hudBatch.vertices=hudSkinVertices54b;}
static void hud_batch_begin_texture53(void*texture,unsigned width,unsigned height,unsigned pitch,unsigned format){if(hudBatch.active)fail("Nested HUD batch");unsigned used253=texture==skinTexture?hudSkinUsed253:hudDamageUsed253;if(used253>HUD_BATCH_QUADS)fail("HUD arena bounds invalid");hudBatch.vertices=(texture==skinTexture?hudSkinVertices54b:hudDamageVertices54b)+used253*HUD_QUAD_FLOATS;hudBatchTexture53=texture;hudBatchWidth53=width;hudBatchHeight53=height;hudBatchPitch53=pitch;hudBatchFormat53=format;hudBatch.count=0;hudBatch.active=1;}
static void hud_batch_begin(void){item_icon_begin52();hud_batch_begin_texture53(skinTexture,512,SKIN_H,2048,0x0001122a);}
static void hud_batch_end(void){
 hudBatch.active=0;if(!hudBatch.count)return;
 float*arena253=hudBatchTexture53==skinTexture?hudSkinVertices54b:hudDamageVertices54b;unsigned used253=(unsigned)(hudBatch.vertices-arena253)/HUD_QUAD_FLOATS+hudBatch.count;if(used253>HUD_BATCH_QUADS)fail("HUD arena capacity exceeded");if(hudBatchTexture53==skinTexture)hudSkinUsed253=used253;else hudDamageUsed253=used253;
 __sync_synchronize(); /* publish write-combined vertices before GPU submission */
 hud_setup_direct(hudBatchTexture53,hudBatchWidth53,hudBatchHeight53,hudBatchPitch53,hudBatchFormat53,1);
 uint32_t*p=pb_begin();
 p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT,2|(3<<4)|(20<<8));
 p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+9*4,2|(2<<4)|(20<<8));
 p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_OFFSET,(DWORD)hudBatch.vertices&0x03ffffff);
 p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_OFFSET+9*4,((DWORD)hudBatch.vertices+12)&0x03ffffff);
 p=pb_push1(p,NV097_BREAK_VERTEX_BUFFER_CACHE,0);
 p=pb_push1(p,NV097_SET_BEGIN_END,NV097_SET_BEGIN_END_OP_QUADS);
 unsigned count=hudBatch.count*4,at=0;
 while(at<count){unsigned n=count-at;if(n>252)n=252;p=pb_push1(p,NV097_DRAW_ARRAYS,((n-1)<<24)|at);at+=n;}
 p=pb_push1(p,NV097_SET_BEGIN_END,0);pb_end(p);
}
static void hud_quad(float x,float y,float w,float h,float u,float v,float uw,float vh){
 if(hudBatch.active){float*base200=hudBatchTexture53==skinTexture?hudSkinVertices54b:hudDamageVertices54b;if(hudBatch.vertices+(hudBatch.count+1)*HUD_QUAD_FLOATS>base200+HUD_BATCH_QUADS*HUD_QUAD_FLOATS)fail("HUD segment capacity exceeded");if(!hud_batch_add(&hudBatch,x,y,w,h,u,v,uw,vh))fail("HUD batch capacity exceeded");return;}
 uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_BEGIN_END,6);p=vertex(p,x,y,1,u,v);p=vertex(p,x+w,y,1,u+uw,v);p=vertex(p,x,y+h,1,u,v+vh);p=vertex(p,x+w,y+h,1,u+uw,v+vh);p=pb_push1(p,NV097_SET_BEGIN_END,0);pb_end(p);
}
#include "font_sample53.h"
static void ui_text(int,int,const char*,...);
static void hud_text(int x,int y,const char*fmt,...){char line[160];va_list a;va_start(a,fmt);vsnprintf(line,sizeof(line),fmt,a);va_end(a);ui_text(x,y,"%s",line);}
static void hud_fill(int x,int y,int w,int h,unsigned color){
 if(!hudBatch.active){pb_fill(x,y,w,h,color);return;}
 for(unsigned i=0;i<sizeof(skinColors)/sizeof(skinColors[0]);i++)if(skinColors[i]==color){float u,v;hud_solid_uv(i,&u,&v);hud_quad(x,y,w,h,u,v,0,0);return;}
 fail("HUD solid colour missing from atlas");
}
/* World draws remain native fills; only the explicitly scoped HUD is batched. */
#undef pb_fill
#define pb_fill hud_fill
#include "hud_theme.h"
static void hud_bar(int x,int y,int w,int n,int max,unsigned color){pb_fill(x,y,w,8,0xff101711);if(max>0&&n>0)pb_fill(x+1,y+1,(int)((int64_t)(w-2)*n/max),6,color);}
static void world_loading(const char*stage){
 snprintf(runtimeStage,sizeof(runtimeStage),"%s",stage);
 if(!loadingTexture&&!loadingArtError){
  if(loading_image_raw!=640*480*2)loadingArtError=-101;
  else{unsigned char*raw=malloc(loading_image_raw);if(!raw)loadingArtError=-100;
   else{z_stream z={0};z.zalloc=asset_zalloc;z.zfree=asset_zfree;z.next_in=(Bytef*)loading_image;z.avail_in=loading_image_size;z.next_out=raw;z.avail_out=loading_image_raw;int init=inflateInit(&z);
    if(init!=Z_OK)loadingArtError=init;else{int result=inflate(&z,Z_FINISH);if(result!=Z_STREAM_END||z.total_out!=loading_image_raw)loadingArtError=result?result:-102;inflateEnd(&z);}
    if(!loadingArtError){loadingTexture=MmAllocateContiguousMemoryEx(loading_image_raw,0,0x03ffafff,4096,PAGE_READWRITE|PAGE_WRITECOMBINE);if(loadingTexture)memcpy(loadingTexture,raw,loading_image_raw);else loadingArtError=-103;}free(raw);
   }
  }
 }

 pb_wait_for_vbl();pb_target_back_buffer();pb_reset();while(pb_busy()){}hud_frame_begin253();pb_fill(0,0,640,480,0xff17251f);
 if(loadingTexture){hud_setup(loadingTexture,640,480,1280,0x0001112a,0);hud_quad(0,0,640,480,0,0,640,480);}
 hud_panel(20,414,600,42);hud_text(32,421,"%s",stage);while(pb_busy()){}while(pb_finished()){}
}
static void world_loading_end(void){while(pb_busy()){}if(loadingTexture){MmFreeContiguousMemory(loadingTexture);loadingTexture=NULL;}}
#include "shop_draw.h"
