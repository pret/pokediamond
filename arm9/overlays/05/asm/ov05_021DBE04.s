	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021DBE04
ov05_021DBE04: ; 0x021DBE04
	push {r4, lr}
	ldr r4, [r0, #0x18]
	cmp r4, #0
	bne _021DBE10
	bl GF_AssertFail
_021DBE10:
	cmp r4, #5
	blt _021DBE18
	bl GF_AssertFail
_021DBE18:
	sub r0, r4, #1
	pop {r4, pc}

	thumb_func_start ov05_021DBE1C
ov05_021DBE1C: ; 0x021DBE1C
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021DBE04
	add r1, r0, #0
	lsl r2, r1, #4
	ldr r1, _021DBE34 ; =ov05_021F6788
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_021DBE34: .word ov05_021F6788

	thumb_func_start ov05_021DBE38
ov05_021DBE38: ; 0x021DBE38
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021DBE04
	lsl r1, r0, #4
	ldr r0, _021DBE54 ; =ov05_021F678C
	ldr r1, [r0, r1]
	cmp r1, #0
	bne _021DBE4E
	mov r0, #1
	pop {r4, pc}
_021DBE4E:
	add r0, r4, #0
	blx r1
	pop {r4, pc}
	.balign 4, 0
_021DBE54: .word ov05_021F678C

	thumb_func_start ov05_021DBE58
ov05_021DBE58: ; 0x021DBE58
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021DBE04
	add r1, r0, #0
	lsl r2, r1, #4
	ldr r1, _021DBE70 ; =ov05_021F6790
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_021DBE70: .word ov05_021F6790

	thumb_func_start ov05_021DBE74
ov05_021DBE74: ; 0x021DBE74
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021DBE04
	add r1, r0, #0
	lsl r2, r1, #4
	ldr r1, _021DBE8C ; =ov05_021F6794
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	pop {r4, pc}
	nop
_021DBE8C: .word ov05_021F6794

	thumb_func_start ov05_021DBE90
ov05_021DBE90: ; 0x021DBE90
	ldr r3, _021DBE94 ; =ov05_021EFAAC
	bx r3
	.balign 4, 0
_021DBE94: .word ov05_021EFAAC

	thumb_func_start ov05_021DBE98
ov05_021DBE98: ; 0x021DBE98
	ldr r3, _021DBE9C ; =sub_02050E2C
	bx r3
	.balign 4, 0
_021DBE9C: .word sub_02050E2C

	thumb_func_start ov05_021DBEA0
ov05_021DBEA0: ; 0x021DBEA0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _021DBEB8 ; =SDK_OVERLAY_OVERLAY_51_ID
	mov r1, #2
	bl HandleLoadOverlay
	add r0, r4, #0
	bl ov51_02254A68
	add r4, #0x80
	str r0, [r4]
	pop {r4, pc}
	.balign 4, 0
_021DBEB8: .word SDK_OVERLAY_OVERLAY_51_ID

	thumb_func_start ov05_021DBEBC
ov05_021DBEBC: ; 0x021DBEBC
	ldr r3, _021DBEC0 ; =ov05_021EFB14
	bx r3
	.balign 4, 0
_021DBEC0: .word ov05_021EFB14

	thumb_func_start ov05_021DBEC4
ov05_021DBEC4: ; 0x021DBEC4
	ldr r3, _021DBEC8 ; =sub_02050E10
	bx r3
	.balign 4, 0
_021DBEC8: .word sub_02050E10

	thumb_func_start ov05_021DBECC
ov05_021DBECC: ; 0x021DBECC
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0]
	bl ov51_02254AB8
	ldr r0, _021DBEE0 ; =SDK_OVERLAY_OVERLAY_51_ID
	bl UnloadOverlayByID
	pop {r3, pc}
	nop
_021DBEE0: .word SDK_OVERLAY_OVERLAY_51_ID

	thumb_func_start ov05_021DBEE4
ov05_021DBEE4: ; 0x021DBEE4
	ldr r3, _021DBEE8 ; =ov05_021EFB50
	bx r3
	.balign 4, 0
_021DBEE8: .word ov05_021EFB50

	thumb_func_start ov05_021DBEEC
ov05_021DBEEC: ; 0x021DBEEC
	mov r0, #1
	bx lr

	thumb_func_start ov05_021DBEF0
ov05_021DBEF0: ; 0x021DBEF0
	mov r0, #1
	bx lr

	.section .rodata

	.global ov05_021F6788
ov05_021F6788: ; 0x021F6788
	.word ov05_021DBE90

	.global ov05_021F678C
ov05_021F678C: ; 0x021F678C
	.word 0x00000000

	.global ov05_021F6790
ov05_021F6790: ; 0x021F6790
	.word ov05_021DBEBC

	.global ov05_021F6794
ov05_021F6794: ; 0x021F6794
	.word ov05_021DBEE4, ov05_021DBE98, 0x00000000, ov05_021DBEC4
	.word ov05_021DBEF0, ov05_021DBEA0, 0x00000000, ov05_021DBECC
	.word ov05_021DBEEC, ov05_021EFBB4, 0x00000000, ov05_021EFBCC
	.word ov05_021EFBD8
