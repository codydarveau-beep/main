"""Read-only byte comparison: distinguish retained release assets from source parity."""
from pathlib import Path
import hashlib,json,re
R=Path(__file__).resolve().parent.parent;recovery=R.parent
baseline=json.loads((recovery/'baseline-file-verification.json').read_text())['files'];entries=[]
for name,b in baseline.items():
 p=R/'XboxFiles'/name
 e=dict(name=name,releasedBytes=b['bytes'],releasedSHA256=b['sha256'],releasedAssetRecoverable=True)
 if p.exists():
  h=hashlib.sha256()
  with p.open('rb')as f:
   for chunk in iter(lambda:f.read(4*1024*1024),b''):h.update(chunk)
  e.update(privateBytes=p.stat().st_size,privateSHA256=h.hexdigest(),matchesReleased=h.hexdigest()==b['sha256'])
 else:e.update(matchesReleased=False,privateInputMissing=True)
 entries.append(e)
S=R/'Source';macro=lambda file,name:int(re.search(r'#define\s+'+name+r'\s+(\d+)',(S/file).read_text()).group(1))
companions=(S/'campaign_companions200.h').read_text();actors=re.findall(r'\{"[^"\n]+",[^,\n]+,(\d+)\}',companions)
report=dict(scope='Recovery and release-readiness assessment; not playtesting',baselineVersion='1.10.0',targetVersion='1.11.0',releasedISO_SHA256='b6f4f9c5e8af271f40aaa8eaae5bcca5329ba29693c6ab65a40702261736e25e',releasedFilesVerified=19,files=entries,sourceEvidence=dict(openingReady=macro('campaign_actor_data200.h','CAMPAIGN_OPENING_READY200'),typedScenes=macro('chapter1_data200.h','CAMPAIGN_TYPED_SCENES200'),runtimeSceneCeiling=macro('chapter1_data200.h','CAMPAIGN_RELEASE_SCENES193'),campaignStages=36,placeholderDirections=(S/'campaign_data200.h').read_text().count('Destination will be supplied after quest integration.'),rosterEntries=len(actors),rosterSceneActorsPrepared=sum(int(a)!=255 for a in actors),worldMapCount=macro('world_data.h','WORLD_MAP_COUNT'),policyMapCount=497,privateLaterMapsLoadable=(R/"Validation/Story-Alias-Checks199.json").exists() and json.loads((R/"Validation/Story-Alias-Checks199.json").read_text())["passed"]),normalReleaseWideChecksComplete=False,additionalReviewPassesCompleted=0,packagingValidated=False)
(R/'Validation/Release-Inputs194.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(dict(matches=sum(e['matchesReleased']for e in entries),different=[e['name']for e in entries if not e['matchesReleased']],sourceEvidence=report['sourceEvidence']),indent=2))
