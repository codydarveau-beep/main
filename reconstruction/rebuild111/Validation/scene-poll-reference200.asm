   c9a70:	53                   	push   ebx
   c9a71:	57                   	push   edi
   c9a72:	56                   	push   esi
   c9a73:	81 ec 34 02 00 00    	sub    esp,0x234
   c9a79:	e8 52 01 00 00       	call   0xc9bd0
   c9a7e:	83 3d 2c 2a d4 00 00 	cmp    DWORD PTR ds:0xd42a2c,0x0
   c9a85:	0f 84 92 00 00 00    	je     0xc9b1d
   c9a8b:	89 c7                	mov    edi,eax
   c9a8d:	8b 0d 28 2a d4 00    	mov    ecx,DWORD PTR ds:0xd42a28
   c9a93:	89 e2                	mov    edx,esp
   c9a95:	e8 16 7f fc ff       	call   0x919b0
   c9a9a:	83 f8 01             	cmp    eax,0x1
   c9a9d:	75 79                	jne    0xc9b18
   c9a9f:	8b 4c 24 14          	mov    ecx,DWORD PTR [esp+0x14]
   c9aa3:	3b 0d 4c 2a d4 00    	cmp    ecx,DWORD PTR ds:0xd42a4c
   c9aa9:	89 f8                	mov    eax,edi
   c9aab:	74 70                	je     0xc9b1d
   c9aad:	89 0d 4c 2a d4 00    	mov    DWORD PTR ds:0xd42a4c,ecx
   c9ab3:	c7 05 48 2a d4 00 00 	mov    DWORD PTR ds:0xd42a48,0x0
   c9aba:	00 00 00 
   c9abd:	c7 05 44 2a d4 00 00 	mov    DWORD PTR ds:0xd42a44,0x0
   c9ac4:	00 00 00 
   c9ac7:	83 3d 2c 2a d4 00 00 	cmp    DWORD PTR ds:0xd42a2c,0x0
   c9ace:	74 57                	je     0xc9b27
   c9ad0:	8b 0d 28 2a d4 00    	mov    ecx,DWORD PTR ds:0xd42a28
   c9ad6:	8d 54 24 34          	lea    edx,[esp+0x34]
   c9ada:	e8 d1 7e fc ff       	call   0x919b0
   c9adf:	be 09 8d bd 00       	mov    esi,0xbd8d09
   c9ae4:	83 f8 01             	cmp    eax,0x1
   c9ae7:	75 43                	jne    0xc9b2c
   c9ae9:	8b 44 24 34          	mov    eax,DWORD PTR [esp+0x34]
   c9aed:	3b 05 3c 2a d4 00    	cmp    eax,DWORD PTR ds:0xd42a3c
   c9af3:	75 37                	jne    0xc9b2c
   c9af5:	8b 44 24 48          	mov    eax,DWORD PTR [esp+0x48]
   c9af9:	3b 05 34 2a d4 00    	cmp    eax,DWORD PTR ds:0xd42a34
   c9aff:	73 2b                	jae    0xc9b2c
   c9b01:	8b 0d 2c 2a d4 00    	mov    ecx,DWORD PTR ds:0xd42a2c
   c9b07:	8b 35 38 2a d4 00    	mov    esi,DWORD PTR ds:0xd42a38
   c9b0d:	01 ce                	add    esi,ecx
   c9b0f:	c1 e0 05             	shl    eax,0x5
   c9b12:	03 74 01 18          	add    esi,DWORD PTR [ecx+eax*1+0x18]
   c9b16:	eb 14                	jmp    0xc9b2c
   c9b18:	b8 ff ff ff ff       	mov    eax,0xffffffff
   c9b1d:	81 c4 34 02 00 00    	add    esp,0x234
   c9b23:	5e                   	pop    esi
   c9b24:	5f                   	pop    edi
   c9b25:	5b                   	pop    ebx
   c9b26:	c3                   	ret
   c9b27:	be 09 8d bd 00       	mov    esi,0xbd8d09
   c9b2c:	68 9d 92 a1 00       	push   0xa1929d
   c9b31:	56                   	push   esi
   c9b32:	e8 d9 e5 06 00       	call   0x138110
   c9b37:	83 c4 08             	add    esp,0x8
   c9b3a:	85 c0                	test   eax,eax
   c9b3c:	74 26                	je     0xc9b64
   c9b3e:	8d 48 07             	lea    ecx,[eax+0x7]
   c9b41:	8d 54 24 18          	lea    edx,[esp+0x18]
   c9b45:	29 f0                	sub    eax,esi
   c9b47:	8d 5c 24 34          	lea    ebx,[esp+0x34]
   c9b4b:	51                   	push   ecx
   c9b4c:	52                   	push   edx
   c9b4d:	56                   	push   esi
   c9b4e:	50                   	push   eax
   c9b4f:	68 4d 4d a4 00       	push   0xa44d4d
   c9b54:	68 00 02 00 00       	push   0x200
   c9b59:	53                   	push   ebx
   c9b5a:	e8 81 dc 06 00       	call   0x1377e0
   c9b5f:	83 c4 1c             	add    esp,0x1c
   c9b62:	89 de                	mov    esi,ebx
   c9b64:	89 f1                	mov    ecx,esi
   c9b66:	ba 74 2b d4 00       	mov    edx,0xd42b74
   c9b6b:	68 00 00 80 3f       	push   0x3f800000
   c9b70:	68 74 01 00 00       	push   0x174
   c9b75:	e8 86 c5 fc ff       	call   0x96100
   c9b7a:	83 c4 08             	add    esp,0x8
   c9b7d:	a3 74 2e d4 00       	mov    ds:0xd42e74,eax
   c9b82:	89 f8                	mov    eax,edi
   c9b84:	83 ff 06             	cmp    edi,0x6
   c9b87:	75 94                	jne    0xc9b1d
   c9b89:	68 0c 01 00 00       	push   0x10c
   c9b8e:	6a 00                	push   0x0
   c9b90:	68 68 2a d4 00       	push   0xd42a68
   c9b95:	e8 86 d8 06 00       	call   0x137420
   c9b9a:	89 f8                	mov    eax,edi
   c9b9c:	83 c4 0c             	add    esp,0xc
   c9b9f:	c7 05 70 2b d4 00 01 	mov    DWORD PTR ds:0xd42b70,0x1
   c9ba6:	00 00 00 
   c9ba9:	c7 05 64 2a d4 00 00 	mov    DWORD PTR ds:0xd42a64,0x0
   c9bb0:	00 00 00 
   c9bb3:	c7 05 60 2a d4 00 00 	mov    DWORD PTR ds:0xd42a60,0x0
   c9bba:	00 00 00 
   c9bbd:	e9 5b ff ff ff       	jmp    0xc9b1d
   c9bc2:	66 2e 0f 1f 84 00 00 	nop    WORD PTR cs:[eax+eax*1+0x0]
   c9bc9:	00 00 00 
   c9bcc:	0f 1f 40 00          	nop    DWORD PTR [eax+0x0]
   c9bd0:	83 3d 2c 2a d4 00 00 	cmp    DWORD PTR ds:0xd42a2c,0x0
   c9bd7:	0f 84 fc 01 00 00    	je     0xc9dd9
   c9bdd:	55                   	push   ebp
   c9bde:	53                   	push   ebx
   c9bdf:	57                   	push   edi
   c9be0:	56                   	push   esi
   c9be1:	83 ec 74             	sub    esp,0x74
   c9be4:	bb 40 00 00 00       	mov    ebx,0x40
   c9be9:	8d 7c 24 0c          	lea    edi,[esp+0xc]
   c9bed:	8b 0d 28 2a d4 00    	mov    ecx,DWORD PTR ds:0xd42a28
   c9bf3:	8d 54 24 40          	lea    edx,[esp+0x40]
   c9bf7:	e8 b4 7d fc ff       	call   0x919b0
   c9bfc:	83 f8 01             	cmp    eax,0x1
   c9bff:	0f 85 02 03 00 00    	jne    0xc9f07
   c9c05:	8b 44 24 40          	mov    eax,DWORD PTR [esp+0x40]
   c9c09:	3b 05 3c 2a d4 00    	cmp    eax,DWORD PTR ds:0xd42a3c
   c9c0f:	0f 85 f2 02 00 00    	jne    0xc9f07
   c9c15:	8b 54 24 54          	mov    edx,DWORD PTR [esp+0x54]
   c9c19:	8b 35 34 2a d4 00    	mov    esi,DWORD PTR ds:0xd42a34
   c9c1f:	39 f2                	cmp    edx,esi
   c9c21:	0f 83 e0 02 00 00    	jae    0xc9f07
   c9c27:	89 04 24             	mov    DWORD PTR [esp],eax
   c9c2a:	89 5c 24 08          	mov    DWORD PTR [esp+0x8],ebx
   c9c2e:	89 fd                	mov    ebp,edi
   c9c30:	8b 1d 2c 2a d4 00    	mov    ebx,DWORD PTR ds:0xd42a2c
   c9c36:	c1 e2 05             	shl    edx,0x5
   c9c39:	0f b6 44 13 10       	movzx  eax,BYTE PTR [ebx+edx*1+0x10]
   c9c3e:	0f b6 7c 13 11       	movzx  edi,BYTE PTR [ebx+edx*1+0x11]
   c9c43:	85 ff                	test   edi,edi
   c9c45:	0f b7 4c 13 12       	movzx  ecx,WORD PTR [ebx+edx*1+0x12]
   c9c4a:	89 4c 24 04          	mov    DWORD PTR [esp+0x4],ecx
   c9c4e:	74 16                	je     0xc9c66
   c9c50:	8b 4c 24 44          	mov    ecx,DWORD PTR [esp+0x44]
   c9c54:	85 c9                	test   ecx,ecx
   c9c56:	0f 84 83 01 00 00    	je     0xc9ddf
   c9c5c:	fe c9                	dec    cl
   c9c5e:	0f b6 c9             	movzx  ecx,cl
   c9c61:	0f a3 cf             	bt     edi,ecx
   c9c64:	73 2a                	jae    0xc9c90
   c9c66:	8d 48 ff             	lea    ecx,[eax-0x1]
   c9c69:	83 f9 07             	cmp    ecx,0x7
   c9c6c:	0f 87 e6 00 00 00    	ja     0xc9d58
   c9c72:	89 ef                	mov    edi,ebp
   c9c74:	ff 24 8d 78 1e 1c 00 	jmp    DWORD PTR [ecx*4+0x1c1e78]
   c9c7b:	8b 44 24 50          	mov    eax,DWORD PTR [esp+0x50]
   c9c7f:	f7 d0                	not    eax
   c9c81:	85 44 13 28          	test   DWORD PTR [ebx+edx*1+0x28],eax
   c9c85:	0f 84 cf 00 00 00    	je     0xc9d5a
   c9c8b:	e9 f5 02 00 00       	jmp    0xc9f85
   c9c90:	8b 44 24 04          	mov    eax,DWORD PTR [esp+0x4]
   c9c94:	39 c6                	cmp    esi,eax
   c9c96:	0f 86 6b 02 00 00    	jbe    0xc9f07
   c9c9c:	3d ff 00 00 00       	cmp    eax,0xff
   c9ca1:	0f 87 60 02 00 00    	ja     0xc9f07
   c9ca7:	89 ef                	mov    edi,ebp
   c9ca9:	8b 1d 28 2a d4 00    	mov    ebx,DWORD PTR ds:0xd42a28
   c9caf:	89 d9                	mov    ecx,ebx
   c9cb1:	89 ea                	mov    edx,ebp
   c9cb3:	e8 f8 7c fc ff       	call   0x919b0
   c9cb8:	83 f8 01             	cmp    eax,0x1
   c9cbb:	0f 85 46 02 00 00    	jne    0xc9f07
   c9cc1:	8b 44 24 0c          	mov    eax,DWORD PTR [esp+0xc]
   c9cc5:	3b 04 24             	cmp    eax,DWORD PTR [esp]
   c9cc8:	0f 85 39 02 00 00    	jne    0xc9f07
   c9cce:	83 f8 24             	cmp    eax,0x24
   c9cd1:	0f 83 30 02 00 00    	jae    0xc9f07
   c9cd7:	8b 44 24 04          	mov    eax,DWORD PTR [esp+0x4]
   c9cdb:	89 44 24 20          	mov    DWORD PTR [esp+0x20],eax
   c9cdf:	e9 c5 00 00 00       	jmp    0xc9da9
   c9ce4:	8b 74 13 28          	mov    esi,DWORD PTR [ebx+edx*1+0x28]
   c9ce8:	8d 86 00 00 f8 ff    	lea    eax,[esi-0x80000]
   c9cee:	3d 01 00 f8 ff       	cmp    eax,0xfff80001
   c9cf3:	0f 82 0e 02 00 00    	jb     0xc9f07
   c9cf9:	8b 1d 28 2a d4 00    	mov    ebx,DWORD PTR ds:0xd42a28
   c9cff:	89 d9                	mov    ecx,ebx
   c9d01:	89 fa                	mov    edx,edi
   c9d03:	e8 a8 7c fc ff       	call   0x919b0
   c9d08:	83 f8 01             	cmp    eax,0x1
   c9d0b:	0f 85 f6 01 00 00    	jne    0xc9f07
   c9d11:	8b 04 24             	mov    eax,DWORD PTR [esp]
   c9d14:	39 44 24 0c          	cmp    DWORD PTR [esp+0xc],eax
   c9d18:	0f 85 e9 01 00 00    	jne    0xc9f07
   c9d1e:	09 74 24 18          	or     DWORD PTR [esp+0x18],esi
   c9d22:	80 4c 24 1c 01       	or     BYTE PTR [esp+0x1c],0x1
   c9d27:	89 d9                	mov    ecx,ebx
   c9d29:	89 fa                	mov    edx,edi
   c9d2b:	e8 90 7f fc ff       	call   0x91cc0
   c9d30:	85 c0                	test   eax,eax
   c9d32:	0f 84 cf 01 00 00    	je     0xc9f07
   c9d38:	8b 35 34 2a d4 00    	mov    esi,DWORD PTR ds:0xd42a34
   c9d3e:	eb 1a                	jmp    0xc9d5a
   c9d40:	83 7c 24 44 00       	cmp    DWORD PTR [esp+0x44],0x0
   c9d45:	75 13                	jne    0xc9d5a
   c9d47:	e9 93 00 00 00       	jmp    0xc9ddf
   c9d4c:	80 7c 24 58 00       	cmp    BYTE PTR [esp+0x58],0x0
   c9d51:	75 07                	jne    0xc9d5a
   c9d53:	e9 5e 01 00 00       	jmp    0xc9eb6
   c9d58:	89 ef                	mov    edi,ebp
   c9d5a:	8b 6c 24 04          	mov    ebp,DWORD PTR [esp+0x4]
   c9d5e:	39 ee                	cmp    esi,ebp
   c9d60:	0f 86 a1 01 00 00    	jbe    0xc9f07
   c9d66:	81 fd ff 00 00 00    	cmp    ebp,0xff
   c9d6c:	0f 87 95 01 00 00    	ja     0xc9f07
   c9d72:	8b 35 3c 2a d4 00    	mov    esi,DWORD PTR ds:0xd42a3c
   c9d78:	8b 1d 28 2a d4 00    	mov    ebx,DWORD PTR ds:0xd42a28
   c9d7e:	89 d9                	mov    ecx,ebx
   c9d80:	89 fa                	mov    edx,edi
   c9d82:	e8 29 7c fc ff       	call   0x919b0
   c9d87:	83 f8 01             	cmp    eax,0x1
   c9d8a:	0f 85 77 01 00 00    	jne    0xc9f07
   c9d90:	8b 44 24 0c          	mov    eax,DWORD PTR [esp+0xc]
   c9d94:	39 f0                	cmp    eax,esi
   c9d96:	0f 85 6b 01 00 00    	jne    0xc9f07
   c9d9c:	83 f8 24             	cmp    eax,0x24
   c9d9f:	0f 83 62 01 00 00    	jae    0xc9f07
   c9da5:	89 6c 24 20          	mov    DWORD PTR [esp+0x20],ebp
   c9da9:	89 d9                	mov    ecx,ebx
   c9dab:	89 fa                	mov    edx,edi
   c9dad:	e8 0e 7f fc ff       	call   0x91cc0
   c9db2:	85 c0                	test   eax,eax
   c9db4:	b8 ff ff ff ff       	mov    eax,0xffffffff
   c9db9:	8b 5c 24 08          	mov    ebx,DWORD PTR [esp+0x8]
   c9dbd:	0f 84 49 01 00 00    	je     0xc9f0c
   c9dc3:	4b                   	dec    ebx
   c9dc4:	0f 85 23 fe ff ff    	jne    0xc9bed
   c9dca:	c7 05 40 2a d4 00 ff 	mov    DWORD PTR ds:0xd42a40,0xffffffff
   c9dd1:	ff ff ff 
   c9dd4:	e9 38 01 00 00       	jmp    0xc9f11
   c9dd9:	a1 40 2a d4 00       	mov    eax,ds:0xd42a40
   c9dde:	c3                   	ret
   c9ddf:	b8 04 00 00 00       	mov    eax,0x4
   c9de4:	e9 23 01 00 00       	jmp    0xc9f0c
   c9de9:	8b 5c 13 28          	mov    ebx,DWORD PTR [ebx+edx*1+0x28]
   c9ded:	85 db                	test   ebx,ebx
   c9def:	0f 84 c8 00 00 00    	je     0xc9ebd
   c9df5:	8b 34 24             	mov    esi,DWORD PTR [esp]
   c9df8:	8b 3d 28 2a d4 00    	mov    edi,DWORD PTR ds:0xd42a28
   c9dfe:	8d 54 24 0c          	lea    edx,[esp+0xc]