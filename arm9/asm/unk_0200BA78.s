    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_0200BA78
FUN_0200BA78: ; 0x0200BA78
	push {r3-r6, lr}
	sub sp, #0xc
	add r4, r2, #0x0
	ldr r2, [sp, #0x2c]
	add r6, r3, #0x0
	str r2, [sp, #0x0]
	ldr r2, [sp, #0x24]
	ldr r3, [sp, #0x28]
	add r5, r0, #0x0
	bl FUN_0200B9A8
	ldr r0, [sp, #0x24]
	ldr r3, [sp, #0x20]
	str r0, [sp, #0x0]
	ldr r0, [sp, #0x28]
	add r1, r4, #0x0
	add r0, #0x10
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x2c]
	add r2, r6, #0x0
	str r0, [sp, #0x8]
	add r0, r5, #0x0
	bl FUN_0200B9EC
	add sp, #0xc
	pop {r3-r6, pc}

	thumb_func_start FUN_0200BAAC
FUN_0200BAAC: ; 0x0200BAAC
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r4, r2, #0x0
	ldr r2, [r7, #0x28]
	ldr r6, [sp, #0x18]
	lsl r0, r2, #0x4
	orr r0, r2
	lsl r0, r0, #0x18
	lsr r0, r0, #0x18
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	add r2, r3, #0x0
	add r0, #0x8
	add r3, r4, #0x0
	bl ConvertUIntToDecimalString
	ldrh r1, [r7, #0x8]
	ldr r0, _0200BB10 ; =0x0000FFFF
	cmp r1, r0
	beq _0200BB0C
	add r4, r7, #0x0
	mov r5, #0x0
_0200BAD8:
	ldrh r2, [r4, #0x8]
	cmp r2, #0xa2
	blo _0200BAF6
	cmp r2, #0xab
	bhi _0200BAF6
	ldr r0, [r7, #0x4]
	sub r2, #0xa2
	ldr r1, [r0, #0x14]
	lsl r0, r2, #0x5
	add r0, r1, r0
	add r1, r6, r5
	mov r2, #0x20
	bl MIi_CpuCopy32
	b _0200BB00
_0200BAF6:
	ldr r1, [sp, #0x0]
	add r0, r6, r5
	mov r2, #0x20
	bl MI_CpuFill8
_0200BB00:
	add r4, r4, #0x2
	ldrh r1, [r4, #0x8]
	ldr r0, _0200BB10 ; =0x0000FFFF
	add r5, #0x20
	cmp r1, r0
	bne _0200BAD8
_0200BB0C:
	pop {r3-r7, pc}
	nop
_0200BB10: .word 0x0000FFFF
