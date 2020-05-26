	.include "asm/macros.inc"
	.include "global.inc"

	.text

	.extern _SDK_NintendoDWC

	arm_func_start DWC_Init
DWC_Init: ; 0x02096B14
	stmdb sp!, {r4-r6,lr}
	mov r6, r0
	ldr r0, _02096B74 ; =_SDK_NintendoDWC
	mov r4, #0x0
	bl OSi_ReferSymbol
	mov r0, r6
	bl DWC_BM_Init
	mov r5, r0
	bl DWC_Auth_CheckWiFiIDNeedCreate
	cmp r0, #0x0
	beq _02096B4C
	mov r0, r6
	bl DWCi_AUTH_MakeWiFiID
	mov r4, #0x1
_02096B4C:
	cmp r5, #0x0
	bge _02096B64
	cmp r4, #0x0
	movne r0, #0x2
	moveq r0, #0x3
	ldmia sp!, {r4-r6,pc}
_02096B64:
	cmp r4, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	ldmia sp!, {r4-r6,pc}
	.balign 4
_02096B74: .word _SDK_NintendoDWC
