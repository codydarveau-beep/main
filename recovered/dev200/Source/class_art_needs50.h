/* MIT. Only the selected class, parents and one copied skill are resident. */
static void class_art_needs50(unsigned char*need,unsigned job,unsigned copy){
 if(job<12)return;
 for(int k=0;k<LEARN_COUNT;k++)if(job_owns_skill48(job,learnJobs[k],learnIds[k])){int c=art39_skill_clip(learnIds[k]);if(c>=0&&c<ART39_COUNT)need[c]=1;}
 if(job==J60_GUNSLINGER){need[FX62_TRACK_CAST]=need[FX62_INCREASING_CAST]=need[FX62_INCREASING_BOTTOM]=1;for(int i=FX62_MINE_WIND;i<=FX62_MINE_FIRE;i++)need[i]=1;}
 if(job==J60_TAEKWON||job==J60_STAR_GLADIATOR)need[FX62_COUNTER_BOTTOM]=1;
 if(job==J52_SUPER_NOVICE){need[3]=need[15]=need[16]=need[17]=need[41]=need[42]=need[43]=need[45]=1;int fury=art39_skill_clip(209);if(fury>=0)need[fury]=1;int steel=art39_skill_clip(207);if(steel>=0)need[steel]=1;}unsigned baseJob=job_parent52(job);need[2]=1;if(job_first50(job)==3||job==J52_SUPER_NOVICE)need[45]=1;if((job_first50(job)==6||job==J52_SUPER_NOVICE))need[9]=1;
 if(baseJob==12){need[FX50_VENOMDUST]=need[FX50_VENOMSPLASHER]=need[FX50_POISONREACT]=1;}
 if(baseJob==18)need[FX50_SPIRIT_SPHERE]=1;
 if(baseJob==17)need[FX50_MAGNUS]=need[FX50_SANCTUARY]=1;
 if(baseJob==20){need[45]=1;need[FX50_DEMONSTRATION]=need[FX50_DEFENSE]=need[FX50_CASTLING]=need[FX50_BLOODLUST]=1;need[15]=need[16]=need[17]=need[5]=need[6]=1;}
 if(baseJob==13&&copy){int c=art39_skill_clip(copy);if(c>=0)need[c]=1;int air=art_air_clip40(copy);if(air>=0)need[air]=1;if(copy==75)for(int i=37;i<=40;i++)need[i]=1;if(copy==77)need[7]=1;if(copy==80)need[22]=1;if(copy==189)need[FX50_SANCTUARY]=1;if(copy==197)need[FX50_MAGNUS]=1;}
}
