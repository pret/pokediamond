#ifndef POKEDIAMOND_MAP_H
#define POKEDIAMOND_MAP_H

typedef struct {
    u8 MapAreaData;
    u8 field_0x1;
    u16 Matrix;
    u16 MapScripts;
    u16 MapLevelScripts;
    u16 MapTexts;
    u16 DayMusic;
    u16 NightMusic;
    u16 WildPokemonData;
    u16 MapEvents;
    u16 MapName;
    u8 WeatherType;
    u8 field_0x15;
    u8 field_0x16;
    u8 field_0x17;
} MapHeader;

#endif //POKEDIAMOND_MAP_H
