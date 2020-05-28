//============================================================================================
/**
 * @file	safari_train.h
 * @brief	サファリ電車関連
 * @date	2006.04.29
 *
 */
//============================================================================================
#ifndef __SAFARI_TRAIN_H__
#define __SAFARI_TRAIN_H__

#include "common.h"

extern void SafariTrain_Setup(FIELDSYS_WORK *fsys);
extern void SafariTrain_Init(FIELDSYS_WORK *fsys);
extern void SafariTrain_Move(FIELDSYS_WORK *fsys, const u16 inDstPos, const u16 inMoveType);
extern u32 SafariTrain_CheckPos(FIELDSYS_WORK *fsys, const u16 inPos);

#endif	//__SAFARI_TRAIN_H__
