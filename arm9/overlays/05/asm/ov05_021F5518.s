	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021F5518
ov05_021F5518: ; 0x021F5518
	push {r3, r4, lr}
	sub sp, #4
	ldr r0, [r1, #8]
	add r4, r2, #0
	bl ov05_021F5608
	add r0, r4, #0
	mov r1, #0
	mov r2, #0xa
	mov r3, #0x13
	bl ov05_021F5660
	mov r3, #0
	str r3, [r4, #0x14]
	mov r0, #0x10
	str r0, [sp]
	ldr r0, _021F555C ; =0x04000050
	mov r1, #4
	mov r2, #0x29
	bl G2x_SetBlendAlpha_
	mov r0, #2
	mov r1, #0
	bl SetBgPriority
	mov r0, #4
	mov r1, #1
	bl GfGfx_EngineATogglePlanes
	ldr r0, _021F5560 ; =0x00000648
	bl PlaySE
	add sp, #4
	pop {r3, r4, pc}
	.balign 4, 0
_021F555C: .word 0x04000050
_021F5560: .word 0x00000648

	thumb_func_start ov05_021F5564
ov05_021F5564: ; 0x021F5564
	push {r3, r4, lr}
	sub sp, #4
	ldr r0, [r1, #8]
	add r4, r2, #0
	bl ov05_021F5608
	add r0, r4, #0
	mov r1, #0xa
	mov r2, #0
	mov r3, #0xf
	bl ov05_021F5660
	mov r0, #0
	str r0, [r4, #0x14]
	mov r0, #6
	str r0, [sp]
	ldr r0, _021F5594 ; =0x04000050
	mov r1, #4
	mov r2, #0x21
	mov r3, #0xa
	bl G2x_SetBlendAlpha_
	add sp, #4
	pop {r3, r4, pc}
	.balign 4, 0
_021F5594: .word 0x04000050

	thumb_func_start ov05_021F5598
ov05_021F5598: ; 0x021F5598
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F559C
ov05_021F559C: ; 0x021F559C
	push {r4, lr}
	add r4, r2, #0
	ldr r0, [r4, #0x14]
	cmp r0, #1
	beq _021F55C2
	add r0, r4, #0
	bl ov05_021F5670
	cmp r0, #0
	beq _021F55B4
	mov r0, #1
	str r0, [r4, #0x14]
_021F55B4:
	ldr r1, [r4]
	mov r0, #0x10
	sub r0, r0, r1
	lsl r0, r0, #8
	orr r1, r0
	ldr r0, _021F55C4 ; =0x04000052
	strh r1, [r0]
_021F55C2:
	pop {r4, pc}
	.balign 4, 0
_021F55C4: .word 0x04000052

	thumb_func_start ov05_021F55C8
ov05_021F55C8: ; 0x021F55C8
	bx lr
	.balign 4, 0

	thumb_func_start ov05_021F55CC
ov05_021F55CC: ; 0x021F55CC
	ldr r0, [r0, #4]
	ldr r3, _021F55D8 ; =ov05_021D8024
	ldr r0, [r0, #4]
	ldr r1, _021F55DC ; =ov05_021FC6C0
	bx r3
	nop
_021F55D8: .word ov05_021D8024
_021F55DC: .word ov05_021FC6C0

	thumb_func_start ov05_021F55E0
ov05_021F55E0: ; 0x021F55E0
	ldr r3, _021F55E4 ; =ov05_021D80A4
	bx r3
	.balign 4, 0
_021F55E4: .word ov05_021D80A4

	thumb_func_start ov05_021F55E8
ov05_021F55E8: ; 0x021F55E8
	push {r3, lr}
	bl ov05_021D80E4
	ldr r0, [r0, #0x14]
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021F55F4
ov05_021F55F4: ; 0x021F55F4
	ldr r0, [r0, #4]
	ldr r3, _021F5600 ; =ov05_021D8024
	ldr r0, [r0, #4]
	ldr r1, _021F5604 ; =ov05_021FC6A8
	bx r3
	nop
_021F5600: .word ov05_021D8024
_021F5604: .word ov05_021FC6A8

	thumb_func_start ov05_021F5608
ov05_021F5608: ; 0x021F5608
	push {r3, r4, r5, lr}
	sub sp, #8
	ldr r1, _021F5658 ; =0x00005D5F
	add r5, r0, #0
	add r0, sp, #4
	strh r1, [r0]
	mov r0, #2
	add r1, sp, #4
	add r2, r0, #0
	mov r3, #0xc2
	bl BG_LoadPlttData
	mov r0, #4
	mov r1, #0x20
	bl AllocFromHeap
	mov r1, #0x11
	mov r2, #0x20
	add r4, r0, #0
	bl memset
	mov r0, #1
	str r0, [sp]
	add r0, r5, #0
	mov r1, #2
	add r2, r4, #0
	mov r3, #0x20
	bl BG_LoadCharTilesData
	add r0, r4, #0
	bl FreeToHeap
	ldr r2, _021F565C ; =0x00006001
	add r0, r5, #0
	mov r1, #2
	bl BgFillTilemapBufferAndCommit
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_021F5658: .word 0x00005D5F
_021F565C: .word 0x00006001

	thumb_func_start ov05_021F5660
ov05_021F5660: ; 0x021F5660
	str r1, [r0]
	str r1, [r0, #4]
	sub r1, r2, r1
	str r1, [r0, #8]
	str r3, [r0, #0x10]
	mov r1, #0
	str r1, [r0, #0xc]
	bx lr

	thumb_func_start ov05_021F5670
ov05_021F5670: ; 0x021F5670
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #8]
	ldr r0, [r4, #0xc]
	mul r0, r1
	ldr r1, [r4, #0x10]
	bl _s32_div_f
	ldr r1, [r4, #4]
	add r0, r0, r1
	str r0, [r4]
	ldr r0, [r4, #0xc]
	ldr r1, [r4, #0x10]
	add r0, r0, #1
	cmp r0, r1
	bgt _021F5696
	str r0, [r4, #0xc]
	mov r0, #0
	pop {r4, pc}
_021F5696:
	str r1, [r4, #0xc]
	mov r0, #1
	pop {r4, pc}

	thumb_func_start ov05_021F569C
ov05_021F569C: ; 0x021F569C
	ldr r3, _021F56A4 ; =BG_SetMaskColor
	mov r0, #2
	mov r1, #0
	bx r3
	.balign 4, 0
_021F56A4: .word BG_SetMaskColor

	thumb_func_start ov05_021F56A8
ov05_021F56A8: ; 0x021F56A8
	ldr r3, _021F56B0 ; =BG_SetMaskColor
	mov r0, #2
	ldr r1, _021F56B4 ; =0x00007FFF
	bx r3
	.balign 4, 0
_021F56B0: .word BG_SetMaskColor
_021F56B4: .word 0x00007FFF

	thumb_func_start ov05_021F56B8
ov05_021F56B8: ; 0x021F56B8
	push {r4, lr}
	sub sp, #8
	ldr r1, _021F5710 ; =0x00007FFF
	add r4, r0, #0
	add r0, sp, #4
	strh r1, [r0]
	mov r0, #4
	mov r1, #0
	bl GfGfx_EngineATogglePlanes
	ldr r1, _021F5714 ; =0x0400000C
	mov r0, #3
	ldrh r2, [r1]
	mov r3, #0xc4
	bic r2, r0
	mov r0, #3
	orr r0, r2
	strh r0, [r1]
	mov r0, #2
	add r1, sp, #4
	add r2, r0, #0
	bl BG_LoadPlttData
	mov r1, #2
	str r1, [sp]
	ldr r0, [r4, #8]
	add r2, r1, #0
	mov r3, #1
	bl BG_FillCharDataRange
	ldr r0, [r4, #8]
	ldr r2, _021F5718 ; =0x00006002
	mov r1, #2
	bl BgFillTilemapBufferAndCommit
	mov r0, #4
	mov r1, #1
	bl GfGfx_EngineATogglePlanes
	add r0, r4, #0
	bl ov05_021F569C
	add sp, #8
	pop {r4, pc}
	.balign 4, 0
_021F5710: .word 0x00007FFF
_021F5714: .word 0x0400000C
_021F5718: .word 0x00006002

	thumb_func_start ov05_021F571C
ov05_021F571C: ; 0x021F571C
	push {r4, lr}
	sub sp, #8
	ldr r1, _021F5774 ; =0x00007FFF
	add r4, r0, #0
	add r0, sp, #4
	strh r1, [r0]
	mov r0, #8
	mov r1, #0
	bl GfGfx_EngineATogglePlanes
	ldr r1, _021F5778 ; =0x0400000E
	mov r0, #3
	ldrh r2, [r1]
	mov r3, #0xc4
	bic r2, r0
	mov r0, #3
	orr r2, r0
	strh r2, [r1]
	add r1, sp, #4
	mov r2, #2
	bl BG_LoadPlttData
	mov r2, #2
	str r2, [sp]
	ldr r0, [r4, #8]
	mov r1, #3
	mov r3, #1
	bl BG_FillCharDataRange
	ldr r0, [r4, #8]
	ldr r2, _021F577C ; =0x00006002
	mov r1, #3
	bl BgFillTilemapBufferAndCommit
	mov r0, #8
	mov r1, #1
	bl GfGfx_EngineATogglePlanes
	add r0, r4, #0
	bl ov05_021F569C
	add sp, #8
	pop {r4, pc}
	nop
_021F5774: .word 0x00007FFF
_021F5778: .word 0x0400000E
_021F577C: .word 0x00006002

	thumb_func_start ov05_021F5780
ov05_021F5780: ; 0x021F5780
	push {r3, lr}
	ldr r0, [r0, #4]
	ldr r0, [r0, #0xc]
	bl ov05_021DC1D0
	ldr r3, _021F57A4 ; =ov05_021FC6A4
	mov r2, #0
_021F578E:
	ldr r1, [r3]
	cmp r0, r1
	bne _021F5798
	mov r0, #1
	pop {r3, pc}
_021F5798:
	add r2, r2, #1
	add r3, r3, #4
	cmp r2, #1
	blt _021F578E
	mov r0, #0
	pop {r3, pc}
	.balign 4, 0
_021F57A4: .word ov05_021FC6A4

	thumb_func_start ov05_021F57A8
ov05_021F57A8: ; 0x021F57A8
	push {r3, lr}
	ldr r0, [r0, #4]
	ldr r0, [r0, #0xc]
	bl ov05_021DC1D0
	ldr r3, _021F57CC ; =ov05_021FC6D8
	mov r2, #0
_021F57B6:
	ldr r1, [r3]
	cmp r0, r1
	bne _021F57C0
	mov r0, #0
	pop {r3, pc}
_021F57C0:
	add r2, r2, #1
	add r3, r3, #4
	cmp r2, #0x10
	blt _021F57B6
	mov r0, #1
	pop {r3, pc}
	.balign 4, 0
_021F57CC: .word ov05_021FC6D8

	thumb_func_start ov05_021F57D0
ov05_021F57D0: ; 0x021F57D0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F57E2
	bl ov05_021F55E0
	mov r0, #0
	str r0, [r4]
_021F57E2:
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021F57EC
ov05_021F57EC: ; 0x021F57EC
	mov r0, #0xc
	bx lr

	thumb_func_start ov05_021F57F0
ov05_021F57F0: ; 0x021F57F0
	push {r4, r5, r6, lr}
	add r6, r0, #0
	bl TaskManager_GetFieldSystem
	add r5, r0, #0
	add r0, r6, #0
	bl TaskManager_GetEnvironment
	add r4, r0, #0
	ldrh r1, [r4, #8]
	cmp r1, #9
	bls _021F580A
	b _021F597C
_021F580A:
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_021F5816: ; jump table
	.short _021F582A - _021F5816 - 2 ; case 0
	.short _021F5856 - _021F5816 - 2 ; case 1
	.short _021F5872 - _021F5816 - 2 ; case 2
	.short _021F5888 - _021F5816 - 2 ; case 3
	.short _021F58DA - _021F5816 - 2 ; case 4
	.short _021F58EE - _021F5816 - 2 ; case 5
	.short _021F5914 - _021F5816 - 2 ; case 6
	.short _021F5936 - _021F5816 - 2 ; case 7
	.short _021F5956 - _021F5816 - 2 ; case 8
	.short _021F5968 - _021F5816 - 2 ; case 9
_021F582A:
	add r0, r5, #0
	bl ov05_021F57A8
	cmp r0, #1
	bne _021F584C
	mov r0, #1
	strh r0, [r4, #8]
	add r0, r5, #0
	bl ov05_021F5780
	str r0, [r4, #4]
	cmp r0, #0
	beq _021F587C
	add r0, r5, #0
	bl ov05_021F56A8
	b _021F5980
_021F584C:
	mov r0, #7
	strh r0, [r4, #8]
	mov r0, #0x14
	strh r0, [r4, #0xa]
	b _021F5980
_021F5856:
	add r0, r5, #0
	bl ov05_021F55CC
	str r0, [r4]
	mov r0, #2
	mov r1, #0
	strh r0, [r4, #8]
	bl SetBgPriority
	mov r0, #4
	mov r1, #1
	bl GfGfx_EngineATogglePlanes
	b _021F5980
_021F5872:
	ldr r0, [r4]
	bl ov05_021F55E8
	cmp r0, #0
	bne _021F587E
_021F587C:
	b _021F5980
_021F587E:
	mov r0, #0x16
	strh r0, [r4, #0xa]
	mov r0, #3
	strh r0, [r4, #8]
	b _021F5980
_021F5888:
	mov r0, #0xa
	ldrsh r0, [r4, r0]
	sub r0, r0, #1
	strh r0, [r4, #0xa]
	ldr r0, [r5, #0x1c]
	ldr r0, [r0]
	bl MapHeader_HasWildEncounters
	cmp r0, #0
	beq _021F58D4
	mov r0, #0xa
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bge _021F5980
	ldr r0, [r5, #0x38]
	bl GetPlayerXCoord
	add r6, r0, #0
	ldr r0, [r5, #0x38]
	bl GetPlayerYCoord
	add r2, r0, #0
	add r0, r5, #0
	add r1, r6, #0
	bl sub_0204A6E0
	add r1, r0, #0
	add r0, r5, #0
	bl ov06_0223CDB8
	cmp r0, #0
	beq _021F58CE
	mov r0, #6
	strh r0, [r4, #8]
	b _021F5980
_021F58CE:
	mov r0, #4
	strh r0, [r4, #8]
	b _021F5980
_021F58D4:
	mov r0, #4
	strh r0, [r4, #8]
	b _021F5980
_021F58DA:
	ldr r0, [r4]
	bl ov05_021F55E0
	add r0, r5, #0
	bl ov05_021F55F4
	str r0, [r4]
	mov r0, #5
	strh r0, [r4, #8]
	b _021F5980
_021F58EE:
	ldr r0, [r4]
	bl ov05_021F55E8
	cmp r0, #0
	beq _021F5980
	mov r0, #4
	mov r1, #0
	bl GfGfx_EngineATogglePlanes
	ldr r0, _021F5984 ; =0x04000050
	mov r1, #0
	strh r1, [r0]
	mov r0, #2
	mov r1, #3
	bl SetBgPriority
	mov r0, #8
	strh r0, [r4, #8]
	b _021F5980
_021F5914:
	bl ov05_021F57D0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021F5924
	add r0, r5, #0
	bl ov05_021F571C
_021F5924:
	add r0, r5, #0
	add r1, r6, #0
	bl ov06_0223BE70
	cmp r0, #0
	bne _021F5980
	bl GF_AssertFail
	b _021F5980
_021F5936:
	mov r0, #0xa
	ldrsh r1, [r4, r0]
	sub r1, r1, #1
	strh r1, [r4, #0xa]
	ldrsh r0, [r4, r0]
	cmp r0, #0
	bge _021F5980
	mov r2, #0
	ldr r1, _021F5988 ; =0x000007ED
	add r0, r6, #0
	add r3, r2, #0
	bl QueueScript
	mov r0, #9
	strh r0, [r4, #8]
	b _021F5980
_021F5956:
	mov r2, #0
	ldr r1, _021F598C ; =0x000007EC
	add r0, r6, #0
	add r3, r2, #0
	bl QueueScript
	mov r0, #9
	strh r0, [r4, #8]
	b _021F5980
_021F5968:
	bl ov05_021F57D0
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _021F5978
	add r0, r5, #0
	bl ov05_021F56B8
_021F5978:
	mov r0, #1
	pop {r4, r5, r6, pc}
_021F597C:
	bl GF_AssertFail
_021F5980:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021F5984: .word 0x04000050
_021F5988: .word 0x000007ED
_021F598C: .word 0x000007EC

	.section .rodata

	.global ov05_021FC6A4
ov05_021FC6A4: ; 0x021FC6A4
	.byte 0x08, 0x00, 0x00, 0x00

	.global ov05_021FC6A8
ov05_021FC6A8: ; 0x021FC6A8
	.word 0x00000400, 0x00000018, ov05_021F5564, ov05_021F5598
	.word ov05_021F559C, ov05_021F55C8

	.global ov05_021FC6C0
ov05_021FC6C0: ; 0x021FC6C0
	.word 0x00000400, 0x00000018, ov05_021F5518, ov05_021F5598
	.word ov05_021F559C, ov05_021F55C8

	.global ov05_021FC6D8
ov05_021FC6D8: ; 0x021FC6D8
	.byte 0x02, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00
	.byte 0x07, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00
	.byte 0x0E, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00
	.byte 0x09, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00
