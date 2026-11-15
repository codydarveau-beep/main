
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00068980(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  int *piVar4;
  
  uVar3 = 0;
  if ((0xfffffffb < param_2 - 5U) && (iVar1 = FUN_00068830(), iVar1 != 0)) {
    piVar4 = (int *)0x0;
    if (_DAT_00d2fb8c != 0) {
      piVar2 = (int *)0xd2f8b0;
      iVar1 = _DAT_00d2fb8c;
      do {
        if (*piVar2 == _DAT_00d4766c + -1) {
          piVar4 = piVar2;
          break;
        }
        piVar2 = piVar2 + 0x3d;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    func_0x0013d068((ulonglong)*(uint *)(param_2 * 4 + 0x2d4800) * (ulonglong)(uint)piVar4[7],100,0)
    ;
    iVar1 = func_0x00095650(piVar4[6]);
    if (iVar1 == 0) {
      func_0x00074540(param_1,0xb5506a);
      uVar3 = 0;
    }
    else {
      _DAT_00d47674 = _DAT_00d47674 + 1 + (uint)(_DAT_00d47674 == -1);
      piVar4[9] = _DAT_00d47674;
      piVar4[0x20] = 0;
      piVar4[0x30] = 0;
      piVar4[0x33] = 0;
      piVar4[0x1c] = -1;
      piVar4[0x1b] = -1;
      piVar4[0x36] = (int)(*(float *)(param_1 + 0x4ab8) + _DAT_0074a314);
      uVar3 = 1;
    }
  }
  return uVar3;
}

