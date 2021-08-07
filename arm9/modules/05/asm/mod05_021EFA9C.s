	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD05_021EFA9C
MOD05_021EFA9C: ; 0x021EFA9C
	push {r3, lr}
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x14]
	cmp r0, #0
	beq _021EFAAA
	bl MOD20_022524DC
_021EFAAA:
	pop {r3, pc}

	thumb_func_start MOD05_021EFAAC
MOD05_021EFAAC: ; 0x021EFAAC
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	bl Sav2_Poketch_get
	add r4, r0, #0
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	add r6, r0, #0
	add r0, r4, #0
	bl Sav2_Poketch_IsGiven
	cmp r0, #0
	beq _021EFAF8
	add r0, r6, #0
	bl FUN_0205F1E4
	cmp r0, #0
	bne _021EFAF8
	ldr r0, _021EFB0C ; =SDK_OVERLAY_MODULE_20_ID
	mov r1, #2
	bl HandleLoadOverlay
	mov r0, #1
	bl FUN_0200A03C
	str r0, [sp]
	ldr r1, [r5, #4]
	ldr r2, [r5, #0xc]
	ldr r3, [r5, #8]
	add r0, r5, #0
	add r1, #0x14
	bl MOD20_02252448
	add sp, #4
	pop {r3, r4, r5, r6, pc}
_021EFAF8:
	ldr r0, _021EFB10 ; =SDK_OVERLAY_MODULE_19_ID
	mov r1, #2
	bl HandleLoadOverlay
	ldr r0, [r5, #8]
	bl MOD19_02252440
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_021EFB0C: .word SDK_OVERLAY_MODULE_20_ID
_021EFB10: .word SDK_OVERLAY_MODULE_19_ID

	thumb_func_start MOD05_021EFB14
MOD05_021EFB14: ; 0x021EFB14
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	bl Sav2_Poketch_get
	add r4, r0, #0
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	add r6, r0, #0
	add r0, r4, #0
	bl Sav2_Poketch_IsGiven
	cmp r0, #0
	beq _021EFB46
	add r0, r6, #0
	bl FUN_0205F1E4
	cmp r0, #0
	bne _021EFB46
	ldr r0, [r5, #4]
	ldr r0, [r0, #0x14]
	bl MOD20_022524BC
	pop {r4, r5, r6, pc}
_021EFB46:
	ldr r0, [r5, #8]
	bl MOD19_022524F4
	pop {r4, r5, r6, pc}
	.balign 4, 0

	thumb_func_start MOD05_021EFB50
MOD05_021EFB50: ; 0x021EFB50
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0xc]
	bl Sav2_Poketch_get
	add r4, r0, #0
	ldr r0, [r5, #0xc]
	bl SavArray_Flags_get
	add r6, r0, #0
	add r0, r4, #0
	bl Sav2_Poketch_IsGiven
	cmp r0, #0
	beq _021EFB94
	add r0, r6, #0
	bl FUN_0205F1E4
	cmp r0, #0
	bne _021EFB94
	ldr r0, [r5, #4]
	ldr r0, [r0, #0x14]
	bl MOD20_022524D0
	cmp r0, #0
	beq _021EFBA8
	ldr r0, [r5, #4]
	mov r1, #0
	str r1, [r0, #0x14]
	ldr r0, _021EFBAC ; =SDK_OVERLAY_MODULE_20_ID
	bl UnloadOverlayByID
	mov r0, #1
	pop {r4, r5, r6, pc}
_021EFB94:
	ldr r0, [r5, #8]
	bl MOD19_02252504
	cmp r0, #0
	beq _021EFBA8
	ldr r0, _021EFBB0 ; =SDK_OVERLAY_MODULE_19_ID
	bl UnloadOverlayByID
	mov r0, #1
	pop {r4, r5, r6, pc}
_021EFBA8:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021EFBAC: .word SDK_OVERLAY_MODULE_20_ID
_021EFBB0: .word SDK_OVERLAY_MODULE_19_ID

	thumb_func_start MOD05_021EFBB4
MOD05_021EFBB4: ; 0x021EFBB4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021EFBC8 ; =SDK_OVERLAY_MODULE_19_ID
	mov r1, #2
	bl HandleLoadOverlay
	ldr r0, [r4, #8]
	bl MOD19_02252440
	pop {r4, pc}
	.balign 4, 0
_021EFBC8: .word SDK_OVERLAY_MODULE_19_ID

	thumb_func_start MOD05_021EFBCC
MOD05_021EFBCC: ; 0x021EFBCC
	ldr r3, _021EFBD4 ; =MOD19_022524F4
	ldr r0, [r0, #8]
	bx r3
	nop
_021EFBD4: .word MOD19_022524F4

	thumb_func_start MOD05_021EFBD8
MOD05_021EFBD8: ; 0x021EFBD8
	push {r3, lr}
	ldr r0, [r0, #8]
	bl MOD19_02252504
	cmp r0, #0
	beq _021EFBEE
	ldr r0, _021EFBF4 ; =SDK_OVERLAY_MODULE_19_ID
	bl UnloadOverlayByID
	mov r0, #1
	pop {r3, pc}
_021EFBEE:
	mov r0, #0
	pop {r3, pc}
	nop
_021EFBF4: .word SDK_OVERLAY_MODULE_19_ID
