from pathlib import Path
import json,struct,zlib
B=Path('/workspace/myro/dev200');S=B/'Source';D=B/'Campaign';D.mkdir(exist_ok=True)
# Named labels compile into bounded node indices. Explicit branch/gates replace
# the prose draft's provisional automatic dialogue extraction.
def say(label,who,text,next,role=0,expression=0):return dict(label=label,kind=1,speaker=who,text=text,next=next,role=role,expression=expression)
def choice(label,a,b,ta,tb):return dict(label=label,kind=2,speaker='Player',options=[a,b],targets=[ta,tb])
def gate(label,mask,next):return dict(label=label,kind=3,required=mask,next=next)
def end(label,mask=0):return dict(label=label,kind=4,required=mask)
def role(label,next):return dict(label=label,kind=5,next=next)
def close(label):return dict(label=label,kind=6)
def join(label,mask,next):return dict(label=label,kind=7,required=mask,next=next)
scenes=[[
 say('start','Nera','Please tell me you are the rescue party.','roan'),say('roan','Roan','We are a party. The rescue part is new.','yuufa'),say('yuufa','Yuufa','Then we should start before the cart notices.','ask'),choice('ask','Who is still missing?','Tell me where to help.','driver_first','driver_first'),say('driver_first','Nera','The driver. And a parcel with a blue cord. Driver first. Please.','rescue'),gate('rescue',3,'rescued'),say('rescued','Driver','I thought you would take the parcel and leave.','louder'),say('louder','Yuufa','You were considerably louder than the parcel.','reports'),say('reports','Nera','It contains missing-person reports. Someone has been collecting the originals.','finish'),end('finish',3)],
 [say('start','Hald','Your first job fixes your career in normal play. You can promote and be reborn within that path, but cannot change to another.','limits'),say('limits','Yuufa','And discover which limits are yours to change.','consent'),choice('consent','I understand. This is my path.','I need more time.','job_proof','more_time'),say('more_time','Hald','Good. A considered answer is cheaper than a lifelong mistake.','close'),close('close'),gate('job_proof',1,'role'),role('role','vanguard'),say('vanguard','Roan','Then I will trust you to choose where we stand.','pathfinder',1),say('pathfinder','Roan','Then show me what I cannot see from behind a shield.','keeper',2),say('keeper','Roan','Then I will listen when you tell me we cannot keep pushing.','commission',4),say('commission','Hald',"The reports lead to Payon. You are not commissioned to solve a kingdom's problems. You are commissioned to deliver a parcel.",'names'),say('names','Nera','And perhaps ask why every copy has a different name.','finish'),end('finish',1)],
 [say('start','Roan','Do you think a real adventurer knows when they have started?','bill'),say('bill','Yuufa','Usually when the bill arrives.','answer'),choice('answer','We started when we went back for the driver.','Ask me after Payon.','rule','rule'),say('rule','Roan','Then let us make one rule. If someone falls behind, we notice.','inconvenient'),say('inconvenient','Yuufa','And if noticing is inconvenient?','return'),say('return','Player','We go back.','offer'),say('offer','Yuufa','Then would you like us to travel with you? Roan can hold a road. I can help keep you both on it.','consent'),choice('consent','Come with me. We go together.','I need a little more time.','joined','later'),say('later','Roan','We will be here. No one gets left behind because they needed a moment.','close'),close('close'),join('joined',(1<<1)|(1<<4),'welcome'),say('welcome','Yuufa','Then it is settled. Try not to make our first rule necessary before lunch.','finish'),end('finish',1)]]
def guild(label,next):return dict(label=label,kind=8,next=next)
from chapter2_graphs200 import make_chapter2
scenes.extend(make_chapter2(say,choice,gate,end,close,join,guild))
# Expression IDs: neutral0,happy1,angry2,sad3,worried4,surprised5.
expressions=[{'start':4,'roan':4,'driver_first':4,'rescued':3,'louder':1,'reports':4},{'limits':1,'more_time':1,'names':4},{'start':4,'bill':1,'welcome':1},{'start':4,'weather':4,'daughter':4,'evidence':3,'distinction':2},{'start':4,'veyr':0,'people':0,'driver':4,'permission':1,'thanks':1},{'start':1,'heroic':1,'short':1,'recognize':4,'named':1,'staying':1,'maya':1,'welcome':1}]
for cursor,cues in enumerate(expressions):
 for node in scenes[cursor]:
  if node['kind']==1:node['expression']=cues.get(node['label'],0)
index=[];out=(D/'chapter1-scenes.bin').open('wb');manifest=[]
for cursor,nodes in enumerate(scenes):
 labels={n['label']:i for i,n in enumerate(nodes)};pool=bytearray(b'\0');strings={'':0}
 def string(text):
  if text not in strings:strings[text]=len(pool);pool.extend(text.encode('ascii')+b'\0')
  return strings[text]
 records=bytearray()
 for node in nodes:
  opts=node.get('options',['','']);targets=node.get('targets',['','']);nxt=labels.get(node.get('next',''),65535)
  records.extend(struct.pack('<BBHIIIIHHII',node['kind'],node.get('role',0),nxt,string(node.get('speaker','')),string(node.get('text','')),string(opts[0]),string(opts[1]),labels.get(targets[0],65535),labels.get(targets[1],65535),node.get('required',0),node.get('expression',0)))
 raw=struct.pack('<4sHHIHH',b'RSC2',1,len(nodes),len(pool),cursor,0)+records+pool;packed=zlib.compress(raw,6);index.append((out.tell(),len(packed),len(raw),zlib.crc32(raw)));out.write(packed);manifest.append(dict(scene=f'{cursor//3+1}.{cursor%3+1}',cursor=cursor,nodes=nodes))
out.close();h='/* MIT. First two chapters: typed scene-pack bounds. Not activated until staging is audited. */\n#ifndef MYRO_CHAPTER1_DATA200_H\n#define MYRO_CHAPTER1_DATA200_H\n#define CHAPTER1_RESCUE_GATE200 %du\nstatic const struct{unsigned offset,packed,raw,crc;}chapter1Index200[]={\n'.replace('%du',str(next(i for i,n in enumerate(scenes[0])if n['label']=='rescue'))+'u')+'#define CAMPAIGN_TYPED_SCENES200 6u\n#define CHAPTER2_INVESTIGATION_GATE200 '+str(next(i for i,n in enumerate(scenes[3])if n['label']=='investigate'))+'u\n'+''.join('{%du,%du,%du,%du},\n'%x for x in index)+'};\n#define CHAPTER1_FILE_BYTES200 %du\n#endif\n'%(D/'chapter1-scenes.bin').stat().st_size;(S/'chapter1_data200.h').write_text(h);(B/'Preparation/Chapter1-Graph200.json').write_text(json.dumps(manifest,indent=2));print('Compiled six typed Chapter1/2 graphs:',(D/'chapter1-scenes.bin').stat().st_size,'bytes')

(S/"chapter2_gates200.h").write_text("/* Typed Chapter2 checkpoint identities; generated with the dialogue pack. */\n#ifndef MYRO_CHAPTER2_GATES200_H\n#define MYRO_CHAPTER2_GATES200_H\n"+"".join("#define "+macro+" "+str(next(i for i,n in enumerate(scenes[cursor])if n["label"]==label))+"u\n"for cursor,label,macro in [(3,"investigate","CHAPTER2_WITNESS_GATE200"),(4,"ledger","CHAPTER2_LEDGER_GATE200"),(5,"guild","CHAPTER2_GUILD_GATE200")])+"#endif\n")
