/* MIT. Known live buffers, not an invented estimate of total process memory. */
static unsigned memory_page183(unsigned n){return(n+4095u)&~4095u;}
static void ui_memory183(void){
 MM_STATISTICS mem={0};mem.Length=sizeof(mem);MmQueryStatistics(&mem);unsigned spritesGpu=0,artGpu=0;
 for(unsigned i=0;i<SPRITE_SLOT_COUNT;i++)if(entityTextures[i])spritesGpu+=entityCapacity51[i]?entityCapacity51[i]:65536;
 for(unsigned i=0;i<ART39_DRAW_LIMIT;i++)if(art39Textures[i])artGpu+=65536;
 unsigned terrainGpu=(gpuTerrain?memory_page183(tw*th*2):0)+(gpuMesh?memory_page183(nverts*20):0);
 unsigned sceneryGpu=(sceneTexture?memory_page183(sceneW*sceneH*2):0)+(sceneMesh?memory_page183(sceneVertices*20):0);
 unsigned actorCpu=sprites[0].raw&&spriteVariantIndex54<ACTOR_VARIANTS?actorBlobs[spriteVariantIndex54].raw:0;
 const char*names[]={"Free physical RAM","Terrain GPU","Scenery GPU","Player body CPU","Spell artwork CPU","Spell artwork GPU","Actor textures GPU","Enemy raw frames","Enemy packed frames","Shared effects GPU","Streaming audio CPU","NPC scripts CPU","NPC art cache CPU","CPU heap reserved","Heap returned (total)","Water CPU + GPU"};
 unsigned bytes[]={mem.AvailablePages*4096u,terrainGpu,sceneryGpu,actorCpu,artCacheBytes183+artRawBytes183+artPackedBytes183,artGpu,spritesGpu,cropBytes51,enemyPackedBytes164,effectCacheBytes171,classSoundBytes50+deathBytes51+musicResident50,npcGame55.programs.bytes,npcGame55.disc.artBytes,heap_footprint183(),heapReturned183,waterBytes190*2+waterPackedCapacity190};
 for(unsigned i=0;i<sizeof(bytes)/sizeof(*bytes);i++){ui_scaled(159,108+i*16,.85f,"%s",names[i]);char value[32];snprintf(value,sizeof(value),"%u KiB",bytes[i]/1024+(bytes[i]%1024!=0));ui_scaled(486-ui_text_width(value,.85f),108+i*16,.85f,"%s",value);}
 ui_scaled(159,354,.7f,"Buffers overlap heap; excludes driver memory.");
}
