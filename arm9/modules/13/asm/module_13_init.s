	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	thumb_func_start MOD13_02211E60
MOD13_02211E60: ; 0x02211E60
	push {r3, r4, r5, lr}
	add r4, r0, #0
	bl sub_0202E49C
	bl OS_InitTick
	bl OS_InitAlarm
	bl OS_DisableInterrupts
	mov r1, #1
	add r5, r0, #0
	add r0, r4, #0
	lsl r1, r1, #0x12
	bl AllocFromHeap
	add r4, r0, #0
	mov r1, #1
	mov r2, #0
	bl MOD13_02223494
	add r0, r4, #0
	bl FreeToHeap
	add r0, r5, #0
	bl OS_RestoreInterrupts
	ldr r1, _02211EA0 ; =0x04000208
	ldrh r0, [r1]
	mov r0, #1
	strh r0, [r1]
	pop {r3, r4, r5, pc}
	.align 2, 0
_02211EA0: .word 0x04000208
	.rodata
	.data
	.bss
