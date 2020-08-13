    .include "asm/macros.inc"
    .include "global.inc"

	.section .rodata

	.global UNK_020FD6E4
UNK_020FD6E4: ; 0x020FD6E4
	.word FUN_020889B0, FUN_02088A00, FUN_02088A78, 0xFFFFFFFF

	.text

	thumb_func_start FUN_0208890C
FUN_0208890C: ; 0x0208890C
	push {r3-r7, lr}
	add r6, r0, #0x0
	add r5, r1, #0x0
	add r0, r2, #0x0
	mov r1, #0x20
	add r7, r3, #0x0
	bl AllocFromHeap
	add r4, r0, #0x0
	mov r1, #0x0
	mov r2, #0x20
	bl MI_CpuFill8
	str r5, [r4, #0xc]
	add r0, r5, #0x0
	bl FUN_02028048
	str r0, [r4, #0x8]
	add r0, r5, #0x0
	bl Sav2_PlayerData_GetProfileAddr
	str r0, [r4, #0x10]
	add r0, r5, #0x0
	bl Sav2_Bag_get
	str r0, [r4, #0x14]
	add r0, r5, #0x0
	bl Sav2_PlayerData_GetOptionsAddr
	str r0, [r4, #0x18]
	str r7, [r4, #0x1c]
	str r6, [r4, #0x4]
	add r0, r4, #0x0
	pop {r3-r7, pc}

	thumb_func_start FUN_02088950
FUN_02088950: ; 0x02088950
	ldr r3, _02088958 ; =FUN_020373D4
	add r2, r1, #0x0
	ldr r1, _0208895C ; =UNK_020FD6E4
	bx r3
	.balign 4
_02088958: .word FUN_020373D4
_0208895C: .word UNK_020FD6E4

	thumb_func_start FUN_02088960
FUN_02088960: ; 0x02088960
	push {r4-r6, lr}
	add r5, r0, #0x0
	add r4, r1, #0x0
	add r6, r2, #0x0
	bl FUN_020377AC
	add r3, r5, #0x0
	add r3, #0x98
	add r1, r0, #0x0
	ldr r3, [r3, #0x0]
	add r0, r4, #0x0
	add r2, r6, #0x0
	bl FUN_0208890C
	add r4, r0, #0x0
	add r0, r5, #0x0
	add r1, r4, #0x0
	bl FUN_02088950
	add r0, r4, #0x0
	pop {r4-r6, pc}
	.balign 4
