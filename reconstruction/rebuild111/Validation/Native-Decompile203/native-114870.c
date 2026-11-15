
int __thiscall FUN_00114870(uint *param_1,float param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar1 = *param_1;
  uVar6 = 0;
  uVar7 = 0;
  if (uVar1 < 0x13) {
    uVar7 = *(uint *)(&DAT_005e59a0 + uVar1 * 4);
  }
  uVar3 = 0x1c89;
  do {
    while (uVar5 = uVar3 + uVar6 >> 1, (uint)(&DAT_0035d3d4)[uVar5 * 5] < uVar7) {
      uVar6 = uVar5 + 1;
      if (uVar3 <= uVar6) goto LAB_001148be;
    }
    uVar3 = uVar5;
  } while (uVar6 < uVar5);
LAB_001148be:
  iVar4 = 0;
  if ((uVar6 < 0x1c89) && ((&DAT_0035d3d4)[uVar6 * 5] == uVar7)) {
    iVar4 = *(int *)(&DAT_002d944c + (uint)(ushort)(&DAT_003a6608)[uVar6] * 0x44);
  }
  uVar7 = (uint)(byte)param_1[0x14];
  if ((float)param_1[0x16] <= param_2) {
    uVar6 = (uint)(byte)param_1[0x15];
  }
  else {
    uVar7 = uVar7 + *(byte *)((int)param_1 + 0x56);
    uVar6 = (uint)(byte)param_1[0x15] + (uint)*(byte *)((int)param_1 + 0x56);
  }
  if ((uVar1 < 0x10) && ((0x8700U >> (uVar1 & 0x1f) & 1) != 0)) {
    iVar2 = *(byte *)((int)param_1 + 0x55) / 5 + uVar7 / 5 + uVar6 + (uVar6 / 10) * (uVar6 / 10);
  }
  else {
    iVar2 = uVar6 / 5 + uVar7 + *(byte *)((int)param_1 + 0x55) / 5 + (uVar7 / 10) * (uVar7 / 10);
  }
  return iVar2 + iVar4;
}

