/* SPDX-License-Identifier: MIT. Read-only migration from shipped Test48/49 saves. */
#ifndef MYRO_SAVE48_IMPORT50_H
#define MYRO_SAVE48_IMPORT50_H
#define SAVE48_BYTES50 4096
static int save_decode48_50(SavedCharacter*s,const unsigned char*p){
 if(memcmp(p,"MYROSV48",8)||save_u32(p+8)!=48||save_u32(p+12)!=SAVE48_BYTES50||save_u32(p+20)!=SAVE_WORLD43)return -1;
 if(save_crc(p,4092)!=save_u32(p+4092)||save_u32(p+108)!=1||save_u32(p+156)!=1)return 0;
 if(p[138]||p[139]||p[167]||p[182]||p[183])return 0;
 for(int i=196;i<200;i++)if(p[i])return 0;
 if(p[231])return 0;for(int i=324;i<328;i++)if(p[i])return 0;for(int i=348;i<352;i++)if(p[i])return 0;
 SavedCharacter t;memset(&t,0,sizeof(t));
 t.sequence=save_u32(p+16);
 t.x=save_float(p+24);
 t.y=save_float(p+28);
 t.faceX=save_float(p+32);
 t.faceY=save_float(p+36);
 t.hp=save_u32(p+40);
 t.sp=save_u32(p+44);
 t.level=save_u32(p+48);
 t.joblevel=save_u32(p+52);
 t.exp=save_u32(p+56);
 t.jexp=save_u32(p+60);
 t.kills=save_u32(p+64);
 t.jellopy=save_u32(p+68);
 t.clover=save_u32(p+72);
 t.apples=save_u32(p+76);
 t.rng=save_u32(p+80);
 t.equipment=save_u32(p+104);
 t.hotSlot=save_u32(p+120);
 t.mapId=save_u32(p+124);
 t.zeny=save_u32(p+128);
 t.statPoints=save_u32(p+140);
 t.jobId=save_u32(p+144);
 t.skillPoints=save_u32(p+148);
 t.quickKind=save_u32(p+168);
 t.quickId=save_u32(p+172);
 t.rbBinding=save_u32(p+200);
 t.brokenWeapon48=save_u32(p+3000);
 t.mounted48=save_u32(p+3004);
 t.walkPercent45=save_u32(p+628);
 t.diagnosticsOff45=save_u32(p+632);
 t.memoCount=save_u32(p+260);
 t.popupDisabled=save_u32(p+344);
 t.cartOwned=save_u32(p+424);
 t.cartStyle=save_u32(p+428);
 t.tooltipsDisabled=save_u32(p+504);
 if(t.jobId>11||t.quickKind==1&&t.quickId>=127)return 0;
 memcpy(t.stats,p+132,6);t.home=(WorldPosition){save_u32(p+248),save_float(p+252),save_float(p+256)};
 for(int i=0;i<3;i++)t.memos[i]=(WorldPosition){save_u32(p+264+i*12),save_float(p+268+i*12),save_float(p+272+i*12)};
 for(int i=0;i<112;i++)t.extraItems[i]=save_u32(p+1024+i*4);
 for(int i=0;i<115;i++){t.storageItems[i]=save_u32(p+1536+i*4);t.cartItems[i]=save_u32(p+2048+i*4);}
 for(int i=0;i<10;i++){unsigned eq=save_u32(p+2560+i*4);if(eq>115)return 0;t.equipped46[i]=eq;}
 memcpy(t.ranks,p+2700,124);memcpy(t.useRanks45,p+2840,124);
 for(int i=0;i<12;i++){unsigned raw=p[i<8?112+i:300+i-8],b=binding_from48(raw);if(b>BIND_EMPTY50)return 0;t.hotbar[i]=b;}
 t.rbBinding=binding_from48(t.rbBinding);if(t.rbBinding>BIND_EMPTY50)return 0;
 if(t.quickKind==0&&t.quickId>=115)return 0;
 if(!save_valid(&t))return 0;*s=t;return 1;
}
#endif
