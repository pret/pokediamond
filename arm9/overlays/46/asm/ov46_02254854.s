	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov46_02254854
ov46_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x10
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl ov46_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =ov46_022548D4
	add r1, r4, #0
	mov r2, #1
	bl sub_0200CA44
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
_02254898: .word ov46_022548D4
	thumb_func_end ov46_02254854

	thumb_func_start ov46_0225489C
ov46_0225489C: ; 0x0225489C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r0, #8
	add r1, r5, #4
	bl ov46_022549AC
	cmp r0, #0
	beq _022548BC
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	str r4, [r5, #0xc]
	mov r0, #1
	pop {r3, r4, r5, pc}
_022548BC:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end ov46_0225489C

	thumb_func_start ov46_022548C0
ov46_022548C0: ; 0x022548C0
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	bl ov46_022549DC
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov46_022548C0

	thumb_func_start ov46_022548D4
ov46_022548D4: ; 0x022548D4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #3
	bhs _02254900
	lsl r2, r1, #2
	ldr r1, _02254904 ; =ov46_02254AF4
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254900
	add r0, r4, #0
	bl ov46_022548C0
	add r0, r5, #0
	bl sub_0200CAB4
	ldr r0, [r4, #0xc]
	bl ov20_022529A0
_02254900:
	pop {r3, r4, r5, pc}
	nop
_02254904: .word ov46_02254AF4
	thumb_func_end ov46_022548D4

	thumb_func_start ov46_02254908
ov46_02254908: ; 0x02254908
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end ov46_02254908

	thumb_func_start ov46_02254910
ov46_02254910: ; 0x02254910
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254918
	b _0225491A
_02254918:
	mov r1, #2
_0225491A:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end ov46_02254910

	thumb_func_start ov46_02254924
ov46_02254924: ; 0x02254924
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254934
	cmp r0, #1
	beq _02254944
	b _0225495E
_02254934:
	ldr r0, [r4, #8]
	mov r1, #0
	bl ov46_022549E8
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _0225495E
_02254944:
	ldr r0, [r4, #8]
	mov r1, #0
	bl ov46_02254A0C
	cmp r0, #0
	beq _0225495E
	ldr r0, [r4, #0xc]
	bl ov20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl ov46_02254910
_0225495E:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov46_02254924

	thumb_func_start ov46_02254964
ov46_02254964: ; 0x02254964
	push {r3, lr}
	ldrb r1, [r0, #2]
	cmp r1, #0
	beq _02254972
	mov r1, #2
	bl ov46_02254910
_02254972:
	mov r0, #0
	pop {r3, pc}
	.align 2, 0
	thumb_func_end ov46_02254964

	thumb_func_start ov46_02254978
ov46_02254978: ; 0x02254978
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254988
	cmp r0, #1
	beq _02254998
	b _022549A6
_02254988:
	ldr r0, [r4, #8]
	mov r1, #1
	bl ov46_022549E8
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549A6
_02254998:
	ldr r0, [r4, #8]
	bl ov46_02254A18
	cmp r0, #0
	beq _022549A6
	mov r0, #1
	pop {r4, pc}
_022549A6:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end ov46_02254978

	.section .rodata

	.global ov46_02254AF4
ov46_02254AF4: ; 0x02254AF4
	.word ov46_02254924, ov46_02254964, ov46_02254978
