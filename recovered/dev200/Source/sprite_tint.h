/* MIT. Tint only uploaded sprite pixels; source frames and alpha stay intact. */
static void sprite_green(void*buffer,unsigned pixels,unsigned bpp){unsigned char*dest=buffer;if(bpp==2){unsigned short*q=(unsigned short*)dest;for(unsigned i=0;i<pixels;i++){unsigned v=q[i];if(v&0x8000)q[i]=(v&0x8000)|(((v>>10&31)*2/5)<<10)|((((v>>5&31)*3+31)/4)<<5)|((v&31)*2/5);}}else{unsigned*q=(unsigned*)dest;for(unsigned i=0;i<pixels;i++){unsigned v=q[i];q[i]=(v&0xff000000)|(((v>>16&255)*2/5)<<16)|((((v>>8&255)*3+255)/4)<<8)|((v&255)*2/5);}}}

/* Keep alpha and source frames unchanged; only the cached upload is iced. */
static void sprite_ice(void*buffer,unsigned pixels,unsigned bpp){if(bpp==2){uint16_t*p=buffer;for(unsigned i=0;i<pixels;i++){unsigned v=p[i];if(v&0x8000)p[i]=0x8000|(((v>>10&31)*2/5)<<10)|(((v>>5&31)+31)/2<<5)|((v&31)+93)/4;}}else{uint32_t*p=buffer;for(unsigned i=0;i<pixels;i++){unsigned v=p[i];p[i]=(v&0xff000000)|(((v>>16&255)*2/5)<<16)|(((v>>8&255)+255)/2<<8)|((v&255)+765)/4;}}}

/* Owner-only ghost: binary-alpha sprites use a stable 50% screen-door pattern. */
static void sprite_hide(void*buffer,unsigned pixels,unsigned bpp){if(bpp==2){uint16_t*p=buffer;for(unsigned i=0;i<pixels;i++)if((i^(i/128))&1)p[i]&=0x7fff;}else{uint32_t*p=buffer;for(unsigned i=0;i<pixels;i++)if((i^(i/128))&1)p[i]&=0x00ffffff;}}

/* Stone uses greyscale in the existing upload buffer; preserves alpha/source. */
static void sprite_stone(void*buffer,unsigned pixels,unsigned bpp){if(bpp==2){uint16_t*p=buffer;for(unsigned i=0;i<pixels;i++){unsigned v=p[i];if(v&0x8000){unsigned a=((v>>10&31)+(v>>5&31)+(v&31))/3;p[i]=(v&0x8000)|(a<<10)|(a<<5)|a;}}}else{uint32_t*p=buffer;for(unsigned i=0;i<pixels;i++){unsigned v=p[i],a=((v>>16&255)+(v>>8&255)+(v&255))/3;p[i]=(v&0xff000000)|(a<<16)|(a<<8)|a;}}}

/* Subtle steady blue coating; preserves source/alpha and costs no new texture. */
static void sprite_coat(void*buffer,unsigned pixels,unsigned bpp){if(bpp==2){uint16_t*p=buffer;for(unsigned i=0;i<pixels;i++){unsigned v=p[i];if(v&0x8000)p[i]=0x8000|(((v>>10&31)*7/8)<<10)|((((v>>5&31)*7+31)/8)<<5)|(((v&31)*3+31)/4);}}else{uint32_t*p=buffer;for(unsigned i=0;i<pixels;i++){unsigned v=p[i];p[i]=(v&0xff000000)|(((v>>16&255)*7/8)<<16)|((((v>>8&255)*7+255)/8)<<8)|(((v&255)*3+255)/4);}}}

/* Four-bit alpha creature frames preserve source fade while composing statuses. */
static void sprite_tint4444_45(void*buffer,unsigned pixels,int ice,int stone,int poison){uint16_t*p=buffer;for(unsigned i=0;i<pixels;i++){unsigned v=p[i],r=v>>8&15,g=v>>4&15,b=v&15;if(ice){r=r*2/5;g=(g+15)/2;b=(b+45)/4;}if(stone)r=g=b=(r+g+b)/3;if(poison){r=r*2/5;g=(g*3+15)/4;b=b*2/5;}p[i]=(v&0xf000)|(r<<8)|(g<<4)|b;}}

/* Original-style warm Quicken colouring / low-HP Provoke feedback. */
static void sprite_warm45(void*buffer,unsigned pixels,int red){uint16_t*p=buffer;for(unsigned i=0;i<pixels;i++){unsigned v=p[i];if(v&0x8000){unsigned r=v>>10&31,g=v>>5&31,b=v&31;if(red){r=(r+31)/2;g/=2;b/=3;}else{r=(4*r+31)/5;g=(4*g+31)/5;b=b*11/15;}p[i]=0x8000|(r<<10)|(g<<5)|b;}}}

/* Stave Crasher source EF380: transient target body colour, retain all alpha. */
static void sprite_flash49(void*buffer,unsigned pixels,unsigned bpp,int alpha4444,unsigned color){unsigned cr=color>>16&255,cg=color>>8&255,cb=color&255;if(bpp==2){uint16_t*p=buffer;for(unsigned i=0;i<pixels;i++){unsigned v=p[i];if(alpha4444){unsigned r=v>>8&15,g=v>>4&15,b=v&15;p[i]=(v&0xf000)|((r*cr/255)<<8)|((g*cg/255)<<4)|(b*cb/255);}else{unsigned r=v>>10&31,g=v>>5&31,b=v&31;p[i]=(v&0x8000)|((r*cr/255)<<10)|((g*cg/255)<<5)|(b*cb/255);}}}else{uint32_t*p=buffer;for(unsigned i=0;i<pixels;i++){unsigned v=p[i];p[i]=(v&0xff000000)|(((v>>16&255)*cr/255)<<16)|(((v>>8&255)*cg/255)<<8)|((v&255)*cb/255);}}}
