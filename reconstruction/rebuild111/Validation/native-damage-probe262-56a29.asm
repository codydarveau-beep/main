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
56b22: subss xmm1, dword ptr [0x74a300]
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
