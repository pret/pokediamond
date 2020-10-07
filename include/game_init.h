#ifndef POKEDIAMOND_GAME_INIT_H
#define POKEDIAMOND_GAME_INIT_H

#include "main.h"

void FUN_02015EA0(void);
void FUN_02015ED4(void);
void FUN_02015EF4(void);
void Main_SetVBlankIntrCB(void (*a0)(void *), void * a1);
void FUN_02015F1C(void);
BOOL FUN_02015F34(void (*a0)(void *), void * a1);
void FUN_02015F6C(void);
void Main_HBlankIntr(BOOL a0);
void FUN_02015FC8(void);
void InitSystemForTheGame(void);
void InitGraphicMemory(void);
void * FUN_020161A4(u32 heap_id, const char * path);
void FUN_020161F8(const char * path, void ** ptr);
u32 FUN_02016230(const s8 * str);
int FUN_020162A0(u32 a0);
int FUN_020162C8(void * a0, u32 a1);
void FUN_020162FC(void);
void * FUN_02016324(const s8 * str, u32 heap_id);
void FUN_020163BC(void);
void FUN_02016438(u8 a0);
void FUN_02016444(u8 a0);
void FUN_02016454(u8 a0);
void FUN_02016464(void);
void FUN_02016568(void);
void FUN_0201669C(int x, int y);
void FUN_020166A8(u8 a0);
void FUN_020166B8(u8 a0);

#endif //POKEDIAMOND_GAME_INIT_H
