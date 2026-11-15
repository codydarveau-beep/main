/* MIT. Rare source Double Body outline, using the existing bounded effect cache. */
static void*npcHalo180[SPRITE_SLOT_COUNT];static unsigned npcHaloQuads180;
static void npc_halo_draw180(const NpcGame55*n,unsigned entity,unsigned life,const DrawActor*a,SparseSprite*s,float scale,float foot,float slope){
 if(npcHaloQuads180>=4||!npc_proc_flash180(n,entity,life)||!s||s->stream51||s->guardian51||!entityTextures[a->slot])return;
 unsigned pixels=s->w*s->h;if(pixels>32768||s->bytesPerPixel!=2&&s->bytesPerPixel!=4)return;
 MM_STATISTICS memory={0};memory.Length=sizeof(memory);MmQueryStatistics(&memory);if(memory.AvailablePages<1040)return;
 void**slot=npcHalo180+a->slot;effect_cache_prepare171(slot,pixels*2);while(pb_busy()){}
 const unsigned char*src=entityTextures[a->slot];uint16_t*out=*slot;
 for(unsigned i=0;i<pixels;i++){unsigned r,g,b,alpha;if(s->bytesPerPixel==4){b=src[i*4];g=src[i*4+1];r=src[i*4+2];alpha=src[i*4+3]*9/255;}else{unsigned v=src[i*2]|src[i*2+1]<<8;if(s->alpha4444){r=(v>>8&15)*17;g=(v>>4&15)*17;b=(v&15)*17;alpha=(v>>12)*9/15;}else{r=(v>>10&31)*255/31;g=(v>>5&31)*255/31;b=(v&31)*255/31;alpha=v&0x8000?9:0;}}out[i]=alpha?(uint16_t)((alpha<<12)|(r>>4)<<8|(g>>4)<<4|(b>>4)):0;}
 SparseSprite shape=*s;shape.bytesPerPixel=2;shape.alpha4444=1;gpu_actor_sprite50c(*slot,&shape,a->x,a->y,a->depth+.01f,scale*1.15f,foot,slope,a->sourceFade50c);npcHaloQuads180++;
}
