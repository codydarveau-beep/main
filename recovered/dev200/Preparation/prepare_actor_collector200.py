from pathlib import Path
import shutil,hashlib,zipfile,json,re
R=Path('/workspace/myro');O=R/'asset-request200/Campaign-Actors';O.mkdir(parents=True,exist_ok=True);T=R/'asset-request69/Appearance-Effects'
for n in ['GrfCrypt.cs','Reader.cs','Binary.cs','GPL-3.0.txt']:shutil.copyfile(T/n,O/n)
for n in ['Map-Requests.tsv','Monster-Requests.tsv','Model3D-Requests.tsv','Item-Requests.tsv','Resource-Prefixes.tsv','Already-Collected.tsv']:(O/n).write_text('')
requests=['data\\sprite\\인간족\\몸통\\여\\'+name+'_여.'+ext for name in ['초보자','검사','마법사','성직자','도둑','궁수','상인']for ext in ['spr','act']]
(O/'Resource-Requests.tsv').write_text(''.join(p+'\tcampaign-female-player-body\n'for p in requests),encoding='utf-8-sig')
s=(T/'WorldMaps.cs').read_text(encoding='utf-8-sig').replace('RO-1.8.1-Assets-Appearance-Effects-','RO-2.0.0-Assets-Campaign-Actors-').replace('MyRO1.8.1 original appearance and remaining effect resources','MyRO2.0.0 source companion actor bodies')
a=s.index('    foreach(var request in Table(manifests,"Resource-Requests.tsv",2))');b=s.index('    foreach(var request in Table(manifests,"Resource-Prefixes.tsv",4))',a);s=s[:a]+'    foreach(var request in Table(manifests,"Resource-Requests.tsv",2))w.Get(request[0],request[1],true);\n'+s[b:];(O/'WorldMaps.cs').write_text(s,encoding='utf-8-sig')
s=(T/'Collect-Monster-Races.ps1').read_text(encoding='utf-8-sig').replace('original hairstyles, compatible palettes and remaining effect layers','source body sprites for the campaign companions').replace('RO-1.8.1-Appearance-Effects-Error-','RO-2.0.0-Campaign-Actors-Error-');(O/'Collect-Campaign-Actors.ps1').write_text(s,encoding='utf-8-sig');(O/'Collect-Campaign-Actors.cmd').write_bytes(b'@echo off\r\npowershell.exe -NoProfile -STA -ExecutionPolicy Bypass -File "%~dp0Collect-Campaign-Actors.ps1" %*\r\necho.\r\npause\r\n')
(O/'START-HERE.txt').write_text('MyRO2.0.0 - source companion body sprites\n\nExtract this folder and run Collect-Campaign-Actors.cmd. Select the same RO\nclient folder as usual if prompted. Send every ZIP part it creates.\n\nRequests only14 female first-job body SPR/ACT files from existing client\narchives. These source images are needed to stage and animate companions;\nthe game already contains the corresponding heads. No maps, items, music,\nwhole sprite trees or game saves are collected. The client files are read\nonly. If any files are missing, send the partial output for review.\n',encoding='utf-8-sig')
p=O.parent/'MyRO-2.0.0-Campaign-Actors-Collector.zip'
with zipfile.ZipFile(p,'w',zipfile.ZIP_DEFLATED)as z:
 for f in sorted(O.iterdir()):z.write(f,f.name)
with zipfile.ZipFile(p)as z:assert z.testzip()is None
(R/'dev200/Preparation/Actor-Collector200.json').write_text(json.dumps({'requests':requests,'bytes':p.stat().st_size,'sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'path':str(p)},indent=2,ensure_ascii=False)+'\n');print('Prepared focused14-file campaign actor collector:',p.stat().st_size,'bytes')
