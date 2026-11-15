
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00067f30(int param_1,int param_2,float param_3)

{
  float *pfVar1;
  float *pfVar2;
  int *piVar3;
  undefined8 uVar4;
  byte bVar5;
  undefined4 uVar6;
  undefined1 auVar7 [16];
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  int *piVar16;
  float10 fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar22;
  undefined1 auVar21 [16];
  int iStack_70;
  
  iVar15 = param_2 * 0x298;
  iVar9 = *(int *)(param_1 + 0x111e8 + iVar15);
  if (0xffffffec < iVar9 - 0x20014U) {
    if (_DAT_00d2fb8c != 0) {
      piVar16 = (int *)0xd2f8b0;
      iVar14 = _DAT_00d2fb8c;
      do {
        if (*piVar16 == iVar9 + -0x20001) {
          if ((((piVar16[10] != 0) && (piVar16[5] != 0)) &&
              (piVar16[1] == *(int *)(param_1 + 0xdfcc))) &&
             ((0 < *(int *)(param_1 + 0x4ad0) &&
              (fVar18 = *(float *)(param_1 + 0x4aa0) - *(float *)(param_1 + 0x111f8 + iVar15),
              fVar19 = *(float *)(param_1 + 0x4aa4) - *(float *)(param_1 + 0x111fc + iVar15),
              fVar17 = (float10)func_0x00137820(fVar18 * fVar18 + fVar19 * fVar19),
              (float)fVar17 <= _DAT_0074a470)))) {
            pfVar1 = (float *)(param_1 + 0x111f8 + iVar15);
            fVar20 = (float)*(undefined8 *)(piVar16 + 0x29) - (float)*(undefined8 *)pfVar1;
            fVar22 = (float)((ulonglong)*(undefined8 *)(piVar16 + 0x29) >> 0x20) -
                     (float)((ulonglong)*(undefined8 *)pfVar1 >> 0x20);
            fVar19 = fVar20 * fVar20 + fVar22 * fVar22;
            fVar17 = (float10)func_0x00137820(fVar19);
            fVar18 = (float)fVar17;
            *(undefined4 *)(param_1 + 0x112b0 + iVar15) = 1;
            *(undefined4 *)(param_1 + 0x112c0 + iVar15) = 0;
            fVar17 = (float10)func_0x00137820(fVar19);
            fVar19 = (float)fVar17;
            if (_DAT_0074a494 < fVar19) {
              auVar7._4_4_ = fVar22;
              auVar7._0_4_ = fVar20;
              auVar7._8_8_ = 0;
              auVar21._4_4_ = fVar19;
              auVar21._0_4_ = fVar19;
              auVar21._8_8_ = 0;
              auVar21 = divps(auVar7,auVar21);
              *(longlong *)(param_1 + 0x11208 + iVar15) = auVar21._0_8_;
            }
            pfVar2 = (float *)(param_1 + 0x111fc + iVar15);
            iVar9 = *(int *)(param_1 + 0x112a8 + iVar15);
            if (fVar18 <= (float)*(ushort *)(iVar9 * 2 + 0x2bf210)) {
              if (0.0 < *(float *)(param_1 + 0x11210 + iVar15)) {
                return 1;
              }
              iVar9 = func_0x00094070(*pfVar1,*pfVar2,piVar16[0x29],piVar16[0x2a]);
              if (iVar9 != 0) {
                if (_DAT_00d42514 == 0) {
                  iStack_70 = 0;
                }
                else if (_DAT_00d4254c == 0) {
                  iStack_70 = 1;
                }
                else if (_DAT_00d42584 == 0) {
                  iStack_70 = 2;
                }
                else if (_DAT_00d425bc == 0) {
                  iStack_70 = 3;
                }
                else if (_DAT_00d425f4 == 0) {
                  iStack_70 = 4;
                }
                else if (_DAT_00d4262c == 0) {
                  iStack_70 = 5;
                }
                else if (_DAT_00d42664 == 0) {
                  iStack_70 = 6;
                }
                else if (_DAT_00d4269c == 0) {
                  iStack_70 = 7;
                }
                else if (_DAT_00d426d4 == 0) {
                  iStack_70 = 8;
                }
                else if (_DAT_00d4270c == 0) {
                  iStack_70 = 9;
                }
                else if (_DAT_00d42744 == 0) {
                  iStack_70 = 10;
                }
                else if (_DAT_00d4277c == 0) {
                  iStack_70 = 0xb;
                }
                else if (_DAT_00d427b4 == 0) {
                  iStack_70 = 0xc;
                }
                else if (_DAT_00d427ec == 0) {
                  iStack_70 = 0xd;
                }
                else if (_DAT_00d42824 == 0) {
                  iStack_70 = 0xe;
                }
                else {
                  if (_DAT_00d4285c != 0) {
                    return 1;
                  }
                  iStack_70 = 0xf;
                }
                piVar3 = (int *)(param_1 + 0x112a8 + iVar15);
                pfVar2 = (float *)(param_1 + 0x11210 + iVar15);
                *(undefined4 *)(param_1 + 0x11214 + iVar15) = *(undefined4 *)(param_1 + 0x4ab8);
                fVar17 = (float10)func_0x00094110();
                *pfVar2 = (float)fVar17;
                uVar10 = *(int *)(param_1 + 0x477e8) * 0x19660d + 0x3c6ef35f;
                *(uint *)(param_1 + 0x477e8) = uVar10;
                iVar9 = piVar16[4];
                uVar12 = (uint)*(byte *)((int)piVar16 + 0x51);
                if (*(float *)(param_1 + 0x4ab8) <= (float)piVar16[0x17] &&
                    (float)piVar16[0x17] != *(float *)(param_1 + 0x4ab8)) {
                  uVar12 = uVar12 + 2 + (uint)*(byte *)((int)piVar16 + 0x57);
                }
                iVar11 = func_0x000941f0();
                iVar14 = *piVar3;
                uVar12 = ((uint)*(ushort *)(iVar14 * 2 + 0x2bf730) - (iVar11 * 3 + uVar12 + iVar9))
                         + 0x50 + (uint)*(ushort *)(iVar14 * 2 + 0x2bfc50);
                uVar13 = 100;
                if ((int)uVar12 < 100) {
                  uVar13 = uVar12;
                }
                uVar12 = 5;
                if (5 < (int)uVar13) {
                  uVar12 = uVar13;
                }
                if ((uVar10 >> 0x10 ^ uVar10) % 100 < uVar12) {
                  *(int *)(param_1 + 0x477e8) = *(int *)(param_1 + 0x477e8) * 0x19660d + 0x3c6ef35f;
                  fVar19 = *(float *)(param_1 + 0x4ab8);
                  bVar5 = *(byte *)((int)piVar16 + 0x52);
                  iVar9 = func_0x00094500();
                  iVar9 = iVar9 - (uint)bVar5;
                  if (iVar9 < 2) {
                    iVar9 = 1;
                  }
                  fVar17 = (float10)func_0x00136dc0(*pfVar2,*(undefined4 *)
                                                             (iVar14 * 0x44 + 0x259794));
                  fVar19 = (float)fVar17 * _DAT_0074a2f0 + fVar19;
                  fVar20 = 0.0;
                  if (0x18 < *(ushort *)(*piVar3 * 2 + 0x2bf210)) {
                    fVar20 = fVar18 / _DAT_0074a4a8;
                  }
                  uVar8 = *(undefined4 *)(param_1 + 0x112a4 + iVar15);
                  fVar18 = *pfVar1;
                  fVar22 = pfVar1[1];
                  iStack_70 = iStack_70 * 0x38;
                  uVar6 = *(undefined4 *)(param_1 + 0xdfcc);
                  *(undefined4 *)(&DAT_00d42514 + iStack_70) = 1;
                  *(undefined4 *)(iStack_70 + 0xd42518) = uVar6;
                  *(int *)(iStack_70 + 0xd4251c) = param_2;
                  *(undefined4 *)(iStack_70 + 0xd42520) = uVar8;
                  *(int *)(iStack_70 + 0xd42524) = *piVar16;
                  uVar4 = *(undefined8 *)(piVar16 + 0x29);
                  *(int *)(iStack_70 + 0xd42528) = piVar16[9];
                  *(int *)(iStack_70 + 0xd4252c) = iVar9;
                  fVar20 = fVar20 + fVar19;
                  *(float *)(iStack_70 + 0xd42530) = fVar20;
                  *(float *)(iStack_70 + 0xd42534) = fVar19;
                  *(float *)(iStack_70 + 0xd42538) = fVar20;
                  *(float *)(iStack_70 + 0xd4253c) = fVar18;
                  *(float *)(iStack_70 + 0xd42540) = fVar22;
                  *(int *)(iStack_70 + 0xd42544) = (int)uVar4;
                  *(int *)(iStack_70 + 0xd42548) = (int)((ulonglong)uVar4 >> 0x20);
                }
                else {
                  func_0x00094440(piVar16[0x29],piVar16[0x2a]);
                }
              }
              return 1;
            }
            if (*(float *)(param_1 + 0x4ab8) < *(float *)(param_1 + 0x11114 + iVar15)) {
              return 1;
            }
            if (*(float *)(param_1 + 0x4ab8) < *(float *)(param_1 + 0x1111c + iVar15)) {
              return 1;
            }
            if (fVar18 <= _DAT_0074a414) {
              return 1;
            }
            fVar19 = *(float *)(iVar9 * 0x44 + 0x259790);
            uVar8 = func_0x00093b20((fVar20 / fVar18) * fVar19 * param_3 + *pfVar1,
                                    (fVar22 / fVar18) * fVar19 * param_3 + *pfVar2);
            *(undefined4 *)(param_1 + 0x112b4 + iVar15) = uVar8;
            return 1;
          }
          break;
        }
        piVar16 = piVar16 + 0x3d;
        iVar14 = iVar14 + -1;
      } while (iVar14 != 0);
    }
    *(undefined4 *)(param_1 + 0x111e8 + iVar15) = 0;
  }
  return 0;
}

