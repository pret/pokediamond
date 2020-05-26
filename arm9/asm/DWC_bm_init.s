	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global DWCi_SETTING_NONE
DWCi_SETTING_NONE: ; 0x020FF574
	.byte 0x00, 0x00, 0x00, 0x00

	.text

	arm_func_start initPage
initPage: ; 0x02095FDC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	add r1, r5, r4, lsl #0x8
	mov r0, #0x0
	mov r2, #0x100
	bl MIi_CpuClear16
	add r0, r5, r4, lsl #0x8
	mov r1, #0xff
	strb r1, [r0, #0xe7]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,pc}

	arm_func_start init
init: ; 0x02096010
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x14
	mov r7, r0
	mov r1, r7
	mov r0, #0x0
	mov r2, #0x400
	bl MIi_CpuClear16
	mov r2, #0x0
	mov r1, #0xff
_02096034:
	add r0, r7, r2, lsl #0x8
	add r2, r2, #0x1
	strb r1, [r0, #0xe7]
	cmp r2, #0x3
	blt _02096034
	add r0, sp, #0x0
	bl DWCi_AUTH_GetNewWiFiInfo
	add r0, sp, #0x0
	bl DWCi_BACKUPlConvWifiInfo
	mov r6, r0
	mov r5, #0x0
	mov r4, #0xe
_02096064:
	mov r0, r6
	mov r2, r4
	add r1, r7, #0xf0
	bl MI_CpuCopy8
	add r5, r5, #0x1
	cmp r5, #0x2
	add r7, r7, #0x100
	blt _02096064
	mov r0, #0x0
	add sp, sp, #0x14
	ldmia sp!, {r4-r7,pc}

	arm_func_start checkAp
checkAp:
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	mov r4, r0
	ldrb r0, [r4, #0xe7]
	cmp r0, #0xff
	addeq sp, sp, #0x8
	moveq r0, #0x1
	ldmeqia sp!, {r4,pc}
	cmp r0, #0x2
	addhi sp, sp, #0x8
	movhi r0, #0x0
	ldmhiia sp!, {r4,pc}
	add r0, r4, #0x40
	bl DWC_BACKUPlCheckSsid
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldr r1, _0209618C ; =DWCi_SETTING_NONE
	add r0, r4, #0xc0
	mov r2, #0x4
	bl memcmp
	cmp r0, #0x0
	beq _02096140
	add r0, r4, #0xc4
	bl DWC_BACKUPlCheckAddress
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
	ldrb r0, [r4, #0xd0]
	cmp r0, #0x20
	addhi sp, sp, #0x8
	movhi r0, #0x0
	ldmhiia sp!, {r4,pc}
	add r1, sp, #0x0
	bl DWCi_BACKUPlConvMaskAddr
	add r1, sp, #0x0
	add r0, r4, #0xc0
	bl DWC_BACKUPlCheckIp
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_02096140:
	ldr r1, _0209618C ; =DWCi_SETTING_NONE
	add r0, r4, #0xc8
	mov r2, #0x4
	bl memcmp
	cmp r0, #0x0
	beq _02096180
	add r0, r4, #0xc8
	bl DWC_BACKUPlCheckAddress
	cmp r0, #0x0
	bne _02096180
	add r0, r4, #0xcc
	bl DWC_BACKUPlCheckAddress
	cmp r0, #0x0
	addeq sp, sp, #0x8
	moveq r0, #0x0
	ldmeqia sp!, {r4,pc}
_02096180:
	mov r0, #0x1
	add sp, sp, #0x8
	ldmia sp!, {r4,pc}
	.balign 4
_0209618C: .word DWCi_SETTING_NONE

	arm_func_start DWC_BM_Init
DWC_BM_Init: ; 0x02096190
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x14
	mov r10, r0
	mov r1, #0x0
	mov r2, #0x700
	bl MI_CpuFill8
	mov r0, r10
	bl DWCi_BACKUPlInit
	cmp r0, #0x0
	addeq sp, sp, #0x14
	ldreq r0, _020964B4 ; =0xFFFFD8EF
	ldmeqia sp!, {r4-r11,pc}
	ldr r1, _020964B8 ; =0x0000A001
	add r0, r10, #0x500
	bl MATHi_CRC16InitTableRev
	mov r0, r10
	bl DWCi_BACKUPlRead
	cmp r0, #0x0
	addeq sp, sp, #0x14
	ldreq r0, _020964B4 ; =0xFFFFD8EF
	ldmeqia sp!, {r4-r11,pc}
	add r0, sp, #0x0
	mov r1, #0x0
	mov r2, #0x10
	bl MI_CpuFill8
	mov r8, r10
	mov r7, r10
	mov r9, #0x0
	add r11, sp, #0x0
	add r6, r10, #0x500
	mov r4, #0x1
	mov r5, #0xfe
_02096210:
	mov r0, r6
	mov r1, r8
	mov r2, r5
	bl MATH_CalcCRC16
	add r1, r10, r9, lsl #0x8
	ldrh r1, [r1, #0xfe]
	cmp r0, r1
	bne _02096240
	mov r0, r7
	bl checkAp
	cmp r0, #0x0
	strne r4, [r11, r9, lsl #0x2]
_02096240:
	add r9, r9, #0x1
	cmp r9, #0x3
	add r8, r8, #0x100
	add r7, r7, #0x100
	blt _02096210
	add r0, r10, #0x500
	add r1, r10, #0x300
	mov r2, #0xfe
	bl MATH_CalcCRC16
	add r1, r10, #0x300
	ldrh r1, [r1, #0xfe]
	cmp r0, r1
	moveq r0, #0x1
	ldr r1, [sp, #0x0]
	streq r0, [sp, #0xc]
	cmp r1, #0x0
	beq _020962BC
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020962BC
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _020962BC
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	beq _020962BC
	add r0, r10, #0xf0
	bl DWCi_BACKUPlSetWiFi
	add sp, sp, #0x14
	mov r0, #0x0
	ldmia sp!, {r4-r11,pc}
_020962BC:
	cmp r1, #0x0
	bne _0209630C
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _0209630C
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bne _0209630C
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	bne _0209630C
	mov r0, r10
	bl init
	mov r0, r10
	bl DWCi_BACKUPlWriteAll
	cmp r0, #0x0
	movne r0, #0x0
	add sp, sp, #0x14
	ldreq r0, _020964BC ; =0xFFFFD8F0
	ldmia sp!, {r4-r11,pc}
_0209630C:
	cmp r1, #0x0
	beq _02096320
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _0209635C
_02096320:
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	beq _02096338
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	bne _0209635C
_02096338:
	mov r0, r10
	bl init
	mov r0, r10
	bl DWCi_BACKUPlWriteAll
	cmp r0, #0x0
	movne r0, #0x0
	add sp, sp, #0x14
	ldreq r0, _020964BC ; =0xFFFFD8F0
	ldmia sp!, {r4-r11,pc}
_0209635C:
	cmp r1, #0x0
	bne _02096394
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _02096394
	mov r0, r10
	bl init
	mov r0, r10
	bl DWCi_BACKUPlWriteAll
	cmp r0, #0x0
	ldrne r0, _020964C0 ; =0xFFFFD8ED
	add sp, sp, #0x14
	ldreq r0, _020964BC ; =0xFFFFD8F0
	ldmia sp!, {r4-r11,pc}
_02096394:
	cmp r1, #0x0
	bne _020963C4
	mov r0, r10
	mov r1, #0x0
	bl initPage
	add r0, r10, #0x1f0
	add r1, r10, #0xf0
	mov r2, #0xe
	bl MI_CpuCopy8
	ldrb r0, [r10, #0x1ef]
	strb r0, [r10, #0xef]
	b _020963F4
_020963C4:
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	bne _020963F4
	mov r0, r10
	mov r1, #0x1
	bl initPage
	add r0, r10, #0xf0
	add r1, r10, #0x1f0
	mov r2, #0xe
	bl MI_CpuCopy8
	ldrb r0, [r10, #0xef]
	strb r0, [r10, #0x1ef]
_020963F4:
	add r0, r10, #0xf0
	bl DWCi_BACKUPlSetWiFi
	ldr r0, [sp, #0x8]
	cmp r0, #0x0
	bne _02096414
	mov r0, r10
	mov r1, #0x2
	bl initPage
_02096414:
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	bne _02096430
	add r1, r10, #0x300
	mov r0, #0x0
	mov r2, #0x100
	bl MIi_CpuClear16
_02096430:
	mov r4, #0x0
	mov r1, r4
	add r0, sp, #0x0
	add r5, r10, #0xef
	mov r6, #0x1
_02096444:
	ldr r2, [r0, r1, lsl #0x2]
	cmp r2, #0x0
	bne _0209647C
	ldrb r2, [r10, #0xef]
	mov r7, r6, lsl r1
	ands r2, r2, r7
	beq _0209647C
	ldrb r3, [r5, #0x0]
	mvn r2, r7
	mov r4, r6
	and r2, r3, r2
	strb r2, [r5, #0x0]
	ldrb r2, [r10, #0xef]
	strb r2, [r10, #0x1ef]
_0209647C:
	add r1, r1, #0x1
	cmp r1, #0x3
	blt _02096444
	mov r0, r10
	bl DWCi_BACKUPlWriteAll
	cmp r0, #0x0
	addeq sp, sp, #0x14
	ldreq r0, _020964BC ; =0xFFFFD8F0
	ldmeqia sp!, {r4-r11,pc}
	cmp r4, #0x0
	ldrne r0, _020964C4 ; =0xFFFFD8EE
	moveq r0, #0x0
	add sp, sp, #0x14
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020964B4: .word 0xFFFFD8EF
_020964B8: .word 0x0000A001
_020964BC: .word 0xFFFFD8F0
_020964C0: .word 0xFFFFD8ED
_020964C4: .word 0xFFFFD8EE
