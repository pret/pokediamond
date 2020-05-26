	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global nv_result
nv_result: ; 0x021C8C78
	.space 0x4

	.global nv_cb_occurred
nv_cb_occurred: ; 0x021C8C7C
	.space 0x4

	.global Address
Address: ; 0x021C8C80
	.space 0x4

	.global Wifi
Wifi: ; 0x021C8C84
	.space 0x1c

	.global Work
Work: ; 0x021C8CA0
	.space 0x20

	.text

	arm_func_start DWCi_BACKUPlGetWifi
DWCi_BACKUPlGetWifi: ; 0x02095324
	ldr r0, _0209532C ; =Wifi
	bx lr
	.balign 4
_0209532C: .word Wifi

	arm_func_start DWCi_BACKUPlConvWifiInfo
DWCi_BACKUPlConvWifiInfo: ; 0x02095330
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r4, r0
	ldr r3, [r4, #0x8]
	ldr r2, [r4, #0xc]
	ldr r1, _020953E4 ; =Wifi
	str r2, [sp, #0x4]
	str r3, [sp, #0x0]
	mov r2, #0x5
	bl MI_CpuCopy8
	ldr r1, [sp, #0x0]
	ldr r2, [r4, #0x4]
	ldr r0, [sp, #0x4]
	mov r2, r2, lsr #0x8
	mov r12, r1, lsr #0x5
	mov r3, r0, lsr #0x5
	orr r12, r12, r0, lsl #0x1b
	and lr, r2, #0x7
	and r0, r1, #0x1f
	orr lr, lr, r0, lsl #0x3
	ldr r2, _020953E4 ; =Wifi
	ldr r1, _020953E8 ; =Wifi + 0x6
	strb lr, [r2, #0x5]
	add r0, sp, #0x0
	str r12, [sp, #0x0]
	str r3, [sp, #0x4]
	mov r2, #0x4
	bl MI_CpuCopy8
	ldrh r0, [r4, #0x10]
	ldr r1, [sp, #0x4]
	ldr r3, _020953E4 ; =Wifi
	and r1, r1, #0x3f
	and r0, r0, #0x3
	orr r0, r1, r0, lsl #0x6
	strb r0, [r3, #0xa]
	ldrh r2, [r4, #0x10]
	add r0, r4, #0x12
	ldr r1, _020953EC ; =Wifi + 0xc
	mov r4, r2, asr #0x2
	mov r2, #0x2
	strb r4, [r3, #0xb]
	bl MI_CpuCopy8
	ldr r0, _020953E4 ; =Wifi
	add sp, sp, #0x8
	ldmia sp!, {r4,pc}
	.balign 4
_020953E4: .word Wifi
_020953E8: .word Wifi + 0x6
_020953EC: .word Wifi + 0xc

	arm_func_start Callback_NVRAM
Callback_NVRAM: ; 0x020953F0
	ldr r3, _02095420 ; =nv_result
	and r12, r1, #0xff
	ldr r0, _02095424 ; =nv_cb_occurred
	mov r1, #0x1
	strh r12, [r3, #0x0]
	str r1, [r0, #0x0]
	cmp r2, #0x0
	movne r0, #0xff
	strneh r0, [r3, #0x0]
	ldr r0, _02095420 ; =nv_result
	ldrh r0, [r0, #0x0]
	bx lr
	.balign 4
_02095420: .word nv_result
_02095424: .word nv_cb_occurred

	arm_func_start writeDisable
writeDisable:
	stmdb sp!, {r4-r6,lr}
	mov r5, #0x4
	mov r4, #0x1
_02095434:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
	cmp r0, #0x0
	beq _02095434
	ldr r1, _02095490 ; =Callback_NVRAM
	mov r0, #0x4
	bl PXI_SetFifoRecvCallback
	mov r4, #0x40000
	mov r6, #0x7
	mov r5, #0x0
_02095460:
	mov r0, r6
	mov r1, r5
	mov r2, r5
	mov r3, r5
	bl NVRAMm_ExecuteCommand
	cmp r0, #0x1
	beq _02095488
	mov r0, r4
	bl SVC_WaitByLoop
	b _02095460
_02095488:
	mov r0, #0x1
	ldmia sp!, {r4-r6,pc}
	.balign 4
_02095490: .word Callback_NVRAM

	arm_func_start verify
verify:
	stmdb sp!, {r4-r6,lr}
	mov r5, r2
	mov r4, r3
	mov r6, r0
	mov r0, r1
	mov r1, r5
	mov r2, r4
	bl readNvram
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4-r6,pc}
	mov r0, r6
	mov r1, r4
	mov r2, r5
	bl memcmp
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	ldmia sp!, {r4-r6,pc}

	arm_func_start writeNvram
writeNvram: ; 0x020954E0
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	mov r6, r2
	mov r5, #0x4
	mov r4, #0x1
_020954F8:
	mov r0, r5
	mov r1, r4
	bl PXI_IsCallbackReady
	cmp r0, #0x0
	beq _020954F8
	ldr r1, _02095558 ; =Callback_NVRAM
	mov r0, #0x4
	bl PXI_SetFifoRecvCallback
	mov r0, r6
	mov r1, r7
	bl DC_StoreRange
	mov r4, #0x40000
	mov r5, #0x2
_0209552C:
	mov r0, r5
	mov r1, r8
	mov r2, r7
	mov r3, r6
	bl NVRAMm_ExecuteCommand
	cmp r0, #0x1
	ldmeqia sp!, {r4-r8,pc}
	mov r0, r4
	bl SVC_WaitByLoop
	b _0209552C
	ldmia sp!, {r4-r8,pc}
	.balign 4
_02095558: .word Callback_NVRAM

	arm_func_start readNvram
readNvram:
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	mov r4, r2
	mov r6, r0
	mov r0, r4
	mov r5, r1
	bl DC_InvalidateRange
	mov r8, #0x4
	mov r7, #0x1
_02095580:
	mov r0, r8
	mov r1, r7
	bl PXI_IsCallbackReady
	cmp r0, #0x0
	beq _02095580
	ldr r1, _020955F0 ; =Callback_NVRAM
	mov r0, #0x4
	bl PXI_SetFifoRecvCallback
	mov r0, r5, lsl #0x10
	mov r8, r0, lsr #0x10
	mov r7, #0x40000
	mov r9, #0x1
_020955B0:
	mov r0, r9
	mov r1, r6
	mov r2, r8
	mov r3, r4
	bl NVRAMm_ExecuteCommand
	cmp r0, #0x1
	beq _020955D8
	mov r0, r7
	bl SVC_WaitByLoop
	b _020955B0
_020955D8:
	mov r0, r4
	mov r1, r5
	bl DC_InvalidateRange
	mov r0, #0x1
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_020955F0: .word Callback_NVRAM

	arm_func_start NVRAMm_ExecuteCommand
NVRAMm_ExecuteCommand: ; 0x020955F4
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xc4
	ldr ip, _02095AAC ; =0x0000FFFF
	ldr sl, _02095AB0 ; =Work
	and r8, r2, r12
	and r7, r1, r12
	mov r5, r1, lsr #0x10
	mov r4, r3, lsr #0x10
	and r1, r3, r12
	orr r3, r8, #0x30000
	str r3, [sp, #0xc]
	ldr r3, _02095AB4 ; =0x01050000
	orr r2, r2, #0x20000
	orr r3, r1, r3
	str r3, [sp, #0x14]
	orr r1, r1, #0x1040000
	mov r9, r0
	and r0, r5, #0xff
	str r2, [sp, #0x1c]
	str r1, [sp, #0x24]
	ldr r1, _02095AB8 ; =0x02002200
	mov r8, #0x0
	orr r2, r4, #0x40000
	orr r1, r1, r10, lsr #0x18
	str r1, [sp, #0x28]
	and r1, r12, r10, lsr #0x8
	orr r1, r1, #0x10000
	ldr r3, _02095ABC ; =0x02002300
	str r2, [sp, #0x10]
	orr r2, r0, r3
	str r2, [sp, #0x8]
	orr r2, r4, #0x30000
	str r2, [sp, #0x20]
	ldr r2, _02095AC0 ; =0x02002500
	mov r6, r10, lsl #0x8
	str r1, [sp, #0x2c]
	and r1, r6, #0xff00
	orr r0, r0, r2
	ldr r3, _02095AC4 ; =0x01020000
	str r0, [sp, #0x18]
	orr r0, r1, r3
	str r0, [sp, #0x30]
	mov r0, #0x20000
	str r0, [sp, #0x40]
	mov r0, #0x5
	str r0, [sp, #0xac]
	mov r0, #0x3
	str r0, [sp, #0xb0]
	mov r0, #0x6
	str r0, [sp, #0xb8]
	mov r0, #0x4000
	orr r7, r7, #0x10000
	str r8, [sp, #0xb4]
	mov r4, #0x1
	str r8, [sp, #0xa8]
	mov r5, #0x4
	str r8, [sp, #0xa4]
	str r8, [sp, #0xa0]
	str r8, [sp, #0x90]
	str r8, [sp, #0x98]
	str r8, [sp, #0x9c]
	str r8, [sp, #0x94]
	str r8, [sp, #0x8c]
	str r8, [sp, #0x6c]
	str r8, [sp, #0x74]
	str r8, [sp, #0x7c]
	str r8, [sp, #0x84]
	str r8, [sp, #0x88]
	str r8, [sp, #0x80]
	str r8, [sp, #0x78]
	str r8, [sp, #0x70]
	str r8, [sp, #0x68]
	str r8, [sp, #0x64]
	str r8, [sp, #0x38]
	str r8, [sp, #0x44]
	str r8, [sp, #0x4c]
	str r8, [sp, #0x54]
	str r8, [sp, #0x5c]
	str r8, [sp, #0x60]
	str r8, [sp, #0x58]
	str r8, [sp, #0x50]
	str r8, [sp, #0x48]
	str r8, [sp, #0x3c]
	str r8, [sp, #0x34]
	mov r6, r8
	str r0, [sp, #0xbc]
_0209574C:
	cmp r8, #0x0
	bne _02095988
	ldr r0, _02095AC8 ; =nv_cb_occurred
	cmp r9, #0x7
	str r6, [r0, #0x0]
	addls pc, pc, r9, lsl #0x2
	b _0209574C
_02095768: ; jump table
	b _0209574C ; case 0
	b _02095788 ; case 1
	b _02095834 ; case 2
	b _02095854 ; case 3
	b _020958F0 ; case 4
	b _020958F0 ; case 5
	b _02095948 ; case 6
	b _02095968 ; case 7
_02095788:
	ldr r1, [sp, #0x8]
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x34]
	blt _0209574C
	ldr r2, [sp, #0x38]
	mov r0, r5
	mov r1, r7
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x3c]
	blt _0209574C
	ldr r1, [sp, #0x40]
	ldr r2, [sp, #0x44]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x48]
	blt _0209574C
	ldr r1, [sp, #0xc]
	ldr r2, [sp, #0x4c]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x50]
	blt _0209574C
	ldr r1, [sp, #0x10]
	ldr r2, [sp, #0x54]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x58]
	blt _0209574C
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x5c]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x60]
	movge r8, r4
	b _0209574C
_02095834:
	ldr r1, _02095ACC ; =0x03002000
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movge r8, r4
	ldrlt r8, [sp, #0x64]
	b _0209574C
_02095854:
	ldr r1, [sp, #0x18]
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x68]
	blt _020958E0
	ldr r2, [sp, #0x6c]
	mov r0, r5
	mov r1, r7
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x70]
	blt _020958E0
	ldr r1, [sp, #0x1c]
	ldr r2, [sp, #0x74]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x78]
	blt _020958E0
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x7c]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x80]
	blt _020958E0
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x84]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x88]
	movge r8, r4
_020958E0:
	bl OS_GetTick
	str r0, [sp, #0x0]
	mov r11, r1
	b _0209574C
_020958F0:
	ldr r1, [sp, #0x28]
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x8c]
	blt _0209574C
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x90]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x94]
	blt _0209574C
	ldr r1, [sp, #0x30]
	ldr r2, [sp, #0x98]
	mov r0, r5
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	ldrlt r8, [sp, #0x9c]
	movge r8, r4
	b _0209574C
_02095948:
	ldr r1, _02095AD0 ; =0x03002D00
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movge r8, r4
	ldrlt r8, [sp, #0xa0]
	b _0209574C
_02095968:
	ldr r1, _02095AD4 ; =0x03002100
	mov r0, r5
	mov r2, r6
	bl PXI_SendWordByFifo
	cmp r0, #0x0
	movge r8, r4
	ldrlt r8, [sp, #0xa4]
	b _0209574C
_02095988:
	ldr r0, _02095AC8 ; =nv_cb_occurred
	ldr r0, [r0, #0x0]
	cmp r0, #0x1
	bne _0209574C
	ldr r0, _02095AD8 ; =nv_result
	ldr r8, [sp, #0xa8]
	ldrh r0, [r0, #0x0]
	cmp r0, #0x0
	bne _02095AA0
	cmp r9, #0x7
	addls pc, pc, r9, lsl #0x2
	b _0209574C
_020959B8: ; jump table
	b _0209574C ; case 0
	b _020959D8 ; case 1
	b _020959E4 ; case 2
	b _020959EC ; case 3
	b _020959F4 ; case 4
	b _020959F4 ; case 5
	b _02095A88 ; case 6
	b _02095A94 ; case 7
_020959D8:
	add sp, sp, #0xc4
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_020959E4:
	mov r9, r5
	b _0209574C
_020959EC:
	ldr r9, [sp, #0xac]
	b _0209574C
_020959F4:
	mov r0, r10
	mov r1, r4
	bl DC_InvalidateRange
	cmp r9, #0x4
	bne _02095A24
	ldrb r0, [r10, #0x0]
	ands r0, r0, #0x2
	ldrne r9, [sp, #0xb0]
	bne _0209574C
	add sp, sp, #0xc4
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_02095A24:
	ldrb r1, [r10, #0x0]
	ands r0, r1, #0x1
	addeq sp, sp, #0xc4
	moveq r0, #0x1
	ldmeqia sp!, {r4-r11,pc}
	ands r0, r1, #0x20
	bne _02095A74
	bl OS_GetTick
	ldr r2, [sp, #0x0]
	ldr r3, [sp, #0xb4]
	subs r2, r0, r2
	sbc r0, r1, r11
	mov r1, r0, lsl #0x6
	orr r1, r1, r2, lsr #0x1a
	mov r0, r2, lsl #0x6
	ldr r2, _02095ADC ; =0x000082EA
	bl _ll_udiv
	cmp r1, #0x0
	cmpeq r0, #0xfa0
	bls _02095A7C
_02095A74:
	ldr r9, [sp, #0xb8]
	b _0209574C
_02095A7C:
	ldr r0, [sp, #0xbc]
	bl SVC_WaitByLoop
	b _0209574C
_02095A88:
	add sp, sp, #0xc4
	mov r0, r8
	ldmia sp!, {r4-r11,pc}
_02095A94:
	add sp, sp, #0xc4
	mov r0, #0x1
	ldmia sp!, {r4-r11,pc}
_02095AA0:
	mov r0, r8
	add sp, sp, #0xc4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_02095AAC: .word 0x0000FFFF
_02095AB0: .word Work
_02095AB4: .word 0x01050000
_02095AB8: .word 0x02002200
_02095ABC: .word 0x02002300
_02095AC0: .word 0x02002500
_02095AC4: .word 0x01020000
_02095AC8: .word nv_cb_occurred
_02095ACC: .word 0x03002000
_02095AD0: .word 0x03002D00
_02095AD4: .word 0x03002100
_02095AD8: .word nv_result
_02095ADC: .word 0x000082EA

	arm_func_start DWC_BACKUPlCheckAddress
DWC_BACKUPlCheckAddress:
	ldrb r0, [r0, #0x0]
	cmp r0, #0x7f
	moveq r0, #0x0
	bxeq lr
	cmp r0, #0x1
	movcc r0, #0x0
	bxcc lr
	cmp r0, #0xdf
	movls r0, #0x1
	movhi r0, #0x0
	bx lr

	arm_func_start DWC_BACKUPlCheckIp
DWC_BACKUPlCheckIp:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r5, r0
	mov r4, r1
	bl DWC_BACKUPlCheckAddress
	cmp r0, #0x0
	addeq sp, sp, #0xc
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	add r1, sp, #0x0
	mov r0, r5
	mov r2, #0x4
	bl MI_CpuCopy8
	add r1, sp, #0x4
	mov r0, r4
	mov r2, #0x4
	bl MI_CpuCopy8
	ldr r3, [sp, #0x4]
	ldr r2, [sp, #0x0]
	mvn r0, #0x1
	orr r1, r2, r3
	cmp r1, r0
	addeq sp, sp, #0xc
	moveq r0, #0x0
	ldmeqia sp!, {r4-r5,pc}
	mvn r0, r3
	ands r0, r2, r0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}

	arm_func_start DWC_BACKUPlCheckSsid
DWC_BACKUPlCheckSsid:
	mov r2, #0x0
_02095B8C:
	ldrb r1, [r0, r2]
	cmp r1, #0x0
	movne r0, #0x1
	bxne lr
	add r2, r2, #0x1
	cmp r2, #0x20
	blt _02095B8C
	mov r0, #0x0
	bx lr

	arm_func_start DWCi_BACKUPlConvMaskAddr
DWCi_BACKUPlConvMaskAddr: ; 0x02095BB0
	mvn r2, #0x0
	mov r12, #0x0
	eor r3, r2, r2, lsr r0
	mov r2, r12
_02095BC0:
	rsb r0, r2, #0x18
	mov r0, r3, lsr r0
	strb r0, [r1, r12]
	add r12, r12, #0x1
	cmp r12, #0x4
	add r2, r2, #0x8
	blt _02095BC0
	bx lr

	arm_func_start DWCi_BACKUPlConvMaskCidr
DWCi_BACKUPlConvMaskCidr: ; 0x02095BE0
	stmdb sp!, {r4,lr}
	mov lr, #0x0
	mov r4, lr
	mov r2, lr
_02095BF0:
	ldrb r3, [r0, lr]
	mov r12, r2
_02095BF8:
	mov r1, r3, asr r12
	ands r1, r1, #0x1
	add r12, r12, #0x1
	addne r4, r4, #0x1
	cmp r12, #0x8
	blt _02095BF8
	add lr, lr, #0x1
	cmp lr, #0x4
	blt _02095BF0
	and r0, r4, #0xff
	ldmia sp!, {r4,pc}

	arm_func_start DWCi_BACKUPlSetWiFi
DWCi_BACKUPlSetWiFi: ; 0x02095C24
	ldr ip, _02095C34 ; =MI_CpuCopy8
	ldr r1, _02095C38 ; =Wifi
	mov r2, #0xe
	bx r12
	.balign 4
_02095C34: .word MI_CpuCopy8
_02095C38: .word Wifi

	arm_func_start DWCi_BACKUPlWriteAll
DWCi_BACKUPlWriteAll:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r1, _02095CD8 ; =Address
	mov r10, r0
	ldr r8, [r1, #0x0]
	mov r7, r10
	mov r9, #0x0
	add r4, r10, #0x400
	add r6, r10, #0x500
	mov r5, #0x100
	mov r11, #0xfe
_02095C68:
	mov r0, r6
	mov r1, r7
	mov r2, r11
	bl MATH_CalcCRC16
	add r1, r10, r9, lsl #0x8
	strh r0, [r1, #0xfe]
_02095C80:
	mov r0, r8
	mov r1, r5
	mov r2, r7
	bl writeNvram
	mov r0, r7
	mov r1, r8
	mov r2, r5
	mov r3, r4
	bl verify
	cmp r0, #0x0
	beq _02095C80
	add r9, r9, #0x1
	cmp r9, #0x4
	add r7, r7, #0x100
	add r8, r8, #0x100
	blt _02095C68
	bl writeDisable
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_02095CD8: .word Address

	arm_func_start DWCi_BACKUPlWritePage
DWCi_BACKUPlWritePage: ; 0x02095CDC
	stmdb sp!, {r4-r9,lr}
	sub sp, sp, #0x4
	ldr r3, _02095D64 ; =Address
	mov r4, r0
	ldr r6, [r3, #0x0]
	mov r9, r1
	mov r8, r2
	mov r7, #0x0
	mov r5, #0x100
_02095D00:
	ldr r0, [r9, r7, lsl #0x2]
	cmp r0, #0x0
	beq _02095D38
_02095D0C:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl writeNvram
	mov r0, r4
	mov r1, r6
	mov r2, r5
	mov r3, r8
	bl verify
	cmp r0, #0x0
	beq _02095D0C
_02095D38:
	add r7, r7, #0x1
	cmp r7, #0x4
	add r4, r4, #0x100
	add r6, r6, #0x100
	blt _02095D00
	bl writeDisable
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r9,pc}
	.balign 4
_02095D64: .word Address

	arm_func_start DWCi_BACKUPlRead
DWCi_BACKUPlRead:
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _02095D98 ; =Address
	mov r2, r0
	ldr r0, [r1, #0x0]
	mov r1, #0x400
	bl readNvram
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_02095D98: .word Address

	arm_func_start DWCi_BACKUPlInit
DWCi_BACKUPlInit:
	stmdb sp!, {r4,lr}
	mov r4, r0
	mov r0, #0x20
	mov r1, r0
	mov r2, r4
	bl readNvram
	cmp r0, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldrh r2, [r4, #0x0]
	ldr r1, _02095DDC ; =Address
	mov r0, #0x1
	mov r2, r2, lsl #0x3
	sub r2, r2, #0x400
	str r2, [r1, #0x0]
	ldmia sp!, {r4,pc}
	.balign 4
_02095DDC: .word Address

	arm_func_start DWCi_BM_SetWiFiInfo
DWCi_BM_SetWiFiInfo:
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x4
	ldr r2, _02095EBC ; =Address
	mov r10, r1
	ldr r8, [r2, #0x0]
	bl DWCi_BACKUPlConvWifiInfo
	ldr r1, _02095EC0 ; =0x0000A001
	add r0, r10, #0x200
	bl MATHi_CRC16InitTableRev
	mov r9, #0x0
	add r4, r10, #0x100
	add r6, r10, #0xf0
	mov r7, #0x100
	mov r5, #0xe
	mov r11, #0xfe
_02095E1C:
	mov r0, r8
	mov r1, r7
	mov r2, r10
	bl readNvram
	cmp r0, #0x0
	bne _02095E44
	bl OS_Terminate
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_02095E44:
	ldr r0, _02095EC4 ; =Wifi
	mov r1, r6
	mov r2, r5
	bl MI_CpuCopy8
	mov r1, r10
	mov r2, r11
	add r0, r10, #0x200
	bl MATH_CalcCRC16
	strh r0, [r10, #0xfe]
_02095E68:
	mov r0, r8
	mov r1, r7
	mov r2, r10
	bl writeNvram
	mov r0, r10
	mov r1, r8
	mov r2, r7
	mov r3, r4
	bl verify
	cmp r0, #0x0
	beq _02095E68
	add r9, r9, #0x1
	cmp r9, #0x2
	add r8, r8, #0x100
	blt _02095E1C
	bl writeDisable
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {r4-r11,pc}
	.balign 4
_02095EBC: .word Address
_02095EC0: .word 0x0000A001
_02095EC4: .word Wifi

	arm_func_start DWCi_BM_GetWiFiInfo
DWCi_BM_GetWiFiInfo:
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldr r0, _02095F90 ; =Wifi
	mov r1, r4
	mov r2, #0x6
	bl MI_CpuCopy8
	ldr r3, [r4, #0x0]
	mvn r0, #0x0
	ldr r2, [r4, #0x4]
	ldr r1, _02095F94 ; =0x000007FF
	and r0, r3, r0
	str r0, [r4, #0x0]
	and r1, r2, r1
	ldr r0, _02095F98 ; =Wifi + 0x5
	str r1, [r4, #0x4]
	add r1, r4, #0x8
	mov r2, #0x6
	bl MI_CpuCopy8
	add r12, r4, #0x8
	ldr r1, [r4, #0x8]
	ldr r0, [r12, #0x4]
	mov r1, r1, lsr #0x3
	orr r1, r1, r0, lsl #0x1d
	str r1, [r4, #0x8]
	mov r0, r0, lsr #0x3
	str r0, [r12, #0x4]
	ldr r3, [r4, #0x8]
	mvn r0, #0x0
	ldr r2, [r12, #0x4]
	ldr r1, _02095F94 ; =0x000007FF
	and r0, r3, r0
	str r0, [r4, #0x8]
	and r1, r2, r1
	ldr r0, _02095F9C ; =Wifi + 0xa
	str r1, [r12, #0x4]
	add r1, r4, #0x10
	mov r2, #0x2
	bl MI_CpuCopy8
	ldrh r1, [r4, #0x10]
	ldr r3, _02095FA0 ; =0x000003FF
	ldr r0, _02095FA4 ; =Wifi + 0xc
	mov r1, r1, asr #0x6
	strh r1, [r4, #0x10]
	ldrh r12, [r4, #0x10]
	add r1, r4, #0x12
	mov r2, #0x2
	and r3, r12, r3
	strh r3, [r4, #0x10]
	bl MI_CpuCopy8
	ldmia sp!, {r4,pc}
	.balign 4
_02095F90: .word Wifi
_02095F94: .word 0x000007FF
_02095F98: .word Wifi + 0x5
_02095F9C: .word Wifi + 0xa
_02095FA0: .word 0x000003FF
_02095FA4: .word Wifi + 0xc

	arm_func_start DWCi_BM_GetApInfo
DWCi_BM_GetApInfo: ; 0x02095FA8
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _02095FD8 ; =Address
	mov r2, r0
	ldr r0, [r1, #0x0]
	mov r1, #0x300
	bl readNvram
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {pc}
	.balign 4
_02095FD8: .word Address
