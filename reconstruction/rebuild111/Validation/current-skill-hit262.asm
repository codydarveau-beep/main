
Source/main.obj:	file format coff-i386

Disassembly of section .text:

000b71a0 <_skill_hit_ex>:
   b71a0: 55                           	pushl	%ebp
   b71a1: 53                           	pushl	%ebx
   b71a2: 57                           	pushl	%edi
   b71a3: 56                           	pushl	%esi
   b71a4: 83 ec 10                     	subl	$0x10, %esp
   b71a7: 81 f9 4f 01 00 00            	cmpl	$0x14f, %ecx            # imm = 0x14F
   b71ad: 76 08                        	jbe	0xb71b7 <_skill_hit_ex+0x17>
   b71af: 83 c4 10                     	addl	$0x10, %esp
   b71b2: 5e                           	popl	%esi
   b71b3: 5f                           	popl	%edi
   b71b4: 5b                           	popl	%ebx
   b71b5: 5d                           	popl	%ebp
   b71b6: c3                           	retl
   b71b7: 8b 44 24 28                  	movl	0x28(%esp), %eax
   b71bb: 8b 74 24 24                  	movl	0x24(%esp), %esi
   b71bf: 89 34 24                     	movl	%esi, (%esp)
   b71c2: 69 f9 98 02 00 00            	imull	$0x298, %ecx, %edi      # imm = 0x298
   b71c8: 8b b7 a8 12 01 00            	movl	0x112a8(%edi), %esi
   b71ce: 81 fe 8f 02 00 00            	cmpl	$0x28f, %esi            # imm = 0x28F
   b71d4: 77 16                        	ja	0xb71ec <_skill_hit_ex+0x4c>
   b71d6: 89 f5                        	movl	%esi, %ebp
   b71d8: c1 e5 06                     	shll	$0x6, %ebp
   b71db: bb 3d f9 ff ff               	movl	$0xfffff93d, %ebx       # imm = 0xFFFFF93D
   b71e0: 03 9c b5 28 00 00 00         	addl	0x28(%ebp,%esi,4), %ebx
   b71e7: 83 fb f9                     	cmpl	$-0x7, %ebx
   b71ea: 77 c3                        	ja	0xb71af <_skill_hit_ex+0xf>
   b71ec: 85 d2                        	testl	%edx, %edx
   b71ee: 7e bf                        	jle	0xb71af <_skill_hit_ex+0xf>
   b71f0: 83 bf ac 12 01 00 00         	cmpl	$0x0, 0x112ac(%edi)
   b71f7: 7e b6                        	jle	0xb71af <_skill_hit_ex+0xf>
   b71f9: 83 f8 02                     	cmpl	$0x2, %eax
   b71fc: 7c 7d                        	jl	0xb727b <_skill_hit_ex+0xdb>
   b71fe: 89 f3                        	movl	%esi, %ebx
   b7200: c1 e3 06                     	shll	$0x6, %ebx
   b7203: f6 84 b3 2c 00 00 00 10      	testb	$0x10, 0x2c(%ebx,%esi,4)
   b720b: 75 6e                        	jne	0xb727b <_skill_hit_ex+0xdb>
   b720d: 8d b7 68 10 01 00            	leal	0x11068(%edi), %esi
   b7213: 83 f8 19                     	cmpl	$0x19, %eax
   b7216: bd 19 00 00 00               	movl	$0x19, %ebp
   b721b: 0f 4c e8                     	cmovll	%eax, %ebp
   b721e: 39 d5                        	cmpl	%edx, %ebp
   b7220: 0f 43 ea                     	cmovael	%edx, %ebp
   b7223: b8 00 e0 ff ff               	movl	$0xffffe000, %eax       # imm = 0xFFFFE000
   b7228: 0f 1f 84 00 00 00 00 00      	nopl	(%eax,%eax)
   b7230: 83 b8 64 0d 01 00 00         	cmpl	$0x0, 0x10d64(%eax)
   b7237: 0f 84 2d 01 00 00            	je	0xb736a <_skill_hit_ex+0x1ca>
   b723d: 83 c0 40                     	addl	$0x40, %eax
   b7240: 75 ee                        	jne	0xb7230 <_skill_hit_ex+0x90>
   b7242: f3 0f 10 87 18 11 01 00      	movss	0x11118(%edi), %xmm0
   b724a: 0f 2e 05 b8 4a 00 00         	ucomiss	0x4ab8, %xmm0
   b7251: 0f 86 15 02 00 00            	jbe	0xb746c <_skill_hit_ex+0x2cc>
   b7257: 89 c8                        	movl	%ecx, %eax
   b7259: 8d 8f 18 11 01 00            	leal	0x11118(%edi), %ecx
   b725f: c7 01 00 00 00 00            	movl	$0x0, (%ecx)
   b7265: 8d 0c 12                     	leal	(%edx,%edx), %ecx
   b7268: 81 fa 01 ca 9a 3b            	cmpl	$0x3b9aca01, %edx       # imm = 0x3B9ACA01
   b726e: bf 00 94 35 77               	movl	$0x77359400, %edi       # imm = 0x77359400
   b7273: 0f 42 f9                     	cmovbl	%ecx, %edi
   b7276: e9 f5 01 00 00               	jmp	0xb7470 <_skill_hit_ex+0x2d0>
   b727b: 8d b7 ac 12 01 00            	leal	0x112ac(%edi), %esi
   b7281: f3 0f 10 87 18 11 01 00      	movss	0x11118(%edi), %xmm0
   b7289: 0f 2e 05 b8 4a 00 00         	ucomiss	0x4ab8, %xmm0
   b7290: 76 21                        	jbe	0xb72b3 <_skill_hit_ex+0x113>
   b7292: 89 c8                        	movl	%ecx, %eax
   b7294: 8d 8f 18 11 01 00            	leal	0x11118(%edi), %ecx
   b729a: c7 01 00 00 00 00            	movl	$0x0, (%ecx)
   b72a0: 8d 0c 12                     	leal	(%edx,%edx), %ecx
   b72a3: 81 fa 01 ca 9a 3b            	cmpl	$0x3b9aca01, %edx       # imm = 0x3B9ACA01
   b72a9: bd 00 94 35 77               	movl	$0x77359400, %ebp       # imm = 0x77359400
   b72ae: 0f 42 e9                     	cmovbl	%ecx, %ebp
   b72b1: eb 04                        	jmp	0xb72b7 <_skill_hit_ex+0x117>
   b72b3: 89 c8                        	movl	%ecx, %eax
   b72b5: 89 d5                        	movl	%edx, %ebp
   b72b7: b9 00 00 00 00               	movl	$0x0, %ecx
   b72bc: 89 c2                        	movl	%eax, %edx
   b72be: 6a 01                        	pushl	$0x1
   b72c0: ff 74 24 04                  	pushl	0x4(%esp)
   b72c4: 55                           	pushl	%ebp
   b72c5: e8 00 00 00 00               	calll	0xb72ca <_skill_hit_ex+0x12a>
   b72ca: 83 c4 0c                     	addl	$0xc, %esp
   b72cd: 83 3e 00                     	cmpl	$0x0, (%esi)
   b72d0: 0f 8e d9 fe ff ff            	jle	0xb71af <_skill_hit_ex+0xf>
   b72d6: 8d 87 a8 12 01 00            	leal	0x112a8(%edi), %eax
   b72dc: 8b 00                        	movl	(%eax), %eax
   b72de: 3d 8f 02 00 00               	cmpl	$0x28f, %eax            # imm = 0x28F
   b72e3: 77 1a                        	ja	0xb72ff <_skill_hit_ex+0x15f>
   b72e5: 89 c1                        	movl	%eax, %ecx
   b72e7: c1 e1 06                     	shll	$0x6, %ecx
   b72ea: ba 3d f9 ff ff               	movl	$0xfffff93d, %edx       # imm = 0xFFFFF93D
   b72ef: 03 94 81 28 00 00 00         	addl	0x28(%ecx,%eax,4), %edx
   b72f6: 83 fa f9                     	cmpl	$-0x7, %edx
   b72f9: 0f 87 b0 fe ff ff            	ja	0xb71af <_skill_hit_ex+0xf>
   b72ff: 83 bf 8c 12 01 00 00         	cmpl	$0x0, 0x1128c(%edi)
   b7306: 74 14                        	je	0xb731c <_skill_hit_ex+0x17c>
   b7308: 8b 97 a0 12 01 00            	movl	0x112a0(%edi), %edx
   b730e: 85 d2                        	testl	%edx, %edx
   b7310: 74 0a                        	je	0xb731c <_skill_hit_ex+0x17c>
   b7312: 31 c9                        	xorl	%ecx, %ecx
   b7314: 83 fa 03                     	cmpl	$0x3, %edx
   b7317: 0f 94 c1                     	sete	%cl
   b731a: eb 0b                        	jmp	0xb7327 <_skill_hit_ex+0x187>
   b731c: 89 c1                        	movl	%eax, %ecx
   b731e: c1 e1 06                     	shll	$0x6, %ecx
   b7321: 8b 89 08 00 00 00            	movl	0x8(%ecx), %ecx
   b7327: 85 c9                        	testl	%ecx, %ecx
   b7329: 0f 85 80 fe ff ff            	jne	0xb71af <_skill_hit_ex+0xf>
   b732f: 0f b7 84 00 00 00 00 00      	movzwl	(%eax,%eax), %eax
   b7337: 0f 57 c0                     	xorps	%xmm0, %xmm0
   b733a: f3 0f 2a c0                  	cvtsi2ss	%eax, %xmm0
   b733e: f3 0f 5e 05 00 00 00 00      	divss	0x0, %xmm0
   b7346: f3 0f 58 05 b8 4a 00 00      	addss	0x4ab8, %xmm0
   b734e: 0f 2e 87 38 12 01 00         	ucomiss	0x11238(%edi), %xmm0
   b7355: 0f 86 54 fe ff ff            	jbe	0xb71af <_skill_hit_ex+0xf>
   b735b: 8d 87 38 12 01 00            	leal	0x11238(%edi), %eax
   b7361: f3 0f 11 00                  	movss	%xmm0, (%eax)
   b7365: e9 45 fe ff ff               	jmp	0xb71af <_skill_hit_ex+0xf>
   b736a: f3 0f 10 8f 18 11 01 00      	movss	0x11118(%edi), %xmm1
   b7372: f3 0f 10 05 b8 4a 00 00      	movss	0x4ab8, %xmm0
   b737a: 0f 2e c8                     	ucomiss	%xmm0, %xmm1
   b737d: 76 1d                        	jbe	0xb739c <_skill_hit_ex+0x1fc>
   b737f: 8d b7 18 11 01 00            	leal	0x11118(%edi), %esi
   b7385: c7 06 00 00 00 00            	movl	$0x0, (%esi)
   b738b: 8d 34 12                     	leal	(%edx,%edx), %esi
   b738e: 81 fa 01 ca 9a 3b            	cmpl	$0x3b9aca01, %edx       # imm = 0x3B9ACA01
   b7394: ba 00 94 35 77               	movl	$0x77359400, %edx       # imm = 0x77359400
   b7399: 0f 42 d6                     	cmovbl	%esi, %edx
   b739c: 8b 35 40 ed 00 00            	movl	0xed40, %esi
   b73a2: 8b bf a4 12 01 00            	movl	0x112a4(%edi), %edi
   b73a8: 89 7c 24 08                  	movl	%edi, 0x8(%esp)
   b73ac: 8b 3d 44 ed 00 00            	movl	0xed44, %edi
   b73b2: 8b 1d 10 44 00 00            	movl	0x4410, %ebx
   b73b8: 89 5c 24 04                  	movl	%ebx, 0x4(%esp)
   b73bc: 8b 1d cc df 00 00            	movl	0xdfcc, %ebx
   b73c2: 89 5c 24 0c                  	movl	%ebx, 0xc(%esp)
   b73c6: 8b 1d 08 e0 00 00            	movl	0xe008, %ebx
   b73cc: c7 80 64 0d 01 00 01 00 00 00	movl	$0x1, 0x10d64(%eax)
   b73d6: 89 88 68 0d 01 00            	movl	%ecx, 0x10d68(%eax)
   b73dc: 89 a8 6c 0d 01 00            	movl	%ebp, 0x10d6c(%eax)
   b73e2: c7 80 70 0d 01 00 00 00 00 00	movl	$0x0, 0x10d70(%eax)
   b73ec: 89 90 74 0d 01 00            	movl	%edx, 0x10d74(%eax)
   b73f2: c7 80 78 0d 01 00 00 00 00 00	movl	$0x0, 0x10d78(%eax)
   b73fc: 8b 0c 24                     	movl	(%esp), %ecx
   b73ff: 89 88 7c 0d 01 00            	movl	%ecx, 0x10d7c(%eax)
   b7405: 31 c9                        	xorl	%ecx, %ecx
   b7407: 83 fe 4e                     	cmpl	$0x4e, %esi
   b740a: 89 b0 80 0d 01 00            	movl	%esi, 0x10d80(%eax)
   b7410: 89 b8 84 0d 01 00            	movl	%edi, 0x10d84(%eax)
   b7416: 8b 54 24 04                  	movl	0x4(%esp), %edx
   b741a: 89 90 88 0d 01 00            	movl	%edx, 0x10d88(%eax)
   b7420: 8b 54 24 08                  	movl	0x8(%esp), %edx
   b7424: 89 90 8c 0d 01 00            	movl	%edx, 0x10d8c(%eax)
   b742a: 8b 54 24 0c                  	movl	0xc(%esp), %edx
   b742e: 89 90 90 0d 01 00            	movl	%edx, 0x10d90(%eax)
   b7434: 89 98 94 0d 01 00            	movl	%ebx, 0x10d94(%eax)
   b743a: 0f 94 c1                     	sete	%cl
   b743d: f3 0f 10 0c 8d 00 00 00 00   	movss	(,%ecx,4), %xmm1
   b7446: c7 80 98 0d 01 00 00 00 00 00	movl	$0x0, 0x10d98(%eax)
   b7450: f3 0f 11 80 9c 0d 01 00      	movss	%xmm0, 0x10d9c(%eax)
   b7458: f3 0f 11 88 a0 0d 01 00      	movss	%xmm1, 0x10da0(%eax)
   b7460: 83 c4 10                     	addl	$0x10, %esp
   b7463: 5e                           	popl	%esi
   b7464: 5f                           	popl	%edi
   b7465: 5b                           	popl	%ebx
   b7466: 5d                           	popl	%ebp
   b7467: e9 00 00 00 00               	jmp	0xb746c <_skill_hit_ex+0x2cc>
   b746c: 89 c8                        	movl	%ecx, %eax
   b746e: 89 d7                        	movl	%edx, %edi
   b7470: b9 00 00 00 00               	movl	$0x0, %ecx
   b7475: 89 c2                        	movl	%eax, %edx
   b7477: 55                           	pushl	%ebp
   b7478: ff 74 24 04                  	pushl	0x4(%esp)
   b747c: 57                           	pushl	%edi
   b747d: e8 00 00 00 00               	calll	0xb7482 <_skill_hit_ex+0x2e2>
   b7482: 83 c4 0c                     	addl	$0xc, %esp
   b7485: b9 00 00 00 00               	movl	$0x0, %ecx
   b748a: 89 f2                        	movl	%esi, %edx
   b748c: 83 c4 10                     	addl	$0x10, %esp
   b748f: 5e                           	popl	%esi
   b7490: 5f                           	popl	%edi
   b7491: 5b                           	popl	%ebx
   b7492: 5d                           	popl	%ebp
   b7493: e9 00 00 00 00               	jmp	0xb7498 <_skill_hit_ex+0x2f8>
   b7498: 0f 1f 84 00 00 00 00 00      	nopl	(%eax,%eax)
