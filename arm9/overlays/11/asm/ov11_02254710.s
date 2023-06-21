	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov11_02254710
ov11_02254710: ; 0x02254710
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r0, #0
	str r1, [sp]
	str r2, [sp, #4]
	add r6, r3, #0
	bl ov11_022300DC
	add r4, r0, #0
	add r0, r7, #0
	bl ov11_02230118
	add r5, r0, #0
	add r0, r7, #0
	bl ov11_02230124
	add r7, r0, #0
	add r0, sp, #0x10
	ldrh r2, [r5]
	ldrb r3, [r0, #0x10]
	add r0, r2, #5
	add r1, r0, r3
	mov r0, #1
	lsl r0, r0, #0xc
	cmp r1, r0
	bls _0225474A
	strh r2, [r7]
	mov r0, #0
	strh r0, [r5]
_0225474A:
	ldr r1, [sp]
	add r0, sp, #8
	strb r1, [r0]
	ldr r1, [sp, #4]
	strb r1, [r0, #1]
	add r1, sp, #0x10
	ldrb r1, [r1, #0x10]
	strh r1, [r0, #2]
	add r1, sp, #8
	mov r0, #0
_0225475E:
	ldrb r7, [r1, r0]
	ldrh r2, [r5]
	add r0, r0, #1
	strb r7, [r4, r2]
	ldrh r2, [r5]
	add r2, r2, #1
	strh r2, [r5]
	cmp r0, #4
	blo _0225475E
	mov r0, #0
	cmp r3, #0
	ble _02254788
_02254776:
	ldrb r2, [r6, r0]
	ldrh r1, [r5]
	add r0, r0, #1
	strb r2, [r4, r1]
	ldrh r1, [r5]
	add r1, r1, #1
	strh r1, [r5]
	cmp r0, r3
	blt _02254776
_02254788:
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov11_0225478C
ov11_0225478C: ; 0x0225478C
	push {r3, r4, r5, r6, r7, lr}
	add r3, r1, #0
	ldrb r6, [r3, #3]
	ldrb r1, [r3]
	ldrb r7, [r3, #2]
	lsl r6, r6, #8
	add r5, r0, #0
	mov r2, #0
	orr r6, r7
	ldrb r4, [r3, #1]
	cmp r1, #0
	bne _022547D2
	ldr r0, [r5, #0x30]
	lsl r1, r4, #8
	add r4, r0, r1
	mov r0, #0x23
	lsl r0, r0, #8
	ldrb r0, [r4, r0]
	cmp r0, #0
	bne _0225481C
	cmp r6, #0
	ble _022547CE
	mov r4, #0x23
	lsl r4, r4, #8
_022547BC:
	add r0, r3, r2
	ldr r7, [r5, #0x30]
	ldrb r0, [r0, #4]
	add r7, r1, r7
	add r7, r2, r7
	add r2, r2, #1
	strb r0, [r7, r4]
	cmp r2, r6
	blt _022547BC
_022547CE:
	mov r2, #1
	b _0225481C
_022547D2:
	cmp r1, #1
	bne _022547FE
	lsl r0, r4, #2
	add r0, r5, r0
	ldr r1, [r0, #0x34]
	add r1, #0x94
	ldrb r1, [r1]
	cmp r1, #0
	bne _0225481C
	cmp r6, #0
	ble _022547FA
_022547E8:
	add r1, r3, r2
	ldrb r4, [r1, #4]
	ldr r1, [r0, #0x34]
	add r1, r1, r2
	add r1, #0x94
	add r2, r2, #1
	strb r4, [r1]
	cmp r2, r6
	blt _022547E8
_022547FA:
	mov r2, #1
	b _0225481C
_022547FE:
	cmp r1, #2
	bne _0225481C
	ldrb r7, [r3, #4]
	ldrb r6, [r3, #5]
	bl ov11_02230DD4
	cmp r0, #0
	beq _0225481A
	ldr r0, [r5, #0x30]
	add r1, r6, #0
	add r2, r4, #0
	add r3, r7, #0
	bl ov11_02243340
_0225481A:
	mov r2, #1
_0225481C:
	add r0, r2, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_02254820
ov11_02254820: ; 0x02254820
	push {r3, r4, r5, r6, r7, lr}
	add r6, r0, #0
	bl ov11_022300DC
	add r4, r0, #0
	add r0, r6, #0
	bl ov11_0223010C
	add r5, r0, #0
	add r0, r6, #0
	bl ov11_02230118
	add r7, r0, #0
	add r0, r6, #0
	bl ov11_02230124
	ldrh r1, [r5]
	ldrh r2, [r7]
	cmp r1, r2
	beq _02254876
	ldrh r2, [r0]
	cmp r1, r2
	bne _02254854
	mov r1, #0
	strh r1, [r5]
	strh r1, [r0]
_02254854:
	ldrh r1, [r5]
	add r0, r6, #0
	add r1, r4, r1
	bl ov11_0225478C
	cmp r0, #1
	bne _02254876
	ldrh r0, [r5]
	add r1, r0, #2
	ldrb r2, [r4, r1]
	add r1, r0, #3
	ldrb r1, [r4, r1]
	lsl r1, r1, #8
	orr r1, r2
	add r1, r1, #4
	add r0, r0, r1
	strh r0, [r5]
_02254876:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_02254878
ov11_02254878: ; 0x02254878
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r0, #0
	str r1, [sp, #4]
	ldr r1, [r5, #0x2c]
	mov r0, #4
	add r7, r2, #0
	add r6, r3, #0
	tst r0, r1
	beq _022548C8
	ldr r0, [sp, #4]
	cmp r0, #1
	bne _022548B2
	mov r4, #0
	bl sub_02030F20
	cmp r0, #0
	ble _022548B2
_0225489C:
	ldrb r3, [r6]
	ldr r0, [r5, #0x30]
	add r1, r4, #0
	add r2, r7, #0
	bl ov11_02243304
	add r4, r4, #1
	bl sub_02030F20
	cmp r4, r0
	blt _0225489C
_022548B2:
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	ldr r1, [sp, #4]
	add r2, r7, #0
	str r0, [sp]
	add r0, r5, #0
	add r3, r6, #0
	bl sub_0206C0C8
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
_022548C8:
	ldr r0, [sp, #4]
	cmp r0, #1
	bne _022548D8
	ldrb r3, [r6]
	ldr r0, [r5, #0x30]
	mov r1, #0
	bl ov11_02243304
_022548D8:
	add r0, sp, #0x10
	ldrb r0, [r0, #0x10]
	ldr r1, [sp, #4]
	add r2, r7, #0
	str r0, [sp]
	add r0, r5, #0
	add r3, r6, #0
	bl ov11_02254710
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0

	thumb_func_start ov11_022548F0
ov11_022548F0: ; 0x022548F0
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #1
	str r1, [sp, #4]
	mov r3, #4
	str r3, [sp]
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}

	thumb_func_start ov11_02254908
ov11_02254908: ; 0x02254908
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x48
	add r7, r1, #0
	mov r3, #2
	add r2, sp, #0xc
	strb r3, [r2]
	mov r2, #0xc0
	add r4, r7, #0
	mul r4, r2
	add r2, sp, #0xc
	ldrb r2, [r2, #1]
	mov r3, #3
	add r6, r0, #0
	str r2, [sp, #4]
	bic r2, r3
	str r2, [sp, #4]
	ldr r2, [r6, #0x30]
	add r3, r2, r4
	ldr r2, _02254A04 ; =0x00002DBE
	str r2, [sp, #8]
	ldrb r2, [r3, r2]
	lsl r2, r2, #0x1c
	lsr r3, r2, #0x1c
	mov r2, #3
	and r3, r2
	ldr r2, [sp, #4]
	orr r3, r2
	add r2, sp, #0xc
	strb r3, [r2, #1]
	ldrb r3, [r2, #1]
	mov r2, #4
	bic r3, r2
	ldr r2, [r6, #0x30]
	add r5, r2, r4
	ldr r2, [sp, #8]
	sub r2, #0x58
	ldrb r2, [r5, r2]
	lsl r2, r2, #0x1a
	lsr r2, r2, #0x1f
	lsl r2, r2, #0x1f
	lsr r2, r2, #0x1d
	orr r3, r2
	add r2, sp, #0xc
	strb r3, [r2, #1]
	ldr r2, [r6, #0x30]
	add r3, r2, r4
	ldr r2, [sp, #8]
	sub r2, #0x7e
	ldrh r3, [r3, r2]
	add r2, sp, #0xc
	strh r3, [r2, #2]
	ldr r2, [r6, #0x30]
	add r3, r2, r4
	ldr r2, [sp, #8]
	sub r2, #0x16
	str r2, [sp, #8]
	ldr r2, [r3, r2]
	str r2, [sp, #0x10]
	bl ov11_02230260
	add r2, r0, #0
	ldr r0, [r6, #0x30]
	add r1, r7, #0
	mov r3, #1
	bl ov11_0224ACAC
	add r2, sp, #0xc
	str r0, [sp, #0x14]
	ldrb r0, [r2, #1]
	mov r1, #0xf8
	add r5, sp, #0xc
	bic r0, r1
	ldr r1, [r6, #0x30]
	add r3, r1, r4
	ldr r1, _02254A08 ; =0x00002D66
	mov r4, #0
	ldrb r1, [r3, r1]
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x1b
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x18
	orr r0, r1
	strb r0, [r2, #1]
_022549AE:
	ldr r0, [r6, #0x30]
	add r1, r7, #0
	add r2, r4, #6
	mov r3, #0
	bl ov11_02243420
	strh r0, [r5, #0xc]
	add r2, r4, #0
	ldr r0, [r6, #0x30]
	add r1, r7, #0
	add r2, #0x1f
	mov r3, #0
	bl ov11_02243420
	strh r0, [r5, #0x14]
	add r2, r4, #0
	ldr r0, [r6, #0x30]
	add r1, r7, #0
	add r2, #0x27
	mov r3, #0
	bl ov11_02243420
	strh r0, [r5, #0x1c]
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, #4
	blt _022549AE
	ldr r0, [r6, #0x30]
	add r1, r7, #0
	mov r2, #0x2d
	add r3, sp, #0x30
	bl ov11_02243420
	mov r0, #0x3c
	str r0, [sp]
	add r0, r6, #0
	mov r1, #1
	add r2, r7, #0
	add r3, sp, #0xc
	bl ov11_02254878
	add sp, #0x48
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254A04: .word 0x00002DBE
_02254A08: .word 0x00002D66

	thumb_func_start ov11_02254A0C
ov11_02254A0C: ; 0x02254A0C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x7c
	add r7, r1, #0
	mov r3, #3
	add r2, sp, #8
	strb r3, [r2]
	mov r2, #0xc0
	add r4, r7, #0
	mul r4, r2
	add r2, sp, #8
	ldrb r5, [r2, #1]
	mov r2, #3
	add r6, r0, #0
	bic r5, r2
	ldr r2, [r6, #0x30]
	add r3, r2, r4
	ldr r2, _02254B34 ; =0x00002DBE
	str r2, [sp, #4]
	ldrb r2, [r3, r2]
	lsl r2, r2, #0x1c
	lsr r3, r2, #0x1c
	mov r2, #3
	and r2, r3
	add r3, r5, #0
	orr r3, r2
	add r2, sp, #8
	strb r3, [r2, #1]
	ldrb r3, [r2, #1]
	mov r2, #4
	bic r3, r2
	ldr r2, [r6, #0x30]
	add r5, r2, r4
	ldr r2, [sp, #4]
	sub r2, #0x58
	ldrb r2, [r5, r2]
	lsl r2, r2, #0x1a
	lsr r2, r2, #0x1f
	lsl r2, r2, #0x1f
	lsr r2, r2, #0x1d
	orr r3, r2
	add r2, sp, #8
	strb r3, [r2, #1]
	ldr r2, [r6, #0x30]
	add r3, r2, r4
	ldr r2, [sp, #4]
	sub r2, #0x7e
	ldrh r3, [r3, r2]
	add r2, sp, #8
	strh r3, [r2, #2]
	ldr r2, [r6, #0x30]
	add r3, r2, r4
	ldr r2, [sp, #4]
	sub r2, #0x16
	str r2, [sp, #4]
	ldr r2, [r3, r2]
	str r2, [sp, #0xc]
	bl ov11_02230260
	add r2, r0, #0
	ldr r0, [r6, #0x30]
	add r1, r7, #0
	mov r3, #1
	bl ov11_0224ACAC
	str r0, [sp, #0x10]
	ldr r0, [r6, #0x30]
	add r2, sp, #8
	add r1, r0, r7
	ldr r0, _02254B38 ; =0x0000219C
	ldrb r0, [r1, r0]
	mov r1, #0xf8
	str r0, [sp, #0x14]
	ldrb r0, [r2, #1]
	bic r0, r1
	ldr r1, [r6, #0x30]
	add r3, r1, r4
	ldr r1, _02254B3C ; =0x00002D66
	ldrb r3, [r3, r1]
	add r1, #0x59
	lsl r3, r3, #0x1b
	lsr r3, r3, #0x1b
	lsl r3, r3, #0x1b
	lsr r3, r3, #0x18
	orr r0, r3
	strb r0, [r2, #1]
	ldr r0, [r6, #0x30]
	add r0, r0, r4
	ldrb r0, [r0, r1]
	add r1, r7, #0
	str r0, [sp, #0x18]
	add r0, r6, #0
	bl ov11_022302BC
	ldr r1, [r6, #0x30]
	ldr r2, [sp, #0x14]
	add r1, r1, r0
	ldr r0, _02254B38 ; =0x0000219C
	ldrb r0, [r1, r0]
	add r1, r7, #0
	str r0, [sp, #0x50]
	add r0, r6, #0
	bl ov11_02230F6C
	mov r4, #0
	add r5, sp, #8
_02254ADE:
	ldr r0, [r6, #0x30]
	add r1, r7, #0
	add r2, r4, #6
	mov r3, #0
	bl ov11_02243420
	strh r0, [r5, #0x18]
	add r2, r4, #0
	ldr r0, [r6, #0x30]
	add r1, r7, #0
	add r2, #0x1f
	mov r3, #0
	bl ov11_02243420
	strh r0, [r5, #0x20]
	add r2, r4, #0
	ldr r0, [r6, #0x30]
	add r1, r7, #0
	add r2, #0x27
	mov r3, #0
	bl ov11_02243420
	strh r0, [r5, #0x28]
	add r4, r4, #1
	add r5, r5, #2
	cmp r4, #4
	blt _02254ADE
	ldr r0, [r6, #0x30]
	add r1, r7, #0
	mov r2, #0x2d
	add r3, sp, #0x38
	bl ov11_02243420
	mov r0, #0x74
	str r0, [sp]
	add r0, r6, #0
	mov r1, #1
	add r2, r7, #0
	add r3, sp, #8
	bl ov11_02254878
	add sp, #0x7c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02254B34: .word 0x00002DBE
_02254B38: .word 0x0000219C
_02254B3C: .word 0x00002D66

	thumb_func_start ov11_02254B40
ov11_02254B40: ; 0x02254B40
	push {r4, r5, r6, r7, lr}
	sub sp, #0x84
	add r7, r1, #0
	add r4, r0, #0
	mov r1, #4
	add r6, sp, #0x10
	strb r1, [r6]
	mov r0, #0xc0
	add r5, r7, #0
	mul r5, r0
	ldr r0, [r4, #0x30]
	str r2, [sp, #4]
	add r2, r0, r5
	ldr r0, _02254D34 ; =0x00002DB0
	str r3, [sp, #8]
	ldr r3, [r2, r0]
	lsl r1, r1, #0x13
	tst r1, r3
	ldrb r1, [r6, #1]
	beq _02254B8A
	mov r3, #3
	bic r1, r3
	add r3, r0, #0
	add r3, #0x4a
	ldrh r2, [r2, r3]
	add r0, #0x34
	lsl r2, r2, #0x18
	lsr r3, r2, #0x18
	mov r2, #3
	and r2, r3
	orr r1, r2
	strb r1, [r6, #1]
	ldr r1, [r4, #0x30]
	add r1, r1, r5
	ldr r0, [r1, r0]
	str r0, [sp, #0x14]
	b _02254BAA
_02254B8A:
	mov r3, #3
	bic r1, r3
	add r3, r0, #0
	add r3, #0xe
	ldrb r2, [r2, r3]
	sub r0, #8
	lsl r2, r2, #0x1c
	lsr r3, r2, #0x1c
	mov r2, #3
	and r2, r3
	orr r1, r2
	strb r1, [r6, #1]
	ldr r1, [r4, #0x30]
	add r1, r1, r5
	ldr r0, [r1, r0]
	str r0, [sp, #0x14]
_02254BAA:
	mov r0, #0xc0
	add r6, r7, #0
	add r3, sp, #0x10
	mul r6, r0
	ldrb r0, [r3, #1]
	mov r1, #4
	bic r0, r1
	ldr r1, [r4, #0x30]
	add r2, r1, r6
	ldr r1, _02254D38 ; =0x00002D66
	ldrb r2, [r2, r1]
	sub r1, #0x26
	lsl r2, r2, #0x1a
	lsr r2, r2, #0x1f
	lsl r2, r2, #0x1f
	lsr r2, r2, #0x1d
	orr r0, r2
	strb r0, [r3, #1]
	ldr r0, [r4, #0x30]
	add r0, r0, r6
	ldrh r0, [r0, r1]
	add r1, r7, #0
	strh r0, [r3, #2]
	add r0, r4, #0
	bl ov11_02230260
	add r2, r0, #0
	ldr r0, [r4, #0x30]
	add r1, r7, #0
	mov r3, #0
	bl ov11_0224ACAC
	str r0, [sp, #0x18]
	ldr r0, [r4, #0x30]
	mov r2, #0xf8
	add r1, r0, r7
	ldr r0, _02254D3C ; =0x0000219C
	ldrb r0, [r1, r0]
	str r0, [sp, #0x1c]
	add r0, sp, #0x10
	ldrb r1, [r0, #1]
	bic r1, r2
	ldr r2, [r4, #0x30]
	add r3, r2, r6
	ldr r2, _02254D38 ; =0x00002D66
	ldrb r3, [r3, r2]
	lsl r3, r3, #0x1b
	lsr r3, r3, #0x1b
	lsl r3, r3, #0x1b
	lsr r3, r3, #0x18
	orr r1, r3
	strb r1, [r0, #1]
	ldr r0, [sp, #4]
	cmp r0, #0
	beq _02254C1C
	str r0, [sp, #0x20]
	b _02254C26
_02254C1C:
	ldr r0, [r4, #0x30]
	add r2, #0x59
	add r0, r0, r5
	ldrb r0, [r0, r2]
	str r0, [sp, #0x20]
_02254C26:
	ldr r0, [sp, #8]
	str r0, [sp, #0x24]
	ldr r0, [r4, #0x30]
	add r1, r0, r5
	ldr r0, _02254D34 ; =0x00002DB0
	ldr r1, [r1, r0]
	mov r0, #1
	lsl r0, r0, #0x18
	tst r0, r1
	beq _02254C3E
	mov r0, #1
	b _02254C40
_02254C3E:
	mov r0, #0
_02254C40:
	ldr r2, [sp, #0x1c]
	str r0, [sp, #0x5c]
	add r0, r4, #0
	add r1, r7, #0
	bl ov11_02230F6C
	mov r6, #0
	add r5, sp, #0x10
_02254C50:
	ldr r0, [r4, #0x30]
	add r1, r7, #0
	add r2, r6, #6
	mov r3, #0
	bl ov11_02243420
	strh r0, [r5, #0x18]
	add r2, r6, #0
	ldr r0, [r4, #0x30]
	add r1, r7, #0
	add r2, #0x1f
	mov r3, #0
	bl ov11_02243420
	strh r0, [r5, #0x20]
	add r2, r6, #0
	ldr r0, [r4, #0x30]
	add r1, r7, #0
	add r2, #0x27
	mov r3, #0
	bl ov11_02243420
	strh r0, [r5, #0x28]
	add r6, r6, #1
	add r5, r5, #2
	cmp r6, #4
	blt _02254C50
	ldr r0, [r4, #0x30]
	add r1, r7, #0
	mov r2, #0x2d
	add r3, sp, #0x40
	bl ov11_02243420
	add r3, sp, #0x10
	mov r2, #0
	mov ip, r2
	str r3, [sp, #0xc]
	add r5, r3, #0
_02254C9C:
	ldr r0, [r4, #0x30]
	add r1, r0, r2
	mov r0, #0xb5
	lsl r0, r0, #6
	ldrh r1, [r1, r0]
	ldr r0, [sp, #0xc]
	add r0, #0x50
	strh r1, [r0]
	ldr r0, [r4, #0x30]
	add r1, r0, r2
	ldr r0, _02254D38 ; =0x00002D66
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x1a
	lsr r1, r0, #0x1f
	add r0, r3, #0
	add r0, #0x5c
	strb r1, [r0]
	ldr r0, [r4, #0x30]
	add r1, r0, r2
	ldr r0, _02254D38 ; =0x00002D66
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x1b
	lsr r1, r0, #0x1b
	add r0, r3, #0
	add r0, #0x60
	strb r1, [r0]
	ldr r0, [r4, #0x30]
	add r6, r0, r2
	ldr r0, _02254D34 ; =0x00002DB0
	ldr r1, [r6, r0]
	mov r0, #2
	lsl r0, r0, #0x14
	tst r0, r1
	beq _02254CF2
	ldr r0, _02254D40 ; =0x00002DFA
	ldrh r1, [r6, r0]
	add r0, r3, #0
	add r0, #0x58
	strb r1, [r0]
	ldr r0, [r4, #0x30]
	add r1, r0, r2
	ldr r0, _02254D44 ; =0x00002DE4
	b _02254D06
_02254CF2:
	ldr r0, _02254D48 ; =0x00002DBE
	ldrb r0, [r6, r0]
	lsl r0, r0, #0x1c
	lsr r1, r0, #0x1c
	add r0, r3, #0
	add r0, #0x58
	strb r1, [r0]
	ldr r0, [r4, #0x30]
	add r1, r0, r2
	ldr r0, _02254D4C ; =0x00002DA8
_02254D06:
	ldr r0, [r1, r0]
	add r2, #0xc0
	str r0, [r5, #0x64]
	ldr r0, [sp, #0xc]
	add r3, r3, #1
	add r0, r0, #2
	str r0, [sp, #0xc]
	mov r0, ip
	add r0, r0, #1
	add r5, r5, #4
	mov ip, r0
	cmp r0, #4
	blt _02254C9C
	mov r0, #0x74
	str r0, [sp]
	add r0, r4, #0
	mov r1, #1
	add r2, r7, #0
	add r3, sp, #0x10
	bl ov11_02254878
	add sp, #0x84
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02254D34: .word 0x00002DB0
_02254D38: .word 0x00002D66
_02254D3C: .word 0x0000219C
_02254D40: .word 0x00002DFA
_02254D44: .word 0x00002DE4
_02254D48: .word 0x00002DBE
_02254D4C: .word 0x00002DA8

	thumb_func_start ov11_02254D50
ov11_02254D50: ; 0x02254D50
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	add r4, r1, #0
	lsl r1, r2, #2
	str r0, [sp, #4]
	add r0, r0, r1
	ldr r1, [r0, #0x34]
	ldr r0, _02254E8C ; =0x00000195
	str r2, [sp, #8]
	ldrb r1, [r1, r0]
	mov r0, #1
	tst r0, r1
	beq _02254D6E
	mov r2, #2
	b _02254D70
_02254D6E:
	mov r2, #0
_02254D70:
	ldr r0, [sp, #8]
	mov r1, #0xc0
	add r5, r0, #0
	ldr r0, [sp, #4]
	mul r5, r1
	ldr r0, [r0, #0x30]
	ldr r3, _02254E90 ; =0x00002D66
	add r0, r0, r5
	ldrb r0, [r0, r3]
	mov r1, #5
	lsl r0, r0, #0x1b
	lsr r7, r0, #0x1b
	add r0, sp, #0xc
	strb r1, [r0]
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x30]
	add r1, r0, r5
	add r0, r3, #0
	add r0, #0x4a
	ldr r6, [r1, r0]
	mov r0, #2
	lsl r0, r0, #0x14
	tst r0, r6
	beq _02254DC4
	add r0, r3, #0
	add r0, #0x7e
	ldr r0, [r1, r0]
	lsl r2, r2, #0x18
	str r0, [sp]
	add r0, r3, #0
	sub r0, #0x26
	add r3, #0x94
	ldrh r0, [r1, r0]
	ldrh r1, [r1, r3]
	lsl r3, r7, #0x18
	lsr r2, r2, #0x18
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsr r3, r3, #0x18
	bl sub_02068E88
	b _02254DE6
_02254DC4:
	add r0, r3, #0
	add r0, #0x42
	ldr r0, [r1, r0]
	lsl r2, r2, #0x18
	str r0, [sp]
	add r0, r3, #0
	sub r0, #0x26
	add r3, #0x58
	ldrh r0, [r1, r0]
	ldrb r1, [r1, r3]
	lsl r3, r7, #0x18
	lsr r2, r2, #0x18
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	lsr r3, r3, #0x18
	bl sub_02068E88
_02254DE6:
	add r1, sp, #0xc
	strb r0, [r1, #1]
	ldr r0, [sp, #4]
	ldr r1, _02254E94 ; =0x00002DBF
	ldr r0, [r0, #0x30]
	add r0, r0, r5
	ldrb r2, [r0, r1]
	add r0, sp, #0xc
	sub r1, #0xf
	strh r2, [r0, #2]
	ldr r0, [sp, #4]
	ldr r0, [r0, #0x30]
	add r0, r0, r5
	ldr r1, [r0, r1]
	mov r0, #1
	lsl r0, r0, #0x18
	tst r0, r1
	beq _02254E0E
	mov r0, #1
	b _02254E10
_02254E0E:
	mov r0, #0
_02254E10:
	str r0, [sp, #0x10]
	mov r0, #0
	mov ip, r0
	add r7, sp, #0xc
	ldr r0, _02254E90 ; =0x00002D66
	add r3, r7, #0
	add r2, r4, r0
	add r0, #0x58
	add r5, r7, #0
	add r6, r4, r0
_02254E24:
	mov r0, #0xb5
	lsl r0, r0, #6
	ldrh r0, [r4, r0]
	strh r0, [r7, #8]
	ldrb r0, [r2]
	lsl r0, r0, #0x1a
	lsr r0, r0, #0x1f
	strb r0, [r3, #0x14]
	ldrb r0, [r2]
	lsl r0, r0, #0x1b
	lsr r0, r0, #0x1b
	strb r0, [r3, #0x18]
	ldr r0, _02254E98 ; =0x00002DB0
	ldr r1, [r4, r0]
	mov r0, #2
	lsl r0, r0, #0x14
	tst r0, r1
	beq _02254E52
	ldr r0, _02254E9C ; =0x00002DFA
	ldrh r0, [r4, r0]
	strb r0, [r3, #0x10]
	ldr r0, _02254EA0 ; =0x00002DE4
	b _02254E5C
_02254E52:
	ldrb r0, [r6]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	strb r0, [r3, #0x10]
	ldr r0, _02254EA4 ; =0x00002DA8
_02254E5C:
	ldr r0, [r4, r0]
	add r4, #0xc0
	str r0, [r5, #0x1c]
	mov r0, ip
	add r0, r0, #1
	add r7, r7, #2
	add r2, #0xc0
	add r3, r3, #1
	add r5, r5, #4
	add r6, #0xc0
	mov ip, r0
	cmp r0, #4
	blt _02254E24
	mov r0, #0x2c
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r2, [sp, #8]
	mov r1, #1
	add r3, sp, #0xc
	bl ov11_02254878
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254E8C: .word 0x00000195
_02254E90: .word 0x00002D66
_02254E94: .word 0x00002DBF
_02254E98: .word 0x00002DB0
_02254E9C: .word 0x00002DFA
_02254EA0: .word 0x00002DE4
_02254EA4: .word 0x00002DA8

	thumb_func_start ov11_02254EA8
ov11_02254EA8: ; 0x02254EA8
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r1, #0
	add r4, r0, #0
	lsl r0, r7, #2
	add r0, r4, r0
	ldr r1, [r0, #0x34]
	ldr r0, _02254F58 ; =0x00000195
	str r2, [sp, #4]
	ldrb r1, [r1, r0]
	mov r0, #1
	tst r0, r1
	beq _02254EC6
	mov r2, #2
	b _02254EC8
_02254EC6:
	mov r2, #0
_02254EC8:
	mov r0, #0xc0
	add r6, r7, #0
	mul r6, r0
	ldr r0, [r4, #0x30]
	ldr r5, _02254F5C ; =0x00002D66
	add r0, r0, r6
	ldrb r0, [r0, r5]
	mov r1, #6
	lsl r0, r0, #0x1b
	lsr r3, r0, #0x1b
	add r0, sp, #8
	strb r1, [r0]
	ldr r0, [r4, #0x30]
	add r1, r0, r6
	add r0, r5, #0
	add r0, #0x4a
	ldr r6, [r1, r0]
	mov r0, #2
	lsl r0, r0, #0x14
	tst r0, r6
	beq _02254F16
	add r0, r5, #0
	add r0, #0x7e
	ldr r0, [r1, r0]
	lsl r2, r2, #0x18
	str r0, [sp]
	add r0, r5, #0
	sub r0, #0x26
	add r5, #0x94
	ldrh r0, [r1, r0]
	ldrh r1, [r1, r5]
	lsl r3, r3, #0x18
	lsr r2, r2, #0x18
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	lsr r3, r3, #0x18
	bl sub_02068E88
	b _02254F38
_02254F16:
	add r0, r5, #0
	add r0, #0x42
	ldr r0, [r1, r0]
	lsl r2, r2, #0x18
	str r0, [sp]
	add r0, r5, #0
	sub r0, #0x26
	add r5, #0x58
	ldrh r0, [r1, r0]
	ldrb r1, [r1, r5]
	lsl r3, r3, #0x18
	lsr r2, r2, #0x18
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	lsr r3, r3, #0x18
	bl sub_02068E88
_02254F38:
	add r1, sp, #8
	strb r0, [r1, #1]
	ldr r0, [sp, #4]
	add r1, sp, #8
	strh r0, [r1, #2]
	mov r0, #4
	str r0, [sp]
	add r0, r4, #0
	mov r1, #1
	add r2, r7, #0
	add r3, sp, #8
	bl ov11_02254878
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02254F58: .word 0x00000195
_02254F5C: .word 0x00002D66

	thumb_func_start ov11_02254F60
ov11_02254F60: ; 0x02254F60
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #7
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_02254F7C
ov11_02254F7C: ; 0x02254F7C
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #8
	add r3, sp, #4
	strb r1, [r3]
	mov r1, #0x34
	mul r1, r2
	add r1, r0, r1
	add r1, #0xad
	ldrb r1, [r1]
	strh r1, [r3, #2]
	add r1, r0, r2
	add r1, #0xa8
	ldrb r1, [r1]
	strb r1, [r3, #1]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}

	thumb_func_start ov11_02254FAC
ov11_02254FAC: ; 0x02254FAC
	push {r4, r5, r6, lr}
	sub sp, #8
	mov r6, #9
	add r3, sp, #4
	strb r6, [r3]
	add r5, r0, #0
	strb r2, [r3, #1]
	add r4, r1, #0
	bl ov11_022302BC
	ldr r1, [r5, #0x30]
	add r2, r4, #0
	add r1, r1, r0
	ldr r0, _02254FE0 ; =0x0000219C
	add r3, sp, #4
	ldrb r1, [r1, r0]
	add r0, sp, #4
	strh r1, [r0, #2]
	mov r0, #4
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	bl ov11_02254878
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_02254FE0: .word 0x0000219C

	thumb_func_start ov11_02254FE4
ov11_02254FE4: ; 0x02254FE4
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #0xa
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_02255000
ov11_02255000: ; 0x02255000
	push {r3, r4, lr}
	sub sp, #0xc
	add r3, r1, #0
	mov r1, #0xb
	add r4, sp, #4
	strb r1, [r4]
	mov r1, #0x34
	mul r1, r3
	add r1, r0, r1
	add r1, #0xad
	ldrb r1, [r1]
	strh r1, [r4, #2]
	add r1, r0, r3
	add r1, #0xa8
	ldrb r1, [r1]
	strb r1, [r4, #1]
	str r2, [sp, #8]
	mov r1, #8
	str r1, [sp]
	add r2, r3, #0
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #0xc
	pop {r3, r4, pc}

	thumb_func_start ov11_02255034
ov11_02255034: ; 0x02255034
	push {r4, r5, r6, r7, lr}
	sub sp, #0x2c
	add r5, r1, #0
	ldr r1, _02255158 ; =0x0000219C
	add r4, r2, #0
	add r7, r5, r1
	ldrb r2, [r7, r4]
	add r1, r4, #0
	str r0, [sp, #4]
	str r3, [sp, #8]
	bl ov11_02230014
	add r6, r0, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0x10]
	add r0, r6, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0xc]
	mov r0, #0xc
	add r2, sp, #0x14
	strb r0, [r2]
	mov r0, #0xc0
	add r6, r4, #0
	mul r6, r0
	ldr r1, _0225515C ; =0x00002D74
	add r0, r5, r6
	ldrb r3, [r0, r1]
	strb r3, [r2, #1]
	add r3, r1, #0
	add r3, #0x18
	ldr r3, [r0, r3]
	add r1, #0x1c
	strh r3, [r2, #2]
	ldr r0, [r0, r1]
	add r1, r4, #0
	strh r0, [r2, #4]
	ldrb r0, [r7, r4]
	strb r0, [r2, #6]
	add r0, r5, #0
	bl ov11_0224524C
	add r1, sp, #0x14
	ldrb r2, [r1, #7]
	mov r3, #0x1f
	lsl r0, r0, #0x18
	bic r2, r3
	lsr r3, r0, #0x18
	mov r0, #0x1f
	and r0, r3
	orr r0, r2
	strb r0, [r1, #7]
	mov r0, #0xb5
	lsl r0, r0, #6
	add r7, r5, r0
	ldrh r0, [r7, r6]
	cmp r0, #0x1d
	beq _022550B6
	cmp r0, #0x20
	bne _022550D0
_022550B6:
	ldr r0, _02255160 ; =0x00002D54
	add r1, r5, r6
	ldr r0, [r1, r0]
	lsr r0, r0, #0x1f
	bne _022550D0
	add r0, sp, #0x14
	ldrb r1, [r0, #7]
	mov r2, #0x60
	bic r1, r2
	mov r2, #0x40
	orr r1, r2
	strb r1, [r0, #7]
	b _022550EA
_022550D0:
	add r3, sp, #0x14
	ldrb r2, [r3, #7]
	mov r0, #0x60
	add r1, r5, r6
	bic r2, r0
	ldr r0, _02255164 ; =0x00002DBE
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x19
	orr r0, r2
	strb r0, [r3, #7]
_022550EA:
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0xc]
	bl GetMonExpBySpeciesAndLevel
	mov r1, #0xc0
	mul r1, r4
	add r2, r5, r1
	ldr r1, _02255168 ; =0x00002DA4
	ldr r1, [r2, r1]
	sub r0, r1, r0
	ldr r1, [sp, #0xc]
	str r0, [sp, #0x1c]
	ldr r0, [sp, #0x10]
	add r1, r1, #1
	bl GetMonExpBySpeciesAndLevel
	add r5, r0, #0
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0xc]
	bl GetMonExpBySpeciesAndLevel
	sub r0, r5, r0
	str r0, [sp, #0x20]
	ldrh r1, [r7, r6]
	ldr r0, [sp, #4]
	bl ov11_02231668
	add r3, sp, #0x14
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1f
	ldrb r1, [r3, #7]
	mov r2, #0x80
	lsr r0, r0, #0x18
	bic r1, r2
	orr r0, r1
	strb r0, [r3, #7]
	ldr r0, [sp, #4]
	bl ov11_02230E00
	str r0, [sp, #0x24]
	ldr r0, [sp, #8]
	add r1, sp, #0x14
	strb r0, [r1, #0x14]
	mov r0, #0x18
	str r0, [sp]
	ldr r0, [sp, #4]
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #0x14
	bl ov11_02254878
	add sp, #0x2c
	pop {r4, r5, r6, r7, pc}
	nop
_02255158: .word 0x0000219C
_0225515C: .word 0x00002D74
_02255160: .word 0x00002D54
_02255164: .word 0x00002DBE
_02255168: .word 0x00002DA4

	thumb_func_start ov11_0225516C
ov11_0225516C: ; 0x0225516C
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #0xd
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_02255188
ov11_02255188: ; 0x02255188
	push {r4, r5, r6, r7, lr}
	sub sp, #0x54
	str r0, [sp, #4]
	str r1, [sp, #8]
	str r2, [sp, #0xc]
	mov r0, #0
	add r1, sp, #0x28
	mov r2, #0x2c
	add r6, r3, #0
	bl MIi_CpuClearFast
	ldr r0, [sp, #4]
	bl ov11_0222FF78
	ldr r1, [sp, #0xc]
	bl ov11_02243400
	mov r5, #0
	ldr r0, [sp, #4]
	add r4, r5, #0
	bl ov11_0222FF84
	cmp r0, #0
	ble _022551D8
_022551B8:
	ldr r0, [sp, #8]
	add r1, r4, #0
	bl ov11_0224AD04
	cmp r0, #0
	bne _022551CC
	add r0, r4, #0
	bl MaskOfFlagNo
	orr r5, r0
_022551CC:
	ldr r0, [sp, #4]
	add r4, r4, #1
	bl ov11_0222FF84
	cmp r4, r0
	blt _022551B8
_022551D8:
	mov r1, #0xe
	add r0, sp, #0x28
	strb r1, [r0]
	strb r6, [r0, #1]
	ldr r1, _022554F8 ; =0x00003108
	ldr r0, [sp, #8]
	ldrb r0, [r0, r1]
	add r1, r0, #0
	orr r1, r5
	add r0, sp, #0x48
	strb r1, [r0, #9]
	ldr r0, [sp, #4]
	bl ov11_0222FF74
	mov r1, #2
	str r0, [sp, #0x20]
	tst r0, r1
	beq _0225520E
	ldr r0, [sp, #0x20]
	mov r1, #8
	tst r0, r1
	bne _0225520E
	ldr r0, [sp, #0xc]
	mov r1, #1
	add r4, r0, #0
	and r4, r1
	b _02255210
_0225520E:
	ldr r4, [sp, #0xc]
_02255210:
	ldr r0, [sp, #4]
	add r1, r4, #0
	bl ov11_0222FF88
	str r0, [sp, #0x24]
	mov r6, #0
	bl GetPartyCount
	cmp r0, #0
	ble _022552A6
	mov r0, #6
	add r1, r4, #0
	mul r1, r0
	ldr r0, [sp, #8]
	add r5, sp, #0x28
	add r7, r0, r1
	mov r1, #0xa9
	ldr r0, [sp, #0x20]
	lsl r1, r1, #2
	and r0, r1
	str r0, [sp, #0x1c]
_0225523A:
	ldr r1, _022554FC ; =0x0000312C
	ldr r0, [sp, #0x24]
	ldrb r1, [r7, r1]
	bl GetPartyMonByIndex
	mov r1, #0xad
	mov r2, #0
	add r4, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _02255298
	ldr r1, _02255500 ; =0x000001EE
	cmp r0, r1
	beq _02255298
	add r0, r4, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02255280
	add r0, r4, #0
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _0225527A
	mov r0, #3
	strb r0, [r5, #8]
	b _02255284
_0225527A:
	mov r0, #1
	strb r0, [r5, #8]
	b _02255284
_02255280:
	mov r0, #2
	strb r0, [r5, #8]
_02255284:
	ldr r0, [sp, #0x1c]
	cmp r0, #0
	beq _0225528E
	mov r0, #0
	b _02255294
_0225528E:
	add r0, r4, #0
	bl GetPercentProgressTowardsNextLevel
_02255294:
	strb r0, [r5, #2]
	add r5, r5, #1
_02255298:
	ldr r0, [sp, #0x24]
	add r7, r7, #1
	add r6, r6, #1
	bl GetPartyCount
	cmp r6, r0
	blt _0225523A
_022552A6:
	ldr r0, [sp, #0x20]
	mov r1, #0xc
	and r0, r1
	cmp r0, #0xc
	beq _022552C4
	ldr r0, [sp, #0x20]
	mov r1, #0x10
	tst r0, r1
	bne _022552C4
	ldr r0, [sp, #0x20]
	cmp r0, #0x4b
	beq _022552C4
	cmp r0, #0xcb
	beq _022552C4
	b _022553FC
_022552C4:
	ldr r0, [sp, #4]
	ldr r1, [sp, #0xc]
	bl ov11_02230270
	cmp r0, #0
	beq _022552DA
	ldr r0, [sp, #4]
	mov r1, #2
	bl ov11_0223022C
	b _022552E2
_022552DA:
	ldr r0, [sp, #4]
	mov r1, #3
	bl ov11_0223022C
_022552E2:
	add r4, r0, #0
	ldr r0, [sp, #4]
	add r1, r4, #0
	bl ov11_0222FF88
	str r0, [sp, #0x10]
	mov r5, #0
	bl GetPartyCount
	cmp r0, #0
	ble _0225535E
	add r1, r4, #0
	mov r0, #6
	mul r1, r0
	ldr r0, [sp, #8]
	add r4, sp, #0x28
	add r6, r0, r1
_02255304:
	ldr r1, _022554FC ; =0x0000312C
	ldr r0, [sp, #0x10]
	ldrb r1, [r6, r1]
	bl GetPartyMonByIndex
	mov r1, #0xad
	mov r2, #0
	add r7, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _02255350
	ldr r1, _02255500 ; =0x000001EE
	cmp r0, r1
	beq _02255350
	add r0, r7, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _0225534A
	add r0, r7, #0
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02255344
	mov r0, #3
	strb r0, [r4, #0xe]
	b _0225534E
_02255344:
	mov r0, #1
	strb r0, [r4, #0xe]
	b _0225534E
_0225534A:
	mov r0, #2
	strb r0, [r4, #0xe]
_0225534E:
	add r4, r4, #1
_02255350:
	ldr r0, [sp, #0x10]
	add r6, r6, #1
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _02255304
_0225535E:
	ldr r0, [sp, #4]
	ldr r1, [sp, #0xc]
	bl ov11_02230270
	cmp r0, #0
	beq _02255374
	ldr r0, [sp, #4]
	mov r1, #4
	bl ov11_0223022C
	b _0225537C
_02255374:
	ldr r0, [sp, #4]
	mov r1, #5
	bl ov11_0223022C
_0225537C:
	add r4, r0, #0
	ldr r0, [sp, #4]
	add r1, r4, #0
	bl ov11_0222FF88
	str r0, [sp, #0x14]
	mov r5, #0
	bl GetPartyCount
	cmp r0, #0
	ble _02255482
	add r1, r4, #0
	mov r0, #6
	mul r1, r0
	ldr r0, [sp, #8]
	add r4, sp, #0x28
	add r6, r0, r1
	add r4, #3
_022553A0:
	ldr r1, _022554FC ; =0x0000312C
	ldr r0, [sp, #0x14]
	ldrb r1, [r6, r1]
	bl GetPartyMonByIndex
	mov r1, #0xad
	mov r2, #0
	add r7, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _022553EC
	ldr r1, _02255500 ; =0x000001EE
	cmp r0, r1
	beq _022553EC
	add r0, r7, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _022553E6
	add r0, r7, #0
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _022553E0
	mov r0, #3
	strb r0, [r4, #0xe]
	b _022553EA
_022553E0:
	mov r0, #1
	strb r0, [r4, #0xe]
	b _022553EA
_022553E6:
	mov r0, #2
	strb r0, [r4, #0xe]
_022553EA:
	add r4, r4, #1
_022553EC:
	ldr r0, [sp, #0x14]
	add r6, r6, #1
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _022553A0
	b _02255482
_022553FC:
	ldr r0, [sp, #4]
	ldr r1, [sp, #0xc]
	mov r2, #2
	bl ov11_02230308
	add r4, r0, #0
	ldr r0, [sp, #4]
	add r1, r4, #0
	bl ov11_0222FF88
	str r0, [sp, #0x18]
	mov r5, #0
	bl GetPartyCount
	cmp r0, #0
	ble _02255482
	add r1, r4, #0
	mov r0, #6
	mul r1, r0
	ldr r0, [sp, #8]
	add r4, sp, #0x28
	add r6, r0, r1
_02255428:
	ldr r1, _022554FC ; =0x0000312C
	ldr r0, [sp, #0x18]
	ldrb r1, [r6, r1]
	bl GetPartyMonByIndex
	mov r1, #0xad
	mov r2, #0
	add r7, r0, #0
	bl GetMonData
	cmp r0, #0
	beq _02255474
	ldr r1, _02255500 ; =0x000001EE
	cmp r0, r1
	beq _02255474
	add r0, r7, #0
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _0225546E
	add r0, r7, #0
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02255468
	mov r0, #3
	strb r0, [r4, #0xe]
	b _02255472
_02255468:
	mov r0, #1
	strb r0, [r4, #0xe]
	b _02255472
_0225546E:
	mov r0, #2
	strb r0, [r4, #0xe]
_02255472:
	add r4, r4, #1
_02255474:
	ldr r0, [sp, #0x18]
	add r6, r6, #1
	add r5, r5, #1
	bl GetPartyCount
	cmp r5, r0
	blt _02255428
_02255482:
	mov r5, #0
	add r6, sp, #0x28
	add r4, r6, #0
	add r7, r5, #0
_0225548A:
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	add r2, r5, #6
	add r3, r7, #0
	bl ov11_02243420
	strh r0, [r6, #0x14]
	add r2, r5, #0
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	add r2, #0x1f
	mov r3, #0
	bl ov11_02243420
	strb r0, [r4, #0x1c]
	add r2, r5, #0
	ldr r0, [sp, #8]
	ldr r1, [sp, #0xc]
	add r2, #0x27
	mov r3, #0
	bl ov11_02243420
	add r1, r4, #0
	add r1, #0x20
	add r5, r5, #1
	strb r0, [r1]
	add r6, r6, #2
	add r4, r4, #1
	cmp r5, #4
	blt _0225548A
	ldr r0, [sp, #0xc]
	mov r1, #0xc0
	mul r1, r0
	ldr r0, [sp, #8]
	add r3, sp, #0x28
	add r0, r0, r1
	ldr r1, _02255504 ; =0x00002D8C
	ldr r2, [r0, r1]
	strh r2, [r3, #0x24]
	add r2, r1, #4
	ldr r2, [r0, r2]
	strh r2, [r3, #0x26]
	mov r2, #0x24
	ldrsh r2, [r3, r2]
	cmp r2, #0
	beq _0225550E
	add r1, #0x20
	ldr r0, [r0, r1]
	cmp r0, #0
	add r0, sp, #0x48
	beq _02255508
	mov r1, #3
	strb r1, [r0, #8]
	b _02255514
	nop
_022554F8: .word 0x00003108
_022554FC: .word 0x0000312C
_02255500: .word 0x000001EE
_02255504: .word 0x00002D8C
_02255508:
	mov r1, #1
	strb r1, [r0, #8]
	b _02255514
_0225550E:
	mov r1, #2
	add r0, sp, #0x48
	strb r1, [r0, #8]
_02255514:
	mov r0, #0x2c
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r2, [sp, #0xc]
	mov r1, #1
	add r3, sp, #0x28
	bl ov11_02254878
	add sp, #0x54
	pop {r4, r5, r6, r7, pc}

	thumb_func_start ov11_02255528
ov11_02255528: ; 0x02255528
	push {r0, r1, r2, r3}
	push {r3, lr}
	add r2, r1, #0
	mov r1, #4
	str r1, [sp]
	mov r1, #0
	add r3, sp, #0x10
	bl ov11_02254878
	pop {r3}
	pop {r3}
	add sp, #0x10
	bx r3
	.align 2, 0

	thumb_func_start ov11_02255544
ov11_02255544: ; 0x02255544
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x28
	str r2, [sp, #0xc]
	str r0, [sp, #4]
	str r1, [sp, #8]
	bl ov11_0222FF78
	ldr r1, [sp, #0xc]
	bl ov11_02243400
	mov r0, #0xf
	add r2, sp, #0x14
	strb r0, [r2]
	add r7, sp, #0x14
	ldr r1, [sp, #8]
	ldr r0, [sp, #0xc]
	add r5, r7, #0
	add r1, r1, r0
	ldr r0, _022555D4 ; =0x0000219C
	ldrb r0, [r1, r0]
	mov r1, #0xc0
	strb r0, [r2, #1]
	mov r0, #0
	str r0, [sp, #0x10]
	ldr r0, [sp, #0xc]
	mul r1, r0
	ldr r0, [sp, #8]
	add r6, r0, r1
	add r4, r6, #0
_0225557E:
	ldr r0, _022555D8 ; =0x00002D4C
	ldr r1, _022555DC ; =0x00002D70
	ldrh r0, [r6, r0]
	strh r0, [r7, #4]
	ldr r0, _022555E0 ; =0x00002D6C
	ldrb r0, [r4, r0]
	strb r0, [r5, #0xc]
	ldr r0, _022555D8 ; =0x00002D4C
	ldrb r1, [r4, r1]
	ldrh r0, [r6, r0]
	bl WazaGetMaxPp
	strb r0, [r5, #0x10]
	ldr r0, [sp, #0x10]
	add r6, r6, #2
	add r0, r0, #1
	add r7, r7, #2
	add r4, r4, #1
	add r5, r5, #1
	str r0, [sp, #0x10]
	cmp r0, #4
	blt _0225557E
	mov r0, #0
	mvn r0, r0
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r1, [sp, #8]
	ldr r2, [sp, #0xc]
	mov r3, #0
	bl ov11_02245D38
	add r1, sp, #0x14
	strh r0, [r1, #2]
	mov r0, #0x14
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r2, [sp, #0xc]
	mov r1, #1
	add r3, sp, #0x14
	bl ov11_02254878
	add sp, #0x28
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022555D4: .word 0x0000219C
_022555D8: .word 0x00002D4C
_022555DC: .word 0x00002D70
_022555E0: .word 0x00002D6C

	thumb_func_start ov11_022555E4
ov11_022555E4: ; 0x022555E4
	push {r0, r1, r2, r3}
	push {r3, lr}
	add r2, r1, #0
	mov r1, #4
	str r1, [sp]
	mov r1, #0
	add r3, sp, #0x10
	bl ov11_02254878
	pop {r3}
	pop {r3}
	add sp, #0x10
	bx r3
	.align 2, 0

	thumb_func_start ov11_02255600
ov11_02255600: ; 0x02255600
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x40
	str r0, [sp, #4]
	str r1, [sp, #8]
	add r0, r1, #0
	add r1, r3, #0
	add r4, r2, #0
	str r3, [sp, #0xc]
	bl ov11_02243400
	ldr r0, [sp, #4]
	bl ov11_0222FF74
	mov r2, #0x10
	add r1, sp, #0x1c
	strb r2, [r1]
	strh r4, [r1, #2]
	mov r1, #2
	add r2, r0, #0
	and r2, r1
	beq _0225563A
	mov r1, #8
	tst r0, r1
	bne _0225563A
	cmp r2, #0
	beq _02255642
	ldr r0, [sp, #0xc]
	cmp r0, #2
	blt _02255642
_0225563A:
	mov r1, #1
	add r0, sp, #0x1c
	strb r1, [r0, #1]
	b _02255648
_02255642:
	mov r1, #0
	add r0, sp, #0x1c
	strb r1, [r0, #1]
_02255648:
	ldr r2, [sp, #8]
	mov r0, #0
	str r0, [sp, #0x18]
	ldr r1, _0225570C ; =0x00002D54
	add r0, r2, #0
	add r7, r0, r1
	add r1, #0x6a
	add r5, r0, r1
	mov r0, #3
	add r4, sp, #0x20
	str r0, [sp, #0x14]
	str r0, [sp, #0x10]
	mov r0, #4
	add r3, sp, #0x1c
	add r4, #1
	mov ip, r0
_02255668:
	ldr r0, _02255710 ; =0x00002D8C
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _022556D6
	strh r0, [r3, #8]
	ldr r0, _02255714 ; =0x00002D90
	ldr r0, [r2, r0]
	strh r0, [r3, #0xa]
	ldrb r1, [r4]
	mov r0, #4
	orr r0, r1
	strb r0, [r4]
	mov r0, #0xb5
	lsl r0, r0, #6
	ldrh r0, [r2, r0]
	cmp r0, #0x1d
	beq _0225568E
	cmp r0, #0x20
	bne _022556A2
_0225568E:
	ldr r0, [r7]
	lsr r0, r0, #0x1f
	bne _022556A2
	ldrb r0, [r4]
	ldr r1, [sp, #0x10]
	bic r0, r1
	mov r1, #2
	orr r0, r1
	strb r0, [r4]
	b _022556B6
_022556A2:
	ldrb r6, [r4]
	ldr r0, [sp, #0x14]
	bic r6, r0
	ldrb r0, [r5]
	lsl r0, r0, #0x1c
	lsr r1, r0, #0x1c
	mov r0, #3
	and r0, r1
	orr r0, r6
	strb r0, [r4]
_022556B6:
	ldr r1, [sp, #8]
	ldr r0, [sp, #0x18]
	add r1, r1, r0
	ldr r0, _02255718 ; =0x0000219C
	ldrb r0, [r1, r0]
	strb r0, [r3, #4]
	ldr r0, _0225571C ; =0x00002DAC
	ldr r0, [r2, r0]
	cmp r0, #0
	beq _022556D0
	mov r0, #3
	strb r0, [r3, #6]
	b _022556E2
_022556D0:
	mov r0, #1
	strb r0, [r3, #6]
	b _022556E2
_022556D6:
	ldrb r1, [r4]
	mov r0, ip
	bic r1, r0
	strb r1, [r4]
	mov r0, #2
	strb r0, [r3, #6]
_022556E2:
	ldr r0, [sp, #0x18]
	add r2, #0xc0
	add r0, r0, #1
	add r3, #8
	add r4, #8
	add r7, #0xc0
	add r5, #0xc0
	str r0, [sp, #0x18]
	cmp r0, #4
	blt _02255668
	mov r0, #0x24
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r2, [sp, #0xc]
	mov r1, #1
	add r3, sp, #0x1c
	bl ov11_02254878
	add sp, #0x40
	pop {r3, r4, r5, r6, r7, pc}
	nop
_0225570C: .word 0x00002D54
_02255710: .word 0x00002D8C
_02255714: .word 0x00002D90
_02255718: .word 0x0000219C
_0225571C: .word 0x00002DAC

	thumb_func_start ov11_02255720
ov11_02255720: ; 0x02255720
	push {r0, r1, r2, r3}
	push {r3, lr}
	add r2, r1, #0
	mov r1, #4
	str r1, [sp]
	mov r1, #0
	add r3, sp, #0x10
	bl ov11_02254878
	pop {r3}
	pop {r3}
	add sp, #0x10
	bx r3
	.align 2, 0

	thumb_func_start ov11_0225573C
ov11_0225573C: ; 0x0225573C
	push {r4, r5, r6, r7, lr}
	sub sp, #0x34
	str r0, [sp, #4]
	str r1, [sp, #8]
	add r0, r1, #0
	add r1, r2, #0
	str r2, [sp, #0xc]
	bl ov11_02243400
	add r6, sp, #0x10
	mov r1, #0x11
	add r0, sp, #0x10
	strb r1, [r0]
	mov r0, #0
	ldr r4, [sp, #8]
	mov ip, r0
	ldr r1, _022558B0 ; =0x00002DCC
	add r0, r4, #0
	add r7, r0, r1
	ldr r0, _022558B4 ; =0x0000312C
	add r5, r6, #0
_02255766:
	ldr r2, [sp, #8]
	mov r1, ip
	add r2, r2, r1
	ldr r1, _022558B8 ; =0x0000219C
	mov r3, #0
	ldrb r1, [r2, r1]
	strb r1, [r6, #4]
_02255774:
	add r1, r4, r3
	ldrb r2, [r1, r0]
	add r1, r5, r3
	add r3, r3, #1
	strb r2, [r1, #8]
	cmp r3, #6
	blt _02255774
	ldr r1, [r7]
	add r2, r6, #0
	lsl r1, r1, #0xa
	lsr r1, r1, #0x1d
	add r2, #0x20
	strb r1, [r2]
	mov r1, ip
	add r1, r1, #1
	add r6, r6, #1
	add r4, r4, #6
	add r5, r5, #6
	add r7, #0xc0
	mov ip, r1
	cmp r1, #4
	blt _02255766
	ldr r0, [sp, #4]
	bl ov11_0222FF74
	cmp r0, #0x4a
	bne _02255852
	mov r0, #1
	bl MaskOfFlagNo
	ldr r2, _022558BC ; =0x00003108
	ldr r1, [sp, #8]
	ldrb r1, [r1, r2]
	tst r0, r1
	bne _022557D8
	mov r0, #3
	bl MaskOfFlagNo
	ldr r2, _022558BC ; =0x00003108
	ldr r1, [sp, #8]
	ldrb r1, [r1, r2]
	tst r0, r1
	bne _022557D8
	mov r1, #1
	add r0, sp, #0x10
	strb r1, [r0, #1]
	mov r1, #0
	strb r1, [r0, #2]
	strb r1, [r0, #3]
	b _0225589C
_022557D8:
	mov r0, #1
	bl MaskOfFlagNo
	ldr r2, _022558BC ; =0x00003108
	ldr r1, [sp, #8]
	add r3, sp, #0x10
	ldrb r1, [r1, r2]
	tst r0, r1
	bne _0225581E
	mov r0, #0
	mov r2, #0xba
	ldr r1, [sp, #8]
	strb r0, [r3, #1]
	lsl r2, r2, #6
	ldr r4, [r1, r2]
	ldr r1, _022558C0 ; =0x200400C0
	tst r1, r4
	beq _02255804
	mov r1, #1
	strb r1, [r3, #2]
	strb r0, [r3, #3]
	b _0225589C
_02255804:
	ldr r1, [sp, #8]
	sub r2, #0x10
	ldr r2, [r1, r2]
	mov r1, #1
	lsl r1, r1, #0x18
	tst r1, r2
	strb r0, [r3, #2]
	beq _0225581A
	mov r0, #1
	strb r0, [r3, #3]
	b _0225589C
_0225581A:
	strb r0, [r3, #3]
	b _0225589C
_0225581E:
	mov r0, #0
	mov r2, #3
	ldr r1, [sp, #8]
	strb r0, [r3, #1]
	lsl r2, r2, #0xc
	ldr r4, [r1, r2]
	ldr r1, _022558C0 ; =0x200400C0
	tst r1, r4
	beq _02255838
	mov r1, #1
	strb r1, [r3, #2]
	strb r0, [r3, #3]
	b _0225589C
_02255838:
	ldr r1, [sp, #8]
	sub r2, #0x10
	ldr r2, [r1, r2]
	mov r1, #1
	lsl r1, r1, #0x18
	tst r1, r2
	strb r0, [r3, #2]
	beq _0225584E
	mov r0, #1
	strb r0, [r3, #3]
	b _0225589C
_0225584E:
	strb r0, [r3, #3]
	b _0225589C
_02255852:
	ldr r0, [sp, #4]
	bl ov11_0222FF74
	cmp r0, #0
	bne _02255892
	mov r2, #0xba
	mov r0, #0
	add r3, sp, #0x10
	ldr r1, [sp, #8]
	strb r0, [r3, #1]
	lsl r2, r2, #6
	ldr r4, [r1, r2]
	ldr r1, _022558C0 ; =0x200400C0
	tst r1, r4
	beq _02255878
	mov r1, #1
	strb r1, [r3, #2]
	strb r0, [r3, #3]
	b _0225589C
_02255878:
	ldr r1, [sp, #8]
	sub r2, #0x10
	ldr r2, [r1, r2]
	mov r1, #1
	lsl r1, r1, #0x18
	tst r1, r2
	strb r0, [r3, #2]
	beq _0225588E
	mov r0, #1
	strb r0, [r3, #3]
	b _0225589C
_0225588E:
	strb r0, [r3, #3]
	b _0225589C
_02255892:
	mov r1, #0
	add r0, sp, #0x10
	strb r1, [r0, #1]
	strb r1, [r0, #2]
	strb r1, [r0, #3]
_0225589C:
	mov r0, #0x24
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r2, [sp, #0xc]
	mov r1, #1
	add r3, sp, #0x10
	bl ov11_02254878
	add sp, #0x34
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_022558B0: .word 0x00002DCC
_022558B4: .word 0x0000312C
_022558B8: .word 0x0000219C
_022558BC: .word 0x00003108
_022558C0: .word 0x200400C0

	thumb_func_start ov11_022558C4
ov11_022558C4: ; 0x022558C4
	push {r0, r1, r2, r3}
	push {r3, lr}
	add r2, r1, #0
	mov r1, #4
	str r1, [sp]
	mov r1, #0
	add r3, sp, #0x10
	bl ov11_02254878
	pop {r3}
	pop {r3}
	add sp, #0x10
	bx r3
	.align 2, 0

	thumb_func_start ov11_022558E0
ov11_022558E0: ; 0x022558E0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x38
	str r0, [sp, #4]
	str r1, [sp, #8]
	add r0, r1, #0
	add r1, r2, #0
	str r2, [sp, #0xc]
	add r4, r3, #0
	bl ov11_02243400
	mov r0, #0x12
	add r1, sp, #0x10
	strb r0, [r1]
	ldr r0, [sp, #0xc]
	add r7, sp, #0x10
	strb r0, [r1, #1]
	ldr r0, [sp, #0x50]
	strb r4, [r1, #2]
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x54]
	ldr r5, [sp, #8]
	strb r0, [r1, #3]
	ldr r1, _02255958 ; =0x00003108
	ldr r0, [sp, #8]
	mov r3, #0
	ldrb r1, [r0, r1]
	add r0, sp, #0x30
	add r6, r7, #0
	strb r1, [r0, #4]
	ldr r0, _0225595C ; =0x0000312C
_0225591C:
	ldr r1, [sp, #8]
	mov r4, #0
	add r2, r1, r3
	ldr r1, _02255960 ; =0x0000219C
	ldrb r1, [r2, r1]
	strb r1, [r7, #4]
_02255928:
	add r1, r5, r4
	ldrb r2, [r1, r0]
	add r1, r6, r4
	add r4, r4, #1
	strb r2, [r1, #8]
	cmp r4, #6
	blt _02255928
	add r3, r3, #1
	add r7, r7, #1
	add r5, r5, #6
	add r6, r6, #6
	cmp r3, #4
	blt _0225591C
	mov r0, #0x28
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r2, [sp, #0xc]
	mov r1, #1
	add r3, sp, #0x10
	bl ov11_02254878
	add sp, #0x38
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02255958: .word 0x00003108
_0225595C: .word 0x0000312C
_02255960: .word 0x0000219C

	thumb_func_start ov11_02255964
ov11_02255964: ; 0x02255964
	push {r0, r1, r2, r3}
	push {r3, lr}
	add r2, r1, #0
	mov r1, #4
	str r1, [sp]
	mov r1, #0
	add r3, sp, #0x10
	bl ov11_02254878
	pop {r3}
	pop {r3}
	add sp, #0x10
	bx r3
	.align 2, 0

	thumb_func_start ov11_02255980
ov11_02255980: ; 0x02255980
	push {r4, r5, r6, lr}
	sub sp, #0x10
	add r5, r2, #0
	add r6, r0, #0
	add r0, r1, #0
	add r1, r5, #0
	add r4, r3, #0
	bl ov11_02243400
	mov r1, #0x13
	add r0, sp, #4
	strb r1, [r0]
	ldr r1, [sp, #0x20]
	strh r4, [r0, #2]
	strb r1, [r0, #1]
	ldr r0, [sp, #0x24]
	mov r1, #1
	str r0, [sp, #8]
	ldr r0, [sp, #0x28]
	add r2, r5, #0
	str r0, [sp, #0xc]
	mov r0, #0xc
	str r0, [sp]
	add r0, r6, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #0x10
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_022559BC
ov11_022559BC: ; 0x022559BC
	push {r4, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #0x14
	add r3, sp, #4
	strb r1, [r3]
	ldr r1, [r2, #0x64]
	add r4, r2, r1
	ldr r1, _022559EC ; =0x0000219C
	ldrb r1, [r4, r1]
	strb r1, [r3, #1]
	ldr r1, _022559F0 ; =0x00003044
	ldr r1, [r2, r1]
	strh r1, [r3, #2]
	mov r1, #4
	str r1, [sp]
	ldr r2, [r2, #0x64]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r4, pc}
	nop
_022559EC: .word 0x0000219C
_022559F0: .word 0x00003044

	thumb_func_start ov11_022559F4
ov11_022559F4: ; 0x022559F4
	push {r3, r4, lr}
	sub sp, #4
	add r4, r1, #0
	add r3, r2, #0
	mov r1, #0x15
	strb r1, [r3]
	mov r1, #0x24
	str r1, [sp]
	ldr r2, [r4, #0x64]
	mov r1, #1
	bl ov11_02254878
	add sp, #4
	pop {r3, r4, pc}

	thumb_func_start ov11_02255A10
ov11_02255A10: ; 0x02255A10
	push {r4, r5, r6, lr}
	sub sp, #0x68
	mov r3, #0
	add r4, r1, #0
	str r3, [sp]
	ldr r6, [r4, #0x64]
	add r5, r0, #0
	str r6, [sp, #4]
	ldr r6, [r4, #0x6c]
	str r6, [sp, #8]
	str r2, [sp, #0xc]
	add r2, sp, #0x10
	bl ov11_02256854
	mov r0, #0x58
	str r0, [sp]
	ldr r2, [r4, #0x64]
	add r0, r5, #0
	mov r1, #1
	add r3, sp, #0x10
	bl ov11_02254878
	add sp, #0x68
	pop {r4, r5, r6, pc}

	thumb_func_start ov11_02255A40
ov11_02255A40: ; 0x02255A40
	push {r4, r5, r6, lr}
	sub sp, #0x68
	add r4, r3, #0
	mov r3, #0
	str r3, [sp]
	ldr r6, [sp, #0x78]
	str r4, [sp, #4]
	str r6, [sp, #8]
	str r2, [sp, #0xc]
	add r2, sp, #0x10
	add r5, r0, #0
	bl ov11_02256854
	mov r0, #0x58
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #0x10
	bl ov11_02254878
	add sp, #0x68
	pop {r4, r5, r6, pc}
	.align 2, 0

	thumb_func_start ov11_02255A70
ov11_02255A70: ; 0x02255A70
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #0x17
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_02255A8C
ov11_02255A8C: ; 0x02255A8C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	add r5, r1, #0
	str r2, [sp, #8]
	add r1, r2, #0
	add r3, r5, r2
	ldr r2, _02255B50 ; =0x0000219C
	str r0, [sp, #4]
	ldrb r2, [r3, r2]
	bl ov11_02230014
	add r4, r0, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	add r7, r0, #0
	add r0, r4, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	add r6, r0, #0
	mov r0, #0x18
	add r2, sp, #0xc
	strb r0, [r2]
	ldr r0, [sp, #8]
	mov r1, #0xc0
	add r4, r0, #0
	mul r4, r1
	ldr r1, _02255B54 ; =0x00002D74
	add r0, r5, r4
	ldrb r3, [r0, r1]
	strb r3, [r2, #1]
	add r3, r1, #0
	add r3, #0x18
	ldr r3, [r0, r3]
	strh r3, [r2, #2]
	add r3, r1, #0
	add r3, #0x1c
	ldr r3, [r0, r3]
	sub r1, #0x34
	strh r3, [r2, #4]
	ldr r2, _02255B58 ; =0x0000215C
	ldr r2, [r5, r2]
	str r2, [sp, #0x14]
	ldrh r0, [r0, r1]
	cmp r0, #0x1d
	beq _02255AF2
	cmp r0, #0x20
	bne _02255B04
_02255AF2:
	ldr r0, _02255B5C ; =0x00002D54
	add r1, r5, r4
	ldr r0, [r1, r0]
	lsr r0, r0, #0x1f
	bne _02255B04
	mov r1, #2
	add r0, sp, #0xc
	strb r1, [r0, #7]
	b _02255B12
_02255B04:
	ldr r0, _02255B60 ; =0x00002DBE
	add r1, r5, r4
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x1c
	lsr r1, r0, #0x1c
	add r0, sp, #0xc
	strb r1, [r0, #7]
_02255B12:
	add r0, r7, #0
	add r1, r6, #0
	bl GetMonExpBySpeciesAndLevel
	ldr r1, _02255B64 ; =0x00002DA4
	add r2, r5, r4
	ldr r1, [r2, r1]
	sub r0, r1, r0
	str r0, [sp, #0x18]
	add r0, r7, #0
	add r1, r6, #1
	bl GetMonExpBySpeciesAndLevel
	add r4, r0, #0
	add r0, r7, #0
	add r1, r6, #0
	bl GetMonExpBySpeciesAndLevel
	sub r0, r4, r0
	str r0, [sp, #0x1c]
	mov r0, #0x14
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r2, [sp, #8]
	mov r1, #1
	add r3, sp, #0xc
	bl ov11_02254878
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02255B50: .word 0x0000219C
_02255B54: .word 0x00002D74
_02255B58: .word 0x0000215C
_02255B5C: .word 0x00002D54
_02255B60: .word 0x00002DBE
_02255B64: .word 0x00002DA4

	thumb_func_start ov11_02255B68
ov11_02255B68: ; 0x02255B68
	push {r4, r5, r6, r7, lr}
	sub sp, #0x1c
	add r4, r2, #0
	add r5, r1, #0
	str r3, [sp, #8]
	ldr r2, _02255BE4 ; =0x0000219C
	add r3, r5, r4
	ldrb r2, [r3, r2]
	add r1, r4, #0
	str r0, [sp, #4]
	bl ov11_02230014
	add r6, r0, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	add r7, r0, #0
	add r0, r6, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	add r6, r0, #0
	mov r1, #0x19
	add r0, sp, #0xc
	strb r1, [r0]
	ldr r0, [sp, #8]
	add r1, r6, #0
	str r0, [sp, #0x10]
	add r0, r7, #0
	bl GetMonExpBySpeciesAndLevel
	mov r1, #0xc0
	mul r1, r4
	add r2, r5, r1
	ldr r1, _02255BE8 ; =0x00002DA4
	ldr r1, [r2, r1]
	sub r0, r1, r0
	str r0, [sp, #0x14]
	add r0, r7, #0
	add r1, r6, #1
	bl GetMonExpBySpeciesAndLevel
	add r5, r0, #0
	add r0, r7, #0
	add r1, r6, #0
	bl GetMonExpBySpeciesAndLevel
	sub r0, r5, r0
	str r0, [sp, #0x18]
	mov r0, #0x10
	str r0, [sp]
	ldr r0, [sp, #4]
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #0xc
	bl ov11_02254878
	add sp, #0x1c
	pop {r4, r5, r6, r7, pc}
	nop
_02255BE4: .word 0x0000219C
_02255BE8: .word 0x00002DA4

	thumb_func_start ov11_02255BEC
ov11_02255BEC: ; 0x02255BEC
	push {r4, r5, r6, r7, lr}
	sub sp, #0x3c
	str r0, [sp, #4]
	add r0, r1, #0
	mov ip, r2
	mov r5, #0xb5
	mov r2, #0x1a
	add r1, sp, #0xc
	strb r2, [r1]
	mov r3, #0xc0
	mov r2, ip
	mul r3, r2
	add r2, r0, r3
	lsl r5, r5, #6
	ldrh r4, [r2, r5]
	strh r4, [r1, #2]
	add r4, r5, #0
	add r4, #0x26
	ldrb r2, [r2, r4]
	add r5, #0x70
	lsl r2, r2, #0x1b
	lsr r2, r2, #0x1b
	strb r2, [r1, #8]
	add r2, r0, r5
	mov r1, #1
	ldr r4, [r2, r3]
	lsl r1, r1, #0x18
	tst r1, r4
	beq _02255C2A
	mov r4, #1
	b _02255C2C
_02255C2A:
	mov r4, #0
_02255C2C:
	add r1, sp, #0xc
	strb r4, [r1, #9]
	mov r1, #2
	ldr r4, [r2, r3]
	lsl r1, r1, #0x14
	tst r1, r4
	beq _02255C3E
	mov r4, #1
	b _02255C40
_02255C3E:
	mov r4, #0
_02255C40:
	add r1, sp, #0xc
	strb r4, [r1, #0xa]
	ldr r4, [r2, r3]
	mov r2, #2
	lsl r2, r2, #0x14
	tst r2, r4
	beq _02255C5E
	ldr r2, _02255CE8 ; =0x00002DFA
	add r4, r0, r3
	ldrh r3, [r4, r2]
	sub r2, #0x16
	strb r3, [r1, #1]
	ldr r1, [r4, r2]
	str r1, [sp, #0x10]
	b _02255C70
_02255C5E:
	ldr r2, _02255CEC ; =0x00002DBE
	add r4, r0, r3
	ldrb r3, [r4, r2]
	sub r2, #0x16
	lsl r3, r3, #0x1c
	lsr r3, r3, #0x1c
	strb r3, [r1, #1]
	ldr r1, [r4, r2]
	str r1, [sp, #0x10]
_02255C70:
	mov r1, #0
	str r1, [sp, #8]
	ldr r1, _02255CF0 ; =0x00002D66
	add r7, sp, #0xc
	add r3, r0, r1
	add r1, #0x58
	add r4, r7, #0
	add r5, r7, #0
	add r6, r0, r1
_02255C82:
	mov r1, #0xb5
	lsl r1, r1, #6
	ldrh r1, [r0, r1]
	strh r1, [r7, #0xc]
	ldrb r1, [r3]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1f
	strb r1, [r4, #0x18]
	ldrb r1, [r3]
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x1b
	strb r1, [r4, #0x1c]
	ldr r1, _02255CF4 ; =0x00002DB0
	ldr r2, [r0, r1]
	mov r1, #2
	lsl r1, r1, #0x14
	tst r1, r2
	beq _02255CB0
	ldr r1, _02255CE8 ; =0x00002DFA
	ldrh r1, [r0, r1]
	strb r1, [r4, #0x14]
	ldr r1, _02255CF8 ; =0x00002DE4
	b _02255CBA
_02255CB0:
	ldrb r1, [r6]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	strb r1, [r4, #0x14]
	ldr r1, _02255CFC ; =0x00002DA8
_02255CBA:
	ldr r1, [r0, r1]
	add r0, #0xc0
	str r1, [r5, #0x20]
	ldr r1, [sp, #8]
	add r7, r7, #2
	add r1, r1, #1
	add r3, #0xc0
	add r4, r4, #1
	add r5, r5, #4
	add r6, #0xc0
	str r1, [sp, #8]
	cmp r1, #4
	blt _02255C82
	mov r0, #0x30
	str r0, [sp]
	ldr r0, [sp, #4]
	mov r1, #1
	mov r2, ip
	add r3, sp, #0xc
	bl ov11_02254878
	add sp, #0x3c
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02255CE8: .word 0x00002DFA
_02255CEC: .word 0x00002DBE
_02255CF0: .word 0x00002D66
_02255CF4: .word 0x00002DB0
_02255CF8: .word 0x00002DE4
_02255CFC: .word 0x00002DA8

	thumb_func_start ov11_02255D00
ov11_02255D00: ; 0x02255D00
	push {r4, lr}
	sub sp, #8
	mov r4, #0x1b
	add r1, sp, #4
	strb r4, [r1]
	strh r2, [r1, #2]
	mov r1, #4
	str r1, [sp]
	add r2, r3, #0
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r4, pc}
	.align 2, 0

	thumb_func_start ov11_02255D20
ov11_02255D20: ; 0x02255D20
	push {r3, lr}
	sub sp, #8
	mov r1, #0x1c
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	mov r2, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_02255D3C
ov11_02255D3C: ; 0x02255D3C
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	mov ip, r1
	mov r3, #0x1d
	add r1, sp, #8
	strb r3, [r1]
	strb r2, [r1, #1]
	ldr r3, [r0, #0x30]
	mov r2, #0xc0
	mov r1, ip
	mul r2, r1
	ldr r1, _02255DF4 ; =0x00002DB0
	add r2, r3, r2
	ldr r2, [r2, r1]
	mov r1, #1
	lsl r1, r1, #0x18
	tst r1, r2
	beq _02255D64
	mov r2, #1
	b _02255D66
_02255D64:
	mov r2, #0
_02255D66:
	add r7, sp, #8
	add r1, sp, #8
	mov r3, #0
	strb r2, [r1, #2]
	str r3, [sp, #4]
	add r4, r7, #0
	add r5, r7, #0
_02255D74:
	ldr r1, [r0, #0x30]
	add r2, r1, r3
	mov r1, #0xb5
	lsl r1, r1, #6
	ldrh r1, [r2, r1]
	strh r1, [r7, #4]
	ldr r1, [r0, #0x30]
	add r2, r1, r3
	ldr r1, _02255DF8 ; =0x00002D66
	ldrb r1, [r2, r1]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1f
	strb r1, [r4, #0x10]
	ldr r1, [r0, #0x30]
	add r2, r1, r3
	ldr r1, _02255DF8 ; =0x00002D66
	ldrb r1, [r2, r1]
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x1b
	strb r1, [r4, #0x14]
	ldr r1, [r0, #0x30]
	add r6, r1, r3
	ldr r1, _02255DF4 ; =0x00002DB0
	ldr r2, [r6, r1]
	mov r1, #2
	lsl r1, r1, #0x14
	tst r1, r2
	beq _02255DBA
	ldr r1, _02255DFC ; =0x00002DFA
	ldrh r1, [r6, r1]
	strb r1, [r4, #0xc]
	ldr r1, [r0, #0x30]
	add r2, r1, r3
	ldr r1, _02255E00 ; =0x00002DE4
	b _02255DCA
_02255DBA:
	ldr r1, _02255E04 ; =0x00002DBE
	ldrb r1, [r6, r1]
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	strb r1, [r4, #0xc]
	ldr r1, [r0, #0x30]
	add r2, r1, r3
	ldr r1, _02255E08 ; =0x00002DA8
_02255DCA:
	ldr r1, [r2, r1]
	add r3, #0xc0
	str r1, [r5, #0x18]
	ldr r1, [sp, #4]
	add r7, r7, #2
	add r1, r1, #1
	add r4, r4, #1
	add r5, r5, #4
	str r1, [sp, #4]
	cmp r1, #4
	blt _02255D74
	mov r1, #0x28
	str r1, [sp]
	mov r1, #1
	mov r2, ip
	add r3, sp, #8
	bl ov11_02254878
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02255DF4: .word 0x00002DB0
_02255DF8: .word 0x00002D66
_02255DFC: .word 0x00002DFA
_02255E00: .word 0x00002DE4
_02255E04: .word 0x00002DBE
_02255E08: .word 0x00002DA8

	thumb_func_start ov11_02255E0C
ov11_02255E0C: ; 0x02255E0C
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	mov r3, #0x1e
	add r1, sp, #4
	strb r3, [r1]
	strb r2, [r1, #1]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r4, pc}

	thumb_func_start ov11_02255E2C
ov11_02255E2C: ; 0x02255E2C
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	mov r3, #0x1f
	add r1, sp, #4
	strb r3, [r1]
	strb r2, [r1, #1]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r4, pc}

	thumb_func_start ov11_02255E4C
ov11_02255E4C: ; 0x02255E4C
	push {r3, r4, r5, lr}
	sub sp, #0x68
	add r4, r2, #0
	str r3, [sp]
	str r4, [sp, #4]
	str r4, [sp, #8]
	mov r2, #0
	str r2, [sp, #0xc]
	add r2, sp, #0x10
	mov r3, #1
	add r5, r0, #0
	bl ov11_02256854
	mov r0, #0x58
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #0x10
	bl ov11_02254878
	add sp, #0x68
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02255E7C
ov11_02255E7C: ; 0x02255E7C
	push {r3, r4, r5, lr}
	sub sp, #0x68
	add r4, r2, #0
	ldr r2, [sp, #0x78]
	add r5, r0, #0
	str r2, [sp]
	str r4, [sp, #4]
	str r3, [sp, #8]
	mov r2, #0
	str r2, [sp, #0xc]
	add r2, sp, #0x10
	mov r3, #1
	bl ov11_02256854
	mov r0, #0x58
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #0x10
	bl ov11_02254878
	add sp, #0x68
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_02255EAC
ov11_02255EAC: ; 0x02255EAC
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	add r4, r2, #0
	mov r2, #0x20
	add r0, sp, #4
	strb r2, [r0]
	strb r3, [r0, #1]
	ldr r0, _02255EE8 ; =0x00003122
	ldrsh r2, [r1, r0]
	ldr r0, _02255EEC ; =0x00002E4C
	ldr r0, [r1, r0]
	sub r1, r2, r0
	mov r0, #0x64
	mul r0, r1
	add r1, r2, #0
	bl _s32_div_f
	add r1, sp, #4
	strh r0, [r1, #2]
	mov r0, #4
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_02255EE8: .word 0x00003122
_02255EEC: .word 0x00002E4C

	thumb_func_start ov11_02255EF0
ov11_02255EF0: ; 0x02255EF0
	push {r4, r5, r6, lr}
	sub sp, #8
	add r5, r0, #0
	add r6, r1, #0
	add r4, r2, #0
	mov r1, #0x21
	add r0, sp, #4
	strb r1, [r0]
	ldr r2, _02255F38 ; =0x00002E4C
	strb r3, [r0, #1]
	ldr r1, [r6, r2]
	cmp r1, #0
	bne _02255F12
	mov r1, #0xfa
	lsl r1, r1, #2
	strh r1, [r0, #2]
	b _02255F24
_02255F12:
	mov r0, #0xfa
	lsl r0, r0, #2
	mul r0, r1
	add r1, r2, #4
	ldr r1, [r6, r1]
	bl _u32_div_f
	add r1, sp, #4
	strh r0, [r1, #2]
_02255F24:
	mov r0, #4
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
_02255F38: .word 0x00002E4C

	thumb_func_start ov11_02255F3C
ov11_02255F3C: ; 0x02255F3C
	push {r3, lr}
	sub sp, #8
	mov r1, #0x22
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}

	thumb_func_start ov11_02255F54
ov11_02255F54: ; 0x02255F54
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r1, #0
	str r2, [sp, #4]
	mov r2, #0x23
	add r1, sp, #8
	add r6, r0, #0
	strb r2, [r1]
	mov r4, #0
	bl ov11_0222FF84
	cmp r0, #0
	ble _02255F86
	add r5, sp, #8
_02255F70:
	ldr r0, _02255F9C ; =0x0000219C
	add r1, r7, r4
	ldrb r0, [r1, r0]
	add r4, r4, #1
	strb r0, [r5, #4]
	add r0, r6, #0
	add r5, r5, #1
	bl ov11_0222FF84
	cmp r4, r0
	blt _02255F70
_02255F86:
	mov r0, #8
	str r0, [sp]
	ldr r2, [sp, #4]
	add r0, r6, #0
	mov r1, #1
	add r3, sp, #8
	bl ov11_02254878
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02255F9C: .word 0x0000219C

	thumb_func_start ov11_02255FA0
ov11_02255FA0: ; 0x02255FA0
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #0x24
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_02255FBC
ov11_02255FBC: ; 0x02255FBC
	push {r0, r1, r2, r3}
	push {r3, r4, r5, r6, lr}
	sub sp, #0x2c
	add r4, r1, #0
	add r5, r0, #0
	bl ov11_0222FF78
	add r1, r4, #0
	bl ov11_02243400
	mov r1, #0x25
	add r0, sp, #4
	strb r1, [r0]
	add r6, sp, #0x48
	add r3, sp, #8
	mov r2, #4
_02255FDC:
	ldmia r6!, {r0, r1}
	stmia r3!, {r0, r1}
	sub r2, r2, #1
	bne _02255FDC
	ldr r0, [r6]
	mov r1, #1
	str r0, [r3]
	mov r0, #0x28
	str r0, [sp]
	add r0, r5, #0
	add r2, r4, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #0x2c
	pop {r3, r4, r5, r6}
	pop {r3}
	add sp, #0x10
	bx r3
	.align 2, 0

	thumb_func_start ov11_02256004
ov11_02256004: ; 0x02256004
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #1
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_02256020
ov11_02256020: ; 0x02256020
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r1, #0
	ldr r1, _0225613C ; =0x0000219C
	add r4, r2, #0
	add r7, r5, r1
	ldrb r2, [r7, r4]
	add r1, r4, #0
	str r0, [sp, #4]
	bl ov11_02230014
	add r6, r0, #0
	mov r1, #5
	mov r2, #0
	bl GetMonData
	str r0, [sp, #0xc]
	add r0, r6, #0
	mov r1, #0xa0
	mov r2, #0
	bl GetMonData
	str r0, [sp, #8]
	mov r0, #0x26
	add r2, sp, #0x10
	strb r0, [r2]
	mov r0, #0xc0
	add r6, r4, #0
	mul r6, r0
	ldr r1, _02256140 ; =0x00002D74
	add r0, r5, r6
	ldrb r3, [r0, r1]
	strb r3, [r2, #1]
	add r3, r1, #0
	add r3, #0x18
	ldr r3, [r0, r3]
	add r1, #0x1c
	strh r3, [r2, #2]
	ldr r0, [r0, r1]
	add r1, r4, #0
	strh r0, [r2, #4]
	ldrb r0, [r7, r4]
	strb r0, [r2, #6]
	add r0, r5, #0
	bl ov11_0224524C
	add r1, sp, #0x10
	ldrb r2, [r1, #7]
	mov r3, #0x1f
	lsl r0, r0, #0x18
	bic r2, r3
	lsr r3, r0, #0x18
	mov r0, #0x1f
	and r0, r3
	orr r0, r2
	strb r0, [r1, #7]
	mov r0, #0xb5
	lsl r0, r0, #6
	add r7, r5, r0
	ldrh r0, [r7, r6]
	cmp r0, #0x1d
	beq _022560A0
	cmp r0, #0x20
	bne _022560BA
_022560A0:
	ldr r0, _02256144 ; =0x00002D54
	add r1, r5, r6
	ldr r0, [r1, r0]
	lsr r0, r0, #0x1f
	bne _022560BA
	add r0, sp, #0x10
	ldrb r1, [r0, #7]
	mov r2, #0x60
	bic r1, r2
	mov r2, #0x40
	orr r1, r2
	strb r1, [r0, #7]
	b _022560D4
_022560BA:
	add r3, sp, #0x10
	ldrb r2, [r3, #7]
	mov r0, #0x60
	add r1, r5, r6
	bic r2, r0
	ldr r0, _02256148 ; =0x00002DBE
	ldrb r0, [r1, r0]
	lsl r0, r0, #0x1c
	lsr r0, r0, #0x1c
	lsl r0, r0, #0x1e
	lsr r0, r0, #0x19
	orr r0, r2
	strb r0, [r3, #7]
_022560D4:
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #8]
	bl GetMonExpBySpeciesAndLevel
	mov r1, #0xc0
	mul r1, r4
	add r2, r5, r1
	ldr r1, _0225614C ; =0x00002DA4
	ldr r1, [r2, r1]
	sub r0, r1, r0
	ldr r1, [sp, #8]
	str r0, [sp, #0x18]
	ldr r0, [sp, #0xc]
	add r1, r1, #1
	bl GetMonExpBySpeciesAndLevel
	add r5, r0, #0
	ldr r0, [sp, #0xc]
	ldr r1, [sp, #8]
	bl GetMonExpBySpeciesAndLevel
	sub r0, r5, r0
	str r0, [sp, #0x1c]
	ldrh r1, [r7, r6]
	ldr r0, [sp, #4]
	bl ov11_02231668
	add r3, sp, #0x10
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	lsl r0, r0, #0x1f
	ldrb r1, [r3, #7]
	mov r2, #0x80
	lsr r0, r0, #0x18
	bic r1, r2
	orr r0, r1
	strb r0, [r3, #7]
	ldr r0, [sp, #4]
	bl ov11_02230E00
	str r0, [sp, #0x20]
	mov r0, #0x14
	str r0, [sp]
	ldr r0, [sp, #4]
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #0x10
	bl ov11_02254878
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	nop
_0225613C: .word 0x0000219C
_02256140: .word 0x00002D74
_02256144: .word 0x00002D54
_02256148: .word 0x00002DBE
_0225614C: .word 0x00002DA4

	thumb_func_start ov11_02256150
ov11_02256150: ; 0x02256150
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x30
	add r6, r1, #0
	str r2, [sp, #8]
	mov r1, #0x27
	add r2, sp, #0x10
	strb r1, [r2]
	ldrb r1, [r2, #1]
	mov r3, #0xf
	str r0, [sp, #4]
	bic r1, r3
	ldr r3, [sp, #8]
	add r4, r6, r3
	ldr r3, _02256230 ; =0x0000219C
	ldrb r4, [r4, r3]
	mov r3, #0xf
	and r3, r4
	orr r1, r3
	strb r1, [r2, #1]
	ldr r1, [sp, #8]
	mov r3, #0xc0
	mul r3, r1
	ldrb r4, [r2, #1]
	mov r1, #0xf0
	str r3, [sp, #0xc]
	bic r4, r1
	add r1, r3, #0
	add r3, r6, r1
	ldr r1, _02256234 ; =0x00002DCC
	ldr r5, [r3, r1]
	lsl r5, r5, #0x1a
	lsr r5, r5, #0x1c
	lsl r5, r5, #0x18
	lsr r5, r5, #0x18
	lsl r5, r5, #0x1c
	lsr r5, r5, #0x18
	orr r4, r5
	strb r4, [r2, #1]
	add r4, r1, #0
	sub r4, #0x40
	ldr r4, [r3, r4]
	sub r1, #0x14
	strh r4, [r2, #2]
	ldrh r1, [r3, r1]
	strh r1, [r2, #0xc]
	ldr r1, [sp, #8]
	bl ov11_02230270
	lsl r0, r0, #3
	add r1, r6, r0
	mov r0, #0x71
	lsl r0, r0, #2
	ldr r0, [r1, r0]
	ldr r1, [sp, #8]
	mov r2, #0xc0
	mul r2, r1
	lsl r0, r0, #3
	lsr r0, r0, #0x1a
	add r1, r6, r2
	mov ip, r2
	add r2, sp, #0x10
	str r0, [sp, #0x18]
	ldr r7, _02256238 ; =0x00002D6C
	mov r0, #0
	add r3, r1, #0
	add r4, r2, #0
_022561D4:
	ldr r5, _0225623C ; =0x00002D4C
	add r0, r0, #1
	ldrh r5, [r1, r5]
	add r1, r1, #2
	strh r5, [r2, #0xe]
	ldrb r5, [r3, r7]
	add r2, r2, #2
	add r3, r3, #1
	strb r5, [r4, #0x16]
	add r4, r4, #1
	cmp r0, #4
	blt _022561D4
	add r1, sp, #0x10
	mov r0, #2
	ldrsh r0, [r1, r0]
	cmp r0, #0
	beq _0225620C
	mov r0, ip
	add r3, r6, r0
	ldr r0, _02256240 ; =0x00002DAC
	ldr r1, _02256244 ; =0xFFFFF0FF
	ldr r2, [r3, r0]
	add r0, r0, #4
	and r1, r2
	str r1, [sp, #0x14]
	ldr r0, [r3, r0]
	str r0, [sp, #0x2c]
	b _0225621A
_0225620C:
	mov r0, #0
	str r0, [sp, #0x14]
	ldr r0, [sp, #0xc]
	add r1, r6, r0
	ldr r0, _02256248 ; =0x00002DB0
	ldr r0, [r1, r0]
	str r0, [sp, #0x2c]
_0225621A:
	mov r0, #0x20
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r2, [sp, #8]
	mov r1, #1
	add r3, sp, #0x10
	bl ov11_02254878
	add sp, #0x30
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02256230: .word 0x0000219C
_02256234: .word 0x00002DCC
_02256238: .word 0x00002D6C
_0225623C: .word 0x00002D4C
_02256240: .word 0x00002DAC
_02256244: .word 0xFFFFF0FF
_02256248: .word 0x00002DB0

	thumb_func_start ov11_0225624C
ov11_0225624C: ; 0x0225624C
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #0x28
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_02256268
ov11_02256268: ; 0x02256268
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #0x29
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_02256284
ov11_02256284: ; 0x02256284
	push {r3, r4, r5, lr}
	sub sp, #8
	mov r5, #0x2a
	add r4, sp, #4
	strb r5, [r4]
	strh r3, [r4, #2]
	mov r3, #0xc0
	mul r3, r2
	add r3, r1, r3
	ldr r1, _022562AC ; =0x00002D67
	ldrb r1, [r3, r1]
	add r3, sp, #4
	strb r1, [r4, #1]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	bl ov11_02254878
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0
_022562AC: .word 0x00002D67

	thumb_func_start ov11_022562B0
ov11_022562B0: ; 0x022562B0
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	add r7, r0, #0
	add r4, r2, #0
	add r6, r3, #0
	bl ov11_0222FF78
	add r1, r5, #0
	bl ov11_02243400
	mov r1, #0x2b
	add r0, sp, #4
	strb r1, [r0]
	strh r4, [r0, #2]
	strb r6, [r0, #1]
	mov r0, #4
	str r0, [sp]
	add r0, r7, #0
	mov r1, #1
	add r2, r5, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_022562E4
ov11_022562E4: ; 0x022562E4
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	mov r5, #0x2c
	add r1, sp, #4
	strb r5, [r1]
	strb r2, [r1, #1]
	strb r3, [r1, #2]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_02256308
ov11_02256308: ; 0x02256308
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r7, r1, #0
	mov r1, #0x2d
	add r3, sp, #4
	strb r1, [r3]
	mov r1, #0xc0
	add r6, r7, #0
	mul r6, r1
	ldr r1, [r0, #0x30]
	add r2, r1, r6
	mov r1, #0xb5
	lsl r1, r1, #6
	ldrh r2, [r2, r1]
	strh r2, [r3, #2]
	ldr r2, [r0, #0x30]
	add r4, r2, r6
	add r2, r1, #0
	add r2, #0x26
	ldrb r2, [r4, r2]
	lsl r2, r2, #0x1a
	lsr r2, r2, #0x1f
	strb r2, [r3, #5]
	ldr r2, [r0, #0x30]
	add r5, r2, r6
	add r2, r1, #0
	add r2, #0x70
	ldr r4, [r5, r2]
	mov r2, #2
	lsl r2, r2, #0x14
	tst r2, r4
	beq _0225635C
	add r2, r1, #0
	add r2, #0xba
	ldrh r2, [r5, r2]
	add r1, #0xa4
	strb r2, [r3, #4]
	ldr r2, [r0, #0x30]
	add r2, r2, r6
	ldr r1, [r2, r1]
	str r1, [sp, #0xc]
	b _02256372
_0225635C:
	add r2, r1, #0
	add r2, #0x7e
	ldrb r2, [r5, r2]
	add r1, #0x68
	lsl r2, r2, #0x1c
	lsr r2, r2, #0x1c
	strb r2, [r3, #4]
	ldr r2, [r0, #0x30]
	add r2, r2, r6
	ldr r1, [r2, r1]
	str r1, [sp, #0xc]
_02256372:
	ldr r1, [r0, #0x30]
	add r3, sp, #4
	add r2, r1, r6
	ldr r1, _02256394 ; =0x00002D66
	ldrb r1, [r2, r1]
	lsl r1, r1, #0x1b
	lsr r2, r1, #0x1b
	add r1, sp, #4
	strb r2, [r1, #1]
	mov r1, #0xc
	str r1, [sp]
	mov r1, #1
	add r2, r7, #0
	bl ov11_02254878
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02256394: .word 0x00002D66

	thumb_func_start ov11_02256398
ov11_02256398: ; 0x02256398
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #0x2e
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_022563B4
ov11_022563B4: ; 0x022563B4
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #0x2f
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_022563D0
ov11_022563D0: ; 0x022563D0
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	str r4, [sp]
	ldr r1, [r5, #0x30]
	add r2, sp, #4
	mov r3, #0x30
	bl ov11_022569DC
	mov r0, #8
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov11_022563F8
ov11_022563F8: ; 0x022563F8
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	str r4, [sp]
	ldr r1, [r5, #0x30]
	add r2, sp, #4
	mov r3, #0x31
	bl ov11_022569DC
	mov r0, #8
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov11_02256420
ov11_02256420: ; 0x02256420
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	str r4, [sp]
	ldr r1, [r5, #0x30]
	add r2, sp, #4
	mov r3, #0x32
	bl ov11_022569DC
	mov r0, #8
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov11_02256448
ov11_02256448: ; 0x02256448
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	str r4, [sp]
	ldr r1, [r5, #0x30]
	add r2, sp, #4
	mov r3, #0x33
	bl ov11_022569DC
	mov r0, #8
	str r0, [sp]
	add r0, r5, #0
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #0xc
	pop {r4, r5, pc}

	thumb_func_start ov11_02256470
ov11_02256470: ; 0x02256470
	push {r3, lr}
	sub sp, #8
	mov r1, #0x34
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	mov r2, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_0225648C
ov11_0225648C: ; 0x0225648C
	push {r3, lr}
	sub sp, #8
	mov r1, #0x35
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	mov r2, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_022564A8
ov11_022564A8: ; 0x022564A8
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	mov r5, #0x36
	add r1, sp, #4
	strb r5, [r1]
	strb r2, [r1, #1]
	strh r3, [r1, #2]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, r4, r5, pc}
	.align 2, 0

	thumb_func_start ov11_022564CC
ov11_022564CC: ; 0x022564CC
	push {r3, r4, r5, lr}
	sub sp, #8
	add r4, r1, #0
	mov r1, #0x37
	add r5, r0, #0
	str r1, [sp, #4]
	bl ov11_0222FF74
	mov r1, #4
	tst r0, r1
	beq _022564F0
	str r1, [sp]
	add r0, r5, #0
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #4
	bl ov11_02254878
_022564F0:
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_022564F4
ov11_022564F4: ; 0x022564F4
	push {r4, r5, r6, r7, lr}
	sub sp, #0x64
	str r0, [sp, #4]
	add r0, r1, #0
	str r2, [sp, #8]
	mov r2, #0x38
	add r7, sp, #0xc
	add r1, sp, #0xc
	strb r2, [r1]
	mov r1, #0
	mov ip, r1
	ldr r1, _0225658C ; =0x00002D66
	add r4, r7, #0
	add r3, r0, r1
	add r1, #0x58
	add r5, r7, #0
	add r6, r0, r1
_02256516:
	mov r1, #0xb5
	lsl r1, r1, #6
	ldrh r1, [r0, r1]
	add r2, r4, #0
	add r2, #0x24
	strh r1, [r7, #0x18]
	ldrb r1, [r3]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1f
	strb r1, [r2]
	ldrb r1, [r3]
	add r2, r4, #0
	add r2, #0x28
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x1b
	strb r1, [r2]
	ldr r1, _02256590 ; =0x00002DB0
	ldr r2, [r0, r1]
	mov r1, #2
	lsl r1, r1, #0x14
	tst r1, r2
	beq _02256550
	ldr r1, _02256594 ; =0x00002DFA
	add r2, r4, #0
	ldrh r1, [r0, r1]
	add r2, #0x20
	strb r1, [r2]
	ldr r1, _02256598 ; =0x00002DE4
	b _0225655E
_02256550:
	ldrb r1, [r6]
	add r2, r4, #0
	add r2, #0x20
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	strb r1, [r2]
	ldr r1, _0225659C ; =0x00002DA8
_0225655E:
	ldr r1, [r0, r1]
	add r0, #0xc0
	str r1, [r5, #0x2c]
	mov r1, ip
	add r1, r1, #1
	add r7, r7, #2
	add r3, #0xc0
	add r4, r4, #1
	add r5, r5, #4
	add r6, #0xc0
	mov ip, r1
	cmp r1, #4
	blt _02256516
	mov r0, #0x58
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r2, [sp, #8]
	mov r1, #1
	add r3, sp, #0xc
	bl ov11_02254878
	add sp, #0x64
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_0225658C: .word 0x00002D66
_02256590: .word 0x00002DB0
_02256594: .word 0x00002DFA
_02256598: .word 0x00002DE4
_0225659C: .word 0x00002DA8

	thumb_func_start ov11_022565A0
ov11_022565A0: ; 0x022565A0
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #0x39
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_022565BC
ov11_022565BC: ; 0x022565BC
	push {r3, lr}
	sub sp, #8
	add r2, r1, #0
	mov r1, #0x3a
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_022565D8
ov11_022565D8: ; 0x022565D8
	push {r3, lr}
	sub sp, #8
	mov r1, #0x3b
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	mov r2, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_022565F4
ov11_022565F4: ; 0x022565F4
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #8
	add r5, r1, #0
	mov r2, #0x3c
	add r1, sp, #4
	strb r2, [r1]
	mov r4, #0
	add r6, r0, #0
	strb r4, [r1, #1]
	bl ov11_0222FF84
	cmp r0, #0
	ble _02256632
	add r7, sp, #4
_02256610:
	ldr r0, _02256648 ; =0x000021A8
	ldr r0, [r5, r0]
	cmp r0, #0x10
	bne _02256624
	add r0, r4, #0
	bl MaskOfFlagNo
	ldrb r1, [r7, #1]
	orr r0, r1
	strb r0, [r7, #1]
_02256624:
	add r0, r6, #0
	add r5, #0x10
	add r4, r4, #1
	bl ov11_0222FF84
	cmp r4, r0
	blt _02256610
_02256632:
	mov r0, #4
	str r0, [sp]
	add r0, r6, #0
	mov r1, #1
	mov r2, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02256648: .word 0x000021A8

	thumb_func_start ov11_0225664C
ov11_0225664C: ; 0x0225664C
	push {r3, lr}
	sub sp, #8
	mov r1, #0x3d
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	mov r2, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_02256668
ov11_02256668: ; 0x02256668
	push {r4, r5, r6, r7, lr}
	sub sp, #0x64
	str r0, [sp, #4]
	add r0, r1, #0
	str r2, [sp, #8]
	mov r2, #0x3e
	add r7, sp, #0xc
	add r1, sp, #0xc
	strb r2, [r1]
	mov r1, #0
	mov ip, r1
	ldr r1, _02256700 ; =0x00002D66
	add r4, r7, #0
	add r3, r0, r1
	add r1, #0x58
	add r5, r7, #0
	add r6, r0, r1
_0225668A:
	mov r1, #0xb5
	lsl r1, r1, #6
	ldrh r1, [r0, r1]
	add r2, r4, #0
	add r2, #0x24
	strh r1, [r7, #0x18]
	ldrb r1, [r3]
	lsl r1, r1, #0x1a
	lsr r1, r1, #0x1f
	strb r1, [r2]
	ldrb r1, [r3]
	add r2, r4, #0
	add r2, #0x28
	lsl r1, r1, #0x1b
	lsr r1, r1, #0x1b
	strb r1, [r2]
	ldr r1, _02256704 ; =0x00002DB0
	ldr r2, [r0, r1]
	mov r1, #2
	lsl r1, r1, #0x14
	tst r1, r2
	beq _022566C4
	ldr r1, _02256708 ; =0x00002DFA
	add r2, r4, #0
	ldrh r1, [r0, r1]
	add r2, #0x20
	strb r1, [r2]
	ldr r1, _0225670C ; =0x00002DE4
	b _022566D2
_022566C4:
	ldrb r1, [r6]
	add r2, r4, #0
	add r2, #0x20
	lsl r1, r1, #0x1c
	lsr r1, r1, #0x1c
	strb r1, [r2]
	ldr r1, _02256710 ; =0x00002DA8
_022566D2:
	ldr r1, [r0, r1]
	add r0, #0xc0
	str r1, [r5, #0x2c]
	mov r1, ip
	add r1, r1, #1
	add r7, r7, #2
	add r3, #0xc0
	add r4, r4, #1
	add r5, r5, #4
	add r6, #0xc0
	mov ip, r1
	cmp r1, #4
	blt _0225668A
	mov r0, #0x58
	str r0, [sp]
	ldr r0, [sp, #4]
	ldr r2, [sp, #8]
	mov r1, #1
	add r3, sp, #0xc
	bl ov11_02254878
	add sp, #0x64
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02256700: .word 0x00002D66
_02256704: .word 0x00002DB0
_02256708: .word 0x00002DFA
_0225670C: .word 0x00002DE4
_02256710: .word 0x00002DA8

	thumb_func_start ov11_02256714
ov11_02256714: ; 0x02256714
	push {r3, r4, r5, lr}
	sub sp, #8
	mov r3, #0x3f
	add r4, sp, #4
	strb r3, [r4]
	ldr r3, _02256750 ; =0x0000216C
	ldr r5, [r1, r3]
	mov r1, #2
	add r3, r5, #0
	tst r3, r1
	beq _0225672E
	strb r1, [r4, #1]
	b _0225673E
_0225672E:
	mov r1, #4
	tst r1, r5
	beq _0225673A
	mov r1, #1
	strb r1, [r4, #1]
	b _0225673E
_0225673A:
	mov r1, #0
	strb r1, [r4, #1]
_0225673E:
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, r4, r5, pc}
	nop
_02256750: .word 0x0000216C

	thumb_func_start ov11_02256754
ov11_02256754: ; 0x02256754
	push {r4, lr}
	sub sp, #8
	add r4, r1, #0
	mov r3, #0x40
	add r1, sp, #4
	strb r3, [r1]
	strh r2, [r1, #2]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	add r2, r4, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r4, pc}

	thumb_func_start ov11_02256774
ov11_02256774: ; 0x02256774
	push {r3, r4, lr}
	sub sp, #0xc
	mov r2, #0x41
	add r1, sp, #4
	strb r2, [r1]
	add r4, r0, #0
	bl ov11_0223145C
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	mov r1, #1
	mov r2, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #0xc
	pop {r3, r4, pc}
	.align 2, 0

	thumb_func_start ov11_0225679C
ov11_0225679C: ; 0x0225679C
	push {r3, lr}
	sub sp, #8
	mov r1, #0x42
	str r1, [sp, #4]
	mov r1, #4
	str r1, [sp]
	mov r1, #1
	mov r2, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, pc}
	.align 2, 0

	thumb_func_start ov11_022567B8
ov11_022567B8: ; 0x022567B8
	push {r3, r4, r5, lr}
	sub sp, #8
	add r5, r0, #0
	add r0, sp, #4
	add r4, r1, #0
	strb r2, [r0]
	bl sub_02031190
	add r1, sp, #4
	strb r0, [r1, #1]
	mov r0, #4
	str r0, [sp]
	add r0, r5, #0
	mov r1, #2
	add r2, r4, #0
	add r3, sp, #4
	bl ov11_02254878
	add sp, #8
	pop {r3, r4, r5, pc}

	thumb_func_start ov11_022567E0
ov11_022567E0: ; 0x022567E0
	push {r3, r4, r5, r6, r7, lr}
	ldrb r6, [r1, #3]
	ldrb r3, [r1]
	ldrb r2, [r1, #2]
	lsl r6, r6, #8
	add r5, r0, #0
	orr r2, r6
	ldrb r4, [r1, #1]
	cmp r3, #0
	bne _02256814
	mov r3, #0
	cmp r2, #0
	ble _02256852
	mov r6, #0x23
	lsl r4, r4, #8
	lsl r6, r6, #8
_02256800:
	add r0, r1, r3
	ldr r7, [r5, #0x30]
	ldrb r0, [r0, #4]
	add r7, r4, r7
	add r7, r3, r7
	add r3, r3, #1
	strb r0, [r7, r6]
	cmp r3, r2
	blt _02256800
	pop {r3, r4, r5, r6, r7, pc}
_02256814:
	cmp r3, #1
	bne _02256836
	mov r0, #0
	cmp r2, #0
	ble _02256852
	lsl r3, r4, #2
	add r5, r5, r3
_02256822:
	add r3, r1, r0
	ldrb r4, [r3, #4]
	ldr r3, [r5, #0x34]
	add r3, r3, r0
	add r3, #0x94
	add r0, r0, #1
	strb r4, [r3]
	cmp r0, r2
	blt _02256822
	pop {r3, r4, r5, r6, r7, pc}
_02256836:
	cmp r3, #2
	bne _02256852
	ldrb r7, [r1, #4]
	ldrb r6, [r1, #5]
	bl ov11_02230DD4
	cmp r0, #0
	beq _02256852
	ldr r0, [r5, #0x30]
	add r1, r6, #0
	add r2, r4, #0
	add r3, r7, #0
	bl ov11_02243340
_02256852:
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov11_02256854
ov11_02256854: ; 0x02256854
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r5, r2, #0
	mov r1, #0x16
	strb r1, [r5]
	add r1, sp, #0x18
	ldrh r1, [r1, #0x1c]
	add r7, r0, #0
	strh r1, [r5, #2]
	ldr r1, [sp, #0x2c]
	strh r1, [r5, #0x14]
	ldr r1, [sp, #0x30]
	strh r1, [r5, #0x16]
	ldr r1, [sp, #0x28]
	str r3, [r5, #0x4c]
	str r1, [r5, #0x50]
	bl ov11_02230294
	str r0, [r5, #0x54]
	cmp r4, #0
	bne _02256882
	b _022569B2
_02256882:
	ldr r0, _022569B8 ; =0x00002144
	ldr r1, [r4, r0]
	add r0, #0x10
	str r1, [r5, #4]
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _02256892
	b _0225689E
_02256892:
	add r0, sp, #0x18
	ldrh r0, [r0, #0x1c]
	lsl r0, r0, #4
	add r1, r4, r0
	ldr r0, _022569BC ; =0x000003E1
	ldrb r0, [r1, r0]
_0225689E:
	ldr r1, [sp, #0x2c]
	strh r0, [r5, #8]
	mov r0, #0xc0
	add r6, r1, #0
	mul r6, r0
	ldr r0, _022569C0 ; =0x00002D75
	add r1, r4, r6
	ldrb r0, [r1, r0]
	add r1, r4, #0
	mov r2, #8
	strh r0, [r5, #0xc]
	mov r0, #0xd
	str r0, [sp]
	add r0, r7, #0
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	bne _022568E2
	mov r0, #0x4c
	str r0, [sp]
	add r0, r7, #0
	add r1, r4, #0
	mov r2, #8
	mov r3, #0
	bl ov11_02246870
	cmp r0, #0
	bne _022568E2
	mov r0, #6
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	str r0, [r5, #0x10]
	b _022568E6
_022568E2:
	mov r0, #0
	str r0, [r5, #0x10]
_022568E6:
	ldr r0, _022569C4 ; =0x00002164
	ldr r0, [r4, r0]
	strh r0, [r5, #0xa]
	ldr r0, _022569C8 ; =0x00002DB0
	add r1, r4, r0
	mov r0, #1
	ldr r2, [r1, r6]
	lsl r0, r0, #0x18
	tst r0, r2
	beq _022568FE
	mov r3, #1
	b _02256900
_022568FE:
	mov r3, #0
_02256900:
	ldrh r0, [r5, #0xe]
	mov r2, #1
	bic r0, r2
	lsl r2, r3, #0x10
	lsr r3, r2, #0x10
	mov r2, #1
	and r3, r2
	orr r0, r3
	strh r0, [r5, #0xe]
	ldr r1, [r1, r6]
	lsl r0, r2, #0x15
	tst r0, r1
	bne _0225691C
	mov r2, #0
_0225691C:
	ldrh r0, [r5, #0xe]
	mov r1, #2
	str r5, [sp, #0x10]
	bic r0, r1
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	lsl r1, r1, #0x1f
	lsr r1, r1, #0x1e
	orr r0, r1
	strh r0, [r5, #0xe]
	ldr r0, _022569CC ; =0x00002D66
	mov r1, #0
	add r2, r4, r0
	add r0, #0x58
	add r3, r5, #0
	add r7, r4, r0
_0225693C:
	mov r0, #0xb5
	lsl r0, r0, #6
	ldrh r6, [r4, r0]
	ldr r0, [sp, #0x10]
	strh r6, [r0, #0x18]
	ldrb r0, [r2]
	lsl r0, r0, #0x1a
	lsr r6, r0, #0x1f
	add r0, r5, r1
	str r0, [sp, #8]
	add r0, #0x24
	str r0, [sp, #8]
	strb r6, [r0]
	ldrb r0, [r2]
	lsl r0, r0, #0x1b
	lsr r6, r0, #0x1b
	add r0, r5, r1
	str r0, [sp, #4]
	add r0, #0x28
	str r0, [sp, #4]
	strb r6, [r0]
	mov r0, #0xb7
	lsl r0, r0, #6
	ldr r0, [r4, r0]
	str r0, [r3, #0x3c]
	ldr r0, _022569C8 ; =0x00002DB0
	ldr r6, [r4, r0]
	mov r0, #2
	lsl r0, r0, #0x14
	tst r0, r6
	beq _0225698C
	ldr r0, _022569D0 ; =0x00002DFA
	ldrh r6, [r4, r0]
	add r0, r5, r1
	str r0, [sp, #0xc]
	add r0, #0x20
	str r0, [sp, #0xc]
	strb r6, [r0]
	ldr r0, _022569D4 ; =0x00002DE4
	b _0225699A
_0225698C:
	ldrb r0, [r7]
	lsl r0, r0, #0x1c
	lsr r6, r0, #0x1c
	add r0, r5, r1
	add r0, #0x20
	strb r6, [r0]
	ldr r0, _022569D8 ; =0x00002DA8
_0225699A:
	ldr r0, [r4, r0]
	add r1, r1, #1
	str r0, [r3, #0x2c]
	ldr r0, [sp, #0x10]
	add r4, #0xc0
	add r0, r0, #2
	str r0, [sp, #0x10]
	add r2, #0xc0
	add r3, r3, #4
	add r7, #0xc0
	cmp r1, #4
	blt _0225693C
_022569B2:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	nop
_022569B8: .word 0x00002144
_022569BC: .word 0x000003E1
_022569C0: .word 0x00002D75
_022569C4: .word 0x00002164
_022569C8: .word 0x00002DB0
_022569CC: .word 0x00002D66
_022569D0: .word 0x00002DFA
_022569D4: .word 0x00002DE4
_022569D8: .word 0x00002DA8

	thumb_func_start ov11_022569DC
ov11_022569DC: ; 0x022569DC
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x20
	str r0, [sp]
	ldr r0, [sp, #0x38]
	add r5, r2, #0
	str r1, [sp, #4]
	str r0, [sp, #0x38]
	mov r0, #0
	add r1, r5, #0
	mov r2, #8
	add r6, r3, #0
	bl MIi_CpuClearFast
	ldr r0, [sp]
	bl ov11_0222FF74
	add r4, r0, #0
	mov r0, #0xc
	and r0, r4
	strb r6, [r5]
	cmp r0, #0xc
	beq _02256A30
	mov r0, #0x10
	tst r0, r4
	beq _02256A1A
	ldr r0, [sp]
	ldr r1, [sp, #0x38]
	bl ov11_02230270
	cmp r0, #0
	bne _02256A30
_02256A1A:
	cmp r4, #0x4b
	bne _02256A2A
	ldr r0, [sp]
	ldr r1, [sp, #0x38]
	bl ov11_02230270
	cmp r0, #0
	bne _02256A30
_02256A2A:
	cmp r4, #0xcb
	beq _02256A30
	b _02256B66
_02256A30:
	ldr r0, [sp]
	ldr r1, [sp, #0x38]
	bl ov11_02230260
	cmp r0, #2
	beq _02256A48
	ldr r0, [sp]
	ldr r1, [sp, #0x38]
	bl ov11_02230260
	cmp r0, #3
	bne _02256A56
_02256A48:
	ldr r6, [sp, #0x38]
	ldr r0, [sp]
	add r1, r6, #0
	bl ov11_022302BC
	str r0, [sp, #0x38]
	b _02256A60
_02256A56:
	ldr r0, [sp]
	ldr r1, [sp, #0x38]
	bl ov11_022302BC
	add r6, r0, #0
_02256A60:
	ldr r0, [sp]
	add r1, r6, #0
	bl ov11_0222FF88
	mov r4, #0
	str r0, [sp, #0x10]
	add r7, r4, #0
	bl GetPartyCount
	cmp r0, #0
	ble _02256AE0
	mov r0, #6
	add r1, r6, #0
	mul r1, r0
	ldr r0, [sp, #4]
	add r6, r0, r1
_02256A80:
	ldr r1, _02256C00 ; =0x0000312C
	ldr r0, [sp, #0x10]
	ldrb r1, [r6, r1]
	bl GetPartyMonByIndex
	mov r1, #0xad
	mov r2, #0
	str r0, [sp, #0x14]
	bl GetMonData
	cmp r0, #0
	beq _02256AD2
	ldr r1, _02256C04 ; =0x000001EE
	cmp r0, r1
	beq _02256AD2
	ldr r0, [sp, #0x14]
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02256ACA
	ldr r0, [sp, #0x14]
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02256AC2
	add r1, r5, r4
	mov r0, #3
	strb r0, [r1, #2]
	b _02256AD0
_02256AC2:
	add r1, r5, r4
	mov r0, #1
	strb r0, [r1, #2]
	b _02256AD0
_02256ACA:
	add r1, r5, r4
	mov r0, #2
	strb r0, [r1, #2]
_02256AD0:
	add r4, r4, #1
_02256AD2:
	ldr r0, [sp, #0x10]
	add r6, r6, #1
	add r7, r7, #1
	bl GetPartyCount
	cmp r7, r0
	blt _02256A80
_02256AE0:
	ldr r0, [sp]
	ldr r1, [sp, #0x38]
	bl ov11_0222FF88
	str r0, [sp, #8]
	mov r4, #3
	mov r6, #0
	bl GetPartyCount
	cmp r0, #0
	bgt _02256AF8
	b _02256BFA
_02256AF8:
	ldr r0, [sp, #0x38]
	mov r1, #6
	mul r1, r0
	ldr r0, [sp, #4]
	add r7, r0, r1
_02256B02:
	ldr r1, _02256C00 ; =0x0000312C
	ldr r0, [sp, #8]
	ldrb r1, [r7, r1]
	bl GetPartyMonByIndex
	mov r1, #0xad
	mov r2, #0
	str r0, [sp, #0x18]
	bl GetMonData
	cmp r0, #0
	beq _02256B54
	ldr r1, _02256C04 ; =0x000001EE
	cmp r0, r1
	beq _02256B54
	ldr r0, [sp, #0x18]
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02256B4C
	ldr r0, [sp, #0x18]
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02256B44
	add r1, r5, r4
	mov r0, #3
	strb r0, [r1, #2]
	b _02256B52
_02256B44:
	add r1, r5, r4
	mov r0, #1
	strb r0, [r1, #2]
	b _02256B52
_02256B4C:
	add r1, r5, r4
	mov r0, #2
	strb r0, [r1, #2]
_02256B52:
	add r4, r4, #1
_02256B54:
	ldr r0, [sp, #8]
	add r7, r7, #1
	add r6, r6, #1
	bl GetPartyCount
	cmp r6, r0
	blt _02256B02
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
_02256B66:
	mov r0, #2
	tst r0, r4
	beq _02256B7A
	mov r0, #8
	tst r0, r4
	bne _02256B7A
	ldr r0, [sp, #0x38]
	mov r1, #1
	and r0, r1
	str r0, [sp, #0x38]
_02256B7A:
	ldr r0, [sp]
	ldr r1, [sp, #0x38]
	bl ov11_0222FF88
	mov r4, #0
	str r0, [sp, #0xc]
	add r7, r4, #0
	bl GetPartyCount
	cmp r0, #0
	ble _02256BFA
	ldr r0, [sp, #0x38]
	mov r1, #6
	mul r1, r0
	ldr r0, [sp, #4]
	add r6, r0, r1
_02256B9A:
	ldr r1, _02256C00 ; =0x0000312C
	ldr r0, [sp, #0xc]
	ldrb r1, [r6, r1]
	bl GetPartyMonByIndex
	mov r1, #0xad
	mov r2, #0
	str r0, [sp, #0x1c]
	bl GetMonData
	cmp r0, #0
	beq _02256BEC
	ldr r1, _02256C04 ; =0x000001EE
	cmp r0, r1
	beq _02256BEC
	ldr r0, [sp, #0x1c]
	mov r1, #0xa2
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02256BE4
	ldr r0, [sp, #0x1c]
	mov r1, #0x9f
	mov r2, #0
	bl GetMonData
	cmp r0, #0
	beq _02256BDC
	add r1, r5, r4
	mov r0, #3
	strb r0, [r1, #2]
	b _02256BEA
_02256BDC:
	add r1, r5, r4
	mov r0, #1
	strb r0, [r1, #2]
	b _02256BEA
_02256BE4:
	add r1, r5, r4
	mov r0, #2
	strb r0, [r1, #2]
_02256BEA:
	add r4, r4, #1
_02256BEC:
	ldr r0, [sp, #0xc]
	add r6, r6, #1
	add r7, r7, #1
	bl GetPartyCount
	cmp r7, r0
	blt _02256B9A
_02256BFA:
	add sp, #0x20
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02256C00: .word 0x0000312C
_02256C04: .word 0x000001EE
