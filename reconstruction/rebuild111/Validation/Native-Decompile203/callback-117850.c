
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00117850(float *param_1,float param_2,float param_3,float param_4,float param_5)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  ushort *puVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  float10 fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  
  if (((_DAT_00d34050 == 0) || (_DAT_00d3404c == 0)) ||
     (((uVar2 = func_0x00132b30(param_4), (uVar2 & 0x100) == 0 &&
       ((((uVar2 = func_0x00132b30(param_5), 0.0 <= param_5 && (0.0 <= param_4)) &&
         ((uVar2 & 0x100) == 0)) &&
        ((uVar2 = (uint)(param_4 * _DAT_0074a508),
         uVar2 = (int)(param_4 * _DAT_0074a508 - _DAT_0074a300) & (int)uVar2 >> 0x1f | uVar2,
         uVar2 < _DAT_00d34040 &&
         (uVar8 = (uint)(_DAT_0074a508 * param_5),
         uVar8 = (int)(_DAT_0074a508 * param_5 - _DAT_0074a300) & (int)uVar8 >> 0x1f | uVar8,
         uVar8 < _DAT_00d34044)))))) &&
      (_DAT_00d3404c == *(byte *)(uVar2 + _DAT_00d34040 * uVar8 + _DAT_00d34050))))) {
    iVar6 = (int)(param_4 * _DAT_0074a3d4);
    iVar3 = (int)(_DAT_0074a3d4 * param_5);
    if (iVar6 < 1) {
      iVar6 = 0;
    }
    iVar9 = 0;
    if (0 < iVar3) {
      iVar9 = iVar3;
    }
    iVar3 = _DAT_00d48034 + -1;
    if (iVar6 < _DAT_00d48034) {
      iVar3 = iVar6;
    }
    iVar6 = _DAT_00d48038 + -1;
    if (iVar9 < _DAT_00d48038) {
      iVar6 = iVar9;
    }
    fVar13 = param_4 * _DAT_0074a3d4 - (float)iVar3;
    fVar11 = _DAT_0074a3d4 * param_5 - (float)iVar6;
    iVar3 = iVar6 * _DAT_00d48034 + iVar3;
    fVar12 = *(float *)(_DAT_00d48044 + iVar3 * 0x10);
    if (fVar13 <= fVar11) {
      fVar14 = *(float *)(_DAT_00d48044 + 8 + iVar3 * 0x10);
      fVar15 = *(float *)(_DAT_00d48044 + 0xc + iVar3 * 0x10) - fVar14;
      fVar14 = fVar14 - fVar12;
    }
    else {
      fVar15 = *(float *)(_DAT_00d48044 + 4 + iVar3 * 0x10);
      fVar14 = *(float *)(_DAT_00d48044 + 0xc + iVar3 * 0x10) - fVar15;
      fVar15 = fVar15 - fVar12;
    }
    fVar10 = (float10)func_0x00115530(_DAT_00d2fbac,param_4,param_5,
                                      fVar14 * fVar11 + fVar15 * fVar13 + fVar12);
    fVar12 = (float)fVar10;
    fVar11 = *param_1 * param_4 + param_1[1] * param_5 + param_1[3];
    if (((_DAT_0074a6cc <= fVar11) && (fVar11 <= _DAT_0074a6d0)) &&
       ((fVar13 = param_1[6] * fVar12 + param_1[4] * param_4 + param_1[5] * param_5 + param_1[7],
        _DAT_0074a6cc <= fVar13 && (fVar13 <= _DAT_0074a6d4)))) {
      uVar8 = 0;
      uVar2 = 0x1c89;
      do {
        while (uVar7 = uVar2 + uVar8 >> 1, *(uint *)(uVar7 * 0x14 + 0x35d3d4) < 0x60e) {
          uVar8 = uVar7 + 1;
          if (uVar2 <= uVar8) goto LAB_00117b02;
        }
        uVar2 = uVar7;
      } while (uVar8 < uVar7);
LAB_00117b02:
      if ((uVar8 < 0x1c89) && (*(int *)(uVar8 * 0x14 + 0x35d3d4) == 0x60e)) {
        uVar1 = *(ushort *)(uVar8 * 2 + 0x3a6608);
        _DAT_00d476a0 = _DAT_00d476a0 + 1;
        if (_DAT_00d476a0 == 0) {
          _DAT_00d476a0 = 1;
          func_0x00137420(0xd476a4,0,0x218,fVar13,fVar12,fVar11);
        }
        iVar3 = *(int *)((uint)uVar1 * 4 + 0x3561b0);
        if (iVar3 < 0x4000) {
          if (iVar3 < 0) {
            return;
          }
          puVar4 = (ushort *)(iVar3 * 8 + 0x2d7918);
        }
        else {
          puVar4 = (ushort *)func_0x00097800();
          if (puVar4 == (ushort *)0x0) {
            return;
          }
        }
        fVar15 = fVar12 * param_1[10] + param_4 * param_1[8] + param_5 * param_1[9] + param_1[0xb] +
                 _DAT_0074a554;
        param_2 = param_2 * _DAT_0074a238;
        fVar11 = fVar11 + _DAT_0074a6d8 * param_2;
        fVar12 = fVar13 - param_2;
        fVar13 = (fVar12 - fVar13) * param_3 + fVar15;
        func_0x00097c60(0x800,0x800,0x1122a,1,fVar13,fVar15,fVar11,param_2,fVar12);
        uVar5 = func_0x0012f420();
        uVar5 = func_0x0013c860(uVar5,0x30c,1);
        uVar5 = func_0x0013c860(uVar5,0x35c,0);
        func_0x0012f430(uVar5);
        func_0x001175f0(fVar11,fVar12,param_2,param_2,fVar13,fVar15,(float)*puVar4,(float)puVar4[1],
                        (float)puVar4[2],(float)puVar4[3]);
      }
    }
  }
  return;
}

