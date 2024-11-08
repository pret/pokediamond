	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021F46C8
ov05_021F46C8: ; 0x021F46C8
	push {r4, r5, r6, lr}
	add r5, r1, #0
	mov r1, #0xca
	lsl r1, r1, #2
	add r6, r0, #0
	bl AllocFromHeap
	mov r2, #0xca
	mov r1, #0
	lsl r2, r2, #2
	add r4, r0, #0
	bl memset
	mov r2, #0x63
	mov r0, #0
	add r1, r4, #0
	lsl r2, r2, #2
	str r0, [r4]
	add r0, r6, #0
	add r1, #0xc
	add r2, r4, r2
	bl sub_02012944
	mov r1, #0xc3
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r1, #4
	str r5, [r4, r0]
	add r0, r4, #0
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021F4704
ov05_021F4704: ; 0x021F4704
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	cmp r1, #1
	bne _021F4712
	bl ov05_021F491C
_021F4712:
	mov r0, #0xc3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl sub_02012974
	add r0, r4, #0
	bl FreeToHeap
	pop {r4, pc}

	thumb_func_start ov05_021F4724
ov05_021F4724: ; 0x021F4724
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #0
	beq _021F4732
	bl GF_AssertFail
_021F4732:
	mov r0, #0x31
	lsl r0, r0, #4
	ldr r0, [r4, r0]
	ldr r1, _021F47A4 ; =ov05_021F48CC
	add r2, r4, #0
	bl ov05_021F4624
	mov r2, #0xc5
	lsl r2, r2, #2
	str r0, [r4, r2]
	ldr r0, _021F47A8 ; =ov05_021F47B4
	add r1, r4, #0
	add r2, #0xec
	bl SysTask_CreateOnMainQueue
	mov r2, #0xc7
	lsl r2, r2, #2
	str r0, [r4, r2]
	ldr r0, _021F47AC ; =ov05_021F48BC
	add r1, r4, #0
	add r2, #0xe4
	bl sub_0200CA60
	mov r2, #0x32
	lsl r2, r2, #4
	str r0, [r4, r2]
	ldr r0, _021F47B0 ; =ov05_021F48F0
	add r1, r4, #0
	add r2, #0xe0
	bl sub_0200CA60
	mov r1, #0xc9
	lsl r1, r1, #2
	str r0, [r4, r1]
	add r0, r4, #0
	mov r2, #6
	add r0, #0xc
	mov r1, #0
	lsl r2, r2, #6
	bl memset
	mov r2, #0x63
	lsl r2, r2, #2
	add r0, r4, r2
	mov r1, #0
	sub r2, #0xc
	bl memset
	mov r0, #1
	str r0, [r4]
	mov r0, #0
	str r0, [r4, #8]
	mov r0, #0x61
	lsl r0, r0, #4
	bl PlaySE
	pop {r4, pc}
	.balign 4, 0
_021F47A4: .word ov05_021F48CC
_021F47A8: .word ov05_021F47B4
_021F47AC: .word ov05_021F48BC
_021F47B0: .word ov05_021F48F0

	thumb_func_start ov05_021F47B4
ov05_021F47B4: ; 0x021F47B4
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4, #8]
	cmp r0, #3
	bhi _021F483C
	add r0, r0, r0
	add r0, pc
	ldrh r0, [r0, #6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_021F47CA: ; jump table
	.short _021F47D2 - _021F47CA - 2 ; case 0
	.short _021F47DE - _021F47CA - 2 ; case 1
	.short _021F480A - _021F47CA - 2 ; case 2
	.short _021F4830 - _021F47CA - 2 ; case 3
_021F47D2:
	mov r0, #3
	str r0, [r4, #4]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r4, pc}
_021F47DE:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0xc3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl sub_02012988
	ldr r1, [r4, #4]
	mov r2, #3
	sub r1, r2, r1
	bl ov05_021F4878
	ldr r0, [r4, #4]
	cmp r0, #0
	bgt _021F483C
	mov r0, #3
	str r0, [r4, #4]
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r4, pc}
_021F480A:
	ldr r0, [r4, #4]
	sub r0, r0, #1
	str r0, [r4, #4]
	mov r0, #0xc3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl sub_02012988
	ldr r1, [r4, #4]
	mov r2, #3
	bl ov05_021F4878
	ldr r0, [r4, #4]
	cmp r0, #0
	bgt _021F483C
	ldr r0, [r4, #8]
	add r0, r0, #1
	str r0, [r4, #8]
	pop {r4, pc}
_021F4830:
	add r0, r4, #0
	bl ov05_021F491C
	mov r0, #0
	bl G3X_SetHOffset
_021F483C:
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021F4840
ov05_021F4840: ; 0x021F4840
	push {r4, lr}
	ldr r1, _021F4870 ; =0x04000006
	ldrh r4, [r1]
	mov r1, #0xc3
	lsl r1, r1, #2
	ldr r0, [r0, r1]
	bl sub_0201299C
	cmp r4, #0xc0
	bge _021F486E
	add r3, r4, #1
	cmp r3, #0xc0
	blt _021F485C
	sub r3, #0xc0
_021F485C:
	ldr r1, _021F4874 ; =0x04000004
	ldrh r2, [r1]
	mov r1, #2
	tst r1, r2
	beq _021F486E
	lsl r1, r3, #1
	ldrh r0, [r0, r1]
	bl G3X_SetHOffset
_021F486E:
	pop {r4, pc}
	.balign 4, 0
_021F4870: .word 0x04000006
_021F4874: .word 0x04000004

	thumb_func_start ov05_021F4878
ov05_021F4878: ; 0x021F4878
	push {r3, r4, r5, r6, r7, lr}
	add r5, r0, #0
	lsl r0, r1, #1
	add r0, r1, r0
	add r1, r2, #0
	mov r4, #1
	bl _s32_div_f
	neg r1, r0
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsl r0, r0, #0x10
	mov r6, #0
	str r1, [sp]
	lsr r7, r0, #0x10
_021F4896:
	add r0, r6, #0
	mov r1, #0xa
	bl _s32_div_f
	cmp r1, #0
	bne _021F48A6
	mov r0, #1
	eor r4, r0
_021F48A6:
	cmp r4, #0
	beq _021F48AE
	strh r7, [r5]
	b _021F48B2
_021F48AE:
	ldr r0, [sp]
	strh r0, [r5]
_021F48B2:
	add r6, r6, #1
	add r5, r5, #2
	cmp r6, #0xc0
	blt _021F4896
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021F48BC
ov05_021F48BC: ; 0x021F48BC
	mov r2, #0xc6
	ldr r3, _021F48C8 ; =G3X_SetHOffset
	mov r0, #0
	lsl r2, r2, #2
	str r0, [r1, r2]
	bx r3
	.balign 4, 0
_021F48C8: .word G3X_SetHOffset

	thumb_func_start ov05_021F48CC
ov05_021F48CC: ; 0x021F48CC
	ldr r3, _021F48D4 ; =ov05_021F48D8
	add r0, r1, #0
	bx r3
	nop
_021F48D4: .word ov05_021F48D8

	thumb_func_start ov05_021F48D8
ov05_021F48D8: ; 0x021F48D8
	push {r3, lr}
	ldr r1, [r0]
	cmp r1, #1
	bne _021F48EE
	mov r1, #0xc6
	lsl r1, r1, #2
	ldr r1, [r0, r1]
	cmp r1, #1
	bne _021F48EE
	bl ov05_021F4840
_021F48EE:
	pop {r3, pc}

	thumb_func_start ov05_021F48F0
ov05_021F48F0: ; 0x021F48F0
	ldr r3, _021F48F8 ; =ov05_021F48FC
	add r0, r1, #0
	bx r3
	nop
_021F48F8: .word ov05_021F48FC

	thumb_func_start ov05_021F48FC
ov05_021F48FC: ; 0x021F48FC
	push {r4, lr}
	add r4, r0, #0
	ldr r0, [r4]
	cmp r0, #1
	bne _021F4918
	mov r0, #0xc3
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl sub_020129B4
	mov r0, #0xc6
	mov r1, #1
	lsl r0, r0, #2
	str r1, [r4, r0]
_021F4918:
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021F491C
ov05_021F491C: ; 0x021F491C
	push {r4, lr}
	add r4, r0, #0
	mov r0, #0xc5
	lsl r0, r0, #2
	ldr r0, [r4, r0]
	bl ov05_021F4648
	mov r0, #0xc5
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, #8
	ldr r0, [r4, r0]
	bl SysTask_Destroy
	mov r0, #0xc7
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	add r0, r0, #4
	ldr r0, [r4, r0]
	bl SysTask_Destroy
	mov r0, #0x32
	mov r1, #0
	lsl r0, r0, #4
	str r1, [r4, r0]
	add r0, r0, #4
	ldr r0, [r4, r0]
	bl SysTask_Destroy
	mov r0, #0xc9
	mov r1, #0
	lsl r0, r0, #2
	str r1, [r4, r0]
	str r1, [r4]
	pop {r4, pc}
	.balign 4, 0
