    .include "asm/macros.inc"
    .include "global.inc"

	.text

	thumb_func_start ScrCmd_PokeParkControl
ScrCmd_PokeParkControl: ; 0x0204387C
	push {r3-r5, lr}
	add r5, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020462AC
	add r4, r0, #0x0
	add r0, r5, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r5, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	cmp r0, #0x0
	bne _020438B2
	add r0, r4, #0x0
	bl FUN_0205F224
	add r5, #0x80
	ldr r0, [r5, #0x0]
	bl FUN_0204B9EC
	b _020438CA
_020438B2:
	cmp r0, #0x1
	bne _020438C6
	add r0, r4, #0x0
	bl FUN_0205F234
	add r5, #0x80
	ldr r0, [r5, #0x0]
	bl FUN_0204BA1C
	b _020438CA
_020438C6:
	bl ErrorHandling
_020438CA:
	mov r0, #0x0
	pop {r3-r5, pc}
	.balign 4

	thumb_func_start ScrCmd_PokeParkDepositCount
ScrCmd_PokeParkDepositCount: ; 0x020438D0
	push {r4-r6, lr}
	add r4, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02022528
	add r6, r0, #0x0
	mov r0, #0x20
	bl FUN_020669C0
	add r5, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r4, #0x80
	add r1, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_020394B8
	add r4, r0, #0x0
	add r0, r6, #0x0
	bl FUN_0202C000
	cmp r0, #0x6
	bne _02043908
	mov r0, #0x1
	b _0204390A
_02043908:
	mov r0, #0x0
_0204390A:
	strh r0, [r4, #0x0]
	add r0, r5, #0x0
	bl FreeToHeap
	mov r0, #0x0
	pop {r4-r6, pc}
	.balign 4

	thumb_func_start ScrCmd_PokeParkTransMons
ScrCmd_PokeParkTransMons: ; 0x02043918
	push {r4-r7, lr}
	sub sp, #0xc
	add r6, r0, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02022528
	add r7, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02022510
	str r0, [sp, #0x8]
	mov r0, #0x20
	bl FUN_020669C0
	add r4, r0, #0x0
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_020238F4
	str r0, [sp, #0x4]
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	ldr r0, [r0, #0xc]
	bl FUN_02024DA0
	mov r5, #0x0
_0204395C:
	add r0, r7, #0x0
	add r1, r5, #0x0
	add r2, r4, #0x0
	bl FUN_0202BFD8
	mov r0, #0x20
	str r0, [sp, #0x0]
	ldr r1, [sp, #0x4]
	add r0, r4, #0x0
	mov r2, #0x2
	mov r3, #0x0
	bl FUN_0208089C
	add r0, r4, #0x0
	bl FUN_020690E4
	add r1, r0, #0x0
	ldr r0, [sp, #0x8]
	bl FUN_0206B20C
	cmp r0, #0x0
	bne _0204398C
	bl ErrorHandling
_0204398C:
	add r0, r6, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	add r1, r4, #0x0
	ldr r0, [r0, #0xc]
	bl FUN_0202C144
	add r5, r5, #0x1
	cmp r5, #0x6
	blt _0204395C
	add r0, r4, #0x0
	bl FreeToHeap
	add r0, r7, #0x0
	bl FUN_0202BEDC
	mov r0, #0x0
	add sp, #0xc
	pop {r4-r7, pc}
	.balign 4

	thumb_func_start ScrCmd_PokeParkGetScore
ScrCmd_PokeParkGetScore: ; 0x020439B4
	push {r3-r7, lr}
	add r4, r0, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394F0
	add r6, r0, #0x0
	add r0, r4, #0x0
	bl ScriptReadHalfword
	add r1, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_020394B8
	add r5, r0, #0x0
	cmp r6, #0x3
	bhi _02043A40
	add r0, r6, r6
	add r0, pc
	ldrh r0, [r0, #0x6]
	lsl r0, r0, #0x10
	asr r0, r0, #0x10
	add pc, r0
_020439EE: ; jump table (using 16-bit offset)
	.short _020439F6 - _020439EE - 2; case 0
	.short _02043A02 - _020439EE - 2; case 1
	.short _02043A0E - _020439EE - 2; case 2
	.short _02043A1A - _020439EE - 2; case 3
_020439F6:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_0204BAC4
	strh r0, [r5, #0x0]
	b _02043A40
_02043A02:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_0204BAD4
	strh r0, [r5, #0x0]
	b _02043A40
_02043A0E:
	add r4, #0x80
	ldr r0, [r4, #0x0]
	bl FUN_0204BAE4
	strh r0, [r5, #0x0]
	b _02043A40
_02043A1A:
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0204BAD4
	add r6, r0, #0x0
	add r0, r4, #0x0
	add r0, #0x80
	ldr r0, [r0, #0x0]
	bl FUN_0204BAC4
	add r4, #0x80
	add r7, r0, #0x0
	ldr r0, [r4, #0x0]
	bl FUN_0204BAE4
	add r0, r7, r0
	add r0, r6, r0
	strh r0, [r5, #0x0]
_02043A40:
	mov r0, #0x0
	pop {r3-r7, pc}
