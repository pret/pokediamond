#include "global.h"
#include "save.h"
#include "event_data.h"

u8 UNK_021C5A14[8];

u8 * GetFlagAddr(struct SaveVarsFlags * state, u16 flag_id);

u32 Save_VarsFlags_sizeof(void)
{
    return sizeof(struct SaveVarsFlags);
}

void Save_VarsFlags_Init(struct SaveVarsFlags * state)
{
    memset(state, 0, sizeof(struct SaveVarsFlags));
}

struct SaveVarsFlags * Save_VarsFlags_Get(struct SaveData * save)
{
    return (struct SaveVarsFlags *)SaveArray_Get(save, 4);
}

BOOL CheckFlagInArray(struct SaveVarsFlags * state, u16 flag_id)
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

void SetFlagInArray(struct SaveVarsFlags * state, u16 flag_id)
{
    u8 * ptr = GetFlagAddr(state, flag_id);
    if (ptr != NULL)
    {
        int mask = 1 << (flag_id % 8);
        *ptr |= mask;
    }
}

void ClearFlagInArray(struct SaveVarsFlags * state, u16 flag_id)
{
    u8 * ptr = GetFlagAddr(state, flag_id);
    if (ptr != NULL)
    {
        int mask = 1 << (flag_id % 8);
        *ptr &= 0xFF ^ mask;
    }
}

u8 * GetFlagAddr(struct SaveVarsFlags * state, u16 flag_id)
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

u16 * GetVarAddr(struct SaveVarsFlags * state, u16 var_id)
{
    GF_ASSERT((var_id - 0x4000) < 288);
    return &state->vars[var_id - 0x4000];
}
