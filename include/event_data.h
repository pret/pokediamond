#ifndef GUARD_SCRIPT_STATE_H
#define GUARD_SCRIPT_STATE_H

#include "save_block_2.h"

struct ScriptState
{
    u16 vars[288];
    u8 flags[364];
};

u32 SavArray_Flags_sizeof(void);
void SavArray_Flags_init(struct ScriptState * state);
struct ScriptState * SavArray_Flags_get(struct SaveBlock2 * sav2);
BOOL CheckFlagInArray(struct ScriptState * state, u16 flag_id);
void SetFlagInArray(struct ScriptState * state, u16 flag_id);
void ClearFlagInArray(struct ScriptState * state, u16 flag_id);
u8 * GetFlagAddr(struct ScriptState * state, u16 flag_id);
u16 * GetVarAddr(struct ScriptState * state, u16 var_id);

#endif //GUARD_SCRIPT_STATE_H
