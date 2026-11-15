
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00068de0(undefined4 param_1,int param_2,int param_3)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 uStack_7a4;
  undefined4 uStack_7a0;
  undefined4 *puStack_79c;
  byte abStack_791 [8];
  uint uStack_789;
  undefined4 auStack_77d [154];
  undefined4 uStack_515;
  byte abStack_511 [1281];
  
  if (_DAT_00d2fb8c == 0) {
    uVar7 = 1;
  }
  else {
    iVar4 = func_0x00092ae0();
    uVar7 = 0;
    if (-1 < iVar4) {
      if (_DAT_00d2fb8c != 0) {
        puVar8 = (undefined4 *)0xd2f8c4;
        iVar4 = _DAT_00d2fb8c;
        do {
          if (puVar8[5] != 0) {
            puVar10 = puVar8 + 2;
            if (param_2 == 0) {
              puVar10 = puVar8;
            }
            uVar2 = puVar8[-5];
            if (0x12 < uVar2) goto LAB_00069029;
            if ((uStack_789 >> (uVar2 & 0x1f) & 1) == 0) {
              puStack_79c = (undefined4 *)(uVar2 * 4 + 0x2a7984);
              uStack_7a0 = 0;
              uStack_7a4 = 2;
              uVar7 = 0;
            }
            else {
              puStack_79c = auStack_77d + uVar2 * 8 + 3;
              uStack_7a0 = auStack_77d[uVar2 * 8 + 2];
              uVar7 = auStack_77d[uVar2 * 8];
              uStack_7a4 = auStack_77d[uVar2 * 8 + 1];
            }
            iVar5 = func_0x00093300(puVar8[-1],uVar7,uStack_7a4,uStack_7a0,*puStack_79c,*puVar10,
                                    puVar8[(uint)(param_3 != 0) * 2 + 1]);
            if (iVar5 == 0) goto LAB_00069029;
          }
          puVar8 = puVar8 + 0x3d;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
      iVar4 = _DAT_00d424d4;
      uStack_515 = func_0x0013d320(0,abStack_791,0x27c);
      if (iVar4 == 0) {
LAB_00069029:
        uVar7 = 0;
      }
      else {
        iVar4 = -0x280;
        do {
          bVar1 = abStack_511[iVar4];
          abStack_511[iVar4 * 2 + 0x500] = *(byte *)((bVar1 >> 4) + 0x2bef28);
          abStack_511[iVar4 * 2 + 0x501] = *(byte *)((bVar1 & 0xf) + 0x2bef28);
          iVar4 = iVar4 + 1;
        } while (iVar4 != 0);
        abStack_511[0x500] = 0;
        iVar4 = func_0x00091ff0(0xeca20000,0,2,0,0,abStack_511,0x500);
        uVar7 = 0;
        if (iVar4 != 0) {
          uVar7 = 1;
          if (_DAT_00d2fb8c != 0) {
            piVar6 = (int *)0xd2f8c4;
            iVar4 = _DAT_00d2fb8c;
            iVar5 = _DAT_00d47674;
            do {
              if (piVar6[5] != 0) {
                iVar3 = *piVar6;
                iVar9 = iVar3;
                if (param_2 != 0) {
                  iVar9 = piVar6[2];
                  *piVar6 = iVar9;
                }
                if (param_3 != 0) {
                  piVar6[1] = piVar6[3];
                }
                if ((iVar3 == 0) && (iVar9 != 0)) {
                  piVar6[0x1b] = 0;
                  piVar6[0x2b] = 0;
                  piVar6[0x2e] = 0;
                  iVar5 = iVar5 + 1 + (uint)(iVar5 == -1);
                  _DAT_00d47674 = iVar5;
                  piVar6[4] = iVar5;
                }
              }
              piVar6 = piVar6 + 0x3d;
              iVar4 = iVar4 + -1;
            } while (iVar4 != 0);
          }
        }
      }
    }
  }
  return uVar7;
}

