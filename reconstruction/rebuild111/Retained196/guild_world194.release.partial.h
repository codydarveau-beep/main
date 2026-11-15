static void*guildTexture194,*guildMesh194;
static unsigned char*guildFloor194;
static unsigned guildFloorBytes194;
static unsigned guildBuilt194=~0u,guildDecor194=~0u;
static unsigned guildPropCount194;
static GuildProp194 guildProps194[GUILD_PROPS_MAX194];

static void guild_world_release194(void){
 if(guildTexture194)MmFreeContiguousMemory(guildTexture194);
 if(guildMesh194)MmFreeContiguousMemory(guildMesh194);

 guildTexture194=guildMesh194=NULL;

 free(guildFloor194);
 guildFloor194=NULL;

 guildFloorBytes194=guildPropCount194=0;
 guildBuilt194=guildDecor194=~0u;
}

static void campaign_guild_release194(void){
 campaign_reset200();
 guild_world_release194();
}
