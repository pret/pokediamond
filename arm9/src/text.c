#include "text.h"
#include "heap.h"

const struct FontInfo *gFonts = NULL;

u8 UNK_021C5734[0x200];
u32 UNK_021C5714[8];
u8 UNK_021C570C[8];

extern u32 FUN_0200CA7C(void *param0, u32 param1, u32 param2);

extern void *FUN_0201B6C8(void);
extern void FUN_0200CAB4(u32 param0);
extern void FUN_0201C238(void);

THUMB_FUNC void SetFontsPointer(const struct FontInfo *fonts)
{
    gFonts = fonts;
}

THUMB_FUNC u8 FUN_0201BCC8(void *param0, u32 param1, u32 param2)
{
    u32 *r4 = UNK_021C5714;
    s32 i;
    for (i = 0; i < 8; i++, r4++)
    {
        if (r4[0] != 0)
        {
            continue;
        }
        UNK_021C5714[i] = FUN_0200CA7C(param0, param1, param2);
        if (UNK_021C5714[i] != 0)
        {
            break;
        }
        i = 8;
        break;
    }
    return (u8)i;
}

THUMB_FUNC void FUN_0201BCFC(u32 param0)
{
    GF_ASSERT(param0 < 8);
    GF_ASSERT(UNK_021C5714[param0] != 0);
    if (param0 >= 8)
    {
        return;
    }
    if (UNK_021C5714[param0] == 0)
    {
        return;
    }
    void *r5 = FUN_0201B6C8();
    if (r5)
    {
        FUN_0201C238();
        FreeToHeap(r5);
    }
    FUN_0200CAB4(UNK_021C5714[param0]);
    UNK_021C5714[param0] = 0;
}

THUMB_FUNC BOOL FUN_0201BD44(u32 param0)
{
    return UNK_021C5714[param0] ? TRUE : FALSE;
}

THUMB_FUNC void FUN_0201BD5C(void)
{
    for (s32 i = 0; i < 8; i++)
    {
        UNK_021C5714[i] = 0;
    }
}

THUMB_FUNC u8 FUN_0201BD70(u32 param0)
{
    return (u8)FUN_0201BD44(param0);
}

THUMB_FUNC void FUN_0201BD7C(u32 param0)
{
    FUN_0201BCFC(param0);
}
