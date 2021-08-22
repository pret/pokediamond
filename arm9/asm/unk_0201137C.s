	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_02011480
FUN_02011480: ; 0x02011480
	cmp r1, #0x0
	ldr r1, _020114A4 ; =0xFFFF1FFF
	bne _02011496
	mov r3, #0x1
	lsl r3, r3, #0x1a
	ldr r2, [r3, #0x0]
	lsl r0, r0, #0xd
	and r1, r2
	orr r0, r1
	str r0, [r3, #0x0]
	bx lr
_02011496:
	ldr r3, _020114A8 ; =0x04001000
	lsl r0, r0, #0xd
	ldr r2, [r3, #0x0]
	and r1, r2
	orr r0, r1
	str r0, [r3, #0x0]
	bx lr
	.balign 4
_020114A4: .word 0xFFFF1FFF
_020114A8: .word 0x04001000

	thumb_func_start FUN_020114AC
FUN_020114AC: ; 0x020114AC
	push {r3-r4}
	cmp r2, #0x0
	bne _020114EE
	cmp r3, #0x0
	bne _020114D2
	ldr r2, _02011528 ; =0x04000048
	ldrh r3, [r2, #0x0]
	mov r2, #0x3f
	bic r3, r2
	add r2, r3, #0x0
	orr r2, r0
	cmp r1, #0x0
	beq _020114CA
	mov r0, #0x20
	orr r2, r0
_020114CA:
	ldr r0, _02011528 ; =0x04000048
	strh r2, [r0, #0x0]
	pop {r3-r4}
	bx lr
_020114D2:
	ldr r2, _0201152C ; =0x04001048
	ldrh r3, [r2, #0x0]
	mov r2, #0x3f
	bic r3, r2
	add r2, r3, #0x0
	orr r2, r0
	cmp r1, #0x0
	beq _020114E6
	mov r0, #0x20
	orr r2, r0
_020114E6:
	ldr r0, _0201152C ; =0x04001048
	strh r2, [r0, #0x0]
	pop {r3-r4}
	bx lr
_020114EE:
	cmp r3, #0x0
	ldr r2, _02011530 ; =0xFFFFC0FF
	bne _0201150E
	ldr r4, _02011528 ; =0x04000048
	lsl r0, r0, #0x8
	ldrh r3, [r4, #0x0]
	and r2, r3
	orr r2, r0
	cmp r1, #0x0
	beq _02011506
	lsr r0, r4, #0xd
	orr r2, r0
_02011506:
	ldr r0, _02011528 ; =0x04000048
	strh r2, [r0, #0x0]
	pop {r3-r4}
	bx lr
_0201150E:
	ldr r4, _0201152C ; =0x04001048
	lsl r0, r0, #0x8
	ldrh r3, [r4, #0x0]
	and r2, r3
	orr r2, r0
	cmp r1, #0x0
	beq _02011520
	lsr r0, r4, #0xd
	orr r2, r0
_02011520:
	ldr r0, _0201152C ; =0x04001048
	strh r2, [r0, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4
_02011528: .word 0x04000048
_0201152C: .word 0x04001048
_02011530: .word 0xFFFFC0FF

	thumb_func_start FUN_02011534
FUN_02011534: ; 0x02011534
	cmp r2, #0x0
	bne _02011552
	ldr r2, _0201156C ; =0x0400004A
	ldrh r3, [r2, #0x0]
	mov r2, #0x3f
	bic r3, r2
	add r2, r3, #0x0
	orr r2, r0
	cmp r1, #0x0
	beq _0201154C
	mov r0, #0x20
	orr r2, r0
_0201154C:
	ldr r0, _0201156C ; =0x0400004A
	strh r2, [r0, #0x0]
	bx lr
_02011552:
	ldr r2, _02011570 ; =0x0400104A
	ldrh r3, [r2, #0x0]
	mov r2, #0x3f
	bic r3, r2
	add r2, r3, #0x0
	orr r2, r0
	cmp r1, #0x0
	beq _02011566
	mov r0, #0x20
	orr r2, r0
_02011566:
	ldr r0, _02011570 ; =0x0400104A
	strh r2, [r0, #0x0]
	bx lr
	.balign 4
_0201156C: .word 0x0400004A
_02011570: .word 0x0400104A

	thumb_func_start FUN_02011574
FUN_02011574: ; 0x02011574
	push {r4-r5}
	add r4, r2, #0x0
	add r2, r3, #0x0
	ldr r3, [sp, #0x8]
	cmp r3, #0x0
	bne _020115D2
	ldr r3, [sp, #0xc]
	cmp r3, #0x0
	bne _020115AC
	lsl r0, r0, #0x8
	mov r3, #0xff
	add r5, r0, #0x0
	lsl r3, r3, #0x8
	lsl r0, r4, #0x18
	and r5, r3
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	add r4, r5, #0x0
	orr r4, r0
	ldr r0, _02011624 ; =0x04000040
	orr r1, r3
	strh r4, [r0, #0x0]
	strh r1, [r0, #0x4]
	pop {r4-r5}
	bx lr
_020115AC:
	lsl r0, r0, #0x8
	mov r3, #0xff
	add r5, r0, #0x0
	lsl r3, r3, #0x8
	lsl r0, r4, #0x18
	and r5, r3
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	add r4, r5, #0x0
	orr r4, r0
	ldr r0, _02011628 ; =0x04001040
	orr r1, r3
	strh r4, [r0, #0x0]
	strh r1, [r0, #0x4]
	pop {r4-r5}
	bx lr
_020115D2:
	ldr r3, [sp, #0xc]
	cmp r3, #0x0
	bne _020115FE
	lsl r0, r0, #0x8
	mov r3, #0xff
	add r5, r0, #0x0
	lsl r3, r3, #0x8
	lsl r0, r4, #0x18
	and r5, r3
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	add r4, r5, #0x0
	orr r4, r0
	ldr r0, _0201162C ; =0x04000042
	orr r1, r3
	strh r4, [r0, #0x0]
	strh r1, [r0, #0x4]
	pop {r4-r5}
	bx lr
_020115FE:
	lsl r0, r0, #0x8
	mov r3, #0xff
	add r5, r0, #0x0
	lsl r3, r3, #0x8
	lsl r0, r4, #0x18
	and r5, r3
	lsl r1, r1, #0x8
	and r3, r1
	lsl r1, r2, #0x18
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	add r4, r5, #0x0
	orr r4, r0
	ldr r0, _02011630 ; =0x04001042
	orr r1, r3
	strh r4, [r0, #0x0]
	strh r1, [r0, #0x4]
	pop {r4-r5}
	bx lr
	.balign 4
_02011624: .word 0x04000040
_02011628: .word 0x04001040
_0201162C: .word 0x04000042
_02011630: .word 0x04001042

	thumb_func_start FUN_02011634
FUN_02011634: ; 0x02011634
	push {r4, lr}
	lsl r3, r2, #0x3
	add r4, r0, r3
	str r1, [r0, r3]
	str r2, [r4, #0x4]
	ldr r0, _0201164C ; =FUN_020116CC
	add r1, r4, #0x0
	mov r2, #0x1
	bl FUN_0200CA98
	pop {r4, pc}
	nop
_0201164C: .word FUN_020116CC

	thumb_func_start FUN_02011650
FUN_02011650: ; 0x02011650
	push {r4-r6, lr}
	ldr r5, [sp, #0x10]
	add r0, #0x10
	lsl r4, r5, #0x5
	add r6, r0, r4
	lsl r0, r3, #0x4
	add r4, r6, r0
	str r1, [r6, r0]
	str r2, [r4, #0x4]
	str r3, [r4, #0x8]
	ldr r0, _02011674 ; =FUN_020116E0
	add r1, r4, #0x0
	mov r2, #0x1
	str r5, [r4, #0xc]
	bl FUN_0200CA98
	pop {r4-r6, pc}
	nop
_02011674: .word FUN_020116E0

	thumb_func_start FUN_02011678
FUN_02011678: ; 0x02011678
	push {r3-r5, lr}
	mov r4, #0xc
	add r0, #0x68
	mul r4, r3
	add r5, r0, r4
	str r1, [r0, r4]
	str r2, [r5, #0x4]
	ldr r0, _02011694 ; =FUN_020116FC
	add r1, r5, #0x0
	mov r2, #0x1
	str r3, [r5, #0x8]
	bl FUN_0200CA98
	pop {r3-r5, pc}
	.balign 4
_02011694: .word FUN_020116FC

	thumb_func_start FUN_02011698
FUN_02011698: ; 0x02011698
	push {r3-r7, lr}
	ldr r5, [sp, #0x20]
	add r7, r1, #0x0
	add r0, #0x80
	lsl r1, r5, #0x5
	add r6, r0, r1
	add r4, r2, #0x0
	ldr r0, [sp, #0x1c]
	add r2, r3, #0x0
	lsl r3, r0, #0x4
	add r1, r6, r3
	strh r7, [r6, r3]
	strh r4, [r1, #0x2]
	strh r2, [r1, #0x4]
	ldr r2, [sp, #0x18]
	strh r2, [r1, #0x6]
	str r0, [r1, #0x8]
	ldr r0, _020116C8 ; =FUN_02011714
	mov r2, #0x1
	str r5, [r1, #0xc]
	bl FUN_0200CA98
	pop {r3-r7, pc}
	nop
_020116C8: .word FUN_02011714

	thumb_func_start FUN_020116CC
FUN_020116CC: ; 0x020116CC
	push {r4, lr}
	add r4, r0, #0x0
	ldmia r1!, {r0-r1}
	bl FUN_02011480
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020116E0
FUN_020116E0: ; 0x020116E0
	push {r4, lr}
	add r3, r1, #0x0
	add r4, r0, #0x0
	ldr r0, [r3, #0x0]
	ldr r1, [r3, #0x4]
	ldr r2, [r3, #0x8]
	ldr r3, [r3, #0xc]
	bl FUN_020114AC
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_020116FC
FUN_020116FC: ; 0x020116FC
	push {r4, lr}
	add r2, r1, #0x0
	add r4, r0, #0x0
	ldr r0, [r2, #0x0]
	ldr r1, [r2, #0x4]
	ldr r2, [r2, #0x8]
	bl FUN_02011534
	add r0, r4, #0x0
	bl FUN_0200CAB4
	pop {r4, pc}

	thumb_func_start FUN_02011714
FUN_02011714: ; 0x02011714
	push {r3-r5, lr}
	sub sp, #0x8
	add r3, r1, #0x0
	add r4, r0, #0x0
	ldr r0, [r3, #0x8]
	mov r1, #0x2
	str r0, [sp, #0x0]
	ldr r0, [r3, #0xc]
	mov r2, #0x4
	str r0, [sp, #0x4]
	mov r0, #0x0
	mov r5, #0x6
	ldrsh r0, [r3, r0]
	ldrsh r1, [r3, r1]
	ldrsh r2, [r3, r2]
	ldrsh r3, [r3, r5]
	bl FUN_02011574
	add r0, r4, #0x0
	bl FUN_0200CAB4
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4
