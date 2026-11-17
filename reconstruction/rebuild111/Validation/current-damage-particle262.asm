
Source/main.obj:	file format coff-i386

Disassembly of section .text:

00115c10 <_damage_particle53>:
  115c10: 55                           	pushl	%ebp
  115c11: 53                           	pushl	%ebx
  115c12: 57                           	pushl	%edi
  115c13: 56                           	pushl	%esi
  115c14: 83 ec 48                     	subl	$0x48, %esp
  115c17: f3 0f 10 54 24 60            	movss	0x60(%esp), %xmm2
  115c1d: f3 0f 5e 15 00 00 00 00      	divss	0x0, %xmm2
  115c25: 0f 57 c0                     	xorps	%xmm0, %xmm0
  115c28: 0f 2e c2                     	ucomiss	%xmm2, %xmm0
  115c2b: 0f 87 e2 03 00 00            	ja	0x116013 <_damage_particle53+0x403>
  115c31: 0f 2e 15 00 00 00 00         	ucomiss	0x0, %xmm2
  115c38: 0f 87 d5 03 00 00            	ja	0x116013 <_damage_particle53+0x403>
  115c3e: 89 d7                        	movl	%edx, %edi
  115c40: 89 ce                        	movl	%ecx, %esi
  115c42: f3 0f 10 01                  	movss	(%ecx), %xmm0
  115c46: f3 0f 10 49 04               	movss	0x4(%ecx), %xmm1
  115c4b: f3 0f 10 1d 00 00 00 00      	movss	0x0, %xmm3
  115c53: f3 0f 59 da                  	mulss	%xmm2, %xmm3
  115c57: f3 0f 58 d8                  	addss	%xmm0, %xmm3
  115c5b: f3 0f 11 5c 24 24            	movss	%xmm3, 0x24(%esp)
  115c61: f3 0f 10 1d 00 00 00 00      	movss	0x0, %xmm3
  115c69: 0f 11 54 24 38               	movups	%xmm2, 0x38(%esp)
  115c6e: f3 0f 59 da                  	mulss	%xmm2, %xmm3
  115c72: f3 0f 58 d9                  	addss	%xmm1, %xmm3
  115c76: f3 0f 11 5c 24 28            	movss	%xmm3, 0x28(%esp)
  115c7c: f3 0f 10 15 00 00 00 00      	movss	0x0, %xmm2
  115c84: 0f 28 d8                     	movaps	%xmm0, %xmm3
  115c87: f3 0f 59 da                  	mulss	%xmm2, %xmm3
  115c8b: f3 0f 2c cb                  	cvttss2si	%xmm3, %ecx
  115c8f: f3 0f 59 d1                  	mulss	%xmm1, %xmm2
  115c93: f3 0f 2c c2                  	cvttss2si	%xmm2, %eax
  115c97: 31 db                        	xorl	%ebx, %ebx
  115c99: 85 c9                        	testl	%ecx, %ecx
  115c9b: 0f 4e cb                     	cmovlel	%ebx, %ecx
  115c9e: 85 c0                        	testl	%eax, %eax
  115ca0: 0f 4f d8                     	cmovgl	%eax, %ebx
  115ca3: 8b 15 00 00 00 00            	movl	0x0, %edx
  115ca9: 8d 42 ff                     	leal	-0x1(%edx), %eax
  115cac: 39 d1                        	cmpl	%edx, %ecx
  115cae: 0f 4c c1                     	cmovll	%ecx, %eax
  115cb1: 8b 2d 00 00 00 00            	movl	0x0, %ebp
  115cb7: 8d 4d ff                     	leal	-0x1(%ebp), %ecx
  115cba: 39 eb                        	cmpl	%ebp, %ebx
  115cbc: 0f 4c cb                     	cmovll	%ebx, %ecx
  115cbf: f3 0f 2a e0                  	cvtsi2ss	%eax, %xmm4
  115cc3: f3 0f 5c dc                  	subss	%xmm4, %xmm3
  115cc7: 0f 57 e4                     	xorps	%xmm4, %xmm4
  115cca: f3 0f 2a e1                  	cvtsi2ss	%ecx, %xmm4
  115cce: f3 0f 5c d4                  	subss	%xmm4, %xmm2
  115cd2: 8b 1d 00 00 00 00            	movl	0x0, %ebx
  115cd8: 0f af ca                     	imull	%edx, %ecx
  115cdb: 01 c1                        	addl	%eax, %ecx
  115cdd: 8d 2c 8d 00 00 00 00         	leal	(,%ecx,4), %ebp
  115ce4: c1 e1 04                     	shll	$0x4, %ecx
  115ce7: 0f 2e da                     	ucomiss	%xmm2, %xmm3
  115cea: f3 0f 10 2c 0b               	movss	(%ebx,%ecx), %xmm5
  115cef: a1 00 00 00 00               	movl	0x0, %eax
  115cf4: 8b 15 00 00 00 00            	movl	0x0, %edx
  115cfa: 8b 0d 00 00 00 00            	movl	0x0, %ecx
  115d00: 76 1e                        	jbe	0x115d20 <_damage_particle53+0x110>
  115d02: f3 0f 10 74 ab 04            	movss	0x4(%ebx,%ebp,4), %xmm6
  115d08: f3 0f 10 64 ab 0c            	movss	0xc(%ebx,%ebp,4), %xmm4
  115d0e: f3 0f 5c e6                  	subss	%xmm6, %xmm4
  115d12: f3 0f 5c f5                  	subss	%xmm5, %xmm6
  115d16: f3 0f 59 f3                  	mulss	%xmm3, %xmm6
  115d1a: f3 0f 58 f5                  	addss	%xmm5, %xmm6
  115d1e: eb 1c                        	jmp	0x115d3c <_damage_particle53+0x12c>
  115d20: f3 0f 10 64 ab 08            	movss	0x8(%ebx,%ebp,4), %xmm4
  115d26: f3 0f 10 74 ab 0c            	movss	0xc(%ebx,%ebp,4), %xmm6
  115d2c: f3 0f 5c f4                  	subss	%xmm4, %xmm6
  115d30: f3 0f 59 f3                  	mulss	%xmm3, %xmm6
  115d34: f3 0f 58 f5                  	addss	%xmm5, %xmm6
  115d38: f3 0f 5c e5                  	subss	%xmm5, %xmm4
  115d3c: f3 0f 59 e2                  	mulss	%xmm2, %xmm4
  115d40: f3 0f 58 e6                  	addss	%xmm6, %xmm4
  115d44: 8b 5c 24 64                  	movl	0x64(%esp), %ebx
  115d48: f3 0f 11 64 24 0c            	movss	%xmm4, 0xc(%esp)
  115d4e: f3 0f 11 4c 24 08            	movss	%xmm1, 0x8(%esp)
  115d54: f3 0f 11 44 24 04            	movss	%xmm0, 0x4(%esp)
  115d5a: 89 04 24                     	movl	%eax, (%esp)
  115d5d: e8 00 00 00 00               	calll	0x115d62 <_damage_particle53+0x152>
  115d62: d9 5c 24 34                  	fstps	0x34(%esp)
  115d66: f3 0f 10 44 24 34            	movss	0x34(%esp), %xmm0
  115d6c: f3 0f 58 05 00 00 00 00      	addss	0x0, %xmm0
  115d74: f3 0f 11 44 24 20            	movss	%xmm0, 0x20(%esp)
  115d7a: f3 0f 10 05 00 00 00 00      	movss	0x0, %xmm0
  115d82: f3 0f 59 44 24 38            	mulss	0x38(%esp), %xmm0
  115d88: f3 0f 11 04 24               	movss	%xmm0, (%esp)
  115d8d: e8 00 00 00 00               	calll	0x115d92 <_damage_particle53+0x182>
  115d92: d9 5c 24 30                  	fstps	0x30(%esp)
  115d96: f3 0f 10 54 24 30            	movss	0x30(%esp), %xmm2
  115d9c: f3 0f 59 15 00 00 00 00      	mulss	0x0, %xmm2
  115da4: f3 0f 58 54 24 20            	addss	0x20(%esp), %xmm2
  115daa: f3 0f 10 47 04               	movss	0x4(%edi), %xmm0
  115daf: f3 0f 10 64 24 28            	movss	0x28(%esp), %xmm4
  115db5: f3 0f 59 c4                  	mulss	%xmm4, %xmm0
  115db9: f3 0f 10 0f                  	movss	(%edi), %xmm1
  115dbd: f3 0f 10 5c 24 24            	movss	0x24(%esp), %xmm3
  115dc3: f3 0f 59 cb                  	mulss	%xmm3, %xmm1
  115dc7: f3 0f 58 c8                  	addss	%xmm0, %xmm1
  115dcb: f3 0f 10 47 08               	movss	0x8(%edi), %xmm0
  115dd0: f3 0f 59 c2                  	mulss	%xmm2, %xmm0
  115dd4: f3 0f 58 c1                  	addss	%xmm1, %xmm0
  115dd8: f3 0f 58 47 0c               	addss	0xc(%edi), %xmm0
  115ddd: f3 0f 11 44 24 20            	movss	%xmm0, 0x20(%esp)
  115de3: f3 0f 59 67 14               	mulss	0x14(%edi), %xmm4
  115de8: f3 0f 59 5f 10               	mulss	0x10(%edi), %xmm3
  115ded: f3 0f 58 dc                  	addss	%xmm4, %xmm3
  115df1: f3 0f 59 57 18               	mulss	0x18(%edi), %xmm2
  115df6: f3 0f 58 d3                  	addss	%xmm3, %xmm2
  115dfa: f3 0f 58 57 1c               	addss	0x1c(%edi), %xmm2
  115dff: f3 0f 11 54 24 24            	movss	%xmm2, 0x24(%esp)
  115e05: f3 0f 10 05 00 00 00 00      	movss	0x0, %xmm0
  115e0d: f3 0f 5c 44 24 38            	subss	0x38(%esp), %xmm0
  115e13: f3 0f 59 05 00 00 00 00      	mulss	0x0, %xmm0
  115e1b: f3 0f 11 44 24 04            	movss	%xmm0, 0x4(%esp)
  115e21: c7 04 24 9a 99 99 3e         	movl	$0x3e99999a, (%esp)     # imm = 0x3E99999A
  115e28: e8 00 00 00 00               	calll	0x115e2d <_damage_particle53+0x21d>
  115e2d: d9 5c 24 2c                  	fstps	0x2c(%esp)
  115e31: f3 0f 10 5c 24 2c            	movss	0x2c(%esp), %xmm3
  115e37: 0f 10 44 24 38               	movups	0x38(%esp), %xmm0
  115e3c: f3 0f 59 05 00 00 00 00      	mulss	0x0, %xmm0
  115e44: f3 0f 2c c0                  	cvttss2si	%xmm0, %eax
  115e48: 89 c1                        	movl	%eax, %ecx
  115e4a: c1 f9 1f                     	sarl	$0x1f, %ecx
  115e4d: f3 0f 5c 05 00 00 00 00      	subss	0x0, %xmm0
  115e55: f3 0f 2c d0                  	cvttss2si	%xmm0, %edx
  115e59: 21 ca                        	andl	%ecx, %edx
  115e5b: 09 c2                        	orl	%eax, %edx
  115e5d: 83 fa 05                     	cmpl	$0x5, %edx
  115e60: bf 05 00 00 00               	movl	$0x5, %edi
  115e65: 0f 42 fa                     	cmovbl	%edx, %edi
  115e68: 83 7e 2c 00                  	cmpl	$0x0, 0x2c(%esi)
  115e6c: 0f 84 90 00 00 00            	je	0x115f02 <_damage_particle53+0x2f2>
  115e72: 8b 46 24                     	movl	0x24(%esi), %eax
  115e75: 85 c0                        	testl	%eax, %eax
  115e77: 0f 84 85 00 00 00            	je	0x115f02 <_damage_particle53+0x2f2>
  115e7d: 69 c0 83 00 00 00            	imull	$0x83, %eax, %eax
  115e83: 69 4e 28 ef 1e 00 00         	imull	$0x1eef, 0x28(%esi), %ecx # imm = 0x1EEF
  115e8a: 01 c1                        	addl	%eax, %ecx
  115e8c: 89 c8                        	movl	%ecx, %eax
  115e8e: c1 e8 10                     	shrl	$0x10, %eax
  115e91: 31 c8                        	xorl	%ecx, %eax
  115e93: 69 c8 2d 35 eb 7f            	imull	$0x7feb352d, %eax, %ecx # imm = 0x7FEB352D
  115e99: 89 c8                        	movl	%ecx, %eax
  115e9b: c1 e8 0f                     	shrl	$0xf, %eax
  115e9e: 31 c8                        	xorl	%ecx, %eax
  115ea0: 0f b6 c8                     	movzbl	%al, %ecx
  115ea3: 0f 57 c0                     	xorps	%xmm0, %xmm0
  115ea6: f3 0f 2a c1                  	cvtsi2ss	%ecx, %xmm0
  115eaa: f3 0f 10 0d 00 00 00 00      	movss	0x0, %xmm1
  115eb2: f3 0f 5e c1                  	divss	%xmm1, %xmm0
  115eb6: f3 0f 10 15 00 00 00 00      	movss	0x0, %xmm2
  115ebe: f3 0f 58 c2                  	addss	%xmm2, %xmm0
  115ec2: f3 0f 59 05 00 00 00 00      	mulss	0x0, %xmm0
  115eca: f3 0f 59 c3                  	mulss	%xmm3, %xmm0
  115ece: f3 0f 10 74 24 20            	movss	0x20(%esp), %xmm6
  115ed4: f3 0f 58 f0                  	addss	%xmm0, %xmm6
  115ed8: 0f b6 c4                     	movzbl	%ah, %eax
  115edb: 0f 57 c0                     	xorps	%xmm0, %xmm0
  115ede: f3 0f 2a c0                  	cvtsi2ss	%eax, %xmm0
  115ee2: f3 0f 5e c1                  	divss	%xmm1, %xmm0
  115ee6: f3 0f 58 c2                  	addss	%xmm2, %xmm0
  115eea: f3 0f 59 05 00 00 00 00      	mulss	0x0, %xmm0
  115ef2: f3 0f 59 c3                  	mulss	%xmm3, %xmm0
  115ef6: f3 0f 10 7c 24 24            	movss	0x24(%esp), %xmm7
  115efc: f3 0f 58 f8                  	addss	%xmm0, %xmm7
  115f00: eb 0c                        	jmp	0x115f0e <_damage_particle53+0x2fe>
  115f02: f3 0f 10 7c 24 24            	movss	0x24(%esp), %xmm7
  115f08: f3 0f 10 74 24 20            	movss	0x20(%esp), %xmm6
  115f0e: 8b 74 24 5c                  	movl	0x5c(%esp), %esi
  115f12: 85 db                        	testl	%ebx, %ebx
  115f14: 0f 84 d9 00 00 00            	je	0x115ff3 <_damage_particle53+0x3e3>
  115f1a: f3 0f 10 05 00 00 00 00      	movss	0x0, %xmm0
  115f22: f3 0f 59 c3                  	mulss	%xmm3, %xmm0
  115f26: 0f b7 04 fd 26 0a 00 00      	movzwl	0xa26(,%edi,8), %eax
  115f2e: 0f 57 c9                     	xorps	%xmm1, %xmm1
  115f31: f3 0f 2a c8                  	cvtsi2ss	%eax, %xmm1
  115f35: 0f b7 04 fd 24 0a 00 00      	movzwl	0xa24(,%edi,8), %eax
  115f3d: 0f 57 d2                     	xorps	%xmm2, %xmm2
  115f40: f3 0f 2a d0                  	cvtsi2ss	%eax, %xmm2
  115f44: 0f b7 04 fd 22 0a 00 00      	movzwl	0xa22(,%edi,8), %eax
  115f4c: f3 0f 11 5c 24 38            	movss	%xmm3, 0x38(%esp)
  115f52: 0f 57 db                     	xorps	%xmm3, %xmm3
  115f55: f3 0f 2a d8                  	cvtsi2ss	%eax, %xmm3
  115f59: 0f b7 04 fd 20 0a 00 00      	movzwl	0xa20(,%edi,8), %eax
  115f61: 0f 28 e0                     	movaps	%xmm0, %xmm4
  115f64: f3 0f 59 e1                  	mulss	%xmm1, %xmm4
  115f68: f3 0f 59 c2                  	mulss	%xmm2, %xmm0
  115f6c: f3 0f 10 2d 00 00 00 00      	movss	0x0, %xmm5
  115f74: f3 0f 11 74 24 20            	movss	%xmm6, 0x20(%esp)
  115f7a: 0f 28 f4                     	movaps	%xmm4, %xmm6
  115f7d: f3 0f 59 f5                  	mulss	%xmm5, %xmm6
  115f81: f3 0f 11 7c 24 24            	movss	%xmm7, 0x24(%esp)
  115f87: f3 0f 10 7c 24 24            	movss	0x24(%esp), %xmm7
  115f8d: f3 0f 5c fe                  	subss	%xmm6, %xmm7
  115f91: f3 0f 59 e8                  	mulss	%xmm0, %xmm5
  115f95: f3 0f 10 74 24 20            	movss	0x20(%esp), %xmm6
  115f9b: f3 0f 5c f5                  	subss	%xmm5, %xmm6
  115f9f: 0f 57 ed                     	xorps	%xmm5, %xmm5
  115fa2: f3 0f 2a e8                  	cvtsi2ss	%eax, %xmm5
  115fa6: f3 0f 11 4c 24 1c            	movss	%xmm1, 0x1c(%esp)
  115fac: f3 0f 11 54 24 18            	movss	%xmm2, 0x18(%esp)
  115fb2: f3 0f 11 5c 24 14            	movss	%xmm3, 0x14(%esp)
  115fb8: f3 0f 11 6c 24 10            	movss	%xmm5, 0x10(%esp)
  115fbe: f3 0f 11 64 24 0c            	movss	%xmm4, 0xc(%esp)
  115fc4: f3 0f 11 44 24 08            	movss	%xmm0, 0x8(%esp)
  115fca: f3 0f 11 7c 24 04            	movss	%xmm7, 0x4(%esp)
  115fd0: f3 0f 11 34 24               	movss	%xmm6, (%esp)
  115fd5: e8 00 00 00 00               	calll	0x115fda <_damage_particle53+0x3ca>
  115fda: f3 0f 10 5c 24 38            	movss	0x38(%esp), %xmm3
  115fe0: f3 0f 10 74 24 20            	movss	0x20(%esp), %xmm6
  115fe6: f3 0f 10 7c 24 24            	movss	0x24(%esp), %xmm7
  115fec: ba 01 00 00 00               	movl	$0x1, %edx
  115ff1: eb 04                        	jmp	0x115ff7 <_damage_particle53+0x3e7>
  115ff3: 8b 54 24 68                  	movl	0x68(%esp), %edx
  115ff7: 89 7c 24 0c                  	movl	%edi, 0xc(%esp)
  115ffb: f3 0f 11 5c 24 08            	movss	%xmm3, 0x8(%esp)
  116001: f3 0f 11 7c 24 04            	movss	%xmm7, 0x4(%esp)
  116007: f3 0f 11 34 24               	movss	%xmm6, (%esp)
  11600c: 89 f1                        	movl	%esi, %ecx
  11600e: e8 00 00 00 00               	calll	0x116013 <_damage_particle53+0x403>
  116013: 83 c4 48                     	addl	$0x48, %esp
  116016: 5e                           	popl	%esi
  116017: 5f                           	popl	%edi
  116018: 5b                           	popl	%ebx
  116019: 5d                           	popl	%ebp
  11601a: c3                           	retl
  11601b: 0f 1f 44 00 00               	nopl	(%eax,%eax)
