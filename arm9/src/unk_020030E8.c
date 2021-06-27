#include "global.h"
#include "unk_020030E8.h"
#include "MI_memory.h"
#include "unk_02002F08.h"
#include "unk_0200CA44.h"

extern void *FUN_020222E8();
extern void *FUN_020222F8();
extern void *FUN_02022308();
extern void *FUN_02022310();
extern int abs(int);

THUMB_FUNC void FUN_02003108(struct PaletteData *param0, u32 param1, u16 param2, u32 param3)
{
    GF_ASSERT(param2 * 2 + param3 <= param0->pltt[param1].bufSize);

    u16 *r1;
    switch (param1)
    {
        case 0:
            r1 = FUN_020222E8();
            break;
        case 1:
            r1 = FUN_020222F8();
            break;
        case 2:
            r1 = FUN_02022308();
            break;
        case 3:
            r1 = FUN_02022310();
            break;
        default:
            GF_ASSERT(FALSE);
            return;
    }

    PaletteData_LoadPalette(param0, r1 + param2, param1, param2, (u16)param3);
}

THUMB_FUNC void FUN_0200317C(
    NarcId narcId, s32 memberId, u32 heap_id, u32 size, u16 offset, void *dest)
{
    NNSG2dPaletteData *pltData;

    void *ptr = GfGfxLoader_GetPlttData(narcId, memberId, &pltData, heap_id);
    GF_ASSERT(ptr != NULL);

    if (size == 0)
    {
        size = pltData->szByte;
    }

    MI_CpuCopy16(pltData->pRawData + offset * 2, dest, size);

    FreeToHeap(ptr);
}

THUMB_FUNC void FUN_020031B8(
    struct PaletteData *param0, u32 param1, u16 param2, u32 param3, u16 param4, u16 param5)
{

    MI_CpuCopy16(
        param0->pltt[param1].unfadedBuf + param2, param0->pltt[param3].unfadedBuf + param4, param5);
    MI_CpuCopy16(
        param0->pltt[param1].unfadedBuf + param2, param0->pltt[param3].fadedBuf + param4, param5);
}

THUMB_FUNC u16 *FUN_020031FC(struct PaletteData *param0, u32 param1)
{
    return param0->pltt[param1].unfadedBuf;
}

THUMB_FUNC u16 *FUN_02003204(struct PaletteData *param0, u32 param1)
{
    return param0->pltt[param1].fadedBuf;
}

THUMB_FUNC u32 FUN_02003210(struct PaletteData *param0,
    u16 param1,
    u16 param2,
    s16 param3,
    u8 param6,
    u8 param7,
    u16 param8)
{

    u16 stc = param2;
    u32 r6 = 0;

    for (u8 r4 = 0; r4 < 14; r4++)
    {
        if (FUN_02003314(param1, r4) != 1)
        {
            continue;
        }

        if (FUN_02003314(param0->unk118_2, r4) != 0)
        {
            continue;
        }

        FUN_02003368(r4, &param0->pltt[r4], &param2);

        FUN_020033A4(&param0->pltt[r4].unk0c, param2, param3, param6, param7, param8);

        FUN_02003328(param0, r4);

        if (r4 >= 4)
        {
            FUN_0200359C(param0, r4, 0x100);
        }
        else
        {
            FUN_0200359C(param0, r4, 0x10);
        }

        param2 = stc;
        r6 = 1;
    }

    if (r6 == 1)
    {
        param0->unk118_2 |= param1;
        if (param0->unk11a_e == 0)
        {
            param0->unk11a_e = 1;

            param0->unk118_0 = 1;
            param0->unk11c = 0;

            // wtf is that?
            FUN_0200CA44((void (*)(u32, struct TextPrinter *))FUN_02003464,
                (struct TextPrinter *)param0,
                (u32)(-2));
        }
    }

    return r6;
}

THUMB_FUNC u8 FUN_02003314(u16 param0, u16 param1)
{
    u32 r3 = 1;
    if ((param0 & (1 << param1)) == 0)
    {
        r3 = 0;
    }

    return (u8)r3;
}

THUMB_FUNC void FUN_02003328(struct PaletteData *param0, u16 param1)
{
    if (FUN_02003314(param0->unk11a_0, param1) != 1)
    {
        param0->unk11a_0 |= 1 << param1;
    }
}

THUMB_FUNC void FUN_02003368(s32 param0, struct Palette *param1, u16 *param2)
{
    u8 r0;
    if (param0 < 4)
    {
        r0 = (u8)(param1->bufSize >> 5);
    }
    else
    {
        r0 = (u8)(param1->bufSize >> 9);
    }

    u16 r4 = 0;
    for (u8 i = 0; i < r0; i++)
    {
        r4 += 1 << i;
    }

    *param2 &= r4;
}

THUMB_FUNC void FUN_020033A4(struct PaletteControl *param0,
    u16 param1,
    s16 param2,
    u8 param3,
    u8 param4,
    u16 param5)
{
    if (param2 < 0)
    {
        param0->unk06_0 = abs(param2) + 2;
        param0->unk02_0 = 0;
    }
    else
    {
        param0->unk06_0 = 2;
        param0->unk02_0 = param2;
    }

    param0->unk00 = param1;
    param0->unk02_6 = param3;
    param0->unk02_b = param4;
    param0->unk04_0 = param5;

    param0->unk06_4 = param0->unk02_0;

    if (param3 < param4)
    {
        param0->unk04_f = 0;
        return;
    }
    param0->unk04_f = 1;
}

THUMB_FUNC void FUN_02003464(u32 param0, struct PaletteData *param1)
{
    if (param1->unk11c == 1)
    {
        param1->unk11c = 0;
        param1->unk11a_0 = 0;
        param1->unk118_2 = 0;
        param1->unk11a_e = 0;
        FUN_0200CAB4((s32)param0);
        return;
    }

    if (param1->unk118_0 == 1)
    {
        param1->unk11a_0 = param1->unk118_2;
        FUN_02003500(param1);
        FUN_02003520(param1);

        if (param1->unk118_2 == 0)
        {
            param1->unk11a_e = 0;
            FUN_0200CAB4((s32)param0);
        }
    }
}

THUMB_FUNC void FUN_02003500(struct PaletteData *param0)
{
    for (u8 i = 0; i < 4; i++)
    {
        FUN_02003540(param0, i, 0x10);
    }
}

THUMB_FUNC void FUN_02003520(struct PaletteData *param0)
{
    for (u8 i = 4; i < 14; i++)
    {
        FUN_02003540(param0, i, 0x100);
    }
}

THUMB_FUNC void FUN_02003540(struct PaletteData *param0, u8 param1, u32 param2)
{
    if (FUN_02003314(param0->unk118_2, param1) != 0)
    {
        if (param0->pltt[param1].unk0c.unk06_4 < param0->pltt[param1].unk0c.unk02_0)
        {
            param0->pltt[param1].unk0c.unk06_4++;
            return;
        }

        param0->pltt[param1].unk0c.unk06_4 = 0;
        FUN_0200359C(param0, param1, param2);
    }
}

THUMB_FUNC void FUN_0200359C(struct PaletteData *param0, u32 param1, u32 param2)
{

    for (u32 r6 = 0; r6 < 0x10; r6++)
    {
        if (FUN_02003314(param0->pltt[param1].unk0c.unk00, (u16)r6) != 0)
        {
            FUN_020035F8(param0->pltt[param1].unfadedBuf + param2 * r6,
                param0->pltt[param1].fadedBuf + param2 * r6,
                &param0->pltt[param1].unk0c,
                param2);
        }
    }

    FUN_02003684(param0, (u8)param1, &param0->pltt[param1].unk0c);
}

THUMB_FUNC void FUN_020035F8(
    u16 *param0, u16 *param1, struct PaletteControl *param2, u32 param3)
{
    for (u32 i = 0; i < param3; i++)
    {
        u8 lo = (u8)((param0[i] & 0x1f) +
                     ((((param2->unk04_0 & 0x1f) - (param0[i] & 0x1f)) * param2->unk02_6) >> 4));

        u8 hi = (u8)(((param0[i] >> 10) & 0x1f) +
                     (((((param2->unk04_0 >> 10) & 0x1f) - ((param0[i] >> 10) & 0x1f)) *
                          param2->unk02_6) >>
                         4));
        u8 mid = (u8)(((param0[i] >> 5) & 0x1f) +
                      (((((param2->unk04_0 >> 5) & 0x1f) - ((param0[i] >> 5) & 0x1f)) *
                           param2->unk02_6) >>
                          4));

        param1[i] = (u16)((hi << 10) | (mid << 5) | lo);
    }
}

THUMB_FUNC void FUN_02003684(
    struct PaletteData *param0, u8 param1, struct PaletteControl *param2)
{
    s16 r4;
    if (param2->unk02_6 == param2->unk02_b)
    {
        if ((param0->unk118_2 & (1 << param1)) == 0)
        {
            return;
        }

        param0->unk118_2 ^= (1 << param1);

        return;
    }

    if (param2->unk04_f == 0)
    {
        r4 = (s16)param2->unk02_6;
        r4 += param2->unk06_0;
        if (r4 > param2->unk02_b)
        {
            r4 = (s16)param2->unk02_b;
        }

        param2->unk02_6 = r4;
        return;
    }

    r4 = (s16)param2->unk02_6;
    r4 -= param2->unk06_0;
    if (r4 < param2->unk02_b)
    {
        r4 = (s16)param2->unk02_b;
    }

    param2->unk02_6 = r4;
}

THUMB_FUNC void FUN_0200372C(struct PaletteData *param0)
{
    if (param0->unk11a_f == 0 && param0->unk118_0 != 1)
    {
        return;
    }

    for (s32 r5 = 0; r5 < 14; r5++)
    {
        if (param0->unk11a_f != 0 ||
            (param0->pltt[r5].fadedBuf != 0 && FUN_02003314(param0->unk11a_0, (u16)r5) != 0))
        {
            DC_FlushRange(param0->pltt[r5].fadedBuf, param0->pltt[r5].bufSize);

            switch (r5)
            {
                case 0:
                    GX_LoadBGPltt(param0->pltt[r5].fadedBuf, 0, param0->pltt[r5].bufSize);
                    break;
                case 1:
                    GXS_LoadBGPltt(param0->pltt[r5].fadedBuf, 0, param0->pltt[r5].bufSize);
                    break;
                case 2:
                    GX_LoadOBJPltt(param0->pltt[r5].fadedBuf, 0, param0->pltt[r5].bufSize);
                    break;
                case 3:
                    GXS_LoadOBJPltt(param0->pltt[r5].fadedBuf, 0, param0->pltt[r5].bufSize);
                    break;
                case 4:
                    GX_BeginLoadBGExtPltt();
                    GX_LoadBGExtPltt(param0->pltt[r5].fadedBuf, 0, param0->pltt[r5].bufSize);
                    GX_EndLoadBGExtPltt();
                    break;
                case 5:
                    GX_BeginLoadBGExtPltt();
                    GX_LoadBGExtPltt(param0->pltt[r5].fadedBuf, 0x2000, param0->pltt[r5].bufSize);
                    GX_EndLoadBGExtPltt();
                    break;
                case 6:
                    GX_BeginLoadBGExtPltt();
                    GX_LoadBGExtPltt(param0->pltt[r5].fadedBuf, 0x4000, param0->pltt[r5].bufSize);
                    GX_EndLoadBGExtPltt();
                    break;
                case 7:
                    GX_BeginLoadBGExtPltt();
                    GX_LoadBGExtPltt(param0->pltt[r5].fadedBuf, 0x6000, param0->pltt[r5].bufSize);
                    GX_EndLoadBGExtPltt();
                    break;
                case 8:
                    GXS_BeginLoadBGExtPltt();
                    GXS_LoadBGExtPltt(param0->pltt[r5].fadedBuf, 0, param0->pltt[r5].bufSize);
                    GXS_EndLoadBGExtPltt();
                    break;
                case 9:
                    GXS_BeginLoadBGExtPltt();
                    GXS_LoadBGExtPltt(param0->pltt[r5].fadedBuf, 0x2000, param0->pltt[r5].bufSize);
                    GXS_EndLoadBGExtPltt();
                    break;
                case 10:
                    GXS_BeginLoadBGExtPltt();
                    GXS_LoadBGExtPltt(param0->pltt[r5].fadedBuf, 0x4000, param0->pltt[r5].bufSize);
                    GXS_EndLoadBGExtPltt();
                    break;
                case 11:
                    GXS_BeginLoadBGExtPltt();
                    GXS_LoadBGExtPltt(param0->pltt[r5].fadedBuf, 0x6000, param0->pltt[r5].bufSize);
                    GXS_EndLoadBGExtPltt();
                    break;
                case 12:
                    GX_BeginLoadOBJExtPltt();
                    GX_LoadOBJExtPltt(param0->pltt[r5].fadedBuf, 0, param0->pltt[r5].bufSize);
                    GX_EndLoadOBJExtPltt();
                    break;
                case 13:
                    GXS_BeginLoadOBJExtPltt();
                    GXS_LoadOBJExtPltt(param0->pltt[r5].fadedBuf, 0, param0->pltt[r5].bufSize);
                    GXS_EndLoadOBJExtPltt();
                    break;
            }
        }
    }

    param0->unk11a_0 = param0->unk118_2;
    if (param0->unk11a_0 == 0)
    {
        param0->unk118_0 = 0;
    }
}

THUMB_FUNC u16 FUN_020038E4(struct PaletteData *param0)
{
    return param0->unk118_2;
}

THUMB_FUNC void FUN_020038F0(struct PaletteData *param0, u32 param1)
{
    param0->unk11a_f = param1;
}

THUMB_FUNC void FUN_02003914(
    struct PaletteData *param0, u32 param1, u32 param2, u16 param3, u16 param4, u16 param5)
{
    GF_ASSERT(param5 * 2 <= param0->pltt[param1].bufSize);
    if (param2 - 1 <= 1)
    {
        MI_CpuFill16(&param0->pltt[param1].unfadedBuf[param4], param3, (u32)((param5 - param4) * 2));
    }

    if (param2 == 0 || param2 == 2)
    {
        MI_CpuFill16(&param0->pltt[param1].fadedBuf[param4], param3, (u32)((param5 - param4) * 2));
    }
}

#ifdef NONMATCHING
THUMB_FUNC void FUN_02003974(u16 *param0, u16 *param1, u16 param2, u8 param3, u16 param4)
{
    s32 r12 = ((u32)(param4 << 0x1b)) >> 0x1b;
    s32 lr = ((u32)(param4 << 0x16)) >> 0x1b;
    s32 st8 = ((u32)(param4 << 0x11)) >> 0x1b;
    s32 lo, mid, hi;

    for (u16 i = 0; i < param2; i++)
    {
        lo = (((u32)(param0[i] << 0x1b)) >> 0x1b);
        mid = (((u32)(param0[i] << 0x16)) >> 0x1b);
        hi = (((u32)(param0[i] << 0x11)) >> 0x1b);

        param1[i] = (lo + ((r12 - lo) * param3) >> 4) | (mid + ((lr - mid) * param3) >> 4) << 5 |
                    (hi + ((st8 - hi) * param3) >> 4) << 10;
    }
}
#else
asm void FUN_02003974(u16 *param0, u16 *param1, u16 param2, u8 param3, u16 param4)
{
    // clang-format off
	push {r4-r7, lr}
	sub sp, #0xc
	str r0, [sp, #0x0]
	add r0, sp, #0x10
	ldrh r0, [r0, #0x10]
	str r1, [sp, #0x4]
	add r7, r2, #0x0
	lsl r1, r0, #0x1b
	lsr r1, r1, #0x1b
	mov r12, r1
	lsl r1, r0, #0x16
	lsl r0, r0, #0x11
	lsr r1, r1, #0x1b
	lsr r0, r0, #0x1b
	mov r2, #0x0
	mov lr, r1
	str r0, [sp, #0x8]
	cmp r7, #0x0
	bls _020039E2
_0200399A:
	ldr r0, [sp, #0x0]
	lsl r6, r2, #0x1
	ldrh r4, [r0, r6]
	lsl r0, r4, #0x1b
	lsr r1, r0, #0x1b
	lsl r0, r4, #0x16
	lsl r4, r4, #0x11
	lsr r5, r4, #0x1b
	ldr r4, [sp, #0x8]
	lsr r0, r0, #0x1b
	sub r4, r4, r5
	mul r4, r3
	asr r4, r4, #0x4
	add r4, r5, r4
	lsl r5, r4, #0xa
	mov r4, r12
	sub r4, r4, r1
	mul r4, r3
	asr r4, r4, #0x4
	add r1, r1, r4
	mov r4, lr
	sub r4, r4, r0
	mul r4, r3
	asr r4, r4, #0x4
	add r0, r0, r4
	lsl r0, r0, #0x5
	orr r0, r1
	add r1, r5, #0x0
	orr r1, r0
	ldr r0, [sp, #0x4]
	strh r1, [r0, r6]
	add r0, r2, #0x1
	lsl r0, r0, #0x10
	lsr r2, r0, #0x10
	cmp r2, r7
	blo _0200399A
_020039E2:
	add sp, #0xc
	pop {r4-r7, pc}
    // clang-format on
}
#endif

THUMB_FUNC void FUN_020039E8(
    struct PaletteData *param0, u32 param1, u16 param2, u16 param3, u8 param4, u16 param5)
{
    BOOL r0 = FALSE;
    if (param0->pltt[param1].unfadedBuf != 0 && param0->pltt[param1].fadedBuf != 0)
    {
        r0 = TRUE;
    }

    GF_ASSERT(r0);

    FUN_02003974(param0->pltt[param1].unfadedBuf + param2,
        param0->pltt[param1].fadedBuf + param2,
        param3,
        param4,
        param5);
}

THUMB_FUNC void FUN_02003A30(u16 *param0, u16 *param1, u16 param2, u8 param3, u16 param4)
{
    while (param2 != 0)
    {
        if ((param2 & 1) != 0)
        {
            FUN_02003974(param0, param1, 0x10, param3, param4);
        }

        param2 >>= 1;
        param1 += 0x10;
        param0 += 0x10;
    }
}

THUMB_FUNC void FUN_02003A64(
    struct PaletteData *param0, u32 param1, u16 param2, u8 param3, u16 param4)
{
    u32 r4 = 0;
    BOOL r0 = FALSE;
    if (param0->pltt[param1].unfadedBuf != 0 && param0->pltt[param1].fadedBuf != 0)
    {
        r0 = TRUE;
    }

    GF_ASSERT(r0);

    while (param2 != 0)
    {
        if ((param2 & 1) != 0)
        {
            FUN_020039E8(param0, param1, (u16)r4, 0x10, param3, param4);
        }

        param2 >>= 1;
        r4 += 0x10;
    }
}

#ifdef NONMATCHING
THUMB_FUNC void FUN_02003AC4(u16 *param0, u32 param1, u32 param2, u32 param3, u32 param4)
{
    s32 r4, lo, mid, hi, add;
    for (r4 = 0; r4 < param1; r4++)
    {
        lo = ((param0[r4]) & 0x1f);
        mid = ((param0[r4] >> 5) & 0x1f);
        hi = ((param0[r4] >> 10) & 0x1f);

        add = (lo * 0x4c + mid * 0x97 + hi * 0x1d) >> 8;

        lo = (u16)(add * param2) >> 8;
        mid = (u16)(add * param3) >> 8;
        hi = (u16)(add * param4) >> 8;

        if (lo > 0x1f)
        {
            lo = 0x1f;
        }
        if (mid > 0x1f)
        {
            mid = 0x1f;
        }
        if (hi > 0x1f)
        {
            hi = 0x1f;
        }

        param0[r4] = (hi << 10) | (mid << 5) | lo;
    }
}
#else
asm void FUN_02003AC4(u16 *param0, u32 param1, u32 param2, u32 param3, u32 param4)
{
    // clang-format off
	push {r3-r7, lr}
	mov lr, r1
	mov r12, r2
	add r7, r3, #0x0
	mov r4, #0x0
	cmp r1, #0x0
	ble _02003B3C
	ldr r6, [sp, #0x18]
_02003AD4:
	ldrh r3, [r0, #0x0]
	mov r1, #0x1f
	add r2, r3, #0x0
	asr r5, r3, #0xa
	and r2, r1
	and r5, r1
	mov r1, #0x1d
	mul r1, r5
	mov r5, #0x4c
	mul r5, r2
	asr r3, r3, #0x5
	mov r2, #0x1f
	and r3, r2
	mov r2, #0x97
	mul r2, r3
	add r2, r5, r2
	add r1, r1, r2
	asr r3, r1, #0x8
	mov r1, r12
	add r2, r1, #0x0
	mul r2, r3
	lsl r1, r2, #0x10
	lsr r1, r1, #0x10
	asr r2, r1, #0x8
	add r1, r7, #0x0
	mul r1, r3
	mul r3, r6
	lsl r1, r1, #0x10
	lsl r3, r3, #0x10
	lsr r1, r1, #0x10
	lsr r3, r3, #0x10
	asr r1, r1, #0x8
	asr r3, r3, #0x8
	cmp r2, #0x1f
	ble _02003B1C
	mov r2, #0x1f
_02003B1C:
	cmp r1, #0x1f
	ble _02003B22
	mov r1, #0x1f
_02003B22:
	cmp r3, #0x1f
	ble _02003B28
	mov r3, #0x1f
_02003B28:
	lsl r3, r3, #0xa
	lsl r1, r1, #0x5
	orr r1, r3
	orr r1, r2
	strh r1, [r0, #0x0]
	add r4, r4, #0x1
	mov r1, lr
	add r0, r0, #0x2
	cmp r4, r1
	blt _02003AD4
_02003B3C:
	pop {r3-r7, pc}
    // clang-format on
}
#endif

THUMB_FUNC void FUN_02003B40(struct PaletteData *param0,
    NarcId narcId,
    s32 memberId,
    u32 heap_id,
    u32 param4,
    u32 param5,
    u16 param6,
    u32 param7,
    u32 param8,
    u32 param9)
{
    NNSG2dPaletteData *pltData;
    void *ptr = GfGfxLoader_GetPlttData(narcId, memberId, &pltData, heap_id);
    GF_ASSERT(ptr != NULL);

    if (param5 == 0)
    {
        param5 = pltData->szByte;
    }

    FUN_02003AC4(pltData->pRawData, 0x10, param7, param8, param9);
    PaletteData_LoadPalette(param0, pltData->pRawData, param4, param6, (u16)param5);

    FreeToHeap(ptr);
}
