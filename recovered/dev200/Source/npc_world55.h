/* MIT. Original-script map operations; map transitions run outside the interpreter. */
#ifndef MYRO_NPC_WORLD55_H
#define MYRO_NPC_WORLD55_H
#include "npc_vm55.h"
typedef struct{Combat*game;const char*const*names;const unsigned*widths,*heights;uint32_t count,pending,map,random,clean;float x,y;unsigned fee64;}NpcWorld55;
typedef int(*NpcWorldWarp55)(void*,Combat*,uint32_t,float,float,int,int);
static int npc_world_map55(const NpcWorld55*w,const char*name){size_t n=strlen(name);if(n>4&&!strcmp(name+n-4,".gat"))n-=4;for(uint32_t i=0;i<w->count;i++)if(strlen(w->names[i])==n&&!strncmp(name,w->names[i],n))return(int)i;return-1;}
static int npc_world_args55(NpcMachine55*m,const NpcValue55*args,NpcValue55*name,int64_t*x,int64_t*y){return npc_vm_value55(m,args[0],name)&&name->kind==N55_STRING_KIND&&npc_vm_integer55(m,args[1],x)&&npc_vm_integer55(m,args[2],y)&&*x>=INT32_MIN&&*x<=INT32_MAX&&*y>=INT32_MIN&&*y<=INT32_MAX;}
static int npc_world_command55(NpcWorld55*w,NpcMachine55*m,int attached,const char*command,const NpcValue55*args,uint32_t count,NpcValue55*out){
 *out=npc_vm_number55(0);
 if(!strcmp(command,"strcharinfo")){int64_t mode;if(count!=1||!npc_vm_integer55(m,args[0],&mode))return N55_ERROR;if(mode!=3)return-1;if(!attached||w->game->mapId>=w->count)return N55_ERROR;*out=npc_vm_string55(w->names[w->game->mapId]);return N55_READY;}
 if(!strcmp(command,"getmapusers")){NpcValue55 name;if(count!=1||!npc_vm_value55(m,args[0],&name)||name.kind!=N55_STRING_KIND)return N55_ERROR;int map=npc_world_map55(w,name.text);*out=npc_vm_number55(map<0?-1:(uint32_t)map==w->game->mapId);return N55_READY;}
 if(!strcmp(command,"getareausers")){NpcValue55 name;int64_t x0,y0,x1,y1;if(count!=5||!npc_vm_value55(m,args[0],&name)||name.kind!=N55_STRING_KIND||!npc_vm_integer55(m,args[1],&x0)||!npc_vm_integer55(m,args[2],&y0)||!npc_vm_integer55(m,args[3],&x1)||!npc_vm_integer55(m,args[4],&y1)||x1<x0||y1<y0)return N55_ERROR;int map=npc_world_map55(w,name.text);int x=(int)(w->game->x/8),y=(int)(w->game->y/8);*out=npc_vm_number55(map<0?-1:(unsigned)map==w->game->mapId&&x>=x0&&x<=x1&&y>=y0&&y<=y1);return N55_READY;}
 if(!strcmp(command,"getmapxy")){int64_t type;NpcValue55 who;if(count<4||count>5||!attached||!npc_vm_integer55(m,args[3],&type)||type!=0||w->game->mapId>=w->count||!m->api.write)return N55_ERROR;for(unsigned i=0;i<3;i++)if(args[i].kind!=N55_REFERENCE_KIND)return N55_ERROR;if(count==5){if(!npc_vm_value55(m,args[4],&who)||who.kind!=N55_STRING_KIND)return N55_ERROR;if(strcmp(who.text,w->game->name56)){*out=npc_vm_number55(-1);return N55_READY;}}NpcValue55 values[]={npc_vm_string55(w->names[w->game->mapId]),npc_vm_number55((int)(w->game->x/8)),npc_vm_number55((int)(w->game->y/8))};for(unsigned i=0;i<3;i++)if(!m->api.write(m->api.context,args+i,values+i))return N55_ERROR;return N55_READY;}
 int warp=!strcmp(command,"warp");if(!warp&&strcmp(command,"savepoint"))return-1;
 if(!attached||w->pending||count<3||count>(warp?4u:3u))return N55_ERROR;
 NpcValue55 name;int64_t x,y,clean=1;if(!npc_world_args55(m,args,&name,&x,&y)||(count==4&&(!npc_vm_integer55(m,args[3],&clean)||(clean!=0&&clean!=1))))return N55_ERROR;
 int map;int random=0;float wx,wy;
 if(warp&&(!strcmp(name.text,"Save")||!strcmp(name.text,"SavePoint"))){WorldPosition p=w->game->home;if(p.map>=w->count||!combat_position_valid(p))return N55_ERROR;map=(int)p.map;wx=p.x;wy=p.y;}
 else{map=warp&&!strcmp(name.text,"Random")?(int)w->game->mapId:npc_world_map55(w,name.text);if(map<0||(uint32_t)map>=w->count)return N55_ERROR;random=warp&&(!strcmp(name.text,"Random")||x<=0||y<=0);if(!random&&(x<1||y<1||x>=(int64_t)w->widths[map]/8||y>=(int64_t)w->heights[map]/8))return N55_ERROR;wx=random?0:(float)(x*8+4);wy=random?0:(float)(y*8+4);}
 if(!warp){w->game->home=(WorldPosition){(unsigned)map,wx,wy};return N55_READY;}
 w->pending=1;w->map=(uint32_t)map;w->x=wx;w->y=wy;w->random=(uint32_t)random;w->clean=(uint32_t)clean;return N55_WAIT;
}
/* The renderer/map loader must finish before script statements after warp execute. */
static int npc_world_commit55(NpcWorld55*w,NpcMachine55*m,NpcWorldWarp55 warp,void*context){if(!w->pending||m->status!=N55_WAIT||!warp)return 0;if(w->game->zeny<(int)w->fee64){w->pending=w->fee64=0;npc_vm_error55(m,"Not enough Zeny for entry");return 0;}int ok=warp(context,w->game,w->map,w->x,w->y,(int)w->random,(int)w->clean);w->pending=0;if(!ok){w->fee64=0;npc_vm_error55(m,"NPC destination could not be loaded");return 0;}w->game->zeny-=(int)w->fee64;w->fee64=0;return npc_vm_resume55(m,npc_vm_number55(0));}
static void npc_world_cancel55(NpcWorld55*w){w->pending=w->fee64=0;}
#endif
