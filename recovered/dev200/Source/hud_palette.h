/* MIT. Interior coordinates keep linear filtering fully opaque. */
static void hud_solid_uv(unsigned index,float*u,float*v){*u=SKIN_PALETTE_X+(index%64)*8+3.0f;*v=SKIN_PALETTE_Y+(index/64)*8+3.0f;}
