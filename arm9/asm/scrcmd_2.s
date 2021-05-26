    .include "asm/macros.inc"
    .include "global.inc"

    .extern UNK_02105DEC
    .extern UNK_02105DF4
    .extern UNK_02105E10

	.text

	thumb_func_start FUN_0203FDBC
FUN_0203FDBC: ; 0x0203FDBC
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r2, r0, #0x0
	ldr r0, _0203FE00 ; =0x0000FFF8
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	cmp r0, #0x5
	bhi _0203FDE4
	mov r0, #0x1
	b _0203FDE6
_0203FDE4:
	mov r0, #0x0
_0203FDE6:
	lsl r3, r2, #0x2
	str r0, [sp, #0x0]
	ldr r2, _0203FE04 ; =UNK_02105E10
	ldr r0, [r4, #0x74]
	add r4, #0x80
	ldr r2, [r2, r3]
	ldr r1, [r4, #0x0]
	mov r3, #0x0
	bl MOD06_0223D3D0
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0203FE00: .word 0x0000FFF8
_0203FE04: .word UNK_02105E10

	thumb_func_start FUN_0203FE08
FUN_0203FE08: ; 0x0203FE08
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r2, r0, #0x0
	cmp r2, #0x1
	bhi _0203FE28
	mov r0, #0x1
	b _0203FE2A
_0203FE28:
	mov r0, #0x0
_0203FE2A:
	lsl r3, r2, #0x2
	str r0, [sp, #0x0]
	ldr r2, _0203FE44 ; =UNK_02105DEC
	ldr r0, [r4, #0x74]
	add r4, #0x80
	ldr r2, [r2, r3]
	ldr r1, [r4, #0x0]
	mov r3, #0x1
	bl MOD06_0223D3D0
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0203FE44: .word UNK_02105DEC

	thumb_func_start FUN_0203FE48
FUN_0203FE48: ; 0x0203FE48
	push {r3-r4, lr}
	sub sp, #0x4
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl VarGet
	add r2, r0, #0x0
	mov r0, #0x0
	lsl r3, r2, #0x2
	str r0, [sp, #0x0]
	ldr r2, _0203FE7C ; =UNK_02105DF4
	ldr r0, [r4, #0x74]
	add r4, #0x80
	ldr r2, [r2, r3]
	ldr r1, [r4, #0x0]
	mov r3, #0x2
	bl MOD06_0223D3D0
	mov r0, #0x1
	add sp, #0x4
	pop {r3-r4, pc}
	.balign 4
_0203FE7C: .word UNK_02105DF4

	thumb_func_start FUN_0203FE80
FUN_0203FE80: ; 0x0203FE80
	push {r3, lr}
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0x10]
	bl FUN_02038AD0
	mov r0, #0x1
	pop {r3, pc}
