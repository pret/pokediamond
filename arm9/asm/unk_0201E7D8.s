	.include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_021C59A4
	.extern UNK_021CED98
	.extern UNK_021CEF64
	.extern UNK_021CED20
	.extern UNK_020FFA38
	.extern UNK_02105BB8
	.extern UNK_021CEF58
	.extern UNK_021CEF70
	.extern UNK_021CED64

	.text

	thumb_func_start FUN_0201E7D8
FUN_0201E7D8: ; 0x0201E7D8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x3e]
	ldr r2, [r5, #0x38]
	ldrh r4, [r5, #0x3c]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _0201E8B4 ; =UNK_020FFA38
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r0, r0, r2
	adc r1, r3
	asr r2, r4, #0x4
	lsl r2, r2, #0x1
	add r2, r2, #0x1
	lsl r3, r2, #0x1
	ldr r2, _0201E8B4 ; =UNK_020FFA38
	lsl r1, r1, #0x14
	ldrsh r2, [r2, r3]
	lsr r0, r0, #0xc
	orr r0, r1
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	str r1, [r5, #0x14]
	ldrh r0, [r5, #0x3e]
	ldr r2, [r5, #0x38]
	asr r0, r0, #0x4
	lsl r0, r0, #0x1
	add r0, r0, #0x1
	lsl r1, r0, #0x1
	ldr r0, _0201E8B4 ; =UNK_020FFA38
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	lsl r2, r2, #0xa
	mov r3, #0x0
	add r0, r0, r2
	adc r1, r3
	ldrh r2, [r5, #0x3c]
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	asr r2, r2, #0x4
	lsl r2, r2, #0x1
	add r2, r2, #0x1
	lsl r3, r2, #0x1
	ldr r2, _0201E8B4 ; =UNK_020FFA38
	orr r0, r1
	ldrsh r2, [r2, r3]
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	neg r0, r4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r1, [r5, #0x1c]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _0201E8B4 ; =UNK_020FFA38
	ldr r2, [r5, #0x38]
	ldrsh r0, [r0, r1]
	asr r3, r2, #0x1f
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	add r0, r5, #0x0
	str r1, [r5, #0x18]
	add r0, #0x14
	add r5, #0x20
	add r1, r5, #0x0
	add r2, r0, #0x0
	bl VEC_Add
	pop {r3-r5, pc}
	nop
_0201E8B4: .word UNK_020FFA38

	thumb_func_start FUN_0201E8B8
FUN_0201E8B8: ; 0x0201E8B8
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldrh r0, [r5, #0x3e]
	ldr r2, [r5, #0x38]
	ldrh r4, [r5, #0x3c]
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _0201E998 ; =UNK_020FFA38
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r0, r0, r2
	adc r1, r3
	asr r2, r4, #0x4
	lsl r2, r2, #0x1
	add r2, r2, #0x1
	lsl r3, r2, #0x1
	ldr r2, _0201E998 ; =UNK_020FFA38
	lsl r1, r1, #0x14
	ldrsh r2, [r2, r3]
	lsr r0, r0, #0xc
	orr r0, r1
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	neg r0, r1
	str r0, [r5, #0x20]
	ldrh r0, [r5, #0x3e]
	ldr r2, [r5, #0x38]
	asr r0, r0, #0x4
	lsl r0, r0, #0x1
	add r0, r0, #0x1
	lsl r1, r0, #0x1
	ldr r0, _0201E998 ; =UNK_020FFA38
	asr r3, r2, #0x1f
	ldrsh r0, [r0, r1]
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	lsl r2, r2, #0xa
	mov r3, #0x0
	add r0, r0, r2
	adc r1, r3
	ldrh r2, [r5, #0x3c]
	lsl r1, r1, #0x14
	lsr r0, r0, #0xc
	asr r2, r2, #0x4
	lsl r2, r2, #0x1
	add r2, r2, #0x1
	lsl r3, r2, #0x1
	ldr r2, _0201E998 ; =UNK_020FFA38
	orr r0, r1
	ldrsh r2, [r2, r3]
	asr r1, r0, #0x1f
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	neg r0, r1
	str r0, [r5, #0x28]
	neg r0, r4
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r0, r0, #0x4
	lsl r1, r0, #0x2
	ldr r0, _0201E998 ; =UNK_020FFA38
	ldr r2, [r5, #0x38]
	ldrsh r0, [r0, r1]
	asr r3, r2, #0x1f
	asr r1, r0, #0x1f
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsl r0, r1, #0x14
	lsr r1, r2, #0xc
	orr r1, r0
	neg r0, r1
	str r0, [r5, #0x24]
	add r0, r5, #0x0
	add r0, #0x20
	add r5, #0x14
	add r1, r5, #0x0
	add r2, r0, #0x0
	bl VEC_Add
	pop {r3-r5, pc}
	.balign 4
_0201E998: .word UNK_020FFA38

	thumb_func_start FUN_0201E99C
FUN_0201E99C: ; 0x0201E99C
	add r2, r1, #0x0
	add r2, #0x46
	strh r0, [r2, #0x0]
	asr r0, r0, #0x4
	lsl r3, r0, #0x1
	ldr r2, _0201E9E0 ; =UNK_020FFA38
	lsl r0, r3, #0x1
	ldrsh r0, [r2, r0]
	str r0, [r1, #0x0]
	add r0, r3, #0x1
	lsl r0, r0, #0x1
	ldrsh r0, [r2, r0]
	mov r2, #0x0
	str r0, [r1, #0x4]
	ldr r0, _0201E9E4 ; =0x00001555
	str r0, [r1, #0x8]
	mov r0, #0x96
	lsl r0, r0, #0xc
	str r0, [r1, #0xc]
	mov r0, #0xe1
	lsl r0, r0, #0xe
	str r0, [r1, #0x10]
	mov r0, #0x1
	str r2, [r1, #0x2c]
	lsl r0, r0, #0xc
	str r0, [r1, #0x30]
	str r2, [r1, #0x34]
	str r2, [r1, #0x54]
	str r2, [r1, #0x58]
	str r2, [r1, #0x5c]
	str r2, [r1, #0x60]
	str r2, [r1, #0x64]
	bx lr
	nop
_0201E9E0: .word UNK_020FFA38
_0201E9E4: .word 0x00001555

	thumb_func_start FUN_0201E9E8
FUN_0201E9E8: ; 0x0201E9E8
	ldr r2, [r0, #0x58]
	cmp r2, #0x0
	bne _0201E9F2
	mov r2, #0x0
	str r2, [r1, #0x0]
_0201E9F2:
	ldr r2, [r0, #0x5c]
	cmp r2, #0x0
	bne _0201E9FC
	mov r2, #0x0
	str r2, [r1, #0x4]
_0201E9FC:
	ldr r0, [r0, #0x60]
	cmp r0, #0x0
	bne _0201EA06
	mov r0, #0x0
	str r0, [r1, #0x8]
_0201EA06:
	bx lr

	thumb_func_start FUN_0201EA08
FUN_0201EA08: ; 0x0201EA08
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r7, [r5, #0x64]
	add r4, r1, #0x0
	add r6, r2, #0x0
	cmp r7, #0x0
	bne _0201EA20
	ldmia r4!, {r0-r1}
	stmia r6!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r6, #0x0]
	pop {r3-r7, pc}
_0201EA20:
	add r0, r7, #0x0
	str r0, [sp, #0x0]
	add r0, #0x8
	str r0, [sp, #0x0]
	ldr r0, [r7, #0x10]
	cmp r0, #0x0
	bne _0201EA48
	add r3, r4, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldr r0, [r5, #0x64]
	ldr r2, [r7, #0x4]
	ldr r1, [r0, #0xc]
	cmp r2, r1
	bne _0201EA5C
	mov r1, #0x1
	str r1, [r0, #0x10]
	b _0201EA5C
_0201EA48:
	ldr r2, [r7, #0x4]
	mov r1, #0xc
	mul r1, r2
	ldr r0, [r7, #0x20]
	add r2, r6, #0x0
	add r3, r0, r1
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
_0201EA5C:
	ldr r1, [r5, #0x64]
	ldr r0, [r7, #0x4]
	ldr r1, [r1, #0x0]
	add r0, r0, #0x1
	bl _s32_div_f
	str r1, [r7, #0x4]
	ldr r1, [sp, #0x0]
	ldr r0, [r5, #0x64]
	ldr r2, [r1, #0x0]
	mov r1, #0xc
	ldr r0, [r0, #0x20]
	mul r1, r2
	add r3, r4, #0x0
	add r2, r0, r1
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	ldr r0, [sp, #0x0]
	ldr r1, [r5, #0x64]
	ldr r0, [r0, #0x0]
	ldr r1, [r1, #0x0]
	add r0, r0, #0x1
	bl _s32_div_f
	ldr r0, [sp, #0x0]
	str r1, [r0, #0x0]
	ldr r0, [r5, #0x64]
	ldr r0, [r0, #0x14]
	cmp r0, #0x0
	bne _0201EAA0
	ldr r0, [r4, #0x0]
	str r0, [r6, #0x0]
_0201EAA0:
	ldr r0, [r5, #0x64]
	ldr r0, [r0, #0x18]
	cmp r0, #0x0
	bne _0201EAAC
	ldr r0, [r4, #0x4]
	str r0, [r6, #0x4]
_0201EAAC:
	ldr r0, [r5, #0x64]
	ldr r0, [r0, #0x1c]
	cmp r0, #0x0
	bne _0201EAB8
	ldr r0, [r4, #0x8]
	str r0, [r6, #0x8]
_0201EAB8:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201EABC
FUN_0201EABC: ; 0x0201EABC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, [sp, #0x18]
	add r7, r1, #0x0
	str r0, [sp, #0x18]
	ldr r0, [r0, #0x54]
	add r6, r2, #0x0
	str r3, [sp, #0x0]
	cmp r0, #0x0
	beq _0201EB46
	add r0, r7, #0x1
	cmp r0, r5
	ble _0201EADA
	bl ErrorHandling
_0201EADA:
	ldr r0, [sp, #0x0]
	mov r1, #0x24
	bl FUN_02016998
	add r4, r0, #0x0
	mov r1, #0xc
	ldr r0, [sp, #0x0]
	mul r1, r5
	bl FUN_02016998
	mov r1, #0x0
	str r0, [r4, #0x20]
	cmp r5, #0x0
	ble _0201EB12
	add r2, r1, #0x0
	add r0, r1, #0x0
_0201EAFA:
	ldr r3, [r4, #0x20]
	add r1, r1, #0x1
	str r0, [r3, r2]
	ldr r3, [r4, #0x20]
	add r3, r3, r2
	str r0, [r3, #0x4]
	ldr r3, [r4, #0x20]
	add r3, r3, r2
	str r0, [r3, #0x8]
	add r2, #0xc
	cmp r1, r5
	blt _0201EAFA
_0201EB12:
	str r5, [r4, #0x0]
	mov r0, #0x0
	str r0, [r4, #0x4]
	str r7, [r4, #0x8]
	str r7, [r4, #0xc]
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	str r0, [r4, #0x18]
	str r0, [r4, #0x1c]
	mov r0, #0x1
	add r1, r6, #0x0
	tst r1, r0
	beq _0201EB2E
	str r0, [r4, #0x14]
_0201EB2E:
	mov r0, #0x2
	tst r0, r6
	beq _0201EB38
	mov r0, #0x1
	str r0, [r4, #0x18]
_0201EB38:
	mov r0, #0x4
	tst r0, r6
	beq _0201EB42
	mov r0, #0x1
	str r0, [r4, #0x1c]
_0201EB42:
	ldr r0, [sp, #0x18]
	str r4, [r0, #0x64]
_0201EB46:
	pop {r3-r7, pc}

	thumb_func_start FUN_0201EB48
FUN_0201EB48: ; 0x0201EB48
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x64]
	cmp r0, #0x0
	beq _0201EB62
	ldr r0, [r0, #0x20]
	bl FUN_02016A18
	ldr r0, [r4, #0x64]
	bl FUN_02016A18
	mov r0, #0x0
	str r0, [r4, #0x64]
_0201EB62:
	pop {r4, pc}

	thumb_func_start FUN_0201EB64
FUN_0201EB64: ; 0x0201EB64
	ldr r3, _0201EB6C ; =FUN_02016998
	mov r1, #0x68
	bx r3
	nop
_0201EB6C: .word FUN_02016998

	thumb_func_start FUN_0201EB70
FUN_0201EB70: ; 0x0201EB70
	ldr r3, _0201EB74 ; =FUN_02016A18
	bx r3
	.balign 4
_0201EB74: .word FUN_02016A18

	thumb_func_start FUN_0201EB78
FUN_0201EB78: ; 0x0201EB78
	push {r3-r4}
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r2, #0xd
_0201EB80:
	ldmia r4!, {r0-r1}
	stmia r3!, {r0-r1}
	sub r2, r2, #0x1
	bne _0201EB80
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0201EB8C
FUN_0201EB8C: ; 0x0201EB8C
	ldr r1, _0201EB94 ; =UNK_021C59A4
	str r0, [r1, #0x0]
	bx lr
	nop
_0201EB94: .word UNK_021C59A4

	thumb_func_start FUN_0201EB98
FUN_0201EB98: ; 0x0201EB98
	ldr r0, _0201EBA0 ; =UNK_021C59A4
	mov r1, #0x0
	str r1, [r0, #0x0]
	bx lr
	.balign 4
_0201EBA0: .word UNK_021C59A4

	thumb_func_start FUN_0201EBA4
FUN_0201EBA4: ; 0x0201EBA4
	push {r3-r6, lr}
	sub sp, #0x1c
	ldr r0, _0201EC40 ; =UNK_021C59A4
	ldr r1, [r0, #0x0]
	cmp r1, #0x0
	beq _0201EC3A
	ldr r0, [r1, #0x54]
	cmp r0, #0x0
	beq _0201EBEE
	add r1, #0x48
	add r2, sp, #0x10
	bl VEC_Subtract
	ldr r0, _0201EC40 ; =UNK_021C59A4
	add r1, sp, #0x10
	ldr r0, [r0, #0x0]
	bl FUN_0201E9E8
	ldr r0, _0201EC40 ; =UNK_021C59A4
	add r1, sp, #0x10
	ldr r0, [r0, #0x0]
	add r2, sp, #0x4
	bl FUN_0201EA08
	ldr r1, _0201EC40 ; =UNK_021C59A4
	add r0, sp, #0x4
	ldr r1, [r1, #0x0]
	bl FUN_0201EF70
	ldr r0, _0201EC40 ; =UNK_021C59A4
	ldr r3, [r0, #0x0]
	ldr r2, [r3, #0x54]
	add r3, #0x48
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
_0201EBEE:
	ldr r0, _0201EC40 ; =UNK_021C59A4
	ldr r5, _0201EC44 ; =UNK_021CEF58
	ldr r4, [r0, #0x0]
	add r3, r4, #0x0
	add r2, r4, #0x0
	add r4, #0x14
	add r6, r4, #0x0
	ldmia r6!, {r0-r1}
	stmia r5!, {r0-r1}
	ldr r0, [r6, #0x0]
	add r2, #0x2c
	str r0, [r5, #0x0]
	add r6, r2, #0x0
	ldr r5, _0201EC48 ; =UNK_021CEF64
	ldmia r6!, {r0-r1}
	stmia r5!, {r0-r1}
	ldr r0, [r6, #0x0]
	add r3, #0x20
	str r0, [r5, #0x0]
	add r6, r3, #0x0
	ldr r5, _0201EC4C ; =UNK_021CEF70
	ldmia r6!, {r0-r1}
	stmia r5!, {r0-r1}
	ldr r0, [r6, #0x0]
	add r1, r2, #0x0
	str r0, [r5, #0x0]
	ldr r0, _0201EC50 ; =UNK_021CED64
	add r2, r3, #0x0
	str r0, [sp, #0x0]
	add r0, r4, #0x0
	mov r3, #0x0
	bl G3i_LookAt_
	ldr r1, _0201EC54 ; =UNK_021CED98
	mov r0, #0xe8
	ldr r2, [r1, #0x7c]
	bic r2, r0
	str r2, [r1, #0x7c]
_0201EC3A:
	add sp, #0x1c
	pop {r3-r6, pc}
	nop
_0201EC40: .word UNK_021C59A4
_0201EC44: .word UNK_021CEF58
_0201EC48: .word UNK_021CEF64
_0201EC4C: .word UNK_021CEF70
_0201EC50: .word UNK_021CED64
_0201EC54: .word UNK_021CED98

	thumb_func_start FUN_0201EC58
FUN_0201EC58: ; 0x0201EC58
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x2c
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_0201EC68
FUN_0201EC68: ; 0x0201EC68
	push {r3-r4}
	add r3, r1, #0x0
	add r4, r0, #0x0
	str r4, [r3, #0x54]
	add r2, r3, #0x0
	ldmia r4!, {r0-r1}
	add r2, #0x48
	stmia r2!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r2, #0x0]
	mov r0, #0x1
	str r0, [r3, #0x58]
	str r0, [r3, #0x5c]
	str r0, [r3, #0x60]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_0201EC88
FUN_0201EC88: ; 0x0201EC88
	mov r1, #0x0
	str r1, [r0, #0x54]
	str r1, [r0, #0x58]
	str r1, [r0, #0x5c]
	str r1, [r0, #0x60]
	bx lr

	thumb_func_start FUN_0201EC94
FUN_0201EC94: ; 0x0201EC94
	str r0, [r2, #0xc]
	add r0, r2, #0x0
	str r1, [r2, #0x10]
	add r0, #0x44
	ldr r3, _0201ECA4 ; =FUN_0201EE2C
	ldrb r0, [r0, #0x0]
	add r1, r2, #0x0
	bx r3
	.balign 4
_0201ECA4: .word FUN_0201EE2C

	thumb_func_start FUN_0201ECA8
FUN_0201ECA8: ; 0x0201ECA8
	push {r3-r7, lr}
	ldr r4, [sp, #0x20]
	add r5, r0, #0x0
	add r7, r1, #0x0
	add r0, r3, #0x0
	add r1, r4, #0x0
	add r6, r2, #0x0
	bl FUN_0201E99C
	add r3, r5, #0x0
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x20
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	str r7, [r4, #0x38]
	ldrh r0, [r6, #0x0]
	strh r0, [r4, #0x3c]
	ldrh r0, [r6, #0x2]
	strh r0, [r4, #0x3e]
	add r0, r4, #0x0
	ldrh r1, [r6, #0x4]
	add r0, #0x40
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	ldrh r1, [r6, #0x6]
	add r0, #0x42
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_0201E7D8
	add r0, sp, #0x8
	ldrb r0, [r0, #0x10]
	add r1, r4, #0x0
	bl FUN_0201EE2C
	ldr r0, [sp, #0x1c]
	cmp r0, #0x0
	beq _0201ED0E
	str r5, [r4, #0x54]
	add r2, r4, #0x0
	ldmia r5!, {r0-r1}
	add r2, #0x48
	stmia r2!, {r0-r1}
	ldr r0, [r5, #0x0]
	str r0, [r2, #0x0]
	mov r0, #0x1
	str r0, [r4, #0x58]
	str r0, [r4, #0x5c]
	str r0, [r4, #0x60]
_0201ED0E:
	pop {r3-r7, pc}

	thumb_func_start FUN_0201ED10
FUN_0201ED10: ; 0x0201ED10
	push {r3-r7, lr}
	ldr r4, [sp, #0x1c]
	add r6, r0, #0x0
	add r7, r1, #0x0
	add r0, r3, #0x0
	add r1, r4, #0x0
	add r5, r2, #0x0
	bl FUN_0201E99C
	add r2, r4, #0x0
	ldmia r6!, {r0-r1}
	add r2, #0x14
	stmia r2!, {r0-r1}
	ldr r0, [r6, #0x0]
	str r0, [r2, #0x0]
	str r7, [r4, #0x38]
	ldrh r0, [r5, #0x0]
	strh r0, [r4, #0x3c]
	ldrh r0, [r5, #0x2]
	strh r0, [r4, #0x3e]
	add r0, r4, #0x0
	ldrh r1, [r5, #0x4]
	add r0, #0x40
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	ldrh r1, [r5, #0x6]
	add r0, #0x42
	strh r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_0201E8B8
	add r0, sp, #0x8
	ldrb r0, [r0, #0x10]
	add r1, r4, #0x0
	bl FUN_0201EE2C
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0201ED5C
FUN_0201ED5C: ; 0x0201ED5C
	push {r4-r7, lr}
	sub sp, #0x3c
	ldr r4, [sp, #0x54]
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r0, r2, #0x0
	add r1, r4, #0x0
	add r7, r3, #0x0
	bl FUN_0201E99C
	add r3, r5, #0x0
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x20
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	add r3, r6, #0x0
	str r0, [r2, #0x0]
	add r2, r4, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x14
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	add r1, r5, #0x0
	str r0, [r2, #0x0]
	add r0, r6, #0x0
	add r2, sp, #0x30
	bl VEC_Subtract
	add r0, sp, #0x30
	bl VEC_Mag
	str r0, [r4, #0x38]
	mov r6, #0x0
	add r0, sp, #0x24
	str r6, [r0, #0x0]
	str r6, [r0, #0x4]
	str r6, [r0, #0x8]
	add r0, sp, #0x18
	str r6, [r0, #0x0]
	str r6, [r0, #0x4]
	str r6, [r0, #0x8]
	add r0, sp, #0xc
	str r6, [r0, #0x0]
	str r6, [r0, #0x4]
	str r6, [r0, #0x8]
	mov r0, #0x1
	lsl r0, r0, #0xc
	add r3, sp, #0x30
	str r0, [sp, #0x8]
	ldmia r3!, {r0-r1}
	add r2, sp, #0xc
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r6, [sp, #0x0]
	str r0, [r2, #0x0]
	str r6, [sp, #0x4]
	str r6, [sp, #0x10]
	add r0, sp, #0x0
	add r1, sp, #0xc
	bl FUN_0201C7B0
	strh r0, [r4, #0x3e]
	add r1, r6, #0x0
	mov r0, #0x1
	lsl r0, r0, #0xc
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x38]
	str r1, [sp, #0x4]
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x34]
	str r1, [sp, #0x8]
	str r0, [sp, #0x14]
	str r1, [sp, #0x10]
	add r0, sp, #0x0
	add r1, sp, #0xc
	bl FUN_0201C7B0
	strh r0, [r4, #0x3c]
	add r0, r4, #0x0
	add r1, r6, #0x0
	add r0, #0x40
	strh r1, [r0, #0x0]
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl FUN_0201EE2C
	ldr r0, [sp, #0x50]
	cmp r0, #0x0
	beq _0201EE26
	str r5, [r4, #0x54]
	add r2, r4, #0x0
	ldmia r5!, {r0-r1}
	add r2, #0x48
	stmia r2!, {r0-r1}
	ldr r0, [r5, #0x0]
	str r0, [r2, #0x0]
	mov r0, #0x1
	str r0, [r4, #0x58]
	str r0, [r4, #0x5c]
	str r0, [r4, #0x60]
_0201EE26:
	add sp, #0x3c
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_0201EE2C
FUN_0201EE2C: ; 0x0201EE2C
	push {r3-r6, lr}
	sub sp, #0x14
	add r5, r1, #0x0
	cmp r0, #0x0
	bne _0201EE6C
	ldr r0, [r5, #0x10]
	str r0, [sp, #0x0]
	mov r0, #0x1
	lsl r0, r0, #0xc
	str r0, [sp, #0x4]
	mov r0, #0x0
	str r0, [sp, #0x8]
	ldr r0, _0201EEE4 ; =UNK_021CED20
	str r0, [sp, #0xc]
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x4]
	ldr r2, [r5, #0x8]
	ldr r3, [r5, #0xc]
	bl G3i_PerspectiveW_
	ldr r1, _0201EEE8 ; =UNK_021CED98
	mov r0, #0x50
	ldr r2, [r1, #0x7c]
	add r5, #0x44
	bic r2, r0
	str r2, [r1, #0x7c]
	mov r1, #0x0
	ldr r0, _0201EEEC ; =UNK_02105BB8
	strb r1, [r5, #0x0]
	str r1, [r0, #0x0]
	add sp, #0x14
	pop {r3-r6, pc}
_0201EE6C:
	ldr r4, [r5, #0x38]
	ldr r0, [r5, #0x0]
	ldr r1, [r5, #0x4]
	bl FX_Div
	asr r1, r0, #0x1f
	asr r3, r4, #0x1f
	add r2, r4, #0x0
	bl _ll_mul
	mov r2, #0x2
	mov r3, #0x0
	lsl r2, r2, #0xa
	add r2, r0, r2
	adc r1, r3
	lsr r4, r2, #0xc
	lsl r0, r1, #0x14
	orr r4, r0
	ldr r2, [r5, #0x8]
	asr r1, r4, #0x1f
	add r0, r4, #0x0
	asr r3, r2, #0x1f
	bl _ll_mul
	mov r6, #0x2
	mov r2, #0x0
	lsl r6, r6, #0xa
	add r3, r0, r6
	adc r1, r2
	lsl r0, r1, #0x14
	lsr r3, r3, #0xc
	orr r3, r0
	ldr r0, [r5, #0xc]
	neg r1, r4
	str r0, [sp, #0x0]
	ldr r0, [r5, #0x10]
	str r0, [sp, #0x4]
	lsl r0, r6, #0x1
	str r0, [sp, #0x8]
	str r2, [sp, #0xc]
	ldr r0, _0201EEE4 ; =UNK_021CED20
	neg r2, r3
	str r0, [sp, #0x10]
	add r0, r4, #0x0
	bl G3i_OrthoW_
	ldr r1, _0201EEE8 ; =UNK_021CED98
	mov r0, #0x50
	ldr r2, [r1, #0x7c]
	add r5, #0x44
	bic r2, r0
	str r2, [r1, #0x7c]
	mov r0, #0x1
	strb r0, [r5, #0x0]
	ldr r0, _0201EEEC ; =UNK_02105BB8
	mov r1, #0x0
	str r1, [r0, #0x0]
	add sp, #0x14
	pop {r3-r6, pc}
	nop
_0201EEE4: .word UNK_021CED20
_0201EEE8: .word UNK_021CED98
_0201EEEC: .word UNK_02105BB8

	thumb_func_start FUN_0201EEF0
FUN_0201EEF0: ; 0x0201EEF0
	add r2, r1, #0x0
	add r2, #0x46
	strh r0, [r2, #0x0]
	add r0, r1, #0x0
	add r0, #0x46
	ldrh r0, [r0, #0x0]
	ldr r3, _0201EF24 ; =FUN_0201EE2C
	asr r0, r0, #0x4
	lsl r2, r0, #0x2
	ldr r0, _0201EF28 ; =UNK_020FFA38
	ldrsh r2, [r0, r2]
	str r2, [r1, #0x0]
	add r2, r1, #0x0
	add r2, #0x46
	ldrh r2, [r2, #0x0]
	asr r2, r2, #0x4
	lsl r2, r2, #0x1
	add r2, r2, #0x1
	lsl r2, r2, #0x1
	ldrsh r0, [r0, r2]
	str r0, [r1, #0x4]
	add r0, r1, #0x0
	add r0, #0x44
	ldrb r0, [r0, #0x0]
	bx r3
	nop
_0201EF24: .word FUN_0201EE2C
_0201EF28: .word UNK_020FFA38

	thumb_func_start FUN_0201EF2C
FUN_0201EF2C: ; 0x0201EF2C
	add r2, r1, #0x0
	add r2, #0x46
	ldrh r2, [r2, #0x0]
	ldr r3, _0201EF68 ; =FUN_0201EE2C
	add r2, r2, r0
	add r0, r1, #0x0
	add r0, #0x46
	strh r2, [r0, #0x0]
	add r0, r1, #0x0
	add r0, #0x46
	ldrh r0, [r0, #0x0]
	asr r0, r0, #0x4
	lsl r2, r0, #0x2
	ldr r0, _0201EF6C ; =UNK_020FFA38
	ldrsh r2, [r0, r2]
	str r2, [r1, #0x0]
	add r2, r1, #0x0
	add r2, #0x46
	ldrh r2, [r2, #0x0]
	asr r2, r2, #0x4
	lsl r2, r2, #0x1
	add r2, r2, #0x1
	lsl r2, r2, #0x1
	ldrsh r0, [r0, r2]
	str r0, [r1, #0x4]
	add r0, r1, #0x0
	add r0, #0x44
	ldrb r0, [r0, #0x0]
	bx r3
	nop
_0201EF68: .word FUN_0201EE2C
_0201EF6C: .word UNK_020FFA38

	thumb_func_start FUN_0201EF70
FUN_0201EF70: ; 0x0201EF70
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x14
	add r1, r5, #0x0
	add r2, r0, #0x0
	bl VEC_Add
	add r4, #0x20
	add r0, r4, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl VEC_Add
	pop {r3-r5, pc}

	thumb_func_start FUN_0201EF90
FUN_0201EF90: ; 0x0201EF90
	ldrh r2, [r0, #0x0]
	strh r2, [r1, #0x3c]
	ldrh r2, [r0, #0x2]
	strh r2, [r1, #0x3e]
	add r2, r1, #0x0
	ldrh r3, [r0, #0x4]
	add r2, #0x40
	strh r3, [r2, #0x0]
	ldrh r2, [r0, #0x6]
	add r0, r1, #0x0
	add r0, #0x42
	strh r2, [r0, #0x0]
	ldr r3, _0201EFB0 ; =FUN_0201E7D8
	add r0, r1, #0x0
	bx r3
	nop
_0201EFB0: .word FUN_0201E7D8

	thumb_func_start FUN_0201EFB4
FUN_0201EFB4: ; 0x0201EFB4
	ldrh r3, [r1, #0x3c]
	ldrh r2, [r0, #0x0]
	add r2, r3, r2
	strh r2, [r1, #0x3c]
	ldrh r3, [r1, #0x3e]
	ldrh r2, [r0, #0x2]
	add r2, r3, r2
	strh r2, [r1, #0x3e]
	add r2, r1, #0x0
	add r2, #0x40
	ldrh r2, [r2, #0x0]
	ldrh r0, [r0, #0x4]
	ldr r3, _0201EFDC ; =FUN_0201E8B8
	add r2, r2, r0
	add r0, r1, #0x0
	add r0, #0x40
	strh r2, [r0, #0x0]
	add r0, r1, #0x0
	bx r3
	nop
_0201EFDC: .word FUN_0201E8B8

	thumb_func_start FUN_0201EFE0
FUN_0201EFE0: ; 0x0201EFE0
	ldr r3, _0201EFE8 ; =FUN_0201E7D8
	str r0, [r1, #0x38]
	add r0, r1, #0x0
	bx r3
	.balign 4
_0201EFE8: .word FUN_0201E7D8

	thumb_func_start FUN_0201EFEC
FUN_0201EFEC: ; 0x0201EFEC
	push {r4, lr}
	add r3, r1, #0x0
	add r4, r0, #0x0
	add r2, r3, #0x0
	ldmia r4!, {r0-r1}
	add r2, #0x20
	stmia r2!, {r0-r1}
	ldr r0, [r4, #0x0]
	str r0, [r2, #0x0]
	add r0, r3, #0x0
	bl FUN_0201E7D8
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_0201F008
FUN_0201F008: ; 0x0201F008
	add r0, #0x46
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_0201F010
FUN_0201F010: ; 0x0201F010
	ldr r0, [r0, #0x38]
	bx lr

	thumb_func_start FUN_0201F014
FUN_0201F014: ; 0x0201F014
	ldrh r2, [r1, #0x3c]
	strh r2, [r0, #0x0]
	ldrh r2, [r1, #0x3e]
	strh r2, [r0, #0x2]
	add r2, r1, #0x0
	add r2, #0x40
	ldrh r2, [r2, #0x0]
	add r1, #0x42
	strh r2, [r0, #0x4]
	ldrh r1, [r1, #0x0]
	strh r1, [r0, #0x6]
	bx lr

	thumb_func_start FUN_0201F02C
FUN_0201F02C: ; 0x0201F02C
	add r2, r1, #0x0
	add r2, #0x20
	add r3, r0, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start FUN_0201F03C
FUN_0201F03C: ; 0x0201F03C
	add r2, r1, #0x0
	add r2, #0x14
	add r3, r0, #0x0
	ldmia r2!, {r0-r1}
	stmia r3!, {r0-r1}
	ldr r0, [r2, #0x0]
	str r0, [r3, #0x0]
	bx lr

	thumb_func_start FUN_0201F04C
FUN_0201F04C: ; 0x0201F04C
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x20
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr

	thumb_func_start FUN_0201F05C
FUN_0201F05C: ; 0x0201F05C
	add r3, r0, #0x0
	add r2, r1, #0x0
	ldmia r3!, {r0-r1}
	add r2, #0x14
	stmia r2!, {r0-r1}
	ldr r0, [r3, #0x0]
	str r0, [r2, #0x0]
	bx lr
