	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD04_021DB730
MOD04_021DB730: ; 0x021DB730
	stmdb sp!, {r4, lr}
	ldr r2, _021DB770 ; =UNK04_02210484
	ldr r1, _021DB774 ; =0x000011DC
	ldr r2, [r2]
	mov r4, r0
	add r0, r2, r1
	bl OS_LockMutex
	ldr r2, _021DB770 ; =UNK04_02210484
	ldr r1, _021DB774 ; =0x000011DC
	ldr r0, [r2]
	add r0, r0, #0x1000
	str r4, [r0]
	ldr r0, [r2]
	add r0, r0, r1
	bl OS_UnlockMutex
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DB770: .word UNK04_02210484
_021DB774: .word 0x000011DC
	arm_func_end MOD04_021DB730

	arm_func_start MOD04_021DB778
MOD04_021DB778: ; 0x021DB778
	stmdb sp!, {r4, r5, r6, r7, r8, sb, sl, fp, lr}
	sub sp, sp, #0x2d4
	ldr r5, _021DC670 ; =UNK04_02210484
	mov r0, #0
	str r0, [sp]
	ldr r0, [r5]
	ldr r7, [sp]
	add r0, r0, #0x1000
	ldr sb, [r0, #0x108]
	ldr r8, [r0, #0x10c]
	mov r0, r7
	str r0, [sp, #8]
	str r0, [sp, #0x1c]
	mvn r0, #2
	str r0, [sp, #0x20]
	mov r0, r7
	str r0, [sp, #0x24]
	mvn r0, #3
	str r0, [sp, #0x28]
	mov r0, r7
	str r0, [sp, #0x2c]
	mov r0, #0x1000
	str r0, [sp, #0x14]
	mov r0, #5
	str r0, [sp, #0x30]
	mov r0, r7
	str r0, [sp, #0x34]
	str r0, [sp, #0x38]
	str r0, [sp, #0x3c]
	mov r0, #4
	str r0, [sp, #0x40]
	mov r0, r7
	str r0, [sp, #0x44]
	str r0, [sp, #0x48]
	str r0, [sp, #0x4c]
	str r0, [sp, #0x50]
	str r0, [sp, #0x58]
	str r0, [sp, #0x54]
	mvn r0, #4
	str r0, [sp, #0x5c]
	mov r0, r7
	str r0, [sp, #0x60]
	mvn r0, #1
	ldr r4, _021DC674 ; =UNK04_02210490
	mov r6, #1
	str r0, [sp, #0x18]
_021DB830:
	ldr r0, _021DC678 ; =UNK04_02210494
	ldr r1, [sp, #0x14]
	str r6, [r0, #4]
	str r1, [r0, #8]
	ldr r1, _021DC67C ; =0x00004E20
	str sb, [r0, #0xc]
	str r1, [r0, #0x18]
	str r8, [r0, #0x10]
	ldr r0, _021DC680 ; =UNK04_0220C36C
	ldr r1, [r5]
	ldr r2, [r0]
	ldr r0, _021DC678 ; =UNK04_02210494
	add r1, r1, #0x1000
	str r2, [r0]
	ldr r0, [sp, #0x18]
	str r0, [r1, #4]
	ldr r0, [r4]
	ldr r1, _021DC678 ; =UNK04_02210494
	bl MOD04_021DB608
	cmp r0, #0
	beq _021DB89C
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #1
	bl MOD04_021DB730
	b _021DC614
_021DB89C:
	ldr r0, [r4]
	bl MOD04_021DB570
	cmp r0, #0
	beq _021DB8C4
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #1
	bl MOD04_021DB730
	b _021DC614
_021DB8C4:
	ldr r0, _021DC684 ; =OSi_ThreadInfo
	ldr r0, [r0, #4]
	bl OS_GetThreadPriority
	sub r1, r0, #1
	ldr r0, [r4]
	bl MOD04_021DB4A4
	ldr r1, [r4]
	add r0, r1, #0x1000
	ldr r0, [r0, #0xba0]
	cmp r0, #0
	beq _021DB8FC
	ldr r0, _021DC688 ; =0x00001B34
	add r0, r1, r0
	bl OS_JoinThread
_021DB8FC:
	ldr r0, [r4]
	add r1, r0, #0x1000
	ldr r1, [r1, #0x20]
	cmp r1, #2
	beq _021DB91C
	cmp r1, #8
	beq _021DB948
	b _021DB930
_021DB91C:
	ldr r0, _021DC670 ; =UNK04_02210484
	mvn r1, #0
	ldr r0, [r0]
	add r0, r0, #0x1000
	str r1, [r0, #4]
_021DB930:
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #3
	bl MOD04_021DB730
	b _021DC614
_021DB948:
	ldr r1, [sp, #0x1c]
	bl MOD04_021DA3DC
	cmp r0, #1
	beq _021DB970
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #2
	bl MOD04_021DB730
	b _021DC614
_021DB970:
	ldr r0, [r4]
	ldr r1, _021DC68C ; =UNK04_0220C418
	bl MOD04_021DA388
	bl atol
	mov sl, r0
	ldr r0, _021DC690 ; =errno
	ldr r0, [r0]
	cmp r0, #0x22
	bne _021DB9A0
	mov r0, #2
	bl MOD04_021DB730
	b _021DC614
_021DB9A0:
	cmp sl, #0xc8
	beq _021DBCB4
	ldr r0, _021DC694 ; =0x0000012E
	cmp sl, r0
	bne _021DBC9C
	ldr r0, _021DC698 ; =UNK04_0221048C
	str r6, [r0]
	ldr r0, [r5]
	add r0, r0, #0x1000
	ldr r1, [r0, #0x118]
	cmp r1, #0
	beq _021DBC0C
	ldr r1, _021DC674 ; =UNK04_02210490
	mvn r2, #5
	str r2, [r0, #4]
	ldr r0, [r1]
	bl MOD04_021DAE4C
	ldr r2, _021DC678 ; =UNK04_02210494
	ldr r0, _021DC69C ; =UNK04_0220BEB4
	ldr r3, _021DC67C ; =0x00004E20
	ldr r0, [r0]
	mov r5, #0
	mov r4, #0x200
	ldr r1, _021DC6A0 ; =UNK04_0220C424
	str r0, [r2]
	str r5, [r2, #4]
	str r4, [r2, #8]
	str sb, [r2, #0xc]
	str r8, [r2, #0x10]
	str r3, [r2, #0x18]
	bl strcmp
	cmp r0, #0
	ldrne r0, _021DC678 ; =UNK04_02210494
	movne r1, #1
	strne r1, [r0, #0x14]
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r1, _021DC678 ; =UNK04_02210494
	ldr r0, [r0]
	bl MOD04_021DB608
	cmp r0, #0
	beq _021DBA5C
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #1
	bl MOD04_021DB730
	b _021DC614
_021DBA5C:
	add r0, sp, #0x240
	bl MOD04_021DA238
	cmp r0, #0
	beq _021DBA88
	ldr r0, _021DC674 ; =UNK04_02210490
	add r1, sp, #0x240
	ldr r0, [r0]
	mov r2, #1
	bl MOD04_021D9C2C
	cmp r0, #0
	bne _021DBAA0
_021DBA88:
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #8
	bl MOD04_021DB730
	b _021DC614
_021DBAA0:
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r1, _021DC6A4 ; =UNK04_0220C444
	ldr r0, [r0]
	ldr r2, _021DC6A8 ; =UNK04_0220C44C
	mov r3, #7
	bl MOD04_021DAB68
	cmp r0, #0
	bne _021DBAF8
	ldr r0, _021DC670 ; =UNK04_02210484
	ldr r0, [r0]
	add r0, r0, #0x1000
	ldr r4, [r0, #0x118]
	mov r0, r4
	bl strlen
	ldr r1, _021DC674 ; =UNK04_02210490
	mov r3, r0
	ldr r0, [r1]
	ldr r1, _021DC6AC ; =UNK04_0220C454
	mov r2, r4
	bl MOD04_021DAB68
	cmp r0, #0
	beq _021DBB10
_021DBAF8:
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #8
	bl MOD04_021DB730
	b _021DC614
_021DBB10:
	ldr r1, _021DC670 ; =UNK04_02210484
	ldr r0, _021DC6B0 ; =UNK04_0220C464
	ldr r1, [r1]
	mov r2, #0
	add r1, r1, #0x1000
	ldr r1, [r1, #0x118]
	blx r8
	ldr r0, _021DC670 ; =UNK04_02210484
	mov r2, #0
	ldr r0, [r0]
	ldr r1, _021DC674 ; =UNK04_02210490
	add r0, r0, #0x1000
	str r2, [r0, #0x118]
	ldr r0, [r1]
	bl MOD04_021DB570
	cmp r0, #0
	beq _021DBB6C
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #1
	bl MOD04_021DB730
	b _021DC614
_021DBB6C:
	ldr r0, _021DC684 ; =OSi_ThreadInfo
	ldr r0, [r0, #4]
	bl OS_GetThreadPriority
	ldr r2, _021DC674 ; =UNK04_02210490
	sub r1, r0, #1
	ldr r0, [r2]
	bl MOD04_021DB4A4
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r1, [r0]
	add r0, r1, #0x1000
	ldr r0, [r0, #0xba0]
	cmp r0, #0
	beq _021DBBAC
	ldr r0, _021DC688 ; =0x00001B34
	add r0, r1, r0
	bl OS_JoinThread
_021DBBAC:
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	add r1, r0, #0x1000
	ldr r1, [r1, #0x20]
	cmp r1, #2
	beq _021DBBD0
	cmp r1, #8
	beq _021DBBFC
	b _021DBBE4
_021DBBD0:
	ldr r0, _021DC670 ; =UNK04_02210484
	mvn r1, #0
	ldr r0, [r0]
	add r0, r0, #0x1000
	str r1, [r0, #4]
_021DBBE4:
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #3
	bl MOD04_021DB730
	b _021DC614
_021DBBFC:
	bl MOD04_021DAE4C
	mov r0, #7
	bl MOD04_021DB730
	b _021DC614
_021DBC0C:
	ldr r0, [r4]
	add r1, r0, #0x1000
	ldr fp, [r1, #0xa04]
	cmp fp, #0
	bne _021DBC30
	bl MOD04_021DAE4C
	mov r0, #2
	bl MOD04_021DB730
	b _021DC614
_021DBC30:
	mov r0, fp
	bl strlen
	add r1, r0, #1
	ldr r0, _021DC6B4 ; =UNK04_0220C394
	blx sb
	ldr r1, [r5]
	add r1, r1, #0x1000
	str r0, [r1, #0x114]
	ldr r0, [r5]
	add r0, r0, #0x1000
	ldr r0, [r0, #0x114]
	str r0, [sp, #0xc]
	cmp r0, #0
	bne _021DBC80
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #4
	bl MOD04_021DB730
	b _021DC614
_021DBC80:
	mov r0, fp
	bl strlen
	mov r2, r0
	ldr r0, [sp, #0xc]
	mov r1, fp
	bl strncpy
	b _021DBCB4
_021DBC9C:
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #0xa
	bl MOD04_021DB730
	b _021DC614
_021DBCB4:
	ldr r0, [r4]
	bl MOD04_021DAE4C
	add r0, sp, #0x68
	bl DWCi_BM_GetWiFiInfo
	ldr r2, [sp, #0x68]
	ldr r1, [sp, #0x6c]
	mov r0, #0
	cmp r1, r0
	cmpeq r2, r0
	bne _021DBDEC
	ldr r1, [r5]
	ldr r0, _021DC6B8 ; =UNK04_022104B0
	add r2, r1, #0x1000
	ldr r1, [sp, #0x20]
	str r1, [r2, #4]
	ldr r2, [sp, #0x24]
	mov r1, r0
	strh r2, [r1]
	strb r2, [r1, #0x34]
	ldr r2, [r5]
	ldr r1, [r4]
	add r3, r2, #0x1000
	ldr fp, [r3, #0x108]
	mov r2, r0
	str fp, [r2, #0x40]
	ldr r3, [r3, #0x10c]
	str r3, [r2, #0x44]
	bl MOD04_021D9ACC
	cmp r0, #0
	beq _021DBD38
	mov r0, #5
	bl MOD04_021DB730
	b _021DC614
_021DBD38:
	bl MOD04_021D98DC
	bl MOD04_021D988C
	cmp r0, #0x15
	beq _021DBDE8
	bl MOD04_021D988C
	cmp r0, #9
	bne _021DBD6C
	ldr r0, _021DC670 ; =UNK04_02210484
	mvn r1, #0
	ldr r0, [r0]
	add r0, r0, #0x1000
	str r1, [r0, #4]
	b _021DBDD8
_021DBD6C:
	add r0, sp, #0x7c
	bl MOD04_021D97F8
	ldr r0, _021DC6BC ; =UNK04_02210488
	ldr r0, [r0]
	cmp r0, #1
	bne _021DBDC4
	ldr r1, [sp, #0x7c]
	ldr r0, _021DC6C0 ; =0xFFFFA4FA
	cmp r1, r0
	beq _021DBDA0
	bl MOD04_021D988C
	cmp r0, #0xb
	bne _021DBDC4
_021DBDA0:
	ldr r0, _021DC670 ; =UNK04_02210484
	mov r1, #0
	ldr r0, [r0]
	add r0, r0, #0x1000
	str r1, [r0, #4]
	bl MOD04_021D991C
	mov r0, #0xb
	bl MOD04_021DB730
	b _021DC614
_021DBDC4:
	ldr r0, _021DC670 ; =UNK04_02210484
	ldr r1, [sp, #0x7c]
	ldr r0, [r0]
	add r0, r0, #0x1000
	str r1, [r0, #4]
_021DBDD8:
	bl MOD04_021D991C
	mov r0, #6
	bl MOD04_021DB730
	b _021DC614
_021DBDE8:
	bl MOD04_021D991C
_021DBDEC:
	cmp sl, #0xc8
	bne _021DBE14
	ldr r0, _021DC670 ; =UNK04_02210484
	mov r2, #0
	ldr r1, [r0]
	mov r0, #0xb
	add r1, r1, #0x1000
	str r2, [r1, #4]
	bl MOD04_021DB730
	b _021DC614
_021DBE14:
	ldr r0, [r5]
	ldr r1, _021DC6A0 ; =UNK04_0220C424
	add r2, r0, #0x1000
	ldr r0, [sp, #0x28]
	str r0, [r2, #4]
	ldr r0, _021DC678 ; =UNK04_02210494
	ldr r2, [sp, #0x2c]
	str sb, [r0, #0xc]
	str r2, [r0, #4]
	ldr r2, [sp, #0x14]
	str r8, [r0, #0x10]
	str r2, [r0, #8]
	ldr r2, _021DC6C4 ; =0x00009C40
	str r2, [r0, #0x18]
	ldr r0, _021DC69C ; =UNK04_0220BEB4
	ldr r2, _021DC678 ; =UNK04_02210494
	ldr r0, [r0]
	str r0, [r2]
	bl strcmp
	cmp r0, #0
	ldrne r0, _021DC678 ; =UNK04_02210494
	ldr r1, _021DC678 ; =UNK04_02210494
	strne r6, [r0, #0x14]
	ldr r0, [r4]
	bl MOD04_021DB608
	cmp r0, #0
	beq _021DBE98
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #1
	bl MOD04_021DB730
	b _021DC614
_021DBE98:
	add r0, sp, #0x240
	bl MOD04_021DA238
	cmp r0, #0
	beq _021DBEC0
	ldr r0, [r4]
	add r1, sp, #0x240
	mov r2, r6
	bl MOD04_021D9C2C
	cmp r0, #0
	bne _021DBED8
_021DBEC0:
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #8
	bl MOD04_021DB730
	b _021DC614
_021DBED8:
	ldr r0, [r4]
	ldr r1, _021DC6A4 ; =UNK04_0220C444
	ldr r2, _021DC6C8 ; =UNK04_0220C484
	ldr r3, [sp, #0x30]
	bl MOD04_021DAB68
	cmp r0, #0
	bne _021DBF24
	ldr r0, [r5]
	add r0, r0, #0x1000
	ldr sl, [r0, #0x114]
	mov r0, sl
	bl strlen
	mov r3, r0
	ldr r0, [r4]
	ldr r1, _021DC6CC ; =UNK04_0220C48C
	mov r2, sl
	bl MOD04_021DAB68
	cmp r0, #0
	beq _021DBF3C
_021DBF24:
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #8
	bl MOD04_021DB730
	b _021DC614
_021DBF3C:
	ldr r1, [r5]
	ldr r0, _021DC6D0 ; =UNK04_0220C3B0
	add r1, r1, #0x1000
	ldr r2, [sp, #0x34]
	ldr r1, [r1, #0x114]
	blx r8
	ldr r0, [r5]
	add r1, r0, #0x1000
	ldr r0, [sp, #0x38]
	str r0, [r1, #0x114]
	ldr r0, [r4]
	bl MOD04_021DB570
	cmp r0, #0
	beq _021DBF8C
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #1
	bl MOD04_021DB730
	b _021DC614
_021DBF8C:
	ldr r0, _021DC684 ; =OSi_ThreadInfo
	ldr r0, [r0, #4]
	bl OS_GetThreadPriority
	sub r1, r0, #1
	ldr r0, [r4]
	bl MOD04_021DB4A4
	ldr r1, [r4]
	add r0, r1, #0x1000
	ldr r0, [r0, #0xba0]
	cmp r0, #0
	beq _021DBFC4
	ldr r0, _021DC688 ; =0x00001B34
	add r0, r1, r0
	bl OS_JoinThread
_021DBFC4:
	ldr r0, [r4]
	add r1, r0, #0x1000
	ldr r1, [r1, #0x20]
	cmp r1, #2
	beq _021DC02C
	cmp r1, #3
	beq _021DBFEC
	cmp r1, #8
	beq _021DC058
	b _021DC040
_021DBFEC:
	bl MOD04_021DAE4C
	ldr r0, _021DC6BC ; =UNK04_02210488
	ldr r0, [r0]
	cmp r0, #1
	bne _021DC020
	ldr r0, _021DC670 ; =UNK04_02210484
	mov r2, #0
	ldr r1, [r0]
	mov r0, #0xb
	add r1, r1, #0x1000
	str r2, [r1, #4]
	bl MOD04_021DB730
	b _021DC614
_021DC020:
	mov r0, #3
	bl MOD04_021DB730
	b _021DC614
_021DC02C:
	ldr r0, _021DC670 ; =UNK04_02210484
	mvn r1, #0
	ldr r0, [r0]
	add r0, r0, #0x1000
	str r1, [r0, #4]
_021DC040:
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #3
	bl MOD04_021DB730
	b _021DC614
_021DC058:
	ldr r1, [sp, #0x3c]
	bl MOD04_021DA3DC
	cmp r0, #1
	beq _021DC080
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #2
	bl MOD04_021DB730
	b _021DC614
_021DC080:
	ldr r0, [r4]
	ldr r1, _021DC68C ; =UNK04_0220C418
	bl MOD04_021DA388
	bl atol
	mov sl, r0
	ldr r0, _021DC690 ; =errno
	ldr r0, [r0]
	cmp r0, #0x22
	bne _021DC0BC
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #2
	bl MOD04_021DB730
	b _021DC614
_021DC0BC:
	cmp sl, #0xc8
	beq _021DC118
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	ldr r0, _021DC6BC ; =UNK04_02210488
	ldr r0, [r0]
	cmp r0, #1
	bne _021DC10C
	ldr r0, _021DC694 ; =0x0000012E
	cmp sl, r0
	bne _021DC10C
	ldr r0, _021DC670 ; =UNK04_02210484
	mov r2, #0
	ldr r1, [r0]
	mov r0, #0xb
	add r1, r1, #0x1000
	str r2, [r1, #4]
	bl MOD04_021DB730
	b _021DC614
_021DC10C:
	mov r0, #2
	bl MOD04_021DB730
	b _021DC614
_021DC118:
	ldr r0, [r4]
	ldr r1, _021DC6D4 ; =UNK04_0220C494
	ldr r3, [sp, #0x40]
	add r2, sp, #0x64
	bl MOD04_021DA334
	cmp r0, #0
	bgt _021DC14C
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #9
	bl MOD04_021DB730
	b _021DC614
_021DC14C:
	add r0, sp, #0x64
	bl atol
	ldr r1, _021DC690 ; =errno
	ldr r1, [r1]
	cmp r1, #0x22
	bne _021DC17C
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #9
	bl MOD04_021DB730
	b _021DC614
_021DC17C:
	ldr r1, _021DC6BC ; =UNK04_02210488
	ldr r1, [r1]
	cmp r1, #1
	bne _021DC1B4
	cmp r0, #0x72
	bne _021DC1B4
	ldr r0, _021DC670 ; =UNK04_02210484
	mov r2, #0
	ldr r1, [r0]
	mov r0, #0xb
	add r1, r1, #0x1000
	str r2, [r1, #4]
	bl MOD04_021DB730
	b _021DC614
_021DC1B4:
	cmp r0, #0x64
	blt _021DC1D4
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #6
	bl MOD04_021DB730
	b _021DC614
_021DC1D4:
	ldr r2, [sp, #0x44]
	ldr r0, [r4]
	ldr r1, _021DC6D8 ; =UNK04_0220C4A0
	mov r3, r2
	bl MOD04_021DA334
	mov fp, r0
	cmp fp, #0
	bgt _021DC20C
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #9
	bl MOD04_021DB730
	b _021DC614
_021DC20C:
	ldr r2, [sp, #0x48]
	ldr r0, [r4]
	ldr r1, _021DC6DC ; =UNK04_0220C4A4
	mov r3, r2
	bl MOD04_021DA334
	str r0, [sp, #4]
	cmp r0, #0
	bgt _021DC244
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #9
	bl MOD04_021DB730
	b _021DC614
_021DC244:
	ldr r2, [sp, #0x4c]
	ldr r0, [r4]
	ldr r1, _021DC6E0 ; =UNK04_0220C4AC
	mov r3, r2
	bl MOD04_021DA334
	mov sl, r0
	ldr r0, _021DC6E4 ; =UNK04_0220C3CC
	add r1, fp, #1
	blx sb
	str r0, [sp]
	cmp r0, #0
	bne _021DC28C
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #4
	bl MOD04_021DB730
	b _021DC614
_021DC28C:
	ldr r1, [sp, #4]
	ldr r0, _021DC6E8 ; =UNK04_0220C3D8
	add r1, r1, #1
	blx sb
	movs r7, r0
	bne _021DC2BC
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #4
	bl MOD04_021DB730
	b _021DC614
_021DC2BC:
	cmp sl, #0
	ble _021DC2F4
	ldr r0, _021DC6EC ; =UNK04_0220C3E8
	add r1, sl, #1
	blx sb
	str r0, [sp, #8]
	cmp r0, #0
	bne _021DC2F4
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #4
	bl MOD04_021DB730
	b _021DC614
_021DC2F4:
	ldr r0, [r4]
	ldr r1, _021DC6D8 ; =UNK04_0220C4A0
	ldr r2, [sp]
	add r3, fp, #1
	bl MOD04_021DA334
	cmp r0, #0
	bge _021DC328
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #9
	bl MOD04_021DB730
	b _021DC614
_021DC328:
	ldr r1, [sp, #4]
	ldr r2, [sp, #0x50]
	add r3, r1, #1
	ldr r1, [sp]
	strb r2, [r1, r0]
	ldr r0, [r4]
	ldr r1, _021DC6DC ; =UNK04_0220C4A4
	mov r2, r7
	bl MOD04_021DA334
	cmp r0, #0
	bge _021DC36C
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #9
	bl MOD04_021DB730
	b _021DC614
_021DC36C:
	ldr r1, [sp, #0x54]
	cmp sl, #0
	strb r1, [r7, r0]
	mov fp, r1
	ble _021DC404
	ldr r0, [r4]
	ldr r1, _021DC6E0 ; =UNK04_0220C4AC
	ldr r2, [sp, #8]
	add r3, sl, #1
	bl MOD04_021DA334
	cmp r0, #0
	bge _021DC3B4
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #9
	bl MOD04_021DB730
	b _021DC614
_021DC3B4:
	ldr r2, [sp, #0x58]
	ldr r1, [sp, #8]
	strb r2, [r1, r0]
	mov r0, r1
	bl atol
	ldr r1, _021DC690 ; =errno
	ldr r1, [r1]
	cmp r1, #0x22
	bne _021DC3F0
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #9
	bl MOD04_021DB730
	b _021DC614
_021DC3F0:
	mov r1, #0x3e8
	mul fp, r0, r1
	ldr r0, _021DC6F0 ; =0x0002BF20
	cmp fp, r0
	movgt fp, r0
_021DC404:
	ldr r0, [r4]
	bl MOD04_021DAE4C
	ldr r0, [r5]
	ldr r1, _021DC678 ; =UNK04_02210494
	add r2, r0, #0x1000
	ldr r0, [sp, #0x5c]
	str r0, [r2, #4]
	mov r0, r1
	ldr r2, [sp]
	str sb, [r0, #0xc]
	str r2, [r0]
	ldr r2, [sp, #0x60]
	str r8, [r0, #0x10]
	str r2, [r0, #4]
	ldr r2, [sp, #0x14]
	str r2, [r0, #8]
	ldr r2, _021DC6F4 ; =0x0001D4C0
	str r2, [r0, #0x18]
	ldr r0, [r4]
	bl MOD04_021DB608
	cmp r0, #0
	beq _021DC474
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #1
	bl MOD04_021DB730
	b _021DC614
_021DC474:
	ldr r0, [r4]
	mov r1, r7
	bl MOD04_021DAACC
	cmp r0, #0
	beq _021DC4A0
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #8
	bl MOD04_021DB730
	b _021DC614
_021DC4A0:
	ldr r0, [r4]
	bl MOD04_021DB570
	cmp r0, #0
	beq _021DC4C8
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #1
	bl MOD04_021DB730
	b _021DC614
_021DC4C8:
	ldr r0, _021DC684 ; =OSi_ThreadInfo
	ldr r0, [r0, #4]
	bl OS_GetThreadPriority
	sub r1, r0, #1
	ldr r0, [r4]
	bl MOD04_021DB4A4
	ldr r1, [r4]
	add r0, r1, #0x1000
	ldr r0, [r0, #0xba0]
	cmp r0, #0
	beq _021DC500
	ldr r0, _021DC688 ; =0x00001B34
	add r0, r1, r0
	bl OS_JoinThread
_021DC500:
	ldr r0, [r4]
	add r1, r0, #0x1000
	ldr r1, [r1, #0x20]
	cmp r1, #2
	beq _021DC520
	cmp r1, #8
	beq _021DC54C
	b _021DC534
_021DC520:
	ldr r0, _021DC670 ; =UNK04_02210484
	mvn r1, #0
	ldr r0, [r0]
	add r0, r0, #0x1000
	str r1, [r0, #4]
_021DC534:
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #3
	bl MOD04_021DB730
	b _021DC614
_021DC54C:
	mov r1, r6
	bl MOD04_021DA3DC
	cmp r0, #1
	beq _021DC574
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #2
	bl MOD04_021DB730
	b _021DC614
_021DC574:
	ldr r0, [r4]
	add r1, r0, #0x1000
	ldr sl, [r1, #0xa04]
	cmp sl, #0
	bne _021DC598
	bl MOD04_021DAE4C
	mov r0, #2
	bl MOD04_021DB730
	b _021DC614
_021DC598:
	mov r0, sl
	bl strlen
	add r1, r0, #1
	ldr r0, _021DC6F8 ; =UNK04_0220C3F8
	blx sb
	ldr r1, [r5]
	add r1, r1, #0x1000
	str r0, [r1, #0x118]
	ldr r0, [r5]
	add r0, r0, #0x1000
	ldr r0, [r0, #0x118]
	str r0, [sp, #0x10]
	cmp r0, #0
	bne _021DC5E8
	ldr r0, _021DC674 ; =UNK04_02210490
	ldr r0, [r0]
	bl MOD04_021DAE4C
	mov r0, #4
	bl MOD04_021DB730
	b _021DC614
_021DC5E8:
	mov r0, sl
	bl strlen
	mov r2, r0
	ldr r0, [sp, #0x10]
	mov r1, sl
	bl strncpy
	ldr r0, [r4]
	bl MOD04_021DAE4C
	mov r0, fp
	bl OS_Sleep
	b _021DB830
_021DC614:
	ldr r0, [sp]
	cmp r0, #0
	beq _021DC630
	ldr r0, _021DC6FC ; =UNK04_0220C4B4
	ldr r1, [sp]
	mov r2, #0
	blx r8
_021DC630:
	cmp r7, #0
	beq _021DC648
	ldr r0, _021DC700 ; =UNK04_0220C4C0
	mov r1, r7
	mov r2, #0
	blx r8
_021DC648:
	ldr r0, [sp, #8]
	cmp r0, #0
	addeq sp, sp, #0x2d4
	ldmeqia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	ldr r0, _021DC704 ; =UNK04_0220C4CC
	ldr r1, [sp, #8]
	mov r2, #0
	blx r8
	add sp, sp, #0x2d4
	ldmia sp!, {r4, r5, r6, r7, r8, sb, sl, fp, pc}
	.align 2, 0
_021DC670: .word UNK04_02210484
_021DC674: .word UNK04_02210490
_021DC678: .word UNK04_02210494
_021DC67C: .word 0x00004E20
_021DC680: .word UNK04_0220C36C
_021DC684: .word OSi_ThreadInfo
_021DC688: .word 0x00001B34
_021DC68C: .word UNK04_0220C418
_021DC690: .word errno
_021DC694: .word 0x0000012E
_021DC698: .word UNK04_0221048C
_021DC69C: .word UNK04_0220BEB4
_021DC6A0: .word UNK04_0220C424
_021DC6A4: .word UNK04_0220C444
_021DC6A8: .word UNK04_0220C44C
_021DC6AC: .word UNK04_0220C454
_021DC6B0: .word UNK04_0220C464
_021DC6B4: .word UNK04_0220C394
_021DC6B8: .word UNK04_022104B0
_021DC6BC: .word UNK04_02210488
_021DC6C0: .word 0xFFFFA4FA
_021DC6C4: .word 0x00009C40
_021DC6C8: .word UNK04_0220C484
_021DC6CC: .word UNK04_0220C48C
_021DC6D0: .word UNK04_0220C3B0
_021DC6D4: .word UNK04_0220C494
_021DC6D8: .word UNK04_0220C4A0
_021DC6DC: .word UNK04_0220C4A4
_021DC6E0: .word UNK04_0220C4AC
_021DC6E4: .word UNK04_0220C3CC
_021DC6E8: .word UNK04_0220C3D8
_021DC6EC: .word UNK04_0220C3E8
_021DC6F0: .word 0x0002BF20
_021DC6F4: .word 0x0001D4C0
_021DC6F8: .word UNK04_0220C3F8
_021DC6FC: .word UNK04_0220C4B4
_021DC700: .word UNK04_0220C4C0
_021DC704: .word UNK04_0220C4CC
	arm_func_end MOD04_021DB778

	arm_func_start MOD04_021DC708
MOD04_021DC708: ; 0x021DC708
	stmdb sp!, {lr}
	sub sp, sp, #0xc
	ldr r0, _021DC788 ; =UNK04_02210484
	ldr r1, [r0]
	add r0, r1, #0x1000
	ldr r0, [r0, #0x188]
	cmp r0, #0
	beq _021DC740
	ldr r0, _021DC78C ; =0x0000111C
	add r0, r1, r0
	bl OS_IsThreadTerminated
	cmp r0, #0
	addeq sp, sp, #0xc
	ldmeqia sp!, {pc}
_021DC740:
	ldr r1, _021DC788 ; =UNK04_02210484
	ldr r0, _021DC78C ; =0x0000111C
	ldr r2, [r1]
	mov r3, #0x1000
	ldr r1, _021DC790 ; =MOD04_021DB778
	str r3, [sp]
	mov ip, #0x10
	add r0, r2, r0
	add r3, r2, #0x1000
	str ip, [sp, #4]
	bl OS_CreateThread
	ldr r1, _021DC788 ; =UNK04_02210484
	ldr r0, _021DC78C ; =0x0000111C
	ldr r1, [r1]
	add r0, r1, r0
	bl OS_WakeupThreadDirect
	add sp, sp, #0xc
	ldmfd sp!, {pc}
	.align 2, 0
_021DC788: .word UNK04_02210484
_021DC78C: .word 0x0000111C
_021DC790: .word MOD04_021DB778
	arm_func_end MOD04_021DC708

	arm_func_start MOD04_021DC794
MOD04_021DC794: ; 0x021DC794
	ldr r0, _021DC7A8 ; =UNK04_02210484
	ldr r0, [r0]
	add r0, r0, #0x1000
	ldr r0, [r0, #4]
	bx lr
	.align 2, 0
_021DC7A8: .word UNK04_02210484
	arm_func_end MOD04_021DC794

	arm_func_start MOD04_021DC7AC
MOD04_021DC7AC: ; 0x021DC7AC
	stmdb sp!, {r4, lr}
	ldr r1, _021DC7E8 ; =UNK04_02210484
	ldr r0, _021DC7EC ; =0x000011DC
	ldr r1, [r1]
	add r0, r1, r0
	bl OS_LockMutex
	ldr r1, _021DC7E8 ; =UNK04_02210484
	ldr r0, _021DC7EC ; =0x000011DC
	ldr r2, [r1]
	add r1, r2, #0x1000
	add r0, r2, r0
	ldr r4, [r1]
	bl OS_UnlockMutex
	mov r0, r4
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DC7E8: .word UNK04_02210484
_021DC7EC: .word 0x000011DC
	arm_func_end MOD04_021DC7AC

	arm_func_start MOD04_021DC7F0
MOD04_021DC7F0: ; 0x021DC7F0
	stmdb sp!, {lr}
	sub sp, sp, #4
	ldr r0, _021DC864 ; =UNK04_02210484
	ldr r0, [r0]
	cmp r0, #0
	addeq sp, sp, #4
	ldmeqia sp!, {pc}
	ldr r0, _021DC868 ; =UNK04_02210490
	ldr r0, [r0]
	cmp r0, #0
	beq _021DC820
	bl MOD04_021DB440
_021DC820:
	bl MOD04_021D9974
	ldr r0, _021DC864 ; =UNK04_02210484
	ldr r1, [r0]
	add r0, r1, #0x1000
	ldr r0, [r0, #0x188]
	cmp r0, #0
	beq _021DC848
	ldr r0, _021DC86C ; =0x0000111C
	add r0, r1, r0
	bl OS_JoinThread
_021DC848:
	ldr r0, _021DC864 ; =UNK04_02210484
	mvn r1, #6
	ldr r0, [r0]
	add r0, r0, #0x1000
	str r1, [r0, #4]
	add sp, sp, #4
	ldmfd sp!, {pc}
	.align 2, 0
_021DC864: .word UNK04_02210484
_021DC868: .word UNK04_02210490
_021DC86C: .word 0x0000111C
	arm_func_end MOD04_021DC7F0

	arm_func_start MOD04_021DC870
MOD04_021DC870: ; 0x021DC870
	stmdb sp!, {r4, lr}
	ldr r1, _021DC958 ; =UNK04_02210484
	ldr r0, _021DC95C ; =UNK04_02210490
	ldr r1, [r1]
	ldr r0, [r0]
	add r1, r1, #0x1000
	cmp r0, #0
	ldr r4, [r1, #0x10c]
	beq _021DC8B8
	bl MOD04_021DAE4C
	ldr r1, _021DC95C ; =UNK04_02210490
	ldr r0, _021DC960 ; =UNK04_0220C4D8
	ldr r1, [r1]
	mov r2, #0
	blx r4
	ldr r0, _021DC95C ; =UNK04_02210490
	mov r1, #0
	str r1, [r0]
_021DC8B8:
	bl MOD04_021D991C
	ldr r0, _021DC958 ; =UNK04_02210484
	ldr r0, [r0]
	cmp r0, #0
	ldmeqia sp!, {r4, pc}
	add r0, r0, #0x1000
	ldr r1, [r0, #0x114]
	cmp r1, #0
	beq _021DC8FC
	ldr r0, _021DC964 ; =UNK04_0220C3B0
	mov r2, #0
	blx r4
	ldr r0, _021DC958 ; =UNK04_02210484
	mov r1, #0
	ldr r0, [r0]
	add r0, r0, #0x1000
	str r1, [r0, #0x114]
_021DC8FC:
	ldr r0, _021DC958 ; =UNK04_02210484
	ldr r0, [r0]
	add r0, r0, #0x1000
	ldr r1, [r0, #0x118]
	cmp r1, #0
	beq _021DC934
	ldr r0, _021DC968 ; =UNK04_0220C464
	mov r2, #0
	blx r4
	ldr r0, _021DC958 ; =UNK04_02210484
	mov r1, #0
	ldr r0, [r0]
	add r0, r0, #0x1000
	str r1, [r0, #0x118]
_021DC934:
	ldr r1, _021DC958 ; =UNK04_02210484
	ldr r0, _021DC96C ; =UNK04_0220C4E8
	ldr r1, [r1]
	mov r2, #0
	blx r4
	ldr r0, _021DC958 ; =UNK04_02210484
	mov r1, #0
	str r1, [r0]
	ldmia sp!, {r4, pc}
	.align 2, 0
_021DC958: .word UNK04_02210484
_021DC95C: .word UNK04_02210490
_021DC960: .word UNK04_0220C4D8
_021DC964: .word UNK04_0220C3B0
_021DC968: .word UNK04_0220C464
_021DC96C: .word UNK04_0220C4E8
	arm_func_end MOD04_021DC870

	arm_func_start MOD04_021DC970
MOD04_021DC970: ; 0x021DC970
	stmdb sp!, {r4, r5, lr}
	sub sp, sp, #4
	ldr r1, _021DCA5C ; =UNK04_02210484
	mov r5, r0
	ldr r0, [r1]
	ldr r4, [r5]
	cmp r0, #0
	addne sp, sp, #4
	movne r0, #4
	ldmneia sp!, {r4, r5, pc}
	ldr r0, _021DCA60 ; =UNK04_0220C4FC
	ldr r1, _021DCA64 ; =0x000011F4
	blx r4
	ldr r1, _021DCA5C ; =UNK04_02210484
	cmp r0, #0
	str r0, [r1]
	addeq sp, sp, #4
	moveq r0, #4
	ldmeqia sp!, {r4, r5, pc}
	ldr r2, _021DCA64 ; =0x000011F4
	mov r1, #0
	bl MI_CpuFill8
	ldr r1, _021DCA5C ; =UNK04_02210484
	ldr r2, _021DCA68 ; =0xFFFE7961
	ldr r0, [r1]
	ldr r3, _021DCA6C ; =0x00001108
	add r0, r0, #0x1000
	str r2, [r0, #4]
	ldr ip, [r1]
	ldmia r5, {r0, r1, r2}
	add r3, ip, r3
	stmia r3, {r0, r1, r2}
	ldr r0, _021DCA70 ; =UNK04_02210490
	ldr r0, [r0]
	cmp r0, #0
	addne sp, sp, #4
	movne r0, #4
	ldmneia sp!, {r4, r5, pc}
	ldr r0, _021DCA74 ; =UNK04_0220C510
	ldr r1, _021DCA78 ; =0x00001C10
	blx r4
	ldr r1, _021DCA70 ; =UNK04_02210490
	cmp r0, #0
	str r0, [r1]
	addeq sp, sp, #4
	moveq r0, #4
	ldmeqia sp!, {r4, r5, pc}
	ldr r1, _021DCA5C ; =UNK04_02210484
	ldr r0, _021DCA7C ; =0x000011DC
	ldr r2, [r1]
	ldr r1, _021DCA80 ; =UNK04_0221048C
	mov r3, #0
	add r0, r2, r0
	str r3, [r1]
	bl OS_InitMutex
	bl MOD04_021DC708
	mov r0, #0
	add sp, sp, #4
	ldmia sp!, {r4, r5, pc}
	.align 2, 0
_021DCA5C: .word UNK04_02210484
_021DCA60: .word UNK04_0220C4FC
_021DCA64: .word 0x000011F4
_021DCA68: .word 0xFFFE7961
_021DCA6C: .word 0x00001108
_021DCA70: .word UNK04_02210490
_021DCA74: .word UNK04_0220C510
_021DCA78: .word 0x00001C10
_021DCA7C: .word 0x000011DC
_021DCA80: .word UNK04_0221048C
	arm_func_end MOD04_021DC970

	.section .data

	.global UNK04_0220C36C
UNK04_0220C36C: ; 0x0220C36C
	.word UNK04_0220C370

	.global UNK04_0220C370
UNK04_0220C370: ; 0x0220C370
	.asciz "http://conntest.nintendowifi.net/"

	.balign 4, 0
	.global UNK04_0220C394
UNK04_0220C394: ; 0x0220C394
	.asciz "ALLOC DWCnetcheck->body_302"

	.balign 4, 0
	.global UNK04_0220C3B0
UNK04_0220C3B0: ; 0x0220C3B0
	.asciz "FREE DWCnetcheck->body_302"

	.balign 4, 0
	.global UNK04_0220C3CC
UNK04_0220C3CC: ; 0x0220C3CC
	.asciz "ALLOC url"

	.balign 4, 0
	.global UNK04_0220C3D8
UNK04_0220C3D8: ; 0x0220C3D8
	.asciz "ALLOC data_len"

	.balign 4, 0
	.global UNK04_0220C3E8
UNK04_0220C3E8: ; 0x0220C3E8
	.asciz "ALLOC wait_len"

	.balign 4, 0
	.global UNK04_0220C3F8
UNK04_0220C3F8: ; 0x0220C3F8
	.asciz "ALLOC DWCnetcheck->body_wayport"

	.balign 4, 0
	.global UNK04_0220C418
UNK04_0220C418: ; 0x0220C418
	.asciz "httpresult"

	.balign 4, 0
	.global UNK04_0220C424
UNK04_0220C424: ; 0x0220C424
	.asciz "https://nas.nintendowifi.net/ac"

	.balign 4, 0
	.global UNK04_0220C444
UNK04_0220C444: ; 0x0220C444
	.asciz "action"

	.balign 4, 0
	.global UNK04_0220C44C
UNK04_0220C44C: ; 0x0220C44C
	.asciz "message"

	.balign 4, 0
	.global UNK04_0220C454
UNK04_0220C454: ; 0x0220C454
	.asciz "HotSpotResponse"

	.balign 4, 0
	.global UNK04_0220C464
UNK04_0220C464: ; 0x0220C464
	.asciz "FREE DWCnetcheck->body_wayport"

	.balign 4, 0
	.global UNK04_0220C484
UNK04_0220C484: ; 0x0220C484
	.asciz "parse"

	.balign 4, 0
	.global UNK04_0220C48C
UNK04_0220C48C: ; 0x0220C48C
	.asciz "HTML"

	.balign 4, 0
	.global UNK04_0220C494
UNK04_0220C494: ; 0x0220C494
	.asciz "returncd"

	.balign 4, 0
	.global UNK04_0220C4A0
UNK04_0220C4A0: ; 0x0220C4A0
	.asciz "url"

	.balign 4, 0
	.global UNK04_0220C4A4
UNK04_0220C4A4: ; 0x0220C4A4
	.asciz "data"

	.balign 4, 0
	.global UNK04_0220C4AC
UNK04_0220C4AC: ; 0x0220C4AC
	.asciz "wait"

	.balign 4, 0
	.global UNK04_0220C4B4
UNK04_0220C4B4: ; 0x0220C4B4
	.asciz "FREE url"

	.balign 4, 0
	.global UNK04_0220C4C0
UNK04_0220C4C0: ; 0x0220C4C0
	.asciz "FREE data"

	.balign 4, 0
	.global UNK04_0220C4CC
UNK04_0220C4CC: ; 0x0220C4CC
	.asciz "FREE wait"

	.balign 4, 0
	.global UNK04_0220C4D8
UNK04_0220C4D8: ; 0x0220C4D8
	.asciz "FREE DWChttp"

	.balign 4, 0
	.global UNK04_0220C4E8
UNK04_0220C4E8: ; 0x0220C4E8
	.asciz "FREE DWCnetcheck"

	.balign 4, 0
	.global UNK04_0220C4FC
UNK04_0220C4FC: ; 0x0220C4FC
	.asciz "ALLOC DWCnetcheck"

	.balign 4, 0
	.global UNK04_0220C510
UNK04_0220C510: ; 0x0220C510
	.asciz "ALLOC DWChttp"

	.balign 4, 0
	.section .bss

	.global UNK04_02210490
UNK04_02210490: ; 0x02210490
	.space 0x4

	.global UNK04_02210494
UNK04_02210494: ; 0x02210494
	.space 0x1C

	.global UNK04_022104B0
UNK04_022104B0: ; 0x022104B0
	.space 0x48
