//==============================================================================
/**
 * @file	contest_savedata.c
 * @brief	コンテストセーブデータ操作
 * @author	matsuda
 * @date	2006.06.03(土)
 */
//==============================================================================
#include "savedata/savedata_def.h"
#include "savedata/savedata.h"
#include "savedata/contest_savedata.h"
#include "contest/contest_def.h"
#include "contest_savedata_local.h"
#include "gflib/assert.h"



//==============================================================================
//	定数定義
//==============================================================================
///対戦成績記録最大数
#define CON_RECORD_COUNT_MAX		(9999)



//--------------------------------------------------------------
/**
 * @brief	カスタムボールのサイズを取得
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	CONDATA_GetWorkSize(void)
{
	return sizeof(CONTEST_DATA);
}

//---------------------------------------------------------------------------
/**
 * @brief	コンテストセーブデータの初期化処理
 * @param	condata		コンテストセーブデータへのポインタ
 */
//---------------------------------------------------------------------------
void CONDATA_Init(CONTEST_DATA * condata)
{
	int ranking, type;
	
	for(type = 0; type < CONTYPE_MAX; type++){
		for(ranking = 0; ranking < BREEDER_MAX; ranking++){
			condata->TuushinRecord[type][ranking] = 0;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   対戦成績をセットする
 *
 * @param   condata		コンテストデータへのポインタ
 * @param   type		CONTYPE_???
 * @param   ranking		順位(0origin)
 */
//--------------------------------------------------------------
void CONDATA_RecordAdd(SAVEDATA *sv, int type, int ranking)
{
	CONTEST_DATA *condata;
	
	condata = SaveData_Get(sv, GMDATA_ID_CONTEST);
	if(condata->TuushinRecord[type][ranking] < CON_RECORD_COUNT_MAX){
		condata->TuushinRecord[type][ranking]++;
	}
}

//--------------------------------------------------------------
/**
 * @brief   対戦成績を取得する
 *
 * @param   condata		コンテストデータへのポインタ
 * @param   type		CONTYPE_???
 * @param   ranking		取得する順位(0origin)
 *
 * @retval  対戦成績
 */
//--------------------------------------------------------------
u16 CONDATA_GetValue(SAVEDATA *sv, int type, int ranking)
{
	CONTEST_DATA *condata;
	
	condata = SaveData_Get(sv, GMDATA_ID_CONTEST);
	return condata->TuushinRecord[type][ranking];
}

