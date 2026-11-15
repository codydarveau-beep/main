/* Shared stylist/creation cue: 50ms fade and centred5% size change. */
static void preview_hint191(const PreviewTurn191*p,int cx,int y){
 hud_setup(skinTexture,512,SKIN_H,2048,0x0001122a,1);
 for(unsigned side=0;side<2;side++){float f=side?p->right:p->left,scale=1+.05f*f,w=32*scale,h=16*scale,x=cx+(side?43:-43)-w*.5f;unsigned shade=(unsigned)(f*3+.5f);hud_quad(x,y+(16-h)*.5f,w,h,240+shade*32+(side?32:0),1840,side?-32:32,16);}
 hud_quad(cx-16,y,32,16,368,1840,32,16);
 const char*label="ROTATE PREVIEW";int x=cx-ui_text_width(label,1)/2;ui_scaled(x,y+20,1,"%s",label);ui_scaled(x+1,y+20,1,"%s",label);
}
