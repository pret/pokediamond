//============================================================================================
/**
 * @file	sway_grass_enc.h
 * @brief	揺れ草エンカウント
 * @author	saito GAME FREAK inc.
 * @date	2006.02.14
 */
//============================================================================================
#ifndef _SWAY_GRASS_ENC_H_
#define _SWAY_GRASS_ENC_H_

#include "common.h"
#include "field_common.h"
#include "eoa.h"

#include "sway_grass_hist_def.h"

#include "poketool/monsno.h"

#define SWAY_GRASS_CHAIN_MAX	(999)	//揺れ草連鎖最大数

typedef struct SWAY_GRASS_tag * SWAY_GRASS_PTR;

typedef enum {
	SWAY_GRASS_ENC_NORMAL,
	SWAY_GRASS_ENC_SP,
}SWAY_GRASS_ENC;

extern SWAY_GRASS_PTR SwayGrass_AllocSwayGrass(const int inHeapID);
extern void SwayGrass_FreeSwayGrass(SWAY_GRASS_PTR outSwayGrass);

extern void SwayGrass_InitSwayGrass(SWAY_GRASS_PTR outSwayGrass);
extern BOOL SwayGrass_SearchSwayGrass(	FIELDSYS_WORK * fsys,
							const int inX, const int inZ,
							SWAY_GRASS_PTR ioSwayGrass);
extern void	SwayGrass_SetChain(	FIELDSYS_WORK * fsys,
								const int inBattleResult,
								SWAY_GRASS_PTR ioSwayGrass);
extern void SwayGrass_SetSwayGrassAnime(FIELDSYS_WORK * fsys, SWAY_GRASS_PTR outSwayGrass);
extern BOOL SwayGrass_CheckSwayGrassAnimeEnd(SWAY_GRASS_PTR ioSwayGrass);
extern int	SwayGrass_CheckSpEncount( const int inX, const int inZ,
							FIELDSYS_WORK * fsys,
							SWAY_GRASS_PTR ioSwayGrass,
							int *outUseEncTable,
							BOOL *outMonsDeside,
							BOOL *outRare);
extern void SwayGrass_SetEncMonsNoLv(SWAY_GRASS_PTR outSwayGrass, const int inMonsNo, const int inMonsLv);
extern void SwayGrass_GetEncMonsNoLv(SWAY_GRASS_PTR inSwayGrass,  int *outMonsNo, int *outMonsLv);

extern const BOOL SwayGrass_IsSwayEncRetern(const SWAY_GRASS_PTR inSwayGrass);

extern void SwayGrass_CheckIO(FIELDSYS_WORK * fsys);
extern BOOL SwayGrass_CheckValid( const SWAY_GRASS_PTR inSwayGrass );
extern void SwayGrass_Setup(FIELDSYS_WORK * fsys);
extern BOOL SwayGrass_SetupEvent(GMEVENT_CONTROL * event);

extern void SwayGrass_UpDateChain(FIELDSYS_WORK * fsys);
//extern void SwayGrass_ChangeHistRewritePos(FIELDSYS_WORK * fsys);


extern int SwayGrass_GetChain(FIELDSYS_WORK * fsys);
extern void SwayGrass_ChargePokeSearcher(FIELDSYS_WORK *fsys);

#ifdef PM_DEBUG
extern void SwayGrass_DebugIncChain(FIELDSYS_WORK * fsys, int n);
extern void SwayGrass_DebugSetChain(FIELDSYS_WORK * fsys, int n);
extern void SwayGrass_GetGrassInfo(	FIELDSYS_WORK * fsys, const u8 inIdx,
									int *outX, int *outZ, u8 *outTbl,
									BOOL *outValid, BOOL *outChainFlg, BOOL *outRare);
#endif

#endif	//_SWAY_GRASS_ENC_H_

