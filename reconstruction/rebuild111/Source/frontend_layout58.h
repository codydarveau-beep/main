/* MIT. Pixel coordinates from the original 576x342 client backgrounds. */
#ifndef MYRO_FRONTEND_LAYOUT58_H
#define MYRO_FRONTEND_LAYOUT58_H
#include <stdint.h>
#include <string.h>
static int front_slot_x58(unsigned slot){return 92+(int)(slot%3)*163;}
static int front_slot_shadow58(unsigned slot){return 156+(int)(slot%3)*163;}
static const unsigned char frontOpposite58[6]={3,5,4,0,2,1};
enum{FRONT_STAT_X112=511,FRONT_STAT_Y112=198};
static const short frontStatPoints58[6][2]={{511,136},{566,167},{566,229},{511,260},{456,167},{456,229}};
static int front_stat_adjust58(unsigned char stats[6],unsigned stat,int delta){if(stat>=6)return 0;int n=stats[stat]+delta;if(n<1||n>9)return 0;stats[stat]=(unsigned char)n;stats[frontOpposite58[stat]]=(unsigned char)(10-n);return 1;}
/* Directional focus follows the actual vertices, rather than stat-array order. */
static int front_spatial265(const short(*points)[2],unsigned count,int selected,unsigned buttons){int nx=!!(buttons&8192)-!!(buttons&4096),ny=!!(buttons&2048)-!!(buttons&1024);if(!nx&&!ny)return selected;int best=selected;int64_t bestDot2=0,bestDistance=1;for(unsigned i=0;i<count;i++){if((int)i==selected)continue;int dx=points[i][0]-points[selected][0],dy=points[i][1]-points[selected][1],dot=dx*nx+dy*ny;int64_t distance=dx*dx+dy*dy,dot2=(int64_t)dot*dot;if(dot<=0||!distance)continue;if(best==selected||dot2*bestDistance>bestDot2*distance||(dot2*bestDistance==bestDot2*distance&&distance<bestDistance)){best=(int)i;bestDot2=dot2;bestDistance=distance;}}return best;}
static int front_field_move265(int field,unsigned buttons){static const int ids[]={0,1,7,8,9,10};static const short points[][2]={{140,310},{511,243},{136,338},{321,203},{321,354},{136,376}};int selected=0;for(unsigned i=0;i<6;i++)if(ids[i]==field||(i==1&&field>=1&&field<=6))selected=i;int next=front_spatial265(points,6,selected,buttons);return next==selected?field:ids[next];}
typedef struct{unsigned mode;unsigned char before[6];int sexBefore;}FrontEdit265;
static void front_edit_begin265(FrontEdit265*edit,const unsigned char stats[6],int sex,unsigned mode){memcpy(edit->before,stats,6);edit->sexBefore=sex;edit->mode=mode;}
static int front_edit_input265(FrontEdit265*edit,unsigned char stats[6],int*field,int*sex,unsigned p){if(!edit->mode)return 0;if(p&4){memcpy(stats,edit->before,6);*sex=edit->sexBefore;edit->mode=0;return 1;}if(p&2){edit->mode=0;return 1;}if(edit->mode==1){if(p&(1024|2048|4096|8192))*field=1+front_spatial265(frontStatPoints58,6,*field-1,p);else if(p&8)front_stat_adjust58(stats,*field-1,1);else if(p&16)front_stat_adjust58(stats,*field-1,-1);}else if(p&(4096|8192))*sex=!*sex;return 1;}
#endif
