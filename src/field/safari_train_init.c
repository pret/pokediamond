//=============================================================================
/**
 * @file	safari_train_init.c
 * @bfief	サファリを縦断する乗り物の処理(初期化)
 * @author	Nozomu Saito
 *
 */
//=============================================================================

#include "common.h"
#include "fieldsys.h"
#include "include/savedata/gimmickwork.h"
//#include "../fielddata/build_model/build_model_id.h"
#include "field_gimmick_def.h"
//#include "system/snd_tool.h"
#include "safari_train_def.h"

#include "safari_train_local.h"

//--------------------------------------------------------
//前方宣言------------------------------------------------
void SafariTrain_Init(FIELDSYS_WORK *fsys);
//--------------------------------------------------------

//---------------------------------------------------------------------------
/**
 * @brief	初期化
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void SafariTrain_Init(FIELDSYS_WORK *fsys)
{	
	int id;
	GIMMICKWORK *work;
	SAFARI_TRAIN_WORK *train_work;
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));

	id = GIMMICKWORK_GetAssignID(work);
	if (id != FLD_GIMMICK_SAFARI_TRAIN){
		GIMMICKWORK_Assign(work, FLD_GIMMICK_SAFARI_TRAIN);
		train_work = (SAFARI_TRAIN_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_SAFARI_TRAIN);
		train_work->NowPos = TRAIN_POS_3;
	}
}
