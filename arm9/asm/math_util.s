	.include "asm/macros.inc"
    .include "global.inc"

	.section .bss

	.global gLCRNG_State
gLCRNG_State: ; 0x021C4D48
	.space 4

	.global gMTRNG_State
gMTRNG_State: ; 0x021C4D4C
	.space 624 * 4

	.extern UNK_020EDC7E
	.extern UNK_020EDF50
	.extern UNK_020FFA38
	.extern UNK_02105BA8
	.extern UNK_02105BAC

	.text

	thumb_func_start FUN_0201B93C
FUN_0201B93C: ; 0x0201B93C
	mov r1, #0x5a
	lsl r1, r1, #0x2
	cmp r0, r1
	blo _0201B948
	mov r0, #0x0
	bx lr
_0201B948:
	lsl r1, r0, #0x2
	ldr r0, _0201B950 ; =UNK_020EDF50
	ldr r0, [r0, r1]
	bx lr
	.balign 4
_0201B950: .word UNK_020EDF50

	thumb_func_start FUN_0201B954
FUN_0201B954: ; 0x0201B954
	mov r1, #0x5a
	lsl r1, r1, #0x2
	cmp r0, r1
	blo _0201B960
	mov r0, #0x0
	bx lr
_0201B960:
	add r0, #0x5a
	lsl r1, r0, #0x2
	ldr r0, _0201B96C ; =UNK_020EDF50
	ldr r0, [r0, r1]
	bx lr
	nop
_0201B96C: .word UNK_020EDF50

	thumb_func_start FUN_0201B970
FUN_0201B970: ; 0x0201B970
	; gSineTable[x % 360]
	push {r3, lr}
	mov r1, #0x5a
	lsl r1, r1, #0x2
	bl _s32_div_f
	ldr r0, _0201B984 ; =UNK_020EDF50
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	pop {r3, pc}
	nop
_0201B984: .word UNK_020EDF50

	thumb_func_start FUN_0201B988
FUN_0201B988: ; 0x0201B988
	; gSineTable[(x % 360) + 90]
	push {r3, lr}
	mov r1, #0x5a
	lsl r1, r1, #0x2
	bl _s32_div_f
	add r1, #0x5a
	ldr r0, _0201B99C ; =UNK_020EDF50
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	pop {r3, pc}
	.balign 4
_0201B99C: .word UNK_020EDF50

	thumb_func_start FUN_0201B9A0
FUN_0201B9A0: ; 0x0201B9A0
	; UNK_020EDC7E[x % 360]
	push {r3, lr}
	mov r1, #0x5a
	lsl r1, r1, #0x2
	bl _s32_div_f
	ldr r0, _0201B9B4 ; =UNK_020EDC7E
	lsl r1, r1, #0x1
	ldrh r0, [r0, r1]
	pop {r3, pc}
	nop
_0201B9B4: .word UNK_020EDC7E

	thumb_func_start FUN_0201B9B8
FUN_0201B9B8: ; 0x0201B9B8
	; gSineTable[((x << 4) >> 16) % 360]
	push {r3, lr}
	lsl r0, r0, #0x4
	mov r1, #0x5a
	lsr r0, r0, #0x10
	lsl r1, r1, #0x2
	bl _s32_div_f
	ldr r0, _0201B9D0 ; =UNK_020EDF50
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	pop {r3, pc}
	nop
_0201B9D0: .word UNK_020EDF50

	thumb_func_start getseed_LC
getseed_LC: ; 0x0201B9D4
	ldr r0, _0201B9DC ; =gLCRNG_State
	ldr r0, [r0, #0x0]
	bx lr
	nop
_0201B9DC: .word gLCRNG_State

	thumb_func_start seedr_LC
seedr_LC: ; 0x0201B9E0
	ldr r1, _0201B9E8 ; =gLCRNG_State
	str r0, [r1, #0x0]
	bx lr
	nop
_0201B9E8: .word gLCRNG_State

	thumb_func_start rand_LC
rand_LC: ; 0x0201B9EC
	ldr r1, _0201BA04 ; =gLCRNG_State
	ldr r0, _0201BA08 ; =0x41C64E6D
	ldr r2, [r1, #0x0]
	add r3, r2, #0x0
	mul r3, r0
	ldr r0, _0201BA0C ; =0x00006073
	add r0, r3, r0
	str r0, [r1, #0x0]
	lsr r0, r0, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	bx lr
	.balign 4
_0201BA04: .word gLCRNG_State
_0201BA08: .word 0x41C64E6D
_0201BA0C: .word 0x00006073

	thumb_func_start rand_ALT
rand_ALT: ; 0x0201BA10
	ldr r1, _0201BA18 ; =0x6C078965
	mul r1, r0
	add r0, r1, #0x1
	bx lr
	.balign 4
_0201BA18: .word 0x6C078965

	thumb_func_start seedr_MT
seedr_MT: ; 0x0201BA1C
	push {r4-r5}
	ldr r1, _0201BA50 ; =gLCRNG_State
	mov r4, #0x27
	str r0, [r1, #0x4]
	ldr r1, _0201BA54 ; =UNK_02105BA8
	mov r0, #0x1
	str r0, [r1, #0x0]
	ldr r1, _0201BA58 ; =gMTRNG_State + 4
	ldr r3, _0201BA5C ; =0x6C078965
	lsl r4, r4, #0x4
_0201BA30:
	sub r2, r1, #0x4
	ldr r5, [r2, #0x0]
	lsr r2, r5, #0x1e
	eor r2, r5
	add r5, r2, #0x0
	mul r5, r3
	add r2, r0, r5
	add r0, r0, #0x1
	stmia r1!, {r2}
	cmp r0, r4
	blt _0201BA30
	ldr r1, _0201BA54 ; =UNK_02105BA8
	str r0, [r1, #0x0]
	pop {r4-r5}
	bx lr
	nop
_0201BA50: .word gLCRNG_State
_0201BA54: .word UNK_02105BA8
_0201BA58: .word gMTRNG_State + 4
_0201BA5C: .word 0x6C078965

	thumb_func_start rand_MT
rand_MT: ; 0x0201BA60
	push {r3-r7, lr}
	ldr r0, _0201BB44 ; =UNK_02105BA8
	ldr r1, [r0, #0x0]
	mov r0, #0x27
	lsl r0, r0, #0x4
	cmp r1, r0
	blt _0201BB18
	add r0, r0, #0x1
	cmp r1, r0
	bne _0201BA7A
	ldr r0, _0201BB48 ; =0x00001571
	bl seedr_MT
_0201BA7A:
	ldr r4, _0201BB4C ; =gMTRNG_State
	ldr r1, _0201BB50 ; =UNK_02105BAC
	ldr r5, _0201BB54 ; =0x7FFFFFFF
	ldr r6, _0201BB58 ; =0x00000634
	mov r0, #0x0
_0201BA84:
	mov r2, #0x2
	ldr r3, [r4, #0x0]
	lsl r2, r2, #0x1e
	and r3, r2
	ldr r2, [r4, #0x4]
	add r0, r0, #0x1
	and r2, r5
	orr r3, r2
	lsr r7, r3, #0x1
	lsl r3, r3, #0x1f
	ldr r2, [r4, r6]
	lsr r3, r3, #0x1d
	ldr r3, [r1, r3]
	eor r2, r7
	eor r2, r3
	stmia r4!, {r2}
	cmp r0, #0xe3
	blt _0201BA84
	ldr r1, _0201BB5C ; =0x0000026F
	cmp r0, r1
	bge _0201BAE4
	ldr r2, _0201BB4C ; =gMTRNG_State
	lsl r1, r0, #0x2
	add r1, r2, r1
	mov r2, #0xe3
	ldr r4, _0201BB50 ; =UNK_02105BAC
	ldr r3, _0201BB5C ; =0x0000026F
	lsl r2, r2, #0x2
_0201BABC:
	mov r5, #0x2
	ldr r6, [r1, #0x0]
	lsl r5, r5, #0x1e
	and r5, r6
	ldr r7, [r1, #0x4]
	ldr r6, _0201BB54 ; =0x7FFFFFFF
	add r0, r0, #0x1
	and r6, r7
	orr r6, r5
	lsr r5, r6, #0x1
	sub r7, r1, r2
	lsl r6, r6, #0x1f
	ldr r7, [r7, #0x0]
	lsr r6, r6, #0x1d
	ldr r6, [r4, r6]
	eor r5, r7
	eor r5, r6
	stmia r1!, {r5}
	cmp r0, r3
	blt _0201BABC
_0201BAE4:
	ldr r2, _0201BB60 ; =gMTRNG_State + 607 * 4
	mov r0, #0x2
	ldr r1, [r2, #0x40]
	lsl r0, r0, #0x1e
	add r3, r1, #0x0
	ldr r1, _0201BB64 ; =gLCRNG_State
	and r3, r0
	ldr r1, [r1, #0x4]
	sub r0, r0, #0x1
	and r0, r1
	add r4, r3, #0x0
	orr r4, r0
	ldr r0, _0201BB68 ; =gMTRNG_State + 383 * 4
	ldr r1, [r0, #0x34]
	lsr r0, r4, #0x1
	add r3, r1, #0x0
	eor r3, r0
	lsl r0, r4, #0x1f
	lsr r1, r0, #0x1d
	ldr r0, _0201BB50 ; =UNK_02105BAC
	ldr r0, [r0, r1]
	mov r1, #0x0
	eor r0, r3
	str r0, [r2, #0x40]
	ldr r0, _0201BB44 ; =UNK_02105BA8
	str r1, [r0, #0x0]
_0201BB18:
	ldr r0, _0201BB44 ; =UNK_02105BA8
	ldr r2, [r0, #0x0]
	add r1, r2, #0x1
	str r1, [r0, #0x0]
	ldr r0, _0201BB4C ; =gMTRNG_State
	lsl r1, r2, #0x2
	ldr r1, [r0, r1]
	lsr r0, r1, #0xb
	add r2, r1, #0x0
	eor r2, r0
	ldr r0, _0201BB6C ; =0x9D2C5680
	lsl r1, r2, #0x7
	and r0, r1
	eor r2, r0
	ldr r0, _0201BB70 ; =0xEFC60000
	lsl r1, r2, #0xf
	and r0, r1
	add r1, r2, #0x0
	eor r1, r0
	lsr r0, r1, #0x12
	eor r0, r1
	pop {r3-r7, pc}
	.balign 4
_0201BB44: .word UNK_02105BA8
_0201BB48: .word 0x00001571
_0201BB4C: .word gMTRNG_State
_0201BB50: .word UNK_02105BAC
_0201BB54: .word 0x7FFFFFFF
_0201BB58: .word 0x00000634
_0201BB5C: .word 0x0000026F
_0201BB60: .word gMTRNG_State + 607 * 4
_0201BB64: .word gLCRNG_State
_0201BB68: .word gMTRNG_State + 383 * 4
_0201BB6C: .word 0x9D2C5680
_0201BB70: .word 0xEFC60000

	thumb_func_start FUN_0201BB74
FUN_0201BB74: ; 0x0201BB74
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r0, sp, #0x0
	ldrb r0, [r0, #0x10]
	add r4, r2, #0x0
	add r6, r3, #0x0
	cmp r0, #0x1
	bne _0201BB8E
	ldr r0, _0201BBC8 ; =0x0000FFFF
	mul r0, r1
	lsl r0, r0, #0x8
	lsr r1, r0, #0x10
	b _0201BBA2
_0201BB8E:
	cmp r0, #0x2
	bne _0201BBA2
	ldr r0, _0201BBC8 ; =0x0000FFFF
	mul r0, r1
	mov r1, #0x5a
	lsl r1, r1, #0x2
	bl _u32_div_f
	lsl r0, r0, #0x10
	lsr r1, r0, #0x10
_0201BBA2:
	asr r0, r1, #0x4
	lsl r3, r0, #0x1
	lsl r1, r3, #0x1
	ldr r2, _0201BBCC ; =UNK_020FFA38
	add r3, r3, #0x1
	lsl r3, r3, #0x1
	ldrsh r1, [r2, r1]
	ldrsh r2, [r2, r3]
	add r0, r5, #0x0
	bl MTX_Rot22_
	add r0, r5, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	add r3, r6, #0x0
	bl MTX_ScaleApply22
	pop {r4-r6, pc}
	nop
_0201BBC8: .word 0x0000FFFF
_0201BBCC: .word UNK_020FFA38

	thumb_func_start FUN_0201BBD0
FUN_0201BBD0: ; 0x0201BBD0
	push {r3-r7, lr}
	sub sp, #0x38
	lsl r5, r0, #0xc
	lsl r4, r1, #0xc
	mov r1, #0x0
	lsl r0, r2, #0xc
	lsl r6, r3, #0xc
	str r1, [sp, #0x34]
	str r0, [sp, #0x0]
	str r0, [sp, #0x20]
	str r1, [sp, #0x28]
	str r1, [sp, #0x8]
	str r1, [sp, #0xc]
	asr r1, r5, #0x1f
	add r0, r5, #0x0
	asr r3, r6, #0x1f
	add r2, r6, #0x0
	str r5, [sp, #0x2c]
	str r4, [sp, #0x30]
	str r6, [sp, #0x24]
	bl _ll_mul
	str r0, [sp, #0x4]
	add r2, r4, #0x0
	ldr r0, [sp, #0x20]
	add r7, r1, #0x0
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #0x2
	ldr r3, [sp, #0x4]
	lsl r2, r2, #0xa
	add r3, r3, r2
	ldr r2, _0201BC80 ; =0x00000000
	str r4, [sp, #0x2c]
	adc r7, r2
	lsl r2, r7, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	mov r2, #0x2
	lsl r2, r2, #0xa
	add r0, r0, r2
	ldr r2, _0201BC80 ; =0x00000000
	str r5, [sp, #0x30]
	adc r1, r2
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	orr r0, r1
	sub r2, r3, r0
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	str r2, [sp, #0x10]
	add r0, r1, r0
	add r7, r2, r0
	mov r0, #0x0
	str r0, [sp, #0x34]
	add r0, sp, #0x2c
	add r1, sp, #0x14
	bl VEC_Normalize
	mov r1, #0x0
	ldr r0, [sp, #0x0]
	str r1, [sp, #0x34]
	str r0, [sp, #0x20]
	str r1, [sp, #0x28]
	add r0, sp, #0x20
	add r1, sp, #0x2c
	add r2, sp, #0x8
	str r5, [sp, #0x2c]
	str r4, [sp, #0x30]
	str r6, [sp, #0x24]
	bl VEC_Subtract
	add r0, sp, #0x14
	add r1, sp, #0x8
	bl VEC_DotProduct
	asr r0, r0, #0xc
	bpl _0201BC72
	neg r0, r0
_0201BC72:
	cmp r7, #0x0
	bgt _0201BC7C
	mov r1, #0x0
	mvn r1, r1
	mul r0, r1
_0201BC7C:
	add sp, #0x38
	pop {r3-r7, pc}
	.balign 4
_0201BC80: .word 0x00000000

	thumb_func_start FUN_0201BC84
FUN_0201BC84: ; 0x0201BC84
	push {r3-r5, lr}
	lsl r0, r0, #0xd
	add r4, r1, #0x0
	ldr r2, _0201BCB4 ; =0x0000323D
	asr r1, r0, #0x1f
	mov r3, #0x0
	bl _ll_mul
	add r5, r0, #0x0
	ldr r0, _0201BCB8 ; =0x0000FFFF
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	mul r0, r4
	add r2, r5, r2
	adc r1, r3
	lsl r1, r1, #0x14
	lsr r2, r2, #0xc
	orr r2, r1
	asr r1, r2, #0xc
	bl _s32_div_f
	pop {r3-r5, pc}
	nop
_0201BCB4: .word 0x0000323D
_0201BCB8: .word 0x0000FFFF
