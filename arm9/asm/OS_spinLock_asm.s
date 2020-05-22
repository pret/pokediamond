    .include "asm/macros.inc"
    .include "global.inc"

    .text

	arm_func_start OS_UnLockCartridge
OS_UnLockCartridge: ; 0x020CA094
	ldr r1, _020CA09C ; =OS_UnlockCartridge
	bx r1
	.balign 4
_020CA09C: .word OS_UnlockCartridge

	arm_func_start OS_GetLockID
OS_GetLockID: ; 0x020CA0A0
	ldr r3, _020CA0F0 ; =0x027FFFB0
	ldr r1, [r3, #0x0]
	clz r2, r1
	cmp r2, #0x20
	movne r0, #0x40
	bne _020CA0D4
	add r3, r3, #0x4
	ldr r1, [r3, #0x0]
	clz r2, r1
	cmp r2, #0x20
	ldr r0, _020CA0F4 ; =0xFFFFFFFD
	bxeq lr
	mov r0, #0x60
_020CA0D4:
	add r0, r0, r2
	mov r1, #0x80000000
	mov r1, r1, lsr r2
	ldr r2, [r3, #0x0]
	bic r2, r2, r1
	str r2, [r3, #0x0]
	bx lr
	.balign 4
_020CA0F0: .word 0x027FFFB0
_020CA0F4: .word 0xFFFFFFFD

	arm_func_start OS_ReleaseLockID
OS_ReleaseLockID: ; 0x020CA0F8
	ldr r3, _020CA124 ; =0x027FFFB0
	cmp r0, #0x60
	addpl r3, r3, #0x4
	subpl r0, r0, #0x60
	submi r0, r0, #0x40
	mov r1, #0x80000000
	mov r1, r1, lsr r0
	ldr r2, [r3, #0x0]
	orr r2, r2, r1
	str r2, [r3, #0x0]
	bx lr
	.balign 4
_020CA124: .word 0x027FFFB0

	arm_func_start OS_ReadOwnerOfLockWord
OS_ReadOwnerOfLockWord: ; 0x020CA128
	ldrh r0, [r0, #0x4]
	bx lr

	arm_func_start OSi_FreeCardBus
OSi_FreeCardBus: ; 0x020CA130
	ldr r1, _020CA144 ; =0x04000204
	ldrh r0, [r1, #0x0]
	orr r0, r0, #0x800
	strh r0, [r1, #0x0]
	bx lr
	.balign 4
_020CA144: .word 0x04000204

	arm_func_start OSi_AllocateCardBus
OSi_AllocateCardBus: ; 0x020CA148
	ldr r1, _020CA15C ; =0x04000204
	ldrh r0, [r1, #0x0]
	bic r0, r0, #0x800
	strh r0, [r1, #0x0]
	bx lr
	.balign 4
_020CA15C: .word 0x04000204

	arm_func_start OS_UnlockCard
OS_UnlockCard: ; 0x020CA160
	ldr ip, _020CA170 ; =OS_UnlockByWord
	ldr r1, _020CA174 ; =0x027FFFE0
	ldr r2, _020CA178 ; =OSi_FreeCardBus
	bx r12
	.balign 4
_020CA170: .word OS_UnlockByWord
_020CA174: .word 0x027FFFE0
_020CA178: .word OSi_FreeCardBus

	arm_func_start OS_TryLockCard
OS_TryLockCard: ; 0x020CA17C
	ldr ip, _020CA18C ; =OS_TryLockByWord
	ldr r1, _020CA190 ; =0x027FFFE0
	ldr r2, _020CA194 ; =OSi_AllocateCardBus
	bx r12
	.balign 4
_020CA18C: .word OS_TryLockByWord
_020CA190: .word 0x027FFFE0
_020CA194: .word OSi_AllocateCardBus
