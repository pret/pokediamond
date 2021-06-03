	.include "asm/macros.inc"
	.include "global.inc"

	.section .bss

	.global UNK_021C5934
UNK_021C5934: ; 0x021C5934
	.space 0x4

	.text

	thumb_func_start FUN_0201C24C
FUN_0201C24C: ; 0x0201C24C
	push {r3-r5, lr}
	add r5, r0, #0x0
	ldr r0, _0201C298 ; =UNK_021C5934
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201C25E
	bl GF_AssertFail
_0201C25E:
	add r0, r4, #0x0
	mov r1, #0xc
	bl AllocFromHeap
	ldr r1, _0201C298 ; =UNK_021C5934
	cmp r0, #0x0
	str r0, [r1, #0x0]
	bne _0201C272
	bl GF_AssertFail
_0201C272:
	add r0, r4, #0x0
	lsl r1, r5, #0x4
	bl AllocFromHeap
	ldr r1, _0201C298 ; =UNK_021C5934
	ldr r2, [r1, #0x0]
	str r0, [r2, #0x8]
	ldr r0, [r1, #0x0]
	mov r2, #0x0
	str r5, [r0, #0x0]
	ldr r0, [r1, #0x0]
	str r2, [r0, #0x4]
	ldr r1, [r1, #0x0]
	ldr r0, [r1, #0x8]
	ldr r1, [r1, #0x0]
	bl NNS_GfdInitVramTransferManager
	pop {r3-r5, pc}
	nop
_0201C298: .word UNK_021C5934

	thumb_func_start FUN_0201C29C
FUN_0201C29C: ; 0x0201C29C
	push {r3, lr}
	ldr r0, _0201C2C4 ; =UNK_021C5934
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	bne _0201C2AA
	bl GF_AssertFail
_0201C2AA:
	ldr r0, _0201C2C4 ; =UNK_021C5934
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x8]
	bl FreeToHeap
	ldr r0, _0201C2C4 ; =UNK_021C5934
	ldr r0, [r0, #0x0]
	bl FreeToHeap
	ldr r0, _0201C2C4 ; =UNK_021C5934
	mov r1, #0x0
	str r1, [r0, #0x0]
	pop {r3, pc}
	.balign 4
_0201C2C4: .word UNK_021C5934

	thumb_func_start FUN_0201C2C8
FUN_0201C2C8: ; 0x0201C2C8
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r0, _0201C308 ; =UNK_021C5934
	add r4, r1, #0x0
	ldr r0, [r0, #0x0]
	add r6, r2, #0x0
	add r7, r3, #0x0
	cmp r0, #0x0
	bne _0201C2DE
	bl GF_AssertFail
_0201C2DE:
	ldr r1, _0201C308 ; =UNK_021C5934
	ldr r0, [r1, #0x0]
	ldr r2, [r0, #0x4]
	add r2, r2, #0x1
	str r2, [r0, #0x4]
	ldr r0, [r1, #0x0]
	ldr r1, [r0, #0x4]
	ldr r0, [r0, #0x0]
	cmp r1, r0
	blo _0201C2FA
	bl GF_AssertFail
	mov r0, #0x0
	pop {r3-r7, pc}
_0201C2FA:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	add r3, r7, #0x0
	bl NNS_GfdRegisterNewVramTransferTask
	pop {r3-r7, pc}
	.balign 4
_0201C308: .word UNK_021C5934

	thumb_func_start FUN_0201C30C
FUN_0201C30C: ; 0x0201C30C
	push {r3, lr}
	ldr r0, _0201C324 ; =UNK_021C5934
	ldr r0, [r0, #0x0]
	cmp r0, #0x0
	beq _0201C322
	bl NNS_GfdDoVramTransfer
	ldr r0, _0201C324 ; =UNK_021C5934
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x4]
_0201C322:
	pop {r3, pc}
	.balign 4
_0201C324: .word UNK_021C5934

	thumb_func_start FUN_0201C328
FUN_0201C328: ; 0x0201C328
	push {r3-r5, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0x30
	mul r1, r4
	bl AllocFromHeap
	ldr r2, _0201C344 ; =FUN_0201C358
	add r1, r4, #0x0
	add r5, r0, #0x0
	bl NNS_G2dInitCellTransferStateManager
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4
_0201C344: .word FUN_0201C358

	thumb_func_start FUN_0201C348
FUN_0201C348: ; 0x0201C348
	ldr r3, _0201C34C ; =NNS_G2dUpdateCellTransferStateManager
	bx r3
	.balign 4
_0201C34C: .word NNS_G2dUpdateCellTransferStateManager

	thumb_func_start FUN_0201C350
FUN_0201C350: ; 0x0201C350
	ldr r3, _0201C354 ; =FreeToHeap
	bx r3
	.balign 4
_0201C354: .word FreeToHeap

	thumb_func_start FUN_0201C358
FUN_0201C358: ; 0x0201C358
	push {r3, lr}
	bl FUN_0201C2C8
	pop {r3, pc}
