#include "global.h"
#include "unk_0207FC5C.h"
#include "constants/pokemon.h"

#pragma thumb on

struct UnkStruct_020FB788
{
    u32 unk_0;
    u16 unk_4;
    u16 unk_6;
    u16 unk_8;
    u16 unk_A;
};

const struct UnkStruct_020FB788 UNK_020FB788[] = {
    {
        MON_DATA_HOENN_RIBBON_98,
        0x0048,
        0x0000,
        0x0000,
        0x0050
    }, {
        MON_DATA_COOL_RIBBON,
        0x0049,
        0x0000,
        0x0001,
        0x0051
    }, {
        MON_DATA_HOENN_RIBBON_79,
        0x004A,
        0x0000,
        0x0002,
        0x0052
    }, {
        MON_DATA_HOENN_RIBBON_80,
        0x004B,
        0x0000,
        0x0003,
        0x0053
    }, {
        MON_DATA_HOENN_RIBBON_81,
        0x004C,
        0x0000,
        0x0004,
        0x0054
    }, {
        MON_DATA_HOENN_RIBBON_82,
        0x0049,
        0x0001,
        0x0005,
        0x0055
    }, {
        MON_DATA_HOENN_RIBBON_83,
        0x004A,
        0x0001,
        0x0006,
        0x0056
    }, {
        MON_DATA_HOENN_RIBBON_84,
        0x004B,
        0x0001,
        0x0007,
        0x0057
    }, {
        MON_DATA_HOENN_RIBBON_85,
        0x004C,
        0x0001,
        0x0008,
        0x0058
    }, {
        MON_DATA_HOENN_RIBBON_86,
        0x0049,
        0x0002,
        0x0009,
        0x0059
    }, {
        MON_DATA_HOENN_RIBBON_87,
        0x004A,
        0x0002,
        0x000A,
        0x005A
    }, {
        MON_DATA_HOENN_RIBBON_88,
        0x004B,
        0x0002,
        0x000B,
        0x005B
    }, {
        MON_DATA_HOENN_RIBBON_89,
        0x004C,
        0x0002,
        0x000C,
        0x005C
    }, {
        MON_DATA_HOENN_RIBBON_90,
        0x0049,
        0x0003,
        0x000D,
        0x005D
    }, {
        MON_DATA_HOENN_RIBBON_91,
        0x004A,
        0x0003,
        0x000E,
        0x005E
    }, {
        MON_DATA_HOENN_RIBBON_92,
        0x004B,
        0x0003,
        0x000F,
        0x005F
    }, {
        MON_DATA_HOENN_RIBBON_93,
        0x004C,
        0x0003,
        0x0010,
        0x0060
    }, {
        MON_DATA_HOENN_RIBBON_94,
        0x0049,
        0x0004,
        0x0011,
        0x0061
    }, {
        MON_DATA_HOENN_RIBBON_95,
        0x004A,
        0x0004,
        0x0012,
        0x0062
    }, {
        MON_DATA_HOENN_RIBBON_96,
        0x004B,
        0x0004,
        0x0013,
        0x0063
    }, {
        MON_DATA_HOENN_RIBBON_97,
        0x004C,
        0x0004,
        0x0014,
        0x0064
    }, {
        MON_DATA_HOENN_RIBBON_99,
        0x004E,
        0x0000,
        0x0015,
        0x0065
    }, {
        MON_DATA_HOENN_RIBBON_100,
        0x004D,
        0x0000,
        0x0016,
        0x0066
    }, {
        MON_DATA_HOENN_RIBBON_101,
        0x004F,
        0x0001,
        0x0017,
        0x0067
    }, {
        MON_DATA_HOENN_RIBBON_102,
        0x0050,
        0x0002,
        0x0018,
        0x0068
    }, {
        MON_DATA_HOENN_RIBBON_103,
        0x0051,
        0x0001,
        0x0019,
        0x8000
    }, {
        MON_DATA_HOENN_RIBBON_104,
        0x0051,
        0x0003,
        0x001A,
        0x8001
    }, {
        MON_DATA_HOENN_RIBBON_105,
        0x0051,
        0x0004,
        0x001B,
        0x8002
    }, {
        MON_DATA_HOENN_RIBBON_106,
        0x0052,
        0x0003,
        0x001C,
        0x00B2
    }, {
        MON_DATA_HOENN_RIBBON_107,
        0x0052,
        0x0004,
        0x001D,
        0x00BE
    }, {
        MON_DATA_HOENN_RIBBON_108,
        0x0053,
        0x0000,
        0x001E,
        0x00BF
    }, {
        MON_DATA_HOENN_RIBBON_109,
        0x0053,
        0x0001,
        0x001F,
        0x00B2
    }, {
        MON_DATA_SINNOH_CHAMP_RIBBON,
        0x0058,
        0x0000,
        0x0020,
        0x0069
    }, {
        MON_DATA_SINNOH_RIBBON_122,
        0x0059,
        0x0000,
        0x0021,
        0x006A
    }, {
        MON_DATA_SINNOH_RIBBON_123,
        0x005A,
        0x0000,
        0x0022,
        0x006B
    }, {
        MON_DATA_SINNOH_RIBBON_124,
        0x005B,
        0x0000,
        0x0023,
        0x006C
    }, {
        MON_DATA_SINNOH_RIBBON_125,
        0x005C,
        0x0000,
        0x0024,
        0x006D
    }, {
        MON_DATA_SINNOH_RIBBON_126,
        0x0059,
        0x0001,
        0x0025,
        0x006E
    }, {
        MON_DATA_SINNOH_RIBBON_127,
        0x005A,
        0x0001,
        0x0026,
        0x006F
    }, {
        MON_DATA_SINNOH_RIBBON_128,
        0x005B,
        0x0001,
        0x0027,
        0x0070
    }, {
        MON_DATA_SINNOH_RIBBON_129,
        0x005C,
        0x0001,
        0x0028,
        0x0071
    }, {
        MON_DATA_SINNOH_RIBBON_130,
        0x0059,
        0x0002,
        0x0029,
        0x0072
    }, {
        MON_DATA_SINNOH_RIBBON_131,
        0x005A,
        0x0002,
        0x002A,
        0x0073
    }, {
        MON_DATA_SINNOH_RIBBON_132,
        0x005B,
        0x0002,
        0x002B,
        0x0074
    }, {
        MON_DATA_SINNOH_RIBBON_133,
        0x005C,
        0x0002,
        0x002C,
        0x0075
    }, {
        MON_DATA_SINNOH_RIBBON_134,
        0x0059,
        0x0003,
        0x002D,
        0x0076
    }, {
        MON_DATA_SINNOH_RIBBON_135,
        0x005A,
        0x0003,
        0x002E,
        0x0077
    }, {
        MON_DATA_SINNOH_RIBBON_136,
        0x005B,
        0x0003,
        0x002F,
        0x0078
    }, {
        MON_DATA_SINNOH_RIBBON_137,
        0x005C,
        0x0003,
        0x0030,
        0x0079
    }, {
        MON_DATA_SINNOH_RIBBON_138,
        0x0059,
        0x0004,
        0x0031,
        0x007A
    }, {
        MON_DATA_SINNOH_RIBBON_139,
        0x005A,
        0x0004,
        0x0032,
        0x007B
    }, {
        MON_DATA_SINNOH_RIBBON_140,
        0x005B,
        0x0004,
        0x0033,
        0x007C
    }, {
        MON_DATA_SINNOH_RIBBON_141,
        0x005C,
        0x0004,
        0x0034,
        0x007D
    }, {
        MON_DATA_SINNOH_RIBBON_26,
        0x005D,
        0x0000,
        0x0035,
        0x007E
    }, {
        MON_DATA_SINNOH_RIBBON_27,
        0x005E,
        0x0000,
        0x0036,
        0x007F
    }, {
        MON_DATA_SINNOH_RIBBON_28,
        0x005F,
        0x0000,
        0x0037,
        0x0080
    }, {
        MON_DATA_SINNOH_RIBBON_29,
        0x0060,
        0x0000,
        0x0038,
        0x0081
    }, {
        MON_DATA_SINNOH_RIBBON_30,
        0x0061,
        0x0000,
        0x0039,
        0x0082
    }, {
        MON_DATA_SINNOH_RIBBON_31,
        0x0062,
        0x0000,
        0x003A,
        0x0083
    }, {
        MON_DATA_SINNOH_RIBBON_32,
        0x0063,
        0x0002,
        0x003B,
        0x0084
    }, {
        MON_DATA_SINNOH_RIBBON_33,
        0x0064,
        0x0000,
        0x003C,
        0x0085
    }, {
        MON_DATA_SINNOH_RIBBON_34,
        0x0065,
        0x0001,
        0x003D,
        0x0086
    }, {
        MON_DATA_SINNOH_RIBBON_35,
        0x0066,
        0x0002,
        0x003E,
        0x0087
    }, {
        MON_DATA_SINNOH_RIBBON_36,
        0x0067,
        0x0003,
        0x003F,
        0x0088
    }, {
        MON_DATA_SINNOH_RIBBON_37,
        0x0068,
        0x0000,
        0x0040,
        0x0089
    }, {
        MON_DATA_SINNOH_RIBBON_38,
        0x0069,
        0x0002,
        0x0041,
        0x008A
    }, {
        MON_DATA_SINNOH_RIBBON_39,
        0x006A,
        0x0001,
        0x0042,
        0x008B
    }, {
        MON_DATA_SINNOH_RIBBON_40,
        0x006B,
        0x0003,
        0x0043,
        0x008C
    }, {
        MON_DATA_SINNOH_RIBBON_41,
        0x006C,
        0x0000,
        0x0044,
        0x008D
    }, {
        MON_DATA_SINNOH_RIBBON_42,
        0x006D,
        0x0000,
        0x0045,
        0x008E
    }, {
        MON_DATA_SINNOH_RIBBON_43,
        0x006E,
        0x0001,
        0x0046,
        0x008F
    }, {
        MON_DATA_SINNOH_RIBBON_44,
        0x006F,
        0x0003,
        0x0047,
        0x0090
    }, {
        MON_DATA_SINNOH_RIBBON_45,
        0x0070,
        0x0000,
        0x0048,
        0x0091
    }, {
        MON_DATA_SINNOH_RIBBON_46,
        0x0071,
        0x0000,
        0x0049,
        0x8007
    }, {
        MON_DATA_SINNOH_RIBBON_47,
        0x0072,
        0x0003,
        0x004A,
        0x8008
    }, {
        MON_DATA_SINNOH_RIBBON_48,
        0x0073,
        0x0001,
        0x004B,
        0x8009
    }, {
        MON_DATA_SINNOH_RIBBON_49,
        0x0074,
        0x0001,
        0x004C,
        0x800A
    }, {
        MON_DATA_SINNOH_RIBBON_50,
        0x0075,
        0x0000,
        0x004D,
        0x800B
    }, {
        MON_DATA_SINNOH_RIBBON_51,
        0x0076,
        0x0001,
        0x004E,
        0x800C
    }, {
        MON_DATA_SINNOH_RIBBON_52,
        0x0077,
        0x0000,
        0x004F,
        0x800D
    }
};

u32 FUN_0207FC5C(u8 a0, u32 a1)
{
    switch (a1)
    {
    case 0:
        return UNK_020FB788[a0].unk_0;
    case 1:
        return UNK_020FB788[a0].unk_4;
    case 2:
        return UNK_020FB788[a0].unk_6;
    case 3:
        return UNK_020FB788[a0].unk_8;
    case 4:
        return UNK_020FB788[a0].unk_A;
    default:
        return 0;
    }
}

int FUN_0207FCC0(u8 * a0, u32 a1)
{
    int ret = (int)UNK_020FB788[a1].unk_A;
    if (ret & 0x8000)
        ret = a0[(u8)ret] + 0x92;
    return ret;
}

u8 FUN_0207FCE0(u32 a0)
{
    int ret = (int)UNK_020FB788[a0].unk_A;
    if (ret & 0x8000)
        return (u8)ret;
    return 0xFF;
}
