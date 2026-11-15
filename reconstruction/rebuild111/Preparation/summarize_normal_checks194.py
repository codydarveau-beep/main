"""Summarize normal checks without promoting blocked content/platform gates."""
from pathlib import Path
import json,hashlib
R=Path(__file__).resolve().parent.parent;V=R/'Validation'
load=lambda name:json.loads((V/name).read_text())
integration=load('Integration-Checks194.json');hud=load('HUD-Checks194.json');sdk=load('SDK-Checks194.json');native=load('Native-Checks194.json');inputs=load('Release-Inputs194.json')
assert integration['allPassed'] and len(integration['checks'])==6
assert all(x['passed']for x in integration['checks'])and hud['passed']and sdk['passed']and native['nativeCompiled']
assert native['xbeSHA256']==hashlib.sha256((R/'XboxFiles/default.xbe').read_bytes()).hexdigest()
assert 'PASS50a 1347' in (V/'formats194.log').read_text()
checks=[dict(name='six integration sanitizer suites',status='passed',evidence='Integration-Checks194.json'),dict(name='expanded current HUD sanitizer/bounds cases',status='passed',cases=hud['cases'],evidence='HUD-Checks194.json'),dict(name='SDK math/HUD cases',status='passed',cases=sdk['cases'],evidence='SDK-Checks194.json'),dict(name='production literal formats',status='passed',strings=1347,evidence='formats194.log'),dict(name='native build and known stack/artifact guards',status='passed',evidence='Native-Checks194.json'),dict(name='private vs released input reconciliation',status='assessed',matchingFiles=sum(x['matchesReleased']for x in inputs['files']),totalFiles=19,evidence='Release-Inputs194.json')]
for name,label in [('Content-Checks195.json','complete restored art catalogs through production readers'),('Scene-Checks195.json','released scene wire and checkpoint compatibility')]:
 report=load(name);assert report['passed'];checks.append(dict(name=label,status='passed',evidence=name))
blocked=['complete twelve-chapter implementation','released campaign/content reader compatibility','full companion roster and behavior','released guild/cabinet preservation','two later-story maps','complete native-job and chronology paths','full released-save compatibility including legacy sandbox','64 MB Xbox and Xemu runtime validation','complete release-candidate regression']
result=dict(phase='normal integration assessment',availableChecks=checks,normalReleaseWideChecksComplete=False,releaseReady=False,blockedGates=blocked,closureCriteria='RELEASE-GATES.md',additionalReviewPassesCompleted=0,additionalReviewPassesStarted=False,packagingValidated=False,postReviewPackagingGate='Exact-1.10.0 ZIP reconstruction/rejection/rollback validation, after both additional reviews',privateExecutable='development build only',originalXboxPlaytested=False,xemuPlaytested=False)
(V/'Normal-Release-Checks194.json').write_text(json.dumps(result,indent=2)+'\n')
integration.update(nativeCompiled=True,nativeArtifactReport='Native-Checks194.json',normalReleaseWideIntegrationComplete=False);(V/'Integration-Checks194.json').write_text(json.dumps(integration,indent=2)+'\n')
print('PASS available normal checks; release remains BLOCKED by',len(blocked),'explicit gates; extra reviews 0/2; no packaging.')
