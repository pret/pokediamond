	.include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start FUN_020337E8
FUN_020337E8: ; 0x020337E8
	push {r3-r5, lr}
	mov r1, #0x72
	lsl r1, r1, #0x4
	bl FUN_02016998
	add r4, r0, #0x0
	add r0, #0x1f
	mov r1, #0x1f
	bic r0, r1
	bl DWC_Init
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl FUN_02016A18
	add r0, r5, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start FUN_0203380C
FUN_0203380C: ; 0x0203380C
	push {r4, lr}
	bl FUN_02028228
	add r4, r0, #0x0
	bl DWC_CheckUserData
	cmp r0, #0x0
	bne _0203382A
	ldr r1, _0203382C ; =0x4144414A
	add r0, r4, #0x0
	bl DWC_CreateUserData
	add r0, r4, #0x0
	bl DWC_ClearDirtyFlag
_0203382A:
	pop {r4, pc}
	.balign 4
_0203382C: .word 0x4144414A

	thumb_func_start FUN_02033830
FUN_02033830: ; 0x02033830
	push {r3-r4, lr}
	sub sp, #0xc
	bl FUN_02028228
	add r4, r0, #0x0
	add r1, sp, #0x0
	bl DWC_CreateExchangeToken
	add r0, r4, #0x0
	add r1, sp, #0x0
	bl DWC_GetGsProfileId
	add sp, #0xc
	pop {r3-r4, pc}

	thumb_func_start FUN_0203384C
FUN_0203384C: ; 0x0203384C
	push {r4, lr}
	bl FUN_020286EC
	bl FUN_02028228
	add r4, r0, #0x0
	bl DWC_CheckHasProfile
	cmp r0, #0x0
	beq _0203386E
	add r0, r4, #0x0
	bl DWC_CheckValidConsole
	cmp r0, #0x0
	beq _0203386E
	mov r0, #0x1
	pop {r4, pc}
_0203386E:
	mov r0, #0x0
	pop {r4, pc}
	.balign 4
