"""Generate bounded travel pages and current-map town flags."""
from pathlib import Path
import csv,json,re
from collections import OrderedDict
from clearance51 import map_names51
from pack_world51 import label
ROOT=Path(__file__).resolve().parent.parent;SRC=ROOT/'Source'
def main():
 names=map_names51();ids={n:i for i,n in enumerate(names)}
 towns={'prontera','izlude','payon','pay_arche','alberta','aldebaran','geffen','morocc','comodo','umbala','yuno','einbroch','einbech','lighthalzen','rachel','veins','hugel','gonryun','amatsu','ayothaya','louyang','brasilis','moscovia','manuk','splendide','jawaii','xmas','niflheim'}
 groups=OrderedDict([('Towns',[ids[n]for n in names if n in towns]),('Prontera fields',[0,1,4,5,6]),('Sograt Desert',[7,8,9]),('Payon forest',[10]),('Payon Cave',[13,14,15,16,17])]);assigned={i for a in groups.values()for i in a}
 regionnames={'01-Geffen-GlastHeim':'Geffen / Glast Heim'}
 for region,name,*_ in csv.reader((ROOT.parent/'asset-library/Test51-world-maps/Map-Requests.tsv').open(encoding='utf-8-sig'),delimiter='\t'):
  group=regionnames.get(region,re.sub(r'^\d+-','',region).replace('-',' / '))
  if ids[name] not in assigned:groups.setdefault(group,[]).append(ids[name]);assigned.add(ids[name])
 assert len(assigned)==len(names)
 maxrows=max(map(len,groups.values()));count=len(groups)
 h='/* Source regions; IDs exceed 255, so map entries are unsigned short. */\n#ifndef MYRO_MENU_GROUPS48_H\n#define MYRO_MENU_GROUPS48_H\n#define TRAVEL_GROUP_COUNT51 %d\n#define TRAVEL_PAGE_ROWS51 6\n'%count
 h+='static const char*travelGroupNames48[]={'+','.join(json.dumps(n)for n in groups)+'};\nstatic const unsigned short travelGroups48[TRAVEL_GROUP_COUNT51][%d]={\n'%maxrows+''.join('{'+','.join(map(str,a))+'},\n'for a in groups.values())+'};\nstatic const unsigned short travelCounts48[]={'+','.join(str(len(a))for a in groups.values())+'};\n'
 h+='static int travel_group48(int map){for(int g=0;g<TRAVEL_GROUP_COUNT51;g++)for(int r=0;r<travelCounts48[g];r++)if(travelGroups48[g][r]==map)return g;return 0;}\nstatic int travel_row51(int map){int g=travel_group48(map);for(int r=0;r<travelCounts48[g];r++)if(travelGroups48[g][r]==map)return r;return 0;}\nstatic int travel_step48(int map,int delta){int g=travel_group48(map),n=travelCounts48[g];return travelGroups48[g][(travel_row51(map)+delta+n)%n];}\nstatic int travel_region48(int map,int delta){return travelGroups48[(travel_group48(map)+delta+TRAVEL_GROUP_COUNT51)%TRAVEL_GROUP_COUNT51][0];}\n#endif\n';(SRC/'menu_groups48.h').write_text(h)
 # Preserve town behavior without applying peaceful flags to surrounding fields.
 (SRC/'world_regions51.h').write_text('/* Towns clear combat as in the existing four town maps. */\nstatic const unsigned char peacefulMaps51[WORLD_MAP_COUNT]={'+','.join('1'if n in towns else'0'for n in names)+'};\n')
 prior=(ROOT.parent/'test50c/Source/pending_warps.h').read_text();pending=[]
 for mapid,x,y,destination in re.findall(r'\{(\d+),(\d+),(\d+),"([^"]+)"\}',prior):
  if destination not in ids:pending.append((int(mapid),int(x),int(y),destination))
 h='typedef struct{unsigned map;float x,y;const char*destination;} PendingWarp;\nstatic const PendingWarp pendingWarps[]={'+','.join('{%d,%d,%d,%s}'%(m,x,y,json.dumps(d))for m,x,y,d in pending)+'};\n#define PENDING_WARP_COUNT %du\n'%len(pending);(SRC/'pending_warps.h').write_text(h)
 (ROOT/'TRAVEL-REGIONS51.json').write_text(json.dumps(dict(groups=groups,maps=len(names),pending=len(pending)),indent=2));print('PASS',len(names),'maps',count,'groups, largest',maxrows,'entries; six visible rows')
if __name__=='__main__':main()
