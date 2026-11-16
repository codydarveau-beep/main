"""Create a new immutable local developer backup from the pushed source commit."""
from pathlib import Path
import datetime, hashlib, io, json, os, subprocess, tarfile, tempfile

R = Path(__file__).resolve().parent.parent
G = R.parent / 'checkpoint'
def git(*args):
    return subprocess.check_output(['git', '-C', str(G), *args], text=True).strip()
commit = git('rev-parse', 'HEAD')
branch = 'recovery/ragnarok-1.11.0-inventory'
tag = 'ragnarok-1.11.0-dev-benchmark214'
assert git('rev-parse', 'refs/tags/' + tag + '^{}') == commit, 'Pin the checkpoint tag first.'
assert git('rev-parse', 'refs/remotes/origin/' + branch) == commit, 'Push the complete source checkpoint first.'
report = json.loads((R / 'Validation/Developer-Benchmark214.json').read_text())
assert report['passed'] and report['additionalReviewPassesCompleted'] == 0 and not report['additionalReviewPassesStarted']
assert not report['normalReleaseWideChecksComplete'] and not report['packagingValidated']
def digest(path):
    with path.open('rb') as f:
        return hashlib.file_digest(f, 'sha256').hexdigest()
for entry in report['sourceFiles'] + report['nativeArtifacts']:
    assert digest(R / entry['path']) == entry['sha256'], entry['path']
tracked_report = subprocess.check_output(['git', '-C', str(G), 'show', commit + ':reconstruction/rebuild111/Validation/Developer-Benchmark214.json'])
assert tracked_report == (R / 'Validation/Developer-Benchmark214.json').read_bytes(), 'Checkpoint the final benchmark report first.'
stamp = datetime.datetime.now(datetime.timezone.utc).strftime('%Y%m%dT%H%M%SZ')
directory = R.parent / 'benchmarks' / ('Developer-Benchmark214-' + stamp)
directory.mkdir(parents=True, exist_ok=False)
archive = directory / 'Ragnarok-1.11.0-DEVELOPER-SAVEPOINT214.tar.gz'
manifest = []
verify = b'''"""Verify an extracted developer backup; does not install or run the game."""
from pathlib import Path
import hashlib,json
base=Path(__file__).resolve().parent
data=json.loads((base/'manifest.json').read_text())
for row in data['files']:
 p=base/row['path']
 assert p.is_file(),row['path']
 with p.open('rb')as f: actual=hashlib.file_digest(f,'sha256').hexdigest()
 assert actual==row['sha256'],row['path']
 assert p.stat().st_size==row['bytes'],row['path']
print('PASS immutable developer backup integrity; this is not a release patch or playtest.')
'''
baseline = json.loads((R / 'Validation/Release-Inputs194.json').read_text())
receipt = dict(label='Developer-Benchmark214', createdUTC=stamp, sourceCommit=commit, sourceBranch=branch, sourceTag=tag,
    sourceURL='https://github.com/codydarveau-beep/main/commit/' + commit,
    sourceDigest=report['sourceDigest'], nativeArtifacts=report['nativeArtifacts'],
    additionalReviewPassesCompleted=0, additionalReviewPassesStarted=False, normalReleaseWideChecksComplete=False,
    privateExecutable='development build only', releasePatch=False, originalXboxPlaytested=False, xemuPlaytested=False,
    baselineISO=dict(path=str(R.parent / 'released-1.10.0.iso'), bytes=1889075200, sha256=report['baselineISO_SHA256'], included=False),
    releasedContentReferences=[row for row in baseline['files'] if row['name'] != 'default.xbe'],
    restore='Extract into a new directory and run python3 verify.py. Read SOURCE/Preparation/Developer-Benchmark214.md before development. Restore unchanged runtime content from the exact released baseline; preserve the existing workspace.')
readme = ('# Ragnarok Offline developer savepoint 214\n\n'
    'This archive preserves an unfinished development checkpoint. It is not the 1.11.0 ZIP patch and is not ready for a playthrough.\n\n'
    'Extract into a NEW directory, then run `python3 verify.py`. Read `SOURCE/Preparation/Developer-Benchmark214.md` and `receipt.json`.\n\n'
    '`SOURCE/` is the exact pushed source checkpoint and reports. `PRIVATE/` contains the private development native build and stack metadata. '
    '`REFERENCE/` contains the released executable and manifest used for independent native comparisons. `ADDED_RUNTIME/` preserves added runtime assets. '
    'The unchanged released content packs remain recoverable from the exact retained 1.10.0 ISO; their hashes are in the receipt.\n\n'
    'Both additional review passes remain unstarted. Host tests/native compilation are not Xbox or Xemu playtests.\n').encode()
with tempfile.TemporaryDirectory(dir=directory) as temporary:
    source_tar = Path(temporary) / 'source.tar'
    with source_tar.open('wb') as out:
        subprocess.run(['git', '-C', str(G), 'archive', '--format=tar', '--prefix=SOURCE/', commit + ':reconstruction/rebuild111'], stdout=out, check=True)
    with tarfile.open(archive, 'x:gz', compresslevel=6) as backup:
        def add(name, data):
            assert not name.startswith('/') and '..' not in Path(name).parts
            item = tarfile.TarInfo(name); item.size = len(data); item.mode = 0o600
            backup.addfile(item, io.BytesIO(data))
            manifest.append(dict(path=name, bytes=len(data), sha256=hashlib.sha256(data).hexdigest()))
        with tarfile.open(source_tar) as source:
            for item in source:
                if item.isfile():
                    add(item.name, source.extractfile(item).read())
        for relative in ['XboxFiles/default.xbe', 'Source/main.exe', 'Source/main.su']:
            add('PRIVATE/' + Path(relative).name, (R / relative).read_bytes())
        reference = R.parent / 'packet194/released-default.xbe'
        released_xbe = next(row for row in baseline['files'] if row['name'] == 'default.xbe')
        assert digest(reference) == released_xbe['releasedSHA256']
        add('REFERENCE/released-default.xbe', reference.read_bytes())
        add('REFERENCE/baseline-file-verification.json', (R.parent / 'baseline-file-verification.json').read_bytes())
        known = {row['name'] for row in baseline['files']}
        for path in sorted((R / 'XboxFiles').iterdir()):
            if path.is_file() and path.name not in known:
                add('ADDED_RUNTIME/' + path.name, path.read_bytes())
        add('README.md', readme)
        add('receipt.json', (json.dumps(receipt, indent=2) + '\n').encode())
        add('verify.py', verify)
        data = (json.dumps(dict(files=manifest, sourceCommit=commit, releasePatch=False), indent=2) + '\n').encode()
        item = tarfile.TarInfo('manifest.json'); item.size = len(data); item.mode = 0o600
        backup.addfile(item, io.BytesIO(data))
# Independently read every archived entry back, before making the savepoint immutable.
with tarfile.open(archive) as backup:
    stored = json.load(backup.extractfile('manifest.json'))
    for row in stored['files']:
        content = backup.extractfile(row['path']).read()
        assert len(content) == row['bytes'] and hashlib.sha256(content).hexdigest() == row['sha256'], row['path']
archive_sha = digest(archive)
receipt.update(archive=str(archive), archiveBytes=archive.stat().st_size, archiveSHA256=archive_sha,
    archivedFiles=len(manifest), archiveReadbackVerified=True)
(directory / 'receipt.json').write_text(json.dumps(receipt, indent=2) + '\n')
(directory / 'README.md').write_bytes(readme)
(directory / (archive.name + '.sha256')).write_text(archive_sha + '  ' + archive.name + '\n')
os.chmod(archive, 0o400)
for path in directory.iterdir():
    if path.is_file() and path != archive:
        os.chmod(path, 0o444)
print(json.dumps(dict(directory=str(directory), archive=str(archive), receipt=str(directory / 'receipt.json'), verified=True, sourceCommit=commit), indent=2))
