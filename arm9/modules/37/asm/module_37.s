	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD37_02254840
MOD37_02254840: ; 0x02254840
	ldr r3, _02254848 ; =MOD20_02252978
	ldr r0, _0225484C ; =MOD37_02254854
	ldr r1, _02254850 ; =MOD37_02254934
	bx r3
	.align 2, 0
_02254848: .word MOD20_02252978
_0225484C: .word MOD37_02254854
_02254850: .word MOD37_02254934
	thumb_func_end MOD37_02254840

	thumb_func_start MOD37_02254854
MOD37_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x14
	add r7, r2, #0
	str r3, [sp]
	bl FUN_02016998
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD37_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD37_02254900
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
	bl FUN_02016A18
_02254892:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	nop
_02254898: .word MOD37_02254900
	thumb_func_end MOD37_02254854

	thumb_func_start MOD37_0225489C
MOD37_0225489C: ; 0x0225489C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r1, r5, #0
	add r6, r2, #0
	add r0, r3, #0
	add r1, #8
	mov r2, #4
	str r3, [r5, #4]
	bl FUN_02089418
	cmp r0, #0
	bne _022548BA
	mov r0, #1
	str r0, [r5, #8]
_022548BA:
	add r0, r5, #0
	add r1, r5, #0
	add r0, #0xc
	add r1, #8
	add r2, r6, #0
	bl MOD37_02254A54
	cmp r0, #0
	beq _022548DA
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	str r4, [r5, #0x10]
	mov r0, #1
	pop {r4, r5, r6, pc}
_022548DA:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD37_0225489C

	thumb_func_start MOD37_022548E0
MOD37_022548E0: ; 0x022548E0
	push {r4, lr}
	add r4, r0, #0
	add r1, r4, #0
	ldr r0, [r4, #4]
	add r1, #8
	mov r2, #4
	bl FUN_020893F0
	ldr r0, [r4, #0xc]
	bl MOD37_02254B0C
	add r0, r4, #0
	bl FUN_02016A18
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD37_022548E0

	thumb_func_start MOD37_02254900
MOD37_02254900: ; 0x02254900
	push {r3, r4, r5, lr}
	add r4, r1, #0
	ldrb r1, [r4]
	add r5, r0, #0
	cmp r1, #3
	bhs _0225492C
	lsl r2, r1, #2
	ldr r1, _02254930 ; =0x02254D28
	add r0, r4, #0
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _0225492C
	add r0, r4, #0
	bl MOD37_022548E0
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x10]
	bl MOD20_022529A0
_0225492C:
	pop {r3, r4, r5, pc}
	nop
_02254930: .word 0x02254D28
	thumb_func_end MOD37_02254900

	thumb_func_start MOD37_02254934
MOD37_02254934: ; 0x02254934
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD37_02254934

	thumb_func_start MOD37_0225493C
MOD37_0225493C: ; 0x0225493C
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254944
	b _02254946
_02254944:
	mov r1, #2
_02254946:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD37_0225493C

	thumb_func_start MOD37_02254950
MOD37_02254950: ; 0x02254950
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254960
	cmp r0, #1
	beq _02254970
	b _0225498A
_02254960:
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl MOD37_02254B20
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _0225498A
_02254970:
	ldr r0, [r4, #0xc]
	mov r1, #0
	bl MOD37_02254B44
	cmp r0, #0
	beq _0225498A
	ldr r0, [r4, #0x10]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD37_0225493C
_0225498A:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD37_02254950

	thumb_func_start MOD37_02254990
MOD37_02254990: ; 0x02254990
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _022549A0
	mov r1, #2
	bl MOD37_0225493C
_022549A0:
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549AC
	cmp r0, #1
	beq _022549CE
	b _022549DE
_022549AC:
	bl MOD37_02254A18
	cmp r0, #0
	beq _022549DE
	bl FUN_0201BA60
	mov r1, #1
	and r0, r1
	str r0, [r4, #8]
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl MOD37_02254B20
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549DE
_022549CE:
	ldr r0, [r4, #0xc]
	mov r1, #2
	bl MOD37_02254B44
	cmp r0, #0
	beq _022549DE
	mov r0, #0
	strb r0, [r4, #1]
_022549DE:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD37_02254990

	thumb_func_start MOD37_022549E4
MOD37_022549E4: ; 0x022549E4
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549F4
	cmp r0, #1
	beq _02254A04
	b _02254A12
_022549F4:
	ldr r0, [r4, #0xc]
	mov r1, #1
	bl MOD37_02254B20
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A12
_02254A04:
	ldr r0, [r4, #0xc]
	bl MOD37_02254B50
	cmp r0, #0
	beq _02254A12
	mov r0, #1
	pop {r4, pc}
_02254A12:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD37_022549E4

	thumb_func_start MOD37_02254A18
MOD37_02254A18: ; 0x02254A18
	push {r3, lr}
	sub sp, #8
	add r0, sp, #4
	add r1, sp, #0
	bl MOD20_02252BB8
	cmp r0, #0
	beq _02254A4E
	ldr r1, [sp, #4]
	mov r0, #0x70
	sub r0, r0, r1
	add r3, r0, #0
	mul r3, r0
	ldr r1, [sp]
	mov r0, #0x90
	sub r2, r0, r1
	add r1, r2, #0
	mul r1, r2
	str r1, [sp]
	add r1, r3, r1
	lsl r0, r0, #2
	str r3, [sp, #4]
	cmp r1, r0
	bhs _02254A4E
	add sp, #8
	mov r0, #1
	pop {r3, pc}
_02254A4E:
	mov r0, #0
	add sp, #8
	pop {r3, pc}
	thumb_func_end MOD37_02254A18

	thumb_func_start MOD37_02254A54
MOD37_02254A54: ; 0x02254A54
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x48
	bl FUN_02016998
	add r4, r0, #0
	beq _02254A94
	add r0, #8
	mov r1, #4
	bl MOD20_022536F4
	str r6, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x20]
	add r0, r4, #0
	bl MOD37_02254AA0
	ldr r1, _02254A98 ; =0xFFFF5800
	ldr r0, _02254A9C ; =0x02254DA0
	str r1, [r0]
	mov r1, #0xb
	lsl r1, r1, #8
	str r1, [r0, #4]
	str r4, [r5]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254A94:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
_02254A98: .word 0xFFFF5800
_02254A9C: .word 0x02254DA0
	thumb_func_end MOD37_02254A54

	thumb_func_start MOD37_02254AA0
MOD37_02254AA0: ; 0x02254AA0
	push {r3, r4, lr}
	sub sp, #0xc
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	add r4, r0, #0
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x39
	bl FUN_02006A34
	mov r0, #8
	str r0, [sp]
	add r0, r4, #0
	add r0, #0x28
	mov r1, #0xc
	mov r2, #0x37
	mov r3, #0x38
	bl MOD20_02253FBC
	add r2, r4, #0
	ldr r0, [r4, #0x20]
	ldr r1, _02254AF0 ; =0x02254D34
	add r2, #0x28
	bl MOD20_02253E74
	str r0, [r4, #0x24]
	ldr r0, [r4]
	ldr r0, [r0]
	cmp r0, #0
	bne _02254AEA
	ldr r0, [r4, #0x24]
	mov r1, #2
	bl MOD20_02253F28
_02254AEA:
	add sp, #0xc
	pop {r3, r4, pc}
	nop
_02254AF0: .word 0x02254D34
	thumb_func_end MOD37_02254AA0

	thumb_func_start MOD37_02254AF4
MOD37_02254AF4: ; 0x02254AF4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x20]
	ldr r1, [r4, #0x24]
	bl MOD20_02253F14
	add r4, #0x28
	add r0, r4, #0
	bl MOD20_02254014
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD37_02254AF4

	thumb_func_start MOD37_02254B0C
MOD37_02254B0C: ; 0x02254B0C
	push {r4, lr}
	add r4, r0, #0
	beq _02254B1C
	bl MOD37_02254AF4
	add r0, r4, #0
	bl FUN_02016A18
_02254B1C:
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD37_02254B0C

	thumb_func_start MOD37_02254B20
MOD37_02254B20: ; 0x02254B20
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254B40 ; =0x02254D60
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254B40: .word 0x02254D60
	thumb_func_end MOD37_02254B20

	thumb_func_start MOD37_02254B44
MOD37_02254B44: ; 0x02254B44
	ldr r3, _02254B4C ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254B4C: .word MOD20_02253794
	thumb_func_end MOD37_02254B44

	thumb_func_start MOD37_02254B50
MOD37_02254B50: ; 0x02254B50
	ldr r3, _02254B58 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254B58: .word MOD20_022537B8
	thumb_func_end MOD37_02254B50

	thumb_func_start MOD37_02254B5C
MOD37_02254B5C: ; 0x02254B5C
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD37_02254B5C

	thumb_func_start MOD37_02254B70
MOD37_02254B70: ; 0x02254B70
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254BF4 ; =0x02254D44
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
	mov r1, #0x36
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
	mov r1, #0x35
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r1, _02254BF8 ; =0x04001000
	ldr r0, _02254BFC ; =0xFFFFE0FF
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
	bl MOD37_02254B5C
	add sp, #0x14
	pop {r4, r5, pc}
	nop
_02254BF4: .word 0x02254D44
_02254BF8: .word 0x04001000
_02254BFC: .word 0xFFFFE0FF
	thumb_func_end MOD37_02254B70

	thumb_func_start MOD37_02254C00
MOD37_02254C00: ; 0x02254C00
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	add r0, r5, #0
	bl MOD20_022538AC
	cmp r0, #0
	beq _02254C1C
	cmp r0, #1
	beq _02254C26
	pop {r3, r4, r5, pc}
_02254C1C:
	mov r0, #1
	str r0, [r4, #0x44]
	add r0, r5, #0
	bl MOD20_022538B0
_02254C26:
	add r0, r4, #0
	mov r1, #2
	bl MOD37_02254B44
	cmp r0, #0
	beq _02254C40
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r5, #0
	bl MOD37_02254B5C
_02254C40:
	pop {r3, r4, r5, pc}
	.align 2, 0
	thumb_func_end MOD37_02254C00

	thumb_func_start MOD37_02254C44
MOD37_02254C44: ; 0x02254C44
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
	beq _02254C6C
	cmp r0, #1
	beq _02254C90
	cmp r0, #2
	beq _02254D10
	pop {r4, r5, r6, pc}
_02254C6C:
	ldr r0, _02254D18 ; =0x00000675
	bl MOD20_02252B28
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl MOD20_02253F28
	mov r0, #9
	lsl r0, r0, #0x10
	str r0, [r4, #0x3c]
	ldr r0, _02254D1C ; =0x02254DA0
	ldr r0, [r0]
	str r0, [r4, #0x40]
	mov r0, #0
	str r0, [r4, #0x44]
	add r0, r5, #0
	bl MOD20_022538B0
_02254C90:
	ldr r0, [r4, #0x44]
	cmp r0, #0
	beq _02254C9E
	add r0, r5, #0
	bl MOD37_02254B5C
	pop {r4, r5, r6, pc}
_02254C9E:
	ldr r1, [r4, #0x3c]
	ldr r0, [r4, #0x40]
	add r0, r1, r0
	str r0, [r4, #0x3c]
	ldr r0, _02254D1C ; =0x02254DA0
	ldr r1, [r4, #0x40]
	ldr r0, [r0, #4]
	add r1, r1, r0
	str r1, [r4, #0x40]
	cmp r1, #0
	ble _02254D02
	mov r0, #9
	ldr r2, [r4, #0x3c]
	lsl r0, r0, #0x10
	cmp r2, r0
	blt _02254D02
	mov r0, #0x38
	mul r0, r1
	mov r1, #0x64
	bl _s32_div_f
	neg r1, r0
	ldr r0, _02254D20 ; =0xFFFFE000
	str r1, [r4, #0x40]
	cmp r1, r0
	ldr r0, _02254D24 ; =0x00000676
	bge _02254CE0
	bl MOD20_02252B28
	mov r0, #9
	lsl r0, r0, #0x10
	str r0, [r4, #0x3c]
	b _02254D02
_02254CE0:
	bl MOD20_02252B28
	ldr r0, [r6]
	cmp r0, #0
	beq _02254CEE
	mov r1, #1
	b _02254CF0
_02254CEE:
	mov r1, #2
_02254CF0:
	ldr r0, [r4, #0x24]
	bl MOD20_02253F28
	mov r0, #9
	lsl r0, r0, #0x10
	str r0, [r4, #0x3c]
	add r0, r5, #0
	bl MOD20_022538B0
_02254D02:
	mov r1, #7
	ldr r0, [r4, #0x24]
	ldr r2, [r4, #0x3c]
	lsl r1, r1, #0x10
	bl MOD20_02253F64
	pop {r4, r5, r6, pc}
_02254D10:
	add r0, r5, #0
	bl MOD37_02254B5C
	pop {r4, r5, r6, pc}
	.align 2, 0
_02254D18: .word 0x00000675
_02254D1C: .word 0x02254DA0
_02254D20: .word 0xFFFFE000
_02254D24: .word 0x00000676
	thumb_func_end MOD37_02254C44

	.section .rodata
	; 0x02254D28
	.incbin "baserom.nds", 0x2904E8, 0x68

	.section .sinit
	.word MOD37_02254840

	.section .bss
	; 0x02254DA0
	.space 8
