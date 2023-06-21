	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021E779C
ov05_021E779C: ; 0x021E779C
	push {r4, lr}
	mov r2, #0
	mov r1, #0x14
	add r3, r2, #0
	add r4, r0, #0
	bl ov05_021E4BE8
	str r4, [r0, #0x10]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021E77B0
ov05_021E77B0: ; 0x021E77B0
	push {r4, lr}
	add r4, r0, #0
	bl ov05_021E78B4
	add r0, r4, #0
	bl ov05_021E4C00
	pop {r4, pc}

	thumb_func_start ov05_021E77C0
ov05_021E77C0: ; 0x021E77C0
	ldr r1, [r0]
	add r1, r1, #1
	str r1, [r0]
	bx lr

	thumb_func_start ov05_021E77C8
ov05_021E77C8: ; 0x021E77C8
	push {r3, lr}
	ldr r1, [r0]
	sub r1, r1, #1
	str r1, [r0]
	bpl _021E77D6
	bl GF_AssertFail
_021E77D6:
	pop {r3, pc}

	thumb_func_start ov05_021E77D8
ov05_021E77D8: ; 0x021E77D8
	ldr r1, [r0, #4]
	add r1, r1, #1
	str r1, [r0, #4]
	bx lr

	thumb_func_start ov05_021E77E0
ov05_021E77E0: ; 0x021E77E0
	push {r3, lr}
	ldr r1, [r0, #4]
	sub r1, r1, #1
	str r1, [r0, #4]
	bpl _021E77EE
	bl GF_AssertFail
_021E77EE:
	pop {r3, pc}

	thumb_func_start ov05_021E77F0
ov05_021E77F0: ; 0x021E77F0
	push {r3, lr}
	cmp r1, #0
	bne _021E77FC
	bl ov05_021E77C0
	pop {r3, pc}
_021E77FC:
	bl ov05_021E77D8
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021E7804
ov05_021E7804: ; 0x021E7804
	push {r3, lr}
	cmp r1, #0
	bne _021E7810
	bl ov05_021E77C8
	pop {r3, pc}
_021E7810:
	bl ov05_021E77E0
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021E7818
ov05_021E7818: ; 0x021E7818
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #0
	bne _021E785C
	mov r1, #1
	str r1, [r4, #8]
	ldr r0, [r4, #0x10]
	mov r2, #0x55
	bl ov05_021E5078
	ldr r0, [r4, #0x10]
	mov r1, #1
	mov r2, #0x75
	bl ov05_021E50AC
	mov r1, #1
	ldr r0, [r4, #0x10]
	mov r2, #4
	add r3, r1, #0
	bl ov05_021E50D4
	mov r1, #1
	str r1, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _021E7860 ; =ov05_021F7854
	add r2, r1, #0
	str r0, [sp, #8]
	ldr r0, [r4, #0x10]
	add r3, r1, #0
	bl ov05_021E4EFC
_021E785C:
	add sp, #0xc
	pop {r3, r4, pc}
	.balign 4, 0
_021E7860: .word ov05_021F7854

	thumb_func_start ov05_021E7864
ov05_021E7864: ; 0x021E7864
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #0
	bne _021E78AC
	mov r0, #1
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x10]
	mov r1, #0xa
	mov r2, #0x6c
	bl ov05_021E5078
	ldr r0, [r4, #0x10]
	mov r1, #0xa
	mov r2, #0x75
	bl ov05_021E50AC
	ldr r0, [r4, #0x10]
	mov r1, #0xb
	mov r2, #0xd
	mov r3, #1
	bl ov05_021E50D4
	mov r0, #0xb
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #4]
	ldr r0, _021E78B0 ; =ov05_021F7854
	mov r2, #0xa
	str r0, [sp, #8]
	ldr r0, [r4, #0x10]
	mov r1, #0xc
	add r3, r2, #0
	bl ov05_021E4EFC
_021E78AC:
	add sp, #0xc
	pop {r3, r4, pc}
	.balign 4, 0
_021E78B0: .word ov05_021F7854

	thumb_func_start ov05_021E78B4
ov05_021E78B4: ; 0x021E78B4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #8]
	cmp r0, #1
	bne _021E78E2
	mov r0, #0
	str r0, [r4, #8]
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl ov05_021E50A0
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl ov05_021E50C8
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl ov05_021E5114
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl ov05_021E506C
_021E78E2:
	pop {r4, pc}

	thumb_func_start ov05_021E78E4
ov05_021E78E4: ; 0x021E78E4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0xc]
	cmp r0, #1
	bne _021E7912
	mov r0, #0
	str r0, [r4, #0xc]
	ldr r0, [r4, #0x10]
	mov r1, #0xa
	bl ov05_021E50A0
	ldr r0, [r4, #0x10]
	mov r1, #0xa
	bl ov05_021E50C8
	ldr r0, [r4, #0x10]
	mov r1, #0xb
	bl ov05_021E5114
	ldr r0, [r4, #0x10]
	mov r1, #0xc
	bl ov05_021E506C
_021E7912:
	pop {r4, pc}

	thumb_func_start ov05_021E7914
ov05_021E7914: ; 0x021E7914
	push {r3, lr}
	ldr r1, [r0]
	cmp r1, #0
	bne _021E7920
	bl ov05_021E7818
_021E7920:
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021E7924
ov05_021E7924: ; 0x021E7924
	push {r3, lr}
	ldr r1, [r0, #4]
	cmp r1, #0
	bne _021E7930
	bl ov05_021E7864
_021E7930:
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021E7934
ov05_021E7934: ; 0x021E7934
	push {r3, lr}
	ldr r1, [r0]
	cmp r1, #0
	bne _021E7940
	bl ov05_021E78B4
_021E7940:
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021E7944
ov05_021E7944: ; 0x021E7944
	push {r3, lr}
	ldr r1, [r0, #4]
	cmp r1, #0
	bne _021E7950
	bl ov05_021E78E4
_021E7950:
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021E7954
ov05_021E7954: ; 0x021E7954
	push {r3, lr}
	cmp r1, #0
	bne _021E7960
	bl ov05_021E7914
	pop {r3, pc}
_021E7960:
	bl ov05_021E7924
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021E7968
ov05_021E7968: ; 0x021E7968
	push {r3, lr}
	cmp r1, #0
	bne _021E7974
	bl ov05_021E7934
	pop {r3, pc}
_021E7974:
	bl ov05_021E7944
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021E797C
ov05_021E797C: ; 0x021E797C
	push {r3, r4, r5, lr}
	sub sp, #8
	ldr r3, _021E7998 ; =ov05_021F7824
	add r4, sp, #0
	ldr r5, [r3]
	ldr r3, [r3, #4]
	str r5, [sp]
	str r3, [sp, #4]
	lsl r1, r1, #2
	ldr r1, [r4, r1]
	bl ov05_021E4EE4
	add sp, #8
	pop {r3, r4, r5, pc}
	.balign 4, 0
_021E7998: .word ov05_021F7824

	thumb_func_start ov05_021E799C
ov05_021E799C: ; 0x021E799C
	push {r3, lr}
	bl sub_02064738
	ldr r0, [r0, #0x14]
	pop {r3, pc}
	.balign 4, 0

	thumb_func_start ov05_021E79A8
ov05_021E79A8: ; 0x021E79A8
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	bl sub_0206475C
	add r2, r4, #0
	add r3, r0, #0
	add r2, #0x30
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	mov r0, #6
	lsl r0, r0, #0xc
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0x30]
	bl ov05_021E7954
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206477C
	ldr r0, [r4, #0x34]
	ldr r1, [r4, #0x30]
	add r2, sp, #0
	bl ov05_021E797C
	str r0, [r4, #0x40]
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0x30]
	bl ov05_021E77F0
	add r0, r5, #0
	bl sub_02064754
	cmp r0, #1
	bne _021E79FC
	ldr r0, _021E7A04 ; =0x000005DD
	bl PlaySE
_021E79FC:
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021E7A04: .word 0x000005DD

	thumb_func_start ov05_021E7A08
ov05_021E7A08: ; 0x021E7A08
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r1, sp, #0
	add r5, r0, #0
	bl sub_0206477C
	ldr r0, [r4]
	cmp r0, #0
	beq _021E7A24
	cmp r0, #1
	beq _021E7A46
	cmp r0, #2
	b _021E7A5E
_021E7A24:
	ldr r1, [r4, #0x1c]
	ldr r0, [r4, #0x28]
	add r0, r1, r0
	str r0, [r4, #0x1c]
	beq _021E7A3A
	mov r0, #2
	ldr r1, [r4, #0x28]
	lsl r0, r0, #0xc
	sub r0, r1, r0
	str r0, [r4, #0x28]
	b _021E7A5E
_021E7A3A:
	mov r0, #0
	str r0, [r4, #0x28]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E7A5E
_021E7A46:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #0x1e
	blt _021E7A5E
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #4]
	mov r0, #1
	str r0, [r4, #0x14]
_021E7A5E:
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	add sp, #0xc
	pop {r4, r5, pc}
	.balign 4, 0

	thumb_func_start ov05_021E7A6C
ov05_021E7A6C: ; 0x021E7A6C
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #0x40]
	bl sub_0201F744
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0x30]
	bl ov05_021E7804
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0x30]
	bl ov05_021E7968
	pop {r4, pc}

	thumb_func_start ov05_021E7A88
ov05_021E7A88: ; 0x021E7A88
	push {r3, r4, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldr r1, [r4, #0x10]
	cmp r1, #1
	beq _021E7ABA
	add r1, sp, #0
	bl sub_0206477C
	ldr r1, [sp]
	ldr r0, [r4, #0x18]
	add r0, r1, r0
	str r0, [sp]
	ldr r1, [sp, #4]
	ldr r0, [r4, #0x1c]
	add r0, r1, r0
	str r0, [sp, #4]
	ldr r1, [sp, #8]
	ldr r0, [r4, #0x20]
	add r0, r1, r0
	str r0, [sp, #8]
	ldr r0, [r4, #0x40]
	add r1, sp, #0
	bl sub_0201F7C8
_021E7ABA:
	add sp, #0xc
	pop {r3, r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021E7AC0
ov05_021E7AC0: ; 0x021E7AC0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x24
	add r5, r0, #0
	add r6, r1, #0
	add r7, r2, #0
	bl ov05_021E4C24
	add r4, r0, #0
	mov r1, #0x16
	str r6, [sp, #0x14]
	str r4, [sp, #0x18]
	bl ov05_021E4C08
	str r0, [sp, #0x1c]
	add r0, r5, #0
	add r1, sp, #8
	str r5, [sp, #0x20]
	bl sub_02058B5C
	add r0, r5, #0
	bl sub_02058744
	add r1, r0, #1
	add r0, sp, #0x14
	str r0, [sp]
	str r1, [sp, #4]
	ldr r1, _021E7B04 ; =ov05_021F7840
	add r0, r4, #0
	add r2, sp, #8
	add r3, r7, #0
	bl ov05_021E4DC4
	add sp, #0x24
	pop {r4, r5, r6, r7, pc}
	.balign 4, 0
_021E7B04: .word ov05_021F7840

	thumb_func_start ov05_021E7B08
ov05_021E7B08: ; 0x021E7B08
	push {r4, r5, lr}
	sub sp, #0xc
	add r4, r1, #0
	add r5, r0, #0
	bl sub_0206475C
	add r2, r4, #0
	add r3, r0, #0
	add r2, #0x30
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldmia r3!, {r0, r1}
	stmia r2!, {r0, r1}
	ldr r0, [r4, #0x3c]
	bl MapObject_GetID
	str r0, [r4, #8]
	ldr r0, [r4, #0x3c]
	bl sub_02058450
	str r0, [r4, #0xc]
	mov r0, #6
	lsl r0, r0, #0xc
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0x30]
	bl ov05_021E7954
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206477C
	ldr r0, [r4, #0x34]
	ldr r1, [r4, #0x30]
	add r2, sp, #0
	bl ov05_021E797C
	str r0, [r4, #0x40]
	ldr r0, [r4, #0x38]
	ldr r1, [r4, #0x30]
	bl ov05_021E77F0
	add r0, r5, #0
	bl sub_02064754
	cmp r0, #1
	bne _021E7B6C
	ldr r0, _021E7B74 ; =0x000005DD
	bl PlaySE
_021E7B6C:
	mov r0, #1
	add sp, #0xc
	pop {r4, r5, pc}
	nop
_021E7B74: .word 0x000005DD

	thumb_func_start ov05_021E7B78
ov05_021E7B78: ; 0x021E7B78
	push {r3, r4, r5, r6, lr}
	sub sp, #0xc
	add r4, r1, #0
	ldr r6, [r4, #0x3c]
	ldr r1, [r4, #8]
	add r5, r0, #0
	ldr r2, [r4, #0xc]
	add r0, r6, #0
	bl sub_020582A8
	cmp r0, #0
	bne _021E7B94
	bl GF_AssertFail
_021E7B94:
	add r0, r6, #0
	add r1, sp, #0
	bl ov05_021F1E64
	mov r0, #2
	ldr r1, [sp, #4]
	lsl r0, r0, #0x10
	add r1, r1, r0
	str r1, [sp, #4]
	ldr r2, [sp, #8]
	lsr r1, r0, #5
	add r1, r2, r1
	str r1, [sp, #8]
	ldr r1, [r4]
	cmp r1, #0
	beq _021E7BBC
	cmp r1, #1
	beq _021E7BDC
	cmp r1, #2
	b _021E7BF4
_021E7BBC:
	ldr r2, [r4, #0x1c]
	ldr r1, [r4, #0x28]
	add r1, r2, r1
	str r1, [r4, #0x1c]
	beq _021E7BD0
	ldr r1, [r4, #0x28]
	lsr r0, r0, #4
	sub r0, r1, r0
	str r0, [r4, #0x28]
	b _021E7BF4
_021E7BD0:
	mov r0, #0
	str r0, [r4, #0x28]
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	b _021E7BF4
_021E7BDC:
	ldr r0, [r4, #4]
	add r0, r0, #1
	str r0, [r4, #4]
	cmp r0, #0x1e
	blt _021E7BF4
	ldr r0, [r4]
	add r0, r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #4]
	mov r0, #1
	str r0, [r4, #0x14]
_021E7BF4:
	add r0, r5, #0
	add r1, sp, #0
	bl sub_0206476C
	add sp, #0xc
	pop {r3, r4, r5, r6, pc}

	.section .rodata

	.global ov05_021F7824
ov05_021F7824: ; 0x021F7824
	.word 0x00000001, 0x0000000C, 0x00000044, ov05_021E79A8
	.word ov05_021E7A6C, ov05_021E7A08, ov05_021E7A88

	.global ov05_021F7840
ov05_021F7840: ; 0x021F7840
	.word 0x00000044, ov05_021E7B08, ov05_021E7A6C, ov05_021E7B78
	.word ov05_021E7A88

	.global ov05_021F7854
ov05_021F7854: ; 0x021F7854
	.word 0x00000000, 0x00000001, 0x00000000, 0x00000000
	.word 0x00000000, 0x00000002
