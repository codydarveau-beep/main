/* MIT. UI copies use original ACT attachment coordinates, without world depth. */
#ifndef MYRO_HEADGEAR_UI180_H
#define MYRO_HEADGEAR_UI180_H
static void head_ui_draw180(HeadPose54 pose,float x,float y,float scale){for(unsigned i=0;i<3;i++){const HeadCache54*c=headCache54+i;if(!c->raw||c->frame>=c->frames||!c->texture)continue;const unsigned*d=c->directory+c->frame*8;hud_setup_direct(c->texture,d[2],d[3],(d[2]*2+63)&~63u,0x00011d2a,1);hud_quad(x+(pose.x+(int32_t)d[0])*scale,y+(pose.y-10+(int32_t)d[1])*scale,d[2]*scale,d[3]*scale,0,0,d[2],d[3]);}}
static void head_paper_doll180(SparseSprite*s,unsigned frame,HeadPose54 pose,int x,int y,int width,int height){
 unsigned bounds[4];appearance_bounds58(s,frame,0,bounds);if(bounds[2]<=bounds[0]||bounds[3]<=bounds[1])return;
 float left=bounds[0],top=bounds[1],right=bounds[2],bottom=bounds[3];
 for(unsigned i=0;i<3;i++){const HeadCache54*c=headCache54+i;if(!c->raw||c->frame>=c->frames)continue;const unsigned*d=c->directory+c->frame*8;float xx=(float)s->anchorX+pose.x+(int32_t)d[0],yy=(float)s->anchorY+pose.y-10+(int32_t)d[1];left=fminf(left,xx);top=fminf(top,yy);right=fmaxf(right,xx+d[2]);bottom=fmaxf(bottom,yy+d[3]);}
 float scale=.7f*fminf(width/(right-left),height/(bottom-top));float fx=x+(width-(right-left)*scale)*.5f+(s->anchorX-left)*scale,fy=y+(height-(bottom-top)*scale)*.5f+(s->anchorY-top)*scale;
 hud_setup_direct(entityTextures[0],128,s->h,128*s->bytesPerPixel,s->bytesPerPixel==2?0x0001102a:0x0001122a,1);hud_quad(fx+((float)bounds[0]-s->anchorX)*scale,fy+((float)bounds[1]-s->anchorY)*scale,(bounds[2]-bounds[0])*scale,(bounds[3]-bounds[1])*scale,bounds[0],bounds[1],bounds[2]-bounds[0],bounds[3]-bounds[1]);head_ui_draw180(pose,fx,fy,scale);
}
typedef struct{void*texture;int x,y;unsigned width,height,pitch;}FrontHead180;
static void front_head_clear180(FrontHead180*h){if(h->texture)MmFreeContiguousMemory(h->texture);memset(h,0,sizeof(*h));}
static HeadPose54 front_head_pose180(unsigned variant,unsigned at){HeadPose54 pose={0};if(variant>=ACTOR_VARIANTS)return pose;const unsigned*d=headPoseDefs54[variant];if(d[2]%10||at>=d[2]/10||d[2]>81920||d[0]>sizeof(headPoseData54)||d[1]>sizeof(headPoseData54)-d[0]||crc32(0,headPoseData54+d[0],d[1])!=d[3])return pose;unsigned char*raw=inflateasset("preview head anchors",headPoseData54+d[0],d[1],d[2]);const unsigned char*p=raw+at*10;int16_t x,y;uint16_t action,frame,count;memcpy(&x,p,2);memcpy(&y,p+2,2);memcpy(&action,p+4,2);memcpy(&frame,p+6,2);memcpy(&count,p+8,2);pose=(HeadPose54){x,y,action,frame,count};free(raw);return pose;}
static void front_head_load180(FrontHead180*out,unsigned view,unsigned sex,HeadPose54 pose){
 front_head_clear180(out);const unsigned*def=head_definition54(view,sex);if(!def)return;HeadCache54 cache={0};head_load54(&cache,def);unsigned frame=head_frame180(&cache,pose,0);const unsigned*d=cache.directory+frame*8;const unsigned char*cp=cache.packedFrames+d[4]-cache.packedBase;if(crc32(0,cp,d[5])!=d[7])fail("Preview headgear checksum mismatch");unsigned char*raw=inflateasset("preview headgear",cp,d[5],d[6]);unsigned pitch=(d[2]*2+63)&~63u;out->texture=gpu_alloc(pitch*d[3]);out->x=pose.x+(int32_t)d[0];out->y=pose.y-10+(int32_t)d[1];out->width=d[2];out->height=d[3];out->pitch=pitch;for(unsigned y=0;y<d[3];y++)memcpy((unsigned char*)out->texture+y*pitch,raw+y*d[2]*2,d[2]*2);free(raw);head_clear_one54(&cache);
}
static void front_head_draw180(const FrontHead180*h,float x,float y){if(!h->texture)return;hud_setup_direct(h->texture,h->width,h->height,h->pitch,0x00011d2a,1);hud_quad(x+h->x,y+h->y,h->width,h->height,0,0,h->width,h->height);}
#endif
