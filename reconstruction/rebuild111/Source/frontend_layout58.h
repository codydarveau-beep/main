/* MIT. Pixel coordinates from the original 576x342 client backgrounds. */
#ifndef MYRO_FRONTEND_LAYOUT58_H
#define MYRO_FRONTEND_LAYOUT58_H
static int front_slot_x58(unsigned slot){return 92+(int)(slot%3)*163;}
static int front_slot_shadow58(unsigned slot){return 156+(int)(slot%3)*163;}
static const unsigned char frontOpposite58[6]={3,5,4,0,2,1};
enum{FRONT_STAT_X112=511,FRONT_STAT_Y112=198};
static const short frontStatPoints58[6][2]={{511,136},{566,167},{566,229},{511,260},{456,167},{456,229}};
static int front_stat_adjust58(unsigned char stats[6],unsigned stat,int delta){if(stat>=6)return 0;int n=stats[stat]+delta;if(n<1||n>9)return 0;stats[stat]=(unsigned char)n;stats[frontOpposite58[stat]]=(unsigned char)(10-n);return 1;}
#endif
