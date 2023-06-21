	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021DB900
ov05_021DB900: ; 0x021DB900
	push {r4, lr}
	mov r0, #4
	mov r1, #8
	bl AllocFromHeap
	add r4, r0, #0
	bne _021DB912
	bl GF_AssertFail
_021DB912:
	add r0, r4, #0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021DB918
ov05_021DB918: ; 0x021DB918
	push {r3, r4, r5, r6, lr}
	sub sp, #0x4c
	add r4, r0, #0
	add r0, sp, #4
	add r5, r1, #0
	bl FS_InitFile
	add r0, sp, #4
	add r1, r4, #0
	bl FS_OpenFile
	cmp r0, #0
	beq _021DB9B4
	add r1, sp, #0
	add r0, sp, #4
	add r1, #2
	mov r2, #2
	bl FS_ReadFile
	cmp r0, #0
	bge _021DB946
	bl GF_AssertFail
_021DB946:
	add r0, sp, #4
	add r1, sp, #0
	mov r2, #2
	bl FS_ReadFile
	cmp r0, #0
	bge _021DB958
	bl GF_AssertFail
_021DB958:
	add r0, sp, #0
	ldrh r1, [r0, #2]
	ldrh r0, [r0]
	lsl r6, r1, #2
	lsl r4, r0, #2
	mov r0, #4
	add r1, r6, #0
	bl AllocFromHeap
	str r0, [r5]
	cmp r0, #0
	bne _021DB974
	bl GF_AssertFail
_021DB974:
	mov r0, #4
	add r1, r4, #0
	bl AllocFromHeap
	str r0, [r5, #4]
	cmp r0, #0
	bne _021DB986
	bl GF_AssertFail
_021DB986:
	ldr r1, [r5]
	add r0, sp, #4
	add r2, r6, #0
	bl FS_ReadFile
	cmp r0, #0
	bge _021DB998
	bl GF_AssertFail
_021DB998:
	ldr r1, [r5, #4]
	add r0, sp, #4
	add r2, r4, #0
	bl FS_ReadFile
	cmp r0, #0
	bge _021DB9AA
	bl GF_AssertFail
_021DB9AA:
	add r0, sp, #4
	bl FS_CloseFile
	add sp, #0x4c
	pop {r3, r4, r5, r6, pc}
_021DB9B4:
	bl GF_AssertFail
	add sp, #0x4c
	pop {r3, r4, r5, r6, pc}

	thumb_func_start ov05_021DB9BC
ov05_021DB9BC: ; 0x021DB9BC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #4]
	bl FreeToHeap
	ldr r0, [r4]
	bl FreeToHeap
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start ov05_021DB9D4
ov05_021DB9D4: ; 0x021DB9D4
	ldr r1, [r1]
	lsl r0, r0, #2
	ldrh r0, [r1, r0]
	strh r0, [r2]
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021DB9E0
ov05_021DB9E0: ; 0x021DB9E0
	push {r3, r4}
	lsl r4, r0, #2
	ldr r0, [r1]
	ldrh r0, [r0, r4]
	strh r0, [r2]
	ldr r0, [r1]
	add r0, r0, r4
	ldrh r0, [r0, #2]
	strh r0, [r3]
	pop {r3, r4}
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021DB9F8
ov05_021DB9F8: ; 0x021DB9F8
	ldr r1, [r1, #4]
	lsl r0, r0, #2
	add r0, r1, r0
	bx lr
