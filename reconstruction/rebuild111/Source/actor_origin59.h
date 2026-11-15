/* Restore the established canvas origin before composing hair or uploading.
 * Original actor canvases use origin=anchorY-10:80/100/160. */
#ifndef MYRO_ACTOR_ORIGIN59_H
#define MYRO_ACTOR_ORIGIN59_H
static void actor_origin_correct59(SparseSprite*s){if(!s->appearancePoses58)return;if(s->anchorY<10)fail("Appearance anchor invalid");unsigned origin=s->anchorY-10;
 for(unsigned f=0;f<s->frames;f++){unsigned short*p=(unsigned short*)(s->appearancePoses58+f*12);unsigned old=p[4];if(old==origin)continue;if(old<origin||old-origin>s->h)fail("Appearance origin invalid");unsigned shift=old-origin,*d=s->directory+f*5,cut=d[1]<shift?shift-d[1]:0;if(cut>d[3])cut=d[3];d[4]+=cut*d[2]*s->bytesPerPixel;d[3]-=cut;d[1]=d[1]>=shift?d[1]-shift:0;p[4]=(unsigned short)origin;}
}
#endif
