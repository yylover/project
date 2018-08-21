main.go:0:0: open main.go: no such file or directory
"".array STEXT size=175 args=0x2000 locals=0x2008
	0x0000 00000 (slice.go:9)	TEXT	"".array(SB), $8200-8192
	0x0000 00000 (slice.go:9)	MOVQ	(TLS), CX
	0x0009 00009 (slice.go:9)	MOVQ	16(CX), SI
	0x000d 00013 (slice.go:9)	CMPQ	SI, $-1314
	0x0014 00020 (slice.go:9)	JEQ	165
	0x001a 00026 (slice.go:9)	LEAQ	880(SP), AX
	0x0022 00034 (slice.go:9)	SUBQ	SI, AX
	0x0025 00037 (slice.go:9)	CMPQ	AX, $8952
	0x002b 00043 (slice.go:9)	JLS	165
	0x002d 00045 (slice.go:9)	SUBQ	$8200, SP
	0x0034 00052 (slice.go:9)	MOVQ	BP, 8192(SP)
	0x003c 00060 (slice.go:9)	LEAQ	8192(SP), BP
	0x0044 00068 (slice.go:9)	FUNCDATA	$0, gclocals·36e1c0ff78aeb76ca958402c76bd10b4(SB)
	0x0044 00068 (slice.go:9)	FUNCDATA	$1, gclocals·33cdeccccebe80329f1fdbee7f5874cb(SB)
	0x0044 00068 (slice.go:9)	LEAQ	"".~r0+8208(SP), DI
	0x004c 00076 (slice.go:9)	MOVL	$1024, CX
	0x0051 00081 (slice.go:9)	MOVL	$0, AX
	0x0053 00083 (slice.go:9)	REP
	0x0054 00084 (slice.go:9)	STOSQ
	0x0056 00086 (slice.go:10)	LEAQ	"".d(SP), DI
	0x005a 00090 (slice.go:10)	MOVL	$1024, CX
	0x005f 00095 (slice.go:10)	REP
	0x0060 00096 (slice.go:10)	STOSQ
	0x0062 00098 (slice.go:10)	MOVL	$0, AX
	0x0064 00100 (slice.go:12)	JMP	121
	0x0066 00102 (slice.go:12)	MOVQ	AX, DX
	0x0069 00105 (slice.go:13)	SHLQ	$3, AX
	0x006d 00109 (slice.go:13)	MOVQ	$1, "".d(SP)(AX*1)
	0x0075 00117 (slice.go:12)	LEAQ	1(DX), AX
	0x0079 00121 (slice.go:12)	CMPQ	AX, $1024
	0x007f 00127 (slice.go:12)	JLT	102
	0x0081 00129 (slice.go:16)	LEAQ	"".~r0+8208(SP), DI
	0x0089 00137 (slice.go:16)	LEAQ	"".d(SP), SI
	0x008d 00141 (slice.go:16)	MOVL	$1024, CX
	0x0092 00146 (slice.go:16)	REP
	0x0093 00147 (slice.go:16)	MOVSQ
	0x0095 00149 (slice.go:16)	MOVQ	8192(SP), BP
	0x009d 00157 (slice.go:16)	ADDQ	$8200, SP
	0x00a4 00164 (slice.go:16)	RET
	0x00a5 00165 (slice.go:16)	NOP
	0x00a5 00165 (slice.go:9)	PCDATA	$0, $-1
	0x00a5 00165 (slice.go:9)	CALL	runtime.morestack_noctxt(SB)
	0x00aa 00170 (slice.go:9)	JMP	0
	0x0000 65 48 8b 0c 25 00 00 00 00 48 8b 71 10 48 81 fe  eH..%....H.q.H..
	0x0010 de fa ff ff 0f 84 8b 00 00 00 48 8d 84 24 70 03  ..........H..$p.
	0x0020 00 00 48 29 f0 48 3d f8 22 00 00 76 78 48 81 ec  ..H).H=."..vxH..
	0x0030 08 20 00 00 48 89 ac 24 00 20 00 00 48 8d ac 24  . ..H..$. ..H..$
	0x0040 00 20 00 00 48 8d bc 24 10 20 00 00 b9 00 04 00  . ..H..$. ......
	0x0050 00 31 c0 f3 48 ab 48 8d 3c 24 b9 00 04 00 00 f3  .1..H.H.<$......
	0x0060 48 ab 31 c0 eb 13 48 89 c2 48 c1 e0 03 48 c7 04  H.1...H..H...H..
	0x0070 04 01 00 00 00 48 8d 42 01 48 3d 00 04 00 00 7c  .....H.B.H=....|
	0x0080 e5 48 8d bc 24 10 20 00 00 48 8d 34 24 b9 00 04  .H..$. ..H.4$...
	0x0090 00 00 f3 48 a5 48 8b ac 24 00 20 00 00 48 81 c4  ...H.H..$. ..H..
	0x00a0 08 20 00 00 c3 e8 00 00 00 00 e9 51 ff ff ff     . .........Q...
	rel 5+4 t=16 TLS+0
	rel 166+4 t=8 runtime.morestack_noctxt+0
"".slice STEXT size=133 args=0x18 locals=0x38
	0x0000 00000 (slice.go:19)	TEXT	"".slice(SB), $56-24
	0x0000 00000 (slice.go:19)	MOVQ	(TLS), CX
	0x0009 00009 (slice.go:19)	CMPQ	SP, 16(CX)
	0x000d 00013 (slice.go:19)	JLS	123
	0x000f 00015 (slice.go:19)	SUBQ	$56, SP
	0x0013 00019 (slice.go:19)	MOVQ	BP, 48(SP)
	0x0018 00024 (slice.go:19)	LEAQ	48(SP), BP
	0x001d 00029 (slice.go:19)	FUNCDATA	$0, gclocals·54241e171da8af6ae173d69da0236748(SB)
	0x001d 00029 (slice.go:19)	FUNCDATA	$1, gclocals·33cdeccccebe80329f1fdbee7f5874cb(SB)
	0x001d 00029 (slice.go:19)	LEAQ	type.int(SB), AX
	0x0024 00036 (slice.go:20)	MOVQ	AX, (SP)
	0x0028 00040 (slice.go:20)	MOVQ	$1024, 8(SP)
	0x0031 00049 (slice.go:20)	MOVQ	$1024, 16(SP)
	0x003a 00058 (slice.go:20)	PCDATA	$0, $0
	0x003a 00058 (slice.go:20)	CALL	runtime.makeslice(SB)
	0x003f 00063 (slice.go:20)	MOVQ	40(SP), AX
	0x0044 00068 (slice.go:20)	MOVQ	32(SP), CX
	0x0049 00073 (slice.go:20)	MOVQ	24(SP), DX
	0x004e 00078 (slice.go:20)	MOVL	$0, BX
	0x0050 00080 (slice.go:22)	JMP	93
	0x0052 00082 (slice.go:23)	MOVQ	$1, (DX)(BX*8)
	0x005a 00090 (slice.go:22)	INCQ	BX
	0x005d 00093 (slice.go:22)	CMPQ	BX, CX
	0x0060 00096 (slice.go:22)	JLT	82
	0x0062 00098 (slice.go:26)	MOVQ	DX, "".~r0+64(SP)
	0x0067 00103 (slice.go:26)	MOVQ	CX, "".~r0+72(SP)
	0x006c 00108 (slice.go:26)	MOVQ	AX, "".~r0+80(SP)
	0x0071 00113 (slice.go:26)	MOVQ	48(SP), BP
	0x0076 00118 (slice.go:26)	ADDQ	$56, SP
	0x007a 00122 (slice.go:26)	RET
	0x007b 00123 (slice.go:26)	NOP
	0x007b 00123 (slice.go:19)	PCDATA	$0, $-1
	0x007b 00123 (slice.go:19)	CALL	runtime.morestack_noctxt(SB)
	0x0080 00128 (slice.go:19)	JMP	0
	0x0000 65 48 8b 0c 25 00 00 00 00 48 3b 61 10 76 6c 48  eH..%....H;a.vlH
	0x0010 83 ec 38 48 89 6c 24 30 48 8d 6c 24 30 48 8d 05  ..8H.l$0H.l$0H..
	0x0020 00 00 00 00 48 89 04 24 48 c7 44 24 08 00 04 00  ....H..$H.D$....
	0x0030 00 48 c7 44 24 10 00 04 00 00 e8 00 00 00 00 48  .H.D$..........H
	0x0040 8b 44 24 28 48 8b 4c 24 20 48 8b 54 24 18 31 db  .D$(H.L$ H.T$.1.
	0x0050 eb 0b 48 c7 04 da 01 00 00 00 48 ff c3 48 39 cb  ..H.......H..H9.
	0x0060 7c f0 48 89 54 24 40 48 89 4c 24 48 48 89 44 24  |.H.T$@H.L$HH.D$
	0x0070 50 48 8b 6c 24 30 48 83 c4 38 c3 e8 00 00 00 00  PH.l$0H..8......
	0x0080 e9 7b ff ff ff                                   .{...
	rel 5+4 t=16 TLS+0
	rel 32+4 t=15 type.int+0
	rel 59+4 t=8 runtime.makeslice+0
	rel 124+4 t=8 runtime.morestack_noctxt+0
"".main STEXT size=393 args=0x0 locals=0x4040
	0x0000 00000 (slice.go:29)	TEXT	"".main(SB), $16448-0
	0x0000 00000 (slice.go:29)	MOVQ	(TLS), CX
	0x0009 00009 (slice.go:29)	MOVQ	16(CX), SI
	0x000d 00013 (slice.go:29)	CMPQ	SI, $-1314
	0x0014 00020 (slice.go:29)	JEQ	383
	0x001a 00026 (slice.go:29)	LEAQ	880(SP), AX
	0x0022 00034 (slice.go:29)	SUBQ	SI, AX
	0x0025 00037 (slice.go:29)	CMPQ	AX, $17200
	0x002b 00043 (slice.go:29)	JLS	383
	0x0031 00049 (slice.go:29)	SUBQ	$16448, SP
	0x0038 00056 (slice.go:29)	MOVQ	BP, 16440(SP)
	0x0040 00064 (slice.go:29)	LEAQ	16440(SP), BP
	0x0048 00072 (slice.go:29)	FUNCDATA	$0, gclocals·7d2d5fca80364273fb07d5820a76fef4(SB)
	0x0048 00072 (slice.go:29)	FUNCDATA	$1, gclocals·141d4a14b5a868784d1b250c6add626a(SB)
	0x0048 00072 (slice.go:30)	PCDATA	$0, $0
	0x0048 00072 (slice.go:30)	CALL	"".array(SB)
	0x004d 00077 (slice.go:30)	LEAQ	""..autotmp_1+8192(SP), DI
	0x0055 00085 (slice.go:30)	MOVQ	SP, SI
	0x0058 00088 (slice.go:30)	MOVL	$1024, CX
	0x005d 00093 (slice.go:30)	REP
	0x005e 00094 (slice.go:30)	MOVSQ
	0x0060 00096 (slice.go:30)	MOVQ	$0, ""..autotmp_0+16400(SP)
	0x006c 00108 (slice.go:30)	MOVQ	$0, ""..autotmp_0+16408(SP)
	0x0078 00120 (slice.go:30)	LEAQ	type.[1024]int(SB), AX
	0x007f 00127 (slice.go:30)	MOVQ	AX, (SP)
	0x0083 00131 (slice.go:30)	LEAQ	""..autotmp_1+8192(SP), AX
	0x008b 00139 (slice.go:30)	MOVQ	AX, 8(SP)
	0x0090 00144 (slice.go:30)	PCDATA	$0, $1
	0x0090 00144 (slice.go:30)	CALL	runtime.convT2Enoptr(SB)
	0x0095 00149 (slice.go:30)	MOVQ	16(SP), AX
	0x009a 00154 (slice.go:30)	MOVQ	24(SP), CX
	0x009f 00159 (slice.go:30)	MOVQ	AX, ""..autotmp_0+16400(SP)
	0x00a7 00167 (slice.go:30)	MOVQ	CX, ""..autotmp_0+16408(SP)
	0x00af 00175 (slice.go:30)	LEAQ	""..autotmp_0+16400(SP), AX
	0x00b7 00183 (slice.go:30)	MOVQ	AX, (SP)
	0x00bb 00187 (slice.go:30)	MOVQ	$1, 8(SP)
	0x00c4 00196 (slice.go:30)	MOVQ	$1, 16(SP)
	0x00cd 00205 (slice.go:30)	PCDATA	$0, $1
	0x00cd 00205 (slice.go:30)	CALL	fmt.Println(SB)
	0x00d2 00210 (slice.go:31)	PCDATA	$0, $0
	0x00d2 00210 (slice.go:31)	CALL	"".slice(SB)
	0x00d7 00215 (slice.go:31)	MOVQ	8(SP), AX
	0x00dc 00220 (slice.go:31)	MOVQ	(SP), CX
	0x00e0 00224 (slice.go:31)	MOVQ	16(SP), DX
	0x00e5 00229 (slice.go:31)	MOVQ	CX, ""..autotmp_3+16416(SP)
	0x00ed 00237 (slice.go:31)	MOVQ	AX, ""..autotmp_3+16424(SP)
	0x00f5 00245 (slice.go:31)	MOVQ	DX, ""..autotmp_3+16432(SP)
	0x00fd 00253 (slice.go:31)	MOVQ	$0, ""..autotmp_2+16384(SP)
	0x0109 00265 (slice.go:31)	MOVQ	$0, ""..autotmp_2+16392(SP)
	0x0115 00277 (slice.go:31)	LEAQ	type.[]int(SB), AX
	0x011c 00284 (slice.go:31)	MOVQ	AX, (SP)
	0x0120 00288 (slice.go:31)	LEAQ	""..autotmp_3+16416(SP), AX
	0x0128 00296 (slice.go:31)	MOVQ	AX, 8(SP)
	0x012d 00301 (slice.go:31)	PCDATA	$0, $2
	0x012d 00301 (slice.go:31)	CALL	runtime.convT2Eslice(SB)
	0x0132 00306 (slice.go:31)	MOVQ	16(SP), AX
	0x0137 00311 (slice.go:31)	MOVQ	24(SP), CX
	0x013c 00316 (slice.go:31)	MOVQ	AX, ""..autotmp_2+16384(SP)
	0x0144 00324 (slice.go:31)	MOVQ	CX, ""..autotmp_2+16392(SP)
	0x014c 00332 (slice.go:31)	LEAQ	""..autotmp_2+16384(SP), AX
	0x0154 00340 (slice.go:31)	MOVQ	AX, (SP)
	0x0158 00344 (slice.go:31)	MOVQ	$1, 8(SP)
	0x0161 00353 (slice.go:31)	MOVQ	$1, 16(SP)
	0x016a 00362 (slice.go:31)	PCDATA	$0, $2
	0x016a 00362 (slice.go:31)	CALL	fmt.Println(SB)
	0x016f 00367 (slice.go:32)	MOVQ	16440(SP), BP
	0x0177 00375 (slice.go:32)	ADDQ	$16448, SP
	0x017e 00382 (slice.go:32)	RET
	0x017f 00383 (slice.go:32)	NOP
	0x017f 00383 (slice.go:29)	PCDATA	$0, $-1
	0x017f 00383 (slice.go:29)	CALL	runtime.morestack_noctxt(SB)
	0x0184 00388 (slice.go:29)	JMP	0
	0x0000 65 48 8b 0c 25 00 00 00 00 48 8b 71 10 48 81 fe  eH..%....H.q.H..
	0x0010 de fa ff ff 0f 84 65 01 00 00 48 8d 84 24 70 03  ......e...H..$p.
	0x0020 00 00 48 29 f0 48 3d 30 43 00 00 0f 86 4e 01 00  ..H).H=0C....N..
	0x0030 00 48 81 ec 40 40 00 00 48 89 ac 24 38 40 00 00  .H..@@..H..$8@..
	0x0040 48 8d ac 24 38 40 00 00 e8 00 00 00 00 48 8d bc  H..$8@.......H..
	0x0050 24 00 20 00 00 48 89 e6 b9 00 04 00 00 f3 48 a5  $. ..H........H.
	0x0060 48 c7 84 24 10 40 00 00 00 00 00 00 48 c7 84 24  H..$.@......H..$
	0x0070 18 40 00 00 00 00 00 00 48 8d 05 00 00 00 00 48  .@......H......H
	0x0080 89 04 24 48 8d 84 24 00 20 00 00 48 89 44 24 08  ..$H..$. ..H.D$.
	0x0090 e8 00 00 00 00 48 8b 44 24 10 48 8b 4c 24 18 48  .....H.D$.H.L$.H
	0x00a0 89 84 24 10 40 00 00 48 89 8c 24 18 40 00 00 48  ..$.@..H..$.@..H
	0x00b0 8d 84 24 10 40 00 00 48 89 04 24 48 c7 44 24 08  ..$.@..H..$H.D$.
	0x00c0 01 00 00 00 48 c7 44 24 10 01 00 00 00 e8 00 00  ....H.D$........
	0x00d0 00 00 e8 00 00 00 00 48 8b 44 24 08 48 8b 0c 24  .......H.D$.H..$
	0x00e0 48 8b 54 24 10 48 89 8c 24 20 40 00 00 48 89 84  H.T$.H..$ @..H..
	0x00f0 24 28 40 00 00 48 89 94 24 30 40 00 00 48 c7 84  $(@..H..$0@..H..
	0x0100 24 00 40 00 00 00 00 00 00 48 c7 84 24 08 40 00  $.@......H..$.@.
	0x0110 00 00 00 00 00 48 8d 05 00 00 00 00 48 89 04 24  .....H......H..$
	0x0120 48 8d 84 24 20 40 00 00 48 89 44 24 08 e8 00 00  H..$ @..H.D$....
	0x0130 00 00 48 8b 44 24 10 48 8b 4c 24 18 48 89 84 24  ..H.D$.H.L$.H..$
	0x0140 00 40 00 00 48 89 8c 24 08 40 00 00 48 8d 84 24  .@..H..$.@..H..$
	0x0150 00 40 00 00 48 89 04 24 48 c7 44 24 08 01 00 00  .@..H..$H.D$....
	0x0160 00 48 c7 44 24 10 01 00 00 00 e8 00 00 00 00 48  .H.D$..........H
	0x0170 8b ac 24 38 40 00 00 48 81 c4 40 40 00 00 c3 e8  ..$8@..H..@@....
	0x0180 00 00 00 00 e9 77 fe ff ff                       .....w...
	rel 5+4 t=16 TLS+0
	rel 73+4 t=8 "".array+0
	rel 123+4 t=15 type.[1024]int+0
	rel 145+4 t=8 runtime.convT2Enoptr+0
	rel 206+4 t=8 fmt.Println+0
	rel 211+4 t=8 "".slice+0
	rel 280+4 t=15 type.[]int+0
	rel 302+4 t=8 runtime.convT2Eslice+0
	rel 363+4 t=8 fmt.Println+0
	rel 384+4 t=8 runtime.morestack_noctxt+0
"".init STEXT size=91 args=0x0 locals=0x8
	0x0000 00000 (<autogenerated>:1)	TEXT	"".init(SB), $8-0
	0x0000 00000 (<autogenerated>:1)	MOVQ	(TLS), CX
	0x0009 00009 (<autogenerated>:1)	CMPQ	SP, 16(CX)
	0x000d 00013 (<autogenerated>:1)	JLS	84
	0x000f 00015 (<autogenerated>:1)	SUBQ	$8, SP
	0x0013 00019 (<autogenerated>:1)	MOVQ	BP, (SP)
	0x0017 00023 (<autogenerated>:1)	LEAQ	(SP), BP
	0x001b 00027 (<autogenerated>:1)	FUNCDATA	$0, gclocals·33cdeccccebe80329f1fdbee7f5874cb(SB)
	0x001b 00027 (<autogenerated>:1)	FUNCDATA	$1, gclocals·33cdeccccebe80329f1fdbee7f5874cb(SB)
	0x001b 00027 (<autogenerated>:1)	MOVBLZX	"".initdone·(SB), AX
	0x0022 00034 (<autogenerated>:1)	CMPB	AL, $1
	0x0024 00036 (<autogenerated>:1)	JLS	47
	0x0026 00038 (<autogenerated>:1)	MOVQ	(SP), BP
	0x002a 00042 (<autogenerated>:1)	ADDQ	$8, SP
	0x002e 00046 (<autogenerated>:1)	RET
	0x002f 00047 (<autogenerated>:1)	JNE	56
	0x0031 00049 (<autogenerated>:1)	PCDATA	$0, $0
	0x0031 00049 (<autogenerated>:1)	CALL	runtime.throwinit(SB)
	0x0036 00054 (<autogenerated>:1)	UNDEF
	0x0038 00056 (<autogenerated>:1)	MOVB	$1, "".initdone·(SB)
	0x003f 00063 (<autogenerated>:1)	PCDATA	$0, $0
	0x003f 00063 (<autogenerated>:1)	CALL	fmt.init(SB)
	0x0044 00068 (<autogenerated>:1)	MOVB	$2, "".initdone·(SB)
	0x004b 00075 (<autogenerated>:1)	MOVQ	(SP), BP
	0x004f 00079 (<autogenerated>:1)	ADDQ	$8, SP
	0x0053 00083 (<autogenerated>:1)	RET
	0x0054 00084 (<autogenerated>:1)	NOP
	0x0054 00084 (<autogenerated>:1)	PCDATA	$0, $-1
	0x0054 00084 (<autogenerated>:1)	CALL	runtime.morestack_noctxt(SB)
	0x0059 00089 (<autogenerated>:1)	JMP	0
	0x0000 65 48 8b 0c 25 00 00 00 00 48 3b 61 10 76 45 48  eH..%....H;a.vEH
	0x0010 83 ec 08 48 89 2c 24 48 8d 2c 24 0f b6 05 00 00  ...H.,$H.,$.....
	0x0020 00 00 3c 01 76 09 48 8b 2c 24 48 83 c4 08 c3 75  ..<.v.H.,$H....u
	0x0030 07 e8 00 00 00 00 0f 0b c6 05 00 00 00 00 01 e8  ................
	0x0040 00 00 00 00 c6 05 00 00 00 00 02 48 8b 2c 24 48  ...........H.,$H
	0x0050 83 c4 08 c3 e8 00 00 00 00 eb a5                 ...........
	rel 5+4 t=16 TLS+0
	rel 30+4 t=15 "".initdone·+0
	rel 50+4 t=8 runtime.throwinit+0
	rel 58+4 t=15 "".initdone·+-1
	rel 64+4 t=8 fmt.init+0
	rel 70+4 t=15 "".initdone·+-1
	rel 85+4 t=8 runtime.morestack_noctxt+0
go.info."".array SDWARFINFO size=55
	0x0000 02 22 22 2e 61 72 72 61 79 00 00 00 00 00 00 00  ."".array.......
	0x0010 00 00 00 00 00 00 00 00 00 00 01 9c 01 04 64 00  ..............d.
	0x0020 06 9c 11 f0 bf 7f 22 00 00 00 00 05 7e 72 30 00  ......".....~r0.
	0x0030 01 9c 00 00 00 00 00                             .......
	rel 10+8 t=1 "".array+0
	rel 18+8 t=1 "".array+175
	rel 39+4 t=28 go.info.[1024]int+0
	rel 50+4 t=28 go.info.[1024]int+0
go.range."".array SDWARFRANGE size=0
go.info."".slice SDWARFINFO size=41
	0x0000 02 22 22 2e 73 6c 69 63 65 00 00 00 00 00 00 00  ."".slice.......
	0x0010 00 00 00 00 00 00 00 00 00 00 01 9c 01 05 7e 72  ..............~r
	0x0020 30 00 01 9c 00 00 00 00 00                       0........
	rel 10+8 t=1 "".slice+0
	rel 18+8 t=1 "".slice+133
	rel 36+4 t=28 go.info.[]int+0
go.range."".slice SDWARFRANGE size=0
go.info."".main SDWARFINFO size=29
	0x0000 02 22 22 2e 6d 61 69 6e 00 00 00 00 00 00 00 00  ."".main........
	0x0010 00 00 00 00 00 00 00 00 00 01 9c 01 00           .............
	rel 9+8 t=1 "".main+0
	rel 17+8 t=1 "".main+393
go.range."".main SDWARFRANGE size=0
go.info."".init SDWARFINFO size=29
	0x0000 02 22 22 2e 69 6e 69 74 00 00 00 00 00 00 00 00  ."".init........
	0x0010 00 00 00 00 00 00 00 00 00 01 9c 01 00           .............
	rel 9+8 t=1 "".init+0
	rel 17+8 t=1 "".init+91
go.range."".init SDWARFRANGE size=0
"".initdone· SNOPTRBSS size=1
runtime.gcbits.01 SRODATA dupok size=1
	0x0000 01                                               .
type..namedata.*[]int- SRODATA dupok size=9
	0x0000 00 00 06 2a 5b 5d 69 6e 74                       ...*[]int
type.*[]int SRODATA dupok size=56
	0x0000 08 00 00 00 00 00 00 00 08 00 00 00 00 00 00 00  ................
	0x0010 1b 31 52 88 00 08 08 36 00 00 00 00 00 00 00 00  .1R....6........
	0x0020 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0030 00 00 00 00 00 00 00 00                          ........
	rel 24+8 t=1 runtime.algarray+80
	rel 32+8 t=1 runtime.gcbits.01+0
	rel 40+4 t=5 type..namedata.*[]int-+0
	rel 48+8 t=1 type.[]int+0
type.[]int SRODATA dupok size=56
	0x0000 18 00 00 00 00 00 00 00 08 00 00 00 00 00 00 00  ................
	0x0010 8e 66 f9 1b 02 08 08 17 00 00 00 00 00 00 00 00  .f..............
	0x0020 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0030 00 00 00 00 00 00 00 00                          ........
	rel 24+8 t=1 runtime.algarray+0
	rel 32+8 t=1 runtime.gcbits.01+0
	rel 40+4 t=5 type..namedata.*[]int-+0
	rel 44+4 t=6 type.*[]int+0
	rel 48+8 t=1 type.int+0
type..hashfunc8192 SRODATA dupok size=16
	0x0000 00 00 00 00 00 00 00 00 00 20 00 00 00 00 00 00  ......... ......
	rel 0+8 t=1 runtime.memhash_varlen+0
type..eqfunc8192 SRODATA dupok size=16
	0x0000 00 00 00 00 00 00 00 00 00 20 00 00 00 00 00 00  ......... ......
	rel 0+8 t=1 runtime.memequal_varlen+0
type..alg8192 SRODATA dupok size=16
	0x0000 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	rel 0+8 t=1 type..hashfunc8192+0
	rel 8+8 t=1 type..eqfunc8192+0
type..namedata.*[1024]int- SRODATA dupok size=13
	0x0000 00 00 0a 2a 5b 31 30 32 34 5d 69 6e 74           ...*[1024]int
type.*[1024]int SRODATA dupok size=56
	0x0000 08 00 00 00 00 00 00 00 08 00 00 00 00 00 00 00  ................
	0x0010 7d 0d 36 c7 00 08 08 36 00 00 00 00 00 00 00 00  }.6....6........
	0x0020 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0030 00 00 00 00 00 00 00 00                          ........
	rel 24+8 t=1 runtime.algarray+80
	rel 32+8 t=1 runtime.gcbits.01+0
	rel 40+4 t=5 type..namedata.*[1024]int-+0
	rel 48+8 t=1 type.[1024]int+0
runtime.gcbits. SRODATA dupok size=0
type.[1024]int SRODATA dupok size=72
	0x0000 00 20 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . ..............
	0x0010 cd 1e 4d 48 02 08 08 91 00 00 00 00 00 00 00 00  ..MH............
	0x0020 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0030 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0040 00 04 00 00 00 00 00 00                          ........
	rel 24+8 t=1 type..alg8192+0
	rel 32+8 t=1 runtime.gcbits.+0
	rel 40+4 t=5 type..namedata.*[1024]int-+0
	rel 44+4 t=6 type.*[1024]int+0
	rel 48+8 t=1 type.int+0
	rel 56+8 t=1 type.[]int+0
type..namedata.*interface {}- SRODATA dupok size=16
	0x0000 00 00 0d 2a 69 6e 74 65 72 66 61 63 65 20 7b 7d  ...*interface {}
type.*interface {} SRODATA dupok size=56
	0x0000 08 00 00 00 00 00 00 00 08 00 00 00 00 00 00 00  ................
	0x0010 4f 0f 96 9d 00 08 08 36 00 00 00 00 00 00 00 00  O......6........
	0x0020 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0030 00 00 00 00 00 00 00 00                          ........
	rel 24+8 t=1 runtime.algarray+80
	rel 32+8 t=1 runtime.gcbits.01+0
	rel 40+4 t=5 type..namedata.*interface {}-+0
	rel 48+8 t=1 type.interface {}+0
runtime.gcbits.03 SRODATA dupok size=1
	0x0000 03                                               .
type.interface {} SRODATA dupok size=80
	0x0000 10 00 00 00 00 00 00 00 10 00 00 00 00 00 00 00  ................
	0x0010 e7 57 a0 18 02 08 08 14 00 00 00 00 00 00 00 00  .W..............
	0x0020 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0030 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0040 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	rel 24+8 t=1 runtime.algarray+144
	rel 32+8 t=1 runtime.gcbits.03+0
	rel 40+4 t=5 type..namedata.*interface {}-+0
	rel 44+4 t=6 type.*interface {}+0
	rel 56+8 t=1 type.interface {}+80
type..namedata.*[]interface {}- SRODATA dupok size=18
	0x0000 00 00 0f 2a 5b 5d 69 6e 74 65 72 66 61 63 65 20  ...*[]interface 
	0x0010 7b 7d                                            {}
type.*[]interface {} SRODATA dupok size=56
	0x0000 08 00 00 00 00 00 00 00 08 00 00 00 00 00 00 00  ................
	0x0010 f3 04 9a e7 00 08 08 36 00 00 00 00 00 00 00 00  .......6........
	0x0020 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0030 00 00 00 00 00 00 00 00                          ........
	rel 24+8 t=1 runtime.algarray+80
	rel 32+8 t=1 runtime.gcbits.01+0
	rel 40+4 t=5 type..namedata.*[]interface {}-+0
	rel 48+8 t=1 type.[]interface {}+0
type.[]interface {} SRODATA dupok size=56
	0x0000 18 00 00 00 00 00 00 00 08 00 00 00 00 00 00 00  ................
	0x0010 70 93 ea 2f 02 08 08 17 00 00 00 00 00 00 00 00  p../............
	0x0020 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0030 00 00 00 00 00 00 00 00                          ........
	rel 24+8 t=1 runtime.algarray+0
	rel 32+8 t=1 runtime.gcbits.01+0
	rel 40+4 t=5 type..namedata.*[]interface {}-+0
	rel 44+4 t=6 type.*[]interface {}+0
	rel 48+8 t=1 type.interface {}+0
type..namedata.*[1]interface {}- SRODATA dupok size=19
	0x0000 00 00 10 2a 5b 31 5d 69 6e 74 65 72 66 61 63 65  ...*[1]interface
	0x0010 20 7b 7d                                          {}
type.*[1]interface {} SRODATA dupok size=56
	0x0000 08 00 00 00 00 00 00 00 08 00 00 00 00 00 00 00  ................
	0x0010 bf 03 a8 35 00 08 08 36 00 00 00 00 00 00 00 00  ...5...6........
	0x0020 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0030 00 00 00 00 00 00 00 00                          ........
	rel 24+8 t=1 runtime.algarray+80
	rel 32+8 t=1 runtime.gcbits.01+0
	rel 40+4 t=5 type..namedata.*[1]interface {}-+0
	rel 48+8 t=1 type.[1]interface {}+0
type.[1]interface {} SRODATA dupok size=72
	0x0000 10 00 00 00 00 00 00 00 10 00 00 00 00 00 00 00  ................
	0x0010 50 91 5b fa 02 08 08 11 00 00 00 00 00 00 00 00  P.[.............
	0x0020 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0030 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0040 01 00 00 00 00 00 00 00                          ........
	rel 24+8 t=1 runtime.algarray+144
	rel 32+8 t=1 runtime.gcbits.03+0
	rel 40+4 t=5 type..namedata.*[1]interface {}-+0
	rel 44+4 t=6 type.*[1]interface {}+0
	rel 48+8 t=1 type.interface {}+0
	rel 56+8 t=1 type.[]interface {}+0
type..importpath.fmt. SRODATA dupok size=6
	0x0000 00 00 03 66 6d 74                                ...fmt
gclocals·36e1c0ff78aeb76ca958402c76bd10b4 SRODATA dupok size=136
	0x0000 01 00 00 00 00 04 00 00 00 00 00 00 00 00 00 00  ................
	0x0010 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0020 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0030 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0040 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0050 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0060 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0070 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
	0x0080 00 00 00 00 00 00 00 00                          ........
gclocals·33cdeccccebe80329f1fdbee7f5874cb SRODATA dupok size=8
	0x0000 01 00 00 00 00 00 00 00                          ........
gclocals·54241e171da8af6ae173d69da0236748 SRODATA dupok size=9
	0x0000 01 00 00 00 03 00 00 00 00                       .........
gclocals·7d2d5fca80364273fb07d5820a76fef4 SRODATA dupok size=8
	0x0000 03 00 00 00 00 00 00 00                          ........
gclocals·141d4a14b5a868784d1b250c6add626a SRODATA dupok size=11
	0x0000 03 00 00 00 07 00 00 00 00 0c 13                 ...........
