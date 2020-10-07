    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020FD6D4
UNK_020FD6D4: ; 0x020FD6D4
	.word FUN_020888DC, 0x00000000, 0x00000000, 0xFFFFFFFF

	.text

	thumb_func_start FUN_02088858
FUN_02088858: ; 0x02088858
	ldr r3, _02088860 ; =HandleLoadOverlay
	ldr r0, _02088864 ; =SDK_OVERLAY_MODULE_04_ID
	mov r1, #0x2
	bx r3
	.balign 4
_02088860: .word HandleLoadOverlay
_02088864: .word SDK_OVERLAY_MODULE_04_ID

	thumb_func_start FUN_02088868
FUN_02088868: ; 0x02088868
	ldr r3, _02088870 ; =UnloadOverlayByID
	ldr r0, _02088874 ; =SDK_OVERLAY_MODULE_04_ID
	bx r3
	nop
_02088870: .word UnloadOverlayByID
_02088874: .word SDK_OVERLAY_MODULE_04_ID

	thumb_func_start FUN_02088878
FUN_02088878: ; 0x02088878
	ldr r3, _02088880 ; =HandleLoadOverlay
	ldr r0, _02088884 ; =SDK_OVERLAY_MODULE_13_ID
	mov r1, #0x2
	bx r3
	.balign 4
_02088880: .word HandleLoadOverlay
_02088884: .word SDK_OVERLAY_MODULE_13_ID

	thumb_func_start FUN_02088888
FUN_02088888: ; 0x02088888
	ldr r3, _02088890 ; =UnloadOverlayByID
	ldr r0, _02088894 ; =SDK_OVERLAY_MODULE_13_ID
	bx r3
	nop
_02088890: .word UnloadOverlayByID
_02088894: .word SDK_OVERLAY_MODULE_13_ID

	thumb_func_start FUN_02088898
FUN_02088898: ; 0x02088898
	push {r4, lr}
	add r4, r1, #0x0
	bl FUN_02088858
	bl FUN_02088878
	add r0, r4, #0x0
	bl MOD07_02211E60
	bl FUN_02088888
	bl FUN_02088868
	mov r0, #0x0
	bl OS_ResetSystem
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020888BC
FUN_020888BC: ; 0x020888BC
	ldr r3, _020888C4 ; =HandleLoadOverlay
	ldr r0, _020888C8 ; =SDK_OVERLAY_MODULE_79_ID
	mov r1, #0x2
	bx r3
	.balign 4
_020888C4: .word HandleLoadOverlay
_020888C8: .word SDK_OVERLAY_MODULE_79_ID

	thumb_func_start FUN_020888CC
FUN_020888CC: ; 0x020888CC
	ldr r3, _020888D4 ; =UnloadOverlayByID
	ldr r0, _020888D8 ; =SDK_OVERLAY_MODULE_79_ID
	bx r3
	nop
_020888D4: .word UnloadOverlayByID
_020888D8: .word SDK_OVERLAY_MODULE_79_ID

	thumb_func_start FUN_020888DC
FUN_020888DC: ; 0x020888DC
	push {r4, lr}
	mov r2, #0x41
	add r4, r0, #0x0
	mov r0, #0x3
	mov r1, #0x31
	lsl r2, r2, #0xc
	bl FUN_0201681C
	add r0, r4, #0x0
	bl OverlayManager_GetField18
	ldr r0, [r0, #0x8]
	mov r1, #0x31
	bl FUN_02088898
	mov r0, #0x31
	bl FUN_020168D0
	mov r0, #0x0
	bl OS_ResetSystem
	mov r0, #0x1
	pop {r4, pc}
	.balign 4
