//============================================================================================
/**
 * @file	demo_trade.h
 * @brief	ポケモン交換デモ
 * @author	taya
 * @date	2006.04.07
 */
//============================================================================================
#ifndef __DEMO_TRADE_H__
#define __DEMO_TRADE_H__

#include "system\procsys.h"
#include "poketool\poke_tool.h"
#include "savedata\mystatus.h"
#include "savedata\config.h"

//----------------------------------------------
/**
 * 背景タイプ
 */
//----------------------------------------------
typedef enum {
	DEMO_TRADE_BGTYPE_MORNING,		///< 朝～昼の青い空
	DEMO_TRADE_BGTYPE_EVENING,		///< 夕方頃のオレンジ空
	DEMO_TRADE_BGTYPE_NIGHT,		///< 夜の暗い空
	DEMO_TRADE_BGTYPE_WIFI,			///< WI-FI専用チューブ背景
}DEMO_TRADE_BGTYPE;

//----------------------------------------------
/**
 * 再生シーケンス指定
 */
//----------------------------------------------
typedef enum {
	DEMO_TRADE_SEQ_FULL = 1,			///< 全部
	DEMO_TRADE_SEQ_SEND_ONLY = 2,		///< 送る部分だけ
	DEMO_TRADE_SEQ_RECV_ONLY = 4,		///< 受け取る部分だけ
}DEMO_TRADE_SEQFLAG;



//-------------------------------------------------
/**
 *	PROC用パラメータ
 */
//-------------------------------------------------
typedef struct {
	const POKEMON_PASO_PARAM*   sendPoke;	///< こちらから送ったポケモン
	const POKEMON_PASO_PARAM*   recvPoke;	///< あちらから送られてきたポケモン
	const MYSTATUS*             partner;	///< 交換相手のパラメータ

	DEMO_TRADE_BGTYPE           bgType;		///< デモ背景タイプ
	DEMO_TRADE_SEQFLAG          seqFlag;	///< 再生シーケンス

	const CONFIG*      config;		///< ユーザ設定コンフィグデータ

}DEMO_TRADE_PARAM;


//-------------------------------------------------
/**
 *	PROC関数
 */
//-------------------------------------------------
extern PROC_RESULT TradeDemoProc_Init( PROC * proc, int * seq );
extern PROC_RESULT TradeDemoProc_Quit( PROC * proc, int * seq );
extern PROC_RESULT TradeDemoProc_Main( PROC * proc, int * seq );


//-------------------------------------------------
/**
 *	オーバーレイ宣言
 */
//-------------------------------------------------
FS_EXTERN_OVERLAY(demo_trade);

#endif
