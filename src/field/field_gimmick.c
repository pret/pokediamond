//============================================================================================
/**
 * @file	field_gimmick.c
 * @brief	マップ固有の仕掛けを発動するかどうかを判定するソース
 * @author	saito
 * @date	2006.02.09
 *
 */
//============================================================================================

#include "include/savedata/gimmickwork.h"
#include "field_gimmick_def.h"
#include "field_gimmick.h"
#include "gym.h"
#include "fieldsys.h"		//for	GameSystem_GetSaveData
#include "safari_train.h"
#include "fld_lift.h"

const static FLD_GMK_SETUP_FUNC FldGimmickSetupFunc[FLD_GIMMICK_MAX] = {
	NULL,					//0:無し
	GYM_SetupWaterGym,		//1:水ジム
	GYM_SetupGhostGym,		//2:ゴーストジム
	GYM_SetupSteelGym,		//3:鋼ジム
	GYM_SetupCombatGym,		//4:格闘ジム
	GYM_SetupElecGym,		//5:電気ジム
	SafariTrain_Setup,		//6:サファリ電車
	FLIFT_Setup,			//7:フィールドリフト
};

const static FLD_GMK_END_FUNC FldGimmickEndFunc[FLD_GIMMICK_MAX] = {
	NULL,					//0:無し
	NULL,					//1:水ジム
	NULL,					//2:ゴーストジム
	GYM_EndSteelGym,		//3:鋼ジム
	GYM_EndCombatGym,		//4:格闘ジム
	GYM_EndElecGym,			//5:電気ジム
	NULL,					//6:サファリ電車
	NULL,					//7:フィールドリフト
};

const static FLD_GMK_HIT_CHECK FldGimmickHitCheck[FLD_GIMMICK_MAX] = {
	NULL,					//0:無し
	GYM_HitCheckWaterGym,	//1:水ジム
	NULL,					//2:ゴーストジム
	GYM_HitCheckSteelGym,	//3:鋼ジム
	GYM_HitCheckCombatGym,	//4:格闘ジム
	GYM_HitCheckElecGym,	//5:電気ジム
	NULL,					//6:サファリ電車
	NULL,					//7:フィールドリフト
};

//---------------------------------------------------------------------------
/**
 * @brief	ギミックのセットアップ関数
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void FLDGMK_SetUpFieldGimmick(FIELDSYS_WORK *fsys)
{
	int id;
	GIMMICKWORK *work;
	//ギミックワーク取得
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	//ギミックコードを取得
	id = GIMMICKWORK_GetAssignID(work);
	
	if (id == FLD_GIMMICK_NONE){
		return;					//ギミック無し
	}
	//ギミックセットアップ
	FldGimmickSetupFunc[id](fsys);
}

//---------------------------------------------------------------------------
/**
 * @brief	ギミックの終了関数
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void FLDGMK_EndFieldGimmick(FIELDSYS_WORK *fsys)
{
	int id;
	GIMMICKWORK *work;
	//ギミックワーク取得
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	//ギミックコードを取得
	id = GIMMICKWORK_GetAssignID(work);
	
	if (id == FLD_GIMMICK_NONE){
		return;					//ギミック無し
	}
	//ギミック終了
	if (FldGimmickEndFunc[id] != NULL){
		FldGimmickEndFunc[id](fsys);
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	ギミック用特殊当たり判定処理
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	BOOL	TRUE:通常当たり判定を行なわない	FALSE：通常当たり判定を行う
 */
//---------------------------------------------------------------------------
BOOL FLDGMK_FieldGimmickHitCheck(	FIELDSYS_WORK *fsys,
									const int inGridX, const int inGridZ,
									const fx32 inHeight,
									BOOL *outHit)
{
	int id;
	GIMMICKWORK *work;
	//ギミックワーク取得
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	//ギミックコードを取得
	id = GIMMICKWORK_GetAssignID(work);
	
	if (id == FLD_GIMMICK_NONE){
		return FALSE;					//ギミック無し
	}
	//ギミック終了
	if (FldGimmickHitCheck[id] != NULL){
		BOOL rc;
		rc = FldGimmickHitCheck[id](fsys, inGridX, inGridZ, inHeight, outHit);
		return rc;
	}
	
	return FALSE;						//処理無し
}
