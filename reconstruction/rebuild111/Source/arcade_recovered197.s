.def @feat.00; .scl 3; .type 0; .endef
.globl @feat.00
.set @feat.00, 1
/* Recovered original 1.10.0 arcade logic. Generated; edit relocation generator. */
.intel_syntax noprefix
.text
.globl _arcade197_input
_arcade197_input:
push ebp
push ebx
push esi
push edi
mov eax, esp
and esp, -16
sub esp, 0x1800
mov dword ptr [esp + 0x17f0], eax
mov ecx, dword ptr [eax + 20]
mov dword ptr [esp + 0x50], ecx
jmp .L1d343
.Larcade_input_done:
mov esp, dword ptr [esp + 0x17f0]
pop edi
pop esi
pop ebx
pop ebp
ret
.globl _arcade197_tick
_arcade197_tick:
push ebp
push ebx
push esi
push edi
mov eax, esp
and esp, -16
sub esp, 0x1800
mov dword ptr [esp + 0x17f0], eax
mov ecx, dword ptr [eax + 20]
mov dword ptr [esp + 0x254], ecx
xorps xmm0, xmm0
movaps xmmword ptr [esp + 0xb0], xmm0
mov ecx, dword ptr [eax + 24]
mov dword ptr [esp + 0xb0], ecx
jmp .L1e44d
.Larcade_tick_done:
mov esp, dword ptr [esp + 0x17f0]
pop edi
pop esi
pop ebx
pop ebp
ret
.globl _arcade197_reset
_arcade197_reset:
mov ecx, dword ptr [esp + 4]
mov edx, dword ptr [esp + 8]
jmp .Lcc5a0
.L1d343:
test byte ptr [esp + 0x50], 0x10
.L1d348:
je .L1d35b
.L1d34a:
xor eax, eax
.L1d34c:
cmp dword ptr [_arcade197_state + 28], 0
.L1d353:
sete al
.L1d356:
mov dword ptr [_arcade197_state + 28], eax
.L1d35b:
cmp dword ptr [_arcade197_state + 20], 0
.L1d362:
je .L1d485
.L1d368:
test byte ptr [esp + 0x50], 2
.L1d36d:
je .Larcade_input_done
.L1d373:
mov edx, dword ptr [_arcade197_state + 4]
.L1d379:
mov ecx, dword ptr [_arcade197_state]
.L1d37f:
call .Lcc5a0
.L1d384:
jmp .Larcade_input_done
.L1d485:
cmp dword ptr [_arcade197_state + 28], 0
.L1d48c:
jne .Larcade_input_done
.L1d492:
mov eax, dword ptr [_arcade197_state]
.L1d497:
cmp eax, 2
.L1d49a:
jne .L1da69
.L1d4a0:
cmp dword ptr [_arcade197_state + 1264], 0
.L1d4a7:
jne .L1da69
.L1d4ad:
xor eax, eax
.L1d4af:
test dword ptr [esp + 0x50], 0x400
.L1d4b7:
jne .L1d4ec
.L1d4b9:
mov eax, 1
.L1d4be:
test dword ptr [esp + 0x50], 0x800
.L1d4c6:
jne .L1d4ec
.L1d4c8:
mov eax, 2
.L1d4cd:
test dword ptr [esp + 0x50], 0x1000
.L1d4d5:
jne .L1d4ec
.L1d4d7:
test dword ptr [esp + 0x50], 0x2000
.L1d4df:
mov eax, dword ptr [_arcade197_state + 1260]
.L1d4e4:
mov ecx, 3
.L1d4e9:
cmovne eax, ecx
.L1d4ec:
mov ecx, dword ptr [_arcade197_state + 1256]
.L1d4f2:
cmp eax, ecx
.L1d4f4:
je .L1dc37
.L1d4fa:
xor ecx, eax
.L1d4fc:
cmp ecx, 1
.L1d4ff:
je .L1dc37
.L1d505:
mov dword ptr [_arcade197_state + 1260], eax
.L1d50a:
mov eax, offset _arcade197_state + 1264
.L1d50f:
jmp .L1dc31
.L1da69:
cmp eax, 4
.L1da6c:
jne .L1dc37
.L1da72:
movzx eax, byte ptr [_arcade197_state + 1284]
.L1da79:
test dword ptr [esp + 0x50], 0x400
.L1da81:
je .L1da89
.L1da83:
mov bl, 0xfc
.L1da85:
cmp al, 3
.L1da87:
ja .L1dabd
.L1da89:
test dword ptr [esp + 0x50], 0x800
.L1da91:
je .L1da99
.L1da93:
mov bl, 4
.L1da95:
cmp al, 0xc
.L1da97:
jb .L1dabd
.L1da99:
mov ecx, eax
.L1da9b:
and cl, 3
.L1da9e:
test dword ptr [esp + 0x50], 0x1000
.L1daa6:
je .L1daae
.L1daa8:
mov bl, 0xff
.L1daaa:
test cl, cl
.L1daac:
jne .L1dabd
.L1daae:
mov edx, dword ptr [esp + 0x50]
.L1dab2:
shr edx, 0xd
.L1dab5:
cmp cl, 3
.L1dab8:
setne bl
.L1dabb:
and bl, dl
.L1dabd:
add bl, al
.L1dabf:
test byte ptr [esp + 0x50], 2
.L1dac4:
mov byte ptr [_arcade197_state + 1284], bl
.L1daca:
je .Larcade_input_done
.L1dad0:
cmp bl, 0xf
.L1dad3:
ja .L1dc37
.L1dad9:
movzx edi, bl
.L1dadc:
mov eax, edi
.L1dade:
and eax, 3
.L1dae1:
movzx ecx, byte ptr [_arcade197_state + 1285]
.L1dae8:
and ecx, 3
.L1daeb:
sub eax, ecx
.L1daed:
mov dword ptr [esp], eax
.L1daf0:
call .L132bc0
.L1daf5:
mov esi, eax
.L1daf7:
mov eax, edi
.L1daf9:
shr eax, 2
.L1dafc:
movzx ecx, byte ptr [_arcade197_state + 1285]
.L1db03:
shr ecx, 2
.L1db06:
sub eax, ecx
.L1db08:
mov dword ptr [esp], eax
.L1db0b:
call .L132bc0
.L1db10:
add eax, esi
.L1db12:
cmp eax, 1
.L1db15:
jne .L1dc37
.L1db1b:
movzx eax, byte ptr [edi + _arcade197_state + 1268]
.L1db22:
movzx ecx, byte ptr [_arcade197_state + 1285]
.L1db29:
mov byte ptr [ecx + _arcade197_state + 1268], al
.L1db2f:
mov byte ptr [edi + _arcade197_state + 1268], 0
.L1db36:
mov byte ptr [_arcade197_state + 1285], bl
.L1db3c:
inc dword ptr [_arcade197_state + 8]
.L1db42:
cmp byte ptr [_arcade197_state + 1278], 0xb
.L1db49:
setne al
.L1db4c:
shl al, 2
.L1db4f:
cmp byte ptr [_arcade197_state + 1279], 0xc
.L1db56:
setne dl
.L1db59:
shl dl, 3
.L1db5c:
or dl, al
.L1db5e:
cmp byte ptr [_arcade197_state + 1276], 9
.L1db65:
setne al
.L1db68:
cmp byte ptr [_arcade197_state + 1277], 0xa
.L1db6f:
setne cl
.L1db72:
add cl, cl
.L1db74:
or cl, al
.L1db76:
or cl, dl
.L1db78:
cmp byte ptr [_arcade197_state + 1270], 3
.L1db7f:
setne al
.L1db82:
shl al, 2
.L1db85:
cmp byte ptr [_arcade197_state + 1271], 4
.L1db8c:
setne dl
.L1db8f:
shl dl, 3
.L1db92:
or dl, al
.L1db94:
cmp byte ptr [_arcade197_state + 1268], 1
.L1db9b:
setne ah
.L1db9e:
cmp byte ptr [_arcade197_state + 1269], 2
.L1dba5:
setne al
.L1dba8:
add al, al
.L1dbaa:
or al, ah
.L1dbac:
or al, dl
.L1dbae:
or al, cl
.L1dbb0:
cmp byte ptr [_arcade197_state + 1282], 0xf
.L1dbb7:
setne cl
.L1dbba:
shl cl, 2
.L1dbbd:
cmp byte ptr [_arcade197_state + 1283], 0
.L1dbc4:
setne dl
.L1dbc7:
shl dl, 3
.L1dbca:
or dl, cl
.L1dbcc:
cmp byte ptr [_arcade197_state + 1280], 0xd
.L1dbd3:
setne ah
.L1dbd6:
cmp byte ptr [_arcade197_state + 1281], 0xe
.L1dbdd:
setne cl
.L1dbe0:
add cl, cl
.L1dbe2:
or cl, ah
.L1dbe4:
or cl, dl
.L1dbe6:
cmp byte ptr [_arcade197_state + 1274], 7
.L1dbed:
setne dl
.L1dbf0:
shl dl, 2
.L1dbf3:
cmp byte ptr [_arcade197_state + 1275], 8
.L1dbfa:
setne ah
.L1dbfd:
shl ah, 3
.L1dc00:
or ah, dl
.L1dc02:
cmp byte ptr [_arcade197_state + 1272], 5
.L1dc09:
setne dl
.L1dc0c:
cmp byte ptr [_arcade197_state + 1273], 6
.L1dc13:
setne ch
.L1dc16:
add ch, ch
.L1dc18:
or ch, dl
.L1dc1a:
or ch, ah
.L1dc1c:
or ch, cl
.L1dc1e:
or ch, al
.L1dc20:
jne .L1dc37
.L1dc22:
mov dword ptr [_arcade197_state + 20], 1
.L1dc2c:
mov eax, offset _arcade197_state + 24
.L1dc31:
mov dword ptr [eax], 1
.L1dc37:
test byte ptr [esp + 0x50], 2
.L1dc3c:
mov eax, dword ptr [_arcade197_state]
.L1dc41:
je .L1e404
.L1dc47:
cmp eax, 3
.L1dc4a:
jne .L1e404
.L1dc50:
mov dword ptr [_arcade197_state + 1316], 1
.L1dc5a:
jmp .Larcade_input_done
.L1e404:
cmp eax, 5
.L1e407:
jne .Larcade_input_done
.L1e409:
xor eax, eax
.L1e40b:
test dword ptr [esp + 0x50], 0x400
.L1e413:
jne .L1e448
.L1e415:
mov eax, 1
.L1e41a:
test dword ptr [esp + 0x50], 0x800
.L1e422:
jne .L1e448
.L1e424:
mov eax, 2
.L1e429:
test dword ptr [esp + 0x50], 0x1000
.L1e431:
jne .L1e448
.L1e433:
test dword ptr [esp + 0x50], 0x2000
.L1e43b:
mov eax, dword ptr [_arcade197_state + 1260]
.L1e440:
mov ecx, 3
.L1e445:
cmovne eax, ecx
.L1e448:
mov dword ptr [_arcade197_state + 1260], eax
jmp .Larcade_input_done
.L1e44d:
cmp dword ptr [_arcade197_state + 20], 0
.L1e454:
jne .Larcade_tick_done
.L1e45a:
xorps xmm0, xmm0
.L1e45d:
ucomiss xmm0, dword ptr [esp + 0xb0]
.L1e465:
jae .Larcade_tick_done
.L1e46b:
cmp dword ptr [_arcade197_state + 28], 0
.L1e472:
jne .Larcade_tick_done
.L1e478:
movaps xmm0, xmmword ptr [esp + 0xb0]
.L1e480:
movss dword ptr [esp], xmm0
.L1e485:
call .L132b30
.L1e48a:
test eax, 0x100
.L1e48f:
jne .Larcade_tick_done
.L1e495:
movss xmm0, dword ptr [_arcade197_state + 44]
.L1e49d:
addss xmm0, dword ptr [esp + 0xb0]
.L1e4a6:
movss dword ptr [_arcade197_state + 44], xmm0
.L1e4ae:
test dword ptr [esp + 0x254], 0x2000
.L1e4b9:
xorps xmm0, xmm0
.L1e4bc:
xorps xmm3, xmm3
.L1e4bf:
je .L1e4c9
.L1e4c1:
movss xmm3, dword ptr [.Larcade_constants197 + 40]
.L1e4c9:
test dword ptr [esp + 0x254], 0x1000
.L1e4d4:
xorps xmm1, xmm1
.L1e4d7:
je .L1e4e1
.L1e4d9:
movss xmm1, dword ptr [.Larcade_constants197 + 40]
.L1e4e1:
test dword ptr [esp + 0x254], 0x800
.L1e4ec:
xorps xmm2, xmm2
.L1e4ef:
je .L1e4f9
.L1e4f1:
movss xmm2, dword ptr [.Larcade_constants197 + 40]
.L1e4f9:
test dword ptr [esp + 0x254], 0x400
.L1e504:
je .L1e50e
.L1e506:
movss xmm0, dword ptr [.Larcade_constants197 + 40]
.L1e50e:
subss xmm2, xmm0
.L1e512:
subss xmm3, xmm1
.L1e516:
movss xmm0, dword ptr [.Larcade_constants197 + 1284]
.L1e51e:
mulss xmm3, xmm0
.L1e522:
movss dword ptr [esp + 0x70], xmm3
.L1e528:
mulss xmm2, xmm0
.L1e52c:
movss dword ptr [esp + 0x140], xmm2
.L1e535:
mov dword ptr [esp + 0x90], 0
.L1e540:
movss xmm0, dword ptr [_arcade197_state + 44]
.L1e548:
ucomiss xmm0, dword ptr [.Larcade_constants197 + 1284]
.L1e54f:
jb .Larcade_tick_done
.L1e555:
cmp dword ptr [_arcade197_state + 20], 0
.L1e55c:
jne .Larcade_tick_done
.L1e562:
movss xmm2, dword ptr [.Larcade_constants197 + 1288]
.L1e56a:
addss xmm0, xmm2
.L1e56e:
movss dword ptr [_arcade197_state + 44], xmm0
.L1e576:
movss xmm0, dword ptr [_arcade197_state + 36]
.L1e57e:
addss xmm0, dword ptr [.Larcade_constants197 + 1284]
.L1e586:
movss dword ptr [_arcade197_state + 36], xmm0
.L1e58e:
movss xmm1, dword ptr [_arcade197_state + 48]
.L1e596:
addss xmm1, xmm2
.L1e59a:
movss dword ptr [_arcade197_state + 48], xmm1
.L1e5a2:
mov eax, dword ptr [_arcade197_state]
.L1e5a7:
cmp eax, 5
.L1e5aa:
ja .L1f929
.L1e5b0:
jmp dword ptr [eax*4 + .Ltable1c00f4]
.L1e5b7:
movss xmm0, dword ptr [esp + 0x140]
.L1e5c0:
mulss xmm0, dword ptr [.Larcade_constants197 + 1220]
.L1e5c8:
addss xmm0, dword ptr [_arcade197_state + 68]
.L1e5d0:
movss dword ptr [esp + 4], xmm0
.L1e5d6:
mov dword ptr [esp], 0x3f63d70a
.L1e5dd:
call .L136dc0
.L1e5e2:
fstp dword ptr [esp + 4]
.L1e5e6:
mov dword ptr [esp], 0x3de147ae
.L1e5ed:
call .L136bf0
.L1e5f2:
fstp dword ptr [_arcade197_state + 68]
.L1e5f8:
movss xmm0, dword ptr [_arcade197_state + 56]
.L1e600:
subss xmm0, dword ptr [_arcade197_state + 72]
.L1e608:
movss dword ptr [esp + 4], xmm0
.L1e60e:
mov dword ptr [esp], 0x3bead65d
.L1e615:
call .L136dc0
.L1e61a:
fstp dword ptr [esp + 4]
.L1e61e:
mov dword ptr [esp], 0xbbead65d
.L1e625:
call .L136bf0
.L1e62a:
fstp dword ptr [esp + 0xf54]
.L1e631:
movss xmm0, dword ptr [esp + 0xf54]
.L1e63a:
addss xmm0, dword ptr [_arcade197_state + 72]
.L1e642:
movss dword ptr [_arcade197_state + 72], xmm0
.L1e64a:
movss dword ptr [esp + 4], xmm0
.L1e650:
mov dword ptr [esp], 0x3f63d70a
.L1e657:
call .L136dc0
.L1e65c:
fstp dword ptr [esp + 4]
.L1e660:
mov dword ptr [esp], 0x3de147ae
.L1e667:
call .L136bf0
.L1e66c:
fstp dword ptr [_arcade197_state + 72]
.L1e672:
xorps xmm0, xmm0
.L1e675:
movlps xmm0, qword ptr [_arcade197_state + 60]
.L1e67c:
xorps xmm2, xmm2
.L1e67f:
movlps xmm2, qword ptr [_arcade197_state + 52]
.L1e686:
movaps xmm1, xmm0
.L1e689:
mulps xmm1, xmmword ptr [.Larcade_constants197 + 1312]
.L1e690:
addps xmm1, xmm2
.L1e693:
movlps qword ptr [_arcade197_state + 52], xmm1
.L1e69a:
shufps xmm1, xmm1, 0x55
.L1e69e:
movss xmm2, dword ptr [.Larcade_constants197 + 1400]
.L1e6a6:
ucomiss xmm2, xmm1
.L1e6a9:
shufps xmm0, xmm0, 0x55
.L1e6ad:
jbe .L1e6e3
.L1e6af:
mov dword ptr [_arcade197_state + 56], 0x3ccccccd
.L1e6b9:
movss dword ptr [esp], xmm0
.L1e6be:
call .L1369e0
.L1e6c3:
fstp dword ptr [esp + 0xf50]
.L1e6ca:
movss xmm0, dword ptr [esp + 0xf50]
.L1e6d3:
movss dword ptr [_arcade197_state + 64], xmm0
.L1e6db:
movss xmm1, dword ptr [_arcade197_state + 56]
.L1e6e3:
ucomiss xmm1, dword ptr [.Larcade_constants197 + 1404]
.L1e6ea:
jbe .L1e71f
.L1e6ec:
mov dword ptr [_arcade197_state + 56], 0x3f79999a
.L1e6f6:
movss dword ptr [esp], xmm0
.L1e6fb:
call .L1369e0
.L1e700:
fstp dword ptr [esp + 0xf4c]
.L1e707:
movss xmm0, dword ptr [esp + 0xf4c]
.L1e710:
xorps xmm0, xmmword ptr [.Larcade_constants197 + 64]
.L1e717:
movss dword ptr [_arcade197_state + 64], xmm0
.L1e71f:
movss xmm0, dword ptr [_arcade197_state + 60]
.L1e727:
xorps xmm1, xmm1
.L1e72a:
ucomiss xmm1, xmm0
.L1e72d:
jbe .L1e80a
.L1e733:
movss xmm1, dword ptr [_arcade197_state + 52]
.L1e73b:
movss xmm2, dword ptr [.Larcade_constants197 + 1408]
.L1e743:
ucomiss xmm2, xmm1
.L1e746:
jbe .L1e80a
.L1e74c:
ucomiss xmm1, dword ptr [.Larcade_constants197 + 1328]
.L1e753:
jbe .L1e80a
.L1e759:
movss xmm0, dword ptr [_arcade197_state + 56]
.L1e761:
subss xmm0, dword ptr [_arcade197_state + 68]
.L1e769:
movss dword ptr [esp], xmm0
.L1e76e:
call .L1369e0
.L1e773:
fstp dword ptr [esp + 0xf48]
.L1e77a:
movss xmm0, dword ptr [.Larcade_constants197 + 1340]
.L1e782:
ucomiss xmm0, dword ptr [esp + 0xf48]
.L1e78a:
movss xmm0, dword ptr [_arcade197_state + 60]
.L1e792:
jbe .L1e80a
.L1e794:
mov dword ptr [_arcade197_state + 52], 0x3d851eb8
.L1e79e:
movss dword ptr [esp], xmm0
.L1e7a3:
call .L1369e0
.L1e7a8:
fstp dword ptr [esp + 0xf44]
.L1e7af:
movss xmm0, dword ptr [esp + 0xf44]
.L1e7b8:
mulss xmm0, dword ptr [.Larcade_constants197 + 1412]
.L1e7c0:
movss dword ptr [esp + 4], xmm0
.L1e7c6:
mov dword ptr [esp], 0x3f4ccccd
.L1e7cd:
call .L136dc0
.L1e7d2:
fstp dword ptr [esp + 0xf40]
.L1e7d9:
movss xmm0, dword ptr [esp + 0xf40]
.L1e7e2:
movss dword ptr [_arcade197_state + 60], xmm0
.L1e7ea:
movss xmm1, dword ptr [_arcade197_state + 56]
.L1e7f2:
subss xmm1, dword ptr [_arcade197_state + 68]
.L1e7fa:
mulss xmm1, dword ptr [.Larcade_constants197 + 1416]
.L1e802:
movss dword ptr [_arcade197_state + 64], xmm1
.L1e80a:
ucomiss xmm0, dword ptr [.Larcade_constants197 + 3040]
.L1e811:
jbe .L1e8cb
.L1e817:
movss xmm0, dword ptr [_arcade197_state + 52]
.L1e81f:
ucomiss xmm0, dword ptr [.Larcade_constants197 + 1420]
.L1e826:
jbe .L1e8d3
.L1e82c:
movss xmm1, dword ptr [.Larcade_constants197 + 1332]
.L1e834:
ucomiss xmm1, xmm0
.L1e837:
jbe .L1e8d3
.L1e83d:
movss xmm0, dword ptr [_arcade197_state + 56]
.L1e845:
subss xmm0, dword ptr [_arcade197_state + 72]
.L1e84d:
movss dword ptr [esp], xmm0
.L1e852:
call .L1369e0
.L1e857:
fstp dword ptr [esp + 0xf3c]
.L1e85e:
movss xmm0, dword ptr [.Larcade_constants197 + 1340]
.L1e866:
ucomiss xmm0, dword ptr [esp + 0xf3c]
.L1e86e:
jbe .L1e8cb
.L1e870:
mov dword ptr [_arcade197_state + 52], 0x3f6f5c29
.L1e87a:
movss xmm0, dword ptr [_arcade197_state + 60]
.L1e882:
movss dword ptr [esp], xmm0
.L1e887:
call .L1369e0
.L1e88c:
fstp dword ptr [esp + 0xf38]
.L1e893:
movss xmm0, dword ptr [esp + 0xf38]
.L1e89c:
xorps xmm0, xmmword ptr [.Larcade_constants197 + 64]
.L1e8a3:
movss dword ptr [_arcade197_state + 60], xmm0
.L1e8ab:
movss xmm0, dword ptr [_arcade197_state + 56]
.L1e8b3:
subss xmm0, dword ptr [_arcade197_state + 72]
.L1e8bb:
mulss xmm0, dword ptr [.Larcade_constants197 + 1424]
.L1e8c3:
movss dword ptr [_arcade197_state + 64], xmm0
.L1e8cb:
movss xmm0, dword ptr [_arcade197_state + 52]
.L1e8d3:
xorps xmm1, xmm1
.L1e8d6:
ucomiss xmm1, xmm0
.L1e8d9:
ja .L1e8ec
.L1e8db:
movss xmm1, dword ptr [.Larcade_constants197 + 40]
.L1e8e3:
ucomiss xmm0, xmm1
.L1e8e6:
jbe .L1f929
.L1e8ec:
movss xmm1, dword ptr [.Larcade_constants197 + 40]
.L1e8f4:
ucomiss xmm0, xmm1
.L1e8f7:
jbe .L1f6d8
.L1e8fd:
mov eax, dword ptr [_arcade197_state + 8]
.L1e902:
inc eax
.L1e903:
mov dword ptr [_arcade197_state + 8], eax
.L1e908:
cmp eax, 7
.L1e90b:
jb .L1f6eb
.L1e911:
mov dword ptr [_arcade197_state + 20], 1
.L1e91b:
mov eax, offset _arcade197_state + 24
.L1e920:
jmp .L1f6e5
.L1e925:
movss xmm0, dword ptr [esp + 0x70]
.L1e92b:
mulss xmm0, dword ptr [.Larcade_constants197 + 1368]
.L1e933:
addss xmm0, dword ptr [_arcade197_state + 52]
.L1e93b:
movss dword ptr [esp + 4], xmm0
.L1e941:
mov dword ptr [esp], 0x3f75c28f
.L1e948:
call .L136dc0
.L1e94d:
fstp dword ptr [esp + 4]
.L1e951:
mov dword ptr [esp], 0x3d23d70a
.L1e958:
call .L136bf0
.L1e95d:
test byte ptr [esp + 0x254], 2
.L1e965:
fstp dword ptr [esp + 0xf70]
.L1e96c:
movss xmm0, dword ptr [esp + 0xf70]
.L1e975:
movss dword ptr [_arcade197_state + 52], xmm0
.L1e97d:
je .L1e9af
.L1e97f:
xorps xmm1, xmm1
.L1e982:
ucomiss xmm1, dword ptr [_arcade197_state + 48]
.L1e989:
jb .L1e9af
.L1e98b:
movss dword ptr [esp], xmm0
.L1e990:
mov dword ptr [esp + 8], 0xbf666666
.L1e998:
mov dword ptr [esp + 4], 0x3f6147ae
.L1e9a0:
call .Lccc90
.L1e9a5:
mov dword ptr [_arcade197_state + 48], 0x3e3851ec
.L1e9af:
imul eax, dword ptr [_arcade197_state + 4], 0x19660d
.L1e9b9:
add eax, 0x3c6ef35f
.L1e9be:
mov dword ptr [_arcade197_state + 4], eax
.L1e9c3:
test al, 0x7f
.L1e9c5:
jne .L1eaf2
.L1e9cb:
imul ecx, eax, 0x19660d
.L1e9d1:
add ecx, 0x3c6ef35f
.L1e9d7:
mov dword ptr [_arcade197_state + 4], ecx
.L1e9dd:
mov eax, ecx
.L1e9df:
mov edx, 0x38e38e39
.L1e9e4:
mul edx
.L1e9e6:
shr edx, 1
.L1e9e8:
and edx, 0xfffffffc
.L1e9eb:
lea eax, [edx + edx*8]
.L1e9ee:
sub ecx, eax
.L1e9f0:
cmp byte ptr [ecx + _arcade197_state + 76], 0
.L1e9f7:
je .L1eaf2
.L1e9fd:
mov eax, dword ptr [_arcade197_state + 16]
.L1ea02:
mov dword ptr [esp + 0x14e8], eax
.L1ea09:
mov dword ptr [esp + 0x14ec], 0
.L1ea14:
fild qword ptr [esp + 0x14e8]
.L1ea1b:
fstp dword ptr [esp + 0xf6c]
.L1ea22:
movss xmm0, dword ptr [esp + 0xf6c]
.L1ea2b:
mulss xmm0, dword ptr [.Larcade_constants197 + 1372]
.L1ea33:
addss xmm0, dword ptr [.Larcade_constants197 + 1376]
.L1ea3b:
movss dword ptr [esp + 0x60], xmm0
.L1ea41:
movzx eax, cl
.L1ea44:
imul eax, eax, 0x39
.L1ea47:
shr eax, 9
.L1ea4a:
xorps xmm1, xmm1
.L1ea4d:
cvtsi2ss xmm1, eax
.L1ea51:
mulss xmm1, dword ptr [.Larcade_constants197 + 1380]
.L1ea59:
movss xmm0, dword ptr [.Larcade_constants197 + 1384]
.L1ea61:
addss xmm1, xmm0
.L1ea65:
movss dword ptr [esp + 0xc0], xmm1
.L1ea6e:
lea eax, [eax + eax*8]
.L1ea71:
sub cl, al
.L1ea73:
movsx eax, cl
.L1ea76:
xorps xmm1, xmm1
.L1ea79:
cvtsi2ss xmm1, eax
.L1ea7d:
mulss xmm1, dword ptr [.Larcade_constants197 + 1388]
.L1ea85:
addss xmm1, xmm0
.L1ea89:
movss dword ptr [esp + 0xa0], xmm1
.L1ea92:
movss xmm0, dword ptr [_arcade197_state + 36]
.L1ea9a:
mulss xmm0, dword ptr [.Larcade_constants197 + 1220]
.L1eaa2:
movss dword ptr [esp], xmm0
.L1eaa7:
call .L1377c0
.L1eaac:
fstp dword ptr [esp + 0xf68]
.L1eab3:
movss xmm0, dword ptr [esp + 0xf68]
.L1eabc:
mulss xmm0, dword ptr [.Larcade_constants197 + 1228]
.L1eac4:
addss xmm0, dword ptr [esp + 0xa0]
.L1eacd:
movss xmm1, dword ptr [esp + 0x60]
.L1ead3:
movss dword ptr [esp + 8], xmm1
.L1ead9:
movss xmm1, dword ptr [esp + 0xc0]
.L1eae2:
movss dword ptr [esp + 4], xmm1
.L1eae8:
movss dword ptr [esp], xmm0
.L1eaed:
call .Lccc90
.L1eaf2:
cmp dword ptr [_arcade197_state + 20], 0
.L1eaf9:
jne .L1ed4c
.L1eaff:
xor esi, esi
.L1eb01:
lea edi, [esi*4]
.L1eb08:
cmp dword ptr [edi + edi*4 + _arcade197_state + 1340], 0
.L1eb10:
je .L1ed39
.L1eb16:
lea ebx, [edi + edi*4 + _arcade197_state + 1340]
.L1eb1d:
movss xmm0, dword ptr [edi + edi*4 + _arcade197_state + 1336]
.L1eb26:
movaps xmm1, xmm0
.L1eb29:
mulss xmm1, dword ptr [.Larcade_constants197 + 1284]
.L1eb31:
addss xmm1, dword ptr [edi + edi*4 + _arcade197_state + 1328]
.L1eb3a:
movss dword ptr [edi + edi*4 + _arcade197_state + 1328], xmm1
.L1eb43:
xorps xmm2, xmm2
.L1eb46:
ucomiss xmm2, xmm1
.L1eb49:
ja .L1ebc9
.L1eb4b:
movss xmm2, dword ptr [.Larcade_constants197 + 40]
.L1eb53:
ucomiss xmm1, xmm2
.L1eb56:
ja .L1ebc9
.L1eb58:
lea eax, [edi + edi*4 + _arcade197_state + 1324]
.L1eb5f:
mov dword ptr [esp + 0x60], eax
.L1eb63:
ucomiss xmm0, dword ptr [.Larcade_constants197 + 3040]
.L1eb6a:
jbe .L1ebdf
.L1eb6c:
ucomiss xmm1, dword ptr [.Larcade_constants197 + 1392]
.L1eb73:
jbe .L1ebdf
.L1eb75:
mov eax, dword ptr [esp + 0x60]
.L1eb79:
movss xmm0, dword ptr [eax]
.L1eb7d:
subss xmm0, dword ptr [_arcade197_state + 52]
.L1eb85:
movss dword ptr [esp], xmm0
.L1eb8a:
call .L1369e0
.L1eb8f:
fstp dword ptr [esp + 0xf64]
.L1eb96:
movss xmm0, dword ptr [.Larcade_constants197 + 1228]
.L1eb9e:
ucomiss xmm0, dword ptr [esp + 0xf64]
.L1eba6:
jbe .L1ebd4
.L1eba8:
mov dword ptr [ebx], 0
.L1ebae:
dec dword ptr [_arcade197_state + 12]
.L1ebb4:
jne .L1ed39
.L1ebba:
mov dword ptr [_arcade197_state + 20], 1
.L1ebc4:
jmp .L1ed39
.L1ebc9:
mov dword ptr [ebx], 0
.L1ebcf:
jmp .L1ed39
.L1ebd4:
lea eax, [edi + edi*4 + _arcade197_state + 1336]
.L1ebdb:
movss xmm0, dword ptr [eax]
.L1ebdf:
xorps xmm1, xmm1
.L1ebe2:
ucomiss xmm1, xmm0
.L1ebe5:
jbe .L1ed39
.L1ebeb:
lea eax, [edi + edi*4 + _arcade197_state + 1328]
.L1ebf2:
mov dword ptr [esp + 0xc0], eax
.L1ebf9:
xor edi, edi
.L1ebfb:
mov eax, edi
.L1ebfd:
cmp byte ptr [edi + _arcade197_state + 76], 0
.L1ec04:
je .L1ed15
.L1ec0a:
mov edx, edi
.L1ec0c:
movzx eax, dl
.L1ec0f:
imul eax, eax, 0x39
.L1ec12:
shr eax, 9
.L1ec15:
lea eax, [eax + eax*8]
.L1ec18:
neg eax
.L1ec1a:
movzx eax, al
.L1ec1d:
mov ecx, dword ptr [esp + 0x60]
.L1ec21:
movss xmm0, dword ptr [ecx]
.L1ec25:
movss dword ptr [esp + 0xa0], xmm0
.L1ec2e:
add eax, edi
.L1ec30:
movzx eax, al
.L1ec33:
xorps xmm0, xmm0
.L1ec36:
cvtsi2ss xmm0, eax
.L1ec3a:
mulss xmm0, dword ptr [.Larcade_constants197 + 1388]
.L1ec42:
addss xmm0, dword ptr [.Larcade_constants197 + 1384]
.L1ec4a:
movss dword ptr [esp + 0xd0], xmm0
.L1ec53:
movss xmm0, dword ptr [_arcade197_state + 36]
.L1ec5b:
mulss xmm0, dword ptr [.Larcade_constants197 + 1220]
.L1ec63:
movss dword ptr [esp], xmm0
.L1ec68:
call .L1377c0
.L1ec6d:
fstp dword ptr [esp + 0xf60]
.L1ec74:
movss xmm0, dword ptr [esp + 0xf60]
.L1ec7d:
mulss xmm0, dword ptr [.Larcade_constants197 + 1228]
.L1ec85:
addss xmm0, dword ptr [esp + 0xd0]
.L1ec8e:
movss xmm1, dword ptr [esp + 0xa0]
.L1ec97:
subss xmm1, xmm0
.L1ec9b:
movss dword ptr [esp], xmm1
.L1eca0:
call .L1369e0
.L1eca5:
fstp dword ptr [esp + 0xf5c]
.L1ecac:
movss xmm0, dword ptr [.Larcade_constants197 + 1396]
.L1ecb4:
ucomiss xmm0, dword ptr [esp + 0xf5c]
.L1ecbc:
jbe .L1ed15
.L1ecbe:
mov eax, edi
.L1ecc0:
movzx eax, al
.L1ecc3:
imul eax, eax, 0x39
.L1ecc6:
shr eax, 9
.L1ecc9:
mov ecx, dword ptr [esp + 0xc0]
.L1ecd0:
movss xmm0, dword ptr [ecx]
.L1ecd4:
movzx eax, al
.L1ecd7:
xorps xmm1, xmm1
.L1ecda:
cvtsi2ss xmm1, eax
.L1ecde:
mulss xmm1, dword ptr [.Larcade_constants197 + 1380]
.L1ece6:
addss xmm1, dword ptr [.Larcade_constants197 + 1384]
.L1ecee:
subss xmm0, xmm1
.L1ecf2:
movss dword ptr [esp], xmm0
.L1ecf7:
call .L1369e0
.L1ecfc:
fstp dword ptr [esp + 0xf58]
.L1ed03:
movss xmm0, dword ptr [.Larcade_constants197 + 1396]
.L1ed0b:
ucomiss xmm0, dword ptr [esp + 0xf58]
.L1ed13:
ja .L1ed25
.L1ed15:
mov eax, edi
.L1ed17:
inc eax
.L1ed18:
mov edi, eax
.L1ed1a:
cmp eax, 0x24
.L1ed1d:
jne .L1ebfb
.L1ed23:
jmp .L1ed39
.L1ed25:
mov byte ptr [edi + _arcade197_state + 76], 0
.L1ed2c:
mov dword ptr [ebx], 0
.L1ed32:
add dword ptr [_arcade197_state + 8], 0xa
.L1ed39:
cmp esi, 0x16
.L1ed3c:
ja .L1ed4c
.L1ed3e:
inc esi
.L1ed3f:
cmp dword ptr [_arcade197_state + 20], 0
.L1ed46:
je .L1eb01
.L1ed4c:
movzx eax, byte ptr [_arcade197_state + 76]
.L1ed53:
movzx ecx, byte ptr [_arcade197_state + 77]
.L1ed5a:
add ecx, eax
.L1ed5c:
movzx edx, byte ptr [_arcade197_state + 78]
.L1ed63:
movzx eax, byte ptr [_arcade197_state + 79]
.L1ed6a:
add eax, edx
.L1ed6c:
add eax, ecx
.L1ed6e:
movzx ecx, byte ptr [_arcade197_state + 80]
.L1ed75:
movzx edx, byte ptr [_arcade197_state + 81]
.L1ed7c:
add edx, ecx
.L1ed7e:
movzx ecx, byte ptr [_arcade197_state + 82]
.L1ed85:
add ecx, edx
.L1ed87:
add ecx, eax
.L1ed89:
movzx eax, byte ptr [_arcade197_state + 83]
.L1ed90:
movzx edx, byte ptr [_arcade197_state + 84]
.L1ed97:
add edx, eax
.L1ed99:
movzx esi, byte ptr [_arcade197_state + 85]
.L1eda0:
add esi, edx
.L1eda2:
movzx eax, byte ptr [_arcade197_state + 86]
.L1eda9:
add eax, esi
.L1edab:
add eax, ecx
.L1edad:
movzx ecx, byte ptr [_arcade197_state + 87]
.L1edb4:
movzx edx, byte ptr [_arcade197_state + 88]
.L1edbb:
add edx, ecx
.L1edbd:
movzx ecx, byte ptr [_arcade197_state + 89]
.L1edc4:
add ecx, edx
.L1edc6:
movzx edx, byte ptr [_arcade197_state + 90]
.L1edcd:
add edx, ecx
.L1edcf:
movzx ecx, byte ptr [_arcade197_state + 91]
.L1edd6:
add ecx, edx
.L1edd8:
add ecx, eax
.L1edda:
movzx eax, byte ptr [_arcade197_state + 92]
.L1ede1:
movzx edx, byte ptr [_arcade197_state + 93]
.L1ede8:
add edx, eax
.L1edea:
movzx eax, byte ptr [_arcade197_state + 94]
.L1edf1:
add eax, edx
.L1edf3:
movzx edx, byte ptr [_arcade197_state + 95]
.L1edfa:
add edx, eax
.L1edfc:
movzx esi, byte ptr [_arcade197_state + 96]
.L1ee03:
add esi, edx
.L1ee05:
movzx eax, byte ptr [_arcade197_state + 97]
.L1ee0c:
add eax, esi
.L1ee0e:
add eax, ecx
.L1ee10:
movzx ecx, byte ptr [_arcade197_state + 98]
.L1ee17:
movzx edx, byte ptr [_arcade197_state + 99]
.L1ee1e:
add edx, ecx
.L1ee20:
movzx ecx, byte ptr [_arcade197_state + 100]
.L1ee27:
add ecx, edx
.L1ee29:
movzx edx, byte ptr [_arcade197_state + 101]
.L1ee30:
add edx, ecx
.L1ee32:
movzx ecx, byte ptr [_arcade197_state + 102]
.L1ee39:
add ecx, edx
.L1ee3b:
movzx edx, byte ptr [_arcade197_state + 103]
.L1ee42:
add edx, ecx
.L1ee44:
movzx ecx, byte ptr [_arcade197_state + 104]
.L1ee4b:
add ecx, edx
.L1ee4d:
add ecx, eax
.L1ee4f:
movzx eax, byte ptr [_arcade197_state + 105]
.L1ee56:
movzx edx, byte ptr [_arcade197_state + 106]
.L1ee5d:
add edx, eax
.L1ee5f:
movzx eax, byte ptr [_arcade197_state + 107]
.L1ee66:
add eax, edx
.L1ee68:
movzx edx, byte ptr [_arcade197_state + 108]
.L1ee6f:
add edx, eax
.L1ee71:
movzx eax, byte ptr [_arcade197_state + 109]
.L1ee78:
add eax, edx
.L1ee7a:
movzx edx, byte ptr [_arcade197_state + 110]
.L1ee81:
add edx, eax
.L1ee83:
add edx, ecx
.L1ee85:
movzx eax, byte ptr [_arcade197_state + 111]
.L1ee8c:
add eax, edx
.L1ee8e:
jne .L1f929
.L1ee94:
mov eax, dword ptr [_arcade197_state + 16]
.L1ee99:
cmp eax, 5
.L1ee9c:
je .L1f872
.L1eea2:
inc eax
.L1eea3:
mov dword ptr [_arcade197_state + 16], eax
.L1eea8:
mov dword ptr [esp + 8], 0x24
.L1eeb0:
mov dword ptr [esp + 4], 1
.L1eeb8:
mov dword ptr [esp], offset _arcade197_state + 76
.L1eebf:
call .L137420
.L1eec4:
mov dword ptr [esp + 8], 0x1e0
.L1eecc:
mov dword ptr [esp + 4], 0
.L1eed4:
mov dword ptr [esp], offset _arcade197_state + 1324
.L1eedb:
call .L137420
.L1eee0:
jmp .L1f929
.L1eee5:
movss xmm0, dword ptr [_arcade197_state + 40]
.L1eeed:
addss xmm0, dword ptr [.Larcade_constants197 + 1284]
.L1eef5:
movss dword ptr [_arcade197_state + 40], xmm0
.L1eefd:
mov eax, dword ptr [_arcade197_state + 8]
.L1ef02:
mov dword ptr [esp + 0x14f0], eax
.L1ef09:
mov dword ptr [esp + 0x14f4], 0
.L1ef14:
fild qword ptr [esp + 0x14f0]
.L1ef1b:
fstp dword ptr [esp + 0xf78]
.L1ef22:
movss xmm0, dword ptr [esp + 0xf78]
.L1ef2b:
mulss xmm0, dword ptr [.Larcade_constants197 + 1360]
.L1ef33:
addss xmm0, dword ptr [.Larcade_constants197 + 1364]
.L1ef3b:
movss dword ptr [esp + 4], xmm0
.L1ef41:
mov dword ptr [esp], 0x3d851eb8
.L1ef48:
call .L136bf0
.L1ef4d:
fstp dword ptr [esp + 0xf74]
.L1ef54:
movss xmm0, dword ptr [esp + 0xf74]
.L1ef5d:
movss xmm1, dword ptr [_arcade197_state + 40]
.L1ef65:
ucomiss xmm1, xmm0
.L1ef68:
jb .L1f929
.L1ef6e:
subss xmm1, xmm0
.L1ef72:
movss dword ptr [_arcade197_state + 40], xmm1
.L1ef7a:
mov esi, dword ptr [_arcade197_state + 1260]
.L1ef80:
mov dword ptr [_arcade197_state + 1256], esi
.L1ef86:
mov dword ptr [_arcade197_state + 1264], 0
.L1ef90:
movzx edx, word ptr [_arcade197_state + 468]
.L1ef97:
imul eax, edx, 0x642d
.L1ef9d:
shr eax, 0x10
.L1efa0:
mov ecx, edx
.L1efa2:
sub ecx, eax
.L1efa4:
movzx ecx, cx
.L1efa7:
shr ecx, 1
.L1efa9:
add ecx, eax
.L1efab:
shr ecx, 4
.L1efae:
lea edi, [ecx + ecx*2]
.L1efb1:
shl edi, 3
.L1efb4:
mov eax, ecx
.L1efb6:
sub eax, edi
.L1efb8:
add eax, edx
.L1efba:
xor edx, edx
.L1efbc:
cmp esi, 3
.L1efbf:
sete dl
.L1efc2:
xor ebx, ebx
.L1efc4:
cmp esi, 2
.L1efc7:
sete bl
.L1efca:
sub edx, ebx
.L1efcc:
movzx eax, ax
.L1efcf:
add edx, eax
.L1efd1:
xor eax, eax
.L1efd3:
cmp esi, 1
.L1efd6:
sete al
.L1efd9:
sbb eax, 0
.L1efdc:
add eax, ecx
.L1efde:
lea esi, [eax + eax*2]
.L1efe1:
shl esi, 3
.L1efe4:
sub esi, eax
.L1efe6:
add esi, edx
.L1efe8:
cmp eax, 0x11
.L1efeb:
mov ecx, 0xffffffff
.L1eff0:
cmovge esi, ecx
.L1eff3:
test eax, eax
.L1eff5:
cmovs esi, ecx
.L1eff8:
cmp edx, 0x17
.L1effb:
cmovae esi, ecx
.L1effe:
test esi, esi
.L1f000:
js .L1f060
.L1f002:
movzx ecx, word ptr [_arcade197_state + 1252]
.L1f009:
xor ebx, ebx
.L1f00b:
cmp esi, ecx
.L1f00d:
setne bl
.L1f010:
movzx eax, word ptr [_arcade197_state + 1250]
.L1f017:
mov edx, eax
.L1f019:
sub edx, ebx
.L1f01b:
je .L1f030
.L1f01d:
xor edi, edi
.L1f01f:
movzx ebx, word ptr [edi + edi + _arcade197_state + 468]
.L1f027:
cmp esi, ebx
.L1f029:
je .L1f060
.L1f02b:
inc edi
.L1f02c:
cmp edx, edi
.L1f02e:
jne .L1f01f
.L1f030:
cmp esi, ecx
.L1f032:
je .L1f728
.L1f038:
lea eax, [eax + eax - 2]
.L1f03c:
mov dword ptr [esp + 8], eax
.L1f040:
mov dword ptr [esp + 4], offset _arcade197_state + 468
.L1f048:
mov dword ptr [esp], offset _arcade197_state + 470
.L1f04f:
call .L1373d0
.L1f054:
mov word ptr [_arcade197_state + 468], si
.L1f05b:
jmp .L1f929
.L1f060:
mov dword ptr [_arcade197_state + 20], 1
.L1f06a:
jmp .L1f929
.L1f06f:
movss xmm0, dword ptr [esp + 0x70]
.L1f075:
mulss xmm0, dword ptr [.Larcade_constants197 + 1220]
.L1f07d:
addss xmm0, dword ptr [_arcade197_state + 68]
.L1f085:
movss dword ptr [esp + 4], xmm0
.L1f08b:
mov dword ptr [esp], 0x3f666666
.L1f092:
call .L136dc0
.L1f097:
fstp dword ptr [esp + 4]
.L1f09b:
mov dword ptr [esp], 0x3dcccccd
.L1f0a2:
call .L136bf0
.L1f0a7:
fstp dword ptr [esp + 0xf90]
.L1f0ae:
movss xmm0, dword ptr [esp + 0xf90]
.L1f0b7:
movss dword ptr [_arcade197_state + 68], xmm0
.L1f0bf:
cmp dword ptr [_arcade197_state + 1316], 0
.L1f0c6:
je .L1f7c9
.L1f0cc:
xorps xmm2, xmm2
.L1f0cf:
movlps xmm2, qword ptr [_arcade197_state + 52]
.L1f0d6:
xorps xmm0, xmm0
.L1f0d9:
movlps xmm0, qword ptr [_arcade197_state + 60]
.L1f0e0:
movaps xmm1, xmm0
.L1f0e3:
mulps xmm1, xmmword ptr [.Larcade_constants197 + 1312]
.L1f0ea:
movaps xmmword ptr [esp + 0x60], xmm2
.L1f0ef:
addps xmm1, xmm2
.L1f0f2:
movlps qword ptr [_arcade197_state + 52], xmm1
.L1f0f9:
movss xmm2, dword ptr [.Larcade_constants197 + 1328]
.L1f101:
ucomiss xmm2, xmm1
.L1f104:
jbe .L1f13a
.L1f106:
mov dword ptr [_arcade197_state + 52], 0x3ca3d70a
.L1f110:
movss dword ptr [esp], xmm0
.L1f115:
call .L1369e0
.L1f11a:
fstp dword ptr [esp + 0xf8c]
.L1f121:
movss xmm0, dword ptr [esp + 0xf8c]
.L1f12a:
movss dword ptr [_arcade197_state + 60], xmm0
.L1f132:
movss xmm1, dword ptr [_arcade197_state + 52]
.L1f13a:
ucomiss xmm1, dword ptr [.Larcade_constants197 + 1332]
.L1f141:
jbe .L1f176
.L1f143:
mov dword ptr [_arcade197_state + 52], 0x3f7ae148
.L1f14d:
movss dword ptr [esp], xmm0
.L1f152:
call .L1369e0
.L1f157:
fstp dword ptr [esp + 0xf88]
.L1f15e:
movss xmm0, dword ptr [esp + 0xf88]
.L1f167:
xorps xmm0, xmmword ptr [.Larcade_constants197 + 64]
.L1f16e:
movss dword ptr [_arcade197_state + 60], xmm0
.L1f176:
movss xmm0, dword ptr [_arcade197_state + 56]
.L1f17e:
movss xmm1, dword ptr [.Larcade_constants197 + 1328]
.L1f186:
ucomiss xmm1, xmm0
.L1f189:
movss xmm1, dword ptr [_arcade197_state + 64]
.L1f191:
jbe .L1f1c7
.L1f193:
mov dword ptr [_arcade197_state + 56], 0x3ca3d70a
.L1f19d:
movss dword ptr [esp], xmm1
.L1f1a2:
call .L1369e0
.L1f1a7:
fstp dword ptr [esp + 0xf84]
.L1f1ae:
movss xmm1, dword ptr [esp + 0xf84]
.L1f1b7:
movss dword ptr [_arcade197_state + 64], xmm1
.L1f1bf:
movss xmm0, dword ptr [_arcade197_state + 56]
.L1f1c7:
ucomiss xmm1, dword ptr [.Larcade_constants197 + 3040]
.L1f1ce:
jbe .L1f291
.L1f1d4:
movaps xmm2, xmmword ptr [esp + 0x60]
.L1f1d9:
shufps xmm2, xmm2, 0x55
.L1f1dd:
movss xmm1, dword ptr [.Larcade_constants197 + 1336]
.L1f1e5:
ucomiss xmm1, xmm2
.L1f1e8:
jb .L1f291
.L1f1ee:
ucomiss xmm0, dword ptr [.Larcade_constants197 + 1336]
.L1f1f5:
jb .L1f291
.L1f1fb:
movss xmm0, dword ptr [_arcade197_state + 52]
.L1f203:
subss xmm0, dword ptr [_arcade197_state + 68]
.L1f20b:
movss dword ptr [esp], xmm0
.L1f210:
call .L1369e0
.L1f215:
fstp dword ptr [esp + 0xf80]
.L1f21c:
movss xmm0, dword ptr [.Larcade_constants197 + 1340]
.L1f224:
ucomiss xmm0, dword ptr [esp + 0xf80]
.L1f22c:
jbe .L1f289
.L1f22e:
mov dword ptr [_arcade197_state + 56], 0x3f68f5c3
.L1f238:
movss xmm0, dword ptr [_arcade197_state + 64]
.L1f240:
movss dword ptr [esp], xmm0
.L1f245:
call .L1369e0
.L1f24a:
fstp dword ptr [esp + 0xf7c]
.L1f251:
movss xmm0, dword ptr [esp + 0xf7c]
.L1f25a:
xorps xmm0, xmmword ptr [.Larcade_constants197 + 64]
.L1f261:
movss dword ptr [_arcade197_state + 64], xmm0
.L1f269:
movss xmm0, dword ptr [_arcade197_state + 52]
.L1f271:
subss xmm0, dword ptr [_arcade197_state + 68]
.L1f279:
mulss xmm0, dword ptr [.Larcade_constants197 + 1344]
.L1f281:
movss dword ptr [_arcade197_state + 60], xmm0
.L1f289:
movss xmm0, dword ptr [_arcade197_state + 56]
.L1f291:
movss xmm1, dword ptr [.Larcade_constants197 + 40]
.L1f299:
ucomiss xmm0, xmm1
.L1f29c:
jbe .L1f7d6
.L1f2a2:
dec dword ptr [_arcade197_state + 12]
.L1f2a8:
jne .L1f2b4
.L1f2aa:
mov dword ptr [_arcade197_state + 20], 1
.L1f2b4:
mov dword ptr [_arcade197_state + 1316], 0
.L1f2be:
movss xmm0, dword ptr [_arcade197_state + 68]
.L1f2c6:
movss dword ptr [_arcade197_state + 52], xmm0
.L1f2ce:
mov dword ptr [_arcade197_state + 56], 0x3f570a3d
.L1f2d8:
mov dword ptr [_arcade197_state + 64], 0xbef5c28f
.L1f2e2:
jmp .L1f857
.L1f2e7:
movss xmm1, dword ptr [_arcade197_state + 40]
.L1f2ef:
addss xmm1, dword ptr [.Larcade_constants197 + 1284]
.L1f2f7:
movss dword ptr [_arcade197_state + 40], xmm1
.L1f2ff:
ucomiss xmm1, dword ptr [.Larcade_constants197 + 1292]
.L1f306:
jb .L1f929
.L1f30c:
addss xmm1, dword ptr [.Larcade_constants197 + 1296]
.L1f314:
movss dword ptr [_arcade197_state + 40], xmm1
.L1f31c:
mov esi, dword ptr [_arcade197_state + 1260]
.L1f322:
movzx edx, word ptr [_arcade197_state + 1252]
.L1f329:
imul ecx, edx, 0x642d
.L1f32f:
shr ecx, 0x10
.L1f332:
mov eax, edx
.L1f334:
sub eax, ecx
.L1f336:
movzx eax, ax
.L1f339:
shr eax, 1
.L1f33b:
add eax, ecx
.L1f33d:
shr eax, 4
.L1f340:
lea ecx, [eax + eax*2]
.L1f343:
shl ecx, 3
.L1f346:
mov edi, eax
.L1f348:
sub edi, ecx
.L1f34a:
add edi, edx
.L1f34c:
movzx edi, di
.L1f34f:
xor edx, edx
.L1f351:
cmp esi, 3
.L1f354:
sete dl
.L1f357:
xor ecx, ecx
.L1f359:
cmp esi, 2
.L1f35c:
sete cl
.L1f35f:
sub edx, ecx
.L1f361:
mov dword ptr [esp + 0x60], edi
.L1f365:
add edx, edi
.L1f367:
xor ecx, ecx
.L1f369:
cmp esi, 1
.L1f36c:
sete cl
.L1f36f:
sbb ecx, 0
.L1f372:
add ecx, eax
.L1f374:
lea edi, [ecx + ecx*2]
.L1f377:
shl edi, 3
.L1f37a:
sub edi, ecx
.L1f37c:
add edi, edx
.L1f37e:
cmp ecx, 0x11
.L1f381:
mov ebx, 0xffffffff
.L1f386:
cmovge edi, ebx
.L1f389:
test ecx, ecx
.L1f38b:
cmovs edi, ebx
.L1f38e:
cmp edx, 0x17
.L1f391:
cmovae edi, ebx
.L1f394:
test edi, edi
.L1f396:
js .L1f3a7
.L1f398:
cmp byte ptr [edi + _arcade197_state + 76], 0
.L1f39f:
je .L1f3a7
.L1f3a1:
mov dword ptr [_arcade197_state + 1256], esi
.L1f3a7:
mov esi, dword ptr [_arcade197_state + 1256]
.L1f3ad:
xor ecx, ecx
.L1f3af:
cmp esi, 1
.L1f3b2:
sete cl
.L1f3b5:
add ecx, eax
.L1f3b7:
cmp esi, 1
.L1f3ba:
sbb ecx, 0
.L1f3bd:
xor edx, edx
.L1f3bf:
cmp esi, 3
.L1f3c2:
sete dl
.L1f3c5:
add edx, dword ptr [esp + 0x60]
.L1f3c9:
xor eax, eax
.L1f3cb:
cmp esi, 2
.L1f3ce:
sete al
.L1f3d1:
sub edx, eax
.L1f3d3:
lea eax, [ecx + ecx*2]
.L1f3d6:
shl eax, 3
.L1f3d9:
sub eax, ecx
.L1f3db:
add eax, edx
.L1f3dd:
cmp ecx, 0x11
.L1f3e0:
mov esi, 0xffffffff
.L1f3e5:
cmovge eax, esi
.L1f3e8:
test ecx, ecx
.L1f3ea:
cmovs eax, esi
.L1f3ed:
cmp edx, 0x17
.L1f3f0:
cmovae eax, esi
.L1f3f3:
test eax, eax
.L1f3f5:
js .L1f455
.L1f3f7:
cmp byte ptr [eax + _arcade197_state + 76], 0
.L1f3fe:
je .L1f455
.L1f400:
mov word ptr [_arcade197_state + 1252], ax
.L1f406:
movzx ecx, byte ptr [eax + _arcade197_state + 76]
.L1f40d:
mov edx, ecx
.L1f40f:
dec dl
.L1f411:
cmp dl, 1
.L1f414:
ja .L1f455
.L1f416:
cmp cl, 2
.L1f419:
jne .L1f42b
.L1f41b:
addss xmm0, dword ptr [.Larcade_constants197 + 1300]
.L1f423:
movss dword ptr [_arcade197_state + 1320], xmm0
.L1f42b:
mov byte ptr [eax + _arcade197_state + 76], 3
.L1f432:
add dword ptr [_arcade197_state + 8], 0xa
.L1f439:
dec dword ptr [_arcade197_state + 1312]
.L1f43f:
jne .L1f455
.L1f441:
mov dword ptr [_arcade197_state + 20], 1
.L1f44b:
mov dword ptr [_arcade197_state + 24], 1
.L1f455:
mov dword ptr [esp + 0x60], 0
.L1f45d:
mov dword ptr [esp + 0xc0], 4
.L1f468:
mov dword ptr [esp + 0xa0], 0x7fffffff
.L1f473:
xor ebx, ebx
.L1f475:
mov eax, dword ptr [esp + 0x60]
.L1f479:
movzx ecx, word ptr [eax + eax + _arcade197_state + 1286]
.L1f481:
imul eax, ecx, 0x642d
.L1f487:
shr eax, 0x10
.L1f48a:
mov edx, ecx
.L1f48c:
sub edx, eax
.L1f48e:
movzx esi, dx
.L1f491:
shr esi, 1
.L1f493:
add esi, eax
.L1f495:
shr esi, 4
.L1f498:
lea edx, [esi + esi*2]
.L1f49b:
shl edx, 3
.L1f49e:
mov eax, esi
.L1f4a0:
sub eax, edx
.L1f4a2:
add eax, ecx
.L1f4a4:
xor edx, edx
.L1f4a6:
mov edi, ebx
.L1f4a8:
cmp ebx, 3
.L1f4ab:
sete dl
.L1f4ae:
xor ecx, ecx
.L1f4b0:
cmp ebx, 2
.L1f4b3:
sete cl
.L1f4b6:
sub edx, ecx
.L1f4b8:
movzx eax, ax
.L1f4bb:
add edx, eax
.L1f4bd:
xor eax, eax
.L1f4bf:
cmp ebx, 1
.L1f4c2:
sete al
.L1f4c5:
sbb eax, 0
.L1f4c8:
add eax, esi
.L1f4ca:
lea ecx, [eax + eax*2]
.L1f4cd:
shl ecx, 3
.L1f4d0:
sub ecx, eax
.L1f4d2:
add ecx, edx
.L1f4d4:
cmp eax, 0x11
.L1f4d7:
mov esi, 0xffffffff
.L1f4dc:
cmovge ecx, esi
.L1f4df:
test eax, eax
.L1f4e1:
cmovs ecx, esi
.L1f4e4:
cmp edx, 0x17
.L1f4e7:
cmovae ecx, esi
.L1f4ea:
test ecx, ecx
.L1f4ec:
js .L1f5ca
.L1f4f2:
cmp byte ptr [ecx + _arcade197_state + 76], 0
.L1f4f9:
je .L1f5ca
.L1f4ff:
movzx eax, word ptr [_arcade197_state + 1252]
.L1f506:
imul edx, eax, 0x642d
.L1f50c:
shr edx, 0x10
.L1f50f:
mov esi, eax
.L1f511:
sub esi, edx
.L1f513:
movzx edi, si
.L1f516:
shr edi, 1
.L1f518:
add edi, edx
.L1f51a:
shr edi, 4
.L1f51d:
lea edx, [edi + edi*2]
.L1f520:
shl edx, 3
.L1f523:
sub edi, edx
.L1f525:
add edi, eax
.L1f527:
mov eax, ecx
.L1f529:
mov edx, 0xb21642c9
.L1f52e:
mul edx
.L1f530:
mov esi, edx
.L1f532:
shr esi, 4
.L1f535:
lea eax, [esi + esi*2]
.L1f538:
shl eax, 3
.L1f53b:
mov edx, esi
.L1f53d:
sub edx, eax
.L1f53f:
add edx, ecx
.L1f541:
movzx eax, di
.L1f544:
sub edx, eax
.L1f546:
mov dword ptr [esp], edx
.L1f549:
call .L132bc0
.L1f54e:
mov edi, eax
.L1f550:
movzx eax, word ptr [_arcade197_state + 1252]
.L1f557:
imul ecx, eax, 0x642d
.L1f55d:
shr ecx, 0x10
.L1f560:
sub eax, ecx
.L1f562:
movzx eax, ax
.L1f565:
shr eax, 1
.L1f567:
add eax, ecx
.L1f569:
shr eax, 4
.L1f56c:
sub esi, eax
.L1f56e:
mov dword ptr [esp], esi
.L1f571:
call .L132bc0
.L1f576:
add eax, edi
.L1f578:
movss xmm0, dword ptr [_arcade197_state + 1320]
.L1f580:
mov ecx, eax
.L1f582:
neg ecx
.L1f584:
ucomiss xmm0, dword ptr [_arcade197_state + 36]
.L1f58b:
cmovbe ecx, eax
.L1f58e:
mov eax, dword ptr [esp + 0x60]
.L1f592:
mov eax, dword ptr [eax*4 + _arcade197_state + 1296]
.L1f599:
mov edx, ebx
.L1f59b:
xor eax, ebx
.L1f59d:
cmp eax, 1
.L1f5a0:
lea eax, [ecx + 0x14]
.L1f5a3:
cmovne eax, ecx
.L1f5a6:
mov ecx, dword ptr [esp + 0xa0]
.L1f5ad:
cmp eax, ecx
.L1f5af:
cmovl ecx, eax
.L1f5b2:
mov dword ptr [esp + 0xa0], ecx
.L1f5b9:
mov eax, dword ptr [esp + 0xc0]
.L1f5c0:
cmovl eax, ebx
.L1f5c3:
mov dword ptr [esp + 0xc0], eax
.L1f5ca:
mov eax, ebx
.L1f5cc:
inc eax
.L1f5cd:
mov ebx, eax
.L1f5cf:
cmp eax, 4
.L1f5d2:
jne .L1f475
.L1f5d8:
cmp dword ptr [esp + 0xc0], 4
.L1f5e0:
jae .L1f66f
.L1f5e6:
mov edi, dword ptr [esp + 0x60]
.L1f5ea:
movzx ecx, word ptr [edi + edi + _arcade197_state + 1286]
.L1f5f2:
imul edx, ecx, 0x642d
.L1f5f8:
shr edx, 0x10
.L1f5fb:
mov eax, ecx
.L1f5fd:
sub eax, edx
.L1f5ff:
movzx eax, ax
.L1f602:
shr eax, 1
.L1f604:
add eax, edx
.L1f606:
shr eax, 4
.L1f609:
lea esi, [eax + eax*2]
.L1f60c:
shl esi, 3
.L1f60f:
mov edx, eax
.L1f611:
sub edx, esi
.L1f613:
add edx, ecx
.L1f615:
xor ecx, ecx
.L1f617:
mov esi, dword ptr [esp + 0xc0]
.L1f61e:
cmp esi, 3
.L1f621:
sete cl
.L1f624:
xor ebx, ebx
.L1f626:
cmp esi, 2
.L1f629:
sete bl
.L1f62c:
sub ecx, ebx
.L1f62e:
movzx edx, dx
.L1f631:
add ecx, edx
.L1f633:
xor edx, edx
.L1f635:
cmp esi, 1
.L1f638:
sete dl
.L1f63b:
sbb edx, 0
.L1f63e:
add edx, eax
.L1f640:
lea eax, [edx + edx*2]
.L1f643:
shl eax, 3
.L1f646:
sub eax, edx
.L1f648:
add eax, ecx
.L1f64a:
cmp edx, 0x11
.L1f64d:
mov ebx, 0xffff
.L1f652:
cmovge eax, ebx
.L1f655:
test edx, edx
.L1f657:
cmovs eax, ebx
.L1f65a:
cmp ecx, 0x17
.L1f65d:
cmovae eax, ebx
.L1f660:
mov word ptr [edi + edi + _arcade197_state + 1286], ax
.L1f668:
mov dword ptr [edi*4 + _arcade197_state + 1296], esi
.L1f66f:
mov ecx, dword ptr [esp + 0x60]
.L1f673:
inc ecx
.L1f674:
mov eax, ecx
.L1f676:
mov dword ptr [esp + 0x60], ecx
.L1f67a:
cmp ecx, 4
.L1f67d:
jne .L1f45d
.L1f683:
movzx ecx, word ptr [_arcade197_state + 1252]
.L1f68a:
mov eax, dword ptr [_arcade197_state + 8]
.L1f68f:
movss xmm1, dword ptr [_arcade197_state + 1320]
.L1f697:
movss xmm0, dword ptr [_arcade197_state + 36]
.L1f69f:
cmp word ptr [_arcade197_state + 1286], cx
.L1f6a6:
jne .L1f88b
.L1f6ac:
ucomiss xmm1, xmm0
.L1f6af:
jbe .L1f8fe
.L1f6b5:
add eax, 0x64
.L1f6b8:
mov dword ptr [_arcade197_state + 8], eax
.L1f6bd:
mov word ptr [_arcade197_state + 1286], 0x50
.L1f6c6:
cmp word ptr [_arcade197_state + 1288], cx
.L1f6cd:
je .L1f899
.L1f6d3:
jmp .L1f8aa
.L1f6d8:
dec dword ptr [_arcade197_state + 12]
.L1f6de:
jne .L1f6eb
.L1f6e0:
mov eax, offset _arcade197_state + 20
.L1f6e5:
mov dword ptr [eax], 1
.L1f6eb:
movaps xmm0, xmmword ptr [.Larcade_constants197 + 1440]
.L1f6f2:
movlps qword ptr [_arcade197_state + 52], xmm0
.L1f6f9:
xor eax, eax
.L1f6fb:
xorps xmm0, xmm0
.L1f6fe:
ucomiss xmm0, dword ptr [_arcade197_state + 60]
.L1f705:
seta al
.L1f708:
movss xmm0, dword ptr [eax*4 + .Larcade_constants197 + 1456]
.L1f711:
movss dword ptr [_arcade197_state + 60], xmm0
.L1f719:
mov dword ptr [_arcade197_state + 64], 0x3e6b851f
.L1f723:
jmp .L1f929
.L1f728:
inc eax
.L1f729:
mov word ptr [_arcade197_state + 1250], ax
.L1f72f:
inc dword ptr [_arcade197_state + 8]
.L1f735:
movzx eax, ax
.L1f738:
lea eax, [eax + eax - 2]
.L1f73c:
mov dword ptr [esp + 8], eax
.L1f740:
mov dword ptr [esp + 4], offset _arcade197_state + 468
.L1f748:
mov dword ptr [esp], offset _arcade197_state + 470
.L1f74f:
call .L1373d0
.L1f754:
mov word ptr [_arcade197_state + 468], si
.L1f75b:
movzx ecx, word ptr [_arcade197_state + 1250]
.L1f762:
cmp ecx, 0x187
.L1f768:
je .L1f872
.L1f76e:
mov edi, 0x187
.L1f773:
sub edi, ecx
.L1f775:
imul eax, dword ptr [_arcade197_state + 4], 0x19660d
.L1f77f:
add eax, 0x3c6ef35f
.L1f784:
mov dword ptr [_arcade197_state + 4], eax
.L1f789:
xor esi, esi
.L1f78b:
xor edx, edx
.L1f78d:
div edi
.L1f78f:
test cx, cx
.L1f792:
mov eax, 0
.L1f797:
je .L1f7ae
.L1f799:
xor eax, eax
.L1f79b:
movzx edi, word ptr [eax + eax + _arcade197_state + 468]
.L1f7a3:
cmp esi, edi
.L1f7a5:
je .L1f7ae
.L1f7a7:
inc eax
.L1f7a8:
cmp ecx, eax
.L1f7aa:
jne .L1f79b
.L1f7ac:
jmp .L1f7b2
.L1f7ae:
cmp eax, ecx
.L1f7b0:
jne .L1f7bb
.L1f7b2:
sub edx, 1
.L1f7b5:
jb .L1f8d4
.L1f7bb:
inc esi
.L1f7bc:
cmp esi, 0x187
.L1f7c2:
jne .L1f78f
.L1f7c4:
jmp .L1f929
.L1f7c9:
movss dword ptr [_arcade197_state + 52], xmm0
.L1f7d1:
jmp .L1f929
.L1f7d6:
ucomiss xmm0, dword ptr [.Larcade_constants197 + 1216]
.L1f7dd:
jb .L1f857
.L1f7df:
movss xmm1, dword ptr [.Larcade_constants197 + 1172]
.L1f7e7:
ucomiss xmm1, xmm0
.L1f7ea:
jbe .L1f857
.L1f7ec:
movss xmm1, dword ptr [_arcade197_state + 52]
.L1f7f4:
mulss xmm1, dword ptr [.Larcade_constants197 + 1348]
.L1f7fc:
cvttss2si eax, xmm1
.L1f800:
addss xmm0, dword ptr [.Larcade_constants197 + 1352]
.L1f808:
mulss xmm0, dword ptr [.Larcade_constants197 + 1356]
.L1f810:
cmp eax, 9
.L1f813:
ja .L1f857
.L1f815:
cvttss2si ecx, xmm0
.L1f819:
test ecx, ecx
.L1f81b:
js .L1f857
.L1f81d:
cmp ecx, 5
.L1f820:
jg .L1f857
.L1f822:
add ecx, ecx
.L1f824:
lea ecx, [ecx + ecx*4]
.L1f827:
cmp byte ptr [eax + ecx + _arcade197_state + 76], 0
.L1f82f:
je .L1f857
.L1f831:
mov byte ptr [ecx + eax + _arcade197_state + 76], 0
.L1f839:
movss xmm0, dword ptr [_arcade197_state + 64]
.L1f841:
xorps xmm0, xmmword ptr [.Larcade_constants197 + 64]
.L1f848:
movss dword ptr [_arcade197_state + 64], xmm0
.L1f850:
add dword ptr [_arcade197_state + 8], 5
.L1f857:
xor eax, eax
.L1f859:
mov ecx, 0xffffffc4
.L1f85e:
movzx edx, byte ptr [ecx + _arcade197_state + 136]
.L1f865:
add eax, edx
.L1f867:
inc ecx
.L1f868:
jne .L1f85e
.L1f86a:
test eax, eax
.L1f86c:
jne .L1f929
.L1f872:
mov dword ptr [_arcade197_state + 20], 1
.L1f87c:
mov dword ptr [_arcade197_state + 24], 1
.L1f886:
jmp .L1f929
.L1f88b:
cmp word ptr [_arcade197_state + 1288], cx
.L1f892:
jne .L1f8aa
.L1f894:
ucomiss xmm1, xmm0
.L1f897:
jbe .L1f8fe
.L1f899:
add eax, 0x64
.L1f89c:
mov dword ptr [_arcade197_state + 8], eax
.L1f8a1:
mov word ptr [_arcade197_state + 1288], 0x50
.L1f8aa:
cmp word ptr [_arcade197_state + 1290], cx
.L1f8b1:
jne .L1f8dd
.L1f8b3:
ucomiss xmm1, xmm0
.L1f8b6:
jbe .L1f8fe
.L1f8b8:
add eax, 0x64
.L1f8bb:
mov dword ptr [_arcade197_state + 8], eax
.L1f8c0:
mov word ptr [_arcade197_state + 1290], 0x50
.L1f8c9:
cmp word ptr [_arcade197_state + 1292], cx
.L1f8d0:
je .L1f8eb
.L1f8d2:
jmp .L1f929
.L1f8d4:
mov word ptr [_arcade197_state + 1252], si
.L1f8db:
jmp .L1f929
.L1f8dd:
cmp word ptr [_arcade197_state + 1292], cx
.L1f8e4:
jne .L1f929
.L1f8e6:
ucomiss xmm1, xmm0
.L1f8e9:
jbe .L1f8fe
.L1f8eb:
add eax, 0x64
.L1f8ee:
mov dword ptr [_arcade197_state + 8], eax
.L1f8f3:
mov word ptr [_arcade197_state + 1292], 0x50
.L1f8fc:
jmp .L1f929
.L1f8fe:
dec dword ptr [_arcade197_state + 12]
.L1f904:
jne .L1f910
.L1f906:
mov dword ptr [_arcade197_state + 20], 1
.L1f910:
mov word ptr [_arcade197_state + 1252], 0x136
.L1f919:
addss xmm0, dword ptr [.Larcade_constants197 + 1304]
.L1f921:
movss dword ptr [_arcade197_state + 1320], xmm0
.L1f929:
mov eax, dword ptr [esp + 0x90]
.L1f930:
inc eax
.L1f931:
mov dword ptr [esp + 0x90], eax
.L1f938:
cmp eax, 3
.L1f93b:
jne .L1e540
jmp .Larcade_tick_done
.Lcc5a0:
push ebp
.Lcc5a1:
push ebx
.Lcc5a2:
push edi
.Lcc5a3:
push esi
.Lcc5a4:
sub esp, 0x24
.Lcc5a7:
mov edi, edx
.Lcc5a9:
mov esi, ecx
.Lcc5ab:
push 0x70c
.Lcc5b0:
push 0
.Lcc5b2:
.byte 0x68
.long _arcade197_state
.Lcc5b7:
call .L137420
.Lcc5bc:
add esp, 0xc
.Lcc5bf:
xor eax, eax
.Lcc5c1:
cmp esi, 6
.Lcc5c4:
cmovb eax, esi
.Lcc5c7:
mov dword ptr [_arcade197_state], eax
.Lcc5cc:
cmp edi, 1
.Lcc5cf:
adc edi, 0
.Lcc5d2:
mov dword ptr [_arcade197_state + 4], edi
.Lcc5d8:
mov dword ptr [_arcade197_state + 12], 3
.Lcc5e2:
mov dword ptr [_arcade197_state + 16], 1
.Lcc5ec:
movaps xmm0, xmmword ptr [.Larcade_constants197 + 4272]
.Lcc5f3:
movups xmmword ptr [_arcade197_state + 52], xmm0
.Lcc5fa:
movaps xmm0, xmmword ptr [.Larcade_constants197 + 1440]
.Lcc601:
movlps qword ptr [_arcade197_state + 68], xmm0
.Lcc608:
mov dword ptr [_arcade197_state + 1260], 3
.Lcc612:
mov dword ptr [_arcade197_state + 1256], 3
.Lcc61c:
lea eax, [esi - 1]
.Lcc61f:
cmp eax, 4
.Lcc622:
ja .Lccb39
.Lcc628:
jmp dword ptr [eax*4 + .Ltable1c1e98]
.Lcc62f:
mov dword ptr [_arcade197_state + 76], 0x1010101
.Lcc639:
mov dword ptr [_arcade197_state + 80], 0x1010101
.Lcc643:
mov dword ptr [_arcade197_state + 84], 0x1010101
.Lcc64d:
mov dword ptr [_arcade197_state + 88], 0x1010101
.Lcc657:
mov dword ptr [_arcade197_state + 92], 0x1010101
.Lcc661:
mov dword ptr [_arcade197_state + 96], 0x1010101
.Lcc66b:
mov dword ptr [_arcade197_state + 100], 0x1010101
.Lcc675:
mov dword ptr [_arcade197_state + 104], 0x1010101
.Lcc67f:
mov dword ptr [_arcade197_state + 108], 0x1010101
.Lcc689:
jmp .Lccb39
.Lcc68e:
mov word ptr [_arcade197_state + 1250], 3
.Lcc697:
mov dword ptr [_arcade197_state + 468], 0xc200c3
.Lcc6a1:
mov word ptr [_arcade197_state + 472], 0xc1
.Lcc6aa:
imul ecx, edi, 0x19660d
.Lcc6b0:
add ecx, 0x3c6ef35f
.Lcc6b6:
mov dword ptr [_arcade197_state + 4], ecx
.Lcc6bc:
mov eax, ecx
.Lcc6be:
shr eax, 2
.Lcc6c1:
mov edx, 0x151d07eb
.Lcc6c6:
mul edx
.Lcc6c8:
shr edx, 3
.Lcc6cb:
imul eax, edx, 0x184
.Lcc6d1:
sub ecx, eax
.Lcc6d3:
mov eax, 0xffffff3f
.Lcc6d8:
jmp .Lcc6e8
.Lcc6e0:
inc eax
.Lcc6e1:
cmp eax, 0xc6
.Lcc6e6:
je .Lcc6fd
.Lcc6e8:
cmp eax, 3
.Lcc6eb:
jb .Lcc6e0
.Lcc6ed:
sub ecx, 1
.Lcc6f0:
jae .Lcc6e0
.Lcc6f2:
add eax, 0xc1
.Lcc6f7:
mov word ptr [_arcade197_state + 1252], ax
.Lcc6fd:
cmp esi, 5
.Lcc700:
je .Lcc9e4
.Lcc706:
cmp esi, 4
.Lcc709:
je .Lcc74b
.Lcc70b:
cmp esi, 3
.Lcc70e:
jne .Lccb39
.Lcc714:
mov eax, 0xffffffc4
.Lcc719:
nop dword ptr [eax]
.Lcc720:
mov byte ptr [eax + _arcade197_state + 136], 1
.Lcc727:
inc eax
.Lcc728:
jne .Lcc720
.Lcc72a:
movaps xmm0, xmmword ptr [.Larcade_constants197 + 4288]
.Lcc731:
movups xmmword ptr [_arcade197_state + 52], xmm0
.Lcc738:
mov dword ptr [_arcade197_state + 1316], 0
.Lcc742:
cmp esi, 4
.Lcc745:
jne .Lcc9db
.Lcc74b:
mov dword ptr [esp], esi
.Lcc74e:
mov dword ptr [_arcade197_state + 1268], 0x4030201
.Lcc758:
mov dword ptr [_arcade197_state + 1272], 0x8070605
.Lcc762:
mov dword ptr [_arcade197_state + 1276], 0xc0b0a09
.Lcc76c:
mov word ptr [_arcade197_state + 1280], 0xe0d
.Lcc775:
mov byte ptr [_arcade197_state + 1282], 0xf
.Lcc77c:
mov byte ptr [_arcade197_state + 1285], 0xf
.Lcc783:
mov ebp, 0xff
.Lcc788:
xor esi, esi
.Lcc78a:
jmp .Lcc7a1
.Lcc790:
inc esi
.Lcc791:
cmp esi, 0xb4
.Lcc797:
mov ebp, dword ptr [esp + 8]
.Lcc79b:
je .Lcc8a3
.Lcc7a1:
mov dword ptr [esp + 0xc], esi
.Lcc7a5:
movzx eax, byte ptr [_arcade197_state + 1285]
.Lcc7ac:
mov ecx, eax
.Lcc7ae:
and ecx, 3
.Lcc7b1:
mov dword ptr [esp + 4], ecx
.Lcc7b5:
mov dword ptr [esp + 8], eax
.Lcc7b9:
shr eax, 2
.Lcc7bc:
mov dword ptr [esp + 0x10], eax
.Lcc7c0:
xor ebx, ebx
.Lcc7c2:
xor esi, esi
.Lcc7c4:
jmp .Lcc7d6
.Lcc7d0:
inc ebx
.Lcc7d1:
cmp ebx, 0x10
.Lcc7d4:
je .Lcc810
.Lcc7d6:
cmp ebp, ebx
.Lcc7d8:
je .Lcc7d0
.Lcc7da:
mov eax, ebx
.Lcc7dc:
and eax, 3
.Lcc7df:
sub eax, dword ptr [esp + 4]
.Lcc7e3:
push eax
.Lcc7e4:
call .L132bc0
.Lcc7e9:
add esp, 4
.Lcc7ec:
mov edi, eax
.Lcc7ee:
mov eax, ebx
.Lcc7f0:
shr eax, 2
.Lcc7f3:
sub eax, dword ptr [esp + 0x10]
.Lcc7f7:
push eax
.Lcc7f8:
call .L132bc0
.Lcc7fd:
add esp, 4
.Lcc800:
add eax, edi
.Lcc802:
cmp eax, 1
.Lcc805:
jne .Lcc7d0
.Lcc807:
mov dword ptr [esp + esi*4 + 0x14], ebx
.Lcc80b:
inc esi
.Lcc80c:
jmp .Lcc7d0
.Lcc810:
imul eax, dword ptr [_arcade197_state + 4], 0x19660d
.Lcc81a:
add eax, 0x3c6ef35f
.Lcc81f:
mov dword ptr [_arcade197_state + 4], eax
.Lcc824:
shr eax, 0x10
.Lcc827:
xor edx, edx
.Lcc829:
div esi
.Lcc82b:
mov ebx, dword ptr [esp + edx*4 + 0x14]
.Lcc82f:
cmp ebx, 0xf
.Lcc832:
mov esi, dword ptr [esp + 0xc]
.Lcc836:
ja .Lcc790
.Lcc83c:
mov eax, ebx
.Lcc83e:
and eax, 3
.Lcc841:
movzx ecx, byte ptr [_arcade197_state + 1285]
.Lcc848:
and ecx, 3
.Lcc84b:
sub eax, ecx
.Lcc84d:
push eax
.Lcc84e:
call .L132bc0
.Lcc853:
add esp, 4
.Lcc856:
mov edi, eax
.Lcc858:
mov eax, ebx
.Lcc85a:
shr eax, 2
.Lcc85d:
movzx ecx, byte ptr [_arcade197_state + 1285]
.Lcc864:
shr ecx, 2
.Lcc867:
sub eax, ecx
.Lcc869:
push eax
.Lcc86a:
call .L132bc0
.Lcc86f:
add esp, 4
.Lcc872:
add eax, edi
.Lcc874:
cmp eax, 1
.Lcc877:
jne .Lcc790
.Lcc87d:
movzx eax, byte ptr [ebx + _arcade197_state + 1268]
.Lcc884:
movzx ecx, byte ptr [_arcade197_state + 1285]
.Lcc88b:
mov byte ptr [ecx + _arcade197_state + 1268], al
.Lcc891:
mov byte ptr [ebx + _arcade197_state + 1268], 0
.Lcc898:
mov byte ptr [_arcade197_state + 1285], bl
.Lcc89e:
jmp .Lcc790
.Lcc8a3:
cmp byte ptr [_arcade197_state + 1281], 0xe
.Lcc8aa:
setne al
.Lcc8ad:
shl al, 2
.Lcc8b0:
cmp byte ptr [_arcade197_state + 1282], 0xf
.Lcc8b7:
setne cl
.Lcc8ba:
shl cl, 3
.Lcc8bd:
or cl, al
.Lcc8bf:
cmp byte ptr [_arcade197_state + 1279], 0xc
.Lcc8c6:
setne dl
.Lcc8c9:
cmp byte ptr [_arcade197_state + 1280], 0xd
.Lcc8d0:
setne al
.Lcc8d3:
add al, al
.Lcc8d5:
or al, dl
.Lcc8d7:
or al, cl
.Lcc8d9:
cmp byte ptr [_arcade197_state + 1277], 0xa
.Lcc8e0:
setne cl
.Lcc8e3:
shl cl, 2
.Lcc8e6:
cmp byte ptr [_arcade197_state + 1278], 0xb
.Lcc8ed:
setne dl
.Lcc8f0:
shl dl, 3
.Lcc8f3:
or dl, cl
.Lcc8f5:
cmp byte ptr [_arcade197_state + 1275], 8
.Lcc8fc:
setne cl
.Lcc8ff:
cmp byte ptr [_arcade197_state + 1276], 9
.Lcc906:
setne ah
.Lcc909:
add ah, ah
.Lcc90b:
or ah, cl
.Lcc90d:
or ah, dl
.Lcc90f:
or ah, al
.Lcc911:
movzx eax, byte ptr [_arcade197_state + 1285]
.Lcc918:
jne .Lccb41
.Lcc91e:
movzx edx, byte ptr [_arcade197_state + 1273]
.Lcc925:
movzx ecx, byte ptr [_arcade197_state + 1274]
.Lcc92c:
shl ecx, 8
.Lcc92f:
or ecx, edx
.Lcc931:
shl ecx, 0x10
.Lcc934:
movzx edx, byte ptr [_arcade197_state + 1271]
.Lcc93b:
movzx esi, byte ptr [_arcade197_state + 1272]
.Lcc942:
shl esi, 8
.Lcc945:
or esi, edx
.Lcc947:
movzx edx, si
.Lcc94a:
or edx, ecx
.Lcc94c:
cmp edx, 0x7060504
.Lcc952:
jne .Lccb41
.Lcc958:
cmp byte ptr [_arcade197_state + 1270], 3
.Lcc95f:
mov esi, dword ptr [esp]
.Lcc962:
jne .Lcc9d6
.Lcc964:
cmp byte ptr [_arcade197_state + 1269], 2
.Lcc96b:
jne .Lcc9d6
.Lcc96d:
cmp byte ptr [_arcade197_state + 1268], 1
.Lcc974:
jne .Lcc9d6
.Lcc976:
movzx eax, al
.Lcc979:
and eax, 3
.Lcc97c:
mov ecx, 2
.Lcc981:
sub ecx, eax
.Lcc983:
push ecx
.Lcc984:
call .L132bc0
.Lcc989:
add esp, 4
.Lcc98c:
mov edi, eax
.Lcc98e:
movzx eax, byte ptr [_arcade197_state + 1285]
.Lcc995:
shr eax, 2
.Lcc998:
mov ecx, 3
.Lcc99d:
sub ecx, eax
.Lcc99f:
push ecx
.Lcc9a0:
call .L132bc0
.Lcc9a5:
add esp, 4
.Lcc9a8:
add eax, edi
.Lcc9aa:
cmp eax, 1
.Lcc9ad:
movzx eax, byte ptr [_arcade197_state + 1285]
.Lcc9b4:
jne .Lcc9d6
.Lcc9b6:
movzx eax, al
.Lcc9b9:
movzx ecx, byte ptr [_arcade197_state + 1282]
.Lcc9c0:
mov byte ptr [eax + _arcade197_state + 1268], cl
.Lcc9c6:
mov byte ptr [_arcade197_state + 1282], 0
.Lcc9cd:
mov byte ptr [_arcade197_state + 1285], 0xe
.Lcc9d4:
mov al, 0xe
.Lcc9d6:
mov byte ptr [_arcade197_state + 1284], al
.Lcc9db:
cmp esi, 5
.Lcc9de:
jne .Lccb39
.Lcc9e4:
mov dword ptr [_arcade197_state + 1312], 0
.Lcc9ee:
xor eax, eax
.Lcc9f0:
mov ebp, offset _arcade197_state + 77
.Lcc9f5:
jmp .Lcca0d
.Lcca00:
inc eax
.Lcca01:
add ebp, 0x17
.Lcca04:
cmp eax, 0x11
.Lcca07:
je .Lcca9d
.Lcca0d:
lea edx, [eax + eax*2]
.Lcca10:
shl edx, 3
.Lcca13:
sub edx, eax
.Lcca15:
mov byte ptr [edx + _arcade197_state + 76], 0
.Lcca1c:
mov edx, 0xa
.Lcca21:
mov bl, 1
.Lcca23:
mov esi, 0xffffffea
.Lcca28:
mov ecx, eax
.Lcca2a:
and ecx, 2
.Lcca2d:
shr ecx, 1
.Lcca2f:
mov dword ptr [esp + 4], ecx
.Lcca33:
jmp .Lcca4b
.Lcca40:
mov byte ptr [ebp + esi + 0x16], 0
.Lcca45:
dec edx
.Lcca46:
inc bl
.Lcca48:
inc esi
.Lcca49:
je .Lcca00
.Lcca4b:
test eax, 0x7fffffef
.Lcca50:
je .Lcca40
.Lcca52:
cmp esi, -1
.Lcca55:
je .Lcca40
.Lcca57:
movzx edi, bl
.Lcca5a:
imul edi, edi, 0xcd
.Lcca60:
shr edi, 0xa
.Lcca63:
lea ecx, [edi + edi*4]
.Lcca66:
mov bh, bl
.Lcca68:
sub bh, cl
.Lcca6a:
cmp bh, 1
.Lcca6d:
ja .Lcca90
.Lcca6f:
cmp eax, 8
.Lcca72:
sete cl
.Lcca75:
test edx, edx
.Lcca77:
sete ch
.Lcca7a:
or ch, cl
.Lcca7c:
or ch, byte ptr [esp + 4]
.Lcca80:
mov byte ptr [ebp + esi + 0x16], ch
.Lcca84:
je .Lcca45
.Lcca86:
jmp .Lcca95
.Lcca90:
mov byte ptr [ebp + esi + 0x16], 1
.Lcca95:
inc dword ptr [_arcade197_state + 1312]
.Lcca9b:
jmp .Lcca45
.Lcca9d:
mov word ptr [_arcade197_state + 1252], 0x136
.Lccaa6:
mov byte ptr [_arcade197_state + 386], 3
.Lccaad:
mov dword ptr [_arcade197_state + 1286], 0x56004a
.Lccab7:
mov dword ptr [_arcade197_state + 1296], 0
.Lccac1:
mov dword ptr [_arcade197_state + 1300], 1
.Lccacb:
mov dword ptr [_arcade197_state + 1290], 0x10e0102
.Lccad5:
mov dword ptr [_arcade197_state + 1304], 2
.Lccadf:
mov dword ptr [_arcade197_state + 1308], 3
.Lccae9:
mov byte ptr [_arcade197_state + 100], 2
.Lccaf0:
mov byte ptr [_arcade197_state + 120], 2
.Lccaf7:
mov byte ptr [_arcade197_state + 422], 2
.Lccafe:
mov byte ptr [_arcade197_state + 442], 2
.Lccb05:
mov dword ptr [_arcade197_state + 1312], 0
.Lccb0f:
xor eax, eax
.Lccb11:
mov ecx, 0xfffffe79
.Lccb16:
jmp .Lccb23
.Lccb20:
inc ecx
.Lccb21:
je .Lccb39
.Lccb23:
movzx edx, byte ptr [ecx + _arcade197_state + 467]
.Lccb2a:
dec dl
.Lccb2c:
cmp dl, 1
.Lccb2f:
ja .Lccb20
.Lccb31:
inc eax
.Lccb32:
mov dword ptr [_arcade197_state + 1312], eax
.Lccb37:
jmp .Lccb20
.Lccb39:
add esp, 0x24
.Lccb3c:
pop esi
.Lccb3d:
pop edi
.Lccb3e:
pop ebx
.Lccb3f:
pop ebp
.Lccb40:
ret 
.Lccb41:
mov esi, dword ptr [esp]
.Lccb44:
jmp .Lcc9d6
.Lccc90:
cmp dword ptr [_arcade197_state + 1340], 0
.Lccc97:
je .Lccdd7
.Lccc9d:
cmp dword ptr [_arcade197_state + 1360], 0
.Lccca4:
je .Lccde3
.Lcccaa:
cmp dword ptr [_arcade197_state + 1380], 0
.Lcccb1:
je .Lccdf2
.Lcccb7:
cmp dword ptr [_arcade197_state + 1400], 0
.Lcccbe:
je .Lcce01
.Lcccc4:
cmp dword ptr [_arcade197_state + 1420], 0
.Lccccb:
je .Lcce10
.Lcccd1:
cmp dword ptr [_arcade197_state + 1440], 0
.Lcccd8:
je .Lcce1f
.Lcccde:
cmp dword ptr [_arcade197_state + 1460], 0
.Lccce5:
je .Lcce2e
.Lccceb:
cmp dword ptr [_arcade197_state + 1480], 0
.Lcccf2:
je .Lcce3d
.Lcccf8:
cmp dword ptr [_arcade197_state + 1500], 0
.Lcccff:
je .Lcce4c
.Lccd05:
cmp dword ptr [_arcade197_state + 1520], 0
.Lccd0c:
je .Lcce5b
.Lccd12:
cmp dword ptr [_arcade197_state + 1540], 0
.Lccd19:
je .Lcce6a
.Lccd1f:
cmp dword ptr [_arcade197_state + 1560], 0
.Lccd26:
je .Lcce79
.Lccd2c:
cmp dword ptr [_arcade197_state + 1580], 0
.Lccd33:
je .Lcce88
.Lccd39:
cmp dword ptr [_arcade197_state + 1600], 0
.Lccd40:
je .Lcce94
.Lccd46:
cmp dword ptr [_arcade197_state + 1620], 0
.Lccd4d:
je .Lccea0
.Lccd53:
cmp dword ptr [_arcade197_state + 1640], 0
.Lccd5a:
je .Lcceac
.Lccd60:
cmp dword ptr [_arcade197_state + 1660], 0
.Lccd67:
je .Lcceb8
.Lccd6d:
cmp dword ptr [_arcade197_state + 1680], 0
.Lccd74:
je .Lccec4
.Lccd7a:
cmp dword ptr [_arcade197_state + 1700], 0
.Lccd81:
je .Lcced0
.Lccd87:
cmp dword ptr [_arcade197_state + 1720], 0
.Lccd8e:
je .Lccedc
.Lccd94:
cmp dword ptr [_arcade197_state + 1740], 0
.Lccd9b:
je .Lccee8
.Lccda1:
cmp dword ptr [_arcade197_state + 1760], 0
.Lccda8:
je .Lccef4
.Lccdae:
cmp dword ptr [_arcade197_state + 1780], 0
.Lccdb5:
je .Lccf00
.Lccdbb:
cmp dword ptr [_arcade197_state + 1800], 0
.Lccdc2:
jne .Lccf4b
.Lccdc8:
mov eax, offset _arcade197_state + 1800
.Lccdcd:
mov ecx, 0x17
.Lccdd2:
jmp .Lccf0a
.Lccdd7:
mov eax, offset _arcade197_state + 1340
.Lccddc:
xor ecx, ecx
.Lccdde:
jmp .Lccf0a
.Lccde3:
mov eax, offset _arcade197_state + 1360
.Lccde8:
mov ecx, 1
.Lccded:
jmp .Lccf0a
.Lccdf2:
mov eax, offset _arcade197_state + 1380
.Lccdf7:
mov ecx, 2
.Lccdfc:
jmp .Lccf0a
.Lcce01:
mov eax, offset _arcade197_state + 1400
.Lcce06:
mov ecx, 3
.Lcce0b:
jmp .Lccf0a
.Lcce10:
mov eax, offset _arcade197_state + 1420
.Lcce15:
mov ecx, 4
.Lcce1a:
jmp .Lccf0a
.Lcce1f:
mov eax, offset _arcade197_state + 1440
.Lcce24:
mov ecx, 5
.Lcce29:
jmp .Lccf0a
.Lcce2e:
mov eax, offset _arcade197_state + 1460
.Lcce33:
mov ecx, 6
.Lcce38:
jmp .Lccf0a
.Lcce3d:
mov eax, offset _arcade197_state + 1480
.Lcce42:
mov ecx, 7
.Lcce47:
jmp .Lccf0a
.Lcce4c:
mov eax, offset _arcade197_state + 1500
.Lcce51:
mov ecx, 8
.Lcce56:
jmp .Lccf0a
.Lcce5b:
mov eax, offset _arcade197_state + 1520
.Lcce60:
mov ecx, 9
.Lcce65:
jmp .Lccf0a
.Lcce6a:
mov eax, offset _arcade197_state + 1540
.Lcce6f:
mov ecx, 0xa
.Lcce74:
jmp .Lccf0a
.Lcce79:
mov eax, offset _arcade197_state + 1560
.Lcce7e:
mov ecx, 0xb
.Lcce83:
jmp .Lccf0a
.Lcce88:
mov eax, offset _arcade197_state + 1580
.Lcce8d:
mov ecx, 0xc
.Lcce92:
jmp .Lccf0a
.Lcce94:
mov eax, offset _arcade197_state + 1600
.Lcce99:
mov ecx, 0xd
.Lcce9e:
jmp .Lccf0a
.Lccea0:
mov eax, offset _arcade197_state + 1620
.Lccea5:
mov ecx, 0xe
.Lcceaa:
jmp .Lccf0a
.Lcceac:
mov eax, offset _arcade197_state + 1640
.Lcceb1:
mov ecx, 0xf
.Lcceb6:
jmp .Lccf0a
.Lcceb8:
mov eax, offset _arcade197_state + 1660
.Lccebd:
mov ecx, 0x10
.Lccec2:
jmp .Lccf0a
.Lccec4:
mov eax, offset _arcade197_state + 1680
.Lccec9:
mov ecx, 0x11
.Lccece:
jmp .Lccf0a
.Lcced0:
mov eax, offset _arcade197_state + 1700
.Lcced5:
mov ecx, 0x12
.Lcceda:
jmp .Lccf0a
.Lccedc:
mov eax, offset _arcade197_state + 1720
.Lccee1:
mov ecx, 0x13
.Lccee6:
jmp .Lccf0a
.Lccee8:
mov eax, offset _arcade197_state + 1740
.Lcceed:
mov ecx, 0x14
.Lccef2:
jmp .Lccf0a
.Lccef4:
mov eax, offset _arcade197_state + 1760
.Lccef9:
mov ecx, 0x15
.Lccefe:
jmp .Lccf0a
.Lccf00:
mov eax, offset _arcade197_state + 1780
.Lccf05:
mov ecx, 0x16
.Lccf0a:
movss xmm0, dword ptr [esp + 0xc]
.Lccf10:
movss xmm1, dword ptr [esp + 8]
.Lccf16:
movss xmm2, dword ptr [esp + 4]
.Lccf1c:
shl ecx, 2
.Lccf1f:
movss dword ptr [ecx + ecx*4 + _arcade197_state + 1324], xmm2
.Lccf28:
movss dword ptr [ecx + ecx*4 + _arcade197_state + 1328], xmm1
.Lccf31:
mov dword ptr [ecx + ecx*4 + _arcade197_state + 1332], 0
.Lccf3c:
movss dword ptr [ecx + ecx*4 + _arcade197_state + 1336], xmm0
.Lccf45:
mov dword ptr [eax], 1
.Lccf4b:
ret 
.L132bc0:
mov ecx, dword ptr [esp + 4]
.L132bc4:
mov eax, ecx
.L132bc6:
neg eax
.L132bc8:
cmovs eax, ecx
.L132bcb:
ret 
.L1369e0:
fld dword ptr [esp + 4]
.L1369e4:
fabs 
.L1369e6:
ret 
.L136bf0:
push esi
.L136bf1:
sub esp, 8
.L136bf4:
movss xmm0, dword ptr [esp + 0x10]
.L136bfa:
movss dword ptr [esp], xmm0
.L136bff:
call .L132b30
.L136c04:
movss xmm0, dword ptr [esp + 0x14]
.L136c0a:
cmp eax, 0x100
.L136c0f:
je .L136c76
.L136c11:
movss dword ptr [esp], xmm0
.L136c16:
call .L132b30
.L136c1b:
movss xmm0, dword ptr [esp + 0x10]
.L136c21:
cmp eax, 0x100
.L136c26:
je .L136c76
.L136c28:
movss dword ptr [esp], xmm0
.L136c2d:
call .L1466f0
.L136c32:
mov esi, eax
.L136c34:
movss xmm0, dword ptr [esp + 0x14]
.L136c3a:
movss dword ptr [esp], xmm0
.L136c3f:
call .L1466f0
.L136c44:
cmp esi, eax
.L136c46:
jne .L136c56
.L136c48:
movss xmm0, dword ptr [esp + 0x14]
.L136c4e:
maxss xmm0, dword ptr [esp + 0x10]
.L136c54:
jmp .L136c76
.L136c56:
movss xmm0, dword ptr [esp + 0x10]
.L136c5c:
movss dword ptr [esp], xmm0
.L136c61:
call .L1466f0
.L136c66:
test eax, eax
.L136c68:
movss xmm0, dword ptr [esp + 0x10]
.L136c6e:
je .L136c76
.L136c70:
movss xmm0, dword ptr [esp + 0x14]
.L136c76:
movss dword ptr [esp + 4], xmm0
.L136c7c:
fld dword ptr [esp + 4]
.L136c80:
add esp, 8
.L136c83:
pop esi
.L136c84:
ret 
.L136dc0:
push esi
.L136dc1:
sub esp, 8
.L136dc4:
movss xmm0, dword ptr [esp + 0x10]
.L136dca:
movss dword ptr [esp], xmm0
.L136dcf:
call .L132b30
.L136dd4:
movss xmm0, dword ptr [esp + 0x14]
.L136dda:
cmp eax, 0x100
.L136ddf:
je .L136e40
.L136de1:
movss dword ptr [esp], xmm0
.L136de6:
call .L132b30
.L136deb:
movss xmm0, dword ptr [esp + 0x10]
.L136df1:
cmp eax, 0x100
.L136df6:
je .L136e40
.L136df8:
movss dword ptr [esp], xmm0
.L136dfd:
call .L1466f0
.L136e02:
mov esi, eax
.L136e04:
movss xmm0, dword ptr [esp + 0x14]
.L136e0a:
movss dword ptr [esp], xmm0
.L136e0f:
call .L1466f0
.L136e14:
movss xmm0, dword ptr [esp + 0x10]
.L136e1a:
cmp esi, eax
.L136e1c:
jne .L136e26
.L136e1e:
minss xmm0, dword ptr [esp + 0x14]
.L136e24:
jmp .L136e40
.L136e26:
movss dword ptr [esp], xmm0
.L136e2b:
call .L1466f0
.L136e30:
test eax, eax
.L136e32:
movss xmm0, dword ptr [esp + 0x14]
.L136e38:
je .L136e40
.L136e3a:
movss xmm0, dword ptr [esp + 0x10]
.L136e40:
movss dword ptr [esp + 4], xmm0
.L136e46:
fld dword ptr [esp + 4]
.L136e4a:
add esp, 8
.L136e4d:
pop esi
.L136e4e:
ret 
.L1373d0:
push ebx
.L1373d1:
push esi
.L1373d2:
mov edx, dword ptr [esp + 0x14]
.L1373d6:
mov ecx, dword ptr [esp + 0x10]
.L1373da:
mov eax, dword ptr [esp + 0xc]
.L1373de:
cmp eax, ecx
.L1373e0:
jbe .L137400
.L1373e2:
test edx, edx
.L1373e4:
je .L13741c
.L1373e6:
mov esi, edx
.L1373e8:
nop dword ptr [eax + eax]
.L1373f0:
dec esi
.L1373f1:
movzx ebx, byte ptr [ecx + edx - 1]
.L1373f6:
mov byte ptr [eax + edx - 1], bl
.L1373fa:
mov edx, esi
.L1373fc:
jne .L1373f0
.L1373fe:
jmp .L13741c
.L137400:
test edx, edx
.L137402:
je .L13741c
.L137404:
xor esi, esi
.L137406:
nop word ptr cs:[eax + eax]
.L137410:
movzx ebx, byte ptr [ecx + esi]
.L137414:
mov byte ptr [eax + esi], bl
.L137417:
inc esi
.L137418:
cmp edx, esi
.L13741a:
jne .L137410
.L13741c:
pop esi
.L13741d:
pop ebx
.L13741e:
ret 
.L137420:
push esi
.L137421:
mov ecx, dword ptr [esp + 0x10]
.L137425:
mov eax, dword ptr [esp + 8]
.L137429:
test ecx, ecx
.L13742b:
je .L137446
.L13742d:
mov edx, dword ptr [esp + 0xc]
.L137431:
mov esi, eax
.L137433:
nop word ptr cs:[eax + eax]
.L13743d:
nop dword ptr [eax]
.L137440:
mov byte ptr [esi], dl
.L137442:
inc esi
.L137443:
dec ecx
.L137444:
jne .L137440
.L137446:
pop esi
.L137447:
ret 
.L1377c0:
fld dword ptr [esp + 4]
.L1377c4:
fsin 
.L1377c6:
ret 
.L132b30:
fld dword ptr [esp + 4]
.L132b34:
fxam 
.L132b36:
wait 
.L132b37:
fnstsw ax
.L132b39:
fstp st(0)
.L132b3b:
and eax, 0x4500
.L132b40:
ret 
.L1466f0:
fld dword ptr [esp + 4]
.L1466f4:
fxam 
.L1466f6:
wait 
.L1466f7:
fnstsw ax
.L1466f9:
fstp st(0)
.L1466fb:
and eax, 0x200
.L146700:
ret 
.p2align 4
.Larcade_constants197:
.byte 234,249,174,0,226,221,172,0,226,221,172,0,226,221,172,0
.byte 226,221,172,0,226,221,172,0,130,103,162,0,0,0,0,69
.byte 57,142,99,62,171,170,170,63,0,0,128,63,0,0,0,0
.byte 0,0,128,67,0,0,128,65,0,0,0,0,0,0,0,0
.byte 0,0,0,128,0,0,0,128,0,0,0,128,0,0,0,128
.byte 243,4,181,63,0,0,128,63,0,0,0,0,0,0,0,0
.byte 254,181,3,191,254,181,3,191,254,181,3,191,254,181,3,191
.byte 168,132,91,63,168,132,91,63,168,132,91,63,168,132,91,63
.byte 254,181,3,63,254,181,3,63,254,181,3,63,254,181,3,63
.byte 218,134,241,190,218,134,241,190,218,134,241,190,218,134,241,190
.byte 216,185,97,63,216,185,97,63,216,185,97,63,216,185,97,63
.byte 218,134,241,62,218,134,241,62,218,134,241,62,218,134,241,62
.byte 2,115,160,190,2,115,160,190,2,115,160,190,2,115,160,190
.byte 221,26,115,63,221,26,115,63,221,26,115,63,221,26,115,63
.byte 2,115,160,62,2,115,160,62,2,115,160,62,2,115,160,62
.byte 116,71,58,190,116,71,58,190,116,71,58,190,116,71,58,190
.byte 129,186,123,63,129,186,123,63,129,186,123,63,129,186,123,63
.byte 116,71,58,62,116,71,58,62,116,71,58,62,116,71,58,62
.byte 29,176,193,189,29,176,193,189,29,176,193,189,29,176,193,189
.byte 65,218,126,63,65,218,126,63,65,218,126,63,65,218,126,63
.byte 29,176,193,61,29,176,193,61,29,176,193,61,29,176,193,61
.byte 134,203,39,189,134,203,39,189,134,203,39,189,134,203,39,189
.byte 253,200,127,63,253,200,127,63,253,200,127,63,253,200,127,63
.byte 134,203,39,61,134,203,39,61,134,203,39,61,134,203,39,61
.byte 20,161,104,188,20,161,104,188,20,161,104,188,20,161,104,188
.byte 101,249,127,63,101,249,127,63,101,249,127,63,101,249,127,63
.byte 20,161,104,60,20,161,104,60,20,161,104,60,20,161,104,60
.byte 50,123,114,187,50,123,114,187,50,123,114,187,50,123,114,187
.byte 141,255,127,63,141,255,127,63,141,255,127,63,141,255,127,63
.byte 50,123,114,59,50,123,114,59,50,123,114,59,50,123,114,59
.byte 116,71,58,190,2,115,160,190,218,134,241,190,254,181,3,191
.byte 129,186,123,63,221,26,115,63,216,185,97,63,168,132,91,63
.byte 116,71,58,62,2,115,160,62,218,134,241,62,254,181,3,63
.byte 50,123,114,187,20,161,104,188,134,203,39,189,29,176,193,189
.byte 141,255,127,63,101,249,127,63,253,200,127,63,65,218,126,63
.byte 50,123,114,59,20,161,104,60,134,203,39,61,29,176,193,61
.byte 215,179,93,63,0,0,0,63,0,0,0,0,0,0,0,0
.byte 94,131,108,191,52,25,75,63,0,0,0,0,0,0,0,0
.byte 21,239,195,62,202,215,27,63,0,0,0,0,0,0,0,0
.byte 94,131,108,63,85,207,125,63,0,0,0,0,0,0,0,0
.byte 21,239,195,62,168,168,5,62,0,0,0,0,0,0,0,0
.byte 85,207,125,63,168,168,5,62,168,168,5,190,0,0,0,0
.byte 168,168,5,190,21,239,195,190,202,215,27,191,52,25,75,63
.byte 85,207,125,63,94,131,108,63,52,25,75,63,202,215,27,63
.byte 21,239,195,62,202,215,27,191,0,0,0,0,0,0,0,0
.byte 94,131,108,63,52,25,75,63,0,0,0,0,0,0,0,0
.byte 202,215,27,191,52,25,75,63,0,0,0,0,0,0,0,0
.byte 21,239,195,62,168,168,5,190,0,0,0,0,0,0,0,0
.byte 94,131,108,63,85,207,125,63,202,215,27,191,21,239,195,62
.byte 21,239,195,62,168,168,5,62,52,25,75,63,94,131,108,63
.byte 141,158,0,63,120,194,5,63,63,35,17,63,29,150,37,63
.byte 70,10,35,65,66,22,90,64,175,178,3,64,27,249,189,63
.byte 133,39,0,63,139,102,1,63,91,244,3,63,104,242,7,63
.byte 141,158,0,63,120,194,5,63,63,35,17,63,29,150,37,63
.byte 128,196,73,63,73,196,135,63,38,121,220,63,156,60,163,64
.byte 53,176,149,63,59,250,120,63,158,223,86,63,238,153,62,63
.byte 56,152,13,63,58,59,21,63,110,92,31,63,61,192,44,63
.byte 128,196,73,63,73,196,135,63,38,121,220,63,156,60,163,64
.byte 243,4,53,63,243,4,53,63,243,4,53,63,243,4,53,63
.byte 175,175,75,62,175,175,75,62,175,175,75,62,175,175,75,62
.byte 21,239,195,62,21,239,195,62,21,239,195,62,21,239,195,62
.byte 247,129,2,63,247,129,2,63,247,129,2,63,247,129,2,63
.byte 212,139,10,63,212,139,10,63,212,139,10,63,212,139,10,63
.byte 189,241,25,63,189,241,25,63,189,241,25,63,189,241,25,63
.byte 215,100,102,63,215,100,102,63,215,100,102,63,215,100,102,63
.byte 117,61,167,63,117,61,167,63,117,61,167,63,117,61,167,63
.byte 207,6,36,64,207,6,36,64,207,6,36,64,207,6,36,64
.byte 0,253,255,70,0,255,255,198,0,0,160,64,0,0,0,0
.byte 0,0,80,65,0,0,80,65,0,0,80,65,0,0,80,65
.byte 225,122,20,63,51,51,179,63,0,0,128,62,0,0,0,0
.byte 0,0,32,65,0,0,32,65,0,0,32,65,0,0,32,65
.byte 0,0,192,64,0,0,192,64,0,0,192,64,0,0,192,64
.byte 51,51,83,63,53,201,34,64,0,0,122,68,205,204,76,61
.byte 0,0,0,56,205,204,204,62,0,0,0,0,0,0,0,0
.byte 0,0,0,56,0,0,0,56,0,0,0,0,0,0,0,0
.byte 0,0,240,66,0,0,240,66,0,0,0,0,0,0,0,0
.byte 205,204,204,61,205,204,76,63,205,204,204,63,10,215,35,61
.byte 143,194,245,61,41,92,143,61,219,15,73,64,219,15,201,64
.byte 219,15,201,192,23,183,209,184,23,183,209,56,219,15,73,65
.byte 154,153,25,63,0,0,0,65,0,0,192,65,0,0,240,67
.byte 0,0,0,79,137,136,136,60,137,136,136,188,154,153,25,62
.byte 154,153,25,190,0,0,192,64,0,0,0,64,0,0,0,0
.byte 137,136,136,60,137,136,136,60,0,0,0,0,0,0,0,0
.byte 10,215,163,60,72,225,122,63,195,245,104,63,184,30,5,62
.byte 0,0,64,64,0,0,32,65,205,204,204,189,0,0,160,65
.byte 111,18,3,187,236,81,56,62,0,0,64,63,143,194,117,60
.byte 154,153,153,62,123,20,174,61,143,194,245,61,236,81,184,61
.byte 82,184,94,63,41,92,15,61,205,204,204,60,154,153,121,63
.byte 184,30,133,61,20,174,135,63,0,0,96,64,41,92,111,63
.byte 205,204,76,64,0,0,0,0,0,0,0,0,0,0,0,0
.byte 0,0,0,63,0,0,0,63,0,0,0,0,0,0,0,0
.byte 92,143,194,190,92,143,194,62,0,0,0,66,0,0,32,66
.byte 0,0,200,194,0,0,200,194,0,0,0,0,0,0,0,0
.byte 246,40,28,63,0,0,128,61,202,242,73,113,0,0,0,0
.byte 0,128,183,68,0,192,45,69,0,0,0,0,0,0,0,0
.byte 0,0,128,64,0,0,112,66,0,0,16,71,0,0,160,67
.byte 0,0,117,67,0,0,26,68,0,0,210,66,0,0,205,67
.byte 10,215,35,188,10,215,35,60,0,128,128,196,0,128,226,196
.byte 0,0,176,65,0,0,4,195,0,128,143,196,0,64,61,197
.byte 0,64,8,197,0,0,144,65,0,0,128,65,0,0,200,66
.byte 0,0,16,193,0,0,192,191,0,0,0,128,0,0,192,63
.byte 12,2,235,62,215,163,144,63,116,224,82,64,197,173,208,63
.byte 102,102,230,62,143,194,245,60,0,128,182,196,0,64,47,197
.byte 0,0,64,67,0,128,179,68,0,128,185,68,0,0,128,66
.byte 0,192,47,69,0,0,16,66,102,102,38,63,0,0,64,65
.byte 143,194,117,62,111,18,131,58,0,0,144,66,0,0,22,67
.byte 0,124,18,72,111,18,3,59,0,0,180,67,205,204,76,62
.byte 0,0,64,64,0,0,128,63,0,0,250,68,0,0,0,0
.byte 255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
.byte 0,128,59,71,0,0,0,67,0,0,0,0,0,0,0,0
.byte 0,0,0,197,0,0,0,69,0,0,0,0,0,0,0,0
.byte 0,0,0,197,0,0,0,75,0,0,0,0,0,0,128,95
.byte 0,0,254,66,0,0,126,67,0,0,0,62,219,15,73,191
.byte 63,64,3,63,219,15,73,63,102,102,230,190,0,0,224,64
.byte 233,72,174,60,0,254,255,74,0,0,0,0,0,0,0,0
.byte 0,0,80,193,0,0,80,193,0,0,0,0,0,0,0,0
.byte 0,0,128,61,0,0,128,61,0,0,0,0,0,0,0,0
.byte 0,0,180,66,0,0,128,195,0,128,182,68,0,64,45,69
.byte 0,128,182,66,0,64,45,67,0,0,160,194,0,0,52,68
.byte 0,0,240,194,0,0,12,68,154,153,153,63,0,0,200,194
.byte 0,0,57,68,0,0,17,68,0,0,128,191,63,53,94,62
.byte 0,0,200,194,0,0,200,194,0,0,200,194,0,0,200,194
.byte 172,197,39,55,0,0,128,67,0,0,0,0,0,0,0,0
.byte 0,0,64,64,0,0,64,64,0,0,0,0,0,0,0,0
.byte 0,0,224,64,0,0,192,64,0,0,0,0,0,0,0,0
.byte 0,0,128,193,0,0,32,195,0,0,0,0,0,0,0,0
.byte 0,0,128,193,0,0,128,193,0,0,0,0,0,0,0,0
.byte 0,0,0,0,0,0,128,63,0,0,0,0,0,0,0,0
.byte 0,0,112,194,0,0,47,68,0,128,9,68,0,0,0,0
.byte 202,242,73,113,202,242,73,113,202,242,73,113,202,242,73,113
.byte 0,0,0,95,40,107,110,78,40,107,110,206,0,0,32,68
.byte 0,0,0,61,51,51,179,62,205,204,76,190,251,250,122,63
.byte 161,160,160,60,0,0,122,196,0,0,77,67,0,0,127,67
.byte 202,242,73,241,0,0,0,0,0,0,0,0,0,0,0,0
.byte 202,242,73,113,202,242,73,241,202,242,73,113,202,242,73,241
.byte 0,0,242,67,0,0,128,192,0,0,33,68,0,0,128,192
.byte 0,0,33,196,0,0,242,195,0,0,0,0,0,0,0,0
.byte 202,242,73,241,202,242,73,113,202,242,73,241,202,242,73,113
.byte 0,0,242,67,0,0,33,68,0,0,128,192,0,0,36,68
.byte 0,0,248,67,0,0,72,66,0,0,0,192,171,170,170,191
.byte 0,128,185,66,0,64,46,67,0,64,46,69,0,0,240,193
.byte 0,128,39,68,0,0,255,67,0,0,0,191,61,10,215,62
.byte 149,191,214,51,0,36,116,73,186,73,12,62,88,160,139,64
.byte 10,215,35,62,0,0,156,65,0,0,200,65,0,0,64,66
.byte 174,71,225,61,0,0,240,65,102,102,6,64,102,102,102,63
.byte 0,0,96,66,181,61,31,64,154,153,153,64,0,0,0,0
.byte 219,15,201,64,219,15,201,64,0,0,0,0,0,0,0,0
.byte 0,0,192,64,0,0,192,64,0,0,0,0,0,0,0,0
.byte 0,0,0,61,0,0,0,61,0,0,0,0,0,0,0,0
.byte 164,112,125,64,164,112,125,64,0,0,0,0,0,0,0,0
.byte 0,0,62,68,0,255,127,71,0,0,0,0,0,0,0,0
.byte 0,255,127,71,0,255,127,71,0,0,0,0,0,0,0,0
.byte 0,0,128,190,0,0,128,190,0,0,0,0,0,0,0,0
.byte 0,0,0,65,0,0,0,65,0,0,0,0,0,0,0,0
.byte 205,204,76,191,0,0,0,0,0,0,0,0,0,0,0,0
.byte 0,0,0,67,0,0,0,67,0,0,0,67,0,0,0,67
.byte 0,0,0,196,0,0,12,195,0,0,67,68,0,0,52,195
.byte 0,0,37,68,185,14,212,68,38,95,141,68,88,160,11,64
.byte 219,15,201,62,0,0,16,65,0,0,160,66,0,0,0,193
.byte 0,0,192,193,205,204,204,191,102,102,166,63,0,0,144,64
.byte 0,0,240,66,146,10,6,64,146,10,134,64,0,0,112,65
.byte 209,83,251,63,195,245,8,64,51,51,179,64,133,235,17,65
.byte 0,0,64,65,0,0,64,65,0,0,0,65,0,0,0,0
.byte 0,0,64,65,0,0,64,65,0,0,0,0,0,0,0,0
.byte 0,0,64,192,71,225,250,65,184,30,133,190,51,51,147,63
.byte 130,226,71,188,11,206,164,64,41,92,15,189,0,0,64,62
.byte 88,160,139,190,124,217,160,63,51,51,179,190,102,102,134,64
.byte 0,0,128,190,10,215,163,189,254,152,25,64,0,0,72,67
.byte 219,15,201,63,0,0,0,0,0,0,0,0,0,0,0,0
.byte 0,0,64,64,102,102,38,191,0,0,0,0,0,0,0,0
.byte 205,204,204,190,0,0,0,0,0,0,0,0,0,0,0,0
.byte 0,0,128,63,0,0,0,0,0,0,0,0,0,0,128,63
.byte 51,51,51,63,0,0,192,66,23,183,81,58,10,215,163,62
.byte 53,250,142,60,0,0,0,0,0,0,0,0,0,0,0,0
.byte 51,51,179,193,51,51,179,193,0,0,0,0,0,0,0,0
.byte 124,217,32,63,0,0,0,0,0,0,0,0,0,0,0,0
.byte 0,0,32,193,0,0,32,193,0,0,0,0,0,0,0,0
.byte 0,0,32,65,0,0,32,65,0,0,0,0,0,0,0,0
.byte 154,153,89,63,82,73,157,57,82,73,29,58,51,51,51,62
.byte 80,119,86,62,0,0,0,0,0,0,0,0,0,0,0,0
.byte 10,215,163,61,10,215,163,61,0,0,0,0,0,0,0,0
.byte 10,215,163,61,102,102,102,66,0,0,48,66,0,0,0,0
.byte 0,0,192,64,0,0,64,65,0,0,32,193,0,0,0,0
.byte 0,0,192,63,0,0,64,64,0,0,22,68,0,0,224,65
.byte 10,215,35,63,0,0,144,193,0,0,112,193,0,32,153,70
.byte 0,128,31,68,0,0,239,67,0,0,224,192,0,0,192,192
.byte 0,0,56,66,0,0,82,67,146,10,134,62,0,0,16,67
.byte 0,0,128,68,0,0,0,0,0,0,128,63,154,153,89,63
.byte 0,0,47,67,0,0,141,67,0,0,55,67,0,0,0,0
.byte 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
.byte 0,0,0,0,0,0,224,66,0,0,220,67,0,0,132,67
.byte 0,0,160,63,0,0,0,0,0,0,0,0,0,0,0,0
.byte 0,0,0,64,0,0,0,64,0,0,0,64,0,0,0,0
.byte 0,0,32,67,0,0,0,0,0,0,0,0,0,0,0,0
.byte 0,0,16,65,0,0,16,65,0,0,16,65,0,0,16,65
.byte 0,0,0,0,0,0,92,66,0,0,92,66,0,0,0,0
.byte 0,128,255,67,0,128,255,67,0,128,255,67,0,128,255,67
.byte 0,0,120,194,0,0,248,193,0,0,248,65,0,0,120,66
.byte 0,0,70,67,0,0,70,67,0,0,70,67,0,0,70,67
.byte 0,0,92,194,0,128,255,67,0,0,248,65,0,0,70,67
.byte 0,0,248,193,0,0,178,66,0,0,96,65,0,0,95,68
.byte 0,0,214,67,236,81,56,190,143,2,64,67,0,0,0,0
.byte 0,0,0,67,0,128,182,68,0,0,0,0,0,0,0,63
.byte 0,0,108,67,0,128,182,68,0,0,0,0,205,204,76,63
.byte 0,0,108,67,0,128,179,68,0,0,0,0,0,0,128,63
.byte 0,0,124,67,0,128,179,68,0,0,0,0,0,0,128,63
.byte 205,204,76,63,154,153,25,63,0,0,0,0,0,0,0,0
.byte 0,0,64,67,0,0,58,68,0,0,0,0,0,0,0,0
.byte 0,0,32,67,0,0,53,68,0,0,0,0,0,0,128,63
.byte 0,0,96,67,0,0,53,68,0,0,0,0,0,0,128,63
.byte 0,0,32,67,0,0,63,68,0,0,0,0,0,0,128,63
.byte 0,0,96,67,0,0,63,68,0,0,0,0,0,0,128,63
.byte 0,0,200,66,0,0,70,68,0,0,0,0,102,102,38,63
.byte 0,0,65,68,0,0,56,68,0,0,0,0,102,102,166,63
.byte 0,0,72,68,0,0,44,68,0,0,0,0,102,102,166,63
.byte 0,0,57,68,0,0,184,67,218,15,201,191,205,204,76,63
.byte 0,0,78,68,0,0,184,67,218,15,201,63,205,204,76,63
.byte 0,0,57,68,0,0,240,67,218,15,201,191,205,204,76,63
.byte 0,0,78,68,0,0,240,67,218,15,201,63,205,204,76,63
.byte 0,0,57,68,0,0,20,68,218,15,201,191,205,204,76,63
.byte 0,0,78,68,0,0,20,68,218,15,201,63,205,204,76,63
.byte 0,0,64,67,0,0,232,67,218,15,201,63,154,153,153,63
.byte 0,0,36,67,0,0,212,67,0,0,0,0,0,0,128,63
.byte 0,0,92,67,0,0,212,67,0,0,0,0,0,0,128,63
.byte 0,0,36,67,0,0,225,67,0,0,0,0,0,0,128,63
.byte 0,0,92,67,0,0,225,67,0,0,0,0,0,0,128,63
.byte 0,0,36,67,0,0,238,67,0,0,0,0,0,0,128,63
.byte 0,0,92,67,0,0,238,67,0,0,0,0,0,0,128,63
.byte 0,0,36,67,0,0,251,67,0,0,0,0,0,0,128,63
.byte 0,0,92,67,0,0,251,67,0,0,0,0,0,0,128,63
.byte 0,0,184,66,0,0,164,67,218,15,201,191,102,102,102,63
.byte 0,0,146,67,0,0,164,67,218,15,201,63,102,102,102,63
.byte 0,0,184,66,0,0,10,68,218,15,201,191,102,102,102,63
.byte 0,0,146,67,0,0,10,68,218,15,201,63,102,102,102,63
.byte 0,128,164,68,0,0,232,67,0,0,0,0,0,0,128,63
.byte 0,128,164,68,0,0,10,68,0,0,0,0,0,0,128,63
.byte 0,128,164,68,0,0,32,68,0,0,0,0,0,0,128,63
.byte 0,128,164,68,0,0,54,68,0,0,0,0,0,0,128,63
.byte 0,128,164,68,0,0,76,68,0,0,0,0,0,0,128,63
.byte 0,128,164,68,0,0,98,68,0,0,0,0,0,0,128,63
.byte 236,120,173,224,236,120,173,96,0,0,0,0,0,0,0,0
.byte 0,0,16,65,0,0,192,64,0,0,16,193,0,0,192,192
.byte 0,0,188,68,0,0,164,68,0,0,144,67,0,0,136,67
.byte 0,0,92,68,0,0,84,68,0,0,180,68,0,0,160,68
.byte 0,0,176,68,0,0,24,68,0,0,0,0,0,0,0,0
.byte 0,0,64,67,0,128,172,68,0,0,0,0,0,0,0,0
.byte 0,128,172,68,66,0,64,67,0,0,60,195,0,128,139,196
.byte 0,0,0,195,0,128,180,196,137,1,16,69,12,2,224,65
.byte 0,0,160,66,0,0,200,66,0,0,160,193,205,204,76,189
.byte 0,0,128,194,0,0,0,0,0,0,128,63,0,0,192,63
.byte 0,0,32,194,0,128,71,69,0,0,42,67,0,0,140,66
.byte 178,143,112,63,125,27,68,63,212,208,49,62,92,28,124,63
.byte 68,29,175,62,187,141,36,63,0,0,232,65,0,0,85,67
.byte 0,128,229,67,0,160,254,68,0,8,161,69,0,112,205,69
.byte 0,113,18,71,0,143,146,71,0,0,208,66,0,224,195,68
.byte 0,252,23,70,0,19,122,71,0,220,27,198,0,0,52,194
.byte 0,0,18,67,0,0,160,192,0,0,48,65,0,0,0,0
.byte 10,215,35,60,10,215,35,60,0,0,0,0,0,0,0,0
.byte 0,0,128,63,0,0,128,63,0,0,0,0,0,0,0,0
.byte 0,0,160,67,0,0,112,67,0,0,0,0,0,0,0,0
.byte 0,128,181,68,0,192,49,69,0,0,0,0,0,0,0,0
.byte 0,0,107,68,0,0,17,68,0,0,0,0,0,0,0,0
.byte 0,128,155,68,0,128,184,68,0,0,0,0,0,0,0,0
.byte 151,255,15,65,151,255,127,65,0,192,168,71,0,0,32,64
.byte 0,0,97,69,205,204,140,63,51,51,83,64,51,51,243,63
.byte 110,219,54,65,154,153,153,190,0,0,124,66,0,0,0,194
.byte 0,0,250,69,0,0,0,0,0,0,0,0,0,0,0,0
.byte 0,0,0,63,0,0,0,63,92,143,194,62,31,133,107,62
.byte 0,0,0,63,61,10,87,63,174,71,97,62,143,194,245,190
.byte 205,204,76,62,0,0,0,62,113,61,138,62,3,0,16,71
.byte 0,0,52,67,0,0,0,0,0,0,0,0,0,0,0,0
.byte 0,0,128,65,0,0,128,65,0,0,0,0,0,0,0,0
.byte 0,0,150,67,108,18,3,74,0,0,0,0,0,0,0,0
.byte 0,0,0,0,0,0,200,194,0,0,0,0,0,0,0,0
.byte 0,0,128,63,0,0,0,63,0,128,181,196,0,64,48,197
.byte 0,128,179,196,0,64,46,197,0,128,184,196,0,128,185,196
.byte 171,170,170,63,0,0,128,63,0,64,54,73,0,16,120,73
.byte 0,0,128,63,205,204,76,63,0,0,0,0,0,0,0,0
.byte 0,0,0,63,0,0,200,194,0,0,0,0,0,0,0,0
.byte 205,204,204,61,0,0,0,64,0,0,192,65,0,0,128,65
.byte 0,0,72,68,0,0,0,0,0,0,224,65,0,0,160,65
.byte 0,0,0,63,0,0,128,63,0,0,168,66,171,170,42,63
.byte 10,215,67,63,0,0,0,0,205,204,204,61,205,204,76,62
.byte 0,0,112,67,0,0,12,66,0,0,80,65,0,0,76,65
.byte 0,0,52,65,0,0,128,60,102,102,102,191,236,81,8,64
.byte 0,0,64,63,51,51,115,63,0,0,128,62,143,194,245,61
.byte 41,92,15,62,10,215,163,188,0,0,72,195,0,0,82,68
.byte 0,0,150,195,0,0,128,255,0,0,128,51,0,0,0,0
.p2align 2
.Ltable1c00f4:
.long .L1e5b7,.L1e925,.L1eee5,.L1f06f,.L1f929,.L1f2e7
.p2align 2
.Ltable1c1e98:
.long .Lcc62f,.Lcc68e,.Lcc714,.Lcc74b,.Lcc9e4
.bss
.p2align 4
.space 16
.globl _arcade197_state
_arcade197_state:
.space 1804
.space 16
