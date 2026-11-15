
uint __fastcall FUN_00113c70(int *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  float10 fVar11;
  uint uStack_34;
  float fStack_30;
  
  uVar9 = DAT_00bda138;
  cVar3 = (&DAT_00d424db)[*param_1];
  if ((((DAT_00bec5ac == DAT_00e2398c) && (DAT_00be3098 < DAT_00e23990)) &&
      ((0x14f < DAT_00bda138 ||
       (((param_1[0x23] != DAT_00bda138 + 1 ||
         (param_1[0x24] != (&DAT_00bef884)[DAT_00bda138 * 0xa6])) ||
        ((float)param_1[0x38] <= DAT_00be3098)))))) && (iVar4 = FUN_000ca050(), iVar4 != 0)) {
    if (*param_1 == 4) {
      uVar10 = (&DAT_00bef82c)[uVar9 * 0xa6];
      iVar4 = 0;
      if (uVar10 == 0) {
        uVar10 = (uint)(byte)(&DAT_004296e0)[(&DAT_00bef888)[uVar9 * 0xa6] * 2];
        iVar4 = (byte)(&DAT_004296e1)[(&DAT_00bef888)[uVar9 * 0xa6] * 2] - 1;
      }
      uVar8 = 1;
      if ((float)(&DAT_00bef844)[uVar9 * 0xa6] <= 0.0) {
        uVar8 = uVar10;
      }
      if (0.0 < (float)(&DAT_00bef844)[uVar9 * 0xa6]) {
        iVar4 = 0;
      }
      if (0.0 < (float)(&DAT_00bef854)[uVar9 * 0xa6]) {
        iVar4 = 0;
        uVar8 = 2;
      }
      if ((*(short *)(&DAT_00429c0c + uVar8 * 0x14 + iVar4 * 200) < 1) ||
         (((&DAT_002597a0)[(&DAT_00bef888)[uVar9 * 0xa6] * 0x44] & 0x10) != 0)) goto LAB_00113e61;
    }
    if ((&DAT_00bef884)[DAT_00bda138 * 0xa6] == DAT_00e23988) {
      uVar1 = (&DAT_00bef7dc)[DAT_00bda138 * 0xa6];
      uVar2 = (&DAT_00bef7d8)[DAT_00bda138 * 0xa6];
      iVar4 = param_1[0x29];
      iVar6 = param_1[0x2a];
      iVar5 = FUN_00095200(iVar4,iVar6,uVar2,uVar1);
      if ((iVar5 != 0) &&
         ((DAT_00c2c8bc == (code *)0x0 ||
          (iVar4 = (*DAT_00c2c8bc)(DAT_00c2c8c0,iVar4,iVar6,uVar2,uVar1), iVar4 != 0)))) {
        return DAT_00bda138;
      }
    }
  }
LAB_00113e61:
  uVar9 = DAT_00be30e0;
  if (cVar3 == '\x02') {
    return 0xffffffff;
  }
  if (((cVar3 == '\0') &&
      ((((0x14f < DAT_00be30e0 || (param_1[0x23] != DAT_00be30e0 + 1)) ||
        (param_1[0x24] != (&DAT_00bef884)[DAT_00be30e0 * 0xa6])) ||
       ((float)param_1[0x38] <= DAT_00be3098)))) && (iVar4 = FUN_000ca050(), iVar4 != 0)) {
    if (*param_1 == 4) {
      uVar10 = (&DAT_00bef82c)[uVar9 * 0xa6];
      iVar4 = 0;
      if (uVar10 == 0) {
        uVar10 = (uint)(byte)(&DAT_004296e0)[(&DAT_00bef888)[uVar9 * 0xa6] * 2];
        iVar4 = (byte)(&DAT_004296e1)[(&DAT_00bef888)[uVar9 * 0xa6] * 2] - 1;
      }
      uVar8 = 1;
      if ((float)(&DAT_00bef844)[uVar9 * 0xa6] <= 0.0) {
        uVar8 = uVar10;
      }
      if (0.0 < (float)(&DAT_00bef844)[uVar9 * 0xa6]) {
        iVar4 = 0;
      }
      if (0.0 < (float)(&DAT_00bef854)[uVar9 * 0xa6]) {
        iVar4 = 0;
        uVar8 = 2;
      }
      if ((*(short *)(&DAT_00429c0c + uVar8 * 0x14 + iVar4 * 200) < 1) ||
         (((&DAT_002597a0)[(&DAT_00bef888)[uVar9 * 0xa6] * 0x44] & 0x10) != 0)) goto LAB_00114019;
    }
    uVar1 = (&DAT_00bef7dc)[DAT_00be30e0 * 0xa6];
    uVar2 = (&DAT_00bef7d8)[DAT_00be30e0 * 0xa6];
    iVar4 = param_1[0x29];
    iVar6 = param_1[0x2a];
    iVar5 = FUN_00095200(iVar4,iVar6,uVar2,uVar1);
    if ((iVar5 != 0) &&
       ((DAT_00c2c8bc == (code *)0x0 ||
        (iVar4 = (*DAT_00c2c8bc)(DAT_00c2c8c0,iVar4,iVar6,uVar2,uVar1), iVar4 != 0)))) {
      return DAT_00be30e0;
    }
  }
LAB_00114019:
  uStack_34 = 0xffffffff;
  fStack_30 = DAT_0074a470;
  iVar4 = -0x36780;
  uVar9 = 0;
  do {
    if ((uVar9 + 1 == param_1[0x23]) && (param_1[0x24] == *(int *)((int)&DAT_00c26004 + iVar4))) {
      if ((float)param_1[0x38] <= DAT_00be3098) goto LAB_00114080;
    }
    else {
LAB_00114080:
      iVar6 = FUN_000ca050();
      if (iVar6 != 0) {
        if (*param_1 == 4) {
          uVar10 = *(uint *)(iVar4 + 0xc25fac);
          iVar6 = 0;
          if (uVar10 == 0) {
            uVar10 = (uint)(byte)(&DAT_004296e0)[*(int *)(iVar4 + 0xc26008) * 2];
            iVar6 = (byte)(&DAT_004296e1)[*(int *)(iVar4 + 0xc26008) * 2] - 1;
          }
          if (0.0 < *(float *)(iVar4 + 0xc25fc4)) {
            uVar10 = 1;
          }
          if (0.0 < *(float *)(iVar4 + 0xc25fc4)) {
            iVar6 = 0;
          }
          if (0.0 < *(float *)(iVar4 + 0xc25fd4)) {
            uVar10 = 2;
            iVar6 = 0;
          }
          if (0 < *(short *)(&DAT_00429c0c + uVar10 * 0x14 + iVar6 * 200)) {
            if (((&DAT_002597a0)[*(int *)(iVar4 + 0xc26008) * 0x44] & 0x10) == 0) goto LAB_00114120;
          }
        }
        else {
LAB_00114120:
          if (*(int *)(iVar4 + 0xc26010) != 0) {
            fVar11 = (float10)FUN_00137820(((float)param_1[0x29] - *(float *)(&DAT_00c25f58 + iVar4)
                                           ) * ((float)param_1[0x29] -
                                               *(float *)(&DAT_00c25f58 + iVar4)) +
                                           ((float)param_1[0x2a] - *(float *)(&DAT_00c25f5c + iVar4)
                                           ) * ((float)param_1[0x2a] -
                                               *(float *)(&DAT_00c25f5c + iVar4)));
            if ((float)fVar11 < fStack_30) {
              uVar1 = *(undefined4 *)(&DAT_00c25f5c + iVar4);
              uVar2 = *(undefined4 *)(&DAT_00c25f58 + iVar4);
              iVar6 = param_1[0x29];
              iVar5 = param_1[0x2a];
              iVar7 = FUN_00095200(iVar6,iVar5,uVar2,uVar1);
              if (iVar7 != 0) {
                if (DAT_00c2c8bc != (code *)0x0) {
                  iVar6 = (*DAT_00c2c8bc)(DAT_00c2c8c0,iVar6,iVar5,uVar2,uVar1);
                  if (iVar6 == 0) goto LAB_00114040;
                }
                uStack_34 = uVar9;
                fStack_30 = (float)fVar11;
              }
            }
          }
        }
      }
    }
LAB_00114040:
    iVar4 = iVar4 + 0x298;
    uVar9 = uVar9 + 1;
    if (iVar4 == 0) {
      return uStack_34;
    }
  } while( true );
}

