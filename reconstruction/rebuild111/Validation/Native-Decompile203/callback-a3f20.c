
uint __fastcall FUN_000a3f20(int param_1,int param_2,int param_3,int param_4)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  iVar2 = *(int *)(param_1 + 0x10);
  if (0x62 < iVar2) {
    iVar2 = 99;
  }
  uVar1 = *(ushort *)(*(int *)(param_2 + 0x240) * 2 + 0x2bf730);
  uVar3 = 99;
  if (uVar1 < 99) {
    uVar3 = (uint)uVar1;
  }
  iVar4 = (int)((ulonglong)((longlong)(param_3 * param_4) * -0x51eb851f) >> 0x20);
  uVar3 = ((iVar4 >> 5) - (iVar4 >> 0x1f)) + param_3 * 100 +
          ((uint)*(ushort *)(*(int *)(param_2 + 0x240) * 2 + 0x428780) + (uVar3 - iVar2)) * -10;
  if ((0 < (int)uVar3) && (iVar2 = uVar3 + (uVar3 / 5 & 0xfffffffe) * -5, iVar2 != 0)) {
    uVar3 = (uVar3 - iVar2) + 10;
  }
  uVar5 = 10000;
  if ((int)uVar3 < 10000) {
    uVar5 = uVar3;
  }
  uVar3 = 0;
  if (0 < (int)uVar5) {
    uVar3 = uVar5;
  }
  return uVar3;
}

