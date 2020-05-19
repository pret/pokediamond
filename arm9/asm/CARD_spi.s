	.include "asm/macros.inc"
	.include "global.inc"

    .text

	arm_func_start CARDi_IdentifyBackupCore
CARDi_IdentifyBackupCore: ; 0x020D6A60
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4
	ldr r1, _020D6D60 ; =0x021D55C0
	mov r5, r0
	ldr r4, [r1, #0x0]
	mov r1, #0x0
	add r0, r4, #0x18
	mov r2, #0x48
	bl MI_CpuFill8
_020D6A84: ; 0x020D6A84
	cmp r5, #0x0
	str r5, [r4, #0x4]
	mov r0, #0x3f
	addeq sp, sp, #0x4
	str r0, [r4, #0x4c]
	ldmeqia sp!, {r4-r5,lr}
	bxeq lr
	mov r0, r5, asr #0x8
	and r0, r0, #0xff
	mov r2, #0x1
	mov r3, r2, lsl r0
	and r1, r5, #0xff
	str r3, [r4, #0x18]
	mov r0, #0xff
	strb r0, [r4, #0x48]
	cmp r1, #0x1
	bne _020D6B80
	cmp r3, #0x200
	beq _020D6AE4
	cmp r3, #0x2000
	beq _020D6B04
	cmp r3, #0x10000
	beq _020D6B28
	b _020D6D38
_020D6AE4:
	mov r0, #0x10
	str r0, [r4, #0x20]
	str r2, [r4, #0x24]
	mov r0, #0x5
	str r0, [r4, #0x28]
	mov r0, #0xf0
	strb r0, [r4, #0x48]
	b _020D6B48
_020D6B04:
	mov r0, #0x20
	str r0, [r4, #0x20]
	mov r0, #0x2
	str r0, [r4, #0x24]
	mov r0, #0x5
	str r0, [r4, #0x28]
	mov r0, #0x0
	strb r0, [r4, #0x48]
	b _020D6B48
_020D6B28:
	mov r0, #0x80
	str r0, [r4, #0x20]
	mov r0, #0x2
	str r0, [r4, #0x24]
	mov r0, #0xa
	str r0, [r4, #0x28]
	mov r0, #0x0
	strb r0, [r4, #0x48]
_020D6B48:
	ldr r0, [r4, #0x20]
	add sp, sp, #0x4
	str r0, [r4, #0x1c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x40
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x100
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x200
	str r0, [r4, #0x4c]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D6B80:
	cmp r1, #0x2
	bne _020D6CD8
	cmp r3, #0x100000
	bhi _020D6BB8
	cmp r3, #0x100000
	bhs _020D6BD8
	cmp r3, #0x40000
	bhi _020D6BAC
	cmp r3, #0x40000
	beq _020D6BD8
	b _020D6D38
_020D6BAC:
	cmp r3, #0x80000
	beq _020D6BD8
	b _020D6D38
_020D6BB8:
	cmp r3, #0x200000
	bhi _020D6BCC
	cmp r3, #0x200000
	beq _020D6C10
	b _020D6D38
_020D6BCC:
	cmp r3, #0x800000
	beq _020D6C48
	b _020D6D38
_020D6BD8:
	mov r0, #0x19
	str r0, [r4, #0x2c]
	mov r1, #0x12c
	str r1, [r4, #0x30]
	ldr r0, _020D6D64 ; =0x00001388
	str r1, [r4, #0x44]
	str r0, [r4, #0x3c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x80
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x400
	str r0, [r4, #0x4c]
	b _020D6C7C
_020D6C10:
	mov r1, #0x3e8
	ldr r0, _020D6D68 ; =0x00000BB8
	str r1, [r4, #0x3c]
	ldr r1, _020D6D6C ; =0x00004268
	str r0, [r4, #0x40]
	ldr r0, _020D6D70 ; =0x00009C40
	str r1, [r4, #0x34]
	str r0, [r4, #0x38]
	mov r0, #0x0
	strb r0, [r4, #0x48]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x1000
	str r0, [r4, #0x4c]
	b _020D6C7C
_020D6C48:
	mov r1, #0x3e8
	ldr r0, _020D6D68 ; =0x00000BB8
	str r1, [r4, #0x3c]
	ldr r1, _020D6D74 ; =0x000109A0
	str r0, [r4, #0x40]
	ldr r0, _020D6D78 ; =0x00027100
	str r1, [r4, #0x34]
	str r0, [r4, #0x38]
	mov r0, #0x0
	strb r0, [r4, #0x48]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x1000
	str r0, [r4, #0x4c]
_020D6C7C:
	mov r0, #0x10000
	str r0, [r4, #0x1c]
	mov r0, #0x100
	str r0, [r4, #0x20]
	mov r0, #0x3
	str r0, [r4, #0x24]
	mov r0, #0x5
	str r0, [r4, #0x28]
	ldr r0, [r4, #0x4c]
	add sp, sp, #0x4
	orr r0, r0, #0x40
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x100
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x200
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x800
	str r0, [r4, #0x4c]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D6CD8:
	cmp r1, #0x3
	bne _020D6D38
	cmp r3, #0x2000
	beq _020D6CF0
	cmp r3, #0x8000
	bne _020D6D38
_020D6CF0:
	str r3, [r4, #0x20]
	str r3, [r4, #0x1c]
	mov r0, #0x2
	str r0, [r4, #0x24]
	mov r0, #0x0
	strb r0, [r4, #0x48]
	ldr r0, [r4, #0x4c]
	add sp, sp, #0x4
	orr r0, r0, #0x40
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x100
	str r0, [r4, #0x4c]
	ldr r0, [r4, #0x4c]
	orr r0, r0, #0x200
	str r0, [r4, #0x4c]
	ldmia sp!, {r4-r5,lr}
	bx lr
_020D6D38:
	mov r1, #0x0
	str r1, [r4, #0x4]
	str r1, [r4, #0x18]
	ldr r0, _020D6D60 ; =0x021D55C0
	mov r1, #0x3
	ldr r0, [r0, #0x0]
	str r1, [r0, #0x0]
	add sp, sp, #0x4
	ldmia sp!, {r4-r5,lr}
	bx lr
	.balign 4
_020D6D60: .word 0x021D55C0
_020D6D64: .word 0x00001388
_020D6D68: .word 0x00000BB8
_020D6D6C: .word 0x00004268
_020D6D70: .word 0x00009C40
_020D6D74: .word 0x000109A0
_020D6D78: .word 0x00027100
