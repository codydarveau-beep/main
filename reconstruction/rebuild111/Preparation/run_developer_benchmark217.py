"""Record a reproducible developer savepoint baseline; no target-playtest claim."""
from pathlib import Path
import argparse, datetime, hashlib, json, re, subprocess, sys

R = Path(__file__).resolve().parent.parent
V = R / 'Validation'
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--refresh', action='store_true', help='Rerun available integration suites before recording evidence.')
args = parser.parse_args()
suites = [
    'run_checks194.py', 'check_companion_cast201.py', 'check_companion_mage204.py',
    'check_companion_wizard_integration205.py', 'check_companion_elemental_integration211.py',
    'check_companion_soullinker_integration210.py', 'check_companion_archer_integration212.py',
    'check_companion_melee_integration213.py', 'check_companion_pip_integration214.py',
    'check_companion_potion215.py', 'check_companion_potion_integration215.py',
    'check_companion_maya_basic215.py', 'check_companion_maya_physical215.py',
    'check_companion_performer_cast216.py', 'check_companion_performer_impact216.py',
    'check_companion_performer_integration216.py', 'check_companion_blacksmith_cast217.py',
    'check_companion_blacksmith_impact217.py', 'check_companion_blacksmith_basic217.py',
    'check_companion_blacksmith_integration217.py',
]
if args.refresh:
    with (V / 'developer-benchmark-refresh217.log').open('w') as log:
        for script in suites:
            subprocess.run([sys.executable, str(R / 'Preparation' / script)], cwd=R, stdout=log, stderr=subprocess.STDOUT, check=True)
subprocess.run([sys.executable, str(R / 'Preparation/check_native194.py')], cwd=R, stdout=(V / 'developer-benchmark-native217.log').open('w'), check=True)
subprocess.run([sys.executable, str(R / 'Preparation/summarize_normal_checks194.py')], cwd=R, check=True)
normal = json.loads((V / 'Normal-Release-Checks194.json').read_text())
native = json.loads((V / 'Native-Checks194.json').read_text())
def digest(path):
    with path.open('rb') as f:
        return hashlib.file_digest(f, 'sha256').hexdigest()
assert native['nativeCompiled'] and digest(R / 'XboxFiles/default.xbe') == native['xbeSHA256']
evidence = []
for check in normal['availableChecks']:
    path = V / check['evidence']
    assert path.is_file(), path
    evidence.append(dict(name=check['name'], status=check['status'], path=str(path.relative_to(R)), sha256=digest(path)))
sources = []
guards = {}
for path in sorted((R / 'Source').rglob('*')):
    if not path.is_file() or path.suffix not in ['.c', '.h', '.s', '.inc'] and path.name != 'Makefile':
        continue
    sources.append(dict(path=str(path.relative_to(R)), sha256=digest(path)))
    if path.suffix == '.h':
        for name in ['CAMPAIGN_RELEASE_SCENES193', 'CAMPAIGN_OPENING_READY200']:
            found = re.search(r'^#define\s+' + name + r'\s+(\d+)', path.read_text(), re.M)
            if found:
                guards[name] = int(found[1])
assert len(guards) == 2
report = dict(
    benchmark='Developer-Benchmark217', createdUTC=datetime.datetime.now(datetime.timezone.utc).isoformat(),
    purpose='Reproducible development checkpoint and handoff baseline; not a performance/FPS measurement or final release gate.',
    passed=True, refreshedIntegrationSuites=args.refresh, suiteCommands=suites, evidence=evidence,
    sourceDigest=hashlib.sha256(json.dumps(sources, sort_keys=True).encode()).hexdigest(), sourceFiles=sources,
    nativeArtifacts=[dict(path=relative, bytes=(R / relative).stat().st_size, sha256=digest(R / relative)) for relative in ['XboxFiles/default.xbe', 'Source/main.exe', 'Source/main.su']],
    activationGuards=guards, baselineVersion='1.10.0', targetVersion='1.11.0',
    baselineISO_SHA256='b6f4f9c5e8af271f40aaa8eaae5bcca5329ba29693c6ab65a40702261736e25e',
    normalReleaseWideChecksComplete=normal['normalReleaseWideChecksComplete'],
    additionalReviewPassesCompleted=normal['additionalReviewPassesCompleted'],
    additionalReviewPassesStarted=normal['additionalReviewPassesStarted'], packagingValidated=normal['packagingValidated'],
    originalXboxPlaytested=False, xemuPlaytested=False,
    resumeGuide='Preparation/Developer-Benchmark217.md', limitations='See WORK-REMAINING.md and RELEASE-GATES.md; passing available checks does not complete missing functionality or target validation.'
)
(V / 'Developer-Benchmark217.json').write_text(json.dumps(report, indent=2) + '\n')
print('PASS developer checkpoint consistency; normal release work and both extra reviews remain separate.')
