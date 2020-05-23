    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020FA5FC

	.section .rodata

	.global UNK_020FCE14
UNK_020FCE14: ; 0x020FCE14
	.word FUN_02086084, FUN_02086168, FUN_020861DC, 0xFFFFFFFF

	.text

	thumb_func_start FUN_02086084
FUN_02086084: ; 0x02086084
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	bl FUN_02015F1C
	mov r2, #0x1
	mov r0, #0x3
	mov r1, #0x47
	lsl r2, r2, #0x12
	bl FUN_0201681C
	add r0, r5, #0x0
	mov r1, #0x80
	mov r2, #0x47
	bl FUN_02006268
	mov r1, #0x0
	mov r2, #0x80
	add r4, r0, #0x0
	bl memset
	add r0, r5, #0x0
	bl FUN_0200628C
	str r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02024FF4
	str r0, [r4, #0x10]
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02025084
	str r0, [r4, #0x14]
	bl FUN_02086468
	str r0, [r4, #0x38]
	mov r0, #0x47
	bl FUN_02006D98
	str r0, [r4, #0x3c]
	mov r0, #0x47
	bl FUN_02016B94
	str r0, [r4, #0x4]
	mov r0, #0x40
	mov r1, #0x47
	bl FUN_0201C24C
	mov r0, #0x47
	mov r1, #0x1
	mov r2, #0x0
	bl FUN_02014BF4
	str r0, [r4, #0x54]
	mov r0, #0x47
	bl FUN_02002FD0
	str r0, [r4, #0x8]
	mov r1, #0x1
	bl FUN_020038F0
	mov r2, #0x2
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	lsl r2, r2, #0x8
	mov r3, #0x47
	bl FUN_02003008
	mov r1, #0x2
	ldr r0, [r4, #0x8]
	lsl r2, r1, #0x8
	mov r3, #0x47
	bl FUN_02003008
	mov r1, #0x1
	ldr r0, [r4, #0x8]
	lsl r2, r1, #0x9
	mov r3, #0x47
	bl FUN_02003008
	mov r2, #0x2
	ldr r0, [r4, #0x8]
	mov r1, #0x3
	lsl r2, r2, #0x8
	mov r3, #0x47
	bl FUN_02003008
	bl FUN_02086414
	bl FUN_0208643C
	bl FUN_0208650C
	ldr r0, [r4, #0x4]
	bl FUN_0208654C
	add r0, r4, #0x4
	bl FUN_02086E48
	bl FUN_0200541C
	ldr r0, _02086164 ; =FUN_02086664
	add r1, r4, #0x0
	bl FUN_02015F10
	mov r0, #0x1
	pop {r3-r5, pc}
	nop
_02086164: .word FUN_02086664

	thumb_func_start FUN_02086168
FUN_02086168: ; 0x02086168
	push {r3-r5, lr}
	add r5, r1, #0x0
	bl FUN_02006278
	ldr r1, [r5, #0x0]
	add r4, r0, #0x0
	cmp r1, #0x0
	beq _0208617E
	cmp r1, #0x1
	beq _020861AA
	b _020861C6
_0208617E:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _0208618C
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
_0208618C:
	ldr r0, [r4, #0x0]
	mov r1, #0x5
	ldr r0, [r0, #0xc]
	mov r2, #0x0
	bl FUN_020671BC
	ldr r1, _020861D8 ; =0x000001EA
	cmp r0, r1
	bne _020861A4
	mov r0, #0x1
	str r0, [r4, #0x58]
	b _020861D2
_020861A4:
	mov r0, #0x0
	str r0, [r4, #0x58]
	b _020861D2
_020861AA:
	bl FUN_02086FA8
	cmp r0, #0x0
	bne _020861BA
	ldr r0, [r5, #0x0]
	add r0, r0, #0x1
	str r0, [r5, #0x0]
	b _020861D2
_020861BA:
	ldr r0, [r4, #0x3c]
	bl FUN_02006ED4
	bl FUN_02086698
	b _020861D2
_020861C6:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _020861D2
	mov r0, #0x1
	pop {r3-r5, pc}
_020861D2:
	mov r0, #0x0
	pop {r3-r5, pc}
	nop
_020861D8: .word 0x000001EA

	thumb_func_start FUN_020861DC
FUN_020861DC: ; 0x020861DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02006278
	add r4, r0, #0x0
	ldr r0, [r4, #0x38]
	bl FUN_020223BC
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0201E6E4
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_0201E6E4
	mov r0, #0x3
	mov r1, #0x0
	bl FUN_0201E6E4
	mov r0, #0x4
	mov r1, #0x0
	bl FUN_0201E74C
	ldr r0, [r4, #0x8]
	mov r1, #0x0
	bl FUN_02003038
	ldr r0, [r4, #0x8]
	mov r1, #0x2
	bl FUN_02003038
	ldr r0, [r4, #0x8]
	mov r1, #0x1
	bl FUN_02003038
	ldr r0, [r4, #0x8]
	mov r1, #0x3
	bl FUN_02003038
	ldr r0, [r4, #0x8]
	bl FUN_02002FEC
	ldr r0, [r4, #0x4]
	mov r1, #0x1
	bl FUN_020178A0
	ldr r0, [r4, #0x4]
	mov r1, #0x2
	bl FUN_020178A0
	ldr r0, [r4, #0x4]
	mov r1, #0x3
	bl FUN_020178A0
	ldr r0, [r4, #0x4]
	mov r1, #0x4
	bl FUN_020178A0
	ldr r0, [r4, #0x4]
	bl FUN_02016A18
	bl FUN_0201C29C
	ldr r0, [r4, #0x3c]
	bl FUN_020072E8
	ldr r0, [r4, #0x54]
	bl FUN_02014C28
	add r0, r4, #0x4
	bl FUN_02086ED4
	add r0, r5, #0x0
	bl FUN_0200627C
	mov r0, #0x47
	bl FUN_020168D0
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02086280
FUN_02086280: ; 0x02086280
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	bl FUN_0204652C
	add r4, r0, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x6
	bls _02086294
	b _020863CE
_02086294:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020862A0: ; jump table (using 16-bit offset)
	.short _020862AE - _020862A0 - 2; case 0
	.short _020862C4 - _020862A0 - 2; case 1
	.short _020862D6 - _020862A0 - 2; case 2
	.short _0208633A - _020862A0 - 2; case 3
	.short _02086396 - _020862A0 - 2; case 4
	.short _020863B6 - _020862A0 - 2; case 5
	.short _020863C4 - _020862A0 - 2; case 6
_020862AE:
	ldr r0, [r4, #0xc]
	mov r1, #0xb
	bl MOD05_021ED940
	add r0, r5, #0x0
	bl FUN_0204AF3C
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020863CE
_020862C4:
	ldr r1, _020863D4 ; =UNK_020FCE14
	add r0, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02046500
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020863CE
_020862D6:
	add r0, r5, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	ldr r5, [r4, #0xc]
	bl FUN_020377AC
	bl FUN_020238F4
	add r7, r0, #0x0
	ldr r0, [r6, #0x1c]
	ldr r0, [r0, #0x0]
	bl FUN_02034824
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	mov r1, #0x4c
	add r2, sp, #0x8
	bl FUN_02067830
	mov r0, #0xb
	str r0, [sp, #0x0]
	ldr r3, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x6
	bl FUN_0208089C
	add r0, r5, #0x0
	mov r1, #0xb2
	mov r2, #0x0
	bl FUN_02067830
	add r0, r6, #0x0
	bl FUN_020377AC
	ldr r1, [r4, #0xc]
	bl FUN_0202C144
	ldr r0, [r4, #0x4]
	cmp r0, #0x1
	bne _02086334
	mov r0, #0x3
	str r0, [r4, #0x0]
	b _020863CE
_02086334:
	mov r0, #0x5
	str r0, [r4, #0x0]
	b _020863CE
_0208633A:
	add r0, r5, #0x0
	bl FUN_02046528
	add r6, r0, #0x0
	ldr r0, [r4, #0xc]
	mov r1, #0x5
	mov r2, #0x0
	bl FUN_020671BC
	add r7, r0, #0x0
	add r0, r6, #0x0
	bl FUN_020377AC
	bl LoadPlayerDataAddress
	str r0, [sp, #0x0]
	mov r0, #0xb
	mov r1, #0x1
	add r2, r7, #0x0
	mov r3, #0xa
	bl FUN_02077A84
	str r0, [r4, #0x8]
	ldr r0, [r4, #0xc]
	mov r1, #0x6f
	mov r2, #0x0
	bl FUN_020671BC
	ldr r1, [r4, #0x8]
	mov r2, #0x0
	str r0, [r1, #0x10]
	ldr r0, [r4, #0xc]
	mov r1, #0x70
	bl FUN_020671BC
	ldr r1, [r4, #0x8]
	str r0, [r1, #0x8]
	ldr r1, _020863D8 ; =UNK_020FA5FC
	ldr r2, [r4, #0x8]
	add r0, r5, #0x0
	bl FUN_02046500
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020863CE
_02086396:
	ldr r2, [r4, #0x8]
	ldr r0, [r2, #0x14]
	cmp r0, #0x0
	bne _020863A8
	ldr r0, [r4, #0xc]
	ldr r2, [r2, #0x18]
	mov r1, #0x77
	bl FUN_02067830
_020863A8:
	ldr r0, [r4, #0x8]
	bl FUN_02077AC4
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020863CE
_020863B6:
	add r0, r5, #0x0
	bl FUN_0204AF84
	ldr r0, [r4, #0x0]
	add r0, r0, #0x1
	str r0, [r4, #0x0]
	b _020863CE
_020863C4:
	bl FUN_02016A18
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_020863CE:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_020863D4: .word UNK_020FCE14
_020863D8: .word UNK_020FA5FC

	thumb_func_start FUN_020863DC
FUN_020863DC: ; 0x020863DC
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r0, #0xb
	mov r1, #0x1c
	bl FUN_020169D8
	add r2, r0, #0x0
	add r3, r2, #0x0
	mov r1, #0x1c
	mov r0, #0x0
_020863F2:
	strb r0, [r3, #0x0]
	add r3, r3, #0x1
	sub r1, r1, #0x1
	bne _020863F2
	add r3, r2, #0x0
	add r3, #0xc
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r1, _02086410 ; =FUN_02086280
	add r0, r5, #0x0
	bl FUN_0204640C
	pop {r3-r5, pc}
	.balign 4
_02086410: .word FUN_02086280
