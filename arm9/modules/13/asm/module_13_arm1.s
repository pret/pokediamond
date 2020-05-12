	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD13_02211EA4
MOD13_02211EA4: ; 0x02211EA4
	stmdb sp!, {lr}
	sub sp, sp, #4
	strh r1, [sp]
	add r2, sp, #0
	mov r1, #0xd
	bl MOD13_022130E8
	add sp, sp, #4
	ldmia sp!, {lr}
	bx lr

	arm_func_start MOD13_02211EC8
MOD13_02211EC8: ; 0x02211EC8
	cmp r0, #1
	blo _02211EDC
	cmp r0, #0xf
	movls r0, #1
	bxls lr
_02211EDC:
	mov r0, #0
	bx lr

	arm_func_start MOD13_02211EE4
MOD13_02211EE4: ; 0x02211EE4
	cmp r1, r0
	movls r1, r0
	mov r0, r1
	bx lr

	arm_func_start MOD13_02211EF4
MOD13_02211EF4: ; 0x02211EF4
	ldr r1, _02211F6C ; =0x02240A40
	mov r2, #1
	mov r2, r2, lsl r0
	ldr r1, [r1]
	ands r1, r1, r2
	bxeq lr
	ldr r2, _02211F70 ; =0x02240AFC
	ldr r1, _02211F74 ; =0x000005D4
	ldr r2, [r2]
	mla r3, r0, r1, r2
	add r0, r3, #0x1000
	ldrb r0, [r0, #0xd52]
	cmp r0, #0
	bxeq lr
	add r0, r3, #0x1d00
	ldrh r1, [r0, #0x4c]
	cmp r1, #0
	bxeq lr
	ldrh r2, [r0, #0x48]
	ldrh ip, [r0, #0x4a]
	cmp ip, r2
	bhi _02211F60
	add r1, ip, #2
	cmp r2, r1
	addle r1, r2, #1
	strleh r1, [r0, #0x48]
	bxle lr
_02211F60:
	add r0, r3, #0x1d00
	strh ip, [r0, #0x48]
	bx lr
	.align 2, 0
_02211F6C: .word 0x02240A40
_02211F70: .word 0x02240AFC
_02211F74: .word 0x000005D4

	arm_func_start MOD13_02211F78
MOD13_02211F78: ; 0x02211F78
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0xc
	add r1, sp, #0
	mov r0, #0
	mov r2, #0xa
	bl MIi_CpuClear16
	mov ip, #1
	ldr r0, _022120FC ; =0x02240AFC
	mov r4, ip
	ldr r3, [r0]
	mov r5, ip
	mov r0, ip
	mov r1, ip
	mov r2, ip
_02211FB0:
	sub lr, ip, #1
	add lr, r3, lr, lsl #2
	add lr, lr, #0x1000
	ldr lr, [lr, #0x4e8]
	cmp lr, #0xb
	addls pc, pc, lr, lsl #2
	b _02212048
_02211FCC: ; jump table
	b _02212048 ; case 0
	b _02212048 ; case 1
	b _02211FFC ; case 2
	b _02212048 ; case 3
	b _0221201C ; case 4
	b _0221200C ; case 5
	b _02212048 ; case 6
	b _02212048 ; case 7
	b _0221202C ; case 8
	b _02212048 ; case 9
	b _02212048 ; case 10
	b _0221203C ; case 11
_02211FFC:
	ldrh lr, [sp]
	orr lr, lr, r2, lsl ip
	strh lr, [sp]
	b _02212048
_0221200C:
	ldrh lr, [sp, #2]
	orr lr, lr, r1, lsl ip
	strh lr, [sp, #2]
	b _02212048
_0221201C:
	ldrh lr, [sp, #4]
	orr lr, lr, r0, lsl ip
	strh lr, [sp, #4]
	b _02212048
_0221202C:
	ldrh lr, [sp, #6]
	orr lr, lr, r5, lsl ip
	strh lr, [sp, #6]
	b _02212048
_0221203C:
	ldrh lr, [sp, #8]
	orr lr, lr, r4, lsl ip
	strh lr, [sp, #8]
_02212048:
	add ip, ip, #1
	mov ip, ip, lsl #0x10
	mov ip, ip, lsr #0x10
	cmp ip, #0xf
	bls _02211FB0
	ldrh r1, [sp, #6]
	cmp r1, #0
	beq _02212074
	mov r0, #5
	bl MOD13_02212614
	b _022120D4
_02212074:
	ldrh r1, [sp]
	cmp r1, #0
	beq _0221208C
	mov r0, #1
	bl MOD13_02212614
	b _022120D4
_0221208C:
	ldrh r1, [sp, #8]
	cmp r1, #0
	beq _022120A4
	mov r0, #6
	bl MOD13_02212614
	b _022120D4
_022120A4:
	ldrh r1, [sp, #4]
	cmp r1, #0
	beq _022120BC
	mov r0, #2
	bl MOD13_02212614
	b _022120D4
_022120BC:
	ldrh r0, [sp, #2]
	cmp r0, #0
	beq _022120D0
	bl MOD13_02212464
	b _022120D4
_022120D0:
	bl MOD13_02212104
_022120D4:
	cmp r0, #0x15
	addne sp, sp, #0xc
	ldmneia sp!, {r4, r5, lr}
	bxne lr
	ldr r1, _02212100 ; =0x0000FFFF
	mov r0, #0
	bl MOD13_02212614
	add sp, sp, #0xc
	ldmia sp!, {r4, r5, lr}
	bx lr
	.align 2, 0
_022120FC: .word 0x02240AFC
_02212100: .word 0x0000FFFF

	arm_func_start MOD13_02212104
MOD13_02212104: ; 0x02212104
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0x1c
	ldr r5, _022123B0 ; =0x02240AFC
	ldr r0, [r5]
	add r0, r0, #0x1000
	ldrb r0, [r0, #0x524]
	cmp r0, #0
	addeq sp, sp, #0x1c
	moveq r0, #0x15
	ldmeqia sp!, {r4, r5, r6, r7, lr}
	bxeq lr
	ldr r4, _022123B4 ; =0x000005D4
	mov r1, #0
_02212138:
	ldr r0, [r5]
	add r3, r0, #0x1000
	ldrb r0, [r3, #0x525]
	add r0, r0, #1
	mov r2, r0, lsr #0x1f
	rsb r0, r2, r0, lsl #28
	add r0, r2, r0, ror #28
	strb r0, [r3, #0x525]
	ldr r2, [r5]
	add r0, r2, #0x1000
	ldrb r0, [r0, #0x525]
	mla r3, r0, r4, r2
	add r2, r3, #0x1000
	ldrb r2, [r2, #0xd52]
	cmp r2, #0
	beq _02212188
	add r2, r3, #0x1d00
	ldrh r2, [r2, #0x4c]
	cmp r2, #0
	bne _02212198
_02212188:
	add r1, r1, #1
	and r1, r1, #0xff
	cmp r1, #0x10
	blo _02212138
_02212198:
	cmp r1, #0x10
	addeq sp, sp, #0x1c
	moveq r0, #0x15
	ldmeqia sp!, {r4, r5, r6, r7, lr}
	bxeq lr
	bl MOD13_02211EF4
	ldr r0, _022123B0 ; =0x02240AFC
	ldr r1, _022123B4 ; =0x000005D4
	ldr r6, [r0]
	ldr r2, _022123B8 ; =0x00001D2C
	add r0, r6, #0x1000
	ldrb r0, [r0, #0x525]
	ldr r3, _022123BC ; =0x00001788
	add r4, r6, r2
	mul r5, r0, r1
	add r0, r6, r5
	add r0, r0, #0x1d00
	ldrh r2, [r0, #0x48]
	add r3, r6, r3
	add r0, sp, #8
	add r1, r4, r5
	add r3, r3, r5
	bl MOD13_02213558
	cmp r0, #0
	addeq sp, sp, #0x1c
	moveq r0, #0x15
	ldmeqia sp!, {r4, r5, r6, r7, lr}
	bxeq lr
	ldr r0, _022123B0 ; =0x02240AFC
	mov r2, #4
	ldr r1, [r0]
	strb r2, [sp]
	add r2, r1, #0x1000
	ldrb r4, [r2, #0x525]
	ldr r3, _022123B4 ; =0x000005D4
	add r0, sp, #0
	strh r4, [sp, #2]
	ldrb r4, [r2, #0x525]
	mla r2, r4, r3, r1
	add r2, r2, #0x1d00
	ldrh r2, [r2, #0x48]
	strh r2, [sp, #4]
	bl MOD13_022171AC
	ldr r1, _022123B0 ; =0x02240AFC
	ldr r4, _022123B4 ; =0x000005D4
	ldr r5, [r1]
	ldrb r1, [sp, #0x14]
	add r2, r5, #0x1000
	ldrb r2, [r2, #0x525]
	ldr r6, [sp, #0x10]
	ldr r3, [sp, #0xc]
	mla r5, r2, r4, r5
	add r2, r5, r1, lsl #2
	add r4, r5, #0x1000
	add r2, r2, #0x1000
	ldr r5, [r4, #0xd58]
	ldr r2, [r2, #0xd2c]
	ldr r1, [r5, r1, lsl #2]
	sub r2, r6, r2
	add r7, r2, r1
	ldr r6, [r4, #0xd54]
	mov r2, r0
	mov r0, r6
	mov r1, r7
	bl MOD13_02216A68
	cmp r0, #0
	bne _02212378
	ldr r1, _022123B0 ; =0x02240AFC
	ldr r0, _022123C0 ; =0x00007CE0
	ldr r1, [r1]
	add r5, r1, r0
	mov r0, r5
	bl MOD13_02216D78
	cmp r0, #0
	bne _02212368
	ldr r0, [r6]
	cmp r0, #0
	subne r0, r0, #1
	strne r0, [r6]
	bne _02212368
	add lr, r6, #0x30
	mov r4, #0
	mov ip, r4
	mov r3, lr
_022122E8:
	add r0, lr, ip, lsl #4
	ldr r0, [r0, #0xc]
	mov r2, ip, lsl #4
	cmp r0, #2
	bne _02212318
	cmp r4, #0
	beq _02212314
	ldr r1, [r4]
	ldr r0, [lr, r2]
	cmp r1, r0
	bls _02212318
_02212314:
	mov r4, r3
_02212318:
	add ip, ip, #1
	cmp ip, #4
	add r3, r3, #0x10
	blt _022122E8
	cmp r4, #0
	bne _02212334
	bl OS_Terminate
_02212334:
	mov r0, #2
	str r0, [r6]
	mov r0, #1
	str r0, [r4, #0xc]
	bic r0, r7, #0x1f
	str r0, [r4]
	str r4, [r5, #0x10]
	ldr r1, _022123C4 ; =MOD13_022123C8
	mov r0, r5
	mov r2, #0
	mov r3, #4
	str r6, [r5, #0x14]
	bl MOD13_02216BE8
_02212368:
	add sp, sp, #0x1c
	mov r0, #0x15
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
_02212378:
	ldr r0, _022123B0 ; =0x02240AFC
	ldr r4, [sp, #0xc]
	ldr r2, [r0]
	ldr r1, _022123B4 ; =0x000005D4
	add r0, r2, #0x1000
	ldrb r3, [r0, #0x525]
	add r0, r4, #6
	mla r1, r3, r1, r2
	add r1, r1, #0x1d00
	ldrh r1, [r1, #0x4c]
	bl MOD13_022141E8
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
	.align 2, 0
_022123B0: .word 0x02240AFC
_022123B4: .word 0x000005D4
_022123B8: .word 0x00001D2C
_022123BC: .word 0x00001788
_022123C0: .word 0x00007CE0
_022123C4: .word MOD13_022123C8

	arm_func_start MOD13_022123C8
MOD13_022123C8: ; 0x022123C8
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x4c
	ldr r5, [r0, #0x14]
	ldr r4, [r0, #0x10]
	add r0, sp, #4
	bl FS_InitFile
	ldr r1, [r5, #0x14]
	add r0, r5, #0x10
	ldr r5, [r4]
	bl FS_FindArchive
	mvn r1, #0
	str r1, [sp]
	ldr r2, [r4, #4]
	mov r1, r0
	add r3, r5, r2
	add r0, sp, #4
	mov r2, r5
	bl FS_OpenFileDirect
	cmp r0, #0
	beq _02212440
	ldr r1, [r4, #8]
	ldr r2, [r4, #4]
	add r0, sp, #4
	bl FS_ReadFile
	ldr r1, [r4, #4]
	cmp r1, r0
	moveq r0, #2
	streq r0, [r4, #0xc]
	add r0, sp, #4
	bl FS_CloseFile
_02212440:
	ldr r0, [r4, #0xc]
	cmp r0, #2
	movne r0, #0
	strne r0, [r4]
	movne r0, #2
	strne r0, [r4, #0xc]
	add sp, sp, #0x4c
	ldmia sp!, {r4, r5, lr}
	bx lr

	arm_func_start MOD13_02212464
MOD13_02212464: ; 0x02212464
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #0x1c
	mov r4, #0
	add r0, sp, #6
	mov r1, r4
	mov r2, #0x10
	mvn r5, #0
	bl MI_CpuFill8
	ldr r1, _02212604 ; =0x02240AFC
	mov r0, #1
	ldr r1, [r1]
	add ip, sp, #6
_02212494:
	sub r3, r0, #1
	add r2, r1, r3, lsl #2
	add r2, r2, #0x1000
	ldr r2, [r2, #0x4e8]
	cmp r2, #5
	bne _022124C4
	add r2, r1, r3
	add r2, r2, #0x1500
	ldrsb r3, [r2, #0x26]
	ldrb r2, [ip, r3]
	add r2, r2, #1
	strb r2, [ip, r3]
_022124C4:
	add r0, r0, #1
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r0, #0xf
	bls _02212494
	ldr r2, _02212608 ; =0x0223F780
	mov r0, #0
	ldrb r3, [r2]
	add lr, sp, #6
	ldr ip, _0221260C ; =0x000005D4
_022124EC:
	add r2, r3, #1
	mov r3, r2, lsr #0x1f
	rsb r2, r3, r2, lsl #28
	add r2, r3, r2, ror #28
	and r3, r2, #0xff
	mla r2, r3, ip, r1
	add r2, r2, #0x1000
	ldrb r2, [r2, #0xd52]
	cmp r2, #0
	beq _02212528
	ldrb r2, [lr, r3]
	cmp r2, #0
	movne r0, r3, lsl #0x18
	movne r5, r0, asr #0x18
	bne _02212538
_02212528:
	add r0, r0, #1
	and r0, r0, #0xff
	cmp r0, #0x10
	blo _022124EC
_02212538:
	mvn r0, #0
	cmp r5, r0
	addeq sp, sp, #0x1c
	moveq r0, #0x15
	ldmeqia sp!, {r4, r5, lr}
	bxeq lr
	ldr r2, _02212608 ; =0x0223F780
	mov r0, #1
	strb r5, [r2]
	mov r3, r0
_02212560:
	sub ip, r0, #1
	add r2, r1, ip, lsl #2
	add r2, r2, #0x1000
	ldr r2, [r2, #0x4e8]
	cmp r2, #5
	bne _02212594
	add r2, r1, ip
	add r2, r2, #0x1500
	ldrsb r2, [r2, #0x26]
	cmp r5, r2
	orreq r2, r4, r3, lsl r0
	moveq r2, r2, lsl #0x10
	moveq r4, r2, lsr #0x10
_02212594:
	add r0, r0, #1
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	cmp r0, #0xf
	bls _02212560
	mov r2, #3
	add r0, sp, #0
	strb r2, [sp]
	strh r5, [sp, #2]
	bl MOD13_022171AC
	movs r1, r0
	beq _022125E4
	ldr r2, _02212604 ; =0x02240AFC
	ldr r0, _02212610 ; =0x00001788
	ldr r3, [r2]
	ldr r2, _0221260C ; =0x000005D4
	add r0, r3, r0
	mla r0, r5, r2, r0
	mov r2, #0xe4
	bl MI_CpuCopy8
_022125E4:
	ldr r0, _02212604 ; =0x02240AFC
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0xea
	bl MOD13_022141E8
	add sp, sp, #0x1c
	ldmia sp!, {r4, r5, lr}
	bx lr
	.align 2, 0
_02212604: .word 0x02240AFC
_02212608: .word 0x0223F780
_0221260C: .word 0x000005D4
_02212610: .word 0x00001788

	arm_func_start MOD13_02212614
MOD13_02212614: ; 0x02212614
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r2, _02212654 ; =0x02240AFC
	mov r4, r1
	ldr r1, [r2]
	strb r0, [sp]
	add r0, sp, #0
	bl MOD13_022171AC
	ldr r0, _02212654 ; =0x02240AFC
	mov r1, r4
	ldr r2, [r0]
	mov r0, #6
	bl MOD13_022141E8
	add sp, sp, #8
	ldmia sp!, {r4, lr}
	bx lr
	.align 2, 0
_02212654: .word 0x02240AFC

	arm_func_start MOD13_02212658
MOD13_02212658: ; 0x02212658
	stmdb sp!, {r4, r5, r6, lr}
	mov r4, r0
	mov r6, #0
	ldr r2, _02212700 ; =0x02240AFC
	mov r3, r6
	ldr r1, _02212704 ; =0x000005D4
_02212670:
	ldr r0, [r2]
	mla r5, r6, r1, r0
	add r0, r5, #0x1000
	ldrb r0, [r0, #0xd52]
	cmp r0, #0
	addne r0, r5, #0x1d00
	strneh r3, [r0, #0x4a]
	add r0, r6, #1
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
	cmp r6, #0x10
	blo _02212670
	ldr r0, _02212708 ; =0x02240A40
	mov r1, #0
	str r1, [r0]
	mov r6, #1
	ldr r5, _0221270C ; =0x0000FFFF
_022126B4:
	mov r0, r4
	mov r1, r6
	bl WM_ReadMPData
	cmp r0, #0
	beq _022126E4
	ldrh r1, [r0]
	cmp r1, r5
	beq _022126E4
	cmp r1, #0
	beq _022126E4
	mov r1, r6
	bl MOD13_02212710
_022126E4:
	add r0, r6, #1
	mov r0, r0, lsl #0x10
	mov r6, r0, lsr #0x10
	cmp r6, #0xf
	bls _022126B4
	ldmia sp!, {r4, r5, r6, lr}
	bx lr
	.align 2, 0
_02212700: .word 0x02240AFC
_02212704: .word 0x000005D4
_02212708: .word 0x02240A40
_0221270C: .word 0x0000FFFF

	arm_func_start MOD13_02212710
MOD13_02212710: ; 0x02212710
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x38
	movs r7, r1
	addeq sp, sp, #0x38
	ldmeqia sp!, {r4, r5, r6, r7, r8, lr}
	bxeq lr
	cmp r7, #0xf
	addhi sp, sp, #0x38
	ldmhiia sp!, {r4, r5, r6, r7, r8, lr}
	bxhi lr
	add r1, sp, #0
	mov r2, r7
	add r0, r0, #0xa
	bl MOD13_02217070
	ldr r3, _02212C14 ; =0x02240AFC
	ldrb r8, [sp]
	ldr r2, [r3]
	sub r4, r7, #1
	add r1, r2, r4, lsl #2
	add r1, r1, #0x1000
	ldr r6, [r1, #0x4e8]
	mov r5, r0
	cmp r8, #0xb
	addls pc, pc, r8, lsl #2
	b _02212C08
_02212774: ; jump table
	b _02212C08 ; case 0
	b _02212C08 ; case 1
	b _02212C08 ; case 2
	b _02212C08 ; case 3
	b _02212C08 ; case 4
	b _02212C08 ; case 5
	b _02212C08 ; case 6
	b _022127A4 ; case 7
	b _02212A30 ; case 8
	b _02212AEC ; case 9
	b _02212B68 ; case 10
	b _02212C08 ; case 11
_022127A4:
	cmp r6, #2
	bne _02212848
	cmp r5, #0
	addeq sp, sp, #0x38
	ldmeqia sp!, {r4, r5, r6, r7, r8, lr}
	bxeq lr
	add r1, sp, #0x14
	mov r2, #0x1d
	bl MI_CpuCopy8
	ldr r3, _02212C14 ; =0x02240AFC
	mov r0, r4
	ldr r1, [r3]
	ldr r2, [sp, #0x14]
	add r1, r1, r0, lsl #2
	add r1, r1, #0x1000
	str r2, [r1, #0x4a8]
	ldr r1, [r3]
	mov r2, #0x16
	add r1, r1, r0, lsl #1
	mul r8, r0, r2
	ldrh ip, [sp, #0x2e]
	add r1, r1, #0x1400
	add r0, sp, #0x18
	strh ip, [r1, #0x8a]
	ldr r1, [r3]
	add r1, r1, #0x1340
	add r1, r1, r8
	bl MI_CpuCopy8
	ldr r0, _02212C14 ; =0x02240AFC
	and r1, r7, #0xff
	ldr r0, [r0]
	and r2, r1, #0xf
	add ip, r0, #0x1340
	ldrb r3, [ip, r8]
	mov r0, r7
	mov r1, #0xa
	bic r3, r3, #0xf0
	orr r2, r3, r2, lsl #4
	strb r2, [ip, r8]
	add r2, sp, #0x18
	bl MOD13_02213124
_02212848:
	cmp r6, #0xa
	addne sp, sp, #0x38
	ldmneia sp!, {r4, r5, r6, r7, r8, lr}
	bxne lr
	ldrb r8, [r5, #0x1c]
	mov r2, #0
	cmp r8, #0x10
	bhs _022128A4
	ldr r0, _02212C14 ; =0x02240AFC
	ldr r1, _02212C18 ; =0x000005D4
	ldr r0, [r0]
	mla r6, r8, r1, r0
	add r1, r6, #0x1000
	ldrb r3, [r1, #0xd52]
	cmp r3, #0
	beq _022128A4
	add r3, r0, r4, lsl #2
	ldr r1, [r1, #0xd40]
	add r3, r3, #0x1000
	ldr r5, [r3, #0x4a8]
	ldr r3, [r1, #0x14]
	cmp r5, r3
	beq _022128C0
_022128A4:
	ldr r0, _02212C14 ; =0x02240AFC
	mov r1, #4
	ldr r0, [r0]
	add r0, r0, r4, lsl #1
	add r0, r0, #0x1700
	strh r1, [r0, #0x54]
	b _02212924
_022128C0:
	add r3, r6, #0x1d00
	ldrh r6, [r3, #0x4e]
	mov ip, r2
	mov r5, #1
_022128D0:
	mov r3, r5, lsl ip
	ands r3, r3, r6
	add r3, ip, #1
	addne r2, r2, #1
	and ip, r3, #0xff
	andne r2, r2, #0xff
	cmp ip, #0x10
	blo _022128D0
	ldrb r1, [r1, #0x18]
	cmp r2, r1
	blo _02212924
	add r1, r0, r4, lsl #1
	add r3, r1, #0x1700
	mov r2, #0
	mov r0, r7
	mov r1, #0xb
	strh r2, [r3, #0x54]
	bl MOD13_02213124
	add sp, sp, #0x38
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02212924:
	ldr r3, _02212C14 ; =0x02240AFC
	ldr r2, [r3]
	add r0, r2, r4, lsl #1
	add r4, r0, #0x1700
	ldrh r0, [r4, #0x54]
	cmp r0, #3
	beq _02212954
	cmp r0, #4
	beq _02212A10
	add sp, sp, #0x38
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02212954:
	add r0, r2, #0x1500
	mov r1, #1
	ldrh r0, [r0, #0x36]
	mov r6, r1, lsl r7
	ands r0, r0, r6
	addne sp, sp, #0x38
	ldmneia sp!, {r4, r5, r6, r7, r8, lr}
	bxne lr
	add r0, r2, #0x1000
	ldrb r2, [r0, #0x535]
	ldr r1, _02212C18 ; =0x000005D4
	sub r5, r7, #1
	add r2, r2, #1
	strb r2, [r0, #0x535]
	ldr r0, [r3]
	mul r4, r8, r1
	add r1, r0, #0x1500
	ldrh ip, [r1, #0x36]
	mov r0, r7
	mov r2, #0
	orr r7, ip, r6
	strh r7, [r1, #0x36]
	ldr r7, [r3]
	mov r1, #5
	add r7, r7, r5
	add r7, r7, #0x1000
	strb r8, [r7, #0x526]
	ldr r7, [r3]
	add r7, r7, r4
	add r7, r7, #0x1d00
	ldrh r8, [r7, #0x4e]
	orr r8, r8, r6
	strh r8, [r7, #0x4e]
	ldr r7, [r3]
	add r4, r7, r4
	add r4, r4, #0x1d00
	ldrh r7, [r4, #0x50]
	orr r6, r7, r6
	strh r6, [r4, #0x50]
	ldr r3, [r3]
	add r3, r3, r5, lsl #1
	add r3, r3, #0x1700
	strh r2, [r3, #0x54]
	bl MOD13_02213124
	add sp, sp, #0x38
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02212A10:
	mov r2, #0
	mov r0, r7
	mov r1, #4
	strh r2, [r4, #0x54]
	bl MOD13_02213124
	add sp, sp, #0x38
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02212A30:
	cmp r6, #5
	bne _02212A54
	mov r0, r7
	mov r1, #0xe
	mov r2, #0
	bl MOD13_02213124
	add sp, sp, #0x38
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02212A54:
	cmp r6, #0xe
	addne sp, sp, #0x38
	ldmneia sp!, {r4, r5, r6, r7, r8, lr}
	bxne lr
	add r0, r2, r4, lsl #1
	add r0, r0, #0x1700
	ldrh r0, [r0, #0x54]
	mov r5, r4, lsl #1
	cmp r0, #2
	addne sp, sp, #0x38
	ldmneia sp!, {r4, r5, r6, r7, r8, lr}
	bxne lr
	add r0, r2, r4
	add r0, r0, #0x1000
	ldrb r1, [r0, #0x526]
	ldr r0, _02212C18 ; =0x000005D4
	mov r6, #1
	mul r4, r1, r0
	add r0, r2, r4
	add r1, r0, #0x1d00
	ldrh r8, [r1, #0x4c]
	mov r2, #0
	mov r0, r7
	orr r6, r8, r6, lsl r7
	strh r6, [r1, #0x4c]
	ldr r6, [r3]
	mov r1, #6
	add r4, r6, r4
	add r4, r4, #0x1d00
	strh r2, [r4, #0x48]
	ldr r3, [r3]
	add r3, r3, r5
	add r3, r3, #0x1700
	strh r2, [r3, #0x54]
	bl MOD13_02213124
	add sp, sp, #0x38
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02212AEC:
	cmp r6, #6
	addne sp, sp, #0x38
	ldmneia sp!, {r4, r5, r6, r7, r8, lr}
	bxne lr
	add r0, r2, r4
	add r0, r0, #0x1000
	ldrb r5, [r0, #0x526]
	cmp r5, #0xff
	addeq sp, sp, #0x38
	ldmeqia sp!, {r4, r5, r6, r7, r8, lr}
	bxeq lr
	ldr r0, _02212C18 ; =0x000005D4
	ldrh r1, [sp, #2]
	mul r4, r5, r0
	add r0, r2, r4
	add r0, r0, #0x1d00
	ldrh r0, [r0, #0x4a]
	bl MOD13_02211EE4
	ldr r1, _02212C14 ; =0x02240AFC
	ldr r2, _02212C1C ; =0x02240A40
	ldr r1, [r1]
	mov r3, #1
	add r1, r1, r4
	add r1, r1, #0x1d00
	strh r0, [r1, #0x4a]
	ldr r0, [r2]
	add sp, sp, #0x38
	orr r0, r0, r3, lsl r5
	str r0, [r2]
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02212B68:
	cmp r6, #6
	bne _02212BC8
	add r0, r2, r4
	add r0, r0, #0x1000
	ldrb r3, [r0, #0x526]
	cmp r3, #0xff
	addeq sp, sp, #0x38
	ldmeqia sp!, {r4, r5, r6, r7, r8, lr}
	bxeq lr
	ldr r0, _02212C18 ; =0x000005D4
	mov r1, #1
	mla r0, r3, r0, r2
	add r3, r0, #0x1d00
	ldrh r2, [r3, #0x4c]
	mvn r0, r1, lsl r7
	and r4, r2, r0
	mov r0, r7
	mov r1, #7
	mov r2, #0
	strh r4, [r3, #0x4c]
	bl MOD13_02213124
	add sp, sp, #0x38
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02212BC8:
	cmp r6, #7
	addne sp, sp, #0x38
	ldmneia sp!, {r4, r5, r6, r7, r8, lr}
	bxne lr
	add r0, r2, r4, lsl #1
	add r3, r0, #0x1700
	ldrh r0, [r3, #0x54]
	cmp r0, #5
	addne sp, sp, #0x38
	ldmneia sp!, {r4, r5, r6, r7, r8, lr}
	bxne lr
	mov r2, #0
	mov r0, r7
	mov r1, #8
	strh r2, [r3, #0x54]
	bl MOD13_02213124
_02212C08:
	add sp, sp, #0x38
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
	.align 2, 0
_02212C14: .word 0x02240AFC
_02212C18: .word 0x000005D4
_02212C1C: .word 0x02240A40

	arm_func_start MOD13_02212C20
MOD13_02212C20: ; 0x02212C20
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	mov r6, r0
	mov r4, r1
	cmp r6, #0x19
	bgt _02212C84
	cmp r6, #0x19
	bge _02212ECC
	cmp r6, #0x11
	bgt _02212C78
	cmp r6, #0x11
	bge _02213084
	cmp r6, #3
	bgt _02213084
	cmp r6, #0
	blt _02213084
	cmp r6, #0
	beq _02212CC0
	cmp r6, #1
	beq _02212CE4
	cmp r6, #3
	beq _02212EC0
	b _02213084
_02212C78:
	cmp r6, #0x15
	beq _02212CAC
	b _02213084
_02212C84:
	cmp r6, #0xff
	bgt _02212CA0
	cmp r6, #0xff
	bge _02212F70
	cmp r6, #0x1c
	beq _02212ED4
	b _02213084
_02212CA0:
	cmp r6, #0x100
	beq _02212FE0
	b _02213084
_02212CAC:
	mov r2, r4
	mov r0, #0
	mov r1, #1
	bl MOD13_02213124
	b _02213084
_02212CC0:
	ldrh r0, [r4, #0x10]
	cmp r0, #0
	beq _02213084
	cmp r0, #0x10
	bhs _02213084
	mov r2, r4
	mov r1, #2
	bl MOD13_02213124
	b _02213084
_02212CE4:
	ldrh r0, [r4, #0x10]
	cmp r0, #0
	beq _02213084
	cmp r0, #0x10
	bhs _02213084
	ldr r2, _022130D8 ; =0x02240AFC
	sub r0, r0, #1
	ldr r3, [r2]
	mov r1, #0
	add r0, r3, r0, lsl #1
	add r0, r0, #0x1400
	strh r1, [r0, #0x8a]
	ldrh r3, [r4, #0x10]
	ldr r5, [r2]
	ldr r0, _022130DC ; =0x000014A8
	sub r2, r3, #1
	add r0, r5, r0
	add r0, r0, r2, lsl #2
	mov r2, #4
	bl MI_CpuFill8
	ldr r0, _022130D8 ; =0x02240AFC
	ldrh r1, [r4, #0x10]
	ldr r0, [r0]
	mov r2, #0x16
	add r0, r0, #0x1340
	sub r1, r1, #1
	mla r0, r1, r2, r0
	mov r1, #0
	bl MI_CpuFill8
	ldrh r0, [r4, #0x10]
	bl MOD13_02217234
	ldrh r1, [r4, #0x10]
	ldr r0, _022130D8 ; =0x02240AFC
	mov r3, #0
	ldr r2, [r0]
	sub r1, r1, #1
	add r1, r2, r1, lsl #1
	add r1, r1, #0x1700
	strh r3, [r1, #0x54]
	ldrh r8, [r4, #0x10]
	ldr r5, [r0]
	mvn r1, #0
	sub r7, r8, #1
	add r2, r5, r7
	add r2, r2, #0x1500
	ldrsb r3, [r2, #0x26]
	cmp r3, r1
	beq _02212E0C
	ldr r2, _022130E0 ; =0x000005D4
	and r3, r3, #0xff
	mul r2, r3, r2
	add r3, r5, r2
	add sb, r3, #0x1d00
	mov r5, #1
	ldrh sl, [sb, #0x4e]
	mvn r3, r5, lsl r8
	and sl, sl, r3
	strh sl, [sb, #0x4e]
	ldr sb, [r0]
	add sb, sb, r2
	add sb, sb, #0x1d00
	ldrh sl, [sb, #0x50]
	orr r5, sl, r5, lsl r8
	strh r5, [sb, #0x50]
	ldr r5, [r0]
	add r5, r5, r7
	add r5, r5, #0x1000
	strb r1, [r5, #0x526]
	ldr r0, [r0]
	add r0, r0, r2
	add r0, r0, #0x1d00
	ldrh r1, [r0, #0x4c]
	and r1, r1, r3
	strh r1, [r0, #0x4c]
_02212E0C:
	ldr r1, _022130D8 ; =0x02240AFC
	ldrh r2, [r4, #0x10]
	ldr r7, [r1]
	mov r3, #1
	add r0, r7, #0x1500
	ldrh r5, [r0, #0x36]
	mov r0, r3, lsl r2
	ands r0, r5, r0
	beq _02212E5C
	add r0, r7, #0x1000
	ldrb r2, [r0, #0x535]
	sub r2, r2, #1
	strb r2, [r0, #0x535]
	ldr r0, [r1]
	ldrh r1, [r4, #0x10]
	add r0, r0, #0x1500
	ldrh r2, [r0, #0x36]
	mvn r1, r3, lsl r1
	and r1, r2, r1
	strh r1, [r0, #0x36]
_02212E5C:
	ldrh r0, [r4, #0x10]
	ldr r1, _022130D8 ; =0x02240AFC
	ldr r2, [r1]
	sub r1, r0, #1
	add r1, r2, r1, lsl #2
	add r1, r1, #0x1000
	ldr r1, [r1, #0x4e8]
	cmp r1, #8
	bne _02212E8C
	mov r1, #9
	mov r2, #0
	bl MOD13_02213124
_02212E8C:
	ldrh r0, [r4, #0x10]
	mov r2, r4
	mov r1, #3
	bl MOD13_02213124
	ldrh r1, [r4, #0x10]
	ldr r0, _022130D8 ; =0x02240AFC
	mov r3, #0
	ldr r2, [r0]
	sub r0, r1, #1
	add r0, r2, r0, lsl #2
	add r0, r0, #0x1000
	str r3, [r0, #0x4e8]
	b _02213084
_02212EC0:
	mov r0, r4
	bl MOD13_02212658
	b _02213084
_02212ECC:
	bl MOD13_02211F78
	b _02213084
_02212ED4:
	mov r5, #0
	ldr sb, _022130D8 ; =0x02240AFC
	ldr r7, _022130E4 ; =0x0000186C
	ldr r8, _022130E0 ; =0x000005D4
	mov sl, r5
_02212EE8:
	mul r4, r5, r8
	ldr r1, [sb]
	add r2, r1, r4
	add r0, r2, #0x1000
	ldrb r0, [r0, #0xd52]
	cmp r0, #0
	beq _02212F38
	add r0, r2, #0x1d00
	ldrh r3, [r0, #0x50]
	cmp r3, #0
	beq _02212F38
	ldrh r2, [r0, #0x4e]
	add r0, r1, r7
	add r0, r0, r4
	add r1, r1, #0x1340
	bl MOD13_022148D4
	ldr r0, [sb]
	add r0, r0, r4
	add r0, r0, #0x1d00
	strh sl, [r0, #0x50]
_02212F38:
	add r0, r5, #1
	and r5, r0, #0xff
	cmp r5, #0x10
	blo _02212EE8
	bl MOD13_02214BF4
	mov r5, r0
	bl MOD13_02214BE0
	mov r4, r0
	bl MOD13_02214B80
	mov r2, r0
	mov r0, r5
	mov r1, r4
	bl MOD13_02214768
	b _02213084
_02212F70:
	ldrh r0, [r4, #2]
	cmp r0, #0xf
	addls pc, pc, r0, lsl #2
	b _02212FD0
_02212F80: ; jump table
	b _02212FD0 ; case 0
	b _02212FC0 ; case 1
	b _02212FD0 ; case 2
	b _02212FD0 ; case 3
	b _02212FC0 ; case 4
	b _02212FC0 ; case 5
	b _02212FC0 ; case 6
	b _02212FD0 ; case 7
	b _02212FC0 ; case 8
	b _02212FC0 ; case 9
	b _02212FD0 ; case 10
	b _02212FD0 ; case 11
	b _02212FD0 ; case 12
	b _02212FD0 ; case 13
	b _02212FD0 ; case 14
	b _02212FD0 ; case 15
_02212FC0:
	mov r0, #0
	mov r1, #9
	bl MOD13_02211EA4
	b _02213084
_02212FD0:
	mov r0, #0
	mov r1, #8
	bl MOD13_02211EA4
	b _02213084
_02212FE0:
	ldrh r0, [r4]
	cmp r0, #0x1d
	addls pc, pc, r0, lsl #2
	b _02213078
_02212FF0: ; jump table
	b _02213068 ; case 0
	b _02213078 ; case 1
	b _02213078 ; case 2
	b _02213078 ; case 3
	b _02213078 ; case 4
	b _02213078 ; case 5
	b _02213078 ; case 6
	b _02213068 ; case 7
	b _02213068 ; case 8
	b _02213078 ; case 9
	b _02213078 ; case 10
	b _02213078 ; case 11
	b _02213078 ; case 12
	b _02213068 ; case 13
	b _02213068 ; case 14
	b _02213068 ; case 15
	b _02213078 ; case 16
	b _02213068 ; case 17
	b _02213068 ; case 18
	b _02213078 ; case 19
	b _02213078 ; case 20
	b _02213068 ; case 21
	b _02213078 ; case 22
	b _02213078 ; case 23
	b _02213078 ; case 24
	b _02213068 ; case 25
	b _02213078 ; case 26
	b _02213078 ; case 27
	b _02213078 ; case 28
	b _02213068 ; case 29
_02213068:
	mov r0, #0
	mov r1, #9
	bl MOD13_02211EA4
	b _02213084
_02213078:
	mov r0, #0
	mov r1, #8
	bl MOD13_02211EA4
_02213084:
	cmp r6, #0x11
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	bxne lr
	ldr r1, _022130D8 ; =0x02240AFC
	mov r0, #0
	ldr r1, [r1]
	mov r2, #0x7d00
	add r3, r1, #0x1000
	ldr r4, [r3, #0x4e4]
	bl MIi_CpuClearFast
	ldr r1, _022130D8 ; =0x02240AFC
	mov r0, #0
	str r0, [r1]
	cmp r4, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	bxeq lr
	mov r2, r0
	mov r1, #0xc
	blx r4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	bx lr
	.align 2, 0
_022130D8: .word 0x02240AFC
_022130DC: .word 0x000014A8
_022130E0: .word 0x000005D4
_022130E4: .word 0x0000186C

	arm_func_start MOD13_022130E8
MOD13_022130E8: ; 0x022130E8
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r3, _02213120 ; =0x02240AFC
	ldr r3, [r3]
	add r3, r3, #0x1000
	ldr r3, [r3, #0x4e4]
	cmp r3, #0
	addeq sp, sp, #4
	ldmeqia sp!, {lr}
	bxeq lr
	blx r3
	add sp, sp, #4
	ldmia sp!, {lr}
	bx lr
	.align 2, 0
_02213120: .word 0x02240AFC

	arm_func_start MOD13_02213124
MOD13_02213124: ; 0x02213124
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	mov r5, r1
	mov r4, r2
	bl MOD13_02211EC8
	cmp r0, #0
	beq _02213158
	ldr r0, _02213170 ; =0x02240AFC
	sub r1, r6, #1
	ldr r0, [r0]
	add r0, r0, r1, lsl #2
	add r0, r0, #0x1000
	str r5, [r0, #0x4e8]
_02213158:
	mov r0, r6
	mov r1, r5
	mov r2, r4
	bl MOD13_022130E8
	ldmia sp!, {r4, r5, r6, lr}
	bx lr
	.align 2, 0
_02213170: .word 0x02240AFC

	arm_func_start MOD13_02213174
MOD13_02213174: ; 0x02213174
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r5, r1
	mov r7, r0
	bl OS_DisableInterrupts
	mov r4, r0
	cmp r5, #3
	addls pc, pc, r5, lsl #2
	b _022131D8
_02213198: ; jump table
	b _022131A8 ; case 0
	b _022131B4 ; case 1
	b _022131C0 ; case 2
	b _022131CC ; case 3
_022131A8:
	mov r5, #0xa
	mov r6, #4
	b _022131F0
_022131B4:
	mov r5, #0xa
	mov r6, #3
	b _022131F0
_022131C0:
	mov r5, #0xe
	mov r6, #2
	b _022131F0
_022131CC:
	mov r5, #7
	mov r6, #5
	b _022131F0
_022131D8:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
_022131F0:
	ldr r0, _0221326C ; =0x02240AFC
	ldr r0, [r0]
	cmp r0, #0
	beq _02213254
	mov r0, r7
	bl MOD13_02211EC8
	cmp r0, #0
	beq _02213254
	ldr r0, _0221326C ; =0x02240AFC
	sub r2, r7, #1
	ldr r1, [r0]
	add r0, r1, r2, lsl #2
	add r0, r0, #0x1000
	ldr r0, [r0, #0x4e8]
	cmp r5, r0
	bne _02213254
	add r0, r1, r2, lsl #1
	add r1, r0, #0x1700
	mov r0, r4
	strh r6, [r1, #0x54]
	bl OS_RestoreInterrupts
	add sp, sp, #4
	mov r0, #1
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
_02213254:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
	.align 2, 0
_0221326C: .word 0x02240AFC

	arm_func_start MOD13_02213270
MOD13_02213270: ; 0x02213270
	stmdb sp!, {r4, lr}
	ldr r1, _022132C8 ; =0x02240AFC
	mov r4, r0
	ldr r1, [r1]
	cmp r1, #0
	beq _022132BC
	bl MOD13_02211EC8
	cmp r0, #0
	beq _022132BC
	ldr r0, _022132C8 ; =0x02240AFC
	sub r1, r4, #1
	ldr r0, [r0]
	add r0, r0, r1, lsl #2
	add r0, r0, #0x1000
	ldr r0, [r0, #0x4e8]
	cmp r0, #7
	moveq r0, #1
	ldmeqia sp!, {r4, lr}
	bxeq lr
_022132BC:
	mov r0, #0
	ldmia sp!, {r4, lr}
	bx lr
	.align 2, 0
_022132C8: .word 0x02240AFC

	arm_func_start MOD13_022132CC
MOD13_022132CC: ; 0x022132CC
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	bl OS_DisableInterrupts
	ldr r1, _02213360 ; =0x02240AFC
	mov r4, r0
	ldr r0, [r1]
	cmp r0, #0
	beq _02213348
	mov r0, r5
	bl MOD13_02211EC8
	cmp r0, #0
	beq _02213348
	ldr r0, _02213360 ; =0x02240AFC
	sub r3, r5, #1
	ldr ip, [r0]
	ldr r1, _02213364 ; =0x00001772
	add r0, ip, #0x1340
	mov r2, #0x16
	mla r0, r3, r2, r0
	add r1, ip, r1
	bl MI_CpuCopy8
	mov r0, r4
	bl OS_RestoreInterrupts
	ldr r1, _02213360 ; =0x02240AFC
	ldr r0, _02213364 ; =0x00001772
	ldr r1, [r1]
	add sp, sp, #4
	add r0, r1, r0
	ldmia sp!, {r4, r5, lr}
	bx lr
_02213348:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, lr}
	bx lr
	.align 2, 0
_02213360: .word 0x02240AFC
_02213364: .word 0x00001772

	arm_func_start MOD13_02213368
MOD13_02213368: ; 0x02213368
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _02213390 ; =0x02240AFC
	ldr r1, [r1]
	add r1, r1, #0x1000
	str r4, [r1, #0x4e4]
	bl OS_RestoreInterrupts
	ldmia sp!, {r4, lr}
	bx lr
	.align 2, 0
_02213390: .word 0x02240AFC

	arm_func_start MOD13_02213394
MOD13_02213394: ; 0x02213394
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r3, _02213498 ; =0x0223C420
	ldr r3, [r3, r0, lsl #2]
	cmp r3, #0
	beq _022133BC
	cmp r3, #1
	beq _022133CC
	cmp r3, #2
	bne _02213478
_022133BC:
	bl MOD13_022134A8
	add sp, sp, #4
	ldmia sp!, {lr}
	bx lr
_022133CC:
	cmp r1, #0x2000000
	blo _02213444
	ldr r0, _0221349C ; =0x023FE800
	cmp r1, r0
	bhs _02213444
	cmp r1, #0x2300000
	add r1, r1, r2
	bhs _02213400
	cmp r1, #0x2300000
	addhi sp, sp, #4
	movhi r0, #0
	ldmhiia sp!, {lr}
	bxhi lr
_02213400:
	cmp r1, #0x2300000
	addls sp, sp, #4
	movls r0, #1
	ldmlsia sp!, {lr}
	bxls lr
	ldr r0, _0221349C ; =0x023FE800
	cmp r1, r0
	bhs _02213434
	cmp r2, #0x40000
	addls sp, sp, #4
	movls r0, #1
	ldmlsia sp!, {lr}
	bxls lr
_02213434:
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {lr}
	bx lr
_02213444:
	ldr r0, _022134A0 ; =0x037F8000
	cmp r1, r0
	blo _02213488
	ldr r0, _022134A4 ; =0x0380F000
	cmp r1, r0
	bhs _02213488
	add r1, r1, r2
	cmp r1, r0
	movls r0, #1
	add sp, sp, #4
	movhi r0, #0
	ldmia sp!, {lr}
	bx lr
_02213478:
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {lr}
	bx lr
_02213488:
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {lr}
	bx lr
	.align 2, 0
_02213498: .word 0x0223C420
_0221349C: .word 0x023FE800
_022134A0: .word 0x037F8000
_022134A4: .word 0x0380F000

	arm_func_start MOD13_022134A8
MOD13_022134A8: ; 0x022134A8
	ldr r3, _0221354C ; =0x0223C420
	ldr r0, [r3, r0, lsl #2]
	cmp r0, #0
	beq _022134EC
	cmp r0, #1
	beq _02213508
	cmp r0, #2
	bne _0221353C
	ldr r0, _02213550 ; =0x027FFE00
	cmp r1, r0
	blo _02213544
	ldr r0, _02213554 ; =0x027FFF60
	add r1, r1, r2
	cmp r1, r0
	bhi _02213544
	mov r0, #1
	bx lr
_022134EC:
	cmp r1, #0x2000000
	blo _02213544
	add r0, r1, r2
	cmp r0, #0x22c0000
	bhi _02213544
	mov r0, #1
	bx lr
_02213508:
	cmp r1, #0x22c0000
	blo _02213520
	add r0, r1, r2
	cmp r0, #0x2300000
	movls r0, #1
	bxls lr
_02213520:
	cmp r1, #0x2000000
	blo _02213544
	add r0, r1, r2
	cmp r0, #0x2300000
	bhi _02213544
	mov r0, #1
	bx lr
_0221353C:
	mov r0, #0
	bx lr
_02213544:
	mov r0, #0
	bx lr
	.align 2, 0
_0221354C: .word 0x0223C420
_02213550: .word 0x027FFE00
_02213554: .word 0x027FFF60

	arm_func_start MOD13_02213558
MOD13_02213558: ; 0x02213558
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldrh r4, [r1, #0x12]
	cmp r2, r4
	addhs sp, sp, #4
	movhs r0, #0
	ldmhsia sp!, {r4, r5, lr}
	bxhs lr
	mov ip, #2
_0221357C:
	add r4, r1, ip, lsl #1
	ldrh r4, [r4, #0xc]
	cmp r2, r4
	bhs _0221359C
	sub r4, ip, #1
	mov ip, r4, lsl #0x18
	movs ip, ip, asr #0x18
	bpl _0221357C
_0221359C:
	cmp ip, #0
	addlt sp, sp, #4
	movlt r0, #0
	ldmltia sp!, {r4, r5, lr}
	bxlt lr
	ldr r4, _02213628 ; =0x02240AFC
	add r5, r1, ip, lsl #1
	ldr lr, [r4]
	ldrh r5, [r5, #0xc]
	add lr, lr, #0x1000
	ldr lr, [lr, #0x318]
	sub r5, r2, r5
	mul r2, r5, lr
	add r3, r3, #0xc
	add r5, r3, ip, lsl #4
	ldr r3, [r5, #8]
	sub r3, r3, r2
	str r3, [r0, #4]
	ldr r3, [r4]
	ldr r4, [r0, #4]
	add r3, r3, #0x1000
	ldr r3, [r3, #0x318]
	cmp r4, r3
	strhi r3, [r0, #4]
	ldr r1, [r1, ip, lsl #2]
	add r1, r2, r1
	str r1, [r0, #8]
	ldr r1, [r5]
	add r1, r2, r1
	str r1, [r0]
	strb ip, [r0, #0xc]
	mov r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, lr}
	bx lr
	.align 2, 0
_02213628: .word 0x02240AFC

	arm_func_start MOD13_0221362C
MOD13_0221362C: ; 0x0221362C
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	mov r5, r0
	add r4, r5, #0xc
	cmp r1, #0
	mov r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	bxeq lr
	mov r2, r0
_0221364C:
	str r0, [r5, r2, lsl #2]
	add r3, r1, r2, lsl #4
	add r2, r2, #1
	ldr r3, [r3, #0x14]
	and r2, r2, #0xff
	cmp r2, #3
	add r0, r0, r3
	blo _0221364C
	mov r8, #0
	strh r8, [r4]
	ldr r6, _02213704 ; =0x02240AFC
	add r7, r1, #0xc
_0221367C:
	ldr r0, [r6]
	add sl, r7, r8, lsl #4
	add r0, r0, #0x1000
	ldr r1, [r0, #0x318]
	ldr sb, [sl, #8]
	add r0, sb, r1
	sub r0, r0, #1
	bl _u32_div_f
	mov r1, r8, lsl #1
	ldrh r3, [r4, r1]
	mov r2, r0, lsl #0x10
	ldr r1, [sl, #4]
	add r2, r3, r2, lsr #16
	mov r3, r2, lsl #0x10
	mov r2, sb
	mov r0, r8
	mov sb, r3, lsr #0x10
	bl MOD13_02213394
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	bxeq lr
	cmp r8, #2
	addlo r0, r8, #1
	movlo r0, r0, lsl #1
	strloh sb, [r4, r0]
	add r0, r8, #1
	and r8, r0, #0xff
	strhsh sb, [r5, #0x12]
	cmp r8, #3
	blo _0221367C
	mov r0, #1
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	bx lr
	.align 2, 0
_02213704: .word 0x02240AFC

	arm_func_start MOD13_02213708
MOD13_02213708: ; 0x02213708
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	ldr r1, [r1]
	mov r7, r2
	mov r6, r3
	cmp r1, #0
	beq _02213740
	cmp r1, #1
	beq _022137A4
	cmp r1, #2
	beq _02213880
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
_02213740:
	ldr r2, [r0, #0x28]
	add r3, r0, #0x28
	cmp r2, #0x2000000
	blo _02213794
	cmp r2, #0x22c0000
	bhs _02213794
	ldr r1, [r3, #4]
	add r0, r2, r1
	cmp r0, #0x22c0000
	bhi _02213794
	str r1, [r7, #8]
	ldr r0, [r3]
	add sp, sp, #4
	str r0, [r7, #4]
	ldr r0, [r7, #4]
	str r0, [r7]
	ldr r0, [r7, #0xc]
	bic r0, r0, #1
	str r0, [r7, #0xc]
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
_02213794:
	bl OS_Terminate
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
_022137A4:
	add r4, r0, #0x38
	ldr r2, [r0, #0x38]
	ldr r1, [r4, #4]
	mov ip, #0
	mov r5, ip
	cmp r2, #0x2000000
	add r3, r2, r1
	blo _022137F4
	ldr r0, _022138B0 ; =0x023FE800
	cmp r2, r0
	bhs _022137F4
	cmp r3, #0x2300000
	bls _02213820
	cmp r3, r0
	bhs _022137EC
	cmp r1, #0x40000
	movls r5, #1
	bls _02213820
_022137EC:
	mov ip, #1
	b _02213820
_022137F4:
	ldr r0, _022138B4 ; =0x037F8000
	cmp r2, r0
	blo _0221381C
	ldr r0, _022138B8 ; =0x0380F000
	cmp r2, r0
	bhs _0221381C
	cmp r3, r0
	movls r5, #1
	movhi ip, #1
	b _02213820
_0221381C:
	mov ip, #1
_02213820:
	cmp ip, #1
	bne _0221382C
	bl OS_Terminate
_0221382C:
	ldr r0, [r4, #4]
	cmp r5, #0
	str r0, [r7, #8]
	ldr r0, [r4]
	str r0, [r7, #4]
	ldreq r0, [r7, #4]
	streq r0, [r7]
	beq _02213864
	ldr r0, [r6]
	str r0, [r7]
	ldr r1, [r6]
	ldr r0, [r7, #8]
	add r0, r1, r0
	str r0, [r6]
_02213864:
	ldr r0, [r7, #0xc]
	add sp, sp, #4
	bic r0, r0, #1
	orr r0, r0, #1
	str r0, [r7, #0xc]
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
_02213880:
	mov r1, #0x160
	ldr r0, _022138BC ; =0x027FFE00
	str r1, [r7, #8]
	str r0, [r7, #4]
	ldr r0, [r7, #4]
	str r0, [r7]
	ldr r0, [r7, #0xc]
	bic r0, r0, #1
	str r0, [r7, #0xc]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
	.align 2, 0
_022138B0: .word 0x023FE800
_022138B4: .word 0x037F8000
_022138B8: .word 0x0380F000
_022138BC: .word 0x027FFE00

	arm_func_start MOD13_022138C0
MOD13_022138C0: ; 0x022138C0
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	sub sp, sp, #8
	mov r2, #0x22c0000
	mov r5, r1
	str r2, [sp]
	mov r6, r0
	ldr r0, [r5, #0x24]
	ldr r4, _02213940 ; =0x0223C420
	str r0, [r6]
	ldr r0, [r5, #0x34]
	add r8, r5, #0x160
	str r0, [r6, #4]
	add sl, r6, #0xc
	mov sb, #0
	add r7, sp, #0
_022138FC:
	mov r0, r5
	mov r1, r4
	mov r2, sl
	mov r3, r7
	bl MOD13_02213708
	add sb, sb, #1
	cmp sb, #3
	add sl, sl, #0x10
	add r4, r4, #4
	blt _022138FC
	mov r0, r8
	add r1, r6, #0x3c
	mov r2, #0x88
	bl MI_CpuCopy8
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, lr}
	bx lr
	.align 2, 0
_02213940: .word 0x0223C420

	arm_func_start MOD13_02213944
MOD13_02213944: ; 0x02213944
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	mov sb, r0
	mov r8, r1
	mov r6, #0xff
	bl OS_DisableInterrupts
	mov r5, r0
	bl MOD13_02214B60
	cmp r0, #0
	bne _02213984
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, lr}
	bx lr
_02213984:
	ldr r0, _02213BFC ; =0x02240AFC
	ldr r0, [r0]
	add r1, r0, #0x1000
	ldrb r1, [r1, #0x524]
	add r1, r1, #1
	cmp r1, #0x10
	ble _022139B8
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, lr}
	bx lr
_022139B8:
	ldr r1, _02213C00 ; =0x000005D4
	mov r4, #0
_022139C0:
	mla r2, r4, r1, r0
	add r2, r2, #0x1000
	ldr r3, [r2, #0xd40]
	cmp r3, sb
	bne _022139EC
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, lr}
	bx lr
_022139EC:
	ldrb r2, [r2, #0xd52]
	cmp r2, #0
	moveq r6, r4
	beq _02213A0C
	add r2, r4, #1
	and r4, r2, #0xff
	cmp r4, #0x10
	blo _022139C0
_02213A0C:
	cmp r4, #0x10
	bne _02213A2C
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, lr}
	bx lr
_02213A2C:
	ldr r1, _02213C00 ; =0x000005D4
	ldr r2, _02213BFC ; =0x02240AFC
	mul r4, r6, r1
	add r0, r0, r4
	add r0, r0, #0x1000
	str sb, [r0, #0xd40]
	ldr r2, [r2]
	ldr r0, _02213C04 ; =0x00001788
	mov r1, r8
	add r0, r2, r0
	add r7, r0, r4
	mov r0, r7
	bl MOD13_022138C0
	add r0, sb, #0x1c
	add r1, r7, #0xc4
	mov r2, #0x20
	bl MI_CpuCopy8
	ldr r1, _02213BFC ; =0x02240AFC
	ldr r0, _02213C08 ; =0x00001D2C
	ldr r2, [r1]
	mov r1, r7
	add r0, r2, r0
	add r0, r0, r4
	bl MOD13_0221362C
	cmp r0, #0
	bne _02213AAC
	mov r0, r5
	bl OS_RestoreInterrupts
	add sp, sp, #4
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, lr}
	bx lr
_02213AAC:
	ldr r1, _02213BFC ; =0x02240AFC
	ldr r0, _02213C0C ; =0x0000186C
	ldr r2, [r1]
	mov r1, sb
	add r0, r2, r0
	add r0, r0, r4
	add r2, r2, #0x1300
	bl MOD13_02214A0C
	ldr r2, _02213BFC ; =0x02240AFC
	ldr r1, _02213C0C ; =0x0000186C
	ldr r0, [r2]
	add r0, r0, r4
	add r0, r0, #0x1000
	strb r6, [r0, #0xd21]
	ldr r0, [r2]
	add r0, r0, r1
	add r0, r0, r4
	bl MOD13_02214868
	ldr r0, _02213C10 ; =0x02240A44
	ldr r1, _02213BFC ; =0x02240AFC
	ldrb r7, [r0]
	ldr r3, [r1]
	mov r2, #1
	add r6, r7, #1
	add r3, r3, r4
	strb r6, [r0]
	add r0, r3, #0x1000
	strb r7, [r0, #0xd1f]
	ldr r0, [r1]
	add r3, r8, #0x1e8
	add r0, r0, r4
	add r0, r0, #0x1d00
	strh r2, [r0, #0x4e]
	ldr r0, [r1]
	add r2, r8, #0x258
	add r0, r0, r4
	add r0, r0, #0x1000
	str r8, [r0, #0xd44]
	ldr r0, [r1]
	add r0, r0, r4
	add r0, r0, #0x1000
	str r3, [r0, #0xd54]
	ldr r0, [r1]
	add r0, r0, r4
	add r0, r0, #0x1000
	str r2, [r0, #0xd58]
	ldr r0, [r1]
	add r0, r0, r4
	add r0, r0, #0x1000
	ldr r0, [r0, #0xd54]
	ldr r0, [r0, #0x6c]
	cmp r0, #0
	beq _02213BB8
	bl MOD13_02216DA4
	cmp r0, #0
	bne _02213BB8
	ldr r1, _02213BFC ; =0x02240AFC
	ldr r0, _02213C14 ; =0x00007CE0
	ldr r1, [r1]
	add r0, r1, r0
	bl MOD13_02216D90
	ldr r1, _02213BFC ; =0x02240AFC
	ldr r0, _02213C18 ; =0x000074E0
	ldr r2, [r1]
	mov r1, #0x800
	add r0, r2, r0
	bl MOD13_02216DC0
_02213BB8:
	ldr r2, _02213BFC ; =0x02240AFC
	mov r3, #1
	ldr r1, [r2]
	mov r0, r5
	add r1, r1, r4
	add r1, r1, #0x1000
	strb r3, [r1, #0xd52]
	ldr r1, [r2]
	add r1, r1, #0x1000
	ldrb r2, [r1, #0x524]
	add r2, r2, #1
	strb r2, [r1, #0x524]
	bl OS_RestoreInterrupts
	mov r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, lr}
	bx lr
	.align 2, 0
_02213BFC: .word 0x02240AFC
_02213C00: .word 0x000005D4
_02213C04: .word 0x00001788
_02213C08: .word 0x00001D2C
_02213C0C: .word 0x0000186C
_02213C10: .word 0x02240A44
_02213C14: .word 0x00007CE0
_02213C18: .word 0x000074E0

	arm_func_start MOD13_02213C1C
MOD13_02213C1C: ; 0x02213C1C
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov lr, r1
	ldr ip, [r0]
	ldr r1, [r0, #0xc]
	cmp lr, #0x4000
	movlo lr, #0x4000
	cmp r2, #0x8000
	movhi r2, #0x8000
	cmp lr, ip
	add r1, ip, r1
	movlo lr, ip
	cmp r2, r1
	movhi r2, r1
	cmp lr, r2
	addhs sp, sp, #4
	ldmhsia sp!, {lr}
	bxhs lr
	cmp r3, #0
	beq _02213C8C
	ldr r0, [r0, #8]
	sub r2, r2, lr
	add r0, r0, lr
	mov r1, #0
	bl MI_CpuFill8
	add sp, sp, #4
	ldmia sp!, {lr}
	bx lr
_02213C8C:
	ldr r3, [r0, #4]
	ldr r1, [r0, #8]
	add r0, r3, lr
	add r1, r1, lr
	sub r2, r2, lr
	bl MI_CpuCopy8
	add sp, sp, #4
	ldmia sp!, {lr}
	bx lr

	arm_func_start MOD13_02213CB0
MOD13_02213CB0: ; 0x02213CB0
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x6c
	str r2, [sp, #4]
	cmp r2, #0x164
	mov r2, #0
	mov sl, r0
	mov sb, r1
	str r2, [sp, #8]
	blo _022140F4
	ldr r8, [sp, #4]
	mov r7, sb
	str r2, [sp, #0xc]
	mov r6, r2
	mov r5, r2
	cmp sl, #0
	add r7, r7, #0x160
	sub r8, r8, #0x160
	beq _02213D24
	ldr r4, [sl, #0x2c]
	ldr r3, [sl, #0x24]
	mov r2, #0x160
	sub fp, r4, r3
	bl FS_ReadFile
	cmp r0, #0x160
	ldr r4, [sb, #0x80]
	movlt r8, r5
	cmp r4, #0
	moveq r4, #0x1000000
	b _02213D9C
_02213D24:
	ldr r0, _02214104 ; =0x027FFE00
	mov r1, #1
	ldr r4, [r0, #0x80]
	add r0, sp, #0x20
	cmp r4, #0
	moveq r4, #0x1000000
	str r1, [sp, #0xc]
	bl FS_InitFile
	ldr r0, _02214108 ; =0x0223F788
	mov r1, #3
	bl FS_FindArchive
	mov r1, r0
	mvn r0, #0
	str r0, [sp]
	add r0, sp, #0x20
	mov r2, #0
	add r3, r4, #0x88
	bl FS_OpenFileDirect
	ldr r2, [sp, #0x4c]
	ldr r1, [sp, #0x44]
	ldr r0, _02214104 ; =0x027FFE00
	sub fp, r2, r1
	mov r1, sb
	mov r2, #0x160
	add sl, sp, #0x20
	bl MI_CpuCopy8
	ldr r1, [sb, #0x60]
	ldr r0, _0221410C ; =0x00406000
	orr r0, r1, r0
	str r0, [sb, #0x60]
_02213D9C:
	cmp r8, #0x88
	movlo r8, #0
	blo _02213DD0
	mov r0, sl
	add r1, fp, r4
	mov r2, #0
	bl FS_SeekFile
	mov r0, sl
	mov r1, r7
	mov r2, #0x88
	bl FS_ReadFile
	add r7, r7, #0x88
	sub r8, r8, #0x88
_02213DD0:
	cmp r8, #0x70
	blo _02213E40
	mov r0, r7
	mov r6, r7
	bl MOD13_02216B80
	add r7, r7, #0x70
	sub r8, r8, #0x70
	mov r0, #3
	str r0, [sp]
	mov r0, r6
	mov r1, #0
	mov r2, #0x160
	mov r3, sb
	bl MOD13_02216B0C
	ldr r0, [sl, #8]
	mov r4, #0
	b _02213E18
_02213E14:
	add r4, r4, #1
_02213E18:
	cmp r4, #3
	bge _02213E2C
	ldrsb r1, [r0, r4]
	cmp r1, #0
	bne _02213E14
_02213E2C:
	mov r2, r4
	add r1, r6, #0x10
	bl MI_CpuCopy8
	str r4, [r6, #0x14]
	b _02213E44
_02213E40:
	mov r8, #0
_02213E44:
	cmp r8, #0x10
	movlo r8, #0
	blo _02213E8C
	mov r0, #0
	str r0, [r7]
	ldr r0, [sl, #0x24]
	ldr r1, [sb, #0x20]
	add r0, fp, r0
	add r0, r1, r0
	str r0, [r7, #4]
	ldr r0, [sl, #0x24]
	ldr r1, [sb, #0x30]
	add r0, fp, r0
	add r0, r1, r0
	mov r5, r7
	str r0, [r7, #8]
	add r7, r7, #0x10
	sub r8, r8, #0x10
_02213E8C:
	ldr r1, [sb, #0x2c]
	ldr r0, [sb, #0x3c]
	add r0, r1, r0
	cmp r8, r0
	blo _02213F38
	ldr r4, [sl, #0x24]
	ldr r1, [r5, #4]
	mov r0, sl
	sub r1, r1, r4
	mov r2, #0
	bl FS_SeekFile
	ldr r2, [sb, #0x2c]
	mov r0, sl
	mov r1, r7
	bl FS_ReadFile
	mov r0, #3
	str r0, [sp]
	ldr r1, [r5, #4]
	ldr r2, [sb, #0x2c]
	mov r0, r6
	mov r3, r7
	bl MOD13_02216B0C
	ldr r1, [sb, #0x2c]
	mov r0, sl
	add r7, r7, r1
	ldr r1, [r5, #8]
	mov r2, #0
	sub r1, r1, r4
	bl FS_SeekFile
	ldr r2, [sb, #0x3c]
	mov r0, sl
	mov r1, r7
	bl FS_ReadFile
	mov r0, #3
	str r0, [sp]
	ldr r1, [r5, #8]
	ldr r2, [sb, #0x3c]
	mov r3, r7
	mov r0, r6
	bl MOD13_02216B0C
	mov r0, #1
	str r0, [sp, #8]
	b _0221400C
_02213F38:
	cmp r8, #0xcc00
	blo _0221400C
	ldr r4, [sl, #0x24]
	ldr r5, [r5, #4]
	mov r0, sl
	sub r1, r5, r4
	mov r2, #0
	bl FS_SeekFile
	mov r0, sl
	mov r1, r7
	mov r2, #0x4400
	bl FS_ReadFile
	mov r0, #3
	str r0, [sp]
	mov r0, r6
	mov r1, r5
	mov r2, #0x4400
	mov r3, r7
	bl MOD13_02216B0C
	add r1, r5, #0x4400
	mov r0, sl
	sub r1, r1, r4
	mov r2, #0
	bl FS_SeekFile
	mov r0, sl
	add r1, r7, #0x4400
	mov r2, #0x4400
	bl FS_ReadFile
	mov r0, #2
	str r0, [sp]
	mov r0, r6
	add r1, r5, #0x4400
	mov r2, #0x4400
	add r3, r7, #0x4400
	bl MOD13_02216B0C
	add r1, r5, #0x8800
	mov r0, sl
	sub r1, r1, r4
	mov r2, #0
	bl FS_SeekFile
	mov r0, sl
	add r1, r7, #0x8800
	mov r2, #0x4400
	bl FS_ReadFile
	mov r0, #2
	str r0, [sp]
	add r1, r5, #0x8800
	add r3, r7, #0x8800
	mov r0, r6
	mov r2, #0x4400
	bl MOD13_02216B0C
	mov r0, #1
	str r0, [sp, #8]
_0221400C:
	mov r0, sl
	mov r1, fp
	mov r2, #0
	bl FS_SeekFile
	ldr r0, [sp, #0xc]
	cmp r0, #0
	beq _022140DC
	add r0, sp, #0x20
	bl FS_CloseFile
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _022140DC
	ldr r1, [sb, #0x20]
	ldr r0, _02214110 ; =0x0223F784
	str r1, [sp, #0x10]
	ldr r2, [sb, #0x28]
	ldr r1, [sb, #0x20]
	ldr r4, [r0]
	sub r0, r2, r1
	str r0, [sp, #0x14]
	ldr r2, [r6, #0x48]
	ldr r1, [sb, #0x20]
	add r0, sp, #0x10
	sub r1, r2, r1
	str r1, [sp, #0x18]
	ldr r1, [sp, #4]
	mov r2, #0x8000
	str r1, [sp, #0x1c]
	mov r1, #0x4000
	mov r3, #1
	bl MOD13_02213C1C
	ldr r0, [r4, #4]
	cmp r0, #0
	beq _022140C4
	add r7, sp, #0x10
	mov r5, #0
_0221409C:
	ldr r1, [r4]
	ldr r2, [r4, #4]
	mov r0, r7
	mov r3, r5
	add r2, r1, r2
	bl MOD13_02213C1C
	add r4, r4, #8
	ldr r0, [r4, #4]
	cmp r0, #0
	bne _0221409C
_022140C4:
	ldr r1, [sb, #0x28]
	ldr r2, _02214114 ; =0x02000A74
	ldr r3, [r6, #0x48]
	ldr r0, _02214118 ; =0xE12FFF1E
	sub r1, r2, r1
	str r0, [r3, r1]
_022140DC:
	ldr r0, [sp, #8]
	cmp r0, #0
	beq _022140F4
	ldr r1, [sp, #4]
	mov r0, sb
	bl DC_FlushRange
_022140F4:
	ldr r0, [sp, #8]
	add sp, sp, #0x6c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	bx lr
	.align 2, 0
_02214104: .word 0x027FFE00
_02214108: .word 0x0223F788
_0221410C: .word 0x00406000
_02214110: .word 0x0223F784
_02214114: .word 0x02000A74
_02214118: .word 0xE12FFF1E

	arm_func_start MOD13_0221411C
MOD13_0221411C: ; 0x0221411C
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #0x64
	mov r6, #0
	movs r7, r0
	mov r5, r6
	beq _02214168
	ldr ip, [r7, #0x2c]
	ldr r3, [r7, #0x24]
	add r1, sp, #0
	mov r2, #0x60
	sub r4, ip, r3
	bl FS_ReadFile
	cmp r0, #0x60
	mov r0, r7
	mov r1, r4
	mov r2, #0
	addhs r6, sp, #0
	bl FS_SeekFile
	b _0221416C
_02214168:
	ldr r6, _0221419C ; =0x027FFE00
_0221416C:
	cmp r6, #0
	beq _0221418C
	ldr r1, [r6, #0x2c]
	ldr r0, [r6, #0x3c]
	add r1, r1, #0x268
	add r5, r1, r0
	cmp r5, #0x10000
	movlo r5, #0x10000
_0221418C:
	mov r0, r5
	add sp, sp, #0x64
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
	.align 2, 0
_0221419C: .word 0x027FFE00

	arm_func_start MOD13_022141A0
MOD13_022141A0: ; 0x022141A0
	mov r2, r1, asr #1
	cmp r2, #0
	mov r3, #0
	ble _022141C4
_022141B0:
	ldrh r1, [r0], #2
	sub r2, r2, #1
	cmp r2, #0
	add r3, r3, r1
	bgt _022141B0
_022141C4:
	ldr r0, _022141E4 ; =0x0000FFFF
	and r1, r3, r0
	add r1, r1, r3, lsr #16
	add r1, r1, r1, lsr #16
	eor r0, r1, r0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	bx lr
	.align 2, 0
_022141E4: .word 0x0000FFFF

	arm_func_start MOD13_022141E8
MOD13_022141E8: ; 0x022141E8
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	mov r4, r2
	add r2, r6, #0x1f
	mov r5, r1
	mov r0, r4
	bic r1, r2, #0x1f
	bl DC_FlushRange
	bl DC_WaitWriteBufferEmpty
	mov r0, r4
	mov r1, r6
	mov r2, r5
	bl MOD13_02214C08
	ldmia sp!, {r4, r5, r6, lr}
	bx lr

	arm_func_start MOD13_02214224
MOD13_02214224: ; 0x02214224
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x14
	ldr r3, _022144AC ; =0x02240A50
	str r0, [sp, #8]
	ldr r0, [r3, #4]
	ldrb r3, [r3, #0xe]
	ldrb r0, [r0, #0x4b4]
	str r1, [sp, #0xc]
	str r2, [sp, #0x10]
	cmp r3, r0
	beq _02214254
	bl MOD13_022144C8
_02214254:
	ldr r3, _022144B0 ; =0x02240A80
	ldr r1, _022144AC ; =0x02240A50
	ldrb r2, [r3, #4]
	ldr r0, [r1, #4]
	ldrb r5, [r1, #0x11]
	bic r2, r2, #3
	orr r2, r2, #2
	strb r2, [r3, #4]
	ldrb r4, [r0, #0x4b3]
	ldrb r2, [r1, #0xe]
	ldrb r7, [r3, #4]
	strb r4, [r3, #5]
	strb r2, [r3, #6]
	ldr r4, [r0, #0x4b8]
	ldr r2, _022144B4 ; =0x02240A48
	str r4, [r3]
	ldrb r6, [r0, #0x4b5]
	add r4, r5, #1
	bic r7, r7, #0xfc
	and r6, r6, #0x3f
	orr r6, r7, r6, lsl #2
	strb r6, [r3, #4]
	strb r4, [r1, #0x11]
	strb r5, [r3, #7]
	ldrb r4, [r0, #0x358]
	add r1, r0, #0x300
	ldr r2, [r2]
	strb r4, [r3, #0xa]
	ldrh r4, [r1, #0x5a]
	cmp r2, #0
	strh r4, [r3, #0xc]
	ldrh r1, [r1, #0x5c]
	strh r1, [r3, #0xe]
	bne _022142F4
	ldr r1, _022144B8 ; =0x02240A4C
	ldr r1, [r1]
	cmp r1, #0
	beq _022142F4
	ldr r0, [r0, #0x4b8]
	blx r1
_022142F4:
	ldr r0, _022144AC ; =0x02240A50
	ldr r1, _022144B0 ; =0x02240A80
	ldr r2, [r0, #4]
	mov r3, #0
_02214304:
	ldrb r0, [r2, #0x4a8]
	add r3, r3, #1
	cmp r3, #8
	strb r0, [r1, #0x68]
	add r2, r2, #1
	add r1, r1, #1
	blt _02214304
	ldr r1, _022144BC ; =0x02240A90
	mov r0, #0
	mov r2, #0x58
	bl MIi_CpuClear16
	ldr r0, _022144AC ; =0x02240A50
	mov sl, #0
	ldr r1, [r0, #4]
	ldr sb, _022144BC ; =0x02240A90
	add r0, r1, #0x400
	add r1, r1, #0x300
	ldrh r2, [r0, #0xb0]
	ldrh r0, [r1, #0x5a]
	mov r5, sl
	mov r8, sl
	eor r0, r2, r0
	mov r0, r0, lsl #0x10
	mov r7, r0, lsr #0x10
	mov fp, #0x16
	mov r4, #2
_0221436C:
	mov r6, r4, lsl r5
	ands r0, r7, r6
	beq _022143C0
	ldr r0, _022144AC ; =0x02240A50
	mov r1, sb
	ldr r2, [r0, #4]
	ldr r0, _022144C0 ; =0x0000035E
	add r0, r2, r0
	add r0, r0, r8
	mov r2, fp
	bl MIi_CpuCopy16
	ldr r0, _022144AC ; =0x02240A50
	add sl, sl, #1
	ldr r0, [r0, #4]
	add sb, sb, #0x16
	add r0, r0, #0x400
	ldrh r1, [r0, #0xb0]
	cmp sl, #4
	orr r1, r1, r6
	strh r1, [r0, #0xb0]
	beq _022143D0
_022143C0:
	add r5, r5, #1
	cmp r5, #0xf
	add r8, r8, #0x16
	blt _0221436C
_022143D0:
	cmp sl, #4
	bhs _022143F0
	mov r0, #0x16
	mul r1, sl, r0
	ldr r2, _022144BC ; =0x02240A90
	ldrb r0, [r2, r1]
	bic r0, r0, #0xf0
	strb r0, [r2, r1]
_022143F0:
	ldr r2, _022144B0 ; =0x02240A80
	mov r3, #0
	ldr r0, _022144C4 ; =0x02240A88
	mov r1, #0x68
	strh r3, [r2, #8]
	bl MOD13_022141A0
	ldr r2, _022144AC ; =0x02240A50
	ldr r1, _022144B0 ; =0x02240A80
	ldr r3, [r2, #4]
	strh r0, [r1, #8]
	add r0, r3, #0x400
	add r1, r3, #0x300
	ldrh r3, [r0, #0xb0]
	ldrh r0, [r1, #0x5a]
	ldr r1, _022144B0 ; =0x02240A80
	cmp r3, r0
	moveq r0, #1
	streqb r0, [r2, #0xc]
	ldr r0, [sp, #0x10]
	ldr r3, [sp, #8]
	orr r2, r0, #3
	ldr r0, [sp, #0xc]
	and r4, r2, #0xff
	str r0, [sp]
	mov r0, #0
	mov r2, #0x70
	str r4, [sp, #4]
	bl WM_SetGameInfo
	ldr r0, _022144B4 ; =0x02240A48
	ldr r0, [r0]
	cmp r0, #1
	addne sp, sp, #0x14
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	bxne lr
	ldr r0, _022144B8 ; =0x02240A4C
	ldr r1, [r0]
	cmp r1, #0
	addeq sp, sp, #0x14
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	bxeq lr
	ldr r0, _022144AC ; =0x02240A50
	ldr r0, [r0, #4]
	ldr r0, [r0, #0x4b8]
	blx r1
	add sp, sp, #0x14
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	bx lr
	.align 2, 0
_022144AC: .word 0x02240A50
_022144B0: .word 0x02240A80
_022144B4: .word 0x02240A48
_022144B8: .word 0x02240A4C
_022144BC: .word 0x02240A90
_022144C0: .word 0x0000035E
_022144C4: .word 0x02240A88

	arm_func_start MOD13_022144C8
MOD13_022144C8: ; 0x022144C8
	ldr r1, _022144F4 ; =0x02240A50
	mov r3, #1
	ldr r0, [r1, #4]
	mov r2, #5
	add r0, r0, #0x400
	strh r3, [r0, #0xb0]
	ldr r0, [r1, #4]
	ldrb r0, [r0, #0x4b4]
	strb r0, [r1, #0xe]
	strb r2, [r1, #0xc]
	bx lr
	.align 2, 0
_022144F4: .word 0x02240A50

	arm_func_start MOD13_022144F8
MOD13_022144F8: ; 0x022144F8
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #8
	ldr r3, _02214660 ; =0x02240A50
	mov r6, r0
	ldr r0, [r3, #4]
	ldr r3, [r3, #8]
	add r7, r0, #0x358
	add r0, r3, #0x62
	cmp r0, r7
	mov r5, r1
	ldrls r0, _02214664 ; =0x02240A80
	movls r1, #0x62
	mov r4, r2
	strlsb r1, [r0, #0xc]
	bls _02214558
	ldr r0, _02214664 ; =0x02240A80
	sub r1, r7, r3
	strb r1, [r0, #0xc]
	ldrb r2, [r0, #0xc]
	ldr r1, _02214668 ; =0x02240A8E
	mov r0, #0
	add r1, r1, r2
	rsb r2, r2, #0x62
	bl MIi_CpuClear16
_02214558:
	ldr r0, _02214664 ; =0x02240A80
	ldr r1, _02214660 ; =0x02240A50
	ldrb r2, [r0, #0xc]
	ldr r0, [r1, #8]
	ldr r1, _02214668 ; =0x02240A8E
	bl MIi_CpuCopy16
	ldr r3, _02214660 ; =0x02240A50
	ldr r2, _02214664 ; =0x02240A80
	ldrb r8, [r3, #0xf]
	ldrb r1, [r3, #0x10]
	ldrb r7, [r2, #4]
	strb r8, [r2, #0xa]
	ldr r0, [r3, #4]
	strb r1, [r2, #0xb]
	ldrb r1, [r0, #0x4b2]
	bic r7, r7, #3
	ldrb r8, [r3, #0xe]
	and r1, r1, #3
	orr r1, r7, r1
	strb r1, [r2, #4]
	ldrb ip, [r0, #0x4b3]
	ldrb r1, [r2, #4]
	ldrb r7, [r3, #0x11]
	strb ip, [r2, #5]
	strb r8, [r2, #6]
	ldr r8, [r0, #0x4b8]
	bic r1, r1, #0xfc
	str r8, [r2]
	ldrb r0, [r0, #0x4b5]
	add lr, r7, #1
	mov ip, #0
	and r0, r0, #0x3f
	orr r8, r1, r0, lsl #2
	ldr r0, _0221466C ; =0x02240A88
	mov r1, #0x68
	strb r8, [r2, #4]
	strb lr, [r3, #0x11]
	strb r7, [r2, #7]
	strh ip, [r2, #8]
	bl MOD13_022141A0
	ldr r1, _02214660 ; =0x02240A50
	ldr r2, _02214664 ; =0x02240A80
	ldrb ip, [r1, #0xf]
	strh r0, [r2, #8]
	ldrb r3, [r1, #0x10]
	add r0, ip, #1
	strb r0, [r1, #0xf]
	ldrb r0, [r1, #0xf]
	mov r2, #0x70
	cmp r0, r3
	ldrlo r0, [r1, #8]
	mov r3, r6
	addlo r0, r0, #0x62
	strlo r0, [r1, #8]
	movhs r0, #4
	strhsb r0, [r1, #0xc]
	orr r0, r4, #3
	and r4, r0, #0xff
	str r5, [sp]
	ldr r1, _02214664 ; =0x02240A80
	mov r0, #0
	str r4, [sp, #4]
	bl WM_SetGameInfo
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
	.align 2, 0
_02214660: .word 0x02240A50
_02214664: .word 0x02240A80
_02214668: .word 0x02240A8E
_0221466C: .word 0x02240A88

	arm_func_start MOD13_02214670
MOD13_02214670: ; 0x02214670
	ldr r0, _022146B8 ; =0x02240A50
	ldrb r1, [r0, #0xc]
	cmp r1, #2
	bxne lr
	ldr r2, [r0, #4]
	ldrb r1, [r2, #0x4b2]
	cmp r1, #0
	moveq r1, #9
	streqb r1, [r0, #0x10]
	streq r2, [r0, #8]
	addne r1, r2, #0x220
	movne r2, #4
	strne r1, [r0, #8]
	strneb r2, [r0, #0x10]
	ldr r0, _022146B8 ; =0x02240A50
	mov r1, #3
	strb r1, [r0, #0xc]
	bx lr
	.align 2, 0
_022146B8: .word 0x02240A50

	arm_func_start MOD13_022146BC
MOD13_022146BC: ; 0x022146BC
	stmdb sp!, {r4, lr}
	sub sp, sp, #8
	ldr r0, _02214760 ; =0x02240A50
	ldr r1, [r0]
	cmp r1, #0
	bne _02214710
	bl MOD13_02214BF4
	mov r4, r0
	bl MOD13_02214BE0
	str r0, [sp]
	mov ip, #8
	ldr r1, _02214764 ; =0x02240A80
	mov r3, r4
	mov r0, #0
	mov r2, #0x70
	str ip, [sp, #4]
	bl WM_SetGameInfo
	add sp, sp, #8
	mov r0, #0
	ldmia sp!, {r4, lr}
	bx lr
_02214710:
	ldr r0, [r0, #4]
	cmp r0, #0
	beq _0221472C
	ldr r0, [r0, #0x4bc]
	cmp r0, #0
	beq _0221472C
	mov r1, r0
_0221472C:
	ldr r0, _02214760 ; =0x02240A50
	str r1, [r0, #4]
	bl MOD13_02214810
	ldr r1, _02214760 ; =0x02240A50
	mov r2, #2
	ldr r3, [r1, #4]
	mov r0, #1
	ldrb r3, [r3, #0x4b4]
	strb r3, [r1, #0xe]
	strb r2, [r1, #0xc]
	add sp, sp, #8
	ldmia sp!, {r4, lr}
	bx lr
	.align 2, 0
_02214760: .word 0x02240A50
_02214764: .word 0x02240A80

	arm_func_start MOD13_02214768
MOD13_02214768: ; 0x02214768
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r7, r0
	mov r6, r1
	mov r5, r2
	ldr r4, _0221480C ; =0x02240A50
_02214780:
	ldrb r0, [r4, #0xc]
	cmp r0, #6
	addls pc, pc, r0, lsl #2
	b _02214780
_02214790: ; jump table
	b _022147AC ; case 0
	b _022147AC ; case 1
	b _022147C4 ; case 2
	b _022147CC ; case 3
	b _022147E8 ; case 4
	b _022147F0 ; case 5
	b _02214780 ; case 6
_022147AC:
	bl MOD13_022146BC
	cmp r0, #0
	bne _02214780
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
_022147C4:
	bl MOD13_02214670
	b _02214780
_022147CC:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl MOD13_022144F8
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
_022147E8:
	bl MOD13_022144C8
	b _02214780
_022147F0:
	mov r0, r7
	mov r1, r6
	mov r2, r5
	bl MOD13_02214224
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
	.align 2, 0
_0221480C: .word 0x02240A50

	arm_func_start MOD13_02214810
MOD13_02214810: ; 0x02214810
	ldr r0, _02214830 ; =0x02240A50
	mov r1, #0
	strb r1, [r0, #0xd]
	strb r1, [r0, #0xe]
	strb r1, [r0, #0xf]
	strb r1, [r0, #0x10]
	strb r1, [r0, #0x11]
	bx lr
	.align 2, 0
_02214830: .word 0x02240A50

	arm_func_start MOD13_02214834
MOD13_02214834: ; 0x02214834
	ldr r1, _0221485C ; =0x02240A50
	mov r3, #0
	ldr r0, _02214860 ; =0x02240A4C
	mov r2, #1
	ldr ip, _02214864 ; =MOD13_02214810
	str r3, [r1]
	str r3, [r1, #4]
	strb r2, [r1, #0xc]
	str r3, [r0]
	bx ip
	.align 2, 0
_0221485C: .word 0x02240A50
_02214860: .word 0x02240A4C
_02214864: .word MOD13_02214810

	arm_func_start MOD13_02214868
MOD13_02214868: ; 0x02214868
	ldr r1, _022148A8 ; =0x02240A50
	ldr r2, [r1]
	cmp r2, #0
	streq r0, [r1]
	beq _0221489C
	ldr r1, [r2, #0x4bc]
	cmp r1, #0
	beq _02214898
_02214888:
	mov r2, r1
	ldr r1, [r1, #0x4bc]
	cmp r1, #0
	bne _02214888
_02214898:
	str r0, [r2, #0x4bc]
_0221489C:
	mov r1, #0
	str r1, [r0, #0x4bc]
	bx lr
	.align 2, 0
_022148A8: .word 0x02240A50

	arm_func_start MOD13_022148AC
MOD13_022148AC: ; 0x022148AC
	ldrh r1, [r0], #2
	mov r2, #0
	cmp r1, #0
	beq _022148CC
_022148BC:
	ldrh r1, [r0], #2
	add r2, r2, #1
	cmp r1, #0
	bne _022148BC
_022148CC:
	mov r0, r2
	bx lr

	arm_func_start MOD13_022148D4
MOD13_022148D4: ; 0x022148D4
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	ldr r4, _02214950 ; =0x0000035E
	mov r6, r0
	mov r5, r2
	mov r0, r1
	ldr r2, _02214954 ; =0x0000014A
	add r1, r6, r4
	mov r4, r3
	mov r7, #1
	bl MIi_CpuCopy16
	mov r2, #0
	mov r1, #2
_02214908:
	mov r0, r1, lsl r2
	ands r0, r5, r0
	addne r0, r7, #1
	add r2, r2, #1
	andne r7, r0, #0xff
	cmp r2, #0xf
	blt _02214908
	strb r7, [r6, #0x358]
	orr r1, r5, #1
	add r0, r6, #0x300
	strh r1, [r0, #0x5a]
	strh r4, [r0, #0x5c]
	ldrb r0, [r6, #0x4b4]
	add r0, r0, #1
	strb r0, [r6, #0x4b4]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
	.align 2, 0
_02214950: .word 0x0000035E
_02214954: .word 0x0000014A

	arm_func_start MOD13_02214958
MOD13_02214958: ; 0x02214958
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x48
	cmp r2, #0
	movne r4, #0x200
	moveq r4, #0x20
	mov r6, r0
	mov r5, r1
	cmp r2, #0
	addne r5, r5, #0x20
	cmp r6, #0
	addeq sp, sp, #0x48
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, lr}
	bxeq lr
	add r0, sp, #0
	bl FS_InitFile
	add r0, sp, #0
	mov r1, r6
	bl FS_OpenFile
	cmp r0, #0
	addeq sp, sp, #0x48
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, lr}
	bxeq lr
	ldr r1, [sp, #0x28]
	ldr r0, [sp, #0x24]
	sub r0, r1, r0
	cmp r4, r0
	beq _022149E4
	add r0, sp, #0
	bl FS_CloseFile
	add sp, sp, #0x48
	mov r0, #0
	ldmia sp!, {r4, r5, r6, lr}
	bx lr
_022149E4:
	add r0, sp, #0
	mov r1, r5
	mov r2, r4
	bl FS_ReadFile
	add r0, sp, #0
	bl FS_CloseFile
	mov r0, #1
	add sp, sp, #0x48
	ldmia sp!, {r4, r5, r6, lr}
	bx lr

	arm_func_start MOD13_02214A0C
MOD13_02214A0C: ; 0x02214A0C
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r6, r0
	mov r5, r1
	mov r4, r2
	mov r1, r6
	mov r0, #0
	mov r2, #0x4c0
	bl MIi_CpuClear16
	mov r0, #0
	strb r0, [r6, #0x4b2]
	ldr r0, [r5, #0xc]
	mov r1, r6
	mov r2, #1
	bl MOD13_02214958
	cmp r0, #0
	moveq r7, #1
	ldr r0, [r5, #0x10]
	mov r1, r6
	mov r2, #0
	movne r7, #0
	bl MOD13_02214958
	cmp r0, #0
	moveq r0, #1
	movne r0, #0
	orrs r0, r7, r0
	beq _02214A90
	mov r3, #1
	mov r1, r6
	mov r0, #0
	mov r2, #0x220
	strb r3, [r6, #0x4b2]
	bl MIi_CpuClearFast
_02214A90:
	ldr r0, [r5, #0x14]
	cmp r4, #0
	str r0, [r6, #0x4b8]
	beq _02214AB0
	mov r0, r4
	add r1, r6, #0x220
	mov r2, #0x16
	bl MIi_CpuCopy16
_02214AB0:
	ldrb r0, [r5, #0x18]
	strb r0, [r6, #0x236]
	ldr r0, [r5, #4]
	bl MOD13_022148AC
	mov r2, r0, lsl #0x11
	ldr r0, [r5, #4]
	add r1, r6, #0x238
	mov r2, r2, lsr #0x10
	bl MIi_CpuCopy16
	ldr r0, [r5, #8]
	add r1, r6, #0x298
	mov r2, #0xc0
	bl MIi_CpuCopy16
	mov r1, #1
	strb r1, [r6, #0x358]
	add r0, r6, #0x300
	strh r1, [r0, #0x5a]
	add r0, r6, #0x400
	strh r1, [r0, #0xb0]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr

	arm_func_start MOD13_02214B08
MOD13_02214B08: ; 0x02214B08
	stmdb sp!, {lr}
	sub sp, sp, #4
	cmp r1, #2
	addeq sp, sp, #4
	ldmeqia sp!, {lr}
	bxeq lr
	cmp r1, #0
	addeq sp, sp, #4
	ldmeqia sp!, {lr}
	bxeq lr
	ldr r2, _02214B5C ; =0x02240AF8
	strh r0, [sp]
	ldr r0, [r2]
	strh r1, [sp, #2]
	ldr r2, [r0, #0x51c]
	add r1, sp, #0
	mov r0, #0xff
	blx r2
	add sp, sp, #4
	ldmia sp!, {lr}
	bx lr
	.align 2, 0
_02214B5C: .word 0x02240AF8

	arm_func_start MOD13_02214B60
MOD13_02214B60: ; 0x02214B60
	ldr r0, _02214B7C ; =0x02240AF8
	ldr r0, [r0]
	ldrb r0, [r0, #0x50d]
	cmp r0, #1
	moveq r0, #1
	movne r0, #0
	bx lr
	.align 2, 0
_02214B7C: .word 0x02240AF8

	arm_func_start MOD13_02214B80
MOD13_02214B80: ; 0x02214B80
	ldr r0, _02214BDC ; =0x02240AF8
	ldr r1, [r0]
	ldrh r0, [r1, #0x12]
	cmp r0, #0
	ldrh r0, [r1, #0xe]
	movne r2, #2
	moveq r2, #0
	cmp r0, #0
	movne r3, #1
	ldrh r0, [r1, #0x14]
	moveq r3, #0
	cmp r0, #0
	movne ip, #4
	ldrh r0, [r1, #0x16]
	moveq ip, #0
	cmp r0, #0
	movne r1, #8
	orr r0, r3, r2
	moveq r1, #0
	orr r0, ip, r0
	orr r0, r1, r0
	and r0, r0, #0xff
	bx lr
	.align 2, 0
_02214BDC: .word 0x02240AF8

	arm_func_start MOD13_02214BE0
MOD13_02214BE0: ; 0x02214BE0
	ldr r0, _02214BF0 ; =0x02240AF8
	ldr r0, [r0]
	ldrh r0, [r0, #0xc]
	bx lr
	.align 2, 0
_02214BF0: .word 0x02240AF8

	arm_func_start MOD13_02214BF4
MOD13_02214BF4: ; 0x02214BF4
	ldr r0, _02214C04 ; =0x02240AF8
	ldr r0, [r0]
	ldr r0, [r0, #8]
	bx lr
	.align 2, 0
_02214C04: .word 0x02240AF8

	arm_func_start MOD13_02214C08
MOD13_02214C08: ; 0x02214C08
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr ip, _02214D04 ; =0x02240AF8
	mov r3, r1, lsl #0x10
	ldr r5, [ip]
	mov ip, r2, lsl #0x10
	add lr, r5, #0x500
	ldrh r4, [lr, #0x28]
	mov r1, r0
	mov r2, r3, lsr #0x10
	cmp r4, #0
	mov r4, ip, lsr #0x10
	beq _02214C48
	ldrh r0, [lr, #0x26]
	cmp r0, #1
	bne _02214C58
_02214C48:
	add sp, sp, #4
	mov r0, #1
	ldmia sp!, {r4, r5, lr}
	bx lr
_02214C58:
	ldrh r0, [lr, #0x24]
	cmp r0, #1
	beq _02214C70
	cmp r0, #2
	beq _02214CBC
	b _02214CF4
_02214C70:
	ldrh r0, [lr, #0x2c]
	cmp r0, #0
	moveq r0, #0x3e8
	movne r0, #0
	mov r3, r0, lsl #0x10
	str r4, [sp]
	ldr r0, [r5, #0x508]
	mov r3, r3, lsr #0x10
	bl MOD13_02214D0C
	cmp r0, #2
	ldreq r1, _02214D04 ; =0x02240AF8
	moveq r2, #1
	ldreq r1, [r1]
	add sp, sp, #4
	streqb r2, [r1, #0x50c]
	cmp r0, #2
	moveq r0, #0
	ldmia sp!, {r4, r5, lr}
	bx lr
_02214CBC:
	ldr r0, _02214D08 ; =MOD13_02215724
	mov r3, #0
	str r4, [sp]
	bl MOD13_02214D0C
	cmp r0, #2
	ldreq r1, _02214D04 ; =0x02240AF8
	moveq r2, #1
	ldreq r1, [r1]
	add sp, sp, #4
	streqb r2, [r1, #0x50c]
	cmp r0, #2
	moveq r0, #0
	ldmia sp!, {r4, r5, lr}
	bx lr
_02214CF4:
	mov r0, #1
	add sp, sp, #4
	ldmia sp!, {r4, r5, lr}
	bx lr
	.align 2, 0
_02214D04: .word 0x02240AF8
_02214D08: .word MOD13_02215724

	arm_func_start MOD13_02214D0C
MOD13_02214D0C: ; 0x02214D0C
	stmdb sp!, {r4, lr}
	sub sp, sp, #0x10
	ldrh r4, [sp, #0x18]
	mov r3, r2
	mov r2, r1
	str r4, [sp]
	mov r4, #1
	str r4, [sp, #4]
	mov r4, #3
	mov r1, #0
	str r4, [sp, #8]
	bl WM_SetMPDataToPortEx
	mov r4, r0
	mov r1, r4
	mov r0, #0xf
	bl MOD13_02214B08
	mov r0, r4
	add sp, sp, #0x10
	ldmia sp!, {r4, lr}
	bx lr

	arm_func_start MOD13_02214D5C
MOD13_02214D5C: ; 0x02214D5C
	ldr r1, _02214D68 ; =0x02240B00
	strh r0, [r1, #6]
	bx lr
	.align 2, 0
_02214D68: .word 0x02240B00

	arm_func_start MOD13_02214D6C
MOD13_02214D6C: ; 0x02214D6C
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	mov r5, r0
	ldr r0, _02214F08 ; =MOD13_02216098
	mov r1, r5
	bl WM_Disconnect
	cmp r5, #0
	addeq sp, sp, #4
	ldmeqia sp!, {r4, r5, r6, r7, lr}
	bxeq lr
	cmp r5, #0x10
	addhs sp, sp, #4
	ldmhsia sp!, {r4, r5, r6, r7, lr}
	bxhs lr
	ldr r2, _02214F0C ; =0x02240AFC
	sub r4, r5, #1
	ldr r0, [r2]
	mov r1, #0
	add r0, r0, r4, lsl #1
	add r0, r0, #0x1400
	strh r1, [r0, #0x8a]
	ldr r3, [r2]
	ldr r0, _02214F10 ; =0x000014A8
	mov r2, #4
	add r0, r3, r0
	add r0, r0, r4, lsl #2
	bl MI_CpuFill8
	ldr r0, _02214F0C ; =0x02240AFC
	mov r2, #0x16
	ldr r0, [r0]
	mov r1, #0
	add r0, r0, #0x1340
	mla r0, r4, r2, r0
	bl MI_CpuFill8
	mov r0, r5
	bl MOD13_02217234
	ldr lr, _02214F0C ; =0x02240AFC
	mov r2, #0
	ldr r1, [lr]
	mvn r0, #0
	add r1, r1, r4, lsl #1
	add r1, r1, #0x1700
	strh r2, [r1, #0x54]
	ldr r3, [lr]
	add r1, r3, r4
	add r1, r1, #0x1500
	ldrsb r2, [r1, #0x26]
	cmp r2, r0
	beq _02214E9C
	ldr r1, _02214F14 ; =0x000005D4
	and r2, r2, #0xff
	mul r1, r2, r1
	add r2, r3, r1
	add ip, r2, #0x1d00
	mov r3, #1
	ldrh r6, [ip, #0x4e]
	mvn r2, r3, lsl r5
	and r6, r6, r2
	strh r6, [ip, #0x4e]
	ldr r7, [lr]
	mov r6, r4
	add r7, r7, r1
	add ip, r7, #0x1d00
	ldrh r7, [ip, #0x50]
	orr r3, r7, r3, lsl r5
	strh r3, [ip, #0x50]
	ldr r3, [lr]
	add r3, r3, r6
	add r3, r3, #0x1000
	strb r0, [r3, #0x526]
	ldr r0, [lr]
	add r0, r0, r1
	add r0, r0, #0x1d00
	ldrh r1, [r0, #0x4c]
	and r1, r1, r2
	strh r1, [r0, #0x4c]
_02214E9C:
	ldr r1, _02214F0C ; =0x02240AFC
	mov r0, #1
	ldr r2, [r1]
	mov r5, r0, lsl r5
	add r0, r2, #0x1500
	ldrh r0, [r0, #0x36]
	ands r0, r0, r5
	beq _02214EE4
	add r0, r2, #0x1000
	ldrb r3, [r0, #0x535]
	mvn r2, r5
	sub r3, r3, #1
	strb r3, [r0, #0x535]
	ldr r0, [r1]
	add r0, r0, #0x1500
	ldrh r1, [r0, #0x36]
	and r1, r1, r2
	strh r1, [r0, #0x36]
_02214EE4:
	ldr r0, _02214F0C ; =0x02240AFC
	mov r1, #0
	ldr r0, [r0]
	add r0, r0, r4, lsl #2
	add r0, r0, #0x1000
	str r1, [r0, #0x4e8]
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
	.align 2, 0
_02214F08: .word MOD13_02216098
_02214F0C: .word 0x02240AFC
_02214F10: .word 0x000014A8
_02214F14: .word 0x000005D4

	arm_func_start MOD13_02214F18
MOD13_02214F18: ; 0x02214F18
	stmdb sp!, {r4, lr}
	bl OS_DisableInterrupts
	ldr r1, _02214F54 ; =0x02240AFC
	mov r4, r0
	ldr r0, [r1]
	add r0, r0, #0x1000
	ldr r0, [r0, #0x320]
	cmp r0, #0
	bne _02214F40
	bl OS_Terminate
_02214F40:
	bl MOD13_02214F58
	mov r0, r4
	bl OS_RestoreInterrupts
	ldmia sp!, {r4, lr}
	bx lr
	.align 2, 0
_02214F54: .word 0x02240AFC

	arm_func_start MOD13_02214F58
MOD13_02214F58: ; 0x02214F58
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, #1
	bl OS_DisableInterrupts
	ldr r1, _02214FD8 ; =0x02240AF8
	mov r4, r0
	ldr r2, [r1]
	add r0, r2, #0x500
	ldrh r0, [r0, #0x26]
	cmp r0, #0
	bne _02214FC0
	mov r0, #0
	str r0, [r2, #0x5e4]
	ldr r0, [r1]
	mov r1, r5
	add r0, r0, #0x500
	strh r1, [r0, #0x26]
	bl MOD13_02216DA4
	cmp r0, #0
	beq _02214FB8
	ldr r0, _02214FDC ; =MOD13_02214FE0
	bl MOD13_02216B94
	mov r5, #0
	b _02214FC0
_02214FB8:
	bl MOD13_02214FEC
	mov r5, r0
_02214FC0:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r5
	add sp, sp, #4
	ldmia sp!, {r4, r5, lr}
	bx lr
	.align 2, 0
_02214FD8: .word 0x02240AF8
_02214FDC: .word MOD13_02214FE0

	arm_func_start MOD13_02214FE0
MOD13_02214FE0: ; 0x02214FE0
	ldr ip, _02214FE8 ; =MOD13_02214FEC
	bx ip
	.align 2, 0
_02214FE8: .word MOD13_02214FEC

	arm_func_start MOD13_02214FEC
MOD13_02214FEC: ; 0x02214FEC
	stmdb sp!, {r4, lr}
	ldr r0, _02215024 ; =0x02240AF8
	ldr r0, [r0]
	ldr r0, [r0, #0x508]
	bl WM_Reset
	mov r4, r0
	mov r1, r4
	mov r0, #1
	bl MOD13_02214B08
	cmp r4, #2
	moveq r4, #0
	mov r0, r4
	ldmia sp!, {r4, lr}
	bx lr
	.align 2, 0
_02215024: .word 0x02240AF8

	arm_func_start MOD13_02215028
MOD13_02215028: ; 0x02215028
	ldr r1, _02215044 ; =0x02240AFC
	ldr ip, _02215048 ; =MOD13_0221504C
	ldr r1, [r1]
	mov r2, #1
	add r1, r1, #0x1000
	str r2, [r1, #0x320]
	bx ip
	.align 2, 0
_02215044: .word 0x02240AFC
_02215048: .word MOD13_0221504C

	arm_func_start MOD13_0221504C
MOD13_0221504C: ; 0x0221504C
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r4, r0
	bl OS_DisableInterrupts
	ldr r1, _02215234 ; =0x02240AF8
	ldr r2, _02215238 ; =0x02240AFC
	ldr r3, [r1]
	ldr r1, _0221523C ; =0x00007D1F
	strh r4, [r3, #0x32]
	ldr r3, [r2]
	ldr r2, _02215240 ; =0x02240AF4
	add r1, r3, r1
	bic r1, r1, #0x1f
	mov r4, r0
	str r1, [r2]
	add r0, r3, #0x1000
	ldr r5, [r0, #0x4e4]
	ldr r2, _02215244 ; =0x000069C0
	add r1, r3, #0x1340
	mov r0, #0
	bl MIi_CpuClear16
	mov r0, r5
	bl MOD13_02213368
	ldr r1, _02215234 ; =0x02240AF8
	ldr r0, _02215238 ; =0x02240AFC
	ldr r3, [r1]
	ldr r2, [r0]
	add r0, r3, #0x500
	ldrh r3, [r0]
	add r0, r2, #0x1000
	sub r2, r3, #6
	str r2, [r0, #0x318]
	ldr r0, [r1]
	add r0, r0, #0x500
	ldrh r0, [r0, #2]
	bl MOD13_022172A0
	ldr r1, _02215238 ; =0x02240AFC
	ldr r0, _02215248 ; =0x00001538
	ldr r1, [r1]
	add r0, r1, r0
	bl MOD13_02217280
	mov r5, #0
	ldr r2, _02215238 ; =0x02240AFC
	mov r0, r5
	mvn r3, #0
_02215100:
	ldr r1, [r2]
	add r1, r1, r5, lsl #2
	add r1, r1, #0x1000
	str r0, [r1, #0x4e8]
	ldr r1, [r2]
	add r1, r1, r5
	add r1, r1, #0x1000
	add r5, r5, #1
	strb r3, [r1, #0x526]
	cmp r5, #0xf
	blt _02215100
	ldr r1, [r2]
	ldr r3, _0221524C ; =0x00001788
	add r1, r1, #0x1000
	strb r0, [r1, #0x524]
	ldr r1, [r2]
	ldr r2, _02215250 ; =0x00005D40
	add r1, r1, r3
	bl MIi_CpuClear16
	ldr r1, _02215238 ; =0x02240AFC
	ldr r0, _02215254 ; =0x00001754
	ldr r2, [r1]
	mov r1, #0
	add r0, r2, r0
	mov r2, #0x1e
	bl MI_CpuFill8
	ldr r2, _02215234 ; =0x02240AF8
	mov r3, #1
	ldr r0, [r2]
	ldr r1, _02215258 ; =MOD13_02212C20
	add r0, r0, #0x500
	strh r3, [r0, #0x24]
	ldr r0, [r2]
	ldr r3, _0221525C ; =MOD13_02216098
	str r1, [r0, #0x51c]
	ldr r0, [r2]
	mov r1, #0xf
	str r3, [r0, #0x508]
	ldr r3, [r2]
	add r0, r3, #0x500
	ldrh r0, [r0]
	strh r0, [r3, #0x34]
	ldr r0, [r2]
	ldrh r3, [r0, #0x34]
	add r0, r0, #0x500
	add r3, r3, #0x23
	bic r3, r3, #0x1f
	strh r3, [r0, #0x18]
	ldr r3, [r2]
	add r0, r3, #0x500
	ldrh r0, [r0, #2]
	strh r0, [r3, #0x36]
	ldr r0, [r2]
	ldrh r2, [r0, #0x36]
	add r0, r0, #0x500
	add r2, r2, #0xe
	mul r1, r2, r1
	add r1, r1, #0x29
	bic r1, r1, #0x1f
	mov r1, r1, lsl #1
	strh r1, [r0, #0x1a]
	bl MOD13_02214834
	bl MOD13_02215260
	mov r5, r0
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, #0xf
	mov r1, #1
	bl PXI_IsCallbackReady
	ldr r1, _02215238 ; =0x02240AFC
	ldr r1, [r1]
	add r1, r1, #0x7000
	str r0, [r1, #0x4c8]
	mov r0, r5
	add sp, sp, #4
	ldmia sp!, {r4, r5, lr}
	bx lr
	.align 2, 0
_02215234: .word 0x02240AF8
_02215238: .word 0x02240AFC
_0221523C: .word 0x00007D1F
_02215240: .word 0x02240AF4
_02215244: .word 0x000069C0
_02215248: .word 0x00001538
_0221524C: .word 0x00001788
_02215250: .word 0x00005D40
_02215254: .word 0x00001754
_02215258: .word MOD13_02212C20
_0221525C: .word MOD13_02216098

	arm_func_start MOD13_02215260
MOD13_02215260: ; 0x02215260
	stmdb sp!, {r4, r5, r6, lr}
	ldr r2, _02215350 ; =0x02240AF8
	mov r3, #0
	ldr r1, [r2]
	mov r0, #0xa
	add r1, r1, #0x500
	strh r3, [r1, #0x28]
	ldr r1, [r2]
	add r1, r1, #0x500
	strh r3, [r1, #0x2a]
	ldr r1, [r2]
	add r1, r1, #0x500
	strh r3, [r1, #0x26]
	ldr r1, [r2]
	add r1, r1, #0x500
	strh r3, [r1, #0x48]
	bl MOD13_02214D5C
	ldr r0, _02215354 ; =0x02240AFC
	ldr r0, [r0]
	add r0, r0, #0x1000
	ldr r0, [r0, #0x320]
	cmp r0, #0
	bne _02215320
	ldr r6, _02215358 ; =0x02240AF4
	ldr r5, _02215350 ; =0x02240AF8
	ldr r4, _0221535C ; =0x02240AF0
_022152C8:
	ldr r1, [r5]
	ldrh r2, [r4]
	ldr r0, [r6]
	ldr r1, [r1, #0x508]
	bl WM_Initialize
	cmp r0, #4
	beq _022152C8
	cmp r0, #2
	movne r0, #8
	ldmneia sp!, {r4, r5, r6, lr}
	bxne lr
	ldr r0, _02215350 ; =0x02240AF8
	ldr r0, [r0]
	ldr r0, [r0, #0x508]
	bl WM_SetIndCallback
	ldr r0, _02215350 ; =0x02240AF8
	mov r2, #1
	ldr r1, [r0]
	mov r0, #0
	strb r2, [r1, #0x50d]
	ldmia sp!, {r4, r5, r6, lr}
	bx lr
_02215320:
	ldr r0, _02215350 ; =0x02240AF8
	ldr r0, [r0]
	ldr r0, [r0, #0x508]
	bl WM_SetIndCallback
	ldr r0, _02215350 ; =0x02240AF8
	mov r1, #1
	ldr r0, [r0]
	strb r1, [r0, #0x50d]
	bl MOD13_02216910
	mov r0, #0
	ldmia sp!, {r4, r5, r6, lr}
	bx lr
	.align 2, 0
_02215350: .word 0x02240AF8
_02215354: .word 0x02240AFC
_02215358: .word 0x02240AF4
_0221535C: .word 0x02240AF0

	arm_func_start MOD13_02215360
MOD13_02215360: ; 0x02215360
	stmdb sp!, {r4, r5, r6, lr}
	mov r5, r0
	mov r4, r1
	bl OS_DisableInterrupts
	ldr r1, _02215400 ; =0x02240AF8
	mov r6, r0
	ldr r1, [r1]
	ldrb r1, [r1, #0x50d]
	cmp r1, #0
	beq _02215398
	bl OS_RestoreInterrupts
	mov r0, #0
	ldmia sp!, {r4, r5, r6, lr}
	bx lr
_02215398:
	mov r0, r5
	mov r2, r4
	mov r1, #8
	bl MOD13_02215404
	cmp r0, #0
	bne _022153C4
	mov r0, r6
	bl OS_RestoreInterrupts
	mov r0, #0
	ldmia sp!, {r4, r5, r6, lr}
	bx lr
_022153C4:
	ldr r2, _02215400 ; =0x02240AF8
	mov r0, r6
	ldr r1, [r2]
	mov r3, #8
	strh r4, [r1, #0x10]
	ldr r1, [r2]
	add r1, r1, #0x500
	strh r5, [r1]
	ldr r1, [r2]
	add r1, r1, #0x500
	strh r3, [r1, #2]
	bl OS_RestoreInterrupts
	mov r0, #1
	ldmia sp!, {r4, r5, r6, lr}
	bx lr
	.align 2, 0
_02215400: .word 0x02240AF8

	arm_func_start MOD13_02215404
MOD13_02215404: ; 0x02215404
	ldr r3, _02215468 ; =0x000001FE
	cmp r0, r3
	bhi _02215418
	cmp r0, #0xe4
	bhs _02215420
_02215418:
	mov r0, #0
	bx lr
_02215420:
	cmp r1, #0x10
	bhi _02215430
	cmp r1, #8
	bhs _02215438
_02215430:
	mov r0, #0
	bx lr
_02215438:
	add r1, r1, #0x20
	mov r3, r1, lsl #2
	ldr r1, _0221546C ; =0x0000014A
	add r0, r0, #0x26
	add r1, r1, r0, lsl #2
	add r0, r3, #0x70
	mla r1, r2, r0, r1
	ldr r0, _02215470 ; =0x000015E0
	cmp r1, r0
	movlt r0, #1
	movge r0, #0
	bx lr
	.align 2, 0
_02215468: .word 0x000001FE
_0221546C: .word 0x0000014A
_02215470: .word 0x000015E0

	arm_func_start MOD13_02215474
MOD13_02215474: ; 0x02215474
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	ldr r4, _0221567C ; =0x02240AFC
	mov sb, r1
	ldr r1, [r4]
	mov r8, r2
	mov r7, r3
	cmp r1, #0
	beq _022154B4
	add r1, r1, #0x1300
	ldrh r1, [r1, #0x16]
	cmp r1, #0
	addne sp, sp, #4
	movne r0, #2
	ldmneia sp!, {r4, r5, r6, r7, r8, sb, lr}
	bxne lr
_022154B4:
	add r1, r0, #0x1f
	ldr r0, _02215680 ; =0x00001E1F
	bic r6, r1, #0x1f
	add r0, r6, r0
	cmp r7, #0x10000
	bic r5, r0, #0x1f
	bne _022154D8
	bl WM_GetNextTgid
	mov r7, r0
_022154D8:
	bl OS_DisableInterrupts
	ldr ip, _02215684 ; =0x02240AF8
	ldr r3, _0221567C ; =0x02240AFC
	mov r4, r0
	ldr r1, [sp, #0x20]
	ldr r0, _02215688 ; =0x02240AF0
	ldr r2, _0221568C ; =0x0000FFFF
	strh r1, [r0]
	ldr r0, _02215690 ; =0x0223F798
	ldr r1, _02215694 ; =0x0223F78C
	strh r2, [r0]
	mov r2, #5
	ldr r0, _02215698 ; =0x0223F790
	strh r2, [r1]
	mov r2, #0x28
	ldr r1, _0221569C ; =0x0223F794
	strh r2, [r0]
	ldr r0, _022156A0 ; =0x0223F7A0
	strh r2, [r1]
	mov r2, #1
	mov r1, r6
	str r2, [r0]
	mov r0, #0
	mov r2, #0x1e00
	str r6, [ip]
	str r5, [r3]
	bl MIi_CpuClear32
	mov r1, r5
	mov r0, #0
	mov r2, #0x1340
	bl MIi_CpuClear16
	ldrb r0, [sb, #1]
	add r1, r6, #0x530
	mov r2, #0
	cmp r0, #0
	ble _02215584
_02215568:
	add r0, sb, r2, lsl #1
	ldrh r0, [r0, #2]
	add r2, r2, #1
	strh r0, [r1], #2
	ldrb r0, [sb, #1]
	cmp r2, r0
	blt _02215568
_02215584:
	ldr r0, _022156A4 ; =0x00000538
	mov r3, #0
	add ip, r6, r0
	ldr r0, _022156A8 ; =0x0223F79C
_02215594:
	ldr r2, [r0]
	ldrh r1, [r2]
	cmp r1, #0
	beq _022155C0
	add r1, r2, #2
	str r1, [r0]
	ldrh r1, [r2]
	add r3, r3, #1
	cmp r3, #0x10
	strh r1, [ip], #2
	blt _02215594
_022155C0:
	mov r0, sb
	add r1, r5, #0x1300
	mov r2, #0x16
	bl MI_CpuCopy8
	ldrb r0, [sb, #1]
	mov r2, #0
	cmp r0, #0xa
	addlo r0, r5, r0, lsl #1
	addlo r0, r0, #0x1300
	movlo r1, #0
	strloh r1, [r0, #2]
	add r0, r6, #0x500
	mov r1, #0x100
	strh r1, [r0]
	mov r1, #8
	strh r1, [r0, #2]
	strh r2, [r0, #0x18]
	strh r2, [r0, #0x1a]
	mov r1, #1
	strh r1, [r0, #0x2c]
	add r0, r5, #0x400
	str r0, [r6, #0x504]
	strh r2, [r6, #0xe]
	strh r2, [r6, #0x12]
	strh r1, [r6, #0x16]
	strh r2, [r6, #0x14]
	str r8, [r6, #8]
	strh r7, [r6, #0xc]
	bl MOD13_022156AC
	add r0, r0, #0xc8
	strh r0, [r6, #0x18]
	mov r0, #0xf
	strh r0, [r6, #0x10]
	mov r3, #0
	strb r3, [r6, #0x50c]
	strb r3, [r6, #0x50d]
	add r1, r5, #0x1300
	mov r2, #1
	strh r2, [r1, #0x16]
	add r1, r5, #0x1000
	mov r0, r4
	str r3, [r1, #0x31c]
	bl OS_RestoreInterrupts
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, lr}
	bx lr
	.align 2, 0
_0221567C: .word 0x02240AFC
_02215680: .word 0x00001E1F
_02215684: .word 0x02240AF8
_02215688: .word 0x02240AF0
_0221568C: .word 0x0000FFFF
_02215690: .word 0x0223F798
_02215694: .word 0x0223F78C
_02215698: .word 0x0223F790
_0221569C: .word 0x0223F794
_022156A0: .word 0x0223F7A0
_022156A4: .word 0x00000538
_022156A8: .word 0x0223F79C

	arm_func_start MOD13_022156AC
MOD13_022156AC: ; 0x022156AC
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	add r0, sp, #0
	bl OS_GetMacAddress
	mov r2, #0
	add r1, sp, #0
	mov r3, r2
_022156C8:
	ldrb r0, [r1]
	add r2, r2, #1
	cmp r2, #6
	add r3, r3, r0
	add r1, r1, #1
	blt _022156C8
	ldr r1, _02215718 ; =0x027FFC3C
	mov r0, #7
	ldr r2, [r1]
	ldr r1, _0221571C ; =0xCCCCCCCD
	add r2, r3, r2
	mul r3, r2, r0
	umull r1, r0, r3, r1
	ldr r2, _02215720 ; =0x00000014
	mov r0, r0, lsr #4
	umull r0, r1, r2, r0
	sub r0, r3, r0
	add sp, sp, #0xc
	ldmia sp!, {lr}
	bx lr
	.align 2, 0
_02215718: .word 0x027FFC3C
_0221571C: .word 0xCCCCCCCD
_02215720: .word 0x00000014

	arm_func_start MOD13_02215724
MOD13_02215724: ; 0x02215724
	stmdb sp!, {r4, r5, r6, r7, r8, lr}
	sub sp, sp, #0x20
	mov r6, r0
	ldrh r0, [r6]
	ldr r1, _02215F98 ; =0x02240AF8
	cmp r0, #0x1d
	ldr r5, [r1]
	bgt _022157B0
	cmp r0, #0x1d
	bge _02215838
	cmp r0, #0x15
	addls pc, pc, r0, lsl #2
	b _02215F7C
_02215758: ; jump table
	b _022157BC ; case 0
	b _02215E4C ; case 1
	b _02215EB8 ; case 2
	b _02215F7C ; case 3
	b _02215F7C ; case 4
	b _02215F7C ; case 5
	b _02215F7C ; case 6
	b _02215F7C ; case 7
	b _02215F7C ; case 8
	b _02215F7C ; case 9
	b _022158DC ; case 10
	b _02215B64 ; case 11
	b _02215BBC ; case 12
	b _02215F7C ; case 13
	b _02215D54 ; case 14
	b _02215DDC ; case 15
	b _02215F7C ; case 16
	b _02215F7C ; case 17
	b _02215F7C ; case 18
	b _02215F7C ; case 19
	b _02215F7C ; case 20
	b _02215F20 ; case 21
_022157B0:
	cmp r0, #0x80
	beq _02215F50
	b _02215F7C
_022157BC:
	ldrh r0, [r6, #2]
	cmp r0, #0
	beq _022157E4
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0x100
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_022157E4:
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0x15
	blx r2
	ldr r0, _02215F9C ; =0x0223F794
	ldr r1, _02215FA0 ; =0x0223F798
	ldrh r3, [r0]
	ldr r2, _02215FA4 ; =0x0223F790
	ldr r0, _02215FA8 ; =0x0223F78C
	str r3, [sp]
	ldrh r3, [r0]
	ldrh r1, [r1]
	ldrh r2, [r2]
	ldr r0, _02215FAC ; =MOD13_02215724
	bl WM_SetLifeTime
	mov r1, r0
	mov r0, #0x1d
	bl MOD13_02214B08
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215838:
	ldrh r0, [r6, #2]
	cmp r0, #0
	beq _02215860
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0x100
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215860:
	ldr r0, _02215FB0 ; =0x02240B00
	add r2, r5, #0x440
	ldrh r1, [r0, #4]
	str r2, [r0]
	mov r2, #1
	cmp r1, #0
	moveq r1, #1
	streqh r1, [r0, #4]
	ldr r0, _02215FB0 ; =0x02240B00
	ldrh r1, [r0, #6]
	cmp r1, #0
	moveq r1, #0xc8
	streqh r1, [r0, #6]
	ldr r1, _02215FB0 ; =0x02240B00
	mov r0, #0xff
	strb r0, [r1, #8]
	strb r0, [r1, #9]
	strb r0, [r1, #0xa]
	strb r0, [r1, #0xb]
	strb r0, [r1, #0xc]
	strb r0, [r1, #0xd]
	str r2, [r5, #0x5e4]
	ldr r0, _02215FAC ; =MOD13_02215724
	str r2, [r5, #0x5e8]
	bl WM_StartScan
	mov r1, r0
	mov r0, #0xa
	bl MOD13_02214B08
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_022158DC:
	ldrh r0, [r6, #2]
	cmp r0, #0
	beq _02215904
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0x100
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215904:
	ldrh r0, [r6, #8]
	cmp r0, #3
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, r7, r8, lr}
	bxeq lr
	cmp r0, #4
	beq _02215AE0
	cmp r0, #5
	bne _02215B48
	add r0, r5, #0x500
	ldrh r0, [r0, #0xe0]
	add r3, r5, #0x600
	mov r4, #0
	cmp r0, #0
	ble _02215A18
	ldrb r1, [r6, #0xa]
	mov r2, r3
_02215948:
	ldrb r7, [r2, #0xca]
	cmp r1, r7
	bne _02215A08
	ldrb r8, [r6, #0xb]
	ldrb r7, [r2, #0xcb]
	cmp r8, r7
	bne _02215A08
	ldrb r8, [r6, #0xc]
	ldrb r7, [r2, #0xcc]
	cmp r8, r7
	bne _02215A08
	ldrb r8, [r6, #0xd]
	ldrb r7, [r2, #0xcd]
	cmp r8, r7
	bne _02215A08
	ldrb r8, [r6, #0xe]
	ldrb r7, [r2, #0xce]
	cmp r8, r7
	bne _02215A08
	ldrb r8, [r6, #0xf]
	ldrb r7, [r2, #0xcf]
	cmp r8, r7
	bne _02215A08
	mov r0, #0x180
	mul r7, r4, r0
	add r0, r3, r7
	ldrh r1, [r6, #0x36]
	add r8, r6, #0x38
	add lr, r0, #0xf8
	strh r1, [r0, #0xf6]
	mov ip, #8
_022159C4:
	ldmia r8!, {r0, r1, r2, r3}
	stmia lr!, {r0, r1, r2, r3}
	subs ip, ip, #1
	bne _022159C4
	add r0, r5, #0x600
	add r7, r0, r7
	mov r0, r7
	mov r1, #0xc0
	bl DC_InvalidateRange
	ldr r0, _02215FB4 ; =0x02240AF0
	mov r2, r7
	ldrh r0, [r0]
	add r1, r5, #0x440
	mov r3, #0xc0
	bl MI_DmaCopy16
	str r4, [r5, #0x5ec]
	b _02215A78
_02215A08:
	add r4, r4, #1
	cmp r4, r0
	add r2, r2, #0x180
	blt _02215948
_02215A18:
	cmp r4, #0x10
	bge _02215A78
	mov r0, #0x180
	mul r7, r4, r0
	add r1, r3, r7
	mov r0, r6
	add ip, r4, #1
	add r3, r5, #0x500
	add r1, r1, #0xc0
	mov r2, #0xb8
	strh ip, [r3, #0xe0]
	bl MIi_CpuCopy16
	add r0, r5, #0x600
	add r7, r0, r7
	mov r0, r7
	mov r1, #0xc0
	bl DC_InvalidateRange
	ldr r0, _02215FB4 ; =0x02240AF0
	mov r2, r7
	ldrh r0, [r0]
	add r1, r5, #0x440
	mov r3, #0xc0
	bl MI_DmaCopy16
	str r4, [r5, #0x5ec]
_02215A78:
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #4
	blx r2
	ldr r0, [r5, #0x5e4]
	cmp r0, #0
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, r7, r8, lr}
	bxeq lr
	ldr r0, [r5, #0x5e8]
	cmp r0, #0
	beq _02215ABC
	ldr r0, _02215FB0 ; =0x02240B00
	bl MOD13_022169EC
	cmp r0, #0
	bne _02215ABC
	bl MOD13_02214F58
_02215ABC:
	ldr r0, _02215FAC ; =MOD13_02215724
	ldr r1, _02215FB0 ; =0x02240B00
	bl WM_StartScan
	mov r1, r0
	mov r0, #0xa
	bl MOD13_02214B08
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215AE0:
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #5
	blx r2
	ldr r0, [r5, #0x5e4]
	cmp r0, #0
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, r7, r8, lr}
	bxeq lr
	ldr r0, [r5, #0x5e8]
	cmp r0, #0
	beq _02215B24
	ldr r0, _02215FB0 ; =0x02240B00
	bl MOD13_022169EC
	cmp r0, #0
	bne _02215B24
	bl MOD13_02214F58
_02215B24:
	ldr r0, _02215FAC ; =MOD13_02215724
	ldr r1, _02215FB0 ; =0x02240B00
	bl WM_StartScan
	mov r1, r0
	mov r0, #0xa
	bl MOD13_02214B08
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215B48:
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0x100
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215B64:
	ldrh r0, [r6, #2]
	cmp r0, #0
	beq _02215B8C
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0x100
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215B8C:
	mov r2, #0
	str r2, [sp]
	ldr r1, [r5, #0x520]
	ldr r0, _02215FAC ; =MOD13_02215724
	mov r3, #1
	bl WM_StartConnectEx
	mov r1, r0
	mov r0, #0xc
	bl MOD13_02214B08
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215BBC:
	ldrh r0, [r6, #2]
	cmp r0, #0
	beq _02215BF0
	add r0, r5, #0x500
	mov r1, #0
	strh r1, [r0, #0xe0]
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0xb
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215BF0:
	ldrh r0, [r6, #8]
	cmp r0, #9
	bgt _02215C20
	cmp r0, #6
	blt _02215D38
	cmp r0, #6
	beq _02215C34
	cmp r0, #7
	beq _02215C54
	cmp r0, #9
	beq _02215D0C
	b _02215D38
_02215C20:
	cmp r0, #0x1a
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, r7, r8, lr}
	bxeq lr
	b _02215D38
_02215C34:
	add r0, r5, #0x500
	mov r1, #0
	strh r1, [r0, #0x2a]
	mov r1, #1
	strh r1, [r0, #0x28]
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215C54:
	ldrh r2, [r6, #0xa]
	add r0, r5, #0x500
	mov r1, r6
	strh r2, [r0, #0xe2]
	ldr r2, [r5, #0x51c]
	mov r0, #6
	blx r2
	ldr r1, _02215FB8 ; =MOD13_02215FC0
	add r3, r5, #0x500
	mov r0, #1
	mov r2, #0
	strh r0, [r3, #0x2a]
	bl WM_SetPortCallback
	cmp r0, #0
	addne sp, sp, #0x20
	ldmneia sp!, {r4, r5, r6, r7, r8, lr}
	bxne lr
	add r0, r5, #0x500
	ldrh r0, [r0, #0x2c]
	add r1, r5, #0x500
	ldrh r2, [r1, #0x18]
	cmp r0, #0
	moveq r0, #1
	movne r0, #0
	mov r0, r0, lsl #0x10
	mov r0, r0, lsr #0x10
	str r2, [sp]
	str r0, [sp, #4]
	mov r0, #0
	str r0, [sp, #8]
	str r0, [sp, #0xc]
	str r0, [sp, #0x10]
	mov r0, #1
	str r0, [sp, #0x14]
	str r0, [sp, #0x18]
	ldrh r2, [r1, #0x1a]
	ldr r1, [r5, #0x504]
	ldr r0, _02215FAC ; =MOD13_02215724
	add r3, r5, #0x40
	bl WM_StartMPEx
	mov r1, r0
	mov r0, #0xe
	bl MOD13_02214B08
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215D0C:
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0xa
	blx r2
	add r0, r5, #0x500
	mov r1, #0
	strh r1, [r0, #0x2a]
	strh r1, [r0, #0x28]
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215D38:
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0x100
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215D54:
	ldrh r0, [r6, #4]
	cmp r0, #0xa
	beq _02215D84
	cmp r0, #0xc
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, r7, r8, lr}
	bxeq lr
	cmp r0, #0xd
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, r7, r8, lr}
	bxeq lr
	b _02215DC0
_02215D84:
	add r0, r5, #0x500
	mov r1, #1
	strh r1, [r0, #0x28]
	bl MOD13_02216984
	cmp r0, #0
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, r7, r8, lr}
	bxeq lr
	ldr r2, [r5, #0x51c]
	mov r0, #0x19
	mov r1, #0
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215DC0:
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0x100
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215DDC:
	mov r0, #0
	strb r0, [r5, #0x50c]
	ldrh r0, [r6, #2]
	cmp r0, #0
	bne _02215E04
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #8
	blx r2
	b _02215E30
_02215E04:
	cmp r0, #9
	bne _02215E20
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0x29
	blx r2
	b _02215E30
_02215E20:
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0x12
	blx r2
_02215E30:
	ldr r2, [r5, #0x51c]
	mov r0, #0x19
	mov r1, #0
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215E4C:
	ldrh r0, [r6, #2]
	cmp r0, #0
	beq _02215E80
	add r0, r5, #0x500
	mov r1, #0
	strh r1, [r0, #0x26]
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0x100
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215E80:
	add r0, r5, #0x500
	mov r2, #0
	strh r2, [r0, #0x2a]
	ldr r1, [r1]
	ldr r0, _02215FAC ; =MOD13_02215724
	add r1, r1, #0x500
	strh r2, [r1, #0x28]
	bl WM_End
	mov r1, r0
	mov r0, #2
	bl MOD13_02214B08
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215EB8:
	ldrh r0, [r6, #2]
	cmp r0, #0
	beq _02215EEC
	add r0, r5, #0x500
	mov r1, #0
	strh r1, [r0, #0x26]
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0x100
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215EEC:
	mov r2, #0
	ldr r0, _02215FBC ; =0x02240AFC
	strb r2, [r5, #0x50d]
	ldr r0, [r0]
	mov r1, r6
	add r0, r0, #0x1300
	strh r2, [r0, #0x16]
	ldr r2, [r5, #0x51c]
	mov r0, #0x11
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215F20:
	bl MOD13_02216984
	cmp r0, #0
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, r5, r6, r7, r8, lr}
	bxeq lr
	ldr r2, [r5, #0x51c]
	mov r0, #0x19
	mov r1, #0
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215F50:
	ldrh r0, [r6, #4]
	cmp r0, #0x16
	beq _02215F6C
	add sp, sp, #0x20
	cmp r0, #0x17
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215F6C:
	bl OS_Terminate
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
_02215F7C:
	ldr r2, [r5, #0x51c]
	mov r1, r6
	mov r0, #0x100
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, r5, r6, r7, r8, lr}
	bx lr
	.align 2, 0
_02215F98: .word 0x02240AF8
_02215F9C: .word 0x0223F794
_02215FA0: .word 0x0223F798
_02215FA4: .word 0x0223F790
_02215FA8: .word 0x0223F78C
_02215FAC: .word MOD13_02215724
_02215FB0: .word 0x02240B00
_02215FB4: .word 0x02240AF0
_02215FB8: .word MOD13_02215FC0
_02215FBC: .word 0x02240AFC

	arm_func_start MOD13_02215FC0
MOD13_02215FC0: ; 0x02215FC0
	stmdb sp!, {lr}
	sub sp, sp, #4
	mov r1, r0
	ldrh r0, [r1, #2]
	cmp r0, #0
	addne sp, sp, #4
	ldmneia sp!, {lr}
	bxne lr
	ldrh r0, [r1, #4]
	cmp r0, #0x15
	bgt _02216034
	cmp r0, #0x15
	bge _02216074
	cmp r0, #9
	addgt sp, sp, #4
	ldmgtia sp!, {lr}
	bxgt lr
	cmp r0, #7
	addlt sp, sp, #4
	ldmltia sp!, {lr}
	bxlt lr
	cmp r0, #7
	addeq sp, sp, #4
	ldmeqia sp!, {lr}
	bxeq lr
	add sp, sp, #4
	cmp r0, #9
	ldmia sp!, {lr}
	bx lr
_02216034:
	cmp r0, #0x1a
	addgt sp, sp, #4
	ldmgtia sp!, {lr}
	bxgt lr
	cmp r0, #0x19
	addlt sp, sp, #4
	ldmltia sp!, {lr}
	bxlt lr
	cmp r0, #0x19
	addeq sp, sp, #4
	ldmeqia sp!, {lr}
	bxeq lr
	add sp, sp, #4
	cmp r0, #0x1a
	ldmia sp!, {lr}
	bx lr
_02216074:
	ldr r2, _02216094 ; =0x02240AF8
	mov r0, #9
	ldr r2, [r2]
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #4
	ldmia sp!, {lr}
	bx lr
	.align 2, 0
_02216094: .word 0x02240AF8

	arm_func_start MOD13_02216098
MOD13_02216098: ; 0x02216098
	stmdb sp!, {r4, lr}
	sub sp, sp, #0x20
	mov r4, r0
	ldrh r0, [r4]
	cmp r0, #0x19
	bgt _02216104
	cmp r0, #0x19
	bge _022161F8
	cmp r0, #0xf
	addls pc, pc, r0, lsl #2
	b _022168D8
_022160C4: ; jump table
	b _02216124 ; case 0
	b _02216694 ; case 1
	b _02216744 ; case 2
	b _022168D8 ; case 3
	b _022168D8 ; case 4
	b _022168D8 ; case 5
	b _022168D8 ; case 6
	b _022161BC ; case 7
	b _02216250 ; case 8
	b _022168D8 ; case 9
	b _022168D8 ; case 10
	b _022168D8 ; case 11
	b _022168D8 ; case 12
	b _022167C4 ; case 13
	b _022164E0 ; case 14
	b _02216584 ; case 15
_02216104:
	cmp r0, #0x1d
	bgt _02216118
	cmp r0, #0x1d
	beq _02216164
	b _022168D8
_02216118:
	cmp r0, #0x80
	beq _02216804
	b _022168D8
_02216124:
	ldrh r0, [r4, #2]
	cmp r0, #0
	beq _02216154
	ldr r0, _022168FC ; =0x02240AF8
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0x100
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216154:
	bl MOD13_02216910
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216164:
	ldrh r0, [r4, #2]
	cmp r0, #0
	beq _02216194
	ldr r0, _022168FC ; =0x02240AF8
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0x100
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216194:
	ldr r1, _022168FC ; =0x02240AF8
	ldr r0, _02216900 ; =MOD13_02216098
	ldr r1, [r1]
	bl WM_SetParentParameter
	mov r1, r0
	mov r0, #7
	bl MOD13_02214B08
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_022161BC:
	ldr r0, _022168FC ; =0x02240AF8
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0x15
	ldr r2, [r2, #0x51c]
	blx r2
	ldr r0, _02216900 ; =MOD13_02216098
	mov r1, #1
	bl WM_SetBeaconIndication
	mov r1, r0
	mov r0, #0x19
	bl MOD13_02214B08
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_022161F8:
	ldrh r0, [r4, #2]
	cmp r0, #0
	beq _02216228
	ldr r0, _022168FC ; =0x02240AF8
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0x100
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216228:
	ldr r1, _02216904 ; =0x0223F7A0
	ldr r0, _02216900 ; =MOD13_02216098
	ldr r1, [r1]
	bl FUN_020D9564
	mov r1, r0
	mov r0, #8
	bl MOD13_02214B08
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216250:
	ldrh r0, [r4, #2]
	cmp r0, #0
	beq _02216280
	ldr r0, _022168FC ; =0x02240AF8
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0x100
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216280:
	ldrh r0, [r4, #8]
	cmp r0, #7
	bgt _022162B8
	cmp r0, #7
	bge _0221630C
	cmp r0, #2
	bgt _022164BC
	cmp r0, #0
	blt _022164BC
	cmp r0, #0
	beq _022162E0
	cmp r0, #2
	beq _02216480
	b _022164BC
_022162B8:
	cmp r0, #9
	bgt _022162CC
	cmp r0, #9
	beq _02216440
	b _022164BC
_022162CC:
	cmp r0, #0x1a
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, lr}
	bxeq lr
	b _022164BC
_022162E0:
	ldr r1, _022168FC ; =0x02240AF8
	mov r2, #0
	ldr r0, [r1]
	add sp, sp, #0x20
	add r0, r0, #0x500
	strh r2, [r0, #0x2a]
	ldr r0, [r1]
	add r0, r0, #0x500
	strh r2, [r0, #0x28]
	ldmia sp!, {r4, lr}
	bx lr
_0221630C:
	ldr r2, _022168FC ; =0x02240AF8
	ldr r0, [r2]
	add r0, r0, #0x500
	ldrh r1, [r0, #0x26]
	cmp r1, #1
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, lr}
	bxeq lr
	ldrh lr, [r0, #0x2a]
	ldrh r3, [r4, #0x10]
	mov ip, #1
	mov r1, r4
	orr r3, lr, ip, lsl r3
	strh r3, [r0, #0x2a]
	ldr r2, [r2]
	mov r0, #0
	ldr r2, [r2, #0x51c]
	blx r2
	ldr r1, _022168FC ; =0x02240AF8
	ldr r0, [r1]
	add r0, r0, #0x500
	ldrh r0, [r0, #0x28]
	cmp r0, #0
	bne _02216408
	ldr r0, _02216908 ; =0x02240AFC
	ldr r0, [r0]
	add r0, r0, #0x1000
	ldr r2, [r0, #0x31c]
	cmp r2, #0
	bne _02216408
	mov r2, #1
	str r2, [r0, #0x31c]
	ldr r0, [r1]
	ldr r1, _022168FC ; =0x02240AF8
	add r0, r0, #0x500
	ldrh r0, [r0, #0x2c]
	ldr ip, [r1]
	mov r1, #1
	cmp r0, #0
	movne r2, #0
	mov r0, r2, lsl #0x10
	mov r3, r0, lsr #0x10
	add r0, ip, #0x500
	ldrh r4, [r0, #0x18]
	mov r2, #0
	str r4, [sp]
	str r3, [sp, #4]
	str r2, [sp, #8]
	str r2, [sp, #0xc]
	str r2, [sp, #0x10]
	str r1, [sp, #0x14]
	str r1, [sp, #0x18]
	ldrh r2, [r0, #0x1a]
	ldr r1, [ip, #0x504]
	ldr r0, _02216900 ; =MOD13_02216098
	add r3, ip, #0x40
	bl WM_StartMPEx
	mov r1, r0
	mov r0, #0xe
	bl MOD13_02214B08
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216408:
	bl MOD13_02216984
	cmp r0, #0
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, lr}
	bxeq lr
	ldr r1, _022168FC ; =0x02240AF8
	mov r0, #0x19
	ldr r2, [r1]
	mov r1, #0
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216440:
	ldr r2, _022168FC ; =0x02240AF8
	ldrh r3, [r4, #0x10]
	ldr r1, [r2]
	mov r0, #1
	add r1, r1, #0x500
	ldrh ip, [r1, #0x2a]
	mvn r3, r0, lsl r3
	and r3, ip, r3
	strh r3, [r1, #0x2a]
	ldr r2, [r2]
	mov r1, r4
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216480:
	ldr r0, _022168FC ; =0x02240AF8
	ldr r1, [r0]
	add r0, r1, #0x500
	ldrh r0, [r0, #0x26]
	cmp r0, #1
	addeq sp, sp, #0x20
	ldmeqia sp!, {r4, lr}
	bxeq lr
	ldr r2, [r1, #0x51c]
	mov r1, r4
	mov r0, #0x1c
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_022164BC:
	ldr r0, _022168FC ; =0x02240AF8
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0x100
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_022164E0:
	ldr r0, _02216908 ; =0x02240AFC
	mov r1, #0
	ldr r0, [r0]
	add r0, r0, #0x1000
	str r1, [r0, #0x31c]
	ldrh r0, [r4, #4]
	cmp r0, #0xa
	beq _0221650C
	cmp r0, #0xb
	beq _0221653C
	b _02216560
_0221650C:
	ldr r3, _022168FC ; =0x02240AF8
	mov r4, #1
	ldr r2, [r3]
	mov r0, #0x19
	add r2, r2, #0x500
	strh r4, [r2, #0x28]
	ldr r2, [r3]
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_0221653C:
	ldr r0, _022168FC ; =0x02240AF8
	ldr r1, [r4, #8]
	ldr r2, [r0]
	mov r0, #3
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216560:
	ldr r0, _022168FC ; =0x02240AF8
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0x100
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216584:
	ldr r0, _02216908 ; =0x02240AFC
	ldr r1, [r0]
	add r0, r1, #0x7000
	ldr r0, [r0, #0x4c8]
	cmp r0, #0
	beq _022165E0
	mov r3, #0
	mov r2, r3
_022165A4:
	add r0, r1, r2, lsl #2
	add r0, r0, #0x1000
	ldr r0, [r0, #0x4e8]
	cmp r0, #0
	beq _022165C4
	add r3, r3, #1
	cmp r3, #2
	bhs _022165D0
_022165C4:
	add r2, r2, #1
	cmp r2, #0xf
	blo _022165A4
_022165D0:
	cmp r3, #1
	bne _022165E0
	ldr r0, _0221690C ; =0x000032C8
	bl OS_SpinWait
_022165E0:
	ldr r0, _022168FC ; =0x02240AF8
	mov r2, #0
	ldr r1, [r0]
	strb r2, [r1, #0x50c]
	ldrh r1, [r4, #2]
	cmp r1, #0
	bne _02216634
	ldr r0, [r0]
	mov r1, r4
	ldr r2, [r0, #0x51c]
	mov r0, #2
	blx r2
	ldr r1, _022168FC ; =0x02240AF8
	mov r0, #0x19
	ldr r2, [r1]
	mov r1, #0
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216634:
	cmp r1, #0xa
	bne _0221665C
	ldr r0, [r0]
	mov r1, r4
	ldr r2, [r0, #0x51c]
	mov r0, #0x2a
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_0221665C:
	ldr r0, [r0]
	mov r1, r4
	ldr r2, [r0, #0x51c]
	mov r0, #0x13
	blx r2
	ldr r1, _022168FC ; =0x02240AF8
	mov r0, #0x19
	ldr r2, [r1]
	mov r1, #0
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216694:
	ldr r0, _02216908 ; =0x02240AFC
	ldr r0, [r0]
	add r0, r0, #0x1000
	ldr r0, [r0, #0x320]
	cmp r0, #0
	bne _0221672C
	ldrh r0, [r4, #2]
	cmp r0, #0
	beq _022166EC
	ldr r2, _022168FC ; =0x02240AF8
	mov r3, #0
	ldr r0, [r2]
	mov r1, r4
	add r0, r0, #0x500
	strh r3, [r0, #0x26]
	ldr r2, [r2]
	mov r0, #0x100
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_022166EC:
	ldr r2, _022168FC ; =0x02240AF8
	mov r3, #0
	ldr r1, [r2]
	ldr r0, _02216900 ; =MOD13_02216098
	add r1, r1, #0x500
	strh r3, [r1, #0x2a]
	ldr r1, [r2]
	add r1, r1, #0x500
	strh r3, [r1, #0x28]
	bl WM_End
	mov r1, r0
	mov r0, #2
	bl MOD13_02214B08
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_0221672C:
	mov r1, #0
	mov r2, r1
	mov r0, #1
	bl WM_SetPortCallback
	mov r0, #0
	bl WM_SetIndCallback
_02216744:
	ldrh r0, [r4, #2]
	cmp r0, #0
	beq _02216784
	ldr r2, _022168FC ; =0x02240AF8
	mov r3, #0
	ldr r0, [r2]
	mov r1, r4
	add r0, r0, #0x500
	strh r3, [r0, #0x26]
	ldr r2, [r2]
	mov r0, #0x100
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216784:
	ldr r2, _022168FC ; =0x02240AF8
	mov r3, #0
	ldr r1, [r2]
	ldr r0, _02216908 ; =0x02240AFC
	strb r3, [r1, #0x50d]
	ldr r0, [r0]
	mov r1, r4
	add r0, r0, #0x1300
	strh r3, [r0, #0x16]
	ldr r2, [r2]
	mov r0, #0x11
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_022167C4:
	ldrh r0, [r4, #2]
	cmp r0, #0
	addne sp, sp, #0x20
	ldmneia sp!, {r4, lr}
	bxne lr
	ldr r0, _022168FC ; =0x02240AF8
	ldrh r1, [r4, #0xa]
	ldr r0, [r0]
	add sp, sp, #0x20
	add r0, r0, #0x500
	ldrh r2, [r0, #0x2a]
	mvn r1, r1
	and r1, r2, r1
	strh r1, [r0, #0x2a]
	ldmia sp!, {r4, lr}
	bx lr
_02216804:
	ldrh r0, [r4, #4]
	sub r0, r0, #0x10
	cmp r0, #7
	addls pc, pc, r0, lsl #2
	b _022168F0
_02216818: ; jump table
	b _02216838 ; case 0
	b _0221685C ; case 1
	b _02216880 ; case 2
	b _022168A4 ; case 3
	b _022168F0 ; case 4
	b _022168F0 ; case 5
	b _022168C8 ; case 6
	b _022168F0 ; case 7
_02216838:
	ldr r0, _022168FC ; =0x02240AF8
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0x1d
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_0221685C:
	ldr r0, _022168FC ; =0x02240AF8
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0x1f
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_02216880:
	ldr r0, _022168FC ; =0x02240AF8
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0x20
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_022168A4:
	ldr r0, _022168FC ; =0x02240AF8
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0x21
	ldr r2, [r2, #0x51c]
	blx r2
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_022168C8:
	bl OS_Terminate
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
_022168D8:
	ldr r0, _022168FC ; =0x02240AF8
	mov r1, r4
	ldr r2, [r0]
	mov r0, #0x100
	ldr r2, [r2, #0x51c]
	blx r2
_022168F0:
	add sp, sp, #0x20
	ldmia sp!, {r4, lr}
	bx lr
	.align 2, 0
_022168FC: .word 0x02240AF8
_02216900: .word MOD13_02216098
_02216904: .word 0x0223F7A0
_02216908: .word 0x02240AFC
_0221690C: .word 0x000032C8

	arm_func_start MOD13_02216910
MOD13_02216910: ; 0x02216910
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _02216970 ; =MOD13_02216098
	bl WM_SetIndCallback
	mov r1, r0
	mov r0, #0x80
	bl MOD13_02214B08
	ldr r0, _02216974 ; =0x0223F794
	ldr r1, _02216978 ; =0x0223F798
	ldrh r3, [r0]
	ldr r2, _0221697C ; =0x0223F790
	ldr r0, _02216980 ; =0x0223F78C
	str r3, [sp]
	ldrh r1, [r1]
	ldrh r2, [r2]
	ldrh r3, [r0]
	ldr r0, _02216970 ; =MOD13_02216098
	bl WM_SetLifeTime
	mov r1, r0
	mov r0, #0x1d
	bl MOD13_02214B08
	add sp, sp, #4
	ldmia sp!, {lr}
	bx lr
	.align 2, 0
_02216970: .word MOD13_02216098
_02216974: .word 0x0223F794
_02216978: .word 0x0223F798
_0221697C: .word 0x0223F790
_02216980: .word 0x0223F78C

	arm_func_start MOD13_02216984
MOD13_02216984: ; 0x02216984
	ldr r1, _022169E8 ; =0x02240AF8
	mov r0, #0
	ldr r2, [r1]
	mov ip, r0
	add r1, r2, #0x500
	ldrh r1, [r1, #0x28]
	mov r3, r0
	cmp r1, #1
	bne _022169B4
	ldrb r1, [r2, #0x50c]
	cmp r1, #0
	moveq r3, #1
_022169B4:
	cmp r3, #0
	beq _022169CC
	add r1, r2, #0x500
	ldrh r1, [r1, #0x26]
	cmp r1, #0
	moveq ip, #1
_022169CC:
	cmp ip, #0
	bxeq lr
	add r1, r2, #0x500
	ldrh r1, [r1, #0x2a]
	cmp r1, #0
	movne r0, #1
	bx lr
	.align 2, 0
_022169E8: .word 0x02240AF8

	arm_func_start MOD13_022169EC
MOD13_022169EC: ; 0x022169EC
	stmdb sp!, {r4, lr}
	mov r4, r0
	bl WM_GetAllowedChannel
	cmp r0, #0
	moveq r0, #0
	ldmeqia sp!, {r4, lr}
	bxeq lr
	ldrh r3, [r4, #4]
	mov ip, #0
	mov lr, r3
	mov r2, #1
_02216A18:
	sub r1, lr, #1
	mov r1, r2, lsl r1
	ands r1, r0, r1
	beq _02216A34
	cmp r3, lr
	strneh lr, [r4, #4]
	bne _02216A5C
_02216A34:
	add r1, ip, #1
	mov r1, r1, lsl #0x10
	cmp lr, #0x10
	mov ip, r1, lsr #0x10
	moveq r1, r2
	addne r1, lr, #1
	mov r1, r1, lsl #0x10
	cmp ip, #0x10
	mov lr, r1, lsr #0x10
	blo _02216A18
_02216A5C:
	mov r0, #1
	ldmia sp!, {r4, lr}
	bx lr

	arm_func_start MOD13_02216A68
MOD13_02216A68: ; 0x02216A68
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	mov sb, r0
	mov r8, r1
	mov r7, r2
	mov r6, r3
	mov r5, #0
	bl OS_DisableInterrupts
	add r2, sb, #0x30
	add r1, sb, #0x70
	mov r4, r0
	cmp r2, r1
	bhs _02216AF4
_02216A9C:
	ldr r0, [r2, #0xc]
	cmp r0, #2
	blo _02216AE8
	ldr r0, [r2]
	subs r0, r8, r0
	bmi _02216AE8
	ldr r3, [r2, #4]
	add ip, r0, r6
	cmp ip, r3
	bhi _02216AE8
	ldr r3, [r2, #8]
	mov r1, r7
	mov r2, r6
	add r0, r3, r0
	bl MI_CpuCopy8
	mov r0, #0
	str r0, [sb]
	mov r5, #1
	b _02216AF4
_02216AE8:
	add r2, r2, #0x10
	cmp r2, r1
	blo _02216A9C
_02216AF4:
	mov r0, r4
	bl OS_RestoreInterrupts
	mov r0, r5
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, lr}
	bx lr

	arm_func_start MOD13_02216B0C
MOD13_02216B0C: ; 0x02216B0C
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	mov r4, r0
	mov sb, r1
	mov r8, r2
	mov r7, r3
	bl OS_DisableInterrupts
	mov r6, r0
	add r5, r4, #0x30
	add r4, r4, #0x70
_02216B34:
	cmp r5, r4
	blo _02216B40
	bl OS_Terminate
_02216B40:
	ldr r0, [r5, #0xc]
	cmp r0, #0
	bne _02216B64
	str sb, [r5]
	str r8, [r5, #4]
	ldr r0, [sp, #0x20]
	str r7, [r5, #8]
	str r0, [r5, #0xc]
	b _02216B6C
_02216B64:
	add r5, r5, #0x10
	b _02216B34
_02216B6C:
	mov r0, r6
	bl OS_RestoreInterrupts
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, lr}
	bx lr

	arm_func_start MOD13_02216B80
MOD13_02216B80: ; 0x02216B80
	ldr ip, _02216B90 ; =0x020CE34C
	mov r1, #0
	mov r2, #0x70
	bx ip
	.align 2, 0
_02216B90: .word 0x020CE34C

	arm_func_start MOD13_02216B94
MOD13_02216B94: ; 0x02216B94
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	mov r5, r0
	bl OS_DisableInterrupts
	mov r4, r0
	bl MOD13_02216DA4
	cmp r0, #0
	beq _02216BD0
	ldr r0, _02216BE4 ; =0x02240B20
	mov r1, #0
	ldr r0, [r0]
	mov r2, r5
	mov r3, r1
	add r0, r0, #0xc4
	bl MOD13_02216BE8
_02216BD0:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #4
	ldmia sp!, {r4, r5, lr}
	bx lr
	.align 2, 0
_02216BE4: .word 0x02240B20

	arm_func_start MOD13_02216BE8
MOD13_02216BE8: ; 0x02216BE8
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	ldr r4, _02216D74 ; =0x02240B20
	mov sb, r0
	mov r8, r1
	mov r7, r2
	mov r6, r3
	ldr r5, [r4]
	bl MOD13_02216DA4
	cmp r0, #0
	bne _02216C18
	bl OS_Terminate
_02216C18:
	ldr r0, [sb, #4]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	beq _02216C2C
	bl OS_Terminate
_02216C2C:
	cmp r6, #0x1f
	bls _02216C78
	mov r0, r5
	bl OS_GetThreadPriority
	cmp r6, #0x20
	bne _02216C54
	cmp r0, #0
	subne r6, r0, #1
	moveq r6, #0
	b _02216C78
_02216C54:
	cmp r6, #0x21
	bne _02216C6C
	cmp r0, #0x1f
	addlo r6, r0, #1
	movhs r6, #0x1f
	b _02216C78
_02216C6C:
	cmp r6, #0x22
	moveq r6, r0
	movne r6, #0x1f
_02216C78:
	bl OS_DisableInterrupts
	ldr r2, [sb, #4]
	bic r1, r6, #0x80000000
	bic r2, r2, #1
	orr r2, r2, #1
	str r2, [sb, #4]
	ldr r2, [sb, #4]
	mov r4, r0
	and r0, r2, #1
	orr r0, r0, r1, lsl #1
	str r0, [sb, #4]
	str r8, [sb, #8]
	str r7, [sb, #0xc]
	ldr r0, [r5, #0xc0]
	cmp r0, #0
	bne _02216CDC
	add r0, r5, #0xc4
	cmp sb, r0
	ldreq r0, _02216D74 ; =0x02240B20
	moveq r1, #0
	streq r1, [r0]
	mov r0, r5
	str sb, [r5, #0xc0]
	bl OS_WakeupThreadDirect
	b _02216D60
_02216CDC:
	add r0, r5, #0xc4
	cmp sb, r0
	ldr r2, [r5, #0xc0]
	bne _02216D1C
	ldr r0, [r2]
	cmp r0, #0
	beq _02216D08
_02216CF8:
	mov r2, r0
	ldr r0, [r0]
	cmp r0, #0
	bne _02216CF8
_02216D08:
	ldr r0, _02216D74 ; =0x02240B20
	str sb, [r2]
	mov r1, #0
	str r1, [r0]
	b _02216D60
_02216D1C:
	ldr r0, [r2, #4]
	mov r0, r0, lsr #1
	cmp r0, r6
	bls _02216D3C
	str sb, [r5, #0xc0]
	str r2, [sb]
	b _02216D60
_02216D38:
	mov r2, r1
_02216D3C:
	ldr r1, [r2]
	cmp r1, #0
	beq _02216D58
	ldr r0, [r1, #4]
	mov r0, r0, lsr #1
	cmp r0, r6
	bls _02216D38
_02216D58:
	str r1, [sb]
	str sb, [r2]
_02216D60:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, lr}
	bx lr
	.align 2, 0
_02216D74: .word 0x02240B20

	arm_func_start MOD13_02216D78
MOD13_02216D78: ; 0x02216D78
	ldr r0, [r0, #4]
	mov r0, r0, lsl #0x1f
	movs r0, r0, lsr #0x1f
	movne r0, #1
	moveq r0, #0
	bx lr

	arm_func_start MOD13_02216D90
MOD13_02216D90: ; 0x02216D90
	ldr ip, _02216DA0 ; =0x020CE34C
	mov r1, #0
	mov r2, #0x20
	bx ip
	.align 2, 0
_02216DA0: .word 0x020CE34C

	arm_func_start MOD13_02216DA4
MOD13_02216DA4: ; 0x02216DA4
	ldr r0, _02216DBC ; =0x02240B20
	ldr r0, [r0]
	cmp r0, #0
	movne r0, #1
	moveq r0, #0
	bx lr
	.align 2, 0
_02216DBC: .word 0x02240B20

	arm_func_start MOD13_02216DC0
MOD13_02216DC0: ; 0x02216DC0
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #8
	mov r5, r0
	mov r6, r1
	bl OS_DisableInterrupts
	ldr r1, _02216E40 ; =0x02240B20
	mov r4, r0
	ldr r0, [r1]
	cmp r0, #0
	bne _02216E2C
	add r0, r5, #0xc4
	str r5, [r1]
	bl MOD13_02216D90
	sub r0, r6, #0xe4
	mov lr, #0
	str lr, [r5, #0xc0]
	bic ip, r0, #3
	add r3, r5, #0xe4
	str ip, [sp]
	ldr r1, _02216E44 ; =MOD13_02216E48
	mov r0, r5
	mov r2, r5
	add r3, r3, ip
	str lr, [sp, #4]
	bl OS_CreateThread
	mov r0, r5
	bl OS_WakeupThreadDirect
_02216E2C:
	mov r0, r4
	bl OS_RestoreInterrupts
	add sp, sp, #8
	ldmia sp!, {r4, r5, r6, lr}
	bx lr
	.align 2, 0
_02216E40: .word 0x02240B20
_02216E44: .word MOD13_02216E48

	arm_func_start MOD13_02216E48
MOD13_02216E48: ; 0x02216E48
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #4
	mov r8, r0
	add sb, r8, #0xc4
	mov r4, #0
_02216E5C:
	bl OS_DisableInterrupts
	ldr r1, [r8, #0xc0]
	mov r5, r0
	cmp r1, #0
	bne _02216E90
_02216E70:
	mov r0, r8
	mov r1, r4
	bl OS_SetThreadPriority
	mov r0, r4
	bl OS_SleepThread
	ldr r0, [r8, #0xc0]
	cmp r0, #0
	beq _02216E70
_02216E90:
	ldr r7, [r8, #0xc0]
	ldr r1, [r8, #0xc0]
	mov r0, r8
	ldr r1, [r1]
	str r1, [r8, #0xc0]
	ldr r1, [r7, #4]
	mov r1, r1, lsr #1
	bl OS_SetThreadPriority
	mov r0, r5
	bl OS_RestoreInterrupts
	ldr r1, [r7, #8]
	cmp r1, #0
	beq _02216ECC
	mov r0, r7
	blx r1
_02216ECC:
	bl OS_DisableInterrupts
	mov r6, r0
	mov r0, r8
	ldr r5, [r7, #0xc]
	bl OS_GetThreadPriority
	ldr r1, [r8, #0xc0]
	cmp r1, #0
	moveq r1, r4
	beq _02216F0C
	ldr r1, [r8, #0xc0]
	ldr r1, [r1, #4]
	cmp r0, r1, lsr #1
	ldrlo r1, [r8, #0xc0]
	ldrlo r1, [r1, #4]
	movlo r1, r1, lsr #1
	movhs r1, r0
_02216F0C:
	cmp r1, r0
	beq _02216F1C
	mov r0, r8
	bl OS_SetThreadPriority
_02216F1C:
	str r4, [r7]
	ldr r0, [r7, #4]
	cmp r5, #0
	bic r0, r0, #1
	str r0, [r7, #4]
	beq _02216F3C
	mov r0, r7
	blx r5
_02216F3C:
	cmp r7, sb
	beq _02216F50
	mov r0, r6
	bl OS_RestoreInterrupts
	b _02216E5C
_02216F50:
	bl OS_ExitThread
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, lr}
	bx lr

	arm_func_start MOD13_02216F60
MOD13_02216F60: ; 0x02216F60
	ldr r1, _02216FB8 ; =0x02240B28
	mov ip, #0
	ldr r2, [r1, #4]
	cmp r2, #0
	ble _02216FB0
	ldr r1, _02216FBC ; =0x02240B24
	sub r0, r0, #1
	ldr r1, [r1]
	add r0, r1, r0, lsl #2
	ldr r3, [r0, #0x1e0]
	mov r1, #1
_02216F8C:
	mov r0, r1, lsl ip
	ands r0, r0, r3
	moveq r0, #0
	bxeq lr
	add r0, ip, #1
	mov r0, r0, lsl #0x10
	mov ip, r0, lsr #0x10
	cmp ip, r2
	blt _02216F8C
_02216FB0:
	mov r0, #1
	bx lr
	.align 2, 0
_02216FB8: .word 0x02240B28
_02216FBC: .word 0x02240B24

	arm_func_start MOD13_02216FC0
MOD13_02216FC0: ; 0x02216FC0
	stmdb sp!, {r4, r5, r6, r7, lr}
	sub sp, sp, #4
	ldr r2, _02217068 ; =0x02240B24
	mov r7, r1
	ldr r3, [r2]
	cmp r3, #0
	addeq sp, sp, #4
	moveq r0, #0
	ldmeqia sp!, {r4, r5, r6, r7, lr}
	bxeq lr
	ldr r1, _0221706C ; =0x02240B28
	ldrb r4, [r0, #2]
	ldr r2, [r1, #4]
	cmp r4, r2
	addgt sp, sp, #4
	movgt r0, #0
	ldmgtia sp!, {r4, r5, r6, r7, lr}
	bxgt lr
	sub r6, r7, #1
	ldr r2, [r1]
	add r1, r3, r6, lsl #5
	mla r1, r4, r2, r1
	add r0, r0, #3
	mov r5, r6, lsl #5
	bl MI_CpuCopy8
	ldr r0, _02217068 ; =0x02240B24
	mov r1, #1
	ldr r2, [r0]
	mov r0, r7
	add r3, r2, #0x1e0
	ldr r2, [r3, r6, lsl #2]
	orr r1, r2, r1, lsl r4
	str r1, [r3, r6, lsl #2]
	bl MOD13_02216F60
	cmp r0, #0
	ldrne r0, _02217068 ; =0x02240B24
	ldrne r0, [r0]
	addne r0, r0, r5
	moveq r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, r6, r7, lr}
	bx lr
	.align 2, 0
_02217068: .word 0x02240B24
_0221706C: .word 0x02240B28

	arm_func_start MOD13_02217070
MOD13_02217070: ; 0x02217070
	stmdb sp!, {r4, r5, r6, lr}
	mov r6, r0
	ldrb r0, [r6]
	mov r5, r1
	mov r4, r2
	strb r0, [r5]
	ldrb r0, [r5]
	cmp r0, #7
	beq _022170A8
	cmp r0, #8
	beq _02217114
	cmp r0, #9
	beq _02217140
	b _0221718C
_022170A8:
	mov r0, r4
	bl MOD13_02216F60
	cmp r0, #0
	ldrne r0, _022171A4 ; =0x02240B24
	subne r1, r4, #1
	ldrne r0, [r0]
	addne r0, r0, r1, lsl #5
	ldmneia sp!, {r4, r5, r6, lr}
	bxne lr
	ldrb r1, [r6, #1]
	ldr r0, _022171A8 ; =0x02240B28
	strb r1, [r5, #2]
	ldrb r2, [r5, #2]
	ldr r1, [r0, #4]
	cmp r2, r1
	movgt r0, #0
	ldmgtia sp!, {r4, r5, r6, lr}
	bxgt lr
	ldr r2, [r0]
	add r0, r6, #2
	add r1, r5, #3
	bl MI_CpuCopy8
	mov r0, r5
	mov r1, r4
	bl MOD13_02216FC0
	mov r4, r0
	b _02217198
_02217114:
	ldrb r0, [r6, #1]
	add r4, r6, #3
	and r0, r0, #0xff
	strh r0, [r5, #2]
	ldrb r0, [r6, #2]
	ldrh r1, [r5, #2]
	mov r0, r0, lsl #8
	and r0, r0, #0xff00
	orr r0, r1, r0
	strh r0, [r5, #2]
	b _02217198
_02217140:
	ldrb r0, [r6, #1]
	add r4, r6, #3
	ldr r1, _022171A8 ; =0x02240B28
	and r0, r0, #0xff
	strh r0, [r5, #2]
	ldrb r2, [r6, #2]
	ldrh r3, [r5, #2]
	mov r0, r4
	mov r2, r2, lsl #8
	and r2, r2, #0xff00
	orr r2, r3, r2
	strh r2, [r5, #2]
	ldr r2, [r1]
	add r1, r5, #4
	bl MI_CpuCopy8
	ldr r0, _022171A8 ; =0x02240B28
	ldr r0, [r0]
	add r4, r4, r0
	b _02217198
_0221718C:
	mov r0, #0
	ldmia sp!, {r4, r5, r6, lr}
	bx lr
_02217198:
	mov r0, r4
	ldmia sp!, {r4, r5, r6, lr}
	bx lr
	.align 2, 0
_022171A4: .word 0x02240B24
_022171A8: .word 0x02240B28

	arm_func_start MOD13_022171AC
MOD13_022171AC: ; 0x022171AC
	ldrb r3, [r0]
	mov r2, r1
	add r2, r2, #1
	strb r3, [r1]
	ldrb r1, [r0]
	cmp r1, #6
	addls pc, pc, r1, lsl #2
	b _02217224
_022171CC: ; jump table
	b _02217224 ; case 0
	b _0221722C ; case 1
	b _0221722C ; case 2
	b _0221722C ; case 3
	b _022171E8 ; case 4
	b _0221722C ; case 5
	b _0221722C ; case 6
_022171E8:
	ldrh r3, [r0, #2]
	add r1, r2, #3
	strb r3, [r2]
	ldrh r3, [r0, #2]
	and r3, r3, #0xff00
	mov r3, r3, asr #8
	strb r3, [r2, #1]
	ldrh r3, [r0, #4]
	strb r3, [r2, #2]
	ldrh r0, [r0, #4]
	add r2, r2, #4
	and r0, r0, #0xff00
	mov r0, r0, asr #8
	strb r0, [r1]
	b _0221722C
_02217224:
	mov r0, #0
	bx lr
_0221722C:
	mov r0, r2
	bx lr

	arm_func_start MOD13_02217234
MOD13_02217234: ; 0x02217234
	stmdb sp!, {r4, lr}
	ldr r1, _0221727C ; =0x02240B24
	ldr r1, [r1]
	cmp r1, #0
	ldmeqia sp!, {r4, lr}
	bxeq lr
	sub r4, r0, #1
	add r0, r1, r4, lsl #5
	mov r1, #0
	mov r2, #0x1e
	bl MI_CpuFill8
	ldr r0, _0221727C ; =0x02240B24
	mov r1, #0
	ldr r0, [r0]
	add r0, r0, r4, lsl #2
	str r1, [r0, #0x1e0]
	ldmia sp!, {r4, lr}
	bx lr
	.align 2, 0
_0221727C: .word 0x02240B24

	arm_func_start MOD13_02217280
MOD13_02217280: ; 0x02217280
	ldr r3, _02217298 ; =0x02240B24
	ldr ip, _0221729C ; =0x020CE34C
	mov r1, #0
	mov r2, #0x21c
	str r0, [r3]
	bx ip
	.align 2, 0
_02217298: .word 0x02240B24
_0221729C: .word 0x020CE34C

	arm_func_start MOD13_022172A0
MOD13_022172A0: ; 0x022172A0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r2, _022172D8 ; =0x02240B28
	sub r1, r0, #2
	mov r0, #0x1e
	str r1, [r2]
	bl _s32_div_f
	ldr r1, _022172D8 ; =0x02240B28
	mov r2, #0x1e
	str r0, [r1, #4]
	str r2, [r1, #8]
	add sp, sp, #4
	ldmia sp!, {lr}
	bx lr
	.align 2, 0
_022172D8: .word 0x02240B28

	.section .rodata
	; 0x0223C420
	.incbin "baserom.nds", 0x2237C0, 0x24

	.section .data
	; 0x0223F780
	.incbin "baserom.nds", 0x226B20, 0x38

	.section .bss
	; 0x02240A40
	.space 0xF4
