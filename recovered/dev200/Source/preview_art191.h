/* MIT. Native-size curved rotation arrows and analogue stick in shared HUD cells. */
#ifndef MYRO_PREVIEW_ART191_H
#define MYRO_PREVIEW_ART191_H
static void preview_art_init191(unsigned char*bytes){unsigned*p=(unsigned*)bytes;
 for(unsigned y=0;y<16;y++)for(unsigned x=240;x<400;x++)if(p[(1840+y)*512+x])fail("Preview cue atlas cells occupied");
 for(unsigned shade=0;shade<4;shade++)for(int y=0;y<16;y++)for(int x=0;x<32;x++){
  float dx=(x-16)/13.f,dy=(y-7)/5.f,d=dx*dx+dy*dy;int arc=y>=7&&d>.58f&&d<1.4f,tip=x>=1&&x<=9&&y>=3&&y<=10&&x-1<=10-y;
  if(!arc&&!tip)continue;unsigned gain=100-shade*7,red=(unsigned)(160-y*6)*gain/100,green=(unsigned)(215-y*4)*gain/100,blue=(unsigned)(255-y*2)*gain/100;p[(1840+y)*512+240+shade*32+x]=0xff000000|(red<<16)|(green<<8)|blue;
 }
 for(int y=0;y<16;y++)for(int x=0;x<32;x++){float dx=(x-16)/10.f,dy=(y-11)/4.f;unsigned c=dx*dx+dy*dy<=1?0xff313947:0;if(x>=12&&x<=20&&y>=5&&y<=11)c=0xff8999b2;float kx=(x-16)/6.f,ky=(y-5)/4.f;if(kx*kx+ky*ky<=1)c=y<5?0xffeaf0f5:0xff8999b2;if(c)p[(1840+y)*512+368+x]=c;}
}
#endif
