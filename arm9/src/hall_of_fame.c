#include "global.h"
#include "pokemon.h"
#include "save_block_2.h"
#include "MI_memory.h"
#include "party.h"
#include "string16.h"
#include "RTC_api.h"
#include "hall_of_fame.h"

#pragma thumb on

u32 Sav2_HOF_sizeof(void)
{
    return sizeof(struct HallOfFame);
}

void Sav2_HOF_init(struct HallOfFame * hof)
{
    MI_CpuClear32(hof, sizeof(struct HallOfFame));
}

void Sav2_HOF_RecordParty(struct HallOfFame * hof, struct PlayerParty * party, RTCDate * date)
{
    GF_ASSERT(hof != NULL);
    GF_ASSERT(hof->next_record < NUM_HOF_RECORDS);
    if (hof->num_total < 9999)
    {
        struct HOFParty * hof_party = &hof->parties[hof->next_record];
        int nmons = GetPartyCount(party);
        struct String * str = String_ctor(POKEMON_NAME_LENGTH + 1, 0);
        MI_CpuClear16(hof_party->party, 6 * sizeof(struct HOFMon));
        int i, j;
        for (i = 0, j = 0; i < nmons; i++)
        {
            struct Pokemon * mon = GetPartyMonByIndex(party, i);
            BOOL lock = AcquireMonLock(mon);
            if (!GetMonData(mon, MON_DATA_IS_EGG, NULL))
            {
                hof_party->party[j].species = (u16)GetMonData(mon, MON_DATA_SPECIES, NULL);
                hof_party->party[j].level = (u8)GetMonData(mon, MON_DATA_LEVEL, NULL);
                hof_party->party[j].forme = (u8)GetMonData(mon, MON_DATA_FORME, NULL);
                hof_party->party[j].personality = GetMonData(mon, MON_DATA_PERSONALITY, NULL);
                hof_party->party[j].otid = GetMonData(mon, MON_DATA_OTID, NULL);
                hof_party->party[j].moves[0] = (u16)GetMonData(mon, MON_DATA_MOVE1, NULL);
                hof_party->party[j].moves[1] = (u16)GetMonData(mon, MON_DATA_MOVE2, NULL);
                hof_party->party[j].moves[2] = (u16)GetMonData(mon, MON_DATA_MOVE3, NULL);
                hof_party->party[j].moves[3] = (u16)GetMonData(mon, MON_DATA_MOVE4, NULL);
                if (str != NULL)
                {
                    GetMonData(mon, MON_DATA_NICKNAME_3, str);
                    CopyStringToU16Array(str, hof_party->party[j].nickname, POKEMON_NAME_LENGTH + 1);
                    GetMonData(mon, MON_DATA_OT_NAME_2, str);
                    CopyStringToU16Array(str, hof_party->party[j].otname, OT_NAME_LENGTH + 1);
                }
                else
                {
                    hof_party->party[j].nickname[0] = EOS;
                    hof_party->party[j].otname[0] = EOS;
                }
                j++;
            }
            ReleaseMonLock(mon, lock);
        }
        hof_party->year = (u16)date->year;
        hof_party->month = (u8)date->month;
        hof_party->day = (u8)date->day;
        hof->next_record++;
        if (hof->next_record >= NUM_HOF_RECORDS)
            hof->next_record = 0;
        hof->num_total++;
        if (str != NULL)
            String_dtor(str);
    }
}

u32 Sav2_HOF_GetNumRecords(struct HallOfFame * hof)
{
    GF_ASSERT(hof != NULL);
    GF_ASSERT(hof->next_record < NUM_HOF_RECORDS);
    if (hof->num_total < NUM_HOF_RECORDS)
        return hof->num_total;
    else
        return NUM_HOF_RECORDS;
}

int Sav2_HOF_TranslateRecordIdx(struct HallOfFame * hof, int a1)
{
    GF_ASSERT(hof != NULL);
    GF_ASSERT(hof->next_record < NUM_HOF_RECORDS);
    GF_ASSERT(a1 < NUM_HOF_RECORDS);
    return (int)(hof->num_total - a1);
}

u32 Sav2_HOF_RecordCountMons(struct HallOfFame * hof, int a1)
{
    GF_ASSERT(hof != NULL);
    GF_ASSERT(hof->next_record < NUM_HOF_RECORDS);
    GF_ASSERT(a1 < NUM_HOF_RECORDS);
    int hofno = (int)(hof->next_record - 1 - a1);
    if (hofno < 0)
        hofno += NUM_HOF_RECORDS;
    struct HOFParty * hof_party = &hof->parties[hofno];
    u32 i;
    for (i = 0; i < 6; i++)
    {
        if (hof_party->party[i].species == SPECIES_NONE)
            break;
    }
    return i;
}

void Sav2_HOF_GetMonStatsByIndexPair(struct HallOfFame * hof, int a1, int a2, struct HofDisplayMon * dest)
{
    GF_ASSERT(hof != NULL);
    GF_ASSERT(hof->next_record < NUM_HOF_RECORDS);
    GF_ASSERT(a1 < NUM_HOF_RECORDS);
    int hofno = (int)(hof->next_record - 1 - a1);
    if (hofno < 0)
        hofno += NUM_HOF_RECORDS;
    struct HOFMon * mon = &hof->parties[hofno].party[a2];
    dest->species = mon->species;
    dest->level = mon->level;
    dest->personality = mon->personality;
    dest->otid = mon->otid;
    dest->forme = mon->forme;
    CopyU16ArrayToString(dest->nickname, mon->nickname);
    CopyU16ArrayToString(dest->otname, mon->otname);
    for (int i = 0; i < 4; i++)
    {
        dest->moves[i] = mon->moves[i];
    }
}

void Sav2_HOF_GetClearDate(struct HallOfFame * hof, int a1, RTCDate * dest)
{
    GF_ASSERT(hof != NULL);
    GF_ASSERT(hof->next_record < NUM_HOF_RECORDS);
    GF_ASSERT(a1 < NUM_HOF_RECORDS);
    int hofno = (int)(hof->next_record - 1 - a1);
    if (hofno < 0)
        hofno += NUM_HOF_RECORDS;
    struct HOFParty *party = &hof->parties[hofno];
    dest->year = party->year;
    dest->month = party->month;
    dest->day = party->day;
    dest->week = RTC_WEEK_SUNDAY;
}
