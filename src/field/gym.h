//============================================================================================
/**
 * @file	gym.h
 * @brief	ジム関連
 * @date	2006.02.02
 *
 */
//============================================================================================
#ifndef __GYM_H__
#define __GYM_H__

#include "common.h"

//水ジム
extern void GYM_CheckWaterGymButton(FIELDSYS_WORK *fsys);
extern void GYM_SetupWaterGym(FIELDSYS_WORK *fsys);
extern BOOL GYM_HitCheckWaterGym(	FIELDSYS_WORK *fsys,
							const int inGridX, const int inGridZ,
							const fx32 inHeight, BOOL *outHit	);

//ゴーストジム
extern void GYM_SetupGhostGym(FIELDSYS_WORK *fsys);
extern void GYM_MoveGhostGymLift(FIELDSYS_WORK *fsys);

//鋼ジム
extern void GYM_SetupSteelGym(FIELDSYS_WORK *fsys);
extern void GYM_EndSteelGym(FIELDSYS_WORK *fsys);
extern BOOL GYM_HitCheckSteelGym(	FIELDSYS_WORK *fsys,
									const int inGridX, const int inGridZ,
									const fx32 inHeight, BOOL *outHit	);
extern BOOL GYM_CheckSteelLift(FIELDSYS_WORK *fsys);

//格闘ジム
extern void GYM_SetupCombatGym(FIELDSYS_WORK *fsys);
extern void GYM_EndCombatGym(FIELDSYS_WORK *fsys);
extern BOOL GYM_CheckCombatWall(FIELDSYS_WORK *fsys);
extern BOOL GYM_HitCheckCombatGym(	FIELDSYS_WORK *fsys,
									const int inGridX, const int inGridZ,
									const fx32 inHeight, BOOL *outHit	);

//電気ジム
extern void GYM_SetupElecGym(FIELDSYS_WORK *fsys);
extern void GYM_EndElecGym(FIELDSYS_WORK *fsys);
extern BOOL GYM_HitCheckElecGym(	FIELDSYS_WORK *fsys,
									const int inGridX, const int inGridZ,
									const fx32 inHeight, BOOL *outHit	);
extern void GYM_RotateElecGymGear(FIELDSYS_WORK *fsys, const u8 inRotate);
#endif //__GYM_H__
