"""Record policy facts without turning missing values into open destinations."""
from pathlib import Path
import json

ROOT = Path(__file__).resolve().parent
names = json.loads((ROOT / 'RecoveredMetadata/released-map-names.json').read_text())
assert len(names) == 495
names += ['story_thana194', 'story_moc194']
minimums = {
    'moc_fild01': 0, 'moc_fild02': 0, 'moc_fild03': 0,
    'morocc': 35, 'morocc_in': 35, 'moc_fild22': 35,
    'moc_fild20': 31, 'moc_fild21': 31,
    'story_thana194': 28, 'story_moc194': 33, 'guild_in194': 9,
}
assert names[494:] == ['guild_in194', 'story_thana194', 'story_moc194']
regions = {1: 12, 2: 18, 3: 18, 8: 35, 9: 35, 11: 35, 12: 15, 13: 20, 14: 16}
rows = [{'id': i, 'name': name, 'minimumCursor': minimums.get(name),
         'region': None, 'evidence': 'packet section 11' if name in minimums else None}
        for i, name in enumerate(names)]
report = {
    'status': 'Evidence worksheet only; NOT a generated runtime policy',
    'maps': rows, 'knownRegionMinimums': regions,
    'reservedRegionPositions': [region - 1 for region in range(1, 18) if region not in regions],
    'reservedRegionPositionsAreZeroBased': True,
    'frontierPrerequisite': {'regions': [8, 9], 'completedRegion': 11},
    'earlyAccessQualitativeOnly': ['moc_ruins', 'moc_pryd01', 'moc_prydb1', 'que_ng'],
    'chronologyDependenciesOnMap127': [498, 504, 506, 1894, 1901, 1942, 1953, 1954,
                                    1955, 1956, 2011, 2738, 2739, 2740, 2742, 2744,
                                    2745, 2746, 2783, 3152, 3241, 3941],
    'runtimeHeaderGenerated': False,
    'generationBlockers': [
        'Complete map minimum-cursor and region assignments require reconstruction/review.',
        'Dependency abstract interpreter and full transitive table are not yet reconstructed.',
        'Two private later-story map implementations are unavailable.',
    ],
}
# Null is deliberately different from cursor zero or region zero. No generated
# C array is emitted until every row has evidence and a reviewed assignment.
(ROOT / 'map-policy-evidence.json').write_text(json.dumps(report, indent=2) + '\n')
print('Known numeric map minima:', len(minimums), '; unknown minima:', sum(r['minimumCursor'] is None for r in rows))
