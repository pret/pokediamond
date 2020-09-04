    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02054590
FUN_02054590: ; 0x02054590
	push {r4, lr}
	add r4, r0, #0x0
	cmp r1, #0x1
	bne _0205459C
	bl FUN_0201BD5C
_0205459C:
	mov r1, #0x1a
	add r0, r4, #0x0
	lsl r1, r1, #0x4
	mov r2, #0x4
	bl FUN_02002ED0
	mov r1, #0x6
	add r0, r4, #0x0
	lsl r1, r1, #0x6
	mov r2, #0x4
	bl FUN_02002EEC
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020545B8
FUN_020545B8: ; 0x020545B8
	push {lr}
	sub sp, #0x14
	cmp r2, #0x3
	bne _020545E0
	mov r2, #0x13
	str r2, [sp, #0x0]
	mov r2, #0x1b
	str r2, [sp, #0x4]
	mov r2, #0x4
	str r2, [sp, #0x8]
	mov r2, #0xc
	str r2, [sp, #0xc]
	ldr r2, _02054604 ; =0x0000032D
	mov r3, #0x2
	str r2, [sp, #0x10]
	mov r2, #0x3
	bl FUN_02019064
	add sp, #0x14
	pop {pc}
_020545E0:
	mov r2, #0x13
	str r2, [sp, #0x0]
	mov r2, #0x1b
	str r2, [sp, #0x4]
	mov r2, #0x4
	str r2, [sp, #0x8]
	mov r2, #0xc
	str r2, [sp, #0xc]
	mov r2, #0x65
	lsl r2, r2, #0x2
	str r2, [sp, #0x10]
	mov r2, #0x7
	mov r3, #0x2
	bl FUN_02019064
	add sp, #0x14
	pop {pc}
	nop
_02054604: .word 0x0000032D

	thumb_func_start FUN_02054608
FUN_02054608: ; 0x02054608
	push {r4-r6, lr}
	sub sp, #0x8
	add r4, r1, #0x0
	add r5, r0, #0x0
	bl FUN_0201AB08
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl Options_GetFrame
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	mov r0, #0x4
	str r0, [sp, #0x4]
	ldr r0, [r5, #0x0]
	ldr r2, _02054648 ; =0x000003E2
	add r1, r6, #0x0
	mov r3, #0xa
	bl FUN_0200CD68
	add r0, r5, #0x0
	bl FUN_0205464C
	ldr r2, _02054648 ; =0x000003E2
	add r0, r5, #0x0
	mov r1, #0x0
	mov r3, #0xa
	bl FUN_0200D0BC
	add sp, #0x8
	pop {r4-r6, pc}
	.balign 4
_02054648: .word 0x000003E2

	thumb_func_start FUN_0205464C
FUN_0205464C: ; 0x0205464C
	ldr r3, _02054654 ; =FUN_02019620
	mov r1, #0xf
	bx r3
	nop
_02054654: .word FUN_02019620

	thumb_func_start FUN_02054658
FUN_02054658: ; 0x02054658
	push {r3-r6, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r0, r3, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02002B60
	mov r0, #0x0
	bl FUN_02002B7C
	mov r0, #0x0
	bl FUN_02002BB8
	add r0, r6, #0x0
	bl Options_GetTextFrameDelay
	mov r3, #0x0
	str r3, [sp, #0x0]
	str r0, [sp, #0x4]
	add r0, r5, #0x0
	mov r1, #0x1
	add r2, r4, #0x0
	str r3, [sp, #0x8]
	bl AddTextPrinterParameterized
	add sp, #0xc
	pop {r3-r6, pc}

	thumb_func_start DrawFieldMessage
DrawFieldMessage: ; 0x02054690
	push {r4-r7, lr}
	sub sp, #0xc
	add r5, r0, #0x0
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	add r6, r1, #0x0
	add r7, r2, #0x0
	add r4, r3, #0x0
	bl FUN_02002B60
	ldr r0, [sp, #0x24]
	bl FUN_02002B7C
	mov r0, #0x0
	bl FUN_02002BB8
	mov r3, #0x0
	str r3, [sp, #0x0]
	str r4, [sp, #0x4]
	add r0, r5, #0x0
	add r1, r7, #0x0
	add r2, r6, #0x0
	str r3, [sp, #0x8]
	bl AddTextPrinterParameterized
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start FUN_020546C8
FUN_020546C8: ; 0x020546C8
	push {r3, lr}
	bl FUN_0201BD70
	cmp r0, #0x0
	bne _020546D6
	mov r0, #0x1
	b _020546D8
_020546D6:
	mov r0, #0x0
_020546D8:
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_020546E0
FUN_020546E0: ; 0x020546E0
	push {r4-r5, lr}
	sub sp, #0x14
	cmp r2, #0x1
	bhi _020546EE
	mov r4, #0x9
	mov r5, #0x14
	b _020546F2
_020546EE:
	mov r4, #0x2
	mov r5, #0x1b
_020546F2:
	cmp r3, #0x3
	bne _0205471A
	mov r2, #0x13
	str r2, [sp, #0x0]
	lsl r2, r5, #0x18
	lsr r2, r2, #0x18
	str r2, [sp, #0x4]
	mov r2, #0x4
	str r2, [sp, #0x8]
	mov r2, #0x9
	str r2, [sp, #0xc]
	ldr r2, _02054740 ; =0x0000032D
	lsl r3, r4, #0x18
	str r2, [sp, #0x10]
	mov r2, #0x3
	lsr r3, r3, #0x18
	bl FUN_02019064
	add sp, #0x14
	pop {r4-r5, pc}
_0205471A:
	mov r2, #0x13
	str r2, [sp, #0x0]
	lsl r2, r5, #0x18
	lsr r2, r2, #0x18
	str r2, [sp, #0x4]
	mov r2, #0x4
	str r2, [sp, #0x8]
	mov r2, #0x9
	str r2, [sp, #0xc]
	mov r2, #0x65
	lsl r2, r2, #0x2
	lsl r3, r4, #0x18
	str r2, [sp, #0x10]
	mov r2, #0x7
	lsr r3, r3, #0x18
	bl FUN_02019064
	add sp, #0x14
	pop {r4-r5, pc}
	.balign 4
_02054740: .word 0x0000032D

	thumb_func_start FUN_02054744
FUN_02054744: ; 0x02054744
	push {r3-r6, lr}
	sub sp, #0xc
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r6, r2, #0x0
	bl FUN_0201AB08
	add r1, r0, #0x0
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	str r6, [sp, #0x4]
	mov r0, #0x4
	str r0, [sp, #0x8]
	ldr r0, [r5, #0x0]
	ldr r2, _02054788 ; =0x00000399
	mov r3, #0x9
	bl FUN_0200D300
	add r0, r5, #0x0
	mov r1, #0xf
	bl FUN_02019620
	lsl r0, r4, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	ldr r2, _02054788 ; =0x00000399
	add r0, r5, #0x0
	mov r1, #0x0
	mov r3, #0x9
	bl FUN_0200D6F8
	add sp, #0xc
	pop {r3-r6, pc}
	.balign 4
_02054788: .word 0x00000399
