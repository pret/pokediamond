	.include "global.inc"
	.include "asm/macros.inc"

	.data

	.global UNK_02106E48
UNK_02106E48: ; 0x02106E48
	.word 0x00000000, 0x40240000
	.word 0x00000000, 0x40590000
	.word 0x00000000, 0x408F4000
	.word 0x00000000, 0x40C38800
	.word 0x00000000, 0x40F86A00
	.word 0x00000000, 0x412E8480
	.word 0x00000000, 0x416312D0
	.word 0x00000000, 0x4197D784

	.global UNK_02106E88
UNK_02106E88: ; 0x02106E88
	.asciz "542101086242752217003726400434970855712890625"

	.balign 4, 0
	.global UNK_02106EB8
UNK_02106EB8: ; 0x02106EB8
	.asciz "11102230246251565404236316680908203125"

	.balign 4, 0
	.global UNK_02106EE0
UNK_02106EE0: ; 0x02106EE0
	.asciz "23283064365386962890625"

	.balign 4, 0
	.global UNK_02106EF8
UNK_02106EF8: ; 0x02106EF8
	.asciz "152587890625"

	.balign 4, 0
	.global UNK_02106F08
UNK_02106F08: ; 0x02106F08
	.asciz "390625"

	.balign 4, 0
	.global UNK_02106F10
UNK_02106F10: ; 0x02106F10
	.asciz "78125"

	.balign 4, 0
	.global UNK_02106F18
UNK_02106F18: ; 0x02106F18
	.asciz "15625"

	.balign 4, 0
	.global UNK_02106F20
UNK_02106F20: ; 0x02106F20
	.asciz "3125"

	.balign 4, 0
	.global UNK_02106F28
UNK_02106F28: ; 0x02106F28
	.asciz "625"

	.balign 4, 0
	.global UNK_02106F2C
UNK_02106F2C: ; 0x02106F2C
	.asciz "125"

	.balign 4, 0
	.global UNK_02106F30
UNK_02106F30: ; 0x02106F30
	.asciz "25"

	.balign 4, 0
	.global UNK_02106F34
UNK_02106F34: ; 0x02106F34
	.asciz "5"

	.balign 4, 0
	.global UNK_02106F38
UNK_02106F38: ; 0x02106F38
	.asciz "1"

	.balign 4, 0
	.global UNK_02106F3C
UNK_02106F3C: ; 0x02106F3C
	.asciz "2"

	.balign 4, 0
	.global UNK_02106F40
UNK_02106F40: ; 0x02106F40
	.asciz "4"

	.balign 4, 0
	.global UNK_02106F44
UNK_02106F44: ; 0x02106F44
	.asciz "8"

	.balign 4, 0
	.global UNK_02106F48
UNK_02106F48: ; 0x02106F48
	.asciz "16"

	.balign 4, 0
	.global UNK_02106F4C
UNK_02106F4C: ; 0x02106F4C
	.asciz "32"

	.balign 4, 0
	.global UNK_02106F50
UNK_02106F50: ; 0x02106F50
	.asciz "64"

	.balign 4, 0
	.global UNK_02106F54
UNK_02106F54: ; 0x02106F54
	.asciz "128"

	.balign 4, 0
	.global UNK_02106F58
UNK_02106F58: ; 0x02106F58
	.asciz "256"

	.balign 4, 0
	.global UNK_02106F5C
UNK_02106F5C: ; 0x02106F5C
	.asciz "179769313486231580793728714053034151"

	.text

	arm_func_start __must_round
__must_round: ; 0x020E8570
	add r3, r0, #0x5
	ldrb r2, [r3, r1]
	add r12, r3, r1
	cmp r2, #0x5
	movhi r0, #0x1
	bxhi lr
	mvncc r0, #0x0
	bxcc lr
	ldrb r2, [r0, #0x4]
	add r12, r12, #0x1
	add r3, r3, r2
	cmp r12, r3
	bhs _020E85C0
_020E85A4:
	ldrb r2, [r12, #0x0]
	cmp r2, #0x0
	movne r0, #0x1
	bxne lr
	add r12, r12, #0x1
	cmp r12, r3
	blo _020E85A4
_020E85C0:
	sub r1, r1, #0x1
	add r0, r0, r1
	ldrb r0, [r0, #0x5]
	tst r0, #0x1
	movne r0, #0x1
	mvneq r0, #0x0
	bx lr
	arm_func_end __must_round

	arm_func_start __dorounddecup
__dorounddecup: ; 0x020E85DC
	add r3, r0, #0x5
	add r1, r3, r1
	sub r12, r1, #0x1
	mov r1, #0x0
_020E85EC:
	ldrb r2, [r12, #0x0]
	cmp r2, #0x9
	addcc r0, r2, #0x1
	strccb r0, [r12, #0x0]
	bxcc lr
	cmp r12, r3
	bne _020E8620
	mov r1, #0x1
	strb r1, [r12, #0x0]
	ldrsh r1, [r0, #0x2]
	add r1, r1, #0x1
	strh r1, [r0, #0x2]
	bx lr
_020E8620:
	strb r1, [r12], #-0x1
	b _020E85EC
	bx lr
	arm_func_end __dorounddecup

	arm_func_start __rounddec
__rounddec: ; 0x020E862C
	stmdb sp!, {r3-r5,lr}
	mov r4, r1
	mov r5, r0
	cmp r4, #0x0
	ldmleia sp!, {r3-r5,pc}
	ldrb r2, [r5, #0x4]
	cmp r4, r2
	ldmgeia sp!, {r3-r5,pc}
	bl __must_round
	strb r4, [r5, #0x4]
	cmp r0, #0x0
	ldmltia sp!, {r3-r5,pc}
	mov r0, r5
	mov r1, r4
	bl __dorounddecup
	ldmia sp!, {r3-r5,pc}
	arm_func_end __rounddec

	arm_func_start __ull2dec
__ull2dec: ; 0x020E866C
	stmdb sp!, {r3-r11,lr}
	mov r10, r0
	mov r0, #0x0
	mov r8, r2
	strb r0, [r10, #0x0]
	mov r9, r1
	cmp r8, #0x0
	strb r0, [r10, #0x4]
	cmpeq r9, #0x0
	beq _020E86F8
	mov r6, #0xa
	mov r11, r0
	mov r5, r0
	mov r4, r0
_020E86A4:
	ldrb r1, [r10, #0x4]
	mov r0, r9
	mov r2, r6
	add r3, r1, #0x1
	mov r7, r1
	strb r3, [r10, #0x4]
	mov r1, r8
	mov r3, r11
	bl _ull_mod
	add r1, r10, r7
	strb r0, [r1, #0x5]
	mov r0, r9
	mov r1, r8
	mov r2, #0xa
	mov r3, #0x0
	bl _ll_udiv
	mov r8, r1
	mov r9, r0
	cmp r8, r5
	cmpeq r9, r4
	bne _020E86A4
_020E86F8:
	ldrb r0, [r10, #0x4]
	add r2, r10, #0x5
	add r0, r2, r0
	sub r3, r0, #0x1
	cmp r2, r3
	bhs _020E8728
_020E8710:
	ldrb r0, [r3, #0x0]
	ldrb r1, [r2, #0x0]
	strb r0, [r2], #0x1
	strb r1, [r3], #-0x1
	cmp r2, r3
	blo _020E8710
_020E8728:
	ldrb r0, [r10, #0x4]
	sub r0, r0, #0x1
	strh r0, [r10, #0x2]
	ldmia sp!, {r3-r11,pc}
	arm_func_end __ull2dec

	arm_func_start __timesdec
__timesdec: ; 0x020E8738
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x40
	ldrb r6, [r1, #0x4]
	ldrb r5, [r2, #0x4]
	mov r4, #0x0
	add r3, sp, #0x0
	add r5, r6, r5
	sub r5, r5, #0x1
	add r3, r3, r5
	add r6, r3, #0x1
	mov r7, r6
	strb r4, [r0, #0x0]
	cmp r5, #0x0
	ble _020E8800
	add lr, r1, #0x5
	add r11, r2, #0x5
_020E8778:
	ldrb r3, [r2, #0x4]
	sub r10, r3, #0x1
	sub r3, r5, r10
	subs r9, r3, #0x1
	ldrb r3, [r1, #0x4]
	movmi r9, #0x0
	submi r10, r5, #0x1
	add r8, r10, #0x1
	sub r3, r3, r9
	cmp r8, r3
	movgt r8, r3
	add r10, r11, r10
	add r9, lr, r9
	cmp r8, #0x0
	ble _020E87CC
_020E87B4:
	ldrb r12, [r9], #0x1
	ldrb r3, [r10], #-0x1
	sub r8, r8, #0x1
	cmp r8, #0x0
	mla r4, r12, r3, r4
	bgt _020E87B4
_020E87CC:
	ldr r3, _020E88B8 ; =0xCCCCCCCD
	sub r5, r5, #0x1
	umull r8, r9, r4, r3
	mov r9, r9, lsr #0x3
	cmp r5, #0x0
	mov r10, #0xa
	umull r8, r9, r10, r9
	sub r9, r4, r8
	strb r9, [r6, #-0x1]!
	mov r8, r4
	umull r3, r4, r8, r3
	mov r4, r4, lsr #0x3
	bgt _020E8778
_020E8800:
	ldrsh r3, [r1, #0x2]
	ldrsh r1, [r2, #0x2]
	cmp r4, #0x0
	add r1, r3, r1
	strh r1, [r0, #0x2]
	beq _020E8828
	strb r4, [r6, #-0x1]!
	ldrsh r1, [r0, #0x2]
	add r1, r1, #0x1
	strh r1, [r0, #0x2]
_020E8828:
	mov r3, #0x0
	b _020E8840
_020E8830:
	ldrb r2, [r6], #0x1
	add r1, r0, r3
	add r3, r3, #0x1
	strb r2, [r1, #0x5]
_020E8840:
	cmp r3, #0x20
	bge _020E8850
	cmp r6, r7
	blo _020E8830
_020E8850:
	cmp r6, r7
	addcs sp, sp, #0x40
	strb r3, [r0, #0x4]
	ldmcsia sp!, {r3-r11,pc}
	ldrb r1, [r6, #0x0]
	cmp r1, #0x5
	addcc sp, sp, #0x40
	ldmccia sp!, {r3-r11,pc}
	bne _020E88A8
	add r2, r6, #0x1
	cmp r2, r7
	bhs _020E8898
_020E8880:
	ldrb r1, [r2, #0x0]
	cmp r1, #0x0
	bne _020E88A8
	add r2, r2, #0x1
	cmp r2, r7
	blo _020E8880
_020E8898:
	ldrb r1, [r6, #-0x1]
	tst r1, #0x1
	addeq sp, sp, #0x40
	ldmeqia sp!, {r3-r11,pc}
_020E88A8:
	ldrb r1, [r0, #0x4]
	bl __dorounddecup
	add sp, sp, #0x40
	ldmia sp!, {r3-r11,pc}
	.balign 4
_020E88B8: .word 0xCCCCCCCD
	arm_func_end __timesdec

	arm_func_start __str2dec
__str2dec: ; 0x020E88BC
	stmdb sp!, {r3,lr}
	strh r2, [r0, #0x2]
	mov r12, #0x0
	strb r12, [r0, #0x0]
	b _020E88E4
_020E88D0:
	ldrsb r3, [r1], #0x1
	add r2, r0, r12
	add r12, r12, #0x1
	sub r3, r3, #0x30
	strb r3, [r2, #0x5]
_020E88E4:
	cmp r12, #0x20
	bge _020E88F8
	ldrsb r2, [r1, #0x0]
	cmp r2, #0x0
	bne _020E88D0
_020E88F8:
	strb r12, [r0, #0x4]
	ldrsb r2, [r1, #0x0]
	cmp r2, #0x0
	ldmeqia sp!, {r3,pc}
	cmp r2, #0x5
	ldmltia sp!, {r3,pc}
	bgt _020E894C
	ldrsb r2, [r1, #0x1]
	add r1, r1, #0x1
	cmp r2, #0x0
	beq _020E8938
_020E8924:
	cmp r2, #0x30
	bne _020E894C
	ldrsb r2, [r1, #0x1]!
	cmp r2, #0x0
	bne _020E8924
_020E8938:
	sub r1, r12, #0x1
	add r1, r0, r1
	ldrb r1, [r1, #0x5]
	tst r1, #0x1
	ldmeqia sp!, {r3,pc}
_020E894C:
	ldrb r1, [r0, #0x4]
	bl __dorounddecup
	ldmia sp!, {r3,pc}
	arm_func_end __str2dec

	arm_func_start __two_exp
__two_exp: ; 0x020E8958
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4c
	mov r4, r1
	mvn r2, #0x34
	mov r5, r0
	cmp r4, r2
	bgt _020E8988
	bge _020E8A54
	sub r0, r2, #0xb
	cmp r4, r0
	beq _020E8A3C
	b _020E8BE4
_020E8988:
	add r1, r4, #0x20
	cmp r1, #0x28
	addls pc, pc, r1, lsl #0x2
	b _020E8BE4
	b _020E8A68 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8A7C ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8A90 ; case
	b _020E8AA4 ; case
	b _020E8AB8 ; case
	b _020E8ACC ; case
	b _020E8AE0 ; case
	b _020E8AF4 ; case
	b _020E8B08 ; case
	b _020E8B1C ; case
	b _020E8B30 ; case
	b _020E8B44 ; case
	b _020E8B58 ; case
	b _020E8B6C ; case
	b _020E8B80 ; case
	b _020E8B94 ; case
	b _020E8BA8 ; case
	b _020E8BBC ; case
	b _020E8BD0 ; case
_020E8A3C:
	ldr r1, _020E8C88 ; =UNK_02106E88
	mov r0, r5
	mvn r2, #0x13
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8A54:
	ldr r1, _020E8C8C ; =UNK_02106EB8
	add r2, r2, #0x25
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8A68:
	ldr r1, _020E8C90 ; =UNK_02106EE0
	add r2, r2, #0x2b
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8A7C:
	ldr r1, _020E8C94 ; =UNK_02106EF8
	add r2, r2, #0x30
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8A90:
	ldr r1, _020E8C98 ; =UNK_02106F08
	add r2, r2, #0x32
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8AA4:
	ldr r1, _020E8C9C ; =UNK_02106F10
	add r2, r2, #0x32
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8AB8:
	ldr r1, _020E8CA0 ; =UNK_02106F18
	add r2, r2, #0x33
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8ACC:
	ldr r1, _020E8CA4 ; =UNK_02106F20
	add r2, r2, #0x33
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8AE0:
	ldr r1, _020E8CA8 ; =UNK_02106F28
	add r2, r2, #0x33
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8AF4:
	ldr r1, _020E8CAC ; =UNK_02106F2C
	add r2, r2, #0x34
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B08:
	ldr r1, _020E8CB0 ; =UNK_02106F30
	add r2, r2, #0x34
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B1C:
	ldr r1, _020E8CB4 ; =UNK_02106F34
	add r2, r2, #0x34
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B30:
	ldr r1, _020E8CB8 ; =UNK_02106F38
	mov r2, #0x0
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B44:
	ldr r1, _020E8CBC ; =UNK_02106F3C
	mov r2, #0x0
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B58:
	ldr r1, _020E8CC0 ; =UNK_02106F40
	mov r2, #0x0
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B6C:
	ldr r1, _020E8CC4 ; =UNK_02106F44
	mov r2, #0x0
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B80:
	ldr r1, _020E8CC8 ; =UNK_02106F48
	mov r2, #0x1
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B94:
	ldr r1, _020E8CCC ; =UNK_02106F4C
	mov r2, #0x1
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8BA8:
	ldr r1, _020E8CD0 ; =UNK_02106F50
	mov r2, #0x1
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8BBC:
	ldr r1, _020E8CD4 ; =UNK_02106F54
	mov r2, #0x2
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8BD0:
	ldr r1, _020E8CD8 ; =UNK_02106F58
	mov r2, #0x2
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8BE4:
	and r0, r4, #0x80000000
	add r1, r4, r0, lsr #0x1f
	add r0, sp, #0x26
	mov r1, r1, asr #0x1
	bl __two_exp
	add r1, sp, #0x26
	mov r0, r5
	mov r2, r1
	bl __timesdec
	tst r4, #0x1
	addeq sp, sp, #0x4c
	ldmeqia sp!, {r4-r5,pc}
	add r3, sp, #0x0
	mov r12, r5
	mov r2, #0x9
_020E8C20:
	ldrh r1, [r12, #0x0]
	ldrh r0, [r12, #0x2]
	add r12, r12, #0x4
	subs r2, r2, #0x1
	strh r1, [r3, #0x0]
	strh r0, [r3, #0x2]
	add r3, r3, #0x4
	bne _020E8C20
	ldrh r0, [r12, #0x0]
	cmp r4, #0x0
	strh r0, [r3, #0x0]
	add r0, sp, #0x26
	ble _020E8C64
	ldr r1, _020E8CBC ; =UNK_02106F3C
	mov r2, #0x0
	bl __str2dec
	b _020E8C70
_020E8C64:
	ldr r1, _020E8CB4 ; =UNK_02106F34
	mvn r2, #0x0
	bl __str2dec
_020E8C70:
	add r1, sp, #0x0
	add r2, sp, #0x26
	mov r0, r5
	bl __timesdec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020E8C88: .word UNK_02106E88
_020E8C8C: .word UNK_02106EB8
_020E8C90: .word UNK_02106EE0
_020E8C94: .word UNK_02106EF8
_020E8C98: .word UNK_02106F08
_020E8C9C: .word UNK_02106F10
_020E8CA0: .word UNK_02106F18
_020E8CA4: .word UNK_02106F20
_020E8CA8: .word UNK_02106F28
_020E8CAC: .word UNK_02106F2C
_020E8CB0: .word UNK_02106F30
_020E8CB4: .word UNK_02106F34
_020E8CB8: .word UNK_02106F38
_020E8CBC: .word UNK_02106F3C
_020E8CC0: .word UNK_02106F40
_020E8CC4: .word UNK_02106F44
_020E8CC8: .word UNK_02106F48
_020E8CCC: .word UNK_02106F4C
_020E8CD0: .word UNK_02106F50
_020E8CD4: .word UNK_02106F54
_020E8CD8: .word UNK_02106F58
	arm_func_end __two_exp

	arm_func_start __equals_dec
__equals_dec:
	stmdb sp!, {r4,lr}
	ldrb r3, [r0, #0x5]
	cmp r3, #0x0
	bne _020E8D00
	ldrb r0, [r1, #0x5]
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	ldmia sp!, {r4,pc}
_020E8D00:
	ldrb r2, [r1, #0x5]
	cmp r2, #0x0
	bne _020E8D1C
	cmp r3, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	ldmia sp!, {r4,pc}
_020E8D1C:
	ldrsh r3, [r0, #0x2]
	ldrsh r2, [r1, #0x2]
	cmp r3, r2
	bne _020E8DB4
	ldrb r4, [r0, #0x4]
	ldrb r2, [r1, #0x4]
	mov r12, #0x0
	mov lr, r4
	cmp r4, r2
	movgt lr, r2
	cmp lr, #0x0
	ble _020E8D74
_020E8D4C:
	add r3, r0, r12
	add r2, r1, r12
	ldrb r3, [r3, #0x5]
	ldrb r2, [r2, #0x5]
	cmp r3, r2
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
	add r12, r12, #0x1
	cmp r12, lr
	blt _020E8D4C
_020E8D74:
	cmp lr, r4
	moveq r0, r1
	ldrb r1, [r0, #0x4]
	cmp r12, r1
	bge _020E8DAC
_020E8D88:
	add r1, r0, r12
	ldrb r1, [r1, #0x5]
	cmp r1, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
	ldrb r1, [r0, #0x4]
	add r12, r12, #0x1
	cmp r12, r1
	blt _020E8D88
_020E8DAC:
	mov r0, #0x1
	ldmia sp!, {r4,pc}
_020E8DB4:
	mov r0, #0x0
	ldmia sp!, {r4,pc}
	arm_func_end __equals_dec

	arm_func_start __less_dec
__less_dec:
	stmdb sp!, {r3-r5,lr}
	ldrb r2, [r0, #0x5]
	cmp r2, #0x0
	bne _020E8DE0
	ldrb r0, [r1, #0x5]
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	ldmia sp!, {r3-r5,pc}
_020E8DE0:
	ldrb r2, [r1, #0x5]
	cmp r2, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r3-r5,pc}
	ldrsh r3, [r1, #0x2]
	ldrsh r2, [r0, #0x2]
	cmp r2, r3
	bne _020E8E90
	ldrb r5, [r0, #0x4]
	ldrb r4, [r1, #0x4]
	mov r12, #0x0
	mov lr, r5
	cmp r5, r4
	movgt lr, r4
	cmp lr, #0x0
	ble _020E8E54
_020E8E20:
	add r3, r1, r12
	add r2, r0, r12
	ldrb r3, [r3, #0x5]
	ldrb r2, [r2, #0x5]
	cmp r2, r3
	movcc r0, #0x1
	ldmccia sp!, {r3-r5,pc}
	cmp r3, r2
	movcc r0, #0x0
	ldmccia sp!, {r3-r5,pc}
	add r12, r12, #0x1
	cmp r12, lr
	blt _020E8E20
_020E8E54:
	cmp lr, r5
	bne _020E8E88
	cmp r12, r4
	bge _020E8E88
_020E8E64:
	add r0, r1, r12
	ldrb r0, [r0, #0x5]
	cmp r0, #0x0
	movne r0, #0x1
	ldmneia sp!, {r3-r5,pc}
	ldrb r0, [r1, #0x4]
	add r12, r12, #0x1
	cmp r12, r0
	blt _020E8E64
_020E8E88:
	mov r0, #0x0
	ldmia sp!, {r3-r5,pc}
_020E8E90:
	movlt r0, #0x1
	movge r0, #0x0
	ldmia sp!, {r3-r5,pc}
	arm_func_end __less_dec

	arm_func_start __minus_dec
__minus_dec: ; 0x020E8E9C
	stmdb sp!, {r3-r7,lr}
	mov r6, r0
	mov r5, #0x9
_020E8EA8:
	ldrh r4, [r1, #0x0]
	ldrh r3, [r1, #0x2]
	add r1, r1, #0x4
	subs r5, r5, #0x1
	strh r4, [r6, #0x0]
	strh r3, [r6, #0x2]
	add r6, r6, #0x4
	bne _020E8EA8
	ldrh r1, [r1, #0x0]
	strh r1, [r6, #0x0]
	ldrb r1, [r2, #0x5]
	cmp r1, #0x0
	ldmeqia sp!, {r3-r7,pc}
	ldrb r7, [r0, #0x4]
	ldrb r3, [r2, #0x4]
	ldrsh r4, [r0, #0x2]
	mov r1, r7
	cmp r7, r3
	movlt r1, r3
	ldrsh r3, [r2, #0x2]
	sub r6, r4, r3
	add r1, r1, r6
	cmp r1, #0x20
	movgt r1, #0x20
	cmp r7, r1
	bge _020E8F34
	mov r4, #0x0
_020E8F14:
	ldrb r5, [r0, #0x4]
	add r3, r0, r7
	add r5, r5, #0x1
	strb r5, [r0, #0x4]
	strb r4, [r3, #0x5]
	ldrb r7, [r0, #0x4]
	cmp r7, r1
	blt _020E8F14
_020E8F34:
	ldrb r4, [r2, #0x4]
	add r3, r0, #0x5
	add r12, r3, r1
	add r4, r4, r6
	cmp r4, r1
	addlt r12, r3, r4
	sub r4, r12, r3
	add r1, r2, #0x5
	sub r4, r4, r6
	add lr, r1, r4
	mov r4, lr
	b _020E8FC8
_020E8F64:
	ldrb r7, [r12, #-0x1]!
	ldrb r5, [lr, #-0x1]!
	cmp r7, r5
	bhs _020E8FB8
	ldrb r7, [r12, #-0x1]
	sub r5, r12, #0x1
	cmp r7, #0x0
	bne _020E8F90
_020E8F84:
	ldrb r7, [r5, #-0x1]!
	cmp r7, #0x0
	beq _020E8F84
_020E8F90:
	cmp r5, r12
	beq _020E8FB8
_020E8F98:
	ldrb r7, [r5, #0x0]
	sub r7, r7, #0x1
	strb r7, [r5, #0x0]
	ldrb r7, [r5, #0x1]!
	cmp r5, r12
	add r7, r7, #0xa
	strb r7, [r5, #0x0]
	bne _020E8F98
_020E8FB8:
	ldrb r7, [r12, #0x0]
	ldrb r5, [lr, #0x0]
	sub r5, r7, r5
	strb r5, [r12, #0x0]
_020E8FC8:
	cmp r12, r3
	cmphi lr, r1
	bhi _020E8F64
	ldrb r5, [r2, #0x4]
	sub lr, r4, r1
	cmp lr, r5
	bge _020E90A4
	ldrb r1, [r4, #0x0]
	mov r7, #0x0
	cmp r1, #0x5
	movcc r7, #0x1
	blo _020E9040
	bne _020E9040
	add r1, r2, #0x5
	add r2, r1, r5
	add r4, r4, #0x1
	cmp r4, r2
	bhs _020E9028
_020E9010:
	ldrb r1, [r4, #0x0]
	cmp r1, #0x0
	bne _020E90A4
	add r4, r4, #0x1
	cmp r4, r2
	blo _020E9010
_020E9028:
	add r1, r3, lr
	add r2, r1, r6
	ldrb r1, [r2, #-0x1]
	sub r12, r2, #0x1
	tst r1, #0x1
	movne r7, #0x1
_020E9040:
	cmp r7, #0x0
	beq _020E90A4
	ldrb r1, [r12, #0x0]
	cmp r1, #0x1
	bhs _020E9098
	ldrb r1, [r12, #-0x1]
	sub r2, r12, #0x1
	cmp r1, #0x0
	bne _020E9070
_020E9064:
	ldrb r1, [r2, #-0x1]!
	cmp r1, #0x0
	beq _020E9064
_020E9070:
	cmp r2, r12
	beq _020E9098
_020E9078:
	ldrb r1, [r2, #0x0]
	sub r1, r1, #0x1
	strb r1, [r2, #0x0]
	ldrb r1, [r2, #0x1]!
	cmp r2, r12
	add r1, r1, #0xa
	strb r1, [r2, #0x0]
	bne _020E9078
_020E9098:
	ldrb r1, [r12, #0x0]
	sub r1, r1, #0x1
	strb r1, [r12, #0x0]
_020E90A4:
	ldrb r1, [r3, #0x0]
	mov r5, r3
	cmp r1, #0x0
	bne _020E90C0
_020E90B4:
	ldrb r1, [r5, #0x1]!
	cmp r1, #0x0
	beq _020E90B4
_020E90C0:
	cmp r5, r3
	bls _020E9108
	ldrsh r1, [r0, #0x2]
	sub r2, r5, r3
	and r4, r2, #0xff
	sub r1, r1, r4
	strh r1, [r0, #0x2]
	ldrb r1, [r0, #0x4]
	add r2, r3, r1
	cmp r5, r2
	bhs _020E90FC
_020E90EC:
	ldrb r1, [r5], #0x1
	cmp r5, r2
	strb r1, [r3], #0x1
	blo _020E90EC
_020E90FC:
	ldrb r1, [r0, #0x4]
	sub r1, r1, r4
	strb r1, [r0, #0x4]
_020E9108:
	ldrb r1, [r0, #0x4]
	add r2, r0, #0x5
	add r3, r2, r1
	cmp r3, r2
	bls _020E9130
_020E911C:
	ldrb r1, [r3, #-0x1]!
	cmp r1, #0x0
	bne _020E9130
	cmp r3, r2
	bhi _020E911C
_020E9130:
	sub r1, r3, r2
	add r1, r1, #0x1
	strb r1, [r0, #0x4]
	ldmia sp!, {r3-r7,pc}
	arm_func_end __minus_dec

	arm_func_start __num2dec_internal
__num2dec_internal:
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x58
	mov r8, r1
	mov r6, r2
	mov r7, r0
	mov r0, r8
	mov r1, r6
	bl __signbitf
	cmp r0, #0x0
	movne r1, #0x1
	moveq r1, #0x0
	mov r4, r1, lsl #0x18
	mov r0, #0x0
	mov r1, r0
	mov r2, r8
	mov r3, r6
	mov r5, r4, asr #0x18
	bl _deq
	bne _020E91AC
	strb r5, [r7, #0x0]
	mov r1, #0x0
	strh r1, [r7, #0x2]
	mov r0, #0x1
	strb r0, [r7, #0x4]
	add sp, sp, #0x58
	strb r1, [r7, #0x5]
	ldmia sp!, {r4-r8,pc}
_020E91AC:
	mov r0, r8
	mov r1, r6
	bl __fpclassifyf
	cmp r0, #0x2
	bgt _020E91F8
	strb r5, [r7, #0x0]
	mov r2, #0x0
	strh r2, [r7, #0x2]
	mov r2, #0x1
	mov r0, r8
	mov r1, r6
	strb r2, [r7, #0x4]
	bl __fpclassifyf
	cmp r0, #0x1
	moveq r0, #0x4e
	movne r0, #0x49
	add sp, sp, #0x58
	strb r0, [r7, #0x5]
	ldmia sp!, {r4-r8,pc}
_020E91F8:
	cmp r5, #0x0
	beq _020E921C
	mov r0, #0x0
	mov r1, r0
	mov r2, r8
	mov r3, r6
	bl _dsub
	mov r8, r0
	mov r6, r1
_020E921C:
	add r2, sp, #0x8
	mov r0, r8
	mov r1, r6
	bl frexp
	mov r4, r0
	mov r6, r1
	orr r12, r4, #0x0
	rsbs r2, r12, #0x0
	orr r3, r6, #0x100000
	rsc r1, r3, #0x0
	mov r0, #0x0
	and r3, r3, r1
	sub r1, r0, #0x1
	and r12, r12, r2
	mov r2, r1
	adds r0, r12, r1
	adc r1, r3, r2
	str r4, [sp, #0x0]
	str r6, [sp, #0x4]
	bl __msl_generic_count_bits64
	rsb r8, r0, #0x35
	ldr r1, [sp, #0x8]
	add r0, sp, #0xc
	sub r1, r1, r8
	bl __two_exp
	mov r0, r4
	mov r1, r6
	mov r2, r8
	bl ldexp
	bl _ll_ufrom_d
	mov r2, r1
	mov r1, r0
	add r0, sp, #0x32
	bl __ull2dec
	mov r0, r7
	add r1, sp, #0x32
	add r2, sp, #0xc
	bl __timesdec
	strb r5, [r7, #0x0]
	add sp, sp, #0x58
	ldmia sp!, {r4-r8,pc}
	arm_func_end __num2dec_internal

	arm_func_start __num2dec_internal2
__num2dec_internal2: ; 0x020E92C0
	stmdb sp!, {r3-r5,lr}
	mov r4, r3
	ldrsh r5, [r0, #0x2]
	mov r0, r4
	bl __num2dec_internal
	ldrb r0, [r4, #0x5]
	cmp r0, #0x9
	ldmhiia sp!, {r3-r5,pc}
	cmp r5, #0x20
	movgt r5, #0x20
	mov r0, r4
	mov r1, r5
	bl __rounddec
	ldrb r0, [r4, #0x4]
	cmp r0, r5
	bge _020E9324
	mov r1, #0x0
_020E9304:
	ldrb r2, [r4, #0x4]
	add r0, r4, r0
	add r2, r2, #0x1
	strb r2, [r4, #0x4]
	strb r1, [r0, #0x5]
	ldrb r0, [r4, #0x4]
	cmp r0, r5
	blt _020E9304
_020E9324:
	ldrsh r1, [r4, #0x2]
	sub r0, r0, #0x1
	mov r2, #0x0
	sub r0, r1, r0
	strh r0, [r4, #0x2]
	ldrb r0, [r4, #0x4]
	cmp r0, #0x0
	ldmleia sp!, {r3-r5,pc}
_020E9344:
	add r1, r4, r2
	ldrb r0, [r1, #0x5]
	add r2, r2, #0x1
	add r0, r0, #0x30
	strb r0, [r1, #0x5]
	ldrb r0, [r4, #0x4]
	cmp r2, r0
	blt _020E9344
	ldmia sp!, {r3-r5,pc}
	arm_func_end __num2dec_internal2

	arm_func_start __dec2num
__dec2num: ; 0x020E9368
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xfc
	mov r4, r0
	ldrb r0, [r4, #0x4]
	cmp r0, #0x0
	bne _020E93A8
	ldrsb r0, [r4, #0x0]
	mov r2, #0x0
	cmp r0, #0x0
	ldreq r3, _020E996C ; =0x3FF00000
	mov r0, #0x0
	ldrne r3, _020E9970 ; =0xBFF00000
	mov r1, r0
	bl copysign
	add sp, sp, #0xfc
	ldmia sp!, {r4-r11,pc}
_020E93A8:
	ldrb r0, [r4, #0x5]
	cmp r0, #0x30
	beq _020E93C8
	cmp r0, #0x49
	beq _020E93F0
	cmp r0, #0x4e
	beq _020E9424
	b _020E946C
_020E93C8:
	ldrsb r0, [r4, #0x0]
	mov r2, #0x0
	cmp r0, #0x0
	ldreq r3, _020E996C ; =0x3FF00000
	mov r0, #0x0
	ldrne r3, _020E9970 ; =0xBFF00000
	mov r1, r0
	bl copysign
	add sp, sp, #0xfc
	ldmia sp!, {r4-r11,pc}
_020E93F0:
	ldrsb r0, [r4, #0x0]
	mov r5, #0x0
	cmp r0, #0x0
	ldreq r4, _020E996C ; =0x3FF00000
	ldr r0, _020E9974 ; =__float_huge
	ldrne r4, _020E9970 ; =0xBFF00000
	ldr r0, [r0, #0x0]
	bl _f2d
	mov r2, r5
	mov r3, r4
	bl copysign
	add sp, sp, #0xfc
	ldmia sp!, {r4-r11,pc}
_020E9424:
	ldr r1, _020E9978 ; =0x7FF00000
	add r3, sp, #0x10
	mov r2, #0x0
	str r2, [r3, #0x0]
	str r1, [r3, #0x4]
	ldrsb r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020E9454
	orr r0, r1, #0x80000000
	orr r1, r2, r2
	str r1, [r3, #0x0]
	str r0, [r3, #0x4]
_020E9454:
	ldmia r3, {r0-r1}
	orr r0, r0, #0x0
	orr r1, r1, #0x80000
	stmia r3, {r0-r1}
	add sp, sp, #0xfc
	ldmia sp!, {r4-r11,pc}
_020E946C:
	add r3, sp, #0xd6
	mov r5, r4
	mov r2, #0x9
_020E9478:
	ldrh r1, [r5, #0x0]
	ldrh r0, [r5, #0x2]
	add r5, r5, #0x4
	subs r2, r2, #0x1
	strh r1, [r3, #0x0]
	strh r0, [r3, #0x2]
	add r3, r3, #0x4
	bne _020E9478
	ldrh r0, [r5, #0x0]
	add r1, sp, #0xdb
	strh r0, [r3, #0x0]
	ldrb r0, [sp, #0xda]
	add r5, r1, r0
	cmp r1, r5
	bhs _020E94C8
_020E94B4:
	ldrb r0, [r1, #0x0]
	sub r0, r0, #0x30
	strb r0, [r1], #0x1
	cmp r1, r5
	blo _020E94B4
_020E94C8:
	ldrb r1, [sp, #0xda]
	ldrsh r2, [sp, #0xd8]
	add r0, sp, #0xb0
	sub r1, r1, #0x1
	add r1, r2, r1
	strh r1, [sp, #0xd8]
	ldr r1, _020E997C ; =UNK_02106F5C
	mov r2, #0x134
	ldrsh r11, [sp, #0xd8]
	bl __str2dec
	add r0, sp, #0xb0
	add r1, sp, #0xd6
	bl __less_dec
	cmp r0, #0x0
	beq _020E9538
	ldrsb r0, [r4, #0x0]
	mov r5, #0x0
	cmp r0, #0x0
	ldreq r4, _020E996C ; =0x3FF00000
	ldr r0, _020E9974 ; =__float_huge
	ldrne r4, _020E9970 ; =0xBFF00000
	ldr r0, [r0, #0x0]
	bl _f2d
	mov r2, r5
	mov r3, r4
	bl copysign
	add sp, sp, #0xfc
	ldmia sp!, {r4-r11,pc}
_020E9538:
	add r1, sp, #0xdb
	ldrb r0, [r1, #0x0]
	add r8, r1, #0x1
	bl _dfltu
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	cmp r8, r5
	bhs _020E9610
_020E9558:
	sub r0, r5, r8
	mov r1, r0, lsr #0x1f
	rsb r0, r1, r0, lsl #0x1d
	adds r7, r1, r0, ror #0x1d
	moveq r7, #0x8
	mov r6, #0x0
	mov r2, #0x0
	cmp r7, #0x0
	ble _020E9594
	mov r0, #0xa
_020E9580:
	ldrb r1, [r8], #0x1
	add r2, r2, #0x1
	cmp r2, r7
	mla r6, r0, r6, r1
	blt _020E9580
_020E9594:
	ldr r0, _020E9980 ; =UNK_02106E48
	ldr r1, [sp, #0xc]
	add r3, r0, r7, lsl #0x3
	ldr r2, [r3, #-0x8]
	ldr r0, [sp, #0x8]
	ldr r3, [r3, #-0x4]
	bl _dmul
	mov r4, r0
	mov r9, r1
	mov r0, r6
	bl _dfltu
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r9
	bl _dadd
	cmp r6, #0x0
	mov r6, r0
	mov r10, r1
	beq _020E95FC
	mov r0, r4
	mov r1, r9
	mov r2, r6
	mov r3, r10
	bl _deq
	beq _020E9610
_020E95FC:
	str r6, [sp, #0x8]
	str r10, [sp, #0xc]
	cmp r8, r5
	sub r11, r11, r7
	blo _020E9558
_020E9610:
	cmp r11, #0x0
	bge _020E9654
	rsb r0, r11, #0x0
	bl _dflt
	mov r3, r1
	mov r2, r0
	ldr r1, _020E9984 ; =0x40140000
	mov r0, #0x0
	bl pow
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	bl _ddiv
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	b _020E968C
_020E9654:
	mov r0, r11
	bl _dflt
	mov r3, r1
	mov r2, r0
	ldr r1, _020E9984 ; =0x40140000
	mov r0, #0x0
	bl pow
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	bl _dmul
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
_020E968C:
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	mov r2, r11
	bl ldexp
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	bl __fpclassifyf
	cmp r0, #0x2
	bne _020E96C0
	ldr r0, _020E9988 ; =0x7FEFFFFF
	mvn r1, #0x0
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
_020E96C0:
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0xc]
	add r0, sp, #0x8a
	add r4, sp, #0x0
	mov r5, #0x0
	bl __num2dec_internal
	add r0, sp, #0x8a
	add r1, sp, #0xd6
	bl __equals_dec
	cmp r0, #0x0
	bne _020E9934
	add r0, sp, #0x8a
	add r1, sp, #0xd6
	bl __less_dec
	cmp r0, #0x0
	movne r5, #0x1
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	cmp r5, #0x0
	moveq r6, #0x1
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	movne r6, #0x0
_020E971C:
	cmp r6, #0x0
	bne _020E9744
	ldmia r4, {r0-r1}
	adds r0, r0, #0x1
	adc r1, r1, #0x0
	stmia r4, {r0-r1}
	bl __fpclassifyf
	cmp r0, #0x2
	beq _020E9934
	b _020E975C
_020E9744:
	ldr r1, [r4, #0x0]
	ldr r0, [r4, #0x4]
	subs r1, r1, #0x1
	sbc r0, r0, #0x0
	str r1, [r4, #0x0]
	str r0, [r4, #0x4]
_020E975C:
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, sp, #0x64
	bl __num2dec_internal
	cmp r5, #0x0
	beq _020E9788
	add r0, sp, #0x64
	add r1, sp, #0xd6
	bl __less_dec
	cmp r0, #0x0
	beq _020E98AC
_020E9788:
	cmp r5, #0x0
	bne _020E9864
	add r0, sp, #0xd6
	add r1, sp, #0x64
	bl __less_dec
	cmp r0, #0x0
	bne _020E9864
	add r3, sp, #0x8a
	add r5, sp, #0x3e
	mov r2, #0x9
_020E97B0:
	ldrh r1, [r3, #0x0]
	ldrh r0, [r3, #0x2]
	add r3, r3, #0x4
	strh r1, [r5, #0x0]
	strh r0, [r5, #0x2]
	add r5, r5, #0x4
	subs r2, r2, #0x1
	bne _020E97B0
	ldrh r0, [r3, #0x0]
	add r3, sp, #0x64
	add r4, sp, #0x8a
	strh r0, [r5, #0x0]
	mov r2, #0x9
_020E97E4:
	ldrh r1, [r3, #0x0]
	ldrh r0, [r3, #0x2]
	add r3, r3, #0x4
	strh r1, [r4, #0x0]
	strh r0, [r4, #0x2]
	add r4, r4, #0x4
	subs r2, r2, #0x1
	bne _020E97E4
	ldrh r0, [r3, #0x0]
	add r3, sp, #0x3e
	add r5, sp, #0x64
	strh r0, [r4, #0x0]
	mov r2, #0x9
_020E9818:
	ldrh r1, [r3, #0x0]
	ldrh r0, [r3, #0x2]
	add r3, r3, #0x4
	strh r1, [r5, #0x0]
	strh r0, [r5, #0x2]
	add r5, r5, #0x4
	subs r2, r2, #0x1
	bne _020E9818
	ldrh r4, [r3, #0x0]
	ldr r3, [sp, #0x8]
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0xc]
	ldr r0, [sp, #0x4]
	strh r4, [r5, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	str r3, [sp, #0x0]
	str r2, [sp, #0x4]
	b _020E98AC
_020E9864:
	add r7, sp, #0x64
	add r3, sp, #0x8a
	mov r2, #0x9
_020E9870:
	ldrh r1, [r7, #0x0]
	ldrh r0, [r7, #0x2]
	add r7, r7, #0x4
	strh r1, [r3, #0x0]
	strh r0, [r3, #0x2]
	add r3, r3, #0x4
	subs r2, r2, #0x1
	bne _020E9870
	ldrh r2, [r7, #0x0]
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	strh r2, [r3, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	b _020E971C
_020E98AC:
	add r0, sp, #0x3e
	add r1, sp, #0xd6
	add r2, sp, #0x8a
	bl __minus_dec
	add r0, sp, #0x18
	add r1, sp, #0x64
	add r2, sp, #0xd6
	bl __minus_dec
	add r0, sp, #0x3e
	add r1, sp, #0x18
	bl __equals_dec
	cmp r0, #0x0
	beq _020E9910
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	and r1, r1, #0x1
	and r0, r0, #0x0
	cmp r0, #0x0
	cmpeq r1, #0x0
	beq _020E9934
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	b _020E9934
_020E9910:
	add r0, sp, #0x3e
	add r1, sp, #0x18
	bl __less_dec
	cmp r0, #0x0
	bne _020E9934
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
_020E9934:
	ldrsb r0, [sp, #0xd6]
	cmp r0, #0x0
	beq _020E995C
	mov r0, #0x0
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	mov r1, r0
	bl _dsub
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
_020E995C:
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	add sp, sp, #0xfc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020E996C: .word 0x3FF00000
_020E9970: .word 0xBFF00000
_020E9974: .word __float_huge
_020E9978: .word 0x7FF00000
_020E997C: .word UNK_02106F5C
_020E9980: .word UNK_02106E48
_020E9984: .word 0x40140000
_020E9988: .word 0x7FEFFFFF
	arm_func_end __dec2num

	.section .exception,8

	.global UNK_020EC740
UNK_020EC740: ; 0x020EC740
	.byte 0x00, 0xFF, 0x05, 0x20
	.balign 8

	exception __rounddec, 65, 0x00200300
	exception __ull2dec, 205, 0x0050FF00
	exception __timesdec, 389, 0x00D0FF00
	exception __str2dec, 157, 0x00100000
	exception __two_exp, 901, 0x00B00300
	exception __num2dec_internal, 385, 0x00E01F00
	exception __num2dec_internal2, 169, 0x00200300
	exception __dec2num, 1572, UNK_020EC740
