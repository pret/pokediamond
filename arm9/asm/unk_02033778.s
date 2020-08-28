	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02033778
FUN_02033778: ; 0x02033778
	push {r3-r7, lr}
	str r0, [sp, #0x0]
	bl FUN_02030F20
	add r7, r0, #0x0
	mov r0, #0x0
	bl FUN_0202DFA4
	cmp r0, #0x0
	beq _020337C6
	mov r5, #0x0
	cmp r7, #0x0
	ble _020337C6
_02033792:
	bl FUN_02031190
	cmp r5, r0
	beq _020337C0
	add r0, r5, #0x0
	bl FUN_0202E020
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0202E044
	add r6, r0, #0x0
	add r0, r5, #0x0
	bl FUN_0202DFA4
	bl PlayerProfile_GetLanguage
	add r3, r0, #0x0
	ldr r0, [sp, #0x0]
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_020337C8
_020337C0:
	add r5, r5, #0x1
	cmp r5, r7
	blt _02033792
_020337C6:
	pop {r3-r7, pc}

	thumb_func_start FUN_020337C8
FUN_020337C8: ; 0x020337C8
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_02029B40
	cmp r0, #0x0
	bne _020337E4
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	mov r3, #0x1
	bl FUN_02029B90
_020337E4:
	pop {r4-r6, pc}
	.balign 4
