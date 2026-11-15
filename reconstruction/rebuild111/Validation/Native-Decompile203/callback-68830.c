
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00068830(int param_1,float *param_2,float *param_3)

{
  int iVar1;
  float *pfVar2;
  float10 fVar3;
  float fVar4;
  float fVar5;
  undefined4 uVar6;
  
  if ((_DAT_00d4766c != 0) && (_DAT_00d2fb8c != 0)) {
    pfVar2 = (float *)0xd2f958;
    iVar1 = _DAT_00d2fb8c;
    do {
      if (pfVar2[-0x2a] == (float)(_DAT_00d4766c + -1)) {
        if ((((pfVar2[-0x20] != 0.0) && (pfVar2[-0x25] == 0.0)) &&
            (pfVar2[-0x29] == *(float *)(param_1 + 0xdfcc))) && (pfVar2[-0x21] == _DAT_00d47670)) {
          fVar4 = *(float *)(param_1 + 0x4aa0) - pfVar2[-1];
          fVar5 = *(float *)(param_1 + 0x4aa4) - *pfVar2;
          fVar3 = (float10)func_0x00137820(fVar4 * fVar4 + fVar5 * fVar5);
          if (((float)fVar3 <= _DAT_0074a498) &&
             (iVar1 = func_0x00094070(*(undefined4 *)(param_1 + 0x4aa0),
                                      *(undefined4 *)(param_1 + 0x4aa4),pfVar2[-1],*pfVar2),
             iVar1 != 0)) {
            *param_2 = pfVar2[-1];
            *param_3 = *pfVar2;
            return 1;
          }
          uVar6 = 0xb54ffc;
          goto LAB_00068964;
        }
        break;
      }
      pfVar2 = pfVar2 + 0x3d;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  uVar6 = 0xb54c74;
LAB_00068964:
  func_0x00074540(param_1,uVar6);
  return 0;
}

