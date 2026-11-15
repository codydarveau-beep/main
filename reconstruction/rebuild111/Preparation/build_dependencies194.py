"""Conservative bytecode dependency reconstruction from deployed metadata.

Finite stack abstraction follows branches/subroutines. Dependencies are map
references in programs with transitive warp/savepoint operations, propagated
through original global helpers. It does not execute or rewrite native scripts.
"""
from pathlib import Path
from collections import deque
import json
import re
import struct

ROOT = Path(__file__).resolve().parent.parent
PACKET = ROOT.parent/'packet194'
programs = json.loads((PACKET/'released-program-index.json').read_text())
wire = (PACKET/'released-scripts.bin').read_bytes()
names = json.loads((PACKET/'RecoveredMetadata/released-map-names.json').read_text())
map_ids = {n:i for i,n in enumerate(names)}
registry = (ROOT/'Source/npc_registry_data55.h').read_text()
functions_text = re.search(r'npcFunctions55\[\]=\{(.*?)\};',registry,re.S)[1]
functions = {n:int(i) for n,i in re.findall(r'\{"([^"]+)",(\d+)u\}',functions_text)}
constants = {n:int(v) for n,v in re.findall(r'\{"([^"]+)",INT64_C\((-?\d+)\)\}',(ROOT/'Source/npc_constants_data55.h').read_text())}
UNKNOWN = frozenset({('unknown',)})


def value(kind, x): return frozenset({(kind,x)})


def union(a,b):
    c = a | b
    return UNKNOWN if ('unknown',) in c or len(c)>64 else c


def integers(v):
    return [x[1] for x in v if x[0]=='int'] if all(x[0]=='int' for x in v) else []


def strings(v):
    return {x[1] for x in v if x[0] in ('string','ref')}


def binary(a,b,op):
    if a==UNKNOWN or b==UNKNOWN: return UNKNOWN
    result=frozenset()
    for x in a:
        for y in b:
            if op==0 and x[0]==y[0]=='string': z=('string',x[1]+y[1])
            elif x[0]==y[0]=='int':
                u,v=x[1],y[1]
                try:
                    if op==0:n=u+v
                    elif op==1:n=u-v
                    elif op==2:n=u*v
                    elif op==3:n=abs(u)//abs(v)*(1 if (u>=0)==(v>=0) else -1)
                    elif op==4:n=u-(abs(u)//abs(v)*(1 if (u>=0)==(v>=0) else -1))*v
                    elif op==5:
                        if not 0<=v<=16:return UNKNOWN
                        n=u**v
                    elif op==6:n=u<<(v&63)
                    elif op==7:n=u>>(v&63)
                    elif op==8:n=int(u<v)
                    elif op==9:n=int(u<=v)
                    elif op==10:n=int(u>v)
                    elif op==11:n=int(u>=v)
                    elif op==12:n=int(u==v)
                    elif op==13:n=int(u!=v)
                    elif op==14:n=u&v
                    elif op==15:n=u^v
                    elif op==16:n=u|v
                    else:return UNKNOWN
                    n=((n+(1<<63))%(1<<64))-(1<<63);z=('int',n)
                except (ZeroDivisionError,OverflowError):return UNKNOWN
            else:return UNKNOWN
            result=union(result,frozenset({z}))
    return result or UNKNOWN


reports=[]
failures=[]
for p in programs:
    raw=wire[p['offset']:p['offset']+p['bytes']]
    nc,ns,nl,nf=struct.unpack_from('<4I',raw,16)
    pool=raw[40+nc*12+(nl+nf)*8:]
    def text(at):return pool[at:pool.index(0,at)].decode('utf8','replace')
    code=[struct.unpack_from('<III',raw,40+i*12)for i in range(nc)]
    labels=dict(zip(p['labels'],[e[1]for e in p['labelEntries']]))
    all_strings=set(s.decode('utf8','replace')for s in pool.split(b'\0'))
    refs={map_ids[s[:-4]if s.endswith('.gat')else s] for s in all_strings if (s[:-4]if s.endswith('.gat')else s)in map_ids}
    helpers={functions[s] for s in all_strings if s in functions}
    sites={}
    states={}
    queue=deque()
    def submit(pc,stack):
        if not 0<=pc<nc:return
        if len(stack)>512:raise ValueError('abstract stack exceeds native limit')
        key=(pc,len(stack));old=states.get(key)
        merged=tuple(stack)if old is None else tuple(union(a,b)for a,b in zip(old,stack))
        if old!=merged:states[key]=merged;queue.append(key)
    submit(0,[])
    for name,pc in labels.items():
        if name.startswith('On'):submit(pc,[])
    for _,pc in p['functionEntries']:submit(pc,[])
    try:
        iterations=0
        while queue:
            iterations+=1
            if iterations>nc*256:raise ValueError('abstract convergence limit')
            key=queue.popleft();pc=key[0];stack=list(states[key]);op,a,b=code[pc]
            def pop():
                if not stack:raise ValueError('abstract stack underflow at '+str(pc))
                return stack.pop()
            if op in (0,13):continue
            if op==1:
                n=a|(b<<32);stack.append(value('int',n-(1<<64)if n&(1<<63)else n))
            elif op in (2,3):stack.append(value('string'if op==2 else 'ref',text(a)))
            elif op==4:
                v=pop();vs=strings(v)
                stack.append(frozenset(('int',constants[n])for n in vs)if vs and all(n in constants for n in vs)else UNKNOWN)
            elif op==5:
                v=pop();pop();stack.append(v)
            elif op==6:
                v=pop();stack.extend([v,v])
            elif op==7:pop()
            elif op==8:
                v=pop();ns=integers(v)
                stack.append(frozenset(('int',(+n if a==0 else -n if a==1 else int(not n)if a==2 else ~n))for n in ns)if ns else UNKNOWN)
            elif op==9:
                right,left=pop(),pop();stack.append(binary(left,right,a))
            elif op==10:submit(a,stack);continue
            elif op==11:
                v=pop();ns=integers(v)
                if not ns or any(n==0 for n in ns):submit(a,stack)
                if ns and all(n==0 for n in ns):continue
            elif op==12:
                name=text(a)
                if b>len(stack):raise ValueError('call arguments underflow at '+str(pc))
                args=stack[len(stack)-b:]if b else []
                if b:del stack[-b:]
                for arg in args:
                    refs.update(map_ids[n]for n in strings(arg)if n in map_ids)
                if name in ('warp','savepoint'):
                    old_site=sites.get(pc,{'pc':pc,'command':name,'destination':frozenset()})
                    old_site['destination']=union(old_site['destination'],args[0]if args else UNKNOWN);sites[pc]=old_site
                if name=='callsub' and args:
                    for label in strings(args[0]):
                        if label in labels:submit(labels[label],[])
                if name=='callfunc' and args:
                    helpers.update(functions[n]for n in strings(args[0])if n in functions)
                stack.append(UNKNOWN)
            elif op==14:
                pop();stack.append(pop())
            elif op==15:pop();stack.append(UNKNOWN)
            else:raise ValueError('unsupported opcode')
            submit(pc+1,stack)
    except ValueError as error:
        failures.append({'program':p['id'],'error':str(error)})
    # Include every compiled site, even dead branches. An unvisited destination
    # remains unknown; it is never certified by omission.
    for pc,(op,a,b)in enumerate(code):
        if op==12 and text(a)in ('warp','savepoint')and pc not in sites:
            # A literal call after a terminating close remains in the deployed
            # bytecode. Classify its direct arguments without making it live.
            literal = pc>=b and all(code[j][0]in (1,2)for j in range(pc-b,pc))
            destination=value('string',text(code[pc-b][1]))if literal and code[pc-b][0]==2 else UNKNOWN
            sites[pc]={'pc':pc,'command':text(a),'destination':destination}
    reports.append({'program':p['id'],'references':sorted(refs),'helpers':sorted(helpers),
                    'worldOperation':bool(sites),'sites':[dict(pc=s['pc'],command=s['command'],
                    destinationValues=sorted([list(v)for v in s['destination']],key=str),
                    dynamic=any(v[0]not in ('string',)for v in s['destination']))for s in sites.values()]})

world=[r['worldOperation']for r in reports]
changed=True
while changed:
    changed=False
    for i,r in enumerate(reports):
        if not world[i]and any(world[h-1]for h in r['helpers']):world[i]=True;changed=True
managed_menus={696,844,3604,3866}
deps=[set(r['references'])if world[i]and i+1 not in managed_menus else set()for i,r in enumerate(reports)]
changed=True
while changed:
    changed=False
    for i,r in enumerate(reports):
        if not world[i]or i+1 in managed_menus:continue
        for helper in r['helpers']:
            if helper in managed_menus:continue
            before=len(deps[i]);deps[i]|=deps[helper-1]
            if len(deps[i])!=before:changed=True
for p in [498,504,506,1894,1901,1942,1953,1954,1955,1956,2011,2738,2739,2740,2742,2744,2745,2746,2783,3152,3241,3941]:deps[p-1].add(127)
for p in [3884,3885,3886]:
    if map_ids['amatsu'] in deps[p-1]:
        deps[p-1].remove(map_ids['amatsu']);deps[p-1].add(map_ids['que_ng'])
flat=[];offsets=[0]
for d in deps:flat.extend(sorted(d));offsets.append(len(flat))
summary={'programs':len(reports),'warpSites':sum(s['command']=='warp'for r in reports for s in r['sites']),
         'dynamicWarpSites':sum(s['command']=='warp'and s['dynamic']for r in reports for s in r['sites']),
         'stackAnalysisFailures':failures,'dependencyMembers':len(flat),'staticBytes':len(flat)*2+len(offsets)*2,
         'historicalCountsAreComparisonTargetsOnly':True,
         'choicePreflightManagedPrograms':sorted(managed_menus),
         'careerDestinationRemaps':{'3884/3885/3886':'amatsu -> que_ng'},
         'method':'Conservative map-literal/helper closure; includes transitive savepoint operations'}
(ROOT/'Preparation/NPC-Dependencies194.json').write_text(json.dumps({'summary':summary,'programs':reports,'dependencies':[sorted(d)for d in deps]},indent=2)+'\n')
print(json.dumps(summary,indent=2))
assert not failures,'Refuse to generate runtime dependency data after abstract-analysis failures'
assert max(offsets)<65536
text='/* MIT. Reconstructed conservative native transport dependencies. */\n#ifndef MYRO_NPC_ACCESS_DATA194_H\n#define MYRO_NPC_ACCESS_DATA194_H\n#define NPC_ACCESS_PROGRAMS194 3948u\n'
text+='static const unsigned short npcAccessOffsets194[]={'+','.join(map(str,offsets))+'};\n'
text+='static const unsigned short npcAccessMaps194[]={'+','.join(map(str,flat))+'};\n#endif\n'
(ROOT/'Source/npc_access_data194.h').write_text(text)
