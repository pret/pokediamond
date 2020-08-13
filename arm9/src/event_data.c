#include "global.h"
#include "save_block_2.h"
#include "event_data.h"

#pragma thumb on

u8 UNK_021C5A14[8];

u8 * GetFlagAddr(struct ScriptState * state, u16 flag_id);

u32 SavArray_Flags_sizeof(void)
{
    return sizeof(struct ScriptState);
}

void SavArray_Flags_init(struct ScriptState * state)
{
    memset(state, 0, sizeof(struct ScriptState));
}

struct ScriptState * SavArray_Flags_get(struct SaveBlock2 * sav2)
{
    return (struct ScriptState *)SavArray_get(sav2, 4);
}

BOOL CheckFlagInArray(struct ScriptState * state, u16 flag_id)
{
    u8 * ptr = GetFlagAddr(state, flag_id);
    if (ptr != NULL)
    {
        int mask = 1 << (flag_id % 8);
        if (*ptr & mask)
            return TRUE;
    }
    return FALSE;
}

void SetFlagInArray(struct ScriptState * state, u16 flag_id)
{
    u8 * ptr = GetFlagAddr(state, flag_id);
    if (ptr != NULL)
    {
        int mask = 1 << (flag_id % 8);
        *ptr |= mask;
    }
}

void ClearFlagInArray(struct ScriptState * state, u16 flag_id)
{
    u8 * ptr = GetFlagAddr(state, flag_id);
    if (ptr != NULL)
    {
        int mask = 1 << (flag_id % 8);
        *ptr &= 0xFF ^ mask;
    }
}

u8 * GetFlagAddr(struct ScriptState * state, u16 flag_id)
{
    if (flag_id == 0)
        return 0;
    if (flag_id < 0x4000)
    {
        GF_ASSERT((flag_id / 8) < 364);
        return &state->flags[flag_id / 8];
    }
    else
    {
        GF_ASSERT(((flag_id - 0x4000) / 8) < 8);
        return &UNK_021C5A14[(flag_id - 0x4000) / 8];
    }
}

u16 * GetVarAddr(struct ScriptState * state, u16 var_id)
{
    GF_ASSERT((var_id - 0x4000) < 288);
    return &state->vars[var_id - 0x4000];
}
