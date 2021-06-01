	.include "asm/macros.inc"
	.include "global.inc"
	.extern OSi_ThreadInfo
	.extern __console_exit
    .extern __stdio_exit
    .extern __cs_id
    .extern __cs_ref
    .extern __cs
    .extern __files
    .extern __prep_buffer
    .extern __float_nan
    .extern __float_huge
    .extern __double_huge
    .extern memchr
    .extern __StringRead
    .extern wmemchr

	.section .rodata

UNK_021044A4: ; 0x021044A4
	.short 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007
	.short 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F
	.short 0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017
	.short 0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F
	.short 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027
	.short 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F
	.short 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037
	.short 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F
	.short 0x0040, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067
	.short 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F
	.short 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077
	.short 0x0078, 0x0079, 0x007A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F
	.short 0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067
	.short 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F
	.short 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077
	.short 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F

	.global UNK_02104544
UNK_02104544: ; 0x02104544
	.short 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004
	.short 0x0004, 0x0106, 0x0104, 0x0104, 0x0104, 0x0104, 0x0004, 0x0004
	.short 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004
	.short 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004
	.short 0x0142, 0x00D0, 0x00D0, 0x00D0, 0x00D0, 0x00D0, 0x00D0, 0x00D0
	.short 0x00D0, 0x00D0, 0x00D0, 0x00D0, 0x00D0, 0x00D0, 0x00D0, 0x00D0
	.short 0x0458, 0x0458, 0x0458, 0x0458, 0x0458, 0x0458, 0x0458, 0x0458
	.short 0x0458, 0x0458, 0x00D0, 0x00D0, 0x00D0, 0x00D0, 0x00D0, 0x00D0
	.short 0x00D0, 0x0651, 0x0651, 0x0651, 0x0651, 0x0651, 0x0651, 0x0251
	.short 0x0251, 0x0251, 0x0251, 0x0251, 0x0251, 0x0251, 0x0251, 0x0251
	.short 0x0251, 0x0251, 0x0251, 0x0251, 0x0251, 0x0251, 0x0251, 0x0251
	.short 0x0251, 0x0251, 0x0251, 0x00D0, 0x00D0, 0x00D0, 0x00D0, 0x00D0
	.short 0x00D0, 0x0471, 0x0471, 0x0471, 0x0471, 0x0471, 0x0471, 0x0071
	.short 0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071
	.short 0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071, 0x0071
	.short 0x0071, 0x0071, 0x0071, 0x00D0, 0x00D0, 0x00D0, 0x00D0, 0x0004
	.short 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007
	.short 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E, 0x000F
	.short 0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0017
	.short 0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F
	.short 0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027
	.short 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F
	.short 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037
	.short 0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F
	.short 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047
	.short 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F
	.short 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057
	.short 0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F
	.short 0x0060, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047
	.short 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F
	.short 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057
	.short 0x0058, 0x0059, 0x005A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F

	.global UNK_02104744
UNK_02104744: ; 0x02104744
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x03, 0xB8, 0xE2, 0x3F

	.global UNK_02104754
UNK_02104754: ; 0x02104754
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x3F

	.global UNK_02104764
UNK_02104764: ; 0x02104764
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xD0, 0xCF, 0x43, 0xEB, 0xFD, 0x4C, 0x3E

	.section .data

	.balign 4, 0

	.global UNK_02106DE4
UNK_02106DE4: ; 0x02106DE4
	.byte 0x30, 0x00, 0x78, 0x00, 0x30, 0x00, 0x70, 0x00, 0x30, 0x00, 0x00, 0x00

	.global UNK_02106DF0
UNK_02106DF0: ; 0x02106DF0
	.byte 0x2D, 0x00, 0x49, 0x00, 0x4E, 0x00, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_02106DFC
UNK_02106DFC: ; 0x02106DFC
	.byte 0x2D, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_02106E08
UNK_02106E08: ; 0x02106E08
	.byte 0x49, 0x00, 0x4E, 0x00, 0x46, 0x00, 0x00, 0x00

	.global UNK_02106E10
UNK_02106E10: ; 0x02106E10
	.byte 0x69, 0x00, 0x6E, 0x00, 0x66, 0x00, 0x00, 0x00

	.global UNK_02106E18
UNK_02106E18: ; 0x02106E18
	.byte 0x2D, 0x00, 0x4E, 0x00, 0x41, 0x00, 0x4E, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_02106E24
UNK_02106E24: ; 0x02106E24
	.byte 0x2D, 0x00, 0x6E, 0x00, 0x61, 0x00, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00

	.global UNK_02106E30
UNK_02106E30: ; 0x02106E30
	.byte 0x4E, 0x00, 0x41, 0x00, 0x4E, 0x00, 0x00, 0x00

	.global UNK_02106E38
UNK_02106E38: ; 0x02106E38
	.byte 0x6E, 0x00, 0x61, 0x00, 0x6E, 0x00, 0x00, 0x00

	.global UNK_02106E40
UNK_02106E40: ; 0x02106E40
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_02106E44
UNK_02106E44: ; 0x02106E44
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_02106E48
UNK_02106E48: ; 0x02106E48
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x59, 0x40
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x8F, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xC3, 0x40
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x6A, 0xF8, 0x40, 0x00, 0x00, 0x00, 0x00, 0x80, 0x84, 0x2E, 0x41
	.byte 0x00, 0x00, 0x00, 0x00, 0xD0, 0x12, 0x63, 0x41, 0x00, 0x00, 0x00, 0x00, 0x84, 0xD7, 0x97, 0x41

	.global UNK_02106E88
UNK_02106E88: ; 0x02106E88
	.asciz "542101086242752217003726400434970855712890625"

	.balign 4, 0
	.global UNK_02106EB8
UNK_02106EB8: ; 0x02106EB8
	.asciz "11102230246251565404236316680908203125"

	.balign 4, 0
	.global UNK_02106EE0
UNK_02106EE0: ; 0x02106EE0
	.asciz "23283064365386962890625"

	.balign 4, 0
	.global UNK_02106EF8
UNK_02106EF8: ; 0x02106EF8
	.asciz "152587890625"

	.balign 4, 0
	.global UNK_02106F08
UNK_02106F08: ; 0x02106F08
	.asciz "390625"

	.balign 4, 0
	.global UNK_02106F10
UNK_02106F10: ; 0x02106F10
	.asciz "78125"

	.balign 4, 0
	.global UNK_02106F18
UNK_02106F18: ; 0x02106F18
	.asciz "15625"

	.balign 4, 0
	.global UNK_02106F20
UNK_02106F20: ; 0x02106F20
	.asciz "3125"

	.balign 4, 0
	.global UNK_02106F28
UNK_02106F28: ; 0x02106F28
	.asciz "625"

	.balign 4, 0
	.global UNK_02106F2C
UNK_02106F2C: ; 0x02106F2C
	.asciz "125"

	.balign 4, 0
	.global UNK_02106F30
UNK_02106F30: ; 0x02106F30
	.asciz "25"

	.balign 4, 0
	.global UNK_02106F34
UNK_02106F34: ; 0x02106F34
	.asciz "5"

	.balign 4, 0
	.global UNK_02106F38
UNK_02106F38: ; 0x02106F38
	.asciz "1"

	.balign 4, 0
	.global UNK_02106F3C
UNK_02106F3C: ; 0x02106F3C
	.asciz "2"

	.balign 4, 0
	.global UNK_02106F40
UNK_02106F40: ; 0x02106F40
	.asciz "4"

	.balign 4, 0
	.global UNK_02106F44
UNK_02106F44: ; 0x02106F44
	.asciz "8"

	.balign 4, 0
	.global UNK_02106F48
UNK_02106F48: ; 0x02106F48
	.asciz "16"

	.balign 4, 0
	.global UNK_02106F4C
UNK_02106F4C: ; 0x02106F4C
	.asciz "32"

	.balign 4, 0
	.global UNK_02106F50
UNK_02106F50: ; 0x02106F50
	.asciz "64"

	.balign 4, 0
	.global UNK_02106F54
UNK_02106F54: ; 0x02106F54
	.asciz "128"

	.balign 4, 0
	.global UNK_02106F58
UNK_02106F58: ; 0x02106F58
	.asciz "256"

	.balign 4, 0
	.global UNK_02106F5C
UNK_02106F5C: ; 0x02106F5C
	.asciz "179769313486231580793728714053034151"

	.section .text
	.balign 4, 0

	arm_func_start parse_format_wprintf
parse_format_wprintf: ; 0x020E50A0
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x10
	ldrh r3, [r0, #0x2]
	mov r4, #0x0
	mov r5, #0x1
	mov lr, r2
	strb r5, [sp, #0x0]
	strb r4, [sp, #0x1]
	strb r4, [sp, #0x2]
	strb r4, [sp, #0x3]
	strb r4, [sp, #0x4]
	str r4, [sp, #0x8]
	str r4, [sp, #0xc]
	cmp r3, #0x25
	add r12, r0, #0x2
	bne _020E50FC
	add r0, sp, #0x0
	strh r3, [sp, #0x6]
	ldmia r0, {r0-r3}
	stmia lr, {r0-r3}
	add sp, sp, #0x10
	add r0, r12, #0x2
	ldmia sp!, {r4-r8,pc}
_020E50FC:
	mov r2, #0x2
	mov r0, r4
	mov r5, r2
	mov r6, r4
	mov r7, #0x1
_020E5110:
	mov r8, r7
	cmp r3, #0x2b
	bgt _020E5140
	bge _020E5168
	cmp r3, #0x23
	bgt _020E5198
	cmp r3, #0x20
	blt _020E5198
	beq _020E5170
	cmp r3, #0x23
	beq _020E5180
	b _020E5198
_020E5140:
	cmp r3, #0x30
	bgt _020E5198
	cmp r3, #0x2d
	blt _020E5198
	beq _020E5160
	cmp r3, #0x30
	beq _020E5188
	b _020E5198
_020E5160:
	strb r6, [sp, #0x0]
	b _020E519C
_020E5168:
	strb r7, [sp, #0x1]
	b _020E519C
_020E5170:
	ldrb r4, [sp, #0x1]
	cmp r4, #0x1
	strneb r5, [sp, #0x1]
	b _020E519C
_020E5180:
	strb r7, [sp, #0x3]
	b _020E519C
_020E5188:
	ldrb r4, [sp, #0x0]
	cmp r4, #0x0
	strneb r2, [sp, #0x0]
	b _020E519C
_020E5198:
	mov r8, r0
_020E519C:
	cmp r8, #0x0
	ldrneh r3, [r12, #0x2]!
	bne _020E5110
	cmp r3, #0x2a
	bne _020E51E4
	ldr r0, [r1, #0x0]
	add r0, r0, #0x4
	str r0, [r1, #0x0]
	ldr r0, [r0, #-0x4]
	str r0, [sp, #0x8]
	cmp r0, #0x0
	bge _020E51DC
	rsb r0, r0, #0x0
	mov r2, #0x0
	strb r2, [sp, #0x0]
	str r0, [sp, #0x8]
_020E51DC:
	ldrh r3, [r12, #0x2]!
	b _020E5228
_020E51E4:
	mov r2, #0x0
	ldr r5, _020E560C ; =UNK_02104544
	mov r0, #0xa
	b _020E5208
_020E51F4:
	ldr r4, [sp, #0x8]
	sub r3, r3, #0x30
	mla r6, r4, r0, r3
	ldrh r3, [r12, #0x2]!
	str r6, [sp, #0x8]
_020E5208:
	cmp r3, #0x80
	movcs r4, r2
	bhs _020E5220
	mov r4, r3, lsl #0x1
	ldrh r4, [r5, r4]
	and r4, r4, #0x8
_020E5220:
	cmp r4, #0x0
	bne _020E51F4
_020E5228:
	ldr r2, [sp, #0x8]
	ldr r0, _020E5610 ; =0x000001FD
	cmp r2, r0
	ble _020E5258
	ldr r1, _020E5614 ; =0x0000FFFF
	add r0, sp, #0x0
	strh r1, [sp, #0x6]
	ldmia r0, {r0-r3}
	stmia lr, {r0-r3}
	add sp, sp, #0x10
	add r0, r12, #0x2
	ldmia sp!, {r4-r8,pc}
_020E5258:
	cmp r3, #0x2e
	bne _020E52E0
	ldrh r3, [r12, #0x2]!
	mov r0, #0x1
	strb r0, [sp, #0x2]
	cmp r3, #0x2a
	bne _020E529C
	ldr r0, [r1, #0x0]
	add r0, r0, #0x4
	str r0, [r1, #0x0]
	ldr r0, [r0, #-0x4]
	ldrh r3, [r12, #0x2]!
	str r0, [sp, #0xc]
	cmp r0, #0x0
	movlt r0, #0x0
	strltb r0, [sp, #0x2]
	b _020E52E0
_020E529C:
	mov r1, #0x0
	ldr r4, _020E560C ; =UNK_02104544
	mov r0, #0xa
	b _020E52C0
_020E52AC:
	ldr r2, [sp, #0xc]
	sub r3, r3, #0x30
	mla r5, r2, r0, r3
	ldrh r3, [r12, #0x2]!
	str r5, [sp, #0xc]
_020E52C0:
	cmp r3, #0x80
	movcs r2, r1
	bhs _020E52D8
	mov r2, r3, lsl #0x1
	ldrh r2, [r4, r2]
	and r2, r2, #0x8
_020E52D8:
	cmp r2, #0x0
	bne _020E52AC
_020E52E0:
	cmp r3, #0x6c
	mov r0, #0x1
	bgt _020E5318
	cmp r3, #0x68
	blt _020E530C
	beq _020E5334
	cmp r3, #0x6a
	beq _020E5380
	cmp r3, #0x6c
	beq _020E5350
	b _020E53A4
_020E530C:
	cmp r3, #0x4c
	beq _020E5374
	b _020E53A4
_020E5318:
	cmp r3, #0x74
	bgt _020E5328
	beq _020E538C
	b _020E53A4
_020E5328:
	cmp r3, #0x7a
	beq _020E5398
	b _020E53A4
_020E5334:
	ldrh r1, [r12, #0x2]
	mov r2, #0x2
	strb r2, [sp, #0x4]
	cmp r1, #0x68
	streqb r0, [sp, #0x4]
	ldreqh r3, [r12, #0x2]!
	b _020E53A8
_020E5350:
	ldrh r1, [r12, #0x2]
	mov r2, #0x3
	strb r2, [sp, #0x4]
	cmp r1, #0x6c
	bne _020E53A8
	mov r1, #0x4
	strb r1, [sp, #0x4]
	ldrh r3, [r12, #0x2]!
	b _020E53A8
_020E5374:
	mov r1, #0x9
	strb r1, [sp, #0x4]
	b _020E53A8
_020E5380:
	mov r1, #0x6
	strb r1, [sp, #0x4]
	b _020E53A8
_020E538C:
	mov r1, #0x8
	strb r1, [sp, #0x4]
	b _020E53A8
_020E5398:
	mov r1, #0x7
	strb r1, [sp, #0x4]
	b _020E53A8
_020E53A4:
	mov r0, #0x0
_020E53A8:
	cmp r0, #0x0
	ldrneh r3, [r12, #0x2]!
	strh r3, [sp, #0x6]
	cmp r3, #0x61
	bgt _020E53FC
	bge _020E54E0
	cmp r3, #0x47
	bgt _020E53F0
	subs r0, r3, #0x41
	addpl pc, pc, r0, lsl #0x2
	b _020E55EC
	b _020E54E0
	b _020E55EC
	b _020E55EC
	b _020E55EC
	b _020E5528
	b _020E54A8
	b _020E5518
_020E53F0:
	cmp r3, #0x58
	beq _020E5470
	b _020E55EC
_020E53FC:
	cmp r3, #0x63
	bgt _020E540C
	beq _020E5588
	b _020E55EC
_020E540C:
	sub r0, r3, #0x64
	cmp r0, #0x14
	addls pc, pc, r0, lsl #0x2
	b _020E55EC
	b _020E5470 ; case
	b _020E5528 ; case
	b _020E54A8 ; case
	b _020E5518 ; case
	b _020E55EC ; case
	b _020E5470 ; case
	b _020E55EC ; case
	b _020E55EC ; case
	b _020E55EC ; case
	b _020E55EC ; case
	b _020E55D8 ; case
	b _020E5470 ; case
	b _020E5564 ; case
	b _020E55EC ; case
	b _020E55EC ; case
	b _020E55B4 ; case
	b _020E55EC ; case
	b _020E5470 ; case
	b _020E55EC ; case
	b _020E55EC ; case
	b _020E5470 ; case
_020E5470:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x9
	moveq r0, #0x4
	streqb r0, [sp, #0x4]
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	moveq r0, #0x1
	streq r0, [sp, #0xc]
	beq _020E55F4
	ldrb r0, [sp, #0x0]
	cmp r0, #0x2
	moveq r0, #0x1
	streqb r0, [sp, #0x0]
	b _020E55F4
_020E54A8:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x2
	cmpne r0, #0x6
	cmpne r0, #0x7
	cmpne r0, #0x8
	cmpne r0, #0x4
	ldreq r0, _020E5614 ; =0x0000FFFF
	streqh r0, [sp, #0x6]
	beq _020E55F4
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	moveq r0, #0x6
	streq r0, [sp, #0xc]
	b _020E55F4
_020E54E0:
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	moveq r0, #0xd
	streq r0, [sp, #0xc]
	ldrb r0, [sp, #0x4]
	cmp r0, #0x2
	cmpne r0, #0x6
	cmpne r0, #0x7
	cmpne r0, #0x8
	cmpne r0, #0x4
	cmpne r0, #0x1
	ldreq r0, _020E5614 ; =0x0000FFFF
	streqh r0, [sp, #0x6]
	b _020E55F4
_020E5518:
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	moveq r0, #0x1
	streq r0, [sp, #0xc]
_020E5528:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x2
	cmpne r0, #0x6
	cmpne r0, #0x7
	cmpne r0, #0x8
	cmpne r0, #0x4
	cmpne r0, #0x1
	ldreq r0, _020E5614 ; =0x0000FFFF
	streqh r0, [sp, #0x6]
	beq _020E55F4
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	moveq r0, #0x6
	streq r0, [sp, #0xc]
	b _020E55F4
_020E5564:
	mov r3, #0x3
	mov r2, #0x1
	mov r1, #0x78
	mov r0, #0x8
	strb r3, [sp, #0x4]
	strb r2, [sp, #0x3]
	strh r1, [sp, #0x6]
	str r0, [sp, #0xc]
	b _020E55F4
_020E5588:
	ldrb r1, [sp, #0x4]
	cmp r1, #0x3
	moveq r0, #0x5
	streqb r0, [sp, #0x4]
	beq _020E55F4
	ldrb r0, [sp, #0x2]
	cmp r0, #0x0
	cmpeq r1, #0x0
	ldrne r0, _020E5614 ; =0x0000FFFF
	strneh r0, [sp, #0x6]
	b _020E55F4
_020E55B4:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x3
	moveq r0, #0x5
	streqb r0, [sp, #0x4]
	beq _020E55F4
	cmp r0, #0x0
	ldrne r0, _020E5614 ; =0x0000FFFF
	strneh r0, [sp, #0x6]
	b _020E55F4
_020E55D8:
	ldrb r0, [sp, #0x4]
	cmp r0, #0x9
	moveq r0, #0x4
	streqb r0, [sp, #0x4]
	b _020E55F4
_020E55EC:
	ldr r0, _020E5614 ; =0x0000FFFF
	strh r0, [sp, #0x6]
_020E55F4:
	add r0, sp, #0x0
	ldmia r0, {r0-r3}
	stmia lr, {r0-r3}
	add r0, r12, #0x2
	add sp, sp, #0x10
	ldmia sp!, {r4-r8,pc}
	.balign 4
_020E560C: .word UNK_02104544
_020E5610: .word 0x000001FD
_020E5614: .word 0x0000FFFF

	arm_func_start long2str_wide
long2str_wide: ; 0x020E5618
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x10
	movs r10, r0
	mov r0, #0x0
	mov r5, r1
	str r0, [sp, #0xc]
	ldr r7, [sp, #0x4c]
	mov r6, r0
	strh r0, [r5, #-0x2]!
	ldrb r0, [sp, #0x43]
	str r1, [sp, #0x0]
	ldrh r8, [sp, #0x46]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x48]
	ldrb r11, [sp, #0x41]
	str r0, [sp, #0x8]
	cmpeq r7, #0x0
	bne _020E568C
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020E5678
	cmp r8, #0x6f
	beq _020E568C
_020E5678:
	add sp, sp, #0x10
	mov r0, r5
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E568C:
	cmp r8, #0x69
	bgt _020E56B4
	bge _020E56E8
	cmp r8, #0x58
	bgt _020E56A8
	beq _020E5714
	b _020E571C
_020E56A8:
	cmp r8, #0x64
	beq _020E56E8
	b _020E571C
_020E56B4:
	cmp r8, #0x6f
	bgt _020E56C8
	moveq r4, #0x8
	moveq r11, #0x0
	b _020E571C
_020E56C8:
	cmp r8, #0x78
	bgt _020E571C
	cmp r8, #0x75
	blt _020E571C
	beq _020E5708
	cmp r8, #0x78
	beq _020E5714
	b _020E571C
_020E56E8:
	cmp r10, #0x0
	mov r4, #0xa
	bge _020E571C
	mov r0, #0x1
	cmp r10, #0x80000000
	rsbne r10, r10, #0x0
	str r0, [sp, #0xc]
	b _020E571C
_020E5708:
	mov r4, #0xa
	mov r11, #0x0
	b _020E571C
_020E5714:
	mov r4, #0x10
	mov r11, #0x0
_020E571C:
	mov r0, r10
	mov r1, r4
	bl _u32_div_f
	mov r9, r1
	mov r0, r10
	mov r1, r4
	bl _u32_div_f
	cmp r9, #0xa
	mov r10, r0
	addlt r9, r9, #0x30
	blt _020E5754
	cmp r8, #0x78
	addeq r9, r9, #0x57
	addne r9, r9, #0x37
_020E5754:
	cmp r10, #0x0
	strh r9, [r5, #-0x2]!
	add r6, r6, #0x1
	bne _020E571C
	cmp r4, #0x8
	bne _020E5788
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ldrneh r0, [r5, #0x0]
	cmpne r0, #0x30
	movne r0, #0x30
	strneh r0, [r5, #-0x2]!
	addne r6, r6, #0x1
_020E5788:
	ldrb r0, [sp, #0x40]
	cmp r0, #0x2
	bne _020E57BC
	ldr r0, [sp, #0xc]
	ldr r7, [sp, #0x8]
	cmp r0, #0x0
	cmpeq r11, #0x0
	subne r7, r7, #0x1
	cmp r4, #0x10
	bne _020E57BC
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	subne r7, r7, #0x2
_020E57BC:
	ldr r0, [sp, #0x0]
	ldr r1, _020E5864 ; =0x000001FD
	sub r0, r0, r5
	add r0, r0, r0, lsr #0x1f
	add r0, r7, r0, asr #0x1
	cmp r0, r1
	addgt sp, sp, #0x10
	movgt r0, #0x0
	ldmgtia sp!, {r3-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	cmp r6, r7
	bge _020E5804
	mov r0, #0x30
_020E57F4:
	add r6, r6, #0x1
	cmp r6, r7
	strh r0, [r5, #-0x2]!
	blt _020E57F4
_020E5804:
	cmp r4, #0x10
	bne _020E5820
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	movne r0, #0x30
	strneh r8, [r5, #-0x2]
	strneh r0, [r5, #-0x4]!
_020E5820:
	ldr r0, [sp, #0xc]
	cmp r0, #0x0
	movne r0, #0x2d
	strneh r0, [r5, #-0x2]!
	bne _020E5850
	cmp r11, #0x1
	moveq r0, #0x2b
	streqh r0, [r5, #-0x2]!
	beq _020E5850
	cmp r11, #0x2
	moveq r0, #0x20
	streqh r0, [r5, #-0x2]!
_020E5850:
	mov r0, r5
	add sp, sp, #0x10
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E5864: .word 0x000001FD

	arm_func_start longlong2str_wide
longlong2str_wide: ; 0x020E5868
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x18
	mov r9, r1
	mov r1, #0x0
	mov r10, r0
	mov r6, r2
	mov r0, r1
	strh r0, [r6, #-0x2]!
	ldr r0, [sp, #0x58]
	cmp r9, #0x0
	str r0, [sp, #0x10]
	ldrb r0, [sp, #0x4f]
	cmpeq r10, #0x0
	str r2, [sp, #0x0]
	str r0, [sp, #0x4]
	ldr r0, [sp, #0x54]
	str r1, [sp, #0x14]
	str r0, [sp, #0x8]
	ldrb r0, [sp, #0x4d]
	mov r7, r1
	ldrh r8, [sp, #0x52]
	str r0, [sp, #0xc]
	ldreq r0, [sp, #0x10]
	cmpeq r0, #0x0
	bne _020E58F8
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020E58E4
	cmp r8, #0x6f
	beq _020E58F8
_020E58E4:
	add sp, sp, #0x18
	mov r0, r6
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E58F8:
	cmp r8, #0x69
	bgt _020E5920
	bge _020E5950
	cmp r8, #0x58
	bgt _020E5914
	beq _020E59A4
	b _020E59B0
_020E5914:
	cmp r8, #0x64
	beq _020E5950
	b _020E59B0
_020E5920:
	cmp r8, #0x6f
	bgt _020E5930
	beq _020E5984
	b _020E59B0
_020E5930:
	cmp r8, #0x78
	bgt _020E59B0
	cmp r8, #0x75
	blt _020E59B0
	beq _020E5994
	cmp r8, #0x78
	beq _020E59A4
	b _020E59B0
_020E5950:
	subs r0, r10, #0x0
	sbcs r0, r9, #0x0
	mov r11, #0xa
	mov r5, #0x0
	bge _020E59B0
	cmp r9, #0x80000000
	cmpeq r10, r5
	beq _020E5978
	rsbs r10, r10, #0x0
	rsc r9, r9, #0x0
_020E5978:
	mov r0, #0x1
	str r0, [sp, #0x14]
	b _020E59B0
_020E5984:
	mov r5, #0x0
	str r5, [sp, #0xc]
	mov r11, #0x8
	b _020E59B0
_020E5994:
	mov r5, #0x0
	str r5, [sp, #0xc]
	mov r11, #0xa
	b _020E59B0
_020E59A4:
	mov r5, #0x0
	str r5, [sp, #0xc]
	mov r11, #0x10
_020E59B0:
	mov r0, r10
	mov r1, r9
	mov r2, r11
	mov r3, r5
	bl _ull_mod
	mov r4, r0
	mov r0, r10
	mov r1, r9
	mov r2, r11
	mov r3, r5
	bl _ll_udiv
	mov r10, r0
	cmp r4, #0xa
	mov r9, r1
	addlt r0, r4, #0x30
	blt _020E59FC
	cmp r8, #0x78
	addeq r0, r4, #0x57
	addne r0, r4, #0x37
_020E59FC:
	strh r0, [r6, #-0x2]!
	mov r0, #0x0
	cmp r9, r0
	cmpeq r10, r0
	add r7, r7, #0x1
	bne _020E59B0
	cmp r5, #0x0
	cmpeq r11, #0x8
	bne _020E5A3C
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ldrneh r0, [r6, #0x0]
	cmpne r0, #0x30
	movne r0, #0x30
	strneh r0, [r6, #-0x2]!
	addne r7, r7, #0x1
_020E5A3C:
	ldrb r0, [sp, #0x4c]
	cmp r0, #0x2
	bne _020E5A8C
	ldr r0, [sp, #0x8]
	str r0, [sp, #0x10]
	ldr r0, [sp, #0x14]
	cmp r0, #0x0
	ldreq r0, [sp, #0xc]
	cmpeq r0, #0x0
	ldrne r0, [sp, #0x10]
	subne r0, r0, #0x1
	strne r0, [sp, #0x10]
	cmp r5, #0x0
	cmpeq r11, #0x10
	bne _020E5A8C
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	ldrne r0, [sp, #0x10]
	subne r0, r0, #0x2
	strne r0, [sp, #0x10]
_020E5A8C:
	ldr r0, [sp, #0x0]
	ldr r2, _020E5B48 ; =0x000001FD
	sub r0, r0, r6
	add r1, r0, r0, lsr #0x1f
	ldr r0, [sp, #0x10]
	add r0, r0, r1, asr #0x1
	cmp r0, r2
	addgt sp, sp, #0x18
	movgt r0, #0x0
	ldmgtia sp!, {r3-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	ldr r0, [sp, #0x10]
	cmp r7, r0
	bge _020E5AE0
	mov r1, #0x30
_020E5ACC:
	ldr r0, [sp, #0x10]
	add r7, r7, #0x1
	cmp r7, r0
	strh r1, [r6, #-0x2]!
	blt _020E5ACC
_020E5AE0:
	cmp r5, #0x0
	cmpeq r11, #0x10
	bne _020E5B00
	ldr r0, [sp, #0x4]
	cmp r0, #0x0
	movne r0, #0x30
	strneh r8, [r6, #-0x2]
	strneh r0, [r6, #-0x4]!
_020E5B00:
	ldr r0, [sp, #0x14]
	cmp r0, #0x0
	movne r0, #0x2d
	strneh r0, [r6, #-0x2]!
	bne _020E5B34
	ldr r0, [sp, #0xc]
	cmp r0, #0x1
	moveq r0, #0x2b
	streqh r0, [r6, #-0x2]!
	beq _020E5B34
	cmp r0, #0x2
	moveq r0, #0x20
	streqh r0, [r6, #-0x2]!
_020E5B34:
	mov r0, r6
	add sp, sp, #0x18
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E5B48: .word 0x000001FD

	arm_func_start double2hex_wide
double2hex_wide: ; 0x020E5B4C
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3-r10,lr}
	sub sp, sp, #0x44
	ldr r7, [sp, #0x80]
	ldr r0, _020E5EB8 ; =0x000001FD
	mov r8, r2
	cmp r7, r0
	ldrh r6, [sp, #0x7a]
	ldrb r5, [sp, #0x77]
	ldrb r4, [sp, #0x75]
	ldr r1, [sp, #0x68]
	ldr r2, [sp, #0x6c]
	addgt sp, sp, #0x44
	movgt r0, #0x0
	ldmgtia sp!, {r3-r10,lr}
	addgt sp, sp, #0x10
	bxgt lr
	mov r10, #0x0
	mov r9, #0x20
	add r0, sp, #0x8
	add r3, sp, #0xc
	strb r10, [sp, #0x8]
	strh r9, [sp, #0xa]
	bl __num2dec_internal2
	ldr r0, [sp, #0x68]
	ldr r1, [sp, #0x6c]
	bl fabs
	mov r2, r0
	mov r0, r10
	mov r3, r1
	mov r1, r0
	bl _deq
	bne _020E5BF4
	sub r4, r8, #0xc
	ldr r1, _020E5EBC ; =UNK_02106DE4
	mov r0, r4
	bl wcscpy
	add sp, sp, #0x44
	mov r0, r4
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E5BF4:
	ldrb r0, [sp, #0x11]
	cmp r0, #0x49
	bne _020E5C74
	ldrsb r0, [sp, #0xc]
	cmp r0, #0x0
	beq _020E5C38
	cmp r6, #0x41
	sub r4, r8, #0xa
	bne _020E5C28
	ldr r1, _020E5EC0 ; =UNK_02106DF0
	mov r0, r4
	bl wcscpy
	b _020E5C60
_020E5C28:
	ldr r1, _020E5EC4 ; =UNK_02106DFC
	mov r0, r4
	bl wcscpy
	b _020E5C60
_020E5C38:
	cmp r6, #0x41
	sub r4, r8, #0x8
	bne _020E5C54
	ldr r1, _020E5EC8 ; =UNK_02106E08
	mov r0, r4
	bl wcscpy
	b _020E5C60
_020E5C54:
	ldr r1, _020E5ECC ; =UNK_02106E10
	mov r0, r4
	bl wcscpy
_020E5C60:
	add sp, sp, #0x44
	mov r0, r4
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E5C74:
	cmp r0, #0x4e
	bne _020E5CF0
	ldrsb r0, [sp, #0xc]
	cmp r0, #0x0
	beq _020E5CB4
	cmp r6, #0x41
	sub r4, r8, #0xa
	bne _020E5CA4
	ldr r1, _020E5ED0 ; =UNK_02106E18
	mov r0, r4
	bl wcscpy
	b _020E5CDC
_020E5CA4:
	ldr r1, _020E5ED4 ; =UNK_02106E24
	mov r0, r4
	bl wcscpy
	b _020E5CDC
_020E5CB4:
	cmp r6, #0x41
	sub r4, r8, #0x8
	bne _020E5CD0
	ldr r1, _020E5ED8 ; =UNK_02106E30
	mov r0, r4
	bl wcscpy
	b _020E5CDC
_020E5CD0:
	ldr r1, _020E5EDC ; =UNK_02106E38
	mov r0, r4
	bl wcscpy
_020E5CDC:
	add sp, sp, #0x44
	mov r0, r4
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
_020E5CF0:
	mov r3, r10
	mov r1, #0x1
	mov r0, #0x64
	add r9, sp, #0x68
	strb r1, [sp, #0x34]
	strb r1, [sp, #0x35]
	strb r3, [sp, #0x36]
	strb r3, [sp, #0x37]
	strb r3, [sp, #0x38]
	str r3, [sp, #0x3c]
	str r1, [sp, #0x40]
	strh r0, [sp, #0x3a]
_020E5D20:
	rsb r1, r3, #0x7
	ldrsb r2, [r9, r3]
	ldrsb r0, [r9, r1]
	strb r0, [r9, r3]
	add r3, r3, #0x1
	strb r2, [r9, r1]
	cmp r3, #0x4
	blt _020E5D20
	ldrb r0, [sp, #0x69]
	ldrb r1, [sp, #0x68]
	ldr sb, _020E5EE0 ; =0x000007FF
	mov r0, r0, lsl #0x11
	orr r1, r0, r1, lsl #0x19
	add r0, sp, #0x34
	and lr, r9, r1, lsr #0x15
	sub r12, sp, #0x8
	ldmia r0, {r0-r3}
	stmia r12, {r0-r3}
	rsb r0, r9, #0x400
	mov r1, r8
	add r0, lr, r0
	ldmia r12, {r2-r3}
	bl long2str_wide
	cmp r6, #0x61
	moveq r1, #0x70
	movne r1, #0x50
	strh r1, [r0, #-0x2]!
	mov r1, r7, lsl #0x2
	mov lr, r7
	cmp r7, #0x1
	add r8, r1, #0xb
	add r12, sp, #0x68
	blt _020E5E30
	mov r9, #0x30
_020E5DA8:
	cmp r8, #0x40
	bge _020E5E18
	ldrb r1, [r12, r8, asr #0x3]
	and r2, r8, #0x7
	rsb r3, r2, #0x7
	mov r2, r1, asr r3
	sub r10, r8, #0x4
	bic r1, r8, #0x7
	bic r10, r10, #0x7
	cmp r1, r10
	add r10, r12, r8, asr #0x3
	and r1, r2, #0xff
	beq _020E5DEC
	ldrb r2, [r10, #-0x1]
	mov r2, r2, lsl #0x8
	orr r1, r1, r2, asr r3
	and r1, r1, #0xff
_020E5DEC:
	and r1, r1, #0xf
	cmp r1, #0xa
	addcc r1, r1, #0x30
	andcc r1, r1, #0xff
	blo _020E5E1C
	cmp r6, #0x61
	addeq r1, r1, #0x57
	andeq r1, r1, #0xff
	addne r1, r1, #0x37
	andne r1, r1, #0xff
	b _020E5E1C
_020E5E18:
	mov r1, r9
_020E5E1C:
	sub lr, lr, #0x1
	cmp lr, #0x1
	strh r1, [r0, #-0x2]!
	sub r8, r8, #0x4
	bge _020E5DA8
_020E5E30:
	cmp r7, #0x0
	cmpeq r5, #0x0
	movne r1, #0x2e
	strneh r1, [r0, #-0x2]!
	mov r1, #0x31
	strh r1, [r0, #-0x2]
	cmp r6, #0x61
	moveq r1, #0x78
	movne r1, #0x58
	strh r1, [r0, #-0x4]!
	mov r1, #0x30
	strh r1, [r0, #-0x2]!
	ldrsb r1, [sp, #0xc]
	cmp r1, #0x0
	movne r1, #0x2d
	strneh r1, [r0, #-0x2]!
	addne sp, sp, #0x44
	ldmneia sp!, {r3-r10,lr}
	addne sp, sp, #0x10
	bxne lr
	cmp r4, #0x1
	moveq r1, #0x2b
	streqh r1, [r0, #-0x2]!
	addeq sp, sp, #0x44
	ldmeqia sp!, {r3-r10,lr}
	addeq sp, sp, #0x10
	bxeq lr
	cmp r4, #0x2
	moveq r1, #0x20
	streqh r1, [r0, #-0x2]!
	add sp, sp, #0x44
	ldmia sp!, {r3-r10,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E5EB8: .word 0x000001FD
_020E5EBC: .word UNK_02106DE4
_020E5EC0: .word UNK_02106DF0
_020E5EC4: .word UNK_02106DFC
_020E5EC8: .word UNK_02106E08
_020E5ECC: .word UNK_02106E10
_020E5ED0: .word UNK_02106E18
_020E5ED4: .word UNK_02106E24
_020E5ED8: .word UNK_02106E30
_020E5EDC: .word UNK_02106E38
_020E5EE0: .word 0x000007FF

	arm_func_start round_decimal_wide
round_decimal_wide: ; 0x020E5EE4
	stmdb sp!, {r4,lr}
	cmp r1, #0x0
	bge _020E5F0C
_020E5EF0:
	mov r1, #0x0
	strh r1, [r0, #0x2]
	mov r1, #0x1
	strb r1, [r0, #0x4]
	mov r1, #0x30
	strb r1, [r0, #0x5]
	ldmia sp!, {r4,pc}
_020E5F0C:
	ldrb lr, [r0, #0x4]
	cmp r1, lr
	ldmgeia sp!, {r4,pc}
	add r12, r0, #0x5
	add r2, r12, r1
	add r2, r2, #0x1
	ldrsb r3, [r2, #-0x1]!
	sub r3, r3, #0x30
	mov r3, r3, lsl #0x18
	mov r3, r3, asr #0x18
	cmp r3, #0x5
	bne _020E5F6C
	add r12, r12, lr
_020E5F40:
	sub r12, r12, #0x1
	cmp r12, r2
	bls _020E5F58
	ldrsb r3, [r12, #0x0]
	cmp r3, #0x30
	beq _020E5F40
_020E5F58:
	cmp r12, r2
	ldreqsb r3, [r2, #-0x1]
	andeq r4, r3, #0x1
	movne r4, #0x1
	b _020E5F74
_020E5F6C:
	movgt r4, #0x1
	movle r4, #0x0
_020E5F74:
	cmp r1, #0x0
	beq _020E5FD0
	mov r12, #0x0
	mov lr, #0x1
_020E5F84:
	ldrsb r3, [r2, #-0x1]!
	sub r3, r3, #0x30
	add r3, r3, r4
	mov r3, r3, lsl #0x18
	mov r3, r3, asr #0x18
	cmp r3, #0x9
	movgt r4, lr
	movle r4, r12
	cmp r4, #0x0
	bne _020E5FB4
	cmp r3, #0x0
	bne _020E5FBC
_020E5FB4:
	sub r1, r1, #0x1
	b _020E5FC8
_020E5FBC:
	add r3, r3, #0x30
	strb r3, [r2, #0x0]
	b _020E5FD0
_020E5FC8:
	cmp r1, #0x0
	bne _020E5F84
_020E5FD0:
	cmp r4, #0x0
	beq _020E5FF8
	ldrsh r3, [r0, #0x2]
	mov r2, #0x1
	mov r1, #0x31
	add r3, r3, #0x1
	strh r3, [r0, #0x2]
	strb r2, [r0, #0x4]
	strb r1, [r0, #0x5]
	ldmia sp!, {r4,pc}
_020E5FF8:
	cmp r1, #0x0
	beq _020E5EF0
	strb r1, [r0, #0x4]
	ldmia sp!, {r4,pc}

	arm_func_start float2str_wide
float2str_wide: ; 0x020E6008
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x22c
	mov r10, r0
	add r0, sp, #0x250
	ldr r7, [sp, #0x268]
	ldr r3, _020E6628 ; =0x000001FD
	ldrh r6, [r0, #0x12]
	cmp r7, r3
	ldrb r5, [sp, #0x25f]
	ldrb r4, [sp, #0x25d]
	mov r8, r1
	mov r9, r2
	addgt sp, sp, #0x22c
	movgt r0, #0x0
	ldmgtia sp!, {r4-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	mov r12, #0x0
	mov r11, #0x20
	add r0, sp, #0x0
	add r3, sp, #0x4
	mov r1, r10
	mov r2, r8
	strb r12, [sp, #0x0]
	strh r11, [sp, #0x2]
	bl __num2dec_internal2
	ldrb r0, [sp, #0x8]
	add r1, sp, #0x9
	add r0, r1, r0
	b _020E609C
_020E6084:
	ldrb r2, [sp, #0x8]
	ldrsh r1, [sp, #0x6]
	sub r2, r2, #0x1
	add r1, r1, #0x1
	strb r2, [sp, #0x8]
	strh r1, [sp, #0x6]
_020E609C:
	ldrb r1, [sp, #0x8]
	cmp r1, #0x1
	bls _020E60B4
	ldrsb r1, [r0, #-0x1]!
	cmp r1, #0x30
	beq _020E6084
_020E60B4:
	ldrb r0, [sp, #0x9]
	cmp r0, #0x30
	beq _020E60D4
	cmp r0, #0x49
	beq _020E60E0
	cmp r0, #0x4e
	beq _020E6198
	b _020E6244
_020E60D4:
	mov r0, #0x0
	strh r0, [sp, #0x6]
	b _020E6244
_020E60E0:
	mov r2, #0x0
	mov r0, r10
	mov r1, r8
	mov r3, r2
	bl _dls
	bhs _020E6140
	cmp r6, #0x80
	sub r4, r9, #0xa
	movcs r0, #0x0
	bhs _020E6118
	ldr r0, _020E662C ; =UNK_02104544
	mov r1, r6, lsl #0x1
	ldrh r0, [r0, r1]
	and r0, r0, #0x200
_020E6118:
	cmp r0, #0x0
	beq _020E6130
	ldr r1, _020E6630 ; =UNK_02106DF0
	mov r0, r4
	bl wcscpy
	b _020E6184
_020E6130:
	ldr r1, _020E6634 ; =UNK_02106DFC
	mov r0, r4
	bl wcscpy
	b _020E6184
_020E6140:
	cmp r6, #0x80
	sub r4, r9, #0x8
	movcs r0, #0x0
	bhs _020E6160
	ldr r0, _020E662C ; =UNK_02104544
	mov r1, r6, lsl #0x1
	ldrh r0, [r0, r1]
	and r0, r0, #0x200
_020E6160:
	cmp r0, #0x0
	beq _020E6178
	ldr r1, _020E6638 ; =UNK_02106E08
	mov r0, r4
	bl wcscpy
	b _020E6184
_020E6178:
	ldr r1, _020E663C ; =UNK_02106E10
	mov r0, r4
	bl wcscpy
_020E6184:
	add sp, sp, #0x22c
	mov r0, r4
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E6198:
	ldrsb r0, [sp, #0x4]
	cmp r0, #0x0
	beq _020E61EC
	cmp r6, #0x80
	sub r4, r9, #0xa
	movcs r0, #0x0
	bhs _020E61C4
	ldr r0, _020E662C ; =UNK_02104544
	mov r1, r6, lsl #0x1
	ldrh r0, [r0, r1]
	and r0, r0, #0x200
_020E61C4:
	cmp r0, #0x0
	beq _020E61DC
	ldr r1, _020E6640 ; =UNK_02106E18
	mov r0, r4
	bl wcscpy
	b _020E6230
_020E61DC:
	ldr r1, _020E6644 ; =UNK_02106E24
	mov r0, r4
	bl wcscpy
	b _020E6230
_020E61EC:
	cmp r6, #0x80
	sub r4, r9, #0x8
	movcs r0, #0x0
	bhs _020E620C
	ldr r0, _020E662C ; =UNK_02104544
	mov r1, r6, lsl #0x1
	ldrh r0, [r0, r1]
	and r0, r0, #0x200
_020E620C:
	cmp r0, #0x0
	beq _020E6224
	ldr r1, _020E6648 ; =UNK_02106E30
	mov r0, r4
	bl wcscpy
	b _020E6230
_020E6224:
	ldr r1, _020E664C ; =UNK_02106E38
	mov r0, r4
	bl wcscpy
_020E6230:
	add sp, sp, #0x22c
	mov r0, r4
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E6244:
	ldrb r1, [sp, #0x8]
	ldrsh r2, [sp, #0x6]
	add r0, sp, #0x200
	sub r1, r1, #0x1
	add r0, r0, #0x2a
	add r1, r2, r1
	sub r8, r0, #0x1
	strh r1, [sp, #0x6]
	mov r0, #0x0
	strb r0, [r8, #0x0]
	cmp r6, #0x65
	bgt _020E62A0
	bge _020E632C
	cmp r6, #0x47
	bgt _020E65EC
	cmp r6, #0x45
	blt _020E65EC
	beq _020E632C
	cmp r6, #0x46
	beq _020E6478
	cmp r6, #0x47
	beq _020E62B8
	b _020E65EC
_020E62A0:
	cmp r6, #0x66
	bgt _020E62B0
	beq _020E6478
	b _020E65EC
_020E62B0:
	cmp r6, #0x67
	bne _020E65EC
_020E62B8:
	ldrb r0, [sp, #0x8]
	cmp r0, r7
	ble _020E62D0
	add r0, sp, #0x4
	mov r1, r7
	bl round_decimal_wide
_020E62D0:
	ldrsh r2, [sp, #0x6]
	mvn r0, #0x3
	cmp r2, r0
	blt _020E62E8
	cmp r2, r7
	blt _020E6308
_020E62E8:
	cmp r5, #0x0
	ldreqb r0, [sp, #0x8]
	subne r7, r7, #0x1
	subeq r7, r0, #0x1
	cmp r6, #0x67
	moveq r6, #0x65
	movne r6, #0x45
	b _020E632C
_020E6308:
	cmp r5, #0x0
	addne r0, r2, #0x1
	subne r7, r7, r0
	bne _020E6478
	ldrb r1, [sp, #0x8]
	add r0, r2, #0x1
	subs r7, r1, r0
	movmi r7, #0x0
	b _020E6478
_020E632C:
	ldrb r0, [sp, #0x8]
	add r1, r7, #0x1
	cmp r0, r1
	ble _020E6344
	add r0, sp, #0x4
	bl round_decimal_wide
_020E6344:
	ldrsh lr, [sp, #0x6]
	mov r11, #0x2b
	mov r10, #0x0
	cmp lr, #0x0
	rsblt lr, lr, #0x0
	movlt r11, #0x2d
	ldr r3, _020E6650 ; =0x66666667
	mov r0, #0xa
	b _020E6398
_020E6368:
	mov r1, lr, lsr #0x1f
	smull r2, r12, r3, lr
	add r12, r1, r12, asr #0x2
	smull r1, r2, r0, r12
	sub r12, lr, r1
	add r1, r12, #0x30
	strb r1, [r8, #-0x1]!
	mov r2, lr
	smull r1, lr, r3, r2
	mov r1, r2, lsr #0x1f
	add lr, r1, lr, asr #0x2
	add r10, r10, #0x1
_020E6398:
	cmp lr, #0x0
	bne _020E6368
	cmp r10, #0x2
	blt _020E6368
	add r0, sp, #0x2a
	strb r11, [r8, #-0x1]
	strb r6, [r8, #-0x2]!
	sub r1, r0, r8
	ldr r0, _020E6628 ; =0x000001FD
	add r1, r1, r7
	cmp r1, r0
	addgt sp, sp, #0x22c
	movgt r0, #0x0
	ldmgtia sp!, {r4-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	ldrb r1, [sp, #0x8]
	add r0, r7, #0x1
	cmp r1, r0
	bge _020E6408
	add r0, r7, #0x2
	sub r0, r0, r1
	subs r1, r0, #0x1
	beq _020E6408
	mov r0, #0x30
_020E63FC:
	strb r0, [r8, #-0x1]!
	subs r1, r1, #0x1
	bne _020E63FC
_020E6408:
	ldrb r1, [sp, #0x8]
	add r0, sp, #0x9
	add r2, r0, r1
	subs r1, r1, #0x1
	beq _020E642C
_020E641C:
	ldrsb r0, [r2, #-0x1]!
	subs r1, r1, #0x1
	strb r0, [r8, #-0x1]!
	bne _020E641C
_020E642C:
	cmp r7, #0x0
	cmpeq r5, #0x0
	movne r0, #0x2e
	strneb r0, [r8, #-0x1]!
	ldrb r0, [sp, #0x9]
	strb r0, [r8, #-0x1]!
	ldrsb r0, [sp, #0x4]
	cmp r0, #0x0
	movne r0, #0x2d
	strneb r0, [r8, #-0x1]!
	bne _020E65EC
	cmp r4, #0x1
	moveq r0, #0x2b
	streqb r0, [r8, #-0x1]!
	beq _020E65EC
	cmp r4, #0x2
	moveq r0, #0x20
	streqb r0, [r8, #-0x1]!
	b _020E65EC
_020E6478:
	ldrsh r3, [sp, #0x6]
	ldrb r2, [sp, #0x8]
	sub r0, r2, r3
	subs r1, r0, #0x1
	movmi r1, #0x0
	cmp r1, r7
	ble _020E64B8
	sub r1, r1, r7
	add r0, sp, #0x4
	sub r1, r2, r1
	bl round_decimal_wide
	ldrsh r3, [sp, #0x6]
	ldrb r2, [sp, #0x8]
	sub r0, r2, r3
	subs r1, r0, #0x1
	movmi r1, #0x0
_020E64B8:
	adds r0, r3, #0x1
	movmi r0, #0x0
	ldr r3, _020E6628 ; =0x000001FD
	add r6, r0, r1
	cmp r6, r3
	addgt sp, sp, #0x22c
	movgt r0, #0x0
	ldmgtia sp!, {r4-r11,lr}
	addgt sp, sp, #0x10
	bxgt lr
	add r3, sp, #0x9
	sub r6, r7, r1
	cmp r6, #0x0
	add r2, r3, r2
	mov r10, #0x0
	ble _020E650C
	mov r3, #0x30
_020E64FC:
	add r10, r10, #0x1
	cmp r10, r6
	strb r3, [r8, #-0x1]!
	blt _020E64FC
_020E650C:
	mov r6, #0x0
	b _020E6520
_020E6514:
	ldrsb r3, [r2, #-0x1]!
	add r6, r6, #0x1
	strb r3, [r8, #-0x1]!
_020E6520:
	cmp r6, r1
	ldrltb r3, [sp, #0x8]
	cmplt r6, r3
	blt _020E6514
	cmp r6, r1
	bge _020E654C
	mov r3, #0x30
_020E653C:
	add r6, r6, #0x1
	cmp r6, r1
	strb r3, [r8, #-0x1]!
	blt _020E653C
_020E654C:
	cmp r7, #0x0
	cmpeq r5, #0x0
	movne r1, #0x2e
	strneb r1, [r8, #-0x1]!
	cmp r0, #0x0
	beq _020E65B4
	ldrb r1, [sp, #0x8]
	mov r5, #0x0
	sub r1, r0, r1
	cmp r1, #0x0
	ble _020E6594
	mov r3, #0x30
_020E657C:
	strb r3, [r8, #-0x1]!
	ldrb r1, [sp, #0x8]
	add r5, r5, #0x1
	sub r1, r0, r1
	cmp r5, r1
	blt _020E657C
_020E6594:
	cmp r5, r0
	bge _020E65BC
_020E659C:
	ldrsb r1, [r2, #-0x1]!
	add r5, r5, #0x1
	cmp r5, r0
	strb r1, [r8, #-0x1]!
	blt _020E659C
	b _020E65BC
_020E65B4:
	mov r0, #0x30
	strb r0, [r8, #-0x1]!
_020E65BC:
	ldrsb r0, [sp, #0x4]
	cmp r0, #0x0
	movne r0, #0x2d
	strneb r0, [r8, #-0x1]!
	bne _020E65EC
	cmp r4, #0x1
	moveq r0, #0x2b
	streqb r0, [r8, #-0x1]!
	beq _020E65EC
	cmp r4, #0x2
	moveq r0, #0x20
	streqb r0, [r8, #-0x1]!
_020E65EC:
	mov r0, r8
	bl strlen
	sub r1, r9, r0, lsl #0x1
	mov r0, r8
	sub r4, r1, #0x2
	bl strlen
	mov r2, r0
	mov r0, r4
	mov r1, r8
	bl mbstowcs
	mov r0, r4
	add sp, sp, #0x22c
	ldmia sp!, {r4-r11,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E6628: .word 0x000001FD
_020E662C: .word UNK_02104544
_020E6630: .word UNK_02106DF0
_020E6634: .word UNK_02106DFC
_020E6638: .word UNK_02106E08
_020E663C: .word UNK_02106E10
_020E6640: .word UNK_02106E18
_020E6644: .word UNK_02106E24
_020E6648: .word UNK_02106E30
_020E664C: .word UNK_02106E38
_020E6650: .word 0x66666667

	arm_func_start __wpformatter
__wpformatter:
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x430
	mov r3, #0x20
	mov r11, r2
	strh r3, [sp, #0x1c]
	ldrh r2, [r11, #0x0]
	mov r9, r0
	mov r8, r1
	cmp r2, #0x0
	mov r4, #0x0
	beq _020E6F24
_020E6684:
	mov r0, r11
	mov r1, #0x25
	bl wcschr
	str r0, [sp, #0xc]
	cmp r0, #0x0
	bne _020E66D8
	mov r0, r11
	bl wcslen
	movs r2, r0
	add r4, r4, r2
	beq _020E6F24
	mov r0, r8
	mov r1, r11
	blx r9
	cmp r0, #0x0
	bne _020E6F24
	add sp, sp, #0x430
	mvn r0, #0x0
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E66D8:
	sub r0, r0, r11
	add r0, r0, r0, lsr #0x1f
	movs r2, r0, asr #0x1
	add r4, r4, r2
	beq _020E6710
	mov r0, r8
	mov r1, r11
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x430
	mvneq r0, #0x0
	ldmeqia sp!, {r3-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
_020E6710:
	add r1, sp, #0x400
	ldr r0, [sp, #0xc]
	add r1, r1, #0x64
	add r2, sp, #0x20
	bl parse_format_wprintf
	ldrh r1, [sp, #0x26]
	mov r11, r0
	cmp r1, #0x61
	bgt _020E6780
	bge _020E6AEC
	cmp r1, #0x47
	bgt _020E6774
	subs r0, r1, #0x41
	addpl pc, pc, r0, lsl #0x2
	b _020E6768
	b _020E6AEC
	b _020E6D90
	b _020E6D90
	b _020E6D90
	b _020E6A7C
	b _020E6A7C
	b _020E6A7C
_020E6768:
	cmp r1, #0x25
	beq _020E6D7C
	b _020E6D90
_020E6774:
	cmp r1, #0x58
	beq _020E6940
	b _020E6D90
_020E6780:
	cmp r1, #0x75
	bgt _020E67E8
	subs r0, r1, #0x64
	addpl pc, pc, r0, lsl #0x2
	b _020E67DC
	b _020E6804
	b _020E6A7C
	b _020E6A7C
	b _020E6A7C
	b _020E6D90
	b _020E6804
	b _020E6D90
	b _020E6D90
	b _020E6D90
	b _020E6D90
	b _020E6C98
	b _020E6940
	b _020E6D90
	b _020E6D90
	b _020E6D90
	b _020E6B5C
	b _020E6D90
	b _020E6940
_020E67DC:
	cmp r1, #0x63
	beq _020E6D24
	b _020E6D90
_020E67E8:
	cmp r1, #0x78
	bgt _020E67F8
	beq _020E6940
	b _020E6D90
_020E67F8:
	ldr r0, _020E6F38 ; =0x0000FFFF
	cmp r1, r0
	b _020E6D90
_020E6804:
	ldrb r0, [sp, #0x24]
	cmp r0, #0x3
	bne _020E6824
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
	b _020E68BC
_020E6824:
	cmp r0, #0x4
	bne _020E684C
	ldr r1, [sp, #0x464]
	add r2, r1, #0x8
	str r2, [sp, #0x464]
	ldr r1, [r2, #-0x8]
	str r1, [sp, #0x10]
	ldr r1, [r2, #-0x4]
	str r1, [sp, #0x14]
	b _020E68BC
_020E684C:
	cmp r0, #0x6
	bne _020E6874
	ldr r1, [sp, #0x464]
	add r2, r1, #0x8
	str r2, [sp, #0x464]
	ldr r1, [r2, #-0x8]
	str r1, [sp, #0x10]
	ldr r1, [r2, #-0x4]
	str r1, [sp, #0x14]
	b _020E68BC
_020E6874:
	cmp r0, #0x7
	bne _020E6890
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
	b _020E68BC
_020E6890:
	cmp r0, #0x8
	bne _020E68AC
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
	b _020E68BC
_020E68AC:
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
_020E68BC:
	cmp r0, #0x2
	moveq r1, r10, lsl #0x10
	moveq r10, r1, asr #0x10
	cmp r0, #0x4
	cmpne r0, #0x6
	add r0, sp, #0x20
	bne _020E6904
	sub r5, sp, #0x4
	ldmia r0, {r0-r3}
	stmia r5, {r0-r3}
	ldr r3, [r5, #0x0]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r2, sp, #0x430
	bl longlong2str_wide
	movs r6, r0
	beq _020E6D90
	b _020E6928
_020E6904:
	sub r5, sp, #0x8
	ldmia r0, {r0-r3}
	stmia r5, {r0-r3}
	add r1, sp, #0x430
	mov r0, r10
	ldmia r5, {r2-r3}
	bl long2str_wide
	movs r6, r0
	beq _020E6D90
_020E6928:
	add r0, sp, #0x400
	add r0, r0, #0x2e
	sub r0, r0, r6
	add r0, r0, r0, lsr #0x1f
	mov r7, r0, asr #0x1
	b _020E6DDC
_020E6940:
	ldrb r0, [sp, #0x24]
	cmp r0, #0x3
	bne _020E6960
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
	b _020E69F8
_020E6960:
	cmp r0, #0x4
	bne _020E6988
	ldr r1, [sp, #0x464]
	add r2, r1, #0x8
	str r2, [sp, #0x464]
	ldr r1, [r2, #-0x8]
	str r1, [sp, #0x10]
	ldr r1, [r2, #-0x4]
	str r1, [sp, #0x14]
	b _020E69F8
_020E6988:
	cmp r0, #0x6
	bne _020E69B0
	ldr r1, [sp, #0x464]
	add r2, r1, #0x8
	str r2, [sp, #0x464]
	ldr r1, [r2, #-0x8]
	str r1, [sp, #0x10]
	ldr r1, [r2, #-0x4]
	str r1, [sp, #0x14]
	b _020E69F8
_020E69B0:
	cmp r0, #0x7
	bne _020E69CC
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
	b _020E69F8
_020E69CC:
	cmp r0, #0x8
	bne _020E69E8
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
	b _020E69F8
_020E69E8:
	ldr r1, [sp, #0x464]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r10, [r1, #-0x4]
_020E69F8:
	cmp r0, #0x2
	moveq r1, r10, lsl #0x10
	moveq r10, r1, lsr #0x10
	cmp r0, #0x4
	cmpne r0, #0x6
	add r0, sp, #0x20
	bne _020E6A40
	sub r5, sp, #0x4
	ldmia r0, {r0-r3}
	stmia r5, {r0-r3}
	ldr r3, [r5, #0x0]
	ldr r0, [sp, #0x10]
	ldr r1, [sp, #0x14]
	add r2, sp, #0x430
	bl longlong2str_wide
	movs r6, r0
	beq _020E6D90
	b _020E6A64
_020E6A40:
	sub r5, sp, #0x8
	ldmia r0, {r0-r3}
	stmia r5, {r0-r3}
	add r1, sp, #0x430
	mov r0, r10
	ldmia r5, {r2-r3}
	bl long2str_wide
	movs r6, r0
	beq _020E6D90
_020E6A64:
	add r0, sp, #0x400
	add r0, r0, #0x2e
	sub r0, r0, r6
	add r0, r0, r0, lsr #0x1f
	mov r7, r0, asr #0x1
	b _020E6DDC
_020E6A7C:
	ldrb r0, [sp, #0x24]
	cmp r0, #0x9
	ldrne r0, [sp, #0x464]
	addne r0, r0, #0x8
	strne r0, [sp, #0x464]
	bne _020E6AA0
	ldr r0, [sp, #0x464]
	add r0, r0, #0x8
	str r0, [sp, #0x464]
_020E6AA0:
	ldr r7, [r0, #-0x8]
	ldr r6, [r0, #-0x4]
	add r0, sp, #0x20
	sub r5, sp, #0x4
	ldmia r0, {r0-r3}
	stmia r5, {r0-r3}
	ldr r3, [r5, #0x0]
	mov r0, r7
	mov r1, r6
	add r2, sp, #0x430
	bl float2str_wide
	movs r6, r0
	beq _020E6D90
	add r0, sp, #0x400
	add r0, r0, #0x2e
	sub r0, r0, r6
	add r0, r0, r0, lsr #0x1f
	mov r7, r0, asr #0x1
	b _020E6DDC
_020E6AEC:
	ldrb r0, [sp, #0x24]
	cmp r0, #0x9
	ldrne r0, [sp, #0x464]
	addne r0, r0, #0x8
	strne r0, [sp, #0x464]
	bne _020E6B10
	ldr r0, [sp, #0x464]
	add r0, r0, #0x8
	str r0, [sp, #0x464]
_020E6B10:
	ldr r7, [r0, #-0x8]
	ldr r6, [r0, #-0x4]
	add r0, sp, #0x20
	sub r5, sp, #0x4
	ldmia r0, {r0-r3}
	stmia r5, {r0-r3}
	ldr r3, [r5, #0x0]
	mov r0, r7
	mov r1, r6
	add r2, sp, #0x430
	bl double2hex_wide
	movs r6, r0
	beq _020E6D90
	add r0, sp, #0x400
	add r0, r0, #0x2e
	sub r0, r0, r6
	add r0, r0, r0, lsr #0x1f
	mov r7, r0, asr #0x1
	b _020E6DDC
_020E6B5C:
	ldrb r0, [sp, #0x24]
	cmp r0, #0x5
	bne _020E6BF8
	ldr r0, [sp, #0x464]
	add r0, r0, #0x4
	str r0, [sp, #0x464]
	ldr r6, [r0, #-0x4]
	ldrb r0, [sp, #0x23]
	cmp r6, #0x0
	ldreq r6, _020E6F3C ; =UNK_02106E40
	cmp r0, #0x0
	beq _020E6BB0
	ldrh r1, [r6], #0x2
	ldrb r0, [sp, #0x22]
	and r7, r1, #0xff
	cmp r0, #0x0
	beq _020E6DDC
	ldr r0, [sp, #0x2c]
	cmp r7, r0
	movgt r7, r0
	b _020E6DDC
_020E6BB0:
	ldrb r0, [sp, #0x22]
	cmp r0, #0x0
	beq _020E6BE8
	ldr r7, [sp, #0x2c]
	mov r0, r6
	mov r2, r7
	mov r1, #0x0
	bl wmemchr
	cmp r0, #0x0
	beq _020E6DDC
	sub r0, r0, r6
	add r0, r0, r0, lsr #0x1f
	mov r7, r0, asr #0x1
	b _020E6DDC
_020E6BE8:
	mov r0, r6
	bl wcslen
	mov r7, r0
	b _020E6DDC
_020E6BF8:
	ldr r0, [sp, #0x464]
	add r0, r0, #0x4
	str r0, [sp, #0x464]
	ldr r5, [r0, #-0x4]
	ldrb r0, [sp, #0x23]
	cmp r5, #0x0
	ldreq r5, _020E6F40 ; =UNK_02106E44
	cmp r0, #0x0
	beq _020E6C40
	ldrh r1, [r6, #0x0]
	ldrb r0, [sp, #0x22]
	and r6, r1, #0xff
	cmp r0, #0x0
	beq _020E6C78
	ldr r0, [sp, #0x2c]
	cmp r6, r0
	movgt r6, r0
	b _020E6C78
_020E6C40:
	ldrb r0, [sp, #0x22]
	cmp r0, #0x0
	beq _020E6C6C
	ldr r6, [sp, #0x2c]
	mov r0, r5
	mov r2, r6
	mov r1, #0x0
	bl memchr
	cmp r0, #0x0
	subne r6, r0, r5
	b _020E6C78
_020E6C6C:
	mov r0, r5
	bl strlen
	mov r6, r0
_020E6C78:
	add r0, sp, #0x30
	mov r1, r5
	mov r2, r6
	bl mbstowcs
	movs r7, r0
	bmi _020E6D90
	add r6, sp, #0x30
	b _020E6DDC
_020E6C98:
	ldr r1, [sp, #0x464]
	ldrb r0, [sp, #0x24]
	add r1, r1, #0x4
	str r1, [sp, #0x464]
	ldr r6, [r1, #-0x4]
	cmp r0, #0x8
	addls pc, pc, r0, lsl #0x2
	b _020E6F18
	b _020E6CDC ; case
	b _020E6F18 ; case
	b _020E6CE4 ; case
	b _020E6CEC ; case
	b _020E6D14 ; case
	b _020E6F18 ; case
	b _020E6CF4 ; case
	b _020E6D04 ; case
	b _020E6D0C ; case
_020E6CDC:
	str r4, [r6, #0x0]
	b _020E6F18
_020E6CE4:
	strh r4, [r6, #0x0]
	b _020E6F18
_020E6CEC:
	str r4, [r6, #0x0]
	b _020E6F18
_020E6CF4:
	str r4, [r6, #0x0]
	mov r0, r4, asr #0x1f
	str r0, [r6, #0x4]
	b _020E6F18
_020E6D04:
	str r4, [r6, #0x0]
	b _020E6F18
_020E6D0C:
	str r4, [r6, #0x0]
	b _020E6F18
_020E6D14:
	str r4, [r6, #0x0]
	mov r0, r4, asr #0x1f
	str r0, [r6, #0x4]
	b _020E6F18
_020E6D24:
	ldrb r0, [sp, #0x24]
	add r6, sp, #0x30
	cmp r0, #0x5
	bne _020E6D50
	ldr r0, [sp, #0x464]
	mov r7, #0x1
	add r0, r0, #0x4
	str r0, [sp, #0x464]
	ldr r0, [r0, #-0x4]
	strh r0, [r6, #0x0]
	b _020E6DDC
_020E6D50:
	ldr r0, [sp, #0x464]
	add r1, sp, #0x18
	add r0, r0, #0x4
	str r0, [sp, #0x464]
	ldr r3, [r0, #-0x4]
	mov r0, r6
	mov r2, #0x1
	strb r3, [sp, #0x18]
	bl mbtowc
	mov r7, r0
	b _020E6DDC
_020E6D7C:
	mov r0, #0x25
	strh r0, [sp, #0x30]
	add r6, sp, #0x30
	mov r7, #0x1
	b _020E6DDC
_020E6D90:
	ldr r0, [sp, #0xc]
	bl wcslen
	movs r5, r0
	beq _020E6DC8
	ldr r1, [sp, #0xc]
	mov r0, r8
	mov r2, r5
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x430
	mvneq r0, #0x0
	ldmeqia sp!, {r3-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
_020E6DC8:
	add sp, sp, #0x430
	add r0, r4, r5
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E6DDC:
	ldrb r0, [sp, #0x20]
	mov r5, r7
	cmp r0, #0x0
	beq _020E6E8C
	cmp r0, #0x2
	moveq r1, #0x30
	movne r1, #0x20
	strh r1, [sp, #0x1c]
	ldrh r0, [r6, #0x0]
	cmp r0, #0x2b
	cmpne r0, #0x2d
	cmpne r0, #0x20
	bne _020E6E48
	cmp r1, #0x30
	bne _020E6E48
	mov r0, r8
	mov r1, r6
	mov r2, #0x1
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x430
	mvneq r0, #0x0
	ldmeqia sp!, {r3-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
	add r6, r6, #0x2
	sub r7, r7, #0x1
_020E6E48:
	ldr r0, [sp, #0x28]
	cmp r5, r0
	bge _020E6E8C
_020E6E54:
	mov r0, r8
	add r1, sp, #0x1c
	mov r2, #0x1
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x430
	mvneq r0, #0x0
	ldmeqia sp!, {r3-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r0, [sp, #0x28]
	add r5, r5, #0x1
	cmp r5, r0
	blt _020E6E54
_020E6E8C:
	cmp r7, #0x0
	beq _020E6EBC
	mov r0, r8
	mov r1, r6
	mov r2, r7
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x430
	mvneq r0, #0x0
	ldmeqia sp!, {r3-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
_020E6EBC:
	ldrb r0, [sp, #0x20]
	cmp r0, #0x0
	bne _020E6F14
	ldr r0, [sp, #0x28]
	cmp r5, r0
	bge _020E6F14
	mov r7, #0x20
_020E6ED8:
	mov r0, r8
	add r1, sp, #0x1a
	mov r2, #0x1
	strh r7, [sp, #0x1a]
	blx r9
	cmp r0, #0x0
	addeq sp, sp, #0x430
	mvneq r0, #0x0
	ldmeqia sp!, {r3-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r0, [sp, #0x28]
	add r5, r5, #0x1
	cmp r5, r0
	blt _020E6ED8
_020E6F14:
	add r4, r4, r5
_020E6F18:
	ldrh r0, [r11, #0x0]
	cmp r0, #0x0
	bne _020E6684
_020E6F24:
	mov r0, r4
	add sp, sp, #0x430
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E6F38: .word 0x0000FFFF
_020E6F3C: .word UNK_02106E40
_020E6F40: .word UNK_02106E44

	arm_func_start __wStringWrite
__wStringWrite: ; 0x020E6F44
	stmdb sp!, {r3-r5,lr}
	mov r4, r0
	ldr r3, [r4, #0x8]
	mov r5, r2
	ldr r2, [r4, #0x4]
	add r0, r3, r5
	cmp r0, r2
	ldr r0, [r4, #0x0]
	subhi r5, r2, r3
	mov r2, r5
	add r0, r0, r3, lsl #0x1
	bl wmemcpy
	ldr r1, [r4, #0x8]
	add r1, r1, r5
	str r1, [r4, #0x8]
	ldmia sp!, {r3-r5,pc}

	arm_func_start swprintf
swprintf: ; 0x020E6F84
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3,lr}
	add r3, sp, #0x10
	bic r3, r3, #0x3
	ldr r2, [sp, #0x10]
	add r3, r3, #0x4
	bl vswprintf
	ldmia sp!, {r3,lr}
	add sp, sp, #0x10
	bx lr

	arm_func_start vswprintf
vswprintf: ; 0x020E6FAC
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0xc
	mov r5, r0
	mov r4, r1
	mov r12, #0x0
	ldr r0, _020E7018 ; =__wStringWrite
	add r1, sp, #0x0
	str r5, [sp, #0x0]
	str r4, [sp, #0x4]
	str r12, [sp, #0x8]
	bl __wpformatter
	cmp r0, #0x0
	addlt sp, sp, #0xc
	ldmltia sp!, {r4-r5,pc}
	cmp r0, r4
	bhs _020E7000
	mov r1, r0, lsl #0x1
	mov r2, #0x0
	add sp, sp, #0xc
	strh r2, [r5, r1]
	ldmia sp!, {r4-r5,pc}
_020E7000:
	mov r1, #0x0
	add r0, r5, r4, lsl #0x1
	strh r1, [r0, #-0x2]
	sub r0, r1, #0x1
	add sp, sp, #0xc
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020E7018: .word __wStringWrite

	arm_func_start wcslen
wcslen: ; 0x020E701C
	mvn r2, #0x0
_020E7020:
	ldrh r1, [r0], #0x2
	add r2, r2, #0x1
	cmp r1, #0x0
	bne _020E7020
	mov r0, r2
	bx lr

	arm_func_start wcscpy
wcscpy: ; 0x020E7038
	mov r3, r0
_020E703C:
	ldrh r2, [r1], #0x2
	mov r12, r3
	strh r2, [r3], #0x2
	ldrh r2, [r12, #0x0]
	cmp r2, #0x0
	bne _020E703C
	bx lr

	arm_func_start wcschr
wcschr: ; 0x020E7058
	ldrh r2, [r0], #0x2
	cmp r2, #0x0
	beq _020E707C
_020E7064:
	cmp r2, r1
	subeq r0, r0, #0x2
	bxeq lr
	ldrh r2, [r0], #0x2
	cmp r2, #0x0
	bne _020E7064
_020E707C:
	cmp r1, #0x0
	movne r0, #0x0
	subeq r0, r0, #0x2
	bx lr

	arm_func_start __ieee754_pow
__ieee754_pow: ; 0x020E708C
	stmdb sp!, {r0-r3}
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x80
	ldr r8, [sp, #0xb4]
	ldr r6, [sp, #0xac]
	ldr r0, [sp, #0xb0]
	bic r9, r8, #0x80000000
	orrs r1, r9, r0
	ldr r7, [sp, #0xa8]
	bic r4, r6, #0x80000000
	addeq sp, sp, #0x80
	moveq r0, #0x0
	ldreq r1, _020E7638 ; =0x3FF00000
	ldmeqia sp!, {r3-r11,lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r1, _020E763C ; =0x7FF00000
	cmp r4, r1
	bgt _020E70FC
	bne _020E70E4
	cmp r7, #0x0
	bne _020E70FC
_020E70E4:
	ldr r1, _020E763C ; =0x7FF00000
	cmp r9, r1
	bgt _020E70FC
	bne _020E7120
	cmp r0, #0x0
	beq _020E7120
_020E70FC:
	ldr r0, [sp, #0xa8]
	ldr r1, [sp, #0xac]
	ldr r2, [sp, #0xb0]
	ldr r3, [sp, #0xb4]
	bl _dadd
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7120:
	cmp r6, #0x0
	mov r5, #0x0
	bge _020E7188
	ldr r1, _020E7640 ; =0x43400000
	cmp r9, r1
	movge r5, #0x2
	bge _020E7188
	sub r1, r1, #0x3500000
	cmp r9, r1
	blt _020E7188
	ldr r1, _020E7644 ; =0xFFFFFC01
	add r1, r1, r9, asr #0x14
	cmp r1, #0x14
	ble _020E7170
	rsb r2, r1, #0x34
	mov r1, r0, lsr r2
	cmp r0, r1, lsl r2
	andeq r1, r1, #0x1
	rsbeq r5, r1, #0x2
	b _020E7188
_020E7170:
	cmp r0, #0x0
	rsbeq r2, r1, #0x14
	moveq r1, r9, asr r2
	cmpeq r9, r1, lsl r2
	andeq r1, r1, #0x1
	rsbeq r5, r1, #0x2
_020E7188:
	cmp r0, #0x0
	bne _020E72E4
	ldr r1, _020E763C ; =0x7FF00000
	cmp r9, r1
	bne _020E723C
	add r0, r4, #0x100000
	add r0, r0, #0xc0000000
	orrs r0, r0, r7
	bne _020E71D0
	ldr r0, [sp, #0xb0]
	ldr r1, [sp, #0xb4]
	mov r2, r0
	mov r3, r1
	bl _dsub
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E71D0:
	sub r0, r1, #0x40000000
	cmp r4, r0
	blt _020E7200
	cmp r8, #0x0
	ldrge r0, [sp, #0xb0]
	ldrge r1, [sp, #0xb4]
	movlt r0, #0x0
	add sp, sp, #0x80
	movlt r1, r0
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7200:
	cmp r8, #0x0
	mov r0, #0x0
	addge sp, sp, #0x80
	movge r1, r0
	ldmgeia sp!, {r3-r11,lr}
	addge sp, sp, #0x10
	bxge lr
	ldr r2, [sp, #0xb0]
	ldr r3, [sp, #0xb4]
	mov r1, r0
	bl _dsub
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E723C:
	sub r0, r1, #0x40000000
	cmp r9, r0
	bne _020E7288
	cmp r8, #0x0
	ldrge r0, [sp, #0xa8]
	ldrge r1, [sp, #0xac]
	addge sp, sp, #0x80
	ldmgeia sp!, {r3-r11,lr}
	addge sp, sp, #0x10
	bxge lr
	ldr r2, [sp, #0xa8]
	ldr r3, [sp, #0xac]
	sub r1, r1, #0x40000000
	mov r0, #0x0
	bl _ddiv
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7288:
	cmp r8, #0x40000000
	bne _020E72B4
	ldr r0, [sp, #0xa8]
	ldr r1, [sp, #0xac]
	mov r2, r0
	mov r3, r1
	bl _dmul
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E72B4:
	ldr r0, _020E7648 ; =0x3FE00000
	cmp r8, r0
	bne _020E72E4
	cmp r6, #0x0
	blt _020E72E4
	ldr r0, [sp, #0xa8]
	ldr r1, [sp, #0xac]
	bl _dsqrt
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E72E4:
	ldr r0, [sp, #0xa8]
	ldr r1, [sp, #0xac]
	bl fabs
	str r0, [sp, #0x70]
	str r1, [sp, #0x74]
	cmp r7, #0x0
	bne _020E73E8
	ldr r0, _020E763C ; =0x7FF00000
	cmp r4, r0
	cmpne r4, #0x0
	subne r0, r0, #0x40000000
	cmpne r4, r0
	bne _020E73E8
	ldr r2, [sp, #0x70]
	ldr r3, [sp, #0x74]
	str r2, [sp, #0x78]
	str r3, [sp, #0x7c]
	cmp r8, #0x0
	bge _020E7344
	ldr r1, _020E7638 ; =0x3FF00000
	mov r0, #0x0
	bl _ddiv
	str r0, [sp, #0x78]
	str r1, [sp, #0x7c]
_020E7344:
	cmp r6, #0x0
	bge _020E73D0
	add r0, r4, #0x100000
	add r0, r0, #0xc0000000
	orrs r0, r0, r5
	bne _020E73AC
	ldr r0, [sp, #0x78]
	ldr r1, [sp, #0x7c]
	mov r2, r0
	mov r3, r1
	bl _dsub
	mov r4, r0
	mov r5, r1
	ldr r0, [sp, #0x78]
	ldr r1, [sp, #0x7c]
	mov r2, r0
	mov r3, r1
	bl _dsub
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r5
	bl _ddiv
	str r0, [sp, #0x78]
	str r1, [sp, #0x7c]
	b _020E73D0
_020E73AC:
	cmp r5, #0x1
	bne _020E73D0
	mov r0, #0x0
	ldr r2, [sp, #0x78]
	ldr r3, [sp, #0x7c]
	mov r1, r0
	bl _dsub
	str r0, [sp, #0x78]
	str r1, [sp, #0x7c]
_020E73D0:
	ldr r0, [sp, #0x78]
	ldr r1, [sp, #0x7c]
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E73E8:
	mov r0, r6, asr #0x1f
	add r7, r0, #0x1
	orrs r0, r7, r5
	bne _020E7420
	ldr r0, _020E764C ; =__float_nan
	ldr r1, _020E7650 ; =errno
	ldr r0, [r0, #0x0]
	mov r2, #0x21
	str r2, [r1, #0x0]
	bl _f2d
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7420:
	ldr r3, _020E7654 ; =0x41E00000
	cmp r9, r3
	ble _020E7724
	add r0, r3, #0x2100000
	cmp r9, r0
	ble _020E7490
	ldr r1, _020E7658 ; =0x3FEFFFFF
	cmp r4, r1
	bgt _020E7464
	cmp r8, #0x0
	mov r0, #0x0
	addlt r1, r1, #0x40000001
	add sp, sp, #0x80
	movge r1, r0
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7464:
	add r0, r1, #0x1
	cmp r4, r0
	blt _020E7490
	cmp r8, #0x0
	mov r0, #0x0
	addgt r1, r1, #0x40000001
	add sp, sp, #0x80
	movle r1, r0
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7490:
	ldr r2, _020E7658 ; =0x3FEFFFFF
	cmp r4, r2
	bge _020E74BC
	cmp r8, #0x0
	mov r0, #0x0
	addlt r1, r2, #0x40000001
	add sp, sp, #0x80
	movge r1, r0
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E74BC:
	add r0, r2, #0x1
	cmp r4, r0
	ble _020E74E8
	cmp r8, #0x0
	mov r0, #0x0
	addgt r1, r2, #0x40000001
	add sp, sp, #0x80
	movle r1, r0
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E74E8:
	ldr r0, [sp, #0xa8]
	ldr r1, [sp, #0xac]
	add r3, r2, #0x1
	mov r2, #0x0
	bl _dsub
	mov r2, r0
	mov r3, r1
	str r0, [sp, #0x50]
	str r1, [sp, #0x54]
	bl _dmul
	mov r6, r1
	mov r4, r0
	ldr r2, [sp, #0x50]
	ldr r3, [sp, #0x54]
	ldr r1, _020E765C ; =0x3FD00000
	mov r0, #0x0
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E7660 ; =0x55555555
	sub r1, r0, #0x15800000
	bl _dsub
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x50]
	ldr r1, [sp, #0x54]
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, #0x0
	ldr r1, _020E7648 ; =0x3FE00000
	bl _dsub
	mov r2, r0
	mov r0, r4
	mov r3, r1
	mov r1, r6
	bl _dmul
	mov r6, r0
	mov r8, r1
	mov r0, #0x60000000
	ldr r1, _020E7664 ; =0x3FF71547
	ldr r2, [sp, #0x50]
	ldr r3, [sp, #0x54]
	bl _dmul
	mov r4, r0
	mov r9, r1
	ldr r0, _020E7668 ; =0xF85DDF44
	ldr r1, _020E766C ; =0x3E54AE0B
	ldr r2, [sp, #0x50]
	ldr r3, [sp, #0x54]
	bl _dmul
	mov r11, r0
	mov r10, r1
	ldr r0, _020E7670 ; =0x652B82FE
	ldr r1, _020E7664 ; =0x3FF71547
	mov r2, r6
	mov r3, r8
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, r11
	mov r1, r10
	bl _dsub
	mov r6, r0
	mov r8, r1
	mov r0, r4
	mov r1, r9
	mov r2, r6
	mov r3, r8
	bl _dadd
	mov r2, r4
	mov r3, r9
	str r1, [sp, #0x5c]
	mov r0, #0x0
	str r0, [sp, #0x58]
	bl _dsub
	mov r2, r0
	mov r0, r6
	mov r3, r1
	mov r1, r8
	bl _dsub
	mov r4, r0
	mov r8, r1
	b _020E7C80
	.balign 4
_020E7638: .word 0x3FF00000
_020E763C: .word 0x7FF00000
_020E7640: .word 0x43400000
_020E7644: .word 0xFFFFFC01
_020E7648: .word 0x3FE00000
_020E764C: .word __float_nan
_020E7650: .word errno
_020E7654: .word 0x41E00000
_020E7658: .word 0x3FEFFFFF
_020E765C: .word 0x3FD00000
_020E7660: .word 0x55555555
_020E7664: .word 0x3FF71547
_020E7668: .word 0xF85DDF44
_020E766C: .word 0x3E54AE0B
_020E7670: .word 0x652B82FE
_020E7674: .word 0x0003988E
_020E7678: .word 0x000BB67A
_020E767C: .word UNK_02104754
_020E7680: .word 0x4A454EEF
_020E7684: .word 0x3FCA7E28
_020E7688: .word 0x93C9DB65
_020E768C: .word 0x3FCD864A
_020E7690: .word 0xA91D4101
_020E7694: .word 0x3FD17460
_020E7698: .word 0x518F264D
_020E769C: .word 0x3FD55555
_020E76A0: .word 0xDB6FABFF
_020E76A4: .word 0x3FDB6DB6
_020E76A8: .word 0x33333303
_020E76AC: .word 0x3FE33333
_020E76B0: .word 0x40080000
_020E76B4: .word 0x3FEEC709
_020E76B8: .word 0x145B01F5
_020E76BC: .word 0xBE3E2FE0
_020E76C0: .word 0xDC3A03FD
_020E76C4: .word UNK_02104764
_020E76C8: .word UNK_02104744
_020E76CC: .word 0x40900000
_020E76D0: .word 0x8800759C
_020E76D4: .word 0x7E37E43C
_020E76D8: .word 0x3C971547
_020E76DC: .word 0x3F6F3400
_020E76E0: .word 0xC2F8F359
_020E76E4: .word 0x01A56E1F
_020E76E8: .word 0x3FE62E43
_020E76EC: .word 0xFEFA39EF
_020E76F0: .word 0x3FE62E42
_020E76F4: .word 0x0CA86C39
_020E76F8: .word 0xBE205C61
_020E76FC: .word 0x72BEA4D0
_020E7700: .word 0x3E663769
_020E7704: .word 0xC5D26BF1
_020E7708: .word 0xBEBBBD41
_020E770C: .word 0xAF25DE2C
_020E7710: .word 0x3F11566A
_020E7714: .word 0x16BEBD93
_020E7718: .word 0xBF66C16C
_020E771C: .word 0x5555553E
_020E7720: .word 0x3FC55555
_020E7724:
	cmp r4, #0x100000
	mov r6, #0x0
	bge _020E7754
	ldr r0, [sp, #0x70]
	ldr r1, [sp, #0x74]
	mov r2, r6
	add r3, r3, #0x1600000
	bl _dmul
	mov r4, r1
	str r0, [sp, #0x70]
	str r4, [sp, #0x74]
	sub r6, r6, #0x35
_020E7754:
	ldr r0, _020E7644 ; =0xFFFFFC01
	ldr r1, _020E7674 ; =0x0003988E
	and r2, r4, r0, lsr #0xc
	add r0, r0, r4, asr #0x14
	orr r9, r2, #0xff00000
	cmp r2, r1
	add r6, r6, r0
	orr r9, r9, #0x30000000
	movle r8, #0x0
	ble _020E7794
	ldr r0, _020E7678 ; =0x000BB67A
	cmp r2, r0
	movlt r8, #0x1
	addge r6, r6, #0x1
	subge r9, r9, #0x100000
	movge r8, #0x0
_020E7794:
	ldr r2, _020E767C ; =UNK_02104754
	ldr r0, [sp, #0x70]
	add r1, r2, r8, lsl #0x3
	ldr r3, [r1, #0x4]
	ldr r2, [r2, r8, lsl #0x3]
	mov r1, r9
	str r9, [sp, #0x74]
	bl _dsub
	ldr r2, _020E767C ; =UNK_02104754
	mov r10, r0
	add r3, r2, r8, lsl #0x3
	mov r4, r1
	ldr r0, [sp, #0x70]
	ldr r2, [r2, r8, lsl #0x3]
	ldr r3, [r3, #0x4]
	mov r1, r9
	bl _dadd
	mov r3, r1
	mov r2, r0
	ldr r1, _020E7638 ; =0x3FF00000
	mov r0, #0x0
	bl _ddiv
	str r1, [sp, #0x24]
	mov r11, r0
	ldr r3, [sp, #0x24]
	mov r0, r10
	mov r1, r4
	mov r2, r11
	bl _dmul
	mov r2, r9, asr #0x1
	orr r2, r2, #0x20000000
	mov r9, r1
	add r2, r2, #0x80000
	add r1, r2, r8, lsl #0x12
	ldr r2, _020E767C ; =UNK_02104754
	str r0, [sp, #0x28]
	add r3, r2, r8, lsl #0x3
	mov r0, #0x0
	ldr r2, [r2, r8, lsl #0x3]
	ldr r3, [r3, #0x4]
	str r9, [sp, #0x4c]
	str r1, [sp, #0x44]
	str r0, [sp, #0x48]
	str r0, [sp, #0x40]
	bl _dsub
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x70]
	ldr r1, [sp, #0x74]
	bl _dsub
	str r0, [sp, #0x2c]
	str r1, [sp, #0x1c]
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x40]
	ldr r3, [sp, #0x44]
	mov r1, r9
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, r10
	mov r1, r4
	bl _dsub
	mov r10, r0
	mov r4, r1
	ldr r2, [sp, #0x2c]
	ldr r3, [sp, #0x1c]
	ldr r0, [sp, #0x48]
	mov r1, r9
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, r10
	mov r1, r4
	bl _dsub
	mov r3, r1
	mov r2, r0
	ldr r1, [sp, #0x24]
	mov r0, r11
	bl _dmul
	str r0, [sp, #0x30]
	ldr r0, [sp, #0x28]
	str r1, [sp, #0x14]
	mov r1, r9
	mov r2, r0
	mov r3, r9
	bl _dmul
	mov r4, r0
	mov r10, r1
	mov r2, r4
	mov r3, r10
	bl _dmul
	str r0, [sp, #0x34]
	mov r11, r1
	ldr r0, _020E7680 ; =0x4A454EEF
	ldr r1, _020E7684 ; =0x3FCA7E28
	mov r2, r4
	mov r3, r10
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E7688 ; =0x93C9DB65
	ldr r1, _020E768C ; =0x3FCD864A
	bl _dadd
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r10
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E7690 ; =0xA91D4101
	ldr r1, _020E7694 ; =0x3FD17460
	bl _dadd
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r10
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E7698 ; =0x518F264D
	ldr r1, _020E769C ; =0x3FD55555
	bl _dadd
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r10
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76A0 ; =0xDB6FABFF
	ldr r1, _020E76A4 ; =0x3FDB6DB6
	bl _dadd
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r10
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76A8 ; =0x33333303
	ldr r1, _020E76AC ; =0x3FE33333
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x34]
	mov r1, r11
	bl _dmul
	mov r4, r0
	mov r10, r1
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x28]
	mov r1, r9
	mov r3, r9
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x30]
	ldr r1, [sp, #0x14]
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r10
	bl _dadd
	mov r4, r0
	ldr r0, [sp, #0x48]
	mov r10, r1
	mov r1, r9
	mov r2, r0
	mov r3, r1
	bl _dmul
	str r1, [sp, #0xc]
	mov r11, r0
	ldr r1, _020E76B0 ; =0x40080000
	ldr r3, [sp, #0xc]
	mov r0, #0x0
	mov r2, r11
	bl _dadd
	mov r2, r4
	mov r3, r10
	bl _dadd
	mov r0, #0x0
	ldr r3, _020E76B0 ; =0x40080000
	mov r2, r0
	str r1, [sp, #0x44]
	str r0, [sp, #0x40]
	bl _dsub
	ldr r3, [sp, #0xc]
	mov r2, r11
	bl _dsub
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r10
	bl _dsub
	str r0, [sp, #0x38]
	str r1, [sp, #0x4]
	ldr r0, [sp, #0x48]
	ldr r2, [sp, #0x40]
	ldr r3, [sp, #0x44]
	mov r1, r9
	bl _dmul
	mov r4, r0
	mov r10, r1
	ldr r0, [sp, #0x30]
	ldr r1, [sp, #0x14]
	ldr r2, [sp, #0x40]
	ldr r3, [sp, #0x44]
	bl _dmul
	str r0, [sp, #0x3c]
	mov r11, r1
	ldr r0, [sp, #0x38]
	ldr r1, [sp, #0x4]
	ldr r2, [sp, #0x28]
	mov r3, r9
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x3c]
	mov r1, r11
	bl _dadd
	mov r9, r0
	mov r11, r1
	mov r0, r4
	mov r1, r10
	mov r2, r9
	mov r3, r11
	bl _dadd
	mov r0, #0x0
	mov r2, r4
	mov r3, r10
	str r1, [sp, #0x6c]
	str r0, [sp, #0x68]
	bl _dsub
	mov r2, r0
	mov r3, r1
	mov r0, r9
	mov r1, r11
	bl _dsub
	mov r10, r1
	mov r11, r0
	ldr r1, _020E76B4 ; =0x3FEEC709
	ldr r2, [sp, #0x68]
	ldr r3, [sp, #0x6c]
	mov r0, #0xe0000000
	bl _dmul
	mov r4, r0
	mov r9, r1
	ldr r0, _020E76B8 ; =0x145B01F5
	ldr r1, _020E76BC ; =0xBE3E2FE0
	ldr r2, [sp, #0x68]
	ldr r3, [sp, #0x6c]
	bl _dmul
	mov r2, r11
	mov r3, r10
	mov r11, r0
	mov r10, r1
	ldr r0, _020E76C0 ; =0xDC3A03FD
	ldr r1, _020E76B4 ; =0x3FEEC709
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, r11
	mov r1, r10
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76C4 ; =UNK_02104764
	add r1, r0, r8, lsl #0x3
	ldr r0, [r0, r8, lsl #0x3]
	ldr r1, [r1, #0x4]
	bl _dadd
	mov r11, r0
	mov r10, r1
	mov r0, r6
	bl _dflt
	str r0, [sp, #0x50]
	str r1, [sp, #0x54]
	mov r0, r4
	mov r1, r9
	mov r2, r11
	mov r3, r10
	bl _dadd
	ldr r2, _020E76C8 ; =UNK_02104744
	add r3, r2, r8, lsl #0x3
	ldr r2, [r2, r8, lsl #0x3]
	ldr r3, [r3, #0x4]
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x50]
	ldr r1, [sp, #0x54]
	bl _dadd
	str r1, [sp, #0x5c]
	mov r0, #0x0
	str r0, [sp, #0x58]
	ldr r2, [sp, #0x50]
	ldr r3, [sp, #0x54]
	bl _dsub
	ldr r2, _020E76C8 ; =UNK_02104744
	add r3, r2, r8, lsl #0x3
	ldr r2, [r2, r8, lsl #0x3]
	ldr r3, [r3, #0x4]
	bl _dsub
	mov r2, r4
	mov r3, r9
	bl _dsub
	mov r2, r0
	mov r0, r11
	mov r3, r1
	mov r1, r10
	bl _dsub
	mov r4, r0
	mov r8, r1
_020E7C80:
	sub r0, r5, #0x1
	ldr r1, [sp, #0xb4]
	orrs r0, r7, r0
	ldr r5, _020E7638 ; =0x3FF00000
	mov r2, #0x0
	ldr r0, [sp, #0xb0]
	mov r3, r1
	mov r6, #0x0
	subeq r5, r5, #0x80000000
	str r1, [sp, #0x64]
	str r2, [sp, #0x60]
	bl _dsub
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x58]
	ldr r1, [sp, #0x5c]
	bl _dmul
	mov r7, r0
	mov r9, r1
	ldr r0, [sp, #0xb0]
	ldr r1, [sp, #0xb4]
	mov r2, r4
	mov r3, r8
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, r7
	mov r1, r9
	bl _dadd
	mov r7, r0
	mov r8, r1
	ldr r0, [sp, #0x60]
	ldr r1, [sp, #0x64]
	ldr r2, [sp, #0x58]
	ldr r3, [sp, #0x5c]
	bl _dmul
	mov r2, r0
	mov r3, r1
	mov r0, r7
	mov r1, r8
	str r2, [sp, #0x68]
	str r3, [sp, #0x6c]
	bl _dadd
	mov r9, r1
	ldr r2, _020E76CC ; =0x40900000
	str r0, [sp, #0x78]
	str r9, [sp, #0x7c]
	cmp r9, r2
	blt _020E7E0C
	add r1, r9, #0xf700000
	add r1, r1, #0xb0000000
	orrs r0, r1, r0
	beq _020E7D8C
	ldr r0, _020E76D0 ; =0x8800759C
	ldr r1, _020E76D4 ; =0x7E37E43C
	mov r2, r6
	mov r3, r5
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76D0 ; =0x8800759C
	ldr r1, _020E76D4 ; =0x7E37E43C
	bl _dmul
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7D8C:
	ldr r0, _020E7670 ; =0x652B82FE
	ldr r1, _020E76D8 ; =0x3C971547
	mov r2, r7
	mov r3, r8
	bl _dadd
	mov r4, r0
	mov r10, r1
	ldr r0, [sp, #0x78]
	ldr r2, [sp, #0x68]
	ldr r3, [sp, #0x6c]
	mov r1, r9
	bl _dsub
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r10
	bl _dgr
	bls _020E7EC0
	ldr r0, _020E76D0 ; =0x8800759C
	ldr r1, _020E76D4 ; =0x7E37E43C
	mov r2, r6
	mov r3, r5
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76D0 ; =0x8800759C
	ldr r1, _020E76D4 ; =0x7E37E43C
	bl _dmul
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7E0C:
	bic r3, r9, #0x80000000
	add r2, r2, #0xcc00
	cmp r3, r2
	blt _020E7EC0
	ldr r2, _020E76DC ; =0x3F6F3400
	add r2, r9, r2
	orrs r2, r2, r0
	beq _020E7E64
	ldr r0, _020E76E0 ; =0xC2F8F359
	ldr r1, _020E76E4 ; =0x01A56E1F
	mov r2, r6
	mov r3, r5
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76E0 ; =0xC2F8F359
	ldr r1, _020E76E4 ; =0x01A56E1F
	bl _dmul
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7E64:
	ldr r2, [sp, #0x68]
	ldr r3, [sp, #0x6c]
	bl _dsub
	mov r2, r0
	mov r3, r1
	mov r0, r7
	mov r1, r8
	bl _dleq
	bhi _020E7EC0
	ldr r0, _020E76E0 ; =0xC2F8F359
	ldr r1, _020E76E4 ; =0x01A56E1F
	mov r2, r6
	mov r3, r5
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76E0 ; =0xC2F8F359
	ldr r1, _020E76E4 ; =0x01A56E1F
	bl _dmul
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr
_020E7EC0:
	ldr r0, _020E7644 ; =0xFFFFFC01
	bic r3, r9, #0x80000000
	ldr r1, _020E7648 ; =0x3FE00000
	add r2, r0, r3, asr #0x14
	cmp r3, r1
	mov r4, #0x0
	ble _020E7F3C
	mov r1, #0x100000
	add r2, r2, #0x1
	add r2, r9, r1, asr r2
	bic r3, r2, #0x80000000
	add r0, r0, r3, asr #0x14
	sub r3, r1, #0x1
	mvn r3, r3, asr r0
	sub r1, r1, #0x1
	and r1, r2, r1
	and r2, r2, r3
	str r2, [sp, #0x54]
	str r4, [sp, #0x50]
	orr r1, r1, #0x100000
	rsb r0, r0, #0x14
	mov r4, r1, asr r0
	cmp r9, #0x0
	ldr r0, [sp, #0x68]
	ldr r1, [sp, #0x6c]
	ldr r2, [sp, #0x50]
	ldr r3, [sp, #0x54]
	rsblt r4, r4, #0x0
	bl _dsub
	str r0, [sp, #0x68]
	str r1, [sp, #0x6c]
_020E7F3C:
	ldr r2, [sp, #0x68]
	ldr r3, [sp, #0x6c]
	mov r0, r7
	mov r1, r8
	bl _dadd
	mov r3, r1
	mov r0, #0x0
	ldr r1, _020E76E8 ; =0x3FE62E43
	mov r2, r0
	str r3, [sp, #0x54]
	str r0, [sp, #0x50]
	bl _dmul
	mov r9, r0
	mov r10, r1
	ldr r0, [sp, #0x50]
	ldr r1, [sp, #0x54]
	ldr r2, [sp, #0x68]
	ldr r3, [sp, #0x6c]
	bl _dsub
	mov r2, r0
	mov r0, r7
	mov r3, r1
	mov r1, r8
	bl _dsub
	mov r2, r0
	mov r3, r1
	ldr r0, _020E76EC ; =0xFEFA39EF
	ldr r1, _020E76F0 ; =0x3FE62E42
	bl _dmul
	mov r7, r0
	mov r8, r1
	ldr r0, _020E76F4 ; =0x0CA86C39
	ldr r1, _020E76F8 ; =0xBE205C61
	ldr r2, [sp, #0x50]
	ldr r3, [sp, #0x54]
	bl _dmul
	mov r2, r0
	mov r0, r7
	mov r3, r1
	mov r1, r8
	bl _dadd
	mov r7, r0
	mov r8, r1
	mov r0, r9
	mov r1, r10
	mov r2, r7
	mov r3, r8
	bl _dadd
	mov r2, r9
	mov r3, r10
	str r0, [sp, #0x78]
	str r1, [sp, #0x7c]
	bl _dsub
	mov r2, r0
	mov r3, r1
	mov r0, r7
	mov r1, r8
	bl _dsub
	mov r8, r0
	mov r9, r1
	ldr r0, [sp, #0x78]
	ldr r1, [sp, #0x7c]
	mov r2, r0
	mov r3, r1
	bl _dmul
	mov r2, r0
	str r2, [sp, #0x50]
	mov r3, r1
	str r3, [sp, #0x54]
	ldr r0, _020E76FC ; =0x72BEA4D0
	ldr r1, _020E7700 ; =0x3E663769
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E7704 ; =0xC5D26BF1
	ldr r1, _020E7708 ; =0xBEBBBD41
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x50]
	ldr r1, [sp, #0x54]
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E770C ; =0xAF25DE2C
	ldr r1, _020E7710 ; =0x3F11566A
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x50]
	ldr r1, [sp, #0x54]
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E7714 ; =0x16BEBD93
	ldr r1, _020E7718 ; =0xBF66C16C
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x50]
	ldr r1, [sp, #0x54]
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, _020E771C ; =0x5555553E
	ldr r1, _020E7720 ; =0x3FC55555
	bl _dadd
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x50]
	ldr r1, [sp, #0x54]
	bl _dmul
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x78]
	ldr r1, [sp, #0x7c]
	bl _dsub
	mov r2, r0
	str r2, [sp, #0x58]
	mov r3, r1
	str r3, [sp, #0x5c]
	ldr r0, [sp, #0x78]
	ldr r1, [sp, #0x7c]
	bl _dmul
	mov r7, r0
	mov r10, r1
	ldr r0, [sp, #0x58]
	ldr r1, [sp, #0x5c]
	mov r2, #0x0
	mov r3, #0x40000000
	bl _dsub
	mov r2, r0
	mov r0, r7
	mov r3, r1
	mov r1, r10
	bl _ddiv
	mov r7, r0
	mov r10, r1
	ldr r0, [sp, #0x78]
	ldr r1, [sp, #0x7c]
	mov r2, r8
	mov r3, r9
	bl _dmul
	mov r2, r0
	mov r0, r8
	mov r3, r1
	mov r1, r9
	bl _dadd
	mov r2, r0
	mov r0, r7
	mov r3, r1
	mov r1, r10
	bl _dsub
	ldr r2, [sp, #0x78]
	ldr r3, [sp, #0x7c]
	bl _dsub
	mov r3, r1
	mov r2, r0
	ldr r1, _020E7638 ; =0x3FF00000
	mov r0, #0x0
	bl _dsub
	add r3, r1, r4, lsl #0x14
	mov r2, r3, asr #0x14
	str r0, [sp, #0x78]
	cmp r2, #0x0
	str r1, [sp, #0x7c]
	addgt r0, sp, #0x78
	strgt r3, [r0, #0x4]
	bgt _020E81F0
	mov r2, r4
	bl scalbn
	str r0, [sp, #0x78]
	str r1, [sp, #0x7c]
_020E81F0:
	ldr r2, [sp, #0x78]
	ldr r3, [sp, #0x7c]
	mov r0, r6
	mov r1, r5
	bl _dmul
	add sp, sp, #0x80
	ldmia sp!, {r3-r11,lr}
	add sp, sp, #0x10
	bx lr

	arm_func_start copysign
copysign: ; 0x020E8214
	stmdb sp!, {r0-r3}
	ldr r1, [sp, #0x4]
	ldr r0, [sp, #0xc]
	bic r1, r1, #0x80000000
	and r0, r0, #0x80000000
	orr r1, r1, r0
	ldr r0, [sp, #0x0]
	str r1, [sp, #0x4]
	add sp, sp, #0x10
	bx lr

	arm_func_start fabs
fabs: ; 0x020E823C
	stmdb sp!, {r0-r3}
	add r2, sp, #0x0
	ldr r1, [r2, #0x4]
	ldr r0, [sp, #0x0]
	bic r1, r1, #0x80000000
	str r1, [r2, #0x4]
	add sp, sp, #0x10
	bx lr

	arm_func_start frexp
frexp: ; 0x020E825C
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4,lr}
	ldr r1, [sp, #0xc]
	ldr r0, _020E8308 ; =0x7FF00000
	mov r4, r2
	bic r3, r1, #0x80000000
	mov r2, #0x0
	str r2, [r4, #0x0]
	cmp r3, r0
	ldr r0, [sp, #0x8]
	bge _020E8290
	orrs r0, r3, r0
	bne _020E82A4
_020E8290:
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E82A4:
	cmp r3, #0x100000
	bge _020E82D0
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	ldr r3, _020E830C ; =0x43500000
	bl _dmul
	mvn r2, #0x35
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	str r2, [r4, #0x0]
	bic r3, r1, #0x80000000
_020E82D0:
	ldr r2, _020E8310 ; =0x800FFFFF
	ldr r0, _020E8314 ; =0xFFFFFC02
	and r1, r1, r2
	orr r1, r1, #0xfe00000
	orr r1, r1, #0x30000000
	ldr r2, [r4, #0x0]
	add r0, r0, r3, asr #0x14
	add r2, r2, r0
	ldr r0, [sp, #0x8]
	str r2, [r4, #0x0]
	str r1, [sp, #0xc]
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E8308: .word 0x7FF00000
_020E830C: .word 0x43500000
_020E8310: .word 0x800FFFFF
_020E8314: .word 0xFFFFFC02

	arm_func_start ldexp
ldexp: ; 0x020E8318
	stmdb sp!, {r0-r3}
	stmdb sp!, {r4,lr}
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	mov r4, r2
	bl __fpclassifyf
	cmp r0, #0x2
	ble _020E8350
	mov r0, #0x0
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	mov r1, r0
	bl _deq
	bne _020E8364
_020E8350:
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E8364:
	ldr r3, [sp, #0xc]
	ldr r0, _020E8538 ; =0x7FF00000
	ldr r1, [sp, #0x8]
	and r0, r3, r0
	movs r12, r0, asr #0x14
	bne _020E83F0
	bic r0, r3, #0x80000000
	orrs r0, r1, r0
	ldreq r0, [sp, #0x8]
	ldreq r1, [sp, #0xc]
	ldmeqia sp!, {r4,lr}
	addeq sp, sp, #0x10
	bxeq lr
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	ldr r3, _020E853C ; =0x43500000
	mov r2, #0x0
	bl _dmul
	mov r3, r1
	ldr r1, _020E8538 ; =0x7FF00000
	ldr ip, _020E8540 ; =0xFFFF3CB0
	and r1, r3, r1
	mov r2, r0
	mov r0, r1, asr #0x14
	str r2, [sp, #0x8]
	str r3, [sp, #0xc]
	cmp r4, r12
	sub r12, r0, #0x36
	bge _020E83F0
	ldr r0, _020E8544 ; =0xC2F8F359
	ldr r1, _020E8548 ; =0x01A56E1F
	bl _dmul
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E83F0:
	ldr r0, _020E854C ; =0x000007FF
	cmp r12, r0
	bne _020E841C
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	mov r2, r0
	mov r3, r1
	bl _dadd
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E841C:
	add r2, r12, r4
	sub r0, r0, #0x1
	cmp r2, r0
	ble _020E8460
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	ldr r0, _020E8550 ; =0x8800759C
	ldr r1, _020E8554 ; =0x7E37E43C
	bl copysign
	mov r2, r0
	mov r3, r1
	ldr r0, _020E8550 ; =0x8800759C
	ldr r1, _020E8554 ; =0x7E37E43C
	bl _dmul
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E8460:
	cmp r2, #0x0
	ble _020E8488
	ldr r1, _020E8558 ; =0x800FFFFF
	ldr r0, [sp, #0x8]
	and r1, r3, r1
	orr r1, r1, r2, lsl #0x14
	str r1, [sp, #0xc]
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E8488:
	mvn r0, #0x35
	cmp r2, r0
	bgt _020E8508
	ldr r0, _020E855C ; =0x0000C350
	cmp r4, r0
	ble _020E84D4
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	ldr r0, _020E8550 ; =0x8800759C
	ldr r1, _020E8554 ; =0x7E37E43C
	bl copysign
	mov r2, r0
	mov r3, r1
	ldr r0, _020E8550 ; =0x8800759C
	ldr r1, _020E8554 ; =0x7E37E43C
	bl _dmul
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E84D4:
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	ldr r0, _020E8544 ; =0xC2F8F359
	ldr r1, _020E8548 ; =0x01A56E1F
	bl copysign
	mov r2, r0
	mov r3, r1
	ldr r0, _020E8544 ; =0xC2F8F359
	ldr r1, _020E8548 ; =0x01A56E1F
	bl _dmul
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
_020E8508:
	ldr r0, _020E8558 ; =0x800FFFFF
	add r1, r2, #0x36
	and r0, r3, r0
	orr r3, r0, r1, lsl #0x14
	ldr r2, [sp, #0x8]
	ldr r1, _020E8560 ; =0x3C900000
	mov r0, #0x0
	str r3, [sp, #0xc]
	bl _dmul
	ldmia sp!, {r4,lr}
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E8538: .word 0x7FF00000
_020E853C: .word 0x43500000
_020E8540: .word 0xFFFF3CB0
_020E8544: .word 0xC2F8F359
_020E8548: .word 0x01A56E1F
_020E854C: .word 0x000007FF
_020E8550: .word 0x8800759C
_020E8554: .word 0x7E37E43C
_020E8558: .word 0x800FFFFF
_020E855C: .word 0x0000C350
_020E8560: .word 0x3C900000

	arm_func_start pow
pow: ; 0x020E8564
	ldr ip, _020E856C ; =__ieee754_pow
	bx r12
	.balign 4
_020E856C: .word __ieee754_pow

	arm_func_start __must_round
__must_round: ; 0x020E8570
	add r3, r0, #0x5
	ldrb r2, [r3, r1]
	add r12, r3, r1
	cmp r2, #0x5
	movhi r0, #0x1
	bxhi lr
	mvncc r0, #0x0
	bxcc lr
	ldrb r2, [r0, #0x4]
	add r12, r12, #0x1
	add r3, r3, r2
	cmp r12, r3
	bhs _020E85C0
_020E85A4:
	ldrb r2, [r12, #0x0]
	cmp r2, #0x0
	movne r0, #0x1
	bxne lr
	add r12, r12, #0x1
	cmp r12, r3
	blo _020E85A4
_020E85C0:
	sub r1, r1, #0x1
	add r0, r0, r1
	ldrb r0, [r0, #0x5]
	tst r0, #0x1
	movne r0, #0x1
	mvneq r0, #0x0
	bx lr

	arm_func_start __dorounddecup
__dorounddecup: ; 0x020E85DC
	add r3, r0, #0x5
	add r1, r3, r1
	sub r12, r1, #0x1
	mov r1, #0x0
_020E85EC:
	ldrb r2, [r12, #0x0]
	cmp r2, #0x9
	addcc r0, r2, #0x1
	strccb r0, [r12, #0x0]
	bxcc lr
	cmp r12, r3
	bne _020E8620
	mov r1, #0x1
	strb r1, [r12, #0x0]
	ldrsh r1, [r0, #0x2]
	add r1, r1, #0x1
	strh r1, [r0, #0x2]
	bx lr
_020E8620:
	strb r1, [r12], #-0x1
	b _020E85EC
	bx lr

	arm_func_start __rounddec
__rounddec: ; 0x020E862C
	stmdb sp!, {r3-r5,lr}
	mov r4, r1
	mov r5, r0
	cmp r4, #0x0
	ldmleia sp!, {r3-r5,pc}
	ldrb r2, [r5, #0x4]
	cmp r4, r2
	ldmgeia sp!, {r3-r5,pc}
	bl __must_round
	strb r4, [r5, #0x4]
	cmp r0, #0x0
	ldmltia sp!, {r3-r5,pc}
	mov r0, r5
	mov r1, r4
	bl __dorounddecup
	ldmia sp!, {r3-r5,pc}

	arm_func_start __ull2dec
__ull2dec: ; 0x020E866C
	stmdb sp!, {r3-r11,lr}
	mov r10, r0
	mov r0, #0x0
	mov r8, r2
	strb r0, [r10, #0x0]
	mov r9, r1
	cmp r8, #0x0
	strb r0, [r10, #0x4]
	cmpeq r9, #0x0
	beq _020E86F8
	mov r6, #0xa
	mov r11, r0
	mov r5, r0
	mov r4, r0
_020E86A4:
	ldrb r1, [r10, #0x4]
	mov r0, r9
	mov r2, r6
	add r3, r1, #0x1
	mov r7, r1
	strb r3, [r10, #0x4]
	mov r1, r8
	mov r3, r11
	bl _ull_mod
	add r1, r10, r7
	strb r0, [r1, #0x5]
	mov r0, r9
	mov r1, r8
	mov r2, #0xa
	mov r3, #0x0
	bl _ll_udiv
	mov r8, r1
	mov r9, r0
	cmp r8, r5
	cmpeq r9, r4
	bne _020E86A4
_020E86F8:
	ldrb r0, [r10, #0x4]
	add r2, r10, #0x5
	add r0, r2, r0
	sub r3, r0, #0x1
	cmp r2, r3
	bhs _020E8728
_020E8710:
	ldrb r0, [r3, #0x0]
	ldrb r1, [r2, #0x0]
	strb r0, [r2], #0x1
	strb r1, [r3], #-0x1
	cmp r2, r3
	blo _020E8710
_020E8728:
	ldrb r0, [r10, #0x4]
	sub r0, r0, #0x1
	strh r0, [r10, #0x2]
	ldmia sp!, {r3-r11,pc}

	arm_func_start __timesdec
__timesdec: ; 0x020E8738
	stmdb sp!, {r3-r11,lr}
	sub sp, sp, #0x40
	ldrb r6, [r1, #0x4]
	ldrb r5, [r2, #0x4]
	mov r4, #0x0
	add r3, sp, #0x0
	add r5, r6, r5
	sub r5, r5, #0x1
	add r3, r3, r5
	add r6, r3, #0x1
	mov r7, r6
	strb r4, [r0, #0x0]
	cmp r5, #0x0
	ble _020E8800
	add lr, r1, #0x5
	add r11, r2, #0x5
_020E8778:
	ldrb r3, [r2, #0x4]
	sub r10, r3, #0x1
	sub r3, r5, r10
	subs r9, r3, #0x1
	ldrb r3, [r1, #0x4]
	movmi r9, #0x0
	submi r10, r5, #0x1
	add r8, r10, #0x1
	sub r3, r3, r9
	cmp r8, r3
	movgt r8, r3
	add r10, r11, r10
	add r9, lr, r9
	cmp r8, #0x0
	ble _020E87CC
_020E87B4:
	ldrb r12, [r9], #0x1
	ldrb r3, [r10], #-0x1
	sub r8, r8, #0x1
	cmp r8, #0x0
	mla r4, r12, r3, r4
	bgt _020E87B4
_020E87CC:
	ldr r3, _020E88B8 ; =0xCCCCCCCD
	sub r5, r5, #0x1
	umull r8, r9, r4, r3
	mov r9, r9, lsr #0x3
	cmp r5, #0x0
	mov r10, #0xa
	umull r8, r9, r10, r9
	sub r9, r4, r8
	strb r9, [r6, #-0x1]!
	mov r8, r4
	umull r3, r4, r8, r3
	mov r4, r4, lsr #0x3
	bgt _020E8778
_020E8800:
	ldrsh r3, [r1, #0x2]
	ldrsh r1, [r2, #0x2]
	cmp r4, #0x0
	add r1, r3, r1
	strh r1, [r0, #0x2]
	beq _020E8828
	strb r4, [r6, #-0x1]!
	ldrsh r1, [r0, #0x2]
	add r1, r1, #0x1
	strh r1, [r0, #0x2]
_020E8828:
	mov r3, #0x0
	b _020E8840
_020E8830:
	ldrb r2, [r6], #0x1
	add r1, r0, r3
	add r3, r3, #0x1
	strb r2, [r1, #0x5]
_020E8840:
	cmp r3, #0x20
	bge _020E8850
	cmp r6, r7
	blo _020E8830
_020E8850:
	cmp r6, r7
	addcs sp, sp, #0x40
	strb r3, [r0, #0x4]
	ldmcsia sp!, {r3-r11,pc}
	ldrb r1, [r6, #0x0]
	cmp r1, #0x5
	addcc sp, sp, #0x40
	ldmccia sp!, {r3-r11,pc}
	bne _020E88A8
	add r2, r6, #0x1
	cmp r2, r7
	bhs _020E8898
_020E8880:
	ldrb r1, [r2, #0x0]
	cmp r1, #0x0
	bne _020E88A8
	add r2, r2, #0x1
	cmp r2, r7
	blo _020E8880
_020E8898:
	ldrb r1, [r6, #-0x1]
	tst r1, #0x1
	addeq sp, sp, #0x40
	ldmeqia sp!, {r3-r11,pc}
_020E88A8:
	ldrb r1, [r0, #0x4]
	bl __dorounddecup
	add sp, sp, #0x40
	ldmia sp!, {r3-r11,pc}
	.balign 4
_020E88B8: .word 0xCCCCCCCD

	arm_func_start __str2dec
__str2dec: ; 0x020E88BC
	stmdb sp!, {r3,lr}
	strh r2, [r0, #0x2]
	mov r12, #0x0
	strb r12, [r0, #0x0]
	b _020E88E4
_020E88D0:
	ldrsb r3, [r1], #0x1
	add r2, r0, r12
	add r12, r12, #0x1
	sub r3, r3, #0x30
	strb r3, [r2, #0x5]
_020E88E4:
	cmp r12, #0x20
	bge _020E88F8
	ldrsb r2, [r1, #0x0]
	cmp r2, #0x0
	bne _020E88D0
_020E88F8:
	strb r12, [r0, #0x4]
	ldrsb r2, [r1, #0x0]
	cmp r2, #0x0
	ldmeqia sp!, {r3,pc}
	cmp r2, #0x5
	ldmltia sp!, {r3,pc}
	bgt _020E894C
	ldrsb r2, [r1, #0x1]
	add r1, r1, #0x1
	cmp r2, #0x0
	beq _020E8938
_020E8924:
	cmp r2, #0x30
	bne _020E894C
	ldrsb r2, [r1, #0x1]!
	cmp r2, #0x0
	bne _020E8924
_020E8938:
	sub r1, r12, #0x1
	add r1, r0, r1
	ldrb r1, [r1, #0x5]
	tst r1, #0x1
	ldmeqia sp!, {r3,pc}
_020E894C:
	ldrb r1, [r0, #0x4]
	bl __dorounddecup
	ldmia sp!, {r3,pc}

	arm_func_start __two_exp
__two_exp: ; 0x020E8958
	stmdb sp!, {r4-r5,lr}
	sub sp, sp, #0x4c
	mov r4, r1
	mvn r2, #0x34
	mov r5, r0
	cmp r4, r2
	bgt _020E8988
	bge _020E8A54
	sub r0, r2, #0xb
	cmp r4, r0
	beq _020E8A3C
	b _020E8BE4
_020E8988:
	add r1, r4, #0x20
	cmp r1, #0x28
	addls pc, pc, r1, lsl #0x2
	b _020E8BE4
	b _020E8A68 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8A7C ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8BE4 ; case
	b _020E8A90 ; case
	b _020E8AA4 ; case
	b _020E8AB8 ; case
	b _020E8ACC ; case
	b _020E8AE0 ; case
	b _020E8AF4 ; case
	b _020E8B08 ; case
	b _020E8B1C ; case
	b _020E8B30 ; case
	b _020E8B44 ; case
	b _020E8B58 ; case
	b _020E8B6C ; case
	b _020E8B80 ; case
	b _020E8B94 ; case
	b _020E8BA8 ; case
	b _020E8BBC ; case
	b _020E8BD0 ; case
_020E8A3C:
	ldr r1, _020E8C88 ; =UNK_02106E88
	mov r0, r5
	mvn r2, #0x13
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8A54:
	ldr r1, _020E8C8C ; =UNK_02106EB8
	add r2, r2, #0x25
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8A68:
	ldr r1, _020E8C90 ; =UNK_02106EE0
	add r2, r2, #0x2b
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8A7C:
	ldr r1, _020E8C94 ; =UNK_02106EF8
	add r2, r2, #0x30
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8A90:
	ldr r1, _020E8C98 ; =UNK_02106F08
	add r2, r2, #0x32
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8AA4:
	ldr r1, _020E8C9C ; =UNK_02106F10
	add r2, r2, #0x32
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8AB8:
	ldr r1, _020E8CA0 ; =UNK_02106F18
	add r2, r2, #0x33
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8ACC:
	ldr r1, _020E8CA4 ; =UNK_02106F20
	add r2, r2, #0x33
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8AE0:
	ldr r1, _020E8CA8 ; =UNK_02106F28
	add r2, r2, #0x33
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8AF4:
	ldr r1, _020E8CAC ; =UNK_02106F2C
	add r2, r2, #0x34
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B08:
	ldr r1, _020E8CB0 ; =UNK_02106F30
	add r2, r2, #0x34
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B1C:
	ldr r1, _020E8CB4 ; =UNK_02106F34
	add r2, r2, #0x34
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B30:
	ldr r1, _020E8CB8 ; =UNK_02106F38
	mov r2, #0x0
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B44:
	ldr r1, _020E8CBC ; =UNK_02106F3C
	mov r2, #0x0
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B58:
	ldr r1, _020E8CC0 ; =UNK_02106F40
	mov r2, #0x0
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B6C:
	ldr r1, _020E8CC4 ; =UNK_02106F44
	mov r2, #0x0
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B80:
	ldr r1, _020E8CC8 ; =UNK_02106F48
	mov r2, #0x1
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8B94:
	ldr r1, _020E8CCC ; =UNK_02106F4C
	mov r2, #0x1
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8BA8:
	ldr r1, _020E8CD0 ; =UNK_02106F50
	mov r2, #0x1
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8BBC:
	ldr r1, _020E8CD4 ; =UNK_02106F54
	mov r2, #0x2
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8BD0:
	ldr r1, _020E8CD8 ; =UNK_02106F58
	mov r2, #0x2
	bl __str2dec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
_020E8BE4:
	and r0, r4, #0x80000000
	add r1, r4, r0, lsr #0x1f
	add r0, sp, #0x26
	mov r1, r1, asr #0x1
	bl __two_exp
	add r1, sp, #0x26
	mov r0, r5
	mov r2, r1
	bl __timesdec
	tst r4, #0x1
	addeq sp, sp, #0x4c
	ldmeqia sp!, {r4-r5,pc}
	add r3, sp, #0x0
	mov r12, r5
	mov r2, #0x9
_020E8C20:
	ldrh r1, [r12, #0x0]
	ldrh r0, [r12, #0x2]
	add r12, r12, #0x4
	subs r2, r2, #0x1
	strh r1, [r3, #0x0]
	strh r0, [r3, #0x2]
	add r3, r3, #0x4
	bne _020E8C20
	ldrh r0, [r12, #0x0]
	cmp r4, #0x0
	strh r0, [r3, #0x0]
	add r0, sp, #0x26
	ble _020E8C64
	ldr r1, _020E8CBC ; =UNK_02106F3C
	mov r2, #0x0
	bl __str2dec
	b _020E8C70
_020E8C64:
	ldr r1, _020E8CB4 ; =UNK_02106F34
	mvn r2, #0x0
	bl __str2dec
_020E8C70:
	add r1, sp, #0x0
	add r2, sp, #0x26
	mov r0, r5
	bl __timesdec
	add sp, sp, #0x4c
	ldmia sp!, {r4-r5,pc}
	.balign 4
_020E8C88: .word UNK_02106E88
_020E8C8C: .word UNK_02106EB8
_020E8C90: .word UNK_02106EE0
_020E8C94: .word UNK_02106EF8
_020E8C98: .word UNK_02106F08
_020E8C9C: .word UNK_02106F10
_020E8CA0: .word UNK_02106F18
_020E8CA4: .word UNK_02106F20
_020E8CA8: .word UNK_02106F28
_020E8CAC: .word UNK_02106F2C
_020E8CB0: .word UNK_02106F30
_020E8CB4: .word UNK_02106F34
_020E8CB8: .word UNK_02106F38
_020E8CBC: .word UNK_02106F3C
_020E8CC0: .word UNK_02106F40
_020E8CC4: .word UNK_02106F44
_020E8CC8: .word UNK_02106F48
_020E8CCC: .word UNK_02106F4C
_020E8CD0: .word UNK_02106F50
_020E8CD4: .word UNK_02106F54
_020E8CD8: .word UNK_02106F58

	arm_func_start __equals_dec
__equals_dec:
	stmdb sp!, {r4,lr}
	ldrb r3, [r0, #0x5]
	cmp r3, #0x0
	bne _020E8D00
	ldrb r0, [r1, #0x5]
	cmp r0, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	ldmia sp!, {r4,pc}
_020E8D00:
	ldrb r2, [r1, #0x5]
	cmp r2, #0x0
	bne _020E8D1C
	cmp r3, #0x0
	moveq r0, #0x1
	movne r0, #0x0
	ldmia sp!, {r4,pc}
_020E8D1C:
	ldrsh r3, [r0, #0x2]
	ldrsh r2, [r1, #0x2]
	cmp r3, r2
	bne _020E8DB4
	ldrb r4, [r0, #0x4]
	ldrb r2, [r1, #0x4]
	mov r12, #0x0
	mov lr, r4
	cmp r4, r2
	movgt lr, r2
	cmp lr, #0x0
	ble _020E8D74
_020E8D4C:
	add r3, r0, r12
	add r2, r1, r12
	ldrb r3, [r3, #0x5]
	ldrb r2, [r2, #0x5]
	cmp r3, r2
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
	add r12, r12, #0x1
	cmp r12, lr
	blt _020E8D4C
_020E8D74:
	cmp lr, r4
	moveq r0, r1
	ldrb r1, [r0, #0x4]
	cmp r12, r1
	bge _020E8DAC
_020E8D88:
	add r1, r0, r12
	ldrb r1, [r1, #0x5]
	cmp r1, #0x0
	movne r0, #0x0
	ldmneia sp!, {r4,pc}
	ldrb r1, [r0, #0x4]
	add r12, r12, #0x1
	cmp r12, r1
	blt _020E8D88
_020E8DAC:
	mov r0, #0x1
	ldmia sp!, {r4,pc}
_020E8DB4:
	mov r0, #0x0
	ldmia sp!, {r4,pc}

	arm_func_start __less_dec
__less_dec:
	stmdb sp!, {r3-r5,lr}
	ldrb r2, [r0, #0x5]
	cmp r2, #0x0
	bne _020E8DE0
	ldrb r0, [r1, #0x5]
	cmp r0, #0x0
	movne r0, #0x1
	moveq r0, #0x0
	ldmia sp!, {r3-r5,pc}
_020E8DE0:
	ldrb r2, [r1, #0x5]
	cmp r2, #0x0
	moveq r0, #0x0
	ldmeqia sp!, {r3-r5,pc}
	ldrsh r3, [r1, #0x2]
	ldrsh r2, [r0, #0x2]
	cmp r2, r3
	bne _020E8E90
	ldrb r5, [r0, #0x4]
	ldrb r4, [r1, #0x4]
	mov r12, #0x0
	mov lr, r5
	cmp r5, r4
	movgt lr, r4
	cmp lr, #0x0
	ble _020E8E54
_020E8E20:
	add r3, r1, r12
	add r2, r0, r12
	ldrb r3, [r3, #0x5]
	ldrb r2, [r2, #0x5]
	cmp r2, r3
	movcc r0, #0x1
	ldmccia sp!, {r3-r5,pc}
	cmp r3, r2
	movcc r0, #0x0
	ldmccia sp!, {r3-r5,pc}
	add r12, r12, #0x1
	cmp r12, lr
	blt _020E8E20
_020E8E54:
	cmp lr, r5
	bne _020E8E88
	cmp r12, r4
	bge _020E8E88
_020E8E64:
	add r0, r1, r12
	ldrb r0, [r0, #0x5]
	cmp r0, #0x0
	movne r0, #0x1
	ldmneia sp!, {r3-r5,pc}
	ldrb r0, [r1, #0x4]
	add r12, r12, #0x1
	cmp r12, r0
	blt _020E8E64
_020E8E88:
	mov r0, #0x0
	ldmia sp!, {r3-r5,pc}
_020E8E90:
	movlt r0, #0x1
	movge r0, #0x0
	ldmia sp!, {r3-r5,pc}

	arm_func_start __minus_dec
__minus_dec: ; 0x020E8E9C
	stmdb sp!, {r3-r7,lr}
	mov r6, r0
	mov r5, #0x9
_020E8EA8:
	ldrh r4, [r1, #0x0]
	ldrh r3, [r1, #0x2]
	add r1, r1, #0x4
	subs r5, r5, #0x1
	strh r4, [r6, #0x0]
	strh r3, [r6, #0x2]
	add r6, r6, #0x4
	bne _020E8EA8
	ldrh r1, [r1, #0x0]
	strh r1, [r6, #0x0]
	ldrb r1, [r2, #0x5]
	cmp r1, #0x0
	ldmeqia sp!, {r3-r7,pc}
	ldrb r7, [r0, #0x4]
	ldrb r3, [r2, #0x4]
	ldrsh r4, [r0, #0x2]
	mov r1, r7
	cmp r7, r3
	movlt r1, r3
	ldrsh r3, [r2, #0x2]
	sub r6, r4, r3
	add r1, r1, r6
	cmp r1, #0x20
	movgt r1, #0x20
	cmp r7, r1
	bge _020E8F34
	mov r4, #0x0
_020E8F14:
	ldrb r5, [r0, #0x4]
	add r3, r0, r7
	add r5, r5, #0x1
	strb r5, [r0, #0x4]
	strb r4, [r3, #0x5]
	ldrb r7, [r0, #0x4]
	cmp r7, r1
	blt _020E8F14
_020E8F34:
	ldrb r4, [r2, #0x4]
	add r3, r0, #0x5
	add r12, r3, r1
	add r4, r4, r6
	cmp r4, r1
	addlt r12, r3, r4
	sub r4, r12, r3
	add r1, r2, #0x5
	sub r4, r4, r6
	add lr, r1, r4
	mov r4, lr
	b _020E8FC8
_020E8F64:
	ldrb r7, [r12, #-0x1]!
	ldrb r5, [lr, #-0x1]!
	cmp r7, r5
	bhs _020E8FB8
	ldrb r7, [r12, #-0x1]
	sub r5, r12, #0x1
	cmp r7, #0x0
	bne _020E8F90
_020E8F84:
	ldrb r7, [r5, #-0x1]!
	cmp r7, #0x0
	beq _020E8F84
_020E8F90:
	cmp r5, r12
	beq _020E8FB8
_020E8F98:
	ldrb r7, [r5, #0x0]
	sub r7, r7, #0x1
	strb r7, [r5, #0x0]
	ldrb r7, [r5, #0x1]!
	cmp r5, r12
	add r7, r7, #0xa
	strb r7, [r5, #0x0]
	bne _020E8F98
_020E8FB8:
	ldrb r7, [r12, #0x0]
	ldrb r5, [lr, #0x0]
	sub r5, r7, r5
	strb r5, [r12, #0x0]
_020E8FC8:
	cmp r12, r3
	cmphi lr, r1
	bhi _020E8F64
	ldrb r5, [r2, #0x4]
	sub lr, r4, r1
	cmp lr, r5
	bge _020E90A4
	ldrb r1, [r4, #0x0]
	mov r7, #0x0
	cmp r1, #0x5
	movcc r7, #0x1
	blo _020E9040
	bne _020E9040
	add r1, r2, #0x5
	add r2, r1, r5
	add r4, r4, #0x1
	cmp r4, r2
	bhs _020E9028
_020E9010:
	ldrb r1, [r4, #0x0]
	cmp r1, #0x0
	bne _020E90A4
	add r4, r4, #0x1
	cmp r4, r2
	blo _020E9010
_020E9028:
	add r1, r3, lr
	add r2, r1, r6
	ldrb r1, [r2, #-0x1]
	sub r12, r2, #0x1
	tst r1, #0x1
	movne r7, #0x1
_020E9040:
	cmp r7, #0x0
	beq _020E90A4
	ldrb r1, [r12, #0x0]
	cmp r1, #0x1
	bhs _020E9098
	ldrb r1, [r12, #-0x1]
	sub r2, r12, #0x1
	cmp r1, #0x0
	bne _020E9070
_020E9064:
	ldrb r1, [r2, #-0x1]!
	cmp r1, #0x0
	beq _020E9064
_020E9070:
	cmp r2, r12
	beq _020E9098
_020E9078:
	ldrb r1, [r2, #0x0]
	sub r1, r1, #0x1
	strb r1, [r2, #0x0]
	ldrb r1, [r2, #0x1]!
	cmp r2, r12
	add r1, r1, #0xa
	strb r1, [r2, #0x0]
	bne _020E9078
_020E9098:
	ldrb r1, [r12, #0x0]
	sub r1, r1, #0x1
	strb r1, [r12, #0x0]
_020E90A4:
	ldrb r1, [r3, #0x0]
	mov r5, r3
	cmp r1, #0x0
	bne _020E90C0
_020E90B4:
	ldrb r1, [r5, #0x1]!
	cmp r1, #0x0
	beq _020E90B4
_020E90C0:
	cmp r5, r3
	bls _020E9108
	ldrsh r1, [r0, #0x2]
	sub r2, r5, r3
	and r4, r2, #0xff
	sub r1, r1, r4
	strh r1, [r0, #0x2]
	ldrb r1, [r0, #0x4]
	add r2, r3, r1
	cmp r5, r2
	bhs _020E90FC
_020E90EC:
	ldrb r1, [r5], #0x1
	cmp r5, r2
	strb r1, [r3], #0x1
	blo _020E90EC
_020E90FC:
	ldrb r1, [r0, #0x4]
	sub r1, r1, r4
	strb r1, [r0, #0x4]
_020E9108:
	ldrb r1, [r0, #0x4]
	add r2, r0, #0x5
	add r3, r2, r1
	cmp r3, r2
	bls _020E9130
_020E911C:
	ldrb r1, [r3, #-0x1]!
	cmp r1, #0x0
	bne _020E9130
	cmp r3, r2
	bhi _020E911C
_020E9130:
	sub r1, r3, r2
	add r1, r1, #0x1
	strb r1, [r0, #0x4]
	ldmia sp!, {r3-r7,pc}

	arm_func_start __num2dec_internal
__num2dec_internal:
	stmdb sp!, {r4-r8,lr}
	sub sp, sp, #0x58
	mov r8, r1
	mov r6, r2
	mov r7, r0
	mov r0, r8
	mov r1, r6
	bl __signbitf
	cmp r0, #0x0
	movne r1, #0x1
	moveq r1, #0x0
	mov r4, r1, lsl #0x18
	mov r0, #0x0
	mov r1, r0
	mov r2, r8
	mov r3, r6
	mov r5, r4, asr #0x18
	bl _deq
	bne _020E91AC
	strb r5, [r7, #0x0]
	mov r1, #0x0
	strh r1, [r7, #0x2]
	mov r0, #0x1
	strb r0, [r7, #0x4]
	add sp, sp, #0x58
	strb r1, [r7, #0x5]
	ldmia sp!, {r4-r8,pc}
_020E91AC:
	mov r0, r8
	mov r1, r6
	bl __fpclassifyf
	cmp r0, #0x2
	bgt _020E91F8
	strb r5, [r7, #0x0]
	mov r2, #0x0
	strh r2, [r7, #0x2]
	mov r2, #0x1
	mov r0, r8
	mov r1, r6
	strb r2, [r7, #0x4]
	bl __fpclassifyf
	cmp r0, #0x1
	moveq r0, #0x4e
	movne r0, #0x49
	add sp, sp, #0x58
	strb r0, [r7, #0x5]
	ldmia sp!, {r4-r8,pc}
_020E91F8:
	cmp r5, #0x0
	beq _020E921C
	mov r0, #0x0
	mov r1, r0
	mov r2, r8
	mov r3, r6
	bl _dsub
	mov r8, r0
	mov r6, r1
_020E921C:
	add r2, sp, #0x8
	mov r0, r8
	mov r1, r6
	bl frexp
	mov r4, r0
	mov r6, r1
	orr r12, r4, #0x0
	rsbs r2, r12, #0x0
	orr r3, r6, #0x100000
	rsc r1, r3, #0x0
	mov r0, #0x0
	and r3, r3, r1
	sub r1, r0, #0x1
	and r12, r12, r2
	mov r2, r1
	adds r0, r12, r1
	adc r1, r3, r2
	str r4, [sp, #0x0]
	str r6, [sp, #0x4]
	bl __msl_generic_count_bits64
	rsb r8, r0, #0x35
	ldr r1, [sp, #0x8]
	add r0, sp, #0xc
	sub r1, r1, r8
	bl __two_exp
	mov r0, r4
	mov r1, r6
	mov r2, r8
	bl ldexp
	bl _ll_ufrom_d
	mov r2, r1
	mov r1, r0
	add r0, sp, #0x32
	bl __ull2dec
	mov r0, r7
	add r1, sp, #0x32
	add r2, sp, #0xc
	bl __timesdec
	strb r5, [r7, #0x0]
	add sp, sp, #0x58
	ldmia sp!, {r4-r8,pc}

	arm_func_start __num2dec_internal2
__num2dec_internal2: ; 0x020E92C0
	stmdb sp!, {r3-r5,lr}
	mov r4, r3
	ldrsh r5, [r0, #0x2]
	mov r0, r4
	bl __num2dec_internal
	ldrb r0, [r4, #0x5]
	cmp r0, #0x9
	ldmhiia sp!, {r3-r5,pc}
	cmp r5, #0x20
	movgt r5, #0x20
	mov r0, r4
	mov r1, r5
	bl __rounddec
	ldrb r0, [r4, #0x4]
	cmp r0, r5
	bge _020E9324
	mov r1, #0x0
_020E9304:
	ldrb r2, [r4, #0x4]
	add r0, r4, r0
	add r2, r2, #0x1
	strb r2, [r4, #0x4]
	strb r1, [r0, #0x5]
	ldrb r0, [r4, #0x4]
	cmp r0, r5
	blt _020E9304
_020E9324:
	ldrsh r1, [r4, #0x2]
	sub r0, r0, #0x1
	mov r2, #0x0
	sub r0, r1, r0
	strh r0, [r4, #0x2]
	ldrb r0, [r4, #0x4]
	cmp r0, #0x0
	ldmleia sp!, {r3-r5,pc}
_020E9344:
	add r1, r4, r2
	ldrb r0, [r1, #0x5]
	add r2, r2, #0x1
	add r0, r0, #0x30
	strb r0, [r1, #0x5]
	ldrb r0, [r4, #0x4]
	cmp r2, r0
	blt _020E9344
	ldmia sp!, {r3-r5,pc}

	arm_func_start __dec2num
__dec2num: ; 0x020E9368
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0xfc
	mov r4, r0
	ldrb r0, [r4, #0x4]
	cmp r0, #0x0
	bne _020E93A8
	ldrsb r0, [r4, #0x0]
	mov r2, #0x0
	cmp r0, #0x0
	ldreq r3, _020E996C ; =0x3FF00000
	mov r0, #0x0
	ldrne r3, _020E9970 ; =0xBFF00000
	mov r1, r0
	bl copysign
	add sp, sp, #0xfc
	ldmia sp!, {r4-r11,pc}
_020E93A8:
	ldrb r0, [r4, #0x5]
	cmp r0, #0x30
	beq _020E93C8
	cmp r0, #0x49
	beq _020E93F0
	cmp r0, #0x4e
	beq _020E9424
	b _020E946C
_020E93C8:
	ldrsb r0, [r4, #0x0]
	mov r2, #0x0
	cmp r0, #0x0
	ldreq r3, _020E996C ; =0x3FF00000
	mov r0, #0x0
	ldrne r3, _020E9970 ; =0xBFF00000
	mov r1, r0
	bl copysign
	add sp, sp, #0xfc
	ldmia sp!, {r4-r11,pc}
_020E93F0:
	ldrsb r0, [r4, #0x0]
	mov r5, #0x0
	cmp r0, #0x0
	ldreq r4, _020E996C ; =0x3FF00000
	ldr r0, _020E9974 ; =__float_huge
	ldrne r4, _020E9970 ; =0xBFF00000
	ldr r0, [r0, #0x0]
	bl _f2d
	mov r2, r5
	mov r3, r4
	bl copysign
	add sp, sp, #0xfc
	ldmia sp!, {r4-r11,pc}
_020E9424:
	ldr r1, _020E9978 ; =0x7FF00000
	add r3, sp, #0x10
	mov r2, #0x0
	str r2, [r3, #0x0]
	str r1, [r3, #0x4]
	ldrsb r0, [r4, #0x0]
	cmp r0, #0x0
	beq _020E9454
	orr r0, r1, #0x80000000
	orr r1, r2, r2
	str r1, [r3, #0x0]
	str r0, [r3, #0x4]
_020E9454:
	ldmia r3, {r0-r1}
	orr r0, r0, #0x0
	orr r1, r1, #0x80000
	stmia r3, {r0-r1}
	add sp, sp, #0xfc
	ldmia sp!, {r4-r11,pc}
_020E946C:
	add r3, sp, #0xd6
	mov r5, r4
	mov r2, #0x9
_020E9478:
	ldrh r1, [r5, #0x0]
	ldrh r0, [r5, #0x2]
	add r5, r5, #0x4
	subs r2, r2, #0x1
	strh r1, [r3, #0x0]
	strh r0, [r3, #0x2]
	add r3, r3, #0x4
	bne _020E9478
	ldrh r0, [r5, #0x0]
	add r1, sp, #0xdb
	strh r0, [r3, #0x0]
	ldrb r0, [sp, #0xda]
	add r5, r1, r0
	cmp r1, r5
	bhs _020E94C8
_020E94B4:
	ldrb r0, [r1, #0x0]
	sub r0, r0, #0x30
	strb r0, [r1], #0x1
	cmp r1, r5
	blo _020E94B4
_020E94C8:
	ldrb r1, [sp, #0xda]
	ldrsh r2, [sp, #0xd8]
	add r0, sp, #0xb0
	sub r1, r1, #0x1
	add r1, r2, r1
	strh r1, [sp, #0xd8]
	ldr r1, _020E997C ; =UNK_02106F5C
	mov r2, #0x134
	ldrsh r11, [sp, #0xd8]
	bl __str2dec
	add r0, sp, #0xb0
	add r1, sp, #0xd6
	bl __less_dec
	cmp r0, #0x0
	beq _020E9538
	ldrsb r0, [r4, #0x0]
	mov r5, #0x0
	cmp r0, #0x0
	ldreq r4, _020E996C ; =0x3FF00000
	ldr r0, _020E9974 ; =__float_huge
	ldrne r4, _020E9970 ; =0xBFF00000
	ldr r0, [r0, #0x0]
	bl _f2d
	mov r2, r5
	mov r3, r4
	bl copysign
	add sp, sp, #0xfc
	ldmia sp!, {r4-r11,pc}
_020E9538:
	add r1, sp, #0xdb
	ldrb r0, [r1, #0x0]
	add r8, r1, #0x1
	bl _dfltu
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	cmp r8, r5
	bhs _020E9610
_020E9558:
	sub r0, r5, r8
	mov r1, r0, lsr #0x1f
	rsb r0, r1, r0, lsl #0x1d
	adds r7, r1, r0, ror #0x1d
	moveq r7, #0x8
	mov r6, #0x0
	mov r2, #0x0
	cmp r7, #0x0
	ble _020E9594
	mov r0, #0xa
_020E9580:
	ldrb r1, [r8], #0x1
	add r2, r2, #0x1
	cmp r2, r7
	mla r6, r0, r6, r1
	blt _020E9580
_020E9594:
	ldr r0, _020E9980 ; =UNK_02106E48
	ldr r1, [sp, #0xc]
	add r3, r0, r7, lsl #0x3
	ldr r2, [r3, #-0x8]
	ldr r0, [sp, #0x8]
	ldr r3, [r3, #-0x4]
	bl _dmul
	mov r4, r0
	mov r9, r1
	mov r0, r6
	bl _dfltu
	mov r2, r0
	mov r3, r1
	mov r0, r4
	mov r1, r9
	bl _dadd
	cmp r6, #0x0
	mov r6, r0
	mov r10, r1
	beq _020E95FC
	mov r0, r4
	mov r1, r9
	mov r2, r6
	mov r3, r10
	bl _deq
	beq _020E9610
_020E95FC:
	str r6, [sp, #0x8]
	str r10, [sp, #0xc]
	cmp r8, r5
	sub r11, r11, r7
	blo _020E9558
_020E9610:
	cmp r11, #0x0
	bge _020E9654
	rsb r0, r11, #0x0
	bl _dflt
	mov r3, r1
	mov r2, r0
	ldr r1, _020E9984 ; =0x40140000
	mov r0, #0x0
	bl pow
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	bl _ddiv
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	b _020E968C
_020E9654:
	mov r0, r11
	bl _dflt
	mov r3, r1
	mov r2, r0
	ldr r1, _020E9984 ; =0x40140000
	mov r0, #0x0
	bl pow
	mov r2, r0
	mov r3, r1
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	bl _dmul
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
_020E968C:
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	mov r2, r11
	bl ldexp
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
	bl __fpclassifyf
	cmp r0, #0x2
	bne _020E96C0
	ldr r0, _020E9988 ; =0x7FEFFFFF
	mvn r1, #0x0
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
_020E96C0:
	ldr r1, [sp, #0x8]
	ldr r2, [sp, #0xc]
	add r0, sp, #0x8a
	add r4, sp, #0x0
	mov r5, #0x0
	bl __num2dec_internal
	add r0, sp, #0x8a
	add r1, sp, #0xd6
	bl __equals_dec
	cmp r0, #0x0
	bne _020E9934
	add r0, sp, #0x8a
	add r1, sp, #0xd6
	bl __less_dec
	cmp r0, #0x0
	movne r5, #0x1
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	cmp r5, #0x0
	moveq r6, #0x1
	str r1, [sp, #0x0]
	str r0, [sp, #0x4]
	movne r6, #0x0
_020E971C:
	cmp r6, #0x0
	bne _020E9744
	ldmia r4, {r0-r1}
	adds r0, r0, #0x1
	adc r1, r1, #0x0
	stmia r4, {r0-r1}
	bl __fpclassifyf
	cmp r0, #0x2
	beq _020E9934
	b _020E975C
_020E9744:
	ldr r1, [r4, #0x0]
	ldr r0, [r4, #0x4]
	subs r1, r1, #0x1
	sbc r0, r0, #0x0
	str r1, [r4, #0x0]
	str r0, [r4, #0x4]
_020E975C:
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0x4]
	add r0, sp, #0x64
	bl __num2dec_internal
	cmp r5, #0x0
	beq _020E9788
	add r0, sp, #0x64
	add r1, sp, #0xd6
	bl __less_dec
	cmp r0, #0x0
	beq _020E98AC
_020E9788:
	cmp r5, #0x0
	bne _020E9864
	add r0, sp, #0xd6
	add r1, sp, #0x64
	bl __less_dec
	cmp r0, #0x0
	bne _020E9864
	add r3, sp, #0x8a
	add r5, sp, #0x3e
	mov r2, #0x9
_020E97B0:
	ldrh r1, [r3, #0x0]
	ldrh r0, [r3, #0x2]
	add r3, r3, #0x4
	strh r1, [r5, #0x0]
	strh r0, [r5, #0x2]
	add r5, r5, #0x4
	subs r2, r2, #0x1
	bne _020E97B0
	ldrh r0, [r3, #0x0]
	add r3, sp, #0x64
	add r4, sp, #0x8a
	strh r0, [r5, #0x0]
	mov r2, #0x9
_020E97E4:
	ldrh r1, [r3, #0x0]
	ldrh r0, [r3, #0x2]
	add r3, r3, #0x4
	strh r1, [r4, #0x0]
	strh r0, [r4, #0x2]
	add r4, r4, #0x4
	subs r2, r2, #0x1
	bne _020E97E4
	ldrh r0, [r3, #0x0]
	add r3, sp, #0x3e
	add r5, sp, #0x64
	strh r0, [r4, #0x0]
	mov r2, #0x9
_020E9818:
	ldrh r1, [r3, #0x0]
	ldrh r0, [r3, #0x2]
	add r3, r3, #0x4
	strh r1, [r5, #0x0]
	strh r0, [r5, #0x2]
	add r5, r5, #0x4
	subs r2, r2, #0x1
	bne _020E9818
	ldrh r4, [r3, #0x0]
	ldr r3, [sp, #0x8]
	ldr r1, [sp, #0x0]
	ldr r2, [sp, #0xc]
	ldr r0, [sp, #0x4]
	strh r4, [r5, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	str r3, [sp, #0x0]
	str r2, [sp, #0x4]
	b _020E98AC
_020E9864:
	add r7, sp, #0x64
	add r3, sp, #0x8a
	mov r2, #0x9
_020E9870:
	ldrh r1, [r7, #0x0]
	ldrh r0, [r7, #0x2]
	add r7, r7, #0x4
	strh r1, [r3, #0x0]
	strh r0, [r3, #0x2]
	add r3, r3, #0x4
	subs r2, r2, #0x1
	bne _020E9870
	ldrh r2, [r7, #0x0]
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	strh r2, [r3, #0x0]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	b _020E971C
_020E98AC:
	add r0, sp, #0x3e
	add r1, sp, #0xd6
	add r2, sp, #0x8a
	bl __minus_dec
	add r0, sp, #0x18
	add r1, sp, #0x64
	add r2, sp, #0xd6
	bl __minus_dec
	add r0, sp, #0x3e
	add r1, sp, #0x18
	bl __equals_dec
	cmp r0, #0x0
	beq _020E9910
	ldr r1, [sp, #0x8]
	ldr r0, [sp, #0xc]
	and r1, r1, #0x1
	and r0, r0, #0x0
	cmp r0, #0x0
	cmpeq r1, #0x0
	beq _020E9934
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	b _020E9934
_020E9910:
	add r0, sp, #0x3e
	add r1, sp, #0x18
	bl __less_dec
	cmp r0, #0x0
	bne _020E9934
	ldr r1, [sp, #0x0]
	ldr r0, [sp, #0x4]
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
_020E9934:
	ldrsb r0, [sp, #0xd6]
	cmp r0, #0x0
	beq _020E995C
	mov r0, #0x0
	ldr r2, [sp, #0x8]
	ldr r3, [sp, #0xc]
	mov r1, r0
	bl _dsub
	str r0, [sp, #0x8]
	str r1, [sp, #0xc]
_020E995C:
	ldr r0, [sp, #0x8]
	ldr r1, [sp, #0xc]
	add sp, sp, #0xfc
	ldmia sp!, {r4-r11,pc}
	.balign 4
_020E996C: .word 0x3FF00000
_020E9970: .word 0xBFF00000
_020E9974: .word __float_huge
_020E9978: .word 0x7FF00000
_020E997C: .word UNK_02106F5C
_020E9980: .word UNK_02106E48
_020E9984: .word 0x40140000
_020E9988: .word 0x7FEFFFFF

	arm_func_start __msl_generic_count_bits64
__msl_generic_count_bits64: ; 0x020E998C
	mov r3, r0, lsr #0x1
	ldr r2, _020E9A14 ; =0x55555555
	orr r3, r3, r1, lsl #0x1f
	and r3, r3, r2
	subs r12, r0, r3
	and r2, r2, r1, lsr #0x1
	ldr r0, _020E9A18 ; =0x33333333
	sbc r3, r1, r2
	mov r1, r12, lsr #0x2
	orr r1, r1, r3, lsl #0x1e
	and r2, r12, r0
	and r1, r1, r0
	adds r2, r2, r1
	and r1, r3, r0
	and r0, r0, r3, lsr #0x2
	adc r1, r1, r0
	mov r0, r2, lsr #0x4
	orr r0, r0, r1, lsl #0x1c
	adds r2, r2, r0
	ldr r0, _020E9A1C ; =0x0F0F0F0F
	adc r1, r1, r1, lsr #0x4
	and r3, r2, r0
	and r2, r1, r0
	mov r0, r3, lsr #0x8
	orr r0, r0, r2, lsl #0x18
	adds r1, r3, r0
	adc r2, r2, r2, lsr #0x8
	mov r0, r1, lsr #0x10
	orr r0, r0, r2, lsl #0x10
	adds r1, r1, r0
	adc r0, r2, r2, lsr #0x10
	adds r0, r1, r0
	and r0, r0, #0xff
	bx lr
	.balign 4
_020E9A14: .word 0x55555555
_020E9A18: .word 0x33333333
_020E9A1C: .word 0x0F0F0F0F

	arm_func_start __signbitf
__signbitf:
	stmdb sp!, {r0-r3}
	ldr r0, [sp, #0x4]
	and r0, r0, #0x80000000
	add sp, sp, #0x10
	bx lr

	arm_func_start __fpclassifyf
__fpclassifyf: ; 0x020E9A34
	stmdb sp!, {r0-r3}
	ldr r2, [sp, #0x4]
	ldr r0, _020E9A9C ; =0x7FF00000
	ands r1, r2, r0
	beq _020E9A70
	cmp r1, r0
	bne _020E9A90
	ldr r0, _020E9AA0 ; =0x000FFFFF
	tst r2, r0
	ldreq r0, [sp, #0x0]
	add sp, sp, #0x10
	cmpeq r0, #0x0
	movne r0, #0x1
	moveq r0, #0x2
	bx lr
_020E9A70:
	ldr r0, _020E9AA0 ; =0x000FFFFF
	tst r2, r0
	ldreq r0, [sp, #0x0]
	add sp, sp, #0x10
	cmpeq r0, #0x0
	movne r0, #0x5
	moveq r0, #0x3
	bx lr
_020E9A90:
	mov r0, #0x4
	add sp, sp, #0x10
	bx lr
	.balign 4
_020E9A9C: .word 0x7FF00000
_020E9AA0: .word 0x000FFFFF

	arm_func_start scalbn
scalbn: ; 0x020E9AA4
	stmdb sp!, {r3-r4,lr}
	sub sp, sp, #0x4
	mov r4, r2
	add r2, sp, #0x0
	bl frexp
	ldr r2, [sp, #0x0]
	add r2, r2, r4
	str r2, [sp, #0x0]
	bl ldexp
	add sp, sp, #0x4
	ldmia sp!, {r3-r4,pc}

	arm_func_start stricmp
stricmp: ; 0x020E9AD0
	stmdb sp!, {r3,lr}
	ldr r3, _020E9B34 ; =__lower_mapC
_020E9AD8:
	ldrb r2, [r0], #0x1
	cmp r2, #0x0
	blt _020E9AF0
	cmp r2, #0x80
	bge _020E9AF0
	ldrb r2, [r3, r2]
_020E9AF0:
	ldrb lr, [r1], #0x1
	and r12, r2, #0xff
	cmp lr, #0x0
	blt _020E9B0C
	cmp lr, #0x80
	bge _020E9B0C
	ldrb lr, [r3, lr]
_020E9B0C:
	and r2, lr, #0xff
	cmp r12, r2
	mvncc r0, #0x0
	ldmccia sp!, {r3,pc}
	movhi r0, #0x1
	ldmhiia sp!, {r3,pc}
	cmp r12, #0x0
	bne _020E9AD8
	mov r0, #0x0
	ldmia sp!, {r3,pc}
	.balign 4
_020E9B34: .word __lower_mapC

	arm_func_start strnicmp
strnicmp: ; 0x020E9B38
	ldr ip, _020E9B40 ; =stricmp
	bx r12
	.balign 4
_020E9B40: .word stricmp

	.section .exception
	; 0x020EC710
	.global UNK_020EC710
UNK_020EC710: ; 0x020EC710
	.byte 0x20, 0xFF, 0x09, 0x60
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020EC718
UNK_020EC718: ; 0x020EC718
	.byte 0x00, 0xFF, 0x01, 0xB0
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020EC720
UNK_020EC720: ; 0x020EC720
	.byte 0x00, 0xFF, 0x01, 0xD0
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020EC728
UNK_020EC728: ; 0x020EC728
	.byte 0x20, 0xFF, 0x09, 0x60
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020EC730
UNK_020EC730: ; 0x020EC730
	.byte 0x20, 0xFF, 0x11, 0x68
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020EC738
UNK_020EC738: ; 0x020EC738
	.byte 0x20, 0xFF, 0x01, 0xB8
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020EC740
UNK_020EC740: ; 0x020EC740
	.byte 0x00, 0xFF, 0x05, 0x20
	.byte 0x00, 0x00, 0x00, 0x00

	.global UNK_020EC748
UNK_020EC748: ; 0x020EC748
	.word abort
	.short 37
	.word 0x00100000
	.word exit
	.short 77
	.word 0x00100100
	.word __exit
	.short 297
	.word 0x00200300
	.word nan
	.short 25
	.word 0x00000000
	.word __flush_line_buffered_output_files
	.short 141
	.word 0x00403F00
	.word __flush_all
	.short 105
	.word 0x00403F00
	.word __msl_assertion_failed
	.short 61
	.word 0x00200100
	.word __load_buffer
	.short 141
	.word 0x00200700
	.word __flush_buffer
	.short 137
	.word 0x00200300
	.word fread
	.short 269
	.word 0x00407F00
	.word __fread
	.short 841
	.word 0x00507F00
	.word __fwrite
	.short 689
	.word 0x0060FF00
	.word fclose
	.short 117
	.word 0x00200300
	.word fflush
	.short 233
	.word 0x00100100
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
	.word mbtowc
	.short 29
	.word 0x00100000
	.word wctomb
	.short 29
	.word 0x00100000
	.word mbstowcs
	.short 137
	.word 0x00301F00
	.word wcstombs
	.short 121
	.word 0x00403F00
	.word memset
	.short 21
	.word 0x00100100
	.word long2str
	.short 589
	.word 0x0090FF20
	.word longlong2str
	.short 737
	.word 0x00A0FF20
	.word double2hex
	.short 1245
	.word 0x00F07F20
	.word float2str
	.short 1893
	.word 0x00C0FF20
	.word __pformatter
	.short 2084
	.word UNK_020EC710
	.word __FileWrite
	.short 45
	.word 0x00200300
	.word __StringWrite
	.short 69
	.word 0x00200300
	.word printf
	.short 281
	.word 0x00300120
	.word vsnprintf
	.short 105
	.word 0x00300300
	.word snprintf
	.short 41
	.word 0x00300020
	.word sprintf
	.short 45
	.word 0x00300020
	.word qsort
	.short 357
	.word 0x0070FF00
	.word __sformatter
	.short 3412
	.word UNK_020EC718
	.word vsscanf
	.short 85
	.word 0x00200000
	.word sscanf
	.short 41
	.word 0x00300020
	.word raise
	.short 305
	.word 0x00200300
	.word __strtold
	.short 4684
	.word UNK_020EC720
	.word strtold
	.short 225
	.word 0x00500F00
	.word atod
	.short 17
	.word 0x00000000
	.word __strtoul
	.short 1001
	.word 0x0060FF00
	.word __strtoull
	.short 1101
	.word 0x0080FF00
	.word strtoul
	.short 153
	.word 0x00600300
	.word strtol
	.short 201
	.word 0x00600300
	.word atol
	.short 21
	.word 0x00000000
	.word wmemcpy
	.short 17
	.word 0x00000000
	.word long2str_wide
	.short 593
	.word 0x0090FF20
	.word longlong2str_wide
	.short 741
	.word 0x00A0FF20
	.word double2hex_wide
	.short 921
	.word 0x00F07F20
	.word float2str_wide
	.short 1612
	.word UNK_020EC728
	.word __wpformatter
	.short 2288
	.word UNK_020EC730
	.word __wStringWrite
	.short 65
	.word 0x00200300
	.word swprintf
	.short 41
	.word 0x00300020
	.word vswprintf
	.short 113
	.word 0x00300300
	.word __ieee754_pow
	.short 4488
	.word UNK_020EC738
	.word frexp
	.short 189
	.word 0x00300120
	.word ldexp
	.short 589
	.word 0x00300120
	.word pow
	.short 13
	.word 0x00000000
	.word __rounddec
	.short 65
	.word 0x00200300
	.word __ull2dec
	.short 205
	.word 0x0050FF00
	.word __timesdec
	.short 389
	.word 0x00D0FF00
	.word __str2dec
	.short 157
	.word 0x00100000
	.word __two_exp
	.short 901
	.word 0x00B00300
	.word __num2dec_internal
	.short 385
	.word 0x00E01F00
	.word __num2dec_internal2
	.short 169
	.word 0x00200300
	.word __dec2num
	.short 1572
	.word UNK_020EC740
	.word scalbn
	.short 45
