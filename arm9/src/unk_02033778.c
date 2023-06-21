#include "global.h"
#include "unk_02033778.h"
#include "unk_0202F150.h"
#include "player_data.h"

extern PlayerProfile *sub_0202DFA4(s32 param0);
extern u32 sub_0202E020(s32 param0);
extern u32 sub_0202E044(s32 param0);
extern u32 sub_02029B40(u32 param0, u32 param1, u32 param2, u32 language);
extern void sub_02029B90(u32 param0, u32 param1, u32 param2, u32 param3);

void sub_02033778(u32 param0)
{
    s32 unk = sub_02030F20();
    if (sub_0202DFA4(0) != NULL)
    {
        for (s32 i = 0; i < unk; i++)
        {
            if (sub_02031190() != i)
            {
                sub_020337C8(param0, sub_0202E020(i), sub_0202E044(i), PlayerProfile_GetLanguage(sub_0202DFA4(i)));
            }
        }
    }
}

void sub_020337C8(u32 param0, u32 param1, u32 param2, u32 language)
{
    if (sub_02029B40(param0, param1, param2, language) == 0)
    {
        sub_02029B90(param0, param1, param2, 1);
    }
}
