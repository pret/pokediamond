//============================================================================================
/**
 * @file	field_gimmick.h
 * @brief	マップ固有の仕掛けを発動するかどうかを判定するソース
 * @author	saito
 * @date	2006.02.09
 *
 */
//============================================================================================
#ifndef __FIELD_GIMMICK_H__
#define __FIELD_GIMMICK_H__

#include "field_common.h"

typedef void (*FLD_GMK_SETUP_FUNC)(FIELDSYS_WORK *);
typedef void (*FLD_GMK_END_FUNC)(FIELDSYS_WORK *);
typedef BOOL (*FLD_GMK_HIT_CHECK)(FIELDSYS_WORK * , const int, const int, const fx32, BOOL* );

extern void FLDGMK_SetUpFieldGimmick(FIELDSYS_WORK *fsys);
extern void FLDGMK_EndFieldGimmick(FIELDSYS_WORK *fsys);
extern BOOL FLDGMK_FieldGimmickHitCheck(FIELDSYS_WORK *fsys,
										const int inGridX, const int inGridZ,
										const fx32 inHeight,
										BOOL *outHit);
#endif	//__FIELD_GIMMICK_H__

