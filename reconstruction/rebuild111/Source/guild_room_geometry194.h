/* MIT. Reconstructed guild-only geometry, separate from all native quest rooms.
 * Released dimensions are 1600x1600. Layout is reconstructed, not recovered.
 * At most one small map mesh/atlas is resident, through the normal world path. */
#ifndef MYRO_GUILD_ROOM_GEOMETRY194_H
#define MYRO_GUILD_ROOM_GEOMETRY194_H
static unsigned(*guildRoomCompleted194)(void);
static unsigned(*guildRoomStyle194)(void);
static unsigned guildRoomLoadedMask194,guildRoomLoadedStyle194;
static int guild_room_floor194(unsigned completed,float x,float y){
 if((x>=640&&x<960&&y>=1120&&y<1504)||(x>=128&&x<1472&&y>=800&&y<1120))return 1;
 if((completed&2)&&x>=128&&x<640&&y>=128&&y<800)return 1;
 if((completed&4)&&x>=672&&x<1088&&y>=128&&y<800)return 1;
 if((completed&8)&&x>=1120&&x<1472&&y>=128&&y<800)return 1;
 if((completed&16)&&((x>=128&&x<608&&y>=1152&&y<1472)||(x>=352&&x<416&&y>=1120&&y<1152)))return 1;
 if((completed&32)&&((x>=1088&&x<1472&&y>=1152&&y<1472)||(x>=1248&&x<1312&&y>=1120&&y<1152)))return 1;
 return 0;
}
static void guild_room_vertex194(float**out,float x,float y,float z,float u,float v){float*p=*out;*p++=x;*p++=y;*p++=z;*p++=u;*p++=v;*out=p;}
static void guild_room_quad194(float**out,float x0,float y0,float z0,float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3){
 guild_room_vertex194(out,x0,y0,z0,0,0);guild_room_vertex194(out,x1,y1,z1,15,0);guild_room_vertex194(out,x2,y2,z2,15,15);
 guild_room_vertex194(out,x0,y0,z0,0,0);guild_room_vertex194(out,x2,y2,z2,15,15);guild_room_vertex194(out,x3,y3,z3,0,15);
}
static void guild_room_load194(void){
 guildRoomLoadedMask194=guildRoomCompleted194?guildRoomCompleted194():0;guildRoomLoadedStyle194=guildRoomStyle194?guildRoomStyle194():0;
 mw=mh=100;gw=gh=200;tw=th=16;spawnx=800;spawny=1440;surfaceMap=494;surfaceCount45=propCount46=0;surfaceCells45=NULL;propCells46=NULL;
 unsigned char*collision=calloc(1,8+gw*gh);if(!collision)fail("Guild collision allocation failed");walk=collision+8;
 for(unsigned y=0;y<gh;y++)for(unsigned x=0;x<gw;x++)walk[y*gw+x]=(unsigned char)guild_room_floor194(guildRoomLoadedMask194,x*8+4,y*8+4);
 unsigned char*atlas=malloc(8+tw*th*2);if(!atlas)fail("Guild floor atlas allocation failed");terrain=(uint16_t*)(atlas+8);
 static const uint16_t tones[]={0xbdf7,0xd5d5,0xb6dd,0xbdd2};unsigned style=guildRoomLoadedStyle194<4?guildRoomLoadedStyle194:0;
 for(unsigned y=0;y<th;y++)for(unsigned x=0;x<tw;x++)terrain[y*tw+x]=(x==0||y==0)?0x4208:tones[style];
 cellStarts=malloc((mw*mh+1)*sizeof(*cellStarts));groundHeights=calloc(mw*mh*4,sizeof(*groundHeights));if(!cellStarts||!groundHeights)fail("Guild geometry metadata allocation failed");
 nverts=0;for(unsigned y=0;y<mh;y++)for(unsigned x=0;x<mw;x++){
  cellStarts[y*mw+x]=nverts;float xx=x*16+8,yy=y*16+8;if(!guild_room_floor194(guildRoomLoadedMask194,xx,yy))continue;
  nverts+=6;for(unsigned d=0;d<4;d++){static const int dx[]={-16,16,0,0},dy[]={0,0,-16,16};if(!guild_room_floor194(guildRoomLoadedMask194,xx+dx[d],yy+dy[d]))nverts+=6;}
 }cellStarts[mw*mh]=nverts;
 if(nverts>80000)fail("Guild mesh budget exceeded");meshRaw=malloc(nverts*20);if(!meshRaw)fail("Guild mesh allocation failed");meshVertices=(float*)meshRaw;float*out=meshVertices;
 for(unsigned y=0;y<mh;y++)for(unsigned x=0;x<mw;x++){
  float xx=x*16,yy=y*16;if(!guild_room_floor194(guildRoomLoadedMask194,xx+8,yy+8))continue;
  guild_room_quad194(&out,xx,yy,0,xx+16,yy,0,xx+16,yy+16,0,xx,yy+16,0);
  if(!guild_room_floor194(guildRoomLoadedMask194,xx-8,yy+8))guild_room_quad194(&out,xx,yy,0,xx,yy+16,0,xx,yy+16,32,xx,yy,32);
  if(!guild_room_floor194(guildRoomLoadedMask194,xx+24,yy+8))guild_room_quad194(&out,xx+16,yy+16,0,xx+16,yy,0,xx+16,yy,32,xx+16,yy+16,32);
  if(!guild_room_floor194(guildRoomLoadedMask194,xx+8,yy-8))guild_room_quad194(&out,xx+16,yy,0,xx,yy,0,xx,yy,32,xx+16,yy,32);
  if(!guild_room_floor194(guildRoomLoadedMask194,xx+8,yy+24))guild_room_quad194(&out,xx,yy+16,0,xx+16,yy+16,0,xx+16,yy+16,32,xx,yy+16,32);
 }
 if((unsigned)((unsigned char*)out-meshRaw)!=nverts*20)fail("Guild mesh length mismatch");
}
#endif
