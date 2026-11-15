/* MIT. Preview rotation never changes the player's world-facing direction. */
#ifndef MYRO_PREVIEW_TURN191_H
#define MYRO_PREVIEW_TURN191_H
#include <math.h>
typedef struct{unsigned direction;int held,open;float repeat,left,right;}PreviewTurn191;
static PreviewTurn191 stylistTurn191,creationTurn191;
static void preview_turn191(PreviewTurn191*p,float axis,float dt,int open){if(!open){memset(p,0,sizeof(*p));return;}if(!p->open){memset(p,0,sizeof(*p));p->open=1;}if(dt<0)dt=0;if(dt>.05f)dt=.05f;int turn=axis<-.4f?-1:axis>.4f?1:0;float step=dt/.05f;p->left+=turn<0?step:-step;p->right+=turn>0?step:-step;p->left=fmaxf(0,fminf(1,p->left));p->right=fmaxf(0,fminf(1,p->right));if(turn!=p->held){p->held=turn;p->repeat=0;if(turn)p->direction=(p->direction+(turn>0?1:7))%8;}else if(turn){p->repeat+=dt;while(p->repeat>=.18f){p->repeat-=.18f;p->direction=(p->direction+(turn>0?1:7))%8;}}}
#endif
