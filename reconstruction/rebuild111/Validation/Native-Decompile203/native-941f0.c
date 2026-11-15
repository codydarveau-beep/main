
undefined1 __fastcall FUN_000941f0(uint *param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  ushort *puVar6;
  int iVar7;
  
  if (param_1 == (uint *)0x0) {
    return 0;
  }
  uVar4 = *param_1;
  if (uVar4 < 0x13) {
    if (param_2 == 0x152) {
      return 9;
    }
    if ((param_2 == 0x33) && (uVar4 == 4)) {
      return 1;
    }
    if (uVar4 == 0xd) {
      if (param_2 == 1) {
        return 1;
      }
    }
    else if ((param_2 == 1) && (uVar4 == 0xc)) {
      return 1;
    }
    uVar5 = param_1[0xe];
    if (uVar5 == 0) {
      uVar5 = (&DAT_002a7984)[uVar4];
    }
    uVar1 = param_1[0xc];
    iVar7 = -0x191;
    do {
      if (*(ushort *)(&DAT_002caa24 + iVar7 * 2) == param_2) {
        if (uVar1 == 0) {
          return 0;
        }
        if (1 < uVar5 - 0x29) {
          if (uVar5 == 0x21) {
            uVar2 = 10;
            goto LAB_000942c5;
          }
          uVar2 = 99;
          if (uVar5 == 0x28) goto LAB_000942c5;
          uVar2 = 0x32;
          if (0xfffffff8 < uVar5 - 0x28) goto LAB_000942c5;
          if (uVar5 != 8) {
            uVar2 = 0x46;
            if ((uVar5 - 0x28 < 0xffffffed) && (uVar2 = 0x32, uVar5 == 0)) {
              uVar2 = 10;
            }
            goto LAB_000942c5;
          }
        }
        uVar2 = 0x46;
LAB_000942c5:
        if (uVar2 < uVar1) {
          return 0;
        }
        if ((((((DAT_00d47194 == '\0') || (DAT_00d47188 != uVar4)) || (DAT_00d4718c != uVar5)) ||
             (uVar2 = 0, DAT_00d47190 != uVar1)) &&
            (((DAT_00d47334 == '\0' || (DAT_00d47328 != uVar4)) ||
             ((DAT_00d4732c != uVar5 || (uVar2 = 1, DAT_00d47330 != uVar1)))))) &&
           (((DAT_00d474d4 == '\0' || (DAT_00d474c8 != uVar4)) ||
            ((DAT_00d474cc != uVar5 || (uVar2 = 2, DAT_00d474d0 != uVar1)))))) {
          puVar6 = &DAT_002caa28;
          iVar3 = 0x24;
          while ((uVar4 != (byte)puVar6[-2] || (uVar5 != *(byte *)((int)puVar6 + -3)))) {
            puVar6 = puVar6 + 0xa9;
            iVar3 = iVar3 + -1;
            if (iVar3 == 0) {
              return 0;
            }
          }
          uVar2 = DAT_00d47668 % 3;
          iVar3 = uVar2 * 0x1a0;
          DAT_00d47668 = DAT_00d47668 + 1;
          FUN_00137420(&DAT_00d47188 + uVar2 * 0x68,0,0x1a0);
          (&DAT_00d47188)[uVar2 * 0x68] = uVar4;
          (&DAT_00d4718c)[uVar2 * 0x68] = uVar5;
          (&DAT_00d47190)[uVar2 * 0x68] = uVar1;
          (&DAT_00d47194)[iVar3] = 1;
          uVar4 = (uVar1 - 1) + (uint)(byte)puVar6[-1];
          uVar5 = (uint)*(byte *)((int)puVar6 + -1);
          if (uVar4 < *(byte *)((int)puVar6 + -1)) {
            uVar5 = uVar4;
          }
          for (; uVar5 != 0; uVar5 = uVar5 - 1) {
            uVar4 = (uint)*puVar6;
            if ((uVar4 < 0x191) &&
               ((byte)(&DAT_00d47195)[uVar4 + iVar3] < (byte)(&DAT_002ca570)[uVar4])) {
              (&DAT_00d47195)[uVar4 + iVar3] = (&DAT_00d47195)[uVar4 + iVar3] + 1;
            }
            puVar6 = puVar6 + 1;
          }
        }
        return *(undefined1 *)(uVar2 * 0x1a0 + 0xd47326 + iVar7);
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 != 0);
  }
  return 0;
}

