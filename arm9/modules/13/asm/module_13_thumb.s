	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD13_022172DC
MOD13_022172DC: ; 0x022172DC
	str r0, [r1]
	mov r0, #1
	strh r0, [r1, #4]
	bx lr

	thumb_func_start MOD13_022172E4
MOD13_022172E4: ; 0x022172E4
	mov r1, #0
	str r1, [r0]
	strh r1, [r0, #4]
	strh r1, [r0, #6]
	bx lr
	.align 2, 0

	thumb_func_start MOD13_022172F0
MOD13_022172F0: ; 0x022172F0
	push {r4, lr}
	sub sp, #0x10
	ldr r0, _02217358 ; =0x02240B3C
	ldr r0, [r0]
	cmp r0, #0
	bne _02217334
	mov r4, #0
	add r0, sp, #0
	add r1, r4, #0
	mov r2, #0xc
	bl MOD13_022174C0
	add r0, sp, #0
	bl RTC_GetTime
	cmp r0, #0
	bne _02217322
	ldr r0, [sp]
	lsl r0, r0, #0xa
	add r1, r4, r0
	ldr r0, [sp, #4]
	lsl r0, r0, #3
	add r1, r1, r0
	ldr r0, [sp, #8]
	add r4, r1, r0
_02217322:
	ldr r0, _0221735C ; =0x02240B54
	str r4, [r0]
	ldr r1, _02217360 ; =0x5D588B65
	str r1, [r0, #4]
	ldr r1, _02217364 ; =0x00269EC3
	str r1, [r0, #8]
	mov r1, #1
	ldr r0, _02217358 ; =0x02240B3C
	str r1, [r0]
_02217334:
	ldr r0, _0221735C ; =0x02240B54
	ldr r3, [r0, #8]
	ldr r2, [r0, #4]
	ldr r1, [r0]
	mul r2, r1
	add r1, r3, r2
	str r1, [r0]
	lsr r1, r1, #0x10
	ldr r0, _02217368 ; =0x00007FFF
	mul r1, r0
	lsr r0, r1, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	add sp, #0x10
	pop {r4}
	pop {r3}
	bx r3
	nop
_02217358: .word MOD13_02240B3C
_0221735C: .word MOD13_02240B54
_02217360: .word 0x5D588B65
_02217364: .word 0x00269EC3
_02217368: .word 0x00007FFF

	thumb_func_start MOD13_0221736C
MOD13_0221736C: ; 0x0221736C
	mov r2, #0
	ldrsb r1, [r0, r2]
	cmp r1, #0
	beq _0221737C
_02217374:
	add r2, r2, #1
	ldrsb r1, [r0, r2]
	cmp r1, #0
	bne _02217374
_0221737C:
	add r0, r2, #0
	bx lr

	thumb_func_start MOD13_02217380
MOD13_02217380: ; 0x02217380
	asr r2, r0, #8
	mov r1, #0xff
	and r2, r1
	lsl r1, r0, #8
	ldr r0, _02217394 ; =0x0000FF00
	and r1, r0
	orr r2, r1
	lsl r0, r2, #0x10
	lsr r0, r0, #0x10
	bx lr
	.align 2, 0
_02217394: .word 0x0000FF00

	thumb_func_start MOD13_02217398
MOD13_02217398: ; 0x02217398
	push {r4}
	sub sp, #4
	lsl r1, r0, #0x18
	ldr r2, _022173C4 ; =0xFF000000
	and r1, r2
	lsl r4, r0, #8
	ldr r2, _022173C8 ; =0x00FF0000
	and r4, r2
	lsr r3, r0, #0x18
	mov r2, #0xff
	and r3, r2
	lsr r2, r0, #8
	ldr r0, _022173CC ; =0x0000FF00
	and r2, r0
	orr r3, r2
	orr r4, r3
	orr r1, r4
	add r0, r1, #0
	add sp, #4
	pop {r4}
	bx lr
	nop
_022173C4: .word 0xFF000000
_022173C8: .word 0x00FF0000
_022173CC: .word 0x0000FF00

	thumb_func_start MOD13_022173D0
MOD13_022173D0: ; 0x022173D0
	asr r2, r0, #8
	mov r1, #0xff
	and r2, r1
	lsl r1, r0, #8
	ldr r0, _022173E4 ; =0x0000FF00
	and r1, r0
	orr r2, r1
	lsl r0, r2, #0x10
	lsr r0, r0, #0x10
	bx lr
	.align 2, 0
_022173E4: .word 0x0000FF00

	thumb_func_start MOD13_022173E8
MOD13_022173E8: ; 0x022173E8
	push {r4}
	sub sp, #4
	lsl r1, r0, #0x18
	ldr r2, _02217414 ; =0xFF000000
	and r1, r2
	lsl r4, r0, #8
	ldr r2, _02217418 ; =0x00FF0000
	and r4, r2
	lsr r3, r0, #0x18
	mov r2, #0xff
	and r3, r2
	lsr r2, r0, #8
	ldr r0, _0221741C ; =0x0000FF00
	and r2, r0
	orr r3, r2
	orr r4, r3
	orr r1, r4
	add r0, r1, #0
	add sp, #4
	pop {r4}
	bx lr
	nop
_02217414: .word 0xFF000000
_02217418: .word 0x00FF0000
_0221741C: .word 0x0000FF00

	thumb_func_start MOD13_02217420
MOD13_02217420: ; 0x02217420
	ldr r3, _02217424 ; =0x0209A7B8
	bx r3
	.align 2, 0
_02217424: .word 0x0209A7B8

	thumb_func_start MOD13_02217428
MOD13_02217428: ; 0x02217428
	strb r2, [r1]
	ldr r3, _02217430 ; =0x0209A9A4
	bx r3
	nop
_02217430: .word 0x0209A9A4

	thumb_func_start MOD13_02217434
MOD13_02217434: ; 0x02217434
	ldr r3, _02217438 ; =0x0209A9D0
	bx r3
	.align 2, 0
_02217438: .word 0x0209A9D0

	thumb_func_start MOD13_0221743C
MOD13_0221743C: ; 0x0221743C
	bx lr
	.align 2, 0

	thumb_func_start MOD13_02217440
MOD13_02217440: ; 0x02217440
	push {r4, r5, lr}
	sub sp, #4
	ldr r5, [sp, #0x14]
	ldr r4, [sp, #0x10]
	strb r5, [r4]
	str r4, [sp]
	bl SOC_SendTo
	add sp, #4
	pop {r4, r5}
	pop {r3}
	bx r3

	thumb_func_start MOD13_02217458
MOD13_02217458: ; 0x02217458
	push {r4, r5, r6, lr}
	sub sp, #8
	ldr r5, [sp, #0x18]
	mov r4, #0
	ldr r2, [r1]
	ldr r0, [r1, #4]
	str r2, [sp]
	str r0, [sp, #4]
	ldr r0, [r5]
	ldr r1, _022174A0 ; =0x01FF6210
	mul r0, r1
	mov r1, #0x40
	bl _s32_div_f
	asr r1, r0, #0x1f
	add r6, r4, r0
	adc r4, r1
	ldr r0, [r5, #4]
	ldr r1, _022174A0 ; =0x01FF6210
	mul r0, r1
	mov r1, #0x40
	bl _s32_div_f
	asr r1, r0, #0x1f
	add r2, r6, r0
	adc r4, r1
	add r0, sp, #0
	mov r1, #1
	add r3, r4, #0
	bl SOC_Poll
	add sp, #8
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	nop
_022174A0: .word 0x01FF6210

	thumb_func_start MOD13_022174A4
MOD13_022174A4: ; 0x022174A4
	push {r4, r5, lr}
	sub sp, #4
	ldr r4, [sp, #0x14]
	ldr r5, [r4]
	ldr r4, [sp, #0x10]
	strb r5, [r4]
	str r4, [sp]
	bl SOC_RecvFrom
	add sp, #4
	pop {r4, r5}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_022174C0
MOD13_022174C0: ; 0x022174C0
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	ldr r3, _022174C8 ; =0x020CE34C
	bx r3
	.align 2, 0
_022174C8: .word 0x020CE34C

	thumb_func_start MOD13_022174CC
MOD13_022174CC: ; 0x022174CC
	add r3, r0, #0
	add r0, r1, #0
	add r1, r3, #0
	ldr r3, _022174D8 ; =0x020CE3E0
	bx r3
	nop
_022174D8: .word 0x020CE3E0

	thumb_func_start MOD13_022174DC
MOD13_022174DC: ; 0x022174DC
	push {r4}
	sub sp, #4
	mov r4, #0
	b _022174E8
_022174E4:
	add r0, r0, #1
	add r1, r1, #1
_022174E8:
	add r3, r2, #0
	sub r2, r2, #1
	cmp r3, #0
	ble _022174FA
	ldrb r4, [r0]
	ldrb r3, [r1]
	sub r4, r4, r3
	cmp r4, #0
	beq _022174E4
_022174FA:
	add r0, r4, #0
	add sp, #4
	pop {r4}
	bx lr
	.align 2, 0

	thumb_func_start MOD13_02217504
MOD13_02217504: ; 0x02217504
	push {lr}
	sub sp, #4
	bl SOC_Cleanup
	cmp r0, #0
	bge _0221751A
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r3}
	bx r3
_0221751A:
	bl MOD13_02219C60
	cmp r0, #0
	beq _02217526
	mov r0, #1
	b _02217528
_02217526:
	mov r0, #0
_02217528:
	neg r0, r0
	add sp, #4
	pop {r3}
	bx r3

	thumb_func_start MOD13_02217530
MOD13_02217530: ; 0x02217530
	push {r4, r5, lr}
	sub sp, #4
	add r5, r1, #0
	add r4, r2, #0
	bl MOD13_022173E8
	ldr r1, _0221758C ; =0x0223F7C8
	str r0, [r1, #0x10]
	add r0, r5, #0
	bl MOD13_022173E8
	ldr r1, _0221758C ; =0x0223F7C8
	str r0, [r1, #0x14]
	add r0, r4, #0
	bl MOD13_022173E8
	ldr r1, _0221758C ; =0x0223F7C8
	str r0, [r1, #0x18]
	add r0, r1, #0
	bl SOC_Startup
	cmp r0, #0
	bge _0221756A
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5}
	pop {r3}
	bx r3
_0221756A:
	ldr r5, _02217590 ; =CPSMyIp
	ldr r0, [r5]
	cmp r0, #0
	bne _02217580
	mov r4, #0x64
_02217574:
	add r0, r4, #0
	bl OS_Sleep
	ldr r0, [r5]
	cmp r0, #0
	beq _02217574
_02217580:
	mov r0, #0
	add sp, #4
	pop {r4, r5}
	pop {r3}
	bx r3
	nop
_0221758C: .word MOD13_0223F7C8
_02217590: .word CPSMyIp

	thumb_func_start MOD13_02217594
MOD13_02217594: ; 0x02217594
	push {lr}
	sub sp, #4
	add r0, r1, #0
	ldr r1, _022175A8 ; =0x0224190C
	ldr r1, [r1]
	blx r1
	add sp, #4
	pop {r3}
	bx r3
	nop
_022175A8: .word MOD13_0224190C

	thumb_func_start MOD13_022175AC
MOD13_022175AC: ; 0x022175AC
	push {lr}
	sub sp, #4
	cmp r1, #0
	ble _022175C2
	add r0, r1, #0
	ldr r1, _022175CC ; =0x02241900
	ldr r1, [r1]
	blx r1
	add sp, #4
	pop {r3}
	bx r3
_022175C2:
	mov r0, #0
	add sp, #4
	pop {r3}
	bx r3
	nop
_022175CC: .word MOD13_02241900

	thumb_func_start MOD13_022175D0
MOD13_022175D0: ; 0x022175D0
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	add r0, r6, #0
	mov r1, #2
	bl _s32_div_f
	add r7, r0, #0
	add r0, r4, #0
	add r1, r5, r7
	add r2, r7, #0
	bl MOD13_022174CC
	add r0, r4, r7
	add r1, r5, #0
	add r2, r7, #0
	bl MOD13_022174CC
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD13_022174CC
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_0221760C
MOD13_0221760C: ; 0x0221760C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r0, r2, #0
	mov r1, #2
	bl _s32_div_f
	mov r6, #0
	cmp r0, #0
	ble _02217630
_02217620:
	add r3, r0, r6
	ldrb r2, [r4, r3]
	ldrsb r1, [r5, r6]
	eor r2, r1
	strb r2, [r4, r3]
	add r6, r6, #1
	cmp r6, r0
	blt _02217620
_02217630:
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_02217638
MOD13_02217638: ; 0x02217638
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r6, r0, #0
	add r5, r1, #0
	str r3, [sp]
	ldr r4, [sp, #0x18]
	add r0, r2, #0
	mov r1, #2
	bl _s32_div_f
	add r7, r0, #0
	add r0, r6, #0
	add r1, r4, #0
	bl _s32_div_f
	add r2, r1, #0
	mov r1, #0
	cmp r7, #0
	ble _0221767A
	add r6, r1, #0
_02217660:
	strb r1, [r5, r1]
	ldrsb r0, [r5, r1]
	ldr r3, [sp]
	ldrsb r3, [r3, r2]
	add r2, r2, #1
	eor r0, r3
	strb r0, [r5, r1]
	cmp r2, r4
	blt _02217674
	add r2, r6, #0
_02217674:
	add r1, r1, #1
	cmp r1, r7
	blt _02217660
_0221767A:
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_02217684
MOD13_02217684: ; 0x02217684
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r0, #0
	add r5, r1, #0
	str r2, [sp, #4]
	str r3, [sp, #8]
	add r0, r5, #0
	mov r1, #2
	bl _s32_div_f
	bl MOD13_022198B4
	add r6, r0, #0
	cmp r6, #0
	bne _022176AE
	mov r0, #0
	mvn r0, r0
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022176AE:
	add r0, r5, #0
	bl MOD13_022198B4
	str r0, [sp, #0xc]
	cmp r0, #0
	bne _022176CC
	add r0, r6, #0
	bl MOD13_022198A0
	mov r0, #0
	mvn r0, r0
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022176CC:
	mov r4, #0
_022176CE:
	ldr r0, [sp, #8]
	str r0, [sp]
	add r0, r4, #0
	add r1, r6, #0
	add r2, r5, #0
	ldr r3, [sp, #4]
	bl MOD13_02217638
	add r0, r6, #0
	add r1, r7, #0
	add r2, r5, #0
	bl MOD13_0221760C
	add r0, r7, #0
	add r1, r5, #0
	ldr r2, [sp, #0xc]
	bl MOD13_022175D0
	add r4, r4, #1
	cmp r4, #2
	blt _022176CE
	add r0, r6, #0
	bl MOD13_022198A0
	ldr r0, [sp, #0xc]
	bl MOD13_022198A0
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_02217710
MOD13_02217710: ; 0x02217710
	push {r4, r5, r6, r7}
	mov r6, #0
	add r4, r6, #0
	ldr r2, _02217744 ; =0xEDB88320
	mov r3, #1
_0221771A:
	add r7, r6, #0
	add r5, r4, #0
_0221771E:
	add r0, r7, #0
	and r0, r3
	cmp r0, #0
	beq _0221772C
	lsr r7, r7, #1
	eor r7, r2
	b _0221772E
_0221772C:
	lsr r7, r7, #1
_0221772E:
	add r5, r5, #1
	cmp r5, #8
	blt _0221771E
	stmia r1!, {r7}
	add r6, r6, #1
	ldr r0, _02217748 ; =0x00000100
	cmp r6, r0
	blt _0221771A
	pop {r4, r5, r6, r7}
	bx lr
	nop
_02217744: .word 0xEDB88320
_02217748: .word 0x00000100

	thumb_func_start MOD13_0221774C
MOD13_0221774C: ; 0x0221774C
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r5, r0, #0
	add r7, r1, #0
	add r4, r2, #0
	ldr r6, [sp, #0x18]
	cmp r3, #0
	bne _02217764
	add r0, r3, #0
	add r1, r6, #0
	bl MOD13_02217710
_02217764:
	mov r1, #0
	cmp r4, #0
	ble _02217782
	mov r2, #0xff
_0221776C:
	lsr r0, r5, #8
	ldrb r3, [r7, r1]
	eor r5, r3
	and r5, r2
	lsl r3, r5, #2
	ldr r3, [r6, r3]
	add r5, r0, #0
	eor r5, r3
	add r1, r1, #1
	cmp r1, r4
	blt _0221776C
_02217782:
	add r0, r5, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3

	thumb_func_start MOD13_0221778C
MOD13_0221778C: ; 0x0221778C
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r2, r1, #0
	ldr r0, _022177B4 ; =0x02240E60
	str r0, [sp]
	mov r3, #0
	mvn r0, r3
	add r1, r4, #0
	bl MOD13_0221774C
	mov r1, #0
	mvn r1, r1
	eor r0, r1
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	add sp, #8
	pop {r4}
	pop {r3}
	bx r3
	.align 2, 0
_022177B4: .word MOD13_02240E60

	thumb_func_start MOD13_022177B8
MOD13_022177B8: ; 0x022177B8
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r5, r0, #0
	ldr r4, [r5, #8]
	ldr r0, [r5, #0xc]
	str r0, [sp]
	ldr r0, [r5]
	add r0, r0, #1
	ldr r1, [sp]
	bl _u32_div_f
	lsl r0, r1, #0x18
	lsr r6, r0, #0x18
	ldrb r7, [r4, r6]
	ldr r0, [r5, #4]
	add r0, r7, r0
	ldr r1, [sp]
	bl _u32_div_f
	lsl r0, r1, #0x18
	lsr r1, r0, #0x18
	ldrb r0, [r4, r1]
	str r6, [r5]
	str r1, [r5, #4]
	strb r7, [r4, r1]
	strb r0, [r4, r6]
	add r0, r7, r0
	ldr r1, [r5, #0xc]
	bl _u32_div_f
	ldrb r0, [r4, r1]
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_02217800
MOD13_02217800: ; 0x02217800
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	str r0, [sp]
	add r5, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	mov r4, #0
	cmp r7, #0
	bls _02217828
_02217812:
	ldr r0, [sp]
	bl MOD13_022177B8
	lsl r0, r0, #0x18
	lsr r1, r0, #0x18
	ldrb r0, [r6, r4]
	eor r1, r0
	strb r1, [r5, r4]
	add r4, r4, #1
	cmp r4, r7
	blo _02217812
_02217828:
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3

	thumb_func_start MOD13_02217830
MOD13_02217830: ; 0x02217830
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r0, [sp]
	str r1, [sp, #4]
	str r2, [sp, #8]
	str r3, [sp, #0xc]
	ldr r5, [r0, #8]
	mov r0, #0
	ldr r1, [sp]
	str r0, [r1, #4]
	ldr r2, [r1, #4]
	str r2, [r1]
	lsl r2, r3, #0
	str r2, [r1, #0xc]
	lsl r1, r3, #0
	cmp r1, #0
	bls _0221785C
_02217852:
	strb r0, [r5, r0]
	add r0, r0, #1
	ldr r1, [sp, #0xc]
	cmp r0, r1
	blo _02217852
_0221785C:
	mov r1, #0
	add r6, r1, #0
	add r4, r1, #0
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bls _02217894
	str r1, [sp, #0x10]
_0221786A:
	ldrb r7, [r5, r4]
	ldr r0, [sp, #4]
	ldrb r0, [r0, r6]
	add r0, r1, r0
	add r0, r7, r0
	ldr r1, [sp]
	ldr r1, [r1, #0xc]
	bl _u32_div_f
	ldrb r0, [r5, r1]
	strb r7, [r5, r1]
	strb r0, [r5, r4]
	add r6, r6, #1
	ldr r0, [sp, #8]
	cmp r6, r0
	blo _0221788C
	ldr r6, [sp, #0x10]
_0221788C:
	add r4, r4, #1
	ldr r0, [sp, #0xc]
	cmp r4, r0
	blo _0221786A
_02217894:
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3

	thumb_func_start MOD13_0221789C
MOD13_0221789C: ; 0x0221789C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r7, r0, #0
	add r5, r1, #0
	add r4, r2, #0
	add r6, r3, #0
	add r0, r4, #0
	bl MOD13_022198B4
	str r0, [sp, #8]
	cmp r0, #0
	bne _022178C6
	mov r0, #2
	bl MOD13_02218BF4
	mov r0, #0
	mvn r0, r0
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022178C6:
	ldr r0, _02217928 ; =0x02240B7C
	ldr r1, [sp, #0x28]
	mov r2, #2
	bl MOD13_022174CC
	ldr r0, _0221792C ; =0x02240B7E
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x30]
	bl MOD13_022174CC
	add r0, sp, #0
	ldr r1, _02217928 ; =0x02240B7C
	ldr r2, [sp, #0x30]
	add r2, r2, #2
	add r3, r4, #0
	bl MOD13_02217830
	add r0, sp, #0
	add r1, r5, #0
	add r2, r7, #0
	add r3, r4, #0
	bl MOD13_02217800
	add r0, r5, #0
	add r1, r4, #0
	bl MOD13_0221778C
	cmp r0, r6
	beq _02217918
	mov r0, #0x12
	bl MOD13_02218BF4
	ldr r0, [sp, #8]
	bl MOD13_022198A0
	mov r0, #0
	mvn r0, r0
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02217918:
	ldr r0, [sp, #8]
	bl MOD13_022198A0
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_02217928: .word MOD13_02240B7C
_0221792C: .word MOD13_02240B7E

	thumb_func_start MOD13_02217930
MOD13_02217930: ; 0x02217930
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r6, r0, #0
	add r7, r1, #0
	add r5, r2, #0
	add r4, r3, #0
	add r1, r5, #0
	bl MOD13_0221778C
	strb r0, [r4]
	add r0, r5, #0
	bl MOD13_022198B4
	str r0, [sp, #0xc]
	cmp r0, #0
	bne _0221795C
	mov r0, #0
	mvn r0, r0
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221795C:
	bl MOD13_022172F0
	add r1, sp, #0
	strh r0, [r1]
	ldr r0, [sp, #0x28]
	add r1, sp, #0
	mov r2, #2
	bl MOD13_022174CC
	ldr r0, _022179AC ; =0x02240B7C
	ldr r1, [sp, #0x28]
	mov r2, #2
	bl MOD13_022174CC
	ldr r0, _022179B0 ; =0x02240B7E
	ldr r1, [sp, #0x2c]
	ldr r2, [sp, #0x30]
	bl MOD13_022174CC
	add r0, sp, #4
	ldr r1, _022179AC ; =0x02240B7C
	ldr r2, [sp, #0x30]
	add r2, r2, #2
	add r3, r5, #0
	bl MOD13_02217830
	add r0, sp, #4
	add r1, r7, #0
	add r2, r6, #0
	add r3, r5, #0
	bl MOD13_02217800
	ldr r0, [sp, #0xc]
	bl MOD13_022198A0
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_022179AC: .word MOD13_02240B7C
_022179B0: .word MOD13_02240B7E

	thumb_func_start MOD13_022179B4
MOD13_022179B4: ; 0x022179B4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	add r7, r3, #0
	add r0, sp, #8
	mov r1, #0
	mov r2, #8
	bl MOD13_022174C0
	mov r1, #2
	add r0, sp, #8
	strb r1, [r0, #1]
	ldr r0, _02217A14 ; =0x00005790
	bl MOD13_022173D0
	add r1, sp, #8
	strh r0, [r1, #2]
	ldr r0, _02217A18 ; =0x02240B60
	ldr r0, [r0, #0x10]
	bl MOD13_022173E8
	str r0, [sp, #0xc]
	cmp r4, #0xff
	beq _022179F2
	ldr r1, _02217A18 ; =0x02240B60
	mov r0, #0x18
	ldrsb r0, [r1, r0]
	cmp r0, #0
	bne _022179F8
_022179F2:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #0xc]
_022179F8:
	add r0, sp, #8
	str r0, [sp]
	mov r0, #8
	str r0, [sp, #4]
	add r0, r7, #0
	add r1, r5, #0
	add r2, r6, #0
	mov r3, #0
	bl MOD13_02217440
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_02217A14: .word 0x00005790
_02217A18: .word MOD13_02240B60

	thumb_func_start MOD13_02217A1C
MOD13_02217A1C: ; 0x02217A1C
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r7, r3, #0
	mov r0, #1
	bl MOD13_022173D0
	strh r0, [r5]
	mov r0, #0
	strh r0, [r5, #2]
	strh r0, [r5, #4]
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl MOD13_022173D0
	strh r0, [r5, #6]
	mov r0, #0
	strh r0, [r5, #8]
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	bl MOD13_022173D0
	strh r0, [r5, #0xa]
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	bl MOD13_022173D0
	strh r0, [r5, #0xc]
	add r1, sp, #8
	mov r0, #0x10
	ldrsb r0, [r1, r0]
	strb r0, [r5, #0xe]
	mov r0, #0x14
	ldrsb r0, [r1, r0]
	strb r0, [r5, #0xf]
	add r5, #0x10
	add r0, r5, #0
	ldr r1, [sp, #0x20]
	mov r2, #8
	bl MOD13_022174CC
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_02217A7C
MOD13_02217A7C: ; 0x02217A7C
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r1, #0
	add r4, r3, #0
	cmp r0, #1
	bne _02217AC0
	mov r1, #1
	ldr r0, [sp, #0x18]
	strh r1, [r0]
	add r0, r5, #2
	str r0, [sp]
	ldr r0, _02217AD4 ; =0x02240B4C
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	add r0, r2, #0
	add r1, r5, #4
	mov r2, #0
	ldrsh r2, [r4, r2]
	ldr r3, [sp, #0x1c]
	bl MOD13_02217930
	ldrh r0, [r4]
	bl MOD13_022173D0
	strh r0, [r5]
	mov r0, #0
	ldrsh r0, [r4, r0]
	add r0, r0, #4
	strh r0, [r4]
	add sp, #0xc
	pop {r4, r5}
	pop {r3}
	bx r3
_02217AC0:
	add r0, r5, #0
	add r1, r2, #0
	mov r2, #0
	ldrsh r2, [r4, r2]
	bl MOD13_022174CC
	add sp, #0xc
	pop {r4, r5}
	pop {r3}
	bx r3
	.align 2, 0
_02217AD4: .word MOD13_02240B4C

	thumb_func_start MOD13_02217AD8
MOD13_02217AD8: ; 0x02217AD8
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r5, r0, #0
	mov r6, #0
	ldr r1, _02217B60 ; =0x02240B60
	mov r0, #0x19
	ldrsb r0, [r1, r0]
	strb r0, [r5]
	mov r0, #1
	strb r0, [r5, #1]
	ldr r0, [r1, #4]
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	add r0, r5, #6
	ldr r1, [r1]
	add r2, r4, #0
	bl MOD13_022174CC
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl MOD13_022173D0
	strh r0, [r5, #2]
	add r0, r4, #6
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, r0, #1
	mov r1, #2
	bl _s32_div_f
	lsl r0, r0, #0x11
	asr r7, r0, #0x10
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	bl MOD13_022173D0
	strh r0, [r5, #4]
	add r0, r6, r7
	lsl r0, r0, #0x10
	asr r6, r0, #0x10
	add r4, r5, r7
	mov r0, #0x60
	strb r0, [r5, r7]
	mov r0, #0
	strb r0, [r4, #1]
	bl MOD13_022173D0
	strh r0, [r4, #4]
	mov r0, #0xe
	bl MOD13_022173E8
	str r0, [sp]
	add r0, r4, #6
	add r1, sp, #0
	mov r2, #4
	bl MOD13_022174CC
	mov r0, #4
	bl MOD13_022173D0
	strh r0, [r4, #2]
	add r6, #0xa
	lsl r0, r6, #0x10
	asr r0, r0, #0x10
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_02217B60: .word MOD13_02240B60

	thumb_func_start MOD13_02217B64
MOD13_02217B64: ; 0x02217B64
	push {r4, r5, r6, lr}
	sub sp, #0x18
	add r5, r1, #0
	add r6, r2, #0
	ldr r0, _02217BC4 ; =0x02240B48
	ldr r4, [r0]
	add r0, r4, #0
	mov r1, #0
	ldr r2, _02217BC8 ; =0x000005DC
	bl MOD13_022174C0
	add r0, sp, #0xc
	add r5, #0x10
	add r1, r5, #0
	mov r2, #8
	bl MOD13_022174CC
	ldr r0, _02217BCC ; =0x0223F820
	bl MOD13_0221736C
	add r3, r0, #0
	add r0, sp, #0xc
	mov r1, #8
	ldr r2, _02217BCC ; =0x0223F820
	bl MOD13_02217684
	mov r2, #0
	str r2, [sp]
	mov r0, #0x11
	str r0, [sp, #4]
	add r0, sp, #0xc
	str r0, [sp, #8]
	add r0, r4, #0
	ldr r1, _02217BD0 ; =0x00003000
	add r3, r2, #0
	bl MOD13_02217A1C
	add r0, r4, #0
	mov r1, #0x18
	mov r2, #0
	add r3, r6, #0
	bl MOD13_022179B4
	mov r0, #0
	add sp, #0x18
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	.align 2, 0
_02217BC4: .word MOD13_02240B48
_02217BC8: .word 0x000005DC
_02217BCC: .word MOD13_0223F820
_02217BD0: .word 0x00003000

	thumb_func_start MOD13_02217BD4
MOD13_02217BD4: ; 0x02217BD4
	push {r4, r5, r6, lr}
	sub sp, #0x28
	add r5, r1, #0
	add r6, r2, #0
	mov r1, #0
	add r0, sp, #0xc
	strb r1, [r0]
	strh r1, [r0, #2]
	strh r1, [r0, #4]
	ldr r0, _02217CB0 ; =0x02240B48
	ldr r4, [r0]
	add r0, sp, #0x1c
	mov r2, #8
	bl MOD13_022174C0
	add r0, r4, #0
	mov r1, #0
	ldr r2, _02217CB4 ; =0x000005DC
	bl MOD13_022174C0
	mov r1, #2
	add r0, sp, #0xc
	strb r1, [r0, #0x10]
	mov r1, #0
	strb r1, [r0, #0x11]
	mov r0, #4
	bl MOD13_022173D0
	add r1, sp, #0xc
	strh r0, [r1, #0x12]
	ldr r0, _02217CB8 ; =0x02240B60
	ldr r0, [r0, #8]
	str r0, [sp, #0x20]
	bl MOD13_022173E8
	str r0, [sp, #0x20]
	mov r1, #8
	add r0, sp, #0xc
	strh r1, [r0, #2]
	add r0, sp, #0x10
	str r0, [sp]
	add r0, sp, #0xc
	str r0, [sp, #4]
	ldr r0, _02217CBC ; =0x02240B34
	ldr r0, [r0]
	add r1, r4, #0
	add r1, #0x18
	add r2, sp, #0x1c
	add r3, sp, #0xc
	add r3, #2
	bl MOD13_02217A7C
	add r0, sp, #0x10
	add r0, #2
	add r5, #8
	add r1, r5, #0
	mov r2, #8
	bl MOD13_022174CC
	add r0, sp, #0x10
	add r0, #2
	mov r1, #8
	ldr r2, _02217CC0 ; =0x0223F820
	mov r3, #6
	bl MOD13_02217684
	cmp r0, #0
	beq _02217C6E
	mov r0, #2
	bl MOD13_02218BF4
	mov r0, #0
	mvn r0, r0
	add sp, #0x28
	pop {r4, r5, r6}
	pop {r3}
	bx r3
_02217C6E:
	add r3, sp, #0xc
	mov r0, #0
	ldrsb r0, [r3, r0]
	str r0, [sp]
	mov r0, #0x11
	str r0, [sp, #4]
	add r0, sp, #0x10
	add r0, #2
	str r0, [sp, #8]
	add r0, r4, #0
	ldr r1, _02217CC4 ; =0x00002000
	mov r2, #2
	ldrsh r2, [r3, r2]
	mov r5, #4
	ldrsh r3, [r3, r5]
	bl MOD13_02217A1C
	add r2, sp, #0xc
	mov r1, #2
	ldrsh r0, [r2, r1]
	add r0, #0x18
	strh r0, [r2, #2]
	add r0, r4, #0
	ldrsh r1, [r2, r1]
	mov r2, #0
	add r3, r6, #0
	bl MOD13_022179B4
	mov r0, #0
	add sp, #0x28
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	.align 2, 0
_02217CB0: .word MOD13_02240B48
_02217CB4: .word 0x000005DC
_02217CB8: .word MOD13_02240B60
_02217CBC: .word MOD13_02240B34
_02217CC0: .word MOD13_0223F820
_02217CC4: .word 0x00002000

	thumb_func_start MOD13_02217CC8
MOD13_02217CC8: ; 0x02217CC8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r7, r1, #0
	str r2, [sp, #0xc]
	mov r1, #0
	add r0, sp, #0x10
	strb r1, [r0]
	strh r1, [r0, #2]
	strh r1, [r0, #4]
	ldr r0, _02217E08 ; =0x02240B48
	ldr r5, [r0]
	add r0, r5, #0
	ldr r2, _02217E0C ; =0x000005DC
	bl MOD13_022174C0
	ldr r0, _02217E10 ; =0x00000210
	bl MOD13_022198B4
	add r4, r0, #0
	cmp r4, #0
	bne _02217D04
	mov r0, #2
	bl MOD13_02218BF4
	mov r0, #0
	mvn r0, r0
	add sp, #0x24
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02217D04:
	mov r1, #0
	ldr r2, _02217E10 ; =0x00000210
	bl MOD13_022174C0
	add r6, r5, #0
	add r6, #0x18
	ldr r0, _02217E14 ; =0x02240B4C
	add r1, r7, #0
	mov r2, #8
	bl MOD13_022174CC
	add r0, sp, #0x14
	add r0, #2
	ldr r1, _02217E14 ; =0x02240B4C
	mov r2, #8
	bl MOD13_022174CC
	add r0, r4, #4
	bl MOD13_02217AD8
	add r1, sp, #0x10
	strh r0, [r1, #2]
	mov r0, #2
	ldrsh r0, [r1, r0]
	cmp r0, #0
	bge _02217D54
	mov r0, #3
	bl MOD13_02218BF4
	cmp r4, #0
	beq _02217D48
	add r0, r4, #0
	bl MOD13_022198A0
_02217D48:
	mov r0, #0
	mvn r0, r0
	add sp, #0x24
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02217D54:
	mov r0, #0
	strb r0, [r4]
	ldrh r0, [r1, #2]
	bl MOD13_022173D0
	strh r0, [r4, #2]
	add r1, sp, #0x10
	mov r0, #2
	ldrsh r0, [r1, r0]
	add r0, r0, #4
	strh r0, [r1, #2]
	add r0, sp, #0x14
	str r0, [sp]
	add r0, sp, #0x10
	str r0, [sp, #4]
	mov r0, #0
	add r1, r6, #0
	add r2, r4, #0
	add r3, sp, #0x10
	add r3, #2
	bl MOD13_02217A7C
	add r1, sp, #0x10
	mov r0, #4
	ldrsh r2, [r1, r0]
	mov r0, #0x10
	orr r2, r0
	strh r2, [r1, #4]
	add r0, sp, #0x14
	add r0, #2
	mov r1, #8
	ldr r2, _02217E18 ; =0x0223F820
	mov r3, #6
	bl MOD13_02217684
	cmp r0, #0
	beq _02217DBA
	mov r0, #2
	bl MOD13_02218BF4
	cmp r4, #0
	beq _02217DAE
	add r0, r4, #0
	bl MOD13_022198A0
_02217DAE:
	mov r0, #0
	mvn r0, r0
	add sp, #0x24
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02217DBA:
	add r3, sp, #0x10
	mov r0, #0
	ldrsb r0, [r3, r0]
	str r0, [sp]
	mov r0, #0x11
	str r0, [sp, #4]
	add r0, sp, #0x14
	add r0, #2
	str r0, [sp, #8]
	add r0, r5, #0
	ldr r1, _02217E1C ; =0x00001000
	mov r2, #2
	ldrsh r2, [r3, r2]
	mov r6, #4
	ldrsh r3, [r3, r6]
	bl MOD13_02217A1C
	add r2, sp, #0x10
	mov r1, #2
	ldrsh r0, [r2, r1]
	add r0, #0x18
	strh r0, [r2, #2]
	add r0, r5, #0
	ldrsh r1, [r2, r1]
	mov r2, #0xff
	ldr r3, [sp, #0xc]
	bl MOD13_022179B4
	cmp r4, #0
	beq _02217DFC
	add r0, r4, #0
	bl MOD13_022198A0
_02217DFC:
	mov r0, #0
	add sp, #0x24
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_02217E08: .word MOD13_02240B48
_02217E0C: .word 0x000005DC
_02217E10: .word 0x00000210
_02217E14: .word MOD13_02240B4C
_02217E18: .word MOD13_0223F820
_02217E1C: .word 0x00001000

	thumb_func_start MOD13_02217E20
MOD13_02217E20: ; 0x02217E20
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	add r6, r3, #0
	cmp r0, #0
	beq _02217E36
	cmp r0, #1
	beq _02217E4C
	cmp r0, #2
	beq _02217E62
	b _02217E78
_02217E36:
	mov r0, #2
	bl MOD13_02218870
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD13_02217CC8
	pop {r4, r5, r6}
	pop {r3}
	bx r3
_02217E4C:
	mov r0, #3
	bl MOD13_02218870
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD13_02217BD4
	pop {r4, r5, r6}
	pop {r3}
	bx r3
_02217E62:
	mov r0, #5
	bl MOD13_02218870
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD13_02217B64
	pop {r4, r5, r6}
	pop {r3}
	bx r3
_02217E78:
	mov r0, #0
	mvn r0, r0
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_02217E84
MOD13_02217E84: ; 0x02217E84
	mov r2, #0
	mov r1, #0x10
	and r0, r1
	cmp r0, #0
	beq _02217E90
	mov r2, #1
_02217E90:
	add r0, r2, #0
	bx lr

	thumb_func_start MOD13_02217E94
MOD13_02217E94: ; 0x02217E94
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	str r0, [sp]
	add r4, r1, #0
	add r6, r2, #0
	str r3, [sp, #4]
	mov r5, #0
	cmp r6, #0
	bgt _02217EB2
	mov r0, #1
	mvn r0, r0
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02217EB2:
	ldr r1, _02217FA0 ; =0x0223F7B8
	add r7, r1, r0
_02217EB6:
	add r2, r4, #0
	ldrb r1, [r4]
	ldrb r0, [r7]
	cmp r1, r0
	beq _02217EDC
	ldrh r0, [r4, #2]
	bl MOD13_02217380
	add r0, r0, #4
	add r4, r4, r0
	sub r6, r6, r0
	cmp r6, #0
	bgt _02217EB6
	mov r0, #3
	mvn r0, r0
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02217EDC:
	add r4, r4, #4
	ldrh r0, [r2, #2]
	bl MOD13_02217380
	add r7, r0, #0
	ldr r0, _02217FA4 ; =0x00000350
	ldr r1, [sp]
	mul r1, r0
	ldr r0, [sp, #4]
	add r6, r0, r1
	ldr r0, [sp, #0x28]
	ldr r1, [sp]
	add r1, r1, #3
	lsl r1, r1, #7
	add r0, r0, r1
	str r0, [sp, #8]
	mov r0, #2
	mvn r0, r0
	str r0, [sp, #0xc]
_02217F02:
	ldrb r0, [r4]
	cmp r0, #0xa
	bhi _02217F76
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #8]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, pc
	bx r0
_02217F16: ; jump table
	.short _02217F76 - _02217F16 + 1 ; case 0
	.short _02217F76 - _02217F16 + 1 ; case 1
	.short _02217F76 - _02217F16 + 1 ; case 2
	.short _02217F2C - _02217F16 + 1 ; case 3
	.short _02217F3C - _02217F16 + 1 ; case 4
	.short _02217F4C - _02217F16 + 1 ; case 5
	.short _02217F5C - _02217F16 + 1 ; case 6
	.short _02217F76 - _02217F16 + 1 ; case 7
	.short _02217F76 - _02217F16 + 1 ; case 8
	.short _02217F76 - _02217F16 + 1 ; case 9
	.short _02217F6C - _02217F16 + 1 ; case 10
_02217F2C:
	add r0, r4, #0
	add r1, r6, #0
	add r1, #8
	bl MOD13_022180CC
	mov r1, #1
	orr r5, r1
	b _02217F78
_02217F3C:
	add r0, r4, #0
	ldr r1, _02217FA8 ; =0x00000138
	add r1, r6, r1
	bl MOD13_022180CC
	mov r1, #2
	orr r5, r1
	b _02217F78
_02217F4C:
	add r0, r4, #0
	ldr r1, _02217FAC ; =0x00000268
	add r1, r6, r1
	bl MOD13_02217FFC
	mov r1, #4
	orr r5, r1
	b _02217F78
_02217F5C:
	add r0, r4, #0
	ldr r1, _02217FB0 ; =0x000002D8
	add r1, r6, r1
	bl MOD13_02217FFC
	mov r1, #8
	orr r5, r1
	b _02217F78
_02217F6C:
	add r0, r4, #0
	ldr r1, [sp, #8]
	bl MOD13_02217FB8
	b _02217F78
_02217F76:
	ldr r0, [sp, #0xc]
_02217F78:
	cmp r0, #0
	bne _02217F96
	ldrh r0, [r4, #2]
	bl MOD13_02217380
	add r0, r0, #4
	add r4, r4, r0
	sub r7, r7, r0
	cmp r7, #0
	bgt _02217F02
	ldr r0, _02217FB4 ; =0x02240B60
	ldr r1, [r0, #0xc]
	orr r1, r5
	str r1, [r0, #0xc]
	mov r0, #0
_02217F96:
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_02217FA0: .word MOD13_0223F7B8
_02217FA4: .word 0x00000350
_02217FA8: .word 0x00000138
_02217FAC: .word 0x00000268
_02217FB0: .word 0x000002D8
_02217FB4: .word MOD13_02240B60

	thumb_func_start MOD13_02217FB8
MOD13_02217FB8: ; 0x02217FB8
	push {r4, r5, lr}
	sub sp, #4
	add r5, r1, #0
	add r4, r0, #6
	ldrh r0, [r4, #2]
	bl MOD13_02217380
	add r2, r0, #0
	cmp r2, #0
	bgt _02217FD8
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5}
	pop {r3}
	bx r3
_02217FD8:
	ldrb r0, [r4]
	cmp r0, #0x70
	beq _02217FEA
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5}
	pop {r3}
	bx r3
_02217FEA:
	add r0, r5, #0
	add r1, r4, #6
	bl MOD13_022174CC
	mov r0, #0
	add sp, #4
	pop {r4, r5}
	pop {r3}
	bx r3

	thumb_func_start MOD13_02217FFC
MOD13_02217FFC: ; 0x02217FFC
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r7, r0, #0
	add r6, r1, #0
	add r5, r7, #6
_02218006:
	ldrh r0, [r5, #2]
	bl MOD13_02217380
	add r4, r0, #0
	ldrb r0, [r5]
	cmp r0, #0x35
	bgt _0221801E
	cmp r0, #0x35
	bge _0221803E
	cmp r0, #0x30
	beq _0221802E
	b _0221804E
_0221801E:
	cmp r0, #0x40
	bgt _02218028
	cmp r0, #0x40
	beq _0221802E
	b _0221804E
_02218028:
	cmp r0, #0x45
	beq _0221803E
	b _0221804E
_0221802E:
	cmp r4, #0x40
	bls _0221804E
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221803E:
	cmp r4, #0x21
	bls _0221804E
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221804E:
	cmp r0, #0x35
	bgt _0221805C
	cmp r0, #0x35
	bge _0221807C
	cmp r0, #0x30
	beq _0221806C
	b _022180A4
_0221805C:
	cmp r0, #0x40
	bgt _02218066
	cmp r0, #0x40
	beq _0221806C
	b _022180A4
_02218066:
	cmp r0, #0x45
	beq _0221807C
	b _022180A4
_0221806C:
	add r0, r6, #0
	add r0, #0x30
	add r1, r5, #6
	add r2, r4, #0
	bl MOD13_022174CC
	str r4, [r6, #4]
	b _022180B0
_0221807C:
	cmp r4, #0
	beq _02218096
	sub r0, r4, #1
	add r0, r5, r0
	ldrb r0, [r0, #6]
	cmp r0, #0
	beq _02218096
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218096:
	add r0, r6, #0
	add r0, #8
	add r1, r5, #6
	add r2, r4, #0
	bl MOD13_022174CC
	b _022180B0
_022180A4:
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022180B0:
	ldrh r0, [r5, #4]
	cmp r0, #0
	beq _022180C0
	bl MOD13_02217380
	add r1, r7, #6
	add r5, r1, r0
	b _02218006
_022180C0:
	mov r0, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_022180CC
MOD13_022180CC: ; 0x022180CC
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r7, r0, #0
	add r6, r1, #0
	add r5, r7, #6
_022180D6:
	ldrh r0, [r5, #2]
	bl MOD13_02217380
	add r4, r0, #0
	ldrb r0, [r5]
	cmp r0, #0x21
	bgt _02218114
	cmp r0, #0x21
	bge _02218138
	cmp r0, #0x15
	bgt _0221810E
	add r1, r0, #0
	sub r1, #0x10
	cmp r1, #0
	blt _02218158
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #8]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add r1, pc
	bx r1
_02218102: ; jump table
	.short _02218128 - _02218102 + 1 ; case 0
	.short _02218128 - _02218102 + 1 ; case 1
	.short _02218128 - _02218102 + 1 ; case 2
	.short _02218128 - _02218102 + 1 ; case 3
	.short _02218158 - _02218102 + 1 ; case 4
	.short _02218148 - _02218102 + 1 ; case 5
_0221810E:
	cmp r0, #0x20
	beq _02218138
	b _02218158
_02218114:
	cmp r0, #0x23
	bgt _02218122
	cmp r0, #0x23
	bge _02218138
	cmp r0, #0x22
	beq _02218138
	b _02218158
_02218122:
	cmp r0, #0x25
	beq _02218148
	b _02218158
_02218128:
	cmp r4, #5
	bls _02218158
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218138:
	cmp r4, #0xd
	bls _02218158
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218148:
	cmp r4, #0x21
	bls _02218158
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218158:
	cmp r0, #0x21
	bgt _0221818C
	cmp r0, #0x21
	bge _022181B0
	cmp r0, #0x15
	bgt _02218186
	add r1, r0, #0
	sub r1, #0x10
	cmp r1, #0
	blt _02218208
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #8]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add r1, pc
	bx r1
_0221817A: ; jump table
	.short _022181A0 - _0221817A + 1 ; case 0
	.short _022181B0 - _0221817A + 1 ; case 1
	.short _022181C0 - _0221817A + 1 ; case 2
	.short _022181D0 - _0221817A + 1 ; case 3
	.short _02218208 - _0221817A + 1 ; case 4
	.short _022181E0 - _0221817A + 1 ; case 5
_02218186:
	cmp r0, #0x20
	beq _022181A0
	b _02218208
_0221818C:
	cmp r0, #0x23
	bgt _0221819A
	cmp r0, #0x23
	bge _022181D0
	cmp r0, #0x22
	beq _022181C0
	b _02218208
_0221819A:
	cmp r0, #0x25
	beq _022181E0
	b _02218208
_022181A0:
	add r0, r6, #0
	add r0, #0x30
	add r1, r5, #6
	add r2, r4, #0
	bl MOD13_022174CC
	str r4, [r6, #4]
	b _02218214
_022181B0:
	add r0, r6, #0
	add r0, #0x70
	add r1, r5, #6
	add r2, r4, #0
	bl MOD13_022174CC
	str r4, [r6, #4]
	b _02218214
_022181C0:
	add r0, r6, #0
	add r0, #0xb0
	add r1, r5, #6
	add r2, r4, #0
	bl MOD13_022174CC
	str r4, [r6, #4]
	b _02218214
_022181D0:
	add r0, r6, #0
	add r0, #0xf0
	add r1, r5, #6
	add r2, r4, #0
	bl MOD13_022174CC
	str r4, [r6, #4]
	b _02218214
_022181E0:
	cmp r4, #0
	beq _022181FA
	sub r0, r4, #1
	add r0, r5, r0
	ldrb r0, [r0, #6]
	cmp r0, #0
	beq _022181FA
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022181FA:
	add r0, r6, #0
	add r0, #8
	add r1, r5, #6
	add r2, r4, #0
	bl MOD13_022174CC
	b _02218214
_02218208:
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218214:
	ldrh r0, [r5, #4]
	cmp r0, #0
	beq _02218224
	bl MOD13_02217380
	add r1, r7, #6
	add r5, r1, r0
	b _022180D6
_02218224:
	mov r0, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_02218230
MOD13_02218230: ; 0x02218230
	push {r4, r5}
	mov r5, #0
	sub r2, r1, #1
	add r3, r0, r2
	add r4, r5, #0
	cmp r1, #0
	ble _0221824C
_0221823E:
	lsl r2, r5, #8
	ldrb r0, [r3]
	sub r3, r3, #1
	add r5, r2, r0
	add r4, r4, #1
	cmp r4, r1
	blt _0221823E
_0221824C:
	add r0, r5, #0
	pop {r4, r5}
	bx lr
	.align 2, 0

	thumb_func_start MOD13_02218254
MOD13_02218254: ; 0x02218254
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r6, r0, #0
	add r5, r1, #0
	add r0, r5, #0
	mov r1, #0
	ldr r2, _02218320 ; =0x00000104
	bl MOD13_022174C0
	add r4, r6, #0
	ldr r7, _02218324 ; =0x02240B60
_0221826A:
	ldrh r0, [r4, #2]
	bl MOD13_02217380
	add r2, r0, #0
	cmp r2, #0
	bgt _02218282
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218282:
	ldrb r0, [r4]
	cmp r0, #6
	bhi _022182FC
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #8]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, pc
	bx r0
_02218296: ; jump table
	.short _022182A4 - _02218296 + 1 ; case 0
	.short _022182AE - _02218296 + 1 ; case 1
	.short _022182BA - _02218296 + 1 ; case 2
	.short _022182C6 - _02218296 + 1 ; case 3
	.short _022182C6 - _02218296 + 1 ; case 4
	.short _022182DC - _02218296 + 1 ; case 5
	.short _022182EC - _02218296 + 1 ; case 6
_022182A4:
	add r0, r5, #0
	add r1, r4, #6
	bl MOD13_022174CC
	b _02218308
_022182AE:
	add r0, r5, #0
	add r0, #0x80
	add r1, r4, #6
	bl MOD13_022174CC
	b _02218308
_022182BA:
	ldr r0, _02218328 ; =0x00000100
	add r0, r5, r0
	add r1, r4, #6
	bl MOD13_022174CC
	b _02218308
_022182C6:
	ldrb r0, [r4, #6]
	bl MOD13_02217380
	cmp r0, #0
	bgt _02218308
	mov r0, #1
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022182DC:
	add r0, r4, #6
	add r1, r2, #0
	bl MOD13_02218230
	bl MOD13_02217398
	str r0, [r7, #0x10]
	b _02218308
_022182EC:
	add r0, r4, #6
	add r1, r2, #0
	bl MOD13_02218230
	bl MOD13_02217398
	str r0, [r7, #0x14]
	b _02218308
_022182FC:
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218308:
	ldrh r0, [r4, #4]
	cmp r0, #0
	beq _02218316
	bl MOD13_02217380
	add r4, r6, r0
	b _0221826A
_02218316:
	mov r0, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_02218320: .word 0x00000104
_02218324: .word MOD13_02240B60
_02218328: .word 0x00000100

	thumb_func_start MOD13_0221832C
MOD13_0221832C: ; 0x0221832C
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r4, #0
	ldr r0, _0221837C ; =0x0223F820
	bl MOD13_0221736C
	add r3, r0, #0
	add r0, r5, #0
	mov r1, #8
	ldr r2, _0221837C ; =0x0223F820
	bl MOD13_02217684
	add r0, r6, #0
	add r1, r5, #0
	mov r2, #6
	bl MOD13_022174DC
	cmp r0, #0
	beq _0221835A
	lsl r0, r4, #0
	mvn r4, r0
	b _02218372
_0221835A:
	ldrh r0, [r6, #6]
	bl MOD13_02217380
	add r6, r0, #0
	ldrh r0, [r5, #6]
	bl MOD13_02217380
	add r1, r6, #1
	cmp r1, r0
	beq _02218372
	mov r0, #1
	mvn r4, r0
_02218372:
	add r0, r4, #0
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	nop
_0221837C: .word MOD13_0223F820

	thumb_func_start MOD13_02218380
MOD13_02218380: ; 0x02218380
	push {r4, r5, r6, lr}
	mov r4, #0
	add r5, r4, #0
	add r6, r4, #0
	ldr r3, _022183C0 ; =0x02240B4C
_0221838A:
	ldrb r2, [r3]
	cmp r2, #0
	beq _02218394
	mov r5, #1
	b _0221839C
_02218394:
	add r3, r3, #1
	add r6, r6, #1
	cmp r6, #6
	blt _0221838A
_0221839C:
	cmp r5, #0
	beq _022183B0
	ldr r0, _022183C0 ; =0x02240B4C
	mov r2, #6
	bl MOD13_022174DC
	cmp r0, #0
	beq _022183B8
	mov r4, #1
	b _022183B8
_022183B0:
	ldr r1, _022183C4 ; =0x00001000
	cmp r0, r1
	beq _022183B8
	mov r4, #2
_022183B8:
	add r0, r4, #0
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	.align 2, 0
_022183C0: .word MOD13_02240B4C
_022183C4: .word 0x00001000

	thumb_func_start MOD13_022183C8
MOD13_022183C8: ; 0x022183C8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	add r4, r5, #0
	add r4, #0x18
	add r0, sp, #0xc
	add r1, r5, #0
	add r1, #0x10
	mov r2, #8
	bl MOD13_022174CC
	ldr r0, _022184CC ; =0x0223F820
	bl MOD13_0221736C
	add r3, r0, #0
	add r0, sp, #0xc
	mov r1, #8
	ldr r2, _022184CC ; =0x0223F820
	bl MOD13_02217684
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _0221840A
	mov r0, #2
	bl MOD13_02218BF4
	mov r0, #0x63
	mvn r0, r0
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221840A:
	ldrh r0, [r5, #6]
	bl MOD13_02217380
	add r1, sp, #0xc
	bl MOD13_02218380
	cmp r0, #0
	bne _022184C4
	ldrh r0, [r5, #6]
	bl MOD13_02217380
	ldr r1, _022184D0 ; =0x00001000
	cmp r0, r1
	bne _02218430
	ldr r0, _022184D4 ; =0x02240B4C
	add r1, sp, #0xc
	mov r2, #8
	bl MOD13_022174CC
_02218430:
	ldrh r0, [r5, #0xc]
	bl MOD13_02217380
	mov r1, #0xf
	and r0, r1
	cmp r0, #0
	bne _02218448
	mov r0, #0
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218448:
	ldrh r0, [r4]
	bl MOD13_02217380
	add r6, r0, #0
	bl MOD13_022198B4
	add r7, r0, #0
	cmp r7, #0
	bne _0221846A
	mov r0, #2
	bl MOD13_02218BF4
	mov r0, #0x64
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221846A:
	add r0, r4, #2
	str r0, [sp]
	ldr r0, _022184D4 ; =0x02240B4C
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	add r0, r4, #4
	add r1, r7, #0
	add r2, r6, #0
	ldrb r3, [r5, #0xe]
	bl MOD13_0221789C
	cmp r0, #0
	bge _022184A8
	add r0, r7, #0
	bl MOD13_022198A0
	bl MOD13_02218BE8
	cmp r0, #2
	bne _0221849E
	mov r0, #0x64
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221849E:
	mov r0, #0xc8
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022184A8:
	add r0, r4, #0
	add r1, r7, #0
	add r2, r6, #0
	bl MOD13_022174CC
	lsl r0, r6, #0x10
	lsr r0, r0, #0x10
	bl MOD13_022173D0
	strh r0, [r5, #0xa]
	add r0, r7, #0
	bl MOD13_022198A0
	mov r0, #0
_022184C4:
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_022184CC: .word MOD13_0223F820
_022184D0: .word 0x00001000
_022184D4: .word MOD13_02240B4C

	thumb_func_start MOD13_022184D8
MOD13_022184D8: ; 0x022184D8
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r2, #0
	cmp r6, #2
	beq _022184EE
	ldr r1, [r5]
	add r1, r1, #1
	str r1, [r5]
	pop {r4, r5, r6}
	pop {r3}
	bx r3
_022184EE:
	add r4, r1, #0
	add r4, #0x24
	add r3, #0x10
	add r0, r3, #0
	add r1, #0xc
	add r1, #0x10
	bl MOD13_0221832C
	cmp r0, #0
	bge _02218510
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	add r0, r6, #0
	pop {r4, r5, r6}
	pop {r3}
	bx r3
_02218510:
	ldrb r0, [r4]
	cmp r0, #7
	beq _02218524
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	add r0, r6, #0
	pop {r4, r5, r6}
	pop {r3}
	bx r3
_02218524:
	ldrh r0, [r4, #2]
	bl MOD13_02217380
	cmp r0, #0
	bne _0221853C
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	add r0, r6, #0
	pop {r4, r5, r6}
	pop {r3}
	bx r3
_0221853C:
	ldr r0, [r4, #4]
	bl MOD13_02217398
	cmp r0, #0
	bne _0221854E
	mov r0, #0x64
	pop {r4, r5, r6}
	pop {r3}
	bx r3
_0221854E:
	ldr r0, [r4, #4]
	bl MOD13_02217398
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	bne _0221856C
	mov r0, #0x14
	bl MOD13_02218BF4
	mov r0, #0
	mvn r0, r0
	pop {r4, r5, r6}
	pop {r3}
	bx r3
_0221856C:
	ldr r0, [r4, #4]
	bl MOD13_02217398
	mov r1, #2
	mvn r1, r1
	cmp r0, r1
	bne _0221858A
	mov r0, #0x15
	bl MOD13_02218BF4
	mov r0, #0
	mvn r0, r0
	pop {r4, r5, r6}
	pop {r3}
	bx r3
_0221858A:
	mov r0, #0x18
	bl MOD13_02218BF4
	mov r0, #0
	mvn r0, r0
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_0221859C
MOD13_0221859C: ; 0x0221859C
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r6, r0, #0
	add r5, r2, #0
	cmp r6, #1
	beq _022185B6
	ldr r1, [r5]
	add r1, r1, #1
	str r1, [r5]
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022185B6:
	add r7, r1, #0
	add r7, #0xc
	add r4, r1, #0
	add r4, #0x24
	add r3, #8
	add r0, r3, #0
	add r1, r7, #0
	add r1, #0x10
	bl MOD13_0221832C
	cmp r0, #0
	bge _022185DE
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	add r0, r6, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022185DE:
	ldrh r0, [r4, #2]
	bl MOD13_02217380
	cmp r0, #0
	bne _022185F8
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	add r0, r6, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022185F8:
	ldrb r0, [r4]
	cmp r0, #7
	bne _0221863C
	ldr r0, [r4, #4]
	bl MOD13_02217398
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	bne _02218614
	mov r0, #0x14
	bl MOD13_02218BF4
	b _02218630
_02218614:
	ldr r0, [r4, #4]
	bl MOD13_02217398
	mov r1, #2
	mvn r1, r1
	cmp r0, r1
	bne _0221862A
	mov r0, #0x15
	bl MOD13_02218BF4
	b _02218630
_0221862A:
	mov r0, #0x18
	bl MOD13_02218BF4
_02218630:
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221863C:
	ldr r0, _02218694 ; =0x02241260
	mov r1, #0
	ldr r2, _02218698 ; =0x000006A0
	bl MOD13_022174C0
	ldrh r0, [r7, #0xa]
	bl MOD13_02217380
	add r2, r0, #0
	ldr r0, _0221869C ; =0x02240BE0
	str r0, [sp]
	mov r0, #0
	add r1, r4, #0
	ldr r3, _02218694 ; =0x02241260
	bl MOD13_02217E94
	cmp r0, #0
	bge _02218670
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	add r0, r6, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218670:
	ldr r0, _022186A0 ; =0x02240B60
	ldr r1, [r0, #0xc]
	ldr r0, [r0, #8]
	and r1, r0
	cmp r1, #0
	bne _02218686
	add r0, r6, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218686:
	mov r0, #0
	str r0, [r5]
	mov r0, #2
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_02218694: .word MOD13_02241260
_02218698: .word 0x000006A0
_0221869C: .word MOD13_02240BE0
_022186A0: .word MOD13_02240B60

	thumb_func_start MOD13_022186A4
MOD13_022186A4: ; 0x022186A4
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r6, r0, #0
	add r5, r2, #0
	cmp r6, #0
	beq _022186BE
	ldr r1, [r5]
	add r1, r1, #1
	str r1, [r5]
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022186BE:
	add r7, r1, #0
	add r7, #0xc
	add r4, r1, #0
	add r4, #0x24
	add r0, r3, #0
	add r1, r7, #0
	add r1, #0x10
	bl MOD13_0221832C
	cmp r0, #0
	bge _022186E4
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	add r0, r6, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022186E4:
	ldrh r0, [r4, #2]
	bl MOD13_02217380
	cmp r0, #0
	bne _022186FE
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	add r0, r6, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022186FE:
	ldrb r0, [r4]
	cmp r0, #7
	bne _02218744
	add r5, r4, #4
	ldr r0, [r4, #4]
	bl MOD13_02217398
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	bne _0221871C
	mov r0, #0x14
	bl MOD13_02218BF4
	b _02218738
_0221871C:
	ldr r0, [r5]
	bl MOD13_02217398
	mov r1, #2
	mvn r1, r1
	cmp r0, r1
	bne _02218732
	mov r0, #0x15
	bl MOD13_02218BF4
	b _02218738
_02218732:
	mov r0, #0x18
	bl MOD13_02218BF4
_02218738:
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218744:
	cmp r0, #1
	beq _02218758
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	add r0, r6, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218758:
	add r0, r4, #4
	ldr r1, _022187AC ; =0x02240BE0
	bl MOD13_02218254
	cmp r0, #0
	bge _0221878E
	mov r1, #1
	mvn r1, r1
	cmp r0, r1
	bne _0221877E
	mov r0, #0x16
	bl MOD13_02218BF4
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221877E:
	ldr r0, [r5]
	add r0, r0, #1
	str r0, [r5]
	add r0, r6, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221878E:
	ldrh r0, [r7, #0xc]
	bl MOD13_02217380
	bl MOD13_02217E84
	ldr r1, _022187B0 ; =0x02240B34
	str r0, [r1]
	mov r0, #0
	str r0, [r5]
	mov r0, #1
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_022187AC: .word MOD13_02240BE0
_022187B0: .word MOD13_02240B34

	thumb_func_start MOD13_022187B4
MOD13_022187B4: ; 0x022187B4
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	str r3, [sp]
	add r7, r6, #0
	add r7, #0xc
	ldrh r0, [r6, #0xc]
	bl MOD13_02217380
	cmp r0, #1
	bhs _022187DE
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	add r0, r5, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022187DE:
	ldrb r0, [r7, #0xf]
	cmp r0, #0x11
	beq _022187F4
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	add r0, r5, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022187F4:
	add r0, r6, #0
	add r0, #0xc
	bl MOD13_022183C8
	cmp r0, #0
	ble _02218810
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	add r0, r5, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218810:
	ldrh r0, [r7, #6]
	bl MOD13_02217380
	ldr r1, _02218864 ; =0x00001010
	cmp r0, r1
	beq _0221882A
	ldr r1, _02218868 ; =0x00002010
	cmp r0, r1
	beq _0221883A
	ldr r1, _0221886C ; =0x00003010
	cmp r0, r1
	beq _0221884A
	b _02218858
_0221882A:
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	ldr r3, [sp]
	bl MOD13_022186A4
	add r5, r0, #0
	b _02218858
_0221883A:
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	ldr r3, [sp]
	bl MOD13_0221859C
	add r5, r0, #0
	b _02218858
_0221884A:
	add r0, r5, #0
	add r1, r6, #0
	add r2, r4, #0
	ldr r3, [sp]
	bl MOD13_022184D8
	add r5, r0, #0
_02218858:
	add r0, r5, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_02218864: .word 0x00001010
_02218868: .word 0x00002010
_0221886C: .word 0x00003010

	thumb_func_start MOD13_02218870
MOD13_02218870: ; 0x02218870
	push {lr}
	sub sp, #4
	mov r3, #0
	mvn r1, r3
	cmp r0, r1
	bne _02218888
	ldr r1, _022188A4 ; =0x0223F7C4
	str r0, [r1]
	add r0, r3, #0
	add sp, #4
	pop {r3}
	bx r3
_02218888:
	ldr r1, _022188A4 ; =0x0223F7C4
	ldr r2, [r1]
	cmp r2, r0
	beq _0221889C
	str r0, [r1]
	bl MOD13_022198C8
	add sp, #4
	pop {r3}
	bx r3
_0221889C:
	add r0, r3, #0
	add sp, #4
	pop {r3}
	bx r3
	.align 2, 0
_022188A4: .word MOD13_0223F7C4

	thumb_func_start MOD13_022188A8
MOD13_022188A8: ; 0x022188A8
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r6, r0, #0
	add r5, r1, #0
	add r7, r2, #0
	mov r4, #0
	cmp r6, #0
	ble _022188D8
_022188B8:
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #6
	bl MOD13_022174CC
	bl MOD13_022172F0
	strh r0, [r5, #6]
	ldrh r0, [r5, #6]
	bl MOD13_022173D0
	strh r0, [r5, #6]
	add r5, #8
	add r4, r4, #1
	cmp r4, r6
	blt _022188B8
_022188D8:
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3

	thumb_func_start MOD13_022188E0
MOD13_022188E0: ; 0x022188E0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02218924 ; =0x0223F828
	bl MOD13_0221736C
	str r0, [r4]
	add r0, r4, #4
	ldr r1, _02218924 ; =0x0223F828
	ldr r2, [r4]
	bl MOD13_022174CC
	mov r0, #1
	str r0, [r4, #0x24]
	ldr r0, _02218928 ; =0x0223F820
	bl MOD13_0221736C
	str r0, [r4, #0x28]
	ldr r2, [r4, #0x28]
	cmp r2, #0xd
	bls _02218912
	mov r0, #0
	mvn r0, r0
	pop {r4}
	pop {r3}
	bx r3
_02218912:
	add r4, #0x2c
	add r0, r4, #0
	ldr r1, _02218928 ; =0x0223F820
	bl MOD13_022174CC
	mov r0, #0
	pop {r4}
	pop {r3}
	bx r3
	.align 2, 0
_02218924: .word MOD13_0223F828
_02218928: .word MOD13_0223F820

	thumb_func_start MOD13_0221892C
MOD13_0221892C: ; 0x0221892C
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r5, r0, #0
	mov r4, #0
	str r4, [sp, #4]
	ldr r0, [r5]
	str r0, [sp]
	cmp r0, #0
	bne _02218948
	mov r0, #5
	add sp, #0xc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218948:
	cmp r0, #0x40
	bls _02218950
	mov r0, #0x40
	str r0, [sp]
_02218950:
	mov r7, #0
	ldr r0, [sp]
	cmp r0, #0
	ble _02218994
	add r6, r5, #0
	add r6, #8
_0221895C:
	ldr r1, [r5, #0x54]
	mov r0, #1
	and r1, r0
	cmp r1, #0
	beq _02218988
	ldr r0, _022189B0 ; =0x0223F828
	bl MOD13_0221736C
	ldr r1, [r5, #4]
	cmp r1, r0
	bne _02218988
	ldr r0, _022189B0 ; =0x0223F828
	bl MOD13_0221736C
	add r2, r0, #0
	add r0, r6, #0
	ldr r1, _022189B0 ; =0x0223F828
	bl MOD13_022174DC
	cmp r0, #0
	bne _02218988
	add r4, r4, #1
_02218988:
	add r5, #0x54
	add r6, #0x54
	add r7, r7, #1
	ldr r0, [sp]
	cmp r7, r0
	blt _0221895C
_02218994:
	cmp r4, #1
	ble _0221899C
	mov r0, #4
	str r0, [sp, #4]
_0221899C:
	cmp r4, #0
	bne _022189A4
	mov r0, #5
	str r0, [sp, #4]
_022189A4:
	ldr r0, [sp, #4]
	add sp, #0xc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_022189B0: .word MOD13_0223F828

	thumb_func_start MOD13_022189B4
MOD13_022189B4: ; 0x022189B4
	mov r3, #0
	cmp r1, #0
	ble _022189D2
_022189BA:
	ldrb r2, [r0]
	add r0, r0, #1
	cmp r2, #0x20
	blo _022189C6
	cmp r2, #0x7f
	bls _022189CC
_022189C6:
	mov r0, #0
	mvn r0, r0
	bx lr
_022189CC:
	add r3, r3, #1
	cmp r3, r1
	blt _022189BA
_022189D2:
	mov r0, #0
	bx lr
	.align 2, 0

	thumb_func_start MOD13_022189D8
MOD13_022189D8: ; 0x022189D8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r0, #0
	ldr r0, _02218BC4 ; =0x00000117
	add r5, r7, r0
	ldr r4, _02218BC8 ; =0x02241268
	ldr r6, _02218BCC ; =0x02241398
	ldr r0, _02218BD0 ; =0x022414C8
	str r0, [sp]
	ldr r0, _02218BD4 ; =0x02241538
	str r0, [sp, #4]
	cmp r5, #0
	bne _022189FE
	mov r0, #0
	mvn r0, r0
	add sp, #0xc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022189FE:
	ldr r0, _02218BD8 ; =0x02240B60
	ldr r1, [r0, #8]
	ldr r0, [r0, #0xc]
	and r1, r0
	strh r1, [r7]
	add r0, r5, #0
	mov r1, #0
	ldr r2, _02218BDC ; =0x00000154
	bl MOD13_022174C0
	ldrh r1, [r7]
	mov r0, #1
	and r1, r0
	cmp r1, #0
	beq _02218A7E
	add r0, r5, #0
	add r1, r4, #0
	add r1, #0x30
	ldr r2, [r4, #4]
	bl MOD13_022174CC
	add r0, r5, #6
	add r1, r4, #0
	add r1, #0x70
	ldr r2, [r4, #4]
	bl MOD13_022174CC
	add r0, r5, #0
	add r0, #0xc
	add r1, r4, #0
	add r1, #0xb0
	ldr r2, [r4, #4]
	bl MOD13_022174CC
	add r0, r5, #0
	add r0, #0x12
	add r1, r4, #0
	add r1, #0xf0
	ldr r2, [r4, #4]
	bl MOD13_022174CC
	add r0, r4, #0
	add r0, #8
	bl MOD13_0221736C
	add r1, r0, #0
	add r0, r4, #0
	add r0, #8
	bl MOD13_022189B4
	cmp r0, #0
	beq _02218A68
	b _02218BAE
_02218A68:
	add r0, r4, #0
	add r0, #8
	bl MOD13_0221736C
	add r2, r0, #0
	add r0, r5, #0
	add r0, #0x18
	add r4, #8
	add r1, r4, #0
	bl MOD13_022174CC
_02218A7E:
	ldrh r1, [r7]
	mov r0, #2
	and r1, r0
	cmp r1, #0
	beq _02218AEC
	add r0, r5, #0
	add r0, #0x39
	add r1, r6, #0
	add r1, #0x30
	ldr r2, [r6, #4]
	bl MOD13_022174CC
	add r0, r5, #0
	add r0, #0x47
	add r1, r6, #0
	add r1, #0x70
	ldr r2, [r6, #4]
	bl MOD13_022174CC
	add r0, r5, #0
	add r0, #0x55
	add r1, r6, #0
	add r1, #0xb0
	ldr r2, [r6, #4]
	bl MOD13_022174CC
	add r0, r5, #0
	add r0, #0x63
	add r1, r6, #0
	add r1, #0xf0
	ldr r2, [r6, #4]
	bl MOD13_022174CC
	add r0, r6, #0
	add r0, #8
	bl MOD13_0221736C
	add r1, r0, #0
	add r0, r6, #0
	add r0, #8
	bl MOD13_022189B4
	cmp r0, #0
	bne _02218BAE
	add r0, r6, #0
	add r0, #8
	bl MOD13_0221736C
	add r2, r0, #0
	add r0, r5, #0
	add r0, #0x71
	add r6, #8
	add r1, r6, #0
	bl MOD13_022174CC
_02218AEC:
	ldrh r1, [r7]
	mov r0, #4
	and r1, r0
	cmp r1, #0
	beq _02218B46
	ldr r0, [sp]
	add r0, #0x30
	ldr r1, [sp]
	ldr r1, [r1, #4]
	sub r1, r1, #1
	bl MOD13_022189B4
	cmp r0, #0
	bne _02218BAE
	add r0, r5, #0
	add r0, #0x92
	ldr r1, [sp]
	add r1, #0x30
	ldr r2, [sp]
	ldr r2, [r2, #4]
	bl MOD13_022174CC
	ldr r0, [sp]
	add r0, #8
	bl MOD13_0221736C
	add r1, r0, #0
	ldr r0, [sp]
	add r0, #8
	bl MOD13_022189B4
	cmp r0, #0
	bne _02218BAE
	ldr r0, [sp]
	add r0, #8
	bl MOD13_0221736C
	add r2, r0, #0
	add r0, r5, #0
	add r0, #0xd2
	ldr r1, [sp]
	add r1, #8
	str r1, [sp]
	bl MOD13_022174CC
_02218B46:
	ldrh r1, [r7]
	mov r0, #8
	and r1, r0
	cmp r1, #0
	beq _02218BA0
	ldr r0, [sp, #4]
	add r0, #0x30
	ldr r1, [sp, #4]
	ldr r1, [r1, #4]
	sub r1, r1, #1
	bl MOD13_022189B4
	cmp r0, #0
	bne _02218BAE
	add r0, r5, #0
	add r0, #0xf3
	ldr r1, [sp, #4]
	add r1, #0x30
	ldr r2, [sp, #4]
	ldr r2, [r2, #4]
	bl MOD13_022174CC
	ldr r0, [sp, #4]
	add r0, #8
	bl MOD13_0221736C
	add r1, r0, #0
	ldr r0, [sp, #4]
	add r0, #8
	bl MOD13_022189B4
	cmp r0, #0
	bne _02218BAE
	ldr r0, [sp, #4]
	add r0, #8
	bl MOD13_0221736C
	add r2, r0, #0
	ldr r0, _02218BE0 ; =0x00000133
	add r0, r5, r0
	ldr r1, [sp, #4]
	add r1, #8
	str r1, [sp, #4]
	bl MOD13_022174CC
_02218BA0:
	mov r0, #0
	ldr r1, _02218BE4 ; =0x00000116
	strb r0, [r7, r1]
	add sp, #0xc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218BAE:
	add r0, r5, #0
	mov r1, #0
	ldr r2, _02218BDC ; =0x00000154
	bl MOD13_022174C0
	mov r0, #0
	mvn r0, r0
	add sp, #0xc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_02218BC4: .word 0x00000117
_02218BC8: .word MOD13_02241268
_02218BCC: .word MOD13_02241398
_02218BD0: .word MOD13_022414C8
_02218BD4: .word MOD13_02241538
_02218BD8: .word MOD13_02240B60
_02218BDC: .word 0x00000154
_02218BE0: .word 0x00000133
_02218BE4: .word 0x00000116

	thumb_func_start MOD13_02218BE8
MOD13_02218BE8: ; 0x02218BE8
	ldr r0, _02218BF0 ; =0x02240B44
	ldr r0, [r0]
	bx lr
	nop
_02218BF0: .word MOD13_02240B44

	thumb_func_start MOD13_02218BF4
MOD13_02218BF4: ; 0x02218BF4
	ldr r1, _02218BFC ; =0x02240B44
	str r0, [r1]
	bx lr
	nop
_02218BFC: .word MOD13_02240B44

	thumb_func_start MOD13_02218C00
MOD13_02218C00: ; 0x02218C00
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02218C44 ; =0x02240B4C
	mov r1, #0
	mov r2, #8
	bl MOD13_022174C0
	mov r1, #1
	ldr r0, _02218C48 ; =0x02240B44
	str r1, [r0]
	ldr r0, _02218C4C ; =0x02240B60
	mov r1, #0
	mov r2, #0x1c
	bl MOD13_022174C0
	add r0, r4, #6
	ldr r1, _02218C4C ; =0x02240B60
	str r0, [r1]
	ldrh r0, [r4, #4]
	str r0, [r1, #4]
	ldrh r2, [r4]
	mov r0, #0xf
	and r2, r0
	str r2, [r1, #8]
	ldrb r0, [r4, #2]
	strb r0, [r1, #0x19]
	mov r2, #0
	str r2, [r1, #0xc]
	ldr r0, _02218C50 ; =0xC0A80B01
	str r0, [r1, #0x10]
	strb r2, [r1, #0x18]
	pop {r4}
	pop {r3}
	bx r3
	.align 2, 0
_02218C44: .word MOD13_02240B4C
_02218C48: .word MOD13_02240B44
_02218C4C: .word MOD13_02240B60
_02218C50: .word 0xC0A80B01

	thumb_func_start MOD13_02218C54
MOD13_02218C54: ; 0x02218C54
	push {lr}
	sub sp, #4
	ldr r0, _02218C84 ; =0x02240B40
	ldr r0, [r0]
	cmp r0, #0
	beq _02218C6A
	bl MOD13_022198A0
	mov r1, #0
	ldr r0, _02218C84 ; =0x02240B40
	str r1, [r0]
_02218C6A:
	ldr r0, _02218C88 ; =0x02240B38
	ldr r0, [r0]
	cmp r0, #0
	beq _02218C7C
	bl MOD13_022198A0
	mov r1, #0
	ldr r0, _02218C88 ; =0x02240B38
	str r1, [r0]
_02218C7C:
	add sp, #4
	pop {r3}
	bx r3
	nop
_02218C84: .word MOD13_02240B40
_02218C88: .word MOD13_02240B38

	thumb_func_start MOD13_02218C8C
MOD13_02218C8C: ; 0x02218C8C
	add r3, r0, #0
	and r3, r1
	mvn r2, r1
	bic r0, r1
	add r1, r0, #1
	add r0, r3, #0
	orr r0, r1
	add r1, r3, #0
	orr r1, r2
	cmp r0, r1
	blo _02218CA8
	mov r1, #1
	add r0, r3, #0
	orr r0, r1
_02218CA8:
	bx lr
	.align 2, 0

	thumb_func_start MOD13_02218CAC
MOD13_02218CAC: ; 0x02218CAC
	push {r4, r5, r6, r7, lr}
	sub sp, #0xcc
	str r0, [sp, #8]
	ldr r1, _02219044 ; =0x0223F7C0
	ldrh r2, [r1]
	add r0, sp, #0x30
	strh r2, [r0]
	ldrh r1, [r1, #2]
	strh r1, [r0, #2]
	add r1, sp, #0x34
	mov r0, #0
	str r0, [sp, #0x14]
	strh r0, [r1]
	strh r0, [r1, #2]
	mov r0, #1
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x14]
	str r0, [sp, #0x3c]
	str r0, [sp, #0x1c]
	add r0, sp, #0x64
	ldr r1, [sp, #0x14]
	mov r2, #0x18
	bl MOD13_022174C0
	ldr r1, _02219048 ; =0x00000106
	ldr r0, [sp, #8]
	ldrsh r0, [r0, r1]
	add r1, sp, #0x30
	strh r0, [r1]
	mov r0, #0
	ldrsh r2, [r1, r0]
	mvn r0, r0
	cmp r2, r0
	bne _02218CF4
	mov r0, #0xa
	strh r0, [r1]
_02218CF4:
	ldr r1, _0221904C ; =0x0000010A
	ldr r0, [sp, #8]
	ldrsh r0, [r0, r1]
	add r1, sp, #0x30
	strh r0, [r1, #4]
	mov r0, #4
	ldrsh r2, [r1, r0]
	mov r0, #0
	mvn r0, r0
	cmp r2, r0
	bne _02218D0E
	mov r0, #0xa
	strh r0, [r1, #4]
_02218D0E:
	ldr r1, _02219050 ; =0x00000108
	ldr r0, [sp, #8]
	ldrsh r0, [r0, r1]
	add r1, sp, #0x30
	strh r0, [r1, #2]
	mov r0, #2
	ldrsh r2, [r1, r0]
	mov r0, #0
	mvn r0, r0
	cmp r2, r0
	bne _02218D28
	mov r0, #0x64
	strh r0, [r1, #2]
_02218D28:
	ldr r1, _02219054 ; =0x0000010C
	ldr r0, [sp, #8]
	ldrsh r0, [r0, r1]
	add r1, sp, #0x30
	strh r0, [r1, #6]
	mov r0, #6
	ldrsh r2, [r1, r0]
	mov r0, #0
	mvn r0, r0
	cmp r2, r0
	bne _02218D42
	mov r0, #0x64
	strh r0, [r1, #6]
_02218D42:
	ldr r1, _02219058 ; =0x0000010E
	ldr r0, [sp, #8]
	ldrsh r0, [r0, r1]
	str r0, [sp, #0x10]
	mov r0, #0
	mvn r1, r0
	ldr r0, [sp, #0x10]
	cmp r0, r1
	bne _02218D58
	ldr r0, _0221905C ; =0x000007D0
	str r0, [sp, #0x10]
_02218D58:
	ldr r0, [sp, #8]
	bl MOD13_02218C00
	ldr r0, _02219060 ; =0x02240B60
	ldr r1, [r0, #8]
	mov r0, #1
	and r1, r0
	cmp r1, #1
	beq _02218D88
	mov r0, #0x13
	bl MOD13_02218BF4
	mov r2, #0xf
	ldr r1, _02219064 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218D88:
	mov r4, #0
	add r0, r4, #0
	bl MOD13_02218870
	mov r1, #2
	add r0, sp, #0x30
	ldrsh r7, [r0, r1]
	lsl r6, r4, #0
	ldr r5, _02219068 ; =0x02240B38
_02218D9A:
	ldr r0, [r5]
	cmp r0, #0
	beq _02218DA6
	bl MOD13_022198A0
	str r6, [r5]
_02218DA6:
	add r0, r5, #0
	bl MOD13_02219AD0
	mvn r1, r6
	cmp r0, r1
	bne _02218DCA
	mov r2, #0xf
	ldr r1, _02219064 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218DCA:
	ldr r0, [r5]
	bl MOD13_0221892C
	cmp r0, #4
	bne _02218DEC
	mov r2, #2
	ldr r1, _02219064 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218DEC:
	cmp r0, #0
	beq _02218E1E
	add r0, sp, #0x30
	ldrsh r0, [r0, r6]
	cmp r4, r0
	blt _02218E10
	mov r2, #1
	ldr r1, _02219064 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218E10:
	add r0, r7, #0
	bl MOD13_022198E4
	add r0, r4, #1
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	b _02218D9A
_02218E1E:
	mov r0, #1
	bl MOD13_02218870
	add r0, sp, #0x7c
	mov r1, #0
	mov r2, #0x3c
	bl MOD13_022174C0
	add r0, sp, #0x7c
	bl MOD13_022188E0
	cmp r0, #0
	beq _02218E50
	mov r2, #0xf
	ldr r1, _02219064 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218E50:
	mov r0, #0x58
	bl MOD13_022198B4
	ldr r1, _0221906C ; =0x02240B40
	str r0, [r1]
	cmp r0, #0
	bne _02218E76
	mov r2, #0xf
	ldr r1, _02219064 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218E76:
	mov r1, #0
	mov r2, #0x58
	bl MOD13_022174C0
	mov r4, #0
	add r0, sp, #0x30
	ldrsh r0, [r0, r4]
	cmp r0, #0
	ble _02218EDA
	add r6, r4, #0
	add r5, r4, #0
_02218E8C:
	add r0, sp, #0x7c
	ldr r1, _0221906C ; =0x02240B40
	ldr r1, [r1]
	bl MOD13_022198EC
	mvn r1, r5
	cmp r0, r1
	bne _02218EB4
	mov r2, #0xf
	ldr r1, _02219064 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218EB4:
	cmp r0, #0
	bne _02218EC6
	cmp r0, #0
	bne _02218EDA
	ldr r0, _0221906C ; =0x02240B40
	ldr r0, [r0]
	ldr r0, [r0]
	cmp r0, #1
	beq _02218EDA
_02218EC6:
	add r0, r7, #0
	bl MOD13_022198E4
	add r0, r4, #1
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	add r0, sp, #0x30
	ldrsh r0, [r0, r6]
	cmp r4, r0
	blt _02218E8C
_02218EDA:
	add r1, sp, #0x30
	mov r0, #0
	ldrsh r0, [r1, r0]
	cmp r4, r0
	bne _02218EFC
	mov r2, #0xf
	ldr r1, _02219064 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218EFC:
	ldr r0, _02219070 ; =0xC0A80B65
	mov r1, #0xff
	mvn r1, r1
	add r2, r0, #0
	bl MOD13_02217530
	cmp r0, #0
	beq _02218F2A
	mov r0, #0xc
	bl MOD13_02218BF4
	mov r2, #0xf
	ldr r1, _02219064 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218F2A:
	bl MOD13_02218C54
	mov r0, #3
	add r1, sp, #0x64
	ldr r3, _02219074 ; =0x00000110
	ldr r2, [sp, #8]
	add r2, r2, r3
	bl MOD13_022188A8
	mov r0, #2
	add r1, r0, #0
	mov r2, #0
	bl MOD13_02217434
	ldr r1, _02219078 ; =0x0223F7BC
	str r0, [r1]
	cmp r0, #0
	bge _02218F66
	mov r2, #0xf
	ldr r1, _02219064 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218F66:
	mov r1, #4
	str r1, [sp]
	ldr r1, _0221907C ; =0x0000FFFF
	mov r2, #1
	add r3, sp, #0x38
	bl MOD13_0221743C
	cmp r0, #0
	bge _02218F96
	mov r0, #0xb
	bl MOD13_02218BF4
	mov r2, #0xf
	ldr r1, _02219064 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218F96:
	add r0, sp, #0x5c
	mov r1, #0
	mov r2, #8
	bl MOD13_022174C0
	mov r1, #2
	add r0, sp, #0x5c
	strb r1, [r0, #1]
	ldr r0, _02219070 ; =0xC0A80B65
	bl MOD13_022173E8
	str r0, [sp, #0x60]
	ldr r0, _02219080 ; =0x00005790
	bl MOD13_022173D0
	add r1, sp, #0x30
	strh r0, [r1, #0x2e]
	ldr r0, _02219078 ; =0x0223F7BC
	ldr r0, [r0]
	add r1, sp, #0x5c
	mov r2, #8
	bl MOD13_02217428
	cmp r0, #0
	bge _02218FE0
	mov r2, #0xf
	ldr r1, _02219064 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02218FE0:
	mov r5, #0
	ldr r6, _02219068 ; =0x02240B38
	mvn r0, r5
	str r0, [sp, #0x28]
_02218FE8:
	ldr r0, _02219084 ; =0x02240B48
	ldr r0, [r0]
	str r0, [sp, #0x20]
	add r0, sp, #0xb8
	add r1, r5, #0
	mov r2, #0x14
	bl MOD13_022174C0
	ldr r0, _02219070 ; =0xC0A80B65
	str r0, [sp, #0xc8]
	ldr r0, _02219088 ; =0xC0A80B01
	str r0, [sp, #0xb8]
	ldr r0, [sp, #0x10]
	ldr r1, _0221908C ; =0x000003E8
	bl _s32_div_f
	str r0, [sp, #0x24]
	ldr r0, [sp, #0x10]
	ldr r1, _0221908C ; =0x000003E8
	bl _s32_div_f
	str r1, [sp, #0xc]
	ldr r0, _0221908C ; =0x000003E8
	mul r1, r0
	str r1, [sp, #0xc]
_0221901A:
	ldr r0, [sp, #0x14]
	cmp r0, #1
	beq _02219022
	b _0221930A
_02219022:
	ldr r1, _02219060 ; =0x02240B60
	mov r0, #0x18
	ldrsb r0, [r1, r0]
	cmp r0, #1
	bne _0221902E
	b _0221930A
_0221902E:
	ldr r0, _02219078 ; =0x0223F7BC
	ldr r0, [r0]
	mvn r1, r5
	cmp r0, r1
	beq _0221903C
	bl MOD13_02217420
_0221903C:
	ldr r1, [sp, #0x28]
	ldr r0, _02219078 ; =0x0223F7BC
	b _02219090
	nop
_02219044: .word MOD13_0223F7C0
_02219048: .word 0x00000106
_0221904C: .word 0x0000010A
_02219050: .word 0x00000108
_02219054: .word 0x0000010C
_02219058: .word 0x0000010E
_0221905C: .word 0x000007D0
_02219060: .word MOD13_02240B60
_02219064: .word 0x00000116
_02219068: .word MOD13_02240B38
_0221906C: .word MOD13_02240B40
_02219070: .word 0xC0A80B65
_02219074: .word 0x00000110
_02219078: .word MOD13_0223F7BC
_0221907C: .word 0x0000FFFF
_02219080: .word 0x00005790
_02219084: .word MOD13_02240B48
_02219088: .word 0xC0A80B01
_0221908C: .word 0x000003E8
_02219090:
	str r1, [r0]
	bl MOD13_02217504
	cmp r0, #0
	beq _022190B2
	mov r2, #0xf
	ldr r1, _02219414 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022190B2:
	mov r0, #0x58
	bl MOD13_022198B4
	str r0, [r6]
	cmp r0, #0
	bne _022190D6
	mov r2, #0xf
	ldr r1, _02219414 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022190D6:
	ldr r0, [r6]
	cmp r0, #0
	beq _022190E2
	bl MOD13_022198A0
	str r5, [r6]
_022190E2:
	add r0, r6, #0
	bl MOD13_02219AD0
	str r0, [sp, #0x2c]
	mvn r1, r5
	cmp r0, r1
	bne _02219108
	mov r2, #0xf
	ldr r1, _02219414 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219108:
	ldr r0, [r6]
	bl MOD13_0221892C
	cmp r0, #4
	bne _0221912A
	mov r2, #2
	ldr r1, _02219414 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221912A:
	cmp r0, #0
	beq _0221915C
	add r0, sp, #0x30
	ldrsh r0, [r0, r5]
	cmp r4, r0
	blt _0221914E
	mov r2, #1
	ldr r1, _02219414 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221914E:
	add r0, r7, #0
	bl MOD13_022198E4
	add r0, r4, #1
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	b _022190D6
_0221915C:
	mvn r1, r5
	ldr r0, [sp, #0x2c]
	cmp r0, r1
	bne _0221917C
	mov r2, #0xf
	ldr r1, _02219414 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221917C:
	mov r0, #0x58
	bl MOD13_022198B4
	ldr r1, _02219418 ; =0x02240B40
	str r0, [r1]
	cmp r0, #0
	bne _022191A2
	mov r2, #0xf
	ldr r1, _02219414 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022191A2:
	add r1, r5, #0
	mov r2, #0x58
	bl MOD13_022174C0
	add r4, r5, #0
	add r0, sp, #0x30
	ldrsh r0, [r0, r5]
	cmp r0, #0
	ble _02219202
_022191B4:
	add r0, sp, #0x7c
	ldr r1, _02219418 ; =0x02240B40
	ldr r1, [r1]
	bl MOD13_022198EC
	mvn r1, r5
	cmp r0, r1
	bne _022191DC
	mov r2, #0xf
	ldr r1, _02219414 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022191DC:
	cmp r0, #0
	bne _022191EE
	cmp r0, #0
	bne _02219202
	ldr r0, _02219418 ; =0x02240B40
	ldr r0, [r0]
	ldr r0, [r0]
	cmp r0, #1
	beq _02219202
_022191EE:
	add r0, r7, #0
	bl MOD13_022198E4
	add r0, r4, #1
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	add r0, sp, #0x30
	ldrsh r0, [r0, r5]
	cmp r4, r0
	blt _022191B4
_02219202:
	add r0, sp, #0x30
	ldrsh r0, [r0, r5]
	cmp r4, r0
	bne _02219222
	mov r2, #0xf
	ldr r1, _02219414 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219222:
	ldr r0, _0221941C ; =0x02240B60
	ldr r0, [r0, #0x10]
	ldr r1, _0221941C ; =0x02240B60
	ldr r1, [r1, #0x14]
	bl MOD13_02218C8C
	str r0, [sp, #0x1c]
	ldr r1, _0221941C ; =0x02240B60
	ldr r1, [r1, #0x14]
	lsl r2, r0, #0
	bl MOD13_02217530
	cmp r0, #0
	beq _0221925C
	mov r0, #0xc
	bl MOD13_02218BF4
	mov r2, #0xf
	ldr r1, _02219414 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221925C:
	mov r1, #1
	ldr r0, _0221941C ; =0x02240B60
	strb r1, [r0, #0x18]
	bl MOD13_02218C54
	mov r0, #2
	lsl r1, r0, #0
	add r2, r5, #0
	bl MOD13_02217434
	ldr r1, _02219420 ; =0x0223F7BC
	str r0, [r1]
	cmp r0, #0
	bge _02219290
	mov r2, #0xf
	ldr r1, _02219414 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219290:
	mov r1, #4
	str r1, [sp]
	ldr r1, _02219424 ; =0x0000FFFF
	mov r2, #1
	add r3, sp, #0x38
	bl MOD13_0221743C
	cmp r0, #0
	bge _022192C0
	mov r0, #0xb
	bl MOD13_02218BF4
	mov r2, #0xf
	ldr r1, _02219414 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022192C0:
	add r0, sp, #0x5c
	add r1, r5, #0
	mov r2, #8
	bl MOD13_022174C0
	mov r1, #2
	add r0, sp, #0x5c
	strb r1, [r0, #1]
	ldr r0, [sp, #0x1c]
	bl MOD13_022173E8
	str r0, [sp, #0x60]
	ldr r0, _02219428 ; =0x00005790
	bl MOD13_022173D0
	add r1, sp, #0x30
	strh r0, [r1, #0x2e]
	ldr r0, _02219420 ; =0x0223F7BC
	ldr r0, [r0]
	add r1, sp, #0x5c
	mov r2, #8
	bl MOD13_02217428
	cmp r0, #0
	bge _0221930A
	mov r2, #0xf
	ldr r1, _02219414 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221930A:
	ldr r0, [sp, #0x14]
	add r1, sp, #0xb8
	add r2, sp, #0x64
	ldr r3, _02219420 ; =0x0223F7BC
	ldr r3, [r3]
	bl MOD13_02217E20
	mvn r1, r5
	cmp r0, r1
	bne _02219340
	ldr r1, _0221942C ; =0x00001000
	ldr r0, [sp, #0x14]
	add r0, r0, r1
	bl MOD13_02218BF4
	mov r2, #0xf
	ldr r1, _02219414 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219340:
	ldr r0, [sp, #0x20]
	add r1, r5, #0
	ldr r2, _02219430 ; =0x000005F8
	bl MOD13_022174C0
	add r0, sp, #0x4c
	bl MOD13_022172E4
	ldr r0, _02219420 ; =0x0223F7BC
	ldr r0, [r0]
	add r1, sp, #0x4c
	bl MOD13_022172DC
	ldr r0, [sp, #0x24]
	str r0, [sp, #0x54]
	ldr r0, [sp, #0xc]
	str r0, [sp, #0x58]
	add r0, sp, #0x54
	str r0, [sp]
	ldr r0, _02219420 ; =0x0223F7BC
	ldr r0, [r0]
	add r0, r0, #1
	add r1, sp, #0x4c
	add r2, r5, #0
	add r3, r5, #0
	bl MOD13_02217458
	cmp r0, #0
	bgt _022193BA
	ldr r0, [sp, #0x3c]
	add r2, r0, #1
	str r2, [sp, #0x3c]
	add r1, sp, #0x30
	mov r0, #4
	ldrsh r0, [r1, r0]
	cmp r2, r0
	ble _022193B0
	ldr r0, [sp, #0x14]
	cmp r0, #0
	bne _02219398
	mov r0, #0xf
	bl MOD13_02218BF4
	b _022193AA
_02219398:
	cmp r0, #1
	bne _022193A4
	mov r0, #0x10
	bl MOD13_02218BF4
	b _022193AA
_022193A4:
	mov r0, #0x11
	bl MOD13_02218BF4
_022193AA:
	mov r0, #0
	mvn r4, r0
	b _022196C6
_022193B0:
	mov r0, #6
	ldrsh r0, [r1, r0]
	bl MOD13_022198E4
	b _0221901A
_022193BA:
	mov r0, #8
	str r0, [sp, #0x48]
	add r0, sp, #0x40
	str r0, [sp]
	add r0, sp, #0x48
	str r0, [sp, #4]
	ldr r0, _02219420 ; =0x0223F7BC
	ldr r0, [r0]
	ldr r1, [sp, #0x20]
	add r1, #0xc
	ldr r2, _02219434 ; =0x000005DC
	add r3, r5, #0
	bl MOD13_022174A4
	add r2, r0, #0
	ldr r0, _02219420 ; =0x0223F7BC
	ldr r1, [r0]
	ldr r0, [sp, #0x20]
	str r1, [r0]
	lsl r0, r2, #0x10
	lsr r0, r0, #0x10
	bl MOD13_02217380
	ldr r1, [sp, #0x20]
	str r0, [r1, #4]
	ldr r0, _02219420 ; =0x0223F7BC
	ldr r0, [r0]
	str r0, [sp]
	ldr r0, [sp, #0x14]
	add r2, sp, #0x3c
	add r3, sp, #0x64
	bl MOD13_022187B4
	str r0, [sp, #0x18]
	cmp r0, #0x64
	bne _02219406
	mov r4, #0
	b _022196C6
_02219406:
	mvn r1, r5
	cmp r0, r1
	bne _02219438
	mov r0, #0
	mvn r4, r0
	b _022196C6
	nop
_02219414: .word 0x00000116
_02219418: .word MOD13_02240B40
_0221941C: .word MOD13_02240B60
_02219420: .word MOD13_0223F7BC
_02219424: .word 0x0000FFFF
_02219428: .word 0x00005790
_0221942C: .word 0x00001000
_02219430: .word 0x000005F8
_02219434: .word 0x000005DC
_02219438:
	ldr r1, [sp, #0x14]
	cmp r1, r0
	bne _02219440
	b _02219688
_02219440:
	cmp r0, #2
	beq _02219446
	b _02219682
_02219446:
	ldr r0, _02219780 ; =0x0223F7BC
	ldr r0, [r0]
	mvn r1, r5
	cmp r0, r1
	beq _02219454
	bl MOD13_02217420
_02219454:
	ldr r1, [sp, #0x28]
	ldr r0, _02219780 ; =0x0223F7BC
	str r1, [r0]
	bl MOD13_02217504
	cmp r0, #0
	beq _0221947A
	mov r2, #0xf
	ldr r1, _02219784 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221947A:
	add r4, r5, #0
	mov r0, #4
	bl MOD13_02218870
_02219482:
	ldr r0, [r6]
	cmp r0, #0
	beq _0221948E
	bl MOD13_022198A0
	str r5, [r6]
_0221948E:
	add r0, r6, #0
	bl MOD13_02219AD0
	mvn r1, r5
	cmp r0, r1
	bne _022194B2
	mov r2, #0xf
	ldr r1, _02219784 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022194B2:
	ldr r0, [r6]
	bl MOD13_0221892C
	cmp r0, #4
	bne _022194D4
	mov r2, #2
	ldr r1, _02219784 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022194D4:
	cmp r0, #0
	beq _02219506
	add r0, sp, #0x30
	ldrsh r0, [r0, r5]
	cmp r4, r0
	blt _022194F8
	mov r2, #1
	ldr r1, _02219784 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022194F8:
	add r0, r7, #0
	bl MOD13_022198E4
	add r0, r4, #1
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	b _02219482
_02219506:
	mov r0, #0x58
	bl MOD13_022198B4
	ldr r1, _02219788 ; =0x02240B40
	str r0, [r1]
	cmp r0, #0
	bne _0221952C
	mov r2, #0xf
	ldr r1, _02219784 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221952C:
	add r1, r5, #0
	mov r2, #0x58
	bl MOD13_022174C0
	add r4, r5, #0
	add r0, sp, #0x30
	ldrsh r0, [r0, r5]
	cmp r0, #0
	ble _0221958C
_0221953E:
	add r0, sp, #0x7c
	ldr r1, _02219788 ; =0x02240B40
	ldr r1, [r1]
	bl MOD13_022198EC
	mvn r1, r5
	cmp r0, r1
	bne _02219566
	mov r2, #0xf
	ldr r1, _02219784 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219566:
	cmp r0, #0
	bne _02219578
	cmp r0, #0
	bne _0221958C
	ldr r0, _02219788 ; =0x02240B40
	ldr r0, [r0]
	ldr r0, [r0]
	cmp r0, #1
	beq _0221958C
_02219578:
	add r0, r7, #0
	bl MOD13_022198E4
	add r0, r4, #1
	lsl r0, r0, #0x10
	asr r4, r0, #0x10
	add r0, sp, #0x30
	ldrsh r0, [r0, r5]
	cmp r4, r0
	blt _0221953E
_0221958C:
	add r0, sp, #0x30
	ldrsh r0, [r0, r5]
	cmp r4, r0
	bne _022195AC
	mov r2, #0xf
	ldr r1, _02219784 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022195AC:
	ldr r0, [sp, #0x1c]
	ldr r1, _0221978C ; =0x02240B60
	ldr r1, [r1, #0x14]
	lsl r2, r0, #0
	bl MOD13_02217530
	cmp r0, #0
	beq _022195DA
	mov r0, #0xc
	bl MOD13_02218BF4
	mov r2, #0xf
	ldr r1, _02219784 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022195DA:
	bl MOD13_02218C54
	mov r0, #2
	lsl r1, r0, #0
	add r2, r5, #0
	bl MOD13_02217434
	ldr r1, _02219780 ; =0x0223F7BC
	str r0, [r1]
	cmp r0, #0
	bge _02219608
	mov r2, #0xf
	ldr r1, _02219784 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219608:
	mov r1, #4
	str r1, [sp]
	ldr r1, _02219790 ; =0x0000FFFF
	mov r2, #1
	add r3, sp, #0x38
	bl MOD13_0221743C
	cmp r0, #0
	bge _02219638
	mov r0, #0xb
	bl MOD13_02218BF4
	mov r2, #0xf
	ldr r1, _02219784 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219638:
	add r0, sp, #0x5c
	add r1, r5, #0
	mov r2, #8
	bl MOD13_022174C0
	mov r1, #2
	add r0, sp, #0x5c
	strb r1, [r0, #1]
	ldr r0, [sp, #0x1c]
	bl MOD13_022173E8
	str r0, [sp, #0x60]
	ldr r0, _02219794 ; =0x00005790
	bl MOD13_022173D0
	add r1, sp, #0x30
	strh r0, [r1, #0x2e]
	ldr r0, _02219780 ; =0x0223F7BC
	ldr r0, [r0]
	add r1, sp, #0x5c
	mov r2, #8
	bl MOD13_02217428
	cmp r0, #0
	bge _02219682
	mov r2, #0xf
	ldr r1, _02219784 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219682:
	ldr r0, [sp, #0x18]
	str r0, [sp, #0x14]
	b _02218FE8
_02219688:
	str r0, [sp, #0x14]
	ldr r2, [sp, #0x3c]
	add r1, sp, #0x30
	mov r0, #4
	ldrsh r0, [r1, r0]
	cmp r2, r0
	ble _022196BC
	ldr r0, [sp, #0x18]
	cmp r0, #0
	bne _022196A4
	mov r0, #0xf
	bl MOD13_02218BF4
	b _022196B6
_022196A4:
	cmp r0, #1
	bne _022196B0
	mov r0, #0x10
	bl MOD13_02218BF4
	b _022196B6
_022196B0:
	mov r0, #0x11
	bl MOD13_02218BF4
_022196B6:
	mov r0, #0
	mvn r4, r0
	b _022196C6
_022196BC:
	mov r0, #6
	ldrsh r0, [r1, r0]
	bl MOD13_022198E4
	b _02218FE8
_022196C6:
	ldr r0, _02219780 ; =0x0223F7BC
	ldr r0, [r0]
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _022196D6
	bl MOD13_02217420
_022196D6:
	mov r0, #0
	mvn r1, r0
	ldr r0, _02219780 ; =0x0223F7BC
	str r1, [r0]
	bl MOD13_02217504
	cmp r0, #0
	beq _022196FE
	mov r2, #0xf
	ldr r1, _02219784 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_022196FE:
	cmp r4, #0
	beq _02219754
	bl MOD13_02218BE8
	sub r0, #0xf
	cmp r0, #6
	bhi _0221973C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #8]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, pc
	bx r0
_0221971A: ; jump table
	.short _02219728 - _0221971A + 1 ; case 0
	.short _0221972C - _0221971A + 1 ; case 1
	.short _02219730 - _0221971A + 1 ; case 2
	.short _0221973C - _0221971A + 1 ; case 3
	.short _0221973C - _0221971A + 1 ; case 4
	.short _02219734 - _0221971A + 1 ; case 5
	.short _02219738 - _0221971A + 1 ; case 6
_02219728:
	mov r2, #3
	b _0221973E
_0221972C:
	mov r2, #4
	b _0221973E
_02219730:
	mov r2, #5
	b _0221973E
_02219734:
	mov r2, #7
	b _0221973E
_02219738:
	mov r2, #8
	b _0221973E
_0221973C:
	mov r2, #0xf
_0221973E:
	ldr r1, _02219784 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219754:
	ldr r0, [sp, #8]
	bl MOD13_022189D8
	cmp r0, #0
	beq _02219776
	mov r2, #6
	ldr r1, _02219784 ; =0x00000116
	ldr r0, [sp, #8]
	strb r2, [r0, r1]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219776:
	mov r0, #0
	add sp, #0xcc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_02219780: .word MOD13_0223F7BC
_02219784: .word 0x00000116
_02219788: .word MOD13_02240B40
_0221978C: .word MOD13_02240B60
_02219790: .word 0x0000FFFF
_02219794: .word 0x00005790

	thumb_func_start MOD13_02219798
MOD13_02219798: ; 0x02219798
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02219870 ; =0x00000106
	ldrsh r1, [r4, r0]
	cmp r1, #0
	beq _022197E6
	mov r0, #0
	mvn r2, r0
	cmp r1, r2
	blt _022197E6
	ldr r1, _02219874 ; =0x00000108
	ldrsh r1, [r4, r1]
	cmp r1, r2
	blt _022197E6
	ldr r1, _02219878 ; =0x0000010A
	ldrsh r1, [r4, r1]
	cmp r1, #0
	beq _022197E6
	cmp r1, r2
	blt _022197E6
	ldr r1, _0221987C ; =0x0000010C
	ldrsh r1, [r4, r1]
	cmp r1, r2
	blt _022197E6
	ldr r1, _02219880 ; =0x0000010E
	ldrsh r1, [r4, r1]
	cmp r1, r2
	blt _022197E6
	ldrh r2, [r4, #4]
	cmp r2, #0
	beq _022197E6
	ldr r1, _02219884 ; =0x00000100
	cmp r2, r1
	bhi _022197E6
	sub r1, r2, #1
	add r1, r4, r1
	ldrb r1, [r1, #6]
	cmp r1, #0
	beq _022197EA
_022197E6:
	mov r0, #0
	mvn r0, r0
_022197EA:
	ldr r1, _02219888 ; =0x02241900
	ldr r1, [r1]
	cmp r1, #0
	beq _022197FA
	ldr r1, _0221988C ; =0x0224190C
	ldr r1, [r1]
	cmp r1, #0
	bne _022197FE
_022197FA:
	mov r0, #0
	mvn r0, r0
_022197FE:
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	bne _0221981A
	mov r1, #0xf
	ldr r0, _02219890 ; =0x00000116
	strb r1, [r4, r0]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	pop {r4}
	pop {r3}
	bx r3
_0221981A:
	ldr r0, _02219894 ; =0x000005F8
	bl MOD13_022198B4
	ldr r1, _02219898 ; =0x02240B48
	str r0, [r1]
	cmp r0, #0
	bne _0221983C
	mov r1, #0xf
	ldr r0, _02219890 ; =0x00000116
	strb r1, [r4, r0]
	bl MOD13_02218C54
	mov r0, #0
	mvn r0, r0
	pop {r4}
	pop {r3}
	bx r3
_0221983C:
	mov r0, #0
	mvn r0, r0
	bl MOD13_02218870
	add r0, r4, #0
	bl MOD13_02218CAC
	add r4, r0, #0
	ldr r0, _02219898 ; =0x02240B48
	ldr r0, [r0]
	bl MOD13_022198A0
	bl MOD13_02218C54
	ldr r0, _0221989C ; =0x0223F7BC
	ldr r0, [r0]
	mov r1, #0
	mvn r1, r1
	cmp r0, r1
	beq _02219868
	bl MOD13_02217420
_02219868:
	add r0, r4, #0
	pop {r4}
	pop {r3}
	bx r3
	.align 2, 0
_02219870: .word 0x00000106
_02219874: .word 0x00000108
_02219878: .word 0x0000010A
_0221987C: .word 0x0000010C
_02219880: .word 0x0000010E
_02219884: .word 0x00000100
_02219888: .word MOD13_02241900
_0221988C: .word MOD13_0224190C
_02219890: .word 0x00000116
_02219894: .word 0x000005F8
_02219898: .word MOD13_02240B48
_0221989C: .word MOD13_0223F7BC

	thumb_func_start MOD13_022198A0
MOD13_022198A0: ; 0x022198A0
	push {lr}
	sub sp, #4
	ldr r1, _022198B0 ; =0x0224190C
	ldr r1, [r1]
	blx r1
	add sp, #4
	pop {r3}
	bx r3
	.align 2, 0
_022198B0: .word MOD13_0224190C

	thumb_func_start MOD13_022198B4
MOD13_022198B4: ; 0x022198B4
	push {lr}
	sub sp, #4
	ldr r1, _022198C4 ; =0x02241900
	ldr r1, [r1]
	blx r1
	add sp, #4
	pop {r3}
	bx r3
	.align 2, 0
_022198C4: .word MOD13_02241900

	thumb_func_start MOD13_022198C8
MOD13_022198C8: ; 0x022198C8
	push {lr}
	sub sp, #4
	ldr r1, _022198E0 ; =0x02241904
	ldr r1, [r1]
	cmp r1, #0
	beq _022198D6
	blx r1
_022198D6:
	mov r0, #0
	add sp, #4
	pop {r3}
	bx r3
	nop
_022198E0: .word MOD13_02241904

	thumb_func_start MOD13_022198E4
MOD13_022198E4: ; 0x022198E4
	ldr r3, _022198E8 ; =0x020CAFC0
	bx r3
	.align 2, 0
_022198E8: .word 0x020CAFC0

	thumb_func_start MOD13_022198EC
MOD13_022198EC: ; 0x022198EC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x4c
	str r0, [sp, #4]
	str r1, [sp, #8]
	mov r4, #1
	mov r0, #0
	str r0, [sp, #0x14]
	mvn r0, r0
	str r0, [sp, #0xc]
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x24]
	cmp r0, #0
	bne _0221990A
	ldr r6, _02219AA8 ; =0x00080000
	b _02219910
_0221990A:
	cmp r0, #1
	bne _02219910
	ldr r6, _02219AAC ; =0x000C0000
_02219910:
	ldr r0, _02219AB0 ; =0x02241940
	mov r1, #0
	mov r2, #0x60
	bl MI_CpuFill8
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x28]
	cmp r0, #5
	bne _0221992A
	mov r1, #1
	ldr r0, _02219AB0 ; =0x02241940
	strb r1, [r0]
	b _0221994E
_0221992A:
	cmp r0, #0xd
	bne _02219936
	mov r1, #2
	ldr r0, _02219AB0 ; =0x02241940
	strb r1, [r0]
	b _0221994E
_02219936:
	cmp r0, #0x10
	bne _02219942
	mov r1, #3
	ldr r0, _02219AB0 ; =0x02241940
	strb r1, [r0]
	b _0221994E
_02219942:
	mov r0, #0
	mvn r0, r0
	add sp, #0x4c
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221994E:
	mov r1, #0
	ldr r0, _02219AB0 ; =0x02241940
	strb r1, [r0, #1]
	ldr r0, [sp, #4]
	add r0, #0x2c
	ldr r1, _02219AB4 ; =0x02241942
	ldr r2, [sp, #4]
	ldr r2, [r2, #0x28]
	bl MI_CpuCopy8
	bl WCM_ClearApList
	mov r0, #0
	ldr r1, [sp, #4]
	add r1, r1, #4
	ldr r2, [sp, #4]
	ldr r2, [r2]
	ldr r3, _02219AB8 ; =0x0030BFFE
	bl MOD13_0221A1E8
	cmp r0, #0
	bne _0221997C
	b _02219A8A
_0221997C:
	mov r0, #0
	str r0, [sp, #0x10]
	add r0, sp, #0x1c
	bl OS_CreateAlarm
	mov r0, #0x12
	str r0, [sp]
	add r0, sp, #0x1c
	ldr r1, _02219ABC ; =0x003FEC42
	mov r2, #0
	ldr r3, _02219AC0 ; =MOD13_02219E48
	bl OS_SetAlarm
	ldr r0, _02219AC4 ; =0x00030000
	orr r6, r0
	ldr r7, _02219AC8 ; =0x022419A0
	mov r5, #0
_0221999E:
	ldr r0, _02219ACC ; =0x02241920
	add r1, sp, #0x18
	mov r2, #1
	bl OS_ReceiveMessage
	ldr r0, [sp, #0x18]
	cmp r0, #0x13
	bhi _02219A6A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #8]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, pc
	bx r0
_022199BC: ; jump table
	.short _02219A6A - _022199BC + 1 ; case 0
	.short _02219A6A - _022199BC + 1 ; case 1
	.short _02219A6A - _022199BC + 1 ; case 2
	.short _02219A6A - _022199BC + 1 ; case 3
	.short _02219A6C - _022199BC + 1 ; case 4
	.short _022199EE - _022199BC + 1 ; case 5
	.short _02219A6A - _022199BC + 1 ; case 6
	.short _02219A6A - _022199BC + 1 ; case 7
	.short _02219A6C - _022199BC + 1 ; case 8
	.short _02219A6A - _022199BC + 1 ; case 9
	.short _02219A2A - _022199BC + 1 ; case 10
	.short _02219A6A - _022199BC + 1 ; case 11
	.short _02219A44 - _022199BC + 1 ; case 12
	.short _02219A4A - _022199BC + 1 ; case 13
	.short _02219A6A - _022199BC + 1 ; case 14
	.short _02219A6A - _022199BC + 1 ; case 15
	.short _02219A6A - _022199BC + 1 ; case 16
	.short _02219A6A - _022199BC + 1 ; case 17
	.short _022199E4 - _022199BC + 1 ; case 18
	.short _02219A6C - _022199BC + 1 ; case 19
_022199E4:
	ldr r0, [sp, #0x14]
	cmp r0, #0
	bne _02219A6C
	add r4, r5, #0
	b _02219A6C
_022199EE:
	ldr r0, [sp, #0x14]
	cmp r0, #0
	bne _02219A6C
	add r0, sp, #0x1c
	bl OS_CancelAlarm
	add r0, r7, #0
	mov r1, #1
	bl MOD13_0221A2FC
	cmp r0, #1
	beq _02219A0A
	add r4, r5, #0
	b _02219A6C
_02219A0A:
	ldr r0, [sp, #4]
	add r1, r7, #0
	bl MOD13_02219E80
	add r0, r7, #0
	ldr r1, _02219AB0 ; =0x02241940
	add r2, r6, #0
	bl MOD13_0221A04C
	cmp r0, #0
	bne _02219A24
	add r4, r5, #0
	b _02219A6C
_02219A24:
	mov r0, #1
	str r0, [sp, #0x14]
	b _02219A6C
_02219A2A:
	ldr r0, [sp, #4]
	add r1, r7, #0
	bl MOD13_02219E80
	add r0, r7, #0
	ldr r1, _02219AB0 ; =0x02241940
	add r2, r6, #0
	bl MOD13_0221A04C
	cmp r0, #0
	bne _02219A6C
	add r4, r5, #0
	b _02219A6C
_02219A44:
	str r5, [sp, #0xc]
	add r4, r5, #0
	b _02219A6C
_02219A4A:
	ldr r0, [sp, #0x10]
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, #3
	bge _02219A66
	add r0, r7, #0
	ldr r1, _02219AB0 ; =0x02241940
	add r2, r6, #0
	bl MOD13_0221A04C
	cmp r0, #0
	bne _02219A6C
	add r4, r5, #0
	b _02219A6C
_02219A66:
	add r4, r5, #0
	b _02219A6C
_02219A6A:
	add r4, r5, #0
_02219A6C:
	cmp r4, #0
	bne _0221999E
	add r0, sp, #0x1c
	bl OS_CancelAlarm
	ldr r5, _02219ACC ; =0x02241920
	add r4, sp, #0x18
	mov r6, #0
_02219A7C:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl OS_ReceiveMessage
	cmp r0, #1
	beq _02219A7C
_02219A8A:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _02219A94
	mov r2, #1
	b _02219A96
_02219A94:
	mov r2, #0
_02219A96:
	ldr r0, [sp, #8]
	ldr r1, _02219AC8 ; =0x022419A0
	bl MOD13_02219E70
	ldr r0, [sp, #0xc]
	add sp, #0x4c
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_02219AA8: .word 0x00080000
_02219AAC: .word 0x000C0000
_02219AB0: .word MOD13_02241940
_02219AB4: .word MOD13_02241942
_02219AB8: .word 0x0030BFFE
_02219ABC: .word 0x003FEC42
_02219AC0: .word MOD13_02219E48
_02219AC4: .word 0x00030000
_02219AC8: .word MOD13_022419A0
_02219ACC: .word MOD13_02241920

	thumb_func_start MOD13_02219AD0
MOD13_02219AD0: ; 0x02219AD0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x44
	str r0, [sp, #4]
	mov r6, #0
	mvn r0, r6
	str r0, [sp, #8]
	mov r0, #1
	str r0, [sp, #0xc]
	add r7, r6, #0
	add r5, r6, #0
	ldr r0, _02219C44 ; =0x02241900
	ldr r1, [r0]
	cmp r1, #0
	beq _02219AF4
	ldr r0, _02219C48 ; =0x0224190C
	ldr r0, [r0]
	cmp r0, #0
	bne _02219B00
_02219AF4:
	mov r0, #0
	mvn r0, r0
	add sp, #0x44
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219B00:
	ldr r0, _02219C4C ; =0x00003000
	blx r1
	add r4, r0, #0
	cmp r4, #0
	bne _02219B16
	lsl r0, r6, #0
	mvn r0, r0
	add sp, #0x44
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219B16:
	str r4, [sp, #0x10]
	lsl r0, r6, #0
	add r1, r0, #0
	add r2, r0, #0
	ldr r3, _02219C50 ; =0x0030BFFE
	bl MOD13_0221A1E8
	cmp r0, #0
	bne _02219B2A
	b _02219C30
_02219B2A:
	add r0, sp, #0x18
	bl OS_CreateAlarm
	mov r0, #0x13
	str r0, [sp]
	add r0, sp, #0x18
	ldr r1, _02219C54 ; =0x003FEC42
	lsl r2, r6, #0
	ldr r3, _02219C58 ; =MOD13_02219E48
	bl OS_SetAlarm
_02219B40:
	ldr r0, _02219C5C ; =0x02241920
	add r1, sp, #0x14
	mov r2, #1
	bl OS_ReceiveMessage
	ldr r0, [sp, #0x14]
	cmp r0, #0x13
	bhi _02219C16
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #8]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, pc
	bx r0
_02219B5E: ; jump table
	.short _02219C16 - _02219B5E + 1 ; case 0
	.short _02219C16 - _02219B5E + 1 ; case 1
	.short _02219C16 - _02219B5E + 1 ; case 2
	.short _02219C16 - _02219B5E + 1 ; case 3
	.short _02219BCC - _02219B5E + 1 ; case 4
	.short _02219BA4 - _02219B5E + 1 ; case 5
	.short _02219C16 - _02219B5E + 1 ; case 6
	.short _02219C16 - _02219B5E + 1 ; case 7
	.short _02219BCC - _02219B5E + 1 ; case 8
	.short _02219C16 - _02219B5E + 1 ; case 9
	.short _02219BC6 - _02219B5E + 1 ; case 10
	.short _02219C16 - _02219B5E + 1 ; case 11
	.short _02219C16 - _02219B5E + 1 ; case 12
	.short _02219C16 - _02219B5E + 1 ; case 13
	.short _02219C16 - _02219B5E + 1 ; case 14
	.short _02219C16 - _02219B5E + 1 ; case 15
	.short _02219C16 - _02219B5E + 1 ; case 16
	.short _02219C16 - _02219B5E + 1 ; case 17
	.short _02219BCC - _02219B5E + 1 ; case 18
	.short _02219B86 - _02219B5E + 1 ; case 19
_02219B86:
	cmp r6, #0
	bne _02219BCC
	cmp r5, #0
	beq _02219B98
	add r0, r4, #0
	mov r1, #0x40
	bl MOD13_0221A2FC
	add r7, r0, #0
_02219B98:
	bl MOD13_0221A1A4
	cmp r0, #0
	beq _02219C16
	mov r6, #1
	b _02219BCC
_02219BA4:
	cmp r6, #0
	bne _02219BCC
	cmp r5, #8
	bge _02219BB0
	add r5, r5, #1
	b _02219BCC
_02219BB0:
	add r0, r4, #0
	mov r1, #0x40
	bl MOD13_0221A2FC
	add r7, r0, #0
	bl MOD13_0221A1A4
	cmp r0, #0
	beq _02219C16
	mov r6, #1
	b _02219BCC
_02219BC6:
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #8]
_02219BCC:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _02219B40
	cmp r7, #0
	beq _02219BEA
	sub r0, r7, #1
	mov r1, #0x54
	mul r0, r1
	add r0, #0x58
	ldr r1, _02219C44 ; =0x02241900
	ldr r1, [r1]
	blx r1
	cmp r0, #0
	bne _02219BF6
	b _02219C16
_02219BEA:
	mov r0, #0x58
	ldr r1, _02219C44 ; =0x02241900
	ldr r1, [r1]
	blx r1
	cmp r0, #0
	beq _02219C16
_02219BF6:
	ldr r1, [sp, #4]
	str r0, [r1]
	str r7, [r0]
	mov r6, #0
	cmp r7, #0
	ble _02219C16
	add r5, r0, #4
_02219C04:
	add r0, r4, #0
	add r1, r5, #0
	bl MOD13_02219EB4
	add r4, #0xc0
	add r5, #0x54
	add r6, r6, #1
	cmp r6, r7
	blt _02219C04
_02219C16:
	add r0, sp, #0x18
	bl OS_CancelAlarm
	ldr r5, _02219C5C ; =0x02241920
	add r4, sp, #0x14
	mov r6, #0
_02219C22:
	add r0, r5, #0
	add r1, r4, #0
	add r2, r6, #0
	bl OS_ReceiveMessage
	cmp r0, #1
	beq _02219C22
_02219C30:
	ldr r0, [sp, #0x10]
	ldr r1, _02219C48 ; =0x0224190C
	ldr r1, [r1]
	blx r1
	ldr r0, [sp, #8]
	add sp, #0x44
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_02219C44: .word MOD13_02241900
_02219C48: .word MOD13_0224190C
_02219C4C: .word 0x00003000
_02219C50: .word 0x0030BFFE
_02219C54: .word 0x003FEC42
_02219C58: .word MOD13_02219E48
_02219C5C: .word MOD13_02241920

	thumb_func_start MOD13_02219C60
MOD13_02219C60: ; 0x02219C60
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	mov r0, #0
	mvn r4, r0
	bl MOD13_0221A164
	cmp r0, #0
	beq _02219C8C
	mov r5, #0
	ldr r6, _02219C98 ; =0x02241920
	add r7, sp, #0
_02219C76:
	add r0, r6, #0
	add r1, r7, #0
	mov r2, #1
	bl OS_ReceiveMessage
	ldr r0, [sp]
	cmp r0, #0xe
	bne _02219C88
	add r4, r5, #0
_02219C88:
	cmp r5, #0
	bne _02219C76
_02219C8C:
	add r0, r4, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_02219C98: .word MOD13_02241920

	thumb_func_start MOD13_02219C9C
MOD13_02219C9C: ; 0x02219C9C
	push {r4, r5, lr}
	sub sp, #4
	mov r4, #1
	mov r0, #0
	mvn r5, r0
	ldr r0, _02219D48 ; =0x0224190C
	ldr r0, [r0]
	cmp r0, #0
	bne _02219CB8
	add r0, r5, #0
	add sp, #4
	pop {r4, r5}
	pop {r3}
	bx r3
_02219CB8:
	bl MOD13_0221A0FC
	cmp r0, #0
	bne _02219CCC
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5}
	pop {r3}
	bx r3
_02219CCC:
	ldr r0, _02219D4C ; =0x02241920
	add r1, sp, #0
	mov r2, #1
	bl OS_ReceiveMessage
	ldr r0, [sp]
	cmp r0, #0x14
	bhi _02219D24
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #8]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, pc
	bx r0
_02219CEA: ; jump table
	.short _02219D24 - _02219CEA + 1 ; case 0
	.short _02219D24 - _02219CEA + 1 ; case 1
	.short _02219D24 - _02219CEA + 1 ; case 2
	.short _02219D24 - _02219CEA + 1 ; case 3
	.short _02219D26 - _02219CEA + 1 ; case 4
	.short _02219D26 - _02219CEA + 1 ; case 5
	.short _02219D24 - _02219CEA + 1 ; case 6
	.short _02219D24 - _02219CEA + 1 ; case 7
	.short _02219D24 - _02219CEA + 1 ; case 8
	.short _02219D24 - _02219CEA + 1 ; case 9
	.short _02219D24 - _02219CEA + 1 ; case 10
	.short _02219D24 - _02219CEA + 1 ; case 11
	.short _02219D24 - _02219CEA + 1 ; case 12
	.short _02219D24 - _02219CEA + 1 ; case 13
	.short _02219D24 - _02219CEA + 1 ; case 14
	.short _02219D24 - _02219CEA + 1 ; case 15
	.short _02219D24 - _02219CEA + 1 ; case 16
	.short _02219D24 - _02219CEA + 1 ; case 17
	.short _02219D24 - _02219CEA + 1 ; case 18
	.short _02219D24 - _02219CEA + 1 ; case 19
	.short _02219D14 - _02219CEA + 1 ; case 20
_02219D14:
	mov r4, #0
	add r5, r4, #0
	ldr r0, _02219D50 ; =0x02241908
	ldr r0, [r0]
	ldr r1, _02219D48 ; =0x0224190C
	ldr r1, [r1]
	blx r1
	b _02219D26
_02219D24:
	mov r4, #0
_02219D26:
	cmp r4, #0
	bne _02219CCC
	bl OS_DisableInterrupts
	mov r2, #0
	ldr r1, _02219D54 ; =0x02241900
	str r2, [r1]
	ldr r1, _02219D48 ; =0x0224190C
	str r2, [r1]
	bl OS_RestoreInterrupts
	add r0, r5, #0
	add sp, #4
	pop {r4, r5}
	pop {r3}
	bx r3
	nop
_02219D48: .word MOD13_0224190C
_02219D4C: .word MOD13_02241920
_02219D50: .word MOD13_02241908
_02219D54: .word MOD13_02241900

	thumb_func_start MOD13_02219D58
MOD13_02219D58: ; 0x02219D58
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r5, r0, #0
	add r6, r1, #0
	mov r4, #1
	ldr r0, _02219E2C ; =0x02241920
	ldr r1, _02219E30 ; =0x02241910
	mov r2, #4
	bl OS_InitMessageQueue
	cmp r5, #0
	beq _02219D74
	cmp r6, #0
	bne _02219D80
_02219D74:
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219D80:
	bl OS_DisableInterrupts
	ldr r1, _02219E34 ; =0x02241900
	str r5, [r1]
	ldr r1, _02219E38 ; =0x0224190C
	str r6, [r1]
	bl OS_RestoreInterrupts
	ldr r0, _02219E3C ; =0x00005890
	ldr r1, _02219E34 ; =0x02241900
	ldr r1, [r1]
	blx r1
	add r1, r0, #0
	ldr r0, _02219E40 ; =0x02241908
	str r1, [r0]
	cmp r1, #0
	bne _02219DAE
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219DAE:
	ldr r0, _02219E44 ; =MOD13_02219E5C
	ldr r2, _02219E3C ; =0x00005890
	bl MOD13_02219F54
	cmp r0, #0
	bne _02219DBC
	mov r4, #0
_02219DBC:
	cmp r4, #0
	beq _02219E14
	ldr r5, _02219E2C ; =0x02241920
	add r6, sp, #0
	mov r7, #1
_02219DC6:
	add r0, r5, #0
	add r1, r6, #0
	add r2, r7, #0
	bl OS_ReceiveMessage
	ldr r0, [sp]
	cmp r0, #0xf
	bhi _02219E0E
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #8]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, pc
	bx r0
_02219DE4: ; jump table
	.short _02219E0E - _02219DE4 + 1 ; case 0
	.short _02219E0E - _02219DE4 + 1 ; case 1
	.short _02219E0E - _02219DE4 + 1 ; case 2
	.short _02219E0E - _02219DE4 + 1 ; case 3
	.short _02219E10 - _02219DE4 + 1 ; case 4
	.short _02219E10 - _02219DE4 + 1 ; case 5
	.short _02219E04 - _02219DE4 + 1 ; case 6
	.short _02219E0E - _02219DE4 + 1 ; case 7
	.short _02219E0E - _02219DE4 + 1 ; case 8
	.short _02219E0E - _02219DE4 + 1 ; case 9
	.short _02219E0E - _02219DE4 + 1 ; case 10
	.short _02219E0E - _02219DE4 + 1 ; case 11
	.short _02219E0E - _02219DE4 + 1 ; case 12
	.short _02219E0E - _02219DE4 + 1 ; case 13
	.short _02219E0E - _02219DE4 + 1 ; case 14
	.short _02219E0E - _02219DE4 + 1 ; case 15
_02219E04:
	mov r0, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219E0E:
	mov r4, #0
_02219E10:
	cmp r4, #0
	bne _02219DC6
_02219E14:
	ldr r0, _02219E40 ; =0x02241908
	ldr r0, [r0]
	ldr r1, _02219E38 ; =0x0224190C
	ldr r1, [r1]
	blx r1
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_02219E2C: .word MOD13_02241920
_02219E30: .word MOD13_02241910
_02219E34: .word MOD13_02241900
_02219E38: .word MOD13_0224190C
_02219E3C: .word 0x00005890
_02219E40: .word MOD13_02241908
_02219E44: .word MOD13_02219E5C

	thumb_func_start MOD13_02219E48
MOD13_02219E48: ; 0x02219E48
	add r1, r0, #0
	ldr r0, _02219E54 ; =0x02241920
	mov r2, #0
	ldr r3, _02219E58 ; =0x020CBDC4
	bx r3
	nop
_02219E54: .word MOD13_02241920
_02219E58: .word 0x020CBDC4

	thumb_func_start MOD13_02219E5C
MOD13_02219E5C: ; 0x02219E5C
	add r1, r0, #0
	ldr r0, _02219E68 ; =0x02241920
	mov r2, #0
	ldr r3, _02219E6C ; =0x020CBDC4
	bx r3
	nop
_02219E68: .word MOD13_02241920
_02219E6C: .word 0x020CBDC4

	thumb_func_start MOD13_02219E70
MOD13_02219E70: ; 0x02219E70
	add r3, r0, #0
	str r2, [r3]
	add r0, r1, #0
	add r1, r3, #4
	ldr r3, _02219E7C ; =MOD13_02219EB4
	bx r3
	.align 2, 0
_02219E7C: .word MOD13_02219EB4

	thumb_func_start MOD13_02219E80
MOD13_02219E80: ; 0x02219E80
	push {r4, r5, lr}
	sub sp, #4
	add r5, r0, #0
	add r4, r1, #0
	mov r1, #0
	add r0, sp, #0
	strh r1, [r0]
	ldrh r0, [r0]
	add r1, r4, #0
	add r1, #0xc
	mov r2, #0x20
	bl MIi_CpuClear16
	ldr r0, [r5]
	strh r0, [r4, #0xa]
	add r0, r5, #4
	add r1, r4, #0
	add r1, #0xc
	ldrh r2, [r4, #0xa]
	bl MI_CpuCopy8
	add sp, #4
	pop {r4, r5}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_02219EB4
MOD13_02219EB4: ; 0x02219EB4
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r5, r0, #0
	add r4, r1, #0
	ldrh r0, [r5, #0xa]
	str r0, [r4]
	add r0, r5, #0
	add r0, #0xc
	add r1, r4, #4
	mov r2, #0x20
	bl MIi_CpuCopy16
	ldrh r0, [r5, #0x36]
	str r0, [r4, #0x24]
	add r0, r5, #4
	add r1, r4, #0
	add r1, #0x30
	mov r2, #6
	bl MIi_CpuCopy16
	mov r2, #0
	add r3, r2, #0
	ldr r1, _02219F50 ; =0x0223F834
_02219EE2:
	ldrh r6, [r5, #0x30]
	ldrh r0, [r1]
	and r6, r0
	cmp r6, #0
	beq _02219F10
	add r0, r4, r2
	ldrb r7, [r1, #2]
	add r6, r0, #0
	add r6, #0x3c
	strb r7, [r6]
	ldrh r7, [r5, #0x2e]
	ldrh r6, [r1]
	and r7, r6
	cmp r7, #0
	beq _02219F0E
	add r6, r0, #0
	add r6, #0x3c
	ldrb r7, [r6]
	mov r6, #0x80
	orr r7, r6
	add r0, #0x3c
	strb r7, [r0]
_02219F0E:
	add r2, r2, #1
_02219F10:
	add r1, r1, #4
	add r3, r3, #1
	cmp r3, #0xc
	blt _02219EE2
	str r2, [r4, #0x38]
	ldrh r0, [r5, #0x32]
	str r0, [r4, #0x4c]
	ldrh r1, [r5, #0x2c]
	mov r0, #3
	and r1, r0
	cmp r1, #1
	bne _02219F34
	mov r0, #1
	str r0, [r4, #0x50]
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219F34:
	cmp r1, #2
	bne _02219F44
	mov r0, #2
	str r0, [r4, #0x50]
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219F44:
	mov r0, #0
	str r0, [r4, #0x50]
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_02219F50: .word MOD13_0223F834

	thumb_func_start MOD13_02219F54
MOD13_02219F54: ; 0x02219F54
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r6, r0, #0
	add r5, r1, #0
	add r7, r2, #0
	bl OS_DisableInterrupts
	add r4, r0, #0
	ldr r0, _0221A028 ; =0x02241A84
	str r5, [r0]
	add r2, r5, #0
	add r2, #0x53
	mov r0, #3
	bic r2, r0
	ldr r0, _0221A02C ; =0x02241A68
	str r2, [r0]
	add r1, r2, #0
	add r1, #0x2f
	mov r3, #0x1f
	bic r1, r3
	ldr r3, _0221A030 ; =0x02241A60
	str r1, [r3]
	ldr r3, _0221A034 ; =0x0000231F
	add r1, r1, r3
	mov r3, #0x1f
	bic r1, r3
	ldr r3, _0221A038 ; =0x02241A80
	str r1, [r3]
	add r1, #0xdf
	mov r3, #0x1f
	bic r1, r3
	str r1, [r2, #4]
	ldr r1, [r0]
	add r3, r5, r7
	ldr r2, [r1, #4]
	sub r2, r3, r2
	str r2, [r1, #8]
	mov r2, #0
	ldr r1, [r0]
	str r2, [r1, #0xc]
	ldr r1, [r0]
	mov r0, #3
	str r0, [r1]
	ldr r0, _0221A03C ; =0x02241A7C
	str r6, [r0]
	ldr r0, _0221A040 ; =0x02241A78
	ldr r0, [r0]
	cmp r0, #0
	bne _02219FDA
	ldr r0, _0221A030 ; =0x02241A60
	ldr r0, [r0]
	ldr r1, _0221A044 ; =0x00002300
	bl WCM_Init
	cmp r0, #0
	beq _02219FD4
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_02219FD4:
	mov r1, #1
	ldr r0, _0221A040 ; =0x02241A78
	str r1, [r0]
_02219FDA:
	ldr r0, _0221A040 ; =0x02241A78
	ldr r0, [r0]
	cmp r0, #1
	bne _0221A016
	ldr r0, _0221A02C ; =0x02241A68
	ldr r0, [r0]
	ldr r1, _0221A048 ; =MOD13_0221A3CC
	bl WCM_StartupAsync
	cmp r0, #3
	beq _0221A000
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221A000:
	mov r1, #4
	ldr r0, _0221A040 ; =0x02241A78
	str r1, [r0]
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221A016:
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_0221A028: .word MOD13_02241A84
_0221A02C: .word MOD13_02241A68
_0221A030: .word MOD13_02241A60
_0221A034: .word 0x0000231F
_0221A038: .word MOD13_02241A80
_0221A03C: .word MOD13_02241A7C
_0221A040: .word MOD13_02241A78
_0221A044: .word 0x00002300
_0221A048: .word MOD13_0221A3CC

	thumb_func_start MOD13_0221A04C
MOD13_0221A04C: ; 0x0221A04C
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r7, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl OS_DisableInterrupts
	add r4, r0, #0
	ldr r0, _0221A0EC ; =0x02241A6C
	str r6, [r0]
	cmp r5, #0
	beq _0221A072
	add r0, r5, #0
	ldr r1, _0221A0F0 ; =0x02241A84
	ldr r1, [r1]
	mov r2, #0x50
	bl MI_CpuCopy8
	b _0221A07E
_0221A072:
	ldr r0, _0221A0F0 ; =0x02241A84
	ldr r0, [r0]
	mov r1, #0
	mov r2, #0x50
	bl MI_CpuFill8
_0221A07E:
	add r0, r7, #0
	ldr r1, _0221A0F4 ; =0x02241A80
	ldr r1, [r1]
	mov r2, #0xc0
	bl MIi_CpuCopy32
	bl MOD13_0221A348
	cmp r0, #1
	bne _0221A0A8
	mov r1, #8
	ldr r0, _0221A0F8 ; =0x02241A78
	str r1, [r0]
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221A0A8:
	ldr r0, _0221A0F8 ; =0x02241A78
	ldr r0, [r0]
	cmp r0, #3
	bne _0221A0DA
	ldr r0, _0221A0F4 ; =0x02241A80
	ldr r0, [r0]
	ldr r1, _0221A0F0 ; =0x02241A84
	ldr r1, [r1]
	ldr r2, _0221A0EC ; =0x02241A6C
	ldr r2, [r2]
	bl WCM_ConnectAsync
	cmp r0, #3
	bne _0221A0DA
	mov r1, #8
	ldr r0, _0221A0F8 ; =0x02241A78
	str r1, [r0]
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221A0DA:
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_0221A0EC: .word MOD13_02241A6C
_0221A0F0: .word MOD13_02241A84
_0221A0F4: .word MOD13_02241A80
_0221A0F8: .word MOD13_02241A78

	thumb_func_start MOD13_0221A0FC
MOD13_0221A0FC: ; 0x0221A0FC
	push {r4, lr}
	bl OS_DisableInterrupts
	add r4, r0, #0
	ldr r0, _0221A160 ; =0x02241A78
	ldr r0, [r0]
	cmp r0, #3
	bne _0221A136
	bl WCM_CleanupAsync
	cmp r0, #3
	beq _0221A122
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	pop {r4}
	pop {r3}
	bx r3
_0221A122:
	mov r1, #2
	ldr r0, _0221A160 ; =0x02241A78
	str r1, [r0]
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	pop {r4}
	pop {r3}
	bx r3
_0221A136:
	bl MOD13_0221A348
	cmp r0, #1
	bne _0221A152
	mov r1, #2
	ldr r0, _0221A160 ; =0x02241A78
	str r1, [r0]
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	pop {r4}
	pop {r3}
	bx r3
_0221A152:
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	pop {r4}
	pop {r3}
	bx r3
	.align 2, 0
_0221A160: .word MOD13_02241A78

	thumb_func_start MOD13_0221A164
MOD13_0221A164: ; 0x0221A164
	push {r4, lr}
	bl OS_DisableInterrupts
	add r4, r0, #0
	ldr r0, _0221A1A0 ; =0x02241A78
	ldr r0, [r0]
	cmp r0, #7
	bne _0221A190
	bl WCM_DisconnectAsync
	cmp r0, #3
	bne _0221A190
	mov r1, #4
	ldr r0, _0221A1A0 ; =0x02241A78
	str r1, [r0]
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	pop {r4}
	pop {r3}
	bx r3
_0221A190:
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	pop {r4}
	pop {r3}
	bx r3
	nop
_0221A1A0: .word MOD13_02241A78

	thumb_func_start MOD13_0221A1A4
MOD13_0221A1A4: ; 0x0221A1A4
	push {r4, lr}
	bl OS_DisableInterrupts
	add r4, r0, #0
	ldr r0, _0221A1E4 ; =0x02241A78
	ldr r0, [r0]
	cmp r0, #5
	bne _0221A1D6
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	bl WCM_SearchAsync
	cmp r0, #3
	bne _0221A1D6
	mov r1, #4
	ldr r0, _0221A1E4 ; =0x02241A78
	str r1, [r0]
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	pop {r4}
	pop {r3}
	bx r3
_0221A1D6:
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	pop {r4}
	pop {r3}
	bx r3
	.align 2, 0
_0221A1E4: .word MOD13_02241A78

	thumb_func_start MOD13_0221A1E8
MOD13_0221A1E8: ; 0x0221A1E8
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	str r3, [sp]
	bl OS_DisableInterrupts
	add r7, r0, #0
	ldr r1, _0221A2DC ; =0x02241A64
	ldr r0, [sp]
	str r0, [r1]
	cmp r5, #0
	beq _0221A21E
	mov r2, #0
	ldr r1, _0221A2E0 ; =0x02241A88
_0221A208:
	ldrb r0, [r5]
	add r5, r5, #1
	strb r0, [r1]
	add r1, r1, #1
	add r2, r2, #1
	cmp r2, #6
	blt _0221A208
	ldr r1, _0221A2E0 ; =0x02241A88
	ldr r0, _0221A2E4 ; =0x02241A70
	str r1, [r0]
	b _0221A22E
_0221A21E:
	ldr r0, _0221A2E0 ; =0x02241A88
	mov r1, #0xff
	mov r2, #6
	bl MI_CpuFill8
	ldr r1, _0221A2E8 ; =0x020FF590
	ldr r0, _0221A2E4 ; =0x02241A70
	str r1, [r0]
_0221A22E:
	cmp r4, #0
	beq _0221A26C
	cmp r6, #0
	ble _0221A26C
	cmp r6, #0x20
	bgt _0221A26C
	mov r1, #0
	cmp r6, #0
	ble _0221A250
	ldr r2, _0221A2EC ; =0x02241A90
_0221A242:
	ldrb r0, [r4]
	add r4, r4, #1
	strb r0, [r2]
	add r2, r2, #1
	add r1, r1, #1
	cmp r1, r6
	blt _0221A242
_0221A250:
	cmp r1, #0x20
	bge _0221A264
	ldr r0, _0221A2EC ; =0x02241A90
	add r2, r0, r1
	mov r0, #0
_0221A25A:
	strb r0, [r2]
	add r2, r2, #1
	add r1, r1, #1
	cmp r1, #0x20
	blt _0221A25A
_0221A264:
	ldr r1, _0221A2EC ; =0x02241A90
	ldr r0, _0221A2F0 ; =0x02241A74
	str r1, [r0]
	b _0221A27C
_0221A26C:
	ldr r0, _0221A2EC ; =0x02241A90
	mov r1, #0xff
	mov r2, #0x20
	bl MI_CpuFill8
	ldr r1, _0221A2F4 ; =0x020FF598
	ldr r0, _0221A2F0 ; =0x02241A74
	str r1, [r0]
_0221A27C:
	ldr r0, _0221A2F8 ; =0x02241A78
	ldr r0, [r0]
	cmp r0, #3
	bne _0221A2AE
	ldr r0, _0221A2E4 ; =0x02241A70
	ldr r0, [r0]
	ldr r1, _0221A2F0 ; =0x02241A74
	ldr r1, [r1]
	ldr r2, _0221A2DC ; =0x02241A64
	ldr r2, [r2]
	bl WCM_SearchAsync
	cmp r0, #3
	bne _0221A2CC
	mov r1, #6
	ldr r0, _0221A2F8 ; =0x02241A78
	str r1, [r0]
	add r0, r7, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221A2AE:
	bl MOD13_0221A348
	cmp r0, #1
	bne _0221A2CC
	mov r1, #6
	ldr r0, _0221A2F8 ; =0x02241A78
	str r1, [r0]
	add r0, r7, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221A2CC:
	add r0, r7, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_0221A2DC: .word MOD13_02241A64
_0221A2E0: .word MOD13_02241A88
_0221A2E4: .word MOD13_02241A70
_0221A2E8: .word 0x020FF590
_0221A2EC: .word MOD13_02241A90
_0221A2F0: .word MOD13_02241A74
_0221A2F4: .word 0x020FF598
_0221A2F8: .word MOD13_02241A78

	thumb_func_start MOD13_0221A2FC
MOD13_0221A2FC: ; 0x0221A2FC
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r5, r0, #0
	add r7, r1, #0
	mov r0, #1
	bl WCM_LockApList
	bl WCM_CountApList
	add r6, r0, #0
	cmp r6, #0
	ble _0221A336
	mov r4, #0
	cmp r6, #0
	ble _0221A336
_0221A31A:
	cmp r4, r7
	bge _0221A336
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl WCM_PointApList
	add r1, r5, #0
	mov r2, #0xc0
	bl MIi_CpuCopy32
	add r4, r4, #1
	add r5, #0xc0
	cmp r4, r6
	blt _0221A31A
_0221A336:
	mov r0, #0
	bl WCM_LockApList
	add r0, r6, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_0221A348
MOD13_0221A348: ; 0x0221A348
	push {lr}
	sub sp, #4
	ldr r0, _0221A3C0 ; =0x02241A78
	ldr r0, [r0]
	cmp r0, #8
	bhi _0221A3B0
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #8]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, pc
	bx r0
_0221A362: ; jump table
	.short _0221A3B0 - _0221A362 + 1 ; case 0
	.short _0221A39A - _0221A362 + 1 ; case 1
	.short _0221A3B0 - _0221A362 + 1 ; case 2
	.short _0221A3B0 - _0221A362 + 1 ; case 3
	.short _0221A3B0 - _0221A362 + 1 ; case 4
	.short _0221A374 - _0221A362 + 1 ; case 5
	.short _0221A3B0 - _0221A362 + 1 ; case 6
	.short _0221A38A - _0221A362 + 1 ; case 7
	.short _0221A3B0 - _0221A362 + 1 ; case 8
_0221A374:
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	bl WCM_SearchAsync
	cmp r0, #3
	beq _0221A3B8
	mov r0, #0
	add sp, #4
	pop {r3}
	bx r3
_0221A38A:
	bl WCM_DisconnectAsync
	cmp r0, #3
	beq _0221A3B8
	mov r0, #0
	add sp, #4
	pop {r3}
	bx r3
_0221A39A:
	ldr r0, _0221A3C4 ; =0x02241A68
	ldr r0, [r0]
	ldr r1, _0221A3C8 ; =MOD13_0221A3CC
	bl WCM_StartupAsync
	cmp r0, #3
	beq _0221A3B8
	mov r0, #0
	add sp, #4
	pop {r3}
	bx r3
_0221A3B0:
	mov r0, #0
	add sp, #4
	pop {r3}
	bx r3
_0221A3B8:
	mov r0, #1
	add sp, #4
	pop {r3}
	bx r3
	.align 2, 0
_0221A3C0: .word MOD13_02241A78
_0221A3C4: .word MOD13_02241A68
_0221A3C8: .word MOD13_0221A3CC

	thumb_func_start MOD13_0221A3CC
MOD13_0221A3CC: ; 0x0221A3CC
	push {lr}
	sub sp, #4
	cmp r0, #0
	bne _0221A3D6
	b _0221A750
_0221A3D6:
	mov r1, #0
	ldrsh r2, [r0, r1]
	cmp r2, #7
	bls _0221A3E0
	b _0221A742
_0221A3E0:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #8]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add r2, pc
	bx r2
_0221A3EE: ; jump table
	.short _0221A742 - _0221A3EE + 1 ; case 0
	.short _0221A3FE - _0221A3EE + 1 ; case 1
	.short _0221A6E4 - _0221A3EE + 1 ; case 2
	.short _0221A4AE - _0221A3EE + 1 ; case 3
	.short _0221A536 - _0221A3EE + 1 ; case 4
	.short _0221A4F2 - _0221A3EE + 1 ; case 5
	.short _0221A610 - _0221A3EE + 1 ; case 6
	.short _0221A728 - _0221A3EE + 1 ; case 7
_0221A3FE:
	mov r2, #2
	ldrsh r0, [r0, r2]
	cmp r0, #0
	bne _0221A494
	ldr r0, _0221A758 ; =0x02241A78
	ldr r2, [r0]
	cmp r2, #4
	bne _0221A426
	mov r2, #3
	str r2, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	bne _0221A41C
	b _0221A750
_0221A41C:
	mov r0, #6
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A426:
	cmp r2, #6
	bne _0221A45C
	ldr r0, _0221A760 ; =0x02241A70
	ldr r0, [r0]
	ldr r1, _0221A764 ; =0x02241A74
	ldr r1, [r1]
	ldr r2, _0221A768 ; =0x02241A64
	ldr r2, [r2]
	bl WCM_SearchAsync
	cmp r0, #3
	bne _0221A440
	b _0221A750
_0221A440:
	mov r1, #3
	ldr r0, _0221A758 ; =0x02241A78
	str r1, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	bne _0221A450
	b _0221A750
_0221A450:
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A45C:
	cmp r2, #8
	beq _0221A462
	b _0221A750
_0221A462:
	ldr r0, _0221A76C ; =0x02241A80
	ldr r0, [r0]
	ldr r1, _0221A770 ; =0x02241A84
	ldr r1, [r1]
	ldr r2, _0221A774 ; =0x02241A6C
	ldr r2, [r2]
	bl WCM_ConnectAsync
	cmp r0, #3
	bne _0221A478
	b _0221A750
_0221A478:
	mov r1, #3
	ldr r0, _0221A758 ; =0x02241A78
	str r1, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	bne _0221A488
	b _0221A750
_0221A488:
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A494:
	mov r3, #1
	ldr r0, _0221A758 ; =0x02241A78
	str r3, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r3, [r0]
	cmp r3, #0
	bne _0221A4A4
	b _0221A750
_0221A4A4:
	add r0, r2, #0
	blx r3
	add sp, #4
	pop {r3}
	bx r3
_0221A4AE:
	mov r2, #2
	ldrsh r0, [r0, r2]
	cmp r0, #0
	bne _0221A4D8
	ldr r0, _0221A758 ; =0x02241A78
	ldr r2, [r0]
	cmp r2, #6
	beq _0221A4C0
	b _0221A750
_0221A4C0:
	mov r2, #5
	str r2, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	bne _0221A4CE
	b _0221A750
_0221A4CE:
	mov r0, #8
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A4D8:
	mov r2, #3
	ldr r0, _0221A758 ; =0x02241A78
	str r2, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	bne _0221A4E8
	b _0221A750
_0221A4E8:
	mov r0, #9
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A4F2:
	mov r2, #2
	ldrsh r0, [r0, r2]
	cmp r0, #0
	bne _0221A51C
	ldr r0, _0221A758 ; =0x02241A78
	ldr r2, [r0]
	cmp r2, #8
	beq _0221A504
	b _0221A750
_0221A504:
	mov r2, #7
	str r2, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	bne _0221A512
	b _0221A750
_0221A512:
	mov r0, #0xc
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A51C:
	mov r2, #3
	ldr r0, _0221A758 ; =0x02241A78
	str r2, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	bne _0221A52C
	b _0221A750
_0221A52C:
	mov r0, #0xd
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A536:
	mov r2, #2
	ldrsh r0, [r0, r2]
	cmp r0, #0
	bne _0221A5F6
	ldr r0, _0221A758 ; =0x02241A78
	ldr r2, [r0]
	cmp r2, #4
	bne _0221A55E
	mov r2, #3
	str r2, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	bne _0221A554
	b _0221A750
_0221A554:
	mov r0, #0xa
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A55E:
	cmp r2, #6
	bne _0221A594
	ldr r0, _0221A760 ; =0x02241A70
	ldr r0, [r0]
	ldr r1, _0221A764 ; =0x02241A74
	ldr r1, [r1]
	ldr r2, _0221A768 ; =0x02241A64
	ldr r2, [r2]
	bl WCM_SearchAsync
	cmp r0, #3
	bne _0221A578
	b _0221A750
_0221A578:
	mov r1, #3
	ldr r0, _0221A758 ; =0x02241A78
	str r1, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	bne _0221A588
	b _0221A750
_0221A588:
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A594:
	cmp r2, #2
	bne _0221A5BE
	bl WCM_CleanupAsync
	cmp r0, #3
	bne _0221A5A2
	b _0221A750
_0221A5A2:
	mov r1, #3
	ldr r0, _0221A758 ; =0x02241A78
	str r1, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	bne _0221A5B2
	b _0221A750
_0221A5B2:
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A5BE:
	cmp r2, #8
	beq _0221A5C4
	b _0221A750
_0221A5C4:
	ldr r0, _0221A76C ; =0x02241A80
	ldr r0, [r0]
	ldr r1, _0221A770 ; =0x02241A84
	ldr r1, [r1]
	ldr r2, _0221A774 ; =0x02241A6C
	ldr r2, [r2]
	bl WCM_ConnectAsync
	cmp r0, #3
	bne _0221A5DA
	b _0221A750
_0221A5DA:
	mov r1, #3
	ldr r0, _0221A758 ; =0x02241A78
	str r1, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	bne _0221A5EA
	b _0221A750
_0221A5EA:
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A5F6:
	mov r2, #3
	ldr r0, _0221A758 ; =0x02241A78
	str r2, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	bne _0221A606
	b _0221A750
_0221A606:
	mov r0, #0xb
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A610:
	mov r2, #2
	ldrsh r0, [r0, r2]
	cmp r0, #0
	bne _0221A6CC
	ldr r0, _0221A758 ; =0x02241A78
	ldr r2, [r0]
	cmp r2, #4
	bne _0221A638
	mov r2, #3
	str r2, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	bne _0221A62E
	b _0221A750
_0221A62E:
	mov r0, #0xe
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A638:
	cmp r2, #6
	bne _0221A66A
	ldr r0, _0221A760 ; =0x02241A70
	ldr r0, [r0]
	ldr r1, _0221A764 ; =0x02241A74
	ldr r1, [r1]
	ldr r2, _0221A768 ; =0x02241A64
	ldr r2, [r2]
	bl WCM_SearchAsync
	cmp r0, #3
	beq _0221A750
	mov r1, #3
	ldr r0, _0221A758 ; =0x02241A78
	str r1, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	beq _0221A750
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A66A:
	cmp r2, #2
	bne _0221A690
	bl WCM_CleanupAsync
	cmp r0, #3
	beq _0221A750
	mov r1, #3
	ldr r0, _0221A758 ; =0x02241A78
	str r1, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	beq _0221A750
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A690:
	cmp r2, #8
	bne _0221A6C2
	ldr r0, _0221A76C ; =0x02241A80
	ldr r0, [r0]
	ldr r1, _0221A770 ; =0x02241A84
	ldr r1, [r1]
	ldr r2, _0221A774 ; =0x02241A6C
	ldr r2, [r2]
	bl WCM_ConnectAsync
	cmp r0, #3
	beq _0221A750
	mov r1, #3
	ldr r0, _0221A758 ; =0x02241A78
	str r1, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	beq _0221A750
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A6C2:
	mov r1, #3
	str r1, [r0]
	add sp, #4
	pop {r3}
	bx r3
_0221A6CC:
	mov r2, #3
	ldr r0, _0221A758 ; =0x02241A78
	str r2, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	beq _0221A750
	mov r0, #0xf
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A6E4:
	mov r2, #2
	ldrsh r0, [r0, r2]
	cmp r0, #0
	bne _0221A710
	ldr r0, _0221A758 ; =0x02241A78
	ldr r0, [r0]
	cmp r0, #2
	bne _0221A750
	bl WCM_Finish
	mov r1, #0
	ldr r0, _0221A758 ; =0x02241A78
	str r1, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	beq _0221A750
	mov r0, #0x14
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A710:
	mov r3, #3
	ldr r0, _0221A758 ; =0x02241A78
	str r3, [r0]
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r3, [r0]
	cmp r3, #0
	beq _0221A750
	add r0, r2, #0
	blx r3
	add sp, #4
	pop {r3}
	bx r3
_0221A728:
	ldr r0, _0221A758 ; =0x02241A78
	ldr r0, [r0]
	cmp r0, #5
	bne _0221A750
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	beq _0221A750
	mov r0, #5
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221A742:
	ldr r0, _0221A75C ; =0x02241A7C
	ldr r2, [r0]
	cmp r2, #0
	beq _0221A750
	mov r0, #1
	mov r1, #0
	blx r2
_0221A750:
	add sp, #4
	pop {r3}
	bx r3
	nop
_0221A758: .word MOD13_02241A78
_0221A75C: .word MOD13_02241A7C
_0221A760: .word MOD13_02241A70
_0221A764: .word MOD13_02241A74
_0221A768: .word MOD13_02241A64
_0221A76C: .word MOD13_02241A80
_0221A770: .word MOD13_02241A84
_0221A774: .word MOD13_02241A6C

	thumb_func_start MOD13_0221A778
MOD13_0221A778: ; 0x0221A778
	push {lr}
	sub sp, #0xc
	add r0, sp, #0
	bl MOD13_0221A7AC
	add r0, sp, #0
	ldr r1, _0221A790 ; =0x02241B2C
	ldr r1, [r1]
	blx r1
	add sp, #0xc
	pop {r3}
	bx r3
	.align 2, 0
_0221A790: .word MOD13_02241B2C

	thumb_func_start MOD13_0221A794
MOD13_0221A794: ; 0x0221A794
	push {lr}
	sub sp, #4
	ldr r1, _0221A7A8 ; =0x02241CA8
	mov r2, #0xe8
	bl memcpy
	mov r0, #1
	add sp, #4
	pop {r3}
	bx r3
	.align 2, 0
_0221A7A8: .word MOD13_02241CA8

	thumb_func_start MOD13_0221A7AC
MOD13_0221A7AC: ; 0x0221A7AC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _0221A7E0 ; =0x02241AE8
	ldr r0, [r0]
	str r0, [r4]
	ldr r0, _0221A7E4 ; =0x0223F870
	ldr r1, [r0]
	mov r0, #0
	mvn r0, r0
	cmp r1, r0
	bne _0221A7C6
	str r0, [r4, #4]
	b _0221A7D2
_0221A7C6:
	bl MOD13_0221AA90
	ldr r1, _0221A7E4 ; =0x0223F870
	ldr r1, [r1]
	sub r0, r1, r0
	str r0, [r4, #4]
_0221A7D2:
	ldr r0, _0221A7E8 ; =0x02241B28
	ldr r0, [r0]
	str r0, [r4, #8]
	mov r0, #1
	pop {r4}
	pop {r3}
	bx r3
	.align 2, 0
_0221A7E0: .word MOD13_02241AE8
_0221A7E4: .word MOD13_0223F870
_0221A7E8: .word MOD13_02241B28

	thumb_func_start MOD13_0221A7EC
MOD13_0221A7EC: ; 0x0221A7EC
	push {r4, r5, r6, lr}
	ldr r0, _0221A884 ; =0x02241B14
	ldr r0, [r0]
	cmp r0, #0
	beq _0221A862
	ldr r4, _0221A888 ; =0x02241AE8
	ldr r6, [r4]
	mov r1, #1
	ldr r0, _0221A88C ; =0x02241AC0
	str r1, [r0]
	mov r5, #0x64
	b _0221A80A
_0221A804:
	add r0, r5, #0
	bl OS_Sleep
_0221A80A:
	ldr r0, [r4]
	cmp r0, #1
	blt _0221A814
	cmp r0, #5
	ble _0221A804
_0221A814:
	ldr r0, _0221A890 ; =0x000001F4
	bl OS_Sleep
	ldr r0, _0221A894 ; =0x02241BE8
	bl OS_IsThreadTerminated
	cmp r0, #0
	bne _0221A83C
	ldr r4, _0221A894 ; =0x02241BE8
_0221A826:
	add r0, r4, #0
	bl OS_WakeupThreadDirect
	add r0, r4, #0
	bl OS_JoinThread
	add r0, r4, #0
	bl OS_IsThreadTerminated
	cmp r0, #0
	beq _0221A826
_0221A83C:
	ldr r0, _0221A898 ; =0x02241AE0
	ldr r0, [r0]
	cmp r0, #0
	beq _0221A850
	ldr r1, _0221A89C ; =0x02241ABC
	ldr r1, [r1]
	blx r1
	mov r1, #0
	ldr r0, _0221A898 ; =0x02241AE0
	str r1, [r0]
_0221A850:
	mov r1, #0
	ldr r0, _0221A884 ; =0x02241B14
	str r1, [r0]
	ldr r0, _0221A888 ; =0x02241AE8
	ldr r0, [r0]
	cmp r6, r0
	beq _0221A862
	bl MOD13_0221A778
_0221A862:
	ldr r0, _0221A8A0 ; =0x02241B24
	ldr r0, [r0]
	cmp r0, #0
	ble _0221A87A
	bl MOD13_0221DAF4
	mov r2, #0
	ldr r1, _0221A8A0 ; =0x02241B24
	str r2, [r1]
	pop {r4, r5, r6}
	pop {r3}
	bx r3
_0221A87A:
	mov r0, #9
	mvn r0, r0
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	.align 2, 0
_0221A884: .word MOD13_02241B14
_0221A888: .word MOD13_02241AE8
_0221A88C: .word MOD13_02241AC0
_0221A890: .word 0x000001F4
_0221A894: .word MOD13_02241BE8
_0221A898: .word MOD13_02241AE0
_0221A89C: .word MOD13_02241ABC
_0221A8A0: .word MOD13_02241B24

	thumb_func_start MOD13_0221A8A4
MOD13_0221A8A4: ; 0x0221A8A4
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, _0221A998 ; =0x02241AE8
	ldr r0, [r0]
	cmp r0, #1
	blt _0221A8C2
	cmp r0, #5
	bgt _0221A8C2
	mov r0, #9
	mvn r0, r0
	add sp, #0xc
	pop {r4, r5}
	pop {r3}
	bx r3
_0221A8C2:
	ldr r0, _0221A99C ; =0x0223F874
	str r1, [r0]
	mov r5, #7
	ldr r0, _0221A998 ; =0x02241AE8
	str r5, [r0]
	ldr r0, _0221A9A0 ; =0x02241B2C
	str r2, [r0]
	ldr r0, _0221A9A4 ; =0x02241AB4
	str r3, [r0]
	ldr r2, [sp, #0x18]
	ldr r0, _0221A9A8 ; =0x02241ABC
	str r2, [r0]
	ldr r2, [sp, #0x1c]
	ldr r0, _0221A9AC ; =0x0223F86C
	str r2, [r0]
	add r0, r1, #0
	bl MOD13_0221DB54
	mov r2, #1
	ldr r1, _0221A9B0 ; =0x02241B24
	str r2, [r1]
	cmp r0, #0
	bge _0221A8FC
	ldr r1, _0221A9B4 ; =0x02241B28
	str r0, [r1]
	add sp, #0xc
	pop {r4, r5}
	pop {r3}
	bx r3
_0221A8FC:
	ldr r0, _0221A9AC ; =0x0223F86C
	ldr r0, [r0]
	ldr r1, _0221A9A4 ; =0x02241AB4
	ldr r1, [r1]
	blx r1
	ldr r1, _0221A9B8 ; =0x02241AE0
	str r0, [r1]
	cmp r0, #0
	bne _0221A91E
	mov r0, #0
	mvn r0, r0
	ldr r1, _0221A9B4 ; =0x02241B28
	str r0, [r1]
	add sp, #0xc
	pop {r4, r5}
	pop {r3}
	bx r3
_0221A91E:
	bl OS_IsThreadAvailable
	cmp r0, #1
	beq _0221A936
	mov r0, #8
	mvn r0, r0
	ldr r1, _0221A9B4 ; =0x02241B28
	str r0, [r1]
	add sp, #0xc
	pop {r4, r5}
	pop {r3}
	bx r3
_0221A936:
	ldr r0, _0221A9AC ; =0x0223F86C
	ldr r3, [r0]
	str r3, [sp]
	str r4, [sp, #4]
	ldr r0, _0221A9BC ; =0x02241BE8
	ldr r1, _0221A9C0 ; =MOD13_0221C618
	mov r2, #0
	ldr r4, _0221A9B8 ; =0x02241AE0
	ldr r5, [r4]
	mov r4, #7
	bic r3, r4
	add r3, r5, r3
	bl OS_CreateThread
	mov r1, #1
	ldr r0, _0221A998 ; =0x02241AE8
	str r1, [r0]
	bl MOD13_0221AA90
	ldr r1, _0221A9C4 ; =0x0000EA60
	add r1, r0, r1
	ldr r0, _0221A9C8 ; =0x0223F870
	str r1, [r0]
	mov r0, #0
	ldr r1, _0221A9CC ; =0x02241AC0
	str r0, [r1]
	ldr r5, _0221A9D0 ; =0x02241CA8
	add r1, r0, #0
	add r2, r0, #0
	add r3, r0, #0
_0221A972:
	stmia r5!, {r0, r1, r2, r3}
	stmia r5!, {r0, r1, r2, r3}
	sub r4, r4, #1
	cmp r4, #0
	bne _0221A972
	stmia r5!, {r0, r1}
	bl MOD13_0221A778
	ldr r0, _0221A9BC ; =0x02241BE8
	bl OS_WakeupThreadDirect
	mov r0, #1
	ldr r1, _0221A9D4 ; =0x02241B14
	str r0, [r1]
	add sp, #0xc
	pop {r4, r5}
	pop {r3}
	bx r3
	nop
_0221A998: .word MOD13_02241AE8
_0221A99C: .word MOD13_0223F874
_0221A9A0: .word MOD13_02241B2C
_0221A9A4: .word MOD13_02241AB4
_0221A9A8: .word MOD13_02241ABC
_0221A9AC: .word MOD13_0223F86C
_0221A9B0: .word MOD13_02241B24
_0221A9B4: .word MOD13_02241B28
_0221A9B8: .word MOD13_02241AE0
_0221A9BC: .word MOD13_02241BE8
_0221A9C0: .word MOD13_0221C618
_0221A9C4: .word 0x0000EA60
_0221A9C8: .word MOD13_0223F870
_0221A9CC: .word MOD13_02241AC0
_0221A9D0: .word MOD13_02241CA8
_0221A9D4: .word MOD13_02241B14

	thumb_func_start MOD13_0221A9D8
MOD13_0221A9D8: ; 0x0221A9D8
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	str r0, [sp]
	add r6, r1, #0
	lsl r5, r0, #0
	mov r4, #0
	add r7, r4, #0
_0221A9E6:
	add r0, r5, #0
	ldrsb r1, [r6, r7]
	add r6, r6, #1
	bl MOD13_0221AA14
	add r1, r5, r0
	add r5, r1, #0
	cmp r4, #5
	bge _0221A9FE
	add r5, r1, #1
	mov r0, #0x3a
	strb r0, [r1]
_0221A9FE:
	add r4, r4, #1
	cmp r4, #6
	blt _0221A9E6
	mov r0, #0
	strb r0, [r5]
	ldr r0, [sp]
	sub r0, r5, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3

	thumb_func_start MOD13_0221AA14
MOD13_0221AA14: ; 0x0221AA14
	push {r4, r5}
	add r2, r0, #0
	lsl r1, r1, #0x18
	lsr r4, r1, #0x18
	mov r1, #0xf0
	add r3, r4, #0
	and r3, r1
	asr r3, r3, #4
	mov r5, #0
	mov r1, #0xf
	and r4, r1
_0221AA2A:
	cmp r3, #9
	bgt _0221AA36
	add r3, #0x30
	strb r3, [r2]
	add r2, r2, #1
	b _0221AA3C
_0221AA36:
	add r3, #0x37
	strb r3, [r2]
	add r2, r2, #1
_0221AA3C:
	add r3, r4, #0
	add r5, r5, #1
	cmp r5, #2
	blt _0221AA2A
	mov r1, #0
	strb r1, [r2]
	sub r0, r2, r0
	pop {r4, r5}
	bx lr
	.align 2, 0

	thumb_func_start MOD13_0221AA50
MOD13_0221AA50: ; 0x0221AA50
	push {lr}
	sub sp, #4
	ldr r1, _0221AA60 ; =0x02241ABC
	ldr r1, [r1]
	blx r1
	add sp, #4
	pop {r3}
	bx r3
	.align 2, 0
_0221AA60: .word MOD13_02241ABC

	thumb_func_start MOD13_0221AA64
MOD13_0221AA64: ; 0x0221AA64
	push {r4, r5, lr}
	sub sp, #4
	add r4, r0, #0
	mul r4, r1
	add r0, r4, #0
	ldr r1, _0221AA8C ; =0x02241AB4
	ldr r1, [r1]
	blx r1
	add r5, r0, #0
	cmp r5, #0
	beq _0221AA82
	mov r1, #0
	add r2, r4, #0
	bl memset
_0221AA82:
	add r0, r5, #0
	add sp, #4
	pop {r4, r5}
	pop {r3}
	bx r3
	.align 2, 0
_0221AA8C: .word MOD13_02241AB4

	thumb_func_start MOD13_0221AA90
MOD13_0221AA90: ; 0x0221AA90
	push {lr}
	sub sp, #4
	bl OS_GetTick
	lsr r2, r0, #0x1a
	lsl r1, r1, #6
	orr r1, r2
	lsl r0, r0, #6
	ldr r2, _0221AAB0 ; =0x000082EA
	mov r3, #0
	bl _ll_udiv
	add sp, #4
	pop {r3}
	bx r3
	nop
_0221AAB0: .word 0x000082EA

	thumb_func_start MOD13_0221AAB4
MOD13_0221AAB4: ; 0x0221AAB4
	push {r4, r5, r6, lr}
	sub sp, #0x58
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	add r0, sp, #0
	bl MOD13_0221B4AC
	add r0, sp, #0
	add r1, r4, #0
	add r2, r6, #0
	bl MOD13_0221B42C
	add r0, r5, #0
	add r1, sp, #0
	bl MOD13_0221B3D0
	add sp, #0x58
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_0221AAE0
MOD13_0221AAE0: ; 0x0221AAE0
	mov r3, #0
	cmp r2, #0
	bls _0221AAF4
	lsl r1, r1, #0x18
	asr r1, r1, #0x18
_0221AAEA:
	strb r1, [r0]
	add r0, r0, #1
	add r3, r3, #1
	cmp r3, r2
	blo _0221AAEA
_0221AAF4:
	bx lr
	.align 2, 0

	thumb_func_start MOD13_0221AAF8
MOD13_0221AAF8: ; 0x0221AAF8
	push {r4}
	sub sp, #4
	mov r4, #0
	cmp r2, #0
	bls _0221AB0C
_0221AB02:
	ldrb r3, [r1, r4]
	strb r3, [r0, r4]
	add r4, r4, #1
	cmp r4, r2
	blo _0221AB02
_0221AB0C:
	add sp, #4
	pop {r4}
	bx lr
	.align 2, 0

	thumb_func_start MOD13_0221AB14
MOD13_0221AB14: ; 0x0221AB14
	push {r4, r5, r6, r7}
	mov r6, #0
	cmp r2, #0
	bls _0221AB3E
_0221AB1C:
	add r3, r6, #3
	ldrb r3, [r1, r3]
	lsl r5, r3, #0x18
	add r3, r6, #2
	ldrb r3, [r1, r3]
	lsl r4, r3, #0x10
	ldrb r3, [r1, r6]
	add r7, r6, #1
	ldrb r7, [r1, r7]
	lsl r7, r7, #8
	orr r3, r7
	orr r4, r3
	orr r5, r4
	stmia r0!, {r5}
	add r6, r6, #4
	cmp r6, r2
	blo _0221AB1C
_0221AB3E:
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0

	thumb_func_start MOD13_0221AB44
MOD13_0221AB44: ; 0x0221AB44
	push {r4, r5}
	mov r3, #0
	cmp r2, #0
	bls _0221AB70
_0221AB4C:
	ldr r4, [r1]
	strb r4, [r0, r3]
	ldr r4, [r1]
	lsr r5, r4, #8
	add r4, r3, #1
	strb r5, [r0, r4]
	ldr r4, [r1]
	lsr r5, r4, #0x10
	add r4, r3, #2
	strb r5, [r0, r4]
	ldr r4, [r1]
	lsr r5, r4, #0x18
	add r4, r3, #3
	strb r5, [r0, r4]
	add r1, r1, #4
	add r3, r3, #4
	cmp r3, r2
	blo _0221AB4C
_0221AB70:
	pop {r4, r5}
	bx lr

	thumb_func_start MOD13_0221AB74
MOD13_0221AB74: ; 0x0221AB74
	push {r4, r5, r6, r7, lr}
	sub sp, #0x84
	add r5, r0, #0
	ldr r0, [r5]
	str r0, [sp]
	ldr r4, [r5, #4]
	ldr r6, [r5, #8]
	ldr r7, [r5, #0xc]
	add r0, sp, #0x40
	mov r2, #0x40
	bl MOD13_0221AB14
	ldr r0, [sp, #0x40]
	str r0, [sp, #4]
	add r1, r4, #0
	and r1, r6
	mvn r0, r4
	and r0, r7
	orr r1, r0
	ldr r0, [sp, #4]
	add r1, r0, r1
	ldr r0, _0221AF8C ; =0x28955B88
	sub r1, r1, r0
	ldr r0, [sp]
	add r0, r0, r1
	lsl r1, r0, #7
	lsr r0, r0, #0x19
	orr r1, r0
	add r0, r1, r4
	ldr r1, [sp, #0x44]
	str r1, [sp, #8]
	add r1, r0, #0
	and r1, r4
	mvn r2, r0
	and r2, r6
	orr r1, r2
	ldr r2, [sp, #8]
	add r2, r2, r1
	ldr r1, _0221AF90 ; =0x173848AA
	sub r1, r2, r1
	add r1, r7, r1
	lsl r2, r1, #0xc
	lsr r1, r1, #0x14
	orr r2, r1
	add r3, r2, r0
	ldr r1, [sp, #0x48]
	str r1, [sp, #0xc]
	add r1, r3, #0
	and r1, r0
	mvn r2, r3
	and r2, r4
	orr r1, r2
	ldr r2, [sp, #0xc]
	add r2, r2, r1
	ldr r1, _0221AF94 ; =0x242070DB
	add r1, r2, r1
	add r1, r6, r1
	lsl r2, r1, #0x11
	lsr r1, r1, #0xf
	orr r2, r1
	add r2, r2, r3
	ldr r1, [sp, #0x4c]
	str r1, [sp, #0x10]
	add r1, r2, #0
	and r1, r3
	mvn r6, r2
	and r6, r0
	orr r1, r6
	ldr r6, [sp, #0x10]
	add r6, r6, r1
	ldr r1, _0221AF98 ; =0x3E423112
	sub r1, r6, r1
	add r1, r4, r1
	lsl r4, r1, #0x16
	lsr r1, r1, #0xa
	orr r4, r1
	add r1, r4, r2
	ldr r4, [sp, #0x50]
	str r4, [sp, #0x14]
	add r4, r1, #0
	and r4, r2
	mvn r6, r1
	and r6, r3
	orr r4, r6
	ldr r6, [sp, #0x14]
	add r6, r6, r4
	ldr r4, _0221AF9C ; =0x0A83F051
	sub r4, r6, r4
	add r0, r0, r4
	lsl r4, r0, #7
	lsr r0, r0, #0x19
	orr r4, r0
	add r4, r4, r1
	ldr r0, [sp, #0x54]
	str r0, [sp, #0x18]
	add r0, r4, #0
	and r0, r1
	mvn r6, r4
	and r6, r2
	orr r0, r6
	ldr r6, [sp, #0x18]
	add r6, r6, r0
	ldr r0, _0221AFA0 ; =0x4787C62A
	add r0, r6, r0
	add r0, r3, r0
	lsl r3, r0, #0xc
	lsr r0, r0, #0x14
	orr r3, r0
	add r3, r3, r4
	ldr r0, [sp, #0x58]
	str r0, [sp, #0x1c]
	add r0, r3, #0
	and r0, r4
	mvn r6, r3
	and r6, r1
	orr r0, r6
	ldr r6, [sp, #0x1c]
	add r6, r6, r0
	ldr r0, _0221AFA4 ; =0x57CFB9ED
	sub r0, r6, r0
	add r0, r2, r0
	lsl r2, r0, #0x11
	lsr r0, r0, #0xf
	orr r2, r0
	add r0, r2, r3
	ldr r2, [sp, #0x5c]
	str r2, [sp, #0x20]
	add r2, r0, #0
	and r2, r3
	mvn r6, r0
	and r6, r4
	orr r2, r6
	ldr r6, [sp, #0x20]
	add r6, r6, r2
	ldr r2, _0221AFA8 ; =0x02B96AFF
	sub r2, r6, r2
	add r1, r1, r2
	lsl r2, r1, #0x16
	lsr r1, r1, #0xa
	orr r2, r1
	add r6, r2, r0
	ldr r1, [sp, #0x60]
	str r1, [sp, #0x24]
	add r1, r6, #0
	and r1, r0
	mvn r2, r6
	and r2, r3
	orr r1, r2
	ldr r2, [sp, #0x24]
	add r2, r2, r1
	ldr r1, _0221AFAC ; =0x698098D8
	add r1, r2, r1
	add r1, r4, r1
	lsl r2, r1, #7
	lsr r1, r1, #0x19
	orr r2, r1
	add r2, r2, r6
	ldr r1, [sp, #0x64]
	str r1, [sp, #0x28]
	add r1, r2, #0
	and r1, r6
	mvn r4, r2
	and r4, r0
	orr r1, r4
	ldr r4, [sp, #0x28]
	add r4, r4, r1
	ldr r1, _0221AFB0 ; =0x74BB0851
	sub r1, r4, r1
	add r1, r3, r1
	lsl r3, r1, #0xc
	lsr r1, r1, #0x14
	orr r3, r1
	add r1, r3, r2
	ldr r3, [sp, #0x68]
	str r3, [sp, #0x2c]
	add r3, r1, #0
	and r3, r2
	mvn r4, r1
	and r4, r6
	orr r3, r4
	ldr r4, [sp, #0x2c]
	add r4, r4, r3
	ldr r3, _0221AFB4 ; =0x0000A44F
	sub r3, r4, r3
	add r0, r0, r3
	lsl r3, r0, #0x11
	lsr r0, r0, #0xf
	orr r3, r0
	add r4, r3, r1
	ldr r0, [sp, #0x6c]
	str r0, [sp, #0x30]
	add r0, r4, #0
	and r0, r1
	mvn r3, r4
	and r3, r2
	orr r0, r3
	ldr r3, [sp, #0x30]
	add r3, r3, r0
	ldr r0, _0221AFB8 ; =0x76A32842
	sub r0, r3, r0
	add r0, r6, r0
	lsl r3, r0, #0x16
	lsr r0, r0, #0xa
	orr r3, r0
	add r3, r3, r4
	ldr r0, [sp, #0x70]
	str r0, [sp, #0x34]
	add r0, r3, #0
	and r0, r4
	mvn r6, r3
	and r6, r1
	orr r0, r6
	ldr r6, [sp, #0x34]
	add r6, r6, r0
	ldr r0, _0221AFBC ; =0x6B901122
	add r0, r6, r0
	add r0, r2, r0
	lsl r2, r0, #7
	lsr r0, r0, #0x19
	orr r2, r0
	add r0, r2, r3
	ldr r2, [sp, #0x74]
	str r2, [sp, #0x38]
	add r2, r0, #0
	and r2, r3
	mvn r6, r0
	and r6, r4
	orr r2, r6
	ldr r6, [sp, #0x38]
	add r6, r6, r2
	ldr r2, _0221AFC0 ; =0x02678E6D
	sub r2, r6, r2
	add r1, r1, r2
	lsl r2, r1, #0xc
	lsr r1, r1, #0x14
	orr r2, r1
	add r6, r2, r0
	mvn r2, r6
	ldr r7, [sp, #0x78]
	add r1, r6, #0
	and r1, r0
	and r2, r3
	orr r1, r2
	add r2, r7, r1
	ldr r1, _0221AFC4 ; =0x5986BC72
	sub r1, r2, r1
	add r1, r4, r1
	lsl r2, r1, #0x11
	lsr r1, r1, #0xf
	orr r2, r1
	add r2, r2, r6
	mvn r4, r2
	ldr r1, [sp, #0x7c]
	str r1, [sp, #0x3c]
	add r1, r2, #0
	and r1, r6
	and r4, r0
	orr r1, r4
	ldr r4, [sp, #0x3c]
	add r4, r4, r1
	ldr r1, _0221AFC8 ; =0x49B40821
	add r1, r4, r1
	add r1, r3, r1
	lsl r3, r1, #0x16
	lsr r1, r1, #0xa
	orr r3, r1
	add r1, r3, r2
	add r3, r1, #0
	and r3, r6
	add r4, r2, #0
	bic r4, r6
	orr r3, r4
	ldr r4, [sp, #8]
	add r4, r4, r3
	ldr r3, _0221AFCC ; =0x09E1DA9E
	sub r3, r4, r3
	add r0, r0, r3
	lsl r3, r0, #5
	lsr r0, r0, #0x1b
	orr r3, r0
	add r4, r3, r1
	add r0, r4, #0
	and r0, r2
	add r3, r1, #0
	bic r3, r2
	orr r0, r3
	ldr r3, [sp, #0x1c]
	add r3, r3, r0
	ldr r0, _0221AFD0 ; =0x3FBF4CC0
	sub r0, r3, r0
	add r0, r6, r0
	lsl r3, r0, #9
	lsr r0, r0, #0x17
	orr r3, r0
	add r3, r3, r4
	add r0, r3, #0
	and r0, r1
	add r6, r4, #0
	bic r6, r1
	orr r0, r6
	ldr r6, [sp, #0x30]
	add r6, r6, r0
	ldr r0, _0221AFD4 ; =0x265E5A51
	add r0, r6, r0
	add r0, r2, r0
	lsl r2, r0, #0xe
	lsr r0, r0, #0x12
	orr r2, r0
	add r0, r2, r3
	add r2, r0, #0
	and r2, r4
	add r6, r3, #0
	bic r6, r4
	orr r2, r6
	ldr r6, [sp, #4]
	add r6, r6, r2
	ldr r2, _0221AFD8 ; =0x16493856
	sub r2, r6, r2
	add r1, r1, r2
	lsl r2, r1, #0x14
	lsr r1, r1, #0xc
	orr r2, r1
	add r6, r2, r0
	add r1, r6, #0
	and r1, r3
	add r2, r0, #0
	bic r2, r3
	orr r1, r2
	ldr r2, [sp, #0x18]
	add r2, r2, r1
	ldr r1, _0221AFDC ; =0x29D0EFA3
	sub r1, r2, r1
	add r1, r4, r1
	lsl r2, r1, #5
	lsr r1, r1, #0x1b
	orr r2, r1
	add r2, r2, r6
	add r1, r2, #0
	and r1, r0
	add r4, r6, #0
	bic r4, r0
	orr r1, r4
	ldr r4, [sp, #0x2c]
	add r4, r4, r1
	ldr r1, _0221AFE0 ; =0x02441453
	add r1, r4, r1
	add r1, r3, r1
	lsl r3, r1, #9
	lsr r1, r1, #0x17
	orr r3, r1
	add r1, r3, r2
	add r3, r1, #0
	and r3, r6
	add r4, r2, #0
	bic r4, r6
	orr r3, r4
	ldr r4, [sp, #0x3c]
	add r4, r4, r3
	ldr r3, _0221AFE4 ; =0x275E197F
	sub r3, r4, r3
	add r0, r0, r3
	lsl r3, r0, #0xe
	lsr r0, r0, #0x12
	orr r3, r0
	add r4, r3, r1
	add r0, r4, #0
	and r0, r2
	add r3, r1, #0
	bic r3, r2
	orr r0, r3
	ldr r3, [sp, #0x14]
	add r3, r3, r0
	ldr r0, _0221AFE8 ; =0x182C0438
	sub r0, r3, r0
	add r0, r6, r0
	lsl r3, r0, #0x14
	lsr r0, r0, #0xc
	orr r3, r0
	add r3, r3, r4
	add r0, r3, #0
	and r0, r1
	add r6, r4, #0
	bic r6, r1
	orr r0, r6
	ldr r6, [sp, #0x28]
	add r6, r6, r0
	ldr r0, _0221AFEC ; =0x21E1CDE6
	add r0, r6, r0
	add r0, r2, r0
	lsl r2, r0, #5
	lsr r0, r0, #0x1b
	orr r2, r0
	add r0, r2, r3
	add r6, r0, #0
	and r6, r4
	add r2, r3, #0
	bic r2, r4
	orr r6, r2
	add r6, r7, r6
	ldr r2, _0221AFF0 ; =0x3CC8F82A
	sub r2, r6, r2
	add r1, r1, r2
	lsl r2, r1, #9
	lsr r1, r1, #0x17
	orr r2, r1
	add r6, r2, r0
	add r1, r6, #0
	and r1, r3
	add r2, r0, #0
	bic r2, r3
	orr r1, r2
	ldr r2, [sp, #0x10]
	add r2, r2, r1
	ldr r1, _0221AFF4 ; =0x0B2AF279
	sub r1, r2, r1
	add r1, r4, r1
	lsl r2, r1, #0xe
	lsr r1, r1, #0x12
	orr r2, r1
	add r2, r2, r6
	add r1, r2, #0
	and r1, r0
	add r4, r6, #0
	bic r4, r0
	orr r1, r4
	ldr r4, [sp, #0x24]
	add r4, r4, r1
	ldr r1, _0221AFF8 ; =0x455A14ED
	add r1, r4, r1
	add r1, r3, r1
	lsl r3, r1, #0x14
	lsr r1, r1, #0xc
	orr r3, r1
	add r1, r3, r2
	add r3, r1, #0
	and r3, r6
	add r4, r2, #0
	bic r4, r6
	orr r3, r4
	ldr r4, [sp, #0x38]
	add r4, r4, r3
	ldr r3, _0221AFFC ; =0x561C16FB
	sub r3, r4, r3
	add r0, r0, r3
	lsl r3, r0, #5
	lsr r0, r0, #0x1b
	orr r3, r0
	add r4, r3, r1
	add r0, r4, #0
	and r0, r2
	add r3, r1, #0
	bic r3, r2
	orr r0, r3
	ldr r3, [sp, #0xc]
	add r3, r3, r0
	ldr r0, _0221B000 ; =0x03105C08
	sub r0, r3, r0
	add r0, r6, r0
	lsl r3, r0, #9
	lsr r0, r0, #0x17
	orr r3, r0
	add r3, r3, r4
	add r0, r3, #0
	and r0, r1
	add r6, r4, #0
	bic r6, r1
	orr r0, r6
	ldr r6, [sp, #0x20]
	add r6, r6, r0
	ldr r0, _0221B004 ; =0x676F02D9
	add r0, r6, r0
	add r0, r2, r0
	lsl r2, r0, #0xe
	lsr r0, r0, #0x12
	orr r2, r0
	add r0, r2, r3
	add r2, r0, #0
	and r2, r4
	add r6, r3, #0
	bic r6, r4
	orr r2, r6
	ldr r6, [sp, #0x34]
	add r6, r6, r2
	ldr r2, _0221B008 ; =0x72D5B376
	sub r2, r6, r2
	add r1, r1, r2
	lsl r2, r1, #0x14
	lsr r1, r1, #0xc
	orr r2, r1
	add r6, r2, r0
	add r2, r6, #0
	eor r2, r0
	add r1, r3, #0
	eor r1, r2
	ldr r2, [sp, #0x18]
	add r2, r2, r1
	ldr r1, _0221B00C ; =0x0005C6BE
	sub r1, r2, r1
	add r1, r4, r1
	lsl r2, r1, #4
	lsr r1, r1, #0x1c
	orr r2, r1
	add r2, r2, r6
	add r4, r2, #0
	eor r4, r6
	add r1, r0, #0
	eor r1, r4
	ldr r4, [sp, #0x24]
	add r4, r4, r1
	ldr r1, _0221B010 ; =0x788E097F
	sub r1, r4, r1
	add r1, r3, r1
	lsl r3, r1, #0xb
	lsr r1, r1, #0x15
	orr r3, r1
	add r1, r3, r2
	add r4, r1, #0
	eor r4, r2
	add r3, r6, #0
	eor r3, r4
	ldr r4, [sp, #0x30]
	add r4, r4, r3
	ldr r3, _0221B014 ; =0x6D9D6122
	b _0221B018
	.align 2, 0
_0221AF8C: .word 0x28955B88
_0221AF90: .word 0x173848AA
_0221AF94: .word 0x242070DB
_0221AF98: .word 0x3E423112
_0221AF9C: .word 0x0A83F051
_0221AFA0: .word 0x4787C62A
_0221AFA4: .word 0x57CFB9ED
_0221AFA8: .word 0x02B96AFF
_0221AFAC: .word 0x698098D8
_0221AFB0: .word 0x74BB0851
_0221AFB4: .word 0x0000A44F
_0221AFB8: .word 0x76A32842
_0221AFBC: .word 0x6B901122
_0221AFC0: .word 0x02678E6D
_0221AFC4: .word 0x5986BC72
_0221AFC8: .word 0x49B40821
_0221AFCC: .word 0x09E1DA9E
_0221AFD0: .word 0x3FBF4CC0
_0221AFD4: .word 0x265E5A51
_0221AFD8: .word 0x16493856
_0221AFDC: .word 0x29D0EFA3
_0221AFE0: .word 0x02441453
_0221AFE4: .word 0x275E197F
_0221AFE8: .word 0x182C0438
_0221AFEC: .word 0x21E1CDE6
_0221AFF0: .word 0x3CC8F82A
_0221AFF4: .word 0x0B2AF279
_0221AFF8: .word 0x455A14ED
_0221AFFC: .word 0x561C16FB
_0221B000: .word 0x03105C08
_0221B004: .word 0x676F02D9
_0221B008: .word 0x72D5B376
_0221B00C: .word 0x0005C6BE
_0221B010: .word 0x788E097F
_0221B014: .word 0x6D9D6122
_0221B018:
	add r3, r4, r3
	add r0, r0, r3
	lsl r3, r0, #0x10
	lsr r0, r0, #0x10
	orr r3, r0
	add r4, r3, r1
	add r0, r4, #0
	eor r0, r1
	add r3, r2, #0
	eor r3, r0
	add r3, r7, r3
	ldr r0, _0221B35C ; =0x021AC7F4
	sub r0, r3, r0
	add r0, r6, r0
	lsl r3, r0, #0x17
	lsr r0, r0, #9
	orr r3, r0
	add r3, r3, r4
	add r6, r3, #0
	eor r6, r4
	add r0, r1, #0
	eor r0, r6
	ldr r6, [sp, #8]
	add r6, r6, r0
	ldr r0, _0221B360 ; =0x5B4115BC
	sub r0, r6, r0
	add r0, r2, r0
	lsl r2, r0, #4
	lsr r0, r0, #0x1c
	orr r2, r0
	add r0, r2, r3
	add r6, r0, #0
	eor r6, r3
	add r2, r4, #0
	eor r2, r6
	ldr r6, [sp, #0x14]
	add r6, r6, r2
	ldr r2, _0221B364 ; =0x4BDECFA9
	add r2, r6, r2
	add r1, r1, r2
	lsl r2, r1, #0xb
	lsr r1, r1, #0x15
	orr r2, r1
	add r6, r2, r0
	add r2, r6, #0
	eor r2, r0
	add r1, r3, #0
	eor r1, r2
	ldr r2, [sp, #0x20]
	add r2, r2, r1
	ldr r1, _0221B368 ; =0x0944B4A0
	sub r1, r2, r1
	add r1, r4, r1
	lsl r2, r1, #0x10
	lsr r1, r1, #0x10
	orr r2, r1
	add r2, r2, r6
	add r4, r2, #0
	eor r4, r6
	add r1, r0, #0
	eor r1, r4
	ldr r4, [sp, #0x2c]
	add r4, r4, r1
	ldr r1, _0221B36C ; =0x41404390
	sub r1, r4, r1
	add r1, r3, r1
	lsl r3, r1, #0x17
	lsr r1, r1, #9
	orr r3, r1
	add r1, r3, r2
	add r4, r1, #0
	eor r4, r2
	add r3, r6, #0
	eor r3, r4
	ldr r4, [sp, #0x38]
	add r4, r4, r3
	ldr r3, _0221B370 ; =0x289B7EC6
	add r3, r4, r3
	add r0, r0, r3
	lsl r3, r0, #4
	lsr r0, r0, #0x1c
	orr r3, r0
	add r4, r3, r1
	add r3, r4, #0
	eor r3, r1
	add r0, r2, #0
	eor r0, r3
	ldr r3, [sp, #4]
	add r3, r3, r0
	ldr r0, _0221B374 ; =0x155ED806
	sub r0, r3, r0
	add r0, r6, r0
	lsl r3, r0, #0xb
	lsr r0, r0, #0x15
	orr r3, r0
	add r3, r3, r4
	add r6, r3, #0
	eor r6, r4
	add r0, r1, #0
	eor r0, r6
	ldr r6, [sp, #0x10]
	add r6, r6, r0
	ldr r0, _0221B378 ; =0x2B10CF7B
	sub r0, r6, r0
	add r0, r2, r0
	lsl r2, r0, #0x10
	lsr r0, r0, #0x10
	orr r2, r0
	add r0, r2, r3
	add r6, r0, #0
	eor r6, r3
	add r2, r4, #0
	eor r2, r6
	ldr r6, [sp, #0x1c]
	add r6, r6, r2
	ldr r2, _0221B37C ; =0x04881D05
	add r2, r6, r2
	add r1, r1, r2
	lsl r2, r1, #0x17
	lsr r1, r1, #9
	orr r2, r1
	add r6, r2, r0
	add r2, r6, #0
	eor r2, r0
	add r1, r3, #0
	eor r1, r2
	ldr r2, [sp, #0x28]
	add r2, r2, r1
	ldr r1, _0221B380 ; =0x262B2FC7
	sub r1, r2, r1
	add r1, r4, r1
	lsl r2, r1, #4
	lsr r1, r1, #0x1c
	orr r2, r1
	add r2, r2, r6
	add r4, r2, #0
	eor r4, r6
	add r1, r0, #0
	eor r1, r4
	ldr r4, [sp, #0x34]
	add r4, r4, r1
	ldr r1, _0221B384 ; =0x1924661B
	sub r1, r4, r1
	add r1, r3, r1
	lsl r3, r1, #0xb
	lsr r1, r1, #0x15
	orr r3, r1
	add r1, r3, r2
	add r4, r1, #0
	eor r4, r2
	add r3, r6, #0
	eor r3, r4
	ldr r4, [sp, #0x3c]
	add r4, r4, r3
	ldr r3, _0221B388 ; =0x1FA27CF8
	add r3, r4, r3
	add r0, r0, r3
	lsl r3, r0, #0x10
	lsr r0, r0, #0x10
	orr r3, r0
	add r4, r3, r1
	add r3, r4, #0
	eor r3, r1
	add r0, r2, #0
	eor r0, r3
	ldr r3, [sp, #0xc]
	add r3, r3, r0
	ldr r0, _0221B38C ; =0x3B53A99B
	sub r0, r3, r0
	add r0, r6, r0
	lsl r3, r0, #0x17
	lsr r0, r0, #9
	orr r3, r0
	add r3, r3, r4
	mvn r6, r1
	add r0, r3, #0
	orr r0, r6
	add r6, r4, #0
	eor r6, r0
	ldr r0, [sp, #4]
	add r6, r0, r6
	ldr r0, _0221B390 ; =0x0BD6DDBC
	sub r0, r6, r0
	add r0, r2, r0
	lsl r2, r0, #6
	lsr r0, r0, #0x1a
	orr r2, r0
	add r0, r2, r3
	mvn r6, r4
	add r2, r0, #0
	orr r2, r6
	add r6, r3, #0
	eor r6, r2
	ldr r2, [sp, #0x20]
	add r6, r2, r6
	ldr r2, _0221B394 ; =0x432AFF97
	add r2, r6, r2
	add r1, r1, r2
	lsl r2, r1, #0xa
	lsr r1, r1, #0x16
	orr r2, r1
	add r1, r2, r0
	mvn r2, r3
	add r6, r1, #0
	orr r6, r2
	add r2, r0, #0
	eor r2, r6
	add r6, r7, r2
	ldr r2, _0221B398 ; =0x546BDC59
	sub r2, r6, r2
	add r2, r4, r2
	lsl r4, r2, #0xf
	lsr r2, r2, #0x11
	orr r4, r2
	add r2, r4, r1
	mvn r6, r0
	add r4, r2, #0
	orr r4, r6
	add r6, r1, #0
	eor r6, r4
	ldr r4, [sp, #0x18]
	add r6, r4, r6
	ldr r4, _0221B39C ; =0x036C5FC7
	sub r4, r6, r4
	add r3, r3, r4
	lsl r4, r3, #0x15
	lsr r3, r3, #0xb
	orr r4, r3
	add r4, r4, r2
	mvn r6, r1
	add r3, r4, #0
	orr r3, r6
	add r6, r2, #0
	eor r6, r3
	ldr r3, [sp, #0x34]
	add r6, r3, r6
	ldr r3, _0221B3A0 ; =0x655B59C3
	add r3, r6, r3
	add r0, r0, r3
	lsl r3, r0, #6
	lsr r0, r0, #0x1a
	orr r3, r0
	add r3, r3, r4
	mvn r6, r2
	add r0, r3, #0
	orr r0, r6
	add r6, r4, #0
	eor r6, r0
	ldr r0, [sp, #0x10]
	add r6, r0, r6
	ldr r0, _0221B3A4 ; =0x70F3336E
	sub r0, r6, r0
	add r0, r1, r0
	lsl r1, r0, #0xa
	lsr r0, r0, #0x16
	orr r1, r0
	add r0, r1, r3
	mvn r6, r4
	add r1, r0, #0
	orr r1, r6
	add r6, r3, #0
	eor r6, r1
	ldr r1, [sp, #0x2c]
	add r6, r1, r6
	ldr r1, _0221B3A8 ; =0x00100B83
	sub r1, r6, r1
	add r1, r2, r1
	lsl r2, r1, #0xf
	lsr r1, r1, #0x11
	orr r2, r1
	add r6, r2, r0
	mvn r2, r3
	add r1, r6, #0
	orr r1, r2
	add r2, r0, #0
	eor r2, r1
	ldr r1, [sp, #8]
	add r2, r1, r2
	ldr r1, _0221B3AC ; =0x7A7BA22F
	sub r1, r2, r1
	add r1, r4, r1
	lsl r2, r1, #0x15
	lsr r1, r1, #0xb
	orr r2, r1
	add r2, r2, r6
	mvn r4, r0
	add r1, r2, #0
	orr r1, r4
	add r4, r6, #0
	eor r4, r1
	ldr r1, [sp, #0x24]
	add r4, r1, r4
	ldr r1, _0221B3B0 ; =0x6FA87E4F
	add r1, r4, r1
	add r1, r3, r1
	lsl r3, r1, #6
	lsr r1, r1, #0x1a
	orr r3, r1
	add r1, r3, r2
	mvn r4, r6
	add r3, r1, #0
	orr r3, r4
	add r4, r2, #0
	eor r4, r3
	ldr r3, [sp, #0x3c]
	add r4, r3, r4
	ldr r3, _0221B3B4 ; =0x01D31920
	sub r3, r4, r3
	add r0, r0, r3
	lsl r3, r0, #0xa
	lsr r0, r0, #0x16
	orr r3, r0
	add r4, r3, r1
	mvn r3, r2
	add r0, r4, #0
	orr r0, r3
	add r3, r1, #0
	eor r3, r0
	ldr r0, [sp, #0x1c]
	add r3, r0, r3
	ldr r0, _0221B3B8 ; =0x5CFEBCEC
	sub r0, r3, r0
	add r0, r6, r0
	lsl r3, r0, #0xf
	lsr r0, r0, #0x11
	orr r3, r0
	add r3, r3, r4
	mvn r6, r1
	add r0, r3, #0
	orr r0, r6
	add r6, r4, #0
	eor r6, r0
	ldr r0, [sp, #0x38]
	add r6, r0, r6
	ldr r0, _0221B3BC ; =0x4E0811A1
	add r0, r6, r0
	add r0, r2, r0
	lsl r2, r0, #0x15
	lsr r0, r0, #0xb
	orr r2, r0
	add r0, r2, r3
	mvn r6, r4
	add r2, r0, #0
	orr r2, r6
	add r6, r3, #0
	eor r6, r2
	ldr r2, [sp, #0x14]
	add r6, r2, r6
	ldr r2, _0221B3C0 ; =0x08AC817E
	sub r2, r6, r2
	add r1, r1, r2
	lsl r2, r1, #6
	lsr r1, r1, #0x1a
	orr r2, r1
	add r6, r2, r0
	mvn r2, r3
	add r1, r6, #0
	orr r1, r2
	add r2, r0, #0
	eor r2, r1
	ldr r1, [sp, #0x30]
	add r2, r1, r2
	ldr r1, _0221B3C4 ; =0x42C50DCB
	sub r1, r2, r1
	add r1, r4, r1
	lsl r2, r1, #0xa
	lsr r1, r1, #0x16
	orr r2, r1
	add r2, r2, r6
	mvn r4, r0
	add r1, r2, #0
	orr r1, r4
	add r4, r6, #0
	eor r4, r1
	ldr r1, [sp, #0xc]
	add r4, r1, r4
	ldr r1, _0221B3C8 ; =0x2AD7D2BB
	add r1, r4, r1
	add r1, r3, r1
	lsl r3, r1, #0xf
	lsr r1, r1, #0x11
	orr r3, r1
	add r1, r3, r2
	mvn r4, r6
	add r3, r1, #0
	orr r3, r4
	add r4, r2, #0
	eor r4, r3
	ldr r3, [sp, #0x28]
	add r4, r3, r4
	ldr r3, _0221B3CC ; =0x14792C6F
	sub r3, r4, r3
	add r0, r0, r3
	lsl r3, r0, #0x15
	lsr r0, r0, #0xb
	orr r3, r0
	add r0, r3, r1
	ldr r3, [r5]
	add r3, r3, r6
	str r3, [r5]
	ldr r3, [r5, #4]
	add r0, r3, r0
	str r0, [r5, #4]
	ldr r0, [r5, #8]
	add r0, r0, r1
	str r0, [r5, #8]
	ldr r0, [r5, #0xc]
	add r0, r0, r2
	str r0, [r5, #0xc]
	add r0, sp, #0x40
	mov r1, #0
	mov r2, #0x40
	bl MOD13_0221AAE0
	add sp, #0x84
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_0221B35C: .word 0x021AC7F4
_0221B360: .word 0x5B4115BC
_0221B364: .word 0x4BDECFA9
_0221B368: .word 0x0944B4A0
_0221B36C: .word 0x41404390
_0221B370: .word 0x289B7EC6
_0221B374: .word 0x155ED806
_0221B378: .word 0x2B10CF7B
_0221B37C: .word 0x04881D05
_0221B380: .word 0x262B2FC7
_0221B384: .word 0x1924661B
_0221B388: .word 0x1FA27CF8
_0221B38C: .word 0x3B53A99B
_0221B390: .word 0x0BD6DDBC
_0221B394: .word 0x432AFF97
_0221B398: .word 0x546BDC59
_0221B39C: .word 0x036C5FC7
_0221B3A0: .word 0x655B59C3
_0221B3A4: .word 0x70F3336E
_0221B3A8: .word 0x00100B83
_0221B3AC: .word 0x7A7BA22F
_0221B3B0: .word 0x6FA87E4F
_0221B3B4: .word 0x01D31920
_0221B3B8: .word 0x5CFEBCEC
_0221B3BC: .word 0x4E0811A1
_0221B3C0: .word 0x08AC817E
_0221B3C4: .word 0x42C50DCB
_0221B3C8: .word 0x2AD7D2BB
_0221B3CC: .word 0x14792C6F

	thumb_func_start MOD13_0221B3D0
MOD13_0221B3D0: ; 0x0221B3D0
	push {r4, r5, lr}
	sub sp, #0xc
	add r5, r0, #0
	add r4, r1, #0
	add r0, sp, #0
	add r1, #0x10
	mov r2, #8
	bl MOD13_0221AB44
	ldr r0, [r4, #0x10]
	lsr r1, r0, #3
	mov r0, #0x3f
	and r1, r0
	cmp r1, #0x38
	bhs _0221B3F4
	mov r0, #0x38
	sub r2, r0, r1
	b _0221B3F8
_0221B3F4:
	mov r0, #0x78
	sub r2, r0, r1
_0221B3F8:
	add r0, r4, #0
	ldr r1, _0221B428 ; =0x0223F894
	bl MOD13_0221B42C
	add r0, r4, #0
	add r1, sp, #0
	mov r2, #8
	bl MOD13_0221B42C
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x10
	bl MOD13_0221AB44
	add r0, r4, #0
	mov r1, #0
	mov r2, #0x58
	bl MOD13_0221AAE0
	add sp, #0xc
	pop {r4, r5}
	pop {r3}
	bx r3
	nop
_0221B428: .word MOD13_0223F894

	thumb_func_start MOD13_0221B42C
MOD13_0221B42C: ; 0x0221B42C
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r5, r0, #0
	add r7, r1, #0
	add r6, r2, #0
	ldr r3, [r5, #0x10]
	lsr r0, r3, #3
	mov r1, #0x3f
	and r0, r1
	lsl r2, r6, #3
	add r1, r3, r2
	str r1, [r5, #0x10]
	ldr r1, [r5, #0x10]
	cmp r1, r2
	bhs _0221B450
	ldr r1, [r5, #0x14]
	add r1, r1, #1
	str r1, [r5, #0x14]
_0221B450:
	ldr r2, [r5, #0x14]
	lsr r1, r6, #0x1d
	add r1, r2, r1
	str r1, [r5, #0x14]
	mov r1, #0x40
	sub r4, r1, r0
	cmp r6, r4
	blo _0221B496
	add r1, r5, #0
	add r1, #0x18
	add r0, r1, r0
	add r1, r7, #0
	add r2, r4, #0
	bl MOD13_0221AAF8
	add r0, r5, #0
	add r1, r5, #0
	add r1, #0x18
	bl MOD13_0221AB74
	add r0, r4, #0
	add r0, #0x3f
	cmp r0, r6
	bhs _0221B492
_0221B480:
	add r0, r5, #0
	add r1, r7, r4
	bl MOD13_0221AB74
	add r4, #0x40
	add r0, r4, #0
	add r0, #0x3f
	cmp r0, r6
	blo _0221B480
_0221B492:
	mov r0, #0
	b _0221B498
_0221B496:
	mov r4, #0
_0221B498:
	add r5, #0x18
	add r0, r5, r0
	add r1, r7, r4
	sub r2, r6, r4
	bl MOD13_0221AAF8
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3

	thumb_func_start MOD13_0221B4AC
MOD13_0221B4AC: ; 0x0221B4AC
	mov r1, #0
	str r1, [r0, #0x14]
	ldr r1, [r0, #0x14]
	str r1, [r0, #0x10]
	ldr r1, _0221B4C8 ; =0x67452301
	str r1, [r0]
	ldr r1, _0221B4CC ; =0xEFCDAB89
	str r1, [r0, #4]
	ldr r1, _0221B4D0 ; =0x98BADCFE
	str r1, [r0, #8]
	ldr r1, _0221B4D4 ; =0x10325476
	str r1, [r0, #0xc]
	bx lr
	nop
_0221B4C8: .word 0x67452301
_0221B4CC: .word 0xEFCDAB89
_0221B4D0: .word 0x98BADCFE
_0221B4D4: .word 0x10325476

	thumb_func_start MOD13_0221B4D8
MOD13_0221B4D8: ; 0x0221B4D8
	push {r4, r5, r6, r7}
	sub sp, #0x60
	add r4, r1, #0
	add r1, r2, #0
	str r3, [sp]
	ldr r2, [r0]
	str r2, [sp, #4]
	ldrb r5, [r1, #3]
	ldrb r2, [r1, #2]
	lsl r3, r2, #8
	ldrb r2, [r1]
	lsl r2, r2, #0x18
	ldrb r6, [r1, #1]
	lsl r6, r6, #0x10
	eor r2, r6
	eor r3, r2
	eor r5, r3
	ldr r2, [sp, #4]
	eor r2, r5
	str r2, [sp, #4]
	ldr r2, [r0, #4]
	str r2, [sp, #8]
	ldrb r5, [r1, #7]
	ldrb r2, [r1, #6]
	lsl r3, r2, #8
	ldrb r2, [r1, #4]
	lsl r2, r2, #0x18
	ldrb r6, [r1, #5]
	lsl r6, r6, #0x10
	eor r2, r6
	eor r3, r2
	eor r5, r3
	ldr r2, [sp, #8]
	eor r2, r5
	str r2, [sp, #8]
	ldr r2, [r0, #8]
	str r2, [sp, #0x2c]
	ldrb r5, [r1, #0xb]
	ldrb r2, [r1, #0xa]
	lsl r3, r2, #8
	ldrb r2, [r1, #8]
	lsl r2, r2, #0x18
	ldrb r6, [r1, #9]
	lsl r6, r6, #0x10
	eor r2, r6
	eor r3, r2
	eor r5, r3
	ldr r2, [sp, #0x2c]
	eor r2, r5
	str r2, [sp, #0x2c]
	ldr r6, [r0, #0xc]
	ldrb r5, [r1, #0xf]
	ldrb r2, [r1, #0xe]
	lsl r3, r2, #8
	ldrb r2, [r1, #0xc]
	lsl r2, r2, #0x18
	ldrb r1, [r1, #0xd]
	lsl r1, r1, #0x10
	eor r2, r1
	eor r3, r2
	eor r5, r3
	eor r6, r5
	asr r1, r4, #1
	str r1, [sp, #0xc]
	mov r2, #0xff
_0221B55A:
	ldr r1, [r0, #0x10]
	str r1, [sp, #0x10]
	ldr r1, [sp, #8]
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221B8E0 ; =0x0223C86C
	ldr r5, [r1, r3]
	ldr r1, [sp, #0x2c]
	lsr r1, r1, #8
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221B8E4 ; =0x0223C46C
	ldr r4, [r1, r3]
	ldr r1, [sp, #4]
	lsr r1, r1, #0x18
	lsl r3, r1, #2
	ldr r1, _0221B8E8 ; =0x0223E46C
	ldr r7, [r1, r3]
	lsr r1, r6, #0x10
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221B8EC ; =0x0223E86C
	ldr r1, [r1, r3]
	eor r7, r1
	eor r4, r7
	eor r5, r4
	ldr r1, [sp, #0x10]
	eor r1, r5
	str r1, [sp, #0x10]
	ldr r1, [r0, #0x14]
	str r1, [sp, #0x14]
	ldr r1, [sp, #0x2c]
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221B8E0 ; =0x0223C86C
	ldr r5, [r1, r3]
	lsr r1, r6, #8
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221B8E4 ; =0x0223C46C
	ldr r4, [r1, r3]
	ldr r1, [sp, #8]
	lsr r1, r1, #0x18
	lsl r3, r1, #2
	ldr r1, _0221B8E8 ; =0x0223E46C
	ldr r7, [r1, r3]
	ldr r1, [sp, #4]
	lsr r1, r1, #0x10
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221B8EC ; =0x0223E86C
	ldr r1, [r1, r3]
	eor r7, r1
	eor r4, r7
	eor r5, r4
	ldr r1, [sp, #0x14]
	eor r1, r5
	str r1, [sp, #0x14]
	ldr r5, [r0, #0x18]
	add r1, r6, #0
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221B8E0 ; =0x0223C86C
	ldr r4, [r1, r3]
	ldr r1, [sp, #4]
	lsr r1, r1, #8
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221B8E4 ; =0x0223C46C
	ldr r1, [r1, r3]
	str r1, [sp, #0x18]
	ldr r1, [sp, #0x2c]
	lsr r1, r1, #0x18
	lsl r3, r1, #2
	ldr r1, _0221B8E8 ; =0x0223E46C
	ldr r7, [r1, r3]
	ldr r1, [sp, #8]
	lsr r1, r1, #0x10
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221B8EC ; =0x0223E86C
	ldr r1, [r1, r3]
	eor r7, r1
	ldr r1, [sp, #0x18]
	eor r1, r7
	str r1, [sp, #0x18]
	eor r4, r1
	eor r5, r4
	ldr r1, [r0, #0x1c]
	ldr r3, [sp, #4]
	and r3, r2
	str r3, [sp, #4]
	lsl r4, r3, #2
	ldr r3, _0221B8E0 ; =0x0223C86C
	ldr r3, [r3, r4]
	str r3, [sp, #0x30]
	ldr r3, [sp, #8]
	lsr r3, r3, #8
	and r3, r2
	lsl r4, r3, #2
	ldr r3, _0221B8E4 ; =0x0223C46C
	ldr r7, [r3, r4]
	lsr r3, r6, #0x18
	lsl r4, r3, #2
	ldr r3, _0221B8E8 ; =0x0223E46C
	ldr r6, [r3, r4]
	ldr r3, [sp, #0x2c]
	lsr r3, r3, #0x10
	and r3, r2
	lsl r4, r3, #2
	ldr r3, _0221B8EC ; =0x0223E86C
	ldr r3, [r3, r4]
	eor r6, r3
	eor r7, r6
	ldr r3, [sp, #0x30]
	eor r3, r7
	str r3, [sp, #0x30]
	eor r1, r3
	add r0, #0x20
	ldr r3, [sp, #0xc]
	sub r3, r3, #1
	str r3, [sp, #0xc]
	cmp r3, #0
	beq _0221B746
	ldr r3, [r0]
	str r3, [sp, #4]
	ldr r3, [sp, #0x14]
	and r3, r2
	lsl r4, r3, #2
	ldr r3, _0221B8E0 ; =0x0223C86C
	ldr r6, [r3, r4]
	lsr r3, r5, #8
	and r3, r2
	lsl r4, r3, #2
	ldr r3, _0221B8E4 ; =0x0223C46C
	ldr r3, [r3, r4]
	str r3, [sp, #0x34]
	ldr r3, [sp, #0x10]
	lsr r3, r3, #0x18
	lsl r4, r3, #2
	ldr r3, _0221B8E8 ; =0x0223E46C
	ldr r7, [r3, r4]
	lsr r3, r1, #0x10
	and r3, r2
	lsl r4, r3, #2
	ldr r3, _0221B8EC ; =0x0223E86C
	ldr r3, [r3, r4]
	eor r7, r3
	ldr r3, [sp, #0x34]
	eor r3, r7
	str r3, [sp, #0x34]
	eor r6, r3
	ldr r3, [sp, #4]
	eor r3, r6
	str r3, [sp, #4]
	ldr r3, [r0, #4]
	str r3, [sp, #8]
	add r3, r5, #0
	and r3, r2
	lsl r4, r3, #2
	ldr r3, _0221B8E0 ; =0x0223C86C
	ldr r6, [r3, r4]
	lsr r3, r1, #8
	and r3, r2
	lsl r4, r3, #2
	ldr r3, _0221B8E4 ; =0x0223C46C
	ldr r3, [r3, r4]
	str r3, [sp, #0x38]
	ldr r3, [sp, #0x14]
	lsr r3, r3, #0x18
	lsl r4, r3, #2
	ldr r3, _0221B8E8 ; =0x0223E46C
	ldr r7, [r3, r4]
	ldr r3, [sp, #0x10]
	lsr r3, r3, #0x10
	and r3, r2
	lsl r4, r3, #2
	ldr r3, _0221B8EC ; =0x0223E86C
	ldr r3, [r3, r4]
	eor r7, r3
	ldr r3, [sp, #0x38]
	eor r3, r7
	str r3, [sp, #0x38]
	eor r6, r3
	ldr r3, [sp, #8]
	eor r3, r6
	str r3, [sp, #8]
	ldr r3, [r0, #8]
	str r3, [sp, #0x2c]
	add r3, r1, #0
	and r3, r2
	lsl r4, r3, #2
	ldr r3, _0221B8E0 ; =0x0223C86C
	ldr r6, [r3, r4]
	ldr r3, [sp, #0x10]
	lsr r3, r3, #8
	and r3, r2
	lsl r4, r3, #2
	ldr r3, _0221B8E4 ; =0x0223C46C
	ldr r3, [r3, r4]
	str r3, [sp, #0x1c]
	lsr r3, r5, #0x18
	lsl r4, r3, #2
	ldr r3, _0221B8E8 ; =0x0223E46C
	ldr r7, [r3, r4]
	ldr r3, [sp, #0x14]
	lsr r3, r3, #0x10
	and r3, r2
	lsl r4, r3, #2
	ldr r3, _0221B8EC ; =0x0223E86C
	ldr r3, [r3, r4]
	eor r7, r3
	ldr r3, [sp, #0x1c]
	eor r3, r7
	str r3, [sp, #0x1c]
	eor r6, r3
	ldr r3, [sp, #0x2c]
	eor r3, r6
	str r3, [sp, #0x2c]
	ldr r6, [r0, #0xc]
	ldr r3, [sp, #0x10]
	and r3, r2
	str r3, [sp, #0x10]
	lsl r4, r3, #2
	ldr r3, _0221B8E0 ; =0x0223C86C
	ldr r7, [r3, r4]
	ldr r3, [sp, #0x14]
	lsr r3, r3, #8
	and r3, r2
	lsl r4, r3, #2
	ldr r3, _0221B8E4 ; =0x0223C46C
	ldr r3, [r3, r4]
	lsr r1, r1, #0x18
	lsl r4, r1, #2
	ldr r1, _0221B8E8 ; =0x0223E46C
	ldr r1, [r1, r4]
	lsr r4, r5, #0x10
	and r4, r2
	lsl r5, r4, #2
	ldr r4, _0221B8EC ; =0x0223E86C
	ldr r4, [r4, r5]
	eor r1, r4
	eor r3, r1
	eor r7, r3
	eor r6, r7
	b _0221B55A
_0221B746:
	ldr r3, [r0]
	ldr r4, [sp, #0x14]
	mov r2, #0xff
	and r4, r2
	lsl r4, r4, #2
	ldr r2, _0221B8F0 ; =0x0223CC6C
	ldr r6, [r2, r4]
	str r6, [sp, #0x20]
	mov r4, #0xff
	and r6, r4
	str r6, [sp, #0x20]
	lsr r6, r5, #8
	and r6, r4
	lsl r4, r6, #2
	ldr r7, [r2, r4]
	ldr r4, _0221B8F4 ; =0x0000FF00
	and r7, r4
	ldr r4, [sp, #0x10]
	lsr r4, r4, #0x18
	lsl r4, r4, #2
	ldr r4, [r2, r4]
	str r4, [sp, #0x54]
	ldr r6, _0221B8F8 ; =0xFF000000
	and r4, r6
	str r4, [sp, #0x54]
	lsr r4, r1, #0x10
	str r4, [sp, #0x40]
	mov r6, #0xff
	and r4, r6
	str r4, [sp, #0x40]
	lsl r4, r4, #2
	ldr r4, [r2, r4]
	str r4, [sp, #0x3c]
	ldr r4, _0221B8FC ; =0x00FF0000
	ldr r6, [sp, #0x3c]
	and r6, r4
	str r6, [sp, #0x3c]
	ldr r4, [sp, #0x54]
	eor r4, r6
	str r4, [sp, #0x54]
	eor r7, r4
	ldr r4, [sp, #0x20]
	eor r4, r7
	str r4, [sp, #0x20]
	eor r3, r4
	lsr r6, r3, #0x18
	ldr r4, [sp]
	strb r6, [r4]
	lsr r6, r3, #0x10
	strb r6, [r4, #1]
	lsr r6, r3, #8
	strb r6, [r4, #2]
	strb r3, [r4, #3]
	ldr r3, [r0, #4]
	add r6, r5, #0
	mov r4, #0xff
	and r6, r4
	lsl r4, r6, #2
	ldr r6, [r2, r4]
	str r6, [sp, #0x24]
	mov r4, #0xff
	and r6, r4
	str r6, [sp, #0x24]
	lsr r6, r1, #8
	and r6, r4
	lsl r4, r6, #2
	ldr r7, [r2, r4]
	ldr r4, _0221B8F4 ; =0x0000FF00
	and r7, r4
	ldr r4, [sp, #0x14]
	lsr r4, r4, #0x18
	lsl r4, r4, #2
	ldr r4, [r2, r4]
	str r4, [sp, #0x58]
	ldr r6, _0221B8F8 ; =0xFF000000
	and r4, r6
	str r4, [sp, #0x58]
	ldr r4, [sp, #0x10]
	lsr r4, r4, #0x10
	str r4, [sp, #0x48]
	mov r6, #0xff
	and r4, r6
	str r4, [sp, #0x48]
	lsl r4, r4, #2
	ldr r4, [r2, r4]
	str r4, [sp, #0x44]
	ldr r4, _0221B8FC ; =0x00FF0000
	ldr r6, [sp, #0x44]
	and r6, r4
	str r6, [sp, #0x44]
	ldr r4, [sp, #0x58]
	eor r4, r6
	str r4, [sp, #0x58]
	eor r7, r4
	ldr r4, [sp, #0x24]
	eor r4, r7
	str r4, [sp, #0x24]
	eor r3, r4
	lsr r6, r3, #0x18
	ldr r4, [sp]
	strb r6, [r4, #4]
	lsr r6, r3, #0x10
	strb r6, [r4, #5]
	lsr r6, r3, #8
	strb r6, [r4, #6]
	strb r3, [r4, #7]
	ldr r3, [r0, #8]
	add r6, r1, #0
	mov r4, #0xff
	and r6, r4
	lsl r4, r6, #2
	ldr r6, [r2, r4]
	str r6, [sp, #0x28]
	mov r4, #0xff
	and r6, r4
	str r6, [sp, #0x28]
	ldr r4, [sp, #0x10]
	lsr r6, r4, #8
	mov r4, #0xff
	and r6, r4
	lsl r4, r6, #2
	ldr r7, [r2, r4]
	ldr r4, _0221B8F4 ; =0x0000FF00
	and r7, r4
	lsr r4, r5, #0x18
	lsl r4, r4, #2
	ldr r4, [r2, r4]
	str r4, [sp, #0x5c]
	ldr r6, _0221B8F8 ; =0xFF000000
	and r4, r6
	str r4, [sp, #0x5c]
	ldr r4, [sp, #0x14]
	lsr r4, r4, #0x10
	str r4, [sp, #0x50]
	mov r6, #0xff
	and r4, r6
	str r4, [sp, #0x50]
	lsl r4, r4, #2
	ldr r4, [r2, r4]
	str r4, [sp, #0x4c]
	ldr r4, _0221B8FC ; =0x00FF0000
	ldr r6, [sp, #0x4c]
	and r6, r4
	str r6, [sp, #0x4c]
	ldr r4, [sp, #0x5c]
	eor r4, r6
	str r4, [sp, #0x5c]
	eor r7, r4
	ldr r4, [sp, #0x28]
	eor r4, r7
	str r4, [sp, #0x28]
	eor r3, r4
	lsr r6, r3, #0x18
	ldr r4, [sp]
	strb r6, [r4, #8]
	lsr r6, r3, #0x10
	strb r6, [r4, #9]
	lsr r6, r3, #8
	strb r6, [r4, #0xa]
	strb r3, [r4, #0xb]
	ldr r6, [r0, #0xc]
	ldr r3, [sp, #0x10]
	mov r0, #0xff
	and r3, r0
	str r3, [sp, #0x10]
	lsl r0, r3, #2
	ldr r4, [r2, r0]
	mov r0, #0xff
	and r4, r0
	ldr r0, [sp, #0x14]
	lsr r3, r0, #8
	mov r0, #0xff
	and r3, r0
	lsl r0, r3, #2
	ldr r3, [r2, r0]
	ldr r0, _0221B8F4 ; =0x0000FF00
	and r3, r0
	lsr r0, r1, #0x18
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	ldr r1, _0221B8F8 ; =0xFF000000
	and r0, r1
	lsr r5, r5, #0x10
	mov r1, #0xff
	and r5, r1
	lsl r1, r5, #2
	ldr r2, [r2, r1]
	ldr r1, _0221B8FC ; =0x00FF0000
	and r2, r1
	eor r0, r2
	eor r3, r0
	eor r4, r3
	eor r6, r4
	lsr r1, r6, #0x18
	ldr r0, [sp]
	strb r1, [r0, #0xc]
	lsr r1, r6, #0x10
	strb r1, [r0, #0xd]
	lsr r1, r6, #8
	strb r1, [r0, #0xe]
	strb r6, [r0, #0xf]
	add sp, #0x60
	pop {r4, r5, r6, r7}
	bx lr
	nop
_0221B8E0: .word MOD13_0223C86C
_0221B8E4: .word MOD13_0223C46C
_0221B8E8: .word MOD13_0223E46C
_0221B8EC: .word MOD13_0223E86C
_0221B8F0: .word MOD13_0223CC6C
_0221B8F4: .word 0x0000FF00
_0221B8F8: .word 0xFF000000
_0221B8FC: .word 0x00FF0000

	thumb_func_start MOD13_0221B900
MOD13_0221B900: ; 0x0221B900
	push {r4, r5, r6, r7}
	sub sp, #0x60
	add r4, r1, #0
	add r1, r2, #0
	str r3, [sp]
	ldr r2, [r0]
	str r2, [sp, #4]
	ldrb r5, [r1, #3]
	ldrb r2, [r1, #2]
	lsl r3, r2, #8
	ldrb r2, [r1]
	lsl r2, r2, #0x18
	ldrb r6, [r1, #1]
	lsl r6, r6, #0x10
	eor r2, r6
	eor r3, r2
	eor r5, r3
	ldr r2, [sp, #4]
	eor r2, r5
	str r2, [sp, #4]
	ldr r2, [r0, #4]
	str r2, [sp, #8]
	ldrb r5, [r1, #7]
	ldrb r2, [r1, #6]
	lsl r3, r2, #8
	ldrb r2, [r1, #4]
	lsl r2, r2, #0x18
	ldrb r6, [r1, #5]
	lsl r6, r6, #0x10
	eor r2, r6
	eor r3, r2
	eor r5, r3
	ldr r2, [sp, #8]
	eor r2, r5
	str r2, [sp, #8]
	ldr r2, [r0, #8]
	str r2, [sp, #0x2c]
	ldrb r5, [r1, #0xb]
	ldrb r2, [r1, #0xa]
	lsl r3, r2, #8
	ldrb r2, [r1, #8]
	lsl r2, r2, #0x18
	ldrb r6, [r1, #9]
	lsl r6, r6, #0x10
	eor r2, r6
	eor r3, r2
	eor r5, r3
	ldr r2, [sp, #0x2c]
	eor r2, r5
	str r2, [sp, #0x2c]
	ldr r6, [r0, #0xc]
	ldrb r5, [r1, #0xf]
	ldrb r2, [r1, #0xe]
	lsl r3, r2, #8
	ldrb r2, [r1, #0xc]
	lsl r2, r2, #0x18
	ldrb r1, [r1, #0xd]
	lsl r1, r1, #0x10
	eor r2, r1
	eor r3, r2
	eor r5, r3
	eor r6, r5
	asr r1, r4, #1
	str r1, [sp, #0xc]
	mov r2, #0xff
_0221B982:
	ldr r1, [r0, #0x10]
	str r1, [sp, #0x10]
	add r1, r6, #0
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221BD00 ; =0x0223DC6C
	ldr r5, [r1, r3]
	ldr r1, [sp, #0x2c]
	lsr r1, r1, #8
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221BD04 ; =0x0223D86C
	ldr r4, [r1, r3]
	ldr r1, [sp, #4]
	lsr r1, r1, #0x18
	lsl r3, r1, #2
	ldr r1, _0221BD08 ; =0x0223D06C
	ldr r7, [r1, r3]
	ldr r1, [sp, #8]
	lsr r1, r1, #0x10
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221BD0C ; =0x0223D46C
	ldr r1, [r1, r3]
	eor r7, r1
	eor r4, r7
	eor r5, r4
	ldr r1, [sp, #0x10]
	eor r1, r5
	str r1, [sp, #0x10]
	ldr r1, [r0, #0x14]
	str r1, [sp, #0x14]
	ldr r1, [sp, #4]
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221BD00 ; =0x0223DC6C
	ldr r5, [r1, r3]
	lsr r1, r6, #8
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221BD04 ; =0x0223D86C
	ldr r4, [r1, r3]
	ldr r1, [sp, #8]
	lsr r1, r1, #0x18
	lsl r3, r1, #2
	ldr r1, _0221BD08 ; =0x0223D06C
	ldr r7, [r1, r3]
	ldr r1, [sp, #0x2c]
	lsr r1, r1, #0x10
	and r1, r2
	lsl r3, r1, #2
	ldr r1, _0221BD0C ; =0x0223D46C
	ldr r1, [r1, r3]
	eor r7, r1
	eor r4, r7
	eor r5, r4
	ldr r1, [sp, #0x14]
	eor r1, r5
	str r1, [sp, #0x14]
	ldr r3, [r0, #0x18]
	ldr r1, [sp, #8]
	and r1, r2
	lsl r4, r1, #2
	ldr r1, _0221BD00 ; =0x0223DC6C
	ldr r1, [r1, r4]
	ldr r4, [sp, #4]
	lsr r4, r4, #8
	and r4, r2
	lsl r5, r4, #2
	ldr r4, _0221BD04 ; =0x0223D86C
	ldr r7, [r4, r5]
	ldr r4, [sp, #0x2c]
	lsr r4, r4, #0x18
	lsl r5, r4, #2
	ldr r4, _0221BD08 ; =0x0223D06C
	ldr r4, [r4, r5]
	str r4, [sp, #0x18]
	lsr r4, r6, #0x10
	and r4, r2
	lsl r5, r4, #2
	ldr r4, _0221BD0C ; =0x0223D46C
	ldr r5, [r4, r5]
	ldr r4, [sp, #0x18]
	eor r4, r5
	str r4, [sp, #0x18]
	eor r7, r4
	eor r1, r7
	eor r3, r1
	ldr r1, [r0, #0x1c]
	ldr r4, [sp, #0x2c]
	and r4, r2
	str r4, [sp, #0x2c]
	lsl r5, r4, #2
	ldr r4, _0221BD00 ; =0x0223DC6C
	ldr r4, [r4, r5]
	str r4, [sp, #0x30]
	ldr r4, [sp, #8]
	lsr r4, r4, #8
	and r4, r2
	lsl r5, r4, #2
	ldr r4, _0221BD04 ; =0x0223D86C
	ldr r7, [r4, r5]
	lsr r4, r6, #0x18
	lsl r5, r4, #2
	ldr r4, _0221BD08 ; =0x0223D06C
	ldr r6, [r4, r5]
	ldr r4, [sp, #4]
	lsr r4, r4, #0x10
	and r4, r2
	lsl r5, r4, #2
	ldr r4, _0221BD0C ; =0x0223D46C
	ldr r4, [r4, r5]
	eor r6, r4
	eor r7, r6
	ldr r4, [sp, #0x30]
	eor r4, r7
	str r4, [sp, #0x30]
	eor r1, r4
	add r0, #0x20
	ldr r4, [sp, #0xc]
	sub r4, r4, #1
	str r4, [sp, #0xc]
	cmp r4, #0
	beq _0221BB6A
	ldr r4, [r0]
	str r4, [sp, #4]
	add r4, r1, #0
	and r4, r2
	lsl r5, r4, #2
	ldr r4, _0221BD00 ; =0x0223DC6C
	ldr r6, [r4, r5]
	lsr r4, r3, #8
	and r4, r2
	lsl r5, r4, #2
	ldr r4, _0221BD04 ; =0x0223D86C
	ldr r4, [r4, r5]
	str r4, [sp, #0x34]
	ldr r4, [sp, #0x10]
	lsr r4, r4, #0x18
	lsl r5, r4, #2
	ldr r4, _0221BD08 ; =0x0223D06C
	ldr r7, [r4, r5]
	ldr r4, [sp, #0x14]
	lsr r4, r4, #0x10
	and r4, r2
	lsl r5, r4, #2
	ldr r4, _0221BD0C ; =0x0223D46C
	ldr r4, [r4, r5]
	eor r7, r4
	ldr r4, [sp, #0x34]
	eor r4, r7
	str r4, [sp, #0x34]
	eor r6, r4
	ldr r4, [sp, #4]
	eor r4, r6
	str r4, [sp, #4]
	ldr r4, [r0, #4]
	str r4, [sp, #8]
	ldr r4, [sp, #0x10]
	and r4, r2
	lsl r5, r4, #2
	ldr r4, _0221BD00 ; =0x0223DC6C
	ldr r6, [r4, r5]
	lsr r4, r1, #8
	and r4, r2
	lsl r5, r4, #2
	ldr r4, _0221BD04 ; =0x0223D86C
	ldr r4, [r4, r5]
	str r4, [sp, #0x38]
	ldr r4, [sp, #0x14]
	lsr r4, r4, #0x18
	lsl r5, r4, #2
	ldr r4, _0221BD08 ; =0x0223D06C
	ldr r7, [r4, r5]
	lsr r4, r3, #0x10
	and r4, r2
	lsl r5, r4, #2
	ldr r4, _0221BD0C ; =0x0223D46C
	ldr r4, [r4, r5]
	eor r7, r4
	ldr r4, [sp, #0x38]
	eor r4, r7
	str r4, [sp, #0x38]
	eor r6, r4
	ldr r4, [sp, #8]
	eor r4, r6
	str r4, [sp, #8]
	ldr r4, [r0, #8]
	str r4, [sp, #0x2c]
	ldr r4, [sp, #0x14]
	and r4, r2
	lsl r5, r4, #2
	ldr r4, _0221BD00 ; =0x0223DC6C
	ldr r4, [r4, r5]
	ldr r5, [sp, #0x10]
	lsr r5, r5, #8
	and r5, r2
	lsl r6, r5, #2
	ldr r5, _0221BD04 ; =0x0223D86C
	ldr r7, [r5, r6]
	lsr r5, r3, #0x18
	lsl r6, r5, #2
	ldr r5, _0221BD08 ; =0x0223D06C
	ldr r5, [r5, r6]
	str r5, [sp, #0x1c]
	lsr r5, r1, #0x10
	and r5, r2
	lsl r6, r5, #2
	ldr r5, _0221BD0C ; =0x0223D46C
	ldr r6, [r5, r6]
	ldr r5, [sp, #0x1c]
	eor r5, r6
	str r5, [sp, #0x1c]
	eor r7, r5
	eor r4, r7
	ldr r5, [sp, #0x2c]
	eor r5, r4
	str r5, [sp, #0x2c]
	ldr r6, [r0, #0xc]
	and r3, r2
	lsl r4, r3, #2
	ldr r3, _0221BD00 ; =0x0223DC6C
	ldr r3, [r3, r4]
	ldr r4, [sp, #0x14]
	lsr r4, r4, #8
	and r4, r2
	lsl r5, r4, #2
	ldr r4, _0221BD04 ; =0x0223D86C
	ldr r7, [r4, r5]
	lsr r1, r1, #0x18
	lsl r4, r1, #2
	ldr r1, _0221BD08 ; =0x0223D06C
	ldr r5, [r1, r4]
	ldr r1, [sp, #0x10]
	lsr r1, r1, #0x10
	and r1, r2
	lsl r4, r1, #2
	ldr r1, _0221BD0C ; =0x0223D46C
	ldr r1, [r1, r4]
	eor r5, r1
	eor r7, r5
	eor r3, r7
	eor r6, r3
	b _0221B982
_0221BB6A:
	ldr r4, [r0]
	add r5, r1, #0
	mov r2, #0xff
	and r5, r2
	lsl r5, r5, #2
	ldr r2, _0221BD10 ; =0x0223E06C
	ldr r6, [r2, r5]
	str r6, [sp, #0x20]
	mov r5, #0xff
	and r6, r5
	str r6, [sp, #0x20]
	lsr r6, r3, #8
	and r6, r5
	lsl r5, r6, #2
	ldr r7, [r2, r5]
	ldr r5, _0221BD14 ; =0x0000FF00
	and r7, r5
	ldr r5, [sp, #0x10]
	lsr r5, r5, #0x18
	lsl r5, r5, #2
	ldr r5, [r2, r5]
	str r5, [sp, #0x54]
	ldr r6, _0221BD18 ; =0xFF000000
	and r5, r6
	str r5, [sp, #0x54]
	ldr r5, [sp, #0x14]
	lsr r5, r5, #0x10
	str r5, [sp, #0x40]
	mov r6, #0xff
	and r5, r6
	str r5, [sp, #0x40]
	lsl r5, r5, #2
	ldr r5, [r2, r5]
	str r5, [sp, #0x3c]
	ldr r5, _0221BD1C ; =0x00FF0000
	ldr r6, [sp, #0x3c]
	and r6, r5
	str r6, [sp, #0x3c]
	ldr r5, [sp, #0x54]
	eor r5, r6
	str r5, [sp, #0x54]
	eor r7, r5
	ldr r5, [sp, #0x20]
	eor r5, r7
	str r5, [sp, #0x20]
	eor r4, r5
	lsr r6, r4, #0x18
	ldr r5, [sp]
	strb r6, [r5]
	lsr r6, r4, #0x10
	strb r6, [r5, #1]
	lsr r6, r4, #8
	strb r6, [r5, #2]
	strb r4, [r5, #3]
	ldr r4, [r0, #4]
	ldr r6, [sp, #0x10]
	mov r5, #0xff
	and r6, r5
	lsl r5, r6, #2
	ldr r6, [r2, r5]
	str r6, [sp, #0x24]
	mov r5, #0xff
	and r6, r5
	str r6, [sp, #0x24]
	lsr r6, r1, #8
	and r6, r5
	lsl r5, r6, #2
	ldr r7, [r2, r5]
	ldr r5, _0221BD14 ; =0x0000FF00
	and r7, r5
	ldr r5, [sp, #0x14]
	lsr r5, r5, #0x18
	lsl r5, r5, #2
	ldr r5, [r2, r5]
	str r5, [sp, #0x58]
	ldr r6, _0221BD18 ; =0xFF000000
	and r5, r6
	str r5, [sp, #0x58]
	lsr r5, r3, #0x10
	str r5, [sp, #0x48]
	mov r6, #0xff
	and r5, r6
	str r5, [sp, #0x48]
	lsl r5, r5, #2
	ldr r5, [r2, r5]
	str r5, [sp, #0x44]
	ldr r5, _0221BD1C ; =0x00FF0000
	ldr r6, [sp, #0x44]
	and r6, r5
	str r6, [sp, #0x44]
	ldr r5, [sp, #0x58]
	eor r5, r6
	str r5, [sp, #0x58]
	eor r7, r5
	ldr r5, [sp, #0x24]
	eor r5, r7
	str r5, [sp, #0x24]
	eor r4, r5
	lsr r6, r4, #0x18
	ldr r5, [sp]
	strb r6, [r5, #4]
	lsr r6, r4, #0x10
	strb r6, [r5, #5]
	lsr r6, r4, #8
	strb r6, [r5, #6]
	strb r4, [r5, #7]
	ldr r4, [r0, #8]
	ldr r6, [sp, #0x14]
	mov r5, #0xff
	and r6, r5
	lsl r5, r6, #2
	ldr r6, [r2, r5]
	str r6, [sp, #0x28]
	mov r5, #0xff
	and r6, r5
	str r6, [sp, #0x28]
	ldr r5, [sp, #0x10]
	lsr r6, r5, #8
	mov r5, #0xff
	and r6, r5
	lsl r5, r6, #2
	ldr r7, [r2, r5]
	ldr r5, _0221BD14 ; =0x0000FF00
	and r7, r5
	lsr r5, r3, #0x18
	lsl r5, r5, #2
	ldr r5, [r2, r5]
	str r5, [sp, #0x5c]
	ldr r6, _0221BD18 ; =0xFF000000
	and r5, r6
	str r5, [sp, #0x5c]
	lsr r5, r1, #0x10
	str r5, [sp, #0x50]
	mov r6, #0xff
	and r5, r6
	str r5, [sp, #0x50]
	lsl r5, r5, #2
	ldr r5, [r2, r5]
	str r5, [sp, #0x4c]
	ldr r5, _0221BD1C ; =0x00FF0000
	ldr r6, [sp, #0x4c]
	and r6, r5
	str r6, [sp, #0x4c]
	ldr r5, [sp, #0x5c]
	eor r5, r6
	str r5, [sp, #0x5c]
	eor r7, r5
	ldr r5, [sp, #0x28]
	eor r5, r7
	str r5, [sp, #0x28]
	eor r4, r5
	lsr r6, r4, #0x18
	ldr r5, [sp]
	strb r6, [r5, #8]
	lsr r6, r4, #0x10
	strb r6, [r5, #9]
	lsr r6, r4, #8
	strb r6, [r5, #0xa]
	strb r4, [r5, #0xb]
	ldr r5, [r0, #0xc]
	mov r0, #0xff
	and r3, r0
	lsl r0, r3, #2
	ldr r4, [r2, r0]
	mov r0, #0xff
	and r4, r0
	ldr r0, [sp, #0x14]
	lsr r3, r0, #8
	mov r0, #0xff
	and r3, r0
	lsl r0, r3, #2
	ldr r3, [r2, r0]
	ldr r0, _0221BD14 ; =0x0000FF00
	and r3, r0
	lsr r0, r1, #0x18
	lsl r0, r0, #2
	ldr r0, [r2, r0]
	ldr r1, _0221BD18 ; =0xFF000000
	and r0, r1
	ldr r1, [sp, #0x10]
	lsr r6, r1, #0x10
	mov r1, #0xff
	and r6, r1
	lsl r1, r6, #2
	ldr r2, [r2, r1]
	ldr r1, _0221BD1C ; =0x00FF0000
	and r2, r1
	eor r0, r2
	eor r3, r0
	eor r4, r3
	eor r5, r4
	lsr r1, r5, #0x18
	ldr r0, [sp]
	strb r1, [r0, #0xc]
	lsr r1, r5, #0x10
	strb r1, [r0, #0xd]
	lsr r1, r5, #8
	strb r1, [r0, #0xe]
	strb r5, [r0, #0xf]
	add sp, #0x60
	pop {r4, r5, r6, r7}
	bx lr
	nop
_0221BD00: .word MOD13_0223DC6C
_0221BD04: .word MOD13_0223D86C
_0221BD08: .word MOD13_0223D06C
_0221BD0C: .word MOD13_0223D46C
_0221BD10: .word MOD13_0223E06C
_0221BD14: .word 0x0000FF00
_0221BD18: .word 0xFF000000
_0221BD1C: .word 0x00FF0000

	thumb_func_start MOD13_0221BD20
MOD13_0221BD20: ; 0x0221BD20
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r4, r0, #0
	bl MOD13_0221BEE4
	str r0, [sp]
	mov r6, #0
	lsl r5, r0, #2
	cmp r5, #0
	ble _0221BD84
	str r4, [sp, #4]
	lsl r0, r5, #2
	add r3, r4, r0
_0221BD3A:
	ldr r0, [sp, #4]
	ldr r2, [r0]
	ldr r1, [r3]
	str r1, [r0]
	str r2, [r3]
	add r0, r6, #1
	lsl r2, r0, #2
	ldr r1, [r4, r2]
	add r0, r5, #1
	lsl r7, r0, #2
	ldr r0, [r4, r7]
	str r0, [r4, r2]
	str r1, [r4, r7]
	add r0, r6, #2
	lsl r2, r0, #2
	ldr r1, [r4, r2]
	add r0, r5, #2
	lsl r7, r0, #2
	ldr r0, [r4, r7]
	str r0, [r4, r2]
	str r1, [r4, r7]
	add r0, r6, #3
	lsl r2, r0, #2
	ldr r1, [r4, r2]
	add r0, r5, #3
	lsl r7, r0, #2
	ldr r0, [r4, r7]
	str r0, [r4, r2]
	str r1, [r4, r7]
	ldr r0, [sp, #4]
	add r0, #0x10
	str r0, [sp, #4]
	add r6, r6, #4
	sub r3, #0x10
	sub r5, r5, #4
	cmp r6, r5
	blt _0221BD3A
_0221BD84:
	mov r0, #1
	str r0, [sp, #8]
	ldr r0, [sp]
	cmp r0, #1
	bgt _0221BD90
	b _0221BEC4
_0221BD90:
	ldr r2, _0221BED0 ; =0x0223E06C
	mov r0, #0xff
_0221BD94:
	add r4, #0x10
	ldr r5, [r4]
	add r1, r5, #0
	and r1, r0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	and r1, r0
	lsl r3, r1, #2
	ldr r1, _0221BED4 ; =0x0223C86C
	ldr r3, [r1, r3]
	lsr r1, r5, #8
	and r1, r0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	and r1, r0
	lsl r6, r1, #2
	ldr r1, _0221BED8 ; =0x0223C46C
	ldr r7, [r1, r6]
	lsr r1, r5, #0x18
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	and r1, r0
	lsl r6, r1, #2
	ldr r1, _0221BEDC ; =0x0223E46C
	ldr r1, [r1, r6]
	lsr r5, r5, #0x10
	and r5, r0
	lsl r5, r5, #2
	ldr r5, [r2, r5]
	and r5, r0
	lsl r6, r5, #2
	ldr r5, _0221BEE0 ; =0x0223E86C
	ldr r5, [r5, r6]
	eor r1, r5
	eor r7, r1
	eor r3, r7
	str r3, [r4]
	ldr r5, [r4, #4]
	add r1, r5, #0
	and r1, r0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	and r1, r0
	lsl r3, r1, #2
	ldr r1, _0221BED4 ; =0x0223C86C
	ldr r3, [r1, r3]
	lsr r1, r5, #8
	and r1, r0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	and r1, r0
	lsl r6, r1, #2
	ldr r1, _0221BED8 ; =0x0223C46C
	ldr r7, [r1, r6]
	lsr r1, r5, #0x18
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	and r1, r0
	lsl r6, r1, #2
	ldr r1, _0221BEDC ; =0x0223E46C
	ldr r1, [r1, r6]
	lsr r5, r5, #0x10
	and r5, r0
	lsl r5, r5, #2
	ldr r5, [r2, r5]
	and r5, r0
	lsl r6, r5, #2
	ldr r5, _0221BEE0 ; =0x0223E86C
	ldr r5, [r5, r6]
	eor r1, r5
	eor r7, r1
	eor r3, r7
	str r3, [r4, #4]
	ldr r5, [r4, #8]
	add r1, r5, #0
	and r1, r0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	and r1, r0
	lsl r3, r1, #2
	ldr r1, _0221BED4 ; =0x0223C86C
	ldr r3, [r1, r3]
	lsr r1, r5, #8
	and r1, r0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	and r1, r0
	lsl r6, r1, #2
	ldr r1, _0221BED8 ; =0x0223C46C
	ldr r7, [r1, r6]
	lsr r1, r5, #0x18
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	and r1, r0
	lsl r6, r1, #2
	ldr r1, _0221BEDC ; =0x0223E46C
	ldr r1, [r1, r6]
	lsr r5, r5, #0x10
	and r5, r0
	lsl r5, r5, #2
	ldr r5, [r2, r5]
	and r5, r0
	lsl r6, r5, #2
	ldr r5, _0221BEE0 ; =0x0223E86C
	ldr r5, [r5, r6]
	eor r1, r5
	eor r7, r1
	eor r3, r7
	str r3, [r4, #8]
	ldr r5, [r4, #0xc]
	add r1, r5, #0
	and r1, r0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	and r1, r0
	lsl r3, r1, #2
	ldr r1, _0221BED4 ; =0x0223C86C
	ldr r3, [r1, r3]
	lsr r1, r5, #8
	and r1, r0
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	and r1, r0
	lsl r6, r1, #2
	ldr r1, _0221BED8 ; =0x0223C46C
	ldr r7, [r1, r6]
	lsr r1, r5, #0x18
	lsl r1, r1, #2
	ldr r1, [r2, r1]
	and r1, r0
	lsl r6, r1, #2
	ldr r1, _0221BEDC ; =0x0223E46C
	ldr r1, [r1, r6]
	lsr r5, r5, #0x10
	and r5, r0
	lsl r5, r5, #2
	ldr r5, [r2, r5]
	and r5, r0
	lsl r6, r5, #2
	ldr r5, _0221BEE0 ; =0x0223E86C
	ldr r5, [r5, r6]
	eor r1, r5
	eor r7, r1
	eor r3, r7
	str r3, [r4, #0xc]
	ldr r1, [sp, #8]
	add r3, r1, #1
	str r3, [sp, #8]
	ldr r1, [sp]
	cmp r3, r1
	bge _0221BEC4
	b _0221BD94
_0221BEC4:
	ldr r0, [sp]
	add sp, #0xc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_0221BED0: .word MOD13_0223E06C
_0221BED4: .word MOD13_0223C86C
_0221BED8: .word MOD13_0223C46C
_0221BEDC: .word MOD13_0223E46C
_0221BEE0: .word MOD13_0223E86C

	thumb_func_start MOD13_0221BEE4
MOD13_0221BEE4: ; 0x0221BEE4
	push {r4, r5, r6, r7}
	sub sp, #0x20
	add r3, r1, #0
	add r1, r2, #0
	mov r2, #0
	str r2, [sp]
	ldrb r5, [r3, #3]
	ldrb r2, [r3, #2]
	lsl r4, r2, #8
	ldrb r2, [r3]
	lsl r2, r2, #0x18
	ldrb r6, [r3, #1]
	lsl r6, r6, #0x10
	eor r2, r6
	eor r4, r2
	eor r5, r4
	str r5, [r0]
	ldrb r5, [r3, #7]
	ldrb r2, [r3, #6]
	lsl r4, r2, #8
	ldrb r2, [r3, #4]
	lsl r2, r2, #0x18
	ldrb r6, [r3, #5]
	lsl r6, r6, #0x10
	eor r2, r6
	eor r4, r2
	eor r5, r4
	str r5, [r0, #4]
	ldrb r5, [r3, #0xb]
	ldrb r2, [r3, #0xa]
	lsl r4, r2, #8
	ldrb r2, [r3, #8]
	lsl r2, r2, #0x18
	ldrb r6, [r3, #9]
	lsl r6, r6, #0x10
	eor r2, r6
	eor r4, r2
	eor r5, r4
	str r5, [r0, #8]
	ldrb r5, [r3, #0xf]
	ldrb r2, [r3, #0xe]
	lsl r4, r2, #8
	ldrb r2, [r3, #0xc]
	lsl r2, r2, #0x18
	ldrb r6, [r3, #0xd]
	lsl r6, r6, #0x10
	eor r2, r6
	eor r4, r2
	eor r5, r4
	str r5, [r0, #0xc]
	cmp r1, #0x80
	bne _0221BFD0
	ldr r6, _0221C1B4 ; =0x0223C444
_0221BF4E:
	ldr r5, [r0, #0xc]
	ldr r1, [r6]
	str r1, [sp, #0xc]
	lsr r1, r5, #0x18
	lsl r2, r1, #2
	ldr r1, _0221C1B8 ; =0x0223E06C
	ldr r4, [r1, r2]
	mov r1, #0xff
	and r4, r1
	add r2, r5, #0
	and r2, r1
	lsl r2, r2, #2
	ldr r1, _0221C1B8 ; =0x0223E06C
	ldr r7, [r1, r2]
	ldr r1, _0221C1BC ; =0x0000FF00
	and r7, r1
	ldr r3, [r0]
	lsr r2, r5, #0x10
	mov r1, #0xff
	and r2, r1
	lsl r2, r2, #2
	ldr r1, _0221C1B8 ; =0x0223E06C
	ldr r2, [r1, r2]
	ldr r1, _0221C1C0 ; =0xFF000000
	and r2, r1
	eor r3, r2
	lsr r2, r5, #8
	mov r1, #0xff
	and r2, r1
	lsl r2, r2, #2
	ldr r1, _0221C1B8 ; =0x0223E06C
	ldr r2, [r1, r2]
	ldr r1, _0221C1C4 ; =0x00FF0000
	and r2, r1
	eor r3, r2
	eor r7, r3
	eor r4, r7
	ldr r1, [sp, #0xc]
	eor r1, r4
	str r1, [sp, #0xc]
	str r1, [r0, #0x10]
	ldr r2, [r0, #4]
	ldr r1, [r0, #0x10]
	eor r2, r1
	str r2, [r0, #0x14]
	ldr r2, [r0, #8]
	ldr r1, [r0, #0x14]
	eor r2, r1
	str r2, [r0, #0x18]
	ldr r2, [r0, #0xc]
	ldr r1, [r0, #0x18]
	eor r2, r1
	str r2, [r0, #0x1c]
	add r6, r6, #4
	ldr r1, [sp]
	add r1, r1, #1
	str r1, [sp]
	cmp r1, #0xa
	blt _0221BFCC
	mov r0, #0xa
	add sp, #0x20
	pop {r4, r5, r6, r7}
	bx lr
_0221BFCC:
	add r0, #0x10
	b _0221BF4E
_0221BFD0:
	ldrb r5, [r3, #0x13]
	ldrb r2, [r3, #0x12]
	lsl r4, r2, #8
	ldrb r2, [r3, #0x10]
	lsl r2, r2, #0x18
	ldrb r6, [r3, #0x11]
	lsl r6, r6, #0x10
	eor r2, r6
	eor r4, r2
	eor r5, r4
	str r5, [r0, #0x10]
	ldrb r5, [r3, #0x17]
	ldrb r2, [r3, #0x16]
	lsl r4, r2, #8
	ldrb r2, [r3, #0x14]
	lsl r2, r2, #0x18
	ldrb r6, [r3, #0x15]
	lsl r6, r6, #0x10
	eor r2, r6
	eor r4, r2
	eor r5, r4
	str r5, [r0, #0x14]
	cmp r1, #0xc0
	bne _0221C094
	ldr r6, _0221C1B4 ; =0x0223C444
_0221C002:
	ldr r5, [r0, #0x14]
	ldr r1, [r6]
	str r1, [sp, #0x10]
	lsr r1, r5, #0x18
	lsl r2, r1, #2
	ldr r1, _0221C1B8 ; =0x0223E06C
	ldr r4, [r1, r2]
	mov r1, #0xff
	and r4, r1
	add r2, r5, #0
	and r2, r1
	lsl r2, r2, #2
	ldr r1, _0221C1B8 ; =0x0223E06C
	ldr r7, [r1, r2]
	ldr r1, _0221C1BC ; =0x0000FF00
	and r7, r1
	ldr r3, [r0]
	lsr r2, r5, #0x10
	mov r1, #0xff
	and r2, r1
	lsl r2, r2, #2
	ldr r1, _0221C1B8 ; =0x0223E06C
	ldr r2, [r1, r2]
	ldr r1, _0221C1C0 ; =0xFF000000
	and r2, r1
	eor r3, r2
	lsr r2, r5, #8
	mov r1, #0xff
	and r2, r1
	lsl r2, r2, #2
	ldr r1, _0221C1B8 ; =0x0223E06C
	ldr r2, [r1, r2]
	ldr r1, _0221C1C4 ; =0x00FF0000
	and r2, r1
	eor r3, r2
	eor r7, r3
	eor r4, r7
	ldr r1, [sp, #0x10]
	eor r1, r4
	str r1, [sp, #0x10]
	str r1, [r0, #0x18]
	ldr r2, [r0, #4]
	ldr r1, [r0, #0x18]
	eor r2, r1
	str r2, [r0, #0x1c]
	ldr r2, [r0, #8]
	ldr r1, [r0, #0x1c]
	eor r2, r1
	str r2, [r0, #0x20]
	ldr r2, [r0, #0xc]
	ldr r1, [r0, #0x20]
	eor r2, r1
	str r2, [r0, #0x24]
	add r6, r6, #4
	ldr r1, [sp]
	add r1, r1, #1
	str r1, [sp]
	cmp r1, #8
	blt _0221C080
	mov r0, #0xc
	add sp, #0x20
	pop {r4, r5, r6, r7}
	bx lr
_0221C080:
	ldr r2, [r0, #0x10]
	ldr r1, [r0, #0x24]
	eor r2, r1
	str r2, [r0, #0x28]
	ldr r2, [r0, #0x14]
	ldr r1, [r0, #0x28]
	eor r2, r1
	str r2, [r0, #0x2c]
	add r0, #0x18
	b _0221C002
_0221C094:
	ldrb r5, [r3, #0x1b]
	ldrb r2, [r3, #0x1a]
	lsl r4, r2, #8
	ldrb r2, [r3, #0x18]
	lsl r2, r2, #0x18
	ldrb r6, [r3, #0x19]
	lsl r6, r6, #0x10
	eor r2, r6
	eor r4, r2
	eor r5, r4
	str r5, [r0, #0x18]
	ldrb r5, [r3, #0x1f]
	ldrb r2, [r3, #0x1e]
	lsl r4, r2, #8
	ldrb r2, [r3, #0x1c]
	lsl r2, r2, #0x18
	ldrb r3, [r3, #0x1d]
	lsl r3, r3, #0x10
	eor r2, r3
	eor r4, r2
	eor r5, r4
	str r5, [r0, #0x1c]
	ldr r2, _0221C1C8 ; =0x00000100
	cmp r1, r2
	bne _0221C1AC
	ldr r1, _0221C1B4 ; =0x0223C444
	str r1, [sp, #4]
	ldr r7, _0221C1B8 ; =0x0223E06C
_0221C0CC:
	ldr r6, [r0, #0x1c]
	ldr r1, [sp, #4]
	ldr r1, [r1]
	str r1, [sp, #8]
	lsr r1, r6, #0x18
	lsl r1, r1, #2
	ldr r5, [r7, r1]
	mov r1, #0xff
	and r5, r1
	add r2, r6, #0
	and r2, r1
	lsl r1, r2, #2
	ldr r4, [r7, r1]
	ldr r1, _0221C1BC ; =0x0000FF00
	and r4, r1
	ldr r3, [r0]
	lsr r2, r6, #0x10
	mov r1, #0xff
	and r2, r1
	lsl r1, r2, #2
	ldr r1, [r7, r1]
	str r1, [sp, #0x14]
	ldr r2, _0221C1C0 ; =0xFF000000
	and r1, r2
	str r1, [sp, #0x14]
	eor r3, r1
	lsr r2, r6, #8
	mov r1, #0xff
	and r2, r1
	lsl r1, r2, #2
	ldr r2, [r7, r1]
	ldr r1, _0221C1C4 ; =0x00FF0000
	and r2, r1
	eor r3, r2
	eor r4, r3
	eor r5, r4
	ldr r1, [sp, #8]
	eor r1, r5
	str r1, [sp, #8]
	str r1, [r0, #0x20]
	ldr r2, [r0, #4]
	ldr r1, [r0, #0x20]
	eor r2, r1
	str r2, [r0, #0x24]
	ldr r2, [r0, #8]
	ldr r1, [r0, #0x24]
	eor r2, r1
	str r2, [r0, #0x28]
	ldr r2, [r0, #0xc]
	ldr r1, [r0, #0x28]
	eor r2, r1
	str r2, [r0, #0x2c]
	ldr r1, [sp, #4]
	add r1, r1, #4
	str r1, [sp, #4]
	ldr r1, [sp]
	add r1, r1, #1
	str r1, [sp]
	cmp r1, #7
	blt _0221C14C
	mov r0, #0xe
	add sp, #0x20
	pop {r4, r5, r6, r7}
	bx lr
_0221C14C:
	ldr r6, [r0, #0x2c]
	add r2, r6, #0
	mov r1, #0xff
	and r2, r1
	lsl r1, r2, #2
	ldr r5, [r7, r1]
	mov r1, #0xff
	and r5, r1
	lsr r2, r6, #8
	and r2, r1
	lsl r1, r2, #2
	ldr r4, [r7, r1]
	ldr r1, _0221C1BC ; =0x0000FF00
	and r4, r1
	ldr r3, [r0, #0x10]
	lsr r1, r6, #0x18
	lsl r1, r1, #2
	ldr r1, [r7, r1]
	str r1, [sp, #0x18]
	ldr r2, _0221C1C0 ; =0xFF000000
	and r1, r2
	str r1, [sp, #0x18]
	eor r3, r1
	lsr r2, r6, #0x10
	mov r1, #0xff
	and r2, r1
	lsl r1, r2, #2
	ldr r2, [r7, r1]
	ldr r1, _0221C1C4 ; =0x00FF0000
	and r2, r1
	eor r3, r2
	eor r4, r3
	eor r5, r4
	str r5, [r0, #0x30]
	ldr r2, [r0, #0x14]
	ldr r1, [r0, #0x30]
	eor r2, r1
	str r2, [r0, #0x34]
	ldr r2, [r0, #0x18]
	ldr r1, [r0, #0x34]
	eor r2, r1
	str r2, [r0, #0x38]
	ldr r2, [r0, #0x1c]
	ldr r1, [r0, #0x38]
	eor r2, r1
	str r2, [r0, #0x3c]
	add r0, #0x20
	b _0221C0CC
_0221C1AC:
	ldr r0, [sp]
	add sp, #0x20
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
_0221C1B4: .word MOD13_0223C444
_0221C1B8: .word MOD13_0223E06C
_0221C1BC: .word 0x0000FF00
_0221C1C0: .word 0xFF000000
_0221C1C4: .word 0x00FF0000
_0221C1C8: .word 0x00000100

	thumb_func_start MOD13_0221C1CC
MOD13_0221C1CC: ; 0x0221C1CC
	push {r4}
	sub sp, #4
	ldrb r4, [r0]
	ldrb r3, [r1]
	eor r4, r3
	strb r4, [r2]
	ldrb r4, [r0, #1]
	ldrb r3, [r1, #1]
	eor r4, r3
	strb r4, [r2, #1]
	ldrb r4, [r0, #2]
	ldrb r3, [r1, #2]
	eor r4, r3
	strb r4, [r2, #2]
	ldrb r4, [r0, #3]
	ldrb r3, [r1, #3]
	eor r4, r3
	strb r4, [r2, #3]
	ldrb r4, [r0, #4]
	ldrb r3, [r1, #4]
	eor r4, r3
	strb r4, [r2, #4]
	ldrb r4, [r0, #5]
	ldrb r3, [r1, #5]
	eor r4, r3
	strb r4, [r2, #5]
	ldrb r4, [r0, #6]
	ldrb r3, [r1, #6]
	eor r4, r3
	strb r4, [r2, #6]
	ldrb r3, [r0, #7]
	ldrb r0, [r1, #7]
	eor r3, r0
	strb r3, [r2, #7]
	add sp, #4
	pop {r4}
	bx lr
	.align 2, 0

	thumb_func_start MOD13_0221C218
MOD13_0221C218: ; 0x0221C218
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1b4
	str r0, [sp]
	add r5, r1, #0
	add r4, r2, #0
	mov r0, #1
	str r0, [sp, #0x1c]
	ldr r0, _0221C3FC ; =0xA6A6A6A6
	str r0, [sp, #0x58]
	str r0, [sp, #0x5c]
	mov r0, #7
	add r1, r4, #0
	and r1, r0
	cmp r1, #0
	bne _0221C240
	ldr r2, [sp, #0x1c8]
	add r1, r2, #0
	and r1, r0
	cmp r1, #0
	beq _0221C24A
_0221C240:
	mov r0, #0
	add sp, #0x1b4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221C24A:
	sub r0, r4, #1
	lsr r0, r0, #3
	str r0, [sp, #0x14]
	cmp r0, #2
	bge _0221C25E
	mov r0, #0
	add sp, #0x1b4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221C25E:
	add r0, sp, #0x70
	add r1, r3, #0
	lsl r2, r2, #3
	bl MOD13_0221BD20
	str r0, [sp, #0x18]
	add r3, sp, #0x60
	add r2, r5, #0
	mov r1, #8
_0221C270:
	ldrb r0, [r2]
	add r2, r2, #1
	strb r0, [r3]
	add r3, r3, #1
	sub r1, r1, #1
	cmp r1, #0
	bne _0221C270
	ldr r0, [sp]
	add r5, #8
	add r1, r5, #0
	sub r2, r4, #1
	bl memcpy
	mov r0, #5
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	asr r0, r0, #0x1f
	str r0, [sp, #0x24]
_0221C294:
	ldr r0, [sp, #0x14]
	str r0, [sp, #0xc]
	cmp r0, #0
	bgt _0221C29E
	b _0221C3D4
_0221C29E:
	ldr r1, [sp, #0x24]
	ldr r2, [sp, #0x10]
	asr r3, r2, #0x1f
	bl _ll_mul
	str r0, [sp, #0x28]
	str r1, [sp, #8]
_0221C2AC:
	ldr r0, [sp, #0xc]
	asr r1, r0, #0x1f
	lsl r2, r0, #0
	ldr r0, [sp, #0x28]
	add r6, r2, r0
	ldr r0, [sp, #8]
	adc r1, r0
	add r2, r1, #0
	ldr r0, _0221C400 ; =0xFF000000
	and r2, r0
	lsr r0, r2, #0x18
	str r0, [sp, #0x30]
	add r2, r1, #0
	ldr r0, _0221C404 ; =0x00FF0000
	and r2, r0
	lsr r0, r2, #8
	str r0, [sp, #0x48]
	add r2, r1, #0
	ldr r0, _0221C408 ; =0x0000FF00
	and r2, r0
	add r3, r6, #0
	mov r0, #0
	and r3, r0
	lsl r0, r2, #8
	lsr r5, r3, #0x18
	orr r5, r0
	lsr r0, r2, #0x18
	str r0, [sp, #0x34]
	add r0, r1, #0
	mov r2, #0xff
	and r0, r2
	add r3, r6, #0
	mov r2, #0
	and r3, r2
	lsl r2, r0, #0x18
	lsr r4, r3, #8
	orr r4, r2
	lsr r0, r0, #8
	str r0, [sp, #0x38]
	add r3, r1, #0
	mov r0, #0
	and r3, r0
	add r0, r6, #0
	ldr r2, _0221C400 ; =0xFF000000
	and r0, r2
	lsr r2, r0, #0x18
	lsl r3, r3, #8
	orr r3, r2
	lsl r0, r0, #8
	str r0, [sp, #0x4c]
	mov r0, #0
	and r1, r0
	add r0, r6, #0
	ldr r2, _0221C404 ; =0x00FF0000
	and r0, r2
	lsr r2, r0, #8
	str r2, [sp, #0x44]
	lsl r2, r1, #0x18
	ldr r1, [sp, #0x44]
	orr r2, r1
	lsl r7, r0, #0x18
	add r1, r6, #0
	str r1, [sp, #0x40]
	mov r0, #0xff
	and r1, r0
	str r1, [sp, #0x40]
	lsl r0, r1, #0x18
	str r0, [sp, #0x3c]
	ldr r0, _0221C408 ; =0x0000FF00
	and r6, r0
	lsl r1, r6, #8
	ldr r0, [sp, #0x3c]
	orr r0, r1
	str r0, [sp, #0x3c]
	mov r0, #0
	lsl r1, r0, #0
	orr r0, r1
	ldr r1, [sp, #0x3c]
	orr r2, r1
	orr r7, r0
	orr r3, r2
	ldr r0, [sp, #0x4c]
	orr r0, r7
	str r0, [sp, #0x4c]
	ldr r0, [sp, #0x38]
	orr r0, r3
	str r0, [sp, #0x38]
	ldr r0, [sp, #0x4c]
	orr r4, r0
	ldr r1, [sp, #0x34]
	ldr r0, [sp, #0x38]
	orr r1, r0
	str r1, [sp, #0x34]
	orr r5, r4
	mov r1, #0
	ldr r0, [sp, #0x34]
	orr r1, r0
	ldr r0, [sp, #0x48]
	orr r0, r5
	str r0, [sp, #0x48]
	mov r2, #0
	orr r2, r1
	ldr r1, [sp, #0x30]
	orr r1, r0
	str r1, [sp, #0x30]
	str r1, [sp, #0x50]
	str r2, [sp, #0x54]
	add r0, sp, #0x60
	add r1, sp, #0x50
	lsl r2, r0, #0
	bl MOD13_0221C1CC
	ldr r0, [sp, #0xc]
	sub r0, r0, #1
	lsl r1, r0, #3
	ldr r0, [sp]
	add r4, r0, r1
	add r3, r4, #0
	add r2, sp, #0x68
	mov r1, #8
_0221C39C:
	ldrb r0, [r3]
	add r3, r3, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	cmp r1, #0
	bne _0221C39C
	add r0, sp, #0x70
	ldr r1, [sp, #0x18]
	add r2, sp, #0x60
	lsl r3, r2, #0
	bl MOD13_0221B4D8
	add r2, sp, #0x68
	mov r1, #8
_0221C3BA:
	ldrb r0, [r2]
	add r2, r2, #1
	strb r0, [r4]
	add r4, r4, #1
	sub r1, r1, #1
	cmp r1, #0
	bne _0221C3BA
	ldr r0, [sp, #0xc]
	sub r0, r0, #1
	str r0, [sp, #0xc]
	cmp r0, #0
	ble _0221C3D4
	b _0221C2AC
_0221C3D4:
	ldr r0, [sp, #0x10]
	sub r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, #0
	blt _0221C3E0
	b _0221C294
_0221C3E0:
	add r0, sp, #0x58
	add r1, sp, #0x60
	mov r2, #8
	bl memcmp
	cmp r0, #0
	beq _0221C3F2
	mov r0, #0
	str r0, [sp, #0x1c]
_0221C3F2:
	ldr r0, [sp, #0x1c]
	add sp, #0x1b4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_0221C3FC: .word 0xA6A6A6A6
_0221C400: .word 0xFF000000
_0221C404: .word 0x00FF0000
_0221C408: .word 0x0000FF00

	thumb_func_start MOD13_0221C40C
MOD13_0221C40C: ; 0x0221C40C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1d4
	str r0, [sp]
	add r5, r1, #0
	add r4, r2, #0
	ldr r0, _0221C608 ; =0xA6A6A6A6
	str r0, [sp, #0x78]
	str r0, [sp, #0x7c]
	mov r0, #7
	add r1, r4, #0
	and r1, r0
	cmp r1, #0
	bne _0221C430
	ldr r2, [sp, #0x1e8]
	add r1, r2, #0
	and r1, r0
	cmp r1, #0
	beq _0221C43A
_0221C430:
	mov r0, #0
	add sp, #0x1d4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221C43A:
	lsr r0, r4, #3
	str r0, [sp, #0x14]
	cmp r0, #2
	bge _0221C44C
	mov r0, #0
	add sp, #0x1d4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221C44C:
	add r0, sp, #0x90
	add r1, r3, #0
	lsl r2, r2, #3
	bl MOD13_0221BEE4
	str r0, [sp, #0x18]
	ldr r0, [sp]
	add r0, #8
	add r1, r5, #0
	add r2, r4, #0
	bl memcpy
	add r3, sp, #0x80
	add r2, sp, #0x78
	mov r1, #8
_0221C46A:
	ldrb r0, [r2]
	add r2, r2, #1
	strb r0, [r3]
	add r3, r3, #1
	sub r1, r1, #1
	cmp r1, #0
	bne _0221C46A
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	asr r0, r0, #0x1f
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x10]
	str r0, [sp, #0x34]
	str r0, [sp, #0x38]
	str r0, [sp, #0x64]
	str r0, [sp, #0x60]
	str r0, [sp, #0x5c]
	str r0, [sp, #0x58]
	str r0, [sp, #0x48]
	str r0, [sp, #0x50]
_0221C494:
	mov r0, #1
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x14]
	cmp r0, #1
	bge _0221C4A0
	b _0221C5DA
_0221C4A0:
	ldr r1, [sp, #0x20]
	ldr r2, [sp, #0x10]
	asr r3, r2, #0x1f
	bl _ll_mul
	str r0, [sp, #0x24]
	str r1, [sp, #8]
_0221C4AE:
	ldr r0, [sp, #0xc]
	lsl r1, r0, #3
	ldr r0, [sp]
	add r3, r0, r1
	str r3, [sp, #0x2c]
	add r2, sp, #0x88
	mov r1, #8
_0221C4BC:
	ldrb r0, [r3]
	add r3, r3, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	cmp r1, #0
	bne _0221C4BC
	add r0, sp, #0x90
	ldr r1, [sp, #0x18]
	add r2, sp, #0x80
	lsl r3, r2, #0
	bl MOD13_0221B900
	ldr r0, [sp, #0xc]
	asr r1, r0, #0x1f
	lsl r2, r0, #0
	ldr r0, [sp, #0x24]
	add r6, r2, r0
	ldr r0, [sp, #8]
	adc r1, r0
	add r2, r1, #0
	ldr r0, _0221C60C ; =0xFF000000
	and r2, r0
	lsr r0, r2, #0x18
	str r0, [sp, #0x30]
	add r2, r1, #0
	ldr r0, _0221C610 ; =0x00FF0000
	and r2, r0
	lsr r0, r2, #8
	str r0, [sp, #0x68]
	add r2, r1, #0
	ldr r0, _0221C614 ; =0x0000FF00
	and r2, r0
	add r3, r6, #0
	ldr r0, [sp, #0x64]
	and r3, r0
	lsl r0, r2, #8
	lsr r5, r3, #0x18
	orr r5, r0
	lsr r0, r2, #0x18
	str r0, [sp, #0x3c]
	add r0, r1, #0
	mov r2, #0xff
	and r0, r2
	add r3, r6, #0
	ldr r2, [sp, #0x60]
	and r3, r2
	lsl r2, r0, #0x18
	lsr r4, r3, #8
	orr r4, r2
	lsr r0, r0, #8
	str r0, [sp, #0x40]
	add r3, r1, #0
	ldr r0, [sp, #0x5c]
	and r3, r0
	add r0, r6, #0
	ldr r2, _0221C60C ; =0xFF000000
	and r0, r2
	lsr r2, r0, #0x18
	lsl r3, r3, #8
	orr r3, r2
	lsl r0, r0, #8
	str r0, [sp, #0x6c]
	ldr r0, [sp, #0x58]
	and r1, r0
	add r0, r6, #0
	ldr r2, _0221C610 ; =0x00FF0000
	and r0, r2
	lsr r2, r0, #8
	str r2, [sp, #0x54]
	lsl r2, r1, #0x18
	ldr r1, [sp, #0x54]
	orr r2, r1
	lsl r7, r0, #0x18
	add r1, r6, #0
	str r1, [sp, #0x4c]
	mov r0, #0xff
	and r1, r0
	str r1, [sp, #0x4c]
	lsl r0, r1, #0x18
	str r0, [sp, #0x44]
	ldr r0, _0221C614 ; =0x0000FF00
	and r6, r0
	lsl r1, r6, #8
	ldr r0, [sp, #0x44]
	orr r0, r1
	str r0, [sp, #0x44]
	ldr r0, [sp, #0x48]
	ldr r1, [sp, #0x50]
	orr r0, r1
	ldr r1, [sp, #0x44]
	orr r2, r1
	orr r7, r0
	orr r3, r2
	ldr r0, [sp, #0x6c]
	orr r0, r7
	str r0, [sp, #0x6c]
	ldr r0, [sp, #0x40]
	orr r0, r3
	str r0, [sp, #0x40]
	ldr r0, [sp, #0x6c]
	orr r4, r0
	ldr r1, [sp, #0x3c]
	ldr r0, [sp, #0x40]
	orr r1, r0
	str r1, [sp, #0x3c]
	orr r5, r4
	ldr r1, [sp, #0x38]
	ldr r0, [sp, #0x3c]
	orr r1, r0
	ldr r0, [sp, #0x68]
	orr r0, r5
	str r0, [sp, #0x68]
	ldr r2, [sp, #0x34]
	orr r2, r1
	ldr r1, [sp, #0x30]
	orr r1, r0
	str r1, [sp, #0x30]
	str r1, [sp, #0x70]
	str r2, [sp, #0x74]
	add r0, sp, #0x80
	add r1, sp, #0x70
	lsl r2, r0, #0
	bl MOD13_0221C1CC
	add r3, sp, #0x88
	mov r2, #8
_0221C5BA:
	ldrb r1, [r3]
	add r3, r3, #1
	ldr r0, [sp, #0x2c]
	strb r1, [r0]
	add r0, r0, #1
	str r0, [sp, #0x2c]
	sub r2, r2, #1
	cmp r2, #0
	bne _0221C5BA
	ldr r0, [sp, #0xc]
	add r1, r0, #1
	str r1, [sp, #0xc]
	ldr r0, [sp, #0x14]
	cmp r1, r0
	bgt _0221C5DA
	b _0221C4AE
_0221C5DA:
	ldr r0, [sp, #0x10]
	add r0, r0, #1
	str r0, [sp, #0x10]
	cmp r0, #6
	bge _0221C5E6
	b _0221C494
_0221C5E6:
	add r3, sp, #0x80
	mov r2, #8
_0221C5EA:
	ldrb r1, [r3]
	add r3, r3, #1
	ldr r0, [sp]
	strb r1, [r0]
	add r0, r0, #1
	str r0, [sp]
	sub r2, r2, #1
	cmp r2, #0
	bne _0221C5EA
	mov r0, #1
	add sp, #0x1d4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_0221C608: .word 0xA6A6A6A6
_0221C60C: .word 0xFF000000
_0221C610: .word 0x00FF0000
_0221C614: .word 0x0000FF00

	thumb_func_start MOD13_0221C618
MOD13_0221C618: ; 0x0221C618
	push {r4, lr}
	bl MOD13_0221C658
	add r4, r0, #0
	ldr r0, _0221C64C ; =0x02241B28
	str r4, [r0]
	bl MOD13_0221D938
	cmp r4, #1
	bne _0221C634
	mov r1, #6
	ldr r0, _0221C650 ; =0x02241AE8
	str r1, [r0]
	b _0221C63A
_0221C634:
	mov r1, #7
	ldr r0, _0221C650 ; =0x02241AE8
	str r1, [r0]
_0221C63A:
	mov r0, #0
	mvn r1, r0
	ldr r0, _0221C654 ; =0x0223F870
	str r1, [r0]
	bl MOD13_0221A778
	pop {r4}
	pop {r3}
	bx r3
	.align 2, 0
_0221C64C: .word MOD13_02241B28
_0221C650: .word MOD13_02241AE8
_0221C654: .word MOD13_0223F870

	thumb_func_start MOD13_0221C658
MOD13_0221C658: ; 0x0221C658
	push {r4, r5, r6, r7, lr}
	sub sp, #0x64
	mov r4, #0
	mov r0, #4
	mvn r0, r0
	str r0, [sp, #4]
	str r4, [sp, #0x40]
	str r4, [sp, #8]
	str r4, [sp, #0xc]
	ldr r6, _0221C9E0 ; =0x02241ACC
	mov r0, #1
	str r0, [r6]
	str r4, [sp, #0x10]
	str r4, [sp, #0x18]
	str r4, [sp, #0x2c]
	str r4, [sp, #0x34]
	mvn r0, r0
	str r0, [sp, #0x14]
	str r4, [sp, #0x38]
	str r4, [sp, #0x24]
	mvn r0, r4
	str r0, [sp, #0x28]
	mov r0, #3
	mvn r0, r0
	str r0, [sp, #0x20]
	mov r0, #2
	mvn r0, r0
	str r0, [sp, #0x1c]
	str r4, [sp, #0x3c]
	b _0221CA3C
_0221C694:
	ldr r0, _0221C9E4 ; =0x000001F4
	bl OS_Sleep
	ldr r0, [r6]
	cmp r0, #0xa
	bls _0221C6A2
	b _0221CA3C
_0221C6A2:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #8]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, pc
	bx r0
_0221C6B0: ; jump table
	.short _0221CA3C - _0221C6B0 + 1 ; case 0
	.short _0221C6C6 - _0221C6B0 + 1 ; case 1
	.short _0221C6E6 - _0221C6B0 + 1 ; case 2
	.short _0221C6FC - _0221C6B0 + 1 ; case 3
	.short _0221C74C - _0221C6B0 + 1 ; case 4
	.short _0221C7B6 - _0221C6B0 + 1 ; case 5
	.short _0221C7D8 - _0221C6B0 + 1 ; case 6
	.short _0221C880 - _0221C6B0 + 1 ; case 7
	.short _0221C8DE - _0221C6B0 + 1 ; case 8
	.short _0221C960 - _0221C6B0 + 1 ; case 9
	.short _0221C9BA - _0221C6B0 + 1 ; case 10
_0221C6C6:
	bl MOD13_0221D478
	str r0, [sp, #4]
	cmp r0, #1
	beq _0221C6D6
	mov r0, #1
	str r0, [sp, #0xc]
	b _0221CA3C
_0221C6D6:
	mov r1, #3
	ldr r0, _0221C9E8 ; =0x02241AE8
	str r1, [r0]
	bl MOD13_0221A778
	mov r0, #2
	str r0, [r6]
	b _0221CA3C
_0221C6E6:
	bl MOD13_0221D9A0
	str r0, [sp, #4]
	cmp r0, #1
	beq _0221C6F6
	mov r0, #1
	str r0, [sp, #0xc]
	b _0221CA3C
_0221C6F6:
	mov r0, #3
	str r0, [r6]
	b _0221CA3C
_0221C6FC:
	mov r0, #2
	lsl r1, r0, #0
	ldr r2, [sp, #0x10]
	bl SOC_Socket
	add r4, r0, #0
	cmp r4, #0
	bge _0221C716
	ldr r0, [sp, #0x14]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #0xc]
	b _0221CA3C
_0221C716:
	ldr r2, [sp, #0x18]
	add r1, sp, #0x44
	str r2, [r1]
	str r2, [r1, #4]
	mov r2, #8
	add r1, sp, #0x44
	strb r2, [r1]
	mov r2, #2
	strb r2, [r1, #1]
	ldr r2, _0221C9EC ; =0x000001E6
	strh r2, [r1, #2]
	ldr r1, [sp, #0x18]
	str r1, [sp, #0x48]
	add r1, sp, #0x44
	bl SOC_Bind
	str r0, [sp, #4]
	cmp r0, #0
	bge _0221C746
	ldr r0, [sp, #0x14]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #0xc]
	b _0221CA3C
_0221C746:
	mov r0, #4
	str r0, [r6]
	b _0221CA3C
_0221C74C:
	bl MOD13_0221AA90
	ldr r1, _0221C9F0 ; =0x0223F870
	ldr r1, [r1]
	cmp r0, r1
	blo _0221C768
	add r0, r4, #0
	bl SOC_Close
	ldr r0, [sp, #0x1c]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #0xc]
	b _0221CA3C
_0221C768:
	mov r1, #8
	add r0, sp, #0x44
	strb r1, [r0, #8]
	ldr r0, _0221C9F4 ; =0x02241B5C
	add r1, sp, #0x4c
	bl MOD13_0221CEA4
	add r0, sp, #0x4c
	str r0, [sp]
	add r0, r4, #0
	ldr r1, _0221C9F8 ; =0x022427E4
	ldr r2, _0221C9FC ; =0x00000800
	mov r3, #4
	bl SOC_RecvFrom
	cmp r0, #0
	bgt _0221C78C
	b _0221CA3C
_0221C78C:
	ldr r0, _0221C9F8 ; =0x022427E4
	ldr r1, _0221CA00 ; =0x02241B00
	bl MOD13_0221D0D4
	cmp r0, #0
	bne _0221C79A
	b _0221CA3C
_0221C79A:
	bl MOD13_0221AA90
	ldr r1, _0221CA04 ; =0x00007530
	add r1, r0, r1
	ldr r0, _0221C9F0 ; =0x0223F870
	str r1, [r0]
	mov r0, #5
	str r0, [r6]
	mov r1, #4
	ldr r0, _0221C9E8 ; =0x02241AE8
	str r1, [r0]
	bl MOD13_0221A778
	b _0221CA3C
_0221C7B6:
	ldr r0, _0221C9F8 ; =0x022427E4
	bl MOD13_0221CFD0
	add r3, r0, #0
	ldr r0, _0221CA08 ; =0x02241AC4
	str r3, [r0]
	add r0, r4, #0
	add r1, sp, #0x4c
	ldr r2, _0221C9F8 ; =0x022427E4
	bl MOD13_0221D408
	bl MOD13_0221AA90
	str r0, [sp, #0x40]
	mov r0, #6
	str r0, [r6]
	b _0221CA3C
_0221C7D8:
	bl MOD13_0221AA90
	ldr r1, _0221C9F0 ; =0x0223F870
	ldr r1, [r1]
	cmp r0, r1
	blo _0221C7F4
	add r0, r4, #0
	bl SOC_Close
	ldr r0, [sp, #0x20]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #0xc]
	b _0221CA3C
_0221C7F4:
	add r0, sp, #0x4c
	str r0, [sp]
	add r0, r4, #0
	ldr r1, _0221C9F8 ; =0x022427E4
	ldr r2, _0221C9FC ; =0x00000800
	mov r3, #4
	bl SOC_RecvFrom
	cmp r0, #0
	ble _0221C86A
	ldr r0, _0221C9F8 ; =0x022427E4
	mov r1, #3
	ldr r2, _0221CA0C ; =0x02241FE4
	ldr r3, _0221C9F4 ; =0x02241B5C
	bl MOD13_0221D074
	cmp r0, #0
	beq _0221C86A
	ldr r0, _0221CA0C ; =0x02241FE4
	add r1, sp, #0x54
	add r2, sp, #0x58
	bl MOD13_0221D30C
	add r5, r0, #0
	ldr r1, [sp, #0x54]
	ldr r0, _0221CA10 ; =0x00000101
	cmp r1, r0
	beq _0221C82E
	b _0221CA3C
_0221C82E:
	bl MOD13_0221AA90
	str r0, [sp, #0x5c]
	ldr r2, _0221CA14 ; =0x02241B84
	mov r1, #8
_0221C838:
	ldrb r0, [r5]
	add r5, r5, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	cmp r1, #0
	bne _0221C838
	ldr r0, _0221CA18 ; =0x02241B8C
	add r1, sp, #0x5c
	mov r2, #4
	bl MOD13_0221AAB4
	ldr r0, [sp, #0x24]
	str r0, [sp, #8]
	mov r0, #7
	str r0, [r6]
	mov r1, #5
	ldr r0, _0221C9E8 ; =0x02241AE8
	str r1, [r0]
	ldr r1, [sp, #0x28]
	ldr r0, _0221C9F0 ; =0x0223F870
	str r1, [r0]
	bl MOD13_0221A778
	b _0221CA3C
_0221C86A:
	bl MOD13_0221AA90
	ldr r2, _0221CA1C ; =0x000003E8
	ldr r1, [sp, #0x40]
	add r1, r1, r2
	cmp r0, r1
	bhs _0221C87A
	b _0221CA3C
_0221C87A:
	mov r0, #5
	str r0, [r6]
	b _0221CA3C
_0221C880:
	ldr r0, _0221CA0C ; =0x02241FE4
	ldr r1, _0221CA20 ; =0x00000102
	ldr r2, _0221CA18 ; =0x02241B8C
	mov r3, #8
	bl MOD13_0221D1B4
	ldr r1, _0221CA24 ; =0x02241AE4
	str r0, [r1]
	ldr r0, _0221C9F4 ; =0x02241B5C
	str r0, [sp]
	ldr r0, _0221C9F8 ; =0x022427E4
	mov r1, #4
	ldr r2, _0221CA0C ; =0x02241FE4
	ldr r3, _0221CA24 ; =0x02241AE4
	ldr r3, [r3]
	bl MOD13_0221D248
	add r3, r0, #0
	ldr r0, _0221CA08 ; =0x02241AC4
	str r3, [r0]
	add r0, r4, #0
	add r1, sp, #0x4c
	ldr r2, _0221C9F8 ; =0x022427E4
	bl MOD13_0221D408
	bl MOD13_0221AA90
	str r0, [sp, #0x40]
	ldr r7, _0221CA28 ; =0x02241D90
	ldr r0, [sp, #0x2c]
	lsl r1, r0, #0
	lsl r2, r0, #0
	lsl r3, r0, #0
	mov r5, #0x12
	str r5, [sp, #0x30]
_0221C8C6:
	stmia r7!, {r0, r1, r2, r3}
	stmia r7!, {r0, r1, r2, r3}
	ldr r5, [sp, #0x30]
	sub r5, r5, #1
	str r5, [sp, #0x30]
	cmp r5, #0
	bne _0221C8C6
	stmia r7!, {r0, r1, r2, r3}
	str r0, [r7]
	mov r0, #8
	str r0, [r6]
	b _0221CA3C
_0221C8DE:
	add r0, sp, #0x4c
	str r0, [sp]
	add r0, r4, #0
	ldr r1, _0221C9F8 ; =0x022427E4
	ldr r2, _0221C9FC ; =0x00000800
	mov r3, #4
	bl SOC_RecvFrom
	cmp r0, #0
	ble _0221C932
	ldr r0, _0221C9F8 ; =0x022427E4
	mov r1, #5
	ldr r2, _0221CA0C ; =0x02241FE4
	ldr r3, _0221CA14 ; =0x02241B84
	bl MOD13_0221D074
	ldr r1, _0221CA24 ; =0x02241AE4
	str r0, [r1]
	cmp r0, #0
	beq _0221C932
	ldr r0, _0221CA0C ; =0x02241FE4
	bl MOD13_0221CCD8
	cmp r0, #0
	beq _0221C932
	ldr r1, _0221CA2C ; =0x02241E90
	ldr r0, [sp, #0x3c]
	ldrsb r0, [r1, r0]
	cmp r0, #0
	beq _0221C922
	mov r1, #1
	ldr r0, _0221CA30 ; =0x02241AB0
	strb r1, [r0]
	b _0221C928
_0221C922:
	ldr r1, [sp, #0x34]
	ldr r0, _0221CA30 ; =0x02241AB0
	strb r1, [r0]
_0221C928:
	ldr r0, [sp, #0x38]
	str r0, [sp, #8]
	mov r0, #9
	str r0, [r6]
	b _0221CA3C
_0221C932:
	bl MOD13_0221AA90
	ldr r2, _0221CA1C ; =0x000003E8
	ldr r1, [sp, #0x40]
	add r1, r1, r2
	cmp r0, r1
	blo _0221CA3C
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
	cmp r0, #0xa
	blt _0221C95A
	add r0, r4, #0
	bl SOC_Close
	ldr r0, [sp, #0x14]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #0xc]
	b _0221CA3C
_0221C95A:
	mov r0, #7
	str r0, [r6]
	b _0221CA3C
_0221C960:
	ldr r0, _0221CA0C ; =0x02241FE4
	ldr r1, _0221CA34 ; =0x00000301
	ldr r2, _0221CA30 ; =0x02241AB0
	mov r3, #1
	bl MOD13_0221D1B4
	ldr r1, _0221CA24 ; =0x02241AE4
	str r0, [r1]
	ldr r0, _0221CA14 ; =0x02241B84
	str r0, [sp]
	ldr r0, _0221C9F8 ; =0x022427E4
	mov r1, #6
	ldr r2, _0221CA0C ; =0x02241FE4
	ldr r3, _0221CA24 ; =0x02241AE4
	ldr r3, [r3]
	bl MOD13_0221D248
	ldr r1, _0221CA08 ; =0x02241AC4
	str r0, [r1]
	bl MOD13_0221DD40
	cmp r0, #7
	beq _0221C9A0
	bl MOD13_0221AA90
	ldr r1, _0221CA1C ; =0x000003E8
	add r0, r0, r1
	str r0, [sp, #0x40]
	mov r0, #0xa
	str r0, [sp, #8]
	str r0, [r6]
	b _0221CA3C
_0221C9A0:
	add r0, r4, #0
	add r1, sp, #0x4c
	ldr r2, _0221C9F8 ; =0x022427E4
	ldr r3, _0221CA08 ; =0x02241AC4
	ldr r3, [r3]
	bl MOD13_0221D408
	bl MOD13_0221AA90
	str r0, [sp, #0x40]
	mov r0, #0xa
	str r0, [r6]
	b _0221CA3C
_0221C9BA:
	bl MOD13_0221AA90
	ldr r2, _0221CA1C ; =0x000003E8
	ldr r1, [sp, #0x40]
	add r1, r1, r2
	cmp r0, r1
	blo _0221CA3C
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
	cmp r0, #0xa
	blt _0221CA38
	mov r0, #1
	str r0, [sp, #0xc]
	bl MOD13_0221CA74
	str r0, [sp, #4]
	b _0221CA3C
	nop
_0221C9E0: .word MOD13_02241ACC
_0221C9E4: .word 0x000001F4
_0221C9E8: .word MOD13_02241AE8
_0221C9EC: .word 0x000001E6
_0221C9F0: .word MOD13_0223F870
_0221C9F4: .word MOD13_02241B5C
_0221C9F8: .word MOD13_022427E4
_0221C9FC: .word 0x00000800
_0221CA00: .word MOD13_02241B00
_0221CA04: .word 0x00007530
_0221CA08: .word MOD13_02241AC4
_0221CA0C: .word MOD13_02241FE4
_0221CA10: .word 0x00000101
_0221CA14: .word MOD13_02241B84
_0221CA18: .word MOD13_02241B8C
_0221CA1C: .word 0x000003E8
_0221CA20: .word 0x00000102
_0221CA24: .word MOD13_02241AE4
_0221CA28: .word MOD13_02241D90
_0221CA2C: .word MOD13_02241E90
_0221CA30: .word MOD13_02241AB0
_0221CA34: .word 0x00000301
_0221CA38:
	mov r0, #9
	str r0, [r6]
_0221CA3C:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _0221CA4C
	ldr r0, _0221CA70 ; =0x02241AC0
	ldr r0, [r0]
	cmp r0, #0
	bne _0221CA4C
	b _0221C694
_0221CA4C:
	cmp r4, #0
	beq _0221CA56
	add r0, r4, #0
	bl SOC_Close
_0221CA56:
	ldr r0, _0221CA70 ; =0x02241AC0
	ldr r0, [r0]
	cmp r0, #0
	beq _0221CA64
	mov r0, #7
	mvn r0, r0
	str r0, [sp, #4]
_0221CA64:
	ldr r0, [sp, #4]
	add sp, #0x64
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_0221CA70: .word MOD13_02241AC0

	thumb_func_start MOD13_0221CA74
MOD13_0221CA74: ; 0x0221CA74
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	mov r0, #1
	str r0, [sp]
	ldr r0, _0221CBF0 ; =0x02241CA8
	ldr r1, _0221CBF4 ; =0x02241E90
	bl strcpy
	ldr r1, _0221CBF4 ; =0x02241E90
	ldr r0, [r1, #0x2c]
	cmp r0, #3
	bls _0221CA8E
	b _0221CBE0
_0221CA8E:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #8]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, pc
	bx r0
_0221CA9C: ; jump table
	.short _0221CAA4 - _0221CA9C + 1 ; case 0
	.short _0221CAAC - _0221CA9C + 1 ; case 1
	.short _0221CBB0 - _0221CA9C + 1 ; case 2
	.short _0221CBC8 - _0221CA9C + 1 ; case 3
_0221CAA4:
	mov r1, #0
	ldr r0, _0221CBF0 ; =0x02241CA8
	str r1, [r0, #0x20]
	b _0221CBE6
_0221CAAC:
	ldr r0, [r1, #0x30]
	cmp r0, #0
	bne _0221CABA
	mov r0, #6
	mvn r0, r0
	str r0, [sp]
	b _0221CBE6
_0221CABA:
	ldr r6, _0221CBF0 ; =0x02241CA8
	str r0, [r6, #0x24]
	mov r0, #0
	str r0, [sp, #4]
	add r5, sp, #0x10
	ldr r7, _0221CBF8 ; =0x02241EF4
	ldr r4, _0221CBFC ; =0x02241CD0
	mov r0, #6
	mvn r0, r0
	str r0, [sp, #0xc]
	ldr r0, [sp, #4]
	str r0, [sp, #8]
_0221CAD2:
	add r0, r5, #0
	add r1, r7, #0
	mov r2, #0x20
	bl memcpy
	ldr r1, [sp, #8]
	add r0, sp, #0x30
	strb r1, [r0]
	add r0, r5, #0
	bl strlen
	cmp r0, #0x10
	bhi _0221CB0E
	cmp r0, #0xa
	blo _0221CAFE
	cmp r0, #0xa
	beq _0221CB38
	cmp r0, #0xd
	beq _0221CB48
	cmp r0, #0x10
	beq _0221CB72
	b _0221CB9C
_0221CAFE:
	cmp r0, #0
	bhi _0221CB08
	cmp r0, #0
	beq _0221CBA0
	b _0221CB9C
_0221CB08:
	cmp r0, #5
	beq _0221CB1E
	b _0221CB9C
_0221CB0E:
	cmp r0, #0x1a
	bhi _0221CB18
	cmp r0, #0x1a
	beq _0221CB62
	b _0221CB9C
_0221CB18:
	cmp r0, #0x20
	beq _0221CB8C
	b _0221CB9C
_0221CB1E:
	mov r0, #1
	str r0, [r6, #0x20]
	ldrb r0, [r5]
	strb r0, [r4]
	ldrb r0, [r5, #1]
	strb r0, [r4, #1]
	ldrb r0, [r5, #2]
	strb r0, [r4, #2]
	ldrb r0, [r5, #3]
	strb r0, [r4, #3]
	ldrb r0, [r5, #4]
	strb r0, [r4, #4]
	b _0221CBA0
_0221CB38:
	mov r0, #1
	str r0, [r6, #0x20]
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #0xa
	bl MOD13_0221CC08
	b _0221CBA0
_0221CB48:
	mov r0, #2
	str r0, [r6, #0x20]
	add r3, r5, #0
	add r2, r4, #0
	mov r1, #0xd
_0221CB52:
	ldrb r0, [r3]
	add r3, r3, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	cmp r1, #0
	bne _0221CB52
	b _0221CBA0
_0221CB62:
	mov r0, #2
	str r0, [r6, #0x20]
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #0x1a
	bl MOD13_0221CC08
	b _0221CBA0
_0221CB72:
	mov r0, #3
	str r0, [r6, #0x20]
	add r3, r5, #0
	add r2, r4, #0
	mov r1, #0x10
_0221CB7C:
	ldrb r0, [r3]
	add r3, r3, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	cmp r1, #0
	bne _0221CB7C
	b _0221CBA0
_0221CB8C:
	mov r0, #3
	str r0, [r6, #0x20]
	add r0, r4, #0
	add r1, r5, #0
	mov r2, #0x20
	bl MOD13_0221CC08
	b _0221CBA0
_0221CB9C:
	ldr r0, [sp, #0xc]
	str r0, [sp]
_0221CBA0:
	add r7, #0x28
	add r4, #0x20
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
	cmp r0, #4
	blt _0221CAD2
	b _0221CBE6
_0221CBB0:
	mov r1, #4
	ldr r0, _0221CBF0 ; =0x02241CA8
	str r1, [r0, #0x20]
	ldr r4, _0221CC00 ; =0x02241D50
	ldr r3, _0221CC04 ; =0x02241F8C
	mov r2, #8
_0221CBBC:
	ldmia r3!, {r0, r1}
	stmia r4!, {r0, r1}
	sub r2, r2, #1
	cmp r2, #0
	bne _0221CBBC
	b _0221CBE6
_0221CBC8:
	mov r1, #5
	ldr r0, _0221CBF0 ; =0x02241CA8
	str r1, [r0, #0x20]
	ldr r4, _0221CC00 ; =0x02241D50
	ldr r3, _0221CC04 ; =0x02241F8C
	mov r2, #8
_0221CBD4:
	ldmia r3!, {r0, r1}
	stmia r4!, {r0, r1}
	sub r2, r2, #1
	cmp r2, #0
	bne _0221CBD4
	b _0221CBE6
_0221CBE0:
	mov r0, #6
	mvn r0, r0
	str r0, [sp]
_0221CBE6:
	ldr r0, [sp]
	add sp, #0x34
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_0221CBF0: .word MOD13_02241CA8
_0221CBF4: .word MOD13_02241E90
_0221CBF8: .word MOD13_02241EF4
_0221CBFC: .word MOD13_02241CD0
_0221CC00: .word MOD13_02241D50
_0221CC04: .word MOD13_02241F8C

	thumb_func_start MOD13_0221CC08
MOD13_0221CC08: ; 0x0221CC08
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	add r7, r1, #0
	str r2, [sp]
	mov r4, #0
	add r5, r4, #0
	lsl r0, r2, #0
	cmp r0, #0
	ble _0221CCCE
	str r4, [sp, #4]
_0221CC1E:
	ldrsb r0, [r7, r5]
	cmp r0, #0x63
	bgt _0221CC7A
	cmp r0, #0x63
	bge _0221CC94
	cmp r0, #0x61
	bgt _0221CC74
	cmp r0, #0x61
	bge _0221CC94
	add r1, r0, #0
	sub r1, #0x30
	cmp r1, #0x16
	bhi _0221CCA0
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #8]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add r1, pc
	bx r1
_0221CC46: ; jump table
	.short _0221CC8E - _0221CC46 + 1 ; case 0
	.short _0221CC8E - _0221CC46 + 1 ; case 1
	.short _0221CC8E - _0221CC46 + 1 ; case 2
	.short _0221CC8E - _0221CC46 + 1 ; case 3
	.short _0221CC8E - _0221CC46 + 1 ; case 4
	.short _0221CC8E - _0221CC46 + 1 ; case 5
	.short _0221CC8E - _0221CC46 + 1 ; case 6
	.short _0221CC8E - _0221CC46 + 1 ; case 7
	.short _0221CC8E - _0221CC46 + 1 ; case 8
	.short _0221CC8E - _0221CC46 + 1 ; case 9
	.short _0221CCA0 - _0221CC46 + 1 ; case 10
	.short _0221CCA0 - _0221CC46 + 1 ; case 11
	.short _0221CCA0 - _0221CC46 + 1 ; case 12
	.short _0221CCA0 - _0221CC46 + 1 ; case 13
	.short _0221CCA0 - _0221CC46 + 1 ; case 14
	.short _0221CCA0 - _0221CC46 + 1 ; case 15
	.short _0221CCA0 - _0221CC46 + 1 ; case 16
	.short _0221CC9A - _0221CC46 + 1 ; case 17
	.short _0221CC9A - _0221CC46 + 1 ; case 18
	.short _0221CC9A - _0221CC46 + 1 ; case 19
	.short _0221CC9A - _0221CC46 + 1 ; case 20
	.short _0221CC9A - _0221CC46 + 1 ; case 21
	.short _0221CC9A - _0221CC46 + 1 ; case 22
_0221CC74:
	cmp r0, #0x62
	beq _0221CC94
	b _0221CCA0
_0221CC7A:
	cmp r0, #0x65
	bgt _0221CC88
	cmp r0, #0x65
	bge _0221CC94
	cmp r0, #0x64
	beq _0221CC94
	b _0221CCA0
_0221CC88:
	cmp r0, #0x66
	beq _0221CC94
	b _0221CCA0
_0221CC8E:
	sub r0, #0x30
	add r4, r4, r0
	b _0221CCAA
_0221CC94:
	sub r0, #0x57
	add r4, r4, r0
	b _0221CCAA
_0221CC9A:
	sub r0, #0x37
	add r4, r4, r0
	b _0221CCAA
_0221CCA0:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221CCAA:
	add r0, r5, #0
	mov r1, #2
	bl _s32_div_f
	cmp r1, #0
	bne _0221CCBA
	lsl r4, r4, #4
	b _0221CCC6
_0221CCBA:
	add r0, r5, #0
	mov r1, #2
	bl _s32_div_f
	strb r4, [r6, r0]
	ldr r4, [sp, #4]
_0221CCC6:
	add r5, r5, #1
	ldr r0, [sp]
	cmp r5, r0
	blt _0221CC1E
_0221CCCE:
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3

	thumb_func_start MOD13_0221CCD8
MOD13_0221CCD8: ; 0x0221CCD8
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r1, r0, #0
	add r1, #8
	str r1, [sp, #8]
	mov r2, #0
	str r2, [sp, #4]
	ldrh r2, [r0]
	asr r3, r2, #8
	mov r0, #0xff
	and r3, r0
	lsl r2, r2, #8
	ldr r0, _0221CE80 ; =0x0000FF00
	and r2, r0
	orr r3, r2
	lsl r0, r3, #0x10
	lsr r0, r0, #0x10
	add r0, r1, r0
	str r0, [sp]
	add r0, sp, #8
	ldr r1, [sp]
	add r2, sp, #0xc
	add r3, sp, #0x10
	bl MOD13_0221D344
	add r5, r0, #0
	cmp r5, #0
	bne _0221CD12
	b _0221CE76
_0221CD12:
	mov r7, #0
_0221CD14:
	ldr r0, [sp, #0xc]
	ldr r1, _0221CE84 ; =0x00000201
	sub r1, r0, r1
	cmp r1, #9
	bls _0221CD20
	b _0221CE62
_0221CD20:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #8]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add r1, pc
	bx r1
_0221CD2E: ; jump table
	.short _0221CD42 - _0221CD2E + 1 ; case 0
	.short _0221CD60 - _0221CD2E + 1 ; case 1
	.short _0221CD7A - _0221CD2E + 1 ; case 2
	.short _0221CDA0 - _0221CD2E + 1 ; case 3
	.short _0221CDC6 - _0221CD2E + 1 ; case 4
	.short _0221CDE0 - _0221CD2E + 1 ; case 5
	.short _0221CDE0 - _0221CD2E + 1 ; case 6
	.short _0221CDE0 - _0221CD2E + 1 ; case 7
	.short _0221CDE0 - _0221CD2E + 1 ; case 8
	.short _0221CE40 - _0221CD2E + 1 ; case 9
_0221CD42:
	ldr r2, _0221CE88 ; =0x02241E90
	add r0, r7, #0
	add r1, r7, #0
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, _0221CE88 ; =0x02241E90
	add r1, r5, #0
	ldr r2, [sp, #0x10]
	bl memcpy
	mov r0, #1
	str r0, [sp, #4]
	b _0221CE62
_0221CD60:
	ldrh r1, [r5]
	asr r2, r1, #8
	mov r0, #0xff
	and r2, r0
	lsl r1, r1, #8
	ldr r0, _0221CE80 ; =0x0000FF00
	and r1, r0
	orr r2, r1
	lsl r0, r2, #0x10
	lsr r1, r0, #0x10
	ldr r0, _0221CE88 ; =0x02241E90
	str r1, [r0, #0x2c]
	b _0221CE62
_0221CD7A:
	ldrh r1, [r5]
	asr r2, r1, #8
	mov r0, #0xff
	and r2, r0
	lsl r1, r1, #8
	ldr r0, _0221CE80 ; =0x0000FF00
	and r1, r0
	orr r2, r1
	lsl r0, r2, #0x10
	lsr r1, r0, #0x10
	add r3, r7, #0
	ldr r2, _0221CE8C ; =0x02241D90
_0221CD92:
	ldr r0, _0221CE90 ; =0x0000015C
	str r1, [r2, r0]
	add r2, #0x28
	add r3, r3, #1
	cmp r3, #4
	blt _0221CD92
	b _0221CE62
_0221CDA0:
	ldrh r1, [r5]
	asr r2, r1, #8
	mov r0, #0xff
	and r2, r0
	lsl r1, r1, #8
	ldr r0, _0221CE80 ; =0x0000FF00
	and r1, r0
	orr r2, r1
	lsl r0, r2, #0x10
	lsr r2, r0, #0x10
	add r1, r7, #0
	ldr r3, _0221CE8C ; =0x02241D90
_0221CDB8:
	ldr r0, _0221CE94 ; =0x00000160
	str r2, [r3, r0]
	add r3, #0x28
	add r1, r1, #1
	cmp r1, #4
	blt _0221CDB8
	b _0221CE62
_0221CDC6:
	ldrh r1, [r5]
	asr r2, r1, #8
	mov r0, #0xff
	and r2, r0
	lsl r1, r1, #8
	ldr r0, _0221CE80 ; =0x0000FF00
	and r1, r0
	orr r2, r1
	lsl r0, r2, #0x10
	lsr r1, r0, #0x10
	ldr r0, _0221CE88 ; =0x02241E90
	str r1, [r0, #0x30]
	b _0221CE62
_0221CDE0:
	ldr r1, _0221CE98 ; =0x00000206
	sub r1, r0, r1
	mov r0, #0x28
	mul r1, r0
	ldr r0, _0221CE9C ; =0x02241EF4
	add r0, r0, r1
	add r1, r7, #0
	mov r2, #0x20
	bl memset
	ldr r0, _0221CE88 ; =0x02241E90
	ldr r0, [r0, #0x5c]
	cmp r0, #1
	bne _0221CE28
	ldr r1, [sp, #0xc]
	ldr r0, _0221CE98 ; =0x00000206
	sub r1, r1, r0
	mov r0, #0x28
	mul r1, r0
	ldr r0, _0221CE9C ; =0x02241EF4
	add r4, r0, r1
	add r6, r7, #0
	ldr r0, [sp, #0x10]
	cmp r0, #0
	ble _0221CE62
_0221CE12:
	add r0, r4, #0
	ldrsb r1, [r5, r7]
	add r5, r5, #1
	bl MOD13_0221AA14
	add r4, r4, r0
	add r6, r6, #1
	ldr r0, [sp, #0x10]
	cmp r6, r0
	blt _0221CE12
	b _0221CE62
_0221CE28:
	ldr r1, [sp, #0xc]
	ldr r0, _0221CE98 ; =0x00000206
	sub r1, r1, r0
	mov r0, #0x28
	mul r1, r0
	ldr r0, _0221CE9C ; =0x02241EF4
	add r0, r0, r1
	add r1, r5, #0
	ldr r2, [sp, #0x10]
	bl memcpy
	b _0221CE62
_0221CE40:
	ldr r2, _0221CEA0 ; =0x02241F8C
	add r0, r7, #0
	add r1, r7, #0
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, _0221CEA0 ; =0x02241F8C
	add r1, r5, #0
	ldr r2, [sp, #0x10]
	bl memcpy
_0221CE62:
	add r0, sp, #8
	ldr r1, [sp]
	add r2, sp, #0xc
	add r3, sp, #0x10
	bl MOD13_0221D344
	add r5, r0, #0
	cmp r5, #0
	beq _0221CE76
	b _0221CD14
_0221CE76:
	ldr r0, [sp, #4]
	add sp, #0x14
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_0221CE80: .word 0x0000FF00
_0221CE84: .word 0x00000201
_0221CE88: .word MOD13_02241E90
_0221CE8C: .word MOD13_02241D90
_0221CE90: .word 0x0000015C
_0221CE94: .word 0x00000160
_0221CE98: .word 0x00000206
_0221CE9C: .word MOD13_02241EF4
_0221CEA0: .word MOD13_02241F8C

	thumb_func_start MOD13_0221CEA4
MOD13_0221CEA4: ; 0x0221CEA4
	push {r4, lr}
	sub sp, #0x50
	add r4, r0, #0
	add r2, r4, #0
	add r2, #0xc
	ldr r1, _0221CFB0 ; =0x0223F92C
	ldrb r0, [r1]
	strb r0, [r4, #0xc]
	ldrb r0, [r1, #1]
	strb r0, [r2, #1]
	ldrb r0, [r1, #2]
	strb r0, [r2, #2]
	ldrb r0, [r1, #3]
	strb r0, [r2, #3]
	add r1, sp, #0
	ldr r0, _0221CFB4 ; =0x02241B3C
	ldrb r2, [r0]
	strb r2, [r1]
	ldrb r2, [r0, #1]
	strb r2, [r1, #1]
	ldrb r2, [r0, #2]
	strb r2, [r1, #2]
	ldrb r2, [r0, #3]
	strb r2, [r1, #3]
	ldrb r2, [r0, #4]
	strb r2, [r1, #4]
	ldrb r0, [r0, #5]
	strb r0, [r1, #5]
	add r1, sp, #0
	ldrb r2, [r1]
	mov r0, #0xfd
	and r2, r0
	strb r2, [r1]
	add r0, sp, #4
	add r0, #2
	bl MOD13_0221CFC0
	ldr r0, _0221CFB8 ; =0x02241B34
	add r1, sp, #4
	add r1, #2
	ldrb r2, [r1]
	strb r2, [r0]
	ldrb r2, [r1, #1]
	strb r2, [r0, #1]
	ldrb r2, [r1, #2]
	strb r2, [r0, #2]
	ldrb r2, [r1, #3]
	strb r2, [r0, #3]
	ldrb r2, [r1, #4]
	strb r2, [r0, #4]
	ldrb r2, [r1, #5]
	strb r2, [r0, #5]
	add r0, sp, #0
	mov r2, #6
	bl memcmp
	cmp r0, #0
	bgt _0221CF52
	add r1, sp, #4
	add r1, #2
	ldrb r0, [r1]
	strb r0, [r4]
	ldrb r0, [r1, #1]
	strb r0, [r4, #1]
	ldrb r0, [r1, #2]
	strb r0, [r4, #2]
	ldrb r0, [r1, #3]
	strb r0, [r4, #3]
	ldrb r0, [r1, #4]
	strb r0, [r4, #4]
	ldrb r0, [r1, #5]
	strb r0, [r4, #5]
	add r1, r4, #6
	add r0, sp, #0
	ldrb r2, [r0]
	strb r2, [r4, #6]
	ldrb r2, [r0, #1]
	strb r2, [r1, #1]
	ldrb r2, [r0, #2]
	strb r2, [r1, #2]
	ldrb r2, [r0, #3]
	strb r2, [r1, #3]
	ldrb r2, [r0, #4]
	strb r2, [r1, #4]
	ldrb r0, [r0, #5]
	strb r0, [r1, #5]
	b _0221CF8A
_0221CF52:
	add r1, sp, #0
	ldrb r0, [r1]
	strb r0, [r4]
	ldrb r0, [r1, #1]
	strb r0, [r4, #1]
	ldrb r0, [r1, #2]
	strb r0, [r4, #2]
	ldrb r0, [r1, #3]
	strb r0, [r4, #3]
	ldrb r0, [r1, #4]
	strb r0, [r4, #4]
	ldrb r0, [r1, #5]
	strb r0, [r4, #5]
	add r1, r4, #6
	add r0, sp, #4
	add r0, #2
	ldrb r2, [r0]
	strb r2, [r4, #6]
	ldrb r2, [r0, #1]
	strb r2, [r1, #1]
	ldrb r2, [r0, #2]
	strb r2, [r1, #2]
	ldrb r2, [r0, #3]
	strb r2, [r1, #3]
	ldrb r2, [r0, #4]
	strb r2, [r1, #4]
	ldrb r0, [r0, #5]
	strb r0, [r1, #5]
_0221CF8A:
	ldr r0, _0221CFBC ; =0x0223F868
	ldr r0, [r0]
	cmp r0, #0
	beq _0221CFA4
	add r0, sp, #0xc
	add r1, sp, #4
	add r1, #2
	bl MOD13_0221A9D8
	add r0, sp, #0x2c
	add r1, sp, #0
	bl MOD13_0221A9D8
_0221CFA4:
	mov r0, #1
	add sp, #0x50
	pop {r4}
	pop {r3}
	bx r3
	nop
_0221CFB0: .word MOD13_0223F92C
_0221CFB4: .word MOD13_02241B3C
_0221CFB8: .word MOD13_02241B34
_0221CFBC: .word MOD13_0223F868

	thumb_func_start MOD13_0221CFC0
MOD13_0221CFC0: ; 0x0221CFC0
	push {lr}
	sub sp, #4
	bl OS_GetMacAddress
	mov r0, #1
	add sp, #4
	pop {r3}
	bx r3

	thumb_func_start MOD13_0221CFD0
MOD13_0221CFD0: ; 0x0221CFD0
	push {r4, lr}
	sub sp, #0x10
	add r4, r0, #0
	ldr r1, _0221D05C ; =0x00000100
	add r0, sp, #4
	strh r1, [r0]
	ldr r3, _0221D060 ; =0x0223F880
	add r2, sp, #4
	add r2, #2
	mov r1, #7
_0221CFE4:
	ldrb r0, [r3]
	add r3, r3, #1
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	cmp r1, #0
	bne _0221CFE4
	ldr r0, _0221D064 ; =0x0223F864
	ldr r0, [r0]
	mov r1, #1
	add r2, sp, #4
	mov r3, #2
	bl MOD13_0221D1E0
	mov r1, #2
	add r2, sp, #4
	add r3, r1, #0
	bl MOD13_0221D1E0
	ldr r1, _0221D068 ; =0x02241B00
	ldr r1, [r1]
	cmp r1, #0
	beq _0221D01C
	mov r1, #5
	add r2, sp, #4
	mov r3, #2
	bl MOD13_0221D1E0
_0221D01C:
	mov r1, #3
	add r2, sp, #4
	add r2, #2
	mov r3, #7
	bl MOD13_0221D1E0
	add r3, r0, #0
	ldr r1, _0221D068 ; =0x02241B00
	ldr r1, [r1]
	cmp r1, #0
	beq _0221D03E
	mov r1, #4
	ldr r2, _0221D06C ; =0x02241B34
	mov r3, #6
	bl MOD13_0221D1E0
	add r3, r0, #0
_0221D03E:
	mov r0, #0
	str r0, [sp]
	add r0, r4, #0
	mov r1, #2
	ldr r2, _0221D070 ; =0x02241FE4
	ldr r4, _0221D064 ; =0x0223F864
	ldr r4, [r4]
	sub r3, r3, r4
	add r3, #8
	bl MOD13_0221D248
	add sp, #0x10
	pop {r4}
	pop {r3}
	bx r3
	.align 2, 0
_0221D05C: .word 0x00000100
_0221D060: .word MOD13_0223F880
_0221D064: .word MOD13_0223F864
_0221D068: .word MOD13_02241B00
_0221D06C: .word MOD13_02241B34
_0221D070: .word MOD13_02241FE4

	thumb_func_start MOD13_0221D074
MOD13_0221D074: ; 0x0221D074
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r1, #0
	add r6, r2, #0
	add r4, r3, #0
	add r1, sp, #4
	add r2, sp, #8
	bl MOD13_0221D398
	add r1, r0, #0
	cmp r1, #0
	bne _0221D096
	mov r0, #0
	add sp, #0x10
	pop {r4, r5, r6}
	pop {r3}
	bx r3
_0221D096:
	ldr r0, [sp, #4]
	cmp r0, r5
	beq _0221D0A6
	mov r0, #0
	add sp, #0x10
	pop {r4, r5, r6}
	pop {r3}
	bx r3
_0221D0A6:
	cmp r4, #0
	beq _0221D0C0
	mov r0, #0x10
	str r0, [sp]
	add r0, r6, #0
	ldr r2, [sp, #8]
	add r3, r4, #0
	bl MOD13_0221C218
	ldr r0, [sp, #8]
	sub r0, #8
	str r0, [sp, #8]
	b _0221D0C8
_0221D0C0:
	add r0, r6, #0
	ldr r2, [sp, #8]
	bl memcpy
_0221D0C8:
	ldr r0, [sp, #8]
	add sp, #0x10
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_0221D0D4
MOD13_0221D0D4: ; 0x0221D0D4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	str r1, [sp]
	add r1, sp, #0xc
	add r2, sp, #0x10
	bl MOD13_0221D398
	str r0, [sp, #0x1c]
	mov r7, #0
	str r7, [sp, #4]
	str r7, [sp, #8]
	cmp r0, #0
	bne _0221D0F8
	add r0, r7, #0
	add sp, #0x24
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221D0F8:
	ldr r1, [sp, #0xc]
	cmp r1, #1
	beq _0221D108
	add r0, r7, #0
	add sp, #0x24
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221D108:
	ldr r1, [sp, #0x10]
	add r6, r0, r1
	add r0, #8
	str r0, [sp, #0x1c]
	add r0, sp, #0x1c
	add r1, r6, #0
	add r2, sp, #0x14
	add r3, sp, #0x18
	bl MOD13_0221D344
	cmp r0, #0
	beq _0221D17C
	mov r4, #0xff
	ldr r5, _0221D1B0 ; =0x0000FF00
_0221D124:
	ldr r1, [sp, #0x14]
	cmp r1, #1
	beq _0221D134
	cmp r1, #2
	beq _0221D146
	cmp r1, #5
	beq _0221D15A
	b _0221D16C
_0221D134:
	ldrh r0, [r0]
	asr r1, r0, #8
	and r1, r4
	lsl r0, r0, #8
	and r0, r5
	orr r1, r0
	lsl r0, r1, #0x10
	lsr r7, r0, #0x10
	b _0221D16C
_0221D146:
	ldrh r0, [r0]
	asr r1, r0, #8
	and r1, r4
	lsl r0, r0, #8
	and r0, r5
	orr r1, r0
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	b _0221D16C
_0221D15A:
	ldrh r0, [r0]
	asr r1, r0, #8
	and r1, r4
	lsl r0, r0, #8
	and r0, r5
	orr r1, r0
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #8]
_0221D16C:
	add r0, sp, #0x1c
	add r1, r6, #0
	add r2, sp, #0x14
	add r3, sp, #0x18
	bl MOD13_0221D344
	cmp r0, #0
	bne _0221D124
_0221D17C:
	cmp r7, #1
	bne _0221D186
	ldr r0, [sp, #4]
	cmp r0, #1
	beq _0221D190
_0221D186:
	mov r0, #0
	add sp, #0x24
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221D190:
	ldr r0, [sp, #8]
	cmp r0, #1
	blt _0221D19E
	mov r1, #1
	ldr r0, [sp]
	str r1, [r0]
	b _0221D1A4
_0221D19E:
	mov r1, #0
	ldr r0, [sp]
	str r1, [r0]
_0221D1A4:
	mov r0, #1
	add sp, #0x24
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_0221D1B0: .word 0x0000FF00

	thumb_func_start MOD13_0221D1B4
MOD13_0221D1B4: ; 0x0221D1B4
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0
	strb r0, [r4]
	strb r0, [r4, #1]
	strb r0, [r4, #2]
	strb r0, [r4, #3]
	strb r0, [r4, #4]
	strb r0, [r4, #5]
	strb r0, [r4, #6]
	strb r0, [r4, #7]
	add r0, r4, #0
	add r0, #8
	bl MOD13_0221D1E0
	sub r0, r0, r4
	add r1, r0, #0
	sub r1, #8
	strh r1, [r4]
	pop {r4}
	pop {r3}
	bx r3

	thumb_func_start MOD13_0221D1E0
MOD13_0221D1E0: ; 0x0221D1E0
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r5, r0, #0
	add r7, r2, #0
	add r4, r3, #0
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	strb r0, [r5, #3]
	lsl r0, r1, #0x10
	lsr r0, r0, #0x10
	asr r2, r0, #8
	mov r3, #0xff
	and r2, r3
	lsl r1, r0, #8
	ldr r0, _0221D244 ; =0x0000FF00
	and r1, r0
	orr r2, r1
	strh r2, [r5]
	add r2, r4, #0
	add r2, #0xb
	mov r1, #7
	bic r2, r1
	sub r6, r2, #4
	lsl r1, r4, #0x10
	lsr r2, r1, #0x10
	asr r1, r2, #8
	and r1, r3
	lsl r2, r2, #8
	and r2, r0
	orr r1, r2
	strh r1, [r5, #2]
	add r5, r5, #4
	add r0, r5, #0
	mov r1, #0
	add r2, r6, #0
	bl memset
	add r0, r5, #0
	add r1, r7, #0
	add r2, r4, #0
	bl memcpy
	add r0, r5, r6
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_0221D244: .word 0x0000FF00

	thumb_func_start MOD13_0221D248
MOD13_0221D248: ; 0x0221D248
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	str r1, [sp, #4]
	add r1, r2, #0
	add r7, r3, #0
	add r5, r6, #0
	mov r4, #0
	strb r4, [r1]
	strb r4, [r1, #1]
	strb r4, [r1, #2]
	strb r4, [r1, #3]
	strb r4, [r1, #4]
	strb r4, [r1, #5]
	strb r4, [r1, #6]
	strb r4, [r1, #7]
	add r0, r7, #0
	sub r0, #8
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
	asr r2, r3, #8
	mov r0, #0xff
	and r2, r0
	lsl r3, r3, #8
	ldr r0, _0221D308 ; =0x0000FF00
	and r3, r0
	orr r2, r3
	strh r2, [r1]
	ldr r3, [sp, #0x20]
	cmp r3, #0
	beq _0221D296
	mov r0, #0x10
	str r0, [sp]
	add r0, r6, #6
	add r2, r7, #0
	bl MOD13_0221C40C
	add r7, #8
	b _0221D29E
_0221D296:
	add r0, r6, #6
	add r2, r7, #0
	bl memcpy
_0221D29E:
	mov r0, #0
	strb r0, [r6]
	strb r0, [r6, #1]
	strb r0, [r6, #2]
	strb r0, [r6, #3]
	strb r0, [r6, #4]
	strb r0, [r6, #5]
	ldr r0, [sp, #4]
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	asr r3, r0, #8
	mov r1, #0xff
	and r3, r1
	lsl r0, r0, #8
	ldr r2, _0221D308 ; =0x0000FF00
	and r0, r2
	orr r3, r0
	strh r3, [r6]
	lsl r0, r7, #0x10
	lsr r0, r0, #0x10
	asr r3, r0, #8
	and r3, r1
	lsl r0, r0, #8
	and r0, r2
	orr r3, r0
	strh r3, [r6, #2]
	add r0, r5, #6
	add r5, r0, r7
	add r1, r6, #0
	cmp r6, r5
	bhs _0221D2E6
_0221D2DC:
	ldrb r0, [r1]
	add r4, r4, r0
	add r1, r1, #1
	cmp r1, r5
	blo _0221D2DC
_0221D2E6:
	lsl r0, r4, #0x10
	lsr r1, r0, #0x10
	asr r2, r1, #8
	mov r0, #0xff
	and r2, r0
	lsl r1, r1, #8
	ldr r0, _0221D308 ; =0x0000FF00
	and r1, r0
	orr r2, r1
	strh r2, [r5]
	add r0, r5, #2
	sub r0, r0, r6
	add sp, #0xc
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_0221D308: .word 0x0000FF00

	thumb_func_start MOD13_0221D30C
MOD13_0221D30C: ; 0x0221D30C
	push {r4, r5, r6, lr}
	sub sp, #8
	add r4, r1, #0
	add r3, r2, #0
	add r2, r0, #0
	add r2, #8
	str r2, [sp]
	ldrh r6, [r0]
	add r0, sp, #0
	asr r1, r6, #8
	mov r5, #0xff
	and r1, r5
	lsl r6, r6, #8
	ldr r5, _0221D340 ; =0x0000FF00
	and r6, r5
	orr r1, r6
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	add r1, r2, r1
	add r2, r4, #0
	bl MOD13_0221D344
	add sp, #8
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	.align 2, 0
_0221D340: .word 0x0000FF00

	thumb_func_start MOD13_0221D344
MOD13_0221D344: ; 0x0221D344
	push {r4, r5, r6, r7}
	add r5, r0, #0
	add r4, r2, #0
	add r2, r3, #0
	ldr r0, [r5]
	cmp r0, r1
	blo _0221D358
	mov r0, #0
	pop {r4, r5, r6, r7}
	bx lr
_0221D358:
	ldrh r1, [r0]
	asr r7, r1, #8
	mov r3, #0xff
	and r7, r3
	lsl r1, r1, #8
	ldr r6, _0221D394 ; =0x0000FF00
	and r1, r6
	orr r7, r1
	lsl r1, r7, #0x10
	lsr r1, r1, #0x10
	str r1, [r4]
	ldrh r1, [r0, #2]
	asr r4, r1, #8
	and r4, r3
	lsl r1, r1, #8
	and r1, r6
	orr r4, r1
	lsl r1, r4, #0x10
	lsr r1, r1, #0x10
	str r1, [r2]
	add r0, r0, #4
	ldr r2, [r2]
	add r2, #0xb
	mov r1, #7
	bic r2, r1
	sub r1, r2, #4
	add r1, r0, r1
	str r1, [r5]
	pop {r4, r5, r6, r7}
	bx lr
	.align 2, 0
_0221D394: .word 0x0000FF00

	thumb_func_start MOD13_0221D398
MOD13_0221D398: ; 0x0221D398
	push {r4, r5, r6, r7}
	mov r3, #0
	ldrh r4, [r0]
	asr r7, r4, #8
	mov r5, #0xff
	and r7, r5
	lsl r4, r4, #8
	ldr r6, _0221D404 ; =0x0000FF00
	and r4, r6
	orr r7, r4
	lsl r4, r7, #0x10
	lsr r4, r4, #0x10
	str r4, [r1]
	ldrh r1, [r0, #2]
	asr r4, r1, #8
	and r4, r5
	lsl r1, r1, #8
	and r1, r6
	orr r4, r1
	lsl r1, r4, #0x10
	lsr r1, r1, #0x10
	str r1, [r2]
	add r4, r0, #6
	ldr r1, [r2]
	add r4, r4, r1
	add r2, r0, #0
	cmp r0, r4
	bhs _0221D3DA
_0221D3D0:
	ldrb r1, [r2]
	add r3, r3, r1
	add r2, r2, #1
	cmp r2, r4
	blo _0221D3D0
_0221D3DA:
	ldrh r2, [r4]
	lsl r1, r3, #0x10
	lsr r4, r1, #0x10
	asr r3, r2, #8
	mov r1, #0xff
	and r3, r1
	lsl r2, r2, #8
	ldr r1, _0221D404 ; =0x0000FF00
	and r2, r1
	orr r3, r2
	lsl r1, r3, #0x10
	lsr r1, r1, #0x10
	cmp r4, r1
	beq _0221D3FC
	mov r0, #0
	pop {r4, r5, r6, r7}
	bx lr
_0221D3FC:
	add r0, r0, #6
	pop {r4, r5, r6, r7}
	bx lr
	nop
_0221D404: .word 0x0000FF00

	thumb_func_start MOD13_0221D408
MOD13_0221D408: ; 0x0221D408
	add r1, r2, #0
	add r2, r3, #0
	ldr r3, _0221D410 ; =MOD13_0221D414
	bx r3
	.align 2, 0
_0221D410: .word MOD13_0221D414

	thumb_func_start MOD13_0221D414
MOD13_0221D414: ; 0x0221D414
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	mov r0, #8
	add r1, sp, #4
	strb r0, [r1]
	mov r0, #2
	strb r0, [r1, #1]
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #8]
	ldr r0, _0221D454 ; =0x000001E6
	strh r0, [r1, #2]
	bl SOCL_GetHostID
	add r1, sp, #0xc
	bl SOC_U32to4U8
	str r4, [sp]
	add r0, r5, #0
	add r1, sp, #4
	add r2, sp, #0xc
	add r3, r6, #0
	bl MOD13_0221D458
	add sp, #0x10
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	nop
_0221D454: .word 0x000001E6

	thumb_func_start MOD13_0221D458
MOD13_0221D458: ; 0x0221D458
	push {lr}
	sub sp, #4
	str r1, [sp]
	add r1, r3, #0
	ldr r2, [sp, #8]
	mov r3, #0
	bl SOC_SendTo
	cmp r0, #0
	bge _0221D470
	mov r0, #3
	mvn r0, r0
_0221D470:
	add sp, #4
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_0221D478
MOD13_0221D478: ; 0x0221D478
	push {r4, r5, r6, r7, lr}
	sub sp, #0x9c
	mov r0, #0
	str r0, [sp, #0x18]
	mvn r4, r0
	str r0, [sp, #0x48]
	ldr r0, _0221D738 ; =0x02241B20
	ldr r0, [r0]
	str r0, [sp, #0x10]
	mov r1, #0x30
	mul r0, r1
	str r0, [sp, #0x10]
	add r0, #0x34
	str r0, [sp, #0x10]
	mov r0, #1
	ldr r1, [sp, #0x10]
	bl MOD13_0221AA64
	str r0, [sp, #0x14]
	cmp r0, #0
	bne _0221D4A4
	b _0221D718
_0221D4A4:
	mov r0, #1
	ldr r1, [sp, #0x10]
	bl MOD13_0221AA64
	str r0, [sp, #0x18]
	cmp r0, #0
	bne _0221D4B4
	b _0221D718
_0221D4B4:
	mov r0, #0
	str r0, [sp, #4]
	str r0, [sp, #0x44]
	str r0, [sp, #0x3c]
	str r0, [sp, #0x38]
	add r6, sp, #0x6c
	str r0, [sp, #0x34]
	lsl r7, r0, #0
	str r0, [sp, #0x28]
	str r0, [sp, #0x2c]
	str r0, [sp, #0x30]
	str r0, [sp, #0x40]
	b _0221D6E0
_0221D4CE:
	bl MOD13_0221AA90
	ldr r1, _0221D73C ; =0x0223F870
	ldr r1, [r1]
	cmp r0, r1
	blo _0221D4DC
	b _0221D6F0
_0221D4DC:
	ldr r0, [sp, #0x28]
	lsl r1, r0, #0
	lsl r2, r0, #0
	ldr r3, _0221D740 ; =0x0030BFFE
	bl MOD13_0221DF9C
	cmp r0, #0
	bne _0221D4F2
	mov r0, #1
	mvn r4, r0
	b _0221D718
_0221D4F2:
	add r0, r6, #0
	bl OS_CreateAlarm
	mov r0, #0x13
	str r0, [sp]
	add r0, r6, #0
	ldr r1, _0221D744 ; =0x000FFB10
	ldr r2, [sp, #0x2c]
	ldr r3, _0221D748 ; =MOD13_0221DC1C
	bl OS_SetAlarm
	mov r5, #1
	ldr r4, [sp, #0x30]
_0221D50C:
	mov r0, #0xa
	bl OS_Sleep
	bl MOD13_0221AA90
	ldr r1, _0221D73C ; =0x0223F870
	ldr r1, [r1]
	cmp r0, r1
	bhs _0221D5A8
	ldr r0, _0221D74C ; =0x02241AC0
	ldr r0, [r0]
	cmp r0, #0
	bne _0221D5A8
	bl MOD13_0221DC64
	cmp r0, #0
	beq _0221D5A4
_0221D52E:
	cmp r0, #0x13
	bhi _0221D59A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #8]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, pc
	bx r0
_0221D540: ; jump table
	.short _0221D59A - _0221D540 + 1 ; case 0
	.short _0221D59A - _0221D540 + 1 ; case 1
	.short _0221D59A - _0221D540 + 1 ; case 2
	.short _0221D59A - _0221D540 + 1 ; case 3
	.short _0221D59C - _0221D540 + 1 ; case 4
	.short _0221D56C - _0221D540 + 1 ; case 5
	.short _0221D59A - _0221D540 + 1 ; case 6
	.short _0221D59A - _0221D540 + 1 ; case 7
	.short _0221D59C - _0221D540 + 1 ; case 8
	.short _0221D59A - _0221D540 + 1 ; case 9
	.short _0221D596 - _0221D540 + 1 ; case 10
	.short _0221D59A - _0221D540 + 1 ; case 11
	.short _0221D59A - _0221D540 + 1 ; case 12
	.short _0221D59A - _0221D540 + 1 ; case 13
	.short _0221D59A - _0221D540 + 1 ; case 14
	.short _0221D59A - _0221D540 + 1 ; case 15
	.short _0221D59A - _0221D540 + 1 ; case 16
	.short _0221D59A - _0221D540 + 1 ; case 17
	.short _0221D59C - _0221D540 + 1 ; case 18
	.short _0221D568 - _0221D540 + 1 ; case 19
_0221D568:
	add r5, r7, #0
	b _0221D59C
_0221D56C:
	ldr r0, _0221D750 ; =0x02241B0C
	ldr r0, [r0]
	ldr r1, _0221D738 ; =0x02241B20
	ldr r1, [r1]
	bl MOD13_0221E0A8
	cmp r0, r4
	ble _0221D59C
	add r4, r0, #0
	add r0, r6, #0
	bl OS_CancelAlarm
	mov r0, #0x13
	str r0, [sp]
	add r0, r6, #0
	ldr r1, _0221D744 ; =0x000FFB10
	ldr r2, [sp, #0x34]
	ldr r3, _0221D748 ; =MOD13_0221DC1C
	bl OS_SetAlarm
	b _0221D59C
_0221D596:
	ldr r5, [sp, #0x38]
	b _0221D59C
_0221D59A:
	ldr r5, [sp, #0x3c]
_0221D59C:
	bl MOD13_0221DC64
	cmp r0, #0
	bne _0221D52E
_0221D5A4:
	cmp r5, #0
	bne _0221D50C
_0221D5A8:
	add r0, r6, #0
	bl OS_CancelAlarm
_0221D5AE:
	bl MOD13_0221DC64
	cmp r0, #0
	bne _0221D5AE
	ldr r0, _0221D74C ; =0x02241AC0
	ldr r0, [r0]
	cmp r0, #0
	beq _0221D5C0
	b _0221D6F0
_0221D5C0:
	ldr r0, [sp, #0x40]
	str r0, [sp, #0xc]
	ldr r0, _0221D738 ; =0x02241B20
	ldr r0, [r0]
	cmp r4, r0
	blt _0221D5D2
	mov r0, #5
	mvn r4, r0
	b _0221D718
_0221D5D2:
	ldr r0, [sp, #0x40]
	str r0, [sp, #8]
	ldr r0, _0221D750 ; =0x02241B0C
	ldr r0, [r0]
	str r0, [sp, #0x1c]
	cmp r4, #0
	ble _0221D66A
	ldr r0, [sp, #0x14]
	str r0, [sp, #0x20]
	add r0, #8
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x14]
	str r0, [sp, #0x24]
	lsl r5, r0, #0
	add r5, #0x2c
_0221D5F0:
	ldr r0, [sp, #0x20]
	ldr r1, [sp, #0x1c]
	add r1, #0xc
	mov r2, #0x20
	bl memcpy
	ldr r0, [sp, #0x1c]
	ldrh r1, [r0, #0xa]
	ldr r0, [sp, #0x24]
	str r1, [r0, #4]
	ldr r0, [sp, #0x1c]
	ldrh r1, [r0, #0xa]
	ldr r0, [sp, #0x24]
	add r1, r0, r1
	ldr r0, [sp, #0x44]
	strb r0, [r1, #8]
	ldr r0, [sp, #0x1c]
	ldrh r1, [r0, #0x2c]
	mov r0, #0x10
	and r1, r0
	cmp r1, #0
	beq _0221D620
	mov r1, #1
	b _0221D622
_0221D620:
	ldr r1, [sp, #0x44]
_0221D622:
	ldr r0, [sp, #0x24]
	strh r1, [r0, #0x32]
	ldr r0, [sp, #0x1c]
	add r0, r0, #4
	ldr r1, [sp, #0x1c]
	ldrb r1, [r1, #4]
	strb r1, [r5]
	ldrb r1, [r0, #1]
	strb r1, [r5, #1]
	ldrb r1, [r0, #2]
	strb r1, [r5, #2]
	ldrb r1, [r0, #3]
	strb r1, [r5, #3]
	ldrb r1, [r0, #4]
	strb r1, [r5, #4]
	ldrb r0, [r0, #5]
	strb r0, [r5, #5]
	ldr r0, [sp, #0x20]
	add r0, #0x30
	str r0, [sp, #0x20]
	ldr r0, [sp, #0x24]
	add r0, #0x30
	str r0, [sp, #0x24]
	add r5, #0x30
	ldr r0, [sp, #0xc]
	add r0, r0, #1
	str r0, [sp, #0xc]
	ldr r0, [sp, #8]
	add r0, r0, #1
	str r0, [sp, #8]
	ldr r0, [sp, #0x1c]
	add r0, #0xc0
	str r0, [sp, #0x1c]
	ldr r0, [sp, #8]
	cmp r0, r4
	blt _0221D5F0
_0221D66A:
	ldr r0, [sp, #0x14]
	str r4, [r0]
	ldr r0, _0221D754 ; =0x02241AE8
	ldr r0, [r0]
	cmp r0, #1
	beq _0221D6C6
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x18]
	add r2, sp, #0x48
	bl MOD13_0221D764
	cmp r0, #0
	beq _0221D6C6
	ldr r3, [sp, #0x48]
	ldr r0, [sp, #0x14]
	add r2, r0, #4
	mov r0, #0x30
	add r1, r3, #0
	mul r1, r0
	add r4, r2, r1
	ldr r0, _0221D758 ; =0x02241AC8
	str r3, [r0]
	ldr r0, _0221D75C ; =0x02241BC4
	add r1, r4, #4
	bl strcpy
	ldr r1, _0221D760 ; =0x02241B3C
	add r0, r4, #0
	add r0, #0x28
	add r4, #0x28
	ldrb r2, [r4]
	strb r2, [r1]
	ldrb r2, [r0, #1]
	strb r2, [r1, #1]
	ldrb r2, [r0, #2]
	strb r2, [r1, #2]
	ldrb r2, [r0, #3]
	strb r2, [r1, #3]
	ldrb r2, [r0, #4]
	strb r2, [r1, #4]
	ldrb r0, [r0, #5]
	strb r0, [r1, #5]
	add r0, sp, #0x4c
	bl MOD13_0221A9D8
	b _0221D6F0
_0221D6C6:
	ldr r0, [sp, #0x18]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x10]
	bl memcpy
	mov r1, #2
	ldr r0, _0221D754 ; =0x02241AE8
	str r1, [r0]
	bl MOD13_0221A778
	ldr r0, [sp, #4]
	add r0, r0, #1
	str r0, [sp, #4]
_0221D6E0:
	ldr r0, [sp, #4]
	cmp r0, #0x1e
	bge _0221D6F0
	ldr r0, _0221D74C ; =0x02241AC0
	ldr r0, [r0]
	cmp r0, #0
	bne _0221D6F0
	b _0221D4CE
_0221D6F0:
	ldr r0, [sp, #4]
	cmp r0, #0x1e
	bge _0221D702
	bl MOD13_0221AA90
	ldr r1, _0221D73C ; =0x0223F870
	ldr r1, [r1]
	cmp r0, r1
	bls _0221D708
_0221D702:
	mov r0, #2
	mvn r4, r0
	b _0221D718
_0221D708:
	ldr r0, _0221D74C ; =0x02241AC0
	ldr r0, [r0]
	cmp r0, #0
	beq _0221D716
	mov r0, #7
	mvn r4, r0
	b _0221D718
_0221D716:
	mov r4, #1
_0221D718:
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _0221D722
	bl MOD13_0221AA50
_0221D722:
	ldr r0, [sp, #0x18]
	cmp r0, #0
	beq _0221D72C
	bl MOD13_0221AA50
_0221D72C:
	add r0, r4, #0
	add sp, #0x9c
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_0221D738: .word MOD13_02241B20
_0221D73C: .word MOD13_0223F870
_0221D740: .word 0x0030BFFE
_0221D744: .word 0x000FFB10
_0221D748: .word MOD13_0221DC1C
_0221D74C: .word MOD13_02241AC0
_0221D750: .word MOD13_02241B0C
_0221D754: .word MOD13_02241AE8
_0221D758: .word MOD13_02241AC8
_0221D75C: .word MOD13_02241BC4
_0221D760: .word MOD13_02241B3C

	thumb_func_start MOD13_0221D764
MOD13_0221D764: ; 0x0221D764
	push {r4, r5, r6, r7, lr}
	sub sp, #0x74
	str r0, [sp]
	str r1, [sp, #4]
	str r2, [sp, #8]
	mov r0, #0
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	ldr r0, [sp]
	add r5, r0, #4
	lsl r0, r1, #0
	add r4, r0, #4
	ldr r0, [sp, #0xc]
	str r0, [sp, #0x20]
	ldr r0, [sp]
	ldr r0, [r0]
	cmp r0, #0
	bls _0221D832
	ldr r0, [sp, #0xc]
	str r0, [sp, #0x28]
	str r0, [sp, #0x24]
_0221D78E:
	add r2, sp, #0x30
	mov r1, #0x22
_0221D792:
	ldr r0, [sp, #0x24]
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	cmp r1, #0
	bne _0221D792
	add r0, sp, #0x30
	add r1, r5, #4
	mov r2, #0x20
	bl memcpy
	ldr r2, [r5]
	ldr r1, [sp, #0x28]
	add r0, sp, #0x30
	strb r1, [r0, r2]
	lsl r7, r1, #0
	ldr r0, [sp, #4]
	ldr r0, [r0]
	str r0, [sp, #0x1c]
	cmp r0, #0
	bls _0221D816
	ldr r6, [r5]
_0221D7BE:
	cmp r6, #0
	beq _0221D816
	cmp r6, #0x20
	bhi _0221D816
	cmp r6, #1
	bne _0221D7D4
	ldrb r0, [r5, #4]
	cmp r0, #0
	beq _0221D816
	cmp r0, #0x20
	beq _0221D816
_0221D7D4:
	add r0, sp, #0x30
	bl strlen
	add r2, r0, #0
	add r0, sp, #0x30
	add r1, r4, #4
	bl memcmp
	cmp r0, #0
	bne _0221D80C
	add r0, r5, #0
	add r0, #0x28
	add r1, r4, #0
	add r1, #0x28
	mov r2, #4
	bl memcmp
	cmp r0, #0
	bne _0221D80C
	ldrh r1, [r5, #0x2e]
	ldrh r0, [r4, #0x2e]
	cmp r1, r0
	beq _0221D80C
	cmp r1, #0
	bne _0221D80C
	mov r0, #1
	str r0, [sp, #0xc]
	b _0221D816
_0221D80C:
	add r4, #0x30
	add r7, r7, #1
	ldr r0, [sp, #0x1c]
	cmp r7, r0
	blo _0221D7BE
_0221D816:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _0221D832
	add r5, #0x30
	ldr r0, [sp, #4]
	add r4, r0, #4
	ldr r0, [sp, #0x20]
	add r0, r0, #1
	str r0, [sp, #0x20]
	ldr r0, [sp]
	ldr r1, [r0]
	ldr r0, [sp, #0x20]
	cmp r0, r1
	blo _0221D78E
_0221D832:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	bne _0221D91A
	add r2, sp, #0x50
	add r2, #2
	mov r1, #0x22
	mov r0, #0
_0221D840:
	strb r0, [r2]
	add r2, r2, #1
	sub r1, r1, #1
	cmp r1, #0
	bne _0221D840
	mov r0, #0
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	ldr r0, [sp]
	add r5, r0, #4
	ldr r0, [sp, #4]
	add r4, r0, #4
	ldr r6, [sp, #0x14]
	ldr r0, [r0]
	cmp r0, #0
	bls _0221D8A0
	add r7, sp, #0x50
	add r7, #2
_0221D864:
	add r0, r7, #0
	add r1, r4, #4
	mov r2, #0x20
	bl memcpy
	ldr r1, [r4]
	ldr r0, [sp, #0x14]
	strb r0, [r7, r1]
	ldr r0, _0221D934 ; =0x0223F878
	bl strlen
	add r2, r0, #0
	add r0, r7, #0
	ldr r1, _0221D934 ; =0x0223F878
	bl memcmp
	cmp r0, #0
	bne _0221D894
	ldrh r0, [r4, #0x2e]
	cmp r0, #0
	bne _0221D894
	mov r0, #1
	str r0, [sp, #0x18]
	b _0221D8A0
_0221D894:
	add r4, #0x30
	add r6, r6, #1
	ldr r0, [sp, #4]
	ldr r0, [r0]
	cmp r6, r0
	blo _0221D864
_0221D8A0:
	mov r0, #0
	str r0, [sp, #0x20]
	ldr r0, [sp]
	ldr r0, [r0]
	cmp r0, #0
	bls _0221D90A
	ldr r7, _0221D934 ; =0x0223F878
	add r4, sp, #0x50
	add r4, #2
	ldr r0, [sp, #0x20]
	str r0, [sp, #0x2c]
_0221D8B6:
	add r0, r4, #0
	add r1, r5, #4
	mov r2, #0x20
	bl memcpy
	ldr r1, [r5]
	ldr r0, [sp, #0x2c]
	strb r0, [r4, r1]
	add r0, r4, #0
	bl strlen
	add r6, r0, #0
	add r0, r7, #0
	bl strlen
	cmp r6, r0
	bne _0221D8F8
	add r0, r7, #0
	bl strlen
	add r2, r0, #0
	add r0, r4, #0
	add r1, r7, #0
	bl memcmp
	cmp r0, #0
	bne _0221D8F8
	ldrh r0, [r5, #0x2e]
	cmp r0, #0
	bne _0221D8F8
	mov r0, #1
	str r0, [sp, #0x14]
	b _0221D90A
_0221D8F8:
	add r5, #0x30
	ldr r0, [sp, #0x20]
	add r0, r0, #1
	str r0, [sp, #0x20]
	ldr r0, [sp]
	ldr r1, [r0]
	ldr r0, [sp, #0x20]
	cmp r0, r1
	blo _0221D8B6
_0221D90A:
	ldr r0, [sp, #0x14]
	cmp r0, #0
	beq _0221D91A
	ldr r0, [sp, #0x18]
	cmp r0, #0
	bne _0221D91A
	mov r0, #1
	str r0, [sp, #0xc]
_0221D91A:
	ldr r0, [sp, #0xc]
	cmp r0, #0
	beq _0221D92A
	ldr r1, [sp, #0x20]
	ldr r0, [sp, #8]
	str r1, [r0]
	mov r0, #1
	str r0, [sp, #0x10]
_0221D92A:
	ldr r0, [sp, #0x10]
	add sp, #0x74
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_0221D934: .word MOD13_0223F878

	thumb_func_start MOD13_0221D938
MOD13_0221D938: ; 0x0221D938
	push {r4, r5, r6, lr}
	mov r5, #1
	ldr r0, _0221D998 ; =0x02241AD0
	ldr r0, [r0]
	cmp r0, #0
	beq _0221D982
	bl MOD13_0221DF5C
	cmp r0, #0
	beq _0221D97C
	mov r4, #0
	mov r6, #0xa
_0221D950:
	add r0, r6, #0
	bl OS_Sleep
	bl MOD13_0221DC64
	cmp r0, #0
	beq _0221D978
_0221D95E:
	cmp r0, #4
	beq _0221D970
	cmp r0, #5
	beq _0221D970
	cmp r0, #0xe
	bne _0221D96E
	add r5, r4, #0
	b _0221D970
_0221D96E:
	add r5, r4, #0
_0221D970:
	bl MOD13_0221DC64
	cmp r0, #0
	bne _0221D95E
_0221D978:
	cmp r5, #0
	bne _0221D950
_0221D97C:
	mov r1, #0
	ldr r0, _0221D998 ; =0x02241AD0
	str r1, [r0]
_0221D982:
	ldr r0, _0221D99C ; =0x02241AD4
	ldr r1, [r0]
	cmp r1, #0
	beq _0221D992
	mov r1, #0
	str r1, [r0]
	bl SOC_Cleanup
_0221D992:
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	.align 2, 0
_0221D998: .word MOD13_02241AD0
_0221D99C: .word MOD13_02241AD4

	thumb_func_start MOD13_0221D9A0
MOD13_0221D9A0: ; 0x0221D9A0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	mov r5, #1
	mvn r6, r5
	ldr r0, _0221DACC ; =0x02241B0C
	ldr r2, [r0]
	ldr r0, _0221DAD0 ; =0x02241AC8
	ldr r1, [r0]
	mov r0, #0xc0
	mul r1, r0
	add r7, r2, r1
	cmp r7, #0
	bne _0221D9C4
	mov r0, #0
	add sp, #0x34
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221D9C4:
	add r0, r7, #0
	mov r1, #0
	ldr r2, _0221DAD4 ; =0x00030000
	bl MOD13_0221DE44
	cmp r0, #0
	bne _0221D9DE
	lsl r0, r5, #0
	mvn r0, r0
	add sp, #0x34
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221D9DE:
	add r0, sp, #8
	bl OS_CreateAlarm
	mov r0, #0x12
	str r0, [sp]
	add r0, sp, #8
	ldr r1, _0221DAD8 ; =0x003FEC42
	mov r2, #0
	ldr r3, _0221DADC ; =MOD13_0221DC1C
	bl OS_SetAlarm
	mov r4, #0
	mov r0, #7
	mvn r0, r0
	str r0, [sp, #4]
_0221D9FC:
	bl MOD13_0221AA90
	ldr r1, _0221DAE0 ; =0x0223F870
	ldr r1, [r1]
	cmp r0, r1
	blo _0221DA0E
	mov r0, #2
	mvn r6, r0
	b _0221DA94
_0221DA0E:
	ldr r0, _0221DAE4 ; =0x02241AC0
	ldr r0, [r0]
	cmp r0, #0
	beq _0221DA1C
	mov r0, #7
	mvn r6, r0
	b _0221DA94
_0221DA1C:
	mov r0, #0xa
	bl OS_Sleep
	bl MOD13_0221DC64
	cmp r0, #0
	beq _0221DA90
_0221DA2A:
	cmp r0, #0xc
	bgt _0221DA44
	cmp r0, #0xc
	bge _0221DA5A
	cmp r0, #5
	bgt _0221DA86
	cmp r0, #4
	blt _0221DA86
	cmp r0, #4
	beq _0221DA88
	cmp r0, #5
	beq _0221DA88
	b _0221DA86
_0221DA44:
	cmp r0, #0x13
	bgt _0221DA86
	cmp r0, #0xd
	blt _0221DA86
	cmp r0, #0xd
	beq _0221DA60
	cmp r0, #0x12
	beq _0221DA88
	cmp r0, #0x13
	beq _0221DA88
	b _0221DA86
_0221DA5A:
	add r5, r4, #0
	mov r6, #1
	b _0221DA88
_0221DA60:
	ldr r0, _0221DAE4 ; =0x02241AC0
	ldr r0, [r0]
	cmp r0, #0
	beq _0221DA6E
	add r5, r4, #0
	ldr r6, [sp, #4]
	b _0221DA88
_0221DA6E:
	add r0, r7, #0
	add r1, r4, #0
	ldr r2, _0221DAD4 ; =0x00030000
	bl MOD13_0221DE44
	cmp r0, #0
	bne _0221DA88
	add r0, r6, #0
	add sp, #0x34
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221DA86:
	add r5, r4, #0
_0221DA88:
	bl MOD13_0221DC64
	cmp r0, #0
	bne _0221DA2A
_0221DA90:
	cmp r5, #0
	bne _0221D9FC
_0221DA94:
	add r0, sp, #8
	bl OS_CancelAlarm
_0221DA9A:
	bl MOD13_0221DC64
	cmp r0, #0
	bne _0221DA9A
	cmp r6, #0
	ble _0221DAC2
	mov r1, #1
	ldr r0, _0221DAE8 ; =0x02241AD0
	str r1, [r0]
	ldr r0, _0221DAEC ; =0x0223F8D4
	bl SOC_Startup
	cmp r0, #0
	bge _0221DABC
	mov r0, #1
	mvn r6, r0
	b _0221DAC2
_0221DABC:
	mov r1, #1
	ldr r0, _0221DAF0 ; =0x02241AD4
	str r1, [r0]
_0221DAC2:
	add r0, r6, #0
	add sp, #0x34
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_0221DACC: .word MOD13_02241B0C
_0221DAD0: .word MOD13_02241AC8
_0221DAD4: .word 0x00030000
_0221DAD8: .word 0x003FEC42
_0221DADC: .word MOD13_0221DC1C
_0221DAE0: .word MOD13_0223F870
_0221DAE4: .word MOD13_02241AC0
_0221DAE8: .word MOD13_02241AD0
_0221DAEC: .word MOD13_0223F8D4
_0221DAF0: .word MOD13_02241AD4

	thumb_func_start MOD13_0221DAF4
MOD13_0221DAF4: ; 0x0221DAF4
	push {r4, r5, r6, lr}
	mov r5, #1
	bl MOD13_0221DEF4
	cmp r0, #0
	beq _0221DB30
	mov r4, #0
	mov r6, #0xa
_0221DB04:
	add r0, r6, #0
	bl OS_Sleep
	bl MOD13_0221DC64
	cmp r0, #0
	beq _0221DB2C
_0221DB12:
	cmp r0, #4
	beq _0221DB24
	cmp r0, #5
	beq _0221DB24
	cmp r0, #0x14
	bne _0221DB22
	add r5, r4, #0
	b _0221DB24
_0221DB22:
	add r5, r4, #0
_0221DB24:
	bl MOD13_0221DC64
	cmp r0, #0
	bne _0221DB12
_0221DB2C:
	cmp r5, #0
	bne _0221DB04
_0221DB30:
	ldr r0, _0221DB4C ; =0x02241B04
	ldr r0, [r0]
	cmp r0, #0
	beq _0221DB44
	ldr r1, _0221DB50 ; =0x02241ABC
	ldr r1, [r1]
	blx r1
	mov r1, #0
	ldr r0, _0221DB4C ; =0x02241B04
	str r1, [r0]
_0221DB44:
	mov r0, #1
	pop {r4, r5, r6}
	pop {r3}
	bx r3
	.align 2, 0
_0221DB4C: .word MOD13_02241B04
_0221DB50: .word MOD13_02241ABC

	thumb_func_start MOD13_0221DB54
MOD13_0221DB54: ; 0x0221DB54
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r6, r0, #0
	mov r5, #1
	ldr r0, _0221DBFC ; =0x02241B20
	str r6, [r0]
	bl MOD13_0221DCA4
	mov r0, #0xd0
	add r7, r6, #0
	mul r7, r0
	ldr r0, _0221DC00 ; =0x000024D0
	add r1, r7, r0
	mov r0, #0xc0
	mul r6, r0
	add r0, r1, r6
	ldr r1, _0221DC04 ; =0x02241AB4
	ldr r1, [r1]
	blx r1
	ldr r1, _0221DC08 ; =0x02241B04
	str r0, [r1]
	cmp r0, #0
	bne _0221DB8E
	mov r0, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221DB8E:
	mov r3, #0x1f
	add r1, r0, r3
	bic r1, r3
	ldr r0, _0221DC0C ; =0x02241AF0
	str r1, [r0]
	ldr r0, _0221DC10 ; =0x00002490
	add r2, r7, r0
	add r0, r1, r2
	add r6, r0, r3
	bic r6, r3
	ldr r0, _0221DC14 ; =0x02241B0C
	str r6, [r0]
	ldr r0, _0221DC18 ; =MOD13_0221DC28
	bl MOD13_0221DD4C
	cmp r0, #0
	bne _0221DBBC
	lsl r0, r5, #0
	mvn r0, r0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221DBBC:
	mov r0, #0xa
	bl OS_Sleep
	bl MOD13_0221DC64
	cmp r0, #0
	beq _0221DBEE
	mov r7, #0
	mov r1, #1
	mvn r6, r1
_0221DBD0:
	cmp r0, #4
	beq _0221DBE6
	cmp r0, #5
	beq _0221DBE6
	cmp r0, #6
	bne _0221DBE2
	add r5, r7, #0
	mov r4, #1
	b _0221DBE6
_0221DBE2:
	add r5, r7, #0
	add r4, r6, #0
_0221DBE6:
	bl MOD13_0221DC64
	cmp r0, #0
	bne _0221DBD0
_0221DBEE:
	cmp r5, #0
	bne _0221DBBC
	add r0, r4, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_0221DBFC: .word MOD13_02241B20
_0221DC00: .word 0x000024D0
_0221DC04: .word MOD13_02241AB4
_0221DC08: .word MOD13_02241B04
_0221DC0C: .word MOD13_02241AF0
_0221DC10: .word 0x00002490
_0221DC14: .word MOD13_02241B0C
_0221DC18: .word MOD13_0221DC28

	thumb_func_start MOD13_0221DC1C
MOD13_0221DC1C: ; 0x0221DC1C
	mov r1, #0
	ldr r3, _0221DC24 ; =MOD13_0221DC28
	bx r3
	nop
_0221DC24: .word MOD13_0221DC28

	thumb_func_start MOD13_0221DC28
MOD13_0221DC28: ; 0x0221DC28
	push {r4}
	sub sp, #4
	ldr r1, _0221DC58 ; =0x02241B1C
	ldr r2, [r1]
	ldr r1, _0221DC5C ; =0x02241B18
	ldr r3, [r1]
	add r4, r3, #1
	cmp r4, r2
	beq _0221DC50
	add r2, r2, #3
	cmp r3, r2
	beq _0221DC50
	lsl r3, r3, #2
	ldr r2, _0221DC60 ; =0x02241B4C
	str r0, [r2, r3]
	str r4, [r1]
	cmp r4, #4
	blt _0221DC50
	mov r0, #0
	str r0, [r1]
_0221DC50:
	add sp, #4
	pop {r4}
	bx lr
	nop
_0221DC58: .word MOD13_02241B1C
_0221DC5C: .word MOD13_02241B18
_0221DC60: .word MOD13_02241B4C

	thumb_func_start MOD13_0221DC64
MOD13_0221DC64: ; 0x0221DC64
	push {r4, lr}
	bl OS_DisableInterrupts
	ldr r3, _0221DC98 ; =0x02241B1C
	ldr r1, [r3]
	ldr r2, _0221DC9C ; =0x02241B18
	ldr r2, [r2]
	cmp r2, r1
	bne _0221DC7A
	mov r4, #0
	b _0221DC8C
_0221DC7A:
	lsl r4, r1, #2
	ldr r2, _0221DCA0 ; =0x02241B4C
	ldr r4, [r2, r4]
	add r1, r1, #1
	str r1, [r3]
	cmp r1, #4
	blt _0221DC8C
	mov r1, #0
	str r1, [r3]
_0221DC8C:
	bl OS_RestoreInterrupts
	add r0, r4, #0
	pop {r4}
	pop {r3}
	bx r3
	.align 2, 0
_0221DC98: .word MOD13_02241B1C
_0221DC9C: .word MOD13_02241B18
_0221DCA0: .word MOD13_02241B4C

	thumb_func_start MOD13_0221DCA4
MOD13_0221DCA4: ; 0x0221DCA4
	push {lr}
	sub sp, #4
	bl OS_DisableInterrupts
	mov r3, #0
	ldr r1, _0221DCCC ; =0x02241B18
	str r3, [r1]
	ldr r1, _0221DCD0 ; =0x02241B1C
	str r3, [r1]
	ldr r2, _0221DCD4 ; =0x02241B4C
	add r1, r3, #0
_0221DCBA:
	stmia r2!, {r1}
	add r3, r3, #1
	cmp r3, #4
	blt _0221DCBA
	bl OS_RestoreInterrupts
	add sp, #4
	pop {r3}
	bx r3
	.align 2, 0
_0221DCCC: .word MOD13_02241B18
_0221DCD0: .word MOD13_02241B1C
_0221DCD4: .word MOD13_02241B4C

	thumb_func_start MOD13_0221DCD8
MOD13_0221DCD8: ; 0x0221DCD8
	push {r4, lr}
	add r4, r1, #0
	cmp r4, #0
	beq _0221DCF8
	cmp r2, #0
	ble _0221DCF8
	ldr r0, _0221DD00 ; =0x02241B6C
	bl OS_LockMutex
	add r0, r4, #0
	ldr r1, _0221DD04 ; =0x02241ABC
	ldr r1, [r1]
	blx r1
	ldr r0, _0221DD00 ; =0x02241B6C
	bl OS_UnlockMutex
_0221DCF8:
	pop {r4}
	pop {r3}
	bx r3
	nop
_0221DD00: .word MOD13_02241B6C
_0221DD04: .word MOD13_02241ABC

	thumb_func_start MOD13_0221DD08
MOD13_0221DD08: ; 0x0221DD08
	push {r4, lr}
	add r4, r1, #0
	cmp r4, #0
	ble _0221DD2E
	ldr r0, _0221DD38 ; =0x02241B6C
	bl OS_LockMutex
	add r0, r4, #0
	ldr r1, _0221DD3C ; =0x02241AB4
	ldr r1, [r1]
	blx r1
	add r4, r0, #0
	ldr r0, _0221DD38 ; =0x02241B6C
	bl OS_UnlockMutex
	add r0, r4, #0
	pop {r4}
	pop {r3}
	bx r3
_0221DD2E:
	mov r0, #0
	pop {r4}
	pop {r3}
	bx r3
	nop
_0221DD38: .word MOD13_02241B6C
_0221DD3C: .word MOD13_02241AB4

	thumb_func_start MOD13_0221DD40
MOD13_0221DD40: ; 0x0221DD40
	ldr r0, _0221DD48 ; =0x02241ADC
	ldr r0, [r0]
	bx lr
	nop
_0221DD48: .word MOD13_02241ADC

	thumb_func_start MOD13_0221DD4C
MOD13_0221DD4C: ; 0x0221DD4C
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r6, r0, #0
	add r5, r1, #0
	add r7, r2, #0
	bl OS_DisableInterrupts
	add r4, r0, #0
	ldr r0, _0221DE20 ; =0x02241AD8
	str r5, [r0]
	add r2, r5, #0
	add r2, #0x63
	mov r0, #3
	bic r2, r0
	ldr r0, _0221DE24 ; =0x02241AB8
	str r2, [r0]
	add r1, r2, #0
	add r1, #0x2f
	mov r3, #0x1f
	bic r1, r3
	ldr r3, _0221DE28 ; =0x02241AEC
	str r1, [r3]
	ldr r3, _0221DE2C ; =0x0000231F
	add r1, r1, r3
	mov r3, #0x1f
	bic r1, r3
	ldr r3, _0221DE30 ; =0x02241AFC
	str r1, [r3]
	add r1, #0xdf
	mov r3, #0x1f
	bic r1, r3
	str r1, [r2, #4]
	ldr r1, [r0]
	add r3, r5, r7
	ldr r2, [r1, #4]
	sub r2, r3, r2
	str r2, [r1, #8]
	mov r2, #0
	ldr r1, [r0]
	str r2, [r1, #0xc]
	ldr r1, [r0]
	mov r0, #3
	str r0, [r1]
	ldr r0, _0221DE34 ; =0x02241B30
	str r6, [r0]
	ldr r0, _0221DE38 ; =0x02241ADC
	ldr r0, [r0]
	cmp r0, #0
	bne _0221DDD2
	ldr r0, _0221DE28 ; =0x02241AEC
	ldr r0, [r0]
	ldr r1, _0221DE3C ; =0x00002300
	bl WCM_Init
	cmp r0, #0
	beq _0221DDCC
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221DDCC:
	mov r1, #1
	ldr r0, _0221DE38 ; =0x02241ADC
	str r1, [r0]
_0221DDD2:
	ldr r0, _0221DE38 ; =0x02241ADC
	ldr r0, [r0]
	cmp r0, #1
	bne _0221DE0E
	ldr r0, _0221DE24 ; =0x02241AB8
	ldr r0, [r0]
	ldr r1, _0221DE40 ; =MOD13_0221E178
	bl WCM_StartupAsync
	cmp r0, #3
	beq _0221DDF8
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221DDF8:
	mov r1, #4
	ldr r0, _0221DE38 ; =0x02241ADC
	str r1, [r0]
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221DE0E:
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_0221DE20: .word MOD13_02241AD8
_0221DE24: .word MOD13_02241AB8
_0221DE28: .word MOD13_02241AEC
_0221DE2C: .word 0x0000231F
_0221DE30: .word MOD13_02241AFC
_0221DE34: .word MOD13_02241B30
_0221DE38: .word MOD13_02241ADC
_0221DE3C: .word 0x00002300
_0221DE40: .word MOD13_0221E178

	thumb_func_start MOD13_0221DE44
MOD13_0221DE44: ; 0x0221DE44
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r7, r0, #0
	add r5, r1, #0
	add r6, r2, #0
	bl OS_DisableInterrupts
	add r4, r0, #0
	ldr r0, _0221DEE4 ; =0x02241B08
	str r6, [r0]
	cmp r5, #0
	beq _0221DE6A
	add r0, r5, #0
	ldr r1, _0221DEE8 ; =0x02241AD8
	ldr r1, [r1]
	mov r2, #0x60
	bl MI_CpuCopy8
	b _0221DE76
_0221DE6A:
	ldr r0, _0221DEE8 ; =0x02241AD8
	ldr r0, [r0]
	mov r1, #0
	mov r2, #0x60
	bl MI_CpuFill8
_0221DE76:
	add r0, r7, #0
	ldr r1, _0221DEEC ; =0x02241AFC
	ldr r1, [r1]
	mov r2, #0xc0
	bl MIi_CpuCopy32
	bl MOD13_0221E0F4
	cmp r0, #1
	bne _0221DEA0
	mov r1, #8
	ldr r0, _0221DEF0 ; =0x02241ADC
	str r1, [r0]
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221DEA0:
	ldr r0, _0221DEF0 ; =0x02241ADC
	ldr r0, [r0]
	cmp r0, #3
	bne _0221DED2
	ldr r0, _0221DEEC ; =0x02241AFC
	ldr r0, [r0]
	ldr r1, _0221DEE8 ; =0x02241AD8
	ldr r1, [r1]
	ldr r2, _0221DEE4 ; =0x02241B08
	ldr r2, [r2]
	bl WCM_ConnectAsync
	cmp r0, #3
	bne _0221DED2
	mov r1, #8
	ldr r0, _0221DEF0 ; =0x02241ADC
	str r1, [r0]
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221DED2:
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	nop
_0221DEE4: .word MOD13_02241B08
_0221DEE8: .word MOD13_02241AD8
_0221DEEC: .word MOD13_02241AFC
_0221DEF0: .word MOD13_02241ADC

	thumb_func_start MOD13_0221DEF4
MOD13_0221DEF4: ; 0x0221DEF4
	push {r4, lr}
	bl OS_DisableInterrupts
	add r4, r0, #0
	ldr r0, _0221DF58 ; =0x02241ADC
	ldr r0, [r0]
	cmp r0, #3
	bne _0221DF2E
	bl WCM_CleanupAsync
	cmp r0, #3
	beq _0221DF1A
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	pop {r4}
	pop {r3}
	bx r3
_0221DF1A:
	mov r1, #2
	ldr r0, _0221DF58 ; =0x02241ADC
	str r1, [r0]
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	pop {r4}
	pop {r3}
	bx r3
_0221DF2E:
	bl MOD13_0221E0F4
	cmp r0, #1
	bne _0221DF4A
	mov r1, #2
	ldr r0, _0221DF58 ; =0x02241ADC
	str r1, [r0]
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	pop {r4}
	pop {r3}
	bx r3
_0221DF4A:
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	pop {r4}
	pop {r3}
	bx r3
	.align 2, 0
_0221DF58: .word MOD13_02241ADC

	thumb_func_start MOD13_0221DF5C
MOD13_0221DF5C: ; 0x0221DF5C
	push {r4, lr}
	bl OS_DisableInterrupts
	add r4, r0, #0
	ldr r0, _0221DF98 ; =0x02241ADC
	ldr r0, [r0]
	cmp r0, #7
	bne _0221DF88
	bl WCM_DisconnectAsync
	cmp r0, #3
	bne _0221DF88
	mov r1, #4
	ldr r0, _0221DF98 ; =0x02241ADC
	str r1, [r0]
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	pop {r4}
	pop {r3}
	bx r3
_0221DF88:
	add r0, r4, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	pop {r4}
	pop {r3}
	bx r3
	nop
_0221DF98: .word MOD13_02241ADC

	thumb_func_start MOD13_0221DF9C
MOD13_0221DF9C: ; 0x0221DF9C
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r5, r0, #0
	add r4, r1, #0
	add r6, r2, #0
	str r3, [sp]
	bl OS_DisableInterrupts
	add r7, r0, #0
	ldr r1, _0221E088 ; =0x02241B10
	ldr r0, [sp]
	str r0, [r1]
	ldr r0, _0221E08C ; =0x02241B44
	ldr r1, _0221E090 ; =0x02241AF4
	str r0, [r1]
	cmp r5, #0
	beq _0221DFD0
	mov r2, #0
_0221DFC0:
	ldrb r1, [r5]
	add r5, r5, #1
	strb r1, [r0]
	add r0, r0, #1
	add r2, r2, #1
	cmp r2, #6
	blt _0221DFC0
	b _0221DFDE
_0221DFD0:
	mov r1, #0xff
	mov r2, #6
	bl MI_CpuFill8
	ldr r1, _0221E094 ; =0x020FF590
	ldr r0, _0221E090 ; =0x02241AF4
	str r1, [r0]
_0221DFDE:
	ldr r2, _0221E098 ; =0x02241BA4
	ldr r0, _0221E09C ; =0x02241AF8
	str r2, [r0]
	cmp r4, #0
	beq _0221E01A
	cmp r6, #0
	ble _0221E01A
	cmp r6, #0x20
	bge _0221E01A
	mov r1, #0
	cmp r6, #0
	ble _0221E004
_0221DFF6:
	ldrb r0, [r4]
	add r4, r4, #1
	strb r0, [r2]
	add r2, r2, #1
	add r1, r1, #1
	cmp r1, r6
	blt _0221DFF6
_0221E004:
	cmp r1, #0x20
	bge _0221E02A
	ldr r0, _0221E098 ; =0x02241BA4
	add r2, r0, r1
	mov r0, #0
_0221E00E:
	strb r0, [r2]
	add r2, r2, #1
	add r1, r1, #1
	cmp r1, #0x20
	blt _0221E00E
	b _0221E02A
_0221E01A:
	ldr r0, _0221E098 ; =0x02241BA4
	mov r1, #0xff
	mov r2, #0x20
	bl MI_CpuFill8
	ldr r1, _0221E0A0 ; =0x020FF598
	ldr r0, _0221E09C ; =0x02241AF8
	str r1, [r0]
_0221E02A:
	ldr r0, _0221E0A4 ; =0x02241ADC
	ldr r0, [r0]
	cmp r0, #3
	bne _0221E05A
	ldr r0, _0221E08C ; =0x02241B44
	ldr r1, _0221E09C ; =0x02241AF8
	ldr r1, [r1]
	ldr r2, _0221E088 ; =0x02241B10
	ldr r2, [r2]
	bl WCM_SearchAsync
	cmp r0, #3
	bne _0221E078
	mov r1, #6
	ldr r0, _0221E0A4 ; =0x02241ADC
	str r1, [r0]
	add r0, r7, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221E05A:
	bl MOD13_0221E0F4
	cmp r0, #1
	bne _0221E078
	mov r1, #6
	ldr r0, _0221E0A4 ; =0x02241ADC
	str r1, [r0]
	add r0, r7, #0
	bl OS_RestoreInterrupts
	mov r0, #1
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
_0221E078:
	add r0, r7, #0
	bl OS_RestoreInterrupts
	mov r0, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0
_0221E088: .word MOD13_02241B10
_0221E08C: .word MOD13_02241B44
_0221E090: .word MOD13_02241AF4
_0221E094: .word 0x020FF590
_0221E098: .word MOD13_02241BA4
_0221E09C: .word MOD13_02241AF8
_0221E0A0: .word 0x020FF598
_0221E0A4: .word MOD13_02241ADC

	thumb_func_start MOD13_0221E0A8
MOD13_0221E0A8: ; 0x0221E0A8
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	add r5, r0, #0
	add r7, r1, #0
	mov r0, #1
	bl WCM_LockApList
	bl WCM_CountApList
	add r6, r0, #0
	cmp r6, #0
	ble _0221E0E2
	mov r4, #0
	cmp r6, #0
	ble _0221E0E2
_0221E0C6:
	cmp r4, r7
	bge _0221E0E2
	lsl r0, r4, #0x10
	lsr r0, r0, #0x10
	bl WCM_PointApList
	add r1, r5, #0
	mov r2, #0xc0
	bl MIi_CpuCopy32
	add r4, r4, #1
	add r5, #0xc0
	cmp r4, r6
	blt _0221E0C6
_0221E0E2:
	mov r0, #0
	bl WCM_LockApList
	add r0, r6, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r3}
	bx r3
	.align 2, 0

	thumb_func_start MOD13_0221E0F4
MOD13_0221E0F4: ; 0x0221E0F4
	push {lr}
	sub sp, #4
	ldr r0, _0221E16C ; =0x02241ADC
	ldr r0, [r0]
	cmp r0, #8
	bhi _0221E15C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #8]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add r0, pc
	bx r0
_0221E10E: ; jump table
	.short _0221E15C - _0221E10E + 1 ; case 0
	.short _0221E146 - _0221E10E + 1 ; case 1
	.short _0221E15C - _0221E10E + 1 ; case 2
	.short _0221E15C - _0221E10E + 1 ; case 3
	.short _0221E15C - _0221E10E + 1 ; case 4
	.short _0221E120 - _0221E10E + 1 ; case 5
	.short _0221E15C - _0221E10E + 1 ; case 6
	.short _0221E136 - _0221E10E + 1 ; case 7
	.short _0221E15C - _0221E10E + 1 ; case 8
_0221E120:
	mov r0, #0
	add r1, r0, #0
	add r2, r0, #0
	bl WCM_SearchAsync
	cmp r0, #3
	beq _0221E164
	mov r0, #0
	add sp, #4
	pop {r3}
	bx r3
_0221E136:
	bl WCM_DisconnectAsync
	cmp r0, #3
	beq _0221E164
	mov r0, #0
	add sp, #4
	pop {r3}
	bx r3
_0221E146:
	ldr r0, _0221E170 ; =0x02241AB8
	ldr r0, [r0]
	ldr r1, _0221E174 ; =MOD13_0221E178
	bl WCM_StartupAsync
	cmp r0, #3
	beq _0221E164
	mov r0, #0
	add sp, #4
	pop {r3}
	bx r3
_0221E15C:
	mov r0, #0
	add sp, #4
	pop {r3}
	bx r3
_0221E164:
	mov r0, #1
	add sp, #4
	pop {r3}
	bx r3
	.align 2, 0
_0221E16C: .word MOD13_02241ADC
_0221E170: .word MOD13_02241AB8
_0221E174: .word MOD13_0221E178

	thumb_func_start MOD13_0221E178
MOD13_0221E178: ; 0x0221E178
	push {lr}
	sub sp, #4
	cmp r0, #0
	bne _0221E182
	b _0221E556
_0221E182:
	mov r1, #0
	ldrsh r2, [r0, r1]
	cmp r2, #9
	bls _0221E18C
	b _0221E548
_0221E18C:
	add r2, r2, r2
	add r2, pc
	ldrh r2, [r2, #8]
	lsl r2, r2, #0x10
	asr r2, r2, #0x10
	add r2, pc
	bx r2
_0221E19A: ; jump table
	.short _0221E548 - _0221E19A + 1 ; case 0
	.short _0221E1AE - _0221E19A + 1 ; case 1
	.short _0221E4A0 - _0221E19A + 1 ; case 2
	.short _0221E25E - _0221E19A + 1 ; case 3
	.short _0221E2E6 - _0221E19A + 1 ; case 4
	.short _0221E2A2 - _0221E19A + 1 ; case 5
	.short _0221E3C0 - _0221E19A + 1 ; case 6
	.short _0221E4E4 - _0221E19A + 1 ; case 7
	.short _0221E4FE - _0221E19A + 1 ; case 8
	.short _0221E510 - _0221E19A + 1 ; case 9
_0221E1AE:
	mov r2, #2
	ldrsh r0, [r0, r2]
	cmp r0, #0
	bne _0221E244
	ldr r0, _0221E518 ; =0x02241ADC
	ldr r2, [r0]
	cmp r2, #4
	bne _0221E1D6
	mov r2, #3
	str r2, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E1CC
	b _0221E556
_0221E1CC:
	mov r0, #6
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E1D6:
	cmp r2, #6
	bne _0221E20C
	ldr r0, _0221E520 ; =0x02241AF4
	ldr r0, [r0]
	ldr r1, _0221E524 ; =0x02241AF8
	ldr r1, [r1]
	ldr r2, _0221E528 ; =0x02241B10
	ldr r2, [r2]
	bl WCM_SearchAsync
	cmp r0, #3
	bne _0221E1F0
	b _0221E556
_0221E1F0:
	mov r1, #3
	ldr r0, _0221E518 ; =0x02241ADC
	str r1, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E200
	b _0221E556
_0221E200:
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E20C:
	cmp r2, #8
	beq _0221E212
	b _0221E556
_0221E212:
	ldr r0, _0221E52C ; =0x02241AFC
	ldr r0, [r0]
	ldr r1, _0221E530 ; =0x02241AD8
	ldr r1, [r1]
	ldr r2, _0221E534 ; =0x02241B08
	ldr r2, [r2]
	bl WCM_ConnectAsync
	cmp r0, #3
	bne _0221E228
	b _0221E556
_0221E228:
	mov r1, #3
	ldr r0, _0221E518 ; =0x02241ADC
	str r1, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E238
	b _0221E556
_0221E238:
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E244:
	mov r3, #1
	ldr r0, _0221E518 ; =0x02241ADC
	str r3, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r3, [r0]
	cmp r3, #0
	bne _0221E254
	b _0221E556
_0221E254:
	add r0, r2, #0
	blx r3
	add sp, #4
	pop {r3}
	bx r3
_0221E25E:
	mov r2, #2
	ldrsh r0, [r0, r2]
	cmp r0, #0
	bne _0221E288
	ldr r0, _0221E518 ; =0x02241ADC
	ldr r2, [r0]
	cmp r2, #6
	beq _0221E270
	b _0221E556
_0221E270:
	mov r2, #5
	str r2, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E27E
	b _0221E556
_0221E27E:
	mov r0, #8
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E288:
	mov r2, #3
	ldr r0, _0221E518 ; =0x02241ADC
	str r2, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E298
	b _0221E556
_0221E298:
	mov r0, #9
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E2A2:
	mov r2, #2
	ldrsh r0, [r0, r2]
	cmp r0, #0
	bne _0221E2CC
	ldr r0, _0221E518 ; =0x02241ADC
	ldr r2, [r0]
	cmp r2, #8
	beq _0221E2B4
	b _0221E556
_0221E2B4:
	mov r2, #7
	str r2, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E2C2
	b _0221E556
_0221E2C2:
	mov r0, #0xc
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E2CC:
	mov r2, #3
	ldr r0, _0221E518 ; =0x02241ADC
	str r2, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E2DC
	b _0221E556
_0221E2DC:
	mov r0, #0xd
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E2E6:
	mov r2, #2
	ldrsh r0, [r0, r2]
	cmp r0, #0
	bne _0221E3A6
	ldr r0, _0221E518 ; =0x02241ADC
	ldr r2, [r0]
	cmp r2, #4
	bne _0221E30E
	mov r2, #3
	str r2, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E304
	b _0221E556
_0221E304:
	mov r0, #0xa
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E30E:
	cmp r2, #6
	bne _0221E344
	ldr r0, _0221E520 ; =0x02241AF4
	ldr r0, [r0]
	ldr r1, _0221E524 ; =0x02241AF8
	ldr r1, [r1]
	ldr r2, _0221E528 ; =0x02241B10
	ldr r2, [r2]
	bl WCM_SearchAsync
	cmp r0, #3
	bne _0221E328
	b _0221E556
_0221E328:
	mov r1, #3
	ldr r0, _0221E518 ; =0x02241ADC
	str r1, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E338
	b _0221E556
_0221E338:
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E344:
	cmp r2, #2
	bne _0221E36E
	bl WCM_CleanupAsync
	cmp r0, #3
	bne _0221E352
	b _0221E556
_0221E352:
	mov r1, #3
	ldr r0, _0221E518 ; =0x02241ADC
	str r1, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E362
	b _0221E556
_0221E362:
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E36E:
	cmp r2, #8
	beq _0221E374
	b _0221E556
_0221E374:
	ldr r0, _0221E52C ; =0x02241AFC
	ldr r0, [r0]
	ldr r1, _0221E530 ; =0x02241AD8
	ldr r1, [r1]
	ldr r2, _0221E534 ; =0x02241B08
	ldr r2, [r2]
	bl WCM_ConnectAsync
	cmp r0, #3
	bne _0221E38A
	b _0221E556
_0221E38A:
	mov r1, #3
	ldr r0, _0221E518 ; =0x02241ADC
	str r1, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E39A
	b _0221E556
_0221E39A:
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E3A6:
	mov r2, #3
	ldr r0, _0221E518 ; =0x02241ADC
	str r2, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E3B6
	b _0221E556
_0221E3B6:
	mov r0, #0xb
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E3C0:
	mov r2, #2
	ldrsh r0, [r0, r2]
	cmp r0, #0
	bne _0221E488
	ldr r0, _0221E518 ; =0x02241ADC
	ldr r2, [r0]
	cmp r2, #4
	bne _0221E3E8
	mov r2, #3
	str r2, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E3DE
	b _0221E556
_0221E3DE:
	mov r0, #0xe
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E3E8:
	cmp r2, #6
	bne _0221E41E
	ldr r0, _0221E520 ; =0x02241AF4
	ldr r0, [r0]
	ldr r1, _0221E524 ; =0x02241AF8
	ldr r1, [r1]
	ldr r2, _0221E528 ; =0x02241B10
	ldr r2, [r2]
	bl WCM_SearchAsync
	cmp r0, #3
	bne _0221E402
	b _0221E556
_0221E402:
	mov r1, #3
	ldr r0, _0221E518 ; =0x02241ADC
	str r1, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E412
	b _0221E556
_0221E412:
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E41E:
	cmp r2, #2
	bne _0221E448
	bl WCM_CleanupAsync
	cmp r0, #3
	bne _0221E42C
	b _0221E556
_0221E42C:
	mov r1, #3
	ldr r0, _0221E518 ; =0x02241ADC
	str r1, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	bne _0221E43C
	b _0221E556
_0221E43C:
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E448:
	cmp r2, #8
	bne _0221E47A
	ldr r0, _0221E52C ; =0x02241AFC
	ldr r0, [r0]
	ldr r1, _0221E530 ; =0x02241AD8
	ldr r1, [r1]
	ldr r2, _0221E534 ; =0x02241B08
	ldr r2, [r2]
	bl WCM_ConnectAsync
	cmp r0, #3
	beq _0221E556
	mov r1, #3
	ldr r0, _0221E518 ; =0x02241ADC
	str r1, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	beq _0221E556
	mov r0, #2
	mov r1, #0
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E47A:
	cmp r2, #7
	bne _0221E556
	mov r1, #3
	str r1, [r0]
	add sp, #4
	pop {r3}
	bx r3
_0221E488:
	mov r2, #3
	ldr r0, _0221E518 ; =0x02241ADC
	str r2, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	beq _0221E556
	mov r0, #0xf
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E4A0:
	mov r2, #2
	ldrsh r0, [r0, r2]
	cmp r0, #0
	bne _0221E4CC
	ldr r0, _0221E518 ; =0x02241ADC
	ldr r0, [r0]
	cmp r0, #2
	bne _0221E556
	bl WCM_Finish
	mov r1, #0
	ldr r0, _0221E518 ; =0x02241ADC
	str r1, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	beq _0221E556
	mov r0, #0x14
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E4CC:
	mov r3, #3
	ldr r0, _0221E518 ; =0x02241ADC
	str r3, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	ldr r3, [r0]
	cmp r3, #0
	beq _0221E556
	add r0, r2, #0
	blx r3
	add sp, #4
	pop {r3}
	bx r3
_0221E4E4:
	ldr r0, _0221E518 ; =0x02241ADC
	ldr r0, [r0]
	cmp r0, #5
	bne _0221E556
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	beq _0221E556
	mov r0, #5
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E4FE:
	ldr r0, _0221E51C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	beq _0221E556
	mov r0, #4
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E510:
	ldr r0, _0221E518 ; =0x02241ADC
	str r1, [r0]
	ldr r0, _0221E51C ; =0x02241B30
	b _0221E538
	.align 2, 0
_0221E518: .word MOD13_02241ADC
_0221E51C: .word MOD13_02241B30
_0221E520: .word MOD13_02241AF4
_0221E524: .word MOD13_02241AF8
_0221E528: .word MOD13_02241B10
_0221E52C: .word MOD13_02241AFC
_0221E530: .word MOD13_02241AD8
_0221E534: .word MOD13_02241B08
_0221E538:
	ldr r2, [r0]
	cmp r2, #0
	beq _0221E556
	mov r0, #3
	blx r2
	add sp, #4
	pop {r3}
	bx r3
_0221E548:
	ldr r0, _0221E55C ; =0x02241B30
	ldr r2, [r0]
	cmp r2, #0
	beq _0221E556
	mov r0, #1
	mov r1, #0
	blx r2
_0221E556:
	add sp, #4
	pop {r3}
	bx r3
	.align 2, 0
_0221E55C: .word MOD13_02241B30

	.rodata
	.global MOD13_0223C444
MOD13_0223C444: ; 0x0223C444
	.byte 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x08
	.byte 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x80
	.byte 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x36

	.global MOD13_0223C46C
MOD13_0223C46C: ; 0x0223C46C
	.byte 0xF4, 0x51, 0x50, 0xA7, 0x41, 0x7E, 0x53, 0x65, 0x17, 0x1A, 0xC3, 0xA4, 0x27, 0x3A, 0x96, 0x5E
	.byte 0xAB, 0x3B, 0xCB, 0x6B, 0x9D, 0x1F, 0xF1, 0x45, 0xFA, 0xAC, 0xAB, 0x58, 0xE3, 0x4B, 0x93, 0x03
	.byte 0x30, 0x20, 0x55, 0xFA, 0x76, 0xAD, 0xF6, 0x6D, 0xCC, 0x88, 0x91, 0x76, 0x02, 0xF5, 0x25, 0x4C
	.byte 0xE5, 0x4F, 0xFC, 0xD7, 0x2A, 0xC5, 0xD7, 0xCB, 0x35, 0x26, 0x80, 0x44, 0x62, 0xB5, 0x8F, 0xA3
	.byte 0xB1, 0xDE, 0x49, 0x5A, 0xBA, 0x25, 0x67, 0x1B, 0xEA, 0x45, 0x98, 0x0E, 0xFE, 0x5D, 0xE1, 0xC0
	.byte 0x2F, 0xC3, 0x02, 0x75, 0x4C, 0x81, 0x12, 0xF0, 0x46, 0x8D, 0xA3, 0x97, 0xD3, 0x6B, 0xC6, 0xF9
	.byte 0x8F, 0x03, 0xE7, 0x5F, 0x92, 0x15, 0x95, 0x9C, 0x6D, 0xBF, 0xEB, 0x7A, 0x52, 0x95, 0xDA, 0x59
	.byte 0xBE, 0xD4, 0x2D, 0x83, 0x74, 0x58, 0xD3, 0x21, 0xE0, 0x49, 0x29, 0x69, 0xC9, 0x8E, 0x44, 0xC8
	.byte 0xC2, 0x75, 0x6A, 0x89, 0x8E, 0xF4, 0x78, 0x79, 0x58, 0x99, 0x6B, 0x3E, 0xB9, 0x27, 0xDD, 0x71
	.byte 0xE1, 0xBE, 0xB6, 0x4F, 0x88, 0xF0, 0x17, 0xAD, 0x20, 0xC9, 0x66, 0xAC, 0xCE, 0x7D, 0xB4, 0x3A
	.byte 0xDF, 0x63, 0x18, 0x4A, 0x1A, 0xE5, 0x82, 0x31, 0x51, 0x97, 0x60, 0x33, 0x53, 0x62, 0x45, 0x7F
	.byte 0x64, 0xB1, 0xE0, 0x77, 0x6B, 0xBB, 0x84, 0xAE, 0x81, 0xFE, 0x1C, 0xA0, 0x08, 0xF9, 0x94, 0x2B
	.byte 0x48, 0x70, 0x58, 0x68, 0x45, 0x8F, 0x19, 0xFD, 0xDE, 0x94, 0x87, 0x6C, 0x7B, 0x52, 0xB7, 0xF8
	.byte 0x73, 0xAB, 0x23, 0xD3, 0x4B, 0x72, 0xE2, 0x02, 0x1F, 0xE3, 0x57, 0x8F, 0x55, 0x66, 0x2A, 0xAB
	.byte 0xEB, 0xB2, 0x07, 0x28, 0xB5, 0x2F, 0x03, 0xC2, 0xC5, 0x86, 0x9A, 0x7B, 0x37, 0xD3, 0xA5, 0x08
	.byte 0x28, 0x30, 0xF2, 0x87, 0xBF, 0x23, 0xB2, 0xA5, 0x03, 0x02, 0xBA, 0x6A, 0x16, 0xED, 0x5C, 0x82
	.byte 0xCF, 0x8A, 0x2B, 0x1C, 0x79, 0xA7, 0x92, 0xB4, 0x07, 0xF3, 0xF0, 0xF2, 0x69, 0x4E, 0xA1, 0xE2
	.byte 0xDA, 0x65, 0xCD, 0xF4, 0x05, 0x06, 0xD5, 0xBE, 0x34, 0xD1, 0x1F, 0x62, 0xA6, 0xC4, 0x8A, 0xFE
	.byte 0x2E, 0x34, 0x9D, 0x53, 0xF3, 0xA2, 0xA0, 0x55, 0x8A, 0x05, 0x32, 0xE1, 0xF6, 0xA4, 0x75, 0xEB
	.byte 0x83, 0x0B, 0x39, 0xEC, 0x60, 0x40, 0xAA, 0xEF, 0x71, 0x5E, 0x06, 0x9F, 0x6E, 0xBD, 0x51, 0x10
	.byte 0x21, 0x3E, 0xF9, 0x8A, 0xDD, 0x96, 0x3D, 0x06, 0x3E, 0xDD, 0xAE, 0x05, 0xE6, 0x4D, 0x46, 0xBD
	.byte 0x54, 0x91, 0xB5, 0x8D, 0xC4, 0x71, 0x05, 0x5D, 0x06, 0x04, 0x6F, 0xD4, 0x50, 0x60, 0xFF, 0x15
	.byte 0x98, 0x19, 0x24, 0xFB, 0xBD, 0xD6, 0x97, 0xE9, 0x40, 0x89, 0xCC, 0x43, 0xD9, 0x67, 0x77, 0x9E
	.byte 0xE8, 0xB0, 0xBD, 0x42, 0x89, 0x07, 0x88, 0x8B, 0x19, 0xE7, 0x38, 0x5B, 0xC8, 0x79, 0xDB, 0xEE
	.byte 0x7C, 0xA1, 0x47, 0x0A, 0x42, 0x7C, 0xE9, 0x0F, 0x84, 0xF8, 0xC9, 0x1E, 0x00, 0x00, 0x00, 0x00
	.byte 0x80, 0x09, 0x83, 0x86, 0x2B, 0x32, 0x48, 0xED, 0x11, 0x1E, 0xAC, 0x70, 0x5A, 0x6C, 0x4E, 0x72
	.byte 0x0E, 0xFD, 0xFB, 0xFF, 0x85, 0x0F, 0x56, 0x38, 0xAE, 0x3D, 0x1E, 0xD5, 0x2D, 0x36, 0x27, 0x39
	.byte 0x0F, 0x0A, 0x64, 0xD9, 0x5C, 0x68, 0x21, 0xA6, 0x5B, 0x9B, 0xD1, 0x54, 0x36, 0x24, 0x3A, 0x2E
	.byte 0x0A, 0x0C, 0xB1, 0x67, 0x57, 0x93, 0x0F, 0xE7, 0xEE, 0xB4, 0xD2, 0x96, 0x9B, 0x1B, 0x9E, 0x91
	.byte 0xC0, 0x80, 0x4F, 0xC5, 0xDC, 0x61, 0xA2, 0x20, 0x77, 0x5A, 0x69, 0x4B, 0x12, 0x1C, 0x16, 0x1A
	.byte 0x93, 0xE2, 0x0A, 0xBA, 0xA0, 0xC0, 0xE5, 0x2A, 0x22, 0x3C, 0x43, 0xE0, 0x1B, 0x12, 0x1D, 0x17
	.byte 0x09, 0x0E, 0x0B, 0x0D, 0x8B, 0xF2, 0xAD, 0xC7, 0xB6, 0x2D, 0xB9, 0xA8, 0x1E, 0x14, 0xC8, 0xA9
	.byte 0xF1, 0x57, 0x85, 0x19, 0x75, 0xAF, 0x4C, 0x07, 0x99, 0xEE, 0xBB, 0xDD, 0x7F, 0xA3, 0xFD, 0x60
	.byte 0x01, 0xF7, 0x9F, 0x26, 0x72, 0x5C, 0xBC, 0xF5, 0x66, 0x44, 0xC5, 0x3B, 0xFB, 0x5B, 0x34, 0x7E
	.byte 0x43, 0x8B, 0x76, 0x29, 0x23, 0xCB, 0xDC, 0xC6, 0xED, 0xB6, 0x68, 0xFC, 0xE4, 0xB8, 0x63, 0xF1
	.byte 0x31, 0xD7, 0xCA, 0xDC, 0x63, 0x42, 0x10, 0x85, 0x97, 0x13, 0x40, 0x22, 0xC6, 0x84, 0x20, 0x11
	.byte 0x4A, 0x85, 0x7D, 0x24, 0xBB, 0xD2, 0xF8, 0x3D, 0xF9, 0xAE, 0x11, 0x32, 0x29, 0xC7, 0x6D, 0xA1
	.byte 0x9E, 0x1D, 0x4B, 0x2F, 0xB2, 0xDC, 0xF3, 0x30, 0x86, 0x0D, 0xEC, 0x52, 0xC1, 0x77, 0xD0, 0xE3
	.byte 0xB3, 0x2B, 0x6C, 0x16, 0x70, 0xA9, 0x99, 0xB9, 0x94, 0x11, 0xFA, 0x48, 0xE9, 0x47, 0x22, 0x64
	.byte 0xFC, 0xA8, 0xC4, 0x8C, 0xF0, 0xA0, 0x1A, 0x3F, 0x7D, 0x56, 0xD8, 0x2C, 0x33, 0x22, 0xEF, 0x90
	.byte 0x49, 0x87, 0xC7, 0x4E, 0x38, 0xD9, 0xC1, 0xD1, 0xCA, 0x8C, 0xFE, 0xA2, 0xD4, 0x98, 0x36, 0x0B
	.byte 0xF5, 0xA6, 0xCF, 0x81, 0x7A, 0xA5, 0x28, 0xDE, 0xB7, 0xDA, 0x26, 0x8E, 0xAD, 0x3F, 0xA4, 0xBF
	.byte 0x3A, 0x2C, 0xE4, 0x9D, 0x78, 0x50, 0x0D, 0x92, 0x5F, 0x6A, 0x9B, 0xCC, 0x7E, 0x54, 0x62, 0x46
	.byte 0x8D, 0xF6, 0xC2, 0x13, 0xD8, 0x90, 0xE8, 0xB8, 0x39, 0x2E, 0x5E, 0xF7, 0xC3, 0x82, 0xF5, 0xAF
	.byte 0x5D, 0x9F, 0xBE, 0x80, 0xD0, 0x69, 0x7C, 0x93, 0xD5, 0x6F, 0xA9, 0x2D, 0x25, 0xCF, 0xB3, 0x12
	.byte 0xAC, 0xC8, 0x3B, 0x99, 0x18, 0x10, 0xA7, 0x7D, 0x9C, 0xE8, 0x6E, 0x63, 0x3B, 0xDB, 0x7B, 0xBB
	.byte 0x26, 0xCD, 0x09, 0x78, 0x59, 0x6E, 0xF4, 0x18, 0x9A, 0xEC, 0x01, 0xB7, 0x4F, 0x83, 0xA8, 0x9A
	.byte 0x95, 0xE6, 0x65, 0x6E, 0xFF, 0xAA, 0x7E, 0xE6, 0xBC, 0x21, 0x08, 0xCF, 0x15, 0xEF, 0xE6, 0xE8
	.byte 0xE7, 0xBA, 0xD9, 0x9B, 0x6F, 0x4A, 0xCE, 0x36, 0x9F, 0xEA, 0xD4, 0x09, 0xB0, 0x29, 0xD6, 0x7C
	.byte 0xA4, 0x31, 0xAF, 0xB2, 0x3F, 0x2A, 0x31, 0x23, 0xA5, 0xC6, 0x30, 0x94, 0xA2, 0x35, 0xC0, 0x66
	.byte 0x4E, 0x74, 0x37, 0xBC, 0x82, 0xFC, 0xA6, 0xCA, 0x90, 0xE0, 0xB0, 0xD0, 0xA7, 0x33, 0x15, 0xD8
	.byte 0x04, 0xF1, 0x4A, 0x98, 0xEC, 0x41, 0xF7, 0xDA, 0xCD, 0x7F, 0x0E, 0x50, 0x91, 0x17, 0x2F, 0xF6
	.byte 0x4D, 0x76, 0x8D, 0xD6, 0xEF, 0x43, 0x4D, 0xB0, 0xAA, 0xCC, 0x54, 0x4D, 0x96, 0xE4, 0xDF, 0x04
	.byte 0xD1, 0x9E, 0xE3, 0xB5, 0x6A, 0x4C, 0x1B, 0x88, 0x2C, 0xC1, 0xB8, 0x1F, 0x65, 0x46, 0x7F, 0x51
	.byte 0x5E, 0x9D, 0x04, 0xEA, 0x8C, 0x01, 0x5D, 0x35, 0x87, 0xFA, 0x73, 0x74, 0x0B, 0xFB, 0x2E, 0x41
	.byte 0x67, 0xB3, 0x5A, 0x1D, 0xDB, 0x92, 0x52, 0xD2, 0x10, 0xE9, 0x33, 0x56, 0xD6, 0x6D, 0x13, 0x47
	.byte 0xD7, 0x9A, 0x8C, 0x61, 0xA1, 0x37, 0x7A, 0x0C, 0xF8, 0x59, 0x8E, 0x14, 0x13, 0xEB, 0x89, 0x3C
	.byte 0xA9, 0xCE, 0xEE, 0x27, 0x61, 0xB7, 0x35, 0xC9, 0x1C, 0xE1, 0xED, 0xE5, 0x47, 0x7A, 0x3C, 0xB1
	.byte 0xD2, 0x9C, 0x59, 0xDF, 0xF2, 0x55, 0x3F, 0x73, 0x14, 0x18, 0x79, 0xCE, 0xC7, 0x73, 0xBF, 0x37
	.byte 0xF7, 0x53, 0xEA, 0xCD, 0xFD, 0x5F, 0x5B, 0xAA, 0x3D, 0xDF, 0x14, 0x6F, 0x44, 0x78, 0x86, 0xDB
	.byte 0xAF, 0xCA, 0x81, 0xF3, 0x68, 0xB9, 0x3E, 0xC4, 0x24, 0x38, 0x2C, 0x34, 0xA3, 0xC2, 0x5F, 0x40
	.byte 0x1D, 0x16, 0x72, 0xC3, 0xE2, 0xBC, 0x0C, 0x25, 0x3C, 0x28, 0x8B, 0x49, 0x0D, 0xFF, 0x41, 0x95
	.byte 0xA8, 0x39, 0x71, 0x01, 0x0C, 0x08, 0xDE, 0xB3, 0xB4, 0xD8, 0x9C, 0xE4, 0x56, 0x64, 0x90, 0xC1
	.byte 0xCB, 0x7B, 0x61, 0x84, 0x32, 0xD5, 0x70, 0xB6, 0x6C, 0x48, 0x74, 0x5C, 0xB8, 0xD0, 0x42, 0x57

	.global MOD13_0223C86C
MOD13_0223C86C: ; 0x0223C86C
	.byte 0x51, 0x50, 0xA7, 0xF4, 0x7E, 0x53, 0x65, 0x41, 0x1A, 0xC3, 0xA4, 0x17, 0x3A, 0x96, 0x5E, 0x27
	.byte 0x3B, 0xCB, 0x6B, 0xAB, 0x1F, 0xF1, 0x45, 0x9D, 0xAC, 0xAB, 0x58, 0xFA, 0x4B, 0x93, 0x03, 0xE3
	.byte 0x20, 0x55, 0xFA, 0x30, 0xAD, 0xF6, 0x6D, 0x76, 0x88, 0x91, 0x76, 0xCC, 0xF5, 0x25, 0x4C, 0x02
	.byte 0x4F, 0xFC, 0xD7, 0xE5, 0xC5, 0xD7, 0xCB, 0x2A, 0x26, 0x80, 0x44, 0x35, 0xB5, 0x8F, 0xA3, 0x62
	.byte 0xDE, 0x49, 0x5A, 0xB1, 0x25, 0x67, 0x1B, 0xBA, 0x45, 0x98, 0x0E, 0xEA, 0x5D, 0xE1, 0xC0, 0xFE
	.byte 0xC3, 0x02, 0x75, 0x2F, 0x81, 0x12, 0xF0, 0x4C, 0x8D, 0xA3, 0x97, 0x46, 0x6B, 0xC6, 0xF9, 0xD3
	.byte 0x03, 0xE7, 0x5F, 0x8F, 0x15, 0x95, 0x9C, 0x92, 0xBF, 0xEB, 0x7A, 0x6D, 0x95, 0xDA, 0x59, 0x52
	.byte 0xD4, 0x2D, 0x83, 0xBE, 0x58, 0xD3, 0x21, 0x74, 0x49, 0x29, 0x69, 0xE0, 0x8E, 0x44, 0xC8, 0xC9
	.byte 0x75, 0x6A, 0x89, 0xC2, 0xF4, 0x78, 0x79, 0x8E, 0x99, 0x6B, 0x3E, 0x58, 0x27, 0xDD, 0x71, 0xB9
	.byte 0xBE, 0xB6, 0x4F, 0xE1, 0xF0, 0x17, 0xAD, 0x88, 0xC9, 0x66, 0xAC, 0x20, 0x7D, 0xB4, 0x3A, 0xCE
	.byte 0x63, 0x18, 0x4A, 0xDF, 0xE5, 0x82, 0x31, 0x1A, 0x97, 0x60, 0x33, 0x51, 0x62, 0x45, 0x7F, 0x53
	.byte 0xB1, 0xE0, 0x77, 0x64, 0xBB, 0x84, 0xAE, 0x6B, 0xFE, 0x1C, 0xA0, 0x81, 0xF9, 0x94, 0x2B, 0x08
	.byte 0x70, 0x58, 0x68, 0x48, 0x8F, 0x19, 0xFD, 0x45, 0x94, 0x87, 0x6C, 0xDE, 0x52, 0xB7, 0xF8, 0x7B
	.byte 0xAB, 0x23, 0xD3, 0x73, 0x72, 0xE2, 0x02, 0x4B, 0xE3, 0x57, 0x8F, 0x1F, 0x66, 0x2A, 0xAB, 0x55
	.byte 0xB2, 0x07, 0x28, 0xEB, 0x2F, 0x03, 0xC2, 0xB5, 0x86, 0x9A, 0x7B, 0xC5, 0xD3, 0xA5, 0x08, 0x37
	.byte 0x30, 0xF2, 0x87, 0x28, 0x23, 0xB2, 0xA5, 0xBF, 0x02, 0xBA, 0x6A, 0x03, 0xED, 0x5C, 0x82, 0x16
	.byte 0x8A, 0x2B, 0x1C, 0xCF, 0xA7, 0x92, 0xB4, 0x79, 0xF3, 0xF0, 0xF2, 0x07, 0x4E, 0xA1, 0xE2, 0x69
	.byte 0x65, 0xCD, 0xF4, 0xDA, 0x06, 0xD5, 0xBE, 0x05, 0xD1, 0x1F, 0x62, 0x34, 0xC4, 0x8A, 0xFE, 0xA6
	.byte 0x34, 0x9D, 0x53, 0x2E, 0xA2, 0xA0, 0x55, 0xF3, 0x05, 0x32, 0xE1, 0x8A, 0xA4, 0x75, 0xEB, 0xF6
	.byte 0x0B, 0x39, 0xEC, 0x83, 0x40, 0xAA, 0xEF, 0x60, 0x5E, 0x06, 0x9F, 0x71, 0xBD, 0x51, 0x10, 0x6E
	.byte 0x3E, 0xF9, 0x8A, 0x21, 0x96, 0x3D, 0x06, 0xDD, 0xDD, 0xAE, 0x05, 0x3E, 0x4D, 0x46, 0xBD, 0xE6
	.byte 0x91, 0xB5, 0x8D, 0x54, 0x71, 0x05, 0x5D, 0xC4, 0x04, 0x6F, 0xD4, 0x06, 0x60, 0xFF, 0x15, 0x50
	.byte 0x19, 0x24, 0xFB, 0x98, 0xD6, 0x97, 0xE9, 0xBD, 0x89, 0xCC, 0x43, 0x40, 0x67, 0x77, 0x9E, 0xD9
	.byte 0xB0, 0xBD, 0x42, 0xE8, 0x07, 0x88, 0x8B, 0x89, 0xE7, 0x38, 0x5B, 0x19, 0x79, 0xDB, 0xEE, 0xC8
	.byte 0xA1, 0x47, 0x0A, 0x7C, 0x7C, 0xE9, 0x0F, 0x42, 0xF8, 0xC9, 0x1E, 0x84, 0x00, 0x00, 0x00, 0x00
	.byte 0x09, 0x83, 0x86, 0x80, 0x32, 0x48, 0xED, 0x2B, 0x1E, 0xAC, 0x70, 0x11, 0x6C, 0x4E, 0x72, 0x5A
	.byte 0xFD, 0xFB, 0xFF, 0x0E, 0x0F, 0x56, 0x38, 0x85, 0x3D, 0x1E, 0xD5, 0xAE, 0x36, 0x27, 0x39, 0x2D
	.byte 0x0A, 0x64, 0xD9, 0x0F, 0x68, 0x21, 0xA6, 0x5C, 0x9B, 0xD1, 0x54, 0x5B, 0x24, 0x3A, 0x2E, 0x36
	.byte 0x0C, 0xB1, 0x67, 0x0A, 0x93, 0x0F, 0xE7, 0x57, 0xB4, 0xD2, 0x96, 0xEE, 0x1B, 0x9E, 0x91, 0x9B
	.byte 0x80, 0x4F, 0xC5, 0xC0, 0x61, 0xA2, 0x20, 0xDC, 0x5A, 0x69, 0x4B, 0x77, 0x1C, 0x16, 0x1A, 0x12
	.byte 0xE2, 0x0A, 0xBA, 0x93, 0xC0, 0xE5, 0x2A, 0xA0, 0x3C, 0x43, 0xE0, 0x22, 0x12, 0x1D, 0x17, 0x1B
	.byte 0x0E, 0x0B, 0x0D, 0x09, 0xF2, 0xAD, 0xC7, 0x8B, 0x2D, 0xB9, 0xA8, 0xB6, 0x14, 0xC8, 0xA9, 0x1E
	.byte 0x57, 0x85, 0x19, 0xF1, 0xAF, 0x4C, 0x07, 0x75, 0xEE, 0xBB, 0xDD, 0x99, 0xA3, 0xFD, 0x60, 0x7F
	.byte 0xF7, 0x9F, 0x26, 0x01, 0x5C, 0xBC, 0xF5, 0x72, 0x44, 0xC5, 0x3B, 0x66, 0x5B, 0x34, 0x7E, 0xFB
	.byte 0x8B, 0x76, 0x29, 0x43, 0xCB, 0xDC, 0xC6, 0x23, 0xB6, 0x68, 0xFC, 0xED, 0xB8, 0x63, 0xF1, 0xE4
	.byte 0xD7, 0xCA, 0xDC, 0x31, 0x42, 0x10, 0x85, 0x63, 0x13, 0x40, 0x22, 0x97, 0x84, 0x20, 0x11, 0xC6
	.byte 0x85, 0x7D, 0x24, 0x4A, 0xD2, 0xF8, 0x3D, 0xBB, 0xAE, 0x11, 0x32, 0xF9, 0xC7, 0x6D, 0xA1, 0x29
	.byte 0x1D, 0x4B, 0x2F, 0x9E, 0xDC, 0xF3, 0x30, 0xB2, 0x0D, 0xEC, 0x52, 0x86, 0x77, 0xD0, 0xE3, 0xC1
	.byte 0x2B, 0x6C, 0x16, 0xB3, 0xA9, 0x99, 0xB9, 0x70, 0x11, 0xFA, 0x48, 0x94, 0x47, 0x22, 0x64, 0xE9
	.byte 0xA8, 0xC4, 0x8C, 0xFC, 0xA0, 0x1A, 0x3F, 0xF0, 0x56, 0xD8, 0x2C, 0x7D, 0x22, 0xEF, 0x90, 0x33
	.byte 0x87, 0xC7, 0x4E, 0x49, 0xD9, 0xC1, 0xD1, 0x38, 0x8C, 0xFE, 0xA2, 0xCA, 0x98, 0x36, 0x0B, 0xD4
	.byte 0xA6, 0xCF, 0x81, 0xF5, 0xA5, 0x28, 0xDE, 0x7A, 0xDA, 0x26, 0x8E, 0xB7, 0x3F, 0xA4, 0xBF, 0xAD
	.byte 0x2C, 0xE4, 0x9D, 0x3A, 0x50, 0x0D, 0x92, 0x78, 0x6A, 0x9B, 0xCC, 0x5F, 0x54, 0x62, 0x46, 0x7E
	.byte 0xF6, 0xC2, 0x13, 0x8D, 0x90, 0xE8, 0xB8, 0xD8, 0x2E, 0x5E, 0xF7, 0x39, 0x82, 0xF5, 0xAF, 0xC3
	.byte 0x9F, 0xBE, 0x80, 0x5D, 0x69, 0x7C, 0x93, 0xD0, 0x6F, 0xA9, 0x2D, 0xD5, 0xCF, 0xB3, 0x12, 0x25
	.byte 0xC8, 0x3B, 0x99, 0xAC, 0x10, 0xA7, 0x7D, 0x18, 0xE8, 0x6E, 0x63, 0x9C, 0xDB, 0x7B, 0xBB, 0x3B
	.byte 0xCD, 0x09, 0x78, 0x26, 0x6E, 0xF4, 0x18, 0x59, 0xEC, 0x01, 0xB7, 0x9A, 0x83, 0xA8, 0x9A, 0x4F
	.byte 0xE6, 0x65, 0x6E, 0x95, 0xAA, 0x7E, 0xE6, 0xFF, 0x21, 0x08, 0xCF, 0xBC, 0xEF, 0xE6, 0xE8, 0x15
	.byte 0xBA, 0xD9, 0x9B, 0xE7, 0x4A, 0xCE, 0x36, 0x6F, 0xEA, 0xD4, 0x09, 0x9F, 0x29, 0xD6, 0x7C, 0xB0
	.byte 0x31, 0xAF, 0xB2, 0xA4, 0x2A, 0x31, 0x23, 0x3F, 0xC6, 0x30, 0x94, 0xA5, 0x35, 0xC0, 0x66, 0xA2
	.byte 0x74, 0x37, 0xBC, 0x4E, 0xFC, 0xA6, 0xCA, 0x82, 0xE0, 0xB0, 0xD0, 0x90, 0x33, 0x15, 0xD8, 0xA7
	.byte 0xF1, 0x4A, 0x98, 0x04, 0x41, 0xF7, 0xDA, 0xEC, 0x7F, 0x0E, 0x50, 0xCD, 0x17, 0x2F, 0xF6, 0x91
	.byte 0x76, 0x8D, 0xD6, 0x4D, 0x43, 0x4D, 0xB0, 0xEF, 0xCC, 0x54, 0x4D, 0xAA, 0xE4, 0xDF, 0x04, 0x96
	.byte 0x9E, 0xE3, 0xB5, 0xD1, 0x4C, 0x1B, 0x88, 0x6A, 0xC1, 0xB8, 0x1F, 0x2C, 0x46, 0x7F, 0x51, 0x65
	.byte 0x9D, 0x04, 0xEA, 0x5E, 0x01, 0x5D, 0x35, 0x8C, 0xFA, 0x73, 0x74, 0x87, 0xFB, 0x2E, 0x41, 0x0B
	.byte 0xB3, 0x5A, 0x1D, 0x67, 0x92, 0x52, 0xD2, 0xDB, 0xE9, 0x33, 0x56, 0x10, 0x6D, 0x13, 0x47, 0xD6
	.byte 0x9A, 0x8C, 0x61, 0xD7, 0x37, 0x7A, 0x0C, 0xA1, 0x59, 0x8E, 0x14, 0xF8, 0xEB, 0x89, 0x3C, 0x13
	.byte 0xCE, 0xEE, 0x27, 0xA9, 0xB7, 0x35, 0xC9, 0x61, 0xE1, 0xED, 0xE5, 0x1C, 0x7A, 0x3C, 0xB1, 0x47
	.byte 0x9C, 0x59, 0xDF, 0xD2, 0x55, 0x3F, 0x73, 0xF2, 0x18, 0x79, 0xCE, 0x14, 0x73, 0xBF, 0x37, 0xC7
	.byte 0x53, 0xEA, 0xCD, 0xF7, 0x5F, 0x5B, 0xAA, 0xFD, 0xDF, 0x14, 0x6F, 0x3D, 0x78, 0x86, 0xDB, 0x44
	.byte 0xCA, 0x81, 0xF3, 0xAF, 0xB9, 0x3E, 0xC4, 0x68, 0x38, 0x2C, 0x34, 0x24, 0xC2, 0x5F, 0x40, 0xA3
	.byte 0x16, 0x72, 0xC3, 0x1D, 0xBC, 0x0C, 0x25, 0xE2, 0x28, 0x8B, 0x49, 0x3C, 0xFF, 0x41, 0x95, 0x0D
	.byte 0x39, 0x71, 0x01, 0xA8, 0x08, 0xDE, 0xB3, 0x0C, 0xD8, 0x9C, 0xE4, 0xB4, 0x64, 0x90, 0xC1, 0x56
	.byte 0x7B, 0x61, 0x84, 0xCB, 0xD5, 0x70, 0xB6, 0x32, 0x48, 0x74, 0x5C, 0x6C, 0xD0, 0x42, 0x57, 0xB8

	.global MOD13_0223CC6C
MOD13_0223CC6C: ; 0x0223CC6C
	.byte 0x52, 0x52, 0x52, 0x52, 0x09, 0x09, 0x09, 0x09, 0x6A, 0x6A, 0x6A, 0x6A, 0xD5, 0xD5, 0xD5, 0xD5
	.byte 0x30, 0x30, 0x30, 0x30, 0x36, 0x36, 0x36, 0x36, 0xA5, 0xA5, 0xA5, 0xA5, 0x38, 0x38, 0x38, 0x38
	.byte 0xBF, 0xBF, 0xBF, 0xBF, 0x40, 0x40, 0x40, 0x40, 0xA3, 0xA3, 0xA3, 0xA3, 0x9E, 0x9E, 0x9E, 0x9E
	.byte 0x81, 0x81, 0x81, 0x81, 0xF3, 0xF3, 0xF3, 0xF3, 0xD7, 0xD7, 0xD7, 0xD7, 0xFB, 0xFB, 0xFB, 0xFB
	.byte 0x7C, 0x7C, 0x7C, 0x7C, 0xE3, 0xE3, 0xE3, 0xE3, 0x39, 0x39, 0x39, 0x39, 0x82, 0x82, 0x82, 0x82
	.byte 0x9B, 0x9B, 0x9B, 0x9B, 0x2F, 0x2F, 0x2F, 0x2F, 0xFF, 0xFF, 0xFF, 0xFF, 0x87, 0x87, 0x87, 0x87
	.byte 0x34, 0x34, 0x34, 0x34, 0x8E, 0x8E, 0x8E, 0x8E, 0x43, 0x43, 0x43, 0x43, 0x44, 0x44, 0x44, 0x44
	.byte 0xC4, 0xC4, 0xC4, 0xC4, 0xDE, 0xDE, 0xDE, 0xDE, 0xE9, 0xE9, 0xE9, 0xE9, 0xCB, 0xCB, 0xCB, 0xCB
	.byte 0x54, 0x54, 0x54, 0x54, 0x7B, 0x7B, 0x7B, 0x7B, 0x94, 0x94, 0x94, 0x94, 0x32, 0x32, 0x32, 0x32
	.byte 0xA6, 0xA6, 0xA6, 0xA6, 0xC2, 0xC2, 0xC2, 0xC2, 0x23, 0x23, 0x23, 0x23, 0x3D, 0x3D, 0x3D, 0x3D
	.byte 0xEE, 0xEE, 0xEE, 0xEE, 0x4C, 0x4C, 0x4C, 0x4C, 0x95, 0x95, 0x95, 0x95, 0x0B, 0x0B, 0x0B, 0x0B
	.byte 0x42, 0x42, 0x42, 0x42, 0xFA, 0xFA, 0xFA, 0xFA, 0xC3, 0xC3, 0xC3, 0xC3, 0x4E, 0x4E, 0x4E, 0x4E
	.byte 0x08, 0x08, 0x08, 0x08, 0x2E, 0x2E, 0x2E, 0x2E, 0xA1, 0xA1, 0xA1, 0xA1, 0x66, 0x66, 0x66, 0x66
	.byte 0x28, 0x28, 0x28, 0x28, 0xD9, 0xD9, 0xD9, 0xD9, 0x24, 0x24, 0x24, 0x24, 0xB2, 0xB2, 0xB2, 0xB2
	.byte 0x76, 0x76, 0x76, 0x76, 0x5B, 0x5B, 0x5B, 0x5B, 0xA2, 0xA2, 0xA2, 0xA2, 0x49, 0x49, 0x49, 0x49
	.byte 0x6D, 0x6D, 0x6D, 0x6D, 0x8B, 0x8B, 0x8B, 0x8B, 0xD1, 0xD1, 0xD1, 0xD1, 0x25, 0x25, 0x25, 0x25
	.byte 0x72, 0x72, 0x72, 0x72, 0xF8, 0xF8, 0xF8, 0xF8, 0xF6, 0xF6, 0xF6, 0xF6, 0x64, 0x64, 0x64, 0x64
	.byte 0x86, 0x86, 0x86, 0x86, 0x68, 0x68, 0x68, 0x68, 0x98, 0x98, 0x98, 0x98, 0x16, 0x16, 0x16, 0x16
	.byte 0xD4, 0xD4, 0xD4, 0xD4, 0xA4, 0xA4, 0xA4, 0xA4, 0x5C, 0x5C, 0x5C, 0x5C, 0xCC, 0xCC, 0xCC, 0xCC
	.byte 0x5D, 0x5D, 0x5D, 0x5D, 0x65, 0x65, 0x65, 0x65, 0xB6, 0xB6, 0xB6, 0xB6, 0x92, 0x92, 0x92, 0x92
	.byte 0x6C, 0x6C, 0x6C, 0x6C, 0x70, 0x70, 0x70, 0x70, 0x48, 0x48, 0x48, 0x48, 0x50, 0x50, 0x50, 0x50
	.byte 0xFD, 0xFD, 0xFD, 0xFD, 0xED, 0xED, 0xED, 0xED, 0xB9, 0xB9, 0xB9, 0xB9, 0xDA, 0xDA, 0xDA, 0xDA
	.byte 0x5E, 0x5E, 0x5E, 0x5E, 0x15, 0x15, 0x15, 0x15, 0x46, 0x46, 0x46, 0x46, 0x57, 0x57, 0x57, 0x57
	.byte 0xA7, 0xA7, 0xA7, 0xA7, 0x8D, 0x8D, 0x8D, 0x8D, 0x9D, 0x9D, 0x9D, 0x9D, 0x84, 0x84, 0x84, 0x84
	.byte 0x90, 0x90, 0x90, 0x90, 0xD8, 0xD8, 0xD8, 0xD8, 0xAB, 0xAB, 0xAB, 0xAB, 0x00, 0x00, 0x00, 0x00
	.byte 0x8C, 0x8C, 0x8C, 0x8C, 0xBC, 0xBC, 0xBC, 0xBC, 0xD3, 0xD3, 0xD3, 0xD3, 0x0A, 0x0A, 0x0A, 0x0A
	.byte 0xF7, 0xF7, 0xF7, 0xF7, 0xE4, 0xE4, 0xE4, 0xE4, 0x58, 0x58, 0x58, 0x58, 0x05, 0x05, 0x05, 0x05
	.byte 0xB8, 0xB8, 0xB8, 0xB8, 0xB3, 0xB3, 0xB3, 0xB3, 0x45, 0x45, 0x45, 0x45, 0x06, 0x06, 0x06, 0x06
	.byte 0xD0, 0xD0, 0xD0, 0xD0, 0x2C, 0x2C, 0x2C, 0x2C, 0x1E, 0x1E, 0x1E, 0x1E, 0x8F, 0x8F, 0x8F, 0x8F
	.byte 0xCA, 0xCA, 0xCA, 0xCA, 0x3F, 0x3F, 0x3F, 0x3F, 0x0F, 0x0F, 0x0F, 0x0F, 0x02, 0x02, 0x02, 0x02
	.byte 0xC1, 0xC1, 0xC1, 0xC1, 0xAF, 0xAF, 0xAF, 0xAF, 0xBD, 0xBD, 0xBD, 0xBD, 0x03, 0x03, 0x03, 0x03
	.byte 0x01, 0x01, 0x01, 0x01, 0x13, 0x13, 0x13, 0x13, 0x8A, 0x8A, 0x8A, 0x8A, 0x6B, 0x6B, 0x6B, 0x6B
	.byte 0x3A, 0x3A, 0x3A, 0x3A, 0x91, 0x91, 0x91, 0x91, 0x11, 0x11, 0x11, 0x11, 0x41, 0x41, 0x41, 0x41
	.byte 0x4F, 0x4F, 0x4F, 0x4F, 0x67, 0x67, 0x67, 0x67, 0xDC, 0xDC, 0xDC, 0xDC, 0xEA, 0xEA, 0xEA, 0xEA
	.byte 0x97, 0x97, 0x97, 0x97, 0xF2, 0xF2, 0xF2, 0xF2, 0xCF, 0xCF, 0xCF, 0xCF, 0xCE, 0xCE, 0xCE, 0xCE
	.byte 0xF0, 0xF0, 0xF0, 0xF0, 0xB4, 0xB4, 0xB4, 0xB4, 0xE6, 0xE6, 0xE6, 0xE6, 0x73, 0x73, 0x73, 0x73
	.byte 0x96, 0x96, 0x96, 0x96, 0xAC, 0xAC, 0xAC, 0xAC, 0x74, 0x74, 0x74, 0x74, 0x22, 0x22, 0x22, 0x22
	.byte 0xE7, 0xE7, 0xE7, 0xE7, 0xAD, 0xAD, 0xAD, 0xAD, 0x35, 0x35, 0x35, 0x35, 0x85, 0x85, 0x85, 0x85
	.byte 0xE2, 0xE2, 0xE2, 0xE2, 0xF9, 0xF9, 0xF9, 0xF9, 0x37, 0x37, 0x37, 0x37, 0xE8, 0xE8, 0xE8, 0xE8
	.byte 0x1C, 0x1C, 0x1C, 0x1C, 0x75, 0x75, 0x75, 0x75, 0xDF, 0xDF, 0xDF, 0xDF, 0x6E, 0x6E, 0x6E, 0x6E
	.byte 0x47, 0x47, 0x47, 0x47, 0xF1, 0xF1, 0xF1, 0xF1, 0x1A, 0x1A, 0x1A, 0x1A, 0x71, 0x71, 0x71, 0x71
	.byte 0x1D, 0x1D, 0x1D, 0x1D, 0x29, 0x29, 0x29, 0x29, 0xC5, 0xC5, 0xC5, 0xC5, 0x89, 0x89, 0x89, 0x89
	.byte 0x6F, 0x6F, 0x6F, 0x6F, 0xB7, 0xB7, 0xB7, 0xB7, 0x62, 0x62, 0x62, 0x62, 0x0E, 0x0E, 0x0E, 0x0E
	.byte 0xAA, 0xAA, 0xAA, 0xAA, 0x18, 0x18, 0x18, 0x18, 0xBE, 0xBE, 0xBE, 0xBE, 0x1B, 0x1B, 0x1B, 0x1B
	.byte 0xFC, 0xFC, 0xFC, 0xFC, 0x56, 0x56, 0x56, 0x56, 0x3E, 0x3E, 0x3E, 0x3E, 0x4B, 0x4B, 0x4B, 0x4B
	.byte 0xC6, 0xC6, 0xC6, 0xC6, 0xD2, 0xD2, 0xD2, 0xD2, 0x79, 0x79, 0x79, 0x79, 0x20, 0x20, 0x20, 0x20
	.byte 0x9A, 0x9A, 0x9A, 0x9A, 0xDB, 0xDB, 0xDB, 0xDB, 0xC0, 0xC0, 0xC0, 0xC0, 0xFE, 0xFE, 0xFE, 0xFE
	.byte 0x78, 0x78, 0x78, 0x78, 0xCD, 0xCD, 0xCD, 0xCD, 0x5A, 0x5A, 0x5A, 0x5A, 0xF4, 0xF4, 0xF4, 0xF4
	.byte 0x1F, 0x1F, 0x1F, 0x1F, 0xDD, 0xDD, 0xDD, 0xDD, 0xA8, 0xA8, 0xA8, 0xA8, 0x33, 0x33, 0x33, 0x33
	.byte 0x88, 0x88, 0x88, 0x88, 0x07, 0x07, 0x07, 0x07, 0xC7, 0xC7, 0xC7, 0xC7, 0x31, 0x31, 0x31, 0x31
	.byte 0xB1, 0xB1, 0xB1, 0xB1, 0x12, 0x12, 0x12, 0x12, 0x10, 0x10, 0x10, 0x10, 0x59, 0x59, 0x59, 0x59
	.byte 0x27, 0x27, 0x27, 0x27, 0x80, 0x80, 0x80, 0x80, 0xEC, 0xEC, 0xEC, 0xEC, 0x5F, 0x5F, 0x5F, 0x5F
	.byte 0x60, 0x60, 0x60, 0x60, 0x51, 0x51, 0x51, 0x51, 0x7F, 0x7F, 0x7F, 0x7F, 0xA9, 0xA9, 0xA9, 0xA9
	.byte 0x19, 0x19, 0x19, 0x19, 0xB5, 0xB5, 0xB5, 0xB5, 0x4A, 0x4A, 0x4A, 0x4A, 0x0D, 0x0D, 0x0D, 0x0D
	.byte 0x2D, 0x2D, 0x2D, 0x2D, 0xE5, 0xE5, 0xE5, 0xE5, 0x7A, 0x7A, 0x7A, 0x7A, 0x9F, 0x9F, 0x9F, 0x9F
	.byte 0x93, 0x93, 0x93, 0x93, 0xC9, 0xC9, 0xC9, 0xC9, 0x9C, 0x9C, 0x9C, 0x9C, 0xEF, 0xEF, 0xEF, 0xEF
	.byte 0xA0, 0xA0, 0xA0, 0xA0, 0xE0, 0xE0, 0xE0, 0xE0, 0x3B, 0x3B, 0x3B, 0x3B, 0x4D, 0x4D, 0x4D, 0x4D
	.byte 0xAE, 0xAE, 0xAE, 0xAE, 0x2A, 0x2A, 0x2A, 0x2A, 0xF5, 0xF5, 0xF5, 0xF5, 0xB0, 0xB0, 0xB0, 0xB0
	.byte 0xC8, 0xC8, 0xC8, 0xC8, 0xEB, 0xEB, 0xEB, 0xEB, 0xBB, 0xBB, 0xBB, 0xBB, 0x3C, 0x3C, 0x3C, 0x3C
	.byte 0x83, 0x83, 0x83, 0x83, 0x53, 0x53, 0x53, 0x53, 0x99, 0x99, 0x99, 0x99, 0x61, 0x61, 0x61, 0x61
	.byte 0x17, 0x17, 0x17, 0x17, 0x2B, 0x2B, 0x2B, 0x2B, 0x04, 0x04, 0x04, 0x04, 0x7E, 0x7E, 0x7E, 0x7E
	.byte 0xBA, 0xBA, 0xBA, 0xBA, 0x77, 0x77, 0x77, 0x77, 0xD6, 0xD6, 0xD6, 0xD6, 0x26, 0x26, 0x26, 0x26
	.byte 0xE1, 0xE1, 0xE1, 0xE1, 0x69, 0x69, 0x69, 0x69, 0x14, 0x14, 0x14, 0x14, 0x63, 0x63, 0x63, 0x63
	.byte 0x55, 0x55, 0x55, 0x55, 0x21, 0x21, 0x21, 0x21, 0x0C, 0x0C, 0x0C, 0x0C, 0x7D, 0x7D, 0x7D, 0x7D

	.global MOD13_0223D06C
MOD13_0223D06C: ; 0x0223D06C
	.byte 0xA5, 0x63, 0x63, 0xC6, 0x84, 0x7C, 0x7C, 0xF8, 0x99, 0x77, 0x77, 0xEE, 0x8D, 0x7B, 0x7B, 0xF6
	.byte 0x0D, 0xF2, 0xF2, 0xFF, 0xBD, 0x6B, 0x6B, 0xD6, 0xB1, 0x6F, 0x6F, 0xDE, 0x54, 0xC5, 0xC5, 0x91
	.byte 0x50, 0x30, 0x30, 0x60, 0x03, 0x01, 0x01, 0x02, 0xA9, 0x67, 0x67, 0xCE, 0x7D, 0x2B, 0x2B, 0x56
	.byte 0x19, 0xFE, 0xFE, 0xE7, 0x62, 0xD7, 0xD7, 0xB5, 0xE6, 0xAB, 0xAB, 0x4D, 0x9A, 0x76, 0x76, 0xEC
	.byte 0x45, 0xCA, 0xCA, 0x8F, 0x9D, 0x82, 0x82, 0x1F, 0x40, 0xC9, 0xC9, 0x89, 0x87, 0x7D, 0x7D, 0xFA
	.byte 0x15, 0xFA, 0xFA, 0xEF, 0xEB, 0x59, 0x59, 0xB2, 0xC9, 0x47, 0x47, 0x8E, 0x0B, 0xF0, 0xF0, 0xFB
	.byte 0xEC, 0xAD, 0xAD, 0x41, 0x67, 0xD4, 0xD4, 0xB3, 0xFD, 0xA2, 0xA2, 0x5F, 0xEA, 0xAF, 0xAF, 0x45
	.byte 0xBF, 0x9C, 0x9C, 0x23, 0xF7, 0xA4, 0xA4, 0x53, 0x96, 0x72, 0x72, 0xE4, 0x5B, 0xC0, 0xC0, 0x9B
	.byte 0xC2, 0xB7, 0xB7, 0x75, 0x1C, 0xFD, 0xFD, 0xE1, 0xAE, 0x93, 0x93, 0x3D, 0x6A, 0x26, 0x26, 0x4C
	.byte 0x5A, 0x36, 0x36, 0x6C, 0x41, 0x3F, 0x3F, 0x7E, 0x02, 0xF7, 0xF7, 0xF5, 0x4F, 0xCC, 0xCC, 0x83
	.byte 0x5C, 0x34, 0x34, 0x68, 0xF4, 0xA5, 0xA5, 0x51, 0x34, 0xE5, 0xE5, 0xD1, 0x08, 0xF1, 0xF1, 0xF9
	.byte 0x93, 0x71, 0x71, 0xE2, 0x73, 0xD8, 0xD8, 0xAB, 0x53, 0x31, 0x31, 0x62, 0x3F, 0x15, 0x15, 0x2A
	.byte 0x0C, 0x04, 0x04, 0x08, 0x52, 0xC7, 0xC7, 0x95, 0x65, 0x23, 0x23, 0x46, 0x5E, 0xC3, 0xC3, 0x9D
	.byte 0x28, 0x18, 0x18, 0x30, 0xA1, 0x96, 0x96, 0x37, 0x0F, 0x05, 0x05, 0x0A, 0xB5, 0x9A, 0x9A, 0x2F
	.byte 0x09, 0x07, 0x07, 0x0E, 0x36, 0x12, 0x12, 0x24, 0x9B, 0x80, 0x80, 0x1B, 0x3D, 0xE2, 0xE2, 0xDF
	.byte 0x26, 0xEB, 0xEB, 0xCD, 0x69, 0x27, 0x27, 0x4E, 0xCD, 0xB2, 0xB2, 0x7F, 0x9F, 0x75, 0x75, 0xEA
	.byte 0x1B, 0x09, 0x09, 0x12, 0x9E, 0x83, 0x83, 0x1D, 0x74, 0x2C, 0x2C, 0x58, 0x2E, 0x1A, 0x1A, 0x34
	.byte 0x2D, 0x1B, 0x1B, 0x36, 0xB2, 0x6E, 0x6E, 0xDC, 0xEE, 0x5A, 0x5A, 0xB4, 0xFB, 0xA0, 0xA0, 0x5B
	.byte 0xF6, 0x52, 0x52, 0xA4, 0x4D, 0x3B, 0x3B, 0x76, 0x61, 0xD6, 0xD6, 0xB7, 0xCE, 0xB3, 0xB3, 0x7D
	.byte 0x7B, 0x29, 0x29, 0x52, 0x3E, 0xE3, 0xE3, 0xDD, 0x71, 0x2F, 0x2F, 0x5E, 0x97, 0x84, 0x84, 0x13
	.byte 0xF5, 0x53, 0x53, 0xA6, 0x68, 0xD1, 0xD1, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x2C, 0xED, 0xED, 0xC1
	.byte 0x60, 0x20, 0x20, 0x40, 0x1F, 0xFC, 0xFC, 0xE3, 0xC8, 0xB1, 0xB1, 0x79, 0xED, 0x5B, 0x5B, 0xB6
	.byte 0xBE, 0x6A, 0x6A, 0xD4, 0x46, 0xCB, 0xCB, 0x8D, 0xD9, 0xBE, 0xBE, 0x67, 0x4B, 0x39, 0x39, 0x72
	.byte 0xDE, 0x4A, 0x4A, 0x94, 0xD4, 0x4C, 0x4C, 0x98, 0xE8, 0x58, 0x58, 0xB0, 0x4A, 0xCF, 0xCF, 0x85
	.byte 0x6B, 0xD0, 0xD0, 0xBB, 0x2A, 0xEF, 0xEF, 0xC5, 0xE5, 0xAA, 0xAA, 0x4F, 0x16, 0xFB, 0xFB, 0xED
	.byte 0xC5, 0x43, 0x43, 0x86, 0xD7, 0x4D, 0x4D, 0x9A, 0x55, 0x33, 0x33, 0x66, 0x94, 0x85, 0x85, 0x11
	.byte 0xCF, 0x45, 0x45, 0x8A, 0x10, 0xF9, 0xF9, 0xE9, 0x06, 0x02, 0x02, 0x04, 0x81, 0x7F, 0x7F, 0xFE
	.byte 0xF0, 0x50, 0x50, 0xA0, 0x44, 0x3C, 0x3C, 0x78, 0xBA, 0x9F, 0x9F, 0x25, 0xE3, 0xA8, 0xA8, 0x4B
	.byte 0xF3, 0x51, 0x51, 0xA2, 0xFE, 0xA3, 0xA3, 0x5D, 0xC0, 0x40, 0x40, 0x80, 0x8A, 0x8F, 0x8F, 0x05
	.byte 0xAD, 0x92, 0x92, 0x3F, 0xBC, 0x9D, 0x9D, 0x21, 0x48, 0x38, 0x38, 0x70, 0x04, 0xF5, 0xF5, 0xF1
	.byte 0xDF, 0xBC, 0xBC, 0x63, 0xC1, 0xB6, 0xB6, 0x77, 0x75, 0xDA, 0xDA, 0xAF, 0x63, 0x21, 0x21, 0x42
	.byte 0x30, 0x10, 0x10, 0x20, 0x1A, 0xFF, 0xFF, 0xE5, 0x0E, 0xF3, 0xF3, 0xFD, 0x6D, 0xD2, 0xD2, 0xBF
	.byte 0x4C, 0xCD, 0xCD, 0x81, 0x14, 0x0C, 0x0C, 0x18, 0x35, 0x13, 0x13, 0x26, 0x2F, 0xEC, 0xEC, 0xC3
	.byte 0xE1, 0x5F, 0x5F, 0xBE, 0xA2, 0x97, 0x97, 0x35, 0xCC, 0x44, 0x44, 0x88, 0x39, 0x17, 0x17, 0x2E
	.byte 0x57, 0xC4, 0xC4, 0x93, 0xF2, 0xA7, 0xA7, 0x55, 0x82, 0x7E, 0x7E, 0xFC, 0x47, 0x3D, 0x3D, 0x7A
	.byte 0xAC, 0x64, 0x64, 0xC8, 0xE7, 0x5D, 0x5D, 0xBA, 0x2B, 0x19, 0x19, 0x32, 0x95, 0x73, 0x73, 0xE6
	.byte 0xA0, 0x60, 0x60, 0xC0, 0x98, 0x81, 0x81, 0x19, 0xD1, 0x4F, 0x4F, 0x9E, 0x7F, 0xDC, 0xDC, 0xA3
	.byte 0x66, 0x22, 0x22, 0x44, 0x7E, 0x2A, 0x2A, 0x54, 0xAB, 0x90, 0x90, 0x3B, 0x83, 0x88, 0x88, 0x0B
	.byte 0xCA, 0x46, 0x46, 0x8C, 0x29, 0xEE, 0xEE, 0xC7, 0xD3, 0xB8, 0xB8, 0x6B, 0x3C, 0x14, 0x14, 0x28
	.byte 0x79, 0xDE, 0xDE, 0xA7, 0xE2, 0x5E, 0x5E, 0xBC, 0x1D, 0x0B, 0x0B, 0x16, 0x76, 0xDB, 0xDB, 0xAD
	.byte 0x3B, 0xE0, 0xE0, 0xDB, 0x56, 0x32, 0x32, 0x64, 0x4E, 0x3A, 0x3A, 0x74, 0x1E, 0x0A, 0x0A, 0x14
	.byte 0xDB, 0x49, 0x49, 0x92, 0x0A, 0x06, 0x06, 0x0C, 0x6C, 0x24, 0x24, 0x48, 0xE4, 0x5C, 0x5C, 0xB8
	.byte 0x5D, 0xC2, 0xC2, 0x9F, 0x6E, 0xD3, 0xD3, 0xBD, 0xEF, 0xAC, 0xAC, 0x43, 0xA6, 0x62, 0x62, 0xC4
	.byte 0xA8, 0x91, 0x91, 0x39, 0xA4, 0x95, 0x95, 0x31, 0x37, 0xE4, 0xE4, 0xD3, 0x8B, 0x79, 0x79, 0xF2
	.byte 0x32, 0xE7, 0xE7, 0xD5, 0x43, 0xC8, 0xC8, 0x8B, 0x59, 0x37, 0x37, 0x6E, 0xB7, 0x6D, 0x6D, 0xDA
	.byte 0x8C, 0x8D, 0x8D, 0x01, 0x64, 0xD5, 0xD5, 0xB1, 0xD2, 0x4E, 0x4E, 0x9C, 0xE0, 0xA9, 0xA9, 0x49
	.byte 0xB4, 0x6C, 0x6C, 0xD8, 0xFA, 0x56, 0x56, 0xAC, 0x07, 0xF4, 0xF4, 0xF3, 0x25, 0xEA, 0xEA, 0xCF
	.byte 0xAF, 0x65, 0x65, 0xCA, 0x8E, 0x7A, 0x7A, 0xF4, 0xE9, 0xAE, 0xAE, 0x47, 0x18, 0x08, 0x08, 0x10
	.byte 0xD5, 0xBA, 0xBA, 0x6F, 0x88, 0x78, 0x78, 0xF0, 0x6F, 0x25, 0x25, 0x4A, 0x72, 0x2E, 0x2E, 0x5C
	.byte 0x24, 0x1C, 0x1C, 0x38, 0xF1, 0xA6, 0xA6, 0x57, 0xC7, 0xB4, 0xB4, 0x73, 0x51, 0xC6, 0xC6, 0x97
	.byte 0x23, 0xE8, 0xE8, 0xCB, 0x7C, 0xDD, 0xDD, 0xA1, 0x9C, 0x74, 0x74, 0xE8, 0x21, 0x1F, 0x1F, 0x3E
	.byte 0xDD, 0x4B, 0x4B, 0x96, 0xDC, 0xBD, 0xBD, 0x61, 0x86, 0x8B, 0x8B, 0x0D, 0x85, 0x8A, 0x8A, 0x0F
	.byte 0x90, 0x70, 0x70, 0xE0, 0x42, 0x3E, 0x3E, 0x7C, 0xC4, 0xB5, 0xB5, 0x71, 0xAA, 0x66, 0x66, 0xCC
	.byte 0xD8, 0x48, 0x48, 0x90, 0x05, 0x03, 0x03, 0x06, 0x01, 0xF6, 0xF6, 0xF7, 0x12, 0x0E, 0x0E, 0x1C
	.byte 0xA3, 0x61, 0x61, 0xC2, 0x5F, 0x35, 0x35, 0x6A, 0xF9, 0x57, 0x57, 0xAE, 0xD0, 0xB9, 0xB9, 0x69
	.byte 0x91, 0x86, 0x86, 0x17, 0x58, 0xC1, 0xC1, 0x99, 0x27, 0x1D, 0x1D, 0x3A, 0xB9, 0x9E, 0x9E, 0x27
	.byte 0x38, 0xE1, 0xE1, 0xD9, 0x13, 0xF8, 0xF8, 0xEB, 0xB3, 0x98, 0x98, 0x2B, 0x33, 0x11, 0x11, 0x22
	.byte 0xBB, 0x69, 0x69, 0xD2, 0x70, 0xD9, 0xD9, 0xA9, 0x89, 0x8E, 0x8E, 0x07, 0xA7, 0x94, 0x94, 0x33
	.byte 0xB6, 0x9B, 0x9B, 0x2D, 0x22, 0x1E, 0x1E, 0x3C, 0x92, 0x87, 0x87, 0x15, 0x20, 0xE9, 0xE9, 0xC9
	.byte 0x49, 0xCE, 0xCE, 0x87, 0xFF, 0x55, 0x55, 0xAA, 0x78, 0x28, 0x28, 0x50, 0x7A, 0xDF, 0xDF, 0xA5
	.byte 0x8F, 0x8C, 0x8C, 0x03, 0xF8, 0xA1, 0xA1, 0x59, 0x80, 0x89, 0x89, 0x09, 0x17, 0x0D, 0x0D, 0x1A
	.byte 0xDA, 0xBF, 0xBF, 0x65, 0x31, 0xE6, 0xE6, 0xD7, 0xC6, 0x42, 0x42, 0x84, 0xB8, 0x68, 0x68, 0xD0
	.byte 0xC3, 0x41, 0x41, 0x82, 0xB0, 0x99, 0x99, 0x29, 0x77, 0x2D, 0x2D, 0x5A, 0x11, 0x0F, 0x0F, 0x1E
	.byte 0xCB, 0xB0, 0xB0, 0x7B, 0xFC, 0x54, 0x54, 0xA8, 0xD6, 0xBB, 0xBB, 0x6D, 0x3A, 0x16, 0x16, 0x2C

	.global MOD13_0223D46C
MOD13_0223D46C: ; 0x0223D46C
	.byte 0x63, 0x63, 0xC6, 0xA5, 0x7C, 0x7C, 0xF8, 0x84, 0x77, 0x77, 0xEE, 0x99, 0x7B, 0x7B, 0xF6, 0x8D
	.byte 0xF2, 0xF2, 0xFF, 0x0D, 0x6B, 0x6B, 0xD6, 0xBD, 0x6F, 0x6F, 0xDE, 0xB1, 0xC5, 0xC5, 0x91, 0x54
	.byte 0x30, 0x30, 0x60, 0x50, 0x01, 0x01, 0x02, 0x03, 0x67, 0x67, 0xCE, 0xA9, 0x2B, 0x2B, 0x56, 0x7D
	.byte 0xFE, 0xFE, 0xE7, 0x19, 0xD7, 0xD7, 0xB5, 0x62, 0xAB, 0xAB, 0x4D, 0xE6, 0x76, 0x76, 0xEC, 0x9A
	.byte 0xCA, 0xCA, 0x8F, 0x45, 0x82, 0x82, 0x1F, 0x9D, 0xC9, 0xC9, 0x89, 0x40, 0x7D, 0x7D, 0xFA, 0x87
	.byte 0xFA, 0xFA, 0xEF, 0x15, 0x59, 0x59, 0xB2, 0xEB, 0x47, 0x47, 0x8E, 0xC9, 0xF0, 0xF0, 0xFB, 0x0B
	.byte 0xAD, 0xAD, 0x41, 0xEC, 0xD4, 0xD4, 0xB3, 0x67, 0xA2, 0xA2, 0x5F, 0xFD, 0xAF, 0xAF, 0x45, 0xEA
	.byte 0x9C, 0x9C, 0x23, 0xBF, 0xA4, 0xA4, 0x53, 0xF7, 0x72, 0x72, 0xE4, 0x96, 0xC0, 0xC0, 0x9B, 0x5B
	.byte 0xB7, 0xB7, 0x75, 0xC2, 0xFD, 0xFD, 0xE1, 0x1C, 0x93, 0x93, 0x3D, 0xAE, 0x26, 0x26, 0x4C, 0x6A
	.byte 0x36, 0x36, 0x6C, 0x5A, 0x3F, 0x3F, 0x7E, 0x41, 0xF7, 0xF7, 0xF5, 0x02, 0xCC, 0xCC, 0x83, 0x4F
	.byte 0x34, 0x34, 0x68, 0x5C, 0xA5, 0xA5, 0x51, 0xF4, 0xE5, 0xE5, 0xD1, 0x34, 0xF1, 0xF1, 0xF9, 0x08
	.byte 0x71, 0x71, 0xE2, 0x93, 0xD8, 0xD8, 0xAB, 0x73, 0x31, 0x31, 0x62, 0x53, 0x15, 0x15, 0x2A, 0x3F
	.byte 0x04, 0x04, 0x08, 0x0C, 0xC7, 0xC7, 0x95, 0x52, 0x23, 0x23, 0x46, 0x65, 0xC3, 0xC3, 0x9D, 0x5E
	.byte 0x18, 0x18, 0x30, 0x28, 0x96, 0x96, 0x37, 0xA1, 0x05, 0x05, 0x0A, 0x0F, 0x9A, 0x9A, 0x2F, 0xB5
	.byte 0x07, 0x07, 0x0E, 0x09, 0x12, 0x12, 0x24, 0x36, 0x80, 0x80, 0x1B, 0x9B, 0xE2, 0xE2, 0xDF, 0x3D
	.byte 0xEB, 0xEB, 0xCD, 0x26, 0x27, 0x27, 0x4E, 0x69, 0xB2, 0xB2, 0x7F, 0xCD, 0x75, 0x75, 0xEA, 0x9F
	.byte 0x09, 0x09, 0x12, 0x1B, 0x83, 0x83, 0x1D, 0x9E, 0x2C, 0x2C, 0x58, 0x74, 0x1A, 0x1A, 0x34, 0x2E
	.byte 0x1B, 0x1B, 0x36, 0x2D, 0x6E, 0x6E, 0xDC, 0xB2, 0x5A, 0x5A, 0xB4, 0xEE, 0xA0, 0xA0, 0x5B, 0xFB
	.byte 0x52, 0x52, 0xA4, 0xF6, 0x3B, 0x3B, 0x76, 0x4D, 0xD6, 0xD6, 0xB7, 0x61, 0xB3, 0xB3, 0x7D, 0xCE
	.byte 0x29, 0x29, 0x52, 0x7B, 0xE3, 0xE3, 0xDD, 0x3E, 0x2F, 0x2F, 0x5E, 0x71, 0x84, 0x84, 0x13, 0x97
	.byte 0x53, 0x53, 0xA6, 0xF5, 0xD1, 0xD1, 0xB9, 0x68, 0x00, 0x00, 0x00, 0x00, 0xED, 0xED, 0xC1, 0x2C
	.byte 0x20, 0x20, 0x40, 0x60, 0xFC, 0xFC, 0xE3, 0x1F, 0xB1, 0xB1, 0x79, 0xC8, 0x5B, 0x5B, 0xB6, 0xED
	.byte 0x6A, 0x6A, 0xD4, 0xBE, 0xCB, 0xCB, 0x8D, 0x46, 0xBE, 0xBE, 0x67, 0xD9, 0x39, 0x39, 0x72, 0x4B
	.byte 0x4A, 0x4A, 0x94, 0xDE, 0x4C, 0x4C, 0x98, 0xD4, 0x58, 0x58, 0xB0, 0xE8, 0xCF, 0xCF, 0x85, 0x4A
	.byte 0xD0, 0xD0, 0xBB, 0x6B, 0xEF, 0xEF, 0xC5, 0x2A, 0xAA, 0xAA, 0x4F, 0xE5, 0xFB, 0xFB, 0xED, 0x16
	.byte 0x43, 0x43, 0x86, 0xC5, 0x4D, 0x4D, 0x9A, 0xD7, 0x33, 0x33, 0x66, 0x55, 0x85, 0x85, 0x11, 0x94
	.byte 0x45, 0x45, 0x8A, 0xCF, 0xF9, 0xF9, 0xE9, 0x10, 0x02, 0x02, 0x04, 0x06, 0x7F, 0x7F, 0xFE, 0x81
	.byte 0x50, 0x50, 0xA0, 0xF0, 0x3C, 0x3C, 0x78, 0x44, 0x9F, 0x9F, 0x25, 0xBA, 0xA8, 0xA8, 0x4B, 0xE3
	.byte 0x51, 0x51, 0xA2, 0xF3, 0xA3, 0xA3, 0x5D, 0xFE, 0x40, 0x40, 0x80, 0xC0, 0x8F, 0x8F, 0x05, 0x8A
	.byte 0x92, 0x92, 0x3F, 0xAD, 0x9D, 0x9D, 0x21, 0xBC, 0x38, 0x38, 0x70, 0x48, 0xF5, 0xF5, 0xF1, 0x04
	.byte 0xBC, 0xBC, 0x63, 0xDF, 0xB6, 0xB6, 0x77, 0xC1, 0xDA, 0xDA, 0xAF, 0x75, 0x21, 0x21, 0x42, 0x63
	.byte 0x10, 0x10, 0x20, 0x30, 0xFF, 0xFF, 0xE5, 0x1A, 0xF3, 0xF3, 0xFD, 0x0E, 0xD2, 0xD2, 0xBF, 0x6D
	.byte 0xCD, 0xCD, 0x81, 0x4C, 0x0C, 0x0C, 0x18, 0x14, 0x13, 0x13, 0x26, 0x35, 0xEC, 0xEC, 0xC3, 0x2F
	.byte 0x5F, 0x5F, 0xBE, 0xE1, 0x97, 0x97, 0x35, 0xA2, 0x44, 0x44, 0x88, 0xCC, 0x17, 0x17, 0x2E, 0x39
	.byte 0xC4, 0xC4, 0x93, 0x57, 0xA7, 0xA7, 0x55, 0xF2, 0x7E, 0x7E, 0xFC, 0x82, 0x3D, 0x3D, 0x7A, 0x47
	.byte 0x64, 0x64, 0xC8, 0xAC, 0x5D, 0x5D, 0xBA, 0xE7, 0x19, 0x19, 0x32, 0x2B, 0x73, 0x73, 0xE6, 0x95
	.byte 0x60, 0x60, 0xC0, 0xA0, 0x81, 0x81, 0x19, 0x98, 0x4F, 0x4F, 0x9E, 0xD1, 0xDC, 0xDC, 0xA3, 0x7F
	.byte 0x22, 0x22, 0x44, 0x66, 0x2A, 0x2A, 0x54, 0x7E, 0x90, 0x90, 0x3B, 0xAB, 0x88, 0x88, 0x0B, 0x83
	.byte 0x46, 0x46, 0x8C, 0xCA, 0xEE, 0xEE, 0xC7, 0x29, 0xB8, 0xB8, 0x6B, 0xD3, 0x14, 0x14, 0x28, 0x3C
	.byte 0xDE, 0xDE, 0xA7, 0x79, 0x5E, 0x5E, 0xBC, 0xE2, 0x0B, 0x0B, 0x16, 0x1D, 0xDB, 0xDB, 0xAD, 0x76
	.byte 0xE0, 0xE0, 0xDB, 0x3B, 0x32, 0x32, 0x64, 0x56, 0x3A, 0x3A, 0x74, 0x4E, 0x0A, 0x0A, 0x14, 0x1E
	.byte 0x49, 0x49, 0x92, 0xDB, 0x06, 0x06, 0x0C, 0x0A, 0x24, 0x24, 0x48, 0x6C, 0x5C, 0x5C, 0xB8, 0xE4
	.byte 0xC2, 0xC2, 0x9F, 0x5D, 0xD3, 0xD3, 0xBD, 0x6E, 0xAC, 0xAC, 0x43, 0xEF, 0x62, 0x62, 0xC4, 0xA6
	.byte 0x91, 0x91, 0x39, 0xA8, 0x95, 0x95, 0x31, 0xA4, 0xE4, 0xE4, 0xD3, 0x37, 0x79, 0x79, 0xF2, 0x8B
	.byte 0xE7, 0xE7, 0xD5, 0x32, 0xC8, 0xC8, 0x8B, 0x43, 0x37, 0x37, 0x6E, 0x59, 0x6D, 0x6D, 0xDA, 0xB7
	.byte 0x8D, 0x8D, 0x01, 0x8C, 0xD5, 0xD5, 0xB1, 0x64, 0x4E, 0x4E, 0x9C, 0xD2, 0xA9, 0xA9, 0x49, 0xE0
	.byte 0x6C, 0x6C, 0xD8, 0xB4, 0x56, 0x56, 0xAC, 0xFA, 0xF4, 0xF4, 0xF3, 0x07, 0xEA, 0xEA, 0xCF, 0x25
	.byte 0x65, 0x65, 0xCA, 0xAF, 0x7A, 0x7A, 0xF4, 0x8E, 0xAE, 0xAE, 0x47, 0xE9, 0x08, 0x08, 0x10, 0x18
	.byte 0xBA, 0xBA, 0x6F, 0xD5, 0x78, 0x78, 0xF0, 0x88, 0x25, 0x25, 0x4A, 0x6F, 0x2E, 0x2E, 0x5C, 0x72
	.byte 0x1C, 0x1C, 0x38, 0x24, 0xA6, 0xA6, 0x57, 0xF1, 0xB4, 0xB4, 0x73, 0xC7, 0xC6, 0xC6, 0x97, 0x51
	.byte 0xE8, 0xE8, 0xCB, 0x23, 0xDD, 0xDD, 0xA1, 0x7C, 0x74, 0x74, 0xE8, 0x9C, 0x1F, 0x1F, 0x3E, 0x21
	.byte 0x4B, 0x4B, 0x96, 0xDD, 0xBD, 0xBD, 0x61, 0xDC, 0x8B, 0x8B, 0x0D, 0x86, 0x8A, 0x8A, 0x0F, 0x85
	.byte 0x70, 0x70, 0xE0, 0x90, 0x3E, 0x3E, 0x7C, 0x42, 0xB5, 0xB5, 0x71, 0xC4, 0x66, 0x66, 0xCC, 0xAA
	.byte 0x48, 0x48, 0x90, 0xD8, 0x03, 0x03, 0x06, 0x05, 0xF6, 0xF6, 0xF7, 0x01, 0x0E, 0x0E, 0x1C, 0x12
	.byte 0x61, 0x61, 0xC2, 0xA3, 0x35, 0x35, 0x6A, 0x5F, 0x57, 0x57, 0xAE, 0xF9, 0xB9, 0xB9, 0x69, 0xD0
	.byte 0x86, 0x86, 0x17, 0x91, 0xC1, 0xC1, 0x99, 0x58, 0x1D, 0x1D, 0x3A, 0x27, 0x9E, 0x9E, 0x27, 0xB9
	.byte 0xE1, 0xE1, 0xD9, 0x38, 0xF8, 0xF8, 0xEB, 0x13, 0x98, 0x98, 0x2B, 0xB3, 0x11, 0x11, 0x22, 0x33
	.byte 0x69, 0x69, 0xD2, 0xBB, 0xD9, 0xD9, 0xA9, 0x70, 0x8E, 0x8E, 0x07, 0x89, 0x94, 0x94, 0x33, 0xA7
	.byte 0x9B, 0x9B, 0x2D, 0xB6, 0x1E, 0x1E, 0x3C, 0x22, 0x87, 0x87, 0x15, 0x92, 0xE9, 0xE9, 0xC9, 0x20
	.byte 0xCE, 0xCE, 0x87, 0x49, 0x55, 0x55, 0xAA, 0xFF, 0x28, 0x28, 0x50, 0x78, 0xDF, 0xDF, 0xA5, 0x7A
	.byte 0x8C, 0x8C, 0x03, 0x8F, 0xA1, 0xA1, 0x59, 0xF8, 0x89, 0x89, 0x09, 0x80, 0x0D, 0x0D, 0x1A, 0x17
	.byte 0xBF, 0xBF, 0x65, 0xDA, 0xE6, 0xE6, 0xD7, 0x31, 0x42, 0x42, 0x84, 0xC6, 0x68, 0x68, 0xD0, 0xB8
	.byte 0x41, 0x41, 0x82, 0xC3, 0x99, 0x99, 0x29, 0xB0, 0x2D, 0x2D, 0x5A, 0x77, 0x0F, 0x0F, 0x1E, 0x11
	.byte 0xB0, 0xB0, 0x7B, 0xCB, 0x54, 0x54, 0xA8, 0xFC, 0xBB, 0xBB, 0x6D, 0xD6, 0x16, 0x16, 0x2C, 0x3A

	.global MOD13_0223D86C
MOD13_0223D86C: ; 0x0223D86C
	.byte 0x63, 0xC6, 0xA5, 0x63, 0x7C, 0xF8, 0x84, 0x7C, 0x77, 0xEE, 0x99, 0x77, 0x7B, 0xF6, 0x8D, 0x7B
	.byte 0xF2, 0xFF, 0x0D, 0xF2, 0x6B, 0xD6, 0xBD, 0x6B, 0x6F, 0xDE, 0xB1, 0x6F, 0xC5, 0x91, 0x54, 0xC5
	.byte 0x30, 0x60, 0x50, 0x30, 0x01, 0x02, 0x03, 0x01, 0x67, 0xCE, 0xA9, 0x67, 0x2B, 0x56, 0x7D, 0x2B
	.byte 0xFE, 0xE7, 0x19, 0xFE, 0xD7, 0xB5, 0x62, 0xD7, 0xAB, 0x4D, 0xE6, 0xAB, 0x76, 0xEC, 0x9A, 0x76
	.byte 0xCA, 0x8F, 0x45, 0xCA, 0x82, 0x1F, 0x9D, 0x82, 0xC9, 0x89, 0x40, 0xC9, 0x7D, 0xFA, 0x87, 0x7D
	.byte 0xFA, 0xEF, 0x15, 0xFA, 0x59, 0xB2, 0xEB, 0x59, 0x47, 0x8E, 0xC9, 0x47, 0xF0, 0xFB, 0x0B, 0xF0
	.byte 0xAD, 0x41, 0xEC, 0xAD, 0xD4, 0xB3, 0x67, 0xD4, 0xA2, 0x5F, 0xFD, 0xA2, 0xAF, 0x45, 0xEA, 0xAF
	.byte 0x9C, 0x23, 0xBF, 0x9C, 0xA4, 0x53, 0xF7, 0xA4, 0x72, 0xE4, 0x96, 0x72, 0xC0, 0x9B, 0x5B, 0xC0
	.byte 0xB7, 0x75, 0xC2, 0xB7, 0xFD, 0xE1, 0x1C, 0xFD, 0x93, 0x3D, 0xAE, 0x93, 0x26, 0x4C, 0x6A, 0x26
	.byte 0x36, 0x6C, 0x5A, 0x36, 0x3F, 0x7E, 0x41, 0x3F, 0xF7, 0xF5, 0x02, 0xF7, 0xCC, 0x83, 0x4F, 0xCC
	.byte 0x34, 0x68, 0x5C, 0x34, 0xA5, 0x51, 0xF4, 0xA5, 0xE5, 0xD1, 0x34, 0xE5, 0xF1, 0xF9, 0x08, 0xF1
	.byte 0x71, 0xE2, 0x93, 0x71, 0xD8, 0xAB, 0x73, 0xD8, 0x31, 0x62, 0x53, 0x31, 0x15, 0x2A, 0x3F, 0x15
	.byte 0x04, 0x08, 0x0C, 0x04, 0xC7, 0x95, 0x52, 0xC7, 0x23, 0x46, 0x65, 0x23, 0xC3, 0x9D, 0x5E, 0xC3
	.byte 0x18, 0x30, 0x28, 0x18, 0x96, 0x37, 0xA1, 0x96, 0x05, 0x0A, 0x0F, 0x05, 0x9A, 0x2F, 0xB5, 0x9A
	.byte 0x07, 0x0E, 0x09, 0x07, 0x12, 0x24, 0x36, 0x12, 0x80, 0x1B, 0x9B, 0x80, 0xE2, 0xDF, 0x3D, 0xE2
	.byte 0xEB, 0xCD, 0x26, 0xEB, 0x27, 0x4E, 0x69, 0x27, 0xB2, 0x7F, 0xCD, 0xB2, 0x75, 0xEA, 0x9F, 0x75
	.byte 0x09, 0x12, 0x1B, 0x09, 0x83, 0x1D, 0x9E, 0x83, 0x2C, 0x58, 0x74, 0x2C, 0x1A, 0x34, 0x2E, 0x1A
	.byte 0x1B, 0x36, 0x2D, 0x1B, 0x6E, 0xDC, 0xB2, 0x6E, 0x5A, 0xB4, 0xEE, 0x5A, 0xA0, 0x5B, 0xFB, 0xA0
	.byte 0x52, 0xA4, 0xF6, 0x52, 0x3B, 0x76, 0x4D, 0x3B, 0xD6, 0xB7, 0x61, 0xD6, 0xB3, 0x7D, 0xCE, 0xB3
	.byte 0x29, 0x52, 0x7B, 0x29, 0xE3, 0xDD, 0x3E, 0xE3, 0x2F, 0x5E, 0x71, 0x2F, 0x84, 0x13, 0x97, 0x84
	.byte 0x53, 0xA6, 0xF5, 0x53, 0xD1, 0xB9, 0x68, 0xD1, 0x00, 0x00, 0x00, 0x00, 0xED, 0xC1, 0x2C, 0xED
	.byte 0x20, 0x40, 0x60, 0x20, 0xFC, 0xE3, 0x1F, 0xFC, 0xB1, 0x79, 0xC8, 0xB1, 0x5B, 0xB6, 0xED, 0x5B
	.byte 0x6A, 0xD4, 0xBE, 0x6A, 0xCB, 0x8D, 0x46, 0xCB, 0xBE, 0x67, 0xD9, 0xBE, 0x39, 0x72, 0x4B, 0x39
	.byte 0x4A, 0x94, 0xDE, 0x4A, 0x4C, 0x98, 0xD4, 0x4C, 0x58, 0xB0, 0xE8, 0x58, 0xCF, 0x85, 0x4A, 0xCF
	.byte 0xD0, 0xBB, 0x6B, 0xD0, 0xEF, 0xC5, 0x2A, 0xEF, 0xAA, 0x4F, 0xE5, 0xAA, 0xFB, 0xED, 0x16, 0xFB
	.byte 0x43, 0x86, 0xC5, 0x43, 0x4D, 0x9A, 0xD7, 0x4D, 0x33, 0x66, 0x55, 0x33, 0x85, 0x11, 0x94, 0x85
	.byte 0x45, 0x8A, 0xCF, 0x45, 0xF9, 0xE9, 0x10, 0xF9, 0x02, 0x04, 0x06, 0x02, 0x7F, 0xFE, 0x81, 0x7F
	.byte 0x50, 0xA0, 0xF0, 0x50, 0x3C, 0x78, 0x44, 0x3C, 0x9F, 0x25, 0xBA, 0x9F, 0xA8, 0x4B, 0xE3, 0xA8
	.byte 0x51, 0xA2, 0xF3, 0x51, 0xA3, 0x5D, 0xFE, 0xA3, 0x40, 0x80, 0xC0, 0x40, 0x8F, 0x05, 0x8A, 0x8F
	.byte 0x92, 0x3F, 0xAD, 0x92, 0x9D, 0x21, 0xBC, 0x9D, 0x38, 0x70, 0x48, 0x38, 0xF5, 0xF1, 0x04, 0xF5
	.byte 0xBC, 0x63, 0xDF, 0xBC, 0xB6, 0x77, 0xC1, 0xB6, 0xDA, 0xAF, 0x75, 0xDA, 0x21, 0x42, 0x63, 0x21
	.byte 0x10, 0x20, 0x30, 0x10, 0xFF, 0xE5, 0x1A, 0xFF, 0xF3, 0xFD, 0x0E, 0xF3, 0xD2, 0xBF, 0x6D, 0xD2
	.byte 0xCD, 0x81, 0x4C, 0xCD, 0x0C, 0x18, 0x14, 0x0C, 0x13, 0x26, 0x35, 0x13, 0xEC, 0xC3, 0x2F, 0xEC
	.byte 0x5F, 0xBE, 0xE1, 0x5F, 0x97, 0x35, 0xA2, 0x97, 0x44, 0x88, 0xCC, 0x44, 0x17, 0x2E, 0x39, 0x17
	.byte 0xC4, 0x93, 0x57, 0xC4, 0xA7, 0x55, 0xF2, 0xA7, 0x7E, 0xFC, 0x82, 0x7E, 0x3D, 0x7A, 0x47, 0x3D
	.byte 0x64, 0xC8, 0xAC, 0x64, 0x5D, 0xBA, 0xE7, 0x5D, 0x19, 0x32, 0x2B, 0x19, 0x73, 0xE6, 0x95, 0x73
	.byte 0x60, 0xC0, 0xA0, 0x60, 0x81, 0x19, 0x98, 0x81, 0x4F, 0x9E, 0xD1, 0x4F, 0xDC, 0xA3, 0x7F, 0xDC
	.byte 0x22, 0x44, 0x66, 0x22, 0x2A, 0x54, 0x7E, 0x2A, 0x90, 0x3B, 0xAB, 0x90, 0x88, 0x0B, 0x83, 0x88
	.byte 0x46, 0x8C, 0xCA, 0x46, 0xEE, 0xC7, 0x29, 0xEE, 0xB8, 0x6B, 0xD3, 0xB8, 0x14, 0x28, 0x3C, 0x14
	.byte 0xDE, 0xA7, 0x79, 0xDE, 0x5E, 0xBC, 0xE2, 0x5E, 0x0B, 0x16, 0x1D, 0x0B, 0xDB, 0xAD, 0x76, 0xDB
	.byte 0xE0, 0xDB, 0x3B, 0xE0, 0x32, 0x64, 0x56, 0x32, 0x3A, 0x74, 0x4E, 0x3A, 0x0A, 0x14, 0x1E, 0x0A
	.byte 0x49, 0x92, 0xDB, 0x49, 0x06, 0x0C, 0x0A, 0x06, 0x24, 0x48, 0x6C, 0x24, 0x5C, 0xB8, 0xE4, 0x5C
	.byte 0xC2, 0x9F, 0x5D, 0xC2, 0xD3, 0xBD, 0x6E, 0xD3, 0xAC, 0x43, 0xEF, 0xAC, 0x62, 0xC4, 0xA6, 0x62
	.byte 0x91, 0x39, 0xA8, 0x91, 0x95, 0x31, 0xA4, 0x95, 0xE4, 0xD3, 0x37, 0xE4, 0x79, 0xF2, 0x8B, 0x79
	.byte 0xE7, 0xD5, 0x32, 0xE7, 0xC8, 0x8B, 0x43, 0xC8, 0x37, 0x6E, 0x59, 0x37, 0x6D, 0xDA, 0xB7, 0x6D
	.byte 0x8D, 0x01, 0x8C, 0x8D, 0xD5, 0xB1, 0x64, 0xD5, 0x4E, 0x9C, 0xD2, 0x4E, 0xA9, 0x49, 0xE0, 0xA9
	.byte 0x6C, 0xD8, 0xB4, 0x6C, 0x56, 0xAC, 0xFA, 0x56, 0xF4, 0xF3, 0x07, 0xF4, 0xEA, 0xCF, 0x25, 0xEA
	.byte 0x65, 0xCA, 0xAF, 0x65, 0x7A, 0xF4, 0x8E, 0x7A, 0xAE, 0x47, 0xE9, 0xAE, 0x08, 0x10, 0x18, 0x08
	.byte 0xBA, 0x6F, 0xD5, 0xBA, 0x78, 0xF0, 0x88, 0x78, 0x25, 0x4A, 0x6F, 0x25, 0x2E, 0x5C, 0x72, 0x2E
	.byte 0x1C, 0x38, 0x24, 0x1C, 0xA6, 0x57, 0xF1, 0xA6, 0xB4, 0x73, 0xC7, 0xB4, 0xC6, 0x97, 0x51, 0xC6
	.byte 0xE8, 0xCB, 0x23, 0xE8, 0xDD, 0xA1, 0x7C, 0xDD, 0x74, 0xE8, 0x9C, 0x74, 0x1F, 0x3E, 0x21, 0x1F
	.byte 0x4B, 0x96, 0xDD, 0x4B, 0xBD, 0x61, 0xDC, 0xBD, 0x8B, 0x0D, 0x86, 0x8B, 0x8A, 0x0F, 0x85, 0x8A
	.byte 0x70, 0xE0, 0x90, 0x70, 0x3E, 0x7C, 0x42, 0x3E, 0xB5, 0x71, 0xC4, 0xB5, 0x66, 0xCC, 0xAA, 0x66
	.byte 0x48, 0x90, 0xD8, 0x48, 0x03, 0x06, 0x05, 0x03, 0xF6, 0xF7, 0x01, 0xF6, 0x0E, 0x1C, 0x12, 0x0E
	.byte 0x61, 0xC2, 0xA3, 0x61, 0x35, 0x6A, 0x5F, 0x35, 0x57, 0xAE, 0xF9, 0x57, 0xB9, 0x69, 0xD0, 0xB9
	.byte 0x86, 0x17, 0x91, 0x86, 0xC1, 0x99, 0x58, 0xC1, 0x1D, 0x3A, 0x27, 0x1D, 0x9E, 0x27, 0xB9, 0x9E
	.byte 0xE1, 0xD9, 0x38, 0xE1, 0xF8, 0xEB, 0x13, 0xF8, 0x98, 0x2B, 0xB3, 0x98, 0x11, 0x22, 0x33, 0x11
	.byte 0x69, 0xD2, 0xBB, 0x69, 0xD9, 0xA9, 0x70, 0xD9, 0x8E, 0x07, 0x89, 0x8E, 0x94, 0x33, 0xA7, 0x94
	.byte 0x9B, 0x2D, 0xB6, 0x9B, 0x1E, 0x3C, 0x22, 0x1E, 0x87, 0x15, 0x92, 0x87, 0xE9, 0xC9, 0x20, 0xE9
	.byte 0xCE, 0x87, 0x49, 0xCE, 0x55, 0xAA, 0xFF, 0x55, 0x28, 0x50, 0x78, 0x28, 0xDF, 0xA5, 0x7A, 0xDF
	.byte 0x8C, 0x03, 0x8F, 0x8C, 0xA1, 0x59, 0xF8, 0xA1, 0x89, 0x09, 0x80, 0x89, 0x0D, 0x1A, 0x17, 0x0D
	.byte 0xBF, 0x65, 0xDA, 0xBF, 0xE6, 0xD7, 0x31, 0xE6, 0x42, 0x84, 0xC6, 0x42, 0x68, 0xD0, 0xB8, 0x68
	.byte 0x41, 0x82, 0xC3, 0x41, 0x99, 0x29, 0xB0, 0x99, 0x2D, 0x5A, 0x77, 0x2D, 0x0F, 0x1E, 0x11, 0x0F
	.byte 0xB0, 0x7B, 0xCB, 0xB0, 0x54, 0xA8, 0xFC, 0x54, 0xBB, 0x6D, 0xD6, 0xBB, 0x16, 0x2C, 0x3A, 0x16

	.global MOD13_0223DC6C
MOD13_0223DC6C: ; 0x0223DC6C
	.byte 0xC6, 0xA5, 0x63, 0x63, 0xF8, 0x84, 0x7C, 0x7C, 0xEE, 0x99, 0x77, 0x77, 0xF6, 0x8D, 0x7B, 0x7B
	.byte 0xFF, 0x0D, 0xF2, 0xF2, 0xD6, 0xBD, 0x6B, 0x6B, 0xDE, 0xB1, 0x6F, 0x6F, 0x91, 0x54, 0xC5, 0xC5
	.byte 0x60, 0x50, 0x30, 0x30, 0x02, 0x03, 0x01, 0x01, 0xCE, 0xA9, 0x67, 0x67, 0x56, 0x7D, 0x2B, 0x2B
	.byte 0xE7, 0x19, 0xFE, 0xFE, 0xB5, 0x62, 0xD7, 0xD7, 0x4D, 0xE6, 0xAB, 0xAB, 0xEC, 0x9A, 0x76, 0x76
	.byte 0x8F, 0x45, 0xCA, 0xCA, 0x1F, 0x9D, 0x82, 0x82, 0x89, 0x40, 0xC9, 0xC9, 0xFA, 0x87, 0x7D, 0x7D
	.byte 0xEF, 0x15, 0xFA, 0xFA, 0xB2, 0xEB, 0x59, 0x59, 0x8E, 0xC9, 0x47, 0x47, 0xFB, 0x0B, 0xF0, 0xF0
	.byte 0x41, 0xEC, 0xAD, 0xAD, 0xB3, 0x67, 0xD4, 0xD4, 0x5F, 0xFD, 0xA2, 0xA2, 0x45, 0xEA, 0xAF, 0xAF
	.byte 0x23, 0xBF, 0x9C, 0x9C, 0x53, 0xF7, 0xA4, 0xA4, 0xE4, 0x96, 0x72, 0x72, 0x9B, 0x5B, 0xC0, 0xC0
	.byte 0x75, 0xC2, 0xB7, 0xB7, 0xE1, 0x1C, 0xFD, 0xFD, 0x3D, 0xAE, 0x93, 0x93, 0x4C, 0x6A, 0x26, 0x26
	.byte 0x6C, 0x5A, 0x36, 0x36, 0x7E, 0x41, 0x3F, 0x3F, 0xF5, 0x02, 0xF7, 0xF7, 0x83, 0x4F, 0xCC, 0xCC
	.byte 0x68, 0x5C, 0x34, 0x34, 0x51, 0xF4, 0xA5, 0xA5, 0xD1, 0x34, 0xE5, 0xE5, 0xF9, 0x08, 0xF1, 0xF1
	.byte 0xE2, 0x93, 0x71, 0x71, 0xAB, 0x73, 0xD8, 0xD8, 0x62, 0x53, 0x31, 0x31, 0x2A, 0x3F, 0x15, 0x15
	.byte 0x08, 0x0C, 0x04, 0x04, 0x95, 0x52, 0xC7, 0xC7, 0x46, 0x65, 0x23, 0x23, 0x9D, 0x5E, 0xC3, 0xC3
	.byte 0x30, 0x28, 0x18, 0x18, 0x37, 0xA1, 0x96, 0x96, 0x0A, 0x0F, 0x05, 0x05, 0x2F, 0xB5, 0x9A, 0x9A
	.byte 0x0E, 0x09, 0x07, 0x07, 0x24, 0x36, 0x12, 0x12, 0x1B, 0x9B, 0x80, 0x80, 0xDF, 0x3D, 0xE2, 0xE2
	.byte 0xCD, 0x26, 0xEB, 0xEB, 0x4E, 0x69, 0x27, 0x27, 0x7F, 0xCD, 0xB2, 0xB2, 0xEA, 0x9F, 0x75, 0x75
	.byte 0x12, 0x1B, 0x09, 0x09, 0x1D, 0x9E, 0x83, 0x83, 0x58, 0x74, 0x2C, 0x2C, 0x34, 0x2E, 0x1A, 0x1A
	.byte 0x36, 0x2D, 0x1B, 0x1B, 0xDC, 0xB2, 0x6E, 0x6E, 0xB4, 0xEE, 0x5A, 0x5A, 0x5B, 0xFB, 0xA0, 0xA0
	.byte 0xA4, 0xF6, 0x52, 0x52, 0x76, 0x4D, 0x3B, 0x3B, 0xB7, 0x61, 0xD6, 0xD6, 0x7D, 0xCE, 0xB3, 0xB3
	.byte 0x52, 0x7B, 0x29, 0x29, 0xDD, 0x3E, 0xE3, 0xE3, 0x5E, 0x71, 0x2F, 0x2F, 0x13, 0x97, 0x84, 0x84
	.byte 0xA6, 0xF5, 0x53, 0x53, 0xB9, 0x68, 0xD1, 0xD1, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x2C, 0xED, 0xED
	.byte 0x40, 0x60, 0x20, 0x20, 0xE3, 0x1F, 0xFC, 0xFC, 0x79, 0xC8, 0xB1, 0xB1, 0xB6, 0xED, 0x5B, 0x5B
	.byte 0xD4, 0xBE, 0x6A, 0x6A, 0x8D, 0x46, 0xCB, 0xCB, 0x67, 0xD9, 0xBE, 0xBE, 0x72, 0x4B, 0x39, 0x39
	.byte 0x94, 0xDE, 0x4A, 0x4A, 0x98, 0xD4, 0x4C, 0x4C, 0xB0, 0xE8, 0x58, 0x58, 0x85, 0x4A, 0xCF, 0xCF
	.byte 0xBB, 0x6B, 0xD0, 0xD0, 0xC5, 0x2A, 0xEF, 0xEF, 0x4F, 0xE5, 0xAA, 0xAA, 0xED, 0x16, 0xFB, 0xFB
	.byte 0x86, 0xC5, 0x43, 0x43, 0x9A, 0xD7, 0x4D, 0x4D, 0x66, 0x55, 0x33, 0x33, 0x11, 0x94, 0x85, 0x85
	.byte 0x8A, 0xCF, 0x45, 0x45, 0xE9, 0x10, 0xF9, 0xF9, 0x04, 0x06, 0x02, 0x02, 0xFE, 0x81, 0x7F, 0x7F
	.byte 0xA0, 0xF0, 0x50, 0x50, 0x78, 0x44, 0x3C, 0x3C, 0x25, 0xBA, 0x9F, 0x9F, 0x4B, 0xE3, 0xA8, 0xA8
	.byte 0xA2, 0xF3, 0x51, 0x51, 0x5D, 0xFE, 0xA3, 0xA3, 0x80, 0xC0, 0x40, 0x40, 0x05, 0x8A, 0x8F, 0x8F
	.byte 0x3F, 0xAD, 0x92, 0x92, 0x21, 0xBC, 0x9D, 0x9D, 0x70, 0x48, 0x38, 0x38, 0xF1, 0x04, 0xF5, 0xF5
	.byte 0x63, 0xDF, 0xBC, 0xBC, 0x77, 0xC1, 0xB6, 0xB6, 0xAF, 0x75, 0xDA, 0xDA, 0x42, 0x63, 0x21, 0x21
	.byte 0x20, 0x30, 0x10, 0x10, 0xE5, 0x1A, 0xFF, 0xFF, 0xFD, 0x0E, 0xF3, 0xF3, 0xBF, 0x6D, 0xD2, 0xD2
	.byte 0x81, 0x4C, 0xCD, 0xCD, 0x18, 0x14, 0x0C, 0x0C, 0x26, 0x35, 0x13, 0x13, 0xC3, 0x2F, 0xEC, 0xEC
	.byte 0xBE, 0xE1, 0x5F, 0x5F, 0x35, 0xA2, 0x97, 0x97, 0x88, 0xCC, 0x44, 0x44, 0x2E, 0x39, 0x17, 0x17
	.byte 0x93, 0x57, 0xC4, 0xC4, 0x55, 0xF2, 0xA7, 0xA7, 0xFC, 0x82, 0x7E, 0x7E, 0x7A, 0x47, 0x3D, 0x3D
	.byte 0xC8, 0xAC, 0x64, 0x64, 0xBA, 0xE7, 0x5D, 0x5D, 0x32, 0x2B, 0x19, 0x19, 0xE6, 0x95, 0x73, 0x73
	.byte 0xC0, 0xA0, 0x60, 0x60, 0x19, 0x98, 0x81, 0x81, 0x9E, 0xD1, 0x4F, 0x4F, 0xA3, 0x7F, 0xDC, 0xDC
	.byte 0x44, 0x66, 0x22, 0x22, 0x54, 0x7E, 0x2A, 0x2A, 0x3B, 0xAB, 0x90, 0x90, 0x0B, 0x83, 0x88, 0x88
	.byte 0x8C, 0xCA, 0x46, 0x46, 0xC7, 0x29, 0xEE, 0xEE, 0x6B, 0xD3, 0xB8, 0xB8, 0x28, 0x3C, 0x14, 0x14
	.byte 0xA7, 0x79, 0xDE, 0xDE, 0xBC, 0xE2, 0x5E, 0x5E, 0x16, 0x1D, 0x0B, 0x0B, 0xAD, 0x76, 0xDB, 0xDB
	.byte 0xDB, 0x3B, 0xE0, 0xE0, 0x64, 0x56, 0x32, 0x32, 0x74, 0x4E, 0x3A, 0x3A, 0x14, 0x1E, 0x0A, 0x0A
	.byte 0x92, 0xDB, 0x49, 0x49, 0x0C, 0x0A, 0x06, 0x06, 0x48, 0x6C, 0x24, 0x24, 0xB8, 0xE4, 0x5C, 0x5C
	.byte 0x9F, 0x5D, 0xC2, 0xC2, 0xBD, 0x6E, 0xD3, 0xD3, 0x43, 0xEF, 0xAC, 0xAC, 0xC4, 0xA6, 0x62, 0x62
	.byte 0x39, 0xA8, 0x91, 0x91, 0x31, 0xA4, 0x95, 0x95, 0xD3, 0x37, 0xE4, 0xE4, 0xF2, 0x8B, 0x79, 0x79
	.byte 0xD5, 0x32, 0xE7, 0xE7, 0x8B, 0x43, 0xC8, 0xC8, 0x6E, 0x59, 0x37, 0x37, 0xDA, 0xB7, 0x6D, 0x6D
	.byte 0x01, 0x8C, 0x8D, 0x8D, 0xB1, 0x64, 0xD5, 0xD5, 0x9C, 0xD2, 0x4E, 0x4E, 0x49, 0xE0, 0xA9, 0xA9
	.byte 0xD8, 0xB4, 0x6C, 0x6C, 0xAC, 0xFA, 0x56, 0x56, 0xF3, 0x07, 0xF4, 0xF4, 0xCF, 0x25, 0xEA, 0xEA
	.byte 0xCA, 0xAF, 0x65, 0x65, 0xF4, 0x8E, 0x7A, 0x7A, 0x47, 0xE9, 0xAE, 0xAE, 0x10, 0x18, 0x08, 0x08
	.byte 0x6F, 0xD5, 0xBA, 0xBA, 0xF0, 0x88, 0x78, 0x78, 0x4A, 0x6F, 0x25, 0x25, 0x5C, 0x72, 0x2E, 0x2E
	.byte 0x38, 0x24, 0x1C, 0x1C, 0x57, 0xF1, 0xA6, 0xA6, 0x73, 0xC7, 0xB4, 0xB4, 0x97, 0x51, 0xC6, 0xC6
	.byte 0xCB, 0x23, 0xE8, 0xE8, 0xA1, 0x7C, 0xDD, 0xDD, 0xE8, 0x9C, 0x74, 0x74, 0x3E, 0x21, 0x1F, 0x1F
	.byte 0x96, 0xDD, 0x4B, 0x4B, 0x61, 0xDC, 0xBD, 0xBD, 0x0D, 0x86, 0x8B, 0x8B, 0x0F, 0x85, 0x8A, 0x8A
	.byte 0xE0, 0x90, 0x70, 0x70, 0x7C, 0x42, 0x3E, 0x3E, 0x71, 0xC4, 0xB5, 0xB5, 0xCC, 0xAA, 0x66, 0x66
	.byte 0x90, 0xD8, 0x48, 0x48, 0x06, 0x05, 0x03, 0x03, 0xF7, 0x01, 0xF6, 0xF6, 0x1C, 0x12, 0x0E, 0x0E
	.byte 0xC2, 0xA3, 0x61, 0x61, 0x6A, 0x5F, 0x35, 0x35, 0xAE, 0xF9, 0x57, 0x57, 0x69, 0xD0, 0xB9, 0xB9
	.byte 0x17, 0x91, 0x86, 0x86, 0x99, 0x58, 0xC1, 0xC1, 0x3A, 0x27, 0x1D, 0x1D, 0x27, 0xB9, 0x9E, 0x9E
	.byte 0xD9, 0x38, 0xE1, 0xE1, 0xEB, 0x13, 0xF8, 0xF8, 0x2B, 0xB3, 0x98, 0x98, 0x22, 0x33, 0x11, 0x11
	.byte 0xD2, 0xBB, 0x69, 0x69, 0xA9, 0x70, 0xD9, 0xD9, 0x07, 0x89, 0x8E, 0x8E, 0x33, 0xA7, 0x94, 0x94
	.byte 0x2D, 0xB6, 0x9B, 0x9B, 0x3C, 0x22, 0x1E, 0x1E, 0x15, 0x92, 0x87, 0x87, 0xC9, 0x20, 0xE9, 0xE9
	.byte 0x87, 0x49, 0xCE, 0xCE, 0xAA, 0xFF, 0x55, 0x55, 0x50, 0x78, 0x28, 0x28, 0xA5, 0x7A, 0xDF, 0xDF
	.byte 0x03, 0x8F, 0x8C, 0x8C, 0x59, 0xF8, 0xA1, 0xA1, 0x09, 0x80, 0x89, 0x89, 0x1A, 0x17, 0x0D, 0x0D
	.byte 0x65, 0xDA, 0xBF, 0xBF, 0xD7, 0x31, 0xE6, 0xE6, 0x84, 0xC6, 0x42, 0x42, 0xD0, 0xB8, 0x68, 0x68
	.byte 0x82, 0xC3, 0x41, 0x41, 0x29, 0xB0, 0x99, 0x99, 0x5A, 0x77, 0x2D, 0x2D, 0x1E, 0x11, 0x0F, 0x0F
	.byte 0x7B, 0xCB, 0xB0, 0xB0, 0xA8, 0xFC, 0x54, 0x54, 0x6D, 0xD6, 0xBB, 0xBB, 0x2C, 0x3A, 0x16, 0x16

	.global MOD13_0223E06C
MOD13_0223E06C: ; 0x0223E06C
	.byte 0x63, 0x63, 0x63, 0x63, 0x7C, 0x7C, 0x7C, 0x7C, 0x77, 0x77, 0x77, 0x77, 0x7B, 0x7B, 0x7B, 0x7B
	.byte 0xF2, 0xF2, 0xF2, 0xF2, 0x6B, 0x6B, 0x6B, 0x6B, 0x6F, 0x6F, 0x6F, 0x6F, 0xC5, 0xC5, 0xC5, 0xC5
	.byte 0x30, 0x30, 0x30, 0x30, 0x01, 0x01, 0x01, 0x01, 0x67, 0x67, 0x67, 0x67, 0x2B, 0x2B, 0x2B, 0x2B
	.byte 0xFE, 0xFE, 0xFE, 0xFE, 0xD7, 0xD7, 0xD7, 0xD7, 0xAB, 0xAB, 0xAB, 0xAB, 0x76, 0x76, 0x76, 0x76
	.byte 0xCA, 0xCA, 0xCA, 0xCA, 0x82, 0x82, 0x82, 0x82, 0xC9, 0xC9, 0xC9, 0xC9, 0x7D, 0x7D, 0x7D, 0x7D
	.byte 0xFA, 0xFA, 0xFA, 0xFA, 0x59, 0x59, 0x59, 0x59, 0x47, 0x47, 0x47, 0x47, 0xF0, 0xF0, 0xF0, 0xF0
	.byte 0xAD, 0xAD, 0xAD, 0xAD, 0xD4, 0xD4, 0xD4, 0xD4, 0xA2, 0xA2, 0xA2, 0xA2, 0xAF, 0xAF, 0xAF, 0xAF
	.byte 0x9C, 0x9C, 0x9C, 0x9C, 0xA4, 0xA4, 0xA4, 0xA4, 0x72, 0x72, 0x72, 0x72, 0xC0, 0xC0, 0xC0, 0xC0
	.byte 0xB7, 0xB7, 0xB7, 0xB7, 0xFD, 0xFD, 0xFD, 0xFD, 0x93, 0x93, 0x93, 0x93, 0x26, 0x26, 0x26, 0x26
	.byte 0x36, 0x36, 0x36, 0x36, 0x3F, 0x3F, 0x3F, 0x3F, 0xF7, 0xF7, 0xF7, 0xF7, 0xCC, 0xCC, 0xCC, 0xCC
	.byte 0x34, 0x34, 0x34, 0x34, 0xA5, 0xA5, 0xA5, 0xA5, 0xE5, 0xE5, 0xE5, 0xE5, 0xF1, 0xF1, 0xF1, 0xF1
	.byte 0x71, 0x71, 0x71, 0x71, 0xD8, 0xD8, 0xD8, 0xD8, 0x31, 0x31, 0x31, 0x31, 0x15, 0x15, 0x15, 0x15
	.byte 0x04, 0x04, 0x04, 0x04, 0xC7, 0xC7, 0xC7, 0xC7, 0x23, 0x23, 0x23, 0x23, 0xC3, 0xC3, 0xC3, 0xC3
	.byte 0x18, 0x18, 0x18, 0x18, 0x96, 0x96, 0x96, 0x96, 0x05, 0x05, 0x05, 0x05, 0x9A, 0x9A, 0x9A, 0x9A
	.byte 0x07, 0x07, 0x07, 0x07, 0x12, 0x12, 0x12, 0x12, 0x80, 0x80, 0x80, 0x80, 0xE2, 0xE2, 0xE2, 0xE2
	.byte 0xEB, 0xEB, 0xEB, 0xEB, 0x27, 0x27, 0x27, 0x27, 0xB2, 0xB2, 0xB2, 0xB2, 0x75, 0x75, 0x75, 0x75
	.byte 0x09, 0x09, 0x09, 0x09, 0x83, 0x83, 0x83, 0x83, 0x2C, 0x2C, 0x2C, 0x2C, 0x1A, 0x1A, 0x1A, 0x1A
	.byte 0x1B, 0x1B, 0x1B, 0x1B, 0x6E, 0x6E, 0x6E, 0x6E, 0x5A, 0x5A, 0x5A, 0x5A, 0xA0, 0xA0, 0xA0, 0xA0
	.byte 0x52, 0x52, 0x52, 0x52, 0x3B, 0x3B, 0x3B, 0x3B, 0xD6, 0xD6, 0xD6, 0xD6, 0xB3, 0xB3, 0xB3, 0xB3
	.byte 0x29, 0x29, 0x29, 0x29, 0xE3, 0xE3, 0xE3, 0xE3, 0x2F, 0x2F, 0x2F, 0x2F, 0x84, 0x84, 0x84, 0x84
	.byte 0x53, 0x53, 0x53, 0x53, 0xD1, 0xD1, 0xD1, 0xD1, 0x00, 0x00, 0x00, 0x00, 0xED, 0xED, 0xED, 0xED
	.byte 0x20, 0x20, 0x20, 0x20, 0xFC, 0xFC, 0xFC, 0xFC, 0xB1, 0xB1, 0xB1, 0xB1, 0x5B, 0x5B, 0x5B, 0x5B
	.byte 0x6A, 0x6A, 0x6A, 0x6A, 0xCB, 0xCB, 0xCB, 0xCB, 0xBE, 0xBE, 0xBE, 0xBE, 0x39, 0x39, 0x39, 0x39
	.byte 0x4A, 0x4A, 0x4A, 0x4A, 0x4C, 0x4C, 0x4C, 0x4C, 0x58, 0x58, 0x58, 0x58, 0xCF, 0xCF, 0xCF, 0xCF
	.byte 0xD0, 0xD0, 0xD0, 0xD0, 0xEF, 0xEF, 0xEF, 0xEF, 0xAA, 0xAA, 0xAA, 0xAA, 0xFB, 0xFB, 0xFB, 0xFB
	.byte 0x43, 0x43, 0x43, 0x43, 0x4D, 0x4D, 0x4D, 0x4D, 0x33, 0x33, 0x33, 0x33, 0x85, 0x85, 0x85, 0x85
	.byte 0x45, 0x45, 0x45, 0x45, 0xF9, 0xF9, 0xF9, 0xF9, 0x02, 0x02, 0x02, 0x02, 0x7F, 0x7F, 0x7F, 0x7F
	.byte 0x50, 0x50, 0x50, 0x50, 0x3C, 0x3C, 0x3C, 0x3C, 0x9F, 0x9F, 0x9F, 0x9F, 0xA8, 0xA8, 0xA8, 0xA8
	.byte 0x51, 0x51, 0x51, 0x51, 0xA3, 0xA3, 0xA3, 0xA3, 0x40, 0x40, 0x40, 0x40, 0x8F, 0x8F, 0x8F, 0x8F
	.byte 0x92, 0x92, 0x92, 0x92, 0x9D, 0x9D, 0x9D, 0x9D, 0x38, 0x38, 0x38, 0x38, 0xF5, 0xF5, 0xF5, 0xF5
	.byte 0xBC, 0xBC, 0xBC, 0xBC, 0xB6, 0xB6, 0xB6, 0xB6, 0xDA, 0xDA, 0xDA, 0xDA, 0x21, 0x21, 0x21, 0x21
	.byte 0x10, 0x10, 0x10, 0x10, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0xF3, 0xF3, 0xF3, 0xD2, 0xD2, 0xD2, 0xD2
	.byte 0xCD, 0xCD, 0xCD, 0xCD, 0x0C, 0x0C, 0x0C, 0x0C, 0x13, 0x13, 0x13, 0x13, 0xEC, 0xEC, 0xEC, 0xEC
	.byte 0x5F, 0x5F, 0x5F, 0x5F, 0x97, 0x97, 0x97, 0x97, 0x44, 0x44, 0x44, 0x44, 0x17, 0x17, 0x17, 0x17
	.byte 0xC4, 0xC4, 0xC4, 0xC4, 0xA7, 0xA7, 0xA7, 0xA7, 0x7E, 0x7E, 0x7E, 0x7E, 0x3D, 0x3D, 0x3D, 0x3D
	.byte 0x64, 0x64, 0x64, 0x64, 0x5D, 0x5D, 0x5D, 0x5D, 0x19, 0x19, 0x19, 0x19, 0x73, 0x73, 0x73, 0x73
	.byte 0x60, 0x60, 0x60, 0x60, 0x81, 0x81, 0x81, 0x81, 0x4F, 0x4F, 0x4F, 0x4F, 0xDC, 0xDC, 0xDC, 0xDC
	.byte 0x22, 0x22, 0x22, 0x22, 0x2A, 0x2A, 0x2A, 0x2A, 0x90, 0x90, 0x90, 0x90, 0x88, 0x88, 0x88, 0x88
	.byte 0x46, 0x46, 0x46, 0x46, 0xEE, 0xEE, 0xEE, 0xEE, 0xB8, 0xB8, 0xB8, 0xB8, 0x14, 0x14, 0x14, 0x14
	.byte 0xDE, 0xDE, 0xDE, 0xDE, 0x5E, 0x5E, 0x5E, 0x5E, 0x0B, 0x0B, 0x0B, 0x0B, 0xDB, 0xDB, 0xDB, 0xDB
	.byte 0xE0, 0xE0, 0xE0, 0xE0, 0x32, 0x32, 0x32, 0x32, 0x3A, 0x3A, 0x3A, 0x3A, 0x0A, 0x0A, 0x0A, 0x0A
	.byte 0x49, 0x49, 0x49, 0x49, 0x06, 0x06, 0x06, 0x06, 0x24, 0x24, 0x24, 0x24, 0x5C, 0x5C, 0x5C, 0x5C
	.byte 0xC2, 0xC2, 0xC2, 0xC2, 0xD3, 0xD3, 0xD3, 0xD3, 0xAC, 0xAC, 0xAC, 0xAC, 0x62, 0x62, 0x62, 0x62
	.byte 0x91, 0x91, 0x91, 0x91, 0x95, 0x95, 0x95, 0x95, 0xE4, 0xE4, 0xE4, 0xE4, 0x79, 0x79, 0x79, 0x79
	.byte 0xE7, 0xE7, 0xE7, 0xE7, 0xC8, 0xC8, 0xC8, 0xC8, 0x37, 0x37, 0x37, 0x37, 0x6D, 0x6D, 0x6D, 0x6D
	.byte 0x8D, 0x8D, 0x8D, 0x8D, 0xD5, 0xD5, 0xD5, 0xD5, 0x4E, 0x4E, 0x4E, 0x4E, 0xA9, 0xA9, 0xA9, 0xA9
	.byte 0x6C, 0x6C, 0x6C, 0x6C, 0x56, 0x56, 0x56, 0x56, 0xF4, 0xF4, 0xF4, 0xF4, 0xEA, 0xEA, 0xEA, 0xEA
	.byte 0x65, 0x65, 0x65, 0x65, 0x7A, 0x7A, 0x7A, 0x7A, 0xAE, 0xAE, 0xAE, 0xAE, 0x08, 0x08, 0x08, 0x08
	.byte 0xBA, 0xBA, 0xBA, 0xBA, 0x78, 0x78, 0x78, 0x78, 0x25, 0x25, 0x25, 0x25, 0x2E, 0x2E, 0x2E, 0x2E
	.byte 0x1C, 0x1C, 0x1C, 0x1C, 0xA6, 0xA6, 0xA6, 0xA6, 0xB4, 0xB4, 0xB4, 0xB4, 0xC6, 0xC6, 0xC6, 0xC6
	.byte 0xE8, 0xE8, 0xE8, 0xE8, 0xDD, 0xDD, 0xDD, 0xDD, 0x74, 0x74, 0x74, 0x74, 0x1F, 0x1F, 0x1F, 0x1F
	.byte 0x4B, 0x4B, 0x4B, 0x4B, 0xBD, 0xBD, 0xBD, 0xBD, 0x8B, 0x8B, 0x8B, 0x8B, 0x8A, 0x8A, 0x8A, 0x8A
	.byte 0x70, 0x70, 0x70, 0x70, 0x3E, 0x3E, 0x3E, 0x3E, 0xB5, 0xB5, 0xB5, 0xB5, 0x66, 0x66, 0x66, 0x66
	.byte 0x48, 0x48, 0x48, 0x48, 0x03, 0x03, 0x03, 0x03, 0xF6, 0xF6, 0xF6, 0xF6, 0x0E, 0x0E, 0x0E, 0x0E
	.byte 0x61, 0x61, 0x61, 0x61, 0x35, 0x35, 0x35, 0x35, 0x57, 0x57, 0x57, 0x57, 0xB9, 0xB9, 0xB9, 0xB9
	.byte 0x86, 0x86, 0x86, 0x86, 0xC1, 0xC1, 0xC1, 0xC1, 0x1D, 0x1D, 0x1D, 0x1D, 0x9E, 0x9E, 0x9E, 0x9E
	.byte 0xE1, 0xE1, 0xE1, 0xE1, 0xF8, 0xF8, 0xF8, 0xF8, 0x98, 0x98, 0x98, 0x98, 0x11, 0x11, 0x11, 0x11
	.byte 0x69, 0x69, 0x69, 0x69, 0xD9, 0xD9, 0xD9, 0xD9, 0x8E, 0x8E, 0x8E, 0x8E, 0x94, 0x94, 0x94, 0x94
	.byte 0x9B, 0x9B, 0x9B, 0x9B, 0x1E, 0x1E, 0x1E, 0x1E, 0x87, 0x87, 0x87, 0x87, 0xE9, 0xE9, 0xE9, 0xE9
	.byte 0xCE, 0xCE, 0xCE, 0xCE, 0x55, 0x55, 0x55, 0x55, 0x28, 0x28, 0x28, 0x28, 0xDF, 0xDF, 0xDF, 0xDF
	.byte 0x8C, 0x8C, 0x8C, 0x8C, 0xA1, 0xA1, 0xA1, 0xA1, 0x89, 0x89, 0x89, 0x89, 0x0D, 0x0D, 0x0D, 0x0D
	.byte 0xBF, 0xBF, 0xBF, 0xBF, 0xE6, 0xE6, 0xE6, 0xE6, 0x42, 0x42, 0x42, 0x42, 0x68, 0x68, 0x68, 0x68
	.byte 0x41, 0x41, 0x41, 0x41, 0x99, 0x99, 0x99, 0x99, 0x2D, 0x2D, 0x2D, 0x2D, 0x0F, 0x0F, 0x0F, 0x0F
	.byte 0xB0, 0xB0, 0xB0, 0xB0, 0x54, 0x54, 0x54, 0x54, 0xBB, 0xBB, 0xBB, 0xBB, 0x16, 0x16, 0x16, 0x16

	.global MOD13_0223E46C
MOD13_0223E46C: ; 0x0223E46C
	.byte 0x50, 0xA7, 0xF4, 0x51, 0x53, 0x65, 0x41, 0x7E, 0xC3, 0xA4, 0x17, 0x1A, 0x96, 0x5E, 0x27, 0x3A
	.byte 0xCB, 0x6B, 0xAB, 0x3B, 0xF1, 0x45, 0x9D, 0x1F, 0xAB, 0x58, 0xFA, 0xAC, 0x93, 0x03, 0xE3, 0x4B
	.byte 0x55, 0xFA, 0x30, 0x20, 0xF6, 0x6D, 0x76, 0xAD, 0x91, 0x76, 0xCC, 0x88, 0x25, 0x4C, 0x02, 0xF5
	.byte 0xFC, 0xD7, 0xE5, 0x4F, 0xD7, 0xCB, 0x2A, 0xC5, 0x80, 0x44, 0x35, 0x26, 0x8F, 0xA3, 0x62, 0xB5
	.byte 0x49, 0x5A, 0xB1, 0xDE, 0x67, 0x1B, 0xBA, 0x25, 0x98, 0x0E, 0xEA, 0x45, 0xE1, 0xC0, 0xFE, 0x5D
	.byte 0x02, 0x75, 0x2F, 0xC3, 0x12, 0xF0, 0x4C, 0x81, 0xA3, 0x97, 0x46, 0x8D, 0xC6, 0xF9, 0xD3, 0x6B
	.byte 0xE7, 0x5F, 0x8F, 0x03, 0x95, 0x9C, 0x92, 0x15, 0xEB, 0x7A, 0x6D, 0xBF, 0xDA, 0x59, 0x52, 0x95
	.byte 0x2D, 0x83, 0xBE, 0xD4, 0xD3, 0x21, 0x74, 0x58, 0x29, 0x69, 0xE0, 0x49, 0x44, 0xC8, 0xC9, 0x8E
	.byte 0x6A, 0x89, 0xC2, 0x75, 0x78, 0x79, 0x8E, 0xF4, 0x6B, 0x3E, 0x58, 0x99, 0xDD, 0x71, 0xB9, 0x27
	.byte 0xB6, 0x4F, 0xE1, 0xBE, 0x17, 0xAD, 0x88, 0xF0, 0x66, 0xAC, 0x20, 0xC9, 0xB4, 0x3A, 0xCE, 0x7D
	.byte 0x18, 0x4A, 0xDF, 0x63, 0x82, 0x31, 0x1A, 0xE5, 0x60, 0x33, 0x51, 0x97, 0x45, 0x7F, 0x53, 0x62
	.byte 0xE0, 0x77, 0x64, 0xB1, 0x84, 0xAE, 0x6B, 0xBB, 0x1C, 0xA0, 0x81, 0xFE, 0x94, 0x2B, 0x08, 0xF9
	.byte 0x58, 0x68, 0x48, 0x70, 0x19, 0xFD, 0x45, 0x8F, 0x87, 0x6C, 0xDE, 0x94, 0xB7, 0xF8, 0x7B, 0x52
	.byte 0x23, 0xD3, 0x73, 0xAB, 0xE2, 0x02, 0x4B, 0x72, 0x57, 0x8F, 0x1F, 0xE3, 0x2A, 0xAB, 0x55, 0x66
	.byte 0x07, 0x28, 0xEB, 0xB2, 0x03, 0xC2, 0xB5, 0x2F, 0x9A, 0x7B, 0xC5, 0x86, 0xA5, 0x08, 0x37, 0xD3
	.byte 0xF2, 0x87, 0x28, 0x30, 0xB2, 0xA5, 0xBF, 0x23, 0xBA, 0x6A, 0x03, 0x02, 0x5C, 0x82, 0x16, 0xED
	.byte 0x2B, 0x1C, 0xCF, 0x8A, 0x92, 0xB4, 0x79, 0xA7, 0xF0, 0xF2, 0x07, 0xF3, 0xA1, 0xE2, 0x69, 0x4E
	.byte 0xCD, 0xF4, 0xDA, 0x65, 0xD5, 0xBE, 0x05, 0x06, 0x1F, 0x62, 0x34, 0xD1, 0x8A, 0xFE, 0xA6, 0xC4
	.byte 0x9D, 0x53, 0x2E, 0x34, 0xA0, 0x55, 0xF3, 0xA2, 0x32, 0xE1, 0x8A, 0x05, 0x75, 0xEB, 0xF6, 0xA4
	.byte 0x39, 0xEC, 0x83, 0x0B, 0xAA, 0xEF, 0x60, 0x40, 0x06, 0x9F, 0x71, 0x5E, 0x51, 0x10, 0x6E, 0xBD
	.byte 0xF9, 0x8A, 0x21, 0x3E, 0x3D, 0x06, 0xDD, 0x96, 0xAE, 0x05, 0x3E, 0xDD, 0x46, 0xBD, 0xE6, 0x4D
	.byte 0xB5, 0x8D, 0x54, 0x91, 0x05, 0x5D, 0xC4, 0x71, 0x6F, 0xD4, 0x06, 0x04, 0xFF, 0x15, 0x50, 0x60
	.byte 0x24, 0xFB, 0x98, 0x19, 0x97, 0xE9, 0xBD, 0xD6, 0xCC, 0x43, 0x40, 0x89, 0x77, 0x9E, 0xD9, 0x67
	.byte 0xBD, 0x42, 0xE8, 0xB0, 0x88, 0x8B, 0x89, 0x07, 0x38, 0x5B, 0x19, 0xE7, 0xDB, 0xEE, 0xC8, 0x79
	.byte 0x47, 0x0A, 0x7C, 0xA1, 0xE9, 0x0F, 0x42, 0x7C, 0xC9, 0x1E, 0x84, 0xF8, 0x00, 0x00, 0x00, 0x00
	.byte 0x83, 0x86, 0x80, 0x09, 0x48, 0xED, 0x2B, 0x32, 0xAC, 0x70, 0x11, 0x1E, 0x4E, 0x72, 0x5A, 0x6C
	.byte 0xFB, 0xFF, 0x0E, 0xFD, 0x56, 0x38, 0x85, 0x0F, 0x1E, 0xD5, 0xAE, 0x3D, 0x27, 0x39, 0x2D, 0x36
	.byte 0x64, 0xD9, 0x0F, 0x0A, 0x21, 0xA6, 0x5C, 0x68, 0xD1, 0x54, 0x5B, 0x9B, 0x3A, 0x2E, 0x36, 0x24
	.byte 0xB1, 0x67, 0x0A, 0x0C, 0x0F, 0xE7, 0x57, 0x93, 0xD2, 0x96, 0xEE, 0xB4, 0x9E, 0x91, 0x9B, 0x1B
	.byte 0x4F, 0xC5, 0xC0, 0x80, 0xA2, 0x20, 0xDC, 0x61, 0x69, 0x4B, 0x77, 0x5A, 0x16, 0x1A, 0x12, 0x1C
	.byte 0x0A, 0xBA, 0x93, 0xE2, 0xE5, 0x2A, 0xA0, 0xC0, 0x43, 0xE0, 0x22, 0x3C, 0x1D, 0x17, 0x1B, 0x12
	.byte 0x0B, 0x0D, 0x09, 0x0E, 0xAD, 0xC7, 0x8B, 0xF2, 0xB9, 0xA8, 0xB6, 0x2D, 0xC8, 0xA9, 0x1E, 0x14
	.byte 0x85, 0x19, 0xF1, 0x57, 0x4C, 0x07, 0x75, 0xAF, 0xBB, 0xDD, 0x99, 0xEE, 0xFD, 0x60, 0x7F, 0xA3
	.byte 0x9F, 0x26, 0x01, 0xF7, 0xBC, 0xF5, 0x72, 0x5C, 0xC5, 0x3B, 0x66, 0x44, 0x34, 0x7E, 0xFB, 0x5B
	.byte 0x76, 0x29, 0x43, 0x8B, 0xDC, 0xC6, 0x23, 0xCB, 0x68, 0xFC, 0xED, 0xB6, 0x63, 0xF1, 0xE4, 0xB8
	.byte 0xCA, 0xDC, 0x31, 0xD7, 0x10, 0x85, 0x63, 0x42, 0x40, 0x22, 0x97, 0x13, 0x20, 0x11, 0xC6, 0x84
	.byte 0x7D, 0x24, 0x4A, 0x85, 0xF8, 0x3D, 0xBB, 0xD2, 0x11, 0x32, 0xF9, 0xAE, 0x6D, 0xA1, 0x29, 0xC7
	.byte 0x4B, 0x2F, 0x9E, 0x1D, 0xF3, 0x30, 0xB2, 0xDC, 0xEC, 0x52, 0x86, 0x0D, 0xD0, 0xE3, 0xC1, 0x77
	.byte 0x6C, 0x16, 0xB3, 0x2B, 0x99, 0xB9, 0x70, 0xA9, 0xFA, 0x48, 0x94, 0x11, 0x22, 0x64, 0xE9, 0x47
	.byte 0xC4, 0x8C, 0xFC, 0xA8, 0x1A, 0x3F, 0xF0, 0xA0, 0xD8, 0x2C, 0x7D, 0x56, 0xEF, 0x90, 0x33, 0x22
	.byte 0xC7, 0x4E, 0x49, 0x87, 0xC1, 0xD1, 0x38, 0xD9, 0xFE, 0xA2, 0xCA, 0x8C, 0x36, 0x0B, 0xD4, 0x98
	.byte 0xCF, 0x81, 0xF5, 0xA6, 0x28, 0xDE, 0x7A, 0xA5, 0x26, 0x8E, 0xB7, 0xDA, 0xA4, 0xBF, 0xAD, 0x3F
	.byte 0xE4, 0x9D, 0x3A, 0x2C, 0x0D, 0x92, 0x78, 0x50, 0x9B, 0xCC, 0x5F, 0x6A, 0x62, 0x46, 0x7E, 0x54
	.byte 0xC2, 0x13, 0x8D, 0xF6, 0xE8, 0xB8, 0xD8, 0x90, 0x5E, 0xF7, 0x39, 0x2E, 0xF5, 0xAF, 0xC3, 0x82
	.byte 0xBE, 0x80, 0x5D, 0x9F, 0x7C, 0x93, 0xD0, 0x69, 0xA9, 0x2D, 0xD5, 0x6F, 0xB3, 0x12, 0x25, 0xCF
	.byte 0x3B, 0x99, 0xAC, 0xC8, 0xA7, 0x7D, 0x18, 0x10, 0x6E, 0x63, 0x9C, 0xE8, 0x7B, 0xBB, 0x3B, 0xDB
	.byte 0x09, 0x78, 0x26, 0xCD, 0xF4, 0x18, 0x59, 0x6E, 0x01, 0xB7, 0x9A, 0xEC, 0xA8, 0x9A, 0x4F, 0x83
	.byte 0x65, 0x6E, 0x95, 0xE6, 0x7E, 0xE6, 0xFF, 0xAA, 0x08, 0xCF, 0xBC, 0x21, 0xE6, 0xE8, 0x15, 0xEF
	.byte 0xD9, 0x9B, 0xE7, 0xBA, 0xCE, 0x36, 0x6F, 0x4A, 0xD4, 0x09, 0x9F, 0xEA, 0xD6, 0x7C, 0xB0, 0x29
	.byte 0xAF, 0xB2, 0xA4, 0x31, 0x31, 0x23, 0x3F, 0x2A, 0x30, 0x94, 0xA5, 0xC6, 0xC0, 0x66, 0xA2, 0x35
	.byte 0x37, 0xBC, 0x4E, 0x74, 0xA6, 0xCA, 0x82, 0xFC, 0xB0, 0xD0, 0x90, 0xE0, 0x15, 0xD8, 0xA7, 0x33
	.byte 0x4A, 0x98, 0x04, 0xF1, 0xF7, 0xDA, 0xEC, 0x41, 0x0E, 0x50, 0xCD, 0x7F, 0x2F, 0xF6, 0x91, 0x17
	.byte 0x8D, 0xD6, 0x4D, 0x76, 0x4D, 0xB0, 0xEF, 0x43, 0x54, 0x4D, 0xAA, 0xCC, 0xDF, 0x04, 0x96, 0xE4
	.byte 0xE3, 0xB5, 0xD1, 0x9E, 0x1B, 0x88, 0x6A, 0x4C, 0xB8, 0x1F, 0x2C, 0xC1, 0x7F, 0x51, 0x65, 0x46
	.byte 0x04, 0xEA, 0x5E, 0x9D, 0x5D, 0x35, 0x8C, 0x01, 0x73, 0x74, 0x87, 0xFA, 0x2E, 0x41, 0x0B, 0xFB
	.byte 0x5A, 0x1D, 0x67, 0xB3, 0x52, 0xD2, 0xDB, 0x92, 0x33, 0x56, 0x10, 0xE9, 0x13, 0x47, 0xD6, 0x6D
	.byte 0x8C, 0x61, 0xD7, 0x9A, 0x7A, 0x0C, 0xA1, 0x37, 0x8E, 0x14, 0xF8, 0x59, 0x89, 0x3C, 0x13, 0xEB
	.byte 0xEE, 0x27, 0xA9, 0xCE, 0x35, 0xC9, 0x61, 0xB7, 0xED, 0xE5, 0x1C, 0xE1, 0x3C, 0xB1, 0x47, 0x7A
	.byte 0x59, 0xDF, 0xD2, 0x9C, 0x3F, 0x73, 0xF2, 0x55, 0x79, 0xCE, 0x14, 0x18, 0xBF, 0x37, 0xC7, 0x73
	.byte 0xEA, 0xCD, 0xF7, 0x53, 0x5B, 0xAA, 0xFD, 0x5F, 0x14, 0x6F, 0x3D, 0xDF, 0x86, 0xDB, 0x44, 0x78
	.byte 0x81, 0xF3, 0xAF, 0xCA, 0x3E, 0xC4, 0x68, 0xB9, 0x2C, 0x34, 0x24, 0x38, 0x5F, 0x40, 0xA3, 0xC2
	.byte 0x72, 0xC3, 0x1D, 0x16, 0x0C, 0x25, 0xE2, 0xBC, 0x8B, 0x49, 0x3C, 0x28, 0x41, 0x95, 0x0D, 0xFF
	.byte 0x71, 0x01, 0xA8, 0x39, 0xDE, 0xB3, 0x0C, 0x08, 0x9C, 0xE4, 0xB4, 0xD8, 0x90, 0xC1, 0x56, 0x64
	.byte 0x61, 0x84, 0xCB, 0x7B, 0x70, 0xB6, 0x32, 0xD5, 0x74, 0x5C, 0x6C, 0x48, 0x42, 0x57, 0xB8, 0xD0

	.global MOD13_0223E86C
MOD13_0223E86C: ; 0x0223E86C
	.byte 0xA7, 0xF4, 0x51, 0x50, 0x65, 0x41, 0x7E, 0x53, 0xA4, 0x17, 0x1A, 0xC3, 0x5E, 0x27, 0x3A, 0x96
	.byte 0x6B, 0xAB, 0x3B, 0xCB, 0x45, 0x9D, 0x1F, 0xF1, 0x58, 0xFA, 0xAC, 0xAB, 0x03, 0xE3, 0x4B, 0x93
	.byte 0xFA, 0x30, 0x20, 0x55, 0x6D, 0x76, 0xAD, 0xF6, 0x76, 0xCC, 0x88, 0x91, 0x4C, 0x02, 0xF5, 0x25
	.byte 0xD7, 0xE5, 0x4F, 0xFC, 0xCB, 0x2A, 0xC5, 0xD7, 0x44, 0x35, 0x26, 0x80, 0xA3, 0x62, 0xB5, 0x8F
	.byte 0x5A, 0xB1, 0xDE, 0x49, 0x1B, 0xBA, 0x25, 0x67, 0x0E, 0xEA, 0x45, 0x98, 0xC0, 0xFE, 0x5D, 0xE1
	.byte 0x75, 0x2F, 0xC3, 0x02, 0xF0, 0x4C, 0x81, 0x12, 0x97, 0x46, 0x8D, 0xA3, 0xF9, 0xD3, 0x6B, 0xC6
	.byte 0x5F, 0x8F, 0x03, 0xE7, 0x9C, 0x92, 0x15, 0x95, 0x7A, 0x6D, 0xBF, 0xEB, 0x59, 0x52, 0x95, 0xDA
	.byte 0x83, 0xBE, 0xD4, 0x2D, 0x21, 0x74, 0x58, 0xD3, 0x69, 0xE0, 0x49, 0x29, 0xC8, 0xC9, 0x8E, 0x44
	.byte 0x89, 0xC2, 0x75, 0x6A, 0x79, 0x8E, 0xF4, 0x78, 0x3E, 0x58, 0x99, 0x6B, 0x71, 0xB9, 0x27, 0xDD
	.byte 0x4F, 0xE1, 0xBE, 0xB6, 0xAD, 0x88, 0xF0, 0x17, 0xAC, 0x20, 0xC9, 0x66, 0x3A, 0xCE, 0x7D, 0xB4
	.byte 0x4A, 0xDF, 0x63, 0x18, 0x31, 0x1A, 0xE5, 0x82, 0x33, 0x51, 0x97, 0x60, 0x7F, 0x53, 0x62, 0x45
	.byte 0x77, 0x64, 0xB1, 0xE0, 0xAE, 0x6B, 0xBB, 0x84, 0xA0, 0x81, 0xFE, 0x1C, 0x2B, 0x08, 0xF9, 0x94
	.byte 0x68, 0x48, 0x70, 0x58, 0xFD, 0x45, 0x8F, 0x19, 0x6C, 0xDE, 0x94, 0x87, 0xF8, 0x7B, 0x52, 0xB7
	.byte 0xD3, 0x73, 0xAB, 0x23, 0x02, 0x4B, 0x72, 0xE2, 0x8F, 0x1F, 0xE3, 0x57, 0xAB, 0x55, 0x66, 0x2A
	.byte 0x28, 0xEB, 0xB2, 0x07, 0xC2, 0xB5, 0x2F, 0x03, 0x7B, 0xC5, 0x86, 0x9A, 0x08, 0x37, 0xD3, 0xA5
	.byte 0x87, 0x28, 0x30, 0xF2, 0xA5, 0xBF, 0x23, 0xB2, 0x6A, 0x03, 0x02, 0xBA, 0x82, 0x16, 0xED, 0x5C
	.byte 0x1C, 0xCF, 0x8A, 0x2B, 0xB4, 0x79, 0xA7, 0x92, 0xF2, 0x07, 0xF3, 0xF0, 0xE2, 0x69, 0x4E, 0xA1
	.byte 0xF4, 0xDA, 0x65, 0xCD, 0xBE, 0x05, 0x06, 0xD5, 0x62, 0x34, 0xD1, 0x1F, 0xFE, 0xA6, 0xC4, 0x8A
	.byte 0x53, 0x2E, 0x34, 0x9D, 0x55, 0xF3, 0xA2, 0xA0, 0xE1, 0x8A, 0x05, 0x32, 0xEB, 0xF6, 0xA4, 0x75
	.byte 0xEC, 0x83, 0x0B, 0x39, 0xEF, 0x60, 0x40, 0xAA, 0x9F, 0x71, 0x5E, 0x06, 0x10, 0x6E, 0xBD, 0x51
	.byte 0x8A, 0x21, 0x3E, 0xF9, 0x06, 0xDD, 0x96, 0x3D, 0x05, 0x3E, 0xDD, 0xAE, 0xBD, 0xE6, 0x4D, 0x46
	.byte 0x8D, 0x54, 0x91, 0xB5, 0x5D, 0xC4, 0x71, 0x05, 0xD4, 0x06, 0x04, 0x6F, 0x15, 0x50, 0x60, 0xFF
	.byte 0xFB, 0x98, 0x19, 0x24, 0xE9, 0xBD, 0xD6, 0x97, 0x43, 0x40, 0x89, 0xCC, 0x9E, 0xD9, 0x67, 0x77
	.byte 0x42, 0xE8, 0xB0, 0xBD, 0x8B, 0x89, 0x07, 0x88, 0x5B, 0x19, 0xE7, 0x38, 0xEE, 0xC8, 0x79, 0xDB
	.byte 0x0A, 0x7C, 0xA1, 0x47, 0x0F, 0x42, 0x7C, 0xE9, 0x1E, 0x84, 0xF8, 0xC9, 0x00, 0x00, 0x00, 0x00
	.byte 0x86, 0x80, 0x09, 0x83, 0xED, 0x2B, 0x32, 0x48, 0x70, 0x11, 0x1E, 0xAC, 0x72, 0x5A, 0x6C, 0x4E
	.byte 0xFF, 0x0E, 0xFD, 0xFB, 0x38, 0x85, 0x0F, 0x56, 0xD5, 0xAE, 0x3D, 0x1E, 0x39, 0x2D, 0x36, 0x27
	.byte 0xD9, 0x0F, 0x0A, 0x64, 0xA6, 0x5C, 0x68, 0x21, 0x54, 0x5B, 0x9B, 0xD1, 0x2E, 0x36, 0x24, 0x3A
	.byte 0x67, 0x0A, 0x0C, 0xB1, 0xE7, 0x57, 0x93, 0x0F, 0x96, 0xEE, 0xB4, 0xD2, 0x91, 0x9B, 0x1B, 0x9E
	.byte 0xC5, 0xC0, 0x80, 0x4F, 0x20, 0xDC, 0x61, 0xA2, 0x4B, 0x77, 0x5A, 0x69, 0x1A, 0x12, 0x1C, 0x16
	.byte 0xBA, 0x93, 0xE2, 0x0A, 0x2A, 0xA0, 0xC0, 0xE5, 0xE0, 0x22, 0x3C, 0x43, 0x17, 0x1B, 0x12, 0x1D
	.byte 0x0D, 0x09, 0x0E, 0x0B, 0xC7, 0x8B, 0xF2, 0xAD, 0xA8, 0xB6, 0x2D, 0xB9, 0xA9, 0x1E, 0x14, 0xC8
	.byte 0x19, 0xF1, 0x57, 0x85, 0x07, 0x75, 0xAF, 0x4C, 0xDD, 0x99, 0xEE, 0xBB, 0x60, 0x7F, 0xA3, 0xFD
	.byte 0x26, 0x01, 0xF7, 0x9F, 0xF5, 0x72, 0x5C, 0xBC, 0x3B, 0x66, 0x44, 0xC5, 0x7E, 0xFB, 0x5B, 0x34
	.byte 0x29, 0x43, 0x8B, 0x76, 0xC6, 0x23, 0xCB, 0xDC, 0xFC, 0xED, 0xB6, 0x68, 0xF1, 0xE4, 0xB8, 0x63
	.byte 0xDC, 0x31, 0xD7, 0xCA, 0x85, 0x63, 0x42, 0x10, 0x22, 0x97, 0x13, 0x40, 0x11, 0xC6, 0x84, 0x20
	.byte 0x24, 0x4A, 0x85, 0x7D, 0x3D, 0xBB, 0xD2, 0xF8, 0x32, 0xF9, 0xAE, 0x11, 0xA1, 0x29, 0xC7, 0x6D
	.byte 0x2F, 0x9E, 0x1D, 0x4B, 0x30, 0xB2, 0xDC, 0xF3, 0x52, 0x86, 0x0D, 0xEC, 0xE3, 0xC1, 0x77, 0xD0
	.byte 0x16, 0xB3, 0x2B, 0x6C, 0xB9, 0x70, 0xA9, 0x99, 0x48, 0x94, 0x11, 0xFA, 0x64, 0xE9, 0x47, 0x22
	.byte 0x8C, 0xFC, 0xA8, 0xC4, 0x3F, 0xF0, 0xA0, 0x1A, 0x2C, 0x7D, 0x56, 0xD8, 0x90, 0x33, 0x22, 0xEF
	.byte 0x4E, 0x49, 0x87, 0xC7, 0xD1, 0x38, 0xD9, 0xC1, 0xA2, 0xCA, 0x8C, 0xFE, 0x0B, 0xD4, 0x98, 0x36
	.byte 0x81, 0xF5, 0xA6, 0xCF, 0xDE, 0x7A, 0xA5, 0x28, 0x8E, 0xB7, 0xDA, 0x26, 0xBF, 0xAD, 0x3F, 0xA4
	.byte 0x9D, 0x3A, 0x2C, 0xE4, 0x92, 0x78, 0x50, 0x0D, 0xCC, 0x5F, 0x6A, 0x9B, 0x46, 0x7E, 0x54, 0x62
	.byte 0x13, 0x8D, 0xF6, 0xC2, 0xB8, 0xD8, 0x90, 0xE8, 0xF7, 0x39, 0x2E, 0x5E, 0xAF, 0xC3, 0x82, 0xF5
	.byte 0x80, 0x5D, 0x9F, 0xBE, 0x93, 0xD0, 0x69, 0x7C, 0x2D, 0xD5, 0x6F, 0xA9, 0x12, 0x25, 0xCF, 0xB3
	.byte 0x99, 0xAC, 0xC8, 0x3B, 0x7D, 0x18, 0x10, 0xA7, 0x63, 0x9C, 0xE8, 0x6E, 0xBB, 0x3B, 0xDB, 0x7B
	.byte 0x78, 0x26, 0xCD, 0x09, 0x18, 0x59, 0x6E, 0xF4, 0xB7, 0x9A, 0xEC, 0x01, 0x9A, 0x4F, 0x83, 0xA8
	.byte 0x6E, 0x95, 0xE6, 0x65, 0xE6, 0xFF, 0xAA, 0x7E, 0xCF, 0xBC, 0x21, 0x08, 0xE8, 0x15, 0xEF, 0xE6
	.byte 0x9B, 0xE7, 0xBA, 0xD9, 0x36, 0x6F, 0x4A, 0xCE, 0x09, 0x9F, 0xEA, 0xD4, 0x7C, 0xB0, 0x29, 0xD6
	.byte 0xB2, 0xA4, 0x31, 0xAF, 0x23, 0x3F, 0x2A, 0x31, 0x94, 0xA5, 0xC6, 0x30, 0x66, 0xA2, 0x35, 0xC0
	.byte 0xBC, 0x4E, 0x74, 0x37, 0xCA, 0x82, 0xFC, 0xA6, 0xD0, 0x90, 0xE0, 0xB0, 0xD8, 0xA7, 0x33, 0x15
	.byte 0x98, 0x04, 0xF1, 0x4A, 0xDA, 0xEC, 0x41, 0xF7, 0x50, 0xCD, 0x7F, 0x0E, 0xF6, 0x91, 0x17, 0x2F
	.byte 0xD6, 0x4D, 0x76, 0x8D, 0xB0, 0xEF, 0x43, 0x4D, 0x4D, 0xAA, 0xCC, 0x54, 0x04, 0x96, 0xE4, 0xDF
	.byte 0xB5, 0xD1, 0x9E, 0xE3, 0x88, 0x6A, 0x4C, 0x1B, 0x1F, 0x2C, 0xC1, 0xB8, 0x51, 0x65, 0x46, 0x7F
	.byte 0xEA, 0x5E, 0x9D, 0x04, 0x35, 0x8C, 0x01, 0x5D, 0x74, 0x87, 0xFA, 0x73, 0x41, 0x0B, 0xFB, 0x2E
	.byte 0x1D, 0x67, 0xB3, 0x5A, 0xD2, 0xDB, 0x92, 0x52, 0x56, 0x10, 0xE9, 0x33, 0x47, 0xD6, 0x6D, 0x13
	.byte 0x61, 0xD7, 0x9A, 0x8C, 0x0C, 0xA1, 0x37, 0x7A, 0x14, 0xF8, 0x59, 0x8E, 0x3C, 0x13, 0xEB, 0x89
	.byte 0x27, 0xA9, 0xCE, 0xEE, 0xC9, 0x61, 0xB7, 0x35, 0xE5, 0x1C, 0xE1, 0xED, 0xB1, 0x47, 0x7A, 0x3C
	.byte 0xDF, 0xD2, 0x9C, 0x59, 0x73, 0xF2, 0x55, 0x3F, 0xCE, 0x14, 0x18, 0x79, 0x37, 0xC7, 0x73, 0xBF
	.byte 0xCD, 0xF7, 0x53, 0xEA, 0xAA, 0xFD, 0x5F, 0x5B, 0x6F, 0x3D, 0xDF, 0x14, 0xDB, 0x44, 0x78, 0x86
	.byte 0xF3, 0xAF, 0xCA, 0x81, 0xC4, 0x68, 0xB9, 0x3E, 0x34, 0x24, 0x38, 0x2C, 0x40, 0xA3, 0xC2, 0x5F
	.byte 0xC3, 0x1D, 0x16, 0x72, 0x25, 0xE2, 0xBC, 0x0C, 0x49, 0x3C, 0x28, 0x8B, 0x95, 0x0D, 0xFF, 0x41
	.byte 0x01, 0xA8, 0x39, 0x71, 0xB3, 0x0C, 0x08, 0xDE, 0xE4, 0xB4, 0xD8, 0x9C, 0xC1, 0x56, 0x64, 0x90
	.byte 0x84, 0xCB, 0x7B, 0x61, 0xB6, 0x32, 0xD5, 0x70, 0x5C, 0x6C, 0x48, 0x74, 0x57, 0xB8, 0xD0, 0x42

	.data
	.global MOD13_0223F7B8
MOD13_0223F7B8: ; 0x0223F7B8
	.byte 0x09, 0x08, 0x00, 0x00

	.global MOD13_0223F7BC
MOD13_0223F7BC: ; 0x0223F7BC
	.byte 0xFF, 0xFF, 0xFF, 0xFF

	.global MOD13_0223F7C0
MOD13_0223F7C0: ; 0x0223F7C0
	.byte 0xFF, 0xFF, 0xFF, 0xFF

	.global MOD13_0223F7C4
MOD13_0223F7C4: ; 0x0223F7C4
	.byte 0xFF, 0xFF, 0xFF, 0xFF

	.global MOD13_0223F7C8
MOD13_0223F7C8: ; 0x0223F7C8
	.byte 0x00, 0x00, 0x00, 0x01, 0xAD, 0x75, 0x21, 0x02, 0x95, 0x75, 0x21, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD13_0223F820
MOD13_0223F820: ; 0x0223F820
	.asciz "MELCO"

	.balign 4
	.global MOD13_0223F828
MOD13_0223F828: ; 0x0223F828
	.asciz "ESSID-AOSS"

	.balign 4
	.global MOD13_0223F834
MOD13_0223F834: ; 0x0223F834
	.byte 0x01, 0x00, 0x02, 0x00, 0x02, 0x00, 0x04, 0x00, 0x04, 0x00, 0x0B, 0x00, 0x08, 0x00, 0x0C, 0x00
	.byte 0x10, 0x00, 0x12, 0x00, 0x20, 0x00, 0x16, 0x00, 0x40, 0x00, 0x18, 0x00, 0x80, 0x00, 0x24, 0x00
	.byte 0x00, 0x01, 0x30, 0x00, 0x00, 0x02, 0x48, 0x00, 0x00, 0x04, 0x60, 0x00, 0x00, 0x08, 0x6C, 0x00

	.global MOD13_0223F864
MOD13_0223F864: ; 0x0223F864
	.byte 0xEC, 0x1F, 0x24, 0x02

	.global MOD13_0223F868
MOD13_0223F868: ; 0x0223F868
	.byte 0x01, 0x00, 0x00, 0x00

	.global MOD13_0223F86C
MOD13_0223F86C: ; 0x0223F86C
	.byte 0x00, 0x08, 0x00, 0x00

	.global MOD13_0223F870
MOD13_0223F870: ; 0x0223F870
	.byte 0xFF, 0xFF, 0xFF, 0xFF

	.global MOD13_0223F874
MOD13_0223F874: ; 0x0223F874
	.byte 0x40, 0x00, 0x00, 0x00

	.global MOD13_0223F878
MOD13_0223F878: ; 0x0223F878
	.asciz "******"

	.balign 4
	.global MOD13_0223F880
MOD13_0223F880: ; 0x0223F880
	.byte 0x06, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x4E, 0x49, 0x4E, 0x54, 0x45, 0x4E, 0x44, 0x4F
	.byte 0x2D, 0x44, 0x53, 0x00

	.global MOD13_0223F894
MOD13_0223F894: ; 0x0223F894
	.byte 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD13_0223F8D4
MOD13_0223F8D4: ; 0x0223F8D4
	.byte 0x00, 0x00, 0x00, 0x01, 0x09, 0xDD, 0x21, 0x02, 0xD9, 0xDC, 0x21, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0xC0, 0xA8, 0x00, 0xB0, 0xFF, 0xFF, 0xFF, 0x00, 0xC0, 0xA8, 0x00, 0xC8, 0xC0, 0xA8, 0x00, 0x20
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xF8, 0x23, 0x02, 0x04, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD13_0223F92C
MOD13_0223F92C: ; 0x0223F92C
	.asciz "WARP"

	.bss
	.global MOD13_02240B34
MOD13_02240B34: ; 0x02240B34
	.space 0x4

	.global MOD13_02240B38
MOD13_02240B38: ; 0x02240B38
	.space 0x4

	.global MOD13_02240B3C
MOD13_02240B3C: ; 0x02240B3C
	.space 0x4

	.global MOD13_02240B40
MOD13_02240B40: ; 0x02240B40
	.space 0x4

	.global MOD13_02240B44
MOD13_02240B44: ; 0x02240B44
	.space 0x4

	.global MOD13_02240B48
MOD13_02240B48: ; 0x02240B48
	.space 0x4

	.global MOD13_02240B4C
MOD13_02240B4C: ; 0x02240B4C
	.space 0x8

	.global MOD13_02240B54
MOD13_02240B54: ; 0x02240B54
	.space 0xC

	.global MOD13_02240B60
MOD13_02240B60: ; 0x02240B60
	.space 0x1C

	.global MOD13_02240B7C
MOD13_02240B7C: ; 0x02240B7C
	.space 0x2

	.global MOD13_02240B7E
MOD13_02240B7E: ; 0x02240B7E
	.space 0x62

	.global MOD13_02240BE0
MOD13_02240BE0: ; 0x02240BE0
	.space 0x280

	.global MOD13_02240E60
MOD13_02240E60: ; 0x02240E60
	.space 0x400

	.global MOD13_02241260
MOD13_02241260: ; 0x02241260
	.space 0x8

	.global MOD13_02241268
MOD13_02241268: ; 0x02241268
	.space 0x130

	.global MOD13_02241398
MOD13_02241398: ; 0x02241398
	.space 0x130

	.global MOD13_022414C8
MOD13_022414C8: ; 0x022414C8
	.space 0x70

	.global MOD13_02241538
MOD13_02241538: ; 0x02241538
	.space 0x3C8

	.global MOD13_02241900
MOD13_02241900: ; 0x02241900
	.space 0x4

	.global MOD13_02241904
MOD13_02241904: ; 0x02241904
	.space 0x4

	.global MOD13_02241908
MOD13_02241908: ; 0x02241908
	.space 0x4

	.global MOD13_0224190C
MOD13_0224190C: ; 0x0224190C
	.space 0x4

	.global MOD13_02241910
MOD13_02241910: ; 0x02241910
	.space 0x10

	.global MOD13_02241920
MOD13_02241920: ; 0x02241920
	.space 0x20

	.global MOD13_02241940
MOD13_02241940: ; 0x02241940
	.space 0x2

	.global MOD13_02241942
MOD13_02241942: ; 0x02241942
	.space 0x5E

	.global MOD13_022419A0
MOD13_022419A0: ; 0x022419A0
	.space 0xC0

	.global MOD13_02241A60
MOD13_02241A60: ; 0x02241A60
	.space 0x4

	.global MOD13_02241A64
MOD13_02241A64: ; 0x02241A64
	.space 0x4

	.global MOD13_02241A68
MOD13_02241A68: ; 0x02241A68
	.space 0x4

	.global MOD13_02241A6C
MOD13_02241A6C: ; 0x02241A6C
	.space 0x4

	.global MOD13_02241A70
MOD13_02241A70: ; 0x02241A70
	.space 0x4

	.global MOD13_02241A74
MOD13_02241A74: ; 0x02241A74
	.space 0x4

	.global MOD13_02241A78
MOD13_02241A78: ; 0x02241A78
	.space 0x4

	.global MOD13_02241A7C
MOD13_02241A7C: ; 0x02241A7C
	.space 0x4

	.global MOD13_02241A80
MOD13_02241A80: ; 0x02241A80
	.space 0x4

	.global MOD13_02241A84
MOD13_02241A84: ; 0x02241A84
	.space 0x4

	.global MOD13_02241A88
MOD13_02241A88: ; 0x02241A88
	.space 0x8

	.global MOD13_02241A90
MOD13_02241A90: ; 0x02241A90
	.space 0x20

	.global MOD13_02241AB0
MOD13_02241AB0: ; 0x02241AB0
	.space 0x4

	.global MOD13_02241AB4
MOD13_02241AB4: ; 0x02241AB4
	.space 0x4

	.global MOD13_02241AB8
MOD13_02241AB8: ; 0x02241AB8
	.space 0x4

	.global MOD13_02241ABC
MOD13_02241ABC: ; 0x02241ABC
	.space 0x4

	.global MOD13_02241AC0
MOD13_02241AC0: ; 0x02241AC0
	.space 0x4

	.global MOD13_02241AC4
MOD13_02241AC4: ; 0x02241AC4
	.space 0x4

	.global MOD13_02241AC8
MOD13_02241AC8: ; 0x02241AC8
	.space 0x4

	.global MOD13_02241ACC
MOD13_02241ACC: ; 0x02241ACC
	.space 0x4

	.global MOD13_02241AD0
MOD13_02241AD0: ; 0x02241AD0
	.space 0x4

	.global MOD13_02241AD4
MOD13_02241AD4: ; 0x02241AD4
	.space 0x4

	.global MOD13_02241AD8
MOD13_02241AD8: ; 0x02241AD8
	.space 0x4

	.global MOD13_02241ADC
MOD13_02241ADC: ; 0x02241ADC
	.space 0x4

	.global MOD13_02241AE0
MOD13_02241AE0: ; 0x02241AE0
	.space 0x4

	.global MOD13_02241AE4
MOD13_02241AE4: ; 0x02241AE4
	.space 0x4

	.global MOD13_02241AE8
MOD13_02241AE8: ; 0x02241AE8
	.space 0x4

	.global MOD13_02241AEC
MOD13_02241AEC: ; 0x02241AEC
	.space 0x4

	.global MOD13_02241AF0
MOD13_02241AF0: ; 0x02241AF0
	.space 0x4

	.global MOD13_02241AF4
MOD13_02241AF4: ; 0x02241AF4
	.space 0x4

	.global MOD13_02241AF8
MOD13_02241AF8: ; 0x02241AF8
	.space 0x4

	.global MOD13_02241AFC
MOD13_02241AFC: ; 0x02241AFC
	.space 0x4

	.global MOD13_02241B00
MOD13_02241B00: ; 0x02241B00
	.space 0x4

	.global MOD13_02241B04
MOD13_02241B04: ; 0x02241B04
	.space 0x4

	.global MOD13_02241B08
MOD13_02241B08: ; 0x02241B08
	.space 0x4

	.global MOD13_02241B0C
MOD13_02241B0C: ; 0x02241B0C
	.space 0x4

	.global MOD13_02241B10
MOD13_02241B10: ; 0x02241B10
	.space 0x4

	.global MOD13_02241B14
MOD13_02241B14: ; 0x02241B14
	.space 0x4

	.global MOD13_02241B18
MOD13_02241B18: ; 0x02241B18
	.space 0x4

	.global MOD13_02241B1C
MOD13_02241B1C: ; 0x02241B1C
	.space 0x4

	.global MOD13_02241B20
MOD13_02241B20: ; 0x02241B20
	.space 0x4

	.global MOD13_02241B24
MOD13_02241B24: ; 0x02241B24
	.space 0x4

	.global MOD13_02241B28
MOD13_02241B28: ; 0x02241B28
	.space 0x4

	.global MOD13_02241B2C
MOD13_02241B2C: ; 0x02241B2C
	.space 0x4

	.global MOD13_02241B30
MOD13_02241B30: ; 0x02241B30
	.space 0x4

	.global MOD13_02241B34
MOD13_02241B34: ; 0x02241B34
	.space 0x8

	.global MOD13_02241B3C
MOD13_02241B3C: ; 0x02241B3C
	.space 0x8

	.global MOD13_02241B44
MOD13_02241B44: ; 0x02241B44
	.space 0x8

	.global MOD13_02241B4C
MOD13_02241B4C: ; 0x02241B4C
	.space 0x10

	.global MOD13_02241B5C
MOD13_02241B5C: ; 0x02241B5C
	.space 0x10

	.global MOD13_02241B6C
MOD13_02241B6C: ; 0x02241B6C
	.space 0x18

	.global MOD13_02241B84
MOD13_02241B84: ; 0x02241B84
	.space 0x8

	.global MOD13_02241B8C
MOD13_02241B8C: ; 0x02241B8C
	.space 0x18

	.global MOD13_02241BA4
MOD13_02241BA4: ; 0x02241BA4
	.space 0x20

	.global MOD13_02241BC4
MOD13_02241BC4: ; 0x02241BC4
	.space 0x24

	.global MOD13_02241BE8
MOD13_02241BE8: ; 0x02241BE8
	.space 0xC0

	.global MOD13_02241CA8
MOD13_02241CA8: ; 0x02241CA8
	.space 0x28

	.global MOD13_02241CD0
MOD13_02241CD0: ; 0x02241CD0
	.space 0x80

	.global MOD13_02241D50
MOD13_02241D50: ; 0x02241D50
	.space 0x40

	.global MOD13_02241D90
MOD13_02241D90: ; 0x02241D90
	.space 0x100

	.global MOD13_02241E90
MOD13_02241E90: ; 0x02241E90
	.space 0x64

	.global MOD13_02241EF4
MOD13_02241EF4: ; 0x02241EF4
	.space 0x98

	.global MOD13_02241F8C
MOD13_02241F8C: ; 0x02241F8C
	.space 0x58

	.global MOD13_02241FE4
MOD13_02241FE4: ; 0x02241FE4
	.space 0x800

	.global MOD13_022427E4
MOD13_022427E4: ; 0x022427E4
	.space 0x800

