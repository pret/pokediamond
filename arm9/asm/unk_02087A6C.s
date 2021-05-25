    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020FD144
UNK_020FD144: ; 0x020FD144
	.word MOD59_Init, MOD59_021D7564, MOD59_021D76C0, SDK_OVERLAY_MODULE_59_ID

	.text

	thumb_func_start FUN_02087A6C
FUN_02087A6C: ; 0x02087A6C
	push {r3, lr}
	mov r1, #0x18
	bl AllocFromHeap
	add r3, r0, #0x0
	mov r2, #0x18
	mov r1, #0x0
_02087A7A:
	strb r1, [r3, #0x0]
	add r3, r3, #0x1
	sub r2, r2, #0x1
	bne _02087A7A
	pop {r3, pc}

	thumb_func_start FUN_02087A84
FUN_02087A84: ; 0x02087A84
	push {r4, lr}
	add r4, r0, #0x0
	bne _02087A8E
	bl GF_AssertFail
_02087A8E:
	add r0, r4, #0x0
	bl FreeToHeap
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02087A98
FUN_02087A98: ; 0x02087A98
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r6, r1, #0x0
	add r4, r2, #0x0
	cmp r5, #0x0
	bne _02087AA8
	bl GF_AssertFail
_02087AA8:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	beq _02087AB2
	bl GF_AssertFail
_02087AB2:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	beq _02087ABC
	bl GF_AssertFail
_02087ABC:
	add r0, r4, #0x0
	bl FUN_02087C18
	str r0, [r5, #0x0]
	add r0, r4, #0x0
	bl FUN_02087C2C
	str r0, [r5, #0x4]
	cmp r6, #0x0
	bne _02087AEE
	add r0, r5, #0x0
	add r1, r5, #0x0
	add r0, #0x8
	add r1, #0xc
	add r2, r4, #0x0
	bl FUN_02087C40
	add r0, r5, #0x0
	add r5, #0x14
	add r0, #0x10
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02087CA0
	pop {r4-r6, pc}
_02087AEE:
	add r0, r5, #0x0
	add r1, r5, #0x0
	add r0, #0x8
	add r1, #0xc
	add r2, r4, #0x0
	bl FUN_02087C70
	add r0, r5, #0x0
	add r5, #0x14
	add r0, #0x10
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_02087CD0
	pop {r4-r6, pc}

	thumb_func_start FUN_02087B0C
FUN_02087B0C: ; 0x02087B0C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r0, [r4, #0x0]
	cmp r0, #0x0
	bne _02087B1A
	bl GF_AssertFail
_02087B1A:
	ldr r0, [r4, #0x4]
	cmp r0, #0x0
	bne _02087B24
	bl GF_AssertFail
_02087B24:
	ldr r0, [r4, #0x0]
	bl FreeToHeap
	ldr r0, [r4, #0x4]
	bl FreeToHeap
	ldr r0, [r4, #0x8]
	bl FreeToHeap
	ldr r0, [r4, #0xc]
	bl FreeToHeap
	ldr r0, [r4, #0x10]
	bl FreeToHeap
	ldr r0, [r4, #0x14]
	bl FreeToHeap
	mov r0, #0x0
	str r0, [r4, #0x0]
	str r0, [r4, #0x4]
	str r0, [r4, #0x8]
	str r0, [r4, #0xc]
	str r0, [r4, #0x10]
	str r0, [r4, #0x14]
	pop {r4, pc}

	thumb_func_start FUN_02087B58
FUN_02087B58: ; 0x02087B58
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02087B66
	bl GF_AssertFail
_02087B66:
	ldr r0, [r5, #0x0]
	cmp r0, #0x0
	bne _02087B70
	bl GF_AssertFail
_02087B70:
	ldr r1, [r5, #0x0]
	lsl r0, r4, #0x2
	ldr r0, [r1, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02087B78
FUN_02087B78: ; 0x02087B78
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02087B86
	bl GF_AssertFail
_02087B86:
	ldr r0, [r5, #0x4]
	cmp r0, #0x0
	bne _02087B90
	bl GF_AssertFail
_02087B90:
	ldr r1, [r5, #0x4]
	lsl r0, r4, #0x2
	ldr r0, [r1, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02087B98
FUN_02087B98: ; 0x02087B98
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02087BA6
	bl GF_AssertFail
_02087BA6:
	ldr r0, [r5, #0x8]
	cmp r0, #0x0
	bne _02087BB0
	bl GF_AssertFail
_02087BB0:
	ldr r1, [r5, #0x8]
	lsl r0, r4, #0x1
	ldrsh r0, [r1, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02087BB8
FUN_02087BB8: ; 0x02087BB8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02087BC6
	bl GF_AssertFail
_02087BC6:
	ldr r0, [r5, #0xc]
	cmp r0, #0x0
	bne _02087BD0
	bl GF_AssertFail
_02087BD0:
	ldr r1, [r5, #0xc]
	lsl r0, r4, #0x1
	ldrsh r0, [r1, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02087BD8
FUN_02087BD8: ; 0x02087BD8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02087BE6
	bl GF_AssertFail
_02087BE6:
	ldr r0, [r5, #0x10]
	cmp r0, #0x0
	bne _02087BF0
	bl GF_AssertFail
_02087BF0:
	ldr r1, [r5, #0x10]
	lsl r0, r4, #0x1
	ldrsh r0, [r1, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02087BF8
FUN_02087BF8: ; 0x02087BF8
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	cmp r5, #0x0
	bne _02087C06
	bl GF_AssertFail
_02087C06:
	ldr r0, [r5, #0x14]
	cmp r0, #0x0
	bne _02087C10
	bl GF_AssertFail
_02087C10:
	ldr r1, [r5, #0x14]
	lsl r0, r4, #0x1
	ldrsh r0, [r1, r0]
	pop {r3-r5, pc}

	thumb_func_start FUN_02087C18
FUN_02087C18: ; 0x02087C18
	push {r3, lr}
	mov r1, #0x0
	add r3, r0, #0x0
	mov r0, #0x4b
	add r2, r1, #0x0
	str r1, [sp, #0x0]
	bl UncompressFromNarc
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02087C2C
FUN_02087C2C: ; 0x02087C2C
	push {r3, lr}
	add r3, r0, #0x0
	mov r2, #0x0
	mov r0, #0x4b
	mov r1, #0x1
	str r2, [sp, #0x0]
	bl UncompressFromNarc
	pop {r3, pc}
	.balign 4

	thumb_func_start FUN_02087C40
FUN_02087C40: ; 0x02087C40
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r2, #0x0
	mov r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x4b
	mov r1, #0x9
	add r3, r6, #0x0
	bl UncompressFromNarc
	str r0, [r5, #0x0]
	mov r2, #0x0
	mov r0, #0x4b
	mov r1, #0xa
	add r3, r6, #0x0
	str r2, [sp, #0x0]
	bl UncompressFromNarc
	str r0, [r4, #0x0]
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02087C70
FUN_02087C70: ; 0x02087C70
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r2, #0x0
	mov r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x4b
	mov r1, #0x7
	add r3, r6, #0x0
	bl UncompressFromNarc
	str r0, [r5, #0x0]
	mov r2, #0x0
	mov r0, #0x4b
	mov r1, #0x8
	add r3, r6, #0x0
	str r2, [sp, #0x0]
	bl UncompressFromNarc
	str r0, [r4, #0x0]
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02087CA0
FUN_02087CA0: ; 0x02087CA0
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r2, #0x0
	mov r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x4b
	mov r1, #0x5
	add r3, r6, #0x0
	bl UncompressFromNarc
	str r0, [r5, #0x0]
	mov r2, #0x0
	mov r0, #0x4b
	mov r1, #0x6
	add r3, r6, #0x0
	str r2, [sp, #0x0]
	bl UncompressFromNarc
	str r0, [r4, #0x0]
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4

	thumb_func_start FUN_02087CD0
FUN_02087CD0: ; 0x02087CD0
	push {r3-r6, lr}
	sub sp, #0x4
	add r6, r2, #0x0
	mov r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	str r2, [sp, #0x0]
	mov r0, #0x4b
	mov r1, #0x3
	add r3, r6, #0x0
	bl UncompressFromNarc
	str r0, [r5, #0x0]
	mov r2, #0x0
	mov r0, #0x4b
	mov r1, #0x4
	add r3, r6, #0x0
	str r2, [sp, #0x0]
	bl UncompressFromNarc
	str r0, [r4, #0x0]
	add sp, #0x4
	pop {r3-r6, pc}
	.balign 4
