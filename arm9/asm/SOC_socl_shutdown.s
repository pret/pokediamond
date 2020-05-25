	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start SOCLi_ShutdownCallBack
SOCLi_ShutdownCallBack: ; 0x0209959C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x4]
	mov r1, #0x1
	ldrsb r0, [r0, #0x73]
	cmp r0, #0x0
	beq _020995C0
	cmp r0, #0x4
	movne r1, #0x0
_020995C0:
	cmp r1, #0x0
	beq _020995CC
	bl CPS_TcpShutdown
_020995CC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SOCL_Shutdown
SOCL_Shutdown: ; 0x020995DC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	bl SOCL_SocketIsInvalid
	cmp r0, #0x0
	addne sp, sp, #0x4
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r5,lr}
	bxne lr
	cmp r4, #0x0
	mov r1, #0x0
	beq _02099618
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_02099618:
	cmp r1, #0x0
	addeq sp, sp, #0x4
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x4
	beq _02099644
	ldrsh r0, [r4, #0x70]
	ands r0, r0, #0x8
	beq _02099654
_02099644:
	add sp, sp, #0x4
	mvn r0, #0x37
	ldmia sp!, {r4-r5,lr}
	bx lr
_02099654:
	ldrsh r0, [r4, #0x70]
	orr r0, r0, #0x8
	strh r0, [r4, #0x70]
	ldr r5, [r4, #0x68]
	cmp r5, #0x0
	beq _020996AC
	ldr r1, [r5, #0x10c]
	cmp r1, #0x0
	beq _020996AC
	ldrsb r2, [r4, #0x72]
	ldr r0, _020996BC ; =SOCLi_ShutdownCallBack
	bl SOCLi_CreateCommandPacket
	movs r1, r0
	addeq sp, sp, #0x4
	mvneq r0, #0x20
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, [r5, #0x10c]
	bl SOCLi_ExecCommandPacketInSendPipe
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020996AC:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020996BC: .word SOCLi_ShutdownCallBack
