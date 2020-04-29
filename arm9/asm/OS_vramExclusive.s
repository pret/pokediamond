    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OsCountZeroBits
OsCountZeroBits: ; 0x020CD5BC
	clz r0, r0
	bx lr

	arm_func_start OSi_UnlockVram
OSi_UnlockVram: ; 0x020CD5C4
	stmdb sp!, {r4-r10,lr}
	mov r5, r0
	mov r10, r1
	bl OS_DisableInterrupts
	ldr r4, _020CD640 ; =OSi_vramExclusive
	ldr r1, _020CD644 ; =0x000001FF
	ldr r2, [r4, #0x0]
	mov r8, r0
	and r0, r5, r2
	and r9, r0, r1
	ldr r6, _020CD648 ; =OSi_vramLockId
	mov r7, #0x1
	mov r5, #0x0
_020CD5F8:
	mov r0, r9
	bl OsCountZeroBits
	rsbs r2, r0, #0x1f
	bmi _020CD630
	mov r1, r2, lsl #0x1
	ldrh r0, [r6, r1]
	mvn r2, r7, lsl r2
	cmp r10, r0
	ldreq r0, [r4, #0x0]
	and r9, r9, r2
	andeq r0, r0, r2
	streqh r5, [r6, r1]
	streq r0, [r4, #0x0]
	b _020CD5F8
_020CD630:
	mov r0, r8
	bl OS_RestoreInterrupts
	ldmia sp!, {r4-r10,lr}
	bx lr
	.balign 4
_020CD640: .word OSi_vramExclusive
_020CD644: .word 0x000001FF
_020CD648: .word OSi_vramLockId

	arm_func_start OSi_TryLockVram
OSi_TryLockVram: ; 0x020CD64C
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r6, r0
	mov r8, r1
	bl OS_DisableInterrupts
	ldr r1, _020CD714 ; =OSi_vramExclusive
	mov r7, r0
	ldr r0, [r1, #0x0]
	and r5, r6, r0
	ldr sb, _020CD718 ; =OSi_vramLockId
	mov r4, #0x1
_020CD678:
	mov r0, r5
	bl OsCountZeroBits
	rsbs r1, r0, #0x1f
	bmi _020CD6B8
	mov r0, r1, lsl #0x1
	ldrh r0, [r9, r0]
	mvn r1, r4, lsl r1
	cmp r8, r0
	and r5, r5, r1
	beq _020CD678
	mov r0, r7
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r9,lr}
	bx lr
_020CD6B8:
	ldr r0, _020CD71C ; =0x000001FF
	and r6, r6, r0
	ldr r4, _020CD718 ; =OSi_vramLockId
	ldr sb, _020CD714 ; =OSi_vramExclusive
	mov r5, #0x1
_020CD6CC:
	mov r0, r6
	bl OsCountZeroBits
	rsbs r1, r0, #0x1f
	bmi _020CD6FC
	ldr r0, [r9, #0x0]
	mvn r2, r5, lsl r1
	orr r0, r0, r5, lsl r1
	mov r1, r1, lsl #0x1
	strh r8, [r4, r1]
	str r0, [r9, #0x0]
	and r6, r6, r2
	b _020CD6CC
_020CD6FC:
	mov r0, r7
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_020CD714: .word OSi_vramExclusive
_020CD718: .word OSi_vramLockId
_020CD71C: .word 0x000001FF

	arm_func_start OSi_InitVramExclusive
OSi_InitVramExclusive: ; 0x020CD720
	ldr r0, _020CD74C ; =OSi_vramExclusive
	mov r3, #0x0
	str r3, [r0, #0x0]
	ldr r0, _020CD750 ; =OSi_vramLockId
	mov r2, r3
_020CD734:
	mov r1, r3, lsl #0x1
	add r3, r3, #0x1
	strh r2, [r0, r1]
	cmp r3, #0x9
	blt _020CD734
	bx lr
	.balign 4
_020CD74C: .word OSi_vramExclusive
_020CD750: .word OSi_vramLockId
