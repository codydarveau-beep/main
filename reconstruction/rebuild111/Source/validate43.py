# MIT. Current native source sanitizer checks; no emulator/hardware claims.
from pathlib import Path
import subprocess,tempfile,os,math
root=Path(__file__).resolve().parent
env=os.environ.copy();env['MYRO_WORLD_PATH']=str(root.parent/'Packed/world.bin')
with tempfile.TemporaryDirectory(prefix='myro43-')as tmp:
 out=Path(tmp);tests=[('test_expedition43',[]),('test_second_jobs43',[]),('test_spell_world43',[]),('test_world43',[]),('test_target_frames41',['encounter_assets.c']),('test_cart43',[]),('test_projection',[]),('test_sprite_projection35',[]),('test_hud_batch',[]),('test_inventory',[]),('test_shop',[]),('test_services36',[]),('test_art41',[]),('test_art_render41',[]),('test_upload40',[]),('test_session40',[])]
 for name,extra in tests:
  exe=out/name;subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined',str(root/(name+'.c')),*[str(root/p)for p in extra],'-lm','-lz','-o',str(exe)],check=True)
  args=[str(exe)]+([str(root.parent/'Actors/actors.bin')]if name=='test_sprite_projection35'else[]);subprocess.run(args,check=True,env=env)
 exe=out/'ui';subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined',str(root/'test_ui42.c'),str(root/'ui_assets.c'),str(root/'skin_assets.c'),'-lm','-lz','-o',str(exe)],check=True)
 cases=[['assign',str(i)]for i in range(14)]+[['skills',str(i)]for i in range(1,9)]+[['label40',str(i)]for i in range(89)]+[['cast','.001',str(t*.5)]for t in range(1,13)]+[['cast',str(v)]for v in [0,.1,2.5,5]]+[['dock40',str(i)]for i in range(512)]+[['inventory',str(i)]for i in range(18)]+[['toggles41',str(row),str(mask)]for row in range(12)for mask in [0,1,127]]+[['dev41',str(tab),str(row)]for tab in range(4)for row in [*range([8,9,8,4][tab])]]
 peak=0
 for args in cases:
  run=subprocess.run([str(exe),*args],check=True,capture_output=True,text=True);quads=0
  for line in run.stdout.splitlines():
   a=line.split()
   if a and a[0]=='Q':
    x,y,w,h,*uv=map(float,a[1:]);assert min(x,y)>=0 and x+w<=640.1 and y+h<=480.1,(args,line);quads+=1
   elif a and a[0]=='F':
    x,y,w,h,c=map(int,a[1:]);assert min(x,y)>=0 and x+w<=640 and y+h<=480,(args,line)
  peak=max(peak,quads);assert quads<=1536
 print('PASS43',len(tests),'ASan/UBSan C suites;',len(cases),'actual HUD cases; peak',peak,'/1536quads')
