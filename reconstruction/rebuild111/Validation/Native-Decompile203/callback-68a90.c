
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00068a90(int param_1,float *param_2,float *param_3)

{
  undefined4 uVar1;
  int iVar2;
  float *pfVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  undefined4 uVar7;
  
  if ((_DAT_00d4766c != 0) && (_DAT_00d2fb8c != 0)) {
    pfVar3 = (float *)0xd2f958;
    iVar2 = _DAT_00d2fb8c;
    do {
      if (pfVar3[-0x2a] == (float)(_DAT_00d4766c + -1)) {
        if ((((pfVar3[-0x20] != 0.0) && (pfVar3[-0x25] != 0.0)) &&
            (pfVar3[-0x29] == *(float *)(param_1 + 0xdfcc))) && (pfVar3[-0x21] == _DAT_00d47670)) {
          fVar5 = *(float *)(param_1 + 0x4aa0) - pfVar3[-1];
          fVar6 = *(float *)(param_1 + 0x4aa4) - *pfVar3;
          fVar4 = (float10)func_0x00137820(fVar5 * fVar5 + fVar6 * fVar6);
          if ((float)fVar4 <= _DAT_0074a498) {
            fVar5 = pfVar3[-1];
            fVar6 = *pfVar3;
            uVar7 = *(undefined4 *)(param_1 + 0x4aa0);
            uVar1 = *(undefined4 *)(param_1 + 0x4aa4);
            iVar2 = func_0x00095200(uVar7,uVar1,fVar5,fVar6);
            if ((iVar2 != 0) &&
               ((*(code **)(param_1 + 0x4e2dc) == (code *)0x0 ||
                (iVar2 = (**(code **)(param_1 + 0x4e2dc))
                                   (*(undefined4 *)(param_1 + 0x4e2e0),uVar7,uVar1,fVar5,fVar6),
                iVar2 != 0)))) {
              *param_2 = pfVar3[-1];
              *param_3 = *pfVar3;
              return 1;
            }
          }
          uVar7 = 0xb558fe;
          goto LAB_00068c2b;
        }
        break;
      }
      pfVar3 = pfVar3 + 0x3d;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  uVar7 = 0xb556e7;
LAB_00068c2b:
  func_0x00074540(param_1,uVar7);
  return 0;
}

