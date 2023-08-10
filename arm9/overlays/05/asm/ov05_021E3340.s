	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021E3340
ov05_021E3340: ; 0x021E3340
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r4, r0, #0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0
	add r0, r4, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #4
	bhi _021E3414
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021E3366: ; jump table
	.short _021E3370 - _021E3366 - 2 ; case 0
	.short _021E3388 - _021E3366 - 2 ; case 1
	.short _021E33A0 - _021E3366 - 2 ; case 2
	.short _021E33E4 - _021E3366 - 2 ; case 3
	.short _021E33FE - _021E3366 - 2 ; case 4
_021E3370:
	mov r0, #2
	add r1, r0, #0
	str r0, [sp]
	sub r1, #0x12
	mov r2, #0
	mov r3, #0x3f
	bl StartBrightnessTransition
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E3414
_021E3388:
	mov r0, #2
	bl IsBrightnessTransitionActive
	cmp r0, #0
	beq _021E3414
	ldr r0, [r5, #8]
	bl ov19_022524F4
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E3414
_021E33A0:
	ldr r0, [r5, #8]
	bl ov19_02252504
	cmp r0, #0
	beq _021E3414
	ldr r0, [r5, #0xc]
	bl Save_Poketch_Get
	add r6, r0, #0
	ldr r0, _021E341C ; =SDK_OVERLAY_OVERLAY_19_ID
	bl UnloadOverlayByID
	ldr r0, _021E3420 ; =SDK_OVERLAY_OVERLAY_20_ID
	mov r1, #2
	bl HandleLoadOverlay
	add r0, r6, #0
	bl Save_Poketch_Give
	mov r0, #1
	bl GetOamManager
	str r0, [sp]
	ldr r1, [r5, #4]
	ldr r2, [r5, #0xc]
	ldr r3, [r5, #8]
	add r0, r5, #0
	add r1, #0x14
	bl ov20_02252448
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E3414
_021E33E4:
	mov r1, #0
	mov r0, #2
	add r2, r1, #0
	str r0, [sp]
	mov r0, #4
	sub r2, #0x10
	mov r3, #0x3f
	bl StartBrightnessTransition
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E3414
_021E33FE:
	mov r0, #2
	bl IsBrightnessTransitionActive
	cmp r0, #0
	beq _021E3414
	add r0, r4, #0
	bl FreeToHeap
	add sp, #4
	mov r0, #1
	pop {r3, r4, r5, r6, pc}
_021E3414:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_021E341C: .word SDK_OVERLAY_OVERLAY_19_ID
_021E3420: .word SDK_OVERLAY_OVERLAY_20_ID

	thumb_func_start Field_GivePoketch
Field_GivePoketch: ; 0x021E3424
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xb
	mov r1, #4
	bl AllocFromHeapAtEnd
	add r2, r0, #0
	mov r0, #0
	str r0, [r2]
	ldr r1, _021E3440 ; =ov05_021E3340
	add r0, r4, #0
	bl TaskManager_Call
	pop {r4, pc}
	.balign 4, 0
_021E3440: .word ov05_021E3340
