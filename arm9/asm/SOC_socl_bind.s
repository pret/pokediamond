	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.balign 4, 0
	.global SOCLiResultCodeInConnecting
SOCLiResultCodeInConnecting: ; 0x021061C0
	.word -26

	.text

	arm_func_start SOCLi_BindCallBack
SOCLi_BindCallBack: ; 0x020982C4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldr r4, [r7, #0x4]
	mov r5, #0x0
	ldr r6, [r4, #0x64]
	add r0, r6, #0xe0
	bl OS_LockMutex
	ldrh r0, [r7, #0x10]
	ldrh r1, [r7, #0x12]
	ldr r2, [r7, #0x14]
	bl CPS_SocPingMode
	mov r0, r5
	str r0, [r6, #0xf8]
	ldrsb r0, [r7, #0xc]
	cmp r0, #0x0
	beq _02098310
	cmp r0, #0x4
	bne _02098318
_02098310:
	bl CPS_TcpConnect
	mov r5, r0
_02098318:
	add r0, r6, #0xe0
	bl OS_UnlockMutex
	cmp r5, #0x0
	ldrnesh r1, [r4, #0x70]
	mvnne r0, #0x4b
	moveq r0, #0x0
	orrne r1, r1, #0x40
	strneh r1, [r4, #0x70]
	ldreqsh r1, [r4, #0x70]
	orreq r1, r1, #0x4
	streqh r1, [r4, #0x70]
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start SOCLi_ExecBindCommand
SOCLi_ExecBindCommand: ; 0x02098350
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrsb r2, [r4, #0x72]
	ldr r0, _020983AC ; =SOCLi_BindCallBack
	mov r1, r4
	bl SOCLi_CreateCommandPacket
	movs r1, r0
	mvneq r0, #0x20
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldrh r2, [r4, #0x74]
	mov r0, r4
	strh r2, [r1, #0x10]
	ldrh r2, [r4, #0x76]
	strh r2, [r1, #0x12]
	ldr r2, [r4, #0x78]
	str r2, [r1, #0x14]
	ldrsh r2, [r4, #0x70]
	orr r2, r2, #0x2
	strh r2, [r4, #0x70]
	bl SOCLi_ExecCommandPacketInRecvPipe
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020983AC: .word SOCLi_BindCallBack

	arm_func_start SOCL_Connect
SOCL_Connect: ; 0x020983B0
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl SOCL_SocketIsInvalid
	cmp r0, #0x0
	bne _020983D8
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x8
	beq _020983E4
_020983D8:
	mvn r0, #0x1b
	ldmia sp!, {r4-r6,lr}
	bx lr
_020983E4:
	cmp r6, #0x0
	mov r1, #0x0
	beq _020983FC
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_020983FC:
	cmp r1, #0x0
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	ldrsb r0, [r6, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _02098424
	cmp r0, #0x4
	movne r1, #0x0
_02098424:
	cmp r1, #0x0
	beq _0209849C
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x4
	beq _02098450
	ldrsb r0, [r6, #0x72]
	cmp r0, #0x1
	mvneq r0, #0x1d
	movne r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_02098450:
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x2
	beq _02098478
	ldrsh r0, [r6, #0x70]
	ands r0, r0, #0x40
	ldrne r0, [r6, #0x6c]
	ldreq r0, _020984B0 ; =SOCLiResultCodeInConnecting
	ldreq r0, [r0, #0x0]
	ldmia sp!, {r4-r6,lr}
	bx lr
_02098478:
	strh r5, [r6, #0x76]
	mov r0, r6
	str r4, [r6, #0x78]
	bl SOCLi_ExecBindCommand
	ldrsb r1, [r6, #0x72]
	cmp r1, #0x1
	mvnne r0, #0x19
	ldmia sp!, {r4-r6,lr}
	bx lr
_0209849C:
	strh r5, [r6, #0x76]
	str r4, [r6, #0x78]
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020984B0: .word SOCLiResultCodeInConnecting

	arm_func_start SOCL_Bind
SOCL_Bind:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	mov r5, r1
	bl SOCL_SocketIsInvalid
	cmp r0, #0x0
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	cmp r4, #0x0
	mov r1, #0x0
	beq _020984F4
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_020984F4:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x2
	addne sp, sp, #0x4
	mvnne r0, #0x6
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	strh r5, [r4, #0x74]
	ldrsb r0, [r4, #0x73]
	cmp r0, #0x1
	addne sp, sp, #0x4
	movne r0, #0x0
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	mov r0, r4
	bl SOCLi_ExecBindCommand
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
