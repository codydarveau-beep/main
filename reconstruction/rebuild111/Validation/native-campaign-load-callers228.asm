CALL 1a81c
1a821: cmp eax, 1
1a824: jne 0x1a833
1a826: cmp dword ptr [esp + 0x32a0], 1
1a82e: sete dl
1a831: jmp 0x1a835
1a833: xor edx, edx
1a835: test dl, dl
1a837: jne 0x1a8de
1a83d: cmp dword ptr [esp + 0x37c], 0
1a845: jne 0x1a8de
1a84b: cmp dword ptr [esp + 0x130], 0
1a853: jne 0x1a8de
1a859: cmp dword ptr [0xbe305c], 0
1a860: jne 0x1a8de
1a862: mov eax, dword ptr [esp + 0x50]
1a866: and eax, 0x101
1a86b: jne 0x1a8de
1a86d: mov eax, dword ptr [esp + 0x460]
1a874: test al, 1
1a876: jne 0x1a94b
1a87c: test byte ptr [esp + 0x254], 0x20
1a884: mov ecx, dword ptr [esp + 0x458]
1a88b: jne 0x1a96c
1a891: mov dword ptr [esp + 0x100], 0
1a89c: test cl, 1
1a89f: je 0x1a9d4

CALL 1ac03
1ac08: cmp eax, 1
1ac0b: jne 0x1ac1a
1ac0d: xor ebx, ebx
1ac0f: cmp dword ptr [esp + 0x32a0], 1
1ac17: sete bl
1ac1a: or ebx, dword ptr [esp + 0x8c]
1ac21: mov al, 1
1ac23: mov dword ptr [esp + 0x90], eax
1ac2a: jne 0x1ac52
1ac2c: cmp dword ptr [esp + 0x37c], 0
1ac34: jne 0x1ac52
1ac36: cmp dword ptr [esp + 0x130], 0
1ac3e: jne 0x1ac52
1ac40: test dword ptr [esp + 0x50], 0x101
1ac48: setne byte ptr [esp + 0x120]
1ac50: jmp 0x1ac5a
1ac52: mov byte ptr [esp + 0x120], 1
1ac5a: test byte ptr [esp + 0x50], 1
1ac5f: jne 0x1aec5
1ac65: cmp dword ptr [esp + 0x8c], 0
1ac6d: jne 0x1d0fe
1ac73: call 0xc9a70
1ac78: cmp eax, 6
1ac7b: ja 0x1ac87
1ac7d: mov ecx, 0x56
1ac82: bt ecx, eax
1ac85: jb 0x1acc1
1ac87: cmp eax, 3

CALL 1aca5
1acaa: cmp eax, 1
1acad: jne 0x1b045
1acb3: cmp dword ptr [esp + 0x32a0], 1
1acbb: jne 0x1b045
1acc1: mov ebx, dword ptr [0xbec5e8]
1acc7: mov dword ptr [0xd42a5c], ebx
1accd: mov ecx, dword ptr [0xd42a28]
1acd3: lea edx, [esp + 0x32a0]
1acda: call 0x919b0
1acdf: xor esi, esi
1ace1: cmp eax, 1
1ace4: jne 0x1ad26
1ace6: cmp dword ptr [esp + 0x32a0], 1
1acee: jne 0x1ad26
1acf0: mov ecx, ebx
1acf2: call 0x93ab0
1acf7: cmp dword ptr [esp + 0x32b0], 0
1acff: mov ecx, 0x28
1ad04: cmovns ecx, eax
1ad07: test ebx, ebx
1ad09: cmovne ecx, eax
1ad0c: test ecx, ecx
1ad0e: je 0x1ad26
1ad10: mov eax, dword ptr [esp + 0x32a8]
1ad17: cmp eax, ecx
1ad19: mov esi, 0
1ad1e: cmove esi, ecx
1ad21: test eax, eax
1ad23: cmove esi, ecx
1ad26: call 0xc9a70
1ad2b: mov edi, eax

CALL 1acda
1acdf: xor esi, esi
1ace1: cmp eax, 1
1ace4: jne 0x1ad26
1ace6: cmp dword ptr [esp + 0x32a0], 1
1acee: jne 0x1ad26
1acf0: mov ecx, ebx
1acf2: call 0x93ab0
1acf7: cmp dword ptr [esp + 0x32b0], 0
1acff: mov ecx, 0x28
1ad04: cmovns ecx, eax
1ad07: test ebx, ebx
1ad09: cmovne ecx, eax
1ad0c: test ecx, ecx
1ad0e: je 0x1ad26
1ad10: mov eax, dword ptr [esp + 0x32a8]
1ad17: cmp eax, ecx
1ad19: mov esi, 0
1ad1e: cmove esi, ecx
1ad21: test eax, eax
1ad23: cmove esi, ecx
1ad26: call 0xc9a70
1ad2b: mov edi, eax
1ad2d: call 0xc9a70
1ad32: cmp eax, 6
1ad35: ja 0x1ad41
1ad37: mov ecx, 0x56
1ad3c: bt ecx, eax
1ad3f: jb 0x1ad86
1ad41: cmp eax, 3
1ad44: jne 0x1d0f3
1ad4a: mov ecx, dword ptr [0xd42a28]
1ad50: test ecx, ecx
1ad52: je 0x1d0f3
1ad58: lea edx, [esp + 0x32a0]
1ad5f: call 0x919b0

CALL 1ad5f
1ad64: cmp eax, 1
1ad67: jne 0x1d0f3
1ad6d: mov dword ptr [esp + 0x8c], 0
1ad78: cmp dword ptr [esp + 0x32a0], 1
1ad80: jne 0x1d0fe
1ad86: cmp edi, 6
1ad89: jne 0x1b08e
1ad8f: cmp dword ptr [0xd42a60], 0
1ad96: je 0x1b10b
1ad9c: test byte ptr [esp + 0x50], 4
1ada1: jne 0x1b17d
1ada7: mov dword ptr [esp + 0x8c], 0
1adb2: test byte ptr [esp + 0x50], 2
1adb7: je 0x1d0fe
1adbd: mov esi, dword ptr [0xd42a28]
1adc3: mov ecx, esi
1adc5: lea edx, [esp + 0x32a0]
1adcc: call 0x919b0
1add1: cmp eax, 1
1add4: jne 0x1b18c
1adda: cmp dword ptr [esp + 0x32a0], 5
1ade2: jne 0x1b18c

CALL 1adcc
1add1: cmp eax, 1
1add4: jne 0x1b18c
1adda: cmp dword ptr [esp + 0x32a0], 5
1ade2: jne 0x1b18c
1ade8: cmp byte ptr [0xd42a68], 0
1adef: je 0x1b18c
1adf5: mov dword ptr [esp], 0xd42a68
1adfc: call 0x1380a0
1ae01: cmp eax, 0x18
1ae04: ja 0x1b18c
1ae0a: cmp byte ptr [0xd42a68], 0x20
1ae11: je 0x1b18c
1ae17: mov dword ptr [esp], 0xd42a68
1ae1e: call 0x1380a0
1ae23: cmp byte ptr [eax + 0xd42a67], 0x20
1ae2a: je 0x1b18c
1ae30: xorps xmm0, xmm0
1ae33: movaps xmmword ptr [esp + 0x1670], xmm0
1ae3b: mov byte ptr [esp + 0x1688], 0
1ae43: mov dword ptr [esp + 0x1684], 0

CALL 1b2a9
1b2ae: cmp esi, 0x2d
1b2b1: ja 0x1b58d
1b2b7: cmp edi, 2
1b2ba: ja 0x1b58d
1b2c0: cmp eax, 1
1b2c3: jne 0x1b58d
1b2c9: inc edi
1b2ca: mov ecx, dword ptr [esp + 0x32a4]
1b2d1: test ecx, ecx
1b2d3: je 0x1b419
1b2d9: xor ecx, edi
1b2db: xor esi, dword ptr [esp + 0x32a8]
1b2e2: xor eax, eax
1b2e4: or esi, ecx
1b2e6: sete al
1b2e9: jmp 0x1b443
1b2ee: xor ecx, ecx
1b2f0: call 0xc9f90
1b2f5: jmp 0x1b58d
1b2fa: mov eax, dword ptr [0xd42b68]
1b2ff: lea ecx, [eax - 0x19]
1b302: cmp ecx, -0x18
1b305: jb 0x1b31d
1b307: cmp byte ptr [0xd42a68], 0x20
1b30e: je 0x1b31d
1b310: cmp byte ptr [eax + 0xd42a67], 0x20
1b317: jne 0x1b45a
1b31d: mov dword ptr [0xd42a64], 1
1b327: jmp 0x1d0fe
1b32c: test ecx, ecx
1b32e: je 0x1b86e

CALL 1b393
1b398: cmp eax, 1
1b39b: jne 0x1b58d
1b3a1: cmp dword ptr [esp + 0x32a0], 1
1b3a9: jne 0x1b58d
1b3af: cmp dword ptr [esp + 0x32a4], 0
1b3b7: jne 0x1b58d
1b3bd: or dword ptr [esp + 0x32b0], 0x80000001
1b3c8: mov ecx, esi
1b3ca: lea edx, [esp + 0x32a0]
1b3d1: call 0x91cc0
1b3d6: test eax, eax
1b3d8: je 0x1b58d
1b3de: mov dword ptr [0xd42a58], 0
1b3e8: jmp 0x1b58d
1b3ed: test dword ptr [esp + 0x50], 0x400
1b3f5: jne 0x1b52a
1b3fb: test dword ptr [esp + 0x50], 0x800
1b403: jne 0x1b558
1b409: test byte ptr [esp + 0x50], 2
1b40e: jne 0x1b57f
1b414: jmp 0x1b58d

CALL 1d2e4
1d2e9: cmp eax, 1
1d2ec: jne 0x1d3ca
1d2f2: cmp dword ptr [esp + 0x32a0], 9
1d2fa: jb 0x1d3ca
1d300: cmp byte ptr [esp + 0x32b8], 0
1d308: je 0x1d3ca
1d30e: cmp dword ptr [0xbe305c], 0x1f9
1d318: jne 0x1d3e1
1d31e: call 0xcc4e0
1d323: test byte ptr [esp + 0x50], 4
1d328: jne 0x1d467
1d32e: test byte ptr [esp + 0x50], 2
1d333: je 0x1d343
1d335: cmp dword ptr [0xd47904], 0
1d33c: je 0x1d343
1d33e: call 0xcc4e0
1d343: test byte ptr [esp + 0x50], 0x10
1d348: je 0x1d35b
1d34a: xor eax, eax
1d34c: cmp dword ptr [0xd4790c], 0
1d353: sete al
1d356: mov dword ptr [0xd4790c], eax
1d35b: cmp dword ptr [0xd47904], 0
1d362: je 0x1d485
1d368: test byte ptr [esp + 0x50], 2

CALL 1d807
1d80c: mov edx, 0xbb287b
1d811: cmp eax, 1
1d814: jne 0x1e3ee
1d81a: mov eax, dword ptr [esp + 0x103c]
1d821: mov ecx, dword ptr [0xd478e4]
1d827: mov edx, 1
1d82c: shl edx, cl
1d82e: mov dword ptr [esp + 0x60], edx
1d832: mov edx, 0xb64131
1d837: bt eax, ecx
1d83a: jb 0x1e3ee
1d840: cmp ecx, 0x12
1d843: ja 0x1e3e9
1d849: mov ecx, dword ptr [0xd34020]
1d84f: mov dword ptr [esp + 0xc0], ecx
1d856: lea edx, [esp + 0x32a0]
1d85d: call 0x919b0
1d862: cmp eax, 1
1d865: jne 0x1e3e9
1d86b: cmp dword ptr [esp + 0x32a0], 9
1d873: jb 0x1e3e9
1d879: cmp byte ptr [esp + 0x32b8], 0
1d881: je 0x1e3e9
1d887: mov ecx, dword ptr [esp + 0xc0]

CALL 1d85d
1d862: cmp eax, 1
1d865: jne 0x1e3e9
1d86b: cmp dword ptr [esp + 0x32a0], 9
1d873: jb 0x1e3e9
1d879: cmp byte ptr [esp + 0x32b8], 0
1d881: je 0x1e3e9
1d887: mov ecx, dword ptr [esp + 0xc0]
1d88e: lea edx, [esp + 0x1670]
1d895: call 0x919b0
1d89a: cmp eax, 1
1d89d: jne 0x1e3e9
1d8a3: mov esi, dword ptr [esp + 0x1670]
1d8aa: xor edx, edx
1d8ac: cmp esi, 9
1d8af: setae dl
1d8b2: mov dword ptr [esp + 0x70], edx
1d8b6: xor ecx, ecx
1d8b8: cmp esi, 3
1d8bb: setae cl
1d8be: lea eax, [edx + ecx*2]
1d8c1: lea eax, [eax + edx*4]
1d8c4: xor edx, edx
1d8c6: cmp esi, 0x10
1d8c9: setae dl
1d8cc: lea eax, [eax + edx*8]
1d8cf: shl ecx, 4
1d8d2: or ecx, eax
1d8d4: xor edx, edx
1d8d6: cmp esi, 0xf
1d8d9: setae dl
1d8dc: shl edx, 5
1d8df: xor eax, eax
1d8e1: cmp esi, 0xc
1d8e4: setae al

CALL 1d895
1d89a: cmp eax, 1
1d89d: jne 0x1e3e9
1d8a3: mov esi, dword ptr [esp + 0x1670]
1d8aa: xor edx, edx
1d8ac: cmp esi, 9
1d8af: setae dl
1d8b2: mov dword ptr [esp + 0x70], edx
1d8b6: xor ecx, ecx
1d8b8: cmp esi, 3
1d8bb: setae cl
1d8be: lea eax, [edx + ecx*2]
1d8c1: lea eax, [eax + edx*4]
1d8c4: xor edx, edx
1d8c6: cmp esi, 0x10
1d8c9: setae dl
1d8cc: lea eax, [eax + edx*8]
1d8cf: shl ecx, 4
1d8d2: or ecx, eax
1d8d4: xor edx, edx
1d8d6: cmp esi, 0xf
1d8d9: setae dl
1d8dc: shl edx, 5
1d8df: xor eax, eax
1d8e1: cmp esi, 0xc
1d8e4: setae al
1d8e7: shl eax, 6
1d8ea: or eax, edx
1d8ec: xor edx, edx
1d8ee: cmp esi, 0xe
1d8f1: setae dl
1d8f4: mov ebx, edx
1d8f6: mov dword ptr [esp + 0x90], edx
1d8fd: shl ebx, 7
1d900: or ebx, eax
1d902: xor eax, eax
1d904: cmp esi, 6
1d907: setae al
1d90a: mov edi, eax
1d90c: shl edi, 8
1d90f: or edi, ebx
1d911: or edi, ecx
1d913: mov ecx, edx
1d915: shl ecx, 9
1d918: mov ebx, edx
1d91a: shl ebx, 0xa
1d91d: or ebx, ecx
1d91f: xor edx, edx

CALL 1d9e5
1d9ea: cmp eax, 1
1d9ed: jne 0x1e3f7
1d9f3: cmp dword ptr [esp + 0x32a0], 9
1d9fb: jb 0x1e3f7
1da01: cmp byte ptr [esp + 0x32b8], 0
1da09: je 0x1e3f7
1da0f: mov dword ptr [esp + 0x14], 0
1da17: mov dword ptr [esp + 0x10], 0x44ac8000
1da1f: mov dword ptr [esp + 0xc], 0x43400000
1da27: mov dword ptr [esp + 8], 0x1ee
1da2f: mov dword ptr [esp + 4], 0xbde5e0
1da37: call 0x98cc0
1da3c: test eax, eax
1da3e: je 0x1e3f7
1da44: mov ecx, 0xbde5e0
1da49: call 0x76650
1da4e: test eax, eax
1da50: je 0x1e3f7
1da56: mov dword ptr [0xbe305c], 0
1da60: mov eax, dword ptr [esp + 0x40]
1da64: jmp 0x1e3b6
1da69: cmp eax, 4

CALL 1dd48
1dd4d: cmp eax, 1
1dd50: jne 0x224f9
1dd56: mov dword ptr [esp + 0x40], 0
1dd5e: mov eax, dword ptr [esp + 0x32ac]
1dd65: mov ecx, dword ptr [esp + 0xc0]
1dd6c: mov edx, dword ptr [esp + 0x40]
1dd70: bt eax, edx
1dd73: jae 0x1dd7e
1dd75: sub ecx, 1
1dd78: jb 0x1f99e
1dd7e: mov esi, dword ptr [esp + 0x40]
1dd82: inc esi
1dd83: mov edx, esi
1dd85: mov dword ptr [esp + 0x40], esi
1dd89: cmp esi, 0x13
1dd8c: jne 0x1dd6c
1dd8e: jmp 0x224f9
1dd93: test byte ptr [esp + 0x50], 4
1dd98: mov eax, dword ptr [0xd4767c]
1dd9d: jne 0x1fb07
1dda3: test eax, eax
1dda5: je 0x1fb22
1ddab: mov esi, dword ptr [0xd47684]
1ddb1: xor eax, eax
1ddb3: cmp esi, 2
1ddb6: setne cl
1ddb9: test dword ptr [esp + 0x50], 0x1000
1ddc1: je 0x1ddd4
1ddc3: mov edx, dword ptr [0xd47688]
1ddc9: test edx, edx
1ddcb: je 0x1ddd4
1ddcd: dec edx
1ddce: mov dword ptr [0xd47688], edx

CALL 1de61
1de66: cmp eax, 1
1de69: jne 0x1fb64
1de6f: mov eax, dword ptr [esp + 0x167c]
1de76: mov ecx, dword ptr [0xd424d4]
1de7c: mov dword ptr [esp], eax
1de7f: lea edx, [esp + 0x32a0]
1de86: call 0xccf50
1de8b: test eax, eax
1de8d: je 0x1fb64
1de93: lea eax, [esp + 0x32a0]
1de9a: mov dword ptr [esp + 4], eax
1de9e: mov dword ptr [esp + 8], 0x3c
1dea6: mov dword ptr [esp], 0xd424d8
1dead: call 0x1373a0
1deb2: jmp 0x1fb0f
1deb7: mov dword ptr [0xd4768c], 0
1dec1: mov eax, dword ptr [esp + 0x40]
1dec5: jmp 0x1e3b6
1deca: mov ecx, dword ptr [0xd47690]
1ded0: lea eax, [ecx + 4]
1ded3: mov edx, 0xcccccccd
1ded8: mul edx
1deda: shr edx, 2
1dedd: lea eax, [edx + edx*4]
1dee0: neg eax
1dee2: lea eax, [ecx + eax + 4]
1dee6: mov dword ptr [0xd47690], eax

CALL 1dfd6
1dfdb: cmp eax, 1
1dfde: jne 0x1fc83
1dfe4: cmp dword ptr [esp + 0x32a0], 9
1dfec: jb 0x1fc83
1dff2: cmp byte ptr [esp + 0x32b8], 0
1dffa: je 0x1fc83
1e000: mov ecx, dword ptr [esp + 0xc0]
1e007: lea edx, [esp + 0x1670]
1e00e: call 0x919b0
1e013: cmp eax, 1
1e016: jne 0x1fc83
1e01c: mov ecx, dword ptr [esp + 0xc0]
1e023: lea edx, [esp + 0x1030]
1e02a: call 0x98830
1e02f: test eax, eax
1e031: js 0x1fc83
1e037: mov eax, dword ptr [esp + 0x1670]
1e03e: shl esi, 5
1e041: mov dword ptr [esp + 0x90], esi
1e048: cmp eax, dword ptr [esi + 0x3a6468]
1e04e: jb 0x1fc83
1e054: mov eax, dword ptr [esp + 0x1034]
1e05b: not eax

CALL 1e00e
1e013: cmp eax, 1
1e016: jne 0x1fc83
1e01c: mov ecx, dword ptr [esp + 0xc0]
1e023: lea edx, [esp + 0x1030]
1e02a: call 0x98830
1e02f: test eax, eax
1e031: js 0x1fc83
1e037: mov eax, dword ptr [esp + 0x1670]
1e03e: shl esi, 5
1e041: mov dword ptr [esp + 0x90], esi
1e048: cmp eax, dword ptr [esi + 0x3a6468]
1e04e: jb 0x1fc83
1e054: mov eax, dword ptr [esp + 0x1034]
1e05b: not eax
1e05d: mov ecx, dword ptr [esp + 0x90]
1e064: test dword ptr [ecx + 0x3a646c], eax
1e06a: jne 0x1fc83
1e070: mov ecx, dword ptr [esp + 0xc0]
1e077: lea edx, [esp + 0x1570]
1e07e: call 0x98830
1e083: test eax, eax
1e085: js 0x1fc83
1e08b: mov eax, dword ptr [esp + 0x70]
1e08f: test dword ptr [esp + 0x1570], eax

CALL 1fab1
1fab6: cmp eax, 1
1fab9: jne 0x1fd20
1fabf: mov eax, dword ptr [esp + 0x167c]
1fac6: mov ecx, dword ptr [0xd424d4]
1facc: mov dword ptr [esp], eax
1facf: lea edx, [esp + 0x32a0]
1fad6: call 0xccf50
1fadb: test eax, eax
1fadd: je 0x1fd20
1fae3: lea eax, [esp + 0x32a0]
1faea: mov dword ptr [esp + 4], eax
1faee: mov dword ptr [esp + 8], 0x3c
1faf6: mov dword ptr [esp], 0xd424d8
1fafd: call 0x1373a0
1fb02: jmp 0x224f9
1fb07: test eax, eax
1fb09: je 0x1fd2d
1fb0f: mov dword ptr [0xd4767c], 0
1fb19: mov eax, dword ptr [esp + 0x40]
1fb1d: jmp 0x1e3b6
1fb22: test byte ptr [esp + 0x50], 8
1fb27: jne 0x1fd40
1fb2d: test byte ptr [esp + 0x50], 0x10
1fb32: jne 0x1fd5d

CALL 1fb9b
1fba0: cmp eax, 1
1fba3: jne 0x1fe10
1fba9: cmp dword ptr [esp + 0x32a0], 9
1fbb1: jb 0x1fe10
1fbb7: cmp byte ptr [esp + 0x32b8], 0
1fbbf: je 0x1fe10
1fbc5: mov ecx, dword ptr [esp + 0xc0]
1fbcc: lea edx, [esp + 0x1670]
1fbd3: call 0x919b0
1fbd8: cmp eax, 1
1fbdb: jne 0x1fe10
1fbe1: mov ecx, dword ptr [esp + 0xc0]
1fbe8: lea edx, [esp + 0x1030]
1fbef: call 0x98830
1fbf4: test eax, eax
1fbf6: js 0x1fe10
1fbfc: mov eax, dword ptr [esp + 0x1670]
1fc03: shl esi, 5
1fc06: cmp eax, dword ptr [esi + 0x3a6468]
1fc0c: jb 0x1fe10
1fc12: mov ecx, esi
1fc14: mov eax, dword ptr [esp + 0x1034]
1fc1b: not eax
1fc1d: test dword ptr [esi + 0x3a646c], eax

CALL 1fbd3
1fbd8: cmp eax, 1
1fbdb: jne 0x1fe10
1fbe1: mov ecx, dword ptr [esp + 0xc0]
1fbe8: lea edx, [esp + 0x1030]
1fbef: call 0x98830
1fbf4: test eax, eax
1fbf6: js 0x1fe10
1fbfc: mov eax, dword ptr [esp + 0x1670]
1fc03: shl esi, 5
1fc06: cmp eax, dword ptr [esi + 0x3a6468]
1fc0c: jb 0x1fe10
1fc12: mov ecx, esi
1fc14: mov eax, dword ptr [esp + 0x1034]
1fc1b: not eax
1fc1d: test dword ptr [esi + 0x3a646c], eax
1fc23: jne 0x1fe10
1fc29: mov ecx, dword ptr [esp + 0xc0]
1fc30: lea edx, [esp + 0x1570]
1fc37: call 0x98830
1fc3c: test eax, eax
1fc3e: js 0x1fe10
1fc44: mov eax, dword ptr [esp + 0x70]
1fc48: or dword ptr [esp + 0x1570], eax
1fc4f: mov ecx, dword ptr [esp + 0xc0]
1fc56: lea edx, [esp + 0x1570]

CALL 2b1e0
2b1e5: cmp eax, 1
2b1e8: mov eax, 0
2b1ed: jne 0x2b1fc
2b1ef: xor eax, eax
2b1f1: cmp dword ptr [esp + 0x32a0], 1
2b1f9: sete al
2b1fc: test eax, eax
2b1fe: jne 0x2b445
2b204: cmp dword ptr [0xbe305c], 0x1f9
2b20e: je 0x2b445
2b214: mov edx, dword ptr [0xc4ae50]
2b21a: mov eax, dword ptr [0xc4ae54]
2b21f: mov dword ptr [0xd2fba4], eax
2b224: mov dword ptr [0xd2fba0], edx
2b22a: movaps xmm0, xmmword ptr [esp + 0xb0]
2b232: mulss xmm0, dword ptr [0x74a288]
2b23a: addss xmm0, dword ptr [0x74a044]
2b242: cvttss2si esi, xmm0
2b246: mov edi, esi
2b248: sar edi, 0x1f
2b24b: subss xmm0, dword ptr [0x74a300]
2b253: cvttss2si ecx, xmm0
2b257: and ecx, edi
2b259: or ecx, esi
2b25b: mov dword ptr [esp], eax
2b25e: call 0x77850
2b263: mov eax, dword ptr [0xcf0edc]
2b268: test eax, eax
2b26a: je 0x2b2aa

CALL 2b4a2
2b4a7: cmp eax, 1
2b4aa: jne 0x2b577
2b4b0: mov ecx, dword ptr [esp + 0x32a0]
2b4b7: cmp ecx, 3
2b4ba: jb 0x2b577
2b4c0: cmp ecx, 0xb
2b4c3: ja 0x2b577
2b4c9: mov eax, dword ptr [0xbec5ac]
2b4ce: mov edx, 0x5c07c8
2b4d3: mov esi, 0x21
2b4d8: mov edi, dword ptr [esp + 0x32b0]
2b4df: not edi
2b4e1: cmp dword ptr [edx], ecx
2b4e3: jne 0x2b4ef
2b4e5: cmp dword ptr [edx + 4], eax
2b4e8: jne 0x2b4ef
2b4ea: test dword ptr [edx + 0x78], edi
2b4ed: je 0x2b567
2b4ef: sub edx, -0x80
2b4f2: dec esi
2b4f3: jne 0x2b4e1
2b4f5: add ecx, -3
2b4f8: cmp ecx, 8
2b4fb: ja 0x2b577
2b4fd: jmp dword ptr [ecx*4 + 0x1c0290]
2b504: xor ecx, ecx
2b506: cmp eax, 0xc
2b509: je 0x2b55e
2b50b: jmp 0x2b577
2b50d: mov ecx, 1
2b512: jmp 0x2b538
2b514: mov ecx, 2
2b519: jmp 0x2b538
2b51b: mov ecx, 3
2b520: cmp eax, 0x2a
2b523: je 0x2b55e
2b525: jmp 0x2b577
2b527: mov ecx, 4

CALL 2b58c
2b591: cmp eax, 1
2b594: jne 0x2b623
2b59a: cmp dword ptr [esp + 0x32a0], 1
2b5a2: jne 0x2b623
2b5a4: mov ecx, edi
2b5a6: call 0x93ab0
2b5ab: cmp dword ptr [esp + 0x32b0], 0
2b5b3: mov ecx, 0x28
2b5b8: cmovns ecx, eax
2b5bb: test edi, edi
2b5bd: cmovne ecx, eax
2b5c0: test ecx, ecx
2b5c2: je 0x2b623
2b5c4: mov eax, dword ptr [esp + 0x32a8]
2b5cb: test eax, eax
2b5cd: je 0x2b5d3
2b5cf: cmp eax, ecx
2b5d1: jne 0x2b623
2b5d3: mov ecx, esi
2b5d5: lea edx, [esp + 0x1670]
2b5dc: call 0x919b0
2b5e1: cmp eax, 1
2b5e4: jne 0x2b623
2b5e6: test byte ptr [esp + 0x1680], 1
2b5ee: jne 0x2b623
2b5f0: mov ecx, esi
2b5f2: lea edx, [esp + 0x32a0]
2b5f9: call 0x919b0
2b5fe: cmp eax, 1
2b601: jne 0x2b623
2b603: cmp dword ptr [esp + 0x32a0], 1
2b60b: jne 0x2b623
2b60d: or byte ptr [esp + 0x32b0], 1
2b615: mov ecx, esi

CALL 2b5dc
2b5e1: cmp eax, 1
2b5e4: jne 0x2b623
2b5e6: test byte ptr [esp + 0x1680], 1
2b5ee: jne 0x2b623
2b5f0: mov ecx, esi
2b5f2: lea edx, [esp + 0x32a0]
2b5f9: call 0x919b0
2b5fe: cmp eax, 1
2b601: jne 0x2b623
2b603: cmp dword ptr [esp + 0x32a0], 1
2b60b: jne 0x2b623
2b60d: or byte ptr [esp + 0x32b0], 1
2b615: mov ecx, esi
2b617: lea edx, [esp + 0x32a0]
2b61e: call 0x91cc0
2b623: mov esi, dword ptr [0xd34020]
2b629: test esi, esi
2b62b: je 0x2b73a
2b631: mov ecx, esi
2b633: lea edx, [esp + 0x32a0]
2b63a: call 0x919b0
2b63f: cmp eax, 1
2b642: jne 0x2b73a
2b648: mov eax, dword ptr [esp + 0x32a0]
2b64f: cmp eax, 2
2b652: ja 0x2b73a
2b658: cmp dword ptr [0xbec5ac], 0
2b65f: jne 0x2b73a

CALL 2b5f9
2b5fe: cmp eax, 1
2b601: jne 0x2b623
2b603: cmp dword ptr [esp + 0x32a0], 1
2b60b: jne 0x2b623
2b60d: or byte ptr [esp + 0x32b0], 1
2b615: mov ecx, esi
2b617: lea edx, [esp + 0x32a0]
2b61e: call 0x91cc0
2b623: mov esi, dword ptr [0xd34020]
2b629: test esi, esi
2b62b: je 0x2b73a
2b631: mov ecx, esi
2b633: lea edx, [esp + 0x32a0]
2b63a: call 0x919b0
2b63f: cmp eax, 1
2b642: jne 0x2b73a
2b648: mov eax, dword ptr [esp + 0x32a0]
2b64f: cmp eax, 2
2b652: ja 0x2b73a
2b658: cmp dword ptr [0xbec5ac], 0
2b65f: jne 0x2b73a
2b665: cmp dword ptr [0xd33ffc], 0xbde5e0
2b66f: jne 0x2b685
2b671: cmp dword ptr [0xd34004], esi
2b677: jne 0x2b685
2b679: cmp dword ptr [0xd34000], 0xceeba4
2b683: je 0x2b6d5

CALL 2b63a
2b63f: cmp eax, 1
2b642: jne 0x2b73a
2b648: mov eax, dword ptr [esp + 0x32a0]
2b64f: cmp eax, 2
2b652: ja 0x2b73a
2b658: cmp dword ptr [0xbec5ac], 0
2b65f: jne 0x2b73a
2b665: cmp dword ptr [0xd33ffc], 0xbde5e0
2b66f: jne 0x2b685
2b671: cmp dword ptr [0xd34004], esi
2b677: jne 0x2b685
2b679: cmp dword ptr [0xd34000], 0xceeba4
2b683: je 0x2b6d5
2b685: call 0x91880
2b68a: mov dword ptr [esp + 8], 0x24
2b692: mov dword ptr [esp + 4], 0
2b69a: mov dword ptr [esp], 0xd33ffc
2b6a1: call 0x137420
2b6a6: mov dword ptr [0xd33ffc], 0xbde5e0
2b6b0: mov dword ptr [0xd34000], 0xceeba4
2b6ba: mov dword ptr [0xd34004], esi

CALL 2b87d
2b882: cmp eax, 1
2b885: jne 0x2bba3
2b88b: mov eax, dword ptr [esp + 0x1670]
2b892: mov ecx, dword ptr [esp + 0x1684]
2b899: cmp eax, dword ptr [0xbda944]
2b89f: jne 0x2b8ad
2b8a1: cmp ecx, dword ptr [0xbda940]
2b8a7: je 0x2bba3
2b8ad: mov dword ptr [0xbda944], eax
2b8b2: mov dword ptr [0xbda940], ecx
2b8b8: cmp dword ptr [0xd42a2c], 0
2b8bf: je 0x2bba3
2b8c5: mov ecx, dword ptr [0xd42a28]
2b8cb: lea edx, [esp + 0x32a0]
2b8d2: call 0x919b0
2b8d7: cmp eax, 1
2b8da: jne 0x2bba3
2b8e0: mov eax, dword ptr [esp + 0x32a0]
2b8e7: cmp eax, dword ptr [0xd42a3c]
2b8ed: jne 0x2bba3
2b8f3: mov eax, dword ptr [esp + 0x32b4]
2b8fa: cmp eax, dword ptr [0xd42a34]
2b900: jae 0x2bba3

CALL 2b8d2
2b8d7: cmp eax, 1
2b8da: jne 0x2bba3
2b8e0: mov eax, dword ptr [esp + 0x32a0]
2b8e7: cmp eax, dword ptr [0xd42a3c]
2b8ed: jne 0x2bba3
2b8f3: mov eax, dword ptr [esp + 0x32b4]
2b8fa: cmp eax, dword ptr [0xd42a34]
2b900: jae 0x2bba3
2b906: mov ecx, dword ptr [0xd42a2c]
2b90c: shl eax, 5
2b90f: mov eax, dword ptr [ecx + eax + 0x2c]
2b913: mov dword ptr [esp + 0x130], eax
2b91a: cmp eax, 0xff
2b91f: jbe 0x2bba3
2b925: mov ecx, dword ptr [0xd42a28]
2b92b: lea edx, [esp + 0x32a0]
2b932: call 0x919b0
2b937: mov dword ptr [esp + 0x40], 0xbd8d09
2b93f: cmp eax, 1
2b942: jne 0x2b97b
2b944: mov eax, dword ptr [esp + 0x32a0]
2b94b: cmp eax, dword ptr [0xd42a3c]
2b951: jne 0x2b97b
2b953: mov eax, dword ptr [esp + 0x32b4]

CALL 2b932
2b937: mov dword ptr [esp + 0x40], 0xbd8d09
2b93f: cmp eax, 1
2b942: jne 0x2b97b
2b944: mov eax, dword ptr [esp + 0x32a0]
2b94b: cmp eax, dword ptr [0xd42a3c]
2b951: jne 0x2b97b
2b953: mov eax, dword ptr [esp + 0x32b4]
2b95a: cmp eax, dword ptr [0xd42a34]
2b960: jae 0x2b97b
2b962: mov ecx, dword ptr [0xd42a2c]
2b968: mov edx, dword ptr [0xd42a38]
2b96e: add edx, ecx
2b970: shl eax, 5
2b973: add edx, dword ptr [ecx + eax + 0x14]
2b977: mov dword ptr [esp + 0x40], edx
2b97b: mov eax, dword ptr [esp + 0x40]
2b97f: mov dword ptr [esp], eax
2b982: mov dword ptr [esp + 4], 0xa4788e
2b98a: call 0x1378a0
2b98f: test eax, eax
2b991: je 0x2baff
2b997: cmp dword ptr [0xd34008], 0
2b99e: je 0x2ba3a
2b9a4: mov eax, dword ptr [esp + 0x40]
2b9a8: mov dword ptr [esp], eax
2b9ab: mov dword ptr [esp + 4], 0xacdd02
2b9b3: call 0x1378a0
2b9b8: test eax, eax

CALL 2d06a
2d06f: cmp eax, 1
2d072: jne 0x2e1f4
2d078: mov ecx, dword ptr [esp + 0x1670]
2d07f: mov eax, ecx
2d081: mov dword ptr [esp + 0x40], ecx
2d085: cmp ecx, 0xc
2d088: jb 0x2d2bf
2d08e: mov edi, dword ptr [0xd424c8]
2d094: mov eax, dword ptr [0xd424c0]
2d099: mov dword ptr [esp + 0x1d0], eax
2d0a0: cmp esi, 0x6d
2d0a3: ja 0x2d3c3
2d0a9: mov eax, dword ptr [edi + 0x7c]
2d0ac: mov edx, 0xb90c85
2d0b1: test dword ptr [esp + 0x1680], eax
2d0b8: jne 0x2df35
2d0be: jmp 0x2d9c9
2d0c3: mov ecx, dword ptr [0xbec5ac]
2d0c9: cmp ecx, 0x1ee
2d0cf: mov eax, dword ptr [0xbe30b0]
2d0d4: jne 0x2d1b8
2d0da: test eax, eax
2d0dc: jle 0x2d1b8
2d0e2: mov edi, 0xffffff20
2d0e7: movss xmm2, dword ptr [edi + 0x5dd388]

CALL 2d280
2d285: cmp eax, 1
2d288: jne 0x2d999
2d28e: mov eax, dword ptr [esp + 0x1670]
2d295: cmp eax, 2
2d298: ja 0x2d999
2d29e: test eax, eax
2d2a0: je 0x2d57f
2d2a6: mov dword ptr [esp + 0x130], 0
2d2b1: cmp esi, 3
2d2b4: jbe 0x2d588
2d2ba: jmp 0x2e1f4
2d2bf: cmp dword ptr [esp + 0x40], 6
2d2c4: jb 0x2d5d9
2d2ca: cmp esi, 0x6e
2d2cd: jb 0x2d9c9
2d2d3: mov eax, dword ptr [0xd424c8]
2d2d8: lea ebx, [esi - 0x6e]
2d2db: cmp ebx, dword ptr [eax + 0x5c]
2d2de: jae 0x2e1f4
2d2e4: xor eax, eax
2d2e6: mov ecx, dword ptr [esp + 0x40]
2d2ea: cmp ecx, 9
2d2ed: sete al
2d2f0: cmp ecx, 6
2d2f3: lea eax, [eax + eax + 7]
2d2f7: mov ecx, 9
2d2fc: cmove eax, ecx
2d2ff: cmp dword ptr [esp + 0x1684], eax
2d306: jne 0x2d635

CALL 2d674
2d679: cmp eax, 1
2d67c: jne 0x2e1f4
2d682: mov eax, dword ptr [esp + 0x40]
2d686: cmp dword ptr [esp + 0x32a0], eax
2d68d: jne 0x2e1f4
2d693: mov eax, 1
2d698: mov ecx, ebx
2d69a: shl eax, cl
2d69c: or dword ptr [esp + 0x32b0], eax
2d6a3: mov ecx, edi
2d6a5: lea edx, [esp + 0x32a0]
2d6ac: call 0x91cc0
2d6b1: test eax, eax
2d6b3: je 0x2e1f4
2d6b9: mov eax, 0xbb6d78
2d6be: cmp dword ptr [esp + 0x1670], 9
2d6c6: je 0x2df12
2d6cc: mov eax, dword ptr [esi*4 + 0x5dcd80]
2d6d3: jmp 0x2df12
2d6d8: mov eax, dword ptr [0xd424c0]
2d6dd: mov dword ptr [esp], eax
2d6e0: mov dword ptr [esp + 4], 0xb514b9
2d6e8: call 0x74540
2d6ed: jmp 0x2e1f4
2d6f2: mov eax, dword ptr [0xd424c0]
2d6f7: mov dword ptr [esp], eax

CALL 2d962
2d967: cmp eax, 1
2d96a: jne 0x2d999
2d96c: cmp dword ptr [esp + 0x32a0], 0
2d974: jne 0x2d999
2d976: or byte ptr [esp + 0x32b0], 2
2d97e: mov ecx, esi
2d980: lea edx, [esp + 0x32a0]
2d987: call 0x91cc0
2d98c: mov ecx, 0xba5935
2d991: test eax, eax
2d993: jne 0x2de62
2d999: mov dword ptr [esp + 0x130], 0
2d9a4: jmp 0x2e1f4
2d9a9: mov dword ptr [esp], eax
2d9ac: mov dword ptr [esp + 4], 0xb7ea13
2d9b4: jmp 0x2de69
2d9b9: mov ecx, 2
2d9be: mov dword ptr [0xd42a50], ecx
2d9c4: jmp 0x2e1f4
2d9c9: mov ecx, dword ptr [0xd34020]
2d9cf: call 0xf7e30
2d9d4: test eax, eax
2d9d6: je 0x2de7e
2d9dc: call 0xc9a70
2d9e1: cmp eax, 3
2d9e4: jne 0x2e1f4

CALL 2d9f7
2d9fc: cmp eax, 1
2d9ff: jne 0x2da27
2da01: lea ecx, [esp + 0x32a0]
2da08: call 0xf8140
2da0d: mov ecx, dword ptr [0xd424c0]
2da13: mov dword ptr [esp + 8], eax
2da17: mov dword ptr [esp], ecx
2da1a: mov dword ptr [esp + 4], 0xa451a1
2da22: call 0x74540
2da27: mov eax, dword ptr [0xd42a2c]
2da2c: mov dword ptr [esp], eax
2da2f: call 0x133f30
2da34: mov dword ptr [esp + 8], 0x1c
2da3c: mov dword ptr [esp + 4], 0
2da44: mov dword ptr [esp], 0xd42a28
2da4b: call 0x137420
2da50: mov dword ptr [esp + 8], 0x450
2da58: mov dword ptr [esp + 4], 0
2da60: mov dword ptr [esp], 0xd42a28
2da67: call 0x137420
2da6c: jmp 0x2e1f4
2da71: cmp dword ptr [esp + 0x1684], 7
2da79: jne 0x2de98
2da7f: xor ecx, ecx

CALL 2dec1
2dec6: cmp eax, 1
2dec9: jne 0x2dfa1
2decf: mov eax, dword ptr [esp + 0x40]
2ded3: cmp dword ptr [esp + 0x32a0], eax
2deda: jne 0x2dfa1
2dee0: or dword ptr [esp + 0x32b0], edi
2dee7: mov ecx, esi
2dee9: lea edx, [esp + 0x32a0]
2def0: call 0x91cc0
2def5: test eax, eax
2def7: je 0x2dfa1
2defd: cmp dword ptr [esp + 0x1670], 3
2df05: mov eax, 0xb6d9b8
2df0a: mov ecx, 0xbb6c10
2df0f: cmove eax, ecx
2df12: mov ecx, dword ptr [0xd424c0]
2df18: mov dword ptr [esp + 4], eax
2df1c: mov dword ptr [esp], ecx
2df1f: call 0x74540
2df24: jmp 0x2e1f4
2df29: mov edx, 0xb7e9e2
2df2e: jmp 0x2df35
2df30: mov edx, 0xb829a1
2df35: mov dword ptr [esp + 4], edx
2df39: mov eax, dword ptr [esp + 0x1d0]
2df40: mov dword ptr [esp], eax
2df43: call 0x74540
2df48: jmp 0x2e1f4

CALL 2f39f
2f3a4: cmp eax, 1
2f3a7: jne 0x2f3b7
2f3a9: cmp dword ptr [esp + 0x32a0], 1
2f3b1: je 0x2f43a
2f3b7: cmp dword ptr [0xbe305c], 0x1f9
2f3c1: je 0x2f43a
2f3c3: cmp byte ptr [esp + 0x31c], 0
2f3cb: xorps xmm0, xmm0
2f3ce: xorps xmm1, xmm1
2f3d1: jne 0x2f41c
2f3d3: movaps xmm4, xmmword ptr [esp + 0xf0]
2f3db: movss xmm0, dword ptr [esp + 0x70]
2f3e1: divss xmm4, xmm0
2f3e5: movaps xmm3, xmmword ptr [esp + 0x40]
2f3ea: divss xmm3, xmm0
2f3ee: movaps xmm0, xmmword ptr [esp + 0x140]
2f3f6: movaps xmm1, xmm0
2f3f9: mulss xmm1, xmm4
2f3fd: movaps xmm2, xmmword ptr [esp + 0x200]
2f405: mulss xmm4, xmm2
2f409: mulss xmm0, xmm3
2f40d: subss xmm0, xmm4
2f411: mulss xmm3, xmm2
2f415: addss xmm3, xmm1
2f419: movaps xmm1, xmm3
2f41c: movaps xmm2, xmmword ptr [esp + 0xb0]
2f424: movss dword ptr [esp], xmm2

CALL 2f468
2f46d: cmp eax, 1
2f470: jne 0x2f480
2f472: cmp dword ptr [esp + 0x32a0], 1
2f47a: je 0x2fcec
2f480: cmp dword ptr [0xbe305c], 0x1f9
2f48a: je 0x2fcec
2f490: cmp dword ptr [0xd34008], 0
2f497: je 0x2fcec
2f49d: mov eax, dword ptr [0xd33ffc]
2f4a2: mov dword ptr [esp + 0xf0], eax
2f4a9: mov ecx, dword ptr [0xd34004]
2f4af: lea edx, [esp + 0x1030]
2f4b6: call 0x919b0
2f4bb: cmp eax, 1
2f4be: jne 0x2f4dc
2f4c0: mov eax, dword ptr [esp + 0x1030]
2f4c7: cmp eax, 2
2f4ca: ja 0x2f4dc
2f4cc: mov ecx, dword ptr [esp + 0xf0]
2f4d3: cmp dword ptr [ecx + 0xdfcc], 0
2f4da: je 0x2f52c
2f4dc: call 0x91880
2f4e1: mov dword ptr [esp + 8], 0x24
2f4e9: mov dword ptr [esp + 4], 0

CALL 2f4b6
2f4bb: cmp eax, 1
2f4be: jne 0x2f4dc
2f4c0: mov eax, dword ptr [esp + 0x1030]
2f4c7: cmp eax, 2
2f4ca: ja 0x2f4dc
2f4cc: mov ecx, dword ptr [esp + 0xf0]
2f4d3: cmp dword ptr [ecx + 0xdfcc], 0
2f4da: je 0x2f52c
2f4dc: call 0x91880
2f4e1: mov dword ptr [esp + 8], 0x24
2f4e9: mov dword ptr [esp + 4], 0
2f4f1: mov dword ptr [esp], 0xd33ffc
2f4f8: call 0x137420
2f4fd: jmp 0x2fcec
2f502: call 0x7ff50
2f507: xorps xmm0, xmm0
2f50a: movss dword ptr [esp + 0x430], xmm0
2f513: xor eax, eax
2f515: movss dword ptr [esp + 0x324], xmm0
2f51e: movss dword ptr [esp + 0x320], xmm0
2f527: jmp 0x355ba
2f52c: test eax, eax
2f52e: jne 0x2fcec
2f534: mov eax, dword ptr [esp + 0xf0]
2f53b: cmp dword ptr [eax + 0x4ad0], 0

CALL 2f55e
2f563: cmp eax, 1
2f566: jne 0x2fcec
2f56c: cmp dword ptr [esp + 0x32a0], 0
2f574: jne 0x2fcec
2f57a: mov eax, dword ptr [esp + 0x32b0]
2f581: or eax, dword ptr [0xd34010]
2f587: mov ecx, eax
2f589: not ecx
2f58b: mov edx, eax
2f58d: or edx, 4
2f590: test cl, 0x18
2f593: cmovne edx, eax
2f596: mov dword ptr [esp + 0x32b0], edx
2f59d: mov ecx, dword ptr [0xd34004]
2f5a3: lea edx, [esp + 0x32a0]
2f5aa: call 0x91cc0
2f5af: test eax, eax
2f5b1: je 0x2fcec
2f5b7: mov dword ptr [0xd34010], 0
2f5c1: cmp dword ptr [0xd34008], 0
2f5c8: je 0x2fb6e
2f5ce: mov ecx, dword ptr [0xd34004]
2f5d4: lea edx, [esp + 0x1670]
2f5db: call 0x919b0
2f5e0: cmp eax, 1
2f5e3: jne 0x2fb6e

CALL 2f5db
2f5e0: cmp eax, 1
2f5e3: jne 0x2fb6e
2f5e9: cmp dword ptr [esp + 0x1670], 0
2f5f1: jne 0x2fb6e
2f5f7: cmp dword ptr [esp + 0x1684], 5
2f5ff: jne 0x2fb6e
2f605: test byte ptr [esp + 0x1680], 4
2f60d: jne 0x2fb6e
2f613: mov eax, dword ptr [0xd33ffc]
2f618: mov dword ptr [esp + 0x90], eax
2f61f: cmp dword ptr [eax + 0x4ad0], 0
2f626: jle 0x2fb6e
2f62c: mov eax, dword ptr [0xd34000]
2f631: mov dword ptr [esp + 0x40], eax
2f635: mov eax, dword ptr [esp + 0x90]
2f63c: movss xmm0, dword ptr [eax + 0x4aa0]
2f644: addss xmm0, dword ptr [0x74a468]
2f64c: movss xmm1, dword ptr [eax + 0x4aa4]
2f654: addss xmm1, dword ptr [0x74a46c]
2f65c: mulss xmm1, xmm1
2f660: mulss xmm0, xmm0

CALL 2fcad
2fcb2: cmp eax, 1
2fcb5: jne 0x2fcec
2fcb7: cmp dword ptr [esp + 0x32a0], 0
2fcbf: jne 0x2fcec
2fcc1: or byte ptr [esp + 0x32b0], 1
2fcc9: mov ecx, esi
2fccb: lea edx, [esp + 0x32a0]
2fcd2: call 0x91cc0
2fcd7: test eax, eax
2fcd9: je 0x2fcec
2fcdb: mov dword ptr [0xd3400c], 0
2fce5: jmp 0x2fcec
2fce7: call 0x91880
2fcec: call 0xc9a70
2fcf1: cmp eax, 6
2fcf4: ja 0x2fd04
2fcf6: mov ecx, 0x56
2fcfb: bt ecx, eax
2fcfe: jae 0x2fd04
2fd00: mov al, 1
2fd02: jmp 0x2fd4d
2fd04: cmp eax, 3
2fd07: jne 0x2fd40
2fd09: mov ecx, dword ptr [0xd42a28]
2fd0f: test ecx, ecx
2fd11: je 0x2fd40
2fd13: lea edx, [esp + 0x32a0]
2fd1a: call 0x919b0
2fd1f: cmp eax, 1
2fd22: jne 0x2fd40
2fd24: cmp dword ptr [esp + 0x32a0], 1
2fd2c: sete cl
2fd2f: cmp dword ptr [0xbe305c], 0x1f9

CALL 2fd1a
2fd1f: cmp eax, 1
2fd22: jne 0x2fd40
2fd24: cmp dword ptr [esp + 0x32a0], 1
2fd2c: sete cl
2fd2f: cmp dword ptr [0xbe305c], 0x1f9
2fd39: sete al
2fd3c: or al, cl
2fd3e: jmp 0x2fd4d
2fd40: cmp dword ptr [0xbe305c], 0x1f9
2fd4a: sete al
2fd4d: movzx edx, al
2fd50: mov ecx, dword ptr [0xd34020]
2fd56: call 0x80190
2fd5b: call 0x80660
2fd60: call 0xc9a70
2fd65: cmp eax, 6
2fd68: ja 0x2fd78
2fd6a: mov ecx, 0x56
2fd6f: bt ecx, eax
2fd72: jb 0x350a9
2fd78: cmp eax, 3
2fd7b: jne 0x2fda6
2fd7d: mov ecx, dword ptr [0xd42a28]
2fd83: test ecx, ecx
2fd85: je 0x2fda6
2fd87: lea edx, [esp + 0x32a0]
2fd8e: call 0x919b0
2fd93: cmp eax, 1
2fd96: jne 0x2fda6
2fd98: cmp dword ptr [esp + 0x32a0], 1
2fda0: je 0x350a9

CALL 2fd8e
2fd93: cmp eax, 1
2fd96: jne 0x2fda6
2fd98: cmp dword ptr [esp + 0x32a0], 1
2fda0: je 0x350a9
2fda6: xorps xmm0, xmm0
2fda9: ucomiss xmm0, dword ptr [esp + 0xb0]
2fdb1: jae 0x350a9
2fdb7: cmp dword ptr [0xbe305c], 0x1f9
2fdc1: je 0x350a9
2fdc7: movaps xmm0, xmmword ptr [esp + 0xb0]
2fdcf: movss dword ptr [esp], xmm0
2fdd4: call 0x132b30
2fdd9: test eax, 0x100
2fdde: jne 0x350a9
2fde4: cmp dword ptr [0xd424d4], 0
2fdeb: je 0x350a9
2fdf1: cmp dword ptr [0xbe30b0], 0
2fdf8: jle 0x35051
2fdfe: mov dword ptr [esp + 0x70], 0
2fe06: imul edi, dword ptr [esp + 0x70], 0x38
2fe0b: cmp dword ptr [edi + 0xd42514], 0
2fe12: je 0x303df

CALL 350d7
350dc: cmp eax, 1
350df: jne 0x350fd
350e1: cmp dword ptr [esp + 0x32a0], 1
350e9: sete cl
350ec: cmp dword ptr [0xbe305c], 0x1f9
350f6: sete al
350f9: or al, cl
350fb: jmp 0x3510a
350fd: cmp dword ptr [0xbe305c], 0x1f9
35107: sete al
3510a: movzx ecx, al
3510d: movaps xmm0, xmmword ptr [esp + 0xb0]
35115: movss dword ptr [esp], xmm0
3511a: call 0x81360
3511f: call 0xc9a70
35124: cmp eax, 6
35127: ja 0x35137
35129: mov ecx, 0x56
3512e: bt ecx, eax
35131: jb 0x35281
35137: xor ebx, ebx
35139: cmp eax, 3
3513c: jne 0x35166
3513e: mov ecx, dword ptr [0xd42a28]
35144: test ecx, ecx
35146: je 0x35166
35148: lea edx, [esp + 0x32a0]
3514f: call 0x919b0
35154: cmp eax, 1
35157: jne 0x35166
35159: xor ebx, ebx
3515b: cmp dword ptr [esp + 0x32a0], 1

CALL 3514f
35154: cmp eax, 1
35157: jne 0x35166
35159: xor ebx, ebx
3515b: cmp dword ptr [esp + 0x32a0], 1
35163: sete bl
35166: test ebx, ebx
35168: jne 0x35281
3516e: cmp dword ptr [0xbe305c], 0x1f9
35178: je 0x35281
3517e: mov ecx, dword ptr [0xd34020]
35184: test ecx, ecx
35186: je 0x35281
3518c: lea edx, [esp + 0x1670]
35193: call 0x919b0
35198: cmp eax, 1
3519b: jne 0x35281
351a1: mov eax, dword ptr [esp + 0x1670]
351a8: test eax, eax
351aa: je 0x35281
351b0: cmp eax, 0x24
351b3: ja 0x35281
351b9: mov ecx, dword ptr [0xd34020]
351bf: test ecx, ecx
351c1: je 0x351ec
351c3: lea edx, [esp + 0x32a0]
351ca: call 0x919b0
351cf: cmp eax, 1
351d2: jne 0x351ec

CALL 35193
35198: cmp eax, 1
3519b: jne 0x35281
351a1: mov eax, dword ptr [esp + 0x1670]
351a8: test eax, eax
351aa: je 0x35281
351b0: cmp eax, 0x24
351b3: ja 0x35281
351b9: mov ecx, dword ptr [0xd34020]
351bf: test ecx, ecx
351c1: je 0x351ec
351c3: lea edx, [esp + 0x32a0]
351ca: call 0x919b0
351cf: cmp eax, 1
351d2: jne 0x351ec
351d4: cmp dword ptr [esp + 0x32a0], 0x24
351dc: jne 0x351ec
351de: cmp dword ptr [esp + 0x32b0], 0
351e6: js 0x35281
351ec: mov ecx, dword ptr [0xd34020]
351f2: lea edx, [esp + 0x32a0]
351f9: call 0x92ae0
351fe: test eax, eax
35200: js 0x35281
35202: mov eax, dword ptr [esp + 0x32ac]
35209: cmp eax, dword ptr [esp + 0x1670]
35210: jae 0x35281
35212: mov esi, dword ptr [eax*4 + 0x5e59ec]
35219: mov edi, esi
3521b: shr edi, 0x1f

CALL 351ca
351cf: cmp eax, 1
351d2: jne 0x351ec
351d4: cmp dword ptr [esp + 0x32a0], 0x24
351dc: jne 0x351ec
351de: cmp dword ptr [esp + 0x32b0], 0
351e6: js 0x35281
351ec: mov ecx, dword ptr [0xd34020]
351f2: lea edx, [esp + 0x32a0]
351f9: call 0x92ae0
351fe: test eax, eax
35200: js 0x35281
35202: mov eax, dword ptr [esp + 0x32ac]
35209: cmp eax, dword ptr [esp + 0x1670]
35210: jae 0x35281
35212: mov esi, dword ptr [eax*4 + 0x5e59ec]
35219: mov edi, esi
3521b: shr edi, 0x1f
3521e: add edi, esi
35220: sar edi, 1
35222: inc eax
35223: movss xmm0, dword ptr [0xbe3084]
3522b: movss xmm1, dword ptr [0xbe3080]
35233: mov dword ptr [esp + 0xc], eax
35237: movss dword ptr [esp + 8], xmm0
3523d: movss dword ptr [esp + 4], xmm1
35243: mov dword ptr [esp], edi
35246: mov ecx, 0xbde5e0
3524b: mov edx, esi
3524d: call 0x92470
35252: test eax, eax
35254: je 0x35281

CALL 35595
3559a: cmp eax, 1
3559d: jne 0x355ad
3559f: cmp dword ptr [esp + 0x32a0], 1
355a7: jne 0x355ad
355a9: xor eax, eax
355ab: jmp 0x355ba
355ad: cmp dword ptr [0xbe305c], 0x1f9
355b7: setne al
355ba: mov edi, dword ptr [esp + 0x434]
355c1: test edi, edi
355c3: sete dl
355c6: mov ecx, dword ptr [0xbe30b0]
355cc: test ecx, ecx
355ce: setle dh
355d1: or dh, dl
355d3: mov esi, dword ptr [esp + 0x6d0]
355da: cmp dword ptr [0xbec5ac], esi
355e0: setne dl
355e3: or dl, dh
355e5: mov edx, edi
355e7: mov esi, 0
355ec: cmovne edx, esi
355ef: jne 0x3563b
355f1: test al, al
355f3: je 0x3563b
355f5: movss xmm0, dword ptr [esp + 0x5e0]
355fe: subss xmm0, dword ptr [esp + 0xb0]
35607: movss dword ptr [esp + 0x5e0], xmm0
35610: ucomiss xmm0, dword ptr [0x74a9e0]
35617: ja 0x35642
35619: mov ecx, 0x14

CALL 3e068
3e06d: cmp eax, 1
3e070: jne 0x3e07f
3e072: xor ebx, ebx
3e074: cmp dword ptr [esp + 0x1670], 1
3e07c: sete bl
3e07f: mov dword ptr [0xd36104], ebx
3e085: mov dword ptr [0xbda13c], 0xffffffff
3e08f: mov dword ptr [0xbda140], 0xffffffff
3e099: mov dword ptr [0xbda144], 0xffffffff
3e0a3: mov dword ptr [0xbda148], 0xffffffff
3e0ad: cmp dword ptr [0xd34008], 0
3e0b4: je 0x3e2cc
3e0ba: cmp dword ptr [0xbda9d4], 0
3e0c1: je 0x3e64d
3e0c7: lea ebx, [esp + 0x25c]
3e0ce: mov dword ptr [esp + 0x2c], ebx
3e0d2: lea esi, [esp + 0x32a0]
3e0d9: mov dword ptr [esp + 0x28], esi
3e0dd: movaps xmm0, xmmword ptr [esp + 0x1f0]
3e0e5: movss dword ptr [esp + 8], xmm0
3e0eb: movaps xmm0, xmmword ptr [esp + 0x140]

CALL 3ef06
3ef0b: cmp eax, 1
3ef0e: jne 0x3ef1d
3ef10: xor ebx, ebx
3ef12: cmp dword ptr [esp + 0x1670], 1
3ef1a: sete bl
3ef1d: mov dword ptr [0xe42610], ebx
3ef23: cmp dword ptr [0xbda9d8], 0
3ef2a: je 0x3f05a
3ef30: test ebx, ebx
3ef32: je 0x3f0c0
3ef38: cmp dword ptr [0xe42614], 0
3ef3f: je 0x3ef83
3ef41: call 0x12ebd0
3ef46: test eax, eax
3ef48: jne 0x3ef41
3ef4a: mov eax, dword ptr [0xe42614]
3ef4f: mov dword ptr [esp], eax
3ef52: call dword ptr [0xbd8f44]
3ef58: sub esp, 4
3ef5b: mov dword ptr [0xe42614], 0
3ef65: mov dword ptr [0xbdaa30], 0xffffffff
3ef6f: mov dword ptr [0xbdaa2c], 0xffffffff
3ef79: mov dword ptr [0xbdaa28], 0xffffffff
3ef83: call 0xc9a70
3ef88: cmp eax, 1
3ef8b: jne 0x3f5ea

CALL 3efab
3efb0: mov dword ptr [esp + 0x60], 0
3efb8: cmp eax, 1
3efbb: jne 0x3efed
3efbd: mov eax, dword ptr [esp + 0x1670]
3efc4: cmp eax, dword ptr [0xd42a3c]
3efca: jne 0x3efed
3efcc: mov eax, dword ptr [esp + 0x1684]
3efd3: cmp eax, dword ptr [0xd42a34]
3efd9: jae 0x3efed
3efdb: mov ecx, dword ptr [0xd42a2c]
3efe1: shl eax, 5
3efe4: movzx eax, byte ptr [ecx + eax + 0x2c]
3efe9: mov dword ptr [esp + 0x60], eax
3efed: cmp dword ptr [0xd42a2c], 0
3eff4: je 0x3f592
3effa: mov ecx, dword ptr [0xd42a28]
3f000: lea edx, [esp + 0x1670]
3f007: call 0x919b0
3f00c: mov ebx, 0xbd8d09
3f011: cmp eax, 1
3f014: jne 0x3f597
3f01a: mov eax, dword ptr [esp + 0x1670]
3f021: cmp eax, dword ptr [0xd42a3c]
3f027: jne 0x3f597
3f02d: mov eax, dword ptr [esp + 0x1684]

CALL 3f007
3f00c: mov ebx, 0xbd8d09
3f011: cmp eax, 1
3f014: jne 0x3f597
3f01a: mov eax, dword ptr [esp + 0x1670]
3f021: cmp eax, dword ptr [0xd42a3c]
3f027: jne 0x3f597
3f02d: mov eax, dword ptr [esp + 0x1684]
3f034: cmp eax, dword ptr [0xd42a34]
3f03a: jae 0x3f597
3f040: mov ecx, dword ptr [0xd42a2c]
3f046: mov ebx, dword ptr [0xd42a38]
3f04c: add ebx, ecx
3f04e: shl eax, 5
3f051: add ebx, dword ptr [ecx + eax + 0x14]
3f055: jmp 0x3f597
3f05a: cmp dword ptr [0xd395fc], 0
3f061: je 0x3f07d
3f063: call 0x12ebd0
3f068: test eax, eax
3f06a: jne 0x3f063
3f06c: mov eax, dword ptr [0xd395fc]
3f071: mov dword ptr [esp], eax
3f074: call dword ptr [0xbd8f44]
3f07a: sub esp, 4
3f07d: mov dword ptr [0xd395fc], 0
3f087: mov dword ptr [0xbda100], 0xffffffff

CALL 4570e
45713: cmp eax, 1
45716: jne 0x45dd1
4571c: cmp dword ptr [esp + 0x1670], 0
45724: jne 0x45dd1
4572a: test byte ptr [esp + 0x1680], 2
45732: jne 0x45dd1
45738: cmp dword ptr [0xd34050], 0
4573f: je 0x457b8
45741: cmp dword ptr [0xd3404c], 0
45748: je 0x457b8
4574a: mov dword ptr [esp], 0x44b98000
45751: call 0x132b30
45756: test eax, 0x100
4575b: jne 0x45dd1
45761: mov dword ptr [esp], 0x452e4000
45768: call 0x132b30
4576d: test eax, 0x100
45772: jne 0x45dd1
45778: mov eax, dword ptr [0xd34040]
4577d: cmp eax, 0xba
45782: jb 0x45dd1
45788: cmp dword ptr [0xd34044], 0x15d
45792: jb 0x45dd1

CALL 45dde
45de3: cmp eax, 1
45de6: jne 0x45e40
45de8: cmp dword ptr [esp + 0x1670], 9
45df0: jb 0x45e40
45df2: cmp byte ptr [esp + 0x1688], 0
45dfa: je 0x45e40
45dfc: cmp dword ptr [0xbec5ac], 0x84
45e06: jne 0x45e40
45e08: movss xmm0, dword ptr [esp + 0x158]
45e11: movss dword ptr [esp + 4], xmm0
45e17: movaps xmm0, xmmword ptr [esp + 0x1f0]
45e1f: movss dword ptr [esp], xmm0
45e24: mov dword ptr [esp + 0xc], 0x448b8000
45e2c: mov dword ptr [esp + 8], 0x433c0000
45e34: lea ecx, [esp + 0x190]
45e3b: call 0x117850
45e40: cmp dword ptr [0xd424cc], 0
45e47: je 0x45f2f
45e4d: mov esi, dword ptr [0xd424c8]
45e53: test esi, esi
45e55: je 0x45f2f
45e5b: mov ebx, 1
45e60: cmp dword ptr [esi], 5
45e63: jb 0x45e70
45e65: mov ebx, dword ptr [esi + 0x5c]
45e68: test ebx, ebx

CALL 5739a
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

CALL 573f6
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

CALL 5d5ac
5d5b1: cmp eax, 1
5d5b4: jne 0x5d646
5d5ba: mov eax, 0xac5ab9
5d5bf: cmp dword ptr [esp + 0x1670], 0
5d5c7: jne 0x5d702
5d5cd: jmp 0x5d646
5d5cf: shl esi, 4
5d5d2: mov eax, dword ptr [esi + eax - 0x618]
5d5d9: mov dword ptr [esp + 0xc], eax
5d5dd: mov dword ptr [esp + 8], 0xa44e63
5d5e5: mov dword ptr [esp + 4], 0x50
5d5ed: mov dword ptr [esp], 0xe54e7c
5d5f4: call 0x1377e0
5d5f9: mov eax, 0xe54e7c
5d5fe: jmp 0x5d702
5d603: cmp ecx, 3
5d606: mov eax, 0xa55aca
5d60b: mov ecx, 0xa48c05
5d610: jmp 0x5d6ff
5d615: cmp dword ptr [0xbec534], 0
5d61c: jne 0x5d725
5d622: call 0x7ee90
5d627: test eax, eax
5d629: je 0x5d652
5d62b: lea eax, [esp + 0x640]
5d632: mov dword ptr [esp], eax

CALL 6090d
60912: cmp eax, 1
60915: jne 0x62032
6091b: cmp dword ptr [esp + 0x1670], 1
60923: jne 0x62032
60929: cmp dword ptr [esp + 0x50], 6
6092e: jne 0x60ae1
60934: cmp dword ptr [0xd42a60], 0
6093b: je 0x60b10
60941: mov dword ptr [esp + 8], 0xffffffff
60949: mov dword ptr [esp + 4], 0x9c
60951: mov dword ptr [esp], 0x1a4
60958: mov ecx, 0x6e
6095d: mov edx, 0xa4
60962: call 0x837d0
60967: mov dword ptr [esp + 8], 0xff8999b2
6096f: mov dword ptr [esp + 4], 2
60977: mov dword ptr [esp], 0x1a4
6097e: mov ecx, 0x6e
60983: mov edx, 0xa4
60988: call 0x837d0
6098d: mov dword ptr [esp + 8], 0xff8999b2

CALL 60db0
60db5: mov esi, 0xbd8d09
60dba: cmp eax, 1
60dbd: jne 0x61118
60dc3: mov eax, dword ptr [esp + 0x1670]
60dca: cmp eax, dword ptr [0xd42a3c]
60dd0: jne 0x61118
60dd6: mov eax, dword ptr [esp + 0x1684]
60ddd: cmp eax, dword ptr [0xd42a34]
60de3: jae 0x61118
60de9: mov ecx, dword ptr [0xd42a2c]
60def: mov esi, dword ptr [0xd42a38]
60df5: add esi, ecx
60df7: shl eax, 5
60dfa: add esi, dword ptr [ecx + eax + 0x14]
60dfe: jmp 0x61118
60e03: add esi, 2
60e06: mov eax, dword ptr [esp + 0x50]
60e0a: mov ecx, 0xcccccccd
60e0f: mul ecx
60e11: shr edx, 3
60e14: imul eax, edx, 0x168
60e1a: mov ebx, dword ptr [esp + 0xb0]
60e21: sub ebx, eax
60e23: mov dword ptr [esp + 4], esi
60e27: mov dword ptr [esp], ebx
60e2a: mov dword ptr [esp + 0xc], 0xad8713
60e32: mov dword ptr [esp + 8], 0x3f4ccccd

CALL 6126b
61270: mov ecx, 0xbd8d09
61275: cmp eax, 1
61278: jne 0x612ad
6127a: mov eax, dword ptr [esp + 0x1670]
61281: cmp eax, dword ptr [0xd42a3c]
61287: jne 0x612ad
61289: mov eax, dword ptr [esp + 0x1684]
61290: cmp eax, dword ptr [0xd42a34]
61296: jae 0x612ad
61298: mov edx, dword ptr [0xd42a2c]
6129e: mov ecx, dword ptr [0xd42a38]
612a4: add ecx, edx
612a6: shl eax, 5
612a9: add ecx, dword ptr [edx + eax + 0x1c]
612ad: mov edx, 0x1e4
612b2: sub edx, ebx
612b4: mov dword ptr [esp + 8], ecx
612b8: mov dword ptr [esp + 4], 0x3f800000
612c0: mov dword ptr [esp], 0x16d
612c7: mov ecx, 0x88
612cc: call 0x96a30
612d1: xor eax, eax
612d3: cmp dword ptr [0xd42a48], 1
612da: sete al
612dd: mov edx, 0x1fe
612e2: sub edx, ebx
612e4: mov dword ptr [esp + 8], eax
612e8: mov dword ptr [esp + 4], 0x1c
612f0: mov dword ptr [esp], 0x17e

CALL 61317
6131c: cmp eax, 1
6131f: jne 0x61354
61321: mov eax, dword ptr [esp + 0x1670]
61328: cmp eax, dword ptr [0xd42a3c]
6132e: jne 0x61354
61330: mov eax, dword ptr [esp + 0x1684]
61337: cmp eax, dword ptr [0xd42a34]
6133d: jae 0x61354
6133f: mov ecx, dword ptr [0xd42a2c]
61345: mov edi, dword ptr [0xd42a38]
6134b: add edi, ecx
6134d: shl eax, 5
61350: add edi, dword ptr [ecx + eax + 0x20]
61354: mov edx, 0x202
61359: sub edx, ebx
6135b: mov dword ptr [esp + 8], edi
6135f: mov dword ptr [esp + 4], 0x3f800000
61367: mov dword ptr [esp], 0x16d
6136e: mov ecx, 0x88
61373: call 0x96a30
61378: mov dword ptr [esp + 0xc], 0xaa82a5
61380: jmp 0x62016
61385: imul esi, dword ptr [0xdb1bc8], 0x410
6138f: xor eax, eax
61391: cmp dword ptr [0xe28190], 0
61398: sete al
6139b: mov dword ptr [esp + 8], eax

CALL 62d72
62d77: mov dword ptr [esp + 0x40], 0
62d7f: cmp eax, 1
62d82: sete al
62d85: mov dword ptr [esp + 0x100], eax
62d8c: mov dword ptr [esp + 0x70], 0
62d94: jne 0x62e27
62d9a: mov eax, dword ptr [esp + 0x167c]
62da1: mov edx, eax
62da3: and edx, 1
62da6: mov ecx, eax
62da8: shr ecx, 1
62daa: and ecx, 1
62dad: bt eax, 2
62db1: adc ecx, edx
62db3: mov edx, eax
62db5: shr edx, 3
62db8: and edx, 1
62dbb: bt eax, 4
62dbf: adc edx, ecx
62dc1: mov ecx, eax
62dc3: shr ecx, 5
62dc6: and ecx, 1
62dc9: bt eax, 6
62dcd: adc ecx, edx
62dcf: mov edx, eax
62dd1: shr edx, 7
62dd4: and edx, 1
62dd7: bt eax, 8
62ddb: adc edx, ecx
62ddd: mov ecx, eax
62ddf: shr ecx, 9
62de2: and ecx, 1
62de5: bt eax, 0xa
62de9: adc ecx, edx
62deb: mov edx, eax
62ded: shr edx, 0xb
62df0: and edx, 1
62df3: bt eax, 0xc
62df7: adc edx, ecx
62df9: mov ecx, eax
62dfb: shr ecx, 0xd

CALL 67b76
67b7b: cmp eax, 1
67b7e: jne 0x67b8d
67b80: cmp dword ptr [esp], 0x24
67b84: jne 0x67b8d
67b86: cmp dword ptr [esp + 0x10], 0
67b8b: js 0x67bdf
67b8d: mov ecx, dword ptr [0xd34020]
67b93: mov edx, esp
67b95: call 0x919b0
67b9a: mov esi, 1
67b9f: test eax, eax
67ba1: je 0x67bdf
67ba3: js 0x67bcb
67ba5: mov edi, dword ptr [esp + 8]
67ba9: test edi, edi
67bab: je 0x67bdf
67bad: mov ecx, dword ptr [esp + 0x44]
67bb1: test ecx, ecx
67bb3: jne 0x67bba
67bb5: cmp edi, 0x28
67bb8: je 0x67bdf
67bba: cmp ecx, 0x21
67bbd: jne 0x67be7
67bbf: mov ecx, 0xb9f4cd
67bc4: cmp edi, 7
67bc7: jae 0x67bd0
67bc9: jmp 0x67bdf
67bcb: mov ecx, 0xbb166f
67bd0: push ecx
67bd1: push dword ptr [esp + 0x44]
67bd5: call 0x74540
67bda: add esp, 8
67bdd: xor esi, esi
67bdf: mov eax, esi
67be1: add esp, 0x34
67be4: pop esi
67be5: pop edi
67be6: ret 
67be7: call 0x93ab0
67bec: mov ecx, 0xb9f4cd
67bf1: cmp eax, edi
67bf3: jne 0x67bd0
67bf5: jmp 0x67bdf
67bf7: nop word ptr [eax + eax]
67c00: push esi

CALL 67b95
67b9a: mov esi, 1
67b9f: test eax, eax
67ba1: je 0x67bdf
67ba3: js 0x67bcb
67ba5: mov edi, dword ptr [esp + 8]
67ba9: test edi, edi
67bab: je 0x67bdf
67bad: mov ecx, dword ptr [esp + 0x44]
67bb1: test ecx, ecx
67bb3: jne 0x67bba
67bb5: cmp edi, 0x28
67bb8: je 0x67bdf
67bba: cmp ecx, 0x21
67bbd: jne 0x67be7
67bbf: mov ecx, 0xb9f4cd
67bc4: cmp edi, 7
67bc7: jae 0x67bd0
67bc9: jmp 0x67bdf
67bcb: mov ecx, 0xbb166f
67bd0: push ecx
67bd1: push dword ptr [esp + 0x44]
67bd5: call 0x74540
67bda: add esp, 8
67bdd: xor esi, esi
67bdf: mov eax, esi
67be1: add esp, 0x34
67be4: pop esi
67be5: pop edi
67be6: ret 
67be7: call 0x93ab0
67bec: mov ecx, 0xb9f4cd
67bf1: cmp eax, edi
67bf3: jne 0x67bd0
67bf5: jmp 0x67bdf
67bf7: nop word ptr [eax + eax]
67c00: push esi
67c01: sub esp, 0x34
67c04: mov esi, dword ptr [esp + 0x40]
67c08: mov eax, 0xfffffe38
67c0d: add eax, dword ptr [esi]
67c0f: cmp eax, -5
67c12: ja 0x67c7b
67c14: mov eax, dword ptr [esp + 0x3c]
67c18: mov eax, dword ptr [eax + 0xdfcc]
67c1e: and eax, 0xfffffffc

CALL 67c30
67c35: cmp eax, 1
67c38: jne 0x67c7b
67c3a: cmp dword ptr [esp], 0
67c3e: jne 0x67c7b
67c40: cmp dword ptr [esp + 0x14], 0
67c45: jne 0x67c7b
67c47: xor eax, eax
67c49: cmp dword ptr [esp + 4], 0
67c4e: jne 0x67c7d
67c50: mov eax, dword ptr [esp + 0x4c]
67c54: mov ecx, dword ptr [esp + 0x48]
67c58: mov edx, dword ptr [esp + 0x44]
67c5c: mov dword ptr [esi], 0
67c62: mov dword ptr [edx], 0x44b58000
67c68: mov dword ptr [ecx], 0x4531c000
67c6e: mov dword ptr [eax], 0
67c74: mov eax, 1
67c79: jmp 0x67c7d
67c7b: xor eax, eax
67c7d: add esp, 0x34
67c80: pop esi
67c81: ret 
67c82: nop word ptr cs:[eax + eax]
67c8c: nop dword ptr [eax]
67c90: push edi
67c91: push esi
67c92: sub esp, 0x34
67c95: mov eax, dword ptr [esp + 0x48]
67c99: mov esi, dword ptr [esp + 0x40]
67c9d: test esi, esi
67c9f: je 0x67cfa
67ca1: mov ecx, dword ptr [esp + 0x44]
67ca5: lea edx, [ecx - 0x27c6]
67cab: cmp edx, 0xffffd83b
67cb1: jb 0x67cfa
67cb3: mov edx, dword ptr [esi + 0x708]

CALL 67d04
67d09: cmp eax, 1
67d0c: jne 0x67cf2
67d0e: cmp dword ptr [esp], 0
67d12: mov ecx, edi
67d14: jne 0x67cf8
67d16: cmp dword ptr [esp + 0x14], 0
67d1b: jne 0x67cf8
67d1d: push 0xa99cf5
67d22: push ecx
67d23: call 0x138110
67d28: add esp, 8
67d2b: mov ecx, 0xb7b969
67d30: test eax, eax
67d32: jne 0x67cf8
67d34: push 0xaae897
67d39: push edi
67d3a: call 0x138110
67d3f: add esp, 8
67d42: mov ecx, 0xbb608a
67d47: test eax, eax
67d49: jne 0x67cf8
67d4b: push 0xacc6e7
67d50: push edi
67d51: call 0x138110
67d56: add esp, 8
67d59: mov ecx, 0xbb601e
67d5e: test eax, eax
67d60: jne 0x67cf8
67d62: push 0xac8859
67d67: push edi
67d68: call 0x138110
67d6d: add esp, 8
67d70: mov ecx, 0xbb5faa
67d75: test eax, eax
67d77: jne 0x67cf8
67d7d: push 0xa5db47
67d82: push edi
67d83: call 0x138110
67d88: add esp, 8
67d8b: mov ecx, 0xbb5f36

CALL 67e2e
67e33: cmp eax, 1
67e36: setne al
67e39: add al, al
67e3b: cmp dword ptr [esp], 3
67e3f: setne cl
67e42: or cl, al
67e44: cmp ebx, 0xb
67e47: mov ebx, dword ptr [esp + 0x84]
67e4e: setne al
67e51: shl al, 3
67e54: cmp dword ptr [esp + 0x14], 9
67e59: setne dl
67e5c: shl dl, 2
67e5f: or dl, al
67e61: or dl, cl
67e63: jne 0x67e8e
67e65: cmp edi, 0xb
67e68: jne 0x67e8e
67e6a: push 0xaf8fd8
67e6f: push ebp
67e70: call 0x1378a0
67e75: add esp, 8
67e78: test eax, eax
67e7a: je 0x67e9b
67e7c: push 0xa5d92b
67e81: push ebp
67e82: call 0x1378a0
67e87: add esp, 8
67e8a: test eax, eax
67e8c: je 0x67ebb
67e8e: mov eax, 1
67e93: add esp, 0x68
67e96: pop esi
67e97: pop edi
67e98: pop ebx
67e99: pop ebp
67e9a: ret 
67e9b: push 0xbd052d
67ea0: push ebx
67ea1: call 0x138110
67ea6: add esp, 8
67ea9: test eax, eax
67eab: je 0x67e7c
67ead: test byte ptr [esp + 0x10], 1
67eb2: jne 0x67e8e
67eb4: mov edi, 1

CALL 67edf
67ee4: cmp eax, 1
67ee7: jne 0x67f0a
67ee9: cmp dword ptr [esp + 0x34], 3
67eee: jne 0x67f0a
67ef0: or dword ptr [esp + 0x44], edi
67ef4: lea edx, [esp + 0x34]
67ef8: mov ecx, esi
67efa: call 0x91cc0
67eff: mov ecx, eax
67f01: mov eax, 1
67f06: test ecx, ecx
67f08: jne 0x67e93
67f0a: push 0xb7e944
67f0f: push dword ptr [esp + 0x80]
67f16: call 0x74540
67f1b: add esp, 8
67f1e: xor eax, eax
67f20: jmp 0x67e93
67f25: nop word ptr cs:[eax + eax]
67f2f: nop 
67f30: push ebp
67f31: push ebx
67f32: push edi
67f33: push esi
67f34: sub esp, 0x70
67f37: mov ebx, dword ptr [esp + 0x88]
67f3e: mov esi, dword ptr [esp + 0x84]
67f45: imul ebp, ebx, 0x298
67f4b: mov ecx, dword ptr [esi + ebp + 0x111e8]
67f52: lea edx, [ecx - 0x20014]
67f58: xor eax, eax
67f5a: cmp edx, -0x13
67f5d: jb 0x6802d
67f63: mov edx, dword ptr [0xd2fb8c]
67f69: test edx, edx

CALL 69897
6989c: cmp eax, 1
6989f: jne 0x698d0
698a1: xor eax, eax
698a3: mov ecx, dword ptr [esp + 0x2c]
698a7: mov edx, ebx
698a9: jmp 0x698b6
698ab: nop dword ptr [eax + eax]
698b0: inc eax
698b1: cmp eax, 0x13
698b4: je 0x698d0
698b6: bt ecx, eax
698b9: jae 0x698b0
698bb: sub edx, 1
698be: jae 0x698b0
698c0: mov ebp, eax
698c2: nop word ptr cs:[eax + eax]
698cc: nop dword ptr [eax]
698d0: imul edi, esi, 0x4c
698d3: xor eax, eax
698d5: cmp ebx, dword ptr [esp + 0x4b8]
698dc: sete al
698df: lea edx, [edi + 0x7b]
698e2: mov ecx, 0x78
698e7: push eax
698e8: push 0x46
698ea: push 0x190
698ef: call 0x964d0
698f4: add esp, 0xc
698f7: mov eax, dword ptr [0xd2fb8c]
698fc: test eax, eax
698fe: mov dword ptr [esp + 4], esi
69902: je 0x6991d
69904: mov ecx, 0xd2f8b0
69909: nop dword ptr [eax]
69910: cmp dword ptr [ecx], ebp
69912: je 0x69926
69914: add ecx, 0xf4
6991a: dec eax
6991b: jne 0x69910

CALL 6a19a
6a19f: cmp eax, 1
6a1a2: jne 0x6b5c9
6a1a8: lea eax, [esp + 0xbc]
6a1af: cmp byte ptr [esp + 0xbc], 0
6a1b7: mov esi, 0xac093d
6a1bc: cmovne esi, eax
6a1bf: mov ecx, 0x46
6a1c4: mov edx, 0x36
6a1c9: push -1
6a1cb: push 1
6a1cd: push esi
6a1ce: push 0x170
6a1d3: push 0x1f4
6a1d8: call 0x95c50
6a1dd: add esp, 0x14
6a1e0: mov eax, dword ptr [0xd478e0]
6a1e5: cmp eax, 3
6a1e8: ja 0x6b177
6a1ee: jmp dword ptr [eax*4 + 0x1c0b68]
6a1f5: mov ecx, dword ptr [0xd478e4]
6a1fb: mov edx, 0x24924925
6a200: mov eax, ecx
6a202: mul edx
6a204: sub ecx, edx
6a206: shr ecx, 1
6a208: add ecx, edx
6a20a: shr ecx, 2
6a20d: lea eax, [ecx*8]
6a214: sub eax, ecx
6a216: lea ecx, [eax - 0xa]
6a219: cmp ecx, -0x11
6a21c: mov ebx, 9
6a221: cmovae ebx, eax

CALL 6a2de
6a2e3: cmp eax, 1
6a2e6: mov dword ptr [esp + 4], ebp
6a2ea: jne 0x6a370
6a2f0: cmp dword ptr [esp + 0xd8], 9
6a2f8: jb 0x6a370
6a2fa: cmp byte ptr [esp + 0xf0], 0
6a302: je 0x6a370
6a304: mov ecx, edi
6a306: lea edx, [esp + 0x4c]
6a30a: call 0x919b0
6a30f: cmp eax, 1
6a312: jne 0x6a370
6a314: mov ecx, edi
6a316: lea edx, [esp + 0x80]
6a31d: call 0x98830
6a322: test eax, eax
6a324: js 0x6a370
6a326: mov eax, dword ptr [esp + 0x4c]
6a32a: cmp eax, dword ptr [ebp - 4]
6a32d: jb 0x6a370
6a32f: mov eax, dword ptr [esp + 0x84]
6a336: not eax
6a338: test dword ptr [ebp], eax
6a33b: jne 0x6a370
6a33d: mov ebp, 1
6a342: mov ecx, ebx
6a344: shl ebp, cl
6a346: jmp 0x6a382
6a348: nop dword ptr [eax + eax]
6a350: cmp ebx, 0xc
6a353: je 0x6a250
6a359: cmp ebx, 0xd
6a35c: jne 0x6a425
6a362: mov eax, 0xa30ec9

CALL 6a30a
6a30f: cmp eax, 1
6a312: jne 0x6a370
6a314: mov ecx, edi
6a316: lea edx, [esp + 0x80]
6a31d: call 0x98830
6a322: test eax, eax
6a324: js 0x6a370
6a326: mov eax, dword ptr [esp + 0x4c]
6a32a: cmp eax, dword ptr [ebp - 4]
6a32d: jb 0x6a370
6a32f: mov eax, dword ptr [esp + 0x84]
6a336: not eax
6a338: test dword ptr [ebp], eax
6a33b: jne 0x6a370
6a33d: mov ebp, 1
6a342: mov ecx, ebx
6a344: shl ebp, cl
6a346: jmp 0x6a382
6a348: nop dword ptr [eax + eax]
6a350: cmp ebx, 0xc
6a353: je 0x6a250
6a359: cmp ebx, 0xd
6a35c: jne 0x6a425
6a362: mov eax, 0xa30ec9
6a367: jmp 0x6a255
6a36c: nop dword ptr [eax]
6a370: mov eax, dword ptr [esp + 0x2c]
6a374: mov ebp, 1
6a379: mov ecx, ebx
6a37b: shl ebp, cl
6a37d: bt eax, ebx
6a380: jae 0x6a38b
6a382: mov eax, dword ptr [esp + 4]
6a386: mov eax, dword ptr [eax - 0xc]
6a389: jmp 0x6a390
6a38b: mov eax, 0xa26c16
6a390: mov ecx, 0x5e

CALL 6a3cf
6a3d4: cmp eax, 1
6a3d7: jne 0x6a418
6a3d9: cmp dword ptr [esp + 0xd8], 9
6a3e1: jb 0x6a418
6a3e3: cmp byte ptr [esp + 0xf0], 0
6a3eb: je 0x6a418
6a3ed: mov ecx, edi
6a3ef: lea edx, [esp + 0x4c]
6a3f3: call 0x919b0
6a3f8: cmp eax, 1
6a3fb: jne 0x6a418
6a3fd: mov ecx, edi
6a3ff: lea edx, [esp + 0x80]
6a406: call 0x98830
6a40b: test eax, eax
6a40d: js 0x6a418
6a40f: mov eax, dword ptr [esp + 0x4c]
6a413: cmp eax, dword ptr [ebp - 4]
6a416: jae 0x6a43a
6a418: mov eax, 0xa4bdda
6a41d: mov edi, dword ptr [esp]
6a420: jmp 0x6a274
6a425: cmp ebx, 0xe
6a428: mov eax, 0xa7147f
6a42d: mov ecx, 0xa1c146
6a432: cmove eax, ecx
6a435: jmp 0x6a255
6a43a: mov eax, dword ptr [esp + 0x84]
6a441: not eax
6a443: test dword ptr [ebp], eax
6a446: setne al
6a449: test al, 1
6a44b: mov eax, 0xa66678
6a450: mov ecx, 0xa4bdda
6a455: cmovne eax, ecx
6a458: jmp 0x6a41d

CALL 6a3f3
6a3f8: cmp eax, 1
6a3fb: jne 0x6a418
6a3fd: mov ecx, edi
6a3ff: lea edx, [esp + 0x80]
6a406: call 0x98830
6a40b: test eax, eax
6a40d: js 0x6a418
6a40f: mov eax, dword ptr [esp + 0x4c]
6a413: cmp eax, dword ptr [ebp - 4]
6a416: jae 0x6a43a
6a418: mov eax, 0xa4bdda
6a41d: mov edi, dword ptr [esp]
6a420: jmp 0x6a274
6a425: cmp ebx, 0xe
6a428: mov eax, 0xa7147f
6a42d: mov ecx, 0xa1c146
6a432: cmove eax, ecx
6a435: jmp 0x6a255
6a43a: mov eax, dword ptr [esp + 0x84]
6a441: not eax
6a443: test dword ptr [ebp], eax
6a446: setne al
6a449: test al, 1
6a44b: mov eax, 0xa66678
6a450: mov ecx, 0xa4bdda
6a455: cmovne eax, ecx
6a458: jmp 0x6a41d
6a45a: xor ebp, ebp
6a45c: lea esi, [esp + 0xd8]
6a463: jmp 0x6a4ca
6a465: nop word ptr cs:[eax + eax]
6a46f: nop 
6a470: xorps xmm0, xmm0
6a473: mov ebx, dword ptr [esp + 8]
6a477: add ebx, 0x97

CALL 6af75
6af7a: cmp eax, 1
6af7d: jne 0x6afc8
6af7f: cmp dword ptr [esp + 0xd8], 9
6af87: jb 0x6afc8
6af89: cmp byte ptr [esp + 0xf0], 0
6af91: je 0x6afc8
6af93: lea edx, [esp + 0x4c]
6af97: mov ecx, esi
6af99: call 0x919b0
6af9e: cmp eax, 1
6afa1: jne 0x6afc8
6afa3: lea edx, [esp + 0x80]
6afaa: mov ecx, esi
6afac: call 0x98830
6afb1: test eax, eax
6afb3: js 0x6afc8
6afb5: mov eax, dword ptr [esp + 0x4c]
6afb9: shl edi, 5
6afbc: cmp eax, dword ptr [edi + 0x3a6468]
6afc2: jae 0x6b5d4
6afc8: mov edi, dword ptr [0xd478e8]
6afce: mov eax, dword ptr [esp + 0x2c]
6afd2: bt eax, edi
6afd5: jae 0x6b3d0
6afdb: shl edi, 5
6afde: mov esi, dword ptr [edi + 0x3a6460]
6afe4: mov ecx, 0x58
6afe9: mov edx, 0x56
6afee: push esi
6afef: push 0x3f800000
6aff4: push 0x1cd
6aff9: call 0x96a30
6affe: add esp, 0xc

CALL 6af99
6af9e: cmp eax, 1
6afa1: jne 0x6afc8
6afa3: lea edx, [esp + 0x80]
6afaa: mov ecx, esi
6afac: call 0x98830
6afb1: test eax, eax
6afb3: js 0x6afc8
6afb5: mov eax, dword ptr [esp + 0x4c]
6afb9: shl edi, 5
6afbc: cmp eax, dword ptr [edi + 0x3a6468]
6afc2: jae 0x6b5d4
6afc8: mov edi, dword ptr [0xd478e8]
6afce: mov eax, dword ptr [esp + 0x2c]
6afd2: bt eax, edi
6afd5: jae 0x6b3d0
6afdb: shl edi, 5
6afde: mov esi, dword ptr [edi + 0x3a6460]
6afe4: mov ecx, 0x58
6afe9: mov edx, 0x56
6afee: push esi
6afef: push 0x3f800000
6aff4: push 0x1cd
6aff9: call 0x96a30
6affe: add esp, 0xc
6b001: mov ecx, 0x59
6b006: mov edx, 0x56
6b00b: push esi
6b00c: push 0x3f800000
6b011: push 0x1cd
6b016: call 0x96a30
6b01b: add esp, 0xc
6b01e: mov ecx, dword ptr [edi + 0x3a6464]

CALL 700ef
700f4: cmp eax, 1
700f7: jne 0x70111
700f9: cmp dword ptr [esp + 0x690], 0x24
70101: jne 0x70111
70103: cmp dword ptr [esp + 0x6a0], 0
7010b: js 0x7117f
70111: push 0x10
70113: push 0
70115: lea eax, [esp + 0xb4]
7011c: push eax
7011d: call 0x137420
70122: add esp, 0xc
70125: mov dword ptr [esp + 0xb0], 1
70130: mov eax, dword ptr [esp + 0x30]
70134: mov ecx, dword ptr [eax]
70136: call 0x72440
7013b: mov ebx, eax
7013d: nop dword ptr [eax]
70140: mov edx, dword ptr [esp + 0xb4]
70147: mov ecx, dword ptr [esp + 0xb8]
7014e: mov eax, edx
70150: or eax, ecx
70152: je 0x70169
70154: jmp 0x705e8
70159: nop dword ptr [eax]
70160: mov eax, dword ptr [esp + 0x30]
70164: cmp dword ptr [eax], 0
70167: je 0x70198
70169: lea eax, [esp + 0x214]
70170: push eax
70171: call 0x145c30
70176: add esp, 4
70179: test eax, eax

CALL 70631
70636: test eax, eax
70638: js 0x70883
7063e: mov ecx, edi
70640: lea edx, [esp + 0x690]
70647: call 0x919b0
7064c: cmp eax, 1
7064f: jne 0x70669
70651: cmp dword ptr [esp + 0x690], 0x24
70659: jne 0x70669
7065b: cmp dword ptr [esp + 0x6a0], 0
70663: js 0x70874
70669: cmp dword ptr [esp + 0x394], 0
70671: jne 0x70837
70677: mov ecx, esi
70679: call 0x93ab0
7067e: mov ecx, 1
70683: lea edx, [eax - 2]
70686: cmp edx, 0x28
70689: ja 0x7081f
7068f: jmp dword ptr [edx*4 + 0x1c0bb8]
70696: mov ecx, 2
7069b: jmp 0x7081f
706a0: xorps xmm0, xmm0
706a3: movaps xmmword ptr [esp + 0x6b0], xmm0
706ab: movaps xmmword ptr [esp + 0x6a0], xmm0
706b3: movaps xmmword ptr [esp + 0x690], xmm0

CALL 70647
7064c: cmp eax, 1
7064f: jne 0x70669
70651: cmp dword ptr [esp + 0x690], 0x24
70659: jne 0x70669
7065b: cmp dword ptr [esp + 0x6a0], 0
70663: js 0x70874
70669: cmp dword ptr [esp + 0x394], 0
70671: jne 0x70837
70677: mov ecx, esi
70679: call 0x93ab0
7067e: mov ecx, 1
70683: lea edx, [eax - 2]
70686: cmp edx, 0x28
70689: ja 0x7081f
7068f: jmp dword ptr [edx*4 + 0x1c0bb8]
70696: mov ecx, 2
7069b: jmp 0x7081f
706a0: xorps xmm0, xmm0
706a3: movaps xmmword ptr [esp + 0x6b0], xmm0
706ab: movaps xmmword ptr [esp + 0x6a0], xmm0
706b3: movaps xmmword ptr [esp + 0x690], xmm0
706bb: mov dword ptr [esp + 0x6c0], 0
706c6: mov esi, ecx
706c8: lea edx, [esp + 0x690]

CALL 706cf
706d4: cmp eax, 1
706d7: je 0x7117f
706dd: test eax, eax
706df: js 0x706f7
706e1: mov ecx, esi
706e3: lea edx, [esp + 0x690]
706ea: call 0x91cc0
706ef: test eax, eax
706f1: jne 0x7117f
706f7: push 0xbb0bc2
706fc: jmp 0x70888
70701: push 0xbb16b0
70706: push 0x64
70708: lea eax, [esp + 0x1b8]
7070f: push eax
70710: call 0x1377e0
70715: add esp, 0xc
70718: mov dword ptr [esp + 0x70], 0
70720: mov dword ptr [0xc5af30], 0
7072a: mov dword ptr [esp + 0x54], 3
70732: mov dword ptr [esp + 0x50], 3
7073a: mov dword ptr [esp + 0x58], 2
70742: mov dword ptr [esp + 0x5c], 0
7074a: mov dword ptr [esp + 0x60], 0xff
70752: mov eax, dword ptr [esp + 0x30]
70756: mov ecx, dword ptr [eax]

CALL 70ebd
70ec2: cmp eax, 1
70ec5: je 0x70ee9
70ec7: test eax, eax
70ec9: js 0x7089a
70ecf: mov ecx, esi
70ed1: lea edx, [esp + 0x690]
70ed8: call 0x91cc0
70edd: test eax, eax
70edf: mov ecx, dword ptr [esp + 0x3c]
70ee3: je 0x7089e
70ee9: mov dword ptr [0xc4ae78], 0
70ef3: mov dword ptr [0xc4ace0], 0
70efd: xor ecx, ecx
70eff: call 0xb33e0
70f04: jmp 0x700bd
70f09: mov ebx, 1
70f0e: mov dword ptr [esp + 0x28], 2
70f16: mov dword ptr [esp + 0x18], 0xfffffff8
70f1e: mov dword ptr [esp + 0x1c], 3
70f26: mov eax, ebx
70f28: neg eax
70f2a: mov dword ptr [esp + 0x2c], eax
70f2e: mov dword ptr [esp + 0x14], eax
70f32: jmp 0x70f49
70f34: mov ecx, dword ptr [esp + 0x14]
70f38: inc ecx
70f39: mov eax, ecx
70f3b: mov dword ptr [esp + 0x14], ecx
70f3f: cmp ecx, dword ptr [esp + 0x28]
70f43: je 0x70fe1

CALL 7669a
7669f: cmp eax, 1
766a2: jne 0x76929
766a8: cmp dword ptr [esp + 0xc4], 9
766b0: jb 0x76929
766b6: cmp byte ptr [esp + 0xdc], 0
766be: je 0x76929
766c4: mov ecx, dword ptr [0xd34020]
766ca: lea edx, [esp + 0xa0]
766d1: call 0x98830
766d6: test eax, eax
766d8: js 0x76929
766de: mov dword ptr [esp + 0x30], esi
766e2: mov esi, dword ptr [0xd2fbac]
766e8: imul esi, dword ptr [0xd2fbb0]
766ef: mov ebx, dword ptr [0xd424b8]
766f5: test ebx, ebx
766f7: je 0x769ea
766fd: mov ecx, dword ptr [esp + 0xa4]
76704: cmp dword ptr [0xbda134], ecx
7670a: jne 0x76724
7670c: mov edx, dword ptr [0xbda130]
76712: mov eax, 1
76717: cmp edx, dword ptr [esp + 0xa8]
7671e: je 0x76954
76724: test esi, esi

CALL 7d8a2
7d8a7: cmp eax, 1
7d8aa: jne 0x7daeb
7d8b0: mov eax, dword ptr [ebp + 8]
7d8b3: mov esi, dword ptr [0xd424c8]
7d8b9: mov eax, dword ptr [eax + 0xdfcc]
7d8bf: cmp eax, dword ptr [esi + 4]
7d8c2: jne 0x7daeb
7d8c8: mov eax, dword ptr [esp + 0x28]
7d8cc: cmp eax, dword ptr [esi]
7d8ce: jne 0x7daeb
7d8d4: mov ecx, dword ptr [esi + 0x7c]
7d8d7: test dword ptr [esp + 0x38], ecx
7d8db: jne 0x7daeb
7d8e1: mov ecx, dword ptr [esi + 8]
7d8e4: test ecx, ecx
7d8e6: je 0x7d949
7d8e8: xor ebx, ebx
7d8ea: cmp eax, 5
7d8ed: sete bl
7d8f0: add ebx, ebx
7d8f2: cmp ebx, ecx
7d8f4: jae 0x7d949
7d8f6: shl ebx, 4
7d8f9: movss xmm0, dword ptr [esi + ebx + 0x20]
7d8ff: movss xmm1, dword ptr [esi + ebx + 0x24]
7d905: movss dword ptr [esp + 4], xmm1
7d90b: movss dword ptr [esp], xmm0
7d910: mov ecx, 0xff000000
7d915: mov edx, 6
7d91a: call 0xd7150
7d91f: movss xmm0, dword ptr [esi + ebx + 0x20]
7d925: movss xmm1, dword ptr [esi + ebx + 0x24]

CALL 7ee9d
7eea2: cmp eax, 1
7eea5: jne 0x7f02a
7eeab: cmp dword ptr [esp + 0x1c], 9
7eeb0: jb 0x7f02a
7eeb6: cmp byte ptr [esp + 0x34], 0
7eebb: je 0x7f02a
7eec1: cmp dword ptr [0xbe30b0], 0
7eec8: jle 0x7f02a
7eece: mov eax, dword ptr [0xbec5ac]
7eed3: cmp eax, 0x84
7eed8: jne 0x7ef84
7eede: movss xmm0, dword ptr [0xbe3084]
7eee6: movss xmm1, dword ptr [0xbe3080]
7eeee: addss xmm1, dword ptr [0x74ad68]
7eef6: addss xmm0, dword ptr [0x74ad6c]
7eefe: mulss xmm0, xmm0
7ef02: mulss xmm1, xmm1
7ef06: addss xmm1, xmm0
7ef0a: movss dword ptr [esp], xmm1
7ef0f: call 0x137820
7ef14: fstp dword ptr [esp + 0x18]
7ef18: movss xmm0, dword ptr [0x74a420]
7ef20: ucomiss xmm0, dword ptr [esp + 0x18]
7ef25: jbe 0x7ef7f

CALL 801cf
801d4: cmp eax, 1
801d7: jne 0x80279
801dd: mov eax, dword ptr [esp + 0x34]
801e1: cmp eax, dword ptr [ebx]
801e3: jne 0x80279
801e9: mov ecx, dword ptr [0xbec5ac]
801ef: cmp ecx, dword ptr [ebx + 4]
801f2: jne 0x80279
801f8: cmp dword ptr [0xbe30b0], 0
801ff: jle 0x80279
80201: cmp dword ptr [0xd42a14], 0xbde5e0
8020b: jne 0x80229
8020d: cmp dword ptr [0xd42a18], 0xceeba4
80217: jne 0x80229
80219: cmp dword ptr [0xd42a1c], esi
8021f: jne 0x80229
80221: cmp dword ptr [0xd42a20], eax
80227: je 0x80251
80229: call 0x915f0
8022e: mov dword ptr [0xd42a14], 0xbde5e0
80238: mov dword ptr [0xd42a18], 0xceeba4
80242: mov dword ptr [0xd42a1c], esi
80248: mov eax, dword ptr [esp + 0x34]
8024c: mov dword ptr [0xd42a20], eax
80251: call 0x92400
80256: test eax, eax
80258: je 0x8027e

CALL 8067a
8067f: cmp eax, 1
80682: jne 0x80e75
80688: cmp dword ptr [esp + 0x18], 2
8068d: jbe 0x80e75
80693: mov edx, 0xf219bc63
80698: mov esi, dword ptr [esp + 0x24]
8069c: mov ecx, dword ptr [0xd34020]
806a2: xor eax, eax
806a4: add edx, -1
806a7: adc eax, 0xeca1ffff
806ac: lea edi, [esp + 0x3c0]
806b3: push 0x50
806b5: push edi
806b6: push eax
806b7: call 0x93460
806bc: add esp, 0xc
806bf: cmp eax, 1
806c2: jne 0x8085c
806c8: push 4
806ca: push 0xaf717b
806cf: push edi
806d0: call 0x137360
806d5: add esp, 0xc
806d8: test eax, eax
806da: mov eax, 0xffffffff
806df: jne 0x80864
806e5: movzx edx, byte ptr [esp + 0x3c6]
806ed: movzx ecx, byte ptr [esp + 0x3c7]
806f5: shl ecx, 8
806f8: or ecx, edx
806fa: shl ecx, 0x10
806fd: movzx edx, byte ptr [esp + 0x3c4]

CALL 8a6dc
8a6e1: cmp eax, 1
8a6e4: jne 0x8a736
8a6e6: mov eax, dword ptr [esp + 0xc0]
8a6ed: cmp eax, 0x24
8a6f0: jne 0x8a701
8a6f2: mov ebx, 0xa1d1cb
8a6f7: cmp dword ptr [esp + 0xd0], 0
8a6ff: js 0x8a736
8a701: lea ecx, [eax - 0xc]
8a704: mov ebx, 0xaa78fa
8a709: cmp ecx, 0x18
8a70c: jb 0x8a736
8a70e: mov ebx, 0xaa7821
8a713: cmp eax, 0x23
8a716: ja 0x8a736
8a718: mov ebx, dword ptr [eax*8 + 0x5dd184]
8a71f: jmp 0x8a736
8a721: inc dword ptr [esp + 0x34]
8a725: jmp 0x8a474
8a72a: mov edx, 1
8a72f: call 0x12b450
8a734: mov ebx, eax
8a736: movzx ecx, byte ptr [ebx]
8a739: test cl, cl
8a73b: je 0x8a807
8a741: xorps xmm0, xmm0
8a744: cvtsi2ss xmm0, edi
8a748: movss dword ptr [esp + 4], xmm0
8a74e: inc ebx
8a74f: mov eax, 0x19
8a754: jmp 0x8a76e
8a756: nop word ptr cs:[eax + eax]
8a760: movzx ecx, byte ptr [ebx]
8a763: inc ebx
8a764: test cl, cl
8a766: mov eax, esi

CALL 8b752
8b757: cmp eax, 1
8b75a: jne 0x8b7ae
8b75c: mov eax, dword ptr [esp + 0x2f0]
8b763: cmp eax, 0x24
8b766: jne 0x8b777
8b768: mov edi, 0xa1d1cb
8b76d: cmp dword ptr [esp + 0x300], 0
8b775: js 0x8b7ae
8b777: lea ecx, [eax - 0xc]
8b77a: mov edi, 0xaa78fa
8b77f: cmp ecx, 0x18
8b782: jb 0x8b7ae
8b784: mov edi, 0xaa7821
8b789: cmp eax, 0x23
8b78c: ja 0x8b7ae
8b78e: mov edi, dword ptr [eax*8 + 0x5dd184]
8b795: jmp 0x8b7ae
8b797: nop word ptr [eax + eax]
8b7a0: mov ecx, esi
8b7a2: mov edx, 1
8b7a7: call 0x12b450
8b7ac: mov edi, eax
8b7ae: mov ecx, dword ptr [esp + 0x38]
8b7b2: mov ebx, dword ptr [esp]
8b7b5: mov edx, ebx
8b7b7: push edi
8b7b8: push 0x3f800000
8b7bd: push 0xe5
8b7c2: call 0x96a30
8b7c7: add esp, 0xc
8b7ca: mov ecx, dword ptr [esp + 8]
8b7ce: mov edx, ebx
8b7d0: push edi
8b7d1: push 0x3f800000
8b7d6: push 0xe5

CALL 8eb7a
8eb7f: cmp eax, 1
8eb82: jne 0x8eac7
8eb88: lea ecx, [esp + 0x2f0]
8eb8f: call 0xf8140
8eb94: mov esi, eax
8eb96: jmp 0x8eac7
8eb9b: mov edx, 0x1640
8eba0: xor eax, eax
8eba2: jmp 0x8ebb6
8eba4: nop word ptr cs:[eax + eax]
8ebae: nop 
8ebb0: mov edx, edi
8ebb2: cmp eax, edx
8ebb4: jae 0x8ebd4
8ebb6: mov esi, edx
8ebb8: sub esi, eax
8ebba: shr esi, 1
8ebbc: lea edi, [esi + eax]
8ebbf: mov ebx, edi
8ebc1: shl ebx, 4
8ebc4: cmp dword ptr [ebx + 0x584470], ecx
8ebca: jae 0x8ebb0
8ebcc: lea eax, [esi + eax + 1]
8ebd0: cmp eax, edx
8ebd2: jb 0x8ebb6
8ebd4: mov esi, 0xb9586c
8ebd9: cmp eax, 0x163f
8ebde: ja 0x8eac7
8ebe4: shl eax, 4
8ebe7: cmp dword ptr [eax + 0x584470], ecx
8ebed: jne 0x8eac7
8ebf3: mov esi, dword ptr [eax + 0x584478]
8ebf9: jmp 0x8eac7
8ebfe: push 0xa26f5d
8ec03: push ebx

CALL 91964
91969: cmp eax, 1
9196c: jne 0x919ac
9196e: cmp dword ptr [esp], 0
91972: jne 0x919ac
91974: mov eax, dword ptr [esp + 0x10]
91978: or eax, dword ptr [0xd34010]
9197e: mov ecx, eax
91980: not ecx
91982: mov edx, eax
91984: or edx, 4
91987: test cl, 0x18
9198a: cmovne edx, eax
9198d: mov dword ptr [esp + 0x10], edx
91991: mov ecx, dword ptr [0xd34004]
91997: mov edx, esp
91999: call 0x91cc0
9199e: test eax, eax
919a0: je 0x919ac
919a2: mov dword ptr [0xd34010], 0
919ac: add esp, 0x34
919af: ret 
919b0: push ebp
919b1: push ebx
919b2: push edi
919b3: push esi
919b4: sub esp, 0x84
919ba: test ecx, ecx
919bc: je 0x91ad0
919c2: test edx, edx
919c4: je 0x91ad0
919ca: mov dword ptr [esp + 0xc], edx
919ce: mov dword ptr [esp + 4], ecx
919d2: mov eax, dword ptr [ecx + 4]
919d5: mov dword ptr [esp], 0
919dc: mov dword ptr [esp + 8], eax
919e0: test eax, eax
919e2: mov edx, 0
919e7: je 0x91a32
919e9: mov eax, dword ptr [esp + 4]
919ed: mov edi, dword ptr [eax]

CALL 92414
92419: mov ecx, eax
9241b: xor eax, eax
9241d: cmp ecx, 1
92420: jne 0x9245a
92422: mov ecx, dword ptr [esp]
92425: cmp ecx, dword ptr [0xd42a20]
9242b: jne 0x9245a
9242d: mov eax, dword ptr [0xd42a24]
92432: or dword ptr [esp + 0x10], eax
92436: mov ecx, dword ptr [0xd42a1c]
9243c: mov edx, esp
9243e: call 0x91cc0
92443: mov ecx, eax
92445: xor eax, eax
92447: test ecx, ecx
92449: je 0x9245a
9244b: mov dword ptr [0xd42a24], 0
92455: mov eax, 1
9245a: add esp, 0x34
9245d: ret 
9245e: mov eax, 1
92463: ret 
92464: nop word ptr cs:[eax + eax]
9246e: nop 
92470: push ebp
92471: push ebx
92472: push edi
92473: push esi
92474: sub esp, 0xaa0
9247a: mov dword ptr [esp + 0x2c], edx
9247e: mov ebp, ecx
92480: mov ecx, dword ptr [0xd424d4]
92486: test ecx, ecx
92488: je 0x92ace
9248e: lea edx, [esp + 0x31f]
92495: call 0x92ae0
9249a: test eax, eax

CALL 96c26
96c2b: cmp eax, 1
96c2e: jne 0x96cba
96c34: mov eax, dword ptr [esp + 0xc]
96c38: mov ecx, eax
96c3a: and ecx, 1
96c3d: mov edx, eax
96c3f: shr edx, 1
96c41: and edx, 1
96c44: bt eax, 2
96c48: adc edx, ecx
96c4a: mov ecx, eax
96c4c: shr ecx, 3
96c4f: and ecx, 1
96c52: bt eax, 4
96c56: adc ecx, edx
96c58: mov edx, eax
96c5a: shr edx, 5
96c5d: and edx, 1
96c60: bt eax, 6
96c64: adc edx, ecx
96c66: mov ecx, eax
96c68: shr ecx, 7
96c6b: and ecx, 1
96c6e: bt eax, 8
96c72: adc ecx, edx
96c74: mov edx, eax
96c76: shr edx, 9
96c79: and edx, 1
96c7c: bt eax, 0xa
96c80: adc edx, ecx
96c82: mov ecx, eax
96c84: shr ecx, 0xb
96c87: and ecx, 1
96c8a: bt eax, 0xc
96c8e: adc ecx, edx
96c90: mov edx, eax
96c92: shr edx, 0xd
96c95: and edx, 1
96c98: bt eax, 0xe
96c9c: adc edx, ecx
96c9e: mov ecx, eax
96ca0: shr ecx, 0xf
96ca3: and ecx, 1
96ca6: bt eax, 0x10
96caa: adc ecx, edx
96cac: mov esi, eax
96cae: shr esi, 0x11

CALL 98d0a
98d0f: cmp eax, 1
98d12: jne 0x98d36
98d14: cmp dword ptr [esp + 0x19a0], 0
98d1c: jne 0x98d36
98d1e: cmp dword ptr [esp + 0x19b4], 0
98d26: jne 0x98d36
98d28: cmp dword ptr [esp + 0x19a4], 0
98d30: je 0x99138
98d36: xor eax, eax
98d38: cmp esi, 0x1ee
98d3e: ja 0x9920a
98d44: movss xmm2, dword ptr [ebp + 0x18]
98d49: movss xmm0, dword ptr [ebp + 0x14]
98d4e: mov bl, 1
98d50: cmp dword ptr [ebp + 0x1c], 0
98d54: je 0x98f00
98d5a: mov al, 1
98d5c: mov dword ptr [esp + 0xc], eax
98d60: xor ebx, ebx
98d62: movss dword ptr [esp + 8], xmm2
98d68: movss dword ptr [esp + 0x10], xmm0
98d6e: mov eax, dword ptr [0xbda004]
98d73: mov dword ptr [esp + 0x20], eax
98d77: lea ecx, [esp + 0x6c]
98d7b: mov edx, edi
98d7d: call 0x99220
98d82: mov dword ptr [esp], 1
98d89: lea ecx, [esp + 0x19a0]
98d90: mov edx, edi

CALL c9a95
c9a9a: cmp eax, 1
c9a9d: jne 0xc9b18
c9a9f: mov ecx, dword ptr [esp + 0x14]
c9aa3: cmp ecx, dword ptr [0xd42a4c]
c9aa9: mov eax, edi
c9aab: je 0xc9b1d
c9aad: mov dword ptr [0xd42a4c], ecx
c9ab3: mov dword ptr [0xd42a48], 0
c9abd: mov dword ptr [0xd42a44], 0
c9ac7: cmp dword ptr [0xd42a2c], 0
c9ace: je 0xc9b27
c9ad0: mov ecx, dword ptr [0xd42a28]
c9ad6: lea edx, [esp + 0x34]
c9ada: call 0x919b0
c9adf: mov esi, 0xbd8d09
c9ae4: cmp eax, 1
c9ae7: jne 0xc9b2c
c9ae9: mov eax, dword ptr [esp + 0x34]
c9aed: cmp eax, dword ptr [0xd42a3c]
c9af3: jne 0xc9b2c
c9af5: mov eax, dword ptr [esp + 0x48]
c9af9: cmp eax, dword ptr [0xd42a34]
c9aff: jae 0xc9b2c
c9b01: mov ecx, dword ptr [0xd42a2c]
c9b07: mov esi, dword ptr [0xd42a38]
c9b0d: add esi, ecx
c9b0f: shl eax, 5
c9b12: add esi, dword ptr [ecx + eax + 0x18]
c9b16: jmp 0xc9b2c
c9b18: mov eax, 0xffffffff

CALL c9ada
c9adf: mov esi, 0xbd8d09
c9ae4: cmp eax, 1
c9ae7: jne 0xc9b2c
c9ae9: mov eax, dword ptr [esp + 0x34]
c9aed: cmp eax, dword ptr [0xd42a3c]
c9af3: jne 0xc9b2c
c9af5: mov eax, dword ptr [esp + 0x48]
c9af9: cmp eax, dword ptr [0xd42a34]
c9aff: jae 0xc9b2c
c9b01: mov ecx, dword ptr [0xd42a2c]
c9b07: mov esi, dword ptr [0xd42a38]
c9b0d: add esi, ecx
c9b0f: shl eax, 5
c9b12: add esi, dword ptr [ecx + eax + 0x18]
c9b16: jmp 0xc9b2c
c9b18: mov eax, 0xffffffff
c9b1d: add esp, 0x234
c9b23: pop esi
c9b24: pop edi
c9b25: pop ebx
c9b26: ret 
c9b27: mov esi, 0xbd8d09
c9b2c: push 0xa1929d
c9b31: push esi
c9b32: call 0x138110
c9b37: add esp, 8
c9b3a: test eax, eax
c9b3c: je 0xc9b64
c9b3e: lea ecx, [eax + 7]
c9b41: lea edx, [esp + 0x18]
c9b45: sub eax, esi
c9b47: lea ebx, [esp + 0x34]
c9b4b: push ecx
c9b4c: push edx
c9b4d: push esi
c9b4e: push eax
c9b4f: push 0xa44d4d
c9b54: push 0x200
c9b59: push ebx
c9b5a: call 0x1377e0
c9b5f: add esp, 0x1c
c9b62: mov esi, ebx
c9b64: mov ecx, esi

CALL c9bf7
c9bfc: cmp eax, 1
c9bff: jne 0xc9f07
c9c05: mov eax, dword ptr [esp + 0x40]
c9c09: cmp eax, dword ptr [0xd42a3c]
c9c0f: jne 0xc9f07
c9c15: mov edx, dword ptr [esp + 0x54]
c9c19: mov esi, dword ptr [0xd42a34]
c9c1f: cmp edx, esi
c9c21: jae 0xc9f07
c9c27: mov dword ptr [esp], eax
c9c2a: mov dword ptr [esp + 8], ebx
c9c2e: mov ebp, edi
c9c30: mov ebx, dword ptr [0xd42a2c]
c9c36: shl edx, 5
c9c39: movzx eax, byte ptr [ebx + edx + 0x10]
c9c3e: movzx edi, byte ptr [ebx + edx + 0x11]
c9c43: test edi, edi
c9c45: movzx ecx, word ptr [ebx + edx + 0x12]
c9c4a: mov dword ptr [esp + 4], ecx
c9c4e: je 0xc9c66
c9c50: mov ecx, dword ptr [esp + 0x44]
c9c54: test ecx, ecx
c9c56: je 0xc9ddf
c9c5c: dec cl
c9c5e: movzx ecx, cl
c9c61: bt edi, ecx
c9c64: jae 0xc9c90
c9c66: lea ecx, [eax - 1]
c9c69: cmp ecx, 7
c9c6c: ja 0xc9d58
c9c72: mov edi, ebp
c9c74: jmp dword ptr [ecx*4 + 0x1c1e78]
c9c7b: mov eax, dword ptr [esp + 0x50]
c9c7f: not eax

CALL c9cb3
c9cb8: cmp eax, 1
c9cbb: jne 0xc9f07
c9cc1: mov eax, dword ptr [esp + 0xc]
c9cc5: cmp eax, dword ptr [esp]
c9cc8: jne 0xc9f07
c9cce: cmp eax, 0x24
c9cd1: jae 0xc9f07
c9cd7: mov eax, dword ptr [esp + 4]
c9cdb: mov dword ptr [esp + 0x20], eax
c9cdf: jmp 0xc9da9
c9ce4: mov esi, dword ptr [ebx + edx + 0x28]
c9ce8: lea eax, [esi - 0x80000]
c9cee: cmp eax, 0xfff80001
c9cf3: jb 0xc9f07
c9cf9: mov ebx, dword ptr [0xd42a28]
c9cff: mov ecx, ebx
c9d01: mov edx, edi
c9d03: call 0x919b0
c9d08: cmp eax, 1
c9d0b: jne 0xc9f07
c9d11: mov eax, dword ptr [esp]
c9d14: cmp dword ptr [esp + 0xc], eax
c9d18: jne 0xc9f07
c9d1e: or dword ptr [esp + 0x18], esi
c9d22: or byte ptr [esp + 0x1c], 1
c9d27: mov ecx, ebx
c9d29: mov edx, edi
c9d2b: call 0x91cc0
c9d30: test eax, eax
c9d32: je 0xc9f07
c9d38: mov esi, dword ptr [0xd42a34]

CALL c9d03
c9d08: cmp eax, 1
c9d0b: jne 0xc9f07
c9d11: mov eax, dword ptr [esp]
c9d14: cmp dword ptr [esp + 0xc], eax
c9d18: jne 0xc9f07
c9d1e: or dword ptr [esp + 0x18], esi
c9d22: or byte ptr [esp + 0x1c], 1
c9d27: mov ecx, ebx
c9d29: mov edx, edi
c9d2b: call 0x91cc0
c9d30: test eax, eax
c9d32: je 0xc9f07
c9d38: mov esi, dword ptr [0xd42a34]
c9d3e: jmp 0xc9d5a
c9d40: cmp dword ptr [esp + 0x44], 0
c9d45: jne 0xc9d5a
c9d47: jmp 0xc9ddf
c9d4c: cmp byte ptr [esp + 0x58], 0
c9d51: jne 0xc9d5a
c9d53: jmp 0xc9eb6
c9d58: mov edi, ebp
c9d5a: mov ebp, dword ptr [esp + 4]
c9d5e: cmp esi, ebp
c9d60: jbe 0xc9f07
c9d66: cmp ebp, 0xff
c9d6c: ja 0xc9f07
c9d72: mov esi, dword ptr [0xd42a3c]
c9d78: mov ebx, dword ptr [0xd42a28]
c9d7e: mov ecx, ebx
c9d80: mov edx, edi
c9d82: call 0x919b0
c9d87: cmp eax, 1

CALL c9d82
c9d87: cmp eax, 1
c9d8a: jne 0xc9f07
c9d90: mov eax, dword ptr [esp + 0xc]
c9d94: cmp eax, esi
c9d96: jne 0xc9f07
c9d9c: cmp eax, 0x24
c9d9f: jae 0xc9f07
c9da5: mov dword ptr [esp + 0x20], ebp
c9da9: mov ecx, ebx
c9dab: mov edx, edi
c9dad: call 0x91cc0
c9db2: test eax, eax
c9db4: mov eax, 0xffffffff
c9db9: mov ebx, dword ptr [esp + 8]
c9dbd: je 0xc9f0c
c9dc3: dec ebx
c9dc4: jne 0xc9bed
c9dca: mov dword ptr [0xd42a40], 0xffffffff
c9dd4: jmp 0xc9f11
c9dd9: mov eax, dword ptr [0xd42a40]
c9dde: ret 
c9ddf: mov eax, 4
c9de4: jmp 0xc9f0c
c9de9: mov ebx, dword ptr [ebx + edx + 0x28]
c9ded: test ebx, ebx
c9def: je 0xc9ebd
c9df5: mov esi, dword ptr [esp]
c9df8: mov edi, dword ptr [0xd42a28]
c9dfe: lea edx, [esp + 0xc]
c9e02: mov ecx, edi
c9e04: call 0x919b0
c9e09: cmp esi, 0x23

CALL c9e04
c9e09: cmp esi, 0x23
c9e0c: ja 0xc9f85
c9e12: cmp eax, 1
c9e15: jne 0xc9f85
c9e1b: cmp dword ptr [esp + 0xc], esi
c9e1f: jne 0xc9f85
c9e25: mov eax, dword ptr [esp + 0x1c]
c9e29: cmp esi, 0xc
c9e2c: jb 0xc9f19
c9e32: cmp ebx, 1
c9e35: adc ebx, 0
c9e38: jmp 0xc9f29
c9e3d: mov eax, 2
c9e42: jmp 0xc9f0c
c9e47: mov edi, dword ptr [0xd42a28]
c9e4d: lea edx, [esp + 0xc]
c9e51: mov ecx, edi
c9e53: call 0x919b0
c9e58: cmp eax, 1
c9e5b: jne 0xc9f07
c9e61: mov eax, dword ptr [esp + 0xc]
c9e65: cmp eax, dword ptr [esp]
c9e68: jne 0xc9f07
c9e6e: cmp eax, 0x24
c9e71: jae 0xc9f07
c9e77: mov dword ptr [esp + 0x20], 0
c9e7f: lea edx, [esp + 0xc]
c9e83: mov ecx, edi
c9e85: call 0x91cc0
c9e8a: test eax, eax

CALL c9e53
c9e58: cmp eax, 1
c9e5b: jne 0xc9f07
c9e61: mov eax, dword ptr [esp + 0xc]
c9e65: cmp eax, dword ptr [esp]
c9e68: jne 0xc9f07
c9e6e: cmp eax, 0x24
c9e71: jae 0xc9f07
c9e77: mov dword ptr [esp + 0x20], 0
c9e7f: lea edx, [esp + 0xc]
c9e83: mov ecx, edi
c9e85: call 0x91cc0
c9e8a: test eax, eax
c9e8c: mov eax, 0xffffffff
c9e91: je 0xc9f0c
c9e93: push dword ptr [0xd42a2c]
c9e99: call 0x133f30
c9e9e: add esp, 4
c9ea1: push 0x1c
c9ea3: push 0
c9ea5: push 0xd42a28
c9eaa: call 0x137420
c9eaf: add esp, 0xc
c9eb2: xor eax, eax
c9eb4: jmp 0xc9f0c
c9eb6: mov eax, 6
c9ebb: jmp 0xc9f0c
c9ebd: mov edi, dword ptr [0xd42a28]
c9ec3: lea edx, [esp + 0xc]
c9ec7: mov ecx, edi
c9ec9: call 0x919b0
c9ece: cmp eax, 1
c9ed1: mov ecx, dword ptr [esp]
c9ed4: jne 0xc9f07
c9ed6: mov eax, dword ptr [esp + 0xc]
c9eda: cmp eax, ecx
c9edc: jne 0xc9f07

CALL c9ec9
c9ece: cmp eax, 1
c9ed1: mov ecx, dword ptr [esp]
c9ed4: jne 0xc9f07
c9ed6: mov eax, dword ptr [esp + 0xc]
c9eda: cmp eax, ecx
c9edc: jne 0xc9f07
c9ede: cmp eax, 0x24
c9ee1: jae 0xc9f07
c9ee3: or byte ptr [esp + 0x1c], 1
c9ee8: lea edx, [esp + 0xc]
c9eec: mov ecx, edi
c9eee: call 0x91cc0
c9ef3: test eax, eax
c9ef5: mov eax, 0xffffffff
c9efa: je 0xc9f0c
c9efc: mov esi, dword ptr [0xd42a3c]
c9f02: jmp 0xc9df8
c9f07: mov eax, 0xffffffff
c9f0c: mov dword ptr [0xd42a40], eax
c9f11: add esp, 0x74
c9f14: pop esi
c9f15: pop edi
c9f16: pop ebx
c9f17: pop ebp
c9f18: ret 
c9f19: xor ecx, ecx
c9f1b: test esi, esi
c9f1d: sete cl
c9f20: add ecx, ecx
c9f22: or ecx, ebx
c9f24: or ecx, 1
c9f27: mov ebx, ecx
c9f29: not eax
c9f2b: test ebx, eax
c9f2d: jne 0xc9f85
c9f2f: cmp esi, 1
c9f32: jne 0xc9f3b
c9f34: cmp dword ptr [esp + 0x10], 0
c9f39: je 0xc9f85
c9f3b: inc esi
c9f3c: mov dword ptr [esp + 0xc], esi
c9f40: mov dword ptr [esp + 0x20], 0
c9f48: mov dword ptr [esp + 0x1c], 0
c9f50: lea edx, [esp + 0xc]

CALL c9fc5
c9fca: cmp eax, 1
c9fcd: jne 0xca048
c9fcf: mov eax, dword ptr [esp + 0x48]
c9fd3: shl eax, 5
c9fd6: add eax, dword ptr [0xd42a2c]
c9fdc: cmp edi, 2
c9fdf: lea ecx, [esi + esi + 0x14]
c9fe3: mov edx, 2
c9fe8: cmove edx, ecx
c9feb: movzx edi, word ptr [edx + eax + 0x10]
c9ff0: cmp dword ptr [0xd42a34], edi
c9ff6: jbe 0xca03e
c9ff8: cmp edi, 0xff
c9ffe: ja 0xca03e
ca000: mov ebx, dword ptr [0xd42a3c]
ca006: mov esi, dword ptr [0xd42a28]
ca00c: mov edx, esp
ca00e: mov ecx, esi
ca010: call 0x919b0
ca015: cmp eax, 1
ca018: jne 0xca03e
ca01a: mov eax, dword ptr [esp]
ca01d: cmp eax, ebx
ca01f: jne 0xca03e
ca021: cmp eax, 0x24
ca024: jae 0xca03e
ca026: mov dword ptr [esp + 0x14], edi
ca02a: mov edx, esp
ca02c: mov ecx, esi
ca02e: call 0x91cc0
ca033: test eax, eax
ca035: je 0xca03e
ca037: call 0xc9bd0
ca03c: jmp 0xca048
ca03e: mov dword ptr [0xd42a40], 0xffffffff
ca048: add esp, 0x68
ca04b: pop esi
ca04c: pop edi
ca04d: pop ebx
ca04e: ret 
ca04f: nop 

CALL ca010
ca015: cmp eax, 1
ca018: jne 0xca03e
ca01a: mov eax, dword ptr [esp]
ca01d: cmp eax, ebx
ca01f: jne 0xca03e
ca021: cmp eax, 0x24
ca024: jae 0xca03e
ca026: mov dword ptr [esp + 0x14], edi
ca02a: mov edx, esp
ca02c: mov ecx, esi
ca02e: call 0x91cc0
ca033: test eax, eax
ca035: je 0xca03e
ca037: call 0xc9bd0
ca03c: jmp 0xca048
ca03e: mov dword ptr [0xd42a40], 0xffffffff
ca048: add esp, 0x68
ca04b: pop esi
ca04c: pop edi
ca04d: pop ebx
ca04e: ret 
ca04f: nop 
ca050: xor eax, eax
ca052: cmp ecx, 0x14f
ca058: ja 0xca156
ca05e: push edi
ca05f: push esi
ca060: sub esp, 8
ca063: movss xmm0, dword ptr [0xbe3080]
ca06b: imul esi, ecx, 0x298
ca071: subss xmm0, dword ptr [esi + 0xbef7d8]
ca079: movss xmm1, dword ptr [0xbe3084]
ca081: subss xmm1, dword ptr [esi + 0xbef7dc]
ca089: mulss xmm1, xmm1
ca08d: mulss xmm0, xmm0
ca091: addss xmm0, xmm1
ca095: ucomiss xmm0, dword ptr [0x74a3f8]

CALL ca17c
ca181: cmp eax, 1
ca184: jne 0xca18f
ca186: test esi, esi
ca188: je 0xca41f
ca18e: dec esi
ca18f: cmp dword ptr [0xe23994], 0
ca196: je 0xca31d
ca19c: xor edi, edi
ca19e: jmp 0xca1b7
ca1a0: sub esi, 1
ca1a3: jb 0xca412
ca1a9: inc edi
ca1aa: mov eax, dword ptr [0xe23994]
ca1af: cmp edi, eax
ca1b1: jae 0xca268
ca1b7: mov eax, dword ptr [edi*4 + 0xe23998]
ca1be: cmp eax, 0x77359400
ca1c3: je 0xca1a0
ca1c5: mov dword ptr [esp], esi
ca1c8: mov esi, 0x1640
ca1cd: xor ecx, ecx
ca1cf: jmp 0xca1e6
ca1d1: nop word ptr cs:[eax + eax]
ca1db: nop dword ptr [eax + eax]
ca1e0: mov esi, edx
ca1e2: cmp ecx, esi
ca1e4: jae 0xca204
ca1e6: mov ebx, esi
ca1e8: sub ebx, ecx
ca1ea: shr ebx, 1
ca1ec: lea edx, [ebx + ecx]
ca1ef: mov ebp, edx
ca1f1: shl ebp, 4
ca1f4: cmp dword ptr [ebp + 0x584470], eax
ca1fa: jae 0xca1e0
ca1fc: lea ecx, [ebx + ecx + 1]
ca200: cmp ecx, esi
ca202: jb 0xca1e6

CALL cb3c5
cb3ca: cmp eax, 1
cb3cd: jne 0xcb57d
cb3d3: cmp dword ptr [esp + 4], 0xb
cb3d8: ja 0xcb57d
cb3de: mov esi, 0xa8c7f832
cb3e3: mov ecx, 0x77359400
cb3e8: call 0xcbf10
cb3ed: xor ecx, ecx
cb3ef: test eax, eax
cb3f1: setne cl
cb3f4: add ecx, ecx
cb3f6: mov dword ptr [esp], ecx
cb3f9: lea eax, [esp + 0x38]
cb3fd: push 0x77359400
cb402: push 0xa22eca
cb407: push 0x30
cb409: push eax
cb40a: call 0x1377e0
cb40f: add esp, 0x10
cb412: movzx ecx, byte ptr [esp + 0x38]
cb417: test cl, cl
cb419: je 0xcb546
cb41f: mov ebp, 0x1b3
cb424: lea ebx, [esp + 0x39]
cb428: mov eax, 0x281a39c5
cb42d: nop dword ptr [eax]
cb430: movzx ecx, cl
cb433: xor ecx, eax
cb435: mov edi, ecx
cb437: mov eax, 0x100
cb43c: imul edi, eax
cb43f: mov eax, ecx
cb441: mul ebp
cb443: add edx, edi
cb445: imul esi, ebp
cb448: add esi, edx
cb44a: movzx ecx, byte ptr [ebx]
cb44d: inc ebx
cb44e: test cl, cl

CALL cbe81
cbe86: xor ebx, ebx
cbe88: cmp eax, 1
cbe8b: sete bl
cbe8e: mov ecx, dword ptr [0xd34020]
cbe94: jmp 0xcbe9a
cbe96: xor ecx, ecx
cbe98: xor ebx, ebx
cbe9a: mov edx, esp
cbe9c: call 0x98830
cbea1: test eax, eax
cbea3: js 0xcbefa
cbea5: mov eax, dword ptr [esp]
cbea8: mov ecx, eax
cbeaa: and ecx, 1
cbead: bt eax, 1
cbeb1: adc ecx, 0
cbeb4: mov edx, eax
cbeb6: shr edx, 2
cbeb9: and edx, 1
cbebc: bt eax, 3
cbec0: adc edx, ecx
cbec2: mov ecx, eax
cbec4: shr ecx, 4
cbec7: and ecx, 1
cbeca: bt eax, 5
cbece: adc ecx, edx
cbed0: mov edx, eax
cbed2: shr edx, 6
cbed5: and edx, 1
cbed8: bt eax, 7
cbedc: adc edx, ecx
cbede: mov ecx, eax
cbee0: shr ecx, 8
cbee3: and ecx, 1
cbee6: bt eax, 9
cbeea: adc ecx, edx
cbeec: mov edi, eax
cbeee: shr edi, 0xa
cbef1: and edi, 1
cbef4: bt eax, 0xb
cbef8: adc edi, ecx
cbefa: add ebx, esi
cbefc: add ebx, edi
cbefe: mov eax, ebx
cbf00: add esp, 0x58
cbf03: pop esi
cbf04: pop edi
cbf05: pop ebx
cbf06: ret 

CALL cc05c
cc061: cmp eax, 1
cc064: jne 0xcc418
cc06a: cmp dword ptr [esp + 0x18], 0xb
cc06f: mov eax, 0
cc074: ja 0xcc331
cc07a: mov edi, 0xa8c7f832
cc07f: mov esi, 0x281a39c5
cc084: lea eax, [esp + 0x4c]
cc088: push 0x77359400
cc08d: push 0xa22eca
cc092: push 0x30
cc094: push eax
cc095: call 0x1377e0
cc09a: add esp, 0x10
cc09d: movzx edx, byte ptr [esp + 0x4c]
cc0a2: test dl, dl
cc0a4: je 0xcc0de
cc0a6: mov ecx, 0x100
cc0ab: mov ebx, 0x1b3
cc0b0: lea ebp, [esp + 0x4d]
cc0b4: nop word ptr cs:[eax + eax]
cc0be: nop 
cc0c0: movzx eax, dl
cc0c3: xor eax, esi
cc0c5: mov esi, eax
cc0c7: imul esi, ecx
cc0ca: mul ebx
cc0cc: add edx, esi
cc0ce: imul edi, ebx
cc0d1: add edi, edx
cc0d3: movzx edx, byte ptr [ebp]
cc0d7: inc ebp
cc0d8: test dl, dl
cc0da: mov esi, eax
cc0dc: jne 0xcc0c0
cc0de: cmp esi, 1
cc0e1: mov eax, esi
cc0e3: adc eax, 0
cc0e6: test edi, edi

CALL f775b
f7760: cmp eax, 1
f7763: jne 0xf7b1d
f7769: mov ecx, dword ptr [esp + 0x50]
f776d: cmp ecx, dword ptr [edi]
f776f: jne 0xf7b1d
f7775: xor ebx, ebx
f7777: cmp ecx, 5
f777a: sete bl
f777d: add ebx, ebx
f777f: cmp ebx, dword ptr [edi + 8]
f7782: jae 0xf78f2
f7788: mov eax, ebx
f778a: shl eax, 4
f778d: mov edx, edi
f778f: lea edi, [eax + edi + 0x24]
f7793: movss xmm0, dword ptr [0x74a34c]
f779b: movss dword ptr [esp + 0x14], xmm0
f77a1: mov eax, 0xffffffff
f77a6: mov dword ptr [esp + 0x28], edx
f77aa: jmp 0xf77ce
f77ac: lea eax, [ebx + 0x64]
f77af: mov dword ptr [esp + 0x18], eax
f77b3: movss dword ptr [esp + 0x14], xmm1
f77b9: inc ebx
f77ba: add edi, 0x10
f77bd: mov edx, dword ptr [esp + 0x28]
f77c1: cmp ebx, dword ptr [edx + 8]
f77c4: mov eax, dword ptr [esp + 0x18]
f77c8: jae 0xf790d
f77ce: mov ecx, dword ptr [edx]
f77d0: xor edx, edx
f77d2: cmp ecx, 5
f77d5: sete dl
f77d8: lea edx, [edx + edx + 1]
f77dc: cmp ebx, edx
f77de: jae 0xf7907

CALL f7b65
f7b6a: cmp eax, 1
f7b6d: mov eax, 0xffffffff
f7b72: jne 0xf7d69
f7b78: cmp dword ptr [esp + 0x1c], 2
f7b7d: ja 0xf7d69
f7b83: mov eax, dword ptr [0xd33ffc]
f7b88: movss xmm0, dword ptr [eax + 0x4aa0]
f7b90: addss xmm0, dword ptr [0x74af28]
f7b98: movss xmm1, dword ptr [eax + 0x4aa4]
f7ba0: addss xmm1, dword ptr [0x74af2c]
f7ba8: mulss xmm1, xmm1
f7bac: mulss xmm0, xmm0
f7bb0: addss xmm0, xmm1
f7bb4: movss dword ptr [esp], xmm0
f7bb9: call 0x137820
f7bbe: fstp dword ptr [esp + 0x18]
f7bc2: movss xmm1, dword ptr [esp + 0x18]
f7bc8: movss xmm0, dword ptr [0x74a34c]
f7bd0: xor ebx, ebx
f7bd2: ucomiss xmm0, xmm1
f7bd5: setbe bl
f7bd8: neg ebx
f7bda: minss xmm1, xmm0
f7bde: movss dword ptr [esp + 4], xmm1
f7be4: mov eax, dword ptr [0xd33ffc]
f7be9: movss xmm0, dword ptr [eax + 0x4aa0]

CALL f7e91
f7e96: cmp eax, 1
f7e99: jne 0xf7ffc
f7e9f: mov ecx, dword ptr [esp + 0x58]
f7ea3: cmp ecx, 0x23
f7ea6: ja 0xf7ffc
f7eac: cmp ecx, 0xb
f7eaf: ja 0xf7ffc
f7eb5: mov edx, ecx
f7eb7: shl edx, 4
f7eba: mov ebp, dword ptr [edx + 0x5dcf44]
f7ec0: mov eax, 0x5ca5
f7ec5: mov dword ptr [esp + 0xc], ebp
f7ec9: sub eax, ebp
f7ecb: jb 0xf7ffc
f7ed1: mov ebp, dword ptr [edx + 0x5dcf48]
f7ed7: cmp ebp, eax
f7ed9: ja 0xf7ffc
f7edf: mov eax, ebp
f7ee1: mov dword ptr [esp + 0x10], ecx
f7ee5: mov dword ptr [esp + 0x1c], edx
f7ee9: mov ebp, dword ptr [edx + 0x5dcf4c]
f7eef: mov dword ptr [esp + 4], eax
f7ef3: push eax
f7ef4: call 0x132c00
f7ef9: add esp, 4
f7efc: mov dword ptr [esp + 8], ebp
f7f00: push ebp
f7f01: mov ebp, eax
f7f03: call 0x132c00
f7f08: add esp, 4
f7f0b: test ebp, ebp
f7f0d: je 0xf7fe8
f7f13: test eax, eax
f7f15: je 0xf7fe8

CALL 128fd6
128fdb: cmp eax, 1
128fde: jne 0x1299ef
128fe4: mov ecx, dword ptr [esp + 0x34]
128fe8: lea eax, [ecx - 0xc]
128feb: cmp eax, 0x17
128fee: ja 0x1292af
128ff4: lea ecx, [esp + 0x34]
128ff8: mov edx, dword ptr [esp + 0x10]
128ffc: call 0x12a6c0
129001: mov esi, eax
129003: jmp 0x1299ef
129008: mov ecx, dword ptr [esp + 8]
12900c: test dword ptr [esp + 0x38], ecx
129010: cmovne ebp, esi
129013: nop word ptr cs:[eax + eax]
12901d: nop dword ptr [eax]
129020: mov ecx, edi
129022: shl ecx, 6
129025: mov edx, dword ptr [ecx + edi*4 + 0x2d943c]
12902c: imul edi, eax, 0x78
12902f: lea eax, [ebx + edi]
129032: push edx
129033: push esi
129034: push ebp
129035: push 0xa44db9
12903a: push 0x60
12903c: push eax
12903d: call 0x1377e0
129042: add esp, 0x18
129045: mov dword ptr [ebx + edi + 0x68], ebp
129049: mov dword ptr [ebx + edi + 0x6c], 0
129051: mov dword ptr [ebx + edi + 0x70], esi
129055: mov dword ptr [ebx + edi + 0x74], 0
12905d: xor eax, eax
12905f: cmp ebp, esi

CALL 129a3a
129a3f: cmp eax, 1
129a42: jne 0x129db2
129a48: mov eax, dword ptr [esp + 0x2c]
129a4c: cmp eax, 0xc
129a4f: jb 0x129db2
129a55: cmp eax, 0x23
129a58: ja 0x129db2
129a5e: lea edi, [esp + 0x60]
129a62: push 0x1e0
129a67: push 0
129a69: push edi
129a6a: call 0x137420
129a6f: add esp, 0xc
129a72: lea ecx, [esp + 0x2c]
129a76: mov edx, edi
129a78: call 0x12a6c0
129a7d: mov ecx, dword ptr [ebp + 8]
129a80: mov dword ptr [ecx], 0
129a86: mov dword ptr [ecx + 4], 0
129a8d: mov dword ptr [esi], 0
129a93: mov dword ptr [esi + 4], 0
129a9a: test eax, eax
129a9c: jle 0x12a008
129aa2: lea ecx, [esp + 0xd0]
129aa9: jmp 0x129aba
129aab: nop dword ptr [eax + eax]
129ab0: add ecx, 0x78
129ab3: dec eax
129ab4: je 0x12a008
129aba: mov edx, dword ptr [ecx]
129abc: mov esi, dword ptr [ecx + 4]
129abf: cmp edx, 2
129ac2: mov edi, esi

CALL 129de1
129de6: cmp eax, 1
129de9: jne 0x12a094
129def: mov eax, dword ptr [esp + 0x60]
129df3: cmp eax, 0xb
129df6: ja 0x12a094
129dfc: jae 0x12a086
129e02: jmp dword ptr [eax*4 + 0x1c3f64]
129e09: mov eax, dword ptr [ebp + 8]
129e0c: mov dword ptr [eax + 4], 0
129e13: mov dword ptr [eax], 3
129e19: mov ecx, dword ptr [esp + 0x70]
129e1d: mov edx, ecx
129e1f: and edx, 1
129e22: mov eax, ecx
129e24: shr eax, 1
129e26: and eax, 1
129e29: bt ecx, 2
129e2d: jmp 0x12a07b
129e32: xor eax, eax
129e34: test eax, eax
129e36: jne 0x129fc3
129e3c: jmp 0x12a094
129e41: mov dword ptr [esp + 0xc], edx
129e45: test edx, edx
129e47: je 0x129fa7
129e4d: mov dword ptr [esp + 8], ebx
129e51: mov esi, dword ptr [ebx + 0x194d7390]
129e57: mov ebx, 0x1c89
129e5c: xor edx, edx
129e5e: jmp 0x129e66
129e60: mov ebx, ecx
129e62: cmp edx, ebx
129e64: jae 0x129e7e
129e66: lea ecx, [ebx + edx]
129e69: shr ecx, 1

CALL 129fdf
129fe4: cmp eax, 1
129fe7: jne 0x12a094
129fed: mov eax, dword ptr [esp + 0x60]
129ff1: cmp eax, 0xa
129ff4: ja 0x12a094
129ffa: mov ecx, 0x4c0
129fff: bt ecx, eax
12a002: jae 0x12a094
12a008: xor eax, eax
12a00a: mov ecx, 1
12a00f: mov edx, dword ptr [ebp + 8]
12a012: cmp ecx, dword ptr [edx]
12a014: sbb eax, dword ptr [edx + 4]
12a017: setb dl
12a01a: jmp 0x12a096
12a01c: mov eax, dword ptr [ebp + 8]
12a01f: mov dword ptr [eax + 4], 0
12a026: mov dword ptr [eax], 1
12a02c: mov eax, dword ptr [esp + 0x70]
12a030: and eax, 1
12a033: jmp 0x12a07d
12a035: mov eax, dword ptr [ebp + 8]
12a038: mov dword ptr [eax + 4], 0
12a03f: mov dword ptr [eax], 2
12a045: mov eax, dword ptr [esp + 0x70]
12a049: and eax, 1
12a04c: cmp byte ptr [esp + 0x78], 1
12a051: sbb eax, -1
12a054: jmp 0x12a07d
12a056: mov eax, dword ptr [ebp + 8]
12a059: mov dword ptr [eax + 4], 0
12a060: mov dword ptr [eax], 3
12a066: mov ecx, dword ptr [esp + 0x70]

CALL 12b6a8
12b6ad: mov ecx, eax
12b6af: mov eax, 0xaabd6c
12b6b4: cmp ecx, 1
12b6b7: jne 0x12b7a9
12b6bd: mov ecx, dword ptr [esp]
12b6c0: cmp ecx, 0x24
12b6c3: jne 0x12b6d5
12b6c5: mov eax, 0xa1d1cb
12b6ca: cmp dword ptr [esp + 0x10], 0
12b6cf: js 0x12b7a9
12b6d5: lea edx, [ecx - 0xc]
12b6d8: mov eax, 0xaa78fa
12b6dd: cmp edx, 0x18
12b6e0: jb 0x12b7a9
12b6e6: mov eax, 0xaa7821
12b6eb: cmp ecx, 0x23
12b6ee: ja 0x12b7a9
12b6f4: mov eax, dword ptr [ecx*8 + 0x5dd184]
12b6fb: jmp 0x12b7a9
12b700: mov edx, 0x1640
12b705: xor eax, eax
12b707: jmp 0x12b716
12b709: nop dword ptr [eax]
12b710: mov edx, edi
12b712: cmp eax, edx
12b714: jae 0x12b734
12b716: mov esi, edx
12b718: sub esi, eax
12b71a: shr esi, 1
12b71c: lea edi, [esi + eax]
12b71f: mov ebx, edi
12b721: shl ebx, 4
12b724: cmp dword ptr [ebx + 0x584470], ecx
12b72a: jae 0x12b710
12b72c: lea eax, [esi + eax + 1]
12b730: cmp eax, edx
12b732: jb 0x12b716