
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000678b0(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  float10 fVar7;
  float fVar8;
  float fVar9;
  
  iVar4 = _DAT_00d2f3ac;
  uVar2 = _DAT_00d2f3a8;
  if (_DAT_00c5b640 == param_1) {
    if (param_2 != 0) {
      piVar6 = (int *)0xc5af38;
      uVar1 = *(undefined4 *)(param_1 + 0xdfcc);
      uVar5 = 0;
      do {
        if ((*piVar6 == 0) ||
           (iVar3 = (_DAT_00d2f3ac - piVar6[7]) - (uint)(_DAT_00d2f3a8 < (uint)piVar6[6]),
           iVar3 != 0 || (uint)-iVar3 < (uint)(29999 < _DAT_00d2f3a8 - piVar6[6])))
        goto LAB_0006793b;
        uVar5 = uVar5 + 1;
        piVar6 = piVar6 + 0xe;
      } while (uVar5 != 0x20);
      uVar5 = _DAT_00c5b638 & 0x1f;
      _DAT_00c5b63c = _DAT_00c5b63c + 1;
      _DAT_00c5b638 = _DAT_00c5b638 + 1;
LAB_0006793b:
      iVar3 = uVar5 * 0x38;
      *(undefined4 *)(iVar3 + 0xc5af38) = 2;
      *(undefined4 *)(iVar3 + 0xc5af3c) = 0x173;
      *(undefined4 *)(iVar3 + 0xc5af40) = 1;
      *(undefined4 *)(iVar3 + 0xc5af44) = 0;
      *(undefined4 *)(iVar3 + 0xc5af48) = uVar1;
      *(uint *)(iVar3 + 0xc5af50) = uVar2;
      *(int *)(iVar3 + 0xc5af54) = iVar4;
      *(undefined8 *)(iVar3 + 0xc5af58) = 0;
      *(undefined4 *)(iVar3 + 0xc5af60) = 0;
      *(undefined4 *)(iVar3 + 0xc5af64) = 0;
      *(undefined4 *)(iVar3 + 0xc5af68) = 0;
      iVar4 = _DAT_00c5b640;
      fVar8 = *(float *)(_DAT_00c5b640 + 0x4aa0);
      fVar9 = *(float *)(_DAT_00c5b640 + 0x4aa4);
      iVar3 = func_0x00093900(fVar8,fVar9,fVar8,fVar9,fVar9,fVar8);
      if (iVar3 != 0) {
        fVar8 = *(float *)(iVar4 + 0x4aa0) - fVar8;
        fVar9 = *(float *)(iVar4 + 0x4aa4) - fVar9;
        fVar7 = (float10)func_0x00137820(fVar8 * fVar8 + fVar9 * fVar9);
        if ((float)fVar7 <= _DAT_0074a9e4) {
          iVar4 = -0x2c0;
          do {
            if ((*(int *)(iVar4 + 0x2bf1fc) == 0x173) && (_DAT_00cf0edc < 0x20)) {
              iVar3 = _DAT_00cf0edc * 4;
              _DAT_00cf0edc = _DAT_00cf0edc + 1;
              *(undefined4 *)(iVar3 + 0xcf0ee0) = *(undefined4 *)(iVar4 + 0x2bf200);
            }
            iVar4 = iVar4 + 8;
          } while (iVar4 != 0);
        }
      }
    }
    iVar4 = _DAT_00d2f3ac;
    uVar2 = _DAT_00d2f3a8;
    if (param_3 != 0) {
      piVar6 = (int *)0xc5af38;
      uVar1 = *(undefined4 *)(param_1 + 0xdfcc);
      uVar5 = 0;
      do {
        if ((*piVar6 == 0) ||
           (iVar3 = (_DAT_00d2f3ac - piVar6[7]) - (uint)(_DAT_00d2f3a8 < (uint)piVar6[6]),
           iVar3 != 0 || (uint)-iVar3 < (uint)(29999 < _DAT_00d2f3a8 - piVar6[6])))
        goto LAB_00067a9b;
        uVar5 = uVar5 + 1;
        piVar6 = piVar6 + 0xe;
      } while (uVar5 != 0x20);
      uVar5 = _DAT_00c5b638 & 0x1f;
      _DAT_00c5b63c = _DAT_00c5b63c + 1;
      _DAT_00c5b638 = _DAT_00c5b638 + 1;
LAB_00067a9b:
      iVar3 = uVar5 * 0x38;
      *(undefined4 *)(iVar3 + 0xc5af38) = 2;
      *(undefined4 *)(iVar3 + 0xc5af3c) = 0x9e;
      *(undefined4 *)(iVar3 + 0xc5af40) = 1;
      *(undefined4 *)(iVar3 + 0xc5af44) = 0;
      *(undefined4 *)(iVar3 + 0xc5af48) = uVar1;
      *(int *)(iVar3 + 0xc5af54) = iVar4;
      *(uint *)(iVar3 + 0xc5af50) = uVar2;
      *(undefined8 *)(iVar3 + 0xc5af58) = 0;
      *(undefined4 *)(iVar3 + 0xc5af60) = 0;
      *(undefined4 *)(iVar3 + 0xc5af64) = 0;
      *(undefined4 *)(iVar3 + 0xc5af68) = 0;
    }
  }
  return;
}

