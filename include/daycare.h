#ifndef POKEDIAMOND_DAYCARE_H
#define POKEDIAMOND_DAYCARE_H

#include "global.h"

struct DayCareMail
{
    struct Mail seal;
    u16 ot_name[OT_NAME_LENGTH + 1];
    u16 nickname[POKEMON_NAME_LENGTH + 1];
    u8 padding_5E[2];
};

struct DayCareMon
{
    struct BoxPokemon mon;
    struct DayCareMail mail;
    u32 steps;
};

struct DayCare
{
    struct DayCareMon mons[2];
    u32 egg_pid;
    u8 egg_cycles;
    u8 padding_1DD[3];
};

u32 Save_DayCare_sizeof(void);
void Save_DayCare_Init(struct DayCare * daycare);
struct DayCareMon * Save_DayCare_GetMonX(struct DayCare * daycare, s32 i);
struct BoxPokemon * DayCareMon_GetBoxMon(struct DayCareMon * dcmon);
struct DayCareMail * DayCareMon_GetExtras(struct DayCareMon * dcmon);
u32 DayCareMon_GetSteps(struct DayCareMon * dcmon);
struct Mail * DayCareMail_GetCapsule(struct DayCareMail * dcmail);
u32 Save_DayCare_GetEggPID(struct DayCare * daycare);
u8 Save_DayCare_GetEggCycleCounter(struct DayCare * daycare);
void DayCareMon_SetSteps(struct DayCareMon * dcmon, u32 steps);
void DayCareMon_AddSteps(struct DayCareMon * dcmon, u32 steps);
void Save_DayCare_SetEggPID(struct DayCare * daycare, u32 pid);
void Save_DayCare_SetEggCycleCounter(struct DayCare * daycare, u8 count);
BOOL Save_DayCare_MasudaCheck(struct DayCare * daycare);
void DayCareMon_Copy(struct DayCareMon * dest, const struct DayCareMon * src);
void DayCareMon_Extras_Init(struct DayCareMail * mail);
void DayCareMon_Init(struct DayCareMon * mon);
struct DayCare * Save_DayCare_Get(struct SaveBlock2 * sav2);

#endif //POKEDIAMOND_DAYCARE_H
