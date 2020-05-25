	.include "asm/macros.inc"
	.include "global.inc"

	.section .rodata

	.global UNK_020FF590
UNK_020FF590: ; 0x020FF590
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00

	.global UNK_020FF598
UNK_020FF598: ; 0x020FF598
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	.byte 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF

	.bss

	.global UNK_021CA86C
UNK_021CA86C: ; 0x021CA86C
	.space 0x4

	.global UNK_021CA870
UNK_021CA870: ; 0x021CA870
	.space 0x4

	.global UNK_021CA874
UNK_021CA874: ; 0x021CA874
	.space 0x8

	.global UNK_021CA87C
UNK_021CA87C: ; 0x021CA87C
	.space 0x20

	.global UNK_021CA89C
UNK_021CA89C: ; 0x021CA89C
	.space 0x4

	.global UNK_021CA8A0
UNK_021CA8A0: ; 0x021CA8A0
	.space 0x10

	.text

	arm_func_start FUN_020A5A4C
FUN_020A5A4C: ; 0x020A5A4C
	mov r1, r0
	mov r0, #0x0
	mov r3, #0x1
_020A5A58:
	clz r2, r1
	rsbs r2, r2, #0x1f
	bxcc lr
	bic r1, r1, r3, lsl r2
	add r0, r0, #0x1
	b _020A5A58

	arm_func_start FUN_020A5A70
FUN_020A5A70: ; 0x020A5A70
	clz r0, r0
	bx lr

	arm_func_start FUN_020A5A78
FUN_020A5A78: ; 0x020A5A78
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	bne _020A5D80
	ldr r2, _020A5DA8 ; =UNK_021CA86C
	mov r0, #0x0
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2000
	strb r0, [r1, #0x26b]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0x82]
	ldr r3, [r2, #0x0]
	add r1, r3, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0xd
	addls pc, pc, r1, lsl #0x2
	b _020A5D4C
_020A5AC4:
	b _020A5D4C
_020A5AC8:
	b _020A5D4C
_020A5ACC:
	b _020A5D4C
_020A5AD0:
	b _020A5D4C
_020A5AD4:
	b _020A5D4C
_020A5AD8:
	b _020A5AFC
_020A5ADC:
	b _020A5AFC
_020A5AE0:
	b _020A5B24
_020A5AE4:
	b _020A5B4C
_020A5AE8:
	b _020A5C74
_020A5AEC:
	b _020A5CA4
_020A5AF0:
	b _020A5D4C
_020A5AF4:
	b _020A5C74
_020A5AF8:
	b _020A5CD4
_020A5AFC:
	mov r0, #0x3
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A5DAC ; =0x000008F5
	mov r2, r1
	mov r0, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5B24:
	mov r0, #0x3
	bl FUN_020A6C38
	mov r0, #0x0
	ldr r3, _020A5DB0 ; =0x000008FB
	mov r1, r0
	mov r2, r0
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5B4C:
	add r1, r3, #0x2200
	ldrh r4, [r1, #0xf8]
	strh r0, [r1, #0xf8]
	cmp r4, #0x12
	bne _020A5C44
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2100
	ldrh r3, [r1, #0x70]
	and r12, r3, #0x24
	cmp r12, #0x24
	beq _020A5C44
	orr r3, r3, #0x24
	strh r3, [r1, #0x70]
	ldr r2, [r2, #0x0]
	add r1, r2, #0x2000
	ldr r3, [r1, #0x264]
	and r1, r3, #0xc0000
	cmp r1, #0xc0000
	moveq r0, #0x1
	mov r0, r0, lsl #0x10
	mov r12, r0, lsr #0x10
	and r1, r3, #0x30000
	cmp r1, #0x30000
	movne r3, #0x1
	add r1, r2, #0x2140
	ldr r0, _020A5DB4 ; =FUN_020A6144
	moveq r3, #0x0
	mov r2, #0x0
	str r12, [sp, #0x0]
	bl WM_StartConnectEx
	cmp r0, #0x2
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x3
	beq _020A5C14
	cmp r0, #0x8
	bne _020A5C14
	mov r0, #0xc
	bl FUN_020A6C38
	ldr r0, _020A5DA8 ; =UNK_021CA86C
	ldr r3, _020A5DB8 ; =0x0000091C
	ldr r0, [r0, #0x0]
	mov r2, r4
	add r1, r0, #0x2140
	mov r0, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5C14:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A5DA8 ; =UNK_021CA86C
	ldr r3, _020A5DBC ; =0x00000925
	ldr r0, [r0, #0x0]
	mov r2, r4
	add r1, r0, #0x2140
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5C44:
	mov r0, #0x3
	bl FUN_020A6C38
	ldr r0, _020A5DA8 ; =UNK_021CA86C
	ldr r3, _020A5DC0 ; =0x0000092D
	ldr r0, [r0, #0x0]
	mov r2, r4
	add r1, r0, #0x2140
	mov r0, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5C74:
	mov r0, #0x3
	bl FUN_020A6C38
	ldr r0, _020A5DA8 ; =UNK_021CA86C
	ldr r3, _020A5DC4 ; =0x00000935
	ldr r1, [r0, #0x0]
	mov r0, #0x0
	add r1, r1, #0x2140
	mov r2, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5CA4:
	mov r0, #0x3
	bl FUN_020A6C38
	ldr r1, _020A5DA8 ; =UNK_021CA86C
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r3, _020A5DC8 ; =0x0000093C
	mov r2, r0
	add r1, r1, #0x2140
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5CD4:
	ldr r0, _020A5DCC ; =FUN_020A6768
	bl WM_PowerOff
	cmp r0, #0x2
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x3
	beq _020A5D24
	cmp r0, #0x8
	bne _020A5D24
	mov r0, #0xc
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A5DD0 ; =0x0000094A
	mov r2, r1
	mov r0, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5D24:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A5DD4 ; =0x00000953
	mov r2, r1
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5D4C:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A5DA8 ; =UNK_021CA86C
	ldr r3, _020A5DD8 ; =0x00000959
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2000
	ldr r2, [r1, #0x260]
	mov r1, #0x0
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
_020A5D80:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r1, #0x0
	mov r2, r1
	mov r0, #0x7
	mov r3, #0x960
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A5DA8: .word UNK_021CA86C
_020A5DAC: .word 0x000008F5
_020A5DB0: .word 0x000008FB
_020A5DB4: .word FUN_020A6144
_020A5DB8: .word 0x0000091C
_020A5DBC: .word 0x00000925
_020A5DC0: .word 0x0000092D
_020A5DC4: .word 0x00000935
_020A5DC8: .word 0x0000093C
_020A5DCC: .word FUN_020A6768
_020A5DD0: .word 0x0000094A
_020A5DD4: .word 0x00000953
_020A5DD8: .word 0x00000959

	arm_func_start FUN_020A5DDC
FUN_020A5DDC: ; 0x020A5DDC
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r0, [r0, #0x2]
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A5EF4
_020A5DF4:
	b _020A5E08
_020A5DF8:
	b _020A5EDC
_020A5DFC:
	b _020A5EF4
_020A5E00:
	b _020A5EDC
_020A5E04:
	b _020A5EF4
_020A5E08:
	ldr r0, _020A5F24 ; =UNK_021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0xc
	bne _020A5E38
	mov r0, #0xa
	bl FUN_020A6C38
	bl FUN_020A6B28
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5E38:
	ldr r0, _020A5F28 ; =FUN_020A6058
	mov r1, #0x0
	bl WM_Disconnect
	cmp r0, #0x2
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	cmp r0, #0x3
	beq _020A5E94
	cmp r0, #0x8
	bne _020A5EAC
	mov r0, #0xc
	bl FUN_020A6C38
	ldr r0, _020A5F24 ; =UNK_021CA86C
	ldr r3, _020A5F2C ; =0x000008B4
	ldr r1, [r0, #0x0]
	mov r0, #0x1
	add r1, r1, #0x2140
	mov r2, #0x0
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5E94:
	mov r0, #0xa
	bl FUN_020A6C38
	bl FUN_020A6B28
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5EAC:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r1, _020A5F24 ; =UNK_021CA86C
	mov r0, #0x7
	ldr r1, [r1, #0x0]
	mov r2, #0x0
	add r1, r1, #0x2140
	mov r3, #0x8c0
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5EDC:
	mov r0, #0xa
	bl FUN_020A6C38
	bl FUN_020A6B28
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A5EF4:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A5F24 ; =UNK_021CA86C
	ldr r3, _020A5F30 ; =0x000008D3
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A5F24: .word UNK_021CA86C
_020A5F28: .word FUN_020A6058
_020A5F2C: .word 0x000008B4
_020A5F30: .word 0x000008D3

	arm_func_start FUN_020A5F34
FUN_020A5F34: ; 0x020A5F34
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrh r0, [r4, #0x2]
	cmp r0, #0x0
	beq _020A5F50
	cmp r0, #0x4
	b _020A601C
_020A5F50:
	ldrh r0, [r4, #0x4]
	cmp r0, #0xe
	beq _020A5F68
	cmp r0, #0xf
	beq _020A5FC0
	b _020A5FF0
_020A5F68:
	ldr r0, _020A6048 ; =UNK_021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0xc
	bne _020A5F94
	mov r0, #0x8
	bl FUN_020A6C38
	bl FUN_020A6B28
	ldmia sp!, {r4,lr}
	bx lr
_020A5F94:
	mov r0, #0x9
	bl FUN_020A6C38
	ldr r1, _020A6048 ; =UNK_021CA86C
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r3, _020A604C ; =0x00000872
	mov r2, r0
	add r1, r1, #0x2140
	bl FUN_020A6D3C
	ldmia sp!, {r4,lr}
	bx lr
_020A5FC0:
	ldr r0, [r4, #0x8]
	ldrh r0, [r0, #0xe]
	mov r0, r0, asr #0x8
	and r0, r0, #0xff
	bl FUN_020A89D0
	ldr r0, [r4, #0x8]
	mov r1, #0x620
	bl DC_InvalidateRange
	ldr r0, [r4, #0x8]
	bl FUN_020A8934
	ldmia sp!, {r4,lr}
	bx lr
_020A5FF0:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A6048 ; =UNK_021CA86C
	ldrh r2, [r4, #0x4]
	ldr r0, [r0, #0x0]
	ldr r3, _020A6050 ; =0x00000881
	add r1, r0, #0x2140
	mov r0, #0x7
	bl FUN_020A6D3C
	ldmia sp!, {r4,lr}
	bx lr
_020A601C:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A6048 ; =UNK_021CA86C
	ldr r3, _020A6054 ; =0x0000088C
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl FUN_020A6D3C
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A6048: .word UNK_021CA86C
_020A604C: .word 0x00000872
_020A6050: .word 0x00000881
_020A6054: .word 0x0000088C

	arm_func_start FUN_020A6058
FUN_020A6058: ; 0x020A6058
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r0, [r0, #0x2]
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A6108
_020A6070:
	b _020A6084
_020A6074:
	b _020A60F0
_020A6078:
	b _020A6108
_020A607C:
	b _020A60F0
_020A6080:
	b _020A6108
_020A6084:
	ldr r0, _020A6138 ; =UNK_021CA86C
	ldr r1, [r0, #0x0]
	add r0, r1, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0xc
	bne _020A60B4
	mov r0, #0xa
	bl FUN_020A6C38
	bl FUN_020A6B28
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A60B4:
	add r1, r1, #0x2200
	mov r2, #0x0
	mov r0, #0x3
	strh r2, [r1, #0x82]
	bl FUN_020A6C38
	ldr r1, _020A6138 ; =UNK_021CA86C
	mov r0, #0x0
	ldr r1, [r1, #0x0]
	ldr r3, _020A613C ; =0x0000083D
	mov r2, r0
	add r1, r1, #0x2140
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A60F0:
	mov r0, #0xa
	bl FUN_020A6C38
	bl FUN_020A6B28
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6108:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A6138 ; =UNK_021CA86C
	ldr r3, _020A6140 ; =0x0000084F
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6138: .word UNK_021CA86C
_020A613C: .word 0x0000083D
_020A6140: .word 0x0000084F

	arm_func_start FUN_020A6144
FUN_020A6144: ; 0x020A6144
	stmdb sp!, {r4,lr}
	mov r4, r0
	ldrh r0, [r4, #0x2]
	cmp r0, #0xc
	addls pc, pc, r0, lsl #0x2
	b _020A638C
_020A615C:
	b _020A6190
_020A6160:
	b _020A6364
_020A6164:
	b _020A638C
_020A6168:
	b _020A638C
_020A616C:
	b _020A638C
_020A6170:
	b _020A638C
_020A6174:
	b _020A6378
_020A6178:
	b _020A638C
_020A617C:
	b _020A638C
_020A6180:
	b _020A638C
_020A6184:
	b _020A638C
_020A6188:
	b _020A6378
_020A618C:
	b _020A6378
_020A6190:
	ldrh r0, [r4, #0x8]
	cmp r0, #0x9
	bgt _020A61D0
	cmp r0, #0x0
	addge pc, pc, r0, lsl #0x2
	b _020A6338
	b _020A6338
	b _020A6338
	b _020A6338
	b _020A6338
	b _020A6338
	b _020A6338
	b _020A63B0
	b _020A6258
	b _020A61E0
	b _020A61E0
_020A61D0:
	cmp r0, #0x1a
	ldmeqia sp!, {r4,lr}
	bxeq lr
	b _020A6338
_020A61E0:
	ldr r1, _020A63B8 ; =UNK_021CA86C
	ldr r2, [r1, #0x0]
	add r0, r2, #0x2000
	ldr r0, [r0, #0x260]
	sub r0, r0, #0x8
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A63B0
_020A6200:
	b _020A6220
_020A6204:
	b _020A6230
_020A6208:
	b _020A6214
_020A620C:
	b _020A63B0
_020A6210:
	b _020A624C
_020A6214:
	add r0, r2, #0x2200
	mov r1, #0x0
	strh r1, [r0, #0x82]
_020A6220:
	mov r0, #0xc
	bl FUN_020A6C38
	ldmia sp!, {r4,lr}
	bx lr
_020A6230:
	add r0, r2, #0x2200
	mov r2, #0x0
	strh r2, [r0, #0x82]
	ldr r0, [r1, #0x0]
	mov r1, #0x6
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
_020A624C:
	bl FUN_020A6B28
	ldmia sp!, {r4,lr}
	bx lr
_020A6258:
	ldr r1, _020A63B8 ; =UNK_021CA86C
	ldr r3, [r1, #0x0]
	add r0, r3, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0xc
	bne _020A6284
	mov r0, #0x8
	bl FUN_020A6C38
	bl FUN_020A6B28
	ldmia sp!, {r4,lr}
	bx lr
_020A6284:
	ldrh r2, [r4, #0xa]
	cmp r2, #0x1
	blo _020A632C
	ldr r0, _020A63BC ; =0x000007D7
	cmp r2, r0
	bhi _020A632C
	add r0, r3, #0x2200
	strh r2, [r0, #0x82]
	ldr r1, [r1, #0x0]
	ldr r0, _020A63C0 ; =FUN_020A5F34
	add r1, r1, #0x1500
	mov r2, #0x620
	bl WM_StartDCF
	cmp r0, #0x2
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x3
	beq _020A6300
	cmp r0, #0x8
	bne _020A6300
	mov r0, #0xc
	bl FUN_020A6C38
	ldr r0, _020A63B8 ; =UNK_021CA86C
	ldr r3, _020A63C4 ; =0x000007ED
	ldr r1, [r0, #0x0]
	mov r0, #0x1
	add r1, r1, #0x2140
	mov r2, #0x0
	bl FUN_020A6D3C
	ldmia sp!, {r4,lr}
	bx lr
_020A6300:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A63B8 ; =UNK_021CA86C
	ldr r3, _020A63C8 ; =0x000007F6
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl FUN_020A6D3C
	ldmia sp!, {r4,lr}
	bx lr
_020A632C:
	bl FUN_020A6B28
	ldmia sp!, {r4,lr}
	bx lr
_020A6338:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A63B8 ; =UNK_021CA86C
	ldrh r2, [r4, #0x8]
	ldr r0, [r0, #0x0]
	ldr r3, _020A63CC ; =0x00000804
	add r1, r0, #0x2140
	mov r0, #0x7
	bl FUN_020A6D3C
	ldmia sp!, {r4,lr}
	bx lr
_020A6364:
	ldr r0, _020A63B8 ; =UNK_021CA86C
	ldrh r1, [r4, #0xe]
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0xf8]
_020A6378:
	mov r0, #0x8
	bl FUN_020A6C38
	bl FUN_020A6B28
	ldmia sp!, {r4,lr}
	bx lr
_020A638C:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A63B8 ; =UNK_021CA86C
	ldr r3, _020A63D0 ; =0x0000081B
	ldr r1, [r0, #0x0]
	mov r0, #0x7
	add r1, r1, #0x2140
	mov r2, #0x0
	bl FUN_020A6D3C
_020A63B0:
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A63B8: .word UNK_021CA86C
_020A63BC: .word 0x000007D7
_020A63C0: .word FUN_020A5F34
_020A63C4: .word 0x000007ED
_020A63C8: .word 0x000007F6
_020A63CC: .word 0x00000804
_020A63D0: .word 0x0000081B

	arm_func_start FUN_020A63D4
FUN_020A63D4: ; 0x020A63D4
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r0, [r0, #0x2]
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A6438
_020A63EC:
	b _020A6400
_020A63F0:
	b _020A6428
_020A63F4:
	b _020A6438
_020A63F8:
	b _020A6438
_020A63FC:
	b _020A6438
_020A6400:
	mov r0, #0x3
	bl FUN_020A6C38
	mov r0, #0x0
	ldr r3, _020A6460 ; =0x00000783
	mov r1, r0
	mov r2, r0
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6428:
	bl FUN_020A6B28
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6438:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A6464 ; =0x00000793
	mov r2, r1
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6460: .word 0x00000783
_020A6464: .word 0x00000793

	arm_func_start FUN_020A6468
FUN_020A6468: ; 0x020A6468
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x8
	mov r5, r0
	ldrh r0, [r5, #0x2]
	mov r4, #0x14
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A6714
_020A6488:
	b _020A649C
_020A648C:
	b _020A6704
_020A6490:
	b _020A6714
_020A6494:
	b _020A6714
_020A6498:
	b _020A6714
_020A649C:
	ldr r0, _020A673C ; =UNK_021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x5
	bne _020A64D0
	mov r0, #0x6
	bl FUN_020A6C38
	mov r0, #0x0
	ldr r3, _020A6740 ; =0x00000704
	mov r1, r0
	mov r2, r0
	bl FUN_020A6D3C
_020A64D0:
	ldr r1, _020A673C ; =UNK_021CA86C
	ldr r2, [r1, #0x0]
	add r0, r2, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x6
	beq _020A64FC
	cmp r0, #0x7
	beq _020A6674
	cmp r0, #0xd
	beq _020A6684
	b _020A6694
_020A64FC:
	add r0, r2, #0x2200
	mov r2, #0x7
	strh r2, [r0, #0x80]
	ldrh r0, [r5, #0x8]
	cmp r0, #0x5
	bne _020A6588
	ldr r0, [r1, #0x0]
	add r1, r0, #0x2200
	add r0, r0, #0x2000
	ldrh r1, [r1, #0x8c]
	ldr r0, [r0, #0x288]
	bl DC_InvalidateRange
	ldrh r0, [r5, #0xe]
	mov r4, #0x0
	cmp r0, #0x0
	ble _020A6588
	ldr r8, _020A6744 ; =0x0000071A
	mov r6, r4
	mov r7, #0x7
_020A6548:
	add r0, r5, r4, lsl #0x1
	add r2, r5, r4, lsl #0x2
	ldrh r1, [r0, #0x50]
	ldr r0, [r2, #0x10]
	bl FUN_020A8298
	str r8, [sp, #0x0]
	add r0, r5, r4, lsl #0x2
	ldr r2, [r0, #0x10]
	mov r0, r7
	mov r1, r6
	mov r3, r5
	bl FUN_020A6CE0
	ldrh r0, [r5, #0xe]
	add r4, r4, #0x1
	cmp r4, r0
	blt _020A6548
_020A6588:
	ldr r0, _020A673C ; =UNK_021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r1, [r0, #0x264]
	and r0, r1, #0xc00000
	cmp r0, #0xc00000
	bne _020A65F4
	ldr r0, _020A6748 ; =0x00003FFE
	and r0, r1, r0
	bl FUN_020A5A4C
	movs r1, r0
	beq _020A65F4
	ldr r0, _020A673C ; =UNK_021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r6, [r0, #0x284]
	mov r0, r6
	bl _u32_div_f
	cmp r1, #0x0
	bne _020A65F4
	ldr r4, _020A674C ; =0x00000728
	mov r1, #0x0
	mov r2, r6
	mov r3, r1
	mov r0, #0x8
	str r4, [sp, #0x0]
	bl FUN_020A6CE0
_020A65F4:
	ldrh r0, [r5, #0xa]
	bl FUN_020A5A70
	rsb r0, r0, #0x20
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bl FUN_020A6D8C
	ldr r1, _020A673C ; =UNK_021CA86C
	mov r2, #0x1
	mov r2, r2, lsl r0
	ldr r0, [r1, #0x0]
	mov r2, r2, asr #0x1
	add r0, r0, #0x2200
	strh r2, [r0, #0x8e]
	ldr r0, [r1, #0x0]
	add r1, r0, #0x2200
	add r0, r0, #0x2000
	ldrh r1, [r1, #0x8c]
	ldr r0, [r0, #0x288]
	bl DC_InvalidateRange
	ldr r3, _020A673C ; =UNK_021CA86C
	ldr r2, _020A6750 ; =0x00002288
	ldr r1, [r3, #0x0]
	ldr r0, _020A6754 ; =FUN_020A6468
	add r1, r1, #0x2000
	ldr r4, [r1, #0x284]
	add r4, r4, #0x1
	str r4, [r1, #0x284]
	ldr r1, [r3, #0x0]
	add r1, r1, r2
	bl WM_StartScanEx
	mov r4, r0
	b _020A6694
_020A6674:
	ldr r0, _020A6758 ; =FUN_020A63D4
	bl WM_EndScan
	mov r4, r0
	b _020A6694
_020A6684:
	bl FUN_020A6B28
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A6694:
	cmp r4, #0x2
	addeq sp, sp, #0x8
	ldmeqia sp!, {r4-r8,lr}
	bxeq lr
	cmp r4, #0x3
	beq _020A66DC
	cmp r4, #0x8
	bne _020A66DC
	mov r0, #0xc
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A675C ; =0x00000753
	mov r2, r1
	mov r0, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A66DC:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A6760 ; =0x0000075C
	mov r2, r1
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A6704:
	bl FUN_020A6B28
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A6714:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A6764 ; =0x0000076D
	mov r2, r1
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x8
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A673C: .word UNK_021CA86C
_020A6740: .word 0x00000704
_020A6744: .word 0x0000071A
_020A6748: .word 0x00003FFE
_020A674C: .word 0x00000728
_020A6750: .word 0x00002288
_020A6754: .word FUN_020A6468
_020A6758: .word FUN_020A63D4
_020A675C: .word 0x00000753
_020A6760: .word 0x0000075C
_020A6764: .word 0x0000076D

	arm_func_start FUN_020A6768
FUN_020A6768: ; 0x020A6768
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r1, [r0, #0x2]
	mov r2, #0x14
	cmp r1, #0x4
	addls pc, pc, r1, lsl #0x2
	b _020A6A0C
_020A6784:
	b _020A6798
_020A6788:
	b _020A69CC
_020A678C:
	b _020A6A0C
_020A6790:
	b _020A6A0C
_020A6794:
	b _020A6A0C
_020A6798:
	ldrh r0, [r0, #0x0]
	cmp r0, #0x19
	bgt _020A67D4
	cmp r0, #0x19
	bge _020A68B4
	cmp r0, #0x6
	addls pc, pc, r0, lsl #0x2
	b _020A692C
_020A67B8:
	b _020A692C
_020A67BC:
	b _020A692C
_020A67C0:
	b _020A692C
_020A67C4:
	b _020A67F4
_020A67C8:
	b _020A6804
_020A67CC:
	b _020A6868
_020A67D0:
	b _020A6890
_020A67D4:
	cmp r0, #0x1d
	bgt _020A67E8
	cmp r0, #0x1d
	beq _020A68A0
	b _020A692C
_020A67E8:
	cmp r0, #0x27
	beq _020A68DC
	b _020A692C
_020A67F4:
	ldr r0, _020A6A4C ; =FUN_020A6768
	bl WM_PowerOn
	mov r2, r0
	b _020A692C
_020A6804:
	bl WM_Finish
	cmp r0, #0x0
	beq _020A6818
	cmp r0, #0x4
	b _020A6840
_020A6818:
	mov r0, #0x1
	bl FUN_020A6C38
	mov r0, #0x0
	ldr r3, _020A6A50 ; =0x00000663
	mov r1, r0
	mov r2, r0
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6840:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r1, #0x0
	ldr r3, _020A6A54 ; =0x0000066C
	mov r2, r1
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6868:
	mov r0, #0x3
	bl FUN_020A6C38
	mov r0, #0x0
	ldr r3, _020A6A58 ; =0x00000673
	mov r1, r0
	mov r2, r0
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6890:
	ldr r0, _020A6A4C ; =FUN_020A6768
	bl WM_Disable
	mov r2, r0
	b _020A692C
_020A68A0:
	ldr r0, _020A6A4C ; =FUN_020A6768
	mov r1, #0x0
	bl WM_SetBeaconIndication
	mov r2, r0
	b _020A692C
_020A68B4:
	ldr r1, _020A6A5C ; =UNK_021CA86C
	ldr r0, _020A6A4C ; =FUN_020A6768
	ldr r3, [r1, #0x0]
	add r2, r3, #0x2000
	ldrb r1, [r2, #0x250]
	ldrb r2, [r2, #0x251]
	add r3, r3, #0x2200
	bl WM_SetWEPKeyEx
	mov r2, r0
	b _020A692C
_020A68DC:
	ldr r0, _020A6A5C ; =UNK_021CA86C
	ldr r2, [r0, #0x0]
	add r0, r2, #0x2000
	ldr r1, [r0, #0x264]
	and r0, r1, #0xc0000
	cmp r0, #0xc0000
	moveq r0, #0x1
	movne r0, #0x0
	mov r0, r0, lsl #0x10
	mov r12, r0, lsr #0x10
	and r1, r1, #0x30000
	cmp r1, #0x30000
	movne r3, #0x1
	add r1, r2, #0x2140
	ldr r0, _020A6A60 ; =FUN_020A6144
	moveq r3, #0x0
	mov r2, #0x0
	str r12, [sp, #0x0]
	bl WM_StartConnectEx
	mov r2, r0
_020A692C:
	cmp r2, #0x2
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	cmp r2, #0x3
	beq _020A698C
	cmp r2, #0x8
	bne _020A698C
	mov r0, #0xc
	bl FUN_020A6C38
	ldr r0, _020A6A5C ; =UNK_021CA86C
	ldr r3, _020A6A64 ; =0x000006AF
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	add r0, r1, #0x2200
	ldrsh r0, [r0, #0x80]
	cmp r0, #0x5
	addeq r1, r1, #0x2140
	movne r1, #0x0
	mov r0, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A698C:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A6A5C ; =UNK_021CA86C
	ldr r3, _020A6A68 ; =0x000006B8
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	add r0, r1, #0x2200
	ldrsh r0, [r0, #0x80]
	cmp r0, #0x5
	addeq r1, r1, #0x2140
	movne r1, #0x0
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A69CC:
	mov r0, #0xc
	bl FUN_020A6C38
	ldr r0, _020A6A5C ; =UNK_021CA86C
	ldr r3, _020A6A6C ; =0x000006DE
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	add r0, r1, #0x2200
	ldrsh r0, [r0, #0x80]
	cmp r0, #0x5
	addeq r1, r1, #0x2140
	movne r1, #0x0
	mov r0, #0x1
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6A0C:
	mov r0, #0xb
	bl FUN_020A6C38
	ldr r0, _020A6A5C ; =UNK_021CA86C
	ldr r3, _020A6A70 ; =0x000006E8
	ldr r1, [r0, #0x0]
	mov r2, #0x0
	add r0, r1, #0x2200
	ldrsh r0, [r0, #0x80]
	cmp r0, #0x5
	addeq r1, r1, #0x2140
	movne r1, #0x0
	mov r0, #0x7
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6A4C: .word FUN_020A6768
_020A6A50: .word 0x00000663
_020A6A54: .word 0x0000066C
_020A6A58: .word 0x00000673
_020A6A5C: .word UNK_021CA86C
_020A6A60: .word FUN_020A6144
_020A6A64: .word 0x000006AF
_020A6A68: .word 0x000006B8
_020A6A6C: .word 0x000006DE
_020A6A70: .word 0x000006E8

	arm_func_start FUN_020A6A74
FUN_020A6A74: ; 0x020A6A74
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r1, [r0, #0x2]
	cmp r1, #0x8
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldrh r1, [r0, #0x4]
	cmp r1, #0x16
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldrh r0, [r0, #0x6]
	cmp r0, #0x25
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020A6B24 ; =UNK_021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	sub r0, r0, #0x8
	cmp r0, #0x4
	addls pc, pc, r0, lsl #0x2
	b _020A6B18
_020A6AD8:
	b _020A6AEC
_020A6ADC:
	b _020A6B00
_020A6AE0:
	b _020A6B10
_020A6AE4:
	b _020A6B18
_020A6AE8:
	b _020A6B00
_020A6AEC:
	mov r0, #0xc
	bl FUN_020A6C38
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6B00:
	bl FUN_020A6B28
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A6B10:
	mov r0, #0xc
	bl FUN_020A6C38
_020A6B18:
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6B24: .word UNK_021CA86C

	arm_func_start FUN_020A6B28
FUN_020A6B28: ; 0x020A6B28
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r0, _020A6B98 ; =UNK_021CA86C
	ldr r0, [r0, #0x0]
	add r1, r0, #0x2000
	ldrb r0, [r1, #0x26b]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020A6B9C ; =FUN_020A5A78
	mov r2, #0x1
	strb r2, [r1, #0x26b]
	bl WM_Reset
	cmp r0, #0x2
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	mov r0, #0xb
	bl FUN_020A6C38
	mov r1, #0x0
	mov r2, r1
	mov r0, #0x7
	mov r3, #0x610
	bl FUN_020A6D3C
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6B98: .word UNK_021CA86C
_020A6B9C: .word FUN_020A5A78

	arm_func_start FUN_020A6BA0
FUN_020A6BA0: ; 0x020A6BA0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020A88A8
	bl FUN_020A6BBC
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020A6BBC
FUN_020A6BBC: ; 0x020A6BBC
	stmdb sp!, {r4,lr}
	sub sp, sp, #0x8
	bl OS_DisableInterrupts
	ldr r2, _020A6C28 ; =UNK_021CA86C
	ldr r1, _020A6C2C ; =0x000022CC
	ldr r2, [r2, #0x0]
	mov r4, r0
	add r0, r2, r1
	bl OS_CancelAlarm
	ldr r0, _020A6C28 ; =UNK_021CA86C
	ldr r12, [r0, #0x0]
	add r0, r12, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x9
	bne _020A6C14
	ldr r0, _020A6C2C ; =0x000022CC
	ldr r1, _020A6C30 ; =0x022F5341
	mov r2, #0x0
	ldr r3, _020A6C34 ; =FUN_020A6BA0
	add r0, r12, r0
	str r2, [sp, #0x0]
	bl OS_SetAlarm
_020A6C14:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x8
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A6C28: .word UNK_021CA86C
_020A6C2C: .word 0x000022CC
_020A6C30: .word 0x022F5341
_020A6C34: .word FUN_020A6BA0

	arm_func_start FUN_020A6C38
FUN_020A6C38:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020A6CD0 ; =UNK_021CA86C
	mov r4, r0
	ldr r1, [r1, #0x0]
	add r0, r1, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x9
	bne _020A6C78
	cmp r5, #0x9
	beq _020A6C78
	ldr r0, _020A6CD4 ; =0x000022CC
	add r0, r1, r0
	bl OS_CancelAlarm
_020A6C78:
	ldr r0, _020A6CD0 ; =UNK_021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	ldr r1, [r0, #0x260]
	cmp r1, #0xb
	strne r5, [r0, #0x260]
	cmp r5, #0x9
	bne _020A6CBC
	mov r2, #0x0
	ldr r0, _020A6CD0 ; =UNK_021CA86C
	str r2, [sp, #0x0]
	ldr r5, [r0, #0x0]
	ldr r0, _020A6CD4 ; =0x000022CC
	ldr r1, _020A6CD8 ; =0x022F5341
	ldr r3, _020A6CDC ; =FUN_020A6BA0
	add r0, r5, r0
	bl OS_SetAlarm
_020A6CBC:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A6CD0: .word UNK_021CA86C
_020A6CD4: .word 0x000022CC
_020A6CD8: .word 0x022F5341
_020A6CDC: .word FUN_020A6BA0

	arm_func_start FUN_020A6CE0
FUN_020A6CE0: ; 0x020A6CE0
	stmdb sp!, {lr}
	sub sp, sp, #0x14
	ldr ip, _020A6D38 ; =UNK_021CA86C
	ldr r12, [r12, #0x0]
	add r12, r12, #0x2000
	ldr lr, [r12, #0x27c]
	cmp lr, #0x0
	addeq sp, sp, #0x14
	ldmeqia sp!, {lr}
	bxeq lr
	ldr lr, [sp, #0x18]
	strh r0, [sp, #0x0]
	str r2, [sp, #0x4]
	str r3, [sp, #0x8]
	str lr, [sp, #0xc]
	strh r1, [sp, #0x2]
	ldr r1, [r12, #0x27c]
	add r0, sp, #0x0
	blx r1
	add sp, sp, #0x14
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A6D38: .word UNK_021CA86C

	arm_func_start FUN_020A6D3C
FUN_020A6D3C: ; 0x020A6D3C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr ip, _020A6D88 ; =UNK_021CA86C
	mov r5, r0
	ldr r0, [r12, #0x0]
	mov r4, r1
	add r1, r0, #0x2200
	ldrsh r0, [r1, #0x80]
	mov r12, #0x0
	mov lr, r2
	strh r12, [r1, #0x80]
	str r3, [sp, #0x0]
	mov r1, r5
	mov r2, r4
	mov r3, lr
	bl FUN_020A6CE0
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A6D88: .word UNK_021CA86C

	arm_func_start FUN_020A6D8C
FUN_020A6D8C: ; 0x020A6D8C
	stmdb sp!, {r4-r6,lr}
	ldr r1, _020A6E24 ; =UNK_021CA86C
	mov r2, r0
	ldr r1, [r1, #0x0]
	mov r3, #0x0
	add r1, r1, #0x2000
	ldr r1, [r1, #0x264]
	mov r6, #0x1
	ldr r5, _020A6E28 ; =0x4EC4EC4F
	ldr r4, _020A6E2C ; =0x0000000D
_020A6DB4:
	smull r12, lr, r5, r2
	mov lr, lr, asr #0x2
	mov r12, r2, lsr #0x1f
	add lr, r12, lr
	smull r12, lr, r4, lr
	sub lr, r2, r12
	add r12, lr, #0x1
	mov r12, r6, lsl r12
	ands r12, r1, r12
	bne _020A6DEC
	add r3, r3, #0x1
	cmp r3, #0xd
	add r2, r2, #0x1
	blt _020A6DB4
_020A6DEC:
	ldr r1, _020A6E28 ; =0x4EC4EC4F
	add r3, r0, r3
	smull r0, r4, r1, r3
	mov r4, r4, asr #0x2
	mov r0, r3, lsr #0x1f
	ldr r2, _020A6E2C ; =0x0000000D
	add r4, r0, r4
	smull r0, r1, r2, r4
	sub r4, r3, r0
	add r0, r4, #0x1
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A6E24: .word UNK_021CA86C
_020A6E28: .word 0x4EC4EC4F
_020A6E2C: .word 0x0000000D

	arm_func_start FUN_020A6E30
FUN_020A6E30: ; 0x020A6E30
	ldr r0, _020A6E48 ; =UNK_021CA86C
	ldr r1, _020A6E4C ; =0x00AAA082
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	str r1, [r0, #0x264]
	bx lr
	.balign 4
_020A6E48: .word UNK_021CA86C
_020A6E4C: .word 0x00AAA082

	arm_func_start FUN_020A6E50
FUN_020A6E50: ; 0x020A6E50
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r0, r2
	mov r4, r1
	bl FUN_020A7148
	ldr r2, _020A6FF4 ; =UNK_021CA86C
	mov r3, #0x400
	ldr r1, [r2, #0x0]
	mov r0, #0x0
	add r12, r1, #0x1500
	add r1, r1, #0x2000
	str r12, [r1, #0x288]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r3, [r1, #0x8c]
	bl FUN_020A6D8C
	ldr r1, _020A6FF4 ; =UNK_021CA86C
	mov r2, #0x1
	mov r2, r2, lsl r0
	ldr r0, [r1, #0x0]
	mov r2, r2, asr #0x1
	add r0, r0, #0x2200
	strh r2, [r0, #0x8e]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2200
	ldrh r0, [r0, #0x68]
	cmp r0, #0x0
	bne _020A6EC8
	bl WM_GetDispersionScanPeriod
_020A6EC8:
	ldr r2, _020A6FF4 ; =UNK_021CA86C
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0x90]
	ldr r1, [r2, #0x0]
	add r0, r1, #0x2000
	ldr r0, [r0, #0x264]
	and r0, r0, #0x300000
	cmp r0, #0x300000
	movne r2, #0x1
	moveq r2, #0x0
	add r0, r1, #0x2200
	strh r2, [r0, #0x98]
	cmp r5, #0x0
	bne _020A6F24
	ldr r0, _020A6FF4 ; =UNK_021CA86C
	ldr r1, _020A6FF8 ; =0x00002292
	ldr r2, [r0, #0x0]
	ldr r0, _020A6FFC ; =UNK_020FF590
	add r1, r2, r1
	mov r2, #0x6
	bl MI_CpuCopy8
	b _020A6F40
_020A6F24:
	ldr r0, _020A6FF4 ; =UNK_021CA86C
	ldr r1, _020A6FF8 ; =0x00002292
	ldr r2, [r0, #0x0]
	mov r0, r5
	add r1, r2, r1
	mov r2, #0x6
	bl MI_CpuCopy8
_020A6F40:
	cmp r4, #0x0
	beq _020A6F54
	ldr r0, _020A7000 ; =UNK_020FF598
	cmp r4, r0
	bne _020A6F88
_020A6F54:
	ldr r0, _020A6FF4 ; =UNK_021CA86C
	ldr r1, _020A7004 ; =0x0000229C
	ldr r2, [r0, #0x0]
	ldr r0, _020A7000 ; =UNK_020FF598
	add r1, r2, r1
	mov r2, #0x20
	bl MI_CpuCopy8
	ldr r0, _020A6FF4 ; =UNK_021CA86C
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x9a]
	b _020A6FD4
_020A6F88:
	ldr r0, _020A6FF4 ; =UNK_021CA86C
	ldr r1, _020A7004 ; =0x0000229C
	ldr r2, [r0, #0x0]
	mov r0, r4
	add r1, r2, r1
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r1, #0x0
_020A6FA8:
	ldrb r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020A6FC4
	add r1, r1, #0x1
	cmp r1, #0x20
	add r4, r4, #0x1
	blt _020A6FA8
_020A6FC4:
	ldr r0, _020A6FF4 ; =UNK_021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x9a]
_020A6FD4:
	ldr r0, _020A6FF4 ; =UNK_021CA86C
	mov r1, #0x0
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	str r1, [r0, #0x284]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A6FF4: .word UNK_021CA86C
_020A6FF8: .word 0x00002292
_020A6FFC: .word UNK_020FF590
_020A7000: .word UNK_020FF598
_020A7004: .word 0x0000229C

	arm_func_start FUN_020A7008
FUN_020A7008: ; 0x020A7008
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	movs r5, r0
	mov r4, r1
	bne _020A705C
	ldr r1, _020A7134 ; =UNK_021CA86C
	mov r3, #0x3
	ldr r0, [r1, #0x0]
	mov r2, #0x0
	add r0, r0, #0x2000
	str r3, [r0, #0x26c]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2000
	str r2, [r0, #0x270]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2000
	str r2, [r0, #0x274]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2000
	str r2, [r0, #0x278]
	b _020A7118
_020A705C:
	ldr r1, _020A7134 ; =UNK_021CA86C
	ldr r2, [r5, #0x0]
	ldr r0, [r1, #0x0]
	and r2, r2, #0x3
	add r0, r0, #0x2000
	str r2, [r0, #0x26c]
	ldr r3, [r5, #0x4]
	ldr r0, [r5, #0x8]
	and r2, r3, #0x3
	rsb r2, r2, #0x4
	and r2, r2, #0x3
	add r2, r2, #0xc
	cmp r2, r0
	bls _020A70B4
	ldr r0, [r1, #0x0]
	mov r2, #0x0
	add r0, r0, #0x2000
	str r2, [r0, #0x270]
	ldr r0, [r1, #0x0]
	add r0, r0, #0x2000
	str r2, [r0, #0x274]
	b _020A7104
_020A70B4:
	ldr r0, [r1, #0x0]
	add r2, r3, #0x3
	bic r2, r2, #0x3
	add r0, r0, #0x2000
	str r2, [r0, #0x270]
	ldr r2, [r5, #0x4]
	ldr r0, [r1, #0x0]
	and r2, r2, #0x3
	rsb r2, r2, #0x4
	ldr r3, [r5, #0x8]
	and r2, r2, #0x3
	sub r2, r3, r2
	add r0, r0, #0x2000
	str r2, [r0, #0x274]
	ldr r0, [r1, #0x0]
	mov r1, #0x0
	add r2, r0, #0x2000
	ldr r0, [r2, #0x270]
	ldr r2, [r2, #0x274]
	bl MI_CpuFill8
_020A7104:
	ldr r0, _020A7134 ; =UNK_021CA86C
	ldr r1, [r5, #0xc]
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	str r1, [r0, #0x278]
_020A7118:
	ldr r0, _020A7134 ; =UNK_021CA86C
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2000
	str r4, [r0, #0x27c]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A7134: .word UNK_021CA86C

	arm_func_start FUN_020A7138
FUN_020A7138:
	ldr r0, _020A7144 ; =UNK_021CA86C
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4
_020A7144: .word UNK_021CA86C

	arm_func_start FUN_020A7148
FUN_020A7148: ; 0x020A7148
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _020A71EC ; =UNK_021CA86C
	mov r2, #0x0
	ldr r1, [r1, #0x0]
	add r3, r1, #0x2000
	cmp r1, #0x0
	ldr r4, [r3, #0x264]
	bne _020A7188
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7188:
	ands r3, r5, #0x8000
	beq _020A71A4
	ldr r3, _020A71F0 ; =0x00003FFE
	orr r2, r2, r3
	ands r3, r5, r3
	ldreq r3, _020A71F4 ; =0x0000A082
	orreq r5, r5, r3
_020A71A4:
	ands r3, r5, #0x20000
	orrne r2, r2, #0x10000
	ands r3, r5, #0x80000
	orrne r2, r2, #0x40000
	ands r3, r5, #0x200000
	orrne r2, r2, #0x100000
	ands r3, r5, #0x800000
	orrne r2, r2, #0x400000
	mvn r2, r2
	and r2, r4, r2
	orr r2, r5, r2
	add r1, r1, #0x2000
	str r2, [r1, #0x264]
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A71EC: .word UNK_021CA86C
_020A71F0: .word 0x00003FFE
_020A71F4: .word 0x0000A082

	arm_func_start FUN_020A71F8
FUN_020A71F8: ; 0x020A71F8
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020A7228 ; =UNK_021CA86C
	mov r4, #0x0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	addne r1, r1, #0x2000
	ldrne r4, [r1, #0x260]
	bl OS_RestoreInterrupts
	mov r0, r4
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A7228: .word UNK_021CA86C

	arm_func_start FUN_020A722C
FUN_020A722C: ; 0x020A722C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r1, _020A747C ; =UNK_021CA86C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A7260
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7260:
	add r1, r1, #0x2000
	ldr r2, [r1, #0x260]
	cmp r2, #0xd
	addls pc, pc, r2, lsl #0x2
	b _020A7308
_020A7274:
	b _020A7308
_020A7278:
	b _020A72C0
_020A727C:
	b _020A7308
_020A7280:
	b _020A7320
_020A7284:
	b _020A7308
_020A7288:
	b _020A7308
_020A728C:
	b _020A72D4
_020A7290:
	b _020A7308
_020A7294:
	b _020A7308
_020A7298:
	b _020A7320
_020A729C:
	b _020A7308
_020A72A0:
	b _020A7308
_020A72A4:
	b _020A7320
_020A72A8:
	b _020A72AC
_020A72AC:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x2
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A72C0:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A72D4:
	mov r0, #0xd
	bl FUN_020A6C38
	ldr r1, _020A747C ; =UNK_021CA86C
	mov r0, r4
	ldr r1, [r1, #0x0]
	mov r2, #0x9
	add r1, r1, #0x2200
	strh r2, [r1, #0x80]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x3
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7308:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7320:
	ldrb r0, [r1, #0x26b]
	cmp r0, #0x1
	bne _020A734C
	mov r0, #0xd
	bl FUN_020A6C38
	ldr r0, _020A747C ; =UNK_021CA86C
	mov r1, #0x9
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7464
_020A734C:
	bl WMi_GetStatusAddress
	mov r5, r0
	mov r1, #0x2
	bl DC_InvalidateRange
	ldrh r0, [r5, #0x0]
	cmp r0, #0x0
	beq _020A737C
	cmp r0, #0x1
	beq _020A73BC
	cmp r0, #0x2
	beq _020A73C8
	b _020A73D4
_020A737C:
	bl WM_Finish
	cmp r0, #0x0
	bne _020A73F0
	mov r0, #0x1
	bl FUN_020A6C38
	ldr r1, _020A747C ; =UNK_021CA86C
	mov r0, r4
	ldr r1, [r1, #0x0]
	mov r2, #0x0
	add r1, r1, #0x2200
	strh r2, [r1, #0x80]
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A73BC:
	ldr r0, _020A7480 ; =FUN_020A6768
	bl WM_Disable
	b _020A73F0
_020A73C8:
	ldr r0, _020A7480 ; =FUN_020A6768
	bl WM_PowerOff
	b _020A73F0
_020A73D4:
	ldr r1, _020A747C ; =UNK_021CA86C
	ldr r0, _020A7484 ; =FUN_020A5A78
	ldr r1, [r1, #0x0]
	mov r2, #0x1
	add r1, r1, #0x2000
	strb r2, [r1, #0x26b]
	bl WM_Reset
_020A73F0:
	cmp r0, #0x2
	beq _020A740C
	cmp r0, #0x3
	beq _020A7444
	cmp r0, #0x8
	beq _020A742C
	b _020A7444
_020A740C:
	mov r0, #0xd
	bl FUN_020A6C38
	ldr r0, _020A747C ; =UNK_021CA86C
	mov r1, #0x9
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7464
_020A742C:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7444:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x7
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A7464:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A747C: .word UNK_021CA86C
_020A7480: .word FUN_020A6768
_020A7484: .word FUN_020A5A78

	arm_func_start FUN_020A7488
FUN_020A7488: ; 0x020A7488
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020A75B8 ; =UNK_021CA86C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A74B4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A74B4:
	add r1, r1, #0x2000
	ldr r2, [r1, #0x260]
	cmp r2, #0x3
	beq _020A74E4
	cmp r2, #0x9
	beq _020A7504
	cmp r2, #0xa
	bne _020A74F4
	bl OS_RestoreInterrupts
	mov r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr
_020A74E4:
	bl OS_RestoreInterrupts
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
_020A74F4:
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A7504:
	ldrb r0, [r1, #0x26b]
	cmp r0, #0x1
	bne _020A7530
	mov r0, #0xa
	bl FUN_020A6C38
	ldr r0, _020A75B8 ; =UNK_021CA86C
	mov r1, #0x6
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A75A4
_020A7530:
	ldr r0, _020A75BC ; =FUN_020A5DDC
	bl WM_EndDCF
	cmp r0, #0x2
	beq _020A7554
	cmp r0, #0x3
	beq _020A7588
	cmp r0, #0x8
	beq _020A7574
	b _020A7588
_020A7554:
	mov r0, #0xa
	bl FUN_020A6C38
	ldr r0, _020A75B8 ; =UNK_021CA86C
	mov r1, #0x6
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A75A4
_020A7574:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x4
	ldmia sp!, {r4,lr}
	bx lr
_020A7588:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4,lr}
	bx lr
_020A75A4:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A75B8: .word UNK_021CA86C
_020A75BC: .word FUN_020A5DDC

	arm_func_start FUN_020A75C0
FUN_020A75C0: ; 0x020A75C0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl OS_DisableInterrupts
	ldr r2, _020A7814 ; =UNK_021CA86C
	mov r4, r0
	ldr r12, [r2, #0x0]
	cmp r12, #0x0
	bne _020A7600
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7600:
	add r1, r12, #0x2000
	ldr r3, [r1, #0x260]
	cmp r3, #0x3
	beq _020A7624
	cmp r3, #0x8
	beq _020A7734
	cmp r3, #0x9
	beq _020A7748
	b _020A775C
_020A7624:
	cmp r7, #0x0
	bne _020A7640
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7640:
	ldrh r3, [r7, #0x3c]
	cmp r3, #0x0
	beq _020A7660
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7660:
	cmp r6, #0x0
	beq _020A76E8
	ldrb r3, [r6, #0x0]
	cmp r3, #0x4
	bhs _020A7680
	ldrb r0, [r6, #0x1]
	cmp r0, #0x4
	blo _020A7698
_020A7680:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7698:
	strb r3, [r1, #0x250]
	ldr r0, [r2, #0x0]
	ldrb r1, [r6, #0x1]
	add r0, r0, #0x2000
	strb r1, [r0, #0x251]
	ldr r1, [r2, #0x0]
	add r0, r1, #0x2000
	ldrb r0, [r0, #0x250]
	cmp r0, #0x0
	bne _020A76D4
	add r0, r1, #0x2200
	mov r1, #0x0
	mov r2, #0x50
	bl MI_CpuFill8
	b _020A76F8
_020A76D4:
	add r0, r6, #0x2
	add r1, r1, #0x2200
	mov r2, #0x50
	bl MI_CpuCopy8
	b _020A76F8
_020A76E8:
	add r0, r12, #0x2200
	mov r1, #0x0
	mov r2, #0x52
	bl MI_CpuFill8
_020A76F8:
	ldr r1, _020A7814 ; =UNK_021CA86C
	mov r0, r7
	ldr r1, [r1, #0x0]
	mov r2, #0xc0
	add r1, r1, #0x2140
	bl MI_CpuCopy8
	ldr r1, _020A7814 ; =UNK_021CA86C
	mov r0, r5
	ldr r1, [r1, #0x0]
	add r1, r1, #0x2100
	ldrh r2, [r1, #0x6e]
	orr r2, r2, #0x3
	strh r2, [r1, #0x70]
	bl FUN_020A7148
	b _020A7770
_020A7734:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x2
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7748:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A775C:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7770:
	ldr r1, _020A7818 ; =0x0000FFFF
	ldr r0, _020A781C ; =FUN_020A6768
	mov r3, r1
	mov r2, #0x50
	str r1, [sp, #0x0]
	bl WM_SetLifeTime
	cmp r0, #0x2
	beq _020A77A4
	cmp r0, #0x3
	beq _020A77DC
	cmp r0, #0x8
	beq _020A77C4
	b _020A77DC
_020A77A4:
	mov r0, #0x8
	bl FUN_020A6C38
	ldr r0, _020A7814 ; =UNK_021CA86C
	mov r1, #0x5
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A77FC
_020A77C4:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A77DC:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x7
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A77FC:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020A7814: .word UNK_021CA86C
_020A7818: .word 0x0000FFFF
_020A781C: .word FUN_020A6768

	arm_func_start FUN_020A7820
FUN_020A7820: ; 0x020A7820
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020A78D4 ; =UNK_021CA86C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A784C
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A784C:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x3
	beq _020A78A0
	cmp r1, #0x6
	beq _020A7870
	cmp r1, #0x7
	beq _020A7890
	b _020A78B0
_020A7870:
	mov r0, #0x7
	bl FUN_020A6C38
	ldr r0, _020A78D4 ; =UNK_021CA86C
	mov r1, #0x4
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A78C0
_020A7890:
	bl OS_RestoreInterrupts
	mov r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr
_020A78A0:
	bl OS_RestoreInterrupts
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
_020A78B0:
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A78C0:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A78D4: .word UNK_021CA86C

	arm_func_start FUN_020A78D8
FUN_020A78D8: ; 0x020A78D8
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	bl OS_DisableInterrupts
	ldr r1, _020A7A84 ; =UNK_021CA86C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A7918
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7918:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x3
	beq _020A79A0
	cmp r1, #0x5
	beq _020A793C
	cmp r1, #0x6
	beq _020A7964
	b _020A798C
_020A793C:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl FUN_020A6E50
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x2
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7964:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl FUN_020A6E50
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A798C:
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A79A0:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl FUN_020A6E50
	ldr r0, _020A7A84 ; =UNK_021CA86C
	ldr r0, [r0, #0x0]
	add r1, r0, #0x2200
	add r0, r0, #0x2000
	ldrh r1, [r1, #0x8c]
	ldr r0, [r0, #0x288]
	bl DC_InvalidateRange
	ldr r3, _020A7A84 ; =UNK_021CA86C
	ldr r2, _020A7A88 ; =0x00002288
	ldr r1, [r3, #0x0]
	ldr r0, _020A7A8C ; =FUN_020A6468
	add r1, r1, #0x2000
	ldr r5, [r1, #0x284]
	add r5, r5, #0x1
	str r5, [r1, #0x284]
	ldr r1, [r3, #0x0]
	add r1, r1, r2
	bl WM_StartScanEx
	cmp r0, #0x2
	beq _020A7A14
	cmp r0, #0x3
	beq _020A7A4C
	cmp r0, #0x8
	beq _020A7A34
	b _020A7A4C
_020A7A14:
	mov r0, #0x5
	bl FUN_020A6C38
	ldr r0, _020A7A84 ; =UNK_021CA86C
	mov r1, #0x3
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7A6C
_020A7A34:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7A4C:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x7
	ldmia sp!, {r4-r7,lr}
	bx lr
_020A7A6C:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020A7A84: .word UNK_021CA86C
_020A7A88: .word 0x00002288
_020A7A8C: .word FUN_020A6468

	arm_func_start FUN_020A7A90
FUN_020A7A90: ; 0x020A7A90
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	cmp r0, #0x0
	beq _020A7AA8
	cmp r1, #0x0
	bne _020A7AB8
_020A7AA8:
	bl FUN_020A7820
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
_020A7AB8:
	bl FUN_020A78D8
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020A7AC8
FUN_020A7AC8: ; 0x020A7AC8
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	ldr r1, _020A7BCC ; =UNK_021CA86C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A7AF4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A7AF4:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x1
	beq _020A7B24
	cmp r1, #0x3
	beq _020A7B44
	cmp r1, #0x4
	bne _020A7B34
	bl OS_RestoreInterrupts
	mov r0, #0x2
	ldmia sp!, {r4,lr}
	bx lr
_020A7B24:
	bl OS_RestoreInterrupts
	mov r0, #0x0
	ldmia sp!, {r4,lr}
	bx lr
_020A7B34:
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4,lr}
	bx lr
_020A7B44:
	ldr r0, _020A7BD0 ; =FUN_020A6768
	bl WM_PowerOff
	cmp r0, #0x2
	beq _020A7B68
	cmp r0, #0x3
	beq _020A7B9C
	cmp r0, #0x8
	beq _020A7B88
	b _020A7B9C
_020A7B68:
	mov r0, #0x4
	bl FUN_020A6C38
	ldr r0, _020A7BCC ; =UNK_021CA86C
	mov r1, #0x2
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7BB8
_020A7B88:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x4
	ldmia sp!, {r4,lr}
	bx lr
_020A7B9C:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4,lr}
	bx lr
_020A7BB8:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A7BCC: .word UNK_021CA86C
_020A7BD0: .word FUN_020A6768

	arm_func_start FUN_020A7BD4
FUN_020A7BD4: ; 0x020A7BD4
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	bl OS_DisableInterrupts
	ldr r1, _020A7E00 ; =UNK_021CA86C
	mov r4, r0
	ldr r1, [r1, #0x0]
	cmp r1, #0x0
	bne _020A7C08
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7C08:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x1
	beq _020A7C2C
	cmp r1, #0x2
	beq _020A7C3C
	cmp r1, #0x3
	beq _020A7C4C
	b _020A7C5C
_020A7C2C:
	mov r0, r6
	mov r1, r5
	bl FUN_020A7008
	b _020A7C6C
_020A7C3C:
	bl OS_RestoreInterrupts
	mov r0, #0x2
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7C4C:
	bl OS_RestoreInterrupts
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7C5C:
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7C6C:
	ldr r0, _020A7E00 ; =UNK_021CA86C
	ldr r0, [r0, #0x0]
	add r1, r0, #0x2000
	ldr r1, [r1, #0x26c]
	mov r1, r1, lsl #0x10
	mov r1, r1, lsr #0x10
	bl WM_Init
	cmp r0, #0x6
	addls pc, pc, r0, lsl #0x2
	b _020A7CE0
_020A7C94:
	b _020A7CFC
_020A7C98:
	b _020A7CE0
_020A7C9C:
	b _020A7CE0
_020A7CA0:
	b _020A7CB0
_020A7CA4:
	b _020A7CCC
_020A7CA8:
	b _020A7CE0
_020A7CAC:
	b _020A7CE0
_020A7CB0:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7CCC:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x5
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7CE0:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7CFC:
	bl WM_GetAllowedChannel
	cmp r0, #0x0
	bne _020A7D44
	bl WM_Finish
	cmp r0, #0x0
	beq _020A7D30
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7D30:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x5
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7D44:
	ldr r0, _020A7E04 ; =FUN_020A6A74
	bl WM_SetIndCallback
	cmp r0, #0x0
	beq _020A7D70
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7D70:
	ldr r0, _020A7E08 ; =FUN_020A6768
	bl WM_Enable
	cmp r0, #0x2
	beq _020A7D94
	cmp r0, #0x3
	beq _020A7DD0
	cmp r0, #0x8
	beq _020A7DB4
	b _020A7DD0
_020A7D94:
	mov r0, #0x2
	bl FUN_020A6C38
	ldr r0, _020A7E00 ; =UNK_021CA86C
	mov r1, #0x1
	ldr r0, [r0, #0x0]
	add r0, r0, #0x2200
	strh r1, [r0, #0x80]
	b _020A7DEC
_020A7DB4:
	mov r0, #0xc
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7DD0:
	mov r0, #0xb
	bl FUN_020A6C38
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x7
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7DEC:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x3
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A7E00: .word UNK_021CA86C
_020A7E04: .word FUN_020A6A74
_020A7E08: .word FUN_020A6768

	arm_func_start FUN_020A7E0C
FUN_020A7E0C: ; 0x020A7E0C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	ldr r2, _020A7E7C ; =UNK_021CA86C
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	bne _020A7E3C
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {lr}
	bx lr
_020A7E3C:
	add r1, r1, #0x2000
	ldr r1, [r1, #0x260]
	cmp r1, #0x1
	beq _020A7E60
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x1
	ldmia sp!, {lr}
	bx lr
_020A7E60:
	mov r1, #0x0
	str r1, [r2, #0x0]
	bl OS_RestoreInterrupts
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A7E7C: .word UNK_021CA86C

	arm_func_start FUN_020A7E80
FUN_020A7E80: ; 0x020A7E80
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	mov r5, r1
	bl OS_DisableInterrupts
	ldr r2, _020A7FA8 ; =UNK_021CA86C
	mov r4, r0
	ldr r1, [r2, #0x0]
	cmp r1, #0x0
	beq _020A7EB4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7EB4:
	cmp r6, #0x0
	bne _020A7ECC
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7ECC:
	ands r1, r6, #0x1f
	beq _020A7EE4
	bl OS_RestoreInterrupts
	mov r0, #0x1
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7EE4:
	cmp r5, #0x2300
	bhs _020A7EFC
	bl OS_RestoreInterrupts
	mov r0, #0x6
	ldmia sp!, {r4-r6,lr}
	bx lr
_020A7EFC:
	str r6, [r2, #0x0]
	add r0, r6, #0x2000
	mov r1, #0x1
	str r1, [r0, #0x260]
	ldr r1, [r2, #0x0]
	mov r0, #0x0
	add r1, r1, #0x2200
	strh r0, [r1, #0x80]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0x68]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2000
	strb r0, [r1, #0x26a]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2000
	strb r0, [r1, #0x26b]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0x82]
	ldr r1, [r2, #0x0]
	add r1, r1, #0x2200
	strh r0, [r1, #0xf8]
	bl FUN_020A6E30
	bl FUN_020A897C
	bl OS_IsTickAvailable
	cmp r0, #0x0
	bne _020A7F70
	bl OS_InitTick
_020A7F70:
	bl OS_IsAlarmAvailable
	cmp r0, #0x0
	bne _020A7F80
	bl OS_InitAlarm
_020A7F80:
	ldr r1, _020A7FA8 ; =UNK_021CA86C
	ldr r0, _020A7FAC ; =0x000022CC
	ldr r1, [r1, #0x0]
	add r0, r1, r0
	bl OS_CreateAlarm
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0x0
	ldmia sp!, {r4-r6,lr}
	bx lr
	.balign 4
_020A7FA8: .word UNK_021CA86C
_020A7FAC: .word 0x000022CC

	arm_func_start FUN_020A7FB0
FUN_020A7FB0: ; 0x020A7FB0
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020A7138
	add r1, r0, #0x2000
	cmp r4, #0x0
	ldr r0, [r1, #0x270]
	ldmeqia sp!, {r4,lr}
	bxeq lr
	cmp r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, [r1, #0x274]
	cmp r1, #0xc
	ldmlsia sp!, {r4,lr}
	bxls lr
	ldr r3, [r0, #0x4]
	cmp r3, #0x0
	beq _020A8040
_020A7FF8:
	cmp r3, r4
	bne _020A8034
	ldr r2, [r3, #0x8]
	cmp r2, #0x0
	ldrne r1, [r3, #0xc]
	strne r1, [r2, #0xc]
	ldreq r1, [r3, #0xc]
	streq r1, [r0, #0x4]
	ldr r2, [r3, #0xc]
	cmp r2, #0x0
	ldrne r1, [r3, #0x8]
	strne r1, [r2, #0x8]
	ldreq r1, [r3, #0x8]
	streq r1, [r0, #0x8]
	b _020A8040
_020A8034:
	ldr r3, [r3, #0xc]
	cmp r3, #0x0
	bne _020A7FF8
_020A8040:
	mov r1, #0x0
	str r1, [r4, #0xc]
	ldr r1, [r0, #0x8]
	str r1, [r4, #0x8]
	str r4, [r0, #0x8]
	ldr r1, [r4, #0x8]
	cmp r1, #0x0
	strne r4, [r1, #0xc]
	streq r4, [r0, #0x4]
	cmp r3, #0x0
	ldreq r1, [r0, #0x0]
	streq r1, [r4, #0x4]
	ldreq r1, [r0, #0x0]
	addeq r1, r1, #0x1
	streq r1, [r0, #0x0]
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020A8084
FUN_020A8084: ; 0x020A8084
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl FUN_020A7138
	add r1, r0, #0x2000
	ldr r2, [r1, #0x270]
	mov r0, #0x0
	cmp r2, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, [r1, #0x274]
	cmp r1, #0xc
	ldmlsia sp!, {r4,lr}
	bxls lr
	ldr r0, [r2, #0x4]
	cmp r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
_020A80C8:
	ldr r1, [r0, #0x4]
	cmp r1, r4
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, [r0, #0xc]
	cmp r0, #0x0
	bne _020A80C8
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020A80EC
FUN_020A80EC: ; 0x020A80EC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl FUN_020A7138
	add r0, r0, #0x2000
	cmp r5, #0x0
	mov r4, #0x0
	ldr r1, [r0, #0x270]
	addeq sp, sp, #0x4
	moveq r0, r4
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	cmp r1, #0x0
	beq _020A8160
	ldr r0, [r0, #0x274]
	cmp r0, #0xc
	bls _020A8160
	ldr r4, [r1, #0x4]
	cmp r4, #0x0
	beq _020A8160
_020A813C:
	add r0, r4, #0x10
	mov r1, r5
	add r0, r0, #0x4
	bl FUN_020A8B78
	cmp r0, #0x0
	bne _020A8160
	ldr r4, [r4, #0xc]
	cmp r4, #0x0
	bne _020A813C
_020A8160:
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A8170
FUN_020A8170: ; 0x020A8170
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020A7138
	add r0, r0, #0x2000
	ldr r1, [r0, #0x270]
	cmp r1, #0x0
	beq _020A81A4
	ldr r0, [r0, #0x274]
	cmp r0, #0xc
	addhi sp, sp, #0x4
	ldrhi r0, [r1, #0x4]
	ldmhiia sp!, {lr}
	bxhi lr
_020A81A4:
	mov r0, #0x0
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020A81B4
FUN_020A81B4: ; 0x020A81B4
	stmdb sp!, {r4,lr}
	bl FUN_020A7138
	add r2, r0, #0x2000
	ldr r1, [r2, #0x270]
	mov r0, #0x0
	cmp r1, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r3, [r2, #0x274]
	cmp r3, #0xc
	ldmlsia sp!, {r4,lr}
	bxls lr
	ldr r2, _020A8294 ; =0x4EC4EC4F
	sub r3, r3, #0xc
	umull r2, r4, r3, r2
	movs r4, r4, lsr #0x6
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r2, [r1, #0x0]
	cmp r4, r2
	ldmlsia sp!, {r4,lr}
	bxls lr
	mov lr, r0
	cmp r4, #0x0
	bls _020A8240
	add r12, r1, #0xc
	mov r2, #0xd0
_020A8220:
	mul r0, lr, r2
	ldrb r3, [r12, r0]
	add r0, r12, r0
	cmp r3, #0x0
	beq _020A8240
	add lr, lr, #0x1
	cmp lr, r4
	blo _020A8220
_020A8240:
	cmp lr, r4
	ldmcsia sp!, {r4,lr}
	bxcs lr
	mov r2, #0x1
	strb r2, [r0, #0x0]
	ldr r3, [r1, #0x0]
	mov r2, #0x0
	str r3, [r0, #0x4]
	str r2, [r0, #0xc]
	ldr r2, [r1, #0x8]
	str r2, [r0, #0x8]
	str r0, [r1, #0x8]
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	strne r0, [r2, #0xc]
	streq r0, [r1, #0x4]
	ldr r2, [r1, #0x0]
	add r2, r2, #0x1
	str r2, [r1, #0x0]
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A8294: .word 0x4EC4EC4F

	arm_func_start FUN_020A8298
FUN_020A8298: ; 0x020A8298
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r0
	mov r4, r1
	bl FUN_020A7138
	movs r7, r0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	add r0, r7, #0x2000
	ldrb r0, [r0, #0x26a]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	ldrh r0, [r5, #0x3c]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {r4-r7,lr}
	bxne lr
	add r0, r5, #0x4
	bl FUN_020A80EC
	movs r6, r0
	bne _020A8300
	bl FUN_020A81B4
	mov r6, r0
_020A8300:
	cmp r6, #0x0
	bne _020A8320
	add r0, r7, #0x2000
	ldr r0, [r0, #0x278]
	cmp r0, #0x1
	bne _020A8320
	bl FUN_020A8170
	mov r6, r0
_020A8320:
	cmp r6, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7,lr}
	bxeq lr
	mov r0, r5
	add r1, r6, #0x10
	mov r2, #0xc0
	strh r4, [r6, #0x2]
	bl MIi_CpuCopyFast
	mov r0, r6
	bl FUN_020A7FB0
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr

	arm_func_start FUN_020A8358
FUN_020A8358: ; 0x020A8358
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r4, r0
	bl OS_DisableInterrupts
	mov r5, r0
	bl FUN_020A7138
	cmp r0, #0x0
	bne _020A8390
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A8390:
	mov r0, r4
	bl FUN_020A8084
	movs r4, r0
	bne _020A83B8
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A83B8:
	mov r0, r5
	bl OS_RestoreInterrupts
	add r0, r4, #0x10
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A83D0
FUN_020A83D0: ; 0x020A83D0
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, r0
	bl OS_DisableInterrupts
	mov r4, r0
	bl FUN_020A7138
	cmp r0, #0x0
	bne _020A8408
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A8408:
	cmp r5, #0x0
	beq _020A8434
	add r1, r0, #0x2000
	ldrb r1, [r1, #0x26a]
	add r0, r0, #0x2000
	cmp r1, #0x0
	movne r5, #0x1
	mov r1, #0x1
	moveq r5, #0x0
	strb r1, [r0, #0x26a]
	b _020A8454
_020A8434:
	add r1, r0, #0x2000
	ldrb r1, [r1, #0x26a]
	add r0, r0, #0x2000
	cmp r1, #0x0
	movne r5, #0x1
	mov r1, #0x0
	moveq r5, #0x0
	strb r1, [r0, #0x26a]
_020A8454:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A846C
FUN_020A846C: ; 0x020A846C
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	mov r5, r0
	bl FUN_020A7138
	cmp r0, #0x0
	mov r4, #0x0
	bne _020A84A4
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #0x4
	mov r0, r4
	ldmia sp!, {r4-r5,lr}
	bx lr
_020A84A4:
	add r0, r0, #0x2000
	ldr r1, [r0, #0x270]
	cmp r1, #0x0
	beq _020A84C0
	ldr r0, [r0, #0x274]
	cmp r0, #0xc
	ldrhi r4, [r1, #0x0]
_020A84C0:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A84D8
FUN_020A84D8: ; 0x020A84D8
	stmdb sp!, {r4,lr}
	bl OS_DisableInterrupts
	mov r4, r0
	bl FUN_020A7138
	cmp r0, #0x0
	bne _020A8500
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
_020A8500:
	add r1, r0, #0x2000
	ldr r0, [r1, #0x270]
	cmp r0, #0x0
	beq _020A8524
	ldr r2, [r1, #0x274]
	cmp r2, #0x0
	ble _020A8524
	mov r1, #0x0
	bl MI_CpuFill8
_020A8524:
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr

	arm_func_start FUN_020A8534
FUN_020A8534: ; 0x020A8534
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, [r0, #0x8]
	ldr r1, _020A858C ; =0x01FF8000
	cmp r2, r1
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r1, [r0, #0xc]
	sub r1, r1, #0x1
	str r1, [r0, #0xc]
	ldr r1, [r0, #0xc]
	cmp r1, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	mov r1, #0x0
	str r1, [r0, #0x8]
	bl OS_WakeupThread
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A858C: .word 0x01FF8000

	arm_func_start FUN_020A8590
FUN_020A8590:
	ldr r2, [r0, #0x8]
	cmp r2, #0x0
	bne _020A85B8
	ldr r1, _020A85D8 ; =0x01FF8000
	str r1, [r0, #0x8]
	ldr r1, [r0, #0xc]
	add r1, r1, #0x1
	str r1, [r0, #0xc]
	mov r0, #0x1
	bx lr
_020A85B8:
	ldr r1, _020A85D8 ; =0x01FF8000
	cmp r2, r1
	ldreq r1, [r0, #0xc]
	addeq r1, r1, #0x1
	streq r1, [r0, #0xc]
	moveq r0, #0x1
	movne r0, #0x0
	bx lr
	.balign 4
_020A85D8: .word 0x01FF8000

	arm_func_start FUN_020A85DC
FUN_020A85DC: ; 0x020A85DC
	ldr ip, _020A85E8 ; =FUN_020A8534
	ldr r0, _020A85EC ; =UNK_021CA87C
	bx r12
	.balign 4
_020A85E8: .word FUN_020A8534
_020A85EC: .word UNK_021CA87C

	arm_func_start FUN_020A85F0
FUN_020A85F0: ; 0x020A85F0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldrh r1, [r0, #0x0]
	cmp r1, #0x12
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldrh r2, [r0, #0x2]
	ldr r1, _020A863C ; =UNK_021CA870
	str r2, [r1, #0x24]
	ldrh r0, [r0, #0x2]
	cmp r0, #0x0
	bne _020A8628
	bl FUN_020A6BBC
_020A8628:
	ldr r0, _020A8640 ; =UNK_021CA874
	bl OS_WakeupThread
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A863C: .word UNK_021CA870
_020A8640: .word UNK_021CA874

	arm_func_start WCM_SendDCFData
WCM_SendDCFData:
	stmdb sp!, {r4-r8,lr}
	mov r8, r0
	mov r7, r1
	mov r6, r2
	bl OS_DisableInterrupts
	mov r5, r0
	bl FUN_020A7138
	cmp r0, #0x0
	bne _020A867C
	mov r0, r5
	bl OS_RestoreInterrupts
	mvn r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A867C:
	ldr r0, _020A87AC ; =UNK_021CA87C
	bl OS_LockMutex
	bl FUN_020A7138
	movs r4, r0
	bne _020A86AC
	ldr r0, _020A87AC ; =UNK_021CA87C
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
	mvn r0, #0x0
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A86AC:
	add r0, r4, #0x2000
	ldr r1, [r0, #0x260]
	cmp r1, #0x9
	bne _020A86C8
	ldrb r0, [r0, #0x26b]
	cmp r0, #0x1
	bne _020A86E4
_020A86C8:
	ldr r0, _020A87AC ; =UNK_021CA87C
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
	mvn r0, #0x3
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A86E4:
	mov r0, r7
	mov r2, r6
	add r1, r4, #0xf00
	bl MI_CpuCopy8
	mov r3, r6, lsl #0x10
	ldr r0, _020A87B0 ; =FUN_020A85F0
	mov r1, r8
	add r2, r4, #0xf00
	mov r3, r3, lsr #0x10
	bl WM_SetDCFData
	cmp r0, #0x8
	addls pc, pc, r0, lsl #0x2
	b _020A873C
_020A8718:
	b _020A873C
_020A871C:
	b _020A873C
_020A8720:
	b _020A8758
_020A8724:
	b _020A873C
_020A8728:
	b _020A873C
_020A872C:
	b _020A873C
_020A8730:
	b _020A873C
_020A8734:
	b _020A873C
_020A8738:
	b _020A873C
_020A873C:
	ldr r0, _020A87AC ; =UNK_021CA87C
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
	mvn r0, #0x4
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A8758:
	ldr r0, _020A87B4 ; =UNK_021CA874
	bl OS_SleepThread
	ldr r0, _020A87B8 ; =UNK_021CA870
	ldr r0, [r0, #0x24]
	cmp r0, #0x0
	beq _020A8790
	cmp r0, #0x1
	ldr r0, _020A87AC ; =UNK_021CA87C
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
	mvn r0, #0x4
	ldmia sp!, {r4-r8,lr}
	bx lr
_020A8790:
	ldr r0, _020A87AC ; =UNK_021CA87C
	bl OS_UnlockMutex
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r6
	ldmia sp!, {r4-r8,lr}
	bx lr
	.balign 4
_020A87AC: .word UNK_021CA87C
_020A87B0: .word FUN_020A85F0
_020A87B4: .word UNK_021CA874
_020A87B8: .word UNK_021CA870

	arm_func_start WCM_SetRecvDCFCallback
WCM_SetRecvDCFCallback: ; 0x020A87BC
	stmdb sp!, {r4,lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _020A87DC ; =UNK_021CA870
	str r4, [r1, #0x28]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A87DC: .word UNK_021CA870

	arm_func_start FUN_020A87E0
FUN_020A87E0: ; 0x020A87E0
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r7, #0x0
	mov r4, r0
	mov r6, r7
	bl FUN_020A7138
	mov r5, r0
	bl OS_DisableInterrupts
	cmp r5, #0x0
	beq _020A8830
	add r1, r5, #0x2000
	ldr r2, [r1, #0x260]
	cmp r2, #0x9
	bne _020A8830
	ldrb r1, [r1, #0x26b]
	cmp r1, #0x0
	addeq r2, r5, #0x2100
	ldreq r1, _020A884C ; =0x0000214C
	ldreqh r6, [r2, #0x4a]
	addeq r7, r5, r1
_020A8830:
	bl OS_RestoreInterrupts
	cmp r4, #0x0
	strneh r6, [r4, #0x0]
	mov r0, r7
	add sp, sp, #0x4
	ldmia sp!, {r4-r7,lr}
	bx lr
	.balign 4
_020A884C: .word 0x0000214C

	arm_func_start WCM_GetApMacAddress
WCM_GetApMacAddress:
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	mov r5, #0x0
	bl FUN_020A7138
	mov r4, r0
	bl OS_DisableInterrupts
	cmp r4, #0x0
	beq _020A8890
	add r1, r4, #0x2000
	ldr r2, [r1, #0x260]
	cmp r2, #0x9
	bne _020A8890
	ldrb r1, [r1, #0x26b]
	cmp r1, #0x0
	ldreq r1, _020A88A4 ; =0x00002144
	addeq r5, r4, r1
_020A8890:
	bl OS_RestoreInterrupts
	mov r0, r5
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020A88A4: .word 0x00002144

	arm_func_start FUN_020A88A8
FUN_020A88A8: ; 0x020A88A8
	stmdb sp!, {r4,lr}
	bl FUN_020A7138
	movs r4, r0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	add r0, r4, #0x2000
	ldr r1, [r0, #0x260]
	cmp r1, #0x9
	ldmneia sp!, {r4,lr}
	bxne lr
	ldrb r0, [r0, #0x26b]
	cmp r0, #0x1
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, _020A8928 ; =UNK_021CA87C
	bl FUN_020A8590
	cmp r0, #0x0
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r1, _020A892C ; =0x00002144
	ldr r0, _020A8930 ; =FUN_020A85DC
	add r1, r4, r1
	add r2, r4, #0xf00
	mov r3, #0x0
	bl WM_SetDCFData
	cmp r0, #0x2
	ldmeqia sp!, {r4,lr}
	bxeq lr
	ldr r0, _020A8928 ; =UNK_021CA87C
	bl FUN_020A8534
	ldmia sp!, {r4,lr}
	bx lr
	.balign 4
_020A8928: .word UNK_021CA87C
_020A892C: .word 0x00002144
_020A8930: .word FUN_020A85DC

	arm_func_start FUN_020A8934
FUN_020A8934: ; 0x020A8934
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020A8978 ; =UNK_021CA870
	mov r2, r0
	ldr r12, [r1, #0x28]
	cmp r12, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {lr}
	bxeq lr
	ldrh r3, [r2, #0x6]
	add r0, r2, #0x1e
	add r1, r2, #0x18
	add r2, r2, #0x2c
	blx r12
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A8978: .word UNK_021CA870

	arm_func_start FUN_020A897C
FUN_020A897C: ; 0x020A897C
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020A89C8 ; =UNK_021CA870
	ldrb r0, [r1, #0x0]
	cmp r0, #0x0
	addne sp, sp, #0x4
	ldmneia sp!, {lr}
	bxne lr
	ldr r0, _020A89CC ; =UNK_021CA87C
	mov r2, #0x0
	mov r3, #0x1
	strb r3, [r1, #0x0]
	str r2, [r1, #0x24]
	str r2, [r1, #0x8]
	str r2, [r1, #0x4]
	bl OS_InitMutex
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A89C8: .word UNK_021CA870
_020A89CC: .word UNK_021CA87C

	arm_func_start FUN_020A89D0
FUN_020A89D0: ; 0x020A89D0
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r2, _020A8A48 ; =UNK_021CA89C
	ands r1, r0, #0x2
	ldrb r12, [r2, #0x0]
	movne r0, r0, asr #0x2
	andne lr, r0, #0xff
	moveq r0, r0, asr #0x2
	addeq r0, r0, #0x19
	andeq lr, r0, #0xff
	mov r1, r12, lsr #0x1f
	rsb r0, r1, r12, lsl #0x1c
	cmp r12, #0x10
	ldr r3, _020A8A4C ; =UNK_021CA8A0
	add r0, r1, r0, ror #0x1c
	strb lr, [r3, r0]
	addcc r0, r12, #0x1
	strccb r0, [r2, #0x0]
	addcc sp, sp, #0x4
	ldmccia sp!, {lr}
	bxcc lr
	add r0, r12, #0x1
	mov r1, r0, lsr #0x1f
	rsb r0, r1, r0, lsl #0x1c
	add r0, r1, r0, ror #0x1c
	add r0, r0, #0x10
	strb r0, [r2, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A8A48: .word UNK_021CA89C
_020A8A4C: .word UNK_021CA8A0

	arm_func_start FUN_020A8A50
FUN_020A8A50: ; 0x020A8A50
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	bl FUN_020A8A90
	mov r1, #0x0
	cmp r0, #0x1c
	movcs r1, #0x3
	bhs _020A8A80
	cmp r0, #0x16
	movcs r1, #0x2
	bhs _020A8A80
	cmp r0, #0x10
	movcs r1, #0x1
_020A8A80:
	mov r0, r1
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr

	arm_func_start FUN_020A8A90
FUN_020A8A90: ; 0x020A8A90
	stmdb sp!, {lr}
	sub sp, sp, #0x4
	ldr r1, _020A8B20 ; =UNK_021CA89C
	mov r0, #0x0
	ldrb r1, [r1, #0x0]
	cmp r1, #0x10
	bls _020A8ADC
	ldr r2, _020A8B24 ; =UNK_021CA8A0
	mov r3, r0
_020A8AB4:
	ldrb r1, [r2, #0x0]
	add r3, r3, #0x1
	cmp r3, #0x10
	add r0, r0, r1
	add r2, r2, #0x1
	blt _020A8AB4
	mov r1, r0, asr #0x3
	add r0, r0, r1, lsr #0x1c
	mov r0, r0, asr #0x4
	b _020A8B10
_020A8ADC:
	cmp r1, #0x0
	beq _020A8B10
	mov r3, r0
	cmp r1, #0x0
	ble _020A8B0C
	ldr ip, _020A8B24 ; =UNK_021CA8A0
_020A8AF4:
	ldrb r2, [r12, #0x0]
	add r3, r3, #0x1
	cmp r3, r1
	add r0, r0, r2
	add r12, r12, #0x1
	blt _020A8AF4
_020A8B0C:
	bl _s32_div_f
_020A8B10:
	and r0, r0, #0xff
	add sp, sp, #0x4
	ldmia sp!, {lr}
	bx lr
	.balign 4
_020A8B20: .word UNK_021CA89C
_020A8B24: .word UNK_021CA8A0

	arm_func_start FUN_020A8B28
FUN_020A8B28: ; 0x020A8B28
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	bl OS_DisableInterrupts
	mov r5, r0
	bl FUN_020A7138
	cmp r0, #0x0
	mov r4, #0x0
	beq _020A8B60
	add r0, r0, #0x2000
	ldr r0, [r0, #0x260]
	cmp r0, #0x9
	bne _020A8B60
	bl FUN_020A8A50
	mov r4, r0
_020A8B60:
	mov r0, r5
	bl OS_RestoreInterrupts
	mov r0, r4
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr

	arm_func_start FUN_020A8B78
FUN_020A8B78:
	mov r12, #0x0
_020A8B7C:
	ldrb r3, [r0, r12]
	ldrb r2, [r1, r12]
	cmp r3, r2
	movne r0, #0x0
	bxne lr
	add r12, r12, #0x1
	cmp r12, #0x6
	blt _020A8B7C
	mov r0, #0x1
	bx lr
