/* MIT. Content-sized dialogue and non-overlapping source answer choices. */
#ifndef MYRO_NPC_DIALOGUE_LAYOUT172_H
#define MYRO_NPC_DIALOGUE_LAYOUT172_H
#define NPC_DIALOGUE_ROWS55 11u
#define NPC_DIALOGUE_LINE172 14u
#include "dialogue_font64.h"
#include "npc_dialogue55.h"
#include "npc_text55.h"
static unsigned npc_text_width_native55(void*context,unsigned c){(void)context;if(c>=256&&c<270)return 14;if(c<32||c>127)c='?';return dialogueWidths64[c-32];}
static unsigned npc_line_width172(const char*text){NpcTextCursor55 c={text,0,text,1};unsigned longest=0,width=0,ch;while((ch=npc_text_next55(&c))){if(ch=='\n'){if(width>longest)longest=width;width=0;}else width+=npc_text_width_native55(NULL,ch=='\t'?' ':ch);}return width>longest?width:longest;}
static unsigned npc_choice_width55(const NpcDialogue55*d){unsigned width=140;for(unsigned i=0;i<d->count;i++){unsigned n=npc_line_width172(d->options+d->offsets[i])+24;if(n>width)width=n;}return width>300?300:width;}
static unsigned npc_choice_row55(const NpcDialogue55*d,unsigned width){unsigned lines=1;for(unsigned i=0;i<d->count;i++){unsigned n=npc_text_icons64(d->options+d->offsets[i],width-20,0,0,npc_text_width_native55,NULL,NULL);if(n>lines)lines=n;}if(lines>8)lines=8;return lines==1?20:lines*NPC_DIALOGUE_LINE172+2;}

typedef struct{int x,y,width,height,textX,textY,textWidth,footerY;unsigned rows,lines,maxScroll;int choiceX,choiceY;unsigned choiceWidth,choiceRow,choiceVisible,choiceHeight;}NpcDialogueLayout172;
static NpcDialogueLayout172 npc_dialogue_layout172(const NpcDialogue55*d,const char*title){NpcDialogueLayout172 l={0};unsigned width=npc_line_width172(d->text)+24,titleWidth=npc_line_width172(title?title:"")+30;if(width<titleWidth)width=titleWidth;if(width<240)width=240;if(width>360)width=360;l.x=24;l.width=(int)width;
 if(d->count&&(d->mode==N55_DIALOGUE_SELECT||d->mode==N55_DIALOGUE_PROMPT)){l.choiceWidth=npc_choice_width55(d);l.choiceX=624-(int)l.choiceWidth;int space=l.choiceX-8-l.x;if(space>=240&&l.width>space)l.width=space;l.choiceRow=npc_choice_row55(d,l.choiceWidth);l.choiceVisible=d->count<8?d->count:8;unsigned maximum=(436-12)/l.choiceRow;if(l.choiceVisible>maximum)l.choiceVisible=maximum;l.choiceHeight=l.choiceVisible*l.choiceRow+12;}
 l.textWidth=l.width-24;l.lines=npc_text_icons64(d->text,(unsigned)l.textWidth,0,0,npc_text_width_native55,NULL,NULL);l.rows=l.lines<NPC_DIALOGUE_ROWS55?l.lines:NPC_DIALOGUE_ROWS55;if(l.rows<2)l.rows=2;l.maxScroll=l.lines>l.rows?l.lines-l.rows:0;l.height=26+(int)l.rows*NPC_DIALOGUE_LINE172+25;l.y=440-l.height;l.textX=l.x+12;l.textY=l.y+22;l.footerY=l.y+l.height-19;l.choiceY=440-(int)l.choiceHeight;if(l.choiceHeight&&l.x+l.width+8>l.choiceX){unsigned maximum=(unsigned)(l.y-8-4-12)/l.choiceRow;if(!maximum)maximum=1;if(l.choiceVisible>maximum)l.choiceVisible=maximum;l.choiceHeight=l.choiceVisible*l.choiceRow+12;l.choiceY=l.y-8-(int)l.choiceHeight;}if(l.choiceY<4)l.choiceY=4;return l;}
#endif
