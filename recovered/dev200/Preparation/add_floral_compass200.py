from pathlib import Path
S=Path('/workspace/myro/dev200/Source')
rose=[
'.....ddddd.....',
'...ddrrlrrdd...',
'..drlhhhlrrrd..',
'.drlhrrrrhlrrd.',
'.drhrddrrrhlrd.',
'drlhrllldrhrlrd',
'drhrldhldrrhrd.',
'drlrrdllrrhlrd.',
'.drlhrrrhlrrd..',
'..drrlllrrdd...',
'...ddrrrdd.....',
'..gg.gdg.gg....',
'.gGLggdgGLg....',
'..gGLgdGLg.....',
'...gggdgg......']
flower=[
'....ooo....',
'...owHwo...',
'.ooowHwooo.',
'owwwowowwwo',
'oHHwoYowHHo',
'owwoYyYowwo',
'.ooowYwooo.',
'...owwwo...',
'..ggowogg..',
'.gGLggGLg..',
'..gg..gg...']
leaf=['..gg...','.gGLg..','gGLLLg.','.gGLg..','..gg...']
for rows in [rose,flower,leaf]:assert len({len(s)for s in rows})==1
palette={'.':0,'d':0xff48252b,'r':0xffa62d43,'l':0xffd64859,'h':0xffff8890,'o':0xff655341,'w':0xffe9dabc,'H':0xfffff3d8,'Y':0xffdfb44f,'y':0xff987131,'g':0xff293f32,'G':0xff55754b,'L':0xff9caf69}
header='''/* MIT. Hand-authored compass pixel glyphs; use verified empty shared-atlas cells.
 * No additional texture, allocation, filtering, or per-pixel draw commands. */
#ifndef MYRO_COMPASS_ART200_H
#define MYRO_COMPASS_ART200_H
#define COMPASS_ART_X200 128
#define COMPASS_ART_Y200 1840
'''
for name,rows in [('rose',rose),('flower',flower),('leaf',leaf)]:header+=f'static const char*const compass_{name}200[]={{'+','.join('"'+r+'"'for r in rows)+'};\n'
header+='static unsigned compass_color200(char c){switch(c){'+''.join("case '%s':return 0x%08xu;"%(k,v) for k,v in palette.items())+'default:return 0;}}\n'
header+='''static void compass_art_init200(unsigned char*bytes){
 unsigned*p=(unsigned*)bytes;
 for(unsigned y=0;y<16;y++)for(unsigned x=0;x<48;x++)if(p[(COMPASS_ART_Y200+y)*512+COMPASS_ART_X200+x])fail("Compass atlas cells occupied");
 for(unsigned glyph=0;glyph<3;glyph++){
  const char*const*rows=glyph==0?compass_rose200:glyph==1?compass_flower200:compass_leaf200;
  unsigned h=glyph==0?15:glyph==1?11:5,w=glyph==0?15:glyph==1?11:7,x0=COMPASS_ART_X200+glyph*16;
  /* All glyphs retain their own dark outline and a one-pixel soft shadow. */
  for(unsigned y=0;y<h;y++)for(unsigned x=0;x<w;x++)if(compass_color200(rows[y][x])&&x+1<16&&y+1<16)p[(COMPASS_ART_Y200+y+1)*512+x0+x+1]=0x60000000;
  for(unsigned y=0;y<h;y++)for(unsigned x=0;x<w;x++){unsigned c=compass_color200(rows[y][x]);if(c)p[(COMPASS_ART_Y200+y)*512+x0+x]=c;}
 }
}
#endif
'''
(S/'compass_art200.h').write_text(header)
p=S/'window_draw.h';s=p.read_text().replace('#include "skin_data.h"','#include "skin_data.h"\n#include "compass_art200.h"').replace('skinTexture=gpu_alloc(skin_image_raw);','compass_art_init200(p);skinTexture=gpu_alloc(skin_image_raw);');p.write_text(s)
p=S/'minimap_draw.h';s=p.read_text();a=s.index('static void compass_point65');s=s[:a]+'''/* Floral points replace the crossed spears; open centre preserves world visibility. */
static void compass_flower200(int x,int y,int north){int w=north?16:12,h=north?16:12;hud_quad(x-w/2,y-h/2,w,h,COMPASS_ART_X200+(north?0:16),COMPASS_ART_Y200,w,h);}
static void ui_compass61(float yaw){
 if(compassSize60==DISPLAY_OFF60)return;
 int cx,cy,r;compass_layout62(minimapSize60,compassSize60,&cx,&cy,&r);float co=cosf(yaw),si=sinf(yaw);
 compass_ring62(cx+2,cy+3,r+2,5,0x70000000);
 compass_ring62(cx,cy,r+1,5,0xff241d1b);
 compass_ring62(cx,cy,r,3,0xffbd8c3e);
 compass_ring62(cx,cy,r-1,1,0xfff4d47a);
 /* Restrained alternating over/under gold stitches suggest a Nordic braid. */
 for(unsigned k=0;k<24;k++){float a=k*.2617993878f,rad=r-(k&1?0:1);int x=cx+(int)roundf(sinf(a)*rad),y=cy+(int)roundf(cosf(a)*rad);pb_fill(x,y,1,1,k&1?0xff78532e:0xffffe6a2);}
 hud_setup(skinTexture,512,SKIN_H,2048,0x0001122a,1);
 for(int i=0;i<4;i++){
  float dx=i==0?si:i==1?co:i==2?-si:-co,dy=i==0?-co:i==1?si:i==2?co:-si;
  /* A leaf at the foot of each blossom ties it into the gold ring. */
  int lx=cx+(int)roundf(dx*(r-3)),ly=cy+(int)roundf(dy*(r-3));
  hud_quad(lx-3,ly-2,7,5,COMPASS_ART_X200+32,COMPASS_ART_Y200,7,5);
  int fx=cx+(int)roundf(dx*(r+3)),fy=cy+(int)roundf(dy*(r+3));compass_flower200(fx,fy,i==0);
  int x=cx+(int)roundf(dx*(r+(i?20:23))),y=cy+(int)roundf(dy*(r+(i?20:23)));
  hud_quad(x-8,y-8,16,16,(compassSize60==DISPLAY_LARGE60?4+i:i)*16,SKIN_COMPASS_Y62,16,16);
 }
}
''';p.write_text(s)
p=S/'compass_layout62.h';s=p.read_text().replace('(*r+16)','(*r+32)').replace('*r+74','*r+90').replace('+*r+16','+*r+32');p.write_text(s)
