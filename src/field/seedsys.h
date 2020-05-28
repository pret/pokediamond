//============================================================================================
/**
 * @file	seedsys.h
 * @brief
 * @author	tamada GAME FREAK inc.
 * @date	2006.02.09
 */
//============================================================================================

#ifndef	__SEEDSYS_H__
#define	__SEEDSYS_H__

#include "field_common.h"
#include "fieldobj.h"

#include "savedata/seedbed.h"

//============================================================================================
//============================================================================================
typedef struct SEEDSYS_WORK SEEDSYS_WORK;

//============================================================================================
//============================================================================================
#define SEEDITEMCHK_NOUSE			0x00		///< なにも使えない
#define	SEEDITEMCHK_USE_SEED		0x01		///<きのみをうえることができる
#define	SEEDITEMCHK_USE_COMPOST		0x02		///<こやしをうえることができる
#define SEEDITEMCHK_USE_ZYOURO		0x04		///<じょうろで水やりができる


//============================================================================================
//============================================================================================
extern SEEDSYS_WORK * SeedSys_Init(FIELDSYS_WORK * fsys, int heapID);
extern void SeedSys_Finish(SEEDSYS_WORK * seedsys);
extern void SeedSys_Growth(FIELDSYS_WORK * fsys, int diff_minute);
extern void SeedSys_CheckInScreen(FIELDSYS_WORK * fsys);

extern void SeedSys_SetCompost(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj, u16 item_compost);
extern void SeedSys_SetNuts(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj, u16 item_nuts);
extern BOOL SeedSys_TakeNuts(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj);
extern void SeedSys_SetWater(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj);

extern SEEDSTAT SeedSys_GetSeedStatus(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj);
extern int SeedSys_GetSeedType(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj);
extern u16 SeedSys_GetSeedTypeItem(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj);
extern int SeedSys_GetSeedCount(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj);
extern u16 SeedSys_GetCompost(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj);
extern SEEDGROUND SeedSys_GetGroundStatus(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj);


//きのみがうえられるかどうかのチェック
extern BOOL SeedSys_EnableSetKinomi(FIELDSYS_WORK * fsys, FIELD_OBJ_PTR fldobj);

//水やりイベント呼び出し
extern void EventCall_SeedWater(FIELDSYS_WORK * fsys);
//水やりイベント終了（自機フォームを通常に戻す）
extern void SeedSys_ResetPlayerForm(FIELDSYS_WORK * fsys);

//つかえるどうぐの種類チェック（SEEDITEMCHK_～の指定を参照）
extern u32 SeedSys_ItemUseCheck(const FIELDSYS_WORK * fsys, CONST_FIELD_OBJ_PTR fldobj);

#endif	/* __SEEDSYS_H__ */

