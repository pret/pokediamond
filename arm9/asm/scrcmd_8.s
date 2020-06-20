    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02041C38
FUN_02041C38: ; 0x02041C38
	push {r4-r7, lr}
	sub sp, #0xc
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	mov r1, #0xf
	bl FUN_02039438
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_0202881C
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r7, [r0, #0xc]
	add r0, r4, #0x0
	bl ScriptReadHalfword
	cmp r0, #0x6
	bls _02041C6C
	b _02041E38
_02041C6C:
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_02041C78: ; jump table (using 16-bit offset)
	.short _02041C86 - _02041C78 - 2; case 0
	.short _02041CBC - _02041C78 - 2; case 1
	.short _02041CF2 - _02041C78 - 2; case 2
	.short _02041D28 - _02041C78 - 2; case 3
	.short _02041D5E - _02041C78 - 2; case 4
	.short _02041D94 - _02041C78 - 2; case 5
	.short _02041DCE - _02041C78 - 2; case 6
_02041C86:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02028828
	strh r0, [r4, #0x0]
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02041CBC:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02028840
	strh r0, [r4, #0x0]
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02041CF2:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r3, r0, #0x0
	mov r0, #0x0
	str r0, [sp, #0x0]
	ldr r0, [r6, #0x0]
	add r1, r7, #0x0
	add r2, r5, #0x0
	bl FUN_0200B708
	b _02041E38
_02041D28:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394F0
	add r3, r0, #0x0
	mov r0, #0x1
	str r0, [sp, #0x0]
	ldr r0, [r6, #0x0]
	add r1, r7, #0x0
	add r2, r5, #0x0
	bl FUN_0200B708
	b _02041E38
_02041D5E:
	mov r1, #0x0
	add r0, r5, #0x0
	add r2, r1, #0x0
	bl FUN_020287A8
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	mov r2, #0x0
	str r2, [sp, #0x0]
	str r5, [sp, #0x4]
	str r0, [sp, #0x8]
	ldr r0, [r4, #0x74]
	mov r1, #0x5
	mov r3, #0x7
	bl FUN_020385CC
	add sp, #0xc
	mov r0, #0x1
	pop {r4-r7, pc}
_02041D94:
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r7, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x1
	bl FUN_02028828
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x1
	bl FUN_02028700
	cmp r6, #0x0
	beq _02041DC8
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_020612F8
_02041DC8:
	add sp, #0xc
	mov r0, #0x0
	pop {r4-r7, pc}
_02041DCE:
	mov r0, #0x40
	mov r1, #0x20
	bl String_ctor
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	add r1, r6, #0x0
	add r7, r0, #0x0
	bl FUN_02023990
	add r0, r5, #0x0
	mov r1, #0x0
	mov r2, #0x1
	add r3, r6, #0x0
	bl FUN_020287C0
	add r0, r7, #0x0
	bl FUN_020239CC
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_020287EC
	add r0, r5, #0x0
	mov r1, #0x0
	mov r2, #0x2
	bl FUN_02028810
	bl MTRandom
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_02028788
	add r0, r6, #0x0
	bl String_dtor
	add r0, r5, #0x0
	mov r1, #0x0
	mov r2, #0x1
	bl FUN_02028700
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_020612EC
_02041E38:
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4
