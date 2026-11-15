
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_000a3870(int param_1,int *param_2,uint param_3,int param_4,uint param_5)

{
  int *piVar1;
  float *pfVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  float10 fVar12;
  float fVar13;
  float fVar14;
  
  if (0x14f < param_3) {
    return;
  }
  iVar11 = param_3 * 0x298;
  uVar4 = *(uint *)(param_1 + 0x112a8 + iVar11);
  if ((uVar4 < 0x290) && (0xfffffff9 < *(int *)(uVar4 * 0x44 + 0x25979c) - 0x6c3U)) {
    return;
  }
  if (*(int *)(param_1 + 0x112b8 + iVar11) == 0) {
    return;
  }
  if ((*(int *)(param_1 + 0x11298 + iVar11) != 0) && (*(int *)(param_1 + 0x4f9c) == 0)) {
    return;
  }
  if (*(int *)(param_1 + 0x112ac + iVar11) < 1) {
    return;
  }
  fVar13 = *(float *)(param_1 + 0x4aa0) - *(float *)(param_1 + 0x111f8 + iVar11);
  fVar14 = *(float *)(param_1 + 0x4aa4) - *(float *)(param_1 + 0x111fc + iVar11);
  fVar12 = (float10)func_0x00137820(fVar13 * fVar13 + fVar14 * fVar14);
  if (_DAT_0074a2fc <= (float)fVar12) {
    return;
  }
  if ((int)param_5 < 1) {
    return;
  }
  if (*(int *)(param_1 + 0x112a4 + iVar11) != param_4) {
    return;
  }
  uVar4 = *(uint *)(param_1 + 0x112a8 + iVar11);
  if ((uVar4 < 0x290) && (0xfffffff9 < *(int *)(uVar4 * 0x44 + 0x25979c) - 0x6c3U)) {
    return;
  }
  fVar13 = *(float *)(param_1 + 0x4ab8);
  uVar10 = param_5;
  if (fVar13 < *(float *)(param_1 + 0x11118 + iVar11)) {
    *(undefined4 *)(param_1 + 0x11118 + iVar11) = 0;
    uVar10 = 2000000000;
    if (param_5 < 0x3b9aca01) {
      uVar10 = param_5 * 2;
    }
  }
  uVar7 = 1;
  if ((*(byte *)(uVar4 * 0x44 + 0x2597a0) & 0x10) == 0) {
    uVar7 = uVar10;
  }
  if ((int)uVar7 < 1) {
    return;
  }
  uVar4 = *(uint *)(param_1 + 0x11064);
  *(uint *)(param_1 + 0x11064) = uVar4 + 1;
  iVar5 = (uVar4 & 0xf) * 0x30;
  *(undefined8 *)(param_1 + 0x10d64 + iVar5) = *(undefined8 *)(param_1 + 0x111f8 + iVar11);
  *(float *)(param_1 + 0x10d6c + iVar5) = fVar13;
  *(undefined4 *)(param_1 + 0x10d70 + iVar5) = 0x3e4ccccd;
  *(uint *)(param_1 + 0x10d74 + iVar5) = uVar7;
  *(undefined4 *)(param_1 + 0x10d78 + iVar5) = 1;
  *(undefined4 *)(param_1 + 0x10d7c + iVar5) = 0;
  *(undefined4 *)(param_1 + 0x10d80 + iVar5) = 0;
  *(undefined4 *)(param_1 + 0x10d84 + iVar5) = 0;
  *(undefined4 *)(param_1 + 69000 + iVar5) = 0;
  *(undefined4 *)(param_1 + 0x10d8c + iVar5) = 0;
  *(undefined4 *)(param_1 + 0x10d90 + iVar5) = 0;
  func_0x000a5b10(param_1 + 0x10d64 + iVar5);
  uVar4 = *(uint *)(param_1 + iVar11 + 0x112a8);
  if ((uVar4 < 0x290) && (0xfffffff9 < *(int *)(uVar4 * 0x44 + 0x25979c) - 0x6c3U)) {
    fVar13 = *(float *)(param_1 + 0x4ab8);
    *(float *)(param_1 + 0x11218 + iVar11) = fVar13;
  }
  else {
    if ((*(int *)(param_1 + 0x4410) != 0) &&
       (uVar10 = *(uint *)(param_1 + 0x112ac + iVar11), 0 < (int)uVar10)) {
      if (uVar7 <= uVar10) {
        uVar10 = uVar7;
      }
      piVar1 = (int *)(param_1 + 0x111ec + iVar11);
      *piVar1 = *piVar1 + uVar10;
    }
    *(undefined4 *)(param_1 + 0x1114c + iVar11) = 0;
    *(undefined4 *)(param_1 + 0x11110 + iVar11) = 0;
    *(undefined4 *)(param_1 + 0x11264 + iVar11) = 0;
    if (0.0 < *(float *)(param_1 + 0x11274 + iVar11)) {
      *(undefined4 *)(param_1 + 0x11280 + iVar11) = 3;
      *(float *)(param_1 + 0x1127c + iVar11) = *(float *)(param_1 + 0x4ab8) + _DAT_0074ae7c;
    }
    *(undefined8 *)(param_1 + 0x11274 + iVar11) = 0;
    *(undefined4 *)(param_1 + 0x11298 + iVar11) = 0;
    iVar5 = *(int *)(param_1 + 0x1128c + iVar11);
    if (((iVar5 == 0) || (*(int *)(param_1 + 0x4795c) == 0)) ||
       ((int)uVar7 < *(int *)(param_1 + 0x112ac + iVar11))) {
      piVar1 = (int *)(param_1 + 0x112ac + iVar11);
      iVar9 = *piVar1;
      *piVar1 = *piVar1 - uVar7;
      fVar13 = *(float *)(param_1 + 0x4ab8);
      *(float *)(param_1 + 0x11218 + iVar11) = fVar13;
      if (*piVar1 == 0 || SBORROW4(iVar9,uVar7) != *piVar1 < 0) goto LAB_000a3c51;
    }
    else {
      *(undefined4 *)(param_1 + 0x112ac + iVar11) = 1;
      fVar13 = *(float *)(param_1 + 0x4ab8);
      *(float *)(param_1 + 0x11218 + iVar11) = fVar13;
    }
    if (uVar4 < 0x290) {
      if (0xfffffff9 < *(int *)(uVar4 * 0x44 + 0x25979c) - 0x6c3U) goto LAB_000a3c51;
      iVar5 = *(int *)(param_1 + 0x1128c + iVar11);
    }
    if ((iVar5 == 0) || (iVar5 = *(int *)(param_1 + 0x112a0 + iVar11), iVar5 == 0)) {
      uVar10 = *(uint *)(uVar4 * 0x40 + 0x2c0178);
    }
    else {
      uVar10 = (uint)(iVar5 == 3);
    }
    if ((uVar10 == 0) &&
       (fVar14 = (float)*(ushort *)(uVar4 * 2 + 0x429f20) / _DAT_0074a288 + fVar13,
       pfVar2 = (float *)(param_1 + 0x11238 + iVar11), *pfVar2 <= fVar14 && fVar14 != *pfVar2)) {
      *(float *)(param_1 + 0x11238 + iVar11) = fVar14;
    }
  }
LAB_000a3c51:
  uVar6 = 1;
  switch(param_2[0x22]) {
  case 2:
  case 0x11:
    break;
  case 3:
    uVar6 = 0x31;
    break;
  default:
    iVar5 = *(int *)(param_1 + 0x478d4);
    uVar4 = *(uint *)(param_1 + 0x478d8);
    uVar10 = uVar4 - iVar5;
    if (uVar10 < 0x20) {
      fVar13 = fVar13 + _DAT_0074a330;
      uVar7 = 0;
      if (uVar10 != 0) {
        uVar8 = uVar4;
        uVar7 = uVar10;
        do {
          uVar10 = uVar8 - 1 & 0x1f;
          fVar14 = *(float *)(param_1 + 0x478dc + uVar10 * 4);
          if (fVar14 <= fVar13) goto LAB_000a3d95;
          iVar9 = (uVar8 & 0x1f) * 4;
          *(undefined4 *)(param_1 + 0x47854 + iVar9) =
               *(undefined4 *)(param_1 + 0x47854 + uVar10 * 4);
          *(float *)(param_1 + 0x478dc + iVar9) = fVar14;
          uVar7 = uVar7 - 1;
          uVar8 = uVar8 - 1;
        } while (uVar7 != 0);
        uVar7 = 0;
      }
LAB_000a3d95:
      uVar10 = uVar7 + iVar5 & 0x1f;
      *(undefined4 *)(param_1 + 0x47854 + uVar10 * 4) = 0;
      *(float *)(param_1 + 0x478dc + uVar10 * 4) = fVar13;
      *(uint *)(param_1 + 0x478d8) = uVar4 + 1;
      iVar5 = *(int *)(param_1 + 0x112ac + iVar11);
      goto joined_r0x000a3dbf;
    }
    goto LAB_000a3d5d;
  case 9:
    uVar6 = 0x33;
    break;
  case 0xd:
    uVar6 = 0x14;
    break;
  case 0x15:
    uVar6 = 0x34;
  }
  if (_DAT_00bde3fc != 0) {
    puVar3 = (undefined4 *)(param_1 + 0x111fc + iVar11);
    FUN_000676a0(param_1,uVar6,*param_2 + 1,puVar3[-1],*puVar3,0);
  }
LAB_000a3d5d:
  iVar5 = *(int *)(param_1 + 0x112ac + iVar11);
joined_r0x000a3dbf:
  if (iVar5 < 1) {
    *(undefined4 *)(param_1 + 0x112ac + iVar11) = 0;
    *(undefined4 *)(param_1 + 0x1121c + iVar11) = *(undefined4 *)(param_1 + 0x4ab8);
    *(undefined4 *)(param_1 + 0x112d0 + iVar11) = 0;
    *(undefined4 *)(param_1 + 0x112b0 + iVar11) = 0;
    *(undefined4 *)(param_1 + 0x11284 + iVar11) = 0;
    func_0x000a43f0();
    if (*(uint *)(param_1 + 0x4b00) == param_3) {
      *(undefined4 *)(param_1 + 0x4b00) = 0xffffffff;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x112b0 + iVar11) = 1;
    *(int *)(param_1 + 0x111e8 + iVar11) = *param_2 + 0x20001;
  }
  return;
}

