	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start sub_02063888
sub_02063888: ; 0x02063888
	push {r4-r6, lr}
	add r5, r1, #0x0
	mov r1, #0x18
	add r4, r2, #0x0
	add r6, r3, #0x0
	bl AllocFromHeapAtEnd
	add r3, r0, #0x0
	mov r2, #0x18
	mov r1, #0x0
_0206389C:
	strb r1, [r3, #0x0]
	add r3, r3, #0x1
	sub r2, r2, #0x1
	bne _0206389C
	str r5, [r0, #0x0]
	str r4, [r0, #0x10]
	strh r6, [r0, #0x8]
	add r2, sp, #0x0
	mov r1, #0x10
	ldrsh r1, [r2, r1]
	strh r1, [r0, #0xa]
	mov r1, #0x14
	ldrsh r1, [r2, r1]
	strh r1, [r0, #0xc]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start sub_020638BC
sub_020638BC: ; 0x020638BC
	push {r3-r6, lr}
	sub sp, #0x1c
	add r5, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r0, r5, #0x0
	bl TaskManager_GetEnvironment
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	beq _020638DA
	cmp r0, #0x1
	beq _020638F8
	b _02063942
_020638DA:
	ldr r0, [r4, #0x0]
	ldr r0, [r0, #0x38]
	bl PlayerAvatar_GetGender
	add r3, r0, #0x0
	ldr r0, [r4, #0x0]
	ldr r2, [r4, #0x10]
	mov r1, #0x1
	bl ov06_0224666C
	str r0, [r4, #0x14]
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _02063942
_020638F8:
	ldr r0, [r4, #0x14]
	bl ov06_022466A0
	cmp r0, #0x0
	beq _02063942
	ldr r0, [r4, #0x14]
	bl ov06_022466AC
	mov r1, #0xa
	mov r2, #0xc
	ldrh r0, [r4, #0x8]
	ldrsh r1, [r4, r1]
	ldrsh r2, [r4, r2]
	bl sub_02034F40
	lsl r0, r0, #0x10
	lsr r6, r0, #0x10
	bne _02063920
	bl GF_AssertFail
_02063920:
	add r0, r6, #0x0
	add r1, sp, #0x8
	bl GetSpecialSpawnWarpData
	ldr r0, [sp, #0x14]
	mov r2, #0x1
	str r0, [sp, #0x0]
	str r2, [sp, #0x4]
	ldr r1, [sp, #0x8]
	ldr r3, [sp, #0x10]
	add r0, r5, #0x0
	sub r2, r2, #0x2
	bl sub_020492BC
	add r0, r4, #0x0
	bl FreeToHeap
_02063942:
	mov r0, #0x0
	add sp, #0x1c
	pop {r3-r6, pc}
