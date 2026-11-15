/* MIT. Repeat only explicitly whitelisted numeric controls, after a fresh press. */
typedef struct {unsigned button,context,lastRaw,armed;float held,next;} InputRepeat;
static unsigned input_repeat(InputRepeat*r,unsigned raw,unsigned allowed,unsigned context,float dt){
 unsigned fresh=raw&~r->lastRaw;r->lastRaw=raw;
 if(r->context!=context){r->context=context;r->armed=r->button=0;r->held=0;}
 unsigned b=raw&allowed;
 if(!b||(b&(b-1))){r->armed=r->button=0;r->held=0;return 0;}
 if(fresh&b){r->button=b;r->armed=1;r->held=0;r->next=.4f;return 0;}
 if(!r->armed||b!=r->button)return 0;
 if(dt<0)dt=0;if(dt>.1f)dt=.1f;r->held+=dt;
 if(r->held<r->next)return 0;r->next=r->held+(r->held>1.6f?.04f:r->held>.8f?.07f:.12f);return b;
}
