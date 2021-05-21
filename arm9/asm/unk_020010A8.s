    .include "asm/macros.inc"
    .include "global.inc"

	.extern gMain
	.extern ListMenuPrint
	.extern ListMenuPrintEntries
	.extern ListMenuDrawCursor
	.extern ListMenuErasePrintedCursor
	.extern ListMenuUpdateSelectedRowIndexAndScrollOffset

	.text

	thumb_func_start FUN_0200198C
FUN_0200198C: ; 0x0200198C
	push {r3-r7, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	ldrh r0, [r5, #0x12]
	add r4, r1, #0x0
	add r7, r2, #0x0
	cmp r4, r0
	blt _020019B8
	ldrb r1, [r5, #0x18]
	ldr r0, [r5, #0xc]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	bl FillWindowPixelBuffer
	ldrh r1, [r5, #0x2c]
	ldrh r3, [r5, #0x12]
	add r0, r5, #0x0
	mov r2, #0x0
	bl ListMenuPrintEntries
	add sp, #0x8
	pop {r3-r7, pc}
_020019B8:
	ldrh r0, [r5, #0x1a]
	mov r1, #0x1
	lsl r0, r0, #0x11
	lsr r0, r0, #0x1a
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl GetFontAttribute
	ldrh r1, [r5, #0x1a]
	lsl r1, r1, #0x19
	lsr r1, r1, #0x1c
	add r0, r1, r0
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	cmp r7, #0x0
	ldrb r0, [r5, #0x18]
	bne _02001A46
	lsl r0, r0, #0x1c
	lsr r7, r0, #0x1c
	add r2, r4, #0x0
	lsl r3, r7, #0x4
	mul r2, r6
	orr r3, r7
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r5, #0xc]
	mov r1, #0x1
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_0201A8C8
	ldrh r1, [r5, #0x2c]
	add r0, r5, #0x0
	mov r2, #0x0
	add r3, r4, #0x0
	bl ListMenuPrintEntries
	ldrb r0, [r5, #0x17]
	lsl r0, r0, #0x1c
	lsr r2, r0, #0x1c
	ldrh r0, [r5, #0x12]
	add r1, r0, #0x0
	mul r1, r6
	add r0, r2, r1
	lsl r0, r0, #0x10
	lsr r4, r0, #0x10
	ldr r0, [r5, #0xc]
	bl FUN_0201AB0C
	add r6, r0, #0x0
	ldr r0, [r5, #0xc]
	bl FUN_0201AB10
	lsl r0, r0, #0x3
	lsl r1, r6, #0x13
	sub r0, r0, r4
	lsr r1, r1, #0x10
	lsl r0, r0, #0x10
	str r1, [sp, #0x0]
	lsr r0, r0, #0x10
	str r0, [sp, #0x4]
	ldrb r1, [r5, #0x18]
	ldr r0, [r5, #0xc]
	mov r2, #0x0
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	add r3, r4, #0x0
	bl FillWindowPixelRect
	add sp, #0x8
	pop {r3-r7, pc}
_02001A46:
	lsl r0, r0, #0x1c
	lsr r3, r0, #0x1c
	add r2, r4, #0x0
	mul r2, r6
	lsl r6, r3, #0x4
	orr r3, r6
	lsl r2, r2, #0x18
	lsl r3, r3, #0x18
	ldr r0, [r5, #0xc]
	mov r1, #0x0
	lsr r2, r2, #0x18
	lsr r3, r3, #0x18
	bl FUN_0201A8C8
	ldrh r0, [r5, #0x12]
	ldrh r1, [r5, #0x2c]
	add r3, r4, #0x0
	sub r2, r0, r4
	add r1, r1, r2
	lsl r1, r1, #0x10
	lsl r2, r2, #0x10
	add r0, r5, #0x0
	lsr r1, r1, #0x10
	lsr r2, r2, #0x10
	bl ListMenuPrintEntries
	ldr r0, [r5, #0xc]
	bl FUN_0201AB0C
	lsl r0, r0, #0x13
	lsr r0, r0, #0x10
	str r0, [sp, #0x0]
	ldrb r0, [r5, #0x17]
	mov r2, #0x0
	add r3, r2, #0x0
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	str r0, [sp, #0x4]
	ldrb r1, [r5, #0x18]
	ldr r0, [r5, #0xc]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	bl FillWindowPixelRect
	add sp, #0x8
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start ListMenuChangeSelection
ListMenuChangeSelection: ; 0x02001AA4
	push {r3-r7, lr}
	sub sp, #0x10
	str r1, [sp, #0x0]
	str r2, [sp, #0x4]
	add r4, r0, #0x0
	str r3, [sp, #0x8]
	ldrh r0, [r4, #0x2e]
	mov r6, #0x0
	add r5, r6, #0x0
	str r0, [sp, #0xc]
	ldr r0, [sp, #0x4]
	add r7, r6, #0x0
	cmp r0, #0x0
	bls _02001AF6
_02001AC0:
	ldr r1, [sp, #0x8]
	add r0, r4, #0x0
	bl ListMenuUpdateSelectedRowIndexAndScrollOffset
	orr r5, r0
	cmp r0, #0x2
	bne _02001AEA
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
	ldrh r1, [r4, #0x2c]
	ldrh r0, [r4, #0x2e]
	ldr r2, [r4, #0x0]
	add r0, r1, r0
	lsl r0, r0, #0x3
	add r0, r2, r0
	ldr r1, [r0, #0x4]
	mov r0, #0x2
	mvn r0, r0
	cmp r1, r0
	beq _02001AC0
_02001AEA:
	add r0, r7, #0x1
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	ldr r0, [sp, #0x4]
	cmp r7, r0
	blo _02001AC0
_02001AF6:
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	beq _02001B5E
	cmp r5, #0x3
	bhi _02001B14
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02001B0C: ; jump table (using 16-bit offset)
	.short _02001B14 - _02001B0C - 2; case 0
	.short _02001B1A - _02001B0C - 2; case 1
	.short _02001B38 - _02001B0C - 2; case 2
	.short _02001B38 - _02001B0C - 2; case 3
_02001B14:
	add sp, #0x10
	mov r0, #0x1
	pop {r3-r7, pc}
_02001B1A:
	ldr r1, [sp, #0xc]
	add r0, r4, #0x0
	bl ListMenuErasePrintedCursor
	add r0, r4, #0x0
	bl ListMenuDrawCursor
	add r0, r4, #0x0
	mov r1, #0x0
	bl ListMenuCallSelectionChangedCallback
	ldr r0, [r4, #0xc]
	bl CopyWindowToVram
	b _02001B5E
_02001B38:
	ldr r1, [sp, #0xc]
	add r0, r4, #0x0
	bl ListMenuErasePrintedCursor
	ldr r2, [sp, #0x8]
	add r0, r4, #0x0
	add r1, r6, #0x0
	bl FUN_0200198C
	add r0, r4, #0x0
	bl ListMenuDrawCursor
	add r0, r4, #0x0
	mov r1, #0x0
	bl ListMenuCallSelectionChangedCallback
	ldr r0, [r4, #0xc]
	bl CopyWindowToVram
_02001B5E:
	mov r0, #0x0
	add sp, #0x10
	pop {r3-r7, pc}

	thumb_func_start ListMenuCallSelectionChangedCallback
ListMenuCallSelectionChangedCallback: ; 0x02001B64
	push {r3-r5, lr}
	ldr r3, [r0, #0x4]
	add r2, r1, #0x0
	cmp r3, #0x0
	beq _02001B7E
	ldrh r5, [r0, #0x2c]
	ldrh r4, [r0, #0x2e]
	ldr r1, [r0, #0x0]
	add r4, r5, r4
	lsl r4, r4, #0x3
	add r1, r1, r4
	ldr r1, [r1, #0x4]
	blx r3
_02001B7E:
	pop {r3-r5, pc}
