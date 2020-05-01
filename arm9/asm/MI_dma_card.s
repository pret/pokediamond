    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start MIi_CardDmaCopy32
MIi_CardDmaCopy32: ; 0x020CE5BC
	stmdb sp!, {r4-r7,lr}
	sub sp, sp, #0x4
	mov r5, r1
	mov r6, r0
	mov r7, r3
	mvn r1, #0x0
	mov r4, r2
	bl MIi_CheckAnotherAutoDMA
	mov r0, r6
	mov r1, r5
	mov r2, r7
	mov r3, #0x1000000
	bl MIi_CheckDma0SourceAddress
_020CE5F0:
	cmp r7, #0x0
	addeq sp, sp, #0x4
	ldmeqia sp!, {r4-r7, lr}
	bxeq lr
	mov r0, #0x3
	mul r1, r6, r0
	ldr r0, _020CE640
	add r1, r1, #0x2
	add r1, r0, r1, lsl #0x2
_020CE614:
	ldr r0, [r1]
	ands r0, r0, #0x80000000
	bne _020CE614
	ldr r3, _020CE644
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl MIi_DmaSetParams
	add sp, sp, #0x4
	ldmia sp!, {r4-r7, lr}
	bx lr
_020CE640: .word 0x040000B0
_020CE644: .word 0xAf000001
