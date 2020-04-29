    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start G3_MultMtx33
G3_MultMtx33: ; 0x020C791C
	ldr r1, _020C7930 ; =0x04000400
	mov r2, #0x1a
	ldr ip, _020C7934 ; =MI_Copy36B
	str r2, [r1, #0x0]
	bx r12
	.balign 4
_020C7930: .word 0x04000400
_020C7934: .word MI_Copy36B

	arm_func_start G3_MultMtx43
G3_MultMtx43:
	ldr r1, _020C794C ; =0x04000400
	mov r2, #0x19
	ldr ip, _020C7950 ; =GX_SendFifo48B
	str r2, [r1, #0x0]
	bx r12
	.balign 4
_020C794C: .word 0x04000400
_020C7950: .word GX_SendFifo48B

	arm_func_start G3_LoadMtx43
G3_LoadMtx43: ; 0x020C7954
	ldr r1, _020C7968 ; =0x04000400
	mov r2, #0x17
	ldr ip, _020C796C ; =GX_SendFifo48B
	str r2, [r1, #0x0]
	bx r12
	.balign 4
_020C7968: .word 0x04000400
_020C796C: .word GX_SendFifo48B
