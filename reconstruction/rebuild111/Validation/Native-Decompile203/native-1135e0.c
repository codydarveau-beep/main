
float __fastcall FUN_001135e0(int *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  float fVar5;
  float *pfVar6;
  float10 fVar7;
  undefined8 uVar8;
  float fVar9;
  int iVar10;
  float fVar11;
  
  uVar4 = 0x4b;
  if ((&DAT_00d424ee)[*param_1] == '\x02') {
    uVar4 = 0x5a;
  }
  uVar3 = 0x32;
  if ((&DAT_00d424ee)[*param_1] != '\x01') {
    uVar3 = uVar4;
  }
  fVar5 = -NAN;
  if ((((0 < (int)DAT_00be30b0) && (0 < DAT_00be30b4)) &&
      (uVar4 = FUN_0013d068((ulonglong)DAT_00be30b0 * 100,DAT_00be30b4,0), uVar4 < uVar3)) &&
     (fVar7 = (float10)FUN_00137820(((float)param_1[0x29] - DAT_00be3080) *
                                    ((float)param_1[0x29] - DAT_00be3080) +
                                    ((float)param_1[0x2a] - DAT_00be3084) *
                                    ((float)param_1[0x2a] - DAT_00be3084)),
     (float)fVar7 <= DAT_0074a470)) {
    iVar2 = param_1[0x29];
    iVar10 = param_1[0x2a];
    fVar9 = DAT_00be3084;
    fVar11 = DAT_00be3080;
    iVar1 = FUN_00095200(iVar2,iVar10,DAT_00be3080,DAT_00be3084,DAT_00be3084,iVar10,DAT_00be3080,
                         iVar2);
    if ((iVar1 != 0) &&
       ((DAT_00c2c8bc == (code *)0x0 ||
        (iVar2 = (*DAT_00c2c8bc)(DAT_00c2c8c0,iVar2,iVar10,fVar11,fVar9), iVar2 != 0)))) {
      uVar3 = FUN_0013d068((longlong)(int)DAT_00be30b0 * 100,DAT_00be30b4,DAT_00be30b4 >> 0x1f);
      fVar5 = -NAN;
    }
  }
  if (DAT_00d2fb8c != 0) {
    uVar4 = 0;
    pfVar6 = (float *)&DAT_00d2f958;
    do {
      if (((pfVar6[-0x20] != 0.0) && (pfVar6[-0x25] != 0.0)) &&
         ((pfVar6[-0x29] == DAT_00bec5ac &&
          (((pfVar6[-0x23] != 0.0 &&
            (uVar8 = FUN_0013d068((ulonglong)(uint)pfVar6[-0x25] * 100,pfVar6[-0x23],0),
            (uint)((ulonglong)uVar8 >> 0x20) < (uint)((uint)uVar8 < uVar3))) &&
           (fVar7 = (float10)FUN_00137820(((float)param_1[0x29] - pfVar6[-1]) *
                                          ((float)param_1[0x29] - pfVar6[-1]) +
                                          ((float)param_1[0x2a] - *pfVar6) *
                                          ((float)param_1[0x2a] - *pfVar6)),
           (float)fVar7 <= DAT_0074a470)))))) {
        fVar9 = pfVar6[-1];
        fVar11 = *pfVar6;
        iVar2 = param_1[0x29];
        iVar10 = param_1[0x2a];
        iVar1 = FUN_00095200(iVar2,iVar10,fVar9,fVar11,fVar5,fVar11,iVar2,fVar9,iVar10);
        if ((iVar1 != 0) &&
           ((DAT_00c2c8bc == (code *)0x0 ||
            (iVar2 = (*DAT_00c2c8bc)(DAT_00c2c8c0,iVar2,iVar10,fVar9,fVar11), iVar2 != 0)))) {
          fVar5 = pfVar6[-0x2a];
          uVar3 = FUN_0013d068((ulonglong)(uint)pfVar6[-0x25] * 100,pfVar6[-0x23],0);
        }
      }
      uVar4 = uVar4 + 1;
      pfVar6 = pfVar6 + 0x3d;
    } while (uVar4 < DAT_00d2fb8c);
  }
  return fVar5;
}

