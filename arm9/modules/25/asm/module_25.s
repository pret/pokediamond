	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD25_02254840
MOD25_02254840: ; 0x02254840
	ldr r3, _02254848 ; =MOD20_02252978
	ldr r0, _0225484C ; =MOD25_02254854
	ldr r1, _02254850 ; =MOD25_0225496C
	bx r3
	.align 2, 0
_02254848: .word MOD20_02252978
_0225484C: .word MOD25_02254854
_02254850: .word MOD25_0225496C
	thumb_func_end MOD25_02254840

	thumb_func_start MOD25_02254854
MOD25_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x2c
	add r7, r2, #0
	str r3, [sp]
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD25_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD25_02254930
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
_02254898: .word MOD25_02254930
	thumb_func_end MOD25_02254854

	thumb_func_start MOD25_0225489C
MOD25_0225489C: ; 0x0225489C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r1, r5, #0
	add r0, #0x24
	add r1, #0x14
	bl MOD25_02254A6C
	cmp r0, #0
	beq _0225490A
	mov r1, #0
	strb r1, [r5]
	strb r1, [r5, #1]
	strb r1, [r5, #2]
	mov r0, #1
	strb r0, [r5, #3]
	strb r1, [r5, #6]
	add r0, r5, #0
	str r1, [r5, #0x20]
	add r0, #0x14
	bl FUN_02012690
	ldr r0, [r5, #0x14]
	cmp r0, #0x18
	blo _022548D6
	mov r1, #0x18
	bl _u32_div_f
	str r1, [r5, #0x14]
_022548D6:
	ldr r0, [r5, #0x18]
	cmp r0, #0x3c
	blo _022548E6
	ldr r0, [r5, #0x14]
	mov r1, #0x3c
	bl _u32_div_f
	str r1, [r5, #0x14]
_022548E6:
	ldr r0, [r5, #0x18]
	ldr r2, _02254910 ; =MOD25_02254974
	strb r0, [r5, #5]
	mov r0, #8
	str r0, [sp]
	ldr r0, _02254914 ; =0x02254CF8
	mov r1, #1
	add r3, r5, #0
	bl MOD20_02254130
	str r0, [r5, #0x10]
	cmp r0, #0
	bne _02254904
	mov r0, #0
	pop {r3, r4, r5, pc}
_02254904:
	str r4, [r5, #0x28]
	mov r0, #1
	pop {r3, r4, r5, pc}
_0225490A:
	mov r0, #0
	pop {r3, r4, r5, pc}
	nop
_02254910: .word MOD25_02254974
_02254914: .word 0x02254CF8
	thumb_func_end MOD25_0225489C

	thumb_func_start MOD25_02254918
MOD25_02254918: ; 0x02254918
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x24]
	bl MOD25_02254AC4
	ldr r0, [r4, #0x10]
	bl MOD20_02254198
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}
	thumb_func_end MOD25_02254918

	thumb_func_start MOD25_02254930
MOD25_02254930: ; 0x02254930
	push {r3, r4, r5, lr}
	add r4, r1, #0
	add r5, r0, #0
	ldrb r0, [r4]
	cmp r0, #3
	bhs _02254966
	ldr r0, [r4, #0x28]
	ldr r1, [r4, #0x10]
	bl MOD20_02252C14
	ldrb r1, [r4]
	add r0, r4, #0
	lsl r2, r1, #2
	ldr r1, _02254968 ; =0x02254CFC
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254966
	add r0, r4, #0
	bl MOD25_02254918
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x28]
	bl MOD20_022529A0
_02254966:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254968: .word 0x02254CFC
	thumb_func_end MOD25_02254930

	thumb_func_start MOD25_0225496C
MOD25_0225496C: ; 0x0225496C
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD25_0225496C

	thumb_func_start MOD25_02254974
MOD25_02254974: ; 0x02254974
	cmp r2, #0
	beq _02254984
	cmp r2, #1
	bne _0225498C
	mov r0, #1
	str r0, [r3, #0x20]
	strb r0, [r3, #6]
	bx lr
_02254984:
	mov r0, #0
	str r0, [r3, #0x20]
	mov r0, #1
	strb r0, [r3, #6]
_0225498C:
	bx lr
	.align 2, 0
	thumb_func_end MOD25_02254974

	thumb_func_start MOD25_02254990
MOD25_02254990: ; 0x02254990
	ldrb r2, [r0, #2]
	cmp r2, #0
	bne _02254998
	b _0225499A
_02254998:
	mov r1, #2
_0225499A:
	strb r1, [r0]
	mov r1, #0
	strb r1, [r0, #1]
	bx lr
	.align 2, 0
	thumb_func_end MOD25_02254990

	thumb_func_start MOD25_022549A4
MOD25_022549A4: ; 0x022549A4
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _022549B4
	cmp r0, #1
	beq _022549C4
	b _022549DE
_022549B4:
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl MOD25_02254AE4
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549DE
_022549C4:
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl MOD25_02254B08
	cmp r0, #0
	beq _022549DE
	ldr r0, [r4, #0x28]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD25_02254990
_022549DE:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD25_022549A4

	thumb_func_start MOD25_022549E4
MOD25_022549E4: ; 0x022549E4
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _022549F8
	mov r1, #2
	bl MOD25_02254990
	mov r0, #0
	pop {r4, pc}
_022549F8:
	ldrb r0, [r4, #6]
	cmp r0, #0
	beq _02254A0A
	mov r0, #0
	strb r0, [r4, #6]
	ldr r0, [r4, #0x24]
	mov r1, #2
	bl MOD25_02254AE4
_02254A0A:
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl MOD25_02254B08
	cmp r0, #0
	beq _02254A32
	ldr r0, [r4, #0x18]
	strb r0, [r4, #5]
	add r0, r4, #0
	add r0, #0x14
	bl FUN_02012690
	ldrb r1, [r4, #5]
	ldr r0, [r4, #0x18]
	cmp r1, r0
	beq _02254A32
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl MOD25_02254AE4
_02254A32:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD25_022549E4

	thumb_func_start MOD25_02254A38
MOD25_02254A38: ; 0x02254A38
	push {r4, lr}
	add r4, r0, #0
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _02254A48
	cmp r0, #1
	beq _02254A58
	b _02254A66
_02254A48:
	ldr r0, [r4, #0x24]
	mov r1, #3
	bl MOD25_02254AE4
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A66
_02254A58:
	ldr r0, [r4, #0x24]
	bl MOD25_02254B14
	cmp r0, #0
	beq _02254A66
	mov r0, #1
	pop {r4, pc}
_02254A66:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD25_02254A38

	thumb_func_start MOD25_02254A6C
MOD25_02254A6C: ; 0x02254A6C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x54
	bl AllocFromHeap
	add r4, r0, #0
	beq _02254ABA
	add r0, #8
	mov r1, #8
	bl MOD20_022536F4
	str r6, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	bl MOD20_02252D24
	str r0, [r4, #0x48]
	add r0, r4, #0
	bl MOD25_02254C74
	cmp r0, #0
	bne _02254AA8
	add r0, r4, #0
	bl FreeToHeap
	mov r0, #0
	pop {r4, r5, r6, pc}
_02254AA8:
	ldr r0, _02254AC0 ; =MOD25_02254AE0
	add r1, r4, #0
	mov r2, #3
	bl FUN_0200CA44
	str r0, [r4, #0x30]
	str r4, [r5]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254ABA:
	mov r0, #0
	pop {r4, r5, r6, pc}
	nop
_02254AC0: .word MOD25_02254AE0
	thumb_func_end MOD25_02254A6C

	thumb_func_start MOD25_02254AC4
MOD25_02254AC4: ; 0x02254AC4
	push {r4, lr}
	add r4, r0, #0
	beq _02254ADE
	bl MOD25_02254CD8
	ldr r0, [r4, #0x30]
	cmp r0, #0
	beq _02254AD8
	bl FUN_0200CAB4
_02254AD8:
	add r0, r4, #0
	bl FreeToHeap
_02254ADE:
	pop {r4, pc}
	thumb_func_end MOD25_02254AC4

	thumb_func_start MOD25_02254AE0
MOD25_02254AE0: ; 0x02254AE0
	bx lr
	.align 2, 0
	thumb_func_end MOD25_02254AE0

	thumb_func_start MOD25_02254AE4
MOD25_02254AE4: ; 0x02254AE4
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254B04 ; =0x02254D44
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254B04: .word 0x02254D44
	thumb_func_end MOD25_02254AE4

	thumb_func_start MOD25_02254B08
MOD25_02254B08: ; 0x02254B08
	ldr r3, _02254B10 ; =MOD20_02253794
	add r0, #8
	bx r3
	nop
_02254B10: .word MOD20_02253794
	thumb_func_end MOD25_02254B08

	thumb_func_start MOD25_02254B14
MOD25_02254B14: ; 0x02254B14
	ldr r3, _02254B1C ; =MOD20_022537B8
	add r0, #8
	bx r3
	nop
_02254B1C: .word MOD20_022537B8
	thumb_func_end MOD25_02254B14

	thumb_func_start MOD25_02254B20
MOD25_02254B20: ; 0x02254B20
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD25_02254B20

	thumb_func_start MOD25_02254B34
MOD25_02254B34: ; 0x02254B34
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254BBC ; =0x02254D08
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
	mov r1, #0x17
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
	mov r1, #0x1a
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	add r0, r5, #0
	bl MOD25_02254C30
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r1, _02254BC0 ; =0x04001000
	ldr r0, _02254BC4 ; =0xFFFFE0FF
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
	bl MOD25_02254B20
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_02254BBC: .word 0x02254D08
_02254BC0: .word 0x04001000
_02254BC4: .word 0xFFFFE0FF
	thumb_func_end MOD25_02254B34

	thumb_func_start MOD25_02254BC8
MOD25_02254BC8: ; 0x02254BC8
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	bl MOD25_02254C30
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r5, #0
	bl MOD25_02254B20
	pop {r3, r4, r5, pc}
	thumb_func_end MOD25_02254BC8

	thumb_func_start MOD25_02254BE8
MOD25_02254BE8: ; 0x02254BE8
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	cmp r0, #0
	beq _02254C04
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252DB4
	b _02254C0C
_02254C04:
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
_02254C0C:
	add r0, r4, #0
	bl MOD25_02254B20
	pop {r4, pc}
	thumb_func_end MOD25_02254BE8

	thumb_func_start MOD25_02254C14
MOD25_02254C14: ; 0x02254C14
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	bl MOD25_02254B20
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD25_02254C14

	thumb_func_start MOD25_02254C30
MOD25_02254C30: ; 0x02254C30
	push {r3, r4, r5, lr}
	add r4, r0, #0
	ldr r0, [r4]
	ldr r1, _02254C70 ; =0x04000280
	ldr r0, [r0]
	mov r2, #0
	strh r2, [r1]
	str r0, [r1, #0x10]
	mov r0, #0xa
	add r1, #0x18
	str r0, [r1]
	str r2, [r1, #4]
	ldr r5, [r4]
	mov r1, #0xc
	ldr r0, [r5]
	bl _u32_div_f
	ldr r2, [r5, #4]
	ldr r0, [r4, #0x4c]
	lsr r3, r2, #1
	mov r2, #0x1e
	mul r2, r1
	add r2, #0x3c
	add r1, r3, r2
	bl MOD20_02253F28
	ldr r1, [r4]
	ldr r0, [r4, #0x50]
	ldr r1, [r1, #4]
	bl MOD20_02253F28
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254C70: .word 0x04000280
	thumb_func_end MOD25_02254C30

	thumb_func_start MOD25_02254C74
MOD25_02254C74: ; 0x02254C74
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
	mov r1, #0x1d
	bl FUN_02006A34
	mov r0, #8
	str r0, [sp]
	add r0, r7, #0
	add r0, #0x34
	mov r1, #0xc
	mov r2, #0x1b
	mov r3, #0x1c
	bl MOD20_02253FBC
	cmp r0, #0
	beq _02254CCE
	add r0, r7, #0
	str r0, [sp, #0xc]
	add r0, #0x34
	ldr r4, _02254CD4 ; =0x02254D24
	mov r6, #0
	add r5, r7, #0
	str r0, [sp, #0xc]
_02254CB2:
	ldr r0, [r7, #0x48]
	ldr r2, [sp, #0xc]
	add r1, r4, #0
	bl MOD20_02253E74
	str r0, [r5, #0x4c]
	add r6, r6, #1
	add r4, #0x10
	add r5, r5, #4
	cmp r6, #2
	blt _02254CB2
	add sp, #0x10
	mov r0, #1
	pop {r3, r4, r5, r6, r7, pc}
_02254CCE:
	mov r0, #0
	add sp, #0x10
	pop {r3, r4, r5, r6, r7, pc}
	.align 2, 0
_02254CD4: .word 0x02254D24
	thumb_func_end MOD25_02254C74

	thumb_func_start MOD25_02254CD8
MOD25_02254CD8: ; 0x02254CD8
	push {r4, r5, r6, lr}
	add r6, r0, #0
	add r0, #0x34
	bl MOD20_02254014
	mov r4, #0
	add r5, r6, #0
_02254CE6:
	ldr r0, [r6, #0x48]
	ldr r1, [r5, #0x4c]
	bl MOD20_02253F14
	add r4, r4, #1
	add r5, r5, #4
	cmp r4, #2
	blt _02254CE6
	pop {r4, r5, r6, pc}
	thumb_func_end MOD25_02254CD8

	.section .rodata
	; 0x02254CF8
	.byte 0x10, 0xAF, 0x10, 0xCF, 0xA5, 0x49, 0x25, 0x02, 0xE5, 0x49, 0x25, 0x02, 0x39, 0x4A, 0x25, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x01, 0x00, 0x0E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x07, 0x00
	.byte 0x00, 0x40, 0x06, 0x00, 0x3C, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x40, 0x07, 0x00
	.byte 0x00, 0x40, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x35, 0x4B, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xC9, 0x4B, 0x25, 0x02
	.byte 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xE9, 0x4B, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x00, 0x00, 0x00, 0x15, 0x4C, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

	.section .sinit
	.word MOD25_02254840
