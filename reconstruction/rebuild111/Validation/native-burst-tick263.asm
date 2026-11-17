ce5f0: push ebp
ce5f1: push ebx
ce5f2: push edi
ce5f3: push esi
ce5f4: sub esp, 0x10
ce5f7: mov edi, 0xffffe000
ce5fc: movss xmm2, dword ptr [0x74a5a0]
ce604: jmp 0xce623
ce606: nop word ptr cs:[eax + eax]
ce610: mov dword ptr [edi + 0xbef344], 0
ce61a: add edi, 0x40
ce61d: je 0xce9be
ce623: cmp dword ptr [edi + 0xbef344], 0
ce62a: je 0xce61a
ce62c: cmp dword ptr [0xbe30b0], 0
ce633: jle 0xce610
ce635: mov eax, dword ptr [0xbec5ac]
ce63a: cmp eax, dword ptr [edi + 0xbef370]
ce640: jne 0xce610
ce642: mov eax, dword ptr [0xbec5e8]
ce647: cmp eax, dword ptr [edi + 0xbef374]
ce64d: jne 0xce610
ce64f: mov esi, dword ptr [edi + 0xbef348]
ce655: cmp esi, 0x150
ce65b: jae 0xce610
ce65d: imul ebp, esi, 0x298
ce663: cmp dword ptr [ebp + 0xbef898], 0
ce66a: je 0xce610
ce66c: cmp dword ptr [ebp + 0xbef88c], 0
ce673: jle 0xce610
ce675: mov eax, dword ptr [ebp + 0xbef884]
ce67b: cmp eax, dword ptr [edi + 0xbef36c]
ce681: jne 0xce610
ce683: movss xmm0, dword ptr [0xbe3098]
ce68b: addss xmm0, xmm2
ce68f: movss xmm1, dword ptr [edi + 0xbef37c]
ce697: ucomiss xmm1, xmm0
ce69a: ja 0xce61a
ce6a0: mov eax, dword ptr [edi + 0xbef354]
ce6a6: mov ecx, dword ptr [edi + 0xbef350]
ce6ac: cdq 
ce6ad: idiv dword ptr [edi + 0xbef34c]
ce6b3: xor ebx, ebx
ce6b5: cmp ecx, edx
ce6b7: setl bl
ce6ba: add ebx, eax
ce6bc: mov eax, dword ptr [0xbed320]
ce6c1: mov dword ptr [esp], eax
ce6c4: mov eax, dword ptr [0xbed324]
ce6c9: mov dword ptr [esp + 0xc], eax
ce6cd: mov eax, dword ptr [0xbe29f0]
ce6d2: mov dword ptr [esp + 8], eax
ce6d6: mov eax, dword ptr [edi + 0xbef364]
ce6dc: mov dword ptr [0xbed324], eax
ce6e1: mov eax, dword ptr [edi + 0xbef368]
ce6e7: mov dword ptr [0xbe29f0], eax
ce6ec: mov eax, dword ptr [edi + 0xbef360]
ce6f2: mov dword ptr [0xbed320], eax
ce6f7: xor eax, eax
ce6f9: test ecx, ecx
ce6fb: setg al
ce6fe: mov dword ptr [0xbe5474], eax
ce703: lea eax, [ebp + 0xbef88c]
ce709: mov dword ptr [esp + 4], eax
ce70d: mov ecx, 0xbde5e0
ce712: mov edx, esi
ce714: push 1
ce716: push dword ptr [edi + 0xbef35c]
ce71c: push ebx
ce71d: call 0xa8800
ce722: movss xmm1, dword ptr [0x74a288]
ce72a: add esp, 0xc
ce72d: mov dword ptr [0xbe5474], 0
ce737: mov eax, dword ptr [esp]
ce73a: mov dword ptr [0xbed320], eax
ce73f: mov eax, dword ptr [esp + 0xc]
ce743: mov dword ptr [0xbed324], eax
ce748: mov eax, dword ptr [esp + 8]
ce74c: mov dword ptr [0xbe29f0], eax
ce751: add dword ptr [edi + 0xbef358], ebx
ce757: mov ebx, dword ptr [esp + 4]
ce75b: mov edx, 0xfffff93d
ce760: inc dword ptr [edi + 0xbef350]
ce766: cmp dword ptr [ebx], 0
ce769: jle 0xce7e2
ce76b: mov eax, dword ptr [ebp + 0xbef888]
ce771: cmp eax, 0x28f
ce776: ja 0xce78b
ce778: mov ecx, eax
ce77a: shl ecx, 6
ce77d: mov ecx, dword ptr [ecx + eax*4 + 0x25979c]
ce784: add ecx, edx
ce786: cmp ecx, -7
ce789: ja 0xce7e2
ce78b: cmp dword ptr [ebp + 0xbef86c], 0
ce792: je 0xce7a8
ce794: mov edx, dword ptr [ebp + 0xbef880]
ce79a: test edx, edx
ce79c: je 0xce7a8
ce79e: xor ecx, ecx
ce7a0: cmp edx, 3
ce7a3: sete cl
ce7a6: jmp 0xce7b3
ce7a8: mov ecx, eax
ce7aa: shl ecx, 6
ce7ad: mov ecx, dword ptr [ecx + 0x2c0178]
ce7b3: test ecx, ecx
ce7b5: jne 0xce7e2
ce7b7: movzx eax, word ptr [eax + eax + 0x429f20]
ce7bf: cvtsi2ss xmm0, eax
ce7c3: divss xmm0, xmm1
ce7c7: addss xmm0, dword ptr [0xbe3098]
ce7cf: ucomiss xmm0, dword ptr [ebp + 0xbef818]
ce7d6: jbe 0xce7e2
ce7d8: lea eax, [ebp + 0xbef818]
ce7de: movss dword ptr [eax], xmm0
ce7e2: mov ecx, dword ptr [edi + 0xbef360]
ce7e8: cmp ecx, 2
ce7eb: movss xmm2, dword ptr [0x74a5a0]
ce7f3: movss xmm0, dword ptr [0x74a30c]
ce7fb: je 0xce81c
ce7fd: cmp ecx, 0x4b
ce800: je 0xce81c
ce802: cmp ecx, 0x7e
ce805: jg 0xce81c
ce807: call 0xce9d0
ce80c: movss xmm0, dword ptr [0x74a30c]
ce814: movss xmm2, dword ptr [0x74a5a0]
ce81c: mov eax, dword ptr [edi + 0xbef34c]
ce822: cmp eax, 2
ce825: jl 0xce97c
ce82b: mov eax, dword ptr [edi + 0xbef358]
ce831: xorps xmm0, xmm0
ce834: movlps xmm0, qword ptr [ebp + 0xbef7d8]
ce83b: mov ecx, dword ptr [edi + 0xbef378]
ce841: mov edx, dword ptr [0xbef644]
ce847: dec ecx
ce848: mov esi, edx
ce84a: sub esi, ecx
ce84c: jbe 0xce879
ce84e: cmp esi, 0x10
ce851: ja 0xce879
ce853: mov esi, ecx
ce855: and esi, 0xf
ce858: mov dword ptr [esp], eax
ce85b: mov eax, ebx
ce85d: lea ebx, [esi + esi*2]
ce860: shl ebx, 4
ce863: cmp dword ptr [ebx + 0xbef360], 1
ce86a: mov ebx, eax
ce86c: mov eax, dword ptr [esp]
ce86f: jne 0xce879
ce871: and ecx, 0xf
ce874: jmp 0xce918
ce879: test eax, eax
ce87b: jle 0xce90a
ce881: lea ecx, [edx + 1]
ce884: mov dword ptr [0xbef644], ecx
ce88a: and edx, 0xf
ce88d: shl edx, 4
ce890: movss xmm1, dword ptr [0xbe3098]
ce898: movlps qword ptr [edx + edx*2 + 0xbef344], xmm0
ce8a0: movss dword ptr [edx + edx*2 + 0xbef34c], xmm1
ce8a9: mov dword ptr [edx + edx*2 + 0xbef350], 0x3e4ccccd
ce8b4: mov dword ptr [edx + edx*2 + 0xbef354], eax
ce8bb: mov dword ptr [edx + edx*2 + 0xbef358], 1
ce8c6: mov dword ptr [edx + edx*2 + 0xbef35c], 0
ce8d1: mov dword ptr [edx + edx*2 + 0xbef360], 0
ce8dc: mov dword ptr [edx + edx*2 + 0xbef364], 0
ce8e7: mov dword ptr [edx + edx*2 + 0xbef368], 0
ce8f2: mov dword ptr [edx + edx*2 + 0xbef36c], 0
ce8fd: mov dword ptr [edx + edx*2 + 0xbef370], 0
ce908: jmp 0xce90c
ce90a: mov ecx, edx
ce90c: mov dword ptr [edi + 0xbef378], ecx
ce912: dec ecx
ce913: and ecx, 0xf
ce916: mov esi, ecx
ce918: lea edx, [ebp + 0xbef648]
ce91e: shl esi, 4
ce921: movlps qword ptr [esi + esi*2 + 0xbef344], xmm0
ce929: mov dword ptr [esi + esi*2 + 0xbef354], eax
ce930: movss xmm0, dword ptr [0xbe3098]
ce938: movss dword ptr [esi + esi*2 + 0xbef34c], xmm0
ce941: mov dword ptr [esi + esi*2 + 0xbef360], 1
ce94c: lea eax, [ecx + ecx*2]
ce94f: shl eax, 4
ce952: lea eax, [eax + 0xbef344]
ce958: mov ecx, 0xbde5e0
ce95d: push eax
ce95e: call 0xa5b10
ce963: add esp, 4
ce966: mov eax, dword ptr [edi + 0xbef34c]
ce96c: movss xmm2, dword ptr [0x74a5a0]
ce974: movss xmm0, dword ptr [0x74a30c]
ce97c: mov ecx, dword ptr [edi + 0xbef350]
ce982: cmp ecx, eax
ce984: jge 0xce610
ce98a: cmp dword ptr [ebx], 0
ce98d: jle 0xce610
ce993: cmp ecx, 1
ce996: jne 0xce9a1
ce998: cmp dword ptr [edi + 0xbef360], 0x4e
ce99f: je 0xce9a9
ce9a1: movss xmm0, dword ptr [edi + 0xbef380]
ce9a9: addss xmm0, dword ptr [edi + 0xbef37c]
ce9b1: movss dword ptr [edi + 0xbef37c], xmm0
ce9b9: jmp 0xce61a
ce9be: add esp, 0x10
ce9c1: pop esi
ce9c2: pop edi
ce9c3: pop ebx
ce9c4: pop ebp
ce9c5: ret 
ce9c6: nop word ptr cs:[eax + eax]
ce9d0: cmp ecx, 0x7e
