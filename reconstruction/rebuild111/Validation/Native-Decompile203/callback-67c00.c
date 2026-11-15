
undefined4
FUN_00067c00(int param_1,int *param_2,undefined4 *param_3,undefined4 *param_4,undefined4 *param_5)

{
  int iVar1;
  int iStack_38;
  int iStack_34;
  int iStack_24;
  
  if ((((0xfffffffb < *param_2 - 0x1c8U) || ((*(uint *)(param_1 + 0xdfcc) & 0xfffffffc) != 0x1c4))
      || (iVar1 = func_0x000919b0(), iVar1 != 1)) || ((iStack_38 != 0 || (iStack_24 != 0)))) {
    return 0;
  }
  if (iStack_34 == 0) {
    *param_2 = 0;
    *param_3 = 0x44b58000;
    *param_4 = 0x4531c000;
    *param_5 = 0;
    return 1;
  }
  return 0;
}

