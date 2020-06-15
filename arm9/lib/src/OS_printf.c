#include "global.h"
#include "OS_printf.h"

typedef struct printfStr
{
    s32 spaceLeft;
    s8 *stringEnd;
    s8 *stringStart;
} printfStr;

void string_put_char(struct printfStr *dest, s8 value);
void string_fill_char(struct printfStr *dest, s8 value, s32 count);
void string_put_string(struct printfStr *dest, const s8 *src, s32 count);


#ifndef NONMATCHING
// c definition is at the bottom of the file
u64 _ll_udiv(u64 a, u64 b);

ARM_FUNC asm s32 OS_VSNPrintf(s8 *buffer, s32 bufsz, const s8 *format, void *args)
{
	stmdb sp!, {r4-r11,lr}
	sub sp, sp, #0x64
	mov r9, r2
	str r1, [sp, #0x54]
	str r0, [sp, #0x5c]
	str r0, [sp, #0x58]
	ldrsb r0, [r9, #0x0]
	str r1, [sp, #0x0]
	mov r11, r3
	cmp r0, #0x0
	beq _020CAD18
	mov r0, #0xa
	str r0, [sp, #0xc]
	mov r0, #0x0
	str r0, [sp, #0x4]
	mov r0, #0x20
	str r0, [sp, #0x1c]
	mov r0, #0x30
	str r0, [sp, #0x20]
	mvn r0, #0x0
	str r0, [sp, #0x8]
	mov r0, #0x57
	str r0, [sp, #0x10]
	mov r0, #0x8
	str r0, [sp, #0x14]
	mov r0, #0x37
	str r0, [sp, #0x18]
	mov r0, #0x10
	str r0, [sp, #0x24]
	mov r0, #0x1
	str r0, [sp, #0x28]
	mov r0, #0x2b
	str r0, [sp, #0x34]
	mov r0, #0x2d
	str r0, [sp, #0x30]
	mov r0, #0x2
	str r0, [sp, #0x2c]
_020CA530:
	ldrsb r1, [r9, #0x0]
	and r0, r1, #0xff
	eor r0, r0, #0x20
	sub r0, r0, #0xa1
	cmp r0, #0x3c
	bhs _020CA56C
	add r0, sp, #0x54
	bl string_put_char
	ldrsb r1, [r9, #0x1]!
	cmp r1, #0x0
	beq _020CAD0C
	add r0, sp, #0x54
	add r9, r9, #0x1
	bl string_put_char
	b _020CAD0C
_020CA56C:
	cmp r1, #0x25
	beq _020CA584
	add r0, sp, #0x54
	add r9, r9, #0x1
	bl string_put_char
	b _020CAD0C
_020CA584:
	ldr r6, [sp, #0x4]
	ldr r5, [sp, #0x8]
	ldr r2, [sp, #0xc]
	ldr r0, [sp, #0x10]
	mov r10, r6
	mov r3, r9
_020CA59C:
	ldrsb r4, [r9, #0x1]!
	cmp r4, #0x20
	bgt _020CA5B4
	cmp r4, #0x20
	beq _020CA5F4
	b _020CA60C
_020CA5B4:
	cmp r4, #0x30
	bgt _020CA60C
	cmp r4, #0x2b
	blt _020CA60C
	cmp r4, #0x2b
	beq _020CA5E0
	cmp r4, #0x2d
	beq _020CA5FC
	cmp r4, #0x30
	beq _020CA604
	b _020CA60C
_020CA5E0:
	ldrsb r1, [r9, #-0x1]
	cmp r1, #0x20
	bne _020CA60C
	orr r6, r6, #0x2
	b _020CA59C
_020CA5F4:
	orr r6, r6, #0x1
	b _020CA59C
_020CA5FC:
	orr r6, r6, #0x8
	b _020CA59C
_020CA604:
	orr r6, r6, #0x10
	b _020CA59C
_020CA60C:
	cmp r4, #0x2a
	bne _020CA640
	add r11, r11, #0x4
	ldr r10, [r11, #-0x4]
	add r9, r9, #0x1
	cmp r10, #0x0
	rsblt r10, r10, #0x0
	orrlt r6, r6, #0x8
	b _020CA654
_020CA630:
	ldrsb r4, [r9], #0x1
	mov r1, #0xa
	mla r1, r10, r1, r4
	sub r10, r1, #0x30
_020CA640:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x30
	blt _020CA654
	cmp r1, #0x39
	ble _020CA630
_020CA654:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x2e
	bne _020CA6AC
	ldrsb r1, [r9, #0x1]!
	ldr r5, [sp, #0x4]
	cmp r1, #0x2a
	bne _020CA698
	add r11, r11, #0x4
	ldr r5, [r11, #-0x4]
	add r9, r9, #0x1
	cmp r5, #0x0
	ldrlt r5, [sp, #0x8]
	b _020CA6AC
_020CA688:
	ldrsb r4, [r9], #0x1
	mov r1, #0xa
	mla r1, r5, r1, r4
	sub r5, r1, #0x30
_020CA698:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x30
	blt _020CA6AC
	cmp r1, #0x39
	ble _020CA688
_020CA6AC:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x68
	beq _020CA6C4
	cmp r1, #0x6c
	beq _020CA6DC
	b _020CA6F0
_020CA6C4: // h
	ldrsb r1, [r9, #0x1]!
	cmp r1, #0x68
	orrne r6, r6, #0x40
	addeq r9, r9, #0x1
	orreq r6, r6, #0x100
	b _020CA6F0
_020CA6DC: // l
	ldrsb r1, [r9, #0x1]!
	cmp r1, #0x6c
	orrne r6, r6, #0x20
	addeq r9, r9, #0x1
	orreq r6, r6, #0x80
_020CA6F0:
	ldrsb r1, [r9, #0x0]
	cmp r1, #0x69
	bgt _020CA740
	cmp r1, #0x63
	blt _020CA720
	cmp r1, #0x63
	beq _020CA7B4
	cmp r1, #0x64
	beq _020CA96C
	cmp r1, #0x69
	beq _020CA96C
	b _020CA950
_020CA720:
	cmp r1, #0x25
	bgt _020CA734
	cmp r1, #0x25
	beq _020CA934
	b _020CA950
_020CA734:
	cmp r1, #0x58
	beq _020CA7A0
	b _020CA950
_020CA740:
	cmp r1, #0x6e
	bgt _020CA754
	cmp r1, #0x6e
	beq _020CA8DC
	b _020CA950
_020CA754:
	sub r1, r1, #0x6f
	cmp r1, #0x9
	addls pc, pc, r1, lsl #0x2
	b _020CA950
_020CA764:
	b _020CA78C
	b _020CA7A8
	b _020CA950
	b _020CA950
	b _020CA828
	b _020CA950
	b _020CA798
	b _020CA950
	b _020CA950
	b _020CA964
_020CA78C:
	ldr r2, [sp, #0x14]
	orr r6, r6, #0x1000
	b _020CA96C
_020CA798:
	orr r6, r6, #0x1000
	b _020CA96C
_020CA7A0:
	ldr r0, [sp, #0x18]
	b _020CA964
_020CA7A8:
	orr r6, r6, #0x4
	ldr r5, [sp, #0x14]
	b _020CA964
_020CA7B4:
	cmp r5, #0x0
	bge _020CA950
	ands r0, r6, #0x8
	add r11, r11, #0x4
	ldr r4, [r11, #-0x4]
	beq _020CA7F0
	mov r0, r4, lsl #0x18
	mov r1, r0, asr #0x18
	add r0, sp, #0x54
	bl string_put_char
	ldr r1, [sp, #0x1c]
	sub r2, r10, #0x1
	add r0, sp, #0x54
	bl string_fill_char
	b _020CA820
_020CA7F0:
	ands r0, r6, #0x10
	ldrne r0, [sp, #0x20]
	sub r2, r10, #0x1
	ldreq r0, [sp, #0x1c]
	mov r0, r0, lsl #0x18
	mov r1, r0, asr #0x18
	add r0, sp, #0x54
	bl string_fill_char
	mov r0, r4, lsl #0x18
	mov r1, r0, asr #0x18
	add r0, sp, #0x54
	bl string_put_char
_020CA820:
	add r9, r9, #0x1
	b _020CAD0C
_020CA828:
	add r11, r11, #0x4
	cmp r5, #0x0
	ldr r7, [sp, #0x4]
	ldr r4, [r11, #-0x4]
	bge _020CA860
	ldrsb r0, [r4]
	cmp r0, #0x0
	beq _020CA874
_020CA848:
	add r7, r7, #0x1
	ldrsb r0, [r4, r7]
	cmp r0, #0x0
	bne _020CA848
	b _020CA874
_020CA85C:
	add r7, r7, #0x1
_020CA860:
	cmp r7, r5
	bge _020CA874
	ldrsb r0, [r4, r7]
	cmp r0, #0x0
	bne _020CA85C
_020CA874:
	ands r0, r6, #0x8
	sub r10, r10, r7
	beq _020CA8A4
	mov r1, r4
	mov r2, r7
	add r0, sp, #0x54
	bl string_put_string
	ldr r1, [sp, #0x1C]
	mov r2, r10
	add r0, sp, #0x54
	bl string_fill_char
	b _020CA8D4
_020CA8A4:
	ands r0, r6, #0x10
	ldrne r0, [sp, #0x20]
	mov r2, r10
	ldreq r0, [sp, #0x1C]
	mov r0, r0, lsl #0x18
	mov r1, r0, asr #0x18
	add r0, sp, #0x54
	bl string_fill_char
	mov r1, r4
	mov r2, r7
	add r0, sp, #0x54
	bl string_put_string
_020CA8D4:
	add r9, r9, #0x1
	b _020CAD0C
_020CA8DC:
	ands r0, r6, #0x100
	ldr r1, [sp, #0x58]
	ldr r0, [sp, #0x5c]
	sub r2, r1, r0
	bne _020CA92C
	ands r0, r6, #0x40
	addne r11, r11, #0x4
	ldrne r0, [r11, #-0x4]
	strneh r2, [r0, #0x0]
	bne _020CA92C
	ands r0, r6, #0x80
	addeq r11, r11, #0x4
	ldreq r0, [r11, #-0x4]
	streq r2, [r0, #0x0]
	beq _020CA92C
	add r11, r11, #0x4
	ldr r0, [r11, #-0x4]
	mov r1, r2, asr #0x1f
	str r2, [r0, #0x0]
	str r1, [r0, #0x4]
_020CA92C:
	add r9, r9, #0x1
	b _020CAD0C
_020CA934:
	add r0, r3, #0x1
	cmp r0, r9
	bne _020CA950
	add r0, sp, #0x54
	add r9, r9, #0x1
	bl string_put_char
	b _020CAD0C
_020CA950:
	add r0, sp, #0x54
	mov r1, r3
	sub r2, r9, r3
	bl string_put_string
	b _020CAD0C
_020CA964:
	ldr r2, [sp, #0x24]
	orr r6, r6, #0x1000
_020CA96C:
	ands r1, r6, #0x8
	bicne r6, r6, #0x10
	cmp r5, #0x0
	bicge r6, r6, #0x10
	ldrlt r5, [sp, #0x28]
	ldr r7, [sp, #0x4]
	ands r1, r6, #0x1000
	beq _020CAA20
	ands r1, r6, #0x100
	addne r11, r11, #0x4
	ldrneb r4, [r11, #-0x4]
	movne r1, #0x0
	bne _020CA9D0
	ands r1, r6, #0x40
	addne r11, r11, #0x4
	ldrneh r4, [r11, #-0x4]
	movne r1, #0x0
	bne _020CA9D0
	ands r1, r6, #0x80
	addne r11, r11, #0x8
	ldrne r1, [r11, #-0x4]
	ldrne r4, [r11, #-0x8]
	addeq r11, r11, #0x4
	ldreq r4, [r11, #-0x4]
	moveq r1, #0x0
_020CA9D0:
	bic r6, r6, #0x3
	ands r3, r6, #0x4
	beq _020CAAD8
	cmp r2, #0x10
	bne _020CAA0C
	mov r3, #0x0
	cmp r1, r3
	cmpeq r4, r3
	beq _020CAAD8
	ldr r3, [sp, #0x20]
	ldr r7, [sp, #0x2c]
	strb r3, [sp, #0x39]
	add r3, r0, #0x21
	strb r3, [sp, #0x38]
	b _020CAAD8
_020CAA0C:
	cmp r2, #0x8
	ldreq r3, [sp, #0x20]
	ldreq r7, [sp, #0x28]
	streqb r3, [sp, #0x38]
	b _020CAAD8
_020CAA20:
	ands r1, r6, #0x100
	addne r11, r11, #0x4
	ldrnesb r4, [r11, #-0x4]
	movne r1, r4, asr #0x1f
	bne _020CAA64
	ands r1, r6, #0x40
	addne r11, r11, #0x4
	ldrnesh r4, [r11, #-0x4]
	movne r1, r4, asr #0x1f
	bne _020CAA64
	ands r1, r6, #0x80
	addne r11, r11, #0x8
	ldrne r4, [r11, #-0x8]
	ldrne r1, [r11, #-0x4]
	addeq r11, r11, #0x4
	ldreq r4, [r11, #-0x4]
	moveq r1, r4, asr #0x1f
_020CAA64:
	mov r3, #0x0
	and r8, r3, #0x0
	cmp r8, r3
	and r8, r1, #0x80000000
	cmpeq r8, r3
	beq _020CAAA0
	ldr r7, [sp, #0x30]
	mvn r4, r4
	strb r7, [sp, #0x38]
	mvn r7, r1
	mov r1, #0x1
	adds r4, r4, r1
	adc r1, r7, r3
	ldr r7, [sp, #0x28]
	b _020CAAD8
_020CAAA0:
	cmp r1, r3
	cmpeq r4, r3
	bne _020CAAB4
	cmp r5, #0x0
	beq _020CAAD8
_020CAAB4:
	ands r3, r6, #0x2
	ldrne r3, [sp, #0x34]
	ldrne r7, [sp, #0x28]
	strneb r3, [sp, #0x38]
	bne _020CAAD8
	ands r3, r6, #0x1
	ldrne r3, [sp, #0x1c]
	ldrne r7, [sp, #0x28]
	strneb r3, [sp, #0x38]
_020CAAD8:
	cmp r2, #0x8
	ldr r8, [sp, #0x4]
	beq _020CAAF8
	cmp r2, #0xa
	beq _020CAB40
	cmp r2, #0x10
	beq _020CABDC
	b _020CAC28
_020CAAF8:
	mov r0, #0x0
	cmp r1, r0
	cmpeq r4, r0
	beq _020CAC28
_020CAB08:
	and r0, r4, #0x7
	add r3, r0, #0x30
	add r0, sp, #0x3a
	strb r3, [r0, r8]
	mov r4, r4, lsr #0x3
	mov r2, #0x0
	mov r0, r1, lsr #0x3
	orr r4, r4, r1, lsl #0x1d
	cmp r0, r2
	cmpeq r4, r2
	mov r1, r0
	add r8, r8, #0x1
	bne _020CAB08
	b _020CAC28
_020CAB40:
	mov r0, #0x0
	cmp r0, r0
	cmpeq r1, r0
	bne _020CAB8C
	cmp r4, #0x0
	beq _020CAC28
_020CAB58:
	ldr r0, =0xCCCCCCCD
	umull r1, r0, r4, r0
	movs r0, r0, lsr #0x3
	mov r1, #0xa
	mul r1, r0, r1
	sub r1, r4, r1
	mov r4, r0
	add r1, r1, #0x30
	add r0, sp, #0x3a
	strb r1, [r0, r8]
	add r8, r8, #0x1
	bne _020CAB58
	b _020CAC28
_020CAB8C:
	cmp r1, r0
	cmpeq r4, r0
	beq _020CAC28
_020CAB98:
	ldr r2, [sp, #0xc]
	ldr r3, [sp, #0x4]
	mov r0, r4
	bl _ll_udiv
	mov r3, #0xa
	umull r3, r12, r0, r3
	subs r3, r4, r3
	mov r2, #0x0
	add r4, r3, #0x30
	add r3, sp, #0x3a
	strb r4, [r3, r8]
	cmp r1, r2
	cmpeq r0, r2
	mov r4, r0
	add r8, r8, #0x1
	bne _020CAB98
	b _020CAC28
_020CABDC:
	mov r2, #0x0
	cmp r1, r2
	cmpeq r4, r2
	beq _020CAC28
_020CABEC:
	and r3, r4, #0xf
	cmp r3, #0xa
	mov r4, r4, lsr #0x4
	addlt r3, r3, #0x30
	mov r2, r1, lsr #0x4
	orr r4, r4, r1, lsl #0x1c
	mov r1, r2
	addge r3, r3, r0
	add r2, sp, #0x3a
	strb r3, [r2, r8]
	mov r2, #0x0
	cmp r1, r2
	add r8, r8, #0x1
	cmpeq r4, r2
	bne _020CABEC
_020CAC28:
	cmp r7, #0x0
	ble _020CAC4C
	ldrsb r0, [sp, #0x38]
	cmp r0, #0x30
	ldreq r1, [sp, #0x20]
	addeq r0, sp, #0x3a
	streqb r1, [r0, r8]
	ldreq r7, [sp, #0x4]
	addeq r8, r8, #0x1
_020CAC4C:
	sub r5, r5, r8
	ands r0, r6, #0x10
	beq _020CAC68
	sub r0, r10, r8
	sub r0, r0, r7
	cmp r5, r0
	movlt r5, r0
_020CAC68:
	cmp r5, #0x0
	subgt r10, r10, r5
	add r0, r7, r8
	ands r6, r6, #0x8
	sub r10, r10, r0
	bne _020CAC90
	ldr r1, [sp, #0x1c]
	add r0, sp, #0x54
	mov r2, r10
	bl string_fill_char
_020CAC90:
	cmp r7, #0x0
	ble _020CACB8
	add r0, sp, #0x38
	add r4, r0, r7
_020CACA0:
	ldrsb r1, [r4, #-0x1]!
	sub r7, r7, #0x1
	add r0, sp, #0x54
	bl string_put_char
_020CACB0:
	cmp r7, #0x0
	bgt _020CACA0
_020CACB8:
	ldr r1, [sp, #0x20]
	mov r2, r5
	add r0, sp, #0x54
	bl string_fill_char
	cmp r8, #0x0
	ble _020CACF0
	add r0, sp, #0x3A
	add r4, r0, r8
_020CACD8:
	ldrsb r1, [r4, #-0x1]!
	sub r8, r8, #0x1
	add r0, sp, #0x54
	bl string_put_char
	cmp r8, #0x0
	bgt _020CACD8
_020CACF0:
	cmp r6, #0x0
	beq _020CAD08
	ldr r1, [sp, #0x1C]
	mov r2, r10
	add r0, sp, #0x54
	bl string_fill_char
_020CAD08:
	add r9, r9, #0x1
_020CAD0C:
	ldrsb r0, [r9, #0x0]
	cmp r0, #0x0
	bne _020CA530
_020CAD18:
	ldr r0, [sp, #0x54]
	cmp r0, #0x0
	ldrne r0, [sp, #0x58]
	movne r1, #0x0
	strneb r1, [r0, #0x0]
	bne _020CAD48
	ldr r0, [sp, #0x0]
	cmp r0, #0x0
	ldrne r1, [sp, #0x5c]
	movne r2, #0x0
	addne r0, r1, r0
	strneb r2, [r0, #-0x1]
_020CAD48:
	ldr r1, [sp, #0x58]
	ldr r0, [sp, #0x5c]
	sub r0, r1, r0
	add sp, sp, #0x64
	ldmia sp!, {r4-r11,lr}
	bx lr
}
#endif

ARM_FUNC void string_put_char(struct printfStr *dest, s8 value)
{
    if (dest->spaceLeft != 0)
    {
        dest->stringEnd[0] = value;
        dest->spaceLeft--;
    }
    dest->stringEnd++;
}

ARM_FUNC void string_fill_char(struct printfStr *dest, s8 value, s32 count)
{
    if (count <= 0)
        return;

    u32 written = 0;
    u32 spaceLeft = (u32)dest->spaceLeft;
    u32 toWrite = spaceLeft > (u32)count ? count : spaceLeft;

    while (written < toWrite)
    {
        dest->stringEnd[written] = value;
        written++;
    }

    dest->spaceLeft -= toWrite;
    dest->stringEnd += count; // this is wrong but matching...
}

ARM_FUNC void string_put_string(struct printfStr *dest, const s8 *src, s32 count)
{
    if (count <= 0)
        return;

    u32 written = 0;
    u32 spaceLeft = (u32)dest->spaceLeft;
    u32 toWrite = spaceLeft > (u32)count ? count : spaceLeft;

    while (written < toWrite)
    {
        dest->stringEnd[written] = src[written];
        written++;
    }

    dest->spaceLeft -= toWrite;
    dest->stringEnd += count; // this is wrong but matching...
}

ARM_FUNC s32 OS_SPrintf(s8 *buffer, const s8 *format, ...)
{
    void *args = (void *)((u32 *)((u32)&format & ~0x3) + 1); // hack since mwccarm doesn't have <stdarg.h> apparently
    return OS_VSPrintf(buffer, format, args);
}

ARM_FUNC s32 OS_VSPrintf(s8 *buffer, const s8 *format, void *args)
{
    return OS_VSNPrintf(buffer, 0x7FFFFFFF, format, args);
}

ARM_FUNC s32 OS_SNPrintf(s8 *buffer, s32 bufsz, const s8 *format, ...)
{
    void *args = (void *)((u32 *)((u32)&format & ~0x3) + 1); // hack since mwccarm doesn't have <stdarg.h> apparently
    return OS_VSNPrintf(buffer, bufsz, format, args);
}

#ifdef NONMATCHING

#define va_arg(list, ty) *(ty *)((u32 *)(list = (void *)((u32 *)(list) + 1)) - 1)
#define va_arg_64(list, sgn) *((sgn##64 *)(list = (void *)((sgn##64 *)(list) + 1)) - 1)

ARM_FUNC s32 OS_VSNPrintf(s8 *buffer, s32 bufsz, const s8 *format, void *args)
{
    s8 buf[24];
    s32 n_buf;
    s8 prefix[2];
    s32 n_prefix;

    const s8 *s = format;

    printfStr str;
    str.spaceLeft = bufsz;
    str.stringStart = buffer;
    str.stringEnd = buffer;

    while (*s)
    {
        // matches:
        // binary range        (hex range) [dec range]
        // 1000 0001-1001 1111 (0x81-0x9F) [129-159]
        // 1110 0000-1111 1100 (0xE0-0xFC) [224-252]
        if ((u32)(((u8)*s ^ 0x20) - 0xa1) < 0x3c)
        {
            string_put_char(&str, *s++);
            if (*s)
            {
                string_put_char(&str, *s++);
            }
        }
        else if (*s != '%')
        {
            string_put_char(&str, *s++);
        }
        else
        {
            enum {
                blank = 000001,
                plus = 000002,
                sharp = 000004,
                minus = 000010,
                zero = 000020,
                l1 = 000040,
                h1 = 000100,
                l2 = 000200,
                h2 = 000400,
                usigned = 010000,
                end
            };
            s32 flag = 0, width = 0, precision = -1, radix = 10;
            s8 hex = 'a' - 10;
            const s8 *p_start = s;
            for (;;)
            {
                switch (*++s)
                {
                case '+':
                    if (s[-1] != ' ')
                        break;
                    flag |= plus;
                    continue;
                case ' ':
                    flag |= blank;
                    continue;
                case '-':
                    flag |= minus;
                    continue;
                case '0':
                    flag |= zero;
                    continue;
                }
                break;
            }
            if (*s == '*')
            {
                ++s, width = va_arg(args, s32);
                if (width < 0)
                {
                    width = -width, flag |= minus;
                }
            }
            else
            {
                while ((*s >= '0') && (*s <= '9'))
                {
                    width = (width * 10) + *s++ - '0';
                }
            }

            if (*s == '.')
            {
                ++s, precision = 0;
                if (*s == '*')
                {
                    ++s, precision = va_arg(args, s32);
                    if (precision < 0)
                    {
                        precision = -1;
                    }
                }
                else
                {
                    while ((*s >= '0') && (*s <= '9'))
                    {
                        precision = (precision * 10) + *s++ - '0';
                    }
                }
            }

            switch (*s)
            {
            case 'h':
                if (*++s != 'h') {
                    flag |= h1;
                }
                else {
                    ++s, flag |= h2;
                }
                break;
            case 'l':
                if (*++s != 'l') {
                    flag |= l1;
                }
                else {
                    ++s, flag |= l2;
                }
                break;
            }

            switch (*s)
            {
            case 'd':
            case 'i':
                goto put_int;
            case 'o':
                radix = 8;
                flag |= usigned;
                goto put_int;
            case 'u':
                flag |= usigned;
                goto put_int;
            case 'X':
                hex = 'A' - 10;
                goto put_hex;
            case 'x':
                goto put_hex;
            case 'p':
                flag |= sharp;
                precision = 8;
                goto put_hex;
            case 'c':
                if (precision >= 0)
                    goto put_invalid;
                {
                    s32 v = va_arg(args, s32);
                    width -= 1;
                    if (flag & minus)
                    {
                        string_put_char(&str, (s8)v);
                        string_fill_char(&str, ' ', width);
                    }
                    else
                    {
                        s8 pad = (s8)((flag & zero) ? '0' : ' ');
                        string_fill_char(&str, pad, width);
                        string_put_char(&str, (s8)v);
                    }
                    ++s;
                }
                break;
            case 's':
            {
                s32 n_bufs = 0;
                const s8 *p_bufs = va_arg(args, const s8 *);
                if (precision < 0)
                {
                    while (p_bufs[n_bufs])
                    {
                        ++n_bufs;
                    }
                }
                else
                {
                    while (n_bufs < precision && p_bufs[n_bufs])
                    {
                        ++n_bufs;
                    }
                }
                width -= n_bufs;
                if (flag & minus)
                {
                    string_put_string(&str, p_bufs, n_bufs);
                    string_fill_char(&str, ' ', width);
                }
                else
                {
                    s8 pad = (s8)((flag & zero) ? '0' : ' ');
                    string_fill_char(&str, pad, width);
                    string_put_string(&str, p_bufs, n_bufs);
                }
                ++s;
            }
            break;
            case 'n':
            {
                s32 count = str.stringEnd - str.stringStart;
                if (!(flag & h2))
                {
                    if (flag & h1)
                    {
                        *va_arg(args, s16 *) = (s16)count;
                    }
                    else if (flag & l2)
                    {
                        *va_arg(args, u64 *) = (u64)count;
                    }
                    else
                    {
                        *va_arg(args, s32 *) = count;
                    }
                }
            }
            ++s;
            break;
            case '%':
                if (p_start + 1 != s)
                    goto put_invalid;
                string_put_char(&str, *s++);
                break;

            default:
                goto put_invalid;

            put_invalid:
                string_put_string(&str, p_start, s - p_start);
                break;

            put_hex:
                radix = 16;
                flag |= usigned;
            put_int:
            {
                u64 value = 0;
                n_prefix = 0;
                if (flag & minus)
                {
                    flag &= ~zero;
                }
                if (precision < 0)
                {
                    precision = 1;
                }
                else
                {
                    flag &= ~zero;
                }
                if (flag & usigned)
                {
                    if (flag & h2)
                    {
                        value = va_arg(args, u8);
                    }
                    else if (flag & h1)
                    {
                        value = va_arg(args, u16);
                    }
                    else if (flag & l2)
                    {
                        value = va_arg_64(args, u);
                    }
                    else
                    {
                        value = va_arg(args, u32);
                    }
                    flag &= ~(plus | blank);
                    if (flag & sharp)
                    {
                        if (radix == 16)
                        {
                            if (value != 0)
                            {
                                prefix[0] = (s8)(hex + (10 - 'x' - 'a'));
                                prefix[1] = '0';
                                n_prefix = 2;
                            }
                        }
                        else
                        {
                            if (radix == 8)
                            {
                                prefix[0] = '0';
                                n_prefix = 1;
                            }
                        }
                    }
                }
                else {
                    if (flag & h2) {
                        value = va_arg(args, s8);
                    } else if (flag & h1) {
                        value = va_arg(args, s16);
                    } else if (flag & l2) {
                        value = va_arg_64(args, u);
                    } else {
                        value = va_arg(args, s32);
                    }

                    if ((value >> 32) & 0x80000000) {
                        value = ~value + 1;
                        prefix[0] = '-';
                        n_prefix = 1;
                    } else {
                        if (value || precision) {
                            if (flag & plus) {
                                prefix[0] = '+';
                                n_prefix = 1;
                            } else if (flag & blank) {
                                prefix[0] = ' ';
                                n_prefix = 1;
                            }
                        }
                    }
                    n_buf = 0;
                    switch (radix) {
                        case 8:
                            while (value != 0) {
                                s32 octDig = (s32) (value & 0x7);
                                value >>= 3;
                                buf[n_buf++] = (s8) (octDig + '0');
                            }
                            break;
                        case 10:
                            if ((value >> 32) == 0) {
                                u32 v = (u32) value;
                                while (v) {
                                    u32 div10 = v / 10;
                                    s32 dig = (s32) (v - (div10 * 10));
                                    v = div10;
                                    buf[n_buf++] = (s8) (dig + '0');
                                }
                            } else {
                                while (value) {
                                    u64 div10 = value / 10;
                                    s32 dig = (s32) (value - (div10 * 10));
                                    value = div10;
                                    buf[n_buf++] = (s8) (dig + '0');
                                }
                            }
                            break;
                        case 16:
                            while (value != 0) {
                                s32 hexDig = (s32) (value & 0xf);
                                value >>= 4;
                                buf[n_buf++] = (s8) ((hexDig < 10) ? (hexDig + '0') : (hexDig + hex));
                            }
                            break;
                    }
                    if (n_prefix > 0) {
                        if (prefix[0] == '0') {
                            n_prefix = 0;
                            buf[n_buf++] = '0';
                        }
                    }
                }
            }
            goto put_to_stream;

        put_to_stream:
            {
                s32 n_pad = (s32)(precision - n_buf);
                if (flag & zero)
                {
                    if (n_pad < width - n_buf - n_prefix)
                    {
                        n_pad = (s32)(width - n_buf - n_prefix);
                    }
                }
                if (n_pad > 0)
                {
                    width -= n_pad;
                }

                width -= n_prefix + n_buf;
                if (!(flag & minus))
                {
                    string_fill_char(&str, ' ', width);
                }
                while (n_prefix > 0)
                {
                    string_put_char(&str, prefix[--n_prefix]);
                }
                string_fill_char(&str, '0', n_pad);
                while (n_buf > 0)
                {
                    string_put_char(&str, buf[--n_buf]);
                }
                if (flag & minus)
                {
                    string_fill_char(&str, ' ', width);
                }
                ++s;
            }
            break;
            }
        }
    }

    if (str.spaceLeft != 0)
    {
        *str.stringEnd = '\0';
    }
    else if (bufsz != 0)
    {
        str.stringStart[bufsz - 1] = '\0';
    }
    return str.stringEnd - str.stringStart;
}

#endif
