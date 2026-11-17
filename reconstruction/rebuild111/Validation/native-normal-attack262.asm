100250: mov dh, 5
100252: adc ah, byte ptr [ecx]
100254: mov esi, 0x32d86b00
100259: add ebx, 0x32
10025c: test eax, eax
10025e: cmove ebx, eax
100261: movss xmm0, dword ptr [0xbe16e4]; 0.0
100269: xor eax, eax
10026b: ucomiss xmm0, xmm1
10026e: cmovbe ebx, eax
100271: movss xmm0, dword ptr [0xbe1614]; 0.0
100279: ucomiss xmm0, xmm1
10027c: movzx eax, byte ptr [0xbe20de]
100283: lea eax, [eax + eax*4]
100286: mov edx, 0
10028b: cmovbe eax, edx
10028e: add eax, dword ptr [esp + 0x20]
100292: add eax, ebx
100294: movss xmm0, dword ptr [0xbe1678]; 0.0
10029c: cmp byte ptr [0xbe20f7], 0
1002a3: cmove ecx, edx
1002a6: movss dword ptr [esp + 0x70], xmm1
1002ac: ucomiss xmm0, xmm1
1002af: cmovbe ecx, edx
1002b2: add ecx, eax
1002b4: imul ecx, edi
1002b7: mov eax, ecx
1002b9: mov edi, 0x51eb851f
1002be: mov ecx, 0x51eb851f
1002c3: imul ecx
1002c5: mov eax, edx
1002c7: shr eax, 0x1f
1002ca: sar edx, 5
1002cd: add edx, eax
1002cf: mov dword ptr [esp + 0x20], edx
1002d3: call 0x108a40
1002d8: test eax, eax
1002da: js 0x10031c
1002dc: mov eax, dword ptr [0xbec674]
1002e1: movzx ecx, byte ptr [0xbe52e1]
1002e8: cmp al, cl
1002ea: cmova ecx, eax
1002ed: movzx eax, cl
1002f0: lea eax, [eax + eax*4]
1002f3: lea eax, [eax + eax + 0x32]
1002f7: imul eax, dword ptr [esp + 0x20]
1002fc: imul edi
1002fe: mov eax, edx
100300: shr eax, 0x1f
100303: sar edx, 5
100306: add edx, eax
100308: mov dword ptr [esp + 0x20], edx
10030c: jmp 0x10031c
10030e: movss xmm0, dword ptr [0xbe3098]; 0.0
100316: movss dword ptr [esp + 0x70], xmm0
10031c: movss xmm0, dword ptr [0xbe1704]; 0.0
100324: ucomiss xmm0, dword ptr [esp + 0x70]
100329: movzx eax, byte ptr [0xbe211a]
100330: lea ecx, [eax + eax + 0x64]
100334: mov eax, 0x64
100339: cmova eax, ecx
10033c: imul eax, dword ptr [esp + 0x20]
100341: mov edi, 0x51eb851f
100346: imul edi
100348: mov eax, edx
10034a: shr eax, 0x1f
10034d: sar edx, 5
100350: add edx, eax
100352: mov dword ptr [esp + 4], 0
10035a: mov dword ptr [esp], 0
100361: mov ecx, dword ptr [esp + 0x30]
100365: call 0xf24c0
10036a: mov ecx, dword ptr [esp + 0x40]
10036e: shl eax, cl
100370: cmp byte ptr [esp + 0x28], 0
100375: je 0x100395
100377: mov ecx, 0x8c
10037c: add ecx, dword ptr [0xbe3508]
100382: imul ecx, eax
100385: mov eax, ecx
100387: imul edi
100389: mov eax, edx
10038b: mov ecx, edx
10038d: shr ecx, 0x1f
100390: sar eax, 5
100393: add eax, ecx
100395: mov edi, dword ptr [esi + 0xbef888]
10039b: mov ecx, edi
10039d: shl ecx, 6
1003a0: mov dword ptr [esp + 0x20], 1
1003a8: test byte ptr [ecx + edi*4 + 0x2597a0], 0x10
1003b0: mov ebx, 1
1003b5: jne 0x10055f
1003bb: mov ecx, dword ptr [esp + 0x24]
1003bf: mov dword ptr [esp], ecx
1003c2: mov ecx, dword ptr [esp + 0x30]
1003c6: mov edx, eax
1003c8: call 0xf1a70
1003cd: mov dword ptr [esp + 0x28], eax
1003d1: mov ebx, dword ptr [0xbec5e8]
1003d7: mov ecx, ebx
1003d9: call 0x95b20
1003de: cmp ebx, 0x28
1003e1: je 0x1003ec
1003e3: cmp eax, 3
1003e6: jne 0x10053c
1003ec: cmp dword ptr [esi + 0xbef86c], 0
1003f3: je 0x1004ff
1003f9: mov ecx, dword ptr [esi + 0xbef880]
1003ff: test ecx, ecx
100401: je 0x1004ff
100407: cmp ecx, 1
10040a: je 0x10050a
100410: xor eax, eax
100412: cmp ecx, 2
100415: sete al
100418: jmp 0x100506
10041d: mov dword ptr [0xbe30e4], 0
100427: jmp 0xfe1ce
10042c: movss xmm0, dword ptr [edi + 0xbef7dc]
100434: movss xmm1, dword ptr [edi + 0xbef7d8]
10043c: movss dword ptr [esp + 4], xmm0
100442: movss dword ptr [esp], xmm1
100447: mov ecx, 0xbde5e0
10044c: call 0x94440
100451: jmp 0xffe26
100456: movss xmm0, dword ptr [edi + 4]
10045b: movss xmm1, dword ptr [edi]
10045f: movss dword ptr [esp + 4], xmm0
100465: movss dword ptr [esp], xmm1
10046a: mov ecx, 0xbde5e0
10046f: call 0x94440
100474: xor eax, eax
100476: cmp dword ptr [esi + 0xbef86c], 0
10047d: jne 0x100496
10047f: mov eax, dword ptr [esi + 0xbef888]
100485: mov ecx, eax
100487: shl ecx, 6
10048a: mov eax, dword ptr [ecx + eax*4 + 0x2597a0]
100491: shr eax, 1
100493: and eax, 1
100496: mov dword ptr [esi + 0xbef890], eax
10049c: movss xmm0, dword ptr [0xbe3098]; 0.0
1004a4: movss dword ptr [0xbe309c], xmm0; 0.0
1004ac: call 0xf38f0
1004b1: xorps xmm0, xmm0
1004b4: cvtsi2ss xmm0, eax
1004b8: mulss xmm0, dword ptr [0x74a4a4]; 0.0020000000949949026
1004c0: movss dword ptr [0xbe30a8], xmm0; 0.0
1004c8: mov eax, dword ptr [esi + 0xbef888]
1004ce: mov ecx, eax
1004d0: shl ecx, 6
1004d3: mov eax, dword ptr [ecx + eax*4 + 0x259774]
1004da: mov dword ptr [esp + 0xc], eax
1004de: mov dword ptr [esp + 8], 0xb6d931
1004e6: mov dword ptr [esp + 4], 1
1004ee: mov dword ptr [esp], 0xbde5e0
1004f5: call 0xa5cf0
1004fa: jmp 0xfad45
1004ff: movzx eax, byte ptr [edi + 0x5e56ac]
100506: test eax, eax
100508: je 0x10053c
10050a: movzx eax, byte ptr [0xbec61e]
100511: xorps xmm0, xmm0
100514: cvtsi2ss xmm0, eax
100518: cvtsi2ss xmm1, dword ptr [0xbe30c0]
100520: divss xmm1, dword ptr [0x74a34c]; 20.0
100528: addss xmm1, dword ptr [0x74a340]; 3.0
100530: mulss xmm1, xmm0
100534: cvttss2si eax, xmm1
100538: add dword ptr [esp + 0x28], eax
10053c: movss xmm0, dword ptr [0xbe1668]; 0.0
100544: movzx eax, byte ptr [0xbe20f3]
10054b: shl eax, 2
10054e: xor ecx, ecx
100550: ucomiss xmm0, dword ptr [esp + 0x70]
100555: lea ebx, [eax + eax*4]
100558: cmovbe ebx, ecx
10055b: add ebx, dword ptr [esp + 0x28]
10055f: cmp ebx, 2
100562: mov eax, dword ptr [esp + 0x20]
100566: cmovge eax, ebx
100569: mov dword ptr [esp + 0x20], eax
10056d: mov ecx, dword ptr [0xbe30e0]
100573: call 0x108b40
100578: mov dword ptr [esp + 0x70], eax
10057c: test eax, eax
10057e: jne 0x100677
100584: cmp byte ptr [esp + 0x40], 0
100589: je 0x1005c4
10058b: mov edi, dword ptr [0xbed320]
100591: mov dword ptr [0xbed320], 0
10059b: mov ecx, dword ptr [0xbe30e0]
1005a1: mov dword ptr [esp + 4], 2
1005a9: mov dword ptr [esp], 0
1005b0: mov edx, dword ptr [esp + 0x20]
1005b4: call 0xce1e0
1005b9: mov dword ptr [0xbed320], edi
1005bf: jmp 0x100654
1005c4: movss xmm0, dword ptr [esi + 0xbef6f8]
1005cc: ucomiss xmm0, dword ptr [0xbe3098]
1005d3: jbe 0x1005f9
1005d5: lea eax, [esi + 0xbef6f8]
1005db: mov dword ptr [eax], 0
1005e1: mov ecx, dword ptr [esp + 0x20]
1005e5: add ecx, ecx
1005e7: cmp ebx, 0x3b9aca01
1005ed: mov eax, 0x77359400
1005f2: cmovge ecx, eax
1005f5: mov dword ptr [esp + 0x20], ecx
1005f9: mov eax, dword ptr [esp + 0x24]
1005fd: mov dword ptr [esp + 8], eax
100601: mov ebx, dword ptr [esp + 0x20]
100605: mov dword ptr [esp], ebx
100608: mov dword ptr [esp + 4], 1
100610: mov ecx, 0xbde5e0
100615: mov edi, dword ptr [esp + 0x30]
100619: mov edx, edi
10061b: call 0xa41b0
100620: mov ecx, 0xbde5e0
100625: mov edx, 1
10062a: call 0xa3e30
10062f: mov dword ptr [0xbe5478], 0
100639: mov dword ptr [esp], ebx
10063c: mov ecx, 0xbde5e0
100641: mov edx, edi
100643: call 0xa4260
100648: mov ecx, 0xbde5e0
10064d: mov edx, edi
10064f: call 0xa4350
100654: mov eax, dword ptr [esp + 0x20]
100658: mov dword ptr [esp + 4], eax
10065c: mov eax, dword ptr [esp + 0x2c]
100660: mov dword ptr [esp], eax
100663: mov dword ptr [esp + 8], 0
10066b: mov ecx, 0xbde5e0
100670: xor edx, edx
100672: call 0xa5d30
100677: lea edi, [esi + 0xbef888]
10067d: movss xmm0, dword ptr [0xbe3098]; 0.0
100685: movss dword ptr [esp + 0x24], xmm0
10068b: movss dword ptr [esi + 0xbef7f8], xmm0
100693: xor eax, eax
100695: cmp dword ptr [esi + 0xbef86c], 0
10069c: jne 0x1006b1
10069e: mov eax, dword ptr [edi]
1006a0: mov ecx, eax
1006a2: shl ecx, 6
1006a5: mov eax, dword ptr [ecx + eax*4 + 0x2597a0]
1006ac: shr eax, 1
1006ae: and eax, 1
1006b1: mov dword ptr [esi + 0xbef890], eax
1006b7: movss xmm0, dword ptr [esp + 0x24]
1006bd: movss dword ptr [0xbe309c], xmm0; 0.0
1006c5: call 0xf38f0
1006ca: xorps xmm0, xmm0
1006cd: cvtsi2ss xmm0, eax
1006d1: mulss xmm0, dword ptr [0x74a4a4]; 0.0020000000949949026
1006d9: movss dword ptr [0xbe30a8], xmm0; 0.0
1006e1: movss xmm1, dword ptr [0xbe28f8]; 0.0
1006e9: ucomiss xmm1, dword ptr [esp + 0x24]
1006ee: jbe 0x100703
1006f0: subss xmm1, dword ptr [esp + 0x24]
1006f6: ucomiss xmm1, xmm0
1006f9: jbe 0x100703
1006fb: movss dword ptr [0xbe30a8], xmm1; 0.0
100703: cmp dword ptr [esi + 0xbef88c], 0
10070a: jle 0x10076b
10070c: mov eax, dword ptr [edi]
10070e: mov ecx, eax
100710: shl ecx, 6
100713: mov eax, dword ptr [ecx + eax*4 + 0x259774]
10071a: mov ecx, 0xbb2b9a
10071f: mov edx, 0xbb2b8b
100724: cmp byte ptr [esp + 0x40], 0
100729: cmovne edx, ecx
10072c: mov ecx, dword ptr [esp + 0x20]
100730: mov dword ptr [esp + 0x10], ecx
100734: mov dword ptr [esp + 0xc], eax
100738: mov dword ptr [esp + 8], edx
10073c: mov dword ptr [esp + 4], 1
100744: mov dword ptr [esp], 0xbde5e0
10074b: call 0xa5cf0
100750: mov ecx, dword ptr [0xbe30e0]
100756: call 0x108d00
10075b: mov ecx, dword ptr [0xbe30e0]
100761: call 0x109390
100766: jmp 0xfad45
10076b: lea eax, [esi + 0xbef890]
100771: cmp dword ptr [esp + 0x70], 0
100776: setne cl
100779: mov dword ptr [eax - 4], 0
100780: movss xmm0, dword ptr [esp + 0x24]
100786: movss dword ptr [esi + 0xbef7fc], xmm0
10078e: mov dword ptr [esi + 0xbef8b0], 0
100798: mov dword ptr [esi + 0xbef864], 0
1007a2: mov dword ptr [esi + 0xbef868], 0
1007ac: mov dword ptr [eax], 0
1007b2: mov eax, dword ptr [esp + 0x40]
1007b6: or al, cl
1007b8: jne 0x1007c8
1007ba: mov ecx, 0xbde5e0
1007bf: mov edx, dword ptr [esp + 0x30]
1007c3: call 0xa43f0
1007c8: cmp dword ptr [0xbe345c], 0
1007cf: jne 0x1007db
1007d1: mov dword ptr [0xbe30e4], 0
1007db: mov dword ptr [0xbe30e0], 0xffffffff
1007e5: mov dword ptr [0xbe30f8], 0
1007ef: jmp 0xfad45
1007f4: movss xmm0, dword ptr [0xbe3098]; 0.0
1007fc: subss xmm0, dword ptr [0xbe309c]; 0.0
100804: movss xmm1, dword ptr [0x74a460]; 0.44999998807907104
10080c: ucomiss xmm1, xmm0
10080f: mov edx, dword ptr [esp + 0x2c]
100813: ja 0xfad45
100819: mov eax, 0xb54972
10081e: movss xmm0, dword ptr [0x74a494]; 0.0010000000474974513
100826: ucomiss xmm0, xmm2
100829: ja 0xfe648
10082f: movaps xmm0, xmmword ptr [esp + 0x60]
100834: movss dword ptr [esp + 4], xmm0
10083a: movss dword ptr [esp], xmm3
10083f: mov ecx, edi
100841: call 0x1087a0
100846: xor ecx, ecx
100848: cmp eax, 1
10084b: sete cl
10084e: mov dword ptr [0xbe30e8], ecx
100854: test eax, eax
100856: je 0x10085d
100858: xorps xmm0, xmm0
10085b: jmp 0x10086b
10085d: movss xmm0, dword ptr [0xbe3458]; 0.0
100865: addss xmm0, dword ptr [esp + 0x60]
10086b: movss dword ptr [0xbe3458], xmm0; 0.0
100873: ucomiss xmm0, dword ptr [0x74a358]
10087a: jbe 0xfad45
100880: mov dword ptr [0xbe3440], 0
10088a: mov dword ptr [esp + 8], 0xb547be
100892: mov dword ptr [esp + 4], 4
10089a: jmp 0x1004ee
10089f: nop 
1008a0: xor eax, eax
1008a2: cmp dword ptr [0xbe30b0], 0
1008a9: jle 0x1008ac
1008ab: ret 
1008ac: movss xmm0, dword ptr [0xbe1934]; 0.0
1008b4: ucomiss xmm0, dword ptr [0xbe3098]
1008bb: jbe 0x1008ab
1008bd: push ebp
1008be: mov ebp, esp
1008c0: push esi
1008c1: and esp, 0xfffffff8
1008c4: sub esp, 0x18
1008c7: movzx esi, byte ptr [0xbe21a6]
1008ce: test esi, esi
1008d0: je 0x100a34
1008d6: mov eax, esi
1008d8: imul dword ptr [0xbe30b4]
1008de: mov ecx, edx
1008e0: mov edx, 0xa
1008e5: mul edx
1008e7: lea ecx, [ecx + ecx*4]
1008ea: lea ecx, [edx + ecx*2]
1008ed: push 0
1008ef: push 0x64
1008f1: push ecx
1008f2: push eax
1008f3: call 0x13ce50
1008f8: cmp eax, 2
1008fb: mov ecx, 1
100900: cmovge ecx, eax
100903: mov dword ptr [0xbe30b0], ecx
100909: mov ecx, 0xbde5e0
10090e: call 0xa90a0
100913: push 0xc
100915: push 0
100917: push 0xbec920
10091c: call 0x137420
100921: add esp, 0xc
100924: xorps xmm0, xmm0
100927: movlps qword ptr [0xbed338], xmm0
10092e: mov dword ptr [0xbec5e4], 0
100938: mov dword ptr [0xbe30e4], 0
100942: mov dword ptr [0xbe30e0], 0xffffffff
10094c: mov dword ptr [0xbe30a4], 0xc2c80000
