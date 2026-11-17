568b0: xchg dword ptr [esi], eax
568b2: or dword ptr [eax], eax
568b4: add bh, bh
568b6: test byte ptr [eax + eax], ah
568b9: add dword ptr [eax], eax
568bb: add byte ptr [ebp - 0x77c00b9], cl
568c1: push es
568c2: ja 0x56950
568c8: lea esi, [esi + esi*2 + 0xbef360]
568cf: jmp dword ptr [eax*4 + 0x1c0898]
568d6: movaps xmm1, xmmword ptr [esp + 0x60]
568db: movaps xmm0, xmm1
568de: divss xmm0, dword ptr [0x74a44c]; 1.5
568e6: mulss xmm1, dword ptr [0x74a710]; 56.0
568ee: divss xmm1, dword ptr [0x74a2c4]; 0.800000011920929
568f6: addss xmm1, dword ptr [0x74a97c]; 28.0
568fe: movss xmm2, dword ptr [esp + 0xb0]
56907: mulss xmm2, xmm1
5690b: addss xmm2, dword ptr [esp + 0x70]
56911: movss dword ptr [esp + 0xb0], xmm2
5691a: cmp edi, 6
5691d: xorps xmm1, xmm1
56920: maxss xmm1, xmm0
56924: movaps xmmword ptr [esp + 0x60], xmm1
56929: je 0x56f95
5692f: xor eax, eax
56931: cmp edi, 3
56934: jne 0x57074
5693a: mov ecx, dword ptr [esp + 0x40]
5693e: cmp dword ptr [ecx + 0xbef364], 2
56945: sete al
56948: or eax, 0x34
5694b: jmp 0x57094
56950: cmp dword ptr [esp + 0x90], 2
56958: jl 0x5717d
5695e: mov eax, dword ptr [esi + esi*2 + 0xbef354]
56965: cdq 
56966: idiv dword ptr [esp + 0x90]
5696d: mov ebx, eax
5696f: mov dword ptr [esp + 0xb0], edx
56976: lea edi, [esi + esi*2 + 0xbef358]
5697d: xor esi, esi
5697f: xorps xmm1, xmm1
56982: cvtsi2ss xmm1, esi
56986: mulss xmm1, dword ptr [edi - 8]
5698b: movaps xmm0, xmmword ptr [esp + 0x60]
56990: subss xmm0, xmm1
56994: ucomiss xmm0, dword ptr [0x74a9e0]; 0.0
5699b: jb 0x569ec
5699d: movss xmm1, dword ptr [0x74a44c]; 1.5
569a5: ucomiss xmm1, xmm0
569a8: jb 0x569ec
569aa: mov ecx, dword ptr [edi + 0xc]
569ad: xor eax, eax
569af: cmp esi, dword ptr [esp + 0xb0]
569b6: setl al
569b9: add eax, ebx
569bb: mov dword ptr [esp + 0xc], ecx
569bf: movss dword ptr [esp + 4], xmm0
569c5: mov dword ptr [esp], eax
569c8: mov dword ptr [esp + 8], 0
569d0: mov ecx, dword ptr [esp + 0x140]
569d7: lea edx, [esp + 0x190]
569de: call 0x126100
569e3: mov eax, dword ptr [edi]
569e5: mov dword ptr [esp + 0x90], eax
569ec: inc esi
569ed: cmp esi, dword ptr [esp + 0x90]
569f4: jl 0x5697f
569f6: mov eax, dword ptr [esp + 0x40]
569fa: cmp dword ptr [eax + 0xbef370], 0
56a01: je 0x56ab7
56a07: mov eax, dword ptr [esp + 0x40]
56a0b: mov eax, dword ptr [eax + 0xbef368]
56a11: test eax, eax
56a13: je 0x56ab7
56a19: imul eax, eax, 0x83
56a1f: mov ecx, dword ptr [esp + 0x40]
56a23: imul ecx, dword ptr [ecx + 0xbef36c], 0x1eef
56a2d: add ecx, eax
56a2f: mov eax, ecx
56a31: shr eax, 0x10
56a34: xor eax, ecx
56a36: imul ecx, eax, 0x7feb352d
56a3c: mov eax, ecx
56a3e: shr eax, 0xf
56a41: xor eax, ecx
56a43: movzx ecx, al
56a46: xorps xmm0, xmm0
56a49: cvtsi2ss xmm0, ecx
56a4d: movss xmm1, dword ptr [0x74a64c]; 255.0
56a55: divss xmm0, xmm1
56a59: movss xmm2, dword ptr [0x74a6d8]; -0.5
56a61: addss xmm0, xmm2
56a65: mulss xmm0, dword ptr [0x74a438]; 16.0
56a6d: movss xmm3, dword ptr [0x74a578]; 1.2000000476837158
56a75: mulss xmm0, xmm3
56a79: movss xmm4, dword ptr [esp + 0x50]
56a7f: addss xmm4, xmm0
56a83: movss dword ptr [esp + 0x50], xmm4
56a89: movzx eax, ah
56a8c: xorps xmm0, xmm0
56a8f: cvtsi2ss xmm0, eax
56a93: divss xmm0, xmm1
56a97: addss xmm0, xmm2
56a9b: mulss xmm0, dword ptr [0x74a344]; 10.0
56aa3: mulss xmm0, xmm3
56aa7: movss xmm1, dword ptr [esp + 0x70]
56aad: addss xmm1, xmm0
56ab1: movss dword ptr [esp + 0x70], xmm1
56ab7: movaps xmm1, xmmword ptr [esp + 0x60]
56abc: movaps xmm0, xmm1
56abf: divss xmm0, dword ptr [edi - 8]
56ac4: cvttss2si eax, xmm0
56ac8: lea esi, [eax + 1]
56acb: mov ecx, dword ptr [esp + 0x90]
56ad2: cmp ecx, eax
56ad4: cmovle esi, ecx
56ad7: subss xmm1, dword ptr [esp + 0x120]
56ae0: movss dword ptr [esp + 4], xmm1
56ae6: mov dword ptr [esp], 0
56aed: call 0x136bf0
56af2: fstp dword ptr [esp + 0x890]
56af9: movss xmm0, dword ptr [esp + 0x890]
56b02: divss xmm0, dword ptr [0x74a44c]; 1.5
56b0a: xorps xmm1, xmm1
56b0d: maxss xmm1, xmm0
56b11: mulss xmm1, dword ptr [0x74a314]; 6.0
56b19: cvttss2si ecx, xmm1
56b1d: mov edx, ecx
56b1f: sar edx, 0x1f
56b22: subss xmm1, dword ptr [0x74a300]; 2147483648.0
56b2a: cvttss2si eax, xmm1
56b2e: and eax, edx
56b30: or eax, ecx
56b32: cmp eax, 5
56b35: mov ecx, 5
56b3a: cmovae eax, ecx
56b3d: xor edx, edx
56b3f: cmp dword ptr [edi + 0xc], 2
56b43: sete dl
56b46: inc edx
56b47: imul ebx, esi
56b4a: mov ecx, dword ptr [esp + 0xb0]
56b51: cmp ecx, esi
56b53: cmovl esi, ecx
56b56: add esi, ebx
56b58: movss xmm0, dword ptr [esp + 0x1a8]
56b61: mulss xmm0, dword ptr [0x74a710]; 56.0
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
56c8a: subss xmm0, dword ptr [0x74a300]; 2147483648.0
56c92: cvttss2si esi, xmm0
56c96: and esi, ecx
56c98: or esi, eax
56c9a: cmp esi, 5
56c9d: mov eax, 5
56ca2: cmovae esi, eax
56ca5: movss xmm0, dword ptr [0x74a2f4]; 8.0
56cad: mulss xmm1, xmm0
56cb1: addss xmm1, dword ptr [0x74a2f0]; 0.6000000238418579
56cb9: movss dword ptr [esp + 4], xmm1
56cbf: mov dword ptr [esp], 0x3fb33333
56cc6: call 0x136dc0
56ccb: movss xmm0, dword ptr [esp + 0xb0]
56cd4: movss xmm1, dword ptr [0x74a2f4]; 8.0
56cdc: mulss xmm0, xmm1
56ce0: addss xmm0, dword ptr [0x74a710]; 56.0
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
56d24: divss xmm0, dword ptr [0x74a44c]; 1.5
56d2c: movaps xmmword ptr [esp + 0x60], xmm0
56d31: cmp edi, 5
56d34: mov eax, 0x10
56d39: mov ecx, 0x24
56d3e: cmove eax, ecx
56d41: xorps xmm1, xmm1
56d44: cvtsi2ss xmm1, eax
56d48: movss dword ptr [esp + 0x90], xmm1
56d51: addss xmm0, dword ptr [0x74a8a0]; -0.4000000059604645
56d59: movss dword ptr [esp + 4], xmm0
56d5f: mov dword ptr [esp], 0
56d66: call 0x136bf0
56d6b: fstp dword ptr [esp + 0x894]
56d72: movss xmm0, dword ptr [esp + 0x894]
56d7b: mulss xmm0, dword ptr [0x74a3bc]; 40.0
56d83: addss xmm0, dword ptr [esp + 0x90]
56d8c: movss xmm1, dword ptr [esp + 0xb0]
56d95: mulss xmm1, xmm0
56d99: addss xmm1, dword ptr [esp + 0x70]
56d9f: movss dword ptr [esp + 0xb0], xmm1
56da8: movaps xmm0, xmmword ptr [esp + 0x60]
56dad: addss xmm0, xmm0
56db1: movss xmm1, dword ptr [0x749e28]; 1.0
56db9: subss xmm1, xmm0
56dbd: mulss xmm1, dword ptr [0x74a7f8]; 1.2999999523162842
56dc5: movss dword ptr [esp + 4], xmm1
56dcb: mov dword ptr [esp], 0x3f4ccccd
56dd2: call 0x136bf0
56dd7: xorps xmm0, xmm0
56dda: maxss xmm0, dword ptr [esp + 0x60]
56de0: mulss xmm0, dword ptr [0x74a314]; 6.0
56de8: cvttss2si ecx, xmm0
56dec: mov edx, ecx
56dee: sar edx, 0x1f
56df1: subss xmm0, dword ptr [0x74a300]; 2147483648.0
56df9: cvttss2si eax, xmm0
56dfd: and eax, edx
56dff: or eax, ecx
56e01: cmp eax, 5
56e04: mov ecx, 5
56e09: cmovae eax, ecx
56e0c: xor edx, edx
56e0e: cmp dword ptr [esi], 4
56e11: setne dl
56e14: add edx, 3
56e17: mov ecx, dword ptr [esp + 0x40]
56e1b: mov ecx, dword ptr [ecx + 0xbef354]
56e21: mov dword ptr [esp + 0xc], eax
56e25: fstp dword ptr [esp + 8]
56e29: movss xmm0, dword ptr [esp + 0xb0]
56e32: movss dword ptr [esp + 4], xmm0
56e38: movss xmm0, dword ptr [esp + 0x50]
56e3e: movss dword ptr [esp], xmm0
56e43: call 0x125f40
56e48: jmp 0x571bb
56e4d: movss xmm1, dword ptr [esp + 0x70]
56e53: addss xmm1, dword ptr [0x74a968]; -10.0
56e5b: movaps xmm0, xmmword ptr [esp + 0x60]
56e60: movaps xmm2, xmm0
56e63: mulss xmm2, dword ptr [0x74a984]; -18.0
56e6b: addss xmm2, xmm1
56e6f: movss dword ptr [esp + 0x70], xmm2
56e75: mulss xmm0, dword ptr [0x74a314]; 6.0
56e7d: cvttss2si eax, xmm0
56e81: mov ecx, eax
56e83: sar ecx, 0x1f
56e86: subss xmm0, dword ptr [0x74a300]; 2147483648.0
56e8e: cvttss2si esi, xmm0
56e92: and esi, ecx
56e94: or esi, eax
56e96: cmp esi, 5
56e99: mov eax, 5
56e9e: cmovae esi, eax
56ea1: movss xmm0, dword ptr [esp + 0x50]
56ea7: addss xmm0, dword ptr [0x74a988]; -15.0
56eaf: movzx eax, word ptr [esi*8 + 0x74680e]
56eb7: xorps xmm1, xmm1
56eba: cvtsi2ss xmm1, eax
56ebe: movzx eax, word ptr [esi*8 + 0x74680c]
56ec6: xorps xmm2, xmm2
56ec9: cvtsi2ss xmm2, eax
56ecd: movzx eax, word ptr [esi*8 + 0x74680a]
56ed5: movaps xmm3, xmm1
56ed8: movss xmm5, dword ptr [0x74a360]; 0.30000001192092896
56ee0: mulss xmm3, xmm5
56ee4: movaps xmm4, xmm2
56ee7: mulss xmm4, xmm5
56eeb: movaps xmm6, xmm3
56eee: movss xmm7, dword ptr [0x74a044]; 0.5
56ef6: mulss xmm6, xmm7
56efa: movss xmm5, dword ptr [esp + 0x70]
56f00: subss xmm5, xmm6
56f04: movaps xmm6, xmm4
56f07: mulss xmm6, xmm7
56f0b: subss xmm0, xmm6
56f0f: xorps xmm6, xmm6
56f12: cvtsi2ss xmm6, eax
56f16: movzx eax, word ptr [esi*8 + 0x746808]
56f1e: xorps xmm7, xmm7
56f21: cvtsi2ss xmm7, eax
56f25: movss dword ptr [esp + 0x1c], xmm1
56f2b: movss dword ptr [esp + 0x18], xmm2
56f31: movss dword ptr [esp + 0x14], xmm6
56f37: movss dword ptr [esp + 0x10], xmm7
56f3d: movss dword ptr [esp + 0xc], xmm3
56f43: movss dword ptr [esp + 8], xmm4
56f49: movss dword ptr [esp + 4], xmm5
56f4f: movss dword ptr [esp], xmm0
56f54: call 0x96cd0
56f59: mov eax, dword ptr [esp + 0x40]
56f5d: mov ecx, dword ptr [eax + 0xbef354]
56f63: mov dword ptr [esp + 0xc], esi
56f67: movss xmm0, dword ptr [esp + 0x70]
56f6d: movss dword ptr [esp + 4], xmm0
56f73: movss xmm0, dword ptr [esp + 0x50]
56f79: movss dword ptr [esp], xmm0
56f7e: mov dword ptr [esp + 8], 0x3ea66666
56f86: mov edx, 1
56f8b: call 0x125f40
56f90: jmp 0x571bb
56f95: movss xmm0, dword ptr [esp + 0xb0]
56f9e: addss xmm0, dword ptr [0x74a340]; 3.0
56fa6: movaps xmm1, xmmword ptr [esp + 0x60]
56fab: mulss xmm1, dword ptr [0x74a314]; 6.0
56fb3: cvttss2si ecx, xmm1
56fb7: mov edx, ecx
56fb9: sar edx, 0x1f
56fbc: subss xmm1, dword ptr [0x74a300]; 2147483648.0
56fc4: cvttss2si eax, xmm1
56fc8: and eax, edx
56fca: or eax, ecx
56fcc: cmp eax, 5
56fcf: mov ecx, 5
56fd4: cmovae eax, ecx
56fd7: movzx ecx, word ptr [eax*8 + 0x7467de]
56fdf: xorps xmm1, xmm1
56fe2: cvtsi2ss xmm1, ecx
56fe6: movzx ecx, word ptr [eax*8 + 0x7467dc]
56fee: xorps xmm2, xmm2
56ff1: cvtsi2ss xmm2, ecx
56ff5: movzx ecx, word ptr [eax*8 + 0x7467da]
56ffd: xorps xmm3, xmm3
57000: cvtsi2ss xmm3, ecx
57004: movzx eax, word ptr [eax*8 + 0x7467d8]
5700c: movaps xmm4, xmm1
5700f: movss xmm5, dword ptr [0x74a044]; 0.5
57017: mulss xmm4, xmm5
5701b: subss xmm0, xmm4
5701f: movaps xmm4, xmm2
57022: mulss xmm4, xmm5
57026: movss xmm5, dword ptr [esp + 0x50]
5702c: subss xmm5, xmm4
57030: xorps xmm4, xmm4
57033: cvtsi2ss xmm4, eax
57037: movss dword ptr [esp + 0x1c], xmm1
5703d: movss dword ptr [esp + 0x18], xmm2
57043: movss dword ptr [esp + 0x14], xmm3
57049: movss dword ptr [esp + 0x10], xmm4
5704f: movss dword ptr [esp + 0xc], xmm1
57055: movss dword ptr [esp + 8], xmm2
5705b: movss dword ptr [esp + 4], xmm0
57061: movss dword ptr [esp], xmm5
57066: call 0x96cd0
5706b: mov edi, dword ptr [esi]
5706d: mov eax, 0x37
57072: jmp 0x57085
57074: mov ecx, dword ptr [esp + 0x40]
57078: cmp dword ptr [ecx + 0xbef364], 2
5707f: sete al
57082: or eax, 0x32
57085: cmp edi, 2
57088: jne 0x57094
5708a: movss xmm0, dword ptr [0x74a980]; 0.6399999856948853
57092: jmp 0x5709c
57094: movss xmm0, dword ptr [0x749e28]; 1.0
5709c: movaps xmm1, xmmword ptr [esp + 0x60]
570a1: mulss xmm1, dword ptr [0x74a314]; 6.0
570a9: cvttss2si ecx, xmm1
570ad: mov edx, ecx
570af: sar edx, 0x1f
570b2: subss xmm1, dword ptr [0x74a300]; 2147483648.0
570ba: cvttss2si esi, xmm1
570be: and esi, edx
570c0: or esi, ecx
570c2: cmp esi, 5
570c5: mov ecx, 5
570ca: cmovae esi, ecx
570cd: lea eax, [eax + eax*2]
570d0: lea eax, [esi + eax*2]
570d3: movzx ecx, word ptr [eax*8 + 0x745d5e]
570db: xorps xmm1, xmm1
570de: cvtsi2ss xmm1, ecx
570e2: movzx ecx, word ptr [eax*8 + 0x745d5c]
570ea: xorps xmm2, xmm2
570ed: cvtsi2ss xmm2, ecx
570f1: movzx ecx, word ptr [eax*8 + 0x745d5a]
570f9: xorps xmm3, xmm3
570fc: cvtsi2ss xmm3, ecx
57100: movzx eax, word ptr [eax*8 + 0x745d58]
57108: movaps xmm4, xmm0
5710b: mulss xmm4, xmm1
5710f: mulss xmm0, xmm2
57113: movaps xmm5, xmm4
57116: movss xmm6, dword ptr [0x74a044]; 0.5
5711e: mulss xmm5, xmm6
57122: movss xmm7, dword ptr [esp + 0xb0]
5712b: subss xmm7, xmm5
5712f: movaps xmm5, xmm0
57132: mulss xmm5, xmm6
57136: movss xmm6, dword ptr [esp + 0x50]
5713c: subss xmm6, xmm5
57140: xorps xmm5, xmm5
57143: cvtsi2ss xmm5, eax
57147: movss dword ptr [esp + 0x1c], xmm1
5714d: movss dword ptr [esp + 0x18], xmm2
57153: movss dword ptr [esp + 0x14], xmm3
57159: movss dword ptr [esp + 0x10], xmm5
5715f: movss dword ptr [esp + 0xc], xmm4
57165: movss dword ptr [esp + 8], xmm0
5716b: movss dword ptr [esp + 4], xmm7
57171: movss dword ptr [esp], xmm6
57176: call 0x96cd0
5717b: jmp 0x571bb
5717d: mov eax, dword ptr [esi + esi*2 + 0xbef364]
57184: mov ecx, dword ptr [esi + esi*2 + 0xbef35c]
5718b: mov edx, dword ptr [esi + esi*2 + 0xbef354]
57192: mov dword ptr [esp + 0xc], eax
57196: mov dword ptr [esp + 8], ecx
5719a: movaps xmm0, xmmword ptr [esp + 0x60]
5719f: movss dword ptr [esp + 4], xmm0
571a5: mov dword ptr [esp], edx
571a8: mov ecx, dword ptr [esp + 0x140]
571af: lea edx, [esp + 0x190]
571b6: call 0x126100
571bb: mov eax, dword ptr [esp + 0xa0]
571c2: inc eax
571c3: mov dword ptr [esp + 0xa0], eax
571ca: cmp eax, dword ptr [esp + 0xd0]
571d1: jae 0x571e1
571d3: cmp dword ptr [esp + 0x100], 8
571db: jb 0x56559
571e1: call 0x87450
571e6: cmp dword ptr [0xbe30b0], 0
571ed: jle 0x57310
571f3: cmp dword ptr [0xbec5e8], 0x2c
571fa: jne 0x57310
57200: cmp dword ptr [0xbe30c4], 0x32
57207: jl 0x57310
5720d: movzx eax, byte ptr [0xbe5400]
57214: or al, byte ptr [0xbec77c]
5721a: je 0x57310
57220: mov ebx, 0xfffffff8
57225: lea eax, [ebx + 0xc]
57228: xorps xmm1, xmm1
5722b: cvtsi2ss xmm1, eax
5722f: subss xmm1, dword ptr [esp + 0x290]
57238: divss xmm1, dword ptr [0x74a920]; 0.8500000238418579
57240: mulss xmm1, xmm1
57244: xorps xmm0, xmm0
57247: movss xmm2, dword ptr [0x74a98c]; 19600.0
5724f: ucomiss xmm2, xmm1
57252: jbe 0x5727a
57254: movss xmm0, dword ptr [0x74a98c]; 19600.0
5725c: subss xmm0, xmm1
57260: movss dword ptr [esp], xmm0
57265: call 0x137820
5726a: fstp dword ptr [esp + 0x88c]
57271: movss xmm0, dword ptr [esp + 0x88c]
5727a: add ebx, 8
5727d: movss xmm2, dword ptr [esp + 0x6c0]
57286: movaps xmm1, xmm2
57289: subss xmm1, xmm0
5728d: cvttss2si eax, xmm1
57291: addss xmm0, xmm2
57295: cvttss2si esi, xmm0
57299: test esi, esi
5729b: mov edi, 0
572a0: cmovg edi, esi
572a3: cmp edi, 0x280
572a9: mov ecx, 0x280
572ae: cmovae edi, ecx
572b1: test eax, eax
572b3: jle 0x572d9
572b5: cmp eax, 0x280
572ba: cmovae eax, ecx
572bd: mov dword ptr [esp], eax
572c0: mov dword ptr [esp + 8], 0xff000000
572c8: mov dword ptr [esp + 4], 8
572d0: xor ecx, ecx
572d2: mov edx, ebx
572d4: call 0x837d0
572d9: cmp esi, 0x27f
572df: jg 0x57304
572e1: mov eax, 0x280
572e6: sub eax, edi
572e8: mov dword ptr [esp], eax
572eb: mov dword ptr [esp + 8], 0xff000000
572f3: mov dword ptr [esp + 4], 8
572fb: mov ecx, edi
572fd: mov edx, ebx
572ff: call 0x837d0
57304: cmp ebx, 0x1d8
5730a: jb 0x57225
57310: cmp dword ptr [esp + 0x8c], 0
57318: je 0x5733e
5731a: cmp dword ptr [esp + 0x130], 3
57322: sete al
57325: mov dword ptr [esp + 0x40], eax
57329: mov dword ptr [esp + 0x60], 0
57331: mov dword ptr [esp + 0x50], 0
57339: jmp 0x57d4d
5733e: cmp dword ptr [0xbda9d8], 0
57345: je 0x5776e
5734b: cmp dword ptr [0xe42610], 0
57352: je 0x57449
57358: cmp dword ptr [0xd395fc], 0
5735f: je 0x5776e
57365: cmp dword ptr [0xbda104], 0
5736c: js 0x5776e
57372: call 0xc9a70
57377: cmp eax, 1
5737a: jne 0x5776e
57380: cmp dword ptr [0xd42a2c], 0
57387: je 0x575f8
5738d: mov ecx, dword ptr [0xd42a28]
57393: lea edx, [esp + 0x1670]
5739a: call 0x919b0
5739f: mov dword ptr [esp + 0x40], 0
573a7: cmp eax, 1
573aa: jne 0x573dc
573ac: mov eax, dword ptr [esp + 0x1670]
573b3: cmp eax, dword ptr [0xd42a3c]
573b9: jne 0x573dc
573bb: mov eax, dword ptr [esp + 0x1684]
573c2: cmp eax, dword ptr [0xd42a34]
573c8: jae 0x573dc
573ca: mov ecx, dword ptr [0xd42a2c]
573d0: shl eax, 5
573d3: movzx eax, byte ptr [ecx + eax + 0x2c]
573d8: mov dword ptr [esp + 0x40], eax
573dc: cmp dword ptr [0xd42a2c], 0
573e3: je 0x57600
573e9: mov ecx, dword ptr [0xd42a28]
573ef: lea edx, [esp + 0x1670]
573f6: call 0x919b0
573fb: mov ebx, 0xbd8d09
57400: cmp eax, 1
57403: jne 0x57605
57409: mov eax, dword ptr [esp + 0x1670]
57410: cmp eax, dword ptr [0xd42a3c]
57416: jne 0x57605
5741c: mov eax, dword ptr [esp + 0x1684]
57423: cmp eax, dword ptr [0xd42a34]
57429: jae 0x57605
5742f: mov ecx, dword ptr [0xd42a2c]
57435: mov ebx, dword ptr [0xd42a38]
5743b: add ebx, ecx
5743d: shl eax, 5
57440: add ebx, dword ptr [ecx + eax + 0x14]
57444: jmp 0x57605
57449: cmp dword ptr [0xbdaa2c], 0
57450: js 0x5776e
57456: cmp dword ptr [0xe42614], 0
5745d: je 0x5776e
57463: cmp byte ptr [0xd2f7c8], 0
5746a: je 0x5776e
57470: call 0x1169e0
57475: cmp eax, dword ptr [0xbdaa2c]
5747b: jne 0x5776e
57481: cmp eax, 0x105
57486: ja 0x5776e
5748c: mov ecx, dword ptr [0xd2f848]
57492: cmp ecx, 4
57495: ja 0x5776e
5749b: shl eax, 3
5749e: mov edx, dword ptr [eax + eax*2 + 0x6e6924]
574a5: mov dword ptr [esp + 0x1180], edx
574ac: mov dword ptr [esp + 0x1184], 0
574b7: fild qword ptr [esp + 0x1180]
574be: fstp dword ptr [esp + 0x888]
574c5: movss xmm0, dword ptr [esp + 0x888]
574ce: movss dword ptr [esp + 0x60], xmm0
574d4: mov eax, dword ptr [eax + eax*2 + 0x6e6928]
574db: mov dword ptr [esp + 0x1178], eax
574e2: mov dword ptr [esp + 0x117c], 0
574ed: fild qword ptr [esp + 0x1178]
574f4: fstp dword ptr [esp + 0x884]
574fb: movss xmm0, dword ptr [esp + 0x884]
57504: movss dword ptr [esp + 0x40], xmm0
5750a: test ecx, ecx
5750c: je 0x57652
57512: cmp ecx, 2
57515: movss xmm0, dword ptr [0x74a62c]; 640.0
5751d: subss xmm0, dword ptr [esp + 0x60]
57523: movss dword ptr [esp + 0x50], xmm0
57529: je 0x5765b
5752f: movss xmm0, dword ptr [0x74a2fc]; 480.0
57537: subss xmm0, dword ptr [esp + 0x40]
5753d: movaps xmm1, xmm0
57540: mulss xmm1, dword ptr [0x74a044]; 0.5
57548: cmp ecx, 3
5754b: movss dword ptr [esp + 0xb0], xmm1
57554: movss dword ptr [esp + 0x70], xmm1
5755a: jae 0x57562
5755c: movss dword ptr [esp + 0x70], xmm0
57562: movss xmm0, dword ptr [esp + 0x50]
57568: mulss xmm0, dword ptr [0x74a044]; 0.5
57570: movss dword ptr [esp + 0x50], xmm0
57576: jne 0x5766f
5757c: mov ecx, dword ptr [0xd4769c]
57582: mov dword ptr [esp + 0xc], 1
5758a: mov dword ptr [esp + 8], 0x1122a
57592: mov dword ptr [esp + 4], 0x800
5759a: mov dword ptr [esp], 0x800
575a1: mov edx, 0x200
575a6: call 0x97c60
575ab: cvttss2si eax, dword ptr [esp + 0x40]
575b1: add eax, 0x16
575b4: cvttss2si esi, dword ptr [esp + 0x60]
575ba: add esi, 4
575bd: cvttss2si edx, dword ptr [esp + 0xb0]
575c6: add edx, -0x14
575c9: cvttss2si ecx, dword ptr [esp + 0x50]
575cf: add ecx, -2
575d2: mov dword ptr [esp + 4], eax
575d6: mov dword ptr [esp], esi
575d9: mov dword ptr [esp + 0x10], 0xffffffff
575e1: mov dword ptr [esp + 0xc], 0
575e9: mov dword ptr [esp + 8], 0xbd8d09
575f1: call 0x95c50
575f6: jmp 0x5766f
575f8: mov dword ptr [esp + 0x40], 0
57600: mov ebx, 0xbd8d09
57605: mov dword ptr [esp + 0x50], 0xffffffff
5760d: xor esi, esi
5760f: mov edi, 0xfffff790
57614: mov eax, dword ptr [edi + 0x6e8a14]
5761a: mov dword ptr [esp + 4], eax
5761e: mov dword ptr [esp], ebx
57621: call 0x1378a0
57626: test eax, eax
57628: jne 0x57647
5762a: mov eax, dword ptr [edi + 0x6e8a18]
57630: cmp eax, dword ptr [esp + 0x40]
57634: je 0x576eb
5763a: test eax, eax
5763c: mov eax, dword ptr [esp + 0x50]
57640: cmove eax, esi
57643: mov dword ptr [esp + 0x50], eax
57647: inc esi
57648: add edi, 0x18
5764b: jne 0x57614
5764d: jmp 0x576ef
57652: xorps xmm0, xmm0
57655: movss dword ptr [esp + 0x50], xmm0
5765b: movss xmm0, dword ptr [0x74a2fc]; 480.0
57663: subss xmm0, dword ptr [esp + 0x40]
57669: movss dword ptr [esp + 0x70], xmm0
5766f: mov ecx, dword ptr [0xe42614]
57675: mov dword ptr [esp + 0xc], 1
5767d: mov dword ptr [esp + 8], 0x1122a
57685: mov dword ptr [esp + 4], 0x800
5768d: mov dword ptr [esp], 0x200
57694: mov edx, 0x200
57699: call 0x97c60
5769e: movss xmm1, dword ptr [esp + 0x40]
576a4: movss dword ptr [esp + 0x1c], xmm1
576aa: movss xmm0, dword ptr [esp + 0x60]
576b0: movss dword ptr [esp + 0x18], xmm0
576b6: movss dword ptr [esp + 0xc], xmm1
576bc: movss dword ptr [esp + 8], xmm0
576c2: movss xmm0, dword ptr [esp + 0x70]
576c8: movss dword ptr [esp + 4], xmm0
576ce: movss xmm0, dword ptr [esp + 0x50]
576d4: movss dword ptr [esp], xmm0
576d9: mov dword ptr [esp + 0x14], 0
576e1: mov dword ptr [esp + 0x10], 0
576e9: jmp 0x57769
576eb: mov dword ptr [esp + 0x50], esi
576ef: mov eax, dword ptr [esp + 0x50]
576f3: cmp eax, dword ptr [0xbda104]
576f9: jne 0x5776e
576fb: mov ecx, dword ptr [0xd395fc]
57701: mov dword ptr [esp + 0xc], 1
57709: mov dword ptr [esp + 8], 0x1122a
57711: mov dword ptr [esp + 4], 0x400
57719: mov dword ptr [esp], 0x100
57720: mov edx, 0x100
57725: call 0x97c60
5772a: mov dword ptr [esp + 0x1c], 0x43800000
57732: mov dword ptr [esp + 0x18], 0x43800000
5773a: mov dword ptr [esp + 0x14], 0
57742: mov dword ptr [esp + 0x10], 0
5774a: mov dword ptr [esp + 0xc], 0x43800000
57752: mov dword ptr [esp + 8], 0x43800000
5775a: mov dword ptr [esp + 4], 0x43480000
57762: mov dword ptr [esp], 0x41000000
57769: call 0x96cd0
5776e: mov dword ptr [esp + 0x60], 0
57776: cmp dword ptr [esp + 0x130], 3
5777e: mov dword ptr [esp + 0x40], 0
57786: mov dword ptr [esp + 0x50], 0
5778e: jne 0x57d4d
57794: mov eax, dword ptr [0xd2f494]
57799: mov byte ptr [esp + 0xa0], 1
577a1: mov dword ptr [esp + 0x50], 0
577a9: test eax, eax
577ab: js 0x57a36
577b1: imul esi, eax, 0x14498
577b7: mov eax, dword ptr [esi + 0xc6faf0]
577bd: lea ecx, [eax - 0x27c6]
577c3: cmp ecx, 0xffffd83b
577c9: jb 0x57a36
577cf: imul eax, eax, 0x3c
577d2: mov edi, dword ptr [eax + 0x1c4544]
577d8: test edi, edi
577da: je 0x57a36
577e0: mov dword ptr [esp], edi
577e3: mov dword ptr [esp + 4], 0xafc9d1
577eb: call 0x1378a0
577f0: test eax, eax
577f2: je 0x578c8
577f8: mov dword ptr [esp], edi
577fb: mov dword ptr [esp + 4], 0xa21680
57803: call 0x1378a0
57808: test eax, eax
5780a: je 0x578c8
57810: mov dword ptr [esp], edi
57813: mov dword ptr [esp + 4], 0xa21672
5781b: call 0x1378a0
57820: test eax, eax
57822: je 0x578c8
57828: mov dword ptr [esp], edi
5782b: mov dword ptr [esp + 4], 0xa2168f
57833: call 0x1378a0
57838: test eax, eax
5783a: je 0x578c8
57840: mov dword ptr [esp], edi
57843: mov dword ptr [esp + 4], 0xa458da
5784b: call 0x1378a0
