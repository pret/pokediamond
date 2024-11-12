#include "poketch.h"

#include "global.h"

#include "MI_memory.h"
#include "pokemon.h"

extern u16 BoxMon_GetAlternateForm(struct BoxPokemon *mon);

static const u8 sMarkingMapInitialPos[][2] = {
    { 0x68, 0x98 },
    { 0x78, 0x98 },
    { 0x88, 0x98 },
    { 0x98, 0x98 },
    { 0xA8, 0x98 },
    { 0xB8, 0x98 },
};

u32 Save_Poketch_sizeof(void) {
    return sizeof(struct Poketch);
}

void Save_Poketch_Init(struct Poketch *poketch) {
    int i;

    for (i = 0; i < 32; i++) {
        poketch->unlockedApps[i] = 0;
    }
    poketch->numApps = 0;
    poketch->selectedApp = 0;
    poketch->isGiven = 0;
    poketch->color = 0;
    poketch->pedometerActive = 0;
    poketch->stepCounter = 0;
    poketch->alarmActive = 0;
    poketch->alarmHour = 0;
    poketch->alarmMinute = 0;
    poketch->calendarMonth = 1; // January
    poketch->calendarFlags = 0;
    for (i = 0; i < 6; i++) {
        poketch->markingMapPos[i][0] = sMarkingMapInitialPos[i][0];
        poketch->markingMapPos[i][1] = sMarkingMapInitialPos[i][1];
    }
    for (i = 0; i < 12; i++) {
        poketch->pokemonHistory[i][0] = SPECIES_NONE;
        poketch->pokemonHistory[i][1] = 0;
    }
    poketch->dotArtistEnabled = 0;
    Save_Poketch_UnlockApp(poketch, POKETCH_DIGITAL_WATCH);
}

void Save_Poketch_Give(struct Poketch *poketch) {
    poketch->isGiven = TRUE;
}

BOOL Save_Poketch_IsGiven(struct Poketch *poketch) {
    return poketch->isGiven;
}

u8 Save_Poketch_AppIsUnlocked(struct Poketch *poketch, PoketchApp app) {
    return poketch->unlockedApps[app];
}

BOOL Save_Poketch_UnlockApp(struct Poketch *poketch, PoketchApp app) {
    GF_ASSERT(app >= FIRST_POKETCH_APP_ID && app < NUM_POKETCH_APPS);
    if (poketch->numApps < NUM_POKETCH_APPS && !poketch->unlockedApps[app]) {
        poketch->unlockedApps[app] = TRUE;
        poketch->numApps++;
        if (app == POKETCH_PEDOMETER) // pedometer
        {
            poketch->pedometerActive = TRUE;
        }
        return TRUE;
    }
    return FALSE;
}

PoketchApp Save_Poketch_GetSelectedApp(struct Poketch *poketch) {
    return (PoketchApp)poketch->selectedApp;
}

PoketchApp Save_Poketch_CycleNextApp(struct Poketch *poketch) {
    PoketchApp app = (PoketchApp)poketch->selectedApp;
    PoketchApp prev = app;

    while (1) {
        if (++app >= NUM_POKETCH_APPS) {
            app = FIRST_POKETCH_APP_ID;
        }
        if (app == prev) {
            break;
        }
        if (poketch->unlockedApps[app]) {
            break;
        }
    }
    poketch->selectedApp = (s8)app;
    return (PoketchApp)poketch->selectedApp;
}

u8 Save_Poketch_GetScreenTint(struct Poketch *poketch) {
    GF_ASSERT(poketch != NULL);
    return poketch->color;
}

void Save_Poketch_SetScreenTint(struct Poketch *poketch, u32 color) {
    GF_ASSERT(poketch != NULL);
    GF_ASSERT(color < 8);
    poketch->color = (u8)color;
}

u32 Save_Poketch_GetStepCounter(struct Poketch *poketch) {
    return poketch->stepCounter;
}

void Save_Poketch_SetStepCounter(struct Poketch *poketch, u32 steps) {
    if (poketch->pedometerActive) {
        poketch->stepCounter = steps;
    }
}

BOOL Save_Poketch_GetAlarmState(struct Poketch *poketch) {
    return poketch->alarmActive;
}

void Save_Poketch_GetAlarmSetTime(struct Poketch *poketch, u32 *hour_p, u32 *min_p) {
    *hour_p = poketch->alarmHour;
    *min_p = poketch->alarmMinute;
}

void Save_Poketch_SetAlarm(struct Poketch *poketch, BOOL enabled, u32 hour, u32 minute) {
    poketch->alarmActive = enabled;
    poketch->alarmHour = hour;
    poketch->alarmMinute = minute;
}

void Save_Poketch_CalendarDateHighlight(struct Poketch *poketch, u32 month, u32 day) {
    if (poketch->calendarMonth == month) {
        poketch->calendarFlags |= (1u << (day - 1));
    } else {
        poketch->calendarMonth = (u8)month;
        poketch->calendarFlags = (1u << (day - 1));
    }
}

void Save_Poketch_CalendarDateUnhighlight(struct Poketch *poketch, u32 month, u32 day) {
    if (poketch->calendarMonth == month) {
        poketch->calendarFlags &= ~(1u << (day - 1));
    } else {
        poketch->calendarMonth = (u8)month;
        poketch->calendarFlags = 0;
    }
}

BOOL Save_Poketch_CalendarDateIsHighlighted(struct Poketch *poketch, u32 month, u32 day) {
    if (poketch->calendarMonth == month) {
        return (BOOL)((poketch->calendarFlags >> (day - 1)) & 1);
    } else {
        return FALSE;
    }
}

void Save_Poketch_MarkingMapSetPos(struct Poketch *poketch, s32 mark, u8 x, u8 y) {
    GF_ASSERT(mark < 6);
    poketch->markingMapPos[mark][0] = x;
    poketch->markingMapPos[mark][1] = y;
}

void Save_Poketch_MarkingMapGetPos(struct Poketch *poketch, s32 mark, u8 *x_p, u8 *y_p) {
    GF_ASSERT(mark < 6);
    *x_p = poketch->markingMapPos[mark][0];
    *y_p = poketch->markingMapPos[mark][1];
}

u32 Save_Poketch_DotArtistIsEnabled(struct Poketch *poketch) {
    return poketch->dotArtistEnabled;
}

void Save_Poketch_DotArtistGetDrawing(struct Poketch *poketch, void *grid) {
    if (poketch->dotArtistEnabled) {
        MI_CpuCopy8(poketch->dotArtistGrid, grid, DOT_ARTIST_SIZE);
    }
}

void Save_Poketch_DotArtistSetDrawingAndEnable(struct Poketch *poketch, void *grid) {
    MI_CpuCopy8(grid, poketch->dotArtistGrid, DOT_ARTIST_SIZE);
    poketch->dotArtistEnabled = TRUE;
}

void Save_Poketch_PokemonHistoryAddMon(struct Poketch *poketch, struct BoxPokemon *mon) {
    int i = Save_Poketch_PokemonHistoryGetFirstEmptySlot(poketch);
    if (i >= 12) {
        for (i = 0; i < 11; i++) {
            poketch->pokemonHistory[i][0] = poketch->pokemonHistory[i + 1][0];
            poketch->pokemonHistory[i][1] = poketch->pokemonHistory[i + 1][1];
        }
        i = 11;
    }
    poketch->pokemonHistory[i][0] = (u16)GetBoxMonData(mon, MON_DATA_SPECIES, NULL);
    poketch->pokemonHistory[i][1] = BoxMon_GetAlternateForm(mon);
}

int Save_Poketch_PokemonHistoryGetFirstEmptySlot(struct Poketch *poketch) {
    int i;
    for (i = 0; i < 12; i++) {
        if (poketch->pokemonHistory[i][0] == SPECIES_NONE) {
            return i;
        }
    }
    return i;
}

void Save_Poketch_PokemonHistoryGetSlotN(struct Poketch *poketch, s32 i, u32 *species_p, u32 *form_p) {
    GF_ASSERT(i < 12);
    GF_ASSERT(poketch->pokemonHistory[i][0] != SPECIES_NONE);
    *species_p = poketch->pokemonHistory[i][0];
    *form_p = poketch->pokemonHistory[i][1];
}

struct Poketch *Save_Poketch_Get(struct SaveData *save) {
    return (struct Poketch *)SaveArray_Get(save, 5);
}
