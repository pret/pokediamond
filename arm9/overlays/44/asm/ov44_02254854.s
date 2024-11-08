	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov44_02254854
ov44_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x14
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl ov44_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =ov44_022548EC
	add r1, r4, #0
	mov r2, #1
	bl SysTask_CreateOnMainQueue
	cmp r0, #0
	beq _0225488C
	str r4, [r5]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0225488C:
	add r0, r4, #0
	bl FreeToHeap
_02254892:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254898: .word ov44_022548EC
	thumb_func_end ov44_02254854

	thumb_func_start ov44_0225489C
ov44_0225489C: ; 0x0225489C
	push {r4, r5, r6, lr}
	add r4, r1, #0
	add r5, r0, #0
	add r0, r4, #0
	add r6, r2, #0
	bl ov20_02252C3C
	str r0, [r5, #0x10]
	bl Save_Poketch_GetScreenTint
	str r0, [r5, #4]
	strb r0, [r5, #3]
	add r0, r5, #0
	add r0, #8
	add r1, r5, #4
	add r2, r6, #0
	bl ov44_02254A54
	cmp r0, #0
	beq _022548D2
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	str r4, [r5, #0xc]
	mov r0, #1
	pop {r4, r5, r6, pc}
_022548D2:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end ov44_0225489C

	thumb_func_start ov44_022548D8
ov44_022548D8: ; 0x022548D8
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	bl ov44_02254B00
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov44_022548D8

	thumb_func_start ov44_022548EC
ov44_022548EC: ; 0x022548EC
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #3
	bhs _02254918
	lsl r2, r1, #2
	ldr r1, _0225491C ; =ov44_02254C54
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254918
	add r0, r4, #0
	bl ov44_022548D8
	add r0, r5, #0
	bl SysTask_Destroy
	ldr r0, [r4, #0xc]
	bl ov20_022529A0
_02254918:
	pop {r3, r4, r5, pc}
	nop
_0225491C: .word ov44_02254C54
	thumb_func_end ov44_022548EC

	thumb_func_start ov44_02254920
ov44_02254920: ; 0x02254920
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end ov44_02254920

	thumb_func_start ov44_02254928
ov44_02254928: ; 0x02254928
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254930
	b _02254932
_02254930:
	mov r1, #2
_02254932:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end ov44_02254928

	thumb_func_start ov44_0225493C
ov44_0225493C: ; 0x0225493C
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _0225494C
	cmp r0, #1
	beq _0225495C
	b _02254976
_0225494C:
	ldr r0, [r4, #8]
	mov r1, #0
	bl ov44_02254B14
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254976
_0225495C:
	ldr r0, [r4, #8]
	mov r1, #0
	bl ov44_02254B38
	cmp r0, #0
	beq _02254976
	ldr r0, [r4, #0xc]
	bl ov20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl ov44_02254928
_02254976:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov44_0225493C

	thumb_func_start ov44_0225497C
ov44_0225497C: ; 0x0225497C
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254990
	mov r1, #2
	bl ov44_02254928
	mov r0, #0
	pop {r4, pc}
_02254990:
	ldrb r1, [r4, #1]
	cmp r1, #0
	beq _0225499C
	cmp r1, #1
	beq _022549B4
	b _022549C4
_0225499C:
	bl ov44_022549C8
	cmp r0, #0
	beq _022549C4
	ldr r0, [r4, #8]
	mov r1, #2
	bl ov44_02254B14
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549C4
_022549B4:
	ldr r0, [r4, #8]
	mov r1, #2
	bl ov44_02254B38
	cmp r0, #0
	beq _022549C4
	mov r0, #0
	strb r0, [r4, #1]
_022549C4:
	mov r0, #0
	pop {r4, pc}
	thumb_func_end ov44_0225497C

	thumb_func_start ov44_022549C8
ov44_022549C8: ; 0x022549C8
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	bl ov20_02252C08
	cmp r0, #0
	bne _02254A18
	add r0, sp, #4
	add r1, sp, #0
	bl sub_02020AB0
	cmp r0, #0
	beq _02254A18
	ldr r0, [sp]
	cmp r0, #0x88
	blo _02254A18
	cmp r0, #0xa0
	bhs _02254A18
	ldr r0, [sp, #4]
	cmp r0, #0x30
	blo _02254A18
	cmp r0, #0xb8
	bhs _02254A18
	sub r0, #0x30
	lsr r1, r0, #4
	cmp r1, #8
	blo _02254A02
	mov r1, #7
_02254A02:
	ldrb r0, [r4, #3]
	cmp r1, r0
	beq _02254A18
	str r1, [r4, #4]
	strb r1, [r4, #3]
	ldr r0, [r4, #0x10]
	bl Save_Poketch_SetScreenTint
	add sp, #8
	mov r0, #1
	pop {r4, pc}
_02254A18:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov44_022549C8

	thumb_func_start ov44_02254A20
ov44_02254A20: ; 0x02254A20
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A30
	cmp r0, #1
	beq _02254A40
	b _02254A4E
_02254A30:
	ldr r0, [r4, #8]
	mov r1, #1
	bl ov44_02254B14
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A4E
_02254A40:
	ldr r0, [r4, #8]
	bl ov44_02254B44
	cmp r0, #0
	beq _02254A4E
	mov r0, #1
	pop {r4, pc}
_02254A4E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov44_02254A20

	.section .rodata

	.global ov44_02254C54
ov44_02254C54: ; 0x02254C54
	.word ov44_0225493C, ov44_0225497C, ov44_02254A20
