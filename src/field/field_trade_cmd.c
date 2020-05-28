//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_trade_cmd.c
 *	@brief		ゲーム内交換　常駐　イベントコマンド
 *	@author		tomoya takahashi
 *	@data		2006.05.16
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "fieldsys.h"
#include "field_event.h"
#include "ev_mapchange.h"
#include "ev_time.h"


#define __FIELD_TRADE_CMD_H_GLOBAL
#include "field_trade_cmd.h"

//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
typedef struct {
	FLD_TRADE_WORK* p_trade;
	u32 seq;
	int party_pos;
	DEMO_TRADE_PARAM demo;

	POKEMON_PARAM*   sendPoke;	///< こちらから送ったポケモン
	POKEMON_PARAM*   recvPoke;	///< あちらから送られてきたポケモン
} FIELD_TRADE_EVENT_WORK;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static BOOL GMEVENT_FldTrade( GMEVENT_CONTROL * event );
static void FLD_TradeStartDemo( GMEVENT_CONTROL * event );

// デモ開始
void FLD_TradeStartDemo( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * p_fsys = FieldEvent_GetFieldSysWork(event);
	FIELD_TRADE_EVENT_WORK* p_work = FieldEvent_GetSpecialWork(event);

	{
		FS_EXTERN_OVERLAY(demo_trade);

		static const PROC_DATA  TradeDemoProcData = {
			TradeDemoProc_Init,
			TradeDemoProc_Main,
			TradeDemoProc_Quit,
			FS_OVERLAY_ID(demo_trade),
		};
		EventCmd_CallSubProc(event, &TradeDemoProcData, &p_work->demo );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	交換実行
 *	@param	event イベント
 *	@return
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_FldTrade( GMEVENT_CONTROL * event )
{
	FIELDSYS_WORK * p_fsys = FieldEvent_GetFieldSysWork(event);
	FIELD_TRADE_EVENT_WORK* p_work = FieldEvent_GetSpecialWork(event);

	switch( p_work->seq ){
	case 0:	// 交換デモデータ作成
		FLD_TradeDemoDataMake( p_fsys, p_work->p_trade, p_work->party_pos, &p_work->demo, p_work->sendPoke, p_work->recvPoke );

		// データ部分交換
		FLD_Trade( p_fsys, p_work->p_trade, p_work->party_pos );
		p_work->seq++;
		break;

	case 1:	// フェードアウト
		EventCmd_FieldFadeOut( event );
		p_work->seq++;
		break;

	case 2:	// フィールド破棄
		EventCmd_FinishFieldMap(event);
		p_work->seq++;
		break;

	case 3:	//交換デモ
		FLD_TradeStartDemo( event );
		p_work->seq++;
		break;

	case 4:	// フィールド復帰
		EventCmd_StartFieldMap( event );
		p_work->seq++;
		break;

	case 5:	// フェードイン
		EventCmd_FieldFadeIn( event );
		p_work->seq++;
		break;

	case 6:	// 終了
		sys_FreeMemoryEz( p_work->sendPoke );
		sys_FreeMemoryEz( p_work->recvPoke );
		sys_FreeMemoryEz( p_work );
		return TRUE;
	}
	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	交換実行
 *
 *	@param	event		イベントワーク
 *	@param	p_work		交換用ワーク
 *	@param	party_pos	パーティーナンバー
 *	@param	heapID
 */
//-----------------------------------------------------------------------------
void EventCmd_FldTrade(GMEVENT_CONTROL * event, FLD_TRADE_WORK* p_work, int party_pos, u32 heapID )
{
	FIELD_TRADE_EVENT_WORK* p_data = sys_AllocMemory( heapID, sizeof(FIELD_TRADE_EVENT_WORK) );
	memset( p_data, 0, sizeof(FIELD_TRADE_EVENT_WORK) );
	p_data->seq =  0;
	p_data->p_trade = p_work;
	p_data->party_pos = party_pos;

	// ポケモンデータ保存用領域を作成
	p_data->sendPoke = PokemonParam_AllocWork( heapID );
	p_data->recvPoke = PokemonParam_AllocWork( heapID );
	
	FieldEvent_Call(event, GMEVENT_FldTrade, p_data);
}
