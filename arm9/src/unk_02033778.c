#include "global.h"
#include "unk_02033778.h"
#include "unk_0202F150.h"
#include "player_data.h"

extern PlayerProfile *FUN_0202DFA4(s32 param0);
extern u32 FUN_0202E020(s32 param0);
extern u32 FUN_0202E044(s32 param0);
extern u32 FUN_02029B40(u32 param0, u32 param1, u32 param2, u32 language);
extern void FUN_02029B90(u32 param0, u32 param1, u32 param2, u32 param3);

void FUN_02033778(u32 param0)
{
    s32 unk = FUN_02030F20();
    if (FUN_0202DFA4(0) != NULL)
    {
        for (s32 i = 0; i < unk; i++)
        {
            if (FUN_02031190() != i)
            {
                FUN_020337C8(param0, FUN_0202E020(i), FUN_0202E044(i), PlayerProfile_GetLanguage(FUN_0202DFA4(i)));
            }
        }
    }
}

void FUN_020337C8(u32 param0, u32 param1, u32 param2, u32 language)
{
    if (FUN_02029B40(param0, param1, param2, language) == 0)
    {
        FUN_02029B90(param0, param1, param2, 1);
    }
}
