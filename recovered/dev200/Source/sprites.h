/* SPDX-License-Identifier: MIT. Validated sparse SPR/ACT frame container. */
typedef struct EnemyStream51 EnemyStream51;
typedef struct {unsigned w,h,frames,actions,sequenceCount,anchorX,anchorY,pixelBytes;unsigned *meta,*sequence,*directory;unsigned char *pixels,*raw;unsigned bytesPerPixel,alpha4444;const EnemyStream51*stream51;unsigned*blocks51;unsigned guardian51;unsigned char*appearancePoses58,*material58;Appearance58 appearance58;unsigned actor58,sex58;} SparseSprite;

#include "actor_origin59.h"
static SparseSprite sprites[MOB_SPEC_COUNT+1];static unsigned spriteEpoch;
#include "enemy_blobs.h"
static void sprite_set_equipment(unsigned id,unsigned equipment);
static void sprite_load(SparseSprite*s,const char*name,const unsigned char*src,unsigned packed,unsigned size){
 if(size<32||size>16*1024*1024)fail("Sprite size outside bounds");
 unsigned char*p=inflateasset(name,src,packed,size);s->raw=p;memcpy(s,p,32);s->bytesPerPixel=(s->pixelBytes&0x80000000)?2:4;s->alpha4444=(s->pixelBytes>>30)&1;unsigned appearanceFlag58=s->pixelBytes&0x20000000u;s->pixelBytes&=appearanceFlag58?0x1fffffffu:0x3fffffffu;
 if(!((s->w==128&&(s->h==128||s->h==256))||(s->w==256&&s->h==128&&s->alpha4444&&!appearanceFlag58))||s->frames>1024||(s->actions!=40&&s->actions!=48&&s->actions!=56&&s->actions!=64)||s->sequenceCount>8192||s->anchorX>s->w||s->anchorY>s->h)fail("Sprite header mismatch");
 if(s->w*s->h*s->bytesPerPixel>65536)fail("Sprite exceeds GPU slot capacity");
 unsigned bytes=32+s->actions*12+s->sequenceCount*4+s->frames*20;
 if(appearanceFlag58){if(s->bytesPerPixel!=2||s->alpha4444||s->pixelBytes&1)fail("Appearance format invalid");bytes+=s->frames*12+s->pixelBytes/2;}
 if(bytes>size||s->pixelBytes!=size-bytes)fail("Sprite layout mismatch");
 s->meta=(unsigned*)(p+32);s->sequence=s->meta+s->actions*3;s->directory=s->sequence+s->sequenceCount;s->pixels=(unsigned char*)(s->directory+s->frames*5);if(appearanceFlag58){s->appearancePoses58=s->pixels;s->material58=s->pixels+s->frames*12;s->pixels=s->material58+s->pixelBytes/2;}
 for(unsigned i=0;i<s->actions;i++){unsigned*a=s->meta+i*3;if(a[0]>s->sequenceCount||!a[1]||a[1]>s->sequenceCount-a[0]||a[2]<20)fail("Invalid animation sequence");}
 for(unsigned i=0;i<s->sequenceCount;i++)if(s->sequence[i]>=s->frames)fail("Sprite frame index outside bounds");
 for(unsigned i=0;i<s->frames;i++){unsigned*d=s->directory+i*5;if(d[0]>s->w||d[1]>s->h||d[2]>s->w-d[0]||d[3]>s->h-d[1]||d[4]>s->pixelBytes||d[2]*d[3]*s->bytesPerPixel>s->pixelBytes-d[4])fail("Sprite crop outside bounds");}
 actor_origin_correct59(s);
}
#include "enemy_stream51.h"
static void sprite_load_enemy44(unsigned k){
 if(k>=MOB_SPEC_COUNT)fail("Enemy species outside catalog");
#if defined(MYRO_HOST) && !defined(MYRO_DISC_ENEMIES44)
 unsigned art=mob_art_kind55(k);if(art>=50){sprite_stream_load51(k);return;}sprite_load(&sprites[k+1],mobSpecs[k].name,enemyData[art],enemySize[art],enemyRaw[art]);
#else
 sprite_stream_load51(k);
#endif
}

static void sprite_load_all(void){enemy_blob_init();sprite_set_equipment(0,0);}
static void sprite_release_enemies(void){enemy_cache_clear51();for(unsigned i=1;i<=MOB_SPEC_COUNT;i++){free(sprites[i].raw);memset(&sprites[i],0,sizeof(sprites[i]));}spriteEpoch++;}
static void sprite_load_map(unsigned map){
 for(unsigned j=0;j<SPAWN_DEF_COUNT;j++)if(spawnDefs[j].map==map){unsigned k=spawnDefs[j].kind;if(!sprites[k+1].raw)sprite_load_enemy44(k);}
}
/* Keep at most one non-map species for developer testing, never all species. */
static void sprite_test_target(unsigned map,int kind){
#ifndef MYRO_HOST
 while(pb_busy()){}
#endif
 enemy_cache_clear51();for(unsigned k=0;k<MOB_SPEC_COUNT;k++){int needed=(int)k==kind;for(unsigned j=0;j<SPAWN_DEF_COUNT&&!needed;j++)if(spawnDefs[j].map==map&&spawnDefs[j].kind==k)needed=1;
  if(!needed&&sprites[k+1].raw){free(sprites[k+1].raw);memset(&sprites[k+1],0,sizeof(sprites[k+1]));}}
 if(kind>=0&&kind<MOB_SPEC_COUNT&&!sprites[kind+1].raw)sprite_load_enemy44(kind);spriteEpoch++;
}
static unsigned sprite_frame(SparseSprite*s,int group,int dir,float elapsed,float duration,int repeat){
 if(group<0||dir<0||dir>=8||(unsigned)(group*8+dir)>=s->actions)group=dir=0;unsigned*a=s->meta+(group*8+dir)*3;unsigned f=0;if(elapsed<0)elapsed=0;
 if(duration>0){f=(unsigned)(elapsed/duration*a[1]);if(f>=a[1])f=a[1]-1;}
 else if(repeat)f=(unsigned)(elapsed*1000/a[2])%a[1];
 else if(s->stream51==guardianBaked162||s->stream51==guardianBaked162+1){f=(unsigned)(elapsed*1000/a[2]);if(f>=a[1])f=a[1]-1;}
 unsigned frame=s->sequence[a[0]+f];if(s->appearancePoses58){short encoded=((short*)(s->appearancePoses58+frame*12))[5];s->anchorX=64+(encoded>>1);}return frame;
}

#include "actor_disc.h"
static unsigned spriteVariantIndex54=~0u;static unsigned spriteDualGear50;static unsigned spriteJob=~0u,spriteGear=~0u;
static void sprite_set_equipment_sex60(unsigned id,unsigned equipment,unsigned sex){
 if(id>48)fail("Player job outside actor catalog");
unsigned gear=(equipment&(1u<<25))?117:(equipment&(1u<<26))?118:(equipment&(1u<<27))?119:(equipment&(1u<<28))?120:(equipment&(1u<<29))?121:(equipment&(1u<<30))?122:(id==13||id==27)&&spriteDualGear50?spriteDualGear50:(equipment&(1u<<21))?113:(equipment&(1u<<22))?114:(equipment&(1u<<23))?115:(equipment&(1u<<24))?116:((id==1||id==7||id==11||id==12||id==22||id==23||id==40||id==41||id==42)&&(equipment&32))?3:(equipment&16)?2:(equipment&1)?1:(equipment&64)?102:(equipment&128)?104:(equipment&256)?105:(equipment&512)?106:(equipment&1024)?107:(equipment&2048)?108:(equipment&4096)?109:(equipment&8192)?111:0;unsigned index=ACTOR_VARIANTS;
 for(unsigned i=0;i<ACTOR_VARIANTS;i++)if(actorBlobs[i].job==id&&actorBlobs[i].gear==gear&&(actorSex60[i]==2||actorSex60[i]==sex)){index=i;break;}
 if(index==ACTOR_VARIANTS){gear=0;for(unsigned i=0;i<ACTOR_VARIANTS;i++)if(actorBlobs[i].job==id&&!actorBlobs[i].gear&&(actorSex60[i]==2||actorSex60[i]==sex)){index=i;break;}}
 if(index==ACTOR_VARIANTS)fail("Player actor variant missing");if(id==spriteJob&&gear==spriteGear&&spriteVariantIndex54==index)return;spriteVariantIndex54=index;
#ifndef MYRO_HOST
 while(pb_busy()){}
#endif
 free(sprites[0].raw);memset(&sprites[0],0,sizeof(sprites[0]));const ActorBlob*b=&actorBlobs[index];unsigned char*packed=actor_packed(index);sprite_load(&sprites[0],"equipped player",packed,b->packed,b->raw);free(packed);sprites[0].actor58=id;spriteJob=id;spriteGear=gear;spriteEpoch++;
}
static void sprite_set_equipment(unsigned id,unsigned equipment){sprite_set_equipment_sex60(id,equipment,1);}
static void sprite_set_job(unsigned id){sprite_set_equipment(id,0);}
