	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD24_02254840
MOD24_02254840: ; 0x02254840
	ldr r3, _02254848 ; =MOD20_02252978
	ldr r0, _0225484C ; =MOD24_02254854
	ldr r1, _02254850 ; =MOD24_02254990
	bx r3
	.align 2, 0
_02254848: .word MOD20_02252978
_0225484C: .word MOD24_02254854
_02254850: .word MOD24_02254990
	thumb_func_end MOD24_02254840

	thumb_func_start MOD24_02254854
MOD24_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r6, r1, #0
	mov r1, #0x17
	add r5, r0, #0
	mov r0, #8
	lsl r1, r1, #8
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254894
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD24_0225489C
	cmp r0, #0
	beq _0225488E
	ldr r0, _02254898 ; =MOD24_02254918
	add r1, r4, #0
	mov r2, #1
	bl FUN_0200CA44
	cmp r0, #0
	beq _0225488E
	str r4, [r5]
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_0225488E:
	add r0, r4, #0
	bl FreeToHeap
_02254894:
	mov r0, #0
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254898: .word MOD24_02254918
	thumb_func_end MOD24_02254854

	thumb_func_start MOD24_0225489C
MOD24_0225489C: ; 0x0225489C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	ldr r0, _022548E4 ; =0x000016F0
	add r4, r1, #0
	str r3, [r5, r0]
	mov r1, #1
	str r1, [r5, #8]
	add r0, r0, #4
	add r1, r5, #0
	add r0, r5, r0
	add r1, #8
	bl MOD24_02254CA0
	cmp r0, #0
	beq _022548E0
	mov r0, #0
	strb r0, [r5]
	strb r0, [r5, #1]
	strb r0, [r5, #2]
	strb r0, [r5, #3]
	mov r0, #8
	str r0, [sp]
	ldr r0, _022548E8 ; =0x022550F8
	ldr r2, _022548EC ; =MOD24_02254960
	mov r1, #2
	add r3, r5, #0
	bl MOD20_02254130
	ldr r1, _022548F0 ; =0x000016FC
	str r0, [r5, r1]
	sub r0, r1, #4
	str r4, [r5, r0]
	mov r0, #1
	pop {r3, r4, r5, pc}
_022548E0:
	mov r0, #0
	pop {r3, r4, r5, pc}
	.align 2, 0
_022548E4: .word 0x000016F0
_022548E8: .word 0x022550F8
_022548EC: .word MOD24_02254960
_022548F0: .word 0x000016FC
	thumb_func_end MOD24_0225489C

	thumb_func_start MOD24_022548F4
MOD24_022548F4: ; 0x022548F4
	push {r4, lr}
	add r4, r0, #0
	ldr r0, _02254910 ; =0x000016FC
	ldr r0, [r4, r0]
	bl MOD20_02254198
	ldr r0, _02254914 ; =0x000016F4
	ldr r0, [r4, r0]
	bl MOD24_02254D48
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	.align 2, 0
_02254910: .word 0x000016FC
_02254914: .word 0x000016F4
	thumb_func_end MOD24_022548F4

	thumb_func_start MOD24_02254918
MOD24_02254918: ; 0x02254918
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhs _02254954
	ldr r1, _02254958 ; =0x000016F8
	ldr r0, [r4, r1]
	add r1, r1, #4
	ldr r1, [r4, r1]
	bl MOD20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _0225495C ; =0x02255100
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254954
	add r0, r4, #0
	bl MOD24_022548F4
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, _02254958 ; =0x000016F8
	ldr r0, [r4, r0]
	bl MOD20_022529A0
_02254954:
	pop {r3, r4, r5, pc}
	nop
_02254958: .word 0x000016F8
_0225495C: .word 0x02255100
	thumb_func_end MOD24_02254918

	thumb_func_start MOD24_02254960
MOD24_02254960: ; 0x02254960
	push {r3, lr}
	cmp r2, #1
	bne _02254988
	ldr r1, [r3, #8]
	cmp r1, #1
	bne _02254970
	cmp r0, #0
	beq _02254978
_02254970:
	cmp r1, #0
	bne _02254988
	cmp r0, #1
	bne _02254988
_02254978:
	ldr r0, [r3, #8]
	mov r1, #1
	eor r0, r1
	str r0, [r3, #8]
	ldr r0, _0225498C ; =0x000016F4
	ldr r0, [r3, r0]
	bl MOD24_02254D8C
_02254988:
	pop {r3, pc}
	nop
_0225498C: .word 0x000016F4
	thumb_func_end MOD24_02254960

	thumb_func_start MOD24_02254990
MOD24_02254990: ; 0x02254990
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD24_02254990

	thumb_func_start MOD24_02254998
MOD24_02254998: ; 0x02254998
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _022549A0
	b _022549A2
_022549A0:
	mov r1, #2
_022549A2:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD24_02254998

	thumb_func_start MOD24_022549AC
MOD24_022549AC: ; 0x022549AC
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549BC
	cmp r0, #1
	beq _022549CE
	b _022549EC
_022549BC:
	ldr r0, _022549F0 ; =0x000016F4
	mov r1, #0
	ldr r0, [r4, r0]
	bl MOD24_02254D8C
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549EC
_022549CE:
	ldr r0, _022549F0 ; =0x000016F4
	mov r1, #0
	ldr r0, [r4, r0]
	bl MOD24_02254DB0
	cmp r0, #0
	beq _022549EC
	ldr r0, _022549F4 ; =0x000016F8
	ldr r0, [r4, r0]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD24_02254998
_022549EC:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_022549F0: .word 0x000016F4
_022549F4: .word 0x000016F8
	thumb_func_end MOD24_022549AC

	thumb_func_start MOD24_022549F8
MOD24_022549F8: ; 0x022549F8
	push {r3, r4, r5, r6, lr}
	sub sp, #4
	add r5, r0, #0
	ldrb r1, [r5, #2]
	cmp r1, #0
	beq _02254A0A
	mov r1, #2
	bl MOD24_02254998
_02254A0A:
	ldrb r0, [r5, #1]
	cmp r0, #0
	bne _02254A60
	ldr r0, _02254A68 ; =0x000016F8
	ldr r0, [r5, r0]
	bl MOD20_02252C08
	cmp r0, #0
	bne _02254A60
	ldrb r0, [r5, #3]
	cmp r0, #0
	beq _02254A48
	add r0, r5, #0
	ldr r6, [r5, #0xc]
	ldr r4, [r5, #0x10]
	bl MOD24_02254AD4
	cmp r0, #0
	beq _02254A42
	ldr r0, [r5, #0x10]
	add r1, r6, #0
	str r0, [sp]
	ldr r3, [r5, #0xc]
	add r0, r5, #0
	add r2, r4, #0
	bl MOD24_02254B20
	b _02254A60
_02254A42:
	mov r0, #0
	strb r0, [r5, #3]
	b _02254A60
_02254A48:
	add r0, r5, #0
	bl MOD24_02254A70
	cmp r0, #0
	beq _02254A60
	ldr r0, _02254A6C ; =0x000016F4
	mov r1, #3
	ldr r0, [r5, r0]
	bl MOD24_02254D8C
	mov r0, #1
	strb r0, [r5, #3]
_02254A60:
	mov r0, #0
	add sp, #4
	pop {r3, r4, r5, r6, pc}
	nop
_02254A68: .word 0x000016F8
_02254A6C: .word 0x000016F4
	thumb_func_end MOD24_022549F8

	thumb_func_start MOD24_02254A70
MOD24_02254A70: ; 0x02254A70
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r0, sp, #4
	add r1, sp, #0
	bl MOD20_02252B68
	cmp r0, #0
	beq _02254ACC
	ldr r1, [sp, #4]
	ldr r2, [sp]
	sub r1, #0x10
	sub r2, #0x10
	cmp r1, #0x9c
	bhs _02254A92
	mov r0, #1
	b _02254A94
_02254A92:
	mov r0, #0
_02254A94:
	cmp r2, #0x96
	bhs _02254A9C
	mov r3, #1
	b _02254A9E
_02254A9C:
	mov r3, #0
_02254A9E:
	tst r0, r3
	beq _02254ACC
	lsr r3, r1, #1
	lsr r0, r2, #1
	add r2, r4, #0
	mov r1, #0x4b
	add r2, #0x14
	mul r1, r3
	str r3, [sp, #4]
	str r0, [sp]
	add r3, r2, r1
	ldrb r1, [r3, r0]
	ldr r2, [r4, #8]
	cmp r2, r1
	beq _02254ACC
	strb r2, [r3, r0]
	ldr r0, [sp, #4]
	str r0, [r4, #0xc]
	ldr r0, [sp]
	add sp, #8
	str r0, [r4, #0x10]
	mov r0, #1
	pop {r4, pc}
_02254ACC:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD24_02254A70

	thumb_func_start MOD24_02254AD4
MOD24_02254AD4: ; 0x02254AD4
	push {r4, lr}
	sub sp, #8
	add r4, r0, #0
	add r0, sp, #4
	add r1, sp, #0
	bl MOD20_02252B68
	cmp r0, #0
	beq _02254B1A
	ldr r1, [sp, #4]
	ldr r2, [sp]
	sub r1, #0x10
	sub r2, #0x10
	cmp r1, #0x9c
	bhs _02254AF6
	mov r0, #1
	b _02254AF8
_02254AF6:
	mov r0, #0
_02254AF8:
	cmp r2, #0x96
	bhs _02254B00
	mov r3, #1
	b _02254B02
_02254B00:
	mov r3, #0
_02254B02:
	tst r0, r3
	beq _02254B1A
	lsr r1, r1, #1
	lsr r0, r2, #1
	str r1, [sp, #4]
	str r0, [sp]
	str r1, [r4, #0xc]
	ldr r0, [sp]
	add sp, #8
	str r0, [r4, #0x10]
	mov r0, #1
	pop {r4, pc}
_02254B1A:
	mov r0, #0
	add sp, #8
	pop {r4, pc}
	thumb_func_end MOD24_02254AD4

	thumb_func_start MOD24_02254B20
MOD24_02254B20: ; 0x02254B20
	push {r4, r5, r6, r7, lr}
	sub sp, #0x14
	add r5, r0, #0
	ldr r0, [sp, #0x28]
	add r4, r2, #0
	add r6, r1, #0
	str r3, [sp]
	str r0, [sp, #0x28]
	cmp r4, r0
	bne _02254B3C
	add r0, r3, #0
	cmp r6, r0
	bne _02254B3C
	b _02254C5C
_02254B3C:
	ldr r0, [sp]
	cmp r0, r6
	bls _02254B46
	sub r1, r0, r6
	b _02254B48
_02254B46:
	sub r1, r6, r0
_02254B48:
	ldr r0, [sp, #0x28]
	cmp r0, r4
	bls _02254B52
	sub r2, r0, r4
	b _02254B54
_02254B52:
	sub r2, r4, r0
_02254B54:
	cmp r1, r2
	bls _02254BD6
	ldr r0, [sp]
	cmp r0, r6
	bls _02254B64
	mov r0, #1
	str r0, [sp, #4]
	b _02254B6A
_02254B64:
	mov r0, #0
	mvn r0, r0
	str r0, [sp, #4]
_02254B6A:
	cmp r1, #0
	beq _02254B7C
	ldr r0, [sp, #0x28]
	sub r0, r0, r4
	lsl r0, r0, #0xc
	bl _s32_div_f
	str r0, [sp, #0x10]
	b _02254B80
_02254B7C:
	mov r0, #0
	str r0, [sp, #0x10]
_02254B80:
	ldr r0, [sp, #0x10]
	lsl r1, r4, #0xc
	add r7, r1, r0
	ldr r0, [sp, #4]
	add r6, r6, r0
	ldr r0, [sp]
	cmp r6, r0
	beq _02254C40
	mov r1, #0x4b
	add r0, r6, #0
	mul r0, r1
	add r4, r5, r0
	ldr r0, [sp, #4]
	mul r1, r0
	str r1, [sp, #0xc]
_02254B9E:
	asr r2, r7, #0xc
	cmp r6, #0x4e
	bhs _02254BC2
	cmp r2, #0x4b
	bhs _02254BC2
	add r1, r4, r2
	ldrb r0, [r1, #0x14]
	ldr r3, [r5, #8]
	cmp r3, r0
	beq _02254BC2
	strb r3, [r1, #0x14]
	str r6, [r5, #0xc]
	ldr r0, _02254C60 ; =0x000016F4
	str r2, [r5, #0x10]
	ldr r0, [r5, r0]
	mov r1, #3
	bl MOD24_02254D8C
_02254BC2:
	ldr r0, [sp, #0xc]
	add r4, r4, r0
	ldr r0, [sp, #4]
	add r6, r6, r0
	ldr r0, [sp, #0x10]
	add r7, r7, r0
	ldr r0, [sp]
	cmp r6, r0
	bne _02254B9E
	b _02254C40
_02254BD6:
	ldr r0, [sp, #0x28]
	cmp r0, r4
	bls _02254BE0
	mov r7, #1
	b _02254BE4
_02254BE0:
	mov r7, #0
	mvn r7, r7
_02254BE4:
	cmp r2, #0
	beq _02254BF8
	ldr r0, [sp]
	add r1, r2, #0
	sub r0, r0, r6
	lsl r0, r0, #0xc
	bl _s32_div_f
	str r0, [sp, #8]
	b _02254BFC
_02254BF8:
	mov r0, #0
	str r0, [sp, #8]
_02254BFC:
	ldr r0, [sp, #8]
	lsl r1, r6, #0xc
	add r6, r1, r0
	ldr r0, [sp, #0x28]
	add r4, r4, r7
	cmp r4, r0
	beq _02254C40
_02254C0A:
	asr r3, r6, #0xc
	cmp r4, #0x4b
	bhs _02254C34
	cmp r3, #0x4e
	bhs _02254C34
	mov r0, #0x4b
	mul r0, r3
	add r0, r5, r0
	add r2, r0, r4
	ldrb r0, [r2, #0x14]
	ldr r1, [r5, #8]
	cmp r1, r0
	beq _02254C34
	strb r1, [r2, #0x14]
	str r3, [r5, #0xc]
	ldr r0, _02254C60 ; =0x000016F4
	str r4, [r5, #0x10]
	ldr r0, [r5, r0]
	mov r1, #3
	bl MOD24_02254D8C
_02254C34:
	ldr r0, [sp, #8]
	add r4, r4, r7
	add r6, r6, r0
	ldr r0, [sp, #0x28]
	cmp r4, r0
	bne _02254C0A
_02254C40:
	ldr r0, [sp, #0x28]
	cmp r0, #0x4b
	bhs _02254C5C
	ldr r0, [sp]
	cmp r0, #0x4e
	bhs _02254C5C
	str r0, [r5, #0xc]
	ldr r0, [sp, #0x28]
	mov r1, #3
	str r0, [r5, #0x10]
	ldr r0, _02254C60 ; =0x000016F4
	ldr r0, [r5, r0]
	bl MOD24_02254D8C
_02254C5C:
	add sp, #0x14
	pop {r4, r5, r6, r7, pc}
	.align 2, 0
_02254C60: .word 0x000016F4
	thumb_func_end MOD24_02254B20

	thumb_func_start MOD24_02254C64
MOD24_02254C64: ; 0x02254C64
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254C74
	cmp r0, #1
	beq _02254C86
	b _02254C96
_02254C74:
	ldr r0, _02254C9C ; =0x000016F4
	mov r1, #5
	ldr r0, [r4, r0]
	bl MOD24_02254D8C
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254C96
_02254C86:
	ldr r0, _02254C9C ; =0x000016F4
	ldr r0, [r4, r0]
	bl MOD24_02254DBC
	cmp r0, #0
	beq _02254C96
	mov r0, #1
	pop {r4, pc}
_02254C96:
	mov r0, #0
	pop {r4, pc}
	nop
_02254C9C: .word 0x000016F4
	thumb_func_end MOD24_02254C64

	thumb_func_start MOD24_02254CA0
MOD24_02254CA0: ; 0x02254CA0
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x74
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254CFA
	mov r0, #7
	bl FUN_02016B90
	cmp r0, #0
	bne _02254CC0
	bl ErrorHandling
_02254CC0:
	add r0, r4, #0
	add r0, #8
	mov r1, #0x10
	bl MOD20_022536F4
	mov r0, #7
	bl FUN_02016B90
	cmp r0, #0
	bne _02254CD8
	bl ErrorHandling
_02254CD8:
	str r6, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x50]
	mov r0, #7
	bl FUN_02016B90
	cmp r0, #0
	bne _02254CF4
	bl ErrorHandling
_02254CF4:
	str r4, [r5]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254CFA:
	mov r0, #0
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD24_02254CA0

	thumb_func_start MOD24_02254D00
MOD24_02254D00: ; 0x02254D00
	push {r4, lr}
	add r4, r0, #0
	mov r0, #8
	mov r1, #1
	bl FUN_02018FF4
	str r0, [r4, #0x70]
	add r1, r0, #0
	beq _02254D3C
	ldr r0, [r4, #4]
	ldr r2, _02254D40 ; =0x0225510C
	bl FUN_02019150
	mov r2, #0xbe
	ldr r1, [r4]
	ldr r0, _02254D44 ; =0x000016E8
	lsl r2, r2, #6
	ldr r0, [r1, r0]
	ldr r1, [r4, #0x70]
	ldr r1, [r1, #0xc]
	bl FUN_0208946C
	cmp r0, #0
	bne _02254D38
	ldr r0, [r4, #0x70]
	mov r1, #4
	bl FUN_02019620
_02254D38:
	mov r0, #1
	pop {r4, pc}
_02254D3C:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
_02254D40: .word 0x0225510C
_02254D44: .word 0x000016E8
	thumb_func_end MOD24_02254D00

	thumb_func_start MOD24_02254D48
MOD24_02254D48: ; 0x02254D48
	push {r4, lr}
	add r4, r0, #0
	beq _02254D84
	mov r0, #7
	bl FUN_02016B90
	cmp r0, #0
	bne _02254D5C
	bl ErrorHandling
_02254D5C:
	ldr r2, [r4, #0x70]
	cmp r2, #0
	beq _02254D7E
	ldr r1, [r4]
	ldr r0, _02254D88 ; =0x000016E8
	ldr r0, [r1, r0]
	ldr r1, [r2, #0xc]
	mov r2, #0xbe
	lsl r2, r2, #6
	bl FUN_02089444
	ldr r0, [r4, #0x70]
	bl FUN_02019178
	ldr r0, [r4, #0x70]
	bl FreeToHeap
_02254D7E:
	add r0, r4, #0
	bl FreeToHeap
_02254D84:
	pop {r4, pc}
	nop
_02254D88: .word 0x000016E8
	thumb_func_end MOD24_02254D48

	thumb_func_start MOD24_02254D8C
MOD24_02254D8C: ; 0x02254D8C
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254DAC ; =0x0225516C
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254DAC: .word 0x0225516C
	thumb_func_end MOD24_02254D8C

	thumb_func_start MOD24_02254DB0
MOD24_02254DB0: ; 0x02254DB0
	ldr r3, _02254DB8 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254DB8: .word MOD20_02253794
	thumb_func_end MOD24_02254DB0

	thumb_func_start MOD24_02254DBC
MOD24_02254DBC: ; 0x02254DBC
	ldr r3, _02254DC4 ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254DC4: .word MOD20_022537B8
	thumb_func_end MOD24_02254DBC

	thumb_func_start MOD24_02254DC8
MOD24_02254DC8: ; 0x02254DC8
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD24_02254DC8

	thumb_func_start MOD24_02254DDC
MOD24_02254DDC: ; 0x02254DDC
	push {r4, r5, lr}
	sub sp, #0x14
	mov r0, #8
	add r4, r1, #0
	bl FUN_02016B90
	cmp r0, #0
	bne _02254DF0
	bl ErrorHandling
_02254DF0:
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254ED0 ; =0x02255114
	mov r1, #6
	mov r3, #0
	bl FUN_02016C18
	ldr r0, [r5, #4]
	ldr r2, _02254ED4 ; =0x02255130
	mov r1, #7
	mov r3, #0
	bl FUN_02016C18
	mov r0, #8
	bl FUN_02016B90
	cmp r0, #0
	bne _02254E1E
	bl ErrorHandling
_02254E1E:
	mov r0, #0
	str r0, [sp]
	str r0, [sp, #4]
	mov r0, #1
	str r0, [sp, #8]
	mov r0, #8
	str r0, [sp, #0xc]
	ldr r2, [r5, #4]
	mov r0, #0xc
	mov r1, #0x1e
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
	mov r1, #0x1f
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	mov r0, #8
	bl FUN_02016B90
	cmp r0, #0
	bne _02254E68
	bl ErrorHandling
_02254E68:
	add r0, r5, #0
	bl MOD24_02254D00
	ldr r0, [r5, #0x70]
	bl FUN_020191D0
	mov r0, #8
	bl FUN_02016B90
	cmp r0, #0
	bne _02254E82
	bl ErrorHandling
_02254E82:
	add r0, r5, #0
	bl MOD24_02255078
	mov r0, #8
	bl FUN_02016B90
	cmp r0, #0
	bne _02254E96
	bl ErrorHandling
_02254E96:
	ldr r0, [r5, #4]
	mov r1, #7
	bl FUN_02017CD0
	ldr r1, _02254ED8 ; =0x04001000
	ldr r0, _02254EDC ; =0xFFFFE0FF
	ldr r3, [r1]
	ldr r2, [r1]
	str r3, [sp, #0x10]
	and r0, r2
	lsl r2, r3, #0x13
	lsr r3, r2, #0x1b
	mov r2, #0x14
	orr r2, r3
	lsl r2, r2, #8
	orr r0, r2
	str r0, [r1]
	add r0, r4, #0
	bl MOD24_02254DC8
	mov r0, #8
	bl FUN_02016B90
	cmp r0, #0
	bne _02254ECC
	bl ErrorHandling
_02254ECC:
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_02254ED0: .word 0x02255114
_02254ED4: .word 0x02255130
_02254ED8: .word 0x04001000
_02254EDC: .word 0xFFFFE0FF
	thumb_func_end MOD24_02254DDC

	thumb_func_start MOD24_02254EE0
MOD24_02254EE0: ; 0x02254EE0
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	ldr r0, [r4]
	ldr r0, [r0]
	cmp r0, #1
	ldr r0, [r4, #0x68]
	bne _02254F06
	mov r1, #0
	bl MOD20_02253F28
	ldr r0, [r4, #0x6c]
	mov r1, #3
	bl MOD20_02253F28
	b _02254F14
_02254F06:
	mov r1, #1
	bl MOD20_02253F28
	ldr r0, [r4, #0x6c]
	mov r1, #2
	bl MOD20_02253F28
_02254F14:
	ldr r0, _02254F24 ; =0x00000663
	bl MOD20_02252B28
	add r0, r5, #0
	bl MOD24_02254DC8
	pop {r3, r4, r5, pc}
	nop
_02254F24: .word 0x00000663
	thumb_func_end MOD24_02254EE0

	thumb_func_start MOD24_02254F28
MOD24_02254F28: ; 0x02254F28
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0, #0x70]
	bl FUN_02019548
	add r0, r4, #0
	bl MOD24_02254DC8
	pop {r4, pc}
	thumb_func_end MOD24_02254F28

	thumb_func_start MOD24_02254F40
MOD24_02254F40: ; 0x02254F40
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x18
	add r0, r1, #0
	str r1, [sp, #8]
	bl MOD20_022538A0
	add r7, r0, #0
	ldr r0, [r7]
	ldr r1, [r0]
	cmp r1, #0
	bne _02254FF2
	mov r1, #8
	str r1, [sp, #0x10]
	str r1, [sp, #0x14]
	ldr r1, [r0, #4]
	ldr r0, [r0, #8]
	lsl r1, r1, #1
	lsl r0, r0, #1
	sub r6, r1, #4
	sub r5, r0, #4
	cmp r6, #0
	bge _02254F74
	ldr r0, [sp, #0x10]
	add r0, r0, r6
	str r0, [sp, #0x14]
	mov r6, #0
_02254F74:
	cmp r5, #0
	bge _02254F80
	ldr r0, [sp, #0x10]
	add r0, r0, r5
	str r0, [sp, #0x10]
	mov r5, #0
_02254F80:
	ldr r0, [sp, #0x14]
	lsl r2, r6, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp]
	ldr r0, [sp, #0x10]
	lsl r3, r5, #0x10
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	str r0, [sp, #4]
	ldr r0, [r7, #0x70]
	mov r1, #4
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl FUN_020196F4
	asr r1, r5, #3
	mov r2, #0x14
	asr r0, r6, #3
	mul r2, r1
	add r4, r0, r2
	ldr r2, [sp, #0x14]
	add r2, r6, r2
	sub r2, r2, #1
	asr r2, r2, #3
	sub r0, r2, r0
	ldr r2, [sp, #0x10]
	add r0, r0, #1
	add r2, r5, r2
	sub r2, r2, #1
	asr r2, r2, #3
	sub r1, r2, r1
	add r1, r1, #1
	sub r6, r1, #1
	cmp r1, #0
	beq _0225502C
	lsl r0, r0, #5
	lsl r5, r4, #5
	str r0, [sp, #0xc]
_02254FCE:
	ldr r0, [r7, #0x70]
	add r1, r4, #0
	ldr r0, [r0, #0xc]
	add r1, #0xc
	ldr r2, [sp, #0xc]
	add r0, r0, r5
	lsl r1, r1, #5
	bl GXS_LoadBG3Char
	mov r0, #0xa
	lsl r0, r0, #6
	add r5, r5, r0
	add r0, r6, #0
	add r4, #0x14
	sub r6, r6, #1
	cmp r0, #0
	bne _02254FCE
	b _0225502C
_02254FF2:
	ldr r1, [r0, #4]
	ldr r0, [r0, #8]
	lsl r2, r1, #1
	lsl r3, r0, #1
	asr r1, r3, #3
	mov r0, #0x14
	asr r4, r2, #3
	mul r0, r1
	add r4, r4, r0
	mov r0, #2
	str r0, [sp]
	str r0, [sp, #4]
	lsl r2, r2, #0x10
	lsl r3, r3, #0x10
	ldr r0, [r7, #0x70]
	mov r1, #1
	lsr r2, r2, #0x10
	lsr r3, r3, #0x10
	bl FUN_020196F4
	ldr r0, [r7, #0x70]
	mov r2, #0x20
	ldr r1, [r0, #0xc]
	lsl r0, r4, #5
	add r4, #0xc
	add r0, r1, r0
	lsl r1, r4, #5
	bl GXS_LoadBG3Char
_0225502C:
	ldr r0, [sp, #8]
	bl MOD24_02254DC8
	add sp, #0x18
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
	thumb_func_end MOD24_02254F40

	thumb_func_start MOD24_02255038
MOD24_02255038: ; 0x02255038
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0, #0x70]
	bl FUN_02019548
	add r0, r4, #0
	bl MOD24_02254DC8
	pop {r4, pc}
	thumb_func_end MOD24_02255038

	thumb_func_start MOD24_02255050
MOD24_02255050: ; 0x02255050
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	bl MOD24_022550D4
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_020178A0
	ldr r0, [r4, #4]
	mov r1, #7
	bl FUN_020178A0
	add r0, r5, #0
	bl MOD24_02254DC8
	pop {r3, r4, r5, pc}
	thumb_func_end MOD24_02255050

	thumb_func_start MOD24_02255078
MOD24_02255078: ; 0x02255078
	push {r3, r4, r5, r6, r7, lr}
	sub sp, #0x10
	mov r3, #0
	str r3, [sp]
	mov r2, #1
	add r7, r0, #0
	str r2, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	mov r0, #0xc
	mov r1, #0x20
	bl FUN_02006A34
	mov r0, #8
	str r0, [sp]
	add r0, r7, #0
	add r0, #0x54
	mov r1, #0xc
	mov r2, #0x21
	mov r3, #0x22
	bl MOD20_02253FBC
	cmp r0, #0
	beq _022550CC
	add r0, r7, #0
	str r0, [sp, #0xc]
	add r0, #0x54
	ldr r4, _022550D0 ; =0x0225514C
	mov r6, #0
	add r5, r7, #0
	str r0, [sp, #0xc]
_022550B6:
	ldr r0, [r7, #0x50]
	ldr r2, [sp, #0xc]
	add r1, r4, #0
	bl MOD20_02253E74
	str r0, [r5, #0x68]
	add r6, r6, #1
	add r4, #0x10
	add r5, r5, #4
	cmp r6, #2
	blt _022550B6
_022550CC:
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_022550D0: .word 0x0225514C
	thumb_func_end MOD24_02255078

	thumb_func_start MOD24_022550D4
MOD24_022550D4: ; 0x022550D4
	push {r4, r5, r6, lr}
	add r6, r0, #0
	mov r4, #0
	add r5, r6, #0
_022550DC:
	ldr r0, [r6, #0x50]
	ldr r1, [r5, #0x68]
	bl MOD20_02253F14
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blo _022550DC
	add r6, #0x54
	add r0, r6, #0
	bl MOD20_02254014
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD24_022550D4

	.section .rodata
	; 0x022550F8
	.byte 0x18, 0x58, 0xB4, 0xCC, 0x68, 0xA8, 0xB4, 0xCC, 0xAD, 0x49, 0x25, 0x02, 0xF9, 0x49, 0x25, 0x02
	.byte 0x65, 0x4C, 0x25, 0x02, 0x07, 0x02, 0x02, 0x14, 0x13, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0E, 0x00
	.byte 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x0F, 0x00, 0x00, 0x03, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x80, 0x08, 0x00, 0x03, 0x00, 0x00, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDD, 0x4D, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x00, 0x00, 0xE1, 0x4E, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00
	.byte 0x29, 0x4F, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x41, 0x4F, 0x25, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x39, 0x50, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x05, 0x00, 0x00, 0x00, 0x51, 0x50, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.section .sinit
	.word MOD24_02254840
