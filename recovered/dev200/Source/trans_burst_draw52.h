/* Source fixed-perspective sectors use the original alpha_center texture.
 * Deterministic seed affects only angles, never the combat random sequence. */
static void trans_burst_draw52(const Combat*g,const Art39State*s,const float*m){int begun=0;float right=sqrtf(m[0]*m[0]+m[1]*m[1]);if(right<.001f)return;float rx=m[0]/right,ry=m[1]/right;
 for(unsigned i=0;i<ART39_EVENTS;i++){const Art39Event*e=s->events+i;float age=g->time-e->at,phase=0;int count=trans_burst_count52(e->skill,age,&phase);if(!count)continue;if(!begun){spell_world_begin41();uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,1);pb_end(p);begun=1;}float x=g->x,y=g->y;if(e->skill==SK52_CH_TIGERFIST){x=e->x;y=e->y;}float z=height_at(x,y)+12;field_bind48(12,(int)(9*field_fade48(phase,1)+.5f),0);
 for(int layer=0;layer<2;layer++)for(int n=0;n<count;n++){float angle=ice_unit48((unsigned)(e->at*1000)+n*31+layer*409)*6.2831853f,end=angle+.20943951f,r=(layer?57.6f:36)*phase;float ca=cosf(angle),sa=sinf(angle),cb=cosf(end),sb=sinf(end);SpellPoint41 q[4]={{x+rx*ca*.08f,y+ry*ca*.08f,z+sa*.08f},{x+rx*ca*r,y+ry*ca*r,z+sa*r},{x+rx*cb*r,y+ry*cb*r,z+sb*r},{x+rx*cb*.08f,y+ry*cb*.08f,z+sb*.08f}};float uv[8]={0,64,0,0,64.f/30,0,64.f/30,64};field_quad48(m,q,uv);}
 }if(begun){uint32_t*p=pb_begin();p=pb_push1(p,NV097_SET_BLEND_FUNC_DFACTOR,0x303);pb_end(p);}
}
