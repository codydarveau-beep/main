82870 push ebp
82871 mov ebp, esp
82873 push ebx
82874 push edi
82875 push esi
82876 and esp, 0xfffffff8
82879 sub esp, 0x30
8287c movss xmm1, dword ptr [ebp + 0x10]
82881 movss xmm2, dword ptr [ebp + 0xc]
82886 mov eax, dword ptr [ebp + 8]
82889 cmp eax, 7
8288c jg 0x8289c
8288e mov esi, eax
82890 or esi, edx
82892 js 0x8289c
82894 lea esi, [eax + edx*8]
82897 cmp esi, dword ptr [ecx + 0xc]
8289a jb 0x828a0
8289c xor edx, edx
8289e xor eax, eax
828a0 mov ebx, dword ptr [ecx + 0x20]
828a3 lea eax, [eax + edx*8]
828a6 lea edi, [eax + eax*2]
828a9 xorps xmm0, xmm0
828ac ucomiss xmm1, xmm0
828af maxss xmm0, xmm2
828b3 jbe 0x8290b
828b5 divss xmm0, xmm1
828b9 mov eax, dword ptr [ebx + edi*4 + 4]
828bd mov dword ptr [esp + 0x10], eax
828c1 mov dword ptr [esp + 0x14], 0
828c9 fild qword ptr [esp + 0x10]
828cd fstp dword ptr [esp + 4]
828d1 mulss xmm0, dword ptr [esp + 4]
828d7 cvttss2si edx, xmm0
828db mov dword ptr [esp], ecx
828de mov ecx, edi
828e0 mov edi, ebx
828e2 mov ebx, edx
828e4 sar ebx, 0x1f
828e7 subss xmm0, dword ptr [0x74a300]
828ef cvttss2si esi, xmm0
828f3 and esi, ebx
828f5 mov ebx, edi
828f7 mov edi, ecx
828f9 mov ecx, dword ptr [esp]
828fc or esi, edx
828fe cmp eax, esi
82900 lea edx, [eax - 1]
82903 cmova edx, esi
82906 jmp 0x829bc
8290b cmp dword ptr [ebp + 0x14], 0
8290f je 0x82958
82911 mulss xmm0, dword ptr [0x74a288]
82919 mov eax, dword ptr [ebx + edi*4 + 8]
8291d mov dword ptr [esp + 0x20], eax
82921 mov dword ptr [esp + 0x24], 0
82929 fild qword ptr [esp + 0x20]
8292d fstp dword ptr [esp + 0xc]
82931 divss xmm0, dword ptr [esp + 0xc]
82937 cvttss2si edx, xmm0
8293b mov esi, edx
8293d sar esi, 0x1f
82940 subss xmm0, dword ptr [0x74a300]
82948 cvttss2si eax, xmm0
8294c and eax, esi
8294e or eax, edx
82950 xor edx, edx
82952 div dword ptr [ebx + edi*4 + 4]
82956 jmp 0x829bc
82958 mov eax, dword ptr [ecx + 0x3c]
8295b cmp eax, 0x3dcac8
82960 je 0x8296b
82962 xor edx, edx
82964 cmp eax, 0x3dcae4
82969 jne 0x829bc
8296b mulss xmm0, dword ptr [0x74a288]
82973 mov eax, dword ptr [ebx + edi*4 + 4]
82977 mov edx, dword ptr [ebx + edi*4 + 8]
8297b mov dword ptr [esp + 0x18], edx
8297f mov dword ptr [esp + 0x1c], 0
82987 fild qword ptr [esp + 0x18]
8298b fstp dword ptr [esp + 8]
8298f divss xmm0, dword ptr [esp + 8]
82995 cvttss2si edx, xmm0
82999 mov esi, edx
8299b sar esi, 0x1f
8299e subss xmm0, dword ptr [0x74a300]
829a6 mov dword ptr [esp], ebx
829a9 cvttss2si ebx, xmm0
829ad and ebx, esi
829af or ebx, edx
829b1 cmp eax, ebx
829b3 lea edx, [eax - 1]
829b6 cmova edx, ebx
829b9 mov ebx, dword ptr [esp]
829bc mov eax, dword ptr [ebx + edi*4]
829bf shl eax, 2
829c2 add eax, dword ptr [ecx + 0x24]
829c5 mov eax, dword ptr [eax + edx*4]
829c8 mov edx, dword ptr [ecx + 0x48]
829cb test edx, edx
829cd je 0x829e2
829cf lea esi, [eax + eax*2]
829d2 movsx edx, word ptr [edx + esi*4 + 0xa]
829d7 sar edx, 1
829d9 add edx, 0x40
829dc movsx edx, dx
829df mov dword ptr [ecx + 0x14], edx
829e2 lea esp, [ebp - 0xc]
829e5 pop esi
829e6 pop edi
829e7 pop ebx
829e8 pop ebp
829e9 ret 