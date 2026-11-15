"""Convert verified world assets once per map; resumable and bounded host cache."""
from pathlib import Path
import contextlib,csv,json,struct,time,traceback
from world_assets51 import WorldAssets51
from convert_world import ground
from convert_scenery import convert,AtlasPackingError
ROOT=Path(__file__).resolve().parent.parent
LIB=ROOT.parent/'asset-library/Test51-world-maps'

def run():
 assets=WorldAssets51(LIB/'Asset-Index.json')
 requests=list(csv.reader((LIB/'Map-Requests.tsv').open(),delimiter='\t'))
 results=[]
 for number,(region,name,music,minimap) in enumerate(requests,1):
  out=ROOT/'WorldAssets'/name;out.mkdir(parents=True,exist_ok=True)
  done=out/'CONVERSION51.json'
  if done.exists():
   results.append(json.loads(done.read_text()));continue
  started=time.monotonic()
  try:
   terrain=ground(assets,name,out,label=name)
   with (out/'scenery.log').open('w') as log,contextlib.redirect_stdout(log):
    for texture_limit in (128,96,64):
     try:
      scene=convert([],out,map_names=[name],assets=assets,emit_c=False,preview=False,texture_limit=texture_limit);break
     except AtlasPackingError:
      if texture_limit==64:raise
    scene['texture_limit']=texture_limit
   assert terrain['vertices']<=1000000, 'terrain exceeds native loader bound'
   assert max(terrain['atlas'])<=4096, 'ground atlas exceeds native loader bound'
   row=dict(map=name,region=region,terrain=terrain,scenery=scene,seconds=round(time.monotonic()-started,3),status='converted')
   done.write_text(json.dumps(row,ensure_ascii=False,indent=2))
  except Exception as e:
   row=dict(map=name,region=region,status='error',error=str(e));(out/'ERROR51.txt').write_text(traceback.format_exc())
  results.append(row)
  (ROOT/'WORLD-CONVERSION51.json').write_text(json.dumps(results,ensure_ascii=False,indent=2))
  print(number,len(requests),name,row['status'],row.get('error',''),flush=True)
 (ROOT/'WORLD-CONVERSION51.json').write_text(json.dumps(results,ensure_ascii=False,indent=2))
 print('COMPLETE',sum(r['status']=='converted' for r in results),'converted;',sum(r['status']=='error' for r in results),'errors',flush=True)
if __name__=='__main__':run()
