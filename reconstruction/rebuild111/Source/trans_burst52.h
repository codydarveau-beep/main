/* Original EF366/377/399/400: alpha_center sectors, two radii,175ms.
 * Pure timing helper keeps the caster flash and the authored burst in step. */
#ifndef MYRO_TRANS_BURST52_H
#define MYRO_TRANS_BURST52_H
static int trans_burst_count52(unsigned id,float age,float*phase){float delay;int count;if(id==SK60_GS_DUST){delay=0;count=6;}else if(id==SK52_PA_SACRIFICE){delay=.2f;count=5;}else if(id==SK52_CH_TIGERFIST){delay=.05f;count=8;}else if(id==SK52_LK_HEADCRUSH||id==SK52_LK_JOINTBEAT){delay=.5f;count=6;}else return 0;float t=age-delay;if(t<0||t>=.175f)return 0;*phase=t/.175f;return count;}
static unsigned trans_flash52(unsigned id,float age){if(age<0)return 0;if(id==SK52_CH_TIGERFIST)return age>=.05f&&age<=.35f?0xff6464u:0;if(id==SK52_PA_SACRIFICE)return age>=.15f&&age<=.45f?0xffc8c8u:0;if(id==SK52_LK_HEADCRUSH&&age<.5f){float blue=age<.2f?(205-1000*age)/255.f:5/255.f+(age-.2f)/.3f*(250/255.f);if(blue<0)blue=0;if(blue>1)blue=1;return 0xffff00u|(unsigned)(blue*255);}return 0;}
#endif
