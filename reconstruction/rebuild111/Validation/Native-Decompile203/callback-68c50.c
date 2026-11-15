
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00068c50(int param_1,int param_2,uint param_3)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  undefined4 uVar9;
  float fVar10;
  longlong lVar11;
  
  uVar9 = 0;
  if (((0xfffffffc < param_2 - 8U) && (0xfffffff5 < param_3 - 0xb)) &&
     (iVar3 = FUN_00068a90(), iVar3 != 0)) {
    piVar8 = (int *)0x0;
    if (_DAT_00d2fb8c != 0) {
      piVar5 = (int *)0xd2f8b0;
      iVar3 = _DAT_00d2fb8c;
      do {
        if (*piVar5 == _DAT_00d4766c + -1) {
          piVar8 = piVar5;
          break;
        }
        piVar5 = piVar5 + 0x3d;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    if (param_2 - 5U < 2) {
      *(char *)((int)piVar8 + param_2 + 0x51) = (char)param_3;
      piVar8[param_2 + 0x11] =
           (int)((float)(int)(param_3 * 0x14) + *(float *)(param_1 + 0x4ab8) + _DAT_0074a3bc);
      fVar10 = (float)piVar8[0x18];
    }
    else {
      fVar10 = *(float *)(param_1 + 0x4ab8) + _DAT_0074a800;
      piVar8[0x18] = (int)fVar10;
      iVar3 = func_0x0013d068((ulonglong)(param_3 * 2 + 10) * (ulonglong)(uint)piVar8[7],100,0);
      piVar8[0x19] = iVar3;
      piVar8[0x1a] = (param_3 >> 1) + 5;
    }
    fVar1 = *(float *)(param_1 + 0x4ab8);
    if (fVar10 <= fVar1) {
      piVar8[0x1a] = 0;
      piVar8[0x19] = 0;
    }
    uVar2 = *(uint *)(piVar8[0xe] * 1000 + 0x2b378c + piVar8[4] * 4);
    uVar4 = (uint)*(byte *)((int)piVar8 + 0x53);
    if (fVar1 < (float)piVar8[0x16]) {
      uVar4 = uVar4 + *(byte *)((int)piVar8 + 0x56);
    }
    lVar11 = func_0x0013d068((ulonglong)uVar4 * (ulonglong)uVar2,100,0);
    lVar11 = lVar11 + (ulonglong)uVar2;
    uVar4 = (uint)lVar11;
    iVar6 = (int)((ulonglong)lVar11 >> 0x20);
    uVar2 = (uint)(uVar4 < 20000000);
    iVar3 = iVar6;
    if ((int)uVar2 <= iVar6) {
      iVar3 = 0;
    }
    uVar7 = 20000000;
    if (iVar6 < (int)uVar2) {
      uVar7 = uVar4;
    }
    uVar9 = 1;
    if ((SBORROW4(0,iVar3) != SBORROW4(-iVar3,(uint)(1 < uVar7))) ==
        (int)(-iVar3 - (uint)(1 < uVar7)) < 0) {
      uVar7 = 1;
    }
    if (((uint)piVar8[6] <= uVar7) || (iVar3 = func_0x00095650(uVar7), iVar3 != 0)) {
      piVar8[8] = uVar7;
    }
  }
  return uVar9;
}

