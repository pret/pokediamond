#ifndef POKEDIAMOND_GAME_INIT_H
#define POKEDIAMOND_GAME_INIT_H

#include "main.h"

void FUN_02015EA0(void);
void FUN_02015ED4(void);
void FUN_02015EF4(void);
void Main_SetVBlankIntrCB(void (*a0)(void *), void * a1);
void FUN_02015F1C(void);
BOOL FUN_02015F34(void (*a0)(void *), void * a1);
void Main_CallHBlankCallback(void);
void Main_ToggleHBlankInterrupt(BOOL enableFlag);
void FUN_02015FC8(void);
void InitSystemForTheGame(void);
void InitGraphicMemory(void);
void * AllocAndReadFile(u32 heap_id, const char * path);
void OpenAndReadWholeFile(const char * path, void ** ptr);
u32 GetFilenameHash(const s8 * str);
int GetFileCacheId(u32 hash);
int AddFileToCache(void * contents, u32 hash);
void ClearFileCache(void);
void * OpenFileCached(const s8 * str, u32 heap_id);
void InitKeypadAndTouchpad(void);
void FUN_02016438(u8 a0);
void FUN_02016444(u8 a0);
void FUN_02016454(u8 a0);
void ReadKeypadAndTocuhpad(void);
void ApplyButtonModeToInput(void);
void SetKeyRepeatTimers(int x, int y);
void SetSoftResetDisableMask(u8 a0);
void ClearSoftResetDisableMask(u8 a0);

#endif //POKEDIAMOND_GAME_INIT_H
