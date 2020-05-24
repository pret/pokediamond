//
// Created by red031000 on 2020-05-24.
//

#ifndef POKEDIAMOND_GFLIB_SYSCTL_H
#define POKEDIAMOND_GFLIB_SYSCTL_H

#include "global.h"
#include "main.h"

extern struct Unk21C48B8 gUnknown21C48B8;
struct Unk2106FA0 gBacklightTop;

void FUN_02000DF4(void);
void FUN_02000E0C(void);
void FUN_02000E7C(FSOverlayID id, struct Unk21DBE18 * arg1);
void FUN_02000E9C(void);
void FUN_02000EC8(u32 parameter);
void FUN_02000EE8(void);
void DoSoftReset(u32 parameter);
void FUN_02000F4C(u32 arg0, u32 arg1);
void InitializeMainRNG(void);
void FUN_02000FE8(void);

#endif //POKEDIAMOND_GFLIB_SYSCTL_H
