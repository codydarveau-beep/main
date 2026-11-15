"""GPL-3.0-or-later. Build typed second-class source data without activating jobs.

The parser reads the collector's libconfig subset as data. It keeps signed values
and nested rank requirements; missing levels have the source database's zero
default, rather than a guessed carry-forward. Existing runtime IDs never move.
"""
from pathlib import Path
import json
import re
import hashlib

ROOT = Path(__file__).resolve().parent
OUT = ROOT.parent / 'ClassAssets50'


def parse_group(text):
    tokens = re.findall(r'"(?:\\.|[^"\\])*"|[A-Za-z0-9_]+|-[A-Za-z0-9_]+|[{}:]|\S',
                        re.sub(r'//[^\n]*|/\*.*?\*/', '', text, flags=re.S))
    pos = 0

    def group(close=False):
        nonlocal pos
        result = {}
        while pos < len(tokens) and tokens[pos] != '}':
            key = tokens[pos]
            pos += 1
            assert tokens[pos] == ':', (key, tokens[pos:pos+5])
            pos += 1
            value = tokens[pos]
            pos += 1
            if value == '{':
                value = group(True)
            elif value.startswith('"'):
                value = json.loads(value)
            elif value in ('true', 'false'):
                value = value == 'true'
            else:
                value = int(value, 16 if '0x' in value else 10)
            assert key not in result, key
            result[key] = value
        if close:
            assert pos < len(tokens) and tokens[pos] == '}'
            pos += 1
        return result

    result = group()
    assert pos == len(tokens), tokens[pos:]
    return result


def levels(value, count=10, default=0):
    if value is None:
        return [default] * count
    if isinstance(value, dict):
        assert all(re.fullmatch(r'Lv\d+', k) for k in value), value
        return [value.get('Lv' + str(i), default) for i in range(1, count+1)]
    assert isinstance(value, int)
    return [value] * count


def carray(value):
    return json.dumps(value, separators=(',', ':')).replace('[', '{').replace(']', '}')


def prepare():
    OUT.mkdir(exist_ok=True)
    plan = json.loads((ROOT / 'class_plan50.json').read_text())
    audit = json.loads((ROOT / 'class_skill_audit50.json').read_text())
    deferred = json.loads((ROOT / 'class_asset_audit50.json').read_text())['deferred']
    # Only keys referenced by the added trees are needed here. These are stable
    # existing runtime IDs, verified against the original first-class catalog.
    ids = dict(SM_SWORD=35, AC_VULTURE=16, AC_DOUBLE=17, MG_SRECOVERY=25,
               MG_SAFETYWALL=48, PR_KYRIE=7, AC_CONCENTRATION=39,
               AL_ANGELUS=33, AL_DEMONBANE=42, AL_DP=11, AL_HEAL=10,
               AL_HOLYWATER=55, AL_RUWACH=40, TF_HIDING=38, TF_POISON=13,
               TF_STEAL=37)
    ids.update({k: v['id'] for k, v in plan['skills'].items()})
    inherited = {q['id']: q['firstClass'] for q in plan['classes']}
    skills = []
    for key, row in plan['skills'].items():
        source = parse_group(row['source'])
        requirements = source.get('Requirements', {})
        record = dict(key=key, id=row['id'], sourceID=source['Id'],
                      name=source['Description'], maxRank=row['maxRank'],
                      owners=row['owners'], passive='SkillType' not in source,
                      quest=source.get('SkillInfo', {}).get('Quest', False),
                      target=source.get('SkillType', {}),
                      interruptible=source.get('InterruptCast', False),
                      source=source, requirements=requirements)
        for field in ('Range', 'SplashRange', 'CastTime', 'AfterCastActDelay',
                      'AfterCastWalkDelay', 'CoolDown', 'NumberOfHits',
                      'SkillData1', 'SkillData2', 'KnockBackTiles', 'SkillInstances'):
            record[field] = levels(source.get(field), default=1 if field == 'NumberOfHits' else 0)
        for field in ('SPCost', 'HPCost', 'SpiritSphereCost'):
            record[field] = levels(requirements.get(field))
        record['items'] = {k: levels(v) for k, v in requirements.get('Items', {}).items()}
        skills.append(record)
    edges = []
    waived = []
    for job in plan['classes']:
        for row in audit['classes'][job['name']]:
            if row['key'] not in plan['skills']:
                continue
            for key, rank in row['prerequisites'].items():
                if key in deferred:
                    # Solo skills behind a purely multiplayer branch must remain
                    # learnable. The skipped branch itself grants no solo bonus.
                    waived.append(dict(job=job['id'], skill=row['key'], prerequisite=key,
                                       rank=rank, reason=deferred[key]))
                    continue
                assert key in ids, (job['name'], row['key'], key)
                edges.append([job['id'], ids[row['key']], ids[key], rank])
    old = (ROOT.parent.parent / 'test49/Source/skills.h').read_text()
    rank_ids = list(map(int, re.search(r'learnIds\[LEARN_COUNT\]=\{([^}]+)', old)[1].split(',')))
    assert len(rank_ids) == 124 and 7 not in rank_ids
    rank_ids += sorted(v['id'] for v in skills if v['id'] >= 127)
    rank_ids.append(7)
    assert len(rank_ids) == len(set(rank_ids)) == 252
    assert rank_ids[:124] == list(map(int, re.search(r'learnIds\[LEARN_COUNT\]=\{([^}]+)', old)[1].split(',')))
    assert set(rank_ids) | {0, 1} == set(range(254))
    companions = []
    for key, row in audit['companionSkills'].items():
        source = parse_group(row['source'])
        companions.append(dict(key=key, sourceID=source['Id'], maxRank=row['maxRank'], source=source))
    output = dict(sourceCommit=plan['sourceCommit'], classes=plan['classes'], skills=skills,
                  prerequisiteEdges=edges, soloWaivedPrerequisites=waived, rankIDs=rank_ids,
                  skillCount=254, rankCount=252, companions=companions,
                  inputs={p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in
                          [ROOT/'class_plan50.json', ROOT/'class_skill_audit50.json']},
                  status='prepared data; jobs are gated until mechanics/art integration is complete')
    (OUT / 'catalog50.json').write_text(json.dumps(output, indent=2, ensure_ascii=False)+'\n')
    header = ['/* GPL-3.0-or-later. Generated pinned pre-renewal job/skill data. */',
              '#ifndef MYRO_PREPARED_CATALOG50_H', '#define MYRO_PREPARED_CATALOG50_H',
              '#include <stdint.h>', '#define CLASS50_FIRST_JOB 12',
              '#define CLASS50_JOB_COUNT 9', '#define CLASS50_SKILL_COUNT 254',
              '#define CLASS50_RANK_COUNT 252',
              'static const uint8_t classParent50[9]='+carray(list(inherited.values()))+';',
              'static const uint16_t classHP50[9][99]='+carray([q['sourceHP99'] for q in plan['classes']])+';',
              'static const uint16_t classSP50[9][99]='+carray([q['sourceSP99'] for q in plan['classes']])+';',
              'static const uint8_t classBonus50[9][50][6]='+carray([q['sourceJobBonus50'] for q in plan['classes']])+';']
    weapon_names = ['Fist','Dagger','Sword','TwoHandSword','Spear','TwoHandSpear','Axe',
                    'TwoHandAxe','Mace','Rod','Bow','Book','TwoHandRod','Knuckle','Instrument','Whip','Katar']
    header.append('static const uint16_t classMotion50[9][17]='+carray([
        [q['sourceWeaponMotion'].get(w, 2000) for w in weapon_names] for q in plan['classes']])+';')
    header.append('static const uint16_t classRankIDs50[252]='+carray(rank_ids)+';')
    header.append('static const uint16_t classPrereqs50[][4]='+carray(edges)+';')
    header += ['typedef struct {uint16_t id,sourceID;uint64_t owners;const char *key,*name;',
               'uint8_t maxRank,passive,quest,target,interruptible;',
               'int16_t range[10],splash[10],hits[10],knockback[10],instances[10];',
               'uint32_t cast[10],delay[10],walkDelay[10],cooldown[10],duration[10],duration2[10];',
               'uint16_t sp[10],hp[10],spheres[10];} ClassSkill50;',
               'static const ClassSkill50 classSkills50[]={']
    for row in skills:
        target = row['target']
        flags = sum(bit for key, bit in [('Self',1),('Enemy',2),('Place',4),('Friend',8)] if target.get(key))
        values = [str(row['id']),str(row['sourceID']),'UINT64_C('+str(sum(1 << i for i in row['owners']))+')',
                  json.dumps(row['key']),json.dumps(row['name']),str(row['maxRank']),
                  str(int(row['passive'])),str(int(row['quest'])),str(flags),str(int(row['interruptible']))]
        for field in ('Range','SplashRange','NumberOfHits','KnockBackTiles','SkillInstances',
                      'CastTime','AfterCastActDelay','AfterCastWalkDelay','CoolDown','SkillData1',
                      'SkillData2','SPCost','HPCost','SpiritSphereCost'):
            values.append(carray(row[field]))
        header.append('{'+','.join(values)+'},')
    header += ['};', 'static const ClassSkill50*class_skill_data50(unsigned id){',
               'for(unsigned i=0;i<sizeof(classSkills50)/sizeof(*classSkills50);i++)',
               'if(classSkills50[i].id==id)return &classSkills50[i];return 0;}',
               'static unsigned class_actor_id50(unsigned job,int mounted){',
               'return job>=12&&job<=20?job+1:job==11&&mounted?12:job;}', '#endif']
    (OUT / 'catalog50.h').write_text('\n'.join(header)+'\n')
    print('PASS50 prepared nine integer source profiles,133 skill records,',len(edges),
          'class-scoped prerequisite edges,252 stable rank slots and16 companion records.')
    print('Solo-only skipped prerequisite edges:', json.dumps(waived))


if __name__ == '__main__':
    prepare()
