	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_02024E6C
FUN_02024E6C: ; 0x02024E6C
	push {r4, lr}
	add r4, r0, #0x0
	ldr r2, _02024EA4 ; =0x0000074C
	mov r0, #0x0
	add r1, r4, #0x0
	bl MIi_CpuClearFast
	add r0, r4, #0x0
	bl FUN_020250A4
	mov r0, #0x7
	lsl r0, r0, #0x8
	add r0, r4, r0
	bl FUN_02025484
	ldr r1, _02024EA8 ; =0x00000724
	ldr r0, _02024EAC ; =0x0000FFFF
	add r1, r4, r1
	mov r2, #0x8
	bl MIi_CpuClear16
	ldr r1, _02024EB0 ; =0x00000734
	ldr r0, _02024EAC ; =0x0000FFFF
	add r1, r4, r1
	mov r2, #0xb
	bl MIi_CpuClear16
	pop {r4, pc}
	.balign 4
_02024EA4: .word 0x0000074C
_02024EA8: .word 0x00000724
_02024EAC: .word 0x0000FFFF
_02024EB0: .word 0x00000734

	thumb_func_start FUN_02024EB4
FUN_02024EB4: ; 0x02024EB4
	ldr r3, _02024EBC ; =SavArray_get
	mov r1, #0xa
	bx r3
	nop
_02024EBC: .word SavArray_get

	thumb_func_start FUN_02024EC0
FUN_02024EC0: ; 0x02024EC0
	ldr r3, _02024EC8 ; =FUN_02022634
	mov r1, #0xa
	bx r3
	nop
_02024EC8: .word FUN_02022634

	thumb_func_start FUN_02024ECC
FUN_02024ECC: ; 0x02024ECC
	ldr r3, _02024ED4 ; =SavArray_get
	mov r1, #0xa
	bx r3
	nop
_02024ED4: .word SavArray_get

	thumb_func_start FUN_02024ED8
FUN_02024ED8: ; 0x02024ED8
	push {r3, lr}
	mov r1, #0xa
	bl SavArray_get
	mov r1, #0x7
	lsl r1, r1, #0x8
	add r0, r0, r1
	pop {r3, pc}

	thumb_func_start FUN_02024EE8
FUN_02024EE8: ; 0x02024EE8
	ldr r1, _02024EF0 ; =0x00000724
	add r0, r0, r1
	bx lr
	nop
_02024EF0: .word 0x00000724

	thumb_func_start FUN_02024EF4
FUN_02024EF4: ; 0x02024EF4
	add r2, r0, #0x0
	add r0, r1, #0x0
	ldr r1, _02024F04 ; =0x00000724
	ldr r3, _02024F08 ; =CopyStringToU16Array
	add r1, r2, r1
	mov r2, #0x8
	bx r3
	nop
_02024F04: .word 0x00000724
_02024F08: .word CopyStringToU16Array

	thumb_func_start FUN_02024F0C
FUN_02024F0C: ; 0x02024F0C
	ldr r1, _02024F14 ; =0x00000734
	add r0, r0, r1
	bx lr
	nop
_02024F14: .word 0x00000734

	thumb_func_start FUN_02024F18
FUN_02024F18: ; 0x02024F18
	add r2, r0, #0x0
	add r0, r1, #0x0
	ldr r1, _02024F28 ; =0x00000734
	ldr r3, _02024F2C ; =CopyStringToU16Array
	add r1, r2, r1
	mov r2, #0xb
	bx r3
	nop
_02024F28: .word 0x00000734
_02024F2C: .word CopyStringToU16Array
