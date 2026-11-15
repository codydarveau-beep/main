#include "font_sample53.h"
#include "font_metrics65.h"
/* Native10px EXP text; measured from the same atlas as other window text. */
static void ui_exp_text(int x,int y,const char*fmt,...){char line[96];va_list a;va_start(a,fmt);vsnprintf(line,sizeof(line),fmt,a);va_end(a);float xx=x;for(const char*p=line;*p;p++){unsigned c=(unsigned char)*p;if(c<32||c>127)c='?';unsigned k=c-32;if(c!=' ')hud_glyph53(xx,y-3,16*9.f/11.f,16*9.f/11.f,(k%16)*16,(k/16)*16,16,16);xx+=ui_native_advance65(c,9.f/11.f);}}
static int ui_exp_width(const char*s){int width=0;for(;*s;s++)width+=ui_native_advance65((unsigned char)*s,9.f/11.f);return width;}
