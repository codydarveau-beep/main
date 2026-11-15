/* MIT. Original NPC artwork can extend below its ACT ground origin.
 * Keep the upper body upright for wall occlusion; draw only the below-origin
 * skirt/feet/shadow at ground-plane depth, retaining source pixels/positions.
 * Both portions retain the caller's water clipping and original texture UVs. */
static void gpu_npc_sprite182(void*t,SparseSprite*s,float x,float y,float depth,float scale,float foot,float upright,float ground){
 float r[4];sprite_screen_rect(x,y,scale,s->anchorX,s->anchorY,s->h,r);
 float lo=spriteClipLow54,hi=spriteClipHigh54;
 spriteClipHigh54=fminf(hi,foot);
 if(fminf(r[1]+r[3],spriteClipHigh54)>fmaxf(r[1],lo))gpu_actor_sprite50c(t,s,x,y,depth,scale,foot,upright,0);
 spriteClipLow54=fmaxf(lo,foot);spriteClipHigh54=hi;
 if(fminf(r[1]+r[3],hi)>fmaxf(r[1],spriteClipLow54))gpu_sprite_plane50(t,s,x,y,depth,scale,depth+(r[1]-foot)*ground,depth+(r[1]+r[3]-foot)*ground);
 spriteClipLow54=lo;spriteClipHigh54=hi;
}
