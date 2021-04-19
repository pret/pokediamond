#include "unk_0202D858.h"

struct UnkStruct_0202D858
{
    u8 unk00[0x1a];
};

static const struct UnkStruct_0202D858 UNK_020EEB04 = { {
    0x01,
    0x01,
    0x01,
    0x01,
    0x03,
    0x03,
    0x03,
    0x04,
    0x03,
    0x04,
    0x07,
    0x03,
    0x07,
    0x04,
    0x01,
    0x04,
    0x01,
    0x01,
    0x04,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x00,
    0x00,
} };

static const struct UnkStruct_0202D858 UNK_020EEB1E = { {
    0x01,
    0x01,
    0x01,
    0x01,
    0x03,
    0x03,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x00,
    0x00,
} };

THUMB_FUNC u8 FUN_0202D858(u16 param0)
{
    struct UnkStruct_0202D858 st0 = UNK_020EEB04;

    GF_ASSERT(param0 < 0x1a);

    return st0.unk00[param0];
}

THUMB_FUNC u8 FUN_0202D884(u16 param0)
{
    struct UnkStruct_0202D858 st0 = UNK_020EEB1E;

    GF_ASSERT(param0 < 0x1a);

    return st0.unk00[param0];
}

THUMB_FUNC u32 FUN_0202D8B0(int param0)
{
    switch (param0)
    {
    case 0x7:
    case 0x9:
    case 0xd:
    case 0x12:
        return 1;
    }

    return 0;
}
