"""Necessary campaign connectivity under actual chronology; not a quest-playthrough proof."""
from pathlib import Path
import re,json,ctypes,subprocess
R=Path(__file__).resolve().parent.parent;S=R/'Source';V=R/'Validation';world=(S/'world_data.h').read_text();body=world.split('static const WorldGate worldGates[]={',1)[1].split('};',1)[0];gates=[]
for row in re.findall(r'\{([^{}]+)\}',body):
 values=row.split(',');gates.append((int(values[0].rstrip('u')),int(values[5].rstrip('u'))))
runtime=(S/'campaign_admission_runtime194.h').read_text();begin=runtime.index('static int campaign_career_gate194(');line=runtime[begin:runtime.index('static void campaign_admission_install194(',begin)];(V/'actual_career_gate236.inc').write_text('/* Exact production career gate. */\n'+line+'\n')
subprocess.run(['cc','-O1','-shared','-fPIC','-I'+str(S),str(V/'campaign_reach_adapter236.c'),'-lm','-lz','-o',str(V/'campaign_reach236.so')],check=True)
lib=ctypes.CDLL(str(V/'campaign_reach236.so'));B=ctypes.c_ubyte;lib.reach236.argtypes=[ctypes.c_uint,ctypes.c_uint,ctypes.c_void_p,ctypes.c_void_p,ctypes.c_void_p]
stages=[(int(a),int(b))for a,b in re.findall(r'\{(\d+)u,(\d+)u,\d+u,[\d.]+f,',(S/'campaign_stage_data197.h').read_text())];assert len(stages)==42
# Later authored rows replace the old early Morroc placements for normal play.
later=stages[9:];later_cursors={c for c,m in later};normalStages=later+[r for r in stages[:9]if r[0]not in later_cursors]
registry=(S/'npc_registry_data55.h').read_text();npcs=[]
for line in registry.splitlines():
 if not line.startswith('{'):continue
 vals=line.split(',',12)
 if len(vals)!=13 or not all(v.isdigit()for v in vals[1:6]):continue
 npcs.append((int(vals[0][1:])-1,int(vals[1]),int(vals[2]),int(vals[11])))
assert len(npcs)==10181
deps=json.loads((R/'Preparation/NPC-Dependencies194.json').read_text())['programs'];helpers=[set(r['helpers'])for r in deps];transit={696,844,3604,3866};changed=True
while changed:
 changed=False
 for i,h in enumerate(helpers):
  new=set(h)
  for p in h:new|=helpers[p-1]
  if new!=h:helpers[i]=new;changed=True
travel=list(json.loads((R/'Preparation/Native-Travel-Routes194.json').read_text()).values());rows=[];unreachable=[]
for cursor in range(36):
 maps=(B*497)();admit=(B*10181)();enabled=(B*len(gates))();lib.reach236(cursor,0xffffffff,maps,admit,enabled);edges=[set()for _ in range(497)]
 for i,(a,b)in enumerate(gates):
  if enabled[i]and a<497 and b<497 and maps[a]and maps[b]:edges[a].add(b)
 for npc,program,source,flags in npcs:
  if not program or source>=497 or flags&2 or not admit[npc]or not maps[source]:continue
  d=deps[program-1];destinations=set(d['references'])if d['worldOperation']else set()
  if program in transit or helpers[program-1]&transit:destinations.update(travel)
  for dest in destinations:
   if dest<497 and maps[dest]:edges[source].add(dest)
 seen={0};todo=[0]
 while todo:
  source=todo.pop()
  for dest in edges[source]-seen:seen.add(dest);todo.append(dest)
 required=sorted({m for c,m in normalStages if c==cursor}|({0}if cursor<3 else set()));missing=[m for m in required if m not in seen];rows.append(dict(cursor=cursor,reachableMaps=len(seen),requiredSceneMaps=required,missing=missing));unreachable.extend((cursor,m)for m in missing)
(V/'Campaign-Reach-Checks236.json').write_text(json.dumps(dict(passed=not unreachable,cases=rows,unreachable=unreachable,scope='Necessary map-level reachability from opening camp to every current authored stage, including all four optional cursor-18 evidence locations, at each cursor; historical superseded early Morroc rows remain preserved but are not required for normal progression, using actual production map/NPC chronology and career/story gate predicates, static door graph and admitted native script map references/helper transport menus. Completed scene objectives are assumed to permit within-scene passages. Graph is an upper bound: native quest/event/fee requirements, precise entrance path and selected dynamic destination execution are not completed by this analysis. No scripts, maps or policies changed.',originalXboxPlaytested=False,xemuPlaytested=False,additionalReviewPassesCompleted=0),indent=2)+'\n')
assert not unreachable,unreachable
print('PASS necessary authored-stage connectivity under current chronology; native quest/fee/controller journeys remain separately tested.')
