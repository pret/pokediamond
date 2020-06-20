    .include "asm/macros.inc"
    .include "global.inc"

	.extern gUnknown21C48B8

	.section .rodata

	.global UNK_020FF304
UNK_020FF304: ; 0x020FF304
	.byte 0x00, 0x02, 0x13, 0x1B, 0x04, 0x01, 0x6D, 0x01

	.global UNK_020FF30C
UNK_020FF30C: ; 0x020FF30C
	.byte 0x00, 0x19, 0x0D, 0x06, 0x04, 0x01, 0x55, 0x01

	.global UNK_020FF314
UNK_020FF314: ; 0x020FF314
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FF324
UNK_020FF324: ; 0x020FF324
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FF340
UNK_020FF340: ; 0x020FF340
	.byte 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_020FF368
UNK_020FF368: ; 0x020FF368
	.word FUN_02089498, FUN_020894D4, FUN_020895F0, 0xFFFFFFFF

	.text

	thumb_func_start FUN_02089498
FUN_02089498: ; 0x02089498
	push {r3-r5, lr}
	mov r2, #0x2
	add r5, r0, #0x0
	mov r0, #0x3
	mov r1, #0x58
	lsl r2, r2, #0x10
	bl FUN_0201681C
	add r0, r5, #0x0
	mov r1, #0x38
	mov r2, #0x58
	bl FUN_02006268
	mov r1, #0x0
	mov r2, #0x38
	add r4, r0, #0x0
	bl memset
	mov r0, #0x58
	str r0, [r4, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	add r0, r5, #0x0
	bl FUN_0200628C
	ldr r0, [r0, #0x8]
	str r0, [r4, #0x30]
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_020894D4
FUN_020894D4: ; 0x020894D4
	push {r3-r6, lr}
	sub sp, #0xc
	add r5, r1, #0x0
	bl FUN_02006278
	ldr r1, [r5, #0x0]
	add r4, r0, #0x0
	mov r6, #0x0
	cmp r1, #0x3
	bhi _020895DA
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020894F4: ; jump table (using 16-bit offset)
	.short _020894FC - _020894F4 - 2; case 0
	.short _02089588 - _020894F4 - 2; case 1
	.short _02089596 - _020894F4 - 2; case 2
	.short _020895BC - _020894F4 - 2; case 3
_020894FC:
	ldr r0, _020895E0 ; =0x00000495
	add r1, r6, #0x0
	bl FUN_02005350
	add r0, r6, #0x0
	bl FUN_0200516C
	add r0, r6, #0x0
	bl FUN_0200415C
	add r0, r6, #0x0
	add r1, r0, #0x0
	bl FUN_0200E3A0
	mov r0, #0x1
	add r1, r6, #0x0
	bl FUN_0200E3A0
	add r0, r6, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	add r0, r6, #0x0
	add r1, r0, #0x0
	bl FUN_02015F34
	bl FUN_0201E6D8
	bl FUN_0201E740
	mov r2, #0x1
	lsl r2, r2, #0x1a
	ldr r1, [r2, #0x0]
	ldr r0, _020895E4 ; =0xFFFFE0FF
	and r1, r0
	str r1, [r2, #0x0]
	ldr r2, _020895E8 ; =0x04001000
	ldr r1, [r2, #0x0]
	and r0, r1
	str r0, [r2, #0x0]
	mov r0, #0x4
	mov r1, #0x8
	bl FUN_0201669C
	add r0, r4, #0x0
	bl FUN_0208961C
	add r0, r4, #0x0
	bl FUN_02089734
	ldr r0, _020895EC ; =FUN_02089610
	add r1, r4, #0x0
	bl FUN_02015F10
	bl FUN_0201E788
	mov r0, #0x6
	mov r1, #0x1
	str r0, [sp, #0x0]
	str r1, [sp, #0x4]
	ldr r0, [r4, #0x0]
	add r2, r1, #0x0
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	mov r0, #0x1
	str r0, [r5, #0x0]
	b _020895DA
_02089588:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _020895DA
	mov r0, #0x2
	str r0, [r5, #0x0]
	b _020895DA
_02089596:
	bl FUN_02089790
	cmp r0, #0x1
	bne _020895DA
	mov r0, #0x6
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x0]
	str r0, [sp, #0x8]
	add r0, r6, #0x0
	add r1, r0, #0x0
	add r2, r0, #0x0
	add r3, r0, #0x0
	bl FUN_0200E1D0
	mov r0, #0x3
	str r0, [r5, #0x0]
	b _020895DA
_020895BC:
	bl FUN_0200E308
	cmp r0, #0x1
	bne _020895DA
	add r0, r4, #0x0
	bl FUN_0208977C
	add r0, r4, #0x0
	bl FUN_020896E0
	add r0, r6, #0x0
	add r1, r0, #0x0
	bl FUN_02015F10
	mov r6, #0x1
_020895DA:
	add r0, r6, #0x0
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4
_020895E0: .word 0x00000495
_020895E4: .word 0xFFFFE0FF
_020895E8: .word 0x04001000
_020895EC: .word FUN_02089610

	thumb_func_start FUN_020895F0
FUN_020895F0: ; 0x020895F0
	push {r3-r5, lr}
	add r5, r0, #0x0
	bl FUN_02006278
	ldr r4, [r0, #0x0]
	add r0, r5, #0x0
	bl FUN_0200627C
	add r0, r4, #0x0
	bl FUN_020168D0
	mov r0, #0x0
	bl OS_ResetSystem
	mov r0, #0x1
	pop {r3-r5, pc}

	thumb_func_start FUN_02089610
FUN_02089610: ; 0x02089610
	ldr r3, _02089618 ; =FUN_0201AB60
	ldr r0, [r0, #0x14]
	bx r3
	nop
_02089618: .word FUN_0201AB60

	thumb_func_start FUN_0208961C
FUN_0208961C: ; 0x0208961C
	push {r4-r5, lr}
	sub sp, #0x5c
	ldr r5, _020896C8 ; =UNK_020FF340
	add r4, r0, #0x0
	add r3, sp, #0x34
	mov r2, #0x5
_02089628:
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _02089628
	add r0, sp, #0x34
	bl FUN_0201E66C
	ldr r0, [r4, #0x0]
	bl FUN_02016B94
	add r3, sp, #0x24
	ldr r5, _020896CC ; =UNK_020FF314
	str r0, [r4, #0x14]
	add r2, r3, #0x0
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	bl FUN_02016BBC
	ldr r5, _020896D0 ; =UNK_020FF324
	add r3, sp, #0x8
	ldmia r5!, {r0-r1}
	add r2, r3, #0x0
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r5, #0x0]
	mov r1, #0x0
	str r0, [r3, #0x0]
	ldr r0, [r4, #0x14]
	add r3, r1, #0x0
	bl FUN_02016C18
	ldr r0, [r4, #0x14]
	mov r1, #0x0
	bl FUN_02018744
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r2, _020896D4 ; =0x000001E2
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x14]
	mov r3, #0x2
	bl FUN_0200CD68
	mov r1, #0x0
	str r1, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r2, _020896D8 ; =0x000001D9
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x14]
	mov r3, #0x3
	bl FUN_0200CB00
	ldr r2, [r4, #0x0]
	mov r0, #0x0
	mov r1, #0x20
	bl FUN_02002ED0
	mov r0, #0x0
	ldr r3, [r4, #0x0]
	mov r1, #0x20
	add r2, r0, #0x0
	bl FUN_02017F18
	ldr r1, _020896DC ; =0x00006C21
	mov r0, #0x0
	bl FUN_02017FE4
	ldr r1, _020896DC ; =0x00006C21
	mov r0, #0x4
	bl FUN_02017FE4
	add sp, #0x5c
	pop {r4-r5, pc}
	.balign 4
_020896C8: .word UNK_020FF340
_020896CC: .word UNK_020FF314
_020896D0: .word UNK_020FF324
_020896D4: .word 0x000001E2
_020896D8: .word 0x000001D9
_020896DC: .word 0x00006C21

	thumb_func_start FUN_020896E0
FUN_020896E0: ; 0x020896E0
	push {r4, lr}
	add r4, r0, #0x0
	mov r0, #0x0
	add r1, r0, #0x0
	bl FUN_0201797C
	mov r0, #0x1
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x2
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x3
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x4
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x5
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x6
	mov r1, #0x0
	bl FUN_0201797C
	mov r0, #0x7
	mov r1, #0x0
	bl FUN_0201797C
	ldr r0, [r4, #0x14]
	mov r1, #0x0
	bl FUN_020178A0
	ldr r0, [r4, #0x14]
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start FUN_02089734
FUN_02089734: ; 0x02089734
	push {r4, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	ldr r3, [r4, #0x0]
	mov r0, #0x1
	mov r1, #0x1a
	mov r2, #0x4
	bl NewMsgDataFromNarc
	str r0, [r4, #0x18]
	bl FUN_0201BD5C
	mov r0, #0x0
	str r0, [r4, #0x8]
	add r1, r4, #0x0
	ldr r0, [r4, #0x14]
	ldr r2, _02089778 ; =UNK_020FF304
	add r1, #0x1c
	bl FUN_02019150
	mov r0, #0xd8
	str r0, [sp, #0x0]
	mov r0, #0x20
	mov r2, #0x0
	add r4, #0x1c
	str r0, [sp, #0x4]
	add r0, r4, #0x0
	mov r1, #0xf
	add r3, r2, #0x0
	bl FUN_020196F4
	add sp, #0x8
	pop {r4, pc}
	nop
_02089778: .word UNK_020FF304

	thumb_func_start FUN_0208977C
FUN_0208977C: ; 0x0208977C
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x1c
	bl FUN_02019178
	ldr r0, [r4, #0x18]
	bl DestroyMsgData
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02089790
FUN_02089790: ; 0x02089790
	push {r3-r5, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	ldr r1, [r4, #0x4]
	mov r5, #0x0
	cmp r1, #0x6
	bhi _02089888
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_020897AA: ; jump table (using 16-bit offset)
	.short _020897B8 - _020897AA - 2; case 0
	.short _020897E2 - _020897AA - 2; case 1
	.short _02089802 - _020897AA - 2; case 2
	.short _0208982C - _020897AA - 2; case 3
	.short _0208984C - _020897AA - 2; case 4
	.short _0208986C - _020897AA - 2; case 5
	.short _0208987E - _020897AA - 2; case 6
_020897B8:
	add r1, r5, #0x0
	mov r2, #0x1
	mov r3, #0x4
	bl FUN_0208989C
	cmp r0, #0x1
	bne _02089888
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r1, _02089890 ; =UNK_020FF30C
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x14]
	ldr r2, _02089894 ; =0x000001D9
	mov r3, #0x3
	bl FUN_020020EC
	str r0, [r4, #0x2c]
	mov r0, #0x1
	str r0, [r4, #0x4]
	b _02089888
_020897E2:
	ldr r0, [r4, #0x2c]
	ldr r1, [r4, #0x0]
	bl FUN_020021AC
	cmp r0, #0x0
	beq _020897F6
	sub r1, r5, #0x2
	cmp r0, r1
	beq _020897FC
	b _02089888
_020897F6:
	mov r0, #0x2
	str r0, [r4, #0x4]
	b _02089888
_020897FC:
	mov r0, #0x6
	str r0, [r4, #0x4]
	b _02089888
_02089802:
	mov r1, #0x1
	add r2, r1, #0x0
	mov r3, #0x4
	bl FUN_0208989C
	cmp r0, #0x1
	bne _02089888
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x0]
	ldr r1, _02089890 ; =UNK_020FF30C
	str r0, [sp, #0x4]
	ldr r0, [r4, #0x14]
	ldr r2, _02089894 ; =0x000001D9
	mov r3, #0x3
	bl FUN_020020EC
	str r0, [r4, #0x2c]
	mov r0, #0x3
	str r0, [r4, #0x4]
	b _02089888
_0208982C:
	ldr r0, [r4, #0x2c]
	ldr r1, [r4, #0x0]
	bl FUN_020021AC
	cmp r0, #0x0
	beq _02089840
	sub r1, r5, #0x2
	cmp r0, r1
	beq _02089846
	b _02089888
_02089840:
	mov r0, #0x4
	str r0, [r4, #0x4]
	b _02089888
_02089846:
	mov r0, #0x6
	str r0, [r4, #0x4]
	b _02089888
_0208984C:
	mov r1, #0x2
	mov r2, #0x1
	add r3, r5, #0x0
	bl FUN_0208989C
	cmp r0, #0x1
	bne _02089888
	add r0, r4, #0x0
	ldr r1, _02089898 ; =0x000001E2
	add r0, #0x1c
	bl FUN_0200D858
	str r0, [r4, #0x34]
	mov r0, #0x5
	str r0, [r4, #0x4]
	b _02089888
_0208986C:
	ldr r0, [r4, #0x30]
	bl FUN_0202263C
	ldr r0, [r4, #0x34]
	bl FUN_0200DBFC
	mov r0, #0x6
	str r0, [r4, #0x4]
	b _02089888
_0208987E:
	ldr r0, [r4, #0x14]
	add r1, r5, #0x0
	bl FUN_02018744
	mov r5, #0x1
_02089888:
	add r0, r5, #0x0
	add sp, #0x8
	pop {r3-r5, pc}
	nop
_02089890: .word UNK_020FF30C
_02089894: .word 0x000001D9
_02089898: .word 0x000001E2

	thumb_func_start FUN_0208989C
FUN_0208989C: ; 0x0208989C
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	ldr r0, [r5, #0x8]
	add r7, r1, #0x0
	add r4, r3, #0x0
	mov r6, #0x0
	cmp r0, #0x0
	beq _020898B8
	cmp r0, #0x1
	beq _02089920
	cmp r0, #0x2
	beq _0208993C
	b _02089950
_020898B8:
	mov r0, #0xd8
	str r0, [sp, #0x0]
	mov r0, #0x20
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	add r0, #0x1c
	mov r1, #0xf
	add r2, r6, #0x0
	add r3, r6, #0x0
	bl FUN_020196F4
	add r0, r5, #0x0
	ldr r2, _02089958 ; =0x000001E2
	add r0, #0x1c
	add r1, r6, #0x0
	mov r3, #0x2
	bl FUN_0200D0BC
	mov r0, #0x1
	ldr r1, [r5, #0x0]
	lsl r0, r0, #0xa
	bl String_ctor
	str r0, [r5, #0x10]
	ldr r0, [r5, #0x18]
	ldr r2, [r5, #0x10]
	add r1, r7, #0x0
	bl ReadMsgDataIntoString
	add r3, r6, #0x0
	str r3, [sp, #0x0]
	str r4, [sp, #0x4]
	str r3, [sp, #0x8]
	add r0, r5, #0x0
	ldr r2, [r5, #0x10]
	add r0, #0x1c
	mov r1, #0x1
	bl FUN_0201BD84
	str r0, [r5, #0xc]
	cmp r4, #0x0
	bne _02089918
	ldr r0, [r5, #0x10]
	bl String_dtor
	ldr r0, [r5, #0x8]
	add r0, r0, #0x1
	str r0, [r5, #0x8]
_02089918:
	ldr r0, [r5, #0x8]
	add r0, r0, #0x1
	str r0, [r5, #0x8]
	b _02089950
_02089920:
	ldr r0, [r5, #0xc]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _02089950
	ldr r0, [r5, #0x10]
	bl String_dtor
	ldr r0, [r5, #0x8]
	add r0, r0, #0x1
	str r0, [r5, #0x8]
	b _02089950
_0208993C:
	cmp r2, #0x0
	bne _0208994A
	ldr r0, _0208995C ; =gUnknown21C48B8
	ldr r1, [r0, #0x48]
	mov r0, #0x1
	tst r0, r1
	beq _02089950
_0208994A:
	mov r0, #0x0
	str r0, [r5, #0x8]
	mov r6, #0x1
_02089950:
	add r0, r6, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02089958: .word 0x000001E2
_0208995C: .word gUnknown21C48B8
