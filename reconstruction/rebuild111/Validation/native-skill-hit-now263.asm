a8800: push ebp
a8801: push ebx
a8802: push edi
a8803: push esi
a8804: sub esp, 0x20
a8807: mov dword ptr [esp + 0x1c], edx
a880b: imul ebp, edx, 0x298
a8811: cmp dword ptr [ecx + ebp + 0x112ac], 0
a8819: jle 0xa8e4e
a881f: mov esi, ecx
a8821: mov eax, dword ptr [esp + 0x34]
a8825: mov ecx, dword ptr [ecx + 0xed40]
a882b: mov dword ptr [esi + 0x6e98], ecx
a8831: cmp ecx, 0x1f
a8834: ja 0xa8840
a8836: mov edx, 0x81000008
a883b: bt edx, ecx
a883e: jb 0xa884a
a8840: cmp ecx, 0x4d
a8843: je 0xa884a
a8845: cmp ecx, 0x4b
a8848: jne 0xa8879
a884a: mov edx, dword ptr [esi + ebp + 0x111e0]
a8851: test edx, edx
a8853: jle 0xa8879
a8855: lea edi, [esi + ebp + 0x111e0]
a885c: add eax, eax
a885e: mov dword ptr [esi + ebp + 0x111dc], 0
a8869: dec edx
a886a: mov dword ptr [edi], edx
a886c: jne 0xa8879
a886e: mov dword ptr [esi + ebp + 0x111d4], 0
a8879: mov edi, dword ptr [esp + 0x3c]
a887d: mov edx, dword ptr [esi + ebp + 0x112a8]
a8884: mov ebx, edx
a8886: shl ebx, 6
a8889: test byte ptr [ebx + edx*4 + 0x2597a0], 0x10
a8891: je 0xa88a8
a8893: cmp ecx, 0x10b
a8899: je 0xa88a8
a889b: mov ebx, 1
a88a0: cmp ecx, 0x106
a88a6: jne 0xa88aa
a88a8: mov ebx, eax
a88aa: lea eax, [esi + ebp + 0x11068]
a88b1: mov dword ptr [esp + 0x18], eax
a88b5: cmp ebx, 2
a88b8: xorps xmm0, xmm0
a88bb: movlps xmm0, qword ptr [esi + ebp + 0x111f8]
a88c3: mov eax, dword ptr [esi + 0x11064]
a88c9: lea ecx, [eax + 1]
a88cc: mov dword ptr [esi + 0x11064], ecx
a88d2: mov ecx, 1
a88d7: cmovl ebx, ecx
a88da: and eax, 0xf
a88dd: lea eax, [eax + eax*2]
a88e0: shl eax, 4
a88e3: lea eax, [esi + eax + 0x10d64]
a88ea: movss xmm1, dword ptr [esi + 0x4ab8]
a88f2: test edi, edi
a88f4: jle 0xa8907
a88f6: mov ecx, 0xa
a88fb: cmp edi, 0xa
a88fe: ja 0xa8907
a8900: cmp edi, ebx
a8902: mov ecx, ebx
a8904: cmovl ecx, edi
a8907: movlps qword ptr [eax], xmm0
a890a: movss dword ptr [eax + 8], xmm1
a890f: mov dword ptr [eax + 0xc], 0x3e4ccccd
a8916: mov dword ptr [eax + 0x10], ebx
a8919: mov dword ptr [eax + 0x14], ecx
a891c: mov dword ptr [eax + 0x18], 0
a8923: mov dword ptr [eax + 0x1c], 0
a892a: mov dword ptr [eax + 0x20], 0
a8931: mov dword ptr [eax + 0x24], 0
a8938: mov dword ptr [eax + 0x28], 0
a893f: mov dword ptr [eax + 0x2c], 0
a8946: mov ecx, esi
a8948: mov edx, dword ptr [esp + 0x18]
a894c: push eax
a894d: call 0xa5b10
a8952: add esp, 4
a8955: cmp dword ptr [esi + 0xed40], 2
a895c: jne 0xa89a9
a895e: cmp dword ptr [0xbde3fc], 0
a8965: je 0xa89a9
a8967: lea eax, [esi + ebp + 0x111fc]
a896e: movss xmm0, dword ptr [eax]
a8972: movss xmm1, dword ptr [eax - 4]
a8977: sub esp, 0x18
a897a: movss dword ptr [esp + 0x10], xmm0
a8980: movss dword ptr [esp + 0xc], xmm1
a8986: mov dword ptr [esp], esi
a8989: mov dword ptr [esp + 0x14], 0
a8991: mov dword ptr [esp + 8], 0
a8999: mov dword ptr [esp + 4], 1
a89a1: call 0x676a0
a89a6: add esp, 0x18
a89a9: lea eax, [esi + ebp + 0x112a8]
a89b0: mov dword ptr [esp + 0x14], eax
a89b4: cmp edi, 2
a89b7: mov dword ptr [esp + 8], ebp
a89bb: mov dword ptr [esp + 4], ebx
a89bf: jl 0xa8ab1
a89c5: cmp edi, 0xa
a89c8: mov eax, 0xa
a89cd: cmovl eax, edi
a89d0: mov ecx, dword ptr [esi + 0x478d4]
a89d6: mov edx, dword ptr [esi + 0x478d8]
a89dc: mov dword ptr [esp], edx
a89df: xor edi, edi
a89e1: movss xmm0, dword ptr [0x74a4ac]; 0.20000000298023224
a89e9: movss xmm1, dword ptr [0x74a330]; 0.019999999552965164
a89f1: mov dword ptr [esp + 0xc], eax
a89f5: mov dword ptr [esp + 0x10], ecx
a89f9: jmp 0xa8a3c
a89fb: mov ebx, edx
a89fd: mov ebp, dword ptr [esp + 8]
a8a01: mov eax, dword ptr [esp + 0xc]
a8a05: mov ecx, dword ptr [esp + 0x10]
a8a09: add ebx, ecx
a8a0b: and ebx, 0x1f
a8a0e: mov dword ptr [esi + ebx*4 + 0x47854], 0
a8a19: movss dword ptr [esi + ebx*4 + 0x478dc], xmm2
a8a22: mov edx, dword ptr [esp]
a8a25: inc edx
a8a26: mov dword ptr [esp], edx
a8a29: mov dword ptr [esi + 0x478d8], edx
a8a2f: mov ebx, dword ptr [esp + 4]
a8a33: inc edi
a8a34: cmp edi, eax
a8a36: je 0xa8b67
a8a3c: mov edx, dword ptr [esp]
a8a3f: sub edx, ecx
a8a41: cmp edx, 0x1f
a8a44: ja 0xa8a33
a8a46: xorps xmm2, xmm2
a8a49: cvtsi2ss xmm2, edi
a8a4d: mulss xmm2, xmm0
a8a51: addss xmm2, xmm1
a8a55: addss xmm2, dword ptr [esi + 0x4ab8]
a8a5d: xor ebx, ebx
a8a5f: test edx, edx
a8a61: je 0xa8a09
a8a63: mov ebp, dword ptr [esp]
a8a66: nop word ptr cs:[eax + eax]
a8a70: lea eax, [ebp - 1]
a8a73: mov ecx, eax
a8a75: and ecx, 0x1f
a8a78: movss xmm3, dword ptr [esi + ecx*4 + 0x478dc]
a8a81: ucomiss xmm3, xmm2
a8a84: jbe 0xa89fb
a8a8a: mov ecx, dword ptr [esi + ecx*4 + 0x47854]
a8a91: shl ebp, 2
a8a94: and ebp, 0x7c
a8a97: mov dword ptr [esi + ebp + 0x47854], ecx
a8a9e: movss dword ptr [esi + ebp + 0x478dc], xmm3
a8aa7: dec edx
a8aa8: mov ebp, eax
a8aaa: jne 0xa8a70
a8aac: jmp 0xa89fd
a8ab1: mov eax, dword ptr [esi + 0xed40]
a8ab7: cmp eax, 0x7f
a8aba: jl 0xa8b67
a8ac0: cmp eax, 0xca
a8ac5: je 0xa8b67
a8acb: mov ecx, dword ptr [esi + 0x478d4]
a8ad1: mov eax, dword ptr [esi + 0x478d8]
a8ad7: mov edi, eax
a8ad9: sub edi, ecx
a8adb: cmp edi, 0x1f
a8ade: ja 0xa8b67
a8ae4: movss xmm0, dword ptr [esi + 0x4ab8]
a8aec: addss xmm0, dword ptr [0x74a330]; 0.019999999552965164
a8af4: xor edx, edx
a8af6: test edi, edi
a8af8: je 0xa8b47
a8afa: mov dword ptr [esp], ecx
a8afd: mov ebx, eax
a8aff: nop 
a8b00: lea ecx, [ebx - 1]
a8b03: mov ebp, ecx
a8b05: and ebp, 0x1f
a8b08: movss xmm1, dword ptr [esi + ebp*4 + 0x478dc]
a8b11: ucomiss xmm1, xmm0
a8b14: jbe 0xa8b3a
a8b16: mov ebp, dword ptr [esi + ebp*4 + 0x47854]
a8b1d: shl ebx, 2
a8b20: and ebx, 0x7c
a8b23: mov dword ptr [esi + ebx + 0x47854], ebp
a8b2a: movss dword ptr [esi + ebx + 0x478dc], xmm1
a8b33: dec edi
a8b34: mov ebx, ecx
a8b36: jne 0xa8b00
a8b38: jmp 0xa8b3c
a8b3a: mov edx, edi
a8b3c: mov ebp, dword ptr [esp + 8]
a8b40: mov ebx, dword ptr [esp + 4]
a8b44: mov ecx, dword ptr [esp]
a8b47: add edx, ecx
a8b49: and edx, 0x1f
a8b4c: mov dword ptr [esi + edx*4 + 0x47854], 0
a8b57: movss dword ptr [esi + edx*4 + 0x478dc], xmm0
a8b60: inc eax
a8b61: mov dword ptr [esi + 0x478d8], eax
a8b67: lea edi, [esi + ebp + 0x112ac]
a8b6e: mov eax, dword ptr [esp + 0x14]
a8b72: mov eax, dword ptr [eax]
a8b74: cmp eax, 0x28f
a8b79: ja 0xa8b95
a8b7b: mov ecx, eax
a8b7d: shl ecx, 6
a8b80: mov edx, 0xfffff93d
a8b85: add edx, dword ptr [ecx + eax*4 + 0x25979c]
a8b8c: cmp edx, -7
a8b8f: ja 0xa8c46
a8b95: cmp dword ptr [esi + 0x4410], 0
a8b9c: je 0xa8bb0
a8b9e: mov eax, dword ptr [edi]
a8ba0: test eax, eax
a8ba2: jle 0xa8bb0
a8ba4: cmp eax, ebx
a8ba6: cmovae eax, ebx
a8ba9: add dword ptr [esi + ebp + 0x111ec], eax
a8bb0: mov dword ptr [esi + ebp + 0x1114c], 0
a8bbb: mov dword ptr [esi + ebp + 0x11110], 0
a8bc6: mov dword ptr [esi + ebp + 0x11264], 0
a8bd1: lea eax, [esi + ebp + 0x11274]
a8bd8: movss xmm0, dword ptr [esi + ebp + 0x11274]
a8be1: xorps xmm1, xmm1
a8be4: ucomiss xmm0, xmm1
a8be7: jbe 0xa8c0d
a8be9: mov dword ptr [esi + ebp + 0x11280], 3
a8bf4: movss xmm0, dword ptr [esi + 0x4ab8]
a8bfc: addss xmm0, dword ptr [0x74ae7c]; 2.5
a8c04: movss dword ptr [esi + ebp + 0x1127c], xmm0
a8c0d: xorps xmm0, xmm0
a8c10: movlps qword ptr [eax], xmm0
a8c13: mov dword ptr [esi + ebp + 0x11298], 0
a8c1e: cmp dword ptr [esi + ebp + 0x1128c], 0
a8c26: je 0xa8c3e
a8c28: cmp dword ptr [esi + 0x4795c], 0
a8c2f: mov eax, dword ptr [edi]
a8c31: je 0xa8c40
a8c33: mov ecx, 1
a8c38: cmp eax, ebx
a8c3a: jle 0xa8c44
a8c3c: jmp 0xa8c40
a8c3e: mov eax, dword ptr [edi]
a8c40: sub eax, ebx
a8c42: mov ecx, eax
a8c44: mov dword ptr [edi], ecx
a8c46: cmp dword ptr [esi + 0xe008], 0x2c
a8c4d: jne 0xa8c93
a8c4f: imul eax, dword ptr [esi + 0x477e8], 0x19660d
a8c59: add eax, 0x3c6ef35f
a8c5e: mov dword ptr [esi + 0x477e8], eax
a8c64: mov ecx, eax
a8c66: shr ecx, 0x10
a8c69: xor ecx, eax
a8c6b: imul eax, ecx, 0x3afb7e91
a8c71: ror eax, 4
a8c74: cmp eax, 0x68db8
a8c79: ja 0xa8c93
a8c7b: movss xmm0, dword ptr [esi + 0x4ab8]
a8c83: addss xmm0, dword ptr [0x74ae80]; 3600.0
a8c8b: movss dword ptr [esi + 0x4214], xmm0
a8c93: mov eax, dword ptr [esi + 0xed40]
a8c99: test eax, eax
a8c9b: jle 0xa8cb2
a8c9d: mov ecx, esi
a8c9f: mov edx, 1
a8ca4: push eax
a8ca5: push ebx
a8ca6: push dword ptr [esp + 0x24]
a8caa: call 0xa5d30
a8caf: add esp, 0xc
a8cb2: movss xmm0, dword ptr [esi + 0x4ab8]
a8cba: movss dword ptr [esi + ebp + 0x11218], xmm0
a8cc3: mov ebx, dword ptr [esi + ebp + 0x1128c]
a8cca: xor eax, eax
a8ccc: test ebx, ebx
a8cce: jne 0xa8ce7
a8cd0: mov eax, dword ptr [esp + 0x14]
a8cd4: mov eax, dword ptr [eax]
a8cd6: mov ecx, eax
a8cd8: shl ecx, 6
a8cdb: mov eax, dword ptr [ecx + eax*4 + 0x2597a0]
a8ce2: shr eax, 1
a8ce4: and eax, 1
a8ce7: mov edx, dword ptr [esp + 0x38]
a8ceb: mov dword ptr [esi + ebp + 0x112b0], eax
a8cf2: mov ecx, dword ptr [esi + 0xed40]
a8cf8: cmp ecx, 2
a8cfb: jne 0xa8d9e
a8d01: mov eax, dword ptr [esi + 0xed44]
a8d07: cmp eax, 6
a8d0a: jl 0xa8d9e
a8d10: cmp byte ptr [esi + 0xe041], 0
a8d17: je 0xa8d9e
a8d1d: cmp dword ptr [edi], 0
a8d20: jle 0xa8d9e
a8d22: mov edx, dword ptr [esp + 0x14]
a8d26: mov edx, dword ptr [edx]
a8d28: mov dword ptr [esp], edx
a8d2b: cmp edx, 0x28f
a8d31: ja 0xa8d65
a8d33: mov edx, dword ptr [esp]
a8d36: shl edx, 6
a8d39: mov dword ptr [esp + 4], edx
a8d3d: mov ebp, 0xfffff93d
a8d42: mov edx, dword ptr [esp]
a8d45: mov dword ptr [esp + 0xc], ebx
a8d49: mov ebx, dword ptr [esp + 4]
a8d4d: add ebp, dword ptr [ebx + edx*4 + 0x25979c]
a8d54: mov ebx, dword ptr [esp + 0xc]
a8d58: mov edx, dword ptr [esp + 0x38]
a8d5c: cmp ebp, -7
a8d5f: mov ebp, dword ptr [esp + 8]
a8d63: ja 0xa8d9e
a8d65: test ebx, ebx
a8d67: je 0xa8d82
a8d69: mov edx, dword ptr [esp + 8]
a8d6d: mov ebp, dword ptr [esi + edx + 0x112a0]
a8d74: test ebp, ebp
a8d76: je 0xa8d82
a8d78: xor edx, edx
a8d7a: cmp ebp, 3
a8d7d: sete dl
a8d80: jmp 0xa8d8e
a8d82: mov edx, dword ptr [esp]
a8d85: shl edx, 6
a8d88: mov edx, dword ptr [edx + 0x2c0178]
a8d8e: test edx, edx
a8d90: mov ebp, dword ptr [esp + 8]
a8d94: mov edx, dword ptr [esp + 0x38]
a8d98: je 0xa8e56
a8d9e: test edx, edx
a8da0: je 0xa8dad
a8da2: mov dword ptr [esi + ebp + 0x112cc], 0x3f99999a
a8dad: cmp dword ptr [edi], 0
a8db0: jg 0xa8e4e
a8db6: lea eax, [esi + ebp + 0x112b0]
a8dbd: cmp dword ptr [esi + 0xe008], 8
a8dc4: jne 0xa8df7
a8dc6: test ebx, ebx
a8dc8: jne 0xa8df7
a8dca: cmp ecx, 0x56
a8dcd: je 0xa8df7
a8dcf: movzx ecx, byte ptr [esi + 0xe069]
a8dd6: test cl, cl
a8dd8: je 0xa8df7
a8dda: movzx ecx, cl
a8ddd: lea ecx, [ecx + ecx*2]
a8de0: add ecx, dword ptr [esi + 0x4ad8]
a8de6: mov edx, dword ptr [esi + 0x4adc]
a8dec: cmp ecx, edx
a8dee: cmovge ecx, edx
a8df1: mov dword ptr [esi + 0x4ad8], ecx
a8df7: mov dword ptr [edi], 0
a8dfd: movss dword ptr [esi + ebp + 0x1121c], xmm0
a8e06: mov dword ptr [esi + ebp + 0x11284], 0
a8e11: mov dword ptr [esi + ebp + 0x11288], 0
a8e1c: mov dword ptr [eax], 0
a8e22: xorps xmm0, xmm0
a8e25: movlps qword ptr [esi + ebp + 0x112cc], xmm0
a8e2d: mov ecx, esi
a8e2f: mov edx, dword ptr [esp + 0x18]
a8e33: call 0xa43f0
a8e38: mov eax, dword ptr [esp + 0x1c]
a8e3c: cmp dword ptr [esi + 0x4b00], eax
a8e42: jne 0xa8e4e
a8e44: mov dword ptr [esi + 0x4b00], 0xffffffff
a8e4e: add esp, 0x20
a8e51: pop esi
a8e52: pop edi
a8e53: pop ebx
a8e54: pop ebp
a8e55: ret 
a8e56: imul eax, eax, 0x1f4
a8e5c: add eax, 0xfffff63c
a8e61: imul eax, dword ptr [esi + 0x4ae0]
a8e68: mov edx, 0x51eb851f
a8e6d: imul edx
a8e6f: mov eax, edx
a8e71: shr eax, 0x1f
a8e74: sar edx, 4
a8e77: add eax, edx
a8e79: mov edx, dword ptr [esp]
a8e7c: movzx ebp, word ptr [edx + edx + 0x427d40]
a8e84: mov edx, 0x64
a8e89: sub edx, ebp
a8e8b: mov dword ptr [esp + 0x10], edx
a8e8f: imul eax, edx
a8e92: mov edx, 0x51eb851f
a8e97: imul edx
a8e99: mov ebp, dword ptr [esp + 8]
a8e9d: mov dword ptr [esp + 4], edx
a8ea1: mov edx, dword ptr [esp + 0x38]
a8ea5: mov eax, dword ptr [esp + 4]
a8ea9: shr eax, 0x1f
a8eac: mov dword ptr [esp + 0xc], eax
a8eb0: mov eax, dword ptr [esp + 4]
a8eb4: sar eax, 5
a8eb7: add eax, dword ptr [esp + 0xc]
a8ebb: mov dword ptr [esp + 4], eax
a8ebf: mov eax, dword ptr [esp]
a8ec2: movzx eax, word ptr [eax + eax + 0x428780]
a8eca: add eax, eax
a8ecc: lea eax, [eax + eax*4]
a8ecf: sub dword ptr [esp + 4], eax
a8ed3: cmp dword ptr [esp + 4], 0
a8ed8: jle 0xa8d9e
a8ede: imul eax, dword ptr [esi + 0x477e8], 0x19660d
a8ee8: add eax, 0x3c6ef35f
a8eed: mov dword ptr [esi + 0x477e8], eax
a8ef3: mov edx, eax
a8ef5: shr edx, 0x10
a8ef8: xor edx, eax
a8efa: mov eax, edx
a8efc: mov dword ptr [esp], edx
a8eff: mov edx, 0xd1b71759
a8f04: mul edx
a8f06: shr edx, 0xd
a8f09: imul eax, edx, 0x2710
a8f0f: mov edx, dword ptr [esp + 0x38]
a8f13: sub dword ptr [esp], eax
a8f16: mov eax, dword ptr [esp]
a8f19: cmp eax, dword ptr [esp + 4]
a8f1d: jae 0xa8d9e
a8f23: cvtsi2ss xmm1, dword ptr [esp + 0x10]
a8f29: mulss xmm1, dword ptr [0x74a238]; 5.0
a8f31: divss xmm1, dword ptr [0x74a43c]
a8f39: movss dword ptr [esi + ebp + 0x112cc], xmm1
a8f42: jmp 0xa8d9e
a8f47: nop word ptr [eax + eax]
a8f50: push edi
a8f51: push esi
a8f52: mov eax, dword ptr [esp + 0xc]
a8f56: test edx, edx
a8f58: jle 0xa8ff8
a8f5e: mov esi, dword ptr [ecx + 0x11064]
a8f64: lea edi, [esi + 1]
a8f67: mov dword ptr [ecx + 0x11064], edi
a8f6d: and esi, 0xf
a8f70: lea esi, [esi + esi*2]
a8f73: shl esi, 4
a8f76: movss xmm0, dword ptr [ecx + 0x4ab8]
a8f7e: xorps xmm1, xmm1
a8f81: movlps xmm1, qword ptr [ecx + 0x4aa0]
a8f88: movlps qword ptr [ecx + esi + 0x10d64], xmm1
a8f90: movss dword ptr [ecx + esi + 0x10d6c], xmm0
a8f99: mov dword ptr [ecx + esi + 0x10d70], 0x3e4ccccd
a8fa4: mov dword ptr [ecx + esi + 0x10d74], edx
a8fab: mov dword ptr [ecx + esi + 0x10d78], 1
a8fb6: mov dword ptr [ecx + esi + 0x10d7c], 0
a8fc1: mov dword ptr [ecx + esi + 0x10d88], 0
a8fcc: mov dword ptr [ecx + esi + 0x10d8c], 0
a8fd7: mov dword ptr [ecx + esi + 0x10d90], 0
a8fe2: mov dword ptr [ecx + esi + 0x10d80], 4
a8fed: mov dword ptr [ecx + esi + 0x10d84], 3
a8ff8: test eax, eax
a8ffa: jle 0xa909a
a9000: mov edx, dword ptr [ecx + 0x11064]
a9006: lea esi, [edx + 1]
a9009: mov dword ptr [ecx + 0x11064], esi
a900f: and edx, 0xf
a9012: lea edx, [edx + edx*2]
a9015: shl edx, 4
a9018: movss xmm0, dword ptr [ecx + 0x4ab8]
a9020: xorps xmm1, xmm1
a9023: movlps xmm1, qword ptr [ecx + 0x4aa0]
a902a: movlps qword ptr [ecx + edx + 0x10d64], xmm1
a9032: movss dword ptr [ecx + edx + 0x10d6c], xmm0
a903b: mov dword ptr [ecx + edx + 0x10d70], 0x3e4ccccd
a9046: mov dword ptr [ecx + edx + 0x10d74], eax
a904d: mov dword ptr [ecx + edx + 0x10d78], 1
a9058: mov dword ptr [ecx + edx + 0x10d7c], 0
a9063: mov dword ptr [ecx + edx + 0x10d88], 0
a906e: mov dword ptr [ecx + edx + 0x10d8c], 0
a9079: mov dword ptr [ecx + edx + 0x10d90], 0
a9084: mov dword ptr [ecx + edx + 0x10d80], 5
a908f: mov dword ptr [ecx + edx + 0x10d84], 4
a909a: pop esi
a909b: pop edi
a909c: ret 
a909d: nop dword ptr [eax]
a90a0: push esi
a90a1: mov esi, ecx
a90a3: mov dword ptr [ecx + 0x4b34], 0
a90ad: mov dword ptr [ecx + 0x4e60], 0
a90b7: lea eax, [ecx + 0x2e8c]
a90bd: push 0x158c
a90c2: push 0
a90c4: push eax
a90c5: call 0x137420
a90ca: add esp, 0xc
a90cd: lea eax, [esi + 0x4418]
a90d3: push 0x2d0
a90d8: push 0
a90da: push eax
a90db: call 0x137420
a90e0: add esp, 0xc
a90e3: lea eax, [esi + 0x46e8]
a90e9: push 0xf0
a90ee: push 0
a90f0: push eax
a90f1: call 0x137420
a90f6: add esp, 0xc
