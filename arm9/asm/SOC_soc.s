	.include "asm/macros.inc"
	.include "global.inc"

	.section .data

	.global SOCLSocketParamUDP
SOCLSocketParamUDP: ; 0x021061C4
	.byte 0x01, 0x01, 0xC0, 0x05, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08
	.byte 0x00, 0x08, 0x0C, 0x20, 0x00, 0x00, 0x00, 0x00

	.global SOCLSocketParamTCP
SOCLSocketParamTCP: ; 0x021061DC
	.byte 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x66, 0x04, 0x00, 0x00, 0x00, 0x00, 0x61, 0x08, 0x00, 0x00
	.byte 0x00, 0x08, 0x0C, 0x20, 0x00, 0x08, 0x0D, 0x20

	.global SOCLSocketParamUDPSend
SOCLSocketParamUDPSend: ; 0x021061F4
	.byte 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEA, 0x05, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x06, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0D, 0x20

	.global UNK_0210620C
UNK_0210620C: ; 0x0210620C
	.byte 0x25, 0x64, 0x2E, 0x25, 0x64, 0x2E, 0x25, 0x64, 0x2E, 0x25, 0x64, 0x00

	.section .bss

	.global UNK_021C8D38
UNK_021C8D38: ; 0x021C8D38
	.space 0x4

	.global FreeFunc_SOC
FreeFunc_SOC: ; 0x021C8D3C
	.space 0x4

	.global AllocFunc_SOC
AllocFunc_SOC: ; 0x021C8D40
	.space 0x4

	.global UNK_021C8D44
UNK_021C8D44: ; 0x021C8D44
	.space 0x8

	.global UNK_021C8D4C
UNK_021C8D4C: ; 0x021C8D4C
	.space 0x10

	.global UNK_021C8D5C
UNK_021C8D5C: ; 0x021C8D5C
	.space 0x10

	.global UNK_021C8D6C
UNK_021C8D6C: ; 0x021C8D6C
	.space 0x38

	.global UNK_021C8DA4
UNK_021C8DA4: ; 0x021C8DA4
	.space 0x104

	.text

	arm_func_start SOC_Poll
SOC_Poll: ; 0x0209A0AC
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc
	mov r9, r2
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x8]
	mov r0, #0x0
	mov r8, r3
	mvn r2, #0x0
	cmp r8, r2
	cmpeq r9, r2
	movne r11, #0x1
	mov r10, r1
	moveq r11, #0x0
	str r0, [sp, #0x4]
_0209A0E8:
	ldr r5, [sp, #0x4]
	ldr r7, [sp, #0x0]
	mov r6, r5
	cmp r10, #0x0
	bls _0209A128
_0209A0FC:
	ldrsh r1, [r7, #0x4]
	ldr r0, [r7, #0x0]
	orr r4, r1, #0xe0
	bl SOCL_GetStatus
	ands r0, r4, r0
	strh r0, [r7, #0x6]
	add r6, r6, #0x1
	addne r5, r5, #0x1
	cmp r6, r10
	add r7, r7, #0x8
	blo _0209A0FC
_0209A128:
	cmp r5, #0x0
	bgt _0209A160
	cmp r11, #0x0
	beq _0209A148
	mov r1, #0x0
	subs r0, r1, r9
	sbcs r0, r1, r8
	bge _0209A160
_0209A148:
	ldr r0, [sp, #0x8]
	bl OS_Sleep
	ldr r0, _0209A170 ; =0x0000020B
	subs r9, r9, r0
	sbc r8, r8, #0x0
	b _0209A0E8
_0209A160:
	mov r0, r5
	add sp, sp, #0xc
	ldmia sp!, {r4-r11,lr}
	bx lr
	.balign 4
_0209A170: .word 0x0000020B

	arm_func_start SOC_U32to4U8
SOC_U32to4U8: ; 0x0209A174
	mov r2, r0, lsr #0x18
	strb r2, [r1, #0x0]
	mov r2, r0, lsr #0x10
	strb r2, [r1, #0x1]
	mov r2, r0, lsr #0x8
	strb r2, [r1, #0x2]
	strb r0, [r1, #0x3]
	bx lr

	arm_func_start SOC_InetNtoP
SOC_InetNtoP: ; 0x0209A194
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x18
	cmp r0, #0x2
	mov r4, r2
	addne sp, sp, #0x18
	movne r0, #0x0
	ldmneia sp!, {r4,lr}
	bxne lr
	cmp r3, #0x10
	addcc sp, sp, #0x18
	movcc r0, #0x0
	ldmccia sp!, {r4,lr}
	bxcc lr
	mov r0, r1
	add r1, sp, #0xc
	mov r2, #0x4
	bl MI_CpuCopy8
	ldr r0, [sp, #0xc]
	add r1, sp, #0x10
	bl SOC_U32to4U8
	ldrb r1, [sp, #0x12]
	ldr r2, _0209A220 ; =UNK_0210620C
	mov r0, r4
	str r1, [sp, #0x0]
	ldrb r3, [sp, #0x11]
	mov r1, #0x10
	str r3, [sp, #0x4]
	ldrb r3, [sp, #0x10]
	str r3, [sp, #0x8]
	ldrb r3, [sp, #0x13]
	bl OS_SNPrintf
	mov r0, r4
	add sp, sp, #0x18
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209A220: .word UNK_0210620C

	arm_func_start SOC_InetAtoN
SOC_InetAtoN: ; 0x0209A224
	stmdb sp!, {r4,lr}
	mov r4, r1
	bl SOCL_InetAtoH
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	mov r2, r0, lsr #0x18
	mov r1, r0, lsr #0x8
	mov r3, r0, lsl #0x8
	mov r12, r0, lsl #0x18
	and r2, r2, #0xff
	and r0, r1, #0xff00
	and r1, r3, #0xff0000
	orr r0, r2, r0
	and r2, r12, #0xff000000
	orr r0, r1, r0
	orr r0, r2, r0
	str r0, [r4, #0x0]
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SOC_InetNtoA
SOC_InetNtoA: ; 0x0209A27C
	stmdb sp!, {r0-r3}
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _0209A2B0 ; =UNK_021C8D5C
	add r1, sp, #0x8
	mov r0, #0x2
	mov r3, #0x10
	bl SOC_InetNtoP
	ldr r0, _0209A2B0 ; =UNK_021C8D5C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_0209A2B0: .word UNK_021C8D5C

	arm_func_start SOC_Cleanup
SOC_Cleanup: ; 0x0209A2B4
	ldr ip, _0209A2BC ; =SOCL_Cleanup
	bx r12
	.balign 4
_0209A2BC: .word SOCL_Cleanup

	arm_func_start SOC_Startup
SOC_Startup: ; 0x0209A2C0
	stmdb sp!, {r4-r8,lr}
	ldr r1, [r0, #0xc]
	ldr ip, _0209A430 ; =UNK_021C8D6C
	cmp r1, #0x1
	moveq r1, #0x1
	movne r1, #0x0
	str r1, [r12, #0x0]
	ldr r6, [r0, #0x10]
	ldr r5, _0209A434 ; =AllocFunc_SOCL
	mov r2, r6, lsr #0x18
	mov r1, r6, lsr #0x8
	mov r3, r6, lsl #0x8
	and r2, r2, #0xff
	and r1, r1, #0xff00
	mov r6, r6, lsl #0x18
	orr r1, r2, r1
	and r3, r3, #0xff0000
	orr r1, r3, r1
	and r2, r6, #0xff000000
	orr r1, r2, r1
	str r1, [r12, #0x4]
	ldr r7, [r0, #0x14]
	ldr r4, _0209A438 ; =FreeFunc_SOCL
	mov r2, r7, lsr #0x18
	mov r1, r7, lsr #0x8
	mov r6, r7, lsl #0x8
	and r2, r2, #0xff
	and r1, r1, #0xff00
	mov r7, r7, lsl #0x18
	orr r1, r2, r1
	and r6, r6, #0xff0000
	and r2, r7, #0xff000000
	orr r1, r6, r1
	orr r1, r2, r1
	str r1, [r12, #0x8]
	ldr r1, [r0, #0x18]
	ldr r3, _0209A43C ; =AllocFunc_SOC
	mov r7, r1, lsr #0x18
	mov r6, r1, lsr #0x8
	mov r8, r1, lsl #0x8
	and r7, r7, #0xff
	and r6, r6, #0xff00
	mov r1, r1, lsl #0x18
	orr r6, r7, r6
	and r8, r8, #0xff0000
	and r7, r1, #0xff000000
	orr r1, r8, r6
	orr r1, r7, r1
	str r1, [r12, #0xc]
	ldr r1, [r0, #0x1c]
	ldr r2, _0209A440 ; =FreeFunc_SOC
	mov r7, r1, lsr #0x18
	mov r6, r1, lsr #0x8
	mov r8, r1, lsl #0x8
	and r7, r7, #0xff
	and r6, r6, #0xff00
	mov r1, r1, lsl #0x18
	orr r6, r7, r6
	and r8, r8, #0xff0000
	and r7, r1, #0xff000000
	orr r1, r8, r6
	orr r1, r7, r1
	str r1, [r12, #0x10]
	ldr r1, [r0, #0x20]
	mov lr, #0x40
	mov r7, r1, lsr #0x18
	mov r6, r1, lsr #0x8
	mov r8, r1, lsl #0x8
	and r7, r7, #0xff
	and r6, r6, #0xff00
	mov r1, r1, lsl #0x18
	orr r6, r7, r6
	and r8, r8, #0xff0000
	and r7, r1, #0xff000000
	orr r1, r8, r6
	orr r1, r7, r1
	str r5, [r12, #0x18]
	str r4, [r12, #0x1c]
	str r1, [r12, #0x14]
	ldr r1, [r0, #0x4]
	str r1, [r3, #0x0]
	ldr r1, [r0, #0x8]
	str lr, [r12, #0x20]
	str r1, [r2, #0x0]
	ldr r1, [r0, #0x2c]
	str r1, [r12, #0x30]
	ldr r1, [r0, #0x30]
	mov r0, r12
	str r1, [r12, #0x34]
	bl SOCL_Startup
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_0209A430: .word UNK_021C8D6C
_0209A434: .word AllocFunc_SOCL
_0209A438: .word FreeFunc_SOCL
_0209A43C: .word AllocFunc_SOC
_0209A440: .word FreeFunc_SOC

	arm_func_start FreeFunc_SOCL
FreeFunc_SOCL: ; 0x0209A444
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r1, _0209A480 ; =FreeFunc_SOC
	ldr r2, [r0, #-0x4]
	ldr r3, [r1, #0x0]
	sub r1, r0, #0x4
	mov r0, #0x0
	blx r3
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209A480: .word FreeFunc_SOC

	arm_func_start AllocFunc_SOCL
AllocFunc_SOCL: ; 0x0209A484
	stmdb sp!, {r4,lr}
	ldr r1, _0209A4B0 ; =AllocFunc_SOC
	add r4, r0, #0x4
	ldr r2, [r1, #0x0]
	mov r1, r4
	mov r0, #0x0
	blx r2
	cmp r0, #0x0
	strne r4, [r0], #0x4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_0209A4B0: .word AllocFunc_SOC

	arm_func_start SOC_Fcntl
SOC_Fcntl: ; 0x0209A4B4
	cmp r0, #0x0
	mvneq r0, #0x0
	bxeq lr
	cmp r1, #0x3
	beq _0209A4D4
	cmp r1, #0x4
	beq _0209A4E8
	b _0209A4FC
_0209A4D4:
	ldrsb r0, [r0, #0x72]
	cmp r0, #0x1
	moveq r0, #0x0
	movne r0, #0x4
	bx lr
_0209A4E8:
	ands r1, r2, #0x4
	movne r1, #0x0
	strneb r1, [r0, #0x72]
	moveq r1, #0x1
	streqb r1, [r0, #0x72]
_0209A4FC:
	mov r0, #0x0
	bx lr

	arm_func_start SOC_Accept
SOC_Accept: ; 0x0209A504
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r4, r1
	add r1, sp, #0x0
	add r2, sp, #0x4
	bl SOCL_Accept
	cmp r0, #0x0
	addlt sp, sp, #0x8
	ldmltia sp!, {r4,lr}
	bxlt lr
	ldrh r1, [sp, #0x0]
	mov r2, r1, asr #0x8
	mov r1, r1, lsl #0x8
	and r2, r2, #0xff
	and r1, r1, #0xff00
	orr r1, r2, r1
	strh r1, [r4, #0x2]
	ldr r12, [sp, #0x4]
	mov r2, r12, lsr #0x18
	mov r1, r12, lsr #0x8
	mov r3, r12, lsl #0x8
	mov r12, r12, lsl #0x18
	and r2, r2, #0xff
	and r1, r1, #0xff00
	and r3, r3, #0xff0000
	orr r1, r2, r1
	and r2, r12, #0xff000000
	orr r1, r3, r1
	orr r1, r2, r1
	str r1, [r4, #0x4]
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SOC_Listen
SOC_Listen: ; 0x0209A588
	ldr ip, _0209A590 ; =SOCL_Listen
	bx r12
	.balign 4
_0209A590: .word SOCL_Listen

	arm_func_start SOC_GetResolver
SOC_GetResolver: ; 0x0209A594
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r12, [r1, #0x0]
	ldr r0, [r0, #0x0]
	mov r2, r12, lsr #0x18
	mov r4, r0, lsr #0x18
	mov lr, r0, lsr #0x8
	mov r1, r12, lsr #0x8
	mov r5, r0, lsl #0x8
	mov r3, r12, lsl #0x8
	mov r0, r0, lsl #0x18
	mov r12, r12, lsl #0x18
	and r4, r4, #0xff
	and lr, lr, #0xff00
	and r2, r2, #0xff
	and r1, r1, #0xff00
	and r5, r5, #0xff0000
	orr r4, r4, lr
	and r3, r3, #0xff0000
	orr r1, r2, r1
	and lr, r0, #0xff000000
	orr r0, r5, r4
	and r2, r12, #0xff000000
	orr r1, r3, r1
	orr r0, lr, r0
	orr r1, r2, r1
	bl SOCL_SetResolver
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start SOC_GetHostID
SOC_GetHostID: ; 0x0209A60C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl SOCL_GetHostID
	mov r2, r0, lsr #0x18
	mov r1, r0, lsr #0x8
	mov r3, r0, lsl #0x8
	mov r12, r0, lsl #0x18
	and r2, r2, #0xff
	and r0, r1, #0xff00
	and r1, r3, #0xff0000
	orr r0, r2, r0
	and r2, r12, #0xff000000
	orr r0, r1, r0
	orr r0, r2, r0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start SOC_GetSockName
SOC_GetSockName: ; 0x0209A650
	stmdb sp!, {r4-r6,lr}
	movs r5, r0
	mov r4, r1
	mvneq r0, #0x26
	ldmeqia sp!, {r4-r6,lr}
	bxeq lr
	bl SOCL_GetHostID
	cmp r5, #0x0
	ldrneh r1, [r5, #0x74]
	mov r2, r0, lsr #0x18
	mov r6, #0x8
	moveq r1, #0x0
	cmp r0, #0x0
	moveq r1, #0x0
	mov r1, r1, lsl #0x10
	mov r3, r1, lsr #0x10
	mov r5, r3, asr #0x8
	mov lr, r3, lsl #0x8
	strb r6, [r4, #0x0]
	mov r6, #0x2
	mov r1, r0, lsr #0x8
	mov r3, r0, lsl #0x8
	mov r12, r0, lsl #0x18
	and r0, r1, #0xff00
	and r2, r2, #0xff
	orr r0, r2, r0
	and r1, r3, #0xff0000
	and r5, r5, #0xff
	and lr, lr, #0xff00
	strb r6, [r4, #0x1]
	orr r3, r5, lr
	and r2, r12, #0xff000000
	orr r0, r1, r0
	strh r3, [r4, #0x2]
	orr r0, r2, r0
	str r0, [r4, #0x4]
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr

	arm_func_start SOC_GetHostByAddr
SOC_GetHostByAddr: ; 0x0209A6EC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl SOCL_Resolve
	movs r4, r0
	addeq sp, sp, #0x4
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	ldr r0, _0209A7A4 ; =UNK_021C8DA4
	ldr r2, _0209A7A8 ; =0x00000101
	mov r1, #0x0
	bl MI_CpuFill8
	ldr r0, _0209A7A4 ; =UNK_021C8DA4
	ldr r2, _0209A7A8 ; =0x00000101
	mov r1, r5
	bl STD_CopyLString
	mov r1, r4, lsr #0x18
	mov r0, r4, lsr #0x8
	mov r2, r4, lsl #0x8
	mov r3, r4, lsl #0x18
	and r1, r1, #0xff
	and r0, r0, #0xff00
	and r2, r2, #0xff0000
	orr r0, r1, r0
	and r3, r3, #0xff000000
	orr r1, r2, r0
	ldr r5, _0209A7A4 ; =UNK_021C8DA4
	ldr r0, _0209A7AC ; =UNK_021C8D4C
	ldr ip, _0209A7B0 ; =UNK_021C8D44
	mov r4, #0x0
	ldr r2, _0209A7B4 ; =UNK_021C8D38
	orr r1, r3, r1
	mov lr, #0x2
	mov r3, #0x4
	str r5, [r0, #0x0]
	str r4, [r0, #0x4]
	strh lr, [r0, #0x8]
	strh r3, [r0, #0xa]
	str r12, [r0, #0xc]
	str r2, [r12, #0x0]
	str r4, [r12, #0x4]
	str r1, [r2, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_0209A7A4: .word UNK_021C8DA4 ; entName
_0209A7A8: .word 0x00000101
_0209A7AC: .word UNK_021C8D4C ; hostent
_0209A7B0: .word UNK_021C8D44 ; hostAddrList
_0209A7B4: .word UNK_021C8D38 ; hostip

	arm_func_start SOC_Close
SOC_Close: ; 0x0209A7B8
	ldr ip, _0209A7C0 ; =SOCL_Close
	bx r12
	.balign 4
_0209A7C0: .word SOCL_Close

	arm_func_start SOC_Shutdown
SOC_Shutdown: ; 0x0209A7C4
	ldr ip, _0209A7CC ; =SOCL_Shutdown
	bx r12
	.balign 4
_0209A7CC: .word SOCL_Shutdown

	arm_func_start SOC_SendTo
SOC_SendTo: ; 0x0209A7D0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0xc
	ldr r5, [sp, #0x20]
	cmp r5, #0x0
	moveq r5, #0x0
	moveq r4, r5
	beq _0209A83C
	ldrh r4, [r5, #0x2]
	ldr r6, [r5, #0x4]
	mov r7, r4, asr #0x8
	mov r12, r4, lsl #0x8
	mov r4, r6, lsr #0x18
	mov lr, r6, lsr #0x8
	mov r5, r6, lsl #0x8
	mov r6, r6, lsl #0x18
	and r7, r7, #0xff
	and r12, r12, #0xff00
	orr r7, r7, r12
	and r4, r4, #0xff
	and lr, lr, #0xff00
	and r5, r5, #0xff0000
	orr r4, r4, lr
	mov r12, r7, lsl #0x10
	orr r4, r5, r4
	and r6, r6, #0xff000000
	mov r5, r12, lsr #0x10
	orr r4, r6, r4
_0209A83C:
	str r4, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r3, r5
	bl SOCL_WriteTo
	add sp, sp, #0xc
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start SOC_Send
SOC_Send: ; 0x0209A858
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	mov r12, #0x0
	str r12, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r3, r12
	bl SOCL_WriteTo
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr

	arm_func_start SOC_RecvFrom
SOC_RecvFrom: ; 0x0209A880
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	add r12, sp, #0xc
	str r12, [sp, #0x0]
	str r3, [sp, #0x4]
	add r3, sp, #0x8
	bl SOCLi_ReadFrom
	cmp r0, #0x0
	addlt sp, sp, #0x14
	ldmltia sp!, {lr}
	bxlt lr
	ldr r1, [sp, #0x18]
	cmp r1, #0x0
	addeq sp, sp, #0x14
	ldmeqia sp!, {lr}
	bxeq lr
	ldrh r2, [sp, #0x8]
	mov r3, r2, asr #0x8
	mov r2, r2, lsl #0x8
	and r3, r3, #0xff
	and r2, r2, #0xff00
	orr r2, r3, r2
	strh r2, [r1, #0x2]
	ldr lr, [sp, #0xc]
	mov r3, lr, lsr #0x18
	mov r2, lr, lsr #0x8
	mov r12, lr, lsl #0x8
	mov lr, lr, lsl #0x18
	and r3, r3, #0xff
	and r2, r2, #0xff00
	and r12, r12, #0xff0000
	orr r2, r3, r2
	and r3, lr, #0xff000000
	orr r2, r12, r2
	orr r2, r3, r2
	str r2, [r1, #0x4]
	add sp, sp, #0x14
	ldmia sp!, {lr}
	bx lr

	arm_func_start SOC_Read
SOC_Read: ; 0x0209A91C
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	mov r12, #0x0
	str r12, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r3, r12
	bl SOCLi_ReadFrom
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr

	arm_func_start SOC_Connect
SOC_Connect: ; 0x0209A944
	stmdb sp!, {r4,lr}
	ldrh r2, [r1, #0x2]
	ldr lr, [r1, #0x4]
	mov r4, r2, asr #0x8
	mov r1, r2, lsl #0x8
	mov r3, lr, lsr #0x18
	mov r2, lr, lsr #0x8
	mov r12, lr, lsl #0x8
	mov lr, lr, lsl #0x18
	and r4, r4, #0xff
	and r1, r1, #0xff00
	orr r1, r4, r1
	mov r1, r1, lsl #0x10
	and r3, r3, #0xff
	and r2, r2, #0xff00
	and r12, r12, #0xff0000
	orr r2, r3, r2
	and r3, lr, #0xff000000
	orr r2, r12, r2
	mov r1, r1, lsr #0x10
	orr r2, r3, r2
	bl SOCL_Connect
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start SOC_Bind
SOC_Bind: ; 0x0209A9A4
	ldrh r1, [r1, #0x2]
	ldr ip, _0209A9CC ; =SOCL_Bind
	mov r2, r1, asr #0x8
	mov r1, r1, lsl #0x8
	and r2, r2, #0xff
	and r1, r1, #0xff00
	orr r1, r2, r1
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	bx r12
	.balign 4
_0209A9CC: .word SOCL_Bind

	arm_func_start SOC_Socket
SOC_Socket: ; 0x0209A9D0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r1, #0x1
	bne _0209A9F4
	ldr r0, _0209AA08 ; =SOCLSocketParamTCP
	bl SOCL_CreateSocket
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_0209A9F4:
	ldr r0, _0209AA0C ; =SOCLSocketParamUDP
	bl SOCL_CreateSocket
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_0209AA08: .word SOCLSocketParamTCP
_0209AA0C: .word SOCLSocketParamUDP
