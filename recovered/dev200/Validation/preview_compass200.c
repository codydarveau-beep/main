#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <zlib.h>
#include "skin_layout.h"
#include "skin_colors.h"
static void fail(const char*s){fprintf(stderr,"%s\n",s);exit(2);}
#include "compass_art200.h"
extern const unsigned char skin_image[];extern const unsigned int skin_image_raw,skin_image_size;
static unsigned *skinTexture,pixels[640*480],minimapSize60=1,compassSize60=1;
enum{DISPLAY_OFF60,DISPLAY_SMALL60,DISPLAY_LARGE60};
static unsigned quads;
static void pixel(int x,int y,unsigned c){if(x<0||x>=640||y<0||y>=480)return;unsigned a=c>>24,b=pixels[y*640+x],out=((a+((b>>24)*(255-a)+127)/255)<<24);for(int n=0;n<3;n++){unsigned shift=n*8,v=(((c>>shift)&255)*a+((b>>shift)&255)*(255-a)+127)/255;out|=v<<shift;}pixels[y*640+x]=out;}
static void pb_fill(int x,int y,int w,int h,unsigned c){int found=0;for(unsigned k=0;k<sizeof(skinColors)/sizeof(*skinColors);k++)found|=skinColors[k]==c;assert(found);for(int j=0;j<h;j++)for(int i=0;i<w;i++)pixel(x+i,y+j,c);}
static void hud_setup(void*p,int w,int h,int pitch,unsigned format,int blend){(void)p;(void)w;(void)h;(void)pitch;(void)format;(void)blend;}
static void hud_quad(int x,int y,int w,int h,int u,int v,int sw,int sh){quads++;assert(u>=0&&v>=0&&u+sw<=512&&v+sh<=2048);for(int j=0;j<h;j++)for(int i=0;i<w;i++)pixel(x+i,y+j,skinTexture[(v+j*sh/h)*512+u+i*sw/w]);}
#include "compass_renderer200.inc"
int main(void){skinTexture=malloc(skin_image_raw);assert(skinTexture);unsigned long n=skin_image_raw;assert(uncompress((void*)skinTexture,&n,skin_image,skin_image_size)==Z_OK);unsigned char *before=malloc(n);memcpy(before,skinTexture,n);compass_art_init200((void*)skinTexture);
 for(unsigned y=0;y<2048;y++)for(unsigned x=0;x<512;x++)if((y<1840||y>=1856||x<128||x>=240)&&(y<264||y>=272||x<248||x>=288))assert(skinTexture[y*512+x]==((unsigned*)before)[y*512+x]);free(before);
 for(unsigned map=0;map<3;map++)for(unsigned size=1;size<=2;size++)for(unsigned a=0;a<64;a++){minimapSize60=map;compassSize60=size;int cx,cy,r;compass_layout62(map,size,&cx,&cy,&r);assert(cx+r+32<=(map==0?626:map==2?470:518)-12);assert(cy-r-32>=top_buttons200(basicInfoRight200,map).bottom+2);for(int k=0;k<640*480;k++)pixels[k]=0xff5b665d;unsigned before=quads;ui_compass61(a*.0981747704f);assert(quads-before==12);assert(pixels[cy*640+cx]==0xff5b665d);}
 /* Native-size comparison sheet: each compass at three orientations. */
 for(int k=0;k<640*480;k++)pixels[k]=0xff5b665d;
 for(unsigned row=0;row<2;row++)for(unsigned a=0;a<3;a++){compassSize60=row+1;minimapSize60=1;int cx,cy,r;compass_layout62(1,row+1,&cx,&cy,&r);unsigned tmp[640*480];memcpy(tmp,pixels,sizeof(tmp));for(int k=0;k<640*480;k++)pixels[k]=0;ui_compass61(a*.7853981634f);int tx=120+a*180,ty=110+row*200;for(int y=-70;y<70;y++)for(int x=-70;x<70;x++){unsigned color=pixels[(cy+y)*640+cx+x];if(color>>24)tmp[(ty+y)*640+tx+x]=color;}memcpy(pixels,tmp,sizeof(tmp));}
 FILE*f=fopen("/workspace/myro/dev200/Validation/compass-floral200.ppm","wb");assert(f);fprintf(f,"P6\n640 480\n255\n");for(unsigned i=0;i<640*480;i++){unsigned c=pixels[i];fputc(c>>16,f);fputc(c>>8,f);fputc(c,f);}fclose(f);free(skinTexture);puts("PASS shared atlas cells isolated; 384 size/map/yaw combinations, transparent centre, layout clearance and 12 atlas quads per compass.");}
