	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD29_02254840
MOD29_02254840: ; 0x02254840
	ldr r3, _02254848 ; =Poketch_InitApp
	ldr r0, _0225484C ; =MOD29_02254854
	ldr r1, _02254850 ; =MOD29_02254914
	bx r3
	.align 2, 0
_02254848: .word Poketch_InitApp
_0225484C: .word MOD29_02254854
_02254850: .word MOD29_02254914
	thumb_func_end MOD29_02254840

	thumb_func_start MOD29_02254854
MOD29_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x54
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD29_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD29_022548E0
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
_02254898: .word MOD29_022548E0
	thumb_func_end MOD29_02254854

	thumb_func_start MOD29_0225489C
MOD29_0225489C: ; 0x0225489C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r0, #0x48
	add r1, r5, #4
	bl MOD29_02254BC0
	cmp r0, #0
	beq _022548BE
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	str r0, [r5, #0x50]
	str r4, [r5, #0x4c]
	mov r0, #1
	pop {r3, r4, r5, pc}
_022548BE:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD29_0225489C

	thumb_func_start MOD29_022548C4
MOD29_022548C4: ; 0x022548C4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x50]
	cmp r0, #0
	beq _022548D2
	bl FreeToHeap
_022548D2:
	ldr r0, [r4, #0x48]
	bl MOD29_02254C84
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD29_022548C4

	thumb_func_start MOD29_022548E0
MOD29_022548E0: ; 0x022548E0
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #3
	bhs _0225490C
	lsl r2, r1, #2
	ldr r1, _02254910 ; =MOD29_0225509C
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _0225490C
	add r0, r4, #0
	bl MOD29_022548C4
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x4c]
	bl MOD20_022529A0
_0225490C:
	pop {r3, r4, r5, pc}
	nop
_02254910: .word MOD29_0225509C
	thumb_func_end MOD29_022548E0

	thumb_func_start MOD29_02254914
MOD29_02254914: ; 0x02254914
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD29_02254914

	thumb_func_start MOD29_0225491C
MOD29_0225491C: ; 0x0225491C
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254924
	b _02254926
_02254924:
	mov r1, #2
_02254926:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD29_0225491C

	thumb_func_start MOD29_02254930
MOD29_02254930: ; 0x02254930
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254940
	cmp r0, #1
	beq _02254950
	b _0225496A
_02254940:
	ldr r0, [r4, #0x48]
	mov r1, #0
	bl MOD29_02254CC0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _0225496A
_02254950:
	ldr r0, [r4, #0x48]
	mov r1, #0
	bl MOD29_02254CE4
	cmp r0, #0
	beq _0225496A
	ldr r0, [r4, #0x4c]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD29_0225491C
_0225496A:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD29_02254930

	thumb_func_start MOD29_02254970
MOD29_02254970: ; 0x02254970
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _02254990
	ldr r0, [r4, #0x48]
	bl MOD29_0225508C
	add r0, r4, #0
	mov r1, #2
	bl MOD29_0225491C
	add sp, #8
	mov r0, #0
	pop {r4, pc}
_02254990:
	ldrb r1, [r4, #1]
	cmp r1, #3
	bhi _02254A5A
	add r1, r1, r1
	add r1, pc
	ldrh r1, [r1, #6]
	lsl r1, r1, #0x10
	asr r1, r1, #0x10
	add pc, r1
_022549A2: ; jump table
	.short _022549AA - _022549A2 - 2 ; case 0
	.short _022549D4 - _022549A2 - 2 ; case 1
	.short _02254A2A - _022549A2 - 2 ; case 2
	.short _02254A3C - _022549A2 - 2 ; case 3
_022549AA:
	add r1, sp, #4
	add r2, sp, #0
	bl MOD29_02254A64
	cmp r0, #0
	beq _02254A5A
	ldr r1, [sp, #4]
	ldr r2, [sp]
	add r0, r4, #0
	bl MOD29_02254AA8
	ldr r0, _02254A60 ; =0x00000668
	bl MOD20_02252B28
	ldr r0, [r4, #0x48]
	mov r1, #2
	bl MOD29_02254CC0
	mov r0, #1
	strb r0, [r4, #1]
	b _02254A5A
_022549D4:
	ldr r0, [r4, #0x48]
	mov r1, #2
	bl MOD29_02254CE4
	cmp r0, #0
	beq _022549E6
	mov r0, #0
	strb r0, [r4, #1]
	b _02254A5A
_022549E6:
	ldr r0, [r4, #0x4c]
	bl MOD20_02252C30
	cmp r0, #1
	beq _022549FA
	ldr r0, [r4, #0x4c]
	bl MOD20_02252C08
	cmp r0, #0
	beq _02254A06
_022549FA:
	ldr r0, [r4, #0x48]
	bl MOD29_0225508C
	mov r0, #2
	strb r0, [r4, #1]
	b _02254A5A
_02254A06:
	add r0, r4, #0
	add r1, sp, #4
	add r2, sp, #0
	bl MOD29_02254A64
	cmp r0, #0
	beq _02254A5A
	ldr r1, [sp, #4]
	ldr r2, [sp]
	add r0, r4, #0
	bl MOD29_02254AA8
	ldr r0, [r4, #0x48]
	bl MOD29_0225508C
	mov r0, #3
	strb r0, [r4, #1]
	b _02254A5A
_02254A2A:
	ldr r0, [r4, #0x48]
	mov r1, #2
	bl MOD29_02254CE4
	cmp r0, #0
	beq _02254A5A
	mov r0, #0
	strb r0, [r4, #1]
	b _02254A5A
_02254A3C:
	ldr r0, [r4, #0x48]
	mov r1, #2
	bl MOD29_02254CE4
	cmp r0, #0
	beq _02254A5A
	ldr r0, _02254A60 ; =0x00000668
	bl MOD20_02252B28
	ldr r0, [r4, #0x48]
	mov r1, #2
	bl MOD29_02254CC0
	mov r0, #1
	strb r0, [r4, #1]
_02254A5A:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	.align 2, 0
_02254A60: .word 0x00000668
	thumb_func_end MOD29_02254970

	thumb_func_start MOD29_02254A64
MOD29_02254A64: ; 0x02254A64
	push {r3, r4, r5, lr}
	ldr r0, [r0, #0x4c]
	add r5, r1, #0
	add r4, r2, #0
	bl MOD20_02252C08
	cmp r0, #0
	bne _02254AA4
	add r0, r5, #0
	add r1, r4, #0
	bl FUN_02020ACC
	cmp r0, #0
	beq _02254AA4
	ldr r0, [r5]
	sub r0, #0x18
	cmp r0, #0xb0
	bhs _02254A8C
	mov r1, #1
	b _02254A8E
_02254A8C:
	mov r1, #0
_02254A8E:
	ldr r0, [r4]
	sub r0, #0x18
	cmp r0, #0x90
	bhs _02254A9A
	mov r0, #1
	b _02254A9C
_02254A9A:
	mov r0, #0
_02254A9C:
	tst r0, r1
	beq _02254AA4
	mov r0, #1
	pop {r3, r4, r5, pc}
_02254AA4:
	mov r0, #0
	pop {r3, r4, r5, pc}
	thumb_func_end MOD29_02254A64

	thumb_func_start MOD29_02254AA8
MOD29_02254AA8: ; 0x02254AA8
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	add r5, r0, #0
	ldr r0, [r5, #0x4c]
	add r7, r1, #0
	str r2, [sp]
	bl MOD20_02252C38
	mov r1, #8
	bl FUN_02039754
	str r0, [sp, #4]
	add r4, r5, #4
	mov r1, #0
	str r1, [r4, #8]
	ldr r0, [sp]
	str r7, [r5, #4]
	str r0, [r4, #4]
	ldr r0, [sp, #4]
	str r1, [r4, #0xc]
	cmp r0, #0
	beq _02254B66
	ldrb r0, [r0, #4]
	cmp r0, #0xff
	beq _02254B60
	add r6, r4, #0
	ldr r5, [sp, #4]
	add r6, #0xc
_02254AE0:
	ldrh r0, [r5]
	ldrh r1, [r5, #2]
	add r2, sp, #0xc
	add r3, sp, #8
	bl MOD29_02254B70
	ldr r1, [sp, #8]
	ldr r0, [sp]
	sub r0, r1, r0
	ldr r1, [sp, #0xc]
	sub r1, r1, r7
	add r2, r1, #0
	mul r2, r1
	add r1, r0, #0
	mul r1, r0
	add r0, r2, r1
	lsl r0, r0, #0xc
	bl FX_Sqrt
	ldrb r1, [r5, #4]
	lsl r2, r1, #2
	ldr r1, _02254B6C ; =MOD29_022550A8
	ldr r1, [r1, r2]
	cmp r0, r1
	bgt _02254B46
	ldr r1, [r4, #0xc]
	cmp r1, #8
	bhs _02254B58
	mov r2, #6
	mul r2, r1
	ldr r0, [sp, #0xc]
	add r1, r4, r2
	strh r0, [r1, #0x10]
	ldr r2, [r4, #0xc]
	mov r1, #6
	mul r1, r2
	ldr r0, [sp, #8]
	add r1, r4, r1
	strh r0, [r1, #0x12]
	ldr r2, [r4, #0xc]
	mov r1, #6
	mul r1, r2
	ldrb r0, [r5, #4]
	add r1, r4, r1
	strh r0, [r1, #0x14]
	ldr r0, [r6]
	add r0, r0, #1
	str r0, [r6]
	mov r0, #2
	str r0, [r4, #8]
	b _02254B58
_02254B46:
	mov r1, #3
	lsl r1, r1, #0x10
	cmp r0, r1
	bgt _02254B58
	ldr r0, [r4, #8]
	cmp r0, #0
	bne _02254B58
	mov r0, #1
	str r0, [r4, #8]
_02254B58:
	add r5, r5, #6
	ldrb r0, [r5, #4]
	cmp r0, #0xff
	bne _02254AE0
_02254B60:
	ldr r0, [sp, #4]
	bl FreeToHeap
_02254B66:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254B6C: .word MOD29_022550A8
	thumb_func_end MOD29_02254AA8

	thumb_func_start MOD29_02254B70
MOD29_02254B70: ; 0x02254B70
	push {r4, r5}
	sub r4, r0, #7
	mov r0, #0xb
	add r5, r4, #0
	mul r5, r0
	sub r1, r1, #7
	add r5, #0x70
	mul r0, r1
	str r5, [r2]
	add r0, #0x65
	str r0, [r3]
	pop {r4, r5}
	bx lr
	.align 2, 0
	thumb_func_end MOD29_02254B70

	thumb_func_start MOD29_02254B8C
MOD29_02254B8C: ; 0x02254B8C
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254B9C
	cmp r0, #1
	beq _02254BAC
	b _02254BBA
_02254B9C:
	ldr r0, [r4, #0x48]
	mov r1, #1
	bl MOD29_02254CC0
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254BBA
_02254BAC:
	ldr r0, [r4, #0x48]
	bl MOD29_02254CF0
	cmp r0, #0
	beq _02254BBA
	mov r0, #1
	pop {r4, pc}
_02254BBA:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD29_02254B8C

	thumb_func_start MOD29_02254BC0
MOD29_02254BC0: ; 0x02254BC0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x90
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254C04
	add r0, #8
	mov r1, #8
	bl MOD20_022536F4
	str r6, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	mov r0, #0
	str r0, [r4, #0x6c]
	bl MOD20_02252D24
	str r0, [r4, #0x30]
	mov r1, #0
	str r1, [r4, #0x34]
	add r2, r4, #0
	add r0, r1, #0
_02254BF4:
	add r1, r1, #1
	str r0, [r2, #0x38]
	add r2, r2, #4
	cmp r1, #8
	blt _02254BF4
	str r4, [r5]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254C04:
	mov r0, #0
	pop {r4, r5, r6, pc}
	thumb_func_end MOD29_02254BC0

	thumb_func_start MOD29_02254C08
MOD29_02254C08: ; 0x02254C08
	push {r4, r5, r6, r7, lr}
	sub sp, #0xc
	add r6, r0, #0
	mov r0, #8
	str r0, [sp]
	add r0, r6, #0
	add r0, #0x58
	mov r1, #0xc
	mov r2, #0x28
	mov r3, #0x29
	bl MOD20_02253FBC
	cmp r0, #0
	beq _02254C74
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x2a
	bl FUN_02006A34
	add r2, r6, #0
	ldr r0, [r6, #0x30]
	ldr r1, _02254C7C ; =MOD29_022550C0
	add r2, #0x58
	bl MOD20_02253E74
	mov r1, #1
	str r0, [r6, #0x34]
	bl MOD20_02253F78
	add r7, r6, #0
	mov r4, #0
	add r5, r6, #0
	add r7, #0x58
_02254C54:
	ldr r0, [r6, #0x30]
	ldr r1, _02254C80 ; =MOD29_022550D0
	add r2, r7, #0
	bl MOD20_02253E74
	mov r1, #1
	str r0, [r5, #0x38]
	bl MOD20_02253F78
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #8
	blt _02254C54
	add sp, #0xc
	mov r0, #1
	pop {r4, r5, r6, r7, pc}
_02254C74:
	mov r0, #0
	add sp, #0xc
	pop {r4, r5, r6, r7, pc}
	nop
_02254C7C: .word MOD29_022550C0
_02254C80: .word MOD29_022550D0
	thumb_func_end MOD29_02254C08

	thumb_func_start MOD29_02254C84
MOD29_02254C84: ; 0x02254C84
	push {r4, r5, r6, lr}
	add r6, r0, #0
	beq _02254CBC
	mov r4, #0
	add r5, r6, #0
_02254C8E:
	ldr r1, [r5, #0x38]
	cmp r1, #0
	beq _02254C9A
	ldr r0, [r6, #0x30]
	bl MOD20_02253F14
_02254C9A:
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #8
	blt _02254C8E
	ldr r1, [r6, #0x34]
	cmp r1, #0
	beq _02254CAE
	ldr r0, [r6, #0x30]
	bl MOD20_02253F14
_02254CAE:
	add r0, r6, #0
	add r0, #0x58
	bl MOD20_02254014
	add r0, r6, #0
	bl FreeToHeap
_02254CBC:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD29_02254C84

	thumb_func_start MOD29_02254CC0
MOD29_02254CC0: ; 0x02254CC0
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254CE0 ; =MOD29_022550FC
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254CE0: .word MOD29_022550FC
	thumb_func_end MOD29_02254CC0

	thumb_func_start MOD29_02254CE4
MOD29_02254CE4: ; 0x02254CE4
	ldr r3, _02254CEC ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254CEC: .word MOD20_02253794
	thumb_func_end MOD29_02254CE4

	thumb_func_start MOD29_02254CF0
MOD29_02254CF0: ; 0x02254CF0
	ldr r3, _02254CF8 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254CF8: .word MOD20_022537B8
	thumb_func_end MOD29_02254CF0

	thumb_func_start MOD29_02254CFC
MOD29_02254CFC: ; 0x02254CFC
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD29_02254CFC

	thumb_func_start MOD29_02254D10
MOD29_02254D10: ; 0x02254D10
	push {r4, r5, lr}
	sub sp, #0x14
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	ldr r0, [r4, #4]
	ldr r2, _02254DE8 ; =MOD29_022550E0
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
	ldr r2, [r4, #4]
	mov r0, #0xc
	mov r1, #0x27
	mov r3, #6
	bl FUN_0200687C
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r4, #4]
	mov r0, #0xc
	mov r1, #0x26
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	add r0, r4, #0
	add r0, #0x70
	bl MOD20_02252DEC
	add r0, r4, #0
	add r0, #0x80
	ldrh r1, [r0]
	add r0, r4, #0
	add r0, #0x72
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0x70
	mov r1, #0x20
	bl DC_FlushRange
	add r0, r4, #0
	mov r1, #0x1a
	add r0, #0x70
	lsl r1, r1, #4
	mov r2, #0x20
	bl GXS_LoadOBJPltt
	add r0, r4, #0
	add r0, #0x8e
	ldrh r1, [r0]
	add r0, r4, #0
	add r0, #0x72
	strh r1, [r0]
	add r0, r4, #0
	add r0, #0x70
	mov r1, #0x20
	bl DC_FlushRange
	add r0, r4, #0
	mov r1, #7
	add r0, #0x70
	lsl r1, r1, #6
	mov r2, #0x20
	bl GXS_LoadOBJPltt
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r1, _02254DEC ; =0x04001000
	ldr r0, _02254DF0 ; =0xFFFFE0FF
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
	bl MOD29_02254C08
	add r0, r5, #0
	bl MOD29_02254CFC
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_02254DE8: .word MOD29_022550E0
_02254DEC: .word 0x04001000
_02254DF0: .word 0xFFFFE0FF
	thumb_func_end MOD29_02254D10

	thumb_func_start MOD29_02254DF4
MOD29_02254DF4: ; 0x02254DF4
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	bl MOD29_02254CFC
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD29_02254DF4

	thumb_func_start MOD29_02254E10
MOD29_02254E10: ; 0x02254E10
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	str r0, [sp]
	add r0, r5, #0
	bl MOD20_022538A0
	add r6, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r7, r0, #0
	add r0, r5, #0
	bl MOD20_022538A8
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538AC
	cmp r0, #0
	bne _02254E40
	mov r0, #1
	str r0, [r6, #0x6c]
	ldr r0, [r7, #8]
	str r0, [r4]
_02254E40:
	ldr r2, [r4]
	ldr r0, [sp]
	lsl r3, r2, #2
	ldr r2, _02254E50 ; =MOD29_022550B4
	add r1, r5, #0
	ldr r2, [r2, r3]
	blx r2
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254E50: .word MOD29_022550B4
	thumb_func_end MOD29_02254E10

	thumb_func_start MOD29_02254E54
MOD29_02254E54: ; 0x02254E54
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r6, r0, #0
	add r0, r5, #0
	bl MOD20_022538AC
	cmp r0, #0
	beq _02254E78
	cmp r0, #1
	beq _02254E9E
	pop {r4, r5, r6, pc}
_02254E78:
	ldr r1, [r6]
	ldr r2, [r6, #4]
	ldr r0, [r4, #0x34]
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	bl MOD20_02253F64
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl MOD20_02253F28
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r4, r5, r6, pc}
_02254E9E:
	ldr r0, [r4, #0x6c]
	cmp r0, #0
	bne _02254EB2
	add r0, r4, #0
	bl MOD29_02255068
	add r0, r5, #0
	bl MOD29_02254CFC
	pop {r4, r5, r6, pc}
_02254EB2:
	ldr r0, [r4, #0x34]
	bl MOD20_02253F44
	cmp r0, #0
	beq _02254EC8
	add r0, r4, #0
	bl MOD29_02255068
	add r0, r5, #0
	bl MOD29_02254CFC
_02254EC8:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD29_02254E54

	thumb_func_start MOD29_02254ECC
MOD29_02254ECC: ; 0x02254ECC
	push {r4, r5, r6, lr}
	add r6, r1, #0
	add r0, r6, #0
	bl MOD20_022538A0
	add r5, r0, #0
	add r0, r6, #0
	bl MOD20_022538A4
	add r4, r0, #0
	add r0, r6, #0
	bl MOD20_022538AC
	cmp r0, #0
	beq _02254EF0
	cmp r0, #1
	beq _02254F16
	pop {r4, r5, r6, pc}
_02254EF0:
	ldr r1, [r4]
	ldr r2, [r4, #4]
	ldr r0, [r5, #0x34]
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	bl MOD20_02253F64
	ldr r0, [r5, #0x34]
	mov r1, #0
	bl MOD20_02253F28
	ldr r0, [r5, #0x34]
	mov r1, #0
	bl MOD20_02253F78
	add r0, r6, #0
	bl MOD20_022538B0
	pop {r4, r5, r6, pc}
_02254F16:
	ldr r0, [r5, #0x6c]
	cmp r0, #0
	bne _02254F2A
	add r0, r5, #0
	bl MOD29_02255068
	add r0, r6, #0
	bl MOD29_02254CFC
	pop {r4, r5, r6, pc}
_02254F2A:
	ldr r0, [r5, #0x34]
	bl MOD20_02253F44
	cmp r0, #0
	beq _02254F3C
	ldr r0, [r5, #0x34]
	mov r1, #0
	bl MOD20_02253F28
_02254F3C:
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD29_02254ECC

	thumb_func_start MOD29_02254F40
MOD29_02254F40: ; 0x02254F40
	push {r4, r5, r6, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538A4
	add r6, r0, #0
	add r0, r5, #0
	bl MOD20_022538AC
	cmp r0, #0
	beq _02254F68
	cmp r0, #1
	beq _02254F96
	cmp r0, #2
	beq _02254FC4
	pop {r4, r5, r6, pc}
_02254F68:
	add r0, r4, #0
	add r1, r6, #0
	bl MOD29_02254FF4
	ldr r1, [r6]
	ldr r2, [r6, #4]
	ldr r0, [r4, #0x34]
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	bl MOD20_02253F64
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl MOD20_02253F28
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl MOD20_02253F78
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r4, r5, r6, pc}
_02254F96:
	ldr r0, [r4, #0x6c]
	cmp r0, #0
	bne _02254FAA
	add r0, r4, #0
	bl MOD29_02255068
	add r0, r5, #0
	bl MOD29_02254CFC
	pop {r4, r5, r6, pc}
_02254FAA:
	ldr r0, [r4, #0x34]
	bl MOD20_02253F44
	cmp r0, #0
	beq _02254FF2
	add r0, r4, #0
	add r1, r6, #0
	bl MOD29_02255020
	add r0, r5, #0
	bl MOD20_022538B0
	pop {r4, r5, r6, pc}
_02254FC4:
	ldr r0, [r4, #0x6c]
	cmp r0, #0
	bne _02254FD8
	add r0, r4, #0
	bl MOD29_02255068
	add r0, r5, #0
	bl MOD29_02254CFC
	pop {r4, r5, r6, pc}
_02254FD8:
	add r0, r4, #0
	bl MOD29_0225505C
	cmp r0, #0
	beq _02254FF2
	ldr r0, [r4, #0x34]
	mov r1, #0
	bl MOD20_02253F28
	add r0, r5, #0
	mov r1, #1
	bl MOD20_022538B8
_02254FF2:
	pop {r4, r5, r6, pc}
	thumb_func_end MOD29_02254F40

	thumb_func_start MOD29_02254FF4
MOD29_02254FF4: ; 0x02254FF4
	push {r3, r4, r5, r6, r7, lr}
	add r7, r1, #0
	add r5, r0, #0
	ldr r0, [r7, #0xc]
	mov r6, #0
	cmp r0, #0
	bls _0225501E
	add r4, r7, #0
_02255004:
	ldrh r1, [r4, #0x10]
	ldrh r2, [r4, #0x12]
	ldr r0, [r5, #0x38]
	lsl r1, r1, #0xc
	lsl r2, r2, #0xc
	bl MOD20_02253F64
	ldr r0, [r7, #0xc]
	add r6, r6, #1
	add r4, r4, #6
	add r5, r5, #4
	cmp r6, r0
	blo _02255004
_0225501E:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD29_02254FF4

	thumb_func_start MOD29_02255020
MOD29_02255020: ; 0x02255020
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r0, r1, #0
	ldr r0, [r0, #0xc]
	mov r6, #0
	str r1, [sp]
	cmp r0, #0
	bls _0225505A
	add r4, r1, #0
_02255032:
	ldrh r0, [r4, #0x14]
	add r7, r0, #1
	cmp r7, #3
	blo _0225503C
	mov r7, #3
_0225503C:
	ldr r0, [r5, #0x38]
	mov r1, #0
	bl MOD20_02253F78
	ldr r0, [r5, #0x38]
	add r1, r7, #0
	bl MOD20_02253F28
	ldr r0, [sp]
	add r6, r6, #1
	ldr r0, [r0, #0xc]
	add r4, r4, #6
	add r5, r5, #4
	cmp r6, r0
	blo _02255032
_0225505A:
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD29_02255020

	thumb_func_start MOD29_0225505C
MOD29_0225505C: ; 0x0225505C
	ldr r3, _02255064 ; =MOD20_02253F44
	ldr r0, [r0, #0x38]
	bx r3
	nop
_02255064: .word MOD20_02253F44
	thumb_func_end MOD29_0225505C

	thumb_func_start MOD29_02255068
MOD29_02255068: ; 0x02255068
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #0x34]
	mov r1, #1
	bl MOD20_02253F78
	mov r4, #0
	mov r6, #1
_02255078:
	ldr r0, [r5, #0x38]
	add r1, r6, #0
	bl MOD20_02253F78
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #8
	blt _02255078
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD29_02255068

	thumb_func_start MOD29_0225508C
MOD29_0225508C: ; 0x0225508C
	push {r4, lr}
	add r4, r0, #0
	bl MOD29_02255068
	mov r0, #0
	str r0, [r4, #0x6c]
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD29_0225508C

	.section .rodata

	.global MOD29_0225509C
MOD29_0225509C: ; 0x0225509C
	.word MOD29_02254930, MOD29_02254970, MOD29_02254B8C

	.global MOD29_022550A8
MOD29_022550A8: ; 0x022550A8
	.byte 0x00, 0x80, 0x00, 0x00
	.byte 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00

	.global MOD29_022550B4
MOD29_022550B4: ; 0x022550B4
	.word MOD29_02254E54, MOD29_02254ECC, MOD29_02254F40

	.global MOD29_022550C0
MOD29_022550C0: ; 0x022550C0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02
	.byte 0x00, 0x01, 0x00, 0x00

	.global MOD29_022550D0
MOD29_022550D0: ; 0x022550D0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02
	.byte 0x01, 0x00, 0x00, 0x00

	.global MOD29_022550E0
MOD29_022550E0: ; 0x022550E0
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.global MOD29_022550FC
MOD29_022550FC: ; 0x022550FC
	.word 0x00, MOD29_02254D10, 0x00
	.word 0x01, MOD29_02254DF4, 0x00
	.word 0x02, MOD29_02254E10, 0x04
	.word 0x00, 0x00000000, 0x00
