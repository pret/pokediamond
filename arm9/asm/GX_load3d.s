	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start GX_EndLoadClearImage
GX_EndLoadClearImage: ; 0x020C95AC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C95F8 ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C95CC
	bl MI_WaitDma
_020C95CC:
	ldr r0, _020C95FC ; =0x021D33FC
	ldr r0, [r0, #0x0]
	bl GX_SetBankForClearImage
	ldr r1, _020C95FC ; =0x021D33FC
	mov r2, #0x0
	ldr r0, _020C9600 ; =0x021D340C
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C95F8: .word 0x02106814
_020C95FC: .word 0x021D33FC
_020C9600: .word 0x021D340C

	arm_func_start GX_LoadClearImageDepth
GX_LoadClearImageDepth: ; 0x020C9604
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r3, _020C9670 ; =0x021D340C
	ldr r2, _020C9674 ; =0x02106814
	ldr r12, [r3, #0x0]
	ldr lr, [r2, #0x0]
	mvn r2, #0x0
	mov r4, r0
	mov r3, r1
	cmp lr, r2
	add r2, r12, #0x20000
	beq _020C9658
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r0, lr
	mov r1, r4
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020C9658:
	mov r1, r2
	mov r2, r3
	bl MIi_CpuCopy32
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C9670: .word 0x021D340C
_020C9674: .word 0x02106814

	arm_func_start GX_LoadClearImageColor
GX_LoadClearImageColor: ; 0x020C9678
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldr r2, _020C96E0 ; =0x02106814
	ldr ip, _020C96E4 ; =0x021D340C
	ldr lr, [r2, #0x0]
	mvn r2, #0x0
	mov r4, r0
	mov r3, r1
	cmp lr, r2
	ldr r2, [r12, #0x0]
	beq _020C96C8
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r0, lr
	mov r1, r4
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020C96C8:
	mov r1, r2
	mov r2, r3
	bl MIi_CpuCopy32
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020C96E0: .word 0x02106814
_020C96E4: .word 0x021D340C

	arm_func_start GX_BeginLoadClearImage
GX_BeginLoadClearImage: ; 0x020C96E8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl GX_ResetBankForClearImage
	ldr r1, _020C979C ; =0x021D33FC
	cmp r0, #0xc
	str r0, [r1, #0x0]
	addls pc, pc, r0, lsl #0x2
	b _020C9790
_020C9708:
	b _020C9790
_020C970C:
	b _020C976C
_020C9710:
	b _020C973C
_020C9714:
	b _020C973C
_020C9718:
	b _020C9784
_020C971C:
	b _020C9790
_020C9720:
	b _020C9790
_020C9724:
	b _020C9790
_020C9728:
	b _020C9754
_020C972C:
	b _020C9790
_020C9730:
	b _020C9790
_020C9734:
	b _020C9790
_020C9738:
	b _020C9754
_020C973C:
	ldr r0, _020C97A0 ; =0x021D340C
	mov r1, #0x6800000
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020C9754:
	ldr r1, _020C97A4 ; =0x06840000
	ldr r0, _020C97A0 ; =0x021D340C
	add sp, sp, #0x4
	str r1, [r0, #0x0]
	ldmia sp!, {lr}
	bx lr
_020C976C:
	ldr r1, _020C97A8 ; =0x067E0000
	ldr r0, _020C97A0 ; =0x021D340C
	add sp, sp, #0x4
	str r1, [r0, #0x0]
	ldmia sp!, {lr}
	bx lr
_020C9784:
	ldr r1, _020C97AC ; =0x06820000
	ldr r0, _020C97A0 ; =0x021D340C
	str r1, [r0, #0x0]
_020C9790:
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C979C: .word 0x021D33FC
_020C97A0: .word 0x021D340C
_020C97A4: .word 0x06840000
_020C97A8: .word 0x067E0000
_020C97AC: .word 0x06820000

	arm_func_start GX_EndLoadTexPltt
GX_EndLoadTexPltt: ; 0x020C97B0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C97FC ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C97D0
	bl MI_WaitDma
_020C97D0:
	ldr r0, _020C9800 ; =0x021D3408
	ldr r0, [r0, #0x0]
	bl GX_SetBankForTexPltt
	ldr r1, _020C9800 ; =0x021D3408
	mov r2, #0x0
	ldr r0, _020C9804 ; =0x021D3404
	str r2, [r1, #0x0]
	str r2, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C97FC: .word 0x02106814
_020C9800: .word 0x021D3408
_020C9804: .word 0x021D3404

	arm_func_start GX_LoadTexPltt
GX_LoadTexPltt: ; 0x020C9808
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	ldr ip, _020C9874 ; =0x021D3404
	ldr r3, _020C9878 ; =0x02106814
	ldr r4, [r12, #0x0]
	ldr lr, [r3, #0x0]
	mvn r12, #0x0
	mov r5, r0
	mov r3, r2
	cmp lr, r12
	add r4, r4, r1
	beq _020C9860
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r0, lr
	mov r1, r5
	mov r2, r4
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
_020C9860:
	mov r1, r4
	bl MIi_CpuCopy32
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C9874: .word 0x021D3404
_020C9878: .word 0x02106814

	arm_func_start GX_BeginLoadTexPltt
GX_BeginLoadTexPltt: ; 0x020C987C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl GX_ResetBankForTexPltt
	mov r3, r0, asr #0x4
	ldr r2, _020C98B8 ; =0x021D3408
	ldr r1, _020C98BC ; =0x02103B3C
	mov r3, r3, lsl #0x1
	ldrh r3, [r1, r3]
	ldr r1, _020C98C0 ; =0x021D3404
	str r0, [r2, #0x0]
	mov r0, r3, lsl #0xc
	str r0, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C98B8: .word 0x021D3408
_020C98BC: .word 0x02103B3C
_020C98C0: .word 0x021D3404

	arm_func_start GX_EndLoadTex
GX_EndLoadTex: ; 0x020C98C4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020C9920 ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C98E4
	bl MI_WaitDma
_020C98E4:
	ldr r0, _020C9924 ; =0x021D3410
	ldr r0, [r0, #0x0]
	bl GX_SetBankForTex
	ldr r3, _020C9928 ; =0x021D3418
	mov r12, #0x0
	ldr r2, _020C992C ; =0x021D3414
	ldr r1, _020C9930 ; =0x021D3400
	ldr r0, _020C9924 ; =0x021D3410
	str r12, [r3, #0x0]
	str r12, [r2, #0x0]
	str r12, [r1, #0x0]
	str r12, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020C9920: .word 0x02106814
_020C9924: .word 0x021D3410
_020C9928: .word 0x021D3418
_020C992C: .word 0x021D3414
_020C9930: .word 0x021D3400

	arm_func_start GX_LoadTex
GX_LoadTex: ; 0x020C9934
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	ldr r3, _020C9A88 ; =0x021D3414
	mov r7, r0
	ldr r5, [r3, #0x0]
	mov r6, r2
	cmp r5, #0x0
	ldreq r0, _020C9A8C ; =0x021D3400
	ldreq r0, [r0, #0x0]
	addeq r2, r0, r1
	beq _020C9A34
	ldr r0, _020C9A90 ; =0x021D3418
	add r2, r1, r6
	ldr r4, [r0, #0x0]
	cmp r2, r4
	ldrlo r0, _020C9A8C ; =0x021D3400
	ldrcc r0, [r0, #0x0]
	addcc r2, r0, r1
	blo _020C9A34
	cmp r1, r4
	addcs r0, r5, r1
	subcs r2, r0, r4
	bhs _020C9A34
	ldr r2, _020C9A8C ; =0x021D3400
	ldr r0, _020C9A94 ; =0x02106814
	ldr r3, [r2, #0x0]
	ldr r0, [r0, #0x0]
	mvn r2, #0x0
	cmp r0, r2
	sub r4, r4, r1
	add r2, r3, r1
	beq _020C99CC
	cmp r4, #0x30
	bls _020C99CC
	mov r1, r7
	mov r3, r4
	bl MI_DmaCopy32
	b _020C99DC
_020C99CC:
	mov r1, r2
	mov r0, r7
	mov r2, r4
	bl MIi_CpuCopy32
_020C99DC:
	ldr r0, _020C9A94 ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C9A18
	mov r12, #0x0
	str r12, [sp, #0x0]
	mov r2, r5
	add r1, r7, r4
	sub r3, r6, r4
	str r12, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
_020C9A18:
	mov r1, r5
	add r0, r7, r4
	sub r2, r6, r4
	bl MIi_CpuCopy32
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
_020C9A34:
	ldr r0, _020C9A94 ; =0x02106814
	mvn r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, r1
	beq _020C9A6C
	mov r4, #0x0
	str r4, [sp, #0x0]
	mov r1, r7
	mov r3, r6
	str r4, [sp, #0x4]
	bl MI_DmaCopy32Async
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
_020C9A6C:
	mov r1, r2
	mov r0, r7
	mov r2, r6
	bl MIi_CpuCopy32
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020C9A88: .word 0x021D3414
_020C9A8C: .word 0x021D3400
_020C9A90: .word 0x021D3418
_020C9A94: .word 0x02106814

	arm_func_start GX_BeginLoadTex
GX_BeginLoadTex: ; 0x020C9A98
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl GX_ResetBankForTex
	mov r1, #0x6
	mul r12, r0, r1
	ldr r3, _020C9AFC ; =0x02103B4C
	ldr r2, _020C9B00 ; =0x02103B4E
	ldr r1, _020C9B04 ; =0x02103B50
	ldrh r5, [r3, r12]
	ldrh r4, [r2, r12]
	ldrh lr, [r1, r12]
	ldr ip, _020C9B08 ; =0x021D3410
	ldr r3, _020C9B0C ; =0x021D3400
	mov r5, r5, lsl #0xc
	ldr r2, _020C9B10 ; =0x021D3414
	mov r4, r4, lsl #0xc
	ldr r1, _020C9B14 ; =0x021D3418
	mov lr, lr, lsl #0xc
	str r0, [r12, #0x0]
	str r5, [r3, #0x0]
	str r4, [r2, #0x0]
	str lr, [r1, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020C9AFC: .word 0x02103B4C
_020C9B00: .word 0x02103B4E
_020C9B04: .word 0x02103B50
_020C9B08: .word 0x021D3410
_020C9B0C: .word 0x021D3400
_020C9B10: .word 0x021D3414
_020C9B14: .word 0x021D3418
