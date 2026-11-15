
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_00068620(int param_1,undefined4 param_2,int *param_3,int *param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  undefined4 uVar11;
  
  if ((_DAT_00d4766c != 0) && (_DAT_00d2fb8c != 0)) {
    piVar7 = (int *)0xd2f8b0;
    iVar5 = _DAT_00d2fb8c;
    do {
      if (*piVar7 == _DAT_00d4766c + -1) {
        if (((piVar7[10] != 0) && (piVar7[5] != 0)) && (piVar7[1] == *(int *)(param_1 + 0xdfcc))) {
          if ((uint)piVar7[7] <= (uint)piVar7[5]) {
            uVar11 = 0xb5571a;
            goto LAB_000687f0;
          }
          fVar9 = *(float *)(param_1 + 0x4aa0) - (float)piVar7[0x29];
          fVar10 = *(float *)(param_1 + 0x4aa4) - (float)piVar7[0x2a];
          fVar8 = (float10)func_0x00137820(fVar9 * fVar9 + fVar10 * fVar10);
          if ((float)fVar8 <= _DAT_0074a498) {
            iVar5 = piVar7[0x29];
            iVar1 = piVar7[0x2a];
            uVar11 = *(undefined4 *)(param_1 + 0x4aa0);
            uVar2 = *(undefined4 *)(param_1 + 0x4aa4);
            iVar3 = func_0x00095200(uVar11,uVar2,iVar5,iVar1);
            if ((iVar3 != 0) &&
               ((*(code **)(param_1 + 0x4e2dc) == (code *)0x0 ||
                (iVar5 = (**(code **)(param_1 + 0x4e2dc))
                                   (*(undefined4 *)(param_1 + 0x4e2e0),uVar11,uVar2,iVar5,iVar1),
                iVar5 != 0)))) {
              uVar4 = func_0x00095570();
              uVar6 = piVar7[7] - piVar7[5];
              if (uVar4 < (uint)(piVar7[7] - piVar7[5])) {
                uVar6 = uVar4;
              }
              iVar5 = func_0x00095650(piVar7[6]);
              if (iVar5 != 0) {
                *param_3 = piVar7[0x29];
                *param_4 = piVar7[0x2a];
                return uVar6;
              }
              uVar11 = 0xb559f8;
              goto LAB_000687f0;
            }
          }
          uVar11 = 0xb5592a;
          goto LAB_000687f0;
        }
        break;
      }
      piVar7 = piVar7 + 0x3d;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
  }
  uVar11 = 0xb89ee3;
LAB_000687f0:
  func_0x00074540(param_1,uVar11);
  return 0xffffffff;
}

