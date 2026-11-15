/* MIT. Nine characters; one logical autosave plus nine manual records each.
 * Every record keeps the existing verified alternating character/quest bundle. */
#ifndef MYRO_CHARACTER_BANK56_H
#define MYRO_CHARACTER_BANK56_H
#define CHARACTER_SLOTS56 9u
#define CHARACTER_RECORDS56 10u
typedef struct {int state;uint64_t utc;uint32_t sequence;unsigned job,level,joblevel,map;char name[20];unsigned char stats[6];int hp,sp,exp;unsigned sex58,headSources180[3];Appearance58 appearance58;} CharacterRecord56;
static CharacterRecord56 characterRecords56[CHARACTER_SLOTS56][CHARACTER_RECORDS56];
static int developerUnlocked56,developerSession56;
static void bank_cache_clear56(void){npc_bundle_clear55(npcSaveBridge55.cached);npc_bundle_clear55(npcSaveBridge55.cached+1);}
static void bank_record_scan56(unsigned character,unsigned record){
 CharacterRecord56*out=&characterRecords56[character][record];memset(out,0,sizeof(*out));unsigned oldChar=saveCharacter56,oldRecord=saveRecord56;save_select56(character,record);bank_cache_clear56();static SaveStore scan;memset(&scan,0,sizeof(scan));save_npc_setup55(&scan);save_scan(&scan);
 if(scan.newest>=0&&!scan.blocked){const SavedCharacter*c=scan.character+scan.newest;out->state=1;out->sequence=c->sequence;out->utc=npcSaveBridge55.cached[scan.newest].utc;out->job=c->jobId;out->level=c->level;out->joblevel=c->joblevel;out->map=c->mapId;out->hp=c->hp;out->sp=c->sp;out->exp=c->exp;out->sex58=c->sex55;out->appearance58=c->appearance58;memcpy(out->name,c->name56,20);if(!out->name[0])memcpy(out->name,"Novice",7);memcpy(out->stats,c->stats,6);for(unsigned slot180=0;slot180<3;slot180++){unsigned bit180=(unsigned[]){512,256,1}[slot180],costume180=(unsigned[]){2048,1024,4096}[slot180];for(unsigned pass180=0;pass180<2&&!out->headSources180[slot180];pass180++)for(unsigned k180=0;k180<c->owned52.count[0];k180++){const OwnedItem52*piece180=c->owned52.items+k180;if(piece180->quantity&&(piece180->equipped&(pass180?bit180:costume180))){out->headSources180[slot180]=piece180->sourceID;break;}}}}
 else if(scan.blocked||scan.bad)out->state=2;
 bank_cache_clear56();save_select56(oldChar,oldRecord);
}
static void bank_scan56(void){for(unsigned c=0;c<CHARACTER_SLOTS56;c++)for(unsigned r=0;r<CHARACTER_RECORDS56;r++)bank_record_scan56(c,r);}
static int bank_latest56(unsigned character){int latest=-1;for(unsigned r=0;r<CHARACTER_RECORDS56;r++){CharacterRecord56*p=&characterRecords56[character][r];if(p->state==1&&(latest<0||p->utc>characterRecords56[character][latest].utc||(p->utc==characterRecords56[character][latest].utc&&p->sequence>characterRecords56[character][latest].sequence)))latest=(int)r;}return latest;}
static int bank_occupied56(unsigned character){for(unsigned r=0;r<CHARACTER_RECORDS56;r++)if(characterRecords56[character][r].state)return 1;return 0;}
static int bank_save56(SaveStore*store,const Combat*game,unsigned record){if(record>=CHARACTER_RECORDS56)return 0;save_select56(saveCharacter56,record);bank_cache_clear56();store->sequenceFloor56=0;for(unsigned i=0;i<10;i++)if(characterRecords56[saveCharacter56][i].state==1&&store->sequenceFloor56<characterRecords56[saveCharacter56][i].sequence)store->sequenceFloor56=characterRecords56[saveCharacter56][i].sequence;int ok=save_commit(store,game);store->sequenceFloor56=0;bank_record_scan56(saveCharacter56,record);save_select56(saveCharacter56,0);bank_cache_clear56();return ok;}
static int bank_load56(SaveStore*store,Combat*game,unsigned record){if(record>=CHARACTER_RECORDS56)return 0;save_select56(saveCharacter56,record);bank_cache_clear56();int ok=save_load(store,game,spawnx,spawny,world_can_move,NULL);save_select56(saveCharacter56,0);bank_cache_clear56();return ok;}
static int bank_delete_record56(unsigned character,unsigned record){if(character>=CHARACTER_SLOTS56||record>=CHARACTER_RECORDS56)return 0;unsigned oldChar=saveCharacter56,oldRecord=saveRecord56;save_select56(character,record);int ok=1;for(unsigned i=0;i<2;i++)if(!DeleteFile(savePaths[i])&&GetLastError()!=ERROR_FILE_NOT_FOUND)ok=0;save_select56(oldChar,oldRecord);bank_record_scan56(character,record);return ok;}
static int bank_delete_character56(unsigned character){int ok=1;for(unsigned r=0;r<CHARACTER_RECORDS56;r++)if(!bank_delete_record56(character,r))ok=0;return ok;}
#endif
