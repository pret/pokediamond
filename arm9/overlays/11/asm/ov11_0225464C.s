	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov11_0225464C
ov11_0225464C: ; 0x0225464C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	bne _02254680
	add r0, r1, #0
	bl ov11_0222FF74
	mov r1, #0x22
	lsl r1, r1, #4
	tst r0, r1
	bne _02254680
	mov r1, #0xb4
	add r0, r1, #0
	add r0, #0xe8
	strh r1, [r4, r0]
	ldr r0, _02254684 ; =ov11_022546B4
	ldr r2, _02254688 ; =0x000003F2
	add r1, r4, #0
	bl SysTask_CreateOnMainQueue
	mov r1, #0x66
	lsl r1, r1, #2
	str r0, [r4, r1]
_02254680:
	pop {r4, pc}
	nop
_02254684: .word ov11_022546B4
_02254688: .word 0x000003F2

	thumb_func_start ov11_0225468C
ov11_0225468C: ; 0x0225468C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0x66
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	cmp r0, #0
	beq _022546B2
	bl sub_0200CAB4
	mov r0, #0x66
	mov r2, #0
	lsl r0, r0, #2
	str r2, [r4, r0]
	add r0, r0, #4
	strh r2, [r4, r0]
	ldr r0, [r4, #0x20]
	mov r1, #4
	bl sub_02007558
_022546B2:
	pop {r4, pc}

	thumb_func_start ov11_022546B4
ov11_022546B4: ; 0x022546B4
	push {r3, r4, r5, lr}
	add r4, r1, #0
	mov r1, #0x67
	lsl r1, r1, #2
	ldrh r0, [r4, r1]
	add r0, #0x14
	strh r0, [r4, r1]
	add r0, r1, #0
	ldrh r2, [r4, r1]
	sub r0, #0x34
	cmp r2, r0
	blo _022546D4
	add r0, r1, #0
	sub r0, #0x34
	sub r0, r2, r0
	strh r0, [r4, r1]
_022546D4:
	mov r0, #0x67
	lsl r0, r0, #2
	ldrh r0, [r4, r0]
	bl Sin
	mov r2, #6
	asr r1, r0, #0x1f
	lsl r2, r2, #0xa
	mov r3, #0
	bl _ll_mul
	add r2, r1, #0
	mov r1, #4
	add r5, r0, #0
	ldr r0, [r4, #0x20]
	mov r4, #0
	lsl r3, r1, #9
	add r3, r5, r3
	adc r2, r4
	lsl r2, r2, #0x14
	lsr r3, r3, #0xc
	orr r3, r2
	asr r2, r3, #0xb
	lsr r2, r2, #0x14
	add r2, r3, r2
	asr r2, r2, #0xc
	bl sub_02007558
	pop {r3, r4, r5, pc}
	.align 2, 0
