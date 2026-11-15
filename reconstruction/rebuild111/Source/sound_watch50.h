/* MIT. Poll policy shared by the native worker and DMA fault-injection checks. */
#ifndef MYRO_SOUND_WATCH50_H
#define MYRO_SOUND_WATCH50_H
enum { SOUND_AHEAD50=4, SOUND_BAD_QUEUE50=33 };
typedef struct {unsigned cursor,last,flags,pending;} SoundSnapshot50;
typedef struct {unsigned cursor,progressAt,badAt;int initialized,bad;} SoundWatch50;
static SoundSnapshot50 sound_snapshot50(unsigned submitted,unsigned word){
 SoundSnapshot50 s={word&31,(word>>8)&31,(word>>16)&255,0};
 if(!submitted)return s;
 if(s.last!=((submitted-1)&31)){s.pending=SOUND_BAD_QUEUE50;return s;}
 s.pending=sound_pending(submitted,s.cursor,s.flags);
 if(s.pending>SOUND_AHEAD50||(s.flags&1)&&s.cursor!=s.last)s.pending=SOUND_BAD_QUEUE50;
 return s;
}
static int sound_recover_needed50(SoundWatch50*w,SoundSnapshot50 s,unsigned now){
 /* A hardware FIFO error can produce corrupt output while CIV still advances. */
 if(s.flags&0x10u)return 1;
 if(!w->initialized){w->cursor=s.cursor;w->progressAt=now;w->initialized=1;}
 if(s.cursor!=w->cursor){w->cursor=s.cursor;w->progressAt=now;}
 if(!s.pending){w->bad=0;w->progressAt=now;return 0;}
 if(s.pending==SOUND_BAD_QUEUE50){
  if(!w->bad){w->bad=1;w->badAt=now;}
  return (unsigned)(now-w->badAt)>=20;
 }
 w->bad=0;
 return (unsigned)(now-w->progressAt)>=250;
}
#endif
