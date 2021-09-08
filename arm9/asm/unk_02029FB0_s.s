	.include "asm/macros.inc"
	.include "global.inc"

	.extern FUN_02029FD4
	.extern FUN_02029FF8
	.extern FUN_0202A028
	.extern FUN_0202A070

	.text

	thumb_func_start FUN_0202A0A8
FUN_0202A0A8: ; 0x0202A0A8
	push {r3-r7, lr}
	add r6, r1, #0x0
	add r7, r0, #0x0
	add r0, r6, #0x0
	add r5, r2, #0x0
	bl FUN_0202A028
	add r4, r0, #0x0
	add r0, r7, #0x0
	add r1, r6, #0x0
	bl FUN_02029FD4
	cmp r5, r4
	bls _0202A0C6
	add r5, r4, #0x0
_0202A0C6:
	cmp r0, r5
	bhs _0202A0D6
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r5, #0x0
	bl FUN_02029FF8
	pop {r3-r7, pc}
_0202A0D6:
	cmp r0, r4
	bls _0202A0E4
	add r0, r7, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02029FF8
_0202A0E4:
	pop {r3-r7, pc}
	.balign 4

	thumb_func_start FUN_0202A0E8
FUN_0202A0E8: ; 0x0202A0E8
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0202A028
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02029FD4
	add r2, r0, #0x1
	cmp r2, r4
	bhs _0202A10E
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02029FF8
	pop {r4-r6, pc}
_0202A10E:
	add r0, r5, #0x0
	add r1, r6, #0x0
	add r2, r4, #0x0
	bl FUN_02029FF8
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start FUN_0202A11C
FUN_0202A11C: ; 0x0202A11C
	push {r3-r7, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	add r0, r4, #0x0
	add r7, r2, #0x0
	bl FUN_0202A028
	add r6, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029FD4
	add r2, r0, r7
	cmp r2, r6
	bhs _0202A144
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02029FF8
	pop {r3-r7, pc}
_0202A144:
	add r0, r5, #0x0
	add r1, r4, #0x0
	add r2, r6, #0x0
	bl FUN_02029FF8
	pop {r3-r7, pc}

	thumb_func_start FUN_0202A150
FUN_0202A150: ; 0x0202A150
	push {r4-r6, lr}
	add r6, r1, #0x0
	add r5, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0202A028
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r6, #0x0
	bl FUN_02029FD4
	cmp r0, r4
	bhi _0202A16C
	add r4, r0, #0x0
_0202A16C:
	add r0, r4, #0x0
	pop {r4-r6, pc}

	thumb_func_start FUN_0202A170
FUN_0202A170: ; 0x0202A170
	push {r4-r6, lr}
	add r4, r1, #0x0
	add r5, r0, #0x0
	cmp r4, #0x26
	blt _0202A17E
	bl GF_AssertFail
_0202A17E:
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0202A150
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl FUN_0202A070
	ldr r2, _0202A1B4 ; =0x05F5E0FF
	add r0, r6, r0
	cmp r0, r2
	bls _0202A1A0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0202A07C
	pop {r4-r6, pc}
_0202A1A0:
	add r0, r4, #0x0
	bl FUN_0202A070
	add r2, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0x0
	bl FUN_0202A11C
	pop {r4-r6, pc}
	nop
_0202A1B4: .word 0x05F5E0FF

	thumb_func_start FUN_0202A1B8
FUN_0202A1B8: ; 0x0202A1B8
	ldr r3, _0202A1C0 ; =FUN_0202A150
	mov r1, #0x0
	bx r3
	nop
_0202A1C0: .word FUN_0202A150

	thumb_func_start FUN_0202A1C4
FUN_0202A1C4: ; 0x0202A1C4
	push {r4, lr}
	add r4, r0, #0x0
	add r0, r1, #0x0
	add r1, r2, #0x0
	bl Pokedex_CheckMonCaughtFlag
	cmp r0, #0x0
	bne _0202A1DC
	add r0, r4, #0x0
	mov r1, #0x16
	bl FUN_0202A170
_0202A1DC:
	pop {r4, pc}
	.balign 4
