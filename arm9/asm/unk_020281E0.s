	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_020281E0
FUN_020281E0: ; 0x020281E0
	mov r0, #0x1f
	lsl r0, r0, #0x6
	bx lr
	.balign 4

	thumb_func_start FUN_020281E8
FUN_020281E8: ; 0x020281E8
	push {r3-r7, lr}
	add r7, r0, #0x0
	mov r2, #0x1f
	mov r0, #0x0
	add r1, r7, #0x0
	lsl r2, r2, #0x6
	bl MIi_CpuClearFast
	mov r0, #0x1d
	lsl r0, r0, #0x4
	add r1, r0, #0x0
	add r2, r0, #0x0
	ldr r4, _02028224 ; =0x0000FFFF
	mov r5, #0x0
	add r6, r7, #0x0
	mov r3, #0x2
	sub r1, #0x10
	add r2, #0x1e
_0202820C:
	strh r4, [r6, r0]
	strh r4, [r6, r1]
	strb r3, [r6, r2]
	add r5, r5, #0x1
	add r6, #0x30
	cmp r5, #0x20
	blt _0202820C
	add r0, r7, #0x0
	bl FUN_0203380C
	pop {r3-r7, pc}
	nop
_02028224: .word 0x0000FFFF

	thumb_func_start FUN_02028228
FUN_02028228: ; 0x02028228
	bx lr
	.balign 4

	thumb_func_start FUN_0202822C
FUN_0202822C: ; 0x0202822C
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r7, r2, #0x0
	cmp r4, #0x20
	blt _0202823C
	bl GF_AssertFail
_0202823C:
	cmp r7, #0x8
	bhi _020282D0
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202824C: ; jump table (using 16-bit offset)
	.short _0202825E - _0202824C - 2; case 0
	.short _0202826C - _0202824C - 2; case 1
	.short _0202827A - _0202824C - 2; case 2
	.short _02028286 - _0202824C - 2; case 3
	.short _02028294 - _0202824C - 2; case 4
	.short _020282A0 - _0202824C - 2; case 5
	.short _020282AE - _0202824C - 2; case 6
	.short _020282C6 - _0202824C - 2; case 7
	.short _020282BA - _0202824C - 2; case 8
_0202825E:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x1e
	lsl r0, r0, #0x4
	ldr r6, [r1, r0]
	b _020282D0
_0202826C:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x79
	lsl r0, r0, #0x2
	ldrh r6, [r1, r0]
	b _020282D0
_0202827A:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _020282D4 ; =0x000001E6
	ldrh r6, [r1, r0]
	b _020282D0
_02028286:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x7a
	lsl r0, r0, #0x2
	ldrh r6, [r1, r0]
	b _020282D0
_02028294:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _020282D8 ; =0x000001EA
	ldrh r6, [r1, r0]
	b _020282D0
_020282A0:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x7b
	lsl r0, r0, #0x2
	ldrb r6, [r1, r0]
	b _020282D0
_020282AE:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _020282DC ; =0x000001ED
	ldrb r6, [r1, r0]
	b _020282D0
_020282BA:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _020282E0 ; =0x000001EE
	ldrb r6, [r1, r0]
	b _020282D0
_020282C6:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _020282E4 ; =0x000001EF
	ldrb r6, [r1, r0]
_020282D0:
	add r0, r6, #0x0
	pop {r3-r7, pc}
	.balign 4
_020282D4: .word 0x000001E6
_020282D8: .word 0x000001EA
_020282DC: .word 0x000001ED
_020282E0: .word 0x000001EE
_020282E4: .word 0x000001EF

	thumb_func_start FUN_020282E8
FUN_020282E8: ; 0x020282E8
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r7, r2, #0x0
	add r6, r3, #0x0
	cmp r4, #0x20
	blt _020282FA
	bl GF_AssertFail
_020282FA:
	cmp r7, #0x8
	bhi _02028378
	add r0, r7, r7
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_0202830A: ; jump table (using 16-bit offset)
	.short _0202831C - _0202830A - 2; case 0
	.short _0202832A - _0202830A - 2; case 1
	.short _02028330 - _0202830A - 2; case 2
	.short _02028336 - _0202830A - 2; case 3
	.short _0202833C - _0202830A - 2; case 4
	.short _02028348 - _0202830A - 2; case 5
	.short _02028356 - _0202830A - 2; case 6
	.short _0202836E - _0202830A - 2; case 7
	.short _02028362 - _0202830A - 2; case 8
_0202831C:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x1e
	lsl r0, r0, #0x4
	str r6, [r1, r0]
	pop {r3-r7, pc}
_0202832A:
	bl GF_AssertFail
	pop {r3-r7, pc}
_02028330:
	bl GF_AssertFail
	pop {r3-r7, pc}
_02028336:
	bl GF_AssertFail
	pop {r3-r7, pc}
_0202833C:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _0202837C ; =0x000001EA
	strh r6, [r1, r0]
	pop {r3-r7, pc}
_02028348:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	mov r0, #0x7b
	lsl r0, r0, #0x2
	strb r6, [r1, r0]
	pop {r3-r7, pc}
_02028356:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _02028380 ; =0x000001ED
	strb r6, [r1, r0]
	pop {r3-r7, pc}
_02028362:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _02028384 ; =0x000001EE
	strb r6, [r1, r0]
	pop {r3-r7, pc}
_0202836E:
	mov r0, #0x30
	mul r0, r4
	add r1, r5, r0
	ldr r0, _02028388 ; =0x000001EF
	strb r6, [r1, r0]
_02028378:
	pop {r3-r7, pc}
	nop
_0202837C: .word 0x000001EA
_02028380: .word 0x000001ED
_02028384: .word 0x000001EE
_02028388: .word 0x000001EF

	thumb_func_start FUN_0202838C
FUN_0202838C: ; 0x0202838C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x20
	blt _0202839A
	bl GF_AssertFail
_0202839A:
	mov r0, #0xc
	add r5, #0x40
	mul r0, r4
	add r0, r5, r0
	pop {r3-r5, pc}

	thumb_func_start FUN_020283A4
FUN_020283A4: ; 0x020283A4
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x20
	blt _020283B2
	bl GF_AssertFail
_020283B2:
	mov r0, #0x1d
	lsl r0, r0, #0x4
	add r1, r5, r0
	mov r0, #0x30
	mul r0, r4
	add r0, r1, r0
	pop {r3-r5, pc}

	thumb_func_start FUN_020283C0
FUN_020283C0: ; 0x020283C0
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x20
	blt _020283D0
	bl GF_AssertFail
_020283D0:
	mov r1, #0x1d
	lsl r1, r1, #0x4
	add r2, r5, r1
	mov r1, #0x30
	mul r1, r4
	add r1, r2, r1
	add r0, r6, #0x0
	mov r2, #0x10
	bl CopyStringToU16Array
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_020283E8
FUN_020283E8: ; 0x020283E8
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x20
	blt _020283F6
	bl GF_AssertFail
_020283F6:
	mov r0, #0x7
	lsl r0, r0, #0x6
	add r1, r5, r0
	mov r0, #0x30
	mul r0, r4
	add r0, r1, r0
	pop {r3-r5, pc}

	thumb_func_start FUN_02028404
FUN_02028404: ; 0x02028404
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	cmp r4, #0x20
	blt _02028414
	bl GF_AssertFail
_02028414:
	mov r1, #0x7
	lsl r1, r1, #0x6
	add r2, r5, r1
	mov r1, #0x30
	mul r1, r4
	add r1, r2, r1
	add r0, r6, #0x0
	mov r2, #0x10
	bl CopyStringToU16Array
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202842C
FUN_0202842C: ; 0x0202842C
	push {r3-r5, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x20
	blt _0202843A
	bl GF_AssertFail
_0202843A:
	mov r0, #0xc
	add r5, #0x40
	mul r0, r4
	add r0, r5, r0
	bl DWC_IsValidFriendData
	pop {r3-r5, pc}

	thumb_func_start FUN_02028448
FUN_02028448: ; 0x02028448
	push {r4-r6, lr}
	mov r5, #0x0
	add r6, r0, #0x0
	add r4, r5, #0x0
_02028450:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0202842C
	cmp r0, #0x0
	beq _0202845E
	add r5, r5, #0x1
_0202845E:
	add r4, r4, #0x1
	cmp r4, #0x20
	blt _02028450
	add r0, r5, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02028468
FUN_02028468: ; 0x02028468
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r1, #0x0
	str r0, [sp, #0x0]
	cmp r5, #0x20
	blt _02028478
	bl GF_AssertFail
_02028478:
	cmp r5, #0x1f
	bge _020284D2
	mov r1, #0x7
	ldr r0, [sp, #0x0]
	lsl r1, r1, #0x6
	add r0, r0, r1
	str r0, [sp, #0x4]
	mov r0, #0x30
	add r1, r5, #0x0
	mul r1, r0
	ldr r0, [sp, #0x4]
	add r6, r0, r1
	ldr r0, [sp, #0x0]
	add r1, r5, #0x0
	str r0, [sp, #0x8]
	add r0, #0x40
	str r0, [sp, #0x8]
	mov r0, #0xc
	mul r1, r0
	ldr r0, [sp, #0x8]
	add r4, r0, r1
_020284A2:
	add r7, r5, #0x1
	mov r0, #0x30
	add r1, r7, #0x0
	mul r1, r0
	ldr r0, [sp, #0x4]
	mov r2, #0x30
	add r0, r0, r1
	add r1, r6, #0x0
	bl MI_CpuCopy8
	mov r0, #0xc
	add r1, r7, #0x0
	mul r1, r0
	ldr r0, [sp, #0x8]
	mov r2, #0xc
	add r0, r0, r1
	add r1, r4, #0x0
	bl MI_CpuCopy8
	add r5, r5, #0x1
	add r6, #0x30
	add r4, #0xc
	cmp r5, #0x1f
	blt _020284A2
_020284D2:
	mov r2, #0x7
	ldr r1, [sp, #0x0]
	lsl r2, r2, #0x6
	add r2, r1, r2
	mov r1, #0x5d
	lsl r1, r1, #0x4
	add r1, r2, r1
	mov r0, #0x0
	mov r2, #0x30
	bl MIi_CpuClearFast
	ldr r2, [sp, #0x0]
	mov r1, #0x5d
	add r2, #0x40
	lsl r1, r1, #0x2
	add r1, r2, r1
	mov r0, #0x0
	mov r2, #0xc
	bl MIi_CpuClearFast
	mov r2, #0x7a
	lsl r2, r2, #0x4
	add r1, r2, #0x0
	ldr r3, _02028514 ; =0x0000FFFF
	ldr r0, [sp, #0x0]
	sub r1, #0x10
	strh r3, [r0, r2]
	strh r3, [r0, r1]
	mov r1, #0x2
	add r2, #0x1e
	strb r1, [r0, r2]
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
_02028514: .word 0x0000FFFF

	thumb_func_start FUN_02028518
FUN_02028518: ; 0x02028518
	push {r4-r7, lr}
	sub sp, #0xc
	str r2, [sp, #0x4]
	add r7, r0, #0x0
	ldr r0, [sp, #0x4]
	mov r2, #0x30
	add r5, r0, #0x0
	mov r0, #0x7
	lsl r0, r0, #0x6
	add r3, r1, #0x0
	mul r5, r2
	add r4, r7, r0
	mul r3, r2
	str r1, [sp, #0x0]
	add r0, r4, r5
	add r1, r4, r3
	bl MI_CpuCopy8
	ldr r0, [sp, #0x4]
	add r6, r7, #0x0
	mov r3, #0xc
	add r1, r0, #0x0
	mul r1, r3
	add r6, #0x40
	str r1, [sp, #0x8]
	add r0, r6, r1
	ldr r1, [sp, #0x0]
	add r2, r1, #0x0
	mul r2, r3
	add r1, r6, r2
	add r2, r3, #0x0
	bl MI_CpuCopy8
	mov r0, #0x0
	add r1, r4, r5
	mov r2, #0x30
	bl MIi_CpuClearFast
	ldr r1, [sp, #0x8]
	mov r0, #0x0
	add r1, r6, r1
	mov r2, #0xc
	bl MIi_CpuClearFast
	mov r0, #0x1d
	ldr r1, _02028588 ; =0x0000FFFF
	add r2, r7, r5
	lsl r0, r0, #0x4
	strh r1, [r2, r0]
	strh r1, [r4, r5]
	mov r1, #0x2
	add r0, #0x1e
	strb r1, [r2, r0]
	add sp, #0xc
	pop {r4-r7, pc}
	nop
_02028588: .word 0x0000FFFF

	thumb_func_start FUN_0202858C
FUN_0202858C: ; 0x0202858C
	push {r3-r7, lr}
	mov r5, #0x0
	mvn r5, r5
	add r6, r0, #0x0
	mov r4, #0x0
	add r7, r5, #0x0
_02028598:
	add r0, r6, #0x0
	add r1, r4, #0x0
	bl FUN_0202842C
	cmp r0, #0x0
	beq _020285BC
	mov r0, #0x0
	mvn r0, r0
	cmp r5, r0
	beq _020285C6
	add r0, r6, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02028518
	add r4, r7, #0x0
	add r5, r7, #0x0
	b _020285C6
_020285BC:
	mov r0, #0x0
	mvn r0, r0
	cmp r5, r0
	bne _020285C6
	add r5, r4, #0x0
_020285C6:
	add r4, r4, #0x1
	cmp r4, #0x20
	blt _02028598
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_020285D0
FUN_020285D0: ; 0x020285D0
	push {r3-r5, lr}
	sub sp, #0x10
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r0, sp, #0x0
	bl GF_RTC_CopyDate
	mov r0, #0x30
	add r2, r4, #0x0
	mul r2, r0
	mov r0, #0x7d
	ldr r1, [sp, #0x0]
	lsl r0, r0, #0x4
	add r1, r1, r0
	ldr r0, _02028604 ; =0x000001EA
	add r3, r5, r2
	strh r1, [r3, r0]
	add r1, r0, #0x2
	ldr r2, [sp, #0x4]
	add r0, r0, #0x3
	strb r2, [r3, r1]
	ldr r1, [sp, #0x8]
	strb r1, [r3, r0]
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_02028604: .word 0x000001EA

	thumb_func_start FUN_02028608
FUN_02028608: ; 0x02028608
	push {r4-r6, lr}
	mov r5, #0x79
	add r4, r0, #0x0
	mov r0, #0x30
	lsl r5, r5, #0x2
	mul r0, r1
	add r5, r4, r5
	ldrh r6, [r5, r0]
	add r2, r6, r2
	strh r2, [r5, r0]
	ldrh r6, [r5, r0]
	ldr r2, _0202865C ; =0x0000270F
	cmp r6, r2
	bls _02028626
	strh r2, [r5, r0]
_02028626:
	ldr r2, _02028660 ; =0x000001E6
	add r2, r4, r2
	ldrh r5, [r2, r0]
	add r3, r5, r3
	strh r3, [r2, r0]
	ldrh r5, [r2, r0]
	ldr r3, _0202865C ; =0x0000270F
	cmp r5, r3
	bls _0202863A
	strh r3, [r2, r0]
_0202863A:
	mov r2, #0x7a
	lsl r2, r2, #0x2
	add r2, r4, r2
	ldrh r5, [r2, r0]
	ldr r3, [sp, #0x10]
	add r3, r5, r3
	strh r3, [r2, r0]
	ldrh r5, [r2, r0]
	ldr r3, _0202865C ; =0x0000270F
	cmp r5, r3
	bls _02028652
	strh r3, [r2, r0]
_02028652:
	add r0, r4, #0x0
	bl FUN_020285D0
	pop {r4-r6, pc}
	nop
_0202865C: .word 0x0000270F
_02028660: .word 0x000001E6

	thumb_func_start FUN_02028664
FUN_02028664: ; 0x02028664
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r3, #0x79
	mov r0, #0x30
	add r4, r1, #0x0
	mul r4, r0
	lsl r3, r3, #0x2
	mul r0, r2
	add r2, r5, r3
	add r6, r5, r4
	ldrh r1, [r2, r0]
	ldrh r3, [r6, r3]
	add r1, r1, r3
	strh r1, [r2, r0]
	ldrh r3, [r2, r0]
	ldr r1, _020286E0 ; =0x0000270F
	cmp r3, r1
	bls _0202868A
	strh r1, [r2, r0]
_0202868A:
	ldr r3, _020286E4 ; =0x000001E6
	add r6, r5, r4
	add r2, r5, r3
	ldrh r1, [r2, r0]
	ldrh r3, [r6, r3]
	add r1, r1, r3
	strh r1, [r2, r0]
	ldrh r3, [r2, r0]
	ldr r1, _020286E0 ; =0x0000270F
	cmp r3, r1
	bls _020286A2
	strh r1, [r2, r0]
_020286A2:
	mov r3, #0x7a
	lsl r3, r3, #0x2
	add r2, r5, r3
	add r6, r5, r4
	ldrh r1, [r2, r0]
	ldrh r3, [r6, r3]
	add r1, r1, r3
	strh r1, [r2, r0]
	ldrh r3, [r2, r0]
	ldr r1, _020286E0 ; =0x0000270F
	cmp r3, r1
	bls _020286BC
	strh r1, [r2, r0]
_020286BC:
	mov r0, #0x7
	lsl r0, r0, #0x6
	add r6, r5, r0
	mov r0, #0x0
	add r1, r6, r4
	mov r2, #0x30
	bl MIi_CpuClearFast
	mov r0, #0x1d
	ldr r1, _020286E8 ; =0x0000FFFF
	add r2, r5, r4
	lsl r0, r0, #0x4
	strh r1, [r2, r0]
	strh r1, [r6, r4]
	mov r1, #0x2
	add r0, #0x1e
	strb r1, [r2, r0]
	pop {r4-r6, pc}
	.balign 4
_020286E0: .word 0x0000270F
_020286E4: .word 0x000001E6
_020286E8: .word 0x0000FFFF

	thumb_func_start FUN_020286EC
FUN_020286EC: ; 0x020286EC
	ldr r3, _020286F4 ; =SavArray_get
	mov r1, #0x1d
	bx r3
	nop
_020286F4: .word SavArray_get
