
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void companion_tick_slice203(void)

{
  byte *pbVar1;
  byte *pbVar2;
  float *pfVar3;
  float *pfVar4;
  int *piVar5;
  float *pfVar6;
  byte *pbVar7;
  float *pfVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  byte bVar11;
  ushort uVar12;
  short sVar13;
  int iVar14;
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  bool bVar17;
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  int iVar22;
  int iVar23;
  float *pfVar24;
  undefined4 uVar25;
  dword dVar26;
  dword dVar27;
  dword dVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  NativeFollower203 *pNVar32;
  uint uVar33;
  NativeFollower203 *pNVar34;
  uint *puVar35;
  short sVar36;
  short sVar37;
  uint uVar38;
  int iVar39;
  ushort *puVar40;
  uint uVar41;
  uint uVar42;
  bool bVar43;
  bool bVar44;
  bool bVar45;
  float10 fVar46;
  float10 fVar47;
  float fVar48;
  float fVar49;
  float fVar50;
  undefined1 auVar51 [16];
  float fVar52;
  float fVar53;
  undefined4 uVar54;
  undefined4 uVar55;
  float fVar56;
  longlong lVar57;
  float fStack00000008;
  float fStack0000000c;
  float fStack00000040;
  byte *pbStack00000070;
  float fStack00000090;
  float in_stack_000000b0;
  int iStack000000d0;
  NativeFollower203 *pNStack000000f0;
  uint uStack00000100;
  NativeFollower203 *pNStack00000120;
  uint uStack00000158;
  uint uStack0000015c;
  uint uStack00000160;
  undefined1 in_stack_00000260 [16];
  uint in_stack_00001678;
  byte abStack_7ffffffe [2];
  float afStack_7ffffffc [536870911];
  
  if ((_DAT_00bda9c8 == 0) || (_DAT_00d2fb8c == 0)) {
    return;
  }
  fVar48 = in_stack_000000b0 * _DAT_0074a484;
  uStack00000158 = 0;
LAB_0003042e:
  uVar42 = uStack00000158;
  fStack00000040 = (float)(uStack00000158 * 0xf4);
  fStack00000090 = (float)NativeFollower203_ARRAY_00d2f8b0[uStack00000158].moving;
  NativeFollower203_ARRAY_00d2f8b0[uStack00000158].ownsMove = 0;
  NativeFollower203_ARRAY_00d2f8b0[uStack00000158].moving = 0;
  if (((NativeFollower203_ARRAY_00d2f8b0[uStack00000158].initialized == 0) ||
      (pbStack00000070 = (byte *)NativeFollower203_ARRAY_00d2f8b0[uStack00000158].hp,
      pbStack00000070 == (byte *)0x0)) ||
     (NativeFollower203_ARRAY_00d2f8b0[uStack00000158].map != _DAT_00bec5ac)) goto LAB_00035034;
  if (NativeFollower203_ARRAY_00d2f8b0[uStack00000158].buffUntil[2] <= _DAT_00be3098) {
    NativeFollower203_ARRAY_00d2f8b0[uStack00000158].shieldHits = 0;
    NativeFollower203_ARRAY_00d2f8b0[uStack00000158].shieldHP = 0;
  }
  pNStack000000f0 = NativeFollower203_ARRAY_00d2f8b0 + uStack00000158;
  uVar41 = *(uint *)(NativeFollower203_ARRAY_00d2f8b0[uStack00000158].job * 1000 + 0x2b378c +
                    NativeFollower203_ARRAY_00d2f8b0[uStack00000158].level * 4);
  fStack0000000c = 0.0;
  fStack00000008 = 1.4013e-43;
  lVar57 = func_0x0013d068();
  lVar57 = lVar57 + (ulonglong)uVar41;
  if ((int)(uint)((uint)lVar57 < 20000000) <= (int)((ulonglong)lVar57 >> 0x20)) {
    lVar57 = 20000000;
  }
  iVar23 = (int)((ulonglong)lVar57 >> 0x20);
  uVar41 = (uint)lVar57;
  iVar22 = -iVar23;
  if ((SBORROW4(0,iVar23) != SBORROW4(iVar22,(uint)(1 < uVar41))) ==
      (int)(iVar22 - (uint)(1 < uVar41)) < 0) {
    uVar41 = 1;
  }
  if ((uVar41 < NativeFollower203_ARRAY_00d2f8b0[uVar42].sp) &&
     (iVar22 = func_0x00095650(), iVar22 == 0)) goto LAB_00035034;
  pbVar1 = NativeFollower203_ARRAY_00d2f8b0[0].stats + (int)fStack00000040 + -0x44;
  *(uint *)(NativeFollower203_ARRAY_00d2f8b0[0].stats + (int)fStack00000040 + -0x30) = uVar41;
  fVar46 = (float10)func_0x00137820();
  iVar22 = (int)fStack00000040;
  if (_DAT_0074a470 < (float)fVar46) {
    pbVar1[0] = 1;
    pbVar1[1] = 0;
    pbVar1[2] = 0;
    pbVar1[3] = 0;
    func_0x00111110();
    goto LAB_00035034;
  }
  pbStack00000070 = NativeFollower203_ARRAY_00d2f8b0[0].stats + (int)fStack00000040 + -0x3c;
  party_resolve_native203(pNStack000000f0);
  fVar52 = _DAT_00be3098;
  fVar50 = _DAT_0074a314;
  if ((*(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x80) <=
       _DAT_00be3098) &&
     (*(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x80) =
           _DAT_00be3098 + _DAT_0074a314,
     fVar50 <= fVar52 - *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                                  (int)fStack00000040 + 0x78))) {
    func_0x00095650();
  }
  iVar22 = (int)fStack00000040;
  if ((((*(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x28)
         != 0) ||
       (_DAT_00be3098 <
        *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x68))
       ) || (_DAT_00be3098 <
             *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                       (int)fStack00000040 + 0x74))) ||
     (_DAT_00be3098 -
      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x78) <
      _DAT_0074a490)) {
    pbVar1[0] = 1;
    pbVar1[1] = 0;
    pbVar1[2] = 0;
    pbVar1[3] = 0;
    goto LAB_00035034;
  }
  fVar50 = (float)pNStack000000f0->id;
  if (0x12 < (uint)fVar50) goto LAB_00035034;
  pbVar2 = NativeFollower203_ARRAY_00d2f8b0[0].stats + (int)fStack00000040 + -0x48;
  pfVar3 = (float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x50
                    );
  pfVar4 = (float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x4c
                    );
  fStack00000090 = fVar50;
  switch(fVar50) {
  case 0.0:
  case 2.8026e-45:
  case 8.40779e-45:
  case 1.12104e-44:
  case 1.68156e-44:
  case 1.82169e-44:
    if ((fVar50 == 2.8026e-45) && (cRam00d42503 == '\0')) break;
    if (fVar50 == 1.68156e-44) {
      dVar26 = party_skill_rank_native203(pNStack000000f0,0xf2);
      if ((((dVar26 != 0) && (*(char *)(pNStack000000f0->id + 0xd42501) != '\0')) &&
          (*(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                     (int)fStack00000040 + 0x7c) <= _DAT_00be3098)) && (uRam00bec504 != 0)) {
        iVar23 = (int)fStack00000040 + 0x7c;
        iVar31 = 0;
        iVar29 = 0;
        do {
          if (*(int *)(iVar31 + 0xbe5488) == 0x1f5) {
            iVar29 = iVar29 + *(int *)(iVar31 + 0xbe548c);
          }
          iVar31 = iVar31 + 0x24;
        } while ((uint)uRam00bec504 * 0x24 != iVar31);
        if ((iVar29 != 0) &&
           (dVar26 = party_heal_target_native203(pNStack000000f0), dVar26 != 0xfffffffe)) {
          pNStack00000120 = (NativeFollower203 *)0x0;
          if ((-1 < (int)dVar26) && (_DAT_00d2fb8c != 0)) {
            pNVar34 = NativeFollower203_ARRAY_00d2f8b0;
            uVar42 = _DAT_00d2fb8c;
            do {
              if (pNVar34->id == dVar26) {
                pNStack00000120 = pNVar34;
                break;
              }
              pNVar34 = pNVar34 + 1;
              uVar42 = uVar42 - 1;
            } while (uVar42 != 0);
          }
          pfVar24 = &pNStack00000120->x;
          if (pNStack00000120 == (NativeFollower203 *)0x0) {
            pfVar24 = (float *)&DAT_00be3080;
          }
          fVar50 = *pfVar24;
          pfVar24 = &pNStack00000120->y;
          if (pNStack00000120 == (NativeFollower203 *)0x0) {
            pfVar24 = (float *)&DAT_00be3084;
          }
          fVar52 = *pfVar24;
          fVar46 = (float10)func_0x00137820();
          if (fRam0074a47c < (float)fVar46) {
            pbVar1[0] = 1;
            pbVar1[1] = 0;
            pbVar1[2] = 0;
            pbVar1[3] = 0;
            fStack0000000c = 0.05;
            goto code_r0x000311ed;
          }
          fVar49 = *pfVar3;
          fStack00000008 = fVar50;
          fStack0000000c = fVar52;
          iVar31 = func_0x00095200();
          if (iVar31 != 0) {
            if (_DAT_00c2c8bc != (code *)0x0) {
              fStack00000008 = fVar49;
              fStack0000000c = fVar50;
              iVar31 = (*_DAT_00c2c8bc)();
              if (iVar31 == 0) goto code_r0x0003298c;
            }
            iVar31 = -0x22470;
            do {
              if (*(short *)(iVar31 + 0x3a63d0) == 0xf2) {
                uStack0000015c = (uint)*(ushort *)(iVar31 + 0x3a6544);
                if (*(uint *)(pbStack00000070 + 4) < uStack0000015c) goto code_r0x0003298c;
                goto code_r0x00031942;
              }
              iVar31 = iVar31 + 0x1b0;
            } while (iVar31 != 0);
            uStack0000015c = 0;
code_r0x00031942:
            dVar26 = party_skill_rank_native203(pNStack000000f0,0xee);
            if (pNStack00000120 == (NativeFollower203 *)0x0) {
              uVar42 = func_0x000957c0();
              uVar41 = _DAT_00be30b4 - _DAT_00be30b0;
            }
            else {
              uVar42 = (uint)pNStack00000120->stats[2];
              uVar41 = pNStack00000120->maxHP - pNStack00000120->hp;
            }
            uVar42 = ((uVar42 * 2 + 100) * ((dVar26 * 0x113 + 0x17a2) / 100)) / 100;
            if (uVar41 <= uVar42) {
              uVar42 = uVar41;
            }
            if (((uVar42 != 0) && (iVar31 = func_0x00092ae0(), -1 < iVar31)) &&
               (uVar41 = pNStack000000f0->id, uVar41 < 0x13)) {
              if ((in_stack_00001678 >> (uVar41 & 0x1f) & 1) == 0) {
                fStack0000000c = 0.0;
                in_stack_00000260._0_4_ = 2;
              }
              else {
                fStack0000000c = *(float *)((int)register0x00000010 + uVar41 * 0x20 + 0x168c);
                in_stack_00000260._0_4_ =
                     *(undefined4 *)((int)register0x00000010 + uVar41 * 0x20 + 0x1688);
              }
              fStack00000008 = in_stack_00000260._0_4_;
              iVar31 = func_0x00093300();
              if (iVar31 != 0) {
                if ((pNStack00000120 == (NativeFollower203 *)0x0) ||
                   (pNStack00000120 == pNStack000000f0)) {
code_r0x0003262e:
                  iVar31 = _DAT_00d424d4;
                  fStack00000008 = 8.91226e-43;
                  func_0x0013d320();
                  if (iVar31 != 0) {
                    iVar31 = -0x280;
                    do {
                      bVar11 = *(byte *)((int)register0x00000010 + iVar31 + 0x18f0);
                      *(undefined1 *)((int)register0x00000010 + iVar31 * 2 + 0x37a0) =
                           *(undefined1 *)((bVar11 >> 4) + 0x2bef28);
                      *(undefined1 *)((int)register0x00000010 + iVar31 * 2 + 0x37a1) =
                           *(undefined1 *)((bVar11 & 0xf) + 0x2bef28);
                      iVar31 = iVar31 + 1;
                    } while (iVar31 != 0);
                    fStack0000000c = 0.0;
                    fStack00000008 = 2.8026e-45;
                    iVar31 = func_0x00091ff0();
                    if (iVar31 != 0) {
                      func_0x000e5e10();
                      *(uint *)(pbStack00000070 + 4) =
                           *(int *)(pbStack00000070 + 4) - uStack0000015c;
                      if (pNStack00000120 == (NativeFollower203 *)0x0) {
                        _DAT_00be30b0 = _DAT_00be30b0 + uVar42;
                      }
                      else {
                        pNStack00000120->hp = pNStack00000120->hp + uVar42;
                      }
                      *(undefined4 *)
                       ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                       (int)fStack00000040 + 0x30) = 0xf2;
                      fVar49 = _DAT_00be3098;
                      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                                (int)fStack00000040 + 100) = _DAT_00be3098;
                      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x68)
                           = fVar49 + fRam0074a2f0;
                      fVar49 = fVar49 + _DAT_00749e28;
                      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar23) =
                           fVar49;
                      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                                (int)fStack00000040 + 0x6c) = fVar49;
                      pbVar1[0] = 1;
                      pbVar1[1] = 0;
                      pbVar1[2] = 0;
                      pbVar1[3] = 0;
                      pNStack000000f0 = (NativeFollower203 *)(fVar52 - *pfVar3);
                      pbStack00000070 = (byte *)(fVar50 - *pfVar4);
                      fVar46 = (float10)func_0x00137820();
                      fVar49 = (float)fVar46;
                      if (_DAT_0074a494 < fVar49) {
                        *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                                  (int)fStack00000040 + 0x54) = (float)pbStack00000070 / fVar49;
                        *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                                  (int)fStack00000040 + 0x58) = (float)pNStack000000f0 / fVar49;
                      }
                      fVar49 = _DAT_00be3098;
                      uVar41 = _DAT_00bef644 & 0xf;
                      _DAT_00bef644 = _DAT_00bef644 + 1;
                      *(float *)(uVar41 * 0x30 + 0xbef344) = fVar50;
                      *(float *)(uVar41 * 0x30 + 0xbef348) = fVar52;
                      *(float *)(uVar41 * 0x30 + 0xbef34c) = fVar49;
                      *(undefined4 *)(uVar41 * 0x30 + 0xbef350) = 0x3e4ccccd;
                      *(uint *)(uVar41 * 0x30 + 0xbef354) = uVar42;
                      *(undefined4 *)(uVar41 * 0x30 + 0xbef358) = 1;
                      *(undefined4 *)(uVar41 * 0x30 + 0xbef35c) = 0;
                      *(undefined4 *)(uVar41 * 0x30 + 0xbef368) = 0;
                      *(undefined4 *)(uVar41 * 0x30 + 0xbef36c) = 0;
                      *(undefined4 *)(uVar41 * 0x30 + 0xbef370) = 0;
                      *(undefined4 *)(uVar41 * 0x30 + 0xbef360) = 4;
                      *(undefined4 *)(uVar41 * 0x30 + 0xbef364) = 3;
                      func_0x00114370();
                      break;
                    }
                  }
                }
                else {
                  uVar41 = pNStack00000120->id;
                  if (uVar41 < 0x13) {
                    if ((in_stack_00001678 >> (uVar41 & 0x1f) & 1) == 0) {
                      fStack0000000c = 0.0;
                      in_stack_00000260._0_4_ = 2;
                    }
                    else {
                      fStack0000000c = *(float *)((int)register0x00000010 + uVar41 * 0x20 + 0x168c);
                      in_stack_00000260._0_4_ =
                           *(undefined4 *)((int)register0x00000010 + uVar41 * 0x20 + 0x1688);
                    }
                    fStack00000008 = in_stack_00000260._0_4_;
                    iVar31 = func_0x00093300();
                    if (iVar31 != 0) goto code_r0x0003262e;
                  }
                }
              }
            }
          }
        }
        goto code_r0x0003298c;
      }
    }
    else {
code_r0x0003298c:
      if (((fStack00000090 == 1.82169e-44) && (cRam00d4250e != '\0')) &&
         (*(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x7c
                    ) <= _DAT_00be3098)) {
        dVar26 = party_skill_rank_native203(pNStack000000f0,10);
        uVar42 = dVar26 + (dVar26 == 0);
        if (9 < uVar42) {
          uVar42 = 10;
        }
        if (dVar26 != 0) {
          uVar12 = *(ushort *)(uVar42 * 2 + 0x383162);
          dVar28 = party_heal_target_native203(pNStack000000f0);
          if ((dVar28 != 0xfffffffe) && ((uint)uVar12 <= *(uint *)(pbStack00000070 + 4))) {
            pNVar34 = (NativeFollower203 *)0x0;
            if ((-1 < (int)dVar28) && (_DAT_00d2fb8c != 0)) {
              pNVar32 = NativeFollower203_ARRAY_00d2f8b0;
              uVar42 = _DAT_00d2fb8c;
              do {
                if (pNVar32->id == dVar28) {
                  pNVar34 = pNVar32;
                  break;
                }
                pNVar32 = pNVar32 + 1;
                uVar42 = uVar42 - 1;
              } while (uVar42 != 0);
            }
            pfVar24 = &pNVar34->x;
            if (pNVar34 == (NativeFollower203 *)0x0) {
              pfVar24 = (float *)&DAT_00be3080;
            }
            fVar50 = *pfVar24;
            pfVar24 = &pNVar34->y;
            if (pNVar34 == (NativeFollower203 *)0x0) {
              pfVar24 = (float *)&DAT_00be3084;
            }
            fVar52 = *pfVar24;
            fVar46 = (float10)func_0x00137820();
            if ((float)fVar46 <= fRam0074a47c) {
              fVar49 = *pfVar3;
              fStack00000008 = fVar50;
              fStack0000000c = fVar52;
              iVar23 = func_0x00095200();
              if (iVar23 != 0) {
                if (_DAT_00c2c8bc != (code *)0x0) {
                  fStack00000008 = fVar49;
                  fStack0000000c = fVar50;
                  iVar23 = (*_DAT_00c2c8bc)();
                  if (iVar23 == 0) goto code_r0x000333c3;
                }
                iVar23 = func_0x00095650();
                if (iVar23 != 0) {
                  *(undefined4 *)
                   ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x28) = 10;
                  *(undefined4 *)
                   ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x30)
                       = 10;
                  *(dword *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                            (int)fStack00000040 + 0x2c) = dVar26;
                  *(dword *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                            (int)fStack00000040 + 0x1c) = dVar28;
                  if (pNVar34 == (NativeFollower203 *)0x0) {
                    dVar26 = 0;
                  }
                  else {
                    dVar26 = pNVar34->life;
                  }
                  *(dword *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                            (int)fStack00000040 + 0x24) = dVar26;
                  fVar50 = _DAT_00be3098;
                  *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                            (int)fStack00000040 + 0x70) = _DAT_00be3098;
                  *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                            (int)fStack00000040 + 100) = fVar50;
                  *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x68) =
                       fVar50 + fRam0074a2f0;
                  fVar50 = fVar50 + _DAT_00749e28;
                  *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                            (int)fStack00000040 + 0x6c) = fVar50;
                  *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                            (int)fStack00000040 + 0x7c) = fVar50;
                  pbVar1[0] = 1;
                  pbVar1[1] = 0;
                  pbVar1[2] = 0;
                  pbVar1[3] = 0;
                  goto code_r0x000334c1;
                }
              }
            }
          }
        }
      }
    }
code_r0x000333c3:
    if (iRam00bec5c4 == 0) {
      piVar5 = (int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                      (int)fStack00000040 + 0x14);
      iVar23 = func_0x000ca050();
      if (((iVar23 == 0) ||
          (iVar23 = *piVar5,
          *(int *)(iVar23 * 0x298 + 0xbef884) !=
          *(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x20))
          ) || (*(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                          (int)fStack00000040 + 0x84) <= _DAT_00be3098)) {
        iVar23 = party_choose_target_native203(pNStack000000f0);
        *piVar5 = iVar23;
        if (iVar23 < 0) {
          uVar25 = 0;
        }
        else {
          uVar25 = *(undefined4 *)(iVar23 * 0x298 + 0xbef884);
        }
        *(undefined4 *)
         ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x20) = uVar25;
        *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x84)
             = _DAT_00be3098 + fRam0074a30c;
      }
      if (-1 < iVar23) {
        bVar43 = fStack00000090 == 2.8026e-45;
        bVar44 = fStack00000090 == 1.12104e-44;
        iVar23 = iVar23 * 0x298;
        uVar9 = *(undefined8 *)(iVar23 + 0xbef7d8);
        uVar10 = *(undefined8 *)pfVar4;
        fVar52 = (float)((ulonglong)uVar9 >> 0x20) - (float)((ulonglong)uVar10 >> 0x20);
        in_stack_00000260 = ZEXT416((uint)fVar52) << 0x20;
        fVar46 = (float10)func_0x00137820();
        fVar50 = (float)fVar46;
        pNStack00000120 = (NativeFollower203 *)_DAT_0074a498;
        if (!bVar44 && !bVar43) {
          pNStack00000120 = (NativeFollower203 *)fRam0074a438;
        }
        pbVar1[0] = 1;
        pbVar1[1] = 0;
        pbVar1[2] = 0;
        pbVar1[3] = 0;
        fVar46 = (float10)func_0x00137820();
        fVar49 = (float)fVar46;
        if (_DAT_0074a494 < fVar49) {
          auVar18._4_4_ = fVar52;
          auVar18._0_4_ = (float)uVar9 - (float)uVar10;
          auVar18._8_8_ = 0;
          auVar15._4_4_ = fVar49;
          auVar15._0_4_ = fVar49;
          auVar15._8_8_ = 0;
          auVar51 = divps(auVar18,auVar15);
          *(longlong *)
           ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x54) =
               auVar51._0_8_;
        }
        if ((fStack00000090 == 2.8026e-45) && (fVar50 < fRam0074a3b8)) {
          if (fVar50 <= _DAT_00749e28) {
            iVar31 = *(int *)pbVar2;
          }
          else {
            fStack00000008 = *pfVar3 - (fVar52 / fVar50) * fVar48;
            iVar31 = func_0x00094d70();
            *(int *)pbVar2 = iVar31;
          }
          if (iVar31 != 0) {
code_r0x00033bfc:
            *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                      (int)fStack00000040 + 0x60) =
                 *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                           (int)fStack00000040 + 0x60) + in_stack_000000b0;
            break;
          }
        }
        pfVar24 = (float *)(iVar23 + 0xbef7d8);
        if ((float)pNStack00000120 < fVar50) {
code_r0x00033c79:
          fStack0000000c = in_stack_000000b0;
          fStack00000008 = (float)pNStack00000120;
          goto code_r0x00033c8a;
        }
        if (_DAT_00be3098 <
            *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                      (int)fStack00000040 + 0x6c)) break;
        fStack0000000c = *(float *)(iVar23 + 0xbef7dc);
        fVar49 = *pfVar24;
        fVar53 = *pfVar3;
        in_stack_00000260._4_4_ = fVar52;
        in_stack_00000260._0_4_ = fVar53;
        in_stack_00000260._8_8_ = 0;
        fStack00000008 = fVar49;
        iVar31 = func_0x00095200();
        if (iVar31 == 0) break;
        if (_DAT_00c2c8bc != (code *)0x0) {
          fStack00000008 = fVar53;
          fStack0000000c = fVar49;
          iVar31 = (*_DAT_00c2c8bc)();
          if (iVar31 == 0) break;
        }
        pfVar6 = (float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                          (int)fStack00000040 + 0x6c);
        if (fStack00000090 == 2.8026e-45) {
          if (((((pNStack000000f0->id == 2) && (cRam00d42503 != '\0')) && (cRam00d424f0 != '\x02'))
              && (((_DAT_00c260c4 == 0 && (_DAT_00c260c0 <= _DAT_00be3098)) ||
                  ((((_DAT_00c278d4 == 0 && (_DAT_00c278d0 <= _DAT_00be3098)) ||
                    ((_DAT_00c290e4 == 0 && (_DAT_00c290e0 <= _DAT_00be3098)))) &&
                   ((_DAT_00c260c4 == 0 || (iRam00c260dc != 3)))))))) &&
             (((_DAT_00c278d4 == 0 || (iRam00c278ec != 3)) &&
              ((_DAT_00c290e4 == 0 || (iRam00c290fc != 3)))))) {
            uVar42 = CONCAT31(0,cRam00d424f0 == '\x01');
            uVar41 = uVar42 ^ 3;
            in_stack_00000260._0_4_ = uVar42;
            in_stack_00000260._8_8_ = 0;
            dVar26 = party_skill_rank_native203(pNStack000000f0,0x50);
            iVar31 = 0;
            if (dVar26 == 0) {
code_r0x00033eba:
              dVar28 = 0;
            }
            else {
              dVar28 = 10;
              if (dVar26 < 10) {
                dVar28 = dVar26;
              }
              if (*(uint *)(pbStack00000070 + 4) < (uint)*(ushort *)(dVar28 * 2 + 0x3836da))
              goto code_r0x00033eba;
              fStack00000008 = 36.0;
              iVar29 = func_0x00114b60();
              dVar28 = 0;
              if ((int)uVar41 <= iVar29) {
                uVar42 = *(uint *)(iVar23 + 0xbef82c);
                iVar31 = 0;
                if (uVar42 == 0) {
                  uVar42 = (uint)*(byte *)(*(int *)(iVar23 + 0xbef888) * 2 + 0x4296e0);
                  iVar31 = *(byte *)(*(int *)(iVar23 + 0xbef888) * 2 + 0x4296e1) - 1;
                }
                if (0.0 < *(float *)(iVar23 + 0xbef844)) {
                  uVar42 = 1;
                }
                dVar28 = 0;
                if (0.0 < *(float *)(iVar23 + 0xbef844)) {
                  iVar31 = 0;
                }
                if (0.0 < *(float *)(iVar23 + 0xbef854)) {
                  uVar42 = 2;
                  iVar31 = 0;
                }
                iVar31 = iVar29 * (dVar26 * 0x28 + 100) *
                         (int)*(short *)(iVar31 * 200 + 0x429c02 + uVar42 * 0x14);
                if (iVar31 < 1) {
                  iVar31 = 0;
                }
                else {
                  dVar28 = 0x50;
                }
              }
            }
            dVar26 = party_skill_rank_native203(pNStack000000f0,0x4d);
            if (dVar26 == 0) {
code_r0x00034116:
              dVar27 = dVar28;
              if (dVar28 == 0) goto code_r0x00034311;
            }
            else {
              dVar27 = 10;
              if (dVar26 < 10) {
                dVar27 = dVar26;
              }
              if (*(uint *)(pbStack00000070 + 4) < (uint)*(ushort *)(dVar27 * 2 + 0x38369e))
              goto code_r0x00034116;
              fStack00000008 = 44.0;
              iVar29 = func_0x00114b60();
              if (iVar29 < (int)uVar41) goto code_r0x00034116;
              uVar42 = *(uint *)(iVar23 + 0xbef82c);
              iVar30 = 0;
              if (uVar42 == 0) {
                uVar42 = (uint)*(byte *)(*(int *)(iVar23 + 0xbef888) * 2 + 0x4296e0);
                iVar30 = *(byte *)(*(int *)(iVar23 + 0xbef888) * 2 + 0x4296e1) - 1;
              }
              if (0.0 < *(float *)(iVar23 + 0xbef844)) {
                uVar42 = 1;
                iVar30 = 0;
              }
              if (0.0 < *(float *)(iVar23 + 0xbef854)) {
                uVar42 = 2;
                iVar30 = 0;
              }
              dVar27 = 0x4d;
              if ((int)(iVar29 * (dVar26 * 0x14 + 0x50) *
                       (int)*(short *)(iVar30 * 200 + 0x429c08 + uVar42 * 0x14)) <= iVar31)
              goto code_r0x00034116;
            }
            fVar46 = (float10)func_0x00137820();
            pfVar8 = (float *)(dVar27 * 0x1c + 0x2d4874);
            if ((float)fVar46 < *pfVar8 || (float)fVar46 == *pfVar8) {
              fStack0000000c = *(float *)(iVar23 + 0xbef7dc);
              fVar49 = *pfVar24;
              fVar53 = *pfVar3;
              in_stack_00000260._0_4_ = fVar49;
              in_stack_00000260._8_8_ = 0;
              fStack00000008 = fVar49;
              iVar31 = func_0x00095200();
              if (iVar31 != 0) {
                if (_DAT_00c2c8bc != (code *)0x0) {
                  fStack00000008 = fVar53;
                  fStack0000000c = fVar49;
                  iVar31 = (*_DAT_00c2c8bc)();
                  if (iVar31 == 0) goto code_r0x00034311;
                }
                pNStack000000f0 =
                     (NativeFollower203 *)party_skill_rank_native203(pNStack000000f0,dVar27);
                iVar23 = -0x10098;
                do {
                  if (*(dword *)(iVar23 + 0x5d3960) == dVar27) {
                    pbStack00000070 =
                         (byte *)(float)*(uint *)(iVar23 + 0x5d3960 + (int)pNStack000000f0 * 4);
                    fVar46 = (float10)func_0x00136dc0();
                    pbStack00000070 =
                         (byte *)(((fRam0074a49c - (float)fVar46) * (float)pbStack00000070) /
                                 fRam0074a4a0);
                    goto code_r0x0003468a;
                  }
                  iVar23 = iVar23 + 0xa8;
                } while (iVar23 != 0);
                pbStack00000070 = (byte *)0x0;
code_r0x0003468a:
                iVar23 = (int)fStack00000040;
                *(undefined8 *)
                 ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x3c) =
                     *(undefined8 *)pfVar24;
                *(dword *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x28) =
                     dVar27;
                *(dword *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                          (int)fStack00000040 + 0x30) = dVar27;
                *(NativeFollower203 **)
                 ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x2c) =
                     pNStack000000f0;
                pbVar7 = NativeFollower203_ARRAY_00d2f8b0[0].stats + (int)fStack00000040 + -0x14;
                pbVar7[0] = 1;
                pbVar7[1] = 0;
                pbVar7[2] = 0;
                pbVar7[3] = 0;
                pbVar7 = NativeFollower203_ARRAY_00d2f8b0[0].stats + (int)fStack00000040 + -0x10;
                pbVar7[0] = 0;
                fVar50 = _DAT_00be3098;
                pbVar7[1] = 0;
                pbVar7[2] = 0;
                pbVar7[3] = 0;
                *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                          (int)fStack00000040 + 100) = _DAT_00be3098;
                fVar50 = fVar50 + (float)pbStack00000070;
                *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                          (int)fStack00000040 + 0x70) = fVar50;
                *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x74) =
                     fVar50;
                *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x68) =
                     fVar50 + fRam0074a360;
                fVar46 = (float10)func_0x00136bf0();
                *pfVar6 = (float)fVar46;
                *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar23 + 0x7c) =
                     (float)fVar46;
                pbVar2[0] = 0;
                pbVar2[1] = 0;
                pbVar2[2] = 0;
                pbVar2[3] = 0;
                pbVar1[0] = 1;
                pbVar1[1] = 0;
                pbVar1[2] = 0;
                pbVar1[3] = 0;
                if (_DAT_0074a9e0 < (float)pbStack00000070) {
                  fStack00000040 = _DAT_00c25eb4;
                  uVar42 = _DAT_00c25eb8 - (int)_DAT_00c25eb4;
                  if (uVar42 < 0x20) {
                    fVar50 = _DAT_00be3098 + _DAT_0074a9e0;
                    uVar41 = 0;
                    if (uVar42 != 0) {
                      uVar33 = _DAT_00c25eb8;
                      do {
                        uVar38 = uVar33 - 1 & 0x1f;
                        fVar52 = *(float *)(uVar38 * 4 + 0xc25ebc);
                        if (fVar52 <= fVar50) goto code_r0x000347d6;
                        iVar22 = (uVar33 & 0x1f) * 4;
                        *(undefined4 *)(iVar22 + 0xc25e34) = *(undefined4 *)(uVar38 * 4 + 0xc25e34);
                        *(float *)(iVar22 + 0xc25ebc) = fVar52;
                        uVar42 = uVar42 - 1;
                        uVar33 = uVar33 - 1;
                      } while (uVar42 != 0);
                    }
                    goto code_r0x000347d8;
                  }
                }
                break;
              }
            }
          }
code_r0x00034311:
          if (cRam00d42503 != '\0') {
            pNStack00000120 = (NativeFollower203 *)party_skill_rank_native203(pNStack000000f0,3);
            uVar42 = *(uint *)(iVar23 + 0xbef82c);
            iVar29 = 0;
            iVar31 = 0;
            if (uVar42 == 0) {
              uVar42 = (uint)*(byte *)(*(int *)(iVar23 + 0xbef888) * 2 + 0x4296e0);
              iVar31 = *(byte *)(*(int *)(iVar23 + 0xbef888) * 2 + 0x4296e1) - 1;
            }
            if (0.0 < *(float *)(iVar23 + 0xbef844)) {
              uVar42 = 1;
            }
            if (0.0 < *(float *)(iVar23 + 0xbef844)) {
              iVar31 = 0;
            }
            if (0.0 < *(float *)(iVar23 + 0xbef854)) {
              uVar42 = 2;
              iVar31 = 0;
            }
            sVar36 = *(short *)(iVar31 * 200 + 0x429c06 + uVar42 * 0x14);
            bVar45 = sVar36 < 0;
            auVar21[0xf] = 0;
            auVar21._0_15_ = in_stack_00000260._1_15_;
            in_stack_00000260 = auVar21 << 8;
            if (pNStack00000120 == (NativeFollower203 *)0x0 || bVar45) {
              sVar36 = -1;
            }
            dVar26 = party_skill_rank_native203(pNStack000000f0,9);
            uVar42 = *(uint *)(iVar23 + 0xbef82c);
            if (uVar42 == 0) {
              uVar42 = (uint)*(byte *)(*(int *)(iVar23 + 0xbef888) * 2 + 0x4296e0);
              iVar29 = *(byte *)(*(int *)(iVar23 + 0xbef888) * 2 + 0x4296e1) - 1;
            }
            fVar52 = *(float *)(iVar23 + 0xbef844);
            iVar31 = 0;
            if (0.0 < fVar52) {
              uVar42 = 1;
            }
            if (0.0 < fVar52) {
              iVar29 = 0;
            }
            if (0.0 < *(float *)(iVar23 + 0xbef854)) {
              uVar42 = 2;
              iVar29 = 0;
            }
            sVar13 = *(short *)(iVar29 * 200 + 0x429c02 + uVar42 * 0x14);
            bVar17 = sVar36 < sVar13 && dVar26 != 0;
            if (sVar36 < sVar13 && dVar26 != 0) {
              sVar36 = sVar13;
            }
            dVar28 = party_skill_rank_native203(pNStack000000f0,0x15);
            uVar42 = *(uint *)(iVar23 + 0xbef82c);
            if (uVar42 == 0) {
              uVar42 = (uint)*(byte *)(*(int *)(iVar23 + 0xbef888) * 2 + 0x4296e0);
              iVar31 = *(byte *)(*(int *)(iVar23 + 0xbef888) * 2 + 0x4296e1) - 1;
            }
            if (0.0 < *(float *)(iVar23 + 0xbef844)) {
              uVar42 = 1;
              iVar31 = 0;
            }
            if (0.0 < *(float *)(iVar23 + 0xbef854)) {
              uVar42 = 2;
              iVar31 = 0;
            }
            sVar13 = *(short *)(iVar31 * 200 + 0x429c08 + uVar42 * 0x14);
            sVar37 = sVar36;
            if (sVar36 < sVar13 && dVar28 != 0) {
              sVar37 = sVar13;
            }
            if (0 < sVar37) {
              if (pNStack00000120 == (NativeFollower203 *)0x0 || bVar45) {
                pNStack00000120 = (NativeFollower203 *)0x1;
              }
              if (bVar17) {
                pNStack00000120 = (NativeFollower203 *)dVar26;
              }
              uStack00000160 = 3;
              if (bVar17) {
                uStack00000160 = 9;
              }
              if (sVar36 < sVar13 && dVar28 != 0) {
                uStack00000160 = 0x15;
                pNStack00000120 = (NativeFollower203 *)dVar28;
              }
              uVar42 = (int)pNStack00000120 + (uint)(pNStack00000120 == (NativeFollower203 *)0x0);
              if (9 < uVar42) {
                uVar42 = 10;
              }
              if (*(uint *)(pbStack00000070 + 4) <
                  (uint)*(ushort *)(uStack00000160 * 0x14 + 0x38309a + uVar42 * 2)) break;
              goto code_r0x00034902;
            }
          }
          break;
        }
        if (fStack00000090 == 1.12104e-44) {
          dVar26 = 0;
          uVar42 = 0x11;
          if (((cRam00d42509 == '\0') || (cRam00d424f6 == '\x02')) ||
             (_DAT_00be3098 <
              *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                        (int)fStack00000040 + 0x7c))) goto code_r0x000348c0;
          pNStack00000120 = (NativeFollower203 *)party_skill_rank_native203(pNStack000000f0,0x11);
          uStack00000160 = 0x11;
          if (pNStack00000120 == (NativeFollower203 *)0x0) goto code_r0x000348c0;
code_r0x0003485c:
          uVar42 = 10;
          if (pNStack00000120 < 10) {
            uVar42 = (uint)pNStack00000120;
          }
          if (*(uint *)(pbStack00000070 + 4) <
              (uint)*(ushort *)(uStack00000160 * 0x14 + 0x38309a + uVar42 * 2)) {
            uStack00000160 = (uint)(fStack00000090 == 1.12104e-44) << 4 | 1;
            pNStack00000120 = (NativeFollower203 *)0x0;
          }
        }
        else {
          uVar42 = 1;
          if (fStack00000090 == 1.82169e-44) {
code_r0x000342b6:
            dVar26 = party_skill_rank_native203(pNStack000000f0,2);
            if (dVar26 == 0) {
code_r0x000348b7:
              dVar26 = 0;
            }
            else if ((*(char *)((int)fStack00000090 + 0xd42501) != '\0') &&
                    (*(char *)((int)fStack00000090 + 0xd424ee) != '\x02')) {
              uStack00000160 = 2;
              goto code_r0x00034846;
            }
          }
          else {
            if (fStack00000090 != 8.40779e-45) {
              if (fStack00000090 != 0.0) {
                dVar26 = 1;
                goto code_r0x000348c0;
              }
              goto code_r0x000342b6;
            }
            dVar26 = party_skill_rank_native203(pNStack000000f0,0xd);
            if (dVar26 == 0) goto code_r0x000348b7;
            if ((cRam00d42507 == '\0') || (cRam00d424f4 == '\x02')) goto code_r0x000348c0;
            uStack00000160 = 0xd;
code_r0x00034846:
            pNStack00000120 = (NativeFollower203 *)dVar26;
            if (*(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                          (int)fStack00000040 + 0x7c) <= _DAT_00be3098) goto code_r0x0003485c;
          }
code_r0x000348c0:
          pNStack00000120 = (NativeFollower203 *)dVar26;
          uStack00000160 = uVar42;
        }
        iVar31 = func_0x00095650();
        if (iVar31 == 0) break;
        uVar42 = 0;
        if ((uint)fStack00000090 < 0x13) {
code_r0x00034902:
          uVar42 = *(uint *)((int)fStack00000090 * 4 + 0x5e59a0);
        }
        uVar41 = 0x1c89;
        uVar33 = 0;
        do {
          uVar38 = uVar41 + uVar33 >> 1;
          if (*(uint *)(uVar38 * 0x14 + 0x35d3d4) < uVar42) {
            uVar33 = uVar38 + 1;
          }
          else {
            uVar41 = uVar38;
          }
        } while (uVar33 < uVar41);
        iVar31 = 0;
        if ((uVar33 < 0x1c89) && (*(uint *)(uVar33 * 0x14 + 0x35d3d4) == uVar42)) {
          iVar31 = *(int *)((uint)*(ushort *)(uVar33 * 2 + 0x3a6608) * 0x44 + 0x2d9464);
        }
        iVar29 = *(int *)(NativeFollower203_ARRAY_00d2f8b0[0].stats + iVar22 + -0x18);
        if (iVar29 < 0x15) {
          if (iVar29 < 0xc) {
            if (0xc < iVar31) {
              iVar31 = 0;
            }
            puVar40 = (ushort *)(iVar29 * 0x1a + 0x5d49d2 + iVar31 * 2);
          }
          else {
            puVar40 = (ushort *)(iVar29 * 0x22 + 0x5d4708 + iVar31 * 2);
          }
        }
        else {
          puVar40 = (ushort *)(iVar29 * 0x2e + 0x5d405c + iVar31 * 2);
        }
        uVar42 = (uint)NativeFollower203_ARRAY_00d2f8b0[0].stats[(int)fStack00000040 + 1];
        if (_DAT_00be3098 <
            *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 4)
           ) {
          uVar42 = uVar42 + 2 +
                   (uint)NativeFollower203_ARRAY_00d2f8b0[0].buffRank[(int)fStack00000040 + 1];
        }
        uVar41 = (uint)NativeFollower203_ARRAY_00d2f8b0[0].stats[(int)fStack00000040 + 4];
        if (_DAT_00be3098 < *(float *)(pbStack00000070 + 0x44)) {
          uVar41 = uVar41 + NativeFollower203_ARRAY_00d2f8b0[0].buffRank[(int)fStack00000040];
        }
        iVar31 = (uint)*puVar40 - ((uVar42 * 4 + uVar41) * (uint)*puVar40) / 1000;
        if (iVar31 < 0x1f) {
          iVar31 = 0x1e;
        }
        pNStack000000f0 = (NativeFollower203 *)((float)iVar31 * fRam0074a4a4);
        fVar46 = (float10)func_0x00136dc0();
        pbVar2[0] = 0;
        pbVar2[1] = 0;
        pbVar2[2] = 0;
        pbVar2[3] = 0;
        *(uint *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x28) =
             uStack00000160;
        *(uint *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x30) =
             uStack00000160;
        *(NativeFollower203 **)
         ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x2c) =
             pNStack00000120;
        dVar26 = (pNStack00000120 != (NativeFollower203 *)0x0 && uStack00000160 == 0x11) + 1;
        if (fStack00000090 == 2.8026e-45) {
          dVar26 = (dword)pNStack00000120;
        }
        *(dword *)(NativeFollower203_ARRAY_00d2f8b0[0].stats + (int)fStack00000040 + -0x14) = dVar26
        ;
        *(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x18) =
             *piVar5;
        *(undefined4 *)
         ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x24) =
             *(undefined4 *)(iVar23 + 0xbef884);
        fVar52 = _DAT_00be3098;
        *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 100) =
             _DAT_00be3098;
        *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x68) =
             (float)fVar46 + fVar52;
        *pfVar6 = (float)pNStack000000f0 + fVar52;
        pNStack000000f0 = (NativeFollower203 *)fVar52;
        fVar52 = (float)fVar46 * fRam0074a2f0 + fVar52;
        pfVar3 = (float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                          (int)fStack00000040 + 0x70);
        *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x70)
             = fVar52;
        if (fStack00000090 != 2.8026e-45) {
          if (fStack00000090 == 1.12104e-44) {
            fVar50 = fVar50 / fRam0074a4a8;
            fVar53 = fVar50 + fVar52;
            *pfVar3 = fVar53;
            dVar26 = _DAT_00bec5ac;
            uVar42 = uRam00e381c0 & 7;
            fVar49 = *pfVar4;
            uVar25 = *(undefined4 *)
                      ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x50);
            uVar54 = (undefined4)*(undefined8 *)pfVar24;
            uVar55 = (undefined4)((ulonglong)*(undefined8 *)pfVar24 >> 0x20);
            *(dword *)(uVar42 * 0x1c + 0xd42894) = _DAT_00bec5ac;
            iVar23 = uVar42 * 0x1c;
            *(float *)(iVar23 + 0xd42898) = fVar49;
            *(undefined4 *)(iVar23 + 0xd4289c) = uVar25;
            *(undefined4 *)(iVar23 + 0xd428a0) = uVar54;
            *(undefined4 *)(iVar23 + 0xd428a4) = uVar55;
            *(float *)(uVar42 * 0x1c + 0xd428a8) = fVar52;
            *(float *)(uVar42 * 0x1c + 0xd428ac) = fVar53;
            uVar42 = uRam00e381c0 + 1;
            if (pNStack00000120 != (NativeFollower203 *)0x0) {
              uRam00e381c0 = uRam00e381c0 + 2;
              uVar42 = uVar42 & 7;
              fVar52 = fVar52 + _DAT_0074a2c0;
              *(dword *)(uVar42 * 0x1c + 0xd42894) = dVar26;
              iVar23 = uVar42 * 0x1c;
              *(float *)(iVar23 + 0xd42898) = fVar49;
              *(undefined4 *)(iVar23 + 0xd4289c) = uVar25;
              *(undefined4 *)(iVar23 + 0xd428a0) = uVar54;
              *(undefined4 *)(iVar23 + 0xd428a4) = uVar55;
              *(float *)(uVar42 * 0x1c + 0xd428a8) = fVar52;
              *(float *)(uVar42 * 0x1c + 0xd428ac) = fVar50 + fVar52;
              fVar46 = (float10)func_0x00136bf0();
              *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x68) =
                   (float)fVar46;
              fVar46 = (float10)func_0x00136bf0();
              *pfVar6 = (float)fVar46;
              fStack0000000c = *pfVar4;
              fStack00000008 = 1.26117e-44;
              goto code_r0x00034f54;
            }
            uRam00e381c0 = uVar42;
            fVar46 = (float10)func_0x00136bf0();
            *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x68) =
                 (float)fVar46;
            fVar46 = (float10)func_0x00136bf0();
            *pfVar6 = (float)fVar46;
          }
          else if (uStack00000160 == 2) {
            fStack0000000c = *pfVar4;
            fStack00000008 = (float)((int)fStack00000090 + 1);
code_r0x00034f54:
            func_0x000676a0();
          }
        }
        else {
          puVar35 = (uint *)0x5c38c8;
          iVar23 = 0x187;
          do {
            uVar42 = *puVar35;
            if (uVar42 == uStack00000160) {
              pNStack000000f0 = (NativeFollower203 *)(float)puVar35[(int)pNStack00000120];
              fVar46 = (float10)func_0x00136dc0();
              pbStack00000070 =
                   (byte *)(((fRam0074a49c - (float)fVar46) * (float)pNStack000000f0) / fRam0074a4a0
                           );
              pNStack000000f0 = (NativeFollower203 *)_DAT_00be3098;
              goto code_r0x00034d97;
            }
            puVar35 = puVar35 + 0x2a;
            iVar23 = iVar23 + -1;
          } while (iVar23 != 0);
          pbStack00000070 = (byte *)0x0;
          puVar35 = (uint *)0x0;
code_r0x00034d97:
          uStack00000100 = (int)pNStack00000120 - 1;
          fVar46 = (float10)func_0x00136bf0();
          fVar50 = (float)pNStack000000f0 + (float)fVar46;
          *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x74) = fVar50;
          *pfVar3 = fVar50;
          fVar52 = (float)uStack00000100 * _DAT_0074a4ac + fVar50 + fRam0074a360;
          *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x68) = fVar52;
          fVar50 = fRam0074a044;
          if (uVar42 == uStack00000160) {
            fVar50 = (float)puVar35[(int)pNStack00000120 + 10] * _DAT_0074a494;
          }
          *pfVar6 = fVar52 + fVar50;
          fVar50 = _DAT_00c25eb4;
          if ((_DAT_0074a9e0 < (float)pbStack00000070) &&
             (uVar42 = _DAT_00c25eb8 - (int)_DAT_00c25eb4, uVar42 < 0x20)) {
            fVar52 = _DAT_00be3098 + _DAT_0074a9e0;
            uVar41 = 0;
            if (uVar42 != 0) {
              uVar33 = _DAT_00c25eb8;
              do {
                uVar38 = uVar33 - 1 & 0x1f;
                fVar49 = *(float *)(uVar38 * 4 + 0xc25ebc);
                if (fVar49 <= fVar52) {
                  uVar41 = uVar42;
                  break;
                }
                iVar22 = (uVar33 & 0x1f) * 4;
                *(undefined4 *)(iVar22 + 0xc25e34) = *(undefined4 *)(uVar38 * 4 + 0xc25e34);
                *(float *)(iVar22 + 0xc25ebc) = fVar49;
                uVar42 = uVar42 - 1;
                uVar33 = uVar33 - 1;
              } while (uVar42 != 0);
            }
            uVar42 = uVar41 + (int)fVar50 & 0x1f;
            *(undefined4 *)(uVar42 * 4 + 0xc25e34) = 0x3a;
            *(float *)(uVar42 * 4 + 0xc25ebc) = fVar52;
            _DAT_00c25eb8 = _DAT_00c25eb8 + 1;
          }
        }
        if ((uStack00000160 == 1) ||
           ((bVar44 || bVar43) && pNStack00000120 == (NativeFollower203 *)0x0)) break;
code_r0x00035004:
        *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x7c)
             = _DAT_00be3098 +
               *(float *)((uint)(*(char *)((int)fStack00000090 + 0xd424ee) == '\x01') * 4 + 0x74a4b0
                         );
      }
    }
    break;
  case 1.4013e-45:
  case 5.60519e-45:
    dVar26 = party_skill_rank_native203(pNStack000000f0,(uint)(fVar50 == 5.60519e-45) * 8 + 2);
    if ((int)dVar26 < 2) {
      dVar26 = 1;
    }
    if (((fVar50 != 5.60519e-45) || (cRam00d42505 == '\0')) ||
       (_DAT_00be3098 <
        *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x7c))
       ) {
code_r0x000311fa:
      if (iRam00bec5c4 == 0) {
        if ((fStack00000090 == 5.60519e-45) &&
           ((cRam00d42505 == '\0' || (*(uint *)(pbStack00000070 + 4) < 0xf)))) {
          *(undefined4 *)
           ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x14) =
               0xffffffff;
        }
        else {
          piVar5 = (int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                          (int)fStack00000040 + 0x14);
          iVar23 = func_0x000ca050();
          if (((iVar23 == 0) ||
              (iVar23 = *piVar5,
              *(int *)(iVar23 * 0x298 + 0xbef884) !=
              *(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                      (int)fStack00000040 + 0x20))) ||
             (*(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                        (int)fStack00000040 + 0x84) <= _DAT_00be3098)) {
            iVar23 = party_choose_target_native203(pNStack000000f0);
            *piVar5 = iVar23;
            if (iVar23 < 0) {
              uVar25 = 0;
            }
            else {
              uVar25 = *(undefined4 *)(iVar23 * 0x298 + 0xbef884);
            }
            *(undefined4 *)
             ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x20) =
                 uVar25;
            *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                      (int)fStack00000040 + 0x84) = _DAT_00be3098 + fRam0074a30c;
          }
          if (-1 < iVar23) {
            pbVar1[0] = 1;
            pbVar1[1] = 0;
            pbVar1[2] = 0;
            pbVar1[3] = 0;
            iVar23 = iVar23 * 0x298;
            uVar9 = *(undefined8 *)(iVar23 + 0xbef7d8);
            uVar10 = *(undefined8 *)pfVar4;
            fVar46 = (float10)func_0x00137820();
            iVar31 = 0x40;
            if (fStack00000090 != 5.60519e-45) {
              iVar31 = 0x10;
            }
            fVar47 = (float10)func_0x00137820();
            fVar50 = (float)fVar47;
            if (_DAT_0074a494 < fVar50) {
              auVar19._4_4_ = (float)((ulonglong)uVar9 >> 0x20) - (float)((ulonglong)uVar10 >> 0x20)
              ;
              auVar19._0_4_ = (float)uVar9 - (float)uVar10;
              auVar19._8_8_ = 0;
              auVar16._4_4_ = fVar50;
              auVar16._0_4_ = fVar50;
              auVar16._8_8_ = 0;
              auVar51 = divps(auVar19,auVar16);
              *(longlong *)
               ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x54) =
                   auVar51._0_8_;
            }
            fStack00000008 = (float)iVar31;
            if (fStack00000008 < (float)fVar46) goto code_r0x00031fc6;
            pbVar2[0] = 0;
            pbVar2[1] = 0;
            pbVar2[2] = 0;
            pbVar2[3] = 0;
            if (*(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                          (int)fStack00000040 + 0x6c) <= _DAT_00be3098) {
              fStack0000000c = *(float *)(iVar23 + 0xbef7dc);
              fVar50 = *(float *)(iVar23 + 0xbef7d8);
              fVar52 = *pfVar3;
              fStack00000008 = fVar50;
              iVar31 = func_0x00095200();
              if (iVar31 != 0) {
                if (_DAT_00c2c8bc != (code *)0x0) {
                  fStack00000008 = fVar52;
                  fStack0000000c = fVar50;
                  iVar31 = (*_DAT_00c2c8bc)();
                  if (iVar31 == 0) break;
                }
                if (((fStack00000090 == 1.4013e-45) && (cRam00d424ef != '\x02')) &&
                   (cRam00d42502 != '\0')) {
                  iVar31 = 1;
                  uVar42 = 0;
                  if (*(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                                (int)fStack00000040 + 0x7c) <= _DAT_00be3098) {
                    uVar42 = 10;
                    if (dVar26 < 10) {
                      uVar42 = dVar26;
                    }
                    uVar42 = (uint)*(ushort *)(uVar42 * 2 + 0x3830c2);
                    iVar31 = 2;
                  }
code_r0x00032751:
                  if ((*(byte *)(*(int *)(iVar23 + 0xbef888) * 0x44 + 0x2597a0) & 0x10) != 0) {
                    uVar42 = 0;
                    iVar31 = 1;
                  }
                }
                else if (fStack00000090 == 5.60519e-45) {
                  if (cRam00d42505 == '\0') break;
                  iVar31 = 0x33;
                  uVar42 = 0xf;
                  dVar26 = 1;
                }
                else {
                  uVar42 = 0;
                  iVar31 = 1;
                  if (fStack00000090 == 1.4013e-45) goto code_r0x00032751;
                }
                if (fStack00000090 == 1.4013e-45 && *(uint *)(pbStack00000070 + 4) < uVar42) {
                  uVar42 = 0;
                  iVar31 = 1;
                }
                if ((uVar42 <= *(uint *)(pbStack00000070 + 4)) &&
                   ((iVar31 == 0x33 || (iVar29 = func_0x00095650(), iVar29 != 0)))) {
                  pfVar3 = (float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                                    (int)fStack00000040 + 0x6c);
                  uVar42 = 0x1c89;
                  uVar41 = 0;
                  do {
                    uVar33 = uVar42 + uVar41 >> 1;
                    if (*(uint *)(uVar33 * 0x14 + 0x35d3d4) < 0x44d) {
                      uVar41 = uVar33 + 1;
                    }
                    else {
                      uVar42 = uVar33;
                    }
                  } while (uVar41 < uVar42);
                  iVar29 = 2;
                  if ((uVar41 < 0x1c89) && (*(int *)(uVar41 * 0x14 + 0x35d3d4) == 0x44d)) {
                    iVar29 = *(int *)((uint)*(ushort *)(uVar41 * 2 + 0x3a6608) * 0x44 + 0x2d9464);
                  }
                  iVar30 = iVar29 * 2 + 0x4e;
                  if (fStack00000090 != 5.60519e-45) {
                    iVar30 = iVar29 * 2 + 0x1a;
                  }
                  uVar42 = (uint)NativeFollower203_ARRAY_00d2f8b0[0].stats[(int)fStack00000040 + 1];
                  if (_DAT_00be3098 <
                      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                                (int)fStack00000040 + 4)) {
                    uVar42 = uVar42 + 2 +
                             (uint)NativeFollower203_ARRAY_00d2f8b0[0].buffRank
                                   [(int)fStack00000040 + 1];
                  }
                  uVar41 = (uint)NativeFollower203_ARRAY_00d2f8b0[0].stats[(int)fStack00000040 + 4];
                  if (_DAT_00be3098 < *(float *)(pbStack00000070 + 0x44)) {
                    uVar41 = uVar41 + NativeFollower203_ARRAY_00d2f8b0[0].buffRank
                                      [(int)fStack00000040];
                  }
                  iVar29 = (uint)*(ushort *)(iVar30 + 0x5d49d2) -
                           ((uVar42 * 4 + uVar41) * (uint)*(ushort *)(iVar30 + 0x5d49d2)) / 1000;
                  if (iVar29 < 0x1f) {
                    iVar29 = 0x1e;
                  }
                  fVar52 = (float)iVar29 * fRam0074a4a4;
                  fVar46 = (float10)func_0x00136dc0();
                  fVar50 = _DAT_00be3098;
                  *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                            (int)fStack00000040 + 100) = _DAT_00be3098;
                  *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x68) =
                       (float)fVar46 + fVar50;
                  *pfVar3 = fVar52 + fVar50;
                  *(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                          (int)fStack00000040 + 0x30) = iVar31;
                  *(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x28) =
                       iVar31;
                  *(dword *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                            (int)fStack00000040 + 0x2c) = dVar26;
                  *(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                          (int)fStack00000040 + 0x18) = *piVar5;
                  *(undefined4 *)
                   ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x24)
                       = *(undefined4 *)(iVar23 + 0xbef884);
                  if (iVar31 == 0x33) {
                    fVar46 = (float10)func_0x00136dc0();
                    pbStack00000070 =
                         (byte *)(((fRam0074a49c - (float)fVar46) * fRam0074a4b8) / fRam0074a4a0);
                    fStack00000090 = _DAT_00be3098;
                    fVar46 = (float10)func_0x00136bf0();
                    fVar52 = fStack00000090 + (float)fVar46;
                    *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x74) =
                         fVar52;
                    fVar50 = _DAT_00c25eb4;
                    if (_DAT_0074a9e0 < (float)pbStack00000070) {
                      fStack00000090 = _DAT_00c25eb4;
                      uVar42 = _DAT_00c25eb8 - (int)_DAT_00c25eb4;
                      if (uVar42 < 0x20) {
                        fVar49 = _DAT_00be3098 + _DAT_0074a9e0;
                        uVar41 = 0;
                        if (uVar42 != 0) {
                          uVar33 = _DAT_00c25eb8;
                          do {
                            uVar38 = uVar33 - 1 & 0x1f;
                            fVar53 = *(float *)(uVar38 * 4 + 0xc25ebc);
                            if (fVar53 <= fVar49) {
                              uVar41 = uVar42;
                              break;
                            }
                            iVar23 = (uVar33 & 0x1f) * 4;
                            *(undefined4 *)(iVar23 + 0xc25e34) =
                                 *(undefined4 *)(uVar38 * 4 + 0xc25e34);
                            *(float *)(iVar23 + 0xc25ebc) = fVar53;
                            uVar42 = uVar42 - 1;
                            uVar33 = uVar33 - 1;
                          } while (uVar42 != 0);
                        }
                        uVar42 = uVar41 + (int)fVar50 & 0x1f;
                        *(undefined4 *)(uVar42 * 4 + 0xc25e34) = 0x3a;
                        *(float *)(uVar42 * 4 + 0xc25ebc) = fVar49;
                        _DAT_00c25eb8 = _DAT_00c25eb8 + 1;
                      }
                    }
                    *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                              (int)fStack00000040 + 0x70) = fVar52;
                    *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x68) =
                         fVar52 + fRam0074a360;
                    fVar46 = (float10)func_0x00136bf0();
                    *pfVar3 = (float)fVar46;
                    if (((float)pbStack00000070 == _DAT_0074a9e0) &&
                       (!NAN((float)pbStack00000070) && !NAN(_DAT_0074a9e0))) goto code_r0x000334c1;
                  }
                  else {
                    *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                              (int)fStack00000040 + 0x70) = (float)fVar46 * fRam0074a2f0 + fVar50;
                    if (iVar31 == 2) {
                      fStack0000000c = *pfVar4;
                      fStack00000008 = (float)(pNStack000000f0->id + 1);
                      func_0x000676a0();
                      goto code_r0x00035004;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else {
      fVar50 = (float)party_heal_target_native203(pNStack000000f0);
      uVar42 = 10;
      if (dVar26 < 10) {
        uVar42 = dVar26;
      }
      if (fVar50 == -NAN) goto code_r0x000311fa;
      uVar41 = (uint)*(ushort *)(uVar42 * 2 + 0x383162);
      uVar42 = *(uint *)(pbStack00000070 + 4);
      if (uVar41 <= uVar42) {
        if ((-1 < (int)fVar50) && (_DAT_00d2fb8c != 0)) {
          pNVar34 = NativeFollower203_ARRAY_00d2f8b0;
          uVar42 = _DAT_00d2fb8c;
          do {
            if ((float)pNVar34->id == fVar50) break;
            pNVar34 = pNVar34 + 1;
            uVar42 = uVar42 - 1;
          } while (uVar42 != 0);
        }
        fVar46 = (float10)func_0x00137820();
        if ((float)fVar46 <= fRam0074a47c) {
          uVar42 = *(uint *)(pbStack00000070 + 4);
          goto code_r0x00030d51;
        }
        pbVar1[0] = 1;
        pbVar1[1] = 0;
        pbVar1[2] = 0;
        pbVar1[3] = 0;
        fStack0000000c = in_stack_000000b0;
code_r0x000311ed:
        fStack00000008 = 64.0;
        goto code_r0x00033c8a;
      }
code_r0x00030d51:
      if ((uVar42 < uVar41) || (iVar23 = func_0x00095650(), iVar23 == 0)) goto code_r0x000311fa;
      pbVar1[0] = 1;
      pbVar1[1] = 0;
      pbVar1[2] = 0;
      pbVar1[3] = 0;
      pbVar2[0] = 0;
      pbVar2[1] = 0;
      pbVar2[2] = 0;
      pbVar2[3] = 0;
      *(undefined4 *)
       ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x30) = 10;
      fVar52 = _DAT_00be3098;
      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 100) =
           _DAT_00be3098;
      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x68) =
           fVar52 + fRam0074a2f0;
      *(undefined4 *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x28) = 10;
      *(dword *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x2c) =
           dVar26;
      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x1c) =
           fVar50;
      if ((-1 < (int)fVar50) && (_DAT_00d2fb8c != 0)) {
        pfVar24 = &NativeFollower203_ARRAY_00d2f8b0[0].x;
        uVar42 = _DAT_00d2fb8c;
        do {
          if ((float)((NativeFollower203 *)(pfVar24 + -0x29))->id == fVar50) {
            *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                      (int)fStack00000040 + 0x24) = pfVar24[-0x20];
            pbStack00000070 = (byte *)(pfVar24[1] - *pfVar3);
            goto code_r0x00031262;
          }
          pfVar24 = pfVar24 + 0x3d;
          uVar42 = uVar42 - 1;
        } while (uVar42 != 0);
      }
      *(undefined4 *)
       ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x24) = 0;
      pbStack00000070 = (byte *)(_DAT_00be3084 - *pfVar3);
      pfVar24 = (float *)&DAT_00be3080;
code_r0x00031262:
      fStack00000090 = *pfVar24 - *pfVar4;
      fVar46 = (float10)func_0x00137820();
      fVar50 = (float)fVar46;
      if (_DAT_0074a494 < fVar50) {
        *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x54)
             = fStack00000090 / fVar50;
        *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x58)
             = (float)pbStack00000070 / fVar50;
      }
      *(undefined4 *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x74) = 0;
      fVar50 = _DAT_00be3098;
      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x70) =
           _DAT_00be3098;
      fVar50 = fVar50 + _DAT_00749e28;
      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x7c) =
           fVar50;
      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x6c) =
           fVar50;
code_r0x000334c1:
      party_resolve_native203(pNStack000000f0);
    }
    break;
  case 4.2039e-45:
  case 1.96182e-44:
  case 2.52234e-44:
    if (iRam00bec5c4 != 0) break;
    piVar5 = (int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x14
                    );
    iVar23 = func_0x000ca050();
    if (((iVar23 == 0) ||
        (iVar23 = *piVar5,
        *(int *)(iVar23 * 0x298 + 0xbef884) !=
        *(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x20)))
       || (*(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                     (int)fStack00000040 + 0x84) <= _DAT_00be3098)) {
      iVar23 = party_choose_target_native203(pNStack000000f0);
      *piVar5 = iVar23;
      if (iVar23 < 0) {
        uVar25 = 0;
      }
      else {
        uVar25 = *(undefined4 *)(iVar23 * 0x298 + 0xbef884);
      }
      *(undefined4 *)
       ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x20) = uVar25;
      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x84) =
           _DAT_00be3098 + fRam0074a30c;
    }
    if ((iVar23 < 0) || (*(char *)(pNStack000000f0->id + 0xd42501) == '\0')) break;
    if (pNStack000000f0->id == 0x12) {
      dVar26 = party_skill_rank_native203(pNStack000000f0,0x1b8);
      pNVar34 = pNStack000000f0;
      if ((_DAT_00be3098 <
           *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                     (int)fStack00000040 + 0x44)) && (dVar26 != 0)) {
        fStack00000090 = *(float *)(pbStack00000070 + 4);
        if (9 < dVar26) {
          dVar26 = 10;
        }
        iVar31 = -0x22470;
        do {
          if (*(short *)(iVar31 + 0x3a63d0) == 0x1b8) {
            uVar42 = (uint)*(ushort *)(iVar31 + 0x3a6542 + dVar26 * 2);
            goto code_r0x0003174f;
          }
          iVar31 = iVar31 + 0x1b0;
        } while (iVar31 != 0);
        uVar42 = 0;
code_r0x0003174f:
        uVar41 = *(uint *)(NativeFollower203_ARRAY_00d2f8b0[0].stats + iVar22 + -0x40);
        iVar31 = 7;
        if ((uVar41 < 0x5a) && (iVar31 = 5, uVar41 < 0x50)) {
          iVar31 = (uint)(0x45 < uVar41) * 3;
        }
        dVar26 = party_skill_rank_native203(pNStack000000f0,0x1b5);
        dVar28 = party_skill_rank_native203(pNVar34,0x117);
        pNStack00000120 = (NativeFollower203 *)0x1b8;
        if (((dVar28 * -4 + 100) * (uVar42 - (dVar26 * iVar31 * uVar42) / 100)) / 100 <=
            (uint)fStack00000090) goto code_r0x00031dc0;
      }
      fStack00000090 = *(float *)(*(int *)(iVar23 * 0x298 + 0xbef888) * 0xc + 0x42c2ec);
      pNStack00000120 = (NativeFollower203 *)(0x1b7 - (fStack00000090 == 0.0));
      dVar26 = party_skill_rank_native203(pNStack000000f0,(dword)pNStack00000120);
      pNVar34 = pNStack000000f0;
      if (dVar26 != 0) {
        uVar42 = *(uint *)(pbStack00000070 + 4);
        if (9 < dVar26) {
          dVar26 = 10;
        }
        iVar31 = -0x22470;
        do {
          if (pNStack00000120 == (NativeFollower203 *)(uint)*(ushort *)(iVar31 + 0x3a63d0)) {
            uVar41 = (uint)*(ushort *)(iVar31 + 0x3a6542 + dVar26 * 2);
            goto code_r0x00031a1b;
          }
          iVar31 = iVar31 + 0x1b0;
        } while (iVar31 != 0);
        uVar41 = 0;
code_r0x00031a1b:
        uVar33 = *(uint *)(NativeFollower203_ARRAY_00d2f8b0[0].stats + iVar22 + -0x40);
        iVar31 = 7;
        if ((uVar33 < 0x5a) && (iVar31 = 5, uVar33 < 0x50)) {
          iVar31 = (uint)(0x45 < uVar33) * 3;
        }
        dVar26 = party_skill_rank_native203(pNStack000000f0,0x1b5);
        dVar28 = party_skill_rank_native203(pNVar34,0x117);
        if (((dVar28 * -4 + 100) * (uVar41 - (dVar26 * iVar31 * uVar41) / 100)) / 100 <= uVar42)
        goto code_r0x00031dc0;
      }
      pNStack00000120 = (NativeFollower203 *)((fStack00000090 == 0.0) + 0x1b6);
      dVar26 = party_skill_rank_native203(pNStack000000f0,(dword)pNStack00000120);
      pNVar34 = pNStack000000f0;
      if (dVar26 != 0) {
        fStack00000090 = *(float *)(pbStack00000070 + 4);
        if (9 < dVar26) {
          dVar26 = 10;
        }
        iVar31 = -0x22470;
        do {
          if (pNStack00000120 == (NativeFollower203 *)(uint)*(ushort *)(iVar31 + 0x3a63d0)) {
            uVar42 = (uint)*(ushort *)(iVar31 + 0x3a6542 + dVar26 * 2);
            goto code_r0x00031d45;
          }
          iVar31 = iVar31 + 0x1b0;
        } while (iVar31 != 0);
        uVar42 = 0;
code_r0x00031d45:
        uVar41 = *(uint *)(NativeFollower203_ARRAY_00d2f8b0[0].stats + iVar22 + -0x40);
        iVar31 = 7;
        if ((uVar41 < 0x5a) && (iVar31 = 5, uVar41 < 0x50)) {
          iVar31 = (uint)(0x45 < uVar41) * 3;
        }
        dVar26 = party_skill_rank_native203(pNStack000000f0,0x1b5);
        dVar28 = party_skill_rank_native203(pNVar34,0x117);
        if (((dVar28 * -4 + 100) * (uVar42 - (dVar26 * iVar31 * uVar42) / 100)) / 100 <=
            (uint)fStack00000090) goto code_r0x00031dc0;
      }
      break;
    }
    iVar31 = iVar23 * 0x298;
    iVar29 = 0;
    auVar20._12_4_ = 0;
    auVar20._0_12_ = in_stack_00000260._4_12_;
    in_stack_00000260 = auVar20 << 0x20;
    pNStack00000120 = (NativeFollower203 *)0x0;
    do {
      if (pNStack000000f0->id == 0xe) {
        iVar30 = (int)register0x00000010 + 0x32a0;
      }
      else {
        in_stack_00001678 = 0x15;
        iVar30 = (int)register0x00000010 + 0x1670;
      }
      fStack00000090 = *(float *)(iVar30 + iVar29 * 4);
      dVar26 = party_skill_rank_native203(pNStack000000f0,(dword)fStack00000090);
      if (dVar26 != 0) {
        dVar28 = 10;
        if (dVar26 < 10) {
          dVar28 = dVar26;
        }
        if ((uint)fStack00000090 < 0x7f) {
          if (fStack00000090 != 0.0) {
            puVar40 = (ushort *)((int)fStack00000090 * 0x14 + 0x38309a + dVar28 * 2);
code_r0x0003144e:
            uVar42 = (uint)*puVar40;
            goto code_r0x00031451;
          }
          uVar42 = 0;
        }
        else {
          puVar40 = (ushort *)(dVar28 * 2 + 0x3840d2);
          iVar30 = -0x22470;
          do {
            if (fStack00000090 == (float)(uint)*(ushort *)(iVar30 + 0x3a63d0))
            goto code_r0x0003144e;
            puVar40 = puVar40 + 0xd8;
            iVar30 = iVar30 + 0x1b0;
          } while (iVar30 != 0);
          uVar42 = 0;
code_r0x00031451:
          if ((int)fStack00000090 - 0x1b6U < 3) {
            uVar41 = *(uint *)(NativeFollower203_ARRAY_00d2f8b0[0].stats + iVar22 + -0x40);
            iVar30 = 7;
            if ((uVar41 < 0x5a) && (iVar30 = 5, uVar41 < 0x50)) {
              iVar30 = (uint)(0x45 < uVar41) * 3;
            }
            dVar28 = party_skill_rank_native203(pNStack000000f0,0x1b5);
            uVar42 = uVar42 - (dVar28 * iVar30 * uVar42) / 100;
          }
        }
        dVar28 = party_skill_rank_native203(pNStack000000f0,0x117);
        uVar42 = ((dVar28 * -4 + 100) * uVar42) / 100;
        if (uVar42 <= *(uint *)(pbStack00000070 + 4)) {
          iVar30 = 3;
          if ((int)fStack00000090 < 0x160) {
            if (fStack00000090 != 4.2039e-45) {
              if (fStack00000090 == 1.26117e-44) goto code_r0x00031567;
              if (fStack00000090 == 2.94273e-44) goto code_r0x00031560;
code_r0x0003151b:
              iVar30 = 6;
              if ((int)fStack00000090 - 0x1b6U < 3) {
                iVar30 = 0;
              }
            }
          }
          else if (fStack00000090 != 4.93257e-43) {
            if (fStack00000090 == 4.97461e-43) {
code_r0x00031567:
              iVar30 = 1;
            }
            else {
              if (fStack00000090 != 5.01665e-43) goto code_r0x0003151b;
code_r0x00031560:
              iVar30 = 4;
            }
          }
          uVar41 = *(uint *)(iVar31 + 0xbef82c);
          iVar39 = 0;
          if (uVar41 == 0) {
            uVar41 = (uint)*(byte *)(*(int *)(iVar31 + 0xbef888) * 2 + 0x4296e0);
            iVar39 = *(byte *)(*(int *)(iVar31 + 0xbef888) * 2 + 0x4296e1) - 1;
          }
          if (0.0 < *(float *)(iVar31 + 0xbef844)) {
            uVar41 = 1;
          }
          if (0.0 < *(float *)(iVar31 + 0xbef844)) {
            iVar39 = 0;
          }
          if (0.0 < *(float *)(iVar31 + 0xbef854)) {
            uVar41 = 2;
            iVar39 = 0;
          }
          iVar30 = (int)*(short *)(iVar39 * 200 + uVar41 * 0x14 + 0x429c00 + iVar30 * 2);
          if (0 < iVar30) {
            iVar39 = -0x22470;
            do {
              if (fStack00000090 == (float)(uint)*(ushort *)(iVar39 + 0x3a63d0)) {
                dVar28 = (dword)*(short *)(iVar39 + 0x3a6414 + dVar26 * 2);
                goto code_r0x0003161b;
              }
              iVar39 = iVar39 + 0x1b0;
            } while (iVar39 != 0);
            dVar28 = dVar26;
code_r0x0003161b:
            if (fStack00000090 == 6.16571e-43) {
              dVar28 = dVar26;
            }
            dVar27 = -dVar28;
            if ((int)-dVar28 < 0) {
              dVar27 = dVar28;
            }
            if ((int)dVar27 < 2) {
              dVar27 = 1;
            }
            if (fStack00000090 == 4.93257e-43) {
              iVar39 = 0x5a;
            }
            else if (fStack00000090 == 6.16571e-43) {
              iVar39 = *(int *)(NativeFollower203_ARRAY_00d2f8b0[0].stats + iVar22 + -0x40) + 0x28;
            }
            else {
              iVar14 = *(int *)(*(int *)(iVar31 + 0xbef888) * 0xc + 0x42c2ec);
              if (fStack00000090 == 6.1517e-43) {
                iVar39 = dVar26 * 5 + 100;
                if (iVar14 == 2) {
                  iVar39 = 1;
                }
              }
              else {
                iVar39 = 100;
                if ((fStack00000090 == 6.13769e-43) && (iVar39 = dVar26 * 10 + 100, iVar14 != 0)) {
                  iVar39 = 1;
                }
              }
            }
            iVar39 = dVar27 * iVar30 * iVar39;
            if (*(char *)(pNStack000000f0->id + 0xd424ee) == '\x02') {
              iVar39 = iVar39 / (int)(uVar42 + (uVar42 == 0));
            }
            iVar30 = in_stack_00000260._0_4_;
            if (in_stack_00000260._0_4_ < iVar39) {
              iVar30 = iVar39;
              pNStack00000120 = (NativeFollower203 *)fStack00000090;
            }
            in_stack_00000260._0_4_ = iVar30;
          }
        }
      }
      iVar29 = iVar29 + 1;
    } while (iVar29 != 3);
    if (pNStack00000120 == (NativeFollower203 *)0x0) break;
code_r0x00031dc0:
    dVar26 = party_skill_rank_native203(pNStack000000f0,(dword)pNStack00000120);
    puVar40 = (ushort *)0x383f60;
    iVar31 = 0x145;
    do {
      uVar12 = *puVar40;
      if (pNStack00000120 == (NativeFollower203 *)(uint)uVar12) {
        iVar31 = func_0x00132bc0();
        fVar50 = (float)iVar31 * _DAT_0074a2f4;
        goto code_r0x00032264;
      }
      puVar40 = puVar40 + 0xd8;
      iVar31 = iVar31 + -1;
    } while (iVar31 != 0);
    puVar40 = (ushort *)0x0;
    fVar50 = _DAT_0074a498;
code_r0x00032264:
    iVar23 = iVar23 * 0x298;
    fVar52 = *(float *)(iVar23 + 0xbef7d8);
    fVar49 = *pfVar4;
    fVar56 = *(float *)(iVar23 + 0xbef7dc) - *pfVar3;
    fVar46 = (float10)func_0x00137820();
    fStack00000090 = (float)fVar46;
    pbVar1[0] = 1;
    pbVar1[1] = 0;
    pbVar1[2] = 0;
    pbVar1[3] = 0;
    fVar46 = (float10)func_0x00137820();
    fVar53 = (float)fVar46;
    if (_DAT_0074a494 < fVar53) {
      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x54) =
           (fVar52 - fVar49) / fVar53;
      *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x58) =
           fVar56 / fVar53;
    }
    if ((fStack00000090 < fRam0074a3b8) && (_DAT_00749e28 < fStack00000090)) {
      fStack00000008 = *pfVar3 - (fVar56 / fStack00000090) * fVar48;
      iVar31 = func_0x00094d70();
      *(int *)pbVar2 = iVar31;
      if (iVar31 == 0) goto code_r0x00032416;
      goto code_r0x00033bfc;
    }
code_r0x00032416:
    if (fVar50 < fStack00000090) {
      pNStack00000120 = (NativeFollower203 *)fVar50;
      goto code_r0x00033c79;
    }
    if ((_DAT_00be3098 <
         *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x6c)
        ) || (_DAT_00be3098 <
              *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                        (int)fStack00000040 + 0x7c))) break;
    fStack0000000c = *(float *)(iVar23 + 0xbef7dc);
    fStack00000008 = *(float *)(iVar23 + 0xbef7d8);
    fVar50 = *pfVar3;
    fStack00000090 = fStack00000008;
    pNStack000000f0 = (NativeFollower203 *)fStack0000000c;
    iVar31 = func_0x00095200();
    if (iVar31 == 0) break;
    if (_DAT_00c2c8bc != (code *)0x0) {
      fStack0000000c = fStack00000090;
      fStack00000008 = fVar50;
      iVar31 = (*_DAT_00c2c8bc)();
      if (iVar31 == 0) break;
    }
    fVar46 = (float10)func_0x00136dc0();
    iVar31 = (int)fStack00000040;
    if (pNStack00000120 == (NativeFollower203 *)(uint)uVar12) {
      puVar35 = (uint *)(puVar40 + dVar26 * 2 + 0x40);
code_r0x0003329f:
      fVar50 = (float)*puVar35 * _DAT_0074a494;
    }
    else {
      iVar29 = dVar26 * -4;
      iVar30 = -0x10098;
      do {
        if ((NativeFollower203 *)*(dword *)(iVar30 + 0x5d3960) == pNStack00000120) {
          puVar35 = (uint *)(0x5c38c8 - iVar29);
          goto code_r0x0003329f;
        }
        iVar29 = iVar29 + -0xa8;
        iVar30 = iVar30 + 0xa8;
      } while (iVar30 != 0);
      fVar50 = 0.0;
    }
    iVar29 = (int)fStack00000040 + 0x6c;
    pNStack000000f0 =
         (NativeFollower203 *)(((fRam0074a49c - (float)fVar46) / fRam0074a49c) * fVar50);
    pbVar2[0] = 0;
    pbVar2[1] = 0;
    pbVar2[2] = 0;
    pbVar2[3] = 0;
    *(NativeFollower203 **)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x28) =
         pNStack00000120;
    *(NativeFollower203 **)
     ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x30) =
         pNStack00000120;
    *(dword *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x2c) =
         dVar26;
    iVar30 = -0x22470;
    do {
      if (pNStack00000120 == (NativeFollower203 *)(uint)*(ushort *)(iVar30 + 0x3a63d0)) {
        dVar28 = (dword)*(short *)(iVar30 + 0x3a6414 + dVar26 * 2);
        goto code_r0x000334da;
      }
      iVar30 = iVar30 + 0x1b0;
    } while (iVar30 != 0);
    dVar28 = dVar26;
code_r0x000334da:
    if (pNStack00000120 == (NativeFollower203 *)0x1b8) {
      dVar28 = dVar26;
    }
    dVar26 = -dVar28;
    if ((int)-dVar28 < 0) {
      dVar26 = dVar28;
    }
    if ((int)dVar26 < 2) {
      dVar26 = 1;
    }
    *(dword *)(NativeFollower203_ARRAY_00d2f8b0[0].stats + (int)fStack00000040 + -0x14) = dVar26;
    pbVar1 = NativeFollower203_ARRAY_00d2f8b0[0].stats + (int)fStack00000040 + -0x10;
    pbVar1[0] = 0;
    pbVar1[1] = 0;
    pbVar1[2] = 0;
    pbVar1[3] = 0;
    *(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x18) =
         *piVar5;
    *(undefined4 *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x24)
         = *(undefined4 *)(iVar23 + 0xbef884);
    fVar50 = _DAT_00be3098;
    *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 100) =
         _DAT_00be3098;
    fVar50 = fVar50 + (float)pNStack000000f0;
    *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x74) = fVar50;
    *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x70) =
         fVar50;
    *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x68) =
         (float)(dVar26 - 1) * _DAT_0074a4ac + fVar50 + fRam0074a360;
    fVar46 = (float10)func_0x00136bf0();
    *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar29) = (float)fVar46;
    *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar31 + 0x7c) = (float)fVar46;
    if ((float)pNStack000000f0 <= _DAT_0074a9e0) break;
    fStack00000040 = _DAT_00c25eb4;
    uVar42 = _DAT_00c25eb8 - (int)_DAT_00c25eb4;
    if (0x1f < uVar42) break;
    fVar50 = _DAT_00be3098 + _DAT_0074a9e0;
    uVar41 = 0;
    if (uVar42 != 0) {
      uVar33 = _DAT_00c25eb8;
      do {
        uVar38 = uVar33 - 1 & 0x1f;
        fVar52 = *(float *)(uVar38 * 4 + 0xc25ebc);
        if (fVar52 <= fVar50) goto code_r0x000347d6;
        iVar22 = (uVar33 & 0x1f) * 4;
        *(undefined4 *)(iVar22 + 0xc25e34) = *(undefined4 *)(uVar38 * 4 + 0xc25e34);
        *(float *)(iVar22 + 0xc25ebc) = fVar52;
        uVar42 = uVar42 - 1;
        uVar33 = uVar33 - 1;
      } while (uVar42 != 0);
    }
    goto code_r0x000347d8;
  default:
    if (iRam00bec5c4 == 0) {
      piVar5 = (int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                      (int)fStack00000040 + 0x14);
      iVar23 = func_0x000ca050();
      if (((iVar23 == 0) ||
          (pNStack00000120 = (NativeFollower203 *)*piVar5,
          *(int *)((int)pNStack00000120 * 0x298 + 0xbef884) !=
          *(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x20))
          ) || (fVar50 = _DAT_00be3098,
               *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                         (int)fStack00000040 + 0x84) <= _DAT_00be3098)) {
        pNStack00000120 = (NativeFollower203 *)party_choose_target_native203(pNStack000000f0);
        *piVar5 = (int)pNStack00000120;
        if ((int)pNStack00000120 < 0) {
          uVar25 = 0;
        }
        else {
          uVar25 = *(undefined4 *)((int)pNStack00000120 * 0x298 + 0xbef884);
        }
        *(undefined4 *)
         ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x20) = uVar25;
        fVar50 = _DAT_00be3098;
        *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x84)
             = _DAT_00be3098 + fRam0074a30c;
      }
      if (-1 < (int)pNStack00000120) {
        dVar26 = pNStack000000f0->id;
        uVar42 = 0;
        if (((*(char *)(dVar26 + 0xd42501) == '\0') ||
            (fVar50 < *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                                (int)fStack00000040 + 0x7c))) ||
           (*(char *)(dVar26 + 0xd424ee) == '\x02')) goto code_r0x00031b05;
        if (dVar26 - 0x10 < 2) {
          if ((((*(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                           (int)fStack00000040 + 0x48) <= fVar50) ||
               ((NativeFollower203 *)
                *(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                        (int)fStack00000040 + 0x18) != pNStack00000120)) ||
              (*(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                       (int)fStack00000040 + 0x24) !=
               *(int *)((int)pNStack00000120 * 0x298 + 0xbef884))) ||
             ((dVar26 = party_skill_rank_native203
                                  (pNStack000000f0,
                                   *(dword *)(NativeFollower203_ARRAY_00d2f8b0[0].stats +
                                             (int)fStack00000040 + -0xc)), dVar26 == 0 ||
              (dVar26 = *(dword *)(NativeFollower203_ARRAY_00d2f8b0[0].stats +
                                  (int)fStack00000040 + -0xc), dVar26 == 1))))
          goto code_r0x00031b05;
code_r0x000318c9:
          fStack00000090 = (float)party_skill_rank_native203(pNStack000000f0,dVar26);
          uVar41 = (int)fStack00000090 + (uint)(fStack00000090 == 0.0);
          if (9 < uVar41) {
            uVar41 = 10;
          }
          if (dVar26 < 0x7f) {
            if (dVar26 == 0) {
              dVar26 = 0;
              uVar42 = 0;
            }
            else {
              puVar40 = (ushort *)(dVar26 * 0x14 + 0x38309a + uVar41 * 2);
code_r0x00031b2f:
              uVar42 = (uint)*puVar40;
            }
          }
          else {
            puVar40 = (ushort *)(uVar41 * 2 + 0x3840d2);
            iVar23 = -0x22470;
            do {
              if (dVar26 == *(ushort *)(iVar23 + 0x3a63d0)) goto code_r0x00031b2f;
              puVar40 = puVar40 + 0xd8;
              iVar23 = iVar23 + 0x1b0;
            } while (iVar23 != 0);
          }
        }
        else {
          if (dVar26 == 7) {
            iVar23 = (int)pNStack00000120 * 0x298;
            if ((*pfVar4 - *(float *)(iVar23 + 0xbef7d8)) * *(float *)(iVar23 + 0xbef7e8) +
                (*pfVar3 - *(float *)(iVar23 + 0xbef7dc)) * *(float *)(iVar23 + 0xbef7ec) < 0.0) {
              dVar26 = 0x8e;
              dVar28 = party_skill_rank_native203(pNStack000000f0,0x8e);
              if (dVar28 != 0) goto code_r0x000318c9;
            }
            dVar26 = 0xd;
            dVar28 = party_skill_rank_native203(pNStack000000f0,0xd);
            if (dVar28 != 0) goto code_r0x000318c9;
            dVar26 = pNStack000000f0->id;
code_r0x00031003:
            if (dVar26 == 9) {
              dVar26 = 0xad;
              dVar28 = party_skill_rank_native203(pNStack000000f0,0xad);
              if (dVar28 != 0) goto code_r0x000318c9;
              dVar26 = pNStack000000f0->id;
            }
            if (dVar26 == 10) {
              dVar26 = 0xb4;
              dVar28 = party_skill_rank_native203(pNStack000000f0,0xb4);
              if (dVar28 != 0) goto code_r0x000318c9;
              dVar26 = pNStack000000f0->id;
            }
            if (dVar26 == 0xb) {
              iVar23 = (int)pNStack00000120 * 0x298;
              uVar41 = *(uint *)(iVar23 + 0xbef888);
              if ((0x28f < uVar41) || (*(int *)(uVar41 * 0x44 + 0x25979c) - 0x6c3U < 0xfffffffa)) {
                if ((*(int *)(iVar23 + 0xbef86c) == 0) || (*(int *)(iVar23 + 0xbef880) == 0)) {
                  uVar41 = *(uint *)(uVar41 * 0x40 + 0x2c0178);
                }
                else {
                  uVar41 = (uint)(*(int *)(iVar23 + 0xbef880) == 3);
                }
                if ((uVar41 == 0) && (*(float *)(iVar23 + 0xbef8ac) <= 0.0)) {
                  dVar26 = 0xe6;
                  dVar28 = party_skill_rank_native203(pNStack000000f0,0xe6);
                  if (dVar28 != 0) goto code_r0x000318c9;
                  dVar26 = pNStack000000f0->id;
                  goto code_r0x000318a2;
                }
              }
            }
            else {
code_r0x000318a2:
              if (dVar26 == 0xf) {
                dVar26 = 0x17a;
                dVar28 = 0x17a;
                goto code_r0x000318bc;
              }
            }
          }
          else {
            if (dVar26 != 5) goto code_r0x00031003;
            if ((((*(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                             (int)fStack00000040 + 0x48) <= fVar50) ||
                 (*(int *)(NativeFollower203_ARRAY_00d2f8b0[0].stats + (int)fStack00000040 + -0xc)
                  != 0xca)) ||
                ((NativeFollower203 *)
                 *(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                         (int)fStack00000040 + 0x18) != pNStack00000120)) ||
               (*(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                        (int)fStack00000040 + 0x24) !=
                *(int *)((int)pNStack00000120 * 0x298 + 0xbef884))) goto code_r0x00031b05;
            dVar26 = 0xd3;
            dVar28 = 0xd3;
code_r0x000318bc:
            dVar28 = party_skill_rank_native203(pNStack000000f0,dVar28);
            if (dVar28 != 0) goto code_r0x000318c9;
          }
code_r0x00031b05:
          fStack00000090 = 0.0;
          dVar26 = 1;
        }
        uVar41 = dVar26;
        if (*(uint *)(pbStack00000070 + 4) < uVar42) {
          fStack00000090 = 0.0;
          uVar41 = 1;
        }
        iVar23 = 0x48;
        if (((pNStack000000f0->id != 0xf) && (uVar41 != 0xad)) &&
           ((uVar41 != 0xb4 && (iVar23 = 0x10, uVar41 == 0xe6)))) {
          iVar23 = 0x40;
        }
        iVar31 = (int)pNStack00000120 * 0x298;
        fVar50 = *(float *)(iVar31 + 0xbef7d8);
        fVar52 = *pfVar4;
        fVar49 = *(float *)(iVar31 + 0xbef7dc);
        fVar53 = *pfVar3;
        fVar46 = (float10)func_0x00137820();
        pbVar1[0] = 1;
        pbVar1[1] = 0;
        pbVar1[2] = 0;
        pbVar1[3] = 0;
        fVar47 = (float10)func_0x00137820();
        fVar56 = (float)fVar47;
        if (_DAT_0074a494 < fVar56) {
          *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x54
                    ) = (fVar50 - fVar52) / fVar56;
          *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x58
                    ) = (fVar49 - fVar53) / fVar56;
        }
        fStack00000008 = (float)iVar23;
        if ((float)fVar46 <= fStack00000008) {
          if (*(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                        (int)fStack00000040 + 0x6c) <= _DAT_00be3098) {
            fStack0000000c = *(float *)(iVar31 + 0xbef7dc);
            fVar50 = *(float *)(iVar31 + 0xbef7d8);
            fVar52 = *pfVar3;
            fStack00000008 = fVar50;
            iVar23 = func_0x00095200();
            if (iVar23 != 0) {
              if (_DAT_00c2c8bc != (code *)0x0) {
                fStack00000008 = fVar52;
                fStack0000000c = fVar50;
                iVar23 = (*_DAT_00c2c8bc)();
                if (iVar23 == 0) break;
              }
              pNVar34 = pNStack000000f0;
              iStack000000d0 = (uint)(uVar41 == 0x17a) * 4 + 1;
              if (uVar41 == 0xd3) {
                iStack000000d0 = 4;
              }
              uVar42 = pNStack000000f0->id;
              if ((uVar41 == 1) && (dVar26 = 1, *(char *)(uVar42 + 0xd42501) != '\0')) {
                if (uVar42 == 5) {
                  dVar28 = 0xca;
                }
                else if (uVar42 == 0xf) {
                  dVar28 = 0x176;
                }
                else {
                  dVar28 = 0;
                  if (uVar42 == 7) {
                    dVar28 = 0xc;
                  }
                }
                fVar50 = (float)party_skill_rank_native203(pNStack000000f0,dVar28);
                uVar42 = pNVar34->id;
                if ((uVar42 == 5) && (fVar50 != 0.0)) {
                  _DAT_00c25dc8 = _DAT_00c25dc8 * 0x19660d + 0x3c6ef35f;
                  uVar42 = 5;
                  if ((_DAT_00c25dc8 >> 0x10 ^ _DAT_00c25dc8) % 100 < 0x1eU - (int)fVar50) {
                    iStack000000d0 = 3;
                    dVar26 = 0xca;
                    fStack00000090 = fVar50;
                  }
                  else {
                    dVar26 = 1;
                  }
                }
                else {
                  if (uVar42 == 0xf) {
                    if (fVar50 == 0.0) {
                      uVar42 = 0xf;
                      goto code_r0x0003366b;
                    }
                  }
                  else if ((uVar42 != 7) || (fVar50 == 0.0)) goto code_r0x00033664;
                  _DAT_00c25dc8 = _DAT_00c25dc8 * 0x19660d + 0x3c6ef35f;
                  iStack000000d0 =
                       ((_DAT_00c25dc8 >> 0x10 ^ _DAT_00c25dc8) % 100 < (uint)((int)fVar50 * 5)) + 1
                  ;
                  dVar26 = 1;
                }
code_r0x0003366b:
                uVar41 = *(uint *)(uVar42 * 4 + 0x5e59a0);
              }
              else {
code_r0x00033664:
                uVar41 = 0;
                if (uVar42 < 0x13) goto code_r0x0003366b;
              }
              pfVar3 = (float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                                (int)fStack00000040 + 0x6c);
              uVar42 = 0x1c89;
              uVar33 = 0;
              do {
                uVar38 = uVar42 + uVar33 >> 1;
                if (*(uint *)(uVar38 * 0x14 + 0x35d3d4) < uVar41) {
                  uVar33 = uVar38 + 1;
                }
                else {
                  uVar42 = uVar38;
                }
              } while (uVar33 < uVar42);
              iVar23 = 0;
              if (((uVar33 < 0x1c89) && (*(uint *)(uVar33 * 0x14 + 0x35d3d4) == uVar41)) &&
                 (iVar23 = *(int *)((uint)*(ushort *)(uVar33 * 2 + 0x3a6608) * 0x44 + 0x2d9464),
                 0x16 < iVar23)) {
                iVar23 = 0;
              }
              uVar41 = (uint)*(ushort *)
                              (*(int *)(NativeFollower203_ARRAY_00d2f8b0[0].stats + iVar22 + -0x18)
                               * 0x2e + 0x5d405c + iVar23 * 2);
              uVar42 = (uint)NativeFollower203_ARRAY_00d2f8b0[0].stats[(int)fStack00000040 + 1];
              if (_DAT_00be3098 <
                  *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                            (int)fStack00000040 + 4)) {
                uVar42 = uVar42 + 2 +
                         (uint)NativeFollower203_ARRAY_00d2f8b0[0].buffRank[(int)fStack00000040 + 1]
                ;
              }
              uVar33 = (uint)NativeFollower203_ARRAY_00d2f8b0[0].stats[(int)fStack00000040 + 4];
              if (_DAT_00be3098 < *(float *)(pbStack00000070 + 0x44)) {
                uVar33 = uVar33 + NativeFollower203_ARRAY_00d2f8b0[0].buffRank[(int)fStack00000040];
              }
              iVar23 = uVar41 - ((uVar42 * 4 + uVar33) * uVar41) / 1000;
              if (iVar23 < 0x1f) {
                iVar23 = 0x1e;
              }
              pbStack00000070 = (byte *)((float)iVar23 * fRam0074a4a4);
              func_0x00136dc0();
              fVar47 = (float10)func_0x00136bf0();
              pbVar2[0] = 0;
              pbVar2[1] = 0;
              pbVar2[2] = 0;
              pbVar2[3] = 0;
              *(dword *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x28) =
                   dVar26;
              *(dword *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                        (int)fStack00000040 + 0x30) = dVar26;
              *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                        (int)fStack00000040 + 0x2c) = fStack00000090;
              *(int *)(NativeFollower203_ARRAY_00d2f8b0[0].stats + (int)fStack00000040 + -0x14) =
                   iStack000000d0;
              pbVar1 = NativeFollower203_ARRAY_00d2f8b0[0].stats + (int)fStack00000040 + -0x10;
              pbVar1[0] = 0;
              pbVar1[1] = 0;
              pbVar1[2] = 0;
              pbVar1[3] = 0;
              *(int *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                      (int)fStack00000040 + 0x18) = *piVar5;
              *(undefined4 *)
               ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x24) =
                   *(undefined4 *)(iVar31 + 0xbef884);
              fVar50 = _DAT_00be3098;
              *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                        (int)fStack00000040 + 100) = _DAT_00be3098;
              *(undefined4 *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x74) =
                   0;
              *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + iVar22 + 0x68) =
                   (float)fVar47 + fVar50;
              *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                        (int)fStack00000040 + 0x70) = (float)fVar47 * fRam0074a2f0 + fVar50;
              *pfVar3 = (float)pbStack00000070 + fVar50;
              if ((dVar26 != 1) && (dVar26 != 0xca)) {
                iVar22 = -0x22470;
                do {
                  if (dVar26 == *(ushort *)(iVar22 + 0x3a63d0)) {
                    pbStack00000070 =
                         (byte *)((float)*(uint *)(iVar22 + 0x3a6478 + (int)fStack00000090 * 4) *
                                 _DAT_0074a494);
                    goto code_r0x00033ac2;
                  }
                  iVar22 = iVar22 + 0x1b0;
                } while (iVar22 != 0);
                pbStack00000070 = (byte *)_DAT_00749e28;
code_r0x00033ac2:
                fVar47 = (float10)func_0x00136bf0();
                *pfVar3 = (float)fVar47;
                fStack00000090 = _DAT_00be3098;
                fVar47 = (float10)func_0x00136bf0();
                *(float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                          (int)fStack00000040 + 0x7c) = fStack00000090 + (float)fVar47;
                *(undefined4 *)
                 ((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil + (int)fStack00000040 + 0x48) =
                     0;
              }
              if (pNStack000000f0->id - 9 < 2) {
                pfVar3 = (float *)((int)NativeFollower203_ARRAY_00d2f8b0[0].buffUntil +
                                  (int)fStack00000040 + 0x70);
                fVar50 = *pfVar3;
                fVar52 = (float)fVar46 / fRam0074a4a8 + fVar50;
                *pfVar3 = fVar52;
                uVar42 = uRam00e381c0 & 7;
                auVar51._8_8_ = *(undefined8 *)(iVar31 + 0xbef7d8);
                auVar51._0_8_ = *(undefined8 *)pfVar4;
                uRam00e381c0 = uRam00e381c0 + 1;
                *(dword *)(uVar42 * 0x1c + 0xd42894) = _DAT_00bec5ac;
                *(undefined1 (*) [16])(uVar42 * 0x1c + 0xd42898) = auVar51;
                *(float *)(uVar42 * 0x1c + 0xd428a8) = fVar50;
                *(float *)(uVar42 * 0x1c + 0xd428ac) = fVar52;
              }
            }
          }
          break;
        }
code_r0x00031fc6:
        fStack0000000c = in_stack_000000b0;
code_r0x00033c8a:
        func_0x00113990();
      }
    }
  }
  goto LAB_00035034;
code_r0x000347d6:
  uVar41 = uVar42;
code_r0x000347d8:
  uVar42 = uVar41 + (int)fStack00000040 & 0x1f;
  *(undefined4 *)(uVar42 * 4 + 0xc25e34) = 0x3a;
  *(float *)(uVar42 * 4 + 0xc25ebc) = fVar50;
  _DAT_00c25eb8 = _DAT_00c25eb8 + 1;
LAB_00035034:
  uStack00000158 = uStack00000158 + 1;
  if (_DAT_00d2fb8c <= uStack00000158) {
    return;
  }
  goto LAB_0003042e;
}

