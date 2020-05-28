//=============================================================================
/**
 * @file	spray.c
 * @bfief	スプレー処理
 * @author	Nozomu Saito
 *
 *
 */
//=============================================================================

#include "common.h"
#include "field_common.h"
#include "savedata/encount.h"
#include "savedata/savedata.h"
#include "script.h"
#include "fielddata/script/common_scr_def.h"

#include "spray.h"

//==============================================================================
/**
 * 1歩ごとのスプレー効果減算
 *
 * @param	sv		セーブデータポインタ
 * 
 * @retval	BOOL	TRUE:スプレー効果切れ	FALSE:それ以外
 * 
 */
//==============================================================================
BOOL Spray_DecSpray(SAVEDATA * sv, FIELDSYS_WORK * fsys)
{
	u8 *spray;
	//セーブデータ取得
	spray = EncDataSave_GetSprayCnt(EncDataSave_GetSaveDataPtr(sv));
	//0でなければ、減算
	if ( (*spray) > 0 ){
		(*spray)--;
		//減算した結果0になったら効果切れメッセージ
		if( (*spray)==0 ){
			OS_Printf("スプレー効果切れ\n");
			EventSet_Script(fsys, SCRID_END_SPRAY, NULL);
			return TRUE;
		}
	}
	return FALSE;
}
