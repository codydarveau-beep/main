
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00067b60(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iStack_3c;
  uint uStack_34;
  int iStack_2c;
  
  uVar3 = 1;
  if ((_DAT_00d34020 != 0) &&
     (((iVar1 = func_0x000919b0(), iVar1 != 1 || (iStack_3c != 0x24)) || (-1 < iStack_2c)))) {
    iVar1 = func_0x000919b0();
    uVar3 = 1;
    if (iVar1 != 0) {
      if (iVar1 < 0) {
        uVar3 = 0xbb166f;
      }
      else {
        if (uStack_34 == 0) {
          return 1;
        }
        if ((param_2 == 0) && (uStack_34 == 0x28)) {
          return 1;
        }
        if (param_2 == 0x21) {
          uVar3 = 0xb9f4cd;
          if (uStack_34 < 7) {
            return 1;
          }
        }
        else {
          uVar2 = func_0x00093ab0();
          uVar3 = 0xb9f4cd;
          if (uVar2 == uStack_34) {
            return 1;
          }
        }
      }
      func_0x00074540(param_1,uVar3);
      uVar3 = 0;
    }
  }
  return uVar3;
}

