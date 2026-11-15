/* Designer-confirmed passages. Unretained coordinates are reconstructed and
 * collision-checked; geometry and authored scene placements remain unchanged. */
#ifndef MYRO_STORY_ROUTES199_H
#define MYRO_STORY_ROUTES199_H
static int campaign_story_gate_visible199(unsigned gate){if(gate<STORY_GATE_START199)return 1;if(gate>=STORY_GATE_START199+4)return 0;Campaign200 c;if(!questPins65||campaign_load200(questPins65,&c)!=1)return 0;return c.cursor>=(gate<STORY_GATE_START199+2?28:32);}
static int campaign_story_gate_open199(unsigned gate){if(gate<STORY_GATE_START199)return 1;if(!campaign_story_gate_visible199(gate))return 0;unsigned route=gate-STORY_GATE_START199;if(route==1||route==3)return 1;Campaign200 c;if(campaign_load200(questPins65,&c)!=1)return 0;if(route==0)return c.cursor>28||(c.cursor==28&&(c.objectives&(1u<<2)));return c.cursor>=33;}
#endif
