"""Restore designer-confirmed scene environment references; no native scripts copied."""
from pathlib import Path
import re,json,hashlib
R=Path(__file__).resolve().parent.parent;S=R/'Source';changes=[]
def extend(file,name,overrides=None,pad=None):
 p=S/file;s=p.read_text();m=re.search(r'\b'+name+r'\s*(?:\[[^]]*\])+\s*=\s*\{',s);assert m,(file,name);start=m.end();depth=0;quoted=False;escape=False;parts=[];a=start
 for i in range(start,len(s)):
  c=s[i]
  if quoted:
   if escape:escape=False
   elif c=='\\':escape=True
   elif c=='"':quoted=False
   continue
  if c=='"':quoted=True
  elif c=='{':depth+=1
  elif c=='}':
   if depth==0:
    if s[a:i].strip():parts.append(s[a:i].strip())
    end=i;break
   depth-=1
  elif c==','and depth==0:
   if s[a:i].strip():parts.append(s[a:i].strip())
   a=i+1
 assert len(parts)in[494,495,497],(name,len(parts))
 originalCount=len(parts)
 if len(parts)==494:assert pad is not None;parts.append(pad)
 aliases=[overrides[k]if overrides else parts[src]for k,src in enumerate([343,118])]
 before=hashlib.sha256(s.encode()).hexdigest()
 if len(parts)==497:assert parts[495:]==aliases;return
 prefix=s[start:end];comma=''if prefix.rstrip().endswith(',')else','
 # The padding slot exists only in the music table, whose guild map was silent.
 extra=[pad]if originalCount==494 else []
 s=s[:end]+comma+'\n'+','.join(extra+aliases)+s[end:];p.write_text(s);changes.append(dict(file=file,array=name,beforeSHA256=before,aliases=aliases))
for name in ['worldBlobs','minimapBlobs45','mapWidths','mapHeights']:extend('world_data.h',name)
extend('world_data.h','mapNames',['"story_thana194"','"story_moc194"'])
extend('world_data.h','mapLabels')
for name in ['mapWidth43','mapHeight43']:extend('map_limits43.h',name)
extend('water_data.h','waterMaps');extend('water_data190.h','waterSettings190',pad='{0,0,0,0,1}');extend('music_data.h','musicMapTracks',pad='-1')
for file,macro in [('world_data.h','WORLD_MAP_COUNT'),('map_limits43.h','MYRO_MAP_COUNT43'),('music_data.h','MUSIC_MAP_COUNT49')]:
 p=S/file;s=p.read_text();s,n=re.subn(r'(#define '+macro+r' )\d+',r'\g<1>497',s);assert n==1;p.write_text(s)
(R/'Preparation/Story-Aliases-Recovery199.json').write_text(json.dumps(dict(authority='Designer clarification in current conversation',aliases=[dict(map=495,name='story_thana194',source=343),dict(map=496,name='story_moc194',source=118,sourceName='moc_fild22')],staticModifications=False,nativeScriptsCopied=False,nativeSpawnDefinitionsCopied=False,changes=changes,transportRecovered=[dict(source=280,x=1004,y=100,destination=495,destX=1092,destY=932,visibleCursor=28,requiredObjectiveBitAt28=2),dict(source=7,destination=496,visibleCursor=32,openCursor=33)],transportMissing=['495 return trigger coordinates','map 7 breach trigger and arrival','496 return trigger and map 7 arrival'],sourceMap118SeparateMinimumCursor=35,sceneArchitecture='Environment -> staged actors/encounters -> scripted movement/dialogue/combat with control locks -> resource release -> exploration',status='Environment tables restored; physical access/transport and scene lifecycle validation pending'),indent=2)+'\n')
print('Restored both scene-only environment aliases, water, minimaps and music. Native scripts/encounters remain separate.')
