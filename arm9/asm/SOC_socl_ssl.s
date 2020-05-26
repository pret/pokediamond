	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start SOCLi_EnableSslCallBack
SOCLi_EnableSslCallBack: ; 0x0209AA10
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r6, [r7, #0x4]
	ldr r5, [r6, #0x64]
	add r0, r5, #0xe0
	ldr r4, [r5, #0xc4]
	bl OS_LockMutex
	ldr r1, [r7, #0x10]
	cmp r1, #0x0
	beq _0209AA54
	mov r0, #0x1
	str r1, [r4, #0xc]
	bl CPS_SetSsl
	mov r0, #0x4
	strb r0, [r6, #0x73]
	b _0209AA68
_0209AA54:
	mov r0, #0x0
	strb r0, [r6, #0x73]
	bl CPS_SetSsl
	mov r0, #0x0
	str r0, [r4, #0xc]
_0209AA68:
	add r0, r5, #0xe0
	bl OS_UnlockMutex
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start SOCLi_ExecEnableSslCommand
SOCLi_ExecEnableSslCommand: ; 0x0209AA80
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	ldr r0, _0209AACC ; =SOCLi_EnableSslCallBack
	mov r1, r5
	mov r2, #0x1
	bl SOCLi_CreateCommandPacket
	movs r1, r0
	addeq sp, sp, #0x4
	mvneq r0, #0x20
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	mov r0, r5
	str r4, [r1, #0x10]
	bl SOCLi_ExecCommandPacketInRecvPipe
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209AACC: .word SOCLi_EnableSslCallBack

	arm_func_start SOCL_EnableSsl
SOCL_EnableSsl: ; 0x0209AAD0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl SOCL_SocketIsInvalid
	cmp r0, #0x0
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	ldrsb r0, [r5, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _0209AB10
	cmp r0, #0x4
	movne r1, #0x0
_0209AB10:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r5, #0x0
	mov r1, #0x0
	beq _0209AB3C
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_0209AB3C:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldrsh r0, [r5, #0x70]
	ands r0, r0, #0x2
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r0, r5
	mov r1, r4
	bl SOCLi_ExecEnableSslCommand
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
