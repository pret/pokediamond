#ifndef POKEDIAMOND_POKEMON_STORAGE_SYSTEM_H
#define POKEDIAMOND_POKEMON_STORAGE_SYSTEM_H

#include "pokemon.h"

#define NUM_BOXES                        18u
#define MONS_PER_BOX                     30u
#define BOX_NAME_LENGTH                  20u
#define NUM_DEFAULT_WALLPAPERS           16u
#define NUM_BONUS_WALLPAPERS              8u
#define NUM_WALLPAPERS ((u32)(NUM_DEFAULT_WALLPAPERS + NUM_BONUS_WALLPAPERS))

typedef struct PCStorage
{
    /* 0x00000 */ u32 curBox;
    /* 0x00004 */ struct BoxPokemon boxes[NUM_BOXES][MONS_PER_BOX];
    /* 0x11EE4 */ u16 names[NUM_BOXES][BOX_NAME_LENGTH];
    /* 0x121B4 */ u8 wallpapers[NUM_BOXES];
    /* 0x121C6 */ u8 unlockedWallpapers;
    /* 0x121C7 */ u8 pad_byte; // suppresses mwcc warning
} PCStorage;

void PCStorage_Init(struct PCStorage * pc);
u32 PCStorage_sizeof(void);
void PCStorage_InitializeBoxes(struct PCStorage * pc);
BOOL PCStorage_PlaceMonInFirstEmptySlotInAnyBox(struct PCStorage * pc, struct BoxPokemon * boxmon);
BOOL PCStorage_PlaceMonInBoxFirstEmptySlot(struct PCStorage * pc, int boxno, struct BoxPokemon * boxmon);
BOOL PCStorage_PlaceMonInBoxByIndexPair(struct PCStorage * pc, int boxno, int slotno, struct BoxPokemon * boxmon);
void PCStorage_DeleteBoxMonByIndexPair(struct PCStorage * pc, int boxno, int slotno);
int PCStorage_GetActiveBox(struct PCStorage * pc);
int PCStorage_FindFirstBoxWithEmptySlot(struct PCStorage * pc);
BOOL PCStorage_FindFirstEmptySlot(struct PCStorage * pc, int * boxno, int * slotno);
int PCStorage_CountMonsAndEggsInAllBoxes(struct PCStorage * pc);
void PCStorage_SetActiveBox(struct PCStorage * pc, int boxno);
u8 PCStorage_GetBoxWallpaper(struct PCStorage * pc, int boxno);
void PCStorage_SetBoxWallpaper(struct PCStorage * pc, int boxno, u8 wallpaper);
void PCStorage_GetBoxName(struct PCStorage * pc, int boxno, struct String * ret);
void PCStorage_SetBoxName(struct PCStorage * pc, int boxno, struct String * src);
int PCStorage_CountMonsAndEggsInBox(struct PCStorage * pc, int boxno);
int PCStorage_CountMonsInBox(struct PCStorage * pc, int boxno);
int PCStorage_CountMonsInAllBoxes(struct PCStorage * pc);
void PCStorage_SetBoxMonDataByIndexPair(struct PCStorage * pc, int boxno, int slotno, u32 attr, void * value);
struct BoxPokemon * PCStorage_GetMonByIndexPair(struct PCStorage * pc, int boxno, int slotno);
void PCStorage_UnlockBonusWallpaper(struct PCStorage * pc, int wallpaper);
BOOL PCStorage_IsBonusWallpaperUnlocked(struct PCStorage * pc, int wallpaper);
int PCStorage_CountUnlockedBonusWallpapers(struct PCStorage * pc);

#endif //POKEDIAMOND_POKEMON_STORAGE_SYSTEM_H
