	.include "asm/macros.inc"
	.include "global.inc"

	.text

	arm_func_start fread
fread: ; 0x020DE584
	stmdb sp!, {r4-r10,lr}
	ldr r4, _020DE67C ; =__files
	mov r7, r3
	cmp r7, r4
	moveq r6, #0x2
	mov r10, r0
	movne r6, #0x5
	mov r0, #0x18
	mul r4, r6, r0
	ldr r5, _020DE680 ; =__cs
	mov r9, r1
	add r0, r5, r4
	mov r8, r2
	bl OS_TryLockMutex
	cmp r0, #0x0
	bne _020DE5E8
	ldr r0, _020DE684 ; =OSi_ThreadInfo
	ldr r2, _020DE688 ; =__cs_id
	ldr r1, [r0, #0x4]
	ldr r0, _020DE68C ; =__cs_ref
	ldr r3, [r1, #0x6c]
	mov r1, #0x1
	str r3, [r2, r6, lsl #0x2]
	str r1, [r0, r6, lsl #0x2]
	b _020DE640
_020DE5E8:
	ldr r0, _020DE684 ; =OSi_ThreadInfo
	ldr r1, _020DE688 ; =__cs_id
	ldr r0, [r0, #0x4]
	ldr r1, [r1, r6, lsl #0x2]
	ldr r0, [r0, #0x6c]
	cmp r1, r0
	bne _020DE618
	ldr r1, _020DE68C ; =__cs_ref
	ldr r0, [r1, r6, lsl #0x2]
	add r0, r0, #0x1
	str r0, [r1, r6, lsl #0x2]
	b _020DE640
_020DE618:
	add r0, r5, r4
	bl OS_LockMutex
	ldr r0, _020DE684 ; =OSi_ThreadInfo
	ldr r2, _020DE688 ; =__cs_id
	ldr r1, [r0, #0x4]
	ldr r0, _020DE68C ; =__cs_ref
	ldr r3, [r1, #0x6c]
	mov r1, #0x1
	str r3, [r2, r6, lsl #0x2]
	str r1, [r0, r6, lsl #0x2]
_020DE640:
	mov r0, r10
	mov r1, r9
	mov r2, r8
	mov r3, r7
	bl __fread
	ldr r1, _020DE68C ; =__cs_ref
	mov r7, r0
	ldr r0, [r1, r6, lsl #0x2]
	subs r0, r0, #0x1
	str r0, [r1, r6, lsl #0x2]
	bne _020DE674
	add r0, r5, r4
	bl OS_UnlockMutex
_020DE674:
	mov r0, r7
	ldmia sp!, {r4-r10,pc}
	.balign 4
_020DE67C: .word __files
_020DE680: .word __cs
_020DE684: .word OSi_ThreadInfo
_020DE688: .word __cs_id
_020DE68C: .word __cs_ref
	arm_func_end fread

	arm_func_start __fread
__fread: ; 0x020DE690
	stmdb sp!, {r3-r10,lr}
	sub sp, sp, #0x4
	mov r7, r3
	mov r9, r0
	mov r8, r1
	mov r0, r7
	mov r1, #0x0
	mov r4, r2
	bl fwide
	cmp r0, #0x0
	bne _020DE6C8
	mov r0, r7
	mvn r1, #0x0
	bl fwide
_020DE6C8:
	muls r4, r8, r4
	beq _020DE6EC
	ldrb r0, [r7, #0xd]
	cmp r0, #0x0
	bne _020DE6EC
	ldr r1, [r7, #0x4]
	mov r0, r1, lsl #0x16
	movs r0, r0, lsr #0x1d
	bne _020DE6F8
_020DE6EC:
	add sp, sp, #0x4
	mov r0, #0x0
	ldmia sp!, {r3-r10,pc}
_020DE6F8:
	mov r0, r1, lsl #0x13
	movs r0, r0, lsr #0x1f
	movne r0, r1, lsl #0x19
	movne r0, r0, lsr #0x1e
	ldr r1, [r7, #0x8]
	cmpne r0, #0x2
	mov r6, #0x1
	mov r0, r1, lsl #0x1d
	movne r6, #0x0
	movs r0, r0, lsr #0x1d
	bne _020DE74C
	ldr r0, [r7, #0x4]
	mov r0, r0, lsl #0x1b
	mov r0, r0, lsr #0x1d
	tst r0, #0x1
	beq _020DE74C
	bic r0, r1, #0x7
	orr r0, r0, #0x2
	str r0, [r7, #0x8]
	mov r0, #0x0
	str r0, [r7, #0x28]
_020DE74C:
	ldr r0, [r7, #0x8]
	mov r0, r0, lsl #0x1d
	mov r0, r0, lsr #0x1d
	cmp r0, #0x2
	bhs _020DE778
	mov r0, #0x1
	strb r0, [r7, #0xd]
	mov r0, #0x0
	add sp, sp, #0x4
	str r0, [r7, #0x28]
	ldmia sp!, {r3-r10,pc}
_020DE778:
	ldr r0, [r7, #0x4]
	mov r0, r0, lsl #0x19
	mov r0, r0, lsr #0x1e
	tst r0, #0x1
	beq _020DE7B0
	bl __flush_line_buffered_output_files
	cmp r0, #0x0
	beq _020DE7B0
	mov r0, #0x1
	strb r0, [r7, #0xd]
	mov r0, #0x0
	add sp, sp, #0x4
	str r0, [r7, #0x28]
	ldmia sp!, {r3-r10,pc}
_020DE7B0:
	cmp r4, #0x0
	mov r5, #0x0
	beq _020DE874
	ldr r0, [r7, #0x8]
	mov r0, r0, lsl #0x1d
	mov r0, r0, lsr #0x1d
	cmp r0, #0x3
	blo _020DE874
	mov r10, r5
_020DE7D4:
	mov r0, r7
	mov r1, r10
	bl fwide
	cmp r0, #0x1
	ldr r0, [r7, #0x8]
	bne _020DE808
	mov r0, r0, lsl #0x1d
	add r0, r7, r0, lsr #0x1c
	ldrh r0, [r0, #0xe]
	add r5, r5, #0x2
	sub r4, r4, #0x2
	strh r0, [r9], #0x2
	b _020DE820
_020DE808:
	mov r0, r0, lsl #0x1d
	add r0, r7, r0, lsr #0x1d
	ldrb r0, [r0, #0xf]
	add r5, r5, #0x1
	sub r4, r4, #0x1
	strb r0, [r9], #0x1
_020DE820:
	ldr r1, [r7, #0x8]
	cmp r4, #0x0
	mov r0, r1, lsl #0x1d
	mov r0, r0, lsr #0x1d
	sub r0, r0, #0x1
	bic r1, r1, #0x7
	and r0, r0, #0x7
	orr r0, r1, r0
	str r0, [r7, #0x8]
	beq _020DE85C
	ldr r0, [r7, #0x8]
	mov r0, r0, lsl #0x1d
	mov r0, r0, lsr #0x1d
	cmp r0, #0x3
	bhs _020DE7D4
_020DE85C:
	ldr r0, [r7, #0x8]
	mov r0, r0, lsl #0x1d
	mov r0, r0, lsr #0x1d
	cmp r0, #0x2
	ldreq r0, [r7, #0x30]
	streq r0, [r7, #0x28]
_020DE874:
	cmp r4, #0x0
	beq _020DE938
	ldr r0, [r7, #0x28]
	cmp r0, #0x0
	cmpeq r6, #0x0
	beq _020DE938
	mov r10, #0x0
_020DE890:
	ldr r0, [r7, #0x28]
	cmp r0, #0x0
	bne _020DE8E4
	mov r0, r7
	mov r1, r10
	mov r2, r10
	bl __load_buffer
	cmp r0, #0x0
	beq _020DE8E4
	cmp r0, #0x1
	mov r0, #0x1
	streqb r0, [r7, #0xd]
	beq _020DE8D4
	ldr r1, [r7, #0x8]
	bic r1, r1, #0x7
	str r1, [r7, #0x8]
	strb r0, [r7, #0xc]
_020DE8D4:
	mov r0, #0x0
	str r0, [r7, #0x28]
	mov r4, #0x0
	b _020DE938
_020DE8E4:
	ldr r0, [r7, #0x28]
	str r0, [sp, #0x0]
	cmp r0, r4
	strhi r4, [sp, #0x0]
	ldr r1, [r7, #0x24]
	ldr r2, [sp, #0x0]
	mov r0, r9
	bl memcpy
	ldr r2, [sp, #0x0]
	ldr r0, [r7, #0x24]
	subs r4, r4, r2
	add r0, r0, r2
	str r0, [r7, #0x24]
	ldr r1, [r7, #0x28]
	ldr r0, [sp, #0x0]
	add r9, r9, r2
	sub r0, r1, r0
	add r5, r5, r2
	str r0, [r7, #0x28]
	cmpne r6, #0x0
	bne _020DE890
_020DE938:
	cmp r4, #0x0
	beq _020DE9C4
	cmp r6, #0x0
	bne _020DE9C4
	ldr r6, [r7, #0x1c]
	ldr r10, [r7, #0x20]
	add r1, sp, #0x0
	str r9, [r7, #0x1c]
	mov r0, r7
	mov r2, #0x1
	str r4, [r7, #0x20]
	bl __load_buffer
	cmp r0, #0x0
	beq _020DE9A4
	cmp r0, #0x1
	mov r0, #0x1
	bne _020DE98C
	strb r0, [r7, #0xd]
	mov r0, #0x0
	str r0, [r7, #0x28]
	b _020DE9A4
_020DE98C:
	ldr r1, [r7, #0x8]
	bic r1, r1, #0x7
	str r1, [r7, #0x8]
	strb r0, [r7, #0xc]
	mov r0, #0x0
	str r0, [r7, #0x28]
_020DE9A4:
	ldr r1, [sp, #0x0]
	mov r0, r7
	str r6, [r7, #0x1c]
	str r10, [r7, #0x20]
	add r5, r5, r1
	bl __prep_buffer
	mov r0, #0x0
	str r0, [r7, #0x28]
_020DE9C4:
	mov r0, r5
	mov r1, r8
	bl _u32_div_f
	add sp, sp, #0x4
	ldmia sp!, {r3-r10,pc}
	arm_func_end __fread

	arm_func_start __fwrite
__fwrite:
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x8
	mov r9, r3
	mov r10, r0
	str r1, [sp, #0x0]
	mov r0, r9
	mov r1, #0x0
	mov r4, r2
	bl fwide
	cmp r0, #0x0
	bne _020DEA10
	mov r0, r9
	mvn r1, #0x0
	bl fwide
_020DEA10:
	ldr r0, [sp, #0x0]
	muls r5, r0, r4
	beq _020DEA38
	ldrb r0, [r9, #0xd]
	cmp r0, #0x0
	bne _020DEA38
	ldr r1, [r9, #0x4]
	mov r0, r1, lsl #0x16
	movs r0, r0, lsr #0x1d
	bne _020DEA44
_020DEA38:
	add sp, sp, #0x8
	mov r0, #0x0
	ldmia sp!, {r3-r11,pc}
_020DEA44:
	mov r0, r1, lsl #0x13
	movs r0, r0, lsr #0x1f
	movne r0, r1, lsl #0x19
	movne r0, r0, lsr #0x1e
	cmpne r0, #0x2
	ldr r1, [r9, #0x8]
	cmpne r0, #0x1
	mov r8, #0x1
	mov r0, r1, lsl #0x1d
	movne r8, #0x0
	movs r0, r0, lsr #0x1d
	bne _020DEA9C
	ldr r0, [r9, #0x4]
	mov r0, r0, lsl #0x1b
	mov r0, r0, lsr #0x1d
	tst r0, #0x2
	beq _020DEA9C
	bic r0, r1, #0x7
	orr r1, r0, #0x1
	mov r0, r9
	str r1, [r9, #0x8]
	bl __prep_buffer
_020DEA9C:
	ldr r0, [r9, #0x8]
	mov r0, r0, lsl #0x1d
	mov r0, r0, lsr #0x1d
	cmp r0, #0x1
	beq _020DEAC8
	mov r0, #0x1
	strb r0, [r9, #0xd]
	mov r0, #0x0
	add sp, sp, #0x8
	str r0, [r9, #0x28]
	ldmia sp!, {r3-r11,pc}
_020DEAC8:
	cmp r5, #0x0
	mov r6, #0x0
	beq _020DEBF0
	ldr r0, [r9, #0x1c]
	ldr r2, [r9, #0x24]
	cmp r2, r0
	cmpeq r8, #0x0
	beq _020DEBF0
	ldr r1, [r9, #0x20]
	sub r0, r2, r0
	sub r0, r1, r0
	str r0, [r9, #0x28]
	mov r11, #0xa
	mov r4, #0x0
_020DEB00:
	ldr r0, [r9, #0x28]
	mov r7, r4
	str r0, [sp, #0x4]
	cmp r0, r5
	strhi r5, [sp, #0x4]
	ldr r0, [r9, #0x4]
	mov r0, r0, lsl #0x19
	mov r0, r0, lsr #0x1e
	cmp r0, #0x1
	bne _020DEB50
	ldr r2, [sp, #0x4]
	cmp r2, #0x0
	beq _020DEB50
	mov r0, r10
	mov r1, r11
	bl __memrchr
	movs r7, r0
	addne r0, r7, #0x1
	subne r0, r0, r10
	strne r0, [sp, #0x4]
_020DEB50:
	ldr r2, [sp, #0x4]
	cmp r2, #0x0
	beq _020DEB90
	ldr r0, [r9, #0x24]
	mov r1, r10
	bl memcpy
	ldr r2, [sp, #0x4]
	ldr r0, [r9, #0x24]
	add r10, r10, r2
	add r0, r0, r2
	str r0, [r9, #0x24]
	ldr r1, [r9, #0x28]
	ldr r0, [sp, #0x4]
	sub r5, r5, r2
	sub r0, r1, r0
	str r0, [r9, #0x28]
_020DEB90:
	ldr r0, [r9, #0x28]
	cmp r0, #0x0
	beq _020DEBB4
	cmp r7, #0x0
	bne _020DEBB4
	ldr r0, [r9, #0x4]
	mov r0, r0, lsl #0x19
	movs r0, r0, lsr #0x1e
	bne _020DEBDC
_020DEBB4:
	mov r0, r9
	mov r1, #0x0
	bl __flush_buffer
	cmp r0, #0x0
	beq _020DEBDC
	mov r0, #0x1
	strb r0, [r9, #0xd]
	mov r5, #0x0
	str r5, [r9, #0x28]
	b _020DEBF0
_020DEBDC:
	ldr r0, [sp, #0x4]
	cmp r5, #0x0
	add r6, r6, r0
	cmpne r8, #0x0
	bne _020DEB00
_020DEBF0:
	cmp r5, #0x0
	beq _020DEC5C
	cmp r8, #0x0
	bne _020DEC5C
	ldr r4, [r9, #0x1c]
	ldr r7, [r9, #0x20]
	add r2, r10, r5
	str r10, [r9, #0x1c]
	str r5, [r9, #0x20]
	add r1, sp, #0x4
	mov r0, r9
	str r2, [r9, #0x24]
	bl __flush_buffer
	cmp r0, #0x0
	ldreq r0, [sp, #0x4]
	addeq r6, r6, r0
	beq _020DEC44
	mov r0, #0x1
	strb r0, [r9, #0xd]
	mov r0, #0x0
	str r0, [r9, #0x28]
_020DEC44:
	str r4, [r9, #0x1c]
	mov r0, r9
	str r7, [r9, #0x20]
	bl __prep_buffer
	mov r0, #0x0
	str r0, [r9, #0x28]
_020DEC5C:
	ldr r0, [r9, #0x4]
	ldr r1, [sp, #0x0]
	mov r0, r0, lsl #0x19
	mov r0, r0, lsr #0x1e
	cmp r0, #0x2
	movne r0, #0x0
	strne r0, [r9, #0x28]
	mov r0, r6
	bl _u32_div_f
	add sp, sp, #0x8
	ldmia sp!, {r3-r11,pc}
	arm_func_end __fwrite

	.section .exceptix,4

	.word fread
	.short 269
	.word 0x00407F00
	.word __fread
	.short 841
	.word 0x00507F00
	.word __fwrite
	.short 689
	.word 0x0060FF00