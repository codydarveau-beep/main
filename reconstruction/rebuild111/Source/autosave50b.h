/* MIT. Global autosave preference, independent of character saves. */
#ifndef MYRO_AUTOSAVE50B_H
#define MYRO_AUTOSAVE50B_H
#include <stdint.h>
#include <string.h>
enum {AUTOSAVE_CHOICES50B=7,AUTOSAVE_BYTES50B=24};
static const unsigned autosaveMinutes50b[7]={0,1,3,5,10,15,30};
static const char*autosaveNames50b[7]={"OFF","1 min","3 min","5 min","10 min","15 min","30 min"};
typedef int(*AutosaveRead50b)(void*,int,unsigned char*);
typedef int(*AutosaveWrite50b)(void*,int,const unsigned char*);
typedef struct {unsigned choice,sequence;int newest,writable,pending,sessionOnly;uint32_t changedAt;AutosaveRead50b read;AutosaveWrite50b write;void*ctx;} Autosave50b;
static unsigned autosave_u3250b(const unsigned char*p){return (unsigned)p[0]|(unsigned)p[1]<<8|(unsigned)p[2]<<16|(unsigned)p[3]<<24;}
static void autosave_put50b(unsigned char*p,unsigned v){for(int i=0;i<4;i++)p[i]=(unsigned char)(v>>(i*8));}
static unsigned autosave_crc50b(const unsigned char*p,unsigned n){unsigned c=~0u;for(unsigned i=0;i<n;i++){c^=p[i];for(int j=0;j<8;j++)c=(c>>1)^(0xedb88320u&-(c&1u));}return ~c;}
static void autosave_encode50b(unsigned char*p,unsigned seq,unsigned choice){memcpy(p,"MYROAS01",8);autosave_put50b(p+8,1);autosave_put50b(p+12,seq);autosave_put50b(p+16,choice);autosave_put50b(p+20,autosave_crc50b(p,20));}
static int autosave_decode50b(const unsigned char*p,unsigned*seq,unsigned*choice){if(memcmp(p,"MYROAS01",8)||autosave_u3250b(p+8)!=1)return -1;if(autosave_u3250b(p+20)!=autosave_crc50b(p,20)||!autosave_u3250b(p+12)||autosave_u3250b(p+16)>=7)return 0;*seq=autosave_u3250b(p+12);*choice=autosave_u3250b(p+16);return 1;}
static void autosave_load50b(Autosave50b*s){s->choice=1;s->sequence=0;s->newest=-1;s->writable=1;s->pending=s->sessionOnly=0;for(int i=0;i<2;i++){unsigned char b[24];int state=s->read(s->ctx,i,b);if(!state)continue;if(state<0){s->writable=0;continue;}unsigned seq,choice;int valid=autosave_decode50b(b,&seq,&choice);if(valid<0){s->writable=0;continue;}if(valid&&seq>s->sequence){s->choice=choice;s->sequence=seq;s->newest=i;}}}
static int autosave_change50b(Autosave50b*s,int delta,uint32_t now){int next=(int)s->choice+(delta>0?1:-1);if(next<0)next=0;if(next>=7)next=6;if(next==(int)s->choice)return 0;s->choice=next;s->pending=1;s->changedAt=now;return 1;}
static int autosave_enabled50b(unsigned choice){return choice>0&&choice<7;}
static unsigned autosave_interval50b(unsigned choice){return choice<7?autosaveMinutes50b[choice]*60000u:0;}
static int autosave_due50b(unsigned choice,uint32_t now,uint32_t last){unsigned ms=autosave_interval50b(choice);return ms&&(uint32_t)(now-last)>=ms;}
static int autosave_pending50b(const Autosave50b*s,uint32_t now,int adjusting){return s->pending&&!adjusting&&(uint32_t)(now-s->changedAt)>=350;}
static int autosave_commit50b(Autosave50b*s){s->pending=0;if(!s->writable||s->sequence==UINT32_MAX){s->sessionOnly=1;return 0;}unsigned char b[24],check[24];unsigned seq=s->sequence+1;int target=s->newest<0?0:1-s->newest;autosave_encode50b(b,seq,s->choice);if(!s->write(s->ctx,target,b)||s->read(s->ctx,target,check)!=1||memcmp(b,check,24)){s->sessionOnly=1;return 0;}s->newest=target;s->sequence=seq;s->sessionOnly=0;return 1;}
#endif
