/* MIT. Hand-authored compass pixel glyphs; use verified empty shared-atlas cells.
 * No additional texture, allocation, filtering, or per-pixel draw commands. */
#ifndef MYRO_COMPASS_ART200_H
#define MYRO_COMPASS_ART200_H
#include "compass_letters200.h"
#define COMPASS_ART_X200 128
#define COMPASS_ART_Y200 1840
static const char*const compass_rose200[]={".....ddddd.....","...ddrrlrrdd...","..drlhhhlrrrd..",".drlhrrrrhlrrd.",".drhrddrrrhlrd.","drlhrllldrhrlrd","drhrldhldrrhrd.","drlrrdllrrhlrd.",".drlhrrrhlrrd..","..drrlllrrdd...","...ddrrrdd.....","..gg.gdg.gg....",".gGLggdgGLg....","..gGLgdGLg.....","...gggdgg......"};
static const char*const compass_flower200[]={"....ooo....","...owHwo...",".ooowHwooo.","owwwowowwwo","oHHwoYowHHo","owwoYyYowwo",".ooowYwooo.","...owwwo...","..ggowogg..",".gGLggGLg..","..gg..gg..."};
static const char*const compass_leaf200[]={"..gg...",".gGLg..","gGLLLg.",".gGLg..","..gg..."};
static unsigned compass_color200(char c){switch(c){case '.':return 0x00000000u;case 'd':return 0xff48252bu;case 'r':return 0xffa62d43u;case 'l':return 0xffd64859u;case 'h':return 0xffff8890u;case 'o':return 0xff655341u;case 'w':return 0xffe9dabcu;case 'H':return 0xfffff3d8u;case 'Y':return 0xffdfb44fu;case 'y':return 0xff987131u;case 'g':return 0xff293f32u;case 'G':return 0xff55754bu;case 'L':return 0xff9caf69u;default:return 0;}}
static void compass_art_init200(unsigned char*bytes){
 unsigned*p=(unsigned*)bytes;
 for(unsigned y=0;y<16;y++)for(unsigned x=0;x<112;x++)if(p[(COMPASS_ART_Y200+y)*512+COMPASS_ART_X200+x])fail("Compass atlas cells occupied");
 for(unsigned glyph=0;glyph<3;glyph++){
  const char*const*rows=glyph==0?compass_rose200:glyph==1?compass_flower200:compass_leaf200;
  unsigned h=glyph==0?15:glyph==1?11:5,w=glyph==0?15:glyph==1?11:7,x0=COMPASS_ART_X200+glyph*16;
  /* All glyphs retain their own dark outline and a one-pixel soft shadow. */
  for(unsigned y=0;y<h;y++)for(unsigned x=0;x<w;x++)if(compass_color200(rows[y][x])&&x+1<16&&y+1<16)p[(COMPASS_ART_Y200+y+1)*512+x0+x+1]=0x60000000;
  for(unsigned y=0;y<h;y++)for(unsigned x=0;x<w;x++){unsigned c=compass_color200(rows[y][x]);if(c)p[(COMPASS_ART_Y200+y)*512+x0+x]=c;}
 }
 /* Five compass ring shades occupy previously empty protected palette cells. */
 static const unsigned shades200[]={0xff241d1b,0xffbd8c3e,0xfff4d47a,0xff78532e,0xffffe6a2};
 for(unsigned i=0;i<5;i++)for(unsigned y=0;y<8;y++)for(unsigned x=0;x<8;x++){
  unsigned at=(264+y)*512+248+i*8+x;if(p[at])fail("Compass palette cells occupied");p[at]=shades200[i];
 }
 compass_letters_init200(p);
}
#endif
