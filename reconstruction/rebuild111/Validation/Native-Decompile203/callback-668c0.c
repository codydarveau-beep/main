
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_000668c0(void)

{
  undefined4 *puVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  code *pcVar5;
  int iVar6;
  int iVar7;
  undefined4 unaff_EBX;
  undefined4 unaff_EBP;
  int iVar8;
  int iVar9;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  int *piVar10;
  
  if (_DAT_00d395fc != 0) {
    do {
      iVar6 = func_0x0012ebd0();
    } while (iVar6 != 0);
    (*_DAT_00bd8f44)(_DAT_00d395fc);
  }
  _DAT_00d395fc = 0;
  _DAT_00bda100 = 0xffffffff;
  _DAT_00bda104 = 0xffffffff;
  _DAT_00bda108 = 0xffffffff;
  func_0x00133f30(_DAT_00d39630);
  func_0x00137420(0xd39600,0,100);
  _DAT_00bda10c = 0xffffffff;
  _DAT_00d39840 = 0xffffffff;
  _DAT_00d39934 = 0;
  func_0x00133f30(_DAT_00d39694);
  func_0x00137420(0xd39664,0,100);
  _DAT_00bda110 = 0xffffffff;
  _DAT_00d39844 = 0xffffffff;
  _DAT_00d39938 = 0;
  func_0x00133f30(_DAT_00d396f8);
  func_0x00137420(0xd396c8,0,100);
  _DAT_00bda114 = 0xffffffff;
  _DAT_00d39848 = 0xffffffff;
  _DAT_00d3993c = 0;
  func_0x00133f30(_DAT_00d3975c);
  func_0x00137420(0xd3972c,0,100);
  _DAT_00bda118 = 0xffffffff;
  _DAT_00d3984c = 0xffffffff;
  _DAT_00d39940 = 0;
  func_0x00133f30(_DAT_00e26974);
  _DAT_00e26974 = 0;
  _DAT_00e26970 = 0;
  func_0x00137420(0xdfb6e0,0,0x3c);
  iVar6 = 0;
  do {
    func_0x00091370();
    iVar6 = iVar6 + 1;
  } while (iVar6 != 0x6a);
  _DAT_00d39978 = 0;
  iVar6 = 0xc;
  piVar10 = (int *)0xd39c04;
  do {
    if (piVar10[3] != 0) {
      func_0x00139e10(0xd39b24);
      iVar8 = *piVar10;
      if (_DAT_00d39b40 == iVar8) {
        _DAT_00d39b48 = 0;
      }
      if (_DAT_00d39b60 == iVar8) {
        _DAT_00d39b68 = 0;
      }
      if (_DAT_00d39b80 == iVar8) {
        _DAT_00d39b88 = 0;
      }
      if (_DAT_00d39ba0 == iVar8) {
        _DAT_00d39ba8 = 0;
      }
      if (_DAT_00d39bc0 == iVar8) {
        _DAT_00d39bc8 = 0;
      }
      if (_DAT_00d39be0 == iVar8) {
        _DAT_00d39be8 = 0;
      }
      *(undefined4 *)(iVar8 * 4 + 0xbdaa48) = 0;
      *(undefined4 *)(iVar8 * 4 + 0xbdb774) = 0;
      func_0x00139e30(0xd39b24);
      func_0x00133f30(piVar10[3]);
      func_0x00137420(piVar10,0,0x14);
    }
    piVar10 = piVar10 + 5;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  _DAT_00d39cf4 = 0;
  if (_DAT_00d39d28 != 0 || _DAT_00d36830 != 0) {
    do {
      iVar6 = func_0x0012ebd0();
    } while (iVar6 != 0);
    func_0x00133f30(_DAT_00d39d28);
    func_0x00137420(0xd39cf8,0,100);
    if (_DAT_00d36830 != 0) {
      (*_DAT_00bd8f44)(_DAT_00d36830);
    }
    _DAT_00d36830 = 0;
    _DAT_00d39964 = 0;
  }
  _DAT_00bda11c = 0xffffffff;
  do {
    iVar6 = func_0x0012ebd0();
    pcVar5 = _DAT_00bd8f44;
  } while (iVar6 != 0);
  iVar6 = -0xa0;
  do {
    if (*(int *)(iVar6 + 0xd39dfc) != 0) {
      (*pcVar5)(*(int *)(iVar6 + 0xd39dfc));
    }
    *(undefined4 *)(iVar6 + 0xd39dfc) = 0;
    *(undefined4 *)(iVar6 + 0xd39e9c) = 0xffffffff;
    *(undefined4 *)(&DAT_00d39f3c + iVar6) = 0xffffffff;
    iVar6 = iVar6 + 4;
  } while (iVar6 != 0);
  func_0x000910f0();
  func_0x000911f0();
  iVar6 = 0;
  do {
    iVar8 = iVar6 * 0x20;
    if (*(int *)(iVar8 + 0xd41048) != 0) {
      puVar1 = (undefined4 *)(iVar8 + 0xd41048);
      do {
        iVar7 = func_0x0012ebd0();
      } while (iVar7 != 0);
      if (*(int *)*puVar1 != 0) {
        (*pcVar5)(*(int *)*puVar1);
        *(undefined4 *)*puVar1 = 0;
      }
      _DAT_00d42048 = _DAT_00d42048 - *(int *)(iVar8 + 0xd4104c);
      func_0x00137420(puVar1,0,0x20);
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 != 0x80);
  _DAT_00d41044 = 0;
  _DAT_00d41040 = 0;
  do {
    iVar6 = func_0x0012ebd0();
  } while (iVar6 != 0);
  iVar8 = 0;
  iVar6 = 0xd406f0;
  do {
    iVar7 = -0x80;
    do {
      iVar9 = *(int *)(iVar6 + 0x7c + iVar7);
      if (iVar9 != 0) {
        (*pcVar5)(iVar9);
        *(undefined4 *)(iVar6 + 0x7c + iVar7) = 0;
      }
      iVar9 = *(int *)(iVar6 + 0x80 + iVar7);
      if (iVar9 != 0) {
        (*pcVar5)(iVar9);
        *(undefined4 *)(iVar6 + 0x80 + iVar7) = 0;
      }
      iVar7 = iVar7 + 8;
    } while (iVar7 != 0);
    iVar8 = iVar8 + 1;
    iVar6 = iVar6 + 0x80;
  } while (iVar8 != 0x12);
  iVar6 = -0x50;
  do {
    if (*(int *)(&DAT_00d4103c + iVar6) != 0) {
      (*pcVar5)(*(int *)(&DAT_00d4103c + iVar6));
      *(undefined4 *)(&DAT_00d4103c + iVar6) = 0;
    }
    iVar6 = iVar6 + 4;
  } while (iVar6 != 0);
  if (_DAT_00d4103c != 0) {
    (*_DAT_00bd8f44)(_DAT_00d4103c);
    _DAT_00d4103c = 0;
  }
  func_0x00133f30(_DAT_00d4207c);
  func_0x00133f30(_DAT_00d42080);
  if (_DAT_00d42090 != 0) {
    (*_DAT_00bd8f44)(_DAT_00d42090);
  }
  func_0x00137420(0xd4204c,0,0x48);
  _DAT_00d42064 = 0xffffffff;
  _DAT_00d42060 = 0xffffffff;
  func_0x00133f30(_DAT_00d420c4);
  func_0x00133f30(_DAT_00d420c8);
  if (_DAT_00d420d8 != 0) {
    (*_DAT_00bd8f44)(_DAT_00d420d8);
  }
  func_0x00137420(0xd42094,0,0x48);
  _DAT_00d420ac = 0xffffffff;
  _DAT_00d420a8 = 0xffffffff;
  func_0x00133f30(_DAT_00d4210c);
  func_0x00133f30(_DAT_00d42110);
  if (_DAT_00d42120 != 0) {
    (*_DAT_00bd8f44)(_DAT_00d42120);
  }
  func_0x00137420(0xd420dc,0,0x48);
  _DAT_00d420f4 = 0xffffffff;
  _DAT_00d420f0 = 0xffffffff;
  func_0x00133f30(_DAT_00d42124);
  _DAT_00d42124 = 0;
  _DAT_00bda120 = 0xffffffff;
  if (_DAT_00bda124 != -1) {
    func_0x001382a0(_DAT_00bda124);
  }
  _DAT_00bda124 = 0xffffffff;
  if (_DAT_00d42128 != 0) {
    do {
      iVar6 = func_0x0012ebd0();
    } while (iVar6 != 0);
    (*_DAT_00bd8f44)(_DAT_00d42128);
    _DAT_00d42128 = 0;
  }
  iVar6 = -0x20;
  iVar8 = 0xd4212c;
  do {
    func_0x00133f30(*(undefined4 *)(iVar8 + 0x30));
    func_0x00137420(iVar8,0,100);
    *(undefined4 *)(iVar6 + 0xd4246c) = 0xffffffff;
    *(undefined4 *)(&DAT_00d4248c + iVar6) = 0xffffffff;
    *(undefined4 *)(iVar6 + 0xd365bc) = 0xffffffff;
    *(undefined4 *)(&DAT_00d39964 + iVar6) = 0;
    *(undefined4 *)(iVar6 + 0xd39870) = 0xffffffff;
    iVar8 = iVar8 + 100;
    iVar6 = iVar6 + 4;
  } while (iVar6 != 0);
  DAT_00d4248c = 1;
  if (_DAT_00e42614 != 0) {
    do {
      iVar6 = func_0x0012ebd0();
    } while (iVar6 != 0);
    (*_DAT_00bd8f44)(_DAT_00e42614);
  }
  _DAT_00e42614 = 0;
  _DAT_00bdaa30 = 0xffffffff;
  _DAT_00bdaa2c = 0xffffffff;
  _DAT_00bdaa28 = 0xffffffff;
  iVar6 = 0x40;
  iVar8 = 0xcc1788;
  do {
    if (*(int *)(iVar8 + 8) != 0) {
      _DAT_00cc1f88 = _DAT_00cc1f88 - *(int *)(iVar8 + 4);
      func_0x00133f30(*(int *)(iVar8 + 8));
    }
    iVar7 = func_0x00137420(iVar8,0,0x20);
    iVar8 = iVar8 + 0x20;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  _DAT_00cc1f94 = 0;
  _DAT_00cc1f90 = 0;
  if (_DAT_00cc1758 != 0) {
    iVar6 = -1;
    iVar8 = 0;
    do {
      do {
        iVar9 = iVar8 * 0x40;
        if (((*(int *)(iVar9 + 0xcc0d90) != 0) &&
            ((iVar7 = 0, _DAT_00cc1774 == (code *)0x0 ||
             (iVar7 = (*_DAT_00cc1774)(_DAT_00cc1778,iVar9 + 0xcc0d68,unaff_ESI,unaff_EDI,unaff_EBX,
                                       unaff_EBP), iVar7 == 0)))) &&
           ((iVar6 < 0 ||
            (puVar2 = (uint *)(iVar6 * 0x40 + 0xcc0d64),
            uVar3 = (uint)(*(uint *)(iVar9 + 0xcc0d60) < *(uint *)(iVar6 * 0x40 + 0xcc0d60)),
            uVar4 = *(uint *)(iVar9 + 0xcc0d64) - *puVar2, iVar7 = uVar4 - uVar3,
            *(uint *)(iVar9 + 0xcc0d64) < *puVar2 || uVar4 < uVar3)))) {
          iVar6 = iVar8;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 != 0x28);
      if (iVar6 < 0) {
        return iVar7;
      }
      iVar6 = iVar6 * 0x40;
      _DAT_00cc1758 = _DAT_00cc1758 - *(int *)(iVar6 + 0xcc0d5c);
      func_0x00133f30(*(undefined4 *)(iVar6 + 0xcc0d90));
      func_0x00137420(iVar6 + 0xcc0d68,0,0x30);
      iVar7 = func_0x00137420(iVar6 + 0xcc0d58,0,0x40);
      iVar8 = 0;
      iVar6 = -1;
    } while (_DAT_00cc1758 != 0);
  }
  return iVar7;
}

