	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD21_02254840
MOD21_02254840: ; 0x02254840
	ldr r3, _02254848 ; =MOD20_02252978
	ldr r0, _0225484C ; =MOD21_02254854
	ldr r1, _02254850 ; =MOD21_0225496C
	bx r3
	.align 2, 0
_02254848: .word MOD20_02252978
_0225484C: .word MOD21_02254854
_02254850: .word MOD21_0225496C
	thumb_func_end MOD21_02254840

	thumb_func_start MOD21_02254854
MOD21_02254854: ; 0x02254854
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	add r6, r1, #0
	mov r0, #8
	mov r1, #0x2c
	add r7, r2, #0
	str r3, [sp]
	bl FUN_02016998
	add r4, r0, #0
	beq _02254892
	ldr r3, [sp]
	add r1, r6, #0
	add r2, r7, #0
	bl MOD21_0225489C
	cmp r0, #0
	beq _0225488C
	ldr r0, _02254898 ; =MOD21_02254930
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
_02254898: .word MOD21_02254930
	thumb_func_end MOD21_02254854

	thumb_func_start MOD21_0225489C
MOD21_0225489C: ; 0x0225489C
	push {r3, r4, r5, lr}
	add r5, r0, #0
	add r4, r1, #0
	add r1, r5, #0
	add r0, #0x24
	add r1, #0x14
	bl MOD21_02254A6C
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
	ldr r2, _02254910 ; =MOD21_02254974
	strb r0, [r5, #5]
	mov r0, #8
	str r0, [sp]
	ldr r0, _02254914 ; =0x02254D80
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
_02254910: .word MOD21_02254974
_02254914: .word 0x02254D80
	thumb_func_end MOD21_0225489C

	thumb_func_start MOD21_02254918
MOD21_02254918: ; 0x02254918
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4, #0x24]
	bl MOD21_02254B04
	ldr r0, [r4, #0x10]
	bl MOD20_02254198
	add r0, r4, #0
	bl FUN_02016A18
	pop {r4, pc}
	thumb_func_end MOD21_02254918

	thumb_func_start MOD21_02254930
MOD21_02254930: ; 0x02254930
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
	ldr r1, _02254968 ; =0x02254D84
	ldr r1, [r1, r2]
	blx r1
	cmp r0, #0
	beq _02254966
	add r0, r4, #0
	bl MOD21_02254918
	add r0, r5, #0
	bl FUN_0200CAB4
	ldr r0, [r4, #0x28]
	bl MOD20_022529A0
_02254966:
	pop {r3, r4, r5, pc}
	.align 2, 0
_02254968: .word 0x02254D84
	thumb_func_end MOD21_02254930

	thumb_func_start MOD21_0225496C
MOD21_0225496C: ; 0x0225496C
	mov r1, #1
	strb r1, [r0, #2]
	bx lr
	.align 2, 0
	thumb_func_end MOD21_0225496C

	thumb_func_start MOD21_02254974
MOD21_02254974: ; 0x02254974
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
	thumb_func_end MOD21_02254974

	thumb_func_start MOD21_02254990
MOD21_02254990: ; 0x02254990
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
	thumb_func_end MOD21_02254990

	thumb_func_start MOD21_022549A4
MOD21_022549A4: ; 0x022549A4
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
	bl MOD21_02254B10
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _022549DE
_022549C4:
	ldr r0, [r4, #0x24]
	mov r1, #0
	bl MOD21_02254B34
	cmp r0, #0
	beq _022549DE
	ldr r0, [r4, #0x28]
	bl MOD20_0225298C
	add r0, r4, #0
	mov r1, #1
	bl MOD21_02254990
_022549DE:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD21_022549A4

	thumb_func_start MOD21_022549E4
MOD21_022549E4: ; 0x022549E4
	push {r4, lr}
	add r4, r0, #0
	ldrb r1, [r4, #2]
	cmp r1, #0
	beq _022549F8
	mov r1, #2
	bl MOD21_02254990
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
	bl MOD21_02254B10
_02254A0A:
	ldr r0, [r4, #0x24]
	mov r1, #1
	bl MOD21_02254B34
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
	bl MOD21_02254B10
_02254A32:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD21_022549E4

	thumb_func_start MOD21_02254A38
MOD21_02254A38: ; 0x02254A38
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
	bl MOD21_02254B10
	ldrb r0, [r4, #1]
	add r0, r0, #1
	strb r0, [r4, #1]
	b _02254A66
_02254A58:
	ldr r0, [r4, #0x24]
	bl MOD21_02254B40
	cmp r0, #0
	beq _02254A66
	mov r0, #1
	pop {r4, pc}
_02254A66:
	mov r0, #0
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD21_02254A38

	thumb_func_start MOD21_02254A6C
MOD21_02254A6C: ; 0x02254A6C
	push {r4, r5, r6, lr}
	sub sp, #8
	add r6, r1, #0
	mov r1, #3
	add r5, r0, #0
	mov r0, #8
	lsl r1, r1, #8
	bl FUN_02016998
	add r4, r0, #0
	beq _02254ACC
	add r0, #8
	mov r1, #8
	bl MOD20_022536F4
	str r6, [r4]
	bl MOD20_02252D34
	str r0, [r4, #4]
	mov r0, #8
	str r0, [sp]
	mov r0, #0xc
	mov r1, #0x19
	mov r2, #1
	add r3, sp, #4
	bl FUN_02006BDC
	add r6, r0, #0
	bne _02254AB2
	add r0, r4, #0
	bl FUN_02016A18
	add sp, #8
	mov r0, #0
	pop {r4, r5, r6, pc}
_02254AB2:
	ldr r0, [sp, #4]
	add r1, r4, #0
	add r0, #0xc
	add r1, #0x30
	bl MOD21_02254AD4
	add r0, r6, #0
	bl FUN_02016A18
	add sp, #8
	str r4, [r5]
	mov r0, #1
	pop {r4, r5, r6, pc}
_02254ACC:
	mov r0, #0
	add sp, #8
	pop {r4, r5, r6, pc}
	.align 2, 0
	thumb_func_end MOD21_02254A6C

	thumb_func_start MOD21_02254AD4
MOD21_02254AD4: ; 0x02254AD4
	push {r3, r4, r5, r6, r7, lr}
	mov r6, #9
	add r5, r0, #0
	add r4, r1, #0
	mov r7, #0
	lsl r6, r6, #6
_02254AE0:
	add r0, r5, #0
	add r1, r4, #0
	mov r2, #0x40
	bl MIi_CpuCopy16
	add r1, r4, #0
	add r0, r5, r6
	add r1, #0x40
	mov r2, #0x10
	bl MIi_CpuCopy16
	add r7, r7, #1
	add r5, #0x40
	add r4, #0x50
	sub r6, #0x30
	cmp r7, #9
	blt _02254AE0
	pop {r3, r4, r5, r6, r7, pc}
	thumb_func_end MOD21_02254AD4

	thumb_func_start MOD21_02254B04
MOD21_02254B04: ; 0x02254B04
	push {r3, lr}
	cmp r0, #0
	beq _02254B0E
	bl FUN_02016A18
_02254B0E:
	pop {r3, pc}
	thumb_func_end MOD21_02254B04

	thumb_func_start MOD21_02254B10
MOD21_02254B10: ; 0x02254B10
	push {lr}
	sub sp, #0xc
	add r2, r0, #0
	add r0, #8
	str r0, [sp]
	mov r0, #2
	str r0, [sp, #4]
	mov r0, #8
	str r0, [sp, #8]
	ldr r0, _02254B30 ; =0x02254DAC
	ldr r3, [r2]
	bl MOD20_022537E0
	add sp, #0xc
	pop {pc}
	nop
_02254B30: .word 0x02254DAC
	thumb_func_end MOD21_02254B10

	thumb_func_start MOD21_02254B34
MOD21_02254B34: ; 0x02254B34
	ldr r3, _02254B3C ; =0x02253795
	add r0, #8
	bx r3
	nop
_02254B3C: .word 0x02253795
	thumb_func_end MOD21_02254B34

	thumb_func_start MOD21_02254B40
MOD21_02254B40: ; 0x02254B40
	ldr r3, _02254B48 ; =0x022537B9
	add r0, #8
	bx r3
	nop
_02254B48: .word 0x022537B9
	thumb_func_end MOD21_02254B40

	thumb_func_start MOD21_02254B4C
MOD21_02254B4C: ; 0x02254B4C
	push {r4, lr}
	add r4, r0, #0
	bl MOD20_022538A0
	add r0, #8
	add r1, r4, #0
	bl MOD20_02253888
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD21_02254B4C

	thumb_func_start MOD21_02254B60
MOD21_02254B60: ; 0x02254B60
	push {r4, r5, lr}
	sub sp, #0x14
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	add r5, r0, #0
	ldr r0, [r5, #4]
	ldr r2, _02254BE8 ; =0x02254D90
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
	mov r1, #0x18
	mov r3, #6
	bl FUN_020068C8
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
	add r0, r5, #0
	bl MOD21_02254C5C
	ldr r0, [r5, #4]
	mov r1, #6
	bl FUN_02017CD0
	ldr r1, _02254BEC ; =0x04001000
	ldr r0, _02254BF0 ; =0xFFFFE0FF
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
	bl MOD21_02254B4C
	add sp, #0x14
	pop {r4, r5, pc}
	.align 2, 0
_02254BE8: .word 0x02254D90
_02254BEC: .word 0x04001000
_02254BF0: .word 0xFFFFE0FF
	thumb_func_end MOD21_02254B60

	thumb_func_start MOD21_02254BF4
MOD21_02254BF4: ; 0x02254BF4
	push {r3, r4, r5, lr}
	add r5, r1, #0
	add r0, r5, #0
	bl MOD20_022538A0
	add r4, r0, #0
	bl MOD21_02254C5C
	ldr r0, [r4, #4]
	mov r1, #6
	bl FUN_02017CD0
	add r0, r5, #0
	bl MOD21_02254B4C
	pop {r3, r4, r5, pc}
	thumb_func_end MOD21_02254BF4

	thumb_func_start MOD21_02254C14
MOD21_02254C14: ; 0x02254C14
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0]
	ldr r0, [r0, #0xc]
	cmp r0, #0
	beq _02254C30
	mov r0, #0
	add r1, r0, #0
	bl MOD11_02252DB4
	b _02254C38
_02254C30:
	mov r0, #0
	add r1, r0, #0
	bl MOD20_02252D7C
_02254C38:
	add r0, r4, #0
	bl MOD21_02254B4C
	pop {r4, pc}
	thumb_func_end MOD21_02254C14

	thumb_func_start MOD21_02254C40
MOD21_02254C40: ; 0x02254C40
	push {r4, lr}
	add r4, r1, #0
	add r0, r4, #0
	bl MOD20_022538A0
	ldr r0, [r0, #4]
	mov r1, #6
	bl FUN_020178A0
	add r0, r4, #0
	bl MOD21_02254B4C
	pop {r4, pc}
	.align 2, 0
	thumb_func_end MOD21_02254C40

	thumb_func_start MOD21_02254C5C
MOD21_02254C5C: ; 0x02254C5C
	push {r4, r5, lr}
	sub sp, #0x1c
	add r4, r0, #0
	ldr r0, [r4]
	ldr r2, _02254D74 ; =0x04000280
	ldr r0, [r0]
	mov r3, #0
	strh r3, [r2]
	str r0, [r2, #0x10]
	add r0, r2, #0
	mov r1, #0xa
	add r0, #0x18
	str r1, [r0]
	str r3, [r0, #4]
	lsr r0, r2, #0xb
_02254C7A:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254C7A
	ldr r0, _02254D78 ; =0x040002A0
	add r3, r0, #0
	ldr r1, [r0]
	sub r3, #0x20
	lsr r0, r0, #0xb
_02254C8A:
	ldrh r2, [r3]
	tst r2, r0
	bne _02254C8A
	ldr r0, _02254D7C ; =0x040002A8
	add r2, r4, #0
	ldr r5, [r0]
	mov r0, #4
	str r0, [sp]
	mov r0, #9
	lsl r1, r1, #0x1a
	str r0, [sp, #4]
	add r2, #0x30
	str r2, [sp, #8]
	lsr r1, r1, #0x18
	str r1, [sp, #0xc]
	mov r1, #0
	str r1, [sp, #0x10]
	mov r1, #0x28
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #3
	mov r3, #7
	bl FUN_02018170
	mov r0, #4
	str r0, [sp]
	mov r0, #9
	add r1, r4, #0
	str r0, [sp, #4]
	add r1, #0x30
	str r1, [sp, #8]
	lsl r1, r5, #0x1a
	lsr r1, r1, #0x18
	str r1, [sp, #0xc]
	mov r1, #0
	str r1, [sp, #0x10]
	mov r1, #0x28
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #8
	mov r3, #7
	bl FUN_02018170
	ldr r0, [r4]
	ldr r2, _02254D74 ; =0x04000280
	ldr r0, [r0, #4]
	mov r3, #0
	strh r3, [r2]
	str r0, [r2, #0x10]
	add r0, r2, #0
	mov r1, #0xa
	add r0, #0x18
	str r1, [r0]
	str r3, [r0, #4]
	lsr r0, r2, #0xb
_02254D00:
	ldrh r1, [r2]
	tst r1, r0
	bne _02254D00
	ldr r0, _02254D78 ; =0x040002A0
	add r3, r0, #0
	ldr r1, [r0]
	sub r3, #0x20
	lsr r0, r0, #0xb
_02254D10:
	ldrh r2, [r3]
	tst r2, r0
	bne _02254D10
	ldr r0, _02254D7C ; =0x040002A8
	add r2, r4, #0
	ldr r5, [r0]
	mov r0, #4
	str r0, [sp]
	mov r0, #9
	lsl r1, r1, #0x1a
	str r0, [sp, #4]
	add r2, #0x30
	str r2, [sp, #8]
	lsr r1, r1, #0x18
	str r1, [sp, #0xc]
	mov r1, #0
	str r1, [sp, #0x10]
	mov r1, #0x28
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #0xf
	mov r3, #7
	bl FUN_02018170
	mov r0, #4
	str r0, [sp]
	mov r0, #9
	add r1, r4, #0
	str r0, [sp, #4]
	add r1, #0x30
	str r1, [sp, #8]
	lsl r1, r5, #0x1a
	lsr r1, r1, #0x18
	str r1, [sp, #0xc]
	mov r1, #0
	str r1, [sp, #0x10]
	mov r1, #0x28
	str r1, [sp, #0x14]
	str r0, [sp, #0x18]
	ldr r0, [r4, #4]
	mov r1, #6
	mov r2, #0x14
	mov r3, #7
	bl FUN_02018170
	add sp, #0x1c
	pop {r4, r5, pc}
	nop
_02254D74: .word 0x04000280
_02254D78: .word 0x040002A0
_02254D7C: .word 0x040002A8
	thumb_func_end MOD21_02254C5C

	.section .rodata
	; 0x02254D80
	.incbin "baserom.nds", 0x285B40, 0x68

	; Dumb hack because the compiler aligns to 16 instead of 8
	;.section .sinit
	.global SDK_OVERLAY.MODULE_21.SINIT_START
    .global SDK_OVERLAY.MODULE_21.SINIT_END
SDK_OVERLAY.MODULE_21.SINIT_START:
	.word MOD21_02254840
	.word 0
SDK_OVERLAY.MODULE_21.SINIT_END:
