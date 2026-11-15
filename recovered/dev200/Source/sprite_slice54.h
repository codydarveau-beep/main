/* MIT. Clip screen-space sprite geometry and matching UV/depth interpolation.
 * Handles ordinary canvases and streamed crops without touching image pixels. */
#ifndef MYRO_SPRITE_SLICE54_H
#define MYRO_SPRITE_SLICE54_H
static float spriteClipLow54=-1e9f,spriteClipHigh54=1e9f;
typedef struct{float y,height,top,bottom,v0,v1;}SpriteSlice54;
static int sprite_slice54(float y,float height,float top,float bottom,float texHeight,SpriteSlice54*out){
 if(height<=0||spriteClipHigh54<=spriteClipLow54)return 0;float a=fmaxf(y,spriteClipLow54),b=fminf(y+height,spriteClipHigh54);if(b<=a)return 0;float ta=(a-y)/height,tb=(b-y)/height;*out=(SpriteSlice54){a,b-a,top+(bottom-top)*ta,top+(bottom-top)*tb,texHeight*ta,texHeight*tb};return 1;
}
static void sprite_clip_reset54(void){spriteClipLow54=-1e9f;spriteClipHigh54=1e9f;}
#endif
