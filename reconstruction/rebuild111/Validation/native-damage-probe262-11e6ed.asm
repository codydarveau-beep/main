11e689: cvttss2si ecx, xmm1
11e68d: mov edx, ecx
11e68f: sar edx, 0x1f
11e692: subss xmm1, dword ptr [0x74a300]
11e69a: cvttss2si eax, xmm1
11e69e: and eax, edx
11e6a0: or eax, ecx
11e6a2: mov dword ptr [esp + 0x10c], esi
11e6a9: cmp eax, esi
11e6ab: jbe 0x11e5c0
11e6b1: mov esi, dword ptr [ebx + 0xc]
11e6b4: test esi, esi
11e6b6: je 0x11e5c0
11e6bc: movss xmm0, dword ptr [ebx + 0x6c]
11e6c1: movss dword ptr [esp + 0x20], xmm0
11e6c7: movss dword ptr [esp], xmm0
11e6cc: call 0x132b30
11e6d1: movss xmm0, dword ptr [esp + 0x20]
11e6d7: test eax, 0x100
11e6dc: je 0x11e6e6
11e6de: movss xmm0, dword ptr [0x74a288]; 1000.0
11e6e6: imul eax, dword ptr [esp + 0x10c], 0x1eef
11e6f1: add eax, dword ptr [esp + 0x198]
11e6f8: mov ecx, eax
11e6fa: shr ecx, 0x10
11e6fd: xor ecx, eax
11e6ff: imul eax, ecx, 0x7feb352d
11e705: mov ecx, eax
11e707: shr ecx, 0xf
11e70a: xor ecx, eax
11e70c: imul eax, ecx, 0x846ca68b
11e712: mov ecx, eax
11e714: shr ecx, 0x10
11e717: xor ecx, eax
11e719: movss dword ptr [esp + 4], xmm0
11e71f: mov dword ptr [esp + 0xd0], ecx
11e726: mov dword ptr [esp + 8], ecx
11e72a: mov dword ptr [esp + 0xc], 1
11e732: mov dword ptr [esp], 0x16
11e739: mov ecx, ebx
11e73b: mov edx, 0x17
11e740: call 0x124e40
11e745: fstp dword ptr [esp + 0x290]
11e74c: movss xmm1, dword ptr [esp + 0x290]
11e755: movss xmm0, dword ptr [0x749e28]; 1.0
11e75d: ucomiss xmm0, xmm1
11e760: ja 0x11e5c0
11e766: movss dword ptr [esp + 0x60], xmm1
11e76c: movss xmm0, dword ptr [ebx + 0x64]
11e771: movss dword ptr [esp + 0x20], xmm0
11e777: movss dword ptr [esp], xmm0
11e77c: call 0x132b30
11e781: movss xmm0, dword ptr [esp + 0x20]
11e787: test eax, 0x100
11e78c: je 0x11e791
11e78e: xorps xmm0, xmm0
11e791: movss dword ptr [esp + 4], xmm0
11e797: mov dword ptr [esp], 0
11e79e: call 0x136bf0
11e7a3: fstp dword ptr [esp + 0x288]
11e7aa: mov eax, dword ptr [esp + 0x10c]
11e7b1: mov dword ptr [esp + 0x2c8], eax
11e7b8: mov dword ptr [esp + 0x2cc], 0
11e7c3: fild qword ptr [esp + 0x2c8]
11e7ca: fstp dword ptr [esp + 0x28c]
11e7d1: movss xmm0, dword ptr [esp + 0x28c]
11e7da: movss dword ptr [esp + 0xc0], xmm0
11e7e3: movss xmm0, dword ptr [ebx + 0x1bc]
11e7eb: movss dword ptr [esp + 0x20], xmm0
11e7f1: movss dword ptr [esp], xmm0
11e7f6: call 0x132b30
11e7fb: movss xmm0, dword ptr [esp + 0x20]
11e801: test eax, 0x100
11e806: je 0x11e810
11e808: movss xmm0, dword ptr [0x74a87c]; 200.0
11e810: movss dword ptr [esp + 4], xmm0
11e816: mov dword ptr [esp], 0
11e81d: call 0x136bf0
11e822: fstp dword ptr [esp + 0x284]
11e829: movss xmm0, dword ptr [esp + 0x284]
11e832: mulss xmm0, dword ptr [esp + 0xc0]
11e83b: addss xmm0, dword ptr [esp + 0x288]
