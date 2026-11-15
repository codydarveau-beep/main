
int __fastcall FUN_00114980(int param_1,int param_2)

{
  int iVar1;
  
  if (param_1 < 0x17a) {
    switch(param_1) {
    case 0xad:
    case 0xb4:
      return param_2 * 0x19 + 0x7d;
    case 0xae:
    case 0xaf:
    case 0xb0:
    case 0xb1:
    case 0xb2:
    case 0xb3:
    case 0xb5:
    case 0xb6:
    case 0xb7:
    case 0xb8:
    case 0xb9:
    case 0xba:
    case 0xbb:
    case 0xbc:
    case 0xbd:
    case 0xbe:
    case 0xbf:
    case 0xc0:
    case 0xc1:
    case 0xc2:
    case 0xc3:
    case 0xc4:
    case 0xc5:
    case 0xc6:
    case 199:
    case 200:
    case 0xc9:
    case 0xcb:
    case 0xcc:
    case 0xcd:
    case 0xce:
    case 0xcf:
    case 0xd0:
    case 0xd1:
    case 0xd2:
      break;
    case 0xca:
      return param_2 * 0x14 + 100;
    case 0xd3:
      return param_2 * 0x32 + 0x96;
    default:
      if (param_1 == 0x8e) {
        return param_2 * 0x28 + 300;
      }
    }
  }
  else {
    if (param_1 == 0x17a) {
      return param_2 * 10 + 100;
    }
    if ((param_1 == 0x182) || (param_1 == 0x184)) {
      return param_2 * 0x14 + 0xa0;
    }
  }
  iVar1 = 100;
  if ((param_1 - 0x186U & 0xfffffffd) == 0) {
    iVar1 = param_2 * 0x1e + 0xbe;
  }
  return iVar1;
}

