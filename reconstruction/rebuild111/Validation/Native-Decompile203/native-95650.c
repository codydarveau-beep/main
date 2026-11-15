
undefined4 __fastcall FUN_00095650(uint *param_1,uint param_2,uint param_3)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uStack_7a4;
  undefined4 *puStack_7a0;
  byte abStack_791 [8];
  uint uStack_789;
  undefined4 auStack_77d [154];
  undefined4 uStack_515;
  byte abStack_511 [1281];
  
  iVar6 = DAT_00d424d4;
  uVar2 = *param_1;
  uVar3 = param_1[4];
  iVar4 = FUN_00092ae0();
  if ((uVar2 < 0x13) && (-1 < iVar4)) {
    if ((uStack_789 >> (uVar2 & 0x1f) & 1) == 0) {
      puStack_7a0 = &DAT_002a7984 + uVar2;
      uStack_7a4 = 0;
      uVar5 = 2;
      uVar7 = 0;
    }
    else {
      puStack_7a0 = auStack_77d + uVar2 * 8 + 3;
      uStack_7a4 = auStack_77d[uVar2 * 8 + 2];
      uVar7 = auStack_77d[uVar2 * 8];
      uVar5 = auStack_77d[uVar2 * 8 + 1];
    }
    iVar4 = FUN_00093300(uVar3,uVar7,uVar5,uStack_7a4,*puStack_7a0,param_2,param_3);
    if (iVar4 != 0) {
      uStack_515 = thunk_FUN_0013d210(0,abStack_791,0x27c);
      if (iVar6 != 0) {
        iVar6 = -0x280;
        do {
          bVar1 = abStack_511[iVar6];
          abStack_511[iVar6 * 2 + 0x500] = s_0123456789abcdef_002bef28[bVar1 >> 4];
          abStack_511[iVar6 * 2 + 0x501] = s_0123456789abcdef_002bef28[bVar1 & 0xf];
          iVar6 = iVar6 + 1;
        } while (iVar6 != 0);
        abStack_511[0x500] = 0;
        iVar6 = FUN_00091ff0(0xeca20000,0,2,0,0,abStack_511,0x500);
        if (iVar6 != 0) {
          param_1[5] = param_2;
          param_1[6] = param_3;
          return 1;
        }
      }
    }
  }
  return 0;
}

