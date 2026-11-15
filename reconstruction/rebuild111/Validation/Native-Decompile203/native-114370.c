
void __thiscall FUN_00114370(uint param_1,undefined4 param_2,undefined4 param_3)

{
  float fVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  byte bVar6;
  byte bVar5;
  uint uVar7;
  char *pcVar8;
  uint uVar9;
  int iVar10;
  float fVar11;
  char acStack_b1 [161];
  
  uVar2 = DAT_00bec5ac;
  fVar11 = DAT_00be3098;
  if ((param_1 != 0xad) && (param_1 != 0xb4)) {
    uVar3 = DAT_00e381bc & 7;
    DAT_00e381bc = DAT_00e381bc + 1;
    (&DAT_00d42974)[uVar3 * 5] = param_1;
    (&DAT_00d42978)[uVar3 * 5] = uVar2;
    (&DAT_00d4297c)[uVar3 * 5] = param_2;
    (&DAT_00d42980)[uVar3 * 5] = param_3;
    (&DAT_00d42984)[uVar3 * 5] = fVar11;
  }
  pcVar8 = s_effect_ef_bash_wav_00a21c8a;
  if (param_1 == 10) {
    pcVar8 = &DAT_00a21896;
  }
  uVar3 = 0;
  do {
    bVar6 = *pcVar8;
    if ((bVar6 == 0x2f) || (bVar6 == 0x5c)) {
      bVar6 = 0x5c;
      bVar5 = 0x5c;
      if (uVar3 == 0) {
        uVar9 = 1;
        goto LAB_00114405;
      }
      if ((acStack_b1 + 1)[uVar3 - 1] != '\\') goto LAB_0011442d;
    }
    else {
      if (bVar6 == 0) {
        acStack_b1[uVar3 + 1] = '\0';
        iVar10 = 0;
        goto LAB_00114460;
      }
LAB_0011442d:
      bVar5 = bVar6 | 0x20;
      if (0x19 < (byte)(bVar6 + 0xbf)) {
        bVar5 = bVar6;
      }
      uVar9 = uVar3 + 1;
      if (0x9f < uVar9) break;
LAB_00114405:
      acStack_b1[uVar3 + 1] = bVar5;
      uVar3 = uVar9;
    }
    pcVar8 = pcVar8 + 1;
  } while( true );
  iVar10 = -1;
  goto LAB_00114481;
  while (iVar10 = iVar10 + 1, iVar10 != 0x67) {
LAB_00114460:
    iVar4 = FUN_001378a0(acStack_b1 + 1,(&PTR_s__curse_wav_0051a778)[iVar10 * 2]);
    if (iVar4 == 0) goto LAB_00114481;
  }
  iVar10 = -1;
LAB_00114481:
  iVar4 = DAT_00c25eb4;
  if ((param_1 | 8) == 10) {
    if ((-1 < iVar10) && (uVar3 = DAT_00c25eb8 - DAT_00c25eb4, uVar3 < 0x20)) {
      fVar11 = DAT_00be3098 + 0.0;
      uVar9 = 0;
      if (uVar3 != 0) {
        uVar7 = DAT_00c25eb8;
        do {
          uVar9 = uVar3;
          uVar3 = uVar7 - 1 & 0x1f;
          fVar1 = (float)(&DAT_00c25ebc)[uVar3];
          if (fVar1 <= fVar11) break;
          (&DAT_00c25e34)[uVar7 & 0x1f] = (&DAT_00c25e34)[uVar3];
          (&DAT_00c25ebc)[uVar7 & 0x1f] = fVar1;
          uVar3 = uVar9 - 1;
          uVar9 = 0;
          uVar7 = uVar7 - 1;
        } while (uVar3 != 0);
      }
      uVar3 = uVar9 + iVar4 & 0x1f;
      (&DAT_00c25e34)[uVar3] = iVar10 + 0x304;
      (&DAT_00c25ebc)[uVar3] = fVar11;
      DAT_00c25eb8 = DAT_00c25eb8 + 1;
    }
  }
  else {
    FUN_000ceb00();
  }
  return;
}

