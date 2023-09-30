	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020F7630
UNK_020F7630: ; 0x020F7630
	.word ov81_02237E40, ov81_02238064, ov81_02238004, SDK_OVERLAY_OVERLAY_81_ID

	.text

	thumb_func_start sub_020606B0
sub_020606B0: ; 0x020606B0
	push {r4, lr}
	add r4, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r0, r4, #0x0
	bl TaskManager_GetEnvironment
	add r2, r0, #0x0
	ldr r1, _020606CC ; =UNK_020F7630
	add r0, r4, #0x0
	add r2, #0xc
	bl sub_02046500
	pop {r4, pc}
	.balign 4
_020606CC: .word UNK_020F7630

	thumb_func_start sub_020606D0
sub_020606D0: ; 0x020606D0
	push {r4-r6, lr}
	sub sp, #0x8
	add r5, r0, #0x0
	bl TaskManager_GetFieldSystem
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl TaskManager_GetEnvironment
	add r4, r0, #0x0
	ldr r0, [r4, #0x4]
	cmp r0, #0x6
	bhi _0206078A
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020606F6: ; jump table (using 16-bit offset)
	.short _02060704 - _020606F6 - 2; case 0
	.short _0206072C - _020606F6 - 2; case 1
	.short _0206073A - _020606F6 - 2; case 2
	.short _02060748 - _020606F6 - 2; case 3
	.short _02060756 - _020606F6 - 2; case 4
	.short _02060764 - _020606F6 - 2; case 5
	.short _02060772 - _020606F6 - 2; case 6
_02060704:
	ldr r0, [r4, #0x24]
	add r3, r4, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r4, #0x28]
	add r3, #0xc
	str r0, [sp, #0x4]
	ldr r1, [r4, #0x0]
	ldr r2, [r4, #0x8]
	add r0, r6, #0x0
	bl ov06_0224891C
	ldr r1, [r4, #0x0]
	ldr r2, [r4, #0x8]
	add r0, r6, #0x0
	bl ov06_022488FC
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0206078A
_0206072C:
	add r0, r5, #0x0
	bl CallTask_FadeToBlack
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0206078A
_0206073A:
	add r0, r5, #0x0
	bl sub_0204AF3C
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0206078A
_02060748:
	add r0, r5, #0x0
	bl sub_020606B0
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0206078A
_02060756:
	add r0, r5, #0x0
	bl CallTask_RestoreOverworld
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0206078A
_02060764:
	add r0, r5, #0x0
	bl CallTask_FadeFromBlack
	ldr r0, [r4, #0x4]
	add r0, r0, #0x1
	str r0, [r4, #0x4]
	b _0206078A
_02060772:
	ldr r0, [r4, #0x24]
	bl FreeToHeap
	ldr r0, [r4, #0x28]
	bl FreeToHeap
	add r0, r4, #0x0
	bl FreeToHeap
	add sp, #0x8
	mov r0, #0x1
	pop {r4-r6, pc}
_0206078A:
	mov r0, #0x0
	add sp, #0x8
	pop {r4-r6, pc}

	thumb_func_start CallTask_NPCTrade
CallTask_NPCTrade: ; 0x02060790
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r5, r1, #0x0
	add r0, r3, #0x0
	mov r1, #0x2c
	add r6, r2, #0x0
	str r3, [sp, #0x0]
	bl AllocFromHeap
	mov r1, #0x0
	mov r2, #0x2c
	add r4, r0, #0x0
	bl memset
	mov r0, #0x0
	str r0, [r4, #0x4]
	str r5, [r4, #0x0]
	ldr r0, [sp, #0x0]
	str r6, [r4, #0x8]
	bl AllocMonZeroed
	str r0, [r4, #0x24]
	ldr r0, [sp, #0x0]
	bl AllocMonZeroed
	str r0, [r4, #0x28]
	ldr r1, _020607D0 ; =sub_020606D0
	add r0, r7, #0x0
	add r2, r4, #0x0
	bl TaskManager_Call
	pop {r3-r7, pc}
	.balign 4
_020607D0: .word sub_020606D0
