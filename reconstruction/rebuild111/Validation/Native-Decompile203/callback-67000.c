
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00067000(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  uVar1 = func_0x00135940();
  func_0x001358b0(0x10000);
  uVar2 = func_0x00135940();
  uVar3 = uVar1 - uVar2;
  if (uVar2 <= uVar1 && uVar3 != 0) {
    bVar4 = CARRY4(uVar3,_DAT_00d42490);
    uVar3 = uVar3 + _DAT_00d42490;
    _DAT_00d42490 = 0xffffffff;
    if (!bVar4) {
      _DAT_00d42490 = uVar3;
    }
  }
  _DAT_00d42494 = _DAT_00d42494 + 1;
  return;
}

