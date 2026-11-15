
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000676a0(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5,
                 float param_6)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  float fVar12;
  
  switch(param_2) {
  case 1:
  case 0x10:
  case 0x14:
  case 0x31:
  case 0x33:
  case 0x34:
    uVar4 = func_0x00132b30(param_6);
    if (((param_6 <= _DAT_00749e28) && (0.0 <= param_6)) && ((uVar4 & 0x100) == 0)) {
      if (param_3 == 0) {
        iVar9 = *(int *)(param_1 + 0xdfcc);
        iVar6 = 0;
code_r0x0006773f:
        uVar4 = uRam00d42f58 & 7;
        fVar12 = *(float *)(param_1 + 0x4ab8);
        uRam00d42f58 = uRam00d42f58 + 1;
        *(int *)(uVar4 * 0x1c + 0xd42e78) = param_2;
        *(int *)(uVar4 * 0x1c + 0xd42e7c) = param_3;
        *(int *)(uVar4 * 0x1c + 0xd42e80) = iVar9;
        *(int *)(uVar4 * 0x1c + 0xd42e84) = iVar6;
        *(undefined4 *)(uVar4 * 0x1c + 0xd42e88) = param_4;
        *(undefined4 *)(uVar4 * 0x1c + 0xd42e8c) = param_5;
        *(float *)(uVar4 * 0x1c + 0xd42e90) = fVar12 + param_6;
        iVar9 = 0;
        do {
          if (*(int *)(iVar9 * 8 + 0x2bef3c) == param_2) {
            iVar6 = *(int *)(param_1 + 0x478d4);
            uVar4 = *(uint *)(param_1 + 0x478d8);
            uVar11 = uVar4 - iVar6;
            if (uVar11 < 0x20) {
              iVar2 = *(int *)(iVar9 * 8 + 0x2bef40);
              fVar12 = *(float *)(param_1 + 0x4ab8) + param_6;
              uVar3 = uVar4;
              for (; uVar7 = 0, uVar11 != 0; uVar11 = uVar11 - 1) {
                uVar8 = uVar3 - 1 & 0x1f;
                fVar1 = *(float *)(param_1 + 0x478dc + uVar8 * 4);
                uVar7 = uVar11;
                if (fVar1 <= fVar12) break;
                iVar10 = (uVar3 & 0x1f) * 4;
                *(undefined4 *)(param_1 + 0x47854 + iVar10) =
                     *(undefined4 *)(param_1 + 0x47854 + uVar8 * 4);
                *(float *)(param_1 + 0x478dc + iVar10) = fVar1;
                uVar3 = uVar3 - 1;
              }
              uVar11 = uVar7 + iVar6 & 0x1f;
              *(int *)(param_1 + 0x47854 + uVar11 * 4) = iVar2 + 0x304;
              *(float *)(param_1 + 0x478dc + uVar11 * 4) = fVar12;
              *(uint *)(param_1 + 0x478d8) = uVar4 + 1;
            }
          }
          iVar9 = iVar9 + 1;
        } while (iVar9 != 0x58);
      }
      else if (_DAT_00d2fb8c != 0) {
        piVar5 = (int *)0xd2f8d8;
        iVar9 = _DAT_00d2fb8c;
        do {
          if (piVar5[-10] == param_3 + -1) {
            if (*piVar5 == 0) {
              return;
            }
            if (piVar5[-5] == 0) {
              return;
            }
            iVar9 = piVar5[-9];
            if (iVar9 != *(int *)(param_1 + 0xdfcc)) {
              return;
            }
            iVar6 = piVar5[-1];
            goto code_r0x0006773f;
          }
          piVar5 = piVar5 + 0x3d;
          iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
      }
    }
  }
  return;
}

