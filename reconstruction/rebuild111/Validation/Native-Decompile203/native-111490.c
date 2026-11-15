
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint * __fastcall FUN_00111490(uint *param_1)

{
  float *pfVar1;
  float *pfVar2;
  float fVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  byte bVar7;
  ushort uVar8;
  short sVar9;
  ushort uVar10;
  bool bVar11;
  undefined1 auVar12 [16];
  undefined **ppuVar13;
  char cVar25;
  int iVar14;
  uint *puVar15;
  undefined **ppuVar16;
  uint *puVar17;
  uint uVar18;
  float *pfVar19;
  float *pfVar20;
  uint uVar21;
  uint uVar22;
  int iVar23;
  uint *puVar24;
  undefined4 uVar26;
  int iVar27;
  undefined4 *puVar28;
  uint uVar29;
  bool bVar30;
  bool bVar31;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 fVar32;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  float10 extraout_ST0_03;
  float10 extraout_ST0_04;
  float fVar33;
  float fVar34;
  float fVar36;
  undefined1 auVar35 [16];
  float fStack_c4;
  uint uStack_c0;
  int iStack_bc;
  int iStack_b0;
  
  puVar24 = (uint *)param_1[0x20];
  if (puVar24 == (uint *)0x0) {
    return (uint *)0x0;
  }
  if (DAT_00be3098 < (float)param_1[0x32]) {
    return puVar24;
  }
  param_1[0x20] = 0;
  puVar15 = (uint *)*param_1;
  if ((puVar15 < (uint *)0x12) && ((0x38ea0U >> ((uint)puVar15 & 0x1f) & 1) != 0)) {
    iVar14 = FUN_000ca050();
    if (iVar14 == 0) {
      return (uint *)0x0;
    }
    uVar18 = param_1[0x1c];
    if ((uint *)(&DAT_00bef884)[uVar18 * 0xa6] != (uint *)param_1[0x1f]) {
      return (uint *)(&DAT_00bef884)[uVar18 * 0xa6];
    }
    uVar29 = *param_1;
    if ((uVar29 < 0x10) && ((0x8600U >> (uVar29 & 0x1f) & 1) != 0)) {
      iVar27 = 0x60;
    }
    else {
      iVar14 = 0x18;
      if (puVar24 == (uint *)0xe6) {
        iVar14 = 0x50;
      }
      iVar27 = 0x60;
      if (uVar29 != 8) {
        iVar27 = iVar14;
      }
    }
    puVar15 = (uint *)FUN_00137820(((float)param_1[0x29] - (float)(&DAT_00bef7d8)[uVar18 * 0xa6]) *
                                   ((float)param_1[0x29] - (float)(&DAT_00bef7d8)[uVar18 * 0xa6]) +
                                   ((float)param_1[0x2a] - (float)(&DAT_00bef7dc)[uVar18 * 0xa6]) *
                                   ((float)param_1[0x2a] - (float)(&DAT_00bef7dc)[uVar18 * 0xa6]));
    if ((float)iVar27 < (float)extraout_ST0_00) {
      return puVar15;
    }
    pfVar20 = (float *)(&DAT_00bef7dc + uVar18 * 0xa6);
    pfVar19 = (float *)(&DAT_00bef7d8 + uVar18 * 0xa6);
    pfVar1 = (float *)(param_1 + 0x2a);
    pfVar2 = (float *)(param_1 + 0x29);
    fVar33 = *pfVar20;
    fVar34 = *pfVar19;
    fVar36 = *pfVar1;
    fVar3 = *pfVar2;
    iVar14 = FUN_00095200(fVar3,fVar36,fVar34,fVar33);
    if (iVar14 == 0) {
      return (uint *)0x0;
    }
    if ((DAT_00c2c8bc != (code *)0x0) &&
       (iVar14 = (*DAT_00c2c8bc)(DAT_00c2c8c0,fVar3,fVar36,fVar34,fVar33), iVar14 == 0)) {
      return (uint *)0x0;
    }
    if (param_1[0x10] != 0) goto LAB_0011182d;
    if ((puVar24 == (uint *)0xca) || (puVar24 == (uint *)0x1)) {
      puVar15 = (uint *)param_1[6];
      puVar17 = (uint *)0x0;
    }
    else {
      puVar17 = (uint *)FUN_00113920();
      puVar15 = (uint *)param_1[6];
      if (puVar15 < puVar17) {
        return puVar17;
      }
    }
    iVar14 = FUN_00095650((int)puVar15 - (int)puVar17);
    if (iVar14 == 0) {
      return (uint *)0x0;
    }
    param_1[0x10] = 1;
    if (puVar24 == (uint *)0xe6) {
      iVar14 = 0;
      do {
        iVar27 = FUN_000ca050();
        if ((iVar27 != 0) &&
           (fVar32 = (float10)FUN_00137820((*pfVar19 - (float)(&DAT_00bef7d8)[iVar14 * 0xa6]) *
                                           (*pfVar19 - (float)(&DAT_00bef7d8)[iVar14 * 0xa6]) +
                                           (*pfVar20 - (float)(&DAT_00bef7dc)[iVar14 * 0xa6]) *
                                           (*pfVar20 - (float)(&DAT_00bef7dc)[iVar14 * 0xa6])),
           (float)fVar32 <= DAT_0074a34c)) {
          uVar6 = (&DAT_00bef7dc)[iVar14 * 0xa6];
          uVar26 = (&DAT_00bef7d8)[iVar14 * 0xa6];
          fVar33 = *pfVar20;
          fVar34 = *pfVar19;
          iVar27 = FUN_00095200(fVar34,fVar33,uVar26,uVar6);
          if ((iVar27 != 0) &&
             ((DAT_00c2c8bc == (code *)0x0 ||
              (iVar27 = (*DAT_00c2c8bc)(DAT_00c2c8c0,fVar34,fVar33,uVar26,uVar6), iVar27 != 0)))) {
            iVar27 = -0x22470;
            do {
              if (*(short *)(iVar27 + 0x3a63d0) == 0xe6) {
                fVar33 = (float)*(uint *)(iVar27 + 0x3a6518 + param_1[0x21] * 4) * DAT_0074a494;
                goto LAB_00111daf;
              }
              iVar27 = iVar27 + 0x1b0;
            } while (iVar27 != 0);
            fVar33 = 0.0;
LAB_00111daf:
            FUN_000a9340(param_1[0x21] * 10 + 0x14,fVar33);
          }
        }
        iVar14 = iVar14 + 1;
      } while (iVar14 != 0x150);
      fVar34 = *pfVar20;
      fVar33 = *pfVar19;
      goto LAB_00112ff7;
    }
    uVar29 = (uint)(byte)param_1[0x15];
    if (DAT_00be3098 < (float)param_1[0x16]) {
      uVar29 = uVar29 + *(byte *)((int)param_1 + 0x56);
    }
    uVar21 = param_1[4];
    iVar14 = 0;
    if (*param_1 == 0xf) {
      iVar14 = FUN_000941f0();
    }
    DAT_00c25dc8 = DAT_00c25dc8 * 0x19660d + 0x3c6ef35f;
    uVar22 = DAT_00c25dc8 >> 0x10 ^ DAT_00c25dc8;
    iVar27 = FUN_000f3500();
    uVar21 = ((uVar21 + uVar29 + iVar14) - iVar27) + 0x50;
    uVar29 = 100;
    if ((int)uVar21 < 100) {
      uVar29 = uVar21;
    }
    uVar21 = 5;
    if (5 < (int)uVar29) {
      uVar21 = uVar29;
    }
    if (uVar21 <= uVar22 % 100) {
      fVar33 = *pfVar20;
      fVar34 = *pfVar19;
      goto LAB_00112d0b;
    }
    iVar27 = FUN_00114870(DAT_00be3098);
    uVar29 = param_1[0x21];
    iVar23 = FUN_00114980();
    iVar14 = uVar29 * 0xf;
    if (puVar24 != (uint *)0xd) {
      iVar14 = 0;
    }
    iVar14 = iVar14 + iVar27;
    if (*param_1 == 5) {
      iVar27 = FUN_000941f0();
      iVar14 = iVar14 + iVar27 * 3;
    }
    puVar15 = (uint *)FUN_000a36d0();
    if ((int)puVar15 < 1) {
      return puVar15;
    }
    uVar8 = *(ushort *)(&DAT_00427d40 + (&DAT_00bef888)[uVar18 * 0xa6] * 2);
    uVar29 = FUN_000cedf0();
    if ((int)uVar29 < 1) {
      uVar29 = 0;
    }
    iVar27 = 100 - uVar29;
    if (100 < uVar29) {
      iVar27 = 0;
    }
    uVar21 = (iVar27 * ((((iVar14 * iVar23) / 100) * (int)puVar15) / 100)) / 100 - (uint)uVar8;
    uVar29 = 1;
    if (1 < (int)uVar21) {
      uVar29 = uVar21;
    }
    param_1[0x13] = uVar29;
    param_1[0x12] = 0;
    if (puVar24 != (uint *)0x1) {
      if ((puVar24 == (uint *)0xd3) || (puVar24 == (uint *)0xca)) {
        uVar21 = (int)uVar29 / (int)param_1[0xf];
        param_1[0x13] = uVar21;
        param_1[0x12] = uVar29 % param_1[0xf];
        if ((int)uVar21 < 1) {
          param_1[0x13] = 1;
          param_1[0x12] = 0;
        }
        if (puVar24 == (uint *)0xca) goto LAB_0011182d;
      }
      FUN_00114370(*pfVar19,*pfVar20);
    }
LAB_0011182d:
    uVar29 = param_1[0x13];
    if (param_1[0x12] != 0) {
      uVar29 = uVar29 + 1;
      param_1[0x12] = param_1[0x12] - 1;
    }
    if (puVar24 == (uint *)0x182) {
      fVar32 = (float10)FUN_00137820((*pfVar2 - *pfVar19) * (*pfVar2 - *pfVar19) +
                                     (*pfVar1 - *pfVar20) * (*pfVar1 - *pfVar20));
      ppuVar13 = &PTR_DAT_00384110;
      do {
        ppuVar16 = ppuVar13;
        ppuVar13 = ppuVar16 + 0x6c;
      } while (*(short *)ppuVar16 != 0x182);
      if ((float)fVar32 <= (float)(*(short *)((int)ppuVar16 + (param_1[0x21] + 0x18) * 2) * 8 + 4))
      goto LAB_001118d7;
    }
    else {
LAB_001118d7:
      FUN_000a3870(param_1[0x1c],param_1[0x1f],uVar29);
    }
    if ((int)(&DAT_00bef88c)[uVar18 * 0xa6] < 1) {
LAB_0011263f:
      if (((uint)puVar24 & 0xfffffffb) == 0x182) {
        ppuVar13 = &PTR_DAT_00384110;
        do {
          ppuVar16 = ppuVar13;
          ppuVar13 = ppuVar16 + 0x6c;
        } while (puVar24 != (uint *)(uint)*(ushort *)ppuVar16);
        if (puVar24 == (uint *)0x182) {
          pfVar19 = pfVar2;
        }
        fVar33 = *pfVar19;
        if (puVar24 == (uint *)0x182) {
          pfVar20 = pfVar1;
        }
        fVar34 = *pfVar20;
        uVar8 = *(ushort *)((int)ppuVar16 + (param_1[0x21] + 0x18) * 2);
        puVar28 = &DAT_00bef648;
        uVar29 = 0;
        do {
          if (((uVar29 != param_1[0x1c]) && (iVar14 = FUN_000ca050(), iVar14 != 0)) &&
             (fVar32 = (float10)FUN_00137820((fVar33 - (float)puVar28[100]) *
                                             (fVar33 - (float)puVar28[100]) +
                                             (fVar34 - (float)puVar28[0x65]) *
                                             (fVar34 - (float)puVar28[0x65])),
             (float)fVar32 <= (float)((short)uVar8 * 8 + 4))) {
            uVar6 = puVar28[100];
            uVar26 = puVar28[0x65];
            iVar14 = FUN_00095200(fVar33,fVar34,uVar6,uVar26);
            if ((iVar14 != 0) &&
               ((DAT_00c2c8bc == (code *)0x0 ||
                (iVar14 = (*DAT_00c2c8bc)(DAT_00c2c8c0,fVar33,fVar34,uVar6,uVar26), iVar14 != 0))))
            {
              uVar21 = puVar28[0x79];
              iVar14 = 0;
              if (uVar21 == 0) {
                uVar21 = (uint)(byte)(&DAT_004296e0)[puVar28[0x90] * 2];
                iVar14 = (byte)(&DAT_004296e1)[puVar28[0x90] * 2] - 1;
              }
              if (0.0 < (float)puVar28[0x7f]) {
                uVar21 = 1;
                iVar14 = 0;
              }
              if (0.0 < (float)puVar28[0x83]) {
                uVar21 = 2;
                iVar14 = 0;
              }
              sVar9 = *(short *)(&DAT_00429c00 + uVar21 * 0x14 + iVar14 * 200);
              if (0 < sVar9) {
                uVar10 = *(ushort *)(&DAT_00427d40 + puVar28[0x90] * 2);
                uVar22 = FUN_000cedf0();
                iVar14 = FUN_00114870(DAT_00be3098);
                uVar21 = param_1[0x21];
                if ((int)puVar24 < 0x17a) {
                  switch(puVar24) {
                  case (uint *)0xad:
                  case (uint *)0xb4:
                    iVar27 = uVar21 * 0x19 + 0x7d;
                    break;
                  case (uint *)0xae:
                  case (uint *)0xaf:
                  case (uint *)0xb0:
                  case (uint *)0xb1:
                  case (uint *)0xb2:
                  case (uint *)0xb3:
                  case (uint *)0xb5:
                  case (uint *)0xb6:
                  case (uint *)0xb7:
                  case (uint *)0xb8:
                  case (uint *)0xb9:
                  case (uint *)0xba:
                  case (uint *)0xbb:
                  case (uint *)0xbc:
                  case (uint *)0xbd:
                  case (uint *)0xbe:
                  case (uint *)0xbf:
                  case (uint *)0xc0:
                  case (uint *)0xc1:
                  case (uint *)0xc2:
                  case (uint *)0xc3:
                  case (uint *)0xc4:
                  case (uint *)0xc5:
                  case (uint *)0xc6:
                  case (uint *)0xc7:
                  case (uint *)0xc8:
                  case (uint *)0xc9:
                  case (uint *)0xcb:
                  case (uint *)0xcc:
                  case (uint *)0xcd:
                  case (uint *)0xce:
                  case (uint *)0xcf:
                  case (uint *)0xd0:
                  case (uint *)0xd1:
                  case (uint *)0xd2:
switchD_001128aa_caseD_ae:
                    iVar27 = uVar21 * 0x1e + 0xbe;
                    if (((int)puVar24 - 0x186U & 0xfffffffd) != 0) {
                      iVar27 = 100;
                    }
                    break;
                  case (uint *)0xca:
                    iVar27 = uVar21 * 0x14 + 100;
                    break;
                  case (uint *)0xd3:
                    iVar27 = uVar21 * 0x32 + 0x96;
                    break;
                  default:
                    if (puVar24 != (uint *)0x8e) goto switchD_001128aa_caseD_ae;
                    iVar27 = uVar21 * 0x28 + 300;
                  }
                }
                else if (puVar24 == (uint *)0x17a) {
                  iVar27 = uVar21 * 10 + 100;
                }
                else {
                  if ((puVar24 != (uint *)0x182) && (puVar24 != (uint *)0x184))
                  goto switchD_001128aa_caseD_ae;
                  iVar27 = uVar21 * 0x14 + 0xa0;
                }
                if ((int)uVar22 < 1) {
                  uVar22 = 0;
                }
                iVar23 = 100 - uVar22;
                if (100 < uVar22) {
                  iVar23 = 0;
                }
                iVar14 = (iVar23 * ((((iVar27 * iVar14) / 100) * (int)sVar9) / 100)) / 100 -
                         (uint)uVar10;
                if (iVar14 < 2) {
                  iVar14 = 1;
                }
                FUN_000a3870(uVar29,puVar28[0x8f],iVar14);
                if ((puVar24 == (uint *)0x186) && (0 < (int)puVar28[0x91])) {
                  FUN_000a3fc0((float)puVar28[100] - fVar33,(float)puVar28[0x65] - fVar34,
                               (float)((int)(short)*(ushort *)
                                                    ((int)ppuVar16 + (param_1[0x21] + 0x2c) * 2) <<
                                      3));
                }
              }
            }
          }
          uVar29 = uVar29 + 1;
          puVar28 = puVar28 + 0xa6;
        } while (uVar29 != 0x150);
      }
    }
    else {
      if (puVar24 == (uint *)0x184) {
        iVar14 = -0x22470;
        do {
          if (*(short *)(iVar14 + 0x3a63d0) == 0x184) {
            fVar33 = (float)*(uint *)(iVar14 + 0x3a6518 + param_1[0x21] * 4) * DAT_0074a494;
            goto LAB_00112622;
          }
          iVar14 = iVar14 + 0x1b0;
        } while (iVar14 != 0);
        fVar33 = 0.0;
LAB_00112622:
        FUN_000a9340(100,fVar33);
        goto LAB_0011263f;
      }
      if (puVar24 == (uint *)0x8e) {
        fVar34 = (float)*(undefined8 *)pfVar2 - (float)*(undefined8 *)pfVar19;
        fVar36 = (float)((ulonglong)*(undefined8 *)pfVar2 >> 0x20) -
                 (float)((ulonglong)*(undefined8 *)pfVar19 >> 0x20);
        fVar32 = (float10)FUN_00137820(fVar34 * fVar34 + fVar36 * fVar36);
        fVar33 = (float)fVar32;
        if (DAT_0074a494 < fVar33) {
          auVar12._4_4_ = fVar36;
          auVar12._0_4_ = fVar34;
          auVar12._8_8_ = 0;
          auVar35._4_4_ = fVar33;
          auVar35._0_4_ = fVar33;
          auVar35._8_8_ = 0;
          auVar35 = divps(auVar12,auVar35);
          *(longlong *)(&DAT_00bef7e8 + uVar18 * 0x298) = auVar35._0_8_;
        }
      }
      else {
        if (puVar24 != (uint *)0xd) goto LAB_0011263f;
        FUN_000a9510(param_1[0x21] * 4 + 10,(float)param_1[0x21] * DAT_0074a238 + DAT_0074a344);
      }
    }
    puVar15 = (uint *)param_1[0xf];
    if (puVar15 < (uint *)0x2) {
      if ((int)(&DAT_00bef88c)[uVar18 * 0xa6] < 1) {
        return puVar15;
      }
    }
    else {
      if ((int)(&DAT_00bef88c)[uVar18 * 0xa6] < 1) {
        return puVar15;
      }
      if ((&DAT_00bef884)[uVar18 * 0xa6] == param_1[0x1f]) {
        param_1[0xf] = (int)puVar15 - 1;
        param_1[0x20] = (uint)puVar24;
        fVar33 = DAT_00be3098 + DAT_0074a2c0;
        goto LAB_00112a74;
      }
    }
    if (puVar24 == (uint *)0x1) {
      puVar24 = (uint *)FUN_00114a20();
    }
    else if ((puVar24 == (uint *)0xca) && (puVar24 = (uint *)FUN_000941f0(), puVar24 != (uint *)0x0)
            ) {
      param_1[0x11] = 0xca;
      fVar33 = DAT_00be3098;
      param_1[0x28] = (uint)(DAT_0074a578 + DAT_00be3098);
      param_1[0x35] = (uint)fVar33;
    }
  }
  else {
    if ((int)puVar24 - 1U < 2) {
LAB_0011155d:
      iVar14 = FUN_000ca050();
      if (iVar14 == 0) {
        return (uint *)0x0;
      }
      uVar18 = param_1[0x1c];
      if ((uint *)(&DAT_00bef884)[uVar18 * 0xa6] != (uint *)param_1[0x1f]) {
        return (uint *)(&DAT_00bef884)[uVar18 * 0xa6];
      }
      iVar14 = 0x18;
      if (puVar24 == (uint *)0x33) {
        iVar14 = 0x48;
      }
      puVar15 = (uint *)FUN_00137820(((float)param_1[0x29] - (float)(&DAT_00bef7d8)[uVar18 * 0xa6])
                                     * ((float)param_1[0x29] - (float)(&DAT_00bef7d8)[uVar18 * 0xa6]
                                       ) + ((float)param_1[0x2a] -
                                           (float)(&DAT_00bef7dc)[uVar18 * 0xa6]) *
                                           ((float)param_1[0x2a] -
                                           (float)(&DAT_00bef7dc)[uVar18 * 0xa6]));
      if ((float)iVar14 < (float)extraout_ST0) {
        return puVar15;
      }
      pfVar20 = (float *)(&DAT_00bef7dc + uVar18 * 0xa6);
      iVar14 = FUN_00094070(param_1[0x29],param_1[0x2a],(&DAT_00bef7d8)[uVar18 * 0xa6],*pfVar20);
      if (iVar14 == 0) {
        return (uint *)0x0;
      }
      if (puVar24 == (uint *)0x33) {
        uVar21 = param_1[0x21] + (uint)(param_1[0x21] == 0);
        uVar29 = 10;
        if (uVar21 < 10) {
          uVar29 = uVar21;
        }
        uVar29 = (uint)*(ushort *)(uVar29 * 2 + 0x383496);
        puVar15 = (uint *)(param_1[6] - uVar29);
        if (param_1[6] < uVar29) {
          return puVar15;
        }
        iVar14 = FUN_00095650(puVar15);
        if (iVar14 == 0) {
          return (uint *)0x0;
        }
        uVar29 = (uint)*(byte *)((int)param_1 + 0x53);
        if ((float)param_1[0x16] <= DAT_00be3098) {
          cVar25 = (char)(uVar29 * 0x25 >> 8);
          uVar21 = (uint)((byte)(((byte)(*(byte *)((int)param_1 + 0x53) - cVar25) >> 1) + cVar25) >>
                         2);
          iVar14 = uVar21 * uVar21 + uVar29;
        }
        else {
          uVar29 = uVar29 + *(byte *)((int)param_1 + 0x56);
          iVar14 = (uVar29 / 7) * (uVar29 / 7) + uVar29;
        }
        DAT_00c25dc8 = DAT_00c25dc8 * 0x19660d + 0x3c6ef35f;
        iStack_b0 = (int)(((DAT_00c25dc8 >> 0x10 ^ DAT_00c25dc8) %
                           ((uVar29 - iVar14) + 1 + (uVar29 / 5) * (uVar29 / 5)) + iVar14) * 0x7d) /
                    100;
      }
      else {
        iVar14 = FUN_00098af0();
        if (iVar14 < 0) {
          iStack_b0 = 0x19;
        }
        else {
          iStack_b0 = *(int *)(&DAT_002d944c + iVar14 * 0x44);
        }
        uVar29 = (uint)(byte)param_1[0x14];
        if ((float)param_1[0x16] <= DAT_00be3098) {
          iVar14 = (uVar29 / 10) * (uVar29 / 10);
          uVar21 = (uint)(byte)param_1[0x15];
        }
        else {
          uVar29 = uVar29 + *(byte *)((int)param_1 + 0x56);
          iVar14 = (uVar29 / 10) * (uVar29 / 10);
          uVar21 = (uint)(byte)param_1[0x15] + (uint)*(byte *)((int)param_1 + 0x56);
        }
        bVar7 = *(byte *)((int)param_1 + 0x55);
        iVar27 = FUN_000941f0();
        iStack_b0 = iStack_b0 + bVar7 / 5 + uVar21 / 5 + uVar29 + iVar14 + iVar27 * 4;
        if (puVar24 == (uint *)0x2) {
          iStack_b0 = (int)((param_1[0x21] * 0x1e + 100) * iStack_b0) / 100;
        }
        DAT_00c25dc8 = DAT_00c25dc8 * 0x19660d + 0x3c6ef35f;
        uVar21 = DAT_00c25dc8 >> 0x10 ^ DAT_00c25dc8;
        iVar14 = FUN_000f3500();
        uVar29 = (uint)(byte)param_1[0x15];
        if (DAT_00be3098 < (float)param_1[0x16]) {
          uVar29 = uVar29 + *(byte *)((int)param_1 + 0x56);
        }
        uVar29 = (param_1[4] - iVar14) + 0x50 + uVar29;
        uVar22 = 100;
        if ((int)uVar29 < 100) {
          uVar22 = uVar29;
        }
        uVar29 = 5;
        if (5 < (int)uVar22) {
          uVar29 = uVar22;
        }
        if (uVar29 <= uVar21 % 100) {
          fVar33 = *pfVar20;
          fVar34 = (float)(&DAT_00bef7d8)[uVar18 * 0xa6];
LAB_00112d0b:
          puVar24 = (uint *)FUN_00094440(fVar34,fVar33);
          return puVar24;
        }
      }
      FUN_00114540(param_1[0x1f],iStack_b0,puVar24 == (uint *)0x33);
      if ((uint *)0xfffffffd < (uint *)((int)puVar24 - 3U)) {
        return (uint *)((int)puVar24 - 3U);
      }
      fVar34 = *pfVar20;
      fVar33 = (float)(&DAT_00bef7d8)[uVar18 * 0xa6];
LAB_00112ff7:
      puVar24 = (uint *)FUN_00114370(fVar33,fVar34);
      return puVar24;
    }
    if (puVar24 == (uint *)0xa) {
      puVar24 = (uint *)param_1[0x1d];
      if ((int)puVar24 < 0) {
        puVar15 = (uint *)0x0;
      }
      else {
        if (DAT_00d2fb8c == 0) {
          return puVar24;
        }
        puVar15 = &DAT_00d2f8b0;
        iVar14 = DAT_00d2fb8c;
        while ((uint *)*puVar15 != puVar24) {
          puVar15 = puVar15 + 0x3d;
          iVar14 = iVar14 + -1;
          if (iVar14 == 0) {
            return puVar24;
          }
        }
        if (puVar15[5] == 0) {
          return puVar24;
        }
        if ((uint *)puVar15[1] != DAT_00bec5ac) {
          return (uint *)puVar15[1];
        }
        if ((uint *)puVar15[9] != (uint *)param_1[0x1f]) {
          return (uint *)puVar15[9];
        }
      }
      pfVar20 = (float *)&DAT_00be3080;
      if (puVar15 != (uint *)0x0) {
        pfVar20 = (float *)(puVar15 + 0x29);
      }
      fVar33 = *pfVar20;
      pfVar20 = (float *)&DAT_00be3084;
      if (puVar15 != (uint *)0x0) {
        pfVar20 = (float *)(puVar15 + 0x2a);
      }
      fVar34 = *pfVar20;
      puVar24 = (uint *)FUN_00137820(((float)param_1[0x29] - fVar33) *
                                     ((float)param_1[0x29] - fVar33) +
                                     ((float)param_1[0x2a] - fVar34) *
                                     ((float)param_1[0x2a] - fVar34));
      if (_DAT_0074a498 < (float)extraout_ST0_01) {
        return puVar24;
      }
      iVar14 = FUN_00094070(param_1[0x29],param_1[0x2a],fVar33,fVar34);
      if (iVar14 == 0) {
        return (uint *)0x0;
      }
      uVar18 = (uint)*(byte *)((int)param_1 + 0x53);
      if (DAT_00be3098 < (float)param_1[0x16]) {
        uVar18 = uVar18 + *(byte *)((int)param_1 + 0x56);
      }
      iVar27 = (param_1[0x21] * 8 + 4) * (uVar18 + param_1[4] >> 3);
      iVar14 = 1;
      if (1 < iVar27) {
        iVar14 = iVar27;
      }
      if (puVar15 == (uint *)0x0) {
        iVar27 = DAT_00be30b4 - DAT_00be30b0;
        if (iVar14 < DAT_00be30b4 - DAT_00be30b0) {
          iVar27 = iVar14;
        }
        DAT_00be30b0 = DAT_00be30b0 + iVar27;
      }
      else {
        iVar14 = FUN_00095650(puVar15[6]);
        if (iVar14 == 0) {
          return (uint *)0x0;
        }
      }
      FUN_001142c0(fVar33,fVar34);
      goto LAB_00112ff7;
    }
    if (puVar24 == (uint *)0x33) goto LAB_0011155d;
    if ((puVar24 == (uint *)0x50) || (puVar24 == (uint *)0x4d)) {
      uVar18 = param_1[0x21];
      if (((DAT_00c260c4 != 0) || (uVar29 = 0, DAT_00be3098 < _DAT_00c260c0)) &&
         ((DAT_00c278d4 != 0 || (uVar29 = 1, DAT_00be3098 < _DAT_00c278d0)))) {
        puVar15 = (uint *)CONCAT31((int3)((uint)puVar15 >> 8),DAT_00c290e4 != 0);
        uVar29 = -(uint)(DAT_00be3098 < _DAT_00c290e0 || DAT_00c290e4 != 0) | 2;
      }
      if (uVar18 == 0) {
        return puVar15;
      }
      if ((int)uVar29 < 0) {
        return puVar15;
      }
      fVar32 = (float10)FUN_00137820(((float)param_1[0x29] - (float)param_1[0x25]) *
                                     ((float)param_1[0x29] - (float)param_1[0x25]) +
                                     ((float)param_1[0x2a] - (float)param_1[0x26]) *
                                     ((float)param_1[0x2a] - (float)param_1[0x26]));
      if (*(float *)(&DAT_002d4874 + (int)puVar24 * 0x1c) <= (float)fVar32 &&
          (float)fVar32 != *(float *)(&DAT_002d4874 + (int)puVar24 * 0x1c)) {
        return (uint *)((int)puVar24 * 9);
      }
      uVar21 = param_1[0x25];
      uVar22 = param_1[0x26];
      uVar4 = param_1[0x2a];
      uVar5 = param_1[0x29];
      iVar14 = FUN_00095200(uVar5,uVar4,uVar21,uVar22);
      if (iVar14 == 0) {
        return (uint *)0x0;
      }
      if ((DAT_00c2c8bc != (code *)0x0) &&
         (iVar14 = (*DAT_00c2c8bc)(DAT_00c2c8c0,uVar5,uVar4,uVar21,uVar22), iVar14 == 0)) {
        return (uint *)0x0;
      }
      uVar6 = *(undefined4 *)(&DAT_002d4878 + (int)puVar24 * 0x1c);
      iVar14 = FUN_00114b60(param_1[0x25],param_1[0x26],uVar6);
      if (iVar14 == 0) {
        return (uint *)0x0;
      }
      uVar21 = 10;
      if (uVar18 < 10) {
        uVar21 = uVar18;
      }
      puVar15 = (uint *)(param_1[6] -
                        (uint)*(ushort *)(&DAT_0038309a + uVar21 * 2 + (int)puVar24 * 0x14));
      if (param_1[6] < (uint)*(ushort *)(&DAT_0038309a + uVar21 * 2 + (int)puVar24 * 0x14)) {
        return puVar15;
      }
      iVar14 = FUN_00095650(puVar15);
      if (iVar14 == 0) {
        return (uint *)0x0;
      }
      uVar21 = (uint)*(byte *)((int)param_1 + 0x53);
      if (DAT_00be3098 < (float)param_1[0x16]) {
        uVar21 = uVar21 + *(byte *)((int)param_1 + 0x56);
      }
      iVar27 = (uVar21 / 7) * (uVar21 / 7) + uVar21;
      DAT_00c25dc8 = DAT_00c25dc8 * 0x19660d + 0x3c6ef35f;
      uVar22 = DAT_00c25dc8 >> 0x10 ^ DAT_00c25dc8;
      iVar23 = uVar29 * 0x1810;
      FUN_00137420(&DAT_00c26070 + iVar23,0,0x1810);
      iVar14 = uVar18 * 0x14 + 0x50;
      if (puVar24 == (uint *)0x50) {
        iVar14 = uVar18 * 0x28 + 100;
      }
      *(uint *)(&DAT_00c260dc + iVar23) = *param_1 + 1;
      *(undefined8 *)(&DAT_00c260b4 + uVar29 * 0x604) = *(undefined8 *)(param_1 + 0x25);
      fVar33 = DAT_00be3098;
      (&DAT_00c260bc)[uVar29 * 0x604] = DAT_00be3098;
      (&DAT_00c260a8)[uVar29 * 0x604] = fVar33;
      (&DAT_00c260d0)[uVar29 * 0x604] = puVar24;
      *(uint *)(&DAT_00c260d4 + iVar23) = uVar18;
      uVar26 = 4;
      if (puVar24 == (uint *)0x50) {
        uVar26 = 10;
      }
      (&DAT_00c260d8)[uVar29 * 0x604] = uVar6;
      (&DAT_00c260cc)[uVar29 * 0x604] = uVar26;
      (&DAT_00c260c4)[uVar29 * 0x604] = uVar26;
      *(int *)(&DAT_00c260c8 + iVar23) =
           (int)(iVar14 * (iVar27 + uVar22 % ((((uVar21 / 5) * (uVar21 / 5) + uVar21) - iVar27) + 1)
                          )) / 100;
      if (puVar24 == (uint *)0x50) {
        puVar24 = (uint *)FUN_000a5c30();
        return puVar24;
      }
      return (uint *)0xa;
    }
    if ((((uint *)0x12 < puVar15) || ((0x44008U >> ((uint)puVar15 & 0x1f) & 1) == 0)) ||
       ((((uint *)0x15 < puVar24 || ((0x200208U >> ((uint)puVar24 & 0x1f) & 1) == 0)) &&
        ((((uint *)0x6 < puVar24 + -0x58 || ((0x49U >> ((uint)(puVar24 + -0x58) & 0x1f) & 1) == 0))
         && (2 < (int)puVar24 - 0x1b6U)))))) {
      iVar14 = FUN_000ca050();
      if (iVar14 == 0) {
        return (uint *)0x0;
      }
      uVar18 = param_1[0x1c];
      if ((uint *)(&DAT_00bef884)[uVar18 * 0xa6] != (uint *)param_1[0x1f]) {
        return (uint *)(&DAT_00bef884)[uVar18 * 0xa6];
      }
      bVar30 = puVar24 < (uint *)0x16;
      bVar31 = (0x200208U >> ((uint)puVar24 & 0x1f) & 1) != 0;
      bVar11 = bVar31 && bVar30;
      fStack_c4 = DAT_0074a8c4;
      fVar33 = DAT_0074a8c4;
      if (!bVar31 || !bVar30) {
        fVar33 = DAT_0074a2f8;
      }
      if (puVar24 != (uint *)0x11) {
        fStack_c4 = fVar33;
      }
      puVar15 = (uint *)FUN_00137820(((float)param_1[0x29] - (float)(&DAT_00bef7d8)[uVar18 * 0xa6])
                                     * ((float)param_1[0x29] - (float)(&DAT_00bef7d8)[uVar18 * 0xa6]
                                       ) + ((float)param_1[0x2a] -
                                           (float)(&DAT_00bef7dc)[uVar18 * 0xa6]) *
                                           ((float)param_1[0x2a] -
                                           (float)(&DAT_00bef7dc)[uVar18 * 0xa6]));
      if (fStack_c4 < (float)extraout_ST0_02) {
        return puVar15;
      }
      puVar28 = &DAT_00bef7dc + uVar18 * 0xa6;
      uVar6 = *puVar28;
      uVar26 = (&DAT_00bef7d8)[uVar18 * 0xa6];
      uVar29 = param_1[0x29];
      uVar21 = param_1[0x2a];
      iVar14 = FUN_00095200(uVar29,uVar21,uVar26,uVar6);
      if (iVar14 == 0) {
        return (uint *)0x0;
      }
      if ((DAT_00c2c8bc != (code *)0x0) &&
         (iVar14 = (*DAT_00c2c8bc)(DAT_00c2c8c0,uVar29,uVar21,uVar26,uVar6), iVar14 == 0)) {
        return (uint *)0x0;
      }
      if (bVar31 && bVar30) {
        if (param_1[0xf] == param_1[0x21]) {
          puVar15 = (uint *)FUN_00113920();
          if ((uint *)param_1[6] < puVar15) {
            return puVar15;
          }
          iVar14 = FUN_00095650((int)param_1[6] - (int)puVar15);
          if (iVar14 == 0) {
            return (uint *)0x0;
          }
        }
        uVar29 = (uint)*(byte *)((int)param_1 + 0x53);
        if (DAT_00be3098 < (float)param_1[0x16]) {
          uVar29 = uVar29 + *(byte *)((int)param_1 + 0x56);
        }
        iVar14 = (uVar29 / 7) * (uVar29 / 7) + uVar29;
        DAT_00c25dc8 = DAT_00c25dc8 * 0x19660d + 0x3c6ef35f;
        uVar29 = (DAT_00c25dc8 >> 0x10 ^ DAT_00c25dc8) %
                 ((((uVar29 / 5) * (uVar29 / 5) + uVar29) - iVar14) + 1);
      }
      else {
        uStack_c0 = (uint)(byte)param_1[0x15];
        if (DAT_00be3098 < (float)param_1[0x16]) {
          uStack_c0 = uStack_c0 + *(byte *)((int)param_1 + 0x56);
        }
        uVar29 = param_1[4];
        iStack_bc = 0;
        if (*param_1 == 8) {
          iStack_bc = FUN_000941f0();
        }
        DAT_00c25dc8 = DAT_00c25dc8 * 0x19660d + 0x3c6ef35f;
        uVar22 = DAT_00c25dc8 >> 0x10 ^ DAT_00c25dc8;
        iVar14 = FUN_000f3500();
        uVar21 = ((uVar29 + uStack_c0 + iStack_bc) - iVar14) + 0x50;
        uVar29 = 100;
        if ((int)uVar21 < 100) {
          uVar29 = uVar21;
        }
        uVar21 = 5;
        if (5 < (int)uVar29) {
          uVar21 = uVar29;
        }
        if (uVar21 <= uVar22 % 100) {
          FUN_00094440((&DAT_00bef7d8)[uVar18 * 0xa6],*puVar28);
          goto LAB_0011348e;
        }
        iVar14 = FUN_00114870(DAT_00be3098);
        if (puVar24 == (uint *)0x11) {
          if (param_1[0x21] != 0) {
            uVar21 = (param_1[0x21] * 10 + 0x5a) * iVar14;
            uVar29 = uVar21 >> 0x1f;
            iVar14 = (int)uVar21 / 100 + ((int)uVar21 >> 0x1f);
LAB_001133bb:
            iVar14 = iVar14 + uVar29;
          }
        }
        else if (puVar24 == (uint *)0xd) {
          uVar29 = param_1[0x21] * 0xf;
          goto LAB_001133bb;
        }
        uVar29 = 0;
        if (*param_1 == 6) {
          iVar27 = FUN_000941f0();
          uVar29 = iVar27 * 3;
        }
      }
      FUN_00114540(param_1[0x1f],uVar29 + iVar14,bVar11);
      if ((puVar24 == (uint *)0xd) && (0 < (int)(&DAT_00bef88c)[uVar18 * 0xa6])) {
        FUN_000a9510(param_1[0x21] * 4 + 10,(float)param_1[0x21] * DAT_0074a238 + DAT_0074a344);
      }
      if (bVar11) {
        FUN_00114370((&DAT_00bef7d8)[uVar18 * 0xa6],*puVar28);
      }
LAB_0011348e:
      puVar15 = (uint *)param_1[0xf];
      if (puVar15 < (uint *)0x2) {
        return puVar15;
      }
      if ((int)(&DAT_00bef88c)[uVar18 * 0xa6] < 1) {
        return puVar15;
      }
      if ((&DAT_00bef884)[uVar18 * 0xa6] != param_1[0x1f]) {
        return puVar15;
      }
      param_1[0xf] = (int)puVar15 - 1;
      param_1[0x20] = (uint)puVar24;
      if (bVar11) {
        fVar33 = DAT_0074a4ac;
      }
      else {
        fVar33 = DAT_0074a2c0;
      }
      param_1[0x32] = (uint)(fVar33 + DAT_00be3098);
      return param_1;
    }
    iVar14 = FUN_000ca050();
    if (iVar14 == 0) {
      return (uint *)0x0;
    }
    uVar18 = param_1[0x1c];
    if ((uint *)(&DAT_00bef884)[uVar18 * 0xa6] != (uint *)param_1[0x1f]) {
      return (uint *)(&DAT_00bef884)[uVar18 * 0xa6];
    }
    iVar14 = -0x22470;
    do {
      if (puVar24 == (uint *)(uint)*(ushort *)(iVar14 + 0x3a63d0)) {
        iVar14 = FUN_00132bc0((int)*(short *)(iVar14 + 0x3a63ec + param_1[0x21] * 2));
        fVar33 = (float)iVar14 * DAT_0074a2f4;
        break;
      }
      iVar14 = iVar14 + 0x1b0;
      fVar33 = DAT_0074a8c4;
    } while (iVar14 != 0);
    puVar15 = (uint *)FUN_00137820(((float)param_1[0x29] - (float)(&DAT_00bef7d8)[uVar18 * 0xa6]) *
                                   ((float)param_1[0x29] - (float)(&DAT_00bef7d8)[uVar18 * 0xa6]) +
                                   ((float)param_1[0x2a] - (float)(&DAT_00bef7dc)[uVar18 * 0xa6]) *
                                   ((float)param_1[0x2a] - (float)(&DAT_00bef7dc)[uVar18 * 0xa6]));
    if (fVar33 < (float)extraout_ST0_04) {
      return puVar15;
    }
    pfVar20 = (float *)(&DAT_00bef7dc + uVar18 * 0xa6);
    fVar33 = *pfVar20;
    uVar6 = (&DAT_00bef7d8)[uVar18 * 0xa6];
    uVar29 = param_1[0x29];
    uVar21 = param_1[0x2a];
    iVar14 = FUN_00095200(uVar29,uVar21,uVar6,fVar33);
    if (iVar14 == 0) {
      return (uint *)0x0;
    }
    if ((DAT_00c2c8bc != (code *)0x0) &&
       (iVar14 = (*DAT_00c2c8bc)(DAT_00c2c8c0,uVar29,uVar21,uVar6,fVar33), iVar14 == 0)) {
      return (uint *)0x0;
    }
    uVar29 = param_1[0x10];
    if (uVar29 == 0) {
      puVar15 = (uint *)FUN_00114d40(param_1[0x21]);
      if ((puVar24 == (uint *)0x1b8) && ((float)param_1[0x27] <= DAT_00be3098)) {
        return puVar15;
      }
      if ((uint *)param_1[6] < puVar15) {
        return puVar15;
      }
      iVar14 = FUN_00095650((int)param_1[6] - (int)puVar15);
      if (iVar14 == 0) {
        return (uint *)0x0;
      }
      param_1[0x10] = 1;
      fVar33 = 0.0;
      if (puVar24 != (uint *)0x1b8) {
        if ((((uint)puVar24 & 0xfffffffe) != 0x1b6) || (param_1[0x21] < 7)) goto LAB_00112eba;
        iVar14 = -0x22470;
        do {
          if (*(short *)(iVar14 + 0x3a63d0) == 0x1b8) {
            fVar33 = (float)*(uint *)(iVar14 + 0x3a64f0 + param_1[0x21] * 4) * DAT_0074a494;
            goto LAB_001135d4;
          }
          iVar14 = iVar14 + 0x1b0;
        } while (iVar14 != 0);
        fVar33 = 0.0;
LAB_001135d4:
        fVar33 = DAT_00be3098 + fVar33;
      }
      param_1[0x27] = (uint)fVar33;
    }
LAB_00112eba:
    uVar21 = (uint)*(byte *)((int)param_1 + 0x53);
    if (DAT_00be3098 < (float)param_1[0x16]) {
      uVar21 = uVar21 + *(byte *)((int)param_1 + 0x56);
    }
    iVar14 = (uVar21 / 7) * (uVar21 / 7) + uVar21;
    DAT_00c25dc8 = DAT_00c25dc8 * 0x19660d + 0x3c6ef35f;
    if (puVar24 == (uint *)0x160) {
      iVar27 = 0x5a;
    }
    else if (puVar24 == (uint *)0x1b8) {
      iVar27 = param_1[4] + 0x28;
    }
    else if (puVar24 == (uint *)0x1b7) {
      iVar27 = 1;
      if (*(int *)(&DAT_0042c2ec + (&DAT_00bef888)[uVar18 * 0xa6] * 0xc) != 2) {
        iVar27 = param_1[0x21] * 5 + 100;
      }
    }
    else {
      iVar27 = 100;
      if (puVar24 == (uint *)0x1b6) {
        iVar27 = 1;
        if (*(int *)(&DAT_0042c2ec + (&DAT_00bef888)[uVar18 * 0xa6] * 0xc) == 0) {
          iVar27 = param_1[0x21] * 10 + 100;
        }
      }
    }
    iVar14 = (int)(iVar27 * ((DAT_00c25dc8 >> 0x10 ^ DAT_00c25dc8) %
                             ((((uVar21 / 5) * (uVar21 / 5) + uVar21) - iVar14) + 1) + iVar14)) /
             100;
    iVar27 = 1;
    if (1 < iVar14) {
      iVar27 = iVar14;
    }
    FUN_00114540(param_1[0x1f],iVar27,1);
    puVar15 = DAT_00bec5ac;
    fVar33 = DAT_00be3098;
    if (uVar29 == 0) {
      FUN_00114370((&DAT_00bef7d8)[uVar18 * 0xa6],*pfVar20);
    }
    else {
      uVar29 = DAT_00e381bc & 7;
      DAT_00e381bc = DAT_00e381bc + 1;
      (&DAT_00d42974)[uVar29 * 5] = puVar24;
      (&DAT_00d42978)[uVar29 * 5] = puVar15;
      *(undefined8 *)(&DAT_00d4297c + uVar29 * 5) = *(undefined8 *)(&DAT_00bef7d8 + uVar18 * 0xa6);
      (&DAT_00d42984)[uVar29 * 5] = fVar33;
    }
    if ((puVar24 == (uint *)0x1b6) && (0 < (int)(&DAT_00bef88c)[uVar18 * 0xa6])) {
      FUN_000a3fc0((float)(&DAT_00bef7d8)[uVar18 * 0xa6] - (float)param_1[0x29],
                   *pfVar20 - (float)param_1[0x2a],0x41800000);
    }
    else if ((puVar24 == (uint *)0x1b7) &&
            ((0 < (int)(&DAT_00bef88c)[uVar18 * 0xa6] &&
             (*(int *)(&DAT_0042c2ec + (&DAT_00bef888)[uVar18 * 0xa6] * 0xc) == 1)))) {
      iVar14 = -0x22470;
      do {
        if (*(short *)(iVar14 + 0x3a63d0) == 0x1b7) {
          fVar33 = (float)*(uint *)(iVar14 + 0x3a64f0 + param_1[0x21] * 4) * DAT_0074a494;
          goto LAB_00113512;
        }
        iVar14 = iVar14 + 0x1b0;
      } while (iVar14 != 0);
      fVar33 = 0.0;
LAB_00113512:
      FUN_000a9340(param_1[0x21] * 10 + 0x1e,fVar33);
    }
    puVar15 = (uint *)param_1[0xf];
    if (puVar15 < (uint *)0x2) {
      return puVar15;
    }
    if ((int)(&DAT_00bef88c)[uVar18 * 0xa6] < 1) {
      return puVar15;
    }
    if ((&DAT_00bef884)[uVar18 * 0xa6] != param_1[0x1f]) {
      return puVar15;
    }
    param_1[0xf] = (int)puVar15 - 1;
    param_1[0x20] = (uint)puVar24;
    fVar33 = DAT_00be3098 + DAT_0074a4ac;
LAB_00112a74:
    param_1[0x32] = (uint)fVar33;
    puVar24 = (uint *)FUN_00136bf0(param_1[0x30],fVar33 + DAT_0074a28c);
    param_1[0x30] = (uint)(float)extraout_ST0_03;
  }
  return puVar24;
}

