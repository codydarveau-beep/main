# MIT. Current native source sanitizer checks; no emulator/hardware claims.
from pathlib import Path
import subprocess,tempfile,os,math
root=Path(__file__).resolve().parent
env=os.environ.copy();env['MYRO_WORLD_PATH']=str(root.parent/'Packed/world.bin');env['MYRO_ACTOR_PATH']=str(root.parent/'Actors/actors.bin');env['MYRO_ENEMY_PATH']=str(root.parent/'Enemies/enemies.bin');env['MYRO_EFFECT_PATH']=str(root.parent/'Effects/effects.bin');env['MYRO_SYSTEM_PATH50']=str(root.parent/'Systems/systems.bin');env['MYRO_MUSIC_PATH50']=str(root.parent/'Music/music.bin')
with tempfile.TemporaryDirectory(prefix='myro45-')as tmp:
 out=Path(tmp);tests=[('test_bindings50',[]),('test_geometry50',[]),('test_lockon49',[]),('test_cast49',[]),('test_fields49',[]),('test_ui49',[]),('test_timing49',[]),('test_class_interactions48',[]),('test_class_art48',[]),('test_hocus48',[]),('test_classes48',[]),('test_stats48',[]),('test_ui_model47',[]),('test_ground45a',[]),('test_equipment46',[]),('test_skill_views46',[]),('test_footprint46',[]),('test_effect_cache45',[]),('test_feedback45',[]),('test_maps45',[]),('test_sprite_visual45',[]),('test_bridge44',[]),('test_recovery44',[]),('test_disc44',[]),('test_minimap',[]),('test_expedition43',[]),('test_second_jobs43',[]),('test_spell_world43',[]),('test_world43',[]),('test_target_frames41',['encounter_assets.c']),('test_cart43',[]),('test_projection',[]),('test_sprite_projection35',[]),('test_hud_batch',[]),('test_inventory',[]),('test_shop',[]),('test_services36',[]),('test_art45',[]),('test_art_render45',[]),('test_upload40',[]),('test_session40',[])]
 tests[:0]=[('test_autosave50b',[]),('test_audio50b',['sound_assets.c']),('test_navigation50b',[]),('test_profile50b',[]),('test_upload50b',[]),('test_runtime50a',[]),('test_loadouts50a',[]),('test_classes50',[]),('test_solo_systems50',[]),('test_regen50',[]),('test_review50',[]),('test_system_art50',[]),('test_system_cache50',[]),('test_class_audio50',['music_assets.c','sound_assets.c']),('test_dual50',[]),('test_render_memory50',[]),('test_world_memory50',[]),('test_music_disk50',[]),('test_music_residency50',['music_assets.c','sound_assets.c']),('test_prepared_catalog50',[])]
 resume=os.environ.get('MYRO_TESTS_FROM50')
 if resume:
  start=next(i for i,v in enumerate(tests) if v[0]==resume);tests=tests[start:]
 for name,extra in tests:
  exe=out/name;subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined',*(['-I'+env.get('NXDK_DIR',str(root.parent.parent/'toolchain/xbox-nxdk'))+'/lib/pbkit']if name in ['test_ground45a','test_system_cache50']else[]),str(root/(name+'.c')),*[str(root/p)for p in extra],'-lm','-lz','-o',str(exe)],check=True)
  args=[str(exe)]+([str(root.parent/'Actors/actors.bin')]if name=='test_sprite_projection35'else[]);subprocess.run(args,check=True,env=env,cwd=root)
  if name=='test_disc44':
   probe=env.copy();probe['MYRO_DISC_PROBE44']='1';bad=out/'fault-enemies.bin';probe['MYRO_ENEMY_PATH']=str(bad)
   original=(root.parent/'Enemies/enemies.bin').read_bytes()
   for mode in ['missing','truncated','checksum']:
    if mode=='truncated':bad.write_bytes(original[:-1])
    if mode=='checksum':
     data=bytearray(original);data[20]^=1;bad.write_bytes(data)
    run=subprocess.run([str(exe)],env=probe,capture_output=True,text=True);assert run.returncode==2 and {'missing':'Cannot open','truncated':'size/seek','checksum':'checksum'}[mode]in run.stderr,(mode,run.stderr)
   print('PASS44 actual species disc reader rejects missing, truncated and corrupt data')

 exe=out/'autosave_disk50b';subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-I'+str(root.parent.parent/'toolchain/xbox-nxdk/lib'),str(root/'test_autosave_disk50b.c'),'-lm','-lz','-o',str(exe)],check=True);subprocess.run([str(exe)],check=True,cwd=root)
 exe=out/'save_disk50';subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined','-I'+str(root.parent.parent/'toolchain/xbox-nxdk/lib'),str(root/'test_save_disk50.c'),'-lm','-lz','-o',str(exe)],check=True);subprocess.run([str(exe)],check=True,cwd=root)
 exe=out/'ui';subprocess.run(['cc','-O1','-g','-fsanitize=address,undefined',str(root/'test_ui42.c'),str(root/'ui_assets.c'),str(root/'skin_assets.c'),'-lm','-lz','-o',str(exe)],check=True)
 cases=[['autosave50b',str(choice)]for choice in range(7)]+[['performance50b',str(ready),str(value)]for ready in range(2)for value in [0,123,99999]]+[['audio50']]+[['assign',str(i)]for i in range(14)]+[['skills',str(i)]for i in range(1,21)]+[['label40',str(i)]for i in range(254)]+[['cast','.001',str(t*.5)]for t in range(1,13)]+[['cast',str(v)]for v in [0,.1,2.5,5]]+[['dock40',str(i)]for i in range(512)]+[['inventory',str(i)]for i in range(255)]+[['toggles41',str(row),str(mask)]for row in range(12)for mask in [0,1,127]]+[['dev41',str(tab),str(row)]for tab in range(3)for row in [*range([8,11,8][tab])]]
 cases += [['minimap44',str(i)]for i in range(20)]+[['status44',str(i)]for i in [32,999,1000,8488,9999,32767]]
 cases += [['enemy47',str(edge),str(hp)]for edge in range(4)for hp in [1,99,120000,1000000]]
 cases += [['equip',str(slot)]for slot in range(10)]+[['equip49']]
 cases += [['skills',str(job),'1']for job in range(1,21)]
 cases += [['diag45',str(off),str(open)]for off in range(2)for open in range(16)]
 cases += [["dev41","2",str(row),str(group)]for group in range(3)for row in range([6,13,1][group])]+[["windows","0",str(row),"0"]for row in range(6)]
 cases += [['status50',str(job),str(row)]for job in range(21)for row in range(6)]
 cases += [['companion50',str(kind),str(row)]for kind in range(6001,6017)for row in range(8)]
 cases += [['craft50',str(job),str(row),str(tool)]for job,tool in [(19,612),(19,613),(19,614),(19,615),(20,7134)]for row in range(20)]
 cases += [['buffs50',str(job)]for job in range(12,21)]
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
 print('PASS50',len(tests)+2,'ASan/UBSan C suites;',len(cases),'actual HUD cases; peak',peak,'/1536quads')
