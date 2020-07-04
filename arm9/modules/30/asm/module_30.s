	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD30_02254840
MOD30_02254840: ; 0x02254840
	ldr r3, _02254848 ; =Poketch_InitApp
	ldr r0, _0225484C ; =MOD30_02254854
	ldr r1, _02254850 ; =MOD30_0225496C
	bx r3
	.align 2, 0
_02254848: .word Poketch_InitApp
_0225484C: .word MOD30_02254854
_02254850: .word MOD30_0225496C
	thumb_func_end MOD30_02254840

	thumb_func_start MOD30_02254854
MOD30_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x20
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD30_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD30_02254930
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA44
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
_02254898: .word MOD30_02254930
	thumb_func_end MOD30_02254854

	thumb_func_start MOD30_0225489C
MOD30_0225489C: ; 0x0225489C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #1
	add r1, r5, #0
	add r7, r2, #0
	add r4, r3, #0
	str r0, [r5, #0xc]
	add r0, r4, #0
	add r1, #8
	mov r2, #4
	bl FUN_02089418
	cmp r0, #0
	bne _022548BE
	mov r0, #0
	str r0, [r5, #8]
_022548BE:
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0x10
	add r1, #8
	add r2, r7, #0
	str r4, [r5, #4]
	bl MOD30_02254A90
	cmp r0, #0
	beq _022548F6
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	mov r0, #8
	str r0, [sp]
	ldr r0, _022548FC ; =0x02254DA0
	ldr r2, _02254900 ; =MOD30_02254904
	mov r1, #1
	add r3, r5, #0
	bl MOD20_02254130
	str r0, [r5, #0x18]
	mov r0, #0
	str r0, [r5, #0x1c]
	str r6, [r5, #0x14]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_022548F6:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_022548FC: .word 0x02254DA0
_02254900: .word MOD30_02254904
	thumb_func_end MOD30_0225489C

	thumb_func_start MOD30_02254904
MOD30_02254904: ; 0x02254904
	cmp r0, #0
	bne _0225490A
	str r1, [r3, #0x1c]
_0225490A:
	bx lr
	thumb_func_end MOD30_02254904

	thumb_func_start MOD30_0225490C
MOD30_0225490C: ; 0x0225490C
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #8
	mov r2, #4
	bl FUN_020893F0
	ldr r0, [r4, #0x18]
	bl MOD20_02254198
	ldr r0, [r4, #0x10]
	bl MOD30_02254ACC
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD30_0225490C

	thumb_func_start MOD30_02254930
MOD30_02254930: ; 0x02254930
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhs _02254966
	ldr r0, [r4, #0x14]
	ldr r1, [r4, #0x18]
	bl MOD20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02254968 ; =0x02254DA4
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254966
	add r0, r4, #0
	bl MOD30_0225490C
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x14]
	bl MOD20_022529A0
_02254966:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254968: .word 0x02254DA4
	thumb_func_end MOD30_02254930

	thumb_func_start MOD30_0225496C
MOD30_0225496C: ; 0x0225496C
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD30_0225496C

	thumb_func_start MOD30_02254974
MOD30_02254974: ; 0x02254974
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _0225497C
	b _0225497E
_0225497C:
	mov r1, #2
_0225497E:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD30_02254974

	thumb_func_start MOD30_02254988
MOD30_02254988: ; 0x02254988
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254998
	cmp r0, #1
	beq _022549A8
	b _022549C2
_02254998:
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl MOD30_02254BC8
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549C2
_022549A8:
	ldr r0, [r4, #0x10]
	mov r1, #0
	bl MOD30_02254BEC
	cmp r0, #0
	beq _022549C2
	ldr r0, [r4, #0x14]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD30_02254974
_022549C2:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD30_02254988

	thumb_func_start MOD30_022549C8
MOD30_022549C8: ; 0x022549C8
	push {r4, lr}
	add r4, r0, #0
	ldrb r2, [r4, #2]
	add r1, r4, #0
	add r1, #8
	cmp r2, #0
	beq _022549E0
	mov r1, #2
	bl MOD30_02254974
	mov r0, #0
	pop {r4, pc}
_022549E0:
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549EC
	cmp r0, #1
	beq _02254A0A
	b _02254A52
_022549EC:
	ldr r0, [r4, #0x1c]
	cmp r0, #1
	bne _02254A52
	mov r0, #0
	str r0, [r1, #4]
	ldr r0, [r4, #0x10]
	mov r1, #2
	bl MOD30_02254BC8
	mov r0, #0
	str r0, [r4, #0x1c]
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A52
_02254A0A:
	ldr r0, [r4, #0x1c]
	cmp r0, #2
	bne _02254A24
	mov r0, #1
	str r0, [r1, #4]
	ldr r0, [r4, #0x10]
	mov r1, #2
	bl MOD30_02254BC8
	mov r0, #0
	str r0, [r4, #0x1c]
	strb r0, [r4, #1]
	b _02254A52
_02254A24:
	cmp r0, #3
	bne _02254A52
	mov r0, #1
	str r0, [r1, #4]
	ldr r0, [r1]
	add r2, r0, #1
	ldr r0, _02254A58 ; =0x0000270F
	str r2, [r1]
	cmp r2, r0
	bls _02254A3C
	mov r0, #0
	str r0, [r1]
_02254A3C:
	ldr r0, [r4, #0x10]
	mov r1, #2
	bl MOD30_02254BC8
	ldr r0, [r4, #0x10]
	mov r1, #3
	bl MOD30_02254BC8
	mov r0, #0
	str r0, [r4, #0x1c]
	strb r0, [r4, #1]
_02254A52:
	mov r0, #0
	pop {r4, pc}
	nop
_02254A58: .word 0x0000270F
	thumb_func_end MOD30_022549C8

	thumb_func_start MOD30_02254A5C
MOD30_02254A5C: ; 0x02254A5C
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A6C
	cmp r0, #1
	beq _02254A7C
	b _02254A8A
_02254A6C:
	ldr r0, [r4, #0x10]
	mov r1, #1
	bl MOD30_02254BC8
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A8A
_02254A7C:
	ldr r0, [r4, #0x10]
	bl MOD30_02254BF8
	cmp r0, #0
	beq _02254A8A
	mov r0, #1
	pop {r4, pc}
_02254A8A:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD30_02254A5C

	thumb_func_start MOD30_02254A90
MOD30_02254A90: ; 0x02254A90
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r5, r1, #0
	mov r0, #8
	mov r1, #0x60
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254AC6
	add r0, #8
	mov r1, #4
	bl MOD20_022536F4
	str r5, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x20]
	add r0, r4, #0
	add r1, r5, #0
	bl MOD30_02254AE0
	str r4, [r6]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254AC6:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD30_02254A90

	thumb_func_start MOD30_02254ACC
MOD30_02254ACC: ; 0x02254ACC
	push {r4, lr}
	add r4, r0, #0
	beq _02254ADC
	bl MOD30_02254B94
	add r0, r4, #0
	bl FreeToHeap
_02254ADC:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD30_02254ACC

	thumb_func_start MOD30_02254AE0
MOD30_02254AE0: ; 0x02254AE0
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	add r7, r0, #0
	str r1, [sp, #0xc]
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #2
	bl FUN_02006A34
	mov r0, #0
	str r0, [sp]
	mov r2, #1
	mov r3, #0xa
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x2f
	lsl r3, r3, #8
	bl FUN_02006A34
	mov r0, #8
	str r0, [sp]
	add r0, r7, #0
	add r0, #0x38
	mov r1, #0xc
	mov r2, #0x2d
	mov r3, #0x2e
	bl MOD20_02253FBC
	mov r0, #8
	str r0, [sp]
	add r0, r7, #0
	add r0, #0x4c
	mov r1, #0xc
	mov r2, #3
	mov r3, #4
	bl MOD20_02253FBC
	add r2, r7, #0
	ldr r0, [r7, #0x20]
	ldr r1, _02254B8C ; =0x02254DB0
	add r2, #0x38
	bl MOD20_02253E74
	mov r1, #0x50
	str r0, [r7, #0x24]
	bl MOD20_02253FA4
	add r0, r7, #0
	mov r5, #0x16
	str r0, [sp, #0x10]
	add r0, #0x4c
	mov r6, #0
	add r4, r7, #0
	lsl r5, r5, #0xe
	str r0, [sp, #0x10]
_02254B5C:
	ldr r0, [r7, #0x20]
	ldr r1, _02254B90 ; =0x02254DC0
	ldr r2, [sp, #0x10]
	bl MOD20_02253E74
	mov r2, #1
	add r1, r5, #0
	lsl r2, r2, #0x12
	str r0, [r4, #0x28]
	bl MOD20_02253F64
	mov r0, #1
	lsl r0, r0, #0x10
	add r6, r6, #1
	add r4, r4, #4
	add r5, r5, r0
	cmp r6, #4
	blt _02254B5C
	ldr r1, [sp, #0xc]
	add r0, r7, #0
	bl MOD30_02254D28
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02254B8C: .word 0x02254DB0
_02254B90: .word 0x02254DC0
	thumb_func_end MOD30_02254AE0

	thumb_func_start MOD30_02254B94
MOD30_02254B94: ; 0x02254B94
	push {r4, r5, r6, lr}
	add r6, r0, #0
	ldr r0, [r6, #0x20]
	ldr r1, [r6, #0x24]
	bl MOD20_02253F14
	mov r4, #0
	add r5, r6, #0
_02254BA4:
	ldr r0, [r6, #0x20]
	ldr r1, [r5, #0x28]
	bl MOD20_02253F14
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #4
	blt _02254BA4
	add r0, r6, #0
	add r0, #0x38
	bl MOD20_02254014
	add r6, #0x4c
	add r0, r6, #0
	bl MOD20_02254014
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD30_02254B94

	thumb_func_start MOD30_02254BC8
MOD30_02254BC8: ; 0x02254BC8
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254BE8 ; =0x02254DEC
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254BE8: .word 0x02254DEC
	thumb_func_end MOD30_02254BC8

	thumb_func_start MOD30_02254BEC
MOD30_02254BEC: ; 0x02254BEC
	ldr r3, _02254BF4 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254BF4: .word MOD20_02253794
	thumb_func_end MOD30_02254BEC

	thumb_func_start MOD30_02254BF8
MOD30_02254BF8: ; 0x02254BF8
	ldr r3, _02254C00 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254C00: .word MOD20_022537B8
	thumb_func_end MOD30_02254BF8

	thumb_func_start MOD30_02254C04
MOD30_02254C04: ; 0x02254C04
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD30_02254C04

	thumb_func_start MOD30_02254C18
MOD30_02254C18: ; 0x02254C18
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254C9C ; =0x02254DD0
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x2c
	mov r3, #6
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x2b
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r1, _02254CA0 ; =0x04001000
	ldr r0, _02254CA4 ; =0xFFFFE0FF
	ldr r3, [r1]
	ldr r2, [r1]
	str r3, [sp, #0x10]
	and r0, r2
	lsl r2, r3, #0x13
	lsr r3, r2, #0x1b
	mov r2, #4
	orr r2, r3
	lsl r2, r2, #8
	orr r0, r2
	str r0, [r1]
	add r0, r4, #0
	bl MOD30_02254C04
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_02254C9C: .word 0x02254DD0
_02254CA0: .word 0x04001000
_02254CA4: .word 0xFFFFE0FF
	thumb_func_end MOD30_02254C18

	thumb_func_start MOD30_02254CA8
MOD30_02254CA8: ; 0x02254CA8
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	bl MOD30_02254C04
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD30_02254CA8

	thumb_func_start MOD30_02254CC4
MOD30_02254CC4: ; 0x02254CC4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	ldr r0, [r4]
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _02254CDE
	cmp r0, #1
	beq _02254CEE
	b _02254CF6
_02254CDE:
	ldr r0, _02254D00 ; =0x00000669
	bl MOD20_02252B28
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl MOD20_02253F28
	b _02254CF6
_02254CEE:
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl MOD20_02253F28
_02254CF6:
	add r0, r5, #0
	bl MOD30_02254C04
	pop {r3, r4, r5, pc}
	nop
_02254D00: .word 0x00000669
	thumb_func_end MOD30_02254CC4

	thumb_func_start MOD30_02254D04
MOD30_02254D04: ; 0x02254D04
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r1, r0, #0
	add r0, r4, #0
	bl MOD30_02254D28
	add r0, r5, #0
	bl MOD30_02254C04
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD30_02254D04

	thumb_func_start MOD30_02254D28
MOD30_02254D28: ; 0x02254D28
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r7, r0, #0
	ldr r0, [r1]
	ldr r5, _02254D8C ; =0x04000280
	str r0, [sp, #4]
	mov r0, #0xfa
	lsl r0, r0, #2
	str r0, [sp]
	mov r0, #0
	str r0, [sp, #8]
	lsr r4, r5, #0xb
	lsr r6, r5, #0xb
_02254D42:
	mov r0, #0
	strh r0, [r5]
	ldr r1, [sp, #4]
	ldr r0, _02254D90 ; =0x04000290
	str r1, [r0]
	ldr r1, [sp]
	str r1, [r0, #8]
	ldr r0, _02254D94 ; =0x04000298
	mov r1, #0
	str r1, [r0, #4]
_02254D56:
	ldrh r0, [r5]
	tst r0, r4
	bne _02254D56
	ldr r1, _02254D98 ; =0x040002A0
	ldr r0, [r7, #0x28]
	ldr r1, [r1]
	bl MOD20_02253F28
_02254D66:
	ldrh r0, [r5]
	tst r0, r6
	bne _02254D66
	ldr r0, _02254D9C ; =0x040002A8
	mov r1, #0xa
	ldr r0, [r0]
	str r0, [sp, #4]
	ldr r0, [sp]
	bl _u32_div_f
	str r0, [sp]
	ldr r0, [sp, #8]
	add r7, r7, #4
	add r0, r0, #1
	str r0, [sp, #8]
	cmp r0, #4
	blt _02254D42
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02254D8C: .word 0x04000280
_02254D90: .word 0x04000290
_02254D94: .word 0x04000298
_02254D98: .word 0x040002A0
_02254D9C: .word 0x040002A8
	thumb_func_end MOD30_02254D28

	.section .rodata
	; 0x02254DA0
	.byte 0x64, 0x9C, 0x52, 0x92, 0x89, 0x49, 0x25, 0x02, 0xC9, 0x49, 0x25, 0x02, 0x5D, 0x4A, 0x25, 0x02
	.byte 0x00, 0x20, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x19, 0x4C, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xA9, 0x4C, 0x25, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xC5, 0x4C, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x05, 0x4D, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
