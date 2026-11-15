"""Reconstructed chapter/region policy. Unmatched maps stop generation.

These reviewed-in-source family assignments are new reconstruction choices,
not a claim to have recovered the missing original 497-entry policy.
"""
from pathlib import Path
import json

ROOT = Path(__file__).resolve().parent.parent
PACKET = ROOT.parent / 'packet194'
names = json.loads((PACKET / 'RecoveredMetadata/released-map-names.json').read_text())
names += ['story_thana194', 'story_moc194']
assert len(names) == 497 and len(set(names)) == 497

# Ordinary first-career towns, their connected beginner fields and native
# classrooms remain reachable before the career commitment. Local native
# quest scripts still impose their own entry and promotion requirements.
groups = [
 (0, 0, 'First-career towns, native classrooms and beginner connectivity',
  'prt prontera izlude pay payon gef geffen in orcsdun01 orcsdun02 job monk iz izlu2dun alb2trea alb alberta treasure01 treasure02 mjo mjolnir cave himinn valkyrie new sec arena force p'),
 (6, 0, 'Geffen investigation and original adjacent dungeons', 'gefenia01 gefenia02 gefenia03 gefenia04 gl glast'),
 (9, 0, 'Desert chapter; explicit early-career exceptions below', 'moc anthell01 anthell02'),
 (12, 0, 'Northern relief chapter', 'alde aldeba aldebaran c'),
 (13, 0, 'Comodo chapter', 'beach cmd comodo'),
 (15, 0, 'Juno and industrial approaches', 'airplane airport ein einbech einbroch hu hugel jupe juperos mag yuno abyss odin y'),
 (16, 0, 'Lighthalzen investigation', 'lhz lighthalzen'),
 (18, 0, 'Eastern regional chapter', 'ama amatsu ayo ayothaya lou louyang'),
 (19, 0, 'Gonryun chapter', 'gon gonryun'),
 (21, 0, 'Umbala and Niflheim chapter', 'nif niflheim um umbala yggdrasil01'),
 (25, 0, 'Rachel and Veins investigation', 'ice ra rachel ve veins'),
 (27, 0, 'Thor approach', 'thor'),
 (28, 0, 'Abbey and Thanatos investigation', 'abbey01 abbey02 abbey03 nameless tha thana'),
 (12, 1, 'Winter dispatch', 'xmas'),
 (18, 2, 'Moscovia dispatch', 'moscovia mosk'),
 (18, 3, 'Brasilis dispatch', 'bra brasilis'),
 (35, 8, 'Splendide dispatch after Expedition completion', 'spl splendide'),
 (35, 9, 'Manuk dispatch after Expedition completion', 'man manuk'),
 (35, 11, 'Expedition dispatch', 'mid nyd'),
 (15, 12, 'Turtle Island dispatch', 'tur'),
 (20, 13, 'Jawaii dispatch', 'jawaii'),
 (16, 14, 'Kiel Hyre dispatch; original locked-room quests remain intact', 'kh'),
]
families = {}
for cursor, region, reason, words in groups:
    for word in words.split():
        assert word not in families, word
        families[word] = (cursor, region, reason)

exceptions = {
 'moc_fild01': (0, 0, 'Retained starter-town connectivity'),
 'moc_fild02': (0, 0, 'Retained starter-town connectivity'),
 'moc_fild03': (0, 0, 'Retained starter-town connectivity'),
 'moc_ruins': (1, 0, 'Retained early Merchant/Thief outpost access'),
 'moc_pryd01': (1, 0, 'Retained early Thief approach; native room warps remain'),
 'moc_prydb1': (1, 0, 'Retained early Thief room'),
 'que_ng': (1, 0, 'Retained early Ninja/Gunslinger classrooms'),
 'morocc': (35, 0, 'Retained post-catastrophe chronology'),
 'morocc_in': (35, 0, 'Retained post-catastrophe chronology'),
 'moc_fild22': (35, 0, 'Retained original encounter chronology'),
 'moc_fild22b': (35, 0, 'Same original encounter family; reconstructed restriction'),
 'moc_fild20': (31, 0, 'Retained breach chronology'),
 'moc_fild21': (31, 0, 'Retained breach chronology'),
 'guild_in194': (9, 0, 'Retained guild interior milestone'),
 'story_thana194': (28, 0, 'Retained story threshold; environment alias confirmed by designer'),
 'story_moc194': (33, 0, 'Retained story threshold; environment alias confirmed by designer'),
 'que_rachel': (25, 0, 'Rachel quest room'),
 'que_san04': (25, 0, 'Rachel quest room'),
 'que_temsky': (25, 0, 'Rachel quest room'),
 'que_thor': (27, 0, 'Thor quest room'),
 'que_sign01': (6, 0, 'Sign quest room; native quest conditions unchanged'),
 'que_sign02': (6, 0, 'Sign quest room; native quest conditions unchanged'),
 'que_ba': (13, 0, 'Bard quest room'),
 'que_dan01': (13, 0, 'Dancer quest room'),
 'que_dan02': (13, 0, 'Dancer quest room'),
 'que_hugel': (15, 0, 'Hugel quest room'),
 'que_bingo': (15, 0, 'Hugel original activity room'),
 'que_job01': (0, 0, 'Native career room'),
}
rows = []
for i, name in enumerate(names):
    excluded = '@' in name or name in {'z_agit', 'e_tower'}
    if excluded:
        cursor, region, reason = 37, 0, 'Excluded online party-instance/WoE content'
    elif name in exceptions:
        cursor, region, reason = exceptions[name]
    else:
        family = name.split('_')[0]
        assert family in families, f'Unreviewed map: {i} {name}'
        cursor, region, reason = families[family]
    rows.append(dict(id=i, name=name, minimumCursor=cursor, region=region,
                     excluded=excluded, reason=reason,
                     provenance='retained packet + explicit reconstructed chapter-family rules'))
assert rows[108]['name'] == 'moc_fild07'
assert rows[126]['name'] == 'moc_ruins' and rows[127]['name'] == 'morocc'
region_min = [37] * 17
for region, cursor in {1:12,2:18,3:18,8:35,9:35,11:35,12:15,13:20,14:16}.items():
    region_min[region-1] = cursor
assert all(0 <= r['minimumCursor'] <= 37 and 0 <= r['region'] <= 17 for r in rows)
text = '/* MIT. Reconstructed policy; provenance and every assignment are in Map-Policy194.json. */\n#ifndef MYRO_CAMPAIGN_ACCESS_DATA194_H\n#define MYRO_CAMPAIGN_ACCESS_DATA194_H\n#define CAMPAIGN_ACCESS_MAPS194 497u\n#define CAMPAIGN_REGIONS194 17u\n'
for name, values in [
 ('campaignMapMinimum194', [r['minimumCursor'] for r in rows]),
 ('campaignMapRegion194', [r['region'] for r in rows]),
 ('campaignMapExcluded194', [int(r['excluded']) for r in rows]),
 ('campaignRegionMinimum194', region_min),
]:
    text += 'static const unsigned char '+name+'[]={'+','.join(map(str,values))+'};\n'
text += '#endif\n'
(ROOT/'Source/campaign_access_data194.h').write_text(text)
(ROOT/'Preparation/Map-Policy194.json').write_text(json.dumps({'status':'Reconstructed, not recovered original policy', 'maps':rows},indent=2)+'\n')
print('Explicit policy:',len(rows),'maps;',sum(r['excluded'] for r in rows),'excluded; no unmatched/default-open maps')
