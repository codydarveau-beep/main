from pathlib import Path
import subprocess,os,tempfile,zipfile,json,struct,zlib,shutil,csv,io,hashlib
r=Path('/workspace/myro');source=(r/'checks/test_expanded_collector59.py').read_text();ns={};exec(source[source.index('def grf('):source.index('with tempfile.TemporaryDirectory')],dict(zlib=zlib,struct=struct),ns)
env=dict(os.environ,XDG_CACHE_HOME=str(r/'pwsh/cache'),XDG_CONFIG_HOME=str(r/'pwsh/config'),XDG_DATA_HOME=str(r/'pwsh/data'))
with tempfile.TemporaryDirectory(prefix='Mercenary Layers180 ')as tmp:
 d=Path(tmp);tool=d/'Tool';shutil.copytree(r/'asset-request200/Campaign-Actors',tool);client=d/'Client';client.mkdir();out=d/'Output';out.mkdir()
 requested={line.split('\t')[0]for line in (tool/'Resource-Requests.tsv').read_text(encoding='utf-8-sig').splitlines()if line}
 resources={key:(bytes(64)if key.endswith('.act')else('fixture '+key).encode())for key in requested}
 extra='data\\texture\\effect\\unmapped_visual.str';resources[extra]=b'effect inventory only';resources['data\\sprite\\unrelated.spr']=b'not collected'
 original=ns['grf'](resources);(client/'data.grf').write_bytes(original)
 cmd=[str(r/'pwsh/bin/pwsh'),'-NoProfile','-File',str(tool/'Collect-Campaign-Actors.ps1'),'-ClientRoot',str(client),'-OutputFolder',str(out),'-NoPause']
 p=subprocess.run(cmd,env=env,capture_output=True,text=True);assert p.returncode==0,(p.stdout,p.stderr)
 with zipfile.ZipFile(next(out.glob('*.zip')))as z:
  assert z.testzip()is None;report=json.loads(z.read('Report.json'));assert report['complete']and not report['errors']and not report['missing']
  rows=list(csv.DictReader(io.StringIO(z.read('Assets.csv').decode('utf-8-sig'))));bykey={row['virtual_path']:row for row in rows}
  assert requested<=set(bykey)and extra not in bykey and 'data\\sprite\\unrelated.spr'not in bykey
  for row in rows:
   data=z.read(row['payload']);assert len(data)==int(row['bytes'])and hashlib.sha256(data).hexdigest()==row['sha256']
 assert(client/'data.grf').read_bytes()==original
 print('PASS2.0 shipped PowerShell/C# collector: exact14 human body requests,unrelated resources excluded,all output CRC/length/SHA and read-only client archive.')
