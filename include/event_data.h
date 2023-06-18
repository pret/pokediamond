#ifndef GUARD_SCRIPT_STATE_H
#define GUARD_SCRIPT_STATE_H

#include "save.h"

typedef struct ScriptState //todo this is not a very good name
{
    u16 vars[288];
    u8 flags[364];
} ScriptState;

u32 SaveArray_Flags_sizeof(void);
void SaveArray_Flags_Init(struct ScriptState * state);
struct ScriptState * SaveArray_Flags_Get(struct SaveData * save);
BOOL CheckFlagInArray(struct ScriptState * state, u16 flag_id);
void SetFlagInArray(struct ScriptState * state, u16 flag_id);
void ClearFlagInArray(struct ScriptState * state, u16 flag_id);
u8 * GetFlagAddr(struct ScriptState * state, u16 flag_id);
u16 * GetVarAddr(struct ScriptState * state, u16 var_id);

#endif //GUARD_SCRIPT_STATE_H
