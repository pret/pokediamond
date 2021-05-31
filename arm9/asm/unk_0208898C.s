    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0208898C
FUN_0208898C: ; 0x0208898C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020889AC
	bl OverlayManager_Run
	cmp r0, #0x0
	beq _020889AC
	ldr r0, [r4, #0x0]
	bl OverlayManager_delete
	mov r0, #0x0
	str r0, [r4, #0x0]
	mov r0, #0x1
	pop {r4, pc}
_020889AC:
	mov r0, #0x0
	pop {r4, pc}

	thumb_func_start FUN_020889B0
FUN_020889B0: ; 0x020889B0
	push {r3-r5, lr}
	add r4, r0, #0x0
	bl OverlayManager_GetField18
	mov r2, #0x1
	add r5, r0, #0x0
	mov r0, #0x3
	mov r1, #0x37
	lsl r2, r2, #0xe
	bl CreateHeap
	add r0, r4, #0x0
	mov r1, #0x24
	mov r2, #0x37
	bl OverlayManager_CreateAndGetData
	mov r1, #0x0
	mov r2, #0x24
	add r4, r0, #0x0
	bl MI_CpuFill8
	mov r0, #0x37
	str r0, [r4, #0x0]
	str r5, [r4, #0x10]
	ldr r0, [r4, #0x0]
	bl FUN_0206F164
	str r0, [r4, #0xc]
	ldr r0, [r5, #0x4]
	cmp r0, #0x1
	bne _020889FA
	ldrh r1, [r4, #0x6]
	mov r0, #0xff
	bic r1, r0
	mov r0, #0x1
	orr r0, r1
	strh r0, [r4, #0x6]
_020889FA:
	mov r0, #0x1
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02088A00
FUN_02088A00: ; 0x02088A00
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl OverlayManager_GetData
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl OverlayManager_GetField18
	ldr r5, [r4, #0x0]
	cmp r5, #0x4
	bhi _02088A6A
	add r0, r5, r5
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02088A24: ; jump table (using 16-bit offset)
	.short _02088A2E - _02088A24 - 2; case 0
	.short _02088A3C - _02088A24 - 2; case 1
	.short _02088A4A - _02088A24 - 2; case 2
	.short _02088A58 - _02088A24 - 2; case 3
	.short _02088A66 - _02088A24 - 2; case 4
_02088A2E:
	add r1, r6, #0x0
	add r0, r6, #0x0
	add r1, #0x14
	bl FUN_02088AAC
	str r0, [r4, #0x0]
	b _02088A6A
_02088A3C:
	add r1, r6, #0x0
	add r0, r6, #0x0
	add r1, #0x14
	bl FUN_02088AFC
	str r0, [r4, #0x0]
	b _02088A6A
_02088A4A:
	add r1, r6, #0x0
	add r0, r6, #0x0
	add r1, #0x14
	bl FUN_02088B28
	str r0, [r4, #0x0]
	b _02088A6A
_02088A58:
	add r1, r6, #0x0
	add r0, r6, #0x0
	add r1, #0x14
	bl FUN_02088B48
	str r0, [r4, #0x0]
	b _02088A6A
_02088A66:
	mov r0, #0x1
	pop {r4-r6, pc}
_02088A6A:
	ldr r0, [r4, #0x0]
	cmp r5, r0
	beq _02088A74
	mov r0, #0x0
	str r0, [r6, #0x14]
_02088A74:
	mov r0, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_02088A78
FUN_02088A78: ; 0x02088A78
	push {r4-r6, lr}
	add r5, r0, #0x0
	bl OverlayManager_GetData
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl OverlayManager_GetField18
	ldr r0, [r4, #0xc]
	ldr r6, [r4, #0x0]
	bl FreeToHeap
	add r0, r4, #0x0
	mov r1, #0x0
	mov r2, #0x24
	bl MI_CpuFill8
	add r0, r5, #0x0
	bl OverlayManager_FreeData
	add r0, r6, #0x0
	bl DestroyHeap
	mov r0, #0x1
	pop {r4-r6, pc}
	.balign 4
