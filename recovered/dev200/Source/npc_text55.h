/* MIT. Word wrapping and original RO dialogue color/link text markup. */
#ifndef MYRO_NPC_TEXT55_H
#define MYRO_NPC_TEXT55_H
#include <stdint.h>
#include <string.h>
#include "controller_tokens64.h"
typedef struct{const char*at;uint32_t rgb;const char*begin64;unsigned icons64;}NpcTextCursor55;
typedef unsigned(*NpcGlyphWidth55)(void*,unsigned);
typedef void(*NpcGlyphDraw55)(void*,unsigned,unsigned,unsigned,uint32_t);
static int npc_text_hex55(unsigned c){return c>='0'&&c<='9'?(int)c-'0':c>='a'&&c<='f'?(int)c-'a'+10:c>='A'&&c<='F'?(int)c-'A'+10:-1;}
/* Item/navigation labels remain visible; INFO payload and tags are not prose. */
static unsigned npc_text_next55(NpcTextCursor55*c){for(;;){const char*p=c->at;if(!*p)return 0;if(c->icons64){if(!c->begin64)c->begin64=p;unsigned length64=0;int icon64=(p==c->begin64||p[-1]==' '||p[-1]=='/'||p[-1]=='(')?ui_button_token64(c->begin64,p,&length64):-1;if(icon64>=0){c->at+=length64;return 256+(unsigned)icon64;}}if(*p=='^'&&strlen(p)>=7){uint32_t color=0;unsigned i;for(i=1;i<=6;i++){int v=npc_text_hex55((unsigned char)p[i]);if(v<0)break;color=(color<<4)|(unsigned)v;}if(i==7){c->rgb=color;c->at+=7;continue;}}
 if(!strncmp(p,"<INFO>",6)){const char*end=strstr(p+6,"</INFO>");if(end){c->at=end+7;continue;}}
 static const char*const tags[]={"<ITEM>","</ITEM>","<URL>","</URL>","<NAVI>","</NAVI>"};int tag=0;for(unsigned i=0;i<sizeof(tags)/sizeof(*tags);i++){size_t n=strlen(tags[i]);if(!strncmp(p,tags[i],n)){c->at+=n;tag=1;break;}}if(tag)continue;
 c->at++;unsigned ch=(unsigned char)*p;if(ch=='\r')continue;if(ch>=128){while(((unsigned char)*c->at&0xc0)==0x80)c->at++;return'?';}return ch;}}
static unsigned npc_text_word_width55(NpcTextCursor55 cursor,NpcGlyphWidth55 width,void*context,unsigned limit){unsigned total=0,ch;while((ch=npc_text_next55(&cursor))&&ch!=' '&&ch!='\t'&&ch!='\n'){unsigned n=width(context,ch);if(total>limit||n>limit-total)return limit+1;total+=n;}return total;}
/* first/maxRows choose a viewport; return value is the full wrapped line count. */
static unsigned npc_text_layout_mode64(const char*text,unsigned maxWidth,unsigned first,unsigned maxRows,NpcGlyphWidth55 width,NpcGlyphDraw55 draw,void*context,unsigned icons64){if(!text||!maxWidth||!width)return 0;NpcTextCursor55 cursor={text,0,text,icons64};unsigned x=0,row=0,ch;int wordStart=1,content=0;
 while(*cursor.at){NpcTextCursor55 before=cursor;ch=npc_text_next55(&cursor);if(!ch)break;if(ch=='\n'){row++;x=0;content=0;wordStart=1;continue;}if(ch=='\t')ch=' ';
 if(wordStart&&ch!=' '){unsigned word=npc_text_word_width55(before,width,context,maxWidth);if(x&&word<=maxWidth&&word>maxWidth-x){row++;x=0;content=0;}}
 unsigned advance=width(context,ch);if(advance>maxWidth)advance=maxWidth;if(x&&advance>maxWidth-x){row++;x=0;content=0;}
 if(ch==' '&&!x){wordStart=1;continue;}if(draw&&row>=first&&row-first<maxRows)draw(context,ch,x,row-first,cursor.rgb);x+=advance;content=1;wordStart=ch==' ';
 }
 return row+(content?1:0);
}
static unsigned npc_text_layout55(const char*t,unsigned w,unsigned f,unsigned r,NpcGlyphWidth55 width,NpcGlyphDraw55 draw,void*c){return npc_text_layout_mode64(t,w,f,r,width,draw,c,0);}
static unsigned npc_text_icons64(const char*t,unsigned w,unsigned f,unsigned r,NpcGlyphWidth55 width,NpcGlyphDraw55 draw,void*c){return npc_text_layout_mode64(t,w,f,r,width,draw,c,1);}
#endif
