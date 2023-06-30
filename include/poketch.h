#ifndef POKEDIAMOND_POKETCH_H
#define POKEDIAMOND_POKETCH_H

#include "save.h"

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

typedef struct Poketch
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
} Poketch;

u32 Save_Poketch_sizeof(void);
void Save_Poketch_Init(struct Poketch * poketch);
void Save_Poketch_Give(struct Poketch * poketch);
BOOL Save_Poketch_IsGiven(struct Poketch * poketch);
u8 Save_Poketch_AppIsUnlocked(struct Poketch * poketch, PoketchApp app);
BOOL Save_Poketch_UnlockApp(struct Poketch * poketch, PoketchApp app);
PoketchApp Save_Poketch_GetSelectedApp(struct Poketch * poketch);
PoketchApp Save_Poketch_CycleNextApp(struct Poketch * poketch);
u8 Save_Poketch_GetScreenTint(struct Poketch * poketch);
void Save_Poketch_SetScreenTint(struct Poketch * poketch, u32 color);
u32 Save_Poketch_GetStepCounter(struct Poketch * poketch);
void Save_Poketch_SetStepCounter(struct Poketch * poketch, u32 steps);
BOOL Save_Poketch_GetAlarmState(struct Poketch * poketch);
void Save_Poketch_GetAlarmSetTime(struct Poketch * poketch, u32 * hour_p, u32 * min_p);
void Save_Poketch_SetAlarm(struct Poketch * poketch, BOOL enabled, u32 hour, u32 minute);
void Save_Poketch_CalendarDateHighlight(struct Poketch * poketch, u32 month, u32 day);
void Save_Poketch_CalendarDateUnhighlight(struct Poketch * poketch, u32 month, u32 day);
BOOL Save_Poketch_CalendarDateIsHighlighted(struct Poketch * poketch, u32 month, u32 day);
void Save_Poketch_MarkingMapSetPos(struct Poketch * poketch, s32 mark, u8 x, u8 y);
void Save_Poketch_MarkingMapGetPos(struct Poketch * poketch, s32 mark, u8 * x_p, u8 * y_p);
u32 Save_Poketch_DotArtistIsEnabled(struct Poketch * poketch);
void Save_Poketch_DotArtistGetDrawing(struct Poketch * poketch, void * grid);
void Save_Poketch_DotArtistSetDrawingAndEnable(struct Poketch * poketch, void * grid);
void Save_Poketch_PokemonHistoryAddMon(struct Poketch * poketch, struct BoxPokemon * mon);
int Save_Poketch_PokemonHistoryGetFirstEmptySlot(struct Poketch * poketch);
void Save_Poketch_PokemonHistoryGetSlotN(struct Poketch * poketch, s32 i, u32 * species_p, u32 * form_p);
struct Poketch * Save_Poketch_Get(struct SaveData * save);

#endif //POKEDIAMOND_POKETCH_H
