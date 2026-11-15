
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00067480(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  if ((((((_DAT_00d34008 != 0) && (_DAT_00d33ffc == param_1)) && (*(int *)(param_1 + 0xdfcc) == 0))
       && ((0 < *(int *)(param_1 + 0x4ad0) && (*(int *)(param_2 + 0x18c) != 0)))) &&
      (_DAT_00d34000 != (int *)0x0)) &&
     (uVar3 = *(int *)(param_2 + 0x18c) - 1, uVar3 < (uint)_DAT_00d34000[1])) {
    iVar1 = *_DAT_00d34000;
    iVar4 = uVar3 * 0x78;
    if (((*(int *)(iVar1 + 0xc + iVar4) == -1) &&
        (uVar3 = *(uint *)(iVar1 + 0x10 + iVar4), (uVar3 & 0xfffffffe) == 0xec200010)) &&
       ((*(int *)(iVar1 + 8 + iVar4) == *(int *)(param_2 + 0x23c) &&
        (((*(int *)(iVar1 + 0x1c + iVar4) != 0 && (*(int *)(param_2 + 0x244) < 1)) &&
         (*(int *)(param_2 + 0x224) == 0)))))) {
      _DAT_00d34010 = _DAT_00d34010 | 1 << ((char)uVar3 - 0xdU & 0x1f);
      func_0x00091950();
    }
  }
  if ((((_DAT_00d42a14 == param_1) && (_DAT_00d42a18 != (int *)0x0)) &&
      ((*(int *)(param_2 + 0x18c) != 0 &&
       ((*(int *)(param_2 + 0x244) < 1 && (*(int *)(param_2 + 0x224) == 0)))))) &&
     ((0 < *(int *)(param_1 + 0x4ad0) &&
      (uVar3 = *(int *)(param_2 + 0x18c) - 1, uVar3 < (uint)_DAT_00d42a18[1])))) {
    iVar1 = *_DAT_00d42a18;
    iVar4 = uVar3 * 0x78;
    if ((((*(int *)(iVar1 + 0xc + iVar4) == -1) &&
         (iVar2 = *(int *)(iVar1 + 0x10 + iVar4), 0xfffffedf < iVar2 + 0x13e6cee0U)) &&
        (*(int *)(iVar1 + 0x1c + iVar4) != 0)) &&
       ((*(int *)(iVar1 + 8 + iVar4) == *(int *)(param_2 + 0x23c) &&
        (*(int *)(iVar1 + iVar4) == *(int *)(param_1 + 0xdfcc))))) {
      uVar3 = iVar2 + _DAT_00d42a20 * -8 + 0x13e6d000;
      if (uVar3 < 3) {
        _DAT_00d42a24 =
             _DAT_00d42a24 |
             1 << ((0xb < _DAT_00d42a20 || _DAT_00d42a20 == 10) << 3 | (byte)uVar3 & 0x1f);
        func_0x00092400();
      }
    }
  }
  if ((*(int *)(param_2 + 0x224) == 0) && (*(int *)(param_2 + 0x240) < 0x290)) {
    func_0x00092470(*(undefined4 *)(*(int *)(param_2 + 0x240) * 0x44 + 0x259788),
                    *(undefined4 *)(param_2 + 400),*(undefined4 *)(param_2 + 0x194),0);
  }
  return;
}

