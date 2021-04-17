#ifndef POKEDIAMOND_MAP_HEADER_H
#define POKEDIAMOND_MAP_HEADER_H

struct MapHeader
{
    u8 area_data_bank;
    u8 unk1;
    u16 matrix_id;
    u16 scripts_bank;
    u16 level_scripts_bank;
    u16 msg_bank;
    u16 day_music_id;
    u16 night_music_id;
    u16 wild_encounter_bank;
    u16 events_bank;
    u16 mapsec;
    u8 weather_type;
    u8 camera_type;
    u8 unk16;
    u8 unk17_0:4;
    u8 is_bike_allowed:1;
    u8 unk17_5:1;
    u8 unk17_6:1;
    u8 is_fly_allowed:1;
};

u8 MapHeader_GetAreaDataBank(u32 mapno);
u8 MapHeader_GetField1(u32 mapno);
u16 MapHeader_GetMatrixId(u32 mapno);
u16 MapHeader_GetMsgBank(u32 mapno);
u16 MapHeader_GetScriptsBank(u32 mapno);
u16 MapHeader_GetLevelScriptsBank(u32 mapno);
u16 MapHeader_GetDayMusicId(u32 mapno);
u16 MapHeader_GetNightMusicId(u32 mapno);
BOOL MapHeader_HasWildEncounters(u32 mapno);
u16 MapHeader_GetWildEncounterBank(u32 mapno);
u16 MapHeader_GetEventsBank(u32 mapno);
u16 MapHeader_GetMapSec(u32 mapno);
u8 MapHeader_GetWeatherType(u32 mapno);
u8 MapHeader_GetCameraType(u32 mapno);
u8 MapHeader_GetField17_0(u32 mapno);
u8 MapHeader_GetField17_6(u32 mapno);
u8 MapHeader_IsFlyAllowed(u32 mapno);
u8 MapHeader_IsBikeAllowed(u32 mapno);
u8 MapHeader_GetField16(u32 mapno);
BOOL FUN_020348E4(u32 mapno);
BOOL MapHeader_MapIsOnOverworldMatrix(u32 mapno);
BOOL FUN_0203491C(u32 mapno);
BOOL FUN_02034930(u32 mapno);
BOOL FUN_02034944(u32 mapno);
BOOL FUN_02034964(u32 mapno);
BOOL FUN_02034984(u32 mapno);
BOOL FUN_02034998(u32 mapno);
BOOL FUN_020349AC(u32 mapno);
BOOL FUN_020349B8(u32 mapno);
BOOL FUN_020349CC(u32 mapno);
BOOL FUN_020349D8(u32 mapno);
BOOL FUN_020349E4(u16 a0);
u16 FUN_02034A04(u16 a0);

#endif //POKEDIAMOND_MAP_HEADER_H
