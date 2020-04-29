    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_FreeToHeap
OS_FreeToHeap: ; 0x020CC6F8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r5, r1
	mov r4, r2
	bl OS_DisableInterrupts
	ldr r1, _020CC768 ; =OSi_HeapInfo
	mov r6, r0
	ldr r0, [r1, r7, lsl #0x2]
	cmp r5, #0x0
	ldrlt r5, [r0, #0x0]
	ldr r1, [r0, #0x10]
	mov r0, #0xc
	mla r7, r5, r0, r1
	sub r4, r4, #0x20
	ldr r0, [r7, #0x8]
	mov r1, r4
	bl DLExtract
	str r0, [r7, #0x8]
	ldr r0, [r7, #0x4]
	mov r1, r4
	bl DLInsert
	str r0, [r7, #0x4]
	mov r0, r6
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020CC768: .word OSi_HeapInfo

	arm_func_start OS_AllocFromHeap
OS_AllocFromHeap: ; 0x020CC76C
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r5, r1
	mov r7, r2
	bl OS_DisableInterrupts
	ldr r1, _020CC894 ; =OSi_HeapInfo
	mov r4, r0
	ldr r1, [r1, r6, lsl #0x2]
	cmp r1, #0x0
	bne _020CC7AC
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020CC7AC:
	cmp r5, #0x0
	ldrlt r5, [r1, #0x0]
	ldr r1, [r1, #0x10]
	mov r0, #0xc
	mla r6, r5, r0, r1
	ldr r0, [r6, #0x4]
	add r1, r7, #0x20
	add r1, r1, #0x1f
	mov r5, r0
	cmp r0, #0x0
	bic r7, r1, #0x1f
	beq _020CC7F4
_020CC7DC:
	ldr r1, [r5, #0x8]
	cmp r7, r1
	ble _020CC7F4
	ldr r5, [r5, #0x4]
	cmp r5, #0x0
	bne _020CC7DC
_020CC7F4:
	cmp r5, #0x0
	bne _020CC814
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020CC814:
	ldr r1, [r5, #0x8]
	sub r1, r1, r7
	cmp r1, #0x40
	bhs _020CC834
	mov r1, r5
	bl DLExtract
	str r0, [r6, #0x4]
	b _020CC86C
_020CC834:
	str r7, [r5, #0x8]
	add r2, r5, r7
	str r1, [r2, #0x8]
	ldr r0, [r5, #0x0]
	str r0, [r5, r7]
	ldr r0, [r5, #0x4]
	str r0, [r2, #0x4]
	ldr r0, [r2, #0x4]
	cmp r0, #0x0
	strne r2, [r0, #0x0]
	ldr r0, [r2, #0x0]
	cmp r0, #0x0
	strne r2, [r0, #0x4]
	streq r2, [r6, #0x4]
_020CC86C:
	ldr r0, [r6, #0x8]
	mov r1, r5
	bl DLAddFront
	str r0, [r6, #0x8]
	mov r0, r4
	bl OS_RestoreInterrupts
	add r0, r5, #0x20
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020CC894: .word OSi_HeapInfo

	arm_func_start DLInsert
DLInsert: ; 0x020CC898
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	mov r12, r0
	cmp r0, #0x0
	mov lr, #0x0
	beq _020CC8C8
_020CC8B0:
	cmp r1, r12
	bls _020CC8C8
	mov lr, r12
	ldr r12, [r12, #0x4]
	cmp r12, #0x0
	bne _020CC8B0
_020CC8C8:
	str r12, [r1, #0x4]
	str lr, [r1, #0x0]
	cmp r12, #0x0
	beq _020CC908
	str r1, [r12, #0x0]
	ldr r3, [r1, #0x8]
	add r2, r1, r3
	cmp r2, r12
	bne _020CC908
	ldr r2, [r12, #0x8]
	add r2, r3, r2
	str r2, [r1, #0x8]
	ldr r12, [r12, #0x4]
	str r12, [r1, #0x4]
	cmp r12, #0x0
	strne r1, [r12, #0x0]
_020CC908:
	cmp lr, #0x0
	beq _020CC950
	str r1, [lr, #0x4]
	ldr r2, [lr, #0x8]
	add r3, lr, r2
	cmp r3, r1
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r1, [r1, #0x8]
	add sp, sp, #0x4
	add r1, r2, r1
	str r1, [lr, #0x8]
	str r12, [lr, #0x4]
	cmp r12, #0x0
	strne lr, [r12, #0x0]
	ldmia sp!, {lr}
	bx lr
_020CC950:
	mov r0, r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start DLExtract
DLExtract: ; 0x020CC960
	ldr r3, [r1, #0x4]
	cmp r3, #0x0
	ldrne r2, [r1, #0x0]
	strne r2, [r3, #0x0]
	ldr r2, [r1, #0x0]
	cmp r2, #0x0
	ldreq r0, [r1, #0x4]
	ldrne r1, [r1, #0x4]
	strne r1, [r2, #0x4]
	bx lr

	arm_func_start DLAddFront
DLAddFront: ; 0x020CC988
	str r0, [r1, #0x4]
	mov r2, #0x0
	str r2, [r1, #0x0]
	cmp r0, #0x0
	strne r1, [r0, #0x0]
	mov r0, r1
	bx lr
