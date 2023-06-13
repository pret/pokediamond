#ifndef POKEDIAMOND_HALL_OF_FAME_H
#define POKEDIAMOND_HALL_OF_FAME_H

#define NUM_HOF_RECORDS 30

#include "RTC_api.h"

struct HOFMon
{
    /* 0x00 */ u16 species;
    /* 0x02 */ u8 level;
    /* 0x03 */ u8 forme;
    /* 0x04 */ u32 personality;
    /* 0x08 */ u32 otid;
    /* 0x0C */ u16 nickname[POKEMON_NAME_LENGTH + 1];
    /* 0x22 */ u16 otname[PLAYER_NAME_LENGTH + 1];
    /* 0x32 */ u16 moves[4];
    /* 0x3A */ u8 padding[2];
};

struct HOFParty
{
    struct HOFMon party[6];
    u16 year;
    u8 month;
    u8 day;
};

typedef struct HallOfFame
{
    struct HOFParty parties[NUM_HOF_RECORDS];
    u32 next_record;
    u32 num_total;
} HallOfFame;

struct HofDisplayMon
{
    struct String * nickname;
    struct String * otname;
    u32 personality;
    u32 otid;
    u16 species;
    u8 level;
    u8 forme;
    u16 moves[4];
};

u32 Save_HOF_sizeof(void);
void Save_HOF_Init(struct HallOfFame * hof);
void Save_HOF_RecordParty(struct HallOfFame * hof, struct PlayerParty * party, RTCDate * date);
u32 Save_HOF_GetNumRecords(struct HallOfFame * hof);
int Save_HOF_TranslateRecordIdx(struct HallOfFame * hof, int a1);
u32 Save_HOF_RecordCountMons(struct HallOfFame * hof, int a1);
void Save_HOF_GetMonStatsByIndexPair(struct HallOfFame * hof, int a1, int a2, struct HofDisplayMon * dest);
void Save_HOF_GetClearDate(struct HallOfFame * hof, int a1, RTCDate * dest);

#endif //POKEDIAMOND_HALL_OF_FAME_H
