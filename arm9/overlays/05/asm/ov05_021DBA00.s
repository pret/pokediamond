	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start ov05_021DBA00
ov05_021DBA00: ; 0x021DBA00
	push {r4, lr}
	mov r0, #4
	mov r1, #0x38
	bl AllocFromHeap
	add r4, r0, #0
	mov r0, #0
	add r1, r4, #0
	mov r2, #0x38
	bl MIi_CpuClear32
	add r0, r4, #0
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021DBA1C
ov05_021DBA1C: ; 0x021DBA1C
	push {r4, lr}
	add r4, r0, #0
	ldr r1, [r4]
	mov r0, #4
	bl FreeToHeapExplicit
	mov r0, #0
	str r0, [r4]
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021DBA30
ov05_021DBA30: ; 0x021DBA30
	ldr r0, [r0]
	bx lr

	thumb_func_start ov05_021DBA34
ov05_021DBA34: ; 0x021DBA34
	ldr r0, [r0, #8]
	bx lr

	thumb_func_start ov05_021DBA38
ov05_021DBA38: ; 0x021DBA38
	ldr r0, [r0, #0xc]
	bx lr

	thumb_func_start ov05_021DBA3C
ov05_021DBA3C: ; 0x021DBA3C
	ldrh r0, [r0, #0x10]
	bx lr

	thumb_func_start ov05_021DBA40
ov05_021DBA40: ; 0x021DBA40
	push {r4, lr}
	add r4, r0, #0
	mov r0, #1
	tst r0, r1
	beq _021DBA4C
	str r2, [r4]
_021DBA4C:
	mov r0, #2
	tst r0, r1
	beq _021DBA54
	str r3, [r4, #4]
_021DBA54:
	mov r0, #4
	tst r0, r1
	beq _021DBA5E
	ldr r0, [sp, #8]
	str r0, [r4, #8]
_021DBA5E:
	mov r0, #8
	tst r0, r1
	beq _021DBA68
	ldr r0, [sp, #0xc]
	str r0, [r4, #0xc]
_021DBA68:
	ldr r0, [r4]
	ldr r1, [r4, #4]
	ldr r2, [r4, #8]
	ldr r3, [r4, #0xc]
	bl G3X_SetFog
	pop {r4, pc}
	.balign 4, 0

	thumb_func_start ov05_021DBA78
ov05_021DBA78: ; 0x021DBA78
	push {r3, r4}
	mov r4, #0x10
	tst r4, r1
	beq _021DBA82
	strh r2, [r0, #0x10]
_021DBA82:
	mov r2, #0x20
	tst r1, r2
	beq _021DBA8A
	str r3, [r0, #0x14]
_021DBA8A:
	ldrh r1, [r0, #0x10]
	ldr r0, [r0, #0x14]
	lsl r0, r0, #0x10
	orr r1, r0
	ldr r0, _021DBA9C ; =0x04000358
	str r1, [r0]
	pop {r3, r4}
	bx lr
	nop
_021DBA9C: .word 0x04000358

	thumb_func_start ov05_021DBAA0
ov05_021DBAA0: ; 0x021DBAA0
	push {r4, lr}
	add r4, r0, #0
	add r0, r1, #0
	add r1, r4, #0
	add r1, #0x18
	mov r2, #0x20
	bl MIi_CpuCopy32
	add r4, #0x18
	add r0, r4, #0
	bl G3X_SetFogTable
	pop {r4, pc}
	.balign 4, 0
