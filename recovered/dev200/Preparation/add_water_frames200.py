from pathlib import Path
S=Path('/workspace/myro/dev200/Source')
def edit(n,a,b):
 p=S/n;s=p.read_text();assert a in s,(n,a);p.write_text(s.replace(a,b))
edit('water_mode190.h','static unsigned waterOriginal190;','''static unsigned waterOriginal190,waterAnimation200;
#define WATER_ANIMATION_COUNT200 9u
static const unsigned waterFrameCounts200[9]={32,28,24,20,16,12,8,4,1};
static const char*waterFrameNames200[9]={"Full Frames","7/8 Frames","6/8 Frames","5/8 Frames","4/8 Frames","3/8 Frames","2/8 Frames","1/8 Frames","Single Frame"};''')
p=S/'water_wave190.h';s=p.read_text().replace('#include "water_data190.h"','#include "water_data190.h"\n#include "water_mode190.h"');a=s.index('static unsigned water_frame190');b=s.index('static float water_corner190',a);s=s[:a]+'''/* Reduced modes hold selected source frames across the original cycle length. */
static unsigned water_frame190(unsigned map,float seconds){const WaterMap190*w=waterSettings190+map;unsigned count=waterFrameCounts200[waterAnimation200<WATER_ANIMATION_COUNT200?waterAnimation200:0];if(count==1)return 0;float phase=fmodf(seconds*60.f/(float)w->animation,32.f);if(phase<0)phase+=32;unsigned step=(unsigned)floorf(phase*count/32.f);if(step>=count)step=count-1;return step*32u/count;}
static float water_sample_time200(unsigned map,float seconds){if(!waterAnimation200||waterAnimation200>=WATER_ANIMATION_COUNT200)return seconds;if(waterAnimation200==8)return 0;float rate=60.f/waterSettings190[map].animation,clock=seconds*rate,cycle=floorf(clock/32.f);return(cycle*32.f+water_frame190(map,seconds))/rate;}
''' +s[b:];s=s.replace('float phase=fmodf(seconds*60.f*w->speed','seconds=water_sample_time200(map,seconds);float phase=fmodf(seconds*60.f*w->speed');p.write_text(s)
edit('pause_ui.h','{5,7,8,10,8,3,4}','{5,7,8,9,8,5,4}')
edit('pause_ui.h','return u->tab==P53_GAMEPLAY||','return (u->tab==P53_TESTING&&u->row>=3)||u->tab==P53_GAMEPLAY||')
edit('pause_ui.h','int max=1,step=1;','int max=1,step=1;if(u->tab==P53_TESTING&&u->row==4)max=8;')
edit('pause_settings61.h','case 9:return waterOriginal190;','')
edit('pause_settings61.h','case 9:waterOriginal190=!!v;break;','')
edit('pause_settings61.h',' if(tab==P53_MESSAGES)return',' if(tab==P53_TESTING)return row==3?waterOriginal190:row==4?waterAnimation200:0;\n if(tab==P53_MESSAGES)return')
edit('pause_settings61.h',' if(tab==P53_MESSAGES){',' if(tab==P53_TESTING){if(row==3)waterOriginal190=!!v;else if(row==4)waterAnimation200=v<9?v:8;return;}\n if(tab==P53_MESSAGES){')
edit('pause_draw.h',',"Water appearance"','')
edit('pause_draw.h','if(row==9)snprintf(value,48,"%s",waterOriginal190?"ORIGINAL":"CURRENT");else if(row==8)','if(row==8)')
edit('pause_draw.h','"Developer tools...","Test travel...","Invincibility"','"Developer tools...","Test travel...","Invincibility","Water appearance","Water animation frames"')
edit('pause_draw.h','if(row==2)snprintf(value,48,"%s",invincible?"ON":"OFF");','if(row==2)snprintf(value,48,"%s",invincible?"ON":"OFF");else if(row==3)snprintf(value,48,"%s",waterOriginal190?"ORIGINAL":"CURRENT");else if(row==4)snprintf(value,48,"%s",waterFrameNames200[waterAnimation200<9?waterAnimation200:0]);')
edit('pause_draw.h','int slider=(u->tab==P53_GAMEPLAY','int slider=(u->tab==P53_TESTING&&i==4)||(u->tab==P53_GAMEPLAY')
edit('pause_draw.h','unsigned position=0;if(u->tab==P53_AUDIO)','unsigned position=0;if(u->tab==P53_TESTING)position=waterAnimation200*100/8;else if(u->tab==P53_AUDIO)')
edit('prefs_format61.h','r[1]>=10?128u','r[1]>=11?2048u:r[1]>=10?128u')
edit('prefs_format61.h','r[1]>10','r[1]>11')
edit('prefs_format61.h','if(r[1]==1){','if(r[1]>=11&&(r[5]>>7)>=9)return 0;if(r[1]==1){')
edit('frontend_prefs56.h','waterOriginal190=r[1]>=10','waterAnimation200=r[1]>=11?r[5]>>7:0;waterOriginal190=r[1]>=10')
edit('frontend_prefs56.h','{0x3650464d,10,','{0x3650464d,11,')
edit('frontend_prefs56.h','(waterOriginal190?64:0))','(waterOriginal190?64:0)|(waterAnimation200<<7))')
