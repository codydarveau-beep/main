
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0006b630(int param_1,int param_2,uint param_3)

{
  int *piVar1;
  float *pfVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  byte bVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int *piVar12;
  float fVar13;
  uint uStack_20;
  
  if ((param_3 < 0x150) && (_DAT_00d2fb8c != 0)) {
    piVar12 = (int *)0xd2f8b0;
    iVar8 = _DAT_00d2fb8c;
    do {
      if (*piVar12 == *(int *)(param_2 + 0x6c) + -1) {
        if (piVar12[1] != *(int *)(param_1 + 0xdfcc)) {
          return 0;
        }
        iVar10 = param_3 * 0x298;
        uVar11 = *(uint *)(param_1 + 0x1124c + iVar10);
        iVar8 = 0;
        if (uVar11 == 0) {
          iVar8 = *(int *)(param_1 + 0x112a8 + iVar10);
          uVar11 = (uint)*(byte *)(iVar8 * 2 + 0x4296e0);
          iVar8 = *(byte *)(iVar8 * 2 + 0x4296e1) - 1;
        }
        fVar13 = *(float *)(param_1 + 0x11274 + iVar10);
        if (0.0 < *(float *)(param_1 + 0x11264 + iVar10)) {
          iVar8 = 0;
          uVar11 = 1;
        }
        if (0.0 < fVar13) {
          iVar8 = 0;
          uVar11 = 2;
        }
        uVar11 = (int)*(short *)(iVar8 * 200 + uVar11 * 0x14 + 0x429c00 +
                                ((uint)(*(int *)(param_2 + 0x60) != 0x50) * 3 + 1) * 2) *
                 *(int *)(param_2 + 0x58);
        if ((int)uVar11 < 100) {
          return 0;
        }
        iVar8 = *(int *)(param_1 + 0x112a8 + iVar10);
        uStack_20 = (uint)*(short *)(iVar8 * 2 + 0x4291c0);
        if (0.0 < fVar13) {
          uStack_20 = (int)(uStack_20 * 0x7d) / 100;
        }
        iVar9 = 0x3c;
        iVar4 = 100;
        if (0.0 < *(float *)(param_1 + 0x11130 + iVar10)) {
          iVar4 = 0x3c;
        }
        if (*(float *)(param_1 + 0x1112c + iVar10) <= 0.0) {
          iVar9 = 100;
        }
        iVar8 = (iVar9 * (uint)*(ushort *)(iVar8 * 2 + 0x427d40)) / 200 +
                (iVar4 * (uint)*(ushort *)(iVar8 * 2 + 0x428260)) / 100;
        if (0.0 < *(float *)(param_1 + 0x111d0 + iVar10)) {
          iVar4 = (int)((ulonglong)
                        ((longlong)(*(int *)(param_1 + 0x111d8 + iVar10) * iVar8 * 0xc) *
                        -0x51eb851f) >> 0x20);
          iVar8 = iVar8 + ((iVar4 >> 5) - (iVar4 >> 0x1f));
        }
        iVar4 = 0x5a;
        if (*(float *)(param_1 + 0x110f4 + iVar10) <= 0.0) {
          iVar4 = iVar8;
        }
        if ((int)uStack_20 < 1) {
          uStack_20 = 0;
        }
        iVar8 = 100 - uStack_20;
        if (100 < uStack_20) {
          iVar8 = 0;
        }
        iVar4 = (iVar8 * (uVar11 / 100)) / 100 - iVar4;
        iVar8 = 1;
        if (1 < iVar4) {
          iVar8 = iVar4;
        }
        iVar4 = *(int *)(param_1 + 0x11064);
        iVar9 = piVar12[0x22];
        piVar12[0x22] = *(int *)(param_2 + 0x60);
        piVar1 = (int *)(param_1 + 0x112a8 + iVar10);
        FUN_000a3870(param_3,*(undefined4 *)(param_1 + 0x112a4 + iVar10),iVar8);
        piVar12[0x22] = iVar9;
        if (*(int *)(param_2 + 0x60) == 0x4d) {
          if (*(int *)(param_1 + 0x11064) != iVar4) {
            iVar4 = (*(int *)(param_1 + 0x11064) - 1U & 0xf) * 0x30;
            *(undefined4 *)(param_1 + 0x10d78 + iVar4) = 10;
            *(undefined4 *)(param_1 + 0x10d70 + iVar4) = 0x3dcccccd;
            FUN_000a3e30();
          }
          fVar13 = *(float *)(param_1 + 0x4ab8);
          *(float *)(param_1 + 0x11230 + iVar10) = _DAT_0074a9f0 + fVar13;
          if ((0 < *(int *)(param_1 + 0x112ac + iVar10)) && (iVar4 = func_0x00094720(), iVar4 == 0))
          {
            fVar13 = fVar13 + _DAT_0074a70c;
            pfVar2 = (float *)(param_1 + 0x11238 + iVar10);
            if (*pfVar2 <= fVar13 && fVar13 != *pfVar2) {
              *(float *)(param_1 + 0x11238 + iVar10) = fVar13;
            }
            if (0.0 < *(float *)(param_1 + 0x1126c + iVar10)) {
              return iVar8;
            }
            iVar4 = *piVar1;
            iVar5 = ((uint)*(ushort *)(iVar4 * 2 + 0x428260) +
                    (uint)*(ushort *)(iVar4 * 2 + 0x427d40)) * 0x32;
            uVar11 = *(int *)(param_1 + 0x477e8) * 0x19660d + 0x3c6ef35f;
            *(uint *)(param_1 + 0x477e8) = uVar11;
            iVar9 = *(int *)(param_2 + 100);
            uVar6 = FUN_000a3f20(iVar9 * 4,iVar5);
            if ((uVar11 >> 0x10 ^ uVar11) % 10000 < uVar6) {
              iVar9 = iVar9 * 500;
              iVar5 = (int)((ulonglong)((longlong)((iVar9 + 5000) * iVar5) * -0x68db8bad) >> 0x20);
              iVar9 = iVar9 + 5000 + ((iVar5 >> 0xc) - (iVar5 >> 0x1f)) +
                      (uint)*(ushort *)(iVar4 * 2 + 0x428780) * -10;
              iVar4 = 1;
              if (1 < iVar9) {
                iVar4 = iVar9;
              }
              *(float *)(param_1 + 0x1126c + iVar10) = (float)iVar4 / _DAT_0074a288;
            }
          }
        }
        else {
          fVar13 = *(float *)(param_1 + 0x4ab8);
          *(float *)(param_1 + 0x1122c + iVar10) = _DAT_0074a460 + fVar13;
          if (0 < *(int *)(param_1 + 0x112ac + iVar10)) {
            iVar4 = func_0x00094720();
            if (iVar4 == 0) {
              bVar3 = *(byte *)(param_1 + 0x11228 + iVar10);
              bVar7 = 1;
              if (bVar3 < 0xfa) {
                bVar7 = bVar3 + 1;
              }
              *(byte *)(param_1 + 0x11228 + iVar10) = bVar7;
              if ((((2 < bVar7) && (iVar4 = *piVar1, *(short *)(iVar4 * 2 + 0x428ca0) == 0)) &&
                  (pfVar2 = (float *)(param_1 + 0x11264 + iVar10), *pfVar2 <= 0.0)) &&
                 (((*(float *)(param_1 + 0x112cc + iVar10) <= 0.0 &&
                   (*(float *)(param_1 + 0x11274 + iVar10) <= 0.0)) &&
                  (*(float *)(param_1 + 0x11110 + iVar10) <= fVar13)))) {
                uVar11 = *(int *)(param_1 + 0x477e8) * 0x19660d + 0x3c6ef35f;
                *(uint *)(param_1 + 0x477e8) = uVar11;
                iVar4 = (int)*(short *)(iVar4 * 2 + 0x4291c0);
                uVar6 = FUN_000a3f20(0x96,iVar4 * 100);
                if ((uVar11 >> 0x10 ^ uVar11) % 10000 < uVar6) {
                  *(float *)(param_1 + 0x11268 + iVar10) = fVar13;
                  iVar4 = iVar4 * -0x78 + 12000 + (uint)*(byte *)((int)piVar12 + 0x55) * 10;
                  iVar9 = 1;
                  if (1 < iVar4) {
                    iVar9 = iVar4;
                  }
                  *pfVar2 = (float)iVar9 / _DAT_0074a288;
                  *(undefined4 *)(param_1 + 0x112b4 + iVar10) = 0;
                  *(undefined1 *)(param_1 + 0x11228 + iVar10) = 0;
                }
              }
            }
            uVar11 = *(int *)(param_1 + 0x477e8) * 0x19660d + 0x3c6ef35f;
            *(uint *)(param_1 + 0x477e8) = uVar11;
            uVar11 = (uVar11 >> 0x10 ^ uVar11) & 7;
            func_0x000a3fc0(*(undefined4 *)(uVar11 * 4 + 0x5d4fd4),
                            *(undefined4 *)(uVar11 * 4 + 0x5d4ff4),0x41800000);
          }
        }
        return iVar8;
      }
      piVar12 = piVar12 + 0x3d;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  return 0;
}

