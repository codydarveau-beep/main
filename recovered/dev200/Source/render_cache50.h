/* MIT. Reclaim lazily baked spell textures when their map/class is abandoned.
 * Original image pixels, opacity levels, geometry and timing stay unchanged.
 */
static unsigned spell_texture_bytes50(void){
 unsigned bytes=iceTexture48?65536:0;
 for(int i=0;i<FIELD_TEXTURE_COUNT50;i++)for(int level=0;level<16;level++)for(int threshold=0;threshold<2;threshold++)if(fieldTextures48[i][level][threshold])bytes+=fieldTexDefs48[i].side*fieldTexDefs48[i].side*4;
 for(int i=0;i<20;i++)if(lockonTextures49[i])bytes+=65536;
 return bytes;
}
static void spell_texture_release50(void){effect_cache_clear171();
 while(pb_busy()){}
 for(int i=0;i<FIELD_TEXTURE_COUNT50;i++)for(int level=0;level<16;level++)for(int threshold=0;threshold<2;threshold++)if(fieldTextures48[i][level][threshold]){
  MmFreeContiguousMemory(fieldTextures48[i][level][threshold]);fieldTextures48[i][level][threshold]=NULL;
 }
 for(int i=0;i<20;i++)if(lockonTextures49[i]){MmFreeContiguousMemory(lockonTextures49[i]);lockonTextures49[i]=NULL;}
 if(iceTexture48){MmFreeContiguousMemory(iceTexture48);iceTexture48=NULL;}
}
