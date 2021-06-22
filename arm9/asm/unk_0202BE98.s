	.include "asm/macros.inc"
	.include "global.inc"

	.text

	thumb_func_start FUN_0202BE98
FUN_0202BE98: ; 0x0202BE98
	ldr r0, _0202BE9C ; =0x00000688
	bx lr
	.balign 4
_0202BE9C: .word 0x00000688

	thumb_func_start FUN_0202BEA0
FUN_0202BEA0: ; 0x0202BEA0
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r2, _0202BED8 ; =0x00000688
	mov r0, #0x0
	add r1, r5, #0x0
	bl MIi_CpuClearFast
	mov r4, #0x0
	mov r6, #0xab
	add r7, r4, #0x0
_0202BEB4:
	add r0, r5, #0x0
	bl ZeroMonData
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _0202BECC
	bl GF_AssertFail
_0202BECC:
	add r4, r4, #0x1
	add r5, #0xec
	cmp r4, #0x6
	blt _0202BEB4
	pop {r3-r7, pc}
	nop
_0202BED8: .word 0x00000688

	thumb_func_start FUN_0202BEDC
FUN_0202BEDC: ; 0x0202BEDC
	push {r3-r7, lr}
	add r5, r0, #0x0
	ldr r2, _0202BF14 ; =0x00000588
	mov r0, #0x0
	add r1, r5, #0x0
	bl MIi_CpuClearFast
	mov r4, #0x0
	mov r6, #0xab
	add r7, r4, #0x0
_0202BEF0:
	add r0, r5, #0x0
	bl ZeroMonData
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r7, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _0202BF08
	bl GF_AssertFail
_0202BF08:
	add r4, r4, #0x1
	add r5, #0xec
	cmp r4, #0x6
	blt _0202BEF0
	pop {r3-r7, pc}
	nop
_0202BF14: .word 0x00000588

	thumb_func_start FUN_0202BF18
FUN_0202BF18: ; 0x0202BF18
	push {r4-r7}
	add r2, r0, #0x0
	ldr r3, _0202BF70 ; =0x00000588
	mov r0, #0x0
	add r5, r2, #0x0
_0202BF22:
	ldr r4, [r5, r3]
	cmp r1, r4
	beq _0202BF6C
	add r0, r0, #0x1
	add r5, r5, #0x4
	cmp r0, #0x14
	blt _0202BF22
	ldr r1, _0202BF70 ; =0x00000588
	mov r0, #0x0
	add r4, r2, #0x0
_0202BF36:
	ldr r3, [r4, r1]
	cmp r3, #0x0
	beq _0202BF6C
	add r0, r0, #0x1
	add r4, r4, #0x4
	cmp r0, #0x14
	blt _0202BF36
	mov r3, #0x0
	ldr r4, _0202BF74 ; =0x7FFFFFFF
	add r5, r3, #0x0
_0202BF4A:
	ldr r0, _0202BF78 ; =0x000005D8
	ldr r1, [r2, r0]
	add r0, r0, #0x4
	ldr r0, [r2, r0]
	sub r6, r1, r4
	mov r12, r0
	mov r6, r12
	sbc r6, r3
	bge _0202BF62
	add r4, r1, #0x0
	add r3, r0, #0x0
	add r7, r5, #0x0
_0202BF62:
	add r5, r5, #0x1
	add r2, #0x8
	cmp r5, #0x14
	blt _0202BF4A
	add r0, r7, #0x0
_0202BF6C:
	pop {r4-r7}
	bx lr
	.balign 4
_0202BF70: .word 0x00000588
_0202BF74: .word 0x7FFFFFFF
_0202BF78: .word 0x000005D8

	thumb_func_start FUN_0202BF7C
FUN_0202BF7C: ; 0x0202BF7C
	add r3, r0, #0x0
	add r0, r1, #0x0
	mov r1, #0xec
	mul r1, r2
	add r1, r3, r1
	ldr r3, _0202BF8C ; =CopyBoxPokemonToPokemon
	bx r3
	nop
_0202BF8C: .word CopyBoxPokemonToPokemon

	thumb_func_start FUN_0202BF90
FUN_0202BF90: ; 0x0202BF90
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl FUN_0202BF18
	add r6, r0, #0x0
	lsl r0, r6, #0x2
	add r1, r5, r0
	ldr r0, _0202BFCC ; =0x00000588
	str r4, [r1, r0]
	bl GF_RTC_DateTimeToSec
	lsl r2, r6, #0x3
	add r3, r5, r2
	ldr r2, _0202BFD0 ; =0x000005D8
	str r0, [r3, r2]
	add r0, r2, #0x4
	str r1, [r3, r0]
	bl OS_GetOwnerRtcOffset
	ldr r2, _0202BFD4 ; =0x00000678
	str r0, [r5, r2]
	add r0, r2, #0x4
	add r2, #0x8
	str r1, [r5, r0]
	add r0, r5, r2
	bl OS_GetMacAddress
	pop {r4-r6, pc}
	nop
_0202BFCC: .word 0x00000588
_0202BFD0: .word 0x000005D8
_0202BFD4: .word 0x00000678

	thumb_func_start FUN_0202BFD8
FUN_0202BFD8: ; 0x0202BFD8
	push {r4-r6, lr}
	add r5, r1, #0x0
	add r6, r0, #0x0
	add r4, r2, #0x0
	cmp r5, #0x6
	blt _0202BFE8
	bl GF_AssertFail
_0202BFE8:
	mov r0, #0xec
	mul r0, r5
	add r3, r6, r0
	mov r2, #0x1d
_0202BFF0:
	ldmia r3!, {r0-r1}
	stmia r4!, {r0-r1}
	sub r2, r2, #0x1
	bne _0202BFF0
	ldr r0, [r3, #0x0]
	str r0, [r4, #0x0]
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202C000
FUN_0202C000: ; 0x0202C000
	push {r3-r7, lr}
	mov r4, #0x0
	add r5, r0, #0x0
	add r6, r4, #0x0
	mov r7, #0xab
_0202C00A:
	add r0, r5, #0x0
	add r1, r7, #0x0
	mov r2, #0x0
	bl GetMonData
	cmp r0, #0x0
	beq _0202C01A
	add r4, r4, #0x1
_0202C01A:
	add r6, r6, #0x1
	add r5, #0xec
	cmp r6, #0x6
	blt _0202C00A
	add r0, r4, #0x0
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202C028
FUN_0202C028: ; 0x0202C028
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	bl GF_RTC_DateTimeToSec
	ldr r1, _0202C058 ; =0x00000588
	mov r3, #0x0
	add r6, r5, #0x0
_0202C038:
	ldr r2, [r6, r1]
	cmp r4, r2
	bne _0202C04A
	lsl r1, r3, #0x3
	add r2, r5, r1
	ldr r1, _0202C05C ; =0x000005D8
	ldr r1, [r2, r1]
	sub r0, r0, r1
	pop {r4-r6, pc}
_0202C04A:
	add r3, r3, #0x1
	add r6, r6, #0x4
	cmp r3, #0x14
	blt _0202C038
	mov r0, #0x0
	pop {r4-r6, pc}
	nop
_0202C058: .word 0x00000588
_0202C05C: .word 0x000005D8

	thumb_func_start FUN_0202C060
FUN_0202C060: ; 0x0202C060
	push {r3-r5, lr}
	sub sp, #0x8
	add r4, r0, #0x0
	add r0, sp, #0x0
	bl OS_GetMacAddress
	mov r0, #0x1a
	mov r3, #0x0
	add r5, sp, #0x0
	lsl r0, r0, #0x6
_0202C074:
	add r1, r4, r3
	ldrb r2, [r5, #0x0]
	ldrb r1, [r1, r0]
	cmp r2, r1
	beq _0202C084
	add sp, #0x8
	mov r0, #0x0
	pop {r3-r5, pc}
_0202C084:
	add r3, r3, #0x1
	add r5, r5, #0x1
	cmp r3, #0x6
	blt _0202C074
	mov r0, #0x1
	add sp, #0x8
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0202C094
FUN_0202C094: ; 0x0202C094
	push {r4, lr}
	add r4, r0, #0x0
	bl OS_GetOwnerRtcOffset
	ldr r2, _0202C0B4 ; =0x00000678
	ldr r3, [r4, r2]
	add r2, r2, #0x4
	ldr r2, [r4, r2]
	eor r0, r3
	eor r1, r2
	orr r0, r1
	bne _0202C0B0
	mov r0, #0x1
	pop {r4, pc}
_0202C0B0:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
_0202C0B4: .word 0x00000678

	thumb_func_start FUN_0202C0B8
FUN_0202C0B8: ; 0x0202C0B8
	push {r3-r4}
	mov r4, #0x0
	mov r1, #0x1a
	add r3, r4, #0x0
	lsl r1, r1, #0x6
_0202C0C2:
	add r2, r0, r3
	ldrb r2, [r2, r1]
	add r3, r3, #0x1
	orr r4, r2
	cmp r3, #0x6
	blt _0202C0C2
	cmp r4, #0x0
	bne _0202C0D8
	mov r0, #0x1
	pop {r3-r4}
	bx lr
_0202C0D8:
	mov r0, #0x0
	pop {r3-r4}
	bx lr
	.balign 4
