#include "global.h"
#include "MI_memory.h"
#include "msgdata.h"
#include "heap.h"
#include "unk_0202A1E0.h"

THUMB_FUNC s32 FUN_0202A1E0()
{
    return 0xe4; // 228
}

THUMB_FUNC void FUN_0202A1E4(void *dest)
{
    MI_CpuFill8(dest, 0, 0x3c); // 60
}

THUMB_FUNC void FUN_0202A1F0(struct Unk0202A1F0 *unk)
{
    MI_CpuFill8(unk, 0, 0x168); // 360
    unk->b3 = 1;
}

THUMB_FUNC void FUN_0202A204(struct UnkMailStruct *unk)
{
    MailMsg_init_fromTemplate(&unk->messages[0], 0);
    MailMsg_init_fromTemplate(&unk->messages[1], 1);
    MailMsg_init_fromTemplate(&unk->messages[2], 2);
    MailMsg_init_fromTemplate(&unk->messages[3], 3);
}

THUMB_FUNC void FUN_0202A230(void *dst)
{
    MI_CpuFill8(dst, 0, 0xB3C); // 2876
}

THUMB_FUNC u32 FUN_0202A240(struct Unk0202A240 *unk, u32 controlVariable, void *dst)
{
    switch (controlVariable)
    {
        case 0:
            return unk->u_0_2;
        case 1:
            return unk->u_2;
        case 2:
            return unk->u_3;
        case 3:
            return unk->u_4;
        case 4:
            return unk->u_6;
        case 5:
            MI_CpuCopy8(&unk->u_8, dst, 4);
            return 0;
        case 6:
            MI_CpuCopy8(&unk->u_2C, dst, 16);
            return 0;
        case 7:
            return unk->u_0_0;
        case 8:
            MI_CpuCopy8(&unk->u_C, dst, 28);
            return 0;
        case 9:
            return unk->u_0_5;
        case 10:
            return unk->u_28;
        default:
            return 0;
    };
}

THUMB_FUNC void FUN_0202A2C4(struct Unk0202A240 *dst, u32 controlVariable, void *src)
{
    switch (controlVariable)
    {
        case 0:
            dst->u_0_2 = *(u8 *)src;
            break;
        case 1:
            dst->u_2 = *(u8 *)src;
            break;
        case 2:
            dst->u_3 = *(u8 *)src;
            break;
        case 3:
            dst->u_4 = *(u16 *)src;
            break;
        case 4:
            dst->u_6 = *(u16 *)src;
            break;
        case 5:
            MI_CpuCopy8(src, &dst->u_8, 4);
            break;
        case 6:
            MI_CpuCopy8(src, &dst->u_2C, 16);
            break;
        case 7:
            dst->u_0_0 = *(u8 *)src;
            break;
        case 8:
            MI_CpuCopy8(src, &dst->u_C, 28);
            break;
        case 10:
            dst->u_28 = *(u32 *)src;
            break;
        case 9:
            dst->u_0_5 = *(u8 *)src;
            break;
    }
}

THUMB_FUNC void FUN_0202A36C(struct Unk0202A240 *unk, s32 arg1, s32 arg2, s32 arg3)
{
    if (unk->u_3 + arg1 < 0xff)
    {
        unk->u_3 += arg1;
    }

    if (unk->u_4 + arg2 < 0xffff)
    {
        unk->u_4 += arg2;
    }

    if (unk->u_6 + arg3 < 0xffff)
    {
        unk->u_6 += arg3;
    }
}

THUMB_FUNC u8 FUN_0202A398(struct Unk0202A240 *unk)
{
    return unk->u_0_1;
}

THUMB_FUNC void FUN_0202A3A0(struct Unk0202A240 *unk, u16 arg1)
{
    unk->u_0_1 = arg1;
}

THUMB_FUNC u16 FUN_0202A3B4(struct Unk0202A3B4 *unk, u16 arg1, s32 controlVariable)
{
    switch (controlVariable)
    {
        case 0:
            break;
        case 1:
            if (arg1 > 0x270F)
            {
                unk->u_0 = 0x270F;
            }
            else
            {
                unk->u_0 = arg1;
            }
            break;
        case 2:
        case 3:
        case 4:
            break;
        case 5:
            if (unk->u_0 + arg1 > 0x270F)
            {
                unk->u_0 = 0x270F;
            }
            else
            {
                unk->u_0 += arg1;
            }
            break;
        case 6:
            if (unk->u_0 < arg1)
            {
                unk->u_0 = 0;
            }
            else
            {
                unk->u_0 -= arg1;
            }
            break;
    }
    return unk->u_0;
}

THUMB_FUNC u8 FUN_0202A40C(struct Unk0202A40C *unk, s32 controlVariable)
{
    switch (controlVariable)
    {
        case 2:
            unk->u_2 = 0;
            unk->u_8_4 = 0;
            break;
        case 3:
            if (unk->u_8_4 != 0)
            {
                unk->u_2 += 1;
            }
            else
            {
                unk->u_2 = 1;
                unk->u_8_4 = 1;
            }
            break;
    }
    return unk->u_2;
}

THUMB_FUNC u8 FUN_0202A444(struct Unk0202A444 *unk, s32 controlVariable)
{
    switch (controlVariable)
    {
        case 2:
            unk->u_3 = 1;
            break;
        case 3:
            if (unk->u_3 < 0xa)
            {
                unk->u_3++;
            }
            break;
        case 4:
            if (unk->u_3 > 1)
            {
                unk->u_3--;
            }
            break;
    }
    return unk->u_3;
}

THUMB_FUNC void FUN_0202A474(void *dst, s32 arg1, const void *src)
{
    if (arg1 == 0)
    {
        MI_CpuCopy8(src, dst + 0xc0, 0xa8);
    }
    else
    {
        MI_CpuCopy8(src, dst + 0x18, 0xa8);
    }
}

THUMB_FUNC void FUN_0202A498(const void *src, s32 arg1, void *dst)
{
    if (arg1 == 0)
    {
        MI_CpuCopy8(src + 0xc0, dst, 0xa8);
    }
    else
    {
        MI_CpuCopy8(src + 0x18, dst, 0xa8);
    }
}

THUMB_FUNC void FUN_0202A4B8(struct Unk0202A4B8 *arg0, struct Unk0202A4B8 *arg1) 
{
    u16 part1 = (arg1->u_2 - 1) * 1000;
    
    s32 value = (u16) (arg1->u_4 * 10) + (u16) (arg1->u_3 * 20);
    u16 part2;
    if (value > 950)
    {
        part2 = 0;
    }
    else
    {
        part2 = 950 - value;
    }

    u16 part3;
    if (arg1->u_6 > 970)
    {
        part3 = 0;
    }
    else
    {
        part3 = (970 + 30 - arg1->u_6) / 30;
    }

    // Can't seem to get these shifts to happen with a cast
    arg0->u_16 = (u32) ((part1 + part2 + part3) << 16) >> 16;
}

THUMB_FUNC u16 FUN_0202A520(struct Unk0202A4B8 *unk)
{
    return unk->u_16;
}

THUMB_FUNC u8 FUN_0202A524(struct Unk0202A4B8 *unk)
{
    return (u8)(unk->u_16 / (0xfa << 2));
}

THUMB_FUNC u16 FUN_0202A538(struct Unk0202A4B8 *unk, s32 arg1, s32 arg2)
{
    if (arg1 == 5)
    {
        return 0;
    }

    switch(arg2) {
        case 2:
            unk->u_array_C[arg1] = 0;
            break;
        case 3:
            if (unk->u_array_C[arg1] < 0xfffe) {
                unk->u_array_C[arg1]++;
            }
            break;
    }
    return unk->u_array_C[arg1];    
}

THUMB_FUNC u16 FUN_0202A578(struct Unk0202A578 *arg0, u16 arg1, u32 arg2) {
    asm{
    //push {r3-r4}
	mov r3, #0x1
	mov r4, #0x0
	cmp r1, #0x0
	bls _0202A590
    _0202A582:
	add r4, r4, #0x1
	lsl r4, r4, #0x10
	lsl r3, r3, #0x11
	lsr r4, r4, #0x10
	lsr r3, r3, #0x10
	cmp r4, r1
	blo _0202A582
    _0202A590:
	cmp r2, #0x0
	beq _0202A5B4
	cmp r2, #0x1
	beq _0202A5AC
	cmp r2, #0x2
	bne _0202A5C2
	ldr r1, =0x0000FFFF
	eor r1, r3
	lsl r1, r1, #0x10
	lsr r2, r1, #0x10
	ldrh r1, [r0, #0x8]
	and r1, r2
	strh r1, [r0, #0x8]
	b _0202A5C2
    _0202A5AC:
	ldrh r1, [r0, #0x8]
	orr r1, r3
	strh r1, [r0, #0x8]
	b _0202A5C2
    _0202A5B4:
	ldrh r0, [r0, #0x8]
	add r2, r0, #0x0
	asr r2, r1
	mov r0, #0x1
	and r0, r2
	pop {r3-r4}
	bx lr
    _0202A5C2:
	mov r0, #0x0
	// pop {r3-r4}
	// bx lr
	// .balign 4
    // _0202A5C8: .word 0x0000FFFF
    }
}


THUMB_FUNC void FUN_0202A5CC(struct Unk0202A5CC *unk, u32 arg1)
{
    unk->u_4 = arg1;
}

THUMB_FUNC u32 FUN_0202A5D0(struct Unk0202A5CC *unk)
{
    return unk->u_4;
}


THUMB_FUNC void FUN_0202A5D4(struct SaveBlock2 *sav2, u32 arg1, struct MailMessage *arg2)
{
    struct UnkSaveStruct_0202A5D4 *data = SavArray_get(sav2, 23);
    MailMsg_copy(&data->messages.messages[arg1], arg2);
}

THUMB_FUNC struct MailMessage *FUN_0202A5F4(struct SaveBlock2 *sav2, u32 arg1)
{
    struct UnkSaveStruct_0202A5D4 *data = SavArray_get(sav2, 23);
    return &data->messages.messages[arg1];
}

THUMB_FUNC void FUN_0202A60C(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    asm {
    // push {r3-r6}
	add r4, r3, #0x0
	mov r3, #0x1
	cmp r2, #0x0
	beq _0202A66C
	cmp r2, #0xc8
	bhi _0202A66C
	cmp r1, #0x0
	beq _0202A66C
	cmp r1, #0xa
	bhi _0202A66C
	sub r5, r2, #0x1
	sub r2, r1, #0x1
	mov r1, #0xc8
	mul r1, r2
	add r1, r5, r1
	lsl r1, r1, #0x10
	lsr r1, r1, #0x10
	lsr r6, r1, #0x1f
	lsl r5, r1, #0x1d
	sub r5, r5, r6
	mov r2, #0x1d
	ror r5, r2
	add r2, r6, r5
	lsl r2, r2, #0x18
	lsr r2, r2, #0x18
	lsl r3, r2
	lsl r2, r3, #0x18
	lsl r1, r1, #0x15
	lsr r5, r2, #0x18
	add r3, r0, #0x4
	lsr r2, r1, #0x18
	ldrb r1, [r3, r2]
	orr r1, r5
	strb r1, [r3, r2]
	ldr r3, [r4, #0x0]
	ldr r1, [r4, #0x8]
	lsl r5, r3, #0x18
	ldr r3, [r4, #0x4]
	lsl r1, r1, #0x18
	lsl r3, r3, #0x18
	lsr r3, r3, #0x8
	ldr r2, [r4, #0xc]
	lsr r1, r1, #0x10
	orr r3, r5
	orr r1, r3
	orr r1, r2
	str r1, [r0, #0x0]
    _0202A66C:
	// pop {r3-r6}
	// bx lr
    }
}

THUMB_FUNC void FUN_0202A670(struct Unk0202A670 *arg0)
{

    MI_CpuFill8(&(arg0->b4), 0, 0xfa);
    MI_CpuFill8(arg0, 0, 4);
}

THUMB_FUNC u32 FUN_0202A68C(struct Unk0202A68C *arg0, struct Unk0202A68C *arg1)
{
    if (arg0->b0 > arg1->b0) {
        return 1;
    } else if (arg0->b4 > arg1->b4) {
        return 1;
    } else if (arg0->b8 > arg1->b8) {
        return 1;
    }
    return 0;
}

THUMB_FUNC void FUN_0202A6B4(u32 arg0, u32 arg1, u32 arg2) 
{
    asm {
    // push {r3-r7, lr}
	sub sp, #0x10
	add r6, r2, #0x0
	add r5, r0, #0x0
	add r4, r1, #0x0
	mov r7, #0x1
	cmp r6, #0xc8
	bhi _0202A6C8
	cmp r4, #0xa
	bls _0202A6CE
    _0202A6C8:
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
    _0202A6CE:
	ldr r0, [r5, #0x0]
	lsr r1, r0, #0x18
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x0]
	lsr r1, r0, #0x10
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	str r1, [sp, #0x4]
	lsr r1, r0, #0x8
	lsl r1, r1, #0x18
	lsl r0, r0, #0x18
	lsr r1, r1, #0x18
	lsr r0, r0, #0x18
	str r1, [sp, #0x8]
	str r0, [sp, #0xc]
	add r0, r3, #0x0
	add r1, sp, #0x0
	bl FUN_0202A68C
	cmp r0, #0x0
	beq _0202A706
	add r0, r5, #0x0
	bl FUN_0202A670
	add sp, #0x10
	mov r0, #0x0
	pop {r3-r7, pc}
    _0202A706:
	sub r1, r4, #0x1
	mov r0, #0xc8
	mul r0, r1
	sub r2, r6, #0x1
	add r0, r2, r0
	lsl r0, r0, #0x10
	lsr r0, r0, #0x10
	lsr r3, r0, #0x1f
	lsl r2, r0, #0x1d
	lsl r0, r0, #0x15
	lsr r0, r0, #0x18
	add r0, r5, r0
	sub r2, r2, r3
	mov r1, #0x1d
	ror r2, r1
	add r1, r3, r2
	lsl r1, r1, #0x18
	lsr r1, r1, #0x18
	add r2, r7, #0x0
	lsl r2, r1
	lsl r1, r2, #0x18
	ldrb r0, [r0, #0x4]
	lsr r1, r1, #0x18
	tst r0, r1
	beq _0202A73E
	add sp, #0x10
	add r0, r7, #0x0
	pop {r3-r7, pc}
    _0202A73E:
	mov r0, #0x0
	add sp, #0x10
	// pop {r3-r7, pc}
    }
}


THUMB_FUNC u8 FUN_0202A744(struct Unk0202A744 *unk)
{
    return unk->u_FE;
}

THUMB_FUNC u8 FUN_0202A74C(struct Unk0202A744 *unk)
{
    return unk->u_FF;
}

THUMB_FUNC void FUN_0202A754(struct Unk0202A744 *dest, void *src, u8 arg2, u8 arg3)
{
    MI_CpuCopy8(src, &dest->u_104, sizeof(struct Unk0202A744_substruct1));
    dest->u_101 = arg2;
    dest->u_100 = arg3;
    dest->u_FE = 1;
}

THUMB_FUNC void FUN_0202A784(struct Unk0202A744 *src, struct Unk0202A784 *dest)
{
    dest->u_0 = src->u_101;
    dest->u_1 = src->u_100;
}

THUMB_FUNC void FUN_0202A798()
{
    asm {
    //push {r3-r7, lr}
	add r6, r1, #0x0
	mov r1, #0x41
	lsl r1, r1, #0x2
	add r5, r0, r1
	mov r0, #0xe4
	add r4, r2, #0x0
	mul r4, r0
	ldr r0, =0x00002710
	add r7, r6, #0x0
	str r0, [r6, #0x0]
	add r0, r5, r4
	add r0, #0xc9
	ldrb r0, [r0, #0x0]
	add r7, #0x30
	strh r0, [r6, #0x4]
	add r0, r5, r4
	add r0, #0xc8
	ldrb r0, [r0, #0x0]
	lsl r0, r0, #0x1f
	lsr r0, r0, #0x1f
	beq _0202A7EE
	mov r0, #0x0
	mov r1, #0x1a
	mov r2, #0x11
	mov r3, #0xb
	bl NewMsgDataFromNarc
	add r1, r5, r4
	add r1, #0xc8
	ldrb r1, [r1, #0x0]
	add r2, r6, #0x0
	str r0, [sp, #0x0]
	lsl r1, r1, #0x1e
	lsr r1, r1, #0x1f
	add r1, #0x16
	add r2, #0x8
	bl ReadMsgDataIntoU16Array
	ldr r0, [sp, #0x0]
	bl DestroyMsgData
	b _0202A7FC
    _0202A7EE:
	add r0, r5, r4
	add r1, r6, #0x0
	add r0, #0xa8
	add r1, #0x8
	mov r2, #0x10
	bl MI_CpuCopy8
    _0202A7FC:
	add r0, r5, r4
	add r1, r6, #0x0
	add r0, #0xca
	add r1, #0x18
	mov r2, #0x8
	bl MI_CpuCopy8
	add r0, r5, r4
	add r1, r6, #0x0
	add r0, #0xd2
	add r1, #0x20
	mov r2, #0x8
	bl MI_CpuCopy8
	add r0, r5, r4
	add r6, #0x28
	add r0, #0xda
	add r1, r6, #0x0
	mov r2, #0x8
	bl MI_CpuCopy8
	add r0, r5, r4
	add r1, r7, #0x0
	mov r2, #0xa8
	bl MI_CpuCopy8
	//pop {r3-r7, pc}
	//nop
    }
}

THUMB_FUNC void FUN_0202A838(struct Unk0202A744 *dest, void *src, u8 arg2, u8 arg3)
{
    MI_CpuCopy8(src, &dest->u_740, sizeof(dest->u_740));
    dest->u_103 = arg2;
    dest->u_102 = arg3;
    dest->u_FF = 1;
}

THUMB_FUNC void FUN_0202A864(struct Unk0202A744 *src, struct Unk0202A784 *dest)
{
    dest->u_0 = src->u_103;
    dest->u_1 = src->u_102;
}

THUMB_FUNC struct Unk0202A744_substruct2 *FUN_0202A878(struct Unk0202A744 *src, u32 heap_id)
{
    struct Unk0202A744_substruct2 *dstp = AllocFromHeap(heap_id, sizeof(struct Unk0202A744_substruct2) /* 1020 */);
    MI_CpuCopy8(&src->u_740, dstp, 0x3fc);
    return dstp;
}

THUMB_FUNC s32 FUN_0202A89C()
{
    return 0xD00; // 3328
}

THUMB_FUNC void FUN_0202A8A4(struct UnkSaveStruct_0202A5D4 *savStruct)
{
    FUN_0202A1E4(savStruct);
    FUN_0202A1F0(&savStruct->u_3C);
    FUN_0202A204(&savStruct->messages);
    FUN_0202A230(&savStruct->u_1C4);
}

THUMB_FUNC struct UnkSaveStruct_0202A5D4 *FUN_0202A8CC(struct SaveBlock2* sav2)
{
    return SavArray_get(sav2, 23);
}

THUMB_FUNC void *FUN_0202A8D8(struct SaveBlock2* sav2)
{
    struct UnkSaveStruct_0202A5D4 *data = SavArray_get(sav2, 23);
    return &data->u_3C;
}

THUMB_FUNC void *FUN_0202A8E4(struct SaveBlock2* sav2)
{
    struct UnkSaveStruct_0202A5D4 *data = SavArray_get(sav2, 23);
    return &data->u_1C4;
}