	.include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020EE6D8
UNK_020EE6D8: ; 0x020EE6D8
	.word 2

	.global UNK_020EE6DC
UNK_020EE6DC: ; 0x020EE6DC
	.word 36

	.global UNK_020EE6E0
UNK_020EE6E0: ; 0x020EE6E0
	.word 0x00, 0x20, FUN_0202B034, FUN_0202B03C
	.word 0x01, 0x23, FUN_0202AC20, FUN_0202AC28

	.global UNK_020EE700
UNK_020EE700: ; 0x020EE700
	.word 0x00, 0x00, FUN_0202376C, FUN_02023770
	.word 0x01, 0x00, FUN_020238C4, FUN_020238C8
	.word 0x02, 0x00, FUN_0206B8A4, FUN_0206B8C0
	.word 0x03, 0x00, FUN_0206EB80, FUN_0206EBA0
	.word 0x04, 0x00, FUN_02046294, FUN_0204629C
	.word 0x05, 0x00, FUN_0204BE14, FUN_0204BE18
	.word 0x06, 0x00, FUN_02034D7C, FUN_02034D98
	.word 0x07, 0x00, FUN_02023D64, FUN_02024378
	.word 0x08, 0x00, FUN_02023C40, FUN_02023C48
	.word 0x09, 0x00, FUN_020254B8, FUN_020254CC
	.word 0x0A, 0x00, FUN_02024E64, FUN_02024E6C
	.word 0x0B, 0x00, FUN_02034D80, FUN_02034D88
	.word 0x0C, 0x00, FUN_02025954, FUN_0202597C
	.word 0x0D, 0x00, FUN_02023AC8, FUN_02023AD8
	.word 0x0E, 0x00, FUN_02026FD8, FUN_02026F60
	.word 0x0F, 0x00, FUN_02025844, FUN_0202584C
	.word 0x10, 0x00, FUN_02028054, FUN_0202805C
	.word 0x11, 0x00, FUN_020286F8, FUN_02028724
	.word 0x12, 0x00, FUN_02028980, FUN_02028994
	.word 0x13, 0x00, FUN_02029A84, FUN_02029A8C
	.word 0x14, 0x00, FUN_02029FB0, FUN_02029FB8
	.word 0x15, 0x00, FUN_02029C58, FUN_02029C60
	.word 0x16, 0x00, FUN_02029EC4, FUN_02029ECC
	.word 0x17, 0x00, FUN_0202A89C, FUN_0202A8A4
	.word 0x18, 0x00, FUN_0202A8F4, FUN_0202A8F8
	.word 0x19, 0x00, FUN_0202A924, FUN_0202A92C
	.word 0x1A, 0x00, FUN_0202ABC8, FUN_0202ABCC
	.word 0x1B, 0x00, FUN_0202B374, FUN_0202B37C
	.word 0x1C, 0x00, FUN_0202B8B0, FUN_0202B8B8
	.word 0x1D, 0x00, FUN_020281E0, FUN_020281E8
	.word 0x1E, 0x00, FUN_02029AE0, FUN_02029AE8
	.word 0x1F, 0x00, FUN_0202AC20, FUN_0202AC28
	.word 0x20, 0x00, FUN_0202BE98, FUN_0202BEA0
	.word 0x21, 0x00, FUN_0202C0E0, FUN_0202C0E4
	.word 0x22, 0x00, FUN_02013B28, FUN_02013B2C
	.word 0x23, 0x01, FUN_0206B178, FUN_0206B16C

	.section .bss

	.global UNK_021C59C8
UNK_021C59C8: ; 0x021C59C8
	.space 0x8

	.text

	thumb_func_start FUN_0202254C
FUN_0202254C: ; 0x0202254C
	push {r4, lr}
	ldr r1, _020225E0 ; =0x000204A8
	mov r0, #0x1
	bl AllocFromHeap
	add r4, r0, #0x0
	ldr r2, _020225E0 ; =0x000204A8
	mov r0, #0x0
	add r1, r4, #0x0
	bl MIi_CpuClearFast
	ldr r0, _020225E4 ; =UNK_021C59C8
	str r4, [r0, #0x0]
	bl FUN_02023570
	str r0, [r4, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	mov r0, #0x1
	str r0, [r4, #0x8]
	str r0, [r4, #0xc]
	add r0, r4, #0x0
	ldr r1, _020225E8 ; =0x00001021
	add r0, #0x14
	bl MATHi_CRC16InitTable
	ldr r0, _020225EC ; =0x00020224
	add r0, r4, r0
	bl FUN_020230E4
	ldr r0, _020225F0 ; =0x00020464
	ldr r1, _020225EC ; =0x00020224
	add r0, r4, r0
	add r1, r4, r1
	bl FUN_02023160
	ldr r1, _020225F4 ; =0x00020218
	mov r0, #0x0
	add r1, r4, r1
	mov r2, #0x8
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	bl FUN_02022AD8
	str r0, [r4, #0x10]
	cmp r0, #0x3
	bhi _020225DA
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020225B8: ; jump table (using 16-bit offset)
	.short _020225D4 - _020225B8 - 2; case 0
	.short _020225C0 - _020225B8 - 2; case 1
	.short _020225C4 - _020225B8 - 2; case 2
	.short _020225D4 - _020225B8 - 2; case 3
_020225C0:
	mov r0, #0x0
	str r0, [r4, #0xc]
_020225C4:
	add r0, r4, #0x0
	bl FUN_02022D08
	mov r0, #0x1
	str r0, [r4, #0x4]
	mov r0, #0x0
	str r0, [r4, #0x8]
	b _020225DA
_020225D4:
	add r0, r4, #0x0
	bl FUN_020227DC
_020225DA:
	add r0, r4, #0x0
	pop {r4, pc}
	nop
_020225E0: .word 0x000204A8
_020225E4: .word UNK_021C59C8
_020225E8: .word 0x00001021
_020225EC: .word 0x00020224
_020225F0: .word 0x00020464
_020225F4: .word 0x00020218

	thumb_func_start FUN_020225F8
FUN_020225F8: ; 0x020225F8
	push {r3, lr}
	ldr r0, _0202260C ; =UNK_021C59C8
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02022606
	bl ErrorHandling
_02022606:
	ldr r0, _0202260C ; =UNK_021C59C8
	ldr r0, [r0, #0x0]
	pop {r3, pc}
	.balign 4
_0202260C: .word UNK_021C59C8

	thumb_func_start FUN_02022610
FUN_02022610: ; 0x02022610
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x24
	blt _0202261E
	bl ErrorHandling
_0202261E:
	mov r0, #0x85
	lsl r0, r0, #0x2
	add r2, r5, r0
	lsl r0, r4, #0x4
	add r1, r5, r0
	ldr r0, _02022630 ; =0x0002022C
	ldr r0, [r1, r0]
	add r0, r2, r0
	pop {r3-r5, pc}
	.balign 4
_02022630: .word 0x0002022C

	thumb_func_start FUN_02022634
FUN_02022634: ; 0x02022634
	ldr r3, _02022638 ; =FUN_02022610
	bx r3
	.balign 4
_02022638: .word FUN_02022610

	thumb_func_start FUN_0202263C
FUN_0202263C: ; 0x0202263C
	push {r3-r7, lr}
	mov r1, #0x1
	str r0, [sp, #0x0]
	mov r0, #0x3
	lsl r1, r1, #0xc
	bl AllocFromHeapAtEnd
	add r6, r0, #0x0
	mov r0, #0x1
	bl FUN_02016444
	ldr r1, _020226F4 ; =0x00020220
	ldr r0, [sp, #0x0]
	ldrb r0, [r0, r1]
	cmp r0, #0x0
	bne _02022660
	mov r2, #0x1
	b _02022662
_02022660:
	mov r2, #0x0
_02022662:
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	bl FUN_02023074
	ldr r1, _020226F8 ; =0x00020221
	ldr r0, [sp, #0x0]
	ldrb r0, [r0, r1]
	cmp r0, #0x0
	bne _02022678
	mov r2, #0x1
	b _0202267A
_02022678:
	mov r2, #0x0
_0202267A:
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	bl FUN_02023074
	ldr r0, [sp, #0x0]
	ldr r3, _020226F4 ; =0x00020220
	add r2, r0, #0x0
	ldrb r2, [r2, r3]
	mov r1, #0x0
	bl FUN_02023074
	ldr r0, [sp, #0x0]
	ldr r3, _020226F8 ; =0x00020221
	add r2, r0, #0x0
	ldrb r2, [r2, r3]
	mov r1, #0x1
	bl FUN_02023074
	mov r0, #0x0
	mov r2, #0x1
	mvn r0, r0
	add r1, r6, #0x0
	lsl r2, r2, #0xc
	bl MIi_CpuClearFast
	mov r4, #0x0
	mov r7, #0x1
	add r5, r4, #0x0
	lsl r7, r7, #0xc
_020226B4:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020235D0
	add r0, r4, #0x0
	add r0, #0x40
	lsl r0, r0, #0xc
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_020235D0
	mov r0, #0x1
	lsl r0, r0, #0xc
	add r4, r4, #0x1
	add r5, r5, r0
	cmp r4, #0x40
	blt _020226B4
	add r0, r6, #0x0
	bl FreeToHeap
	ldr r0, [sp, #0x0]
	bl FUN_020227DC
	ldr r0, [sp, #0x0]
	mov r1, #0x0
	str r1, [r0, #0x4]
	mov r0, #0x1
	bl FUN_02016454
	mov r0, #0x1
	pop {r3-r7, pc}
	.balign 4
_020226F4: .word 0x00020220
_020226F8: .word 0x00020221

	thumb_func_start FUN_020226FC
FUN_020226FC: ; 0x020226FC
	push {r4, lr}
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	bne _0202270A
	mov r0, #0x0
	pop {r4, pc}
_0202270A:
	bl FUN_02022D08
	cmp r0, #0x0
	beq _0202271C
	mov r0, #0x1
	str r0, [r4, #0x4]
	mov r1, #0x0
	str r1, [r4, #0x8]
	pop {r4, pc}
_0202271C:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_02022720
FUN_02022720: ; 0x02022720
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _0202272E
	mov r0, #0x3
	pop {r4, pc}
_0202272E:
	ldr r0, [r4, #0x8]
	cmp r0, #0x0
	beq _02022784
	mov r0, #0x1
	bl FUN_02016444
	ldr r0, _02022798 ; =0x00020220
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	bne _02022746
	mov r2, #0x1
	b _02022748
_02022746:
	mov r2, #0x0
_02022748:
	add r0, r4, #0x0
	mov r1, #0x0
	bl FUN_02023074
	ldr r0, _0202279C ; =0x00020221
	ldrb r0, [r4, r0]
	cmp r0, #0x0
	bne _0202275C
	mov r2, #0x1
	b _0202275E
_0202275C:
	mov r2, #0x0
_0202275E:
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02023074
	ldr r2, _02022798 ; =0x00020220
	add r0, r4, #0x0
	ldrb r2, [r4, r2]
	mov r1, #0x0
	bl FUN_02023074
	ldr r2, _0202279C ; =0x00020221
	add r0, r4, #0x0
	ldrb r2, [r4, r2]
	mov r1, #0x1
	bl FUN_02023074
	mov r0, #0x1
	bl FUN_02016454
_02022784:
	add r0, r4, #0x0
	bl FUN_02023044
	cmp r0, #0x2
	bne _02022796
	mov r1, #0x1
	str r1, [r4, #0x4]
	mov r1, #0x0
	str r1, [r4, #0x8]
_02022796:
	pop {r4, pc}
	.balign 4
_02022798: .word 0x00020220
_0202279C: .word 0x00020221

	thumb_func_start FUN_020227A0
FUN_020227A0: ; 0x020227A0
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x2
	blt _020227AE
	bl ErrorHandling
_020227AE:
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	beq _020227B8
	bl ErrorHandling
_020227B8:
	ldr r0, [r5, #0x4]
	cmp r0, #0x1
	beq _020227C2
	bl ErrorHandling
_020227C2:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02022840
_020227CA:
	add r0, r5, #0x0
	bl FUN_02022854
	cmp r0, #0x0
	beq _020227CA
	cmp r0, #0x1
	beq _020227CA
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020227DC
FUN_020227DC: ; 0x020227DC
	add r2, r0, #0x0
	mov r0, #0x1
	str r0, [r2, #0x8]
	str r0, [r2, #0xc]
	mov r0, #0x85
	ldr r1, _020227F4 ; =0x00020224
	lsl r0, r0, #0x2
	ldr r3, _020227F8 ; =FUN_020231F4
	add r0, r2, r0
	add r1, r2, r1
	bx r3
	nop
_020227F4: .word 0x00020224
_020227F8: .word FUN_020231F4

	thumb_func_start FUN_020227FC
FUN_020227FC: ; 0x020227FC
	ldr r0, [r0, #0x0]
	bx lr

	thumb_func_start FUN_02022800
FUN_02022800: ; 0x02022800
	ldr r0, [r0, #0x10]
	bx lr

	thumb_func_start FUN_02022804
FUN_02022804: ; 0x02022804
	ldr r0, [r0, #0x4]
	bx lr

	thumb_func_start FUN_02022808
FUN_02022808: ; 0x02022808
	ldr r0, [r0, #0x8]
	bx lr

	thumb_func_start FUN_0202280C
FUN_0202280C: ; 0x0202280C
	push {r4, lr}
	add r4, r0, #0x0
	bl FUN_02022808
	cmp r0, #0x0
	beq _02022826
	add r0, r4, #0x0
	bl FUN_02022804
	cmp r0, #0x0
	beq _02022826
	mov r0, #0x1
	pop {r4, pc}
_02022826:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0202282C
FUN_0202282C: ; 0x0202282C
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start FUN_02022830
FUN_02022830: ; 0x02022830
	ldr r0, _0202283C ; =UNK_021C59C8
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	str r1, [r0, #0xc]
	bx lr
	nop
_0202283C: .word UNK_021C59C8

	thumb_func_start FUN_02022840
FUN_02022840: ; 0x02022840
	add r2, r1, #0x0
	ldr r1, _0202284C ; =0x0002047C
	ldr r3, _02022850 ; =FUN_02022DFC
	add r1, r0, r1
	bx r3
	nop
_0202284C: .word 0x0002047C
_02022850: .word FUN_02022DFC

	thumb_func_start FUN_02022854
FUN_02022854: ; 0x02022854
	push {r3-r5, lr}
	ldr r1, _02022878 ; =0x0002047C
	add r5, r0, #0x0
	add r1, r5, r1
	bl FUN_02022E78
	add r4, r0, #0x0
	beq _02022874
	cmp r4, #0x1
	beq _02022874
	ldr r1, _02022878 ; =0x0002047C
	add r0, r5, #0x0
	add r1, r5, r1
	add r2, r4, #0x0
	bl FUN_02022F80
_02022874:
	add r0, r4, #0x0
	pop {r3-r5, pc}
	.balign 4
_02022878: .word 0x0002047C

	thumb_func_start FUN_0202287C
FUN_0202287C: ; 0x0202287C
	ldr r1, _02022884 ; =0x0002047C
	ldr r3, _02022888 ; =FUN_02022FF0
	add r1, r0, r1
	bx r3
	.balign 4
_02022884: .word 0x0002047C
_02022888: .word FUN_02022FF0

	thumb_func_start FUN_0202288C
FUN_0202288C: ; 0x0202288C
	mov r1, #0x0
	str r1, [r0, #0x0]
	str r1, [r0, #0x4]
	str r1, [r0, #0x8]
	bx lr
	.balign 4

	thumb_func_start FUN_02022898
FUN_02022898: ; 0x02022898
	ldr r3, _020228A0 ; =MATH_CalcCRC16CCITT
	add r0, #0x14
	sub r2, #0x14
	bx r3
	.balign 4
_020228A0: .word MATH_CalcCRC16CCITT

	thumb_func_start FUN_020228A4
FUN_020228A4: ; 0x020228A4
	cmp r0, #0x0
	bne _020228AC
	mov r2, #0x0
	b _020228B0
_020228AC:
	mov r2, #0x1
	lsl r2, r2, #0x12
_020228B0:
	ldr r0, [r1, #0x4]
	add r0, r2, r0
	bx lr
	.balign 4

	thumb_func_start FUN_020228B8
FUN_020228B8: ; 0x020228B8
	push {r3-r5, lr}
	ldr r3, _020228DC ; =0x00020464
	add r3, r0, r3
	mov r0, #0xc
	mul r0, r2
	add r5, r3, r0
	ldr r0, [r5, #0x4]
	add r4, r1, r0
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	bne _020228D2
	bl ErrorHandling
_020228D2:
	ldr r0, [r5, #0x8]
	add r0, r4, r0
	sub r0, #0x14
	pop {r3-r5, pc}
	nop
_020228DC: .word 0x00020464

	thumb_func_start FUN_020228E0
FUN_020228E0: ; 0x020228E0
	push {r3-r7, lr}
	ldr r4, _02022934 ; =0x00020464
	add r3, r0, #0x0
	add r3, r3, r4
	add r5, r2, #0x0
	mov r4, #0xc
	mul r4, r5
	str r0, [sp, #0x0]
	add r7, r1, #0x0
	add r6, r3, r4
	bl FUN_020228B8
	add r4, r0, #0x0
	ldr r2, [r6, #0x8]
	ldr r0, [r4, #0x8]
	ldr r1, [r6, #0x4]
	cmp r0, r2
	beq _02022908
	mov r0, #0x0
	pop {r3-r7, pc}
_02022908:
	ldr r3, [r4, #0xc]
	ldr r0, _02022938 ; =0x20060623
	cmp r3, r0
	beq _02022914
	mov r0, #0x0
	pop {r3-r7, pc}
_02022914:
	ldrb r0, [r4, #0x10]
	cmp r0, r5
	beq _0202291E
	mov r0, #0x0
	pop {r3-r7, pc}
_0202291E:
	ldr r0, [sp, #0x0]
	add r1, r7, r1
	bl FUN_02022898
	ldrh r1, [r4, #0x12]
	cmp r1, r0
	bne _02022930
	mov r0, #0x1
	pop {r3-r7, pc}
_02022930:
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4
_02022934: .word 0x00020464
_02022938: .word 0x20060623

	thumb_func_start FUN_0202293C
FUN_0202293C: ; 0x0202293C
	push {r3-r7, lr}
	add r7, r2, #0x0
	add r6, r1, #0x0
	add r5, r0, #0x0
	str r3, [sp, #0x0]
	add r0, r6, #0x0
	add r1, r7, #0x0
	add r2, r3, #0x0
	bl FUN_020228B8
	add r4, r0, #0x0
	ldr r2, [sp, #0x0]
	add r0, r6, #0x0
	add r1, r7, #0x0
	bl FUN_020228E0
	str r0, [r5, #0x0]
	ldr r0, [r4, #0x0]
	str r0, [r5, #0x4]
	ldr r0, [r4, #0x4]
	str r0, [r5, #0x8]
	pop {r3-r7, pc}

	thumb_func_start FUN_02022968
FUN_02022968: ; 0x02022968
	push {r3-r7, lr}
	ldr r3, _020229AC ; =0x00020464
	add r5, r0, #0x0
	add r7, r2, #0x0
	mov r4, #0xc
	add r3, r5, r3
	mul r4, r7
	str r1, [sp, #0x0]
	add r6, r3, r4
	bl FUN_020228B8
	ldr r2, _020229B0 ; =0x00020214
	add r4, r0, #0x0
	ldr r0, [r5, r2]
	ldr r1, [r6, #0x4]
	add r2, r2, #0x4
	str r0, [r4, #0x0]
	lsl r0, r7, #0x2
	add r0, r5, r0
	ldr r0, [r0, r2]
	ldr r2, [sp, #0x0]
	str r0, [r4, #0x4]
	ldr r0, [r6, #0x8]
	add r1, r2, r1
	str r0, [r4, #0x8]
	ldr r0, _020229B4 ; =0x20060623
	str r0, [r4, #0xc]
	strb r7, [r4, #0x10]
	ldr r2, [r6, #0x8]
	add r0, r5, #0x0
	bl FUN_02022898
	strh r0, [r4, #0x12]
	pop {r3-r7, pc}
	.balign 4
_020229AC: .word 0x00020464
_020229B0: .word 0x00020214
_020229B4: .word 0x20060623

	thumb_func_start FUN_020229B8
FUN_020229B8: ; 0x020229B8
	mov r2, #0x0
	mvn r2, r2
	cmp r0, r2
	bne _020229C8
	cmp r1, #0x0
	bne _020229C8
	add r0, r2, #0x0
	bx lr
_020229C8:
	cmp r0, #0x0
	bne _020229D8
	mov r2, #0x0
	mvn r2, r2
	cmp r1, r2
	bne _020229D8
	mov r0, #0x1
	bx lr
_020229D8:
	cmp r0, r1
	bls _020229E0
	mov r0, #0x1
	bx lr
_020229E0:
	cmp r0, r1
	bhs _020229E8
	mov r0, #0x1
	b _020229EA
_020229E8:
	mov r0, #0x0
_020229EA:
	neg r0, r0
	bx lr
	.balign 4

	thumb_func_start FUN_020229F0
FUN_020229F0: ; 0x020229F0
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r6, r1, #0x0
	ldr r0, [r7, #0x4]
	ldr r1, [r6, #0x4]
	add r5, r2, #0x0
	add r4, r3, #0x0
	bl FUN_020229B8
	str r0, [sp, #0x0]
	ldr r0, [r7, #0x8]
	ldr r1, [r6, #0x8]
	bl FUN_020229B8
	ldr r2, [r7, #0x0]
	cmp r2, #0x0
	beq _02022A6A
	ldr r1, [r6, #0x0]
	cmp r1, #0x0
	beq _02022A6A
	ldr r1, [sp, #0x0]
	cmp r1, #0x0
	ble _02022A30
	cmp r0, #0x0
	bgt _02022A26
	bl ErrorHandling
_02022A26:
	mov r0, #0x0
	str r0, [r5, #0x0]
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _02022A66
_02022A30:
	bge _02022A44
	cmp r0, #0x0
	blt _02022A3A
	bl ErrorHandling
_02022A3A:
	mov r0, #0x1
	str r0, [r5, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x0]
	b _02022A66
_02022A44:
	cmp r0, #0x0
	ble _02022A52
	mov r0, #0x0
	str r0, [r5, #0x0]
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _02022A66
_02022A52:
	bge _02022A5E
	mov r0, #0x1
	str r0, [r5, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x0]
	b _02022A66
_02022A5E:
	mov r0, #0x0
	str r0, [r5, #0x0]
	mov r0, #0x1
	str r0, [r4, #0x0]
_02022A66:
	mov r0, #0x2
	pop {r3-r7, pc}
_02022A6A:
	cmp r2, #0x0
	beq _02022A80
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	bne _02022A80
	mov r0, #0x0
	str r0, [r5, #0x0]
	mov r0, #0x2
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r3-r7, pc}
_02022A80:
	cmp r2, #0x0
	bne _02022A94
	ldr r0, [r6, #0x0]
	cmp r0, #0x0
	beq _02022A94
	mov r0, #0x1
	str r0, [r5, #0x0]
	mov r1, #0x2
	str r1, [r4, #0x0]
	pop {r3-r7, pc}
_02022A94:
	mov r0, #0x2
	str r0, [r5, #0x0]
	str r0, [r4, #0x0]
	mov r0, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_02022AA0
FUN_02022AA0: ; 0x02022AA0
	push {r3-r6}
	mov r4, #0xc
	add r5, r3, #0x0
	mul r5, r4
	add r6, r1, r5
	ldr r5, [r6, #0x4]
	ldr r1, _02022AD4 ; =0x00020214
	str r5, [r0, r1]
	ldr r6, [r6, #0x8]
	add r5, r1, #0x4
	str r6, [r0, r5]
	ldr r5, [sp, #0x10]
	mul r4, r5
	add r2, r2, r4
	ldr r4, [r2, #0x8]
	add r2, r1, #0x0
	add r2, #0x8
	str r4, [r0, r2]
	add r2, r1, #0x0
	add r2, #0xc
	strb r3, [r0, r2]
	add r1, #0xd
	strb r5, [r0, r1]
	pop {r3-r6}
	bx lr
	nop
_02022AD4: .word 0x00020214

	thumb_func_start FUN_02022AD8
FUN_02022AD8: ; 0x02022AD8
	push {r3-r6, lr}
	sub sp, #0x44
	mov r1, #0x2
	add r5, r0, #0x0
	mov r0, #0x3
	lsl r1, r1, #0x10
	bl AllocFromHeapAtEnd
	mov r1, #0x2
	add r6, r0, #0x0
	mov r0, #0x3
	lsl r1, r1, #0x10
	bl AllocFromHeapAtEnd
	mov r2, #0x2
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r6, #0x0
	lsl r2, r2, #0x10
	bl FUN_020235EC
	cmp r0, #0x0
	add r0, sp, #0x2c
	beq _02022B20
	add r1, r5, #0x0
	add r2, r6, #0x0
	mov r3, #0x0
	bl FUN_0202293C
	add r0, sp, #0x14
	add r1, r5, #0x0
	add r2, r6, #0x0
	mov r3, #0x1
	bl FUN_0202293C
	b _02022B2A
_02022B20:
	bl FUN_0202288C
	add r0, sp, #0x14
	bl FUN_0202288C
_02022B2A:
	mov r0, #0x1
	lsl r0, r0, #0x12
	add r1, r4, #0x0
	lsr r2, r0, #0x1
	bl FUN_020235EC
	cmp r0, #0x0
	add r0, sp, #0x38
	beq _02022B54
	add r1, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x0
	bl FUN_0202293C
	add r0, sp, #0x20
	add r1, r5, #0x0
	add r2, r4, #0x0
	mov r3, #0x1
	bl FUN_0202293C
	b _02022B5E
_02022B54:
	bl FUN_0202288C
	add r0, sp, #0x20
	bl FUN_0202288C
_02022B5E:
	add r0, r6, #0x0
	bl FreeToHeap
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, sp, #0x2c
	add r1, sp, #0x38
	add r2, sp, #0x10
	add r3, sp, #0x8
	bl FUN_020229F0
	add r4, r0, #0x0
	add r0, sp, #0x14
	add r1, sp, #0x20
	add r2, sp, #0xc
	add r3, sp, #0x4
	bl FUN_020229F0
	cmp r4, #0x0
	bne _02022B92
	cmp r0, #0x0
	bne _02022B92
	add sp, #0x44
	mov r0, #0x0
	pop {r3-r6, pc}
_02022B92:
	cmp r4, #0x0
	beq _02022B9A
	cmp r0, #0x0
	bne _02022BA0
_02022B9A:
	add sp, #0x44
	mov r0, #0x3
	pop {r3-r6, pc}
_02022BA0:
	cmp r4, #0x2
	bne _02022BE4
	cmp r0, #0x2
	bne _02022BE4
	ldr r3, [sp, #0x10]
	ldr r1, [sp, #0xc]
	mov r2, #0xc
	add r4, r3, #0x0
	mul r4, r2
	add r0, sp, #0x30
	ldr r0, [r0, r4]
	add r4, r1, #0x0
	mul r4, r2
	add r2, sp, #0x18
	ldr r2, [r2, r4]
	cmp r0, r2
	str r1, [sp, #0x0]
	add r1, sp, #0x2c
	bne _02022BD4
	add r0, r5, #0x0
	add r2, sp, #0x14
	bl FUN_02022AA0
	add sp, #0x44
	mov r0, #0x1
	pop {r3-r6, pc}
_02022BD4:
	ldr r3, [sp, #0x8]
	add r0, r5, #0x0
	add r2, sp, #0x14
	bl FUN_02022AA0
	add sp, #0x44
	mov r0, #0x2
	pop {r3-r6, pc}
_02022BE4:
	cmp r4, #0x1
	bne _02022C3A
	cmp r0, #0x2
	bne _02022C3A
	ldr r3, [sp, #0x10]
	ldr r0, [sp, #0xc]
	mov r4, #0xc
	add r2, r3, #0x0
	add r6, r0, #0x0
	mul r2, r4
	add r1, sp, #0x30
	ldr r2, [r1, r2]
	mul r6, r4
	add r1, sp, #0x18
	ldr r6, [r1, r6]
	cmp r2, r6
	bne _02022C18
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, sp, #0x2c
	add r2, sp, #0x14
	bl FUN_02022AA0
	add sp, #0x44
	mov r0, #0x2
	pop {r3-r6, pc}
_02022C18:
	ldr r0, [sp, #0x4]
	mul r4, r0
	ldr r1, [r1, r4]
	cmp r2, r1
	bne _02022C34
	str r0, [sp, #0x0]
	add r0, r5, #0x0
	add r1, sp, #0x2c
	add r2, sp, #0x14
	bl FUN_02022AA0
	add sp, #0x44
	mov r0, #0x2
	pop {r3-r6, pc}
_02022C34:
	add sp, #0x44
	mov r0, #0x3
	pop {r3-r6, pc}
_02022C3A:
	cmp r4, #0x2
	bne _02022C7E
	cmp r0, #0x1
	bne _02022C7E
	ldr r3, [sp, #0x10]
	ldr r1, [sp, #0xc]
	mov r2, #0xc
	add r4, r3, #0x0
	mul r4, r2
	add r0, sp, #0x30
	ldr r0, [r0, r4]
	add r4, r1, #0x0
	mul r4, r2
	add r2, sp, #0x18
	ldr r2, [r2, r4]
	cmp r0, r2
	str r1, [sp, #0x0]
	add r1, sp, #0x2c
	bne _02022C6E
	add r0, r5, #0x0
	add r2, sp, #0x14
	bl FUN_02022AA0
	add sp, #0x44
	mov r0, #0x1
	pop {r3-r6, pc}
_02022C6E:
	ldr r3, [sp, #0x8]
	add r0, r5, #0x0
	add r2, sp, #0x14
	bl FUN_02022AA0
	add sp, #0x44
	mov r0, #0x2
	pop {r3-r6, pc}
_02022C7E:
	cmp r4, #0x1
	bne _02022CBC
	cmp r0, #0x1
	bne _02022CBC
	ldr r0, [sp, #0xc]
	ldr r2, [sp, #0x10]
	cmp r2, r0
	bne _02022CBC
	add r3, r2, #0x0
	mov r1, #0xc
	mul r3, r1
	add r2, sp, #0x30
	mul r1, r0
	add r0, sp, #0x18
	ldr r2, [r2, r3]
	ldr r0, [r0, r1]
	cmp r2, r0
	beq _02022CA6
	bl ErrorHandling
_02022CA6:
	ldr r0, [sp, #0xc]
	add r1, sp, #0x2c
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x10]
	add r0, r5, #0x0
	add r2, sp, #0x14
	bl FUN_02022AA0
	add sp, #0x44
	mov r0, #0x1
	pop {r3-r6, pc}
_02022CBC:
	ldr r1, [sp, #0x10]
	mov r0, #0xc
	add r2, r1, #0x0
	mul r2, r0
	add r1, sp, #0x30
	ldr r3, [r1, r2]
	ldr r1, [sp, #0xc]
	add r2, r1, #0x0
	mul r2, r0
	add r0, sp, #0x18
	ldr r0, [r0, r2]
	cmp r3, r0
	beq _02022CDA
	bl ErrorHandling
_02022CDA:
	ldr r0, [sp, #0xc]
	add r1, sp, #0x2c
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x10]
	add r0, r5, #0x0
	add r2, sp, #0x14
	bl FUN_02022AA0
	mov r0, #0x2
	add sp, #0x44
	pop {r3-r6, pc}

	thumb_func_start FUN_02022CF0
FUN_02022CF0: ; 0x02022CF0
	push {r3-r5, lr}
	add r5, r1, #0x0
	add r4, r2, #0x0
	bl FUN_020228A4
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	add r1, r4, r1
	bl FUN_020235EC
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02022D08
FUN_02022D08: ; 0x02022D08
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _02022D4C ; =0x00020464
	mov r7, #0x85
	mov r4, #0x0
	add r6, r5, r0
	lsl r7, r7, #0x2
_02022D16:
	ldr r0, _02022D50 ; =0x00020220
	add r1, r5, r4
	ldrb r0, [r1, r0]
	add r1, r6, #0x0
	add r2, r5, r7
	bl FUN_02022CF0
	cmp r0, #0x0
	bne _02022D2C
	mov r0, #0x0
	pop {r3-r7, pc}
_02022D2C:
	add r0, r5, #0x0
	add r1, r5, r7
	add r2, r4, #0x0
	bl FUN_020228E0
	cmp r0, #0x0
	bne _02022D3E
	mov r0, #0x0
	pop {r3-r7, pc}
_02022D3E:
	add r4, r4, #0x1
	add r6, #0xc
	cmp r4, #0x2
	blt _02022D16
	mov r0, #0x1
	pop {r3-r7, pc}
	nop
_02022D4C: .word 0x00020464
_02022D50: .word 0x00020220

	thumb_func_start FUN_02022D54
FUN_02022D54: ; 0x02022D54
	push {r4-r6, lr}
	add r3, r1, #0x0
	ldr r1, _02022D90 ; =0x00020464
	add r5, r0, #0x0
	add r6, r2, #0x0
	add r2, r5, r1
	mov r1, #0xc
	mul r1, r3
	add r4, r2, r1
	mov r1, #0x85
	lsl r1, r1, #0x2
	add r1, r5, r1
	add r2, r3, #0x0
	bl FUN_02022968
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_020228A4
	mov r1, #0x85
	lsl r1, r1, #0x2
	add r2, r5, r1
	ldr r1, [r4, #0x4]
	add r1, r2, r1
	ldr r2, [r4, #0x8]
	sub r2, #0x14
	bl FUN_02023668
	pop {r4-r6, pc}
	nop
_02022D90: .word 0x00020464

	thumb_func_start FUN_02022D94
FUN_02022D94: ; 0x02022D94
	push {r4-r6, lr}
	add r6, r0, #0x0
	ldr r0, _02022DC4 ; =0x00020464
	add r3, r6, r0
	mov r0, #0xc
	mul r0, r1
	add r4, r3, r0
	add r0, r2, #0x0
	add r1, r4, #0x0
	ldr r5, [r4, #0x8]
	bl FUN_020228A4
	mov r1, #0x2
	lsl r1, r1, #0x8
	add r2, r6, r1
	ldr r1, [r4, #0x4]
	add r0, r5, r0
	add r1, r2, r1
	sub r0, #0x14
	add r1, r1, r5
	mov r2, #0x14
	bl FUN_02023668
	pop {r4-r6, pc}
	.balign 4
_02022DC4: .word 0x00020464

	thumb_func_start FUN_02022DC8
FUN_02022DC8: ; 0x02022DC8
	push {r4-r6, lr}
	add r6, r0, #0x0
	ldr r0, _02022DF8 ; =0x00020464
	add r3, r6, r0
	mov r0, #0xc
	mul r0, r1
	add r4, r3, r0
	add r0, r2, #0x0
	add r1, r4, #0x0
	ldr r5, [r4, #0x8]
	bl FUN_020228A4
	mov r1, #0x82
	lsl r1, r1, #0x2
	add r2, r6, r1
	ldr r1, [r4, #0x4]
	add r0, r5, r0
	add r1, r2, r1
	sub r0, #0xc
	add r1, r1, r5
	mov r2, #0x8
	bl FUN_02023668
	pop {r4-r6, pc}
	.balign 4
_02022DF8: .word 0x00020464

	thumb_func_start FUN_02022DFC
FUN_02022DFC: ; 0x02022DFC
	push {r3-r7, lr}
	ldr r7, _02022E70 ; =0x00020218
	add r4, r1, #0x0
	mov r12, r2
	mov r1, #0x0
	add r2, r0, #0x0
	add r3, r4, #0x0
	add r6, r7, #0x0
_02022E0C:
	ldr r5, _02022E70 ; =0x00020218
	add r1, r1, #0x1
	ldr r5, [r2, r5]
	str r5, [r3, #0x1c]
	ldr r5, [r2, r7]
	add r3, r3, #0x4
	add r5, r5, #0x1
	str r5, [r2, r6]
	add r2, r2, #0x4
	cmp r1, #0x2
	blt _02022E0C
	mov r1, #0x0
	str r1, [r4, #0x14]
	mov r2, r12
	str r1, [r4, #0x0]
	cmp r2, #0x2
	bne _02022E58
	ldr r2, [r0, #0xc]
	cmp r2, #0x0
	beq _02022E4E
	mov r2, #0x1
	str r2, [r4, #0x0]
	ldr r2, _02022E74 ; =0x00020214
	ldr r3, [r0, r2]
	str r3, [r4, #0x18]
	ldr r3, [r0, r2]
	add r3, r3, #0x1
	str r3, [r0, r2]
	str r1, [r4, #0x4]
	str r1, [r4, #0x8]
	mov r0, #0x2
	str r0, [r4, #0xc]
	b _02022E66
_02022E4E:
	str r1, [r4, #0x4]
	str r1, [r4, #0x8]
	mov r0, #0x1
	str r0, [r4, #0xc]
	b _02022E66
_02022E58:
	mov r0, r12
	str r0, [r4, #0x4]
	mov r0, r12
	str r0, [r4, #0x8]
	mov r0, r12
	add r0, r0, #0x1
	str r0, [r4, #0xc]
_02022E66:
	mov r0, #0x1
	bl FUN_02016444
	pop {r3-r7, pc}
	nop
_02022E70: .word 0x00020218
_02022E74: .word 0x00020214

	thumb_func_start FUN_02022E78
FUN_02022E78: ; 0x02022E78
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	ldr r0, [r4, #0x14]
	cmp r0, #0x5
	bhi _02022F78
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02022E90: ; jump table (using 16-bit offset)
	.short _02022E9C - _02022E90 - 2; case 0
	.short _02022EC0 - _02022E90 - 2; case 1
	.short _02022EDC - _02022E90 - 2; case 2
	.short _02022F00 - _02022E90 - 2; case 3
	.short _02022F2A - _02022E90 - 2; case 4
	.short _02022F4E - _02022E90 - 2; case 5
_02022E9C:
	ldr r1, [r4, #0x8]
	ldr r0, _02022F7C ; =0x00020220
	add r2, r5, r1
	ldrb r0, [r2, r0]
	cmp r0, #0x0
	bne _02022EAC
	mov r2, #0x1
	b _02022EAE
_02022EAC:
	mov r2, #0x0
_02022EAE:
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02022D54
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x14]
	add r0, r0, #0x1
	str r0, [r4, #0x14]
_02022EC0:
	ldr r0, [r4, #0x10]
	add r1, sp, #0x0
	bl FUN_020236E4
	cmp r0, #0x0
	beq _02022F78
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bne _02022ED6
	mov r0, #0x3
	pop {r3-r5, pc}
_02022ED6:
	ldr r0, [r4, #0x14]
	add r0, r0, #0x1
	str r0, [r4, #0x14]
_02022EDC:
	ldr r1, [r4, #0x8]
	ldr r0, _02022F7C ; =0x00020220
	add r2, r5, r1
	ldrb r0, [r2, r0]
	cmp r0, #0x0
	bne _02022EEC
	mov r2, #0x1
	b _02022EEE
_02022EEC:
	mov r2, #0x0
_02022EEE:
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02022DC8
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x14]
	add r0, r0, #0x1
	str r0, [r4, #0x14]
_02022F00:
	ldr r0, [r4, #0x10]
	add r1, sp, #0x0
	bl FUN_020236E4
	cmp r0, #0x0
	beq _02022F78
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bne _02022F16
	mov r0, #0x3
	pop {r3-r5, pc}
_02022F16:
	ldr r0, [r4, #0x14]
	add r0, r0, #0x1
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x8]
	add r1, r0, #0x1
	ldr r0, [r4, #0xc]
	cmp r1, r0
	bne _02022F2A
	mov r0, #0x1
	pop {r3-r5, pc}
_02022F2A:
	ldr r1, [r4, #0x8]
	ldr r0, _02022F7C ; =0x00020220
	add r2, r5, r1
	ldrb r0, [r2, r0]
	cmp r0, #0x0
	bne _02022F3A
	mov r2, #0x1
	b _02022F3C
_02022F3A:
	mov r2, #0x0
_02022F3C:
	lsl r2, r2, #0x18
	add r0, r5, #0x0
	lsr r2, r2, #0x18
	bl FUN_02022D94
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x14]
	add r0, r0, #0x1
	str r0, [r4, #0x14]
_02022F4E:
	ldr r0, [r4, #0x10]
	add r1, sp, #0x0
	bl FUN_020236E4
	cmp r0, #0x0
	beq _02022F78
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	bne _02022F64
	mov r0, #0x3
	pop {r3-r5, pc}
_02022F64:
	ldr r0, [r4, #0x8]
	add r1, r0, #0x1
	str r1, [r4, #0x8]
	ldr r0, [r4, #0xc]
	cmp r1, r0
	bne _02022F74
	mov r0, #0x2
	pop {r3-r5, pc}
_02022F74:
	mov r0, #0x0
	str r0, [r4, #0x14]
_02022F78:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_02022F7C: .word 0x00020220

	thumb_func_start FUN_02022F80
FUN_02022F80: ; 0x02022F80
	push {r3-r7, lr}
	add r3, r0, #0x0
	add r0, r1, #0x0
	cmp r2, #0x3
	bne _02022FAA
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _02022F96
	ldr r2, [r0, #0x18]
	ldr r1, _02022FE4 ; =0x00020214
	str r2, [r3, r1]
_02022F96:
	ldr r1, _02022FE8 ; =0x00020218
	mov r4, #0x0
_02022F9A:
	ldr r2, [r0, #0x1c]
	add r4, r4, #0x1
	str r2, [r3, r1]
	add r0, r0, #0x4
	add r3, r3, #0x4
	cmp r4, #0x2
	blt _02022F9A
	b _02022FDA
_02022FAA:
	ldr r6, [r0, #0x4]
	ldr r1, [r0, #0xc]
	cmp r6, r1
	bge _02022FD0
	ldr r1, _02022FEC ; =0x00020220
	mov r7, #0x1
	add r2, r1, #0x0
_02022FB8:
	add r5, r3, r6
	ldrb r4, [r5, r2]
	cmp r4, #0x0
	bne _02022FC4
	add r4, r7, #0x0
	b _02022FC6
_02022FC4:
	mov r4, #0x0
_02022FC6:
	strb r4, [r5, r1]
	ldr r4, [r0, #0xc]
	add r6, r6, #0x1
	cmp r6, r4
	blt _02022FB8
_02022FD0:
	mov r0, #0x1
	str r0, [r3, #0x4]
	mov r0, #0x0
	str r0, [r3, #0x8]
	str r0, [r3, #0xc]
_02022FDA:
	mov r0, #0x1
	bl FUN_02016454
	pop {r3-r7, pc}
	nop
_02022FE4: .word 0x00020214
_02022FE8: .word 0x00020218
_02022FEC: .word 0x00020220

	thumb_func_start FUN_02022FF0
FUN_02022FF0: ; 0x02022FF0
	push {r3-r5, lr}
	add r4, r1, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x0
	beq _02023000
	ldr r2, [r4, #0x18]
	ldr r1, _0202303C ; =0x00020214
	str r2, [r0, r1]
_02023000:
	ldr r1, _02023040 ; =0x00020218
	mov r3, #0x0
	add r5, r4, #0x0
_02023006:
	ldr r2, [r5, #0x1c]
	add r3, r3, #0x1
	str r2, [r0, r1]
	add r5, r5, #0x4
	add r0, r0, #0x4
	cmp r3, #0x2
	blt _02023006
	bl CARD_TryWaitBackupAsync
	cmp r0, #0x0
	bne _02023034
	bl CARD_CancelBackupAsync
	ldr r0, [r4, #0x10]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl CARD_UnlockBackup
	ldr r0, [r4, #0x10]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bl OS_ReleaseLockID
_02023034:
	mov r0, #0x1
	bl FUN_02016454
	pop {r3-r5, pc}
	.balign 4
_0202303C: .word 0x00020214
_02023040: .word 0x00020218

	thumb_func_start FUN_02023044
FUN_02023044: ; 0x02023044
	push {r3-r6, lr}
	sub sp, #0x24
	add r1, sp, #0x0
	mov r2, #0x2
	add r5, r0, #0x0
	bl FUN_02022DFC
	add r6, sp, #0x0
_02023054:
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02022E78
	add r4, r0, #0x0
	beq _02023054
	cmp r4, #0x1
	beq _02023054
	add r0, r5, #0x0
	add r1, sp, #0x0
	add r2, r4, #0x0
	bl FUN_02022F80
	add r0, r4, #0x0
	add sp, #0x24
	pop {r3-r6, pc}

	thumb_func_start FUN_02023074
FUN_02023074: ; 0x02023074
	push {r4-r5, lr}
	sub sp, #0x14
	add r4, r2, #0x0
	ldr r2, _020230A8 ; =0x00020464
	add r2, r0, r2
	mov r0, #0xc
	mul r0, r1
	add r5, r2, r0
	add r0, sp, #0x0
	mov r1, #0xff
	mov r2, #0x14
	bl MI_CpuFill8
	add r0, r4, #0x0
	add r1, r5, #0x0
	bl FUN_020228A4
	ldr r1, [r5, #0x8]
	mov r2, #0x14
	add r0, r1, r0
	sub r0, #0x14
	add r1, sp, #0x0
	bl FUN_020235D0
	add sp, #0x14
	pop {r4-r5, pc}
	.balign 4
_020230A8: .word 0x00020464

	thumb_func_start FUN_020230AC
FUN_020230AC: ; 0x020230AC
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _020230DC ; =UNK_020EE6DC
	ldr r4, _020230E0 ; =UNK_020EE700
	ldr r0, [r0, #0x0]
	cmp r5, r0
	blt _020230BE
	bl ErrorHandling
_020230BE:
	lsl r0, r5, #0x4
	add r0, r4, r0
	ldr r0, [r0, #0x8]
	blx r0
	lsr r3, r0, #0x1f
	lsl r2, r0, #0x1e
	sub r2, r2, r3
	mov r1, #0x1e
	ror r2, r1
	add r2, r3, r2
	mov r1, #0x4
	sub r1, r1, r2
	add r0, r0, r1
	pop {r3-r5, pc}
	nop
_020230DC: .word UNK_020EE6DC
_020230E0: .word UNK_020EE700

	thumb_func_start FUN_020230E4
FUN_020230E4: ; 0x020230E4
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldr r0, _02023158 ; =UNK_020EE6DC
	ldr r4, _0202315C ; =UNK_020EE700
	ldr r0, [r0, #0x0]
	mov r7, #0x0
	str r0, [sp, #0x0]
	cmp r0, #0x24
	beq _020230FC
	bl ErrorHandling
_020230FC:
	ldr r0, [sp, #0x0]
	mov r6, #0x0
	cmp r0, #0x0
	ble _02023148
	sub r0, r0, #0x1
	str r0, [sp, #0x4]
_02023108:
	ldr r0, [r4, #0x0]
	cmp r6, r0
	beq _02023112
	bl ErrorHandling
_02023112:
	ldr r0, [r4, #0x0]
	str r0, [r5, #0x0]
	add r0, r6, #0x0
	bl FUN_020230AC
	str r0, [r5, #0x4]
	str r7, [r5, #0x8]
	mov r0, #0x0
	strh r0, [r5, #0xc]
	ldr r0, [r4, #0x4]
	strh r0, [r5, #0xe]
	ldr r0, [r5, #0x4]
	add r7, r7, r0
	ldr r0, [sp, #0x4]
	cmp r6, r0
	beq _0202313A
	ldr r1, [r4, #0x4]
	ldr r0, [r4, #0x14]
	cmp r1, r0
	beq _0202313C
_0202313A:
	add r7, #0x14
_0202313C:
	ldr r0, [sp, #0x0]
	add r6, r6, #0x1
	add r4, #0x10
	add r5, #0x10
	cmp r6, r0
	blt _02023108
_02023148:
	mov r0, #0x2
	lsl r0, r0, #0x10
	cmp r7, r0
	ble _02023154
	bl ErrorHandling
_02023154:
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_02023158: .word UNK_020EE6DC
_0202315C: .word UNK_020EE700

	thumb_func_start FUN_02023160
FUN_02023160: ; 0x02023160
	push {r3-r7, lr}
	sub sp, #0x8
	str r0, [sp, #0x0]
	mov r0, #0x0
	str r0, [sp, #0x4]
	mov r12, r0
	add r3, r0, #0x0
	add r6, r0, #0x0
	ldr r0, _020231EC ; =UNK_020EE6DC
	ldr r4, [sp, #0x0]
	ldr r7, [r0, #0x0]
	add r5, r1, #0x0
_02023178:
	add r2, r4, #0x0
	strb r6, [r4, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x8]
	add r2, #0x8
	b _02023190
_02023184:
	ldr r0, [r5, #0x4]
	ldr r1, [r2, #0x0]
	add r5, #0x10
	add r0, r1, r0
	str r0, [r2, #0x0]
	add r3, r3, #0x1
_02023190:
	ldrh r0, [r5, #0xe]
	cmp r6, r0
	bne _0202319A
	cmp r3, r7
	blt _02023184
_0202319A:
	ldr r0, [r4, #0x8]
	add r6, r6, #0x1
	add r0, #0x14
	str r0, [r4, #0x8]
	ldr r0, [sp, #0x4]
	strb r0, [r4, #0x1]
	mov r0, r12
	str r0, [r4, #0x4]
	ldr r1, [r4, #0x8]
	ldr r0, _020231F0 ; =0x00000FFF
	add r0, r1, r0
	lsr r0, r0, #0xc
	strb r0, [r4, #0x2]
	ldrb r1, [r4, #0x2]
	ldr r0, [sp, #0x4]
	add r0, r0, r1
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x8]
	mov r1, r12
	add r0, r1, r0
	add r4, #0xc
	mov r12, r0
	cmp r6, #0x2
	blt _02023178
	ldr r0, [sp, #0x0]
	ldrb r1, [r0, #0xd]
	ldrb r0, [r0, #0xe]
	add r1, r1, r0
	ldr r0, [sp, #0x4]
	cmp r0, r1
	beq _020231DC
	bl ErrorHandling
_020231DC:
	ldr r0, [sp, #0x4]
	cmp r0, #0x20
	ble _020231E6
	bl ErrorHandling
_020231E6:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_020231EC: .word UNK_020EE6DC
_020231F0: .word 0x00000FFF

	thumb_func_start FUN_020231F4
FUN_020231F4: ; 0x020231F4
	push {r3-r7, lr}
	sub sp, #0x8
	add r6, r0, #0x0
	mov r2, #0x2
	add r5, r1, #0x0
	mov r0, #0x0
	add r1, r6, #0x0
	lsl r2, r2, #0x10
	ldr r4, _02023240 ; =UNK_020EE700
	bl MIi_CpuClearFast
	ldr r0, _02023244 ; =UNK_020EE6DC
	mov r7, #0x0
	ldr r0, [r0, #0x0]
	str r0, [sp, #0x0]
	cmp r0, #0x0
	ble _0202323A
_02023216:
	ldr r0, [r5, #0x8]
	ldr r2, [r5, #0x4]
	str r0, [sp, #0x4]
	ldr r1, [sp, #0x4]
	mov r0, #0x0
	add r1, r6, r1
	bl MIi_CpuClearFast
	ldr r0, [sp, #0x4]
	ldr r1, [r4, #0xc]
	add r0, r6, r0
	blx r1
	ldr r0, [sp, #0x0]
	add r7, r7, #0x1
	add r5, #0x10
	add r4, #0x10
	cmp r7, r0
	blt _02023216
_0202323A:
	add sp, #0x8
	pop {r3-r7, pc}
	nop
_02023240: .word UNK_020EE700
_02023244: .word UNK_020EE6DC

	thumb_func_start FUN_02023248
FUN_02023248: ; 0x02023248
	push {r3-r5, lr}
	ldr r5, _0202326C ; =0x20060623
	add r4, r1, r3
	str r5, [r1, r3]
	ldr r5, _02023270 ; =0x000204A4
	ldr r5, [r0, r5]
	add r0, #0x14
	add r5, r5, #0x1
	str r5, [r4, #0x4]
	str r3, [r4, #0x8]
	add r3, #0xe
	strh r2, [r4, #0xc]
	add r2, r3, #0x0
	bl MATH_CalcCRC16CCITT
	strh r0, [r4, #0xe]
	pop {r3-r5, pc}
	nop
_0202326C: .word 0x20060623
_02023270: .word 0x000204A4

	thumb_func_start FUN_02023274
FUN_02023274: ; 0x02023274
	push {r4-r6, lr}
	ldr r6, [r1, r3]
	ldr r5, _020232B0 ; =0x20060623
	add r4, r1, r3
	cmp r6, r5
	beq _02023284
	mov r0, #0x0
	pop {r4-r6, pc}
_02023284:
	ldr r5, [r4, #0x8]
	cmp r5, r3
	beq _0202328E
	mov r0, #0x0
	pop {r4-r6, pc}
_0202328E:
	ldrh r5, [r4, #0xc]
	cmp r5, r2
	beq _02023298
	mov r0, #0x0
	pop {r4-r6, pc}
_02023298:
	add r3, #0xe
	add r0, #0x14
	add r2, r3, #0x0
	bl MATH_CalcCRC16CCITT
	ldrh r1, [r4, #0xe]
	cmp r1, r0
	bne _020232AC
	mov r0, #0x1
	pop {r4-r6, pc}
_020232AC:
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4
_020232B0: .word 0x20060623

	thumb_func_start FUN_020232B4
FUN_020232B4: ; 0x020232B4
	add r0, r0, r1
	ldr r0, [r0, #0x4]
	bx lr
	.balign 4

	thumb_func_start FUN_020232BC
FUN_020232BC: ; 0x020232BC
	push {r3-r7, lr}
	sub sp, #0x8
	add r7, r0, #0x0
	mov r0, #0x1
	add r5, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02016444
	ldr r0, _020233FC ; =UNK_020EE6D8
	ldr r0, [r0, #0x0]
	cmp r5, r0
	blt _020232D8
	bl ErrorHandling
_020232D8:
	ldr r1, _02023400 ; =UNK_020EE6E0
	lsl r0, r5, #0x4
	add r4, r1, r0
	ldr r0, [r1, r0]
	cmp r0, r5
	beq _020232E8
	bl ErrorHandling
_020232E8:
	ldr r0, [r4, #0x8]
	blx r0
	str r0, [sp, #0x4]
	add r0, #0x10
	str r0, [sp, #0x4]
	ldr r0, _02023404 ; =0x000204A0
	ldr r0, [r7, r0]
	cmp r0, #0x1
	ldr r0, [r4, #0x8]
	bne _0202336E
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023248
	ldr r0, [r4, #0x4]
	ldr r2, [sp, #0x4]
	lsl r0, r0, #0xc
	add r1, r6, #0x0
	bl FUN_020235D0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023274
	cmp r0, #0x1
	beq _02023330
	bl ErrorHandling
_02023330:
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023248
	ldr r0, [r4, #0x4]
	ldr r2, [sp, #0x4]
	add r0, #0x40
	lsl r0, r0, #0xc
	add r1, r6, #0x0
	bl FUN_020235D0
	ldr r1, [sp, #0x0]
	orr r0, r1
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023274
	cmp r0, #0x1
	beq _020233DE
	bl ErrorHandling
	b _020233DE
_0202336E:
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023248
	ldr r0, [r4, #0x4]
	ldr r2, [sp, #0x4]
	add r0, #0x40
	lsl r0, r0, #0xc
	add r1, r6, #0x0
	bl FUN_020235D0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023274
	cmp r0, #0x1
	beq _020233A4
	bl ErrorHandling
_020233A4:
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023248
	ldr r0, [r4, #0x4]
	ldr r2, [sp, #0x4]
	lsl r0, r0, #0xc
	add r1, r6, #0x0
	bl FUN_020235D0
	ldr r1, [sp, #0x0]
	orr r0, r1
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02023274
	cmp r0, #0x1
	beq _020233DE
	bl ErrorHandling
_020233DE:
	ldr r0, [sp, #0x0]
	cmp r0, #0x1
	bne _020233F0
	mov r0, #0x1
	bl FUN_02016454
	add sp, #0x8
	mov r0, #0x2
	pop {r3-r7, pc}
_020233F0:
	mov r0, #0x1
	bl FUN_02016454
	mov r0, #0x3
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4
_020233FC: .word UNK_020EE6D8
_02023400: .word UNK_020EE6E0
_02023404: .word 0x000204A0

	thumb_func_start FUN_02023408
FUN_02023408: ; 0x02023408
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	ldr r0, _02023564 ; =UNK_020EE6D8
	add r7, r2, #0x0
	ldr r0, [r0, #0x0]
	add r6, r1, #0x0
	str r3, [sp, #0x0]
	cmp r7, r0
	blt _02023420
	bl ErrorHandling
_02023420:
	ldr r1, _02023568 ; =UNK_020EE6E0
	lsl r0, r7, #0x4
	add r4, r1, r0
	ldr r0, [r1, r0]
	cmp r0, r7
	beq _02023430
	bl ErrorHandling
_02023430:
	ldr r0, [r4, #0x8]
	blx r0
	str r0, [sp, #0x10]
	add r0, #0x10
	str r0, [sp, #0x10]
	ldr r1, [sp, #0x10]
	add r0, r6, #0x0
	bl AllocFromHeap
	add r6, r0, #0x0
	ldr r0, [r4, #0x4]
	ldr r2, [sp, #0x10]
	lsl r0, r0, #0xc
	add r1, r6, #0x0
	bl FUN_020235EC
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02023274
	str r0, [sp, #0xc]
	ldr r0, [r4, #0x8]
	blx r0
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl FUN_020232B4
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x4]
	ldr r2, [sp, #0x10]
	add r0, #0x40
	lsl r0, r0, #0xc
	add r1, r6, #0x0
	bl FUN_020235EC
	ldr r0, [r4, #0x8]
	blx r0
	add r3, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl FUN_02023274
	add r7, r0, #0x0
	ldr r0, [r4, #0x8]
	blx r0
	add r1, r0, #0x0
	add r0, r6, #0x0
	bl FUN_020232B4
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x0]
	mov r1, #0x1
	str r1, [r0, #0x0]
	ldr r0, [sp, #0xc]
	cmp r0, #0x1
	bne _020234CC
	cmp r7, #0x0
	bne _020234CC
	ldr r0, _0202356C ; =0x000204A0
	mov r1, #0x0
	str r1, [r5, r0]
	add r1, r0, #0x4
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0x10]
	str r0, [r5, r1]
	ldr r0, [r4, #0x4]
	add r1, r6, #0x0
	lsl r0, r0, #0xc
	bl FUN_020235EC
	add sp, #0x14
	add r0, r6, #0x0
	pop {r4-r7, pc}
_020234CC:
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	bne _020234F6
	cmp r7, #0x1
	bne _020234F6
	ldr r0, _0202356C ; =0x000204A0
	mov r1, #0x1
	str r1, [r5, r0]
	add r1, r0, #0x4
	ldr r0, [sp, #0x4]
	ldr r2, [sp, #0x10]
	str r0, [r5, r1]
	ldr r0, [r4, #0x4]
	add r1, r6, #0x0
	add r0, #0x40
	lsl r0, r0, #0xc
	bl FUN_020235EC
	add sp, #0x14
	add r0, r6, #0x0
	pop {r4-r7, pc}
_020234F6:
	ldr r0, [sp, #0xc]
	cmp r0, #0x1
	bne _0202354C
	cmp r7, #0x1
	bne _0202354C
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0x4]
	bl FUN_020229B8
	mov r1, #0x0
	mvn r1, r1
	cmp r0, r1
	ldr r0, _0202356C ; =0x000204A0
	beq _0202352E
	mov r1, #0x0
	str r1, [r5, r0]
	add r1, r0, #0x4
	ldr r0, [sp, #0x8]
	ldr r2, [sp, #0x10]
	str r0, [r5, r1]
	ldr r0, [r4, #0x4]
	add r1, r6, #0x0
	lsl r0, r0, #0xc
	bl FUN_020235EC
	add sp, #0x14
	add r0, r6, #0x0
	pop {r4-r7, pc}
_0202352E:
	mov r1, #0x1
	str r1, [r5, r0]
	add r1, r0, #0x4
	ldr r0, [sp, #0x4]
	ldr r2, [sp, #0x10]
	str r0, [r5, r1]
	ldr r0, [r4, #0x4]
	add r1, r6, #0x0
	add r0, #0x40
	lsl r0, r0, #0xc
	bl FUN_020235EC
	add sp, #0x14
	add r0, r6, #0x0
	pop {r4-r7, pc}
_0202354C:
	ldr r0, [sp, #0x0]
	mov r1, #0x2
	str r1, [r0, #0x0]
	ldr r0, _0202356C ; =0x000204A0
	mov r1, #0x0
	str r1, [r5, r0]
	add r0, r0, #0x4
	str r1, [r5, r0]
	add r0, r6, #0x0
	add sp, #0x14
	pop {r4-r7, pc}
	nop
_02023564: .word UNK_020EE6D8
_02023568: .word UNK_020EE6E0
_0202356C: .word 0x000204A0

	thumb_func_start FUN_02023570
FUN_02023570: ; 0x02023570
	push {r3-r5, lr}
	bl OS_GetLockID
	add r4, r0, #0x0
	mov r0, #0x2
	mvn r0, r0
	cmp r4, r0
	bne _02023584
	bl ErrorHandling
_02023584:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl CARD_LockBackup
	ldr r0, _020235C8 ; =0x00001302
	bl CARD_IdentifyBackup
	cmp r0, #0x0
	beq _0202359A
	ldr r5, _020235C8 ; =0x00001302
	b _020235AA
_0202359A:
	ldr r0, _020235CC ; =0x00001202
	bl CARD_IdentifyBackup
	cmp r0, #0x0
	beq _020235A8
	ldr r5, _020235CC ; =0x00001202
	b _020235AA
_020235A8:
	mov r5, #0x0
_020235AA:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl CARD_UnlockBackup
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl OS_ReleaseLockID
	cmp r5, #0x0
	beq _020235C2
	mov r0, #0x1
	pop {r3-r5, pc}
_020235C2:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_020235C8: .word 0x00001302
_020235CC: .word 0x00001202

	thumb_func_start FUN_020235D0
FUN_020235D0: ; 0x020235D0
	push {r3-r5, lr}
	bl FUN_02023668
	add r5, r0, #0x0
	add r4, sp, #0x0
_020235DA:
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_020236E4
	cmp r0, #0x0
	beq _020235DA
	ldr r0, [sp, #0x0]
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020235EC
FUN_020235EC: ; 0x020235EC
	push {r4-r7, lr}
	sub sp, #0x14
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl OS_GetLockID
	add r4, r0, #0x0
	mov r0, #0x2
	mvn r0, r0
	cmp r4, r0
	bne _02023608
	bl ErrorHandling
_02023608:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl CARD_LockBackup
	mov r3, #0x0
	str r3, [sp, #0x0]
	mov r1, #0x1
	str r1, [sp, #0x4]
	mov r0, #0x6
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	str r3, [sp, #0x10]
	bl CARDi_RequestStreamCommand
	bl CARD_WaitBackupAsync
	add r5, r0, #0x0
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl CARD_UnlockBackup
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl OS_ReleaseLockID
	cmp r5, #0x0
	bne _02023652
	ldr r0, _02023658 ; =UNK_021C59C8
	ldr r0, [r0, #0x0]
	bl FreeToHeap
	mov r0, #0x1
	bl FUN_02089D90
_02023652:
	add r0, r5, #0x0
	add sp, #0x14
	pop {r4-r7, pc}
	.balign 4
_02023658: .word UNK_021C59C8

	thumb_func_start FUN_0202365C
FUN_0202365C: ; 0x0202365C
	ldr r0, _02023664 ; =UNK_021C59C8
	mov r1, #0x1
	str r1, [r0, #0x4]
	bx lr
	.balign 4
_02023664: .word UNK_021C59C8

	thumb_func_start FUN_02023668
FUN_02023668: ; 0x02023668
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r7, r2, #0x0
	bl OS_GetLockID
	add r4, r0, #0x0
	mov r0, #0x2
	mvn r0, r0
	cmp r4, r0
	bne _02023684
	bl ErrorHandling
_02023684:
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl CARD_LockBackup
	mov r0, #0x0
	str r0, [sp, #0x0]
	str r0, [sp, #0x4]
	mov r1, #0x6
	str r1, [sp, #0x8]
	mov r1, #0x1
	str r1, [sp, #0xc]
	add r1, sp, #0x14
	mov r2, #0x4
	add r3, r0, #0x0
	str r0, [sp, #0x10]
	bl CARDi_RequestStreamCommand
	cmp r0, #0x0
	bne _020236B2
	add r0, r4, #0x0
	mov r1, #0x1
	bl FUN_02023740
_020236B2:
	ldr r0, _020236DC ; =UNK_021C59C8
	mov r1, #0x0
	str r1, [r0, #0x4]
	str r1, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	mov r0, #0x7
	str r0, [sp, #0x8]
	mov r0, #0xa
	str r0, [sp, #0xc]
	mov r0, #0x2
	str r0, [sp, #0x10]
	ldr r3, _020236E0 ; =FUN_0202365C
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r7, #0x0
	bl CARDi_RequestStreamCommand
	add r0, r4, #0x0
	add sp, #0x18
	pop {r3-r7, pc}
	.balign 4
_020236DC: .word UNK_021C59C8
_020236E0: .word FUN_0202365C

	thumb_func_start FUN_020236E4
FUN_020236E4: ; 0x020236E4
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0202373C ; =UNK_021C59C8
	add r4, r1, #0x0
	ldr r0, [r0, #0x4]
	cmp r0, #0x1
	bne _02023738
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl CARD_UnlockBackup
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl OS_ReleaseLockID
	bl CARD_GetResultCode
	cmp r0, #0x0
	beq _02023714
	cmp r0, #0x4
	beq _0202371E
	cmp r0, #0x6
	beq _02023728
	b _0202371A
_02023714:
	mov r0, #0x1
	str r0, [r4, #0x0]
	b _02023734
_0202371A:
	bl ErrorHandling
_0202371E:
	mov r1, #0x0
	add r0, r5, #0x0
	str r1, [r4, #0x0]
	bl FUN_02023740
_02023728:
	mov r0, #0x0
	str r0, [r4, #0x0]
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02023740
_02023734:
	mov r0, #0x1
	pop {r3-r5, pc}
_02023738:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4
_0202373C: .word UNK_021C59C8

	thumb_func_start FUN_02023740
FUN_02023740: ; 0x02023740
	push {r3-r5, lr}
	add r5, r0, #0x0
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	add r4, r1, #0x0
	bl CARD_UnlockBackup
	lsl r0, r5, #0x10
	lsr r0, r0, #0x10
	bl OS_ReleaseLockID
	ldr r0, _02023768 ; =UNK_021C59C8
	ldr r0, [r0, #0x0]
	bl FreeToHeap
	mov r0, #0x1
	add r1, r4, #0x0
	bl FUN_0208A0B8
	pop {r3-r5, pc}
	.balign 4
_02023768: .word UNK_021C59C8
