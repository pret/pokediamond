	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021F61F4
ov05_021F61F4: ; 0x021F61F4
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r5, r0, #0
	add r0, r6, #0
	mov r1, #0x34
	bl AllocFromHeapAtEnd
	add r4, r0, #0
	mov r1, #0
	mov r2, #0x34
	bl memset
	str r6, [r4]
	mov r0, #0
	str r0, [r4, #0xc]
	str r5, [r4, #0x2c]
	ldr r0, [r5, #0x20]
	str r0, [r4, #0x30]
	bl Camera_GetDistance
	str r0, [r4, #0x10]
	str r0, [r4, #0x20]
	ldr r0, _021F622C ; =ov05_021F6270
	ldr r2, _021F6230 ; =0x0000FFFF
	add r1, r4, #0
	bl sub_0200CA44
	pop {r4, r5, r6, pc}
	.align 2, 0
_021F622C: .word ov05_021F6270
_021F6230: .word 0x0000FFFF

	thumb_func_start ov05_021F6234
ov05_021F6234: ; 0x021F6234
	push {r3, lr}
	bl sub_0201B6C8
	ldr r0, [r0, #8]
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov05_021F6240
ov05_021F6240: ; 0x021F6240
	push {r4, lr}
	add r4, r0, #0
	bl sub_0201B6C8
	bl FreeToHeap
	add r0, r4, #0
	bl sub_0200CAB4
	pop {r4, pc}

	thumb_func_start ov05_021F6254
ov05_021F6254: ; 0x021F6254
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r4, r2, #0
	add r6, r3, #0
	bl sub_0201B6C8
	mov r1, #0
	str r1, [r0, #4]
	str r1, [r0, #8]
	str r5, [r0, #0xc]
	str r4, [r0, #0x14]
	str r6, [r0, #0x1c]
	str r1, [r0, #0x24]
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021F6270
ov05_021F6270: ; 0x021F6270
	push {r3, lr}
	add r0, r1, #0
	ldr r1, [r1, #0xc]
	lsl r2, r1, #2
	ldr r1, _021F6280 ; =ov05_021FD1B8
	ldr r1, [r1, r2]
	blx r1
	pop {r3, pc}
	.align 2, 0
_021F6280: .word ov05_021FD1B8

	thumb_func_start ov05_021F6284
ov05_021F6284: ; 0x021F6284
	mov r1, #1
	str r1, [r0, #8]
	bx lr
	.align 2, 0

	thumb_func_start ov05_021F628C
ov05_021F628C: ; 0x021F628C
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021F629C
	cmp r1, #1
	beq _021F62A6
	pop {r4, pc}
_021F629C:
	bl ov05_021F630C
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021F62A6:
	add r0, r4, #0
	bl ov05_021F633C
	cmp r0, #1
	bne _021F62BA
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #1
	str r0, [r4, #8]
_021F62BA:
	add r0, r4, #0
	bl ov05_021F62FC
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov05_021F62C4
ov05_021F62C4: ; 0x021F62C4
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021F62D4
	cmp r1, #1
	beq _021F62DE
	pop {r4, pc}
_021F62D4:
	bl ov05_021F6324
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
_021F62DE:
	add r0, r4, #0
	bl ov05_021F633C
	cmp r0, #1
	bne _021F62F2
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	mov r0, #1
	str r0, [r4, #8]
_021F62F2:
	add r0, r4, #0
	bl ov05_021F62FC
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov05_021F62FC
ov05_021F62FC: ; 0x021F62FC
	ldr r3, _021F6308 ; =sub_0201EFE0
	add r1, r0, #0
	ldr r0, [r1, #0x20]
	ldr r1, [r1, #0x30]
	bx r3
	nop
_021F6308: .word Camera_SetDistance

	thumb_func_start ov05_021F630C
ov05_021F630C: ; 0x021F630C
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0x1c]
	bl _s32_div_f
	str r0, [r4, #0x28]
	ldr r1, [r4, #0x20]
	ldr r0, [r4, #0x14]
	add r0, r1, r0
	str r0, [r4, #0x18]
	pop {r4, pc}

	thumb_func_start ov05_021F6324
ov05_021F6324: ; 0x021F6324
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #0x10]
	ldr r0, [r4, #0x20]
	sub r0, r1, r0
	ldr r1, [r4, #0x1c]
	bl _s32_div_f
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x10]
	str r0, [r4, #0x18]
	pop {r4, pc}

	thumb_func_start ov05_021F633C
ov05_021F633C: ; 0x021F633C
	ldr r2, [r0, #0x20]
	ldr r1, [r0, #0x28]
	add r1, r2, r1
	str r1, [r0, #0x20]
	ldr r1, [r0, #0x24]
	add r2, r1, #1
	str r2, [r0, #0x24]
	ldr r1, [r0, #0x1c]
	cmp r2, r1
	blo _021F635A
	str r1, [r0, #0x24]
	ldr r1, [r0, #0x18]
	str r1, [r0, #0x20]
	mov r0, #1
	bx lr
_021F635A:
	mov r0, #0
	bx lr
	.align 2, 0

	.section .rodata

	.global ov05_021FD1B8
ov05_021FD1B8: ; 0x021FD1B8
	.word ov05_021F6284, ov05_021F628C, ov05_021F62C4, 0x00000000
