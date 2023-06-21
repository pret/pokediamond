	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov26_02254BD4
ov26_02254BD4: ; 0x02254BD4
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x30
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254C00
	add r0, #8
	mov r1, #8
	bl ov20_022536F4
	str r6, [r4]
	bl ov20_02252D34
	str r0, [r4, #4]
	cmp r0, #0
	beq _02254C00
	str r4, [r5]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254C00:
	mov r0, #0
	pop {r4, r5, r6, pc}
	thumb_func_end ov26_02254BD4

	thumb_func_start ov26_02254C04
ov26_02254C04: ; 0x02254C04
	push {r3, lr}
	cmp r0, #0
	beq _02254C0E
	bl FreeToHeap
_02254C0E:
	pop {r3, pc}
	thumb_func_end ov26_02254C04

	thumb_func_start ov26_02254C10
ov26_02254C10: ; 0x02254C10
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254C30 ; =ov26_02254FF0
	ldr r3, [r2]
	bl ov20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254C30: .word ov26_02254FF0
	thumb_func_end ov26_02254C10

	thumb_func_start ov26_02254C34
ov26_02254C34: ; 0x02254C34
	ldr r3, _02254C3C ; =ov20_02253794
	add r0, #8
	bx r3
	nop
_02254C3C: .word ov20_02253794
	thumb_func_end ov26_02254C34

	thumb_func_start ov26_02254C40
ov26_02254C40: ; 0x02254C40
	ldr r3, _02254C48 ; =ov20_022537B8
	add r0, #8
	bx r3
	nop
_02254C48: .word ov20_022537B8
	thumb_func_end ov26_02254C40

	thumb_func_start ov26_02254C4C
ov26_02254C4C: ; 0x02254C4C
	push {r4, lr}
	add r4, r0, #0
	bl ov20_022538A0
	add r0, #8
	add r1, r4, #0
	bl ov20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov26_02254C4C

	thumb_func_start ov26_02254C60
ov26_02254C60: ; 0x02254C60
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl ov20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254CB8 ; =ov26_02254FD4
	mov r1, #6
	mov r3, #0
	bl InitBgFromTemplate
	ldr r0, [r5, #4]
	bl ov26_02254CC4
	ldr r0, [r5, #4]
	ldr r1, [r5]
	bl ov26_02254DAC
	mov r0, #0
	add r1, r0, #0
	bl ov20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl BgCommitTilemapBufferToVram
	ldr r1, _02254CBC ; =0x04001000
	ldr r0, _02254CC0 ; =0xFFFFE0FF
	ldr r3, [r1]
	ldr r2, [r1]
	str r3, [sp]
	and r0, r2
	lsl r2, r3, #0x13
	lsr r3, r2, #0x1b
	mov r2, #4
	orr r2, r3
	lsl r2, r2, #8
	orr r0, r2
	str r0, [r1]
	add r0, r4, #0
	bl ov26_02254C4C
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254CB8: .word ov26_02254FD4
_02254CBC: .word 0x04001000
_02254CC0: .word 0xFFFFE0FF
	thumb_func_end ov26_02254C60

	thumb_func_start ov26_02254CC4
ov26_02254CC4: ; 0x02254CC4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp, #4]
	mov r0, #8
	lsl r1, r0, #6
	bl AllocFromHeap
	str r0, [sp, #0x1c]
	cmp r0, #0
	beq _02254D68
	mov r0, #0
	str r0, [sp, #0x18]
	str r0, [sp, #0x14]
	str r0, [sp, #0x10]
	str r0, [sp, #0xc]
	str r0, [sp, #8]
	add r7, r0, #0
	add r6, r0, #0
	add r4, r0, #0
	add r5, r0, #0
_02254CEC:
	ldr r1, [sp, #0xc]
	ldr r0, [sp, #0x10]
	ldr r2, [sp, #0x1c]
	orr r1, r0
	ldr r0, [sp, #8]
	orr r0, r1
	orr r0, r7
	orr r0, r6
	orr r0, r4
	add r1, r5, #0
	orr r1, r0
	ldr r0, [sp, #0x18]
	orr r0, r1
	ldr r1, [sp, #0x14]
	add r1, r2, r1
	mov r2, #0x20
	bl MIi_CpuClearFast
	ldr r0, [sp, #0x14]
	ldr r1, [sp, #0x10]
	add r0, #0x20
	str r0, [sp, #0x14]
	mov r0, #1
	lsl r0, r0, #0x18
	add r0, r1, r0
	str r0, [sp, #0x10]
	mov r0, #1
	ldr r1, [sp, #0xc]
	lsl r0, r0, #0x1c
	add r0, r1, r0
	str r0, [sp, #0xc]
	mov r0, #1
	ldr r1, [sp, #8]
	lsl r0, r0, #0x14
	add r0, r1, r0
	str r0, [sp, #8]
	mov r0, #1
	lsl r0, r0, #0x10
	add r7, r7, r0
	lsr r0, r0, #4
	add r6, r6, r0
	mov r0, #1
	lsl r0, r0, #8
	add r4, r4, r0
	ldr r0, [sp, #0x18]
	add r5, #0x10
	add r0, r0, #1
	str r0, [sp, #0x18]
	cmp r0, #0x10
	blt _02254CEC
	mov r0, #0
	str r0, [sp]
	mov r3, #2
	ldr r0, [sp, #4]
	ldr r2, [sp, #0x1c]
	mov r1, #6
	lsl r3, r3, #8
	bl BG_LoadCharTilesData
	ldr r0, [sp, #0x1c]
	bl FreeToHeap
_02254D68:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end ov26_02254CC4

	thumb_func_start ov26_02254D6C
ov26_02254D6C: ; 0x02254D6C
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl ov20_022538A0
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r1, [r4]
	bl ov26_02254DAC
	ldr r0, [r4, #4]
	mov r1, #6
	bl BgCommitTilemapBufferToVram
	add r0, r5, #0
	bl ov26_02254C4C
	pop {r3, r4, r5, pc}
	thumb_func_end ov26_02254D6C

	thumb_func_start ov26_02254D90
ov26_02254D90: ; 0x02254D90
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl ov20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FreeBgTilemapBuffer
	add r0, r4, #0
	bl ov26_02254C4C
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov26_02254D90

	thumb_func_start ov26_02254DAC
ov26_02254DAC: ; 0x02254DAC
	push {r3, r4, r5, r6, r7, lr}
	add r4, r1, #0
	mov r1, #6
	bl GetBgTilemapBuffer
	mov r5, #0
	ldr r1, _02254DE0 ; =ov26_02254FD0
	add r0, #0x84
	add r2, r5, #0
_02254DBE:
	add r3, r2, #0
	add r6, r0, #0
_02254DC2:
	ldrb r7, [r4, r3]
	add r3, r3, #1
	add r7, r1, r7
	sub r7, r7, #1
	ldrb r7, [r7]
	strh r7, [r6]
	add r6, r6, #2
	cmp r3, #0x18
	blt _02254DC2
	add r5, r5, #1
	add r0, #0x40
	add r4, #0x18
	cmp r5, #0x14
	blt _02254DBE
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254DE0: .word ov26_02254FD0
	thumb_func_end ov26_02254DAC

	.section .rodata

	.global ov26_02254FD0
ov26_02254FD0: ; 0x02254FD0
	.byte 0x04, 0x0F, 0x08, 0x01

	.global ov26_02254FD4
ov26_02254FD4: ; 0x02254FD4
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global ov26_02254FF0
ov26_02254FF0: ; 0x02254FF0
	.word 0x00, ov26_02254C60, 0x00
	.word 0x01, ov26_02254D6C, 0x00
	.word 0x02, ov26_02254D90, 0x00
	.word 0x00, 0x00000000, 0x00
