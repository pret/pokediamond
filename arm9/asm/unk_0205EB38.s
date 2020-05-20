    .include "asm/macros.inc"
    .include "global.inc"

	.extern UNK_020F73B0
	.extern UNK_020F73C8

	.text

	thumb_func_start FUN_0205EB38
FUN_0205EB38: ; 0x0205EB38
	push {r4-r7, lr}
	sub sp, #0x24
	ldr r3, _0205EBE0 ; =UNK_020F73B0
	add r2, sp, #0xc
	add r4, r0, #0x0
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	ldmia r3!, {r0-r1}
	stmia r2!, {r0-r1}
	mov r1, #0x5b
	add r0, r4, #0x0
	lsl r1, r1, #0x2
	bl FUN_02016998
	mov r2, #0x5b
	add r7, r0, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x2
	bl MI_CpuFill8
	add r0, r7, #0x0
	add r1, sp, #0xc
	mov r2, #0x2
	mov r3, #0xb
	bl MOD05_021D959C
	mov r0, #0x2
	str r0, [sp, #0x0]
	mov r0, #0x1
	str r0, [sp, #0x4]
	ldr r0, _0205EBE4 ; =0x000034D8
	mov r2, #0x0
	str r0, [sp, #0x8]
	add r0, r7, #0x0
	mov r1, #0x55
	add r3, r2, #0x0
	bl MOD05_021D967C
	ldr r0, _0205EBE4 ; =0x000034D8
	mov r1, #0x55
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	mov r2, #0x2
	mov r3, #0x0
	bl MOD05_021D96F4
	ldr r0, _0205EBE4 ; =0x000034D8
	mov r1, #0x55
	str r0, [sp, #0x0]
	add r0, r7, #0x0
	mov r2, #0x3
	mov r3, #0x0
	bl MOD05_021D9708
	mov r2, #0x1
	ldr r0, _0205EBE4 ; =0x000034D8
	str r2, [sp, #0x0]
	str r0, [sp, #0x4]
	add r0, r7, #0x0
	mov r1, #0x55
	mov r3, #0x0
	bl MOD05_021D971C
	ldr r4, _0205EBE8 ; =UNK_020F73C8
	mov r6, #0x0
	add r5, r7, #0x0
_0205EBC0:
	add r0, r7, #0x0
	add r1, r4, #0x0
	bl MOD05_021D9820
	mov r1, #0x59
	lsl r1, r1, #0x2
	str r0, [r5, r1]
	add r6, r6, #0x1
	add r4, #0x34
	add r5, r5, #0x4
	cmp r6, #0x2
	blo _0205EBC0
	add r0, r7, #0x0
	add sp, #0x24
	pop {r4-r7, pc}
	nop
_0205EBE0: .word UNK_020F73B0
_0205EBE4: .word 0x000034D8
_0205EBE8: .word UNK_020F73C8

	thumb_func_start FUN_0205EBEC
FUN_0205EBEC: ; 0x0205EBEC
	push {r3-r7, lr}
	add r7, r0, #0x0
	mov r6, #0x59
	mov r4, #0x0
	add r5, r7, #0x0
	lsl r6, r6, #0x2
_0205EBF8:
	ldr r0, [r5, r6]
	cmp r0, #0x0
	beq _0205EC02
	bl FUN_0200C3DC
_0205EC02:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x2
	blt _0205EBF8
	add r0, r7, #0x0
	bl MOD05_021D99F8
	add r0, r7, #0x0
	bl FUN_02016A18
	pop {r3-r7, pc}

	thumb_func_start FUN_0205EC18
FUN_0205EC18: ; 0x0205EC18
	push {r3-r7, lr}
	mov r7, #0x1
	mov r6, #0x59
	str r0, [sp, #0x0]
	mov r4, #0x0
	add r5, r0, #0x0
	lsl r7, r7, #0xc
	lsl r6, r6, #0x2
_0205EC28:
	ldr r0, [r5, r6]
	cmp r0, #0x0
	beq _0205EC36
	ldr r0, [r0, #0x0]
	add r1, r7, #0x0
	bl FUN_020201E4
_0205EC36:
	add r4, r4, #0x1
	add r5, r5, #0x4
	cmp r4, #0x2
	blt _0205EC28
	ldr r0, [sp, #0x0]
	ldr r0, [r0, #0x0]
	bl FUN_0201FDEC
	pop {r3-r7, pc}

	thumb_func_start FUN_0205EC48
FUN_0205EC48: ; 0x0205EC48
	push {r4-r6, lr}
	add r5, r0, #0x0
	mov r0, #0x59
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r4, r1, #0x0
	add r6, r3, #0x0
	bl FUN_0200C714
	mov r0, #0x5a
	lsl r0, r0, #0x2
	ldr r0, [r5, r0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0200C714
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0205EC6C
FUN_0205EC6C: ; 0x0205EC6C
	push {r3, lr}
	cmp r1, #0x2
	bhs _0205EC82
	lsl r1, r1, #0x2
	add r1, r0, r1
	mov r0, #0x59
	lsl r0, r0, #0x2
	ldr r0, [r1, r0]
	add r1, r2, #0x0
	bl FUN_0200C644
_0205EC82:
	pop {r3, pc}
