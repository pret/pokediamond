	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021D7F4C
ov05_021D7F4C: ; 0x021D7F4C
	push {r3, r4, r5, r6, r7, lr}
	add r5, r1, #0
	add r7, r0, #0
	add r0, r5, #0
	mov r1, #0x14
	add r6, r2, #0
	bl AllocFromHeap
	add r4, r0, #0
	str r7, [r4]
	str r5, [r4, #4]
	mov r0, #0x14
	add r7, r6, #0
	mul r7, r0
	str r6, [r4, #8]
	add r0, r5, #0
	add r1, r7, #0
	bl AllocFromHeap
	str r0, [r4, #0xc]
	ldr r1, [r4, #0xc]
	mov r0, #0
	add r2, r7, #0
	bl MIi_CpuClear32
	add r0, r6, #0
	bl sub_0201B578
	add r1, r0, #0
	add r0, r5, #0
	bl AllocFromHeap
	str r0, [r4, #0x10]
	ldr r1, [r4, #0x10]
	add r0, r6, #0
	bl sub_0201B580
	str r0, [r4, #0x10]
	add r0, r4, #0
	pop {r3, r4, r5, r6, r7, pc}

	thumb_func_start ov05_021D7F9C
ov05_021D7F9C: ; 0x021D7F9C
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r0, [r5, #8]
	mov r6, #0
	cmp r0, #0
	ble _021D7FBC
	add r4, r6, #0
_021D7FAA:
	ldr r0, [r5, #0xc]
	add r0, r0, r4
	bl ov05_021D80A4
	ldr r0, [r5, #8]
	add r6, r6, #1
	add r4, #0x14
	cmp r6, r0
	blt _021D7FAA
_021D7FBC:
	ldr r0, [r5, #0xc]
	bl FreeToHeap
	ldr r0, [r5, #0x10]
	bl FreeToHeap
	add r0, r5, #0
	bl FreeToHeap
	pop {r4, r5, r6, pc}

	thumb_func_start ov05_021D7FD0
ov05_021D7FD0: ; 0x021D7FD0
	ldr r3, _021D7FD8 ; =sub_0201B5CC
	ldr r0, [r0, #0x10]
	bx r3
	nop
_021D7FD8: .word sub_0201B5CC

	thumb_func_start ov05_021D7FDC
ov05_021D7FDC: ; 0x021D7FDC
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4]
	ldr r0, [r0]
	bl sub_020373AC
	cmp r0, #0
	beq _021D7FFE
	ldr r0, [r4, #0xc]
	ldr r3, [r0, #0x10]
	cmp r3, #0
	beq _021D7FFE
	ldr r1, [r4]
	ldr r2, [r4, #0x10]
	ldr r1, [r1]
	add r0, r4, #0
	blx r3
_021D7FFE:
	pop {r4, pc}

	thumb_func_start ov05_021D8000
ov05_021D8000: ; 0x021D8000
	push {r4, lr}
	add r4, r1, #0
	ldr r0, [r4]
	ldr r0, [r0]
	bl sub_020373AC
	cmp r0, #0
	beq _021D8022
	ldr r0, [r4, #0xc]
	ldr r3, [r0, #0x14]
	cmp r3, #0
	beq _021D8022
	ldr r1, [r4]
	ldr r2, [r4, #0x10]
	ldr r1, [r1]
	add r0, r4, #0
	blx r3
_021D8022:
	pop {r4, pc}

	thumb_func_start ov05_021D8024
ov05_021D8024: ; 0x021D8024
	push {r4, r5, r6, lr}
	add r5, r0, #0
	ldr r2, [r5, #8]
	add r6, r1, #0
	mov r1, #0
	ldr r4, [r5, #0xc]
	cmp r2, #0
	ble _021D8094
_021D8034:
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021D808C
	ldr r0, _021D809C ; =ov05_021D7FDC
	ldr r2, [r6]
	add r1, r4, #0
	bl SysTask_CreateOnMainQueue
	str r0, [r4, #4]
	ldr r0, [r5, #0x10]
	ldr r1, _021D80A0 ; =ov05_021D8000
	ldr r3, [r6]
	add r2, r4, #0
	bl sub_0201B60C
	str r0, [r4, #8]
	str r5, [r4]
	str r6, [r4, #0xc]
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _021D8062
	bl GF_AssertFail
_021D8062:
	ldr r0, [r4, #8]
	cmp r0, #0
	bne _021D806C
	bl GF_AssertFail
_021D806C:
	ldrh r1, [r6, #4]
	cmp r1, #0
	beq _021D807A
	ldr r0, [r5, #4]
	bl AllocFromHeap
	str r0, [r4, #0x10]
_021D807A:
	ldr r3, [r6, #8]
	cmp r3, #0
	beq _021D8088
	ldr r1, [r5]
	ldr r2, [r4, #0x10]
	add r0, r4, #0
	blx r3
_021D8088:
	add r0, r4, #0
	pop {r4, r5, r6, pc}
_021D808C:
	add r1, r1, #1
	add r4, #0x14
	cmp r1, r2
	blt _021D8034
_021D8094:
	bl GF_AssertFail
	mov r0, #0
	pop {r4, r5, r6, pc}
	.balign 4, 0
_021D809C: .word ov05_021D7FDC
_021D80A0: .word ov05_021D8000

	thumb_func_start ov05_021D80A4
ov05_021D80A4: ; 0x021D80A4
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4, #4]
	cmp r1, #0
	beq _021D80E2
	ldr r1, [r4, #0xc]
	ldr r3, [r1, #0xc]
	cmp r3, #0
	beq _021D80BE
	ldr r1, [r4]
	ldr r2, [r4, #0x10]
	ldr r1, [r1]
	blx r3
_021D80BE:
	ldr r0, [r4, #0xc]
	ldrh r0, [r0, #4]
	cmp r0, #0
	beq _021D80CC
	ldr r0, [r4, #0x10]
	bl FreeToHeap
_021D80CC:
	ldr r0, [r4, #4]
	bl sub_0200CAB4
	ldr r0, [r4, #8]
	bl sub_0200CAB4
	mov r0, #0
	add r1, r4, #0
	mov r2, #0x14
	bl MIi_CpuClear32
_021D80E2:
	pop {r4, pc}

	thumb_func_start ov05_021D80E4
ov05_021D80E4: ; 0x021D80E4
	ldr r0, [r0, #0x10]
	bx lr
