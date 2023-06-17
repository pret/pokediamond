#include "global.h"
#include "pokemon.h"
#include "mail.h"
#include "save.h"
#include "daycare.h"

u32 Save_DayCare_sizeof(void)
{
    return sizeof(struct DayCare);
}

void Save_DayCare_Init(struct DayCare * daycare)
{
    memset(daycare, 0, sizeof(struct DayCare));
    ZeroBoxMonData(&daycare->mons[0].mon);
    ZeroBoxMonData(&daycare->mons[1].mon);
    daycare->egg_pid = 0;
    daycare->egg_cycles = 0;
}

struct DayCareMon * Save_DayCare_GetMonX(struct DayCare * daycare, s32 i)
{
    return &daycare->mons[i];
}

struct BoxPokemon * DayCareMon_GetBoxMon(struct DayCareMon * dcmon)
{
    return &dcmon->mon;
}

struct DayCareMail * DayCareMon_GetExtras(struct DayCareMon * dcmon)
{
    return &dcmon->mail;
}

u32 DayCareMon_GetSteps(struct DayCareMon * dcmon)
{
    return dcmon->steps;
}

struct Mail * DayCareMail_GetCapsule(struct DayCareMail * dcmail)
{
    return &dcmail->seal;
}

u32 Save_DayCare_GetEggPID(struct DayCare * daycare)
{
    return daycare->egg_pid;
}

u8 Save_DayCare_GetEggCycleCounter(struct DayCare * daycare)
{
    return daycare->egg_cycles;
}

void DayCareMon_SetSteps(struct DayCareMon * dcmon, u32 steps)
{
    dcmon->steps = steps;
}

void DayCareMon_AddSteps(struct DayCareMon * dcmon, u32 steps)
{
    dcmon->steps += steps;
}

void Save_DayCare_SetEggPID(struct DayCare * daycare, u32 pid)
{
    daycare->egg_pid = pid;
}

void Save_DayCare_SetEggCycleCounter(struct DayCare * daycare, u8 count)
{
    daycare->egg_cycles = count;
}

BOOL Save_DayCare_MasudaCheck(struct DayCare * daycare)
{
    // Checks if the pokemon come from different countries.
    // Uses language as a proxy for country, even though it
    // only accounts for European languages and Japanese.
    // If true, shiny odds are increased (see overlay 05).
    return GetBoxMonData(&daycare->mons[0].mon, MON_DATA_GAME_LANGUAGE, NULL) != GetBoxMonData(&daycare->mons[1].mon, MON_DATA_GAME_LANGUAGE, NULL);
}

void DayCareMon_Copy(struct DayCareMon * dest, const struct DayCareMon * src)
{
    *dest = *src;
}

void DayCareMon_Extras_Init(struct DayCareMail * mail)
{
    int i;

    for (i = 0; i < PLAYER_NAME_LENGTH + 1; i++)
        mail->ot_name[i] = 0;
    for (i = 0; i < POKEMON_NAME_LENGTH + 1; i++)
        mail->nickname[i] = 0;
    mail->ot_name[0] = EOS;
    mail->nickname[0] = EOS;
}

void DayCareMon_Init(struct DayCareMon * mon)
{
    ZeroBoxMonData(&mon->mon);
    mon->steps = 0;
    DayCareMon_Extras_Init(&mon->mail);
}

struct DayCare * Save_DayCare_Get(struct SaveData * save)
{
    return (struct DayCare *)SaveArray_Get(save, 8);
}
