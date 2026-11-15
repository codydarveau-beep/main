#ifndef MYRO_MAP_MARKERS64_H
#define MYRO_MAP_MARKERS64_H
typedef struct{unsigned map,id,x,y,color,active;}MapMarker64;
static MapMarker64 mapMarkers64[32];
static int map_marker_set64(unsigned map,unsigned id,unsigned x,unsigned y,unsigned color,int show){int empty=-1;for(unsigned i=0;i<32;i++){MapMarker64*p=mapMarkers64+i;if(p->active&&p->map==map&&p->id==id){if(show)*p=(MapMarker64){map,id,x,y,color,1};else p->active=0;return 1;}if(!p->active||p->map!=map)empty=(int)i;}if(!show)return 1;if(empty<0)return 0;mapMarkers64[empty]=(MapMarker64){map,id,x,y,color,1};return 1;}
#endif
