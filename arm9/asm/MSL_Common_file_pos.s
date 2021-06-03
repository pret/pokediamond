	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start _ftell
_ftell: ; 0x020DEDE4
	ldr r1, [r0, #0x4]
	mov r1, r1, lsl #0x16
	mov r1, r1, lsr #0x1d
	and r1, r1, #0xff
	add r1, r1, #0xff
	and r1, r1, #0xff
	cmp r1, #0x1
	bhi _020DEE10
	ldrb r1, [r0, #0xd]
	cmp r1, #0x0
	beq _020DEE24
_020DEE10:
	ldr r0, _020DEE5C ; =errno
	mov r1, #0x28
	str r1, [r0, #0x0]
	sub r0, r1, #0x29
	bx lr
_020DEE24:
	ldr r1, [r0, #0x8]
	mov r1, r1, lsl #0x1d
	movs r12, r1, lsr #0x1d
	ldreq r0, [r0, #0x18]
	bxeq lr
	ldr r2, [r0, #0x24]
	ldr r1, [r0, #0x1c]
	ldr r3, [r0, #0x34]
	sub r0, r2, r1
	cmp r12, #0x3
	add r0, r3, r0
	subcs r1, r12, #0x2
	subcs r0, r0, r1
	bx lr
	.balign 4
_020DEE5C: .word errno
	arm_func_end _ftell

	arm_func_start ftell
ftell: ; 0x020DEE60
	stmdb sp!, {r3-r7,lr}
	ldr r1, _020DEF60 ; =__files
	mov r7, r0
	cmp r7, r1
	moveq r6, #0x2
	beq _020DEE98
	ldr r0, _020DEF64 ; =__files + 0x4C
	cmp r7, r0
	moveq r6, #0x3
	beq _020DEE98
	ldr r0, _020DEF68 ; =__files + 0x98
	cmp r7, r0
	moveq r6, #0x4
	movne r6, #0x5
_020DEE98:
	mov r0, #0x18
	mul r4, r6, r0
	ldr r5, _020DEF6C ; =__cs
	add r0, r5, r4
	bl OS_TryLockMutex
	cmp r0, #0x0
	bne _020DEED8
	ldr r0, _020DEF70 ; =OSi_ThreadInfo
	ldr r2, _020DEF74 ; =__cs_id
	ldr r1, [r0, #0x4]
	ldr r0, _020DEF78 ; =__cs_ref
	ldr r3, [r1, #0x6c]
	mov r1, #0x1
	str r3, [r2, r6, lsl #0x2]
	str r1, [r0, r6, lsl #0x2]
	b _020DEF30
_020DEED8:
	ldr r0, _020DEF70 ; =OSi_ThreadInfo
	ldr r1, _020DEF74 ; =__cs_id
	ldr r0, [r0, #0x4]
	ldr r1, [r1, r6, lsl #0x2]
	ldr r0, [r0, #0x6c]
	cmp r1, r0
	bne _020DEF08
	ldr r1, _020DEF78 ; =__cs_ref
	ldr r0, [r1, r6, lsl #0x2]
	add r0, r0, #0x1
	str r0, [r1, r6, lsl #0x2]
	b _020DEF30
_020DEF08:
	add r0, r5, r4
	bl OS_LockMutex
	ldr r0, _020DEF70 ; =OSi_ThreadInfo
	ldr r2, _020DEF74 ; =__cs_id
	ldr r1, [r0, #0x4]
	ldr r0, _020DEF78 ; =__cs_ref
	ldr r3, [r1, #0x6c]
	mov r1, #0x1
	str r3, [r2, r6, lsl #0x2]
	str r1, [r0, r6, lsl #0x2]
_020DEF30:
	mov r0, r7
	bl _ftell
	ldr r1, _020DEF78 ; =__cs_ref
	mov r7, r0
	ldr r0, [r1, r6, lsl #0x2]
	subs r0, r0, #0x1
	str r0, [r1, r6, lsl #0x2]
	bne _020DEF58
	add r0, r5, r4
	bl OS_UnlockMutex
_020DEF58:
	mov r0, r7
	ldmia sp!, {r3-r7,pc}
	.balign 4
_020DEF60: .word __files
_020DEF64: .word __files + 0x4C
_020DEF68: .word __files + 0x98
_020DEF6C: .word __cs
_020DEF70: .word OSi_ThreadInfo
_020DEF74: .word __cs_id
_020DEF78: .word __cs_ref
	arm_func_end ftell

	arm_func_start _fseek
_fseek: ; 0x020DEF7C
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3-r5,lr}
	mov r5, r0
	ldr r1, [r5, #0x4]
	mov r4, r2
	mov r1, r1, lsl #0x16
	mov r1, r1, lsr #0x1d
	and r1, r1, #0xff
	cmp r1, #0x1
	ldreqb r1, [r5, #0xd]
	cmpeq r1, #0x0
	beq _020DEFC8
	ldr r0, _020DF160 ; =errno
	mov r1, #0x28
	str r1, [r0, #0x0]
	sub r0, r1, #0x29
	ldmia sp!, {r3-r5,lr}
	add sp, sp, #0x10
	bx lr
_020DEFC8:
	ldr r1, [r5, #0x8]
	mov r1, r1, lsl #0x1d
	mov r1, r1, lsr #0x1d
	cmp r1, #0x1
	bne _020DF018
	mov r1, #0x0
	bl __flush_buffer
	cmp r0, #0x0
	beq _020DF018
	mov r0, #0x1
	strb r0, [r5, #0xd]
	mov r2, #0x0
	ldr r0, _020DF160 ; =errno
	mov r1, #0x28
	str r2, [r5, #0x28]
	str r1, [r0, #0x0]
	sub r0, r1, #0x29
	ldmia sp!, {r3-r5,lr}
	add sp, sp, #0x10
	bx lr
_020DF018:
	cmp r4, #0x1
	bne _020DF038
	mov r0, r5
	mov r4, #0x0
	bl _ftell
	ldr r1, [sp, #0x14]
	add r0, r1, r0
	str r0, [sp, #0x14]
_020DF038:
	cmp r4, #0x2
	beq _020DF0CC
	ldr r0, [r5, #0x4]
	mov r0, r0, lsl #0x1b
	mov r0, r0, lsr #0x1d
	cmp r0, #0x3
	beq _020DF0CC
	ldr r0, [r5, #0x8]
	mov r0, r0, lsl #0x1d
	mov r0, r0, lsr #0x1d
	sub r0, r0, #0x2
	cmp r0, #0x1
	bhi _020DF0CC
	ldr r2, [sp, #0x14]
	ldr r0, [r5, #0x18]
	cmp r2, r0
	bhs _020DF088
	ldr r0, [r5, #0x34]
	cmp r2, r0
	bhs _020DF098
_020DF088:
	ldr r0, [r5, #0x8]
	bic r0, r0, #0x7
	str r0, [r5, #0x8]
	b _020DF0D8
_020DF098:
	ldr r1, [r5, #0x1c]
	sub r0, r2, r0
	add r0, r1, r0
	str r0, [r5, #0x24]
	ldr r1, [r5, #0x18]
	ldr r0, [sp, #0x14]
	sub r0, r1, r0
	str r0, [r5, #0x28]
	ldr r0, [r5, #0x8]
	bic r0, r0, #0x7
	orr r0, r0, #0x2
	str r0, [r5, #0x8]
	b _020DF0D8
_020DF0CC:
	ldr r0, [r5, #0x8]
	bic r0, r0, #0x7
	str r0, [r5, #0x8]
_020DF0D8:
	ldr r0, [r5, #0x8]
	mov r0, r0, lsl #0x1d
	movs r0, r0, lsr #0x1d
	bne _020DF150
	ldr r12, [r5, #0x38]
	cmp r12, #0x0
	beq _020DF13C
	ldr r0, [r5, #0x0]
	ldr r3, [r5, #0x48]
	add r1, sp, #0x14
	mov r2, r4
	blx r12
	cmp r0, #0x0
	beq _020DF13C
	mov r0, #0x1
	strb r0, [r5, #0xd]
	mov r2, #0x0
	ldr r0, _020DF160 ; =errno
	mov r1, #0x28
	str r2, [r5, #0x28]
	str r1, [r0, #0x0]
	sub r0, r1, #0x29
	ldmia sp!, {r3-r5,lr}
	add sp, sp, #0x10
	bx lr
_020DF13C:
	mov r1, #0x0
	strb r1, [r5, #0xc]
	ldr r0, [sp, #0x14]
	str r0, [r5, #0x18]
	str r1, [r5, #0x28]
_020DF150:
	mov r0, #0x0
	ldmia sp!, {r3-r5,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020DF160: .word errno
	arm_func_end _fseek

	arm_func_start fseek
fseek:
	stmdb sp!, {r3-r9,lr}
	ldr r3, _020DF274 ; =__files
	mov r9, r0
	cmp r9, r3
	mov r8, r1
	mov r7, r2
	moveq r6, #0x2
	beq _020DF1A4
	ldr r0, _020DF278 ; =__files + 0x4C
	cmp r9, r0
	moveq r6, #0x3
	beq _020DF1A4
	ldr r0, _020DF27C ; =__files + 0x98
	cmp r9, r0
	moveq r6, #0x4
	movne r6, #0x5
_020DF1A4:
	mov r0, #0x18
	mul r4, r6, r0
	ldr r5, _020DF280 ; =__cs
	add r0, r5, r4
	bl OS_TryLockMutex
	cmp r0, #0x0
	bne _020DF1E4
	ldr r0, _020DF284 ; =OSi_ThreadInfo
	ldr r2, _020DF288 ; =__cs_id
	ldr r1, [r0, #0x4]
	ldr r0, _020DF28C ; =__cs_ref
	ldr r3, [r1, #0x6c]
	mov r1, #0x1
	str r3, [r2, r6, lsl #0x2]
	str r1, [r0, r6, lsl #0x2]
	b _020DF23C
_020DF1E4:
	ldr r0, _020DF284 ; =OSi_ThreadInfo
	ldr r1, _020DF288 ; =__cs_id
	ldr r0, [r0, #0x4]
	ldr r1, [r1, r6, lsl #0x2]
	ldr r0, [r0, #0x6c]
	cmp r1, r0
	bne _020DF214
	ldr r1, _020DF28C ; =__cs_ref
	ldr r0, [r1, r6, lsl #0x2]
	add r0, r0, #0x1
	str r0, [r1, r6, lsl #0x2]
	b _020DF23C
_020DF214:
	add r0, r5, r4
	bl OS_LockMutex
	ldr r0, _020DF284 ; =OSi_ThreadInfo
	ldr r2, _020DF288 ; =__cs_id
	ldr r1, [r0, #0x4]
	ldr r0, _020DF28C ; =__cs_ref
	ldr r3, [r1, #0x6c]
	mov r1, #0x1
	str r3, [r2, r6, lsl #0x2]
	str r1, [r0, r6, lsl #0x2]
_020DF23C:
	mov r0, r9
	mov r1, r8
	mov r2, r7
	bl _fseek
	ldr r1, _020DF28C ; =__cs_ref
	mov r7, r0
	ldr r0, [r1, r6, lsl #0x2]
	subs r0, r0, #0x1
	str r0, [r1, r6, lsl #0x2]
	bne _020DF26C
	add r0, r5, r4
	bl OS_UnlockMutex
_020DF26C:
	mov r0, r7
	ldmia sp!, {r3-r9,pc}
	.balign 4
_020DF274: .word __files
_020DF278: .word __files + 0x4C
_020DF27C: .word __files + 0x98
_020DF280: .word __cs
_020DF284: .word OSi_ThreadInfo
_020DF288: .word __cs_id
_020DF28C: .word __cs_ref
	arm_func_end fseek

	arm_func_start rewind
rewind: ; 0x020DF290
	stmdb sp!, {r4,lr}
	mov r1, #0x0
	mov r4, r0
	mov r2, r1
	strb r1, [r4, #0xd]
	bl fseek
	mov r0, #0x0
	strb r0, [r4, #0xd]
	ldmia sp!, {r4,pc}
	arm_func_end rewind

	.section .exceptix,4

	.word ftell
	.short 285
	.word 0x00300F00
	.word _fseek
	.short 489
	.word 0x00400320
	.word fseek
	.short 301
	.word 0x00403F00
	.word rewind
	.short 37
	.word 0x00100100
