//=============================================================================
/**
 * @file	comm_save.c
 * @brief	通信を使った汎用関数
 * @author	Katsumi Ohno
 * @date    2006.03.14
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "savedata/savedata.h"
#include "communication/comm_save.h"

//==============================================================================
// 通信同期用定義
//==============================================================================
#define COMM_SAVE_SYNCHRO_NO1	( 111 )
#define COMM_SAVE_SYNCHRO_NO2	( 112 )
#define COMM_SAVE_SYNCHRO_NO3	( 113 )


//==============================================================================
// シーケンス定義
//==============================================================================
enum{
	COMMSAVE_SEQ_START=0,
	COMMSAVE_SEQ_SYNCRO1,
	COMMSAVE_SEQ_SAVE,
	COMMSAVE_SEQ_SYNCRO2,
	COMMSAVE_SEQ_SAVE_FINISH,
	COMMSAVE_SEQ_SYNCRO3,
	COMMSAVE_SEQ_END,
};
//==============================================================================
/**
 * @brief   通信同期セーブ処理初期化
 *
 * @param   savedata		
 * @param   BlockID		
 *
 * @retval  none		
 */
//==============================================================================
void CommSyncronizeSaveInit( int *seq )
{
	*seq = COMMSAVE_SEQ_START;
}


//==============================================================================
/**
 * @brief   通信同期セーブシーケンス
 *
 * @param   savedata	セーブデータ構造体へのポインタ
 * @param   seq			シーケンス管理用わーくのポインタ
 *
 * @retval  int			0:処理中	1:終了
 */
//==============================================================================
int CommSyncronizeSave( SAVEDATA *savedata, int BlockID, int *seq )
{
	SAVE_RESULT result;
	switch(*seq){
	// 1回目の同期開始
	case COMMSAVE_SEQ_START:
		CommTimingSyncStart( COMM_SAVE_SYNCHRO_NO1 );
		*seq = COMMSAVE_SEQ_SYNCRO1;
		break;

	// 同期終了＋セーブ初期化
	case COMMSAVE_SEQ_SYNCRO1:
		if(CommIsTimingSync(COMM_SAVE_SYNCHRO_NO1)){
			SaveData_DivSave_Init(savedata, BlockID);
			*seq = COMMSAVE_SEQ_SAVE;
			OS_Printf("同期１回目\n");
		}
		break;
	// セーブ
	case COMMSAVE_SEQ_SAVE:
		result = SaveData_DivSave_Main(savedata);
		GF_ASSERT(result != SAVE_RESULT_OK);
		GF_ASSERT(result != SAVE_RESULT_NG);
		if (result == SAVE_RESULT_LAST){
			*seq = COMMSAVE_SEQ_SYNCRO2;
			CommTimingSyncStart( COMM_SAVE_SYNCHRO_NO2 );
			OS_Printf("セーブ前半終了\n");
		}
		break;
	// 2回目の同期
	case COMMSAVE_SEQ_SYNCRO2:
		if(CommIsTimingSync(COMM_SAVE_SYNCHRO_NO2)){
			*seq = COMMSAVE_SEQ_SAVE_FINISH;
			OS_Printf("同期２回目\n");
		}
		break;
	// セーブ残りセクタ書き込み処理
	case COMMSAVE_SEQ_SAVE_FINISH:
		result = SaveData_DivSave_Main(savedata);
		GF_ASSERT(result != SAVE_RESULT_NG);
		GF_ASSERT(result != SAVE_RESULT_LAST);
		if (result == SAVE_RESULT_OK) {
			OS_Printf("セーブ後半終了\n");
			*seq = COMMSAVE_SEQ_SYNCRO3;
		}
		break;
	// 終了同期
	case COMMSAVE_SEQ_SYNCRO3:
			*seq = COMMSAVE_SEQ_END;
		break;
	// 終了
	case COMMSAVE_SEQ_END:
		return 1;
		break;
	}
	
	return 0;
}
