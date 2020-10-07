#ifndef POKEDIAMOND_DAYCARE_H
#define POKEDIAMOND_DAYCARE_H

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

u32 Sav2_DayCare_sizeof(void);
void Sav2_DayCare_init(struct DayCare * daycare);
struct DayCareMon * Sav2_DayCare_GetMonX(struct DayCare * daycare, s32 i);
struct BoxPokemon * DayCareMon_GetBoxMon(struct DayCareMon * dcmon);
struct DayCareMail * DayCareMon_GetExtras(struct DayCareMon * dcmon);
u32 DayCareMon_GetSteps(struct DayCareMon * dcmon);
struct Mail * DayCareMail_GetCapsule(struct DayCareMail * dcmail);
u32 Sav2_DayCare_GetEggPID(struct DayCare * daycare);
u8 Sav2_DayCare_GetEggCycleCounter(struct DayCare * daycare);
void DayCareMon_SetSteps(struct DayCareMon * dcmon, u32 steps);
void DayCareMon_AddSteps(struct DayCareMon * dcmon, u32 steps);
void Sav2_DayCare_SetEggPID(struct DayCare * daycare, u32 pid);
void Sav2_DayCare_SetEggCycleCounter(struct DayCare * daycare, u8 count);
BOOL Sav2_DayCare_MasudaCheck(struct DayCare * daycare);
void DayCareMon_Copy(struct DayCareMon * dest, const struct DayCareMon * src);
void DayCareMon_Extras_init(struct DayCareMail * mail);
void DayCareMon_Init(struct DayCareMon * mon);
struct DayCare * Sav2_DayCare_get(struct SaveBlock2 * sav2);

#endif //POKEDIAMOND_DAYCARE_H
