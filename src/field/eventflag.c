//============================================================================================
/**
 * @file	eventflag.c
 * @bfief	セーブフラグ、ワーク操作
 * @author	Tamada
 * @author	Satoshi Nohara
 * @date	05.10.22
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"

#include "system/gamedata.h"
#include "system/savedata.h"		//SaveData_Get & GMDATA_ID_EVENT_WORK

#include "field/eventflag.h"		//EVENTWORK
#include "script.h"
#include "field/evwkdef.h"


//=============================================================================
//=============================================================================
//------------------------------------------------------------------
/**
 * @brief	イベントワーク構造体の定義
 */
//------------------------------------------------------------------
struct _EVENTWORK {
	u16 work[EVENT_WORK_AREA_MAX];	//ワーク
	u8	flag[EVENT_FLAG_AREA_MAX];	//フラグ
};

//セーブしないフラグ
static u8 EventCtrlFlag[CTRLFLAG_AREA_MAX] = {};


//=============================================================================
//=============================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
int EventWork_GetWorkSize(void)
{
	return sizeof(EVENTWORK);
}

//------------------------------------------------------------------
/**
 * @brief	イベントワークを生成する
 *
 * @param	heapID		ヒープID
 *
 * @return	EVENTWORKへのポインタ
 */
//------------------------------------------------------------------
EVENTWORK * EventWork_AllocWork(int heapID)
{
	EVENTWORK * event;
	event = sys_AllocMemory(heapID, sizeof(EVENTWORK));

	EventWork_Init(event);

	return event;
}

//------------------------------------------------------------------
/**
 * @brief	イベントワークの初期化
 * @param	evwk	EVENTWORKへのポインタ
 */
//------------------------------------------------------------------
void EventWork_Init(EVENTWORK * evwk)
{
	//不正な値が入っているのでクリア
	memset( evwk, 0, sizeof(EVENTWORK) );
}

//------------------------------------------------------------------
/**
 * @brief	セーブデータからイベントワークへのポインタを取得する
 *
 * @param	sv	セーブデータへのポインタ
 *
 * @return	セーブデータ中のEVENTWORKへのポインタ
 */
//------------------------------------------------------------------
EVENTWORK * SaveData_GetEventWork(SAVEDATA * sv)
{
	EVENTWORK * event;
	event = (EVENTWORK *)SaveData_Get(sv, GMDATA_ID_EVENT_WORK);
	return event;
}

//------------------------------------------------------------------
/**
 * @brief	イベントフラグをチェックする
 *
 * @param	ev			イベントワークへのポインタ
 * @param	flag_no		フラグナンバー
 *
 * @retval	"1 = フラグON"
 * @retval	"0 = フラグOFF"
 */
//------------------------------------------------------------------
BOOL EventWork_CheckEventFlag( EVENTWORK * ev, u16 flag_no)
{
	u8 * p = EventWork_GetEventFlagAdrs( ev, flag_no );
	if( p != NULL ){
		if( *p & ( 1 << (flag_no % 8) ) ){ return 1; }
	}
	return 0;
}


//------------------------------------------------------------------
/**
 * @brief	イベントフラグをセットする
 *
 * @param	ev			イベントワークへのポインタ
 * @param	flag_no		フラグナンバー
 *
 * @return	none
 */
//------------------------------------------------------------------
void EventWork_SetEventFlag( EVENTWORK * ev, u16 flag_no)
{
	u8 * p = EventWork_GetEventFlagAdrs( ev, flag_no );
	if( p == NULL ){ return; }
	*p |= 1 << ( flag_no % 8 );
	return;
}


//------------------------------------------------------------------
/**
 * @brief	イベントフラグをリセットする
 *
 * @param	ev			イベントワークへのポインタ
 * @param	flag_no		フラグナンバー
 *
 * @return	none
 */
//------------------------------------------------------------------
void EventWork_ResetEventFlag( EVENTWORK * ev, u16 flag_no)
{
	u8 * p = EventWork_GetEventFlagAdrs( ev, flag_no );
	if( p == NULL ){ return; }
	*p &= ( 0xff ^ ( 1 << (flag_no % 8) ) );
	return;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	イベントフラグのアドレスを取得する
 *
 * @param	flag_no		フラグナンバー
 *
 * @retval	"NULL != フラグアドレス"
 * @retval	"NULL = 未定義"
 */
//--------------------------------------------------------------------------------------------
u8 * EventWork_GetEventFlagAdrs( EVENTWORK * ev, u16 flag_no )
{
	if( flag_no == 0 ){
		return NULL;
	}else if( flag_no < SCFLG_START ){

		if( (flag_no / 8) >= EVENT_FLAG_AREA_MAX ){
			GF_ASSERT( (0) && "フラグナンバーが最大数を超えています！" );
		}

		return &ev->flag[flag_no/8];
	}else{

		if( ((flag_no - SCFLG_START) / 8) >= CTRLFLAG_AREA_MAX ){
			GF_ASSERT( (0) && "フラグナンバーが最大数を超えています！" );
		}

		return &( EventCtrlFlag[ (flag_no - SCFLG_START) / 8 ] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	イベントワークアドレスを取得
 *
 * @param	ev			イベントワークへのポインタ
 * @param	work_no		ワークナンバー
 *
 * @return	"ワークのアドレス"
 *
 * @li	work_no < 0x8000	通常のセーブワーク
 * @li	work_no >= 0x8000	スクリプト制御ワークの中に確保しているワーク
 */
//--------------------------------------------------------------------------------------------
u16 * EventWork_GetEventWorkAdrs( EVENTWORK * ev, u16 work_no )
{
	if( (work_no - SVWK_START) >= EVENT_WORK_AREA_MAX ){
		GF_ASSERT( (0) && "ワークナンバーが最大数を超えています！" );
	}

	return &ev->work[ work_no - SVWK_START ];
}


