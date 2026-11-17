126100: push ebp
126101: push ebx
126102: push edi
126103: push esi
126104: sub esp, 0x5c
126107: movss xmm2, dword ptr [esp + 0x74]
12610d: divss xmm2, dword ptr [0x74a44c]; 1.5
126115: xorps xmm0, xmm0
126118: ucomiss xmm0, xmm2
12611b: ja 0x1265a6
126121: ucomiss xmm2, dword ptr [0x749e28]
126128: ja 0x1265a6
12612e: mov edi, edx
126130: mov esi, ecx
126132: movss xmm0, dword ptr [ecx]
126136: movss xmm1, dword ptr [ecx + 4]
12613b: movss xmm3, dword ptr [0x74a3b8]; 32.0
126143: mulss xmm3, xmm2
126147: addss xmm3, xmm0
12614b: movss dword ptr [esp + 0x24], xmm3
126151: movss xmm3, dword ptr [0x74ae9c]; -32.0
126159: movups xmmword ptr [esp + 0x3c], xmm2
12615e: mulss xmm3, xmm2
126162: addss xmm3, xmm1
126166: movss dword ptr [esp + 0x28], xmm3
12616c: movss xmm2, dword ptr [0x74a3d4]; 0.0625
126174: movaps xmm3, xmm0
126177: mulss xmm3, xmm2
12617b: cvttss2si ecx, xmm3
12617f: mulss xmm2, xmm1
126183: cvttss2si eax, xmm2
126187: xor ebx, ebx
126189: test ecx, ecx
12618b: cmovle ecx, ebx
12618e: test eax, eax
126190: cmovg ebx, eax
126193: mov edx, dword ptr [0xd48034]
126199: lea eax, [edx - 1]
12619c: cmp ecx, edx
12619e: cmovl eax, ecx
1261a1: mov ebp, dword ptr [0xd48038]
1261a7: lea ecx, [ebp - 1]
1261aa: cmp ebx, ebp
1261ac: cmovl ecx, ebx
1261af: cvtsi2ss xmm4, eax
1261b3: subss xmm3, xmm4
1261b7: xorps xmm4, xmm4
1261ba: cvtsi2ss xmm4, ecx
1261be: subss xmm2, xmm4
1261c2: mov ebx, dword ptr [0xd48044]
1261c8: imul ecx, edx
1261cb: add ecx, eax
1261cd: lea ebp, [ecx*4]
1261d4: shl ecx, 4
1261d7: ucomiss xmm3, xmm2
1261da: movss xmm5, dword ptr [ebx + ecx]
1261df: mov eax, dword ptr [0xd2fbac]
1261e4: mov edx, dword ptr [0xd2fbb0]
1261ea: mov ecx, dword ptr [0xd48010]
1261f0: jbe 0x126210
1261f2: movss xmm6, dword ptr [ebx + ebp*4 + 4]
1261f8: movss xmm4, dword ptr [ebx + ebp*4 + 0xc]
1261fe: subss xmm4, xmm6
126202: subss xmm6, xmm5
126206: mulss xmm6, xmm3
12620a: addss xmm6, xmm5
12620e: jmp 0x12622c
126210: movss xmm4, dword ptr [ebx + ebp*4 + 8]
126216: movss xmm6, dword ptr [ebx + ebp*4 + 0xc]
12621c: subss xmm6, xmm4
126220: mulss xmm6, xmm3
126224: addss xmm6, xmm5
126228: subss xmm4, xmm5
12622c: mulss xmm4, xmm2
126230: addss xmm4, xmm6
126234: mov ebx, dword ptr [esp + 0x78]
126238: movss dword ptr [esp + 0xc], xmm4
12623e: movss dword ptr [esp + 8], xmm1
126244: movss dword ptr [esp + 4], xmm0
12624a: mov dword ptr [esp], eax
12624d: call 0x115530
126252: fstp dword ptr [esp + 0x38]
126256: movss xmm0, dword ptr [esp + 0x38]
12625c: addss xmm0, dword ptr [0x74a438]
126264: movss dword ptr [esp + 0x20], xmm0
12626a: movss xmm0, dword ptr [0x74b054]; 4.71238899230957
126272: mulss xmm0, dword ptr [esp + 0x3c]
126278: movss dword ptr [esp], xmm0
12627d: call 0x1377c0
126282: fstp dword ptr [esp + 0x34]
126286: movss xmm2, dword ptr [esp + 0x34]
12628c: mulss xmm2, dword ptr [0x74a3bc]; 40.0
126294: addss xmm2, dword ptr [esp + 0x20]
12629a: movss xmm0, dword ptr [edi + 4]
12629f: movss xmm4, dword ptr [esp + 0x28]
1262a5: mulss xmm0, xmm4
1262a9: movss xmm1, dword ptr [edi]
1262ad: movss xmm3, dword ptr [esp + 0x24]
1262b3: mulss xmm1, xmm3
1262b7: addss xmm1, xmm0
1262bb: movss xmm0, dword ptr [edi + 8]
1262c0: mulss xmm0, xmm2
1262c4: addss xmm0, xmm1
1262c8: addss xmm0, dword ptr [edi + 0xc]
1262cd: movss dword ptr [esp + 0x20], xmm0
1262d3: mulss xmm4, dword ptr [edi + 0x14]
1262d8: mulss xmm3, dword ptr [edi + 0x10]
1262dd: addss xmm3, xmm4
1262e1: mulss xmm2, dword ptr [edi + 0x18]
1262e6: addss xmm2, xmm3
1262ea: addss xmm2, dword ptr [edi + 0x1c]
1262ef: movss dword ptr [esp + 0x24], xmm2
1262f5: movss xmm0, dword ptr [0x749e28]; 1.0
1262fd: subss xmm0, dword ptr [esp + 0x3c]
126303: mulss xmm0, dword ptr [0x74a44c]; 1.5
12630b: movss dword ptr [esp + 4], xmm0
126311: mov dword ptr [esp], 0x3e99999a
126318: call 0x136bf0
12631d: fstp dword ptr [esp + 0x30]
126321: movss xmm4, dword ptr [esp + 0x30]
126327: movups xmm0, xmmword ptr [esp + 0x3c]
12632c: mulss xmm0, dword ptr [0x74a314]; 6.0
126334: cvttss2si eax, xmm0
126338: mov ecx, eax
12633a: sar ecx, 0x1f
12633d: subss xmm0, dword ptr [0x74a300]
126345: cvttss2si edx, xmm0
126349: and edx, ecx
12634b: or edx, eax
12634d: cmp edx, 5
126350: mov edi, 5
126355: cmovb edi, edx
126358: cmp dword ptr [esi + 0x2c], 0
12635c: je 0x1263f2
126362: mov eax, dword ptr [esi + 0x24]
126365: test eax, eax
126367: je 0x1263f2
12636d: imul eax, eax, 0x83
126373: imul ecx, dword ptr [esi + 0x28], 0x1eef
12637a: add ecx, eax
12637c: mov eax, ecx
12637e: shr eax, 0x10
126381: xor eax, ecx
126383: imul ecx, eax, 0x7feb352d
126389: mov eax, ecx
12638b: shr eax, 0xf
12638e: xor eax, ecx
126390: movzx ecx, al
126393: xorps xmm0, xmm0
126396: cvtsi2ss xmm0, ecx
12639a: movss xmm1, dword ptr [0x74a64c]; 255.0
1263a2: divss xmm0, xmm1
1263a6: movss xmm2, dword ptr [0x74a6d8]; -0.5
1263ae: addss xmm0, xmm2
1263b2: mulss xmm0, dword ptr [0x74a438]; 16.0
1263ba: mulss xmm0, xmm4
1263be: movss xmm3, dword ptr [esp + 0x20]
1263c4: addss xmm3, xmm0
1263c8: movzx eax, ah
1263cb: xorps xmm0, xmm0
1263ce: cvtsi2ss xmm0, eax
1263d2: divss xmm0, xmm1
1263d6: addss xmm0, xmm2
1263da: mulss xmm0, dword ptr [0x74a344]; 10.0
1263e2: mulss xmm0, xmm4
1263e6: movss xmm1, dword ptr [esp + 0x24]
1263ec: addss xmm1, xmm0
1263f0: jmp 0x1263fe
1263f2: movss xmm1, dword ptr [esp + 0x24]
1263f8: movss xmm3, dword ptr [esp + 0x20]
1263fe: mov esi, dword ptr [esp + 0x70]
126402: test ebx, ebx
126404: je 0x126586
12640a: movss dword ptr [esp + 0x28], xmm4
126410: movss dword ptr [esp + 0x20], xmm3
126416: movss dword ptr [esp + 0x24], xmm1
12641c: mov dword ptr [esp + 0xc], esi
126420: lea eax, [esp + 0x4c]
126424: mov dword ptr [esp], eax
126427: mov dword ptr [esp + 8], 0xac85a7
12642f: mov dword ptr [esp + 4], 0x10
126437: call 0x1377e0
12643c: movzx ecx, byte ptr [esp + 0x4c]
126441: xorps xmm0, xmm0
126444: test cl, cl
126446: xorps xmm1, xmm1
126449: je 0x126476
12644b: lea eax, [esp + 0x4d]
12644f: nop 
126450: movsx ecx, cl
126453: lea ecx, [ecx + ecx*2]
126456: shl ecx, 4
126459: movzx ecx, word ptr [ecx + 0x74563c]
126460: add ecx, 2
126463: xorps xmm2, xmm2
126466: cvtsi2ss xmm2, ecx
12646a: addss xmm1, xmm2
12646e: movzx ecx, byte ptr [eax]
126471: inc eax
126472: test cl, cl
126474: jne 0x126450
126476: cmpltss xmm0, xmm1
12647b: addss xmm1, dword ptr [0x74a6b8]
126483: movss xmm2, dword ptr [0x74a48c]; 12.0
12648b: addss xmm1, xmm2
12648f: andps xmm1, xmm0
126492: andnps xmm0, xmm2
126495: orps xmm0, xmm1
126498: movss dword ptr [esp + 4], xmm0
12649e: mov dword ptr [esp], 0x42280000
1264a5: call 0x136bf0
1264aa: fstp dword ptr [esp + 0x2c]
1264ae: movss xmm3, dword ptr [esp + 0x2c]
1264b4: movss xmm2, dword ptr [esp + 0x28]
1264ba: mulss xmm3, xmm2
1264be: movss xmm1, dword ptr [0x74a484]; 36.0
1264c6: mulss xmm1, xmm2
1264ca: movzx eax, word ptr [edi*8 + 0x74677e]
