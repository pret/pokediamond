#ifndef GUARD_SAVE_VARS_FLAGS_H
#define GUARD_SAVE_VARS_FLAGS_H

#include "save.h"

typedef struct SaveVarsFlags
{
    u16 vars[288];
    u8 flags[364];
} SaveVarsFlags;

u32 Save_VarsFlags_sizeof(void);
void Save_VarsFlags_Init(struct SaveVarsFlags * state);
struct SaveVarsFlags * Save_VarsFlags_Get(struct SaveData * save);
BOOL CheckFlagInArray(struct SaveVarsFlags * state, u16 flag_id);
void SetFlagInArray(struct SaveVarsFlags * state, u16 flag_id);
void ClearFlagInArray(struct SaveVarsFlags * state, u16 flag_id);
u8 * GetFlagAddr(struct SaveVarsFlags * state, u16 flag_id);
u16 * GetVarAddr(struct SaveVarsFlags * state, u16 var_id);

#endif //GUARD_SAVE_VARS_FLAGS_H
