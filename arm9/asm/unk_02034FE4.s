	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02034FE4
FUN_02034FE4: ; 0x02034FE4
	push {r3-r7, lr}
	add r7, r0, #0x0
	add r0, r1, #0x0
	bl FUN_02034838
	add r4, r0, #0x0
	cmp r4, #0x18
	blt _0203505C
	ldr r0, [r7, #0xc]
	bl FUN_02023794
	add r6, r0, #0x0
	add r0, r6, #0x4
	bl FUN_02012710
	sub r5, r0, #0x1
	bmi _0203500C
	ldr r0, _02035060 ; =0x0000016E
	cmp r5, r0
	blt _02035010
_0203500C:
	bl ErrorHandling
_02035010:
	ldr r0, [r6, #0x8]
	cmp r0, #0x2
	bls _02035044
	ldr r6, [r6, #0x4]
	mov r0, #0x3
	tst r0, r6
	bne _0203502A
	add r0, r6, #0x0
	mov r1, #0x64
	bl _u32_div_f
	cmp r1, #0x0
	bne _02035038
_0203502A:
	mov r1, #0x19
	add r0, r6, #0x0
	lsl r1, r1, #0x4
	bl _u32_div_f
	cmp r1, #0x0
	bne _0203503C
_02035038:
	mov r0, #0x1
	b _0203503E
_0203503C:
	mov r0, #0x0
_0203503E:
	cmp r0, #0x0
	bne _02035044
	add r5, r5, #0x1
_02035044:
	add r0, r7, #0x0
	bl FUN_0204B33C
	cmp r0, #0x0
	beq _02035050
	mov r5, #0x1
_02035050:
	lsl r0, r5, #0x2
	sub r4, #0x18
	add r0, r5, r0
	add r1, r4, r0
	ldr r0, _02035064 ; =0x020F2364
	ldrb r0, [r0, r1]
_0203505C:
	pop {r3-r7, pc}
	nop
_02035060: .word 0x0000016E
_02035064: .word 0x020F2364
