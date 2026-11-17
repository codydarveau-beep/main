ce1e0: push ebp
ce1e1: push ebx
ce1e2: push edi
ce1e3: push esi
ce1e4: sub esp, 0x10
ce1e7: cmp ecx, 0x14f
ce1ed: jbe 0xce1f7
ce1ef: add esp, 0x10
ce1f2: pop esi
ce1f3: pop edi
ce1f4: pop ebx
ce1f5: pop ebp
ce1f6: ret 
ce1f7: mov esi, dword ptr [esp + 0x28]
ce1fb: mov eax, dword ptr [esp + 0x24]
ce1ff: mov dword ptr [esp], eax
ce202: imul edi, ecx, 0x298
ce208: mov ebp, dword ptr [edi + 0xbef888]
ce20e: cmp ebp, 0x28f
ce214: ja 0xce22c
ce216: mov eax, ebp
ce218: shl eax, 6
ce21b: mov ebx, 0xfffff93d
ce220: add ebx, dword ptr [eax + ebp*4 + 0x25979c]
ce227: cmp ebx, -7
ce22a: ja 0xce1ef
ce22c: test edx, edx
ce22e: jle 0xce1ef
ce230: cmp dword ptr [edi + 0xbef88c], 0
ce237: jle 0xce1ef
ce239: mov eax, dword ptr [0xbed320]
ce23e: cmp eax, 2
ce241: jne 0xce264
ce243: mov eax, 0xffffe000
ce248: nop dword ptr [eax + eax]
ce250: cmp dword ptr [eax + 0xbef344], 0
ce257: je 0xce32a
ce25d: add eax, 0x40
ce260: jne 0xce250
ce262: jmp 0xce1ef
ce264: cmp esi, 2
ce267: jl 0xce2eb
ce26d: mov ebx, ebp
ce26f: shl ebx, 6
ce272: test byte ptr [ebx + ebp*4 + 0x2597a0], 0x10
ce27a: jne 0xce2eb
ce27c: lea ebx, [edi + 0xbef648]
ce282: cmp esi, 0x19
ce285: mov ebp, 0x19
ce28a: cmovl ebp, esi
ce28d: cmp ebp, edx
ce28f: cmovae ebp, edx
ce292: mov esi, 0xffffe000
ce297: nop word ptr [eax + eax]
ce2a0: cmp dword ptr [esi + 0xbef344], 0
ce2a7: je 0xce4bd
ce2ad: add esi, 0x40
ce2b0: jne 0xce2a0
ce2b2: movss xmm0, dword ptr [edi + 0xbef6f8]
ce2ba: ucomiss xmm0, dword ptr [0xbe3098]
ce2c1: jbe 0xce5b9
ce2c7: mov eax, ecx
ce2c9: lea ecx, [edi + 0xbef6f8]
ce2cf: mov dword ptr [ecx], 0
ce2d5: lea ecx, [edx + edx]
ce2d8: cmp edx, 0x3b9aca01
ce2de: mov esi, 0x77359400
ce2e3: cmovb esi, ecx
ce2e6: jmp 0xce5bd
ce2eb: lea esi, [edi + 0xbef88c]
ce2f1: movss xmm0, dword ptr [edi + 0xbef6f8]
ce2f9: ucomiss xmm0, dword ptr [0xbe3098]
ce300: jbe 0xce406
ce306: mov eax, ecx
ce308: lea ecx, [edi + 0xbef6f8]
ce30e: mov dword ptr [ecx], 0
ce314: lea ecx, [edx + edx]
ce317: cmp edx, 0x3b9aca01
ce31d: mov ebp, 0x77359400
ce322: cmovb ebp, ecx
ce325: jmp 0xce40a
ce32a: movss xmm1, dword ptr [edi + 0xbef6f8]
ce332: movss xmm0, dword ptr [0xbe3098]; 0.0
ce33a: ucomiss xmm1, xmm0
ce33d: jbe 0xce35c
ce33f: lea esi, [edi + 0xbef6f8]
ce345: mov dword ptr [esi], 0
ce34b: lea esi, [edx + edx]
ce34e: cmp edx, 0x3b9aca01
ce354: mov edx, 0x77359400
ce359: cmovb edx, esi
ce35c: mov ebx, dword ptr [0xbed324]
ce362: mov esi, dword ptr [edi + 0xbef884]
ce368: mov edi, dword ptr [0xbec5ac]
ce36e: mov ebp, dword ptr [0xbec5e8]
ce374: mov dword ptr [eax + 0xbef344], 1
ce37e: mov dword ptr [eax + 0xbef348], ecx
ce384: mov dword ptr [eax + 0xbef34c], 1
ce38e: mov dword ptr [eax + 0xbef350], 0
ce398: mov dword ptr [eax + 0xbef354], edx
ce39e: mov dword ptr [eax + 0xbef358], 0
ce3a8: mov ecx, dword ptr [esp]
ce3ab: mov dword ptr [eax + 0xbef35c], ecx
ce3b1: mov dword ptr [eax + 0xbef360], 2
ce3bb: mov dword ptr [eax + 0xbef364], ebx
ce3c1: mov dword ptr [eax + 0xbef368], 0
ce3cb: mov dword ptr [eax + 0xbef36c], esi
ce3d1: mov dword ptr [eax + 0xbef370], edi
ce3d7: mov dword ptr [eax + 0xbef374], ebp
ce3dd: addss xmm0, dword ptr [0x74aed8]; 0.27000001072883606
ce3e5: mov dword ptr [eax + 0xbef378], 0
ce3ef: movss dword ptr [eax + 0xbef37c], xmm0
ce3f7: mov dword ptr [eax + 0xbef380], 0x3e4ccccd
ce401: jmp 0xce1ef
ce406: mov eax, ecx
ce408: mov ebp, edx
ce40a: mov ecx, 0xbde5e0
ce40f: mov edx, eax
ce411: push 1
ce413: push dword ptr [esp + 4]
ce417: push ebp
ce418: call 0xa8800
ce41d: add esp, 0xc
ce420: cmp dword ptr [esi], 0
ce423: jle 0xce1ef
ce429: lea eax, [edi + 0xbef888]
ce42f: mov eax, dword ptr [eax]
ce431: cmp eax, 0x28f
ce436: ja 0xce452
ce438: mov ecx, eax
ce43a: shl ecx, 6
ce43d: mov edx, 0xfffff93d
ce442: add edx, dword ptr [ecx + eax*4 + 0x25979c]
ce449: cmp edx, -7
ce44c: ja 0xce1ef
ce452: cmp dword ptr [edi + 0xbef86c], 0
ce459: je 0xce46f
ce45b: mov edx, dword ptr [edi + 0xbef880]
ce461: test edx, edx
ce463: je 0xce46f
ce465: xor ecx, ecx
ce467: cmp edx, 3
ce46a: sete cl
ce46d: jmp 0xce47a
ce46f: mov ecx, eax
ce471: shl ecx, 6
ce474: mov ecx, dword ptr [ecx + 0x2c0178]
ce47a: test ecx, ecx
ce47c: jne 0xce1ef
ce482: movzx eax, word ptr [eax + eax + 0x429f20]
ce48a: xorps xmm0, xmm0
ce48d: cvtsi2ss xmm0, eax
ce491: divss xmm0, dword ptr [0x74a288]; 1000.0
ce499: addss xmm0, dword ptr [0xbe3098]; 0.0
ce4a1: ucomiss xmm0, dword ptr [edi + 0xbef818]
ce4a8: jbe 0xce1ef
ce4ae: lea eax, [edi + 0xbef818]
ce4b4: movss dword ptr [eax], xmm0
ce4b8: jmp 0xce1ef
ce4bd: movss xmm1, dword ptr [edi + 0xbef6f8]
ce4c5: movss xmm0, dword ptr [0xbe3098]; 0.0
ce4cd: ucomiss xmm1, xmm0
ce4d0: jbe 0xce4ef
ce4d2: lea ebx, [edi + 0xbef6f8]
ce4d8: mov dword ptr [ebx], 0
ce4de: lea ebx, [edx + edx]
ce4e1: cmp edx, 0x3b9aca01
ce4e7: mov edx, 0x77359400
ce4ec: cmovb edx, ebx
ce4ef: mov edi, dword ptr [edi + 0xbef884]
ce4f5: mov dword ptr [esp + 8], edi
ce4f9: mov edi, dword ptr [0xbed324]
ce4ff: mov ebx, dword ptr [0xbe29f0]
ce505: mov dword ptr [esp + 4], ebx
ce509: mov ebx, dword ptr [0xbec5ac]
ce50f: mov dword ptr [esp + 0xc], ebx
ce513: mov ebx, dword ptr [0xbec5e8]
ce519: mov dword ptr [esi + 0xbef344], 1
ce523: mov dword ptr [esi + 0xbef348], ecx
ce529: mov dword ptr [esi + 0xbef34c], ebp
ce52f: mov dword ptr [esi + 0xbef350], 0
ce539: mov dword ptr [esi + 0xbef354], edx
ce53f: mov dword ptr [esi + 0xbef358], 0
ce549: mov ecx, dword ptr [esp]
ce54c: mov dword ptr [esi + 0xbef35c], ecx
ce552: xor ecx, ecx
ce554: cmp eax, 0x4e
ce557: mov dword ptr [esi + 0xbef360], eax
ce55d: mov dword ptr [esi + 0xbef364], edi
ce563: mov eax, dword ptr [esp + 4]
ce567: mov dword ptr [esi + 0xbef368], eax
ce56d: mov eax, dword ptr [esp + 8]
ce571: mov dword ptr [esi + 0xbef36c], eax
ce577: mov eax, dword ptr [esp + 0xc]
ce57b: mov dword ptr [esi + 0xbef370], eax
ce581: mov dword ptr [esi + 0xbef374], ebx
ce587: sete cl
ce58a: movss xmm1, dword ptr [ecx*4 + 0x74aed0]
ce593: mov dword ptr [esi + 0xbef378], 0
ce59d: movss dword ptr [esi + 0xbef37c], xmm0
ce5a5: movss dword ptr [esi + 0xbef380], xmm1
ce5ad: add esp, 0x10
ce5b0: pop esi
ce5b1: pop edi
ce5b2: pop ebx
ce5b3: pop ebp
ce5b4: jmp 0xce5f0
ce5b9: mov eax, ecx
ce5bb: mov esi, edx
ce5bd: mov ecx, 0xbde5e0
ce5c2: mov edx, eax
ce5c4: push ebp
ce5c5: push dword ptr [esp + 4]
ce5c9: push esi
ce5ca: call 0xa8800
ce5cf: add esp, 0xc
ce5d2: mov ecx, 0xbde5e0
ce5d7: mov edx, ebx
ce5d9: add esp, 0x10
ce5dc: pop esi
ce5dd: pop edi
ce5de: pop ebx
ce5df: pop ebp
ce5e0: jmp 0xa4350
ce5e5: nop word ptr cs:[eax + eax]
ce5ef: nop 
ce5f0: push ebp
ce5f1: push ebx
ce5f2: push edi
ce5f3: push esi
ce5f4: sub esp, 0x10
