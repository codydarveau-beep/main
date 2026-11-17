56b67: je 0x56b69
56b69: addss xmm0, dword ptr [esp + 0x70]
56b6f: movss dword ptr [esp + 4], xmm0
56b75: movss xmm0, dword ptr [esp + 0x50]
56b7b: movss dword ptr [esp], xmm0
56b80: mov dword ptr [esp + 0xc], eax
56b84: mov dword ptr [esp + 8], 0x3fb33333
56b8c: mov ecx, esi
56b8e: call 0x125f40
56b93: jmp 0x571bb
56b98: mov eax, dword ptr [esp + 0x40]
56b9c: cmp dword ptr [eax + 0xbef370], 0
56ba3: je 0x56c59
56ba9: mov eax, dword ptr [esp + 0x40]
56bad: mov eax, dword ptr [eax + 0xbef368]
56bb3: test eax, eax
56bb5: je 0x56c59
56bbb: imul eax, eax, 0x83
56bc1: mov ecx, dword ptr [esp + 0x40]
56bc5: imul ecx, dword ptr [ecx + 0xbef36c], 0x1eef
56bcf: add ecx, eax
56bd1: mov eax, ecx
56bd3: shr eax, 0x10
56bd6: xor eax, ecx
56bd8: imul ecx, eax, 0x7feb352d
56bde: mov eax, ecx
56be0: shr eax, 0xf
56be3: xor eax, ecx
56be5: movzx ecx, al
56be8: xorps xmm0, xmm0
56beb: cvtsi2ss xmm0, ecx
56bef: movss xmm1, dword ptr [0x74a64c]; 255.0
56bf7: divss xmm0, xmm1
56bfb: movss xmm2, dword ptr [0x74a6d8]; -0.5
56c03: addss xmm0, xmm2
56c07: mulss xmm0, dword ptr [0x74a438]; 16.0
56c0f: movss xmm3, dword ptr [0x74a578]; 1.2000000476837158
56c17: mulss xmm0, xmm3
56c1b: movss xmm4, dword ptr [esp + 0x50]
56c21: addss xmm4, xmm0
56c25: movss dword ptr [esp + 0x50], xmm4
56c2b: movzx eax, ah
56c2e: xorps xmm0, xmm0
56c31: cvtsi2ss xmm0, eax
56c35: divss xmm0, xmm1
56c39: addss xmm0, xmm2
56c3d: mulss xmm0, dword ptr [0x74a344]; 10.0
56c45: mulss xmm0, xmm3
56c49: movss xmm1, dword ptr [esp + 0x70]
56c4f: addss xmm1, xmm0
56c53: movss dword ptr [esp + 0x70], xmm1
56c59: movaps xmm1, xmmword ptr [esp + 0x60]
56c5e: movaps xmm2, xmm1
56c61: divss xmm2, dword ptr [0x74a340]; 3.0
56c69: movss dword ptr [esp + 0xb0], xmm2
56c72: xorps xmm0, xmm0
56c75: maxss xmm0, xmm2
56c79: mulss xmm0, dword ptr [0x74a314]; 6.0
56c81: cvttss2si eax, xmm0
56c85: mov ecx, eax
56c87: sar ecx, 0x1f
56c8a: subss xmm0, dword ptr [0x74a300]
56c92: cvttss2si esi, xmm0
56c96: and esi, ecx
56c98: or esi, eax
56c9a: cmp esi, 5
56c9d: mov eax, 5
56ca2: cmovae esi, eax
56ca5: movss xmm0, dword ptr [0x74a2f4]; 8.0
56cad: mulss xmm1, xmm0
56cb1: addss xmm1, dword ptr [0x74a2f0]
56cb9: movss dword ptr [esp + 4], xmm1
56cbf: mov dword ptr [esp], 0x3fb33333
56cc6: call 0x136dc0
56ccb: movss xmm0, dword ptr [esp + 0xb0]
56cd4: movss xmm1, dword ptr [0x74a2f4]; 8.0
56cdc: mulss xmm0, xmm1
56ce0: addss xmm0, dword ptr [0x74a710]
56ce8: mulss xmm0, dword ptr [esp + 0x1a8]
56cf1: addss xmm0, dword ptr [esp + 0x70]
56cf7: mov eax, dword ptr [esp + 0x40]
56cfb: mov ecx, dword ptr [eax + 0xbef354]
56d01: fstp dword ptr [esp + 8]
56d05: movss dword ptr [esp + 4], xmm0
56d0b: movss xmm0, dword ptr [esp + 0x50]
56d11: movss dword ptr [esp], xmm0
56d16: mov dword ptr [esp + 0xc], esi
56d1a: jmp 0x56f86
56d1f: movaps xmm0, xmmword ptr [esp + 0x60]
