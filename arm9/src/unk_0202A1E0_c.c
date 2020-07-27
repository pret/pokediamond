#include "global.h"
#include "MI_memory.h"

#pragma thumb on

struct Unk0202A1F0
{
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
};

struct Unk0202A240
{
    u8 b0_0 : 1;
    u8 b0_1 : 1;
    u8 b0_2 : 3;
    u8 b0_5 : 3;
    u8 b1;
    u8 b2;
    u8 b3;
    u16 b4;
    u16 b6;
    int b8;
    int b12;
    int b16;
    int b20;
    int b24;
    int b28;
    int b32;
    int b36;
    int b40;
    int b44;
};

void FUN_02013764(int arg0, int arg1);

int FUN_0202A1E0();
void FUN_0202A1E4(void *dest);
void FUN_0202A1F0(struct Unk0202A1F0 *unk);
void FUN_0202A204(int arg0);
void FUN_0202A230(void *dest);
int FUN_0202A240(struct Unk0202A240 *unk, u32 arg1, void *dest);
// void FUN_0202A2C4(struct Unk0202A2C4 *unk_dest, u32 arg1, struct Unk0202A2C4 *unk_source);
// void FUN_0202A36C(struct Unk0202A2C4 * unk, s8 arg1, s16 arg2, s16 arg3);

int FUN_0202A1E0()
{
    return 0xe4;
}

void FUN_0202A1E4(void *dest)
{
    MI_CpuFill8(dest, 0, 0x3c);
}

void FUN_0202A1F0(struct Unk0202A1F0 *unk)
{
    MI_CpuFill8(unk, 0, 0x5a << 2);
    unk->b3 = 1;
}

void FUN_0202A204(int arg0)
{
    FUN_02013764(arg0, 0);
    FUN_02013764(arg0 + 8, 1);
    FUN_02013764(arg0 + 16, 2);
    FUN_02013764(arg0 + 24, 3);
}

void FUN_0202A230(void *dest)
{
    MI_CpuFill8(dest, 0, 0xB3C);
}

int FUN_0202A240(struct Unk0202A240 *unk, u32 arg1, void *dest)
{
    switch (arg1)
    {
    case 0:
        return unk->b0_2;
    case 1:
        return unk->b2;
    case 2:
        return unk->b3;
    case 3:
        return unk->b4;
    case 4:
        return unk->b6;
    case 5:
        MI_CpuCopy8(&unk->b8, dest, 4);
        return 0;
    case 6:
        MI_CpuCopy8(&unk->b44, dest, 16);
        return 0;
    case 7:
        return unk->b0_0;
    case 8:
        MI_CpuCopy8(&unk->b12, dest, 28);
        return 0;
    case 9:
        return unk->b0_5;
    case 10:
        return unk->b40;
    default:
        return 0;
    };
}

// struct Unk0202A2C4
// {
//     union {
//         struct
//         {
//             u8 b0_0 : 1;
//             u8 b0_1 : 1;
//             u8 b0_2 : 3;
//             u8 b0_5 : 3;
//         } b0_split;
//         u8 b0_combined;
//     } b0;
//     u8 b1;
//     u8 b2;
//     u8 b3;
//     u16 b4;
//     u16 b6;
//     int b8;
//     int b12;
//     int b16;
//     int b20;
//     int b24;
//     int b28;
//     int b32;
//     int b36;
//     int b40;
//     int b44;
// };
// void FUN_0202A2C4(struct Unk0202A2C4 *unk_dest, u32 arg1, struct Unk0202A2C4 *unk_source)
// {
//     switch (arg1)
//     {
//     case 0:
//         unk_dest->b0.b0_split.b0_2 = unk_source->b0.b0_split.b0_2;
//         break;
//     case 1:
//         unk_dest->b2 = unk_source->b0.b0_combined;
//         break;
//     case 2:
//         unk_dest->b3 = unk_source->b0.b0_combined;
//         break;
//     case 3:
//         unk_dest->b4 = unk_source->b0.b0_combined;
//         break;
//     case 4:
//         unk_dest->b6 = unk_source->b0.b0_combined;
//         break;
//     case 5:
//         MI_CpuCopy8(&unk_source->b0, &unk_dest->b8, 4);
//         break;
//     case 6:
//         MI_CpuCopy8(&unk_source->b0, &unk_dest->b44, 16);
//         break;
//     case 7:
//         unk_dest->b0.b0_split.b0_0 = unk_source->b0.b0_split.b0_0;
//         break;
//     case 8:
//         MI_CpuCopy8(&unk_source->b0, &unk_dest->b12, 28);
//         break;
//     case 9:
//         unk_dest->b40 = unk_source->b0.b0_combined;
//     case 10:
//         unk_dest->b0.b0_split.b0_5 = unk_source->b0.b0_split.b0_5;
//         break;
//     default:
//         return;
//     };
// }

// void FUN_0202A36C(struct Unk0202A36C * unk, s8 arg1, s16 arg2, s16 arg3) {
//     if ((unk->b3 + arg1) < 0xff) {
//         unk->b3 += arg1;
//     }
    
//     if ((unk->b4 + arg2) < 0xffff) {
//         unk->b4 += arg2;
//     }

//     if ((unk->b6 + arg3) < 0xffff) {
//         unk->b6 += arg3;
//     }

// }

