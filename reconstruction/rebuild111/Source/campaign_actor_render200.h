/* MIT. Source actor catalog shares four visible poses; IO stays at frame fence. */
#ifndef MYRO_CAMPAIGN_ACTOR_RENDER200_H
#define MYRO_CAMPAIGN_ACTOR_RENDER200_H
#include "campaign_actor_data200.h"
#include "campaign_follow200.h"
#include "companion_art200.h"
#include "campaign_stage200.h"
#define CAMPAIGN_KIND200 (MERCENARY_KIND180+1)
#define CAMPAIGN_TEXTURE200 (MERCENARY_TEXTURE180+1)
static SparseSprite campaignSprites200[4];
static unsigned campaignPose200[4]={~0u,~0u,~0u,~0u},campaignWanted200[4]={~0u,~0u,~0u,~0u};
static int campaign_art_ready200(void){return CAMPAIGN_OPENING_READY200&&CAMPAIGN_ACTOR_COUNT200>=4u&&CAMPAIGN_ACTOR_BYTES200>0&&CAMPAIGN_FRAME_COUNT200>0;}
static void campaign_actor_free200(unsigned i){unsigned slot=CAMPAIGN_TEXTURE200+i;free(campaignSprites200[i].raw);memset(campaignSprites200+i,0,sizeof(SparseSprite));if(entityTextures[slot])MmFreeContiguousMemory(entityTextures[slot]);entityTextures[slot]=NULL;entityCapacity51[slot]=0;uploadedSource[slot]=NULL;uploadedFrames[slot]=~0u;campaignPose200[i]=campaignWanted200[i]=~0u;}
static void campaign_actor_release200(void){for(unsigned i=0;i<4;i++)campaign_actor_free200(i);}
static void campaign_actor_prepare200(void){for(unsigned i=0;i<4;i++){unsigned frame=campaignWanted200[i];if(frame==~0u){if(campaignSprites200[i].raw||entityTextures[CAMPAIGN_TEXTURE200+i])campaign_actor_free200(i);continue;}if(frame==campaignPose200[i])continue;if(frame>=CAMPAIGN_FRAME_COUNT200)fail("Campaign pose index invalid");unsigned at=campaignFrames200[frame].offset,packed=campaignFrames200[frame].packed,raw=campaignFrames200[frame].raw;if(!packed||packed>70000||raw>70000||at>CAMPAIGN_ACTOR_BYTES200||packed>CAMPAIGN_ACTOR_BYTES200-at)fail("Campaign pose bounds invalid");
#ifdef MYRO_HOST
 const char*path=getenv("MYRO_CAMPAIGN_ACTOR_PATH");if(!path)path="../Campaign/actors.bin";
#else
 const char*path="D:\\campaign.bin";
#endif
 FILE*f=fopen(path,"rb");if(!f)fail("Campaign actor file missing");unsigned char*p=malloc(packed);int ok=p&&!fseek(f,0,SEEK_END)&&ftell(f)==CAMPAIGN_ACTOR_BYTES200&&!fseek(f,at,SEEK_SET)&&fread(p,1,packed,f)==packed;fclose(f);if(!ok){free(p);fail("Campaign actor read failed");}if(crc32(0,p,packed)!=campaignFrames200[frame].crc){free(p);fail("Campaign actor checksum mismatch");}free(campaignSprites200[i].raw);memset(campaignSprites200+i,0,sizeof(SparseSprite));sprite_load(campaignSprites200+i,"Campaign actor pose",p,packed,raw);free(p);campaignPose200[i]=frame;uploadedSource[CAMPAIGN_TEXTURE200+i]=NULL;uploadedFrames[CAMPAIGN_TEXTURE200+i]=~0u;
 }}
/* Source IDs index disc metadata. Slots index only the four reusable textures. */
static void campaign_actor_submit200(const Combat*g,const float*m,float co,float si,float zoom,unsigned slot,unsigned source,float x,float y,float fx,float fy,unsigned group,const CampaignFollower200*member,DrawActor*actors,int*count){
 if(slot>=4||source>=CAMPAIGN_ACTOR_COUNT200)return;
 if(!monster_visible52(npcView64,x-g->x,y-g->y)||!rooms_point181(&interiorRooms181,x,y))return;
 float z=height_at(x,y),sx,sy;world_project(m,x,y,z,&sx,&sy);if(sx< -80||sx>720||sy< -160||sy>560)return;
 unsigned dir=(unsigned)facing(fx,fy,co,si);
 if(member&&member->initialized){if(!member->hp)group=4;else if(g->time<member->castUntil||(g->time<member->attackUntil&&(member->lastSkill==SKILL_HEAL||member->lastSkill==SKILL_HOLY_LIGHT)))group=5;else if(g->time<member->attackUntil)group=2;else if(g->time-member->hurtAt<.24f)group=3;}
 if(group*8+dir>=CAMPAIGN_ACTIONS_PER_ACTOR200)return;
 unsigned index=source*CAMPAIGN_ACTIONS_PER_ACTOR200+group*8+dir,first=campaignActions200[index].first,n=campaignActions200[index].count,ms=campaignActions200[index].ms;
 if(!n||!ms||first>=CAMPAIGN_FRAME_COUNT200||n>CAMPAIGN_FRAME_COUNT200-first)fail("Campaign action bounds invalid");
 unsigned pose=((unsigned)((member?member->elapsed:g->time)*1000.f)/ms)%n;
 if(member&&(group==2||group==5)){float end=group==5&&member->castUntil>member->attackAt?member->castUntil:member->attackUntil,duration=end-member->attackAt,phase=duration>0?(g->time-member->attackAt)/duration:0;pose=(unsigned)(fmaxf(0,fminf(.999f,phase))*n);}
 else if(member&&group==3){pose=(unsigned)(fmaxf(0,g->time-member->hurtAt)*1000.f)/ms;if(pose>=n)pose=n-1;}
 else if(group==4)pose=n-1;
 campaignWanted200[slot]=first+pose;
 float depth=m[8]*x+m[9]*y+m[10]*z+m[11]-WORLD_SPRITE_BIAS;
 actors[*count]=(DrawActor){CAMPAIGN_TEXTURE200+(int)slot,CAMPAIGN_KIND200+(int)slot,0,sx+campaignContact200[source][dir][0]*zoom/3,sy+campaignContact200[source][dir][1]*zoom/3,depth,sy};
 water_actor_mark54(actors+*count,m,x,y,z);(*count)++;
}
static void campaign_actor_collect_ready200(const Combat*g,const float*m,float co,float si,float zoom,DrawActor*actors,int*count,int ready){
 for(unsigned slot=0;slot<4;slot++)campaignWanted200[slot]=~0u;
 if(!ready)return;
 if(campaignRescue200.active){for(unsigned source=0;source<4;source++){float x,y;rescue_position200(&campaignRescue200,source,&x,&y);float fx=1468-x,fy=2780-y;unsigned group=0;if(source==R200_DRIVER){fx=0;fy=campaignRescue200.escort?1:-1;group=campaignRescue200.escort?1:0;}campaign_actor_submit200(g,m,co,si,zoom,source,source,x,y,fx,fy,group,NULL,actors,count);}return;}
 unsigned nextSlot=0;if(campaignStage200.active&&campaignStage200.definition&&campaignStage200.definition->map==g->mapId){const CampaignStageDefinition200*d=campaignStage200.definition;unsigned first=d->cursor==5&&!campaignStageModal200?2:0;for(unsigned i=first;i<d->count&&nextSlot<4;i++){const CampaignStageActor200*a=d->actor+i;campaign_actor_submit200(g,m,co,si,zoom,nextSlot++,a->source,a->x,a->y,d->x-a->x,d->y-a->y,0,NULL,actors,count);}if(d->cursor==5&&campaignStageModal200)return;}
 for(unsigned slot=0;slot<campaignParty200.count&&slot<3&&nextSlot<4;slot++){const CampaignFollower200*member=campaignParty200.members+slot;if(member->id>=19||member->map!=g->mapId)continue;unsigned source=party_actor_source200(campaignCompanions200[member->id].sceneActor,member->job);campaign_actor_submit200(g,m,co,si,zoom,nextSlot++,source,member->x,member->y,member->faceX,member->faceY,member->moving?1:0,member,actors,count);}
}
static void campaign_actor_collect200(const Combat*g,const float*m,float co,float si,float zoom,DrawActor*actors,int*count){campaign_actor_collect_ready200(g,m,co,si,zoom,actors,count,campaign_art_ready200());}
#endif
