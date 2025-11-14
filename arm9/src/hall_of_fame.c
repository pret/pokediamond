#include "hall_of_fame.h"

#include "global.h"

#include "MI_memory.h"
#include "RTC_api.h"
#include "heap.h"
#include "party.h"
#include "pokemon.h"
#include "save.h"
#include "string16.h"

u32 Save_HOF_sizeof(void) {
    return sizeof(struct HallOfFame);
}

void Save_HOF_Init(struct HallOfFame *hof) {
    MI_CpuClear32(hof, sizeof(struct HallOfFame));
}

void Save_HOF_RecordParty(struct HallOfFame *hof, struct Party *party, RTCDate *date) {
    GF_ASSERT(hof != NULL);
    GF_ASSERT(hof->next_record < NUM_HOF_RECORDS);
    if (hof->num_total < 9999) {
        struct HOFParty *hof_party = &hof->parties[hof->next_record];
        int nmons = Party_GetCount(party);
        struct String *str = String_New(POKEMON_NAME_LENGTH + 1, HEAP_ID_DEFAULT);
        MI_CpuClear16(hof_party->party, 6 * sizeof(struct HOFMon));
        int i, j;
        for (i = 0, j = 0; i < nmons; i++) {
            struct Pokemon *mon = Party_GetMonByIndex(party, i);
            BOOL lock = AcquireMonLock(mon);
            if (!GetMonData(mon, MON_DATA_IS_EGG, NULL)) {
                hof_party->party[j].species = (u16)GetMonData(mon, MON_DATA_SPECIES, NULL);
                hof_party->party[j].level = (u8)GetMonData(mon, MON_DATA_LEVEL, NULL);
                hof_party->party[j].form = (u8)GetMonData(mon, MON_DATA_FORM, NULL);
                hof_party->party[j].personality = GetMonData(mon, MON_DATA_PERSONALITY, NULL);
                hof_party->party[j].otid = GetMonData(mon, MON_DATA_OT_ID, NULL);
                hof_party->party[j].moves[0] = (u16)GetMonData(mon, MON_DATA_MOVE1, NULL);
                hof_party->party[j].moves[1] = (u16)GetMonData(mon, MON_DATA_MOVE2, NULL);
                hof_party->party[j].moves[2] = (u16)GetMonData(mon, MON_DATA_MOVE3, NULL);
                hof_party->party[j].moves[3] = (u16)GetMonData(mon, MON_DATA_MOVE4, NULL);
                if (str != NULL) {
                    GetMonData(mon, MON_DATA_NICKNAME_STRING, str);
                    CopyStringToU16Array(str, hof_party->party[j].nickname, POKEMON_NAME_LENGTH + 1);
                    GetMonData(mon, MON_DATA_OT_NAME_STRING, str);
                    CopyStringToU16Array(str, hof_party->party[j].otname, PLAYER_NAME_LENGTH + 1);
                } else {
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
        if (hof->next_record >= NUM_HOF_RECORDS) {
            hof->next_record = 0;
        }
        hof->num_total++;
        if (str != NULL) {
            String_Delete(str);
        }
    }
}

u32 Save_HOF_GetNumRecords(struct HallOfFame *hof) {
    GF_ASSERT(hof != NULL);
    GF_ASSERT(hof->next_record < NUM_HOF_RECORDS);
    if (hof->num_total < NUM_HOF_RECORDS) {
        return hof->num_total;
    } else {
        return NUM_HOF_RECORDS;
    }
}

int Save_HOF_TranslateRecordIdx(struct HallOfFame *hof, int a1) {
    GF_ASSERT(hof != NULL);
    GF_ASSERT(hof->next_record < NUM_HOF_RECORDS);
    GF_ASSERT(a1 < NUM_HOF_RECORDS);
    return (int)(hof->num_total - a1);
}

u32 Save_HOF_RecordCountMons(struct HallOfFame *hof, int a1) {
    GF_ASSERT(hof != NULL);
    GF_ASSERT(hof->next_record < NUM_HOF_RECORDS);
    GF_ASSERT(a1 < NUM_HOF_RECORDS);
    int hofno = (int)(hof->next_record - 1 - a1);
    if (hofno < 0) {
        hofno += NUM_HOF_RECORDS;
    }
    struct HOFParty *hof_party = &hof->parties[hofno];
    u32 i;
    for (i = 0; i < 6; i++) {
        if (hof_party->party[i].species == SPECIES_NONE) {
            break;
        }
    }
    return i;
}

void Save_HOF_GetMonStatsByIndexPair(struct HallOfFame *hof, int a1, int a2, struct HofDisplayMon *dest) {
    GF_ASSERT(hof != NULL);
    GF_ASSERT(hof->next_record < NUM_HOF_RECORDS);
    GF_ASSERT(a1 < NUM_HOF_RECORDS);
    int hofno = (int)(hof->next_record - 1 - a1);
    if (hofno < 0) {
        hofno += NUM_HOF_RECORDS;
    }
    struct HOFMon *mon = &hof->parties[hofno].party[a2];
    dest->species = mon->species;
    dest->level = mon->level;
    dest->personality = mon->personality;
    dest->otid = mon->otid;
    dest->form = mon->form;
    CopyU16ArrayToString(dest->nickname, mon->nickname);
    CopyU16ArrayToString(dest->otname, mon->otname);
    for (int i = 0; i < 4; i++) {
        dest->moves[i] = mon->moves[i];
    }
}

void Save_HOF_GetClearDate(struct HallOfFame *hof, int a1, RTCDate *dest) {
    GF_ASSERT(hof != NULL);
    GF_ASSERT(hof->next_record < NUM_HOF_RECORDS);
    GF_ASSERT(a1 < NUM_HOF_RECORDS);
    int hofno = (int)(hof->next_record - 1 - a1);
    if (hofno < 0) {
        hofno += NUM_HOF_RECORDS;
    }
    struct HOFParty *party = &hof->parties[hofno];
    dest->year = party->year;
    dest->month = party->month;
    dest->day = party->day;
    dest->week = RTC_WEEK_SUNDAY;
}
