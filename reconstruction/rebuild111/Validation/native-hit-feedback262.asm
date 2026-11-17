FUNCTION 0xa41b0
a41b0: push ebp
a41b1: push ebx
a41b2: push edi
a41b3: push esi
a41b4: mov eax, dword ptr [esp + 0x14]
a41b8: test eax, eax
a41ba: jle 0xa4259
a41c0: mov esi, dword ptr [esp + 0x1c]
a41c4: mov ebx, dword ptr [esp + 0x18]
a41c8: xorps xmm0, xmm0
a41cb: movlps xmm0, qword ptr [edx + 0x190]
a41d2: mov edi, dword ptr [ecx + 0x11064]
a41d8: lea ebp, [edi + 1]
a41db: mov dword ptr [ecx + 0x11064], ebp
a41e1: and edi, 0xf
a41e4: lea edi, [edi + edi*2]
a41e7: shl edi, 4
a41ea: lea edi, [ecx + edi + 0x10d64]
a41f1: movss xmm1, dword ptr [ecx + 0x4ab8]
a41f9: test ebx, ebx
a41fb: jle 0xa4210
a41fd: mov ebp, 0xa
a4202: cmp ebx, 0xa
a4205: ja 0xa4215
a4207: cmp ebx, eax
a4209: cmovge ebx, eax
a420c: mov ebp, ebx
a420e: jmp 0xa4215
a4210: mov ebp, 1
a4215: movlps qword ptr [edi], xmm0
a4218: movss dword ptr [edi + 8], xmm1
a421d: mov dword ptr [edi + 0xc], 0x3e4ccccd
a4224: mov dword ptr [edi + 0x10], eax
a4227: mov dword ptr [edi + 0x14], ebp
a422a: mov dword ptr [edi + 0x18], esi
a422d: mov dword ptr [edi + 0x1c], 0
a4234: mov dword ptr [edi + 0x20], 0
a423b: mov dword ptr [edi + 0x24], 0
a4242: mov dword ptr [edi + 0x28], 0
a4249: mov dword ptr [edi + 0x2c], 0
a4250: push edi
a4251: call 0xa5b10
a4256: add esp, 4
a4259: pop esi
a425a: pop edi
a425b: pop ebx
a425c: pop ebp
a425d: ret 
FUNCTION 0xa3e30
a3e30: cmp edx, 0xa
a3e33: mov eax, 0xa
a3e38: cmovl eax, edx
a3e3b: test edx, edx
a3e3d: jle 0xa3f14
a3e43: push ebp
a3e44: push ebx
a3e45: push edi
a3e46: push esi
a3e47: sub esp, 0xc
a3e4a: mov edx, dword ptr [ecx + 0x478d4]
a3e50: mov esi, dword ptr [ecx + 0x478d8]
a3e56: xor edi, edi
a3e58: movss xmm0, dword ptr [0x74a4ac]; 0.20000000298023224
a3e60: movss xmm1, dword ptr [0x74a330]; 0.019999999552965164
a3e68: mov dword ptr [esp + 4], eax
a3e6c: mov dword ptr [esp], edx
a3e6f: jmp 0xa3ea3
a3e71: mov ebx, ebp
a3e73: mov eax, dword ptr [esp + 4]
a3e77: mov edx, dword ptr [esp]
a3e7a: mov esi, dword ptr [esp + 8]
a3e7e: add ebx, edx
a3e80: and ebx, 0x1f
a3e83: mov dword ptr [ecx + ebx*4 + 0x47854], 0
a3e8e: movss dword ptr [ecx + ebx*4 + 0x478dc], xmm2
a3e97: inc esi
a3e98: mov dword ptr [ecx + 0x478d8], esi
a3e9e: inc edi
a3e9f: cmp edi, eax
a3ea1: je 0xa3f0d
a3ea3: mov ebp, esi
a3ea5: sub ebp, edx
a3ea7: cmp ebp, 0x1f
a3eaa: ja 0xa3e9e
a3eac: xorps xmm2, xmm2
a3eaf: cvtsi2ss xmm2, edi
a3eb3: mulss xmm2, xmm0
a3eb7: addss xmm2, xmm1
a3ebb: addss xmm2, dword ptr [ecx + 0x4ab8]
a3ec3: xor ebx, ebx
a3ec5: test ebp, ebp
a3ec7: je 0xa3e7e
a3ec9: mov dword ptr [esp + 8], esi
a3ecd: nop dword ptr [eax]
a3ed0: lea eax, [esi - 1]
a3ed3: mov edx, eax
a3ed5: and edx, 0x1f
a3ed8: movss xmm3, dword ptr [ecx + edx*4 + 0x478dc]
a3ee1: ucomiss xmm3, xmm2
a3ee4: jbe 0xa3e71
a3ee6: mov edx, dword ptr [ecx + edx*4 + 0x47854]
a3eed: shl esi, 2
a3ef0: and esi, 0x7c
a3ef3: mov dword ptr [ecx + esi + 0x47854], edx
a3efa: movss dword ptr [ecx + esi + 0x478dc], xmm3
a3f03: dec ebp
a3f04: mov esi, eax
a3f06: jne 0xa3ed0
a3f08: jmp 0xa3e73
a3f0d: add esp, 0xc
a3f10: pop esi
a3f11: pop edi
a3f12: pop ebx
a3f13: pop ebp
a3f14: ret 
