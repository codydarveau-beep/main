
undefined4 FUN_00067c90(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iStack_3c;
  int iStack_28;
  
  if ((param_1 != 0) && (0xffffd83a < param_2 - 0x27c6U)) {
    uVar1 = param_3;
    if (((*(int *)(*(int *)(param_1 + 0x708) + 0xdfcc) == 0x1c7) &&
        (((iVar2 = func_0x001378a0(*(undefined4 *)(param_2 * 0x3c + 0x1c4544),0xa216a7), iVar2 == 0
          && (iVar2 = func_0x000919b0(), iVar2 == 1)) && (iStack_3c == 0)))) && (iStack_28 == 0)) {
      iVar2 = func_0x00138110(param_3,0xa99cf5);
      uVar1 = 0xb7b969;
      if (iVar2 == 0) {
        iVar2 = func_0x00138110(param_3,0xaae897);
        uVar1 = 0xbb608a;
        if (iVar2 == 0) {
          iVar2 = func_0x00138110(param_3,0xacc6e7);
          uVar1 = 0xbb601e;
          if (iVar2 == 0) {
            iVar2 = func_0x00138110(param_3,0xac8859);
            uVar1 = 0xbb5faa;
            if (iVar2 == 0) {
              iVar2 = func_0x00138110(param_3,0xa5db47);
              uVar1 = 0xbb5f36;
              if (iVar2 == 0) {
                iVar2 = func_0x00138110(param_3,0xa5c68b);
                uVar1 = 0xb7893f;
                if (iVar2 == 0) {
                  iVar2 = func_0x001378a0(param_3,0xa251d0);
                  if (iVar2 == 0) {
                    uVar1 = 0xa5acab;
                  }
                  else {
                    iVar2 = func_0x001378a0(param_3,0xa5acc5);
                    uVar1 = 0xa58a83;
                    if (iVar2 != 0) {
                      uVar1 = param_3;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    param_3 = uVar1;
  }
  return param_3;
}

