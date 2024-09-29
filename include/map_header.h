#ifndef POKEDIAMOND_MAP_HEADER_H
#define POKEDIAMOND_MAP_HEADER_H

#include "nitro/types.h"

struct MapHeader {
    u8 area_data_bank;
    u8 move_model_bank;
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
    u8 map_type;
    u8 battle_bg              : 4;
    u8 is_bike_allowed        : 1;
    u8 is_running_allowed     : 1; // unused
    u8 is_escape_rope_allowed : 1;
    u8 is_fly_allowed         : 1;
};

u8 MapHeader_GetAreaDataBank(u32 mapno);
u8 MapHeader_GetMoveModelBank(u32 mapno);
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
u8 MapHeader_GetBattleBg(u32 mapno);
u8 MapHeader_IsEscapeRopeAllowed(u32 mapno);
u8 MapHeader_IsFlyAllowed(u32 mapno);
u8 MapHeader_IsBikeAllowed(u32 mapno);
u8 MapHeader_GetMapType(u32 mapno);
BOOL MapHeader_IsOutdoorNotTown(u32 mapno);
BOOL MapHeader_MapIsOnMainMatrix(u32 mapno);
BOOL MapHeader_IsPokemonCenter(u32 mapno);
BOOL MapHeader_IsCave(u32 mapno);
BOOL MapHeader_IsBuilding(u32 mapno);
BOOL MapHeader_IsOutdoor(u32 mapno);
BOOL MapHeader_MapIsPokemonCenter(u32 mapno);
BOOL MapHeader_MapIsUnionRoom(u32 mapno);
BOOL MapHeader_MapIsMtCoronetFeebasRoom(u32 mapno);
BOOL MapHeader_MapIsTrophyGarden(u32 mapno);
BOOL MapHeader_MapIsAmitySquare(u32 mapno);
BOOL MapHeader_MapIsSpearPillar(u32 mapno);
BOOL MapHeader_MapIsPokemonCenterSecondFloor(u32 mapno);
u16 MapHeader_GetMapEvolutionMethod(u32 mapno);

#endif // POKEDIAMOND_MAP_HEADER_H
