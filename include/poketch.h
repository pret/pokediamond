#ifndef POKEDIAMOND_POKETCH_H
#define POKEDIAMOND_POKETCH_H

#include "save_block_2.h"

#define DOT_ARTIST_SIZE (480 / 4) // 2bpp

typedef enum PoketchApp
{
    FIRST_POKETCH_APP_ID = 0,
    POKETCH_DIGITAL_WATCH = FIRST_POKETCH_APP_ID,
    POKETCH_CALCULATOR,
    POKETCH_MEMO_PAD,
    POKETCH_PEDOMETER,
    POKETCH_POKEMON_LIST,
    POKETCH_FRIENDSHIP_CHECKER,
    POKETCH_DOWSING_MACHINE,
    POKETCH_BERRY_SEARCHER,
    POKETCH_DAY_CARE_CHECKER,
    POKETCH_POKEMON_HISTORY,
    POKETCH_COUNTER,
    POKETCH_ANALOG_WATCH,
    POKETCH_MARKING_MAP,
    POKETCH_LINK_SEARCHER,
    POKETCH_COIN_TOSS,
    POKETCH_MOVE_TESTER,
    POKETCH_CALENDAR,
    POKETCH_DOT_ARTIST,
    POKETCH_ROULETTE,
    POKETCH_TRAINER_COUNTER,
    POKETCH_KITCHEN_TIMER,
    POKETCH_COLOR_CHANGER,
    POKETCH_MATCHUP_CHECKER,
    POKETCH_STOPWATCH,
    POKETCH_ALARM_CLOCK,
    NUM_POKETCH_APPS
}
PoketchApp;

struct SavePoketch
{
    u8 isGiven:1; // set by completing the coupon sidequest in Jubilife
    u8 pedometerActive:1; // set when you receive the Pedometer
    u8 dotArtistEnabled:1; // set when you access dotArtist for the first time
    u8 color:3; // set by Color Changer
    // Green, Yellow, Orange, Red, Purple, Blue, Turquoise, White
    u8 padding_00_6:2; // silence warnings
    s8 numApps;
    s8 selectedApp;
    u8 unlockedApps[32]; // should be 25, one for each app
    u8 filler_23[1]; // silence warnings
    u32 stepCounter; // increments while pedometerActive is 1
    u16 alarmActive:1;
    u16 alarmHour:5;
    u16 alarmMinute:6;
    u16 padding_28_C:4; // silence warnings
    u8 dotArtistGrid[DOT_ARTIST_SIZE];
    u8 filler_A2[1]; // silence warnings
    u32 calendarFlags; // flag X set == day (X + 1) marked
    u8 calendarMonth;
    // X and Y coordinates for each of six markings
    u8 markingMapPos[6][2];
    u8 filler_B5[1]; // silence warnings
    u16 pokemonHistory[12][2];
};

u32 Sav2_Poketch_sizeof(void);
void Sav2_Poketch_init(struct SavePoketch * poketch);
void Sav2_Poketch_Give(struct SavePoketch * poketch);
BOOL Sav2_Poketch_IsGiven(struct SavePoketch * poketch);
u8 Sav2_Poketch_AppIsUnlocked(struct SavePoketch * poketch, PoketchApp app);
BOOL Sav2_Poketch_UnlockApp(struct SavePoketch * poketch, PoketchApp app);
PoketchApp Sav2_Poketch_GetSelectedApp(struct SavePoketch * poketch);
PoketchApp Sav2_Poketch_CycleNextApp(struct SavePoketch * poketch);
u8 Sav2_Poketch_GetScreenTint(struct SavePoketch * poketch);
void Sav2_Poketch_SetScreenTint(struct SavePoketch * poketch, u32 color);
u32 Sav2_Poketch_GetStepCounter(struct SavePoketch * poketch);
void Sav2_Poketch_SetStepCounter(struct SavePoketch * poketch, u32 steps);
BOOL Sav2_Poketch_GetAlarmState(struct SavePoketch * poketch);
void Sav2_Poketch_GetAlarmSetTime(struct SavePoketch * poketch, u32 * hour_p, u32 * min_p);
void Sav2_Poketch_SetAlarm(struct SavePoketch * poketch, BOOL enabled, u32 hour, u32 minute);
void Sav2_Poketch_CalendarDateHighlight(struct SavePoketch * poketch, u32 month, u32 day);
void Sav2_Poketch_CalendarDateUnhighlight(struct SavePoketch * poketch, u32 month, u32 day);
BOOL Sav2_Poketch_CalendarDateIsHighlighted(struct SavePoketch * poketch, u32 month, u32 day);
void Sav2_Poketch_MarkingMapSetPos(struct SavePoketch * poketch, s32 mark, u8 x, u8 y);
void Sav2_Poketch_MarkingMapGetPos(struct SavePoketch * poketch, s32 mark, u8 * x_p, u8 * y_p);
u32 Sav2_Poketch_DotArtistIsEnabled(struct SavePoketch * poketch);
void Sav2_Poketch_DotArtistGetDrawing(struct SavePoketch * poketch, void * grid);
void Sav2_Poketch_DotArtistSetDrawingAndEnable(struct SavePoketch * poketch, void * grid);
void Sav2_Poketch_PokemonHistoryAddMon(struct SavePoketch * poketch, struct BoxPokemon * mon);
int Sav2_Poketch_PokemonHistoryGetFirstEmptySlot(struct SavePoketch * poketch);
void Sav2_Poketch_PokemonHistoryGetSlotN(struct SavePoketch * poketch, s32 i, u32 * species_p, u32 * forme_p);
struct SavePoketch * Sav2_Poketch_get(struct SaveBlock2 * sav2);

#endif //POKEDIAMOND_POKETCH_H
