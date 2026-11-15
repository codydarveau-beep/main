/* Original furnishing generator recovered from deployed code; no invented plans. */
#ifndef MYRO_GUILD_PROPS197_H
#define MYRO_GUILD_PROPS197_H
#include "guild_props_data197.h"
static GuildProp194 guildProps197[GUILD_PROPS_MAX194];static unsigned guildPropCount197;
static void guild_props_build197(unsigned built,unsigned style){if(style>3)style=0;guildPropCount197=sizeof(guildPropBase197)/sizeof(*guildPropBase197);memcpy(guildProps197,guildPropBase197,sizeof(guildPropBase197));for(unsigned bit=0;bit<12;bit++)if((built&(1u<<bit))&&(bit<6||(built&32))){unsigned first=guildPropGroups197[style][bit][0],count=guildPropGroups197[style][bit][1];if(guildPropCount197+count>GUILD_PROPS_MAX194)fail("Guild prop budget exceeded");memcpy(guildProps197+guildPropCount197,guildPropPool197+first,count*sizeof(GuildProp194));guildPropCount197+=count;}}
static void guild_props_collision197(void){for(unsigned i=0;i<guildPropCount197;i++){const GuildProp194*p=guildProps197+i;if(!p->solid)continue;float minX=p->x-9,maxX=p->x+9,minY=p->y-6,maxY=p->y+6;
 if(p->model<5){const float*b=guildModels197[p->model].bounds;float c=cosf(p->angle),s=sinf(p->angle);minX=minY=1e20f;maxX=maxY=-1e20f;for(unsigned k=0;k<4;k++){float x=b[(k&1)?3:0]*p->scale,y=b[(k&2)?4:1]*p->scale,wx=p->x+c*x-s*y,wy=p->y+s*x+c*y;if(wx<minX)minX=wx;if(wx>maxX)maxX=wx;if(wy<minY)minY=wy;if(wy>maxY)maxY=wy;}}
 int x0=(int)floorf(minX/8),x1=(int)floorf(maxX/8),y0=(int)floorf(minY/8),y1=(int)floorf(maxY/8);for(int y=y0;y<=y1;y++)for(int x=x0;x<=x1;x++)if(x>=0&&y>=0&&(unsigned)x<gw&&(unsigned)y<gh)walk[y*gw+x]=0;
 }}
#endif
