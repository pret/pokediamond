	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020FD6F4
UNK_020FD6F4: ; 0x020FD6F4
	.byte 0x04, 0xFF, 0x00, 0x00

	.global UNK_020FD6F8
UNK_020FD6F8: ; 0x020FD6F8
	.word MOD75_021E6BA0, MOD75_021E6D6C, MOD75_021E6F00, SDK_OVERLAY_MODULE_75_ID

	.global UNK_020FD708
UNK_020FD708: ; 0x020FD708
	.word MOD73_021D74F0, MOD73_021D758C, MOD73_021D7640, SDK_OVERLAY_MODULE_73_ID

	.global UNK_020FD718
UNK_020FD718: ; 0x020FD718
	.word MOD68_021D74E0, MOD68_021D75D8, MOD68_021D762C, SDK_OVERLAY_MODULE_68_ID

	.text

	thumb_func_start FUN_02088AAC
FUN_02088AAC: ; 0x02088AAC
	push {r4, lr}
	add r4, r1, #0x0
	ldr r1, [r4, #0x0]
	cmp r1, #0x5
	bhi _02088AF6
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #0x6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_02088AC2: ; jump table (using 16-bit offset)
	.short _02088ACE - _02088AC2 - 2; case 0
	.short _02088AD6 - _02088AC2 - 2; case 1
	.short _02088ADE - _02088AC2 - 2; case 2
	.short _02088AE6 - _02088AC2 - 2; case 3
	.short _02088AEE - _02088AC2 - 2; case 4
	.short _02088AF2 - _02088AC2 - 2; case 5
_02088ACE:
	bl FUN_02088B4C
	str r0, [r4, #0x0]
	b _02088AF6
_02088AD6:
	bl FUN_02088BA8
	str r0, [r4, #0x0]
	b _02088AF6
_02088ADE:
	bl FUN_02088C3C
	str r0, [r4, #0x0]
	b _02088AF6
_02088AE6:
	bl FUN_02088CDC
	str r0, [r4, #0x0]
	b _02088AF6
_02088AEE:
	mov r0, #0x1
	pop {r4, pc}
_02088AF2:
	mov r0, #0x4
	pop {r4, pc}
_02088AF6:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02088AFC
FUN_02088AFC: ; 0x02088AFC
	push {r3-r5, lr}
	sub sp, #0x10
	ldr r5, _02088B24 ; =UNK_020FD708
	add r3, sp, #0x0
	add r4, r0, #0x0
	add r2, r3, #0x0
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	ldmia r5!, {r0-r1}
	stmia r3!, {r0-r1}
	add r0, r2, #0x0
	ldr r2, [r4, #0x0]
	add r1, r4, #0x0
	bl OverlayManager_new
	str r0, [r4, #0x1c]
	mov r0, #0x2
	add sp, #0x10
	pop {r3-r5, pc}
	nop
_02088B24: .word UNK_020FD708

	thumb_func_start FUN_02088B28
FUN_02088B28: ; 0x02088B28
	push {r4, lr}
	add r4, r0, #0x0
	add r0, #0x1c
	bl FUN_0208898C
	cmp r0, #0x0
	bne _02088B3A
	mov r0, #0x2
	pop {r4, pc}
_02088B3A:
	ldr r0, [r4, #0x20]
	cmp r0, #0x1
	bne _02088B44
	mov r0, #0x0
	pop {r4, pc}
_02088B44:
	mov r0, #0x3
	pop {r4, pc}

	thumb_func_start FUN_02088B48
FUN_02088B48: ; 0x02088B48
	mov r0, #0x4
	bx lr

	thumb_func_start FUN_02088B4C
FUN_02088B4C: ; 0x02088B4C
	push {r3-r5, lr}
	sub sp, #0x10
	ldr r3, _02088BA0 ; =UNK_020FD6F8
	add r2, sp, #0x0
	add r5, r0, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r5, #0x10]
	ldr r1, _02088BA4 ; =UNK_020FD6F4
	ldr r0, [r0, #0x14]
	ldr r2, [r5, #0x0]
	bl CreateBagView
	add r4, r0, #0x0
	ldrh r0, [r5, #0x6]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	cmp r0, #0x1
	bne _02088B7A
	mov r2, #0x5
	b _02088B7C
_02088B7A:
	mov r2, #0x4
_02088B7C:
	ldr r1, [r5, #0x10]
	lsl r2, r2, #0x18
	ldr r1, [r1, #0xc]
	ldr r3, [r5, #0xc]
	add r0, r4, #0x0
	lsr r2, r2, #0x18
	bl FUN_0206E314
	ldr r2, [r5, #0x0]
	add r0, sp, #0x0
	add r1, r4, #0x0
	bl OverlayManager_new
	str r0, [r5, #0x1c]
	str r4, [r5, #0x18]
	mov r0, #0x1
	add sp, #0x10
	pop {r3-r5, pc}
	.balign 4
_02088BA0: .word UNK_020FD6F8
_02088BA4: .word UNK_020FD6F4

	thumb_func_start FUN_02088BA8
FUN_02088BA8: ; 0x02088BA8
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, #0x1c
	bl FUN_0208898C
	cmp r0, #0x0
	bne _02088BBA
	mov r0, #0x1
	pop {r3-r5, pc}
_02088BBA:
	ldr r0, [r4, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl BagView_New
	add r5, r0, #0x0
	bl BagView_sizeof
	add r2, r0, #0x0
	ldr r1, [r4, #0x18]
	add r0, r5, #0x0
	bl memcpy
	ldr r0, [r4, #0x18]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x18]
	add r0, r5, #0x0
	bl FUN_0206E37C
	str r0, [r4, #0x8]
	add r0, r5, #0x0
	bl FreeToHeap
	add r0, r5, #0x0
	bl FUN_0206E384
	cmp r0, #0x5
	bhi _02088C16
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02088C02: ; jump table (using 16-bit offset)
	.short _02088C1E - _02088C02 - 2; case 0
	.short _02088C0E - _02088C02 - 2; case 1
	.short _02088C1E - _02088C02 - 2; case 2
	.short _02088C1E - _02088C02 - 2; case 3
	.short _02088C1E - _02088C02 - 2; case 4
	.short _02088C12 - _02088C02 - 2; case 5
_02088C0E:
	mov r0, #0x2
	pop {r3-r5, pc}
_02088C12:
	mov r0, #0x5
	pop {r3-r5, pc}
_02088C16:
	bl GF_AssertFail
	mov r0, #0x95
	str r0, [r4, #0x8]
_02088C1E:
	ldr r0, [r4, #0x10]
	ldr r1, [r4, #0x8]
	ldr r0, [r0, #0x14]
	lsl r1, r1, #0x10
	ldr r3, [r4, #0x0]
	lsr r1, r1, #0x10
	mov r2, #0x1
	bl Bag_TakeItem
	cmp r0, #0x0
	bne _02088C38
	bl GF_AssertFail
_02088C38:
	mov r0, #0x4
	pop {r3-r5, pc}

	thumb_func_start FUN_02088C3C
FUN_02088C3C: ; 0x02088C3C
	push {r3-r7, lr}
	sub sp, #0x18
	add r5, r0, #0x0
	ldr r0, [r5, #0x10]
	ldr r3, _02088CD8 ; =UNK_020FD718
	ldr r0, [r0, #0x14]
	add r2, sp, #0x8
	str r0, [sp, #0x0]
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldr r0, [r5, #0x0]
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	bl FUN_020851B8
	str r0, [r5, #0x18]
	ldr r1, [r5, #0x8]
	mov r2, #0x1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	bl FUN_020851DC
	mov r6, #0x0
	add r4, r6, #0x0
_02088C70:
	add r0, r4, #0x0
	bl BerryToItemId
	lsl r0, r0, #0x18
	lsr r7, r0, #0x18
	ldr r0, [sp, #0x0]
	ldr r3, [r5, #0x0]
	add r1, r7, #0x0
	mov r2, #0x1
	bl Bag_HasItem
	cmp r0, #0x1
	bne _02088C9A
	ldr r0, [r5, #0x18]
	add r1, r7, #0x0
	mov r2, #0x0
	bl FUN_020851DC
	add r0, r6, #0x1
	lsl r0, r0, #0x18
	lsr r6, r0, #0x18
_02088C9A:
	add r0, r4, #0x1
	lsl r0, r0, #0x18
	lsr r4, r0, #0x18
	cmp r4, #0x40
	blo _02088C70
	add r3, sp, #0x4
	ldr r0, [r5, #0xc]
	mov r1, #0x4
	add r2, sp, #0x4
	add r3, #0x1
	bl FUN_0206F17C
	add r2, sp, #0x4
	ldrb r1, [r2, #0x1]
	add r3, r6, #0x2
	lsl r3, r3, #0x18
	ldrb r2, [r2, #0x0]
	ldr r0, [r5, #0x18]
	lsr r3, r3, #0x18
	bl FUN_020851F8
	ldr r1, [r5, #0x18]
	ldr r2, [r5, #0x0]
	add r0, sp, #0x8
	bl OverlayManager_new
	str r0, [r5, #0x1c]
	mov r0, #0x3
	add sp, #0x18
	pop {r3-r7, pc}
	nop
_02088CD8: .word UNK_020FD718

	thumb_func_start FUN_02088CDC
FUN_02088CDC: ; 0x02088CDC
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	add r0, #0x1c
	bl FUN_0208898C
	cmp r0, #0x0
	bne _02088CF2
	add sp, #0x4
	mov r0, #0x3
	pop {r3-r4, pc}
_02088CF2:
	add r1, sp, #0x0
	ldr r0, [r4, #0x18]
	add r1, #0x1
	add r2, sp, #0x0
	bl FUN_0208524C
	add r3, sp, #0x0
	ldrb r2, [r3, #0x0]
	ldrb r3, [r3, #0x1]
	ldr r0, [r4, #0xc]
	mov r1, #0x4
	bl FUN_0206F190
	ldr r0, [r4, #0x18]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x18]
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
