
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_000a3e30(int param_1,int param_2)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  float fVar13;
  
  fVar5 = _DAT_0074a4ac;
  fVar4 = _DAT_0074a330;
  iVar6 = 10;
  if (param_2 < 10) {
    iVar6 = param_2;
  }
  if (0 < param_2) {
    iVar2 = *(int *)(param_1 + 0x478d4);
    uVar10 = *(uint *)(param_1 + 0x478d8);
    iVar12 = 0;
    do {
      uVar9 = uVar10 - iVar2;
      if (uVar9 < 0x20) {
        fVar13 = (float)iVar12 * fVar5 + fVar4 + *(float *)(param_1 + 0x4ab8);
        uVar3 = uVar10;
        for (; uVar8 = 0, uVar9 != 0; uVar9 = uVar9 - 1) {
          uVar7 = uVar3 - 1 & 0x1f;
          fVar1 = *(float *)(param_1 + 0x478dc + uVar7 * 4);
          uVar8 = uVar9;
          if (fVar1 <= fVar13) break;
          iVar11 = (uVar3 & 0x1f) * 4;
          *(undefined4 *)(param_1 + 0x47854 + iVar11) =
               *(undefined4 *)(param_1 + 0x47854 + uVar7 * 4);
          *(float *)(param_1 + 0x478dc + iVar11) = fVar1;
          uVar3 = uVar3 - 1;
        }
        uVar9 = uVar8 + iVar2 & 0x1f;
        *(undefined4 *)(param_1 + 0x47854 + uVar9 * 4) = 0;
        *(float *)(param_1 + 0x478dc + uVar9 * 4) = fVar13;
        uVar10 = uVar10 + 1;
        *(uint *)(param_1 + 0x478d8) = uVar10;
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 != iVar6);
  }
  return;
}

