	.include "asm/macros.inc"
	.include "global.inc"
	.section .text
	.balign 4, 0

	arm_func_start MOD04_021D9C2C
MOD04_021D9C2C: ; 0x021D9C2C
	stmdb sp!, {r4, r5, r6, lr}
	sub sp, sp, #0x28
	mov r4, r2
	mov r6, r0
	mov r5, r1
	mov ip, #2
	ldr r2, _021D9F30 ; =UNK04_0220BFE4
	add r0, sp, #4
	mov r1, #0x21
	mov r3, #1
	str ip, [sp]
	bl OS_SNPrintf
	add r0, sp, #4
	bl strlen
	mov r3, r0
	ldr r1, _021D9F34 ; =UNK04_0220BFF0
	mov r0, r6
	add r2, sp, #4
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	mov r0, r5
	bl strlen
	mov r3, r0
	ldr r1, _021D9F38 ; =UNK04_0220BFF8
	mov r0, r6
	mov r2, r5
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	add r0, r5, #0xe
	bl strlen
	mov r3, r0
	ldr r1, _021D9F3C ; =UNK04_0220C000
	mov r0, r6
	add r2, r5, #0xe
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	add r0, r5, #0x41
	bl strlen
	mov r3, r0
	ldr r1, _021D9F40 ; =UNK04_0220C008
	mov r0, r6
	add r2, r5, #0x41
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	add r0, r5, #0x6f
	bl strlen
	mov r3, r0
	ldr r1, _021D9F44 ; =UNK04_0220C010
	mov r0, r6
	add r2, r5, #0x6f
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	add r0, r5, #0x15
	bl strlen
	mov r3, r0
	ldr r1, _021D9F48 ; =UNK04_0220C018
	mov r0, r6
	add r2, r5, #0x15
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	add r0, r5, #0x1a
	bl strlen
	mov r3, r0
	ldr r1, _021D9F4C ; =UNK04_0220C020
	mov r0, r6
	add r2, r5, #0x1a
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	add r0, r5, #0x1d
	bl strlen
	mov r3, r0
	ldr r1, _021D9F50 ; =UNK04_0220C028
	mov r0, r6
	add r2, r5, #0x1d
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	add r0, r5, #0x1f
	bl strlen
	mov r3, r0
	ldr r1, _021D9F54 ; =UNK04_0220C030
	mov r0, r6
	add r2, r5, #0x1f
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	add r0, r5, #0x2c
	bl strlen
	mov r3, r0
	ldr r1, _021D9F58 ; =UNK04_0220C038
	mov r0, r6
	add r2, r5, #0x2c
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	add r0, r5, #0x2f
	bl strlen
	mov r3, r0
	ldr r1, _021D9F5C ; =UNK04_0220C040
	mov r0, r6
	add r2, r5, #0x2f
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	add r0, r5, #0x34
	bl strlen
	mov r3, r0
	ldr r1, _021D9F60 ; =UNK04_0220C048
	mov r0, r6
	add r2, r5, #0x34
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	add r0, r5, #0x7e
	bl wcslen
	mov r3, r0
	ldr r1, _021D9F64 ; =UNK04_0220C050
	mov r0, r6
	add r2, r5, #0x7e
	mov r3, r3, lsl #1
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	cmp r4, #1
	bne _021D9ED0
	add r0, r5, #0x4e
	bl strlen
	mov r3, r0
	ldr r1, _021D9F68 ; =UNK04_0220C058
	mov r0, r6
	add r2, r5, #0x4e
	bl MOD04_021DAB68
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
_021D9ED0:
	ldr r2, _021D9F6C ; =UNK04_0220C060
	mov ip, #2
	add r0, sp, #4
	mov r1, #0x21
	mov r3, #1
	str ip, [sp]
	bl OS_SNPrintf
	ldr r1, _021D9F70 ; =UNK04_0220C078
	add r2, sp, #4
	mov r0, r6
	bl MOD04_021DAC98
	cmp r0, #0
	addne sp, sp, #0x28
	movne r0, #0
	ldmneia sp!, {r4, r5, r6, pc}
	ldr r1, _021D9F74 ; =UNK04_0220C084
	mov r0, r6
	add r2, r5, #0x15
	bl MOD04_021DAC98
	cmp r0, #0
	moveq r0, #1
	movne r0, #0
	add sp, sp, #0x28
	ldmia sp!, {r4, r5, r6, pc}
	.align 2, 0
_021D9F30: .word UNK04_0220BFE4
_021D9F34: .word UNK04_0220BFF0
_021D9F38: .word UNK04_0220BFF8
_021D9F3C: .word UNK04_0220C000
_021D9F40: .word UNK04_0220C008
_021D9F44: .word UNK04_0220C010
_021D9F48: .word UNK04_0220C018
_021D9F4C: .word UNK04_0220C020
_021D9F50: .word UNK04_0220C028
_021D9F54: .word UNK04_0220C030
_021D9F58: .word UNK04_0220C038
_021D9F5C: .word UNK04_0220C040
_021D9F60: .word UNK04_0220C048
_021D9F64: .word UNK04_0220C050
_021D9F68: .word UNK04_0220C058
_021D9F6C: .word UNK04_0220C060
_021D9F70: .word UNK04_0220C078
_021D9F74: .word UNK04_0220C084
	arm_func_end MOD04_021D9C2C

	arm_func_start MOD04_021D9F78
MOD04_021D9F78: ; 0x021D9F78
	stmdb sp!, {r4, r5, r6, r7, r8, sb, lr}
	sub sp, sp, #0x8c
	mov r6, r1
	mov r1, #0
	mov r2, #0x94
	mov r4, r0
	bl MI_CpuFill8
	ldr r3, [r6]
	ldr r5, [r6, #4]
	mov r0, #0
	cmp r5, r0
	cmpeq r3, r0
	beq _021D9FC4
	ldr r2, _021DA218 ; =UNK04_0220C094
	mov r0, r4
	mov r1, #0xe
	str r5, [sp]
	bl OS_SNPrintf
	b _021D9FE0
_021D9FC4:
	ldr r3, [r6, #8]
	ldr r5, [r6, #0xc]
	ldr r2, _021DA218 ; =UNK04_0220C094
	mov r0, r4
	mov r1, #0xe
	str r5, [sp]
	bl OS_SNPrintf
_021D9FE0:
	ldrh r3, [r6, #0x10]
	ldr r2, _021DA21C ; =UNK04_0220C09C
	add r0, r4, #0xe
	mov r1, #7
	bl OS_SNPrintf
	ldr r0, _021DA220 ; =0x027FFE0C
	ldrb r0, [r0]
	cmp r0, #0
	bne _021DA008
	bl OS_Terminate
_021DA008:
	ldr r0, _021DA220 ; =0x027FFE0C
	add r1, r4, #0x15
	mov r2, #4
	bl MI_CpuCopy8
	ldr r0, _021DA224 ; =0x027FFE10
	ldrb r0, [r0]
	cmp r0, #0
	bne _021DA02C
	bl OS_Terminate
_021DA02C:
	ldr r0, _021DA224 ; =0x027FFE10
	add r1, r4, #0x1a
	mov r2, #2
	bl MI_CpuCopy8
	mov r1, #0x30
	add r0, sp, #0x16
	strb r1, [r4, #0x1d]
	bl OS_GetMacAddress
	ldr r5, _021DA228 ; =UNK04_0220C0A4
	add r7, sp, #0x16
	add r6, r4, #0x1f
	mov r8, #0
_021DA05C:
	ldrb r2, [r7]
	mov r0, r6
	mov r1, r5
	bl OS_SPrintf
	add r8, r8, #1
	cmp r8, #6
	add r7, r7, #1
	add r6, r6, #2
	blt _021DA05C
	add r0, sp, #0x38
	bl OS_GetOwnerInfo
	ldrb r0, [sp, #0x38]
	ldr r2, _021DA228 ; =UNK04_0220C0A4
	mov r1, #3
	cmp r0, #6
	movhi r0, #1
	strhib r0, [sp, #0x38]
	ldrb r3, [sp, #0x38]
	add r0, r4, #0x2c
	bl OS_SNPrintf
	add r0, sp, #0x3c
	add r1, r4, #0x7e
	mov r2, #0x14
	bl MI_CpuCopy8
	ldrb r1, [sp, #0x3b]
	ldr r2, _021DA22C ; =UNK04_0220C0AC
	add r0, r4, #0x2f
	str r1, [sp]
	ldrb r3, [sp, #0x3a]
	mov r1, #5
	bl OS_SNPrintf
	add r0, sp, #0x1c
	bl RTC_GetDate
	cmp r0, #0
	bne _021DA0F8
	add r0, sp, #0x2c
	bl RTC_GetTime
	cmp r0, #0
	beq _021DA104
_021DA0F8:
	add sp, sp, #0x8c
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
_021DA104:
	ldr r0, [sp, #0x20]
	ldr r2, _021DA230 ; =UNK04_0220C0B8
	str r0, [sp]
	ldr r1, [sp, #0x24]
	add r0, r4, #0x34
	str r1, [sp, #4]
	ldr r3, [sp, #0x2c]
	mov r1, #0xd
	str r3, [sp, #8]
	ldr r3, [sp, #0x30]
	str r3, [sp, #0xc]
	ldr r3, [sp, #0x34]
	str r3, [sp, #0x10]
	ldr r3, [sp, #0x1c]
	bl OS_SNPrintf
	bl OS_DisableInterrupts
	mov sb, r0
	bl WCM_GetApMacAddress
	mov r8, r0
	mov r1, #6
	bl DC_InvalidateRange
	cmp r8, #0
	bne _021DA174
	mov r0, sb
	bl OS_RestoreInterrupts
	add sp, sp, #0x8c
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
_021DA174:
	add r7, r4, #0x41
	mov r6, #0
	ldr r5, _021DA228 ; =UNK04_0220C0A4
_021DA180:
	ldrb r2, [r8, r6]
	mov r0, r7
	mov r1, r5
	bl OS_SPrintf
	add r6, r6, #1
	cmp r6, #6
	add r7, r7, #2
	blt _021DA180
	bl MOD04_021EBAB8
	mov r3, r0
	ldr r2, _021DA234 ; =UNK04_0220C0D4
	add r0, r4, #0x6f
	mov r1, #0xe
	bl OS_SNPrintf
	add r0, sp, #0x14
	bl WCM_GetApEssid
	mov r5, r0
	mov r1, #0x20
	bl DC_InvalidateRange
	cmp r5, #0
	bne _021DA1E8
	mov r0, sb
	bl OS_RestoreInterrupts
	add sp, sp, #0x8c
	mov r0, #0
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
_021DA1E8:
	mov r0, r5
	add r1, r4, #0x72
	bl MOD04_021EE5F4
	mov r0, r5
	add r1, r4, #0x4e
	mov r2, #0x20
	bl MI_CpuCopy8
	mov r0, sb
	bl OS_RestoreInterrupts
	mov r0, #1
	add sp, sp, #0x8c
	ldmia sp!, {r4, r5, r6, r7, r8, sb, pc}
	.align 2, 0
_021DA218: .word UNK04_0220C094
_021DA21C: .word UNK04_0220C09C
_021DA220: .word 0x027FFE0C
_021DA224: .word 0x027FFE10
_021DA228: .word UNK04_0220C0A4
_021DA22C: .word UNK04_0220C0AC
_021DA230: .word UNK04_0220C0B8
_021DA234: .word UNK04_0220C0D4
	arm_func_end MOD04_021D9F78

	arm_func_start MOD04_021DA238
MOD04_021DA238: ; 0x021DA238
	stmdb sp!, {r4, lr}
	sub sp, sp, #0x18
	mov r4, r0
	add r0, sp, #0
	bl DWCi_BM_GetWiFiInfo
	add r1, sp, #0
	mov r0, r4
	bl MOD04_021D9F78
	add sp, sp, #0x18
	ldmia sp!, {r4, pc}
	arm_func_end MOD04_021DA238

	.section .data

	.global UNK04_0220BFE4
UNK04_0220BFE4: ; 0x0220BFE4
	.asciz "%03d%03d"

	.balign 4, 0
	.global UNK04_0220BFF0
UNK04_0220BFF0: ; 0x0220BFF0
	.asciz "sdkver"

	.balign 4, 0
	.global UNK04_0220BFF8
UNK04_0220BFF8: ; 0x0220BFF8
	.asciz "userid"

	.balign 4, 0
	.global UNK04_0220C000
UNK04_0220C000: ; 0x0220C000
	.asciz "passwd"

	.balign 4, 0
	.global UNK04_0220C008
UNK04_0220C008: ; 0x0220C008
	.asciz "bssid"

	.balign 4, 0
	.global UNK04_0220C010
UNK04_0220C010: ; 0x0220C010
	.asciz "apinfo"

	.balign 4, 0
	.global UNK04_0220C018
UNK04_0220C018: ; 0x0220C018
	.asciz "gamecd"

	.balign 4, 0
	.global UNK04_0220C020
UNK04_0220C020: ; 0x0220C020
	.asciz "makercd"

	.balign 4, 0
	.global UNK04_0220C028
UNK04_0220C028: ; 0x0220C028
	.asciz "unitcd"

	.balign 4, 0
	.global UNK04_0220C030
UNK04_0220C030: ; 0x0220C030
	.asciz "macadr"

	.balign 4, 0
	.global UNK04_0220C038
UNK04_0220C038: ; 0x0220C038
	.asciz "lang"

	.balign 4, 0
	.global UNK04_0220C040
UNK04_0220C040: ; 0x0220C040
	.asciz "birth"

	.balign 4, 0
	.global UNK04_0220C048
UNK04_0220C048: ; 0x0220C048
	.asciz "devtime"

	.balign 4, 0
	.global UNK04_0220C050
UNK04_0220C050: ; 0x0220C050
	.asciz "devname"

	.balign 4, 0
	.global UNK04_0220C058
UNK04_0220C058: ; 0x0220C058
	.asciz "ssid"

	.balign 4, 0
	.global UNK04_0220C060
UNK04_0220C060: ; 0x0220C060
	.asciz "Nitro WiFi SDK/%d.%d"

	.balign 4, 0
	.global UNK04_0220C078
UNK04_0220C078: ; 0x0220C078
	.asciz "User-Agent"

	.balign 4, 0
	.global UNK04_0220C084
UNK04_0220C084: ; 0x0220C084
	.asciz "HTTP_X_GAMECD"

	.balign 4, 0
	.global UNK04_0220C094
UNK04_0220C094: ; 0x0220C094
	.asciz "%013llu"

	.balign 4, 0
	.global UNK04_0220C09C
UNK04_0220C09C: ; 0x0220C09C
	.asciz "%03u"

	.balign 4, 0
	.global UNK04_0220C0A4
UNK04_0220C0A4: ; 0x0220C0A4
	.asciz "%02x"

	.balign 4, 0
	.global UNK04_0220C0AC
UNK04_0220C0AC: ; 0x0220C0AC
	.asciz "%02x%02x"

	.balign 4, 0
	.global UNK04_0220C0B8
UNK04_0220C0B8: ; 0x0220C0B8
	.asciz "%02d%02d%02d%02d%02d%02d"

	.balign 4, 0
	.global UNK_0220C0D4
UNK04_0220C0D4: ; 0x0220C0D4
	.asciz "%02d:0000000-00"

	.balign 4, 0
