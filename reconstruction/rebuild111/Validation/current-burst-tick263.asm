
Source/main.obj:	file format coff-i386

Disassembly of section .text:

000b74a0 <_skill_burst_tick49>:
   b74a0: 55                           	pushl	%ebp
   b74a1: 53                           	pushl	%ebx
   b74a2: 57                           	pushl	%edi
   b74a3: 56                           	pushl	%esi
   b74a4: 83 ec 0c                     	subl	$0xc, %esp
   b74a7: bf 00 e0 ff ff               	movl	$0xffffe000, %edi       # imm = 0xFFFFE000
   b74ac: f3 0f 10 15 00 00 00 00      	movss	0x0, %xmm2
   b74b4: eb 1d                        	jmp	0xb74d3 <_skill_burst_tick49+0x33>
   b74b6: 66 2e 0f 1f 84 00 00 00 00 00	nopw	%cs:(%eax,%eax)
   b74c0: c7 87 64 0d 01 00 00 00 00 00	movl	$0x0, 0x10d64(%edi)
   b74ca: 83 c7 40                     	addl	$0x40, %edi
   b74cd: 0f 84 60 03 00 00            	je	0xb7833 <_skill_burst_tick49+0x393>
   b74d3: 83 bf 64 0d 01 00 00         	cmpl	$0x0, 0x10d64(%edi)
   b74da: 74 ee                        	je	0xb74ca <_skill_burst_tick49+0x2a>
   b74dc: 83 3d d0 4a 00 00 00         	cmpl	$0x0, 0x4ad0
   b74e3: 7e db                        	jle	0xb74c0 <_skill_burst_tick49+0x20>
   b74e5: a1 cc df 00 00               	movl	0xdfcc, %eax
   b74ea: 3b 87 90 0d 01 00            	cmpl	0x10d90(%edi), %eax
   b74f0: 75 ce                        	jne	0xb74c0 <_skill_burst_tick49+0x20>
   b74f2: a1 08 e0 00 00               	movl	0xe008, %eax
   b74f7: 3b 87 94 0d 01 00            	cmpl	0x10d94(%edi), %eax
   b74fd: 75 c1                        	jne	0xb74c0 <_skill_burst_tick49+0x20>
   b74ff: 8b b7 68 0d 01 00            	movl	0x10d68(%edi), %esi
   b7505: 81 fe 50 01 00 00            	cmpl	$0x150, %esi            # imm = 0x150
   b750b: 73 b3                        	jae	0xb74c0 <_skill_burst_tick49+0x20>
   b750d: 69 ee 98 02 00 00            	imull	$0x298, %esi, %ebp      # imm = 0x298
   b7513: 83 bd b8 12 01 00 00         	cmpl	$0x0, 0x112b8(%ebp)
   b751a: 74 a4                        	je	0xb74c0 <_skill_burst_tick49+0x20>
   b751c: 83 bd ac 12 01 00 00         	cmpl	$0x0, 0x112ac(%ebp)
   b7523: 7e 9b                        	jle	0xb74c0 <_skill_burst_tick49+0x20>
   b7525: 8b 85 a4 12 01 00            	movl	0x112a4(%ebp), %eax
   b752b: 3b 87 8c 0d 01 00            	cmpl	0x10d8c(%edi), %eax
   b7531: 75 8d                        	jne	0xb74c0 <_skill_burst_tick49+0x20>
   b7533: f3 0f 10 05 b8 4a 00 00      	movss	0x4ab8, %xmm0
   b753b: f3 0f 58 c2                  	addss	%xmm2, %xmm0
   b753f: f3 0f 10 8f 9c 0d 01 00      	movss	0x10d9c(%edi), %xmm1
   b7547: 0f 2e c8                     	ucomiss	%xmm0, %xmm1
   b754a: 0f 87 7a ff ff ff            	ja	0xb74ca <_skill_burst_tick49+0x2a>
   b7550: 8b 87 74 0d 01 00            	movl	0x10d74(%edi), %eax
   b7556: 8b 8f 70 0d 01 00            	movl	0x10d70(%edi), %ecx
   b755c: 99                           	cltd
   b755d: f7 bf 6c 0d 01 00            	idivl	0x10d6c(%edi)
   b7563: 31 db                        	xorl	%ebx, %ebx
   b7565: 39 d1                        	cmpl	%edx, %ecx
   b7567: 0f 9c c3                     	setl	%bl
   b756a: 01 c3                        	addl	%eax, %ebx
   b756c: a1 40 ed 00 00               	movl	0xed40, %eax
   b7571: 89 44 24 08                  	movl	%eax, 0x8(%esp)
   b7575: a1 10 44 00 00               	movl	0x4410, %eax
   b757a: 89 44 24 04                  	movl	%eax, 0x4(%esp)
   b757e: 8b 87 88 0d 01 00            	movl	0x10d88(%edi), %eax
   b7584: a3 10 44 00 00               	movl	%eax, 0x4410
   b7589: 8b 87 80 0d 01 00            	movl	0x10d80(%edi), %eax
   b758f: a3 40 ed 00 00               	movl	%eax, 0xed40
   b7594: 31 c0                        	xorl	%eax, %eax
   b7596: 85 c9                        	testl	%ecx, %ecx
   b7598: 0f 9f c0                     	setg	%al
   b759b: a3 94 6e 00 00               	movl	%eax, 0x6e94
   b75a0: 8d 85 ac 12 01 00            	leal	0x112ac(%ebp), %eax
   b75a6: 89 04 24                     	movl	%eax, (%esp)
   b75a9: b9 00 00 00 00               	movl	$0x0, %ecx
   b75ae: 89 f2                        	movl	%esi, %edx
   b75b0: 6a 01                        	pushl	$0x1
   b75b2: ff b7 7c 0d 01 00            	pushl	0x10d7c(%edi)
   b75b8: 53                           	pushl	%ebx
   b75b9: e8 00 00 00 00               	calll	0xb75be <_skill_burst_tick49+0x11e>
   b75be: f3 0f 10 0d 00 00 00 00      	movss	0x0, %xmm1
   b75c6: 83 c4 0c                     	addl	$0xc, %esp
   b75c9: c7 05 94 6e 00 00 00 00 00 00	movl	$0x0, 0x6e94
   b75d3: 8b 44 24 08                  	movl	0x8(%esp), %eax
   b75d7: a3 40 ed 00 00               	movl	%eax, 0xed40
   b75dc: 8b 44 24 04                  	movl	0x4(%esp), %eax
   b75e0: a3 10 44 00 00               	movl	%eax, 0x4410
   b75e5: 03 9f 78 0d 01 00            	addl	0x10d78(%edi), %ebx
   b75eb: 89 de                        	movl	%ebx, %esi
   b75ed: 89 9f 78 0d 01 00            	movl	%ebx, 0x10d78(%edi)
   b75f3: ff 87 70 0d 01 00            	incl	0x10d70(%edi)
   b75f9: 8b 04 24                     	movl	(%esp), %eax
   b75fc: 83 38 00                     	cmpl	$0x0, (%eax)
   b75ff: 7e 7f                        	jle	0xb7680 <_skill_burst_tick49+0x1e0>
   b7601: 8b 85 a8 12 01 00            	movl	0x112a8(%ebp), %eax
   b7607: 3d 8f 02 00 00               	cmpl	$0x28f, %eax            # imm = 0x28F
   b760c: 77 18                        	ja	0xb7626 <_skill_burst_tick49+0x186>
   b760e: 89 c1                        	movl	%eax, %ecx
   b7610: c1 e1 06                     	shll	$0x6, %ecx
   b7613: 8b 8c 81 28 00 00 00         	movl	0x28(%ecx,%eax,4), %ecx
   b761a: ba 3d f9 ff ff               	movl	$0xfffff93d, %edx       # imm = 0xFFFFF93D
   b761f: 01 d1                        	addl	%edx, %ecx
   b7621: 83 f9 f9                     	cmpl	$-0x7, %ecx
   b7624: 77 5a                        	ja	0xb7680 <_skill_burst_tick49+0x1e0>
   b7626: 83 bd 8c 12 01 00 00         	cmpl	$0x0, 0x1128c(%ebp)
   b762d: 74 14                        	je	0xb7643 <_skill_burst_tick49+0x1a3>
   b762f: 8b 95 a0 12 01 00            	movl	0x112a0(%ebp), %edx
   b7635: 85 d2                        	testl	%edx, %edx
   b7637: 74 0a                        	je	0xb7643 <_skill_burst_tick49+0x1a3>
   b7639: 31 c9                        	xorl	%ecx, %ecx
   b763b: 83 fa 03                     	cmpl	$0x3, %edx
   b763e: 0f 94 c1                     	sete	%cl
   b7641: eb 0b                        	jmp	0xb764e <_skill_burst_tick49+0x1ae>
   b7643: 89 c1                        	movl	%eax, %ecx
   b7645: c1 e1 06                     	shll	$0x6, %ecx
   b7648: 8b 89 08 00 00 00            	movl	0x8(%ecx), %ecx
   b764e: 85 c9                        	testl	%ecx, %ecx
   b7650: 75 2e                        	jne	0xb7680 <_skill_burst_tick49+0x1e0>
   b7652: 0f b7 84 00 00 00 00 00      	movzwl	(%eax,%eax), %eax
   b765a: 0f 57 c0                     	xorps	%xmm0, %xmm0
   b765d: f3 0f 2a c0                  	cvtsi2ss	%eax, %xmm0
   b7661: f3 0f 5e c1                  	divss	%xmm1, %xmm0
   b7665: f3 0f 58 05 b8 4a 00 00      	addss	0x4ab8, %xmm0
   b766d: 0f 2e 85 38 12 01 00         	ucomiss	0x11238(%ebp), %xmm0
   b7674: 76 0a                        	jbe	0xb7680 <_skill_burst_tick49+0x1e0>
   b7676: 8d 85 38 12 01 00            	leal	0x11238(%ebp), %eax
   b767c: f3 0f 11 00                  	movss	%xmm0, (%eax)
   b7680: 8b 8f 80 0d 01 00            	movl	0x10d80(%edi), %ecx
   b7686: 83 f9 4b                     	cmpl	$0x4b, %ecx
   b7689: 74 14                        	je	0xb769f <_skill_burst_tick49+0x1ff>
   b768b: 83 f9 7e                     	cmpl	$0x7e, %ecx
   b768e: 89 f3                        	movl	%esi, %ebx
   b7690: 7f 0f                        	jg	0xb76a1 <_skill_burst_tick49+0x201>
   b7692: e8 00 00 00 00               	calll	0xb7697 <_skill_burst_tick49+0x1f7>
   b7697: 8b 9f 78 0d 01 00            	movl	0x10d78(%edi), %ebx
   b769d: eb 02                        	jmp	0xb76a1 <_skill_burst_tick49+0x201>
   b769f: 89 f3                        	movl	%esi, %ebx
   b76a1: 0f 57 c0                     	xorps	%xmm0, %xmm0
   b76a4: 0f 12 85 f8 11 01 00         	movlps	0x111f8(%ebp), %xmm0    # xmm0 = mem[0,1],xmm0[2,3]
   b76ab: 8b 87 98 0d 01 00            	movl	0x10d98(%edi), %eax
   b76b1: 8b 0d 64 10 01 00            	movl	0x11064, %ecx
   b76b7: 48                           	decl	%eax
   b76b8: 89 ca                        	movl	%ecx, %edx
   b76ba: 29 c2                        	subl	%eax, %edx
   b76bc: 76 21                        	jbe	0xb76df <_skill_burst_tick49+0x23f>
   b76be: 83 fa 10                     	cmpl	$0x10, %edx
   b76c1: 77 1c                        	ja	0xb76df <_skill_burst_tick49+0x23f>
   b76c3: 89 c6                        	movl	%eax, %esi
   b76c5: 83 e6 0f                     	andl	$0xf, %esi
   b76c8: 8d 14 76                     	leal	(%esi,%esi,2), %edx
   b76cb: c1 e2 04                     	shll	$0x4, %edx
   b76ce: 83 ba 80 0d 01 00 01         	cmpl	$0x1, 0x10d80(%edx)
   b76d5: 75 08                        	jne	0xb76df <_skill_burst_tick49+0x23f>
   b76d7: 83 e0 0f                     	andl	$0xf, %eax
   b76da: e9 9e 00 00 00               	jmp	0xb777d <_skill_burst_tick49+0x2dd>
   b76df: 85 db                        	testl	%ebx, %ebx
   b76e1: 0f 8e 88 00 00 00            	jle	0xb776f <_skill_burst_tick49+0x2cf>
   b76e7: 8d 41 01                     	leal	0x1(%ecx), %eax
   b76ea: a3 64 10 01 00               	movl	%eax, 0x11064
   b76ef: 83 e1 0f                     	andl	$0xf, %ecx
   b76f2: c1 e1 04                     	shll	$0x4, %ecx
   b76f5: f3 0f 10 0d b8 4a 00 00      	movss	0x4ab8, %xmm1
   b76fd: 0f 13 84 49 64 0d 01 00      	movlps	%xmm0, 0x10d64(%ecx,%ecx,2)
   b7705: f3 0f 11 8c 49 6c 0d 01 00   	movss	%xmm1, 0x10d6c(%ecx,%ecx,2)
   b770e: c7 84 49 70 0d 01 00 cd cc 4c 3e     	movl	$0x3e4ccccd, 0x10d70(%ecx,%ecx,2) # imm = 0x3E4CCCCD
   b7719: 89 9c 49 74 0d 01 00         	movl	%ebx, 0x10d74(%ecx,%ecx,2)
   b7720: c7 84 49 78 0d 01 00 01 00 00 00     	movl	$0x1, 0x10d78(%ecx,%ecx,2)
   b772b: c7 84 49 7c 0d 01 00 00 00 00 00     	movl	$0x0, 0x10d7c(%ecx,%ecx,2)
   b7736: c7 84 49 80 0d 01 00 00 00 00 00     	movl	$0x0, 0x10d80(%ecx,%ecx,2)
   b7741: c7 84 49 84 0d 01 00 00 00 00 00     	movl	$0x0, 0x10d84(%ecx,%ecx,2)
   b774c: c7 84 49 88 0d 01 00 00 00 00 00     	movl	$0x0, 0x10d88(%ecx,%ecx,2)
   b7757: c7 84 49 8c 0d 01 00 00 00 00 00     	movl	$0x0, 0x10d8c(%ecx,%ecx,2)
   b7762: c7 84 49 90 0d 01 00 00 00 00 00     	movl	$0x0, 0x10d90(%ecx,%ecx,2)
   b776d: eb 02                        	jmp	0xb7771 <_skill_burst_tick49+0x2d1>
   b776f: 89 c8                        	movl	%ecx, %eax
   b7771: 89 87 98 0d 01 00            	movl	%eax, 0x10d98(%edi)
   b7777: 48                           	decl	%eax
   b7778: 83 e0 0f                     	andl	$0xf, %eax
   b777b: 89 c6                        	movl	%eax, %esi
   b777d: 8d 95 68 10 01 00            	leal	0x11068(%ebp), %edx
   b7783: c1 e6 04                     	shll	$0x4, %esi
   b7786: 0f 13 84 76 64 0d 01 00      	movlps	%xmm0, 0x10d64(%esi,%esi,2)
   b778e: 89 9c 76 74 0d 01 00         	movl	%ebx, 0x10d74(%esi,%esi,2)
   b7795: f3 0f 10 05 b8 4a 00 00      	movss	0x4ab8, %xmm0
   b779d: f3 0f 11 84 76 6c 0d 01 00   	movss	%xmm0, 0x10d6c(%esi,%esi,2)
   b77a6: c7 84 76 80 0d 01 00 01 00 00 00     	movl	$0x1, 0x10d80(%esi,%esi,2)
   b77b1: 8d 04 40                     	leal	(%eax,%eax,2), %eax
   b77b4: c1 e0 04                     	shll	$0x4, %eax
   b77b7: 8d 80 64 0d 01 00            	leal	0x10d64(%eax), %eax
   b77bd: b9 00 00 00 00               	movl	$0x0, %ecx
   b77c2: 50                           	pushl	%eax
   b77c3: e8 00 00 00 00               	calll	0xb77c8 <_skill_burst_tick49+0x328>
   b77c8: 83 c4 04                     	addl	$0x4, %esp
   b77cb: 8b 87 70 0d 01 00            	movl	0x10d70(%edi), %eax
   b77d1: 3b 87 6c 0d 01 00            	cmpl	0x10d6c(%edi), %eax
   b77d7: 7d 43                        	jge	0xb781c <_skill_burst_tick49+0x37c>
   b77d9: 8b 0c 24                     	movl	(%esp), %ecx
   b77dc: 83 39 00                     	cmpl	$0x0, (%ecx)
   b77df: 7e 3b                        	jle	0xb781c <_skill_burst_tick49+0x37c>
   b77e1: 83 f8 01                     	cmpl	$0x1, %eax
   b77e4: f3 0f 10 15 00 00 00 00      	movss	0x0, %xmm2
   b77ec: f3 0f 10 05 00 00 00 00      	movss	0x0, %xmm0
   b77f4: 75 09                        	jne	0xb77ff <_skill_burst_tick49+0x35f>
   b77f6: 83 bf 80 0d 01 00 4e         	cmpl	$0x4e, 0x10d80(%edi)
   b77fd: 74 08                        	je	0xb7807 <_skill_burst_tick49+0x367>
   b77ff: f3 0f 10 87 a0 0d 01 00      	movss	0x10da0(%edi), %xmm0
   b7807: f3 0f 58 87 9c 0d 01 00      	addss	0x10d9c(%edi), %xmm0
   b780f: f3 0f 11 87 9c 0d 01 00      	movss	%xmm0, 0x10d9c(%edi)
   b7817: e9 ae fc ff ff               	jmp	0xb74ca <_skill_burst_tick49+0x2a>
   b781c: c7 87 64 0d 01 00 00 00 00 00	movl	$0x0, 0x10d64(%edi)
   b7826: f3 0f 10 15 00 00 00 00      	movss	0x0, %xmm2
   b782e: e9 97 fc ff ff               	jmp	0xb74ca <_skill_burst_tick49+0x2a>
   b7833: 83 c4 0c                     	addl	$0xc, %esp
   b7836: 5e                           	popl	%esi
   b7837: 5f                           	popl	%edi
   b7838: 5b                           	popl	%ebx
   b7839: 5d                           	popl	%ebp
   b783a: c3                           	retl
   b783b: 0f 1f 44 00 00               	nopl	(%eax,%eax)
