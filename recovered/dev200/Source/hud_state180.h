/* MIT. HUD rendering must not inherit additive/tinted world-effect state. */
#ifndef MYRO_HUD_STATE180_H
#define MYRO_HUD_STATE180_H
static uint32_t*hud_state180(uint32_t*p,int blend){
 for(int i=0;i<16;i++)p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_FORMAT+i*4,2);
 p=pb_push1(p,NV097_SET_CULL_FACE_ENABLE,0);p=pb_push1(p,NV097_SET_DEPTH_TEST_ENABLE,0);p=pb_push1(p,NV097_SET_DEPTH_MASK,0);p=pb_push1(p,NV097_SET_ALPHA_TEST_ENABLE,0);p=pb_push1(p,NV097_SET_BLEND_ENABLE,blend);
 p=pb_push1(p,NV097_SET_BLEND_FUNC_SFACTOR,0x302);p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,0x303);p=pb_push1(p,NV097_SET_BLEND_EQUATION,0x8006);
 p=pb_push1(p,NV097_SET_COMBINER_SPECULAR_FOG_CW0,8);p=pb_push1(p,NV097_SET_COMBINER_SPECULAR_FOG_CW1,0x1800);return p;
}
#endif
