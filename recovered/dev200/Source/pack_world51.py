"""Append new current-map blobs; preserve every byte and ID of the accepted build."""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import csv,hashlib,json,re,struct,zlib
from clearance51 import map_names51,source_gates51
ROOT=Path(__file__).resolve().parent.parent;BASE=ROOT.parent/'test50c';SOURCE=ROOT/'Source'

def label(name):
 towns={'aldebaran':'Al De Baran','geffen':'Geffen','morocc':'Morocc','alberta':'Alberta','comodo':'Comodo','umbala':'Umbala','yuno':'Juno','einbroch':'Einbroch','einbech':'Einbech','lighthalzen':'Lighthalzen','rachel':'Rachel','veins':'Veins','hugel':'Hugel','izlude':'Izlude','prontera':'Prontera','payon':'Payon','gonryun':'Gonryun','amatsu':'Amatsu','ayothaya':'Ayothaya','louyang':'Louyang','brasilis':'Brasilis','moscovia':'Moscovia','manuk':'Manuk','splendide':'Splendide','jawaii':'Jawaii','xmas':'Lutie','niflheim':'Niflheim'}
 if name in towns:return towns[name]
 prefixes={'gef_fild':'Geffen Field','gef_dun':'Geffen Dungeon','gefenia':'Geffenia','mjolnir_':'Mt. Mjolnir','mjo_dun':'Mjolnir Mine','prt_fild':'Prontera Field','moc_fild':'Sograt','pay_fild':'Payon Forest','pay_dun':'Payon Cave','prt_sewb':'Prontera Culvert','iz_dun':'Undersea Tunnel','gl_':'Glast Heim','in_sphinx':'Sphinx','moc_pryd':'Pyramid','c_tower':'Clock Tower','alde_dun':'Clock Basement','xmas_dun':'Toy Factory','nif_fild':'Niflheim Field','um_fild':'Umbala Field','cmd_fild':'Comodo Field','beach_dun':'Comodo Cave','yuno_fild':'Juno Field','mag_dun':'Magma Dungeon','ein_fild':'Einbroch Field','ein_dun':'Einbech Mine','lhz_dun':'Biolabs','lhz_fild':'Lighthalzen Field','hu_fild':'Hugel Field','jupe_':'Juperos','ra_fild':'Rachel Field','ra_san':'Rachel Sanctuary','ve_fild':'Veins Field','thor_v':'Thor Volcano','ice_dun':'Ice Dungeon','abyss_':'Abyss Lake','tha_t':'Thanatos Tower','odin_tem':'Odin Temple','ama_dun':'Amatsu Dungeon','gon_dun':'Gonryun Dungeon','lou_dun':'Louyang Dungeon','ayo_dun':'Ayothaya Dungeon','mosk_dun':'Moscovia Dungeon','bra_dun':'Brasilis Dungeon','man_fild':'Manuk Field','spl_fild':'Splendide Field','nyd_dun':'Nidhogg Nest'}
 for prefix,title in sorted(prefixes.items(),key=lambda x:-len(x[0])):
  if name.startswith(prefix):return title+' '+name[len(prefix):].replace('_',' ').upper()
 # Retain recognizable room names when there is no authoritative translated name.
 return name.replace('_',' ').title()

def prepare(name):
 out=ROOT/'WorldAssets'/name;paths=['atlas.bin','collision.bin','spawn.bin','geometry.bin','SceneryAssets/atlas.bin','SceneryAssets/mesh.bin','SceneryAssets/instances.bin','minimap.bin'];blobs=[]
 for path in paths:
  raw=(out/path).read_bytes();packed=zlib.compress(raw,6);blobs.append((packed,len(raw),zlib.crc32(packed)))
 return name,blobs

def main():
 old=(BASE/'Source/world_data.h').read_text();names=map_names51();assert len(names)==409
 oldnames=re.findall(r'"(.*?)"',re.search(r'mapNames\[\]=\{(.*?)\}',old)[1]);assert names[:18]==oldnames
 rows=[list(map(int,v))for v in re.findall(r'\{(\d+),(\d+),(\d+),(\d+)\}',old[:old.index('static const WorldBlob minimapBlobs45')])];rows=[rows[i*7:(i+1)*7]for i in range(18)]
 minis=[list(map(int,v))for v in re.findall(r'\{(\d+),(\d+),(\d+),(\d+)\}',re.search(r'minimapBlobs45\[18\]=\{(.*?)\};',old,re.S)[1])]
 labels=re.findall(r'"(.*?)"',re.search(r'mapLabels\[\]=\{(.*?)\}',old)[1]);widths=list(map(int,re.search(r'mapWidths\[\]=\{(.*?)\}',old)[1].split(',')));heights=list(map(int,re.search(r'mapHeights\[\]=\{(.*?)\}',old)[1].split(',')))
 target=ROOT/'Packed/world.bin';temporary=target.with_suffix('.pending');reports=[]
 with temporary.open('wb')as stream:
  prefix=(BASE/'Packed/world.bin').read_bytes();stream.write(prefix)
  with ThreadPoolExecutor(max_workers=4)as pool:
   for number,(name,blobs)in enumerate(pool.map(prepare,names[18:]),18):
    descriptors=[]
    for packed,raw,crc in blobs:
     descriptors.append([stream.tell(),len(packed),raw,crc]);stream.write(packed)
    rows.append(descriptors[:7]);minis.append(descriptors[7]);r=json.loads((ROOT/'WorldAssets'/name/'CONVERSION51.json').read_text());widths.append(r['terrain']['width']);heights.append(r['terrain']['height']);labels.append(label(name))
    reports.append({'id':number,'map':name,'packed':sum(x[1]for x in descriptors),'world_resident_raw':sum(x[2]for x in descriptors[:7])});print(number,name,stream.tell(),flush=True)
  total=stream.tell()
 temporary.replace(target);gates=source_gates51(names)
 def array(key,values,string=False):return 'static const '+('char*'if string else'unsigned ')+key+'[]={'+','.join(json.dumps(v)if string else str(v)for v in values)+'};\n'
 h='/* Generated source world maps. Only the active area is resident. */\n#define WORLD_MAP_COUNT %d\ntypedef struct {unsigned offset,packed,raw,crc;} WorldBlob;\ntypedef struct {unsigned source;float x,y,rx,ry;unsigned destination;float destX,destY;} WorldGate;\n#define WORLD_FILE_BYTES %du\n'%(len(names),total)
 h+='static const WorldBlob worldBlobs[WORLD_MAP_COUNT][7]={\n'+',\n'.join('{'+','.join('{'+','.join(map(str,b))+'}'for b in row)+'}'for row in rows)+'};\n'
 h+='static const WorldBlob minimapBlobs45[WORLD_MAP_COUNT]={'+','.join('{'+','.join(map(str,b))+'}'for b in minis)+'};\nstatic void world_blob_init(void){}\n'
 h+=array('mapLabels',labels,True)+array('mapNames',names,True)+array('mapWidths',widths)+array('mapHeights',heights)
 h+='static const WorldGate worldGates[]={\n'+''.join('{'+','.join(map(str,g))+'},\n'for g in gates)+'};\n#define WORLD_GATE_COUNT (sizeof(worldGates)/sizeof(worldGates[0]))\n'
 (SOURCE/'world_data.h').write_text(h)
 (SOURCE/'map_limits43.h').write_text('#ifndef MYRO_MAP_LIMITS43_H\n#define MYRO_MAP_LIMITS43_H\n#define MYRO_MAP_COUNT43 %d\n'%len(names)+array('mapWidth43',[w*16 for w in widths])+array('mapHeight43',[h*16 for h in heights])+'#endif\n')
 manifest=dict(maps=len(names),gates=len(gates),bytes=total,preserved_prefix_bytes=len(prefix),preserved_prefix_sha256=hashlib.sha256(prefix).hexdigest(),new_maps=reports)
 (ROOT/'WORLD-PACK51.json').write_text(json.dumps(manifest,indent=2));print('PASS',len(names),'maps',len(gates),'gates',total,'bytes')
if __name__=='__main__':main()
