	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global SOCLi_CheckCount
SOCLi_CheckCount: ; 0x021C8D28
	.space 0x8

	.text

	arm_func_start SOCLi_UdpRecvCallback
SOCLi_UdpRecvCallback: ; 0x02098550
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r7, r2
	ldr r6, [r7, #0x64]
	mov r9, r0
	mov r8, r1
	bl OS_DisableInterrupts
	add r1, r6, #0x100
	ldrh r2, [r1, #0x8]
	ldrh r1, [r1, #0xa]
	mov r4, r0
	add r0, r2, r8
	cmp r1, r0
	blo _02098618
	ldr r1, _02098668 ; =SOCLiConfigPtr
	add r0, r8, #0xc
	ldr r1, [r1, #0x0]
	ldr r1, [r1, #0x18]
	blx r1
	movs r5, r0
	beq _02098604
	add r1, r6, #0x100
	ldrh r3, [r1, #0x8]
	mov r2, #0x0
	mov r0, r9
	add r3, r3, r8
	strh r3, [r1, #0x8]
	str r2, [r5, #0x0]
	strh r8, [r5, #0x4]
	ldrh r3, [r7, #0x18]
	mov r2, r8
	add r1, r5, #0xc
	strh r3, [r5, #0x6]
	ldr r3, [r7, #0x1c]
	str r3, [r5, #0x8]
	bl MI_CpuCopy8
	ldr r0, [r6, #0x100]
	cmp r0, #0x0
	ldrne r0, [r6, #0x100]
	strne r5, [r0, #0x0]
	str r5, [r6, #0x100]
	ldr r0, [r6, #0x104]
	cmp r0, #0x0
	streq r5, [r6, #0x104]
	b _02098628
_02098604:
	ldr r0, _0209866C ; =SOCLi_CheckCount
	ldr r1, [r0, #0x0]
	add r1, r1, #0x1
	str r1, [r0, #0x0]
	b _02098628
_02098618:
	ldr r0, _0209866C ; =SOCLi_CheckCount
	ldr r1, [r0, #0x4]
	add r1, r1, #0x1
	str r1, [r0, #0x4]
_02098628:
	ldrh r0, [r7, #0x74]
	cmp r0, #0x0
	ldreqh r0, [r7, #0xa]
	streqh r0, [r7, #0x74]
	ldrh r1, [r7, #0x1a]
	add r0, r6, #0x10c
	strh r1, [r7, #0x18]
	ldr r1, [r7, #0x20]
	str r1, [r7, #0x1c]
	bl OS_WakeupThread
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_02098668: .word SOCLiConfigPtr
_0209866C: .word SOCLi_CheckCount

	arm_func_start SOCLi_ReadUdpBuffer
SOCLi_ReadUdpBuffer: ; 0x02098670
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r10, r0
	ldr r9, [r10, #0x64]
	str r1, [sp, #0x0]
	ldr r0, [r9, #0x104]
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	bl OS_DisableInterrupts
	ldr r8, [r9, #0x104]
	str r0, [sp, #0xc]
	cmp r8, #0x0
	bne _02098710
	ldr r0, [sp, #0x3c]
	and r7, r0, #0x1
	add r6, r9, #0x10c
	mov r4, #0x1
	mov r5, #0x0
_020986B8:
	cmp r7, #0x0
	mvneq r11, #0x5
	beq _02098710
	mov r0, r6
	bl OS_SleepThread
	mov r0, r10
	bl SOCL_SocketIsInvalid
	cmp r0, #0x0
	bne _020986FC
	mov r1, r5
	cmp r10, #0x0
	beq _020986F4
	ldrsh r0, [r10, #0x70]
	ands r0, r0, #0x1
	movne r1, r4
_020986F4:
	cmp r1, #0x0
	bne _02098704
_020986FC:
	mvn r11, #0x37
	b _02098710
_02098704:
	ldr r8, [r9, #0x104]
	cmp r8, #0x0
	beq _020986B8
_02098710:
	cmp r8, #0x0
	beq _020987A4
	ldrh r1, [r8, #0x4]
	ldr r0, [sp, #0x4]
	cmp r0, r1
	strgt r1, [sp, #0x4]
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, r8, #0xc
	bl MI_CpuCopy8
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	ldrneh r1, [r8, #0x6]
	strneh r1, [r0, #0x0]
	ldr r1, [sp, #0x38]
	cmp r1, #0x0
	ldrne r0, [r8, #0x8]
	strne r0, [r1, #0x0]
	ldrsb r0, [r9, #0xfe]
	ldrh r11, [r8, #0x4]
	cmp r0, #0x0
	bne _020987A4
	ldr r0, [r8, #0x0]
	ldr r1, _020987BC ; =SOCLiConfigPtr
	str r0, [r9, #0x104]
	ldr r0, [r8, #0x0]
	cmp r0, #0x0
	moveq r0, #0x0
	streq r0, [r9, #0x100]
	ldr r1, [r1, #0x0]
	mov r0, r8
	ldr r1, [r1, #0x1c]
	blx r1
	add r0, r9, #0x100
	ldrh r1, [r0, #0x8]
	sub r1, r1, r11
	strh r1, [r0, #0x8]
_020987A4:
	ldr r0, [sp, #0xc]
	bl OS_RestoreInterrupts
	mov r0, r11
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_020987BC: .word SOCLiConfigPtr

	arm_func_start SOCLi_ConsumeCPSBuffer
SOCLi_ConsumeCPSBuffer: ; 0x020987C0
	stmdb sp!, {r4-r6,lr}
	ldr r6, [r0, #0x64]
	bl OS_DisableInterrupts
	ldr r4, [r6, #0xf8]
	mov r5, r0
	cmp r4, #0x0
	beq _020987EC
	mov r1, #0x0
	mov r0, r4
	str r1, [r6, #0xf8]
	bl CPS_SocConsume
_020987EC:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start SOCLi_ConsumeCallBack
SOCLi_ConsumeCallBack: ; 0x02098800
	ldr ip, _0209880C ; =SOCLi_ConsumeCPSBuffer
	ldr r0, [r0, #0x4]
	bx r12
	.balign 4
_0209880C: .word SOCLi_ConsumeCPSBuffer

	arm_func_start SOCLi_ConsumeBuffer
SOCLi_ConsumeBuffer:
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r1, [r4, #0x64]
	ldrh r0, [r1, #0xfc]
	ldr r1, [r1, #0xf8]
	cmp r1, r0
	movlt r0, #0x0
	ldmltia sp!, {r4,lr}
	bxlt lr
	ldr r0, _02098864 ; =SOCLi_ConsumeCallBack
	mov r1, r4
	mov r2, #0x0
	bl SOCLi_CreateCommandPacket
	movs r1, r0
	mvneq r0, #0x20
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r0, r4
	bl SOCLi_ExecCommandPacketInRecvPipe
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_02098864: .word SOCLi_ConsumeCallBack

	arm_func_start SOCLi_ReadCallBack
SOCLi_ReadCallBack: ; 0x02098868
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	ldr r9, [r0, #0x4]
	ldr r1, [r0, #0x10]
	ldr r8, [r9, #0x64]
	str r1, [sp, #0x4]
	ldr r1, [r0, #0x18]
	ldr r10, [r0, #0x14]
	ldr r0, [r0, #0x1c]
	ldr r7, [r8, #0xf8]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	add r11, sp, #0x10
	mov r5, #0x0
	mov r6, #0x1
	mov r4, #0xa
_020988A8:
	mov r0, r11
	bl CPS_SocRead
	cmp r0, #0x0
	beq _02098904
	ldr r1, [sp, #0x10]
	sub r1, r1, r7
	cmp r1, #0x0
	bgt _02098904
	ldrsb r0, [r9, #0x73]
	mov r1, r6
	cmp r0, #0x0
	beq _020988E0
	cmp r0, #0x4
	movne r1, r5
_020988E0:
	cmp r1, #0x0
	beq _020988F8
	ldrb r0, [r9, #0x8]
	cmp r0, #0x4
	movne r0, #0x0
	bne _02098904
_020988F8:
	mov r0, r4
	bl OS_Sleep
	b _020988A8
_02098904:
	ldrsb r1, [r9, #0x73]
	cmp r1, #0x4
	bne _02098954
	cmp r0, #0x0
	addeq sp, sp, #0x14
	moveq r0, #0x0
	ldmeqia sp!, {r4-r11,lr}
	bxeq lr
	ldr r1, [sp, #0x10]
	cmp r10, r1
	movhi r10, r1
	ldr r1, [sp, #0x4]
	mov r2, r10
	bl MI_CpuCopy8
	mov r0, r10
	bl CPS_SocConsume
	add sp, sp, #0x14
	mov r0, r10
	ldmia sp!, {r4-r11,lr}
	bx lr
_02098954:
	cmp r0, #0x0
	moveq r4, #0x0
	beq _02098980
	ldr r4, [sp, #0xc]
	ldr r1, [sp, #0x4]
	ldr r3, [sp, #0x8]
	mov r0, r9
	mov r2, r10
	str r4, [sp, #0x0]
	bl SOCLi_CopyCPSBuffer
	mov r4, r0
_02098980:
	cmp r4, #0x0
	addle sp, sp, #0x14
	movle r0, r4
	ldmleia sp!, {r4-r11,lr}
	bxle lr
	ldrh r0, [r8, #0xfc]
	ldr r1, [r8, #0xf8]
	cmp r1, r0
	blt _020989AC
	mov r0, r9
	bl SOCLi_ConsumeCPSBuffer
_020989AC:
	mov r0, r4
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start SOCLi_ExecReadCommand
SOCLi_ExecReadCommand: ; 0x020989BC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	ldr r0, _02098A10 ; =SOCLi_ReadCallBack
	mov r1, r7
	mov r2, #0x1
	mov r4, r3
	bl SOCLi_CreateCommandPacket
	mov r1, r0
	str r6, [r1, #0x10]
	str r5, [r1, #0x14]
	ldr r2, [sp, #0x18]
	str r4, [r1, #0x18]
	mov r0, r7
	str r2, [r1, #0x1c]
	bl SOCLi_ExecCommandPacketInRecvPipe
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_02098A10: .word SOCLi_ReadCallBack

	arm_func_start SOCLi_ReadCPSBuffer
SOCLi_ReadCPSBuffer:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r0, [r0, #0x64]
	ldr r5, [r0, #0xc4]
	ldr r4, [r0, #0xf8]
	ldr r0, [r5, #0x44]
	subs lr, r0, r4
	bmi _02098A78
	ldrh r12, [r5, #0xa]
	ldr r0, [sp, #0x10]
	cmp lr, #0x0
	strh r12, [r2, #0x0]
	ldrh r2, [r5, #0x18]
	strh r2, [r3, #0x0]
	ldr r2, [r5, #0x1c]
	str r2, [r0, #0x0]
	str lr, [r1, #0x0]
	bne _02098A90
	ldrb r0, [r5, #0x8]
	cmp r0, #0x4
	beq _02098A90
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_02098A78:
	mvn r0, #0x0
	str r0, [r1, #0x0]
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_02098A90:
	ldr r0, [r5, #0x40]
	add r0, r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SOCLi_CopyCPSBuffer
SOCLi_CopyCPSBuffer: ; 0x02098AA4
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x14
	mov r9, r0
	mov r8, r1
	mov r7, r2
	mov r6, r3
	bl OS_DisableInterrupts
	add r1, sp, #0xc
	mov r5, r0
	str r1, [sp, #0x0]
	add r1, sp, #0x8
	mov r0, r9
	add r2, sp, #0x4
	add r3, sp, #0x6
	bl SOCLi_ReadCPSBuffer
	cmp r0, #0x0
	beq _02098B48
	ldr r4, [sp, #0x8]
	cmp r4, #0x0
	mvneq r4, #0x5
	beq _02098B64
	ldrsb r1, [r9, #0x73]
	cmp r7, r4
	movgt r7, r4
	mov r2, #0x1
	cmp r1, #0x0
	beq _02098B18
	cmp r1, #0x4
	movne r2, #0x0
_02098B18:
	cmp r2, #0x0
	mov r1, r8
	mov r2, r7
	movne r4, r7
	bl MI_CpuCopy8
	ldr r1, [r9, #0x64]
	ldrsb r0, [r1, #0xfe]
	cmp r0, #0x0
	ldreq r0, [r1, #0xf8]
	addeq r0, r0, r4
	streq r0, [r1, #0xf8]
	b _02098B64
_02098B48:
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	ldrsh r0, [r9, #0x70]
	moveq r4, #0x0
	mvnne r4, #0x1b
	bic r0, r0, #0x6
	strh r0, [r9, #0x70]
_02098B64:
	cmp r4, #0x0
	blt _02098B9C
	cmp r6, #0x0
	beq _02098B8C
	ldr r1, [sp, #0x30]
	cmp r1, #0x0
	ldrneh r0, [sp, #0x6]
	strneh r0, [r6, #0x0]
	ldrne r0, [sp, #0xc]
	strne r0, [r1, #0x0]
_02098B8C:
	ldrh r0, [r9, #0x74]
	cmp r0, #0x0
	ldreqh r0, [sp, #0x4]
	streqh r0, [r9, #0x74]
_02098B9C:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x14
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start SOCLi_ReadBuffer
SOCLi_ReadBuffer: ; 0x02098BB4
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	ldrsb r12, [r7, #0x73]
	mov r6, r1
	mov r5, r2
	mov r4, r3
	cmp r12, #0x4
	bne _02098BF0
	ldr r4, [sp, #0x18]
	str r4, [sp, #0x0]
	bl SOCLi_ExecReadCommand
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_02098BF0:
	ldr r12, [sp, #0x18]
	str r12, [sp, #0x0]
	bl SOCLi_CopyCPSBuffer
	mvn r1, #0x5
	cmp r0, r1
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldr r1, [sp, #0x1c]
	ands r1, r1, #0x1
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	ldr r12, [sp, #0x18]
	mov r0, r7
	mov r1, r6
	mov r2, r5
	mov r3, r4
	str r12, [sp, #0x0]
	bl SOCLi_ExecReadCommand
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start SOCLi_ReadAndConsumeBuffer
SOCLi_ReadAndConsumeBuffer: ; 0x02098C4C
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	ldr r5, [sp, #0x28]
	mov r7, r0
	ands r0, r5, #0x2
	ldr r5, [r7, #0x64]
	beq _02098C74
	cmp r5, #0x0
	movne r6, #0x1
	bne _02098C78
_02098C74:
	mov r6, #0x0
_02098C78:
	cmp r6, #0x0
	ldrnesb r4, [r5, #0xfe]
	movne r0, #0x1
	strneb r0, [r5, #0xfe]
	ldrsb r0, [r7, #0x73]
	cmp r0, #0x1
	bne _02098CB4
	ldr r0, [sp, #0x20]
	ldr r12, [sp, #0x24]
	str r0, [sp, #0x0]
	mov r0, r7
	str r12, [sp, #0x4]
	bl SOCLi_ReadUdpBuffer
	mov r8, r0
	b _02098CDC
_02098CB4:
	ldr r0, [sp, #0x20]
	ldr r12, [sp, #0x24]
	str r0, [sp, #0x0]
	mov r0, r7
	str r12, [sp, #0x4]
	bl SOCLi_ReadBuffer
	movs r8, r0
	bmi _02098CDC
	mov r0, r7
	bl SOCLi_ConsumeBuffer
_02098CDC:
	cmp r6, #0x0
	strneb r4, [r5, #0xfe]
	mov r0, r8
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr

	arm_func_start SOCLi_ReadFrom
SOCLi_ReadFrom:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0xc
	mov r9, r0
	mov r8, r1
	mov r7, r2
	mov r6, r3
	bl SOCL_SocketIsInvalid
	cmp r0, #0x0
	addne sp, sp, #0xc
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r9,lr}
	bxne lr
	ldr r0, [sp, #0x2c]
	ands r0, r0, #0x4
	bne _02098D3C
	ldrsb r0, [r9, #0x72]
	cmp r0, #0x0
	bne _02098D5C
_02098D3C:
	ldrsb r0, [r9, #0x73]
	cmp r0, #0x4
	addeq sp, sp, #0xc
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r4, #0x0
	b _02098D78
_02098D5C:
	bl OS_GetProcMode
	cmp r0, #0x12
	addeq sp, sp, #0xc
	mvneq r0, #0x1b
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	mov r4, #0x1
_02098D78:
	cmp r9, #0x0
	mov r1, #0x0
	beq _02098D90
	ldrsh r0, [r9, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_02098D90:
	cmp r1, #0x0
	addeq sp, sp, #0xc
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldrsb r0, [r9, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _02098DBC
	cmp r0, #0x4
	movne r1, #0x0
_02098DBC:
	cmp r1, #0x0
	beq _02098DEC
	ldrsh r0, [r9, #0x70]
	ands r0, r0, #0x4
	beq _02098DDC
	ldrsh r0, [r9, #0x70]
	ands r0, r0, #0x8
	beq _02098DEC
_02098DDC:
	add sp, sp, #0xc
	mvn r0, #0x37
	ldmia sp!, {r4-r9,lr}
	bx lr
_02098DEC:
	ands r0, r4, #0x1
	ldr r5, [r9, #0x64]
	bne _02098E18
	add r0, r5, #0xe0
	bl OS_TryLockMutex
	cmp r0, #0x0
	bne _02098E20
	add sp, sp, #0xc
	mvn r0, #0x5
	ldmia sp!, {r4-r9,lr}
	bx lr
_02098E18:
	add r0, r5, #0xe0
	bl OS_LockMutex
_02098E20:
	ldr r0, [sp, #0x28]
	ldr r12, [sp, #0x2c]
	str r0, [sp, #0x0]
	str r4, [sp, #0x4]
	mov r0, r9
	mov r1, r8
	mov r2, r7
	mov r3, r6
	str r12, [sp, #0x8]
	bl SOCLi_ReadAndConsumeBuffer
	mov r4, r0
	add r0, r5, #0xe0
	bl OS_UnlockMutex
	mov r0, r4
	add sp, sp, #0xc
	ldmia sp!, {r4-r9,lr}
	bx lr

; libsoc.a:socl_write.a

	arm_func_start SOCLi_MemCpy
SOCLi_MemCpy: ; 0x02098E64
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r6, r2
	ldr r5, [r6, #0x14]
	ldr r4, [r6, #0x1c]
	cmp r5, r1
	mov r7, r0
	movgt r5, r1
	movgt r4, #0x0
	bgt _02098E98
	sub r0, r1, r5
	cmp r4, r0
	movgt r4, r0
_02098E98:
	cmp r5, #0x0
	ble _02098EC8
	ldr r0, [r6, #0x10]
	mov r1, r7
	mov r2, r5
	bl MI_CpuCopy8
	ldr r0, [r6, #0x10]
	add r0, r0, r5
	str r0, [r6, #0x10]
	ldr r0, [r6, #0x14]
	sub r0, r0, r5
	str r0, [r6, #0x14]
_02098EC8:
	cmp r4, #0x0
	ble _02098EF8
	ldr r0, [r6, #0x18]
	mov r2, r4
	add r1, r7, r5
	bl MI_CpuCopy8
	ldr r0, [r6, #0x18]
	add r0, r0, r4
	str r0, [r6, #0x18]
	ldr r0, [r6, #0x1c]
	sub r0, r0, r4
	str r0, [r6, #0x1c]
_02098EF8:
	add r0, r5, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start SOCLi_GetOptimumSendBufLen
SOCLi_GetOptimumSendBufLen: ; 0x02098F08
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _02098FBC ; =OSi_ThreadInfo
	mov r4, r0
	ldr r0, [r1, #0x4]
	ldr r5, [r0, #0xa4]
	bl OS_DisableInterrupts
	cmp r5, #0x0
	beq _02098F74
	ldrh r3, [r5, #0x2e]
	cmp r3, #0x0
	beq _02098F64
	ldrh r2, [r5, #0x2c]
	cmp r2, #0x0
	beq _02098F64
	ldr r1, _02098FC0 ; =SOCLiCPSConfig
	cmp r3, r2
	ldr r1, [r1, #0x24]
	movgt r3, r2
	cmp r3, r1
	movgt r3, r1
	mov r5, r3, lsl #0x1
	b _02098F80
_02098F64:
	ldr r1, _02098FC0 ; =SOCLiCPSConfig
	ldr r1, [r1, #0x24]
	mov r5, r1, lsl #0x1
	b _02098F80
_02098F74:
	ldr r1, _02098FC0 ; =SOCLiCPSConfig
	ldr r1, [r1, #0x24]
	mov r5, r1, lsl #0x1
_02098F80:
	bl OS_RestoreInterrupts
	cmp r5, #0x0
	ble _02098FAC
	mov r0, r4
	mov r1, r5
	bl _s32_div_f
	cmp r0, #0x0
	mulgt r0, r5, r0
	addgt sp, sp, #0x4
	ldmgtia sp!, {r4-r5,lr}
	bxgt lr
_02098FAC:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_02098FBC: .word OSi_ThreadInfo
_02098FC0: .word SOCLiCPSConfig

	arm_func_start SOCLi_WriteCallBack
SOCLi_WriteCallBack: ; 0x02098FC4
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r8, r0
	ldr r7, [r8, #0x4]
	mov r4, #0x0
	ldrsb r0, [r7, #0x73]
	ldr r6, [r7, #0x68]
	mov r1, #0x1
	cmp r0, #0x0
	beq _02098FF4
	cmp r0, #0x4
	movne r1, r4
_02098FF4:
	cmp r1, #0x0
	beq _02099008
	ldrsh r0, [r7, #0x70]
	ands r0, r0, #0x4
	beq _020990DC
_02099008:
	ldr r2, [r8, #0x28]
	cmp r2, #0x0
	beq _02099020
	ldrh r0, [r8, #0x24]
	ldrh r1, [r8, #0x26]
	bl CPS_SocPingMode
_02099020:
	ldrsb r1, [r7, #0x73]
	mov r0, #0x1
	cmp r1, #0x0
	beq _02099038
	cmp r1, #0x4
	movne r0, #0x0
_02099038:
	cmp r0, #0x0
	movne r2, #0x36
	moveq r2, #0x2a
	ldr r0, [r7, #0x4c]
	cmp r1, #0x0
	add r5, r0, r2
	beq _0209905C
	cmp r1, #0x4
	bne _02099070
_0209905C:
	ldr r0, [r7, #0x48]
	sub r0, r0, r2
	bl SOCLi_GetOptimumSendBufLen
	mov r9, r0
	b _02099078
_02099070:
	ldr r0, [r7, #0x48]
	sub r9, r0, r2
_02099078:
	mov r0, r5
	mov r1, r9
	mov r2, r8
	bl SOCLi_MemCpy
	mov r1, r0
	cmp r1, #0x0
	ble _020990E0
	mov r0, r5
	bl CPS_SocWrite
	cmp r0, #0x0
	bgt _020990D4
	ldrsb r0, [r7, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _020990BC
	cmp r0, #0x4
	movne r1, #0x0
_020990BC:
	cmp r1, #0x0
	ldrnesh r0, [r7, #0x70]
	mvn r4, #0x4b
	bicne r0, r0, #0xe
	strneh r0, [r7, #0x70]
	b _020990E0
_020990D4:
	add r4, r4, r0
	b _02099078
_020990DC:
	mvn r4, #0x4b
_020990E0:
	ldrh r2, [r8, #0x20]
	add r1, r6, #0x100
	add r0, r6, #0x104
	strh r2, [r1, #0x2]
	bl OS_WakeupThread
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr

	arm_func_start SOCLi_ExecWriteCommand
SOCLi_ExecWriteCommand:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r9, r0
	ldr r6, [r9, #0x68]
	mov r4, r1
	mov r8, r2
	ldr r1, [r6, #0x10c]
	ldr r2, [sp, #0x28]
	ldr r0, _0209929C ; =SOCLi_WriteCallBack
	mov r7, r3
	bl SOCLi_CreateCommandPacket
	movs r5, r0
	addeq sp, sp, #0x4
	mvneq r0, #0x20
	ldmeqia sp!, {r4-r9,lr}
	bxeq lr
	ldr r0, [sp, #0x28]
	ands r0, r0, #0x1
	beq _02099164
	ldrsb r0, [r9, #0x73]
	cmp r0, #0x1
	movne r0, #0x3
	strneb r0, [r5, #0xd]
	bne _0209916C
_02099164:
	mov r0, #0x0
	strb r0, [r5, #0xd]
_0209916C:
	ldr r2, [r6, #0xf8]
	add r1, r7, r8
	cmp r1, r2
	ldr r3, [r6, #0xfc]
	bge _020991A0
	add r0, r3, r7
	str r0, [r5, #0x10]
	str r8, [r5, #0x14]
	mov r0, #0x0
	str r0, [r5, #0x18]
	mov r7, r1
	str r0, [r5, #0x1c]
	b _020991D8
_020991A0:
	add r0, r3, r7
	str r0, [r5, #0x10]
	sub r0, r2, r7
	str r0, [r5, #0x14]
	str r3, [r5, #0x18]
	ldr r0, [r5, #0x14]
	sub r0, r8, r0
	str r0, [r5, #0x1c]
	ldr r7, [r5, #0x1c]
	ldr r0, [r5, #0x14]
	ldr r1, [r5, #0x18]
	mov r2, r7
	add r0, r4, r0
	bl MI_CpuCopy8
_020991D8:
	ldr r1, [r5, #0x10]
	ldr r2, [r5, #0x14]
	mov r0, r4
	bl MI_CpuCopy8
	add r0, r6, #0x100
	ldrh r4, [r0, #0x0]
	strh r7, [r5, #0x20]
	ldrh r1, [r5, #0x20]
	strh r1, [r0, #0x0]
	ldrsb r0, [r9, #0x73]
	cmp r0, #0x1
	bne _02099268
	ldrh r0, [r9, #0x74]
	cmp r0, #0x0
	bne _02099224
	bl CPS_SocGetEport
	strh r0, [r9, #0x74]
	ldrh r0, [r9, #0x74]
	strh r0, [r9, #0xa]
_02099224:
	ldrh r0, [r9, #0x74]
	strh r0, [r5, #0x24]
	ldr r1, [r9, #0x78]
	cmp r1, #0x0
	beq _02099244
	ldr r0, [sp, #0x24]
	cmp r0, #0x0
	beq _02099258
_02099244:
	ldr r1, [sp, #0x24]
	ldrh r0, [sp, #0x20]
	str r1, [r5, #0x28]
	strh r0, [r5, #0x26]
	b _02099270
_02099258:
	str r1, [r5, #0x28]
	ldrh r0, [r9, #0x76]
	strh r0, [r5, #0x26]
	b _02099270
_02099268:
	mov r0, #0x0
	str r0, [r5, #0x28]
_02099270:
	ldr r0, [r6, #0x10c]
	mov r1, r5
	bl SOCLi_ExecCommandPacketInSendPipe
	cmp r0, #0x0
	addne r0, r6, #0x100
	movne r8, #0x0
	strneh r4, [r0, #0x0]
	mov r0, r8
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,lr}
	bx lr
	.balign 4
_0209929C: .word SOCLi_WriteCallBack

	arm_func_start SOCLi_GetWriteBufferFreeSize
SOCLi_GetWriteBufferFreeSize:
	ldr r2, [r0, #0x68]
	add r0, r2, #0x100
	ldrh r1, [r0, #0x0]
	ldrh r0, [r0, #0x2]
	ldr r2, [r2, #0xf8]
	sub r0, r0, r1
	subs r0, r0, #0x1
	addmi r0, r0, r2
	bx lr

	arm_func_start SOCLi_AllocWriteBuffer
SOCLi_AllocWriteBuffer: ; 0x020992C4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	mov r10, r0
	mov r9, r1
	mov r8, r2
	cmp r8, r9
	mov r11, r3
	ldr r7, [r10, #0x68]
	movgt r8, r9
	bl OS_DisableInterrupts
	ldr r1, [sp, #0x28]
	str r0, [sp, #0x0]
	and r5, r1, #0x1
	add r4, r7, #0x104
_020992FC:
	mov r0, r10
	bl SOCLi_GetWriteBufferFreeSize
	mov r6, r0
	cmp r6, r8
	blt _02099328
	add r0, r7, #0x100
	ldrh r0, [r0, #0x0]
	cmp r6, r9
	movge r6, r9
	str r0, [r11, #0x0]
	b _02099340
_02099328:
	cmp r5, #0x0
	moveq r6, #0x0
	beq _02099340
	mov r0, r4
	bl OS_SleepThread
	b _020992FC
_02099340:
	ldr r0, [sp, #0x0]
	bl OS_RestoreInterrupts
	mov r0, r6
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start SOCLi_WriteBuffer
SOCLi_WriteBuffer: ; 0x02099358
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x1c
	mov r10, r0
	ldr r4, [r10, #0x68]
	ldrsb r0, [r10, #0x73]
	ldr r4, [r4, #0x10c]
	mov r9, r1
	cmp r0, #0x1
	ldr r0, [r4, #0x48]
	mov r8, r2
	str r3, [sp, #0xc]
	ldr r7, [sp, #0x40]
	ldr r6, [sp, #0x44]
	mov r4, #0x0
	bne _020993B4
	sub r0, r0, #0x2a
	cmp r8, r0
	addgt sp, sp, #0x1c
	mvngt r0, #0x22
	ldmgtia sp!, {r4-r11,lr}
	bxgt lr
	str r8, [sp, #0x10]
	b _020993C4
_020993B4:
	sub r0, r0, #0x36
	str r0, [sp, #0x10]
	cmp r8, r0
	strle r8, [sp, #0x10]
_020993C4:
	cmp r8, #0x0
	ble _02099460
	and r11, r6, #0x1
_020993D0:
	ldr r2, [sp, #0x10]
	mov r0, r10
	mov r1, r8
	add r3, sp, #0x14
	str r6, [sp, #0x0]
	bl SOCLi_AllocWriteBuffer
	mov r5, r0
	cmp r5, #0x0
	ble _02099438
	ldr r0, [sp, #0xc]
	mov r1, r9
	str r0, [sp, #0x0]
	str r7, [sp, #0x4]
	str r6, [sp, #0x8]
	ldr r3, [sp, #0x14]
	mov r0, r10
	mov r2, r5
	bl SOCLi_ExecWriteCommand
	cmp r0, #0x0
	addle sp, sp, #0x1c
	mvnle r0, #0x5
	ldmleia sp!, {r4-r11,lr}
	bxle lr
	add r9, r9, r5
	sub r8, r8, r5
	add r4, r4, r5
_02099438:
	cmp r11, #0x0
	bne _02099458
	cmp r5, #0x0
	bgt _02099460
	add sp, sp, #0x1c
	mvn r0, #0x5
	ldmia sp!, {r4-r11,lr}
	bx lr
_02099458:
	cmp r8, #0x0
	bgt _020993D0
_02099460:
	mov r0, r4
	add sp, sp, #0x1c
	ldmia sp!, {r4-r11,lr}
	bx lr

	arm_func_start SOCL_WriteTo
SOCL_WriteTo: ; 0x02099470
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, r3
	bl SOCL_SocketIsInvalid
	cmp r0, #0x0
	addne sp, sp, #0x8
	mvnne r0, #0x1b
	ldmneia sp!, {r4-r8,lr}
	bxne lr
	cmp r8, #0x0
	mov r1, #0x0
	beq _020994B8
	ldrsh r0, [r8, #0x70]
	ands r0, r0, #0x1
	movne r1, #0x1
_020994B8:
	cmp r1, #0x0
	addeq sp, sp, #0x8
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	ldrsb r0, [r8, #0x73]
	mov r1, #0x1
	cmp r0, #0x0
	beq _020994E4
	cmp r0, #0x4
	movne r1, #0x0
_020994E4:
	cmp r1, #0x0
	beq _02099514
	ldrsh r0, [r8, #0x70]
	ands r0, r0, #0x4
	beq _02099504
	ldrsh r0, [r8, #0x70]
	ands r0, r0, #0x8
	beq _02099514
_02099504:
	add sp, sp, #0x8
	mvn r0, #0x37
	ldmia sp!, {r4-r8,lr}
	bx lr
_02099514:
	ldr r0, [sp, #0x24]
	ldr r4, [r8, #0x68]
	ands r0, r0, #0x4
	bne _02099530
	ldrsb r0, [r8, #0x72]
	cmp r0, #0x0
	bne _02099554
_02099530:
	add r0, r4, #0xe0
	bl OS_TryLockMutex
	cmp r0, #0x0
	addeq sp, sp, #0x8
	mvneq r0, #0x5
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	mov r12, #0x0
	b _02099560
_02099554:
	add r0, r4, #0xe0
	bl OS_LockMutex
	mov r12, #0x1
_02099560:
	ldr r1, [sp, #0x20]
	mov r0, r8
	str r1, [sp, #0x0]
	mov r1, r7
	mov r2, r6
	mov r3, r5
	str r12, [sp, #0x4]
	bl SOCLi_WriteBuffer
	mov r5, r0
	add r0, r4, #0xe0
	bl OS_UnlockMutex
	mov r0, r5
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
