/* MIT. Preserve GPU frame slots when nearest-visible ordering changes. */
#ifndef MYRO_SPRITE_SLOTS45_H
#define MYRO_SPRITE_SLOTS45_H
typedef struct {int ready,owners[32];unsigned life[32],map;} SpriteSlots45;
static void sprite_slots45(SpriteSlots45*s,unsigned map,const int*ids,const unsigned*life,int n,int*out){if(!s->ready||s->map!=map){for(int i=0;i<32;i++)s->owners[i]=-1;s->map=map;s->ready=1;}for(int i=0;i<n;i++){int at=-1;for(int k=0;k<32;k++)if(s->owners[k]==ids[i]&&s->life[k]==life[i]){at=k;break;}if(at<0)for(int k=0;k<32;k++){int keep=0;for(int j=0;j<n;j++)if(s->owners[k]==ids[j]&&s->life[k]==life[j]){keep=1;break;}if(!keep){at=k;break;}}if(at<0)at=0;s->owners[at]=ids[i];s->life[at]=life[i];out[i]=at+1;}}
#endif
