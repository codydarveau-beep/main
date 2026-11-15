
int __fastcall FUN_000a36d0(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(param_1 + 0x1e4);
  iVar1 = 0;
  if (uVar2 == 0) {
    uVar2 = (uint)*(byte *)(*(int *)(param_1 + 0x240) * 2 + 0x4296e0);
    iVar1 = *(byte *)(*(int *)(param_1 + 0x240) * 2 + 0x4296e1) - 1;
  }
  if (0.0 < *(float *)(param_1 + 0x1fc)) {
    iVar1 = 0;
    uVar2 = 1;
  }
  if (0.0 < *(float *)(param_1 + 0x20c)) {
    iVar1 = 0;
    uVar2 = 2;
  }
  return (int)*(short *)(iVar1 * 200 + uVar2 * 0x14 + 0x429c00 + param_2 * 2);
}

