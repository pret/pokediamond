	.include "asm/macros.inc"
    .include "global.inc"
    .include "constants/species.h"

	.text

	thumb_func_start Sav2_Daycare_sizeof
Sav2_Daycare_sizeof: ; 0x02023C40
	mov r0, #0x1e
	lsl r0, r0, #0x4
	bx lr
	.balign 4

	thumb_func_start Sav2_Daycare_init
Sav2_Daycare_init: ; 0x02023C48
	push {r4, lr}
	mov r2, #0x1e
	add r4, r0, #0x0
	mov r1, #0x0
	lsl r2, r2, #0x4
	bl memset
	add r0, r4, #0x0
	bl ZeroBoxMonData
	add r0, r4, #0x0
	add r0, #0xec
	bl ZeroBoxMonData
	mov r0, #0x76
	mov r1, #0x0
	lsl r0, r0, #0x2
	str r1, [r4, r0]
	add r0, r0, #0x4
	strb r1, [r4, r0]
	pop {r4, pc}
	.balign 4

	thumb_func_start FUN_02023C74
FUN_02023C74: ; 0x02023C74
	mov r2, #0xec
	mul r2, r1
	add r0, r0, r2
	bx lr

	thumb_func_start FUN_02023C7C
FUN_02023C7C: ; 0x02023C7C
	bx lr
	.balign 4

	thumb_func_start FUN_02023C80
FUN_02023C80: ; 0x02023C80
	add r0, #0x88
	bx lr

	thumb_func_start FUN_02023C84
FUN_02023C84: ; 0x02023C84
	add r0, #0xe8
	ldr r0, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02023C8C
FUN_02023C8C: ; 0x02023C8C
	bx lr
	.balign 4

	thumb_func_start FUN_02023C90
FUN_02023C90: ; 0x02023C90
	mov r1, #0x76
	lsl r1, r1, #0x2
	ldr r0, [r0, r1]
	bx lr

	thumb_func_start FUN_02023C98
FUN_02023C98: ; 0x02023C98
	mov r1, #0x77
	lsl r1, r1, #0x2
	ldrb r0, [r0, r1]
	bx lr

	thumb_func_start FUN_02023CA0
FUN_02023CA0: ; 0x02023CA0
	add r0, #0xe8
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02023CA8
FUN_02023CA8: ; 0x02023CA8
	add r2, r0, #0x0
	add r2, #0xe8
	ldr r2, [r2, #0x0]
	add r0, #0xe8
	add r1, r2, r1
	str r1, [r0, #0x0]
	bx lr
	.balign 4

	thumb_func_start FUN_02023CB8
FUN_02023CB8: ; 0x02023CB8
	mov r2, #0x76
	lsl r2, r2, #0x2
	str r1, [r0, r2]
	bx lr

	thumb_func_start FUN_02023CC0
FUN_02023CC0: ; 0x02023CC0
	mov r2, #0x77
	lsl r2, r2, #0x2
	strb r1, [r0, r2]
	bx lr

	thumb_func_start FUN_02023CC8
FUN_02023CC8: ; 0x02023CC8
	push {r3-r5, lr}
	add r5, r0, #0x0
	mov r1, #0xc
	mov r2, #0x0
	bl GetBoxMonData
	add r5, #0xec
	add r4, r0, #0x0
	add r0, r5, #0x0
	mov r1, #0xc
	mov r2, #0x0
	bl GetBoxMonData
	cmp r4, r0
	beq _02023CEA
	mov r0, #0x1
	pop {r3-r5, pc}
_02023CEA:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_02023CF0
FUN_02023CF0: ; 0x02023CF0
	push {r3-r4}
	add r4, r0, #0x0
	add r3, r1, #0x0
	mov r2, #0x1d
_02023CF8:
	ldmia r3!, {r0-r1}
	stmia r4!, {r0-r1}
	sub r2, r2, #0x1
	bne _02023CF8
	ldr r0, [r3, #0x0]
	str r0, [r4, #0x0]
	pop {r3-r4}
	bx lr

	thumb_func_start FUN_02023D08
FUN_02023D08: ; 0x02023D08
	push {r3-r4}
	mov r1, #0x0
	add r2, r0, #0x0
	add r4, r1, #0x0
_02023D10:
	add r1, r1, #0x1
	strh r4, [r2, #0x38]
	add r2, r2, #0x2
	cmp r1, #0x8
	blt _02023D10
	add r3, r0, #0x0
	mov r2, #0x0
_02023D1E:
	add r1, r3, #0x0
	add r1, #0x48
	add r4, r4, #0x1
	add r3, r3, #0x2
	strh r2, [r1, #0x0]
	cmp r4, #0xb
	blt _02023D1E
	ldr r1, _02023D38 ; =0x0000FFFF
	strh r1, [r0, #0x38]
	add r0, #0x48
	strh r1, [r0, #0x0]
	pop {r3-r4}
	bx lr
	.balign 4
_02023D38: .word 0x0000FFFF

	thumb_func_start FUN_02023D3C
FUN_02023D3C: ; 0x02023D3C
	push {r4, lr}
	add r4, r0, #0x0
	bl ZeroBoxMonData
	add r0, r4, #0x0
	mov r1, #0x0
	add r0, #0xe8
	add r4, #0x88
	str r1, [r0, #0x0]
	add r0, r4, #0x0
	bl FUN_02023D08
	pop {r4, pc}
	.balign 4

	thumb_func_start Sav2_Daycare_get
Sav2_Daycare_get: ; 0x02023D58
	ldr r3, _02023D60 ; =SavArray_get
	mov r1, #0x8
	bx r3
	nop
_02023D60: .word SavArray_get
