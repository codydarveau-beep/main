/* SPDX-License-Identifier: MIT. Bounded quad vertex stream, one shared HUD atlas. */
#ifndef MYRO_HUD_BATCH_H
#define MYRO_HUD_BATCH_H
#define HUD_BATCH_QUADS 4096
#define HUD_QUAD_FLOATS 20
/* Four vertices of x,y,z,u,v; clockwise independent quads preserve draw order. */
typedef struct {float*vertices;unsigned count,peak;int active;} HudBatch;
static int hud_batch_add(HudBatch*b,float x,float y,float w,float h,float u,float v,float uw,float vh){
 if(w<=0||h<=0)return 1;if(b->count>=HUD_BATCH_QUADS)return 0;
 float*p=b->vertices+b->count*HUD_QUAD_FLOATS;
 const float q[HUD_QUAD_FLOATS]={x,y,1,u,v, x+w,y,1,u+uw,v, x+w,y+h,1,u+uw,v+vh, x,y+h,1,u,v+vh};
 memcpy(p,q,sizeof(q));b->count++;if(b->count>b->peak)b->peak=b->count;return 1;
}
#endif
